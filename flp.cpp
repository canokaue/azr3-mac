#include "Globals.h"
#ifndef __VstXSynth__
#include "flp.h"
#endif
#include "Editor.h"

#ifdef WIN32
#include <wtypes.h>
#endif

#include <stdio.h>

extern void convert_bendrange (float value, char*string);
extern void convert_tone (float value, char*string);
extern void convert_speed (float value, char*string);
extern void convert_perc (float value, char*string);
extern void convert_shape (float value, char*string); 

AudioEffect* createEffectInstance (audioMasterCallback audioMaster)
{
	return new flp(audioMaster);
}

/*
	OK, this "factory sound" stuff looks weird,
	but it works just perfect. I wrote a mini tool
	which analyzes a Cubase program bank file and
	writes just these lines. This makes it very easy
	to implement "factory sounds".
*/
void flp::setFactorySounds()
{
	int x=0;
// 32 programs, ID=FLP5
	{
		float mp[kNumParams]=
		{
			0.0000f,
			0.9300f,
			0.2000f,
			0.4800f,
			0.4300f,
			0.3300f,
			0.5000f,
			0.6000f,
			0.6000f,
			0.3400f,
			0.3000f,
			1.0000f,
			0.6500f,
			0.0000f,
			1.0000f,
			0.1900f,
			0.5400f,
			0.0000f,
			0.2300f,
			0.1500f,
			0.0000f,
			0.0000f,
			0.3000f,
			0.3500f,
			1.0000f,
			1.0000f,
			0.2100f,
			0.3400f,
			0.3700f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.3010f,
			0.3510f,
			0.0000f,
			1.0000f,
			0.5900f,
			0.9400f,
			0.0000f,
			0.0000f,
			1.0000f,
			0.4400f,
			1.0000f,
			0.2700f,
			0.1800f,
			1.0000f,
			0.0000f,
			0.0900f,
			0.4800f,
			0.0470f,
			0.6500f,
			0.5000f,
			0.4200f,
			1.0000f,
			1.0000f,
			0.4609f,
			0.6700f,
			0.0000f,
			0.0000f,
			1.0000f,
		};
		memcpy(programs[x].p,mp,sizeof(mp));
		strcpy(programs[x++].name,"muddy moods SPLIT");
	}

	{
		float mp[kNumParams]=
		{
			0.0000f,
			0.5200f,
			0.2000f,
			0.4000f,
			0.5000f,
			1.0000f,
			0.5000f,
			0.6000f,
			0.6000f,
			0.7900f,
			0.2300f,
			1.0000f,
			1.0000f,
			1.0000f,
			1.0000f,
			1.0000f,
			1.0000f,
			1.0000f,
			1.0000f,
			1.0000f,
			1.0000f,
			1.0000f,
			0.3000f,
			0.3500f,
			1.0000f,
			1.0000f,
			0.2100f,
			0.3400f,
			0.3700f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.3010f,
			0.3510f,
			0.0000f,
			1.0000f,
			0.2100f,
			0.6700f,
			0.0900f,
			0.0000f,
			0.0000f,
			0.0000f,
			1.0000f,
			0.5000f,
			1.0000f,
			1.0000f,
			0.0000f,
			0.0400f,
			0.4700f,
			0.0500f,
			0.6800f,
			0.5000f,
			0.5100f,
			1.0000f,
			1.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
		};
		memcpy(programs[x].p,mp,sizeof(mp));
		strcpy(programs[x++].name,"Volle Kante");
	}

	{
		float mp[kNumParams]=
		{
			0.0000f,
			0.2200f,
			0.2000f,
			0.3000f,
			0.0000f,
			0.1000f,
			0.5000f,
			0.3700f,
			0.6000f,
			0.6600f,
			0.3900f,
			1.0000f,
			1.0000f,
			0.8800f,
			0.0000f,
			0.5700f,
			0.0000f,
			0.5500f,
			0.0000f,
			0.5100f,
			0.4600f,
			0.0000f,
			0.3000f,
			0.3500f,
			0.0000f,
			1.0000f,
			0.2100f,
			0.3400f,
			0.3700f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.3010f,
			0.3510f,
			0.0000f,
			1.0000f,
			0.3600f,
			0.4500f,
			0.0900f,
			0.0000f,
			0.0000f,
			0.4400f,
			1.0000f,
			0.1000f,
			0.2500f,
			1.0000f,
			0.0000f,
			0.0900f,
			0.4700f,
			0.0470f,
			0.6600f,
			0.4200f,
			0.3200f,
			1.0000f,
			1.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
		};
		memcpy(programs[x].p,mp,sizeof(mp));
		strcpy(programs[x++].name,"clean");
	}

	{
		float mp[kNumParams]=
		{
			0.0000f,
			0.5100f,
			0.2000f,
			0.0000f,
			0.7500f,
			0.2700f,
			1.0000f,
			0.3400f,
			0.6000f,
			0.3100f,
			0.5400f,
			1.0000f,
			1.0000f,
			0.0000f,
			0.0000f,
			0.0900f,
			0.4800f,
			0.0000f,
			0.3700f,
			0.1700f,
			0.0000f,
			0.0000f,
			0.3000f,
			0.3500f,
			1.0000f,
			1.0000f,
			0.2100f,
			0.3400f,
			0.3700f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.3010f,
			0.3510f,
			0.0000f,
			1.0000f,
			0.6300f,
			0.4100f,
			0.4400f,
			0.0000f,
			1.0000f,
			0.5600f,
			1.0000f,
			1.0000f,
			0.0000f,
			1.0000f,
			0.0000f,
			0.0400f,
			0.6000f,
			0.0770f,
			0.7300f,
			1.0000f,
			0.6400f,
			0.0000f,
			1.0000f,
			0.4609f,
			0.0000f,
			0.0000f,
			0.0000f,
			1.0000f,
		};
		memcpy(programs[x].p,mp,sizeof(mp));
		strcpy(programs[x++].name,"hollow SPLIT");
	}

	{
		float mp[kNumParams]=
		{
			0.0000f,
			0.2000f,
			0.2000f,
			0.3000f,
			0.3400f,
			0.3700f,
			1.0000f,
			0.6900f,
			0.6000f,
			0.0000f,
			0.5400f,
			1.0000f,
			0.2200f,
			1.0000f,
			0.0000f,
			0.0200f,
			0.0800f,
			0.0000f,
			0.2300f,
			0.1500f,
			0.1800f,
			1.0000f,
			0.3000f,
			0.3500f,
			1.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.2500f,
			0.4400f,
			1.0000f,
			0.0000f,
			0.0600f,
			0.5300f,
			0.0400f,
			0.7500f,
			0.5000f,
			0.1900f,
			1.0000f,
			1.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
		};
		memcpy(programs[x].p,mp,sizeof(mp));
		strcpy(programs[x++].name,"talking space");
	}

	{
		float mp[kNumParams]=
		{
			0.0000f,
			1.0000f,
			0.2000f,
			0.0000f,
			0.3600f,
			0.3900f,
			0.9700f,
			0.5300f,
			0.6000f,
			0.3400f,
			0.2100f,
			1.0000f,
			1.0000f,
			0.7800f,
			0.0000f,
			0.6500f,
			0.0000f,
			0.4961f,
			0.2300f,
			0.1200f,
			0.0000f,
			0.0000f,
			0.3000f,
			0.3500f,
			1.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			1.0000f,
			0.6400f,
			0.4900f,
			0.0000f,
			0.0000f,
			1.0000f,
			0.3100f,
			1.0000f,
			0.4500f,
			0.2700f,
			1.0000f,
			0.0000f,
			0.1000f,
			0.4900f,
			0.0470f,
			0.6700f,
			0.2100f,
			0.5000f,
			1.0000f,
			1.0000f,
			0.4609f,
			0.0500f,
			0.0000f,
			0.0000f,
			1.0000f,
		};
		memcpy(programs[x].p,mp,sizeof(mp));
		strcpy(programs[x++].name,"fat amped SPLIT");
	}

	{
		float mp[kNumParams]=
		{
			0.0000f,
			1.0000f,
			0.2000f,
			0.6800f,
			0.6800f,
			0.7500f,
			0.1000f,
			0.5500f,
			0.6000f,
			0.0000f,
			0.2200f,
			1.0000f,
			0.6500f,
			1.0000f,
			1.0000f,
			0.4500f,
			0.0000f,
			0.4500f,
			1.0000f,
			1.0000f,
			1.0000f,
			0.0000f,
			0.3000f,
			0.3500f,
			1.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			1.0000f,
			0.4600f,
			0.1000f,
			0.3800f,
			0.2400f,
			1.0000f,
			0.0000f,
			0.1000f,
			0.6500f,
			0.0670f,
			0.7800f,
			0.5000f,
			0.2200f,
			0.0000f,
			1.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
		};
		memcpy(programs[x].p,mp,sizeof(mp));
		strcpy(programs[x++].name,"FLPs fiese Forfiesa");
	}

	{
		float mp[kNumParams]=
		{
			0.0000f,
			0.0000f,
			0.2000f,
			0.5000f,
			0.2200f,
			0.3900f,
			0.5000f,
			0.6000f,
			0.6000f,
			0.0000f,
			0.4800f,
			1.0000f,
			1.0000f,
			0.4540f,
			0.2170f,
			0.3550f,
			0.1510f,
			0.3030f,
			0.0960f,
			0.1890f,
			0.0000f,
			1.0000f,
			0.5000f,
			0.3800f,
			1.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			1.0000f,
			0.0000f,
			1.0000f,
			0.5100f,
			1.0000f,
			1.0000f,
			1.0000f,
			0.1000f,
			0.6500f,
			0.0470f,
			0.7100f,
			1.0000f,
			0.1700f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
		};
		memcpy(programs[x].p,mp,sizeof(mp));
		strcpy(programs[x++].name,"NHL");
	}

	{
		float mp[kNumParams]=
		{
			1.0000f,
			0.0000f,
			0.2000f,
			0.0000f,
			0.4300f,
			0.2000f,
			0.5000f,
			0.7000f,
			0.6000f,
			0.0000f,
			0.7000f,
			1.0000f,
			1.0000f,
			0.4300f,
			0.3050f,
			0.2400f,
			0.0990f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.3000f,
			0.3500f,
			1.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			1.0000f,
			0.0000f,
			0.6450f,
			0.0000f,
			0.7400f,
			0.0000f,
			0.0000f,
			0.1000f,
			0.6500f,
			0.0470f,
			0.7800f,
			0.5000f,
			0.5000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0300f,
			1.0000f,
			0.0000f,
			0.0000f,
		};
		memcpy(programs[x].p,mp,sizeof(mp));
		strcpy(programs[x++].name,"FLPs cool bass 1");
	}

	{
		float mp[kNumParams]=
		{
			1.0000f,
			0.0000f,
			0.2000f,
			0.0000f,
			0.5200f,
			0.1400f,
			0.5000f,
			0.7800f,
			0.6000f,
			0.0000f,
			0.7000f,
			1.0000f,
			1.0000f,
			0.4200f,
			0.3050f,
			0.1900f,
			0.1690f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.3000f,
			0.3500f,
			1.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			1.0000f,
			0.0000f,
			0.6450f,
			0.0000f,
			0.7400f,
			0.0000f,
			0.0000f,
			0.1000f,
			0.6500f,
			0.0470f,
			0.7800f,
			0.5000f,
			0.5000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
		};
		memcpy(programs[x].p,mp,sizeof(mp));
		strcpy(programs[x++].name,"FLPs cool bass 2");
	}

	{
		float mp[kNumParams]=
		{
			1.0000f,
			0.0000f,
			0.2000f,
			0.0000f,
			0.5200f,
			0.2100f,
			0.5000f,
			0.7000f,
			0.6000f,
			0.0000f,
			0.4000f,
			1.0000f,
			1.0000f,
			0.2500f,
			0.1450f,
			0.0900f,
			0.0390f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.3000f,
			0.3500f,
			1.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			1.0000f,
			0.5400f,
			1.0000f,
			0.0000f,
			0.2600f,
			0.0000f,
			0.0000f,
			0.1000f,
			0.6500f,
			0.0470f,
			0.7800f,
			0.5000f,
			0.1000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
		};
		memcpy(programs[x].p,mp,sizeof(mp));
		strcpy(programs[x++].name,"FLPs even cooler bass");
	}

	{
		float mp[kNumParams]=
		{
			0.0000f,
			0.7200f,
			0.2000f,
			0.0000f,
			1.0000f,
			0.3000f,
			0.0100f,
			0.5600f,
			0.6000f,
			0.0000f,
			0.2800f,
			1.0000f,
			0.1600f,
			0.5900f,
			1.0000f,
			0.0000f,
			0.9900f,
			0.3000f,
			0.4200f,
			0.8900f,
			0.2400f,
			1.0000f,
			0.3000f,
			0.3500f,
			1.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			1.0000f,
			0.3500f,
			1.0000f,
			0.3700f,
			0.6000f,
			1.0000f,
			1.0000f,
			0.1000f,
			0.3900f,
			0.0470f,
			1.0000f,
			1.0000f,
			0.5000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
		};
		memcpy(programs[x].p,mp,sizeof(mp));
		strcpy(programs[x++].name,"cutter");
	}

	{
		float mp[kNumParams]=
		{
			0.0000f,
			0.0000f,
			1.0000f,
			1.0000f,
			0.7300f,
			0.0000f,
			1.0000f,
			0.6000f,
			0.6000f,
			0.0000f,
			0.1700f,
			1.0000f,
			0.7600f,
			0.3400f,
			0.0700f,
			0.1400f,
			0.5800f,
			0.2700f,
			1.0000f,
			1.0000f,
			1.0000f,
			0.0000f,
			0.3000f,
			0.3500f,
			1.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			1.0000f,
			0.5200f,
			0.2400f,
			1.0000f,
			1.0000f,
			0.0000f,
			0.0000f,
			0.1100f,
			0.6800f,
			0.0570f,
			0.7700f,
			0.5000f,
			0.1100f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
		};
		memcpy(programs[x].p,mp,sizeof(mp));
		strcpy(programs[x++].name,"MODEM");
	}

	{
		float mp[kNumParams]=
		{
			0.0000f,
			0.0400f,
			0.2000f,
			0.0000f,
			0.2100f,
			1.0000f,
			1.0000f,
			0.5200f,
			0.6000f,
			0.0000f,
			0.4500f,
			1.0000f,
			1.0000f,
			0.5900f,
			0.0000f,
			0.0000f,
			0.0500f,
			0.0000f,
			0.0200f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.7000f,
			0.2900f,
			1.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.5700f,
			0.4700f,
			1.0000f,
			1.0000f,
			0.0000f,
			0.2900f,
			0.6500f,
			0.1300f,
			0.7800f,
			0.5000f,
			1.0000f,
			1.0000f,
			0.0000f,
			0.0000f,
			0.9800f,
			1.0000f,
			0.0000f,
			0.0000f,
		};
		memcpy(programs[x].p,mp,sizeof(mp));
		strcpy(programs[x++].name,"sine vibra");
	}

	{
		float mp[kNumParams]=
		{
			0.0000f,
			1.0000f,
			0.2000f,
			0.4600f,
			0.5700f,
			0.3700f,
			0.2000f,
			0.6000f,
			0.6000f,
			0.4400f,
			0.2900f,
			1.0000f,
			1.0000f,
			0.8800f,
			0.3700f,
			0.7500f,
			0.0000f,
			0.5800f,
			0.5400f,
			0.0000f,
			0.0800f,
			0.0000f,
			0.3000f,
			0.3500f,
			1.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			1.0000f,
			0.5300f,
			0.4100f,
			0.6500f,
			0.0000f,
			1.0000f,
			0.3900f,
			1.0000f,
			0.4500f,
			0.1900f,
			1.0000f,
			0.0000f,
			0.1000f,
			0.6800f,
			0.0470f,
			0.7200f,
			0.5000f,
			0.4200f,
			1.0000f,
			1.0000f,
			0.4297f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
		};
		memcpy(programs[x].p,mp,sizeof(mp));
		strcpy(programs[x++].name,"some rotz SPLIT");
	}

	{
		float mp[kNumParams]=
		{
			0.0000f,
			0.3300f,
			0.2000f,
			1.0000f,
			0.7300f,
			0.2400f,
			1.0000f,
			0.4600f,
			0.6000f,
			0.0000f,
			0.3400f,
			1.0000f,
			1.0000f,
			0.2300f,
			0.0000f,
			0.1100f,
			0.6400f,
			0.0000f,
			0.4500f,
			0.8400f,
			0.4100f,
			0.0000f,
			0.3000f,
			0.3500f,
			1.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			1.0000f,
			0.1600f,
			0.4800f,
			0.2100f,
			0.1000f,
			1.0000f,
			0.0000f,
			0.0400f,
			0.2500f,
			0.0570f,
			0.6100f,
			0.7100f,
			0.3800f,
			0.0000f,
			1.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
		};
		memcpy(programs[x].p,mp,sizeof(mp));
		strcpy(programs[x++].name,"thin");
	}

	{
		float mp[kNumParams]=
		{
			0.0000f,
			0.5500f,
			0.2000f,
			0.6000f,
			0.1800f,
			0.4400f,
			0.0000f,
			0.4900f,
			0.6000f,
			0.0000f,
			0.6000f,
			1.0000f,
			0.4400f,
			0.0000f,
			1.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.2600f,
			0.4900f,
			0.0000f,
			0.0000f,
			0.3000f,
			0.3500f,
			1.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.2800f,
			1.0000f,
			0.3400f,
			0.1900f,
			1.0000f,
			0.0000f,
			0.0400f,
			0.6400f,
			0.0770f,
			0.7700f,
			1.0000f,
			0.6900f,
			1.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
		};
		memcpy(programs[x].p,mp,sizeof(mp));
		strcpy(programs[x++].name,"angel hair");
	}

	{
		float mp[kNumParams]=
		{
			0.0000f,
			0.4500f,
			0.2000f,
			0.5300f,
			0.5600f,
			1.0000f,
			0.5000f,
			0.6000f,
			0.6000f,
			0.0000f,
			0.2400f,
			1.0000f,
			1.0000f,
			0.0000f,
			0.2100f,
			0.2700f,
			0.6200f,
			1.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.3000f,
			0.3500f,
			1.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.4000f,
			0.0000f,
			0.6600f,
			0.0000f,
			1.0000f,
			0.0000f,
			0.1000f,
			0.6500f,
			0.0670f,
			0.7800f,
			0.7700f,
			0.4200f,
			1.0000f,
			1.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
		};
		memcpy(programs[x].p,mp,sizeof(mp));
		strcpy(programs[x++].name,"little duck");
	}

	{
		float mp[kNumParams]=
		{
			0.0000f,
			0.0000f,
			0.2000f,
			0.6200f,
			0.4500f,
			0.2400f,
			1.0000f,
			0.6000f,
			0.6000f,
			0.0000f,
			0.4500f,
			1.0000f,
			1.0000f,
			0.7900f,
			0.0000f,
			0.4300f,
			0.0000f,
			0.1800f,
			0.0000f,
			0.0000f,
			0.0800f,
			1.0000f,
			0.5700f,
			0.3500f,
			1.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.4000f,
			0.0000f,
			0.6600f,
			0.0000f,
			1.0000f,
			0.0000f,
			0.1000f,
			0.6500f,
			0.0470f,
			0.7800f,
			0.5000f,
			0.4200f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
		};
		memcpy(programs[x].p,mp,sizeof(mp));
		strcpy(programs[x++].name,"dead entertainer");
	}

	{
		float mp[kNumParams]=
		{
			0.0000f,
			0.9100f,
			0.2000f,
			0.4400f,
			0.6500f,
			0.3300f,
			0.6800f,
			0.6000f,
			0.6000f,
			0.0000f,
			0.2200f,
			1.0000f,
			1.0000f,
			0.0000f,
			0.7900f,
			0.5800f,
			0.0000f,
			0.2600f,
			0.0000f,
			0.0000f,
			0.4400f,
			1.0000f,
			0.2100f,
			0.3400f,
			1.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			1.0000f,
			0.4000f,
			0.0000f,
			0.6600f,
			0.0000f,
			1.0000f,
			0.0000f,
			0.1000f,
			0.6500f,
			0.0470f,
			0.7200f,
			0.5000f,
			0.5000f,
			0.0000f,
			1.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
		};
		memcpy(programs[x].p,mp,sizeof(mp));
		strcpy(programs[x++].name,"resurrected entertainer");
	}

	{
		float mp[kNumParams]=
		{
			0.0000f,
			0.0100f,
			0.2000f,
			0.8500f,
			0.2300f,
			0.3600f,
			0.9900f,
			0.6000f,
			0.6000f,
			0.0000f,
			0.3700f,
			1.0000f,
			1.0000f,
			0.4700f,
			0.3800f,
			0.2100f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			1.0000f,
			0.3000f,
			0.3000f,
			1.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.4000f,
			0.0000f,
			0.6600f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.1000f,
			0.6500f,
			0.0470f,
			0.7800f,
			0.5000f,
			0.5000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
		};
		memcpy(programs[x].p,mp,sizeof(mp));
		strcpy(programs[x++].name,"cheap B*ntempi");
	}

	{
		float mp[kNumParams]=
		{
			1.0000f,
			0.0000f,
			0.2000f,
			0.8600f,
			0.0000f,
			0.7500f,
			0.5000f,
			0.5100f,
			0.6000f,
			0.0000f,
			0.6800f,
			0.0000f,
			1.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			1.0000f,
			0.0000f,
			0.0000f,
			0.0400f,
			0.0400f,
			1.0000f,
			0.3000f,
			0.3500f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.6900f,
			1.0000f,
			0.9800f,
			0.1900f,
			1.0000f,
			0.0000f,
			0.0600f,
			0.6500f,
			0.0770f,
			0.7800f,
			0.5000f,
			0.2200f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
		};
		memcpy(programs[x].p,mp,sizeof(mp));
		strcpy(programs[x++].name,"NDW lead");
	}

	{
		float mp[kNumParams]=
		{
			0.0000f,
			0.2000f,
			0.2000f,
			0.0000f,
			0.0000f,
			0.7500f,
			0.5000f,
			0.6000f,
			0.6000f,
			0.0000f,
			0.2200f,
			0.0000f,
			1.0000f,
			1.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.3000f,
			0.3500f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.4000f,
			0.0000f,
			0.6600f,
			0.0000f,
			1.0000f,
			0.0000f,
			0.1000f,
			0.6500f,
			0.0470f,
			0.7800f,
			0.5000f,
			0.5000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
		};
		memcpy(programs[x].p,mp,sizeof(mp));
		strcpy(programs[x++].name,"the rest is empty");
	}

	{
		float mp[kNumParams]=
		{
			0.0000f,
			0.2000f,
			0.2000f,
			0.0000f,
			0.0000f,
			0.7500f,
			0.5000f,
			0.6000f,
			0.6000f,
			0.0000f,
			0.2200f,
			0.0000f,
			1.0000f,
			1.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.3000f,
			0.3500f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.4000f,
			0.0000f,
			0.6600f,
			0.0000f,
			1.0000f,
			0.0000f,
			0.1000f,
			0.6500f,
			0.0470f,
			0.7800f,
			0.5000f,
			0.5000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
		};
		memcpy(programs[x].p,mp,sizeof(mp));
		strcpy(programs[x++].name,"make your own!");
	}

	{
		float mp[kNumParams]=
		{
			0.0000f,
			0.2000f,
			0.2000f,
			0.0000f,
			0.0000f,
			0.7500f,
			0.5000f,
			0.6000f,
			0.6000f,
			0.0000f,
			0.2200f,
			0.0000f,
			1.0000f,
			1.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.3000f,
			0.3500f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.4000f,
			0.0000f,
			0.6600f,
			0.0000f,
			1.0000f,
			0.0000f,
			0.1000f,
			0.6500f,
			0.0470f,
			0.7800f,
			0.5000f,
			0.5000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
		};
		memcpy(programs[x].p,mp,sizeof(mp));
		strcpy(programs[x++].name,"just turn the knobs-");
	}

	{
		float mp[kNumParams]=
		{
			0.0000f,
			0.2000f,
			0.2000f,
			0.0000f,
			0.0000f,
			0.7500f,
			0.5000f,
			0.6000f,
			0.6000f,
			0.0000f,
			0.2200f,
			0.0000f,
			1.0000f,
			1.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.3000f,
			0.3500f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.4000f,
			0.0000f,
			0.6600f,
			0.0000f,
			1.0000f,
			0.0000f,
			0.1000f,
			0.6500f,
			0.0470f,
			0.7800f,
			0.5000f,
			0.5000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
		};
		memcpy(programs[x].p,mp,sizeof(mp));
		strcpy(programs[x++].name,"-it's not very hard!");
	}

	{
		float mp[kNumParams]=
		{
			0.0000f,
			0.2000f,
			0.2000f,
			0.0000f,
			0.0000f,
			0.7500f,
			0.5000f,
			0.6000f,
			0.6000f,
			0.0000f,
			0.2200f,
			0.0000f,
			1.0000f,
			1.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.3000f,
			0.3500f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.4000f,
			0.0000f,
			0.6600f,
			0.0000f,
			1.0000f,
			0.0000f,
			0.1000f,
			0.6500f,
			0.0470f,
			0.7800f,
			0.5000f,
			0.5000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
		};
		memcpy(programs[x].p,mp,sizeof(mp));
		strcpy(programs[x++].name,"Still here?");
	}

	{
		float mp[kNumParams]=
		{
			0.0000f,
			0.2000f,
			0.2000f,
			0.0000f,
			0.0000f,
			0.7500f,
			0.5000f,
			0.6000f,
			0.6000f,
			0.0000f,
			0.2200f,
			0.0000f,
			1.0000f,
			1.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.3000f,
			0.3500f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.4000f,
			0.0000f,
			0.6600f,
			0.0000f,
			1.0000f,
			0.0000f,
			0.1000f,
			0.6500f,
			0.0470f,
			0.7800f,
			0.5000f,
			0.5000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
		};
		memcpy(programs[x].p,mp,sizeof(mp));
		strcpy(programs[x++].name,"Come on now!");
	}

	{
		float mp[kNumParams]=
		{
			0.0000f,
			0.2000f,
			0.2000f,
			0.0000f,
			0.0000f,
			0.7500f,
			0.5000f,
			0.6000f,
			0.6000f,
			0.0000f,
			0.2200f,
			0.0000f,
			1.0000f,
			1.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.3000f,
			0.3500f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.4000f,
			0.0000f,
			0.6600f,
			0.0000f,
			1.0000f,
			0.0000f,
			0.1000f,
			0.6500f,
			0.0470f,
			0.7800f,
			0.5000f,
			0.5000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
		};
		memcpy(programs[x].p,mp,sizeof(mp));
		strcpy(programs[x++].name,"You can't wait forever.");
	}

	{
		float mp[kNumParams]=
		{
			0.0000f,
			0.2000f,
			0.2000f,
			0.0000f,
			0.0000f,
			0.7500f,
			0.5000f,
			0.6000f,
			0.6000f,
			0.0000f,
			0.2200f,
			0.0000f,
			1.0000f,
			1.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.3000f,
			0.3500f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.4000f,
			0.0000f,
			0.6600f,
			0.0000f,
			1.0000f,
			0.0000f,
			0.1000f,
			0.6500f,
			0.0470f,
			0.7800f,
			0.5000f,
			0.5000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
		};
		memcpy(programs[x].p,mp,sizeof(mp));
		strcpy(programs[x++].name,"Give it a try.");
	}

	{
		float mp[kNumParams]=
		{
			0.0000f,
			0.2000f,
			0.2000f,
			0.0000f,
			0.0000f,
			0.7500f,
			0.5000f,
			0.6000f,
			0.6000f,
			0.0000f,
			0.2200f,
			0.0000f,
			1.0000f,
			1.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.3000f,
			0.3500f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.4000f,
			0.0000f,
			0.6600f,
			0.0000f,
			1.0000f,
			0.0000f,
			0.1000f,
			0.6500f,
			0.0470f,
			0.7800f,
			0.5000f,
			0.5000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
		};
		memcpy(programs[x].p,mp,sizeof(mp));
		strcpy(programs[x++].name,"Not?");
	}

	{
		float mp[kNumParams]=
		{
			0.0000f,
			0.2000f,
			0.2000f,
			0.0000f,
			0.0000f,
			0.7500f,
			0.5000f,
			0.6000f,
			0.6000f,
			0.0000f,
			0.2200f,
			0.0000f,
			1.0000f,
			1.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.3000f,
			0.3500f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.4000f,
			0.0000f,
			0.6600f,
			0.0000f,
			1.0000f,
			0.0000f,
			0.1000f,
			0.6500f,
			0.0470f,
			0.7800f,
			0.5000f,
			0.5000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
			0.0000f,
		};
		memcpy(programs[x].p,mp,sizeof(mp));
		strcpy(programs[x++].name,"--init--");
	}

}

