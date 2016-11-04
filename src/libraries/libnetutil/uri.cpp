#include "uri_impl.hpp"

namespace razor {

	IUri* IUri::make_uri(const tstring & strUri) {
		return new UriImpl(strUri);
	}


	UriImpl::UriImpl(const tstring & strUri) {
			mUriTokens = URIParser::Parse(strUri);
	}

	tstring UriImpl::Scheme() const { return mUriTokens.Scheme; };
	tstring UriImpl::User() const { return mUriTokens.Authority.UserInfo.UserName; };
	tstring UriImpl::Password() const { return mUriTokens.Authority.UserInfo.Password; };
	tstring UriImpl::Host() const { return mUriTokens.Authority.HostInfo.Host; };
	tstring UriImpl::Port() const { return mUriTokens.Authority.HostInfo.Port; }
	tstring UriImpl::Path() const { return mUriTokens.Path; };
	tstring UriImpl::Query() const { return mUriTokens.Query; };
	tstring UriImpl::Fragment() const { return mUriTokens.Fragment; };

	bool UriImpl::IsWellFormed() const { 
		return false; 
	};
	bool UriImpl::IsHostAnIP() const { return false; };
	bool UriImpl::IsEmpty() const { return false; };

}