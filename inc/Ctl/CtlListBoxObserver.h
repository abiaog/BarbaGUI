#ifndef CTLLISTBOXOBSERVER_H_
#define CTLLISTBOXOBSERVER_H_

class CCtlListBox;

class MCtlListBoxObserver
	{
public:
    /**
    List box event codes.
	*/
	enum TCtlListBoxEvent
	    {
	    /**
	    This event is reported when an item is tapped, and denotes a user action
	    on an item. This event is reported somewhat differently for items having
	    a highlight layout and those that does not.
	     
	    When an item, having only a normal layout, is tapped on this event is
	    triggered.
	    
	    An item that has a highlight layout, needs to be highlighted and then
	    tapped for this event to be reported.
	    
	    The observer is allowed to change the state of the List Box and its 
	    components when receiving this event.
	    */
	    EEventItemTapped,
	    
	    /**
	    This event is reported when a item having a highlight layout but not
	    currently highlighted, is tapped. In this case a
	    <code>EEventHighlightMoved</code> event will be reported first,
	    followed by this event. Can be used as a way to distinguish between
	    pen or key cause of highlight moved.
	    
	    The observer is allowed to change the state of the List Box and its 
	    components when receiving this event.
	    */
	    EEventItemHighlighted,
	    
	    /** 
	    Item confirm event. When an item is selected using select soft key.
	     
	    The observer is allowed to change the state of the List Box and its 
	    components when receiving this event.
	    */			
	    EEventItemConfirmed,			

	    /** 
	    An item has been selected or deselected in a multiple slect enabled
	    List Box. If more then one item is affected the event will be reported
	    with index parameters having value EQikListBoxParamNotApplicable.
	    
	    The observer must not alter the state of any List Box components when
	    receiving this event.
	    */
	    EEventSelectionChanged,
	    	
	    /** 
	    The buffer that holds the characters that has currently been matched,
	    has changed.
	    
	    The observer must not alter the state of any List Box components when
	    receiving this event. 
	    */
	    EEventMatchBufferChanged,		

	    /** 
	    The top of the list has been reached. Event generated when standing on
	    top item and trying to go up.
	    
	    The observer must not alter the state of any List Box components when
	    receiving this event. 
	    */
	    EEventTopReached,
	    
	    /** 
	    The bottom of the list has been reached. Event generated when standing
	    on last item and trying to go down.
	    
	    The observer must not alter the state of any List Box components when
	    receiving this event.
	    */
	    EEventBottomReached,		

	    /** 
	    A tap in an empty List Box generates this event.
	    
	    The observer is allowed to change the state of the List Box and its 
	    components when receiving this event. 
	    */
	    EEventEmptyListBoxActioned,	

	    /** 
	    The highlight has moved. 
	    
	    The observer must not alter the state of any List Box components when
	    receiving this event.
	    */
	    EEventHighlightMoved,
	    
	    /** 
	    The index on the slot has changed.
	    
	    The observer must not alter the state of any List Box components when
	    receiving this event.
	    */
	    EEventSlotIndexChanged,
	    
	    /** 
	    An attempt to confirm a dimmed item has been made.
	    
	    The observer is allowed to change the state of the List Box and its 
	    components when receiving this event. 
	    */
	    EEventDimmedItemConfirmedAttempt,
	    
	    /**
	    The incremental match buffer is full, the maximum number of characters to match on
	    has been reached.
	    
	    The observer must not alter the state of any List Box components when
	    receiving this event. 
	    */
	    EEventMatchBufferFull,

	    /** 
	    Custom events section start.
	    
	    The observer must not alter the state of any List Box components when
	    receiving this event.
	    */
	    EEventCustomStart		= 0x1000
	    };

	/**
	Handles list box events.
	
	This pure virtual function is invoked by <code>CQikListBox</code> to
	notify the observer of list box events.
	
	The List Box observer must never alter the state of the List Box or any of
	its components while in between a MQikListBoxModel::ModelBeginUpdateLC
	and a MQikListBoxModel::ModelEndUpdateL call. Further more each event 
	either allows or forbids altering of the List Box and its components upon 
	receving the particular event, see <code>TQikListBoxEvent</code> for 
	further information on this.
	
	
	@param   aListBox	The originating list box.
	@param   aEventType	A code for the event. Further information may be obtained by accessing the list box itself.
	@param	aItemIndex	The item index, if applicable, else EQikListBoxParamNotApplicable.
	@param	aSlotId		The item slot id the event was generated in, if applicable, else EQikListBoxParamNotApplicable.
 	*/
	virtual void HandleListBoxEventL(CCtlListBox* aListBox, TCtlListBoxEvent aEventType, TInt aItemIndex, TInt aSlotId) = 0;
	};

#endif /*CTLLISTBOXOBSERVER_H_*/
