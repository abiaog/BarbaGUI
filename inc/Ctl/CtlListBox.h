#ifndef CTLLISTBOX_H_
#define CTLLISTBOX_H_

#include <e32cmn.h>
#include <gulicon.h>

class MCtlListBoxObserver;
class CGulIcon;
//class RPointerArray;

class CCtlListBox 
{
public:
	MCtlListBoxObserver* Observer() {return iObserver;}
	void SetObserver(MCtlListBoxObserver* aObserver) {iObserver = aObserver;}
	TInt AppendIcon(CGulIcon* aGulIcon);
	~CCtlListBox();
	
protected:
	CCtlListBox();
	
protected:
	MCtlListBoxObserver* iObserver;
	RPointerArray<CGulIcon> iIconArray;
};

#endif /*CTLLISTBOX_H_*/
