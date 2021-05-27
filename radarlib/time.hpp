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
 *  \brief Functions about times and dates
 */ 

#ifndef __RADAR_TIME_HPP__
#define __RADAR_TIME_HPP__

#include <ctime>
#include <string>
#include <stdexcept>

#include <radarlib/defs.h>

namespace Radar {  

/*!
 * \brief  Functions about times and dates
 */
namespace timeutils {

/*===========================================================================*/
/* FUNZIONI PER AVERE IL TEMPO */
/*===========================================================================*/

RADAR_API bool		isNull	(time_t value);
RADAR_API bool		isNull	(double value);

/*!
 * \brief Get the current UTC time from the system 
 *
 * Get the current UTC time from the system as a time_t value
 * \return		A time_t value
 */
RADAR_API time_t	getUTC	();

/*!
 * \brief Create a time from a date
 *
 * Create a time_t value from a date. The time_t value will be aligned to the hour 00:00:00 of the day specified
 * \param year		the year to use. It must be >= 1970
 * \param month		the month to use
 * \param day		the day to use
 * \return		The time_t value representing the date specified
 * \throws std::invalid_argument	If the date is not a valid date
 */
RADAR_API time_t	mktime	(int year, int month, int day);
/*!
 * \brief Create a time from a date
 *
 * Create a time_t value from a date and a time
 * \param year		the year to use. It must be >= 1970
 * \param month		the month to use
 * \param day		the day to use
 * \param hour		the hour to use
 * \param min		the minutes to use
 * \param sec		the seconds to use
 * \return		The time_t value representing the date specified
 * \throws std::invalid_argument	If the values are out of range
 */
RADAR_API time_t	mktime	(int year, int month, int day, int hour, int min, int sec);
/*!
 * \brief Create a time from a date
 *
 * Create a time_t value from a date and a time
 * \param year		the year to use. It must be >= 1970
 * \param month		the month to use
 * \param day		the day to use
 * \param hour		the hour to use
 * \param min		the minutes to use
 * \param sec		the seconds to use
 * \param msec		the milliseconds to use
 * \return		The time_t value representing the date specified
 * \throws std::invalid_argument	If the values are out of range
 */
RADAR_API double	mktime	(int year, int month, int day, int hour, int min, int sec, int msec);

/*===========================================================================*/
/* FUNZIONI DI CHECK */
/*===========================================================================*/

/*!
 * \brief Check if the specified date is a valid date
 *
 * Check if the specified date is a valid date
 * \param year		the year to use. It must be >= 1970
 * \param month		the month to use
 * \param day		the day to use
 * \return		True if the date is valid, false otherwise
 */
RADAR_API bool	isValidDate	(int year, int month, int day);
/*!
 * \brief Check if the specified time is a valid date
 *
 * Check if the specified time is a valid date
 * \param hour		the hour to use. It must be >= 1970
 * \param min		the min to use
 * \param sec		the sec to use
 * \return		True if the time is valid, false otherwise
 */
RADAR_API bool	isValidTime	(int hour, int min, int sec);

/*===========================================================================*/
/* SPLIT FUNCTIONS */
/*===========================================================================*/

/*!
 * \brief Extract date informations from a time_t value
 *
 * Extract date informations from the given time_t value
 * \param absolute	the absolute time_t value 
 * \param year		a reference to a integer that will store the extracted year number
 * \param month		a reference to a integer that will store the extracted month number
 * \param day		a reference to a integer that will store the extracted day number
 */
RADAR_API void	splitYMD	(time_t absolute, int& year, int& month, int& day);
/*!
 * \brief Extract date informations from a double value 
 *
 * Extract date informations from the given double value representing an absolute time_t value with milliseconds
 * \param absolute	the absolute time_t value 
 * \param year		a reference to a integer that will store the extracted year number
 * \param month		a reference to a integer that will store the extracted month number
 * \param day		a reference to a integer that will store the extracted day number
 */
RADAR_API void	splitYMD	(double absolute, int& year, int& month, int& day);
/*!
 * \brief Extract day time informations from a time_t value
 *
 * Extract day time informations from the given time_t value
 * \param absolute	the absolute time_t value 
 * \param hour		a reference to a integer that will store the extracted hour number
 * \param min  		a reference to a integer that will store the extracted minutes number
 * \param sec		a reference to a integer that will store the extracted seconds number
 */
RADAR_API void	splitHMS	(time_t absolute, int& hour, int& min, int& sec);
/*!
 * \brief Extract day time informations from a double value
 *
 * Extract day time informations from the given double value representing an absolute time_t value with milliseconds
 * \param absolute	the absolute time_t value 
 * \param hour		a reference to a integer that will store the extracted hour number
 * \param min		a reference to a integer that will store the extracted minutes number
 * \param sec		a reference to a integer that will store the extracted seconds number
 * \param msec		a reference to a integer that will store the extracted milliseconds number
 */
RADAR_API void	splitHMS	(double absolute, int& hour, int& min, int& sec, int& msec);
/*!
 * \brief Extract date and day time informations from a time_t value
 *
 * Extract date and day time informations from the given time_t value 
 * \param absolute	the absolute time_t value 
 * \param year		a reference to a integer that will store the extracted hour number
 * \param month		a reference to a integer that will store the extracted minutes number
 * \param day		a reference to a integer that will store the extracted seconds number
 * \param hour		a reference to a integer that will store the extracted hour number
 * \param min		a reference to a integer that will store the extracted minutes number
 * \param sec		a reference to a integer that will store the extracted seconds number
 */
RADAR_API void	splitYMDHMS	(time_t absolute, int& year, int& month, int& day, int& hour, int& min, int& sec);
/*!
 * \brief Extract date and day time informations from a double value
 *
 * Extract date and day time informations from the given double value representing an absolute time_t value with milliseconds
 * \param absolute	the absolute time_t value 
 * \param year		a reference to a integer that will store the extracted hour number
 * \param month		a reference to a integer that will store the extracted minutes number
 * \param day		a reference to a integer that will store the extracted seconds number
 * \param hour		a reference to a integer that will store the extracted hour number
 * \param min		a reference to a integer that will store the extracted minutes number
 * \param sec		a reference to a integer that will store the extracted seconds number
 * \param msec		a reference to a integer that will store the extracted milliseconds number
 */
RADAR_API void	splitYMDHMS	(double absolute, int& year, int& month, int& day, int& hour, int& min, int& sec, int& msec);

/*===========================================================================*/
/* FUNIONI SU TEMPI ASSOLUTI */
/*===========================================================================*/

/*!
 * \brief Convert an absolute time_t value to a string
 *
 * Convert an absolute time_t value to a string with format 'YYYY-MM-DD hh:mm:ss'
 * \param value		the time_t value to convert
 * \returns		the formated string
 */
RADAR_API std::string absoluteToString(time_t value);
/*!
 * \brief Convert an double value representing an absolute time_t value with milliseconds
 *
 * Convert an absolute time_t value to a string with format 'YYYY-MM-DD hh:mm:ss.msec'
 * \param value		the time_t value to convert
 * \param allowNAN	if the value is NAN returns "0000-00-00 00:00:00" instead of throwing an exception
 * \returns		the formated string
 * \throws std::invalid_argument	If the value cannot be converted 
 */
RADAR_API std::string absoluteToString(double value, bool allowNAN);
/*!
 * \brief Convert a string to a time_t value
 *
 * Convert a string to a time_t value. The string must be formated as 'YYYY-MM-DD hh:mm:ss'
 * \param str		the string to convert
 * \returns		the formated string
 * \throws std::invalid_argument	If the string cannot be converted
 * \remarks This function will try to parse the given string with diffrent type of char separator (-,:, spaces etc.)
 */
RADAR_API time_t parseYYYYMMDDHHMMSS(const std::string& str);
/*!
 * \brief Reduce a float value to a time_t value, truncating the milliseconds
 */
RADAR_API time_t toEpoch	(float  absolute);
/*!
 * \brief Reduce a double value to a time_t value, truncating the milliseconds
 */
RADAR_API time_t toEpoch	(double absolute);

/*===========================================================================*/
/* FUNZIONI SU TEMPI GIORNALIERI */
/*===========================================================================*/

/*!
 * \brief Extract the date from a time_t value to a new time_t value 
 *
 * Extract the date from a time_t value to a new time_t value. 
 * Day time informations will be set to 00:00:00
 * \param absolute	the absolute time to use
 * \returns		the date extracted
 */
RADAR_API time_t extractDate	(time_t absolute);
/*!
 * \brief Extract the date from a double value to a new double value
 *
 * Extract the date from a double value to a new time_t value. 
 * Day time informations will be set to 00:00:00
 * \param absolute	the absolute time to use
 * \returns		the date extracted
 */
RADAR_API double extractDate	(double absolute);
/*!
 * \brief Extract the day time from a time_t value to a new time_t value
 *
 * Extract the day time from a time_t value to a new time_t value. 
 * The result value range is between 0 and 60*60*24 minutes
 * \param absolute	the absolute time to use
 * \returns		the day time extracted
 */
RADAR_API time_t extractTime	(time_t absolute);
/*!
 * \brief Extract the day time from a double value to a new double value
 *
 * Extract the day time from a time_t value to a new time_t value. 
 * The result value range is between 0 and 60*60*24 minutes
 * \param absolute	the absolute time to use
 * \returns		the day time extracted
 */
RADAR_API double extractTime	(double absolute);
/*!
 * \brief Convert a day time to a string
 *
 * Convert a day time to string formated as 'HH:MM:SS'
 * \param value		the day time as a time_t value
 * \returns		the formatted string
 */
RADAR_API std::string dayTimeToStr(time_t value);
/*!
 * \brief Convert a day time with milliseconds to a string
 *
 * Convert a day time to string formated as 'HH:MM:SS.msec'
 * \param value		the day time as a double value
 * \returns		the formatted string
 */
RADAR_API std::string dayTimeToStr(double value);

/*===========================================================================*/

/*!
 * \brief Convert a year day to the corresponding month and day number
 *
 * Convert a year day to the corresponding month and day number
 * \param year				the year to use
 * \param yday				the year day to use (from 1 to 365/366)
 * \param month				a reference to an integer that will store the month number (from 1 to 12)
 * \param day				a reference to an integer that will store the day number (from 1 to 31)
 * \throws std::invalid_argument	if the year or yday values are not valid
 */
RADAR_API void   convertYday(int year, int yday, int& month, int& day);
/*!
 * \brief Convert a year day to the corresponding time_t value
 *
 * Convert a year day to the corresponding time_t value
 * \param year				the year to use
 * \param yday				the year day to use (from 1 to 365/366)
 * \throws std::invalid_argument	if the year or yday values are not valid
 */
RADAR_API time_t convertYday(int year, int yday);
/*!
 * \brief Calculate the year day from a date
 *
 * Calculate the year day from a date
 * \param year				the year value (must be >= 1970)
 * \param month				the month value (from 1 to 12)
 * \param day				the day day (from 1 to 365/366)
 * \throws std::invalid_argument	if the year or yday values are not valid
 */
RADAR_API int    mkYday(int year, int month, int day);

/*===========================================================================*/

} }

#endif


























