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


#include "odimh5v20_support.hpp"

/*===========================================================================*/

#include <cmath>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <cstdio>

#include <radarlib/string.hpp>
#include <radarlib/time.hpp>
#include <radarlib/odimh5v20_const.hpp>
#include <radarlib/odimh5v20_format.hpp>

namespace OdimH5v20 {

/*===========================================================================*/
/* MODEL VERSION */
/*===========================================================================*/

ModelVersion::ModelVersion(int maj, int min)
:Major(maj)
,Minor(min)
{
}

ModelVersion::ModelVersion(const std::string& value)
:Major(0)
,Minor(0)
{
	parse(value);
}

void ModelVersion::parse(const std::string& value)
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
		
		if (key == OdimH5v20::SOURCE_WMO)
		{
			WMO = val;
		}
		else if (key == OdimH5v20::SOURCE_RAD)
		{
			OperaRadarSite = val;
		}
		else if (key == OdimH5v20::SOURCE_ORG)
		{
			try {
				OriginatingCenter = Radar::stringutils::parseInt(val);
			} catch (std::invalid_argument& e) {
				std::ostringstream ss;
				ss << "Value '" << val << "' is not a valid source info ORG: " << e.what();
				throw OdimH5FormatException(ss.str());
			}
		}
		else if (key == OdimH5v20::SOURCE_PLC)
		{
			Place = val;
		}
		else if (key == OdimH5v20::SOURCE_CTY)
		{
			try {
				Country = Radar::stringutils::parseInt(val);
			} catch (std::invalid_argument& e) {
				std::ostringstream ss;
				ss << "Value '" << val << "' is not a valid source info CTY: " << e.what();
				throw OdimH5FormatException(ss.str());
			}
		}
		else if (key == OdimH5v20::SOURCE_CMT)
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
		ss << OdimH5v20::SOURCE_WMO << ":" << WMO;		notEmpty = true;
	}
	if (OperaRadarSite.length())
	{
		if (notEmpty) ss << ",";
		ss << OdimH5v20::SOURCE_RAD << ":" << OperaRadarSite;	notEmpty = true;
	}
	if (OriginatingCenter)
	{
		if (notEmpty) ss << ",";
		ss << OdimH5v20::SOURCE_ORG << ":" << OriginatingCenter;	notEmpty = true;
	}
	if (Place.length())
	{
		if (notEmpty) ss << ",";
		ss << OdimH5v20::SOURCE_PLC << ":" << Place;		notEmpty = true;
	}
	if (Country)
	{
		if (notEmpty) ss << ",";
		ss << OdimH5v20::SOURCE_CTY << ":" << Country;		notEmpty = true;
	}
	if (Comment.length())
	{
		if (notEmpty) ss << ",";
		ss << OdimH5v20::SOURCE_CMT << ":" << Comment;		notEmpty = true;
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

AZAngles::AZAngles(const std::string& value)
:start(0)
,stop(0)
{
	parse(value);
}

void AZAngles::set(double start, double stop)
{
	this->start = start;
	this->stop = stop;
}

void AZAngles::parse(const std::string& str)
{
	std::string::size_type pos = str.find(':');
	if (pos == std::string::npos)
		throw OdimH5FormatException("Value '"+str+"' is not a valid azimuth angles pair");
	start = Radar::stringutils::parseDouble(str.substr(0, pos));
	stop  = Radar::stringutils::parseDouble(str.substr(pos + 1));
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

std::vector<AZAngles> AZAngles::parseSequence(const std::string& str)
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

AZTimes::AZTimes(const std::string& value)
:start(0)
,stop(0)
{
	parse(value);
}

void AZTimes::set(double start, double stop)
{
	this->start = start;
	this->stop = stop;
}

void AZTimes::parse(const std::string& str)
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

std::vector<AZTimes> AZTimes::parseSequence(const std::string& str)
{
	std::vector<std::string> tokens;
	Radar::stringutils::split(str, tokens, ",");
	std::vector<AZTimes> result;
	for (size_t i=0; i<tokens.size(); i++)
		result.push_back(AZTimes(tokens[i]));
	return result;
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

VILHeights::VILHeights(const std::string& value)
:bottom(0)
,top(0)
{
	parse(value);
}

void VILHeights::set(double bottom, double top)
{
	this->bottom = bottom;
	this->top = top;
}

void VILHeights::parse(const std::string& str)
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

Angles::Angles(const std::string& value)
:value(0)
{
	parse(value);
}

void Angles::set(double value)
{
	this->value = value;
}

void Angles::parse(const std::string& str)
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

std::vector<Angles> Angles::parseSequence(const std::string& str)
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

Arotation::Arotation(const std::string& value)
:value(0)
{
	parse(value);
}

void Arotation::set(double value)
{
	this->value = value;
}

void Arotation::parse(const std::string& str)
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

std::vector<Arotation> Arotation::parseSequence(const std::string& str)
{
	std::vector<std::string> tokens;
	Radar::stringutils::split(str, tokens, ",");
	std::vector<Arotation> result;
	for (size_t i=0; i<tokens.size(); i++)
		result.push_back(Arotation(tokens[i]));
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
/* NODES  */
/*===========================================================================*/

Nodes::Nodes()
:radar("")
{
}

Nodes::Nodes(const std::string& radar)
:radar("")
{
	set(radar);	
}

Nodes::Nodes(const char * radar)
:radar("")
{
	set(radar);
}
std::string Nodes::get() const {
	return this->radar;
}

void Nodes::set(const std::string& radar)
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

void Nodes::set(const char * radar)
{
	set(std::string(radar));
}

std::vector<Nodes> Nodes::parseSequence(const std::string& str)
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
