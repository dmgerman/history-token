multiline_comment|/*&n; * include/asm-sparc/audioio.h&n; *&n; * Sparc Audio Midlayer&n; * Copyright (C) 1996 Thomas K. Dyas (tdyas@noc.rutgers.edu)&n; */
macro_line|#ifndef _AUDIOIO_H_
DECL|macro|_AUDIOIO_H_
mdefine_line|#define _AUDIOIO_H_
multiline_comment|/*&n; *&t;SunOS/Solaris /dev/audio interface&n; */
macro_line|#if defined(__KERNEL__) || !defined(__GLIBC__) || (__GLIBC__ &lt; 2)
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/ioctl.h&gt;
macro_line|#endif
multiline_comment|/*&n; * This structure contains state information for audio device IO streams.&n; */
DECL|struct|audio_prinfo
r_typedef
r_struct
id|audio_prinfo
(brace
multiline_comment|/*&n;&t; * The following values describe the audio data encoding.&n;&t; */
DECL|member|sample_rate
r_int
r_int
id|sample_rate
suffix:semicolon
multiline_comment|/* samples per second */
DECL|member|channels
r_int
r_int
id|channels
suffix:semicolon
multiline_comment|/* number of interleaved channels */
DECL|member|precision
r_int
r_int
id|precision
suffix:semicolon
multiline_comment|/* bit-width of each sample */
DECL|member|encoding
r_int
r_int
id|encoding
suffix:semicolon
multiline_comment|/* data encoding method */
multiline_comment|/*&n;&t; * The following values control audio device configuration&n;&t; */
DECL|member|gain
r_int
r_int
id|gain
suffix:semicolon
multiline_comment|/* gain level: 0 - 255 */
DECL|member|port
r_int
r_int
id|port
suffix:semicolon
multiline_comment|/* selected I/O port (see below) */
DECL|member|avail_ports
r_int
r_int
id|avail_ports
suffix:semicolon
multiline_comment|/* available I/O ports (see below) */
DECL|member|_xxx
r_int
r_int
id|_xxx
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Reserved for future use */
DECL|member|buffer_size
r_int
r_int
id|buffer_size
suffix:semicolon
multiline_comment|/* I/O buffer size */
multiline_comment|/*&n;&t; * The following values describe driver state&n;&t; */
DECL|member|samples
r_int
r_int
id|samples
suffix:semicolon
multiline_comment|/* number of samples converted */
DECL|member|eof
r_int
r_int
id|eof
suffix:semicolon
multiline_comment|/* End Of File counter (play only) */
DECL|member|pause
r_int
r_char
id|pause
suffix:semicolon
multiline_comment|/* non-zero for pause, zero to resume */
DECL|member|error
r_int
r_char
id|error
suffix:semicolon
multiline_comment|/* non-zero if overflow/underflow */
DECL|member|waiting
r_int
r_char
id|waiting
suffix:semicolon
multiline_comment|/* non-zero if a process wants access */
DECL|member|balance
r_int
r_char
id|balance
suffix:semicolon
multiline_comment|/* stereo channel balance */
DECL|member|minordev
r_int
r_int
id|minordev
suffix:semicolon
multiline_comment|/*&n;&t; * The following values are read-only state flags&n;&t; */
DECL|member|open
r_int
r_char
id|open
suffix:semicolon
multiline_comment|/* non-zero if open access permitted */
DECL|member|active
r_int
r_char
id|active
suffix:semicolon
multiline_comment|/* non-zero if I/O is active */
DECL|typedef|audio_prinfo_t
)brace
id|audio_prinfo_t
suffix:semicolon
multiline_comment|/*&n; * This structure describes the current state of the audio device.&n; */
DECL|struct|audio_info
r_typedef
r_struct
id|audio_info
(brace
multiline_comment|/*&n;&t; * Per-stream information&n;&t; */
DECL|member|play
id|audio_prinfo_t
id|play
suffix:semicolon
multiline_comment|/* output status information */
DECL|member|record
id|audio_prinfo_t
id|record
suffix:semicolon
multiline_comment|/* input status information */
multiline_comment|/*&n;&t; * Per-unit/channel information&n;&t; */
DECL|member|monitor_gain
r_int
r_int
id|monitor_gain
suffix:semicolon
multiline_comment|/* input to output mix: 0 - 255 */
DECL|member|output_muted
r_int
r_char
id|output_muted
suffix:semicolon
multiline_comment|/* non-zero if output is muted */
DECL|member|_xxx
r_int
r_char
id|_xxx
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* Reserved for future use */
DECL|member|_yyy
r_int
r_int
id|_yyy
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* Reserved for future use */
DECL|typedef|audio_info_t
)brace
id|audio_info_t
suffix:semicolon
multiline_comment|/*&n; * Audio encoding types&n; */
DECL|macro|AUDIO_ENCODING_NONE
mdefine_line|#define&t;AUDIO_ENCODING_NONE&t;(0)&t;/* no encoding assigned&t;  */
DECL|macro|AUDIO_ENCODING_ULAW
mdefine_line|#define&t;AUDIO_ENCODING_ULAW&t;(1)&t;/* u-law encoding&t;  */
DECL|macro|AUDIO_ENCODING_ALAW
mdefine_line|#define&t;AUDIO_ENCODING_ALAW&t;(2)&t;/* A-law encoding&t;  */
DECL|macro|AUDIO_ENCODING_LINEAR
mdefine_line|#define&t;AUDIO_ENCODING_LINEAR&t;(3)&t;/* Linear PCM encoding&t;  */
DECL|macro|AUDIO_ENCODING_FLOAT
mdefine_line|#define AUDIO_ENCODING_FLOAT    (4)     /* IEEE float (-1. &lt;-&gt; +1.) */
DECL|macro|AUDIO_ENCODING_DVI
mdefine_line|#define&t;AUDIO_ENCODING_DVI&t;(104)&t;/* DVI ADPCM&t;&t;  */
DECL|macro|AUDIO_ENCODING_LINEAR8
mdefine_line|#define&t;AUDIO_ENCODING_LINEAR8&t;(105)&t;/* 8 bit UNSIGNED&t;  */
DECL|macro|AUDIO_ENCODING_LINEARLE
mdefine_line|#define&t;AUDIO_ENCODING_LINEARLE&t;(106)&t;/* Linear PCM LE encoding */
multiline_comment|/*&n; * These ranges apply to record, play, and monitor gain values&n; */
DECL|macro|AUDIO_MIN_GAIN
mdefine_line|#define&t;AUDIO_MIN_GAIN&t;(0)&t;/* minimum gain value */
DECL|macro|AUDIO_MAX_GAIN
mdefine_line|#define&t;AUDIO_MAX_GAIN&t;(255)&t;/* maximum gain value */
multiline_comment|/*&n; * These values apply to the balance field to adjust channel gain values&n; */
DECL|macro|AUDIO_LEFT_BALANCE
mdefine_line|#define&t;AUDIO_LEFT_BALANCE&t;(0)&t;/* left channel only&t;*/
DECL|macro|AUDIO_MID_BALANCE
mdefine_line|#define&t;AUDIO_MID_BALANCE&t;(32)&t;/* equal left/right channel */
DECL|macro|AUDIO_RIGHT_BALANCE
mdefine_line|#define&t;AUDIO_RIGHT_BALANCE&t;(64)&t;/* right channel only&t;*/
DECL|macro|AUDIO_BALANCE_SHIFT
mdefine_line|#define&t;AUDIO_BALANCE_SHIFT&t;(3)
multiline_comment|/*&n; * Generic minimum/maximum limits for number of channels, both modes&n; */
DECL|macro|AUDIO_MIN_PLAY_CHANNELS
mdefine_line|#define&t;AUDIO_MIN_PLAY_CHANNELS&t;(1)
DECL|macro|AUDIO_MAX_PLAY_CHANNELS
mdefine_line|#define&t;AUDIO_MAX_PLAY_CHANNELS&t;(4)
DECL|macro|AUDIO_MIN_REC_CHANNELS
mdefine_line|#define&t;AUDIO_MIN_REC_CHANNELS&t;(1)
DECL|macro|AUDIO_MAX_REC_CHANNELS
mdefine_line|#define&t;AUDIO_MAX_REC_CHANNELS&t;(4)
multiline_comment|/*&n; * Generic minimum/maximum limits for sample precision&n; */
DECL|macro|AUDIO_MIN_PLAY_PRECISION
mdefine_line|#define&t;AUDIO_MIN_PLAY_PRECISION&t;(8)
DECL|macro|AUDIO_MAX_PLAY_PRECISION
mdefine_line|#define&t;AUDIO_MAX_PLAY_PRECISION&t;(32)
DECL|macro|AUDIO_MIN_REC_PRECISION
mdefine_line|#define&t;AUDIO_MIN_REC_PRECISION&t;&t;(8)
DECL|macro|AUDIO_MAX_REC_PRECISION
mdefine_line|#define&t;AUDIO_MAX_REC_PRECISION&t;&t;(32)
multiline_comment|/*&n; * Define some convenient names for typical audio ports&n; */
multiline_comment|/*&n; * output ports (several may be enabled simultaneously)&n; */
DECL|macro|AUDIO_SPEAKER
mdefine_line|#define&t;AUDIO_SPEAKER&t;&t;0x01&t;/* output to built-in speaker */
DECL|macro|AUDIO_HEADPHONE
mdefine_line|#define&t;AUDIO_HEADPHONE&t;&t;0x02&t;/* output to headphone jack */
DECL|macro|AUDIO_LINE_OUT
mdefine_line|#define&t;AUDIO_LINE_OUT&t;&t;0x04&t;/* output to line out&t; */
multiline_comment|/*&n; * input ports (usually only one at a time)&n; */
DECL|macro|AUDIO_MICROPHONE
mdefine_line|#define&t;AUDIO_MICROPHONE&t;0x01&t;/* input from microphone */
DECL|macro|AUDIO_LINE_IN
mdefine_line|#define&t;AUDIO_LINE_IN&t;&t;0x02&t;/* input from line in&t; */
DECL|macro|AUDIO_CD
mdefine_line|#define&t;AUDIO_CD&t;&t;0x04&t;/* input from on-board CD inputs */
DECL|macro|AUDIO_INTERNAL_CD_IN
mdefine_line|#define&t;AUDIO_INTERNAL_CD_IN&t;AUDIO_CD&t;/* input from internal CDROM */
DECL|macro|AUDIO_ANALOG_LOOPBACK
mdefine_line|#define AUDIO_ANALOG_LOOPBACK   0x40    /* input from output */
multiline_comment|/*&n; * This macro initializes an audio_info structure to &squot;harmless&squot; values.&n; * Note that (~0) might not be a harmless value for a flag that was&n; * a signed int.&n; */
DECL|macro|AUDIO_INITINFO
mdefine_line|#define&t;AUDIO_INITINFO(i)&t;{&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned int&t;*__x__;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;for (__x__ = (unsigned int *)(i);&t;&t;&t;&t;&bslash;&n;&t;    (char *) __x__ &lt; (((char *)(i)) + sizeof (audio_info_t));&t;&bslash;&n;&t;    *__x__++ = ~0);&t;&t;&t;&t;&t;&t;&bslash;&n;}
multiline_comment|/*&n; * These allow testing for what the user wants to set &n; */
DECL|macro|AUD_INITVALUE
mdefine_line|#define AUD_INITVALUE   (~0)
DECL|macro|Modify
mdefine_line|#define Modify(X)       ((unsigned int)(X) != AUD_INITVALUE)
DECL|macro|Modifys
mdefine_line|#define Modifys(X)      ((X) != (unsigned short)AUD_INITVALUE)
DECL|macro|Modifyc
mdefine_line|#define Modifyc(X)      ((X) != (unsigned char)AUD_INITVALUE)
multiline_comment|/*&n; * Parameter for the AUDIO_GETDEV ioctl to determine current&n; * audio devices.&n; */
DECL|macro|MAX_AUDIO_DEV_LEN
mdefine_line|#define&t;MAX_AUDIO_DEV_LEN&t;(16)
DECL|struct|audio_device
r_typedef
r_struct
id|audio_device
(brace
DECL|member|name
r_char
id|name
(braket
id|MAX_AUDIO_DEV_LEN
)braket
suffix:semicolon
DECL|member|version
r_char
id|version
(braket
id|MAX_AUDIO_DEV_LEN
)braket
suffix:semicolon
DECL|member|config
r_char
id|config
(braket
id|MAX_AUDIO_DEV_LEN
)braket
suffix:semicolon
DECL|typedef|audio_device_t
)brace
id|audio_device_t
suffix:semicolon
multiline_comment|/*&n; * Ioctl calls for the audio device.&n; */
multiline_comment|/*&n; * AUDIO_GETINFO retrieves the current state of the audio device.&n; *&n; * AUDIO_SETINFO copies all fields of the audio_info structure whose&n; * values are not set to the initialized value (-1) to the device state.&n; * It performs an implicit AUDIO_GETINFO to return the new state of the&n; * device.  Note that the record.samples and play.samples fields are set&n; * to the last value before the AUDIO_SETINFO took effect.  This allows&n; * an application to reset the counters while atomically retrieving the&n; * last value.&n; *&n; * AUDIO_DRAIN suspends the calling process until the write buffers are&n; * empty.&n; *&n; * AUDIO_GETDEV returns a structure of type audio_device_t which contains&n; * three strings.  The string &quot;name&quot; is a short identifying string (for&n; * example, the SBus Fcode name string), the string &quot;version&quot; identifies&n; * the current version of the device, and the &quot;config&quot; string identifies&n; * the specific configuration of the audio stream.  All fields are&n; * device-dependent -- see the device specific manual pages for details.&n; *&n; * AUDIO_GETDEV_SUNOS returns a number which is an audio device defined &n; * herein (making it not too portable)&n; *&n; * AUDIO_FLUSH stops all playback and recording, clears all queued buffers, &n; * resets error counters, and restarts recording and playback as appropriate&n; * for the current sampling mode.&n; */
DECL|macro|AUDIO_GETINFO
mdefine_line|#define&t;AUDIO_GETINFO&t;_IOR(&squot;A&squot;, 1, audio_info_t)
DECL|macro|AUDIO_SETINFO
mdefine_line|#define&t;AUDIO_SETINFO&t;_IOWR(&squot;A&squot;, 2, audio_info_t)
DECL|macro|AUDIO_DRAIN
mdefine_line|#define&t;AUDIO_DRAIN&t;_IO(&squot;A&squot;, 3)
DECL|macro|AUDIO_GETDEV
mdefine_line|#define&t;AUDIO_GETDEV&t;_IOR(&squot;A&squot;, 4, audio_device_t)
DECL|macro|AUDIO_GETDEV_SUNOS
mdefine_line|#define&t;AUDIO_GETDEV_SUNOS&t;_IOR(&squot;A&squot;, 4, int)
DECL|macro|AUDIO_FLUSH
mdefine_line|#define AUDIO_FLUSH     _IO(&squot;A&squot;, 5)
multiline_comment|/* Define possible audio hardware configurations for &n; * old SunOS-style AUDIO_GETDEV ioctl */
DECL|macro|AUDIO_DEV_UNKNOWN
mdefine_line|#define AUDIO_DEV_UNKNOWN       (0)     /* not defined */
DECL|macro|AUDIO_DEV_AMD
mdefine_line|#define AUDIO_DEV_AMD           (1)     /* audioamd device */
DECL|macro|AUDIO_DEV_SPEAKERBOX
mdefine_line|#define AUDIO_DEV_SPEAKERBOX    (2)     /* dbri device with speakerbox */
DECL|macro|AUDIO_DEV_CODEC
mdefine_line|#define AUDIO_DEV_CODEC         (3)     /* dbri device (internal speaker) */
DECL|macro|AUDIO_DEV_CS4231
mdefine_line|#define AUDIO_DEV_CS4231        (5)     /* cs4231 device */
multiline_comment|/*&n; * The following ioctl sets the audio device into an internal loopback mode,&n; * if the hardware supports this.  The argument is TRUE to set loopback,&n; * FALSE to reset to normal operation.  If the hardware does not support&n; * internal loopback, the ioctl should fail with EINVAL.&n; * Causes ADC data to be digitally mixed in and sent to the DAC.&n; */
DECL|macro|AUDIO_DIAG_LOOPBACK
mdefine_line|#define&t;AUDIO_DIAG_LOOPBACK&t;_IOW(&squot;A&squot;, 101, int)
macro_line|#endif /* _AUDIOIO_H_ */
eof
