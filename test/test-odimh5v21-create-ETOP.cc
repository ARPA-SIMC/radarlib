/*===========================================================================*/
/*
/* Questo programma crea un prodotto ti tipo ETOP utilizzando le classi specifiche di OdimH5
/*
/*===========================================================================*/


#include <iostream>
#include <assert.h>

#include <radarlib/radar.hpp>
using namespace OdimH5v21;


#define TESTFILE TESTDIR"/ETOP-ODIMh5V21.h5"

void setUp()
{
	/* assicuriamoci che la installata della libreria sia quella giusta */
	Radar::RadarLibrary::checkVersion();

	OdimFactory*		factory = NULL;
	ImageObject*		image	= NULL;

	std::set<std::string>	quantities;

	OdimH5v21::Specification::getStandardQuantities(quantities);

	/* creazione di una factory */
	factory		= new OdimFactory();

	/* creazione di un oggetto generico */
	image		= factory->createImageObject(TESTFILE);

	/* what */

	image->setDateTime( Radar::timeutils::mktime(2000,1,2,3,4,5));
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

	image->setXSize(256);
	image->setYSize(256);
	image->setXScale(1000.);
	image->setYScale(1000.);
	image->setProjectionArguments("+proj=gnom +lat_0=44.7914N +lon_0=10.4992E +units=m +ellps=sphere");

	/* how */

	image->setTaskOrProdGen("prova");
	image->setStartEpochs(Radar::timeutils::mktime(2000,1,2,3,4,5));
	image->setEndEpochs(Radar::timeutils::mktime(2000,1,2,3,4,5));
	image->setSystem("ARPA-SIMC");


	/* A questo punto creiamo il prodotto ETOP all'interno dell'oggetto IMAGE */
	unsigned short missing;
	missing = 65535;

	Product_ETOP * dataset =  image->createProductETOP();
	dataset->setProdPar(10.);
	Product_2D_Data* data = dataset->createQuantityData(PRODUCT_QUANTITY_HGHT);
	data->setNodata(missing);
	data->setUndetect(0.);
	data->setOffset(0);
	data->setGain(1./1000.);

	std::vector<Angles> angles;
	std::vector<Arotation> arotations;
	std::vector<Nodes> nodes;

	for (int i=0; i<10; i++){
	  angles.push_back(Angles(i*0.5));
	  arotations.push_back(Arotation(10+i));
	  nodes.push_back(Nodes("'aaa'"));
        }
	dataset->setAngles(angles);  
	dataset->setArotation(arotations);
	dataset->setNodes(nodes);
	

	DataMatrix<unsigned short> matrix(256,256,missing);

	for (int i=10; i<246; i++)
		for (int j=10; j<246; j++)
			matrix.elem(i,j) = (65 + ((i * j) % 65)*1000.);

	data->writeData(matrix);

	delete data;
	delete dataset;

	Product_PPI * datasetPPI =  image->createProductPPI();
	datasetPPI->setProdPar(1.);
	Product_2D_Data* dataPPI = datasetPPI->createQuantityData(PRODUCT_QUANTITY_DBZH);
	dataPPI->setNodata(missing);
	dataPPI->setUndetect(0.);
	dataPPI->setOffset(0);
	dataPPI->setGain(1./1000.);

//	dataset->setAngles(angles, 2);  questo attributo non esiste in odimh5v21
	datasetPPI->setArotation(arotations);
	datasetPPI->setNodes(nodes);
	
	/* where */

	datasetPPI->setLL_Latitude(41.0);
	datasetPPI->setLL_Longitude(10.0);
	datasetPPI->setLR_Latitude(41.0); 
	datasetPPI->setLR_Longitude(15.0);
	datasetPPI->setUL_Latitude(45.0); 
	datasetPPI->setUL_Longitude(10.0);
	datasetPPI->setUR_Latitude(45.0);
	datasetPPI->setUR_Longitude(15.0);

	datasetPPI->setXSize(256);
	datasetPPI->setYSize(256);
	datasetPPI->setXScale(1000.);
	datasetPPI->setYScale(1000.);
	datasetPPI->setProjectionArguments("+proj=gnom +lat_0=44.7914N +lon_0=10.4992E +units=m +ellps=sphere");


	for (int i=10; i<246; i++)
		for (int j=10; j<246; j++)
			matrix.elem(i,j) = (65 + ((i * j) % 65)*1000.);

	dataPPI->writeData(matrix);
	delete dataPPI;

	dataPPI = datasetPPI->createQuantityData(PRODUCT_QUANTITY_TH);
	dataPPI->setNodata(missing);
	dataPPI->setUndetect(0.);
	dataPPI->setOffset(0);
	dataPPI->setGain(1./1000.);
	for (int i=10; i<246; i++)
		for (int j=10; j<246; j++)
			matrix.elem(i,j) = (65 + ((i * j) % 65)*1000.);

	dataPPI->writeData(matrix);

	delete dataPPI;
	delete datasetPPI;
	delete image;
	delete factory;
}

void test_ETOP()
{
	/* assicuriamoci che la installata della libreria sia quella giusta */
	Radar::RadarLibrary::checkVersion();

	OdimFactory*		factory = NULL;
	ImageObject*		image	= NULL;
	OdimData* data = NULL;
	OdimDataset* dataset = NULL;

	std::set<std::string>	quantities;

	OdimH5v21::Specification::getStandardQuantities(quantities);

	/* creazione di una factory */
	factory		= new OdimFactory();

	/* creazione di un oggetto generico */
	image		= factory->openImageObject(TESTFILE);

	assert(image != NULL);
	assert(image->getLL_Longitude() == 10.0);
	assert(image->getLR_Longitude() == 15.0);
	assert(image->getUL_Longitude() == 10.0);
	assert(image->getUR_Longitude() == 15.0);
	assert(image->getTaskOrProdGen() == "prova");

	assert(image->getProductCount() == 2);
	Product_2D* product = image->getProduct(0);
	product->getWhat();
	assert(product != NULL);
	Product_ETOP* etop = dynamic_cast<Product_ETOP*>(product);
	assert(etop != NULL);	
	etop->getHow();
	//assert(etop->getNodes().size() == 10);
	//std::cout << Nodes::toString(etop->getNodes()) << std::endl;
	//assert(etop->getNodes().at(0).get() == "'aaa'");

	//delete data;
	//delete dataset;
	//delete image;
	//delete factory;
}


int main (){

	setUp();
	test_ETOP();

	return 0;

}
