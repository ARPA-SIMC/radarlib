/*
 * Radar Library
 *
 * Copyright (C) 2.19-2010  ARPA-SIM <urpsim@smr.arpa.emr.it>
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
 *  \brief Main library classes (generic objects, polar volumes etc.)
 */

#ifndef __RADAR_ODIMH5V21_CLASES_HPP__
#define __RADAR_ODIMH5V21_CLASES_HPP__

#include <radarlib/defs.h>
#include <radarlib/odimh5v21_const.hpp>
#include <radarlib/odimh5v21_support.hpp>
#include <radarlib/odimh5v21_exceptions.hpp>
#include <radarlib/odimh5v21_metadata.hpp>

#include <set>

namespace OdimH5v21 
{

/*===========================================================================*/
/* FORWARD DECLARATIONS */
/*===========================================================================*/

class OdimFactory;
class OdimObject;
class OdimDataset;
class OdimData;
class OdimQuality;
class OdimObjectDumper;
class PolarVolume;
class PolarScan;
class PolarScanData;
class Object_2D;
class HorizontalObject_2D; 
class ImageObject; 
class CompObject; 
class XsecObject; 
class Product_2D;
class Horizontal_Product_2D;
class Product_PPI;
class Product_CAPPI;
class Product_PCAPPI;
class Product_ETOP;
class Product_MAX;
class Product_RR;
class Product_VIL;
class Product_LBM;
class Product_COMP;
class Vertical_Product_2D;
class Product_Panel;
class Product_XSEC;
class Product_RHI;
class Product_VSP;
class Product_HSP;
class Product_2D_Data;
class Vertical_Product_2D_Data;
/*===========================================================================*/
/* ODIM ROOT OBJECT */
/*===========================================================================*/

/*! 
 * \brief Generic OdimH5 v2.1 object
 * 
 * All OdimH5 objects have the same general structure. \n
 * This class allows users to manipulate OdimH5 objects in the most generic way. \n
 * This means that users can manipulate only Odim datasets and common mandatory attributes. \n
 * Only mandatory informations common to every OdimH5 objects are automatic written or checked by the internal implementatino. \n
 * Users are responsible for manipulating informations following OdimH5 specifications. \n
 * 
 * \see OdimDataset
 */
class RADAR_API OdimObject : public WHATRootMetadata
{ 
public: 
	virtual ~OdimObject(); 
 
	/*!  
	 * \brief Get OdimH5 conventions attribute value 
	 * 
	 * \throws OdimH5Exception		if an unexpected error occurs 
	 */ 
	virtual std::string	getConventions(); 
	/*!  
	 * \brief Set OdimH5 conventions attribute value to the value required by OdimH5 specification 
	 * 
	 * \throws OdimH5Exception		if an unexpected error occurs 
	 */ 
	virtual void		setConventions();	 
 
	/*!  
	 * \brief Get the associated HDF5 file object 
	 * 
	 * Get the associated HDF5 file object  
	 * \remarks user must not delete this object 
	 * \throws OdimH5Exception		if an unexpected error occurs 
	 */ 
	virtual H5::H5File*	getFile();	 
	/*!  
	 * \brief Get the HDF5 group associated to this object 
	 * 
	 * Get the HDF5 group associated to this object  
	 * \remarks user must not delete this object 
	 * \throws OdimH5Exception		if an unexpected error occurs 
	 */ 
	virtual H5::Group*	getH5Object();	 
 
	/*!  
	 * \brief Test is the WHAT attributes group exist
	 * 
	 * Check if the WHAT attributes group of this object exist.
	 * \throws OdimH5Exception		if an unexpected error occurs 
	 */ 
	virtual bool	existWhat();

	/*!  
	 * \brief Test is the WHERE attributes group exist
	 * 
	 * Check if the WHERE attributes group of this object exist.
	 * \throws OdimH5Exception		if an unexpected error occurs 
	 */ 
	virtual bool 	existWhere(); 
	/*!  
	 * \brief Test is the HOW attributes group exist
	 * 
	 * Check if the HOW attributes group of this object exist.
	 * \throws OdimH5Exception		if an unexpected error occurs 
	 */ 
	virtual bool 	existHow(); 
 
	/*!  
	 * \brief Get the WHAT attributes group 
	 * 
	 * Get the WHAT attributes group of this object. If it does not exist it will be created 
	 * \remarks user must not delete this object 
	 * \throws OdimH5Exception		if an unexpected error occurs 
	 */ 
	virtual MetadataGroup*	getWhat(); 
	/*!  
	 * \brief Get the WHERE attributes group 
	 * 
	 * Get the WHERE attributes group of this object. If it does not exist it will be created 
	 * \remarks user must not delete this object 
	 * \throws OdimH5Exception		if an unexpected error occurs 
	 */ 
	virtual MetadataGroup*	getWhere(); 
	/*!  
	 * \brief Get the HOW attributes group 
	 * 
	 * Get the HOW attributes group of this object. If it does not exist it will be created 
	 * \remarks user must not delete this object 
	 * \throws OdimH5Exception		if an unexpected error occurs 
	 */ 

	virtual MetadataGroup*	getHow(); 
	virtual std::string	getObject	();			 
	virtual void		setObject	(const std::string& val); 
	virtual std::string	getVersion	();			 
	virtual void		setVersion	(const std::string& val); 
	virtual time_t		getDateTime	();			 
	virtual void		setDateTime	(const time_t val);	 
	virtual SourceInfo	getSource	(); 			 
	virtual void		setSource	(const SourceInfo& val); 
 
	/*!  
	 * \brief Get the number of datasets in the file 
	 * 
	 * Get the number of datasets in the odim object 
	 * \throws OdimH5Exception		if an unexpected error occurs 
	 */ 
	virtual int		getDatasetCount(); 
	/*!  
	 * \brief Create a new dataset 
	 * 
	 * Create a new dataset in the odim object 
	 * \returns				the new OdimDataset object associated to the new HDF5 group 
	 * \throws OdimH5Exception		if an unexpected error occurs 
	 * \remarks				User is responsible for deleting the returned object  
	 */ 
	virtual OdimDataset*	createDataset(); 
	/*!  
	 * \brief Get a dataset  
	 * 
	 * Get the existing dataset with the given index 
	 * \param index				the dataset index from 0 to n-1 
	 * \returns				the OdimDataset object associated to the new HDF5 group or NULL if the dataset does not exist 
	 * \throws OdimH5Exception		if an unexpected error occurs 
	 * \remarks				User is responsible for deleting the returned object  
	 */ 
	virtual OdimDataset*	getDataset(int index); 
	/*!  
	 * \brief Delete a odim dataset group from the odim object 
	 * 
	 * Delete the odim dataset with the given index. Nothing is done if the dataset does not exist 
	 * \param index				the dataset index from 0 to n-1 
	 * \throws OdimH5Exception		if an unexpected error occurs 
	 * \remarks				User is responsible for deleting the returned object  
	 */ 
	virtual void		removeDataset(int index); 
 
 
protected:	 
	H5::H5File*	    file; 
	H5::Group*	    group; 
	MetadataGroup*	meta_what; 
	MetadataGroup*	meta_where; 
	MetadataGroup*	meta_how;	 
 
	/* uses cannot directly create OdimH5 objects, only factories provide functions to do it */ 
	friend class OdimFactory; 
	OdimObject(H5::H5File*	file); 
 
	virtual H5::Group*	createDatasetGroup();	 
	virtual H5::Group*	getDatasetGroup(int num); 
 
	virtual void		setMandatoryInformations	(); 
	virtual void		checkMandatoryInformations	(); 
 
}; 
 
/*===========================================================================*/ 
/* ODIM DATASET */ 
/*===========================================================================*/ 
 
/*!  
 * \brief Generic OdimH5 v2.1 dataset group 
 *  
 * All OdimH5 objects split informations into a variable number of datasets. \n 
 * This class represents a generic OdimH5 dataset. \n 
 * Generic datasets allow only to create/remove sub data and attributes. \n 
 * Users are responsible for manipulating informations following OdimH5 specifications. \n 
 *  
 * \see OdimObject, OdimData 
 */ 
class RADAR_API OdimDataset 
{ 
public: 
	virtual ~OdimDataset(); 
 
	/*!  
	 * \brief Get the HDF5 group associated to this object 
	 * 
	 * Get the HDF5 group associated to this object  
	 * \remarks user must not delete this object 
	 * \throws OdimH5Exception		if an unexpected error occurs 
	 */ 
	virtual H5::Group*	getH5Object(); 
 
	/*!  
	 * \brief Test is the WHAT attributes group exist
	 * 
	 * Check if the WHAT attributes group of this object exist.
	 * \throws OdimH5Exception		if an unexpected error occurs 
	 */ 
	virtual bool	existWhat();

	/*!  
	 * \brief Test is the WHERE attributes group exist
	 * 
	 * Check if the WHERE attributes group of this object exist.
	 * \throws OdimH5Exception		if an unexpected error occurs 
	 */ 
	virtual bool 	existWhere(); 
	/*!  
	 * \brief Test is the HOW attributes group exist
	 * 
	 * Check if the HOW attributes group of this object exist.
	 * \throws OdimH5Exception		if an unexpected error occurs 
	 */ 
	virtual bool 	existHow(); 
	/*!  
	 * \brief Get the WHAT attributes group 
	 * 
	 * Get the WHAT attributes group of this object. If it does not exist it will be created 
	 * \remarks user must not delete this object 
	 * \throws OdimH5Exception		if an unexpected error occurs 
	 */ 
	virtual MetadataGroup*	getWhat(); 
	/*!  
	 * \brief Get the WHERE attributes group 
	 * 
	 * Get the WHERE attributes group of this object. If it does not exist it will be created 
	 * \remarks user must not delete this object 
	 * \throws OdimH5Exception		if an unexpected error occurs 
	 */ 
	virtual MetadataGroup*	getWhere(); 
	/*!  
	 * \brief Get the HOW attributes group 
	 * 
	 * Get the HOW attributes group of this object. If it does not exist it will be created 
	 * \remarks user must not delete this object 
	 * \throws OdimH5Exception		if an unexpected error occurs 
	 */ 
	virtual MetadataGroup*	getHow(); 
 
	/*!  
	 * \brief Get the number of 'data' groups inside this dataset group 
	 * 
	 * \returns				the number of 'data' groups 
	 * \throws OdimH5Exception		if an unexpected error occurs 
	 */ 
	virtual int		getDataCount();	 
	/*!  
	 * \brief Create a new group 'data' inside this dataset 
	 * 
	 * \returns				the object associated to the new 'data' group 
	 * \throws OdimH5Exception		if an unexpected error occurs 
	 * \remarks				User is responsible for deleting the returned object  
	 */ 
	virtual OdimData*	createData();	 
	/*!  
	 * \brief Get an existing dataset using the given index 
	 * 
	 * Get an existing dataset using the given index 
	 * \param index				the dataset index from 0 to n-1 
	 * \returns				the OdimData object associated to the HDF5 group or NULL if the group does not exist 
	 * \throws OdimH5Exception		if an unexpected error occurs 
	 * \remarks				User is responsible for deleting the returned object  
	 */ 
	virtual OdimData*	getData(int index); 
	/*!  
	 * \brief Remove a 'data' group from this dataset 
	 * 
	 * Remove a 'data' group from this dataset 
	 * \param index				the dataset index from 0 to n-1 
	 * \throws OdimH5Exception		if an unexpected error occurs 
	 */ 
	virtual void		removeData(int index); 
 
protected: 
	H5::Group*	group;	 
	MetadataGroup*	meta_what; 
	MetadataGroup*	meta_where; 
	MetadataGroup*	meta_how; 
 
	/* uses cannot directly create OdimH5 objects, only factories provide functions to do it */ 
	friend class OdimObject; 
	OdimDataset(H5::Group* group); 
 
	virtual H5::Group*	createDataGroup();	 
	virtual H5::Group*	getDataGroup(int num);	 
}; 
 
/*===========================================================================*/ 
/* ODIM DATA */ 
/*===========================================================================*/ 
 
/*!  
 * \brief Generic OdimH5 v2.1 data group 
 *  
 * All OdimH5 datasets can store one o more data groups. \n 
 * This class represents a generic OdimH5 data group. \n 
 * Generic data allow only to read/write attributes and matrices of binary data (RayMatrix). \n 
 * Users are responsible for manipulating informations following OdimH5 specifications. \n 
 *  
 * \see OdimDataset, RayMatrix 
 */ 
class RADAR_API OdimData 
{ 
public: 
	virtual ~OdimData(); 
 
	/*!  
	 * \brief Get the HDF5 group associated to this object 
	 * 
	 * Get the HDF5 group associated to this object  
	 * \remarks user must not delete this object 
	 * \throws OdimH5Exception		if an unexpected error occurs 
	 */ 
	virtual H5::Group*	getH5Object(); 
	/*!  
	 * \brief Test is the WHAT attributes group exist
	 * 
	 * Check if the WHAT attributes group of this object exist.
	 * \throws OdimH5Exception		if an unexpected error occurs 
	 */ 
	virtual bool	existWhat();

