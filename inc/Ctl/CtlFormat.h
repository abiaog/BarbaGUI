#ifndef CTLFORMAT_H_
#define CTLFORMAT_H_

#include <e32base.h>

class CFont;

class CCtlFormat : public CBase
{
public:
	TRect iRect;
	TRect iViewRect;
	TInt iLeftMarginInPixels;
	TInt iRightMarginInPixels;
	TInt iTopMarginInPixels;
	TInt iBottomMarginInPixels;
};

class CColumnFormat : public CCtlFormat
{
public:
	CColumnFormat* Clone();
	
public:
	TInt iRowHeightInPixels;
	TInt iRowSpacingInPixels;
	TInt iOddEvenRowDispersion;
};

class CRowFormat : public CCtlFormat
{
public:
	CRowFormat* Clone();
	
//public:
//	const CFont* iFont;
};

#endif /*CTLFORMAT_H_*/
