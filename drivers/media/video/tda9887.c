macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/i2c.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/videodev.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;media/audiochip.h&gt;
macro_line|#include &lt;media/id.h&gt;
multiline_comment|/* Chips:&n;   TDA9885 (PAL, NTSC)&n;   TDA9886 (PAL, SECAM, NTSC)&n;   TDA9887 (PAL, SECAM, NTSC, FM Radio)&n;&n;   found on:&n;   - Pinnacle PCTV (Jul.2002 Version with MT2032, bttv)&n;      TDA9887 (world), TDA9885 (USA)&n;      Note: OP2 of tda988x must be set to 1, else MT2032 is disabled!&n;   - KNC One TV-Station RDS (saa7134)&n;*/
multiline_comment|/* Addresses to scan */
DECL|variable|normal_i2c
r_static
r_int
r_int
id|normal_i2c
(braket
)braket
op_assign
(brace
l_int|0x86
op_rshift
l_int|1
comma
l_int|0x96
op_rshift
l_int|1
comma
id|I2C_CLIENT_END
comma
)brace
suffix:semicolon
DECL|variable|normal_i2c_range
r_static
r_int
r_int
id|normal_i2c_range
(braket
)braket
op_assign
(brace
id|I2C_CLIENT_END
comma
id|I2C_CLIENT_END
)brace
suffix:semicolon
id|I2C_CLIENT_INSMOD
suffix:semicolon
multiline_comment|/* insmod options */
DECL|variable|debug
r_static
r_int
r_int
id|debug
op_assign
l_int|0
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|debug
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
multiline_comment|/* ---------------------------------------------------------------------- */
DECL|macro|UNSET
mdefine_line|#define UNSET       (-1U)
DECL|macro|PREFIX
mdefine_line|#define PREFIX      &quot;tda9885/6/7: &quot;
DECL|macro|dprintk
mdefine_line|#define dprintk     if (debug) printk
DECL|struct|tda9887
r_struct
id|tda9887
(brace
DECL|member|client
r_struct
id|i2c_client
id|client
suffix:semicolon
DECL|member|std
id|v4l2_std_id
id|std
suffix:semicolon
DECL|member|radio
r_int
r_int
id|radio
suffix:semicolon
DECL|member|pinnacle_id
r_int
r_int
id|pinnacle_id
suffix:semicolon
DECL|member|using_v4l2
r_int
r_int
id|using_v4l2
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|tvnorm
r_struct
id|tvnorm
(brace
DECL|member|std
id|v4l2_std_id
id|std
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|b
r_int
r_char
id|b
suffix:semicolon
DECL|member|c
r_int
r_char
id|c
suffix:semicolon
DECL|member|e
r_int
r_char
id|e
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|driver
r_static
r_struct
id|i2c_driver
id|driver
suffix:semicolon
DECL|variable|client_template
r_static
r_struct
id|i2c_client
id|client_template
suffix:semicolon
multiline_comment|/* ---------------------------------------------------------------------- */
singleline_comment|//
singleline_comment|// TDA defines
singleline_comment|//
singleline_comment|//// first reg (b)
DECL|macro|cVideoTrapBypassOFF
mdefine_line|#define cVideoTrapBypassOFF     0x00    
singleline_comment|// bit b0
DECL|macro|cVideoTrapBypassON
mdefine_line|#define cVideoTrapBypassON      0x01    
singleline_comment|// bit b0
DECL|macro|cAutoMuteFmInactive
mdefine_line|#define cAutoMuteFmInactive     0x00    
singleline_comment|// bit b1
DECL|macro|cAutoMuteFmActive
mdefine_line|#define cAutoMuteFmActive       0x02    
singleline_comment|// bit b1
DECL|macro|cIntercarrier
mdefine_line|#define cIntercarrier           0x00    
singleline_comment|// bit b2
DECL|macro|cQSS
mdefine_line|#define cQSS                    0x04    
singleline_comment|// bit b2
DECL|macro|cPositiveAmTV
mdefine_line|#define cPositiveAmTV           0x00    
singleline_comment|// bit b3:4
DECL|macro|cFmRadio
mdefine_line|#define cFmRadio                0x08    
singleline_comment|// bit b3:4
DECL|macro|cNegativeFmTV
mdefine_line|#define cNegativeFmTV           0x10    
singleline_comment|// bit b3:4
DECL|macro|cForcedMuteAudioON
mdefine_line|#define cForcedMuteAudioON      0x20    
singleline_comment|// bit b5
DECL|macro|cForcedMuteAudioOFF
mdefine_line|#define cForcedMuteAudioOFF     0x00    
singleline_comment|// bit b5
DECL|macro|cOutputPort1Active
mdefine_line|#define cOutputPort1Active      0x00    
singleline_comment|// bit b6
DECL|macro|cOutputPort1Inactive
mdefine_line|#define cOutputPort1Inactive    0x40    
singleline_comment|// bit b6
DECL|macro|cOutputPort2Active
mdefine_line|#define cOutputPort2Active      0x00    
singleline_comment|// bit b7
DECL|macro|cOutputPort2Inactive
mdefine_line|#define cOutputPort2Inactive    0x80    
singleline_comment|// bit b7
singleline_comment|//// second reg (c)
DECL|macro|cDeemphasisOFF
mdefine_line|#define cDeemphasisOFF          0x00    
singleline_comment|// bit c5
DECL|macro|cDeemphasisON
mdefine_line|#define cDeemphasisON           0x20    
singleline_comment|// bit c5
DECL|macro|cDeemphasis75
mdefine_line|#define cDeemphasis75           0x00    
singleline_comment|// bit c6
DECL|macro|cDeemphasis50
mdefine_line|#define cDeemphasis50           0x40    
singleline_comment|// bit c6
DECL|macro|cAudioGain0
mdefine_line|#define cAudioGain0             0x00    
singleline_comment|// bit c7
DECL|macro|cAudioGain6
mdefine_line|#define cAudioGain6             0x80    
singleline_comment|// bit c7
singleline_comment|//// third reg (e)
DECL|macro|cAudioIF_4_5
mdefine_line|#define cAudioIF_4_5             0x00    
singleline_comment|// bit e0:1
DECL|macro|cAudioIF_5_5
mdefine_line|#define cAudioIF_5_5             0x01    
singleline_comment|// bit e0:1
DECL|macro|cAudioIF_6_0
mdefine_line|#define cAudioIF_6_0             0x02    
singleline_comment|// bit e0:1
DECL|macro|cAudioIF_6_5
mdefine_line|#define cAudioIF_6_5             0x03    
singleline_comment|// bit e0:1
DECL|macro|cVideoIF_58_75
mdefine_line|#define cVideoIF_58_75           0x00    
singleline_comment|// bit e2:4
DECL|macro|cVideoIF_45_75
mdefine_line|#define cVideoIF_45_75           0x04    
singleline_comment|// bit e2:4
DECL|macro|cVideoIF_38_90
mdefine_line|#define cVideoIF_38_90           0x08    
singleline_comment|// bit e2:4
DECL|macro|cVideoIF_38_00
mdefine_line|#define cVideoIF_38_00           0x0C    
singleline_comment|// bit e2:4
DECL|macro|cVideoIF_33_90
mdefine_line|#define cVideoIF_33_90           0x10    
singleline_comment|// bit e2:4
DECL|macro|cVideoIF_33_40
mdefine_line|#define cVideoIF_33_40           0x14    
singleline_comment|// bit e2:4
DECL|macro|cRadioIF_45_75
mdefine_line|#define cRadioIF_45_75           0x18    
singleline_comment|// bit e2:4
DECL|macro|cRadioIF_38_90
mdefine_line|#define cRadioIF_38_90           0x1C    
singleline_comment|// bit e2:4
DECL|macro|cTunerGainNormal
mdefine_line|#define cTunerGainNormal         0x00    
singleline_comment|// bit e5
DECL|macro|cTunerGainLow
mdefine_line|#define cTunerGainLow            0x20    
singleline_comment|// bit e5
DECL|macro|cGating_18
mdefine_line|#define cGating_18               0x00    
singleline_comment|// bit e6
DECL|macro|cGating_36
mdefine_line|#define cGating_36               0x40    
singleline_comment|// bit e6
DECL|macro|cAgcOutON
mdefine_line|#define cAgcOutON                0x80    
singleline_comment|// bit e7
DECL|macro|cAgcOutOFF
mdefine_line|#define cAgcOutOFF               0x00    
singleline_comment|// bit e7
multiline_comment|/* ---------------------------------------------------------------------- */
DECL|variable|tvnorms
r_static
r_struct
id|tvnorm
id|tvnorms
(braket
)braket
op_assign
(brace
(brace
dot
id|std
op_assign
id|V4L2_STD_PAL_BG
comma
dot
id|name
op_assign
l_string|&quot;PAL-BG&quot;
comma
dot
id|b
op_assign
(paren
id|cNegativeFmTV
op_or
id|cQSS
)paren
comma
dot
id|c
op_assign
(paren
id|cDeemphasisON
op_or
id|cDeemphasis50
)paren
comma
dot
id|e
op_assign
(paren
id|cAudioIF_5_5
op_or
id|cVideoIF_38_90
)paren
comma
)brace
comma
(brace
dot
id|std
op_assign
id|V4L2_STD_PAL_I
comma
dot
id|name
op_assign
l_string|&quot;PAL-I&quot;
comma
dot
id|b
op_assign
(paren
id|cNegativeFmTV
op_or
id|cQSS
)paren
comma
dot
id|c
op_assign
(paren
id|cDeemphasisON
op_or
id|cDeemphasis50
)paren
comma
dot
id|e
op_assign
(paren
id|cAudioIF_6_0
op_or
id|cVideoIF_38_90
)paren
comma
)brace
comma
(brace
dot
id|std
op_assign
id|V4L2_STD_PAL_DK
comma
dot
id|name
op_assign
l_string|&quot;PAL-DK&quot;
comma
dot
id|b
op_assign
(paren
id|cNegativeFmTV
op_or
id|cQSS
)paren
comma
dot
id|c
op_assign
(paren
id|cDeemphasisON
op_or
id|cDeemphasis50
)paren
comma
dot
id|e
op_assign
(paren
id|cAudioIF_6_5
op_or
id|cVideoIF_38_00
)paren
comma
)brace
comma
(brace
dot
id|std
op_assign
id|V4L2_STD_PAL_M
op_or
id|V4L2_STD_PAL_N
comma
dot
id|name
op_assign
l_string|&quot;PAL-M/N&quot;
comma
dot
id|b
op_assign
(paren
id|cNegativeFmTV
op_or
id|cQSS
)paren
comma
dot
id|c
op_assign
(paren
id|cDeemphasisON
op_or
id|cDeemphasis75
)paren
comma
dot
id|e
op_assign
(paren
id|cAudioIF_4_5
op_or
id|cVideoIF_45_75
)paren
comma
)brace
comma
(brace
dot
id|std
op_assign
id|V4L2_STD_SECAM_L
comma
dot
id|name
op_assign
l_string|&quot;SECAM-L&quot;
comma
dot
id|b
op_assign
(paren
id|cPositiveAmTV
op_or
id|cQSS
)paren
comma
dot
id|e
op_assign
(paren
id|cAudioIF_6_5
op_or
id|cVideoIF_38_90
)paren
comma
)brace
comma
(brace
dot
id|std
op_assign
id|V4L2_STD_SECAM_DK
comma
dot
id|name
op_assign
l_string|&quot;SECAM-DK&quot;
comma
dot
id|b
op_assign
(paren
id|cNegativeFmTV
op_or
id|cQSS
)paren
comma
dot
id|c
op_assign
(paren
id|cDeemphasisON
op_or
id|cDeemphasis50
)paren
comma
dot
id|e
op_assign
(paren
id|cAudioIF_6_5
op_or
id|cVideoIF_38_00
)paren
comma
)brace
comma
(brace
dot
id|std
op_assign
id|V4L2_STD_NTSC_M
comma
dot
id|name
op_assign
l_string|&quot;NTSC-M&quot;
comma
dot
id|b
op_assign
(paren
id|cNegativeFmTV
op_or
id|cQSS
)paren
comma
dot
id|c
op_assign
(paren
id|cDeemphasisON
op_or
id|cDeemphasis50
)paren
comma
dot
id|e
op_assign
(paren
id|cGating_36
op_or
id|cAudioIF_4_5
op_or
id|cVideoIF_45_75
)paren
comma
)brace
comma
(brace
dot
id|std
op_assign
id|V4L2_STD_NTSC_M_JP
comma
dot
id|name
op_assign
l_string|&quot;NTSC-JP&quot;
comma
dot
id|b
op_assign
(paren
id|cNegativeFmTV
op_or
id|cQSS
)paren
comma
dot
id|c
op_assign
(paren
id|cDeemphasisON
op_or
id|cDeemphasis50
)paren
comma
dot
id|e
op_assign
(paren
id|cGating_36
op_or
id|cAudioIF_4_5
op_or
id|cVideoIF_58_75
)paren
comma
)brace
)brace
suffix:semicolon
DECL|variable|radio
r_static
r_struct
id|tvnorm
id|radio
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;radio&quot;
comma
dot
id|b
op_assign
(paren
id|cFmRadio
op_or
id|cQSS
)paren
comma
dot
id|c
op_assign
(paren
id|cDeemphasisON
op_or
id|cDeemphasis50
)paren
comma
dot
id|e
op_assign
(paren
id|cAudioIF_5_5
op_or
id|cRadioIF_38_90
)paren
comma
)brace
suffix:semicolon
multiline_comment|/* ---------------------------------------------------------------------- */
DECL|function|dump_read_message
r_static
r_void
id|dump_read_message
c_func
(paren
r_int
r_char
op_star
id|buf
)paren
(brace
r_static
r_char
op_star
id|afc
(braket
l_int|16
)braket
op_assign
(brace
l_string|&quot;- 12.5 kHz&quot;
comma
l_string|&quot;- 37.5 kHz&quot;
comma
l_string|&quot;- 62.5 kHz&quot;
comma
l_string|&quot;- 87.5 kHz&quot;
comma
l_string|&quot;-112.5 kHz&quot;
comma
l_string|&quot;-137.5 kHz&quot;
comma
l_string|&quot;-162.5 kHz&quot;
comma
l_string|&quot;-187.5 kHz [min]&quot;
comma
l_string|&quot;+187.5 kHz [max]&quot;
comma
l_string|&quot;+162.5 kHz&quot;
comma
l_string|&quot;+137.5 kHz&quot;
comma
l_string|&quot;+112.5 kHz&quot;
comma
l_string|&quot;+ 87.5 kHz&quot;
comma
l_string|&quot;+ 62.5 kHz&quot;
comma
l_string|&quot;+ 37.5 kHz&quot;
comma
l_string|&quot;+ 12.5 kHz&quot;
comma
)brace
suffix:semicolon
id|printk
c_func
(paren
id|PREFIX
l_string|&quot;read: 0x%2x&bslash;n&quot;
comma
id|buf
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;  after power on : %s&bslash;n&quot;
comma
(paren
id|buf
(braket
l_int|0
)braket
op_amp
l_int|0x01
)paren
ques
c_cond
l_string|&quot;yes&quot;
suffix:colon
l_string|&quot;no&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;  afc            : %s&bslash;n&quot;
comma
id|afc
(braket
(paren
id|buf
(braket
l_int|0
)braket
op_rshift
l_int|1
)paren
op_amp
l_int|0x0f
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;  afc window     : %s&bslash;n&quot;
comma
(paren
id|buf
(braket
l_int|0
)braket
op_amp
l_int|0x40
)paren
ques
c_cond
l_string|&quot;in&quot;
suffix:colon
l_string|&quot;out&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;  vfi level      : %s&bslash;n&quot;
comma
(paren
id|buf
(braket
l_int|0
)braket
op_amp
l_int|0x80
)paren
ques
c_cond
l_string|&quot;high&quot;
suffix:colon
l_string|&quot;low&quot;
)paren
suffix:semicolon
)brace
DECL|function|dump_write_message
r_static
r_void
id|dump_write_message
c_func
(paren
r_int
r_char
op_star
id|buf
)paren
(brace
r_static
r_char
op_star
id|sound
(braket
l_int|4
)braket
op_assign
(brace
l_string|&quot;AM/TV&quot;
comma
l_string|&quot;FM/radio&quot;
comma
l_string|&quot;FM/TV&quot;
comma
l_string|&quot;FM/radio&quot;
)brace
suffix:semicolon
r_static
r_char
op_star
id|adjust
(braket
l_int|32
)braket
op_assign
(brace
l_string|&quot;-16&quot;
comma
l_string|&quot;-15&quot;
comma
l_string|&quot;-14&quot;
comma
l_string|&quot;-13&quot;
comma
l_string|&quot;-12&quot;
comma
l_string|&quot;-11&quot;
comma
l_string|&quot;-10&quot;
comma
l_string|&quot;-9&quot;
comma
l_string|&quot;-8&quot;
comma
l_string|&quot;-7&quot;
comma
l_string|&quot;-6&quot;
comma
l_string|&quot;-5&quot;
comma
l_string|&quot;-4&quot;
comma
l_string|&quot;-3&quot;
comma
l_string|&quot;-2&quot;
comma
l_string|&quot;-1&quot;
comma
l_string|&quot;0&quot;
comma
l_string|&quot;+1&quot;
comma
l_string|&quot;+2&quot;
comma
l_string|&quot;+3&quot;
comma
l_string|&quot;+4&quot;
comma
l_string|&quot;+5&quot;
comma
l_string|&quot;+6&quot;
comma
l_string|&quot;+7&quot;
comma
l_string|&quot;+8&quot;
comma
l_string|&quot;+9&quot;
comma
l_string|&quot;+10&quot;
comma
l_string|&quot;+11&quot;
comma
l_string|&quot;+12&quot;
comma
l_string|&quot;+13&quot;
comma
l_string|&quot;+14&quot;
comma
l_string|&quot;+15&quot;
)brace
suffix:semicolon
r_static
r_char
op_star
id|deemph
(braket
l_int|4
)braket
op_assign
(brace
l_string|&quot;no&quot;
comma
l_string|&quot;no&quot;
comma
l_string|&quot;75&quot;
comma
l_string|&quot;50&quot;
)brace
suffix:semicolon
r_static
r_char
op_star
id|carrier
(braket
l_int|4
)braket
op_assign
(brace
l_string|&quot;4.5 MHz&quot;
comma
l_string|&quot;5.5 MHz&quot;
comma
l_string|&quot;6.0 MHz&quot;
comma
l_string|&quot;6.5 MHz / AM&quot;
)brace
suffix:semicolon
r_static
r_char
op_star
id|vif
(braket
l_int|8
)braket
op_assign
(brace
l_string|&quot;58.75 MHz&quot;
comma
l_string|&quot;45.75 MHz&quot;
comma
l_string|&quot;38.9 MHz&quot;
comma
l_string|&quot;38.0 MHz&quot;
comma
l_string|&quot;33.9 MHz&quot;
comma
l_string|&quot;33.4 MHz&quot;
comma
l_string|&quot;45.75 MHz + pin13&quot;
comma
l_string|&quot;38.9 MHz + pin13&quot;
comma
)brace
suffix:semicolon
r_static
r_char
op_star
id|rif
(braket
l_int|4
)braket
op_assign
(brace
l_string|&quot;44 MHz&quot;
comma
l_string|&quot;52 MHz&quot;
comma
l_string|&quot;52 MHz&quot;
comma
l_string|&quot;44 MHz&quot;
comma
)brace
suffix:semicolon
id|printk
c_func
(paren
id|PREFIX
l_string|&quot;write: byte B 0x%02x&bslash;n&quot;
comma
id|buf
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;  B0   video mode      : %s&bslash;n&quot;
comma
(paren
id|buf
(braket
l_int|1
)braket
op_amp
l_int|0x01
)paren
ques
c_cond
l_string|&quot;video trap&quot;
suffix:colon
l_string|&quot;sound trap&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;  B1   auto mute fm    : %s&bslash;n&quot;
comma
(paren
id|buf
(braket
l_int|1
)braket
op_amp
l_int|0x02
)paren
ques
c_cond
l_string|&quot;yes&quot;
suffix:colon
l_string|&quot;no&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;  B2   carrier mode    : %s&bslash;n&quot;
comma
(paren
id|buf
(braket
l_int|1
)braket
op_amp
l_int|0x04
)paren
ques
c_cond
l_string|&quot;QSS&quot;
suffix:colon
l_string|&quot;Intercarrier&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;  B3-4 tv sound/radio  : %s&bslash;n&quot;
comma
id|sound
(braket
(paren
id|buf
(braket
l_int|1
)braket
op_amp
l_int|0x18
)paren
op_rshift
l_int|3
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;  B5   force mute audio: %s&bslash;n&quot;
comma
(paren
id|buf
(braket
l_int|1
)braket
op_amp
l_int|0x20
)paren
ques
c_cond
l_string|&quot;yes&quot;
suffix:colon
l_string|&quot;no&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;  B6   output port 1   : %s&bslash;n&quot;
comma
(paren
id|buf
(braket
l_int|1
)braket
op_amp
l_int|0x40
)paren
ques
c_cond
l_string|&quot;high&quot;
suffix:colon
l_string|&quot;low&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;  B7   output port 2   : %s&bslash;n&quot;
comma
(paren
id|buf
(braket
l_int|1
)braket
op_amp
l_int|0x80
)paren
ques
c_cond
l_string|&quot;high&quot;
suffix:colon
l_string|&quot;low&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|PREFIX
l_string|&quot;write: byte C 0x%02x&bslash;n&quot;
comma
id|buf
(braket
l_int|2
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;  C0-4 top adjustment  : %s dB&bslash;n&quot;
comma
id|adjust
(braket
id|buf
(braket
l_int|2
)braket
op_amp
l_int|0x1f
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;  C5-6 de-emphasis     : %s&bslash;n&quot;
comma
id|deemph
(braket
(paren
id|buf
(braket
l_int|2
)braket
op_amp
l_int|0x60
)paren
op_rshift
l_int|5
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;  C7   audio gain      : %s&bslash;n&quot;
comma
(paren
id|buf
(braket
l_int|2
)braket
op_amp
l_int|0x80
)paren
ques
c_cond
l_string|&quot;-6&quot;
suffix:colon
l_string|&quot;0&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|PREFIX
l_string|&quot;write: byte E 0x%02x&bslash;n&quot;
comma
id|buf
(braket
l_int|3
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;  E0-1 sound carrier   : %s&bslash;n&quot;
comma
id|carrier
(braket
(paren
id|buf
(braket
l_int|3
)braket
op_amp
l_int|0x03
)paren
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;  E6   l pll ganting   : %s&bslash;n&quot;
comma
(paren
id|buf
(braket
l_int|3
)braket
op_amp
l_int|0x40
)paren
ques
c_cond
l_string|&quot;36&quot;
suffix:colon
l_string|&quot;13&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buf
(braket
l_int|1
)braket
op_amp
l_int|0x08
)paren
(brace
multiline_comment|/* radio */
id|printk
c_func
(paren
l_string|&quot;  E2-4 video if        : %s&bslash;n&quot;
comma
id|rif
(braket
(paren
id|buf
(braket
l_int|3
)braket
op_amp
l_int|0x0c
)paren
op_rshift
l_int|2
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;  E7   vif agc output  : %s&bslash;n&quot;
comma
(paren
id|buf
(braket
l_int|3
)braket
op_amp
l_int|0x80
)paren
ques
c_cond
(paren
(paren
id|buf
(braket
l_int|3
)braket
op_amp
l_int|0x10
)paren
ques
c_cond
l_string|&quot;fm-agc radio&quot;
suffix:colon
l_string|&quot;sif-agc radio&quot;
)paren
suffix:colon
l_string|&quot;fm radio carrier afc&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* video */
id|printk
c_func
(paren
l_string|&quot;  E2-4 video if        : %s&bslash;n&quot;
comma
id|vif
(braket
(paren
id|buf
(braket
l_int|3
)braket
op_amp
l_int|0x1c
)paren
op_rshift
l_int|2
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;  E5   tuner gain      : %s&bslash;n&quot;
comma
(paren
id|buf
(braket
l_int|3
)braket
op_amp
l_int|0x80
)paren
ques
c_cond
(paren
(paren
id|buf
(braket
l_int|3
)braket
op_amp
l_int|0x20
)paren
ques
c_cond
l_string|&quot;external&quot;
suffix:colon
l_string|&quot;normal&quot;
)paren
suffix:colon
(paren
(paren
id|buf
(braket
l_int|3
)braket
op_amp
l_int|0x20
)paren
ques
c_cond
l_string|&quot;minimum&quot;
suffix:colon
l_string|&quot;normal&quot;
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;  E7   vif agc output  : %s&bslash;n&quot;
comma
(paren
id|buf
(braket
l_int|3
)braket
op_amp
l_int|0x80
)paren
ques
c_cond
(paren
(paren
id|buf
(braket
l_int|3
)braket
op_amp
l_int|0x20
)paren
ques
c_cond
l_string|&quot;pin3 port, pin22 vif agc out&quot;
suffix:colon
l_string|&quot;pin22 port, pin3 vif acg ext in&quot;
)paren
suffix:colon
l_string|&quot;pin3+pin22 port&quot;
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;--&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* ---------------------------------------------------------------------- */
DECL|function|tda9887_set_tvnorm
r_static
r_int
id|tda9887_set_tvnorm
c_func
(paren
r_struct
id|tda9887
op_star
id|t
comma
r_char
op_star
id|buf
)paren
(brace
r_struct
id|tvnorm
op_star
id|norm
op_assign
l_int|NULL
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|t-&gt;radio
)paren
(brace
id|norm
op_assign
op_amp
id|radio
suffix:semicolon
)brace
r_else
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|ARRAY_SIZE
c_func
(paren
id|tvnorms
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|tvnorms
(braket
id|i
)braket
dot
id|std
op_amp
id|t-&gt;std
)paren
(brace
id|norm
op_assign
id|tvnorms
op_plus
id|i
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
r_if
c_cond
(paren
l_int|NULL
op_eq
id|norm
)paren
(brace
id|dprintk
c_func
(paren
id|PREFIX
l_string|&quot;Oops: no tvnorm entry found&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|dprintk
c_func
(paren
id|PREFIX
l_string|&quot;configure for: %s&bslash;n&quot;
comma
id|norm-&gt;name
)paren
suffix:semicolon
id|buf
(braket
l_int|1
)braket
op_assign
id|norm-&gt;b
suffix:semicolon
id|buf
(braket
l_int|2
)braket
op_assign
id|norm-&gt;c
suffix:semicolon
id|buf
(braket
l_int|3
)braket
op_assign
id|norm-&gt;e
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|port1
r_static
r_int
r_int
id|port1
op_assign
l_int|1
suffix:semicolon
DECL|variable|port2
r_static
r_int
r_int
id|port2
op_assign
l_int|1
suffix:semicolon
DECL|variable|qss
r_static
r_int
r_int
id|qss
op_assign
id|UNSET
suffix:semicolon
DECL|variable|adjust
r_static
r_int
r_int
id|adjust
op_assign
l_int|0x10
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|port1
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|port2
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|qss
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|adjust
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
DECL|function|tda9887_set_insmod
r_static
r_int
id|tda9887_set_insmod
c_func
(paren
r_struct
id|tda9887
op_star
id|t
comma
r_char
op_star
id|buf
)paren
(brace
r_if
c_cond
(paren
id|port1
)paren
id|buf
(braket
l_int|1
)braket
op_or_assign
id|cOutputPort1Inactive
suffix:semicolon
r_if
c_cond
(paren
id|port2
)paren
id|buf
(braket
l_int|1
)braket
op_or_assign
id|cOutputPort2Inactive
suffix:semicolon
r_if
c_cond
(paren
id|UNSET
op_ne
id|qss
)paren
(brace
r_if
c_cond
(paren
id|qss
)paren
id|buf
(braket
l_int|1
)braket
op_or_assign
id|cQSS
suffix:semicolon
r_else
id|buf
(braket
l_int|1
)braket
op_and_assign
op_complement
id|cQSS
suffix:semicolon
)brace
r_if
c_cond
(paren
id|adjust
op_ge
l_int|0x00
op_logical_and
id|adjust
OL
l_int|0x20
)paren
id|buf
(braket
l_int|2
)braket
op_or_assign
id|adjust
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* ---------------------------------------------------------------------- */
DECL|function|tda9887_set_pinnacle
r_static
r_int
id|tda9887_set_pinnacle
c_func
(paren
r_struct
id|tda9887
op_star
id|t
comma
r_char
op_star
id|buf
)paren
(brace
r_int
r_int
id|bCarrierMode
op_assign
id|UNSET
suffix:semicolon
r_if
c_cond
(paren
id|t-&gt;std
op_amp
id|V4L2_STD_PAL
)paren
(brace
r_if
c_cond
(paren
(paren
l_int|1
op_eq
id|t-&gt;pinnacle_id
)paren
op_logical_or
(paren
l_int|7
op_eq
id|t-&gt;pinnacle_id
)paren
)paren
(brace
id|bCarrierMode
op_assign
id|cIntercarrier
suffix:semicolon
)brace
r_else
(brace
id|bCarrierMode
op_assign
id|cQSS
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|t-&gt;std
op_amp
id|V4L2_STD_NTSC
)paren
(brace
r_if
c_cond
(paren
(paren
l_int|5
op_eq
id|t-&gt;pinnacle_id
)paren
op_logical_or
(paren
l_int|6
op_eq
id|t-&gt;pinnacle_id
)paren
)paren
(brace
id|bCarrierMode
op_assign
id|cIntercarrier
suffix:semicolon
)brace
r_else
(brace
id|bCarrierMode
op_assign
id|cQSS
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|bCarrierMode
op_ne
id|UNSET
)paren
(brace
id|buf
(braket
l_int|1
)braket
op_and_assign
op_complement
l_int|0x04
suffix:semicolon
id|buf
(braket
l_int|1
)braket
op_or_assign
id|bCarrierMode
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* ---------------------------------------------------------------------- */
DECL|variable|pal
r_static
r_char
op_star
id|pal
op_assign
l_string|&quot;-&quot;
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|pal
comma
l_string|&quot;s&quot;
)paren
suffix:semicolon
DECL|variable|secam
r_static
r_char
op_star
id|secam
op_assign
l_string|&quot;-&quot;
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|secam
comma
l_string|&quot;s&quot;
)paren
suffix:semicolon
DECL|function|tda9887_fixup_std
r_static
r_int
id|tda9887_fixup_std
c_func
(paren
r_struct
id|tda9887
op_star
id|t
)paren
(brace
multiline_comment|/* get more precise norm info from insmod option */
r_if
c_cond
(paren
(paren
id|t-&gt;std
op_amp
id|V4L2_STD_PAL
)paren
op_eq
id|V4L2_STD_PAL
)paren
(brace
r_switch
c_cond
(paren
id|pal
(braket
l_int|0
)braket
)paren
(brace
r_case
l_char|&squot;b&squot;
suffix:colon
r_case
l_char|&squot;B&squot;
suffix:colon
r_case
l_char|&squot;g&squot;
suffix:colon
r_case
l_char|&squot;G&squot;
suffix:colon
id|dprintk
c_func
(paren
id|PREFIX
l_string|&quot;insmod fixup: PAL =&gt; PAL-BG&bslash;n&quot;
)paren
suffix:semicolon
id|t-&gt;std
op_assign
id|V4L2_STD_PAL_BG
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;i&squot;
suffix:colon
r_case
l_char|&squot;I&squot;
suffix:colon
id|dprintk
c_func
(paren
id|PREFIX
l_string|&quot;insmod fixup: PAL =&gt; PAL-I&bslash;n&quot;
)paren
suffix:semicolon
id|t-&gt;std
op_assign
id|V4L2_STD_PAL_I
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;d&squot;
suffix:colon
r_case
l_char|&squot;D&squot;
suffix:colon
r_case
l_char|&squot;k&squot;
suffix:colon
r_case
l_char|&squot;K&squot;
suffix:colon
id|dprintk
c_func
(paren
id|PREFIX
l_string|&quot;insmod fixup: PAL =&gt; PAL-DK&bslash;n&quot;
)paren
suffix:semicolon
id|t-&gt;std
op_assign
id|V4L2_STD_PAL_DK
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
(paren
id|t-&gt;std
op_amp
id|V4L2_STD_SECAM
)paren
op_eq
id|V4L2_STD_SECAM
)paren
(brace
r_switch
c_cond
(paren
id|secam
(braket
l_int|0
)braket
)paren
(brace
r_case
l_char|&squot;d&squot;
suffix:colon
r_case
l_char|&squot;D&squot;
suffix:colon
r_case
l_char|&squot;k&squot;
suffix:colon
r_case
l_char|&squot;K&squot;
suffix:colon
id|dprintk
c_func
(paren
id|PREFIX
l_string|&quot;insmod fixup: SECAM =&gt; SECAM-DK&bslash;n&quot;
)paren
suffix:semicolon
id|t-&gt;std
op_assign
id|V4L2_STD_SECAM_DK
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;l&squot;
suffix:colon
r_case
l_char|&squot;L&squot;
suffix:colon
id|dprintk
c_func
(paren
id|PREFIX
l_string|&quot;insmod fixup: SECAM =&gt; SECAM-L&bslash;n&quot;
)paren
suffix:semicolon
id|t-&gt;std
op_assign
id|V4L2_STD_SECAM_L
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|tda9887_status
r_static
r_int
id|tda9887_status
c_func
(paren
r_struct
id|tda9887
op_star
id|t
)paren
(brace
r_int
r_char
id|buf
(braket
l_int|1
)braket
suffix:semicolon
r_int
id|rc
suffix:semicolon
id|memset
c_func
(paren
id|buf
comma
l_int|0
comma
r_sizeof
(paren
id|buf
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|1
op_ne
(paren
id|rc
op_assign
id|i2c_master_recv
c_func
(paren
op_amp
id|t-&gt;client
comma
id|buf
comma
l_int|1
)paren
)paren
)paren
id|printk
c_func
(paren
id|PREFIX
l_string|&quot;i2c i/o error: rc == %d (should be 1)&bslash;n&quot;
comma
id|rc
)paren
suffix:semicolon
id|dump_read_message
c_func
(paren
id|buf
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|tda9887_configure
r_static
r_int
id|tda9887_configure
c_func
(paren
r_struct
id|tda9887
op_star
id|t
)paren
(brace
r_int
r_char
id|buf
(braket
l_int|4
)braket
suffix:semicolon
r_int
id|rc
suffix:semicolon
id|memset
c_func
(paren
id|buf
comma
l_int|0
comma
r_sizeof
(paren
id|buf
)paren
)paren
suffix:semicolon
id|tda9887_set_tvnorm
c_func
(paren
id|t
comma
id|buf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|UNSET
op_ne
id|t-&gt;pinnacle_id
)paren
(brace
id|tda9887_set_pinnacle
c_func
(paren
id|t
comma
id|buf
)paren
suffix:semicolon
)brace
id|tda9887_set_insmod
c_func
(paren
id|t
comma
id|buf
)paren
suffix:semicolon
id|dprintk
c_func
(paren
id|PREFIX
l_string|&quot;writing: b=0x%02x c=0x%02x e=0x%02x&bslash;n&quot;
comma
id|buf
(braket
l_int|1
)braket
comma
id|buf
(braket
l_int|2
)braket
comma
id|buf
(braket
l_int|3
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|debug
OG
l_int|1
)paren
id|dump_write_message
c_func
(paren
id|buf
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|4
op_ne
(paren
id|rc
op_assign
id|i2c_master_send
c_func
(paren
op_amp
id|t-&gt;client
comma
id|buf
comma
l_int|4
)paren
)paren
)paren
id|printk
c_func
(paren
id|PREFIX
l_string|&quot;i2c i/o error: rc == %d (should be 4)&bslash;n&quot;
comma
id|rc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|debug
OG
l_int|2
)paren
(brace
id|set_current_state
c_func
(paren
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
id|schedule_timeout
c_func
(paren
id|HZ
)paren
suffix:semicolon
id|tda9887_status
c_func
(paren
id|t
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* ---------------------------------------------------------------------- */
DECL|function|tda9887_attach
r_static
r_int
id|tda9887_attach
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|adap
comma
r_int
id|addr
comma
r_int
id|kind
)paren
(brace
r_struct
id|tda9887
op_star
id|t
suffix:semicolon
id|client_template.adapter
op_assign
id|adap
suffix:semicolon
id|client_template.addr
op_assign
id|addr
suffix:semicolon
id|printk
c_func
(paren
id|PREFIX
l_string|&quot;chip found @ 0x%x&bslash;n&quot;
comma
id|addr
op_lshift
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|NULL
op_eq
(paren
id|t
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|t
)paren
comma
id|GFP_KERNEL
)paren
)paren
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
c_func
(paren
id|t
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|t
)paren
)paren
suffix:semicolon
id|t-&gt;client
op_assign
id|client_template
suffix:semicolon
id|t-&gt;std
op_assign
l_int|0
suffix:semicolon
suffix:semicolon
id|t-&gt;pinnacle_id
op_assign
id|UNSET
suffix:semicolon
id|i2c_set_clientdata
c_func
(paren
op_amp
id|t-&gt;client
comma
id|t
)paren
suffix:semicolon
id|i2c_attach_client
c_func
(paren
op_amp
id|t-&gt;client
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|tda9887_probe
r_static
r_int
id|tda9887_probe
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|adap
)paren
(brace
macro_line|#ifdef I2C_CLASS_TV_ANALOG
r_if
c_cond
(paren
id|adap
op_member_access_from_pointer
r_class
op_amp
id|I2C_CLASS_TV_ANALOG
)paren
r_return
id|i2c_probe
c_func
(paren
id|adap
comma
op_amp
id|addr_data
comma
id|tda9887_attach
)paren
suffix:semicolon
macro_line|#else
r_switch
c_cond
(paren
id|adap-&gt;id
)paren
(brace
r_case
id|I2C_ALGO_BIT
op_or
id|I2C_HW_B_BT848
suffix:colon
r_case
id|I2C_ALGO_BIT
op_or
id|I2C_HW_B_RIVA
suffix:colon
r_case
id|I2C_ALGO_SAA7134
suffix:colon
r_return
id|i2c_probe
c_func
(paren
id|adap
comma
op_amp
id|addr_data
comma
id|tda9887_attach
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|tda9887_detach
r_static
r_int
id|tda9887_detach
c_func
(paren
r_struct
id|i2c_client
op_star
id|client
)paren
(brace
r_struct
id|tda9887
op_star
id|t
op_assign
id|i2c_get_clientdata
c_func
(paren
id|client
)paren
suffix:semicolon
id|i2c_detach_client
c_func
(paren
id|client
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|t
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|macro|SWITCH_V4L2
mdefine_line|#define SWITCH_V4L2&t;if (!t-&gt;using_v4l2 &amp;&amp; debug) &bslash;&n;&t;&t;          printk(PREFIX &quot;switching to v4l2&bslash;n&quot;); &bslash;&n;&t;                  t-&gt;using_v4l2 = 1;
DECL|macro|CHECK_V4L2
mdefine_line|#define CHECK_V4L2&t;if (t-&gt;using_v4l2) { if (debug) &bslash;&n;&t;&t;&t;  printk(PREFIX &quot;ignore v4l1 call&bslash;n&quot;); &bslash;&n;&t;&t;          return 0; }
r_static
r_int
DECL|function|tda9887_command
id|tda9887_command
c_func
(paren
r_struct
id|i2c_client
op_star
id|client
comma
r_int
r_int
id|cmd
comma
r_void
op_star
id|arg
)paren
(brace
r_struct
id|tda9887
op_star
id|t
op_assign
id|i2c_get_clientdata
c_func
(paren
id|client
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
multiline_comment|/* --- configuration --- */
r_case
id|AUDC_SET_RADIO
suffix:colon
id|t-&gt;radio
op_assign
l_int|1
suffix:semicolon
id|tda9887_configure
c_func
(paren
id|t
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AUDC_CONFIG_PINNACLE
suffix:colon
(brace
r_int
op_star
id|i
op_assign
id|arg
suffix:semicolon
id|t-&gt;pinnacle_id
op_assign
op_star
id|i
suffix:semicolon
id|tda9887_configure
c_func
(paren
id|t
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* --- v4l ioctls --- */
multiline_comment|/* take care: bttv does userspace copying, we&squot;ll get a&n;&t;   kernel pointer here... */
r_case
id|VIDIOCSCHAN
suffix:colon
(brace
r_static
r_const
id|v4l2_std_id
id|map
(braket
)braket
op_assign
(brace
(braket
id|VIDEO_MODE_PAL
)braket
op_assign
id|V4L2_STD_PAL
comma
(braket
id|VIDEO_MODE_NTSC
)braket
op_assign
id|V4L2_STD_NTSC_M
comma
(braket
id|VIDEO_MODE_SECAM
)braket
op_assign
id|V4L2_STD_SECAM
comma
(braket
l_int|4
multiline_comment|/* bttv */
)braket
op_assign
id|V4L2_STD_PAL_M
comma
(braket
l_int|5
multiline_comment|/* bttv */
)braket
op_assign
id|V4L2_STD_PAL_N
comma
(braket
l_int|6
multiline_comment|/* bttv */
)braket
op_assign
id|V4L2_STD_NTSC_M_JP
comma
)brace
suffix:semicolon
r_struct
id|video_channel
op_star
id|vc
op_assign
id|arg
suffix:semicolon
id|CHECK_V4L2
suffix:semicolon
id|t-&gt;radio
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|vc-&gt;norm
OL
id|ARRAY_SIZE
c_func
(paren
id|map
)paren
)paren
id|t-&gt;std
op_assign
id|map
(braket
id|vc-&gt;norm
)braket
suffix:semicolon
id|tda9887_fixup_std
c_func
(paren
id|t
)paren
suffix:semicolon
id|tda9887_configure
c_func
(paren
id|t
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|VIDIOC_S_STD
suffix:colon
(brace
id|v4l2_std_id
op_star
id|id
op_assign
id|arg
suffix:semicolon
id|SWITCH_V4L2
suffix:semicolon
id|t-&gt;radio
op_assign
l_int|0
suffix:semicolon
id|t-&gt;std
op_assign
op_star
id|id
suffix:semicolon
id|tda9887_fixup_std
c_func
(paren
id|t
)paren
suffix:semicolon
id|tda9887_configure
c_func
(paren
id|t
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|VIDIOC_S_FREQUENCY
suffix:colon
(brace
r_struct
id|v4l2_frequency
op_star
id|f
op_assign
id|arg
suffix:semicolon
id|SWITCH_V4L2
suffix:semicolon
r_if
c_cond
(paren
id|V4L2_TUNER_ANALOG_TV
op_eq
id|f-&gt;type
)paren
(brace
r_if
c_cond
(paren
id|t-&gt;radio
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|t-&gt;radio
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|V4L2_TUNER_RADIO
op_eq
id|f-&gt;type
)paren
(brace
r_if
c_cond
(paren
id|t-&gt;radio
op_eq
l_int|1
)paren
r_return
l_int|0
suffix:semicolon
id|t-&gt;radio
op_assign
l_int|1
suffix:semicolon
)brace
id|tda9887_configure
c_func
(paren
id|t
)paren
suffix:semicolon
)brace
r_default
suffix:colon
multiline_comment|/* nothing */
r_break
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* ----------------------------------------------------------------------- */
DECL|variable|driver
r_static
r_struct
id|i2c_driver
id|driver
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|name
op_assign
l_string|&quot;i2c tda9887 driver&quot;
comma
dot
id|id
op_assign
op_minus
l_int|1
comma
multiline_comment|/* FIXME */
dot
id|flags
op_assign
id|I2C_DF_NOTIFY
comma
dot
id|attach_adapter
op_assign
id|tda9887_probe
comma
dot
id|detach_client
op_assign
id|tda9887_detach
comma
dot
id|command
op_assign
id|tda9887_command
comma
)brace
suffix:semicolon
DECL|variable|client_template
r_static
r_struct
id|i2c_client
id|client_template
op_assign
(brace
id|I2C_DEVNAME
c_func
(paren
l_string|&quot;tda9887&quot;
)paren
comma
dot
id|flags
op_assign
id|I2C_CLIENT_ALLOW_USE
comma
dot
id|driver
op_assign
op_amp
id|driver
comma
)brace
suffix:semicolon
DECL|function|tda9887_init_module
r_static
r_int
id|tda9887_init_module
c_func
(paren
r_void
)paren
(brace
id|i2c_add_driver
c_func
(paren
op_amp
id|driver
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|tda9887_cleanup_module
r_static
r_void
id|tda9887_cleanup_module
c_func
(paren
r_void
)paren
(brace
id|i2c_del_driver
c_func
(paren
op_amp
id|driver
)paren
suffix:semicolon
)brace
DECL|variable|tda9887_init_module
id|module_init
c_func
(paren
id|tda9887_init_module
)paren
suffix:semicolon
DECL|variable|tda9887_cleanup_module
id|module_exit
c_func
(paren
id|tda9887_cleanup_module
)paren
suffix:semicolon
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-basic-offset: 8&n; * End:&n; */
eof
