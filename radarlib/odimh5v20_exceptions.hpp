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
 *  \brief OdimH5 exceptions
 */

#ifndef __RADAR_ODIMH5V20_EXCEPTIONS_HPP__
#define __RADAR_ODIMH5V20_EXCEPTIONS_HPP__

#include <stdexcept>
#include <radarlib/defs.h>

/* sotto windows bisogna utilizzare queste macro per poter usare la DLL */
#ifndef _HDF5USEDLL_
#define _HDF5USEDLL_
#endif
#ifndef HDF5CPP_USEDLL
#define HDF5CPP_USEDLL
#endif
#include "H5Cpp.h"

namespace OdimH5v20 {

/*===========================================================================*/

/*!
 * \brief
 * OdimH5 generic error
 * 
 * Every exception thrown by OdimH5 library is a specialization of this exception
 */
class OdimH5Exception : public std::logic_error
{
public:
	/*! 
	 * \brief Initialize the exception
	 *
	 * \param msg				the exception msg 
	 */
	OdimH5Exception(const std::string& msg)
	:std::logic_error(msg)
	{
	}
	virtual ~OdimH5Exception() throw()
	{
	}
};

/*===========================================================================*/

/*!
 * \brief
 * OdimH5 unsupported feature error
 * 
 * Raised every time a feature is used with unsupported options.
 * Usually it happens during conversions of binary data from file to memory and viceversa
 */
class OdimH5UnsupportedException : public OdimH5Exception
{
public:
	/*! 
	 * \brief Initialize the exception
	 *
	 * \param msg				the exception msg 
	 */
	OdimH5UnsupportedException(const std::string& msg)
	:OdimH5Exception("Unsupported operation error: " + msg)
	{
	}
	virtual ~OdimH5UnsupportedException() throw()
	{
	}
};

/*===========================================================================*/

/*!
 * \brief
 * OdimH5 format error
 * 
 * Generic exception for situations where HDF5 file is not compliant to OdimH5 specifications
 */
class OdimH5FormatException : public OdimH5Exception
{
public:
	/*! 
	 * \brief Initialize the exception
	 *
	 * \param msg				the exception msg 
	 */
	OdimH5FormatException(const std::string& msg)
	:OdimH5Exception(msg)
	{
	}
	virtual ~OdimH5FormatException() throw()
	{
	}
};

/*===========================================================================*/

/*!
 * \brief
 * OdimH5 unknown format error
 * 
 * Throw every time a HDF5 file has an unknown format
 * \n For example when "/Conventions" has an unexpected value
 */
class OdimH5UnknownFormatException : public OdimH5FormatException
{
public:
	/*! 
	 * \brief Initialize the exception
	 *
	 * \param msg				the exception msg 
	 */
	OdimH5UnknownFormatException(const std::string& msg)
	:OdimH5FormatException(msg)
	{
	}
	virtual ~OdimH5UnknownFormatException() throw()
	{
	}
};

/*===========================================================================*/

/*!
 * \brief
 * OdimH5 missing attribute error
 * 
 * Exception throwed when a attribute is missing
 */
class OdimH5MissingAttributeException : public OdimH5FormatException
{
public:
	/*! 
	 * \brief Initialize the exception
	 *
	 * \param name		the name of the missing attribute
	 */
	OdimH5MissingAttributeException(const std::string& name)
	:OdimH5FormatException("Attribute " + name + " not found")
	{
	}
	virtual ~OdimH5MissingAttributeException() throw()
	{
	}
};

/*===========================================================================*/

/*!
 * \brief
 * OdimH5 invalid attribute value error
 * 
 * Exception throwed when a attribute has an invalid value
 */
class OdimH5InvalidAttributeValueException : public OdimH5FormatException
{
public:
	/*! 
	 * \brief Initialize the exception
	 *
	 * \param name		the name of attribute with the invalid value
	 */
	OdimH5InvalidAttributeValueException(const std::string& name)
	:OdimH5FormatException("Attribute " + name + " has a invalid value")
	{
	}
	virtual ~OdimH5InvalidAttributeValueException() throw()
	{
	}
};

/*===========================================================================*/

/*!
 * \brief
 * OdimH5 missing group error
 * 
 * Exception throwed when an Odim group (a dataset group, a data group etc.) is missing 
 */
class OdimH5MissingGroupException : public OdimH5FormatException
{
public:
	/*! 
	 * \brief Initialize the exception
	 *
	 * \param name		the name of the missing HDF5 group
	 */
	OdimH5MissingGroupException(const std::string& name)
	:OdimH5FormatException("HDF5 Group " + name + " not found")
	{
	}
	virtual ~OdimH5MissingGroupException() throw()
	{
	}
};

/*===========================================================================*/

/*!
 * \brief
 * OdimH5 missing group error
 * 
 * Exception throwed when an dataset is missing 
 */
class OdimH5MissingDatasetException : public OdimH5FormatException
{
public:
	/*! 
	 * \brief Initialize the exception
	 *
	 * \param name		the name of the missing HDF5 dataset
	 */
	OdimH5MissingDatasetException(const std::string& name)
	:OdimH5FormatException("HDF5 dataset " + name + " not found")
	{
	}
	virtual ~OdimH5MissingDatasetException() throw()
	{
	}
};

/*===========================================================================*/

/*!
 * \brief
 * HDF5 exception inside Odim Classes
 * 
 * When HDF5 library raises an exception, OdimH5 classes catch it and
 * throw this exception instead.
 * 
 * \remarks
 * For some reasons HDF5 library throws exceptions without meaningfull messages
 * or NULL buffers. In oder to avoid null pointer exceptions 
 * we OdimH5 library use exception when a HDF5 exception is thrown
 * 
 */
class OdimH5HDF5LibException : public OdimH5Exception
{
public:
	/*! 
	 * \brief Initialize the exception
	 *
	 * Initialize the exception using the given free message
	 * \param msg		the generic error msg
	 */
	OdimH5HDF5LibException(const std::string& msg)
	:OdimH5Exception(msg)
	{
	}
	/*! 
	 * \brief Initialize the exception
	 *
	 * Initialize the exception using the original HDF5 library exception
	 * \param h5e		the HDF5 exception to wrap
	 */
	OdimH5HDF5LibException(H5::Exception& h5e)
	:OdimH5Exception((h5e.getCDetailMsg() ? std::string(h5e.getCDetailMsg()) : "HDF5 internal error"))
	{
	}
	/*! 
	 * \brief Initialize the exception
	 *
	 * Initialize the exception using the given free message and the original HDF5 library exception
	 * \param msg		the error description
	 * \param h5e		the original HDF5 exception 
	 */
	OdimH5HDF5LibException(const std::string& msg, H5::Exception& h5e)
	:OdimH5Exception(msg + ": " + (h5e.getCDetailMsg() ? std::string(h5e.getCDetailMsg()) : "HDF5 internal error"))
	{
	}
	virtual ~OdimH5HDF5LibException() throw()
	{
	}
};

/*===========================================================================*/

}

#endif
























