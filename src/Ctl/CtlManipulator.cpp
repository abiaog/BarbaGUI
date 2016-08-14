#include "Ctl/CtlManipulator.h"

#include "Ctl/CtlColumn.h"
#include "Ctl/CtlRow.h"
#include "Ctl/CtlPicture.h"
//#include "AddLocationListCtl.h"
//#include "PreferenceListCtl.h"
#include "VideoListCtl.h"
//#include "CommonUtility.h"
#include "YKColumn.h"
#include "YKRow.h"

const TInt KSelectRadius = 5;

////////////////////////////////////////////////////////////////////////////////
///MCtlManipulator
////////////////////////////////////////////////////////////////////////////////
MCtlManipulator::MCtlManipulator()
: iIsActive(EFalse)
{}

////////////////////////////////////////////////////////////////////////////////
///CDragManipulator
////////////////////////////////////////////////////////////////////////////////
//CDragManipulator* CDragManipulator::NewL(CYKColumn* aModel, CPreferenceListCtl* aView)
//{
//	CDragManipulator* self = CDragManipulator::NewLC(aModel, aView);
//	CleanupStack::Pop( self );
//	return self;
//}
//
//CDragManipulator* CDragManipulator::NewLC(CYKColumn* aModel, CPreferenceListCtl* aView)
//{
//	CDragManipulator* self = new ( ELeave ) CDragManipulator(aModel, aView);
//	CleanupStack::PushL( self );
//	self->ConstructL();
//	return self;
//}
//
//void CDragManipulator::ConstructL()
//{
//	CActiveScheduler::Add(this);
//	User::LeaveIfError(iTimer.CreateLocal());
//}
//
//CDragManipulator::CDragManipulator(CYKColumn* aModel, CPreferenceListCtl* aView)
//: CActive(EPriorityStandard)
//, iRowModel(NULL)
//, iState(EReady)
//{
//	iModel = aModel;
//	iView = aView;
//}
//
//CDragManipulator::~CDragManipulator()
//{
//	if (NULL != iRowModel)
//	{
//		delete iRowModel;
//		iRowModel = NULL;
//	}
//	
//	Cancel();
//	iTimer.Close();
//}
//
//void CDragManipulator::HandlePointerEventL(const TPointerEvent& aPointerEvent)
//{	
//	if (TPointerEvent::EButton1Down == aPointerEvent.iType)
//	{
//		iIsActive = ETrue;
//		
//		iSourceIndex = iModel->GetSelection(aPointerEvent.iPosition);
//		iButton1DownY = aPointerEvent.iPosition.iY;
//		if (iSourceIndex >=0 && iSourceIndex < iModel->ComponentsCount())
//		{
//			if (NULL != iRowModel)
//			{
//				delete iRowModel;
//				iRowModel = NULL;
//			}
//			
//			iRowModel = iModel->At(iSourceIndex)->Clone3D();
//			iModel->At(iSourceIndex)->MakeVisible(EFalse);
//			
//			iDragPoint = aPointerEvent.iPosition;
//			StartExchange();
//		}
//		iView->DrawDeferred();		
//	}
//	else if (TPointerEvent::EButton1Up == aPointerEvent.iType)
//	{		
//		DoAdjust();
//		if (NULL != iRowModel)
//		{
//			delete iRowModel;
//			iRowModel = NULL;
//		}
//		
//		iView->DrawDeferred();
//		
//		Cancel();
//		iIsActive = EFalse;
//	}
//	else if (TPointerEvent::EDrag == aPointerEvent.iType)
//	{
//		TInt spaceY = aPointerEvent.iPosition.iY - iButton1DownY;
//		if (NULL != iRowModel)
//		{
//			TRect* rect = iRowModel->Rect();
//			rect->iTl.iY += spaceY;
//			rect->iBr.iY += spaceY;
//			iView->DrawDeferred();
//			iButton1DownY = aPointerEvent.iPosition.iY;
//		}	
//		
//		iDragPoint = aPointerEvent.iPosition;
//				
//		TInt curIndex = iModel->GetSelection(aPointerEvent.iPosition);
//		TInt count = iModel->ComponentsCount();
//		if (curIndex >=0 && curIndex < count)
//		{
//			if (iSourceIndex >= 0 && iSourceIndex < count)
//			{
//				if (curIndex != iSourceIndex) // exchange
//				{
//					CCtlModel* sourceModel = iModel->At(iSourceIndex);
//					CCtlModel* desModel = iModel->At(curIndex);
//					iModel->Remove(iSourceIndex);
//					iModel->Insert(desModel,iSourceIndex);
//					iModel->Remove(curIndex);
//					iModel->Insert(sourceModel,curIndex);
//					iView->DrawDeferred();
//					iSourceIndex = curIndex;
//				}
//			}
//		}		
//	}
//}
//
//void CDragManipulator::DoAdjust()
//{
//	const TInt KGraphicIndex = 1;
//	
//	if (NULL != iModel)
//	{
//		TInt count = iModel->ComponentsCount();
//		TInt i = 0;
//		for (; i < count; i++)
//		{
//			CCtlRow* row = static_cast<CCtlRow*>(iModel->At(i));
//			row->MakeVisible(ETrue);
//			CCtlGraphic* graphic = static_cast<CCtlGraphic*>(row->At(KGraphicIndex));
//			row->Remove(KGraphicIndex);
//			delete graphic;
//			graphic = NULL;
//			if (0 == i)
//			{
//				if (count > 1)
//				{
//					graphic = new (ELeave) CCtlGraphicHeader(KBrushColor,KLineColor);
//				}
//				else
//				{
//					graphic = new (ELeave) CCtlRoundRect(KBrushColor,KLineColor);
//				}
//			}
//			else if (count - 1 == i)
//			{
//				graphic = new (ELeave) CCtlGraphicTrail(KBrushColor,KLineColor);
//			}
//			else
//			{
//				graphic = new (ELeave) CCtlGraphicBody(KBrushColor,KLineColor);
//			}
//			row->Insert(graphic,KGraphicIndex);
//		}
//	}
//}
//
//void CDragManipulator::Draw(CWindowGc& gc) const
//{
//	if (NULL != iRowModel)
//	{
//		iRowModel->Draw(gc,iRowModel->Rect());
//	}
//}
//
//void CDragManipulator::StartExchange()
//{
//	Cancel();
//	iState = EReady;
//	iTimer.After(iStatus,1);
//	SetActive();
//}
//
//void CDragManipulator::RunL()
//{
//	TInt readyInterval = 1000;
//	
//	switch(iState)
//	{
//		case EReady:
//		{
//			TInt count = iModel->ComponentsCount();
//			TInt invisibleRowNumUnderBottom = iModel->InvisibleRowNumUnderBottom();
//			TInt invisibleRowNumAboveTop = iModel->InvisibleRowNumAboveTop();
//			if (invisibleRowNumUnderBottom > 0 && count - invisibleRowNumUnderBottom - 1 == iSourceIndex)
//			{
//				iState = EScrollUp;
//				iTimer.After(iStatus,1);
//				SetActive();
//			}
//			else if (invisibleRowNumAboveTop > 0 && invisibleRowNumAboveTop == iSourceIndex)
//			{
//				iState = EScrollDown;
//				iTimer.After(iStatus,1);
//				SetActive();
//			}
//			else
//			{
//				iState = EReady;
//				iTimer.After(iStatus,1000 * readyInterval);
//				SetActive();
//			}
//			break;
//		}
//		case EScrollUp:
//		{
//			TInt count = iModel->ComponentsCount();
//			TInt visibleBottomLine = count - iModel->InvisibleRowNumUnderBottom() - 1;
//			if (visibleBottomLine < count - 1)
//			{
//				iModel->MakeRowAtBottom(visibleBottomLine + 1);
//				iSourceIndex = visibleBottomLine;
//				iDesIndex = visibleBottomLine + 1;
//				TPointerEvent pointerEvent;
//				pointerEvent.iType = TPointerEvent::EDrag;
//				pointerEvent.iPosition = iDragPoint;
//				HandlePointerEventL(pointerEvent);
//			}
//			iState = EReady;
//			iTimer.After(iStatus,1000 * readyInterval);
//			SetActive();	
//
//			break;
//		}
//		case EScrollDown:
//		{
//			TInt visibleTopLine = iModel->InvisibleRowNumAboveTop();
//			if (visibleTopLine > 0)
//			{
//				iModel->MakeRowAtTop(visibleTopLine - 1);
//				iSourceIndex = visibleTopLine;
//				iDesIndex = visibleTopLine - 1;
//				TPointerEvent pointerEvent;
//				pointerEvent.iType = TPointerEvent::EDrag;
//				pointerEvent.iPosition = iDragPoint;
//				HandlePointerEventL(pointerEvent);
//			}
//			iState = EReady;
//			iTimer.After(iStatus,1000 * readyInterval);
//			SetActive();	
//			
//			break;
//		}
//		default:
//		{}
//	}
//}
//
//void CDragManipulator::DoCancel()
//{
//	iTimer.Cancel();
//	iState = EReady;
//}


