#ifndef CTLMODEL_H_
#define CTLMODEL_H_

#include <e32base.h>
#include <e32cmn.h>
#include <w32std.h>
#include <gulicon.h>

#include "Ctl/CtlFormat.h"

class CCtlModel : public CBase
{
public:
	virtual ~CCtlModel() {}
	
	virtual void Add(CCtlModel* /*aCtlModel*/) {}
	virtual void Remove(TInt /*anIndex*/) {}
	virtual TInt Insert(CCtlModel* /*aCtlModel*/, TInt /*aPos*/) {return 0;}
	virtual void Reset() {}
	virtual TInt Count() {return 0;}
	virtual void Draw(CWindowGc& gc,const TRect* aRect) const = 0;
	virtual void MakeVisible(TBool /*aVisible*/) {}
	virtual CCtlModel* At(TInt /*aIndex*/) {return NULL;}
	virtual CCtlModel* Clone() = 0;
	virtual CCtlModel* Clone3D() = 0;
	virtual TRect* Rect() const {return NULL;}
protected:
	CCtlModel() {}	
};


#endif /*CTLMODEL_H_*/
