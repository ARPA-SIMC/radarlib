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

#include <radarlib/odimh5v21_metadata.hpp>

#include <iostream>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <cstdio>
#include <vector>

#include <radarlib/time.hpp>
#include <radarlib/string.hpp>
#include <radarlib/odimh5v21_format.hpp>

namespace OdimH5v21
{

/*===========================================================================*/
/* FUNZIONI DI COMODO */
/*===========================================================================*/

template <class TINT> static std::ostringstream& makeIntSeq(std::ostringstream& result, const std::vector<TINT>& value)
{	
	for (size_t i=0; i<value.size(); i++)
	{
		if (i) result << ",";
		result << value[i];
	}
	return result;	
}

template <class TREAL> static std::ostringstream& makeRealSeq(std::ostringstream& result, const std::vector<TREAL>& value, int precision)
{	
	if (precision)
		result.precision(precision);
	for (size_t i=0; i<value.size(); i++)
	{
		if (i) result << ",";
		result << value[i];
	}
	return result;	
}

static std::vector<std::string>& getStrSeq_(H5::Group* group, const char* name, bool mandatory, std::vector<std::string>& result)
{
	std::string str = mandatory ? HDF5Attribute::getStr(group, name) : HDF5Attribute::getStr(group, name, "");
	Radar::stringutils::split(str, result, ",");
	return result;
}

template <class T> static std::vector<T>& getSeq_(H5::Group* group, const char* name, bool mandatory, std::vector<T>& result, const char* typeName)
{
	std::vector<std::string> strings;
	getStrSeq_(group, name, mandatory, strings);	
	result.resize(strings.size());
	for (size_t i=0; i<strings.size(); i++)
	{
		try
		{
			result[i] = Radar::stringutils::parse<T>(strings[i], typeName);
		}
		catch (std::invalid_argument& e)
		{
			throw OdimH5FormatException("Cannot read "+std::string(name)+" attribute as "+std::string(typeName)+" sequence! " + e.what());
		}
	}
	return result;
}

template<class T> static std::vector<T> getSimpleArray(H5::Group* group, const char* name, bool mandatory, std::vector<T>& result)
{
	H5::DataSet* dataset = HDF5Group::getDataset(group, name);
	// TODO: mandatory
	// TODO: dataset->getSpace().getSimpleExtentDims(sizes) == 1
	hssize_t size = dataset->getSpace().getSimpleExtentNpoints();
	result.resize(size);
	dataset->read(&(result[0]), dataset->getDataType(), dataset->getSpace());

	return result;;
}

/*===========================================================================*/
/* METADATA GROUP */
/*===========================================================================*/

MetadataGroup::MetadataGroup(H5::Group* group)
:group(group) 
{ 
}

MetadataGroup::~MetadataGroup() 
{ 
	delete group;
}

int		MetadataGroup::getCount		()					{ return group->getNumAttrs(); }

H5::Attribute*	MetadataGroup::getH5Attribute	(const char* name, bool mandatory)	{ return HDF5Attribute::get(group, name, mandatory);	}

bool		MetadataGroup::exists		(const char* name)			{ return HDF5Attribute::exists(group, name);	}
void		MetadataGroup::remove		(const char* name)			{ HDF5Attribute::remove(group, name);		}

/*===========================================================================*/
/* scalari */
/*===========================================================================*/

void		MetadataGroup::set		(const char* name, bool			value)	{ HDF5Attribute::set(group, name, value ? TRUESTR : FALSESTR );	}
void		MetadataGroup::set		(const char* name, char			value)	{ HDF5Attribute::set(group, name, (int64_t)value);	}
void		MetadataGroup::set		(const char* name, unsigned char	value)	{ HDF5Attribute::set(group, name, (int64_t)value);	}
void		MetadataGroup::set		(const char* name, short		value)	{ HDF5Attribute::set(group, name, (int64_t)value);	}
void		MetadataGroup::set		(const char* name, unsigned short	value)	{ HDF5Attribute::set(group, name, (int64_t)value);	}
void		MetadataGroup::set		(const char* name, int			value)	{ HDF5Attribute::set(group, name, (int64_t)value);	}
void		MetadataGroup::set		(const char* name, unsigned int		value)	{ HDF5Attribute::set(group, name, (int64_t)value);	}
void		MetadataGroup::set		(const char* name, int64_t		value)	{ HDF5Attribute::set(group, name,          value);	}
void		MetadataGroup::set		(const char* name, float		value)	{ HDF5Attribute::set(group, name, (double) value);	}
void		MetadataGroup::set		(const char* name, double		value)	{ HDF5Attribute::set(group, name, value);		}
void		MetadataGroup::set		(const char* name, const char*		value)	{ HDF5Attribute::set(group, name, value);	}
void		MetadataGroup::set		(const char* name, const std::string&	value)	{ HDF5Attribute::set(group, name, value);	}

void		MetadataGroup::set		(const char* name, const std::stringstream&	value) { HDF5Attribute::set(group, name, value.str()); }
void		MetadataGroup::set		(const char* name, const std::ostringstream&	value) { HDF5Attribute::set(group, name, value.str()); }	

/*===========================================================================*/
/* get di scalari */
/*===========================================================================*/

bool		MetadataGroup::getBool		(const char* name)				{ return		HDF5Attribute::getStr(group, name) == TRUESTR;		}
bool		MetadataGroup::getBool		(const char* name, bool			value)	{ return		HDF5Attribute::getStr(group, name, (value ? TRUESTR : FALSESTR)) == TRUESTR;	}
char		MetadataGroup::getChar		(const char* name)				{ return (char)		HDF5Attribute::getLong(group, name);				}
char		MetadataGroup::getChar		(const char* name, char			value)	{ return (char)		HDF5Attribute::getLong(group, name, (int64_t)value);		}
unsigned char	MetadataGroup::getUChar		(const char* name)				{ return (unsigned char)HDF5Attribute::getLong(group, name);				}
unsigned char	MetadataGroup::getUChar		(const char* name, unsigned char	value)	{ return (unsigned char)HDF5Attribute::getLong(group, name, (int64_t)value);		}
short		MetadataGroup::getShort		(const char* name)				{ return (short)	HDF5Attribute::getLong(group, name);				}
short		MetadataGroup::getShort		(const char* name, short		value)	{ return (short)	HDF5Attribute::getLong(group, name, (int64_t)value);		}
unsigned short	MetadataGroup::getUShort	(const char* name)				{ return (unsigned short)HDF5Attribute::getLong(group, name);				}
unsigned short	MetadataGroup::getUShort	(const char* name, unsigned short	value)	{ return (unsigned short)HDF5Attribute::getLong(group, name, (int64_t)value);		}
int		MetadataGroup::getInt		(const char* name)				{ return (int)		HDF5Attribute::getLong(group, name);				}
int		MetadataGroup::getInt		(const char* name, int			value)	{ return (int)		HDF5Attribute::getLong(group, name, (int64_t)value);		}
unsigned int	MetadataGroup::getUInt		(const char* name)				{ return (unsigned int)	HDF5Attribute::getLong(group, name);				}
unsigned int	MetadataGroup::getUInt		(const char* name, unsigned int		value)	{ return (unsigned int)	HDF5Attribute::getLong(group, name, (int64_t)value);		}
int64_t		MetadataGroup::getLong		(const char* name)				{ return		HDF5Attribute::getLong(group, name);			}
int64_t		MetadataGroup::getLong		(const char* name, int64_t		value)	{ return		HDF5Attribute::getLong(group, name, value);		}
time_t		MetadataGroup::getTimeT		(const char* name)				{ return (time_t)	HDF5Attribute::getLong(group, name);				}
time_t		MetadataGroup::getTimeT		(const char* name, time_t		value)	{ return (time_t)	HDF5Attribute::getLong(group, name, (int64_t)value);		}
float		MetadataGroup::getFloat		(const char* name)				{ return (float)	HDF5Attribute::getDouble(group, name);			}
float		MetadataGroup::getFloat		(const char* name, float		value)	{ return (float)	HDF5Attribute::getDouble(group, name, (double)value);		}
double		MetadataGroup::getDouble	(const char* name)				{ return		HDF5Attribute::getDouble(group, name);		}
double		MetadataGroup::getDouble	(const char* name, double		value)	{ return		HDF5Attribute::getDouble(group, name, value);	}
std::string	MetadataGroup::getStr		(const char* name)				{ return		HDF5Attribute::getStr(group, name);			}
std::string	MetadataGroup::getStr		(const char* name, const std::string& 	value)	{ return		HDF5Attribute::getStr(group, name, value);		}

/*===========================================================================*/
/* sequenze di scalari */
/*===========================================================================*/

void	MetadataGroup::set	(const char* name, const std::vector<bool>&		value) 
{ 
	std::ostringstream ss;
	for (size_t i=0; i<value.size(); i++)
	{
		if (i) ss << ",";
		ss << (value[i] ? TRUESTR : FALSESTR);
	}
	set(name, ss);
}
void	MetadataGroup::set	(const char* name, const std::vector<char>&		value) 
{ 
	std::ostringstream ss;
	for (size_t i=0; i<value.size(); i++)
	{
		if (i) ss << ",";
		ss << (int)value[i];
	}
	set(name, ss); 
}
void	MetadataGroup::set	(const char* name, const std::vector<unsigned char>&	value) { std::ostringstream ss; set(name, makeIntSeq<unsigned char>(ss, value));	}
void	MetadataGroup::set	(const char* name, const std::vector<short>&		value) { std::ostringstream ss; set(name, makeIntSeq<short>(ss, value));		}
void	MetadataGroup::set	(const char* name, const std::vector<unsigned short>&	value) { std::ostringstream ss; set(name, makeIntSeq<unsigned short>(ss, value));	}
void	MetadataGroup::set	(const char* name, const std::vector<int>&		value) { std::ostringstream ss; set(name, makeIntSeq<int>(ss, value));			}
void	MetadataGroup::set	(const char* name, const std::vector<unsigned int>&	value) { std::ostringstream ss; set(name, makeIntSeq<unsigned int>(ss, value));		}
void	MetadataGroup::set	(const char* name, const std::vector<int64_t>&		value) { std::ostringstream ss; set(name, makeIntSeq<int64_t>(ss, value));			}
void	MetadataGroup::set	(const char* name, const std::vector<float>&		value, int precision) { std::ostringstream ss; set(name, makeRealSeq<float>(ss, value, precision));	}
void	MetadataGroup::set	(const char* name, const std::vector<double>&		value, int precision) { std::ostringstream ss; set(name, makeRealSeq<double>(ss, value, precision));	}
void	MetadataGroup::set	(const char* name, const std::vector<char*>&		value) 
{ 
	std::ostringstream ss;
	for (size_t i=0; i<value.size(); i++)
	{
		if (i) ss << ",";
		ss << value[i];
	}
	set(name, ss); 
}
void	MetadataGroup::set	(const char* name, const std::vector<std::string>&	value) 
{ 
	std::ostringstream ss;
	for (size_t i=0; i<value.size(); i++)
	{
		if (i) ss << ",";
		ss << value[i];
	}
	set(name, ss);  
}

/*===========================================================================*/
/* get sequenze di scalari */
/*===========================================================================*/

std::vector<bool>		MetadataGroup::getBools		(const char* name, bool mandatory) 
{ 
	std::vector<std::string> value;
	getStrSeq_(group, name, mandatory, value);
	std::vector<bool> result(value.size());	
	for (size_t i=0; i<value.size(); i++)
	{
		if (value[i] == TRUESTR)	result[i] = true; 
		else if (value[i] == FALSESTR)	result[i] = false;
		else throw OdimH5FormatException("Value "+value[i]+" inside "+std::string(name)+" attribute is not a boolean");
	}
	return result;
}		
std::vector<char>		MetadataGroup::getChars		(const char* name, bool mandatory) { std::vector<char>		result;	return getSeq_<char>		(group, name, mandatory, result, "char");		}
std::vector<unsigned char>	MetadataGroup::getUChars	(const char* name, bool mandatory) { std::vector<unsigned char>	result;	return getSeq_<unsigned char>	(group, name, mandatory, result, "unsigned char");	}
std::vector<short>		MetadataGroup::getShorts	(const char* name, bool mandatory) { std::vector<short>		result;	return getSeq_<short>		(group, name, mandatory, result, "short");		}
std::vector<unsigned short>	MetadataGroup::getUShorts	(const char* name, bool mandatory) { std::vector<unsigned short>result;	return getSeq_<unsigned short>	(group, name, mandatory, result, "unsigned short");	}
std::vector<int>		MetadataGroup::getInts		(const char* name, bool mandatory) { std::vector<int>		result;	return getSeq_<int>		(group, name, mandatory, result, "int");			}
std::vector<unsigned int>	MetadataGroup::getUInts		(const char* name, bool mandatory) { std::vector<unsigned int>	result;	return getSeq_<unsigned int>	(group, name, mandatory, result, "unsigned int");	}
std::vector<int64_t>		MetadataGroup::getLongs		(const char* name, bool mandatory) { std::vector<int64_t>	result;	return getSeq_<int64_t>		(group, name, mandatory, result, "long");	}
std::vector<time_t>		MetadataGroup::getTimes		(const char* name, bool mandatory) { std::vector<time_t>	result;	return getSeq_<time_t>		(group, name, mandatory, result, "time_t");	}
std::vector<float>		MetadataGroup::getFloats	(const char* name, bool mandatory) { std::vector<float>		result;	return getSeq_<float>		(group, name, mandatory, result, "float");	}		
std::vector<double>		MetadataGroup::getDoubles	(const char* name, bool mandatory) { std::vector<double>	result;	return getSeq_<double>		(group, name, mandatory, result, "double");	}		
std::vector<std::string>	MetadataGroup::getStrings	(const char* name, bool mandatory) { std::vector<std::string> result; return getStrSeq_			(group, name, mandatory, result);	}

std::vector<int64_t>	MetadataGroup::getSimpleArrayLong	(const char* name, bool mandatory) {
	std::vector<int64_t>	result;
	return getSimpleArray<int64_t>(group, name, mandatory, result);
}
std::vector<double>	MetadataGroup::getSimpleArrayDouble	(const char* name, bool mandatory) {
	std::vector<double>	result;
	return getSimpleArray<double>(group, name, mandatory, result);
}
	
/*===========================================================================*/
/* set sequenze di coppie */
/*===========================================================================*/

template <class T> static std::ostringstream& writePairs(std::ostringstream& ss, const std::vector<std::pair<T,T> >& value)
{
	for (size_t i=0; i<value.size(); i++)
	{
		if (i) ss<<",";
		ss << value[i].first << ":" << value[i].second;
	}
	return ss;
}

template <class T> static std::ostringstream& writeFloatPairs(std::ostringstream& ss, const std::vector<std::pair<T,T> >& value, int precision)
{
	if (precision)
		ss.precision(precision);
	for (size_t i=0; i<value.size(); i++)
	{
		if (i) ss<<",";
		ss << value[i].first << ":" << value[i].second;
	}
	return ss;
}

void	MetadataGroup::set	(const char* name, const std::vector<std::pair<short,short> >&		value)			{ std::ostringstream s; set(name, writePairs<short>(s, value)); }
void	MetadataGroup::set	(const char* name, const std::vector<std::pair<int,int> >&		value)			{ std::ostringstream s; set(name, writePairs<int>(s, value)); }
void	MetadataGroup::set	(const char* name, const std::vector<std::pair<int64_t,int64_t> >&	value)			{ std::ostringstream s; set(name, writePairs<int64_t>(s, value)); }
void	MetadataGroup::set	(const char* name, const std::vector<std::pair<float,float> >&		value, int precision)	{ std::ostringstream s; set(name, writeFloatPairs<float>(s, value, precision)); }
void	MetadataGroup::set	(const char* name, const std::vector<std::pair<double,double> >&	value, int precision)	{ std::ostringstream s; set(name, writeFloatPairs<double>(s, value, precision)); }
void	MetadataGroup::set	(const char* name, const std::vector<std::pair<std::string,std::string> >& value)		{ std::ostringstream s; set(name, writePairs<std::string>(s, value)); }

/*===========================================================================*/
/* get sequenze di coppie */
/*===========================================================================*/

template <class T> static std::vector<std::pair<T,T> > getPairs(H5::Group* group, const char* name, bool mandatory, const char* typeName)
{
	std::vector<std::string> value;
	getStrSeq_(group, name, mandatory, value);
	std::vector<std::pair<T,T> > result(value.size());	
	for (size_t i=0; i<value.size(); i++)
	{
		std::string first;
		std::string second;
		Radar::stringutils::split(value[i], first, second, ':');
		result[i].first  = Radar::stringutils::parse<T>(first, typeName);
		result[i].second = Radar::stringutils::parse<T>(second, typeName);
	}
	return result;
}

std::vector<std::pair<short,short> >		MetadataGroup::getShortPairs	(const char* name, bool mandatory) { return getPairs<short>(group, name, mandatory, "int"); }
std::vector<std::pair<int,int> >		MetadataGroup::getIntPairs	(const char* name, bool mandatory) { return getPairs<int>(group, name, mandatory, "int"); }
std::vector<std::pair<int64_t,int64_t> >	MetadataGroup::getLongPairs	(const char* name, bool mandatory) { return getPairs<int64_t>(group, name, mandatory, "long"); }
std::vector<std::pair<float,float> >		MetadataGroup::getFloatPairs	(const char* name, bool mandatory) { return getPairs<float>(group, name, mandatory, "double"); }
std::vector<std::pair<double,double> >		MetadataGroup::getDoublePairs	(const char* name, bool mandatory) { return getPairs<double>(group, name, mandatory, "double"); }

const std::vector<std::pair<std::string,std::string> >	MetadataGroup::getStrPairs		(const char* name, bool mandatory)
{
	std::vector<std::string> value;
	getStrSeq_(group, name, mandatory, value);
	std::vector<std::pair<std::string,std::string> > result(value.size());	
	for (size_t i=0; i<value.size(); i++)
		Radar::stringutils::split(value[i], result[i].first, result[i].second, ':');
	return result;
}

/*===========================================================================*/
/* set sequenze particolari */
/*===========================================================================*/

void	MetadataGroup::set	(const char* name, const std::vector<AZTimes>& value)		
{ 
	set(name, AZTimes::toString(value));
}
void	MetadataGroup::set	(const char* name, const std::vector<AZAngles>& value)		
{ 
	set(name, AZAngles::toString(value, 30));	
}
void	MetadataGroup::set	(const char* name, const std::vector<AZAngles>& value, int precision)		
{ 
	set(name, AZAngles::toString(value, precision));	
}
void	MetadataGroup::set	(const char* name, const VILHeights& value)	
{ 
	set(name, value.toString());	
}

void	MetadataGroup::set	(const char* name, const std::vector<Angles>& value, int precision)		
{ 
	set(name, Angles::toString(value, precision));	
}

void	MetadataGroup::set	(const char* name, const std::vector<Arotation>& value, int precision)		
{ 
	set(name, Arotation::toString(value, precision));	
}

void	MetadataGroup::set	(const char* name, const std::vector<Nodes>& value)		
{ 
	set(name, Nodes::toString(value));	
}


/*===========================================================================*/
/* get sequenze particolari */
/*===========================================================================*/

std::vector<AZTimes>		MetadataGroup::getAZTimes	(const char* name)			
{ 
	return AZTimes::parseSequence( getStr(name,"") );
}
std::vector<AZAngles>		MetadataGroup::getAZAngles	(const char* name)			
{ 
	return AZAngles::parseSequence( getStr(name,"") );	
}
VILHeights			MetadataGroup::getVILHeights	(const char* name)			
{ 
	std::string val = getStr(name, "");
	if (val.empty())
		return VILHeights(0,0);
	return VILHeights(val);
}
std::vector<Angles>		MetadataGroup::getAngles	(const char* name)	
{ 
	return Angles::parseSequence( getStr(name,"") );
}
std::vector<Arotation>		MetadataGroup::getArotation	(const char* name)
{ 
	return Arotation::parseSequence( getStr(name,"") );
}
std::vector<Nodes>		MetadataGroup::getNodes	        (const char* name)
{ 
	return Nodes::parseSequence( getStr(name,"") );
}


/*===========================================================================*/
/* ALTRE FUNZIONI
/*===========================================================================*/

void MetadataGroup::import(MetadataGroup* value)
{
	H5::Group* dst = this->group;
	H5::Group* src = value->getH5Object();
	HDF5Group::copyAttributes(src, dst);
}

void MetadataGroup::import(MetadataGroup* value, const std::set<std::string>& names)
{
	H5::Group* dst = this->group;
	H5::Group* src = value->getH5Object();
	HDF5Group::copyAttributes(src, dst, names);
}

/*===========================================================================*/

}




















