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
 *  \brief Classes about attributes groups for OdimH5 objects
 */

#ifndef __RADAR_ODIMH5V21_METADATA_HPP__
#define __RADAR_ODIMH5V21_METADATA_HPP__

#include <string>
#include <sstream>

#include <radarlib/defs.h>
#include <radarlib/odimh5v21_hdf5.hpp>
#include <radarlib/odimh5v21_const.hpp>
#include <radarlib/odimh5v21_support.hpp>
#include <radarlib/odimh5v21_exceptions.hpp>

namespace OdimH5v21 
{

/*===========================================================================*/
/* METADATA GROUP */
/*===========================================================================*/

/*! 
 * \brief Attribute (odim metadata) group
 * 
 * This class represent an attribute collection used to represent odim What, Where and How attribute groups
 * This is a generic class, no checks are made about name or values used for attributes.
 * It is user responsibility to use this class to write and read attributes according to OdimH5 format
 */
class RADAR_API MetadataGroup
{
public:
	/*! 
	 * \brief Create a new metadata group linking it to a HDF5 group object         
	 */
	MetadataGroup(H5::Group* group);
	virtual ~MetadataGroup();
			
	/*! 
	 * \brief Get che number of attributes in the group
	 */
	int	getCount();
	/*! 
	 * \brief Check if an attribute with the given name exists (name is case sensitive)
	 * \param name			the attribute name	
	 * \throws OdimH5Exception	if an unexpected error occurs
	 */
	bool	exists	(const char* name);
	/*! 
	 * \brief Delete the  attribute with the given name (name is case sensitive)
	 * \param name			the attribute name	
	 * \throws OdimH5Exception	if an unexpected error occurs
	 */
	void	remove	(const char* name);
	/*! 
	 * \brief Get pointer to the HDF5 attribute object associated to an attribute 
	 * \param name					the attribute name
	 * \param mandatory				if true, the attribute must be present in the group, otherwise a OdimH5MissingAttributeException will be raised
	 * \throws OdimH5Exception			if an unexpected error occurs
	 * \throws OdimH5MissingAttributeException	if mandatory is true but the attribute is not present
	 */
	H5::Attribute*		getH5Attribute	(const char* name, bool mandatory = false);
	
	/* --- set valori scalari --- */

	/*! 
	 * \brief Set or create an attribute with the given boolean value
	 * 
	 * Boolean values are store ad string values "True" or "False"
	 * \param name					the attribute name
	 * \param value					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	void	set	(const char* name, bool			value);
	/*! 
	 * \brief Set or create an attribute with the given 8 bit signed value
	 * \param name					the attribute name
	 * \param value					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	void	set	(const char* name, char			value);
	/*! 
	 * \brief Set or create an attribute with the given 8 bit unsigned value
	 *
	 * The value will be stored as a 64 bit signed value
	 * \param name					the attribute name
	 * \param value					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	void	set	(const char* name, unsigned char	value);
	/*! 
	 * \brief Set or create an attribute with the given 16 bit signed value
	 *
	 * The value will be stored as a 64 bit signed value
	 * \param name					the attribute name
	 * \param value					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	void	set	(const char* name, short		value);
	/*! 
	 * \brief Set or create an attribute with the given 16 bit unsigned value
	 *
	 * The value will be stored as a 64 bit signed value
	 * \param name					the attribute name
	 * \param value					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	void	set	(const char* name, unsigned short	value);
	/*! 
	 * \brief Set or create an attribute with the given 32 bit signed value
	 *
	 * The value will be stored as a 64 bit signed value
	 * \param name					the attribute name
	 * \param value					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	void	set	(const char* name, int			value);
	/*! 
	 * \brief Set or create an attribute with the given 32 bit unsigned value
	 *
	 * The value will be stored as a 64 bit signed value
	 * \param name					the attribute name
	 * \param value					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	void	set	(const char* name, unsigned int		value);
	/*! 
	 * \brief Set or create an attribute with the given 64 bit signed value
	 *
	 * OdimH5 format does not allow 64 bit unsigned values;
	 * \param name					the attribute name
	 * \param value					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	void	set	(const char* name, int64_t		value);

	/* NOTA: inzialmente pensavo di mettere un metodo specifico per i time_t, ma in realta' cade automaticamente negli altri set visto che e' solo un typedef */

	/*! 
	 * \brief Set or create an attribute with the given 32 bit floating point value
	 *
	 * The value will be stored as a 64 bit floating point value
	 * \param name					the attribute name
	 * \param value					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	void	set	(const char* name, float		value);
	/*! 
	 * \brief Set or create an attribute with the given 64 bit floating point value
	 * \param name					the attribute name
	 * \param value					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	void	set	(const char* name, double		value);	
	/*! 
	 * \brief Set or create an attribute with the given string value
	 * \param name					the attribute name
	 * \param value					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	void	set	(const char* name, const char*		value);	
	/*! 
	 * \brief Set or create an attribute with the given std::string value
	 * \param name					the attribute name
	 * \param value					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	void	set	(const char* name, const std::string&	value);	
	
	/* --- sequenze di scalari ---*/

	/*! 
	 * \brief Set or create a sequence attribute with the given boolean values
	 *
	 * Values are stored as a comma separated string
	 * \param name					the attribute name
	 * \param value					the values to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	void	set	(const char* name, const std::vector<bool>&		value);
	/*! 
	 * \brief Set or create a sequence attribute with the given 8 bit signed values
	 *
	 * Values are stored as a comma separated string
	 * \param name					the attribute name
	 * \param value					the values to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	void	set	(const char* name, const std::vector<char>&		value);
	/*! 
	 * \brief Set or create a sequence attribute with the given 8 bit unsigned values
	 *
	 * Values are stored as a comma separated string
	 * \param name					the attribute name
	 * \param value					the values to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	void	set	(const char* name, const std::vector<unsigned char>&	value);
	/*! 
	 * \brief Set or create a sequence attribute with the given 16 bit signed values
	 *
	 * Values are stored as a comma separated string
	 * \param name					the attribute name
	 * \param value					the values to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	void	set	(const char* name, const std::vector<short>&		value);
	/*! 
	 * \brief Set or create a sequence attribute with the given 16 bit unsigned values
	 *
	 * Values are stored as a comma separated string
	 * \param name					the attribute name
	 * \param value					the values to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	void	set	(const char* name, const std::vector<unsigned short>&	value);
	/*! 
	 * \brief Set or create a sequence attribute with the given 32 bit signed values
	 *
	 * Values are stored as a comma separated string
	 * \param name					the attribute name
	 * \param value					the values to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	void	set	(const char* name, const std::vector<int>&		value);
	/*! 
	 * \brief Set or create a sequence attribute with the given 32 bit unsigned values
	 *
	 * Values are stored as a comma separated string
	 * \param name					the attribute name
	 * \param value					the values to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	void	set	(const char* name, const std::vector<unsigned int>&	value);
	/*! 
	 * \brief Set or create a sequence attribute with the given 64 bit signed values
	 *
	 * Values are stored as a comma separated string
	 * \param name					the attribute name
	 * \param value					the values to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	void	set	(const char* name, const std::vector<int64_t>&		value);
	/*! 
	 * \brief Set or create a sequence attribute with the given 32 bit floating point values
	 *
	 * Values are stored as a comma separated string
	 * \param name					the attribute name
	 * \param value					the values to write
	 * \param precision				the precision to use while converting values to string
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	void	set	(const char* name, const std::vector<float>&		value, int precision = 0);
	/*! 
	 * \brief Set or create a sequence attribute with the given 64 bit floating point values
	 *
	 * Values are stored as a comma separated string
	 * \param name					the attribute name
	 * \param value					the values to write
	 * \param precision				the precision to use while converting values to string
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	void	set	(const char* name, const std::vector<double>&		value, int precision = 0);
	/*! 
	 * \brief Set or create a sequence attribute with the given string values
	 *
	 * Values are stored as a comma separated string
	 * Is use responsibility to remove commas from string values
	 * \param name					the attribute name
	 * \param value					the values to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	void	set	(const char* name, const std::vector<char*>&		value);	
	/*! 
	 * \brief Set or create a sequence attribute with the given string values
	 *
	 * Values are stored as a comma separated string
	 * Is use responsibility to remove commas from string values
	 * \param name					the attribute name
	 * \param value					the values to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	void	set	(const char* name, const std::vector<std::string>&	value);	

	/* --- set sequenze di coppie --- */

