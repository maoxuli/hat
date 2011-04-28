#ifndef HAT_SYNCHRONIZER_ICE
#define HAT_SYNCHRONIZER_ICE

#include <Ice/BuiltinSequences.ice>

module hat
{
	interface Synchronizer
	{
		void refresh(string path);
	};
}; 
#endif  //#ifndef HAT_SYNCHRONIZER_ICE