////////////////////////////////////////////////////////////////////////////////
///CScrollManipulator
////////////////////////////////////////////////////////////////////////////////
CScrollManipulator::CScrollManipulator(CMWRow* aModel, CScrollBarCtl* aView)
{
	iModel = aModel;
	iView = aView;
	iCanMove = EFalse;
}

void CScrollManipulator::HandlePointerEventL(const TPointerEvent& aPointerEvent)
{
	if (TPointerEvent::EButton1Down == aPointerEvent.iType)
	{
		iIsActive = ETrue;
		
		iButton1DownY = aPointerEvent.iPosition.iY;
		
		if (NULL != iModel)
		{
			CMWRow* column = static_cast<CMWRow*>(iModel);
			iCanMove = column->CanDragUpDown();
		}
	}
	else if (TPointerEvent::EButton1Up == aPointerEvent.iType)
	{
		// phase3
//		CYKColumn* column = static_cast<CYKColumn*>(iModel);
//		column->MakeFullyVisible();
//		iView->DrawDeferred();
		
		iIsActive = EFalse;
	}
	else if (TPointerEvent::EDrag == aPointerEvent.iType)
	{
		if (iCanMove)
		{
			if (NULL != iModel)
			{
				TInt space = aPointerEvent.iPosition.iY - iButton1DownY;
				TRect* rect = iModel->Rect();
				
				CMWRow* column = static_cast<CMWRow*>(iModel);
				if (column->CanDragUpDown(space))
				{
					rect->iTl.iY += space;
					rect->iBr.iY += space;
					iView->DrawDeferred();
					iButton1DownY = aPointerEvent.iPosition.iY;
					
					MScrollBarCtlObserver* observer = iView->ScrollBarObserver();
					if (observer)
					{
						observer->HandleScrollBarCtlEventL(iView,MScrollBarCtlObserver::EScroll,space);
					}
				}
			}
		}
	}
}


