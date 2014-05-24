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
 
#include <iostream>
#include <algorithm>
#include <string.h>
#include "iarmProxy.hpp"
#include "audioOutputPortConfig.hpp"
#include "videoOutputPortConfig.hpp"
#include "list.hpp"
#include "host.hpp"
#include "videoDeviceConfig.hpp"
#include "dsVideoPort.h"
#include "dsVideoDevice.h"
#include "dsAudio.h"
#include "dsDisplay.h"


#if 0 //#ifndef __EMU_BUILD__
#include "comcastIrKeyCodes.h"
#endif

using namespace std;

namespace device 
{
   	
	const int Host::kPowerOn = dsPOWER_ON;
    const int Host::kPowerOff = dsPOWER_OFF;
    const int Host::kPowerStandby = dsPOWER_STANDBY;
   
    Host::Host() : _persistence("/opt/ds/hostData")
    {
    }

    Host::~Host() {
    	if (true)
		{
			IARMProxy::getInstance().UnRegisterPowerEventHandler();
		}
    }

    Host& Host::getInstance()
    {
        static Host instance;
        static bool isFirstTime = true;
        try {
			if (isFirstTime) {
				isFirstTime = false;
            }
            else {
            }
        }
        catch (...) {
    		cout << "Exception Thrown ...!\n";
        }
        return instance;
    }

    void Host::addPowerModeListener(PowerModeChangeListener *l)
    {
        std::list < PowerModeChangeListener* > ::iterator it;
        
        it = find (powerEvntListeners.begin(),powerEvntListeners.end(), l);
        if (it == powerEvntListeners.end())
        {
            powerEvntListeners.push_back (l);
            cout << "Added Power Mode listener...!\n";
        }
        else
        {
            cout << "Already register for Power Mode Change\n";
        }
        return ;
    }

    void Host::removePowerModeChangeListener(PowerModeChangeListener *l)
    {
        std::list < PowerModeChangeListener* > ::iterator it ;
        it = find (powerEvntListeners.begin(),powerEvntListeners.end(), l);
        if (it == powerEvntListeners.end())
        {
            cout << "Not Registered for Power Mode change yet...!\n";
        }
        else
        {
            powerEvntListeners.erase (it);
            cout << "Removed from Power Mode listener group..!\n";
        }
        return;
    }

    void Host::addDisplayConnectionListener (DisplayConnectionChangeListener *l)
    {
        std::list < DisplayConnectionChangeListener* > ::iterator it;
        
        it = find (dispEvntListeners.begin(), dispEvntListeners.end(), l);
        if (it == dispEvntListeners.end())
        {
            dispEvntListeners.push_back (l);
            cout << "Added Display listener...!\n";
        }
        else
        {
            cout << "Already registered to the Display listener\n";
        }
        return ;
    }

    void Host::removeDisplayConnectionListener (DisplayConnectionChangeListener *l)
    {
        std::list < DisplayConnectionChangeListener* > ::iterator it ;
        it = find (dispEvntListeners.begin(), dispEvntListeners.end(), l);
        if (it == dispEvntListeners.end())
        {
            cout << "Not Registered to Display Listener yet...!\n";
        }
        else
        {
            dispEvntListeners.erase (it);
            cout << "Removed from the Display listener...!\n";
        }
        return;
    }


    void Host::notifyPowerChange (const  int mode)
    {
    	std::list < PowerModeChangeListener* > ::iterator it;
        for ( it = powerEvntListeners.begin() ; it != powerEvntListeners.end(); it++ )
        {
            (*it)->powerModeChanged (mode);
        }
    }

    
    void Host::notifyDisplayConnectionChange (int portHandle, bool newConnectionStatus)
    {
        std::list < DisplayConnectionChangeListener* > ::iterator it;
        for ( it = dispEvntListeners.begin() ; it != dispEvntListeners.end(); it++ )
        {
            (*it)->displayConnectionChanged(getVideoOutputPort(portHandle), newConnectionStatus);
            getVideoOutputPort(portHandle).setDisplayConnected(newConnectionStatus);
        }
    }

    bool Host::setPowerMode(int mode)
    {
        
        return true;
    }

    int Host::getPowerMode()
    {
	  return 1;  //for testing to avoid warnings
    }

    List<VideoOutputPort>  Host::getVideoOutputPorts()
    {
    	List<VideoOutputPort> rPorts;

        List<VideoOutputPortType> vTypes =  VideoOutputPortConfig::getInstance().getSupportedTypes();
        for (size_t i = 0; i < vTypes.size(); i++) {
        	List<VideoOutputPort> vPorts = vTypes.at(i).getPorts();
            for (size_t j = 0; j < vPorts.size(); j++) {
            	rPorts.push_back(vPorts.at(j));
            }
        }

    	return rPorts;
    }

    List<AudioOutputPort>  Host::getAudioOutputPorts()
    {
    	List<AudioOutputPort> rPorts;

        List<AudioOutputPortType> aTypes = AudioOutputPortConfig::getInstance().getSupportedTypes();
        for (size_t i = 0; i < aTypes.size(); i++) {
        	List<AudioOutputPort> aPorts = aTypes.at(i).getPorts();
            for (size_t j = 0; j < aPorts.size(); j++) {
            	rPorts.push_back(aPorts.at(j));
            }
        }

    	return rPorts;
    }

    List<VideoDevice>  Host::getVideoDevices()
    {
        return VideoDeviceConfig::getInstance().getDevices();
    }


    VideoOutputPort &Host::getVideoOutputPort(const std::string &name)
    {
        return VideoOutputPortConfig::getInstance().getPort(name);
    }

    VideoOutputPort &Host::getVideoOutputPort(int id)
    {
        return VideoOutputPortConfig::getInstance().getPort(id);
    }

    HostPersistence & Host::getPersistence()
    {
    	return _persistence;
    }

}