	/*!  
	 * \brief Test is the WHERE attributes group exist
	 * 
	 * Check if the WHERE attributes group of this object exist.
	 * \throws OdimH5Exception		if an unexpected error occurs 
	 */ 
	virtual bool 	existWhere(); 
	/*!  
	 * \brief Test is the HOW attributes group exist
	 * 
	 * Check if the HOW attributes group of this object exist.
	 * \throws OdimH5Exception		if an unexpected error occurs 
	 */ 
	virtual bool 	existHow(); 
	/*!  
	 * \brief Get the WHAT attributes group 
	 * 
	 * Get the WHAT attributes group of this object. If it does not exist it will be created 
	 * \remarks user must not delete this object 
	 * \throws OdimH5Exception		if an unexpected error occurs 
	 */ 
	virtual MetadataGroup*	getWhat(); 
	/*!  
	 * \brief Get the WHERE attributes group 
	 * 
	 * Get the WHERE attributes group of this object. If it does not exist it will be created 
	 * \remarks user must not delete this object 
	 * \throws OdimH5Exception		if an unexpected error occurs 
	 */ 
	virtual MetadataGroup*	getWhere(); 
	/*!  
	 * \brief Get the HOW attributes group 
	 * 
	 * Get the HOW attributes group of this object. If it does not exist it will be created 
	 * \remarks user must not delete this object 
	 * \throws OdimH5Exception		if an unexpected error occurs 
	 */ 
	virtual MetadataGroup*	getHow(); 
	/*!  
	 * \brief Get the HDF5 atom type of the elements of the HDF5 dataset contained inside this 'data' group 
	 * 
	 * Get the HDF5 atom type of the elements of the HDF5 dataset contained inside this 'data' group.  
	 * If the HDF5 dataset is not present then NATIVE_OPAQUE will be returned. 
	 * OdimH5 allow only atomic types: char, schar, uchar, short, ushort, int, uint, long, ulong, llong, ullong, float, double. 
	 * \throws OdimH5Exception		if an unexpected error occurs 
	 * \throws OdimH5UnsupportedException	if the dataset type cannot be converted to an atomic type 
	 */ 
	virtual H5::AtomType	getDataType(); 
	/*!  
	 * \brief Get the width (cols num) of the matrix associated to this data group 
	 * 
	 * \throws OdimH5Exception		if an unexpected error occurs 
	 */ 
	virtual int		getDataWidth(); 
	/*!  
	 * \brief Get the height (rows num) of the matrix associated to this data group 
	 * 
	 * \throws OdimH5Exception		if an unexpected error occurs 
	 */ 
	virtual int		getDataHeight(); 
	/*!  
	 * \brief Get height and width (rows and cols num) of the matrix associated to this data group 
	 * 
	 * \throws OdimH5Exception		if an unexpected error occurs 
	 */ 
	virtual void		getDataDimension(int* height, int* width); 
	/*!  
	 * \brief Write data to the matrix associated to this 'data' group 
	 * 
	 * Write data to the matrix associated to this 'data' group from the given buffer where each element has the given type. \n 
	 * The buffer must be a continuous memory array logically organized as a matrix divided in rows and cols. \n	  
	 * The size of the buffer must be at least equal to (height * width * elemtype.getSize()). Otherwise a buffer overflow will occur. \n 
	 * \param buff				the buffer containing the data to write 
	 * \param width				the number of cols in the matrix 
	 * \param height			the number of rows in the matrix 
	 * \param elemtype			the HDF5 datatype of the buffer's elements 
	 * \throws OdimH5Exception		if an unexpected error occurs 
	 */ 
	virtual void		writeData(const void* buff,		int width, int height, const H5::DataType& elemtype); 
	/*!  
	 * \brief Write data to the matrix associated to this 'data' group 
	 * 
	 * Write data to the matrix associated to this 'data' group from the given 8 bit signed buffer 	  
	 * \param buff				the buffer containing the data to write 
	 * \param width				the number of cols in the matrix 
	 * \param height			the number of rows in the matrix 
	 * \throws OdimH5Exception		if an unexpected error occurs 
	 */ 
	virtual void		writeData(const char* buff,		int width, int height); 
	/*!  
	 * \brief Write data to the matrix associated to this 'data' group 
	 * 
	 * Write data to the matrix associated to this 'data' group from the given 8 bit unsigned buffer 	  
	 * \param buff				the buffer containing the data to write 
	 * \param width				the number of cols in the matrix 
	 * \param height			the number of rows in the matrix 
	 * \throws OdimH5Exception		if an unexpected error occurs 
	 */ 
	virtual void		writeData(const unsigned char* buff,	int width, int height); 
	/*!  
	 * \brief Write data to the matrix associated to this 'data' group 
	 * 
	 * Write data to the matrix associated to this 'data' group from the given 16 bit unsigned char buffer 	  
	 * \param buff				the buffer containing the data to write 
	 * \param width				the number of cols in the matrix 
	 * \param height			the number of rows in the matrix 
	 * \throws OdimH5Exception		if an unexpected error occurs 
	 */ 
	virtual void		writeData(const unsigned short* buff,	int width, int height); 
	/*!  
	 * \brief Write data to the matrix associated to this 'data' group 
	 * 
	 * Write data to the matrix associated to this 'data' group from the given 32 bit floating point buffer 	  
	 * \param buff				the buffer containing the data to write 
	 * \param width				the number of cols in the matrix 
	 * \param height			the number of rows in the matrix 
	 * \throws OdimH5Exception		if an unexpected error occurs 
	 */ 
	virtual void		writeData(const float* buff,		int width, int height); 
 
	/*!  
	 * \brief Write data to the matrix associated to this 'data' group 
	 * 
	 * Write data to the matrix associated to this 'data' group from the DataMatrix object. \n 
	 * The HDF5 dataset will be created using the size and type of the given matrix object. \n 
	 * \param matrix			the matrix object containing the data 
	 * \throws OdimH5Exception		if an unexpected error occurs 
	 */ 
	virtual void		writeData(const DataMatrix<char>& matrix);	 
	/*!  
	 * \brief Write data to the matrix associated to this 'data' group 
	 * 
	 * Write data to the matrix associated to this 'data' group from the DataMatrix object. \n 
	 * The HDF5 dataset will be created using the size and type of the given matrix object. \n 
	 * \param matrix			the matrix object containing the data 
	 * \throws OdimH5Exception		if an unexpected error occurs 
	 */ 
	virtual void		writeData(const DataMatrix<unsigned char>& matrix); 
	/*!  
	 * \brief Write data to the matrix associated to this 'data' group 
	 * 
	 * Write data to the matrix associated to this 'data' group from the DataMatrix object. \n 
	 * The HDF5 dataset will be created using the size and type of the given matrix object. \n 
	 * \param matrix			the matrix object containing the data 
	 * \throws OdimH5Exception		if an unexpected error occurs 
	 */ 
	virtual void		writeData(const DataMatrix<unsigned short>& matrix); 
	/*!  
	 * \brief Write data to the matrix associated to this 'data' group 
	 * 
	 * Write data to the matrix associated to this 'data' group from the DataMatrix object 
	 * The HDF5 dataset will be created using the size and type of the given matrix object 
	 * \param matrix			the matrix object containing the data 
	 * \throws OdimH5Exception		if an unexpected error occurs 
	 */ 
	virtual void		writeData(const DataMatrix<float>& matrix);	 
	/*!  
	 * \brief Read data from the dataset of this 'data' group  
	 * 
	 * Read data from the dataset of this 'data' group into the given buffer. \n 
	 * The buffer must be large enough to store all elements in the HDF5 dataset. \n 
	 * The minimum size in byte is (getDataWidth() x getDataHeight() x getDataType().getSize()). \n 
	 * \param buffer			the buffer to store the loaded data 
	 * \throws OdimH5Exception		if an unexpected error occurs 
	 */ 
	virtual void		readData(void* buffer); 
	/*!  
	 * \brief Get the number of 'quality' groups inside this data group 
	 * 
	 * \returns				the number of 'quality' groups 
	 * \throws OdimH5Exception		if an unexpected error occurs 
	 */ 
	virtual int		getQualityCount();	 
	/*!  
	 * \brief Create a new group 'Quality' inside this data 
	 * 
	 * \returns				the object associated to the new 'quality' group 
	 * \throws OdimH5Exception		if an unexpected error occurs 
	 * \remarks				User is responsible for deleting the returned object  
	 */ 
	virtual OdimQuality*	createQuality();	 
	/*!  
	 * \brief Get an existing Quality group using the given index 
	 * 
	 * Get an existing dataset using the given index 
	 * \param index				the quality index from 0 to n-1 
	 * \returns				the OdimQuality object associated to the HDF5 group or NULL if the group does not exist 
	 * \throws OdimH5Exception		if an unexpected error occurs 
	 * \remarks				User is responsible for deleting the returned object  
	 */ 
	virtual OdimQuality*	getQuality(int index); 
	/*!  
	 * \brief Remove a 'quality' group from this dataset 
	 * 
	 * Remove a 'quality' group from this dataset 
	 * \param index				the dataset index from 0 to n-1 
	 * \throws OdimH5Exception		if an unexpected error occurs 
	 */ 
	virtual void		removeQuality(int index); 
 
protected: 
	H5::Group*	group;		 
	MetadataGroup*	meta_what; 
	MetadataGroup*	meta_where; 
	MetadataGroup*	meta_how; 
 
	/* uses cannot directly create OdimH5 objects, only factories provide functions to do it */ 
	friend class OdimDataset; 
	OdimData(H5::Group* group); 
 
	virtual H5::DataSet*	getData(); 
	virtual H5::Group*	createQualityGroup();	 
	virtual H5::Group*	getQualityGroup(int num);	 
}; 
 
/*===========================================================================*/ 
/* ODIM QUALITY*/ 
/*===========================================================================*/ 
 
/*!  
 * \brief Generic OdimH5 v2.1 quality group 
 *  
 * All OdimH5 data can store one o more quality groups. \n 
 * This class represents a generic OdimH5 quality group. \n 
 * Generic data allow only to read/write attributes and matrices of binary data (RayMatrix). \n 
 * Users are responsible for manipulating informations following OdimH5 specifications. \n 
 *  
 * \see OdimDataset, RayMatrix 
 */ 
class RADAR_API OdimQuality
{ 
public: 
	virtual ~OdimQuality(); 
 
	/*!  
	 * \brief Get the HDF5 group associated to this object 
	 * 
	 * Get the HDF5 group associated to this object  
	 * \remarks user must not delete this object 
	 * \throws OdimH5Exception		if an unexpected error occurs 
	 */ 
	virtual H5::Group*	getH5Object(); 
	/*!  
	 * \brief Test is the WHAT attributes group exist
	 * 
	 * Check if the WHAT attributes group of this object exist.
	 * \throws OdimH5Exception		if an unexpected error occurs 
	 */ 
	virtual bool	existWhat();

	/*!  
	 * \brief Test is the WHERE attributes group exist
	 * 
	 * Check if the WHERE attributes group of this object exist.
	 * \throws OdimH5Exception		if an unexpected error occurs 
	 */ 
	virtual bool 	existWhere(); 
	/*!  
	 * \brief Test is the HOW attributes group exist
	 * 
	 * Check if the HOW attributes group of this object exist.
	 * \throws OdimH5Exception		if an unexpected error occurs 
	 */ 
	virtual bool 	existHow(); 
 
	/*!  
	 * \brief Get the WHAT attributes group 
	 * 
	 * Get the WHAT attributes group of this object. If it does not exist it will be created 
	 * \remarks user must not delete this object 
	 * \throws OdimH5Exception		if an unexpected error occurs 
	 */ 
	virtual MetadataGroup*	getWhat(); 
	/*!  
	 * \brief Get the WHERE attributes group 
	 * 
	 * Get the WHERE attributes group of this object. If it does not exist it will be created 
	 * \remarks user must not delete this object 
	 * \throws OdimH5Exception		if an unexpected error occurs 
	 */ 
	virtual MetadataGroup*	getWhere(); 
	/*!  
	 * \brief Get the HOW attributes group 
	 * 
	 * Get the HOW attributes group of this object. If it does not exist it will be created 
	 * \remarks user must not delete this object 
	 * \throws OdimH5Exception		if an unexpected error occurs 
	 */ 
	virtual MetadataGroup*	getHow(); 
	/*!  
	 * \brief Get the HDF5 atom type of the elements of the HDF5 dataset contained inside this 'quality' group 
	 * 
	 * Get the HDF5 atom type of the elements of the HDF5 dataset contained inside this 'quality' group.  
	 * If the HDF5 dataset is not present then NATIVE_OPAQUE will be returned. 
	 * OdimH5 allow only atomic types: char, schar, uchar, short, ushort, int, uint, long, ulong, llong, ullong, float, double. 
	 * \throws OdimH5Exception		if an unexpected error occurs 
	 * \throws OdimH5UnsupportedException	if the dataset type cannot be converted to an atomic type 
	 */ 
	virtual H5::AtomType	getQualityType(); 
	/*!  
	 * \brief Get the width (cols num) of the matrix associated to this quality group 
	 * 
	 * \throws OdimH5Exception		if an unexpected error occurs 
	 */ 
	virtual int		getQualityWidth(); 
	/*!  
	 * \brief Get the height (rows num) of the matrix associated to this quality group 
	 * 
	 * \throws OdimH5Exception		if an unexpected error occurs 
	 */ 
	virtual int		getQualityHeight(); 
	/*!  
	 * \brief Get height and width (rows and cols num) of the matrix associated to this quality group 
	 * 
	 * \throws OdimH5Exception		if an unexpected error occurs 
	 */ 
	virtual void		getQualityDimension(int* height, int* width); 
	/*!  
	 * \brief Write data to the matrix associated to this 'quality' group 
	 * 
	 * Write data to the matrix associated to this 'quality' group from the given buffer where each element has the given type. \n 
	 * The buffer must be a continuous memory array logically organized as a matrix divided in rows and cols. \n	  
	 * The size of the buffer must be at least equal to (height * width * elemtype.getSize()). Otherwise a buffer overflow will occur. \n 
	 * \param buff				the buffer containing the quality to write 
	 * \param width				the number of cols in the matrix 
	 * \param height			the number of rows in the matrix 
	 * \param elemtype			the HDF5 datatype of the buffer's elements 
	 * \throws OdimH5Exception		if an unexpected error occurs 
	 */ 
	virtual void		writeQuality(const void* buff,		int width, int height, const H5::DataType& elemtype); 
	/*!  
	 * \brief Write data to the matrix associated to this 'quality' group 
	 * 
	 * Write data to the matrix associated to this 'quality' group from the given 8 bit signed buffer 	  
	 * \param buff				the buffer containing the data to write 
	 * \param width				the number of cols in the matrix 
	 * \param height			the number of rows in the matrix 
	 * \throws OdimH5Exception		if an unexpected error occurs 
	 */ 
	virtual void		writeQuality(const char* buff,		int width, int height); 
	/*!  
	 * \brief Write data to the matrix associated to this 'quality' group 
	 * 
	 * Write data to the matrix associated to this 'quality' group from the given 8 bit unsigned buffer 	  
	 * \param buff				the buffer containing the quality to write 
	 * \param width				the number of cols in the matrix 
	 * \param height			the number of rows in the matrix 
	 * \throws OdimH5Exception		if an unexpected error occurs 
	 */ 
	virtual void		writeQuality(const unsigned char* buff,	int width, int height); 
	/*!  
	 * \brief Write data to the matrix associated to this 'quality' group 
	 * 
	 * Write data to the matrix associated to this 'quality' group from the given 16 bit unsigned char buffer 	  
	 * \param buff				the buffer containing the quality to write 
	 * \param width				the number of cols in the matrix 
	 * \param height			the number of rows in the matrix 
	 * \throws OdimH5Exception		if an unexpected error occurs 
	 */ 
	virtual void		writeQuality(const unsigned short* buff,	int width, int height); 
	/*!  
	 * \brief Write data to the matrix associated to this 'quality' group 
	 * 
	 * Write data to the matrix associated to this 'quality' group from the given 32 bit floating point buffer 	  
	 * \param buff				the buffer containing the quality to write 
	 * \param width				the number of cols in the matrix 
	 * \param height			the number of rows in the matrix 
	 * \throws OdimH5Exception		if an unexpected error occurs 
	 */ 
	virtual void		writeQuality(const float* buff,		int width, int height); 
 