////////////////////////////////////////////////////////////////////////////////
///CDelManipulator
////////////////////////////////////////////////////////////////////////////////
//CDelManipulator::CDelManipulator(CYKColumn* aModel, CPreferenceListCtl* aView)
//{
//	iModel = aModel;
//	iView = aView;
//}
//
//void CDelManipulator::HandlePointerEventL(const TPointerEvent& aPointerEvent)
//{
//	const TInt KDelIconIndex = 0;
//	const TInt KGraphicIndex = 1;
//	
//	if (TPointerEvent::EButton1Down == aPointerEvent.iType)
//	{
//		iIsActive = ETrue;
//		
//		TInt delIndex = iModel->GetSelection(aPointerEvent.iPosition);
//		TInt count = iModel->ComponentsCount();
//		if (delIndex >= 0 && delIndex < count)
//		{
//			CMWRow* delRow =  static_cast<CMWRow*>(iModel->At(delIndex));
//			delRow->SetSelectState(CListItem::ESelected);
//			iView->RefreshSelectState(delRow);
//			iView->DrawDeferred();
//		}
//	}
//	else if (TPointerEvent::EButton1Up == aPointerEvent.iType)
//	{
//		TInt delIndex = -1;
//		TInt count = iModel->ComponentsCount();
//		for (TInt i = 0; i < count; i++)
//		{
//			CMWRow* row = static_cast<CMWRow*>(iModel->At(i));
//			if (CListItem::ESelected == row->SelectState())
//			{
//				delIndex = i;
//				break;
//			}
//		}
//		
////		TInt delIndex = iModel->GetSelection(aPointerEvent.iPosition);
////		TInt count = iModel->ComponentsCount();
//		if (delIndex >= 0 && delIndex < count)
//		{
//			CMWRow* delRow =  static_cast<CMWRow*>(iModel->At(delIndex));
//			CCtlGraphic* delGraphic = static_cast<CCtlGraphic*>(delRow->At(KGraphicIndex));
//			
//			if (1 == count)
//			{
//
//			}
//			else if (2 == count)
//			{
//				CCtlRow* secondRow =  static_cast<CCtlRow*>(iModel->At((delIndex + 1) % 2));	
//				CCtlGraphic* secondGraphic = static_cast<CCtlGraphic*>(secondRow->At(KGraphicIndex));
//				secondRow->Remove(KGraphicIndex);
//				delete secondGraphic;
//				secondGraphic = NULL;
//				CCtlRoundRect* graphic = new (ELeave) CCtlRoundRect(KBrushColor,KLineColor);
//				secondRow->Insert(graphic,KGraphicIndex);
//			}
//			else if (2 < count)
//			{
//				if (0 == delIndex)
//				{
//					CCtlRow* secondRow =  static_cast<CCtlRow*>(iModel->At(1));
//					CCtlGraphic* secondGraphic = static_cast<CCtlGraphic*>(secondRow->At(KGraphicIndex));
//					
//					delRow->Remove(KGraphicIndex);
//					delRow->Insert(secondGraphic,KGraphicIndex);
//					
//					secondRow->Remove(KGraphicIndex);
//					secondRow->Insert(delGraphic,KGraphicIndex);
//				}
//				else if (count - 1 == delIndex)
//				{
//					CCtlRow* secondRow =  static_cast<CCtlRow*>(iModel->At(count - 2));
//					CCtlGraphic* secondGraphic = static_cast<CCtlGraphic*>(secondRow->At(KGraphicIndex));
//					
//					delRow->Remove(KGraphicIndex);
//					delRow->Insert(secondGraphic,KGraphicIndex);
//					
//					secondRow->Remove(KGraphicIndex);
//					secondRow->Insert(delGraphic,KGraphicIndex);
//				}
//			}
//			
//			delRow->SetSelectState(CListItem::EUnselected);
//			iView->RefreshSelectState(delRow);
//			
//			iModel->Remove(delIndex);
//			delete delRow;
//			delRow = NULL;
//			
//			if (iModel->VisibleRowNum() == 0)
//			{
//				iModel->MakeRowAtTop(0);
//			}
//			
//			iView->DrawDeferred();
//		}
//				
//		iIsActive = EFalse;
//	}
//	else if (TPointerEvent::EDrag == aPointerEvent.iType)
//	{
//		TInt count = iModel->ComponentsCount();
//		for (TInt i = 0; i < count; i++)
//		{
//			CMWRow* row = static_cast<CMWRow*>(iModel->At(i));
//			row->SetSelectState(CListItem::EUnselected);
//			iView->RefreshSelectState(row);
//		}
//		
//		TInt delIndex = iModel->GetSelection(aPointerEvent.iPosition);
//		if (delIndex >= 0 && delIndex < count)
//		{			
//			CMWRow* delRow =  static_cast<CMWRow*>(iModel->At(delIndex));
//			TInt componentIndex = delRow->GetSelection(aPointerEvent.iPosition);
//			if (KDelIconIndex == componentIndex)
//			{
//				delRow->SetSelectState(CListItem::ESelected);
//				iView->RefreshSelectState(delRow);
//			}
//		}
//		
//		iView->DrawDeferred();
//	}
//}
//
//
//////////////////////////////////////////////////////////////////////////////////
/////CMultiSelectManipulator
//////////////////////////////////////////////////////////////////////////////////
//CMultiSelectManipulator::CMultiSelectManipulator(CYKColumn* aModel, CAddLocationListCtl* aView)
//{
//	iModel = aModel;
//	iView = aView;
//}
//
//void CMultiSelectManipulator::HandlePointerEventL(const TPointerEvent& aPointerEvent)
//{
//	if (TPointerEvent::EButton1Up == aPointerEvent.iType)
//	{
//		TInt selIndex = iModel->GetSelection(aPointerEvent.iPosition);
//		TInt count = iModel->ComponentsCount();
//		if (selIndex >= 0 && selIndex < count)
//		{
//			CMWRow* row =  static_cast<CMWRow*>(iModel->At(selIndex));
//			iView->ReverseSelectState(row);
//			iView->DrawDeferred();
//		}
//	}
//}


