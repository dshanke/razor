#ifndef __URI_IMPL__HPP__
#define __URI_IMPL__HPP__

#include "include/uri.hpp"
#include "uri_parser.hpp"

namespace razor {

	class UriImpl : public IUri {
	public:
		UriImpl(const tstring & strUri);
		virtual ~UriImpl() {};

		UriImpl(const UriImpl & objUri);
		UriImpl& operator= (const UriImpl & objUri);

		bool operator==(const UriImpl & objUri);
		bool operator==(const tstring & strUri);

		tstring Scheme() const;
		tstring User() const;
		tstring Password() const;
		tstring Host() const;
		tstring Port() const;
		tstring Path() const;
		tstring Query() const;
		tstring Fragment() const;

		bool IsHostAnIP() const;
		bool IsWellFormed() const;
		bool IsEmpty() const;

	private:
		UriTokens mUriTokens;
		tstring mOrigUri;
	};
}





#endif