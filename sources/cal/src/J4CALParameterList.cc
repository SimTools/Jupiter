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
#include "./algorithm"

J4CALParameterList    * J4CALParameterList::fgInstance = 0;

//=====================================================================
//* public getter -----------------------------------------------------
J4CALParameterList* J4CALParameterList::GetInstance()
{
   if (!fgInstance) {
      J4CALParameterList* instance = new J4CALParameterList("CAL");
   }
   return fgInstance;
}

//=====================================================================
//* protected constructor ---------------------------------------------

J4CALParameterList::J4CALParameterList(const G4String& name)
                  :J4VParameterList(name)
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
   fEMMaterial           = "Lead";
   fHDMaterial           = "Lead";
#else
   fCALMaterial          = "vacuum";
   fConeMaterial         = "vacuum";
   fTowerMaterial        = "vacuum";
#endif
}

//=====================================================================
//* SetParameters -----------------------------------------------------
void J4CALParameterList::SetParameters()
{


   // ==== Basic parameters ========================================= 

   // CAL --------------------- 

   fCALDeltaPhi    = 360.*deg;
   fCALPhiOffset   = 0.*deg;
   
   // Barrel ------------------ 

   fBarrelDeltaPhi      = 360.*deg;
   fBarrelPhiOffset     = 0.*deg;

   // Endcap ------------------ 

   fEndcapInnerR    = 45.*cm;
   fEndcapDeltaPhi  = 360.*deg;
   fEndcapPhiOffset = 0.*deg;

   // Tower -------------------

   fNominalBarrelTowerFrontSize = 4. *cm;   // Nominal granularity of BarrelTower 
   fNominalEndcapTowerFrontSize = 4. *cm;   // Nominal granularity of EndcapTower
   fTowerHeight                 = 190.*cm;  // Tower height
   
   fBarrelTowerFrontRho = 160.*cm; // Towers must be placed in a CAL volume completely.  
   fEndcapTowerFrontZ   = 190.*cm; // Check kern/J4ParameterList.cc and 
                                   // see CalcNextTowerEdgeAngle().

   fBarrelCoverageAngle = atan2(fEndcapTowerFrontZ, fBarrelTowerFrontRho);
      // as a dip angle(lambda)
   
   // ==== Calculate Tower parameters =============================== 
   
   G4double startlambda = 0;

   SetTowerParameters(fTowerHeight, 
                      startlambda,fBarrelCoverageAngle, 
                      fBarrelTowerFrontRho,
                      fNominalBarrelTowerFrontSize, TRUE);  

   startlambda = atan2(fEndcapInnerR, fEndcapTowerFrontZ);

   SetTowerParameters(fTowerHeight, 
                      startlambda, 0.5 * M_PI - fBarrelCoverageAngle, 
                      fEndcapTowerFrontZ,
                      fNominalEndcapTowerFrontSize, FALSE);  

   ShowTowerParameters();

   // EM -------------------

   fEMThickness = 26. *cm;

   // HD -------------------

   fHDThickness = 156. *cm;

}

