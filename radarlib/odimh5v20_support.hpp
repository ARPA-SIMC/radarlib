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
 *  \brief Classes and struct used by main OdimH5 classes
 */ 

#ifndef __RADAR_ODIMH5V20_SUPPORT_HPP__
#define __RADAR_ODIMH5V20_SUPPORT_HPP__

/*===========================================================================*/

#include <string>
#include <vector>

#include <radarlib/defs.h>
#include <radarlib/odimh5v20_exceptions.hpp>

namespace OdimH5v20 {

/*===========================================================================*/
/* ODIM OBJECT MODEL VERSION NUMBERS */
/*===========================================================================*/

/*! 
 * \brief OdimH5 model version informations
 * 
 * This class represent a OdimH5 v2.0 model version 
 * It is used to read and write OdimObjects attribute "what.version"
 * See OdimH5 v2.0 specification/page 10 for further informations
 * 
 * \see OdimObject
 */
class RADAR_API ModelVersion
{
public:
	int Major;
	int Minor;

	/*!
	 * \brief
	 * Create and inizalize object fields with the indicated values
	 * 
	 * \param maj			value for Major field
	 * \param min			value for Minor field
	 */	
	ModelVersion(int maj, int min);
	
	/*!
	 * \brief
	 * Create and inizalize object fields decoding the indicated string
	 * 
	 * \param value				a string formatted like "H5rad <MAJOR>.<MINOR>"
	 *
	 * \throws OdimH5FormatException	Throwed when string format is not valid
	 */	
	ModelVersion(const std::string& value);
	/*!
	 * \brief
	 * Set object fields parsing an input string
	 * 
	 * \param val				a string formatted like "H5rad <MAJOR>.<MINOR>"
	 *
	 * \throws OdimH5FormatException	Throwed when string format is not valid
	 */	
	void parse(const std::string& val);

	/*!
	 * \brief
	 * Return a model version string formatted acording to OdimH5 specifications
	 */	
	std::string toString() const;
};


/*===========================================================================*/
/* ODIM OBJECT SOURCE INFORMATIONS */
/*===========================================================================*/

/*! 
 * \brief OdimH5 object source informations
 * 
 * This class represent a OdimH5 object source info
 * \n For further details see OdimH5 v2.0 specifications/page 10
 *
 * \remarks
 * From OdimH5 documentation is not clear a single type of subinformation can have multiple values, so we assume thet every sub info has only one value
 *
 * \see OdimObject
 */
class RADAR_API SourceInfo
{
public:
	/*!
	 * \brief Combined WMO block and station number in the form A1bwnnnnn, or 0 if none assigned
	 */
	std::string	WMO;
	/*!
	 * \brief Radar site as indexed in the OPERA database
	 */
	std::string	OperaRadarSite;
	/*!
	 * \brief Originating centre.
	 */
	int		OriginatingCenter;
	/*!
	 * \brief Place according to Table 9 of OdimH5 standard
	 */
	std::string	Place;
	/*!
	 * \brief Country according to BUFR tables 14 0 1 101
	 */
	int		Country;
	/*!
	 * \brief Free comment
	 */
	std::string	Comment;

	/*!
	 * \brief
	 * Create an empty source information object
	 */
	SourceInfo();
	/*!
	 * \brief
	 * Create and inizalize a source information decoding the indicated string
	 * 
	 * \param value				a string formatted like "type:value,type:value,..."
	 *
	 * \throws OdimH5FormatException	Throwed when string format is not valid
	 */
	SourceInfo(const std::string& value);
	/*!
	 * \brief
	 * Set object fields decoding the indicated string
	 * 
	 * \param value				a string formatted like "type:value,type:value,..."
	 *
	 * \throws OdimH5FormatException	Throwed when string format is not valid
	 */	
	void parse(const std::string value);
	/*!
	 * \brief
	 * Convert fields into a string formated acording to OdimH5 specifications
	 * 
	 */
	std::string toString() const;

