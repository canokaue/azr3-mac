/*
	This is my "standard" controls library.

	CDisplay
		The program display (program number and name, boot message)

	CFader
		Drawbars

	CCircDisplay
		The knobs with integrated number display

	CTab
		Tabs to click on...
*/

#include "Controls.h"
#include "resource.h"

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>

CDisplay::CDisplay(CRect &size, CControlListener *listener, int tag, CBitmap *background) : CControl(size, listener, tag, background)
{
	my_listener=listener;
	my_tag=tag;
	bg=background;
	top=size.top;
	bottom=size.bottom;
	left=size.left;
	right=size.right;
	first=1;
	line1[0]=0;
	line2[0]=0;
	line3[0]=0;
	line4[0]=0;
	value=0;
	last_value=-2;
	linevalue=-1;
	my_drawcontext=NULL;
}

int32_t CDisplay::getTag() const
{
	return(my_tag);
}

void CDisplay::draw(CDrawContext *pContext)
{
    /*
	last_value=value;
	my_drawcontext=pContext;
	if(first==1)
	{
	//	oc=new COffscreenContext(getFrame(),right-left,bottom-top,kBlackCColor);
		first=0;
	}
	CRect rect(0,0,right-left,bottom-top);
	bg->draw(oc,rect,CPoint(left,top));
	oc->setFont(kNormalFontVerySmall);
	{
		CColor mc={255,236,200,0};
		oc->setFontColor(mc);
		oc->setLineWidth(1);
		oc->setFrameColor(mc);
		mc.red=126;
		mc.green=210;
		mc.blue=204;
		oc->setFillColor(mc);
	}
	oc->drawString(line1,CRect(2,0,right-left,10),false,kLeftText);
	oc->drawString(line2,CRect(2,10,right-left,10+10),false,kLeftText);
	oc->drawString(line3,CRect(2,20,right-left,20+10),false,kLeftText);
	oc->drawString(line4,CRect(2,30,right-left,30+10),false,kLeftText);
	if(linevalue>=0)
	{
		oc->drawRect(CRect(2,42,right-left-2,48));
		oc->fillRect(CRect(3,43,4+(int)((right-left-7)*linevalue),47));
	}
	oc->copyFrom(pContext,CRect(left,top,right,bottom),CPoint(0,0));
     */
    
    pContext->setFont(kNormalFontVerySmall);
    CRect rect(size.left, size.top-30, size.right, size.bottom);
    pContext->drawString(line1, rect, kLeftText);
    pContext->drawString(line2, CRect(size.left, size.top-10, size.right, size.bottom), kLeftText);
    pContext->drawString(line3, CRect(size.left, size.top+10, size.right, size.bottom), kLeftText);
    pContext->drawString(line4, CRect(size.left, size.top+30, size.right, size.bottom), kLeftText);
}

void CDisplay::setline(float value)
{
	linevalue=value;
	this->setDirty();
}

void CDisplay::setstring(int line, char *string)
{
	if(line==1)
		strncpy(line1,string,sizeof(line1));
	else if(line==2)
		strncpy(line2,string,sizeof(line2));
	else if(line==3)
		strncpy(line3,string,sizeof(line3));
	else if(line==4)
		strncpy(line4,string,sizeof(line4));
	this->setDirty();
}

void CDisplay::setValue(float value)
{
	this->value=value;
}

float CDisplay::getValue() const
{
	return(value);
}

CDisplay::~CDisplay()
{
//	if(oc!=NULL)
//		delete oc;
}

CFader::CFader(CRect &size, CControlListener *listener, int tag, CBitmap *bitmap, CBitmap *background, int handleheight) : CControl (size, listener, tag, background)
{
	my_listener=listener;
	first=1;
	top=size.top;
	left=size.left;
	bottom=size.bottom;
	right=size.right;
	width=bitmap->getWidth();
	height=bitmap->getHeight();
	my_tag=tag;
	my_bm=bitmap;
	my_bg=background;
	my_handleheight=handleheight;
	value=0;
	last_value=-2;
    m_xStart = 0;
    m_mouseDown = false;
}

