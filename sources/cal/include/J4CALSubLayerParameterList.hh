// Id: J4CALSubLayerParameterList.hh 
//    original by S.Kisimoto, mailto: kisimoto@phys.sci.kobe-u.ac.jp
// ============================================================================
// ============================================================================
#ifndef __J4_SUB_LAYER_PARAMETER_LIST_H__
#define __J4_SUB_LAYER_PARAMETER_LIST_H__ 1

// libstdc++
//#include <utility>   // for pair
//#include <iostream>  // for cout, cerr, endl
#include <vector>    // for vector
//#include <string>    // for string
#include <map>       // for map
#include <iomanip>   // for setw
#include <cstdlib>   // for exit()

// libG4
#include "G4Color.hh"

// ============================================================================
//
//    class definition
//    
//    note:
//    because all of this class methods are implemented as inline method.
//    they are coded in .hh file 
//
// ============================================================================
class J4CALSubLayerParameterList
{
      // ----------------------------------------------------------------------
      // typdefs used inside J4CALSubLayerParameterList
      // ----------------------------------------------------------------------
   private:
      typedef G4String BlockName;
      typedef G4double LayerSize;
      typedef G4String LayerMatName;
      typedef G4bool   LayerVisAtt;
      typedef G4Color  LayerColor; // G4Color
      class J4CALSubLayerParameters;

      // ----------------------------------------------------------------------
      //  constructors, copy constructor operator-equal  and destructor
      // ----------------------------------------------------------------------
   public:
      // default constructor
      inline J4CALSubLayerParameterList()
         //: layerParams( std::map< BlockName, std::vector<J4CALSubLayerParameters> >() ),
         //  sdMaterial(  std::vector<LayerMatName>() )
         : layerParams(),
           sdMaterial()
      {
         setParameters();
         setSDMaterials();
      }

   private:
      // clients cannot use either copy constructor or operator-equal.
      J4CALSubLayerParameterList(const J4CALSubLayerParameterList& copyConstructor);
      J4CALSubLayerParameterList& operator=(const J4CALSubLayerParameterList& rhs);
   
   public:
      // destructor
      inline ~J4CALSubLayerParameterList()
      {
      }

      // ----------------------------------------------------------------------
      // setters for parameters
      // ----------------------------------------------------------------------
   private:
      inline void setParameters()
      {
         // order, size, material.
         setEMParameters();
         setHDParameters();
 
      }

      inline void setEMParameters()
      {
         std::vector<J4CALSubLayerParameters> layerBlockParams;
         // ====================================================================
         // from here
         // you can change EM (layersize, layer material, visAtt, color) here.
         // note: you must keep strictly push_back-order.
         
         layerBlockParams.push_back( J4CALSubLayerParameters(4. *mm, "Lead",         false, G4Color(0, 0, 0)) );
         layerBlockParams.push_back( J4CALSubLayerParameters(1. *mm, "Scintillator", false, G4Color(0, 0, 0)) );
	 //         layerBlockParams.push_back( J4CALSubLayerParameters(2. *mm, "Scintillator", false, G4Color(0, 0, 0)) );
	 //         layerBlockParams.push_back( J4CALSubLayerParameters(3. *mm, "Scintillator", false, G4Color(0, 0, 0)) );
         // to here.
         // ====================================================================

         layerParams.insert( std::pair<BlockName, std::vector<J4CALSubLayerParameters> >("EM", layerBlockParams) );
      }
         
      inline void setHDParameters()
      {
         std::vector<J4CALSubLayerParameters> layerBlockParams;
         // ====================================================================
         // from here
         // you can change EM (layersize, layer material, visAtt, color) here.
         // note: you must keep strictly push_back-order.
         
         layerBlockParams.push_back( J4CALSubLayerParameters(8., "Lead",         false, G4Color(0, 0, 0)) );
         layerBlockParams.push_back( J4CALSubLayerParameters(2., "Scintillator", false, G4Color(0, 0, 0)) );
         //layerBlockParams.push_back( J4CALSubLayerParameters(3., "Scintillator",  false, G4Color(0, 0, 0)) );
         // to here.
         // ====================================================================

         layerParams.insert( std::pair<BlockName, std::vector<J4CALSubLayerParameters> >("HD", layerBlockParams) );
      }

