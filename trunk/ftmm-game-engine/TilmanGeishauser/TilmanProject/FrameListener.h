#ifndef __FrameEvent_h__
#define __FrameEvent_h__

/*struct FrameEvent
     {
         float timeSinceLastEvent;
         float timeSinceLastFrame;
     };
*/// Ogre stuff in case we want to implement


class FrameListener{
public:
	virtual bool frameStarted()
		  {  return true; };
	virtual bool frameEnded()
		  {  return true; };
};

#endif