// make one of the three waveform sets with four complete waves
// per set. "number" is 1..3 and references the waveform set
void flp::calc_waveforms(int number)
{
	int i,c;
	float	*t;
	float	this_p[kNumParams];
	for(c=0;c<kNumParams;c++)
		this_p[c]=my_p[c];
	if(number==2)
	{
		c=n_2_db1;
		t=&wavetable[WAVETABLESIZE*TABLES_PER_CHANNEL];
	}
	else if(number==3)
	{
		t=&wavetable[WAVETABLESIZE*TABLES_PER_CHANNEL*2];
		c=n_3_db1;
	}
	else
	{
		t=&wavetable[0];
		c=n_1_db1;
	}

//	weight to each drawbar
	this_p[c]*=1.5f;
	this_p[c+1]*=1.0f;
	this_p[c+2]*=.8f;
	this_p[c+3]*=.8f;
	this_p[c+4]*=.8f;
	this_p[c+5]*=.8f;
	this_p[c+6]*=.8f;
	this_p[c+7]*=.6f;
	this_p[c+8]*=.6f;

	for(i=0;i<WAVETABLESIZE;i++)
	{
		t[i]=t[i+WAVETABLESIZE]=t[i+WAVETABLESIZE*2]=t[i+WAVETABLESIZE*3]=
			t[i+WAVETABLESIZE*4]=
			t[i+WAVETABLESIZE*5]=
			t[i+WAVETABLESIZE*6]=
			t[i+WAVETABLESIZE*7]=
			sin_16[i]*this_p[c]+sin_8[i]*this_p[c+1]
			+sin_513[i]*this_p[c+2];

/*
	This is very important for a warm sound:
	The "tone wheels" are a limited resource and they
	supply limited pitch heights. If a drawbar register
	is forced to play a tune above the highest possible
	note it will simply be transposed one octave down.
	In addition it will appear less loud; that's what
	d2, d4 and d8 are for.
*/
#define d2 .5f
#define d4 .25f
#define d8 .125f
		if(number==3)
		{
			t[i]+=sin_4[i]*this_p[c+3]+sin_223[i]*this_p[c+4];
			t[i+WAVETABLESIZE  ]+=sin_4[i]*this_p[c+3]+sin_223[i]*this_p[c+4];
			t[i+WAVETABLESIZE*2]+=sin_4[i]*this_p[c+3]+sin_223[i]*this_p[c+4];
			t[i+WAVETABLESIZE*3]+=sin_4[i]*this_p[c+3]+sin_223[i]*this_p[c+4];
			t[i+WAVETABLESIZE*4]+=sin_4[i]*this_p[c+3]+sin_223[i]*this_p[c+4];
			t[i+WAVETABLESIZE*5]+=sin_4[i]*this_p[c+3]+sin_223[int(i/2)]*d2*this_p[c+4];
			t[i+WAVETABLESIZE*6]+=sin_4[i]*this_p[c+3]+sin_223[int(i/2)]*d2*this_p[c+4];
			t[i+WAVETABLESIZE*7]+=sin_4[int(i/2)]*d2*this_p[c+3]+sin_223[int(i/2)]*d2*this_p[c+4];
		}
		else
		{
			t[i]+=sin_4[i]*this_p[c+3]+sin_223[i]*this_p[c+4]
				+sin_2[i]*this_p[c+5]
				+sin_135[i]*this_p[c+6]+sin_113[i]*this_p[c+7]
				+sin_1[i]*this_p[c+8];
			t[i+WAVETABLESIZE]+=sin_4[i]*this_p[c+3]+sin_223[i]*this_p[c+4]
				+sin_2[i]*this_p[c+5]
				+sin_135[i]*this_p[c+6]+sin_113[i]*this_p[c+7]
				+sin_1[int(i/2)]*d2*this_p[c+8];
			t[i+WAVETABLESIZE*2]+=sin_4[i]*this_p[c+3]+sin_223[i]*this_p[c+4]
				+sin_2[i]*this_p[c+5]
				+sin_135[i]*this_p[c+6]+sin_113[int(i/2)]*d2*this_p[c+7]
				+sin_1[int(i/2)]*d2*this_p[c+8];
			t[i+WAVETABLESIZE*3]+=sin_4[i]*this_p[c+3]+sin_223[i]*this_p[c+4]
				+sin_2[i]*this_p[c+5]
				+sin_135[int(i/2)]*d2*this_p[c+6]+sin_113[int(i/2)]*d2*this_p[c+7]
				+sin_1[int(i/2)]*d2*this_p[c+8];
			t[i+WAVETABLESIZE*4]+=sin_4[i]*this_p[c+3]+sin_223[i]*this_p[c+4]
				+sin_2[int(i/2)]*d2*this_p[c+5]
				+sin_135[int(i/2)]*d2*this_p[c+6]+sin_113[int(i/2)]*d2*this_p[c+7]
				+sin_1[int(i/4)]*d4*this_p[c+8];
			t[i+WAVETABLESIZE*5]+=sin_4[i]*this_p[c+3]+sin_223[int(i/2)]*d2*this_p[c+4]
				+sin_2[int(i/2)]*d2*this_p[c+5]
				+sin_135[int(i/2)]*d2*this_p[c+6]+sin_113[int(i/4)]*d4*this_p[c+7]
				+sin_1[int(i/4)]*d4*this_p[c+8];
			t[i+WAVETABLESIZE*6]+=sin_4[i]*this_p[c+3]+sin_223[int(i/2)]*d2*this_p[c+4]
				+sin_2[int(i/2)]*d2*this_p[c+5]
				+sin_135[int(i/4)]*0*this_p[c+6]+sin_113[int(i/4)]*d4*this_p[c+7]
				+sin_1[int(i/4)]*d4*this_p[c+8];
			t[i+WAVETABLESIZE*7]+=sin_4[int(i/2)]*d2*this_p[c+3]+sin_223[int(i/2)]*d2*this_p[c+4]
				+sin_2[int(i/4)]*d4*this_p[c+5]
				+sin_135[int(i/4)]*0*this_p[c+6]+sin_113[int(i/4)]*d4*this_p[c+7]
				+sin_1[int(i/8)]*d8*this_p[c+8];
		}
	}
/*
	The grown up source code viewer will find that sin_135 is only
	folded once (/2). Well, I had terrible aliasing problems when
	folding it twice (/4), and the easiest solution was to set it to
	zero instead. You can't claim you actually heard it, can you?
*/
	wavetable[WAVETABLESIZE*12]=0;
}

