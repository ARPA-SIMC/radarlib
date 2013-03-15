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
 *  \brief Macros, functions and constants about mathematic values
 */

#ifndef __RADAR_MATH_HPP__
#define __RADAR_MATH_HPP__

#include <limits>
#include <climits>
#include <cmath>

#include <radarlib/defs.h>

namespace Radar { namespace math {

/*===========================================================================*/
/* USEFULL DEFINES TO SIMPLIFY CODE */
/*===========================================================================*/

#define FLOAT_NAN		std::numeric_limits<float>::quiet_NaN()
#define FLOAT_MAX		std::numeric_limits<float>::max()
#define FLOAT_MIN		std::numeric_limits<float>::min()

#define DOUBLE_NAN		std::numeric_limits<double>::quiet_NaN()
#define DOUBLE_MAX		std::numeric_limits<double>::max()
#define DOUBLE_MIN		std::numeric_limits<double>::min()

/*===========================================================================*/

#if defined(WIN32)

//#ifndef isnan
static inline bool isnan(double x) { return x != x; }
//#endif

#endif

static inline bool isnan(float x)  { return x != x; }

static inline float  abs(float x)  { return (x > 0 ? x : -x); }
static inline double abs(double x) { return (x > 0 ? x : -x); }

/*===========================================================================*/

} }

#endif

























