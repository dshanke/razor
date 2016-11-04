#include "include\tstring.hpp"
#include <regex>


namespace sutil {
	bool RegExMatch(const tstring & strSrc, const tstring & strExpr, bool bIgnoreCase) {
		const std::regex regEx(strExpr);
		const std::regex regExIgnoreCase(strExpr, std::regex_constants::icase);
		return std::regex_match(strSrc, bIgnoreCase ? regExIgnoreCase : regEx);
	}

	tstring StringTrim(const tstring & strSrc, const tstring & whitespace) {
		size_t first = strSrc.find_first_not_of(whitespace);
		if (first == tstring::npos)
			return _T(""); // no content
		size_t last = strSrc.find_last_not_of(whitespace);
		return strSrc.substr(first, (last - first + 1));
	}
}