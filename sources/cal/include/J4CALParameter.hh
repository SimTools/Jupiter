// $Id$
//=============================================
// Parameter of CAL
//
//
//=============================================


// Materials
#define _CALMATERIAL_            "Lead"

#define _CALIR_		160.*cm
#define _CALOR_		290.*cm
#define _CALLEN_	320.*cm
#define _CALFRONTZ_	190.*cm
#define _CALFRONTZIR_	 45.*cm
#define _CALSPHI_         0.*deg
#define _CALDPHI_       360.*deg
#define _CALVISATT_  	TRUE

#define _CALBARRELIR_		_CALIR_
#define _CALBARRELOR_		_CALOR_
#define _CALBARRELLEN_		_CALFRONTZ_
#define _CALBARRELSPHI_      	0.*deg
#define _CALBARRELDPHI_    	360.*deg
#define _CALBARRELVISATT_	TRUE

#define _CALENDCAPNUM_		2
#define _CALENDCAPIR_	  	_CALFRONTZIR_
#define _CALENDCAPOR_	  	_CALOR_
#define _CALENDCAPLEN_     	(_CALLEN_ - _CALFRONTZ_)/2.
#define _CALENDCAPFRONTZ_ 	_CALFRONTZ_
#define _CALENDCAPSPHI_    	 0.*deg
#define _CALENDCAPDPHI_   	360.*deg
#define _CALENDCAPVISATT_ 	TRUE

