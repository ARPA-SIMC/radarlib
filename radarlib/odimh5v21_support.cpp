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


#include "odimh5v21_support.hpp"

/*===========================================================================*/

#include <cmath>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <cstdio>

#include <radarlib/string.hpp>
#include <radarlib/time.hpp>
#include <radarlib/odimh5v21_const.hpp>
#include <radarlib/odimh5v21_format.hpp>

namespace OdimH5v21 {

/*===========================================================================*/
/* MODEL VERSION */
/*===========================================================================*/

ModelVersion::ModelVersion(int maj, int min)
:Major(maj)
,Minor(min)
{
}

ModelVersion::ModelVersion(const std::string& value)	// throw(std::invalid_argument)
:Major(0)
,Minor(0)
{
	parse(value);
}

void ModelVersion::parse(const std::string& value)	// throw(std::invalid_argument)
{
	if (sscanf(value.c_str(), ATTRIBUTE_WHAT_VERSION_FORMAT, &Major, &Minor) != 2)
		throw OdimH5FormatException("'" + value + "' is not a valid OdimH5 model version");		
}

std::string ModelVersion::toString() const
{
	char buff[50+1];
	snprintf(buff, sizeof(buff), ATTRIBUTE_WHAT_VERSION_FORMAT, Major, Minor);
	return buff;
}


/*===========================================================================*/
/* SOURCE INFO */
/*===========================================================================*/

SourceInfo::SourceInfo()
:WMO()
,OperaRadarSite()
,OriginatingCenter(0)
,Place()
,Country(0)
,Comment("unknown")
{	
}

SourceInfo::SourceInfo(const std::string& value)
/* inizializziamo i campi visto che alcuni potrebbero non comparire nella stringa */
:WMO()
,OperaRadarSite()
,OriginatingCenter(0)
,Place()
,Country(0)
,Comment()
{
	parse(value);
}

void SourceInfo::parse(const std::string value)
{
	std::vector<std::string> tokens;
	std::vector<std::string>::iterator i;

	Radar::stringutils::split(value, tokens, ",");				//str_tokenize(tokens, value, std::string(","));	
	for (i = tokens.begin(); i<tokens.end(); i++)
	{
		std::string& token = *i;

		Radar::stringutils::trim(token);

		std::string::size_type pos = token.find(":");
		if (pos != 3)
			throw OdimH5FormatException("'"+value+"' is not a valid OdimH5 source info");
		
		std::string key = token.substr(0, 3);
		std::string val = token.substr(4);
		
		if (key == OdimH5v21::SOURCE_WMO)
		{
			WMO = val;
		}
		else if (key == OdimH5v21::SOURCE_RAD)
		{
			OperaRadarSite = val;
		}
		else if (key == OdimH5v21::SOURCE_ORG)
		{
			try {
				OriginatingCenter = Radar::stringutils::parseInt(val);
			} catch (std::invalid_argument& e) {
				std::ostringstream ss;
				ss << "Value '" << val << "' is not a valid source info ORG: " << e.what();
				throw OdimH5FormatException(ss.str());
			}
		}
		else if (key == OdimH5v21::SOURCE_PLC)
		{
			Place = val;
		}
		else if (key == OdimH5v21::SOURCE_CTY)
		{
			try {
				Country = Radar::stringutils::parseInt(val);
			} catch (std::invalid_argument& e) {
				std::ostringstream ss;
				ss << "Value '" << val << "' is not a valid source info CTY: " << e.what();
				throw OdimH5FormatException(ss.str());
			}
		}
		else if (key == OdimH5v21::SOURCE_CMT)
		{
			Comment = val;
		}
		else
		{
			throw OdimH5FormatException("'"+value+"' is not a valid OdimH5 source info. Key '"+key+"' is unknown");			
		}
	}
}

std::string SourceInfo::toString() const
{	
	bool notEmpty = false;
	std::stringstream ss;
	if (WMO.length()) 
	{
		ss << OdimH5v21::SOURCE_WMO << ":" << WMO;		notEmpty = true;
	}
	if (OperaRadarSite.length())
	{
		if (notEmpty) ss << ",";
		ss << OdimH5v21::SOURCE_RAD << ":" << OperaRadarSite;	notEmpty = true;
	}
	if (OriginatingCenter)
	{
		if (notEmpty) ss << ",";
		ss << OdimH5v21::SOURCE_ORG << ":" << OriginatingCenter;	notEmpty = true;
	}
	if (Place.length())
	{
		if (notEmpty) ss << ",";
		ss << OdimH5v21::SOURCE_PLC << ":" << Place;		notEmpty = true;
	}
	if (Country)
	{
		if (notEmpty) ss << ",";
		ss << OdimH5v21::SOURCE_CTY << ":" << Country;		notEmpty = true;
	}
	if (Comment.length())
	{
		if (notEmpty) ss << ",";
		ss << OdimH5v21::SOURCE_CMT << ":" << Comment;		notEmpty = true;
	}
	return ss.str();
}

/*===========================================================================*/
/* AZ ANGLES */
/*===========================================================================*/

AZAngles::AZAngles()
:start(0)
,stop(0)
{
}

AZAngles::AZAngles(double start, double stop)
:start(start)
,stop(stop)
{
}

AZAngles::AZAngles(const std::string& value)	// throw(std::invalid_argument)
:start(0)
,stop(0)
{
	parse(value);
}

void AZAngles::set(double start, double stop)	// throw(std::invalid_argument)
{
	this->start = start;
	this->stop = stop;
}

void AZAngles::parse(const std::string& str)	// throw(std::invalid_argument)
{
	std::string::size_type pos = str.find(':');
	if (pos == std::string::npos)
		throw OdimH5FormatException("Value '"+str+"' is not a valid azimuth angles pair");
	start = Radar::stringutils::parseDouble(str.substr(0, pos));
	stop  = Radar::stringutils::parseDouble(str.substr(pos + 1));
}

std::vector<AZAngles> AZAngles::parseSimpleArrays(const std::vector <double> & first,const std::vector <double> & second) 	// throw(std::invalid_argument); 
{
	std::vector<AZAngles> result;
	if (first.size() == second.size()){
	  for (size_t i=0; i<first.size(); i++)
		result.push_back(AZAngles(first[i],second[i]));
	  return result;
	}
	throw  OdimH5FormatException("The two series don't have the same size ");
}

std::string AZAngles::toString() const
{
	std::ostringstream ss;
	ss << start << ":" << stop;	
	return ss.str();
}

std::string AZAngles::toString(int precision) const
{
	std::ostringstream ss;
	ss.precision(precision);	/* NOTA: bisogna usare una precisione altissima altrimenti le riconversioni sbagliano di grado da gradi a unsigned short sbagliano a causa degli arrotondamenti*/
	ss << std::fixed << start << ":" << std::fixed << stop;	
	return ss.str();
}

std::vector<AZAngles> AZAngles::parseSequence(const std::string& str)	// throw(std::invalid_argument)
{
	std::vector<std::string> tokens;
	Radar::stringutils::split(str, tokens, ",");
	std::vector<AZAngles> result;
	for (size_t i=0; i<tokens.size(); i++)
		result.push_back(AZAngles(tokens[i]));
	return result;
}

std::string AZAngles::toString(const std::vector<AZAngles>& value)
{
	std::ostringstream ss;
	for (size_t i=0; i<value.size(); i++)
	{
		if (i) ss << ",";
		ss << value[i].toString();
	}
	return ss.str();
}

std::string AZAngles::toString(const std::vector<AZAngles>& value, int precision)
{
	std::ostringstream ss;
	for (size_t i=0; i<value.size(); i++)
	{
		if (i) ss << ",";
		ss << value[i].toString(precision);
	}
	return ss.str();
}
double AZAngles::averagedAngle(int direction){
	double first, second;
	if (direction >= 0) {
	   first=start;
	   second=stop;
        }else {
	   first=stop;
	   second=start;
	}

	if (first > second) {
	   return fmod((first+second+360)*0.5,360);
	}else{
           return fmod((first+second)*0.5,360);
	}
}


/*===========================================================================*/
/* AZIMUTH TIMES */
/*===========================================================================*/

AZTimes::AZTimes()
:start(0)
,stop(0)
{
}

AZTimes::AZTimes(double start, double stop)
:start(start)
,stop(stop)
{
}

AZTimes::AZTimes(const std::string& value)	// throw(std::invalid_argument)
:start(0)
,stop(0)
{
	parse(value);
}

void AZTimes::set(double start, double stop)	// throw(std::invalid_argument)
{
	this->start = start;
	this->stop = stop;
}

void AZTimes::parse(const std::string& str)	// throw(std::invalid_argument)
{
	std::string::size_type pos = str.find(':');
	if (pos == std::string::npos)
		throw std::invalid_argument("'"+str+"' is not a valid azimut angles pair");
	start = Format::HHMMSSsssToTime(str.substr(0, pos));
	stop  = Format::HHMMSSsssToTime(str.substr(pos + 1));	
}

std::string AZTimes::toString() const
{
	return Format::timeToHHMMSSsss(start) + ":" + Format::timeToHHMMSSsss(stop);
}

std::vector<AZTimes> AZTimes::parseSequence(const std::string& str)	// throw(std::invalid_argument)
{
	std::vector<std::string> tokens;
	Radar::stringutils::split(str, tokens, ",");
	std::vector<AZTimes> result;
	for (size_t i=0; i<tokens.size(); i++)
		result.push_back(AZTimes(tokens[i]));
	return result;
}

std::vector<AZTimes> AZTimes::parseSimpleArrays(const std::vector <double> & first,const std::vector <double> & second) 	// throw(std::invalid_argument); 
{
	std::vector<AZTimes> result;
	if (first.size() == second.size()){
	  for (size_t i=0; i<first.size(); i++)
		result.push_back(AZTimes(first[i],second[i]));
	  return result;
	}
	throw  OdimH5FormatException("The two series don't have the same size ");
}
std::string AZTimes::toString(const std::vector<AZTimes>& value)
{
	std::ostringstream ss;
	for (size_t i=0; i<value.size(); i++)
	{
		if (i) ss << ",";
		ss << value[i].toString();
	}
	return ss.str();
}


/*===========================================================================*/
/* VILHEIGHTS */
/*===========================================================================*/

VILHeights::VILHeights()
:bottom(0)
,top(0)
{
}

VILHeights::VILHeights(double bottom, double top)
:bottom(bottom)
,top(top)
{
}

VILHeights::VILHeights(const std::string& value)	// throw(std::invalid_argument)
:bottom(0)
,top(0)
{
	parse(value);
}

void VILHeights::set(double bottom, double top)	// throw(std::invalid_argument)
{
	this->bottom = bottom;
	this->top = top;
}

void VILHeights::parse(const std::string& str)	// throw(std::invalid_argument)
{
	std::string::size_type pos = str.find(',');
	if (pos == std::string::npos)
		throw std::invalid_argument("'"+str+"' is not a valid azimut angles pair");
	bottom	= Radar::stringutils::parseDouble(str.substr(0, pos));
	top	= Radar::stringutils::parseDouble(str.substr(pos + 1));
}

std::string VILHeights::toString() const
{
	std::ostringstream ss;
	ss.precision(30);		/* NOTA: bisogna usare una altra precisioe per evitare perdite negli arrotondamenti in fase di rilettura */
	ss << bottom << "," << top;
	return ss.str();
}

/*===========================================================================*/
/* ANGLES */
/*===========================================================================*/

Angles::Angles()
:value(0)
{
}

Angles::Angles(double value)
:value(value)
{
}

Angles::Angles(const std::string& value)	// throw(std::invalid_argument)
:value(0)
{
	parse(value);
}

void Angles::set(double value) 	// throw(std::invalid_argument)
{
	this->value = value;
}

void Angles::parse(const std::string& str)	// throw(std::invalid_argument)
{
	value = Radar::stringutils::parseDouble(str); 
}

std::string Angles::toString() const
{
	std::ostringstream ss;
	ss << value;	
	return ss.str();
}

std::string Angles::toString(int precision) const
{
	std::ostringstream ss;
	ss.precision(precision);	/* NOTA: bisogna usare una precisione altissima altrimenti le riconversioni sbagliano di grado da gradi a unsigned short sbagliano a causa degli arrotondamenti*/
	ss << std::fixed << value ;	
	return ss.str();
}

std::vector<Angles> Angles::parseSimpleArray(const std::vector <double> & value)	// throw(std::invalid_argument); 
{
	std::vector<Angles> result;
	for (size_t i=0; i<value.size(); i++)
		result.push_back(Angles(value[i]));
	return result;
}
std::vector<Angles> Angles::parseSequence(const std::string& str)	// throw(std::invalid_argument)
{
	std::vector<std::string> tokens;
	Radar::stringutils::split(str, tokens, ",");
	std::vector<Angles> result;
	for (size_t i=0; i<tokens.size(); i++)
		result.push_back(Angles(tokens[i]));
	return result;
}

std::string Angles::toString(const std::vector<Angles>& value)
{
	std::ostringstream ss;
	for (size_t i=0; i<value.size(); i++)
	{
		if (i) ss << ",";
		ss << value[i].toString();
	}
	return ss.str();
}

std::string Angles::toString(const std::vector<Angles>& value, int precision)
{
	std::ostringstream ss;
	for (size_t i=0; i<value.size(); i++)
	{
		if (i) ss << ",";
		ss << value[i].toString(precision);
	}
	return ss.str();
}

/*===========================================================================*/
/* AROTATION */
/*===========================================================================*/

Arotation::Arotation()
:value(0)
{
}

Arotation::Arotation(double value)
:value(value)
{
}

Arotation::Arotation(const std::string& value)	// throw(std::invalid_argument)
:value(0)
{
	parse(value);
}

void Arotation::set(double value) 	// throw(std::invalid_argument)
{
	this->value = value;
}

void Arotation::parse(const std::string& str)	// throw(std::invalid_argument)
{
	value = Radar::stringutils::parseDouble(str); 
}

std::string Arotation::toString() const
{
	std::ostringstream ss;
	ss << value;	
	return ss.str();
}

std::string Arotation::toString(int precision) const
{
	std::ostringstream ss;
	ss.precision(precision);	/* NOTA: bisogna usare una precisione altissima altrimenti le riconversioni sbagliano di grado da gradi a unsigned short sbagliano a causa degli arrotondamenti*/
	ss << std::fixed << value ;	
	return ss.str();
}

std::vector<Arotation> Arotation::parseSequence(const std::string& str)	// throw(std::invalid_argument)
{
	std::vector<std::string> tokens;
	Radar::stringutils::split(str, tokens, ",");
	std::vector<Arotation> result;
	for (size_t i=0; i<tokens.size(); i++)
		result.push_back(Arotation(tokens[i]));
	return result;
}

std::vector<Arotation> Arotation::parseSimpleArray(const std::vector <double> & value)	// throw(std::invalid_argument); 
{
	std::vector<Arotation> result;
	for (size_t i=0; i<value.size(); i++)
		result.push_back(Arotation(value[i]));
	return result;
}
std::string Arotation::toString(const std::vector<Arotation>& value)
{
	std::ostringstream ss;
	for (size_t i=0; i<value.size(); i++)
	{
		if (i) ss << ",";
		ss << value[i].toString();
	}
	return ss.str();
}

std::string Arotation::toString(const std::vector<Arotation>& value, int precision)
{
	std::ostringstream ss;
	for (size_t i=0; i<value.size(); i++)
	{
		if (i) ss << ",";
		ss << value[i].toString(precision);
	}
	return ss.str();
}

/*===========================================================================*/
/* TXPOWER    */
/*===========================================================================*/

TXpower::TXpower()
:value(0)
{
}

TXpower::TXpower(double value)
:value(value)
{
}

TXpower::TXpower(const std::string& value)	// throw(std::invalid_argument)
:value(0)
{
	parse(value);
}

void TXpower::set(double value) 	// throw(std::invalid_argument)
{
	this->value = value;
}

void TXpower::parse(const std::string& str)	// throw(std::invalid_argument)
{
	value = Radar::stringutils::parseDouble(str); 
}

std::string TXpower::toString() const
{
	std::ostringstream ss;
	ss << value;	
	return ss.str();
}

std::string TXpower::toString(int precision) const
{
	std::ostringstream ss;
	ss.precision(precision);	
	ss << std::fixed << value ;	
	return ss.str();
}

std::vector<TXpower> TXpower::parseSequence(const std::string& str)	// throw(std::invalid_argument)
{
	std::vector<std::string> tokens;
	Radar::stringutils::split(str, tokens, ",");
	std::vector<TXpower> result;
	for (size_t i=0; i<tokens.size(); i++)
		result.push_back(TXpower(tokens[i]));
	return result;
}

std::vector<TXpower> TXpower::parseSimpleArray(const std::vector <double> & value)	// throw(std::invalid_argument); 
{
	std::vector<TXpower> result;
	for (size_t i=0; i<value.size(); i++)
		result.push_back(TXpower(value[i]));
	return result;
}
std::string TXpower::toString(const std::vector<TXpower>& value)
{
	std::ostringstream ss;
	for (size_t i=0; i<value.size(); i++)
	{
		if (i) ss << ",";
		ss << value[i].toString();
	}
	return ss.str();
}

std::string TXpower::toString(const std::vector<TXpower>& value, int precision)
{
	std::ostringstream ss;
	for (size_t i=0; i<value.size(); i++)
	{
		if (i) ss << ",";
		ss << value[i].toString(precision);
	}
	return ss.str();
}

/*===========================================================================*/
/* NODES  */
/*===========================================================================*/

Nodes::Nodes()
:radar("")
{
}

Nodes::Nodes(const std::string& radar)	// throw(std::invalid_argument)
:radar("")
{
	set(radar);	
}

Nodes::Nodes(const char * radar)	// throw(std::invalid_argument)
:radar("")
{
	set(radar);
}
std::string Nodes::get() const {
	return this->radar;
}

void Nodes::set(const std::string& radar) 	// throw(std::invalid_argument)
{
	if (radar.empty())
		throw std::logic_error("empty node is not a valid value");

	std::string::size_type pos = radar.find('\'');
	if (pos == std::string::npos) {
		this->radar = "'" + radar + "'";
	} else if (radar.at(0) == '\'' && radar.at(radar.size()-1) == '\'') {
		this->radar = radar;
	} else {
		throw std::logic_error(radar + " is not a valid node value");
	}
}

void Nodes::set(const char * radar) 	// throw(std::invalid_argument)
{
	set(std::string(radar));
}

std::vector<Nodes> Nodes::parseSequence(const std::string& str)	// throw(std::invalid_argument)
{
	std::vector<std::string> tokens;
	Radar::stringutils::split(str, tokens, ",");
	std::vector<Nodes> result;
	for (size_t i=0; i<tokens.size(); i++)
		result.push_back(Nodes(tokens[i]));
	return result;
}

std::string Nodes::toString(const std::vector<Nodes>& value)
{
	std::ostringstream ss;
	for (size_t i=0; i<value.size(); i++)
	{
		ss << value[i].radar;
		if (i != value.size() - 1)
			ss << ",";
	}
	return ss.str();
}

//std::vector<VILHeights> VILHeights::parseSequence(const std::string& str)	// throw(std::invalid_argument)
//{
//	std::vector<std::string> tokens;
//	Radar::stringutils::split(str, tokens, ",");
//	std::vector<VILHeights> result;
//	for (size_t i=0; i<tokens.size(); i++)
//		result.push_back(VILHeights(tokens[i]));
//	return result;
//}
//
//std::string VILHeights::toString(const std::vector<VILHeights>& value)
//{
//	std::ostringstream ss;
//	for (size_t i=0; i<value.size(); i++)
//	{
//		if (i) ss << ",";
//		ss << value[i].toString();
//	}
//	return ss.str();
//}

/*===========================================================================*/
/* SUPPORT FUNCTIONS */
/*===========================================================================*/
//
//static inline void get_gm_time(struct tm* ctm)
//{
//	time_t ctime = time(NULL);
//	*ctm = *gmtime(&ctime);
//}
//
//static inline void get_local_time(struct tm* ctm)
//{
//	time_t ctime = time(NULL);
//	*ctm = *localtime(&ctime);
//}
//
//
///*===========================================================================*/
///* DATE */
///*===========================================================================*/
//
//const char* Date::FORMAT_YYYY_MM_DD = "%Y-%m-%d";
//
//static void assertValidDate(int year, int month, int day)
//{
//	if (timeutils::isValidDate(year, month, day))
//		return;
//	std::ostringstream ss; 
//	ss << year << "/" << month << "/" << day << " is not a valid date";
//	throw std::invalid_argument(ss.str());
//}
//
//Date::Date()
//:year(1970)
//,month(1)
//,day(1)
//{
//}
//
//Date::Date(time_t value)
//:year(1970)
//,month(1)
//,day(1)
//{
//	time_t value2 = value;
//	struct tm ctm;
//	ctm = *gmtime(&value2);
//	year   = ctm.tm_year + 1900;
//	month  = ctm.tm_mon + 1;
//	day    = ctm.tm_mday;
//}
//
//Date::Date(int year, int month, int day)	throw(std::invalid_argument)
//:year(1970)
//,month(1)
//,day(1)
//{
//	assertValidDate(year, month, day);
//	set(year, month, day);
//}
//
//Date::Date(const std::string& value, bool allowEmpty)	throw(std::invalid_argument)
//:year(1970)
//,month(1)
//,day(1)
//{
//	parse(value, allowEmpty);
//}
//
//Date::Date(const Date& value)
//:year(value.year)
//,month(value.month)
//,day(value.day)
//{
//}
//
//void Date::set(int year, int month, int day)	throw(std::invalid_argument)
//{
//	assertValidDate(year, month, day);
//	this->year = year;
//	this->month = month;
//	this->day = day;
//}
//
//void Date::parse(const std::string& value, bool allowEmpty)	throw(std::invalid_argument)
//{
//	if (value.empty() && allowEmpty)
//		return;
//
//	const char* cstr = value.c_str();
//	int y,m,d;	
//	y=m=d=0;
//	if (sscanf(cstr, "%04d/%02d/%02d", &y, &m, &d) == 3)	goto scanned;
//	if (sscanf(cstr, "%04d-%02d-%02d", &y, &m, &d) == 3)	goto scanned;
//	if (sscanf(cstr, "%04d%02d%02d",   &y, &m, &d) == 3)	goto scanned;
//
//	throw std::invalid_argument("'"+value+"' is not a valid date format");
//scanned:
//	if (!timeutils::isValidDate(y,m,d))
//		throw std::invalid_argument("'"+value+"' is not a valid date");
//	year	= y;
//	month	= m;
//	day	= d;
//}
//
//std::string Date::toString(const char* format) const
//{
//	int d = day;
//	int y = year  >= 1900 ? year - 1900 : 0;
//	int m = month >= 1    ? month - 1  : 0;
//	struct tm ctm = { 
//		0,		//int tm_sec;     /* seconds after the minute - [0,59] */
//		0,		//int tm_min;     /* minutes after the hour - [0,59] */
//		0,		//int tm_hour;    /* hours since midnight - [0,23] */
//		d,		//int tm_mday;    /* day of the month - [1,31] */
//		m,		//int tm_mon;     /* months since January - [0,11] */
//		y,		//int tm_year;    /* years since 1900 */
//		0,		//int tm_wday;    /* days since Sunday - [0,6] */
//		0,		//int tm_yday;   /* days since January 1 - [0,365] */
//		0,		//int tm_isdst;   /* daylight savings time flag */
//		};
//	char buff[100];
//	strftime(buff, sizeof(buff), format, &ctm);
//	return buff;
//}
//
//std::string Date::toString() const
//{
//	return toString(OdimH5v21::ATTRIBUTE_WHAT_DATE_FORMAT);
//}		
//
//Date Date::getLocal()
//{
//	struct tm ctm;
//	get_local_time(&ctm);
//	return Date(ctm.tm_year + 1900, ctm.tm_mon  + 1, ctm.tm_mday);
//}
//
//Date Date::getUTC()
//{
//	struct tm ctm;
//	get_gm_time(&ctm);
//	return Date(ctm.tm_year + 1900, ctm.tm_mon  + 1, ctm.tm_mday);
//}

/*===========================================================================*/
/* TIME */
/*===========================================================================*/
//
//const char* Time::FORMAT_HH_MM_SS = "%H:%M:%S";
//
//static void assertValidTime(int h, int m, int s)
//{
//	if (timeutils::isValidTime(h, m, s))
//		return;
//	std::ostringstream ss; 
//	ss << h << ":" << m << ":" << s << " is not a valid time";
//	throw std::invalid_argument(ss.str());
//}
//
//
//Time::Time()
//:hour(0)
//,min(0)
//,sec(0)
//{
//}
//
//Time::Time(time_t value)
//{
//	struct tm ctm;
//	ctm = *gmtime(&value);
//	hour	= ctm.tm_hour;
//	min	= ctm.tm_min;
//	sec	= ctm.tm_sec;
//}
//
//Time::Time(int hour, int min, int sec)	throw(std::invalid_argument)
//:hour(0)
//,min(0)
//,sec(0)
//{
//	assertValidTime(hour, min, sec);
//	set(hour, min, sec);
//}
//
//Time::Time(const std::string& value, bool allowEmpty)	throw(std::invalid_argument)
//:hour(0)
//,min(0)
//,sec(0)
//{
//	parse(value, allowEmpty);
//}
//
//Time::Time(const Time& value)
//:hour(value.hour)
//,min(value.min)
//,sec(value.sec)
//{	
//}
//
//void Time::set(int hour, int min, int sec)	throw(std::invalid_argument)
//{
//	assertValidTime(hour, min, sec);
//	this->hour = hour;
//	this->min = min;
//	this->sec = sec;
//}
//
//void Time::parse(const std::string& value, bool allowEmpty) throw(std::invalid_argument)
//{
//	if (value.empty() && allowEmpty)
//		return;
//
//	const char* cstr = value.c_str();
//	int h,m,s;
//	if (sscanf(cstr, "%02d:%02d:%02d", &h, &m, &s) == 3)	goto scanned;
//	if (sscanf(cstr, "%02d-%02d-%02d", &h, &m, &s) == 3)	goto scanned;
//	if (sscanf(cstr, "%02d%02d%02d",   &h, &m, &s) == 3)	goto scanned;
//	
//	throw std::invalid_argument("'"+value+"' is not a valid time format");
//
//scanned:
//	if (!timeutils::isValidTime(h, m, s))
//		throw std::invalid_argument("'"+value+"' is not a valid time");
//
//	hour	= h;
//	min	= m;
//	sec	= s;
//}
//
//std::string Time::toString(const char* format) const
//{	
//	char buff[100];
//	struct tm ctm = { 
//		sec,		//int tm_sec;     /* seconds after the minute - [0,59] */
//		min,		//int tm_min;     /* minutes after the hour - [0,59] */
//		hour,		//int tm_hour;    /* hours since midnight - [0,23] */
//		0,		//int tm_mday;    /* day of the month - [1,31] */
//		0,		//int tm_mon;     /* months since January - [0,11] */
//		0,		//int tm_year;    /* years since 1900 */
//		0,		//int tm_wday;    /* days since Sunday - [0,6] */
//		0,		//int tm_yday;   /* days since January 1 - [0,365] */
//		0,		//int tm_isdst;   /* daylight savings time flag */
//		};
//	strftime(buff, sizeof(buff), format, &ctm);	
//	return std::string(buff);
//}	
//
//std::string Time::toString() const
//{
//	return toString(OdimH5v21::ATTRIBUTE_WHAT_TIME_FORMAT);
//}		
//
//Time Time::getLocal()
//{
//	struct tm ctm;
//	get_local_time(&ctm);
//	return Time(ctm.tm_hour, ctm.tm_min, ctm.tm_sec);
//}
//
//Time Time::getUTC()
//{
//	struct tm ctm;
//	get_gm_time(&ctm);
//	return Time(ctm.tm_hour, ctm.tm_min, ctm.tm_sec);
//}

/*===========================================================================*/	


/*===========================================================================*/

//static const char* AZTIMES_ATTRIBUTE_FORMAT = "%02d%02d%02d.%03d";
//
//static std::string valueToString(float value)
//{
//	long	integer = ::floor((double)value);	
//	integer		= integer % (60 * 60 * 24);	//per non saper ne leggere ne scrivere riduco ai dati sulle 24 ore
//	int	ms	= ((int)(value * 1000) % 1000);
//	int	ss	= integer % 60;
//	int	hh	= integer / 3600;
//	int	mm	= (integer - (hh * 3600)) / 60;
//	char buffer[40+1];
//	snprintf(buffer, 40, AZTIMES_ATTRIBUTE_FORMAT, hh, mm, ss, ms);
//	return buffer;
//}
//
//static float stringToValue(const std::string& value)
//{
//	int hh, mm, ss;
//	float ms;
//	if (sscanf(value.c_str(), "%02d%02d%02d%f", &hh, &mm, &ss, &ms) != 4)
//		throw std::invalid_argument("'" + value + "' is not a valid azimuth times pair");
//	return (float)(hh * 3600 + mm * 60 + ss) + ms; //((float)ms / 1000);
//}
//
//std::string AZTimes::toOdimPairStr() const
//{
//	return valueToString(start) + ":" + valueToString(stop);
//}
//
//std::vector<AZTimes> AZTimes::fromOdimPairs(const std::string pairs)
//{
//	std::vector<std::string> tokens;
//	stringutils::split(pairs, tokens, ",");
//	std::vector<AZTimes> result;
//	for (std::vector<std::string>::const_iterator i = tokens.begin(); i<tokens.end(); i++)
//	{
//		std::string pair = *i;
//		std::string::size_type pos = pair.find(':');
//		if (pos == std::string::npos)
//			throw std::invalid_argument("'"+pair+"' is not a valid azimut angles pair");
//		float start = stringToValue(pair.substr(0, pos));
//		float stop  = stringToValue(pair.substr(pos + 1));
//		result.push_back(AZTimes(start, stop));
//	}
//	return result;
//}
//
//std::string AZTimes::toOdimPairs(const std::vector<AZTimes>& right)
//{
//	std::ostringstream ss;
//	for (std::vector<AZTimes>::const_iterator i=right.begin(); i<right.end(); i++)
//	{
//		if (i != right.begin())
//			ss << ",";
//		ss << i->toOdimPairStr();
//	}
//	return ss.str();
//}

/*===========================================================================*/

}