void flp::calc_click()
{
/*
	Click is not just click - it has to follow the underlying
	note pitch. However, the click emulation is just "try and
	error". Improve it if you can, but PLEAZE tell me how you
	did it...
*/
	click[0]=my_p[n_click]*
	(my_p[n_1_db1]+my_p[n_1_db2]
	+my_p[n_1_db3]+my_p[n_1_db4]
	+my_p[n_1_db5]+my_p[n_1_db6]
	+my_p[n_1_db7]+my_p[n_1_db8]
	+my_p[n_1_db9])/9;

	click[1]=my_p[n_click]*
	(my_p[n_2_db1]+my_p[n_2_db2]
	+my_p[n_2_db3]+my_p[n_2_db4]
	+my_p[n_2_db5]+my_p[n_2_db6]
	+my_p[n_2_db7]+my_p[n_2_db8]
	+my_p[n_2_db9])/9;

	click[2]=my_p[n_click]*
	(my_p[n_3_db1]+my_p[n_3_db2]
	+my_p[n_3_db3]+my_p[n_3_db4]
	+my_p[n_1_db5])/22;
}

void flp::setProgram (VstInt32 program)
{
//	this->setProgram(program,false);
	this->setProgram(program,true);
}

void flp::setProgram (VstInt32 program,bool force)
{
	//if (program < 0 || program >= kNumPrograms)
	//	return;

	//curProgram = program;
	//flpProgram *ap = &programs[program];
	//for(int i =0;i < kNumParams; i++)
	//{
	//	setParameter(i,ap->p[i]);
	//}
	//return;

	long x;

	if(force)
		actual_curProgram=-2;

	flpProgram *ap = &programs[program];

// prepare for delayed program change
	virtual_my_p=ap->p;
	curProgram=program;

#ifndef DELAYED_PARAMS
	setProgramDelayCount=-1;
#endif

// has the program change delay elapsed?
	if(setProgramDelayCount==-1)
	{
		curProgram=program;
		virtual_my_p=my_p;
	}

	if(actual_curProgram!=program)
	{
		for(x=0;x<kNumParams;x++)
		{
#ifdef DELAYED_PARAMS
			param_is_manual=true;
#endif
			setParameter(x,ap->p[x]);
		}
	}

// set parameter display only after program change delay has elapsed
// this must occur after the setParameter calls
#ifdef DELAYED_PARAMS
	if(setProgramDelayCount==-1 || param_is_manual)
	{
		setProgramDelayCount=0;
#endif
		if(editor)
			((AEffGUIEditor*)editor)->setParameter(n_display,(float)curProgram);
		actual_curProgram=program;
#ifdef DELAYED_PARAMS
	}
// retrigger delay if we are idle or during delay
	else
	{
		setProgramDelayCount=1;
	}
#endif

	param_is_manual=false;
}