	/*!  
	 * \brief Write data to the matrix associated to this 'quality' group 
	 * 
	 * Write data to the matrix associated to this 'quality' group from the DataMatrix object. \n 
	 * The HDF5 dataset will be created using the size and type of the given matrix object. \n 
	 * \param matrix			the matrix object containing the data 
	 * \throws OdimH5Exception		if an unexpected error occurs 
	 */ 
	virtual void		writeQuality(const DataMatrix<char>& matrix);	 
	/*!  
	 * \brief Write data to the matrix associated to this 'quality' group 
	 * 
	 * Write data to the matrix associated to this 'quality' group from the DataMatrix object. \n 
	 * The HDF5 dataset will be created using the size and type of the given matrix object. \n 
	 * \param matrix			the matrix object containing the data 
	 * \throws OdimH5Exception		if an unexpected error occurs 
	 */ 
	virtual void		writeQuality(const DataMatrix<unsigned char>& matrix); 
	/*!  
	 * \brief Write data to the matrix associated to this 'quality' group 
	 * 
	 * Write data to the matrix associated to this 'quality' group from the DataMatrix object. \n 
	 * The HDF5 dataset will be created using the size and type of the given matrix object. \n 
	 * \param matrix			the matrix object containing the data 
	 * \throws OdimH5Exception		if an unexpected error occurs 
	 */ 
	virtual void		writeQuality(const DataMatrix<unsigned short>& matrix); 
	/*!  
	 * \brief Write data to the matrix associated to this 'quality' group 
	 * 
	 * Write data to the matrix associated to this 'quality' group from the DataMatrix object 
	 * The HDF5 dataset will be created using the size and type of the given matrix object 
	 * \param matrix			the matrix object containing the data 
	 * \throws OdimH5Exception		if an unexpected error occurs 
	 */ 
	virtual void		writeQuality(const DataMatrix<float>& matrix);	 
	/*!  
	 * \brief Read data from the dataset of this 'quality' group  
	 * 
	 * Read data from the dataset of this 'quality' group into the given buffer. \n 
	 * The buffer must be large enough to store all elements in the HDF5 dataset. \n 
	 * The minimum size in byte is (getDataWidth() x getDataHeight() x getDataType().getSize()). \n 
	 * \param buffer			the buffer to store the loaded data 
	 * \throws OdimH5Exception		if an unexpected error occurs 
	 */ 
	virtual void		readQuality(void* buffer); 
 
protected: 
	H5::Group*	group;		 
	MetadataGroup*	meta_what; 
	MetadataGroup*	meta_where; 
	MetadataGroup*	meta_how; 
 
	/* uses cannot directly create OdimH5 objects, only factories provide functions to do it */ 
	friend class OdimData; 
	friend class Product_2D_Data; 
	OdimQuality(H5::Group* group); 
 
	virtual H5::DataSet*	getData(); 
}; 
 
/*===========================================================================*/ 
/* POLAR VOLUME */ 
/*===========================================================================*/ 
 
/*!  
 * \brief OdimH5 v2.1 Polar Volume 
 *  
 * \n This class represents an OdimH5 PVOL composed of SCAN objects. \n 
 * \n Polar volume specific attributes can be manipulated using specific methods. \n 
 * \n Generic data manipulations can be done using methods provided by the OdimObject interface. \n 
 *  
 * \see PolarScan 
 */ 
class RADAR_API PolarVolume : public OdimObject, public WHERERootMetadata, public HOWRootMetadata 
{ 
public: 
	virtual ~PolarVolume(); 
 
	virtual double		getLongitude		();	 
	virtual void		setLongitude		(double val); 
	virtual double		getLatitude		(); 	 
	virtual void		setLatitude		(double val);  
	virtual double		getAltitude		(); 	 
	virtual void		setAltitude		(double val);  
 
	virtual std::string	getTaskOrProdGen	();			 
	virtual void		setTaskOrProdGen	(const std::string& val); 
	virtual time_t		getStartEpochs		();			 
	virtual void		setStartEpochs		(time_t val);		 
	virtual time_t		getEndEpochs		();			 
	virtual void		setEndEpochs		(time_t val);		 
	virtual std::string	getSystem		();			 
	virtual void		setSystem		(const std::string& val); 
	virtual std::string	getSoftware		();			 
	virtual void		setSoftware		(const std::string& val); 
	virtual std::string	getSoftwareVer		();			 
	virtual void		setSoftwareVer		(const std::string& val); 
	virtual double		getZR_A			();			 
	virtual void		setZR_A			(double val);		 
	virtual double		getZR_B			();			 
	virtual void		setZR_B			(double val);		 
	virtual double		getKR_A			();			 
	virtual void		setKR_A			(double val);		 
	virtual double		getKR_B			();			 
	virtual void		setKR_B			(double val);		 
	virtual bool		getSimulated		();			 
	virtual void		setSimulated		(bool val);		 
	 
	/*! 
	 * \brief Get the number of scans store in this volume 
	 *  
	 * \throws OdimH5Exception	Throwed if an error occurs 
	 */ 
	virtual int		getScanCount		(); 
	/*! 
	 * \brief Create a new scan in this volume 
	 *  
	 * \throws OdimH5Exception	Throwed if an error occurs 
	 * \remarks			User is responsible for deleting the returned object  
	 */ 
	virtual PolarScan*	createScan		();  
	/*! 
	 * \brief Get a pointer to a scan of the volume 
	 *  
	 * \param index			The scan number (from 0 to n-1) 
	 * \throws OdimH5Exception	Throwed if an error occurs 
	 * \remarks			User is responsible for deleting the returned object  
	 */ 
	virtual PolarScan*	getScan			(int index); 	 
	/*! 
	 * \brief Remove a scan from the volume 
	 *  
	 * \param index			The scan number (from 0 to n-1) 
	 * \throws OdimH5Exception	Throwed if an error occurs 
	 * \remarks			User is responsible for deleting the returned object  
	 */ 
	virtual void		removeScan		(int index);	 
	/*! 
	 * \brief Get the pointers to all the scans in the volume 
	 *  
	 * \throws OdimH5Exception	Throwed if an error occurs 
	 * \remarks			User is responsible for deleting the returned objects 
	 */ 
	virtual std::vector<PolarScan*> getScans	(); 
	/*! 
	 * \brief Get the pointers to all the scans at the elevation angle indicated +/- a given gap  
	 *  
	 * \param elevation		The base elevation angle  
	 * \param gap			The allowed gap between the scan angle and the base angle 
	 * \throws OdimH5Exception	Throwed if an error occurs 
	 * \remarks			User is responsible for deleting the returned objects 
	 */ 
	virtual std::vector<PolarScan*> getScans	(double elevation, double gap = 0); 
	/*! 
	 * \brief Get the pointers to all the scans with an elevation angle between the given limits 
	 *  
	 * \param minElevation		The lowest allowed angle 
	 * \param maxElevation		The highest allowed angle 
	 * \throws OdimH5Exception	Throwed if an error occurs 
	 * \remarks			User is responsible for deleting the returned objects 
	 */ 
	virtual std::vector<PolarScan*> getScansBetween	(double minElevation, double maxElevation); 
	/*! 
	 * \brief Get the pointers to all the scans that contains indicated quantity  
	 *  
	 * \param quantity		The quanty name 
	 * \throws OdimH5Exception	Throwed if an error occurs 
	 * \remarks			User is responsible for deleting the returned object  
	 */ 
	virtual std::vector<PolarScan*> getScans	(const char* quantity); 
	virtual std::vector<PolarScan*> getScans	(const std::string& quantity); 
	/*! 
	 * \brief Get the elevation angle for each scan in the volume 
	 *  
	 * \returns A vector with the elevation angles 
	 * \throws OdimH5Exception	Throwed if an error occurs 
	 * \remarks			User is responsible for deleting the returned objects 
	 */ 
	virtual std::vector<double> getScanAngles	(); 
	/*! 
	 * \brief Get the elevation angles for all the scans in the volumes without duplicates 
	 *  
	 * \returns	 A vector with the elevation angles 
	 * \throws OdimH5Exception	Throwed if an error occurs 
	 */ 
	virtual std::vector<double> getElevationAngles	(); 
	/*! 
	 * \brief Get the set of radar quantities stored in the scans 
	 *  
	 * \returns	A STL set containing quantity names 
	 * \throws OdimH5Exception	Throwed if an error occurs 
	 */ 
	virtual std::set<std::string>	getStoredQuantities(); 
 
protected: 
	/* uses cannot directly create OdimH5 objects, only factories provide functions to do it */ 
	friend class OdimFactory; 
	PolarVolume(H5::H5File* file);  
 
	virtual void		setMandatoryInformations	(); 
	virtual void		checkMandatoryInformations	(); 
 
}; 
 
/*===========================================================================*/ 
/* POLAR VOLUME SCAN */ 
/*===========================================================================*/ 
 
/*!  
 * \brief OdimH5 v2.1 Polar Volume SCAN 
 *  
 * This class represents an SCAN a OdimH5 PVOL object. \n 
 * Polar SCAN specific attributes can be manipulated using specific methods. \n 
 * Generic data manipulations can be done using methods provided by the OdimObject interface. \n 
 * \see PolarScanData 
 */ 
class RADAR_API PolarScan : public OdimDataset, public WHATDatasetMetadata, public WHEREScanMetadata, public HOWPolarMetadata 
{ 
public: 
	virtual ~PolarScan(); 
 
	virtual void		setMandatoryInformations(); 
 
	virtual std::string		getObject		();				 
	virtual void			setObject		(const std::string& val); 	 
	virtual std::string		getVersion		(); 				 
	virtual void			setVersion		(const std::string& val);	 
	virtual time_t			getDateTime		();				 
	virtual void			setDateTime		(const time_t val);		 
	virtual SourceInfo		getSource		();				 
	virtual void			setSource		(const SourceInfo& val);	 
 
	virtual std::string		getProduct		();				 
	virtual void			setProduct		(const std::string& val);	 
	virtual double			getProdPar		();				 
	virtual VILHeights		getProdParVIL		();				 
	virtual void			setProdPar		(double val); 			 
	virtual void			setProdPar		(const VILHeights& val); 
	virtual std::string		getQuantity		();				 
	virtual void			setQuantity		(const std::string& val);	 
	virtual time_t			getStartDateTime	();				 
	virtual void			setStartDateTime	(time_t val);			 
	virtual time_t			getEndDateTime		();				 
	virtual void			setEndDateTime		(time_t val);			 
	virtual double			getGain			(); 				 
	virtual void			setGain			(double val);			 
	virtual double			getOffset		();				 
	virtual void			setOffset		(double val); 			 
	virtual double			getNodata		();				 
	virtual void			setNodata		(double val); 			 
	virtual double			getUndetect		();				 
	virtual void			setUndetect		(double val); 			 
 
	virtual double			getLongitude		(); 
	virtual void			setLongitude		(double val); 
	virtual double			getLatitude		(); 
	virtual void			setLatitude		(double val); 
	virtual double			getAltitude		(); 
	virtual void			setAltitude		(double val); 
 
	virtual double			getEAngle		(); 
	virtual void			setEAngle		(double val); 
	virtual int			getNumBins		(); 
	virtual void			setNumBins		(int val); 
	virtual double			getRangeStart		(); 
	virtual void			setRangeStart		(double val); 
	virtual double			getRangeScale		(); 
	virtual void			setRangeScale		(double val); 
	virtual int			getNumRays		(); 
	virtual void			setNumRays		(int val); 
	virtual int			getA1Gate		(); 
	virtual void			setA1Gate		(int val); 
 
