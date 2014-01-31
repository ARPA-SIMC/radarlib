#include <iostream>
#include <radarlib/radar.hpp>
#include <stdio.h>

#include <assert.h>
#define NUMRAYS 100

int main()
{
	OdimH5v21::OdimFactory factory;

	OdimH5v21::PolarVolume *volume = factory.openPolarVolume(TESTDIR"/PVOL-ODIMH5V21.h5");

	OdimH5v21::PolarScan *Scan = volume->getScan(0);

	std::vector<OdimH5v21::AZAngles> azangles, azangles_vol, azangles_ccw;
	for (int i=0; i<NUMRAYS; i++){
	 	azangles.push_back(OdimH5v21::AZAngles(fmod(360./(NUMRAYS)*i,360),fmod(360./(NUMRAYS)*(i+1),360)));
		azangles_ccw.push_back(OdimH5v21::AZAngles(azangles[i].stop,azangles[i].start));
	}
	azangles_vol= Scan->getAzimuthAngles();
	for (int i=0; i<NUMRAYS; i++){
	   assert (azangles[i].start ==azangles_vol[i].start);
	   assert (azangles[i].stop ==azangles_vol[i].stop);
	   assert (azangles[i].averagedAngle() == azangles_ccw[i].averagedAngle(-1));
	//   printf("start, stop, ave :  %6.1f %6.1f %6.1f %6.1f\n",azangles[i].start,azangles[i].stop,azangles[i].averagedAngle(),azangles[i].averagedAngle(-1));
	}


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
