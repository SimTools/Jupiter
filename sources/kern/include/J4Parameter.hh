// $Id$
#ifndef __J4PARAMETER__
#define __J4PARAMETER__
//=============================================
// Parameter of all detectors
//
//
//=============================================

//UserLimits

#define _USTEPMAX_ 70.0*m
#define _UTRAKMAX_ 70.0*m
#define _UTIMEMAX_ DBL_MAX
#define _UEKINMIN_ 0.05*MeV
#define _URABGMIN_ 0.

// for ExpHall

#define _EXPHALLMATERIAL_ "Air"

#if 0
#define _EXPHALLHALFX_  40*m
#define _EXPHALLHALFY_  40*m
#define _EXPHALLHALFZ_  4000*m
#else 
#define _EXPHALLHALFX_  5*m
#define _EXPHALLHALFY_  5*m
#define _EXPHALLHALFZ_  5*m
#endif
 
#endif

