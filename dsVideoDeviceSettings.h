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
 
#ifndef _DS_VIDEODEVICESETTINGS_H_
#define _DS_VIDEODEVICESETTINGS_H_

#include "dsUtl.h"
#include "dsTypes.h"


#ifdef __cplusplus
extern "C" {
#endif

namespace  {
static const dsVideoZoom_t kSupportedDFCs[] = { dsVIDEO_ZOOM_NONE, dsVIDEO_ZOOM_FULL, dsVIDEO_ZOOM_PLATFORM};
static const dsVideoZoom_t kDefaultDFC 	   = dsVIDEO_ZOOM_FULL;

static const int kNumVideoDevices = 1;


static const dsVideoConfig_t kConfigs[]= {
		{
		/*.numSupportedDFCs = */ 		dsUTL_DIM(kSupportedDFCs), // 0 means "Info available at runtime"
		/*.supportedDFCs = */			kSupportedDFCs,
		/*.defaultDFC = */			    dsVIDEO_ZOOM_FULL,
		},
};

typedef int _SafetyCheck[(dsUTL_DIM(kConfigs) == kNumVideoDevices) ? 1 : -1];

}
#ifdef __cplusplus
}
#endif

#endif /* RPVIDEODEVICESETTINGS_H_ */
