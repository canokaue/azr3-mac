#include "Globals.h"
#ifndef __flp__
#include "flp.h"
#include "Editor.h"
#endif
#ifdef WIN32
#include <wtypes.h>
#endif

void flp::resume ()
{
	//wantEvents ();
	if(fullyloaded)
	{
		mute=false;
	}
}

void flp::suspend()
{
	int x;
	n1->suspend();
	mute=true;

/*
	mono_before=0;
	samplecount=0;
	mono=mono1=mono2=l_before=r_before=0;
	
	fuzz=odmix=0;
	dist=1;
	lp=right=left=lright=lleft=upper=lower=0;
	last_out1=last_out2=0;
	
	vmix1=0;
	vmix2=0;
*/
	for(x=0;x<4;x++)
	{
		allpass_r[x].reset();
		allpass_l[x].reset();
	}

	delay1->flood(0);
	delay2->flood(0);
	delay3->flood(0);
	delay4->flood(0);
	vdelay1->flood(0);
	vdelay2->flood(0);
	wand_r->flood(0);
	wand_l->flood(0);
	
	param_is_manual=false;
}

bool flp::make_waveforms(int shape)
{
	long	i;
	float	amp=.5f;
	float	tw=0,twfuzz;
	float	twmix=.5f;
	float	twdist=.7f;
	float	tws=(float)WAVETABLESIZE;
	
	
	if(shape==last_shape)
		return(false);
	last_shape=shape;
	/*
	We don't just produce flat sine curves but slightly distorted
	and even a triangle wave can be choosen.
	
	  Though this makes things sound more interesting it's _not_ a
	  tonewheel emulation. If we wanted that we would have to calculate
	  or otherwise define different waves for every playable note. If
	  anyone wants to implement real tonewheels you will have to make
	  drastic changes:
	  - implement many wavetables and a choosing algorithm
	  - construct wavetable data either through calculations
	  or from real wave files. Tha latter is what they do at
	  n@tive 1nstrument5.
	*/
	for(i=0;i<WAVETABLESIZE;i++)
	{
		float	ii=(float)i;
		
		if(shape==W_SINE1 || shape==W_SINE2 || shape==W_SINE3)
		{
			tw= amp *
				(
				sinf( ii*2*Pi/tws )
				+.03f*sinf( ii*8*Pi/tws )
				+.01f*sinf( ii*12*Pi/tws )
				);
			
			if(shape==W_SINE2)
				twdist=1;
			else if(shape==W_SINE3)
				twdist=2;
			
			tw*=twdist;
			twfuzz=2*tw-tw*tw*tw;
			if(twfuzz>1)
				twfuzz=1;
			else if(twfuzz<-1)
				twfuzz=-1;
			tonewheel[i]=.5f*twfuzz/twdist;
		}
		else if(shape==W_TRI)
		{
			if(i<int(tws/4) || i>int(tws*.75f))
				tw+=2/tws;
			else
				tw-=2/tws;
			tonewheel[i]=tw;
		}
		else if(shape==W_SAW)
		{
			tw=sinf(ii*Pi/tws);
			if(i>int(tws/2))
			{
				tw= sinf((ii-tws/2)*Pi/tws);
				tw=1-tw;
			}
			
			tonewheel[i]=tw-.5f;
		}
		else
		{
			tw= amp *
				(
				sinf( ii*2*Pi/tws )
				+.03f*sinf( ii*8*Pi/tws )
				+.01f*sinf( ii*12*Pi/tws )
				);
			tonewheel[i]=tw;
		}
	}
	
	for (i = 0; i < WAVETABLESIZE; i++)
	{
		//		int	f=TONEWHEELSIZE/WAVETABLESIZE;
		int f=1;
		int	icount;
		int i2[9];
		
		i2[0]=(int)(i*1*f);
		i2[1]=(int)(i*2*f);
		i2[2]=(int)(i*3*f);
		i2[3]=(int)(i*4*f);
		i2[4]=(int)(i*6*f);
		i2[5]=(int)(i*8*f);
		i2[6]=(int)(i*10*f);
		i2[7]=(int)(i*12*f);
		i2[8]=(int)(i*16*f);
		
		for(icount=0;icount<9;icount++)
		{
			while(i2[icount]>=WAVETABLESIZE)
				i2[icount]-=WAVETABLESIZE;
		}
		
		sin_16[i] = tonewheel[i2[0]];
		sin_8[i] = tonewheel[i2[1]];
		sin_513[i] = tonewheel[i2[2]];
		sin_4[i] = tonewheel[i2[3]];
		sin_223[i] = tonewheel[i2[4]];
		sin_2[i] = tonewheel[i2[5]];
		sin_135[i] = tonewheel[i2[6]];
		sin_113[i] = tonewheel[i2[7]];
		sin_1[i] = tonewheel[i2[8]];
	}
	
	return(true);
}

