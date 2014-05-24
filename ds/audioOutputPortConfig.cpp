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
 
#include "audioOutputPortConfig.hpp"
#include "dsAudioSettings.h"
#include "illegalArgumentException.hpp"
#include "dsError.h"
#include "dsUtl.h"
#include "stdlib.h"
#include <string.h>

static dsAudioTypeConfig_t kConfigs[2];
static dsAudioPortConfig_t kPorts[2];

namespace device {


AudioOutputPortConfig::AudioOutputPortConfig()
{
}

AudioOutputPortConfig::~AudioOutputPortConfig()
{
}

AudioOutputPortConfig & AudioOutputPortConfig::getInstance()
{
    static AudioOutputPortConfig _singleton;
	return _singleton;
}

const AudioEncoding &AudioOutputPortConfig::getEncoding(int id) const
{
	return _aEncodings.at(id);
}
const AudioCompression &AudioOutputPortConfig::getCompression(int id) const
{
	return _aCompressions.at(id);

}
const AudioStereoMode &AudioOutputPortConfig::getStereoMode(int id) const
{
	return _aStereoModes.at(id);

}
AudioOutputPortType & AudioOutputPortConfig::getPortType(int id)
{
	return _aPortTypes.at(id);
}

AudioOutputPort &AudioOutputPortConfig::getPort(int id)
{
	return _aPorts.at(id);
}

AudioOutputPort &AudioOutputPortConfig::getPort(const std::string & name)
{
	for (size_t i = 0; i < _aPorts.size(); i++) {
		if (name.compare(_aPorts.at(i).getName()) == 0) {
			return _aPorts.at(i);
		}
	}

	throw IllegalArgumentException();
}

List<AudioOutputPort> AudioOutputPortConfig::getPorts()
{
	List <AudioOutputPort> rPorts;

	for (size_t i = 0; i < _aPorts.size(); i++) {
		rPorts.push_back(_aPorts.at(i));
	}

	return rPorts;
}

List<AudioOutputPortType>  AudioOutputPortConfig::getSupportedTypes()
{
	List<AudioOutputPortType> supportedTypes;
	for (std::vector<AudioOutputPortType>::const_iterator it = _aPortTypes.begin(); it != _aPortTypes.end(); it++) {
		if (it->isEnabled()) {
			supportedTypes.push_back(*it);
		}
	}

	return supportedTypes;
}

void AudioOutputPortConfig::load()
{
	try {
		/*
		 * Load Constants First.
		 */
		for (int i = 0; i < dsAUDIO_ENC_MAX; i++) {
			_aEncodings.push_back(AudioEncoding(i));
		}

		for (int i = 0; i < dsAUDIO_CMP_MAX; i++) {
			_aCompressions.push_back(AudioCompression(i));

		}

		for (int i = 0; i < dsAUDIO_STEREO_MAX; i++) {
			_aStereoModes.push_back(AudioStereoMode(i));

		}

		for (int i = 0; i < dsAUDIOPORT_TYPE_MAX; i++) {
			_aPortTypes.push_back(AudioOutputPortType(i));

		}

        /**************** Audio Ports Configuration -LnT Infotech**************/

        for(size_t i =0;i<2;i++) {
            kConfigs[i].typeId = i;
            kConfigs[i].name = (char*)malloc(6);
            strcpy((char*)kConfigs[i].name,"HDMI");
            kConfigs[i].numSupportedCompressions = 1;
            kConfigs[i].numSupportedStereoModes = 1;
            kConfigs[i].numSupportedEncodings = 1;
            kConfigs[i].compressions =(dsAudioCompression_t*)malloc(sizeof(dsAudioCompression_t));
            *((dsAudioCompression_t*)kConfigs[i].compressions + 0) = (dsAudioCompression_t)0;
            kConfigs[i].encodings =(dsAudioEncoding_t*)malloc(sizeof(dsAudioEncoding_t));
            *((dsAudioEncoding_t*)kConfigs[i].encodings + 0) = (dsAudioEncoding_t)0;
            kConfigs[i].stereoModes =(dsAudioStereoMode_t*)malloc(sizeof(dsAudioStereoMode_t));
            *((dsAudioStereoMode_t*)kConfigs[i].stereoModes +0) = (dsAudioStereoMode_t)0;
            kPorts[i].id.type = (dsAudioPortType_t)(i);
            kPorts[i].id.index = i;
            kPorts[i].connectedVOPs = (dsVideoPortPortId_t*)malloc(sizeof(dsVideoPortPortId_t));
            ((dsVideoPortPortId_t*)kPorts[i].connectedVOPs)->type = (dsVideoPortType_t)i;
            ((dsVideoPortPortId_t*)kPorts[i].connectedVOPs)->index = i;
        }

		/**************** END OF THE CODE -LnT Infotech ***************/

		/*
		 * Initialize Audio portTypes (encodings, compressions etc.)
		 * and its port instances (db, level etc)
		 */
		for (size_t i = 0; i < dsUTL_DIM(kConfigs); i++) {
			const dsAudioTypeConfig_t *typeCfg = &kConfigs[i];
			AudioOutputPortType &aPortType = AudioOutputPortType::getInstance(typeCfg->typeId);
			aPortType.enable();
			for (size_t j = 0; j < typeCfg->numSupportedEncodings; j++) {
				aPortType.addEncoding(AudioEncoding::getInstance(typeCfg->encodings[j]));
				_aEncodings.at(typeCfg->encodings[j]).enable();
			}
			for (size_t j = 0; j < typeCfg->numSupportedCompressions; j++) {
				aPortType.addCompression(typeCfg->compressions[j]);
				_aCompressions.at(typeCfg->compressions[j]).enable();

			}
			for (size_t j = 0; j < typeCfg->numSupportedStereoModes; j++) {
				aPortType.addStereoMode(typeCfg->stereoModes[j]);
				_aStereoModes.at(typeCfg->stereoModes[j]).enable();

			}
		}

		/*
		 * set up ports based on kPorts[]
		 */
		for (size_t i = 0; i < dsUTL_DIM(kPorts); i++) {
			const dsAudioPortConfig_t *port = &kPorts[i];
			_aPorts.push_back(AudioOutputPort((port->id.type), port->id.index, i));
			_aPortTypes.at(port->id.type).addPort(_aPorts.at(i));
		}

	}
	catch(const Exception &e) {
		throw e;
	}
}
}

