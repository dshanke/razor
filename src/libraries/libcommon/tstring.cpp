#include "include\tstring.hpp"
#include <regex>


inline bool RegExMatch(const tstring & strSrc, const tstring & strExpr, bool bIgnoreCase) {
	const std::regex regEx(strExpr);
	const std::regex regExIgnoreCase(strExpr, std::regex_constants::icase);
	return std::regex_match(strSrc, bIgnoreCase ? regExIgnoreCase : regEx);
}