	virtual std::string		getTaskOrProdGen	(); 				 
	virtual void			setTaskOrProdGen	(const std::string& val);	 
	virtual time_t			getStartEpochs		();				 
	virtual void			setStartEpochs		(time_t val);			 
	virtual time_t			getEndEpochs		();				 
	virtual void			setEndEpochs		(time_t val);		 
	virtual std::string		getSystem		();				 
	virtual void			setSystem		(const std::string& val);	 
	virtual std::string		getSoftware		();				 
	virtual void			setSoftware		(const std::string& val);	 
	virtual std::string		getSoftwareVer		();				 
	virtual void			setSoftwareVer		(const std::string& val);	 
	virtual double			getZR_A			();				 
	virtual void			setZR_A			(double val);			 
	virtual double			getZR_B			();				 
	virtual void			setZR_B			(double val);			 
	virtual double			getKR_A			();				 
	virtual void			setKR_A			(double val);	 
	virtual double			getKR_B			();		 
	virtual void			setKR_B			(double val);	 
	virtual bool			getSimulated		();		 
	virtual void			setSimulated		(bool val);	 
 
	virtual double			getBeamWidth		();		 
	virtual double			getBeamWidth		(double defaultValue);		 
	virtual void			setBeamWidth		(double val);	 
	virtual double			getWaveLength		();		 
	virtual double			getWaveLength		(double defaultValue);		 
	virtual void			setWaveLength		(double val);	 
	virtual double			getRPM			();		 
	virtual double			getRPM			(double defaultValue);		 
	virtual void			setRPM			(double val);	 
	virtual double			getPulseWidth		();		 
	virtual double			getPulseWidth		(double defaultValue);		 
	virtual void			setPulseWidth		(double val);	 
	virtual double			getRXBandWidth		();
	virtual double			getRXBandWidth		(double defaultValue);
	virtual void			setRXBandWidth		(double val);
	virtual int			getLowPRF		();			 
	virtual int			getLowPRF		(int defaultValue);			 
	virtual void			setLowPRF		(int val);		 
	virtual int			getHighPRF		();			 
	virtual int			getHighPRF		(int defaultValue);			 
	virtual void			setHighPRF		(int val);		 
	virtual double			getTXLoss		()		     ;
	virtual double			getTXLoss		(double defaultValue);
	virtual void			setTXLoss		(double val)	     ;
	virtual double			getRXLoss		()		     ;
	virtual double			getRXLoss		(double defaultValue);
	virtual void			setRXLoss		(double val)	     ;
	virtual double			getRadomeLoss		()		     ;
	virtual double			getRadomeLoss		(double defaultValue);
	virtual void			setRadomeLoss		(double val)	     ;
	virtual double			getAntGain		()		     ;
	virtual double			getAntGain		(double defaultValue);
	virtual void			setAntGain		(double val)	     ;
	virtual double			getBeamWH		()		     ;
	virtual double			getBeamWH		(double defaultValue);
	virtual void			setBeamWH		(double val)	     ;
	virtual double			getBeamWV		()		     ;
	virtual double			getBeamWV		(double defaultValue);
	virtual void			setBeamWV		(double val)	     ;
	virtual double			getGasAttn		()		     ;
	virtual double			getGasAttn		(double defaultValue);
	virtual void			setGasAttn		(double val)	     ;
	virtual double			getRadConstH		()		     ;
	virtual double			getRadConstH		(double defaultValue);
	virtual void			setRadConstH		(double val)	     ;
	virtual double			getRadConstV		()		     ;
	virtual double			getRadConstV		(double defaultValue);
	virtual void			setRadConstV		(double val)	     ;
	virtual double			getNomTXPower		()		     ;
	virtual double			getNomTXPower		(double defaultValue);
	virtual void			setNomTXPower		(double val)	     ;
	virtual std::vector<double>	getTXPower		()		     ;
	virtual std::vector<double>	getTXPower		(double defaultValue);
	virtual void			setTXPower		(double val)	     ;
	virtual double			getNI			()		     ;
	virtual double			getNI			(double defaultValue);
	virtual void			setNI			(double val)	     ;
	virtual double			getVSamples		()		     ;
	virtual double			getVSamples		(double defaultValue);
	virtual void			setVSamples		(double val)	;
 
	virtual std::string		getAzimuthMethod	();			 
	virtual void			setAzimuthMethod	(const std::string& val); 
	virtual std::string		getBinMethod		();			 
	virtual void			setBinMethod		(const std::string& val); 
//	virtual std::vector<AZAngles>	getAzimuthAngles	();				 
//	virtual void			setAzimuthAngles	(const std::vector<AZAngles>& val, int precision = 10); 
	virtual std::vector<double>	getElevationAngles	();				 
	virtual void			setElevationAngles	(const std::vector<double>& val); 
	virtual std::vector<double>	getStartAzimuthAngles	();				 
	virtual void			setStartAzimuthAngles	(const std::vector<double>& val); 
	virtual std::vector<double>	getStopAzimuthAngles	();				 
	virtual void			setStopAzimuthAngles	(const std::vector<double>& val); 
	virtual std::vector<double>	getStartAzimuthTimes	();				 
	virtual void			setStartAzimuthTimes	(const std::vector<double>& val); 
	virtual std::vector<double>	getStopAzimuthTimes	();				 
	virtual void			setStopAzimuthTimes	(const std::vector<double>& val); 
//	virtual std::vector<AZTimes>	getAzimuthTimes		();				 
//	virtual void			setAzimuthTimes		(const std::vector<AZTimes>& val); 
 
	virtual double			getPointAccEl		();			 
	virtual void			setPointAccEl		(double val);		 
	virtual double			getPointAccAZ		();			 
	virtual void			setPointAccAZ		(double val);		 
	virtual bool			getMalfunc		();			 
	virtual void			setMalfunc		(bool val);	 
	virtual std::string		getRadarMsg		();			 
	virtual void			setRadarMsg		(const std::string& val); 
	virtual double			getRadarHorizon		();			 
	virtual void			setRadarHorizon		(double val);		 
//	virtual double			getMDS			();			 
//	virtual void			setMDS			(double val);		 
	virtual double			getNEZ			();			 
	virtual void			setNEZ			(double val);		 
	virtual double			getOUR			();			 
	virtual void			setOUR			(double val);		 
	virtual std::vector<std::string> getDClutter		();
	virtual void			setDClutter		(const std::vector<std::string>& value);
	virtual std::string		getComment		();			 
	virtual void			setComment		(const std::string& val); 
	virtual double			getSQI			();			 
	virtual void			setSQI			(double val);		 
	virtual double			getCSR			();			 
	virtual void			setCSR			(double val);		 
	virtual double			getLOG			();			 
	virtual void			setLOG			(double val);		 
	virtual bool			getVPRCorr		();			 
	virtual void			setVPRCorr		(bool val);		 
	virtual double			getFreeze		();			 
	virtual void			setFreeze		(double val);		 
	virtual double			getMin			();			 
	virtual void			setMin			(double val);		 
	virtual double			getMax			();			 
	virtual void			setMax			(double val);		 
	virtual double			getStep			();			 
	virtual void			setStep			(double val);		 
	virtual int			getLevels		();			 
	virtual void			setLevels		(int val);		 
	virtual double			getPeakPwr		();			 
	virtual void			setPeakPwr		(double val);		 
	virtual double			getAvgPwr		();			 
	virtual void			setAvgPwr		(double val);		 
	virtual double			getDynRange		();			 
	virtual void			setDynRange		(double val);		 
	virtual double			getRAC			();			 
	virtual void			setRAC			(double val);		 
	virtual bool			getBBC			();			 
	virtual void			setBBC			(bool val);		 
	virtual double			getPAC			();			 
	virtual void			setPAC			(double val);		 
	virtual double			getS2N			();			 
	virtual void			setS2N			(double val);		 
	virtual std::string		getPolarization		();			 
	virtual void			setPolarization		(const std::string& val); 
 
	/*! 
	 * \brief Get number of quantities stored in the scan 
	 *  
	 * \returns			The number of quantities 
	 * \throws OdimH5Exception	Throwed if an error occurs 
	 */ 
	virtual int		getQuantityDataCount();	 

	/*! 
	 * \brief Create a new group for a quantity in the scan 
	 *  
	 * \param 			The quantity type to be created
	 * \returns			The number of quantities 
	 * \throws OdimH5Exception	Throwed if an error occurs 
	 */ 
	virtual PolarScanData*	createQuantityData	(const char* name);  
	virtual PolarScanData*	createQuantityData	(const std::string& name);  
	/*! 
	 * \brief Get the data associated to a quantity 
	 *  
	 * Get the data associated to a quantity using its index. \n 
	 * \returns			The object associated to the quantity 
	 * \throws OdimH5Exception	Throwed if an error occurs 
	 * \remarks			User is responsible for deleting the returned object  
	 */ 
	virtual PolarScanData*	getQuantityData		(int index);  
	/*! 
	 * \brief Get the data associated to a quantity 
	 *  
	 * Get the data associated to a quantity using its OdimH5 name. \n 
	 * \returns			The object associated to the quantity 
	 * \throws OdimH5Exception	Throwed if an error occurs 
	 * \remarks			User is responsible for deleting the returned object  
	 */ 
	virtual PolarScanData*	getQuantityData		(const char* name); 
	virtual PolarScanData*	getQuantityData		(const std::string& name);  
	/*! 
	 * \brief Delete the data associated to a quantity 
	 *  
	 * Delete the data associated to a quantity using its OdimH5 name. \n 
	 * \throws OdimH5Exception	Throwed if an error occurs 
	 */ 
	virtual void		removeQuantityData	(const char* name);  
	virtual void		removeQuantityData	(const std::string& name);  
	/*! 
	 * \brief Check if the scan contains the data associated to a quantity 
	 *  
	 * Check if the scan contains the data associated to a quantity using its OdimH5 name. \n 
	 * \param name			The quantity name to find 
	 * \throws OdimH5Exception	Throwed if an error occurs 
	 */ 
	virtual bool		hasQuantityData		(const char* name); 
	virtual bool		hasQuantityData		(const std::string& name); 
	/*! 
	 * \brief Return the index of the 'data' group containing the given quantity 
	 *  
	 * \param name			The quantity name to find 
	 * \return A non negative value if the given quantity is found, -1 otherwise 
	 * \throws OdimH5Exception	Throwed if an error occurs 
	 */ 
	virtual int		getQuantityDataIndex	(const char* name); 
	virtual int		getQuantityDataIndex	(const std::string& name); 
	/*! 
	 * \brief Get the direction of the scan  
	 *  
	 * Get the direction of the scan. The result is > 0 if the scan is clockwise, < 0 if the scan is counter-clockwise. \n 
	 * This value is calculated using the RPM attribute or the AZTimes attribute. \n 
	 * If it is not possibile to calculate the direction of the scan, 0 is returned. \n 
	 * \throws OdimH5Exception	Throwed if an error occurs 
	 */ 
	virtual int		getDirection(); 
	/*! 
	 * \brief Get the name of all quantities present in this scan 
	 *  
	 * \return A std::set containing the name of each quantity present in the scan 
	 * \throws OdimH5Exception	Throwed if an error occurs 
	 */ 
	std::set<std::string>	getStoredQuantities	(); 
	/*! 
	 * \brief Calculate the original ray index of a scan 
	 *  
	 * Scan's rays are always ordered clockwise, with the first ray pointing to the geographic north. \n 
	 * Starting from a index, this function can calculate the index of rays in temporal order. \n 
	 * \param index			the index of a ray in the scan 
	 * \param originalDirection	the direction of the scan (1 or -1) 
	 * \param numrays		the total number of rays in the scan 
	 * \param a1gate		the value of the a1gate attribute 
	 * \throws OdimH5Exception	Throwed if an error occurs 
	 */ 
	static inline int originaRayIndex(int index, int originalDirection, int numrays, int a1gate) 
	{ 
		if (originalDirection>0) 
		{ 
			return (index + a1gate) % numrays; 
		} 
		else 
		{ 
			return ((numrays + a1gate) - index) % numrays; 
		} 
	} 
 
private: 
	PolarVolume*		volume; 
 
	/* uses cannot directly create OdimH5 objects, only factories provide functions to do it */ 
	friend class PolarVolume; 
	PolarScan(PolarVolume* volume, H5::Group* group); 
}; 
 
/*===========================================================================*/ 
/* POLAR SCAN DATA */ 
/*===========================================================================*/ 
 
/*!  
 * \brief OdimH5 v2.1 SCAN quantity data 
 *  
 * This class represents OdimH5 data group associated with a OdimH5 quantity 
 * Generic data manipulations can be done using methods provided by the OdimObject interface 
 * \see PolarScanData 
 */ 
class RADAR_API PolarScanData: public OdimData, public WHATDatasetMetadata 
{ 
public: 
	virtual ~PolarScanData(); 
 
	virtual std::string		getObject	(); 
	virtual void			setObject	(const std::string& val); 
	virtual std::string		getVersion	(); 
	virtual void			setVersion	(const std::string& val); 
	virtual time_t			getDateTime	(); 
	virtual void			setDateTime	(const time_t val); 
	virtual SourceInfo		getSource	(); 
	virtual void			setSource	(const SourceInfo& val); 
 
