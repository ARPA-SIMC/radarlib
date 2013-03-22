
/*===========================================================================*/
/*
/* Questo programma fa lo scan di un OdimH5 file e visualizza alcune
/* informazioni. E' stato usato come base per sviluppare l'estensione allo
/* scanner di arkimet
/*
/* Esempo di utilizzo:
/*	main.exe volume.h5
/*
/*===========================================================================*/

#include <radarlib/radar.hpp>
#include <radarlib/debug.hpp>
using namespace OdimH5v20;
using namespace Radar;

#include <vector>
#include <stdexcept>
#include <set>
#include <string>
#include <sstream>
#include <memory>
#include <iostream>
//using namespace std;

/*===========================================================================*/

struct Metadata
{
	void create() { }

};

/*===========================================================================*/

class OdimScanner
{
public:
	OdimScanner();
	virtual ~OdimScanner();

	static void scanOdimH5(const std::string& path, Metadata& md);

	virtual void open(const std::string path);
	virtual bool next(Metadata& md);
	virtual void close();

//REFTIME
//OBJECT:<object>,<prod>
//PRODPAR:<val>,<val>,....
//SOURCE:<WMO>,<RAD>,<PLC>
//TASK:<val>
//ORIGIN:<lat>,<lon>,<alt>
//EANGLE:<val>,<val>,...
//QUANTITY:<val>,<val>,...


private:
	OdimH5v20::OdimObject*	odimObj;
	virtual void getOdimObjectData(OdimH5v20::OdimObject* obj, Metadata& md);
	virtual void getPVOLData(OdimH5v20::PolarVolume* obj, Metadata& md);
	virtual void buildRefTime(time_t datetime, Metadata& md);
	virtual void buildObject(const std::string& object, const std::string& prod, Metadata& md);
	virtual void buildProdPar(const std::vector<double>& values, Metadata& md);
	virtual void buildSource(const OdimH5v20::SourceInfo& source, Metadata& md);
	virtual void buildTask(const std::string& task, Metadata& md);
	virtual void buildOrigin(double lat, double lon, double alt, Metadata& md);
	virtual void buildEangle(const std::vector<double>& values, Metadata& md);
	virtual void buildQuantity(const std::set<std::string>& values, Metadata& md);
	virtual void throwEx(std::exception& e);
};

OdimScanner::OdimScanner()
:odimObj(NULL)
{
}

OdimScanner::~OdimScanner()
{
	delete odimObj;
}

void OdimScanner::scanOdimH5(const std::string& path, Metadata& md)
{
	OdimScanner scanner;
	scanner.open(path);
	while (scanner.next(md))
		;
	scanner.close();
}

void OdimScanner::open(const std::string path)
{
	try
	{
		std::auto_ptr<OdimH5v20::OdimFactory> f (new OdimH5v20::OdimFactory());
		odimObj = f->open(path);
	}
	catch (std::exception& e)
	{
		throwEx(e);
	}
}

bool OdimScanner::next(Metadata& md)
{
	md.create();
	try
	{
		/* NOTA: per ora la next estrare un metadato unico per un intero file */
		getOdimObjectData(this->odimObj, md);
		return false;
	}
	catch (std::exception& e)
	{
		throwEx(e);
	}
}

void OdimScanner::close()
{
	try
	{
		delete odimObj;
		odimObj = NULL;
	}
	catch (std::exception& e)
	{
		throwEx(e);
	}
}

void OdimScanner::throwEx(std::exception& e)
{
	throw e;	//TODO rimappiamo l'eccezione?
}
void OdimScanner::getOdimObjectData(OdimH5v20::OdimObject* obj, Metadata& md)
{
	std::string object = obj->getObject();
	if (object == OdimH5v20::OBJECT_PVOL)
	{
		getPVOLData((OdimH5v20::PolarVolume*)obj, md);
	}
	else
	{
		std::ostringstream ss;
		ss << "Unsupported odimH5 object " << object << "!";
		throw std::logic_error(ss.str());
	}
}