	/*!
	 * \brief
	 * Set WMO value and return a reference to this object
	 */
	inline SourceInfo& setWMO(const std::string& value)
	{
		WMO = value;
		return *this;
	}
	/*!
	 * \brief
	 * Set OperaRadarSite value and return a reference to this object
	 */
	inline SourceInfo& setOperaRadarSite(const std::string& value)
	{
		OperaRadarSite = value;
		return *this;
	}
	/*!
	 * \brief
	 * Set OriginatingCenter value and return a reference to this object
	 */
	inline SourceInfo& setOriginatingCenter(int value)
	{
		OriginatingCenter = value;
		return *this;
	}
	/*!
	 * \brief
	 * Set Place value and return a reference to this object
	 */
	inline SourceInfo& setPlace(const std::string& value)
	{
		Place = value;
		return *this;
	}
	/*!
	 * \brief
	 * Set Country value and return a reference to this object
	 */
	inline SourceInfo& setCountry(int value)
	{
		Country = value;
		return *this;
	}
	/*!
	 * \brief
	 * Set Comment value and return a reference to this object
	 */
	inline SourceInfo& setComment(const std::string& value)
	{
		Comment = value;
		return *this;
	}
};

/*===========================================================================*/
/* AZIMUTH ANGLES PAIR */
/*===========================================================================*/

/*! 
 * \brief Azimuth angles pair
 * 
 * This class represent a ray's start and stop azimuth angles
 *
 * \see PolarScan | AZTimes
 */
class RADAR_API AZAngles
{
public:
	/*!
	 * \brief Start azimuth angle
	 *
	 * Azimuth angles are clock-wise ordered, so start value is lower than stop value
	 */
	double start;
	/*!
	 * \brief Stop azimuth angle
	 *
	 * Azimuth angles are clock-wise ordered, so stop value is bigger than stat value
	 */
	double stop;
	
	/*!
	 * \brief
	 * Create an object with start and stop set to 0
	 */
	AZAngles();	
	/*!
	 * \brief
	 * Create a pair and set fields using the values passed
	 * 
	 * \param start				value for start angle
	 * \param stop				value for stop angle
	 */	
	AZAngles(double start, double stop);	
	/*!
	 * \brief
	 * Create a pair and object fields decoding the indicated string
	 * 
	 * \param value				a string formatted like "value:value"
	 *
	 * \throws OdimH5FormatException	Throwed when string format is not valid
	 */	
	AZAngles(const std::string& value);
	/*!
	 * \brief
	 * Set fields 
	 * 
	 * \param start				value for start angle
	 * \param stop				value for stop angle
	 */		
	void set(double start, double stop);
	/*!
	 * \brief
	 * Set object fields decoding the indicated string
	 * 
	 * \param str				a string formatted like "value:value"
	 *
	 * \throws OdimH5FormatException	Throwed when string format is not valid
	 */	
	void parse(const std::string& str);
	/*!
	 * \brief
	 * Convert angles to a string formated acording to OdimH5 specifications
	 */	
	std::string toString() const;
	/*!
	 * \brief
	 * Convert angles to a string formated acording to OdimH5 specifications
	 *
	 * \param precision		precision to use when converting double values to strings
	 *
	 */	
	std::string toString(int precision) const;
	/*!
	 * \brief
	 * Create a collection of azimuth angles splitting and decoding a string
	 * \param str				a string formatted like "value:value,value:value,..."
	 * \throws OdimH5FormatException	Throwed when string format is not valid
	 */	
	static std::vector<AZAngles> parseSequence(const std::string& str);
	/*!
	 * \brief
	 * \param right				the values to convert
	 * Convert a collection of azimuth angles to a string formated acording to OdimH5 specifications
	 */	
	static std::string toString(const std::vector<AZAngles>& right);
	/*!
	 * \brief
	 * Convert a collection of azimuth angles to a string formated acording to OdimH5 specifications
	 * \param right				the destination string 
	 * \param precision			the precision to use while converting values to string
	 * \param precision		precision to use when converting double values to strings
	 */	
	static std::string toString(const std::vector<AZAngles>& right, int precision);
};

/*===========================================================================*/
/* AZIMUTH TIMES PAIR */
/*===========================================================================*/

/*! 
 * \brief Azimuth angles pair
 * 
 * This class represent a ray's start and stop azimuth times expressed as 'secconds.milliseconds' from 1970
 *
 * \see PolarScan | AZAngles
 */
class RADAR_API AZTimes
{
public:
	/*!
	 * \brief Start azimuth time (seconds.milliseconds)
	 *
	 * Azimuth start time is always lower than stop time
	 */
	double start;	
	/*!
	 * \brief Start azimuth time (seconds.milliseconds)
	 *
	 * Azimuth stop time is always bigger than start time
	 */
	double stop;	

