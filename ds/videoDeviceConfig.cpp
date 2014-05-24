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
 
#include "videoDeviceConfig.hpp"
#include "dsVideoDeviceSettings.h"
#include "videoDevice.hpp"
#include "videoDFC.hpp"
#include <iostream>
#include "dsUtl.h"

static dsVideoConfig_t kConfigs[8];

namespace device {

VideoDeviceConfig::VideoDeviceConfig() {
	// TODO Auto-generated constructor stub

}

VideoDeviceConfig::~VideoDeviceConfig() {
	// TODO Auto-generated destructor stub
}

VideoDeviceConfig & VideoDeviceConfig::getInstance() {
    static VideoDeviceConfig _singleton;
	return _singleton;
}

List<VideoDevice>  VideoDeviceConfig::getDevices()
{
	List<VideoDevice> devices;
	for (std::vector<VideoDevice>::const_iterator it = _vDevices.begin(); it != _vDevices.end(); it++) {
		devices.push_back(*it);
	}

	return devices;
}

VideoDevice &VideoDeviceConfig::getDevice(int i)
{
	return _vDevices.at(i);
}

List<VideoDFC>  VideoDeviceConfig::getDFCs()
{
	List<VideoDFC> DFCs;
	for (std::vector<VideoDFC>::iterator it = _vDFCs.begin(); it != _vDFCs.end(); it++) {
		DFCs.push_back(*it);
	}

	return DFCs;
}

VideoDFC & VideoDeviceConfig::getDFC(int id)
{
	return _vDFCs.at(id);
}

VideoDFC & VideoDeviceConfig::getDefaultDFC()
{
	return _vDFCs.back();
}

void VideoDeviceConfig::load()
{
	/*
	 * Load Constants First.
	 */
	for (size_t i = 0; i < dsVIDEO_ZOOM_MAX; i++) {
		_vDFCs.push_back(VideoDFC(i));
	}

	/*
	 * Initialize Video Devices (supported DFCs etc.)
	 */
	for (size_t i = 0; i < dsUTL_DIM(kConfigs); i++) {
		_vDevices.push_back(VideoDevice(i));

		for (size_t j = 0; j < kConfigs[i].numSupportedDFCs; j++) {
			_vDevices.at(i).addDFC(VideoDFC::getInstance(kConfigs[i].supportedDFCs[j]));
		}
	}
}


}
