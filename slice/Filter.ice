#ifndef HAT_FILTER_ICE
#define HAT_FILTER_ICE

#include <Ice/BuiltinSequences.ice>

module hat
{
	struct FileInfo
	{
		int		id;
		string	uri;
		long	stamp;
		long	size;
		string	hash;
		float	score;
	};
	sequence<FileInfo> FileInfoSeq;
	
	interface Filter
	{
		FileInfoSeq select(string where);
		FileInfoSeq score(int id);
	};
}; 

#endif  //#ifndef HAT_FILTER_ICE