////////////////////////////////////////////////////////////////////////////////
///CDeceleratedMotion
////////////////////////////////////////////////////////////////////////////////
CDeceleratedMotion* CDeceleratedMotion::NewL(CCtlColumn* aModel, CVideoListCtl* aView)
{
	CDeceleratedMotion* self = CDeceleratedMotion::NewLC(aModel,aView);
	CleanupStack::Pop(self);
	return self;
}

CDeceleratedMotion* CDeceleratedMotion::NewLC(CCtlColumn* aModel, CVideoListCtl* aView)
{
	CDeceleratedMotion* self = new ( ELeave ) CDeceleratedMotion(aModel,aView);
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
}

CDeceleratedMotion::CDeceleratedMotion(CCtlColumn* aModel, CVideoListCtl* aView)
: CActive(EPriorityStandard)
{
	iModel = aModel;
	iView = aView;
}

void CDeceleratedMotion::ConstructL()
{
	CActiveScheduler::Add( this );
	User::LeaveIfError(iTimer.CreateLocal());
}

CDeceleratedMotion::~CDeceleratedMotion() 
{
	Cancel();
//	Deque();
	iTimer.Close();
}

void CDeceleratedMotion::HandlePointerEventL(const TPointerEvent& aPointerEvent)
{
	
	if (TPointerEvent::EButton1Down == aPointerEvent.iType)
	{
		iIsActive = ETrue;
		
		iButton1DownY = aPointerEvent.iPosition.iY;
//		iButton1DownPoint = aPointerEvent.iPosition;
//		iIsMove = EFalse;
		
		TInt selectedIndex = iModel->GetSelection(aPointerEvent.iPosition);
		if (selectedIndex >=0 && selectedIndex < iModel->ComponentsCount())
		{
			iModel->SetSelection(selectedIndex);
			iView->DrawNow();
		}
		
		if (NULL != iModel)
		{
			CYKColumn* column = static_cast<CYKColumn*>(iModel);
			iCanMove = column->CanDragUpDown();
		}
	}
	else if (TPointerEvent::EButton1Up == aPointerEvent.iType)
	{
//		if (!iIsMove)
//		{
//			TInt selectedIndex = iModel->GetSelection(aPointerEvent.iPosition);
//			if (selectedIndex >=0 && selectedIndex < iModel->ComponentsCount())
//			{
//				iModel->SetSelection(selectedIndex);
//				DrawNow();
//				if (NULL != iObserver)
//				{
//					CMWRow* row = static_cast<CMWRow*>(iModel->At(selectedIndex));
//					iObserver->HandleListBoxEventL(this,MCtlListBoxObserver::EEventItemHighlighted,row->Id(),0);
//				}
//			}
//		}
		
		iIsActive = EFalse;
	}
	else if (TPointerEvent::EDrag == aPointerEvent.iType)
	{
		if (iCanMove)
		{
			if (NULL != iModel)
			{
				TInt space = aPointerEvent.iPosition.iY - iButton1DownY;
				TRect* rect = iModel->Rect();
				
				CYKColumn* column = static_cast<CYKColumn*>(iModel);
				if (column->CanDragUpDown(space))
				{
					rect->iTl.iY += space;
					rect->iBr.iY += space;
					iView->DrawDeferred();
					iButton1DownY = aPointerEvent.iPosition.iY;
				}
				
//				if (Distance(iButton1DownPoint,aPointerEvent.iPosition) > KSelectRadius)
//				{
//					iIsMove = ETrue;
//					iModel->SetSelection(CListItem::ENullId);
//					DrawNow();
//				}
			}
		}
	}
}

