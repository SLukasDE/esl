/*
MIT License
Copyright (c) 2019 Sven Lukas

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef ESL_LOGGING_CONFIG_H_
#define ESL_LOGGING_CONFIG_H_

#ifndef ESL_LOGGING_LEVEL

#if defined(ESL_LOGGING_LEVEL_SILENT)

#define ESL_LOGGING_LEVEL 0
#undef ESL_LOGGING_LEVEL_SILENT

#elif defined(ESL_LOGGING_LEVEL_ERROR)

#define ESL_LOGGING_LEVEL 1
#undef ESL_LOGGING_LEVEL_ERROR

#elif defined(ESL_LOGGING_LEVEL_WARN)

#define ESL_LOGGING_LEVEL 2
#undef ESL_LOGGING_LEVEL_WARN

#elif defined(ESL_LOGGING_LEVEL_INFO)

#define ESL_LOGGING_LEVEL 3
#undef ESL_LOGGING_LEVEL_INFO

#elif defined(ESL_LOGGING_LEVEL_DEBUG)

#define ESL_LOGGING_LEVEL 4
#undef ESL_LOGGING_LEVEL_DEBUG

#elif defined(ESL_LOGGING_LEVEL_TRACE)

#define ESL_LOGGING_LEVEL 5
#undef ESL_LOGGING_LEVEL_TRACE

#endif

#endif /* ESL_LOGGING_LEVEL */

#define ESL_LOGGING_LEVEL_SILENT 0
#define ESL_LOGGING_LEVEL_ERROR  1
#define ESL_LOGGING_LEVEL_WARN   2
#define ESL_LOGGING_LEVEL_INFO   3
#define ESL_LOGGING_LEVEL_DEBUG  4
#define ESL_LOGGING_LEVEL_TRACE  5

#ifndef ESL_LOGGING_LEVEL
#define ESL_LOGGING_LEVEL ESL_LOGGING_LEVEL_TRACE
#endif /* ESL_LOGGING_LEVEL */

#endif /* ESL_LOGGING_CONFIG_H_ */
