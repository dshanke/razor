#ifndef __PARSER_HPP__
#define __PARSER_HPP__

#include <uri>

namespace razor {
	
	class parser {
	public:
		static uri make_uri(const tstring & strUri);
	};
}
#endif