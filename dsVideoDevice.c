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

#include <stdlib.h>
#include <stdio.h>
#include "dsTypes.h"
#include "dsVideoDevice.h"

dsError_t  dsVideoDeviceInit()
{
	dsError_t ret = dsERR_NONE;
	return ret;
}

dsError_t  dsGetVideoDevice(int index, int *handle)
{
	dsError_t ret = dsERR_NONE;

	*handle = 0;
	return ret;
}

dsError_t  dsSetDFC(int handle, dsVideoZoom_t dfc)
{
	dsError_t ret = dsERR_NONE;

	return ret;
}

dsError_t  dsVideoDeviceTerm()
{
	dsError_t ret = dsERR_NONE;
	return ret;
}
