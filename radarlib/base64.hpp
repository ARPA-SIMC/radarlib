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
 *  \brief Classes to encoded and decode base64 strings
 */ 

#ifndef __RADAR_BASE64_HPP__
#define __RADAR_BASE64_HPP__

#include <string>
#include <vector>

#include <radarlib/defs.h>

namespace Radar {

/*===========================================================================*/

/*! 
* \brief Base64 encoding class
* 
* \n This class provide functions to encode and decode strings and buffers
* \n acording to Base 64 format.
*/
class RADAR_API Base64
{
public: 
    /*!
    * \brief
    * Calculate the length of the base64 string that would result converting a buffer large 'buffsize' bytes
    *
    * \param buffsize		the binary buffer length (in bytes) 
    */
    static size_t encodeSize(size_t buffsize);
    /*!
    * \brief
    * Encode a buffer into a std::string
    *
    * \param b64str		the destination string variable
    * \param buff			the binary buffer
    * \param buffsize		the binary buffer length (in bytes) 
    */
    static void encode(std::string& b64str, const void* buff, size_t buffsize);
    /*!
    * \brief
    * Calculate the length of the binary buffer that would result deconverting the indicated base64 string
    *
    * \param b64str		the encoded string
    */
    static size_t decodeSize(const std::string& b64str);
    /*!
    * \brief
    * Decode a base64 string allocating a new buffer
    *
    * \param b64str		the encoded string
    */
    static unsigned char* decode(const std::string& b64str);		
    /*!
    * \brief
    * Decode a base64 string allocating a new buffer
    *
    * \param b64str		the encoded string
    * \param resultSize		a pointer to a variabile that will store the size of the allocated buffer
    */
    static unsigned char* decode(const std::string& b64str, size_t* resultSize);		
    /*!
    * \brief
    * Decode a base64 string into an existing std::vector 
    *
    * \param result		the result vector that will store the decoded binary data
    * \param b64str		the encoded string
    */
    static void decode(std::vector<unsigned char>& result, const std::string& b64str);
};

/*===========================================================================*/

}

#endif