int32_t CFader::getTag() const
{
	return(my_tag);
}

void CFader::draw(CDrawContext *pContext)
{
    /*
	last_value=value;
	int	pos=int((1-value)*(height-my_handleheight));
	if(first==1)
	{
		oc=new COffscreenContext(getFrame(),right-left,bottom-top,kBlackCColor);
		first=0;
	}

	CRect rect(0,0,width,height);
	my_bm->draw(oc,rect,CPoint(0,pos));
	rect(0,height-pos,width,height);
	my_bg->draw(oc,rect,CPoint(left,bottom-pos));
	rect(left,top,right,bottom);
	oc->copyFrom(pContext,rect,CPoint(0,0));
     */
    
    last_value=value;
    int	pos=int((1-value)*(height-my_handleheight));
    CRect rect(left,top,right,bottom);
    if (my_bm)
        my_bm->draw((pContext), rect, CPoint(0,pos));
}

CMouseEventResult CFader::onMouseDown (CPoint& where, const CButtonState& buttons)
{
    m_mouseDown = true;
    float pos = where.y - this->top;
    value = pos / (this->bottom - this->top);
    beginEdit();
    valueChanged();
    invalid();
    endEdit();
    
    return kMouseEventHandled;
}
//------------------------------------------------------------------------

CMouseEventResult CFader::onMouseMoved (CPoint& where, const CButtonState& buttons)
{
    if (!m_mouseDown)
        return kMouseEventHandled;
    
    float pos = where.y - this->top;
    value = pos / (this->bottom - this->top);
    
    if (value < 0)
        value = 0.f;
    if (value > 1)
        value = 1.f;
    
    beginEdit();
    valueChanged();
    invalid();
    endEdit();
    return kMouseEventHandled;
}
//------------------------------------------------------------------------

CMouseEventResult CFader::onMouseUp (CPoint& where, const CButtonState& buttons)
{
    invalid();
    m_mouseDown = false;
    return kMouseEventHandled;
}
//------------------------------------------------------------------------

void CFader::setValue(float value)
{
	this->value=value;
}

float CFader::getValue() const
{
	return(value);
}

CFader::~CFader()
{
//	if(oc!=NULL)
//		delete	oc;
}

CCircDisplay::CCircDisplay(CRect &size, CControlListener *listener, int tag, CBitmap *bitmap, CBitmap *digits, CBitmap *background) : CControl (size, listener, tag, background)
{
	my_listener=listener;
	first=1;
	stringConvert=NULL;
	top=size.top;
	left=size.left;
	width=bitmap->getWidth();
	totalheight=bitmap->getHeight();
	numofbm=int(totalheight/width);
	my_tag=tag;
	my_bm=bitmap;
	my_digits=digits;
	my_bg=background;
	digitwidth=digits->getWidth();
	digitheight=digits->getHeight()/12;
	value=0;
	last_value=-2;
    
    m_leftPosXClick = 0;
    m_mouseDown = false;
}

void CCircDisplay::setStringConvert (void (*convert) (float value, char *string))
{
	stringConvert = convert;
}

int32_t CCircDisplay::getTag() const
{
	return(my_tag);
}


void CCircDisplay::setValue(float value)
{
	this->value=value;
}

float CCircDisplay::getValue() const
{
	return(value);
}

CCircDisplay::~CCircDisplay()
{
//	if(oc!=NULL)
//		delete	oc;
}

