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

#include "dsTypes.h"
#include "dsError.h"
#include "dsHost.h"

dsError_t dsHostInit()
{
    dsError_t ret = dsERR_NONE;

    return ret;
}

dsError_t dsSetHostPowerMode(int newPower)
{
    dsError_t ret = dsERR_NONE;

    /* TODO: Standby Mode to be finished */
    return ret;
}

dsError_t dsGetHostPowerMode(int *currPower)
{
    dsError_t ret = dsERR_NONE;
    return ret;
}

dsError_t dsGetPreferredSleepMode(dsSleepMode_t *pMode)
{
    dsError_t ret = dsERR_NONE;

    return ret;
}

dsError_t dsSetPreferredSleepMode(dsSleepMode_t mode)
{
    dsError_t ret = dsERR_NONE;

    return ret;
}

dsError_t dsGetCPUTemperature(float *cpuTemperature)
{
    dsError_t ret = dsERR_NONE;

    return ret;
}

dsError_t dsGetVersion(uint32_t *versionNumber)
{
    dsError_t ret = dsERR_NONE;

    return ret;
}

dsError_t dsSetVersion(uint32_t versionNumber)
{
    dsError_t ret = dsERR_NONE;

    return ret;
}

dsError_t dsHostTerm()
{
    dsError_t ret = dsERR_NONE;

    return ret;
}
