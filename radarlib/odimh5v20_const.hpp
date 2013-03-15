/*
 * Radar Library
 *
 * Copyright (C) 2009-2010  ARPA-SIM <urpsim@smr.arpa.emr.it>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Author: Guido Billi <guidobilli@gmail.com>
 */

/*! \file
 *  \brief Constants and values used by OdimH5 library
 */

#ifndef __RADAR_ODIMH5V20_CONST_HPP__
#define __RADAR_ODIMH5V20_CONST_HPP__

#include <string>
#include <set>

#include "H5public.h"

#include <radarlib/defs.h>

/*===========================================================================*/

namespace OdimH5v20 
{

	extern RADAR_API const char* GROUP_WHAT;
	extern RADAR_API const char* GROUP_WHERE;
	extern RADAR_API const char* GROUP_HOW;
	extern RADAR_API const char* GROUP_DATASET;
	extern RADAR_API const char* GROUP_DATA;
	extern RADAR_API const char* GROUP_QUALITY;
	extern RADAR_API const char* DATASET_DATA;

	extern RADAR_API const char* ATTRIBUTE_ROOT_CONVENTIONS;
	extern RADAR_API const char* CONVENTIONS_ODIM_H5_V2_0;

	extern RADAR_API const char* ATTRIBUTE_WHAT_OBJECT;

	extern RADAR_API const char* OBJECT_PVOL;
	extern RADAR_API const char* OBJECT_CVOL;
	extern RADAR_API const char* OBJECT_SCAN;
	extern RADAR_API const char* OBJECT_RAY;
	extern RADAR_API const char* OBJECT_AZIM;
	extern RADAR_API const char* OBJECT_IMAGE;
	extern RADAR_API const char* OBJECT_COMP;
	extern RADAR_API const char* OBJECT_XSEC;
	extern RADAR_API const char* OBJECT_VP;
	extern RADAR_API const char* OBJECT_PIC;
	
	extern RADAR_API const char* ATTRIBUTE_WHAT_VERSION;
	extern RADAR_API const char* ATTRIBUTE_WHAT_VERSION_FORMAT;

	extern RADAR_API const char* ATTRIBUTE_WHAT_DATE;

	extern RADAR_API const char* ATTRIBUTE_WHAT_DATE_FORMAT;

	extern RADAR_API const char* ATTRIBUTE_WHAT_TIME;

	extern RADAR_API const char* ATTRIBUTE_WHAT_TIME_FORMAT;

	extern RADAR_API const char* ATTRIBUTE_WHAT_SOURCE;

	extern RADAR_API const char* SOURCE_WMO;
	extern RADAR_API const char* SOURCE_RAD;
	extern RADAR_API const char* SOURCE_ORG;
	extern RADAR_API const char* SOURCE_PLC;
	extern RADAR_API const char* SOURCE_CTY;
	extern RADAR_API const char* SOURCE_CMT;

	extern RADAR_API const char* ATTRIBUTE_WHAT_PRODUCT;

	extern RADAR_API const char* PRODUCT_SCAN;
	extern RADAR_API const char* PRODUCT_PPI; 
	extern RADAR_API const char* PRODUCT_CAPPI; 
	extern RADAR_API const char* PRODUCT_PCAPPI; 
	extern RADAR_API const char* PRODUCT_ETOP; 
	extern RADAR_API const char* PRODUCT_MAX; 
	extern RADAR_API const char* PRODUCT_RR; 
	extern RADAR_API const char* PRODUCT_VIL; 
	extern RADAR_API const char* PRODUCT_COMP; 
	extern RADAR_API const char* PRODUCT_VP; 
	extern RADAR_API const char* PRODUCT_RHI; 
	extern RADAR_API const char* PRODUCT_XSEC; 
	extern RADAR_API const char* PRODUCT_VSP; 
	extern RADAR_API const char* PRODUCT_HSP;
	extern RADAR_API const char* PRODUCT_RAY; 
	extern RADAR_API const char* PRODUCT_AZIM; 
	extern RADAR_API const char* PRODUCT_QUAL;
/*===========================================================================*/
/* ADDITIONAL PRODUCT */
/*===========================================================================*/
	extern RADAR_API const char* PRODUCT_LBM_ARPA;

