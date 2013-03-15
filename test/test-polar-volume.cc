#include <iostream>
#include <radarlib/radar.hpp>

#include <assert.h>

int main()
{
	OdimH5v20::OdimFactory factory;

	OdimH5v20::PolarVolume *volume = factory.openPolarVolume(TESTDIR"/PVOL.h5");

	assert(volume->getObject() == OdimH5v20::OBJECT_PVOL);
	int NumScans=volume->getScanCount();
	assert ( NumScans  == 10) ;
	
	for (int i=NumScans-1 ; i >2; i--){
	  try{
	    volume->removeScan(i);
	  }
	  catch(...){
	    assert(false) ;
	  }	
	  assert ( volume->getScanCount() == i) ;
	}

	return 0;
}
