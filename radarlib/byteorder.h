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
 *  \brief Internal macro definitions about system byteorder detection
 */ 

#ifndef __RADAR_BYTEORDER_H__
#define __RADAR_BYTEORDER_H__

/*===========================================================================*/
/* DETECT SYSTEM BYTE ORDER */
/*===========================================================================*/

#ifndef WORDS_BIGENDIAN

	#if  defined(__i386__) || defined(__ia64__) || defined(WIN32) || \
	    (defined(__alpha__) || defined(__alpha)) || \
	     defined(__arm__) || \
	    (defined(__mips__) && defined(__MIPSEL__)) || \
	     defined(__SYMBIAN32__) || \
	     defined(__x86_64__) || \
	     defined(__LITTLE_ENDIAN__)
		/* little endian */
	#else
		#define WORDS_BIGENDIAN	1
	#endif

#endif

/*===========================================================================*/

#endif 