	extern RADAR_API const char* ATTRIBUTE_WHAT_PRODPAR;
	extern RADAR_API const char* ATTRIBUTE_WHAT_QUANTITY;
	extern RADAR_API const char* ATTRIBUTE_WHAT_STARTDATE;
	extern RADAR_API const char* ATTRIBUTE_WHAT_STARTTIME;
	extern RADAR_API const char* ATTRIBUTE_WHAT_ENDDATE;
	extern RADAR_API const char* ATTRIBUTE_WHAT_ENDTIME;
	extern RADAR_API const char* ATTRIBUTE_WHAT_GAIN;
	extern RADAR_API const char* ATTRIBUTE_WHAT_OFFSET;
	extern RADAR_API const char* ATTRIBUTE_WHAT_NODATA;
	extern RADAR_API const char* ATTRIBUTE_WHAT_UNDETECT;

	extern RADAR_API const char* PRODUCT_QUANTITY_TH;		
	extern RADAR_API const char* PRODUCT_QUANTITY_TV;		
	extern RADAR_API const char* PRODUCT_QUANTITY_DBZH;	
	extern RADAR_API const char* PRODUCT_QUANTITY_DBZV;	
	extern RADAR_API const char* PRODUCT_QUANTITY_ZDR;	
	extern RADAR_API const char* PRODUCT_QUANTITY_RHOHV;	
	extern RADAR_API const char* PRODUCT_QUANTITY_LDR;	
	extern RADAR_API const char* PRODUCT_QUANTITY_PHIDP;	
	extern RADAR_API const char* PRODUCT_QUANTITY_KDP;	
	extern RADAR_API const char* PRODUCT_QUANTITY_SQI;	
	extern RADAR_API const char* PRODUCT_QUANTITY_SNR;	
	extern RADAR_API const char* PRODUCT_QUANTITY_RATE;	
	extern RADAR_API const char* PRODUCT_QUANTITY_ACRR;	
	extern RADAR_API const char* PRODUCT_QUANTITY_HGHT;	
	extern RADAR_API const char* PRODUCT_QUANTITY_VIL;	
	extern RADAR_API const char* PRODUCT_QUANTITY_VRAD;	
	extern RADAR_API const char* PRODUCT_QUANTITY_WRAD;	
	extern RADAR_API const char* PRODUCT_QUANTITY_UWND;	
	extern RADAR_API const char* PRODUCT_QUANTITY_VWND;	
	extern RADAR_API const char* PRODUCT_QUANTITY_BRDR;	
	extern RADAR_API const char* PRODUCT_QUANTITY_QIND;	
	extern RADAR_API const char* PRODUCT_QUANTITY_CLASS;	

	extern RADAR_API const char* PRODUCT_QUANTITY_ff;		
	extern RADAR_API const char* PRODUCT_QUANTITY_dd;		
	extern RADAR_API const char* PRODUCT_QUANTITY_ff_dev;	
	extern RADAR_API const char* PRODUCT_QUANTITY_dd_dev;	
	extern RADAR_API const char* PRODUCT_QUANTITY_n;		
	extern RADAR_API const char* PRODUCT_QUANTITY_dbz;	
	extern RADAR_API const char* PRODUCT_QUANTITY_dbz_dev;	
	extern RADAR_API const char* PRODUCT_QUANTITY_z;		
	extern RADAR_API const char* PRODUCT_QUANTITY_z_dev;	
	extern RADAR_API const char* PRODUCT_QUANTITY_w;		
	extern RADAR_API const char* PRODUCT_QUANTITY_w_dev;	
	extern RADAR_API const char* PRODUCT_QUANTITY_div;	
	extern RADAR_API const char* PRODUCT_QUANTITY_div_dev;	
	extern RADAR_API const char* PRODUCT_QUANTITY_def;	
	extern RADAR_API const char* PRODUCT_QUANTITY_def_dev;	
	extern RADAR_API const char* PRODUCT_QUANTITY_ad;		
	extern RADAR_API const char* PRODUCT_QUANTITY_ad_dev;	
	extern RADAR_API const char* PRODUCT_QUANTITY_chi2;	
	extern RADAR_API const char* PRODUCT_QUANTITY_rhohv;	
	extern RADAR_API const char* PRODUCT_QUANTITY_rhohv_dev;	

