# esl
![](https://img.shields.io/github/license/SLukasDE/esl.svg)

C++ Enterprise Support Library

Somebody said C++ is the oldes newest language. It's amazing to see how fast and powerful this language is. Since C++11 it goes forward fortunately. Every 3 years there will be a new C++ standard. All new features are usefull, but most of them are affecting core language features, like Lamdas, Coroutines, etc. and Algorithms, line std::unordered_map. But libary features affecting interacting with the OS get includes very slow. Since C++ 11 there is a standard to work with threads. Sind C++ 17 we are able to create a directory on the filesystem. Networking will be not avaliable before C++29.

If you develop enterprise applications you need higher level features. It starts from using a good logging framework, using libraries for HTTP communication, working with databases and so on. There are many libraries available for all kind of this tasks, but all libraries are different. If you have choosen one library e.g. for writing a HTTP server it is hard to switch to another library because every library is different. From my perspective there is a standard missing for this kind of higher level libraries.

It will take decades to get a C++ standard for HTTP communication, because first we neet a standard for network communicaiton. With ESL I will try to bypass this gap. I don't want to define a standard for low level network communication, but I want to define directly an API for high klevel features.like HTTP communication, database usage etc.

There are some design goals of ESL:
1. The usage of this API / classes must be simple.
2. ESL does NOT contain any specific implementation for this high level classes. It's just something like an interface definition and everone can develop it's own implementation.
3. Moving from one implementation to another one should not effect my code that is build on top of ESL.

Implementations are bindings to this framework. As result you can use ESL directly and you link some specific implementation to your code, e.g. one for HTTP client communication and another one for logging if you need these two features. Later if you are not satisfied with one of these implementaion then you can use another implementation without changing your code.
You just need to know how to use ESL classes if you want to use this framework. You don't need to know how the implementation works.

There are some basic example implementations availabe:
- mhd4esl
  This is an implementation of classes in the namespace esl::com::http::server. This implementaiton is based on Libmicrohttpd.
- curl4esl
  This is an implementation of classes in namespace esl::com::http::client based on libcurl.
- logbook4esl
  This is an implementation of classes in namespace esl::monitoring based on liblogbook.
- odbc4esl
  This is an implementation of classes in the namespacve esl::database based on iODBC (Mac) or unixODBC (Linux) or MS ODBC (Windows).
...

To make it easy, just use [OpenESL](https://github.com/SLukasDE/open-esl). This is a distribution of ESL that contains already implemetations for all classes.
