#include <vector>
#include <stdexcept>
#include <set>
#include <string>
#include <sstream>
#include <iostream>
#include <memory>
#include <radarlib/radar.hpp>

#include <assert.h>

#define TESTFILE TESTDIR"/PROD-ODIMH5V21.h5"


using namespace OdimH5v21;
using namespace Radar;

class ProductVisitor {
 public:
	void visitProduct(OdimH5v21::Product_2D* prod);
 protected:
	virtual void visit(OdimH5v21::Product_2D& prod) {}
	virtual void visit(OdimH5v21::Product_PPI& prod) {}
};

void ProductVisitor::visitProduct(OdimH5v21::Product_2D* prod) {
	const std::string& type = prod->getProduct();
	if (type == OdimH5v21::PRODUCT_PPI) {
		visit(dynamic_cast<OdimH5v21::Product_PPI&>(*prod));
	} 
	else if (type == OdimH5v21::PRODUCT_CAPPI) {
		visit(dynamic_cast<OdimH5v21::Product_CAPPI&>(*prod));
	} else {
		visit(*prod);
	}
}

class ObjectVisitor {
 public:
	void visitObject(OdimH5v21::OdimObject* obj);
 protected:
	virtual void visit(OdimH5v21::OdimObject& obj) {}
//	virtual void visit(OdimH5v21::HorizontalObject& obj) {}
	virtual void visit(OdimH5v21::ImageObject& obj) {}
	virtual void visit(OdimH5v21::CompObject& obj) {}
};

void ObjectVisitor::visitObject(OdimH5v21::OdimObject* obj) {
	const std::string& type = obj->getObject();
	if (type == OdimH5v21::OBJECT_IMAGE) {
		visit(dynamic_cast<OdimH5v21::ImageObject&>(*obj));
	} else if (type == OdimH5v21::OBJECT_COMP) {
		visit(dynamic_cast<OdimH5v21::CompObject&>(*obj));
	} else {
		visit(*obj);
	}
}

class Object2DSplitter {
 private:
	int id_max ;
	int id_hsp ;
	int id_vsp ;
	OdimFactory * factory; 
 public:
	OdimObject *root;
	Object2DSplitter(){
		factory		= new OdimH5v21::OdimFactory();
		id_max = -1;
		id_hsp = -1;
		id_vsp = -1;
		//root = obj;
        }

	~Object2DSplitter(){
	   delete factory;
	}

	std::string createProductFileName(std::string prodObject,double prodPar, std::string Quantity,time_t prodDateTime){
	  std::string result;
	  result=prodObject;
	  result="ODIMH5V21_"+result +"-"+ Radar::stringutils::toString(prodPar)+"_"+Quantity + "_";
	  std::string my_time(Radar::timeutils::absoluteToString(prodDateTime));   	// formato "YYYY-MM-DD hh:mm:ss"
	  my_time.erase(16,3);   							// strippo ":ss"
	  my_time.erase(13,1);								// strippo ":"
	  my_time.erase(10,1);								// strippo " "
	  my_time.erase( 7,1);								// strippo "-"
	  my_time.erase( 4,1);								// strippo "-"
 	  result=result+my_time+".h5";
	  return result;
	}
	std::string createProductFileName(std::string prodObject,OdimH5v21::VILHeights prodPar, std::string Quantity,time_t prodDateTime){
	  std::string result;
	  result=prodObject;
	  result="ODIMh5V21_"+result + Radar::stringutils::toString(prodPar.bottom)+"-"+ Radar::stringutils::toString(prodPar.top)+"_"+Quantity + "_";
	  std::string my_time(Radar::timeutils::absoluteToString(prodDateTime));   	// formato "YYYY-MM-DD hh:mm:ss"
	  my_time.erase(16,3);   							// strippo ":ss"
	  my_time.erase(13,1);								// strippo ":"
	  my_time.erase(10,1);								// strippo " "
	  my_time.erase( 7,1);								// strippo "-"
	  my_time.erase( 4,1);								// strippo "-"
 	  result=result+my_time+".h5";
	  return result;
	}
	std::string createProductFileName(std::string prodObject, std::string Quantity,time_t prodDateTime){
	  std::string result;
	  result=prodObject;
	  result="ODIMh5V21_"+result +Quantity + "_";
	  std::string my_time(Radar::timeutils::absoluteToString(prodDateTime));   	// formato "YYYY-MM-DD hh:mm:ss"
	  my_time.erase(16,3);   							// strippo ":ss"
	  my_time.erase(13,1);								// strippo ":"
	  my_time.erase(10,1);								// strippo " "
	  my_time.erase( 7,1);								// strippo "-"
	  my_time.erase( 4,1);								// strippo "-"
 	  result=result+my_time+".h5";
	  return result;
	}

