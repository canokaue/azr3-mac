#if !defined(AFX_AZEDITOR_H__FA58C980_466D_11D5_8ABF_0000B443497A__INCLUDED_)
#define AFX_AZEDITOR_H__FA58C980_466D_11D5_8ABF_0000B443497A__INCLUDED_

#include "audioeffectx.h"
//#include "AEffEditor.hpp"
#include "vstgui.h"
#include "flp.h"
#include "Controls.h"

#include "plugin-bindings/aeffguieditor.h"

enum
{
	cCOnOffButton=0,
	cCParamDisplay, 
	cCTextEdit,
	cCOptionMenu, 
	cCKnob,
	cCAnimKnob,
	cCVerticalSwitch,
	cCHorizontalSwitch,
	cCRockerSwitch,
	cCMovieBitmap,
	cCMovieButton,
	cCAutoAnimation,
	cCVerticalSlider,
	cCHorizontalSlider,
	cCSpecialDigit,
	cCKickButton,
	cCSplashScreen,
	cCVuMeter,
	cCFileSelector,
	cCDisplay,
	cCFader,
	cCCircDisplay,
	cCTab,
	cCTextSplash,

};


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Editor : public AEffGUIEditor, public CControlListener  
{
public:
	Editor (AudioEffect *effect);
	~Editor ();
	void idle();
protected:
	bool open (void *ptr);
	void close ();
	void setParameter (VstInt32 index, float value);
	void valueChanged (CControl* control);
	void c_visible(long tag,bool show);

private:
	int				panelmode;
	long			m1,m2,m3;
	long			oldTicks,ticks;
	int				panel_width,panel_height;
	bool			justloaded,frame_ok;
	int				mousedown;

	CBitmap*		bitmaps[kNumBitmaps];
	CControl*		controls[kNumControls];
	int				ctyp[kNumControls];
	CDisplay*		ctrl_display;
	COnOffButton*	ctrl_compare;
	COnOffButton*	ctrl_split;
	CKickButton*	ctrl_save;
	CSplashScreen*	ctrl_splash;
};




#endif // !defined(AFX_AZEDITOR_H__FA58C980_466D_11D5_8ABF_0000B443497A__INCLUDED_)

