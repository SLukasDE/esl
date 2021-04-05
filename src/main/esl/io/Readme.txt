Einleitung
==========

Das Package esl::utility::io stellt Klassen bereit, um Daten zwischen Tasks auszutauschen.
Es geht im Folgenden daraum einen effiziente Möglichbeit bereitszustelen, sodass ein Task, der Daten erzeugt diese einem anderen Task bereitstellen kann.

Dabei soll zum einen berücksichtigt werden, dass ein Task entweder jederzeit in der Lage ist Daten zu erzeugen bzw. bereit ist Daten entgegenzunehmen,
aber auch die Situtation betrachtet werden muss, dass ein Task darüber informieren können soll, wenn bei ihm neue Daten bereitstehen bzw. wenn er bereit ist Daten entgegenzunehmen.

Zum anderen soll es möglich sein unnötige Kopieraktionen von Daten zu vermeiden. Z.B. kann es Task geben, die Daten direkt in einem angegeben Zielspeicherbereich erzeugen können,
während es auch Tasks gibt, die die Daten in einem selbst verwalteten Speicherbereich bereitstellen, auf den der lesende Tasks dann zugreifen kann.
Aber auch bei lesenden Tasks gibt es diese beide Möglichkeiten. Entweder kann der lesende Task mit Daten an einem vorgegebenen Speicherbereich direkt umgehen
oder er gibt einen Speicherbereich vor, an dem er die Daten benötigt.


I. Die Basis der Klassenbibliothek stellen sog. Reader und Writer dar
---------------------------------------------------------------------

- Ein Reader-Objekt entspricht im wesentlich einer Klasse mit der folgenden Methode:
  std::size_t read(void* dest, std::size_t size)

- Ein Writer-Objekt entspricht im wesentlich einer Klasse mit der folgenden Methode:
  std::size_t write(const void* source, std::size_t size)

Beide Objekte können sowohl für das Übertragen von Daten von Task 1 an Task 2 genutzt werden.
Welches der Objekte zum Einsatz kommt ist erstmal eine Frage der Prespektive:
- Entweder ließt Task 2 die Daten von Task 1. Dann braucht Task 2 ein Reader-Objekt, dass Task 1 bereitstellen muss.
- Oder Task 1 schreibt die Daten nach Task 2. Dann braucht Task 1 ein Writer-Objekt, dass Task 2 bereitstellen muss.

Bei der oben beschriebenen Design-Entscheidung ist auch zu berücksichten, in welchem Speicherbereich Task 1 die Daten bereitstellen kann und ob Task 2 die Daten direkt aus einem
fremden Speicherbereich weiterverarbeiten kann, oder sich die Daten in einem selbst verwalteten Speicherbereich kopieren muss.

Im folgenden werden 2 Fälle beim Daten erzeugenden Task 1 beschrieben:

Fall 1:
: Task 1 erzeugt die Daten erst beim Abrufen und kann diese an eine beliebige Stelle im Speicher abliefern.
Hier macht es Sinn, wenn Task 1 ein Reader-Objekt zum Auslesen der Daten bereitstellt, auf das Task 2 Zugriff hat.
Somit kann Task 2 den Speicherbereich den sich Task 2 wünscht beim Aufruf der Methode "read" vorgeben.

Fall 2:
: Task 1 hat einen eigenen Speicherbereich, in dem er die Daten erzeugt. Aus diesem Speicherbereich können die Daten dann ausgelesen werden.
Hier macht es Sinn, wenn der konsumierende Task 2 ein Writer-Objekt zum Empfangen von Daten bereitstellt, welches Task 1 mitgeteilt wurde.
Somit kann Task 1 den Speicherbereich an dem sich die Daten befinden Task 2 beim Aufruf der Methode "write" mitteilen.

Ebenso lassen sich die beiden Fälle für den Daten empfangenden Task 2 beschreiben, bei denen aus seiner Sicht die Verwendung eines Read- oder Writer-Ojektes sinnvoll wäre.
Wenn alle die beiden Tasks ideal zusammen passen, werden unnötige Kopieraktionen vermieden, weil entweder Task 1 direkt in den Speicher schreibt, an den Task 2 die Daten benötigt
oder Task 2 die Daten direkt von der Stelle weiterverarbeiten kann, an der sie von Task 1 abgelegt wurden.

