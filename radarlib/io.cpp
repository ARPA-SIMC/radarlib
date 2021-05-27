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

#include <radarlib/io.hpp>

#if defined(WIN32)
	#include <windows.h>		/* dir functions */
	#include <shlobj.h>		/* dir functions */
	#include <tchar.h>
	#include <strsafe.h>	
	#define FILEUTILS_PATH_MAX_LEN		260	/* on windows MAX_PATH 260 is */	

	#define snprintf	_snprintf

#elif defined(__linux__) || defined(linux)
	#include <unistd.h>
	#include <sys/types.h>
	#include <sys/stat.h>
	#include <dirent.h>
	#include <limits.h>
	#include <errno.h>
	#define FILEUTILS_PATH_MAX_LEN		PATH_MAX
#endif

#include <cstdlib>
#include <cstring>
#include <sstream>
#include <fstream>
#include <stdexcept>
#include <memory>
#include <algorithm>

#include <radarlib/debug.hpp>

namespace Radar
{

/*===========================================================================*/
/* WIN32 */
/*===========================================================================*/

#if defined(WIN32) 

static std::string GetLastErrorStr()
{
	LPTSTR Error = NULL;
	try
	{
		if (::FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, GetLastError(), 0, (LPTSTR)&Error, 0, NULL) == 0)
		{
			std::ostringstream ss;
			ss << "System error on FormatMessage(): " << GetLastError();
			return ss.str();
		}
		std::string result = Error;	
		if (Error) ::LocalFree(Error);
		return result;
	}
	catch (...)
	{
		if (Error) ::LocalFree(Error);
		throw;		
	}
}

static std::string normalizePath(const std::string& path)
{
	std::ostringstream ss;
	for (size_t i=0; i<path.length(); i++)
	{
		if (path[i]=='/')	ss << "\\";
		else			ss << path[i];		
	}
	//ss << "\\";
	return ss.str();
}

bool FileSystem::fileExists(const std::string& path)
{
	std::string path2 = normalizePath(path);
	DWORD res = GetFileAttributes(path2.c_str());
	if (res == INVALID_FILE_ATTRIBUTES) 
	{
		DWORD err = GetLastError();
		if ((err == ERROR_FILE_NOT_FOUND) || (err == ERROR_PATH_NOT_FOUND))	
			return false;
		throw std::runtime_error("Unable to check file " + path + ": " + GetLastErrorStr());		
	}
	return (res & FILE_ATTRIBUTE_DIRECTORY) == 0;
}

bool FileSystem::dirExists(const std::string& path)
{
	std::string path2 = normalizePath(path);
	DWORD res = GetFileAttributes(path2.c_str());
	if (res == INVALID_FILE_ATTRIBUTES) 
	{
		DWORD err = GetLastError();
		if ((err == ERROR_FILE_NOT_FOUND) || (err == ERROR_PATH_NOT_FOUND))	
			return false;
		throw std::runtime_error("Unable to check directory " + path + ": " + GetLastErrorStr());		
	}
	return (res & FILE_ATTRIBUTE_DIRECTORY) != 0;
}

void FileSystem::changeDir(const std::string& path)
{	
	std::string path2 = normalizePath(path) + "\\";
	if (SetCurrentDirectory(path2.c_str()) == 0) 
		throw std::runtime_error("Cannot change to directory " + path + ": " + GetLastErrorStr());		
}

std::string FileSystem::getCurrentDir()
{
	char	buf[FILEUTILS_PATH_MAX_LEN+1];
	DWORD	sizeaux = FILEUTILS_PATH_MAX_LEN;
	if (GetFullPathName(".", sizeaux, buf, NULL) == 0) 
		throw std::runtime_error("Cannot get current directory: " + GetLastErrorStr());		
	return buf;
}

void FileSystem::mkDirTree(const std::string& path)
{
	std::string path2 = normalizePath(path)+ "\\";

	int res = SHCreateDirectoryEx(NULL, path2.c_str(), NULL);
	if (res == ERROR_SUCCESS)		return;
	if (res == ERROR_ALREADY_EXISTS)	return;

	throw std::runtime_error("Cannot create directory " + path + ": " + GetLastErrorStr());		
}

