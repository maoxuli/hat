#ifndef HAT_PROFILE_ICE
#define HAT_PROFILE_ICE

#include <Ice/BuiltinSequences.ice>

module hat
{	
	struct FileStat
	{
		int		id;
		string	uri; //host/path/name
		string	pathname; //local file system
		long	stamp; //time_t
		long	size;
	};
	sequence<FileStat> FileStatSeq;
		
	struct ImageMeta
	{
		int		id;
		int		width;
		int		height;
		long	origin; //time_t
	};
		
	struct ImageFeature
	{
		int		id;
	};
		
	interface Profile
	{
		FileStatSeq refreshPath(string path, FileStatSeq fss);
		
		bool updateFile(FileStat stat, string hash);
		bool updateMeta(ImageMeta meta);
		bool updateFeature(ImageFeature feature);
	};
}; 
#endif  //#ifndef HAT_PROFILE_ICE
