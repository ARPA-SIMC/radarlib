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
 *  \brief Functions and classes to manage files and directories
 */ 

#ifndef __RADAR_IO_HPP__
#define __RADAR_IO_HPP__

#include <string>
#include <vector>
#include <fstream>
#include <stdexcept>

#include <radarlib/defs.h>

namespace Radar {

/*===========================================================================*/

/*! 
 * \brief FileSystem class
 * 
 * This class provides functions to manipulate files and directories 
 */
class RADAR_API FileSystem
{
public:
	/*!
	 * \brief
	 * Check the existence of a file
	 * \param path		the file path
	 */
	static bool		fileExists	(const std::string& path);
	/*!
	 * \brief
	 * Check the existence of a directory 
	 * \param path		the directory path
	 */
	static bool		dirExists	(const std::string& path);
	/*!
	 * \brief
	 * Change the current working directory
	 * \param path		the new directory path
	 */
	static void		changeDir	(const std::string& path);
	/*!
	 * \brief
	 * Get the current working directory
	 */
	static std::string	getCurrentDir	();
	/*!
	 * \brief
	 * Create a directory and all its parent directories if they don't exist
	 * If the directory already exists nothing is done
	 * \param path		the new directory path
	 */
	static void		mkDirTree	(const std::string& path);
	/*!
	 * \brief
	 * Remove a directory and all its sub directories
	 * \param path		the directory path to remove
	 */
	static void		rmDirTree	(const std::string& path);
	/*!
	 * \brief
	 * Get the list of all the files in a directory
	 * \param result	the std::vector the will store the result paths
	 * \param path		the parent directory to analize
	 * \param completePath	if true, the result paths will contain also the parent path specified
	 */
	static void listFiles(std::vector<std::string>& result, const std::string& path, bool completePath = false);
	/*!
	 * \brief
	 * Get the list of all the direct sub directories of a specified directory
	 * \param result	the std::vector the will store the result paths
	 * \param path		the parent directory to analize
	 * \param completePath	if true, the result paths will contain also the parent path specified
	 */
	static void listDirs(std::vector<std::string>& result, const std::string& path, bool completePath = false);
	/*!
	 * \brief
	 * Touch a file like unix system command 'touch'
	 * \param path		the path of the file
	 */
	static void createFile(const std::string& path);
	/*!
	 * \brief
	 * Touch a file like unix system command 'touch'
	 * \param path		the path of the file
	 * \param msg		a text to write into nthe file
	 */
	static void createFile(const std::string& path, const std::string& msg);
	/*!	 * \brief Get the size in bytes of the given file
	 * \param path		the path of the file
	 */
	static size_t getFileSize(const std::string& path);
};

/*! 
 * \brief File path manipulation routines
 * 
 * This class provides functions to manipulate file paths, extension etc.
 */
class RADAR_API Path
{
public:
	/*!
	 * \brief
	 * Extract the parent directory path of a file or directory indicated
	 * \param path		the path of a file or directory
	 */
	static std::string getBasePath(const std::string& path);
	/*!
	 * \brief
	 * Extract the file or directory name from a generic path
	 * \param path		the path of a file or directory
	 */
	static std::string getFileName(const std::string& path);
	/*!
	 * \brief
	 * Extract the directory or file exstension without the dot
	 * \param path		the path of a file or directory
	 */
	static std::string getFileExt(const std::string& path);
	/*!
	 * \brief
	 * Returns the path indicated after changing che extension
	 * \param path		the original path
	 * \param newext	the new extension
	 */
	static std::string changeExt(const std::string& path, const std::string& newext);
	/*!
	 * \brief
	 * Remove the extension from a file or directory path
	 * \param path		the original path
	 * \param newext	the new extension
	 */
	static std::string removeExt(const std::string& path);

};

/*===========================================================================*/

}

#endif


























