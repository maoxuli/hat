#ifndef HAT_PROFILE_ICE
#define HAT_PROFILE_ICE

#include <Ice/BuiltinSequences.ice>

module hat
{
	interface Profile
	{
		void setHash(string name, string hash);
		string getHash(string name);
	};
}; 
#endif  //#ifndef HAT_PROFILE_ICE
