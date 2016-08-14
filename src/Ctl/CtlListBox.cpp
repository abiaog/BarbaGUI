#include "Ctl/CtlListBox.h"

CCtlListBox::CCtlListBox()
: iObserver(NULL)
{
}

CCtlListBox::~CCtlListBox()
{
	iIconArray.ResetAndDestroy();
	iIconArray.Close();
}

TInt CCtlListBox::AppendIcon(CGulIcon* aGulIcon)
{
	return iIconArray.Append(aGulIcon);
}