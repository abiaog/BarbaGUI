#include "Ctl/CtlColumn.h"

#include "Ctl/CtlLayout.h"
#include "YoukuLogger.h"
#include "ResPool.h"

CCtlColumn* CCtlColumn::NewL()
{
	CCtlColumn* self = CCtlColumn::NewLC();
	CleanupStack::Pop( self );
	return self;
}

CCtlColumn* CCtlColumn::NewLC()
{
	CCtlColumn* self = new ( ELeave ) CCtlColumn( );
	CleanupStack::PushL( self );
	self->ConstructL();
	return self;
}

void CCtlColumn::ConstructL()
{
	iComponents = new (ELeave) RPointerArray<CCtlModel>(10);
	iFormat = new (ELeave) CColumnFormat;
}

CCtlColumn::CCtlColumn()
: iComponents(NULL)
, iFormat(NULL)
, iSelectedIndex(0)
, iLayout(NULL)
, iVisible(ETrue)
{
}

CCtlColumn::~CCtlColumn()
{
	if (NULL != iComponents)
	{
		TInt count = iComponents->Count();
		TInt i = 0;
		for (; i < count; i++)
		{
			delete (*iComponents)[i];
		}
		iComponents->Close();
		delete iComponents;
	}
		
	if (NULL != iFormat)
	{
		delete iFormat;
		iFormat = NULL;
	}
}

void CCtlColumn::Add(CCtlModel* aCtlModel)
{
	iComponents->Append(aCtlModel);
}

void CCtlColumn::Remove(TInt anIndex)
{
	iComponents->Remove(anIndex);
}

TInt CCtlColumn::Insert(CCtlModel* aCtlModel, TInt aPos)
{
	return iComponents->Insert(aCtlModel,aPos);
}

void CCtlColumn::Draw(CWindowGc& gc,const TRect* aRect) const
{
	iLayout->SetFormat(this->iFormat);
	iLayout->DoLayout(*aRect); 
		
	TInt i = 0;
	TInt count = iComponents->Count();
//	DEBUG(LOG_UI, "count:%d",count);
	for (; i < count; i++)
	{
//		DEBUG(LOG_UI, "%d",i);
		CCtlModel* result = (*iComponents)[i];
		TRect rowRect;
		iLayout->GetComponentRect(i,rowRect);
		if (iVisible)
		{
			CFbsBitmap* bitmap = NULL;
			CFbsBitmap* mask = NULL;
			if (i % 2 == 0)
			{
				CResPool::Instance()->GetImagePool()->GetListBG2L(bitmap,mask);
			}
			else
			{
				CResPool::Instance()->GetImagePool()->GetListBG1L(bitmap,mask);
			}
			gc.BitBlt(TPoint(rowRect.iTl.iX,rowRect.iTl.iY),bitmap,TRect(TPoint(0,0),bitmap->SizeInPixels()));
			
			result->Draw(gc,&rowRect);
			if (i == iSelectedIndex)
			{			
//				DEBUG(LOG_UI, "Draw selector begin");
				DoSelect(result,gc,&rowRect);
//				DEBUG(LOG_UI, "Draw selector end");
			}
		}
	}
}

void CCtlColumn::MakeVisible(TBool aVisible)
{
	iVisible = aVisible;
}

CCtlModel* CCtlColumn::At(TInt aIndex)
{
	CCtlModel* result = NULL;
	if (aIndex >=0 || aIndex < iComponents->Count())
	{
		result = (*iComponents)[aIndex];
	}
	return result;
}

void CCtlColumn::Reset()
{
	if (NULL != iComponents)
	{
		iComponents->ResetAndDestroy();
	}
	iSelectedIndex = 0;
}

TRect* CCtlColumn::Rect() const
{
	return &(iFormat->iRect);
}

void CCtlColumn::SetRect(const TRect& aRect)
{
	iFormat->iRect = aRect;
}

void CCtlColumn::SetViewRect(const TRect& aRect)
{
	iFormat->iViewRect = aRect;
}

CCtlModel* CCtlColumn::Clone()
{
	CCtlColumn* column = CCtlColumn::NewL();
	column->SetLayout(iLayout);
	
	CColumnFormat* oldFormat = column->Format();
	delete oldFormat;
	column->SetFormat(this->Format()->Clone());
	
	TInt i = 0;
	for (; i < iComponents->Count(); i++)
	{
		CCtlModel* result = (*iComponents)[i];
		CCtlModel* newModel = result->Clone();
		column->Add(newModel);
	}
	
	return column;
}

CCtlModel* CCtlColumn::Clone3D()
{
	CCtlColumn* column = CCtlColumn::NewL();
	column->SetLayout(iLayout);
	
	CColumnFormat* oldFormat = column->Format();
	delete oldFormat;
	column->SetFormat(this->Format()->Clone());
	
	TInt i = 0;
	for (; i < iComponents->Count(); i++)
	{
		CCtlModel* result = (*iComponents)[i];
		CCtlModel* newModel = result->Clone3D();
		column->Add(newModel);
	}
	
	return column;
}

TInt CCtlColumn::GetSelection(const TPoint& aPoint)
{
	TInt result = -1;
	TInt i = 0;
	TInt count = iComponents->Count();
	for (; i < count; i++)
	{
		TRect rowRect;
		iLayout->GetComponentRect(i,rowRect);
		if (rowRect.Contains(aPoint))
		{
			result = i;
			break;
		}
	}
	return result;
}

void CCtlColumn::SetSelection(TInt aIndex)
{
	iSelectedIndex = aIndex;
}

void CCtlColumn::DoSelect(CCtlModel* aSource,CWindowGc& gc,const TRect* aRect) const
{
}

TInt CCtlColumn::ComponentsCount()
{
	TInt result = 0;
	if (NULL != iComponents)
	{
		result = iComponents->Count();
	}
	return result;
}

TInt CCtlColumn::VisibleTopLine()
{
	TInt y = Format()->iViewRect.iTl.iY - Format()->iRect.iTl.iY - Format()->iTopMarginInPixels;
	TInt reallyRowHeight = Format()->iRowHeightInPixels + Format()->iRowSpacingInPixels;
	return y / reallyRowHeight;
}

TInt CCtlColumn::VisibleBottomLine()
{
	TInt y = Format()->iViewRect.iBr.iY - Format()->iRect.iTl.iY - Format()->iTopMarginInPixels;
	TInt reallyRowHeight = Format()->iRowHeightInPixels + Format()->iRowSpacingInPixels;
	TInt result = y / reallyRowHeight - 1;
	if (result > ComponentsCount() - 1)
	{
		result = ComponentsCount() - 1;
	}
		
	return result;
}

