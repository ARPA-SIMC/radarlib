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
 *  \brief Interface classes between OdimH5 objects and HDF5 library
 */ 

#ifndef __RADAR_ODIMH5V21_HDF5_HPP__
#define __RADAR_ODIMH5V21_HDF5_HPP__

/*===========================================================================*/
/* INTERNAL HEADER FILE USED INSIDE THE LIBRARY  */
/*===========================================================================*/

#include <radarlib/defs.h>

/* sotto windows bisogna utilizzare queste macro per poter usare la DLL */
#ifndef _HDF5USEDLL_
#define _HDF5USEDLL_
#endif
#ifndef HDF5CPP_USEDLL
#define HDF5CPP_USEDLL
#endif

#include "H5Cpp.h"
//#ifndef H5_NO_NAMESPACE
//using namespace H5;
//#endif

#include <set>

namespace OdimH5v21 {

/*===========================================================================*/
/* HDF5 FILE */
/*===========================================================================*/

/*! 
 * \brief HDF5File class
 * 
 * This is an internal class with methods to perform operations on HDF5 files
 */
class RADAR_API HDF5File
{
public:
	/*! 
	 * \brief Open a HDF5 file
	 *
	 * Open a HDF5 file using the given HDF5 options
	 * \param path				the path to open
	 * \param h5flags			HDF5 io flags 
	 * \throws OdimH5Exception		if an unexpected error occurs
	 */
	static H5::H5File*	open		(const std::string& path, int h5flags);
	/*! 
	 * \brief Get the HDF5 root group of a file
	 * Get the HDF5 root group of a given HDF5 file
	 * \param file				The HDF5 file
	 * \throws OdimH5Exception		if an unexpected error occurs
	 */
	static H5::Group*	getRoot		(H5::H5File* file);
};

/*===========================================================================*/
/* HDF5 ATTRIBUTE */
/*===========================================================================*/

/*! 
 * \brief HDF5Attribute class
 * 
 * This is an internal class with methods to perform operations on HDF5 attributes
 */
class RADAR_API HDF5Attribute
{
public:
	/*! 
	 * \brief Get a HDF5 attribute
	 *
	 * Get the HDF5 attribute of an HDF5 object with the given name
	 * \param obj				the hdf5 object 
	 * \param name				the attribute name
	 * \param mandatory			throw exception if the attribute does not exists
	 * \throws OdimH5Exception		if an unexpected error occurs
	 * \throws OdimH5MissingAttributeException	if mandatory is true and the attribute does not exists
	 */
	static H5::Attribute*	get		(H5::H5Object* obj, const char* name, bool mandatory);
	/*! 
	 * \brief Check if an HDF5 attribute exists
	 *
	 * Check if an HDF5 attribute exists for a given object
	 * \param obj				the hdf5 object 
	 * \param name				the attribute name
	 * \throws OdimH5Exception		if an unexpected error occurs
	 */
	static bool		exists		(H5::H5Object* obj, const char* name);
	/*! 
	 * \brief Delete an HDF5 attribute 
	 *
	 * Delete an HDF5 attribute from an HDF5 object
	 * \param obj				the hdf5 object 
	 * \param name				the attribute name
	 * \throws OdimH5Exception		if an unexpected error occurs
	 */
	static void		remove		(H5::H5Object* obj, const char* name);
	/*! 
	 * \brief Get the name of a given attribute
	 *
	 * Get the name of a given attribute.
	 * This method is defined only to overcome a HDF5 library bug
	 * \param attr				the hdf5 attribute
	 * \throws OdimH5Exception		if an unexpected error occurs
	 */
	static std::string	getName		(H5::Attribute* attr);

	/*! 
	 * \brief Set the value of an attribute
	 *
	 * Set the value of an attribute using the given 64 bit signed int value
	 * If the attribute does not exists it will be created
	 * If the attribute exists it will be erased and then recrated
	 * \param obj				the hdf5 object 
	 * \param name				the attribute name
	 * \param value				the value to write into the attribute
	 * \throws OdimH5Exception		if an unexpected error occurs
	 */
	static void		set		(H5::H5Object* obj, const char* name, int64_t value);
	/*! 
	 * \brief Set the value of an attribute
	 *
	 * Set the value of an attribute using the given 64 bit floating point value
	 * If the attribute does not exists it will be created
	 * If the attribute exists it will be erased and then recrated
	 * \param obj				the hdf5 object 
	 * \param name				the attribute name
	 * \param value				the value to write into the attribute
	 * \throws OdimH5Exception		if an unexpected error occurs
	 */
	static void		set		(H5::H5Object* obj, const char* name, double value);
	/*! 
	 * \brief Set the value of an attribute
	 *
	 * Set the value of an attribute using the given string
	 * If the attribute does not exists it will be created
	 * If the attribute exists it will be erased and then recrated
	 * \param obj				the hdf5 object 
	 * \param name				the attribute name
	 * \param value				the string to use
	 * \throws OdimH5Exception		if an unexpected error occurs
	 */
	static void		set		(H5::H5Object* obj, const char* name, const char* value);
	/*! 
	 * \brief Set the value of an attribute
	 *
	 * Set the value of an attribute using the given std::string
	 * If the attribute does not exists it will be created
	 * If the attribute exists it will be erased and then recrated
	 * \param obj				the hdf5 object 
	 * \param name				the attribute name
	 * \param value				the string to use
	 * \throws OdimH5Exception		if an unexpected error occurs
	 */
	static void		set		(H5::H5Object* obj, const char* name, const std::string& value);

