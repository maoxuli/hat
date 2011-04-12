/*
 *  RemoteSynchronizer.h
 *  hatremote
 *
 *  Created by Maoxu Li on 4/12/11.
 *  Copyright 2011 GWU. All rights reserved.
 *
 */

#include <string>
using namespace std;

class RemoteSynchronizer {
	public:
	RemoteSynchronizer();
	~RemoteSynchronizer();
	
	public:
	bool synchronize(const string& url);
};
