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
 *  \brief Classes and functions for format strings according to OdimH5 format
 */ 

#ifndef __RADAR_ODIMH5V20_FORMAT_HPP__
#define __RADAR_ODIMH5V20_FORMAT_HPP__

/*===========================================================================*/

#include <radarlib/time.hpp>
#include <radarlib/string.hpp>
#include <radarlib/odimh5v20_hdf5.hpp>
#include <radarlib/odimh5v20_const.hpp>

namespace OdimH5v20 {

/*===========================================================================*/
/* FUNCTIONS TO FORMAT VALUES */
/*===========================================================================*/

/*! 
 * \brief HDF5File class
 * 
 * This is an provides several functions to format values according to OdimH5 specifications
 */
class Format
{
public:

	/*==============================================================*/
	/* FUNZIONI DI CONVERSIONE TRA STRINGHE E VALORI */
	/*==============================================================*/

	/*! 
	 * \brief Convert a time_t value to string
	 *
	 * Convert a time_t to a string formatted like 'YYYYMMDD'
	 * \param value				the time to convert
	 * \throws OdimH5Exception		if an unexpected error occurs
	 */	
	static std::string timeToYYYYMMDD(time_t value)
	{
		try
		{
			int year, month, day;
			Radar::timeutils::splitYMD(value, year, month, day);
			char buff[20];
			snprintf(buff, sizeof(buff), "%04d%02d%02d", year, month, day);		
			return buff;
		}
		catch (std::exception& e)
		{
			std::ostringstream ss; 
			ss << "Cannot convert value '" << value <<  "' to a string: " << e.what();
			throw OdimH5Exception(ss.str());
		}
	}
	/*! 
	 * \brief Convert a double value representing a time to string
	 *
	 * Convert a double value representing a time to a string formatted like 'YYYY-MM-DD'. This function truncate the time to seconds
	 * \param value				the time to convert
	 * \throws OdimH5Exception		if an unexpected error occurs
	 */	
	static std::string timeToYYYYMMDD(double value) 
	{ 
		return timeToYYYYMMDD((time_t)value); 
	}
	/*! 
	 * \brief Convert a time to a string
	 *
	 * Convert a time to a string formatted like 'HHMMSS'. 
	 * \param value				the time to convert
	 * \throws OdimH5Exception		if an unexpected error occurs
	 */	
	static std::string timeToHHMMSS(time_t value)
	{
		try
		{
			int hour, min, sec;		
			Radar::timeutils::splitHMS(value, hour, min, sec);
			char buff[20];
			snprintf(buff, sizeof(buff), "%02d%02d%02d", hour, min, sec);		
			return buff;
		}
		catch (std::exception& e)
		{
			std::ostringstream ss; 
			ss << "Cannot convert value '" << value <<  "' to a string: " << e.what();
			throw OdimH5Exception(ss.str());
		}
	}
	/*! 
	 * \brief Convert a time to a string
	 *
	 * Convert a time to a string formatted like 'HHMMSS.000'. 
	 * \param value				the time to convert
	 * \throws OdimH5Exception		if an unexpected error occurs
	 */	
	static std::string timeToHHMMSSsss(time_t value) 
	{ 
		return timeToHHMMSSsss((double)value); 
	}
	/*! 
	 * \brief Convert a time to a string
	 *
	 * Convert a time to a string formatted like 'HHMMSS.sss'. 
	 * \param value				the time to convert
	 * \throws OdimH5Exception		if an unexpected error occurs
	 */	
	static std::string timeToHHMMSSsss(double value)
	{
		try
		{
			int hour, min, sec, msec;
			Radar::timeutils::splitHMS(value, hour, min, sec, msec);
			char buff[30];
			snprintf(buff, sizeof(buff), "%02d%02d%02d.%03d", hour, min, sec, msec);
			return buff;
		}
		catch (std::exception& e)
		{
			std::ostringstream ss; 
			ss << "Cannot convert value '" << value <<  "' to a string: " << e.what();
			throw OdimH5Exception(ss.str());
		}
	}
	/*! 
	 * \brief Convert a string to a time_t value
	 *
	 * Convert a string formatted like 'YYYYMMDD' to a time_t value. 
	 * \param value				the string to convert
	 * \throws OdimH5FormatException	if the string is not well formated
	 */	
	static time_t YYYYMMDDToTime(const std::string& value) throw(OdimH5FormatException)
	{
		try
		{
			int year, month, day;
			if (sscanf(value.c_str(),"%04d%02d%02d", &year, &month, &day) != 3)
				throw OdimH5FormatException("'" + value + "' is not a valid YYYYMMDD date string");
			return Radar::timeutils::mktime(year, month, day, 0, 0, 0);
		}
		catch (std::invalid_argument& iae) 
		{
			throw OdimH5FormatException("'" + value + "' is not a odimh5 date: " + iae.what());
		}
	}
	/*! 
	 * \brief Convert a string to a time_t value
	 *
	 * Convert a string formatted like 'HHMMSS' to a time_t value. 
	 * \param value				the string to convert
	 * \throws OdimH5FormatException	if the string is not well formated
	 */
	static time_t HHMMSSToTime(const std::string& value) throw(OdimH5FormatException)
	{
		try
		{
			int hour, min, sec;
			if (sscanf(value.c_str(),"%02d%02d%02d", &hour, &min, &sec) != 3)
				throw OdimH5FormatException("'" + value + "' is not a valid HHMMSS time string");
			return Radar::timeutils::mktime(0, 0, 0, hour, min, sec);
		}
		catch (std::invalid_argument& iae) 
		{
			throw OdimH5FormatException("'" + value + "' is not a odimh5 time: " + iae.what());
		}
	}
	/*! 
	 * \brief Convert a string to a time_t value
	 *
	 * Convert a string formatted like 'HHMMSS.sss' to a double value representing a time value. 
	 * \param value				the string to convert
	 * \throws OdimH5FormatException	if the string is not well formated
	 */
	static double HHMMSSsssToTime(const std::string& value) throw(OdimH5FormatException)
	{		
		double dvalue;	
		if (sscanf(value.c_str(), "%lf", &dvalue) != 1)
			throw OdimH5FormatException("'" + value + "' is not a odimh5 time (double value)");
		long integer	= (long)(dvalue * 1000);	
		integer = integer % 240000000;	// per non saper ne leggere ne scrivere eliminiamo qualunque tempo oltre le 24 ore
		long msec	= integer % 1000;	integer /= 1000;
		long sec	=  integer % 100;	
		long min	= (integer / 100) %  100;
		long hour	=  integer / 10000;	
		return (double)(hour * 3600 + min * 60 + sec) + ((double)msec / 1000);
	}


};

/*===========================================================================*/

}

#endif












