	/*!
	 * \brief
	 * Create an object with start and stop set to 0
	 */
	AZTimes();
	/*!
	 * \brief
	 * Create a pair and set fields decoding the indicated string
	 * \param start				value for start time
	 * \param stop				value for stop time
	 */
	AZTimes(double start, double stop);
	/*!
	 * \brief
	 * Create a pair and object fields decoding the indicated string
	 * \param str				a string formatted like "value:value"
	 * \throws OdimH5FormatException	Throwed when string format is not valid
	 */
	AZTimes(const std::string& str);
	/*!
	 * \brief
	 * Set fields 
	 * 
	 * \param start				value for start time
	 * \param stop				value for stop time
	 */
	void set(double start, double stop);
	/*!
	 * \brief
	 * Set object fields decoding the indicated string
	 * The string must be formated acording to OdimH5 specifications
	 * \param str				the string to parse		
	 * \throws OdimH5FormatException	Throwed when string format is not valid
	 */	
	void parse(const std::string& str);
	/*!
	 * \brief
	 * Convert times to a string formated acording to OdimH5 specifications
	 */
	std::string toString() const;
	/*!
	 * \brief
	 * Create a collection of azimuth times splitting and decoding a string
	 * \param str				a string formatted like "value:value,value:value,..."
	 * \throws OdimH5FormatException	Throwed when string format is not valid
	 */
	static std::vector<AZTimes> parseSequence(const std::string& str);
	/*!
	 * \brief
	 * Convert a collection of azimuth timesto a string formated acording to OdimH5 specifications
	 */
	static std::string toString(const std::vector<AZTimes>& right);
};

/*===========================================================================*/
/* VIL HEIGHTS PAIR */
/*===========================================================================*/

/*! 
 * \brief Bottom and top heights (m) of the integration layer
 * 
 * This class represent bottom and top height (m) values used in an integration layer
 * This class is defined only for future use
 */
class RADAR_API VILHeights
{
public:
	/*!
	 * \brief Lower value in meters
	 */
	double bottom;	
	/*!
	 * \brief Upper value in meters
	 */
	double top;	

	/*!
	 * \brief Create and intialize a VIL height pair to 0
	 */
	VILHeights();
	/*!
	 * \brief Create and intialize a VIL height pair
	 */
	VILHeights(double bottom, double top);
	/*!
	 * \brief Create and intialize a VIL height pair parsing the given string
     * The string must be formated as indicated in OdimH5 specifications
	 */
	VILHeights(const std::string& str);

