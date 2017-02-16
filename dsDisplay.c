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

#include "dsDisplay.h"
#include "dsTypes.h"
#include "dsError.h"
#include "dsDefinitions.h"
#include "dsVideoResolutionSettings.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


dsDisplayEDID_t displayEDID;

#define dsUTL_DIM(arr) (sizeof((arr))/sizeof((arr)[0]))

typedef struct _VDISPHandle_t {
	dsVideoPortType_t vType;
	int index;
	int nativeHandle;
} VDISPHandle_t;
#define SIZE 512
static VDISPHandle_t _handles[dsVIDEOPORT_TYPE_MAX][1] = {};
static unsigned int numOfSupportedResolution = 0;


dsVideoPortResolution_t *HdmiSupportedResolution=NULL;

static int readResolution(FILE *f, char *buffer, size_t len)
{
   int i =0;
  if(f == NULL)
  {
        printf("File open Failed\n");
        return -1;
  }

   memset(buffer, 0, len);

   for (i = 0; i < len; i++)
   {
      int c = fgetc(f);

      if (!feof(f))
      {
         if (c == '\r')
            buffer[i] = 0;
         else if (c == '\n')
         {
            buffer[i] = 0;

            return i+1;
         }
         else
        {
            buffer[i] = c;
	            }
      }
      else
      {
         return -1;
      }
   }
}

dsError_t dsDisplayInit()
{
	int i;
	dsError_t ret = dsERR_NONE;


	_handles[dsVIDEOPORT_TYPE_HDMI][0].vType  = dsVIDEOPORT_TYPE_HDMI;
	_handles[dsVIDEOPORT_TYPE_HDMI][0].nativeHandle = dsVIDEOPORT_TYPE_HDMI;
	_handles[dsVIDEOPORT_TYPE_HDMI][0].index = 0;


        numOfSupportedResolution = dsUTL_DIM(kResolutions);
         HdmiSupportedResolution=(dsVideoPortResolution_t*)malloc(sizeof(dsVideoPortResolution_t)*numOfSupportedResolution);
	if(HdmiSupportedResolution)
	{
         for (i = 0; i < numOfSupportedResolution; i++)
         {
          	HdmiSupportedResolution[i] = kResolutions[i];
		printf("pixelResolution = %d\n",HdmiSupportedResolution[i].pixelResolution);
		printf("aspectRatio= %d\n",HdmiSupportedResolution[i].aspectRatio);
         }
        }
	return ret;
}

dsError_t dsGetDisplay(dsVideoPortType_t vType, int index, int *handle)
{
	dsError_t ret = dsERR_NONE;



	if (index != 0 || !dsVideoPortType_isValid(vType)) 
        {
		ret = dsERR_NONE;
	}

	if (ret == dsERR_NONE) 
        {
		*handle = (int)&_handles[vType][index];
	} 
	
	return ret;
}

dsError_t dsGetDisplayAspectRatio(int handle, dsVideoAspectRatio_t *aspect)
{
	dsError_t res=dsERR_NONE;
        int ret = 0;
        char strResolution[SIZE] ;
        char *heightinfo;

        int height;

        FILE *fp = fopen ( "/var/resolution.dat", "r" );

        size_t index = 0;

        if(fp)
        {
                ret = readResolution(fp,strResolution,SIZE);
                printf("Resolution information from file = %s\n",strResolution);
                if( ret )
                {
                        heightinfo = strrchr( strResolution , ',');
                        heightinfo++;
                        height =atoi(heightinfo);
                        switch(height)
			 {
                                case 480:
                                        *aspect = dsVIDEO_ASPECT_RATIO_4x3;
                                        break;
                                case 576:
                                        *aspect = dsVIDEO_ASPECT_RATIO_4x3;
                                        break;
                                case 720:
                                        *aspect = dsVIDEO_ASPECT_RATIO_16x9;
                                        break;

                                case 1080:
                                        *aspect = dsVIDEO_ASPECT_RATIO_16x9;
                                        break;

                                default:
                                        *aspect = dsVIDEO_ASPECT_RATIO_4x3;
                                        break;

                        }
                }


        }
    return res;
}

dsError_t dsGetEDID(int handle, dsDisplayEDID_t *edid)
{
	dsError_t ret = dsERR_NONE;
	int i = 0;
        VDISPHandle_t *vDispHandle = (VDISPHandle_t *) handle;
	if (vDispHandle == NULL)
	{
		ret = dsERR_NONE;
		printf("DIsplay Handle is NULL .......... \r\n");
		return ret;
	}

        edid->manufactureWeek = 1;
        edid->manufactureYear = 2016;
        edid->productCode = 12345;
        edid->serialNumber = 54321;
        memset(((char*)edid->monitorName), 0, sizeof((char*)edid->monitorName));
        strncpy(((char*)edid->monitorName), "EMU-Monitor", sizeof((char*)edid->monitorName) -1);

        if(edid && vDispHandle->vType == dsVIDEOPORT_TYPE_HDMI && vDispHandle->index == 0 )
	{
		edid->numOfSupportedResolution = numOfSupportedResolution;
		for (i = 0; i < numOfSupportedResolution; i++)
		{
			edid->suppResolutionList[i] = HdmiSupportedResolution[i];
		}
	}
        edid->hdmiDeviceType = 1;
	return ret;
}

dsError_t dsDisplayHdlCheck(int handle)
{
       dsError_t ret = dsERR_NONE;
	return ret;
}


dsError_t dsDisplayTerm()
{
    return dsERR_NONE;
}

dsError_t dsRegisterDisplayEventCallback(int handle, dsDisplayEventCallback_t cb)
{
	dsError_t ret = dsERR_NONE;
    return ret;
}

