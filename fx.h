#ifndef __FX_h__
#define __FX_h__

#define DENORMALIZE(fv) (fv<.00000001f && fv>-.00000001f)?0:(fv)
#define	PI	3.14159265358979323846f

class delay		// non-interpolating delay
{
public:
	delay(int buflen, bool interpolate);
	~delay();
	void	set_delay(float dtime);
	void	set_samplerate(float samplerate);
	void	flood(float value);
	float	clock(float input);
	void	report();
protected:
	float	*buffer;
	int		p_buflen;
	bool	interp;
	float	offset;
	float	samplerate;
	int		readp,readp2,writep;

	float	outPointer;
	float	alpha,alpha2,alpha3,omAlpha,coeff,lag,lastIn;
	float	ym1;
	float	y0;
	float	y1;
	float	y2;
};

class lfo
{
public:
	lfo();
	~lfo(){};
	float clock();
	void	set_samplerate(float samplerate);
	void	set_rate(float srate,int type);	// Hz; type: 0=sin, 1=tri
	void	set_phase(float phase);
	float	get_rate();
private:
	int		my_type;
	float	output;
	float	samplerate;
	float	inc;
	int		dir;
	float	c,s,ci,si,nc,ns;
	float	my_srate;
};

class filt1
{
	friend class filt_lp;
public:
	filt1();
	~filt1(){};
	float	lp();
	float	bp();
	float	hp();
	void	clock(float input);
	void	setparam(float cutoff, float q, float samplerate);
	void	set_samplerate(float samplerate);
private:
	float	fs;		// sampling freq
	float	fc;		// cutoff freq
	float	q;		// resonance
	float	m_f;		//,m_q,m_qnrm;	
	float	m_h;	// hp out
	float	m_b;	// bp out
	float	m_l;	// lp out
};

class filt_lp : public filt1
{
public:
	filt_lp();
	float	clock(float input);
};

class	filt_allpass
{
public:
	filt_allpass() : a1(0.f), zm1(0.f)
	{
		a1=zm1=my_delay=y=0;
	}

	void	reset()
	{
		a1=zm1=y=0;
		set_delay(my_delay);
	}

	void	set_delay(float delay)
	{
		my_delay=delay;
		a1=(1-delay)/(1+delay);
		a1=DENORMALIZE(a1);
	}

	float	clock(float input)
	{
		if(input<.00000001f && input>-.00000001f)	// prevent Pentium FPU Normalizing
			return(0);

		y=-a1*input + zm1;
		zm1=y*a1+input;
		return(y);
	}
private:
	float	a1,zm1,my_delay,y;
};

#endif