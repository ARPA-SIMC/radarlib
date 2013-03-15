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
 *  \brief Functions and classes that implement Physics formulas
 */ 

#ifndef __RADAR_FORMULA_HPP__
#define __RADAR_FORMULA_HPP__

#include <limits>
#include <climits>
#include <cmath>

namespace Radar {

/*===========================================================================*/

/*! 
 * \brief Niquist velocity class
 * 
 * \n This class provide functions to calculate/convert a nyquist velocity
 */
class NyquistVelocity
{
public:
	/*!
	 * \brief
	 * Calculate nyquist velocity (meters/seconds) using PRF and wavelength 
	 * \param prf			Pulse Repetition Frequency expressed as integer number of pulses per second
	 * \param waveLength_meters	Wave length expressed in meters
	 */
	static inline double calculate(long prf, double waveLength_meters)
	{
		//V = lunghezza d'onda (m) * PRF / 4
		return waveLength_meters * (double)prf / 4;	
	}
	/*!
	 * \brief
	 * Calculate nyquist velocity (meters/seconds) using dual PRF values and wavelength 
	 * 
	 * \param lowPRF			Pulse Repetition Frequency expressed as integer number of pulses per second
	 * \param highPRF			Pulse Repetition Frequency expressed as integer number of pulses per second
	 * \param waveLength_meters		Wave length expressed in meters
	 */
	static inline double calculate(long lowPRF, long highPRF, double waveLength_meters)
	{	
		if (lowPRF == highPRF)
		{
			return calculate(highPRF, waveLength_meters);
		}
		else
		{		
			//     lunghezza d'onda (m)
			// V = --------------------------
			//     4 * (1/LOWPRF - 1/HIGHPRF)
			return waveLength_meters / 4 / ( 1 / (double)lowPRF - 1 / (double)highPRF);
		}
	}
};

/*===========================================================================*/

/*! 
 * \brief Wavelength velocity class
 * 
 * \n This class provide functions to calculate/convert a wave length
 */
class WaveLength
{
public:
	/*!
	 * \brief
	 * Calculate wave length expressed in meters using frequency
	 * 
	 * \param freqMHz		frequency expressed in MHz
	 */
	static inline double freqMHzToMeters(double freqMHz)
	{
		//           Vluce (m/s)   299792458       299.792458
		//lung. cm = ----------- = ------------- = ------------ 
		//           Hz (num/s)    MHz * 1000000   MHz
		return 299.792458 / freqMHz;
	}
	/*!
	 * \brief
	 * Calculate wave length expressed in centimeters using frequency
	 * 
	 * \param freqMHz		frequency expressed in MHz
	 */
	static inline double freqMHzToCM(double freqMHz)
	{
		//           Vluce (m/s) * 100   29979245800     29979.2458
		//lung. cm = ----------------- = ------------- = ------------ 
		//           Hz (num/s)          MHz * 1000000   MHz
		return 29979.2458 / freqMHz;
	}
};

/*===========================================================================*/

/*! 
 * \brief Weather Radar Average Power
 * 
 * \n This class provide functions to calculate/convert a weather radar average power
 */
class WeatherRadarAveragePower
{
public:
	/*!
	 * \brief
	 * Calculate Weather Radar Average Power
	 * 
	 * \param peakPwr	peak transmitter power output in Watts
	 * \param prf		pulse repetition frequency in pulses per second
	 * \param pulseWidth	pulse width in microseconds
	 * \returns		The average power (Watts)
	 */
	static inline double calculateWatts(double peakPwr, int prf, double pulseWidth)
	{
		//        PeakPower (Watts) x PRF (n/s) x PulseWidth (microsec)
		//P avg = -----------------------------------------------------
		//        1.000.000
		return peakPwr * (double)prf * pulseWidth / 1000000.;
	}
	/*!
	 * \brief
	 * Calculate Weather Radar Average Power
	 * 
	 * \param peakPwr	peak transmitter power output in Watts
	 * \param prf		pulse repetition frequency in pulses per second
	 * \param pulseWidth	pulse width in microseconds
	 * \returns		The average power (KiloWatts)
	 */
	static inline double calculateKWatts(double peakPwr, int prf, double pulseWidth)
	{
		return calculateWatts(peakPwr, prf, pulseWidth) / 1000.;
	}
	
};


/*===========================================================================*/

}

#endif
