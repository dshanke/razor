#include "uri_impl.hpp"

namespace razor {

	IUri* IUri::make_uri(const tstring & strUri) {
		return new UriImpl(strUri);
	}

	UriImpl::UriImpl(const UriImpl & objUri) {
		*this = objUri;
	}

	UriImpl& UriImpl::operator=(const UriImpl & objUri) {
		if (this != &objUri) {
			mUriTokens = objUri.mUriTokens;
		}
		return *this;
	}

	bool UriImpl::operator==(const UriImpl & objUri) {

		return (mUriTokens == objUri.mUriTokens);

	}

	bool UriImpl::operator==(const tstring & strUri) {
		try {
			if (mOrigUri == strUri) return true;
			UriImpl objUri(strUri);
			return objUri == *this;
		}
		catch (...) {
			//ignoring for now
		}
		return false;
	}

	UriImpl::UriImpl(const tstring & strUri)
		:mOrigUri(sutil::StringTrim(strUri))
	{
		mUriTokens = URIParser::Parse(mOrigUri);
	}

	tstring UriImpl::Scheme() const { return mUriTokens.Scheme(); };
	tstring UriImpl::User() const { return mUriTokens.Authority().UserInfo.UserName(); };
	tstring UriImpl::Password() const { return mUriTokens.Authority().UserInfo.Password(); };
	tstring UriImpl::Host() const { return mUriTokens.Authority().HostInfo.Host(); };
	tstring UriImpl::Port() const { return mUriTokens.Authority().HostInfo.Port(); }
	tstring UriImpl::Path() const { return mUriTokens.Path(); };
	tstring UriImpl::Query() const { return mUriTokens.Query(); };
	tstring UriImpl::Fragment() const { return mUriTokens.Fragment(); };

	//A rule engine could be implemented to evaluate rules.. currently brute forcing
	bool UriImpl::IsWellFormed() const { 
		const tstring STR_REGEX_SCHEME("[a-zA-Z][a-zA-Z0-9+.-]*");
		if (Scheme().empty() || (!Scheme().empty() && !sutil::RegExMatch(Scheme(), STR_REGEX_SCHEME)))
			return false;

		if (!mUriTokens.Authority().IsEmpty() && !mUriTokens.Path().empty() && mUriTokens.Path()[0] != TCHAR('/'))
			return false;

		return true;
	};
	
	//Not iplemented  since this involves decoding and then matching against regex
	bool UriImpl::IsHostAnIP() const { return false; };
	bool UriImpl::IsEmpty() const { return mOrigUri.empty(); };

}