	/*! 
	 * \brief Get the value of a 64 bit int signed attribute attribute
	 *
	 * Get the value of a 64 bit signed int attribute 
	 * \param obj				the HDF5 object
	 * \param name				the attribute name
	 * \throws OdimH5Exception		if an unexpected error occurs
	 * \throws OdimH5MissingAttributeException	Raised if the attribute does not exists
	 */
	static int64_t		getLong		(H5::H5Object* obj, const char* name);
	/*! 
	 * \brief Get the value of a 64 bit int signed attribute 
	 *
	 * Get the value of a 64 signed int attribute 
	 * \param obj				the hdf5 object 
	 * \param name				the attribute name
	 * \param defaultValue			the value to return if the attribute does not exists
	 * \throws OdimH5Exception		if an unexpected error occurs	 
	 */
	static int64_t		getLong		(H5::H5Object* obj, const char* name, int64_t defaultValue);
	/*! 
	 * \brief Get the value of a 64 bit floating point attribute 
	 *
	 * Get the value of a 64 bit floating point attribute 
	 * \param obj				the hdf5 object 
	 * \param name				the attribute name
	 * \throws OdimH5Exception		if an unexpected error occurs	 
	 * \throws OdimH5MissingAttributeException	Raised if the attribute does not exists
	 */
	static double		getDouble	(H5::H5Object* obj, const char* name);
	/*! 
	 * \brief Get the value of a 64 bit floating point attribute 
	 *
	 * Get the value of a 64 bit floating point attribute 
	 * \param obj				the hdf5 object 
	 * \param name				the attribute name
	 * \param defaultValue			the value to return if the attribute does not exists
	 * \throws OdimH5Exception		if an unexpected error occurs	 
	 * \throws OdimH5MissingAttributeException	Raised if the attribute does not exists
	 */
	static double		getDouble	(H5::H5Object* obj, const char* name, double defaultValue);
	/*! 
	 * \brief Get the value of a string attribute 
	 *
	 * Get the value of a string attribute 
	 * \param obj				the hdf5 object 
	 * \param name				the attribute name
	 * \throws OdimH5Exception		if an unexpected error occurs	 
	 * \throws OdimH5MissingAttributeException	Raised if the attribute does not exists
	 */
	static std::string	getStr		(H5::H5Object* obj, const char* name);
	/*! 
	 * \brief Get the value of a string attribute 
	 *
	 * Get the value of a string attribute 
	 * \param obj				the hdf5 object 
	 * \param name				the attribute name
	 * \param defaultValue			the value to return if the attribute does not exists
	 * \throws OdimH5Exception		if an unexpected error occurs	 
	 * \throws OdimH5MissingAttributeException	Raised if the attribute does not exists
	 */
	static std::string	getStr		(H5::H5Object* obj, const char* name, const std::string& defaultValue);	

};

/*===========================================================================*/
/* HDF5 GROUP */
/*===========================================================================*/

/*! 
 * \brief HDF5Group class
 * 
 * This is an internal class with methods to perform operations on HDF5 groups
 */
class RADAR_API HDF5Group
{
public:
	/*! 
	 * \brief Get the number of children group of a given HDF5 group
	 *
	 * Get the number of children group of a given HDF5 group searching for elements with the same name prefix
	 * \param parent			the parent HDF5 object
	 * \param prefix			the name prefix used to select children
	 * \throws OdimH5Exception		if an unexpected error occurs	 	 
	 */
	static int		getChildCount	(H5::Group* parent, const char* prefix);
	/*! 
	 * \brief Get the a child group of a given HDF5 group
	 *
	 * Get the child group of a given HDF5 group using a given name
	 * \param parent			the parent HDF5 object
	 * \param name				the name of the child
	 * \returns				The child group or NULL if it does not exists
	 * \throws OdimH5Exception		if an unexpected error occurs	 	 
	 */
	static H5::Group*	getChild	(H5::Group* parent, const char* name);
	/*! 
	 * \brief Check or create a child group 
	 *
	 * Check or create a child group of a given group
	 * \param parent			the parent HDF5 object
	 * \param name				the name of the child
	 * \throws OdimH5Exception		if an unexpected error occurs	 	 
	 */
	static void		ensureChild	(H5::Group* parent, const char* name);
	/*! 
	 * \brief Get (and automatically create) a child group 
	 *
	 * Get (and automatically create) a child group of a given group with the given name
	 * \param parent			the parent HDF5 object
	 * \param name				the name of the child
	 * \returns				the child group
	 * \throws OdimH5Exception		if an unexpected error occurs	 	 
	 */
	static H5::Group*	ensureGetChild	(H5::Group* parent, const char* name);
	/*! 
	 * \brief Delete a child group
	 *
	 * Delete a child group
	 * \param parent			the parent HDF5 object
	 * \param name				the name of the child
	 * \throws OdimH5Exception		if an unexpected error occurs	 	 
	 */
	static void		removeChild	(H5::Group* parent, const char* name);

