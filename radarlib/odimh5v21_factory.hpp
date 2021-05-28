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
 *  \brief OdimH5 factory classes
 */ 

#ifndef __RADAR_ODIMH5V21_FACTORY_HPP__
#define __RADAR_ODIMH5V21_FACTORY_HPP__

#include <radarlib/defs.h>
#include <radarlib/odimh5v21_classes.hpp>
#include <radarlib/odimh5v21_dump.hpp>

namespace OdimH5v21 {
	
		/*===========================================================================*/
		/* ODIM FACTORY */
		/*===========================================================================*/
		
		/*! 
		 * \brief OdimH5 objects factory
		 * 
		 * \n OdimH5 objects should not be directly created with "new" operator.
		 * \n OdimH5 objects should be created using the a factory.
		 * \n This factory allow users to create generic OdimH5 object or PVOL objects (PolarVolume::) conformed to OdimH5 v2.1 specifications.
         * \n Note: if the environment variable RADARLIB_SKIP_CHECK_VERSION is
         * equals to "yes", then this class ignores the version of the ODIM file.
		 * 
		 * \see OdimObject | PolarVolume
		 */
		class RADAR_API OdimFactory
		{
			public:	
				OdimFactory();
					virtual ~OdimFactory();
					
					/*!
					 * \brief
					 * Create a new generic OdimH5 object and the associated file
					 * 
					 * \param path			the file path where the object will be stored
					 * 
					 * \returns
					 * Returns the created OdimObject 
					 * 
					 * \throws OdimH5HDF5LibException	Throwed when a HDF5 Exception occurs
					 * 
					 * \n Create a generic OdimH5 object and the associated file. 
					 * \n If the file already exists, it will be recreated. 
					 * \n The file will be opened for input and output operations.
					 * \n In oder to create a specific OdimH5 object use the other methods of the factory
					 * 
					 * \see OdimObject | createPolarVolume | createImageObject | createCompObject | createXsecObject
					 */
					virtual OdimObject*		create(const std::string& path);
					
					/*!
					 * \brief
					 * Get a OdimH5 object from an existing file
					 * 
					 * \param path				the file path where the object will is stored
					 * 
					 * \returns
					 * Returns the OdimObject stored in the file
					 * 
					 * \throws OdimH5FormatException	Throwed when the HDF5 file is not a OdimH5 file 
					 * \throws OdimH5HDF5LibException	Throwed when a HDF5 exception occurs
					 *
					 * \n Get a OdimH5 object stored in an existing file.
					 * \n The file will be opened for input and output operations.
					 * \n If the OdimH5 object is an object supported by the factory, a specialized object will be created.
					 * 
					 * \see openPolarVolume
					 */
					virtual OdimObject*		open(const std::string& path);
					
					/*!
					 * \brief
					 * Get a OdimH5 object from an existing file
					 * 
					 * \param path				the file path where the object will is stored
					 * \param h5flags			the HDF5 I/O flags used to open the file
					 * 
					 * \returns
					 * Returns the OdimObject stored in the file
					 * 
					 * \throws OdimH5FormatException	Throwed when the HDF5 file is not a OdimH5 file 
					 * \throws OdimH5HDF5LibException	Throwed when a HDF5 exception occurs
					 *
					 * \n Get a OdimH5 object stored in an existing file
					 * \n The file will be opened with the I/O options indicated
					 * \n If the OdimH5 object is an object supported by the factory, a specialized object will be created.
					 *
					 * 
					 * \see openPolarVolume | openImageObject | openCompObject | openXsecObject  
					 */
					virtual OdimObject*		open(const std::string& path, int h5flags);
					
					/*!
					 * \brief
					 * Create a new OdimH5 PVOL object and the associated file
					 * 
					 * \param path			the file path where the object will be stored
					 * 
					 * \returns
					 * Returns the created PolarVolume object
					 * 
					 * \throws OdimH5HDF5LibException	Throwed when a HDF5 exception occurs	 
					 * 
					 * \n Create a OdimH5 PVOL object and the associated file. 
					 * \n If the file already exists, it will be recreated. 
					 * \n The file will be opened for input and output operations.
					 * 
					 * \see PolarVolume | openPolarVolume
					 */
					virtual PolarVolume*		createPolarVolume(const std::string& path);

