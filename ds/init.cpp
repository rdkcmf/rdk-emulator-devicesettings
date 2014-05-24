/* 
 * ============================================================================
 * COMCAST C O N F I D E N T I A L AND PROPRIETARY
 * ============================================================================
 * This file and its contents are the intellectual property of Comcast.  It may 
 * not be used, copied, distributed or otherwise disclosed in * whole or in part 
 * without the express written permission of Comcast.
 * ============================================================================
 * Copyright (c) 2011 – 2012 Comcast. All rights reserved.
 * ============================================================================
 */
 
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

//#include "libIBus.h"

static char cliName[32];


#if 0

__attribute__((constructor)) void __init(void)
{
	snprintf(cliName, sizeof(cliName), "DSCli_%d", getpid());
	
	//	IARM_Bus_Init(cliName);
	//	IARM_Bus_Connect();
	
    printf("Library initialized for client %s\r\n", cliName);
}

__attribute__((destructor)) void __term(void)
{
	//IARM_Bus_Disconnect();
	//	IARM_Bus_Term();
    
	printf("Library destructed	for client %s\r\n", cliName);
}

#endif
