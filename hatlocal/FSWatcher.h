/*
 *  FSWatcher.h
 *  hatlocal
 *
 *  Created by Maoxu Li on 4/12/11.
 *  Copyright 2011 GWU. All rights reserved.
 *
 */

class FSWatcher {
public:
	FSWatcher();
	~FSWatcher();
	
public:
	bool start();	//Start monitor file system events
	void stop();	//Stop monitor file system events
	
};