Fall 3:
Falls Task 1 die Daten an eine beliebige Stelle anlegen kann und Task 2 von einer beliebigen Stelle zur weiteren Verarbeiten entgegen nehmen kann, ist ein Zwischenspeicher
erforderlich, der weder von Task 1, noch von Task 2 bereitgestellt wird. Aber auch in diesem Fall findet kein unnötiges Kopieren von Speicherbereichen statt.

Fall 4:
Lediglich bei der letzten Kombination muss Speicher kopiert werden und zwar, wenn Task 1 sein Ergebnis zwingend in einem selbst verwalteten Speicherbereich vorliegen hat
und Task 2 die Daten zwingend in einem ebenfalls selbst vorgegebenen Speicherbereich benötigt. Hier könnte Task 2 über ein Reader-Objekt von Task 1 die Daten auslesen, womit sie
aus dem Speicherbereich von Task 1 in den über "read" vorgegebenen Speicherbereich von Task 2 kopiert werden.

Bei dem Design von produzierenden oder kosumierenden Tasks macht es also Sinn, falls möglich sie immer so zu entwerfen,
dass sie ihre Daten direkt an eine vorgegebene Stelle abliefern können bzw. die zu verarbeitenden Daten direkt von einem vorgegenen Speicherbereich weiterverarbeiten können.
Damit ist man immer auf der sicheren Seite, dass Daten nicht unnötig kopiert werden (Fall 3).
Konkret bedeutet dies, dass ein empfangender Tasks wenn möglich ein Writer-Objekt bereitstellen sollte und ein sendender Task ein Reader-Objekt bereitstellen sollte.
Häufig ist es jedoch nicht möglich seinen Task so zu entwerfen. Wenn nur der vor- oder nachgelagerte Task nicht so entwickelt wurde, läßt sich unnötiges Speicherkopieren
noch immer vermeiden. Lediglich im Fall 4 läßt es sich nicht vermeiden.


II. Events mittels Erweiterung durch Producer und Consumer
----------------------------------------------------------

II.1 Daten senden mittels Writer- oder Consumer-Objekt
------------------------------------------------------

Es gibt Tasks die kontinuierlich Daten erzeugen können. Z.B. wäre ein Tasks, der zeilenweise Fibonacci-Zahlen erzeugt jederzeit in der Lage weitere Daten zu liefern.
Ein lesender Task 2, der die Daten auf die Konsole ausgibt, könnte fortlaufend die Methode "read" des Read-Objektes von Task 1 aufrufen, die empfangenen Daten auf die Konsole
ausgeben und beim Erreichen einer maximalen Zahl abbrechen.
Umgekehrt könnte dieser Task 2 auch dem Task 1 ein Write-Objekt bereitstellen und Taks 1 würde fortlaufend dessen "write"-Methode aufrufen, bis die "write"-Methode mitteilt,
dass sie an keinen weiteren Daten mehr interessiert ist.

Es gibt aber auch Tasks, die nicht zu jeder Zeit Daten vorliegen haben, z.B. wenn sie Daten über das Netz empfangen. Erst wenn neue Daten eintreffen macht es für einen
Task 2 Sinn diese bei dem Task 1 abzufragen. Würde wie zuvor beschrieben Task 2 kontinuierlich die "read" Methode aufrufen, so würde sie die meiste Zeit 0 gelesene Bytes
als Return-Wert zurück geben. Eine solche "Endlosschleife" würde zwar funktionieren, aber die CPU heiß laufen lassen. Ein Sleep zwischen den "read"-Aufrufen ist auch keine
gute Lösung, weil ein Sleep auch dann abgewartet würde, selbst wenn in der Zwischenzeit neue Daten vorliegen. Die Reaktionsgeschwindigkeit der Anwendung leidet somit.

