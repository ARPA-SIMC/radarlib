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

#include <radarlib/odimh5v20_arpav10_classes.hpp>

#include <radarlib/debug.hpp>

namespace ArpaER { namespace OdimH5v20 {

/*===========================================================================*/
/* ARPA CONVENTIONS */
/*===========================================================================*/

const char* ATTRIBUTE_WHAT_ARPAER_CONVENTIONS           = "NEW:ArpaErConventions";

const char* CONVENTIONS_ODIM_H5_V2_0_ARPA_V0_1          = "ODIM_H5/V2_0 ARPA/V0_1";
const char* CONVENTIONS_ODIM_H5_V2_0_ARPA_V1_0          = "ODIM_H5/V2_0 ARPA/V1_0";

/*===========================================================================*/
/* ORIGINAL FORMAT IDENTIFICATION */
/*===========================================================================*/

const char* ATTRIBUTE_WHAT_ARPAER_ORIGINALFILE          = "NEW:arpaer.originalfile";

const char* ATTRIBUTE_WHAT_ARPAER_ORIGINALFORMAT        = "NEW:arpaer.originalformat";

const char* ORIGINALFORMAT_VME				= "VME";
const char* ORIGINALFORMAT_SP20                         = "SP20";
const char* ORIGINALFORMAT_MDB2				= "MDB2";

/*===========================================================================*/
/* SOFTWARE ELABORATION INFORMATIONS */
/*===========================================================================*/

const char* ATTRIBUTE_WHAT_ARPAER_ORIGINALFORMATCONVERTER	= "NEW:arpaer.originalformatconverter";

const char* ATTRIBUTE_HOW_ARPAER_ELABORATIONS		= "NEW:arpaer.elaborations";

/*===========================================================================*/
/* VME FORMAT INFORMATIONS */
/*===========================================================================*/

const char* ATTRIBUTE_HOW_ARPAER_VMEVOLXML              = "NEW:arpaer.vmevolxml";
const char* ATTRIBUTE_HOW_ARPAER_VMEVOLSTATUS		= "NEW:arpaer.vmevolstatus";

const char* ATTRIBUTE_HOW_ARPAER_VMESWEEPXML		= "NEW:arpaer.vmesweepxml";
const char* ATTRIBUTE_HOW_ARPAER_VMESWEEPCOMPRESSION	= "NEW:arpaer.vmesweepcompression";
const char* ATTRIBUTE_HOW_ARPAER_VMEREALNUMBINS         = "NEW:arpaer_vmerealnumbins";
const char* ATTRIBUTE_HOW_ARPAER_VMERAYDATAFLAGS        = "NEW:arpaer.vmeraydataflags";
const char* ATTRIBUTE_HOW_ARPAER_VMERAYNUMPULSES        = "NEW:arpaer.vmeraynumpulses";
const char* ATTRIBUTE_HOW_ARPAER_VMERAYTXPOWS           = "NEW:arpaer_vmeraytxpows";
const char* ATTRIBUTE_HOW_ARPAER_VMERAYELANGLES         = "NEW:arpaer_vmerayelangles";
const char* ATTRIBUTE_HOW_ARPAER_VMERAYFAKE		= "NEW:arpaer_vmerayfake";
const char* ATTRIBUTE_HOW_ARPAER_VMEDISCARDEDRAYS       = "NEW:arpaer_vmediscardedrays";

const char* PRODUCT_QUANTITY_VMESTAT1                   = "NEW:ARPAER-VMESTAT1"; 

/*===========================================================================*/
/* SP20 FORMAT INFORMATIONS */
/*===========================================================================*/

const char* ATTRIBUTE_HOW_ARPAER_SP20VOLHEADER          = "NEW:arpaer_sp20volheader";

const char* ATTRIBUTE_HOW_ARPAER_SP20RAYHEADERS         = "NEW:arpaer_sp20rayheaders";
const char* ATTRIBUTE_HOW_ARPAER_SP20RAYVALIDITY        = "NEW:arpaer_sp20rayvalidity";
const char* ATTRIBUTE_HOW_ARPAER_SP20RAYFAKE            = "NEW:arpaer_sp20rayfake";
const char* ATTRIBUTE_HOW_ARPAER_SP20FAKESCAN           = "NEW:arpaer_sp20fakescan";
const char* ATTRIBUTE_HOW_ARPAER_SP20DISCARDEDRAYS      = "NEW:arpaer_sp20discardedrays";

/*===========================================================================*/
/* MDB2 FORMAT INFORMATIONS */
/*===========================================================================*/

const char* ATTRIBUTE_HOW_ARPAER_MDB2VOLHEADER          = "NEW:arpaer_mdb2volheader";

const char* ATTRIBUTE_HOW_ARPAER_MDB2DISCARDEDRAYS      = "NEW:arpaer_mdb2discardedrays";
const char* ATTRIBUTE_HOW_ARPAER_MDB2RAYAZIMUTH         = "NEW:arpaer_mdb2rayazimuth";
const char* ATTRIBUTE_HOW_ARPAER_MDB2RAYFAKE            = "NEW:arpaer_mdb2rayfake";

const char* ATTRIBUTE_HOW_ARPAER_MDB2RAYBINS            = "NEW:arpaer_mdb2raybins";



/*===========================================================================*/

bool Specification::isMethod(const std::string& value)
{
	return ::OdimH5v20::Specification::isMethod(value);
}

bool Specification::isPolarization(const std::string& value)
{
	return ::OdimH5v20::Specification::isPolarization(value);
}

/*===========================================================================*/

} }





