void flp::setProgramName (char *name)
{
	strcpy (programs[curProgram].name, name);
	if(editor)
		((AEffGUIEditor*)editor)->setParameter(n_display,(float)curProgram);
}

void flp::getProgramName (char *name)
{
	strcpy (name, programs[curProgram].name);
}

void flp::getParameterLabel (VstInt32 index, char *label)
{
	// forget it, we don't fully support non-GUI interface...
	sprintf(label, "",index);
}

void flp::getParameterDisplay (VstInt32 index, char *text)
{
	text[0] = 0;
	switch(index)
	{
	case n_bender:
		convert_bendrange(p[index],text);
		break;
	case n_tone:
		convert_tone(p[index],text);
		break;
	case n_l_slow:
	case n_u_slow:
	case n_l_fast:
	case n_u_fast:
		convert_speed(p[index],text);
		break;
	case n_perc:
		convert_perc(p[index],text);
		break;
	case n_shape:
		convert_shape(p[index],text);
		break;
	default:
		sprintf(text,"%3.1f %%",100*p[index]);
		break;
	}
}

void flp::getParameterName (VstInt32 index, char *label)
{
	if(index<=LAST_PARAM)
		strcpy(label,labels[index]);
	else
		strcpy(label,"---");
}

void flp::my_setParameter (long index, float value)
{
	if(index<0 || index>kNumParams || (!param_is_manual && setProgramDelayCount>=0))
		return;

	if(compare)
	{
		flpProgram*	ap = &programs[curProgram];
		value=ap->p[index];			// fetch value from program memory
		my_p=ap->p;					// let machine use program memory
	}
	else
	{
		p[index]=value;				// put value into edit buffer
		my_p=p;						// let machine use edit buffer
	}

	//if(value!=last_value[index])
	{
		last_value[index]=value;
		switch(index)
		{
			case n_1_db1:
			case n_1_db2:
			case n_1_db3:
			case n_1_db4:
			case n_1_db5:
			case n_1_db6:
			case n_1_db7:
			case n_1_db8:
			case n_1_db9:
				calc_waveforms(1);
				calc_click();
				break;
			case n_2_db1:
			case n_2_db2:
			case n_2_db3:
			case n_2_db4:
			case n_2_db5:
			case n_2_db6:
			case n_2_db7:
			case n_2_db8:
			case n_2_db9:
				calc_waveforms(2);
				calc_click();
				break;
			case n_3_db1:
			case n_3_db2:
			case n_3_db3:
			case n_3_db4:
			case n_3_db5:
				calc_waveforms(3);
				calc_click();
				break;
			case n_shape:
				if(make_waveforms(int(value*(W_NUMOF-1)+1)-1))
				{
					calc_waveforms(1);
					calc_waveforms(2);
					calc_waveforms(3);
				}
				break;
			case n_1_perc:
			case n_2_perc:
			case n_3_perc:
			case n_perc:
			case n_percvol:
			case n_percfade:
				{
					int v=(int)(my_p[n_perc]*10);
					float pmult;
					if(v<1)
						pmult=0;
					else if(v<2)
						pmult=1;
					else if(v<3)
						pmult=2;
					else if(v<4)
						pmult=3;
					else if(v<5)
						pmult=4;
					else if(v<6)
						pmult=6;
					else if(v<7)
						pmult=8;
					else if(v<8)
						pmult=10;
					else if(v<9)
						pmult=12;
					else
						pmult=16;

					n1->set_percussion(1.5f*my_p[n_percvol],pmult,my_p[n_percfade]);
				}
				break;
			case n_click:
				calc_click();
				break;
			case n_vol1:
				n1->set_volume(value*.3f,0);
				break;
			case n_vol2:
				n1->set_volume(value*.4f,1);
				break;
			case n_vol3:
				n1->set_volume(value*.6f,2);
				break;
			case n_mono:
				if(value!=mono_before)
				{
					if(value>=.5f)
						n1->set_numofvoices(1);
					else
						n1->set_numofvoices(NUMOFVOICES);

					n1->set_volume(my_p[n_vol1]*.3f,0);
					n1->set_volume(my_p[n_vol2]*.3f,1);
					n1->set_volume(my_p[n_vol3]*.6f,2);
				}
				mono_before=value;
				break;
			case n_1_vibrato:
				vibchanged1=true;
				break;
			case n_1_vmix:
				if(my_p[n_1_vibrato]==1)
				{
					vmix1=value;
					vibchanged1=true;
				}
				break;
			case n_2_vibrato:
				vibchanged2=true;
				break;
			case n_2_vmix:
				if(my_p[n_2_vibrato]==1)
				{
					vmix2=value;
					vibchanged2=true;
				}
				break;
			case n_drive:
				if(value>0)
					do_dist=true;
				else
					do_dist=false;
				dist=2*(0.1f+value);
				sin_dist=sinf(dist);
				i_dist=1/dist;
				dist4=4*dist;
				dist8=8*dist;
				break;
			case n_mrvalve:
				odchanged=true;
				break;
			case n_mix:
				odmix=value;
				if(my_p[n_mrvalve]==1)
					odchanged=true;
				break;
			case n_tone:
				fuzz_filt.setparam(800+value*3000,.7f,samplerate);
				break;
			case n_speed:
				if(value>.5f)
					fastmode=true;
				else
					fastmode=false;
				break;
			case n_l_slow:
				lslow=value*10;
				break;
			case n_l_fast:
				lfast=value*10;
				break;
			case n_u_slow:
				uslow=value*10;
				break;
			case n_u_fast:
				ufast=value*10;
				break;
			case n_belt:
				ubelt_up=(value*3+1)*.012f;
				ubelt_down=(value*3+1)*.008f;
				lbelt_up=(value*3+1)*.0045f;
				lbelt_down=(value*3+1)*.0035f;
				break;
			case n_spread:
				lfos_ok=false;
				break;
			case n_splitpoint:
				splitpoint=(long)(value*128);
				break;
		}

		if (editor)
			((AEffGUIEditor*)editor)->setParameter(index,value);
	}
}