void CDeceleratedMotion::StartMove()
{
//	TInt64 interval = iUpTime.MicroSecondsFrom(iDownTime).Int64();
//	if (0 != interval)
//	{
//		TReal64 t = interval;
//		v = (iUpPoint.iY - iDownPoint.iY) / t;
//		a = (0 - v) / t;
//		t1 = 0;
//	}
	
//	iStep = 50;
	Cancel();
	iState= KReadyMove;
	iTimer.After( iStatus, 1 );
	SetActive();
}

void CDeceleratedMotion::SetDownPoint(const TPoint& aPoint)
{
	iDownPoint = aPoint;	
	iDownTime.HomeTime();
}

void CDeceleratedMotion::SetUpPoint(const TPoint& aPoint) 
{
	iUpPoint = aPoint;
	iUpTime.HomeTime();
}

// from CActive
void CDeceleratedMotion::RunL()
{
	switch ( iState )
	{
		case KReadyMove:
		{
			CYKColumn* column = static_cast<CYKColumn*>(iModel);
			TRect* rect = column->Rect();
			TRect desRect;
			if (iUpPoint.iY > iDownPoint.iY)
			{
				column->MakeRowAtTop(column->VisibleTopLine());
			}
			else
			{
				column->MakeRowAtBottom(column->VisibleBottomLine());
			}
			iView->DrawDeferred();
			iState = KMoved;
			iTimer.After( iStatus, 1 );
			SetActive();
			break;
			
			iStep = desRect.iTl.iY - rect->iTl.iY;
			if (iStep < 0)
			{
				iStep = -iStep;
			}
			
			iState = KMoving;
			iTimer.After( iStatus, 1 );
			SetActive();
			break;
		}
		case KMoving:
		{
//			CYKColumn* column = static_cast<CYKColumn*>(iModel);
//			column->MakeRowAtBottom(column->BottomLineInVisible());
//			iView->DrawDeferred();
//			iState = KMoved;
//			iTimer.After( iStatus, 1 );
//			SetActive();
			
			
			CYKColumn* column = static_cast<CYKColumn*>(iModel);
			TRect* rect = column->Rect();
			if (iStep <= 0)
			{
				iState = KMoved;
				iTimer.After( iStatus, 1);
				SetActive();
			}
			else
			{
				if (iUpPoint.iY > iDownPoint.iY)
				{
					rect->iTl.iY += 2;
					rect->iBr.iY += 2;
				}
				else
				{
					rect->iTl.iY -= 2;
					rect->iBr.iY -= 2;
				}
				iView->DrawDeferred();
				
				iStep -= 2;
				
				iTimer.After( iStatus, 1000 * 30 );
				SetActive();
			}
			
//			t1 += 1000 * 30;
//			TReal64 s = v * t1 + a * t1 * t1  / 2;
//			if (s > 0)
//			{
//				TRect* rect = iModel->Rect();
//				CYKColumn* column = static_cast<CYKColumn*>(iModel);
//				rect->iTl.iY += s;
//				rect->iBr.iY += s;
//				iView->DrawDeferred();
//				iTimer.After( iStatus, 1000 * 30 );
//				SetActive();
//			}
//			else
//			{
//				iState = KMoved;
//				iTimer.After( iStatus, 1);
//				SetActive();
//			}
			
			
//			if (iStep < 0)
//			{
//				iState = KMoved;
//				iTimer.After( iStatus, 1);
//				SetActive();
//			}
//			else
//			{
//				TRect* rect = iModel->Rect();
//				CYKColumn* column = static_cast<CYKColumn*>(iModel);
//				rect->iTl.iY += 1;
//				rect->iBr.iY += 1;
//				iView->DrawDeferred();
//			
//				iStep--;
//				
//				iTimer.After( iStatus, 1000 * 30 );
//				SetActive();
//			}			
			break;
		}
		case KMoved:
		{
			
			break;
		}
		default:
		{}
	}
}

