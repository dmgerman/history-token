multiline_comment|/*&n; * dib3000mc_priv.h&n; *&n; * Copyright (C) 2004 Patrick Boettcher (patrick.boettcher@desy.de)&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License as&n; *&t;published by the Free Software Foundation, version 2.&n; *&n; * for more information see dib3000mc.c .&n; */
macro_line|#ifndef __DIB3000MC_PRIV_H__
DECL|macro|__DIB3000MC_PRIV_H__
mdefine_line|#define __DIB3000MC_PRIV_H__
multiline_comment|/* info and err, taken from usb.h, if there is anything available like by default,&n; * please change !&n; */
DECL|macro|err
mdefine_line|#define err(format, arg...) printk(KERN_ERR &quot;%s: &quot; format &quot;&bslash;n&quot; , __FILE__ , ## arg)
DECL|macro|info
mdefine_line|#define info(format, arg...) printk(KERN_INFO &quot;%s: &quot; format &quot;&bslash;n&quot; , __FILE__ , ## arg)
DECL|macro|warn
mdefine_line|#define warn(format, arg...) printk(KERN_WARNING &quot;%s: &quot; format &quot;&bslash;n&quot; , __FILE__ , ## arg)
singleline_comment|// defines the phase noise algorithm to be used (O:Inhib, 1:CPE on)
DECL|macro|DEF_PHASE_NOISE_MODE
mdefine_line|#define DEF_PHASE_NOISE_MODE                0
singleline_comment|// define Mobille algorithms
DECL|macro|DEF_MOBILE_MODE
mdefine_line|#define DEF_MOBILE_MODE      Auto_Reception
singleline_comment|// defines the tuner type
DECL|macro|DEF_TUNER_TYPE
mdefine_line|#define DEF_TUNER_TYPE   TUNER_PANASONIC_ENV57H13D5
singleline_comment|// defines the impule noise algorithm to be used
DECL|macro|DEF_IMPULSE_NOISE_MODE
mdefine_line|#define DEF_IMPULSE_NOISE_MODE      0
singleline_comment|// defines the MPEG2 data output format
DECL|macro|DEF_MPEG2_OUTPUT_188
mdefine_line|#define DEF_MPEG2_OUTPUT_188       0
singleline_comment|// defines the MPEG2 data output format
DECL|macro|DEF_OUTPUT_MODE
mdefine_line|#define DEF_OUTPUT_MODE       MPEG2_PARALLEL_CONTINUOUS_CLOCK
multiline_comment|/*&n; * Demodulator parameters&n; * reg: 0  1 1  1 11 11 111&n; *         | |  |  |  |  |&n; *         | |  |  |  |  +-- alpha (000=0, 001=1, 010=2, 100=4)&n; *         | |  |  |  +----- constellation (00=QPSK, 01=16QAM, 10=64QAM)&n; *         | |  |  +-------- guard (00=1/32, 01=1/16, 10=1/8, 11=1/4)&n; *         | |  +----------- transmission mode (0=2k, 1=8k)&n; *         | |&n; *         | +-------------- restart autosearch for parameters&n; *         +---------------- restart the demodulator&n; * reg: 181      1 111 1&n; *               |  |  |&n; *               |  |  +- FEC applies for HP or LP (0=LP, 1=HP)&n; *               |  +---- FEC rate (001=1/2, 010=2/3, 011=3/4, 101=5/6, 111=7/8)&n; *               +------- hierarchy on (0=no, 1=yes)&n; */
multiline_comment|/* demodulator tuning parameter and restart options */
DECL|macro|DIB3000MC_REG_DEMOD_PARM
mdefine_line|#define DIB3000MC_REG_DEMOD_PARM&t;&t;(     0)
DECL|macro|DIB3000MC_DEMOD_PARM
mdefine_line|#define DIB3000MC_DEMOD_PARM(a,c,g,t)&t;( &bslash;&n;&t;&t; (0x7 &amp; a) | &bslash;&n;&t;&t;((0x3 &amp; c) &lt;&lt; 3) | &bslash;&n;&t;&t;((0x3 &amp; g) &lt;&lt; 5) | &bslash;&n;&t;&t;((0x1 &amp; t) &lt;&lt; 7) )
DECL|macro|DIB3000MC_DEMOD_RST_AUTO_SRCH_ON
mdefine_line|#define DIB3000MC_DEMOD_RST_AUTO_SRCH_ON&t;(1 &lt;&lt; 8)
DECL|macro|DIB3000MC_DEMOD_RST_AUTO_SRCH_OFF
mdefine_line|#define DIB3000MC_DEMOD_RST_AUTO_SRCH_OFF&t;(0 &lt;&lt; 8)
DECL|macro|DIB3000MC_DEMOD_RST_DEMOD_ON
mdefine_line|#define DIB3000MC_DEMOD_RST_DEMOD_ON&t;&t;(1 &lt;&lt; 9)
DECL|macro|DIB3000MC_DEMOD_RST_DEMOD_OFF
mdefine_line|#define DIB3000MC_DEMOD_RST_DEMOD_OFF&t;&t;(0 &lt;&lt; 9)
multiline_comment|/* register for hierarchy parameters */
DECL|macro|DIB3000MC_REG_HRCH_PARM
mdefine_line|#define DIB3000MC_REG_HRCH_PARM&t;&t;&t;(   181)
DECL|macro|DIB3000MC_HRCH_PARM
mdefine_line|#define DIB3000MC_HRCH_PARM(s,f,h)&t;&t;( &bslash;&n;&t;&t; (0x1 &amp; s) | &bslash;&n;&t;&t;((0x7 &amp; f) &lt;&lt; 1) | &bslash;&n;&t;&t;((0x1 &amp; h) &lt;&lt; 4) )
multiline_comment|/* timeout ??? */
DECL|macro|DIB3000MC_REG_UNK_1
mdefine_line|#define DIB3000MC_REG_UNK_1&t;&t;&t;&t;(     1)
DECL|macro|DIB3000MC_UNK_1
mdefine_line|#define DIB3000MC_UNK_1&t;&t;&t;&t;&t;(  0x04)
multiline_comment|/* timeout ??? */
DECL|macro|DIB3000MC_REG_UNK_2
mdefine_line|#define DIB3000MC_REG_UNK_2&t;&t;&t;&t;(     2)
DECL|macro|DIB3000MC_UNK_2
mdefine_line|#define DIB3000MC_UNK_2&t;&t;&t;&t;&t;(  0x04)
multiline_comment|/* timeout ??? */
DECL|macro|DIB3000MC_REG_UNK_3
mdefine_line|#define DIB3000MC_REG_UNK_3&t;&t;&t;&t;(     3)
DECL|macro|DIB3000MC_UNK_3
mdefine_line|#define DIB3000MC_UNK_3&t;&t;&t;&t;&t;(0x1000)
DECL|macro|DIB3000MC_REG_UNK_4
mdefine_line|#define DIB3000MC_REG_UNK_4&t;&t;&t;&t;(     4)
DECL|macro|DIB3000MC_UNK_4
mdefine_line|#define DIB3000MC_UNK_4&t;&t;&t;&t;&t;(0x0814)
multiline_comment|/* timeout ??? */
DECL|macro|DIB3000MC_REG_SEQ_TPS
mdefine_line|#define DIB3000MC_REG_SEQ_TPS&t;&t;&t;(     5)
DECL|macro|DIB3000MC_SEQ_TPS_DEFAULT
mdefine_line|#define DIB3000MC_SEQ_TPS_DEFAULT&t;&t;(     1)
DECL|macro|DIB3000MC_SEQ_TPS
mdefine_line|#define DIB3000MC_SEQ_TPS(s,t)&t;&t;&t;( &bslash;&n;&t;&t;((s &amp; 0x0f) &lt;&lt; 4) | &bslash;&n;&t;&t;((t &amp; 0x01) &lt;&lt; 8) )
DECL|macro|DIB3000MC_IS_TPS
mdefine_line|#define DIB3000MC_IS_TPS(v)&t;&t;&t;&t;((v &lt;&lt; 8) &amp; 0x1)
DECL|macro|DIB3000MC_IS_AS
mdefine_line|#define DIB3000MC_IS_AS(v)&t;&t;&t;&t;((v &gt;&gt; 4) &amp; 0xf)
multiline_comment|/* parameters for the bandwidth */
DECL|macro|DIB3000MC_REG_BW_TIMOUT_MSB
mdefine_line|#define DIB3000MC_REG_BW_TIMOUT_MSB&t;&t;(     6)
DECL|macro|DIB3000MC_REG_BW_TIMOUT_LSB
mdefine_line|#define DIB3000MC_REG_BW_TIMOUT_LSB&t;&t;(     7)
DECL|variable|dib3000mc_reg_bandwidth
r_static
id|u16
id|dib3000mc_reg_bandwidth
(braket
)braket
op_assign
(brace
l_int|6
comma
l_int|7
comma
l_int|8
comma
l_int|9
comma
l_int|10
comma
l_int|11
comma
l_int|16
comma
l_int|17
)brace
suffix:semicolon
multiline_comment|/*static u16 dib3000mc_bandwidth_5mhz[] =&n;&t;{ 0x28, 0x9380, 0x87, 0x4100, 0x2a4, 0x4500, 0x1, 0xb0d0 };*/
DECL|variable|dib3000mc_bandwidth_6mhz
r_static
id|u16
id|dib3000mc_bandwidth_6mhz
(braket
)braket
op_assign
(brace
l_int|0x21
comma
l_int|0xd040
comma
l_int|0x70
comma
l_int|0xb62b
comma
l_int|0x233
comma
l_int|0x8ed5
comma
l_int|0x1
comma
l_int|0xb0d0
)brace
suffix:semicolon
DECL|variable|dib3000mc_bandwidth_7mhz
r_static
id|u16
id|dib3000mc_bandwidth_7mhz
(braket
)braket
op_assign
(brace
l_int|0x1c
comma
l_int|0xfba5
comma
l_int|0x60
comma
l_int|0x9c25
comma
l_int|0x1e3
comma
l_int|0x0cb7
comma
l_int|0x1
comma
l_int|0xb0d0
)brace
suffix:semicolon
DECL|variable|dib3000mc_bandwidth_8mhz
r_static
id|u16
id|dib3000mc_bandwidth_8mhz
(braket
)braket
op_assign
(brace
l_int|0x19
comma
l_int|0x5c30
comma
l_int|0x54
comma
l_int|0x88a0
comma
l_int|0x1a6
comma
l_int|0xab20
comma
l_int|0x1
comma
l_int|0xb0b0
)brace
suffix:semicolon
DECL|variable|dib3000mc_reg_bandwidth_general
r_static
id|u16
id|dib3000mc_reg_bandwidth_general
(braket
)braket
op_assign
(brace
l_int|12
comma
l_int|13
comma
l_int|14
comma
l_int|15
)brace
suffix:semicolon
DECL|variable|dib3000mc_bandwidth_general
r_static
id|u16
id|dib3000mc_bandwidth_general
(braket
)braket
op_assign
(brace
l_int|0x0000
comma
l_int|0x03e8
comma
l_int|0x0000
comma
l_int|0x03f2
)brace
suffix:semicolon
multiline_comment|/* lock mask */
DECL|macro|DIB3000MC_REG_LOCK_MASK
mdefine_line|#define DIB3000MC_REG_LOCK_MASK&t;&t;&t;(    15)
DECL|macro|DIB3000MC_ACTIVATE_LOCK_MASK
mdefine_line|#define DIB3000MC_ACTIVATE_LOCK_MASK&t;(0x0800)
multiline_comment|/* reset the uncorrected packet count (??? do it 5 times) */
DECL|macro|DIB3000MC_REG_RST_UNC
mdefine_line|#define DIB3000MC_REG_RST_UNC&t;&t;&t;(    18)
DECL|macro|DIB3000MC_RST_UNC_ON
mdefine_line|#define DIB3000MC_RST_UNC_ON&t;&t;&t;(     1)
DECL|macro|DIB3000MC_RST_UNC_OFF
mdefine_line|#define DIB3000MC_RST_UNC_OFF&t;&t;&t;(     0)
DECL|macro|DIB3000MC_REG_UNK_19
mdefine_line|#define DIB3000MC_REG_UNK_19&t;&t;&t;(    19)
DECL|macro|DIB3000MC_UNK_19
mdefine_line|#define DIB3000MC_UNK_19&t;&t;&t;&t;(     0)
multiline_comment|/* DDS frequency value (IF position) and inversion bit */
DECL|macro|DIB3000MC_REG_INVERSION
mdefine_line|#define DIB3000MC_REG_INVERSION&t;&t;&t;(    21)
DECL|macro|DIB3000MC_REG_SET_DDS_FREQ_MSB
mdefine_line|#define DIB3000MC_REG_SET_DDS_FREQ_MSB&t;(    21)
DECL|macro|DIB3000MC_DDS_FREQ_MSB_INV_OFF
mdefine_line|#define DIB3000MC_DDS_FREQ_MSB_INV_OFF&t;(0x0164)
DECL|macro|DIB3000MC_DDS_FREQ_MSB_INV_ON
mdefine_line|#define DIB3000MC_DDS_FREQ_MSB_INV_ON&t;(0x0364)
DECL|macro|DIB3000MC_REG_SET_DDS_FREQ_LSB
mdefine_line|#define DIB3000MC_REG_SET_DDS_FREQ_LSB&t;(    22)
DECL|macro|DIB3000MC_DDS_FREQ_LSB
mdefine_line|#define DIB3000MC_DDS_FREQ_LSB&t;&t;&t;(0x463d)
multiline_comment|/* timing frequencies setting */
DECL|macro|DIB3000MC_REG_TIMING_FREQ_MSB
mdefine_line|#define DIB3000MC_REG_TIMING_FREQ_MSB&t;(    23)
DECL|macro|DIB3000MC_REG_TIMING_FREQ_LSB
mdefine_line|#define DIB3000MC_REG_TIMING_FREQ_LSB&t;(    24)
DECL|macro|DIB3000MC_CLOCK_REF
mdefine_line|#define DIB3000MC_CLOCK_REF&t;&t;&t;&t;(0x151fd1)
singleline_comment|//static u16 dib3000mc_reg_timing_freq[] = { 23,24 };
singleline_comment|//static u16 dib3000mc_timing_freq[][2] = {
singleline_comment|//&t;{ 0x69, 0x9f18 }, /* 5 MHz */
singleline_comment|//&t;{ 0x7e ,0xbee9 }, /* 6 MHz */
singleline_comment|//&t;{ 0x93 ,0xdebb }, /* 7 MHz */
singleline_comment|//&t;{ 0xa8 ,0xfe8c }, /* 8 MHz */
singleline_comment|//};
multiline_comment|/* timeout ??? */
DECL|variable|dib3000mc_reg_offset
r_static
id|u16
id|dib3000mc_reg_offset
(braket
)braket
op_assign
(brace
l_int|26
comma
l_int|33
)brace
suffix:semicolon
DECL|variable|dib3000mc_offset
r_static
id|u16
id|dib3000mc_offset
(braket
)braket
(braket
l_int|2
)braket
op_assign
(brace
(brace
l_int|26240
comma
l_int|5
)brace
comma
multiline_comment|/* default */
(brace
l_int|30336
comma
l_int|6
)brace
comma
multiline_comment|/* 8K */
(brace
l_int|38528
comma
l_int|8
)brace
comma
multiline_comment|/* 2K */
)brace
suffix:semicolon
DECL|macro|DIB3000MC_REG_ISI
mdefine_line|#define DIB3000MC_REG_ISI&t;&t;&t;&t;(    29)
DECL|macro|DIB3000MC_ISI_DEFAULT
mdefine_line|#define DIB3000MC_ISI_DEFAULT&t;&t;&t;(0x1073)
DECL|macro|DIB3000MC_ISI_ACTIVATE
mdefine_line|#define DIB3000MC_ISI_ACTIVATE&t;&t;&t;(0x0000)
DECL|macro|DIB3000MC_ISI_INHIBIT
mdefine_line|#define DIB3000MC_ISI_INHIBIT&t;&t;&t;(0x0200)
multiline_comment|/* impulse noise control */
DECL|variable|dib3000mc_reg_imp_noise_ctl
r_static
id|u16
id|dib3000mc_reg_imp_noise_ctl
(braket
)braket
op_assign
(brace
l_int|34
comma
l_int|35
)brace
suffix:semicolon
DECL|variable|dib3000mc_imp_noise_ctl
r_static
id|u16
id|dib3000mc_imp_noise_ctl
(braket
)braket
(braket
l_int|2
)braket
op_assign
(brace
(brace
l_int|0x1294
comma
l_int|0xfff8
)brace
comma
multiline_comment|/* mode 0 */
(brace
l_int|0x1294
comma
l_int|0xfff8
)brace
comma
multiline_comment|/* mode 1 */
(brace
l_int|0x1294
comma
l_int|0xfff8
)brace
comma
multiline_comment|/* mode 2 */
(brace
l_int|0x1294
comma
l_int|0xfff8
)brace
comma
multiline_comment|/* mode 3 */
(brace
l_int|0x1294
comma
l_int|0xfff8
)brace
comma
multiline_comment|/* mode 4 */
)brace
suffix:semicolon
multiline_comment|/* AGC registers */
DECL|variable|dib3000mc_reg_agc
r_static
id|u16
id|dib3000mc_reg_agc
(braket
)braket
op_assign
(brace
l_int|36
comma
l_int|37
comma
l_int|38
comma
l_int|39
comma
l_int|42
comma
l_int|43
comma
l_int|44
comma
l_int|45
comma
l_int|46
comma
l_int|47
comma
l_int|48
comma
l_int|49
)brace
suffix:semicolon
DECL|variable|dib3000mc_agc_tuner
r_static
id|u16
id|dib3000mc_agc_tuner
(braket
)braket
(braket
l_int|12
)braket
op_assign
(brace
(brace
l_int|0x0051
comma
l_int|0x301d
comma
l_int|0x0000
comma
l_int|0x1cc7
comma
l_int|0xcf5c
comma
l_int|0x6666
comma
l_int|0xbae1
comma
l_int|0xa148
comma
l_int|0x3b5e
comma
l_int|0x3c1c
comma
l_int|0x001a
comma
l_int|0x2019
)brace
comma
multiline_comment|/* TUNER_PANASONIC_ENV77H04D5, */
(brace
l_int|0x0051
comma
l_int|0x301d
comma
l_int|0x0000
comma
l_int|0x1cc7
comma
l_int|0xdc29
comma
l_int|0x570a
comma
l_int|0xbae1
comma
l_int|0x8ccd
comma
l_int|0x3b6d
comma
l_int|0x551d
comma
l_int|0x000a
comma
l_int|0x951e
)brace
comma
multiline_comment|/* TUNER_PANASONIC_ENV57H13D5, TUNER_PANASONIC_ENV57H12D5 */
(brace
l_int|0x0051
comma
l_int|0x301d
comma
l_int|0x0000
comma
l_int|0x1cc7
comma
l_int|0xffff
comma
l_int|0xffff
comma
l_int|0xffff
comma
l_int|0x0000
comma
l_int|0xfdfd
comma
l_int|0x4040
comma
l_int|0x00fd
comma
l_int|0x4040
)brace
comma
multiline_comment|/* TUNER_SAMSUNG_DTOS333IH102, TUNER_RFAGCIN_UNKNOWN */
(brace
l_int|0x0196
comma
l_int|0x301d
comma
l_int|0x0000
comma
l_int|0x1cc7
comma
l_int|0xbd71
comma
l_int|0x5c29
comma
l_int|0xb5c3
comma
l_int|0x6148
comma
l_int|0x6569
comma
l_int|0x5127
comma
l_int|0x0033
comma
l_int|0x3537
)brace
comma
multiline_comment|/* TUNER_PROVIDER_X */
multiline_comment|/* TODO TUNER_PANASONIC_ENV57H10D8, TUNER_PANASONIC_ENV57H11D8 */
)brace
suffix:semicolon
multiline_comment|/* AGC loop bandwidth */
DECL|variable|dib3000mc_reg_agc_bandwidth
r_static
id|u16
id|dib3000mc_reg_agc_bandwidth
(braket
)braket
op_assign
(brace
l_int|40
comma
l_int|41
)brace
suffix:semicolon
DECL|variable|dib3000mc_agc_bandwidth
r_static
id|u16
id|dib3000mc_agc_bandwidth
(braket
)braket
op_assign
(brace
l_int|0x119
comma
l_int|0x330
)brace
suffix:semicolon
DECL|variable|dib3000mc_reg_agc_bandwidth_general
r_static
id|u16
id|dib3000mc_reg_agc_bandwidth_general
(braket
)braket
op_assign
(brace
l_int|50
comma
l_int|51
comma
l_int|52
comma
l_int|53
comma
l_int|54
)brace
suffix:semicolon
DECL|variable|dib3000mc_agc_bandwidth_general
r_static
id|u16
id|dib3000mc_agc_bandwidth_general
(braket
)braket
op_assign
(brace
l_int|0x8000
comma
l_int|0x91ca
comma
l_int|0x01ba
comma
l_int|0x0087
comma
l_int|0x0087
)brace
suffix:semicolon
DECL|macro|DIB3000MC_REG_IMP_NOISE_55
mdefine_line|#define DIB3000MC_REG_IMP_NOISE_55 &t;&t;(    55)
DECL|macro|DIB3000MC_IMP_NEW_ALGO
mdefine_line|#define DIB3000MC_IMP_NEW_ALGO(w)&t;&t;(w | (1&lt;&lt;10))
multiline_comment|/* Impulse noise params */
DECL|variable|dib3000mc_reg_impulse_noise
r_static
id|u16
id|dib3000mc_reg_impulse_noise
(braket
)braket
op_assign
(brace
l_int|55
comma
l_int|56
comma
l_int|57
)brace
suffix:semicolon
DECL|variable|dib3000mc_impluse_noise
r_static
id|u16
id|dib3000mc_impluse_noise
(braket
)braket
(braket
l_int|3
)braket
op_assign
(brace
(brace
l_int|0x489
comma
l_int|0x89
comma
l_int|0x72
)brace
comma
multiline_comment|/* 5 MHz */
(brace
l_int|0x4a5
comma
l_int|0xa5
comma
l_int|0x89
)brace
comma
multiline_comment|/* 6 MHz */
(brace
l_int|0x4c0
comma
l_int|0xc0
comma
l_int|0xa0
)brace
comma
multiline_comment|/* 7 MHz */
(brace
l_int|0x4db
comma
l_int|0xdb
comma
l_int|0xb7
)brace
comma
multiline_comment|/* 8 Mhz */
)brace
suffix:semicolon
DECL|variable|dib3000mc_reg_fft
r_static
id|u16
id|dib3000mc_reg_fft
(braket
)braket
op_assign
(brace
l_int|58
comma
l_int|59
comma
l_int|60
comma
l_int|61
comma
l_int|62
comma
l_int|63
comma
l_int|64
comma
l_int|65
comma
l_int|66
comma
l_int|67
comma
l_int|68
comma
l_int|69
comma
l_int|70
comma
l_int|71
comma
l_int|72
comma
l_int|73
comma
l_int|74
comma
l_int|75
comma
l_int|76
comma
l_int|77
comma
l_int|78
comma
l_int|79
comma
l_int|80
comma
l_int|81
comma
l_int|82
comma
l_int|83
comma
l_int|84
comma
l_int|85
comma
l_int|86
)brace
suffix:semicolon
DECL|variable|dib3000mc_fft_modes
r_static
id|u16
id|dib3000mc_fft_modes
(braket
)braket
(braket
l_int|29
)braket
op_assign
(brace
(brace
l_int|0x38
comma
l_int|0x6d9
comma
l_int|0x3f28
comma
l_int|0x7a7
comma
l_int|0x3a74
comma
l_int|0x196
comma
l_int|0x32a
comma
l_int|0x48c
comma
l_int|0x3ffe
comma
l_int|0x7f3
comma
l_int|0x2d94
comma
l_int|0x76
comma
l_int|0x53d
comma
l_int|0x3ff8
comma
l_int|0x7e3
comma
l_int|0x3320
comma
l_int|0x76
comma
l_int|0x5b3
comma
l_int|0x3feb
comma
l_int|0x7d2
comma
l_int|0x365e
comma
l_int|0x76
comma
l_int|0x48c
comma
l_int|0x3ffe
comma
l_int|0x5b3
comma
l_int|0x3feb
comma
l_int|0x76
comma
l_int|0x0
comma
l_int|0xd
)brace
comma
multiline_comment|/* fft mode 0 */
(brace
l_int|0x3b
comma
l_int|0x6d9
comma
l_int|0x3f28
comma
l_int|0x7a7
comma
l_int|0x3a74
comma
l_int|0x196
comma
l_int|0x32a
comma
l_int|0x48c
comma
l_int|0x3ffe
comma
l_int|0x7f3
comma
l_int|0x2d94
comma
l_int|0x76
comma
l_int|0x53d
comma
l_int|0x3ff8
comma
l_int|0x7e3
comma
l_int|0x3320
comma
l_int|0x76
comma
l_int|0x5b3
comma
l_int|0x3feb
comma
l_int|0x7d2
comma
l_int|0x365e
comma
l_int|0x76
comma
l_int|0x48c
comma
l_int|0x3ffe
comma
l_int|0x5b3
comma
l_int|0x3feb
comma
l_int|0x0
comma
l_int|0x8200
comma
l_int|0xd
)brace
comma
multiline_comment|/* fft mode 1 */
)brace
suffix:semicolon
DECL|macro|DIB3000MC_REG_UNK_88
mdefine_line|#define DIB3000MC_REG_UNK_88&t;&t;&t;(    88)
DECL|macro|DIB3000MC_UNK_88
mdefine_line|#define DIB3000MC_UNK_88&t;&t;&t;&t;(0x0410)
DECL|variable|dib3000mc_reg_bw
r_static
id|u16
id|dib3000mc_reg_bw
(braket
)braket
op_assign
(brace
l_int|93
comma
l_int|94
comma
l_int|95
comma
l_int|96
comma
l_int|97
comma
l_int|98
)brace
suffix:semicolon
DECL|variable|dib3000mc_bw
r_static
id|u16
id|dib3000mc_bw
(braket
)braket
(braket
l_int|6
)braket
op_assign
(brace
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* 5 MHz */
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* 6 MHz */
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* 7 MHz */
(brace
l_int|0x20
comma
l_int|0x21
comma
l_int|0x20
comma
l_int|0x23
comma
l_int|0x20
comma
l_int|0x27
)brace
comma
multiline_comment|/* 8 MHz */
)brace
suffix:semicolon
multiline_comment|/* phase noise control */
DECL|macro|DIB3000MC_REG_UNK_99
mdefine_line|#define DIB3000MC_REG_UNK_99&t;&t;&t;(    99)
DECL|macro|DIB3000MC_UNK_99
mdefine_line|#define DIB3000MC_UNK_99&t;&t;&t;&t;(0x0220)
DECL|macro|DIB3000MC_REG_SCAN_BOOST
mdefine_line|#define DIB3000MC_REG_SCAN_BOOST&t;&t;(   100)
DECL|macro|DIB3000MC_SCAN_BOOST_ON
mdefine_line|#define DIB3000MC_SCAN_BOOST_ON&t;&t;&t;((11 &lt;&lt; 6) + 6)
DECL|macro|DIB3000MC_SCAN_BOOST_OFF
mdefine_line|#define DIB3000MC_SCAN_BOOST_OFF&t;&t;((16 &lt;&lt; 6) + 9)
multiline_comment|/* timeout ??? */
DECL|macro|DIB3000MC_REG_UNK_110
mdefine_line|#define DIB3000MC_REG_UNK_110&t;&t;&t;(   110)
DECL|macro|DIB3000MC_UNK_110
mdefine_line|#define DIB3000MC_UNK_110&t;&t;&t;&t;(  3277)
DECL|macro|DIB3000MC_REG_UNK_111
mdefine_line|#define DIB3000MC_REG_UNK_111&t;&t;&t;(   111)
DECL|macro|DIB3000MC_UNK_111_PH_N_MODE_0
mdefine_line|#define DIB3000MC_UNK_111_PH_N_MODE_0&t;(     0)
DECL|macro|DIB3000MC_UNK_111_PH_N_MODE_1
mdefine_line|#define DIB3000MC_UNK_111_PH_N_MODE_1&t;(1 &lt;&lt; 1)
multiline_comment|/* superious rm config */
DECL|macro|DIB3000MC_REG_UNK_120
mdefine_line|#define DIB3000MC_REG_UNK_120&t;&t;&t;(   120)
DECL|macro|DIB3000MC_UNK_120
mdefine_line|#define DIB3000MC_UNK_120&t;&t;&t;&t;(  8207)
DECL|macro|DIB3000MC_REG_UNK_133
mdefine_line|#define DIB3000MC_REG_UNK_133&t;&t;&t;(   133)
DECL|macro|DIB3000MC_UNK_133
mdefine_line|#define DIB3000MC_UNK_133&t;&t;&t;&t;( 15564)
DECL|macro|DIB3000MC_REG_UNK_134
mdefine_line|#define DIB3000MC_REG_UNK_134&t;&t;&t;(   134)
DECL|macro|DIB3000MC_UNK_134
mdefine_line|#define DIB3000MC_UNK_134&t;&t;&t;&t;(     0)
multiline_comment|/* adapter config for constellation */
DECL|variable|dib3000mc_reg_adp_cfg
r_static
id|u16
id|dib3000mc_reg_adp_cfg
(braket
)braket
op_assign
(brace
l_int|129
comma
l_int|130
comma
l_int|131
comma
l_int|132
)brace
suffix:semicolon
DECL|variable|dib3000mc_adp_cfg
r_static
id|u16
id|dib3000mc_adp_cfg
(braket
)braket
(braket
l_int|4
)braket
op_assign
(brace
(brace
l_int|0x99a
comma
l_int|0x7fae
comma
l_int|0x333
comma
l_int|0x7ff0
)brace
comma
multiline_comment|/* QPSK  */
(brace
l_int|0x23d
comma
l_int|0x7fdf
comma
l_int|0x0a4
comma
l_int|0x7ff0
)brace
comma
multiline_comment|/* 16-QAM */
(brace
l_int|0x148
comma
l_int|0x7ff0
comma
l_int|0x0a4
comma
l_int|0x7ff8
)brace
comma
multiline_comment|/* 64-QAM */
)brace
suffix:semicolon
DECL|variable|dib3000mc_reg_mobile_mode
r_static
id|u16
id|dib3000mc_reg_mobile_mode
(braket
)braket
op_assign
(brace
l_int|139
comma
l_int|140
comma
l_int|141
comma
l_int|175
comma
l_int|1032
)brace
suffix:semicolon
DECL|variable|dib3000mc_mobile_mode
r_static
id|u16
id|dib3000mc_mobile_mode
(braket
)braket
(braket
l_int|5
)braket
op_assign
(brace
(brace
l_int|0x01
comma
l_int|0x0
comma
l_int|0x0
comma
l_int|0x00
comma
l_int|0x12c
)brace
comma
multiline_comment|/* fixed */
(brace
l_int|0x01
comma
l_int|0x0
comma
l_int|0x0
comma
l_int|0x00
comma
l_int|0x12c
)brace
comma
multiline_comment|/* portable */
(brace
l_int|0x00
comma
l_int|0x0
comma
l_int|0x0
comma
l_int|0x02
comma
l_int|0x000
)brace
comma
multiline_comment|/* mobile */
(brace
l_int|0x00
comma
l_int|0x0
comma
l_int|0x0
comma
l_int|0x02
comma
l_int|0x000
)brace
comma
multiline_comment|/* auto */
)brace
suffix:semicolon
DECL|macro|DIB3000MC_REG_DIVERSITY1
mdefine_line|#define DIB3000MC_REG_DIVERSITY1&t;&t;(   177)
DECL|macro|DIB3000MC_DIVERSITY1_DEFAULT
mdefine_line|#define DIB3000MC_DIVERSITY1_DEFAULT&t;(     1)
DECL|macro|DIB3000MC_REG_DIVERSITY2
mdefine_line|#define DIB3000MC_REG_DIVERSITY2&t;&t;(   178)
DECL|macro|DIB3000MC_DIVERSITY2_DEFAULT
mdefine_line|#define DIB3000MC_DIVERSITY2_DEFAULT&t;(     1)
DECL|macro|DIB3000MC_REG_DIVERSITY3
mdefine_line|#define DIB3000MC_REG_DIVERSITY3&t;&t;(   180)
DECL|macro|DIB3000MC_DIVERSITY3_IN_OFF
mdefine_line|#define DIB3000MC_DIVERSITY3_IN_OFF&t;&t;(0xfff0)
DECL|macro|DIB3000MC_DIVERSITY3_IN_ON
mdefine_line|#define DIB3000MC_DIVERSITY3_IN_ON&t;&t;(0xfff6)
DECL|macro|DIB3000MC_REG_FEC_CFG
mdefine_line|#define DIB3000MC_REG_FEC_CFG&t;&t;&t;(   195)
DECL|macro|DIB3000MC_FEC_CFG
mdefine_line|#define DIB3000MC_FEC_CFG&t;&t;&t;&t;(  0x10)
DECL|macro|DIB3000MC_REG_SMO_MODE
mdefine_line|#define DIB3000MC_REG_SMO_MODE&t;&t;&t;(   206)
DECL|macro|DIB3000MC_SMO_MODE_DEFAULT
mdefine_line|#define DIB3000MC_SMO_MODE_DEFAULT&t;&t;(1 &lt;&lt; 2)
DECL|macro|DIB3000MC_SMO_MODE_FIFO_FLUSH
mdefine_line|#define DIB3000MC_SMO_MODE_FIFO_FLUSH&t;(1 &lt;&lt; 3)
DECL|macro|DIB3000MC_SMO_MODE_FIFO_UNFLUSH
mdefine_line|#define DIB3000MC_SMO_MODE_FIFO_UNFLUSH&t;~DIB3000MC_SMO_MODE_FIFO_FLUSH
DECL|macro|DIB3000MC_SMO_MODE_PID_PARSE
mdefine_line|#define DIB3000MC_SMO_MODE_PID_PARSE&t;(1 &lt;&lt; 4)
DECL|macro|DIB3000MC_SMO_MODE_NO_PID_PARSE
mdefine_line|#define DIB3000MC_SMO_MODE_NO_PID_PARSE&t;~DIB3000MC_SMO_MODE_PID_PARSE
DECL|macro|DIB3000MC_SMO_MODE_188
mdefine_line|#define DIB3000MC_SMO_MODE_188&t;&t;&t;(1 &lt;&lt; 5)
DECL|macro|DIB3000MC_SMO_MODE_SLAVE
mdefine_line|#define DIB3000MC_SMO_MODE_SLAVE&t;&t;(DIB3000MC_SMO_MODE_DEFAULT | &bslash;&n;&t;&t;&t;DIB3000MC_SMO_MODE_188 | DIB3000MC_SMO_MODE_PID_PARSE | (1&lt;&lt;1))
DECL|macro|DIB3000MC_REG_FIFO_THRESHOLD
mdefine_line|#define DIB3000MC_REG_FIFO_THRESHOLD&t;(   207)
DECL|macro|DIB3000MC_FIFO_THRESHOLD_DEFAULT
mdefine_line|#define DIB3000MC_FIFO_THRESHOLD_DEFAULT&t;(  1792)
DECL|macro|DIB3000MC_FIFO_THRESHOLD_SLAVE
mdefine_line|#define DIB3000MC_FIFO_THRESHOLD_SLAVE&t;(   512)
multiline_comment|/*&n; * pidfilter&n; * it is not a hardware pidfilter but a filter which drops all pids&n; * except the ones set. When connected to USB1.1 bandwidth this is important.&n; * DiB3000-MC/P can filter up to 32 PIDs&n; */
DECL|macro|DIB3000MC_REG_FIRST_PID
mdefine_line|#define DIB3000MC_REG_FIRST_PID&t;&t;&t;(   212)
DECL|macro|DIB3000MC_NUM_PIDS
mdefine_line|#define DIB3000MC_NUM_PIDS&t;&t;&t;&t;(    32)
DECL|macro|DIB3000MC_REG_OUTMODE
mdefine_line|#define DIB3000MC_REG_OUTMODE&t;&t;&t;(   244)
DECL|macro|DIB3000MC_OM_PARALLEL_GATED_CLK
mdefine_line|#define DIB3000MC_OM_PARALLEL_GATED_CLK&t;(     0)
DECL|macro|DIB3000MC_OM_PAR_CONT_CLK
mdefine_line|#define DIB3000MC_OM_PAR_CONT_CLK&t;&t;(1 &lt;&lt; 11)
DECL|macro|DIB3000MC_OM_SERIAL
mdefine_line|#define DIB3000MC_OM_SERIAL&t;&t;&t;&t;(2 &lt;&lt; 11)
DECL|macro|DIB3000MC_OM_DIVOUT_ON
mdefine_line|#define DIB3000MC_OM_DIVOUT_ON&t;&t;&t;(4 &lt;&lt; 11)
DECL|macro|DIB3000MC_OM_SLAVE
mdefine_line|#define DIB3000MC_OM_SLAVE&t;&t;&t;&t;(DIB3000MC_OM_DIVOUT_ON | DIB3000MC_OM_PAR_CONT_CLK)
DECL|macro|DIB3000MC_REG_RF_POWER
mdefine_line|#define DIB3000MC_REG_RF_POWER&t;&t;&t;(   392)
DECL|macro|DIB3000MC_REG_FFT_POSITION
mdefine_line|#define DIB3000MC_REG_FFT_POSITION&t;&t;(   407)
DECL|macro|DIB3000MC_REG_DDS_FREQ_MSB
mdefine_line|#define DIB3000MC_REG_DDS_FREQ_MSB&t;&t;(   414)
DECL|macro|DIB3000MC_REG_DDS_FREQ_LSB
mdefine_line|#define DIB3000MC_REG_DDS_FREQ_LSB&t;&t;(   415)
DECL|macro|DIB3000MC_REG_TIMING_OFFS_MSB
mdefine_line|#define DIB3000MC_REG_TIMING_OFFS_MSB&t;(   416)
DECL|macro|DIB3000MC_REG_TIMING_OFFS_LSB
mdefine_line|#define DIB3000MC_REG_TIMING_OFFS_LSB&t;(   417)
DECL|macro|DIB3000MC_REG_TUNING_PARM
mdefine_line|#define DIB3000MC_REG_TUNING_PARM&t;&t;(   458)
DECL|macro|DIB3000MC_TP_QAM
mdefine_line|#define DIB3000MC_TP_QAM(v)&t;&t;&t;&t;((v &gt;&gt; 13) &amp; 0x03)
DECL|macro|DIB3000MC_TP_HRCH
mdefine_line|#define DIB3000MC_TP_HRCH(v)&t;&t;&t;((v &gt;&gt; 12) &amp; 0x01)
DECL|macro|DIB3000MC_TP_ALPHA
mdefine_line|#define DIB3000MC_TP_ALPHA(v)&t;&t;&t;((v &gt;&gt; 9) &amp; 0x07)
DECL|macro|DIB3000MC_TP_FFT
mdefine_line|#define DIB3000MC_TP_FFT(v)&t;&t;&t;&t;((v &gt;&gt; 8) &amp; 0x01)
DECL|macro|DIB3000MC_TP_FEC_CR_HP
mdefine_line|#define DIB3000MC_TP_FEC_CR_HP(v)&t;&t;((v &gt;&gt; 5) &amp; 0x07)
DECL|macro|DIB3000MC_TP_FEC_CR_LP
mdefine_line|#define DIB3000MC_TP_FEC_CR_LP(v)&t;&t;((v &gt;&gt; 2) &amp; 0x07)
DECL|macro|DIB3000MC_TP_GUARD
mdefine_line|#define DIB3000MC_TP_GUARD(v)&t;&t;&t;(v &amp; 0x03)
DECL|macro|DIB3000MC_REG_SIGNAL_NOISE_MSB
mdefine_line|#define DIB3000MC_REG_SIGNAL_NOISE_MSB&t;(   483)
DECL|macro|DIB3000MC_REG_SIGNAL_NOISE_LSB
mdefine_line|#define DIB3000MC_REG_SIGNAL_NOISE_LSB&t;(   484)
DECL|macro|DIB3000MC_REG_MER
mdefine_line|#define DIB3000MC_REG_MER&t;&t;&t;&t;(   485)
DECL|macro|DIB3000MC_REG_BER_MSB
mdefine_line|#define DIB3000MC_REG_BER_MSB&t;&t;&t;(   500)
DECL|macro|DIB3000MC_REG_BER_LSB
mdefine_line|#define DIB3000MC_REG_BER_LSB&t;&t;&t;(   501)
DECL|macro|DIB3000MC_REG_PACKET_ERRORS
mdefine_line|#define DIB3000MC_REG_PACKET_ERRORS&t;&t;(   503)
DECL|macro|DIB3000MC_REG_PACKET_ERROR_COUNT
mdefine_line|#define DIB3000MC_REG_PACKET_ERROR_COUNT&t;(   506)
DECL|macro|DIB3000MC_REG_LOCK_507
mdefine_line|#define DIB3000MC_REG_LOCK_507&t;&t;&t;(   507)
DECL|macro|DIB3000MC_LOCK_507
mdefine_line|#define DIB3000MC_LOCK_507&t;&t;&t;&t;(0x0002) 
singleline_comment|// ? name correct ?
DECL|macro|DIB3000MC_REG_LOCKING
mdefine_line|#define DIB3000MC_REG_LOCKING&t;&t;&t;(   509)
DECL|macro|DIB3000MC_AGC_LOCK
mdefine_line|#define DIB3000MC_AGC_LOCK(v)&t;&t;&t;(v &amp; 0x8000)
DECL|macro|DIB3000MC_CARRIER_LOCK
mdefine_line|#define DIB3000MC_CARRIER_LOCK(v)&t;&t;(v &amp; 0x2000)
DECL|macro|DIB3000MC_MPEG_SYNC_LOCK
mdefine_line|#define DIB3000MC_MPEG_SYNC_LOCK(v)&t;&t;(v &amp; 0x0080)
DECL|macro|DIB3000MC_MPEG_DATA_LOCK
mdefine_line|#define DIB3000MC_MPEG_DATA_LOCK(v)&t;&t;(v &amp; 0x0040)
DECL|macro|DIB3000MC_TPS_LOCK
mdefine_line|#define DIB3000MC_TPS_LOCK(v)&t;&t;&t;(v &amp; 0x0004)
DECL|macro|DIB3000MC_REG_AS_IRQ
mdefine_line|#define DIB3000MC_REG_AS_IRQ&t;&t;&t;(   511)
DECL|macro|DIB3000MC_AS_IRQ_SUCCESS
mdefine_line|#define DIB3000MC_AS_IRQ_SUCCESS&t;&t;(1 &lt;&lt; 1)
DECL|macro|DIB3000MC_AS_IRQ_FAIL
mdefine_line|#define DIB3000MC_AS_IRQ_FAIL&t;&t;&t;(     1)
DECL|macro|DIB3000MC_REG_TUNER
mdefine_line|#define DIB3000MC_REG_TUNER&t;&t;&t;&t;(   769)
DECL|macro|DIB3000MC_REG_RST_I2C_ADDR
mdefine_line|#define DIB3000MC_REG_RST_I2C_ADDR&t;&t;(  1024)
DECL|macro|DIB3000MC_DEMOD_ADDR_ON
mdefine_line|#define DIB3000MC_DEMOD_ADDR_ON&t;&t;&t;(     1)
DECL|macro|DIB3000MC_DEMOD_ADDR
mdefine_line|#define DIB3000MC_DEMOD_ADDR(a)&t;&t;&t;((a &lt;&lt; 3) &amp; 0x03F0)
DECL|macro|DIB3000MC_REG_RESTART
mdefine_line|#define DIB3000MC_REG_RESTART&t;&t;&t;(  1027)
DECL|macro|DIB3000MC_RESTART_OFF
mdefine_line|#define DIB3000MC_RESTART_OFF&t;&t;&t;(0x0000)
DECL|macro|DIB3000MC_RESTART_AGC
mdefine_line|#define DIB3000MC_RESTART_AGC&t;&t;&t;(0x0800)
DECL|macro|DIB3000MC_RESTART_CONFIG
mdefine_line|#define DIB3000MC_RESTART_CONFIG&t;&t;(0x8000)
DECL|macro|DIB3000MC_REG_RESTART_VIT
mdefine_line|#define DIB3000MC_REG_RESTART_VIT&t;&t;(  1028)
DECL|macro|DIB3000MC_RESTART_VIT_OFF
mdefine_line|#define DIB3000MC_RESTART_VIT_OFF&t;&t;(     0)
DECL|macro|DIB3000MC_RESTART_VIT_ON
mdefine_line|#define DIB3000MC_RESTART_VIT_ON&t;&t;(     1)
DECL|macro|DIB3000MC_REG_CLK_CFG_1
mdefine_line|#define DIB3000MC_REG_CLK_CFG_1&t;&t;&t;(  1031)
DECL|macro|DIB3000MC_CLK_CFG_1_POWER_UP
mdefine_line|#define DIB3000MC_CLK_CFG_1_POWER_UP&t;(     0)
DECL|macro|DIB3000MC_CLK_CFG_1_POWER_DOWN
mdefine_line|#define DIB3000MC_CLK_CFG_1_POWER_DOWN&t;(0xffff)
DECL|macro|DIB3000MC_REG_CLK_CFG_2
mdefine_line|#define DIB3000MC_REG_CLK_CFG_2&t;&t;&t;(  1032)
DECL|macro|DIB3000MC_CLK_CFG_2_PUP_FIXED
mdefine_line|#define DIB3000MC_CLK_CFG_2_PUP_FIXED&t;(0x012c)
DECL|macro|DIB3000MC_CLK_CFG_2_PUP_PORT
mdefine_line|#define DIB3000MC_CLK_CFG_2_PUP_PORT&t;(0x0104)
DECL|macro|DIB3000MC_CLK_CFG_2_PUP_MOBILE
mdefine_line|#define DIB3000MC_CLK_CFG_2_PUP_MOBILE  (0x0000)
DECL|macro|DIB3000MC_CLK_CFG_2_POWER_DOWN
mdefine_line|#define DIB3000MC_CLK_CFG_2_POWER_DOWN&t;(0xffff)
DECL|macro|DIB3000MC_REG_CLK_CFG_3
mdefine_line|#define DIB3000MC_REG_CLK_CFG_3&t;&t;&t;(  1033)
DECL|macro|DIB3000MC_CLK_CFG_3_POWER_UP
mdefine_line|#define DIB3000MC_CLK_CFG_3_POWER_UP&t;(     0)
DECL|macro|DIB3000MC_CLK_CFG_3_POWER_DOWN
mdefine_line|#define DIB3000MC_CLK_CFG_3_POWER_DOWN&t;(0xfff5)
DECL|macro|DIB3000MC_REG_CLK_CFG_7
mdefine_line|#define DIB3000MC_REG_CLK_CFG_7&t;&t;&t;(  1037)
DECL|macro|DIB3000MC_CLK_CFG_7_INIT
mdefine_line|#define DIB3000MC_CLK_CFG_7_INIT&t;&t;( 12592)
DECL|macro|DIB3000MC_CLK_CFG_7_POWER_UP
mdefine_line|#define DIB3000MC_CLK_CFG_7_POWER_UP&t;(~0x0003)
DECL|macro|DIB3000MC_CLK_CFG_7_PWR_DOWN
mdefine_line|#define DIB3000MC_CLK_CFG_7_PWR_DOWN&t;(0x0003)
DECL|macro|DIB3000MC_CLK_CFG_7_DIV_IN_OFF
mdefine_line|#define DIB3000MC_CLK_CFG_7_DIV_IN_OFF&t;(1 &lt;&lt; 8)
multiline_comment|/* was commented out ??? */
DECL|macro|DIB3000MC_REG_CLK_CFG_8
mdefine_line|#define DIB3000MC_REG_CLK_CFG_8&t;&t;&t;(  1038)
DECL|macro|DIB3000MC_CLK_CFG_8_POWER_UP
mdefine_line|#define DIB3000MC_CLK_CFG_8_POWER_UP&t;(0x160c)
DECL|macro|DIB3000MC_REG_CLK_CFG_9
mdefine_line|#define DIB3000MC_REG_CLK_CFG_9&t;&t;&t;(  1039)
DECL|macro|DIB3000MC_CLK_CFG_9_POWER_UP
mdefine_line|#define DIB3000MC_CLK_CFG_9_POWER_UP&t;(     0)
multiline_comment|/* also clock ??? */
DECL|macro|DIB3000MC_REG_ELEC_OUT
mdefine_line|#define DIB3000MC_REG_ELEC_OUT&t;&t;&t;(  1040)
DECL|macro|DIB3000MC_ELEC_OUT_HIGH_Z
mdefine_line|#define DIB3000MC_ELEC_OUT_HIGH_Z&t;&t;(     0)
DECL|macro|DIB3000MC_ELEC_OUT_DIV_OUT_ON
mdefine_line|#define DIB3000MC_ELEC_OUT_DIV_OUT_ON&t;(     1)
DECL|macro|DIB3000MC_ELEC_OUT_SLAVE
mdefine_line|#define DIB3000MC_ELEC_OUT_SLAVE&t;&t;(     3)
macro_line|#endif
eof
