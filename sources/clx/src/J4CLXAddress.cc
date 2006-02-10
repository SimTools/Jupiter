#include "J4CLXAddress.hh"
#include "J4CLXParameterList.hh"
#include "G4Trap.hh"

#define BOARD 10000
#define PLUS   1000
#define CELL      1
#define BLOCK  1000
#define EM      100
#define LAYER     1

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------
J4CLXAddress::J4CLXAddress(G4int blockID,
			   G4bool isEM,
			   G4int layerID,
			   G4int boardID,
			   G4int cellCloneID,
			   J4VCLXCell* ptrCellComponent)
    : fBlockID(blockID), fIsEM(isEM), fLayerID(layerID),
      fBoardID(boardID), fCellID(cellCloneID), fCellComponent(ptrCellComponent)
{}

//=====================================================================
//* destructor --------------------------------------------------------
J4CLXAddress::~J4CLXAddress()
{}

//=====================================================================
//* static functions --------------------------------------------------
G4int J4CLXAddress::GetCellID()
{
    G4int tBoardID = fBoardID * BOARD;
    G4int tCellID;

    G4Trap *mother = (G4Trap *)(fCellComponent -> GetMother() -> GetSolid());
    G4double cellStep = J4CLXParameterList::GetInstance() -> GetCellSize();

    G4int isPlus;
    if(fCellID == -1) {
	isPlus = (G4int)(fCellComponent -> IsXPlus()) * PLUS;
	tCellID = (G4int)(mother -> GetXHalfLength1() / cellStep) * CELL;
    } else {
	G4int nHalfCells = (G4int)(fCellComponent -> GetNclones() / 2);

	if(fCellID - nHalfCells < 0) {
	    isPlus = 0 * PLUS;
	    tCellID = std::abs(fCellID - nHalfCells + 1) * CELL;
	} else {
	    isPlus = 1 * PLUS;
	    tCellID = std::abs(fCellID - nHalfCells) * CELL;
	}
    }

    return tBoardID + isPlus + tCellID;
}

G4int J4CLXAddress::GetLayerID()
{
    G4int tBlockID = fBlockID * BLOCK;
    G4int tEMID = (G4int)(fIsEM) * EM;
    G4int tLayerID = fLayerID * LAYER;

    return tBlockID + tEMID + tLayerID;
}

G4int J4CLXAddress::GetLongID()
{
    J4CLXParameterList* ptrList = J4CLXParameterList::GetInstance();
    G4int emLayerNo = ptrList -> GetEMNLayers();
    G4int hdLayerNo = ptrList -> GetHDNLayers();
    G4int boardNo = 2 * (G4int)(ptrList -> GetCLXInnerHalfZ() / ptrList -> GetCellSize());

    G4int boardID = fBlockID * (emLayerNo + hdLayerNo);
    if(fIsEM) {
	boardID += fLayerID * boardNo;
    } else {
	boardID += (emLayerNo + fLayerID) * boardNo;
    }

    boardID += fBoardID;

    return boardID * BOARD + (GetCellID() - fBoardID * BOARD);
}

G4ThreeVector J4CLXAddress::GetCellPosition()
{
    J4CLXParameterList* ptrList = J4CLXParameterList::GetInstance();
    G4Trap *mother = (G4Trap *)(fCellComponent -> GetMother() -> GetSolid());

    G4double cellSize = ptrList -> GetCellSize();

    G4int tCellID, isPlus;
    if(fCellID == -1) {
	isPlus = (G4int)(fCellComponent -> IsXPlus());
	tCellID = (G4int)(mother -> GetXHalfLength1() / cellSize);
    } else {
	G4int nHalfCells = (G4int)(fCellComponent -> GetNclones() / 2);

	if(fCellID - nHalfCells < 0) {
	    isPlus = 0;
	    tCellID = std::abs(fCellID - nHalfCells + 1);
	} else {
	    isPlus = 1;
	    tCellID = std::abs(fCellID - nHalfCells);
	}
    }


    G4double x, y, z;

// Layer Position
    G4double rmin = ptrList -> GetCLXInnerR();
    G4double deltaPhi = ptrList -> GetTrapDeltaPhi();

    G4double layerRadius;
    if(fIsEM) {
	layerRadius = rmin + (1.25 + fLayerID) * ptrList -> GetEMLayerThickness() - .5 * ptrList -> GetEMActiveLayerThickness();
    } else {
	layerRadius = rmin + ptrList -> GetEMLayerThickness() + (1.25 + fLayerID) * ptrList -> GetHDLayerThickness()
	                   - .5 * ptrList -> GetHDActiveLayerThickness();
    }

    x = layerRadius * std::sin(fBlockID * deltaPhi);
    y = layerRadius * std::cos(fBlockID * deltaPhi);

// Board Position
    z = -(G4int)(ptrList -> GetCLXOuterHalfZ() / cellSize) * cellSize + (.5 + fBoardID) * cellSize;

//cell position in board
    G4double cellX;

    if(fCellID == -1) {
	cellX = tCellID * cellSize + .5 * (mother -> GetXHalfLength1() + mother -> GetXHalfLength2());
    } else {
	cellX = (tCellID + .5) * cellSize;
    }
    if(isPlus == 0) cellX = -cellX;

//cell position in CLX
    x += cellX * std::cos(fBlockID * deltaPhi);
    y -= cellX * std::sin(fBlockID * deltaPhi);

    return G4ThreeVector(x, y, z);
}