	virtual std::string		getProduct	(); 
	virtual void			setProduct	(const std::string& val); 
	virtual double			getProdPar	(); 
	virtual VILHeights		getProdParVIL	(); 
	virtual void			setProdPar	(double val); 
	virtual void			setProdPar	(const VILHeights& val); 
	virtual std::string		getQuantity	(); 
	virtual void			setQuantity	(const std::string& val); 
	virtual time_t			getStartDateTime(); 
	virtual void			setStartDateTime(time_t val); 
	virtual time_t			getEndDateTime	(); 
	virtual void			setEndDateTime	(time_t val); 
	virtual double			getGain		(); 
	virtual void			setGain		(double val); 
	virtual double			getOffset	(); 
	virtual void			setOffset	(double val); 
	virtual double			getNodata	(); 
	virtual void			setNodata	(double val); 
	virtual double			getUndetect	(); 
	virtual void			setUndetect	(double val); 
 
	/*! 
	 * \brief Get the number of rays in the matrix 
	 *  
	 * \throws OdimH5Exception	Throwed if an error occurs 
	 */ 
	virtual int		getNumRays(); 
	/*! 
	 * \brief Get the number of bins in each ray of the matrix 
	 *  
	 * \throws OdimH5Exception	Throwed if an error occurs 
	 */ 
	virtual int		getNumBins();  
	/*! 
	 * \brief Get the type of each element in the matrix 
	 *  
	 * \throws OdimH5Exception	Throwed if an error occurs 
	 */ 
	H5::AtomType		getBinType();	 
	/*! 
	 * \brief Read the matrix data translating the values  
	 *  
	 * Read the matrix data translating the values using 'gain' and 'offset' attributes. \n 
	 * The result is store int the given 32 floating point values matrix. \n 
	 * \throws OdimH5Exception	Throwed if an error occurs 
	 */ 
	virtual void		readTranslatedData(RayMatrix<float>& matrix); 
	/*! 
	 * \brief Read the matrix data translating the values  
	 *  
	 * Read the matrix data translating the values using 'gain' and 'offset' attributes 
	 * The result is store int the given 32 floating point values matrix  
	 * \throws OdimH5Exception	Throwed if an error occurs 
	 */ 
	virtual void		readTranslatedData(RayMatrix<double>& matrix); 
	/*! 
	 * \brief Write the given matrix of data into the quantity matrix 
	 *  
	 * Write the given matrix of data into the HDF5 dataset associated to this quantity. \n 
	 * Value will be written according to the given HDF5 type and translated useing the given gain and offset. \n 
	 * \param matrix		the values to rite 
	 * \param gain			the gain value used to translate values 
	 * \param offset		the offset value used to translate values 
	 * \param type			the type to use fo the HDF5 dataset elements 
	 * \throws OdimH5Exception	Throwed if an error occurs 
	 */ 
	virtual void		writeAndTranslate(RayMatrix<float>& matrix, float offset, float gain, H5::DataType type); 
	/*! 
	 * \brief Write the given matrix of data into the quantity matrix 
	 *  
	 * Write the given matrix of data into the HDF5 dataset associated to this quantity. \n 
	 * Values will be written according to the given HDF5 type and translated useing the given gain and offset. \n 
	 * \param matrix		the values to rite 
	 * \param gain			the gain value used to translate values 
	 * \param offset		the offset value used to translate values 
	 * \param type			the type to use fo the HDF5 dataset elements 
	 * \throws OdimH5Exception	Throwed if an error occurs 
	 */ 
	virtual void		writeAndTranslate(RayMatrix<double>& matrix, double offset, double gain, H5::DataType type); 
 
private:  
	PolarScan*	scan; 
	 
	/* uses cannot directly create OdimH5 objects, only factories provide functions to do it */ 
	friend class PolarScan; 
	PolarScanData(PolarScan* scan, H5::Group* group); 
}; 
 


/*===========================================================================*/
/* 2D OBJECT  */
/*===========================================================================*/

/*! 
 * \brief OdimH5 v2.1 Object_2D
 * 
 * \n This class represents an OdimH5 IMAGE composed of product objects. \n
 * \n Image specific attributes can be manipulated using specific methods. \n
 * 
 * \n Generic data manipulations can be done using methods provided by the OdimObject interface. \n
 * 
 * \see Product_2D
 */
class RADAR_API Object_2D : public OdimObject, public HOWRootMetadata
{
public:
	virtual ~Object_2D() = 0;

        //virtual void	setMandatoryInformations();
	//void  	checkMandatoryInformations();

	virtual std::string	getTaskOrProdGen	();			
	virtual void		setTaskOrProdGen	(const std::string& val);
	virtual time_t		getStartEpochs		();			
	virtual void		setStartEpochs		(time_t val);		
	virtual time_t		getEndEpochs		();			
	virtual void		setEndEpochs		(time_t val);
	virtual std::string	getSystem		();
	virtual void		setSystem		(const std::string& val);
	virtual std::string	getSoftware		();			
	virtual void		setSoftware		(const std::string& val);
	virtual std::string	getSoftwareVer		();			
	virtual void		setSoftwareVer		(const std::string& val);
	virtual double		getZR_A			();			
	virtual void		setZR_A			(double val);		
	virtual double		getZR_B			();			
	virtual void		setZR_B			(double val);		
	virtual double		getKR_A			();			
	virtual void		setKR_A			(double val);		
	virtual double		getKR_B			();			
	virtual void		setKR_B			(double val);		
	virtual bool		getSimulated		();			
	virtual void		setSimulated		(bool val);		
	
	/*!
	 * \brief Get the number of products dataset store in this volume
	 * 
	 * \throws OdimH5Exception	Throwed if an error occurs
	 */
	virtual int		getProductCount		();
	/*!
	 * \brief Create a new generic 2D product in this volume
	 * 
	 * \param type 			The type of the product to be created
	 * \throws OdimH5Exception	Throwed if an error occurs
	 * \remarks			User is responsible for deleting the returned object 
	 */
	virtual Product_2D*	createProduct2D		(const char* type); 
	virtual Product_2D*	createProduct2D		(const std::string & type); 
	/*!
	 * \brief Create a new PPI product in this volume
	 * 
	 * \throws OdimH5Exception	Throwed if an error occurs
	 * \remarks			User is responsible for deleting the returned object 
	 */
	virtual Product_PPI*	createProductPPI		();
	/*!
	 * \brief Create a new CAPPI product in this volume
	 * 
	 * \throws OdimH5Exception	Throwed if an error occurs
	 * \remarks			User is responsible for deleting the returned object 
	 */
	virtual Product_CAPPI*	createProductCAPPI		();
	/*!
	 * \brief Create a new PCAPPI product in this volume
	 * 
	 * \throws OdimH5Exception	Throwed if an error occurs
	 * \remarks			User is responsible for deleting the returned object 
	 */
	virtual Product_PCAPPI*	createProductPCAPPI		();
	/*!
	 * \brief Create a new ETOP product in this volume
	 * 
	 * \throws OdimH5Exception	Throwed if an error occurs
	 * \remarks			User is responsible for deleting the returned object 
	 */
	virtual Product_ETOP*	createProductETOP		();
	/*!
	 * \brief Create a new MAX product in this volume
	 * 
	 * \throws OdimH5Exception	Throwed if an error occurs
	 * \remarks			User is responsible for deleting the returned object 
	 */
	virtual Product_MAX*	createProductMAX		();
	/*!
	 * \brief Create a new RR product in this volume
	 * 
	 * \throws OdimH5Exception	Throwed if an error occurs
	 * \remarks			User is responsible for deleting the returned object 
	 */
	virtual Product_RR*	createProductRR		();
	/*!
	 * \brief Create a new VIL product in this volume
	 * 
	 * \throws OdimH5Exception	Throwed if an error occurs
	 * \remarks			User is responsible for deleting the returned object 
	 */
	virtual Product_VIL*	createProductVIL		();
	/*!
	 * \brief Create a new LBM product in this volume
	 * 
	 * \throws OdimH5Exception	Throwed if an error occurs
	 * \remarks			User is responsible for deleting the returned object 
	 */
	virtual Product_LBM*	createProductLBM		();
	/*!
	 * \brief Create a new COMP product in this volume
	 * 
	 * \throws OdimH5Exception	Throwed if an error occurs
	 * \remarks			User is responsible for deleting the returned object 
	 */
	virtual Product_COMP*	createProductCOMP		();
	/*!
	 * \brief Create a new XSEC product in this volume
	 * 
	 * \throws OdimH5Exception	Throwed if an error occurs
	 * \remarks			User is responsible for deleting the returned object 
	 */
	virtual Product_XSEC*	createProductXSEC		();
	/*!
	 * \brief Create a new RHI product in this volume
	 * 
	 * \throws OdimH5Exception	Throwed if an error occurs
	 * \remarks			User is responsible for deleting the returned object 
	 */
	virtual Product_RHI*	createProductRHI		();
	/*!
	 * \brief Create a new VSP product in this volume
	 * 
	 * \throws OdimH5Exception	Throwed if an error occurs
	 * \remarks			User is responsible for deleting the returned object 
	 */
	virtual Product_VSP*	createProductVSP		();
	/*!
	 * \brief Create a new HSP product in this volume
	 * 
	 * \throws OdimH5Exception	Throwed if an error occurs
	 * \remarks			User is responsible for deleting the returned object 
	 */
	virtual Product_HSP*	createProductHSP		();
	/*!
	 * \brief Create a new 2D-horizontal product in this volume
	 * 
	 * \param type 			The type of the product to be created
	 * \throws OdimH5Exception	Throwed if an error occurs
	 * \remarks			User is responsible for deleting the returned object 
	 */
//	virtual Horizontal_Product_2D*	createHorizontal_Product_2D		(const char*  type); 
//	virtual Horizontal_Product_2D*	createHorizontal_Product_2D		(const std::string&  type); 
	/*!
	 * \brief Create a new 2D-Vertival product in this volume
	 * 
	 * \param type 			The type of the product to be created
	 * \throws OdimH5Exception	Throwed if an error occurs
	 * \remarks			User is responsible for deleting the returned object 
	 */
//	virtual Vertical_Product_2D*	createVertical_Product_2D		(const char*  type); 
//	virtual Vertical_Product_2D*	createVertical_Product_2D		(const std::string&  type); 
	/*!
	 * \brief Get a pointer to a generic 2D product of the volume
	 * 
	 * \param index			The scan number (from 0 to n-1)
	 * \throws OdimH5Exception	Throwed if an error occurs
	 * \remarks			User is responsible for deleting the returned object 
	 */
	virtual Product_2D*	getProduct			(int index); 	
	/*!
	 * \brief Get a pointer to a 2D-Horizonatl product of the volume
	 * 
	 * \param index			The scan number (from 0 to n-1)
	 * \throws OdimH5Exception	Throwed if an error occurs
	 * \remarks			User is responsible for deleting the returned object 
	 */
//
//virtual Horizontal_Product_2D*	getHorizontal_Product_2D			(int index); 	
	/*!
	 * \brief Get a pointer to a 2d-vertical product of the volume
	 * 
	 * \param index			The scan number (from 0 to n-1)
	 * \throws OdimH5Exception	Throwed if an error occurs
	 * \remarks			User is responsible for deleting the returned object 
	 */
//
//virtual Vertical_Product_2D*	getVertical_Product_2D			(int index); 	
	/*!
	 * \brief Remove a product dataset from the volume
	 * 
	 * \param index			The product dataset number (from 0 to n-1)
	 * \throws OdimH5Exception	Throwed if an error occurs
	 * \remarks			User is responsible for deleting the returned object 
	 */
	virtual void		removeProduct		(int index);	

	/*!
 	 * \brief Get the pointers to all the product types in the file
	 * 
	 * \throws OdimH5Exception	Throwed if an error occurs
	 * \remarks			User is responsible for deleting the returned objects
	 */
	virtual std::vector<std::string > getProductsType	();

	/*! 
	 * \brief Get the pointers to all the products in the file  
	 *  
	 * \throws OdimH5Exception	Throwed if an error occurs 
	 * \remarks			User is responsible for deleting the returned object  
	 */ 
	virtual std::vector<Product_2D*> getProducts();
/////---------
////	/*! 
////	 * \brief Get the pointers to all the scans that contains indicated quantity  
////	 *  
////	 * \param quantity		The quanty name 
////	 * \throws OdimH5Exception	Throwed if an error occurs 
////	 * \remarks			User is responsible for deleting the returned object  
////	 */ 
////	virtual std::vector<PolarScan*> getScans	(const char* quantity); 
////	virtual std::vector<PolarScan*> getScans	(const std::string& 
/////---------

protected:
	/* uses cannot directly create OdimH5 objects, only factories provide functions to do it */
//	friend class OdimFactory;
	Object_2D(H5::H5File* file); 

	virtual void		setMandatoryInformations	();
	virtual void		checkMandatoryInformations	();
};


/*===========================================================================*/
/* HORIZONTAL OBJECT  */
/*===========================================================================*/
/*! 
 * \brief OdimH5 v2.1 horizontalObject
 * 
 * \n This class represents an OdimH5 horizontal Object. (i.e IMAGE and COMP Object) \n
 * \n Horizontal object specific attributes can be manipulated using specific methods. \n
 * 
 * \n Generic data manipulations can be done using methods provided by the OdimObject interface. \n
 * 
 * \see Product_2D
 */
class RADAR_API HorizontalObject_2D : public Object_2D, public WHEREImageMetadata
{
public:
	virtual ~HorizontalObject_2D() ;

        virtual void	setMandatoryInformations();
	virtual void  	checkMandatoryInformations();

	virtual std::string		getProjectionArguments	() ;
	virtual void			setProjectionArguments	(const std::string& val) ;

	virtual int			getXSize		()		;
	virtual void			setXSize		(int val)	;
	virtual int			getYSize		()		;
	virtual void			setYSize		(int val)	;
	virtual double			getXScale		()		;
	virtual void			setXScale		(double val)	;
	virtual double			getYScale		()		;
	virtual void			setYScale		(double val)	;

