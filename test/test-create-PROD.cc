/*===========================================================================*/
/*
/* Questo programma crea un prodotto utilizzando le classi specifiche di OdimH5  e verifica rileggendo i campi scritti.
/*
/*===========================================================================*/


#include <iostream>
#include <assert.h>

#include <radarlib/radar.hpp>
using namespace OdimH5v20;


#define TESTFILE TESTDIR"/PROD.h5"

void setUp()
{
	/* assicuriamoci che la installata della libreria sia quella giusta */
	Radar::RadarLibrary::checkVersion();

	OdimFactory*		factory = NULL;
	ImageObject*		image	= NULL;

	std::set<std::string>	quantities;

	OdimH5v20::Specification::getStandardQuantities(quantities);

	/* creazione di una factory */
	factory		= new OdimFactory();

	/* creazione di un oggetto generico */
	image		= factory->createImageObject(TESTFILE);

	/* what */

	image->setDateTime( Radar::timeutils::mktime(2000,1,2,3,4,5));
	assert (image->getDateTime() == Radar::timeutils::mktime(2000,1,2,3,4,5));

	SourceInfo source, source_read;
	source.setWMO("wmo");
	source.setOperaRadarSite("rad");
	source.setOriginatingCenter(1);
	source.setPlace("plc");
	source.setCountry(2);
	source.setComment("cmt");
	image->setSource(source);

	source_read=image->getSource();
	assert(source_read.WMO=="wmo");
	assert(source_read.OperaRadarSite=="rad");
	assert(source_read.OriginatingCenter==1);
	assert(source_read.Place=="plc");
	assert(source_read.Country==2);
	assert(source_read.Comment=="cmt");
	
		/* how */

	image->setTaskOrProdGen("prova");
	image->setStartEpochs(Radar::timeutils::mktime(2000,1,2,3,4,5));
	image->setEndEpochs(Radar::timeutils::mktime(2000,1,2,3,4,5));
	image->setSystem("ARPA-SIMC");

	assert(image->getTaskOrProdGen()=="prova");
	assert(image->getStartEpochs()==Radar::timeutils::mktime(2000,1,2,3,4,5));
	assert(image->getEndEpochs() == Radar::timeutils::mktime(2000,1,2,3,4,5));
	assert(image->getSystem() == "ARPA-SIMC");

	/* A questo punto creiamo il prodotto ETOP all'interno dell'oggetto IMAGE */
	unsigned short missing;
	missing = 65535;

	Product_ETOP * dataset =  image->createProductETOP();
	dataset->setProdPar(10.);
	assert (dataset->getProduct()==PRODUCT_ETOP);
	assert(dataset->getProdPar() ==10.);

	Product_2D_Data* data = dataset->createQuantityData(PRODUCT_QUANTITY_HGHT);
	data->setNodata(missing);
	data->setUndetect(0.);
	data->setOffset(0);
	data->setGain(1./1000.);

	assert(data->getNodata()==missing);
	assert(data->getUndetect()==0.);
	assert(data->getOffset()==0);
	assert(data->getGain()==1./1000.);

/* where */
	dataset->setLL_Latitude(40.0);
	dataset->setLL_Longitude(10.0);
	dataset->setLR_Latitude(40.0); 
	dataset->setLR_Longitude(15.0);
	dataset->setUL_Latitude(45.0); 
	dataset->setUL_Longitude(10.0);
	dataset->setUR_Latitude(45.0);
	dataset->setUR_Longitude(15.0);

	dataset->setXSize(256);
	dataset->setYSize(256);
	dataset->setXScale(1000.);
	dataset->setYScale(1000.);
	dataset->setProjectionArguments("+proj=gnom +lat_0=44.7914N +lon_0=10.4992E +units=m +ellps=sphere");

	assert(dataset->getLL_Latitude()==40.0);
	assert(dataset->getLL_Longitude()==10.0);
	assert(dataset->getLR_Latitude()==40.0); 
	assert(dataset->getLR_Longitude()==15.0);
	assert(dataset->getUL_Latitude()==45.0); 
	assert(dataset->getUL_Longitude()==10.0);
	assert(dataset->getUR_Latitude()==45.0);
	assert(dataset->getUR_Longitude()==15.0);

	assert(dataset->getXSize()==256);
	assert(dataset->getYSize()==256);
	assert(dataset->getXScale()==1000.);
	assert(dataset->getYScale()==1000.);
	assert(dataset->getProjectionArguments()=="+proj=gnom +lat_0=44.7914N +lon_0=10.4992E +units=m +ellps=sphere");

	std::vector<Angles> angles;
	std::vector<Arotation> arotations;
	std::vector<Nodes> nodes;

	for (int i=0; i<10; i++){
	  angles.push_back(Angles(i*0.5));
	  arotations.push_back(Arotation(10+i));
	  nodes.push_back(Nodes("'aaa'"));
        }
	dataset->setAngles(angles, 2);
	dataset->setArotation(arotations);
	dataset->setNodes(nodes);

	angles.clear();
	angles=dataset->getAngles();
	arotations=dataset->getArotation();
	nodes=dataset->getNodes();

	assert(angles[0].value == 0.);
	assert(arotations[0].value == 10.);
	assert(nodes[0].get() == "'aaa'");

	DataMatrix<unsigned short> matrix(256,256,missing);
	DataMatrix<unsigned short> matrix_read(256,256,missing);

	for (int i=10; i<246; i++)
		for (int j=10; j<246; j++)
			matrix.elem(i,j) = (65 + ((i * j) % 65)*1000.);

	data->writeData(matrix);
	data->readData(&(matrix_read.elem(0,0)));
	for (int i=0; i<255; i++)
		for (int j=0; j<255; j++)
			assert(matrix.elem(i,j) == matrix_read.elem(i,j));

	delete data;
	delete dataset;

// Add a new product in the file
//
	Product_PPI * datasetPPI =  image->createProductPPI();
	datasetPPI->setProdPar(0.5);
	datasetPPI->setAngles(angles, 2);
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

	Product_2D_Data* dataPPI = datasetPPI->createQuantityData(PRODUCT_QUANTITY_DBZH);
	dataPPI->setNodata(missing);
	dataPPI->setUndetect(0.);
	dataPPI->setOffset(0);
	dataPPI->setGain(1./1000.);


	for (int i=10; i<246; i++)
		for (int j=10; j<246; j++)
			matrix.elem(i,j) = (65 + ((i * j) % 65)*1000.);

	dataPPI->writeData(matrix);
	delete dataPPI;

//  add an additional data group inside the PPI product
	dataPPI = datasetPPI->createQuantityData(PRODUCT_QUANTITY_TH);
	dataPPI->setNodata(missing);
	dataPPI->setUndetect(0.);
	dataPPI->setOffset(0);
	dataPPI->setGain(1./1000.);
	for (int i=10; i<246; i++)
		for (int j=10; j<246; j++)
			matrix.elem(i,j) = (65 + ((i * j) % 65)*1000.);

	dataPPI->writeData(matrix);
//  add a quality data group
//
	OdimQuality * QualityPPI= dataPPI->createQualityData();
	assert (dataPPI->getQualityDataCount() == 1);

	QualityPPI->getWhat()->set		(ATTRIBUTE_WHAT_GAIN, 1.);
	QualityPPI->getWhat()->set		(ATTRIBUTE_WHAT_OFFSET, 0.);
	QualityPPI->getHow()->set		(ATTRIBUTE_HOW_TASK,"Quality field");

	assert(QualityPPI->getWhat()->getDouble(ATTRIBUTE_WHAT_GAIN) == 1.);
	assert(QualityPPI->getWhat()->getDouble(ATTRIBUTE_WHAT_OFFSET) == 0.);
	assert(QualityPPI->getHow()->getStr(ATTRIBUTE_HOW_TASK) =="Quality field");
	
	QualityPPI->writeQuality(matrix);
	QualityPPI->readQuality(&(matrix_read.elem(0,0)));
	for (int i=0; i<255; i++)
		for (int j=0; j<255; j++)
			assert(matrix.elem(i,j) == matrix_read.elem(i,j));

	delete QualityPPI;
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

	OdimH5v20::Specification::getStandardQuantities(quantities);

	/* creazione di una factory */
	factory		= new OdimFactory();

	/* creazione di un oggetto generico */
	image		= factory->openImageObject(TESTFILE);

	assert(image != NULL);
	assert(image->getProductCount() == 2);
	Product_2D* product = image->getProduct(0);
	product->getWhat();
	assert(product != NULL);
	Product_ETOP* etop = dynamic_cast<Product_ETOP*>(product);
	assert(etop != NULL);	
	etop->getHow();
}


int main (){

	setUp();
	test_ETOP();

	return 0;

}
