// $Id$
//*************************************************************************
//* --------------------
//* J4CALParameterList
//* --------------------
//* (Description)
//* 	Parameter list for Intermediate Tracker.
//*
//* (Update Record)
//*	2003/03/18  K.Hoshina	Original version.
//*************************************************************************

#include "J4CALParameterList.hh"
#include <algorithm>
#include "TVNewton.hh"
#include "geomdefs.hh"

J4CALParameterList* J4CALParameterList::fgInstance = 0;

//=====================================================================
//* public getter -----------------------------------------------------
J4CALParameterList* J4CALParameterList::GetInstance()
{
   if ( !fgInstance ) {
      fgInstance = new J4CALParameterList("CAL");
   }
   return fgInstance;
}

//=====================================================================
//* protected constructor ---------------------------------------------

J4CALParameterList::J4CALParameterList( const G4String& name )
  : J4VParameterList(name), fSubLayerParameterList(0)
{
   fgInstance = this;
   
   SetMaterials();
   SetParameters();
   SetVisAttributes();
   SetColors();
}

//=====================================================================
//* destructor -------------------------------------------------------

J4CALParameterList::~J4CALParameterList()
{
   delete fgInstance;
}

//=====================================================================
//* SetMaterials ------------------------------------------------------
void J4CALParameterList::SetMaterials()
{
#if 1
   fCALMaterial          = "Air";
   fConeMaterial         = "Air";
   fTowerMaterial        = "Air";
   fEMMaterial           = "Air";
   fHDMaterial           = "Air";
   fMiniConeMaterial     = "Air";
   fMiniTowerMaterial    = "Air";
   fLayerMaterial        = "Air";
#else
   fCALMaterial          = "vacuum";
   fConeMaterial         = "vacuum";
   fEMMaterial           = "vacuum";
   fHDMaterial           = "vacuum";
   fMiniConeMaterial     = "vacuum";
   fMiniTowerMaterial    = "vacuum";
   fLayerMaterial        = "vacuum";
#endif
}

//=====================================================================
//* SetParameters -----------------------------------------------------
void J4CALParameterList::SetParameters()
{
   // ==== Basic parameters ========================================= 
   // CAL --------------------- 
   fCALDeltaPhi     = 360.*deg;
   fCALPhiOffset    =   0.*deg;
   
   // Barrel ------------------ 
   fBarrelDeltaPhi  = 360.*deg;
   fBarrelPhiOffset =   0.*deg;

   // Endcap ------------------ 
#if defined(__GLD_V1__)
   fEndcapInnerR    =  40.*cm;
#else
   fEndcapInnerR    =  45.*cm;
#endif
   fEndcapDeltaPhi  = 360.*deg;
   fEndcapPhiOffset =   0.*deg;

   // Tower -------------------
   //fNominalBarrelTowerFrontSize = 4. *cm;   // Nominal granularity of BarrelTower 
   //fNominalEndcapTowerFrontSize = 4. *cm;   // Nominal granularity of EndcapTower
   fNominalBarrelTowerFrontSize = 12. *cm;   // Nominal granularity of BarrelTower 
   fNominalEndcapTowerFrontSize = 12. *cm;   // Nominal granularity of EndcapTower

#if defined(__GLD_V1__)
   // default: __GLD_V1__
   fTowerHeight                 = 141.*cm;  // Tower height
   
   fBarrelTowerFrontRho = 210.*cm; // Towers must be placed in a CAL volume completely.  
   fEndcapTowerFrontZ   = 270.*cm; // Check kern/J4ParameterList.cc and 
                                   // see CalcNextTowerEdgeAngle().
#else
   fTowerHeight                 = 190.*cm;  // Tower height
   
   fBarrelTowerFrontRho = 160.*cm; // Towers must be placed in a CAL volume completely.  
   fEndcapTowerFrontZ   = 190.*cm; // Check kern/J4ParameterList.cc and 
                                   // see CalcNextTowerEdgeAngle().
#endif

   fConstNTowers        = 1500;    // Temporary number of towers to check cellID.

   fBarrelCoverageAngle = atan2(fEndcapTowerFrontZ, fBarrelTowerFrontRho);
   // as a dip angle(lambda)

   // EM ------------------
   //fEMNLayers          = 10;
   fEMNLayers          = 38;
   fEMMiniConeNClones  = 3;
   fEMMiniTowerNClones = 3;

   // HD -------------
   //fHDNLayers          = 10;
   fHDNLayers          = 130;
   fHDMiniTowerNClones = 1;
   fHDMiniConeNClones  = 1;

   // Number of Barrel types
   fNIsBarrel          = 2;

   // Nubmer of CAL types
   fNIsEM              = 2;
   
   // ==== Calculate Tower parameters =============================== 
   G4double startlambda = 0;

   SetTowerParameters( fTowerHeight, 
                        startlambda,fBarrelCoverageAngle, 
                        fBarrelTowerFrontRho,
                        fNominalBarrelTowerFrontSize, TRUE );  

   startlambda = atan2( fEndcapInnerR, fEndcapTowerFrontZ );

   SetTowerParameters( fTowerHeight, 
                       startlambda, 0.5 * M_PI - fBarrelCoverageAngle, 
                       fEndcapTowerFrontZ,
                       fNominalEndcapTowerFrontSize, FALSE );  

   ShowTowerParameters();


}

