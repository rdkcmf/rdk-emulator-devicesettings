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
 
#ifndef VIDEOOUTPUTPORTCONFIG_HPP_
#define VIDEOOUTPUTPORTCONFIG_HPP_

#include "videoOutputPortType.hpp"
#include "videoResolution.hpp"




#include <vector>
#include <string>

namespace device {

class  VideoOutputPortConfig {

	

    std::vector<PixelResolution>	 	_vPixelResolutions;
    std::vector<AspectRatio> 			_vAspectRatios;
    std::vector<StereoScopicMode> 		_vStereoScopieModes;
    std::vector<VideoResolution> 		_supportedResolutions;
    std::vector<FrameRate> 				_vFrameRates;
    std::vector<VideoOutputPortType>	_vPortTypes;
    std::vector<VideoOutputPort>        _vPorts;


	VideoOutputPortConfig();
	~VideoOutputPortConfig();

public:
	static VideoOutputPortConfig & getInstance();

	const PixelResolution 	&getPixelResolution(int id) const;
	const AspectRatio 		&getAspectRatio(int id) const;
	const StereoScopicMode 	&getSSMode(int id) const;
	const VideoResolution   &getVideoResolution (int id) const;
	const FrameRate 		&getFrameRate(int id) const;
	VideoOutputPortType 	&getPortType(int id);
	VideoOutputPort 			&getPort(int id);
	VideoOutputPort 			&getPort(const std::string &name);
	List<VideoOutputPort> 		 getPorts();

	List<VideoOutputPortType> getSupportedTypes();
	List<VideoResolution> getSupportedResolutions();

	void load();

};

}

#endif /* VIDEOOUTPUTPORTCONFIG_HPP_ */
