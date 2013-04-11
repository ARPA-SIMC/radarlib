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
 *  \brief ArpaER specific definitions and extensions 
 *  This module include global contants and definitions introduced
 *  by Arpa E.R. as non-standard exstension
 *  The attributes names defined in this module where introduced to
 *  support Arpa E.R. conversion from previous formats: MDB2, SP20, ELDES 
 */

#ifndef __RADAR_ODIMH5V21_ARPAV10_CLASES_HPP__
#define __RADAR_ODIMH5V21_ARPAV10_CLASES_HPP__

#include <radarlib/defs.h>
#include <radarlib/odimh5v21_factory.hpp>

namespace ArpaER { namespace OdimH5v21 {

/*===========================================================================*/
/* ARPA CONVENTIONS */
/*===========================================================================*/

/* Arpa E.R. convetions attribute (STRING) */
/* used in combination with OdimH5 "/conventions" attribute */
extern RADAR_API const char* ATTRIBUTE_WHAT_ARPAER_CONVENTIONS;		

/* Arpa E.R. conventions values*/ 
/* From now on, if the following attributes change, a new convention constant must be added to this list */ 
extern RADAR_API const char* CONVENTIONS_ODIM_H5_V2_1_ARPA_V0_1;
extern RADAR_API const char* CONVENTIONS_ODIM_H5_V2_1_ARPA_V1_0;

/*===========================================================================*/
/* ORIGINAL FORMAT IDENTIFICATION */
/*===========================================================================*/

/* Original volume file name attribute (STRING) */
/* Store informations about the original file name */
extern RADAR_API const char* ATTRIBUTE_WHAT_ARPAER_ORIGINALFILE;	

/* Original volume format attribute (STRING) */
/* Identify the original format of the volume */
extern RADAR_API const char* ATTRIBUTE_WHAT_ARPAER_ORIGINALFORMAT;	

/* original volume format values (new values can be appended to this list)*/
extern RADAR_API const char* ORIGINALFORMAT_VME;
extern RADAR_API const char* ORIGINALFORMAT_SP20;
extern RADAR_API const char* ORIGINALFORMAT_MDB2;

/*===========================================================================*/
/* SOFTWARE ELABORATION INFORMATIONS */
/*===========================================================================*/

/* Arpa conversion software attribute (STRING) */
/* This attribute is used to identify the software and version used for the conversion from the original format to OdimH5 */
/* After few years it could be difficult to remember the software used for the conversion */
extern RADAR_API const char* ATTRIBUTE_WHAT_ARPAER_ORIGINALFORMATCONVERTER;		

/* Arpa E.R. generic elaborations attribute (SEQUENCE OF STRINGS) */
/* A common attribute for future use that allows users to store informations about the elaborations applied to the volume */
/* Any elaboration description should be appended to the current value */
extern RADAR_API const char* ATTRIBUTE_HOW_ARPAER_ELABORATIONS;		

/*===========================================================================*/
/* VME FORMAT INFORMATIONS */
/*===========================================================================*/

/* --- Volume level attributes --- */

/* volume header (XML STRING) */
extern RADAR_API const char* ATTRIBUTE_HOW_ARPAER_VMEVOLXML;		

/* xml VOL/status element value (STRING) */
extern RADAR_API const char* ATTRIBUTE_HOW_ARPAER_VMEVOLSTATUS;		

/* --- dataset level attributes --- */

/* xml SWEEP element (STRING) */
extern RADAR_API const char* ATTRIBUTE_HOW_ARPAER_VMESWEEPXML;		

/* compression used (INT) */
extern RADAR_API const char* ATTRIBUTE_HOW_ARPAER_VMESWEEPCOMPRESSION;

/* original number of bins in rays (there is a bug so nominal bins can be more than real bins) */
extern RADAR_API const char* ATTRIBUTE_HOW_ARPAER_VMEREALNUMBINS;	

/* original rays data flags (SEQUENCE OF HEX STRINGS) */
extern RADAR_API const char* ATTRIBUTE_HOW_ARPAER_VMERAYDATAFLAGS;	

/* original rays num pulses (SEQUENCE OF INTEGERS AS STRING) */
extern RADAR_API const char* ATTRIBUTE_HOW_ARPAER_VMERAYNUMPULSES;	

/* original rays tx_pow (SEQUENCE OF DOUBLE AS STRING) */
extern RADAR_API const char* ATTRIBUTE_HOW_ARPAER_VMERAYTXPOWS;		

/* original rays elevation angles (SEQUENCE OF DOUBLE AS STRING) */
extern RADAR_API const char* ATTRIBUTE_HOW_ARPAER_VMERAYELANGLES;	

/* original discarted rays (SERIALIZED RAYS ENCODED AS BASE64 STRING) */
/* See conveters documentation for further details */
extern RADAR_API const char* ATTRIBUTE_HOW_ARPAER_VMEDISCARDEDRAYS;	

/* says if a ray is a fake ray created by the converter (SEQUENCE OF BOOLS AS STRING)*/
extern RADAR_API const char* ATTRIBUTE_HOW_ARPAER_VMERAYFAKE;		

/* non starndard odimh5 quantity, created for VME values */
extern RADAR_API const char* PRODUCT_QUANTITY_VMESTAT1;			

//tern RADAR_API const char* ATTRIBUTE_HOW_ARPAER_VMESURPLUSRAYS;	/* sequence, VME original surplus rays */

/*===========================================================================*/
/* SP20 FORMAT INFORMATIONS */
/*===========================================================================*/

/* --- volume level attributes --- */

/* volume header (binary header serialized and BASE64 encoded) */
extern RADAR_API const char* ATTRIBUTE_HOW_ARPAER_SP20VOLHEADER;	

/* --- dataset level attributes --- */

/* original SP20 ray headers (BASE64 STRING) */
/* Headers are serialized as a one big buffer */
extern RADAR_API const char* ATTRIBUTE_HOW_ARPAER_SP20RAYHEADERS;	

/* SP20 rays validity flag (SEQUENCE OF BOOLS AS STRING) */
extern RADAR_API const char* ATTRIBUTE_HOW_ARPAER_SP20RAYVALIDITY;	

/* says if a ray is a fake ray created by the converter (SEQUENCE OF BOOLS AS STRING */
extern RADAR_API const char* ATTRIBUTE_HOW_ARPAER_SP20RAYFAKE;		

/* original discarted rays (SERIALIZED RAYS ENCODED AS BASE64 STRING) */
/* See conveters documentation for further details */
extern RADAR_API const char* ATTRIBUTE_HOW_ARPAER_SP20DISCARDEDRAYS;	

/*===========================================================================*/
/* MDB2 FORMAT INFORMATIONS */
/*===========================================================================*/

/* --- volume level attributes --- */

/* original MDB2 vol header, base64 encoded */
extern RADAR_API const char* ATTRIBUTE_HOW_ARPAER_MDB2VOLHEADER;	

/* --- dataset level attributes --- */

/* original ray azimuth (SEQUENCE OF INT AS STRING)*/
extern RADAR_API const char* ATTRIBUTE_HOW_ARPAER_MDB2RAYAZIMUTH;	

/* says if a ray is a fake ray created by the converter (SEQUENCE OF BOOLS) */
extern RADAR_API const char* ATTRIBUTE_HOW_ARPAER_MDB2RAYFAKE;		

/* original discarted rays (SERIALIZED RAYS ENCODED AS BASE64 STRING) */
/* See conveters documentation for further details */
extern RADAR_API const char* ATTRIBUTE_HOW_ARPAER_MDB2DISCARDEDRAYS;	

/* --- data level attributes --- */

/* the original num bins for each ray in the quantity matrix (SEQUENCE OF INT AS STRING)*/
extern RADAR_API const char* ATTRIBUTE_HOW_ARPAER_MDB2RAYBINS;		

/*===========================================================================*/

class RADAR_API Specification
{
public:
	static bool isMethod(const std::string& value);	
	static bool isPolarization(const std::string& value);	
};

/*===========================================================================*/

} }

#endif

























