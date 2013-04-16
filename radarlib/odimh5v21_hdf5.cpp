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

#include <radarlib/odimh5v21_hdf5.hpp>

#include <cstdlib>
#include <cstring>
#include <vector>
#include <iostream>
#include <sstream>
#include <assert.h>

#include <radarlib/debug.hpp>
#include <radarlib/string.hpp>
#include <radarlib/odimh5v21_const.hpp>
#include <radarlib/odimh5v21_exceptions.hpp>

namespace OdimH5v21 {

/*===========================================================================*/
/* FUNZIONI INTERNE DI COMODO */
/*===========================================================================*/

#define THROW_EXCEPTION(name,msg)			\
	do {						\
	std::ostringstream ss; ss << msg;		\
	throw name(ss.str());				\
	} while (0)

/* NOTA: Queste definizioni non possono essere statiche perche' altrimenti nelle operazioni di link si schinata tutto */
/* quindi le ho trasferite all'interno delle singole funzioni a costo di duplicare 2/3 righe */
//atic const H5::IntType	INT64TYPE	(H5::PredType::NATIVE_INT64);
//atic const H5::FloatType	DOUBLETYPE	(H5::PredType::NATIVE_DOUBLE);
//atic const H5::StrType	STRINGTYPE	(H5::PredType::C_S1, H5T_VARIABLE);
//definizioni per usi futuri
//atic const H5::IntType	BOOLTYPE	(H5::PredType::NATIVE_UINT8);
//atic const H5::IntType	INTTYPE		(H5::PredType::NATIVE_INT);
//atic const H5::IntType	LONGTYPE	(H5::PredType::NATIVE_LONG);
//atic const H5::FloatType	FLOATTYPE	(H5::PredType::NATIVE_FLOAT);

/*===========================================================================*/
/* HDF5 FILE */
/*===========================================================================*/

static int odimh5_init = 0;

static void initLibrary()
{
	if (odimh5_init)
		return;
	try
	{
		//H5::Exception::dontPrint();
		odimh5_init++;
	}
	catch (H5::Exception& h5e)
	{
		throw OdimH5HDF5LibException("H5::Exception::dontPrint() failed: ", h5e);
	}
}


H5::H5File* HDF5File::open(const std::string& path, int h5flags) 
{
	initLibrary();
	try
	{	
		return new H5::H5File(path.c_str(), h5flags);
	}
	catch (H5::Exception& h5e)
	{
		std::ostringstream ss; ss << "Cannot open " << path << " with flags 0x" << std::hex << h5flags;
		throw OdimH5HDF5LibException(ss.str(), h5e);		
	}
}

H5::Group* HDF5File::getRoot(H5::H5File* file) 
{
	if (file==NULL) throw std::invalid_argument("H5 FILE is NULL");		
	try
	{
		return new H5::Group( file->openGroup("/") );
	}
	catch (H5::Exception& h5e)
	{
		throw OdimH5HDF5LibException("Cannot get hdf5 '/' group", h5e);		
	}
}

/*===========================================================================*/
/* HDF5 ATTRIBUTE */
/*===========================================================================*/

static inline bool attrExists(H5::H5Object* object, const char* name)
{
	if (object == NULL) throw std::invalid_argument("H5Object is NULL");	
	if (name   == NULL) throw std::invalid_argument("name is NULL");	
	
	hid_t  id     = object->getId();
	htri_t result = H5Aexists(id, name);
	if (result < 0) {
		std::ostringstream ss; ss << "H5Aexists("<<id<<","<<name<<") failed: "<< result;
		throw OdimH5HDF5LibException(ss.str());
	}
	return result == 1;
}

H5::Attribute* HDF5Attribute::get(H5::H5Object* obj, const char* name, bool mandatory)
{
	if (attrExists(obj, name))
		return new H5::Attribute(obj->openAttribute(name));		
	if (mandatory)
		throw OdimH5MissingAttributeException("Mandatory attribute " + std::string(name) + " not found");
	return NULL;
}

bool HDF5Attribute::exists(H5::H5Object* object, const char* name) 	//throw (H5::Exception)
{
	return attrExists(object, name);
}

static void attrRemove(H5::H5Object* obj, const char* name) 
{
	if (obj==NULL) throw std::invalid_argument("obj is NULL");		
	try
	{
		obj->removeAttr(name);
	}
	catch (H5::Exception& h5e)
	{
		throw OdimH5HDF5LibException("Cannot remove attribute " + std::string(name), h5e);
	}
}

void HDF5Attribute::remove(H5::H5Object* obj, const char* name)	// throw (H5::Exception)
{
	if (attrExists(obj, name))
		attrRemove(obj, name);
}

std::string HDF5Attribute::getName(H5::Attribute* attr)
{
	/* NOTA: la funzione H5::Attribute->getName() sembra non funzionare, quindi uso questo wrapper */
	char buff[200+1];	
	size_t len = H5Aget_name(attr->getId(), 200, buff);
	buff[len] = '\0';
	return buff;
}

void HDF5Attribute::set(H5::H5Object* obj, const char* name, int64_t value)	// throw (H5::Exception)
{
	if (attrExists(obj, name))
		attrRemove(obj, name);

	H5::Attribute* attr = NULL;
	try 
	{
		H5::IntType	INT64TYPE	(H5::PredType::NATIVE_INT64);
		attr = new H5::Attribute(obj->createAttribute(name, INT64TYPE, H5::DataSpace()));		
		attr->write(INT64TYPE, &value);	
		delete attr;
	} 
	catch (H5::Exception& h5e)
	{
		delete attr;
		std::ostringstream ss; ss << "HDF5 library inside HDF5Attribute::set(...," << name << "," << value << ")";
		throw OdimH5HDF5LibException(ss.str(), h5e);
	}
	catch (...) 
	{
		delete attr;
		throw;
	}
}

void HDF5Attribute::set(H5::H5Object* obj, const char* name, double value) 
{
	if (attrExists(obj, name))
		attrRemove(obj, name);

	H5::Attribute* attr = NULL;
	try 
	{
		H5::FloatType	DOUBLETYPE	(H5::PredType::NATIVE_DOUBLE);
		attr = new H5::Attribute(obj->createAttribute(name, DOUBLETYPE, H5::DataSpace()));		
		attr->write(DOUBLETYPE, &value);	
		delete attr;	
	} 
	catch (H5::Exception& h5e)
	{
		delete attr;
		std::ostringstream ss; ss << "Cannot open/write attribute " << name;
		throw OdimH5HDF5LibException(ss.str(), h5e);
	}
	catch (...) 
	{
		delete attr;
		throw;
	}
}

void HDF5Attribute::set(H5::H5Object* obj, const char* name, const std::string& value)	// throw (H5::Exception)
{
	if (attrExists(obj, name))
		attrRemove(obj, name);

	H5::Attribute* attr = NULL;
	try
	{
		//VECCHIA VERSIONE FUNINANTE (genera stringe variaibli)
		//const char* buf[1]= { value.c_str() };	
		//attr = new Attribute(obj->createAttribute(name, STRINGTYPE, H5::DataSpace()));		
		//attr->write(STRINGTYPE, buf);		
		//delete attr;				

		H5::StrType STRINGTYPE2	(H5::PredType::C_S1);		
		STRINGTYPE2.setSize(value.length()+1);
		STRINGTYPE2.setCset(H5T_CSET_ASCII);				
		attr = new H5::Attribute(obj->createAttribute(name, STRINGTYPE2, H5::DataSpace()));				
		attr->write(STRINGTYPE2, value.c_str());	
		delete attr;
	}
	catch (H5::Exception& h5e)
	{
		delete attr;
		std::ostringstream ss; ss << "Cannot open/write attribute " << name;
		throw OdimH5HDF5LibException(ss.str(), h5e);
	}
	catch (...) 
	{
		delete attr;
		throw;
	}
}

void HDF5Attribute::set(H5::H5Object* obj, const char* name, const char* value) 
{
	set(obj, name, std::string(value));
}

static int64_t attrGetLong(H5::H5Object* obj, const char* name) 
{
	H5::Attribute* attr = NULL;
	try {
		int64_t result = 0;
		attr = new H5::Attribute(obj->openAttribute(name));		
		H5::IntType	INT64TYPE	(H5::PredType::NATIVE_INT64);
		attr->read(INT64TYPE, &result);			
		delete attr;
		return result;
	}
	catch (H5::Exception& h5e)
	{
		delete attr;
		std::ostringstream ss; ss << "Cannot open/read attribute " << name;
		throw OdimH5HDF5LibException(ss.str(), h5e);
	}
	catch (...) 
	{
		delete attr;
		throw;
	}
}

int64_t HDF5Attribute::getLong(H5::H5Object* obj, const char* name) 
{
	if (!attrExists(obj, name))
		throw OdimH5MissingAttributeException("Cannot open/read mandatory attribute " + std::string(name));
	return attrGetLong(obj, name);
}

int64_t HDF5Attribute::getLong(H5::H5Object* obj, const char* name, int64_t defaultValue) 
{
	if (!attrExists(obj, name))
		return defaultValue;
	return attrGetLong(obj, name);
}

static double attrGetDouble(H5::H5Object* obj, const char* name)
{
	H5::Attribute* attr = NULL;
	try 
	{
		double result;		
		attr = new H5::Attribute(obj->openAttribute(name));		
		H5::FloatType	DOUBLETYPE	(H5::PredType::NATIVE_DOUBLE);
		attr->read(DOUBLETYPE, &result);
		delete attr;
		return result;
	} 
	catch (H5::Exception& h5e)
	{
		delete attr;
		std::ostringstream ss; ss << "Cannot open/read attribute " << name;
		throw OdimH5HDF5LibException(ss.str(), h5e);
	}
	catch (...) 
	{
		delete attr;
		throw;
	}
}

double HDF5Attribute::getDouble(H5::H5Object* obj, const char* name)
{
	if (!attrExists(obj, name)) {
		std::ostringstream ss; ss << "Cannot open/read mandatory attribute " << name;
		throw OdimH5MissingAttributeException(ss.str());
	}
	return attrGetDouble(obj, name);
}

double HDF5Attribute::getDouble(H5::H5Object* obj, const char* name, double defaultValue)
{
	if (!attrExists(obj, name))
		return defaultValue;
	return attrGetDouble(obj, name);
}

std::string attrGetStr(H5::H5Object* obj, const char* name)
{
	H5::Attribute* attr = NULL;
	char* buf[1] = { NULL };	//NOTA: non si capisce bene perche' l'implementazione interna vuole cosi' altrimenti crasha tutto
	try
	{
		//VERSIONE PRECEDENTE
		//char* buf[1];		
		//attr = new Attribute(obj->openAttribute(name));		
		//attr->read(STRINGTYPE, buf);		//attr->read(StrType(PredType::C_S1, H5T_VARIABLE), buf);
		//result = buf[0];
		////free(buf[0]);		
		//delete attr;

		std::string result;
		char* buf[1];		
		attr = new H5::Attribute(obj->openAttribute(name));		
		H5::StrType STRTYPE = attr->getStrType();
		size_t len = (size_t)attr->getStorageSize();
		buf[0] = new char[len];
		attr->read(STRTYPE, buf[0]);		//attr->read(StrType(PredType::C_S1, H5T_VARIABLE), buf);
		result = buf[0];

		free(buf[0]);	buf[0]=NULL;
		delete attr;

		return result;
	}
	catch (H5::Exception& h5e)
	{
		free(buf[0]);	
		delete attr;
		std::ostringstream ss; ss << "Cannot open/read attribute " << name;
		throw OdimH5HDF5LibException(ss.str(), h5e);
	}
	catch (...) 
	{
		free(buf[0]);	
		delete attr;
		throw;
	}		
}

std::string HDF5Attribute::getStr(H5::H5Object* obj, const char* name)
{
	if (!attrExists(obj, name))
		THROW_EXCEPTION(OdimH5MissingAttributeException, "Cannot open/read mandatory attribute " << name);
	return attrGetStr(obj, name);
}

std::string HDF5Attribute::getStr(H5::H5Object* obj, const char* name, const std::string& defaultValue)
{
	if (!attrExists(obj, name))
		return defaultValue;
	return attrGetStr(obj, name);
}

/*===========================================================================*/
/* HDF5GROUP */
/*===========================================================================*/

struct iterate_group_data
{
	const char*	searchName;	
	const size_t	searchNameLen;
	unsigned char	found;
	int		count;

