// $Id$
#ifndef __J4IRSD0PARAMETER__ 
#define __J4IRSD0PARAMETER__ 
//=============================================
//
//
//=============================================

#include <cmath>

#define _SD0MARGIN_ 0.01*cm

// Shape of SD0

#define _SD0NSUS_ 12
#define _SD0NCOLLAR_ 6

// Master volume (Tube) for SD0
#define _SD0INRADIUS_  0.52*cm
#define _SD0THICK_     15.0*cm
#define _SD0ZLEN_      0.30480*2*m
#define _SD0MAT_    "vacuum"

// Position of SD0
#define _SD0ZPOS_      795.528*cm



#define _SD0PHI_SUS_ 30.*degree
// SUS Trap   : Full Length
// X1 Longer side ,  X2 Shorter side
#define _SD0Y1_SUS_  5.*cm
#define _SD0X1_SUS_  (_SD0INRADIUS_+_SD0THICK_)*std::sin(_SD0PHI_SUS_/2.)*2.
#define _SD0X2_SUS_  ((_SD0INRADIUS_+_SD0THICK_-_SD0Y1_SUS_/std::cos(_SD0PHI_SUS_/2.))*std::sin(_SD0PHI_SUS_/2.)*2.)

#define _SD0MAT_SUS_ "Iron"

// Collars
#define _SD0HBOX_IRON_ _SD0X2_SUS_
#define _SD0VBOX_IRON_ _SD0Y1_SUS_
#define _SD0MAT_COLLAR_ "Copper"

#endif

