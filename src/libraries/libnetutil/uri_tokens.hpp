#ifndef __URI_TOKENS__HPP__
#define __URI_TOKENS__HPP__

#include <tstring.hpp>

class UriTokens {
public:
	UriTokens() {}
	virtual ~UriTokens() {}
	
	UriTokens(const UriTokens & objUriToken) {
		*this = objUriToken;
	}

	UriTokens& operator=(const UriTokens & objUriToken) {
		if (this != &objUriToken) {
			mScheme = objUriToken.mScheme;
			mAuthority = objUriToken.mAuthority;
			mPath = objUriToken.mPath;
			mQuery = objUriToken.mQuery;
			mFragment = objUriToken.mFragment;
		}
		return *this;
	}

	bool operator==(const UriTokens & objUriToken) {
		return (this == &objUriToken ||
			(mScheme == objUriToken.mScheme &&
			mAuthority == objUriToken.mAuthority &&
			mPath == objUriToken.mPath &&
			mQuery == objUriToken.mQuery &&
			mFragment == objUriToken.mFragment));
	}

	typedef struct Authority {
		//constructor/destructor
		Authority() {}
		virtual ~Authority() {}

		//overloaded constructor
		Authority(const tstring & strAuthority) {
			Init(strAuthority);
		}
		
		//overloaded constructor
		Authority(const Authority & auth) {
			*this = auth;
		}

		//overloaded assignement operator
		Authority& operator=(const Authority & auth) {
			if (this != &auth) {
				HostInfo = auth.HostInfo;
				UserInfo = auth.UserInfo;
			}
			return *this;
		}

		//overloaded comparison operator
		bool operator==(const Authority & auth) {
			if (this != &auth) {
				return (HostInfo == auth.HostInfo &&
					UserInfo == auth.UserInfo);
			}
			return true;
		}

		void Init(const tstring & strAuthority) {
			if (!strAuthority.empty()) {
				size_t pos = strAuthority.rfind(TCHAR('@'));
				if (tstring::npos == pos) {
					HostInfo.Init(strAuthority);
				}
				else {
					HostInfo.Init(strAuthority.substr(pos + 1));
					UserInfo.Init(strAuthority.substr(0, pos));
				}
			}
		}

		typedef class UserInfo {
		public:
			UserInfo() {
			}
			
			UserInfo(const tstring & strUserInfo) {
				Init(strUserInfo);
			}
			
			virtual ~UserInfo() {}

			//expects format name:passwd -  no check for correcteness
			void Init(const tstring & strUserInfo) {
				if (!strUserInfo.empty()) {
					size_t pos = strUserInfo.find(TCHAR(':'));
					if (tstring::npos == pos) {
						mUserName = strUserInfo;
					}
					else {
						mUserName = strUserInfo.substr(0, pos);
						mPassword = strUserInfo.substr(pos + 1);
					}
				}
			}
			
			//copy constructor
			UserInfo(const UserInfo & usrInfo) {
				*this = usrInfo;
			}

			//assignment operator
			UserInfo& operator=(const UserInfo & usrInfo) {
				if (this != &usrInfo) {
					mUserName = usrInfo.mUserName;
					mPassword = usrInfo.mPassword;
				}
				return *this;			
			}

			//comparison operator
			bool operator==(const UserInfo & usrInfo) {
				return (this == &usrInfo ||
					(mUserName == usrInfo.mUserName && mPassword == usrInfo.mPassword));
			}

			tstring UserName() const {
				return mUserName;
			}

			tstring Password() const {
				return mPassword;
			}
		private:
			tstring mUserName;
			tstring mPassword;
		} UserInfo_t;

		typedef class HostInfo {
		public:
			HostInfo() {}
			virtual ~HostInfo() {}

			HostInfo(const tstring & strHostInfo) {
				Init(strHostInfo);
			}

			void Init(const tstring & strHostInfo) {
				if (!strHostInfo.empty()) {
					size_t pos = strHostInfo.find(TCHAR(':'));
					if (tstring::npos == pos) {
						mHost = strHostInfo;
					} else {
						mHost = strHostInfo.substr(0, pos);
						mPort = strHostInfo.substr(pos + 1);
					}
				}
			}

			HostInfo(const HostInfo & hostInfo) {
				*this = hostInfo;
			}

			HostInfo& operator=(const HostInfo & hostInfo) {
				if (this != &hostInfo) {
					mHost = hostInfo.mHost;
					mPort = hostInfo.mPort;
				}
				return *this;
			}

			bool operator==(const HostInfo & hostInfo) {
				if (this != &hostInfo) {
					return (mHost == hostInfo.mHost && mPort == hostInfo.mPort);
				}
				return true;
			}

			tstring Host() const { return mHost; }
			tstring Port() const { return mPort; }

		private:
			tstring mHost;
			tstring mPort;
		} HostInfo_t;


		//could be refined for making meaningful
		bool IsEmpty() const {
			return (HostInfo.Host().empty() && HostInfo.Port().empty() &&
				UserInfo.UserName().empty() && UserInfo.Password().empty());
		}

		UserInfo_t UserInfo;
		HostInfo_t HostInfo;

	} Authority_t;

	//getter setters
	const tstring& Scheme() const {
		return mScheme;
	}

	void Scheme(const tstring & strScheme) {
		mScheme = strScheme;
	}

	const Authority & Authority() const {
		return mAuthority;
	}

	void Authority(const tstring & strAuthority) {
		mAuthority.Init(strAuthority);
	}

	const tstring& Path() const {
		return mPath;
	}

	void Path(const tstring & strPath) {
		mPath = strPath;
	}

	const tstring& Query() const {
		return mQuery;
	}

	void Query(const tstring & strQuery) {
		mQuery = strQuery;
	}

	const tstring& Fragment() const {
		return mFragment;
	}
	void Fragment(const tstring & strFragment) {
		mFragment = strFragment;
	}

	private:
		tstring mScheme;
		Authority_t mAuthority;
		tstring mPath;
		tstring mQuery;
		tstring mFragment;
};

#endif