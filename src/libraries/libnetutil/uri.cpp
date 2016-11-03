#include "uri_impl.h"

namespace razor {

	IUri* parser::make_uri(const tstring & strUri) {
		return new UriImpl();
	}

	tstring UriImpl::Scheme() const { return ""; };
	tstring UriImpl::User() const { return ""; };
	tstring UriImpl::Password() const { return ""; };
	tstring UriImpl::Host() const { return ""; };
	tstring UriImpl::Port() const { return ""; };
	tstring UriImpl::Path() const { return ""; };
	tstring UriImpl::Query() const { return ""; };
	tstring UriImpl::Fragment() const { return ""; };

	bool UriImpl::IsValid() const { return false; };
	bool UriImpl::IsHostAnIP() const { return false; };
	bool UriImpl::IsEmpty() const { return false; };

}