#ifndef HAT_FILTER_ICE
#define HAT_FILTER_ICE

#include <Ice/BuiltinSequences.ice>

module hat
{
	interface Filter
	{
		string getFile();
	};
}; 
#endif  //#ifndef HAT_FILTER_ICE
