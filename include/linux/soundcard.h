macro_line|#ifndef SOUNDCARD_H
DECL|macro|SOUNDCARD_H
mdefine_line|#define SOUNDCARD_H
multiline_comment|/*&n; * Copyright by Hannu Savolainen 1993-1997&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions are&n; * met: 1. Redistributions of source code must retain the above copyright&n; * notice, this list of conditions and the following disclaimer. 2.&n; * Redistributions in binary form must reproduce the above copyright notice,&n; * this list of conditions and the following disclaimer in the documentation&n; * and/or other materials provided with the distribution.&n; *&n; * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS&squot;&squot; AND ANY&n; * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED&n; * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE&n; * DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR&n; * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR&n; * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER&n; * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT&n; * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY&n; * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF&n; * SUCH DAMAGE.&n; */
multiline_comment|/*&n; * OSS interface version. With versions earlier than 3.6 this value is&n; * an integer with value less than 361. In versions 3.6 and later&n; * it&squot;s a six digit hexadecimal value. For example value&n; * of 0x030600 represents OSS version 3.6.0.&n; * Use ioctl(fd, OSS_GETVERSION, &amp;int) to get the version number of&n; * the currently active driver.&n; */
DECL|macro|SOUND_VERSION
mdefine_line|#define SOUND_VERSION&t;0x030802
DECL|macro|OPEN_SOUND_SYSTEM
mdefine_line|#define OPEN_SOUND_SYSTEM
multiline_comment|/* In Linux we need to be prepared for cross compiling */
macro_line|#include &lt;linux/ioctl.h&gt;
multiline_comment|/*&n; *&t;Supported card ID numbers (Should be somewhere else?)&n; */
DECL|macro|SNDCARD_ADLIB
mdefine_line|#define SNDCARD_ADLIB&t;&t;1
DECL|macro|SNDCARD_SB
mdefine_line|#define SNDCARD_SB&t;&t;2
DECL|macro|SNDCARD_PAS
mdefine_line|#define SNDCARD_PAS&t;&t;3
DECL|macro|SNDCARD_GUS
mdefine_line|#define SNDCARD_GUS&t;&t;4
DECL|macro|SNDCARD_MPU401
mdefine_line|#define SNDCARD_MPU401&t;&t;5
DECL|macro|SNDCARD_SB16
mdefine_line|#define SNDCARD_SB16&t;&t;6
DECL|macro|SNDCARD_SB16MIDI
mdefine_line|#define SNDCARD_SB16MIDI&t;7
DECL|macro|SNDCARD_UART6850
mdefine_line|#define SNDCARD_UART6850&t;8
DECL|macro|SNDCARD_GUS16
mdefine_line|#define SNDCARD_GUS16&t;&t;9
DECL|macro|SNDCARD_MSS
mdefine_line|#define SNDCARD_MSS&t;&t;10
DECL|macro|SNDCARD_PSS
mdefine_line|#define SNDCARD_PSS     &t;11
DECL|macro|SNDCARD_SSCAPE
mdefine_line|#define SNDCARD_SSCAPE&t;&t;12
DECL|macro|SNDCARD_PSS_MPU
mdefine_line|#define SNDCARD_PSS_MPU     &t;13
DECL|macro|SNDCARD_PSS_MSS
mdefine_line|#define SNDCARD_PSS_MSS     &t;14
DECL|macro|SNDCARD_SSCAPE_MSS
mdefine_line|#define SNDCARD_SSCAPE_MSS&t;15
DECL|macro|SNDCARD_TRXPRO
mdefine_line|#define SNDCARD_TRXPRO&t;&t;16
DECL|macro|SNDCARD_TRXPRO_SB
mdefine_line|#define SNDCARD_TRXPRO_SB&t;17
DECL|macro|SNDCARD_TRXPRO_MPU
mdefine_line|#define SNDCARD_TRXPRO_MPU&t;18
DECL|macro|SNDCARD_MAD16
mdefine_line|#define SNDCARD_MAD16&t;&t;19
DECL|macro|SNDCARD_MAD16_MPU
mdefine_line|#define SNDCARD_MAD16_MPU&t;20
DECL|macro|SNDCARD_CS4232
mdefine_line|#define SNDCARD_CS4232&t;&t;21
DECL|macro|SNDCARD_CS4232_MPU
mdefine_line|#define SNDCARD_CS4232_MPU&t;22
DECL|macro|SNDCARD_MAUI
mdefine_line|#define SNDCARD_MAUI&t;&t;23
DECL|macro|SNDCARD_PSEUDO_MSS
mdefine_line|#define SNDCARD_PSEUDO_MSS&t;24
DECL|macro|SNDCARD_GUSPNP
mdefine_line|#define SNDCARD_GUSPNP&t;&t;25
DECL|macro|SNDCARD_UART401
mdefine_line|#define SNDCARD_UART401&t;&t;26
multiline_comment|/* Sound card numbers 27 to N are reserved. Don&squot;t add more numbers here. */
multiline_comment|/***********************************&n; * IOCTL Commands for /dev/sequencer&n; */
macro_line|#ifndef _SIOWR
macro_line|#if defined(_IOWR) &amp;&amp; (defined(_AIX) || (!defined(sun) &amp;&amp; !defined(sparc) &amp;&amp; !defined(__sparc__) &amp;&amp; !defined(__INCioctlh) &amp;&amp; !defined(__Lynx__)))
multiline_comment|/* Use already defined ioctl defines if they exist (except with Sun or Sparc) */
DECL|macro|SIOCPARM_MASK
mdefine_line|#define&t;SIOCPARM_MASK&t;IOCPARM_MASK
DECL|macro|SIOC_VOID
mdefine_line|#define&t;SIOC_VOID&t;IOC_VOID
DECL|macro|SIOC_OUT
mdefine_line|#define&t;SIOC_OUT&t;IOC_OUT
DECL|macro|SIOC_IN
mdefine_line|#define&t;SIOC_IN&t;&t;IOC_IN
DECL|macro|SIOC_INOUT
mdefine_line|#define&t;SIOC_INOUT&t;IOC_INOUT
DECL|macro|_SIOC_SIZE
mdefine_line|#define _SIOC_SIZE&t;_IOC_SIZE
DECL|macro|_SIOC_DIR
mdefine_line|#define _SIOC_DIR&t;_IOC_DIR
DECL|macro|_SIOC_NONE
mdefine_line|#define _SIOC_NONE&t;_IOC_NONE
DECL|macro|_SIOC_READ
mdefine_line|#define _SIOC_READ&t;_IOC_READ
DECL|macro|_SIOC_WRITE
mdefine_line|#define _SIOC_WRITE&t;_IOC_WRITE
DECL|macro|_SIO
mdefine_line|#define&t;_SIO&t;&t;_IO
DECL|macro|_SIOR
mdefine_line|#define&t;_SIOR&t;&t;_IOR
DECL|macro|_SIOW
mdefine_line|#define&t;_SIOW&t;&t;_IOW
DECL|macro|_SIOWR
mdefine_line|#define&t;_SIOWR&t;&t;_IOWR
macro_line|#else
multiline_comment|/* Ioctl&squot;s have the command encoded in the lower word,&n; * and the size of any in or out parameters in the upper&n; * word.  The high 2 bits of the upper word are used&n; * to encode the in/out status of the parameter; for now&n; * we restrict parameters to at most 8191 bytes.&n; */
multiline_comment|/* #define&t;SIOCTYPE&t;&t;(0xff&lt;&lt;8) */
DECL|macro|SIOCPARM_MASK
mdefine_line|#define&t;SIOCPARM_MASK&t;0x1fff&t;&t;/* parameters must be &lt; 8192 bytes */
DECL|macro|SIOC_VOID
mdefine_line|#define&t;SIOC_VOID&t;0x00000000&t;/* no parameters */
DECL|macro|SIOC_OUT
mdefine_line|#define&t;SIOC_OUT&t;0x20000000&t;/* copy out parameters */
DECL|macro|SIOC_IN
mdefine_line|#define&t;SIOC_IN&t;&t;0x40000000&t;/* copy in parameters */
DECL|macro|SIOC_INOUT
mdefine_line|#define&t;SIOC_INOUT&t;(SIOC_IN|SIOC_OUT)
multiline_comment|/* the 0x20000000 is so we can distinguish new ioctl&squot;s from old */
DECL|macro|_SIO
mdefine_line|#define&t;_SIO(x,y)&t;((int)(SIOC_VOID|(x&lt;&lt;8)|y))
DECL|macro|_SIOR
mdefine_line|#define&t;_SIOR(x,y,t)&t;((int)(SIOC_OUT|((sizeof(t)&amp;SIOCPARM_MASK)&lt;&lt;16)|(x&lt;&lt;8)|y))
DECL|macro|_SIOW
mdefine_line|#define&t;_SIOW(x,y,t)&t;((int)(SIOC_IN|((sizeof(t)&amp;SIOCPARM_MASK)&lt;&lt;16)|(x&lt;&lt;8)|y))
multiline_comment|/* this should be _SIORW, but stdio got there first */
DECL|macro|_SIOWR
mdefine_line|#define&t;_SIOWR(x,y,t)&t;((int)(SIOC_INOUT|((sizeof(t)&amp;SIOCPARM_MASK)&lt;&lt;16)|(x&lt;&lt;8)|y))
DECL|macro|_SIOC_SIZE
mdefine_line|#define _SIOC_SIZE(x)&t;((x&gt;&gt;16)&amp;SIOCPARM_MASK)&t;
DECL|macro|_SIOC_DIR
mdefine_line|#define _SIOC_DIR(x)&t;(x &amp; 0xf0000000)
DECL|macro|_SIOC_NONE
mdefine_line|#define _SIOC_NONE&t;SIOC_VOID
DECL|macro|_SIOC_READ
mdefine_line|#define _SIOC_READ&t;SIOC_OUT
DECL|macro|_SIOC_WRITE
mdefine_line|#define _SIOC_WRITE&t;SIOC_IN
macro_line|#  endif /* _IOWR */
macro_line|#endif  /* !_SIOWR */
DECL|macro|SNDCTL_SEQ_RESET
mdefine_line|#define SNDCTL_SEQ_RESET&t;&t;_SIO  (&squot;Q&squot;, 0)
DECL|macro|SNDCTL_SEQ_SYNC
mdefine_line|#define SNDCTL_SEQ_SYNC&t;&t;&t;_SIO  (&squot;Q&squot;, 1)
DECL|macro|SNDCTL_SYNTH_INFO
mdefine_line|#define SNDCTL_SYNTH_INFO&t;&t;_SIOWR(&squot;Q&squot;, 2, struct synth_info)
DECL|macro|SNDCTL_SEQ_CTRLRATE
mdefine_line|#define SNDCTL_SEQ_CTRLRATE&t;&t;_SIOWR(&squot;Q&squot;, 3, int)&t;/* Set/get timer resolution (HZ) */
DECL|macro|SNDCTL_SEQ_GETOUTCOUNT
mdefine_line|#define SNDCTL_SEQ_GETOUTCOUNT&t;&t;_SIOR (&squot;Q&squot;, 4, int)
DECL|macro|SNDCTL_SEQ_GETINCOUNT
mdefine_line|#define SNDCTL_SEQ_GETINCOUNT&t;&t;_SIOR (&squot;Q&squot;, 5, int)
DECL|macro|SNDCTL_SEQ_PERCMODE
mdefine_line|#define SNDCTL_SEQ_PERCMODE&t;&t;_SIOW (&squot;Q&squot;, 6, int)
DECL|macro|SNDCTL_FM_LOAD_INSTR
mdefine_line|#define SNDCTL_FM_LOAD_INSTR&t;&t;_SIOW (&squot;Q&squot;, 7, struct sbi_instrument)&t;/* Obsolete. Don&squot;t use!!!!!! */
DECL|macro|SNDCTL_SEQ_TESTMIDI
mdefine_line|#define SNDCTL_SEQ_TESTMIDI&t;&t;_SIOW (&squot;Q&squot;, 8, int)
DECL|macro|SNDCTL_SEQ_RESETSAMPLES
mdefine_line|#define SNDCTL_SEQ_RESETSAMPLES&t;&t;_SIOW (&squot;Q&squot;, 9, int)
DECL|macro|SNDCTL_SEQ_NRSYNTHS
mdefine_line|#define SNDCTL_SEQ_NRSYNTHS&t;&t;_SIOR (&squot;Q&squot;,10, int)
DECL|macro|SNDCTL_SEQ_NRMIDIS
mdefine_line|#define SNDCTL_SEQ_NRMIDIS&t;&t;_SIOR (&squot;Q&squot;,11, int)
DECL|macro|SNDCTL_MIDI_INFO
mdefine_line|#define SNDCTL_MIDI_INFO&t;&t;_SIOWR(&squot;Q&squot;,12, struct midi_info)
DECL|macro|SNDCTL_SEQ_THRESHOLD
mdefine_line|#define SNDCTL_SEQ_THRESHOLD&t;&t;_SIOW (&squot;Q&squot;,13, int)
DECL|macro|SNDCTL_SYNTH_MEMAVL
mdefine_line|#define SNDCTL_SYNTH_MEMAVL&t;&t;_SIOWR(&squot;Q&squot;,14, int)&t;/* in=dev#, out=memsize */
DECL|macro|SNDCTL_FM_4OP_ENABLE
mdefine_line|#define SNDCTL_FM_4OP_ENABLE&t;&t;_SIOW (&squot;Q&squot;,15, int)&t;/* in=dev# */
DECL|macro|SNDCTL_SEQ_PANIC
mdefine_line|#define SNDCTL_SEQ_PANIC&t;&t;_SIO  (&squot;Q&squot;,17)
DECL|macro|SNDCTL_SEQ_OUTOFBAND
mdefine_line|#define SNDCTL_SEQ_OUTOFBAND&t;&t;_SIOW (&squot;Q&squot;,18, struct seq_event_rec)
DECL|macro|SNDCTL_SEQ_GETTIME
mdefine_line|#define SNDCTL_SEQ_GETTIME&t;&t;_SIOR (&squot;Q&squot;,19, int)
DECL|macro|SNDCTL_SYNTH_ID
mdefine_line|#define SNDCTL_SYNTH_ID&t;&t;&t;_SIOWR(&squot;Q&squot;,20, struct synth_info)
DECL|macro|SNDCTL_SYNTH_CONTROL
mdefine_line|#define SNDCTL_SYNTH_CONTROL&t;&t;_SIOWR(&squot;Q&squot;,21, struct synth_control)
DECL|macro|SNDCTL_SYNTH_REMOVESAMPLE
mdefine_line|#define SNDCTL_SYNTH_REMOVESAMPLE&t;_SIOWR(&squot;Q&squot;,22, struct remove_sample)
DECL|struct|synth_control
r_typedef
r_struct
id|synth_control
(brace
DECL|member|devno
r_int
id|devno
suffix:semicolon
multiline_comment|/* Synthesizer # */
DECL|member|data
r_char
id|data
(braket
l_int|4000
)braket
suffix:semicolon
multiline_comment|/* Device spesific command/data record */
DECL|typedef|synth_control
)brace
id|synth_control
suffix:semicolon
DECL|struct|remove_sample
r_typedef
r_struct
id|remove_sample
(brace
DECL|member|devno
r_int
id|devno
suffix:semicolon
multiline_comment|/* Synthesizer # */
DECL|member|bankno
r_int
id|bankno
suffix:semicolon
multiline_comment|/* MIDI bank # (0=General MIDI) */
DECL|member|instrno
r_int
id|instrno
suffix:semicolon
multiline_comment|/* MIDI instrument number */
DECL|typedef|remove_sample
)brace
id|remove_sample
suffix:semicolon
DECL|struct|seq_event_rec
r_typedef
r_struct
id|seq_event_rec
(brace
DECL|member|arr
r_int
r_char
id|arr
(braket
l_int|8
)braket
suffix:semicolon
DECL|typedef|seq_event_rec
)brace
id|seq_event_rec
suffix:semicolon
DECL|macro|SNDCTL_TMR_TIMEBASE
mdefine_line|#define SNDCTL_TMR_TIMEBASE&t;&t;_SIOWR(&squot;T&squot;, 1, int)
DECL|macro|SNDCTL_TMR_START
mdefine_line|#define SNDCTL_TMR_START&t;&t;_SIO  (&squot;T&squot;, 2)
DECL|macro|SNDCTL_TMR_STOP
mdefine_line|#define SNDCTL_TMR_STOP&t;&t;&t;_SIO  (&squot;T&squot;, 3)
DECL|macro|SNDCTL_TMR_CONTINUE
mdefine_line|#define SNDCTL_TMR_CONTINUE&t;&t;_SIO  (&squot;T&squot;, 4)
DECL|macro|SNDCTL_TMR_TEMPO
mdefine_line|#define SNDCTL_TMR_TEMPO&t;&t;_SIOWR(&squot;T&squot;, 5, int)
DECL|macro|SNDCTL_TMR_SOURCE
mdefine_line|#define SNDCTL_TMR_SOURCE&t;&t;_SIOWR(&squot;T&squot;, 6, int)
DECL|macro|TMR_INTERNAL
macro_line|#&t;define TMR_INTERNAL&t;&t;0x00000001
DECL|macro|TMR_EXTERNAL
macro_line|#&t;define TMR_EXTERNAL&t;&t;0x00000002
DECL|macro|TMR_MODE_MIDI
macro_line|#&t;&t;define TMR_MODE_MIDI&t;0x00000010
DECL|macro|TMR_MODE_FSK
macro_line|#&t;&t;define TMR_MODE_FSK&t;0x00000020
DECL|macro|TMR_MODE_CLS
macro_line|#&t;&t;define TMR_MODE_CLS&t;0x00000040
DECL|macro|TMR_MODE_SMPTE
macro_line|#&t;&t;define TMR_MODE_SMPTE&t;0x00000080
DECL|macro|SNDCTL_TMR_METRONOME
mdefine_line|#define SNDCTL_TMR_METRONOME&t;&t;_SIOW (&squot;T&squot;, 7, int)
DECL|macro|SNDCTL_TMR_SELECT
mdefine_line|#define SNDCTL_TMR_SELECT&t;&t;_SIOW (&squot;T&squot;, 8, int)
multiline_comment|/*&n; * Some big endian/little endian handling macros&n; */
macro_line|#if defined(_AIX) || defined(AIX) || defined(sparc) || defined(__sparc__) || defined(HPPA) || defined(PPC)
multiline_comment|/* Big endian machines */
DECL|macro|_PATCHKEY
macro_line|#  define _PATCHKEY(id) (0xfd00|id)
DECL|macro|AFMT_S16_NE
macro_line|#  define AFMT_S16_NE AFMT_S16_BE
macro_line|#else
DECL|macro|_PATCHKEY
macro_line|#  define _PATCHKEY(id) ((id&lt;&lt;8)|0xfd)
DECL|macro|AFMT_S16_NE
macro_line|#  define AFMT_S16_NE AFMT_S16_LE
macro_line|#endif
multiline_comment|/*&n; *&t;Sample loading mechanism for internal synthesizers (/dev/sequencer)&n; *&t;The following patch_info structure has been designed to support&n; *&t;Gravis UltraSound. It tries to be universal format for uploading&n; *&t;sample based patches but is probably too limited.&n; *&n; *      (PBD) As Hannu guessed, the GUS structure is too limited for &n; *      the WaveFront, but this is the right place for a constant definition.&n; */
DECL|struct|patch_info
r_struct
id|patch_info
(brace
DECL|member|key
r_int
r_int
id|key
suffix:semicolon
multiline_comment|/* Use WAVE_PATCH here */
DECL|macro|WAVE_PATCH
mdefine_line|#define WAVE_PATCH&t;   _PATCHKEY(0x04)
DECL|macro|GUS_PATCH
mdefine_line|#define GUS_PATCH&t;   WAVE_PATCH
DECL|macro|WAVEFRONT_PATCH
mdefine_line|#define WAVEFRONT_PATCH    _PATCHKEY(0x06)
DECL|member|device_no
r_int
id|device_no
suffix:semicolon
multiline_comment|/* Synthesizer number */
DECL|member|instr_no
r_int
id|instr_no
suffix:semicolon
multiline_comment|/* Midi pgm# */
DECL|member|mode
r_int
r_int
id|mode
suffix:semicolon
multiline_comment|/*&n; * The least significant byte has the same format than the GUS .PAT&n; * files&n; */
DECL|macro|WAVE_16_BITS
mdefine_line|#define WAVE_16_BITS&t;0x01&t;/* bit 0 = 8 or 16 bit wave data. */
DECL|macro|WAVE_UNSIGNED
mdefine_line|#define WAVE_UNSIGNED&t;0x02&t;/* bit 1 = Signed - Unsigned data. */
DECL|macro|WAVE_LOOPING
mdefine_line|#define WAVE_LOOPING&t;0x04&t;/* bit 2 = looping enabled-1. */
DECL|macro|WAVE_BIDIR_LOOP
mdefine_line|#define WAVE_BIDIR_LOOP&t;0x08&t;/* bit 3 = Set is bidirectional looping. */
DECL|macro|WAVE_LOOP_BACK
mdefine_line|#define WAVE_LOOP_BACK&t;0x10&t;/* bit 4 = Set is looping backward. */
DECL|macro|WAVE_SUSTAIN_ON
mdefine_line|#define WAVE_SUSTAIN_ON&t;0x20&t;/* bit 5 = Turn sustaining on. (Env. pts. 3)*/
DECL|macro|WAVE_ENVELOPES
mdefine_line|#define WAVE_ENVELOPES&t;0x40&t;/* bit 6 = Enable envelopes - 1 */
DECL|macro|WAVE_FAST_RELEASE
mdefine_line|#define WAVE_FAST_RELEASE 0x80&t;/* bit 7 = Shut off immediately after note off */
multiline_comment|/* &t;(use the env_rate/env_offs fields). */
multiline_comment|/* Linux specific bits */
DECL|macro|WAVE_VIBRATO
mdefine_line|#define WAVE_VIBRATO&t;0x00010000&t;/* The vibrato info is valid */
DECL|macro|WAVE_TREMOLO
mdefine_line|#define WAVE_TREMOLO&t;0x00020000&t;/* The tremolo info is valid */
DECL|macro|WAVE_SCALE
mdefine_line|#define WAVE_SCALE&t;0x00040000&t;/* The scaling info is valid */
DECL|macro|WAVE_FRACTIONS
mdefine_line|#define WAVE_FRACTIONS&t;0x00080000&t;/* Fraction information is valid */
multiline_comment|/* Reserved bits */
DECL|macro|WAVE_ROM
mdefine_line|#define WAVE_ROM&t;0x40000000&t;/* For future use */
DECL|macro|WAVE_MULAW
mdefine_line|#define WAVE_MULAW&t;0x20000000&t;/* For future use */
multiline_comment|/* Other bits must be zeroed */
DECL|member|len
r_int
id|len
suffix:semicolon
multiline_comment|/* Size of the wave data in bytes */
DECL|member|loop_start
DECL|member|loop_end
r_int
id|loop_start
comma
id|loop_end
suffix:semicolon
multiline_comment|/* Byte offsets from the beginning */
multiline_comment|/* &n; * The base_freq and base_note fields are used when computing the&n; * playback speed for a note. The base_note defines the tone frequency&n; * which is heard if the sample is played using the base_freq as the&n; * playback speed.&n; *&n; * The low_note and high_note fields define the minimum and maximum note&n; * frequencies for which this sample is valid. It is possible to define&n; * more than one samples for an instrument number at the same time. The&n; * low_note and high_note fields are used to select the most suitable one.&n; *&n; * The fields base_note, high_note and low_note should contain&n; * the note frequency multiplied by 1000. For example value for the&n; * middle A is 440*1000.&n; */
DECL|member|base_freq
r_int
r_int
id|base_freq
suffix:semicolon
DECL|member|base_note
r_int
r_int
id|base_note
suffix:semicolon
DECL|member|high_note
r_int
r_int
id|high_note
suffix:semicolon
DECL|member|low_note
r_int
r_int
id|low_note
suffix:semicolon
DECL|member|panning
r_int
id|panning
suffix:semicolon
multiline_comment|/* -128=left, 127=right */
DECL|member|detuning
r_int
id|detuning
suffix:semicolon
multiline_comment|/*&t;New fields introduced in version 1.99.5&t;*/
multiline_comment|/* Envelope. Enabled by mode bit WAVE_ENVELOPES&t;*/
DECL|member|env_rate
r_int
r_char
id|env_rate
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* GUS HW ramping rate */
DECL|member|env_offset
r_int
r_char
id|env_offset
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* 255 == 100% */
multiline_comment|/* &n;&t; * The tremolo, vibrato and scale info are not supported yet.&n;&t; * Enable by setting the mode bits WAVE_TREMOLO, WAVE_VIBRATO or&n;&t; * WAVE_SCALE&n;&t; */
DECL|member|tremolo_sweep
r_int
r_char
id|tremolo_sweep
suffix:semicolon
DECL|member|tremolo_rate
r_int
r_char
id|tremolo_rate
suffix:semicolon
DECL|member|tremolo_depth
r_int
r_char
id|tremolo_depth
suffix:semicolon
DECL|member|vibrato_sweep
r_int
r_char
id|vibrato_sweep
suffix:semicolon
DECL|member|vibrato_rate
r_int
r_char
id|vibrato_rate
suffix:semicolon
DECL|member|vibrato_depth
r_int
r_char
id|vibrato_depth
suffix:semicolon
DECL|member|scale_frequency
r_int
id|scale_frequency
suffix:semicolon
DECL|member|scale_factor
r_int
r_int
id|scale_factor
suffix:semicolon
multiline_comment|/* from 0 to 2048 or 0 to 2 */
DECL|member|volume
r_int
id|volume
suffix:semicolon
DECL|member|fractions
r_int
id|fractions
suffix:semicolon
DECL|member|reserved1
r_int
id|reserved1
suffix:semicolon
DECL|member|spare
r_int
id|spare
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|data
r_char
id|data
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* The waveform data starts here */
)brace
suffix:semicolon
DECL|struct|sysex_info
r_struct
id|sysex_info
(brace
DECL|member|key
r_int
id|key
suffix:semicolon
multiline_comment|/* Use SYSEX_PATCH or MAUI_PATCH here */
DECL|macro|SYSEX_PATCH
mdefine_line|#define SYSEX_PATCH&t;_PATCHKEY(0x05)
DECL|macro|MAUI_PATCH
mdefine_line|#define MAUI_PATCH&t;_PATCHKEY(0x06)
DECL|member|device_no
r_int
id|device_no
suffix:semicolon
multiline_comment|/* Synthesizer number */
DECL|member|len
r_int
id|len
suffix:semicolon
multiline_comment|/* Size of the sysex data in bytes */
DECL|member|data
r_int
r_char
id|data
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* Sysex data starts here */
)brace
suffix:semicolon
multiline_comment|/*&n; * /dev/sequencer input events.&n; *&n; * The data written to the /dev/sequencer is a stream of events. Events&n; * are records of 4 or 8 bytes. The first byte defines the size. &n; * Any number of events can be written with a write call. There&n; * is a set of macros for sending these events. Use these macros if you&n; * want to maximize portability of your program.&n; *&n; * Events SEQ_WAIT, SEQ_MIDIPUTC and SEQ_ECHO. Are also input events.&n; * (All input events are currently 4 bytes long. Be prepared to support&n; * 8 byte events also. If you receive any event having first byte &gt;= 128,&n; * it&squot;s a 8 byte event.&n; *&n; * The events are documented at the end of this file.&n; *&n; * Normal events (4 bytes)&n; * There is also a 8 byte version of most of the 4 byte events. The&n; * 8 byte one is recommended.&n; */
DECL|macro|SEQ_NOTEOFF
mdefine_line|#define SEQ_NOTEOFF&t;&t;0
DECL|macro|SEQ_FMNOTEOFF
mdefine_line|#define SEQ_FMNOTEOFF&t;&t;SEQ_NOTEOFF&t;/* Just old name */
DECL|macro|SEQ_NOTEON
mdefine_line|#define SEQ_NOTEON&t;&t;1
DECL|macro|SEQ_FMNOTEON
mdefine_line|#define&t;SEQ_FMNOTEON&t;&t;SEQ_NOTEON
DECL|macro|SEQ_WAIT
mdefine_line|#define SEQ_WAIT&t;&t;TMR_WAIT_ABS
DECL|macro|SEQ_PGMCHANGE
mdefine_line|#define SEQ_PGMCHANGE&t;&t;3
DECL|macro|SEQ_FMPGMCHANGE
mdefine_line|#define SEQ_FMPGMCHANGE&t;&t;SEQ_PGMCHANGE
DECL|macro|SEQ_SYNCTIMER
mdefine_line|#define SEQ_SYNCTIMER&t;&t;TMR_START
DECL|macro|SEQ_MIDIPUTC
mdefine_line|#define SEQ_MIDIPUTC&t;&t;5
DECL|macro|SEQ_DRUMON
mdefine_line|#define SEQ_DRUMON&t;&t;6&t;/*** OBSOLETE ***/
DECL|macro|SEQ_DRUMOFF
mdefine_line|#define SEQ_DRUMOFF&t;&t;7&t;/*** OBSOLETE ***/
DECL|macro|SEQ_ECHO
mdefine_line|#define SEQ_ECHO&t;&t;TMR_ECHO&t;/* For synching programs with output */
DECL|macro|SEQ_AFTERTOUCH
mdefine_line|#define SEQ_AFTERTOUCH&t;&t;9
DECL|macro|SEQ_CONTROLLER
mdefine_line|#define SEQ_CONTROLLER&t;&t;10
multiline_comment|/*******************************************&n; *&t;Midi controller numbers&n; *******************************************&n; * Controllers 0 to 31 (0x00 to 0x1f) and&n; * 32 to 63 (0x20 to 0x3f) are continuous&n; * controllers.&n; * In the MIDI 1.0 these controllers are sent using&n; * two messages. Controller numbers 0 to 31 are used&n; * to send the MSB and the controller numbers 32 to 63&n; * are for the LSB. Note that just 7 bits are used in MIDI bytes.&n; */
DECL|macro|CTL_BANK_SELECT
mdefine_line|#define&t;   CTL_BANK_SELECT&t;&t;0x00
DECL|macro|CTL_MODWHEEL
mdefine_line|#define&t;   CTL_MODWHEEL&t;&t;&t;0x01
DECL|macro|CTL_BREATH
mdefine_line|#define    CTL_BREATH&t;&t;&t;0x02
multiline_comment|/*&t;&t;undefined&t;&t;0x03 */
DECL|macro|CTL_FOOT
mdefine_line|#define    CTL_FOOT&t;&t;&t;0x04
DECL|macro|CTL_PORTAMENTO_TIME
mdefine_line|#define    CTL_PORTAMENTO_TIME&t;&t;0x05
DECL|macro|CTL_DATA_ENTRY
mdefine_line|#define    CTL_DATA_ENTRY&t;&t;0x06
DECL|macro|CTL_MAIN_VOLUME
mdefine_line|#define    CTL_MAIN_VOLUME&t;&t;0x07
DECL|macro|CTL_BALANCE
mdefine_line|#define    CTL_BALANCE&t;&t;&t;0x08
multiline_comment|/*&t;&t;undefined&t;&t;0x09 */
DECL|macro|CTL_PAN
mdefine_line|#define    CTL_PAN&t;&t;&t;0x0a
DECL|macro|CTL_EXPRESSION
mdefine_line|#define    CTL_EXPRESSION&t;&t;0x0b
multiline_comment|/*&t;&t;undefined&t;&t;0x0c */
multiline_comment|/*&t;&t;undefined&t;&t;0x0d */
multiline_comment|/*&t;&t;undefined&t;&t;0x0e */
multiline_comment|/*&t;&t;undefined&t;&t;0x0f */
DECL|macro|CTL_GENERAL_PURPOSE1
mdefine_line|#define    CTL_GENERAL_PURPOSE1&t;0x10
DECL|macro|CTL_GENERAL_PURPOSE2
mdefine_line|#define    CTL_GENERAL_PURPOSE2&t;0x11
DECL|macro|CTL_GENERAL_PURPOSE3
mdefine_line|#define    CTL_GENERAL_PURPOSE3&t;0x12
DECL|macro|CTL_GENERAL_PURPOSE4
mdefine_line|#define    CTL_GENERAL_PURPOSE4&t;0x13
multiline_comment|/*&t;&t;undefined&t;&t;0x14 - 0x1f */
multiline_comment|/*&t;&t;undefined&t;&t;0x20 */
multiline_comment|/* The controller numbers 0x21 to 0x3f are reserved for the */
multiline_comment|/* least significant bytes of the controllers 0x00 to 0x1f. */
multiline_comment|/* These controllers are not recognised by the driver. */
multiline_comment|/* Controllers 64 to 69 (0x40 to 0x45) are on/off switches. */
multiline_comment|/* 0=OFF and 127=ON (intermediate values are possible) */
DECL|macro|CTL_DAMPER_PEDAL
mdefine_line|#define    CTL_DAMPER_PEDAL&t;&t;0x40
DECL|macro|CTL_SUSTAIN
mdefine_line|#define    CTL_SUSTAIN&t;&t;&t;0x40&t;/* Alias */
DECL|macro|CTL_HOLD
mdefine_line|#define    CTL_HOLD&t;&t;&t;0x40&t;/* Alias */
DECL|macro|CTL_PORTAMENTO
mdefine_line|#define    CTL_PORTAMENTO&t;&t;0x41
DECL|macro|CTL_SOSTENUTO
mdefine_line|#define    CTL_SOSTENUTO&t;&t;0x42
DECL|macro|CTL_SOFT_PEDAL
mdefine_line|#define    CTL_SOFT_PEDAL&t;&t;0x43
multiline_comment|/*&t;&t;undefined&t;&t;0x44 */
DECL|macro|CTL_HOLD2
mdefine_line|#define    CTL_HOLD2&t;&t;&t;0x45
multiline_comment|/*&t;&t;undefined&t;&t;0x46 - 0x4f */
DECL|macro|CTL_GENERAL_PURPOSE5
mdefine_line|#define    CTL_GENERAL_PURPOSE5&t;0x50
DECL|macro|CTL_GENERAL_PURPOSE6
mdefine_line|#define    CTL_GENERAL_PURPOSE6&t;0x51
DECL|macro|CTL_GENERAL_PURPOSE7
mdefine_line|#define    CTL_GENERAL_PURPOSE7&t;0x52
DECL|macro|CTL_GENERAL_PURPOSE8
mdefine_line|#define    CTL_GENERAL_PURPOSE8&t;0x53
multiline_comment|/*&t;&t;undefined&t;&t;0x54 - 0x5a */
DECL|macro|CTL_EXT_EFF_DEPTH
mdefine_line|#define    CTL_EXT_EFF_DEPTH&t;&t;0x5b
DECL|macro|CTL_TREMOLO_DEPTH
mdefine_line|#define    CTL_TREMOLO_DEPTH&t;&t;0x5c
DECL|macro|CTL_CHORUS_DEPTH
mdefine_line|#define    CTL_CHORUS_DEPTH&t;&t;0x5d
DECL|macro|CTL_DETUNE_DEPTH
mdefine_line|#define    CTL_DETUNE_DEPTH&t;&t;0x5e
DECL|macro|CTL_CELESTE_DEPTH
mdefine_line|#define    CTL_CELESTE_DEPTH&t;&t;0x5e&t;/* Alias for the above one */
DECL|macro|CTL_PHASER_DEPTH
mdefine_line|#define    CTL_PHASER_DEPTH&t;&t;0x5f
DECL|macro|CTL_DATA_INCREMENT
mdefine_line|#define    CTL_DATA_INCREMENT&t;&t;0x60
DECL|macro|CTL_DATA_DECREMENT
mdefine_line|#define    CTL_DATA_DECREMENT&t;&t;0x61
DECL|macro|CTL_NONREG_PARM_NUM_LSB
mdefine_line|#define    CTL_NONREG_PARM_NUM_LSB&t;0x62
DECL|macro|CTL_NONREG_PARM_NUM_MSB
mdefine_line|#define    CTL_NONREG_PARM_NUM_MSB&t;0x63
DECL|macro|CTL_REGIST_PARM_NUM_LSB
mdefine_line|#define    CTL_REGIST_PARM_NUM_LSB&t;0x64
DECL|macro|CTL_REGIST_PARM_NUM_MSB
mdefine_line|#define    CTL_REGIST_PARM_NUM_MSB&t;0x65
multiline_comment|/*&t;&t;undefined&t;&t;0x66 - 0x78 */
multiline_comment|/*&t;&t;reserved&t;&t;0x79 - 0x7f */
multiline_comment|/* Pseudo controllers (not midi compatible) */
DECL|macro|CTRL_PITCH_BENDER
mdefine_line|#define    CTRL_PITCH_BENDER&t;&t;255
DECL|macro|CTRL_PITCH_BENDER_RANGE
mdefine_line|#define    CTRL_PITCH_BENDER_RANGE&t;254
DECL|macro|CTRL_EXPRESSION
mdefine_line|#define    CTRL_EXPRESSION&t;&t;253&t;/* Obsolete */
DECL|macro|CTRL_MAIN_VOLUME
mdefine_line|#define    CTRL_MAIN_VOLUME&t;&t;252&t;/* Obsolete */
DECL|macro|SEQ_BALANCE
mdefine_line|#define SEQ_BALANCE&t;&t;11
DECL|macro|SEQ_VOLMODE
mdefine_line|#define SEQ_VOLMODE             12
multiline_comment|/*&n; * Volume mode decides how volumes are used&n; */
DECL|macro|VOL_METHOD_ADAGIO
mdefine_line|#define VOL_METHOD_ADAGIO&t;1
DECL|macro|VOL_METHOD_LINEAR
mdefine_line|#define VOL_METHOD_LINEAR&t;2
multiline_comment|/*&n; * Note! SEQ_WAIT, SEQ_MIDIPUTC and SEQ_ECHO are used also as&n; *&t; input events.&n; */
multiline_comment|/*&n; * Event codes 0xf0 to 0xfc are reserved for future extensions.&n; */
DECL|macro|SEQ_FULLSIZE
mdefine_line|#define SEQ_FULLSIZE&t;&t;0xfd&t;/* Long events */
multiline_comment|/*&n; *&t;SEQ_FULLSIZE events are used for loading patches/samples to the&n; *&t;synthesizer devices. These events are passed directly to the driver&n; *&t;of the associated synthesizer device. There is no limit to the size&n; *&t;of the extended events. These events are not queued but executed&n; *&t;immediately when the write() is called (execution can take several&n; *&t;seconds of time). &n; *&n; *&t;When a SEQ_FULLSIZE message is written to the device, it must&n; *&t;be written using exactly one write() call. Other events cannot&n; *&t;be mixed to the same write.&n; *&t;&n; *&t;For FM synths (YM3812/OPL3) use struct sbi_instrument and write it to the &n; *&t;/dev/sequencer. Don&squot;t write other data together with the instrument structure&n; *&t;Set the key field of the structure to FM_PATCH. The device field is used to&n; *&t;route the patch to the corresponding device.&n; *&n; *&t;For wave table use struct patch_info. Initialize the key field&n; *      to WAVE_PATCH.&n; */
DECL|macro|SEQ_PRIVATE
mdefine_line|#define SEQ_PRIVATE&t;&t;0xfe&t;/* Low level HW dependent events (8 bytes) */
DECL|macro|SEQ_EXTENDED
mdefine_line|#define SEQ_EXTENDED&t;&t;0xff&t;/* Extended events (8 bytes) OBSOLETE */
multiline_comment|/*&n; * Record for FM patches&n; */
DECL|typedef|sbi_instr_data
r_typedef
r_int
r_char
id|sbi_instr_data
(braket
l_int|32
)braket
suffix:semicolon
DECL|struct|sbi_instrument
r_struct
id|sbi_instrument
(brace
DECL|member|key
r_int
r_int
id|key
suffix:semicolon
multiline_comment|/* FM_PATCH or OPL3_PATCH */
DECL|macro|FM_PATCH
mdefine_line|#define FM_PATCH&t;_PATCHKEY(0x01)
DECL|macro|OPL3_PATCH
mdefine_line|#define OPL3_PATCH&t;_PATCHKEY(0x03)
DECL|member|device
r_int
id|device
suffix:semicolon
multiline_comment|/*&t;Synth# (0-4)&t;*/
DECL|member|channel
r_int
id|channel
suffix:semicolon
multiline_comment|/*&t;Program# to be initialized &t;*/
DECL|member|operators
id|sbi_instr_data
id|operators
suffix:semicolon
multiline_comment|/*&t;Register settings for operator cells (.SBI format)&t;*/
)brace
suffix:semicolon
DECL|struct|synth_info
r_struct
id|synth_info
(brace
multiline_comment|/* Read only */
DECL|member|name
r_char
id|name
(braket
l_int|30
)braket
suffix:semicolon
DECL|member|device
r_int
id|device
suffix:semicolon
multiline_comment|/* 0-N. INITIALIZE BEFORE CALLING */
DECL|member|synth_type
r_int
id|synth_type
suffix:semicolon
DECL|macro|SYNTH_TYPE_FM
mdefine_line|#define SYNTH_TYPE_FM&t;&t;&t;0
DECL|macro|SYNTH_TYPE_SAMPLE
mdefine_line|#define SYNTH_TYPE_SAMPLE&t;&t;1
DECL|macro|SYNTH_TYPE_MIDI
mdefine_line|#define SYNTH_TYPE_MIDI&t;&t;&t;2&t;/* Midi interface */
DECL|member|synth_subtype
r_int
id|synth_subtype
suffix:semicolon
DECL|macro|FM_TYPE_ADLIB
mdefine_line|#define FM_TYPE_ADLIB&t;&t;&t;0x00
DECL|macro|FM_TYPE_OPL3
mdefine_line|#define FM_TYPE_OPL3&t;&t;&t;0x01
DECL|macro|MIDI_TYPE_MPU401
mdefine_line|#define MIDI_TYPE_MPU401&t;&t;0x401
DECL|macro|SAMPLE_TYPE_BASIC
mdefine_line|#define SAMPLE_TYPE_BASIC&t;&t;0x10
DECL|macro|SAMPLE_TYPE_GUS
mdefine_line|#define SAMPLE_TYPE_GUS&t;&t;&t;SAMPLE_TYPE_BASIC
DECL|macro|SAMPLE_TYPE_WAVEFRONT
mdefine_line|#define SAMPLE_TYPE_WAVEFRONT           0x11
DECL|member|perc_mode
r_int
id|perc_mode
suffix:semicolon
multiline_comment|/* No longer supported */
DECL|member|nr_voices
r_int
id|nr_voices
suffix:semicolon
DECL|member|nr_drums
r_int
id|nr_drums
suffix:semicolon
multiline_comment|/* Obsolete field */
DECL|member|instr_bank_size
r_int
id|instr_bank_size
suffix:semicolon
DECL|member|capabilities
r_int
r_int
id|capabilities
suffix:semicolon
DECL|macro|SYNTH_CAP_PERCMODE
mdefine_line|#define SYNTH_CAP_PERCMODE&t;&t;0x00000001 /* No longer used */
DECL|macro|SYNTH_CAP_OPL3
mdefine_line|#define SYNTH_CAP_OPL3&t;&t;&t;0x00000002 /* Set if OPL3 supported */
DECL|macro|SYNTH_CAP_INPUT
mdefine_line|#define SYNTH_CAP_INPUT&t;&t;&t;0x00000004 /* Input (MIDI) device */
DECL|member|dummies
r_int
id|dummies
(braket
l_int|19
)braket
suffix:semicolon
multiline_comment|/* Reserve space */
)brace
suffix:semicolon
DECL|struct|sound_timer_info
r_struct
id|sound_timer_info
(brace
DECL|member|name
r_char
id|name
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|caps
r_int
id|caps
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|MIDI_CAP_MPU401
mdefine_line|#define MIDI_CAP_MPU401&t;&t;1&t;&t;/* MPU-401 intelligent mode */
DECL|struct|midi_info
r_struct
id|midi_info
(brace
DECL|member|name
r_char
id|name
(braket
l_int|30
)braket
suffix:semicolon
DECL|member|device
r_int
id|device
suffix:semicolon
multiline_comment|/* 0-N. INITIALIZE BEFORE CALLING */
DECL|member|capabilities
r_int
r_int
id|capabilities
suffix:semicolon
multiline_comment|/* To be defined later */
DECL|member|dev_type
r_int
id|dev_type
suffix:semicolon
DECL|member|dummies
r_int
id|dummies
(braket
l_int|18
)braket
suffix:semicolon
multiline_comment|/* Reserve space */
)brace
suffix:semicolon
multiline_comment|/********************************************&n; * ioctl commands for the /dev/midi##&n; */
r_typedef
r_struct
(brace
DECL|member|cmd
r_int
r_char
id|cmd
suffix:semicolon
DECL|member|nr_args
DECL|member|nr_returns
r_char
id|nr_args
comma
id|nr_returns
suffix:semicolon
DECL|member|data
r_int
r_char
id|data
(braket
l_int|30
)braket
suffix:semicolon
DECL|typedef|mpu_command_rec
)brace
id|mpu_command_rec
suffix:semicolon
DECL|macro|SNDCTL_MIDI_PRETIME
mdefine_line|#define SNDCTL_MIDI_PRETIME&t;&t;_SIOWR(&squot;m&squot;, 0, int)
DECL|macro|SNDCTL_MIDI_MPUMODE
mdefine_line|#define SNDCTL_MIDI_MPUMODE&t;&t;_SIOWR(&squot;m&squot;, 1, int)
DECL|macro|SNDCTL_MIDI_MPUCMD
mdefine_line|#define SNDCTL_MIDI_MPUCMD&t;&t;_SIOWR(&squot;m&squot;, 2, mpu_command_rec)
multiline_comment|/********************************************&n; * IOCTL commands for /dev/dsp and /dev/audio&n; */
DECL|macro|SNDCTL_DSP_RESET
mdefine_line|#define SNDCTL_DSP_RESET&t;&t;_SIO  (&squot;P&squot;, 0)
DECL|macro|SNDCTL_DSP_SYNC
mdefine_line|#define SNDCTL_DSP_SYNC&t;&t;&t;_SIO  (&squot;P&squot;, 1)
DECL|macro|SNDCTL_DSP_SPEED
mdefine_line|#define SNDCTL_DSP_SPEED&t;&t;_SIOWR(&squot;P&squot;, 2, int)
DECL|macro|SNDCTL_DSP_STEREO
mdefine_line|#define SNDCTL_DSP_STEREO&t;&t;_SIOWR(&squot;P&squot;, 3, int)
DECL|macro|SNDCTL_DSP_GETBLKSIZE
mdefine_line|#define SNDCTL_DSP_GETBLKSIZE&t;&t;_SIOWR(&squot;P&squot;, 4, int)
DECL|macro|SNDCTL_DSP_SAMPLESIZE
mdefine_line|#define SNDCTL_DSP_SAMPLESIZE&t;&t;SNDCTL_DSP_SETFMT
DECL|macro|SNDCTL_DSP_CHANNELS
mdefine_line|#define SNDCTL_DSP_CHANNELS&t;&t;_SIOWR(&squot;P&squot;, 6, int)
DECL|macro|SOUND_PCM_WRITE_CHANNELS
mdefine_line|#define SOUND_PCM_WRITE_CHANNELS&t;SNDCTL_DSP_CHANNELS
DECL|macro|SOUND_PCM_WRITE_FILTER
mdefine_line|#define SOUND_PCM_WRITE_FILTER&t;&t;_SIOWR(&squot;P&squot;, 7, int)
DECL|macro|SNDCTL_DSP_POST
mdefine_line|#define SNDCTL_DSP_POST&t;&t;&t;_SIO  (&squot;P&squot;, 8)
DECL|macro|SNDCTL_DSP_SUBDIVIDE
mdefine_line|#define SNDCTL_DSP_SUBDIVIDE&t;&t;_SIOWR(&squot;P&squot;, 9, int)
DECL|macro|SNDCTL_DSP_SETFRAGMENT
mdefine_line|#define SNDCTL_DSP_SETFRAGMENT&t;&t;_SIOWR(&squot;P&squot;,10, int)
multiline_comment|/*&t;Audio data formats (Note! U8=8 and S16_LE=16 for compatibility) */
DECL|macro|SNDCTL_DSP_GETFMTS
mdefine_line|#define SNDCTL_DSP_GETFMTS&t;&t;_SIOR (&squot;P&squot;,11, int) /* Returns a mask */
DECL|macro|SNDCTL_DSP_SETFMT
mdefine_line|#define SNDCTL_DSP_SETFMT&t;&t;_SIOWR(&squot;P&squot;,5, int) /* Selects ONE fmt*/
DECL|macro|AFMT_QUERY
macro_line|#&t;define AFMT_QUERY&t;&t;0x00000000&t;/* Return current fmt */
DECL|macro|AFMT_MU_LAW
macro_line|#&t;define AFMT_MU_LAW&t;&t;0x00000001
DECL|macro|AFMT_A_LAW
macro_line|#&t;define AFMT_A_LAW&t;&t;0x00000002
DECL|macro|AFMT_IMA_ADPCM
macro_line|#&t;define AFMT_IMA_ADPCM&t;&t;0x00000004
DECL|macro|AFMT_U8
macro_line|#&t;define AFMT_U8&t;&t;&t;0x00000008
DECL|macro|AFMT_S16_LE
macro_line|#&t;define AFMT_S16_LE&t;&t;0x00000010&t;/* Little endian signed 16*/
DECL|macro|AFMT_S16_BE
macro_line|#&t;define AFMT_S16_BE&t;&t;0x00000020&t;/* Big endian signed 16 */
DECL|macro|AFMT_S8
macro_line|#&t;define AFMT_S8&t;&t;&t;0x00000040
DECL|macro|AFMT_U16_LE
macro_line|#&t;define AFMT_U16_LE&t;&t;0x00000080&t;/* Little endian U16 */
DECL|macro|AFMT_U16_BE
macro_line|#&t;define AFMT_U16_BE&t;&t;0x00000100&t;/* Big endian U16 */
DECL|macro|AFMT_MPEG
macro_line|#&t;define AFMT_MPEG&t;&t;0x00000200&t;/* MPEG (2) audio */
DECL|macro|AFMT_AC3
macro_line|#&t;define AFMT_AC3&t;&t;0x00000400&t;/* Dolby Digital AC3 */
multiline_comment|/*&n; * Buffer status queries.&n; */
DECL|struct|audio_buf_info
r_typedef
r_struct
id|audio_buf_info
(brace
DECL|member|fragments
r_int
id|fragments
suffix:semicolon
multiline_comment|/* # of available fragments (partially usend ones not counted) */
DECL|member|fragstotal
r_int
id|fragstotal
suffix:semicolon
multiline_comment|/* Total # of fragments allocated */
DECL|member|fragsize
r_int
id|fragsize
suffix:semicolon
multiline_comment|/* Size of a fragment in bytes */
DECL|member|bytes
r_int
id|bytes
suffix:semicolon
multiline_comment|/* Available space in bytes (includes partially used fragments) */
multiline_comment|/* Note! &squot;bytes&squot; could be more than fragments*fragsize */
DECL|typedef|audio_buf_info
)brace
id|audio_buf_info
suffix:semicolon
DECL|macro|SNDCTL_DSP_GETOSPACE
mdefine_line|#define SNDCTL_DSP_GETOSPACE&t;&t;_SIOR (&squot;P&squot;,12, audio_buf_info)
DECL|macro|SNDCTL_DSP_GETISPACE
mdefine_line|#define SNDCTL_DSP_GETISPACE&t;&t;_SIOR (&squot;P&squot;,13, audio_buf_info)
DECL|macro|SNDCTL_DSP_NONBLOCK
mdefine_line|#define SNDCTL_DSP_NONBLOCK&t;&t;_SIO  (&squot;P&squot;,14)
DECL|macro|SNDCTL_DSP_GETCAPS
mdefine_line|#define SNDCTL_DSP_GETCAPS&t;&t;_SIOR (&squot;P&squot;,15, int)
DECL|macro|DSP_CAP_REVISION
macro_line|#&t;define DSP_CAP_REVISION&t;&t;0x000000ff&t;/* Bits for revision level (0 to 255) */
DECL|macro|DSP_CAP_DUPLEX
macro_line|#&t;define DSP_CAP_DUPLEX&t;&t;0x00000100&t;/* Full duplex record/playback */
DECL|macro|DSP_CAP_REALTIME
macro_line|#&t;define DSP_CAP_REALTIME&t;&t;0x00000200&t;/* Real time capability */
DECL|macro|DSP_CAP_BATCH
macro_line|#&t;define DSP_CAP_BATCH&t;&t;0x00000400&t;/* Device has some kind of */
multiline_comment|/* internal buffers which may */
multiline_comment|/* cause some delays and */
multiline_comment|/* decrease precision of timing */
DECL|macro|DSP_CAP_COPROC
macro_line|#&t;define DSP_CAP_COPROC&t;&t;0x00000800&t;/* Has a coprocessor */
multiline_comment|/* Sometimes it&squot;s a DSP */
multiline_comment|/* but usually not */
DECL|macro|DSP_CAP_TRIGGER
macro_line|#&t;define DSP_CAP_TRIGGER&t;&t;0x00001000&t;/* Supports SETTRIGGER */
DECL|macro|DSP_CAP_MMAP
macro_line|#&t;define DSP_CAP_MMAP&t;&t;0x00002000&t;/* Supports mmap() */
DECL|macro|DSP_CAP_MULTI
macro_line|#&t;define DSP_CAP_MULTI&t;&t;0x00004000&t;/* support multiple open */
DECL|macro|DSP_CAP_BIND
macro_line|#&t;define DSP_CAP_BIND&t;&t;0x00008000&t;/* channel binding to front/rear/cneter/lfe */
DECL|macro|SNDCTL_DSP_GETTRIGGER
mdefine_line|#define SNDCTL_DSP_GETTRIGGER&t;&t;_SIOR (&squot;P&squot;,16, int)
DECL|macro|SNDCTL_DSP_SETTRIGGER
mdefine_line|#define SNDCTL_DSP_SETTRIGGER&t;&t;_SIOW (&squot;P&squot;,16, int)
DECL|macro|PCM_ENABLE_INPUT
macro_line|#&t;define PCM_ENABLE_INPUT&t;&t;0x00000001
DECL|macro|PCM_ENABLE_OUTPUT
macro_line|#&t;define PCM_ENABLE_OUTPUT&t;&t;0x00000002
DECL|struct|count_info
r_typedef
r_struct
id|count_info
(brace
DECL|member|bytes
r_int
id|bytes
suffix:semicolon
multiline_comment|/* Total # of bytes processed */
DECL|member|blocks
r_int
id|blocks
suffix:semicolon
multiline_comment|/* # of fragment transitions since last time */
DECL|member|ptr
r_int
id|ptr
suffix:semicolon
multiline_comment|/* Current DMA pointer value */
DECL|typedef|count_info
)brace
id|count_info
suffix:semicolon
DECL|macro|SNDCTL_DSP_GETIPTR
mdefine_line|#define SNDCTL_DSP_GETIPTR&t;&t;_SIOR (&squot;P&squot;,17, count_info)
DECL|macro|SNDCTL_DSP_GETOPTR
mdefine_line|#define SNDCTL_DSP_GETOPTR&t;&t;_SIOR (&squot;P&squot;,18, count_info)
DECL|struct|buffmem_desc
r_typedef
r_struct
id|buffmem_desc
(brace
DECL|member|buffer
r_int
op_star
id|buffer
suffix:semicolon
DECL|member|size
r_int
id|size
suffix:semicolon
DECL|typedef|buffmem_desc
)brace
id|buffmem_desc
suffix:semicolon
DECL|macro|SNDCTL_DSP_MAPINBUF
mdefine_line|#define SNDCTL_DSP_MAPINBUF&t;&t;_SIOR (&squot;P&squot;, 19, buffmem_desc)
DECL|macro|SNDCTL_DSP_MAPOUTBUF
mdefine_line|#define SNDCTL_DSP_MAPOUTBUF&t;&t;_SIOR (&squot;P&squot;, 20, buffmem_desc)
DECL|macro|SNDCTL_DSP_SETSYNCRO
mdefine_line|#define SNDCTL_DSP_SETSYNCRO&t;&t;_SIO  (&squot;P&squot;, 21)
DECL|macro|SNDCTL_DSP_SETDUPLEX
mdefine_line|#define SNDCTL_DSP_SETDUPLEX&t;&t;_SIO  (&squot;P&squot;, 22)
DECL|macro|SNDCTL_DSP_GETODELAY
mdefine_line|#define SNDCTL_DSP_GETODELAY&t;&t;_SIOR (&squot;P&squot;, 23, int)
DECL|macro|SNDCTL_DSP_GETCHANNELMASK
mdefine_line|#define SNDCTL_DSP_GETCHANNELMASK&t;&t;_SIOWR(&squot;P&squot;, 64, int)
DECL|macro|SNDCTL_DSP_BIND_CHANNEL
mdefine_line|#define SNDCTL_DSP_BIND_CHANNEL&t;&t;_SIOWR(&squot;P&squot;, 65, int)
DECL|macro|DSP_BIND_QUERY
macro_line|#&t;define DSP_BIND_QUERY&t;&t;0x00000000
DECL|macro|DSP_BIND_FRONT
macro_line|#&t;define DSP_BIND_FRONT&t;&t;0x00000001
DECL|macro|DSP_BIND_SURR
macro_line|#&t;define DSP_BIND_SURR&t;&t;0x00000002
DECL|macro|DSP_BIND_CENTER_LFE
macro_line|#&t;define DSP_BIND_CENTER_LFE&t;0x00000004
DECL|macro|DSP_BIND_HANDSET
macro_line|#&t;define DSP_BIND_HANDSET&t;&t;0x00000008
DECL|macro|DSP_BIND_MIC
macro_line|#&t;define DSP_BIND_MIC&t;&t;0x00000010
DECL|macro|DSP_BIND_MODEM1
macro_line|#&t;define DSP_BIND_MODEM1&t;&t;0x00000020
DECL|macro|DSP_BIND_MODEM2
macro_line|#&t;define DSP_BIND_MODEM2&t;&t;0x00000040
DECL|macro|DSP_BIND_I2S
macro_line|#&t;define DSP_BIND_I2S&t;&t;0x00000080
DECL|macro|DSP_BIND_SPDIF
macro_line|#&t;define DSP_BIND_SPDIF&t;&t;0x00000100
multiline_comment|/*&n; * Application&squot;s profile defines the way how playback underrun situations should be handled.&n; * &n; *&t;APF_NORMAL (the default) and APF_NETWORK make the driver to cleanup the&n; *&t;playback buffer whenever an underrun occurs. This consumes some time&n; *&t;prevents looping the existing buffer.&n; *&t;APF_CPUINTENS is intended to be set by CPU intensive applications which&n; *&t;are likely to run out of time occasionally. In this mode the buffer cleanup is&n; *&t;disabled which saves CPU time but also let&squot;s the previous buffer content to&n; *&t;be played during the &quot;pause&quot; after the underrun.&n; */
DECL|macro|SNDCTL_DSP_PROFILE
mdefine_line|#define SNDCTL_DSP_PROFILE&t;&t;_SIOW (&squot;P&squot;, 23, int)
DECL|macro|APF_NORMAL
mdefine_line|#define&t;  APF_NORMAL&t;0&t;/* Normal applications */
DECL|macro|APF_NETWORK
mdefine_line|#define&t;  APF_NETWORK&t;1&t;/* Underruns probably caused by an &quot;external&quot; delay */
DECL|macro|APF_CPUINTENS
mdefine_line|#define   APF_CPUINTENS 2&t;/* Underruns probably caused by &quot;overheating&quot; the CPU */
DECL|macro|SOUND_PCM_READ_RATE
mdefine_line|#define SOUND_PCM_READ_RATE&t;&t;_SIOR (&squot;P&squot;, 2, int)
DECL|macro|SOUND_PCM_READ_CHANNELS
mdefine_line|#define SOUND_PCM_READ_CHANNELS&t;&t;_SIOR (&squot;P&squot;, 6, int)
DECL|macro|SOUND_PCM_READ_BITS
mdefine_line|#define SOUND_PCM_READ_BITS&t;&t;_SIOR (&squot;P&squot;, 5, int)
DECL|macro|SOUND_PCM_READ_FILTER
mdefine_line|#define SOUND_PCM_READ_FILTER&t;&t;_SIOR (&squot;P&squot;, 7, int)
multiline_comment|/* Some alias names */
DECL|macro|SOUND_PCM_WRITE_BITS
mdefine_line|#define SOUND_PCM_WRITE_BITS&t;&t;SNDCTL_DSP_SETFMT
DECL|macro|SOUND_PCM_WRITE_RATE
mdefine_line|#define SOUND_PCM_WRITE_RATE&t;&t;SNDCTL_DSP_SPEED
DECL|macro|SOUND_PCM_POST
mdefine_line|#define SOUND_PCM_POST&t;&t;&t;SNDCTL_DSP_POST
DECL|macro|SOUND_PCM_RESET
mdefine_line|#define SOUND_PCM_RESET&t;&t;&t;SNDCTL_DSP_RESET
DECL|macro|SOUND_PCM_SYNC
mdefine_line|#define SOUND_PCM_SYNC&t;&t;&t;SNDCTL_DSP_SYNC
DECL|macro|SOUND_PCM_SUBDIVIDE
mdefine_line|#define SOUND_PCM_SUBDIVIDE&t;&t;SNDCTL_DSP_SUBDIVIDE
DECL|macro|SOUND_PCM_SETFRAGMENT
mdefine_line|#define SOUND_PCM_SETFRAGMENT&t;&t;SNDCTL_DSP_SETFRAGMENT
DECL|macro|SOUND_PCM_GETFMTS
mdefine_line|#define SOUND_PCM_GETFMTS&t;&t;SNDCTL_DSP_GETFMTS
DECL|macro|SOUND_PCM_SETFMT
mdefine_line|#define SOUND_PCM_SETFMT&t;&t;SNDCTL_DSP_SETFMT
DECL|macro|SOUND_PCM_GETOSPACE
mdefine_line|#define SOUND_PCM_GETOSPACE&t;&t;SNDCTL_DSP_GETOSPACE
DECL|macro|SOUND_PCM_GETISPACE
mdefine_line|#define SOUND_PCM_GETISPACE&t;&t;SNDCTL_DSP_GETISPACE
DECL|macro|SOUND_PCM_NONBLOCK
mdefine_line|#define SOUND_PCM_NONBLOCK&t;&t;SNDCTL_DSP_NONBLOCK
DECL|macro|SOUND_PCM_GETCAPS
mdefine_line|#define SOUND_PCM_GETCAPS&t;&t;SNDCTL_DSP_GETCAPS
DECL|macro|SOUND_PCM_GETTRIGGER
mdefine_line|#define SOUND_PCM_GETTRIGGER&t;&t;SNDCTL_DSP_GETTRIGGER
DECL|macro|SOUND_PCM_SETTRIGGER
mdefine_line|#define SOUND_PCM_SETTRIGGER&t;&t;SNDCTL_DSP_SETTRIGGER
DECL|macro|SOUND_PCM_SETSYNCRO
mdefine_line|#define SOUND_PCM_SETSYNCRO&t;&t;SNDCTL_DSP_SETSYNCRO
DECL|macro|SOUND_PCM_GETIPTR
mdefine_line|#define SOUND_PCM_GETIPTR&t;&t;SNDCTL_DSP_GETIPTR
DECL|macro|SOUND_PCM_GETOPTR
mdefine_line|#define SOUND_PCM_GETOPTR&t;&t;SNDCTL_DSP_GETOPTR
DECL|macro|SOUND_PCM_MAPINBUF
mdefine_line|#define SOUND_PCM_MAPINBUF&t;&t;SNDCTL_DSP_MAPINBUF
DECL|macro|SOUND_PCM_MAPOUTBUF
mdefine_line|#define SOUND_PCM_MAPOUTBUF&t;&t;SNDCTL_DSP_MAPOUTBUF
multiline_comment|/*&n; * ioctl calls to be used in communication with coprocessors and&n; * DSP chips.&n; */
DECL|struct|copr_buffer
r_typedef
r_struct
id|copr_buffer
(brace
DECL|member|command
r_int
id|command
suffix:semicolon
multiline_comment|/* Set to 0 if not used */
DECL|member|flags
r_int
id|flags
suffix:semicolon
DECL|macro|CPF_NONE
mdefine_line|#define CPF_NONE&t;&t;0x0000
DECL|macro|CPF_FIRST
mdefine_line|#define CPF_FIRST&t;&t;0x0001&t;/* First block */
DECL|macro|CPF_LAST
mdefine_line|#define CPF_LAST&t;&t;0x0002&t;/* Last block */
DECL|member|len
r_int
id|len
suffix:semicolon
DECL|member|offs
r_int
id|offs
suffix:semicolon
multiline_comment|/* If required by the device (0 if not used) */
DECL|member|data
r_int
r_char
id|data
(braket
l_int|4000
)braket
suffix:semicolon
multiline_comment|/* NOTE! 4000 is not 4k */
DECL|typedef|copr_buffer
)brace
id|copr_buffer
suffix:semicolon
DECL|struct|copr_debug_buf
r_typedef
r_struct
id|copr_debug_buf
(brace
DECL|member|command
r_int
id|command
suffix:semicolon
multiline_comment|/* Used internally. Set to 0 */
DECL|member|parm1
r_int
id|parm1
suffix:semicolon
DECL|member|parm2
r_int
id|parm2
suffix:semicolon
DECL|member|flags
r_int
id|flags
suffix:semicolon
DECL|member|len
r_int
id|len
suffix:semicolon
multiline_comment|/* Length of data in bytes */
DECL|typedef|copr_debug_buf
)brace
id|copr_debug_buf
suffix:semicolon
DECL|struct|copr_msg
r_typedef
r_struct
id|copr_msg
(brace
DECL|member|len
r_int
id|len
suffix:semicolon
DECL|member|data
r_int
r_char
id|data
(braket
l_int|4000
)braket
suffix:semicolon
DECL|typedef|copr_msg
)brace
id|copr_msg
suffix:semicolon
DECL|macro|SNDCTL_COPR_RESET
mdefine_line|#define SNDCTL_COPR_RESET             _SIO  (&squot;C&squot;,  0)
DECL|macro|SNDCTL_COPR_LOAD
mdefine_line|#define SNDCTL_COPR_LOAD&t;      _SIOWR(&squot;C&squot;,  1, copr_buffer)
DECL|macro|SNDCTL_COPR_RDATA
mdefine_line|#define SNDCTL_COPR_RDATA&t;      _SIOWR(&squot;C&squot;,  2, copr_debug_buf)
DECL|macro|SNDCTL_COPR_RCODE
mdefine_line|#define SNDCTL_COPR_RCODE&t;      _SIOWR(&squot;C&squot;,  3, copr_debug_buf)
DECL|macro|SNDCTL_COPR_WDATA
mdefine_line|#define SNDCTL_COPR_WDATA&t;      _SIOW (&squot;C&squot;,  4, copr_debug_buf)
DECL|macro|SNDCTL_COPR_WCODE
mdefine_line|#define SNDCTL_COPR_WCODE&t;      _SIOW (&squot;C&squot;,  5, copr_debug_buf)
DECL|macro|SNDCTL_COPR_RUN
mdefine_line|#define SNDCTL_COPR_RUN&t;&t;      _SIOWR(&squot;C&squot;,  6, copr_debug_buf)
DECL|macro|SNDCTL_COPR_HALT
mdefine_line|#define SNDCTL_COPR_HALT&t;      _SIOWR(&squot;C&squot;,  7, copr_debug_buf)
DECL|macro|SNDCTL_COPR_SENDMSG
mdefine_line|#define SNDCTL_COPR_SENDMSG&t;      _SIOWR(&squot;C&squot;,  8, copr_msg)
DECL|macro|SNDCTL_COPR_RCVMSG
mdefine_line|#define SNDCTL_COPR_RCVMSG&t;      _SIOR (&squot;C&squot;,  9, copr_msg)
multiline_comment|/*********************************************&n; * IOCTL commands for /dev/mixer&n; */
multiline_comment|/* &n; * Mixer devices&n; *&n; * There can be up to 20 different analog mixer channels. The&n; * SOUND_MIXER_NRDEVICES gives the currently supported maximum. &n; * The SOUND_MIXER_READ_DEVMASK returns a bitmask which tells&n; * the devices supported by the particular mixer.&n; */
DECL|macro|SOUND_MIXER_NRDEVICES
mdefine_line|#define SOUND_MIXER_NRDEVICES&t;25
DECL|macro|SOUND_MIXER_VOLUME
mdefine_line|#define SOUND_MIXER_VOLUME&t;0
DECL|macro|SOUND_MIXER_BASS
mdefine_line|#define SOUND_MIXER_BASS&t;1
DECL|macro|SOUND_MIXER_TREBLE
mdefine_line|#define SOUND_MIXER_TREBLE&t;2
DECL|macro|SOUND_MIXER_SYNTH
mdefine_line|#define SOUND_MIXER_SYNTH&t;3
DECL|macro|SOUND_MIXER_PCM
mdefine_line|#define SOUND_MIXER_PCM&t;&t;4
DECL|macro|SOUND_MIXER_SPEAKER
mdefine_line|#define SOUND_MIXER_SPEAKER&t;5
DECL|macro|SOUND_MIXER_LINE
mdefine_line|#define SOUND_MIXER_LINE&t;6
DECL|macro|SOUND_MIXER_MIC
mdefine_line|#define SOUND_MIXER_MIC&t;&t;7
DECL|macro|SOUND_MIXER_CD
mdefine_line|#define SOUND_MIXER_CD&t;&t;8
DECL|macro|SOUND_MIXER_IMIX
mdefine_line|#define SOUND_MIXER_IMIX&t;9&t;/*  Recording monitor  */
DECL|macro|SOUND_MIXER_ALTPCM
mdefine_line|#define SOUND_MIXER_ALTPCM&t;10
DECL|macro|SOUND_MIXER_RECLEV
mdefine_line|#define SOUND_MIXER_RECLEV&t;11&t;/* Recording level */
DECL|macro|SOUND_MIXER_IGAIN
mdefine_line|#define SOUND_MIXER_IGAIN&t;12&t;/* Input gain */
DECL|macro|SOUND_MIXER_OGAIN
mdefine_line|#define SOUND_MIXER_OGAIN&t;13&t;/* Output gain */
multiline_comment|/* &n; * The AD1848 codec and compatibles have three line level inputs&n; * (line, aux1 and aux2). Since each card manufacturer have assigned&n; * different meanings to these inputs, it&squot;s inpractical to assign&n; * specific meanings (line, cd, synth etc.) to them.&n; */
DECL|macro|SOUND_MIXER_LINE1
mdefine_line|#define SOUND_MIXER_LINE1&t;14&t;/* Input source 1  (aux1) */
DECL|macro|SOUND_MIXER_LINE2
mdefine_line|#define SOUND_MIXER_LINE2&t;15&t;/* Input source 2  (aux2) */
DECL|macro|SOUND_MIXER_LINE3
mdefine_line|#define SOUND_MIXER_LINE3&t;16&t;/* Input source 3  (line) */
DECL|macro|SOUND_MIXER_DIGITAL1
mdefine_line|#define SOUND_MIXER_DIGITAL1&t;17&t;/* Digital (input) 1 */
DECL|macro|SOUND_MIXER_DIGITAL2
mdefine_line|#define SOUND_MIXER_DIGITAL2&t;18&t;/* Digital (input) 2 */
DECL|macro|SOUND_MIXER_DIGITAL3
mdefine_line|#define SOUND_MIXER_DIGITAL3&t;19&t;/* Digital (input) 3 */
DECL|macro|SOUND_MIXER_PHONEIN
mdefine_line|#define SOUND_MIXER_PHONEIN&t;20&t;/* Phone input */
DECL|macro|SOUND_MIXER_PHONEOUT
mdefine_line|#define SOUND_MIXER_PHONEOUT&t;21&t;/* Phone output */
DECL|macro|SOUND_MIXER_VIDEO
mdefine_line|#define SOUND_MIXER_VIDEO&t;22&t;/* Video/TV (audio) in */
DECL|macro|SOUND_MIXER_RADIO
mdefine_line|#define SOUND_MIXER_RADIO&t;23&t;/* Radio in */
DECL|macro|SOUND_MIXER_MONITOR
mdefine_line|#define SOUND_MIXER_MONITOR&t;24&t;/* Monitor (usually mic) volume */
multiline_comment|/* Some on/off settings (SOUND_SPECIAL_MIN - SOUND_SPECIAL_MAX) */
multiline_comment|/* Not counted to SOUND_MIXER_NRDEVICES, but use the same number space */
DECL|macro|SOUND_ONOFF_MIN
mdefine_line|#define SOUND_ONOFF_MIN&t;&t;28
DECL|macro|SOUND_ONOFF_MAX
mdefine_line|#define SOUND_ONOFF_MAX&t;&t;30
multiline_comment|/* Note!&t;Number 31 cannot be used since the sign bit is reserved */
DECL|macro|SOUND_MIXER_NONE
mdefine_line|#define SOUND_MIXER_NONE&t;31
multiline_comment|/*&n; * The following unsupported macros are no longer functional.&n; * Use SOUND_MIXER_PRIVATE# macros in future.&n; */
DECL|macro|SOUND_MIXER_ENHANCE
mdefine_line|#define SOUND_MIXER_ENHANCE&t;SOUND_MIXER_NONE
DECL|macro|SOUND_MIXER_MUTE
mdefine_line|#define SOUND_MIXER_MUTE&t;SOUND_MIXER_NONE
DECL|macro|SOUND_MIXER_LOUD
mdefine_line|#define SOUND_MIXER_LOUD&t;SOUND_MIXER_NONE
DECL|macro|SOUND_DEVICE_LABELS
mdefine_line|#define SOUND_DEVICE_LABELS&t;{&quot;Vol  &quot;, &quot;Bass &quot;, &quot;Trebl&quot;, &quot;Synth&quot;, &quot;Pcm  &quot;, &quot;Spkr &quot;, &quot;Line &quot;, &bslash;&n;&t;&t;&t;&t; &quot;Mic  &quot;, &quot;CD   &quot;, &quot;Mix  &quot;, &quot;Pcm2 &quot;, &quot;Rec  &quot;, &quot;IGain&quot;, &quot;OGain&quot;, &bslash;&n;&t;&t;&t;&t; &quot;Line1&quot;, &quot;Line2&quot;, &quot;Line3&quot;, &quot;Digital1&quot;, &quot;Digital2&quot;, &quot;Digital3&quot;, &bslash;&n;&t;&t;&t;&t; &quot;PhoneIn&quot;, &quot;PhoneOut&quot;, &quot;Video&quot;, &quot;Radio&quot;, &quot;Monitor&quot;}
DECL|macro|SOUND_DEVICE_NAMES
mdefine_line|#define SOUND_DEVICE_NAMES&t;{&quot;vol&quot;, &quot;bass&quot;, &quot;treble&quot;, &quot;synth&quot;, &quot;pcm&quot;, &quot;speaker&quot;, &quot;line&quot;, &bslash;&n;&t;&t;&t;&t; &quot;mic&quot;, &quot;cd&quot;, &quot;mix&quot;, &quot;pcm2&quot;, &quot;rec&quot;, &quot;igain&quot;, &quot;ogain&quot;, &bslash;&n;&t;&t;&t;&t; &quot;line1&quot;, &quot;line2&quot;, &quot;line3&quot;, &quot;dig1&quot;, &quot;dig2&quot;, &quot;dig3&quot;, &bslash;&n;&t;&t;&t;&t; &quot;phin&quot;, &quot;phout&quot;, &quot;video&quot;, &quot;radio&quot;, &quot;monitor&quot;}
multiline_comment|/*&t;Device bitmask identifiers&t;*/
DECL|macro|SOUND_MIXER_RECSRC
mdefine_line|#define SOUND_MIXER_RECSRC&t;0xff&t;/* Arg contains a bit for each recording source */
DECL|macro|SOUND_MIXER_DEVMASK
mdefine_line|#define SOUND_MIXER_DEVMASK&t;0xfe&t;/* Arg contains a bit for each supported device */
DECL|macro|SOUND_MIXER_RECMASK
mdefine_line|#define SOUND_MIXER_RECMASK&t;0xfd&t;/* Arg contains a bit for each supported recording source */
DECL|macro|SOUND_MIXER_CAPS
mdefine_line|#define SOUND_MIXER_CAPS&t;0xfc
DECL|macro|SOUND_CAP_EXCL_INPUT
macro_line|#&t;define SOUND_CAP_EXCL_INPUT&t;0x00000001&t;/* Only one recording source at a time */
DECL|macro|SOUND_MIXER_STEREODEVS
mdefine_line|#define SOUND_MIXER_STEREODEVS&t;0xfb&t;/* Mixer channels supporting stereo */
DECL|macro|SOUND_MIXER_OUTSRC
mdefine_line|#define SOUND_MIXER_OUTSRC&t;0xfa&t;/* Arg contains a bit for each input source to output */
DECL|macro|SOUND_MIXER_OUTMASK
mdefine_line|#define SOUND_MIXER_OUTMASK&t;0xf9&t;/* Arg contains a bit for each supported input source to output */
multiline_comment|/*&t;Device mask bits&t;*/
DECL|macro|SOUND_MASK_VOLUME
mdefine_line|#define SOUND_MASK_VOLUME&t;(1 &lt;&lt; SOUND_MIXER_VOLUME)
DECL|macro|SOUND_MASK_BASS
mdefine_line|#define SOUND_MASK_BASS&t;&t;(1 &lt;&lt; SOUND_MIXER_BASS)
DECL|macro|SOUND_MASK_TREBLE
mdefine_line|#define SOUND_MASK_TREBLE&t;(1 &lt;&lt; SOUND_MIXER_TREBLE)
DECL|macro|SOUND_MASK_SYNTH
mdefine_line|#define SOUND_MASK_SYNTH&t;(1 &lt;&lt; SOUND_MIXER_SYNTH)
DECL|macro|SOUND_MASK_PCM
mdefine_line|#define SOUND_MASK_PCM&t;&t;(1 &lt;&lt; SOUND_MIXER_PCM)
DECL|macro|SOUND_MASK_SPEAKER
mdefine_line|#define SOUND_MASK_SPEAKER&t;(1 &lt;&lt; SOUND_MIXER_SPEAKER)
DECL|macro|SOUND_MASK_LINE
mdefine_line|#define SOUND_MASK_LINE&t;&t;(1 &lt;&lt; SOUND_MIXER_LINE)
DECL|macro|SOUND_MASK_MIC
mdefine_line|#define SOUND_MASK_MIC&t;&t;(1 &lt;&lt; SOUND_MIXER_MIC)
DECL|macro|SOUND_MASK_CD
mdefine_line|#define SOUND_MASK_CD&t;&t;(1 &lt;&lt; SOUND_MIXER_CD)
DECL|macro|SOUND_MASK_IMIX
mdefine_line|#define SOUND_MASK_IMIX&t;&t;(1 &lt;&lt; SOUND_MIXER_IMIX)
DECL|macro|SOUND_MASK_ALTPCM
mdefine_line|#define SOUND_MASK_ALTPCM&t;(1 &lt;&lt; SOUND_MIXER_ALTPCM)
DECL|macro|SOUND_MASK_RECLEV
mdefine_line|#define SOUND_MASK_RECLEV&t;(1 &lt;&lt; SOUND_MIXER_RECLEV)
DECL|macro|SOUND_MASK_IGAIN
mdefine_line|#define SOUND_MASK_IGAIN&t;(1 &lt;&lt; SOUND_MIXER_IGAIN)
DECL|macro|SOUND_MASK_OGAIN
mdefine_line|#define SOUND_MASK_OGAIN&t;(1 &lt;&lt; SOUND_MIXER_OGAIN)
DECL|macro|SOUND_MASK_LINE1
mdefine_line|#define SOUND_MASK_LINE1&t;(1 &lt;&lt; SOUND_MIXER_LINE1)
DECL|macro|SOUND_MASK_LINE2
mdefine_line|#define SOUND_MASK_LINE2&t;(1 &lt;&lt; SOUND_MIXER_LINE2)
DECL|macro|SOUND_MASK_LINE3
mdefine_line|#define SOUND_MASK_LINE3&t;(1 &lt;&lt; SOUND_MIXER_LINE3)
DECL|macro|SOUND_MASK_DIGITAL1
mdefine_line|#define SOUND_MASK_DIGITAL1&t;(1 &lt;&lt; SOUND_MIXER_DIGITAL1)
DECL|macro|SOUND_MASK_DIGITAL2
mdefine_line|#define SOUND_MASK_DIGITAL2&t;(1 &lt;&lt; SOUND_MIXER_DIGITAL2)
DECL|macro|SOUND_MASK_DIGITAL3
mdefine_line|#define SOUND_MASK_DIGITAL3&t;(1 &lt;&lt; SOUND_MIXER_DIGITAL3)
DECL|macro|SOUND_MASK_PHONEIN
mdefine_line|#define SOUND_MASK_PHONEIN&t;(1 &lt;&lt; SOUND_MIXER_PHONEIN)
DECL|macro|SOUND_MASK_PHONEOUT
mdefine_line|#define SOUND_MASK_PHONEOUT&t;(1 &lt;&lt; SOUND_MIXER_PHONEOUT)
DECL|macro|SOUND_MASK_RADIO
mdefine_line|#define SOUND_MASK_RADIO&t;(1 &lt;&lt; SOUND_MIXER_RADIO)
DECL|macro|SOUND_MASK_VIDEO
mdefine_line|#define SOUND_MASK_VIDEO&t;(1 &lt;&lt; SOUND_MIXER_VIDEO)
DECL|macro|SOUND_MASK_MONITOR
mdefine_line|#define SOUND_MASK_MONITOR&t;(1 &lt;&lt; SOUND_MIXER_MONITOR)
multiline_comment|/* Obsolete macros */
DECL|macro|SOUND_MASK_MUTE
mdefine_line|#define SOUND_MASK_MUTE&t;&t;(1 &lt;&lt; SOUND_MIXER_MUTE)
DECL|macro|SOUND_MASK_ENHANCE
mdefine_line|#define SOUND_MASK_ENHANCE&t;(1 &lt;&lt; SOUND_MIXER_ENHANCE)
DECL|macro|SOUND_MASK_LOUD
mdefine_line|#define SOUND_MASK_LOUD&t;&t;(1 &lt;&lt; SOUND_MIXER_LOUD)
DECL|macro|MIXER_READ
mdefine_line|#define MIXER_READ(dev)&t;&t;_SIOR(&squot;M&squot;, dev, int)
DECL|macro|SOUND_MIXER_READ_VOLUME
mdefine_line|#define SOUND_MIXER_READ_VOLUME&t;&t;MIXER_READ(SOUND_MIXER_VOLUME)
DECL|macro|SOUND_MIXER_READ_BASS
mdefine_line|#define SOUND_MIXER_READ_BASS&t;&t;MIXER_READ(SOUND_MIXER_BASS)
DECL|macro|SOUND_MIXER_READ_TREBLE
mdefine_line|#define SOUND_MIXER_READ_TREBLE&t;&t;MIXER_READ(SOUND_MIXER_TREBLE)
DECL|macro|SOUND_MIXER_READ_SYNTH
mdefine_line|#define SOUND_MIXER_READ_SYNTH&t;&t;MIXER_READ(SOUND_MIXER_SYNTH)
DECL|macro|SOUND_MIXER_READ_PCM
mdefine_line|#define SOUND_MIXER_READ_PCM&t;&t;MIXER_READ(SOUND_MIXER_PCM)
DECL|macro|SOUND_MIXER_READ_SPEAKER
mdefine_line|#define SOUND_MIXER_READ_SPEAKER&t;MIXER_READ(SOUND_MIXER_SPEAKER)
DECL|macro|SOUND_MIXER_READ_LINE
mdefine_line|#define SOUND_MIXER_READ_LINE&t;&t;MIXER_READ(SOUND_MIXER_LINE)
DECL|macro|SOUND_MIXER_READ_MIC
mdefine_line|#define SOUND_MIXER_READ_MIC&t;&t;MIXER_READ(SOUND_MIXER_MIC)
DECL|macro|SOUND_MIXER_READ_CD
mdefine_line|#define SOUND_MIXER_READ_CD&t;&t;MIXER_READ(SOUND_MIXER_CD)
DECL|macro|SOUND_MIXER_READ_IMIX
mdefine_line|#define SOUND_MIXER_READ_IMIX&t;&t;MIXER_READ(SOUND_MIXER_IMIX)
DECL|macro|SOUND_MIXER_READ_ALTPCM
mdefine_line|#define SOUND_MIXER_READ_ALTPCM&t;&t;MIXER_READ(SOUND_MIXER_ALTPCM)
DECL|macro|SOUND_MIXER_READ_RECLEV
mdefine_line|#define SOUND_MIXER_READ_RECLEV&t;&t;MIXER_READ(SOUND_MIXER_RECLEV)
DECL|macro|SOUND_MIXER_READ_IGAIN
mdefine_line|#define SOUND_MIXER_READ_IGAIN&t;&t;MIXER_READ(SOUND_MIXER_IGAIN)
DECL|macro|SOUND_MIXER_READ_OGAIN
mdefine_line|#define SOUND_MIXER_READ_OGAIN&t;&t;MIXER_READ(SOUND_MIXER_OGAIN)
DECL|macro|SOUND_MIXER_READ_LINE1
mdefine_line|#define SOUND_MIXER_READ_LINE1&t;&t;MIXER_READ(SOUND_MIXER_LINE1)
DECL|macro|SOUND_MIXER_READ_LINE2
mdefine_line|#define SOUND_MIXER_READ_LINE2&t;&t;MIXER_READ(SOUND_MIXER_LINE2)
DECL|macro|SOUND_MIXER_READ_LINE3
mdefine_line|#define SOUND_MIXER_READ_LINE3&t;&t;MIXER_READ(SOUND_MIXER_LINE3)
multiline_comment|/* Obsolete macros */
DECL|macro|SOUND_MIXER_READ_MUTE
mdefine_line|#define SOUND_MIXER_READ_MUTE&t;&t;MIXER_READ(SOUND_MIXER_MUTE)
DECL|macro|SOUND_MIXER_READ_ENHANCE
mdefine_line|#define SOUND_MIXER_READ_ENHANCE&t;MIXER_READ(SOUND_MIXER_ENHANCE)
DECL|macro|SOUND_MIXER_READ_LOUD
mdefine_line|#define SOUND_MIXER_READ_LOUD&t;&t;MIXER_READ(SOUND_MIXER_LOUD)
DECL|macro|SOUND_MIXER_READ_RECSRC
mdefine_line|#define SOUND_MIXER_READ_RECSRC&t;&t;MIXER_READ(SOUND_MIXER_RECSRC)
DECL|macro|SOUND_MIXER_READ_DEVMASK
mdefine_line|#define SOUND_MIXER_READ_DEVMASK&t;MIXER_READ(SOUND_MIXER_DEVMASK)
DECL|macro|SOUND_MIXER_READ_RECMASK
mdefine_line|#define SOUND_MIXER_READ_RECMASK&t;MIXER_READ(SOUND_MIXER_RECMASK)
DECL|macro|SOUND_MIXER_READ_STEREODEVS
mdefine_line|#define SOUND_MIXER_READ_STEREODEVS&t;MIXER_READ(SOUND_MIXER_STEREODEVS)
DECL|macro|SOUND_MIXER_READ_CAPS
mdefine_line|#define SOUND_MIXER_READ_CAPS&t;&t;MIXER_READ(SOUND_MIXER_CAPS)
DECL|macro|MIXER_WRITE
mdefine_line|#define MIXER_WRITE(dev)&t;&t;_SIOWR(&squot;M&squot;, dev, int)
DECL|macro|SOUND_MIXER_WRITE_VOLUME
mdefine_line|#define SOUND_MIXER_WRITE_VOLUME&t;MIXER_WRITE(SOUND_MIXER_VOLUME)
DECL|macro|SOUND_MIXER_WRITE_BASS
mdefine_line|#define SOUND_MIXER_WRITE_BASS&t;&t;MIXER_WRITE(SOUND_MIXER_BASS)
DECL|macro|SOUND_MIXER_WRITE_TREBLE
mdefine_line|#define SOUND_MIXER_WRITE_TREBLE&t;MIXER_WRITE(SOUND_MIXER_TREBLE)
DECL|macro|SOUND_MIXER_WRITE_SYNTH
mdefine_line|#define SOUND_MIXER_WRITE_SYNTH&t;&t;MIXER_WRITE(SOUND_MIXER_SYNTH)
DECL|macro|SOUND_MIXER_WRITE_PCM
mdefine_line|#define SOUND_MIXER_WRITE_PCM&t;&t;MIXER_WRITE(SOUND_MIXER_PCM)
DECL|macro|SOUND_MIXER_WRITE_SPEAKER
mdefine_line|#define SOUND_MIXER_WRITE_SPEAKER&t;MIXER_WRITE(SOUND_MIXER_SPEAKER)
DECL|macro|SOUND_MIXER_WRITE_LINE
mdefine_line|#define SOUND_MIXER_WRITE_LINE&t;&t;MIXER_WRITE(SOUND_MIXER_LINE)
DECL|macro|SOUND_MIXER_WRITE_MIC
mdefine_line|#define SOUND_MIXER_WRITE_MIC&t;&t;MIXER_WRITE(SOUND_MIXER_MIC)
DECL|macro|SOUND_MIXER_WRITE_CD
mdefine_line|#define SOUND_MIXER_WRITE_CD&t;&t;MIXER_WRITE(SOUND_MIXER_CD)
DECL|macro|SOUND_MIXER_WRITE_IMIX
mdefine_line|#define SOUND_MIXER_WRITE_IMIX&t;&t;MIXER_WRITE(SOUND_MIXER_IMIX)
DECL|macro|SOUND_MIXER_WRITE_ALTPCM
mdefine_line|#define SOUND_MIXER_WRITE_ALTPCM&t;MIXER_WRITE(SOUND_MIXER_ALTPCM)
DECL|macro|SOUND_MIXER_WRITE_RECLEV
mdefine_line|#define SOUND_MIXER_WRITE_RECLEV&t;MIXER_WRITE(SOUND_MIXER_RECLEV)
DECL|macro|SOUND_MIXER_WRITE_IGAIN
mdefine_line|#define SOUND_MIXER_WRITE_IGAIN&t;&t;MIXER_WRITE(SOUND_MIXER_IGAIN)
DECL|macro|SOUND_MIXER_WRITE_OGAIN
mdefine_line|#define SOUND_MIXER_WRITE_OGAIN&t;&t;MIXER_WRITE(SOUND_MIXER_OGAIN)
DECL|macro|SOUND_MIXER_WRITE_LINE1
mdefine_line|#define SOUND_MIXER_WRITE_LINE1&t;&t;MIXER_WRITE(SOUND_MIXER_LINE1)
DECL|macro|SOUND_MIXER_WRITE_LINE2
mdefine_line|#define SOUND_MIXER_WRITE_LINE2&t;&t;MIXER_WRITE(SOUND_MIXER_LINE2)
DECL|macro|SOUND_MIXER_WRITE_LINE3
mdefine_line|#define SOUND_MIXER_WRITE_LINE3&t;&t;MIXER_WRITE(SOUND_MIXER_LINE3)
multiline_comment|/* Obsolete macros */
DECL|macro|SOUND_MIXER_WRITE_MUTE
mdefine_line|#define SOUND_MIXER_WRITE_MUTE&t;&t;MIXER_WRITE(SOUND_MIXER_MUTE)
DECL|macro|SOUND_MIXER_WRITE_ENHANCE
mdefine_line|#define SOUND_MIXER_WRITE_ENHANCE&t;MIXER_WRITE(SOUND_MIXER_ENHANCE)
DECL|macro|SOUND_MIXER_WRITE_LOUD
mdefine_line|#define SOUND_MIXER_WRITE_LOUD&t;&t;MIXER_WRITE(SOUND_MIXER_LOUD)
DECL|macro|SOUND_MIXER_WRITE_RECSRC
mdefine_line|#define SOUND_MIXER_WRITE_RECSRC&t;MIXER_WRITE(SOUND_MIXER_RECSRC)
DECL|struct|mixer_info
r_typedef
r_struct
id|mixer_info
(brace
DECL|member|id
r_char
id|id
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|modify_counter
r_int
id|modify_counter
suffix:semicolon
DECL|member|fillers
r_int
id|fillers
(braket
l_int|10
)braket
suffix:semicolon
DECL|typedef|mixer_info
)brace
id|mixer_info
suffix:semicolon
DECL|struct|_old_mixer_info
r_typedef
r_struct
id|_old_mixer_info
multiline_comment|/* Obsolete */
(brace
DECL|member|id
r_char
id|id
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
l_int|32
)braket
suffix:semicolon
DECL|typedef|_old_mixer_info
)brace
id|_old_mixer_info
suffix:semicolon
DECL|macro|SOUND_MIXER_INFO
mdefine_line|#define SOUND_MIXER_INFO&t;&t;_SIOR (&squot;M&squot;, 101, mixer_info)
DECL|macro|SOUND_OLD_MIXER_INFO
mdefine_line|#define SOUND_OLD_MIXER_INFO&t;&t;_SIOR (&squot;M&squot;, 101, _old_mixer_info)
multiline_comment|/*&n; * A mechanism for accessing &quot;proprietary&quot; mixer features. This method&n; * permits passing 128 bytes of arbitrary data between a mixer application&n; * and the mixer driver. Interpretation of the record is defined by&n; * the particular mixer driver.&n; */
DECL|typedef|mixer_record
r_typedef
r_int
r_char
id|mixer_record
(braket
l_int|128
)braket
suffix:semicolon
DECL|macro|SOUND_MIXER_ACCESS
mdefine_line|#define SOUND_MIXER_ACCESS&t;&t;_SIOWR(&squot;M&squot;, 102, mixer_record)
multiline_comment|/*&n; * Two ioctls for special souncard function&n; */
DECL|macro|SOUND_MIXER_AGC
mdefine_line|#define SOUND_MIXER_AGC  _SIOWR(&squot;M&squot;, 103, int)
DECL|macro|SOUND_MIXER_3DSE
mdefine_line|#define SOUND_MIXER_3DSE  _SIOWR(&squot;M&squot;, 104, int)
multiline_comment|/*&n; * The SOUND_MIXER_PRIVATE# commands can be redefined by low level drivers.&n; * These features can be used when accessing device specific features.&n; */
DECL|macro|SOUND_MIXER_PRIVATE1
mdefine_line|#define SOUND_MIXER_PRIVATE1&t;&t;_SIOWR(&squot;M&squot;, 111, int)
DECL|macro|SOUND_MIXER_PRIVATE2
mdefine_line|#define SOUND_MIXER_PRIVATE2&t;&t;_SIOWR(&squot;M&squot;, 112, int)
DECL|macro|SOUND_MIXER_PRIVATE3
mdefine_line|#define SOUND_MIXER_PRIVATE3&t;&t;_SIOWR(&squot;M&squot;, 113, int)
DECL|macro|SOUND_MIXER_PRIVATE4
mdefine_line|#define SOUND_MIXER_PRIVATE4&t;&t;_SIOWR(&squot;M&squot;, 114, int)
DECL|macro|SOUND_MIXER_PRIVATE5
mdefine_line|#define SOUND_MIXER_PRIVATE5&t;&t;_SIOWR(&squot;M&squot;, 115, int)
multiline_comment|/*&n; * SOUND_MIXER_GETLEVELS and SOUND_MIXER_SETLEVELS calls can be used&n; * for querying current mixer settings from the driver and for loading&n; * default volume settings _prior_ activating the mixer (loading&n; * doesn&squot;t affect current state of the mixer hardware). These calls&n; * are for internal use only.&n; */
DECL|struct|mixer_vol_table
r_typedef
r_struct
id|mixer_vol_table
(brace
DECL|member|num
r_int
id|num
suffix:semicolon
multiline_comment|/* Index to volume table */
DECL|member|name
r_char
id|name
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|levels
r_int
id|levels
(braket
l_int|32
)braket
suffix:semicolon
DECL|typedef|mixer_vol_table
)brace
id|mixer_vol_table
suffix:semicolon
DECL|macro|SOUND_MIXER_GETLEVELS
mdefine_line|#define SOUND_MIXER_GETLEVELS&t;&t;_SIOWR(&squot;M&squot;, 116, mixer_vol_table)
DECL|macro|SOUND_MIXER_SETLEVELS
mdefine_line|#define SOUND_MIXER_SETLEVELS&t;&t;_SIOWR(&squot;M&squot;, 117, mixer_vol_table)
multiline_comment|/* &n; * An ioctl for identifying the driver version. It will return value&n; * of the SOUND_VERSION macro used when compiling the driver.&n; * This call was introduced in OSS version 3.6 and it will not work&n; * with earlier versions (returns EINVAL).&n; */
DECL|macro|OSS_GETVERSION
mdefine_line|#define OSS_GETVERSION&t;&t;&t;_SIOR (&squot;M&squot;, 118, int)
multiline_comment|/*&n; * Level 2 event types for /dev/sequencer&n; */
multiline_comment|/*&n; * The 4 most significant bits of byte 0 specify the class of&n; * the event: &n; *&n; *&t;0x8X = system level events,&n; *&t;0x9X = device/port specific events, event[1] = device/port,&n; *&t;&t;The last 4 bits give the subtype:&n; *&t;&t;&t;0x02&t;= Channel event (event[3] = chn).&n; *&t;&t;&t;0x01&t;= note event (event[4] = note).&n; *&t;&t;&t;(0x01 is not used alone but always with bit 0x02).&n; *&t;       event[2] = MIDI message code (0x80=note off etc.)&n; *&n; */
DECL|macro|EV_SEQ_LOCAL
mdefine_line|#define EV_SEQ_LOCAL&t;&t;0x80
DECL|macro|EV_TIMING
mdefine_line|#define EV_TIMING&t;&t;0x81
DECL|macro|EV_CHN_COMMON
mdefine_line|#define EV_CHN_COMMON&t;&t;0x92
DECL|macro|EV_CHN_VOICE
mdefine_line|#define EV_CHN_VOICE&t;&t;0x93
DECL|macro|EV_SYSEX
mdefine_line|#define EV_SYSEX&t;&t;0x94
multiline_comment|/*&n; * Event types 200 to 220 are reserved for application use.&n; * These numbers will not be used by the driver.&n; */
multiline_comment|/*&n; * Events for event type EV_CHN_VOICE&n; */
DECL|macro|MIDI_NOTEOFF
mdefine_line|#define MIDI_NOTEOFF&t;&t;0x80
DECL|macro|MIDI_NOTEON
mdefine_line|#define MIDI_NOTEON&t;&t;0x90
DECL|macro|MIDI_KEY_PRESSURE
mdefine_line|#define MIDI_KEY_PRESSURE&t;0xA0
multiline_comment|/*&n; * Events for event type EV_CHN_COMMON&n; */
DECL|macro|MIDI_CTL_CHANGE
mdefine_line|#define MIDI_CTL_CHANGE&t;&t;0xB0
DECL|macro|MIDI_PGM_CHANGE
mdefine_line|#define MIDI_PGM_CHANGE&t;&t;0xC0
DECL|macro|MIDI_CHN_PRESSURE
mdefine_line|#define MIDI_CHN_PRESSURE&t;0xD0
DECL|macro|MIDI_PITCH_BEND
mdefine_line|#define MIDI_PITCH_BEND&t;&t;0xE0
DECL|macro|MIDI_SYSTEM_PREFIX
mdefine_line|#define MIDI_SYSTEM_PREFIX&t;0xF0
multiline_comment|/*&n; * Timer event types&n; */
DECL|macro|TMR_WAIT_REL
mdefine_line|#define TMR_WAIT_REL&t;&t;1&t;/* Time relative to the prev time */
DECL|macro|TMR_WAIT_ABS
mdefine_line|#define TMR_WAIT_ABS&t;&t;2&t;/* Absolute time since TMR_START */
DECL|macro|TMR_STOP
mdefine_line|#define TMR_STOP&t;&t;3
DECL|macro|TMR_START
mdefine_line|#define TMR_START&t;&t;4
DECL|macro|TMR_CONTINUE
mdefine_line|#define TMR_CONTINUE&t;&t;5
DECL|macro|TMR_TEMPO
mdefine_line|#define TMR_TEMPO&t;&t;6
DECL|macro|TMR_ECHO
mdefine_line|#define TMR_ECHO&t;&t;8
DECL|macro|TMR_CLOCK
mdefine_line|#define TMR_CLOCK&t;&t;9&t;/* MIDI clock */
DECL|macro|TMR_SPP
mdefine_line|#define TMR_SPP&t;&t;&t;10&t;/* Song position pointer */
DECL|macro|TMR_TIMESIG
mdefine_line|#define TMR_TIMESIG&t;&t;11&t;/* Time signature */
multiline_comment|/*&n; *&t;Local event types&n; */
DECL|macro|LOCL_STARTAUDIO
mdefine_line|#define LOCL_STARTAUDIO&t;&t;1
macro_line|#if (!defined(__KERNEL__) &amp;&amp; !defined(KERNEL) &amp;&amp; !defined(INKERNEL) &amp;&amp; !defined(_KERNEL)) || defined(USE_SEQ_MACROS) 
multiline_comment|/*&n; *&t;Some convenience macros to simplify programming of the&n; *&t;/dev/sequencer interface&n; *&n; *&t;These macros define the API which should be used when possible.&n; */
DECL|macro|SEQ_DECLAREBUF
mdefine_line|#define SEQ_DECLAREBUF()&t;&t;SEQ_USE_EXTBUF()
r_void
id|seqbuf_dump
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* This function must be provided by programs */
r_extern
r_int
id|OSS_init
c_func
(paren
r_int
id|seqfd
comma
r_int
id|buflen
)paren
suffix:semicolon
r_extern
r_void
id|OSS_seqbuf_dump
c_func
(paren
r_int
id|fd
comma
r_int
r_char
op_star
id|buf
comma
r_int
id|buflen
)paren
suffix:semicolon
r_extern
r_void
id|OSS_seq_advbuf
c_func
(paren
r_int
id|len
comma
r_int
id|fd
comma
r_int
r_char
op_star
id|buf
comma
r_int
id|buflen
)paren
suffix:semicolon
r_extern
r_void
id|OSS_seq_needbuf
c_func
(paren
r_int
id|len
comma
r_int
id|fd
comma
r_int
r_char
op_star
id|buf
comma
r_int
id|buflen
)paren
suffix:semicolon
r_extern
r_void
id|OSS_patch_caching
c_func
(paren
r_int
id|dev
comma
r_int
id|chn
comma
r_int
id|patch
comma
r_int
id|fd
comma
r_int
r_char
op_star
id|buf
comma
r_int
id|buflen
)paren
suffix:semicolon
r_extern
r_void
id|OSS_drum_caching
c_func
(paren
r_int
id|dev
comma
r_int
id|chn
comma
r_int
id|patch
comma
r_int
id|fd
comma
r_int
r_char
op_star
id|buf
comma
r_int
id|buflen
)paren
suffix:semicolon
r_extern
r_void
id|OSS_write_patch
c_func
(paren
r_int
id|fd
comma
r_int
r_char
op_star
id|buf
comma
r_int
id|len
)paren
suffix:semicolon
r_extern
r_int
id|OSS_write_patch2
c_func
(paren
r_int
id|fd
comma
r_int
r_char
op_star
id|buf
comma
r_int
id|len
)paren
suffix:semicolon
DECL|macro|SEQ_PM_DEFINES
mdefine_line|#define SEQ_PM_DEFINES int __foo_bar___
macro_line|#ifdef OSSLIB
DECL|macro|SEQ_USE_EXTBUF
macro_line|#  define SEQ_USE_EXTBUF() &bslash;&n;&t;&t;extern unsigned char *_seqbuf; &bslash;&n;&t;&t;extern int _seqbuflen;extern int _seqbufptr
DECL|macro|SEQ_DEFINEBUF
macro_line|#  define SEQ_DEFINEBUF(len) SEQ_USE_EXTBUF();static int _requested_seqbuflen=len
DECL|macro|_SEQ_ADVBUF
macro_line|#  define _SEQ_ADVBUF(len) OSS_seq_advbuf(len, seqfd, _seqbuf, _seqbuflen)
DECL|macro|_SEQ_NEEDBUF
macro_line|#  define _SEQ_NEEDBUF(len) OSS_seq_needbuf(len, seqfd, _seqbuf, _seqbuflen)
DECL|macro|SEQ_DUMPBUF
macro_line|#  define SEQ_DUMPBUF() OSS_seqbuf_dump(seqfd, _seqbuf, _seqbuflen)
DECL|macro|SEQ_LOAD_GMINSTR
macro_line|#  define SEQ_LOAD_GMINSTR(dev, instr) &bslash;&n;&t;&t;OSS_patch_caching(dev, -1, instr, seqfd, _seqbuf, _seqbuflen)
DECL|macro|SEQ_LOAD_GMDRUM
macro_line|#  define SEQ_LOAD_GMDRUM(dev, drum) &bslash;&n;&t;&t;OSS_drum_caching(dev, -1, drum, seqfd, _seqbuf, _seqbuflen)
macro_line|#else /* !OSSLIB */
DECL|macro|SEQ_LOAD_GMINSTR
macro_line|#  define SEQ_LOAD_GMINSTR(dev, instr)
DECL|macro|SEQ_LOAD_GMDRUM
macro_line|#  define SEQ_LOAD_GMDRUM(dev, drum)
DECL|macro|SEQ_USE_EXTBUF
macro_line|#  define SEQ_USE_EXTBUF() &bslash;&n;&t;&t;extern unsigned char _seqbuf[]; &bslash;&n;&t;&t;extern int _seqbuflen;extern int _seqbufptr
macro_line|#ifndef USE_SIMPLE_MACROS
multiline_comment|/* Sample seqbuf_dump() implementation:&n; *&n; *&t;SEQ_DEFINEBUF (2048);&t;-- Defines a buffer for 2048 bytes&n; *&n; *&t;int seqfd;&t;&t;-- The file descriptor for /dev/sequencer.&n; *&n; *&t;void&n; *&t;seqbuf_dump ()&n; *&t;{&n; *&t;  if (_seqbufptr)&n; *&t;    if (write (seqfd, _seqbuf, _seqbufptr) == -1)&n; *&t;      {&n; *&t;&t;perror (&quot;write /dev/sequencer&quot;);&n; *&t;&t;exit (-1);&n; *&t;      }&n; *&t;  _seqbufptr = 0;&n; *&t;}&n; */
DECL|macro|SEQ_DEFINEBUF
mdefine_line|#define SEQ_DEFINEBUF(len)&t;&t;unsigned char _seqbuf[len]; int _seqbuflen = len;int _seqbufptr = 0
DECL|macro|_SEQ_NEEDBUF
mdefine_line|#define _SEQ_NEEDBUF(len)&t;&t;if ((_seqbufptr+(len)) &gt; _seqbuflen) seqbuf_dump()
DECL|macro|_SEQ_ADVBUF
mdefine_line|#define _SEQ_ADVBUF(len)&t;&t;_seqbufptr += len
DECL|macro|SEQ_DUMPBUF
mdefine_line|#define SEQ_DUMPBUF&t;&t;&t;seqbuf_dump
macro_line|#else
multiline_comment|/*&n; * This variation of the sequencer macros is used just to format one event&n; * using fixed buffer.&n; * &n; * The program using the macro library must define the following macros before&n; * using this library.&n; *&n; * #define _seqbuf &t;&t; name of the buffer (unsigned char[]) &n; * #define _SEQ_ADVBUF(len)&t; If the applic needs to know the exact&n; *&t;&t;&t;&t; size of the event, this macro can be used.&n; *&t;&t;&t;&t; Otherwise this must be defined as empty.&n; * #define _seqbufptr&t;&t; Define the name of index variable or 0 if&n; *&t;&t;&t;&t; not required. &n; */
DECL|macro|_SEQ_NEEDBUF
mdefine_line|#define _SEQ_NEEDBUF(len)&t;/* empty */
macro_line|#endif
macro_line|#endif /* !OSSLIB */
DECL|macro|SEQ_VOLUME_MODE
mdefine_line|#define SEQ_VOLUME_MODE(dev, mode)&t;{_SEQ_NEEDBUF(8);&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr] = SEQ_EXTENDED;&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr+1] = SEQ_VOLMODE;&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr+2] = (dev);&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr+3] = (mode);&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr+4] = 0;&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr+5] = 0;&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr+6] = 0;&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr+7] = 0;&bslash;&n;&t;&t;&t;&t;&t;_SEQ_ADVBUF(8);}
multiline_comment|/*&n; * Midi voice messages&n; */
DECL|macro|_CHN_VOICE
mdefine_line|#define _CHN_VOICE(dev, event, chn, note, parm) &bslash;&n;&t;&t;&t;&t;&t;{_SEQ_NEEDBUF(8);&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr] = EV_CHN_VOICE;&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr+1] = (dev);&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr+2] = (event);&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr+3] = (chn);&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr+4] = (note);&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr+5] = (parm);&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr+6] = (0);&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr+7] = 0;&bslash;&n;&t;&t;&t;&t;&t;_SEQ_ADVBUF(8);}
DECL|macro|SEQ_START_NOTE
mdefine_line|#define SEQ_START_NOTE(dev, chn, note, vol) &bslash;&n;&t;&t;_CHN_VOICE(dev, MIDI_NOTEON, chn, note, vol)
DECL|macro|SEQ_STOP_NOTE
mdefine_line|#define SEQ_STOP_NOTE(dev, chn, note, vol) &bslash;&n;&t;&t;_CHN_VOICE(dev, MIDI_NOTEOFF, chn, note, vol)
DECL|macro|SEQ_KEY_PRESSURE
mdefine_line|#define SEQ_KEY_PRESSURE(dev, chn, note, pressure) &bslash;&n;&t;&t;_CHN_VOICE(dev, MIDI_KEY_PRESSURE, chn, note, pressure)
multiline_comment|/*&n; * Midi channel messages&n; */
DECL|macro|_CHN_COMMON
mdefine_line|#define _CHN_COMMON(dev, event, chn, p1, p2, w14) &bslash;&n;&t;&t;&t;&t;&t;{_SEQ_NEEDBUF(8);&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr] = EV_CHN_COMMON;&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr+1] = (dev);&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr+2] = (event);&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr+3] = (chn);&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr+4] = (p1);&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr+5] = (p2);&bslash;&n;&t;&t;&t;&t;&t;*(short *)&amp;_seqbuf[_seqbufptr+6] = (w14);&bslash;&n;&t;&t;&t;&t;&t;_SEQ_ADVBUF(8);}
multiline_comment|/*&n; * SEQ_SYSEX permits sending of sysex messages. (It may look that it permits&n; * sending any MIDI bytes but it&squot;s absolutely not possible. Trying to do&n; * so _will_ cause problems with MPU401 intelligent mode).&n; *&n; * Sysex messages are sent in blocks of 1 to 6 bytes. Longer messages must be &n; * sent by calling SEQ_SYSEX() several times (there must be no other events&n; * between them). First sysex fragment must have 0xf0 in the first byte&n; * and the last byte (buf[len-1] of the last fragment must be 0xf7. No byte&n; * between these sysex start and end markers cannot be larger than 0x7f. Also&n; * lengths of each fragments (except the last one) must be 6.&n; *&n; * Breaking the above rules may work with some MIDI ports but is likely to&n; * cause fatal problems with some other devices (such as MPU401).&n; */
DECL|macro|SEQ_SYSEX
mdefine_line|#define SEQ_SYSEX(dev, buf, len) &bslash;&n;&t;&t;&t;&t;&t;{int ii, ll=(len); &bslash;&n;&t;&t;&t;&t;&t; unsigned char *bufp=buf;&bslash;&n;&t;&t;&t;&t;&t; if (ll&gt;6)ll=6;&bslash;&n;&t;&t;&t;&t;&t;_SEQ_NEEDBUF(8);&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr] = EV_SYSEX;&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr+1] = (dev);&bslash;&n;&t;&t;&t;&t;&t;for(ii=0;ii&lt;ll;ii++)&bslash;&n;&t;&t;&t;&t;&t;   _seqbuf[_seqbufptr+ii+2] = bufp[ii];&bslash;&n;&t;&t;&t;&t;&t;for(ii=ll;ii&lt;6;ii++)&bslash;&n;&t;&t;&t;&t;&t;   _seqbuf[_seqbufptr+ii+2] = 0xff;&bslash;&n;&t;&t;&t;&t;&t;_SEQ_ADVBUF(8);}
DECL|macro|SEQ_CHN_PRESSURE
mdefine_line|#define SEQ_CHN_PRESSURE(dev, chn, pressure) &bslash;&n;&t;&t;_CHN_COMMON(dev, MIDI_CHN_PRESSURE, chn, pressure, 0, 0)
DECL|macro|SEQ_SET_PATCH
mdefine_line|#define SEQ_SET_PATCH SEQ_PGM_CHANGE
macro_line|#ifdef OSSLIB
DECL|macro|SEQ_PGM_CHANGE
macro_line|#   define SEQ_PGM_CHANGE(dev, chn, patch) &bslash;&n;&t;&t;{OSS_patch_caching(dev, chn, patch, seqfd, _seqbuf, _seqbuflen); &bslash;&n;&t;&t; _CHN_COMMON(dev, MIDI_PGM_CHANGE, chn, patch, 0, 0);}
macro_line|#else
DECL|macro|SEQ_PGM_CHANGE
macro_line|#   define SEQ_PGM_CHANGE(dev, chn, patch) &bslash;&n;&t;&t;_CHN_COMMON(dev, MIDI_PGM_CHANGE, chn, patch, 0, 0)
macro_line|#endif
DECL|macro|SEQ_CONTROL
mdefine_line|#define SEQ_CONTROL(dev, chn, controller, value) &bslash;&n;&t;&t;_CHN_COMMON(dev, MIDI_CTL_CHANGE, chn, controller, 0, value)
DECL|macro|SEQ_BENDER
mdefine_line|#define SEQ_BENDER(dev, chn, value) &bslash;&n;&t;&t;_CHN_COMMON(dev, MIDI_PITCH_BEND, chn, 0, 0, value)
DECL|macro|SEQ_V2_X_CONTROL
mdefine_line|#define SEQ_V2_X_CONTROL(dev, voice, controller, value)&t;{_SEQ_NEEDBUF(8);&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr] = SEQ_EXTENDED;&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr+1] = SEQ_CONTROLLER;&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr+2] = (dev);&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr+3] = (voice);&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr+4] = (controller);&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr+5] = ((value)&amp;0xff);&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr+6] = ((value&gt;&gt;8)&amp;0xff);&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr+7] = 0;&bslash;&n;&t;&t;&t;&t;&t;_SEQ_ADVBUF(8);}
multiline_comment|/*&n; * The following 5 macros are incorrectly implemented and obsolete.&n; * Use SEQ_BENDER and SEQ_CONTROL (with proper controller) instead.&n; */
DECL|macro|SEQ_PITCHBEND
mdefine_line|#define SEQ_PITCHBEND(dev, voice, value) SEQ_V2_X_CONTROL(dev, voice, CTRL_PITCH_BENDER, value)
DECL|macro|SEQ_BENDER_RANGE
mdefine_line|#define SEQ_BENDER_RANGE(dev, voice, value) SEQ_V2_X_CONTROL(dev, voice, CTRL_PITCH_BENDER_RANGE, value)
DECL|macro|SEQ_EXPRESSION
mdefine_line|#define SEQ_EXPRESSION(dev, voice, value) SEQ_CONTROL(dev, voice, CTL_EXPRESSION, value*128)
DECL|macro|SEQ_MAIN_VOLUME
mdefine_line|#define SEQ_MAIN_VOLUME(dev, voice, value) SEQ_CONTROL(dev, voice, CTL_MAIN_VOLUME, (value*16383)/100)
DECL|macro|SEQ_PANNING
mdefine_line|#define SEQ_PANNING(dev, voice, pos) SEQ_CONTROL(dev, voice, CTL_PAN, (pos+128) / 2)
multiline_comment|/*&n; * Timing and syncronization macros&n; */
DECL|macro|_TIMER_EVENT
mdefine_line|#define _TIMER_EVENT(ev, parm)&t;&t;{_SEQ_NEEDBUF(8);&bslash;&n;&t;&t;&t;&t; &t;_seqbuf[_seqbufptr+0] = EV_TIMING; &bslash;&n;&t;&t;&t;&t; &t;_seqbuf[_seqbufptr+1] = (ev); &bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr+2] = 0;&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr+3] = 0;&bslash;&n;&t;&t;&t;&t; &t;*(unsigned int *)&amp;_seqbuf[_seqbufptr+4] = (parm); &bslash;&n;&t;&t;&t;&t;&t;_SEQ_ADVBUF(8);}
DECL|macro|SEQ_START_TIMER
mdefine_line|#define SEQ_START_TIMER()&t;&t;_TIMER_EVENT(TMR_START, 0)
DECL|macro|SEQ_STOP_TIMER
mdefine_line|#define SEQ_STOP_TIMER()&t;&t;_TIMER_EVENT(TMR_STOP, 0)
DECL|macro|SEQ_CONTINUE_TIMER
mdefine_line|#define SEQ_CONTINUE_TIMER()&t;&t;_TIMER_EVENT(TMR_CONTINUE, 0)
DECL|macro|SEQ_WAIT_TIME
mdefine_line|#define SEQ_WAIT_TIME(ticks)&t;&t;_TIMER_EVENT(TMR_WAIT_ABS, ticks)
DECL|macro|SEQ_DELTA_TIME
mdefine_line|#define SEQ_DELTA_TIME(ticks)&t;&t;_TIMER_EVENT(TMR_WAIT_REL, ticks)
DECL|macro|SEQ_ECHO_BACK
mdefine_line|#define SEQ_ECHO_BACK(key)&t;&t;_TIMER_EVENT(TMR_ECHO, key)
DECL|macro|SEQ_SET_TEMPO
mdefine_line|#define SEQ_SET_TEMPO(value)&t;&t;_TIMER_EVENT(TMR_TEMPO, value)
DECL|macro|SEQ_SONGPOS
mdefine_line|#define SEQ_SONGPOS(pos)&t;&t;_TIMER_EVENT(TMR_SPP, pos)
DECL|macro|SEQ_TIME_SIGNATURE
mdefine_line|#define SEQ_TIME_SIGNATURE(sig)&t;&t;_TIMER_EVENT(TMR_TIMESIG, sig)
multiline_comment|/*&n; * Local control events&n; */
DECL|macro|_LOCAL_EVENT
mdefine_line|#define _LOCAL_EVENT(ev, parm)&t;&t;{_SEQ_NEEDBUF(8);&bslash;&n;&t;&t;&t;&t; &t;_seqbuf[_seqbufptr+0] = EV_SEQ_LOCAL; &bslash;&n;&t;&t;&t;&t; &t;_seqbuf[_seqbufptr+1] = (ev); &bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr+2] = 0;&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr+3] = 0;&bslash;&n;&t;&t;&t;&t; &t;*(unsigned int *)&amp;_seqbuf[_seqbufptr+4] = (parm); &bslash;&n;&t;&t;&t;&t;&t;_SEQ_ADVBUF(8);}
DECL|macro|SEQ_PLAYAUDIO
mdefine_line|#define SEQ_PLAYAUDIO(devmask)&t;&t;_LOCAL_EVENT(LOCL_STARTAUDIO, devmask)
multiline_comment|/*&n; * Events for the level 1 interface only &n; */
DECL|macro|SEQ_MIDIOUT
mdefine_line|#define SEQ_MIDIOUT(device, byte)&t;{_SEQ_NEEDBUF(4);&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr] = SEQ_MIDIPUTC;&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr+1] = (byte);&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr+2] = (device);&bslash;&n;&t;&t;&t;&t;&t;_seqbuf[_seqbufptr+3] = 0;&bslash;&n;&t;&t;&t;&t;&t;_SEQ_ADVBUF(4);}
multiline_comment|/*&n; * Patch loading.&n; */
macro_line|#ifdef OSSLIB
DECL|macro|SEQ_WRPATCH
macro_line|#   define SEQ_WRPATCH(patchx, len) &bslash;&n;&t;&t;OSS_write_patch(seqfd, (char*)(patchx), len)
DECL|macro|SEQ_WRPATCH2
macro_line|#   define SEQ_WRPATCH2(patchx, len) &bslash;&n;&t;&t;OSS_write_patch2(seqfd, (char*)(patchx), len)
macro_line|#else
DECL|macro|SEQ_WRPATCH
macro_line|#   define SEQ_WRPATCH(patchx, len) &bslash;&n;&t;&t;{if (_seqbufptr) SEQ_DUMPBUF();&bslash;&n;&t;&t; if (write(seqfd, (char*)(patchx), len)==-1) &bslash;&n;&t;&t;    perror(&quot;Write patch: /dev/sequencer&quot;);}
DECL|macro|SEQ_WRPATCH2
macro_line|#   define SEQ_WRPATCH2(patchx, len) &bslash;&n;&t;&t;(SEQ_DUMPBUF(), write(seqfd, (char*)(patchx), len))
macro_line|#endif
macro_line|#endif
macro_line|#endif
eof
