/*===========================================================================*/
/*
/* Questo programma testa la creazione di un volume polare utilizzando le classi specifiche di OdimH5
/*
/*===========================================================================*/


#include <iostream>
#include <assert.h>

#include <radarlib/radar.hpp>
using namespace OdimH5v21;

bool test_creazione_Pvol ()
{

	/* assicuriamoci che la installata della libreria sia quella giusta */
	Radar::RadarLibrary::checkVersion();

	OdimFactory*		factory = NULL;
	PolarVolume*		volume	= NULL;
	OdimObjectDumper*	dumper	= NULL;

	std::set<std::string>	quantities;

	OdimH5v21::Specification::getStandardQuantities(quantities);

	try
	{
		/* creazione di una factory */
		factory		= new OdimFactory();

		/* creazione di un oggetto generico */
		volume		= factory->createPolarVolume(TESTDIR"/PVOL-ODIMH5V21.h5");

		/* what */

		//volume->setObject();	non serve, viene settato automaticamente
		//volume->setVersion();	non serve, viene settato automaticamente
		volume->setDateTime( Radar::timeutils::mktime(2000,01,02,03,04,05));

		SourceInfo source;
		source.setWMO("wmo");
		source.setOperaRadarSite("rad");
		source.setOriginatingCenter(1);
		source.setPlace("plc");
		source.setCountry(2);
		source.setComment("cmt");
		volume->setSource(source);

		/* where */

		volume->setLongitude		(11.6236);	//san pietro capofiume
		volume->setLatitude		(44.4567); 	//san pietro capofiume
		volume->setAltitude		(31.); 		//san pietro capofiume

		/* how */

		volume->setTaskOrProdGen	("task");

		volume->setStartEpochs		(Radar::timeutils::mktime(2001,02,03,04,05,06));		
		volume->setEndEpochs		(Radar::timeutils::mktime(2002,03,04,05,06,07));		
		volume->setSystem		("system");
		volume->setSoftware		("software");
		volume->setSoftwareVer		("sw_version");
		volume->setZR_A			(10.);		
		volume->setZR_B			(11.);		
		volume->setKR_A			(12.);		
		volume->setKR_B			(13.);		
		volume->setSimulated		(true);

		volume->getHow()->set("attributo intero inventato", (int)100);
		volume->getHow()->set("attributo stringa inventato", "valore stringa inventato");

		for (int s=0; s<10; s++)
		{
			/* creazione di un dataset generico */
			PolarScan* scan =  volume->createScan();

			const int NUMBINS = 10;
			const int NUMRAYS = 100;

			/* set degli attributi, notare che i gruppi WHAT,WHERE,HOW non sono esplicitati, sono gestiti automaticamente nell'implementazione */

			//scan->setProduct()	non serve, settato automaticamente
			//scan->setProdPar()	non serve nei volumi polari
			//scan->setQuantity()	non usato a questo livello nei volumi polari
			scan->setStartDateTime	( Radar::timeutils::mktime(2000+s,02,03,04,05,06) );
			scan->setEndDateTime	( Radar::timeutils::mktime(2000+s,02,03,04,05,06) );
			//scan->setNodata()	non usato a questo livello nei volumi polari
			//scan->setUndetect()	non usato a questo livello nei volumi polari
			//scan->setOffset()	non usato a questo livello nei volumi polari
			//scan->setGain()	non usato a questo livello nei volumi polari
			scan->setEAngle		((double)s * 3.);
			scan->setA1Gate		(s);
			scan->setNumBins	(NUMBINS);
			scan->setNumRays	(NUMRAYS);
			scan->setRangeStart	(0);
			scan->setRangeScale	(1000);
			scan->setRadarHorizon	((double)(1000 * NUMBINS) / 1000.);	//facciamo che il raggio e' 100km

			scan->setBeamWidth	(0.1);
			scan->setWaveLength	(0.1);
			scan->setRPM		(3);
			scan->setLowPRF		(300);
			scan->setHighPRF	(600);

			scan->getWhat()->set("attributo intero inventato", (int)100);
			scan->getWhat()->set("attributo stringa inventato", "valore stringa inventato");

		
			std::vector<AZAngles> azangles;

			for (int i=0; i<NUMRAYS; i++)
					azangles.push_back(AZAngles(360./(NUMRAYS-1.)*i,360./(NUMRAYS-1.)*(i+1)));
			scan->setAzimuthAngles(azangles);

			std::vector<double> elangles;
			for (int i=0; i<NUMRAYS; i++)
					elangles.push_back(i);
			scan->setElevationAngles(elangles);

			/* creiamo un gruppo per ogni quantita' standard */
			for (std::set<std::string>::iterator i=quantities.begin(); i!=quantities.end(); i++)			
			{
				std::string quantityName = *i;

				/* creazionne della quantita WRAD */
				/* per scrivere questa quantita' usiamo le funzioni di basso livello */
				/* scrivendo direttamente dei byte scritti direttamente come vogliamo */

				PolarScanData* data = scan->createQuantityData(quantityName);

				data->setNodata		(0.);
				data->setUndetect	(0.);
				data->setOffset		(0.);
				data->setGain		(1.);

				data->getWhat()->set("attributo intero inventato", (int)100);
				data->getWhat()->set("attributo stringa inventato", "valore stringa inventato");

				/* creazione di una matrice di byte con dei valori stampabili */
				/* per comodita' usiamo dalle lettere maiuscole in su */
				RayMatrix<unsigned char> matrixW(NUMRAYS,NUMBINS);

				for (int i=0; i<NUMRAYS; i++)
					for (int j=0; j<NUMBINS; j++)
						matrixW.elem(i,j) = 65 + ((i * j) % 120);

				data->writeData(matrixW);

				delete data;

				/* creazionne della quantita VRAD in formato 8bit partendo da valori float */
				/* per scrivere questa quantita' usiamo le funzioni di ALTO livello */
				/* la matrice la riempiamo di valori float e poi la conversione a 8bit */
			 	/* la facciamo fare alla libreria in fase di scrittura */

				PolarScanData* data2 = scan->createQuantityData(PRODUCT_QUANTITY_VRAD);

				/* inventiamoci un gain e un offset per i nostri dati */
				double offset	= 123.456;
				double gain	= (NUMRAYS * NUMBINS * 0.5 - offset) / 256.;

				data2->setNodata	(0.);
				data2->setUndetect	(0.);
				data2->setOffset	((double)offset);
				data2->setGain		((double)gain);


				/* creazione di una matrice di byte con dei valori stampabili */
				/* per comodita' usiamo dalle lettere maiuscole in su */
				RayMatrix<float> matrixV(NUMRAYS,NUMBINS);

				for (int i=0; i<NUMRAYS; i++)
					for (int j=0; j<NUMBINS; j++)
		 				matrixV.elem(i,j) = (float)(i * j * 0.5 + offset);

				data2->writeAndTranslate(matrixV, (float)offset, (float)gain, H5::PredType::NATIVE_UINT8);

				delete data2;
			}

			delete scan;
		}

		/* stampiamo a video il risultato */
		/* dumper = factory->getDumper(); */
		/* dumper->dump(volume); */

	//	std::cout << "Esecuzione terminata" << std::endl;
	}
	catch (std::exception& stde)
	{
		std::cerr << "Errore di esecuzione: " << stde.what() << std::endl;
		return false;
	}
	catch (...)
	{
		std::cerr << "Errore sconociuto" << std::endl;
		return false;
	}

	delete dumper;
	delete volume;
	delete factory;
	return true  ;

}

int main (){

 	assert(test_creazione_Pvol ());

	return 0;

}