	extern RADAR_API const char* ATTRIBUTE_WHERE_LON;
	extern RADAR_API const char* ATTRIBUTE_WHERE_LAT;
	extern RADAR_API const char* ATTRIBUTE_WHERE_HEIGHT;

	extern RADAR_API const char* ATTRIBUTE_WHERE_ELANGLE;
	extern RADAR_API const char* ATTRIBUTE_WHERE_NBINS;
	extern RADAR_API const char* ATTRIBUTE_WHERE_RSTART;
	extern RADAR_API const char* ATTRIBUTE_WHERE_RSCALE;
	extern RADAR_API const char* ATTRIBUTE_WHERE_NRAYS;
	extern RADAR_API const char* ATTRIBUTE_WHERE_A1GATE;

	extern RADAR_API const char* ATTRIBUTE_WHERE_STARTAZ;
	extern RADAR_API const char* ATTRIBUTE_WHERE_STOPAZ;

	extern RADAR_API const char* ATTRIBUTE_WHERE_PROJDEF;
	extern RADAR_API const char* ATTRIBUTE_WHERE_XSIZE;
	extern RADAR_API const char* ATTRIBUTE_WHERE_YSIZE;
	extern RADAR_API const char* ATTRIBUTE_WHERE_XSCALE;
	extern RADAR_API const char* ATTRIBUTE_WHERE_YSCALE;
	extern RADAR_API const char* ATTRIBUTE_WHERE_LL_LON;
	extern RADAR_API const char* ATTRIBUTE_WHERE_LL_LAT;
	extern RADAR_API const char* ATTRIBUTE_WHERE_UL_LON;
	extern RADAR_API const char* ATTRIBUTE_WHERE_UL_LAT;
	extern RADAR_API const char* ATTRIBUTE_WHERE_UR_LON;
	extern RADAR_API const char* ATTRIBUTE_WHERE_UR_LAT;
	extern RADAR_API const char* ATTRIBUTE_WHERE_LR_LON;
	extern RADAR_API const char* ATTRIBUTE_WHERE_LR_LAT;

	extern RADAR_API const char* ATTRIBUTE_WHERE_MINHEIGHT;
	extern RADAR_API const char* ATTRIBUTE_WHERE_MAXHEIGHT;

	extern RADAR_API const char* ATTRIBUTE_WHERE_AZ_ANGLE;
	extern RADAR_API const char* ATTRIBUTE_WHERE_ANGLES;
	extern RADAR_API const char* ATTRIBUTE_WHERE_RANGE;

	extern RADAR_API const char* ATTRIBUTE_WHERE_START_LON;
	extern RADAR_API const char* ATTRIBUTE_WHERE_START_LAT;
	extern RADAR_API const char* ATTRIBUTE_WHERE_STOP_LON;
	extern RADAR_API const char* ATTRIBUTE_WHERE_STOP_LAT;

	extern RADAR_API const char* ATTRIBUTE_WHERE_LEVELS;
	extern RADAR_API const char* ATTRIBUTE_WHERE_INTERVAL;

