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


#include <radarlib/string.hpp>

#include <iostream>

namespace Radar { namespace stringutils {

/*===========================================================================*/
/* SPLIT */
/*===========================================================================*/

void split(const std::string& str, std::vector<std::string>& tokens, const std::string& delimiters)
{
	std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);	// Skip delimiters at beginning.
	std::string::size_type pos     = str.find_first_of(delimiters, lastPos);	// Find first "non-delimiter".
	while (std::string::npos != pos || std::string::npos != lastPos)
	{		
		tokens.push_back(str.substr(lastPos, pos - lastPos));	// Found a token, add it to the vector.		
		lastPos = str.find_first_not_of(delimiters, pos);	// Skip delimiters.  Note the "not_of"		
		pos = str.find_first_of(delimiters, lastPos);		// Find next "non-delimiter"
	}
}

void split(const std::string& str, std::string& first, std::string& second, const char separator)
{
	std::string::size_type pos = str.find(separator);
	if (pos == std::string::npos)
		throw std::invalid_argument(str + "is not a pair separated with " + separator);
	first	= str.substr(0, pos);
	second	= str.substr (pos + 1, str.length() - pos - 1);
}

std::string& trimleft(std::string& s)
{
	std::string::iterator it;
	for (it = s.begin(); it != s.end(); it++)
		if (!::isspace( *it ))
			break;
	s.erase(s.begin(), it);
	return s;
}

std::string trimleft(const std::string& s)
{
	std::string value = s;
	trimleft(value);
	return value;
}

std::string& trimright(std::string& s)
{
	std::string::difference_type dt;
	std::string::reverse_iterator it;
	for (it = s.rbegin(); it != s.rend(); it++)
		if (!isspace(*it))
			 break;
	dt = s.rend() - it;
	s.erase(s.begin() + dt, s.end());
	return s;
}

std::string trimright(const std::string& s)
{
	std::string value = s;
	trimright(value);
	return value;
}

std::string& trim(std::string& s)
{
	trimleft(s);
	trimright(s);
	return s;
}

std::string trim(const std::string& s)
{
	std::string t = s;
	return trim(t);
}


/*===========================================================================*/
/* TO STRING */
/*===========================================================================*/

std::string toString(bool value)	{ std::ostringstream stream; stream << value; return stream.str(); }
std::string toString(int value)		{ std::ostringstream stream; stream << value; return stream.str(); }
std::string toString(long value)	{ std::ostringstream stream; stream << value; return stream.str(); }
std::string toString(float value)	{ std::ostringstream stream; stream << value; return stream.str(); }
std::string toString(double value)	{ std::ostringstream stream; stream << value; return stream.str(); }

std::string toString(size_t value)	{ std::ostringstream stream; stream << value; return stream.str(); }

std::string toString(const std::vector<bool>& val, const char* sep) { return toString<bool>(val, sep); }
std::string toString(const std::vector<int>& val, const char* sep)  { return toString<int>(val, sep); }
std::string toString(const std::vector<long>& val, const char* sep) { return toString<long>(val, sep); }
std::string toString(const std::vector<float>& val, const char* sep) { return toString<float>(val, sep); }
std::string toString(const std::vector<double>& val, const char* sep) { return toString<double>(val, sep); }


/*===========================================================================*/
/* PARSE */
/*===========================================================================*/

bool isInt(const std::string& s)
{
	std::istringstream ss(s);
	int temp;
	return (ss >> temp) ? true : false;
}

bool   parseBool	(const std::string& s)
{
	if ((s == "1") || (s == "true")) 	return true;
	if ((s == "0") || (s == "false"))	return false;
	throw std::invalid_argument("'"+s+"' is not a boolean value");
}

template <class T> static T parset(const std::string& s, const std::string& typestr)
{
	if (!s.empty())  
	{
		T result;
		std::istringstream ss(s);
		if ((ss >> result))
			return result;
	}
	throw std::invalid_argument("'" + s + "' is not a valid " + typestr + " value");
}

int    parseInt		(const std::string& s) { return parset<int>(s, "integer"); }
float  parseFloat	(const std::string& s) { return parset<float>(s, "float"); }
double parseDouble	(const std::string& s) { return parset<double>(s, "double"); }

void	parseSeq(const std::string& s, std::vector<bool>& val, const char* sep, const bool allowEmptyStr)
{
	std::vector<std::string> tokens;
	stringutils::split(s, tokens, sep);
	if (tokens.empty() && !allowEmptyStr)
		throw std::invalid_argument(s + " is not a sequence of boolean values");
	for (std::vector<std::string>::size_type i=0; i<tokens.size(); i++)
		val.push_back( stringutils::parseBool(tokens[i]) );
}

void	parseSeq(const std::string& s, std::vector<int>& val, const char* sep, const bool allowEmptyStr)
{
	std::vector<std::string> tokens;
	stringutils::split(s, tokens, sep);
	if (tokens.empty() && !allowEmptyStr)
		throw std::invalid_argument(s + " is not a sequence of integer values");
	for (std::vector<std::string>::size_type i=0; i<tokens.size(); i++)
		val.push_back( stringutils::parseInt(tokens[i]) );
}

void	parseSeq(const std::string& s, std::vector<double>& val, const char* sep, const bool allowEmptyStr)
{
	std::vector<std::string> tokens;
	stringutils::split(s, tokens, sep);
	if (tokens.empty() && !allowEmptyStr)
		throw std::invalid_argument(s + " is not a sequence of double values");
	for (std::vector<std::string>::size_type i=0; i<tokens.size(); i++)
		val.push_back( stringutils::parseDouble(tokens[i]) );
}

void	parseSeq(const std::string& s, std::vector<std::string>& val, const char* sep, const bool allowEmptyStr)
{
	stringutils::split(s, val, sep);
	if (val.empty() && !allowEmptyStr)
		throw std::invalid_argument(s + " is not a sequence of integer values");
}


/*===========================================================================*/

} }























