void flp::process (float **inputs, float **outputs, VstInt32 sampleFrames)
{
	// Do this hack only for VST instruments!!!
	processReplacing (inputs,outputs,sampleFrames);
}

void flp::processReplacing (float **inputs, float **outputs, VstInt32 sampleFrames)
{
/*
OK, here we go. This is the order of actions in here:
- process event queue
- return zeroes if in "mute" state
- clock the "notemaster" and get the combined sound output
from the voices.
We actually get three values, one for each keyboard.
They are added according to the assigned channel volume
control values.
- calculate switch smoothing to prevent clicks
- vibrato
- additional low pass "warmth"
- distortion
- speakers
	*/
	out1 = outputs[0];
	out2 = outputs[1];
	int	x;
	
	while (--sampleFrames >= 0)
	{
#ifdef DELAYED_PARAMS
		if(setProgramDelayCount>0)
		{
			setProgramDelayCount++;
			// here we confirm a requested program change
			if(setProgramDelayCount>4096)
			{
				setProgramDelayCount=-1;
				setProgram(curProgram);
			}
		}
#endif
		// we need this variable further down
		samplecount++;
		if(samplecount>10000)
		{
			samplecount=0;
			if (!fullyloaded)
				mute = false;

			fullyloaded=true;
		}
		
		// read events from our own event queue
		while((evt=this->event_clock())!=NULL)
		{
			int channel=(int)evt[3];
			float	*tbl = 0;
			
			// flash channel LEDs
			if(channel<=0)
				setParameter(n_1_midi,1);
			if(channel==1||channel<0)
				setParameter(n_2_midi,1);
			if(channel==2||channel<0)
				setParameter(n_3_midi,1);
			
			if(channel<0 || channel>2)
				channel=0;
			switch((unsigned char)evt[0])
			{
			case evt_noteon:
				{
					int		note=(int)evt[1];
					bool	percenable=false;
					float	sustain=my_p[n_sustain]+.0001f;
					
					// here we choose the correct wavetable according to the played note
#define foldstart 80
					if(note>foldstart+12+12)
						tbl=&wavetable[channel*WAVETABLESIZE*TABLES_PER_CHANNEL+WAVETABLESIZE*7];
					else if(note>foldstart+12+8)
						tbl=&wavetable[channel*WAVETABLESIZE*TABLES_PER_CHANNEL+WAVETABLESIZE*6];
					else if(note>foldstart+12+5)
						tbl=&wavetable[channel*WAVETABLESIZE*TABLES_PER_CHANNEL+WAVETABLESIZE*5];
					else if(note>foldstart+12)
						tbl=&wavetable[channel*WAVETABLESIZE*TABLES_PER_CHANNEL+WAVETABLESIZE*4];
					else if(note>foldstart+8)
						tbl=&wavetable[channel*WAVETABLESIZE*TABLES_PER_CHANNEL+WAVETABLESIZE*3];
					else if(note>foldstart+5)
						tbl=&wavetable[channel*WAVETABLESIZE*TABLES_PER_CHANNEL+WAVETABLESIZE*2];
					else if(note>foldstart)
						tbl=&wavetable[channel*WAVETABLESIZE*TABLES_PER_CHANNEL+WAVETABLESIZE];
					else
						tbl=&wavetable[channel*WAVETABLESIZE*TABLES_PER_CHANNEL];
					
					if(channel==0)
					{
						if(my_p[n_1_perc]>0)
							percenable=true;
						if(my_p[n_1_sustain]<.5f)
							sustain=0;
					}
					else if(channel==1)
					{
						if(my_p[n_2_perc]>0)
							percenable=true;
						if(my_p[n_2_sustain]<.5f)
							sustain=0;
					}
					else if(channel==2)
					{
						if(my_p[n_3_perc]>0)
							percenable=true;
						if(my_p[n_3_sustain]<.5f)
							sustain=0;
					}
					
					n1->note_on(note,
						(long) this->evt[2],
						tbl,WAVETABLESIZE,channel,percenable,click[channel],sustain);
				}
				break;
			case evt_noteoff:
				n1->note_off((long) evt[1],channel);
				break;
			case evt_alloff:
				n1->all_notes_off();
				break;
			case evt_pedal:
				n1->set_pedal((int) evt[1],channel);
				break;
			case evt_progchange:
				if(evt[1]<kNumPrograms && evt[1]!=curProgram)
				{
					param_is_manual=true;
					setProgram((long) evt[1]);
				}
				break;
			case evt_pitch:
				n1->set_pitch(evt[1],channel);
				break;
			case evt_modulation:
				param_is_manual=true;
				setParameterAutomated(n_speed,evt[1]);
				param_is_manual=false;
				break;
			case evt_volume:
				my_p[n_master]=evt[1];
				break;
			case evt_channel_volume:
				param_is_manual=true;
				setParameterAutomated(n_vol1+channel,evt[1]/127.0f);
				param_is_manual=false;
				break;
			case evt_drawbar:
				if(channel==2 && evt[1]>4)
					break;
				if(evt[1]<0 || evt[1]>8)
					break;
				if(evt[1]==1)
					evt[1]=2;
				else if(evt[1]==2)
					evt[1]=1;
				int offset=n_1_db1;
				if(channel==1)
					offset=n_2_db1;
				else if(channel==2)
					offset=n_3_db1;
				param_is_manual=true;
				setParameterAutomated(offset+(int)evt[1],evt[2]/127.0f);
				param_is_manual=false;
				break;
			}
		}
		
		p_mono=n1->clock();
		mono1=p_mono[0];
		mono2=p_mono[1];
		mono=p_mono[2];
		
		// smoothing of vibrato switch 1
		if(vibchanged1 && samplecount % 10 == 0)
		{
			if(my_p[n_1_vibrato]==1)
			{
				vmix1+=.01f;
				if(vmix1>=my_p[n_1_vmix])
					vibchanged1=false;
			}
			else
			{
				vmix1-=.01f;
				if(vmix1<=0)
					vibchanged1=false;
			}
		}
		
		// smoothing of vibrato switch 2
		if(vibchanged2 && samplecount % 10 == 0)
		{
			if(my_p[n_2_vibrato]==1)
			{
				vmix2+=.01f;
				if(vmix2>=my_p[n_2_vmix])
					vibchanged2=false;
			}
			else
			{
				vmix2-=.01f;
				if(vmix2<=0)
					vibchanged2=false;
			}
		}
		
		// smoothing of OD switch
		if(odchanged && samplecount % 10 == 0)
		{
			if(my_p[n_mrvalve]==1)
			{
				odmix+=.05f;
				if(odmix>=my_p[n_mix])
					odchanged=false;
			}
			else
			{
				odmix-=.05f;
				if(odmix<=0)
					odchanged=false;
			}
			n_odmix=1-odmix;
			n2_odmix=2-odmix;
			odmix75=.75f*odmix;
			n25_odmix=n_odmix*.25f;
		}
		
		// Vibrato LFO
		lfo_calced=false;
		
		// Vibrato 1
		if(my_p[n_1_vibrato]==1 || vibchanged1)
		{
			if(samplecount % 5 == 0)
			{
				viblfo=vlfo.clock();
				lfo_calced=true;
				vdelay1->set_delay(viblfo*2*my_p[n_1_vstrength]);
			}
			mono1=(1-vmix1)*mono1 + vmix1*vdelay1->clock(mono1);
		}
		
		// Vibrato 2
		if(my_p[n_2_vibrato]==1 || vibchanged2)
		{
			if(samplecount % 5 == 0)
			{
				if(!lfo_calced)
					viblfo=vlfo.clock();
				vdelay2->set_delay(viblfo*2*my_p[n_2_vstrength]);
			}
			mono2=(1-vmix2)*mono2 + vmix2*vdelay2->clock(mono2);
		}
		
		
		mono+=mono1+mono2;
		mono*=1.4f;
		
		// Mr. Valve
		/*
		Completely rebuilt.
		Multiband distortion:
		The first atan() waveshaper is applied to a lower band. The second
		one is applied to the whole spectrum as a clipping function (combined
		with an fabs() branch).
		The "warmth" filter is now applied _after_ distortion to flatten
		down distortion overtones. It's only applied with activated distortion
		effect, so we can switch warmth off and on without adding another parameter.
		*/
		if(my_p[n_mrvalve]!=0 || odchanged)
		{
			if(do_dist)
			{
				body_filt.clock(mono);
				postbody_filt.clock(atanf(body_filt.lp()*dist8)*6);
				fuzz=atanf(mono*dist4)*.25f+postbody_filt.bp()+postbody_filt.hp();

				if(_fabsf(mono)>my_p[n_set])
				{
					fuzz=atanf(fuzz*10);
				}
				fuzz_filt.clock(fuzz);
				mono=( ( fuzz_filt.lp()*odmix*sin_dist + mono*(n2_odmix) )*sin_dist)*i_dist;
			}
			else
			{
				fuzz_filt.clock(mono);
				mono=fuzz_filt.lp()*odmix75 + mono*n25_odmix*i_dist;
			}
			mono=warmth.clock(mono);			
		}
		
		// Speakers
		/*
		I started the rotating speaker sim from scratch with just
		a few sketches about how reality looks like:
		Two horn speakers, rotating in a circle. Combined panning
		between low and mid filtered sound and the volume. Add the
		doppler effect. Let the sound of one speaker get reflected
		by a wall and mixed with the other speakers' output. That's
		all not too hard to calculate and to implement in C++, and
		the results were already quite realistic. However, to get
		more density and the explicit "muddy" touch I added some
		phase shifting gags and some unexpected additions with
		the other channels' data. The result did take many nights
		of twiggling wih parameters. There are still some commented
		alternatives; feel free to experiment with the emulation.
		Never forget to mono check since there are so many phase
		effects in here you might end up in the void.
		I'm looking forward to the results...
		*/
		
		/*
		Update:
		I added some phase shifting using allpass filters.
		This should make it sound more realistic.
		*/
		
		if(my_p[n_speakers]!=0)
		{
			if(samplecount%100==0)
			{
				if(fastmode)
				{
					if(lspeed<lfast)
						lspeed+=lbelt_up;
					if(lspeed>lfast)
						lspeed=lfast;
					
					if(uspeed<ufast)
						uspeed+=ubelt_up;
					if(uspeed>ufast)
						uspeed=ufast;
				}
				else
				{
					if(lspeed>lslow)
						lspeed-=lbelt_down;
					if(lspeed<lslow)
						lspeed=lslow;
					if(uspeed>uslow)
						uspeed-=ubelt_down;
					if(uspeed<uslow)
						uspeed=uslow;
				}

				//recalculate mic positions when "spread" has changed
				if(!lfos_ok)
				{
					float s=(my_p[n_spread]+.5f)*.8f;
					spread=(s)*2+1;
					spread2=(1-spread)/2;
					lfo1.set_phase(0);
					lfo2.set_phase(s/2);
					lfo3.set_phase(0);
					lfo4.set_phase(s/2);
					cross1=1.5f-1.2f*s;
					// early reflections depend upon mic position.
					// we want less e/r if mics are positioned on
					// opposite side of speakers.
					// when positioned right in front of them e/r
					// brings back some livelyness.
					//
					// so "spread" does the following to the mic positions:
					// minimum: mics are almost at same position (mono) but
					// further away from cabinet.
					// maximum: mics are on opposite sides of cabinet and very
					// close to speakers.
					// medium: mics form a 90° angle, heading towards cabinet at
					// medium distance.
					er_feedback=.03f*cross1;
					lfos_ok=true;
				}
				
				if(lspeed != lfo3.get_rate())
				{
					lfo3.set_rate(lspeed*5,1);
					lfo4.set_rate(lspeed*5,1);
				}
				
				if(uspeed != lfo1.get_rate())
				{
					lfo1.set_rate(uspeed*5,1);
					lfo2.set_rate(uspeed*5,1);
				}
			}

			// split signal into upper and lower cabinet speakers
			split.clock(mono);
			lower=split.lp()*5;
			upper=split.hp();
			
			// upper speaker is kind of a nasty horn - this makes up
			// a major part of the typical sound!
			horn_filt.clock(upper);
			upper=upper*.5f+horn_filt.lp()*2.3f;
			damp.clock(upper);
			upper_damp=damp.lp();
			
			// do lfo stuff
			if(samplecount % 5 == 0)
			{
				lfo_d_out=lfo1.clock();
				lfo_d_nout=1-lfo_d_out;
				
				delay1->set_delay(10+lfo_d_out*.8f);
				delay2->set_delay(17+lfo_d_nout*.8f);
				
				lfo_d_nout=lfo2.clock();
				
				lfo_out=lfo_d_out*spread+spread2;
				lfo_nout=lfo_d_nout*spread+spread2;

				// phase shifting lines
				// (do you remember? A light bulb and some LDRs...
				//  DSPing is so much nicer than soldering...)
				lfo_phaser1=(1-cosf(lfo_d_out*1.8f)+1)*.054f;
				lfo_phaser2=(1-cosf(lfo_d_nout*1.8f)+1)*.054f;
				for(x=0;x<4;x++)
				{
					allpass_r[x].set_delay(lfo_phaser1);
					allpass_l[x].set_delay(lfo_phaser2);
				}

				if(lslow>0)
				{
					llfo_d_out=lfo3.clock();
					llfo_d_nout=1-llfo_d_out;
				}
				
				// additional delay lines in complex mode
				if(my_p[n_complex]>.5f)
				{
					delay4->set_delay(llfo_d_out+15);
					delay3->set_delay(llfo_d_nout+25);
				}
				
				llfo_d_nout=lfo4.clock();
				llfo_out=llfo_d_out*spread+spread2;
				llfo_nout=llfo_d_nout*spread+spread2;
			}
			
			if(lslow>0)
			{
				lright=(1+.6f*llfo_out)*lower;
				lleft=(1+.6f*llfo_nout)*lower;
			}
			else
			{
				lright=lleft=lower;
			}
			
			// emulate vertical horn characteristics
			// (sound is dampened when listened from aside)
			right=(3+lfo_nout*2.5f)*upper+1.5f*upper_damp;
			left=(3+lfo_out*2.5f)*upper+1.5f*upper_damp;

			//phaser...
			last_r=allpass_r[0].clock(
				allpass_r[1].clock(
				allpass_r[2].clock(
				allpass_r[3].clock(upper+last_r*.33f))));
			last_l=allpass_l[0].clock(
				allpass_l[1].clock(
				allpass_l[2].clock(
				allpass_l[3].clock(upper+last_l*.33f))));

			right+=last_r;
			left+=last_l;
			
			// rotating speakers can only develop in a live room -
			// wouldn't work without some early reflections.
			er_r=wand_r->clock(right+lright-(left*.3f)-er_l*er_feedback);
			er_r=DENORMALIZE(er_r);
			er_l=wand_l->clock(left+lleft-(right*.3f)-er_r_before*er_feedback);
			er_l=DENORMALIZE(er_l);
			er_r_before=er_r;
			

			// We use two additional delay lines in "complex" mode
			if(my_p[n_complex]>.5f)
			{
				right=right*.3f+1.5f*er_r+delay1->clock(right)+delay3->clock(er_r);
				left=left*.3f+1.5f*er_l+delay2->clock(left)+delay4->clock(er_l);
			}
			else
			{
				right=right*.3f+1.5f*er_r+delay1->clock(right)+lright;
				left=left*.3f+1.5f*er_l+delay2->clock(left)+lleft;
			}
			
			right*=.033f;
			left*=.033f;
			
			// spread crossover (emulates mic positions)
			last_out1=(left+cross1*right)*my_p[n_master];
			last_out2=(right+cross1*left)*my_p[n_master];
		}
		else
		{
			last_out1=last_out2=mono*my_p[n_master];
		}
		if(mute)
		{
			last_out1=0;
			last_out2=0;
		}

		(*out1++)=last_out1;
		(*out2++)=last_out2;
	}
	
}

