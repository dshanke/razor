#ifndef __TSTRING_HPP__
#define __TSTRING_HPP__

#include <string>

#ifdef UNICODE
#define _T(X) LX
typedef std::basic_string<wchar_t> tstring;
#else
#define _T(X) X
typedef std::basic_string<char> tstring;
#endif

#endif