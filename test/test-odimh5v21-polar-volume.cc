#include <iostream>
#include <radarlib/radar.hpp>

#include <assert.h>

int main()
{
	OdimH5v21::OdimFactory factory;

	OdimH5v21::PolarVolume *volume = factory.openPolarVolume(TESTDIR"/PVOL-ODIMH5V21.h5");

	assert(volume->getObject() == OdimH5v21::OBJECT_PVOL);
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
