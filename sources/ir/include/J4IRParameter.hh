// $Id$
#ifndef __J4IRPARAMETER__ 
#define __J4IRPARAMETER__ 
//=============================================
// Parameter of all detectors
//
//
//=============================================

#if 1
#include "J4Parameter.hh"
#endif

// Base parameters(IR)

#define _IRMATERIAL_            "Air" 
#define _IRVISATT_              FALSE 
#define _IRZMAX_                10000*cm
#define _IRZMID_                500*cm
#define _IRINNERSUPPORTTUBRAD_  40*cm
#define _IRTHETAMAX_            200*mrad
#define _IROUTERBEAMPIPERAD_    2.0*cm

#if 1

#define _IRBOXHALFX_		_EXPHALLHALFX_ - 1.0*cm
#define _IRBOXHALFY_		_EXPHALLHALFY_ - 1.0*cm

#else

#define _IRBOXHALFX_		40*m - 1.0*cm
#define _IRBOXHALFY_		40*m - 1.0*cm

#endif
 
#endif
