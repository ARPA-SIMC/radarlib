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
#include <radarlib/odimh5v20_hdf5.hpp>
using namespace OdimH5v20;


int main(int argc, char* argv[])
{
	if (argc != 2) 
	{
		std::cout << "Usage: " << argv[0] << " <odimh5file>" << std::endl;
		return -1;
	}

	H5::H5File*	file	= NULL;
	H5::Group*	root	= NULL;
	H5::Group*	group	= NULL;

	try
	{
		file	= HDF5File::open(argv[1], H5F_ACC_TRUNC);

		root	= HDF5File::getRoot(file);

		HDF5Group::ensureChild(root, "xxxa");
		HDF5Group::ensureChild(root, "xxxb");
		HDF5Group::ensureChild(root, "xxxc");
		H5::Group* d = HDF5Group::ensureGetChild(root, "xxxd");
		HDF5Group::ensureChild(root, "xxxe");
		HDF5Group::ensureChild(root, "xxxf");
		HDF5Group::ensureChild(root, "xxxg");

		std::cout << "numattr: " << d->getNumAttrs();
		
		HDF5Group::removeChild(root, "xxxe");
		
		std::cout << "numattr: " << d->getNumAttrs();		
		
	}
	catch(H5::Exception& e)
	{
		//e.
		e.printError(stdout);
	}

	delete group;
	delete root;
	delete file;

	getchar();

	return 0;
}



