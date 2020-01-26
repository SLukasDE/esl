# esl
C++ Enterprise Support Library

Somebody said C++ is the oldes newest language. It's amazing to see how fast and powerful this language is and since C++11 it goes forward fortunately. Now there is a standard to work with threads and so on. And maybe there is a standard to make low level network communication in short time. This is useful and these standards will be well thought-out.

If you develop enterprise applications you need higher level features. It starts from using a good logging framework, using libraries for HTTP communication, working with databases and so on. There are many libraries available for all kind of this tasks, but all libraries are different. If you have choosen one library e.g. for writing a HTTP server it is hard to switch to another library because every library is different. From my perspective there is a standard missing for this kind of higher level libraries.

With ESL I try to define some standard classes that you can use directy for some of this tasks (e.g. HTTP communication).

I try to follow two goals with this framework.
1. The usage of this classes MUST BE simple, simple, simple. Almost everything should be self-explanatory.
2. ESL does NOT contain any specific implementation for this high level classes. It's just something like an interface definition and everybody can make it's own binding for this framework.

Implementations are bindings to this framework. As result you can use ESL directly and you link some specific implementation to your code, e.g. one for HTTP client communication and another one for logging if you need these two features. Later if you are not satisfied with one of these implementaion then you can use another implementation without changing your code.
You just need to know how to use ESL classes if you want to use this framework. You don't need to know how the implementation works.

There are some basic example implementations availabe:
- mhd4esl
  This is an implementation of esl::http::server::Socket based on Libmicrohttpd.
  Just include "mhd4esl/Module.h" into your main.cpp and bind this framework to esl by calling "esl::getModule().addModule(mhd4esl::getModule());".
- curl4esl
  This is an implementation for classes in namespace esl::http::client based on libcurl.
  Just include "curl4esl/Module.h" into your main.cpp and bind this framework to esl by calling "esl::getModule().addModule(curl4esl::getModule());".
- logbook4esl
  This is an implementation for classes in namespace esl::logging based on liblogbook.
  Just include "logbook4esl/Module.h" into your main.cpp and bind this framework to esl by calling "esl::getModule().addModule(logbook4esl::getModule());".
- boostst4esl
  This is an implementation of esl::Stacktrace and classes in namespace esl::stacktrace based on Boost Stacktrace.
  Just include "boostst4esl/Module.h" into your main.cpp and bind this framework to esl by calling "esl::getModule().addModule(boostst4esl::getModule());".
- zsystem4esl
  This is another implementation of esl::Stacktrace and classes in namespace esl::stacktrace based on libzsystem (Linux only!).
  Just include "zsystem4esl/Module.h" into your main.cpp and bind this framework to esl by calling "esl::getModule().addModule(zsystem4esl::getModule());".
