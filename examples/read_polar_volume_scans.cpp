
/*===========================================================================*/
/* 
/* Questo programma legge tutte le elevazioni comprese tra due angoli
/* specificati e stampa angoli e tempi dei raggi nell'ordine originale in cui 
/* erano stati acquisiti
/*
/* Esempo di utilizzo:
/*	main.exe volume.h5 
/*
/*===========================================================================*/

#include <iostream>
using namespace std;

#include <radarlib/radar.hpp>
using namespace OdimH5v20;
using namespace Radar;

/*===========================================================================*/

int main(int argc, char* argv[])
{
	if (argc != 2) 
	{
		cout << "Usage: " << argv[0] << " <odimh5file>" << endl;
		return -1;
	}

	OdimFactory*	factory = NULL;
	PolarVolume*	volume	= NULL;
	std::vector<PolarScan*> scans;

	try
	{

		factory = new OdimFactory();

		volume	= factory->openPolarVolume(argv[1]);

		cout << "File convetions:    " << volume->getConventions() << endl;
		cout << "WHAT:" << endl;
		cout << " - Object:          " << volume->getObject() << endl;
		cout << " - Version:         " << volume->getVersion() << endl;
		cout << " - Date/Time:       " << volume->getDateTime() << endl;
		cout << " - Date/Time str:   " << timeutils::absoluteToString(volume->getDateTime()) << endl;
		cout << " - Source:          " << volume->getSource().toString() << endl;
		cout << "WHERE:" << endl;
		cout << " - Latitude:        " << volume->getLatitude() << endl;
		cout << " - Longitude:       " << volume->getLongitude() << endl;
		cout << " - Altitude:        " << volume->getAltitude() << endl;
		cout << "HOW:" << endl;
		cout << " - Task:            " << volume->getTaskOrProdGen() << endl;
		cout << " - Start epochs:    " << volume->getStartEpochs() << endl;
		cout << " - End epochs:      " << volume->getEndEpochs() << endl;
		cout << " - System:          " << volume->getSystem() << endl;
		cout << " - Software:        " << volume->getSoftware() << endl;
		cout << " - Software ver:    " << volume->getSoftwareVer() << endl;
		cout << " - ZR_A:            " << volume->getZR_A() << endl;
		cout << " - ZR_B:            " << volume->getZR_B() << endl;
		cout << " - KR_A:            " << volume->getKR_A() << endl;
		cout << " - KR_B:            " << volume->getKR_B() << endl;
		cout << " - Simulated:       " << volume->getSimulated() << endl;

		scans = volume->getScansBetween(-1., 5.);

		for (size_t i=0; i<scans.size(); i++)
		{
			PolarScan* scan = scans[i];

			/* estraggo vari dati che mi interessano */
			time_t startdatetime		= scan->getStartDateTime();
			time_t enddatetime		= scan->getEndDateTime();
			int numrays			= scan->getNumRays();
			int a1gate			= scan->getA1Gate();
			int direction			= scan->getDirection();
			std::vector<AZAngles> angles	= scan->getAzimuthAngles();
			std::vector<AZTimes>  times	= scan->getAzimuthTimes();

			cout << "------" << endl;
			cout << " SCAN " << endl;
			cout << "------" << endl;
			cout << "Rays:       " << numrays << endl;
			cout << "Star ttime: " << timeutils::absoluteToString(startdatetime) << endl;
			cout << "End time:   " << timeutils::absoluteToString(enddatetime)   << endl;
			cout << "A1gate:     " << a1gate << endl;
			cout << "Direction:  " << (direction > 0 ? "CW" : "CCW") << endl;
			
			/* stampo tutti i raggi */
			for (int i=0; i<numrays; i++)
			{
				/* traduco in base all'indice progressivo 'i' calcolo l'indice originale */
				int j = PolarScan::originaRayIndex(i, direction, numrays, a1gate);

				printf(
					"i %03d = ray %03d = time %s / %s - az: %03.03f / %03.03f \n",
					i,
					j,
					timeutils::absoluteToString( times[j].start ).c_str(),
					timeutils::absoluteToString( times[j].stop ).c_str(),
					angles[j].start,
					angles[j].stop
					);
									 
			}
					
		}
		
		cout << "Lettura eseguita!" << endl;
	}
	catch (std::exception& stde)
	{
		cerr << "Errore di esecuzione: " << stde.what() << endl;
	}
	catch (...)
	{
		cerr << "Errore di esecuzione sconosciuto" << endl;
	}

	for (size_t i=0; i<scans.size(); i++) delete scans[i];
	delete volume;
	delete factory;

	getchar();

	return 0;
}



















