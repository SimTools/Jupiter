// $Id$
#ifndef __J4IRQC1PARAMETER__ 
#define __J4IRQC1PARAMETER__ 
//=============================================
//
//
//=============================================


#define _QC1MARGIN_ kCarTolerance
#define _QC1PHIMARGIN_ 0.1*degree
//#define _QC1PHIMARGIN_ kAngTolerance

// Shape of QC1
#define _QC1NCOLLAR_ 4

// Length of QC1

// Master volume (Tube) for QC1
#define _QC1INRADIUS_  80*mm
#define _QC1THICK_     85*mm
#define _QC1ZLEN_      1.67640*2*m
#define _QC1MAT_    "vacuum"

// This is given by IR
// Position of QC1 in the world 
//#define _QC1ZPOS_      _LSTAR_

// Only PI/4 part is defined.
// Iron.
#define  _QC1INRADIUS_SUS_ 150.*mm
#define  _QC1THICK_SUS_ 15*mm
#define _QC1MAT_SUS_ "Iron"

#define _QC1INRADIUS_COLLAR_ 110*mm
#define _QC1THICK_COLLAR_     40*mm
#define _QC1PHI_COLLAR_  pi/4
#define _QC1DPHI_COLLAR_ pi/14 // +-10degree=total 20degree 
#define _QC1MAT_COLLAR_ "Iron"

// S-Magnet 4Layer
#define _QC1NLAYER_COIL_   4
#define _QC1INRADIUS_COIL_ _QC1INRADIUS_COLLAR_ 
#define _QC1THICK_COIL_    _QC1THICK_COLLAR_ 
#define _QC1PHI_COIL_    0.
//#define _QC1DPHI_COIL_   (5*pi/28-pi/280 )  // minus avoid intersection
#define _QC1DPHI_COIL_   pi  // minus avoid intersection
#define _QC1MAT_COIL_    "Cupper"

// Whole
#define _QC1INRADIUS_COOLING_ _QC1INRADIUS_
#define _QC1THICK_COOLING_  (_QC1INRADIUS_COLLAR_-_QC1INRADIUS_COOLING_)
#define _QC1MAT_COOLING_ "vacuum"

// Vessel
#define _QC1INRADIUS_VACUUMVESSEL_ _QC1INRADIUS_COOLING_
#define _QC1THICK_VACUUMVESSEL_  2.*mm
#define _QC1MAT_VACUUMVESSEL_ "Iron"

// Thermal
#define _QC1INRADIUS_THERMAL_ (_QC1INRADIUS_VACUUMVESSEL_+_QC1THICK_VACUUMVESSEL_)
#define _QC1THICK_THERMAL_  8.*mm
#define _QC1MAT_THERMAL_ "vacuum"

//Thermal Vessel
#define _QC1INRADIUS_THERMALVESSEL_ (_QC1INRADIUS_THERMAL_+_QC1THICK_THERMAL_)
#define _QC1THICK_THERMALVESSEL_  8.*mm
#define _QC1MAT_THERMALVESSEL_ "Iron"

// He
#define _QC1INRADIUS_HE_ (_QC1INRADIUS_THERMALVESSEL_+_QC1THICK_THERMALVESSEL_)
#define _QC1THICK_HE_  6.*mm
#define _QC1MAT_HE_ "vacuum"

// He Vessel
#define _QC1INRADIUS_HEVESSEL_ (_QC1INRADIUS_HE_+_QC1THICK_HE_)
#define _QC1THICK_HEVESSEL_  6.*mm
#define _QC1MAT_HEVESSEL_ "Iron"

#endif