	extern RADAR_API const char* ATTRIBUTE_HOW_TASK;
	extern RADAR_API const char* ATTRIBUTE_HOW_STARTEPOCHS;
	extern RADAR_API const char* ATTRIBUTE_HOW_ENDEPOCHS;
	extern RADAR_API const char* ATTRIBUTE_HOW_SYSTEM;
	extern RADAR_API const char* ATTRIBUTE_HOW_SOFTWARE;

	extern RADAR_API const char* SOFTWARE_CASTOR;
	extern RADAR_API const char* SOFTWARE_EDGE; 
	extern RADAR_API const char* SOFTWARE_FROG; 
	extern RADAR_API const char* SOFTWARE_IRIS; 
	extern RADAR_API const char* SOFTWARE_NORDRAD; 
	extern RADAR_API const char* SOFTWARE_RADARNET; 
	extern RADAR_API const char* SOFTWARE_RAINBOW; 


	extern RADAR_API const char* ATTRIBUTE_HOW_SW_VERSION;
	extern RADAR_API const char* ATTRIBUTE_HOW_ZR_A;
	extern RADAR_API const char* ATTRIBUTE_HOW_ZR_B;
	extern RADAR_API const char* ATTRIBUTE_HOW_KR_A;
	extern RADAR_API const char* ATTRIBUTE_HOW_KR_B;
	extern RADAR_API const char* ATTRIBUTE_HOW_SIMULATED;

	extern RADAR_API const char* ATTRIBUTE_HOW_BEAMWIDTH;
	extern RADAR_API const char* ATTRIBUTE_HOW_WAVELENGTH;
	extern RADAR_API const char* ATTRIBUTE_HOW_RPM;
	extern RADAR_API const char* ATTRIBUTE_HOW_PULSEWIDTH; 
	extern RADAR_API const char* ATTRIBUTE_HOW_LOWPRF; 
	extern RADAR_API const char* ATTRIBUTE_HOW_HIGHPRF;

	extern RADAR_API const char* ATTRIBUTE_HOW_AZMETHOD;
	extern RADAR_API const char* ATTRIBUTE_HOW_BINMETHOD;
	extern RADAR_API const char* ATTRIBUTE_HOW_AZANGLES;
	extern RADAR_API const char* ATTRIBUTE_HOW_ELANGLES;

	extern RADAR_API const char* METHOD_NEAREST;
	extern RADAR_API const char* METHOD_INTERPOL;
	extern RADAR_API const char* METHOD_AVERAGE;
	extern RADAR_API const char* METHOD_RANDOM;
	extern RADAR_API const char* METHOD_MDE;
	extern RADAR_API const char* METHOD_LATEST;
	extern RADAR_API const char* METHOD_MAXIMUM;
	extern RADAR_API const char* METHOD_DOMAIN;
	extern RADAR_API const char* METHOD_VAD;
	extern RADAR_API const char* METHOD_VVP;
	extern RADAR_API const char* METHOD_RGA;

	extern RADAR_API const char* ATTRIBUTE_HOW_AZTIMES;

	extern RADAR_API const char* ATTRIBUTE_HOW_ANGLES;
	extern RADAR_API const char* ATTRIBUTE_HOW_AROTATION;
	extern RADAR_API const char* ATTRIBUTE_HOW_CAMETHOD;
	extern RADAR_API const char* ATTRIBUTE_HOW_NODES;
	extern RADAR_API const char* ATTRIBUTE_HOW_ACCNUM;

	extern RADAR_API const char* ATTRIBUTE_HOW_MINRANGE;
	extern RADAR_API const char* ATTRIBUTE_HOW_MAXRANGE;
	extern RADAR_API const char* ATTRIBUTE_HOW_NI;
	extern RADAR_API const char* ATTRIBUTE_HOW_DEALIASED;

