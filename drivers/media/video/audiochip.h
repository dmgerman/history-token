macro_line|#ifndef AUDIOCHIP_H
DECL|macro|AUDIOCHIP_H
mdefine_line|#define AUDIOCHIP_H
multiline_comment|/* ---------------------------------------------------------------------- */
DECL|macro|MIN
mdefine_line|#define MIN(a,b) (((a)&gt;(b))?(b):(a))
DECL|macro|MAX
mdefine_line|#define MAX(a,b) (((a)&gt;(b))?(a):(b))
multiline_comment|/* v4l device was opened in Radio mode */
DECL|macro|AUDC_SET_RADIO
mdefine_line|#define AUDC_SET_RADIO        _IO(&squot;m&squot;,2)
multiline_comment|/* select from TV,radio,extern,MUTE */
DECL|macro|AUDC_SET_INPUT
mdefine_line|#define AUDC_SET_INPUT        _IOW(&squot;m&squot;,17,int)
multiline_comment|/* audio inputs */
DECL|macro|AUDIO_TUNER
mdefine_line|#define AUDIO_TUNER        0x00
DECL|macro|AUDIO_RADIO
mdefine_line|#define AUDIO_RADIO        0x01
DECL|macro|AUDIO_EXTERN
mdefine_line|#define AUDIO_EXTERN       0x02
DECL|macro|AUDIO_INTERN
mdefine_line|#define AUDIO_INTERN       0x03
DECL|macro|AUDIO_OFF
mdefine_line|#define AUDIO_OFF          0x04 
DECL|macro|AUDIO_ON
mdefine_line|#define AUDIO_ON           0x05
DECL|macro|AUDIO_MUTE
mdefine_line|#define AUDIO_MUTE         0x80
DECL|macro|AUDIO_UNMUTE
mdefine_line|#define AUDIO_UNMUTE       0x81
multiline_comment|/* all the stuff below is obsolete and just here for reference.  I&squot;ll&n; * remove it once the driver is tested and works fine.&n; *&n; * Instead creating alot of tiny API&squot;s for all kinds of different&n; * chips, we&squot;ll just pass throuth the v4l ioctl structs (v4l2 not&n; * yet...).  It is a bit less flexible, but most/all used i2c chips&n; * make sense in v4l context only.  So I think that&squot;s acceptable...&n; */
macro_line|#if 0
multiline_comment|/* TODO (if it is ever [to be] accessible in the V4L[2] spec):&n; *   maybe fade? (back/front)&n; * notes:&n; * NEWCHANNEL and SWITCH_MUTE are here because the MSP3400 has a special&n; * routine to go through when it tunes in to a new channel before turning&n; * back on the sound.&n; * Either SET_RADIO, NEWCHANNEL, and SWITCH_MUTE or SET_INPUT need to be&n; * implemented (MSP3400 uses SET_RADIO to select inputs, and SWITCH_MUTE for&n; * channel-change mute -- TEA6300 et al use SET_AUDIO to select input [TV, &n; * radio, external, or MUTE]).  If both methods are implemented, you get a&n; * cookie for doing such a good job! :)&n; */
mdefine_line|#define AUDC_SET_TVNORM       _IOW(&squot;m&squot;,1,int)  /* TV mode + PAL/SECAM/NTSC  */
mdefine_line|#define AUDC_NEWCHANNEL       _IO(&squot;m&squot;,3)       /* indicate new chan - off mute */
mdefine_line|#define AUDC_GET_VOLUME_LEFT  _IOR(&squot;m&squot;,4,__u16)
mdefine_line|#define AUDC_GET_VOLUME_RIGHT _IOR(&squot;m&squot;,5,__u16)
mdefine_line|#define AUDC_SET_VOLUME_LEFT  _IOW(&squot;m&squot;,6,__u16)
mdefine_line|#define AUDC_SET_VOLUME_RIGHT _IOW(&squot;m&squot;,7,__u16)
mdefine_line|#define AUDC_GET_STEREO       _IOR(&squot;m&squot;,8,__u16)
mdefine_line|#define AUDC_SET_STEREO       _IOW(&squot;m&squot;,9,__u16)
mdefine_line|#define AUDC_GET_DC           _IOR(&squot;m&squot;,10,__u16)/* ??? */
mdefine_line|#define AUDC_GET_BASS         _IOR(&squot;m&squot;,11,__u16)
mdefine_line|#define AUDC_SET_BASS         _IOW(&squot;m&squot;,12,__u16)
mdefine_line|#define AUDC_GET_TREBLE       _IOR(&squot;m&squot;,13,__u16)
mdefine_line|#define AUDC_SET_TREBLE       _IOW(&squot;m&squot;,14,__u16)
mdefine_line|#define AUDC_GET_UNIT         _IOR(&squot;m&squot;,15,int) /* ??? - unimplemented in MSP3400 */
mdefine_line|#define AUDC_SWITCH_MUTE      _IO(&squot;m&squot;,16)      /* turn on mute */
macro_line|#endif
macro_line|#endif /* AUDIOCHIP_H */
eof
