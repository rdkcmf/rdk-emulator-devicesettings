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
 
#ifndef IARMPROXY_H_
#define IARMPROXY_H_

//#include "libIBus.h"

namespace device {

class IARMProxy {
public:
//    void registerPowerEventHandler(IARM_EventHandler_t _eventHandler);
	void UnRegisterPowerEventHandler();
	static IARMProxy& getInstance(void);
private:
	IARMProxy();
	virtual ~IARMProxy();
    IARMProxy (const IARMProxy&);
    IARMProxy& operator=(const IARMProxy&);
};

}

#endif /* IARMPROXY_H_ */