void CDeceleratedMotion::DoCancel()
{
	iTimer.Cancel();
}

////////////////////////////////////////////////////////////////////////////////
///CItemSelector
////////////////////////////////////////////////////////////////////////////////
#include "ListCtlLayout.h"

CItemSelector* CItemSelector::NewL(CCtlColumn* aModel, CVideoListCtl* aView)
{
	CItemSelector* self = CItemSelector::NewLC(aModel,aView);
	CleanupStack::Pop(self);
	return self;
}

CItemSelector* CItemSelector::NewLC(CCtlColumn* aModel, CVideoListCtl* aView)
{
	CItemSelector* self = new ( ELeave ) CItemSelector(aModel,aView);
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
}


CItemSelector::CItemSelector(CCtlColumn* aModel, CVideoListCtl* aView)
: CActive(EPriorityStandard)
, iState(KNoSelect)
{
	iModel = aModel;
	iView = aView;
}

void CItemSelector::ConstructL()
{
	CActiveScheduler::Add( this );
	User::LeaveIfError(iTimer.CreateLocal());
}

CItemSelector::~CItemSelector() 
{
	Cancel();
//	Deque();
	iTimer.Close();
}

void CItemSelector::HandlePointerEventL(const TPointerEvent& aPointerEvent)
{
	if (TPointerEvent::EButton1Down == aPointerEvent.iType)
	{
		iIsActive = ETrue;
		
		if (iModel->Selection() == iModel->GetSelection(aPointerEvent.iPosition))
		{
			TInt index = iView->GetSelectedCtlIndex(aPointerEvent.iPosition);
			if (CVideoListRowSelectorLayout::EPlay == index) 
			{
				MCtlListBoxObserver* observer = iView->CCtlListBox::Observer();
				if (NULL != observer)
				{
					CMWRow* row = static_cast<CMWRow*>(iModel->At(iModel->Selection()));
					observer->HandleListBoxEventL(iView,MCtlListBoxObserver::EEventItemConfirmed,row->Id(),CVideoListRowSelectorLayout::EPlay);
				}
			}
		}
		else
		{
			SetDownPoint(aPointerEvent.iPosition);
			StartSelect();
		}
	}
	else if (TPointerEvent::EButton1Up == aPointerEvent.iType)
	{
		Cancel();
		iIsActive = EFalse;
	}
	else if (TPointerEvent::EDrag == aPointerEvent.iType)
	{
		
	}
}

