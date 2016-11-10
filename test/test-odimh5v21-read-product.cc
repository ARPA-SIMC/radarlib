
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

#include <stdio.h>
#include <ctime>
#include <stdexcept>
#include <iomanip>
#include <cmath>
#include <string>
#include <vector>

#include <radarlib/radar.hpp>

#define TESTFILE TESTDIR"/PROD-ODIMH5V21.h5"

using namespace OdimH5v21;
using namespace Radar;
using namespace std;

/*===========================================================================*/

int main(int argc, char* argv[])
{
/*	if (argc != 2) 
	{
		cout << "Usage: " << argv[0] << " <odimh5file>" << endl;
		return -1;
	}
*/
	std::string InputFile;
	//InputFile =argv[1];
	InputFile =TESTFILE;

	OdimFactory*	factory = NULL;
	ImageObject*	image	= NULL;

	try
	{
		factory = new OdimFactory();
		image	= factory->openImageObject(InputFile);

	std::vector <std::string> ProductType;
	SourceInfo source ;
	time_t ProductTime;

	// get product type to check if it's a SURF product
	// get data to check if it's DBZH 
	ProductType = image->getProductsType();
//	for (unsigned i=0; i< ProductType.size(); i++) std::cout<<"Prodotto "<<i<<" Contiene "<<ProductType[i]<<std::endl;

	}
	catch (std::exception& stde)
	{
		cerr << "Errore di esecuzione: " << stde.what() << endl;
	}
	catch (...)
	{
		cerr << "Errore di esecuzione sconosciuto" << endl;
	}

	delete image;
	delete factory;

//	getchar();

	return 0;
}



















