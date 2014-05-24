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
#include "iarmProxy.hpp"

using namespace std;
namespace device {
    IARMProxy::IARMProxy()
    {
    }

    IARMProxy::~IARMProxy()
    {
    }

    IARMProxy& IARMProxy::getInstance()
    {
        static IARMProxy instance;
        return instance;
    }

/*    void IARMProxy::registerPowerEventHandler(IARM_EventHandler_t _eventHandler)
    {
          ;
	}*/

	 void IARMProxy::UnRegisterPowerEventHandler()
    {
        ;
	}
	
	
    
}