	/*! 
	 * \brief Set or create a pairs sequence attribute with the given pairs of 16 bit signed values
	 *
	 * Pairs are stored as a comma separated string with pair values separated by ':'
	 * \param name					the attribute name
	 * \param value					the values to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	void	set	(const char* name, const std::vector<std::pair<short,short> >&		value);	
	/*! 
	 * \brief Set or create a pairs sequence attribute with the given pairs of 32 bit signed values
	 *
	 * Pairs are stored as a comma separated string with pair values separated by ':'
	 * \param name					the attribute name
	 * \param value					the values to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	void	set	(const char* name, const std::vector<std::pair<int,int> >&		value);	
	/*! 
	 * \brief Set or create a pairs sequence attribute with the given pairs of 64 bit signed values
	 *
	 * Pairs are stored as a comma separated string with pair values separated by ':'
	 * \param name					the attribute name
	 * \param value					the values to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	void	set	(const char* name, const std::vector<std::pair<int64_t,int64_t> >&	value);	
	/*! 
	 * \brief Set or create a pairs sequence attribute with the given pairs of 32 bit floating point values
	 *
	 * Pairs are stored as a comma separated string with pair values separated by ':'
	 * \param name					the attribute name
	 * \param value					the values to write
	 * \param precision				the precision to use while converting value to strings
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	void	set	(const char* name, const std::vector<std::pair<float,float> >&		value, int precision = 0);	
	/*! 
	 * \brief Set or create a pairs sequence attribute with the given pairs of 64 bit floating point values
	 *
	 * Pairs are stored as a comma separated string with pair values separated by ':'
	 * \param name					the attribute name
	 * \param value					the values to write
	 * \param precision				the precision to use while converting value to strings
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	void	set	(const char* name, const std::vector<std::pair<double,double> >&	value, int precision = 0);	
	/*! 
	 * \brief Set or create a pairs sequence attribute with the given pairs of string values
	 *
	 * Pairs are stored as a comma separated string with pair values separated by ':'
	 * \param name					the attribute name
	 * \param value					the values to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	void	set	(const char* name, const std::vector<std::pair<std::string,std::string> >&	value);	

	/* --- set di sequenze di valori odim --- */

	/*! 
	 * \brief Set or create a pairs sequence attribute with the given azimuth time pairs
	 *
	 * Pairs are stored as a comma separated string with pair values separated by ':'
         * Azimuth times are stored according to OdimH5 format 'HHMMSS.sss'
	 * \param name					the attribute name
	 * \param value					the values to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	void	set	(const char* name, const std::vector<AZTimes>&		value);
	/*! 
	 * \brief Set or create a pairs sequence attribute with the given azimuth angles pairs
	 *
	 * Pairs are stored as a comma separated string with pair values separated by ':'
         * Pair values are stored with the default STL precision for double values.
	 * \param name					the attribute name
	 * \param value					the values to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	void	set	(const char* name, const std::vector<AZAngles>&		value);
	/*! 
	 * \brief Set or create a pairs sequence attribute with the given azimuth angles pairs
	 *
	 * Pairs are stored as a comma separated string with pair values separated by ':'
         * Pair values are stored with the given precision value.
	 * \param name					the attribute name
	 * \param value					the values to write
	 * \param precision				the precision to use while converting value to strings
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	void	set	(const char* name, const std::vector<AZAngles>&		value, int precision);
	/*! 
	 * \brief Set or create a sequence attribute with the given integration layer height pair
	 * \param name					the attribute name
	 * \param value					the values to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	void	set	(const char* name, const VILHeights&	value);

	/*! 
	 * \brief Set or create a sequence attribute with the given elevation angles
	 *
	 * Values are separated by ':'
         * Values are stored with the default STL precision for double values.
	 * \param name					the attribute name
	 * \param value					the values to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	void	set	(const char* name, const std::vector<Angles>&		value);
  	/*! 
	 * \brief Set or create a sequence attribute with the given elevation angles
	 *
	 * Values are separated by ':'
         * Pair values are stored with the given precision value.
	 * \param name					the attribute name
	 * \param value					the values to write
	 * \param precision				the precision to use while converting value to strings
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	void	set	(const char* name, const std::vector<Angles>&		value, int precision);
	/*! 
	 * \brief Set or create a sequence attribute with the given antenna rotation speeds 
	 *
	 * Values are separated by ':'
         * Values are stored with the default STL precision for double values.
	 * \param name					the attribute name
	 * \param value					the values to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	void	set	(const char* name, const std::vector<Arotation>&		value);
  	/*! 
	 * \brief Set or create a sequence attribute with the given antenna rotation speeds 
	 *
	 * Values are separated by ':'
         * Pair values are stored with the given precision value.
	 * \param name					the attribute name
	 * \param value					the values to write
	 * \param precision				the precision to use while converting value to strings
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	void	set	(const char* name, const std::vector<Arotation>&	value, int precision);
	/*! 
	 * \brief Set or create a sequence attribute with the given radar nodes
	 *
	 * Values are separated by ':'
	 * \param name					the attribute name
	 * \param value					the values to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	void	set	(const char* name, const std::vector<Nodes>&		value);

	/* --- set di altri tipi --- */

	/*! 
	 * \brief Set or create a string attribute with the given string stream
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	void	set	(const char* name, const std::stringstream&	value);	
	/*! 
	 * \brief Set or create a string attribute with the given output string stream
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	void	set	(const char* name, const std::ostringstream&	value);	

	/* --- get valori scalari --- */

	/*! 
	 * \brief Get the value of a boolean attribute
	 *
	 * \param name					the attribute name
	 * \throws OdimH5Exception			if an unexpected error occurs
	 * \throws OdimH5MissingAttributeException	if the attribue does not exists
	 */
	bool				getBool		(const char* name);
	/*! 
	 * \brief Get the value of a boolean attribute
	 *
	 * \param name			the attribute name
	 * \param value			the default value to return if attribute is not found
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	bool				getBool		(const char* name, bool			value);
	/*! 
	 * \brief Get the value of a 64 bit signed attribute converting it to 8bit signed value
	 *
	 * \param name			the attribute name
	 * \throws OdimH5Exception			if an unexpected error occurs
	 * \throws OdimH5MissingAttributeException	if the attribue does not exists
	 */
	char				getChar		(const char* name);
	/*! 
	 * \brief Get the value of a 64 bit signed attribute converting it to 8bit signed value
	 *
	 * \param name			the attribute name
	 * \param value			the default value to return if attribute is not found
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	char				getChar		(const char* name, char			value);
	/*! 
	 * \brief Get the value of a 64 bit signed attribute converting it to 8 bit unsigned value
	 *
	 * \param name			the attribute name
	 * \throws OdimH5Exception			if an unexpected error occurs
	 * \throws OdimH5MissingAttributeException	if the attribue does not exists
	 */
	unsigned char			getUChar	(const char* name);
	/*! 
	 * \brief Get the value of a 64 bit signed attribute converting it to 8 bit unsigned value
	 *
	 * \param name			the attribute name
	 * \param value			the default value to return if attribute is not found
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	unsigned char			getUChar	(const char* name, unsigned char	value);
	/*! 
	 * \brief Get the value of a 64 bit signed attribute converting it to 16 bit signed value
	 *
	 * \param name			the attribute name
	 * \throws OdimH5Exception			if an unexpected error occurs
	 * \throws OdimH5MissingAttributeException	if the attribue does not exists
	 */
	short				getShort	(const char* name);
	/*! 
	 * \brief Get the value of a 64 bit signed attribute converting it to 16 bit signed value
	 *
	 * \param name			the attribute name
	 * \param value			the default value to return if attribute is not found
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	short				getShort	(const char* name, short		value);
	/*! 
	 * \brief Get the value of a 64 bit signed attribute converting it to 16 bit unsigned value
	 *
	 * \param name			the attribute name
	 * \throws OdimH5Exception			if an unexpected error occurs
	 * \throws OdimH5MissingAttributeException	if the attribue does not exists
	 */
	unsigned short			getUShort	(const char* name);
	/*! 
	 * \brief Get the value of a 64 bit signed attribute converting it to 16 bit unsigned value
	 *
	 * \param name			the attribute name
	 * \param value			the default value to return if attribute is not found
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	unsigned short			getUShort	(const char* name, unsigned short	value);
	/*! 
	 * \brief Get the value of a 64 bit signed attribute converting it to 32 bit signed value
	 *
	 * \param name			the attribute name
	 * \throws OdimH5Exception			if an unexpected error occurs
	 * \throws OdimH5MissingAttributeException	if the attribue does not exists
	 */
	int				getInt		(const char* name);
	/*! 
	 * \brief Get the value of a 64 bit signed attribute converting it to 32 bit signed value
	 *
	 * \param name			the attribute name
	 * \param value			the default value to return if attribute is not found
	 * \param value					the value to return if the attribute does not exists
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	int				getInt		(const char* name, int			value);
	/*! 
	 * \brief Get the value of a 64 bit signed attribute converting it to 32 bit unsigned value
	 *
	 * \param name			the attribute name
	 * \throws OdimH5Exception			if an unexpected error occurs
	 * \throws OdimH5MissingAttributeException	if the attribue does not exists
	 */
	unsigned int			getUInt		(const char* name);
	/*! 
	 * \brief Get the value of a 64 bit signed attribute converting it to 32 bit unsigned value
	 *
	 * \param name			the attribute name
	 * \param value			the default value to return if attribute is not found
	 * \param value					the value to return if the attribute does not exists
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	unsigned int			getUInt		(const char* name, unsigned int		value);
	/*! 
	 * \brief Get the value of a 64 bit signed attribute 
	 *
	 * \param name			the attribute name
	 * \throws OdimH5Exception			if an unexpected error occurs
	 * \throws OdimH5MissingAttributeException	if the attribue does not exists
	 */
	int64_t				getLong		(const char* name);
	/*! 
	 * \brief Get the value of a 64 bit signed attribute 
	 *
	 * \param name			the attribute name
	 * \param value			the default value to return if attribute is not found
	 * \throws OdimH5Exception			if an unexpected error occurs
	 * \throws OdimH5MissingAttributeException	if the attribue does not exists
	 */
	int64_t				getLong		(const char* name, int64_t		value);
	/*! 
	 * \brief Get the value of a 64 bit signed attribute converting it to time_t value
	 *
	 * \param name			the attribute name
	 * \throws OdimH5Exception			if an unexpected error occurs
	 * \throws OdimH5MissingAttributeException	if the attribue does not exists
	 */
	time_t				getTimeT	(const char* name);
	/*! 
	 * \brief Get the value of a 64 bit signed attribute converting it to time_t value
	 *
	 * \param name			the attribute name
	 * \param value			the default value to return if attribute is not found
	 * \param value					the value to return if the attribute does not exists
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	time_t				getTimeT	(const char* name, time_t		value);
	/*! 
	 * \brief Get the value of a 64 bit floating point attribute converting it to 32 bit floating point value
	 *
	 * \param name			the attribute name
	 * \throws OdimH5Exception			if an unexpected error occurs
	 * \throws OdimH5MissingAttributeException	if the attribue does not exists
	 */
	float				getFloat	(const char* name);
	/*! 
	 * \brief Get the value of a 64 bit floating point attribute converting it to 32 bit floating point value
	 *
	 * \param name			the attribute name
	 * \param value			the default value to return if attribute is not found
	 * \throws OdimH5Exception			if an unexpected error occurs
	 * \throws OdimH5MissingAttributeException	if the attribue does not exists
	 */
	float				getFloat	(const char* name, float		value);
	/*! 
	 * \brief Get the value of a 64 bit floating point attribute
	 *
	 * \param name			the attribute name
	 * \throws OdimH5Exception			if an unexpected error occurs
	 * \throws OdimH5MissingAttributeException	if the attribue does not exists
	 */
	double				getDouble	(const char* name);
	/*! 
	 * \brief Get the value of a 64 bit floating point attribute
	 *
	 * \param name			the attribute name
	 * \param value			the default value to return if attribute is not found
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	double				getDouble	(const char* name, double		value);
	/*! 
	 * \brief Get the value of a string attribute
	 *
	 * \param name			the attribute name
	 * \throws OdimH5Exception			if an unexpected error occurs
	 * \throws OdimH5MissingAttributeException	if the attribue does not exists
	 */
	std::string			getStr		(const char* name);		
	/*! 
	 * \brief Get the value of a string attribute
	 *
	 * \param name			the attribute name
	 * \param value			the default value to return if attribute is not found
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	std::string			getStr		(const char* name, const std::string& 	value);		

	/* --- get sequenze di scalari --- */

