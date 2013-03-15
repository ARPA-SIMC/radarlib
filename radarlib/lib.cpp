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

#include <radarlib/lib.hpp>

#include <stdexcept>
#include <sstream>

/*===========================================================================*/
/* RADARLIB CLASS */
/*===========================================================================*/

namespace Radar 
{

int RadarLibrary::getVersion(void)
{
	return RADARLIB_MAKEVERSION(RADARLIB_MAJOR, RADARLIB_MINOR, RADARLIB_BUILD);
}

void RadarLibrary::checkVersion(int clientVersion)
{
	/* per ora ci limitiamo a controllare che la versione richiesta non sia superiore a quella disponibile */
	if (clientVersion > getVersion())
		throwVersionError(clientVersion);
}

void RadarLibrary::throwVersionError(int clientVersion)
{
	/* per ora ci limitiamo a controllare che la versione richiesta dal programma */
	/* sia inferiore a quella interna alla libreria */

	int cbuild = clientVersion % 100;		clientVersion -= cbuild;
	int cminor = (clientVersion / 100) % 100;	
	int cmajor = clientVersion / 10000;

	int version = getVersion();
	int build = version % 100;		version -= build;
	int minor = (version / 100) % 100;	
	int major = version / 10000;

	std::ostringstream ss;
	ss << "Installed Radar Library version is " << major << "." << minor << "." << build << ". ";
	ss << "Required version >= " << cmajor << "." << cminor << "." << cbuild << "!"; 
	throw std::logic_error(ss.str());
}

}

/*===========================================================================*/

int radarlib_get_version()
{
	return RADARLIB_MAKEVERSION(RADARLIB_MAJOR, RADARLIB_MINOR, RADARLIB_BUILD);
}

/*===========================================================================*/