	extern RADAR_API const char* ATTRIBUTE_HOW_POINTACCEL;
	extern RADAR_API const char* ATTRIBUTE_HOW_POINTACCAZ; 
	extern RADAR_API const char* ATTRIBUTE_HOW_MALFUNC; 
	extern RADAR_API const char* ATTRIBUTE_HOW_RADAR_MSG;
	extern RADAR_API const char* ATTRIBUTE_HOW_RADHORIZ;
	extern RADAR_API const char* ATTRIBUTE_HOW_MDS;
	extern RADAR_API const char* ATTRIBUTE_HOW_OUR;
	extern RADAR_API const char* ATTRIBUTE_HOW_DCLUTTER;
	extern RADAR_API const char* ATTRIBUTE_HOW_COMMENT;
	extern RADAR_API const char* ATTRIBUTE_HOW_SQI;
	extern RADAR_API const char* ATTRIBUTE_HOW_CSR;
	extern RADAR_API const char* ATTRIBUTE_HOW_LOG;
	extern RADAR_API const char* ATTRIBUTE_HOW_VPRCORR;
	extern RADAR_API const char* ATTRIBUTE_HOW_FREEZE;
	extern RADAR_API const char* ATTRIBUTE_HOW_MIN;
	extern RADAR_API const char* ATTRIBUTE_HOW_MAX;
	extern RADAR_API const char* ATTRIBUTE_HOW_STEP;
	extern RADAR_API const char* ATTRIBUTE_HOW_LEVELS; 
	extern RADAR_API const char* ATTRIBUTE_HOW_PEAKPWR;
	extern RADAR_API const char* ATTRIBUTE_HOW_AVGPWR;
	extern RADAR_API const char* ATTRIBUTE_HOW_DYNRANGE;
	extern RADAR_API const char* ATTRIBUTE_HOW_RAC;
	extern RADAR_API const char* ATTRIBUTE_HOW_BBC;
	extern RADAR_API const char* ATTRIBUTE_HOW_PAC;
	extern RADAR_API const char* ATTRIBUTE_HOW_S2N;
	extern RADAR_API const char* ATTRIBUTE_HOW_POLARIZATION;

	extern RADAR_API const char* POLARIZATION_H;
	extern RADAR_API const char* POLARIZATION_V;

	extern RADAR_API const char* ATTRIBUTE_CLASS;
	extern RADAR_API const char* CLASS_IMAGE;

	extern RADAR_API const char* ATTRIBUTE_IMAGE_VERSION;
	extern RADAR_API const char* IMAGE_VERSION_1_2;

	extern RADAR_API const char* ATTRIBUTE_PAL_VERSION;

	const char SEQUENCE_SEPARATOR	= ',';
	const char PAIR_SEPARATOR	= ':';

	extern RADAR_API const char* TRUESTR;
	extern RADAR_API const char* FALSESTR;

	/*! 
	 * \brief Generic OdimH5 specification functions
	 * 
	 * This class collects some methods to check or retrive informations about OdimH5 specifications.
	 */
	class RADAR_API Specification
	{
	public:
		/*! 
		 * \brief Check if given value is a valid 'object' attribute value
		 */
		static bool isObject(const std::string& value);
		/*! 
		 * \brief Check if given value is a valid 'software' attribute value
		 */
		static bool isSoftware(const std::string& value);
		/*! 
		 * \brief Check if given value is a valid 'method' attribute value
		 */
		static bool isMethod(const std::string& value);
		/*! 
		 * \brief Check if given value is a valid 'polarization' attribute value
		 */
		static bool isPolarization(const std::string& value);

		/*! 
		 * \brief Gets the names of standard attributes
		 * \param names		the STL set that will hold the values
		 */
		static void getStandardAttributes(std::set<std::string>& names);
		/*! 
		 * \brief Gets the names of standard quantities
		* \param names		the STL set that will hold the values
		 */
		static void getStandardQuantities(std::set<std::string>& names);
	};

}

/*===========================================================================*/

#endif