VstInt32 flp::processEvents (VstEvents* ev)
{
/*
Fairly linear stuff. Differing from the SDK example:
The SDK	does not guarantee that all events arrive in correct order.
It's possible that a weird VST host sends a note off with a delta
of 500 followed by a note on with a delta of 100. If we process
the events in the order they arrive we would have a "hanging note"
with this example. So we want to do our own event handling and make
it sample accurate. Sample accuracy can only be provided inside the
process/processReplacing function. Now you know why. I have spoken.
	*/
	if(mute)
		return(0);
	for (long i = 0; i <ev->numEvents; i++)
	{
		if ((ev->events[i])->type != kVstMidiType)
			continue;
		VstMidiEvent* event = (VstMidiEvent*)ev->events[i];
		char* midiData = event->midiData;
		
		int status =midiData[0] & 0xf0;		// strip channel
		
		float channel=(float)(midiData[0] & 0x0f);		// strip command
		if(channel>2)
			channel=0;
		
		if (status == 0x90 || status == 0x80)	// notes
		{
			int note = midiData[1] & 0x7f;
			int velocity = midiData[2] & 0x7f;
			if (status == 0x80)
				velocity = 0;
			if (!velocity || status==0x80)
			{
				if(splitpoint>0 && channel==0 && note<=splitpoint)
					channel=2;
				add_event(evt_noteoff,event->deltaFrames,(float)note,(float)velocity,channel);
			}
			else
			{
				if(waitforsplit && note>0)
				{
					splitpoint=note;
					setParameterAutomated(n_splitpoint,float(note)/128.0f);
					if(editor)
						((AEffGUIEditor*)editor)->setParameter(n_split,float(note)/128.0f);
					waitforsplit=false;
				}
				else
				{
					if(splitpoint>0 && channel==0 && note<=splitpoint)
						channel=2;
					add_event(evt_noteon,event->deltaFrames,(float)note,(float)velocity,channel);
				}
			}
		}
		else if (status == 0xb0 && (midiData[1] == 0x78 
			|| midiData[1] == 0x79
			|| midiData[1] == 0x7a
			|| midiData[1] == 0x7b
			|| midiData[1] == 0x7c
			|| midiData[1] == 0x7d
			|| midiData[1] == 0x7e
			|| midiData[1] == 0x7f ))	// all notes off
		{
			add_event(evt_alloff,event->deltaFrames,0,0,-1);
		}
		else if (status == 0xb0 && midiData[1] == 0x07)	// main volume
		{
			add_event(evt_volume,event->deltaFrames,(float)midiData[2]/128,0,-1);
		}
		else if (status == 0xb0 && midiData[1] == 0x40)	// footswitch
		{
			float	mp=0;
			if(midiData[2]>64)
				mp=127;
			if(my_p[n_pedalspeed]<.5f)
			{
				add_event(evt_pedal,event->deltaFrames,mp,0,channel);
			}
			else
			{
				add_event(evt_modulation,event->deltaFrames,mp,0,-1);
			}
		}
#ifndef DEVELOP
		else if (status == 0xb0 && midiData[1] > 0x4a && midiData[1] < 0x54) // drawbar controllers
		{
		add_event(evt_drawbar,event->deltaFrames,(float)(midiData[1]-0x4b),(float)midiData[2],channel);
		}
#endif
		else if (status == 0xb0 && midiData[1] == 0x03) // channel volume
		{
			add_event(evt_channel_volume,event->deltaFrames,(float)midiData[2],0,channel);
		}
		else if (status == 0xb0 && midiData[1] == 0x01)	// Modulation wheel
		{
			// We had problems with many hosts:
			// Modulation was set to 0 during song start
			// So we don't use modulation as volume control anymore
			/*
			if(my_p[n_pedalspeed]<.5f)
			{
			*/
			if(midiData[2]<63)
				add_event(evt_modulation,event->deltaFrames,0,0,-1);
			else
				add_event(evt_modulation,event->deltaFrames,1,0,-1);
				/*
				}
				else
				add_event(evt_volume,event->deltaFrames,(float)midiData[2]/128,0,-1);
			*/
		}
		else if (status == 0xc0)	// Program Change
		{
			add_event(evt_progchange,event->deltaFrames,midiData[1],0,-1);
		}
#ifdef DEVELOP
		else if (status == 0xb0 && midiData[1] == 0x4a) // Ozone Ctrl 1
		{
			char t[100];
			ctrl1=((float)midiData[2])/127;
			sprintf(t,"ctrl1=%f ctrl2=%f ctrl3=%f ctrl4=%f\n",ctrl1,ctrl2,ctrl3,ctrl4);
			OutputDebugString(t);
		}
		else if (status == 0xb0 && midiData[1] == 0x47) // Ozone Ctrl 2
		{
			char t[100];
			ctrl2=((float)midiData[2])/127;
			sprintf(t,"ctrl1=%f ctrl2=%f ctrl3=%f ctrl4=%f\n",ctrl1,ctrl2,ctrl3,ctrl4);
			OutputDebugString(t);
		}
		else if (status == 0xb0 && midiData[1] == 0x51) // Ozone Ctrl 3
		{
			char t[100];
			ctrl3=((float)midiData[2])/127;
			sprintf(t,"ctrl1=%f ctrl2=%f ctrl3=%f ctrl4=%f\n",ctrl1,ctrl2,ctrl3,ctrl4);
			OutputDebugString(t);
		}
		else if (status == 0xb0 && midiData[1] == 0x5b) // Ozone Ctrl 4
		{
			char t[100];
			ctrl4=((float)midiData[2])/127;
			sprintf(t,"ctrl1=%f ctrl2=%f ctrl3=%f ctrl4=%f\n",ctrl1,ctrl2,ctrl3,ctrl4);
			OutputDebugString(t);
		}
#endif
		else if (status == 0xe0)	// pitch bend
		{
			float pitch=(float)(midiData[2]*128+midiData[1]);
			
			if(pitch>8192+600)
			{
				float p=pitch/8192 - 1;
				pitch=p*(float)pow(1.059463094359,int(12*my_p[n_bender]))+1-p;
			}
			else if(pitch<8192-600)
			{
				float p=(8192-pitch)/8192;
				pitch=1/(p*(float)pow(1.059463094359,int(12*my_p[n_bender]))+1-p);
			}
			else
				pitch=1;
			
			add_event(evt_pitch,event->deltaFrames,pitch,0,channel);
		}
		
		event++;
	}
	return 1;		// we want more events
}