void FileSystem::rmDirTree(const std::string& path)
{
	std::string path2 = normalizePath(path)+ "\\";

	char cmd[FILEUTILS_PATH_MAX_LEN+1];
	snprintf(cmd, sizeof(cmd), "rmdir /S /Q \"%s\"", path2.c_str());
	int res = system(cmd);
	if (res == -1) 
		throw std::runtime_error("Cannot remove directory " + path + ": " + GetLastErrorStr());		
}

void FileSystem::listFiles(std::vector<std::string>& result, const std::string& path, bool completePath)
{
	std::string path2 = normalizePath(path);

	WIN32_FIND_DATA		ffd;
	TCHAR			szDir[FILEUTILS_PATH_MAX_LEN+1];
	HANDLE			hFind		= INVALID_HANDLE_VALUE;

	StringCchCopy(szDir, FILEUTILS_PATH_MAX_LEN, path2.c_str());
	StringCchCat(szDir,  FILEUTILS_PATH_MAX_LEN, TEXT("\\*"));

	hFind = FindFirstFile(szDir, &ffd);
		if (INVALID_HANDLE_VALUE == hFind) 
		goto err;

	for (;;)
	{
		if (ffd.dwFileAttributes & (~FILE_ATTRIBUTE_DIRECTORY))
		{
			std::string filename = ffd.cFileName;
			if (completePath)
				filename = path2 + "\\" + filename;
			result.push_back(filename);			
		}
		if (FindNextFile(hFind, &ffd) == 0)
		{
			if (GetLastError() != ERROR_NO_MORE_FILES)
				goto err;
			break;
		}
	}	

	FindClose(hFind);	
	return;

err:		
	std::string msg = "Unable to list files in " + path + ":" + GetLastErrorStr();
	if (hFind != INVALID_HANDLE_VALUE) 
		FindClose(hFind);
	throw std::runtime_error(msg);		
}