	iterate_group_data(const char* name)
	:searchName(name)
	,searchNameLen(strlen(name))
	,found(0)
	,count(0)
	{
	}
};

//extern "C" herr_t find_group(hid_t loc_id, const char *name, const H5L_info_t *linfo, void *opdata)
static herr_t find_group(hid_t loc_id, const char *name, const H5L_info_t *linfo, void *opdata)
{		
	iterate_group_data* data = (iterate_group_data*)opdata;
	if (strcmp(name, data->searchName) == 0)
		data->found = 1;	
	return 0;
}

H5::Group* HDF5Group::getChild(H5::Group* parent, const char* name)	// throw (H5::Exception)
{
	if (parent==NULL)	THROW_EXCEPTION(std::invalid_argument, "parent is NULL");		
	if (name==NULL)		THROW_EXCEPTION(std::invalid_argument, "name is NULL");		

	iterate_group_data data(name);
	herr_t result = H5Literate(parent->getId(), H5_INDEX_NAME, H5_ITER_INC, NULL, find_group, &data);
	if (result < 0)
		THROW_EXCEPTION(OdimH5HDF5LibException, "H5Literate("<<parent->getId()<<",...,"<<name<<") failed: " << result);
	try
	{
		if (data.found)
			return new H5::Group(parent->openGroup(name) );	
		return NULL;
	}
	catch (H5::Exception& h5e)
	{		
		std::ostringstream ss; ss << "Cannot open group " << name;
		throw OdimH5HDF5LibException(ss.str(), h5e);
	}			
}

void HDF5Group::ensureChild(H5::Group* parent, const char* name)	// throw (H5::Exception)
{
	if (parent==NULL)	throw std::invalid_argument("HDF5 parent group is NULL");		
	if (name==NULL)		throw std::invalid_argument("name is NULL");		

	iterate_group_data data(name);

	herr_t result = H5Literate(parent->getId(), H5_INDEX_NAME, H5_ITER_INC, NULL, find_group, &data);

	if (result < 0) 
	{
		std::ostringstream ss; ss << "H5Literate("<<parent->getId()<<",...,"<<name<<") failed: " << result;
		throw OdimH5HDF5LibException(ss.str());
	}

	if (!data.found)
	{
		try
		{
			delete new H5::Group(parent->createGroup(name) );	
		}
		catch (H5::Exception& h5e)
		{		
			std::ostringstream ss; ss << "Cannot create group " << name;
			throw OdimH5HDF5LibException(ss.str(), h5e);
		}
	}
}

H5::Group* HDF5Group::ensureGetChild(H5::Group* parent, const char* name)	// throw (H5::Exception)
{
	if (parent==NULL)	throw std::invalid_argument("HDF5 parent group is NULL");		
	if (name==NULL)		throw std::invalid_argument("name is NULL");		


	iterate_group_data data(name);

	herr_t result = H5Literate(parent->getId(), H5_INDEX_NAME, H5_ITER_INC, NULL, find_group, &data);

	if (result < 0)
	{
		std::ostringstream ss; ss << "H5Literate("<<parent->getId()<<",...,"<<name<<") failed: " << result;
		throw OdimH5HDF5LibException(ss.str());
	}

	if (data.found)
	{
		try
		{
			return new H5::Group(parent->openGroup(name) );	
		}
		catch (H5::Exception& h5e)
		{		
			std::ostringstream ss; ss << "Cannot open group " << name;
			throw OdimH5HDF5LibException(ss.str(), h5e);
		}
	}		
	else
	{
		try
		{
			return new H5::Group(parent->createGroup(name) );	
		}
		catch (H5::Exception& h5e)
		{		
			std::ostringstream ss; ss << "Cannot create group " << name;
			throw OdimH5HDF5LibException(ss.str(), h5e);
		}
	}
}

/*===========================================================================*/

//extern "C" herr_t count_group(hid_t loc_id, const char *name, const H5L_info_t *linfo, void *opdata)
static herr_t count_group(hid_t loc_id, const char *name, const H5L_info_t *linfo, void *opdata)
{		
	iterate_group_data* data = (iterate_group_data*)opdata;
	if (memcmp(name, data->searchName, data->searchNameLen) == 0)	
		data->count++;	
	return 0;
}

int HDF5Group::getChildCount(H5::Group* parent, const char* prefix) //throw (H5::Exception)
{
	if (parent==NULL)	throw std::invalid_argument("HDF5 parent group is NULL");		
	if (prefix==NULL)	throw std::invalid_argument("prefix is NULL");		

	iterate_group_data data(prefix);

	herr_t result = H5Literate(parent->getId(), H5_INDEX_NAME, H5_ITER_INC, NULL, count_group, &data);

	if (result < 0)
	{
		std::ostringstream ss; ss << "H5Literate("<<parent->getId()<<",...,"<<prefix<<") failed: " << result;
		throw OdimH5HDF5LibException(ss.str());
	}

	return data.count;
}

/*===========================================================================*/

void HDF5Group::removeChild(H5::Group* parent, const char* name)	//	throw (H5::Exception)
{
	if (parent==NULL)	throw std::invalid_argument("HDF5 parent group is NULL");		
	if (name==NULL)		throw std::invalid_argument("name is NULL");		

	iterate_group_data data(name);

	herr_t result = H5Literate(parent->getId(), H5_INDEX_NAME, H5_ITER_INC, NULL, find_group, &data);

	if (result < 0)
	{
		std::ostringstream ss; ss << "H5Literate("<<parent->getId()<<",...,"<<name<<") failed: " << result;
		throw OdimH5HDF5LibException(ss.str());
	}

	if (data.found)
	{
		try
		{			
			parent->unlink(name);
		}
		catch (H5::Exception& h5e)
		{		
			std::ostringstream ss; ss << "Cannot delete group " << name;
			throw OdimH5HDF5LibException(ss.str(), h5e);
		}
	}
}

/*===========================================================================*/

struct iterate_dataset_data
{
	const char*	searchName;	
	const size_t	searchNameLen;
	unsigned char	found;
	size_t		count;

