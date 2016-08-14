#include "Ctl/CtlRow.h"

#include "Ctl/CtlLayout.h"
#include "YoukuLogger.h"

CCtlRow* CCtlRow::NewL()
{
	CCtlRow* self = CCtlRow::NewLC();
	CleanupStack::Pop( self );
	return self;
}

CCtlRow* CCtlRow::NewLC()
{
	CCtlRow* self = new ( ELeave ) CCtlRow( );
	CleanupStack::PushL( self );
	self->ConstructL();
	return self;
}

void CCtlRow::ConstructL()
{
	iComponents = new (ELeave) RPointerArray<CCtlModel>(10);
	iFormat = new (ELeave) CRowFormat;	
}

CCtlRow::CCtlRow()
: iComponents(NULL)
, iFormat(NULL)
, iLayout(NULL)
, iVisible(ETrue)
{
}

CCtlRow::~CCtlRow()
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

void CCtlRow::Add(CCtlModel* aHistoryModel)
{
	iComponents->Append(aHistoryModel);
}

void CCtlRow::Remove(TInt anIndex)
{
	iComponents->Remove(anIndex);
}

TInt CCtlRow::Insert(CCtlModel* aCtlModel, TInt aPos)
{
	return iComponents->Insert(aCtlModel,aPos);
}

void CCtlRow::Draw(CWindowGc& gc,const TRect* aRect) const
{
//	if (NULL != iGulIcon)
//	{
//		CFbsBitmap* bitmap = iGulIcon->Bitmap();
//		gc.DrawBitmap(*aRect,bitmap);
//	}
	
	iLayout->SetFormat(this->iFormat);
	iLayout->DoLayout(*aRect); 
	
//	gc.SetPenStyle(CGraphicsContext::ESolidPen);
//	gc.SetBrushStyle(CGraphicsContext::ENullBrush);
//	gc.SetPenColor(KRgbBlue);
//	gc.DrawRect(*aRect);
	
	TInt i = 0;
	TInt count = iComponents->Count();
//	DEBUG(LOG_UI, "count:%d",count);
	for (; i < count; i++)
	{
//		DEBUG(LOG_UI, "i:%d begin",i);
		CCtlModel* result = (*iComponents)[i];
		TRect componentRect;
		iLayout->GetComponentRect(i,componentRect);
		if (iVisible)
		{
			result->Draw(gc,&componentRect);
		}
//		DEBUG(LOG_UI, "i:%d end",i);
	}
}

void CCtlRow::MakeVisible(TBool aVisible)
{
	iVisible = aVisible;
}

CCtlModel* CCtlRow::At(TInt aIndex)
{
	CCtlModel* result = NULL;
	if (aIndex >=0 || aIndex < iComponents->Count())
	{
		result = (*iComponents)[aIndex];
	}
	return result;
}

void CCtlRow::Reset()
{
	if (NULL != iComponents)
	{
		iComponents->ResetAndDestroy();
	}
}

TRect* CCtlRow::Rect() const
{
	return &(iFormat->iRect);
}

void CCtlRow::SetRect(const TRect& aRect)
{
	iFormat->iRect = aRect;
}

void CCtlRow::SetViewRect(const TRect& aRect)
{
	iFormat->iViewRect = aRect;
}

const TRect& CCtlRow::ViewRect() const
{
	return iFormat->iViewRect;
}

CCtlModel* CCtlRow::Clone()
{
	CCtlRow* row = CCtlRow::NewL();
	row->SetLayout(iLayout);
	
	CRowFormat* oldFormat = row->Format();
	delete oldFormat;
	row->SetFormat(this->Format()->Clone());
	
	TInt i = 0;
	for (; i < iComponents->Count(); i++)
	{
		CCtlModel* result = (*iComponents)[i];
		CCtlModel* newModel = result->Clone();
		row->Add(newModel);
	}
	
	return row;
}

CCtlModel* CCtlRow::Clone3D()
{
	return Clone();
}

TInt CCtlRow::GetSelection(const TPoint& aPoint,TBool aIsTopFirst)
{
	iLayout->SetFormat(this->iFormat);
	TInt result = -1;
	TInt count = iComponents->Count();
	if (aIsTopFirst)
	{
		TInt i = count - 1;
		for (; i >= 0; i--)
		{
			TRect rect;
			iLayout->GetComponentRect(i,rect);
			if (rect.Contains(aPoint))
			{
				result = i;
				break;
			}
		}
	}
	else
	{
		TInt i = 0;
		for (; i < count; i++)
		{
			TRect rect;
			iLayout->GetComponentRect(i,rect);
			if (rect.Contains(aPoint))
			{
				result = i;
				break;
			}
		}
	}
	return result;
}