void FileSystem::listDirs(std::vector<std::string>& result, const std::string& path, bool completePath)
{
	std::string path2 = normalizePath(path);

	WIN32_FIND_DATA	ffd;
	TCHAR		szDir[MAX_PATH+1];
	HANDLE		hFind		= INVALID_HANDLE_VALUE;

	StringCchCopy(szDir,	MAX_PATH, path2.c_str());
	StringCchCat(szDir,	MAX_PATH, TEXT("\\*"));

	hFind = FindFirstFile(szDir, &ffd);
		if (INVALID_HANDLE_VALUE == hFind) 
		goto err;

	for (;;)
	{
		if ((ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && (strcmp(ffd.cFileName, TEXT(".")) != 0) && (strcmp(ffd.cFileName, TEXT("..")) != 0))
		{
			std::string filename = ffd.cFileName;
			if (completePath)
				filename = path2 + "\\" + filename;
			result.push_back(filename);
		}
		if (FindNextFile(hFind, &ffd) == 0)
		{
			if (GetLastError() != ERROR_NO_MORE_FILES)
				goto err;
			break;
		}
	}	

	FindClose(hFind);
	return;

err:
	std::string msg = "Unable to list directories in " + path + ":" + GetLastErrorStr();
	if (hFind != INVALID_HANDLE_VALUE) 
		FindClose(hFind);
	throw std::runtime_error(msg);	
}

size_t FileSystem::getFileSize(const std::string& path)
{
	std::string path2 = normalizePath(path);

    	BOOL                        fOk;
    	WIN32_FILE_ATTRIBUTE_DATA   fileInfo;

    	fOk = GetFileAttributesEx(path2.c_str(), GetFileExInfoStandard, (void*)&fileInfo);
		if (!fOk) goto err;
	
    	//assert(0 == fileInfo.nFileSizeHigh);

    	return (size_t)fileInfo.nFileSizeLow;
err:
	std::ostringstream ss;
	ss << "Unable to get file size for " << path2 << ":" << GetLastErrorStr();
	throw std::runtime_error(ss.str());	
}

/*===========================================================================*/
/* LINUX */
/*===========================================================================*/

#elif defined(__linux__) || defined(linux)

static std::string normalizePath(const std::string& path)
{
	std::ostringstream ss;
	for (size_t i=0; i<path.length(); i++)
	{
		if (path[i]=='\\')	ss << "/";
		else			ss << path[i];		
	}	
	return ss.str();
}

bool FileSystem::fileExists(const std::string& path) 
{
	std::string path2 = normalizePath(path);

	struct stat dirstats;
	if (stat(path2.c_str(), &dirstats) == -1)
	{
		if (errno == ENOENT) 
			return false;	
		throw std::runtime_error("Unable to check file " + path + ": " + strerror(errno));				
	}
    	if (S_ISREG(dirstats.st_mode)) 		
		return true;
	return false;
}

bool FileSystem::dirExists(const std::string& path) 
{
	std::string path2 = normalizePath(path);

	struct stat dirstats;
	if (stat(path2.c_str(), &dirstats) == -1)
	{
		if (errno == ENOENT) 
			return false;	
		throw std::runtime_error("Unable to check directory " + path + ": " + strerror(errno));				
	}
    	if (S_ISREG(dirstats.st_mode)) 		
		return false;
	return true;
}

void FileSystem::changeDir(const std::string& path) 
{	
	std::string path2 = normalizePath(path) + "/";
	if (chdir(path2.c_str())) 
		throw std::runtime_error("Cannot change to directory " + path + ": " + strerror(errno));
}

std::string FileSystem::getCurrentDir() 
{
	char	buf[FILEUTILS_PATH_MAX_LEN+1];
	if (getcwd(buf, FILEUTILS_PATH_MAX_LEN) == NULL) 
		throw std::runtime_error(std::string("Cannot get current directory: ") + strerror(errno));		
	return buf;
}

static int mkDirTreeAux(const char* path, mode_t mode)
{
	char subpath[FILEUTILS_PATH_MAX_LEN+1];
	const char* last = path;
	const char* ch = NULL;
	int res;
	size_t len;
	while ((ch = strchr(last,'/')))
	{
		last = ch+1;
		len = ch - path;
		if (len == 0) continue;
		memset(subpath, 0, sizeof(subpath));
		strncpy(subpath, path, ch - path);
		//DEBUG("mkdir [%s]\n", subpath);
		res = mkdir(subpath, mode);
		if (res == 0) continue;
		if (errno == EEXIST) continue;
		return res;
	}
	/* potrebbe avanzare ancora un pezzo */
	return mkdir(path, mode);
}

void FileSystem::mkDirTree(const std::string& path) 
{
	std::string path2 = normalizePath(path) + "/";

	int res = mkDirTreeAux(path2.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	if (res == 0)		return;
	if (errno == EEXIST)	return;

	throw std::runtime_error("Cannot create directory " + path + ": " + strerror(errno));	
}

void FileSystem::rmDirTree(const std::string& path) 
{
	std::string path2 = normalizePath(path) + "/";

	char cmd[FILEUTILS_PATH_MAX_LEN+1];
	snprintf(cmd, sizeof(cmd), "rm -r \"%s\"", path2.c_str());
	if (system(cmd) == -1) 
		throw std::runtime_error("Cannot create directory " + path + ": " + strerror(errno));	
}

static int isfile__(const std::string& path)
{
	struct stat filestat;
	if (stat(path.c_str(), &filestat)) 
		return -1;
    	if (S_ISREG(filestat.st_mode)) 		
		return 1;
	return 0;
}

void FileSystem::listFiles(std::vector<std::string>& result, const std::string& path, bool completePath) 
{
	std::string path2 = normalizePath(path) + "/";

	DIR*			dir		= NULL;
	struct	dirent*		file		= NULL;			

	dir = opendir(path2.c_str());
		if (dir == NULL) 
		goto err;

	for (;;)
	{
		file = readdir(dir);
		if (file == NULL) {
			if (errno == EBADF) 
			goto err;
			break;
		}
		
		int isfile = isfile__(path2 + "/" + file->d_name);
			if (isfile < 0) 
			goto err;

		if (isfile)
		{
			std::string filename = file->d_name;
			if (completePath)
				filename = path2 + "/" + filename;
			result.push_back(filename);		
		}
	}

	if (dir && closedir(dir)) 
		goto err;
	
	std::sort( result.begin(), result.end() );
	
	return;

err:
	std::string msg = "Unable to list files in " + path + ":" + strerror(errno);
	if (dir) closedir(dir);	
	throw std::runtime_error(msg);	
}

void FileSystem::listDirs(std::vector<std::string>& result, const std::string& path, bool completePath) 
{
	std::string path2 = normalizePath(path) + "/";

	DIR*		dir		= NULL;
	struct dirent*	file		= NULL;	
	
	dir = opendir(path2.c_str());
		if (dir == NULL) 
		goto err;		

	for (;;)
	{
		file = readdir(dir);
		if (file == NULL) {
			if (errno == EBADF) 
				goto err;
			break;
		}

		if ((strcmp(file->d_name, ".")==0) || (strcmp(file->d_name, "..")==0))
			continue;
				
		int isfile = isfile__(path2 + "/" + file->d_name);
			if (isfile < 0) 
			goto err;

		if (isfile == 0)
		{
			std::string filename = file->d_name;
			if (completePath)
				filename = path + "/" + filename;
			result.push_back(filename);
		}
	}

	if (dir) {
		if (closedir(dir)) 
		goto err;
	}

	std::sort( result.begin(), result.end() );

	return;
err:
	std::string msg = "Unable to list directories in " + path + ":" + strerror(errno);
	if (dir) closedir(dir);	
	throw std::runtime_error(msg);	
}

size_t FileSystem::getFileSize(const std::string& path)
{
	std::string path2 = normalizePath(path);

	struct stat filestats;
	if (stat(path2.c_str(), &filestats) == -1)
	{
		if (errno == ENOENT) 
			return false;	
		throw std::runtime_error("Unable to get file stats for " + path + ": " + strerror(errno));				
	}    	
	return (size_t)filestats.st_size;
}

#endif

/*===========================================================================*/

void FileSystem::createFile(const std::string& path)
{
	createFile(path, "");
}

void FileSystem::createFile(const std::string& path, const std::string& msg)
{
	FILE* f = NULL;

	f = fopen(path.c_str(), "w+");
		if (f==NULL)
		goto err;

	if (msg.size())
		if (fputs(msg.c_str(), f) == EOF)
			goto err;

	fclose(f);
	return;

err:
	if (f) fclose(f);
	std::string err = "Cannot touch file '" + path + "': ";
	#if defined(WIN32) 
		err += GetLastErrorStr();		
	#elif defined(__linux__) || defined(linux)
		err += strerror(errno);
	#endif
	throw std::runtime_error(err);	
}

/*===========================================================================*/

std::string Path::getBasePath(const std::string& path)
{
	std::string::size_type pos = path.find_last_of("\\/");
	if (pos != std::string::npos)
		return path.substr(0, pos + 1);
	return "";
}

std::string Path::getFileName(const std::string& path)
{
	std::string::size_type pos;

	pos = path.find_last_of("\\/");
	if (pos != std::string::npos)
		return path.substr(pos + 1, path.length() - pos);


	return path;
}

std::string Path::getFileExt(const std::string& path)
{
	std::string::size_type pos = path.rfind('.');
	if (pos == std::string::npos)
		return "";
	return path.substr(pos + 1, path.length() - pos - 1);
}

std::string Path::changeExt(const std::string& path, const std::string& newext)
{
	std::string::size_type pos = path.rfind('.');
	if ((pos == std::string::npos) || (pos == 0))
		return path + newext;
	return path.substr(0, pos) + newext;	
}

std::string Path::removeExt(const std::string& path)
{
	std::string::size_type pos = path.rfind(".");
	if (pos == std::string::npos)
		return path;
	return path.substr(0, pos);
}


/*===========================================================================*/

}













