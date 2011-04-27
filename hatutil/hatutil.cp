/*
 *  hatutil.cp
 *  hatutil
 *
 *  Created by Maoxu Li on 4/27/11.
 *  Copyright 2011 GWU. All rights reserved.
 *
 */

#include <iostream>
#include "hatutil.h"
#include "hatutilPriv.h"

void hatutil::HelloWorld(const char * s)
{
	 hatutilPriv *theObj = new hatutilPriv;
	 theObj->HelloWorldPriv(s);
	 delete theObj;
};

void hatutilPriv::HelloWorldPriv(const char * s) 
{
	std::cout << s << std::endl;
};

