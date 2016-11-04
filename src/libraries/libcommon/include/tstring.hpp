#ifndef __TSTRING_HPP__
#define __TSTRING_HPP__

#include <string>


#ifdef UNICODE
typedef wchar_t TCHAR;
#define _T(X) LX
typedef std::basic_string<wchar_t> tstring;
#else
typedef char TCHAR;
#define _T(X) X
typedef std::basic_string<char> tstring;
#endif

inline bool RegExMatch(const tstring & strSrc, const tstring & strExpr, bool bIgnoreCase = true);

#endif