//=====================================================================
//* SetTowerParameters ------------------------------------------------
void J4CALParameterList::SetTowerParameters(G4double towerheight,
                                            G4double startlambda,
                                            G4double endlambda,
                                            G4double length,
                                            G4double nominalwidth, 
                                            G4bool   isbarrel)
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
      G4cerr << "J4CDCParameterList::SetTowerParameters: endlambda is bigger than startlambda! abort."
             << G4endl;
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

      startr       = length;
      lambda       = asin(0.5 * nominalwidth / startr);
      tanlambda    = tan(lambda);
      tanlambda2   = tanlambda * tanlambda;
      r            = length * sqrt(1 + tanlambda2); 
      ntowers++;

   } else { 

      lambda       = startlambda;
      tanlambda    = tan(lambda);
      tanlambda2   = tanlambda * tanlambda;
      startr       = length * sqrt(1 + tanlambda2); 
      r            = startr;

   }

   width    = nominalwidth;

   while (lambda < endlambda) {

      nextlambda = CalcNextTowerEdgeAngle(r, width, lambda);

      if (nextlambda > endlambda) {
         nextlambda = endlambda;
      }

      dlambda      = nextlambda - lambda;

      lambda       = nextlambda; 
      tanlambda    = tan(lambda);
      tanlambda2   = tanlambda * tanlambda;
      r            = length * sqrt(1 + tanlambda2); 
      ntowers++;
   }

   G4double ddlambda = dlambda / ntowers;
   G4double ddr      = 0.5 * (startr + r);
   G4double ddwidth  = 2 * ddr * sin( 0.5 * ddlambda); 
   nominalwidth      += ddwidth;

   G4cerr << "  ntowers = " << ntowers << G4endl;
   G4cerr << "  nominal tile size is replaced to " 
          << nominalwidth / cm << " cm. " << G4endl; 

   // ------------------------------------------------------
   // set tower parameters 
   // ------------------------------------------------------

   // reset parameters 

   G4double lastr;
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

      paramright = new J4CALTowerParam(r, 
                                       towerheight, 
                                       centerlambda,
                                       dlambda,
                                       width, 
                                       isbarrel);

      J4CALTowerParamPair pair(centerlambda, paramright);
      fTowerParamVector.push_back(pair);
      ntowers++;

      lambda     = asin(0.5 * width / r);
      tanlambda  = tan(lambda);
      tanlambda2 = tanlambda * tanlambda;
      r          = length * sqrt(1 + tanlambda2); 

   } else { 
      lambda = startlambda;
      r      = startr;
   }

   // calculate ntowers 

   lastlambda = -DBL_MAX;

   while (lambda < endlambda) {

      width = nominalwidth;
      
      nextlambda   = CalcNextTowerEdgeAngle(r, width, lambda);   

      if (nextlambda > endlambda) {
         nextlambda = endlambda; 
         width = 2 * r * sin( 0.5 * (nextlambda - lambda) ); 
      } 

      dlambda  = nextlambda - lambda; 

      if (dlambda < 0.5 * nominalwidth / r) {

         if (lastlambda == -DBL_MAX) {
            G4cerr << "J4CDCParameterList::SetTowerParameters:"
                   << " You may set too big nominal tile size. abort."
                   << G4endl;
            abort();
         }

         G4cerr << "J4CDCParameterList::SetTowerParameters:"
                << " delta lambda is too small! " << G4endl;
         G4cerr << "  i, r, dlambda, rdlambda " 
                << ntowers << " " << r << " " 
                << dlambda << " " << r * dlambda << G4endl; 
        
         // delete formar tower parameter 
         fTowerParamVector.pop_back(); 
         fTowerParamVector.pop_back(); 
         if (paramright) delete paramright; 
         if (paramleft)  delete paramleft; 
         ntowers--;
           
         lambda  = lastlambda;
         dlambda = endlambda - lambda; 
         r       = lastr;
         width   = 2 * r * sin( 0.5 * dlambda); 

         G4cerr << "  marged formar tower. " << G4endl;
         G4cerr << "  i, r, dlambda, rdlambda " 
                << ntowers << " " << r << " " << dlambda 
                << " " << r * dlambda << G4endl; 

      }
            
      centerlambda = lambda + 0.5 * dlambda;

      // if endcap CAL, replace theta(angGOX) to lambda(angFOX)  

      if (!isbarrel) centerlambda = 0.5 * M_PI - centerlambda;

      paramright = new J4CALTowerParam(r, 
                                       towerheight, 
                                       centerlambda,
                                       dlambda,
                                       nominalwidth, 
                                       isbarrel);
      paramleft  = new J4CALTowerParam(r, 
                                       towerheight, 
                                       - centerlambda,
                                       dlambda,
                                       nominalwidth,
                                       isbarrel);
      ntowers++;

      J4CALTowerParamPair pairright(centerlambda, paramright);
      J4CALTowerParamPair pairleft(- centerlambda, paramleft);

      fTowerParamVector.push_back(pairright);
      fTowerParamVector.push_back(pairleft);

      lastr      = r; 
      lastlambda = lambda; 

      // calculate next r 

      lambda       = nextlambda;
      tanlambda    = tan(lambda);
      tanlambda2   = tanlambda * tanlambda;
      r            = length * sqrt(1 + tanlambda2); 

   }

   // sort fTowerParamPair .....
   
   sort(fTowerParamVector.begin(), fTowerParamVector.end());
   reverse(fTowerParamVector.begin(), fTowerParamVector.end());

}