      inline void setSDMaterials()
      {
         // ====================================================================
         // Sensitive detector or not
         // this implementation ==> only Sci is sensitive.
         // ====================================================================
         sdMaterial.push_back("Scintillator"); // Sci is sensitive.
         //sdMaterial.push_back("Lead");
         //sdMaterial.push_back("Scintillator");
      }

      // ----------------------------------------------------------------------
      //  Getters 
      // ----------------------------------------------------------------------
   public:
      inline const G4int GetNLayers(const BlockName& blockName) const 
      {
         // blockName: EM or HD
         checkBlockName(blockName);

         return GetLayerParamsVector(blockName).size();
      }

      inline const G4double& GetLayerSize(const BlockName& blockName, const G4int& layerOrder) const
      {
         // blockName:    EM or HD
         checkBlockName(blockName);
         checkLayerBoundary(blockName, layerOrder);

         return GetLayerParamsVector(blockName)[layerOrder].GetLayerSize();
      }

      inline const G4double GetTotalLayerSize(const BlockName& blockName) const
      {
         // blockName:    EM or HD
         checkBlockName(blockName);

         const std::vector<J4CALSubLayerParameters>& refLayerParamsVector 
            = GetLayerParamsVector(blockName);

         G4double totalLayerSize = 0.;
         
         //for( size_t layerOrder = 0; layerOrder < refLayerParamsVector.size(); layerOrder++ ) {
         for( G4int layerOrder = 0; layerOrder < (G4int)refLayerParamsVector.size(); layerOrder++ ) {
            totalLayerSize += refLayerParamsVector[layerOrder].GetLayerSize();
         }
         return totalLayerSize;
      }

      inline const G4double GetLayerFront(const BlockName& blockName, const G4int& layerOrder) const
      {
         // blockName:    EM or HD
         checkBlockName(blockName);
         checkLayerBoundary(blockName, layerOrder);
     
         G4double layerFront = 0;

         //for( size_t i = 0; i < layerOrder; i++ ) {
         for( G4int i = 0; i < layerOrder; i++ ) {
            layerFront += GetLayerSize(blockName, layerOrder);
         }
         
         return layerFront;
      }

      inline const G4String& GetLayerMaterial(const BlockName& blockName, const G4int& layerOrder) const
      {
         // blockName:    EM or HD
         checkBlockName(blockName);
         checkLayerBoundary(blockName, layerOrder);

         return GetLayerParamsVector(blockName)[layerOrder].GetLayerMatName();
      }

      inline const G4bool& GetLayerVisAtt(const BlockName& blockName, const G4int& layerOrder) const
      {
         checkBlockName(blockName);
         checkLayerBoundary(blockName, layerOrder);

         return GetLayerParamsVector(blockName)[layerOrder].GetLayerVisAtt();
      }
       
      inline const G4Color& GetLayerColor(const BlockName& blockName, const G4int& layerOrder) const
      {
         checkBlockName(blockName);
         checkLayerBoundary(blockName, layerOrder);

         return GetLayerParamsVector(blockName)[layerOrder].GetLayerColor();
      }

   private:
      inline const std::vector<J4CALSubLayerParameters>& 
      GetLayerParamsVector(const BlockName& blockName) const
      {
         checkBlockName(blockName);

         std::map< BlockName, std::vector<J4CALSubLayerParameters> >::const_iterator itr
            = layerParams.find(blockName);
         return itr-> second;
      }

      // ----------------------------------------------------------------------
      //    is-methods and check methods
      // ----------------------------------------------------------------------
   public:
      inline G4bool isSD(const BlockName& blockName, const G4int& layerOrder) const
      {
         checkBlockName(blockName);
         checkLayerBoundary(blockName, layerOrder);

         const LayerMatName& materialName = GetLayerMaterial(blockName, layerOrder);
         return isSDMaterial(materialName);
      }

