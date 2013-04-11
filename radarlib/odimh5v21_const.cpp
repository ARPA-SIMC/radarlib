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

#include <radarlib/odimh5v21_const.hpp>

namespace OdimH5v21 {

/*===========================================================================*/

const char* GROUP_WHAT				= "what";
const char* GROUP_WHERE				= "where";
const char* GROUP_HOW				= "how";
const char* GROUP_DATASET			= "dataset";
const char* GROUP_DATA				= "data";
const char* GROUP_QUALITY			= "quality";
const char* DATASET_DATA			= "data";

const char* ATTRIBUTE_ROOT_CONVENTIONS		= "Conventions";
const char* CONVENTIONS_ODIM_H5_V2_1		= "ODIM_H5/V2_1";

const char* ATTRIBUTE_WHAT_OBJECT		= "object";

const char* OBJECT_PVOL				= "PVOL";
const char* OBJECT_CVOL				= "CVOL";
const char* OBJECT_SCAN				= "SCAN";
const char* OBJECT_RAY				= "RAY";
const char* OBJECT_AZIM				= "AZIM";
const char* OBJECT_IMAGE			= "IMAGE";
const char* OBJECT_COMP				= "COMP";
const char* OBJECT_XSEC				= "XSEC";
const char* OBJECT_VP				= "VP";	
const char* OBJECT_PIC				= "PIC";

const char* ATTRIBUTE_WHAT_VERSION		= "version";
const char* ATTRIBUTE_WHAT_VERSION_FORMAT	= "H5rad %d.%d";
const char* ATTRIBUTE_WHAT_DATE			= "date";
const char* ATTRIBUTE_WHAT_DATE_FORMAT		= "%Y%m%d";
const char* ATTRIBUTE_WHAT_TIME			= "time";
const char* ATTRIBUTE_WHAT_TIME_FORMAT		= "%H%M%S";
const char* ATTRIBUTE_WHAT_SOURCE		= "source";

const char* SOURCE_WMO				= "WMO";
const char* SOURCE_RAD				= "RAD";
const char* SOURCE_ORG				= "ORG";
const char* SOURCE_PLC				= "PLC";
const char* SOURCE_CTY				= "CTY";
const char* SOURCE_CMT				= "CMT";

const char* ATTRIBUTE_WHAT_PRODUCT		= "product";

const char* PRODUCT_SCAN			= "SCAN";
const char* PRODUCT_PPI				= "PPI"; 
const char* PRODUCT_CAPPI			= "CAPPI";
const char* PRODUCT_PCAPPI			= "PCAPPI";
const char* PRODUCT_ETOP			= "ETOP";
const char* PRODUCT_MAX				= "MAX";
const char* PRODUCT_RR				= "RR";
const char* PRODUCT_VIL				= "VIL";
const char* PRODUCT_COMP			= "COMP";
const char* PRODUCT_VP				= "VP";
const char* PRODUCT_RHI				= "RHI";
const char* PRODUCT_XSEC			= "XSEC";
const char* PRODUCT_VSP				= "VSP";
const char* PRODUCT_HSP				= "HSP";
const char* PRODUCT_RAY				= "RAY";
const char* PRODUCT_AZIM			= "AZIM";
const char* PRODUCT_QUAL			= "QUAL";
/*===========================================================================*/
/* ADDITIONAL PRODUCT */
/*===========================================================================*/
const char* PRODUCT_LBM_ARPA= "NEW:LBM_ARPA";

const char* ATTRIBUTE_WHAT_PRODPAR		= "prodpar";
const char* ATTRIBUTE_WHAT_QUANTITY		= "quantity";
const char* ATTRIBUTE_WHAT_STARTDATE		= "startdate";
const char* ATTRIBUTE_WHAT_STARTTIME		= "starttime";
const char* ATTRIBUTE_WHAT_ENDDATE		= "enddate";
const char* ATTRIBUTE_WHAT_ENDTIME		= "endtime";
const char* ATTRIBUTE_WHAT_GAIN			= "gain";
const char* ATTRIBUTE_WHAT_OFFSET		= "offset";
const char* ATTRIBUTE_WHAT_NODATA		= "nodata";
const char* ATTRIBUTE_WHAT_UNDETECT		= "undetect";

const char* PRODUCT_QUANTITY_TH			= "TH";	
const char* PRODUCT_QUANTITY_TV			= "TV";	
const char* PRODUCT_QUANTITY_DBZH		= "DBZH";
const char* PRODUCT_QUANTITY_DBZV		= "DBZV";
const char* PRODUCT_QUANTITY_ZDR		= "ZDR"; 
const char* PRODUCT_QUANTITY_RHOHV		= "RHOHV";
const char* PRODUCT_QUANTITY_LDR		= "LDR"; 
const char* PRODUCT_QUANTITY_PHIDP		= "PHIDP"; 
const char* PRODUCT_QUANTITY_KDP		= "KDP"; 
const char* PRODUCT_QUANTITY_SQI		= "SQI"; 
const char* PRODUCT_QUANTITY_SNR		= "SNR"; 
const char* PRODUCT_QUANTITY_RATE		= "RATE";
const char* PRODUCT_QUANTITY_ACRR		= "ACRR";
const char* PRODUCT_QUANTITY_HGHT		= "HGHT";
const char* PRODUCT_QUANTITY_VIL		= "VIL"; 
const char* PRODUCT_QUANTITY_VRAD		= "VRAD"; 
const char* PRODUCT_QUANTITY_WRAD		= "WRAD"; 
const char* PRODUCT_QUANTITY_UWND		= "UWND"; 
const char* PRODUCT_QUANTITY_VWND		= "VWND"; 
const char* PRODUCT_QUANTITY_BRDR		= "BRDR"; 
const char* PRODUCT_QUANTITY_QIND		= "QIND"; 
const char* PRODUCT_QUANTITY_CLASS		= "CLASS";

const char* PRODUCT_QUANTITY_ff			= "ff";
const char* PRODUCT_QUANTITY_dd			= "dd";
const char* PRODUCT_QUANTITY_ff_dev		= "ff_dev";
const char* PRODUCT_QUANTITY_dd_dev		= "dd_dev";
const char* PRODUCT_QUANTITY_n			= "n";
const char* PRODUCT_QUANTITY_dbz		= "dbz";
const char* PRODUCT_QUANTITY_dbz_dev		= "dbz_dev";
const char* PRODUCT_QUANTITY_z			= "z";
const char* PRODUCT_QUANTITY_z_dev		= "z_dev";
const char* PRODUCT_QUANTITY_w			= "w";
const char* PRODUCT_QUANTITY_w_dev		= "w_dev";
const char* PRODUCT_QUANTITY_div		= "div";
const char* PRODUCT_QUANTITY_div_dev		= "div_dev";
const char* PRODUCT_QUANTITY_def		= "def";
const char* PRODUCT_QUANTITY_def_dev		= "def_dev";
const char* PRODUCT_QUANTITY_ad			= "ad";
const char* PRODUCT_QUANTITY_ad_dev		= "ad_dev";
const char* PRODUCT_QUANTITY_chi2		= "chi2";
const char* PRODUCT_QUANTITY_rhohv		= "rhohv";
const char* PRODUCT_QUANTITY_rhohv_dev		= "rhohv_dev";

const char* ATTRIBUTE_WHERE_LON			= "lon";
const char* ATTRIBUTE_WHERE_LAT			= "lat";
const char* ATTRIBUTE_WHERE_HEIGHT		= "height";

const char* ATTRIBUTE_WHERE_ELANGLE		= "elangle";
const char* ATTRIBUTE_WHERE_NBINS		= "nbins";
const char* ATTRIBUTE_WHERE_RSTART		= "rstart";
const char* ATTRIBUTE_WHERE_RSCALE		= "rscale";
const char* ATTRIBUTE_WHERE_NRAYS		= "nrays";
const char* ATTRIBUTE_WHERE_A1GATE		= "a1gate";

const char* ATTRIBUTE_WHERE_STARTAZ		= "startaz";
const char* ATTRIBUTE_WHERE_STOPAZ		= "stopaz";

const char* ATTRIBUTE_WHERE_PROJDEF		= "projdef";
const char* ATTRIBUTE_WHERE_XSIZE		= "xsize";
const char* ATTRIBUTE_WHERE_YSIZE		= "ysize";
const char* ATTRIBUTE_WHERE_XSCALE		= "xscale";
const char* ATTRIBUTE_WHERE_YSCALE		= "yscale";
const char* ATTRIBUTE_WHERE_LL_LON		= "LL_lon";
const char* ATTRIBUTE_WHERE_LL_LAT		= "LL_lat";
const char* ATTRIBUTE_WHERE_UL_LON		= "UL_lon";
const char* ATTRIBUTE_WHERE_UL_LAT		= "UL_lat";
const char* ATTRIBUTE_WHERE_UR_LON		= "UR_lon";
const char* ATTRIBUTE_WHERE_UR_LAT		= "UR_lat";
const char* ATTRIBUTE_WHERE_LR_LON		= "LR_lon";
const char* ATTRIBUTE_WHERE_LR_LAT		= "LR_lat";

const char* ATTRIBUTE_WHERE_MINHEIGHT		= "minheight";
const char* ATTRIBUTE_WHERE_MAXHEIGHT		= "maxheight";

const char* ATTRIBUTE_WHERE_AZ_ANGLE		= "az_angle";
const char* ATTRIBUTE_WHERE_ANGLES		= "angles";
const char* ATTRIBUTE_WHERE_RANGE		= "range";

const char* ATTRIBUTE_WHERE_START_LON		= "start_lon";
const char* ATTRIBUTE_WHERE_START_LAT		= "start_lat";
const char* ATTRIBUTE_WHERE_STOP_LON		= "stop_lon";
const char* ATTRIBUTE_WHERE_STOP_LAT		= "stop_lat";

const char* ATTRIBUTE_WHERE_LEVELS		= "levels";
const char* ATTRIBUTE_WHERE_INTERVAL		= "interval";

const char* ATTRIBUTE_HOW_TASK			= "task";
const char* ATTRIBUTE_HOW_STARTEPOCHS		= "startepochs";
const char* ATTRIBUTE_HOW_ENDEPOCHS		= "endepochs";
const char* ATTRIBUTE_HOW_SYSTEM		= "system";
const char* ATTRIBUTE_HOW_SOFTWARE		= "software";

const char* SOFTWARE_CASTOR			= "CASTOR";
const char* SOFTWARE_EDGE			= "EDGE";
const char* SOFTWARE_FROG			= "FROG";
const char* SOFTWARE_IRIS			= "IRIS";
const char* SOFTWARE_NORDRAD			= "NORDRAD";
const char* SOFTWARE_RADARNET			= "RADARNET";
const char* SOFTWARE_RAINBOW			= "RAINBOW"; 


const char* ATTRIBUTE_HOW_SW_VERSION		= "sw_version";
const char* ATTRIBUTE_HOW_ZR_A			= "zr_a";
const char* ATTRIBUTE_HOW_ZR_B			= "zr_b";
const char* ATTRIBUTE_HOW_KR_A			= "kr_a";
const char* ATTRIBUTE_HOW_KR_B			= "kr_b";
const char* ATTRIBUTE_HOW_SIMULATED		= "simulated";

const char* ATTRIBUTE_HOW_BEAMWIDTH		= "beamwidth";
const char* ATTRIBUTE_HOW_WAVELENGTH		= "wavelength";
const char* ATTRIBUTE_HOW_RPM			= "rpm";
const char* ATTRIBUTE_HOW_PULSEWIDTH		= "pulsewidth"; 
const char* ATTRIBUTE_HOW_RXBANDWIDTH		= "RXbandwidth"; 
const char* ATTRIBUTE_HOW_LOWPRF		= "lowprf"; 
const char* ATTRIBUTE_HOW_HIGHPRF		= "highprf";
const char* ATTRIBUTE_HOW_TXLOSS		= "TXloss";
const char* ATTRIBUTE_HOW_RXLOSS		= "RXloss";
const char* ATTRIBUTE_HOW_RADOMELOSS		= "radomeloss";
const char* ATTRIBUTE_HOW_ANTGAIN		= "antgain";
const char* ATTRIBUTE_HOW_BEAMWH		= "beamwH";
const char* ATTRIBUTE_HOW_BEAMWV		= "beamwV";
const char* ATTRIBUTE_HOW_GASATTN		= "gasattn";
const char* ATTRIBUTE_HOW_RADCONSTH		= "radconstH";
const char* ATTRIBUTE_HOW_RADCONSTV		= "radconstV";
const char* ATTRIBUTE_HOW_NOMTXPOWER		= "nomTXpower";
const char* ATTRIBUTE_HOW_TXPOWER		= "TXpower";
const char* ATTRIBUTE_HOW_NI      		= "NI";
const char* ATTRIBUTE_HOW_VSAMPLES		= "Vsamples";

const char* ATTRIBUTE_HOW_AZMETHOD		= "azmethod";
const char* ATTRIBUTE_HOW_BINMETHOD		= "binmethod";

const char* METHOD_NEAREST			= "NEAREST";
const char* METHOD_INTERPOL			= "INTERPOL";
const char* METHOD_AVERAGE			= "AVERAGE";
const char* METHOD_RANDOM			= "RANDOM";
const char* METHOD_MDE				= "MDE";
const char* METHOD_LATEST			= "LATEST";
const char* METHOD_MAXIMUM			= "MAXIMUM";
const char* METHOD_DOMAIN			= "DOMAIN";
const char* METHOD_VAD				= "VAD";
const char* METHOD_VVP				= "VVP";
const char* METHOD_RGA				= "RGA";



//const char* ATTRIBUTE_HOW_AZANGLES		= "azangles";         removed in ODIMh5 v2.1
const char* ATTRIBUTE_HOW_ELANGLES		= "elangles";

const char* ATTRIBUTE_HOW_STARTAZA		= "startazA";
const char* ATTRIBUTE_HOW_STOPAZA		= "stopazA";
const char* ATTRIBUTE_HOW_STARTAZT		= "startazT";
const char* ATTRIBUTE_HOW_STOPAZT		= "stopazT";

//const char* ATTRIBUTE_HOW_AZTIMES		= "aztimes";       removed in ODIMh5 v2.1

const char* ATTRIBUTE_HOW_ANGLES		= "angles"; 
const char* ATTRIBUTE_HOW_AROTATION		= "arotation"; 
const char* ATTRIBUTE_HOW_CAMETHOD		= "camethod"; 
const char* ATTRIBUTE_HOW_NODES			= "nodes"; 
const char* ATTRIBUTE_HOW_ACCNUM		= "accnum"; 

const char* ATTRIBUTE_HOW_MINRANGE		= "minrange"; 
const char* ATTRIBUTE_HOW_MAXRANGE		= "maxrange"; 
//const char* ATTRIBUTE_HOW_NI 			= "NI";        removed in ODIMh5 v2.1
const char* ATTRIBUTE_HOW_DEALIASED		= "dealiased"; 

const char* ATTRIBUTE_HOW_POINTACCEL		= "pointaccEL"; 
const char* ATTRIBUTE_HOW_POINTACCAZ		= "pointaccAZ";  
const char* ATTRIBUTE_HOW_MALFUNC		= "malfunc";  
const char* ATTRIBUTE_HOW_RADAR_MSG		= "radar_msg"; 
const char* ATTRIBUTE_HOW_RADHORIZ		= "radhoriz"; 
//const char* ATTRIBUTE_HOW_MDS			= "MDS";        removed in ODIMh5 v2.1
const char* ATTRIBUTE_HOW_NEZ			= "NEZ";
const char* ATTRIBUTE_HOW_OUR			= "OUR"; 
const char* ATTRIBUTE_HOW_DCLUTTER		= "Dclutter"; 
const char* ATTRIBUTE_HOW_COMMENT		= "comment"; 
const char* ATTRIBUTE_HOW_SQI			= "SQI"; 
const char* ATTRIBUTE_HOW_CSR			= "CSR"; 
const char* ATTRIBUTE_HOW_LOG			= "LOG"; 
const char* ATTRIBUTE_HOW_VPRCORR		= "VPRCorr"; 
const char* ATTRIBUTE_HOW_FREEZE		= "freeze"; 
const char* ATTRIBUTE_HOW_MIN			= "min"; 
const char* ATTRIBUTE_HOW_MAX			= "max"; 
const char* ATTRIBUTE_HOW_STEP			= "step"; 
const char* ATTRIBUTE_HOW_LEVELS		= "levels";  
const char* ATTRIBUTE_HOW_PEAKPWR		= "peakpwr"; 
const char* ATTRIBUTE_HOW_AVGPWR		= "avgpwr"; 
const char* ATTRIBUTE_HOW_DYNRANGE		= "dynrange"; 
const char* ATTRIBUTE_HOW_RAC			= "RAC"; 
const char* ATTRIBUTE_HOW_BBC			= "BBC"; 
const char* ATTRIBUTE_HOW_PAC			= "PAC"; 
const char* ATTRIBUTE_HOW_S2N			= "S2N"; 
const char* ATTRIBUTE_HOW_POLARIZATION		= "polarization"; 

const char* POLARIZATION_H			= "H";
const char* POLARIZATION_V			= "V";


const char* ATTRIBUTE_CLASS			= "CLASS";
const char* CLASS_IMAGE				= "IMAGE";

const char* ATTRIBUTE_IMAGE_VERSION		= "IMAGE_VERSION";
const char* IMAGE_VERSION_1_2			= "1.2";

const char* ATTRIBUTE_PAL_VERSION		= "PAL_VERSION";

const char* TRUESTR				= "True";
const char* FALSESTR				= "False";


/*===========================================================================*/

bool Specification::isObject(const std::string& value)
{
	return	(value == OBJECT_PVOL) ||
		(value == OBJECT_CVOL) ||
		(value == OBJECT_SCAN) ||
		(value == OBJECT_RAY) ||
		(value == OBJECT_AZIM) ||
		(value == OBJECT_IMAGE) ||
		(value == OBJECT_COMP) ||
		(value == OBJECT_XSEC) ||
		(value == OBJECT_VP) ||
		(value == OBJECT_PIC);
}

bool Specification::isSoftware(const std::string& value)
{
	return	(value == SOFTWARE_CASTOR) ||
		(value == SOFTWARE_EDGE) ||	
		(value == SOFTWARE_FROG) ||	
		(value == SOFTWARE_IRIS) ||	
		(value == SOFTWARE_NORDRAD) ||	
		(value == SOFTWARE_RADARNET) ||	
		(value == SOFTWARE_RAINBOW);
}

bool Specification::isMethod(const std::string& value)
{
	return	(value == METHOD_NEAREST) ||
		(value == METHOD_INTERPOL) ||
		(value == METHOD_AVERAGE) ||
		(value == METHOD_RANDOM) ||
		(value == METHOD_MDE) ||
		(value == METHOD_LATEST) ||
		(value == METHOD_MAXIMUM) ||
		(value == METHOD_DOMAIN) ||
		(value == METHOD_VAD) ||
		(value == METHOD_VVP) ||
		(value == METHOD_RGA);
}

bool Specification::isPolarization(const std::string& value)
{
	return	(value == POLARIZATION_H) ||
		(value == POLARIZATION_V);
}

void Specification::getStandardAttributes(std::set<std::string>& names)
{
	names.insert(ATTRIBUTE_ROOT_CONVENTIONS		); //Conventions";
	names.insert(ATTRIBUTE_WHAT_OBJECT		); //object";
	names.insert(ATTRIBUTE_WHAT_VERSION		); //version";
	names.insert(ATTRIBUTE_WHAT_DATE			); //date";
	names.insert(ATTRIBUTE_WHAT_TIME			); //time";
	names.insert(ATTRIBUTE_WHAT_SOURCE		); //source";
	names.insert(ATTRIBUTE_WHAT_PRODUCT		); //product";
	names.insert(ATTRIBUTE_WHAT_PRODPAR		); //prodpar";
	names.insert(ATTRIBUTE_WHAT_QUANTITY		); //quantity";
	names.insert(ATTRIBUTE_WHAT_STARTDATE		); //startdate";
	names.insert(ATTRIBUTE_WHAT_STARTTIME		); //starttime";
	names.insert(ATTRIBUTE_WHAT_ENDDATE		); //enddate";
	names.insert(ATTRIBUTE_WHAT_ENDTIME		); //endtime";
	names.insert(ATTRIBUTE_WHAT_GAIN			); //gain";
	names.insert(ATTRIBUTE_WHAT_OFFSET		); //offset";
	names.insert(ATTRIBUTE_WHAT_NODATA		); //nodata";
	names.insert(ATTRIBUTE_WHAT_UNDETECT		); //undetect";

	names.insert(ATTRIBUTE_WHERE_LON			); //lon";
	names.insert(ATTRIBUTE_WHERE_LAT			); //lat";
	names.insert(ATTRIBUTE_WHERE_HEIGHT		); //height";

	names.insert(ATTRIBUTE_WHERE_ELANGLE		); //elangle";
	names.insert(ATTRIBUTE_WHERE_NBINS		); //nbins";
	names.insert(ATTRIBUTE_WHERE_RSTART		); //rstart";
	names.insert(ATTRIBUTE_WHERE_RSCALE		); //rscale";
	names.insert(ATTRIBUTE_WHERE_NRAYS		); //nrays";
	names.insert(ATTRIBUTE_WHERE_A1GATE		); //a1gate";

	names.insert(ATTRIBUTE_WHERE_STARTAZ		); //startaz";
	names.insert(ATTRIBUTE_WHERE_STOPAZ		); //stopaz";

	names.insert(ATTRIBUTE_WHERE_PROJDEF		); //projdef";
	names.insert(ATTRIBUTE_WHERE_XSIZE		); //xsize";
	names.insert(ATTRIBUTE_WHERE_YSIZE		); //ysize";
	names.insert(ATTRIBUTE_WHERE_XSCALE		); //xscale";
	names.insert(ATTRIBUTE_WHERE_YSCALE		); //yscale";
	names.insert(ATTRIBUTE_WHERE_LL_LON		); //ll_lon";
	names.insert(ATTRIBUTE_WHERE_LL_LAT		); //ll_lat";
	names.insert(ATTRIBUTE_WHERE_UL_LON		); //ul_lon";
	names.insert(ATTRIBUTE_WHERE_UL_LAT		); //ul_lat";
	names.insert(ATTRIBUTE_WHERE_UR_LON		); //ur_lon";
	names.insert(ATTRIBUTE_WHERE_UR_LAT		); //ur_lat";
	names.insert(ATTRIBUTE_WHERE_LR_LON		); //lr_lon";
	names.insert(ATTRIBUTE_WHERE_LR_LAT		); //lr_lat";

	names.insert(ATTRIBUTE_WHERE_MINHEIGHT		); //minheight";
	names.insert(ATTRIBUTE_WHERE_MAXHEIGHT		); //maxheight";

	names.insert(ATTRIBUTE_WHERE_AZ_ANGLE		); //az_angle";
	names.insert(ATTRIBUTE_WHERE_ANGLES		); //angles";
	names.insert(ATTRIBUTE_WHERE_RANGE		); //range";

	names.insert(ATTRIBUTE_WHERE_START_LON		); //start_lon";
	names.insert(ATTRIBUTE_WHERE_START_LAT		); //start_lat";
	names.insert(ATTRIBUTE_WHERE_STOP_LON		); //stop_lon";
	names.insert(ATTRIBUTE_WHERE_STOP_LAT		); //stop_lat";

	names.insert(ATTRIBUTE_WHERE_LEVELS		); //levels";
	names.insert(ATTRIBUTE_WHERE_INTERVAL		); //interval";

	names.insert(ATTRIBUTE_HOW_TASK			); //task";
	names.insert(ATTRIBUTE_HOW_STARTEPOCHS		); //startepochs";
	names.insert(ATTRIBUTE_HOW_ENDEPOCHS		); //endepochs";
	names.insert(ATTRIBUTE_HOW_SYSTEM		); //system";
	names.insert(ATTRIBUTE_HOW_SOFTWARE		); //software";

	names.insert(ATTRIBUTE_HOW_SW_VERSION		); //sw_version";
	names.insert(ATTRIBUTE_HOW_ZR_A			); //zr_a";
	names.insert(ATTRIBUTE_HOW_ZR_B			); //zr_b";
	names.insert(ATTRIBUTE_HOW_KR_A			); //kr_a";
	names.insert(ATTRIBUTE_HOW_KR_B			); //kr_b";
	names.insert(ATTRIBUTE_HOW_SIMULATED		); //simulated";

	names.insert(ATTRIBUTE_HOW_BEAMWIDTH		); //beamwidth";
	names.insert(ATTRIBUTE_HOW_WAVELENGTH		); //wavelength";
	names.insert(ATTRIBUTE_HOW_RPM			); //rpm";
	names.insert(ATTRIBUTE_HOW_PULSEWIDTH		); //pulsewidth"; 
	names.insert(ATTRIBUTE_HOW_LOWPRF		); //lowprf"; 
	names.insert(ATTRIBUTE_HOW_HIGHPRF		); //highprf";

	names.insert(ATTRIBUTE_HOW_AZMETHOD		); //azmethod";
	names.insert(ATTRIBUTE_HOW_BINMETHOD		); //binmethod";

//	names.insert(ATTRIBUTE_HOW_AZANGLES		); //azangles";
	names.insert(ATTRIBUTE_HOW_ELANGLES		); //elangles";

//	names.insert(ATTRIBUTE_HOW_AZTIMES		); //aztimes";

	names.insert(ATTRIBUTE_HOW_ANGLES		); //angles"; 
	names.insert(ATTRIBUTE_HOW_AROTATION		); //arotation"; 
	names.insert(ATTRIBUTE_HOW_CAMETHOD		); //camethod"; 
	names.insert(ATTRIBUTE_HOW_NODES			); //nodes"; 
	names.insert(ATTRIBUTE_HOW_ACCNUM		); //accnum"; 

	names.insert(ATTRIBUTE_HOW_MINRANGE		); //minrange"; 
	names.insert(ATTRIBUTE_HOW_MAXRANGE		); //maxrange"; 
	names.insert(ATTRIBUTE_HOW_NI 			); //NI"; 
	names.insert(ATTRIBUTE_HOW_DEALIASED		); //dealiased"; 

	names.insert(ATTRIBUTE_HOW_POINTACCEL		); //pointaccEL"; 
	names.insert(ATTRIBUTE_HOW_POINTACCAZ		); //pointaccAZ";  
	names.insert(ATTRIBUTE_HOW_MALFUNC		); //malfunc";  
	names.insert(ATTRIBUTE_HOW_RADAR_MSG		); //radar_msg"; 
	names.insert(ATTRIBUTE_HOW_RADHORIZ		); //radhoriz"; 
//	names.insert(ATTRIBUTE_HOW_MDS			); //MDS"; 
	names.insert(ATTRIBUTE_HOW_NEZ			); //NEZ"; 
	names.insert(ATTRIBUTE_HOW_OUR			); //OUR"; 
	names.insert(ATTRIBUTE_HOW_DCLUTTER		); //Dclutter"; 
	names.insert(ATTRIBUTE_HOW_COMMENT		); //comment"; 
	names.insert(ATTRIBUTE_HOW_SQI			); //SQI"; 
	names.insert(ATTRIBUTE_HOW_CSR			); //CSR"; 
	names.insert(ATTRIBUTE_HOW_LOG			); //LOG"; 
	names.insert(ATTRIBUTE_HOW_VPRCORR		); //VPRCorr"; 
	names.insert(ATTRIBUTE_HOW_FREEZE		); //freeze"; 
	names.insert(ATTRIBUTE_HOW_MIN			); //min"; 
	names.insert(ATTRIBUTE_HOW_MAX			); //max"; 
	names.insert(ATTRIBUTE_HOW_STEP			); //step"; 
	names.insert(ATTRIBUTE_HOW_LEVELS		); //levels";  
	names.insert(ATTRIBUTE_HOW_PEAKPWR		); //peakpwr"; 
	names.insert(ATTRIBUTE_HOW_AVGPWR		); //avgpwr"; 
	names.insert(ATTRIBUTE_HOW_DYNRANGE		); //dynrange"; 
	names.insert(ATTRIBUTE_HOW_RAC			); //RAC"; 
	names.insert(ATTRIBUTE_HOW_BBC			); //BBC"; 
	names.insert(ATTRIBUTE_HOW_PAC			); //PAC"; 
	names.insert(ATTRIBUTE_HOW_S2N			); //S2N"; 
	names.insert(ATTRIBUTE_HOW_POLARIZATION		); //polarization"; 

	names.insert(ATTRIBUTE_CLASS			); //CLASS";
	names.insert(ATTRIBUTE_IMAGE_VERSION		); //IMAGE_VERSION";
	names.insert(ATTRIBUTE_PAL_VERSION		); //PAL_VERSION";


}

void Specification::getStandardQuantities(std::set<std::string>& names)
{
	names.insert(PRODUCT_QUANTITY_TH			); //TH";	
	names.insert(PRODUCT_QUANTITY_TV			); //TV";	
	names.insert(PRODUCT_QUANTITY_DBZH		); //DBZH";
	names.insert(PRODUCT_QUANTITY_DBZV		); //DBZV";
	names.insert(PRODUCT_QUANTITY_ZDR		); //ZDR"; 
	names.insert(PRODUCT_QUANTITY_RHOHV		); //RHOHV";
	names.insert(PRODUCT_QUANTITY_LDR		); //LDR"; 
	names.insert(PRODUCT_QUANTITY_PHIDP		); //PHIDP"; 
	names.insert(PRODUCT_QUANTITY_KDP		); //KDP"; 
	names.insert(PRODUCT_QUANTITY_SQI		); //SQI"; 
	names.insert(PRODUCT_QUANTITY_SNR		); //SNR"; 
	names.insert(PRODUCT_QUANTITY_RATE		); //RATE";
	names.insert(PRODUCT_QUANTITY_ACRR		); //ACRR";
	names.insert(PRODUCT_QUANTITY_HGHT		); //HGHT";
	names.insert(PRODUCT_QUANTITY_VIL		); //VIL"; 
	names.insert(PRODUCT_QUANTITY_VRAD		); //VRAD"; 
	names.insert(PRODUCT_QUANTITY_WRAD		); //WRAD"; 
	names.insert(PRODUCT_QUANTITY_UWND		); //UWND"; 
	names.insert(PRODUCT_QUANTITY_VWND		); //VWND"; 
	names.insert(PRODUCT_QUANTITY_BRDR		); //BRDR"; 
	names.insert(PRODUCT_QUANTITY_QIND		); //QIND"; 
	names.insert(PRODUCT_QUANTITY_CLASS		); //CLASS";

	names.insert(PRODUCT_QUANTITY_ff			); //ff";
	names.insert(PRODUCT_QUANTITY_dd			); //dd";
	names.insert(PRODUCT_QUANTITY_ff_dev		); //ff_dev";
	names.insert(PRODUCT_QUANTITY_dd_dev		); //dd_dev";
	names.insert(PRODUCT_QUANTITY_n			); //n";
	names.insert(PRODUCT_QUANTITY_dbz		); //dbz";
	names.insert(PRODUCT_QUANTITY_dbz_dev		); //dbz_dev";
	names.insert(PRODUCT_QUANTITY_z			); //z";
	names.insert(PRODUCT_QUANTITY_z_dev		); //z_dev";
	names.insert(PRODUCT_QUANTITY_w			); //w";
	names.insert(PRODUCT_QUANTITY_w_dev		); //w_dev";
	names.insert(PRODUCT_QUANTITY_div		); //div";
	names.insert(PRODUCT_QUANTITY_div_dev		); //div_dev";
	names.insert(PRODUCT_QUANTITY_def		); //def";
	names.insert(PRODUCT_QUANTITY_def_dev		); //def_dev";
	names.insert(PRODUCT_QUANTITY_ad			); //ad";
	names.insert(PRODUCT_QUANTITY_ad_dev		); //ad_dev";
	names.insert(PRODUCT_QUANTITY_chi2		); //chi2";
	names.insert(PRODUCT_QUANTITY_rhohv		); //rhohv";
	names.insert(PRODUCT_QUANTITY_rhohv_dev		); //rhohv_dev";

}

/*===========================================================================*/

}
