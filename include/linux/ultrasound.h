macro_line|#ifndef _ULTRASOUND_H_
DECL|macro|_ULTRASOUND_H_
mdefine_line|#define _ULTRASOUND_H_
multiline_comment|/*&n; *&t;ultrasound.h - Macros for programming the Gravis Ultrasound&n; *&t;&t;&t;These macros are extremely device dependent&n; *&t;&t;&t;and not portable.&n; */
multiline_comment|/*&n; * Copyright (C) by Hannu Savolainen 1993-1997&n; *&n; * OSS/Free for Linux is distributed under the GNU GENERAL PUBLIC LICENSE (GPL)&n; * Version 2 (June 1991). See the &quot;COPYING&quot; file distributed with this software&n; * for more info.&n; */
multiline_comment|/*&n; *&t;Private events for Gravis Ultrasound (GUS)&n; *&n; *&t;Format:&n; *&t;&t;byte 0 &t;&t;- SEQ_PRIVATE (0xfe)&n; *&t;&t;byte 1 &t;&t;- Synthesizer device number (0-N)&n; *&t;&t;byte 2 &t;&t;- Command (see below)&n; *&t;&t;byte 3 &t;&t;- Voice number (0-31)&n; *&t;&t;bytes 4 and 5&t;- parameter P1 (unsigned short)&n; *&t;&t;bytes 6 and 7&t;- parameter P2 (unsigned short)&n; *&n; *&t;Commands:&n; *&t;&t;Each command affects one voice defined in byte 3.&n; *&t;&t;Unused parameters (P1 and/or P2 *MUST* be initialized to zero).&n; *&t;&t;_GUS_NUMVOICES&t;- Sets max. number of concurrent voices (P1=14-31, default 16)&n; *&t;&t;_GUS_VOICESAMPLE- ************ OBSOLETE *************&n; *&t;&t;_GUS_VOICEON&t;- Starts voice (P1=voice mode)&n; *&t;&t;_GUS_VOICEOFF&t;- Stops voice (no parameters)&n; *&t;&t;_GUS_VOICEFADE&t;- Stops the voice smoothly.&n; *&t;&t;_GUS_VOICEMODE&t;- Alters the voice mode, don&squot;t start or stop voice (P1=voice mode)&n; *&t;&t;_GUS_VOICEBALA&t;- Sets voice balence (P1, 0=left, 7=middle and 15=right, default 7)&n; *&t;&t;_GUS_VOICEFREQ&t;- Sets voice (sample) playback frequency (P1=Hz)&n; *&t;&t;_GUS_VOICEVOL&t;- Sets voice volume (P1=volume, 0xfff=max, 0xeff=half, 0x000=off)&n; *&t;&t;_GUS_VOICEVOL2&t;- Sets voice volume (P1=volume, 0xfff=max, 0xeff=half, 0x000=off)&n; *&t;&t;&t;&t;  (Like GUS_VOICEVOL but doesn&squot;t change the hw&n; *&t;&t;&t;&t;  volume. It just updates volume in the voice table).&n; *&n; *&t;&t;_GUS_RAMPRANGE&t;- Sets limits for volume ramping (P1=low volume, P2=high volume)&n; *&t;&t;_GUS_RAMPRATE&t;- Sets the speed for volume ramping (P1=scale, P2=rate)&n; *&t;&t;_GUS_RAMPMODE&t;- Sets the volume ramping mode (P1=ramping mode)&n; *&t;&t;_GUS_RAMPON&t;- Starts volume ramping (no parameters)&n; *&t;&t;_GUS_RAMPOFF&t;- Stops volume ramping (no parameters)&n; *&t;&t;_GUS_VOLUME_SCALE - Changes the volume calculation constants&n; *&t;&t;&t;&t;  for all voices.&n; */
DECL|macro|_GUS_NUMVOICES
mdefine_line|#define _GUS_NUMVOICES&t;&t;0x00
DECL|macro|_GUS_VOICESAMPLE
mdefine_line|#define _GUS_VOICESAMPLE&t;0x01&t;/* OBSOLETE */
DECL|macro|_GUS_VOICEON
mdefine_line|#define _GUS_VOICEON&t;&t;0x02
DECL|macro|_GUS_VOICEOFF
mdefine_line|#define _GUS_VOICEOFF&t;&t;0x03
DECL|macro|_GUS_VOICEMODE
mdefine_line|#define _GUS_VOICEMODE&t;&t;0x04
DECL|macro|_GUS_VOICEBALA
mdefine_line|#define _GUS_VOICEBALA&t;&t;0x05
DECL|macro|_GUS_VOICEFREQ
mdefine_line|#define _GUS_VOICEFREQ&t;&t;0x06
DECL|macro|_GUS_VOICEVOL
mdefine_line|#define _GUS_VOICEVOL&t;&t;0x07
DECL|macro|_GUS_RAMPRANGE
mdefine_line|#define _GUS_RAMPRANGE&t;&t;0x08
DECL|macro|_GUS_RAMPRATE
mdefine_line|#define _GUS_RAMPRATE&t;&t;0x09
DECL|macro|_GUS_RAMPMODE
mdefine_line|#define _GUS_RAMPMODE&t;&t;0x0a
DECL|macro|_GUS_RAMPON
mdefine_line|#define _GUS_RAMPON&t;&t;0x0b
DECL|macro|_GUS_RAMPOFF
mdefine_line|#define _GUS_RAMPOFF&t;&t;0x0c
DECL|macro|_GUS_VOICEFADE
mdefine_line|#define _GUS_VOICEFADE&t;&t;0x0d
DECL|macro|_GUS_VOLUME_SCALE
mdefine_line|#define _GUS_VOLUME_SCALE&t;0x0e
DECL|macro|_GUS_VOICEVOL2
mdefine_line|#define _GUS_VOICEVOL2&t;&t;0x0f
DECL|macro|_GUS_VOICE_POS
mdefine_line|#define _GUS_VOICE_POS&t;&t;0x10
multiline_comment|/*&n; *&t;GUS API macros&n; */
DECL|macro|_GUS_CMD
mdefine_line|#define _GUS_CMD(chn, voice, cmd, p1, p2) &bslash;&n;&t;&t;&t;&t;&t;{_SEQ_NEEDBUF(8); _seqbuf[_seqbufptr] = SEQ_PRIVATE;&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr+1] = (chn); _seqbuf[_seqbufptr+2] = cmd;&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr+3] = voice;&bslash;&n;&t;&t;&t;&t;&t;*(unsigned short*)&amp;_seqbuf[_seqbufptr+4] = p1;&bslash;&n;&t;&t;&t;&t;&t;*(unsigned short*)&amp;_seqbuf[_seqbufptr+6] = p2;&bslash;&n;&t;&t;&t;&t;&t;_SEQ_ADVBUF(8);}
DECL|macro|GUS_NUMVOICES
mdefine_line|#define GUS_NUMVOICES(chn, p1)&t;&t;&t;_GUS_CMD(chn, 0, _GUS_NUMVOICES, (p1), 0)
DECL|macro|GUS_VOICESAMPLE
mdefine_line|#define GUS_VOICESAMPLE(chn, voice, p1)&t;&t;_GUS_CMD(chn, voice, _GUS_VOICESAMPLE, (p1), 0)&t;/* OBSOLETE */
DECL|macro|GUS_VOICEON
mdefine_line|#define GUS_VOICEON(chn, voice, p1)&t;&t;_GUS_CMD(chn, voice, _GUS_VOICEON, (p1), 0)
DECL|macro|GUS_VOICEOFF
mdefine_line|#define GUS_VOICEOFF(chn, voice)&t;&t;_GUS_CMD(chn, voice, _GUS_VOICEOFF, 0, 0)
DECL|macro|GUS_VOICEFADE
mdefine_line|#define GUS_VOICEFADE(chn, voice)&t;&t;_GUS_CMD(chn, voice, _GUS_VOICEFADE, 0, 0)
DECL|macro|GUS_VOICEMODE
mdefine_line|#define GUS_VOICEMODE(chn, voice, p1)&t;&t;_GUS_CMD(chn, voice, _GUS_VOICEMODE, (p1), 0)
DECL|macro|GUS_VOICEBALA
mdefine_line|#define GUS_VOICEBALA(chn, voice, p1)&t;&t;_GUS_CMD(chn, voice, _GUS_VOICEBALA, (p1), 0)
DECL|macro|GUS_VOICEFREQ
mdefine_line|#define GUS_VOICEFREQ(chn, voice, p)&t;&t;_GUS_CMD(chn, voice, _GUS_VOICEFREQ, &bslash;&n;&t;&t;&t;&t;&t;&t;&t;(p) &amp; 0xffff, ((p) &gt;&gt; 16) &amp; 0xffff)
DECL|macro|GUS_VOICEVOL
mdefine_line|#define GUS_VOICEVOL(chn, voice, p1)&t;&t;_GUS_CMD(chn, voice, _GUS_VOICEVOL, (p1), 0)
DECL|macro|GUS_VOICEVOL2
mdefine_line|#define GUS_VOICEVOL2(chn, voice, p1)&t;&t;_GUS_CMD(chn, voice, _GUS_VOICEVOL2, (p1), 0)
DECL|macro|GUS_RAMPRANGE
mdefine_line|#define GUS_RAMPRANGE(chn, voice, low, high)&t;_GUS_CMD(chn, voice, _GUS_RAMPRANGE, (low), (high))
DECL|macro|GUS_RAMPRATE
mdefine_line|#define GUS_RAMPRATE(chn, voice, p1, p2)&t;_GUS_CMD(chn, voice, _GUS_RAMPRATE, (p1), (p2))
DECL|macro|GUS_RAMPMODE
mdefine_line|#define GUS_RAMPMODE(chn, voice, p1)&t;&t;_GUS_CMD(chn, voice, _GUS_RAMPMODE, (p1), 0)
DECL|macro|GUS_RAMPON
mdefine_line|#define GUS_RAMPON(chn, voice, p1)&t;&t;_GUS_CMD(chn, voice, _GUS_RAMPON, (p1), 0)
DECL|macro|GUS_RAMPOFF
mdefine_line|#define GUS_RAMPOFF(chn, voice)&t;&t;&t;_GUS_CMD(chn, voice, _GUS_RAMPOFF, 0, 0)
DECL|macro|GUS_VOLUME_SCALE
mdefine_line|#define GUS_VOLUME_SCALE(chn, voice, p1, p2)&t;_GUS_CMD(chn, voice, _GUS_VOLUME_SCALE, (p1), (p2))
DECL|macro|GUS_VOICE_POS
mdefine_line|#define GUS_VOICE_POS(chn, voice, p)&t;&t;_GUS_CMD(chn, voice, _GUS_VOICE_POS, &bslash;&n;&t;&t;&t;&t;&t;&t;&t;(p) &amp; 0xffff, ((p) &gt;&gt; 16) &amp; 0xffff)
macro_line|#endif
eof