//=====================================================================
//* SetTowerParameters ------------------------------------------------
void J4CALParameterList::SetTowerParameters( G4double towerheight,
                                             G4double startlambda,
                                             G4double endlambda,
                                             G4double length,
                                             G4double nominalwidth, 
                                             G4bool   isbarrel )
{
   // SetTowerParameters
   // Calculate tower parameters.  
   //
   // parameters:
   //
   //
   //         y-axis
   //         : 
   //                 /                  
   //        A+------/------------+B 
   //         |     /             |
   //         |    /              | 
   //         |  X/               | 
   //        F+--/-------+E       | 
   //         : /:       |        | 
   //         :/ :      D+--------+C
   //         /..........:............G  z-axis
   //        O   z       D' 
   //
   //
   //    ntowers          : number of towers in AFEB or DEBC
   //    towerheight      : height of tower
   //    width            : width of tile at front face of tower)
   //    isbarrel         : (0, 1) = (barrel, endcap)
   //    lambda           : angAOX(barrel) or angGOX(endcap)
   //    startlambda      : angAOA(barrel) or angGOD(endcap)
   //    endlambda        : angAOE(barrel) or angGOE(endcap)
   //    length           : OF(barrel) or OD'(endcap) 
   //    r                : OX(spherical radius of front surface of tower)
   //  
   // equation: 
   //
   //    r = length * sqrt ( 1 + tan(lambda)*tan(lambda) )
   // 


   // ------------------------------------------------------
   // invalid argument check
   // ------------------------------------------------------

   if (startlambda >= endlambda) {
      std::cerr << "J4CDCParameterList::SetTowerParameters: endlambda is bigger than startlambda! abort."
                << std::endl;
      abort();
   }

   // ------------------------------------------------------
   // definition of local parameters
   // ------------------------------------------------------

   G4double r;          
   G4double startr;          
   G4double width;      // tile width of tower-front 
   G4double lambda;     // tower edge angle (lower side of lambda) 
   G4double nextlambda; // tower edge angle (upper side of lambda)  
   G4double dlambda;    // nextlambda - lambda
   G4double tanlambda;
   G4double tanlambda2;

   // ------------------------------------------------------
   // compensate nominal width 
   // ------------------------------------------------------

   G4int ntowers = 0;

   if (startlambda == 0) {
      // Gaps should not be placed at dipangle(lambda) = 0.

      tanlambda    = (0.5 * nominalwidth / length);
      lambda       = atan(tanlambda);
      ntowers++;

   } else { 

      lambda       = startlambda + kAngTolerance * 1.e3; 
      tanlambda    = tan(lambda);

   }

   tanlambda2   = tanlambda * tanlambda;
   startr       = length * sqrt(1 + tanlambda2); 
   r            = startr;

   width    = nominalwidth;

   while (lambda < endlambda) {

      nextlambda = CalcNextTowerEdgeAngle(startr, width, lambda);

      if (nextlambda > endlambda) {
         nextlambda = endlambda;
         dlambda      = nextlambda - lambda; 
         break;
      }
      lambda       = nextlambda; 
      tanlambda    = tan(lambda);
      tanlambda2   = tanlambda * tanlambda;
      r            = length * sqrt(1 + tanlambda2) ; 
      ntowers++;
   }

   nominalwidth      += r * dlambda / ntowers;

   std::cerr << "  ntowers = " << ntowers << std::endl;
   std::cerr << "  nominal tile size is replaced to " 
             << nominalwidth / cm << " cm. " << std::endl; 

   // ------------------------------------------------------
   // set tower parameters 
   // ------------------------------------------------------

   // reset parameters 

   G4double lastlambda;
   G4double centerlambda;  // lambda at the center of tower-front

   J4CALTowerParam *paramright = 0;
   J4CALTowerParam *paramleft  = 0;

   ntowers = 0;

   if (startlambda == 0) {
      // Gaps should not be placed at dipangle(lambda) = 0.
      // Put first tower at the center of the barrel 

      r            = startr;
      width        = nominalwidth;
      dlambda      = 2 * asin(0.5 * width / r);
      centerlambda = 0; 
      r            /= cos(0.5 * dlambda);
 
      paramright = new J4CALTowerParam(r, 
                                       towerheight, 
                                       centerlambda,
                                       dlambda,
                                       width, 
                                       isbarrel);

      J4CALTowerParamPair pair(centerlambda, paramright);
      fTowerParamVector.push_back(pair);
      ntowers++;

      lambda     = 0.5 * dlambda;


   } else { 
      lambda = startlambda + kAngTolerance * 1.e3; 
      r      = startr;
   }

   // calculate ntowers 

   lastlambda = -DBL_MAX;
   width = nominalwidth;

   while (lambda < endlambda) {

      nextlambda   = CalcNextTowerEdgeAngle(startr, width, lambda);   

      if (nextlambda > endlambda) {
         nextlambda = endlambda; 
      } 

      dlambda  = nextlambda - lambda; 

      if (dlambda < 0.5 * nominalwidth / r) {

         if (lastlambda == -DBL_MAX) {
            std::cerr << "J4CDCParameterList::SetTowerParameters:"
                      << " You may set too big nominal tile size. abort."
                      << std::endl;
            abort();
         }

         std::cerr << "J4CDCParameterList::SetTowerParameters:"
                   << " delta lambda is too small! " << std::endl;
         std::cerr << "  i, r, dlambda, rdlambda " 
                   << ntowers << " " << r << " " 
                   << dlambda << " " << r * dlambda << std::endl; 
        
         // delete the narrow tower and put it to the previous,
         fTowerParamVector.pop_back(); 
         fTowerParamVector.pop_back(); 
         if (paramright) delete paramright; 
         if (paramleft)  delete paramleft; 
         ntowers--;

         lambda  = lastlambda;
         dlambda = endlambda - lambda - kAngTolerance * 1.e3; 

         std::cerr << "  marged formar tower. " << std::endl;
         std::cerr << ( isbarrel ? " Barrel" : "Endcap" )  << std::endl;
         std::cerr << "  i, r, dlambda, rdlambda " 
                   << ntowers << " " << r << " " << dlambda 
                   << " " << r * dlambda << std::endl; 
      }
            
      centerlambda = lambda + 0.5 * dlambda;
      r = length / cos(nextlambda); 

      // if endcap CAL, replace theta(angGOX) to lambda(angFOX)  

      if (!isbarrel) centerlambda = 0.5 * M_PI - centerlambda;

      paramright = new J4CALTowerParam( r, 
                                        towerheight, 
                                        centerlambda,
                                        dlambda,
                                        nominalwidth, 
                                        isbarrel      );
      paramleft  = new J4CALTowerParam( r, 
                                        towerheight, 
                                        - centerlambda,
                                        dlambda,
                                        nominalwidth,
                                        isbarrel       );
      ntowers++;

      J4CALTowerParamPair pairright(centerlambda, paramright);
      J4CALTowerParamPair pairleft(- centerlambda, paramleft);

      fTowerParamVector.push_back(pairright);
      fTowerParamVector.push_back(pairleft);

      lastlambda = lambda; 

      // calculate next r 

      lambda       = nextlambda;
   }

   // sort fTowerParamPair .....
   
   sort(fTowerParamVector.begin(), fTowerParamVector.end());
   reverse(fTowerParamVector.begin(), fTowerParamVector.end());

}


