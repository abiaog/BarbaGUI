#include "Ctl/CtlFormat.h"

CColumnFormat* CColumnFormat::Clone()
{
	CColumnFormat* format = new (ELeave) CColumnFormat;
	format->iRect = iRect;
	format->iViewRect = iViewRect;
	format->iLeftMarginInPixels = iLeftMarginInPixels;
	format->iRightMarginInPixels = iRightMarginInPixels;
	format->iTopMarginInPixels = iTopMarginInPixels;
	format->iBottomMarginInPixels = iBottomMarginInPixels;
	format->iRowHeightInPixels  = iRowHeightInPixels;
	format->iRowSpacingInPixels = iRowSpacingInPixels;
	format->iOddEvenRowDispersion = iOddEvenRowDispersion;
	return format;
}

CRowFormat* CRowFormat::Clone()
{
	CRowFormat* format = new (ELeave) CRowFormat;
	format->iRect = iRect;
	format->iViewRect = iViewRect;
	format->iLeftMarginInPixels = iLeftMarginInPixels;
	format->iRightMarginInPixels = iRightMarginInPixels;
	format->iTopMarginInPixels = iTopMarginInPixels;
	format->iBottomMarginInPixels = iBottomMarginInPixels;
//	format->iFont = iFont;
	return format;
}