	void extractProduct (OdimH5v21::OdimObject* obj,Product_2D* prod, Product_2D_Data* inputQ, const std::string & outname, bool add = false);

	void split(OdimH5v21::OdimObject* obj) {
		const std::string& objtype = obj->getObject();
		assert( objtype != OdimH5v21::OBJECT_IMAGE || objtype != OdimH5v21::OBJECT_COMP );

		OdimH5v21::HorizontalObject_2D& o = dynamic_cast<OdimH5v21::HorizontalObject_2D&>(*obj);
		assert(o.getProductCount() == 2) ;
		for (int nprod = 0; nprod < o.getProductCount(); nprod++) {
			OdimH5v21::Product_2D* prod = o.getProduct(nprod);
			// Se è uno dei 3 prodotti che vanno insieme, gestisci a parte
			// e.g. scrivi sul file $(nprod+1).h5
			const std::string& prod_type = prod->getProduct();
		       if (prod_type == OdimH5v21::PRODUCT_MAX ) {
  			  id_max = nprod; 	
			} else if (prod_type == OdimH5v21::PRODUCT_HSP ) {
  			  id_hsp = nprod; 	
			} else if (prod_type == OdimH5v21::PRODUCT_VSP ) {
  			  id_vsp = nprod; 	
			} else  {
			   std::set<std::string> quantities = prod->getStoredQuantities();
			   std::string filename;
			   for (int ndata = 0; ndata < prod->getQuantityDataCount(); ndata++) {
				Product_2D_Data*     inputQ	( prod->getQuantityData(ndata) );
				std::string quantity ; 
	
				if (inputQ->existWhat()){ 
					quantity = inputQ->getWhat()->getStr	(ATTRIBUTE_WHAT_QUANTITY);
				} else 
					quantity = prod->getWhat()->getStr	(ATTRIBUTE_WHAT_QUANTITY);
			        if ( prod->getProduct() ==  PRODUCT_COMP || prod->getProduct() == PRODUCT_RR || prod->getProduct() == PRODUCT_LBM_ARPA)
    				  filename = createProductFileName(prod->getProduct(),quantity,obj->getDateTime());
			        else if ( prod->getProduct() ==  PRODUCT_VIL )
    				  filename = createProductFileName(prod->getProduct(),prod->getProdParVIL(),quantity,obj->getDateTime());
    				else 
				  filename = createProductFileName(prod->getProduct(),prod->getProdPar(),quantity,obj->getDateTime());
			        extractProduct( obj, prod,  inputQ, filename);
				delete    inputQ	;
			   }
                        }  
			delete prod;
		}
		if (id_max >= 0 && (id_hsp >= 0 || id_vsp >=0) ) {
			   std::string filename;
			OdimH5v21::Product_2D* prod = o.getProduct(id_max);
			Product_2D_Data*     inputQ	( prod->getQuantityData(0) );
			std::string quantity ; 
	
			if (inputQ->existWhat()){ 
				quantity = inputQ->getWhat()->getStr	(ATTRIBUTE_WHAT_QUANTITY);
			} else 
				quantity = prod->getWhat()->getStr	(ATTRIBUTE_WHAT_QUANTITY);
    			filename = createProductFileName("HVMI",quantity,obj->getDateTime());
			extractProduct( obj, prod,  inputQ, filename);
			if(id_hsp >=0 ) {
				OdimH5v21::Product_2D* prod = o.getProduct(id_hsp);
				Product_2D_Data*     inputQ	( prod->getQuantityData(0) );
				extractProduct( obj, prod,  inputQ, filename,true);
			}	  
			if(id_vsp >=0 ) {
				OdimH5v21::Product_2D* prod = o.getProduct(id_hsp);
				Product_2D_Data*     inputQ	( prod->getQuantityData(0) );
				extractProduct( obj, prod,  inputQ, filename,true);
			}	  
		} else if (id_max >= 0 ) {
			   std::string filename;
			OdimH5v21::Product_2D* prod = o.getProduct(id_max);
			Product_2D_Data*     inputQ	( prod->getQuantityData(0) );
			std::string quantity ; 
	
			if (inputQ->existWhat()){ 
				quantity = inputQ->getWhat()->getStr	(ATTRIBUTE_WHAT_QUANTITY);
			} else 
				quantity = prod->getWhat()->getStr	(ATTRIBUTE_WHAT_QUANTITY);
    			filename = createProductFileName(prod->getProduct(),quantity,obj->getDateTime());
			extractProduct( obj, prod,  inputQ, filename);
		}
	}
	
#if 0
 protected:
	virtual void visit(OdimH5v21::OdimObject& obj) {
		throw std::runtime_error("Unsupported object " + obj.getObject());
	}
	virtual void visit(OdimH5v21::Product_2D& prod) {
		throw std::runtime_error("Unsupported product " + prod.getProduct());
	}
	virtual void visit(OdimH5v21::ImageObject& obj) {
		Product_2D* prod = NULL;
		for (int i = 0; i < obj.getProductCount(); ++i) {
			prod = obj.getProduct(i);
			visit(prod);
			delete prod;
		}
	}
	virtual void visit(OdimH5v21::CompObject& obj) {
		Product_2D* prod = NULL;
		for (int i = 0; i < obj.getProductCount(); ++i) {
			prod = obj.getProduct(i);
			const std::string& prod_type = prod->getProduct();
			if (prod_type == OdimH5v21::PRODUCT_MAX ) {
  			  prod_max = prod; 	
			} else if (prod_type == OdimH5v21::PRODUCT_HSP ) {
  			  prod_hsp = prod; 	
			} else if (prod_type == OdimH5v21::PRODUCT_VSP ) {
  			  prod_VSP = prod; 	
			} else if {
			  visit(prod);
			}
			delete prod;
		}
	}