	virtual double			getLL_Longitude		()		;
	virtual void			setLL_Longitude		(double val)	;
	virtual double			getLL_Latitude		()		;
	virtual void			setLL_Latitude		(double val)	;

	virtual double			getUL_Longitude		()		;
	virtual void			setUL_Longitude		(double val)	;
	virtual double			getUL_Latitude		()		;
	virtual void			setUL_Latitude		(double val)	;

	virtual double			getUR_Longitude		()		;
	virtual void			setUR_Longitude		(double val)	;
	virtual double			getUR_Latitude		()		;
	virtual void			setUR_Latitude		(double val)	;

	virtual double			getLR_Longitude		()		;
	virtual void			setLR_Longitude		(double val)	;
	virtual double			getLR_Latitude		()		;
	virtual void			setLR_Latitude		(double val)	;
protected:
	/* uses cannot directly create OdimH5 objects, only factories provide functions to do it */
//	friend class OdimFactory;
	HorizontalObject_2D(H5::H5File* file); 

};
/*===========================================================================*/
/* IMAGE OBJECT  */
/*===========================================================================*/
/*! 
 * \brief OdimH5 v2.1 ImageObject
 * 
 * \n This class represents an OdimH5 IMAGE Object. \n
 * \n IMAGE Object is specification of Horizontal Object. The only difference is the value of Object attribute. \n
 * \n Specific attributes can be manipulated using specific methods. \n
 * 
 * \n Generic data manipulations can be done using methods provided by the OdimObject interface. \n
 * 
 * \see Product_2D
 */
class RADAR_API ImageObject : public HorizontalObject_2D
{
public:
	virtual ~ImageObject() ;

        virtual void	setMandatoryInformations();
	virtual void  	checkMandatoryInformations();

protected:
	/* uses cannot directly create OdimH5 objects, only factories provide functions to do it */
	friend class OdimFactory;
	ImageObject(H5::H5File* file); 
};
/*===========================================================================*/
/* COMP OBJECT  */
/*===========================================================================*/
/*! 
 * \brief OdimH5 v2.1 CompObject
 * 
 * \n This class represents an OdimH5 COMP Object. \n
 * \n COMP Object is specification of Horizontal Object. The only difference is the value of Object attribute. \n
 * \n Specific attributes can be manipulated using specific methods. \n
 * 
 * \n Generic data manipulations can be done using methods provided by the OdimObject interface. \n
 * 
 * \see Product_2D
 */
class RADAR_API CompObject : public HorizontalObject_2D
{
public:
	virtual ~CompObject() ;

        virtual void	setMandatoryInformations();
	virtual void  	checkMandatoryInformations();

protected:
	/* uses cannot directly create OdimH5 objects, only factories provide functions to do it */
	friend class OdimFactory;
	CompObject(H5::H5File* file); 
};

/*===========================================================================*/
/* XSEC OBJECT  */
/*===========================================================================*/
/*! 
 * \brief OdimH5 v2.1 XsecObject
 * 
 * \n This class represents an OdimH5 XSEC Object. \n
 * \n Specific attributes can be manipulated using specific methods. \n
 * 
 * \n Generic data manipulations can be done using methods provided by the OdimObject interface. \n
 * 
 * \see Product_2D
 */
class RADAR_API XsecObject : public Object_2D, public WHEREXSECMetadata, public WHERERhiMetadata, public WHEREPanelMetadata
{
public:
	virtual ~XsecObject();

        virtual void	setMandatoryInformations();
	virtual void  	checkMandatoryInformations();

	virtual int			getXSize		()		;
	virtual void			setXSize		(int val)	;
	virtual int			getYSize		()		;
	virtual void			setYSize		(int val)	;
	virtual double			getXScale		()		;
	virtual void			setXScale		(double val)	;
	virtual double			getYScale		()		;
	virtual void			setYScale		(double val)	;
	virtual double			getMinHeight		()		;
	virtual void			setMinHeight		(double val)	;
	virtual double			getMaxHeight		()		;
	virtual void			setMaxHeight		(double val)	;

        virtual double			getRHILon		();
        virtual void			setRHILon		(double val);
        virtual double			getRHILat		();
        virtual void			setRHILat		(double val);
	virtual double			getAzimuthAngle		();
	virtual void			setAzimuthAngle		(double val);
	virtual std::vector<Angles>	getAngles		();
	virtual void			setAngles		(const std::vector<Angles>& val);
	virtual double			getRange		();
	virtual void			setRange		(double val);

	virtual double			getStartLongitude	() ;
	virtual void			setStartLongitude	(double val);
	virtual double			getStartLatitude	() ;
	virtual void			setStartLatitude	(double val);
	virtual double			getStopLongitude	();
	virtual void			setStopLongitude	(double val);
	virtual double			getStopLatitude		();
	virtual void			setStopLatitude		(double val);

protected:
	/* uses cannot directly create OdimH5 objects, only factories provide functions to do it */
	friend class OdimFactory;
	XsecObject(H5::H5File* file); 

};

/*===========================================================================*/
/* 2D_PRODUCT Dataset  */
/*===========================================================================*/
/*! 
 * \brief OdimH5 v2.1 Product_2D Dataset
 * 
 * This class represents a generic Product_2D interface. \n
 * Product generic attributes can be manipulated using these methods. \n
 *
 * Generic data manipulations can be done using methods provided by the OdimDataset interface. \n
 * \see Horizontal_Product_2D
 * \see Vertical_Product_2D
 */
class RADAR_API Product_2D : public OdimDataset, public WHATDatasetMetadata, public HOWPolarMetadata //, public WHEREImageMetadata, public HOWCartesianImageMetadata
{
public:
	virtual ~Product_2D();

	virtual void		setMandatoryInformations();

 	virtual std::string		getObject		();				
	virtual void			setObject		(const std::string& val); 	
	virtual std::string		getVersion		(); 				
	virtual void			setVersion		(const std::string& val);	
	virtual time_t			getDateTime		();				
	virtual void			setDateTime		(const time_t val);		
	virtual SourceInfo		getSource		();				
	virtual void			setSource		(const SourceInfo& val);	

	virtual std::string		getProduct		();				
	virtual void			setProduct		(const std::string& val);	
	virtual double			getProdPar		();				
	virtual VILHeights		getProdParVIL		();				
	virtual void			setProdPar		(double val); 			
	virtual void			setProdPar		(const VILHeights& val);
	virtual std::string		getQuantity		();				
	virtual void			setQuantity		(const std::string& val);	
	virtual time_t			getStartDateTime	();				
	virtual void			setStartDateTime	(time_t val);			
	virtual time_t			getEndDateTime		();				
	virtual void			setEndDateTime		(time_t val);			
	virtual double			getGain			(); 				
	virtual void			setGain			(double val);			
	virtual double			getOffset		();				
	virtual void			setOffset		(double val); 			
	virtual double			getNodata		();				
	virtual void			setNodata		(double val); 			
	virtual double			getUndetect		();				
	virtual void			setUndetect		(double val); 			

	virtual std::string		getAzimuthMethod	();			 
	virtual void			setAzimuthMethod	(const std::string& val); 
	virtual std::string		getBinMethod		();			 
	virtual void			setBinMethod		(const std::string& val); 
//	virtual std::vector<AZAngles>	getAzimuthAngles	();				 
//	virtual void			setAzimuthAngles	(const std::vector<AZAngles>& val, int precision = 10); 
	virtual std::vector<double>	getElevationAngles	();				 
	virtual void			setElevationAngles	(const std::vector<double>& val); 
	virtual std::vector<double>	getStartAzimuthAngles	();				 
	virtual void			setStartAzimuthAngles	(const std::vector<double>& val); 
	virtual std::vector<double>	getStopAzimuthAngles	();				 
	virtual void			setStopAzimuthAngles	(const std::vector<double>& val); 
	virtual std::vector<double>	getStartAzimuthTimes	();				 
	virtual void			setStartAzimuthTimes	(const std::vector<double>& val); 
	virtual std::vector<double>	getStopAzimuthTimes	();				 
	virtual void			setStopAzimuthTimes	(const std::vector<double>& val); 
//	virtual std::vector<AZTimes>	getAzimuthTimes		();				 
//	virtual void			setAzimuthTimes		(const std::vector<AZTimes>& val); 

	virtual double			getPointAccEl		();			
	virtual void			setPointAccEl		(double val);		
	virtual double			getPointAccAZ		();			
	virtual void			setPointAccAZ		(double val);		
	virtual bool			getMalfunc		();			
	virtual void			setMalfunc		(bool val);	
	virtual std::string		getRadarMsg		();			
	virtual void			setRadarMsg		(const std::string& val);
	virtual double			getRadarHorizon		();			
	virtual void			setRadarHorizon		(double val);		
//	virtual double			getMDS			();			
//	virtual void			setMDS			(double val);		
	virtual double			getNEZ			();			
	virtual void			setNEZ			(double val);		
	virtual double			getOUR			();			
	virtual void			setOUR			(double val);		
	virtual std::vector<std::string> getDClutter		();
	virtual void			setDClutter		(const std::vector<std::string>& value);
	virtual std::string		getComment		();			
	virtual void			setComment		(const std::string& val);
	virtual double			getSQI			();			
	virtual void			setSQI			(double val);		
	virtual double			getCSR			();			
	virtual void			setCSR			(double val);		
	virtual double			getLOG			();			
	virtual void			setLOG			(double val);		
	virtual bool			getVPRCorr		();			
	virtual void			setVPRCorr		(bool val);		
	virtual double			getFreeze		();			
	virtual void			setFreeze		(double val);		
	virtual double			getMin			();			
	virtual void			setMin			(double val);		
	virtual double			getMax			();			
	virtual void			setMax			(double val);		
	virtual double			getStep			();		
	virtual void			setStep			(double val);		
	virtual int			getLevels		();			
	virtual void			setLevels		(int val);		
	virtual double			getPeakPwr		();			
	virtual void			setPeakPwr		(double val);		
	virtual double			getAvgPwr		();			
	virtual void			setAvgPwr		(double val);		
	virtual double			getDynRange		();			
	virtual void			setDynRange		(double val);		
	virtual double			getRAC			();			
	virtual void			setRAC			(double val);		
	virtual bool			getBBC			();			
	virtual void			setBBC			(bool val);		
	virtual double			getPAC			();			
	virtual void			setPAC			(double val);		
	virtual double			getS2N			();			
	virtual void			setS2N			(double val);		
	virtual std::string		getPolarization		();			
	virtual void			setPolarization		(const std::string& val);

	virtual std::string		getTaskOrProdGen	(); 				
	virtual void			setTaskOrProdGen	(const std::string& val);	
	virtual time_t			getStartEpochs		();				
	virtual void			setStartEpochs		(time_t val);			
	virtual time_t			getEndEpochs		();				
	virtual void			setEndEpochs		(time_t val);		
	virtual std::string		getSystem		();				
	virtual void			setSystem		(const std::string& val);	
	virtual std::string		getSoftware		();				
	virtual void			setSoftware		(const std::string& val);	
	virtual std::string		getSoftwareVer		();				
	virtual void			setSoftwareVer		(const std::string& val);	
	virtual double			getZR_A			();				
	virtual void			setZR_A			(double val);			
	virtual double			getZR_B			();				
	virtual void			setZR_B			(double val);			
	virtual double			getKR_A			();				
	virtual void			setKR_A			(double val);	
	virtual double			getKR_B			();		
	virtual void			setKR_B			(double val);	
	virtual bool			getSimulated		();		
	virtual void			setSimulated		(bool val);	

	virtual double			getBeamWidth		();		
	virtual double			getBeamWidth		(double defaultValue);		
	virtual void			setBeamWidth		(double val);	
	virtual double			getWaveLength		();	
	virtual double			getWaveLength		(double defaultValue);		
	virtual void			setWaveLength		(double val);	
	virtual double			getRPM			();		
	virtual double			getRPM			(double defaultValue);		
	virtual void			setRPM			(double val);
	virtual double			getPulseWidth		();		
	virtual double			getPulseWidth		(double defaultValue);		
	virtual void			setPulseWidth		(double val);	
	virtual double			getRXBandWidth		();
	virtual double			getRXBandWidth		(double defaultValue);
	virtual void			setRXBandWidth		(double val);
	virtual int			getLowPRF		();			 
	virtual int			getLowPRF		(int defaultValue);			 
	virtual void			setLowPRF		(int val);		 
	virtual int			getHighPRF		();			 
	virtual int			getHighPRF		(int defaultValue);			 
	virtual void			setHighPRF		(int val);		 
	virtual double			getTXLoss		()		     ;
	virtual double			getTXLoss		(double defaultValue);
	virtual void			setTXLoss		(double val)	     ;
	virtual double			getRXLoss		()		     ;
	virtual double			getRXLoss		(double defaultValue);
	virtual void			setRXLoss		(double val)	     ;
	virtual double			getRadomeLoss		()		     ;
	virtual double			getRadomeLoss		(double defaultValue);
	virtual void			setRadomeLoss		(double val)	     ;
	virtual double			getAntGain		()		     ;
	virtual double			getAntGain		(double defaultValue);
	virtual void			setAntGain		(double val)	     ;
	virtual double			getBeamWH		()		     ;
	virtual double			getBeamWH		(double defaultValue);
	virtual void			setBeamWH		(double val)	     ;
	virtual double			getBeamWV		()		     ;
	virtual double			getBeamWV		(double defaultValue);
	virtual void			setBeamWV		(double val)	     ;
	virtual double			getGasAttn		()		     ;
	virtual double			getGasAttn		(double defaultValue);
	virtual void			setGasAttn		(double val)	     ;
	virtual double			getRadConstH		()		     ;
	virtual double			getRadConstH		(double defaultValue);
	virtual void			setRadConstH		(double val)	     ;
	virtual double			getRadConstV		()		     ;
	virtual double			getRadConstV		(double defaultValue);
	virtual void			setRadConstV		(double val)	     ;
	virtual double			getNomTXPower		()		     ;
	virtual double			getNomTXPower		(double defaultValue);
	virtual void			setNomTXPower		(double val)	     ;
	virtual std::vector<double>	getTXPower		()		     ;
	virtual std::vector<double>	getTXPower		(double defaultValue);
	virtual void			setTXPower		(double val)	     ;
	virtual double			getNI			()		     ;
	virtual double			getNI			(double defaultValue);
	virtual void			setNI			(double val)	     ;
	virtual double			getVSamples		()		     ;
	virtual double			getVSamples		(double defaultValue);
	virtual void			setVSamples		(double val)	;

/*-----

	virtual double			getLongitude		();
	virtual void			setLongitude		(double val);
	virtual double			getLatitude		();
	virtual void			setLatitude		(double val);
	virtual double			getAltitude		();
	virtual void			setAltitude		(double val);


	virtual double			getEAngle		();
	virtual void			setEAngle		(double val);
	virtual int			getNumBins		();
	virtual void			setNumBins		(int val);
	virtual double			getRangeStart		();
	virtual void			setRangeStart		(double val);
	virtual double			getRangeScale		();
	virtual void			setRangeScale		(double val);
	virtual int			getNumRays		();
	virtual void			setNumRays		(int val);
	virtual int			getA1Gate		();
	virtual void			setA1Gate		(int val);

----*/