void flp::setParameter (VstInt32 index, float value)
{
/*
	If you implement a plugin as suggested in the SDK you
	will have the following side effect:
	An automated or manually changed parameter will always
	be written into the actual program. The original program
	is lost. To prevent this we use several program buffers
	and let the plugin decide wether the data will be
	saved or not. This is the desired behaviour, similar
	to all those hardware expanders.

    A new feature is delayed program change. When the host runs
	several setProgram calls shortly after another we don't want
	to perform real program and parameter changes. We store the
	new program name in next_curProgram and let virtual_my_p point
	to the according program memory. From setProgram we set
	setProgramStep=sps_requested. The process routine sees this,
	sets setProgramStep=sps_waiting, counts for a while, sets
	setProgramStep=sps_acknowledged and	runs a setProgram(next_curProgram).
	Now setProgram and setParameter can decide whether to ignore
	the change (if next_curProgram==curProgram) or to perform
	a real, full program change with all parameter changes.
	setProgramStep will be reset to sps_idle.

	ap		program memory
	p		edit buffer
	i_p		buffer to save edit buffer (for compare function)
	my_p	points to any buffer. The "machine" always uses my_p.
*/

/*
	UPDATE:
	Due to incompatibilities with several hosts we make the whole feature
	compile-time switch dependent. We use delayed program change only if
	DELAYED_PARAMS is defined.
*/

	flpProgram*	ap = &programs[curProgram];
	my_p=p;					// let machine use program memory

// ...no "save" button without editor, so no delayed parameter changes...
	if(!editor)
		param_is_manual=true;
	
	if(index==n_mute)
	{
		if(value>0)
			mute=true;
		else
		{
			mute=false;
			fullyloaded=true;
		}
	}

	if(index==n_param_is_manual)
	{
		if(value>.5f)				// we have a manual parameter change
		{
			param_is_manual=true;
		}
		else
			param_is_manual=false;
	}
	else if(index==n_1_midi || index==n_2_midi || index==n_3_midi)
	{
		if (editor)
			((AEffGUIEditor*)editor)->setParameter(index,value);
	}
	else if(index==n_split)
	{
		if(value==1)
			waitforsplit=true;
		else
		{
			waitforsplit=false;
			splitpoint=0;
		}
	}
	else if(index>=0 && index<kNumParams)
	{
#ifdef DELAYED_PARAMS
		if(!param_is_manual)			// not manual: bank or patch load
#endif
			ap->p[index]=value;			// copy value into program memory

		my_setParameter(index,value);
	}
#ifdef DELAYED_PARAMS
	else if(index==n_compare)
	{
		if(value==0)					// compare button released
		{
			int i;
			for(i=0;i<kNumParams;i++)
				p[i]=i_p[i];			// recall edit buffer
			compare=false;
			my_p=p;						// let machine use edit buffer
		}
		else							// compare button pressed
		{
			for(i=0;i<kNumParams;i++)
					i_p[i]=p[i];		// save edit buffer
			compare=true;
			my_p=ap->p;					// let machine use program memory
		}

		for(i=0;i<kNumParams;i++)
			my_setParameter(i,my_p[i]);	// let everyone know the new values
	}
	else if(index==n_save)				// save button pressed
	{
		for(i=0;i<kNumParams;i++)
		{
			if(compare)
			{
				ap->p[i]=i_p[i];		// copy compare buffer params to program memory
			}
			else
			{
				ap->p[i]=my_p[i];		// copy current machine params to program memory
				i_p[i]=my_p[i];			// copy current machine params to compare buffer
										// We need this since there will be a setParameter
										// to n_compare with value 0 which will write the
										// compare buffer back to the edit buffer.
			}
		}
	}
	else if(index==n_display)
#else
	if(index==n_display)
#endif
	{
		if(value<0)
			value=0;
		if(value>kNumPrograms-1)
			value=kNumPrograms-1;
		if((long)value != getProgram())
			setProgram((long)value);
	}
}