   private:
      inline G4bool isSDMaterial(const LayerMatName& materialName) const
      {
         std::vector<LayerMatName>::const_iterator itr = sdMaterial.begin();
         G4bool _IsSDMaterial = false;

         while( itr != sdMaterial.end() ) {
            if( *itr == materialName ) {
               _IsSDMaterial = true;
               break;
            }
            itr++;
         }
         return _IsSDMaterial;
      }

   private:
      inline void checkBlockName(const BlockName& blockName) const
      {
         if( !(blockName == "EM" || blockName == "HD" ) ) {
            std::cerr << " Error: blockName is strange." << G4endl;
            exit(EXIT_FAILURE);
         } 
         return;
      }

      inline void checkLayerBoundary(const BlockName& blockName, const G4int& layerOrder) const
      {
         if( layerOrder >= (G4int)GetLayerParamsVector(blockName).size() ) {
            std::cerr << " Error in " << blockName << ": layerOrder >= nLayers " << G4endl;
            exit(EXIT_FAILURE);
         }
         return;
      }

      // ----------------------------------------------------------------------
      //    print-methods
      // ----------------------------------------------------------------------
      // print methods.
   public:
      inline void printParameters(const BlockName& blockName) const
      {
         // blockName:    EM or HD
         checkBlockName(blockName);

         G4cout.setf(std::ios_base::boolalpha);
         G4cout << G4endl
                << "  " << blockName << ": "<< G4endl 
                << "  ==============================================================" << G4endl 
                << "   " << std::setw(12) << "layer number"   << " | "
                << "   " << std::setw (8) << "material"       << " | "
                << "   " << std::setw(15) << "layer size(mm)" << " | "
                << "   " << std::setw (7) << "is SD ?"       
                << G4endl;

          G4cout << "  ==============================================================" << G4endl;
          for( G4int i = 0; i < GetNLayers(blockName); i++ ) {
             G4cout << "   " << std::setw(12) << i                             << " | " 
                    << "   " << std::setw (8) << GetLayerMaterial(blockName, i)  << " | " 
                    << "   " << std::setw(15) << GetLayerSize(blockName, i)      << " | "
                    << "   " << std::setw (7) << isSD(blockName, i)
                    << "   " << G4endl;
          }
          G4cout << "  ==============================================================" << G4endl;
          G4cout << G4endl;
          G4cout.unsetf(std::ios_base::boolalpha);
      }

      // ======================================================================
      // data-format:
      //    class definition
      // ======================================================================
   private:
      class J4CALSubLayerParameters
      {
         public:
            inline J4CALSubLayerParameters(const LayerSize&    aLayerSize, 
                                           const LayerMatName& aLayerMaterial,
                                           const LayerVisAtt&  aLayerVisAtt,
                                           const LayerColor&   aLayerColor) 
            : layerSize(aLayerSize), 
              layerMaterial(aLayerMaterial),
              layerVisAtt(aLayerVisAtt),
              layerColor(aLayerColor)
         {
         }

      public:
         // Getters.
         inline const LayerSize&    GetLayerSize   () const { return layerSize;     }
         inline const LayerMatName& GetLayerMatName() const { return layerMaterial; }
         inline const LayerVisAtt&  GetLayerVisAtt () const { return layerVisAtt;   }
         inline const LayerColor&   GetLayerColor  () const { return layerColor;    }

      private:
         LayerSize    layerSize;
         LayerMatName layerMaterial;
         LayerVisAtt  layerVisAtt;
         LayerColor   layerColor;
      };

      // ----------------------------------------------------------------------
      //    data-members
      // ----------------------------------------------------------------------
   private:
      std::map< BlockName, std::vector<J4CALSubLayerParameters> > layerParams;

      std::vector<LayerMatName>    sdMaterial;
};

#endif // the end of __J4_SUB_LAYER_PARAMETER_LIST_H__
