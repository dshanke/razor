#ifndef __URI_CLASS__
#define __URI_CLASS__

#include <tstring.hpp>

namespace razor {

	class baduri_exception {
	};
	
	class IUri {
	public:
		virtual tstring Scheme() const = 0;
		virtual tstring User() const = 0;
		virtual tstring Password() const = 0;
		virtual tstring Host() const = 0;
		virtual tstring Port() const = 0;
		virtual tstring Path() const = 0;
		virtual tstring Query() const = 0;
		virtual tstring Fragment() const = 0;
		
		virtual bool IsHostAnIP() const = 0;
		virtual bool IsEmpty() const = 0;
		virtual bool IsValid() const = 0;
		
	};

	class parser {
	public:
		static IUri* make_uri(const tstring & strUri);
	};

}


#endif