//=====================================================================
//* EstimateNtowers ---------------------------------------------------
G4int J4CALParameterList::EstimateNtowers( G4double length,
                                           G4double width,
                                           G4double lambdamin,
                                           G4double lambdamax )
{
   // EstimateNtowers 
   // Estimate number of towers in half length of the barrel calorimeter
   // along z-axis or full radius of the endcap calorimeter .
   //
   //
   // parameters:
   //
   //
   //         y-axis
   //         : 
   //                 /                  
   //        A+------/------------+B 
   //         |     /             |
   //         |    /              | 
   //         |  X/               | 
   //        F+--/-------+E       | 
   //         : /:       |        | 
   //         :/ :      D+--------+C
   //         /.......................G  z-axis
   //        O   z  
   //
   //
   // Equations:
   // 
   //    0A     = length 
   //    angA0X = lambda  
   //    angA0A or angG0D = lambdamin;
   //    angA0E or angG0E = lambdamax;
   //
   //    OX     = r = length * sqrt ( 1 + tan(lambda)*tan(lambda) )
   //    w      = width   // width of tile at front face of tower)
   //    
   //    dn    ~= r * dlambda / w    
   //           = length * sqrt(1 + tan(lambda) * tan(lambda)) / w   
   //    
   //                                                  sin(lambdamax)    
   //    n ~= length / (2*w) * [ ln ((1 + x)/(1 - x)) ]    
   //                                                  sin(lambdamin) 
   //    


   G4double sinlambmax = sin(lambdamax); 
   G4double sinlambmin = sin(lambdamin); 

   G4double ulim = log((1 + sinlambmax) / (1 - sinlambmax));   
   G4double llim = log((1 + sinlambmin) / (1 - sinlambmin));   

   return (G4int) (0.5 * length / width * ( ulim - llim ));
}

