
/*===========================================================================*/
/* 
/* Questo programma crea un file odim h5 e scrive vari attributi diversi
/* in vari modi diversi per far vedere come si usano le funzioni set.
/*
/* Esempo di utilizzo:
/*	main.exe volume.h5 
/*
/*===========================================================================*/


#include <iostream>

#include <radarlib/radar.hpp>
using namespace OdimH5v20;

int main(int argc, char* argv[])
{
	if (argc != 2) 
	{
		std::cerr << "Usage: " << argv[0] << " <odimh5file>" << std::endl;
		return -1;
	}

	OdimFactory*	factory = NULL;
	PolarVolume*	volume	= NULL;

	try
	{
		/* creazione factory */
		factory = new OdimFactory();

		/* creazione volume */
		volume	= factory->createPolarVolume(argv[1]);

		/* esempi di utilizzo diretto con nomi Odim */

		volume->setObject( "tipo oggetto" );
		volume->setDateTime( time(NULL) );	
		volume->setLongitude( 1.2 );		
		
		/* esempi di utilizzo indiretto con nomi inventati */

		bool  variabile_booleana	= true;
		char  variabile_char		= -128;
		short variabile_short		= -32000;
		int   variabile_int		= 2000000000;
		float variabile_float		= 1.2f;

		volume->getWhat()->set("booleano",		true);
		volume->getWhat()->set("char",			variabile_char);
		volume->getWhat()->set("unsigned char",		255);
		volume->getWhat()->set("short",			variabile_short);
		volume->getWhat()->set("unsigned short",	64000);
		volume->getWhat()->set("int",			variabile_int);
		volume->getWhat()->set("unsigned int",		1);
		volume->getWhat()->set("long",			-1);
		volume->getWhat()->set("float",			variabile_float);
		volume->getWhat()->set("double",		3.4);
		volume->getWhat()->set("string",		"valore");

		/* esempi di scritture di sequenze di valori */

		std::vector<bool> bools;
		bools.push_back(true);
		bools.push_back(false);
		bools.push_back(true);
		volume->getWhat()->set("bools", bools);

		std::vector<int> ints;
		ints.push_back(1);
		ints.push_back(2);
		ints.push_back(3);
		volume->getWhat()->set("ints", ints);
		
		std::vector<double> doubles;
		doubles.push_back(1);
		doubles.push_back(2);
		doubles.push_back(3);
		volume->getWhat()->set("doubles", doubles);

		std::vector<std::string> strings;	
		strings.push_back("stringa 1");
		strings.push_back("stringa 2");
		strings.push_back("stringa 3");
		volume->getWhat()->set("strings", strings); 

		/* esempio di scrittura di sequenze di coppie di valori */

		std::pair<float,float> coppiafloat(7. , 8.); /* esempio di dichiarazione e inizializzazione di coppia di valori */

		std::vector<std::pair<float,float> > angles;	/* dichiarazioen di vettore di coppie di numeri reali */
		angles.push_back( std::pair<float,float>(1. , 2.) ); /* esempio di creazione "al volo" di una coppia */
		angles.push_back( std::pair<float,float>(3. , 4.) );
		angles.push_back( std::pair<float,float>(5. , 6.) );		
		angles.push_back( coppiafloat );
		volume->getWhat()->set("angles", angles);	

		/* esempio di scrittura di attributi odim speciali */

		AZTimes tempo1;		//esempio dichiarazione di una coppia di tempo senza inizializzazione dei valori
		tempo1.start = 1;	
		tempo1.stop  = 2;

		AZTimes tempo2(2,3);	//esempio dichiarazione e inizializzazione dei valori

		std::vector<AZTimes> tempi;	
		tempi.push_back(tempo1);
		tempi.push_back(tempo2);		
		volume->getWhat()->set("tempi", tempi);		


		std::cerr << "Scrittura eseguita!" << std::endl;
	}
	catch (std::exception& stde)
	{
		std::cerr << "Errore di esecuzione: " << stde.what() << std::endl;
	}
	catch (...)
	{
		std::cerr << "Errore sconosciuto" << std::endl;
	}

	delete volume;
	delete factory;

	return 0;
}



















