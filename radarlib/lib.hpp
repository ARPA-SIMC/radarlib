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
 *  \brief Functions and classes to handle library informations
 */ 

#ifndef __RADARLIB_LIB_H__
#define __RADARLIB_LIB_H__

#include <radarlib/defs.h>

/*===========================================================================*/
/* CURRENT VERSION */
/*===========================================================================*/

/* current library version values */
#define RADARLIB_MAJOR 		1
#define RADARLIB_MINOR 		4
#define RADARLIB_BUILD 		0

/* macro to convert values into a single integer value */
#define RADARLIB_MAKEVERSION(a,b,c)		((a)*10000 + (b)*100 + (c))

/* currrent library version value */
#define RADARLIB_CURRENT_VERSION	    RADARLIB_MAKEVERSION(RADARLIB_MAJOR,RADARLIB_MINOR,RADARLIB_BUILD)

/*===========================================================================*/
/* RADARLIB CLASS */
/*===========================================================================*/

namespace Radar {

/*! 
 * \brief Library Class
 * 
 * This class allow to perform some operations at library level, such as
 * getting the version number etc.
 */
class RADAR_API RadarLibrary
{
public: 
	/*! 
	 * \brief Get Library Version
	 * 
	 * Return the library version as an integer number calculated as follow:
	 * numer = major version * 10000 + minor version * 100 + BUILD
	 * (This is the C++ method to get the library version)
	 */
	static int getVersion(void);

	/*! 
	 * \brief Check the library version
	 * 
	 * Throw an exception if the linked library is older than the
	 * version used to compile the program.	 */
	static void checkVersion()
	{
		checkVersion(RADARLIB_CURRENT_VERSION);
	}

private:
	static void checkVersion(int clientVersion);
	static void throwVersionError(int clientVersion);
};

}

/*===========================================================================*/
/* C BINDING */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*! 
 * \brief Get Library Version
 * 
 * Return the library version as an integer number calculated as follow:
 * numer = major version * 10000 + minor version * 100 + BUILD
 * (This is the ANSI C method to get the library version)
 */
RADAR_API int radarlib_get_version(void);

#ifdef __cplusplus
}
#endif

/*===========================================================================*/


#endif