void flp::add_event(unsigned char type,VstInt32 deltaframes,float value1,float value2,float value3)
{
	// a valid buffer entry is marked by a delta value >=0
	// to add an event we enter the values and set the pointer to the
	// next position which has to be empty
	
	has_events=true;
	
	// get last event
	event_last_pos=event_pos-1;
	if(event_last_pos<0)
		event_last_pos+=EVTBUFSIZE;
	
	event_next_pos=event_pos+1;
	if(event_next_pos>=EVTBUFSIZE)
		event_next_pos-=EVTBUFSIZE;
	
	if(delta[event_next_pos]>=0)	// event buffer is full
		return;
	
	
	if(delta[event_last_pos]>=0)	// there is an event before this one
	{
		if(deltaframes<delta[event_last_pos]) // error: event not in sequence
			delta[event_pos]=delta[event_last_pos]-deltaframes;	// delta difference
		else
			delta[event_pos]=deltaframes-delta[event_last_pos];	// delta difference
	}
	else
		delta[event_pos]=deltaframes;
	
	
	events[event_pos]=type;
	evalue1[event_pos]=value1;
	evalue2[event_pos]=value2;
	evalue3[event_pos]=value3;
	
	event_pos++;
	if(event_pos>=EVTBUFSIZE)
		event_pos-=EVTBUFSIZE;
}

float* flp::event_clock()
{
	if(!has_events)
		return(0);
	
	if(delta[event_read_pos]<0)	// there are no events in the buffer
	{
		has_events=false;
		return(NULL);
	}
	
	delta[event_read_pos]--;	// count delta frames (reset event if delta==0)
	
	if(delta[event_read_pos]<0)	// event is now
	{
		values[0]=(float)events[event_read_pos];
		values[1]=evalue1[event_read_pos];
		values[2]=evalue2[event_read_pos];
		values[3]=evalue3[event_read_pos];
		ret=values;
		event_read_pos++;
		if(event_read_pos>=EVTBUFSIZE)
			event_read_pos-=EVTBUFSIZE;
	}
	else
		ret=NULL;				// no event yet
	
	return(ret);
}