In diesem Fall wäre die Bereitstellung eines Writers ein Ausweg. Wenn Task 2 einen Writer bereitstellt, kann Task 1 die "write" Methode aufrufen, sobald Task 1 neue Daten
vorliegen hat. Der umgekehrte Fall, dass Task 1 einen Reader bereitstellt und nur über diesen Weg in der Lage ist Daten abzuliefern, macht es dann erforderlich, Task 2
irgendwie darüber zu informieren, dass neue Daten vorliegen.

Zum Verallgemeinern dieser Situation sollte einem sendenden Task immer einen Teil des empfangenden Task bekannt gemacht werden.
Entweder wird dem sendenden Task ein Writer-Objekt des empfangenden Tasks mitgeteilt, über dass er aktiv seine neuen Daten bekannt machen kann.
Oder es wird dem sendenden Task ein anderes Objekt des empfangenden Tasks mitgeteilt, über das er dem empfangenden Task mitteilen kann,
dass bei seinem Read-Objekt die "read" Methode nun Daten liefert. Bei diesem anderen Objekt handelt es sich um einen Consumer.

- Ein Consumer-Objekt entspricht im wesentlich einer Klasse mit der folgenden Methode:
  bool consume(Reader& reader)

Kennt der sendende Task das Consumer-Objekt des empfangenden Tasks, ruft er dessen "consume" Methode auf und übergibt ihr sein Reader-Objekt.
Solange die "consume"-Methode "true" zurück gibt, darf der sendende Tasks erneut die "consume"-Methode aufrufen, falls er noch Daten besitzt,
die noch nicht mittels "read" ausgelesen wurde.
Sobald die "consume"-Methode einmal "false" liefert, soll sie auch nicht mehr aufgerufen werden, selbst wenn zu einem späteren Zeitpunkt neue Daten eintreffen.

Zusammengefasst läßt sich bis hierhin folgendes festhalten:
Ein sendender Task bekommt entweder das Writer-Objekt oder das Consumer-Objekt des empfangenden Tasks mitgeteilt.


II.2 Daten empfangen mittels eigenem Reader- oder fremden Producer-Objekt
-------------------------------------------------------------------------

Der obere Fall behandelt nur die Situation, dass ein sendender Task nicht jederzeit in der Lage ist neue Daten zu senden.
Es ist aber auch denkbar, dass ein empfangender Task nicht jederzeit in der Lage ist neue Daten entgegenzunehmen.
Würde in diesem Fall ein sendender Task die "write" Methode des Writer-Objektes aufrufen, würde sie 0 Bytes geschrieben zurückgeben.
Genauso würde auch im Falle eines Consumer-Objektes die "consume" Methode zwar "true" zurück geben, aber sie hätte das übergebene Read-Objekt gar nicht angefasst.
Auch hier stellt sich wieder die Frage, wie mit dieser Situatuion umgegangen werden soll, denn es liegen ja Daten bereit.
Ein dauerhaftes Wiederholen der Aufrufe würde wieder die CPU heiß laufen lassen. Unter einem Sleep zwischen den Aufrufen würde die Reaktionsgeschwindigkeit leiden.

Zunächst ist das wiederholte Aufrufen solange okay, solange es einen Fortschritt gibt.
Aber sobald einmal keine Daten entgegen genommen wurden, sollte auch ein Ereignis abgewartet werden, dass für weitere Aufrufe Erfolg verspricht.
Folglich reicht es nicht aus, dass dem sendenden Task ein Teil des empfangenden Task bekannt gemacht wird.
Es muss auch dem empfangenden Task ein Teil des sendenden Task bekannt gemacht werden, über das der empfangende Task informiert, dass er empfangsbereit ist.

Eines der bereits bekannten Objekte ist das Read-Objekt des sendenden Tasks. Sobald er empfangsbereit ist, ruft der dessen "read" Methode auf.
Liegen keine Daten vor, liefert die Methode 0 Bytes gelesen und es erfolgt kein weiterer Aufruf. Gleichzeitig hat dieser Aufruf den sendenden Tasks darüber informiert,
dass er dem empfangenden Task nun wieder Daten senden darf, sobald welche vorliegen.

