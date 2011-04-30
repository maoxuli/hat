#ifndef HAT_FILTER_ICE
#define HAT_FILTER_ICE

#include <Ice/BuiltinSequences.ice>

module hat
{
	interface Filter
	{
		Ice::StringSeq select(string where);
	};
}; 

#endif  //#ifndef HAT_FILTER_ICE
