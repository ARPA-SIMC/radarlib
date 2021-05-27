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
 *  \brief Functions for string manipulation and conversion
 */ 

#ifndef __RADAR_STRING_HPP__
#define __RADAR_STRING_HPP__

#include <cstring>
#include <string>
#include <sstream>
#include <vector>
#include <utility>
#include <stdexcept>
#include <ctime>

#include <radarlib/defs.h>

#if defined(WIN32)
#define snprintf	_snprintf
#endif

namespace Radar {  

/*!\brief String manipulation functions
 */
namespace stringutils { 

/*===========================================================================*/
/* SPLIT */
/*===========================================================================*/

/*!
 * \brief Splits a string into two parts, using the given separator
 * \param str			the string to split
 * \param first 		a reference to a string where the first part will be copied
 * \param second 		a reference to a string where the second part will be copied
 * \param separator 		the character separator to use. If the parameter is omited the comma character will be used
 */
RADAR_API void		split		(const std::string& str, std::string& first, std::string& second, const char separator = ',');
/*!
 * \brief
 * Splits a string into substrings using the chacatars of a given string as tokens separators
 *
 * \param str			the string to split
 * \param tokens 		a reference to a std::vector of string that will store a copy of each token
 * \param delimiters 		the string that specifiy the tokens separators, if the parameter is omitted only the space charater will be used 
 */
RADAR_API void		split		(const std::string& str, std::vector<std::string>& tokens, const std::string& delimiters = " ");

/*===========================================================================*/
/* TRIM */
/*===========================================================================*/

/*!
 * \brief
 * removes all spaces to the left of a string
 *
 * \param str			the refernce to the string to trim
 * \returns			the reference used for str param
 */
RADAR_API std::string&	trimleft	(std::string& str);
/*!
 * \brief
 * removes all spaces to the left of a string, building a new string
 *
 * \param str			a constant refernce to string to analize
 * \returns			the new string
 */
RADAR_API std::string	trimleft	(const std::string& str);
/*!
 * \brief
 * removes all spaces to the right of a string
 *
 * \param str			the refernce to the string to trim
 * \returns			the reference used for str param
 */
RADAR_API std::string&	trimright	(std::string& str);
/*!
 * \brief
 * removes all spaces to the right of a string, building a new string
 *
 * \param str			a constant refernce to string to analize
 * \returns			the new string
 */
RADAR_API std::string	trimright	(const std::string& str);
/*!
 * \brief
 * remove all space to the left and the right of a string
 *
 * \param str			the refernce to the string to trim
 * \returns			the reference used for str param
 */
RADAR_API std::string&	trim		(std::string& str);
/*!
 * \brief
 * removes all spaces to the left and the right of a string, building a new string
 *
 * \param str			a constant refernce to string to analize
 * \returns			the new string
 */
RADAR_API std::string	trim		(const std::string& str);

/*===========================================================================*/
/* TO STRING */
/*===========================================================================*/

/*!
 * \brief
 * Convert a value to its string rapresentation.
 *
 * Convert a value to its string rapresentation.
 * The type of the value to convert must be of the same type specified with the template syntax
 * \param value			the value to convert
 * \returns			the string representation of value
 */
template<class T> std::string toString(const T& value)
{
	std::ostringstream stream; stream << std::fixed << value; return stream.str();
}

/*!
 * \brief
 * Convert a boolean value to its string rapresentation (0/1).
 *
 * \param val			the value to convert
 * \returns			the string representation of value
 */
RADAR_API std::string toString(bool val);
/*!
 * \brief
 * Convert a int value to its string rapresentation .
 *
 * \param val			the value to convert
 * \returns			the string representation of value
 */
RADAR_API std::string toString(int val);
/*!
 * \brief
 * Convert a long value to its string rapresentation.
 *
 * \param val			the value to convert
 * \returns			the string representation of value
 */
RADAR_API std::string toString(long val);
/*!
 * \brief
 * Convert a float value to its string rapresentation.
 *
 * \param val			the value to convert
 * \returns			the string representation of value
 */
RADAR_API std::string toString(float val);
/*!
 * \brief
 * Convert a double value to its string rapresentation.
 *
 * \param val			the value to convert
 * \returns			the string representation of value
 */
RADAR_API std::string toString(double val);
/*!
 * \brief
 * Convert a size_t value to its string rapresentation.
 *
 * \param val			the value to convert
 * \returns			the string representation of value
 */
RADAR_API std::string toString(size_t val);

/*!
 * \brief
 * Convert a std::vector to a string.
 *
 * Convert a std::vector to a string, converting the vector values to their string representation.
 * If no separator is specified, the comma character will be used
 * The vector elements type is specified using template syntax
 * \param val			a reference to the vector to convert
 * \param sep			the value separator to use
 * \returns			the new string
 */
template<class T> std::string toString(const std::vector<T>& val, const char* sep = ",")
{
	std::ostringstream ss;	
	ss << std::fixed;	
	for (size_t i=0; i<val.size(); i++)
	{
		if (i) 
			ss << sep;
		ss << val[i];
	}
	return ss.str();	
}

/*!
 * \brief
 * Convert a std::vector of boolean values to a string.
 *
 * Convert a std::vector of booleans values to a string, converting the vector values to their string representation.
 * If no separator is specified, the comma character will be used
 * \param val			a reference to the vector to convert
 * \param sep			the value separator to use
 * \returns			the new string
 */
RADAR_API std::string toString(const std::vector<bool>& val, const char* sep = ",");
/*!
 * \brief
 * Convert a std::vector of int values to a string.
 *
 * Convert a std::vector of int values to a string, converting the vector values to their string representation.
 * If no separator is specified, the comma character will be used
 * \param val			a reference to the vector to convert
 * \param sep			the value separator to use
 * \returns			the new string
 */
RADAR_API std::string toString(const std::vector<int>& val, const char* sep = ",");
/*!
 * \brief
 * Convert a std::vector of long values to a string.
 *
 * Convert a std::vector of long values to a string, converting the vector values to their string representation.
 * If no separator is specified, the comma character will be used
 * \param val			a reference to the vector to convert
 * \param sep			the value separator to use
 * \returns			the new string
 */
RADAR_API std::string toString(const std::vector<long>& val, const char* sep = ",");
/*!
 * \brief
 * Convert a std::vector of float values to a string.
 *
 * Convert a std::vector of float values to a string, converting the vector values to their string representation.
 * If no separator is specified, the comma character will be used
 * \param val			a reference to the vector to convert
 * \param sep			the value separator to use
 * \returns			the new string
 */
RADAR_API std::string toString(const std::vector<float>& val, const char* sep = ",");
/*!
 * \brief
 * Convert a std::vector of double values to a string.
 *
 * Convert a std::vector of double values to a string, converting the vector values to their string representation.
 * If no separator is specified, the comma character will be used
 * \param val			a reference to the vector to convert
 * \param sep			the value separator to use
 * \returns			the new string
 */
RADAR_API std::string toString(const std::vector<double>& val, const char* sep = ",");
/*!
 * \brief
 * Convert a std::vector of pair values to a string.
 *
 * Convert a std::vector of pair values to a string, converting the pair values to their string representation.\n
 * If no separator is specified, the comma character will be used
 * \param value			a reference to the vector to convert
 * \param sep			the value separator to use
 * \returns			the new string
 */
template <class T> std::string toString(const std::vector<std::pair<T,T> > value, const char* sep = ",")
{
	std::ostringstream ss;		
	for (size_t i=0; i<value.size(); i++)
	{
		if (i) 
			ss << sep;
		ss << toString<T>(value[i].first) << ":" << toString<T>(value[i].second);
	}
	return ss.str();	
}

/*===========================================================================*/
/* PARSE */
/*===========================================================================*/

/*!
 * \brief Parse a std::string to a given type value
 *
 * Convert a std::string to a given type value
 * If no separator is specified, the comma character will be used
 * \param str			a reference to the strint to convert
 * \param typestr		the name of the result type (used for exception message if an error occurs)
 * \returns			the parsed value
 * \throw std::invalid_argument	if the string cannot be converted to the given type
 */
template <class T> static T parse(const std::string& str, const std::string& typestr)
{
	if (!str.empty())  
	{
		T result;
		std::istringstream ss(str);
		if ((ss >> result))
			return result;
	}	
	throw std::invalid_argument("'" + str + "' is not a valid " + typestr + " value");
}

/*!
 * \brief Parse a std::string to a boolean value
 *
 * \param str			a reference to the strint to convert
 * \returns			the parsed value
 * \throw std::invalid_argument	if the string cannot be converted to the given type
 */
RADAR_API bool	 parseBool	(const std::string& str);
/*!
 * \brief Parse a std::string to an int value
 *
 * \param str			a reference to the strint to convert
 * \returns			the parsed value
 * \throw std::invalid_argument	if the string cannot be converted to the given type
 */
RADAR_API int	 parseInt	(const std::string& str);
/*!
 * \brief Parse a std::string to a float value
 *
 * \param str			a reference to the strint to convert
 * \returns			the parsed value
 * \throw std::invalid_argument	if the string cannot be converted to the given type
 */
RADAR_API float	 parseFloat	(const std::string& str);
/*!
 * \brief Parse a std::string to a double value
 *
 * \param str			a reference to the strint to convert
 * \returns			the parsed value
 * \throw std::invalid_argument	if the string cannot be converted to the given type
 */
RADAR_API double parseDouble	(const std::string& str);

/*!
 * \brief Parse a string sequence of boolean values to a std::vector
 *
 * Parse a string sequence of boolean values to a std::vector. \n
 * Values will be extracted using the ginve character as separator
 * \param str			the string containing the sequence of values
 * \param val			the vector that will store the parsed values
 * \param sep			the separato used to split the string
 * \param allowEmptyStr		if false empty strings will cause an exception
  * \throw std::invalid_argument	if the string cannot be splitted or converted
 */
RADAR_API void	parseSeq	(const std::string& str, std::vector<bool>& val, const char* sep = ",", const bool allowEmptyStr = true);
/*!
 * \brief Parse a string sequence of integer values to a std::vector
 *
 * Parse a string sequence of integer values to a std::vector. \n
 * Values will be extracted using the ginve character as separator
 * \param str			the string containing the sequence of values
 * \param val			the vector that will store the parsed values
 * \param sep			the separato used to split the string
 * \param allowEmptyStr		if false empty strings will cause an exception
 * \throw std::invalid_argument	if the string cannot be splitted or converted
 */
RADAR_API void	parseSeq	(const std::string& str, std::vector<int>& val, const char* sep = ",", const bool allowEmptyStr = true);
/*!
 * \brief Parse a string sequence of double values to a std::vector
 *
 * Parse a string sequence of double values to a std::vector. \n
 * Values will be extracted using the ginve character as separator
 * \param str			the string containing the sequence of values
 * \param val			the vector that will store the parsed values
 * \param sep			the separato used to split the string
 * \param allowEmptyStr		if false empty strings will cause an exception
 * \throw std::invalid_argument	if the string cannot be splitted or converted
 */
RADAR_API void	parseSeq	(const std::string& str, std::vector<double>& val, const char* sep = ",", const bool allowEmptyStr = true);
/*!
 * \brief Parse a string sequence of string tokens to a std::vector
 *
 * Parse a string sequence of string tokens to a std::vector. \n
 * Values will be extracted using the ginve character as separator
 * \param str			the string containing the sequence of values
 * \param val			the vector that will store the parsed values
 * \param sep			the separato used to split the string
 * \param allowEmptyStr		if false empty strings will cause an exception
 * \throw std::invalid_argument	if the string cannot be splitted or converted
 */
RADAR_API void	parseSeq	(const std::string& str, std::vector<std::string>& val, const char* sep = ",", const bool allowEmptyStr = true);

/*===========================================================================*/

/*!
 * \brief Check if the string is a number
 *
 * \param str			the string to check
 * \return			True if the string can be converted to a integer or floating point value, false otherwise
 */
RADAR_API bool	isInt		(const std::string& str);

/*===========================================================================*/

} }



#endif























































