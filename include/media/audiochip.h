macro_line|#ifndef AUDIOCHIP_H
DECL|macro|AUDIOCHIP_H
mdefine_line|#define AUDIOCHIP_H
multiline_comment|/* ---------------------------------------------------------------------- */
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
DECL|macro|AUDIO_EXTERN_1
mdefine_line|#define AUDIO_EXTERN_1     AUDIO_EXTERN
DECL|macro|AUDIO_EXTERN_2
mdefine_line|#define AUDIO_EXTERN_2     0x06
DECL|macro|AUDIO_MUTE
mdefine_line|#define AUDIO_MUTE         0x80
DECL|macro|AUDIO_UNMUTE
mdefine_line|#define AUDIO_UNMUTE       0x81
multiline_comment|/* all the stuff below is obsolete and just here for reference.  I&squot;ll&n; * remove it once the driver is tested and works fine.&n; *&n; * Instead creating alot of tiny API&squot;s for all kinds of different&n; * chips, we&squot;ll just pass throuth the v4l ioctl structs (v4l2 not&n; * yet...).  It is a bit less flexible, but most/all used i2c chips&n; * make sense in v4l context only.  So I think that&squot;s acceptable...&n; */
multiline_comment|/* misc stuff to pass around config info to i2c chips */
DECL|macro|AUDC_CONFIG_PINNACLE
mdefine_line|#define AUDC_CONFIG_PINNACLE  _IOW(&squot;m&squot;,32,int)
macro_line|#endif /* AUDIOCHIP_H */
eof
