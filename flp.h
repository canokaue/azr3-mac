#ifndef __flp_h__
#define __flp_h__

#ifndef __AudioEffectX__
#include "audioeffectx.h"
#endif

#include <stdio.h>
#include <string.h>
#include <math.h>

#include "voice_classes.h"
#include "fx.h"

#define	EVTBUFSIZE	1024	// number of events to memorize in buffer

enum
{
	evt_none=0,
	evt_noteon,
	evt_noteoff,
	evt_alloff,
	evt_pedal,
	evt_progchange,
	evt_pitch,
	evt_modulation,
	evt_volume,
	evt_channel_volume,
	evt_drawbar,
};

class flpProgram
{
friend class flp;
public:
	flpProgram() {};
	~flpProgram() {}
private:
	float	p[kNumParams];
	char name[24];
};

//------------------------------------------------------------------------------------------
class flp : public AudioEffectX
{
friend class MoogProgram;
public:
	flp(audioMasterCallback audioMaster);
	~flp();

	void process(float **inputs, float **outputs, VstInt32 sampleframes);
	void processReplacing(float **inputs, float **outputs, VstInt32 sampleframes);
	VstInt32 processEvents(VstEvents* events);

	void setProgram(VstInt32 program);
	void setProgram(VstInt32 program,bool force);
	void setProgramName(char *name);
	void getProgramName(char *name);
	VstInt32 getProgram();
	void setParameter(VstInt32 index, float value);
	void my_setParameter(long index, float value);
	float getParameter(VstInt32 index);
	void getParameterLabel(VstInt32 index, char *label);
	void getParameterDisplay(VstInt32 index, char *text);
	void getParameterName(VstInt32 index, char *text);
	void setSampleRate(float sampleRate);
	void resume();
	void suspend();

	bool getOutputProperties (VstInt32 index, VstPinProperties* properties);
	bool getProgramNameIndexed (VstInt32 category, VstInt32 index, char* text);
	bool copyProgram (VstInt32 destination);
	bool getEffectName (char* name);
	bool getVendorString (char* text);
	bool getProductString (char* text);
	VstInt32 getVendorVersion () {return 1;}
	VstInt32 canDo (char* text);

	void setFactorySounds();
	bool make_waveforms(int shape);
	void calc_waveforms(int number);
	void calc_click();
	void initall();
	void add_event(unsigned char type,VstInt32 delta,float value1,float value2,float value3);
	float* event_clock();

private:
	notemaster	*n1;
	bool	mute,fullyloaded;
	float	click[16];
	float	volume[16];
	float	mono_before;
	float	*out1,*out2;
	bool	compare,comparebuffer;
	float	samplerate;
	long	samplecount;
	bool	param_is_manual;
	bool	waitforsplit;
	long	splitpoint;

	float	p[kNumParams],*my_p,*virtual_my_p,actual_p[kNumParams],i_p[kNumParams];
	float	last_value[kNumParams];
	float	*p_mono,mono,mono1,mono2,VCA,l_before,r_before;
	long	setProgramDelayCount, actual_curProgram;
	
	flpProgram	programs[kNumPrograms];

	float tonewheel[WAVETABLESIZE];	// master waveform

	float sin_16[WAVETABLESIZE];
	float sin_8[WAVETABLESIZE];
	float sin_513[WAVETABLESIZE];
	float sin_4[WAVETABLESIZE];
	float sin_223[WAVETABLESIZE];
	float sin_2[WAVETABLESIZE];
	float sin_135[WAVETABLESIZE];
	float sin_113[WAVETABLESIZE];
	float sin_1[WAVETABLESIZE];

// TABLES_PER_CHANNEL tables per channel; 3 channels; 1 spare table
#define TABLES_PER_CHANNEL	8
	float wavetable[WAVETABLESIZE*TABLES_PER_CHANNEL*3+1];	

	lfo		vlfo;
	delay	*vdelay1,*vdelay2;
	float	viblfo;
	bool	vibchanged1,vibchanged2,lfo_calced;
	float	vmix1,vmix2;
	filt_lp	warmth;

	filt1	fuzz_filt,body_filt,postbody_filt;
	float	dist,sin_dist,i_dist,dist4,dist8;
	float	fuzz;
	bool	do_dist;
	bool	odchanged;
	float	odmix,n_odmix,n2_odmix,n25_odmix,odmix75;

	float	spread,spread2;
	float	cross1;
	bool	fastmode;
	float	lslow,lfast,uslow,ufast,lspeed,uspeed;
	float	ubelt_up,ubelt_down,lbelt_up,lbelt_down;
	float	er_r,er_r_before,er_l,er_feedback;
	float	lp,right,left,lright,lleft,upper,lower,upper_damp;
	float	llfo_out,llfo_nout,llfo_d_out,llfo_d_nout;
	float	lfo_out,lfo_nout,lfo_d_out,lfo_d_nout;
	float	last_out1,last_out2;
	bool	lfos_ok;
	filt1	split;
	filt1	horn_filt,damp;
	delay	*wand_r,*wand_l,*delay1,*delay2,*delay3,*delay4;
	lfo		lfo1,lfo2,lfo3,lfo4;

	float		gp_value;
	int			last_shape;
	float		last_r,last_l;
	float		*evt;
// stuff for event handling
	float		values[4],*ret;
	bool		has_events;
	int			event_pos,event_last_pos,event_next_pos,event_read_pos;
	long		delta[EVTBUFSIZE];
	unsigned char	events[EVTBUFSIZE];
	float		evalue1[EVTBUFSIZE];
	float		evalue2[EVTBUFSIZE];
	float		evalue3[EVTBUFSIZE];
	filt_allpass	allpass_l[4],allpass_r[4];
	float		lfo_phaser1,lfo_phaser2;

#ifdef DEVELOP
	float		ctrl1,ctrl2,ctrl3,ctrl4;
#endif

};

#endif
