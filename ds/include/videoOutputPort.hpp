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
 
#ifndef _DS_VIDEOOUTPUTPORT_H_
#define _DS_VIDEOOUTPUTPORT_H_

#include "enumerable.hpp"
#include "aspectRatio.hpp"
#include <string>

namespace device {
class VideoOutputPortType;
class AudioOutputPort;
class VideoResolution;

class  VideoOutputPort : public Enumerable {
	int _type;
	int _index;
	int  _id;

	int _handle;
	std::string _name;

	bool _enabled;
	bool _contentProtected;
	bool _displayConnected;

	int _aPortId;

	std::string _defaultResolution;
	std::string _resolution;

	static const char * kPropertyResolution;


public:

    class Display {
    	friend class VideoOutputPort;
    	 int _handle;
    	 int _productCode;
    	 int _serialNumber;
    	 int _manufacturerYear;
    	 int _manufacturerWeek;
    	 int _aspectRatio;

    public:
    	Display() :_handle(0), _productCode(0), _serialNumber(0), _manufacturerYear(0), _manufacturerWeek(0), _aspectRatio(0) {};
    	Display(VideoOutputPort &vPort);
    	virtual ~Display();
    	const int getProductCode() const {return _productCode;};
    	const int getSerialNumber() const {return _serialNumber;};
    	const int getManufacturerYear() const {return _manufacturerYear;};
    	const int getManufacturerWeek() const {return _manufacturerWeek;};
    	const AspectRatio& getAspectRatio() const {return AspectRatio::getInstance(_aspectRatio);};
    };

 	static VideoOutputPort & getInstance(int id);
 	static VideoOutputPort & getInstance(const std::string &name);
 	VideoOutputPort(const int type, const int index, const int id, int audioPortId, const std::string &resolution);
	virtual ~VideoOutputPort();

	const VideoOutputPortType &getType() const;
 	const int getId() const {return _id; };
 	const std::string &getName() const {return _name;};
	const int getIndex() const {return _index; };

	AudioOutputPort &getAudioOutputPort();
	const VideoResolution &getResolution() const;
	const VideoResolution &getDfeaultResolution() const;

    const VideoOutputPort::Display &getDisplay();
	const bool isDisplayConnected() const;
	const bool isContentProtected() const {return false;};
	const bool isEnabled() const;
	const bool isDynamicResolutionSupported() const;

	void setAudioPort(int id) { _aPortId = id; };
	void setResolution(const std::string &resolution);
	void setDisplayConnected(const bool connected);
	void enable();
	void disable();

private:
	Display _display;


};

}

#endif /* _DS_VIDEOOUTPUTPORT_H_ */
