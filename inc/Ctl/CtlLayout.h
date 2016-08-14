#ifndef CTLLAYOUT_H_
#define CTLLAYOUT_H_

#include <e32base.h>

#include "Ctl/CtlFormat.h"
#include "VideoListCtl.h"

class CCtlLayout : public CBase
{
public:
	virtual ~CCtlLayout() {}
	virtual void DoLayout(const TRect& /*aRect*/) const {}
	virtual void GetComponentRect(const TInt aComponentId,TRect& aRect) const {}
};

class CColumnLayout : public CCtlLayout
{
public:
	CColumnLayout();
	virtual ~CColumnLayout();
	
	virtual void GetComponentRect(const TInt aComponentId,TRect& aRect) const;
	
	void SetFormat(CColumnFormat* aColumnFormat) {iFormat = aColumnFormat;}
	
protected:
	CColumnFormat* iFormat;
};

class CRowLayout : public CCtlLayout
{
public:
	CRowLayout();
	virtual ~CRowLayout();
		
	void SetFormat(CRowFormat* aRowFormat) {iFormat = aRowFormat;}
	
protected:
	CRowFormat* iFormat;
};



#endif /*CTLLAYOUT_H_*/
