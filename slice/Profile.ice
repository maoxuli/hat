#ifndef HAT_PROFILE_ICE
#define HAT_PROFILE_ICE

#include <Ice/BuiltinSequences.ice>

module hat
{
	struct FileStat
	{
		int		fid;
		string	host;
		string	path;
		string	name;
		long	stamp;
		int		size;
		string	hash;
	};
		
	struct FileMeta
	{
		int		fid;
		int		width;
		int		height;
		long	origin;
	};
		
	struct FileFeature
	{
		int		fid;
	};
		
	interface Profile
	{
		int updateFile(FileStat stat);
		void updateMeta(FileMeta meta);
		void updateFeature(FileFeature feature);
	};
}; 
#endif  //#ifndef HAT_PROFILE_ICE
