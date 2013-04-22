/*===========================================================================*/
/*
/* Questo programma crea un prodotto utilizzando le classi specifiche di OdimH5  e verifica rileggendo i campi scritti.
/*
/*===========================================================================*/

#include <iostream>
#include <assert.h>

#include <radarlib/radar.hpp>
using namespace OdimH5v21;


#define TESTFILE TESTDIR"/PROD-ODIMH5V21.h5"

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
	dataset->setAngles(angles);    //non esiste in odimh5v21
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
//	datasetPPI->setAngles(angles, 2);    non esiste in odimh5v21
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

// Add a new product in the file
//
	Product_CAPPI * datasetCAPPI =  image->createProductCAPPI();
	datasetCAPPI->setProdPar(500.);
	datasetCAPPI->setArotation(arotations);
	datasetCAPPI->setNodes(nodes);
	
	/* where */

	datasetCAPPI->setLL_Latitude(41.0);
	datasetCAPPI->setLL_Longitude(10.0);
	datasetCAPPI->setLR_Latitude(41.0); 
	datasetCAPPI->setLR_Longitude(15.0);
	datasetCAPPI->setUL_Latitude(45.0); 
	datasetCAPPI->setUL_Longitude(10.0);
	datasetCAPPI->setUR_Latitude(45.0);
	datasetCAPPI->setUR_Longitude(15.0);

	datasetCAPPI->setXSize(256);
	datasetCAPPI->setYSize(256);
	datasetCAPPI->setXScale(1000.);
	datasetCAPPI->setYScale(1000.);
	datasetCAPPI->setProjectionArguments("+proj=gnom +lat_0=44.7914N +lon_0=10.4992E +units=m +ellps=sphere");

	Product_2D_Data* dataCAPPI = datasetCAPPI->createQuantityData(PRODUCT_QUANTITY_DBZH);
	dataCAPPI->setNodata(missing);
	dataCAPPI->setUndetect(0.);
	dataCAPPI->setOffset(0);
	dataCAPPI->setGain(1./1000.);

	for (int i=10; i<246; i++)
		for (int j=10; j<246; j++)
			matrix.elem(i,j) = (65 + ((i * j) % 65)*1000.);

	dataCAPPI->writeData(matrix);
	delete dataCAPPI;
	delete datasetCAPPI;

// Add a new product in the file
//
	Product_PCAPPI * datasetPCAPPI =  image->createProductPCAPPI();
	datasetPCAPPI->setProdPar(500.);
	datasetPCAPPI->setArotation(arotations);
	datasetPCAPPI->setNodes(nodes);
	
	/* where */

	datasetPCAPPI->setLL_Latitude(41.0);
	datasetPCAPPI->setLL_Longitude(10.0);
	datasetPCAPPI->setLR_Latitude(41.0); 
	datasetPCAPPI->setLR_Longitude(15.0);
	datasetPCAPPI->setUL_Latitude(45.0); 
	datasetPCAPPI->setUL_Longitude(10.0);
	datasetPCAPPI->setUR_Latitude(45.0);
	datasetPCAPPI->setUR_Longitude(15.0);

	datasetPCAPPI->setXSize(256);
	datasetPCAPPI->setYSize(256);
	datasetPCAPPI->setXScale(1000.);
	datasetPCAPPI->setYScale(1000.);
	datasetPCAPPI->setProjectionArguments("+proj=gnom +lat_0=44.7914N +lon_0=10.4992E +units=m +ellps=sphere");

	Product_2D_Data* dataPCAPPI = datasetPCAPPI->createQuantityData(PRODUCT_QUANTITY_DBZH);
	dataPCAPPI->setNodata(missing);
	dataPCAPPI->setUndetect(0.);
	dataPCAPPI->setOffset(0);
	dataPCAPPI->setGain(1./1000.);

	for (int i=10; i<246; i++)
		for (int j=10; j<246; j++)
			matrix.elem(i,j) = (65 + ((i * j) % 65)*1000.);

	dataPCAPPI->writeData(matrix);
	delete dataPCAPPI;
	delete datasetPCAPPI;
// Add a new product in the file
//
	Product_MAX * datasetMAX =  image->createProductMAX();
	datasetMAX->setArotation(arotations);
	datasetMAX->setNodes(nodes);
	
	/* where */

	datasetMAX->setLL_Latitude(41.0);
	datasetMAX->setLL_Longitude(10.0);
	datasetMAX->setLR_Latitude(41.0); 
	datasetMAX->setLR_Longitude(15.0);
	datasetMAX->setUL_Latitude(45.0); 
	datasetMAX->setUL_Longitude(10.0);
	datasetMAX->setUR_Latitude(45.0);
	datasetMAX->setUR_Longitude(15.0);

	datasetMAX->setXSize(256);
	datasetMAX->setYSize(256);
	datasetMAX->setXScale(1000.);
	datasetMAX->setYScale(1000.);
	datasetMAX->setProjectionArguments("+proj=gnom +lat_0=44.7914N +lon_0=10.4992E +units=m +ellps=sphere");

	Product_2D_Data* dataMAX = datasetMAX->createQuantityData(PRODUCT_QUANTITY_DBZH);
	dataMAX->setNodata(missing);
	dataMAX->setUndetect(0.);
	dataMAX->setOffset(0);
	dataMAX->setGain(1./1000.);

	for (int i=10; i<246; i++)
		for (int j=10; j<246; j++)
			matrix.elem(i,j) = (65 + ((i * j) % 65)*1000.);

	dataMAX->writeData(matrix);
	delete dataMAX;
	delete datasetMAX;