void OdimScanner::getPVOLData(OdimH5v20::PolarVolume* pvol, Metadata& md)
{
	std::string		object		= pvol->getObject();
	std::string		prod		= OdimH5v20::PRODUCT_SCAN;
	OdimH5v20::SourceInfo	source		= pvol->getSource();
	time_t			dateTime	= pvol->getDateTime();
	std::string		task		= pvol->getTaskOrProdGen();
	double			lat		= pvol->getLatitude();
	double			lon		= pvol->getLongitude();
	double			alt		= pvol->getAltitude();
	std::vector<double>	eangles		= pvol->getElevationAngles();
	std::set<std::string>	quantities	= pvol->getStoredQuantities();
	std::vector<double>	prodpars;

	buildRefTime	(dateTime, md);
	buildObject	(object, prod, md);
	buildProdPar	(prodpars, md);
	buildSource	(source, md);
	buildTask	(task, md);
	buildOrigin	(lat, lon, alt, md);
	buildEangle	(eangles, md);
	buildQuantity	(quantities, md);
}

template <class T> void DEBUGVECTOR(const std::string& str, const std::vector<T>& values)
{
	std::ostringstream ss;
	ss << str << ": ";
	for (size_t i=0; i<values.size(); i++)
		ss << values[i] << " ";
	DEBUG(ss.str());
}

template <class TYPE> void DEBUGSET(const std::string& str, const std::set<TYPE> & values)
{
	typedef typename std::set<TYPE>::const_iterator iterator;
	std::ostringstream ss;
	ss << str << ": ";
	for (iterator i = values.begin(); i != values.end(); i++)
		ss << *i << " ";
	DEBUG(ss.str());
}

void OdimScanner::buildRefTime(time_t value, Metadata& md)
{
	DEBUG("Date/time: " << timeutils::absoluteToString(value));

	//TODO
}
void OdimScanner::buildObject(const std::string& object, const std::string& prod, Metadata& md)
{
	DEBUG("Object:    " << object);
	DEBUG("Prod:      " << prod);

	//TODO
}
void OdimScanner::buildProdPar(const std::vector<double>& values, Metadata& md)
{
	if (values.empty())
		return;

	DEBUGVECTOR<double>("ProdPar:   ", values);

	//TODO

}
void OdimScanner::buildSource(const OdimH5v20::SourceInfo& source, Metadata& md)
{
	DEBUG("Source:    " << source.toString());

	//TODO
}
void OdimScanner::buildTask(const std::string& task, Metadata& md)
{
	if (task.empty())
		return;

	DEBUG("Task:      " << task);

	//TODO
}
void OdimScanner::buildOrigin(double lat, double lon, double alt, Metadata& md)
{
	DEBUG("LAT:       " << lat);
	DEBUG("LON:       " << lon);
	DEBUG("ALT:       " << alt);

	//TODO
}
void OdimScanner::buildEangle(const std::vector<double>& values, Metadata& md)
{
	if (values.empty())
		return;

	DEBUGVECTOR<double>("EANGLE:    ", values);

	//TODO
}
void OdimScanner::buildQuantity(const std::set<std::string>& values, Metadata& md)
{
	if (values.empty())
		return;

	DEBUGSET<std::string>("EANGLE:    ", values);

	//TODO
}

/*===========================================================================*/

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Usage: " << argv[0] << " <odimh5file>" << std::endl;
		return -1;
	}

	try
	{
		std::cout << "Scansione..." << std::endl;

		Metadata md;
		OdimScanner::scanOdimH5(argv[1], md);

		std::cout << "Scansione eseguita!" << std::endl;
	}
	catch (std::exception& stde)
	{
		std::cerr << "Errore di esecuzione: " << stde.what() << std::endl;
	}
	catch (...)
	{
		std::cerr << "Errore di esecuzione sconosciuto" << std::endl;
	}

	return 0;
}

/*===========================================================================*/

















