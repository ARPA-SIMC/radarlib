
/*===========================================================================*/
/* 
/* Questo programma legge tutte le elevazioni di un volume polare e 
/* stampa a video le grandezze WRAD, VRAD, DBZH, TH di tutti i raggi che 
/* stanno tra 15 e 45 gradi
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

/* funzione ausiliaria che stampa i valori di una quantita' indicata
  prendendo i raggi indicati dalla scansione passata */
void dump_rays(const char* quantityName, PolarScan* scan, const std::vector<int> raysindex)
{
	cout << "Dumping " << quantityName << " values..." << endl;
	
	PolarScanData* data = scan->getQuantityData(quantityName);
		
	H5::AtomType atom	= data->getBinType();
	
	std::cout << "prec:  " << atom.getPrecision() << std::endl;
	std::cout << "order: " << atom.getOrder() << std::endl;
	std::cout << "size:  " << atom.getSize() << std::endl;

	int bins = data->getNumBins();
	int rays = data->getNumRays();

	RayMatrix<float> matrix;

	data->readTranslatedData(matrix);
	
	for (size_t i=0; i<raysindex.size(); i++)
	{		
		int ray = raysindex[i];
		cout << "Raggio n. " << ray << ": ";
		for (int b=0; b<bins; b++)
			cout << matrix.elem(ray, b) << " ";
		cout << endl;
	}
	cout << endl;

	delete data;
}

template <class T> static void writeVector(const std::vector<T>& v)
{
	for (size_t i=0; i<v.size(); i++)
		std::cout << v[i] << " ";
}

int main(int argc, char* argv[])
{
	if (argc != 2) 
	{
		cout << "Usage: " << argv[0] << " <odimh5file>" << endl;
		return -1;
	}

	OdimFactory*	factory = NULL;
	PolarVolume*	volume	= NULL;

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

		int numElevazioni = volume->getScanCount();

		cout << "Numero scansioni: " << numElevazioni << endl;

		std::vector<double> scanAngles = volume->getScanAngles();

		cout << "angoli scansioni: "; writeVector(scanAngles); cout << endl;

		std::vector<double> elevationAngles = volume->getElevationAngles();

		cout << "angoli elevazioni (duplicati esclusi): "; writeVector(elevationAngles); cout << endl;
		
		for (int i=1; i<=numElevazioni; i++)
		{
			PolarScan* scan = volume->getScan(i);

			double elevation	= scan->getEAngle();
			
			cout << "Scansione n. "<<i<<" (elevazione: " << elevation << ")" << endl;

			int numRaggi		= scan->getNumRays();
			
			cout << "Raggi: " << numRaggi << endl;

			/* se gli azimuth angles sono indicati uso quelli */

			std::vector<int> raggiDaGuardare;		
			std::vector<AZAngles> angles = scan->getAzimuthAngles();
			if (angles.size())
			{
				for (int r=0; r<numRaggi; r++)
					if ((angles[r].start >= 15.) && (angles[r].stop < 45.))
						raggiDaGuardare.push_back(r);
			}	
			else
			{
				double step = 360. / numRaggi;
				double startangle = 0;
				for (int i=0; i<numRaggi; i++)
				{
					if (startangle >= 15. && startangle < 45.)
						raggiDaGuardare.push_back(i);
					startangle += step;
				}
			}

			if (scan->hasQuantityData(PRODUCT_QUANTITY_WRAD))
				dump_rays(PRODUCT_QUANTITY_WRAD, scan, raggiDaGuardare);

			if (scan->hasQuantityData(PRODUCT_QUANTITY_VRAD))
				dump_rays(PRODUCT_QUANTITY_VRAD, scan, raggiDaGuardare);

			if (scan->hasQuantityData(PRODUCT_QUANTITY_DBZH))
				dump_rays(PRODUCT_QUANTITY_DBZH, scan, raggiDaGuardare);

			if (scan->hasQuantityData(PRODUCT_QUANTITY_TH))
				dump_rays(PRODUCT_QUANTITY_TH, scan, raggiDaGuardare);
			
			delete scan;
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

	delete volume;
	delete factory;

	getchar();

	return 0;
}



















