# esl
C++ Enterprise Support Library

Somebody said C++ is oldes newest language. It's amazing to see how fast and powerful this language is and since C++11 it goes forward fortunately. Now there is a standard to work with threads and so on. And maybe there is a standard to make low level network communication in short future. This is useful and these standards will be well thought-out.

If you develop enterprise applications you need higher level features. It starts from using a good logging framework, using libraries for HTTP communication, working with databases and so on. There are many libraries available for all of this tasks, but all libraries are different. If you have choosen one library e.g. for making a HTTP server and you want to switch to another library then you have to rewrite much code.

With ESL I try to define some standard classes that you can use directy for some of this tasks (e.g. HTTP communication). But it is not an implementation. Implementations are bindings to this framework. As result you can use ESL directly and you link some specific implementation to your code, e.g. one for HTTP client communication and another one for logging if you need these two features. later if you are not satisfied with one of these implementaion then you can use another implementation without changing your code.