	/*! 
	 * \brief Get the value of a sequence attribute converting it to boolean values
	 *	 
	 * \param name			the attribute name
	 * \param mandatory				throw exception if attribute is not found
	 * \throws OdimH5MissingAttributeException	if mandatory is true and the attribue does not exists
	 * \throws OdimH5FormatException		if a conversion error occurred
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	std::vector<bool>		getBools	(const char* name, bool mandatory = false);
	/*! 
	 * \brief Get the value of a sequence attribute converting it to 8 bit signed values
	 *	 
	 * \param name			the attribute name
	 * \param mandatory				throw exception if attribute is not found
	 * \throws OdimH5MissingAttributeException	if mandatory is true and the attribue does not exists
	 * \throws OdimH5FormatException		if a conversion error occurred
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	std::vector<char>		getChars	(const char* name, bool mandatory = false);
	/*! 
	 * \brief Get the value of a sequence attribute converting it to 8 bit unsigned values
	 *	 
	 * \param name			the attribute name
	 * \param mandatory				throw exception if attribute is not found
	 * \throws OdimH5MissingAttributeException	if mandatory is true and the attribue does not exists
	 * \throws OdimH5FormatException		if a conversion error occurred
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	std::vector<unsigned char>	getUChars	(const char* name, bool mandatory = false);
	/*! 
	 * \brief Get the value of a sequence attribute converting it to 16 bit signed values
	 *	 
	 * \param name			the attribute name
	 * \param mandatory				throw exception if attribute is not found
	 * \throws OdimH5MissingAttributeException	if mandatory is true and the attribue does not exists
	 * \throws OdimH5FormatException		if a conversion error occurred
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	std::vector<short>		getShorts	(const char* name, bool mandatory = false);
	/*! 
	 * \brief Get the value of a sequence attribute converting it to 16 bit unsigned values
	 *	 
	 * \param name			the attribute name
	 * \param mandatory				throw exception if attribute is not found
	 * \throws OdimH5MissingAttributeException	if mandatory is true and the attribue does not exists
	 * \throws OdimH5FormatException		if a conversion error occurred
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	std::vector<unsigned short>	getUShorts	(const char* name, bool mandatory = false);
	/*! 
	 * \brief Get the value of a sequence attribute converting it to 32 bit signed values
	 *	 
	 * \param name			the attribute name
	 * \param mandatory				throw exception if attribute is not found
	 * \throws OdimH5Exception			if an unexpected error occurs
	 * \throws OdimH5MissingAttributeException	if mandatory is true and the attribue does not exists
	 * \throws OdimH5FormatException		if a conversion error occurred
	 */
	std::vector<int>		getInts		(const char* name, bool mandatory = false);
	/*! 
	 * \brief Get the value of a sequence attribute converting it to 32 bit unsigned values
	 *	 
	 * \param name			the attribute name
	 * \param mandatory				throw exception if attribute is not found
	 * \throws OdimH5Exception			if an unexpected error occurs
	 * \throws OdimH5MissingAttributeException	if mandatory is true and the attribue does not exists
	 * \throws OdimH5FormatException		if a conversion error occurred
	 */
	std::vector<unsigned int>	getUInts	(const char* name, bool mandatory = false);
	/*! 
	 * \brief Get the value of a sequence attribute converting it to 64 bit signed values
	 *	 
	 * \param name			the attribute name
	 * \param mandatory				throw exception if attribute is not found
	 * \throws OdimH5Exception			if an unexpected error occurs
	 * \throws OdimH5MissingAttributeException	if mandatory is true and the attribue does not exists
	 * \throws OdimH5FormatException		if a conversion error occurred
	 */
	std::vector<int64_t>		getLongs	(const char* name, bool mandatory = false);
	/*! 
	 * \brief Get the value of a sequence attribute converting it to time_t values
	 *	 
	 * \param name			the attribute name
	 * \param mandatory				throw exception if attribute is not found
	 * \throws OdimH5Exception			if an unexpected error occurs
	 * \throws OdimH5MissingAttributeException	if mandatory is true and the attribue does not exists
	 * \throws OdimH5FormatException		if a conversion error occurred
	 */
	std::vector<time_t>		getTimes	(const char* name, bool mandatory = false);
	/*! 
	 * \brief Get the value of a sequence attribute converting it to 32 bit floating point values
	 *	 
	 * \param name			the attribute name
	 * \param mandatory				throw exception if attribute is not found
	 * \throws OdimH5Exception			if an unexpected error occurs
	 * \throws OdimH5MissingAttributeException	if mandatory is true and the attribue does not exists
	 * \throws OdimH5FormatException		if a conversion error occurred
	 */
	std::vector<float>		getFloats	(const char* name, bool mandatory = false);
	/*! 
	 * \brief Get the value of a sequence attribute converting it to 64 bit floating point values
	 *	 
	 * \param name			the attribute name
	 * \param mandatory				throw exception if attribute is not found
	 * \throws OdimH5Exception			if an unexpected error occurs
	 * \throws OdimH5MissingAttributeException	if mandatory is true and the attribue does not exists
	 * \throws OdimH5FormatException		if a conversion error occurred
	 */
	std::vector<double>		getDoubles	(const char* name, bool mandatory = false);
	/*! 
	 * \brief Get the value of a sequence attribute converting it to string values
	 *	 
	 * \param name			the attribute name
	 * \param mandatory				throw exception if attribute is not found
	 * \throws OdimH5Exception			if an unexpected error occurs
	 * \throws OdimH5MissingAttributeException	if mandatory is true and the attribue does not exists
	 * \throws OdimH5FormatException		if a conversion error occurred
	 */
	std::vector<std::string>	getStrings	(const char* name, bool mandatory = false);		

	/*!
	 * \brief Get the value of the long simple array
	 */
	std::vector<int64_t> getSimpleArrayLong (const char* name, bool mandatory = false);
	/*!
	 * \brief Get the value of the float simple array
	 */
	std::vector<double> getSimpleArrayDouble (const char* name, bool mandatory = false);

	/* --- get sequenze di coppie --- */