	/*! 
	 * \brief Check for child group existance
	 *
	 * Check for child group existance
	 * \param parent			the parent HDF5 object
	 * \param name				the name of the child
	 * \throws OdimH5Exception		if an unexpected error occurs	 	 
	 */
	static bool		exists		(H5::Group* parent, const char* name);
	/*! 
	 * \brief Get a HDF5 dataset child of a given HDF5 group
	 *
	 * Get a HDF5 dataset child of a given HDF5 group
	 * \param parent			the parent HDF5 object
	 * \param name				the name of the child
	 * \throws OdimH5Exception		if an unexpected error occurs or the group is not found
	 */
	static H5::DataSet*	getDataset	(H5::Group* parent, const char* name);
	/*! 
	 * \brief Copy all attributes from a HDF5 group to another
	 *
	 * Copy all attributes from a HDF5 group to another
	 * \param src				the HDF5 group to copy from
	 * \param dst				the HDF5 group to copy to
	 * \throws OdimH5Exception		if an unexpected error occurs 
	 */
	static void		copyAttributes	(H5::Group* src, H5::Group* dst);
	/*! 
	 * \brief Copy all specified attributes from a HDF5 group to another
	 *
	 * Copy all attributes from a HDF5 group to another
	 * \param src				the HDF5 group to copy from
	 * \param dst				the HDF5 group to copy to
	 * \param names				the attributes to copy
	 * \throws OdimH5Exception		if an unexpected error occurs 
	 */
	static void		copyAttributes	(H5::Group* src, H5::Group* dst, const std::set<std::string>& names);
	/*! 
	 * \brief Copy all specified datasets from a HDF5 group to another
	 *
	 * Copy all datasets from a HDF5 group to another
	 * \param src				the HDF5 group to copy from
	 * \param dst				the HDF5 group to copy to
	 * \throws OdimH5Exception		if an unexpected error occurs 
	 */
//	static void		copyDatasets(H5::Group* src, H5::Group* dst);
//	static void  		copyDatasets(MetadataGroup* src, MetadataGroup* dst);
	/*! 
	 * \brief Copy all specified datasets from a HDF5 group to another
	 *
	 * Copy all datasets from a HDF5 group to another
	 * \param src				the HDF5 group to copy from
	 * \param dst				the HDF5 group to copy to
	 * \param names				the datasets to copy
	 * \throws OdimH5Exception		if an unexpected error occurs 
	 */
//	static void		copyDatasets(H5::Group* src, H5::Group* dst, const std::set<std::string>& names);
};

/*===========================================================================*/
/* HDF5 ATOM TYPE */
/*===========================================================================*/

/*! 
 * \brief HDF5Group class
 * 
 * This is an internal class with methods to perform operations on HDF5 atom types
 */
class RADAR_API HDF5AtomType
{
public:
	/*! 
	 * \brief Try to cast a generic HDF5 DataType to a AtomType
	 *
	 * Try to cast a generic HDF5 DataType to a AtomType.
         * This method can be used for example to find the specific type of a HDF5 dataset	 
	 * \param type				the HDF5 generic type
	 * \throws OdimH5Exception		if an unexpected error occurs 
	 * \throws OdimH5UnsupportedException	if the type cannot be converted
	 */
	static H5::AtomType fromDataType(const H5::DataType& type);	
};


/*===========================================================================*/

}

#endif



































