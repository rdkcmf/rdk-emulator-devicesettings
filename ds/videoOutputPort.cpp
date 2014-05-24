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
 
#include "videoOutputPort.hpp"
#include "videoResolution.hpp"
#include "audioOutputPortType.hpp"
#include "videoOutputPortType.hpp"
#include "videoOutputPortConfig.hpp"
#include "audioOutputPortConfig.hpp"
#include "host.hpp"

#include "dsVideoPort.h"
#include "dsDisplay.h"

#include "illegalArgumentException.hpp"


#include <sstream>

namespace device {

const char * VideoOutputPort::kPropertyResolution = ".resolution";

VideoOutputPort & VideoOutputPort::getInstance(int id)
{
	return VideoOutputPortConfig::getInstance().getPort(id);
}

VideoOutputPort & VideoOutputPort::getInstance(const std::string &name)
{
	return VideoOutputPortConfig::getInstance().getPort(name);

}

VideoOutputPort::VideoOutputPort(const int type, const int index, const int id, int audioPortId, const std::string &resolution) :
										_type(type), _index(index), _id(id),
										_handle(-1), _enabled(true), _contentProtected(false),
										_displayConnected(false), _aPortId(audioPortId),
										_defaultResolution(resolution),
										_resolution(resolution),
										_display(*this)
{
	dsError_t ret = dsGetVideoPort((dsVideoPortType_t)_type, _index, &_handle);

	{
		std::stringstream out;
		out << getType().getName() << _index;
		_name = std::string(out.str());
	}

	if (ret == dsERR_NONE) {
        bool enabled = true;
        ret = dsIsVideoPortEnabled(_handle, &enabled);
		if (ret == dsERR_NONE) {
			_enabled = enabled;
			_contentProtected = false;

            bool connected = true;
            ret = dsIsDisplayConnected(_handle, &connected);
			if (ret == dsERR_NONE) {
				_displayConnected = connected;

				/* Get Resolution from Persistence and set it */
				_resolution = Host::getInstance().getPersistence().getProperty (_name + kPropertyResolution, _defaultResolution);
				setResolution(_resolution);
			}
			else {
				throw IllegalArgumentException();
			}
		}
		else {
		}
	}
	else {
		throw IllegalArgumentException();
	}

}

VideoOutputPort::~VideoOutputPort()
{
}

const VideoOutputPortType & VideoOutputPort::getType() const
{
	return VideoOutputPortConfig::getInstance().getPortType(_type);
}

AudioOutputPort &VideoOutputPort::getAudioOutputPort()
{
	return AudioOutputPortConfig::getInstance().getPort(_aPortId);
}

const VideoResolution & VideoOutputPort::getResolution() const
{
	return VideoResolution::getInstance(_resolution);
}

const VideoResolution & VideoOutputPort::getDfeaultResolution() const
{
	return VideoResolution::getInstance(_defaultResolution);
}

const VideoOutputPort::Display &VideoOutputPort::getDisplay()
{
	if (isDisplayConnected()) {
		dsVideoAspectRatio_t aspect;
		dsDisplayEDID_t edid;
		if (_display._handle != 0) {
			dsGetDisplayAspectRatio(_display._handle, &aspect);
			_display._aspectRatio = aspect;
			dsGetEDID(_display._handle, &edid);
			 _display._productCode = edid.productCode;
			 _display._serialNumber = edid.serialNumber;
			 _display._manufacturerYear = edid.manufactureYear;
			 _display._manufacturerWeek = edid.manufactureWeek;
			return _display;
		}
		else {
			throw Exception(dsERR_INVALID_PARAM);
		}
	}
	else {
		throw Exception(dsERR_INVALID_STATE);
	}
}

const bool VideoOutputPort::isDisplayConnected() const
{
    bool connected = false;
    dsError_t ret = dsIsDisplayConnected(_handle, &connected);
	if (ret != dsERR_NONE) {
		throw Exception(ret);
	}
    return connected;
}


const bool VideoOutputPort::isEnabled() const
{
	return _enabled;
}

const bool VideoOutputPort::isDynamicResolutionSupported() const
{
	return VideoOutputPortType::getInstance(_type).isDynamicResolutionsSupported();
}

void VideoOutputPort::setResolution(const std::string &resolutionName)
{

	if (0 && resolutionName.compare(_resolution) == 0) {
		return;
	}

	VideoResolution newResolution = VideoResolution::getInstance(resolutionName);

	dsVideoPortResolution_t resolution;
	resolution.aspectRatio 		= (dsVideoAspectRatio_t)		newResolution.getAspectRatio().getId();
	resolution.frameRate 		= (dsVideoFrameRate_t) 	 	newResolution.getFrameRate().getId();
	resolution.interlaced 		= (bool)					newResolution.isInterlaced();
	resolution.pixelResolution 	= (dsVideoResolution_t)	newResolution.getPixelResolution().getId();
	resolution.stereoScopicMode = (dsVideoStereoScopicMode_t)newResolution.getStereoscopicMode().getId();

	dsError_t ret = dsSetResolution(_handle, &resolution);

	if (ret != dsERR_NONE) {
		throw Exception(ret);
	}
	/* TODO persist settings */
	_resolution = newResolution.getName();

    Host::getInstance().getPersistence().persistHostProperty(_name + kPropertyResolution, newResolution.getName());

}

void VideoOutputPort::setDisplayConnected(const bool connected)
{
	_displayConnected = connected;
}

void VideoOutputPort::enable()
{
	if (dsEnableVideoPort(_handle, true) == dsERR_NONE)
	{
		_enabled = true;
	}
}

void VideoOutputPort::disable()
{
	if (dsEnableVideoPort(_handle, false) == dsERR_NONE)
	{
		_enabled = false;
	}
}

VideoOutputPort::Display::Display(VideoOutputPort &vPort)
{
	dsError_t ret = dsERR_NONE;
	ret = dsGetDisplay((dsVideoPortType_t)vPort.getType().getId(), vPort.getIndex(), &_handle);
	if (ret != dsERR_NONE) {
		throw Exception(ret);
	}
}

VideoOutputPort::Display::~Display()
{
}


}