	/*! 
	 * \brief Get the value of a sequence attribute converting it to 16 bit signed value pairs
	 *	 
	 * \param name			the attribute name
	 * \param mandatory				throw exception if attribute is not found
	 * \throws OdimH5Exception			if an unexpected error occurs
	 * \throws OdimH5MissingAttributeException	if mandatory is true and the attribue does not exists
	 * \throws OdimH5FormatException		if a conversion error occurred
	 */
	std::vector<std::pair<short,short> >			getShortPairs		(const char* name, bool mandatory = false);	
	/*! 
	 * \brief Get the value of a sequence attribute converting it to 32 bit signed value pairs
	 *	 
	 * \param name			the attribute name
	 * \param mandatory				throw exception if attribute is not found
	 * \throws OdimH5Exception			if an unexpected error occurs
	 * \throws OdimH5MissingAttributeException	if mandatory is true and the attribue does not exists
	 * \throws OdimH5FormatException		if a conversion error occurred
	 */
	std::vector<std::pair<int,int> >			getIntPairs		(const char* name, bool mandatory = false);	
	/*! 
	 * \brief Get the value of a sequence attribute converting it to 64 bit signed value pairs
	 *	 
	 * \param name			the attribute name
	 * \param mandatory				throw exception if attribute is not found
	 * \throws OdimH5Exception			if an unexpected error occurs
	 * \throws OdimH5MissingAttributeException	if mandatory is true and the attribue does not exists
	 * \throws OdimH5FormatException		if a conversion error occurred
	 */
	std::vector<std::pair<int64_t,int64_t> >		getLongPairs		(const char* name, bool mandatory = false);	
	/*! 
	 * \brief Get the value of a sequence attribute converting it to 32 bit floating point value pairs
	 *	 
	 * \param name			the attribute name
	 * \param mandatory				throw exception if attribute is not found
	 * \throws OdimH5Exception			if an unexpected error occurs
	 * \throws OdimH5MissingAttributeException	if mandatory is true and the attribue does not exists
	 * \throws OdimH5FormatException		if a conversion error occurred
	 */
	std::vector<std::pair<float,float> >			getFloatPairs		(const char* name, bool mandatory = false);	
	/*! 
	 * \brief Get the value of a sequence attribute converting it to 64 bit floating point value pairs
	 *	 
	 * \param name			the attribute name
	 * \param mandatory				throw exception if attribute is not found
	 * \throws OdimH5Exception			if an unexpected error occurs
	 * \throws OdimH5MissingAttributeException	if mandatory is true and the attribue does not exists
	 * \throws OdimH5FormatException		if a conversion error occurred
	 */
	std::vector<std::pair<double,double> >			getDoublePairs		(const char* name, bool mandatory = false);	
	/*! 
	 * \brief Get the value of a sequence attribute converting it to string pairs
	 *	 
	 * \param name			the attribute name
	 * \param mandatory				throw exception if attribute is not found
	 * \throws OdimH5Exception			if an unexpected error occurs
	 * \throws OdimH5MissingAttributeException	if mandatory is true and the attribue does not exists
	 * \throws OdimH5FormatException		if a conversion error occurred
	 */
	const std::vector<std::pair<std::string,std::string> >	getStrPairs		(const char* name, bool mandatory = false);	

	/* --- get casi particolari --- */

	/*! 
	 * \brief Get the value of a sequence attribute converting it to azimuth time pairs
	 *	 
	 * \param name					the attribute to read
	 * \throws OdimH5Exception			if an unexpected error occurs
	 * \throws OdimH5MissingAttributeException	if mandatory is true and the attribue does not exists
	 * \throws OdimH5FormatException		if a conversion error occurred
	 */
	std::vector<AZTimes>		getAZTimes	(const char* name);
	/*! 
	 * \brief Get the value of a sequence attribute converting it to azimuth angle pairs
	 *	 
	 * \param name					the attribute to read
	 * \throws OdimH5Exception			if an unexpected error occurs
	 * \throws OdimH5MissingAttributeException	if mandatory is true and the attribue does not exists
	 * \throws OdimH5FormatException		if a conversion error occurred
	 */
	std::vector<AZAngles>		getAZAngles	(const char* name);	
	/*! 
	 * \brief Get the value of a sequence attribute converting it to vertical height pairs
	 *	 
	 * \param name					the attribute to read
	 * \throws OdimH5Exception			if an unexpected error occurs
	 * \throws OdimH5MissingAttributeException	if mandatory is true and the attribue does not exists
	 * \throws OdimH5FormatException		if a conversion error occurred
	 */
	VILHeights			getVILHeights	(const char* name);

	/*! 
	 * \brief Get the value of a sequence attribute converting it to elevation angle
	 *	 
	 * \param name					the attribute to read
	 * \throws OdimH5Exception			if an unexpected error occurs
	 * \throws OdimH5MissingAttributeException	if mandatory is true and the attribue does not exists
	 * \throws OdimH5FormatException		if a conversion error occurred
	 */
	std::vector<Angles>		getAngles	(const char* name);	

	/*! 
	 * \brief Get the value of a sequence attribute converting it to antenna rotation speed
	 *	 
	 * \param name					the attribute to read
	 * \throws OdimH5Exception			if an unexpected error occurs
	 * \throws OdimH5MissingAttributeException	if mandatory is true and the attribue does not exists
	 * \throws OdimH5FormatException		if a conversion error occurred
	 */
	std::vector<Arotation>		getArotation	(const char* name);	

	/*! 
	 * \brief Get the value of a sequence attribute converting it to radar nodes
	 *	 
	 * \param name					the attribute to read
	 * \throws OdimH5Exception			if an unexpected error occurs
	 * \throws OdimH5MissingAttributeException	if mandatory is true and the attribue does not exists
	 * \throws OdimH5FormatException		if a conversion error occurred
	 */
	std::vector<Nodes>		getNodes	(const char* name);	

	/* --- altre funzioni --- */

	/*! 
	 * \brief Copy/write all attributes from the given group to this group
	 *	 
	 * \param group					the source group to copy from
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	void import(MetadataGroup* group);
	/*! 
	 * \brief Copy/write all given attributes from the given group to this group
	 *	 
	 * \param group					the source group to copy from
	 * \param names					attributes to copy
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	void import(MetadataGroup* group, const std::set<std::string>& names);


	/*! 
	 * \brief Get a reference to the underneath HDF5 group object
	 */
	H5::Group*		getH5Object	() const { return group; }

	/*==============================================================*/

