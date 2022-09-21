#include <assert.h>

#include <memory>

#include <radarlib/odimh5v20_factory.hpp>
#include <radarlib/odimh5v20_utils.hpp>

class MyProduct2DVisitor : public OdimH5v20::utils::OdimProduct2DVisitor {
 public:
	bool foundProductPPI;
	bool foundProductETOP;

	MyProduct2DVisitor() {
		foundProductPPI = false;
		foundProductETOP = false;
	}

	virtual void visit(OdimH5v20::Product_PPI& prod) {
		foundProductPPI = true;
	}
	virtual void visit(OdimH5v20::Product_ETOP& prod) {
		foundProductETOP = true;
	}
};

class MyObjectVisitor : public OdimH5v20::utils::OdimObjectVisitor {
 public:
	bool foundPolarVolume;
	bool foundImageObject;

	MyProduct2DVisitor pvisitor;

	MyObjectVisitor() {
		foundPolarVolume = false;
		foundImageObject = false;
	}

	virtual void visit(OdimH5v20::PolarVolume& obj) {
		foundPolarVolume = true;
	}
	virtual void visit(OdimH5v20::ImageObject& obj) {
		foundImageObject = true;

		for (int i = 0; i < obj.getProductCount(); ++i) {
			std::unique_ptr<OdimH5v20::Product_2D> prod(obj.getProduct(i));
			pvisitor.visitProduct2D(*prod);
		}
	}
};

void testVisitPolarVolume() {
	MyObjectVisitor visitor;
	OdimH5v20::OdimFactory f;
	OdimH5v20::OdimObject* obj = f.open(TESTDIR"/PVOL.h5");
	visitor.visitObject(*obj);
	assert(visitor.foundPolarVolume);
	delete obj;
}

void testVisitImageObject() {
	MyObjectVisitor visitor;
	OdimH5v20::OdimFactory f;
	OdimH5v20::OdimObject* obj = f.open(TESTDIR"/PROD.h5");
	visitor.visitObject(*obj);
	assert(visitor.foundImageObject);
	assert(visitor.pvisitor.foundProductPPI);
	assert(visitor.pvisitor.foundProductETOP);
	delete obj;
}

int main()
{

	testVisitPolarVolume();
	testVisitImageObject();
	return 0;
}
