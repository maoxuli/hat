#ifndef __FSWATCHER_H__
#define __FSWATCHER_H__

/*
 *  FSWatcher.h
 *  hatlocal
 *
 *  Created by Maoxu Li on 4/12/11.
 *  Copyright 2011 GWU. All rights reserved.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/param.h>
#include <sys/mount.h>
#include <sys/event.h>
#include <dirent.h>
#include <assert.h>
#include <CoreFoundation/CoreFoundation.h>
#include <CoreServices/CoreServices.h>
#include <pthread.h>

#include <string>

using namespace std;

typedef struct _settings_t {
    dev_t                dev;
    FSEventStreamEventId since_when;
    CFAbsoluteTime       latency;
    const char          *fullpath;
    CFUUIDRef            dev_uuid;
    char                 mount_point[MAXPATHLEN];
} settings_t;

void watch_dir_hierarchy(settings_t *settings);

typedef void fCallback(void*, const string&);

class FSWatcher {
public:
	FSWatcher();
	~FSWatcher();
	
public:
	bool start();	//Start monitor file system events
	void stop();	//Stop monitor file system events
	
	void pathChange(const string& path);
	
	void setCallback(void* context, fCallback* callback)
	{
		_context = context;
		_callback = callback;
	}
	
	void* _context;
	fCallback* _callback;
	
};

extern FSWatcher _fswatcher;

#endif //__FSWATCHER_H__