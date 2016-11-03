#ifndef __URI_IMPL__HPP__
#define __URI_IMPL__HPP__

#include "include/uri.hpp"

namespace razor {

	class UriImpl : public IUri {
	public:
		tstring Scheme() const;
		tstring User() const;
		tstring Password() const;
		tstring Host() const;
		tstring Port() const;
		tstring Path() const;
		tstring Query() const;
		tstring Fragment() const;

		bool IsHostAnIP() const;
		bool IsValid() const;
		bool IsEmpty() const;

	};
}

#endif