	/*! 
	 * \brief Static method to write OdimH5 Conventions attribute into given group
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	static void setConventions(H5::Group* root)
	{
		HDF5Attribute::set(root, OdimH5v21::ATTRIBUTE_ROOT_CONVENTIONS, OdimH5v21::CONVENTIONS_ODIM_H5_V2_1);
	}
	/*! 
	 * \brief Static method to read OdimH5 Conventions attribute from a given group
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	static std::string getConventions(H5::Group* root)
	{			
		return HDF5Attribute::getStr(root, OdimH5v21::ATTRIBUTE_ROOT_CONVENTIONS);
	}

private: 
	H5::Group* group;
};

/*===========================================================================*/
/* WHAT METADATA */
/*===========================================================================*/

/*! 
 * \brief Interface fot WHAT root attributes methods
 *
 * This interface declare the methods to read and write root WHAT attributes
 */
class RADAR_API WHATRootMetadata
{
public:
	/*! 
	 * \brief Get the value of 'object' attribute
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual std::string		getObject	()				= 0;
	/*! 
	 * \brief Set the value of 'object' attribute
	 * \param val					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setObject	(const std::string& val)	= 0;
	/*! 
	 * \brief Get the value of 'version' attribute
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual std::string		getVersion	()				= 0;
	/*! 
	 * \brief Set the value of 'version' attribute
	 * \param val					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setVersion	(const std::string& val)	= 0;
	/*! 
	 * \brief Set the value of 'date' and 'time' attributes
	 * 
	 * Set the value of 'date' and 'time' attributes using the given time_t value 
	 * \param val					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setDateTime	(const time_t val)		= 0;
	/*! 
	 * \brief Get the joined value of 'date' and 'time' attributes
	 * 
	 * Get the joined value of 'date' and 'time' attributes in a single time_t value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual time_t			getDateTime	()				= 0;
	/*! 
	 * \brief Get the value of 'source' attribute
	 * \returns A SourceInfo object ottained parsing the 'source' attribute
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual SourceInfo		getSource	()				= 0;
	/*! 
	 * \brief Set the value of 'source' attribute 
	 * 
	 * Set the value of 'source' attribute according to OdimH5 format, using the values stored in a SourceInfo object
	 * \param val					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setSource	(const SourceInfo& val)		= 0;
};

/*! 
 * \brief Interface fot WHAT dataset attributes methods
 */
class RADAR_API WHATDatasetMetadata : public WHATRootMetadata
{
public:
	/*! 
	 * \brief Get the value of 'product' attribute
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual std::string		getProduct		()					= 0;
	/*! 
	 * \brief Set the value of 'product' attribute
	 * \param val					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setProduct		(const std::string& val)		= 0;
	/*! 
	 * \brief Set the value of 'prodpar' attribute
	 *
	 * This method is used only for some kind of products
	 * \param val					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setProdPar		(double val)				= 0;
	/*! 
	 * \brief Set the value of 'prodpar' attribute using the given VILHeights values
	 * 
	 * Set the value of 'prodpar' attribute using the given VILHeights values
	 * This method is used only for some kind of products
	 * \param val					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setProdPar		(const VILHeights& val)	= 0;	
	/*! 
	 * \brief Get the value of 'prodpar' attribute as double value
	 * 
	 * This method is used only for some kind of products
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual double			getProdPar		()					= 0;
	/*! 
	 * \brief Get the value of 'prodpar' attribute as VILHeights pair
	 * 
	 * This method is used only for some kind of products
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual VILHeights		getProdParVIL		()					= 0;
	/*! 
	 * \brief Set the value of 'quantity' attribute
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual std::string		getQuantity		()					= 0;
	/*! 
	 * \brief Get the value of 'quantity' attribute
	 * \param val					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setQuantity		(const std::string& val)		= 0;
	/*! 
	 * \brief Set the value of 'startdate' and 'starttime' attributes
	 * 
	 * Set the value of 'startdate' and 'starttime' attributes using the given absolute time_t value
	 * \param val					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setStartDateTime	(time_t val)		= 0;
	/*! 
	 * \brief Get the value of 'startdate' and 'starttime' attributes
	 * 
	 * Get the value of 'startdate' and 'starttime' attributes joined into a time_t value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual time_t			getStartDateTime	()			= 0;
	/*! 
	 * \brief Set the value of 'enddate' and 'endtime' attributes
	 * 
	 * Set the value of 'enddate' and 'endtime' attributes using the given absolute time_t value
	 * \param val					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setEndDateTime		(time_t val)		= 0;
	/*! 
	 * \brief Get the value of 'enddate' and 'endtime' attributes
	 * 
	 * Get the value of 'enddate' and 'endtime' attributes joined into a time_t value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual time_t			getEndDateTime		()			= 0;
	/*! 
	 * \brief Get the value of 'gain' attribute
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual double			getGain			()			= 0;
	/*! 
	 * \brief Set the value of 'gain' attribute
	 * \param val					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setGain			(double val)		= 0;
	/*! 
	 * \brief Get the value of 'offset' attribute
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual double			getOffset		()			= 0;
	/*! 
	 * \brief Set the value of 'offset' attribute
	 * \param val					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setOffset		(double val)		= 0;
	/*! 
	 * \brief Get the value of 'nodata' attribute
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual double			getNodata		()			= 0;
	/*! 
	 * \brief Set the value of 'nodata' attribute
	 * \param val					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setNodata		(double val)		= 0;
	/*! 
	 * \brief Get the value of 'undetect' attribute
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual double			getUndetect		()			= 0;
	/*! 
	 * \brief Set the value of 'undetect' attribute
	 * \param val					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setUndetect		(double val)		= 0;
};

/*===========================================================================*/
/* WHERE METADATA */
/*===========================================================================*/

/*! 
 * \brief Interface fot WHERE root attributes methods
 */
class RADAR_API WHERERootMetadata 
{
public:
	virtual double			getLongitude		()		= 0;
	/*! 
	 * \brief Set the value of 'longitude' attribute
	 * \param val					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setLongitude		(double val)	= 0;
	/*! 
	 * \brief Get the value of 'longitude' attribute
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual double			getLatitude		()		= 0;
	/*! 
	 * \brief Set the value of 'latitude' attribute
	 * \param val					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setLatitude		(double val)	= 0;
	/*! 
	 * \brief Get the value of 'altitude' attribute
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual double			getAltitude		()		= 0;
	/*! 
	 * \brief Set the value of 'altitude' attribute
	 * \param val					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setAltitude		(double val)	= 0;
};

/*! 
 * \brief Interface fot WHERE dataset attributes methods for polar scan 
 */
class RADAR_API WHEREScanMetadata : public WHERERootMetadata
{
public:
	/*! 
	 * \brief Get the 'elangle' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual double			getEAngle		()		= 0;
	/*! 
	 * \brief Set the 'elangle' attribute value
	 * \param val					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setEAngle		(double val)	= 0;
	/*! 
	 * \brief Get the 'numbins' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual int			getNumBins		()		= 0;
	/*! 
	 * \brief Set the 'numbins' attribute value
	 * \param val					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setNumBins		(int val)	= 0;
	/*! 
	 * \brief Get the 'rstart' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual double			getRangeStart		()		= 0;
	/*! 
	 * \brief Set the 'rstart' attribute value
	 * \param val					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setRangeStart		(double val)	= 0;
	/*! 
	 * \brief Get the 'rscale' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual double			getRangeScale		()		= 0;
	/*! 
	 * \brief Set the 'rscale' attribute value
	 * \param val					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setRangeScale		(double val)	= 0;
	/*! 
	 * \brief Get the 'numrays' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual int			getNumRays		()		= 0;
	/*! 
	 * \brief Set the 'numrays' attribute value
	 * \param val					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setNumRays		(int val)	= 0;
	/*! 
	 * \brief Get the 'a1gate' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual int			getA1Gate		()		= 0;
	/*! 
	 * \brief Set the 'a1gate' attribute value
	 * \param val					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setA1Gate		(int val)	= 0;
};

/*! 
 * \brief Interface fot WHERE dataset attributes methods for sector scan
 */
class RADAR_API WHERESectorMetadata : public WHEREScanMetadata
{
public:
	/*! 
	 * \brief Get the 'startaz' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual double			getStartAzimuth		()		= 0;
	/*! 
	 * \brief Set the 'startaz' attribute value
	 * \param val					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setStartAzimuth		(double val)	= 0;
	/*! 
	 * \brief Get the 'stopaz' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual double			setStopAzimuth		()		= 0;
	/*! 
	 * \brief Set the 'stopaz' attribute value
	 * \param val					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setStopAzimuth		(double val)	= 0;
};

/*! 
 * \brief Interface fot WHERE dataset attributes methods for vertical profile
 */
class RADAR_API WHEREVPMetadata : public WHERERootMetadata
{
public:
	/*! 
	 * \brief Get the 'levels' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual int			getLevels		()		= 0;
	/*! 
	 * \brief Set the 'levels' attribute value
	 * \param val					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setLevels		(int val)	= 0;	
	/*! 
	 * \brief Get the 'interval' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual double			getInterval		()		= 0;
	/*! 
	 * \brief Set the 'interval' attribute value
	 * \param val					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setInterval		(double val)	= 0;
	/*! 
	 * \brief Set the 'minheight' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual double			getMinAltitude		()		= 0;
	/*! 
	 * \brief Get the 'minheight' attribute value
	 * \param val					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setMinAltitude		(double val)	= 0;
	/*! 
	 * \brief Get the 'maxheight' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual double			getMaxAltitude		()		= 0;
	/*! 
	 * \brief Set the 'maxheight' attribute value
	 * \param val					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setMaxAltitude		(double val)	= 0;
}; 

/*! 
 * \brief Interface fot WHERE dataset attributes methods for images
 */
class RADAR_API WHEREImageMetadata //: public WHERERootMetadata
{
public:
	/*! 
	 * \brief Get the 'projection arguments' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual std::string		getProjectionArguments	() = 0;
	/*! 
	 * \brief Set the 'projection arguments' attribute value
	 * \param val					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setProjectionArguments	(const std::string& val) = 0;

	/*! 
	 * \brief Get the 'X size' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual int			getXSize		()		= 0;
	/*! 
	 * \brief Set the 'X size' attribute value
	 * \param val					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setXSize		(int val)	= 0;
	/*! 
	 * \brief Get the 'Y size' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual int			getYSize		()		= 0;
	/*! 
	 * \brief Set the 'Y size' attribute value
	 * \param val					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setYSize		(int val)	= 0;
	/*! 
	 * \brief Get the 'X scale' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual double			getXScale		()		= 0;
	/*! 
	 * \brief Set the 'X scale' attribute value
	 * \param val					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setXScale		(double val)	= 0;
	/*! 
	 * \brief Get the 'Y scale' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual double			getYScale		()		= 0;
	/*! 
	 * \brief Set the 'Y scale' attribute value
	 * \param val					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setYScale		(double val)	= 0;

	/*! 
	 * \brief Get the 'LowerLeft Longitude' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual double			getLL_Longitude		()		= 0;
	/*! 
	 * \brief Set the 'LowerLeft Longitude' attribute value
	 * \param val					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setLL_Longitude		(double val)	= 0;
	/*! 
	 * \brief Get the 'LowerLeft Latitude' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual double			getLL_Latitude		()		= 0;
	/*! 
	 * \brief Set the 'LowerLeft Latitude' attribute value
	 * \param val					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setLL_Latitude		(double val)	= 0;
	/*! 
	 * \brief Get the 'UpperLeft Longitude' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual double			getUL_Longitude		()		= 0;
	/*! 
	 * \brief Set the 'UpperLeft Longitude' attribute value
	 * \param val					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setUL_Longitude		(double val)	= 0;
	/*! 
	 * \brief Get the 'UpperLeft Latitude' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual double			getUL_Latitude		()		= 0;
	/*! 
	 * \brief Set the 'UpperLeft Latitude' attribute value
	 * \param val					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setUL_Latitude		(double val)	= 0;

	/*! 
	 * \brief Get the 'UpperRight Longitude' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual double			getUR_Longitude		()		= 0;
	/*! 
	 * \brief Set the 'UpperRight Longitude' attribute value
	 * \param val					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setUR_Longitude		(double val)	= 0;
	/*! 
	 * \brief Get the 'UpperRight Latitude' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual double			getUR_Latitude		()		= 0;
	/*! 
	 * \brief Set the 'UpperRight Latitude' attribute value
	 * \param val					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setUR_Latitude		(double val)	= 0;

	/*! 
	 * \brief Get the 'LowerRight Longitude' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual double			getLR_Longitude		()		= 0;
	/*! 
	 * \brief Set the 'LowerRight Longitude' attribute value
	 * \param val					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setLR_Longitude		(double val)	= 0;
	/*! 
	 * \brief Get the 'LowerRight Latitude' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual double			getLR_Latitude		()		= 0;
	/*! 
	 * \brief Set the 'LowerRight Latitude' attribute value
	 * \param val					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setLR_Latitude		(double val)	= 0;
};

/*! 
 * \brief Interface for WHERE dataset attributes methods for XSEC
 */
class RADAR_API WHEREXSECMetadata //: public WHERERootMetadata
{
public:
	/*! 
	 * \brief Get the 'X size' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual int			getXSize		()		= 0;
	/*! 
	 * \brief set the 'X size' attribute value
	 * \param val					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setXSize		(int val)	= 0;
	/*! 
	 * \brief Get the 'Y size' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual int			getYSize		()		= 0;
	/*! 
	 * \brief set the 'Y size' attribute value
	 * \param val					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setYSize		(int val)	= 0;
	/*! \
	 * \brief get the 'X scale' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual double			getXScale		()		= 0;
	/*! 
	 * \brief set the 'X scale' attribute value
	 * \param val					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setXScale		(double val)	= 0;
	/*! 
	 * \brief Get the 'Y scale' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual double			getYScale		()		= 0;
	/*! 
	 * \brief set the 'Y scale' attribute value
	 * \param val					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setYScale		(double val)	= 0;
	/*! 
	 * \brief Get the 'Min Height' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual double			getMinHeight		()		= 0;
	/*! 
	 * \brief set the 'Min Height' attribute value
	 * \param val					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setMinHeight		(double val)	= 0;
	/*! 
	 * \brief Get the 'Max Height' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual double			getMaxHeight		()		= 0;
	/*! 
	 * \brief set the 'Max Height' attribute value
	 * \param val					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setMaxHeight		(double val)	= 0;
};

/*! 
 * \brief Interface for WHERE dataset attributes methods for RHI
 */
class RADAR_API WHERERhiMetadata // : public WHERE_XSEC_DatasetMetadata
{
public:
	/*! 
	 * \brief Get the 'RHI longitude' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
        virtual double			getRHILon		()		= 0;
	/*! 
	 * \brief set the 'RHI Longitude' attribute value
	 * \param val					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
        virtual void			setRHILon		(double val)	= 0;
	/*! 
	 * \brief Get the 'RHI Latitude' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
        virtual double			getRHILat		()		= 0;
	/*! 
	 * \brief set the 'RHI Latitude' attribute value
	 * \param val					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
        virtual void			setRHILat		(double val)	= 0;
	/*! 
	 * \brief Get the 'Azimuth Angles' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual double			getAzimuthAngle		()		= 0;
	/*! 
	 * \brief set the 'Azimuth Angles' attribute value
	 * \param val					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setAzimuthAngle		(double val)	= 0;
	/*! 
	 * \brief Get the 'Angles' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual std::vector<Angles>	getAngles		()		= 0;
	/*! 
	 * \brief set the 'Angles' attribute value
	 * \param val					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setAngles		(const std::vector<Angles>& val) = 0;
	/*! 
	 * \brief Get the 'Range' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual double			getRange		()		= 0;
	/*! 
	 * \brief set the 'Range' attribute value
	 * \param val					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setRange		(double val)	= 0;
};

/*! 
 * \brief Interface for WHERE dataset attributes methods for Panel 
 */
class RADAR_API WHEREPanelMetadata // : public WHERE_XSEC_DatasetMetadata
{
public:
	/*! 
	 * \brief Get the 'StartLongitude' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual double			getStartLongitude	() = 0;
	/*! 
	 * \brief set the 'StartLongitude' attribute value
	 * \param val					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setStartLongitude	(double val) = 0;
	/*! 
	 * \brief Get the 'StartLatitide' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual double			getStartLatitude	() = 0;
	/*! 
	 * \brief set the 'StartLatitude' attribute value
	 * \param val					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setStartLatitude	(double val) = 0;
	/*! 
	 * \brief Get the 'StopLongitude' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual double			getStopLongitude	() = 0;
	/*! 
	 * \brief set the 'StopLongitude' attribute value
	 * \param val					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setStopLongitude	(double val) = 0;
	/*! 
	 * \brief Get the 'StopLatitude' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual double			getStopLatitude		() = 0;
	/*! 
	 * \brief set the 'StopLatitude' attribute value
	 * \param val					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setStopLatitude		(double val) = 0;
};

/*===========================================================================*/
/* HOW METADATA */
/*===========================================================================*/

/*! 
 * \brief Interface fot HOW root attributes methods 
 */
class RADAR_API HOWRootMetadata 
{
public:
	/*! 
	 * \brief Get the 'task' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual std::string		getTaskOrProdGen	()		= 0;
	/*! 
	 * \brief Set the 'task' attribute value
	 * \param val					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setTaskOrProdGen	(const std::string& val) = 0;
	/*! 
	 * \brief Get the 'startepochs' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual time_t			getStartEpochs		()		= 0;
	/*! 
	 * \brief Set the 'startepochs' attribute value
	 * \param val					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setStartEpochs		(time_t val)	= 0;
	/*! 
	 * \brief Get the 'endepochs' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual time_t			getEndEpochs		()		= 0;
	/*! 
	 * \brief Set the 'endepochs' attribute value
	 * \param val					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setEndEpochs		(time_t val)	= 0;
	/*! 
	 * \brief Get the 'system' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual std::string		getSystem		()		= 0;
	/*! 
	 * \brief Set the 'system' attribute value
	 * \param val					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setSystem		(const std::string& val) = 0;
	/*! 
	 * \brief Get the 'software' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual std::string		getSoftware		()		= 0;
	/*! 
	 * \brief Set the 'software' attribute value
	 * \param val					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setSoftware		(const std::string& val) = 0;
	/*! 
	 * \brief Get the 'sw_version' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual std::string		getSoftwareVer		()		= 0;
	/*! 
	 * \brief Set the 'sw_version' attribute value
	 * \param val					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setSoftwareVer		(const std::string& val) = 0;
	/*! 
	 * \brief Get the 'zr_a' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual double			getZR_A			()		= 0;
	/*! 
	 * \brief Set the 'zr_a' attribute value
	 * \param val					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setZR_A			(double val)	= 0;
	/*! 
	 * \brief Get the 'zr_b' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual double			getZR_B			()		= 0;
	/*! 
	 * \brief Set the 'zr_b' attribute value
	 * \param val					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setZR_B			(double val)	= 0;
	/*! 
	 * \brief Get the 'kr_a' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual double			getKR_A			()		= 0;
	/*! 
	 * \brief Set the 'kr_a' attribute value
	 * \param val					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setKR_A			(double val)	= 0;
	/*! 
	 * \brief Get the 'kr_b' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual double			getKR_B			()		= 0;
	/*! 
	 * \brief Set the 'kr_b' attribute value
	 * \param val					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setKR_B			(double val)	= 0;
	/*! 
	 * \brief Get the 'simulated' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual bool			getSimulated		()		= 0;
	/*! 
	 * \brief Set the 'simulated' attribute value
	 * \param val					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setSimulated		(bool val)	= 0;
};

/*! 
 * \brief Interface fot HOW dataset attributes methods 
 */
class RADAR_API HOWDatasetMetadata : public HOWRootMetadata
{
public:	
	/*! 
	 * \brief Get the 'beamwidth' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual double			getBeamWidth		()			= 0;
	/*! 
	 * \brief Get the 'beamwidth' attribute value
	 * \param defaultValue		the value to return if the attribute does not exists
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual double			getBeamWidth		(double defaultValue)	= 0;
	/*! 
	 * \brief Set the 'beamwidth' attribute value
	 * \param val					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setBeamWidth		(double val)		= 0;
	/*! 
	 * \brief Get the 'wavelength' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual double			getWaveLength		()			= 0;
	/*! 
	 * \brief Get the 'wavelength' attribute value
	 * \param defaultValue		the value to return if the attribute does not exists
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual double			getWaveLength		(double defaultValue)	= 0;
	/*! 
	 * \brief Set the 'wavelength' attribute value
	 * \param val					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setWaveLength		(double val)		= 0;
	/*! 
	 * \brief Get the 'prm' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual double			getRPM			()			= 0;
	/*! 
	 * \brief Get the 'rpm' attribute value
	 * \param defaultValue		the value to return if the attribute does not exists
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual double			getRPM			(double defaultValue)	= 0;
	/*! 
	 * \brief Set the 'rpm' attribute value
	 * \param val					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setRPM			(double val)		= 0;
	/*! 
	 * \brief Get the 'pulsewidth' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual double			getPulseWidth		()			= 0;
	/*! 
	 * \brief Get the 'pulsewidth' attribute value
	 * \param defaultValue		the value to return if the attribute does not exists
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual double			getPulseWidth		(double defaultValue)	= 0;
	/*! 
	 * \brief Set the 'pulsewidth' attribute value
	 * \param val					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setPulseWidth		(double val)		= 0;
	/*! 
	 * \brief Get the 'RXbandwidth' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual double			getRXBandWidth		()			= 0;
	/*! 
	 * \brief Get the 'RXbandwidth' attribute value
	 * \param defaultValue		the value to return if the attribute does not exists
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual double			getRXBandWidth	(double defaultValue)	= 0;
	/*! 
	 * \brief Set the 'RXbandwidth' attribute value
	 * \param val					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setRXBandWidth		(double val)		= 0;
	/*! 
	 * \brief Get the 'lowprf' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual int			getLowPRF		()			= 0;
	/*! 
	 * \brief Get the 'lowprf' attribute value
	 * \param defaultValue		the value to return if the attribute does not exists
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual int			getLowPRF		(int defaultValue)	= 0;
	/*! 
	 * \brief Set the 'lowprf' attribute value
	 * \param val					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setLowPRF		(int val)		= 0;
	/*! 
	 * \brief Get the 'highprf' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual int			getHighPRF		()			= 0;
	/*! 
	 * \brief Get the 'highprf' attribute value
	 * \param defaultValue		the value to return if the attribute does not exists
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual int			getHighPRF		(int defaultValue)	= 0;
	/*! 
	 * \brief Set the 'highprf' attribute value
	 * \param val					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setHighPRF		(int val)		= 0;
	/*! 
	 * \brief Get the 'TXloss' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual double			getTXLoss		()			= 0;
	/*! 
	 * \brief Get the 'TXloss' attribute value
	 * \param defaultValue		the value to return if the attribute does not exists
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual double			getTXLoss	(double defaultValue)	= 0;
	/*! 
	 * \brief Set the 'TXLoss' attribute value
	 * \param val					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setTXLoss		(double val)		= 0;
	/*! 
	 * \brief Get the 'RXloss' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual double			getRXLoss		()			= 0;
	/*! 
	 * \brief Get the 'RXloss' attribute value
	 * \param defaultValue		the value to return if the attribute does not exists
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual double			getRXLoss	(double defaultValue)	= 0;
	/*! 
	 * \brief Set the 'RXloss' attribute value
	 * \param val					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setRXLoss		(double val)		= 0;
	/*! 
	 * \brief Get the 'radomeloss' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual double			getRadomeLoss		()			= 0;
	/*! 
	 * \brief Get the 'radomeloss' attribute value
	 * \param defaultValue		the value to return if the attribute does not exists
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual double			getRadomeLoss	(double defaultValue)	= 0;
	/*! 
	 * \brief Set the 'radomeloss' attribute value
	 * \param val					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setRadomeLoss		(double val)		= 0;
	/*! 
	 * \brief Get the 'antgain' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual double			getAntGain		()			= 0;
	/*! 
	 * \brief Get the 'antgain' attribute value
	 * \param defaultValue		the value to return if the attribute does not exists
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual double			getAntGain	(double defaultValue)	= 0;
	/*! 
	 * \brief Set the 'antgain' attribute value
	 * \param val					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setAntGain		(double val)		= 0;
	/*! 
	 * \brief Get the 'beamwH' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual double			getBeamWH		()			= 0;
	/*! 
	 * \brief Get the 'beamwH' attribute value
	 * \param defaultValue		the value to return if the attribute does not exists
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual double			getBeamWH	(double defaultValue)	= 0;
	/*! 
	 * \brief Set the 'beamwH' attribute value
	 * \param val					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setBeamWH		(double val)		= 0;
	/*! 
	 * \brief Get the 'beamwV' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual double			getBeamWV		()			= 0;
	/*! 
	 * \brief Get the 'beamwV' attribute value
	 * \param defaultValue		the value to return if the attribute does not exists
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual double			getBeamWV	(double defaultValue)	= 0;
	/*! 
	 * \brief Set the 'beamwV' attribute value
	 * \param val					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setBeamWV		(double val)		= 0;
	/*! 
	 * \brief Get the 'gasattn' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual double			getGasAttn		()			= 0;
	/*! 
	 * \brief Get the 'gasattn' attribute value
	 * \param defaultValue		the value to return if the attribute does not exists
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual double			getGasAttn	(double defaultValue)	= 0;
	/*! 
	 * \brief Set the 'gasattn' attribute value
	 * \param val					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setGasAttn		(double val)		= 0;
	/*! 
	 * \brief Get the 'radconstH' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual double			getRadConstH		()			= 0;
	/*! 
	 * \brief Get the 'radconstH' attribute value
	 * \param defaultValue		the value to return if the attribute does not exists
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual double			getRadConstH	(double defaultValue)	= 0;
	/*! 
	 * \brief Set the 'radconstH' attribute value
	 * \param val					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setRadConstH		(double val)		= 0;
	/*! 
	 * \brief Get the 'radconstV' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual double			getRadConstV		()			= 0;
	/*! 
	 * \brief Get the 'radconstV' attribute value
	 * \param defaultValue		the value to return if the attribute does not exists
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual double			getRadConstV	(double defaultValue)	= 0;
	/*! 
	 * \brief Set the 'radconstV' attribute value
	 * \param val					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setRadConstV		(double val)		= 0;
	/*! 
	 * \brief Get the 'nomTXpower' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual double			getNomTXPower		()			= 0;
	/*! 
	 * \brief Get the 'nomTXpower' attribute value
	 * \param defaultValue		the value to return if the attribute does not exists
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual double			getNomTXPower	(double defaultValue)	= 0;
	/*! 
	 * \brief Set the 'nomTXpower' attribute value
	 * \param val					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setNomTXPower		(double val)		= 0;
	/*! 
	 * \brief Get the 'TXpower' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual std::vector<double>	getTXPower		()			= 0;
	/*! 
	 * \brief Get the 'TXpower' attribute value
	 * \param defaultValue		the value to return if the attribute does not exists
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual std::vector<double>	getTXPower	(double defaultValue)	= 0;
	/*! 
	 * \brief Set the 'TXpower' attribute value
	 * \param val					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setTXPower		(double val)		= 0;
	/*! 
	 * \brief Get the 'NI' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual double			getNI		()			= 0;
	/*! 
	 * \brief Get the 'NI' attribute value
	 * \param defaultValue		the value to return if the attribute does not exists
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual double			getNI	(double defaultValue)	= 0;
	/*! 
	 * \brief Set the 'NI' attribute value
	 * \param val					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setNI		(double val)		= 0;
	/*! 
	 * \brief Get the 'Vsamples' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual double			getVSamples		()			= 0;
	/*! 
	 * \brief Get the 'Vsamples' attribute value
	 * \param defaultValue		the value to return if the attribute does not exists
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual double			getVSamples	(double defaultValue)	= 0;
	/*! 
	 * \brief Set the 'Vsamples' attribute value
	 * \param val					the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setVSamples		(double val)		= 0;
};

/*! 
 * \brief Interface fot HOW dataset attributes methods for polar data
 */
class RADAR_API HOWPolarMetadata : public HOWDatasetMetadata
{
public:
	/*! 
	 * \brief Get the 'azmethod' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual std::string		getAzimuthMethod	() = 0;
	/*! 
	 * \brief Set the 'azmethod' attribute value
	 * \param val			the value tro write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setAzimuthMethod	(const std::string& val) = 0;
	/*! 
	 * \brief Get the 'binmethod' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual std::string		getBinMethod		() = 0;
	/*! 
	 * \brief Set the 'binmethod' attribute value
	 * \param val			the value tro write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setBinMethod		(const std::string& val) = 0;

	/*! 
	 * \brief Get the 'azangles' attribute values
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
//	virtual std::vector<AZAngles>	getAzimuthAngles	() = 0;
	/*! 
	 * \brief Set the 'azangles' attribute values
	 * \param val			the values to write
	 * \param precision				precision to use when converting angle pairs to string pairs
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
//	virtual void			setAzimuthAngles	(const std::vector<AZAngles>& val, int precision = 0) = 0;

	/*! 
	 * \brief Get the 'elangles' attribute values
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual std::vector<double>	getElevationAngles	() = 0;
	/*! 
	 * \brief Set the 'elangles' attribute values
	 * \param val			the values to write
	 * \param precision				precision to use when converting angle pairs to string pairs
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setElevationAngles	(const std::vector<double>& val) = 0;
	/*! 
	 * \brief Get the 'startazA' attribute values
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual std::vector<double>	getStartAzimuthAngles	() = 0;
	/*! 
	 * \brief Set the 'startazA' attribute values
	 * \param val			the values to write
	 * \param precision				precision to use when converting angle pairs to string pairs
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setStartAzimuthAngles	(const std::vector<double>& val) = 0;
	/*! 
	 * \brief Get the 'stopazA' attribute values
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual std::vector<double>	getStopAzimuthAngles	() = 0;
	/*! 
	 * \brief Set the 'stopazA' attribute values
	 * \param val			the values to write
	 * \param precision				precision to use when converting angle pairs to string pairs
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setStopAzimuthAngles	(const std::vector<double>& val) = 0;
	/*! 
	 * \brief Get the 'startazT' attribute values
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual std::vector<double>	getStartAzimuthTimes	() = 0;
	/*! 
	 * \brief Set the 'startazT' attribute values
	 * \param val			the values to write
	 * \param precision				precision to use when converting angle pairs to string pairs
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setStartAzimuthTimes	(const std::vector<double>& val) = 0;
	/*! 
	 * \brief Get the 'stopazT' attribute values
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual std::vector<double>	getStopAzimuthTimes	() = 0;
	/*! 
	 * \brief Set the 'stopazT' attribute values
	 * \param val			the values to write
	 * \param precision				precision to use when converting angle pairs to string pairs
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setStopAzimuthTimes	(const std::vector<double>& val) = 0;

	/*! 
	 * \brief Get the 'aztimes' attribute values
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
//	virtual std::vector<AZTimes>	getAzimuthTimes		() = 0;
	/*! 
	 * \brief Set the 'aztimes' attribute values
	 * \param val			the values to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
//	virtual void			setAzimuthTimes		(const std::vector<AZTimes>& val) = 0;


	/*! 
	 * \brief Get the 'pointaccEL' attribute values
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual double			getPointAccEl		()		= 0;
	/*! 
	 * \brief Set the 'pointaccEL' attribute values
	 * \param val			the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setPointAccEl		(double val)	= 0;
	/*! 
	 * \brief Get the 'pointaccAZ' attribute values
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual double			getPointAccAZ		()		= 0;
	/*! 
	 * \brief Set the 'pointaccAZ' attribute values
	 * \param val			the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setPointAccAZ		(double val)	= 0;
	/*! 
	 * \brief Get the 'malfunc' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual bool			getMalfunc		()		= 0;
	/*! 
	 * \brief Set the 'malfunc' attribute value
	 * \param val			the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setMalfunc		(bool val)	= 0;
	/*! 
	 * \brief Get the 'radarmsg' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual std::string		getRadarMsg		()		= 0;
	/*! 
	 * \brief Set the 'radarmsg' attribute value
	 * \param val			the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setRadarMsg		(const std::string& val) = 0;
	/*! 
	 * \brief Get the 'radhoriz' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual double			getRadarHorizon		()		= 0;
	/*! 
	 * \brief Set the 'radhoriz' attribute value
	 * \param val			the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setRadarHorizon		(double val)	= 0;

	/*! 
	 * \brief Get the 'MDS' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
//	virtual double			getMDS			()		= 0;
	/*! 
	 * \brief Set the 'MDS' attribute value
	 * \param val			the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
//	virtual void			setMDS			(double val)	= 0;

	/*! 
	 * \brief Get the 'NEZ' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual double			getNEZ			()		= 0;
	/*! 
	 * \brief Set the 'NEZ' attribute value
	 * \param val			the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setNEZ			(double val)	= 0;
	/*! 
	 * \brief Get the 'OUR' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual double			getOUR			()		= 0;
	/*! 
	 * \brief Set the 'OUR' attribute value
	 * \param val			the value to write	 
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setOUR			(double val)	= 0;

	/*! 
	 * \brief Get the 'Dclutter' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual std::vector<std::string> getDClutter		()		= 0;
	/*! 
	 * \brief Set the 'Dclutter' attribute value
	 * \param val			the values to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setDClutter		(const std::vector<std::string>& val)	= 0;

	/*! 
	 * \brief Get the 'comment' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual std::string		getComment		()		= 0;
	/*! 
	 * \brief Set the 'comment' attribute value
	 * \param val			the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setComment		(const std::string& val) = 0;
	/*! 
	 * \brief Get the 'SQI' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual double			getSQI			()		= 0;
	/*! 
	 * \brief Set the 'SQI' attribute value
	 * \param val			the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setSQI			(double val)	= 0;
	/*! 
	 * \brief Get the 'CSR' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual double			getCSR			()		= 0;
	/*! 
	 * \brief Set the 'CSR' attribute value
	 * \param val			the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setCSR			(double val)	= 0;
	/*! 
	 * \brief Get the 'LOG' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual double			getLOG			()		= 0;
	/*! 
	 * \brief Set the 'LOG' attribute value
	 * \param val			the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setLOG			(double val)	= 0;
	/*! 
	 * \brief Get the 'VPRCoor' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual bool			getVPRCorr		()		= 0;
	/*! 
	 * \brief Set the 'VPRCoor' attribute value
	 * \param val			the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setVPRCorr		(bool val)	= 0;
	/*! 
	 * \brief Get the 'freeze' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual double			getFreeze		()		= 0;
	/*! 
	 * \brief Set the 'freeze' attribute value
	 * \param val			the value to write	 
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setFreeze		(double val)	= 0;
	/*! 
	 * \brief Get the 'min' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual double			getMin			()		= 0;
	/*! 
	 * \brief Set the 'min' attribute value
	 * \param val			the value to write
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setMin			(double val)	= 0;
	/*! 
	 * \brief Get the 'max' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual double			getMax			()		= 0;
	/*! 
	 * \brief Set the 'max' attribute value
	 * \param val			the value to write	 
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setMax			(double val)	= 0;
	/*! 
	 * \brief Get the 'step' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual double			getStep			()		= 0;
	/*! 
	 * \brief Set the 'step' attribute value
	 * \param val			the value to write	 
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setStep			(double val)	= 0;
	/*! 
	 * \brief Get the 'levels' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual int			getLevels		()		= 0;
	/*! 
	 * \brief Set the 'levels' attribute value
	 * \param val			the value to write	 
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setLevels		(int val)	= 0;
	/*! 
	 * \brief Get the 'peakpwr' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual double			getPeakPwr		()		= 0;
	/*! 
	 * \brief Set the 'peakpwr' attribute value
	 * \param val			the value to write	 
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setPeakPwr		(double val)	= 0;
	/*! 
	 * \brief Get the 'avgpwr' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual double			getAvgPwr		()		= 0;
	/*! 
	 * \brief Set the 'awgpwr' attribute value
	 * \param val			the value to write	 
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setAvgPwr		(double val)	= 0;
	/*! 
	 * \brief Get the 'dynrange' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual double			getDynRange		()		= 0;
	/*! 
	 * \brief Set the 'dynrange' attribute value
	 * \param val			the value to write	 
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setDynRange		(double val)	= 0;
	/*! 
	 * \brief Get the 'RAC' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual double			getRAC			()		= 0;
	/*! 
	 * \brief Set the 'RAC' attribute value
	 * \param val			the value to write	 
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setRAC			(double val)	= 0;
	/*! 
	 * \brief Get the 'BBC' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual bool			getBBC			()		= 0;
	/*! 
	 * \brief Set the 'BBC' attribute value
	 * \param val			the value to write	 
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setBBC			(bool val)	= 0;
	/*! 
	 * \brief Get the 'PAC' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual double			getPAC			()		= 0;
	/*! 
	 * \brief Set the 'PAC' attribute value
	 * \param val			the value to write	 
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setPAC			(double val)	= 0;
	/*! 
	 * \brief Get the 'S2N' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual double			getS2N			()		= 0;
	/*! 
	 * \brief Set the 'S2N' attribute value
	 * \param val			the value to write	 
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setS2N			(double val)	= 0;
	/*! 
	 * \brief Get the 'polarization' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual std::string		getPolarization		()		= 0;
	/*! 
	 * \brief Set the 'polarization' attribute value
	 * \param val			the value to write	 
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setPolarization		(const std::string& val) = 0;

};

/*! 
 * \brief Interface fot HOW dataset attributes methods for cartesian images
 */
class RADAR_API HOWCartesianImageMetadata  ///////: public HOWDatasetMetadata
{
public:
	/*! 
	 * \brief Get the 'angles' attribute values
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual std::vector<Angles>	getAngles		() = 0;
	/*! 
	 * \brief Set the 'angles' attribute values
	 * \param val			the values to write
	 * \param precision				precision to use when converting angle pairs to string pairs
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setAngles		(const std::vector<Angles>& val) = 0;
	/*! 
	 * \brief Get the 'aroration' attribute values
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual std::vector<Arotation>	getArotation		()		= 0;
	/*! 
	 * \brief Set the 'aroration' attribute values
	 * \param val			the values to write
	 * \param precision				precision to use when converting angle pairs to string pairs
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setArotation		(const std::vector<Arotation>& val)	= 0;
	/*! 
	 * \brief Get the 'camethod' attribute values
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual std::string		getCAMethod		()		= 0;
	/*! 
	 * \brief Set the 'camethod' attribute values
	 * \param val			the value to write	 
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setCAMethod		(const std::string& val) = 0;
	/*! 
	 * \brief Get the 'nodes' attribute values
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual std::vector<Nodes>getNodes		()		= 0;
	/*! 
	 * \brief Set the 'nodes' attribute values
	 * \param val			the value to write	 
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setNodes		(const std::vector<Nodes>& val) = 0;
	/*! 
	 * \brief Get the 'ACCnum' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual int			getACCnum		()		= 0;
	/*! 
	 * \brief Set the 'ACCnum' attribute value
	 * \param val			the value to write	 
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setCCnum		(int val)	= 0;
};

/*! 
 * \brief Interface fot HOW dataset attributes methods for vertical profiles
 */
class RADAR_API HOWVerticalProfileMetadata : public HOWDatasetMetadata
{
public:
	/*! 
	 * \brief Get the 'minrange' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual double			getMinRange		()		= 0;
	/*! 
	 * \brief Set the 'minrange' attribute value
	 * \param val			the value to write	 
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setMinRange		(double val)	= 0;
	/*! 
	 * \brief Get the 'maxrange' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual double			getMaxRange		()		= 0;
	/*! 
	 * \brief Set the 'maxrange' attribute value
	 * \param val			the value to write	 
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setMaxRange		(double val)	= 0;

	/*! 
	 * \brief Get the 'NI' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
//	virtual double			getNI			()		= 0;
	/*! 
	 * \brief Set the 'NI' attribute value
	 * \param val			the value to write	 
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
//	virtual void			setNI			(double val)	= 0;

	/*! 
	 * \brief Get the 'dealiased' attribute value
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual int			getDealiased		()		= 0;
	/*! 
	 * \brief Set the 'dealiased' attribute value
	 * \param val			the value to write	 
	 * \throws OdimH5Exception			if an unexpected error occurs
	 */
	virtual void			setDealiased		(int val)	= 0;
};

/*===========================================================================*/

}


#endif

