					/*!
					 * \brief
					 * Create a new OdimH5 IMAGE object and the associated file
					 * 
					 * \param path			the file path where the object will be stored
					 * 
					 * \returns
					 * Returns the created ImageObject object
					 * 
					 * \throws OdimH5HDF5LibException	Throwed when a HDF5 exception occurs	 
					 * 
					 * \n Create a OdimH5 IMAGE object and the associated file. 
					 * \n If the file already exists, it will be recreated. 
					 * \n The file will be opened for input and output operations.
					 * 
					 * \see ImageObject | openImageObject
					 */
					virtual ImageObject*		createImageObject(const std::string& path);

					/*!
					 * \brief
					 * Create a new OdimH5 COMP object and the associated file
					 * 
					 * \param path			the file path where the object will be stored
					 * 
					 * \returns
					 * Returns the created CompObject object
					 * 
					 * \throws OdimH5HDF5LibException	Throwed when a HDF5 exception occurs	 
					 * 
					 * \n Create a OdimH5 COMP object and the associated file. 
					 * \n If the file already exists, it will be recreated. 
					 * \n The file will be opened for input and output operations.
					 * 
					 * \see CompObject | openCompObject
					 */
					virtual CompObject*		createCompObject(const std::string& path);
					
					/*!
					 * \brief
					 * Create a new OdimH5 XSEC object and the associated file
					 * 
					 * \param path			the file path where the object will be stored
					 * 
					 * \returns
					 * Returns the created XsecObject object
					 * 
					 * \throws OdimH5HDF5LibException	Throwed when a HDF5 exception occurs	 
					 * 
					 * \n Create a OdimH5 XSEC object and the associated file. 
					 * \n If the file already exists, it will be recreated. 
					 * \n The file will be opened for input and output operations.
					 * 
					 * \see XsecObject | openXsecObject
					 */
					virtual XsecObject*		createXsecObject(const std::string& path);
					
					/*!
					 * \brief
					 * Get a OdimH5 PVOL object from an existing file
					 * 
					 * \param path				the file path where the object is stored
					 * 
					 * \returns
					 * Returns the PolarVolume that represents the OdimH5 PVOL
					 * 
					 * \throws OdimH5FormatException	Throwed when the HDF5 file is not a OdimH5 file 
					 * \throws OdimH5HDF5LibException	Throwed when a HDF5 exception occurs
					 *
					 * \n Get a OdimH5 PVOL object stored in an existing file
					 * \n If the file does not contains a OdimH5 PVOL object an exception will occur
					 * \n The file will be opened  input and output operations
					 * 
					 * \see openPolarVolume
					 */
					virtual PolarVolume*		openPolarVolume(const std::string& path);
					
					/*!
					 * \brief
					 * Get a OdimH5 PVOL object from an existing file
					 * 
					 * \param path				the file path where the object is stored
					 * \param h5flags			the HDF5 I/O flags used to open the file
					 * 
					 * \returns
					 * Returns the PolarVolume that represents the OdimH5 PVOL
					 * 
					 * \throws OdimH5FormatException	Throwed when the HDF5 file is not a OdimH5 file 
					 * \throws OdimH5HDF5LibException	Throwed when a HDF5 exception occurs
					 *
					 * \n Get a OdimH5 PVOL object stored in an existing file
					 * \n If the file does not contains a OdimH5 PVOL object an exception will occur
					 * \n The file will be opened with the I/O options indicated
					 * 
					 * \see openPolarVolume
					 */
					virtual PolarVolume*		openPolarVolume(const std::string& path, int h5flags);

					/*!
					 * \brief
					 * Get a OdimH5 IMAGE object from an existing file
					 * 
					 * \param path				the file path where the object is stored
					 * 
					 * \returns
					 * Returns the ImageObject that represents the OdimH5 IMAGE
					 * 
					 * \throws OdimH5FormatException	Throwed when the HDF5 file is not a OdimH5 file 
					 * \throws OdimH5HDF5LibException	Throwed when a HDF5 exception occurs
					 *
					 * \n Get a OdimH5 ImageObject object stored in an existing file
					 * \n If the file does not contains a OdimH5 IMAGE object an exception will occur
					 * \n The file will be opened  input and output operations
					 * 
					 * \see openImageObject
					 */
					virtual ImageObject*		openImageObject(const std::string& path);
					
