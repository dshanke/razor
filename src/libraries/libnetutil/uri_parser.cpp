#include "uri_parser.hpp"
#include <regex>

namespace razor {


	inline bool AssessChar(TCHAR srcChar, TCHAR charToMatch, const size_t currentPos, size_t & firstOccurrencePos) {
		if (firstOccurrencePos == tstring::npos && charToMatch == srcChar) {
			firstOccurrencePos = currentPos;
			return true;
		}
		return false;
	}

	UriTokens URIParser::Parse(const tstring & strUri) {

		UriTokens tokenUri;
		const TCHAR * pRawStr = strUri.c_str();

		size_t firstColonPos = tstring::npos,
			firstSlashPos = tstring::npos,
			firstDoubleSlashPos = tstring::npos,
			firstQuestionPos = tstring::npos,
			firstHashPos = tstring::npos;

		size_t i = -1;
		while (pRawStr[++i] != TCHAR('\0')) {
			if (firstColonPos == tstring::npos && AssessChar(pRawStr[i], TCHAR(':'), i, firstColonPos)) {
				continue;
			}
			if (firstSlashPos == tstring::npos && AssessChar(pRawStr[i], TCHAR('/'), i, firstSlashPos)) {
				//if slash is found make sure it is not a double slash
				if (tstring::npos == firstDoubleSlashPos && TCHAR('\0') != pRawStr[i + 1] && TCHAR('/') == pRawStr[i + 1]) {
					firstDoubleSlashPos = firstSlashPos;
					firstSlashPos = tstring::npos;
					++i;
					continue;
				}
			}
			if (firstQuestionPos == tstring::npos && AssessChar(pRawStr[i], TCHAR('?'), i, firstQuestionPos)) {
				continue;
			}
			if (firstHashPos == tstring::npos && AssessChar(pRawStr[i], TCHAR('#'), i, firstHashPos)) {
				continue;
			}
		}
		UriTokens uriTokens;

		//Extract Fragment
		if (firstHashPos != tstring::npos) {
			uriTokens.Fragment(strUri.substr(firstHashPos + 1));
		}

		//Extract Query
		if (firstQuestionPos != tstring::npos) {
			if (firstQuestionPos < firstHashPos) { //occurs before fragment
				uriTokens.Query(strUri.substr(firstQuestionPos, firstHashPos - firstQuestionPos));
			}
			else { //if not Query part does not exist
				firstQuestionPos = tstring::npos;
			}
		}

		//Now Extract Scheme
		if (firstColonPos != tstring::npos) {
			if ((firstDoubleSlashPos != tstring::npos && firstColonPos < firstDoubleSlashPos) //should be occurring before Authority
				&& (firstSlashPos != tstring::npos && firstColonPos < firstSlashPos) //should be occurring before Path
				&& (firstQuestionPos != tstring::npos && firstColonPos < firstQuestionPos) //should be occurring before Query
				&& (firstHashPos != tstring::npos && firstColonPos < firstHashPos)) //should be occurring before fragment
			{
				tstring scheme = strUri.substr(0, firstColonPos);
				std::transform(scheme.begin(), scheme.end(), scheme.begin(), ::tolower);
				uriTokens.Scheme(scheme);
			}
			else {
				//if the first colon position is after double slash/slash/query/fragment then we do not have a scheme
				firstColonPos = tstring::npos;
			}
		}

		//Extract Path
		/*
		If a URI does not contain an authority component, then the path cannot
		begin with two slash characters ("//").  In addition, a URI reference
		(Section 4.1) may be a relative-path reference, in which case the first
		path segment cannot contain a colon (":") character.

		*/
		if (firstDoubleSlashPos == tstring::npos //no authority info
			&& firstSlashPos == tstring::npos // and no slash was found
			&& pRawStr[firstColonPos + 1] != TCHAR('\0') //String is not ending after :
			&& pRawStr[firstColonPos + 1] != TCHAR('?') //Query is not starting from next char
			&& pRawStr[firstColonPos + 1] != TCHAR('#')) //Fragment is not starting from next char
		{
			firstSlashPos = firstColonPos + 1;
		}
		/*
		The path is terminated by the first question mark ("?") or
		number sign ("#") character, or	by the end of the URI.
		If a URI contains an authority component, then the path component
		must either be empty or begin with a slash ("/") character.
		*/
		if (firstSlashPos != tstring::npos  //a slash has been found
			&& (firstHashPos != tstring::npos && firstSlashPos < firstHashPos) //should be occurring before fragment
			&& (firstQuestionPos != tstring::npos && firstSlashPos < firstQuestionPos)) //should be occurring before Query
		{
			if (firstQuestionPos != tstring::npos) {
				uriTokens.Path(strUri.substr(firstSlashPos, firstQuestionPos - firstSlashPos));
			}
			else if (firstHashPos != tstring::npos) {
				uriTokens.Path(strUri.substr(firstSlashPos, firstHashPos - firstSlashPos));
			}
			else {
				uriTokens.Path(strUri.substr(firstSlashPos));
			}
		}

		//Extract Authority
		/*
		The authority component is preceded by a double slash ("//") and is
		terminated by the next slash ("/"), question mark ("?"), or number
		sign ("#") character, or by the end of the URI.
		*/
		size_t authorityStartPos = firstDoubleSlashPos + 2;
		if (firstDoubleSlashPos != tstring::npos  //a double slash has been found
			&& TCHAR('\0') != pRawStr[authorityStartPos] //ensure that there is some content after the double slash
			&& (firstSlashPos != tstring::npos && authorityStartPos < firstSlashPos) //should be occurring before Path
			&& (firstQuestionPos != tstring::npos && authorityStartPos < firstQuestionPos) //should be occurring before Query
			&& (firstHashPos != tstring::npos && authorityStartPos < firstHashPos)) //should be occurring before fragment
		{
			tstring strAuthority;
			if (firstSlashPos != tstring::npos) {
				strAuthority = strUri.substr(authorityStartPos, firstSlashPos - authorityStartPos);
			}
			else if (firstQuestionPos != tstring::npos) {
				strAuthority = strUri.substr(authorityStartPos, firstQuestionPos - firstDoubleSlashPos);
			}
			else if (firstHashPos != tstring::npos) {
				strAuthority = strUri.substr(authorityStartPos, firstHashPos - authorityStartPos);
			}
			else {
				strAuthority = strUri.substr(authorityStartPos);
			}
			uriTokens.Authority(strAuthority);
		}
		return uriTokens;
	}

#if 0
	const tstring STR_REGEX_SCHEME("[a-zA-Z][a-zA-Z0-9+.-]*");

