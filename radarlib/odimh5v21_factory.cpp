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

#include <radarlib/odimh5v21_factory.hpp>

#include <radarlib/debug.hpp>

namespace OdimH5v21 {

/*===========================================================================*/

OdimFactory::OdimFactory()
{
}

OdimFactory::~OdimFactory()
{
	try
	{
		/* quando si chiude una factory si pulisce la memoria */
		/* per obbligare HDF5 a chiudere quello che va chiuso */
		H5::H5Library::garbageCollect();
	}
	catch (...)
	{
	}
}

OdimObject* OdimFactory::create(const std::string& path)
{
	H5::H5File*	file	= NULL;
	OdimObject*	object	= NULL;
	try
	{
		file	= HDF5File::open(path, H5F_ACC_TRUNC );	
		object	= new OdimObject(file);
		file	= NULL;
		object->setMandatoryInformations();
		return object;
	}
	catch (...)
	{
		delete object;
		delete file;
		throw;
	}	
}

H5::H5File* OdimFactory::openOdimFile(const std::string& path, int h5flags, std::string& objtype)
{
	H5::H5File*		file		= NULL;
	H5::Group*		root		= NULL;
	H5::Group*		what		= NULL;		

	try
	{
		file	= HDF5File::open(path, h5flags);
		
		root	= HDF5File::getRoot(file);
		
		std::string conventions = MetadataGroup::getConventions(root);

		if (conventions != CONVENTIONS_ODIM_H5_V2_1)
			throw OdimH5UnknownFormatException("Cannot open file! File use unknown convertions: " + conventions);

		what = HDF5Group::getChild(root, GROUP_WHAT);
		if (what == NULL)
			throw OdimH5MissingGroupException("File does not have WHAT group!");

		objtype = HDF5Attribute::getStr(what, ATTRIBUTE_WHAT_OBJECT);

		delete root;
		delete what;

		return file;
	}
	catch (H5::Exception& h5e)
	{
		delete what;
		delete root;
		delete file;
		throw OdimH5HDF5LibException(h5e);
	}
	catch (...)
	{
		delete what;
		delete root;
		delete file;
		throw;
	}
}

OdimObject* OdimFactory::open(const std::string& path)
{
	return open(path, H5F_ACC_RDWR);
}

OdimObject* OdimFactory::open(const std::string& path, int h5flags) 
{
	H5::H5File*	file		= NULL;
	OdimObject*	object		= NULL;
	std::string	objecttype;

	try
	{
		file = openOdimFile(path, h5flags, objecttype);
		
		if (objecttype == OBJECT_PVOL)
		{			
			object = createPolarVolume(file);
		}
		else if (objecttype == OBJECT_IMAGE)
		{			
			object = createImageObject(file);
		}
		else if (objecttype == OBJECT_COMP)
		{			
			object = createCompObject(file);
		}
		else if (objecttype == OBJECT_XSEC)
		{			
			object = createXsecObject(file);
		}
		else
		{
			object = new OdimObject(file);
		}

		file = NULL;
		object->checkMandatoryInformations();
		return object;
	}
	catch (...)
	{
		delete file;
		delete object;
		throw;
	}
}

PolarVolume* OdimFactory::createPolarVolume(H5::H5File* file)
{
	return new PolarVolume(file);
}

PolarVolume* OdimFactory::createPolarVolume(const std::string& path) 
{
	H5::H5File*	file	= NULL;
	PolarVolume*	volume	= NULL;
	try
	{
		file	= HDF5File::open(path, H5F_ACC_TRUNC);	
		volume	= createPolarVolume(file);
		file	= NULL;
		volume->setMandatoryInformations();
		return volume;
	}
	catch (...)
	{
		delete volume;
		delete file;
		throw;
	}	
}

ImageObject * OdimFactory::createImageObject(H5::H5File* file)
{
	return new ImageObject(file);
}

ImageObject* OdimFactory::createImageObject(const std::string& path)
{
	H5::H5File*	file	= NULL;
	ImageObject*	image	= NULL;
	try
	{
		file	= HDF5File::open(path, H5F_ACC_TRUNC);	
		image	= createImageObject(file);
		file	= NULL;
		image->setMandatoryInformations();
		return image;
	}
	catch (...)
	{
		delete image;
		delete file;
		throw;
	}	
}

CompObject * OdimFactory::createCompObject(H5::H5File* file)
{
	return new CompObject(file);
}

CompObject* OdimFactory::createCompObject(const std::string& path)
{
	H5::H5File*	file	= NULL;
	CompObject*	comp	= NULL;
	try
	{
		file	= HDF5File::open(path, H5F_ACC_TRUNC);	
		comp	= createCompObject(file);
		file	= NULL;
		comp->setMandatoryInformations();
		return comp;
	}
	catch (...)
	{
		delete comp;
		delete file;
		throw;
	}	
}

XsecObject * OdimFactory::createXsecObject(H5::H5File* file)
{
	return new XsecObject(file);
}

XsecObject* OdimFactory::createXsecObject(const std::string& path)
{
	H5::H5File*	file	= NULL;
	XsecObject*	xsec	= NULL;
	try
	{
		file	= HDF5File::open(path, H5F_ACC_TRUNC);	
		xsec	= createXsecObject(file);
		file	= NULL;
		xsec->setMandatoryInformations();
		return xsec;
	}
	catch (...)
	{
		delete xsec;
		delete file;
		throw;
	}	
}

PolarVolume* OdimFactory::openPolarVolume(const std::string& path) 
{
	return openPolarVolume(path, H5F_ACC_RDWR);
}

PolarVolume* OdimFactory::openPolarVolume(const std::string& path, int h5flags)
{
	H5::H5File*	file	= NULL;
	PolarVolume*	volume	= NULL;
	try
	{		
		file	= HDF5File::open(path, h5flags);	
		volume	= createPolarVolume(file);
		file	= NULL;
		volume->checkMandatoryInformations();
		return volume;
	}
	catch (...)
	{	
		delete volume;
		delete file;
		throw;
	}
}

ImageObject* OdimFactory::openImageObject(const std::string& path) 
{
	return openImageObject(path, H5F_ACC_RDWR);
}

ImageObject* OdimFactory::openImageObject(const std::string& path, int h5flags)
{
	H5::H5File*	file	= NULL;
	ImageObject*	image	= NULL;
	try
	{		
		file	= HDF5File::open(path, h5flags);	
		image	= createImageObject(file);
		file	= NULL;
		image->checkMandatoryInformations();
		return image;
	}
	catch (...)
	{	
		delete image;
		delete file;
		throw;
	}
}

CompObject* OdimFactory::openCompObject(const std::string& path) 
{
	return openCompObject(path, H5F_ACC_RDWR);
}

CompObject* OdimFactory::openCompObject(const std::string& path, int h5flags)
{
	H5::H5File*	file	= NULL;
	CompObject*	comp	= NULL;
	try
	{		
		file	= HDF5File::open(path, h5flags);	
		comp	= createCompObject(file);
		file	= NULL;
		comp->checkMandatoryInformations();
		return comp;
	}
	catch (...)
	{	
		delete comp;
		delete file;
		throw;
	}
}

XsecObject* OdimFactory::openXsecObject(const std::string& path) 
{
	return openXsecObject(path, H5F_ACC_RDWR);
}

XsecObject* OdimFactory::openXsecObject(const std::string& path, int h5flags)
{
	H5::H5File*	file	= NULL;
	XsecObject*	xsec	= NULL;
	try
	{		
		file	= HDF5File::open(path, h5flags);	
		xsec	= createXsecObject(file);
		file	= NULL;
		xsec->checkMandatoryInformations();
		return xsec;
	}
	catch (...)
	{	
		delete xsec;
		delete file;
		throw;
	}
}

OdimObjectDumper* OdimFactory::getDumper() 
{	
	return new OdimH5v21::OdimObjectDumper();
}

/*===========================================================================*/


}


