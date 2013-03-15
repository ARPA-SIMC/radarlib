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
 *  \brief Internal library macros 
 */

#ifndef __RADAR_DEFS_H__
#define __RADAR_DEFS_H__

/*===========================================================================*/
/* MACROS USED BY THE LIBRARY TO DECLARE SHARED/EXPORTABLE SYMBOLS */
/*===========================================================================*/

/* disable Visual C++ warnings */
#ifdef _MSC_VER
#ifndef _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_DEPRECATE
#endif
#endif

/* handle different library compilations */
#ifdef _MSC_VER

    #if defined(__BUILDRADARLIB__)
    #define RADAR_API       __declspec(dllexport)
    #define RADAR_APIVAR	extern __declspec(dllexport)
    #else
    #define RADAR_API		__declspec(dllimport)
    #define RADAR_APIVAR	extern __declspec(dllimport)
    #endif

#else

    #define RADAR_API		
    #define RADAR_APIVAR	extern

#endif

/*===========================================================================*/

#endif 