	iterate_dataset_data(const char* name)
	:searchName(name)
	,searchNameLen(strlen(name))
	,found(0)
	,count(0)
	{
	}
};

//extern "C" herr_t find_dataset(hid_t loc_id, const char *name, const H5L_info_t *linfo, void *opdata)
static  herr_t find_dataset(hid_t loc_id, const char *name, const H5L_info_t *linfo, void *opdata)
{		
	iterate_dataset_data* data = (iterate_dataset_data*)opdata;
	if (strcmp(name, data->searchName) == 0)
		data->found = 1;	
	return 0;
}

bool HDF5Group::exists(H5::Group* parent, const char* name)
{
	if (parent==NULL)	throw std::invalid_argument("HDF5 parent group is NULL");		
	if (name==NULL)		throw std::invalid_argument("name is NULL");		

	iterate_dataset_data data(name);

	herr_t result = H5Literate(parent->getId(), H5_INDEX_NAME, H5_ITER_INC, NULL, find_dataset, &data);

	if (result < 0)
	{
		std::ostringstream ss; ss << "H5Literate("<<parent->getId()<<",...,"<<name<<") failed: " << result;
		throw OdimH5HDF5LibException(ss.str());
	}

	return data.found > 0;
}

H5::DataSet* HDF5Group::getDataset(H5::Group* parent, const char* name) 
{
	if (parent==NULL)	throw std::invalid_argument("HDF5 parent group is NULL");	
	if (name==NULL)		throw std::invalid_argument("name is NULL");		

	iterate_dataset_data data(name);

	herr_t result = H5Literate(parent->getId(), H5_INDEX_NAME, H5_ITER_INC, NULL, find_dataset, &data);

	if (result < 0)
	{
		std::ostringstream ss; ss << "H5Literate("<<parent->getId()<<",...,"<<name<<") failed: " << result;
		throw OdimH5HDF5LibException(ss.str());
	}

	if (data.found)
	{
		try
		{
			return new H5::DataSet(parent->openDataSet(name) );	
		}
		catch (H5::Exception& h5e)
		{					
			std::ostringstream ss; ss << "Cannot open dataset " << name;
			throw OdimH5HDF5LibException(ss.str(), h5e);
		}
	}

	return NULL;
}

/*===========================================================================*/

void HDF5Group::copyAttributes(H5::Group* src, H5::Group* dst)
{	
	std::set<std::string> names;
	copyAttributes(src, dst, names);
	//H5::Attribute*	srcAttr	= NULL;
	//H5::Attribute*	dstAttr	= NULL;

	//try
	//{
	//	std::vector<char> buff;

	//	int count = src->getNumAttrs();
	//	for (int i=0; i<count; i++)
	//	{
	//		srcAttr	= new H5::Attribute(src->openAttribute(i));

	//		hsize_t storagesize = srcAttr->getStorageSize();

	//		if (storagesize > buff.size())
	//			buff.resize((size_t)storagesize);

	//		srcAttr->read(srcAttr->getDataType(), &(buff[0]));
	//		
	//		std::string name = HDF5Attribute::getName(srcAttr);

	//		HDF5Attribute::remove(dst, name.c_str());

	//		dstAttr	= new H5::Attribute(dst->createAttribute(name.c_str(), srcAttr->getDataType(), srcAttr->getSpace()));

	//		dstAttr->write(dstAttr->getDataType(), &(buff[0]));

	//		delete srcAttr; srcAttr	= NULL;
	//		delete dstAttr; dstAttr = NULL;
	//	}
	//}
	//catch (H5::Exception& h5e)
	//{
	//	delete srcAttr;
	//	delete dstAttr;
	//	throw OdimH5HDF5LibException("Error coping attributes", h5e);
	//}
	//catch (...)
	//{
	//	delete srcAttr;
	//	delete dstAttr;
	//	throw;
	//}
}

void HDF5Group::copyAttributes(H5::Group* src, H5::Group* dst, const std::set<std::string>& names)
{	
	H5::Attribute*	srcAttr	= NULL;
	H5::Attribute*	dstAttr	= NULL;

	try
	{
		std::vector<char> buff;

		int count = src->getNumAttrs();
		for (int i=0; i<count; i++)
		{
			srcAttr	= new H5::Attribute(src->openAttribute(i));

			std::string name = HDF5Attribute::getName(srcAttr);

			if (names.size())				// se sono specificati degli attributi
				if (names.find(name) == names.end())	//se non l'attribut non e' tra questi
				{
					delete srcAttr; 
					srcAttr	= NULL;
					continue;			//saltalo
				}

			hsize_t storagesize = srcAttr->getStorageSize();

			if (storagesize > buff.size())
				buff.resize((size_t)storagesize);

			srcAttr->read(srcAttr->getDataType(), &(buff[0]));
			

			HDF5Attribute::remove(dst, name.c_str());

			dstAttr	= new H5::Attribute(dst->createAttribute(name.c_str(), srcAttr->getDataType(), srcAttr->getSpace()));

			dstAttr->write(dstAttr->getDataType(), &(buff[0]));

			delete srcAttr; srcAttr	= NULL;
			delete dstAttr; dstAttr = NULL;
		}
		// numero degli object: src->getNumObjs()
		// verificare se l'i-esimo oggetto è un dataset: src->getObjTypeByIdx(i) == H5G_DATASET
		// estraggo il dataset: srcDs = src->openDataset(src->getObjNameByIdx(i))
		// creo un nuovo dataset a partire dal dataset in maniera analoga
		// all'attribute:
		// dstDs = new H5::Dataset(dst->createDataset(name.c_str(), srcDs->getDataType(), srcDs->getSpace()))
		// e poi la write
	}
	catch (H5::Exception& h5e)
	{
		delete srcAttr;
		delete dstAttr;
		throw OdimH5HDF5LibException("Error coping attributes", h5e);
	}
	catch (...)
	{
		delete srcAttr;
		delete dstAttr;
		throw;
	}
}


/*===========================================================================*/
/* HDF5 ATOM TYPE */
/*===========================================================================*/

H5::AtomType HDF5AtomType::fromDataType(const H5::DataType& type)
{
	#define CASE(spectype)	if (type == H5::PredType::spectype) return H5::PredType::spectype;

	CASE(STD_I8BE)
	CASE(STD_I8LE)
	CASE(STD_I16BE)
	CASE(STD_I16LE)
	CASE(STD_I32BE)
	CASE(STD_I32LE)
	CASE(STD_I64BE)
	CASE(STD_I64LE)
	CASE(STD_U8BE)
	CASE(STD_U8LE)
	CASE(STD_U16BE)
	CASE(STD_U16LE)
	CASE(STD_U32BE)
	CASE(STD_U32LE)
	CASE(STD_U64BE)
	CASE(STD_U64LE)
	CASE(STD_B8BE)
	CASE(STD_B8LE)
	CASE(STD_B16BE)
	CASE(STD_B16LE)
	CASE(STD_B32BE)
	CASE(STD_B32LE)
	CASE(STD_B64BE)
	CASE(STD_B64LE)
	CASE(STD_REF_OBJ)
	CASE(STD_REF_DSETREG)

	CASE(C_S1)
	CASE(FORTRAN_S1)

	CASE(IEEE_F32BE)
	CASE(IEEE_F32LE)
	CASE(IEEE_F64BE)
	CASE(IEEE_F64LE)

	CASE(UNIX_D32BE)
	CASE(UNIX_D32LE)
	CASE(UNIX_D64BE)
	CASE(UNIX_D64LE)

	CASE(INTEL_I8)
	CASE(INTEL_I16)
	CASE(INTEL_I32)
	CASE(INTEL_I64)
	CASE(INTEL_U8)
	CASE(INTEL_U16)
	CASE(INTEL_U32)
	CASE(INTEL_U64)
	CASE(INTEL_B8)
	CASE(INTEL_B16)
	CASE(INTEL_B32)
	CASE(INTEL_B64)
	CASE(INTEL_F32)
	CASE(INTEL_F64)

	CASE(ALPHA_I8)
	CASE(ALPHA_I16)
	CASE(ALPHA_I32)
	CASE(ALPHA_I64)
	CASE(ALPHA_U8)
	CASE(ALPHA_U16)
	CASE(ALPHA_U32)
	CASE(ALPHA_U64)
	CASE(ALPHA_B8)
	CASE(ALPHA_B16)
	CASE(ALPHA_B32)
	CASE(ALPHA_B64)
	CASE(ALPHA_F32)
	CASE(ALPHA_F64)

	CASE(MIPS_I8)
	CASE(MIPS_I16)
	CASE(MIPS_I32)
	CASE(MIPS_I64)
	CASE(MIPS_U8)
	CASE(MIPS_U16)
	CASE(MIPS_U32)
	CASE(MIPS_U64)
	CASE(MIPS_B8)
	CASE(MIPS_B16)
	CASE(MIPS_B32)
	CASE(MIPS_B64)
	CASE(MIPS_F32)
	CASE(MIPS_F64)

	CASE(NATIVE_CHAR)
	CASE(NATIVE_SCHAR)
	CASE(NATIVE_UCHAR)
	CASE(NATIVE_SHORT)
	CASE(NATIVE_USHORT)
	CASE(NATIVE_INT)
	CASE(NATIVE_UINT)
	CASE(NATIVE_LONG)
	CASE(NATIVE_ULONG)
	CASE(NATIVE_LLONG)
	CASE(NATIVE_ULLONG)
	CASE(NATIVE_FLOAT)
	CASE(NATIVE_DOUBLE)
	CASE(NATIVE_LDOUBLE)
	CASE(NATIVE_B8)
	CASE(NATIVE_B16)
	CASE(NATIVE_B32)
	CASE(NATIVE_B64)
	CASE(NATIVE_OPAQUE)
	CASE(NATIVE_HSIZE)
	CASE(NATIVE_HSSIZE)
	CASE(NATIVE_HERR)
	CASE(NATIVE_HBOOL)

	CASE(NATIVE_INT8)
	CASE(NATIVE_UINT8)
	CASE(NATIVE_INT16)
	CASE(NATIVE_UINT16)
	CASE(NATIVE_INT32)
	CASE(NATIVE_UINT32)
	CASE(NATIVE_INT64)
	CASE(NATIVE_UINT64)

	#undef CASE

	throw OdimH5UnsupportedException("Unknown H5::DataType");	
}

/*===========================================================================*/

}














































