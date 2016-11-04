#ifndef __URI_PARSER__HPP__
#define __URI_PARSER__HPP__

#include "tstring.hpp"

namespace razor {

	struct UriTokens {
		typedef struct Authority {
			typedef struct UserInfo {
				tstring UserName;
				tstring Password;
				bool IsEmpty() {
					return (UserName.empty());
				}
			} UserInfo_t;
			typedef struct HostInfo {
				tstring Host;
				tstring Port;
				bool IsEmpty() {
					return (Host.empty());
				}
			} HostInfo_t;

			void SetAuthorityInfo(const tstring & strAuthority) {
				size_t pos = strAuthority.rfind(TCHAR('@'));
				tstring hostPort = strAuthority;
				tstring userpwd;
				if (tstring::npos != pos) {
					hostPort = strAuthority.substr(pos + 1);
					if (0 != pos) {
						userpwd = strAuthority.substr(0, pos);
					}
				}
				pos = hostPort.find(TCHAR(':'));
				if (tstring::npos != pos) {
					HostInfo.Port = hostPort.substr(pos + 1);
					hostPort = hostPort.substr(0, pos);
				}
				HostInfo.Host = hostPort;

				if (!userpwd.empty()) {
					UserInfo.UserName = userpwd;
					pos = userpwd.find(TCHAR(':'));
					if (tstring::npos != pos) {
						UserInfo.UserName = userpwd.substr(0, pos);
						UserInfo.Password = userpwd.substr(pos + 1);
					}
				}
			}

			bool IsEmpty() {
				return (HostInfo.IsEmpty() && UserInfo.IsEmpty());
			}

			bool IsValid() {
				return false;
			}
			UserInfo_t UserInfo;
			HostInfo_t HostInfo;
		} Authority_t;

		tstring Scheme;
		Authority_t Authority;
		tstring Path;
		tstring Query;
		tstring Fragment;
	};
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