// Add a new product in the file
//
	Product_HSP * datasetHSP =  image->createProductHSP();
	
	/* where */

	datasetHSP->setStartLatitude(41.0);
	datasetHSP->setStartLongitude(10.0);
	datasetHSP->setStopLatitude(45.0);
	datasetHSP->setStopLongitude(15.0);

	datasetHSP->setXSize(256);
	datasetHSP->setYSize(256);
	datasetHSP->setXScale(1000.);
	datasetHSP->setYScale(1000.);
	datasetHSP->setMinHeight(1000.);
	datasetHSP->setMaxHeight(10000.);

	Product_2D_Data* dataHSP = datasetHSP->createQuantityData(PRODUCT_QUANTITY_DBZH);
	dataHSP->setNodata(missing);
	dataHSP->setUndetect(0.);
	dataHSP->setOffset(0);
	dataHSP->setGain(1./1000.);

	for (int i=10; i<246; i++)
		for (int j=10; j<246; j++)
			matrix.elem(i,j) = (65 + ((i * j) % 65)*1000.);

	dataHSP->writeData(matrix);
	delete dataHSP;
	delete datasetHSP;

// Add a new product in the file
//
	Product_VSP * datasetVSP =  image->createProductVSP();
	
	/* where */

	datasetVSP->setStartLatitude(41.0);
	datasetVSP->setStartLongitude(10.0);
	datasetVSP->setStopLatitude(45.0);
	datasetVSP->setStopLongitude(15.0);

	datasetVSP->setXSize(256);
	datasetVSP->setYSize(256);
	datasetVSP->setXScale(1000.);
	datasetVSP->setYScale(1000.);
	datasetVSP->setMinHeight(1000.);
	datasetVSP->setMaxHeight(10000.);

	Product_2D_Data* dataVSP = datasetVSP->createQuantityData(PRODUCT_QUANTITY_DBZH);
	dataVSP->setNodata(missing);
	dataVSP->setUndetect(0.);
	dataVSP->setOffset(0);
	dataVSP->setGain(1./1000.);

	for (int i=10; i<246; i++)
		for (int j=10; j<246; j++)
			matrix.elem(i,j) = (65 + ((i * j) % 65)*1000.);

	dataVSP->writeData(matrix);
	delete dataVSP;
	delete datasetVSP;

// Add a new product in the file
//
	Product_RR * datasetRR =  image->createProductRR();
	datasetRR->setArotation(arotations);
	datasetRR->setNodes(nodes);
	
	/* where */

	datasetRR->setLL_Latitude(41.0);
	datasetRR->setLL_Longitude(10.0);
	datasetRR->setLR_Latitude(41.0); 
	datasetRR->setLR_Longitude(15.0);
	datasetRR->setUL_Latitude(45.0); 
	datasetRR->setUL_Longitude(10.0);
	datasetRR->setUR_Latitude(45.0);
	datasetRR->setUR_Longitude(15.0);

	datasetRR->setXSize(256);
	datasetRR->setYSize(256);
	datasetRR->setXScale(1000.);
	datasetRR->setYScale(1000.);
	datasetRR->setProjectionArguments("+proj=gnom +lat_0=44.7914N +lon_0=10.4992E +units=m +ellps=sphere");

	Product_2D_Data* dataRR = datasetRR->createQuantityData(PRODUCT_QUANTITY_ACRR);
	dataRR->setNodata(missing);
	dataRR->setUndetect(0.);
	dataRR->setOffset(0);
	dataRR->setGain(1./1000.);

	for (int i=10; i<246; i++)
		for (int j=10; j<246; j++)
			matrix.elem(i,j) = (65 + ((i * j) % 65)*1000.);

	dataRR->writeData(matrix);
	delete dataRR;
	delete datasetRR;

// Add a new product in the file
//
	Product_VIL * datasetVIL =  image->createProductVIL();
	datasetVIL->setProdPar(VILHeights(10.,100.));
	datasetVIL->setArotation(arotations);
	datasetVIL->setNodes(nodes);
	
	/* where */

	datasetVIL->setLL_Latitude(41.0);
	datasetVIL->setLL_Longitude(10.0);
	datasetVIL->setLR_Latitude(41.0); 
	datasetVIL->setLR_Longitude(15.0);
	datasetVIL->setUL_Latitude(45.0); 
	datasetVIL->setUL_Longitude(10.0);
	datasetVIL->setUR_Latitude(45.0);
	datasetVIL->setUR_Longitude(15.0);

	datasetVIL->setXSize(256);
	datasetVIL->setYSize(256);
	datasetVIL->setXScale(1000.);
	datasetVIL->setYScale(1000.);
	datasetVIL->setProjectionArguments("+proj=gnom +lat_0=44.7914N +lon_0=10.4992E +units=m +ellps=sphere");

	Product_2D_Data* dataVIL = datasetVIL->createQuantityData(PRODUCT_QUANTITY_DBZH);
	dataVIL->setNodata(missing);
	dataVIL->setUndetect(0.);
	dataVIL->setOffset(0);
	dataVIL->setGain(1./1000.);

	for (int i=10; i<246; i++)
		for (int j=10; j<246; j++)
			matrix.elem(i,j) = (65 + ((i * j) % 65)*1000.);

	dataVIL->writeData(matrix);
	delete dataVIL;
	delete datasetVIL;







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
//	assert(image->getProductCount() == 2);
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
