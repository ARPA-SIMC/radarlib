/*===========================================================================*/
/* 
/* Questo programma legge gli attributi scritti dall'esempio write_attributes.cpp
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
	OdimObject*	odimobj	= NULL;

	try
	{
		/* creazione factory */
		factory = new OdimFactory();

		/* apertura volume */
		odimobj	= factory->open(argv[1]);
	
		/* esempi di lettura diretto con metodi specifici  */

		std::string	object   = odimobj->getObject();	
		time_t		datetime = odimobj->getDateTime();	
		
		/* esempi di lettura con metodi generici */

		bool           boolval   = odimobj->getWhat()->getBool("booleano");
		char           charval   = odimobj->getWhat()->getChar("char");
		unsigned char  ucharval  = odimobj->getWhat()->getUChar("unsigned char");
		short          shortval  = odimobj->getWhat()->getShort("short");
		unsigned short ushortval = odimobj->getWhat()->getUShort("unsigned short");
		int            intval    = odimobj->getWhat()->getInt("int");
		unsigned int   uintval   = odimobj->getWhat()->getUInt("unsigned int");
		int64_t        int64val  = odimobj->getWhat()->getLong("long"); /* il nome long si riferisce sempre a interi a 64 bit */
		float          floatval  = odimobj->getWhat()->getFloat("float");
		double         doubleval = odimobj->getWhat()->getDouble("double");
		std::string    stringval = odimobj->getWhat()->getStr("string");

		/* esempi di lettura di sequenze di valori con metodi generici */

		std::vector<bool> bools  = odimobj->getWhat()->getBools("bools");

		std::vector<int> ints    = odimobj->getWhat()->getInts("ints");
		
		std::vector<double> doubles = odimobj->getWhat()->getDoubles("doubles");

		std::vector<std::string> strings = odimobj->getWhat()->getStrings("strings"); 

		/* esempio di lettura di sequenze di coppie di valori con metodi generici */

		std::vector<std::pair<float,float> > angles;	

		angles = odimobj->getWhat()->getFloatPairs("angles");	

		/* esempio di lettura di sequenze con metodi specific */

		AZTimes tempo1;
		AZTimes tempo2;

		std::vector<AZTimes> tempi = odimobj->getWhat()->getAZTimes("tempi");	

		tempo1 = tempi[0];
		tempo2 = tempi[1];

		
		std::cout << "Lettura eseguita!" << std::endl;
	}
	catch (std::exception& stde)
	{
		std::cerr << "Errore di esecuzione: " << stde.what() << std::endl;
	}
	catch (...)
	{
		std::cerr << "Errore sconosciuto" << std::endl;
	}

	delete odimobj;
	delete factory;

	return 0;
}



















