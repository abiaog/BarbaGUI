#include "Ctl/CtlLayout.h"

////////////////////////////////////////////////////////////
////CColumnLayout
////////////////////////////////////////////////////////////
CColumnLayout::CColumnLayout()
{

}

CColumnLayout::~CColumnLayout()
{
}

void CColumnLayout::GetComponentRect(const TInt aComponentId,TRect& aRect) const
{
	aRect.iTl.iX = iFormat->iRect.iTl.iX + iFormat->iLeftMarginInPixels;
	aRect.iTl.iY = iFormat->iRect.iTl.iY + iFormat->iTopMarginInPixels
	             + 2 * aComponentId * iFormat->iRowSpacingInPixels
	             + aComponentId * iFormat->iRowHeightInPixels;
	aRect.iBr.iY = aRect.iTl.iY + iFormat->iRowHeightInPixels;
	aRect.iBr.iX = iFormat->iRect.iBr.iX - iFormat->iRightMarginInPixels;
}


////////////////////////////////////////////////////////////
////CRowLayout
////////////////////////////////////////////////////////////
CRowLayout::CRowLayout()
{
}

CRowLayout::~CRowLayout()
{
}
