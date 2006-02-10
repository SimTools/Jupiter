#ifndef __J4CLXHDACTIVESD__
#define __J4CLXHDACTIVESD__

#include "J4VSD.hh"
#include "J4CLXHit.hh"
#include "J4VCLXActiveSD.hh"
#include "J4VCLXDetectorComponent.hh"

//=====================================================================
//---------------------
// class definition
//---------------------
class J4CLXHDActiveSD : public J4VCLXActiveSD {
public:
    J4CLXHDActiveSD(J4VDetectorComponent* ptrDetector);
    ~J4CLXHDActiveSD();

    using J4VSD<J4CLXHit>::operator=;

    virtual G4bool IsEM();
};

//=====================================================================
//* Inline Implementation of Pure Virtuals of Base Class --------------
inline G4bool J4CLXHDActiveSD::IsEM()
{
    return false;
}

#endif