	virtual void visit(OdimH5v21::Product_2D & prod) {

		for (int i = 0; i < obj.getQuantityDataCount(); ++i) {
			std::auto_ptr<OdimObject>   outputObject	;
			std::auto_ptr<OdimDataset>  outputDataset	;
			const std::string& type = root->getObject();
			std::string outname = createProductFileName(prod.getObject(),prod.getProdPar(),prod.getStoredQuantity().at(i),root.getDateTime());
	 	       if (type == OdimH5v21::OBJECT_IMAGE) {
			    outputObject= factory->createImageObject(outname);
	       		} else if (type == OdimH5v21::OBJECT_COMP) {
			    outputObject= factory->createCompObject(outname);
	       		}	

			if (root->existWhat())	outputObject->getWhat()->import( root->getWhat() );			
			if (root->existHow())   outputObject->getHow()->import( root->getHow() );
			if (root->existWhere()) outputObject->getWhere()->import( root->getWhere() );




			prod = obj.getProduct(i);
			const std::string& prod_type = prod.getObject();
			if (prod_type == OdimH5v21::PRODUCT_MAX ) {
  			  prod_max = prod; 	
			} else if (prod_type == OdimH5v21::PRODUCT_HSP ) {
  			  prod_hsp = prod; 	
			} else if (prod_type == OdimH5v21::PRODUCT_VSP ) {
  			  prod_VSP = prod; 	
			} else if {
			  visit(prod);
			}
			delete prod;
		}
	}
	virtual void visit(OdimH5v21::Product_PPI& prod) {
		// Scrivi su file xxxx.h5 il prodotto contenuto in prod
		// facendo eventualmente riferimento a root, e.g.:
		//   root->getHow()
		count++;
		// Uso count per generare un file univoco.
	}
#endif
};
void Object2DSplitter::extractProduct(OdimH5v21::OdimObject* obj,Product_2D* prod, Product_2D_Data* inputQ, const std::string & outname, bool add){
				HorizontalObject_2D*    outputObject	;
				Product_2D*  		outputDataset	;
				Product_2D_Data*	outputQ		;
				std::string quantity ; 
	
				if (inputQ->existWhat()){ 
					quantity = inputQ->getWhat()->getStr	(ATTRIBUTE_WHAT_QUANTITY);
				} else 
					quantity = prod->getWhat()->getStr	(ATTRIBUTE_WHAT_QUANTITY);
 				std::string my_name;
				my_name="/"+outname;
//    				outname = add ? filename : createProductFileName(prod->getProduct(),prod->getProdPar(),quantity,obj->getDateTime());
//			        filename=outname;
				const std::string& type = obj->getObject();
	 	       		if (type == OdimH5v21::OBJECT_IMAGE) {
			    		outputObject = (add) ? factory->openImageObject(outname) : factory->createImageObject(TESTDIR+my_name);
	       			} else if (type == OdimH5v21::OBJECT_COMP) {
			   	 	outputObject=  (add) ? factory->openCompObject(outname) :  factory->createCompObject(TESTDIR+my_name);
	       			}	
// import What, Where and How group at root level
				if (obj->existWhat()) outputObject->getWhat()->import( obj->getWhat() );
				if (obj->existHow())  outputObject->getHow()->import( obj->getHow() );
				if (obj->existWhere()) outputObject->getWhere()->import( obj->getWhere() );

// move the Where group at dataset level to root level
			        if (not add && prod->existWhere()) outputObject->getWhere()->import( prod->getWhere() );

// create a new dataset group to store the product in the output file
				outputDataset = outputObject->createProduct2D(prod->getProduct());
				if (prod->existWhat())	outputDataset->getWhat()->import( prod->getWhat() );			
				if (prod->existHow())   outputDataset->getHow()->import( prod->getHow() );
				if (prod->existWhere()) outputDataset->getWhere()->import( prod->getWhere() );
				
// create a new data group to store the product in the output file
				outputQ = outputDataset->createQuantityData(quantity);
				if (inputQ->existWhat()) outputQ->getWhat()->import(inputQ->getWhat() );			
				if (inputQ->existHow())  outputQ->getWhere()->import(inputQ->getWhere() );
				if (inputQ->existWhere())outputQ->getHow()->import(inputQ->getHow() );
// copy the data
				H5::AtomType	AtomType	= inputQ->getDataType();
				int		height	= inputQ->getDataHeight();
				int		width	= inputQ->getDataWidth();				
				std::vector<char> buff ( AtomType.getSize() * height * width );
				inputQ->readData(&(buff[0]));	
				outputQ->writeData(&(buff[0]), width, height, AtomType);

//  create quality group(s) inside the data group to store the quality matrix in the output file 
			        for (int nqdata = 0; nqdata < inputQ->getQualityDataCount(); nqdata++) {
				   OdimQuality * QualOutput (outputQ->createQualityData());
				   OdimQuality * QualInput  (inputQ->getQualityData(nqdata));

				   QualOutput->getWhat()->import (QualInput->getWhat() );			
				   QualOutput->getWhere()->import(QualInput->getWhere() );
				   QualOutput->getHow()->import  (QualInput->getHow() );

			    	   AtomType	= QualInput->getQualityType();
				   std::vector<char> qual( AtomType.getSize() * height * width );
				
				   QualInput->readQuality(&(qual[0]));	
				   QualOutput->writeQuality(&(qual[0]), width, height, AtomType);

				}
// delete created group
				delete    outputObject	;
				delete    outputDataset	;
				delete	  outputQ	;

	return ;
}

int main()
{
	Object2DSplitter splitter;
	OdimH5v21::OdimFactory factory;
  	OdimH5v21::OdimObject* object = factory.open(TESTFILE);
	try {
		splitter.split(object);
	} catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}
