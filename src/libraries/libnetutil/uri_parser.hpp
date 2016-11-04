#ifndef __URI_PARSER__HPP__
#define __URI_PARSER__HPP__

#include "tstring.hpp"
#include "uri_tokens.hpp"

namespace razor {

#if 0
	struct ParsedTokenInfo {
		size_t StartPos = tstring::npos;
		size_t EndPos = tstring::npos;
		bool Valid = false;
		bool Empty() const { return StartPos == tstring::npos || tstring::npos == EndPos; }
	};
#endif
	//URI = scheme ":" hier - part["?" query]["#" fragment]
	// where hier - part is as follows:
	// hier-part   = "//" authority path-abempty
	//                 / path - absolute
	//	               / path - rootless
	//	               / path - empty
	// Rules:
	// The scheme and path components are mandatory (path may be empty)
	// When authority is present, the path must either be empty or begin with a /
	// The query component is indicated by the first question mark ("?") character and terminated by a number sign ("#") character or by the end of the URI.
	// 

	class URIParser {
	public:
		static UriTokens Parse(const tstring & strUri);
#if 0
		static ParsedTokenInfo ParseScheme(const tstring & strUri, const size_t & startPos, const size_t & endPos = tstring::npos);
		static ParsedTokenInfo ParseAuthority(const tstring & strUri, const size_t & startAtPos, const size_t & endPos = tstring::npos);
		static ParsedTokenInfo ParsePath(const tstring & strUri, const size_t & startAtPos, const size_t & endPos = tstring::npos);
		static ParsedTokenInfo ParseQuery(const tstring & strUri, const size_t & startAtPos, const size_t & endPos = tstring::npos);
		static ParsedTokenInfo ParseFragment(const tstring & strUri, const size_t & startAtPos, const size_t & endPos = tstring::npos);
#endif
	};
}

#endif