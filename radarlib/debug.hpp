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
 *  \brief Macros and functions useful for debug operations
 */

#ifndef __RADAR_DEBUG_HPP__
#define __RADAR_DEBUG_HPP__

#include <iostream>
#include <cstdio>
#include <string>
#include <iomanip>
#include <limits>

#include <radarlib/defs.h>

/*=============================================================================*/
/* INTERNAL MACROS USED FOR DEBUGGING */
/* TO ENABLE THEESE MACROS CODE YOU MUST COMPILE WITH -D_DEBUG */
/*=============================================================================*/

#ifdef _DEBUG

    #define DEBUG(values)		do {             std::cout.setf(std::ios::fixed); std::cout << "DEBUG: " << values << std::endl;   } while (0)
    #define DEBUGIF(cond,values)	do { if (cond) { std::cout.setf(std::ios::fixed); std::cout << "DEBUG: " << values << std::endl; } } while (0)

    #define DEBUG_WAIT		{ getchar(); }
    #define DEBUG_HERE		{ std::cout << "DEBUG: " << __FUNCTION__ << std::endl; }
    #define DEBUG_BEEP		{ putc(7, stdout); }

    #define DEBUG_ASSERT(cond)	do { bool res = cond; if (!res) { DEBUG("ASSERT FAILED: " << #cond << "\t("<< __FILE__ << ":" << __FUNCTION__ << ")");	DEBUG_BEEP; DEBUG_WAIT;	} } while (0)

    #define DEBUG_CODE		if (1)

    template <class T> inline void DEBUG_DUMP(const char* str, const T* values, size_t num)
    {
        std::cout.setf(std::ios::fixed);
        std::cout << str;
        for (size_t i=0; i<num; i++)
            std::cout << (int)values[i] << " ";
        std::cout << std::endl;
    }
    template <class T> inline void DEBUG_DUMP(const T* values, size_t num)
    {
        DEBUG_DUMP<T>("", values, num);
    }
    inline void DEBUG_DUMP(const char*          value, size_t num) { DEBUG_DUMP<char>		("", value, num); }
    inline void DEBUG_DUMP(const unsigned char*	value, size_t num) { DEBUG_DUMP<unsigned char>	("", value, num); }
    inline void DEBUG_DUMP(const short*         value, size_t num) { DEBUG_DUMP<short>		("", value, num); }
    inline void DEBUG_DUMP(const unsigned short* value, size_t num) { DEBUG_DUMP<unsigned short>	("", value, num); }
    inline void DEBUG_DUMP(const int*           value, size_t num) { DEBUG_DUMP<int>		("", value, num); }
    inline void DEBUG_DUMP(const unsigned int*  value, size_t num) { DEBUG_DUMP<unsigned int>	("", value, num); }
    inline void DEBUG_DUMP(const long*          value, size_t num) { DEBUG_DUMP<long>		("", value, num); }
    inline void DEBUG_DUMP(const unsigned long*	value, size_t num) { DEBUG_DUMP<unsigned long>	("", value, num); }
    inline void DEBUG_DUMP(const float*         value, size_t num) { DEBUG_DUMP<float>		("", value, num); }
    inline void DEBUG_DUMP(const double*        value, size_t num) { DEBUG_DUMP<double>		("", value, num); }

#else

    #define DEBUG(values)		do {  } while (0)
    #define DEBUGIF(cond,values)	do {  } while (0)

    #define DEBUG_WAIT		{}
    #define DEBUG_HERE		{}
    #define DEBUG_BEEP		{}

    #define DEBUG_ASSERT(cond)	do {} while(0)

    #define DEBUG_CODE		if (0)

    template <class T> inline void DEBUG_DUMP(const char* str, const T* values, size_t num) { }
    template <class T> inline void DEBUG_DUMP(const T* values, size_t num) { }

    inline void DEBUG_DUMP(const char*          value, size_t num) { }
    inline void DEBUG_DUMP(const unsigned char* value, size_t num) { }
    inline void DEBUG_DUMP(const short*         value, size_t num) { }
    inline void DEBUG_DUMP(const unsigned short* value, size_t num) { }
    inline void DEBUG_DUMP(const int*           value, size_t num) { }
    inline void DEBUG_DUMP(const unsigned int*  value, size_t num) { }
    inline void DEBUG_DUMP(const long*          value, size_t num) { }
    inline void DEBUG_DUMP(const unsigned long* value, size_t num) { }
    inline void DEBUG_DUMP(const float*         value, size_t num) { } 
    inline void DEBUG_DUMP(const double*        value, size_t num) { }

#endif

/*=============================================================================*/

#endif
















































