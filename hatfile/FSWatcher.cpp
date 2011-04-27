/*
 *  FSWatcher.cpp
 *  hatlocal
 *
 *  Created by Maoxu Li on 4/12/11.
 *  Copyright 2011 GWU. All rights reserved.
 *
 */

#include "FSWatcher.h"

FSWatcher _fswatcher;

FSWatcher::FSWatcher() {
}

FSWatcher::~FSWatcher() {
}

/*
 int
 main(int argc, const char * argv[])
 {
 char       fullpath[PATH_MAX];
 settings_t _settings, *settings = &_settings;
 
 parse_settings(argc, argv, settings);
 
 if (settings->fullpath == NULL) {
 // no path given to monitor!
 usage(argv[0]);
 }
 
 if (realpath(settings->fullpath, fullpath) == NULL) {
 if (settings->fullpath[0] != '/') {
 int len;
 
 getcwd(fullpath, sizeof(fullpath));
 len = strlen(fullpath);
 fullpath[len] = '/';
 strlcpy(&fullpath[len+1], settings->fullpath, sizeof(fullpath) - (len+1));
 } else {
 strlcpy(fullpath, settings->fullpath, sizeof(fullpath));
 }
 }
 
 settings->fullpath = fullpath;
 
 watch_dir_hierarchy(settings);
 
 return 0;
 }
 */

bool FSWatcher::start() {
	settings_t _settings, *settings = &_settings;
	watch_dir_hierarchy(settings);
	return true;
}

void FSWatcher::stop() {
	
}
