#ifndef _pc_speaker_
#define _pc_speaker_

#define CONFIG_PORT		0x43
#define CH2_PORT		0x42		
#define STATUS_PORT		0x61

#define PIT_FREQ	 1193180

int pc_speaker_beep(int type, unsigned int freq);

static void pc_speaker_start_beep(unsigned int freq);
 
static void pc_speaker_shut_up();

#endif
