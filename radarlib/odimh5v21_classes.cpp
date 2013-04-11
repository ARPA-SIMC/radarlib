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

#include <radarlib/odimh5v21_classes.hpp>

#include <iomanip>
#include <ctime>
#include <cstdio>

#include <radarlib/debug.hpp>
#include <radarlib/string.hpp>
#include <radarlib/time.hpp>
#include <radarlib/math.hpp>
#include <radarlib/odimh5v21_const.hpp>
#include <radarlib/odimh5v21_format.hpp>
#include <radarlib/odimh5v21_metadata.hpp>

namespace OdimH5v21
{

/*===========================================================================*/
/* FUNZIONI DI SUPPORTO */
/*===========================================================================*/

static void	setWhatDateTime(MetadataGroup* meta, const time_t val)		
{
	meta->set(ATTRIBUTE_WHAT_DATE, Format::timeToYYYYMMDD(val));
	meta->set(ATTRIBUTE_WHAT_TIME, Format::timeToHHMMSS(val));
}
static time_t	getWhatDateTime	(MetadataGroup* meta)				
{
	std::string	datestr = meta->getStr(ATTRIBUTE_WHAT_DATE);
	std::string	timestr = meta->getStr(ATTRIBUTE_WHAT_TIME);
	time_t		dateval	= Format::YYYYMMDDToTime(datestr);
	time_t		timeval	= Format::HHMMSSToTime(timestr);
	return dateval + timeval;		
}

/*==============================================================*/

static void	setWhatStartDateTime(MetadataGroup* meta, const time_t val)		
{
	meta->set	(ATTRIBUTE_WHAT_STARTDATE, Format::timeToYYYYMMDD(val));
	meta->set	(ATTRIBUTE_WHAT_STARTTIME, Format::timeToHHMMSS(val));
}

static time_t	getWhatStartDateTime(MetadataGroup* meta)				
{
	std::string	datestr = meta->getStr(ATTRIBUTE_WHAT_STARTDATE);
	std::string	timestr = meta->getStr(ATTRIBUTE_WHAT_STARTTIME);
	time_t		dateval	= Format::YYYYMMDDToTime(datestr);
	time_t		timeval	= Format::HHMMSSToTime(timestr);
	return dateval + timeval;		
}

/*==============================================================*/

static void	setWhatEndDateTime(MetadataGroup* meta, const time_t val)		
{
	meta->set	(ATTRIBUTE_WHAT_ENDDATE, Format::timeToYYYYMMDD(val));
	meta->set	(ATTRIBUTE_WHAT_ENDTIME, Format::timeToHHMMSS(val));
}
static time_t	getWhatEndDateTime(MetadataGroup* meta)				
{
	std::string	datestr = meta->getStr(ATTRIBUTE_WHAT_ENDDATE);
	std::string	timestr = meta->getStr(ATTRIBUTE_WHAT_ENDTIME);
	time_t		dateval	= Format::YYYYMMDDToTime(datestr);
	time_t		timeval	= Format::HHMMSSToTime(timestr);
	return dateval + timeval;		
}

static MetadataGroup* getMetadataGroup(H5::Group* parent, const char* name)
{
	H5::Group* h5group = NULL;
	try
	{
		h5group = HDF5Group::ensureGetChild(parent, name);
		return new MetadataGroup(h5group);
	}
	catch (...)
	{
		delete h5group;
		throw;
	}
}

/*===========================================================================*/
/* ODIM OBJECT */
/*===========================================================================*/

OdimObject::OdimObject(H5::H5File* file)
:WHATRootMetadata()
,file(file)
,group(HDF5File::getRoot(file))
,meta_what(NULL)
,meta_where(NULL)
,meta_how(NULL)
{	
}

OdimObject::~OdimObject()
{
	try
	{
		delete meta_what;
		delete meta_where;
		delete meta_how;	
		delete group;	
		delete file;
		/* alla chiusura di un file costringiamo la libreria a fare un po' di pulizia */
		H5::H5Library::garbageCollect();
		
	}
	catch (...)
	{
		/* nei distruttori mai lanciare eccezioni*/
	}
}

void OdimObject::checkMandatoryInformations()
{
	std::string conventions = this->getConventions();
	if (conventions != OdimH5v21::CONVENTIONS_ODIM_H5_V2_1)
		throw OdimH5FormatException("Object conventions " + conventions + " unknown");	
}

void OdimObject::setMandatoryInformations()
{
	/* almeno le convenzioni ce le mettiamo */
	setConventions();
}

std::string OdimObject::getConventions() 
{
	return HDF5Attribute::getStr(group, OdimH5v21::ATTRIBUTE_ROOT_CONVENTIONS);	
}

void OdimObject::setConventions() 
{
	HDF5Attribute::set(group, OdimH5v21::ATTRIBUTE_ROOT_CONVENTIONS, OdimH5v21::CONVENTIONS_ODIM_H5_V2_1);
}

H5::H5File* OdimObject::getFile()
{
	return file;
}

H5::Group* OdimObject::getH5Object() 
{
	return group;
}

MetadataGroup* OdimObject::getWhat() 				
{ 
	if (meta_what==NULL)
		meta_what = getMetadataGroup(group, GROUP_WHAT);
	return meta_what;
}

MetadataGroup*	OdimObject::getWhere() 				
{ 
	if (meta_where==NULL)
		meta_where = getMetadataGroup(group, GROUP_WHERE);
	return meta_where;
}

MetadataGroup* OdimObject::getHow() 				
{ 
	if (meta_how==NULL)
		meta_how = getMetadataGroup(group, GROUP_HOW);	
	return meta_how;
}

bool OdimObject::existWhat() 				
{ 
	return HDF5Group::exists(group,GROUP_WHAT);
}

bool OdimObject::existWhere() 				
{ 
	return HDF5Group::exists(group,GROUP_WHERE);
}

bool OdimObject::existHow() 				
{ 
	return HDF5Group::exists(group,GROUP_HOW);	
}

int OdimObject::getDatasetCount()	
{ 
	return HDF5Group::getChildCount(this->group, GROUP_DATASET);
}

OdimDataset* OdimObject::createDataset()		
{ 
	H5::Group* group = createDatasetGroup();
	try
	{
		return new OdimDataset(group);		
	}
	catch (...)
	{
		delete group;
		throw;
	}
}

OdimDataset* OdimObject::getDataset(int index)	
{ 	
	H5::Group* h5group = getDatasetGroup(index);
	try
	{
		if (h5group)
			return new OdimDataset(h5group);
		return NULL;	
	}
	catch (...)
	{
		delete h5group;
		throw;
	}
}

static void renameChildren(H5::Group* parent, int removedElement, int count, const char* prefix)
{
	char name1[100];
	char name2[100];
	for (int i=removedElement+1; i<count; i++)
	{
		snprintf(name1, 100, "%s%d", prefix, i);
		snprintf(name2, 100, "%s%d", prefix, i+1);
		try
		{	
			parent->move(name2, name1);
		}
		catch (H5::Exception& h5e)
		{
			std::ostringstream ss; ss << "Cannot move group " << name2 << " to group " << name1; 
			throw OdimH5HDF5LibException(ss.str(), h5e);
		}
	}
}

void OdimObject::removeDataset(int index)	
{
	try
	{
		std::string name = GROUP_DATASET + Radar::stringutils::toString(index + 1);
		int childrenCount = getDatasetCount();
		HDF5Group::removeChild(this->group, name.c_str());					
		renameChildren(this->group, index, childrenCount, GROUP_DATASET);
	}
	catch (std::exception& e)
	{
		std::ostringstream ss; ss << "Cannot remove dataset group! " << e.what();
		throw OdimH5Exception(ss.str());			
	}
}

H5::Group* OdimObject::createDatasetGroup()
{
	int		num	= getDatasetCount();
	std::string	name	= GROUP_DATASET + Radar::stringutils::toString(num + 1);
	return new H5::Group( this->group->createGroup(name.c_str()));		
}

H5::Group* OdimObject::getDatasetGroup(int index)
{
	std::string name = GROUP_DATASET + Radar::stringutils::toString(index + 1);
	return new H5::Group( this->group->openGroup(name.c_str()));	
}

std::string	OdimObject::getObject	()				{ return getWhat()->getStr	(ATTRIBUTE_WHAT_OBJECT);	}
void		OdimObject::setObject	(const std::string& val) 	{        getWhat()->set		(ATTRIBUTE_WHAT_OBJECT, val);	}
std::string	OdimObject::getVersion	() 				{ return getWhat()->getStr	(ATTRIBUTE_WHAT_VERSION);	}
void		OdimObject::setVersion	(const std::string& val)	{        getWhat()->set		(ATTRIBUTE_WHAT_VERSION, val);	}
time_t		OdimObject::getDateTime	()				{ return getWhatDateTime(this->getWhat());		}
void		OdimObject::setDateTime	(const time_t val)		{	 setWhatDateTime(this->getWhat(), val);		}
SourceInfo	OdimObject::getSource	() 				{ return SourceInfo(getWhat()->getStr(ATTRIBUTE_WHAT_SOURCE));		}
void		OdimObject::setSource	(const SourceInfo& val)		{        getWhat()->set		(ATTRIBUTE_WHAT_SOURCE, val.toString() );	}

/*===========================================================================*/
/* ODIM DATASET */
/*===========================================================================*/

OdimDataset::OdimDataset(H5::Group* group) 
:group(group)
,meta_what(NULL)
,meta_where(NULL)
,meta_how(NULL)
{
}
OdimDataset::~OdimDataset() 
{ 
	try
	{
		delete meta_what;
		delete meta_where;
		delete meta_how;	
		delete group;
	}
	catch (...)
	{
		/* mai lanciare eccezioni nei distruttori */
	}
} 

H5::Group* OdimDataset::getH5Object() 
{ 
	return group; 
}

bool OdimDataset::existWhat() 				
{ 
	return HDF5Group::exists(group,GROUP_WHAT);
}

bool OdimDataset::existWhere() 				
{ 
	return HDF5Group::exists(group,GROUP_WHERE);
}

bool OdimDataset::existHow() 				
{ 
	return HDF5Group::exists(group,GROUP_HOW);	
}

MetadataGroup* OdimDataset::getWhat() 				
{ 
	if (meta_what==NULL)
		meta_what = getMetadataGroup(group, GROUP_WHAT);
	return meta_what;
}

MetadataGroup*	OdimDataset::getWhere() 				
{ 
	if (meta_where==NULL)
		meta_where = getMetadataGroup(group, GROUP_WHERE);
	return meta_where;
}

MetadataGroup* OdimDataset::getHow() 				
{ 
	if (meta_how==NULL)
		meta_how = getMetadataGroup(group, GROUP_HOW);
	return meta_how;
}

int OdimDataset::getDataCount()	
{ 	
	return HDF5Group::getChildCount(this->group, GROUP_DATA);
}

OdimData* OdimDataset::createData()		
{ 
	H5::Group* group = createDataGroup();
	try 
	{
		return new OdimData(group);		
	} 
	catch (...) 
	{
		delete group;
		throw;
	}
}

OdimData* OdimDataset::getData(int index)	
{ 
	//std::string name = GROUP_DATA + Radar::stringutils::toString(index + 1);
	H5::Group* h5group = getDataGroup(index);
	try
	{
		if (h5group)	
			return new OdimData(h5group);	
		return NULL;
	}
	catch (...) 
	{
		delete h5group;
		throw;
	}
}

void OdimDataset::removeData(int index)	
{
	try
	{
		std::string name = GROUP_DATA + Radar::stringutils::toString(index + 1);
		int childrenCount = getDataCount();
		HDF5Group::removeChild(this->group, name.c_str());					
		renameChildren(this->group, index, childrenCount, GROUP_DATA);
	}
	catch (std::exception& e)
	{
		std::ostringstream ss; ss << "Cannot remove data group! " << e.what();
		throw OdimH5Exception(ss.str());			
	}
}

H5::Group* OdimDataset::createDataGroup()
{
	int		num	= getDataCount();
	std::string	name	= GROUP_DATA + Radar::stringutils::toString(num + 1);
	return new H5::Group( this->group->createGroup(name.c_str()));		
}

H5::Group* OdimDataset::getDataGroup(int index)
{
	std::string name = GROUP_DATA + Radar::stringutils::toString(index + 1);
	return HDF5Group::getChild(this->group, name.c_str());				
}

/*===========================================================================*/
/* ODIM DATA */
/*===========================================================================*/

OdimData::OdimData(H5::Group* group)
:group(group)
,meta_what(NULL)
,meta_where(NULL)
,meta_how(NULL)
{
}

OdimData::~OdimData()
{
	try
	{
		delete meta_what;
		delete meta_where;
		delete meta_how;
		delete group;
	}
	catch (...)
	{
		/* mai lanciare eccezioni nei distruttori */
	}
}

H5::Group* OdimData::getH5Object()
{
	return group;
}

bool OdimData::existWhat() 				
{ 
	return HDF5Group::exists(group,GROUP_WHAT);
}

bool OdimData::existWhere() 				
{ 
	return HDF5Group::exists(group,GROUP_WHERE);
}

bool OdimData::existHow() 				
{ 
	return HDF5Group::exists(group,GROUP_HOW);	
}

MetadataGroup* OdimData::getWhat() 				
{ 
	if (meta_what==NULL)
		meta_what = getMetadataGroup(group, GROUP_WHAT);			
	return meta_what;
}

MetadataGroup* OdimData::getWhere() 				
{ 
	if (meta_where==NULL)
		meta_where = getMetadataGroup(group, GROUP_WHERE);			
	return meta_where;
}

MetadataGroup* OdimData::getHow() 				
{ 
	if (meta_how==NULL)
		meta_how = getMetadataGroup(group, GROUP_HOW);	
	return meta_how;
}

H5::DataSet*	OdimData::getData()
{
	return HDF5Group::getDataset(group, DATASET_DATA);
}

H5::AtomType	OdimData::getDataType()
{
	H5::DataSet* dataset = NULL;
	try
	{
		dataset = getData();
		if (dataset)
		{
			H5::DataType type = dataset->getDataType();
			delete dataset;
			return HDF5AtomType::fromDataType(type);
		}
		else
		{
			return H5::PredType::NATIVE_OPAQUE;
		}
	}
	catch (H5::Exception& h5e)
	{
		delete dataset;		
		throw OdimH5HDF5LibException("Unable get odim data type info from HDF5 dataset", h5e);
	}
	catch (...)
	{
		delete dataset;
		throw;
	}
}

int OdimData::getDataWidth()
{
	int height, width;
	getDataDimension(&height, &width);
	return width;
}

int OdimData::getDataHeight()
{
	int height, width;
	getDataDimension(&height, &width);
	return height;
}

void OdimData::getDataDimension(int* height, int* width)
{
	H5::DataSet* dataset = NULL;
	try
	{
		dataset = getData();
		if (dataset)
		{
			hsize_t sizes[3];
			hsize_t numsizes;
			numsizes = dataset->getSpace().getSimpleExtentDims(sizes);
			if (numsizes != 2)
				throw OdimH5v21::OdimH5FormatException("Dataset is not a matrix");			
			*height = (int)sizes[0];
			*width  = (int)sizes[1];
		}
		else
		{
			*height = 0;
			*width  = 0;
		}
		delete dataset;
	}
	catch (H5::Exception& h5e)
	{
		delete dataset;		
		throw OdimH5HDF5LibException("Unable get odim data infos from HDF5 dataset", h5e);
	}
	catch (...)
	{
		delete dataset;
		throw;
	}
}

void OdimData::writeData(const void* buff, int width, int height, const H5::DataType& elemtype)
{
	H5::DataSet* dataset = NULL;
	try
	{		
		HDF5Group::removeChild(group, DATASET_DATA);

		const int RANK = 2;
		hsize_t fdim[] = { (hsize_t)height, (hsize_t)width }; // dim sizes of ds (on disk)
		H5::DataSpace space(RANK, fdim);

		H5::DSetCreatPropList ds_creatplist;  // create dataset creation prop list
		ds_creatplist.setChunk( 2, fdim );  // then modify it for compression
		ds_creatplist.setDeflate( 6 );

		dataset = new H5::DataSet(group->createDataSet(DATASET_DATA, elemtype, space, ds_creatplist));			
		dataset->write(buff, elemtype);	// mspace1, fspace );
		if ((elemtype == H5::PredType::STD_U8BE) || (elemtype == H5::PredType::STD_U8LE) || (elemtype == H5::PredType::INTEL_U8) || 
		    (elemtype == H5::PredType::ALPHA_U8) || (elemtype == H5::PredType::MIPS_U8)  || (elemtype == H5::PredType::NATIVE_UCHAR) || 
		    (elemtype == H5::PredType::NATIVE_UINT8))
		{
			HDF5Attribute::set(dataset, ATTRIBUTE_CLASS,		CLASS_IMAGE);
			HDF5Attribute::set(dataset, ATTRIBUTE_IMAGE_VERSION,	IMAGE_VERSION_1_2);
		}
		delete dataset;
	}
	catch (H5::Exception& h5e)
	{
		delete dataset;		
		throw OdimH5HDF5LibException("Unable to write odim data into HDF5 dataset", h5e);
	}
	catch (...)
	{
		delete dataset;
		throw;
	}
}
void OdimData::writeData(const char* buff, int width, int height)
{
	writeData(buff, width, height, H5::PredType::NATIVE_INT8);
}
void OdimData::writeData(const unsigned char* buff, int width, int height)
{ 
	writeData(buff, width, height, H5::PredType::NATIVE_UINT8);
}
void OdimData::writeData(const unsigned short* buff, int width, int height)
{
	writeData(buff, width, height, H5::PredType::NATIVE_UINT16);
}
void OdimData::writeData(const float* buff, int width, int height)
{
	writeData(buff, width, height, H5::PredType::NATIVE_FLOAT);
}
void	OdimData::writeData(const DataMatrix<char>& matrix)		
{ 
	writeData(matrix.get(), matrix.getColCount(), matrix.getRowCount());	
}
void	OdimData::writeData(const DataMatrix<unsigned char>& matrix)	
{ 
	writeData(matrix.get(), matrix.getColCount(), matrix.getRowCount());	
}
void	OdimData::writeData(const DataMatrix<unsigned short>& matrix)	
{ 
	writeData(matrix.get(), matrix.getColCount(), matrix.getRowCount());	
}
void	OdimData::writeData(const DataMatrix<float>& matrix)		
{ 
	writeData(matrix.get(), matrix.getColCount(), matrix.getRowCount());	
}

void OdimData::readData(void* buff)
{
	H5::DataSet* dataset = getData();
	if (dataset == NULL) 
		return;			
	try
	{
		//hsize_t sizes[2];
		//hsize_t numsizes;
		//numsizes = dataset->getSpace().getSimpleExtentDims(sizes);
		//DataSpace space(numsizes, sizes);
		//dataset = new H5::DataSet(group->openDataSet(DATASET_DATA));
		dataset->read(buff, dataset->getDataType(), dataset->getSpace());	// mspace1, fspace );
		delete dataset;
	}
	catch (H5::Exception& h5e)
	{
		delete dataset;		
		throw OdimH5HDF5LibException("Unable to read odim data from HDF5 dataset", h5e);
	}
	catch (...)
	{
		delete dataset;
		throw;
	}
}
int OdimData::getQualityCount()	
{ 	
	return HDF5Group::getChildCount(this->group, GROUP_QUALITY);
}

OdimQuality* OdimData::createQuality()		
{ 
	H5::Group* group = createQualityGroup();
	try 
	{
		return new OdimQuality(group);		
	} 
	catch (...) 
	{
		delete group;
		throw;
	}
}

OdimQuality* OdimData::getQuality(int index)	
{ 
	//std::string name = P_DATA + Radar::stringutils::toString(index + 1);
	H5::Group* h5group = getQualityGroup(index);
	try
	{
		if (h5group)	
			return new OdimQuality(h5group);	
		return NULL;
	}
	catch (...) 
	{
		delete h5group;
		throw;
	}
}

void OdimData::removeQuality(int index)	
{
	try
	{
		std::string name = GROUP_QUALITY + Radar::stringutils::toString(index + 1);
		int childrenCount = getQualityCount();
		HDF5Group::removeChild(this->group, name.c_str());					
		renameChildren(this->group, index, childrenCount, GROUP_QUALITY);
	}
	catch (std::exception& e)
	{
		std::ostringstream ss; ss << "Cannot remove quality group! " << e.what();
		throw OdimH5Exception(ss.str());			
	}
}

H5::Group* OdimData::createQualityGroup()
{
	int		num	= getQualityCount();
	std::string	name	= GROUP_QUALITY + Radar::stringutils::toString(num + 1);
	return new H5::Group( this->group->createGroup(name.c_str()));		
}

H5::Group* OdimData::getQualityGroup(int index)
{
	std::string name = GROUP_QUALITY + Radar::stringutils::toString(index + 1);
	return HDF5Group::getChild(this->group, name.c_str());				
}







/*===========================================================================*/
/* ODIM QUALITY */
/*===========================================================================*/

OdimQuality::OdimQuality(H5::Group* group)
:group(group)
,meta_what(NULL)
,meta_where(NULL)
,meta_how(NULL)
{
}

OdimQuality::~OdimQuality()
{
	try
	{
		delete meta_what;
		delete meta_where;
		delete meta_how;
		delete group;
	}
	catch (...)
	{
		/* mai lanciare eccezioni nei distruttori */
	}
}

H5::Group* OdimQuality::getH5Object()
{
	return group;
}

bool OdimQuality::existWhat() 				
{ 
	return HDF5Group::exists(group,GROUP_WHAT);
}

bool OdimQuality::existWhere() 				
{ 
	return HDF5Group::exists(group,GROUP_WHERE);
}

bool OdimQuality::existHow() 				
{ 
	return HDF5Group::exists(group,GROUP_HOW);	
}

MetadataGroup* OdimQuality::getWhat() 				
{ 
	if (meta_what==NULL)
		meta_what = getMetadataGroup(group, GROUP_WHAT);			
	return meta_what;
}

MetadataGroup* OdimQuality::getWhere() 				
{ 
	if (meta_where==NULL)
		meta_where = getMetadataGroup(group, GROUP_WHERE);			
	return meta_where;
}

MetadataGroup* OdimQuality::getHow() 				
{ 
	if (meta_how==NULL)
		meta_how = getMetadataGroup(group, GROUP_HOW);	
	return meta_how;
}

H5::DataSet*	OdimQuality::getData()
{
	return HDF5Group::getDataset(group, DATASET_DATA);
}

H5::AtomType	OdimQuality::getQualityType()
{
	H5::DataSet* dataset = NULL;
	try
	{
		dataset = getData();
		if (dataset)
		{
			H5::DataType type = dataset->getDataType();
			delete dataset;
			return HDF5AtomType::fromDataType(type);
		}
		else
		{
			return H5::PredType::NATIVE_OPAQUE;
		}
	}
	catch (H5::Exception& h5e)
	{
		delete dataset;		
		throw OdimH5HDF5LibException("Unable get odim data type info from HDF5 dataset", h5e);
	}
	catch (...)
	{
		delete dataset;
		throw;
	}
}

int OdimQuality::getQualityWidth()
{
	int height, width;
	getQualityDimension(&height, &width);
	return width;
}

int OdimQuality::getQualityHeight()
{
	int height, width;
	getQualityDimension(&height, &width);
	return height;
}

void OdimQuality::getQualityDimension(int* height, int* width)
{
	H5::DataSet* dataset = NULL;
	try
	{
		dataset = getData();
		if (dataset)
		{
			hsize_t sizes[3];
			hsize_t numsizes;
			numsizes = dataset->getSpace().getSimpleExtentDims(sizes);
			if (numsizes != 2)
				throw OdimH5v21::OdimH5FormatException("Dataset is not a matrix");			
			*height = (int)sizes[0];
			*width  = (int)sizes[1];
		}
		else
		{
			*height = 0;
			*width  = 0;
		}
		delete dataset;
	}
	catch (H5::Exception& h5e)
	{
		delete dataset;		
		throw OdimH5HDF5LibException("Unable get odim data infos from HDF5 dataset", h5e);
	}
	catch (...)
	{
		delete dataset;
		throw;
	}
}

void OdimQuality::writeQuality(const void* buff, int width, int height, const H5::DataType& elemtype)
{
	H5::DataSet* dataset = NULL;
	try
	{		
		HDF5Group::removeChild(group, DATASET_DATA);

		const int RANK = 2;
		hsize_t fdim[] = { (hsize_t)height, (hsize_t)width }; // dim sizes of ds (on disk)
		H5::DataSpace space(RANK, fdim);

		H5::DSetCreatPropList ds_creatplist;  // create dataset creation prop list
		ds_creatplist.setChunk( 2, fdim );  // then modify it for compression
		ds_creatplist.setDeflate( 6 );

		dataset = new H5::DataSet(group->createDataSet(DATASET_DATA, elemtype, space, ds_creatplist));			
		dataset->write(buff, elemtype);	// mspace1, fspace );
		if ((elemtype == H5::PredType::STD_U8BE) || (elemtype == H5::PredType::STD_U8LE) || (elemtype == H5::PredType::INTEL_U8) || 
		    (elemtype == H5::PredType::ALPHA_U8) || (elemtype == H5::PredType::MIPS_U8)  || (elemtype == H5::PredType::NATIVE_UCHAR) || 
		    (elemtype == H5::PredType::NATIVE_UINT8))
		{
			HDF5Attribute::set(dataset, ATTRIBUTE_CLASS,		CLASS_IMAGE);
			HDF5Attribute::set(dataset, ATTRIBUTE_IMAGE_VERSION,	IMAGE_VERSION_1_2);
		}
		delete dataset;
	}
	catch (H5::Exception& h5e)
	{
		delete dataset;		
		throw OdimH5HDF5LibException("Unable to write odim data into HDF5 dataset", h5e);
	}
	catch (...)
	{
		delete dataset;
		throw;
	}
}
void OdimQuality::writeQuality(const char* buff, int width, int height)
{
	writeQuality(buff, width, height, H5::PredType::NATIVE_INT8);
}
void OdimQuality::writeQuality(const unsigned char* buff, int width, int height)
{ 
	writeQuality(buff, width, height, H5::PredType::NATIVE_UINT8);
}
void OdimQuality::writeQuality(const unsigned short* buff, int width, int height)
{
	writeQuality(buff, width, height, H5::PredType::NATIVE_UINT16);
}
void OdimQuality::writeQuality(const float* buff, int width, int height)
{
	writeQuality(buff, width, height, H5::PredType::NATIVE_FLOAT);
}
void	OdimQuality::writeQuality(const DataMatrix<char>& matrix)		
{ 
	writeQuality(matrix.get(), matrix.getColCount(), matrix.getRowCount());	
}
void	OdimQuality::writeQuality(const DataMatrix<unsigned char>& matrix)	
{ 
	writeQuality(matrix.get(), matrix.getColCount(), matrix.getRowCount());	
}
void	OdimQuality::writeQuality(const DataMatrix<unsigned short>& matrix)	
{ 
	writeQuality(matrix.get(), matrix.getColCount(), matrix.getRowCount());	
}
void	OdimQuality::writeQuality(const DataMatrix<float>& matrix)		
{ 
	writeQuality(matrix.get(), matrix.getColCount(), matrix.getRowCount());	
}

void OdimQuality::readQuality(void* buff)
{
	H5::DataSet* dataset = getData();
	if (dataset == NULL) 
		return;			
	try
	{
		//hsize_t sizes[2];
		//hsize_t numsizes;
		//numsizes = dataset->getSpace().getSimpleExtentDims(sizes);
		//DataSpace space(numsizes, sizes);
		//dataset = new H5::DataSet(group->openDataSet(DATASET_DATA));
		dataset->read(buff, dataset->getDataType(), dataset->getSpace());	// mspace1, fspace );
		delete dataset;
	}
	catch (H5::Exception& h5e)
	{
		delete dataset;		
		throw OdimH5HDF5LibException("Unable to read odim data from HDF5 dataset", h5e);
	}
	catch (...)
	{
		delete dataset;
		throw;
	}
}

/*===========================================================================*/
/* POLAR VOLUME */
/*===========================================================================*/

PolarVolume::PolarVolume(H5::H5File* file)
:OdimObject(file)
,WHERERootMetadata()
,HOWRootMetadata() 
{		
		
}	

PolarVolume::~PolarVolume()
{	
}

double		PolarVolume::getLongitude	()				{ return getWhere()->getDouble	(ATTRIBUTE_WHERE_LON);		}
void		PolarVolume::setLongitude	(double val) 			{        getWhere()->set	(ATTRIBUTE_WHERE_LON, val);	}
double		PolarVolume::getLatitude	() 				{ return getWhere()->getDouble	(ATTRIBUTE_WHERE_LAT);		}
void		PolarVolume::setLatitude	(double val) 			{        getWhere()->set	(ATTRIBUTE_WHERE_LAT, val);	}
double		PolarVolume::getAltitude	() 				{ return getWhere()->getDouble	(ATTRIBUTE_WHERE_HEIGHT);	}
void		PolarVolume::setAltitude	(double val) 			{        getWhere()->set	(ATTRIBUTE_WHERE_HEIGHT, val);	}

std::string	PolarVolume::getTaskOrProdGen	() 				{ return getHow()->getStr	(ATTRIBUTE_HOW_TASK, "");		} 
void		PolarVolume::setTaskOrProdGen	(const std::string& val)	{        getHow()->set		(ATTRIBUTE_HOW_TASK, val);	}
time_t		PolarVolume::getStartEpochs	()				{ return getHow()->getTimeT	(ATTRIBUTE_HOW_STARTEPOCHS, 0);	}
void		PolarVolume::setStartEpochs	(time_t val) 			{        getHow()->set		(ATTRIBUTE_HOW_STARTEPOCHS, (int64_t)val); }
time_t		PolarVolume::getEndEpochs	()				{ return getHow()->getTimeT	(ATTRIBUTE_HOW_ENDEPOCHS, 0);	}
void		PolarVolume::setEndEpochs	(time_t val)			{        getHow()->set		(ATTRIBUTE_HOW_ENDEPOCHS, (int64_t)val); }
std::string	PolarVolume::getSystem		()				{ return getHow()->getStr	(ATTRIBUTE_HOW_SYSTEM, "");		}
void		PolarVolume::setSystem		(const std::string& val)	{        getHow()->set		(ATTRIBUTE_HOW_SYSTEM, val);	}
std::string	PolarVolume::getSoftware	()				{ return getHow()->getStr	(ATTRIBUTE_HOW_SOFTWARE, "");	}
void		PolarVolume::setSoftware	(const std::string& val)	{        getHow()->set		(ATTRIBUTE_HOW_SOFTWARE, val);	}
std::string	PolarVolume::getSoftwareVer	()				{ return getHow()->getStr	(ATTRIBUTE_HOW_SW_VERSION, "");	}
void		PolarVolume::setSoftwareVer	(const std::string& val)	{        getHow()->set		(ATTRIBUTE_HOW_SW_VERSION, val); }
double		PolarVolume::getZR_A		() 				{ return getHow()->getDouble	(ATTRIBUTE_HOW_ZR_A, 0);	}
void		PolarVolume::setZR_A		(double val)			{        getHow()->set		(ATTRIBUTE_HOW_ZR_A, val);	}
double		PolarVolume::getZR_B		()				{ return getHow()->getDouble	(ATTRIBUTE_HOW_ZR_B, 0);	}
void		PolarVolume::setZR_B		(double val)			{        getHow()->set		(ATTRIBUTE_HOW_ZR_B, val);	}
double		PolarVolume::getKR_A		()				{ return getHow()->getDouble	(ATTRIBUTE_HOW_KR_A, 0);	}
void		PolarVolume::setKR_A		(double val)			{        getHow()->set		(ATTRIBUTE_HOW_KR_A, val);	}
double		PolarVolume::getKR_B		()				{ return getHow()->getDouble	(ATTRIBUTE_HOW_KR_B, 0);	}
void		PolarVolume::setKR_B		(double val)			{        getHow()->set		(ATTRIBUTE_HOW_KR_B, val);	}
bool		PolarVolume::getSimulated	()				{ return getHow()->getBool	(ATTRIBUTE_HOW_SIMULATED, false); }
void		PolarVolume::setSimulated	(bool val)			{        getHow()->set		(ATTRIBUTE_HOW_SIMULATED, val); }

void	PolarVolume::setMandatoryInformations()
{			
	OdimObject::setMandatoryInformations();
	setObject	(OdimH5v21::OBJECT_PVOL);
	setVersion	(ModelVersion(2,1).toString());
	setDateTime	(Radar::timeutils::getUTC());
	setSource	(SourceInfo().setComment("unknown"));
}

void	PolarVolume::checkMandatoryInformations()
{
	OdimObject::checkMandatoryInformations();

	std::string object = this->getObject();
	if (object != OdimH5v21::OBJECT_PVOL)
		throw OdimH5FormatException(std::string("OdimH5 object is not ") + OdimH5v21::OBJECT_PVOL);	

	std::string version = this->getVersion();
	if (version != ModelVersion(2,1).toString())
		throw OdimH5FormatException("OdimH5 object version is not " + ModelVersion(2,1).toString());	

	time_t datetime = this->getDateTime();
	if (datetime == (time_t)-1)
		throw OdimH5FormatException("OdimH5 object date/time is not set");	
	
	SourceInfo source = this->getSource();
	if (source.toString().empty())
		throw OdimH5FormatException("OdimH5 object source is not set");	
}

int	PolarVolume::getScanCount() 
{
	return this->getDatasetCount();	
}

PolarScan* PolarVolume::createScan() 
{		
	H5::Group* scanGroup	= NULL;
	PolarScan* scan		= NULL;
	try
	{		
		scanGroup	= createDatasetGroup();
		scan		= new PolarScan(this, scanGroup);
		scanGroup	= NULL;
		scan->setMandatoryInformations();
		return scan;
	}
	catch (...)
	{
		delete scan;
		delete scanGroup;
		throw;
	}	
}

PolarScan* PolarVolume::getScan(int index) 
{
	H5::Group* h5group = NULL;
	try
	{
		h5group = getDatasetGroup(index);
		if (h5group)
			return new PolarScan(this, h5group);
		return NULL;	
	}
	catch (...)
	{
		delete h5group;
		throw;
	}
}

void PolarVolume::removeScan(int num)
{
	removeDataset(num);
}

std::vector<double> PolarVolume::getElevationAngles()
{
	/* prima prendo i gradi di tutti gli scan */
	std::vector<double> scanAngles = getScanAngles();

	/* poi tolgo i duplicati ma mantengo l'ordine */
	std::vector<double> result;
	for (size_t i=0; i<scanAngles.size(); i++)
	{
		double angle = scanAngles[i];

		if (Radar::math::isnan(angle))
			continue;

		result.push_back(angle);

		for (size_t j=0; j<scanAngles.size(); j++)
			if (scanAngles[j] == angle)
				scanAngles[j] = std::numeric_limits<double>::quiet_NaN();
	}

	return result;
}

std::vector<double> PolarVolume::getScanAngles()
{
	PolarScan* scan = NULL;
	try
	{
		std::vector<double> result;
		int scanCount = this->getScanCount();
		for (int i=0; i<scanCount; i++)
		{
			scan = this->getScan(i);
			result.push_back(scan->getEAngle());
			delete scan; scan = NULL;
		}
		return result;
	}
	catch (...)
	{
		delete scan;
		throw;
	}	
}

std::vector<PolarScan*> PolarVolume::getScans	()
{
	return getScansBetween(-360., 360.);
}

std::vector<PolarScan*> PolarVolume::getScans	(double elevation, double gap)
{
	return getScansBetween(elevation - gap, elevation + gap);
}

std::vector<PolarScan*> PolarVolume::getScansBetween	(double minElevation, double maxElevation)
{
	std::vector<PolarScan*> result;	
	try
	{
		int scanCount = this->getScanCount();
		for (int i=0; i<scanCount; i++)
		{
			PolarScan* scan = NULL;			
			try
			{
				scan = this->getScan(i);
				double angle = scan->getEAngle();
				if ((angle < minElevation) || (angle > maxElevation))				
				{
					delete scan;
					scan = NULL;
				}
				else 
					result.push_back(scan);
			}
			catch (OdimH5Exception& e)
			{
				delete scan;
				throw OdimH5Exception("Error while checking scan n. "+Radar::stringutils::toString(i)+": "+e.what()); 
			}			
		}

		return result;	
	}
	catch (...)
	{
		//cancelliamo gli scan aperti
		for (size_t i=0; i<result.size(); i++)
			delete result[i];
		throw;
	}
}

std::vector<PolarScan*> PolarVolume::getScans(const std::string& quantity)
{
	return getScans(quantity.c_str());
}

std::vector<PolarScan*> PolarVolume::getScans(const char* quantity)
{
	std::vector<PolarScan*> result;	
	try
	{
		int scanCount = this->getScanCount();
		for (int i=0; i<scanCount; i++)
		{
			PolarScan*	scan = NULL;						
			try
			{
				scan = this->getScan(i);	
				if (scan->hasQuantityData(quantity))
					result.push_back(scan);
				else
					delete scan;
			}
			catch (OdimH5Exception& e)
			{				
				delete scan;
				throw OdimH5Exception("Error while checking scan n. "+Radar::stringutils::toString(i)+": "+e.what()); 
			}			
		}

		return result;	
	}
	catch (...)
	{
		//cancelliamo gli scan aperti
		for (size_t i=0; i<result.size(); i++)
			delete result[i];
		throw;
	}
}

static void deleteScans(std::vector<PolarScan*>& scans)
{
	for (size_t i=0; i<scans.size(); i++)
		delete scans[i]; 
	scans.clear();
}

std::set<std::string> PolarVolume::getStoredQuantities()
{
	std::vector<PolarScan*> scans;
	try
	{
		scans = getScans();
		std::set<std::string> result;
		for (size_t i=0; i<scans.size(); i++)
		{
			std::set<std::string> quantities = scans[i]->getStoredQuantities();
			result.insert(quantities.begin(), quantities.end());
		}
		deleteScans(scans);
		return result;
	}
	catch (...)
	{
		deleteScans(scans);
		throw;
	}
}

/*===========================================================================*/
/* POLAR VOLUME SCAN */
/*===========================================================================*/

std::set<std::string> PolarScan::getStoredQuantities()
{
	std::set<std::string> result;
	int dataCount = getDataCount();
	for (int i=0; i<dataCount; i++)
	{
		PolarScanData* data = NULL;
		try
		{
			data = getQuantityData(i);
			result.insert(data->getQuantity());
			delete data;
		}
		catch (...)
		{
			delete data;
			throw;
		}
	}
	return result;
}

PolarScan::PolarScan(PolarVolume* volume, H5::Group* group)
:OdimDataset(group)
,WHATDatasetMetadata()
,WHEREScanMetadata()
,HOWPolarMetadata()
,volume(volume)
{			
}

PolarScan::~PolarScan()
{		
}

void PolarScan::setMandatoryInformations()
{		
	setProduct(OdimH5v21::PRODUCT_SCAN);		
}

//--- WHAT ROOT ---

std::string	PolarScan::getObject		()				{ return getWhat()->getStr	(ATTRIBUTE_WHAT_OBJECT);	}
void		PolarScan::setObject		(const std::string& val) 	{        getWhat()->set		(ATTRIBUTE_WHAT_OBJECT, val);	}
std::string	PolarScan::getVersion		() 				{ return getWhat()->getStr	(ATTRIBUTE_WHAT_VERSION);		}
void		PolarScan::setVersion		(const std::string& val)	{        getWhat()->set		(ATTRIBUTE_WHAT_VERSION, val);	}
time_t		PolarScan::getDateTime		()				{ return getWhatDateTime(this->getWhat()); }
void		PolarScan::setDateTime		(const time_t val)		{	 setWhatDateTime(this->getWhat(), val); }
SourceInfo	PolarScan::getSource		() 				{ return SourceInfo(getWhat()->getStr(ATTRIBUTE_WHAT_SOURCE));		}
void		PolarScan::setSource		(const SourceInfo& val)		{        getWhat()->set		(ATTRIBUTE_WHAT_SOURCE, val.toString() );	}

//--- WHAT DATASET---

std::string		PolarScan::getProduct		()				{ return getWhat()->getStr	(ATTRIBUTE_WHAT_PRODUCT);	}
void			PolarScan::setProduct		(const std::string& val)	{        getWhat()->set		(ATTRIBUTE_WHAT_PRODUCT, val);	}	
double			PolarScan::getProdPar		()				{ return getWhat()->getDouble	(ATTRIBUTE_WHAT_PRODPAR); 	}
VILHeights		PolarScan::getProdParVIL	()				{ return VILHeights();  }
void			PolarScan::setProdPar		(double val) 			{ return getWhat()->set	(ATTRIBUTE_WHAT_PRODPAR, val);	 }
void			PolarScan::setProdPar		(const VILHeights& val)		{ return getWhat()->set	(ATTRIBUTE_WHAT_PRODPAR, val);	 }
std::string		PolarScan::getQuantity		() 				{ return getWhat()->getStr	(ATTRIBUTE_WHAT_QUANTITY);	}
void			PolarScan::setQuantity		(const std::string& val)	{        getWhat()->set		(ATTRIBUTE_WHAT_QUANTITY, val);	}
time_t			PolarScan::getStartDateTime	()				{ return getWhatStartDateTime(this->getWhat());			}
void			PolarScan::setStartDateTime	(time_t value)			{	 setWhatStartDateTime(this->getWhat(), value);		}
time_t			PolarScan::getEndDateTime	()				{ return getWhatEndDateTime(this->getWhat());			}
void			PolarScan::setEndDateTime	(time_t value)			{	 setWhatEndDateTime(this->getWhat(), value);		}
double			PolarScan::getGain		() 				{ return getWhat()->getDouble	(ATTRIBUTE_WHAT_GAIN);			}
void			PolarScan::setGain		(double val)			{        getWhat()->set		(ATTRIBUTE_WHAT_GAIN, val);		}
double			PolarScan::getOffset		() 				{ return getWhat()->getDouble	(ATTRIBUTE_WHAT_OFFSET);		}
void			PolarScan::setOffset		(double val) 			{        getWhat()->set		(ATTRIBUTE_WHAT_OFFSET, val);	}
double			PolarScan::getNodata		()				{ return getWhat()->getDouble	(ATTRIBUTE_WHAT_NODATA);		}
void			PolarScan::setNodata		(double val) 			{        getWhat()->set		(ATTRIBUTE_WHAT_NODATA, val);	}
double			PolarScan::getUndetect		()				{ return getWhat()->getDouble	(ATTRIBUTE_WHAT_UNDETECT);		}
void			PolarScan::setUndetect		(double val) 			{        getWhat()->set		(ATTRIBUTE_WHAT_UNDETECT, val);	}

//--- WHERE ROOT ---

double		PolarScan::getLongitude		()				{ return getWhere()->getDouble	(ATTRIBUTE_WHERE_LON);		}
void		PolarScan::setLongitude		(double val) 			{        getWhere()->set	(ATTRIBUTE_WHERE_LON, val);	}
double		PolarScan::getLatitude		() 				{ return getWhere()->getDouble	(ATTRIBUTE_WHERE_LAT);		}
void		PolarScan::setLatitude		(double val) 			{        getWhere()->set	(ATTRIBUTE_WHERE_LAT, val);	}
double		PolarScan::getAltitude		() 				{ return getWhere()->getDouble	(ATTRIBUTE_WHERE_HEIGHT);	}
void		PolarScan::setAltitude		(double val) 			{        getWhere()->set	(ATTRIBUTE_WHERE_HEIGHT, val);	}

//--- WHERE DATASET ---

double		PolarScan::getEAngle		()				{ return getWhere()->getDouble	(ATTRIBUTE_WHERE_ELANGLE);	}
void		PolarScan::setEAngle		(double val)			{        getWhere()->set	(ATTRIBUTE_WHERE_ELANGLE, val);	}
int		PolarScan::getNumBins		()				{ return getWhere()->getInt	(ATTRIBUTE_WHERE_NBINS);	}
void		PolarScan::setNumBins		(int val)			{        getWhere()->set	(ATTRIBUTE_WHERE_NBINS, val);	}
double		PolarScan::getRangeStart	()				{ return getWhere()->getDouble	(ATTRIBUTE_WHERE_RSTART);	}
void		PolarScan::setRangeStart	(double val)			{        getWhere()->set	(ATTRIBUTE_WHERE_RSTART, val);	}
double		PolarScan::getRangeScale	()				{ return getWhere()->getDouble	(ATTRIBUTE_WHERE_RSCALE);	}
void		PolarScan::setRangeScale	(double val)			{        getWhere()->set	(ATTRIBUTE_WHERE_RSCALE, val);	}
int		PolarScan::getNumRays		()				{ return getWhere()->getInt	(ATTRIBUTE_WHERE_NRAYS);	}
void		PolarScan::setNumRays		(int val)			{        getWhere()->set	(ATTRIBUTE_WHERE_NRAYS, val);	}
int		PolarScan::getA1Gate		()				{ return getWhere()->getInt	(ATTRIBUTE_WHERE_A1GATE);	}
void		PolarScan::setA1Gate		(int val)			{	 getWhere()->set	(ATTRIBUTE_WHERE_A1GATE, val);	}

//--- HOW ROOT ---

std::string	PolarScan::getTaskOrProdGen	() 				{ return getHow()->getStr	(ATTRIBUTE_HOW_TASK, "");		} 
void		PolarScan::setTaskOrProdGen	(const std::string& val)	{        getHow()->set		(ATTRIBUTE_HOW_TASK, val);		}
time_t		PolarScan::getStartEpochs	()				{ return getHow()->getTimeT	(ATTRIBUTE_HOW_STARTEPOCHS, 0);		}
void		PolarScan::setStartEpochs	(time_t val) 			{        getHow()->set		(ATTRIBUTE_HOW_STARTEPOCHS, (int64_t)val); }
time_t		PolarScan::getEndEpochs		()				{ return getHow()->getTimeT	(ATTRIBUTE_HOW_ENDEPOCHS, 0);		}
void		PolarScan::setEndEpochs		(time_t val)			{        getHow()->set		(ATTRIBUTE_HOW_ENDEPOCHS, (int64_t)val); }
std::string	PolarScan::getSystem		()				{ return getHow()->getStr	(ATTRIBUTE_HOW_SYSTEM, 0);		}
void		PolarScan::setSystem		(const std::string& val)	{        getHow()->set		(ATTRIBUTE_HOW_SYSTEM, val);		}
std::string	PolarScan::getSoftware		()				{ return getHow()->getStr	(ATTRIBUTE_HOW_SOFTWARE, 0);		}
void		PolarScan::setSoftware		(const std::string& val)	{        getHow()->set		(ATTRIBUTE_HOW_SOFTWARE, val);		}
std::string	PolarScan::getSoftwareVer	()				{ return getHow()->getStr	(ATTRIBUTE_HOW_SW_VERSION, "");		}
void		PolarScan::setSoftwareVer	(const std::string& val)	{        getHow()->set		(ATTRIBUTE_HOW_SW_VERSION, val);	}
double		PolarScan::getZR_A		() 				{ return getHow()->getDouble	(ATTRIBUTE_HOW_ZR_A, 0);		}
void		PolarScan::setZR_A		(double val)			{        getHow()->set		(ATTRIBUTE_HOW_ZR_A, val);		}
double		PolarScan::getZR_B		()				{ return getHow()->getDouble	(ATTRIBUTE_HOW_ZR_B, 0);		}
void		PolarScan::setZR_B		(double val)			{        getHow()->set		(ATTRIBUTE_HOW_ZR_B, val);		}
double		PolarScan::getKR_A		()				{ return getHow()->getDouble	(ATTRIBUTE_HOW_KR_A, 0);		}
void		PolarScan::setKR_A		(double val)			{        getHow()->set		(ATTRIBUTE_HOW_KR_A, val);		}
double		PolarScan::getKR_B		()				{ return getHow()->getDouble	(ATTRIBUTE_HOW_KR_B, 0);		}
void		PolarScan::setKR_B		(double val)			{        getHow()->set		(ATTRIBUTE_HOW_KR_B, val);		}
bool		PolarScan::getSimulated		()				{ return getHow()->getBool	(ATTRIBUTE_HOW_SIMULATED, false);	}
void		PolarScan::setSimulated		(bool val)			{        getHow()->set		(ATTRIBUTE_HOW_SIMULATED, val);		}

//--- HOW DATASET ---

double		PolarScan::getBeamWidth		()				{ return getHow()->getDouble	(ATTRIBUTE_HOW_BEAMWIDTH, 0);			}
double		PolarScan::getBeamWidth		(double defaultValue)		{ return getHow()->getDouble	(ATTRIBUTE_HOW_BEAMWIDTH, defaultValue);	}
void		PolarScan::setBeamWidth		(double val)			{        getHow()->set		(ATTRIBUTE_HOW_BEAMWIDTH, val);			}
double		PolarScan::getWaveLength	()				{ return getHow()->getDouble	(ATTRIBUTE_HOW_WAVELENGTH, 0);			}
double		PolarScan::getWaveLength	(double defaultValue)		{ return getHow()->getDouble	(ATTRIBUTE_HOW_WAVELENGTH, defaultValue);	}
void		PolarScan::setWaveLength	(double val)			{        getHow()->set		(ATTRIBUTE_HOW_WAVELENGTH, val);		}
double		PolarScan::getRPM		()				{ return getHow()->getDouble	(ATTRIBUTE_HOW_RPM, 0);				}
double		PolarScan::getRPM		(double defaultValue)		{ return getHow()->getDouble	(ATTRIBUTE_HOW_RPM, defaultValue);		}
void		PolarScan::setRPM		(double val)			{        getHow()->set		(ATTRIBUTE_HOW_RPM, val);			}
double		PolarScan::getPulseWidth	()				{ return getHow()->getDouble	(ATTRIBUTE_HOW_PULSEWIDTH, 0);			}
double		PolarScan::getPulseWidth	(double defaultValue)		{ return getHow()->getDouble	(ATTRIBUTE_HOW_PULSEWIDTH, defaultValue);	}
void		PolarScan::setPulseWidth	(double val)			{        getHow()->set		(ATTRIBUTE_HOW_PULSEWIDTH, val);		}
double		PolarScan::getRXBandWidth	()				{ return getHow()->getDouble	(ATTRIBUTE_HOW_RXBANDWIDTH, 0);			}
double		PolarScan::getRXBandWidth	(double defaultValue)		{ return getHow()->getDouble	(ATTRIBUTE_HOW_RXBANDWIDTH, defaultValue);	}
void		PolarScan::setRXBandWidth	(double val)			{        getHow()->set		(ATTRIBUTE_HOW_RXBANDWIDTH, val);		}
int		PolarScan::getLowPRF		()				{ return getHow()->getInt	(ATTRIBUTE_HOW_LOWPRF, 0);			}
int		PolarScan::getLowPRF		(int defaultValue)		{ return getHow()->getInt	(ATTRIBUTE_HOW_LOWPRF, defaultValue);		}
void		PolarScan::setLowPRF		(int val)			{        getHow()->set		(ATTRIBUTE_HOW_LOWPRF, val);			}
int		PolarScan::getHighPRF		()				{ return getHow()->getInt	(ATTRIBUTE_HOW_HIGHPRF, 0);			}
int		PolarScan::getHighPRF		(int defaultValue)		{ return getHow()->getInt	(ATTRIBUTE_HOW_HIGHPRF, defaultValue);		}
void		PolarScan::setHighPRF		(int val)			{        getHow()->set		(ATTRIBUTE_HOW_HIGHPRF, val);			}

double		PolarScan::getTXLoss		()		    		{ return getHow()->getDouble	(ATTRIBUTE_HOW_TXLOSS, 0);			}
double		PolarScan::getTXLoss		(double defaultValue)		{ return getHow()->getDouble	(ATTRIBUTE_HOW_TXLOSS, defaultValue);	}
void		PolarScan::setTXLoss		(double val)	     		{        getHow()->set		(ATTRIBUTE_HOW_TXLOSS, val);		}
double		PolarScan::getRXLoss		()		     		{ return getHow()->getDouble	(ATTRIBUTE_HOW_RXLOSS, 0);			}
double		PolarScan::getRXLoss		(double defaultValue)		{ return getHow()->getDouble	(ATTRIBUTE_HOW_RXLOSS, defaultValue);	}
void		PolarScan::setRXLoss		(double val)	     		{        getHow()->set		(ATTRIBUTE_HOW_RXLOSS, val);		}
double		PolarScan::getRadomeLoss	()				{ return getHow()->getDouble	(ATTRIBUTE_HOW_RADOMELOSS, 0);			}     
double		PolarScan::getRadomeLoss	(double defaultValue)		{ return getHow()->getDouble	(ATTRIBUTE_HOW_RADOMELOSS, defaultValue);	}
void		PolarScan::setRadomeLoss	(double val)	     		{        getHow()->set		(ATTRIBUTE_HOW_RADOMELOSS, val);		}
double		PolarScan::getAntGain		()		     		{ return getHow()->getDouble	(ATTRIBUTE_HOW_ANTGAIN, 0);			}
double		PolarScan::getAntGain		(double defaultValue)		{ return getHow()->getDouble	(ATTRIBUTE_HOW_ANTGAIN, defaultValue);	}
void		PolarScan::setAntGain		(double val)	     		{        getHow()->set		(ATTRIBUTE_HOW_ANTGAIN, val);		}
double		PolarScan::getBeamWH		()		     		{ return getHow()->getDouble	(ATTRIBUTE_HOW_BEAMWH, 0);			}
double		PolarScan::getBeamWH		(double defaultValue)		{ return getHow()->getDouble	(ATTRIBUTE_HOW_BEAMWH, defaultValue);	}
void		PolarScan::setBeamWH		(double val)	     		{        getHow()->set		(ATTRIBUTE_HOW_BEAMWH, val);		}
double		PolarScan::getBeamWV		()		     		{ return getHow()->getDouble	(ATTRIBUTE_HOW_BEAMWV, 0);			}
double		PolarScan::getBeamWV		(double defaultValue)		{ return getHow()->getDouble	(ATTRIBUTE_HOW_BEAMWV, defaultValue);	}
void		PolarScan::setBeamWV		(double val)	     		{        getHow()->set		(ATTRIBUTE_HOW_BEAMWV, val);		}
double		PolarScan::getGasAttn		()		     		{ return getHow()->getDouble	(ATTRIBUTE_HOW_GASATTN, 0);			}
double		PolarScan::getGasAttn		(double defaultValue)		{ return getHow()->getDouble	(ATTRIBUTE_HOW_GASATTN, defaultValue);	}
void		PolarScan::setGasAttn		(double val)	     		{        getHow()->set		(ATTRIBUTE_HOW_GASATTN, val);		}
double		PolarScan::getRadConstH		()		     		{ return getHow()->getDouble	(ATTRIBUTE_HOW_RADCONSTH, 0);			}
double		PolarScan::getRadConstH		(double defaultValue)		{ return getHow()->getDouble	(ATTRIBUTE_HOW_RADCONSTH, defaultValue);	}
void		PolarScan::setRadConstH		(double val)	     		{        getHow()->set		(ATTRIBUTE_HOW_RADCONSTH, val);		}
double		PolarScan::getRadConstV		()		     		{ return getHow()->getDouble	(ATTRIBUTE_HOW_RADCONSTV, 0);			}
double		PolarScan::getRadConstV		(double defaultValue)		{ return getHow()->getDouble	(ATTRIBUTE_HOW_RADCONSTV, defaultValue);	}
void		PolarScan::setRadConstV		(double val)	     		{        getHow()->set		(ATTRIBUTE_HOW_RADCONSTV, val);		}
double		PolarScan::getNomTXPower	()		     		{ return getHow()->getDouble	(ATTRIBUTE_HOW_NOMTXPOWER, 0);			}
double		PolarScan::getNomTXPower	(double defaultValue)		{ return getHow()->getDouble	(ATTRIBUTE_HOW_NOMTXPOWER, defaultValue);	}
void		PolarScan::setNomTXPower	(double val)	     		{        getHow()->set		(ATTRIBUTE_HOW_NOMTXPOWER, val);		}
std::vector<double>	PolarScan::getTXPower		()		        
{ 
	try
	{
		int			numrays = this->getNumRays();
		std::vector<double>	result	;  //  = getHow()->getDoubles(ATTRIBUTE_HOW_ELANGLES);	
	        return result;
		std::ostringstream ss;
		ss << "elangles values ("<<result.size()<<") are not as many as numrays ("<<numrays<<")";
		throw OdimH5FormatException(ss.str());
	}
	catch (std::exception& e)
	{
		throw OdimH5Exception(std::string("Error getting elangles: ") + e.what());
	}
}
		
std::vector<double>	PolarScan::getTXPower		(double defaultValue)
{ 
	try
	{
		int			numrays = this->getNumRays();
		std::vector<double>	result	;  //  = getHow()->getDoubles(ATTRIBUTE_HOW_ELANGLES);	
	        return result;
		std::ostringstream ss;
		ss << "elangles values ("<<result.size()<<") are not as many as numrays ("<<numrays<<")";
		throw OdimH5FormatException(ss.str());
	}
	catch (std::exception& e)
	{
		throw OdimH5Exception(std::string("Error getting elangles: ") + e.what());
	}
}
void		PolarScan::setTXPower		(double val)	   {;}  
// (const std::vector<double>& val, int precision)	{        getHow()->set		(ATTRIBUTE_HOW_ELANGLES, val, precision);	}

double		PolarScan::getNI		()		     		{ return getHow()->getDouble	(ATTRIBUTE_HOW_NI, 0);			}
double		PolarScan::getNI		(double defaultValue)		{ return getHow()->getDouble	(ATTRIBUTE_HOW_NI, defaultValue);	}
void		PolarScan::setNI		(double val)	     		{        getHow()->set		(ATTRIBUTE_HOW_NI, val);		}
double		PolarScan::getVSamples		()		     		{ return getHow()->getDouble	(ATTRIBUTE_HOW_VSAMPLES, 0);			}
double		PolarScan::getVSamples		(double defaultValue)		{ return getHow()->getDouble	(ATTRIBUTE_HOW_VSAMPLES, defaultValue);	}
void		PolarScan::setVSamples		(double val)			{        getHow()->set		(ATTRIBUTE_HOW_VSAMPLES, val);		}




std::string		PolarScan::getAzimuthMethod	()					{ return getHow()->getStr	(ATTRIBUTE_HOW_AZMETHOD, "");	}
void			PolarScan::setAzimuthMethod	(const std::string& val)		{        getHow()->set		(ATTRIBUTE_HOW_AZMETHOD, val);	}
std::string		PolarScan::getBinMethod		()					{ return getHow()->getStr	(ATTRIBUTE_HOW_BINMETHOD, "");	}
void			PolarScan::setBinMethod		(const std::string& val)		{        getHow()->set		(ATTRIBUTE_HOW_BINMETHOD, val);	}
std::vector<double>	PolarScan::getElevationAngles	() 					
{ 
	try
	{
		int			numrays = this->getNumRays();
		std::vector<double>	result	= getHow()->getDoubles(ATTRIBUTE_HOW_ELANGLES);		

		/* se il numero di elementi corrisponde */
		if (result.size() == numrays)	
			return result;

		double			elangle = this->getEAngle();

		/* se l'attributo non aveva nessun valore */
		if (result.size() == 0)
		{	
			result.resize(numrays);
			for (int i=0; i<numrays; i++)
				result[i] = elangle;
			return result;
		}	

		/* se il numero di elementi non corrisponde c'e' qauclacosa che non va*/
		std::ostringstream ss;
		ss << "elangles values ("<<result.size()<<") are not as many as numrays ("<<numrays<<")";
		throw OdimH5FormatException(ss.str());
	}
	catch (std::exception& e)
	{
		throw OdimH5Exception(std::string("Error getting elangles: ") + e.what());
	}
}
void			PolarScan::setElevationAngles	(const std::vector<double>& val)	{        getHow()->set		(ATTRIBUTE_HOW_ELANGLES, val, 5);	}
std::vector<double>	PolarScan::getStartAzimuthAngles	()				 
{
	return getHow()->getSimpleArrayDouble(ATTRIBUTE_HOW_STARTAZA);
}
void			PolarScan::setStartAzimuthAngles	(const std::vector<double>& val) {} 
std::vector<double>	PolarScan::getStopAzimuthAngles	()				 
{ 
	try
	{
		int			numrays = this->getNumRays();
		std::vector<double>	result	;  //  = getHow()->getDoubles(ATTRIBUTE_HOW_ELANGLES);	
	        return result;
		std::ostringstream ss;
		ss << "elangles values ("<<result.size()<<") are not as many as numrays ("<<numrays<<")";
		throw OdimH5FormatException(ss.str());
	}
	catch (std::exception& e)
	{
		throw OdimH5Exception(std::string("Error getting elangles: ") + e.what());
	}
}
void			PolarScan::setStopAzimuthAngles	(const std::vector<double>& val) {}
std::vector<double>	PolarScan::getStartAzimuthTimes	()				 
{ 
	try
	{
		int			numrays = this->getNumRays();
		std::vector<double>	result	;  //  = getHow()->getDoubles(ATTRIBUTE_HOW_ELANGLES);	
	        return result;
		std::ostringstream ss;
		ss << "elangles values ("<<result.size()<<") are not as many as numrays ("<<numrays<<")";
		throw OdimH5FormatException(ss.str());
	}
	catch (std::exception& e)
	{
		throw OdimH5Exception(std::string("Error getting elangles: ") + e.what());
	}
}
void			PolarScan::setStartAzimuthTimes	(const std::vector<double>& val) {}
std::vector<double>	PolarScan::getStopAzimuthTimes	()				 
{ 
	try
	{
		int			numrays = this->getNumRays();
		std::vector<double>	result	;  //  = getHow()->getDoubles(ATTRIBUTE_HOW_ELANGLES);	
	        return result;
		std::ostringstream ss;
		ss << "elangles values ("<<result.size()<<") are not as many as numrays ("<<numrays<<")";
		throw OdimH5FormatException(ss.str());
	}
	catch (std::exception& e)
	{
		throw OdimH5Exception(std::string("Error getting elangles: ") + e.what());
	}
}
void			PolarScan::setStopAzimuthTimes	(const std::vector<double>& val) {}



double		PolarScan::getPointAccEl	()				{ return getHow()->getDouble	(ATTRIBUTE_HOW_POINTACCEL, 0);		}
void		PolarScan::setPointAccEl	(double val)			{        getHow()->set		(ATTRIBUTE_HOW_POINTACCEL, val);	}
double		PolarScan::getPointAccAZ	()				{ return getHow()->getDouble	(ATTRIBUTE_HOW_POINTACCAZ, 0);		} 
void		PolarScan::setPointAccAZ	(double val)			{        getHow()->set		(ATTRIBUTE_HOW_POINTACCAZ, val);	}
bool		PolarScan::getMalfunc		()				{ return getHow()->getBool	(ATTRIBUTE_HOW_MALFUNC, false);		}
void		PolarScan::setMalfunc		(bool val)			{        getHow()->set		(ATTRIBUTE_HOW_MALFUNC, val);		}
std::string	PolarScan::getRadarMsg		()				{ return getHow()->getStr	(ATTRIBUTE_HOW_RADAR_MSG, "");		}
void		PolarScan::setRadarMsg		(const std::string& val)	{        getHow()->set		(ATTRIBUTE_HOW_RADAR_MSG, val);		}
double		PolarScan::getRadarHorizon	()				{ return getHow()->getDouble	(ATTRIBUTE_HOW_RADHORIZ, 0);		}
void		PolarScan::setRadarHorizon	(double val)			{        getHow()->set		(ATTRIBUTE_HOW_RADHORIZ, val);		}
double		PolarScan::getNEZ		()				{ return getHow()->getDouble	(ATTRIBUTE_HOW_NEZ, 0);			}
void		PolarScan::setNEZ		(double val)			{        getHow()->set		(ATTRIBUTE_HOW_NEZ, val);		}
double		PolarScan::getOUR		()				{ return getHow()->getDouble	(ATTRIBUTE_HOW_OUR, 0);			}
void		PolarScan::setOUR		(double val)			{        getHow()->set		(ATTRIBUTE_HOW_OUR, val);		}
std::vector<std::string> PolarScan::getDClutter	()				{ return getHow()->getStrings	(ATTRIBUTE_HOW_DCLUTTER);		}
void		PolarScan::setDClutter		(const std::vector<std::string>& vals) { getHow()->set		(ATTRIBUTE_HOW_DCLUTTER, vals);	}
std::string	PolarScan::getComment		()				{ return getHow()->getStr	(ATTRIBUTE_HOW_COMMENT, "");		}
void		PolarScan::setComment		(const std::string& val)	{        getHow()->set		(ATTRIBUTE_HOW_COMMENT, val);		}
double		PolarScan::getSQI		()				{ return getHow()->getDouble	(ATTRIBUTE_HOW_SQI, 0);			}
void		PolarScan::setSQI		(double val)			{        getHow()->set		(ATTRIBUTE_HOW_SQI, val);		}
double		PolarScan::getCSR		()				{ return getHow()->getDouble	(ATTRIBUTE_HOW_CSR, 0);			}
void		PolarScan::setCSR		(double val)			{        getHow()->set		(ATTRIBUTE_HOW_CSR, val);		}
double		PolarScan::getLOG		()				{ return getHow()->getDouble	(ATTRIBUTE_HOW_LOG, 0);			}
void		PolarScan::setLOG		(double val)			{        getHow()->set		(ATTRIBUTE_HOW_LOG, val);		}
bool		PolarScan::getVPRCorr		()				{ return getHow()->getBool	(ATTRIBUTE_HOW_VPRCORR, false);		}
void		PolarScan::setVPRCorr		(bool val)			{        getHow()->set		(ATTRIBUTE_HOW_VPRCORR, val);		}
double		PolarScan::getFreeze		()				{ return getHow()->getDouble	(ATTRIBUTE_HOW_FREEZE, 0);		}
void		PolarScan::setFreeze		(double val)			{        getHow()->set		(ATTRIBUTE_HOW_FREEZE, val);		}
double		PolarScan::getMin		()				{ return getHow()->getDouble	(ATTRIBUTE_HOW_MIN, 0);			}
void		PolarScan::setMin		(double val)			{        getHow()->set		(ATTRIBUTE_HOW_MIN, val);		}
double		PolarScan::getMax		()				{ return getHow()->getDouble	(ATTRIBUTE_HOW_MAX, 0);			}
void		PolarScan::setMax		(double val)			{        getHow()->set		(ATTRIBUTE_HOW_MAX, val);		}
double		PolarScan::getStep		()				{ return getHow()->getDouble	(ATTRIBUTE_HOW_STEP, 0);		}
void		PolarScan::setStep		(double val)			{        getHow()->set		(ATTRIBUTE_HOW_STEP, val);		}
int		PolarScan::getLevels		()				{ return getHow()->getInt	(ATTRIBUTE_HOW_LEVELS, 0);		}
void		PolarScan::setLevels		(int val)			{        getHow()->set		(ATTRIBUTE_HOW_LEVELS, val);		}
double		PolarScan::getPeakPwr		()				{ return getHow()->getDouble	(ATTRIBUTE_HOW_PEAKPWR, 0);		}
void		PolarScan::setPeakPwr		(double val)			{        getHow()->set		(ATTRIBUTE_HOW_PEAKPWR, val);		}
double		PolarScan::getAvgPwr		()				{ return getHow()->getDouble	(ATTRIBUTE_HOW_AVGPWR, 0);		}
void		PolarScan::setAvgPwr		(double val)			{        getHow()->set		(ATTRIBUTE_HOW_AVGPWR, val);		}
double		PolarScan::getDynRange		()				{ return getHow()->getDouble	(ATTRIBUTE_HOW_DYNRANGE, 0);		}
void		PolarScan::setDynRange		(double val)			{        getHow()->set		(ATTRIBUTE_HOW_DYNRANGE, val);		}
double		PolarScan::getRAC		()				{ return getHow()->getDouble	(ATTRIBUTE_HOW_RAC, 0);			}
void		PolarScan::setRAC		(double val)			{        getHow()->set		(ATTRIBUTE_HOW_RAC, val);		}
bool		PolarScan::getBBC		()				{ return getHow()->getBool	(ATTRIBUTE_HOW_BBC, 0);			}
void		PolarScan::setBBC		(bool val)			{        getHow()->set		(ATTRIBUTE_HOW_BBC, val);		}
double		PolarScan::getPAC		()				{ return getHow()->getDouble	(ATTRIBUTE_HOW_PAC, 0);			}
void		PolarScan::setPAC		(double val)			{        getHow()->set		(ATTRIBUTE_HOW_PAC, val);		}
double		PolarScan::getS2N		()				{ return getHow()->getDouble	(ATTRIBUTE_HOW_S2N, 0);			}
void		PolarScan::setS2N		(double val)			{        getHow()->set		(ATTRIBUTE_HOW_S2N, val);		}
std::string	PolarScan::getPolarization	()				{ return getHow()->getStr	(ATTRIBUTE_HOW_POLARIZATION, "");	}
void		PolarScan::setPolarization	(const std::string& val)	{        getHow()->set		(ATTRIBUTE_HOW_POLARIZATION, val);	}

//--- METODI ---

int PolarScan::getQuantityDataCount	()
{
	return getDataCount();
}

bool PolarScan::hasQuantityData(const std::string& name)
{
	return hasQuantityData(name.c_str());
}

bool PolarScan::hasQuantityData(const char* name) 
{
	return getQuantityDataIndex(name) >= 0;
}

PolarScanData*	PolarScan::createQuantityData(const std::string& name)
{
	return createQuantityData(name.c_str()) ;
}

PolarScanData*	PolarScan::createQuantityData(const char* name) 
{
	PolarScanData* data = getQuantityData(name);
	if (data)
		return data;

	H5::Group*	dataGroup	= NULL;
	PolarScanData*	result		= NULL;
	try
	{
		dataGroup	= createDataGroup();
		result		= new PolarScanData(this, dataGroup);
		dataGroup	= NULL;
		result->setQuantity(name);
		return result;
	}
	catch (...)
	{
		delete dataGroup;
		delete result;
		throw;
	}
}

PolarScanData*	PolarScan::getQuantityData(const std::string& name) 
{
	return getQuantityData(name.c_str()); 
}

PolarScanData*	PolarScan::getQuantityData(const char* name) 
{		
	int dataCount = getDataCount();
	for (int i=0; i<dataCount; i++)
	{
		PolarScanData* data = NULL;
		try
		{
			data = getQuantityData(i);
			std::string quantity = data->getQuantity();
			if (quantity == name)
				return data;
			delete data;
		}
		catch (...)
		{
			delete data;
			throw;
		}
	}
	return NULL;
}

PolarScanData*	PolarScan::getQuantityData(int index) 
{
	H5::Group* h5group = getDataGroup(index);
	try
	{
		if (h5group)
			return  new PolarScanData(this, h5group);
		return NULL;
	}
	catch (...)
	{
		delete h5group;
		throw;
	}
}

void PolarScan::removeQuantityData(const std::string& name) 
{
	return removeQuantityData(name.c_str());
}

void PolarScan::removeQuantityData(const char* name) 
{				
	int index = getQuantityDataIndex(name);
	if (index >= 0)
		removeData(index);	
}

int PolarScan::getDirection()
{
	double rpm = this->getRPM(0);
	if (rpm)
	{
		return (rpm > 0 ? 1 : -1);
	}
	else
	{
		/* se il valore rpm non e' indicato bisogna calcolare la direzione in base ai tempi degli angoli) */
		/* supponiamo che sia oraria */
		int result = +1; 
		/* se i tempi non sono progessivi allora e' una scansione antioraria */
//		std::vector<AZTimes> times = this->getAzimuthTimes();
		std::vector<double> times = this->getStartAzimuthTimes();
		int count  = (int)times.size();
		if (count > 1)
		{
			for (int i=0; i<(count-1); i++)
//				if (times[i].start > times[i].start) {
				if (times[i] > times[i+1]) {
					result = -1;
					break;
				}
		}
		return result;
	}
}

int PolarScan::getQuantityDataIndex(const char* name)
{	
	int dataCount = getDataCount();
	for (int i=0; i<dataCount; i++)
	{
		PolarScanData* data = NULL;
		try
		{
			data = getQuantityData(i);
			if (data->getQuantity() == name)
			{
				delete data;
				return i;
			}
			delete data;
		}
		catch (...)
		{
			delete data;
			throw;
		}
	}
	return -1;
}

int PolarScan::getQuantityDataIndex(const std::string& name)
{
	return getQuantityDataIndex(name.c_str());
}

/*===========================================================================*/
/* POLAR SCAN DATA */
/*===========================================================================*/

PolarScanData::PolarScanData(PolarScan* scan, H5::Group* group)
:OdimData(group)
,WHATDatasetMetadata()
,scan(scan)
{
}
PolarScanData::~PolarScanData()
{
}

std::string		PolarScanData::getObject	()				{ return getWhat()->getStr	(ATTRIBUTE_WHAT_OBJECT, "");	}
void			PolarScanData::setObject	(const std::string& val) 	{        getWhat()->set		(ATTRIBUTE_WHAT_OBJECT, val);	}
std::string		PolarScanData::getVersion	() 				{ return getWhat()->getStr	(ATTRIBUTE_WHAT_VERSION, "");		}
void			PolarScanData::setVersion	(const std::string& val)	{        getWhat()->set		(ATTRIBUTE_WHAT_VERSION, val);	}
time_t			PolarScanData::getDateTime	()				{ return getWhatDateTime(this->getWhat());		}
void			PolarScanData::setDateTime	(const time_t val)		{	 setWhatDateTime(this->getWhat(), (int64_t)val);		}
SourceInfo		PolarScanData::getSource	() 				{ return SourceInfo(getWhat()->getStr(ATTRIBUTE_WHAT_SOURCE, ""));		}
void			PolarScanData::setSource	(const SourceInfo& val)		{        getWhat()->set		(ATTRIBUTE_WHAT_SOURCE, val.toString() );	}

std::string		PolarScanData::getProduct	()				{ return getWhat()->getStr	(ATTRIBUTE_WHAT_PRODUCT, "");		}
void			PolarScanData::setProduct	(const std::string& val)	{        getWhat()->set		(ATTRIBUTE_WHAT_PRODUCT, val);		}
double			PolarScanData::getProdPar	()				{  return getWhat()->getDouble	(ATTRIBUTE_WHAT_PRODPAR); 		}
VILHeights		PolarScanData::getProdParVIL	()				{ return getWhat()->getVILHeights(ATTRIBUTE_WHAT_PRODPAR); 	}
void			PolarScanData::setProdPar	(double val) 			{ return getWhat()->set	(ATTRIBUTE_WHAT_PRODPAR, val);		}
void			PolarScanData::setProdPar	(const VILHeights& val) 	{ return getWhat()->set	(ATTRIBUTE_WHAT_PRODPAR, val);		}
std::string		PolarScanData::getQuantity	() 				{ return getWhat()->getStr	(ATTRIBUTE_WHAT_QUANTITY);	}
void			PolarScanData::setQuantity	(const std::string& val)	{	 getWhat()->set		(ATTRIBUTE_WHAT_QUANTITY, val);	}
time_t			PolarScanData::getStartDateTime	()				{ return getWhatStartDateTime(this->getWhat()); }
void			PolarScanData::setStartDateTime	(time_t value)			{	 setWhatStartDateTime(this->getWhat(), (int64_t)value);	}
time_t			PolarScanData::getEndDateTime	()				{ return getWhatEndDateTime(this->getWhat()); }
void			PolarScanData::setEndDateTime	(time_t value)			{	 setWhatEndDateTime(this->getWhat(), (int64_t)value); }
double			PolarScanData::getGain		() 				{ return getWhat()->getDouble	(ATTRIBUTE_WHAT_GAIN);			}
void			PolarScanData::setGain		(double val)			{        getWhat()->set		(ATTRIBUTE_WHAT_GAIN, val);		}
double			PolarScanData::getOffset	() 				{ return getWhat()->getDouble	(ATTRIBUTE_WHAT_OFFSET);		}
void			PolarScanData::setOffset	(double val) 			{        getWhat()->set		(ATTRIBUTE_WHAT_OFFSET, val);	}
double			PolarScanData::getNodata	()				{ return getWhat()->getDouble	(ATTRIBUTE_WHAT_NODATA);		}
void			PolarScanData::setNodata	(double val) 			{        getWhat()->set		(ATTRIBUTE_WHAT_NODATA, val);	}
double			PolarScanData::getUndetect	()				{ return getWhat()->getDouble	(ATTRIBUTE_WHAT_UNDETECT);		}
void			PolarScanData::setUndetect	(double val) 			{        getWhat()->set		(ATTRIBUTE_WHAT_UNDETECT, val);	}

H5::AtomType PolarScanData::getBinType() 
{
	return this->getDataType();
}

int PolarScanData::getNumRays() 
{
	return this->getDataHeight();
}

int PolarScanData::getNumBins() 
{
	return this->getDataWidth();
}

void PolarScanData::readTranslatedData(RayMatrix<float>& matrix)
{
	H5::DataType	type	= this->getDataType();
	int		rays	= this->getNumRays();
	int		bins	= this->getNumBins();
	double		offset	= this->getOffset();
	double		gain	= this->getGain();

	matrix.resize(rays, bins);

	if (type == H5::PredType::NATIVE_UINT8)
	{
		RayMatrix<unsigned char> rawmatrix(rays, bins);
		readData(const_cast<unsigned char*>(rawmatrix.get()));
		for (int r=0; r<rays; r++)
			for (int b=0; b<bins; b++)
				matrix.elem(r,b) = (float)(((double)rawmatrix.elem(r,b)) * gain + offset);
	}
	else if (type == H5::PredType::NATIVE_UINT16)
	{
		RayMatrix<unsigned short> rawmatrix(rays, bins);
		readData(const_cast<unsigned short*>(rawmatrix.get()));
		for (int r=0; r<rays; r++)
			for (int b=0; b<bins; b++)
				matrix.elem(r,b) = (float)(((double)rawmatrix.elem(r,b)) * gain + offset);
	}
	else if (type == H5::PredType::NATIVE_FLOAT)
	{
		RayMatrix<float> rawmatrix(rays, bins);
		readData(const_cast<float*>(rawmatrix.get()));
		for (int r=0; r<rays; r++)
			for (int b=0; b<bins; b++)
				matrix.elem(r,b) = (float)(((double)rawmatrix.elem(r,b)) * gain + offset);
	}
}

void PolarScanData::readTranslatedData(RayMatrix<double>& matrix)
{
	H5::DataType	type	= this->getDataType();
	int		rays	= this->getNumRays();
	int		bins	= this->getNumBins();
	double		offset	= this->getOffset();
	double		gain	= this->getGain();

	matrix.resize(rays, bins);

	if (type == H5::PredType::NATIVE_UINT8)
	{
		RayMatrix<unsigned char> rawmatrix(rays, bins);
		readData(const_cast<unsigned char*>(rawmatrix.get()));
		for (int r=0; r<rays; r++)
			for (int b=0; b<bins; b++)
				matrix.elem(r,b) = ((double)rawmatrix.elem(r,b)) * gain + offset;
	}
	else if (type == H5::PredType::NATIVE_UINT16)
	{
		RayMatrix<unsigned short> rawmatrix(rays, bins);
		readData(const_cast<unsigned short*>(rawmatrix.get()));
		for (int r=0; r<rays; r++)
			for (int b=0; b<bins; b++)
				matrix.elem(r,b) = ((double)rawmatrix.elem(r,b)) * gain + offset;
	}
	else if (type == H5::PredType::NATIVE_FLOAT)
	{
		RayMatrix<float> rawmatrix(rays, bins);
		readData(const_cast<float*>(rawmatrix.get()));
		for (int r=0; r<rays; r++)
			for (int b=0; b<bins; b++)
				matrix.elem(r,b) = ((double)rawmatrix.elem(r,b)) * gain + offset;
	}
}

/*===========================================================================*/

/* converte la matrice src nella matrice dst traducendo i valori in base a gain e offset */
template <class SRCTYPE, class DSTTYPE> 
static void translate(RayMatrix<SRCTYPE>& src, RayMatrix<DSTTYPE>& dst, SRCTYPE offset, SRCTYPE gain)
{
	int rows = src.getRayCount();
	int cols = src.getBinCount();
	dst.resize(rows,cols);
	for (int i=0; i<rows; i++)
		for (int j=0; j<cols; j++)
			dst.elem(i,j) = (DSTTYPE)((src.elem(i,j) - offset) / gain);
}

void PolarScanData::writeAndTranslate(RayMatrix<float>& matrix, float offset, float gain, H5::DataType bintype)
{
	if (bintype == H5::PredType::NATIVE_INT8)
	{
		RayMatrix<char> matrix2;
		translate<float, char>(matrix, matrix2, offset, gain);	
		writeData(matrix2);
	}
	else if (bintype == H5::PredType::NATIVE_UINT8)
	{
		RayMatrix<unsigned char> matrix2;
		translate<float, unsigned char>(matrix, matrix2, offset, gain);	
		writeData(matrix2);
	}
	else if (bintype == H5::PredType::NATIVE_UINT16)
	{
		RayMatrix<unsigned short> matrix2;
		translate<float, unsigned short>(matrix, matrix2, offset, gain);	
		writeData(matrix2);
	}
	else if (bintype == H5::PredType::NATIVE_FLOAT)
	{
		RayMatrix<float> matrix2;
		translate<float, float>(matrix, matrix2, offset, gain);	
		writeData(matrix2);
	}
	else
	{
		throw OdimH5UnsupportedException("Unable to write and translate matrix values to the requested HDF5 bintype");
	}
}

void PolarScanData::writeAndTranslate(RayMatrix<double>& matrix, double offset, double gain, H5::DataType bintype)
{
	if (bintype == H5::PredType::NATIVE_INT8)
	{
		RayMatrix<char> matrix2;
		translate<double, char>(matrix, matrix2, offset, gain);	
		writeData(matrix2);
	}
	if (bintype == H5::PredType::NATIVE_UINT8)
	{
		RayMatrix<unsigned char> matrix2;
		translate<double, unsigned char>(matrix, matrix2, offset, gain);	
		writeData(matrix2);
	}
	else if (bintype == H5::PredType::NATIVE_UINT16)
	{
		RayMatrix<unsigned short> matrix2;
		translate<double, unsigned short>(matrix, matrix2, offset, gain);	
		writeData(matrix2);
	}
	else if (bintype == H5::PredType::NATIVE_FLOAT)
	{
		RayMatrix<float> matrix2;
		translate<double, float>(matrix, matrix2, offset, gain);	
		writeData(matrix2);
	}
	else
	{
		throw OdimH5UnsupportedException("Unable to write and translate matrix values to the requested HDF5 bintype");
	}

}

//########################################################  PPA #############################
/*===========================================================================*/
/* 2D-Object*/
/*===========================================================================*/

Object_2D::Object_2D(H5::H5File* file)
:OdimObject(file)
,HOWRootMetadata() 
{		
}	

Object_2D::~Object_2D()
{	
}

std::string	Object_2D::getTaskOrProdGen	() 				{ return getHow()->getStr	(ATTRIBUTE_HOW_TASK, "");		} 
void		Object_2D::setTaskOrProdGen	(const std::string& val)	{        getHow()->set		(ATTRIBUTE_HOW_TASK, val);	}
time_t		Object_2D::getStartEpochs	()				{ return getHow()->getTimeT	(ATTRIBUTE_HOW_STARTEPOCHS, 0);	}
void		Object_2D::setStartEpochs	(time_t val) 			{        getHow()->set		(ATTRIBUTE_HOW_STARTEPOCHS, (int64_t)val); }
time_t		Object_2D::getEndEpochs	()				{ return getHow()->getTimeT	(ATTRIBUTE_HOW_ENDEPOCHS, 0);	}
void		Object_2D::setEndEpochs	(time_t val)			{        getHow()->set		(ATTRIBUTE_HOW_ENDEPOCHS, (int64_t)val); }
std::string	Object_2D::getSystem		()				{ return getHow()->getStr	(ATTRIBUTE_HOW_SYSTEM, "");		}
void		Object_2D::setSystem		(const std::string& val)	{        getHow()->set		(ATTRIBUTE_HOW_SYSTEM, val);	}
std::string	Object_2D::getSoftware	()				{ return getHow()->getStr	(ATTRIBUTE_HOW_SOFTWARE, "");	}
void		Object_2D::setSoftware	(const std::string& val)	{        getHow()->set		(ATTRIBUTE_HOW_SOFTWARE, val);	}
std::string	Object_2D::getSoftwareVer	()				{ return getHow()->getStr	(ATTRIBUTE_HOW_SW_VERSION, "");	}
void		Object_2D::setSoftwareVer	(const std::string& val)	{        getHow()->set		(ATTRIBUTE_HOW_SW_VERSION, val); }
double		Object_2D::getZR_A		() 				{ return getHow()->getDouble	(ATTRIBUTE_HOW_ZR_A, 0);	}
void		Object_2D::setZR_A		(double val)			{        getHow()->set		(ATTRIBUTE_HOW_ZR_A, val);	}
double		Object_2D::getZR_B		()				{ return getHow()->getDouble	(ATTRIBUTE_HOW_ZR_B, 0);	}
void		Object_2D::setZR_B		(double val)			{        getHow()->set		(ATTRIBUTE_HOW_ZR_B, val);	}
double		Object_2D::getKR_A		()				{ return getHow()->getDouble	(ATTRIBUTE_HOW_KR_A, 0);	}
void		Object_2D::setKR_A		(double val)			{        getHow()->set		(ATTRIBUTE_HOW_KR_A, val);	}
double		Object_2D::getKR_B		()				{ return getHow()->getDouble	(ATTRIBUTE_HOW_KR_B, 0);	}
void		Object_2D::setKR_B		(double val)			{        getHow()->set		(ATTRIBUTE_HOW_KR_B, val);	}
bool		Object_2D::getSimulated	()				{ return getHow()->getBool	(ATTRIBUTE_HOW_SIMULATED, false); }
void		Object_2D::setSimulated	(bool val)			{        getHow()->set		(ATTRIBUTE_HOW_SIMULATED, val); }


void	Object_2D::setMandatoryInformations()
{			
	OdimObject::setMandatoryInformations();
//	setObject	(OdimH5v21::OBJECT_IMAGE);
	setVersion	(ModelVersion(2,1).toString());
	setDateTime	(Radar::timeutils::getUTC());
	setSource	(SourceInfo().setComment(""));
}

void	Object_2D::checkMandatoryInformations()
{
	OdimObject::checkMandatoryInformations();


	std::string version = this->getVersion();
	if (version != ModelVersion(2,1).toString())
		throw OdimH5FormatException("OdimH5 object version is not " + ModelVersion(2,1).toString());	

	time_t datetime = this->getDateTime();
	if (datetime == (time_t)-1)
		throw OdimH5FormatException("OdimH5 object date/time is not set");	
	
	SourceInfo source = this->getSource();
	if (source.toString().empty())
		throw OdimH5FormatException("OdimH5 object source is not set");	
}
/*-----------------------------------------------------------
--------------------------------------------*/

int	Object_2D::getProductCount() 
{
	return this->getDatasetCount();	
}
Product_2D* Object_2D::createProduct2D(const char *type ) 
{
	std::string std_type;
	std_type=type;
	return createProduct2D(  std_type);		
}
Product_2D* Object_2D::createProduct2D(const std::string& type ) 
{		
		if( type == PRODUCT_PPI   )  return createProductPPI();
		if( type == PRODUCT_CAPPI )  return createProductCAPPI();
		if( type == PRODUCT_PCAPPI)  return createProductPCAPPI();
		if( type == PRODUCT_ETOP  )  return createProductETOP();
		if( type == PRODUCT_MAX   )  return createProductMAX();
		if( type == PRODUCT_RR    )  return createProductRR();
		if( type == PRODUCT_VIL   )  return createProductVIL();
		if( type == PRODUCT_COMP  )  return createProductCOMP();
		if( type == PRODUCT_RHI   )  return createProductRHI();
		if( type == PRODUCT_XSEC  )  return createProductXSEC();
		if( type == PRODUCT_VSP   )  return createProductVSP();
		if( type == PRODUCT_HSP   )  return createProductHSP();
		throw OdimH5Exception("Product requested not supported");
}

Product_PPI* Object_2D::createProductPPI() 
{		
	H5::Group* 		prodGroup	= NULL;
	Product_PPI* 		prod		= NULL;
	try
	{		
		prodGroup	= createDatasetGroup();
		prod = new Product_PPI(this,prodGroup);
		prodGroup	= NULL;
		prod->setMandatoryInformations();
		return prod;
	}
	catch (...)
	{
		delete prod;
		delete prodGroup;
		throw;
	}	
}


Product_CAPPI* Object_2D::createProductCAPPI() 
{		
	H5::Group* 		prodGroup	= NULL;
	Product_CAPPI* 		prod		= NULL;
	try
	{		
		prodGroup	= createDatasetGroup();
		prod = new Product_CAPPI(this,prodGroup);
		prodGroup	= NULL;
		prod->setMandatoryInformations();
		return prod;
	}
	catch (...)
	{
		delete prod;
		delete prodGroup;
		throw;
	}	
}

Product_PCAPPI* Object_2D::createProductPCAPPI() 
{		
	H5::Group* 		prodGroup	= NULL;
	Product_PCAPPI* 		prod		= NULL;
	try
	{		
		prodGroup	= createDatasetGroup();
		prod = new Product_PCAPPI(this,prodGroup);
		prodGroup	= NULL;
		prod->setMandatoryInformations();
		return prod;
	}
	catch (...)
	{
		delete prod;
		delete prodGroup;
		throw;
	}	
}

Product_ETOP* Object_2D::createProductETOP() 
{		
	H5::Group* 		prodGroup	= NULL;
	Product_ETOP*		prod		= NULL;
	try
	{		
		prodGroup	= createDatasetGroup();
		prod = new Product_ETOP(this,prodGroup);
		prodGroup	= NULL;
		prod->setMandatoryInformations();
		return prod;
	}
	catch (...)
	{
		delete prod;
		delete prodGroup;
		throw;
	}	
}

Product_MAX* Object_2D::createProductMAX() 
{		
	H5::Group* 		prodGroup	= NULL;
	Product_MAX*		prod		= NULL;
	try
	{		
		prodGroup	= createDatasetGroup();
		prod = new Product_MAX(this,prodGroup);
		prodGroup	= NULL;
		prod->setMandatoryInformations();
		return prod;
	}
	catch (...)
	{
		delete prod;
		delete prodGroup;
		throw;
	}	
}
Product_RR* Object_2D::createProductRR() 
{		
	H5::Group* 		prodGroup	= NULL;
	Product_RR*		prod		= NULL;
	try
	{		
		prodGroup	= createDatasetGroup();
		prod = new Product_RR(this,prodGroup);
		prodGroup	= NULL;
		prod->setMandatoryInformations();
		return prod;
	}
	catch (...)
	{
		delete prod;
		delete prodGroup;
		throw;
	}	
}
Product_VIL* Object_2D::createProductVIL() 
{		
	H5::Group* 		prodGroup	= NULL;
	Product_VIL*		prod		= NULL;
	try
	{		
		prodGroup	= createDatasetGroup();
		prod = new Product_VIL(this,prodGroup);
		prodGroup	= NULL;
		prod->setMandatoryInformations();
		return prod;
	}
	catch (...)
	{
		delete prod;
		delete prodGroup;
		throw;
	}	
}
Product_LBM* Object_2D::createProductLBM() 
{		
	H5::Group* 		prodGroup	= NULL;
	Product_LBM* 		prod		= NULL;
	try
	{		
		prodGroup	= createDatasetGroup();
		prod = new Product_LBM(this,prodGroup);
		prodGroup	= NULL;
		prod->setMandatoryInformations();
		return prod;
	}
	catch (...)
	{
		delete prod;
		delete prodGroup;
		throw;
	}	
}


Product_COMP* Object_2D::createProductCOMP() 
{		
	H5::Group* 		prodGroup	= NULL;
	Product_COMP*		prod		= NULL;
	try
	{		
		prodGroup	= createDatasetGroup();
		prod = new Product_COMP(this,prodGroup);
		prodGroup	= NULL;
		prod->setMandatoryInformations();
		return prod;
	}
	catch (...)
	{
		delete prod;
		delete prodGroup;
		throw;
	}	
}
Product_RHI* Object_2D::createProductRHI() 
{		
	H5::Group* 		prodGroup	= NULL;
	Product_RHI*		prod		= NULL;
	try
	{		
		prodGroup	= createDatasetGroup();
		prod = new Product_RHI(this,prodGroup);
		prodGroup	= NULL;
		prod->setMandatoryInformations();
		return prod;
	}
	catch (...)
	{
		delete prod;
		delete prodGroup;
		throw;
	}	
}
Product_XSEC* Object_2D::createProductXSEC() 
{		
	H5::Group* 		prodGroup	= NULL;
	Product_XSEC*		prod		= NULL;
	try
	{		
		prodGroup	= createDatasetGroup();
		prod = new Product_XSEC(this,prodGroup);
		prodGroup	= NULL;
		prod->setMandatoryInformations();
		return prod;
	}
	catch (...)
	{
		delete prod;
		delete prodGroup;
		throw;
	}	
}
Product_VSP* Object_2D::createProductVSP() 
{		
	H5::Group* 		prodGroup	= NULL;
	Product_VSP*		prod		= NULL;
	try
	{		
		prodGroup	= createDatasetGroup();
		prod = new Product_VSP(this,prodGroup);
		prodGroup	= NULL;
		prod->setMandatoryInformations();
		return prod;
	}
	catch (...)
	{
		delete prod;
		delete prodGroup;
		throw;
	}	
}
Product_HSP* Object_2D::createProductHSP() 
{		
	H5::Group* 		prodGroup	= NULL;
	Product_HSP*		prod		= NULL;
	try
	{		
		prodGroup	= createDatasetGroup();
		prod = new Product_HSP(this,prodGroup);
		prodGroup	= NULL;
		prod->setMandatoryInformations();
		return prod;
	}
	catch (...)
	{
		delete prod;
		delete prodGroup;
		throw;
	}	
}

Product_2D* Object_2D::getProduct(int index) 
{
	H5::Group* h5group1 = NULL;
	H5::Group* h5group2 = NULL;
	try
	{
		h5group1 = getDatasetGroup(index);
		if (h5group1) {
			Product_2D prod(this, h5group1);
			std::string type= prod.getProduct();
			H5::Group* h5group2 = getDatasetGroup(index);
			if( type == PRODUCT_PPI   )  return new Product_PPI(this, h5group2);
			if( type == PRODUCT_CAPPI )  return new Product_CAPPI(this, h5group2);
			if( type == PRODUCT_PCAPPI)  return new Product_PCAPPI(this, h5group2);
			if( type == PRODUCT_ETOP  )  return new Product_ETOP(this, h5group2);
			if( type == PRODUCT_MAX   )  return new Product_MAX(this, h5group2);
			if( type == PRODUCT_RR    )  return new Product_RR(this, h5group2);
			if( type == PRODUCT_VIL   )  return new Product_VIL(this, h5group2);
			if( type == PRODUCT_LBM_ARPA   )  return new Product_LBM(this, h5group2);
			if( type == PRODUCT_COMP  )  return new Product_COMP(this, h5group2);
			if( type == PRODUCT_RHI   )  return new Product_RHI(this, h5group2);
			if( type == PRODUCT_XSEC  )  return new Product_XSEC(this, h5group2);
			if( type == PRODUCT_VSP   )  return new Product_VSP(this, h5group2);
			if( type == PRODUCT_HSP   )  return new Product_HSP(this, h5group2);
			delete h5group2;
			return NULL;
                } else {
			delete h5group1;
			return NULL;	
		}
	}
	catch (...)
	{
		delete h5group1;
		delete h5group2;
		throw;
	}
}

void Object_2D::removeProduct(int num)
{
	removeDataset(num);
}

std::vector<std::string> Object_2D::getProductsType()
{
	try
	{
		Product_2D * prod;
		int nprod = getProductCount();
		std::vector<std::string> result;
		for (size_t i=0; i<nprod; i++)
		{
    			prod = this->getProduct(i);
			std::string type  = prod->getProduct();
			result.push_back(type);

			delete prod;		
		}
		return result;
	}
	catch (...)
	{
		throw;
	}
}

std::vector<Product_2D*> Object_2D::getProducts()
{
	std::vector<Product_2D*> result;	
	try
	{
		int prodCount = this->getProductCount();
		for (int i=0; i<prodCount; i++)
		{
			try
			{
				result.push_back(this->getProduct(i));
			}
			catch (OdimH5Exception& e)
			{				
				throw OdimH5Exception("Error while checking product n. "+Radar::stringutils::toString(i)+": "+e.what()); 
			}			
		}

		return result;	
	}
	catch (...)
	{
		//cancelliamo i product aperti
		for (size_t i=0; i<result.size(); i++)
			delete result[i];
		throw;
	}
}
/*  std::vector<PolarScan*> PolarVolume::getScans(const char* quantity)
{
	std::vector<PolarScan*> result;	
	try
	{
		int scanCount = this->getScanCount();
		for (int i=0; i<scanCount; i++)
		{
			PolarScan*	scan = NULL;						
			try
			{
				scan = this->getScan(i);	
				if (scan->hasQuantityData(quantity))
					result.push_back(scan);
				else
					delete scan;
			}
			catch (OdimH5Exception& e)
			{				
				delete scan;
				throw OdimH5Exception("Error while checking scan n. "+Radar::stringutils::toString(i)+": "+e.what()); 
			}			
		}

		return result;	
	}
	catch (...)
	{
		//cancelliamo gli scan aperti
		for (size_t i=0; i<result.size(); i++)
			delete result[i];
		throw;
	}
}
 */
/*===========================================================================*/
/* Image Object*/
/*===========================================================================*/

HorizontalObject_2D::HorizontalObject_2D(H5::H5File* file)
:Object_2D(file)
,WHEREImageMetadata()
{		

}	
HorizontalObject_2D::~HorizontalObject_2D() {}
void	HorizontalObject_2D::setMandatoryInformations()
{			
	OdimObject::setMandatoryInformations();
	setObject	(OdimH5v21::OBJECT_IMAGE);
	setVersion	(ModelVersion(2,1).toString());
	setDateTime	(Radar::timeutils::getUTC());
	setSource	(SourceInfo().setComment(""));
}

void	HorizontalObject_2D::checkMandatoryInformations()
{
	OdimObject::checkMandatoryInformations();

	std::string version = this->getVersion();
	if (version != ModelVersion(2,1).toString())
		throw OdimH5FormatException("OdimH5 object version is not " + ModelVersion(2,1).toString());	

	time_t datetime = this->getDateTime();
	if (datetime == (time_t)-1)
		throw OdimH5FormatException("OdimH5 object date/time is not set");	
	
	SourceInfo source = this->getSource();
	if (source.toString().empty())
		throw OdimH5FormatException("OdimH5 object source is not set");	
}
/*-----------------------------------------------------------
----------------------------*/

std::string		HorizontalObject_2D::getProjectionArguments	(){ return getWhere()->getStr	(ATTRIBUTE_WHERE_PROJDEF);	}
void			HorizontalObject_2D::setProjectionArguments	(const std::string& val){   getWhere()->set (ATTRIBUTE_WHERE_PROJDEF, val);	}

int			HorizontalObject_2D::getXSize		(){ return getWhere()->getInt	(ATTRIBUTE_WHERE_XSIZE);	}
void			HorizontalObject_2D::setXSize		(int val){  getWhere()->set	(ATTRIBUTE_WHERE_XSIZE, val);   }
int			HorizontalObject_2D::getYSize		(){ return getWhere()->getInt	(ATTRIBUTE_WHERE_YSIZE);	} 
void			HorizontalObject_2D::setYSize		(int val){  getWhere()->set	(ATTRIBUTE_WHERE_YSIZE, val);   }
double			HorizontalObject_2D::getXScale		(){ return getWhere()->getDouble(ATTRIBUTE_WHERE_XSCALE);	} 
void			HorizontalObject_2D::setXScale		(double val){  getWhere()->set	(ATTRIBUTE_WHERE_XSCALE, val);  }
double			HorizontalObject_2D::getYScale		(){ return getWhere()->getDouble(ATTRIBUTE_WHERE_YSCALE);	} 
void			HorizontalObject_2D::setYScale		(double val){  getWhere()->set	(ATTRIBUTE_WHERE_YSCALE, val);  }

double			HorizontalObject_2D::getLL_Longitude		(){ return getWhere()->getDouble(ATTRIBUTE_WHERE_LL_LON);	} 
void			HorizontalObject_2D::setLL_Longitude		(double val){  getWhere()->set	(ATTRIBUTE_WHERE_LL_LON, val);  }
double			HorizontalObject_2D::getLL_Latitude		(){ return getWhere()->getDouble(ATTRIBUTE_WHERE_LL_LAT);	}
void			HorizontalObject_2D::setLL_Latitude		(double val){  getWhere()->set	(ATTRIBUTE_WHERE_LL_LAT, val);  }

double			HorizontalObject_2D::getUL_Longitude		(){ return getWhere()->getDouble(ATTRIBUTE_WHERE_UL_LON);	}
void			HorizontalObject_2D::setUL_Longitude		(double val){  getWhere()->set	(ATTRIBUTE_WHERE_UL_LON, val);  }
double			HorizontalObject_2D::getUL_Latitude		(){ return getWhere()->getDouble(ATTRIBUTE_WHERE_UL_LAT);	}
void			HorizontalObject_2D::setUL_Latitude		(double val){  getWhere()->set	(ATTRIBUTE_WHERE_UL_LAT, val);  }

double			HorizontalObject_2D::getUR_Longitude		(){ return getWhere()->getDouble(ATTRIBUTE_WHERE_UR_LON);	}
void			HorizontalObject_2D::setUR_Longitude		(double val){  getWhere()->set	(ATTRIBUTE_WHERE_UR_LON, val);  }
double			HorizontalObject_2D::getUR_Latitude		(){ return getWhere()->getDouble(ATTRIBUTE_WHERE_UR_LAT);	}
void			HorizontalObject_2D::setUR_Latitude		(double val){  getWhere()->set	(ATTRIBUTE_WHERE_UR_LAT, val);  }

double			HorizontalObject_2D::getLR_Longitude		(){ return getWhere()->getDouble(ATTRIBUTE_WHERE_LR_LON);	}
void			HorizontalObject_2D::setLR_Longitude		(double val){  getWhere()->set	(ATTRIBUTE_WHERE_LR_LON, val);  }		
double			HorizontalObject_2D::getLR_Latitude		(){ return getWhere()->getDouble(ATTRIBUTE_WHERE_LR_LAT);	}	
void			HorizontalObject_2D::setLR_Latitude	        (double val){  getWhere()->set	(ATTRIBUTE_WHERE_LR_LAT, val);  }		


/*===========================================================================*/
/* IMAGE Object*/
/*===========================================================================*/
ImageObject::ImageObject(H5::H5File* file)
:HorizontalObject_2D(file)
{		

}	
ImageObject::~ImageObject() {}
void	ImageObject::setMandatoryInformations()
{			
	OdimObject::setMandatoryInformations();
	setObject	(OdimH5v21::OBJECT_IMAGE);
	setVersion	(ModelVersion(2,1).toString());
	setDateTime	(Radar::timeutils::getUTC());
	setSource	(SourceInfo().setComment(""));
}

void	ImageObject::checkMandatoryInformations()
{
	OdimObject::checkMandatoryInformations();

	std::string object = this->getObject();
	if (object != OdimH5v21::OBJECT_IMAGE)
		throw OdimH5FormatException(std::string("OdimH5 object is not ") + OdimH5v21::OBJECT_IMAGE);	

	std::string version = this->getVersion();
	if (version != ModelVersion(2,1).toString())
		throw OdimH5FormatException("OdimH5 object version is not " + ModelVersion(2,1).toString());	

	time_t datetime = this->getDateTime();
	if (datetime == (time_t)-1)
		throw OdimH5FormatException("OdimH5 object date/time is not set");	
	
	SourceInfo source = this->getSource();
	if (source.toString().empty())
		throw OdimH5FormatException("OdimH5 object source is not set");	
}
/*-----------------------------------------------------------
----------------------------*/

/*===========================================================================*/
/* COMP Object*/
/*===========================================================================*/

CompObject::CompObject(H5::H5File* file)
:HorizontalObject_2D(file)
{		

}	

CompObject::~CompObject() {}

void	CompObject::setMandatoryInformations()
{			
	OdimObject::setMandatoryInformations();
	setObject	(OdimH5v21::OBJECT_COMP);
	setVersion	(ModelVersion(2,1).toString());
	setDateTime	(Radar::timeutils::getUTC());
	setSource	(SourceInfo().setComment(""));
}

void	CompObject::checkMandatoryInformations()
{
	OdimObject::checkMandatoryInformations();

	std::string object = this->getObject();
	if (object != OdimH5v21::OBJECT_COMP)
		throw OdimH5FormatException(std::string("OdimH5 object is not ") + OdimH5v21::OBJECT_COMP);	

	std::string version = this->getVersion();
	if (version != ModelVersion(2,1).toString())
		throw OdimH5FormatException("OdimH5 object version is not " + ModelVersion(2,1).toString());	

	time_t datetime = this->getDateTime();
	if (datetime == (time_t)-1)
		throw OdimH5FormatException("OdimH5 object date/time is not set");	
	
	SourceInfo source = this->getSource();
	if (source.toString().empty())
		throw OdimH5FormatException("OdimH5 object source is not set");	
}
/*-----------------------------------------------------------
----------------------------*/

/*===========================================================================*/
/* XSEC Object*/
/*===========================================================================*/

XsecObject::XsecObject(H5::H5File* file)
:Object_2D(file)
,WHEREXSECMetadata()
,WHERERhiMetadata()
,WHEREPanelMetadata()
{		

}
XsecObject::~XsecObject() {}
void	XsecObject::setMandatoryInformations()
{			
	OdimObject::setMandatoryInformations();
	setObject	(OdimH5v21::OBJECT_XSEC);
	setVersion	(ModelVersion(2,1).toString());
	setDateTime	(Radar::timeutils::getUTC());
	setSource	(SourceInfo().setComment(""));
}

void	XsecObject::checkMandatoryInformations()
{
	OdimObject::checkMandatoryInformations();

	std::string object = this->getObject();
	if (object != OdimH5v21::OBJECT_XSEC)
		throw OdimH5FormatException(std::string("OdimH5 object is not ") + OdimH5v21::OBJECT_XSEC);	

	std::string version = this->getVersion();
	if (version != ModelVersion(2,1).toString())
		throw OdimH5FormatException("OdimH5 object version is not " + ModelVersion(2,1).toString());	

	time_t datetime = this->getDateTime();
	if (datetime == (time_t)-1)
		throw OdimH5FormatException("OdimH5 object date/time is not set");	
	
	SourceInfo source = this->getSource();
	if (source.toString().empty())
		throw OdimH5FormatException("OdimH5 object source is not set");	
}
/*-----------------------------------------------------------
----------------------------*/
int			XsecObject::getXSize		(){ return getWhere()->getInt	(ATTRIBUTE_WHERE_XSIZE);	} 
void			XsecObject::setXSize		(int val){  getWhere()->set	(ATTRIBUTE_WHERE_XSIZE, val);   }
int			XsecObject::getYSize		(){ return getWhere()->getInt	(ATTRIBUTE_WHERE_YSIZE);	} 
void			XsecObject::setYSize		(int val){  getWhere()->set	(ATTRIBUTE_WHERE_YSIZE, val);   }
double			XsecObject::getXScale		(){ return getWhere()->getDouble(ATTRIBUTE_WHERE_XSCALE);	} 
void			XsecObject::setXScale		(double val){  getWhere()->set	(ATTRIBUTE_WHERE_XSCALE, val);  }
double			XsecObject::getYScale		(){ return getWhere()->getDouble(ATTRIBUTE_WHERE_YSCALE);	} 
void			XsecObject::setYScale		(double val){  getWhere()->set	(ATTRIBUTE_WHERE_YSCALE, val);  }
                        
double			XsecObject::getMinHeight 	(){ return getWhere()->getDouble(ATTRIBUTE_WHERE_MINHEIGHT);	} 
void			XsecObject::setMinHeight	(double val){  getWhere()->set	(ATTRIBUTE_WHERE_MINHEIGHT, val);  }
double			XsecObject::getMaxHeight 	(){ return getWhere()->getDouble(ATTRIBUTE_WHERE_MAXHEIGHT);	} 
void			XsecObject::setMaxHeight	(double val){  getWhere()->set	(ATTRIBUTE_WHERE_MAXHEIGHT, val);  }


double XsecObject::getRHILon		(){ return getWhere()->getDouble(ATTRIBUTE_WHERE_LON); };
void   XsecObject::setRHILon		(double val){  getWhere()->set	(ATTRIBUTE_WHERE_LON, val);  };
double XsecObject::getRHILat		(){ return getWhere()->getDouble(ATTRIBUTE_WHERE_LAT); };
void   XsecObject::setRHILat		(double val){  getWhere()->set	(ATTRIBUTE_WHERE_LAT, val);  };
double XsecObject::getAzimuthAngle		(){ return getWhere()->getDouble(ATTRIBUTE_WHERE_AZ_ANGLE); };
void   XsecObject::setAzimuthAngle		(double val){  getWhere()->set	(ATTRIBUTE_WHERE_AZ_ANGLE, val);  };
std::vector<Angles> XsecObject::getAngles	()  { return getWhere()->getAngles(ATTRIBUTE_HOW_ANGLES); }	;
void   XsecObject::setAngles (const std::vector<Angles>& val) {getWhere()->set(ATTRIBUTE_HOW_ANGLES, val, 5);	}
double XsecObject::getRange		(){ return getWhere()->getDouble(ATTRIBUTE_WHERE_RANGE); };
void   XsecObject::setRange		(double val){  getWhere()->set	(ATTRIBUTE_WHERE_RANGE, val);  };

double XsecObject::getStartLongitude	(){ return getWhere()->getDouble(ATTRIBUTE_WHERE_START_LON); };
void   XsecObject::setStartLongitude	(double val){  getWhere()->set	(ATTRIBUTE_WHERE_START_LON, val);  };
double XsecObject::getStartLatitude	(){ return getWhere()->getDouble(ATTRIBUTE_WHERE_START_LAT); };
void   XsecObject::setStartLatitude	(double val){  getWhere()->set	(ATTRIBUTE_WHERE_START_LAT, val);  };
double XsecObject::getStopLongitude	(){ return getWhere()->getDouble(ATTRIBUTE_WHERE_STOP_LON); };
void   XsecObject::setStopLongitude	(double val){  getWhere()->set	(ATTRIBUTE_WHERE_STOP_LON, val);  };
double XsecObject::getStopLatitude	(){ return getWhere()->getDouble(ATTRIBUTE_WHERE_STOP_LAT); };
void   XsecObject::setStopLatitude	(double val){  getWhere()->set	(ATTRIBUTE_WHERE_STOP_LAT, val);  };


/*===========================================================================*/
/* 2D_PRODUCT Dataset  */
/*===========================================================================*/

Product_2D::Product_2D(Object_2D* object_2d, H5::Group* group)
:OdimDataset(group)
,WHATDatasetMetadata()
,HOWPolarMetadata()
,object_2d(object_2d)
{			
}

Product_2D::~Product_2D()
{		
}


void Product_2D::setMandatoryInformations()
{
// Lascio il metodo vuoto per il momento -- PPA 2013-03-05		
//	setProduct(OdimH5v21::PRODUCT_SCAN);		
}


//--- WHAT ROOT ---

std::string	Product_2D::getObject		()				{ return getWhat()->getStr	(ATTRIBUTE_WHAT_OBJECT);	}
void		Product_2D::setObject		(const std::string& val) 	{        getWhat()->set		(ATTRIBUTE_WHAT_OBJECT, val);	}
std::string	Product_2D::getVersion		() 				{ return getWhat()->getStr	(ATTRIBUTE_WHAT_VERSION);		}
void		Product_2D::setVersion		(const std::string& val)	{        getWhat()->set		(ATTRIBUTE_WHAT_VERSION, val);	}
time_t		Product_2D::getDateTime		()				{ return getWhatDateTime(this->getWhat()); }
void		Product_2D::setDateTime		(const time_t val)		{	 setWhatDateTime(this->getWhat(), val); }
SourceInfo	Product_2D::getSource		() 				{ return SourceInfo(getWhat()->getStr(ATTRIBUTE_WHAT_SOURCE));		}
void		Product_2D::setSource		(const SourceInfo& val)		{        getWhat()->set		(ATTRIBUTE_WHAT_SOURCE, val.toString() );	}

// --- HOW ROOT ---
std::string	Product_2D::getTaskOrProdGen	() 				{ return getHow()->getStr	(ATTRIBUTE_HOW_TASK, "");		} 
void		Product_2D::setTaskOrProdGen	(const std::string& val)	{        getHow()->set		(ATTRIBUTE_HOW_TASK, val);	}
time_t		Product_2D::getStartEpochs	()				{ return getHow()->getTimeT	(ATTRIBUTE_HOW_STARTEPOCHS, 0);	}
void		Product_2D::setStartEpochs	(time_t val) 			{        getHow()->set		(ATTRIBUTE_HOW_STARTEPOCHS, (int64_t)val); }
time_t		Product_2D::getEndEpochs	()				{ return getHow()->getTimeT	(ATTRIBUTE_HOW_ENDEPOCHS, 0);	}
void		Product_2D::setEndEpochs	(time_t val)			{        getHow()->set		(ATTRIBUTE_HOW_ENDEPOCHS, (int64_t)val); }
std::string	Product_2D::getSystem		()				{ return getHow()->getStr	(ATTRIBUTE_HOW_SYSTEM, "");		}
void		Product_2D::setSystem		(const std::string& val)	{        getHow()->set		(ATTRIBUTE_HOW_SYSTEM, val);	}
std::string	Product_2D::getSoftware	()				{ return getHow()->getStr	(ATTRIBUTE_HOW_SOFTWARE, "");	}
void		Product_2D::setSoftware	(const std::string& val)	{        getHow()->set		(ATTRIBUTE_HOW_SOFTWARE, val);	}
std::string	Product_2D::getSoftwareVer	()				{ return getHow()->getStr	(ATTRIBUTE_HOW_SW_VERSION, "");	}
void		Product_2D::setSoftwareVer	(const std::string& val)	{        getHow()->set		(ATTRIBUTE_HOW_SW_VERSION, val); }
double		Product_2D::getZR_A		() 				{ return getHow()->getDouble	(ATTRIBUTE_HOW_ZR_A, 0);	}
void		Product_2D::setZR_A		(double val)			{        getHow()->set		(ATTRIBUTE_HOW_ZR_A, val);	}
double		Product_2D::getZR_B		()				{ return getHow()->getDouble	(ATTRIBUTE_HOW_ZR_B, 0);	}
void		Product_2D::setZR_B		(double val)			{        getHow()->set		(ATTRIBUTE_HOW_ZR_B, val);	}
double		Product_2D::getKR_A		()				{ return getHow()->getDouble	(ATTRIBUTE_HOW_KR_A, 0);	}
void		Product_2D::setKR_A		(double val)			{        getHow()->set		(ATTRIBUTE_HOW_KR_A, val);	}
double		Product_2D::getKR_B		()				{ return getHow()->getDouble	(ATTRIBUTE_HOW_KR_B, 0);	}
void		Product_2D::setKR_B		(double val)			{        getHow()->set		(ATTRIBUTE_HOW_KR_B, val);	}
bool		Product_2D::getSimulated	()				{ return getHow()->getBool	(ATTRIBUTE_HOW_SIMULATED, false); }
void		Product_2D::setSimulated	(bool val)			{        getHow()->set		(ATTRIBUTE_HOW_SIMULATED, val); }
//--- WHAT DATASET---

std::string		Product_2D::getProduct		()				{ return getWhat()->getStr	(ATTRIBUTE_WHAT_PRODUCT);	}
void			Product_2D::setProduct		(const std::string& val)	{        getWhat()->set		(ATTRIBUTE_WHAT_PRODUCT, val);	}	
double			Product_2D::getProdPar		()				{  return getWhat()->getDouble	(ATTRIBUTE_WHAT_PRODPAR);	}
VILHeights		Product_2D::getProdParVIL	()				{ return getWhat()->getVILHeights(ATTRIBUTE_WHAT_PRODPAR); 	}
void			Product_2D::setProdPar		(double val) 			{ return getWhat()->set	(ATTRIBUTE_WHAT_PRODPAR, val);		}
void			Product_2D::setProdPar		(const VILHeights& val)		{ return getWhat()->set	(ATTRIBUTE_WHAT_PRODPAR, val);		}
std::string		Product_2D::getQuantity		() 				{ return getWhat()->getStr	(ATTRIBUTE_WHAT_QUANTITY);	}
void			Product_2D::setQuantity		(const std::string& val)	{        getWhat()->set		(ATTRIBUTE_WHAT_QUANTITY, val);	}
time_t			Product_2D::getStartDateTime	()				{ return getWhatStartDateTime(this->getWhat());			}
void			Product_2D::setStartDateTime	(time_t value)			{	 setWhatStartDateTime(this->getWhat(), value);		}
time_t			Product_2D::getEndDateTime	()				{ return getWhatEndDateTime(this->getWhat());			}
void			Product_2D::setEndDateTime	(time_t value)			{	 setWhatEndDateTime(this->getWhat(), value);		}
double			Product_2D::getGain		() 				{ return getWhat()->getDouble	(ATTRIBUTE_WHAT_GAIN);			}
void			Product_2D::setGain		(double val)			{        getWhat()->set		(ATTRIBUTE_WHAT_GAIN, val);		}
double			Product_2D::getOffset		() 				{ return getWhat()->getDouble	(ATTRIBUTE_WHAT_OFFSET);		}
void			Product_2D::setOffset		(double val) 			{        getWhat()->set		(ATTRIBUTE_WHAT_OFFSET, val);	}
double			Product_2D::getNodata		()				{ return getWhat()->getDouble	(ATTRIBUTE_WHAT_NODATA);		}
void			Product_2D::setNodata		(double val) 			{        getWhat()->set		(ATTRIBUTE_WHAT_NODATA, val);	}
double			Product_2D::getUndetect		()				{ return getWhat()->getDouble	(ATTRIBUTE_WHAT_UNDETECT);		}
void			Product_2D::setUndetect		(double val) 			{        getWhat()->set		(ATTRIBUTE_WHAT_UNDETECT, val);	}

std::string		Product_2D::getAzimuthMethod	()					{ return getHow()->getStr	(ATTRIBUTE_HOW_AZMETHOD, "");	}
void			Product_2D::setAzimuthMethod	(const std::string& val)		{        getHow()->set		(ATTRIBUTE_HOW_AZMETHOD, val);	}
std::string		Product_2D::getBinMethod		()					{ return getHow()->getStr	(ATTRIBUTE_HOW_BINMETHOD, "");	}
void			Product_2D::setBinMethod		(const std::string& val)		{        getHow()->set		(ATTRIBUTE_HOW_BINMETHOD, val);	}


std::vector<double>	Product_2D::getElevationAngles	() 					
{ 
	try
	{
		int			numrays = 1; //this->getNumRays();
		std::vector<double>	result	= getHow()->getDoubles(ATTRIBUTE_HOW_ELANGLES);		

		/* se il numero di elementi corrisponde */
		if (result.size() == numrays)	
			return result;

		double			elangle = 10;//this->getEAngle();

		/* se l'attributo non aveva nessun valore */
		if (result.size() == 0)
		{	
			result.resize(numrays);
			for (int i=0; i<numrays; i++)
				result[i] = elangle;
			return result;
		}	

		/* se il numero di elementi non corrisponde c'e' qauclacosa che non va*/
		std::ostringstream ss;
		ss << "elangles values ("<<result.size()<<") are not as many as numrays ("<<numrays<<")";
		throw OdimH5FormatException(ss.str());
	}
	catch (std::exception& e)
	{
		throw OdimH5Exception(std::string("Error getting elangles: ") + e.what());
	}
}
void			Product_2D::setElevationAngles	(const std::vector<double>& val)	{        getHow()->set		(ATTRIBUTE_HOW_ELANGLES, val, 5);	}
std::vector<double>	Product_2D::getStartAzimuthAngles	()				 
{ 
	try
	{
		int			numrays = 1;//= this->getNumRays();
		std::vector<double>	result	;  //  = getHow()->getDoubles(ATTRIBUTE_HOW_ELANGLES);	
	        return result;
		std::ostringstream ss;
		ss << "elangles values ("<<result.size()<<") are not as many as numrays ("<<numrays<<")";
		throw OdimH5FormatException(ss.str());
	}
	catch (std::exception& e)
	{
		throw OdimH5Exception(std::string("Error getting elangles: ") + e.what());
	}
}
void			Product_2D::setStartAzimuthAngles	(const std::vector<double>& val) {} 
std::vector<double>	Product_2D::getStopAzimuthAngles	()				 
{ 
	try
	{
		int			numrays = 1;//this->getNumRays();
		std::vector<double>	result	;  //  = getHow()->getDoubles(ATTRIBUTE_HOW_ELANGLES);	
	        return result;
		std::ostringstream ss;
		ss << "elangles values ("<<result.size()<<") are not as many as numrays ("<<numrays<<")";
		throw OdimH5FormatException(ss.str());
	}
	catch (std::exception& e)
	{
		throw OdimH5Exception(std::string("Error getting elangles: ") + e.what());
	}
}
void			Product_2D::setStopAzimuthAngles	(const std::vector<double>& val) {}
std::vector<double>	Product_2D::getStartAzimuthTimes	()				 
{ 
	try
	{
		int			numrays = 1;//this->getNumRays();
		std::vector<double>	result	;  //  = getHow()->getDoubles(ATTRIBUTE_HOW_ELANGLES);	
	        return result;
		std::ostringstream ss;
		ss << "elangles values ("<<result.size()<<") are not as many as numrays ("<<numrays<<")";
		throw OdimH5FormatException(ss.str());
	}
	catch (std::exception& e)
	{
		throw OdimH5Exception(std::string("Error getting elangles: ") + e.what());
	}
}
void			Product_2D::setStartAzimuthTimes	(const std::vector<double>& val) {}
std::vector<double>	Product_2D::getStopAzimuthTimes	()				 
{ 
	try
	{
		int			numrays = 1;//this->getNumRays();
		std::vector<double>	result	;  //  = getHow()->getDoubles(ATTRIBUTE_HOW_ELANGLES);	
	        return result;
		std::ostringstream ss;
		ss << "elangles values ("<<result.size()<<") are not as many as numrays ("<<numrays<<")";
		throw OdimH5FormatException(ss.str());
	}
	catch (std::exception& e)
	{
		throw OdimH5Exception(std::string("Error getting elangles: ") + e.what());
	}
}
void			Product_2D::setStopAzimuthTimes	(const std::vector<double>& val) {}

double		Product_2D::getPointAccEl	()				{ return getHow()->getDouble	(ATTRIBUTE_HOW_POINTACCEL, 0);		}
void		Product_2D::setPointAccEl	(double val)			{        getHow()->set		(ATTRIBUTE_HOW_POINTACCEL, val);	}
double		Product_2D::getPointAccAZ	()				{ return getHow()->getDouble	(ATTRIBUTE_HOW_POINTACCAZ, 0);		} 
void		Product_2D::setPointAccAZ	(double val)			{        getHow()->set		(ATTRIBUTE_HOW_POINTACCAZ, val);	}
bool		Product_2D::getMalfunc		()				{ return getHow()->getBool	(ATTRIBUTE_HOW_MALFUNC, false);		}
void		Product_2D::setMalfunc		(bool val)			{        getHow()->set		(ATTRIBUTE_HOW_MALFUNC, val);		}
std::string	Product_2D::getRadarMsg		()				{ return getHow()->getStr	(ATTRIBUTE_HOW_RADAR_MSG, "");		}
void		Product_2D::setRadarMsg		(const std::string& val)	{        getHow()->set		(ATTRIBUTE_HOW_RADAR_MSG, val);		}
double		Product_2D::getRadarHorizon	()				{ return getHow()->getDouble	(ATTRIBUTE_HOW_RADHORIZ, 0);		}
void		Product_2D::setRadarHorizon	(double val)			{        getHow()->set		(ATTRIBUTE_HOW_RADHORIZ, val);		}
double		Product_2D::getNEZ		()				{ return getHow()->getDouble	(ATTRIBUTE_HOW_NEZ, 0);			}
void		Product_2D::setNEZ		(double val)			{        getHow()->set		(ATTRIBUTE_HOW_NEZ, val);		}
double		Product_2D::getOUR		()				{ return getHow()->getDouble	(ATTRIBUTE_HOW_OUR, 0);			}
void		Product_2D::setOUR		(double val)			{        getHow()->set		(ATTRIBUTE_HOW_OUR, val);		}
std::vector<std::string> Product_2D::getDClutter	()				{ return getHow()->getStrings	(ATTRIBUTE_HOW_DCLUTTER);		}
void		Product_2D::setDClutter		(const std::vector<std::string>& vals) { getHow()->set		(ATTRIBUTE_HOW_DCLUTTER, vals);	}
std::string	Product_2D::getComment		()				{ return getHow()->getStr	(ATTRIBUTE_HOW_COMMENT, "");		}
void		Product_2D::setComment		(const std::string& val)	{        getHow()->set		(ATTRIBUTE_HOW_COMMENT, val);		}
double		Product_2D::getSQI		()				{ return getHow()->getDouble	(ATTRIBUTE_HOW_SQI, 0);			}
void		Product_2D::setSQI		(double val)			{        getHow()->set		(ATTRIBUTE_HOW_SQI, val);		}
double		Product_2D::getCSR		()				{ return getHow()->getDouble	(ATTRIBUTE_HOW_CSR, 0);			}
void		Product_2D::setCSR		(double val)			{        getHow()->set		(ATTRIBUTE_HOW_CSR, val);		}
double		Product_2D::getLOG		()				{ return getHow()->getDouble	(ATTRIBUTE_HOW_LOG, 0);			}
void		Product_2D::setLOG		(double val)			{        getHow()->set		(ATTRIBUTE_HOW_LOG, val);		}
bool		Product_2D::getVPRCorr		()				{ return getHow()->getBool	(ATTRIBUTE_HOW_VPRCORR, false);		}
void		Product_2D::setVPRCorr		(bool val)			{        getHow()->set		(ATTRIBUTE_HOW_VPRCORR, val);		}
double		Product_2D::getFreeze		()				{ return getHow()->getDouble	(ATTRIBUTE_HOW_FREEZE, 0);		}
void		Product_2D::setFreeze		(double val)			{        getHow()->set		(ATTRIBUTE_HOW_FREEZE, val);		}
double		Product_2D::getMin		()				{ return getHow()->getDouble	(ATTRIBUTE_HOW_MIN, 0);			}
void		Product_2D::setMin		(double val)			{        getHow()->set		(ATTRIBUTE_HOW_MIN, val);		}
double		Product_2D::getMax		()				{ return getHow()->getDouble	(ATTRIBUTE_HOW_MAX, 0);			}
void		Product_2D::setMax		(double val)			{        getHow()->set		(ATTRIBUTE_HOW_MAX, val);		}
double		Product_2D::getStep		()				{ return getHow()->getDouble	(ATTRIBUTE_HOW_STEP, 0);		}
void		Product_2D::setStep		(double val)			{        getHow()->set		(ATTRIBUTE_HOW_STEP, val);		}
int		Product_2D::getLevels		()				{ return getHow()->getInt	(ATTRIBUTE_HOW_LEVELS, 0);		}
void		Product_2D::setLevels		(int val)			{        getHow()->set		(ATTRIBUTE_HOW_LEVELS, val);		}
double		Product_2D::getPeakPwr		()				{ return getHow()->getDouble	(ATTRIBUTE_HOW_PEAKPWR, 0);		}
void		Product_2D::setPeakPwr		(double val)			{        getHow()->set		(ATTRIBUTE_HOW_PEAKPWR, val);		}
double		Product_2D::getAvgPwr		()				{ return getHow()->getDouble	(ATTRIBUTE_HOW_AVGPWR, 0);		}
void		Product_2D::setAvgPwr		(double val)			{        getHow()->set		(ATTRIBUTE_HOW_AVGPWR, val);		}
double		Product_2D::getDynRange		()				{ return getHow()->getDouble	(ATTRIBUTE_HOW_DYNRANGE, 0);		}
void		Product_2D::setDynRange		(double val)			{        getHow()->set		(ATTRIBUTE_HOW_DYNRANGE, val);		}
double		Product_2D::getRAC		()				{ return getHow()->getDouble	(ATTRIBUTE_HOW_RAC, 0);			}
void		Product_2D::setRAC		(double val)			{        getHow()->set		(ATTRIBUTE_HOW_RAC, val);		}
bool		Product_2D::getBBC		()				{ return getHow()->getBool	(ATTRIBUTE_HOW_BBC, 0);			}
void		Product_2D::setBBC		(bool val)			{        getHow()->set		(ATTRIBUTE_HOW_BBC, val);		}
double		Product_2D::getPAC		()				{ return getHow()->getDouble	(ATTRIBUTE_HOW_PAC, 0);			}
void		Product_2D::setPAC		(double val)			{        getHow()->set		(ATTRIBUTE_HOW_PAC, val);		}
double		Product_2D::getS2N		()				{ return getHow()->getDouble	(ATTRIBUTE_HOW_S2N, 0);			}
void		Product_2D::setS2N		(double val)			{        getHow()->set		(ATTRIBUTE_HOW_S2N, val);		}
std::string	Product_2D::getPolarization	()				{ return getHow()->getStr	(ATTRIBUTE_HOW_POLARIZATION, "");	}
void		Product_2D::setPolarization	(const std::string& val)	{        getHow()->set		(ATTRIBUTE_HOW_POLARIZATION, val);	}
//--- HOW DATASET ---

double		Product_2D::getBeamWidth		()				{ return getHow()->getDouble	(ATTRIBUTE_HOW_BEAMWIDTH, 0);			}
double		Product_2D::getBeamWidth		(double defaultValue)		{ return getHow()->getDouble	(ATTRIBUTE_HOW_BEAMWIDTH, defaultValue);	}
void		Product_2D::setBeamWidth		(double val)			{        getHow()->set		(ATTRIBUTE_HOW_BEAMWIDTH, val);			}
double		Product_2D::getWaveLength	()				{ return getHow()->getDouble	(ATTRIBUTE_HOW_WAVELENGTH, 0);			}
double		Product_2D::getWaveLength	(double defaultValue)		{ return getHow()->getDouble	(ATTRIBUTE_HOW_WAVELENGTH, defaultValue);	}
void		Product_2D::setWaveLength	(double val)			{        getHow()->set		(ATTRIBUTE_HOW_WAVELENGTH, val);		}
double		Product_2D::getRPM		()				{ return getHow()->getDouble	(ATTRIBUTE_HOW_RPM, 0);				}
double		Product_2D::getRPM		(double defaultValue)		{ return getHow()->getDouble	(ATTRIBUTE_HOW_RPM, defaultValue);		}
void		Product_2D::setRPM		(double val)			{        getHow()->set		(ATTRIBUTE_HOW_RPM, val);			}
double		Product_2D::getPulseWidth	()				{ return getHow()->getDouble	(ATTRIBUTE_HOW_PULSEWIDTH, 0);			}
double		Product_2D::getPulseWidth	(double defaultValue)		{ return getHow()->getDouble	(ATTRIBUTE_HOW_PULSEWIDTH, defaultValue);	}
void		Product_2D::setPulseWidth	(double val)			{        getHow()->set		(ATTRIBUTE_HOW_PULSEWIDTH, val);		}
double		Product_2D::getRXBandWidth	()				{ return getHow()->getDouble	(ATTRIBUTE_HOW_RXBANDWIDTH, 0);			}
double		Product_2D::getRXBandWidth	(double defaultValue)		{ return getHow()->getDouble	(ATTRIBUTE_HOW_RXBANDWIDTH, defaultValue);	}
void		Product_2D::setRXBandWidth	(double val)			{        getHow()->set		(ATTRIBUTE_HOW_RXBANDWIDTH, val);		}
int		Product_2D::getLowPRF		()				{ return getHow()->getInt	(ATTRIBUTE_HOW_LOWPRF, 0);			}
int		Product_2D::getLowPRF		(int defaultValue)		{ return getHow()->getInt	(ATTRIBUTE_HOW_LOWPRF, defaultValue);		}
void		Product_2D::setLowPRF		(int val)			{        getHow()->set		(ATTRIBUTE_HOW_LOWPRF, val);			}
int		Product_2D::getHighPRF		()				{ return getHow()->getInt	(ATTRIBUTE_HOW_HIGHPRF, 0);			}
int		Product_2D::getHighPRF		(int defaultValue)		{ return getHow()->getInt	(ATTRIBUTE_HOW_HIGHPRF, defaultValue);		}
void		Product_2D::setHighPRF		(int val)			{        getHow()->set		(ATTRIBUTE_HOW_HIGHPRF, val);			}

double		Product_2D::getTXLoss		()		    		{ return getHow()->getDouble	(ATTRIBUTE_HOW_TXLOSS, 0);			}
double		Product_2D::getTXLoss		(double defaultValue)		{ return getHow()->getDouble	(ATTRIBUTE_HOW_TXLOSS, defaultValue);	}
void		Product_2D::setTXLoss		(double val)	     		{        getHow()->set		(ATTRIBUTE_HOW_TXLOSS, val);		}
double		Product_2D::getRXLoss		()		     		{ return getHow()->getDouble	(ATTRIBUTE_HOW_RXLOSS, 0);			}
double		Product_2D::getRXLoss		(double defaultValue)		{ return getHow()->getDouble	(ATTRIBUTE_HOW_RXLOSS, defaultValue);	}
void		Product_2D::setRXLoss		(double val)	     		{        getHow()->set		(ATTRIBUTE_HOW_RXLOSS, val);		}
double		Product_2D::getRadomeLoss	()				{ return getHow()->getDouble	(ATTRIBUTE_HOW_RADOMELOSS, 0);			}     
double		Product_2D::getRadomeLoss	(double defaultValue)		{ return getHow()->getDouble	(ATTRIBUTE_HOW_RADOMELOSS, defaultValue);	}
void		Product_2D::setRadomeLoss	(double val)	     		{        getHow()->set		(ATTRIBUTE_HOW_RADOMELOSS, val);		}
double		Product_2D::getAntGain		()		     		{ return getHow()->getDouble	(ATTRIBUTE_HOW_ANTGAIN, 0);			}
double		Product_2D::getAntGain		(double defaultValue)		{ return getHow()->getDouble	(ATTRIBUTE_HOW_ANTGAIN, defaultValue);	}
void		Product_2D::setAntGain		(double val)	     		{        getHow()->set		(ATTRIBUTE_HOW_ANTGAIN, val);		}
double		Product_2D::getBeamWH		()		     		{ return getHow()->getDouble	(ATTRIBUTE_HOW_BEAMWH, 0);			}
double		Product_2D::getBeamWH		(double defaultValue)		{ return getHow()->getDouble	(ATTRIBUTE_HOW_BEAMWH, defaultValue);	}
void		Product_2D::setBeamWH		(double val)	     		{        getHow()->set		(ATTRIBUTE_HOW_BEAMWH, val);		}
double		Product_2D::getBeamWV		()		     		{ return getHow()->getDouble	(ATTRIBUTE_HOW_BEAMWV, 0);			}
double		Product_2D::getBeamWV		(double defaultValue)		{ return getHow()->getDouble	(ATTRIBUTE_HOW_BEAMWV, defaultValue);	}
void		Product_2D::setBeamWV		(double val)	     		{        getHow()->set		(ATTRIBUTE_HOW_BEAMWV, val);		}
double		Product_2D::getGasAttn		()		     		{ return getHow()->getDouble	(ATTRIBUTE_HOW_GASATTN, 0);			}
double		Product_2D::getGasAttn		(double defaultValue)		{ return getHow()->getDouble	(ATTRIBUTE_HOW_GASATTN, defaultValue);	}
void		Product_2D::setGasAttn		(double val)	     		{        getHow()->set		(ATTRIBUTE_HOW_GASATTN, val);		}
double		Product_2D::getRadConstH		()		     		{ return getHow()->getDouble	(ATTRIBUTE_HOW_RADCONSTH, 0);			}
double		Product_2D::getRadConstH		(double defaultValue)		{ return getHow()->getDouble	(ATTRIBUTE_HOW_RADCONSTH, defaultValue);	}
void		Product_2D::setRadConstH		(double val)	     		{        getHow()->set		(ATTRIBUTE_HOW_RADCONSTH, val);		}
double		Product_2D::getRadConstV		()		     		{ return getHow()->getDouble	(ATTRIBUTE_HOW_RADCONSTV, 0);			}
double		Product_2D::getRadConstV		(double defaultValue)		{ return getHow()->getDouble	(ATTRIBUTE_HOW_RADCONSTV, defaultValue);	}
void		Product_2D::setRadConstV		(double val)	     		{        getHow()->set		(ATTRIBUTE_HOW_RADCONSTV, val);		}
double		Product_2D::getNomTXPower	()		     		{ return getHow()->getDouble	(ATTRIBUTE_HOW_NOMTXPOWER, 0);			}
double		Product_2D::getNomTXPower	(double defaultValue)		{ return getHow()->getDouble	(ATTRIBUTE_HOW_NOMTXPOWER, defaultValue);	}
void		Product_2D::setNomTXPower	(double val)	     		{        getHow()->set		(ATTRIBUTE_HOW_NOMTXPOWER, val);		}
std::vector<double>	Product_2D::getTXPower		()		        
{ 
	try
	{
		int			numrays = 1;//this->getNumRays();
		std::vector<double>	result	;  //  = getHow()->getDoubles(ATTRIBUTE_HOW_ELANGLES);	
	        return result;
		std::ostringstream ss;
		ss << "elangles values ("<<result.size()<<") are not as many as numrays ("<<numrays<<")";
		throw OdimH5FormatException(ss.str());
	}
	catch (std::exception& e)
	{
		throw OdimH5Exception(std::string("Error getting elangles: ") + e.what());
	}
}
		
std::vector<double>	Product_2D::getTXPower		(double defaultValue)
{ 
	try
	{
		int			numrays = 1;//this->getNumRays();
		std::vector<double>	result	;  //  = getHow()->getDoubles(ATTRIBUTE_HOW_ELANGLES);	
	        return result;
		std::ostringstream ss;
		ss << "elangles values ("<<result.size()<<") are not as many as numrays ("<<numrays<<")";
		throw OdimH5FormatException(ss.str());
	}
	catch (std::exception& e)
	{
		throw OdimH5Exception(std::string("Error getting elangles: ") + e.what());
	}
}
void		Product_2D::setTXPower		(double val)	   {;}  
// (const std::vector<double>& val, int precision)	{        getHow()->set		(ATTRIBUTE_HOW_ELANGLES, val, precision);	}

double		Product_2D::getNI		()		     		{ return getHow()->getDouble	(ATTRIBUTE_HOW_NI, 0);			}
double		Product_2D::getNI		(double defaultValue)		{ return getHow()->getDouble	(ATTRIBUTE_HOW_NI, defaultValue);	}
void		Product_2D::setNI		(double val)	     		{        getHow()->set		(ATTRIBUTE_HOW_NI, val);		}
double		Product_2D::getVSamples		()		     		{ return getHow()->getDouble	(ATTRIBUTE_HOW_VSAMPLES, 0);			}
double		Product_2D::getVSamples		(double defaultValue)		{ return getHow()->getDouble	(ATTRIBUTE_HOW_VSAMPLES, defaultValue);	}
void		Product_2D::setVSamples		(double val)			{        getHow()->set		(ATTRIBUTE_HOW_VSAMPLES, val);		}

//--- METODI ---



Product_2D_Data*	Product_2D::createQuantityData(const std::string& name)
{
	return createQuantityData(name.c_str()) ;
}

Product_2D_Data*	Product_2D::createQuantityData(const char* name) 
{

	H5::Group*	dataGroup	= NULL;
	Product_2D_Data*	result		= NULL;
	try
	{
		dataGroup	= createDataGroup();
		result		= new Product_2D_Data(this, dataGroup);
		result->setQuantity(name);
		dataGroup	= NULL;
		return result;
	}
	catch (...)
	{
		delete dataGroup;
		delete result;
		throw;
	}
}
int Product_2D::getQuantityDataCount	()
{
	return getDataCount();
}

bool Product_2D::hasQuantityData(const std::string& name)
{
	return hasQuantityData(name.c_str());
}

bool Product_2D::hasQuantityData(const char* name) 
{
	return getQuantityDataIndex(name) >= 0;
}

int Product_2D::getQuantityDataIndex(const char* name)
{	
	int dataCount = getDataCount();
	for (int i=0; i<dataCount; i++)
	{
		OdimData* data = NULL;
		try
		{
			data = getData(i);
			if (data->getWhat()->getStr(ATTRIBUTE_WHAT_QUANTITY) == name)
			{
				delete data;
				return i;
			}
			delete data;
		}
		catch (...)
		{
			delete data;
			throw;
		}
	}
	return -1;
}

int Product_2D::getQuantityDataIndex(const std::string& name)
{
	return getQuantityDataIndex(name.c_str());
}

std::set<std::string> Product_2D::getStoredQuantities()
{
	std::set<std::string> result;
	int dataCount = getDataCount();
	for (int i=0; i<dataCount; i++)
	{
		OdimData* data = NULL;
		try
		{
			data = getData(i);
			result.insert(data->getWhat()->getStr(ATTRIBUTE_WHAT_QUANTITY));
			delete data;
		}
		catch (...)
		{
			delete data;
			throw;
		}
	}
	return result;
}

Product_2D_Data*	Product_2D::getQuantityData(int index) 
{
	H5::Group* h5group = getDataGroup(index);
	try
	{
		if (h5group)
			return  new Product_2D_Data(this, h5group);
		return NULL;
	}
	catch (...)
	{
		delete h5group;
		throw;
	}
}

Product_2D_Data*	Product_2D::getQuantityData(const std::string& name) 
{
	return getQuantityData(name.c_str()); 
}

Product_2D_Data*	Product_2D::getQuantityData(const char* name) 
{		
	int dataCount = getDataCount();
	for (int i=0; i<dataCount; i++)
	{
		Product_2D_Data* data = NULL;
		try
		{
			data = getQuantityData(i);
			std::string quantity = data->getQuantity();
			if (quantity == name)
				return data;
			delete data;
		}
		catch (...)
		{
			delete data;
			throw;
		}
	}
	return NULL;
}

void Product_2D::removeQuantityData(const std::string& name) 
{
	return removeQuantityData(name.c_str());
}

void Product_2D::removeQuantityData(const char* name) 
{				
	int index = getQuantityDataIndex(name);
	if (index >= 0)
		removeData(index);
}

/*===========================================================================*/
/* HORIZONTAL PRODUCT Dataset  */
/*===========================================================================*/
Horizontal_Product_2D::Horizontal_Product_2D(Object_2D* object_2d, H5::Group* group)
:WHEREImageMetadata()
,HOWCartesianImageMetadata()
,Product_2D(object_2d,group)
{
}

Horizontal_Product_2D::~Horizontal_Product_2D()
{		
}

/* 
 void Horizontal_Product_2D::setMandatoryInformations(std::string type)
{		
	setProduct(type);		
}
*/

std::string		Horizontal_Product_2D::getProjectionArguments	(){ return getWhere()->getStr	(ATTRIBUTE_WHERE_PROJDEF);	} 
void			Horizontal_Product_2D::setProjectionArguments	(const std::string& val){   getWhere()->set (ATTRIBUTE_WHERE_PROJDEF, val);	} 

int			Horizontal_Product_2D::getXSize		(){ return getWhere()->getInt	(ATTRIBUTE_WHERE_XSIZE);	} 		
void			Horizontal_Product_2D::setXSize		(int val){  getWhere()->set	(ATTRIBUTE_WHERE_XSIZE, val);   }		
int			Horizontal_Product_2D::getYSize		(){ return getWhere()->getInt	(ATTRIBUTE_WHERE_YSIZE);	} 				
void			Horizontal_Product_2D::setYSize		(int val){  getWhere()->set	(ATTRIBUTE_WHERE_YSIZE, val);   }	
double			Horizontal_Product_2D::getXScale		(){ return getWhere()->getDouble(ATTRIBUTE_WHERE_XSCALE);	} 				
void			Horizontal_Product_2D::setXScale		(double val){  getWhere()->set	(ATTRIBUTE_WHERE_XSCALE, val);  }	
double			Horizontal_Product_2D::getYScale		(){ return getWhere()->getDouble(ATTRIBUTE_WHERE_YSCALE);	} 			
void			Horizontal_Product_2D::setYScale		(double val){  getWhere()->set	(ATTRIBUTE_WHERE_YSCALE, val);  }		

double			Horizontal_Product_2D::getLL_Longitude		(){ return getWhere()->getDouble(ATTRIBUTE_WHERE_LL_LON);	} 			
void			Horizontal_Product_2D::setLL_Longitude		(double val){  getWhere()->set	(ATTRIBUTE_WHERE_LL_LON, val);  }		
double			Horizontal_Product_2D::getLL_Latitude		(){ return getWhere()->getDouble(ATTRIBUTE_WHERE_LL_LAT);	}		
void			Horizontal_Product_2D::setLL_Latitude		(double val){  getWhere()->set	(ATTRIBUTE_WHERE_LL_LAT, val);  }			

double			Horizontal_Product_2D::getUL_Longitude		(){ return getWhere()->getDouble(ATTRIBUTE_WHERE_UL_LON);	}		
void			Horizontal_Product_2D::setUL_Longitude		(double val){  getWhere()->set	(ATTRIBUTE_WHERE_UL_LON, val);  }			
double			Horizontal_Product_2D::getUL_Latitude		(){ return getWhere()->getDouble(ATTRIBUTE_WHERE_UL_LAT);	}		
void			Horizontal_Product_2D::setUL_Latitude		(double val){  getWhere()->set	(ATTRIBUTE_WHERE_UL_LAT, val);  }			

double			Horizontal_Product_2D::getUR_Longitude		(){ return getWhere()->getDouble(ATTRIBUTE_WHERE_UR_LON);	}		
void			Horizontal_Product_2D::setUR_Longitude		(double val){  getWhere()->set	(ATTRIBUTE_WHERE_UR_LON, val);  }			
double			Horizontal_Product_2D::getUR_Latitude		(){ return getWhere()->getDouble(ATTRIBUTE_WHERE_UR_LAT);	}		
void			Horizontal_Product_2D::setUR_Latitude		(double val){  getWhere()->set	(ATTRIBUTE_WHERE_UR_LAT, val);  }			

double			Horizontal_Product_2D::getLR_Longitude		(){ return getWhere()->getDouble(ATTRIBUTE_WHERE_LR_LON);	}		
void			Horizontal_Product_2D::setLR_Longitude		(double val){  getWhere()->set	(ATTRIBUTE_WHERE_LR_LON, val);  }			
double			Horizontal_Product_2D::getLR_Latitude		(){ return getWhere()->getDouble(ATTRIBUTE_WHERE_LR_LAT);	}		
void			Horizontal_Product_2D::setLR_Latitude		(double val){  getWhere()->set	(ATTRIBUTE_WHERE_LR_LAT, val);  }			

std::vector<Angles>	Horizontal_Product_2D::getAngles		()  { return getHow()->getAngles(ATTRIBUTE_HOW_ANGLES); }		
void			Horizontal_Product_2D::setAngles		(const std::vector<Angles>& val) {getHow()->set(ATTRIBUTE_HOW_ANGLES, val, 5);	}

std::vector<Arotation>	Horizontal_Product_2D::getArotation		()  { return getHow()->getArotation(ATTRIBUTE_HOW_AROTATION); }
void			Horizontal_Product_2D::setArotation		(const std::vector<Arotation>& val) {getHow()->set(ATTRIBUTE_HOW_AROTATION, val, 5);	}

std::string		Horizontal_Product_2D::getCAMethod		(){ return getHow()->getStr	(ATTRIBUTE_HOW_CAMETHOD);	}
void			Horizontal_Product_2D::setCAMethod		(const std::string& val)  {getHow()->set(ATTRIBUTE_HOW_CAMETHOD, val);	}

std::vector<Nodes> Horizontal_Product_2D::getNodes		() { 
	return getHow()->getNodes (ATTRIBUTE_HOW_NODES);	
}
void			Horizontal_Product_2D::setNodes		(const std::vector<Nodes>& val) {getHow()->set(ATTRIBUTE_HOW_NODES, val);	}

int			Horizontal_Product_2D::getACCnum		(){ return getHow()->getInt (ATTRIBUTE_HOW_ACCNUM);	}
void			Horizontal_Product_2D::setCCnum		(int val){ getHow()->set (ATTRIBUTE_HOW_ACCNUM, val);	}					

/*===========================================================================*/
/* PPI PRODUCT Dataset  */
/*===========================================================================*/
Product_PPI::Product_PPI(Object_2D * object_2d, H5::Group* group)
:Horizontal_Product_2D(object_2d,group)
{			
}

Product_PPI::~Product_PPI()
{		
}

void Product_PPI::setMandatoryInformations()
{		
	setProduct(PRODUCT_PPI);		
}
/*===========================================================================*/
/* CAPPI PRODUCT Dataset  */
/*===========================================================================*/
Product_CAPPI::Product_CAPPI(Object_2D * object_2d, H5::Group* group)
:Horizontal_Product_2D(object_2d,group)
{			
}

Product_CAPPI::~Product_CAPPI()
{		
}

void Product_CAPPI::setMandatoryInformations()
{		
	setProduct(PRODUCT_CAPPI);		
}
/*===========================================================================*/
/* PCAPPI PRODUCT Dataset  */
/*===========================================================================*/
Product_PCAPPI::Product_PCAPPI(Object_2D * object_2d, H5::Group* group)
:Horizontal_Product_2D(object_2d,group)
{			
}

Product_PCAPPI::~Product_PCAPPI()
{		
}

void Product_PCAPPI::setMandatoryInformations()
{		
	setProduct(PRODUCT_PCAPPI);		
}
/*===========================================================================*/
/* ETOP PRODUCT Dataset  */
/*===========================================================================*/
Product_ETOP::Product_ETOP(Object_2D * object_2d, H5::Group* group)
:Horizontal_Product_2D(object_2d,group)
{			
}

Product_ETOP::~Product_ETOP()
{		
}

void Product_ETOP::setMandatoryInformations()
{		
	setProduct(PRODUCT_ETOP);		
}
/*===========================================================================*/
/* MAX PRODUCT Dataset  */
/*===========================================================================*/
Product_MAX::Product_MAX(Object_2D * object_2d, H5::Group* group)
:Horizontal_Product_2D(object_2d,group)
{			
}

Product_MAX::~Product_MAX()
{		
}

void Product_MAX::setMandatoryInformations()
{		
	setProduct(PRODUCT_MAX);		
}
/*===========================================================================*/
/* RR PRODUCT Dataset  */
/*===========================================================================*/
Product_RR::Product_RR(Object_2D * object_2d, H5::Group* group)
:Horizontal_Product_2D(object_2d,group)
{			
}

Product_RR::~Product_RR()
{		
}

void Product_RR::setMandatoryInformations()
{		
	setProduct(PRODUCT_RR);		
}
/*===========================================================================*/
/* VIL PRODUCT Dataset  */
/*===========================================================================*/
Product_VIL::Product_VIL(Object_2D * object_2d, H5::Group* group)
:Horizontal_Product_2D(object_2d,group)
{			
}

Product_VIL::~Product_VIL()
{		
}

void Product_VIL::setMandatoryInformations()
{		
	setProduct(PRODUCT_VIL);		
}
/*===========================================================================*/
/* LBM PRODUCT Dataset  */
/*===========================================================================*/
Product_LBM::Product_LBM(Object_2D * object_2d, H5::Group* group)
:Horizontal_Product_2D(object_2d,group)
{			
}

Product_LBM::~Product_LBM()
{		
}

void Product_LBM::setMandatoryInformations()
{		
	setProduct(PRODUCT_LBM_ARPA);
}
/*===========================================================================*/
/* COMP PRODUCT Dataset  */
/*===========================================================================*/
Product_COMP::Product_COMP(Object_2D * object_2d, H5::Group* group)
:Horizontal_Product_2D(object_2d,group)
{			
}

Product_COMP::~Product_COMP()
{		
}

void Product_COMP::setMandatoryInformations()
{		
	setProduct(PRODUCT_COMP);		
}

/*===========================================================================*/
/* VERTICAL PRODUCT Dataset  */
/*===========================================================================*/

Vertical_Product_2D::Vertical_Product_2D(Object_2D * object_2d, H5::Group* group)
:WHEREXSECMetadata()
,Product_2D(object_2d,group)
{			
}

Vertical_Product_2D::~Vertical_Product_2D()
{		
}


/* 
 void Horizontal_Product_2D::setMandatoryInformations(std::string type)
{		
	setProduct(type);		
}
*/

int			Vertical_Product_2D::getXSize		(){ return getWhere()->getInt	(ATTRIBUTE_WHERE_XSIZE);	} 
void			Vertical_Product_2D::setXSize		(int val){  getWhere()->set	(ATTRIBUTE_WHERE_XSIZE, val);   }
int			Vertical_Product_2D::getYSize		(){ return getWhere()->getInt	(ATTRIBUTE_WHERE_YSIZE);	} 
void			Vertical_Product_2D::setYSize		(int val){  getWhere()->set	(ATTRIBUTE_WHERE_YSIZE, val);   }
double			Vertical_Product_2D::getXScale		(){ return getWhere()->getDouble(ATTRIBUTE_WHERE_XSCALE);	} 
void			Vertical_Product_2D::setXScale		(double val){  getWhere()->set	(ATTRIBUTE_WHERE_XSCALE, val);  }
double			Vertical_Product_2D::getYScale		(){ return getWhere()->getDouble(ATTRIBUTE_WHERE_YSCALE);	} 
void			Vertical_Product_2D::setYScale		(double val){  getWhere()->set	(ATTRIBUTE_WHERE_YSCALE, val);  }

double			Vertical_Product_2D::getMinHeight 	(){ return getWhere()->getDouble(ATTRIBUTE_WHERE_MINHEIGHT);	} 
void			Vertical_Product_2D::setMinHeight	(double val){  getWhere()->set	(ATTRIBUTE_WHERE_MINHEIGHT, val);  }
double			Vertical_Product_2D::getMaxHeight 	(){ return getWhere()->getDouble(ATTRIBUTE_WHERE_MAXHEIGHT);	} 
void			Vertical_Product_2D::setMaxHeight	(double val){  getWhere()->set	(ATTRIBUTE_WHERE_MAXHEIGHT, val);  }

/*===========================================================================*/
/* XSEC PRODUCT Dataset  */
/*===========================================================================*/
Product_XSEC::Product_XSEC(Object_2D * object_2d, H5::Group* group)
:Vertical_Product_2D(object_2d,group)
{			
}

Product_XSEC::~Product_XSEC()
{		
}

void Product_XSEC::setMandatoryInformations()
{		
	setProduct(PRODUCT_XSEC);		
}
/*===========================================================================*/
/* RHI PRODUCT Dataset  */
/*===========================================================================*/
Product_RHI::Product_RHI(Object_2D * object_2d, H5::Group* group)
:WHERERhiMetadata()
,Vertical_Product_2D(object_2d,group)
{			
}

Product_RHI::~Product_RHI()
{		
}

void Product_RHI::setMandatoryInformations()
{		
	setProduct(PRODUCT_RHI);		
}
double Product_RHI::getRHILon		(){ return getWhere()->getDouble(ATTRIBUTE_WHERE_LON); };
void   Product_RHI::setRHILon		(double val){  getWhere()->set	(ATTRIBUTE_WHERE_LON, val);  };
double Product_RHI::getRHILat		(){ return getWhere()->getDouble(ATTRIBUTE_WHERE_LAT); };
void   Product_RHI::setRHILat		(double val){  getWhere()->set	(ATTRIBUTE_WHERE_LAT, val);  };
double Product_RHI::getAzimuthAngle		(){ return getWhere()->getDouble(ATTRIBUTE_WHERE_AZ_ANGLE); };
void   Product_RHI::setAzimuthAngle		(double val){  getWhere()->set	(ATTRIBUTE_WHERE_AZ_ANGLE, val);  };
std::vector<Angles> Product_RHI::getAngles	()  { return getWhere()->getAngles(ATTRIBUTE_HOW_ANGLES); }	;
void   Product_RHI::setAngles (const std::vector<Angles>& val) {getWhere()->set(ATTRIBUTE_HOW_ANGLES, val, 5);	};
double Product_RHI::getRange		(){ return getWhere()->getDouble(ATTRIBUTE_WHERE_RANGE); };
void   Product_RHI::setRange		(double val){  getWhere()->set	(ATTRIBUTE_WHERE_RANGE, val);  };
/*===========================================================================*/
/* Panel PRODUCT Dataset  */
/*===========================================================================*/
Product_Panel::Product_Panel(Object_2D* object_2d, H5::Group* group)
:WHEREPanelMetadata()
,Vertical_Product_2D(object_2d,group)
{			
}

Product_Panel::~Product_Panel()
{		
}

void Product_Panel::setMandatoryInformations()
{		
}
double Product_Panel::getStartLongitude	(){ return getWhere()->getDouble(ATTRIBUTE_WHERE_START_LON); };
void   Product_Panel::setStartLongitude	(double val){  getWhere()->set	(ATTRIBUTE_WHERE_START_LON, val);  };
double Product_Panel::getStartLatitude	(){ return getWhere()->getDouble(ATTRIBUTE_WHERE_START_LAT); };
void   Product_Panel::setStartLatitude	(double val){  getWhere()->set	(ATTRIBUTE_WHERE_START_LAT, val);  };
double Product_Panel::getStopLongitude	(){ return getWhere()->getDouble(ATTRIBUTE_WHERE_STOP_LON); };
void   Product_Panel::setStopLongitude	(double val){  getWhere()->set	(ATTRIBUTE_WHERE_STOP_LON, val);  };
double Product_Panel::getStopLatitude	(){ return getWhere()->getDouble(ATTRIBUTE_WHERE_STOP_LAT); };
void   Product_Panel::setStopLatitude	(double val){  getWhere()->set	(ATTRIBUTE_WHERE_STOP_LAT, val);  };
/*===========================================================================*/
/* HSP PRODUCT Dataset  */
/*===========================================================================*/
Product_HSP::Product_HSP(Object_2D* object2d, H5::Group* group)
:Product_Panel(object_2d,group)
{			
}

Product_HSP::~Product_HSP()
{		
}

void Product_HSP::setMandatoryInformations()
{		
	setProduct(PRODUCT_HSP);		
}

/*===========================================================================*/
/* VSP PRODUCT Dataset  */
/*===========================================================================*/
Product_VSP::Product_VSP(Object_2D* object2d, H5::Group* group)
:Product_Panel(object_2d,group)
{			
}

Product_VSP::~Product_VSP()
{		
}

void Product_VSP::setMandatoryInformations()
{		
	setProduct(PRODUCT_VSP);		
}

/*===========================================================================*/
/* PRODUCT_2D_DATA */
/*===========================================================================*/

Product_2D_Data::Product_2D_Data(Product_2D* prod, H5::Group* group)
:OdimData(group)
,WHATDatasetMetadata()
,prod(prod)
{
}

Product_2D_Data::~Product_2D_Data()
{
}

std::string		Product_2D_Data::getObject	()				{ return getWhat()->getStr	(ATTRIBUTE_WHAT_OBJECT, "");	}
void			Product_2D_Data::setObject	(const std::string& val) 	{        getWhat()->set		(ATTRIBUTE_WHAT_OBJECT, val);	}
std::string		Product_2D_Data::getVersion	() 				{ return getWhat()->getStr	(ATTRIBUTE_WHAT_VERSION, "");		}
void			Product_2D_Data::setVersion	(const std::string& val)	{        getWhat()->set		(ATTRIBUTE_WHAT_VERSION, val);	}
time_t			Product_2D_Data::getDateTime	()				{ return getWhatDateTime(this->getWhat());		}
void			Product_2D_Data::setDateTime	(const time_t val)		{	 setWhatDateTime(this->getWhat(), (int64_t)val);		}
SourceInfo		Product_2D_Data::getSource	() 				{ return SourceInfo(getWhat()->getStr(ATTRIBUTE_WHAT_SOURCE, ""));		}
void			Product_2D_Data::setSource	(const SourceInfo& val)		{        getWhat()->set		(ATTRIBUTE_WHAT_SOURCE, val.toString() );	}

std::string		Product_2D_Data::getProduct	()				{ return getWhat()->getStr	(ATTRIBUTE_WHAT_PRODUCT, "");		}
void			Product_2D_Data::setProduct	(const std::string& val)	{        getWhat()->set		(ATTRIBUTE_WHAT_PRODUCT, val);		}
double			Product_2D_Data::getProdPar	()				{ return getWhat()->getDouble	(ATTRIBUTE_WHAT_PRODPAR);		}
VILHeights		Product_2D_Data::getProdParVIL	()				{ return getWhat()->getVILHeights(ATTRIBUTE_WHAT_PRODPAR); 	}
void			Product_2D_Data::setProdPar	(double val) 			{ return getWhat()->set	(ATTRIBUTE_WHAT_PRODPAR, val);		}
void			Product_2D_Data::setProdPar	(const VILHeights& val) 	{ return getWhat()->set	(ATTRIBUTE_WHAT_PRODPAR, val);		}
std::string		Product_2D_Data::getQuantity	() 				{ return getWhat()->getStr	(ATTRIBUTE_WHAT_QUANTITY);	}
void			Product_2D_Data::setQuantity	(const std::string& val)	{	 getWhat()->set		(ATTRIBUTE_WHAT_QUANTITY, val);	}
time_t			Product_2D_Data::getStartDateTime	()				{ return getWhatStartDateTime(this->getWhat()); }
void			Product_2D_Data::setStartDateTime	(time_t value)			{	 setWhatStartDateTime(this->getWhat(), (int64_t)value);	}
time_t			Product_2D_Data::getEndDateTime	()				{ return getWhatEndDateTime(this->getWhat()); }
void			Product_2D_Data::setEndDateTime	(time_t value)			{	 setWhatEndDateTime(this->getWhat(), (int64_t)value); }
double			Product_2D_Data::getGain		() 				{ return getWhat()->getDouble	(ATTRIBUTE_WHAT_GAIN);			}
void			Product_2D_Data::setGain		(double val)			{        getWhat()->set		(ATTRIBUTE_WHAT_GAIN, val);		}
double			Product_2D_Data::getOffset	() 				{ return getWhat()->getDouble	(ATTRIBUTE_WHAT_OFFSET);		}
void			Product_2D_Data::setOffset	(double val) 			{        getWhat()->set		(ATTRIBUTE_WHAT_OFFSET, val);	}
double			Product_2D_Data::getNodata	()				{ return getWhat()->getDouble	(ATTRIBUTE_WHAT_NODATA);		}
void			Product_2D_Data::setNodata	(double val) 			{        getWhat()->set		(ATTRIBUTE_WHAT_NODATA, val);	}
double			Product_2D_Data::getUndetect	()				{ return getWhat()->getDouble	(ATTRIBUTE_WHAT_UNDETECT);		}
void			Product_2D_Data::setUndetect	(double val) 			{        getWhat()->set		(ATTRIBUTE_WHAT_UNDETECT, val);	}

H5::AtomType Product_2D_Data::getElemType() 
{
	return this->getDataType();
}

int Product_2D_Data::getNumYElem() 
{
	return this->getDataHeight();
}

int Product_2D_Data::getNumXElem() 
{
	return this->getDataWidth();
}

void Product_2D_Data::readTranslatedData(DataMatrix<float>& matrix)
{
	H5::DataType	type	= this->getDataType();
	int		ysize	= this->getNumYElem();
	int		xsize	= this->getNumXElem();
	double		offset	= this->getOffset();
	double		gain	= this->getGain();

	matrix.resize(ysize, xsize);

	if (type == H5::PredType::NATIVE_UINT8)
	{
		DataMatrix<unsigned char> rawmatrix(ysize, xsize);
		readData(const_cast<unsigned char*>(rawmatrix.get()));
		for (int r=0; r<ysize; r++)
			for (int b=0; b<xsize; b++)
				matrix.elem(r,b) = (float)(((double)rawmatrix.elem(r,b)) * gain + offset);
	}
	else if (type == H5::PredType::NATIVE_UINT16)
	{
		DataMatrix<unsigned short> rawmatrix(ysize, xsize);
		readData(const_cast<unsigned short*>(rawmatrix.get()));
		for (int r=0; r<ysize; r++)
			for (int b=0; b<xsize; b++)
				matrix.elem(r,b) = (float)(((double)rawmatrix.elem(r,b)) * gain + offset);
	}
	else if (type == H5::PredType::NATIVE_FLOAT)
	{
		DataMatrix<float> rawmatrix(ysize, xsize);
		readData(const_cast<float*>(rawmatrix.get()));
		for (int r=0; r<ysize; r++)
			for (int b=0; b<xsize; b++)
				matrix.elem(r,b) = (float)(((double)rawmatrix.elem(r,b)) * gain + offset);
	}
}

void Product_2D_Data::readTranslatedData(DataMatrix<double>& matrix)
{
	H5::DataType	type	= this->getDataType();
	int		ysize	= this->getNumYElem();
	int		xsize	= this->getNumXElem();
	double		offset	= this->getOffset();
	double		gain	= this->getGain();

	matrix.resize(ysize,xsize);

	if (type == H5::PredType::NATIVE_UINT8)
	{
		DataMatrix<unsigned char> rawmatrix(ysize,xsize);
		readData(const_cast<unsigned char*>(rawmatrix.get()));
		for (int r=0; r<ysize; r++)
			for (int b=0; b<xsize; b++)
				matrix.elem(r,b) = ((double)rawmatrix.elem(r,b)) * gain + offset;
	}
	else if (type == H5::PredType::NATIVE_UINT16)
	{
		DataMatrix<unsigned short> rawmatrix(ysize, xsize);
		readData(const_cast<unsigned short*>(rawmatrix.get()));
		for (int r=0; r<ysize; r++)
			for (int b=0; b<xsize; b++)
				matrix.elem(r,b) = ((double)rawmatrix.elem(r,b)) * gain + offset;
	}
	else if (type == H5::PredType::NATIVE_FLOAT)
	{
		DataMatrix<float> rawmatrix(ysize,xsize);
		readData(const_cast<float*>(rawmatrix.get()));
		for (int r=0; r<ysize; r++)
			for (int b=0; b<xsize; b++)
				matrix.elem(r,b) = ((double)rawmatrix.elem(r,b)) * gain + offset;
	}
}

/*===========================================================================*/

/* converte la matrice src nella matrice dst traducendo i valori in base a gain e offset */
template <class SRCTYPE, class DSTTYPE> 
static void translate(DataMatrix<SRCTYPE>& src, DataMatrix<DSTTYPE>& dst, SRCTYPE offset, SRCTYPE gain)
{
	int rows = src.getRowCount();
	int cols = src.getColCount();
	dst.resize(rows,cols);
	for (int i=0; i<rows; i++)
		for (int j=0; j<cols; j++)
			dst.elem(i,j) = (DSTTYPE)((src.elem(i,j) - offset) / gain);
}

void Product_2D_Data::writeAndTranslate(DataMatrix<float>& matrix, float offset, float gain, H5::DataType bintype)
{
	if (bintype == H5::PredType::NATIVE_INT8)
	{
		DataMatrix<char> matrix2;
		translate<float, char>(matrix, matrix2, offset, gain);	
		writeData(matrix2);
	}
	else if (bintype == H5::PredType::NATIVE_UINT8)
	{
		DataMatrix<unsigned char> matrix2;
		translate<float, unsigned char>(matrix, matrix2, offset, gain);	
		writeData(matrix2);
	}
	else if (bintype == H5::PredType::NATIVE_UINT16)
	{
		DataMatrix<unsigned short> matrix2;
		translate<float, unsigned short>(matrix, matrix2, offset, gain);	
		writeData(matrix2);
	}
	else if (bintype == H5::PredType::NATIVE_FLOAT)
	{
		DataMatrix<float> matrix2;
		translate<float, float>(matrix, matrix2, offset, gain);	
		writeData(matrix2);
	}
	else
	{
		throw OdimH5UnsupportedException("Unable to write and translate matrix values to the requested HDF5 bintype");
	}
}

void Product_2D_Data::writeAndTranslate(DataMatrix<double>& matrix, double offset, double gain, H5::DataType bintype)
{
	if (bintype == H5::PredType::NATIVE_INT8)
	{
		DataMatrix<char> matrix2;
		translate<double, char>(matrix, matrix2, offset, gain);	
		writeData(matrix2);
	}
	if (bintype == H5::PredType::NATIVE_UINT8)
	{
		DataMatrix<unsigned char> matrix2;
		translate<double, unsigned char>(matrix, matrix2, offset, gain);	
		writeData(matrix2);
	}
	else if (bintype == H5::PredType::NATIVE_UINT16)
	{
		DataMatrix<unsigned short> matrix2;
		translate<double, unsigned short>(matrix, matrix2, offset, gain);	
		writeData(matrix2);
	}
	else if (bintype == H5::PredType::NATIVE_FLOAT)
	{
		DataMatrix<float> matrix2;
		translate<double, float>(matrix, matrix2, offset, gain);	
		writeData(matrix2);
	}
	else
	{
		throw OdimH5UnsupportedException("Unable to write and translate matrix values to the requested HDF5 bintype");
	}

}


int		Product_2D_Data::getQualityDataCount()
{
	return getQualityCount();
}
OdimQuality*	Product_2D_Data::getQualityData		(int index)
{
	H5::Group* h5group = getQualityGroup(index);
	try
	{
		if (h5group)
			return  new OdimQuality(h5group);
		return NULL;
	}
	catch (...)
	{
		delete h5group;
		throw;
	}
}

void		Product_2D_Data::removeQualityData	(int index)  
{				
		removeQuality(index);	
}

OdimQuality* Product_2D_Data::createQualityData() 
{
	H5::Group*	qualityGroup	= NULL;
	OdimQuality*	result		= NULL;
	try
	{
		qualityGroup	= createQualityGroup();
		result		= new OdimQuality(qualityGroup);
		qualityGroup	= NULL;
		return result;
	}
	catch (...)
	{
		delete qualityGroup;
		delete result;
		throw;
	}
}

/*===========================================================================*/




}
