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
#include "videoOutputPortConfig.hpp"
#include "audioOutputPortConfig.hpp"
#include "illegalArgumentException.hpp"
#include "dsVideoPortSettings.h"
//#include "dsVideoResolutionSettings.h"
#include "dsUtl.h"
#include "dsError.h"
#include "illegalArgumentException.hpp"
#include "list.hpp"
#include "videoResolution.hpp"

#include <iostream>
#include <string.h>

using namespace std;
static dsVideoPortResolution_t kResolutions[4];
static dsVideoPortTypeConfig_t kConfigs[2];
static dsVideoPortPortConfig_t kPorts[2];

namespace device {


VideoOutputPortConfig::VideoOutputPortConfig() {
	// TODO Auto-generated constructor stub
}

VideoOutputPortConfig::~VideoOutputPortConfig() {
	// TODO Auto-generated destructor stub
}

VideoOutputPortConfig & VideoOutputPortConfig::getInstance() {
    static VideoOutputPortConfig _singleton;
	return _singleton;
}

const PixelResolution &VideoOutputPortConfig::getPixelResolution(int id) const
{
	return _vPixelResolutions.at(id);
}

const AspectRatio &VideoOutputPortConfig::getAspectRatio(int id) const
{
	return _vAspectRatios.at(id);
}

const StereoScopicMode &VideoOutputPortConfig::getSSMode(int id) const
{
	return _vStereoScopieModes.at(id);
}

const VideoResolution &VideoOutputPortConfig::getVideoResolution (int id) const
{
	return _supportedResolutions.at(id);
}

const FrameRate &VideoOutputPortConfig::getFrameRate(int id) const
{
	return _vFrameRates.at(id);
}

VideoOutputPortType &VideoOutputPortConfig::getPortType(int id)
{
	return _vPortTypes.at(id);
}

VideoOutputPort &VideoOutputPortConfig::getPort(int id)
{
	return _vPorts.at(id);
}

VideoOutputPort &VideoOutputPortConfig::getPort(const std::string & name)
{
	for (size_t i = 0; i < _vPorts.size(); i++) {
		if (name.compare(_vPorts.at(i).getName()) == 0) {
			return _vPorts.at(i);
		}
	}

	throw IllegalArgumentException();
}

List<VideoOutputPort> VideoOutputPortConfig::getPorts()
{
	List <VideoOutputPort> rPorts;

	for (size_t i = 0; i < _vPorts.size(); i++) {
		rPorts.push_back(_vPorts.at(i));
	}

	return rPorts;
}

List<VideoOutputPortType>  VideoOutputPortConfig::getSupportedTypes()
{
	List<VideoOutputPortType> supportedTypes;
	for (std::vector<VideoOutputPortType>::const_iterator it = _vPortTypes.begin(); it != _vPortTypes.end(); it++) {
		if (it->isEnabled()) {
			supportedTypes.push_back(*it);
		}
	}

	return supportedTypes;
}

List<VideoResolution>  VideoOutputPortConfig::getSupportedResolutions()
{
	List<VideoResolution> supportedResolutions;

	for (std::vector<VideoResolution>::iterator it = _supportedResolutions.begin(); it != _supportedResolutions.end(); it++) {
		if (it->isEnabled()) {
			supportedResolutions.push_back(*it);
		}
	}

	return supportedResolutions;
}



void VideoOutputPortConfig::load()
{
	try {
		/*
		 * Load Constants First.
		 */
		for (size_t i = 0; i < dsVIDEO_PIXELRES_MAX; i++) {
			_vPixelResolutions.push_back(PixelResolution(i));
		}
		for (size_t i = 0; i < dsVIDEO_ASPECT_RATIO_MAX; i++) {
			_vAspectRatios.push_back(AspectRatio(i));
		}
		for (size_t i = 0; i < dsVIDEO_SSMODE_MAX; i++) {
			_vStereoScopieModes.push_back(StereoScopicMode(i));
		}
		for (size_t i = 0; i < dsVIDEO_FRAMERATE_MAX; i++) {
			_vFrameRates.push_back(FrameRate((int)i));
		}

		for (size_t i = 0; i < dsVIDEOPORT_TYPE_MAX; i++) {
			_vPortTypes.push_back(VideoOutputPortType((int)i));
		}

		/* Initialize a set of supported resolutions
		 *
		 */

		/**************** Resolution Setting -LnT Infotech ***************/

            kResolutions[0].name = (char*)malloc(strlen("720") + 1);
            strcpy((char*)kResolutions[0].name,"720");

            kResolutions[1].name = (char*)malloc(strlen("480i") + 1);
            strcpy((char*)kResolutions[1].name,"480i");

            kResolutions[2].name = (char*)malloc(strlen("480p") + 1);
            strcpy((char*)kResolutions[2].name,"480p");

            kResolutions[3].name = (char*)malloc(strlen("1080p24") + 1);
            strcpy((char*)kResolutions[3].name,"1080p24");

		/**************** VideoPort Configuration -LnT Infotech ***************/

            size_t i = 0;

            for(;i<2;i++)
            {
                kPorts[i].defaultResolution = (char*)malloc(strlen("720") + 1);
                strcpy((char*)kPorts[i].defaultResolution,"720");
                kPorts[i].id.type = (dsVideoPortType_t)i;
                kPorts[i].id.index = i;
                kPorts[i].connectedAOP.type =dsAUDIOPORT_TYPE_ID_LR;
                kPorts[i].connectedAOP.index = 0;

                kConfigs[i].supportedResolutions = (dsVideoPortResolution_t*)malloc(sizeof(dsVideoPortResolution_t));
                kConfigs[i].supportedResolutions->name = (char*)malloc(strlen("720") + 1);
                strcpy((char*)kConfigs[i].supportedResolutions->name,"720");
                kConfigs[i].supportedResolutions->pixelResolution  =(dsVideoResolution_t)0;       /**< The resolution associated with the name */
                kConfigs[i].supportedResolutions->aspectRatio=(dsVideoAspectRatio_t)0;               /**< The aspect ratio associated with this resolution */
                kConfigs[i].supportedResolutions->stereoScopicMode=(dsVideoStereoScopicMode_t)0;     /**< The Stereo scopic mode associated */
                kConfigs[i].supportedResolutions->frameRate=(dsVideoFrameRate_t)1;
                kConfigs[i].supportedResolutions->interlaced=1;

                kConfigs[i].numSupportedResolutions =1;
                kConfigs[i].restrictedResollution =0;
                kConfigs[i].hdcpSupported =1;
                kConfigs[i].dtcpSupported =1;
                kConfigs[i].name =(char*)malloc(strlen("videoPortResolution_Rf") + 1);
                strcpy((char*)kConfigs[i].name,"videoPortResolution_Rf");

            }
		/**************** END OF THE CODE -LnT Infotech ***************/

		size_t numResolutions = dsUTL_DIM(kResolutions);
		for (size_t i = 0; i < numResolutions; i++) {
			dsVideoPortResolution_t *resolution = &kResolutions[i];
			_supportedResolutions.push_back(
									VideoResolution(
										i, /* id */
										std::string(resolution->name),
										resolution->pixelResolution,
										resolution->aspectRatio,
										resolution->stereoScopicMode,
										resolution->frameRate,
										resolution->interlaced));
		}


	/*
	 * Initialize Video portTypes (supported resolutions, DTCP/HDCP etc.)
	 * and its port instances (curr resolution)
	 */

		for (size_t i = 0; i < dsUTL_DIM(kConfigs); i++) {
			const dsVideoPortTypeConfig_t *typeCfg = &kConfigs[i];
			VideoOutputPortType &vPortType = VideoOutputPortType::getInstance(typeCfg->typeId);

			vPortType.enable();
			if (typeCfg->dtcpSupported) vPortType.enabledDTCP();
			if (typeCfg->hdcpSupported) vPortType.enabledHDCP();
			vPortType.setRestrictedResolution(typeCfg->restrictedResollution);
			for (size_t j = 0; j < typeCfg->numSupportedResolutions; j++) {
				vPortType.addResolution(VideoResolution::getInstance(std::string(typeCfg->supportedResolutions[j].name)));

			}
		}

		/*
		 * set up ports based on kPorts[]
		 */
        for (size_t i = 0; i < dsUTL_DIM(kPorts); i++) {
            AudioOutputPortType::getInstance(kPorts[i].connectedAOP.type).getPort(kPorts[i].connectedAOP.index).getId();
			const dsVideoPortPortConfig_t *port = &kPorts[i];

			_vPorts.push_back(
					VideoOutputPort((port->id.type), port->id.index, i,
							AudioOutputPortType::getInstance(kPorts[i].connectedAOP.type).getPort(kPorts[i].connectedAOP.index).getId(),
							std::string(port->defaultResolution)));

			_vPortTypes.at(port->id.type).addPort(_vPorts.at(i));

		}

	}
	catch (...) {
		cout << "Exception Thrown ...!\n";
	}

}

}