	//Scheme names consist of a sequence of characters beginning with a
	//	letter and followed by any combination of letters, digits, plus
	//	("+"), period("."), or hyphen("-").
	inline bool IsValidSchemeName(const tstring & strUri, const size_t & startAtPos, const size_t & endPos) {
		if (startAtPos == endPos) {
			//treat empty as valid
			return true;
		}
		return RegExMatch(strUri.substr(startAtPos, endPos), STR_REGEX_SCHEME);
	}


	ParsedTokenInfo URIParser::ParseScheme(const tstring & strUri, const size_t & startAtPos, const size_t & endPos) {
		ParsedTokenInfo tokenInfo;
		//skip whitepspace and set actuall beginning pos
		tokenInfo.StartPos = strUri.find_first_not_of(" \t\r\n\f\v", startAtPos);

		size_t colonPos = strUri.find_first_of(":", tokenInfo.StartPos);
		size_t slashPos = strUri.find_first_of("/", tokenInfo.StartPos);
		if (tokenInfo.StartPos == colonPos || slashPos < colonPos) {
			tokenInfo.StartPos = tstring::npos;
		}
		else {
			tokenInfo.EndPos = colonPos - 1;
		}
		tokenInfo.Valid = IsValidSchemeName(strUri, tokenInfo.StartPos, tokenInfo.EndPos);
		return tokenInfo;
	}

	ParsedTokenInfo URIParser::ParseAuthority(const tstring & strUri, const size_t & startAtPos, const size_t & endPos) {
	}

	ParsedTokenInfo URIParser::ParsePath(const tstring & strUri, const size_t & startAtPos, const size_t & endPos) {
	}

	ParsedTokenInfo URIParser::ParseQuery(const tstring & strUri, const size_t & startAtPos, const size_t & endPos) {
		ParsedTokenInfo tokenInfo;
		size_t questionPos = strUri.find_first_of("?", tokenInfo.StartPos);
		if (questionPos != tstring::npos) {
			size_t hashPos = strUri.find_first_of("#", tokenInfo.StartPos);
			if (hashPos < questionPos) {
				tokenInfo.StartPos = tstring::npos;
			}
			else {
				tokenInfo.EndPos = hashPos - 1;
			}
			tokenInfo.Valid = IsValidSchemeName(strUri, tokenInfo.StartPos, tokenInfo.EndPos);
		}
		return tokenInfo;
	}

	ParsedTokenInfo URIParser::ParseFragment(const tstring & strUri, const size_t & startAtPos, const size_t & endPos) {
	}
#endif
}