//=====================================================================
//* CalcNextTowerEdgeAngle --------------------------------------------
G4double J4CALParameterList::CalcNextTowerEdgeAngle(G4double r,
                                                    G4double width,
                                                    G4double lambda)
{
   //CalcNextTowerEdgeAngle 
   // Calculate edge angle of next tower. 
   //
   // parameters:
   //
   //
   //         y-axis   
   //          
   //         |             
   //         |               
   //         |             /     /
   //         |            /     / 
   //         |           /     /
   //         |          /     /
   //         |         /    /
   //         |        /_   /
   //         |     X /  -_/X'             
   //        F+------/----------------+E  
   //         :     /:                |  
   //         :    / :                |  
   //         :   /  :                |   
   //         :  /   :               D+--------
   //         : /    :     
   //         :/     :    
   //         /................................G  z-axis
   //        O       z 
   //
   //
   // Equations:
   //  
   //     
   //    angFOX  = lambda[i-1]  
   //    angXOX' = dlambda[i]  
   //    angFOX' = lambda[i]  
   //    OF      =  R = fBarrelFrontRho
   //    OX'     = r[i] = length / cos( lambda[i] )
   //    w       = width       // width of tile at front face of tower)
   //
   //    sin(0.5 * dlambda[i]) = 0.5 * w / r[i]
   //
   //    0 = F( dlambda[i] )
   //      = 2 * sin( dlambda[i] / 2) - ( W / R ) * cos( lambda[i-1] + dlambda[i] )
   //
   //

class Solver : public TVNewton {
   public:
     Solver( G4double r, G4double w, G4double l, G4double x )
       : TVNewton( x ), fR(r), fW(w), fLambda(l)
     {
     }
     
     G4double F(G4double x)
     {
       return  2 * sin(0.5 * x) - (fW/fR) * cos(fLambda + x );
     }
    
     G4double DFdx(G4double x)
     {
       return cos(0.5 * x) + (fW/fR) * sin(fLambda + x );
     }

     void SetR      (G4double r) { fR = r; }       
     void SetW      (G4double w) { fW = w; }       
     void SetLambda (G4double l) { fLambda = l; }       

   private: 
     G4double fR;
     G4double fW;
     G4double fLambda;
   };
     
   G4double dlambda = width/r;
   Solver sol( r, width, lambda, dlambda );
  
   return lambda + sol.Solve();
}

//=====================================================================
//* ShowTowerParameters -----------------------------------------------
void J4CALParameterList::ShowTowerParameters()
{
   std::cerr << " ============================================================ " << std::endl;
   std::cerr << "   Calorimeter Tower Parameters " << std::endl;
   std::cerr << " ----+---------+---------+---------+---------+---------+---------+---------+---------+---------+ " << std::endl;
   std::cerr << "       barrel    Radius    Height    Lambda    Dlambda   Wlambda   Nphi      Dphi      Wphi      " << std::endl;
   std::cerr << " ----+---------+---------+---------+---------+---------+---------+---------+---------+---------+ " << std::endl;

   for (G4int i=0; i < GetNcones(); i++) {

      std::cerr << std::setw(4) << i ;
      GetTowerParam(i)->ShowData();

   }
}

//=====================================================================
//* SetVisAttributes --------------------------------------------------
void J4CALParameterList::SetVisAttributes()
{
  fCALVisAtt         = TRUE;//FALSE;
   fBarrelVisAtt      = FALSE;
   fEndcapVisAtt      = FALSE;
   fConeVisAtt        = TRUE;//FALSE;
   fTowerVisAtt       = TRUE;//FALSE; 
   fEMVisAtt          = FALSE;//TRUE;
   fHDVisAtt          = FALSE;//TRUE;
   fMiniConeVisAtt    = FALSE;
   fMiniTowerVisAtt   = FALSE;
   fLayerVisAtt       = FALSE;
   fSubLayerVisAtt    = FALSE;
}

//=====================================================================
//* SetColors ---------------------------------------------------------
void J4CALParameterList::SetColors()
{
   SetCALColor(G4Color(0., 0., 1.));
   SetBarrelColor(G4Color(0., 0., 1.));
   SetEndcapColor(G4Color(0., 0., 1.));
   SetConeColor(G4Color(1., 0., 0.));
   SetTowerColor(G4Color(0., 1., 0.));
   SetEMColor(G4Color(0., 0., 1.));
   SetHDColor(G4Color(1., 0., 0.));
   SetMiniConeColor(G4Color(1., 1., 0.));
   SetMiniTowerColor(G4Color(0., 1., 0.));
   SetLayerColor(G4Color(0., 1., 0.));
   SetSubLayerColor(G4Color(0., 1., 0.));
}
