/*
 *  hatcore.cp
 *  hatcore
 *
 *  Created by Maoxu Li on 4/9/11.
 *  Copyright 2011 GWU. All rights reserved.
 *
 */

#include <iostream>
#include "hatcore.h"
#include "hatcorePriv.h"

void hatcore::HelloWorld(const char * s)
{
	 hatcorePriv *theObj = new hatcorePriv;
	 theObj->HelloWorldPriv(s);
	 delete theObj;
};

void hatcorePriv::HelloWorldPriv(const char * s) 
{
	std::cout << s << std::endl;
};