void CCircDisplay::draw(CDrawContext *pContext)
{
    /*
	char	t[16];
	unsigned int		x;
	int					y=0,z;
	if(first==1)
	{
		oc=new COffscreenContext(getFrame(),width,width,kBlackCColor);
		first=0;
	}
	
	last_value=value;

	if(stringConvert)
		stringConvert(value,t);
	else
		sprintf(t,"%3d%",int(100*value+.001f));

	CRect rect(0,0,width,width);
	my_bg->draw(oc,rect,CPoint(left,top));
	my_bm->drawTransparent(oc,rect,CPoint(0,int(value*(numofbm-1))*width));

	for(x=0;x<strlen(t);x++)
	{
		if(t[x]=='.')
		{
			int a;
			if(y>=digitwidth)
				a=y-digitwidth;
			rect(12+a,19,12+a+digitwidth,19+digitheight);
			my_digits->drawTransparent(oc,rect,CPoint(0,10*digitheight));
			continue;
		}
		else if(t[x]==' ')
		{
			y+=digitwidth;
			continue;
		}
		else if(t[x]=='%')
			z=11*digitheight;
		else if(!isdigit(t[x]))
			continue;
		else
			z=digitheight*(t[x]-'0');

		rect(12+y,18,12+y+digitwidth,18+digitheight);
		my_digits->drawTransparent(oc,rect,CPoint(0,z));
		y+=digitwidth;
	}
	oc->copyFrom(pContext,CRect(left,top,left+width,top+width),CPoint(0,0));
     
     */
    
    char	t[16];
	unsigned int		x;
	int					y=0,z;
	
	last_value=value;
    
	if(stringConvert)
		stringConvert(value,t);
	else
		sprintf(t,"%3d%",int(100*value+.001f));
    
	//CRect rect(0,0,width,width);
    CRect rect(left,top,size.right,size.bottom);
	my_bg->draw(pContext,rect,CPoint(left,top));
	my_bm->draw(pContext,rect,CPoint(0,int(value*(numofbm-1))*width), 0.3f);
    
    pContext->setFont(kNormalFontVerySmall);
    pContext->drawString(t,rect);
}

CMouseEventResult CCircDisplay::onMouseDown (CPoint& where, const CButtonState& buttons)
{
    m_mouseDown = true;
    float pos = where.y - this->top;
    m_leftPosXClick = pos;
    beginEdit();
    valueChanged();
    invalid();
    endEdit();
    
    return kMouseEventHandled;
}
//------------------------------------------------------------------------

CMouseEventResult CCircDisplay::onMouseMoved (CPoint& where, const CButtonState& buttons)
{
    if (!m_mouseDown)
        return kMouseEventHandled;
    
    float pos = where.y - this->top;
    float offset= m_leftPosXClick - pos;
    
    if(offset < 0)
        value -= 0.02f;
    if (offset>0)
        value += 0.02f;
    
    if (value < 0)
        value = 0.f;
    if (value > 1)
        value = 1.f;
    
    beginEdit();
    valueChanged();
    invalid();
    endEdit();
    
    m_leftPosXClick = pos;
    
    return kMouseEventHandled;
}
//------------------------------------------------------------------------

CMouseEventResult CCircDisplay::onMouseUp (CPoint& where, const CButtonState& buttons)
{
    invalid();
    m_mouseDown = false;
    return kMouseEventHandled;
}
//------------------------------------------------------------------------

CTextSplash::CTextSplash(CRect &size,CControlListener *listener, int tag, CBitmap *background, CRect   &toDisplay, CPoint  &offset) : CSplashScreen(size,listener,tag,background,toDisplay,offset)
{
}

void CTextSplash::draw(CDrawContext *pContext)
{
	if (value && getBackground())
	{
		getBackground()->draw (pContext, toDisplay, offset);
		pContext->setFont(kNormalFontSmaller);
		{
			int	x;
			CColor mc={0,0,0,0};
			pContext->setFontColor(mc);

			for(x=0;x<100;x++)
			{
				pContext->drawString(text[x],CRect(size.left+158, size.top+x*10, size.right+250, size.bottom+10+x*10),kLeftText);
			}
		}
	}
}

CTab::CTab(CRect &size,CControlListener *listener,int tag,CBitmap *bm) : CControl(size, listener, tag, bm)
{
}

CTab::~CTab()
{
}

void CTab::draw(CDrawContext *pContext)
{
}

CMouseEventResult CTab::onMouseDown (CPoint& where, const CButtonState& buttons)
{
    beginEdit();
    VSTGUIEditorInterface * editor = getEditor();
    setValue(1);    
    valueChanged();
    invalid();
    endEdit();
    
    return kMouseEventHandled;
}
