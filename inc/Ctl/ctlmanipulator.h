#ifndef CTLMANIPULATOR_H_
#define CTLMANIPULATOR_H_

#include <w32std.h>
#include <e32base.h>		// CActive

class CAddLocationListCtl;
class CVideoListCtl;
class CPreferenceListCtl;
class CCtlColumn;
class CCtlModel;
class CYKColumn;
class CMWRow;

const TRgb KBrushColor = TRgb(0xa49c74);
const TRgb KLineColor = TRgb(0xd7d7d7);

class MCtlManipulator
{
public:
	TBool IsActive() {return iIsActive;}
	MCtlManipulator();
	virtual ~MCtlManipulator() {}
	virtual void HandlePointerEventL(const TPointerEvent& aPointerEvent) {}
	virtual void Draw(CWindowGc& gc) const {}

protected:
	TBool iIsActive;
};

class CDragManipulator : public CActive
 					   , public MCtlManipulator
{
public:
	enum TScrollState
	{
		EReady,
		EScrollUp,
		EScrollDown,
	};
	
public:
	static CDragManipulator* NewL(CYKColumn* aModel, CPreferenceListCtl* aView);
	static CDragManipulator* NewLC(CYKColumn* aModel, CPreferenceListCtl* aView);
	
	void StartExchange();
	
	virtual ~CDragManipulator();
	virtual void HandlePointerEventL(const TPointerEvent& aPointerEvent);
	virtual void Draw(CWindowGc& gc) const;
	
private:
	// from CActive
	virtual void RunL();
	virtual void DoCancel();
	
	void DoAdjust();
	
	CDragManipulator(CYKColumn* aModel, CPreferenceListCtl* aView);
	void ConstructL();
	
private:
	CYKColumn* iModel;
	CPreferenceListCtl* iView;
	
	CCtlModel* iRowModel;
		
	TPoint iDragPoint;
	TInt iButton1DownY;
	TInt iSourceIndex;
	TInt iDesIndex;

	RTimer iTimer;
	TInt iState;
};

class MManipulatedView
{
public:
	virtual void DrawDeferred() const {}
	virtual void ReverseSelectState(CMWRow* /*aRow*/) {} // replace by RefreshSelectState? need check
	virtual void RefreshSelectState(CMWRow* aRow) {}
};

#include "ScrollBarCtl.h"
class CScrollManipulator : public CBase
 					     , public MCtlManipulator
{
public:
	CScrollManipulator(CMWRow* aModel, CScrollBarCtl* aView);
	virtual ~CScrollManipulator() {}
	virtual void HandlePointerEventL(const TPointerEvent& aPointerEvent);
	
private:
	CMWRow* iModel;
	CScrollBarCtl* iView;
	
	TInt iButton1DownY;
	TBool iCanMove;
};

class CDelManipulator : public CBase
 					   , public MCtlManipulator
{
public:
	CDelManipulator(CYKColumn* aModel, CPreferenceListCtl* aView);
	virtual ~CDelManipulator() {}
	virtual void HandlePointerEventL(const TPointerEvent& aPointerEvent);
	
private:
	CYKColumn* iModel;
	CPreferenceListCtl* iView;
};

class CMultiSelectManipulator : public CBase
 					   		  , public MCtlManipulator
{
public:
	CMultiSelectManipulator(CYKColumn* aModel, CAddLocationListCtl* aView);
	virtual ~CMultiSelectManipulator() {}
	virtual void HandlePointerEventL(const TPointerEvent& aPointerEvent);
	
private:
	CYKColumn* iModel;
	CAddLocationListCtl* iView;
};

class CDeceleratedMotion : public CActive
 					     , public MCtlManipulator
{
public:
	static CDeceleratedMotion* NewL(CCtlColumn* aModel, CVideoListCtl* aView);
	static CDeceleratedMotion* NewLC(CCtlColumn* aModel, CVideoListCtl* aView);
	
	virtual ~CDeceleratedMotion();
	virtual void HandlePointerEventL(const TPointerEvent& aPointerEvent);
	void StartMove();
	void SetDownPoint(const TPoint& aPoint);
	void SetUpPoint(const TPoint& aPoint);
	
protected:
	CDeceleratedMotion(CCtlColumn* aModel, CVideoListCtl* aView);
	void ConstructL();
	
	// from CActive
	virtual void RunL();
	virtual void DoCancel();
	
	enum TMotionState
	{
		KReadyMove,
		KMoving,
		KMoved,
		KRecovering,
		KRecovered
	};
	
private:
	
	
private:
	CCtlColumn* iModel;
	CVideoListCtl* iView;
	
	TInt iButton1DownY;
	TBool iCanMove;
	RTimer iTimer;
	TInt iState;
	
	TPoint iDownPoint;
	TPoint iUpPoint;
	TTime iDownTime;
	TTime iUpTime;
	TReal64 a;
	TReal64 v;
	TReal64 t1;
	
	TInt iStep;
};

class CItemSelector : public CActive
 					, public MCtlManipulator
{
public:
	static CItemSelector* NewL(CCtlColumn* aModel, CVideoListCtl* aView);
	static CItemSelector* NewLC(CCtlColumn* aModel, CVideoListCtl* aView);
	
	virtual ~CItemSelector();
	virtual void HandlePointerEventL(const TPointerEvent& aPointerEvent);
	
	void SetDownPoint(const TPoint& aPoint) {iDownPoint = aPoint;}
	void StartSelect();
	
protected:
	CItemSelector(CCtlColumn* aModel, CVideoListCtl* aView);
	void ConstructL();
	
	// from CActive
	virtual void RunL();
	virtual void DoCancel();
	TInt RunError(TInt aError);
	
	enum TSelectState
	{
		KNoSelect,
		KSelected
	};
	
private:
	CCtlColumn* iModel;
	CVideoListCtl* iView;
	
	TPoint iButton1DownPoint;
	RTimer iTimer;
	TInt iState;
	TPoint iDownPoint;
};




// phase2
class CDragManipulator2 : public CBase
 					    , public MCtlManipulator
{
public:
	CDragManipulator2(CCtlColumn* aModel, CPreferenceListCtl* aView);
	virtual ~CDragManipulator2();
	virtual void HandlePointerEventL(const TPointerEvent& aPointerEvent);
	virtual void Draw(CWindowGc& gc) const;
	
private:
	void DoAdjust(TInt aSrcIndex,TInt aDesIndex);
	void DoAdjust();
	
private:
	CCtlColumn* iModel;
	CPreferenceListCtl* iView;
	
	CCtlModel* iRowModel;
	
	TInt iButton1DownX;
	TInt iButton1DownY;
	TInt iSourceIndex;
	TInt iDesIndex;

};

#endif /*CTLMANIPULATOR_H_*/
