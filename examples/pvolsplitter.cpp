
/*===========================================================================*/
/* 
/* Questo programma spezza un file OdimH5 PVOL in tanti file
/* uno per ogni elevazione e le relative quantita' 
/*
/* Esempo di utilizzo:
/*	main.exe volume.h5 
/*
/*===========================================================================*/

#include <radarlib/radar.hpp>
using namespace OdimH5v20;
using namespace Radar;

#include <vector>
#include <stdexcept>
#include <set>
#include <string>
#include <sstream>
#include <iostream>
#include <memory>
using namespace std;

/*===========================================================================*/

class OdimH5PVolSplitter
{
	protected: std::string			inputFilePath;
	protected: std::string			inputFileName;
	protected: std::string			outputBasePath;
	protected: OdimH5v20::OdimFactory*	factory;
	protected: OdimH5v20::PolarVolume*	inputPVOL;	

	public: OdimH5PVolSplitter()
	:inputFilePath()
	,inputFileName()
	,outputBasePath()
	,factory(NULL)
	,inputPVOL(NULL)
	{		
	}

	public: virtual ~OdimH5PVolSplitter()
	{
		closeInput();
	}

	public: virtual void split(const std::string& inputPath, const std::string& outPath = "")
	{
		inputFilePath	= inputPath;
		outputBasePath	= outPath.empty() ? Radar::Path::getBasePath(inputPath) : outPath;
		split();
	}

	protected: virtual void split()
	{
		try
		{
			openInput();
			exec();
			closeInput();
		}
		catch (...)
		{
			closeInput();
			throw;
		}
	}	

	protected: virtual void exec() = 0;

	protected: virtual void openInput()
	{
		factory		= new OdimH5v20::OdimFactory();
		inputPVOL	= factory->openPolarVolume(inputFilePath);				
		inputFileName	= Radar::Path::getFileName(inputFilePath);
	}

	protected: virtual void closeInput()
	{
		delete factory;		
		delete inputPVOL;	
		factory		= NULL;
		inputPVOL	= NULL;
		inputFileName	= ""; 
	}
};

class OdimH5PVolScanSplitter : public OdimH5PVolSplitter
{
	protected: virtual void exec()
	{
		int scanCount = inputPVOL->getScanCount();
		for (int s=0; s<scanCount; s++)
		{
			std::string outfilePath = this->outputBasePath + "/" + inputFileName + ".dataset" + Radar::stringutils::toString(s+1) + ".h5";
		
			std::auto_ptr<PolarScan>   inputScan	( inputPVOL->getScan(s) );			
			std::auto_ptr<PolarVolume> outputPVOL	( factory->createPolarVolume(outfilePath) );
			std::auto_ptr<PolarScan>   outputScan	( outputPVOL->createScan() );

			outputPVOL->getWhat()->import( inputPVOL->getWhat() );			
			outputPVOL->getWhere()->import( inputPVOL->getWhere() );
			outputPVOL->getHow()->import( inputPVOL->getHow() );

			outputScan->getWhat()->import( inputScan->getWhat() );			
			outputScan->getWhere()->import( inputScan->getWhere() );
			outputScan->getHow()->import( inputScan->getHow() );

			std::set<std::string> quantities = inputScan->getStoredQuantities();
			for (std::set<std::string>::iterator i = quantities.begin(); i != quantities.end(); i++)
			{
				std::string qname = *i;
				std::auto_ptr<PolarScanData>   inputQ	( inputScan->getQuantityData(qname) );			
				std::auto_ptr<PolarScanData>   outputQ	( outputScan->createQuantityData(qname) );

				outputQ->getWhat()->import( inputQ->getWhat() );			
				outputQ->getWhere()->import( inputQ->getWhere() );
				outputQ->getHow()->import( inputQ->getHow() );

				H5::AtomType	type	= inputQ->getDataType();
				int		height	= inputQ->getDataHeight();
				int		width	= inputQ->getDataWidth();				
				std::vector<char> buff ( type.getSize() * height * width );
				
				inputQ->readData(&(buff[0]));
				
				outputQ->writeData(&(buff[0]), width, height, type);
			}
		}
	}
};

class OdimH5PVolQuantitySplitter : public OdimH5PVolSplitter
{
	protected: virtual void exec()
	{
		int scanCount = inputPVOL->getScanCount();
		for (int s=0; s<scanCount; s++)
		{
			std::auto_ptr<PolarScan>   inputScan	( inputPVOL->getScan(s) );			

			std::set<std::string> quantities = inputScan->getStoredQuantities();
			for (std::set<std::string>::iterator i = quantities.begin(); i != quantities.end(); i++)
			{
				std::string qname = *i;

				std::auto_ptr<PolarScanData>   inputQ	( inputScan->getQuantityData(qname) );			

				std::string outfilePath = this->outputBasePath + "/" + inputFileName + ".dataset" + Radar::stringutils::toString(s+1) + "." + qname + ".h5";
			
				std::auto_ptr<PolarVolume>	outputPVOL	( factory->createPolarVolume(outfilePath) );
				std::auto_ptr<PolarScan>	outputScan	( outputPVOL->createScan() );
				std::auto_ptr<PolarScanData>	outputQ		( outputScan->createQuantityData(qname) );

				outputPVOL->getWhat()->import(	inputPVOL->getWhat() );			
				outputPVOL->getWhere()->import( inputPVOL->getWhere() );
				outputPVOL->getHow()->import(	inputPVOL->getHow() );

				outputScan->getWhat()->import(	inputScan->getWhat() );			
				outputScan->getWhere()->import( inputScan->getWhere() );
				outputScan->getHow()->import(	inputScan->getHow() );

				outputQ->getWhat()->import(	inputQ->getWhat() );			
				outputQ->getWhere()->import(	inputQ->getWhere() );
				outputQ->getHow()->import(	inputQ->getHow() );

				H5::AtomType	type	= inputQ->getDataType();
				int		height	= inputQ->getDataHeight();
				int		width	= inputQ->getDataWidth();				
				std::vector<char> buff ( type.getSize() * height * width );
				
				inputQ->readData(&(buff[0]));
				
				outputQ->writeData(&(buff[0]), width, height, type);
			}
		}
	}
};

/*===========================================================================*/

int main(int argc, char* argv[])
{
	if (argc != 2) 
	{
		cout << "Usage: " << argv[0] << " <odimh5file>" << endl;
		return -1;
	}

	try
	{
		//OdimH5PVolScanSplitter s;
		OdimH5PVolQuantitySplitter s;
		s.split(argv[1]);
	}
	catch (std::exception& stde)
	{
		cerr << "Errore di esecuzione: " << stde.what() << endl;
	}
	catch (...)
	{
		cerr << "Errore di esecuzione sconosciuto" << endl;
	}

	return 0;
}

/*===========================================================================*/

















