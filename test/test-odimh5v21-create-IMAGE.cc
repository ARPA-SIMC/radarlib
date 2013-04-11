/*===========================================================================*/
/*
/* Questo programma crea un image utilizzando le classi specifiche di OdimH5
/*
/*===========================================================================*/


#include <iostream>
#include <assert.h>

#include <radarlib/radar.hpp>
using namespace OdimH5v21;




bool test_crea_IMAGE() 
{
	/* assicuriamoci che la installata della libreria sia quella giusta */
	Radar::RadarLibrary::checkVersion();

	OdimFactory*		factory = NULL;
	ImageObject*		image	= NULL;

	std::set<std::string>	quantities;

	OdimH5v21::Specification::getStandardQuantities(quantities);

	try
	{
		/* creazione di una factory */
		factory		= new OdimFactory();

		/* creazione di un oggetto generico */
		image		= factory->createImageObject(TESTDIR"/IMAGE-ODIMh5V21.h5");

		/* what */

		image->setDateTime( Radar::timeutils::mktime(2000,01,02,03,04,05));
		SourceInfo source;
		source.setWMO("wmo");
		source.setOperaRadarSite("rad");
		source.setOriginatingCenter(1);
		source.setPlace("plc");
		source.setCountry(2);
		source.setComment("cmt");
		image->setSource(source);

		/* where */

  image->setLL_Latitude(40.0);
  image->setLL_Longitude(10.0);
  image->setLR_Latitude(40.0); 
  image->setLR_Longitude(15.0);
  image->setUL_Latitude(45.0); 
  image->setUL_Longitude(10.0);
  image->setUR_Latitude(45.0);
  image->setUR_Longitude(15.0);

  image->setXSize(1000.);
  image->setYSize(1000);
  image->setXScale(1000.);
  image->setYScale(1000.);
  image->setProjectionArguments("+proj=gnom +lat_0=44.7914N +lon_0=10.4992E +units=m +ellps=sphere");

		/* how */

		image->setTaskOrProdGen("prova");
		image->setStartEpochs(Radar::timeutils::mktime(2000,01,02,03,04,05));
		image->setEndEpochs(Radar::timeutils::mktime(2000,01,02,03,04,05));
		image->setSystem("ARPA-SIMC");


		/* stampiamo a video il risultato */

		std::cout << "Esecuzione terminata" << std::endl;
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

	delete image;
	delete factory;
		return true;

}


int main (){

 	assert(test_crea_IMAGE ());

	return 0;

}
