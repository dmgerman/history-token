macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/i2c.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/videodev.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &quot;id.h&quot;
macro_line|#include &quot;audiochip.h&quot;
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
id|I2C_CLIENT_END
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
l_int|0x86
op_rshift
l_int|1
comma
l_int|0x86
op_rshift
l_int|1
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
id|debug
op_assign
l_int|0
suffix:semicolon
DECL|variable|pal
r_static
r_char
op_star
id|pal
op_assign
l_string|&quot;b&quot;
suffix:semicolon
DECL|variable|secam
r_static
r_char
op_star
id|secam
op_assign
l_string|&quot;l&quot;
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|debug
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|pal
comma
l_string|&quot;s&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|secam
comma
l_string|&quot;s&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
multiline_comment|/* ---------------------------------------------------------------------- */
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
DECL|member|radio
DECL|member|tvnorm
r_int
id|radio
comma
id|tvnorm
suffix:semicolon
DECL|member|pinnacle_id
r_int
id|pinnacle_id
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
singleline_comment|//// first reg
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
singleline_comment|//// second reg
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
singleline_comment|//// third reg
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
DECL|function|tda9887_miro
r_static
r_int
id|tda9887_miro
c_func
(paren
r_struct
id|tda9887
op_star
id|t
)paren
(brace
r_int
id|rc
suffix:semicolon
id|u8
id|bData
(braket
l_int|4
)braket
op_assign
(brace
l_int|0
)brace
suffix:semicolon
id|u8
id|bVideoIF
op_assign
l_int|0
suffix:semicolon
id|u8
id|bAudioIF
op_assign
l_int|0
suffix:semicolon
id|u8
id|bDeEmphasis
op_assign
l_int|0
suffix:semicolon
id|u8
id|bDeEmphVal
op_assign
l_int|0
suffix:semicolon
id|u8
id|bModulation
op_assign
l_int|0
suffix:semicolon
id|u8
id|bCarrierMode
op_assign
l_int|0
suffix:semicolon
id|u8
id|bOutPort1
op_assign
id|cOutputPort1Inactive
suffix:semicolon
macro_line|#if 0
id|u8
id|bOutPort2
op_assign
id|cOutputPort2Inactive
op_amp
id|mbTADState
suffix:semicolon
singleline_comment|// store i2c tuner state
macro_line|#else
id|u8
id|bOutPort2
op_assign
id|cOutputPort2Inactive
suffix:semicolon
macro_line|#endif
id|u8
id|bVideoTrap
op_assign
id|cVideoTrapBypassOFF
suffix:semicolon
macro_line|#if 1
id|u8
id|bTopAdjust
op_assign
l_int|0x0e
multiline_comment|/* -2dB */
suffix:semicolon
macro_line|#else
id|u8
id|bTopAdjust
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
macro_line|#if 0
r_if
c_cond
(paren
id|mParams.fVideoTrap
)paren
id|bVideoTrap
op_assign
id|cVideoTrapBypassON
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|t-&gt;radio
)paren
(brace
id|bVideoTrap
op_assign
id|cVideoTrapBypassOFF
suffix:semicolon
id|bCarrierMode
op_assign
id|cQSS
suffix:semicolon
id|bModulation
op_assign
id|cFmRadio
suffix:semicolon
id|bOutPort1
op_assign
id|cOutputPort1Inactive
suffix:semicolon
id|bDeEmphasis
op_assign
id|cDeemphasisON
suffix:semicolon
r_if
c_cond
(paren
l_int|3
op_eq
id|t-&gt;pinnacle_id
)paren
(brace
multiline_comment|/* ntsc */
id|bDeEmphVal
op_assign
id|cDeemphasis75
suffix:semicolon
id|bAudioIF
op_assign
id|cAudioIF_4_5
suffix:semicolon
id|bVideoIF
op_assign
id|cRadioIF_45_75
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* pal */
id|bAudioIF
op_assign
id|cAudioIF_5_5
suffix:semicolon
id|bVideoIF
op_assign
id|cRadioIF_38_90
suffix:semicolon
id|bDeEmphVal
op_assign
id|cDeemphasis50
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|t-&gt;tvnorm
op_eq
id|VIDEO_MODE_PAL
)paren
(brace
id|bDeEmphasis
op_assign
id|cDeemphasisON
suffix:semicolon
id|bDeEmphVal
op_assign
id|cDeemphasis50
suffix:semicolon
id|bModulation
op_assign
id|cNegativeFmTV
suffix:semicolon
id|bOutPort1
op_assign
id|cOutputPort1Inactive
suffix:semicolon
r_if
c_cond
(paren
l_int|1
op_eq
id|t-&gt;pinnacle_id
)paren
(brace
id|bCarrierMode
op_assign
id|cIntercarrier
suffix:semicolon
)brace
r_else
(brace
singleline_comment|// stereo boards
id|bCarrierMode
op_assign
id|cQSS
suffix:semicolon
)brace
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
l_char|&squot;g&squot;
suffix:colon
r_case
l_char|&squot;h&squot;
suffix:colon
id|bVideoIF
op_assign
id|cVideoIF_38_90
suffix:semicolon
id|bAudioIF
op_assign
id|cAudioIF_5_5
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;d&squot;
suffix:colon
id|bVideoIF
op_assign
id|cVideoIF_38_00
suffix:semicolon
id|bAudioIF
op_assign
id|cAudioIF_6_5
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;i&squot;
suffix:colon
id|bVideoIF
op_assign
id|cVideoIF_38_90
suffix:semicolon
id|bAudioIF
op_assign
id|cAudioIF_6_0
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;m&squot;
suffix:colon
r_case
l_char|&squot;n&squot;
suffix:colon
id|bVideoIF
op_assign
id|cVideoIF_45_75
suffix:semicolon
id|bAudioIF
op_assign
id|cAudioIF_4_5
suffix:semicolon
id|bDeEmphVal
op_assign
id|cDeemphasis75
suffix:semicolon
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
r_break
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|t-&gt;tvnorm
op_eq
id|VIDEO_MODE_SECAM
)paren
(brace
id|bAudioIF
op_assign
id|cAudioIF_6_5
suffix:semicolon
id|bDeEmphasis
op_assign
id|cDeemphasisON
suffix:semicolon
id|bDeEmphVal
op_assign
id|cDeemphasis50
suffix:semicolon
id|bModulation
op_assign
id|cNegativeFmTV
suffix:semicolon
id|bCarrierMode
op_assign
id|cQSS
suffix:semicolon
id|bOutPort1
op_assign
id|cOutputPort1Inactive
suffix:semicolon
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
id|bVideoIF
op_assign
id|cVideoIF_38_00
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;k&squot;
suffix:colon
id|bVideoIF
op_assign
id|cVideoIF_38_90
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;l&squot;
suffix:colon
id|bVideoIF
op_assign
id|cVideoIF_38_90
suffix:semicolon
id|bDeEmphasis
op_assign
id|cDeemphasisOFF
suffix:semicolon
id|bDeEmphVal
op_assign
id|cDeemphasis75
suffix:semicolon
id|bModulation
op_assign
id|cPositiveAmTV
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;L&squot;
multiline_comment|/* L1 */
suffix:colon
id|bVideoIF
op_assign
id|cVideoIF_33_90
suffix:semicolon
id|bDeEmphasis
op_assign
id|cDeemphasisOFF
suffix:semicolon
id|bDeEmphVal
op_assign
id|cDeemphasis75
suffix:semicolon
id|bModulation
op_assign
id|cPositiveAmTV
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|t-&gt;tvnorm
op_eq
id|VIDEO_MODE_NTSC
)paren
(brace
id|bVideoIF
op_assign
id|cVideoIF_45_75
suffix:semicolon
id|bAudioIF
op_assign
id|cAudioIF_4_5
suffix:semicolon
id|bDeEmphasis
op_assign
id|cDeemphasisON
suffix:semicolon
id|bDeEmphVal
op_assign
id|cDeemphasis75
suffix:semicolon
id|bModulation
op_assign
id|cNegativeFmTV
suffix:semicolon
id|bOutPort1
op_assign
id|cOutputPort1Inactive
suffix:semicolon
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
id|bData
(braket
l_int|1
)braket
op_assign
id|bVideoTrap
op_or
singleline_comment|// B0: video trap bypass
id|cAutoMuteFmInactive
op_or
singleline_comment|// B1: auto mute
id|bCarrierMode
op_or
singleline_comment|// B2: InterCarrier for PAL else QSS 
id|bModulation
op_or
singleline_comment|// B3 - B4: positive AM TV for SECAM only
id|cForcedMuteAudioOFF
op_or
singleline_comment|// B5: forced Audio Mute (off)
id|bOutPort1
op_or
singleline_comment|// B6: Out Port 1 
id|bOutPort2
suffix:semicolon
singleline_comment|// B7: Out Port 2 
id|bData
(braket
l_int|2
)braket
op_assign
id|bTopAdjust
op_or
singleline_comment|// C0 - C4: Top Adjust 0 == -16dB  31 == 15dB
id|bDeEmphasis
op_or
singleline_comment|// C5: De-emphasis on/off
id|bDeEmphVal
op_or
singleline_comment|// C6: De-emphasis 50/75 microsec
id|cAudioGain0
suffix:semicolon
singleline_comment|// C7: normal audio gain
id|bData
(braket
l_int|3
)braket
op_assign
id|bAudioIF
op_or
singleline_comment|// E0 - E1: Sound IF
id|bVideoIF
op_or
singleline_comment|// E2 - E4: Video IF
id|cTunerGainNormal
op_or
singleline_comment|// E5: Tuner gain (normal)
id|cGating_18
op_or
singleline_comment|// E6: Gating (18%)
id|cAgcOutOFF
suffix:semicolon
singleline_comment|// E7: VAGC  (off)
id|dprintk
c_func
(paren
l_string|&quot;tda9885/6/7: 0x%02x 0x%02x 0x%02x [pinnacle_id=%d]&bslash;n&quot;
comma
id|bData
(braket
l_int|1
)braket
comma
id|bData
(braket
l_int|2
)braket
comma
id|bData
(braket
l_int|3
)braket
comma
id|t-&gt;pinnacle_id
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
id|bData
comma
l_int|4
)paren
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;tda9885/6/7: i2c i/o error: rc == %d (should be 4)&bslash;n&quot;
comma
id|rc
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* ---------------------------------------------------------------------- */
macro_line|#if 0
multiline_comment|/* just for reference: old knc-one saa7134 stuff */
r_static
r_int
r_char
id|buf_pal_bg
(braket
)braket
op_assign
(brace
l_int|0x00
comma
l_int|0x16
comma
l_int|0x70
comma
l_int|0x49
)brace
suffix:semicolon
r_static
r_int
r_char
id|buf_pal_i
(braket
)braket
op_assign
(brace
l_int|0x00
comma
l_int|0x16
comma
l_int|0x70
comma
l_int|0x4a
)brace
suffix:semicolon
r_static
r_int
r_char
id|buf_pal_dk
(braket
)braket
op_assign
(brace
l_int|0x00
comma
l_int|0x16
comma
l_int|0x70
comma
l_int|0x4b
)brace
suffix:semicolon
r_static
r_int
r_char
id|buf_pal_l
(braket
)braket
op_assign
(brace
l_int|0x00
comma
l_int|0x06
comma
l_int|0x50
comma
l_int|0x4b
)brace
suffix:semicolon
r_static
r_int
r_char
id|buf_fm_stereo
(braket
)braket
op_assign
(brace
l_int|0x00
comma
l_int|0x0e
comma
l_int|0x0d
comma
l_int|0x77
)brace
suffix:semicolon
macro_line|#endif
DECL|variable|buf_pal_bg
r_static
r_int
r_char
id|buf_pal_bg
(braket
)braket
op_assign
(brace
l_int|0x00
comma
l_int|0x96
comma
l_int|0x70
comma
l_int|0x49
)brace
suffix:semicolon
DECL|variable|buf_pal_i
r_static
r_int
r_char
id|buf_pal_i
(braket
)braket
op_assign
(brace
l_int|0x00
comma
l_int|0x96
comma
l_int|0x70
comma
l_int|0x4a
)brace
suffix:semicolon
DECL|variable|buf_pal_dk
r_static
r_int
r_char
id|buf_pal_dk
(braket
)braket
op_assign
(brace
l_int|0x00
comma
l_int|0x96
comma
l_int|0x70
comma
l_int|0x4b
)brace
suffix:semicolon
DECL|variable|buf_pal_l
r_static
r_int
r_char
id|buf_pal_l
(braket
)braket
op_assign
(brace
l_int|0x00
comma
l_int|0x86
comma
l_int|0x50
comma
l_int|0x4b
)brace
suffix:semicolon
DECL|variable|buf_fm_stereo
r_static
r_int
r_char
id|buf_fm_stereo
(braket
)braket
op_assign
(brace
l_int|0x00
comma
l_int|0x8e
comma
l_int|0x0d
comma
l_int|0x77
)brace
suffix:semicolon
DECL|variable|buf_ntsc
r_static
r_int
r_char
id|buf_ntsc
(braket
)braket
op_assign
(brace
l_int|0x00
comma
l_int|0x96
comma
l_int|0x70
comma
l_int|0x44
)brace
suffix:semicolon
DECL|variable|buf_ntsc_jp
r_static
r_int
r_char
id|buf_ntsc_jp
(braket
)braket
op_assign
(brace
l_int|0x00
comma
l_int|0x96
comma
l_int|0x70
comma
l_int|0x40
)brace
suffix:semicolon
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
op_star
id|buf
op_assign
l_int|NULL
suffix:semicolon
r_int
id|rc
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;tda9887_configure&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|t-&gt;radio
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;tda9885/6/7: FM Radio mode&bslash;n&quot;
)paren
suffix:semicolon
id|buf
op_assign
id|buf_fm_stereo
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|t-&gt;tvnorm
op_eq
id|VIDEO_MODE_PAL
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;tda9885/6/7: PAL-%c mode&bslash;n&quot;
comma
id|pal
(braket
l_int|0
)braket
)paren
suffix:semicolon
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
l_char|&squot;g&squot;
suffix:colon
id|buf
op_assign
id|buf_pal_bg
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;i&squot;
suffix:colon
id|buf
op_assign
id|buf_pal_i
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;d&squot;
suffix:colon
r_case
l_char|&squot;k&squot;
suffix:colon
id|buf
op_assign
id|buf_pal_dk
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;l&squot;
suffix:colon
id|buf
op_assign
id|buf_pal_l
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|t-&gt;tvnorm
op_eq
id|VIDEO_MODE_NTSC
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;tda9885/6/7: NTSC mode&bslash;n&quot;
)paren
suffix:semicolon
id|buf
op_assign
id|buf_ntsc
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|t-&gt;tvnorm
op_eq
id|VIDEO_MODE_SECAM
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;tda9885/6/7: SECAM mode&bslash;n&quot;
)paren
suffix:semicolon
id|buf
op_assign
id|buf_pal_l
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|t-&gt;tvnorm
op_eq
l_int|6
multiline_comment|/* BTTV hack */
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;tda9885/6/7: NTSC-Japan mode&bslash;n&quot;
)paren
suffix:semicolon
id|buf
op_assign
id|buf_ntsc_jp
suffix:semicolon
)brace
r_if
c_cond
(paren
l_int|NULL
op_eq
id|buf
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;tda9885/6/7 unknown norm=%d&bslash;n&quot;
comma
id|t-&gt;tvnorm
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|dprintk
c_func
(paren
l_string|&quot;tda9885/6/7: 0x%02x 0x%02x 0x%02x&bslash;n&quot;
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
l_string|&quot;tda9885/6/7: i2c i/o error: rc == %d (should be 4)&bslash;n&quot;
comma
id|rc
)paren
suffix:semicolon
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
r_int
id|flags
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
l_string|&quot;tda9887: chip found @ 0x%x&bslash;n&quot;
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
id|t-&gt;client.data
op_assign
id|t
suffix:semicolon
id|t-&gt;pinnacle_id
op_assign
op_minus
l_int|1
suffix:semicolon
id|i2c_attach_client
c_func
(paren
op_amp
id|t-&gt;client
)paren
suffix:semicolon
id|MOD_INC_USE_COUNT
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
r_int
id|rc
suffix:semicolon
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
id|printk
c_func
(paren
l_string|&quot;tda9887: probing %s i2c adapter [id=0x%x]&bslash;n&quot;
comma
id|adap-&gt;name
comma
id|adap-&gt;id
)paren
suffix:semicolon
id|rc
op_assign
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
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;tda9887: ignoring %s i2c adapter [id=0x%x]&bslash;n&quot;
comma
id|adap-&gt;name
comma
id|adap-&gt;id
)paren
suffix:semicolon
id|rc
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* nothing */
)brace
r_return
id|rc
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
(paren
r_struct
id|tda9887
op_star
)paren
id|client-&gt;data
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
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
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
(paren
r_struct
id|tda9887
op_star
)paren
id|client-&gt;data
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
r_if
c_cond
(paren
op_minus
l_int|1
op_ne
id|t-&gt;pinnacle_id
)paren
id|tda9887_miro
c_func
(paren
id|t
)paren
suffix:semicolon
r_else
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
r_break
suffix:semicolon
)brace
multiline_comment|/* --- v4l ioctls --- */
multiline_comment|/* take care: bttv does userspace copying, we&squot;ll get a&n;&t;   kernel pointer here... */
r_case
id|VIDIOCSCHAN
suffix:colon
(brace
r_struct
id|video_channel
op_star
id|vc
op_assign
id|arg
suffix:semicolon
id|t-&gt;radio
op_assign
l_int|0
suffix:semicolon
id|t-&gt;tvnorm
op_assign
id|vc-&gt;norm
suffix:semicolon
r_if
c_cond
(paren
op_minus
l_int|1
op_ne
id|t-&gt;pinnacle_id
)paren
id|tda9887_miro
c_func
(paren
id|t
)paren
suffix:semicolon
r_else
id|tda9887_configure
c_func
(paren
id|t
)paren
suffix:semicolon
r_break
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
dot
id|name
op_assign
l_string|&quot;tda9887&quot;
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
