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

#include "odimh5v20_dump.hpp"

#include <iostream>
#include <memory>
#include <vector>
#include <iomanip>

#include <radarlib/time.hpp>
#include <radarlib/string.hpp>
#include <radarlib/math.hpp>

namespace OdimH5v20 {

/*===========================================================================*/
/* DUMPER */
/*===========================================================================*/

OdimObjectDumper::OdimObjectDumper()
{		
}

OdimObjectDumper::~OdimObjectDumper()
{
}

void OdimObjectDumper::dump(OdimObject* object)
{
	dump(object, std::cout);
}

void OdimObjectDumper::dump(OdimObject* object, std::ostream& out)
{
	dump(object, &(out));
}

void OdimObjectDumper::dump(OdimObject* object, std::ostream* out)
{
	this->out = out;

	std::string conventions = object->getConventions();

	prefix(0) << "Conventions: " << conventions << std::endl;
	
	if (conventions != CONVENTIONS_ODIM_H5_V2_0)
		throw OdimH5FormatException("Unknown /Conventions '" + conventions + "'");
	
	prefix(0) << "ROOT" << std::endl;

	dumpMetadata(1, object->getWhat(), GROUP_WHAT);
	dumpMetadata(1, object->getWhere(), GROUP_WHERE);
	dumpMetadata(1, object->getHow(), GROUP_HOW);		

	int count = 0;
	for (int i=0; count<object->getDatasetCount(); i++)
	{
		OdimDataset* datasetptr = object->getDataset(i);		

		if (datasetptr == NULL)
			continue;

		count++;

		prefix(1) << "+ DATASETS " << i << std::endl;

		std::auto_ptr<OdimDataset> dataset( datasetptr );		

		dumpMetadata(2, dataset->getWhat(),  GROUP_WHAT);
		dumpMetadata(2, dataset->getWhere(), GROUP_WHERE);
		dumpMetadata(2, dataset->getHow(),   GROUP_HOW);


		int datacount = 0;
		for (int i=0; datacount<dataset->getDataCount(); i++)
		{
			OdimData* dataptr = dataset->getData(i);

			if (dataptr == NULL)
				continue;

			datacount++;

			prefix(2) << "+ DATA " << i << std::endl;

			std::auto_ptr<OdimData> data(dataptr); 
			dumpMetadata(3, data->getWhat(),  GROUP_WHAT);
			dumpMetadata(3, data->getWhere(), GROUP_WHERE);
			dumpMetadata(3, data->getHow(),   GROUP_HOW);

			dumpDataset(3, data.get());
		}
	}
}

/*===========================================================================*/


void OdimObjectDumper::dumpMetadata(int level, MetadataGroup* metadata, const std::string& name)
{
	H5::H5Object*		obj		= metadata->getH5Object();
	int			count		= obj->getNumAttrs();
	H5::Attribute*		h5attr		= NULL;

	prefix(level) << "+ " << name << ":" << std::endl;

	for (int i=0; i<count; i++)
	{
		h5attr	= new H5::Attribute(obj->openAttribute(i));

		char name[200+1];	
		size_t len = H5Aget_name(h5attr->getId(), 200, name);
		name[len] = '\0';

		prefix(level) << "|   - " << std::setw(30) << std::left << name << ": ";

		switch (h5attr->getTypeClass())
		{
		case H5T_INTEGER:	*out << "[INT]  " << metadata->getLong(name);	break;
		case H5T_FLOAT:		*out << "[REAL] " << metadata->getDouble(name);	break;
		case H5T_STRING:	*out << "[STR]  " << metadata->getStr(name);	break;
		default:		*out << "<TIPO ATTRIBUTO NON SUPPORTATO>"; break;
		}

		*out << std::endl;

		delete h5attr;
	}	
}

static const char* getTypeName(H5::DataType type)
{
	if      (type == H5::PredType::NATIVE_UINT8)	return "UINT8";
	else if (type == H5::PredType::NATIVE_INT8)	return "INT8";
	else if (type == H5::PredType::NATIVE_UINT16)	return "UINT16";
	else if (type == H5::PredType::NATIVE_INT16)	return "INT16";
	else if (type == H5::PredType::NATIVE_UINT32)	return "INT32";
	else if (type == H5::PredType::NATIVE_INT32)	return "UINT32";
	else if (type == H5::PredType::NATIVE_FLOAT)	return "FLOAT";
	else if (type == H5::PredType::NATIVE_DOUBLE)	return "DOUBLE";
	else return "<TYPE NOT SUPPORTED>";
}

void OdimObjectDumper::dumpDataset(int level, OdimData* data)
{
	int height;
	int width;
	H5::DataType type;

	type = data->getDataType();
	
	data->getDataDimension(&height, &width);
	
	prefix(level) << "+ data ("<<height<<" x "<<width<<") " << getTypeName(type) << std::endl;

	if (height==0 || width==0)
		return;

	std::vector<char> buffer_(height * width * type.getSize());	
	void* buffer = &(buffer_[0]);

	data->readData(buffer);

	double nodata	= data->getWhat()->getDouble(ATTRIBUTE_WHAT_NODATA, 0);
	double undetect = data->getWhat()->getDouble(ATTRIBUTE_WHAT_UNDETECT, 0);

	level++;

	if      (type == H5::PredType::NATIVE_UINT8)	dumpIntBuffer<unsigned char>	(level, (unsigned char*)	buffer, (unsigned char)undetect, (unsigned char)nodata, height, width);
	else if (type == H5::PredType::NATIVE_INT8)	dumpIntBuffer<char>		(level, (char*)			buffer, (char)undetect,		(char)nodata, height, width);
	else if (type == H5::PredType::NATIVE_UINT16)	dumpIntBuffer<unsigned short>	(level, (unsigned short*)	buffer, (unsigned short)undetect, (unsigned short)nodata, height, width);
	else if (type == H5::PredType::NATIVE_INT16)	dumpIntBuffer<short>		(level, (short*)		buffer, (short)undetect,	(short)nodata, height, width);
	else if (type == H5::PredType::NATIVE_INT32)	dumpIntBuffer<unsigned int>	(level, (unsigned int*)		buffer, (unsigned int)undetect, (unsigned int)nodata, height, width);
	else if (type == H5::PredType::NATIVE_UINT32)	dumpIntBuffer<int>		(level, (int*)			buffer, (int)undetect,		(int)nodata, height, width);
	else if (type == H5::PredType::NATIVE_FLOAT)	dumpFloatBuffer<float>		(level, (float*)		buffer, (float)undetect,	(float)nodata, height, width);
	else if (type == H5::PredType::NATIVE_DOUBLE)	dumpFloatBuffer<double>		(level, (double*)		buffer, (double)undetect,	(double)nodata, height, width);
	else {
		std::ostringstream ss; 
		ss << "Dump for datasets with datatype class " << type.getClass() << " not implemented";
		throw std::runtime_error(ss.str());
	}
}

std::ostream& OdimObjectDumper::prefix(int level)
{
	for (int i=0; i<level; i++)
		*out << "    "; 	
	return *out;
}


/*===========================================================================*/

}





















































