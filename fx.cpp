/*
	This is a mixture of simple hacks and sophisticated effect algorithms.
	There's probably a lot of optimization potential in here...
*/
#include "FX.h"

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#ifdef WIN32
#include <wtypes.h>
#endif


delay::delay(int buflen, bool interpolate)
{
	float x=0;
	int	y;
	p_buflen=buflen;
	interp=interpolate;
	buffer=new float[p_buflen];
	for(y=0;y<p_buflen;y++)
		buffer[y]=0;
	lastIn=0;
	readp=0;
	writep=p_buflen>>1;
	offset = 0.1f;	//init me !
};


void delay::set_delay(float dtime)
{
	offset=dtime*samplerate*.001f;

	if(offset<0.1f)
		offset=0.1f;
	else if(offset>=p_buflen)
		offset=(float)p_buflen-1;

	outPointer=writep-offset;
	if(outPointer<0)
		outPointer+=p_buflen;
	
	readp=(int)outPointer;
	alpha=outPointer-readp;
	alpha2=alpha*alpha;
	alpha3=alpha2*alpha;
};

void delay::set_samplerate(float sr)
{
	//set_delay(1000*offset/samplerate);		// crash en puissance
	samplerate=sr;
	set_delay(1000*offset/samplerate);		// moved here (+offset init)
}

void delay::flood(float value)
{
	int x;
	for(x=0;x<p_buflen;x++)
		buffer[x]=value;
}

delay::~delay()
{
	delete[] buffer;
}

float delay::clock(float input)
{
	float	output=0;
	int		ym1p,y1p,y2p;
	if(p_buflen>4410)
	{
		return(0);
	}

	buffer[writep]=input;

	if(interp)
	{
		ym1p=readp-1;
		if(ym1p<0)
			ym1p+=p_buflen;
		y1p=readp+1;
		if(y1p>=p_buflen)
			y1p-=p_buflen;
		y2p=readp+2;
		if(y2p>=p_buflen)
			y2p-=p_buflen;
		
		
		ym1=buffer[ym1p];
		y0=buffer[readp];
		y1=buffer[y1p];
		y2=buffer[y2p];
		
		output=(alpha3*(y0-y1+y2-ym1)+
			alpha2*(-2*y0+y1-y2+2*ym1)+
			alpha*(y1-ym1)+y0);
	}
	else
		output=buffer[readp];

	writep++;
	if(writep>=p_buflen)
		writep-=p_buflen;
	readp++;
	if(readp>=p_buflen)
		readp-=p_buflen;

	return(output);
};

lfo::lfo()
{
	output=0;
	inc=0;
	dir=1;
	c=1;
	s=0;
}

void lfo::set_samplerate(float sr)
{
	samplerate=sr;
}

void lfo::set_rate(float srate,int type)
{
	my_srate=srate;
	my_type=type;
	if(type==0)
		inc=2.0f*PI*srate/samplerate;
	else
		inc=2*srate/samplerate;
	ci=cosf(inc);
	si=sinf(inc);
}

float lfo::get_rate()
{
	return(my_srate);
}

void lfo::set_phase(float phase)
{
	if(phase>=0 && phase <=1)
	{
		output=phase;
		s=phase;
	}
}

float lfo::clock()
{
	if(my_type==1)			// triangle wave
	{
		if(dir==1)
			output+=inc;
		else
			output-=inc;
		
		if(output>=1)
		{
			dir=-1;
			output=1;
		}
		else if(output<=0)
		{
			dir=1;
			output=0;
		}
	}
	else if(my_type==0)	// sine wave
	{
		nc=DENORMALIZE(c*ci-s*si);
		ns=DENORMALIZE(c*si+s*ci);
		c=nc;
		s=ns;
		output=(s+1)/2;
	}

	return(output);
}

filt1::filt1()
{
	m_l=m_h=m_b=m_f=q=0;
}

void filt1::clock(float input)
{
	float	in;
	in=DENORMALIZE(input);
	m_l=DENORMALIZE(m_l);
	m_b=DENORMALIZE(m_b);
	
	m_h = in - m_l - q*m_b;
	m_b += m_f*m_h;
	m_l += m_f*m_b;
}

float filt1::lp()
{
	return(m_l);
}

float filt1::bp()
{
	return(m_b);
}

float filt1::hp()
{
	return(m_h);
}

void filt1::set_samplerate(float samplerate)
{
	fs=samplerate;
	m_l=m_h=m_b=0;
	setparam(fc,q,fs);
}

void filt1::setparam(float cutoff,float mq,float samplerate)
{
	fc=cutoff;
	q=mq;
	fs=samplerate;
	m_f=2.0f*sinf(PI*fc/fs);
}

filt_lp::filt_lp() : filt1()
{
}

float filt_lp::clock(float input)
{
	float	in;
	in=DENORMALIZE(input);
	m_l=DENORMALIZE(m_l);
	m_b=DENORMALIZE(m_b);
	
	m_h = in - m_l - q*m_b;
	m_b += m_f*m_h;
	m_l += m_f*m_b;

	return(m_l);
}
