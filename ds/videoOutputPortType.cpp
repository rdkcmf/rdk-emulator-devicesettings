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
 
#include "videoOutputPortType.hpp"
#include "videoOutputPort.hpp"
#include "list.hpp"
#include "dsUtl.h"
#include "illegalArgumentException.hpp"
#include "videoOutputPortConfig.hpp"

namespace {
	const char *_names[] = {
			"RF",
			"Baseband",
			"SVideo",
			"1394",
			"DVI",
			"Component",
			"HDMI",
			"HDMIInput",
			"Internal",
	};

	inline const bool isValid(int id) {
		return dsVideoPortType_isValid(id);
	}

}

namespace device {

//typedef int _SafetyCheck[(dsUTL_DIM(_names) == dsVIDEOPORT_TYPE_MAX) ? 1 : -1];

const int VideoOutputPortType::kRF 			= dsVIDEOPORT_TYPE_RF;
const int VideoOutputPortType::kBaseband 	= dsVIDEOPORT_TYPE_BB;
const int VideoOutputPortType::kSVideo 		= dsVIDEOPORT_TYPE_SVIDEO;
const int VideoOutputPortType::k1394 		= dsVIDEOPORT_TYPE_1394;
const int VideoOutputPortType::kDVI 		= dsVIDEOPORT_TYPE_DVI;
const int VideoOutputPortType::kComponent 	= dsVIDEOPORT_TYPE_COMPONENT;
const int VideoOutputPortType::kHDMI 		= dsVIDEOPORT_TYPE_HDMI;
const int VideoOutputPortType::kInternal 	= dsVIDEOPORT_TYPE_INTERNAL;
const int VideoOutputPortType::kMax 		= dsVIDEOPORT_TYPE_MAX;

VideoOutputPortType & VideoOutputPortType::getInstance(int id)
{
	if (::isValid(id)) {
		return VideoOutputPortConfig::getInstance().getPortType(id);
	}
	else {
		throw IllegalArgumentException();
	}
}

VideoOutputPortType::VideoOutputPortType(const int id)
 {
	if (::isValid(id)) {
		_id = id;
		_name = std::string(_names[id]);
	}
	else {
		throw IllegalArgumentException();
	}

}

VideoOutputPortType::~VideoOutputPortType()
{
}

const List<VideoOutputPort> VideoOutputPortType::getPorts() const
{
	return _vPorts;
}

void VideoOutputPortType::enabledDTCP()
{
	_dtcpSupported = true;
}

void VideoOutputPortType::enabledHDCP()
{
	_hdcpSupported = true;
}

void VideoOutputPortType::setRestrictedResolution(int resolution)
{
	_restrictedResolution = resolution;
}

void VideoOutputPortType::addResolution(const VideoResolution & resolution)
{
	_supportedResolutions.push_back(resolution);
}

void VideoOutputPortType::addPort(const VideoOutputPort & port)
{
	_vPorts.push_back(port);
}

const bool VideoOutputPortType::isDTCPSupported() const
{
	return _dtcpSupported;
}

const bool VideoOutputPortType::isHDTPSupported() const
{
	return _hdcpSupported;
}

const bool VideoOutputPortType::isDynamicResolutionsSupported() const
{
	return true;
}

const int VideoOutputPortType::getRestrictedResolution() const
{
	return _restrictedResolution;
}

const List<VideoResolution >  VideoOutputPortType::getSupportedResolutions() const
{
	return _supportedResolutions;
}

}
