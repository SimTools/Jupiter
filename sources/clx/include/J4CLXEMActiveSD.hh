// $Id$
#ifndef __J4CLXEMACTIVESD__
#define __J4CLXEMACTIVESD__

#include "J4VSD.hh"
#include "J4CLXHit.hh"
#include "J4VCLXActiveSD.hh"
#include "J4VCLXDetectorComponent.hh"

//=====================================================================
//---------------------
// class definition
//---------------------
class J4CLXEMActiveSD : public J4VCLXActiveSD {
public:
    J4CLXEMActiveSD(J4VDetectorComponent* ptrDetector);
    ~J4CLXEMActiveSD();

    using J4VSD<J4CLXHit>::operator=;

    virtual G4bool IsEM();
};

//=====================================================================
//* Inline Implementation of Pure Virtuals of Base Class --------------
inline G4bool J4CLXEMActiveSD::IsEM()
{
    return true;
}

#endif
