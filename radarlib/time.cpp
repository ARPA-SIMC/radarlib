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


#include <radarlib/time.hpp>

#include <cmath>
#include <sstream>

#include <radarlib/string.hpp>
#include <radarlib/debug.hpp>
#include <radarlib/math.hpp>

namespace Radar { namespace timeutils {

/*===========================================================================*/
/* FUNZIONI PER AVERE L'ORA */
/*===========================================================================*/

static const int TIMEUTILS_BASE_YEAR	= 1970;
static const int TIMEUTILS_FIRST_LEAP	= 1972;

bool isNull(time_t value)
{
	return value == (time_t)-1;
}

bool isNull(double value)
{
	return Radar::math::isnan(value);
}

time_t getUTC()
{
	return time(NULL);
}

static bool isLeap(int year)
{
	if ((year % 4)==0)
	{
		if ((year%100)==0)
		{
			if ((year%400)==0)
				return true;
		}
		else return true;
	}
	return false;
}

static int contaAnniBisestili(int year)
{
	int result = 0;
	for (int i=TIMEUTILS_FIRST_LEAP; i<year; i+=4)
	{
		if ((i%100)==0)
		{
			if ((i%400)==0)
				result++;
		}
		else
			result++;
	}
	return result;
}

const int yeardays[]   = { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 };
const int leapyearydays[] = { 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366 };

static time_t mktime_(int year, int month /*[0,11]*/, int day /*[0,30]*/, int hour, int min, int sec)
{
	time_t result = 0;
	if (year)
	{
		int anni_b	= contaAnniBisestili(year);
		int annidiff	= year - TIMEUTILS_BASE_YEAR;
		int anni	= annidiff - anni_b;
		
		result += anni   * 365 * 24 * 60 * 60;
		result += anni_b * 366 * 24 * 60 * 60;
		
		time_t yday = day + (isLeap(year) ? leapyearydays[month] : yeardays[month]);		
		
		result += yday * 3600 * 24;	
	}
	result += hour * 3600 + min * 60 + sec;
	return  result;
}

time_t mktime(int year, int month, int day) throw (std::invalid_argument)
{
	return mktime(year, month, day, 0, 0, 0);
}

time_t mktime(int year, int month, int day, int hour, int min, int sec) throw (std::invalid_argument)
{
	if (year && month && day)
	{
		if (!isValidDate(year, month, day)) {
			std::ostringstream ss;
			ss <<year<<"/"<<month<<"/"<<day<<" is not valid date ("<<__FUNCTION__<<")";
			throw std::invalid_argument(ss.str());
		}
	}
	if (!isValidTime(hour, min, sec)) {
		std::ostringstream ss;
		ss <<hour<<":"<<min<<":"<<sec<<" is not valid day time ("<<__FUNCTION__<<")";
		throw std::invalid_argument(ss.str());
	}

	return mktime_(year, month-1, day-1, hour, min, sec);
}

double mktime(int year, int month, int day, int hour, int min, int sec, int msec) throw (std::invalid_argument)

{
	if (msec > 1000) {
		std::ostringstream ss;
		ss <<msec<<" are not valid msec ("<<__FUNCTION__<<")";
		throw std::invalid_argument(ss.str());
	}
	time_t integer = mktime_(year, month-1, day-1, hour, min, sec);
	return (double)integer + (double)msec / 1000;
}

/*===========================================================================*/
/* FUNZIONI DI CHECK */
/*===========================================================================*/

bool   isValidDate(int yy, int mm, int dd)
{
	if (yy < TIMEUTILS_BASE_YEAR)	return false;
	if ((mm < 1) || (mm > 12))	return false;
	if (dd < 1)			return false;
	if (isLeap(yy))
	{
		const int mdays[] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		if (dd > mdays[mm-1]) return false;
	}
	//if ((mm == 2) && ((yy % 4)==0) && (dd > 29)) return false;
	else
	{
		const int mdays[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		if (dd > mdays[mm-1]) return false;
	}
	return true;
}

bool   isValidTime(int h, int m, int s)
{
	return (h >= 0) && (h < 24) && (m >= 0) && (m < 60) && (s >= 0) && (s < 60);
}

/*===========================================================================*/
/* SPLIT FUNCTIONS */
/*===========================================================================*/

void splitYMD(time_t absolute, int& year, int& month, int& day)
{
	struct tm *p = gmtime(&absolute); // convert to broken down time
		if (p == NULL) {
		std::ostringstream ss; 
		ss << "'"<<absolute<<"' is not a valid time_t ("<<__FUNCTION__<<")";
		throw std::invalid_argument(ss.str());
		}
	year	= p->tm_year + 1900;	
	month	= p->tm_mon + 1;
	day	= p->tm_mday;
}

void splitYMD(double absolute, int& year, int& month, int& day)
{
	splitYMD((time_t)absolute, year, month, day);
}


void splitHMS(time_t absolute, int& hour, int& min, int& sec)
{
	struct tm *p = gmtime(&absolute); // convert to broken down time
		if (p == NULL) {
		std::stringstream ss; 
		ss << "'"<<absolute<<"' is not a valid time_t ("<<__FUNCTION__<<")";
		throw std::invalid_argument(ss.str());
		}
	hour	= p->tm_hour;
	min	= p->tm_min;
	sec	= p->tm_sec;	
}

void splitHMS(double absolute, int& hour, int& min, int& sec, int& msec)
{
	msec = (int)fmod(absolute * 1000, 1000);
	splitHMS((time_t)floor(absolute), hour, min, sec);
}

/* funzione dii supporto */
static struct tm gmtime_(time_t absolute, const char* funcname) throw (std::invalid_argument)
{
	//TODO mutex
	struct tm* ctm = gmtime(&absolute);
		if (ctm == NULL) {
		std::stringstream ss; 
		ss << "'"<<absolute<<"' is not a valid time_t ("<<funcname<<")";
		throw std::invalid_argument(ss.str());
		}
	return *ctm;
}

/* funzionedi supporto */
static void splitYMDHMS_(time_t absolute, int& year, int& month, int& day, int& hour, int& min, int& sec, const char* funcname)
{
	struct tm ctm = gmtime_(absolute, funcname); // convert to broken down time
	year	= ctm.tm_year + 1900;	
	month	= ctm.tm_mon + 1;
	day	= ctm.tm_mday;
	hour	= ctm.tm_hour;
	min	= ctm.tm_min;
	sec	= ctm.tm_sec;	
}

void splitYMDHMS(time_t absolute, int& year, int& month, int& day, int& hour, int& min, int& sec)
{
	splitYMDHMS_(absolute, year, month, day, hour, min, sec, __FUNCTION__);
}

void splitYMDHMS(double absolute, int& year, int& month, int& day, int& hour, int& min, int& sec, int& msec)
{
	msec = (int)fmod(absolute * 1000, 1000);
	splitYMDHMS_((time_t)floor(absolute), year, month, day, hour, min, sec, __FUNCTION__);	
}

/*===========================================================================*/
/* FUNZIONI SU TEMPI ASSOLUTI */
/*===========================================================================*/

std::string absoluteToString(time_t value) ///, const char* fmt)
{		
	int year, month, day, hour, min, sec;
	splitYMDHMS(value, year, month, day, hour, min, sec);
	//struct tm ctm = gmtime_(value, __FUNCTION__);
	char buffer[50+1];
	snprintf(buffer, sizeof(buffer), "%04d-%02d-%02d %02d:%02d:%02d", year, month, day, hour, min, sec);
	//strftime(buffer, sizeof(buffer), fmt, &ctm);
	return buffer;
}

//std::string absoluteToString(time_t value)
//{
//	return absoluteToString(value, "%Y-%m-%d %H:%M:%S");
//}

std::string absoluteToString(double value, bool allowNAN)
{	
	if (Radar::math::isnan(value))
	{
		if (allowNAN)
			return "0000-00-00 00:00:00";
		throw std::invalid_argument("NAN is not a valid date/time");	
	}
	else
	{
		time_t  epoch	= (time_t)::floor(value);
		long	msint	= (long)fmod(value * 1000, 1000);
		std::ostringstream ss;
		ss.fill('0');
		ss << absoluteToString(epoch) << "." << std::setw(3) << msint;
		return ss.str();
	}
}

time_t parseYYYYMMDDHHMMSS(const std::string& str)
{
	//#define BASE_YEAR 1970

	const char* cstr = str.c_str();

	int year, month, day, hour, min, sec;

	if (sscanf(cstr, "%4d/%2d/%2d %2d:%2d:%2d", &year, &month, &day, &hour, &min, &sec)==6) goto scanned;
	if (sscanf(cstr, "%4d/%2d/%2d %2d-%2d-%2d", &year, &month, &day, &hour, &min, &sec)==6) goto scanned;
	if (sscanf(cstr, "%4d-%2d-%2d %2d:%2d:%2d", &year, &month, &day, &hour, &min, &sec)==6) goto scanned;
	if (sscanf(cstr, "%4d-%2d-%2d %2d-%2d-%2d", &year, &month, &day, &hour, &min, &sec)==6) goto scanned;
	if (sscanf(cstr, "%4d/%2d/%2dT%2d:%2d:%2d", &year, &month, &day, &hour, &min, &sec)==6) goto scanned;
	if (sscanf(cstr, "%4d/%2d/%2dT%2d-%2d-%2d", &year, &month, &day, &hour, &min, &sec)==6) goto scanned;
	if (sscanf(cstr, "%4d-%2d-%2dT%2d:%2d:%2d", &year, &month, &day, &hour, &min, &sec)==6) goto scanned;
	if (sscanf(cstr, "%4d-%2d-%2dT%2d-%2d-%2d", &year, &month, &day, &hour, &min, &sec)==6) goto scanned;
	hour = min = sec = 0;
	if (sscanf(cstr, "%4d/%2d/%2d", &year, &month, &day)==3) goto scanned;
	if (sscanf(cstr, "%4d-%2d-%2d", &year, &month, &day)==3) goto scanned;

	throw std::invalid_argument("'" + str + "' is not a valid date/time format ("+__FUNCTION__+")");

scanned:
	if (!isValidDate(year, month, day) && isValidTime(hour, min, sec))
		throw std::invalid_argument("'" + str + "' is not a valid date/time ("+__FUNCTION__+")");

	return mktime_(year, month-1, day-1, hour, min, sec);
}

time_t	toEpoch		(double absolute) 
{ 
	if (Radar::math::isnan(absolute))
		return (time_t)-1;
	return (time_t)absolute;
}

time_t	toEpoch		(float  absolute) 
{ 
	if (Radar::math::isnan(absolute))
		return (time_t)-1;
	return (time_t)absolute; 
}

/*===========================================================================*/
/* FUNZIONI SU TEMPI GIORNALIERI */
/*===========================================================================*/

static const int DAYSECONDS = 60 * 60 * 24;

time_t	extractDate(time_t absolute)
{
	return absolute - (absolute % DAYSECONDS);
}

double	extractDate(double absolute)
{
	time_t  epoch	= (time_t)::floor(absolute);
	epoch = epoch - (epoch % DAYSECONDS);
	return (double)epoch;
}

time_t  extractTime(time_t absolute)
{
	return absolute % DAYSECONDS;
}

double  extractTime(double absolute)
{
	time_t  epoch	= (time_t)::floor(absolute);
	epoch		= epoch % DAYSECONDS;	//tronchiamo al giorno

	double ms	= fmod(absolute * 1000, 1000);

	return ((double)epoch) + ms;
}

std::string dayTimeToStr(time_t value)
{
	value		= value % DAYSECONDS;	//tronchiamo al giorno

	int ss		= (int)(value % 60);
	int hh		= (int)(value / 3600);
	int mm		= (int)((value - ss - (hh * 3600)) / 60);

	char buff[30];
	snprintf(buff, 30, "%02d:%02d:%02d", hh, mm, ss);	
	return buff;	
}

std::string dayTimeToStr(double value)
{
	//double value to -> HHMMSS.sss 
	long integer	= (long)floorl(value);

	integer		= integer % DAYSECONDS;	// per non saper ne leggere ne scrivere eliminiamo qualunque tempo oltre le 24 ore

	int ss		= (int)(integer % 60);
	int hh		= (int)(integer / 3600);
	int mm		= (int)((integer - ss - (hh * 3600)) / 60);
	int ms		= (int)fmod(value * 1000, (double)1000);

	char buff[30];	
	snprintf(buff, 30, "%02d:%02d:%02d.%03d", hh, mm, ss, ms);	
	return buff;
}

/*===========================================================================*/
/* ALTRE */
/*===========================================================================*/

const int leapdays[] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
const int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

void convertYday(int year, int yday, int& month, int& day)
{
	if (isLeap(year))
	{
		if (yday > 366) {
			std::ostringstream ss;
			ss << "year day is out of range " << yday << "/366 (leap year) ("<<__FUNCTION__<<")";
			throw std::invalid_argument(ss.str());
		}
		int i;		
		for (i=0; (i < 12) && (yday > leapdays[i]); i++)
			yday -= leapdays[i];
		day   = yday;
		month = i + 1;		
	}
	else
	{
		if (yday > 365) {
			std::ostringstream ss;
			ss << "year day is out of range: " << yday << "/365 ("<<__FUNCTION__<<")";
			throw std::invalid_argument(ss.str());
		}
		int i;		
		for (i=0; (i < 12) && (yday > days[i]); i++)
			yday -= days[i];
		day   = yday;
		month = i + 1;
	}
}

time_t convertYday(int year, int yday)
{
	int month, day;
	convertYday(year, yday, month, day);
	return mktime(year, month, day, 0, 0, 0);
}

int mkYday(int year, int month, int day)
{
	if (isValidDate(year, month, day))
		return (isLeap(year) ? leapyearydays[month-1] : yeardays[month-1]) + day;

	std::ostringstream ss;
	ss << "Cannot calculate year day from "<<year<<"-"<<month<<"-"<<day<<" date";
	throw std::invalid_argument(ss.str());

}

/*===========================================================================*/

} }





















