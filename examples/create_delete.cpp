/*===========================================================================*/
/* 
/* Questo programma crea un volume polare utilizzando le classi specifiche di OdimH5
/* Poi cancella qualche dataset e qualche data
/* 
/* Alla fine utilizziamo un dumper per stampare a video il risultato 
/*
/* Esempo di utilizzo:
/*	main.exe volume.h5 
/*
/*===========================================================================*/


#include <iostream>

#include <radarlib/radar.hpp>
using namespace OdimH5v20;

#define NUMDATASETS	10
#define NUMDATAS	10

static int create_example(const char* srcfile)
{
	OdimFactory*		factory = NULL;
	OdimObject*		object	= NULL;	
	OdimObjectDumper*	dumper	= NULL;

	try
	{
		/* creazione di una factory */
		factory		= new OdimFactory();
		
		/* creazione di un oggetto generico */
		object		= factory->create(srcfile);

		object->setObject("prova");

		for (int i=0; i<NUMDATASETS; i++)
		{
			/* creazione di un dataset generico */
			OdimDataset* dataset = object->createDataset();			

			dataset->getWhat()->set("indice", i+1);				

			for (int j=0; j<NUMDATAS; j++)
			{
				OdimData* data = dataset->createData();
				data->getWhat()->set("indice", j+1);
				delete data;						
			}

			delete dataset;
		}

		/* stampiamo a video il risultato */
		dumper = factory->getDumper(); 
		dumper->dump(object); 		

		std::cout << "Esecuzione terminata" << std::endl;
	}
	catch (std::exception& stde)
	{
		std::cerr << "Errore di esecuzione: " << stde.what() << std::endl;
	}
	catch (...)
	{
		std::cerr << "Errore sconociuto" << std::endl;
	}

	delete dumper;
	delete object;
	delete factory;

	return 0;
}

static int remove_example(const char* srcfile)
{	
	OdimFactory*		factory = NULL;
	OdimObject*		object	= NULL;	
	OdimObjectDumper*	dumper	= NULL;

	try
	{
		/* creazione di una factory */
		factory		= new OdimFactory();
		
		/* creazione di un oggetto generico */
		object		= factory->open(srcfile);

		OdimDataset* dataset = object->getDataset(0);

		dataset->removeData(5);

		delete dataset;

		object->removeDataset(5);

//		for (int i=0; i<NUMDATASETS/2; i++)
//		{
//std::cout << "-----------------------------------------------------" << std::endl;
//			object->removeDataset(i);
//			//else
//			//{
//			//	/* creazione di un dataset generico */
//			//	OdimDataset* dataset = object->getDataset(i);
//
//			//	for (int j=NUMDATAS-1; j>=0; j--)
//			//	{		
//			//		if ((j % 2) == 0)
//			//			dataset->removeData(j);
//			//	}
//
//			//	delete dataset;
//			//}
//		}

		/* stampiamo a video il risultato */
		//dumper = factory->getDumper(); 
		//dumper->dump(object); 		

		std::cout << "Esecuzione terminata" << std::endl;
	}
	catch (std::exception& stde)
	{
		std::cerr << "Errore di esecuzione: " << stde.what() << std::endl;
	}
	catch (...)
	{
		std::cerr << "Errore sconociuto" << std::endl;
	}

	delete dumper;
	delete object;
	delete factory;

	return 0;
}

int main(int argc, char* argv[])
{
	if (argc != 2) 
	{
		std::cout << "Usage: " << argv[0] << " <odimh5file>" << std::endl;
		return -1;
	}

	try
	{
		create_example(argv[1]);		
		remove_example(argv[1]);
	}
	catch (...)
	{
	}

	getchar();

	return 0;
}



