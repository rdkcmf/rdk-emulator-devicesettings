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
#include <sstream>

#include "frontPanelTextDisplay.hpp"
#include "frontPanelConfig.hpp"
#include "illegalArgumentException.hpp"
#include "host.hpp"

#include "dsError.h"
#include "dsTypes.h"

using namespace std;

std::string numToStr (int number)
{
    stringstream convert;
    convert << number;
    return convert.str();
}

int strToNum (std::string text)
{
    int number;
    stringstream convert (text);

    if (!(convert >> number) )
                number = 0;

    return number;
}


namespace {
	const char *_names[] = {
			"Text",
	};

	inline const bool isValid(int id) {
		return dsFPDTextDisplay_isValid(id);
	}
}


namespace device {

const int FrontPanelTextDisplay::kModeClock12Hr = dsFPD_TIME_12_HOUR;
const int FrontPanelTextDisplay::kModeClock24Hr = dsFPD_TIME_24_HOUR;
const int FrontPanelTextDisplay::kModeString    = dsFPD_TIME_STRING;
const char * FrontPanelTextDisplay::kPropertyBrightness = ".brightness";

FrontPanelTextDisplay & FrontPanelTextDisplay::getInstance(int id)
{
	if (::isValid(id)) {
		return FrontPanelConfig::getInstance().getTextDisplay(id);
	}
	else {
		throw IllegalArgumentException();
	}

}

FrontPanelTextDisplay & FrontPanelTextDisplay::getInstance(const std::string &name)
{
	for (size_t i = 0; i < dsUTL_DIM(_names); i++) {
		if (name.compare(_names[i]) == 0) {
			return FrontPanelConfig::getInstance().getTextDisplay(i);
		}
	}

	throw IllegalArgumentException();
}

FrontPanelTextDisplay::FrontPanelTextDisplay(int id, int maxBrightness, int maxCycleRate,
                                             int maxHorizontalIterations, int maxVerticalIterations,
                                             const string &supportedCharacters):
                                             FrontPanelIndicator(id, maxBrightness, maxCycleRate)
{
  _timeFormat = kModeClock24Hr;
  _scroll = Scroll(maxVerticalIterations, maxHorizontalIterations);
	if (::isValid(id)) {
		_id = id;
		_name = std::string(_names[id]);
		
	    /* Init the Text Brightness */
	    string value = Host::getInstance().getPersistence().getProperty (_name + kPropertyBrightness, numToStr(maxBrightness));
	    _TextBrightness = strToNum (value);
	    //dsSetFPTextBrightness((dsFPDTextDisplay_t)_id,_TextBrightness);
		
	}
	else {
		throw IllegalArgumentException();
	}
}

FrontPanelTextDisplay::~FrontPanelTextDisplay()
{
}

void FrontPanelTextDisplay::setText(const std::string &text)
{
    dsSetFPText(text.c_str());
}


void FrontPanelTextDisplay::setTextBrightness(const int &brightness)
{
    //dsSetFPTextBrightness((dsFPDTextDisplay_t)_id, brightness);
    _TextBrightness = brightness;
    Host::getInstance().getPersistence().persistHostProperty(getName() + kPropertyBrightness, numToStr(brightness));
}

void FrontPanelTextDisplay::setScroll(const Scroll & scroll)
{
    dsSetFPScroll(scroll.getVerticalIteration(), scroll.getHorizontalIteration(), scroll.getHoldDuration());
    _scroll = scroll;
}

void FrontPanelTextDisplay::setTimeFormat(const int iTimeFormat)
{
    if ((iTimeFormat == kModeClock24Hr) || (iTimeFormat == kModeClock12Hr))
    {
        _timeFormat = iTimeFormat;
    }
}
void FrontPanelTextDisplay::setTime(const int uiHours, const int uiMinutes)
{
    dsSetFPTime ((dsFPDTimeFormat_t)_timeFormat, uiHours, uiMinutes);
}

}