float flp::getParameter (VstInt32 index)
{
	gp_value=0;
	if(index>=0 && index<kNumParams)
		gp_value=virtual_my_p[index];

	if(index==n_output)
	{
		gp_value=fabsf(last_out1)*7;
		if(gp_value<0 || mono==0)
			gp_value=0;
		if(gp_value>1)
			gp_value=1;
	}

	return gp_value;
}

bool flp::getOutputProperties (VstInt32 index, VstPinProperties* properties)
{
	if (index < kNumOutputs)
	{
/*
	We could add "L" and "R" for the channels, but this
	is not recognized by all hosts. This is the most compatible
	solution.
*/
		sprintf (properties->label, "AZR3");
		sprintf (properties->shortLabel, "AZR3");
		properties->flags = kVstPinIsActive;
		if (index < 2)
			properties->flags |= kVstPinIsStereo;
		return true;
	}
	return false;
}

bool flp::getProgramNameIndexed (VstInt32 category, VstInt32 index, char* text)
{
	if (index < kNumPrograms)
	{
		strcpy (text, programs[index].name);
		return true;
	}
	return false;
}

bool flp::copyProgram (VstInt32 destination)
{
	if (destination < kNumPrograms)
	{
		programs[destination] = programs[curProgram];
		return true;
	}
	return false;
}

VstInt32 flp::getProgram()
{
	return(curProgram);
}

bool flp::getEffectName (char* name)
{
	strcpy (name, EFFECT_NAME);
	return true;
}

bool flp::getVendorString (char* text)
{
	strcpy (text, VENDOR_STRING);
	return true;
}

bool flp::getProductString (char* text)
{
	strcpy (text, PRODUCT_STRING);
	return true;
}

VstInt32 flp::canDo (char* text)
{
	if (!strcmp (text, "receiveVstEvents"))
		return 1;
	else if (!strcmp (text, "receiveVstMidiEvent"))
		return 1;
	else if (!strcmp (text, "sendVstMidiEvent"))
		return 1;
	else
		return -1;
}