	/*! 
	 * \brief Create a new group for a quantity in the product 
	 *  
	 * \param 			The quantity type to be created
	 * \returns			The number of quantities 
	 * \throws OdimH5Exception	Throwed if an error occurs 
	 */ 
	virtual Product_2D_Data*	createQuantityData	(const char* name);  
	virtual Product_2D_Data*	createQuantityData	(const std::string& name);  
	/*!
	 * \brief Get number of quantities stored in the scan
	 * 
	 * \returns			The number of quantities
	 * \throws OdimH5Exception	Throwed if an error occurs
	 */
	virtual int		getQuantityDataCount();	
	/*!
	 * \brief Check if the scan contains the data associated to a quantity
	 * 
	 * Check if the scan contains the data associated to a quantity using its OdimH5 name. \n
	 * \param name			The quantity name to find
	 * \throws OdimH5Exception	Throwed if an error occurs
	 */
	virtual bool		hasQuantityData		(const char* name);
	virtual bool		hasQuantityData		(const std::string& name);
	/*!
	 * \brief Return the index of the 'data' group containing the given quantity
	 * 
	 * \param name			The quantity name to find
	 * \return A non negative value if the given quantity is found, -1 otherwise
	 * \throws OdimH5Exception	Throwed if an error occurs
	 */
	virtual int		getQuantityDataIndex	(const char* name);
	virtual int		getQuantityDataIndex	(const std::string& name);
	/*! 
	 * \brief Get the data associated to a quantity 
	 *  
	 * Get the data associated to a quantity using its index. \n 
	 * \returns			The object associated to the quantity 
	 * \throws OdimH5Exception	Throwed if an error occurs 
	 * \remarks			User is responsible for deleting the returned object  
	 */ 
	virtual Product_2D_Data*	getQuantityData		(int index);  
	/*! 
	 * \brief Get the data associated to a quantity 
	 *  
	 * Get the data associated to a quantity using its OdimH5 name. \n 
	 * \returns			The object associated to the quantity 
	 * \throws OdimH5Exception	Throwed if an error occurs 
	 * \remarks			User is responsible for deleting the returned object  
	 */ 
	virtual Product_2D_Data*	getQuantityData		(const char* name); 
	virtual Product_2D_Data*	getQuantityData		(const std::string& name);  
	/*!
	 * \brief Get the name of all quantities present in this scan
	 * 
	 * \return A std::set containing the name of each quantity present in the scan
	 * \throws OdimH5Exception	Throwed if an error occurs
	 */
	std::set<std::string>	getStoredQuantities	();
	/*! 
	 * \brief Delete the data associated to a quantity 
	 *  
	 * Delete the data associated to a quantity using its OdimH5 name. \n 
	 * \throws OdimH5Exception	Throwed if an error occurs 
	 */ 
	virtual void		removeQuantityData	(const char* name);  
	virtual void		removeQuantityData	(const std::string& name);  

protected :
	Object_2D*		object_2d;

	/* uses cannot directly create OdimH5 objects, only factories provide functions to do it */
	friend class Object_2D;
	Product_2D(Object_2D* object_2d, H5::Group* group);

};

/*===========================================================================*/
/* HORIZONTAL 2D_PRODUCT Dataset  */
/*===========================================================================*/

/*! 
 * \brief OdimH5 v2.1 Horizontal Product_2D Dataset
 * 
 * This class represents a 2D-horizontal Product. \n
 * Product generic attributes can be manipulated using these methods. \n
 *
 * Generic data manipulations can be done using methods provided by the OdimDataset interface. \n
 * \see Product_2D_Data
 */

class RADAR_API Horizontal_Product_2D : public Product_2D, public WHEREImageMetadata, public HOWCartesianImageMetadata
{
public:
	virtual ~Horizontal_Product_2D();
public:
//	virtual void		setMandatoryInformations();

	virtual std::string		getProjectionArguments	() ;
	virtual void			setProjectionArguments	(const std::string& val) ;

	virtual int			getXSize		()		;
	virtual void			setXSize		(int val)	;
	virtual int			getYSize		()		;
	virtual void			setYSize		(int val)	;
	virtual double			getXScale		()		;
	virtual void			setXScale		(double val)	;
	virtual double			getYScale		()		;
	virtual void			setYScale		(double val)	;

	virtual double			getLL_Longitude		()		;
	virtual void			setLL_Longitude		(double val)	;
	virtual double			getLL_Latitude		()		;
	virtual void			setLL_Latitude		(double val)	;

	virtual double			getUL_Longitude		()		;
	virtual void			setUL_Longitude		(double val)	;
	virtual double			getUL_Latitude		()		;
	virtual void			setUL_Latitude		(double val)	;

	virtual double			getUR_Longitude		()		;
	virtual void			setUR_Longitude		(double val)	;
	virtual double			getUR_Latitude		()		;
	virtual void			setUR_Latitude		(double val)	;

	virtual double			getLR_Longitude		()		;
	virtual void			setLR_Longitude		(double val)	;
	virtual double			getLR_Latitude		()		;
	virtual void			setLR_Latitude		(double val)	;
/*--- queste devono essere implementate   .-----*/
	virtual std::vector<Angles>	getAngles		() ;
	virtual void			setAngles		(const std::vector<Angles>& val) ;
	virtual std::vector<Arotation>	getArotation		()		;
	virtual void			setArotation		(const std::vector<Arotation>& val);
	virtual std::string		getCAMethod		();
	virtual void			setCAMethod		(const std::string& val) ;
	virtual std::vector<Nodes>      getNodes		()		;
	virtual void			setNodes		(const std::vector<Nodes>& val) ;
	virtual int			getACCnum		()		;
	virtual void			setCCnum		(int val)	;

protected:
//	Product_2D *		prod;

	/* uses cannot directly create OdimH5 objects, only factories provide functions to do it */
	friend class Product_2D;
	Horizontal_Product_2D (Object_2D* object_2d, H5::Group* group);
};

/*===========================================================================*/
/* PPI PRODUCT Dataset  */
/*===========================================================================*/
/*! 
 * \brief OdimH5 v2.1 PPI Product Dataset
 * 
 * This class represents a specilised 2D-Horizonatl Product for PPI. \n
 * Product generic attributes can be manipulated using these methods. \n
 *
 * Generic data manipulations can be done using methods provided by the OdimDataset interface. \n
 * \see Product_2D_Data
 */
class RADAR_API Product_PPI : public Horizontal_Product_2D
{
public:
	virtual ~Product_PPI() ;

        virtual void	setMandatoryInformations();

private:

	/* uses cannot directly create OdimH5 objects, only factories provide functions to do it */
	friend class Horizontal_Product_2D ; 
	friend class Object_2D;
	Product_PPI(Object_2D * object_2d, H5::Group* group);
};
/*===========================================================================*/
/* CAPPI PRODUCT Dataset  */
/*===========================================================================*/
/*! 
 * \brief OdimH5 v2.1 CAPPI Product Dataset
 * 
 * This class represents a specilised 2D-Horizonatl Product for CAPPI. \n
 * Product generic attributes can be manipulated using these methods. \n
 *
 * Generic data manipulations can be done using methods provided by the OdimDataset interface. \n
 * \see Product_2D_Data
 */
class RADAR_API Product_CAPPI : public Horizontal_Product_2D
{
public:
	virtual ~Product_CAPPI() ;

        virtual void	setMandatoryInformations();

private:

	/* uses cannot directly create OdimH5 objects, only factories provide functions to do it */
	friend class Horizontal_Product_2D ; 
	friend class Object_2D;
	Product_CAPPI(Object_2D * object_2d, H5::Group* group);
};
/*===========================================================================*/
/* PCAPPI PRODUCT Dataset  */
/*===========================================================================*/
/*! 
 * \brief OdimH5 v2.1 PCAPPI Product Dataset
 * 
 * This class represents a specilised 2D-Horizonatl Product for PCAPPI. \n
 * Product generic attributes can be manipulated using these methods. \n
 *
 * Generic data manipulations can be done using methods provided by the OdimDataset interface. \n
 * \see Product_2D_Data
 */
class RADAR_API Product_PCAPPI : public Horizontal_Product_2D
{
public:
	virtual ~Product_PCAPPI() ;

        virtual void	setMandatoryInformations();

private:

	/* uses cannot directly create OdimH5 objects, only factories provide functions to do it */
	friend class Horizontal_Product_2D ; 
	friend class Object_2D;
	Product_PCAPPI(Object_2D * object_2d, H5::Group* group);
};
/*===========================================================================*/
/* ETOP PRODUCT Dataset  */
/*===========================================================================*/
/*! 
 * \brief OdimH5 v2.1 ETOP Product Dataset
 * 
 * This class represents a specilised 2D-Horizonatl Product for ETOP. \n
 * Product generic attributes can be manipulated using these methods. \n
 *
 * Generic data manipulations can be done using methods provided by the OdimDataset interface. \n
 * \see Product_2D_Data
 */
class RADAR_API Product_ETOP : public Horizontal_Product_2D
{
public:
	virtual ~Product_ETOP() ;

        virtual void	setMandatoryInformations();

private:

	/* uses cannot directly create OdimH5 objects, only factories provide functions to do it */
	friend class Horizontal_Product_2D ; 
	friend class Object_2D;
	Product_ETOP(Object_2D * object_2d, H5::Group* group);
};
/*===========================================================================*/
/* MAX PRODUCT Dataset  */
/*===========================================================================*/
/*! 
 * \brief OdimH5 v2.1 MAX Product Dataset
 * 
 * This class represents a specilised 2D-Horizonatl Product for MAX. \n
 * Product generic attributes can be manipulated using these methods. \n
 *
 * Generic data manipulations can be done using methods provided by the OdimDataset interface. \n
 * \see Product_2D_Data
 */
class RADAR_API Product_MAX : public Horizontal_Product_2D
{
public:
	virtual ~Product_MAX() ;

        virtual void	setMandatoryInformations();

private:

	/* uses cannot directly create OdimH5 objects, only factories provide functions to do it */
	friend class Horizontal_Product_2D ; 
	friend class Object_2D;
	Product_MAX(Object_2D * object_2d, H5::Group* group);
};

/*===========================================================================*/
/* RR PRODUCT Dataset  */
/*===========================================================================*/
/*! 
 * \brief OdimH5 v2.1 RR Product Dataset
 * 
 * This class represents a specilised 2D-Horizonatl Product for RR. \n
 * Product generic attributes can be manipulated using these methods. \n
 *
 * Generic data manipulations can be done using methods provided by the OdimDataset interface. \n
 * \see Product_2D_Data
 */
class RADAR_API Product_RR : public Horizontal_Product_2D
{
public:
	virtual ~Product_RR() ;

        virtual void	setMandatoryInformations();

private:

	/* uses cannot directly create OdimH5 objects, only factories provide functions to do it */
	friend class Horizontal_Product_2D ; 
	friend class Object_2D;
	Product_RR(Object_2D * object_2d, H5::Group* group);
};
/*===========================================================================*/
/* VIL PRODUCT Dataset  */
/*===========================================================================*/
/*! 
 * \brief OdimH5 v2.1 VIL Product Dataset
 * 
 * This class represents a specilised 2D-Horizonatl Product for VIL. \n
 * Product generic attributes can be manipulated using these methods. \n
 *
 * Generic data manipulations can be done using methods provided by the OdimDataset interface. \n
 * \see Product_2D_Data
 */
class RADAR_API Product_VIL : public Horizontal_Product_2D
{
public:
	virtual ~Product_VIL() ;

        virtual void	setMandatoryInformations();

private:

	/* uses cannot directly create OdimH5 objects, only factories provide functions to do it */
	friend class Horizontal_Product_2D ; 
	friend class Object_2D;
	Product_VIL(Object_2D * object_2d, H5::Group* group);
};
/*===========================================================================*/
/* LBM PRODUCT Dataset  */
/*===========================================================================*/
/*! 
 * \brief OdimH5 v2.1 PPI Product Dataset
 * 
 * This class represents a specilised 2D-Horizonatl Product for LBM. \n
 * Product generic attributes can be manipulated using these methods. \n
 *
 * Generic data manipulations can be done using methods provided by the OdimDataset interface. \n
 * \see Product_2D_Data
 */
class RADAR_API Product_LBM : public Horizontal_Product_2D
{
public:
	virtual ~Product_LBM() ;

