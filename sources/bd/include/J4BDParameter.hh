// $Id$
#ifndef __J4BDPARAMETER__ 
#define __J4BDPARAMETER__ 
//=============================================
// Parameter of Beam Delibery Area
//
//=============================================

#if 1
#include "J4IRParameter.hh"
#endif

#define _BDMATERIAL_	"Air" 
#define _BDVISATT_      FALSE	

#if 1

#define _BDOUTERHALFX_	_EXPHALLHALFX_
#define _BDOUTERHALFY_	_EXPHALLHALFY_
#define _BDOUTERHALFZ_	_EXPHALLHALFZ_
 
#define _BDINNERHALFX_	_IRBOXHALFX_
#define _BDINNERHALFY_  _IRBOXHALFX_	
#define _BDINNERHALFZ_	_IRZMAX_

#else

#define _BDOUTERHALFX_	40*m
#define _BDOUTERHALFY_	40*m
#define _BDOUTERHALFZ_	4000*m
 
#define _BDINNERHALFX_	_BDOUTERHALFX_ - 1.0*cm
#define _BDINNERHALFY_  _BDOUTERHALFY_ - 1.0*cm	
#define _BDINNERHALFZ_	10000*cm

#endif

#endif
