
/*===========================================================================*/
/*
/* Questo programma fa il dump testuale di un file odimh5
/*
/* Esempi:
/*	main.exe volume.h5               -> scrive su stdout
/*	main.exe volume.h5 prova.txt     -> scrive sull file prova.txt
/*
/*===========================================================================*/

#include <iostream>
#include <radarlib/radar.hpp>

int main(int argc, char* argv[])
{
	char* input;
	char* output;

	if (argc == 2)
	{
		input  = argv[1];
		output = NULL;
	}
	else if (argc == 3)
	{
		input  = argv[1];
		output = argv[2];
	}
	else
	{
		std::cerr << "Usage: " << argv[0] << " <odimh5file> [outputfile]" << std::endl;
		return -1;
	}

	OdimH5v20::OdimFactory*		factory = NULL;
	OdimH5v20::OdimObject*		object	= NULL;
	OdimH5v20::OdimObjectDumper*	dumper	= NULL;

	try
	{
		/* creo la factory */
		factory = new OdimH5v20::OdimFactory();

		/* apro l'oggetto */
		object = factory->open(input);

		/* creo un dumper */
		dumper	= factory->getDumper();

		/* stampo su video o su file */
		if (output == NULL)
		{
			dumper->dump(object);
		}
		else
		{
			std::ofstream fout;
			fout.exceptions(std::ios::failbit);
			fout.open(output, std::ios::binary);
			dumper->dump(object, fout);
			fout.close();
		}

		std::cout << "Dump terminato!"<< std::endl;
	}
	catch (std::exception& stde)
	{
		std::cerr << "Errore durante l'esecuzione: " << stde.what() << std::endl;
	}
	catch (...)
	{
		std::cerr << "Errore sconosciuto" << std::endl;
	}

	delete object;
	delete dumper;
	delete factory;

	return 0;
}



