//=====================================================================
//* EstimateNtowers ---------------------------------------------------
G4int J4CALParameterList::EstimateNtowers(G4double length,
                                         G4double width,
                                         G4double lambdamin,
                                         G4double lambdamax)
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
   // CalcNextTowerEdgeAngle 
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
   //         |       X /    /
   //       F'|......../_   /.............E'
   //         |       /: -_/X'           :  
   //        F+------/----------------+E : 
   //         :     /  :              |  :
   //         :    /   :              |  :.....
   //         :   /    :              |  D' 
   //         :  /     :             D+--------
   //         : /      :     
   //         :/       :    
   //         /................................G  z-axis
   //        O         z 
   //
   //
   // Equations:
   //  
   //     
   //    angFOX  = lambda[i]  
   //    angXOX' = dlambda[i]  
   //    OF'     = fBarrelFrontRho
   //    OX      = r = length * sqrt ( 1 + tan(lambda)*tan(lambda) )
   //    w       = width       // width of tile at front face of tower)
   //
   //    sin(0.5 * dlambda[i]) = 0.5 * w / r
   //
   //    lambda[i+1] = lambda[i] + dlambda[i] 
   //
   //

   G4double deltalambda = 2 * asin(0.5 * width / r);
   return   lambda + deltalambda;

}

//=====================================================================
//* ShowTowerParameters -----------------------------------------------
void J4CALParameterList::ShowTowerParameters()
{
   G4cerr << " ============================================================ " << G4endl;
   G4cerr << "   Calorimeter Tower Parameters " << G4endl;
   G4cerr << " ----+---------+---------+---------+---------+---------+---------+---------+---------+---------+ " << G4endl;
   G4cerr << "       barrel    Radius    Height    Lambda    Dlambda   Wlambda   Nphi      Dphi      Wphi      " << G4endl;
   G4cerr << " ----+---------+---------+---------+---------+---------+---------+---------+---------+---------+ " << G4endl;

   for (G4int i=0; i < GetNcones(); i++) {

      G4cerr << std::setw(4) << i ;
      GetTowerParam(i)->ShowData();

   }
}

//=====================================================================
//* SetVisAttributes --------------------------------------------------
void J4CALParameterList::SetVisAttributes()
{
   fCALVisAtt          = FALSE;
   fBarrelVisAtt       = FALSE;
   fEndcapVisAtt       = FALSE;
   fConeVisAtt         = FALSE;
   fTowerVisAtt        = TRUE;
   fEMVisAtt           = TRUE;
   fHDVisAtt           = TRUE;
}

//=====================================================================
//* SetColors ---------------------------------------------------------
void J4CALParameterList::SetColors()
{
   SetCALColor(G4Color(0., 0., 1.));
   SetBarrelColor(G4Color(0., 0., 1.));
   SetEndcapColor(G4Color(0., 0., 1.));
   SetConeColor(G4Color(1., 1., 0.));
   SetTowerColor(G4Color(1., 1., 0.));
   SetEMColor(G4Color(1., 1., 0.));
   SetHDColor(G4Color(1., 1., 0.));
}