	/*!
	 * \brief Set pair values
	 */
	void set(double bottom, double top);
	/*!
	 * \brief Set pair values parsing the given string
	 */
	void parse(const std::string& str);
	/*!
	 * \brief Convert the pair to a string according to OdimH5 specifications
	 */
	std::string toString() const;
};

/*===========================================================================*/
/* DATA MATRIX */
/*===========================================================================*/

/*! 
 * \brief Matrix of data values
 * 
 * This class represent matrix of values \n
 * The type of every value in the matrix is defined by the user using the template syntax \n
 * The internal data buffer is automatically allocated and deallocated 
 * The matrix can be resized but the previous values will be lost and the elements will be set to 0 or to the fill value specified in the constructor
 *
 * \see OdimData
 */
template <class T> class DataMatrix
{
public:
	/*!
	 * \brief Create an empty 0x0 matrix
	 *
	 * Create an empty 0x0 matrix
         * The default fill value for resize operations will be 0
	 */
	DataMatrix()
	:fillvalue(0)
	,rows(0)
	,cols(0)
	,cells()
	{		
	}
	/*!
	 * \brief Create an empty rows x cols matrix
	 * 
	 * Create an empty rows x cols matrix, setting elements to 0
         * The default fill value for resize operations will be 0
	 * \param rows		number of rows to store in the matrix 
	 * \param cols		number of cols for each row 
	 */
	DataMatrix(int rows, int cols)
	:fillvalue(0)
	,rows(0)
	,cols(0)
	,cells()
	{
		resize(rows, cols);
	}
	/*!
	 * \brief Create an empty rows x cols matrix, setting elements to 0
	 * 
	 * \param rows		number of rows to store in the matrix 
	 * \param cols		number of cols for each row 
	 * \param value		number value used to fill the new allocated cells
	 */
	DataMatrix(int rows, int cols, T value)
	:fillvalue(value)
	,rows(0)
	,cols(0)
	,cells()
	{
		resize(rows, cols);
	}
	virtual ~DataMatrix()
	{
	}
	/*!
	 * \brief	Resize the matrix
	 * 
	 * Resize the matrix using the given number of rows and cols
	 * The previous matrix data will be erased and filled with the current fill value
	 * \param rows		the new rows number 
	 * \param cols		the new cols number 
	 */
	inline void resize(const int rows, const int cols)
	{
		resize(rows, cols, fillvalue);
	}
	/*!
	 * \brief	Resize the matrix
	 *
	 * Resize the matrix using the given number of rows and cols
	 * The previous matrix data will be erased and filled with the new fill value
	 * \param rows			the new rows number 
	 * \param cols			the new cols number 
	 * \param fillvalue		value used to initialize matrix cells
	 */
	inline void resize(const int rows, const int cols, const T fillvalue)
	{
		this->rows = rows;
		this->cols = cols;
		cells.resize(rows * cols * sizeof(T));				
		fill(fillvalue);
	}
	/*!
	 * \brief Set all matrix values to the current fill value
	 */
	inline void erase()
	{
		fill(this->fillvalue);
	}
	/*!
	 * \brief Set all matrix values to the given value
	 */
	inline void fill(T value)
	{
		int total = rows * cols;
		for (int i=0; i<total; i++)
			cells[i] = value;	
		this->fillvalue = value;
	}

	/*!
	 * \brief Reference to the element (r,b) 
	 * 
	 * \param r			row index from 0 to rows-1
	 * \param b			col index from 0 to cols-1
	 */
	inline T& elem(const int r, const int b)  
	{
		return cells[r * cols + b];
	}
	/*!
	 * \brief Return the pointer to the underneath data buffer 
	 */
	inline const T* get() const
	{
		return &(cells[0]);
	}
	/*!
	 * \brief Return the number of rows 
	 */
	inline int getRowCount() const { return rows; }
	/*!
	 * \brief Return the number of cols
	 */
	inline int getColCount() const { return cols; }

protected:
	T		fillvalue;
	int		rows;
	int		cols;
	std::vector<T>	cells;
};

/*===========================================================================*/
/* RAY MATRIX */
/*===========================================================================*/

/*! 
 * \brief OdimH5 rays matrix 
 * 
 * This class represent a collection of rays stored as a matrix \n
 * The rows are the single rays. The rows elements are the bins values of the single ray
 * The type of every value in the matrix is defined by the user using the template syntax \n
 * The internal data buffer is automatically allocated and deallocated 
 * The matrix can be resized but the previous values will be lost and the elements will be set to 0 or to the fill value specified in the constructor
 *
 * \see PolarScanData 
 */
template <class T> class RayMatrix: public DataMatrix<T>
{
public:
	/*!
	 * \brief Create a matrix with no rays
	 *
	 * Create an empty matrix with nor rays
     * The default fill value for resize operations will be 0
	 */
	RayMatrix()
	:DataMatrix<T>()
	{		
	}
	/*!
	 * \brief Create a matrix to store a ray collection
	 * 
	 * Create an empty matrix large enough to store the given number of rays. 
     * Each ray can store the given number of bins
     * The default fill value for resize operations will be 0
	 * \param rays		number of rays
	 * \param bins		number of bins in a single ray
	 */
	RayMatrix(int rays, int bins)
	:DataMatrix<T>(rays, bins)
	{
	}
	/*!
	 * \brief Create a matrix to store a ray collection
	 * 
	 * Create an empty matrix large enough to store the given number of rays. 
     * Each ray can store the given number of bins
     * The given fillvalue will be used for resize operations 
	 * \param rays		    number of rays
	 * \param bins	    	number of bins in a single ray
	 * \param fillvalue		number of bins in a single ray
	 */
	RayMatrix(int rays, int bins, T fillvalue)
	:DataMatrix<T>(rays, bins, fillvalue)
	{
	}
	virtual ~RayMatrix()
	{
	}
	/*!
	 * \brief	Resize the matrix
	 *
	 * Resize the ray matrix
	 * The previous matrix data will be erased and filled with the default fill value
	 * \param rays			the new rows number 
	 * \param bins			the new cols number 
	 */
	inline void resize(const int rays, const int bins)
	{
		DataMatrix<T>::resize(rays, bins);
	}
	/*!
	 * \brief	Resize the matrix
	 *
	 * Resize the ray matrix and set the new default fill value
	 * The previous matrix data will be erased and filled with the new fill value    
	 * \param rays			the new rays number
	 * \param bins			the new bins number 
	 * \param fillvalue		the new fill value to use
	 */
	inline void resize(const int rays, const int bins, const T fillvalue)
	{
		DataMatrix<T>::resize(rays, bins, fillvalue);
	}
	/*!
	 * \brief Get the number of rays that can be store in the matrix (matrix rows num)
	 */
	inline int getRayCount() const { return this->rows; }
	/*!
	 * \brief Get the number of bins that can be store in a single ray (matrix cols num)
	 */
	inline int getBinCount() const { return this->cols; }
};

/*===========================================================================*/
/* ELEVATION ANGLES */
/*===========================================================================*/

/*!
 * \brief Elevation angle
 *
 * This class represent an elevation angle
 *
 * \see Horizontal_Product_2D | Angles
 */
class RADAR_API Angles
{
public:
	/*!
	 * \brief Elevation angle
	 * Elevation angles are ordered from lower to upper values
	 */
	double value;
	/*!
	 * \brief Create an object with values set to 0
	 */
	Angles();
	/*!
	 * \brief Create an object set to the value passed
	 * \param [in] value a double value for the elevation angle
	 */	
	Angles(double value);
	/*!
	 * \brief Create an object set to the value passed
	 * \param [in] value a string value for the elevation angle
	 */	
	Angles(const std::string& value);
	/*!
	 * \brief
	 * Set field 
	 * 
	 * \param value 			value for elevation angle
	 */		
	void set(double value);
	/*!
	 * \brief
	 * Set object fields decoding the indicated string
	 * 
	 * \param str				a string formatted like "value"
	 *
	 * \throws OdimH5FormatException	Throwed when string format is not valid
	 */	
	void parse(const std::string& str);
	/*!
	 * \brief
	 * Convert angle to a string formated according to OdimH5 specifications
	 */	
	std::string toString() const;
	/*!
	 * \brief
	 * Convert angles to a string formated according to OdimH5 specifications
	 *
	 * \param precision		precision to use when converting double values to strings
	 *
	 */	
	std::string toString(int precision) const;
	/*!
	 * \brief
	 * Create a collection of angles decoding a string
	 * \param str				a string formatted like "value,value,..."
	 * \throws OdimH5FormatException	Throwed when string format is not valid
	 */	
	static std::vector<Angles> parseSequence(const std::string& str);
	/*!
	 * \brief
	 * \param right				the values to convert
	 * Convert a collection of azimuth angles to a string formated according to OdimH5 specifications
	 */	
	static std::string toString(const std::vector<Angles>& right);
	/*!
	 * \brief
	 * Convert a collection of azimuth angles to a string formated acording to OdimH5 specifications
	 * \param right				the destination string 
	 * \param precision		precision to use when converting double values to strings
	 */	
	static std::string toString(const std::vector<Angles>& right, int precision);
};

/*===========================================================================*/
/* AROTATION */
/*===========================================================================*/

/*!
 * \brief Arotation - Antenna Rotation Speed
 *
 * This class represent the Antenna Rotation Speed 
 *
 * \see Horizontal_Product_2D | Arotation
 */
class RADAR_API Arotation
{
public:
	/*!
	 * \brief Antenna rotation speed
	 */
	double value;
	/*!
	 * \brief Create an object with values set to 0
	 */
	Arotation();
	/*!
	 * \brief Create an object set to the value passed
	 * \param [in] value a double value for the Antenna rotation speed
	 */	
	Arotation(double value);
	/*!
	 * \brief Create an object set to the value passed
	 * \param [in] value a string value for the antenna rotation speed
	 */	
	Arotation(const std::string& value);
	/*!
	 * \brief
	 * Set field 
	 * 
	 * \param value 			value for antenna rotation speed
	 */		
	void set(double value);
	/*!
	 * \brief
	 * Set object fields decoding the indicated string
	 * 
	 * \param str				a string formatted like "value"
	 *
	 * \throws OdimH5FormatException	Throwed when string format is not valid
	 */	
	void parse(const std::string& str);
	/*!
	 * \brief
	 * Convert antenna rotation speed to a string formated according to OdimH5 specifications
	 */	
	std::string toString() const;
	/*!
	 * \brief
	 * Convert antenna rotation speed to a string formated according to OdimH5 specifications
	 *
	 * \param precision		precision to use when converting double values to strings
	 *
	 */	
	std::string toString(int precision) const;
	/*!
	 * \brief
	 * Create a collection of antenna rotation speeds decoding a string
	 * \param str				a string formatted like "value,value,..."
	 * \throws OdimH5FormatException	Throwed when string format is not valid
	 */	
	static std::vector<Arotation> parseSequence(const std::string& str);
	/*!
	 * \brief
	 * \param right				the values to convert
	 * Convert a collection of antenna rotation speeds to a string formated according to OdimH5 specifications
	 */	
	static std::string toString(const std::vector<Arotation>& right);
	/*!
	 * \brief
	 * Convert a collection of antenna rotation speeds to a string formated acording to OdimH5 specifications
	 * \param right			the destination string 
	 * \param precision		precision to use when converting double values to strings
	 */	
	static std::string toString(const std::vector<Arotation>& right, int precision);
};

/*===========================================================================*/
/* NODES  */
/*===========================================================================*/

/*!
 * \brief Nodes - Radar nodes which have crontributed data to composit
 *
 * This class represent the Radar nodes
 *
 * \see Horizontal_Product_2D | Nodes
 */
class RADAR_API Nodes
{
private:
	/*!
	 * \brief Radar nodes 
	 */
	std::string radar;
public:
	/*!
	 * \brief Create an object with values set to ""
	 */
	Nodes();
	/*!
	 * \brief Create an object set to the value passed
	 * \param [in] radar - string for radar node
	 */	
	Nodes(const std::string & radar);
	/*!
	 * \brief Create an object set to the value passed
	 * \param [in] radar - string for radar node
	 */	
	Nodes(const char * radar);

	std::string get() const;
	/*!
	 * \brief
	 * Set field 
	 * 
	 * \param radar 	string for radar node
	 */		
	void set(const std::string & radar);
	/*!
	 * \brief
	 * Set field 
	 * 
	 * \param radar 	string for radar node
	 */		
	void set(const char * radar);
	/*!
	 * \brief
	 * Create a collection of radar nodes decoding a string
	 * \param str				a string formatted like "'value','value',..."
	 * \throws OdimH5FormatException	Throwed when string format is not valid
	 */	
	static std::vector<Nodes> parseSequence(const std::string& str);
	/*!
	 * \brief
	 * \param radars				the values to convert
	 * Convert a collection of radar nodes to a string formated according to OdimH5 specifications
	 */	
	static std::string toString(const std::vector<Nodes>& radars);
};


}

#endif
