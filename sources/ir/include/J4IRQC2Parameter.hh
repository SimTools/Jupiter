// $Id$
#ifndef __J4IRQC2PARAMETER__ 
#define __J4IRQC2PARAMETER__ 
//=============================================
//
//
//=============================================

#include <math.h>

#define _QC2MARGIN_ 1.e-6*mm

#define _QC2PHI_COLLAR_ 45.*degree

// Master volume (Box) for QC2
#define _QC2HBOX_ 10.2*cm*2   // full length of Horizontal 
#define _QC2VBOX_ 16.0*cm*2
#define _QC2ZLEN_      1.99796*2*m
#define _QC2MAT_    "vacuum"

#define _QC2INRADIUS_ 5*cm

// Position of QC2
#define _QC2ZPOS_      1252.7289*cm

//Coil
#define _QC2NCOIL_  4
#define _QC2HBOX_COIL_ 20.*mm
#define _QC2VBOX_COIL_ 60.*mm
#define _QC2XPOS1_COIL_ (101.666+81.666)/2.*mm
#define _QC2XPOS2_COIL_ (25+5)/2.*mm
#define _QC2YPOS_COIL_ (115.+55.)/2.*mm
#define _QC2MAT_COIL_    "Copper"

// Iron Collars
#define _QC2MAT_IRON_  "Iron"
// IronBox1
#define _QC2NIRON1_ 2
#define _QC2HBOX_IRON1_   80.*mm*2
#define _QC2VBOX_IRON1_   40.*mm
#define _QC2XPOS_IRON1_    0.*mm
#define _QC2YPOS_IRON1_  140.*mm

// IronBox2 
#define _QC2NIRON2_ 4
#define _QC2HBOX_IRON2_   (80.-26.666)*mm  // Full Length
#define _QC2VBOX_IRON2_   (120-51.666)*mm  
#define _QC2XPOS_IRON2_   (80.+26.666)/2.*mm
#define _QC2YPOS_IRON2_   (120.+51.666)/2.*mm

// IronBox3 ( Trap )
#define _QC2NIRON3_ 4
#define _QC2PZ_IRON3_    _QC2ZLEN_
#define _QC2PLTX_IRON3_  sqrt(pow((26.666-6.666),2.)+pow((51.666-35),2.))*mm

// Iron Collar2 (x4)
#endif