        virtual void	setMandatoryInformations();

private:

	/* uses cannot directly create OdimH5 objects, only factories provide functions to do it */
	friend class Horizontal_Product_2D ; 
	friend class Object_2D;
	Product_LBM(Object_2D * object_2d, H5::Group* group);
};

/*===========================================================================*/
/* COMP PRODUCT Dataset  */
/*===========================================================================*/
/*! 
 * \brief OdimH5 v2.1 COMP Product Dataset
 * 
 * This class represents a specilised 2D-Horizonatl Product for COMP. \n
 * Product generic attributes can be manipulated using these methods. \n
 *
 * Generic data manipulations can be done using methods provided by the OdimDataset interface. \n
 * \see Product_2D_Data
 */
class RADAR_API Product_COMP : public Horizontal_Product_2D
{
public:
	virtual ~Product_COMP() ;

        virtual void	setMandatoryInformations();

private:

	/* uses cannot directly create OdimH5 objects, only factories provide functions to do it */
	friend class Horizontal_Product_2D ; 
	friend class Object_2D;
	Product_COMP(Object_2D * object_2d, H5::Group* group);
};

/*===========================================================================*/
/* VERTICAL 2D_PRODUCT Dataset  */
/*===========================================================================*/
/*! 
 * \brief OdimH5 v2.1 Vericat Product_2D Dataset
 * 
 * This class represents a 2D-vertical Product. \n
 * Product generic attributes can be manipulated using these methods. \n
 *
 * Generic data manipulations can be done using methods provided by the OdimDataset interface. \n
 * \see Product_2D_Data
 */
class RADAR_API Vertical_Product_2D : public Product_2D, public WHEREXSECMetadata
{
public:
	virtual ~Vertical_Product_2D();
public:
	//virtual void		setMandatoryInformations();

	virtual int			getXSize		()		;
	virtual void			setXSize		(int val)	;
	virtual int			getYSize		()		;
	virtual void			setYSize		(int val)	;
	virtual double			getXScale		()		;
	virtual void			setXScale		(double val)	;
	virtual double			getYScale		()		;
	virtual void			setYScale		(double val)	;
	virtual double			getMinHeight		()		;
	virtual void			setMinHeight		(double val)	;
	virtual double			getMaxHeight		()		;
	virtual void			setMaxHeight		(double val)	;
	
protected:
	/* uses cannot directly create OdimH5 objects, only factories provide functions to do it */
	friend class Product_2D;
	Vertical_Product_2D(Object_2D* object_2d, H5::Group* group);
};

/*===========================================================================*/
/* XSEC PRODUCT Dataset  */
/*===========================================================================*/
/*! 
 * \brief OdimH5 v2.1 XSEC Product Dataset
 * 
 * This class represents a specilised 2D-Vertical Product for XSEC. \n
 * Product generic attributes can be manipulated using these methods. \n
 *
 * Generic data manipulations can be done using methods provided by the OdimDataset interface. \n
 * \see Product_2D_Data
 */
class RADAR_API Product_XSEC : public Vertical_Product_2D
{
public:
	virtual ~Product_XSEC() ;

        virtual void	setMandatoryInformations();

private:

	/* uses cannot directly create OdimH5 objects, only factories provide functions to do it */
	friend class Vertical_Product_2D ; 
	friend class Object_2D;
	Product_XSEC(Object_2D* object_2d, H5::Group* group);
};

/*===========================================================================*/
/* RHI PRODUCT Dataset  */
/*===========================================================================*/
/*! 
 * \brief OdimH5 v2.1 RHI Product Dataset
 * 
 * This class represents a specilised 2D-Vertical Product for RHI. \n
 * Product generic attributes can be manipulated using these methods. \n
 *
 * Generic data manipulations can be done using methods provided by the OdimDataset interface. \n
 * \see Product_2D_Data
 */
class RADAR_API Product_RHI : public Vertical_Product_2D, public WHERERhiMetadata
{
public:
	virtual ~Product_RHI() ;

        virtual void	setMandatoryInformations();

        virtual double			getRHILon		();
        virtual void			setRHILon		(double val);
        virtual double			getRHILat		();
        virtual void			setRHILat		(double val);
	virtual double			getAzimuthAngle		();
	virtual void			setAzimuthAngle		(double val);
	virtual std::vector<Angles>	getAngles		();
	virtual void			setAngles		(const std::vector<Angles>& val);
	virtual double			getRange		();
	virtual void			setRange		(double val);

private:

	/* uses cannot directly create OdimH5 objects, only factories provide functions to do it */
	friend class Vertical_Product_2D ; 
	friend class Object_2D;
	Product_RHI(Object_2D* object_2d, H5::Group* group);
};

/*===========================================================================*/
/* VSP PRODUCT Dataset  */
/*===========================================================================*/
/*! 
 * \brief OdimH5 v2.1 Panel Product Dataset
 * 
 * This class represents a specilised 2D-Vertical Product for Panel (Vertical and Horizontal Side Panel). \n
 * Product generic attributes can be manipulated using these methods. \n
 *
 * Generic data manipulations can be done using methods provided by the OdimDataset interface. \n
 * \see Product_2D_Data
 */
class RADAR_API Product_Panel : public Vertical_Product_2D , public WHEREPanelMetadata
{
public:
	virtual ~Product_Panel() ;

        virtual void	setMandatoryInformations();
	virtual double			getStartLongitude	() ;
	virtual void			setStartLongitude	(double val);
	virtual double			getStartLatitude	() ;
	virtual void			setStartLatitude	(double val);
	virtual double			getStopLongitude	();
	virtual void			setStopLongitude	(double val);
	virtual double			getStopLatitude		();
	virtual void			setStopLatitude		(double val);

protected:

	/* uses cannot directly create OdimH5 objects, only factories provide functions to do it */
	friend class Vertical_Product_2D ; 
	friend class Product_2D;
	Product_Panel(Object_2D* object_2d, H5::Group* group);
};

/*===========================================================================*/
/* HSP PRODUCT Dataset  */
/*===========================================================================*/
/*! 
 * \brief OdimH5 v2.1 HSP Product Dataset
 * 
 * This class represents a specilised 2D-Vertical Product for HSP (Horizontal Side Panel). \n
 * Product generic attributes can be manipulated using these methods. \n
 *
 * Generic data manipulations can be done using methods provided by the OdimDataset interface. \n
 * \see Product_2D_Data
 */
class RADAR_API Product_HSP : public Product_Panel
{
public:
	virtual ~Product_HSP() ;

        virtual void	setMandatoryInformations();

private:

	/* uses cannot directly create OdimH5 objects, only factories provide functions to do it */
	friend class Product_Panel;
	friend class Object_2D;
	Product_HSP(Object_2D* object_2d, H5::Group* group);
};

/*===========================================================================*/
/* VSP PRODUCT Dataset  */
/*===========================================================================*/
/*! 
 * \brief OdimH5 v2.1 VSP Product Dataset
 * 
 * This class represents a specilised 2D-Vertical Product for VSP (Vertical Side Panel). \n
 * Product generic attributes can be manipulated using these methods. \n
 *
 * Generic data manipulations can be done using methods provided by the OdimDataset interface. \n
 * \see Product_2D_Data
 */
class RADAR_API Product_VSP : public Product_Panel
{
public:
	virtual ~Product_VSP() ;

        virtual void	setMandatoryInformations();

private:

	/* uses cannot directly create OdimH5 objects, only factories provide functions to do it */
	friend class Product_Panel;
	friend class Object_2D;
	Product_VSP(Object_2D* object_2d, H5::Group* group);
};
/*===========================================================================*/ 
/* 2D PRODUCT DATA */ 
/*===========================================================================*/ 
 
/*!  
 * \brief OdimH5 v2.1 2d product quantity data 
 *  
 * This class represents OdimH5 data group associated with a OdimH5 quantity 
 * Generic data manipulations can be done using methods provided by the OdimData interface 
 *  
 */ 
class RADAR_API Product_2D_Data: public OdimData, public WHATDatasetMetadata 
{ 
public: 
	virtual ~Product_2D_Data(); 
 
	virtual std::string		getObject	(); 
	virtual void			setObject	(const std::string& val); 
	virtual std::string		getVersion	(); 
	virtual void			setVersion	(const std::string& val); 
	virtual time_t			getDateTime	(); 
	virtual void			setDateTime	(const time_t val); 
	virtual SourceInfo		getSource	(); 
	virtual void			setSource	(const SourceInfo& val); 
 
	virtual std::string		getProduct	(); 
	virtual void			setProduct	(const std::string& val); 
	virtual double			getProdPar	(); 
	virtual VILHeights		getProdParVIL	(); 
	virtual void			setProdPar	(double val); 
	virtual void			setProdPar	(const VILHeights& val); 
	virtual std::string		getQuantity	(); 
	virtual void			setQuantity	(const std::string& val); 
	virtual time_t			getStartDateTime(); 
	virtual void			setStartDateTime(time_t val); 
	virtual time_t			getEndDateTime	(); 
	virtual void			setEndDateTime	(time_t val); 
	virtual double			getGain		(); 
	virtual void			setGain		(double val); 
	virtual double			getOffset	(); 
	virtual void			setOffset	(double val); 
	virtual double			getNodata	(); 
	virtual void			setNodata	(double val); 
	virtual double			getUndetect	(); 
	virtual void			setUndetect	(double val); 
 
	/*! 
	 * \brief Get the number of x elements of the matrix 
	 *  
	 * \throws OdimH5Exception	Throwed if an error occurs 
	 */ 
	virtual int		getNumXElem(); 
	/*! 
	 * \brief Get the number of y elements of the matrix 
	 *  
	 * \throws OdimH5Exception	Throwed if an error occurs 
	 */ 
	virtual int		getNumYElem();  
	/*! 
	 * \brief Get the type of each element in the matrix 
	 *  
	 * \throws OdimH5Exception	Throwed if an error occurs 
	 */ 
	H5::AtomType		getElemType();	 
	/*! 
	 * \brief Read the matrix data translating the values  
	 *  
	 * Read the matrix data translating the values using 'gain' and 'offset' attributes. \n 
	 * The result is store int the given 32 floating point values matrix. \n 
	 * \throws OdimH5Exception	Throwed if an error occurs 
	 */ 
	virtual void		readTranslatedData(DataMatrix<float>& matrix); 
	/*! 
	 * \brief Read the matrix data translating the values  
	 *  
	 * Read the matrix data translating the values using 'gain' and 'offset' attributes 
	 * The result is store int the given 32 floating point values matrix  
	 * \throws OdimH5Exception	Throwed if an error occurs 
	 */ 
	virtual void		readTranslatedData(DataMatrix<double>& matrix); 
	/*! 
	 * \brief Write the given matrix of data into the quantity matrix 
	 *  
	 * Write the given matrix of data into the HDF5 dataset associated to this quantity. \n 
	 * Value will be written according to the given HDF5 type and translated useing the given gain and offset. \n 
	 * \param matrix		the values to rite 
	 * \param gain			the gain value used to translate values 
	 * \param offset		the offset value used to translate values 
	 * \param type			the type to use fo the HDF5 dataset elements 
	 * \throws OdimH5Exception	Throwed if an error occurs 
	 */ 
	virtual void		writeAndTranslate(DataMatrix<float>& matrix, float offset, float gain, H5::DataType type); 
	/*! 
	 * \brief Write the given matrix of data into the quantity matrix 
	 *  
	 * Write the given matrix of data into the HDF5 dataset associated to this quantity. \n 
	 * Values will be written according to the given HDF5 type and translated useing the given gain and offset. \n 
	 * \param matrix		the values to rite 
	 * \param gain			the gain value used to translate values 
	 * \param offset		the offset value used to translate values 
	 * \param type			the type to use fo the HDF5 dataset elements 
	 * \throws OdimH5Exception	Throwed if an error occurs 
	 */ 
	virtual void		writeAndTranslate(DataMatrix<double>& matrix, double offset, double gain, H5::DataType type); 
 
	/*!
	 * \brief Get number of quality fields stored in the scan
	 * 
	 * \returns			The number of quality fields 
	 * \throws OdimH5Exception	Throwed if an error occurs
	 */
	virtual int		getQualityDataCount();	
	/*! 
	 * \brief Create a new group for quality within the 'data' group 
	 *  
	 * \returns			The number of quantities 
	 * \throws OdimH5Exception	Throwed if an error occurs 
	 */ 
	virtual OdimQuality*	createQualityData	();  
	/*! 
	 * \brief Get the data associated to a quality 
	 *  
	 * Get the data associated to a quality using its index. \n 
	 * \param 			The index in the 'data' group
	 * \returns			The object associated to the quality 
	 * \throws OdimH5Exception	Throwed if an error occurs 
	 * \remarks			User is responsible for deleting the returned object  
	 */ 
	virtual OdimQuality*	getQualityData		(int index);  
	/*! 
	 * \brief Delete the data associated to a quality 
	 *  
	 * Delete the data associated to the quality using its index . \n 
	 * \param 			The index in the 'data' group
	 * \throws OdimH5Exception	Throwed if an error occurs 
	 */ 
	virtual void		removeQualityData	(int index);  

private:  
	Product_2D*	prod; 
	 
	/* uses cannot directly create OdimH5 objects, only factories provide functions to do it */ 
	friend class Horizontal_Product_2D; 
	friend class Product_2D; 
	Product_2D_Data(Product_2D* prod, H5::Group* group); 
}; 
 

/*===========================================================================*/ 
 
} 

#endif


