
/*===========================================================================*/
/* 
/* Questo programma apre un volume e ne crea una copia copiando solo
/* gli attributi dei gruppi what, where e how della radice 
/*
/* Esempo di utilizzo:
/*	main.exe volume.h5 copia.h5 
/*
/*===========================================================================*/

#include <iostream>
using namespace std;

#include <radarlib/radar.hpp>
using namespace OdimH5v20;

/*===========================================================================*/

int main(int argc, char* argv[])
{
	if (argc != 3) 
	{
		cout << "Usage: " << argv[0] << " <odimh5filesorgente> <odimh5filedestinazione>" << endl;
		return -1;
	}

	OdimFactory*	factory = NULL;
	PolarVolume*	volume1	= NULL;
	PolarVolume*	volume2	= NULL;

	try
	{

		factory = new OdimFactory();

		/* apriamo il volume di origine */

		volume1	= factory->openPolarVolume(argv[1]);

		/* creiamo il volume di destinazione */

		volume2	= factory->createPolarVolume(argv[2]);

		/* copiamo ogni gruppo di attributi della radice */

		volume2->getWhat()->import( volume1->getWhat() );
		volume2->getWhere()->import( volume1->getWhere() );
		volume2->getHow()->import( volume1->getHow() );

		cout << "Copia eseguita!" << endl;
	}
	catch (std::exception& stde)
	{
		cerr << "Errore di esecuzione: " << stde.what() << endl;
	}
	catch (...)
	{
		cerr << "Errore di esecuzione sconosciuto" << endl;
	}

	delete volume1;
	delete volume2;
	delete factory;

	return 0;
}



















