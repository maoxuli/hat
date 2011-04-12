/*
 *  LocalSynchronizer.h
 *  hatlocal
 *
 *  Created by Maoxu Li on 4/12/11.
 *  Copyright 2011 GWU. All rights reserved.
 *
 */

#include <string>
using namespace std;

class LocalSynchronizer {
	public:
	LocalSynchronizer();
	~LocalSynchronizer();

	public:
	bool synchronize(const string& dir);
};