					/*!
					 * \brief
					 * Get a OdimH5 IMAGE object from an existing file
					 * 
					 * \param path				the file path where the object is stored
					 * \param h5flags			the HDF5 I/O flags used to open the file
					 * 
					 * \returns
					 * Returns the ImageObject that represents the OdimH5 IMAGE 
					 * 
					 * \throws OdimH5FormatException	Throwed when the HDF5 file is not a OdimH5 file 
					 * \throws OdimH5HDF5LibException	Throwed when a HDF5 exception occurs
					 *
					 * \n Get a OdimH5 ImageObject object stored in an existing file
					 * \n If the file does not contains a OdimH5 IMAGE object an exception will occur
					 * \n The file will be opened with the I/O options indicated
					 * 
					 * \see openImageObject
					 */
					virtual ImageObject*		openImageObject(const std::string& path, int h5flags);
					
					/*!
					 * \brief
					 * Get a OdimH5 COMP object from an existing file
					 * 
					 * \param path				the file path where the object is stored
					 * 
					 * \returns
					 * Returns the CompObject that represents the OdimH5 COMP
					 * 
					 * \throws OdimH5FormatException	Throwed when the HDF5 file is not a OdimH5 file 
					 * \throws OdimH5HDF5LibException	Throwed when a HDF5 exception occurs
					 *
					 * \n Get a OdimH5 CompObject object stored in an existing file
					 * \n If the file does not contains a OdimH5 COMP object an exception will occur
					 * \n The file will be opened  input and output operations
					 * 
					 * \see openCompObject
					 */
					virtual CompObject*		openCompObject(const std::string& path);
					
					/*!
					 * \brief
					 * Get a OdimH5 COMP object from an existing file
					 * 
					 * \param path				the file path where the object is stored
					 * \param h5flags			the HDF5 I/O flags used to open the file
					 * 
					 * \returns
					 * Returns the CompObject that represents the OdimH5 COMP 
					 * 
					 * \throws OdimH5FormatException	Throwed when the HDF5 file is not a OdimH5 file 
					 * \throws OdimH5HDF5LibException	Throwed when a HDF5 exception occurs
					 *
					 * \n Get a OdimH5 CompObject object stored in an existing file
					 * \n If the file does not contains a OdimH5 COMP object an exception will occur
					 * \n The file will be opened with the I/O options indicated
					 * 
					 * \see openCompObject
					 */
					virtual CompObject*		openCompObject(const std::string& path, int h5flags);
					
					/*!
					 * \brief
					 * Get a OdimH5 XSEC object from an existing file
					 * 
					 * \param path				the file path where the object is stored
					 * 
					 * \returns
					 * Returns the XsecObject that represents the OdimH5 XSEC
					 * 
					 * \throws OdimH5FormatException	Throwed when the HDF5 file is not a OdimH5 file 
					 * \throws OdimH5HDF5LibException	Throwed when a HDF5 exception occurs
					 *
					 * \n Get a OdimH5 XsecObject object stored in an existing file
					 * \n If the file does not contains a OdimH5 XSEC object an exception will occur
					 * \n The file will be opened  input and output operations
					 * 
					 * \see openXsecObject
					 */
					virtual XsecObject*		openXsecObject(const std::string& path);
					
					/*!
					 * \brief
					 * Get a OdimH5 XSEC object from an existing file
					 * 
					 * \param path				the file path where the object is stored
					 * \param h5flags			the HDF5 I/O flags used to open the file
					 * 
					 * \returns
					 * Returns the XsecObject that represents the OdimH5 XSEC 
					 * 
					 * \throws OdimH5FormatException	Throwed when the HDF5 file is not a OdimH5 file 
					 * \throws OdimH5HDF5LibException	Throwed when a HDF5 exception occurs
					 *
					 * \n Get a OdimH5 XsecObject object stored in an existing file
					 * \n If the file does not contains a OdimH5 XSEC object an exception will occur
					 * \n The file will be opened with the I/O options indicated
					 * 
					 * \see openXsecObject
					 */
					virtual XsecObject*		openXsecObject(const std::string& path, int h5flags);
					
					/*!
					 * \brief
					 * Create a dumper for OdimH5 objects
					 * 
					 * \returns
					 * Returns an object that can create textual representation of OdimH5 objects
					 * 
					 * \n The dumper created can operate on on OdimH5 v2.1 objects
					 * 
					 * \see ObjectDumper
					 */
					virtual OdimObjectDumper*	getDumper();
					
			protected:
				  virtual H5::H5File* openOdimFile(const std::string& path, int h5flags, std::string& objtype);	
					  virtual PolarVolume* createPolarVolume(H5::H5File* file);
					  virtual ImageObject* createImageObject(H5::H5File* file);
					  virtual CompObject*  createCompObject (H5::H5File* file);
					  virtual XsecObject*  createXsecObject (H5::H5File* file);
					  
		};
	
		/*===========================================================================*/
		
}

#endif





