void CItemSelector::StartSelect()
{
	Cancel();
	iState= KNoSelect;
	iTimer.After( iStatus, 1 );
	SetActive();
}
TInt CItemSelector::RunError(TInt aError)
{
	return 0;
}

// from CActive
void CItemSelector::RunL()
{
	switch ( iState )
	{
		case KNoSelect:
		{
			iState = KSelected;
			iTimer.After( iStatus, 1000 * 100 );
			SetActive();
			break;
		}
		case KSelected:
		{
//			if (!iView->IsMove()) // is select
//			{
				TInt selectedIndex = iModel->GetSelection(iDownPoint);
				if (selectedIndex >=0 && selectedIndex < iModel->ComponentsCount())
				{
					iModel->SetSelection(selectedIndex);
					iView->DrawNow();
					MCtlListBoxObserver* observer = iView->CCtlListBox::Observer();
					if (NULL != observer)
					{
						CMWRow* row = static_cast<CMWRow*>(iModel->At(selectedIndex));
						observer->HandleListBoxEventL(iView,MCtlListBoxObserver::EEventItemHighlighted,row->Id(),0);
					}
				}
//			}
			break;
		}
		default:
		{}
	}
}

void CItemSelector::DoCancel()
{
	iTimer.Cancel();
}




// phase2
////////////////////////////////////////////////////////////////////////////////
///CDragManipulator2
////////////////////////////////////////////////////////////////////////////////
//CDragManipulator2::CDragManipulator2(CCtlColumn* aModel, CPreferenceListCtl* aView)
//: iRowModel(NULL)
//{
//	iModel = aModel;
//	iView = aView;
//}
//
//CDragManipulator2::~CDragManipulator2()
//{
//	if (NULL != iRowModel)
//	{
//		delete iRowModel;
//		iRowModel = NULL;
//	}
//}
//
//void CDragManipulator2::HandlePointerEventL(const TPointerEvent& aPointerEvent)
//{
//	if (TPointerEvent::EButton1Down == aPointerEvent.iType)
//	{
//		iIsActive = ETrue;
//		
//		iSourceIndex = iModel->GetSelection(aPointerEvent.iPosition);
////			iButton1DownX = aPointerEvent.iPosition.iX;
//		iButton1DownY = aPointerEvent.iPosition.iY;
//		if (iSourceIndex >=0 && iSourceIndex < iModel->ComponentsCount())
//		{
//			if (NULL != iRowModel)
//			{
//				delete iRowModel;
//				iRowModel = NULL;
//			}
//			
//			iRowModel = iModel->At(iSourceIndex)->Clone3D();
//		}
//		iView->DrawDeferred();
//	}
//	else if (TPointerEvent::EButton1Up == aPointerEvent.iType)
//	{
//		if (NULL != iRowModel)
//		{
//			delete iRowModel;
//			iRowModel = NULL;
//		}
//		
//		iDesIndex = iModel->GetSelection(aPointerEvent.iPosition);
//		TInt count = iModel->ComponentsCount();
//		if (iSourceIndex >=0 && iSourceIndex < count)
//		{
//			if (iDesIndex >=0 && iDesIndex < count)
//			{
////				CCtlModel* sourceModel = iModel->At(iSourceIndex);
////				CCtlModel* desModel = iModel->At(iDesIndex);
////				iModel->Remove(iSourceIndex);
////				iModel->Insert(desModel,iSourceIndex);
////				iModel->Remove(iDesIndex);
////				iModel->Insert(sourceModel,iDesIndex);
////				DoAdjust(iSourceIndex,iDesIndex);
//				
//				if (iSourceIndex < iDesIndex)
//				{
//					CCtlModel* sourceModel = iModel->At(iSourceIndex);
//					iModel->Remove(iSourceIndex);
//					iModel->Insert(sourceModel,iDesIndex);
//					DoAdjust();
//				}
//				else if (iSourceIndex > iDesIndex)
//				{
//					CCtlModel* sourceModel = iModel->At(iSourceIndex);
//					iModel->Remove(iSourceIndex);
//					iModel->Insert(sourceModel,iDesIndex);
//					DoAdjust();
//				}
//			}
//		}
//		iView->DrawDeferred();
//		
//		iIsActive = EFalse;
//	}
//	else if (TPointerEvent::EDrag == aPointerEvent.iType)
//	{
//		TInt spaceX = aPointerEvent.iPosition.iX - iButton1DownX;
//		TInt spaceY = aPointerEvent.iPosition.iY - iButton1DownY;
//		if (NULL != iRowModel)
//		{
//			TRect* rect = iRowModel->Rect();
//			rect->iTl.iY += spaceY;
//			rect->iBr.iY += spaceY;
////				rect->iTl.iX += spaceX;
////				rect->iBr.iX += spaceX;
//			iView->DrawDeferred();
////				iButton1DownX = aPointerEvent.iPosition.iX;
//			iButton1DownY = aPointerEvent.iPosition.iY;
//		}				
//	}
//}
//
//void CDragManipulator2::DoAdjust(TInt aSrcIndex,TInt aDesIndex)
//{
//	if (NULL != iModel)
//	{
//		TInt graphicIndex = 1;
//		
//		CCtlRow* sourceModel = static_cast<CCtlRow*>(iModel->At(aSrcIndex));
//		CCtlRow* desModel = static_cast<CCtlRow*>(iModel->At(aDesIndex));
//		
//		CCtlGraphic* srcGraphic = static_cast<CCtlGraphic*>(sourceModel->At(graphicIndex));
//		CCtlGraphic* desGraphic = static_cast<CCtlGraphic*>(desModel->At(graphicIndex));
//		
//		sourceModel->Remove(graphicIndex);
//		sourceModel->Insert(desGraphic,graphicIndex);
//		
//		desModel->Remove(graphicIndex);
//		desModel->Insert(srcGraphic,graphicIndex);
//	}
//}
//
//void CDragManipulator2::DoAdjust()
//{
//	const TInt KGraphicIndex = 1;
//	
//	if (NULL != iModel)
//	{
//		TInt count = iModel->ComponentsCount();
//		TInt i = 0;
//		for (; i < count; i++)
//		{
//			CCtlRow* row = static_cast<CCtlRow*>(iModel->At(i));
//			CCtlGraphic* graphic = static_cast<CCtlGraphic*>(row->At(KGraphicIndex));
//			row->Remove(KGraphicIndex);
//			delete graphic;
//			graphic = NULL;
//			if (0 == i)
//			{
//				graphic = new (ELeave) CCtlGraphicHeader(KBrushColor,KLineColor);
//			}
//			else if (count - 1 == i)
//			{
//				graphic = new (ELeave) CCtlGraphicTrail(KBrushColor,KLineColor);
//			}
//			else
//			{
//				graphic = new (ELeave) CCtlGraphicBody(KBrushColor,KLineColor);
//			}
//			row->Insert(graphic,KGraphicIndex);
//		}
//	}
//}
//
//void CDragManipulator2::Draw(CWindowGc& gc) const
//{
//	if (NULL != iRowModel)
//	{
//		iRowModel->Draw(gc,iRowModel->Rect());
//	}
//}











