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
 *  \brief OdimH5 classes to create OdimH5 objects dumps 
 */

#ifndef __RADAR_ODIMH5V20_DUMP_HPP__
#define __RADAR_ODIMH5V20_DUMP_HPP__

#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>

#include <radarlib/math.hpp>
#include <radarlib/odimh5v20_classes.hpp>

namespace OdimH5v20 {

/*===========================================================================*/
/* DUMPER */
/*===========================================================================*/

/*! 
 * \brief OdimH5 object dumper
 * 
 * \n This class allow users to create a textual representation of a OdimObject writting it to standard output
 * 
 * \see OdimObject
 */
class RADAR_API OdimObjectDumper
{
public:
	virtual ~OdimObjectDumper();	
	
	/*!
	 * \brief Dump object informations to standard output
	 * 
	 * This class write object informations using a tree layout
	 * \param object		the object to dump
	 * \throws OdimH5Exception	Every HDF5 internal exception is wrapped with a OdimH5Exception
	 * \see OdimObject
	 */
	virtual void dump(OdimObject* object);

	/*!
	 * \brief Dump object informations to a stream
	 * 
	 * This class write object informations using a tree layout
	 * \param object		the object to dump
	 * \param out			the reference to the stream to use
	 * \throws OdimH5Exception	Every HDF5 internal exception is wrapped with a OdimH5Exception
	 * \see OdimObject
	 */
	virtual void dump(OdimObject* object, std::ostream& out);

	/*!
	 * \brief Dump object informations to a stream
	 * 
	 * This class write object informations using a tree layout
	 * \param object		the object to dump
	 * \param out			the pointer to the stream to use
	 * \throws OdimH5Exception	Every HDF5 internal exception is wrapped with a OdimH5Exception
	 * \see OdimObject
	 */
	virtual void dump(OdimObject* object, std::ostream* out);
		
protected:
	int level;		/* current indendation level for output formatting */
	std::ostream* out;	/* current output stream  */
	
	virtual void dumpMetadata(int level, MetadataGroup* metadata, const std::string& name);
	virtual void dumpDataset(int level, OdimData* data);
	std::ostream& prefix(int level);

	template <class T> void dumpIntBuffer(int level, const T* values, const T undetect, const T nodata, int rows, int cols)
	{
		for (int y=0; y<rows; y++)
		{
			prefix(level) << std::setw(3) << y << ": ";	
			for (int x=0; x<cols; x++)
			{
				T value = values[y * cols + x];
				if (value == undetect)		*out << "_ ";
				else if (value == nodata)	*out << ". ";
				else				*out << value << " ";
			}
			*out << std::endl;
		}	
	}

	template <class T> void dumpFloatBuffer(int level, const T* values, const T undetect, const T nodata, int rows, int cols)
	{
		for (int y=0; y<rows; y++)
		{
			prefix(level) << std::setw(3) << y << ": ";	
			for (int x=0; x<cols; x++)
			{		
				T value = values[y * cols + x];
				if (value == undetect)			*out << "_ ";
				else if (value == nodata)		*out << ". ";
				else if (Radar::math::isnan(value))	*out << "N " << " ";
				else					*out << value << " ";
			}
			*out << std::endl;
		}	
	}

protected:
		
	
	/* default constructor is not public in order to deny users from directly creating dumpers */
	/* only class factories are allowed to create instances */
	OdimObjectDumper();
	friend class OdimFactory;

};

/*===========================================================================*/

}

#endif




















































//	virtual void dumpFileConventions		(OdimObject* object);	
//	virtual void dumpPolarVolume			(PolarVolume* volume);	
//	virtual void dumpPolarVolumeWhat		(PolarVolume* volume);
//	virtual void dumpPolarVolumeWhere		(PolarVolume* volume);
//	virtual void dumpPolarVolumeHow			(PolarVolume* volume);
//	virtual void dumpPolarVolumeScans		(PolarVolume* volume);
//
//	virtual void dumpPolarScan			(PolarScan* scan);
//	virtual void dumpPolarScanWhat			(PolarScan* scan);
//	virtual void dumpPolarScanWhere			(PolarScan* scan);
//	virtual void dumpPolarScanHow			(PolarScan* scan);
//	virtual void dumpPolarScanDatas			(PolarScan* scan);
//
//	virtual void dumpPolarScanData			(PolarScan* scan, PolarScanData* scanData);
//	virtual void dumpPolarScanDataWhat		(PolarScan* scan, PolarScanData* scanData);
//	virtual void dumpPolarScanDataWhere		(PolarScan* scan, PolarScanData* scanData);
//	virtual void dumpPolarScanDataHow		(PolarScan* scan, PolarScanData* scanData);
//	virtual void dumpPolarScanDataMatrix		(PolarScan* scan, PolarScanData* scanData);
//
//	virtual void dumpGroupName(int level, const char* name);
//	virtual void dumpAttribute(int level, const char* name, bool value);
//	virtual void dumpAttribute(int level, const char* name, int value);	
//	virtual void dumpAttribute(int level, const char* name, int64_t value);	
//	virtual void dumpAttribute(int level, const char* name, double value);
//	virtual void dumpAttribute(int level, const char* name, const std::string& value);	
//	virtual void dumpAttribute(int level, const char* name, const char* value);		
//	virtual void dumpAttribute(int level, const char* name, const std::vector<int64_t>& value);
//	virtual void dumpAttribute(int level, const char* name, const std::vector<double>& value);
//	virtual void dumpAttribute(int level, const char* name, const std::vector<std::string>& value);
