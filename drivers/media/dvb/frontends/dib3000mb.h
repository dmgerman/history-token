multiline_comment|/*&n; * dib3000mb.h&n; *&n; * Copyright (C) 2004 Patrick Boettcher (patrick.boettcher@desy.de)&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License as&n; *&t;published by the Free Software Foundation, version 2.&n; *&n; * &n; *&n; * for more information see dib3000mb.c .&n; */
macro_line|#ifndef __DIB3000MB_H_INCLUDED__
DECL|macro|__DIB3000MB_H_INCLUDED__
mdefine_line|#define __DIB3000MB_H_INCLUDED__
multiline_comment|/* info and err, taken from usb.h, if there is anything available like by default,&n; * please change !&n; */
DECL|macro|err
mdefine_line|#define err(format, arg...) printk(KERN_ERR &quot;%s: &quot; format &quot;&bslash;n&quot; , __FILE__ , ## arg)
DECL|macro|info
mdefine_line|#define info(format, arg...) printk(KERN_INFO &quot;%s: &quot; format &quot;&bslash;n&quot; , __FILE__ , ## arg)
DECL|macro|warn
mdefine_line|#define warn(format, arg...) printk(KERN_WARNING &quot;%s: &quot; format &quot;&bslash;n&quot; , __FILE__ , ## arg)
multiline_comment|/* register addresses and some of their default values */
multiline_comment|/* restart subsystems */
DECL|macro|DIB3000MB_REG_RESTART
mdefine_line|#define DIB3000MB_REG_RESTART&t;&t;&t;(     0)
DECL|macro|DIB3000MB_RESTART_OFF
mdefine_line|#define DIB3000MB_RESTART_OFF&t;&t;&t;(     0)
DECL|macro|DIB3000MB_RESTART_AUTO_SEARCH
mdefine_line|#define DIB3000MB_RESTART_AUTO_SEARCH&t;&t;(1 &lt;&lt; 1)
DECL|macro|DIB3000MB_RESTART_CTRL
mdefine_line|#define DIB3000MB_RESTART_CTRL&t;&t;&t;&t;(1 &lt;&lt; 2)
DECL|macro|DIB3000MB_RESTART_AGC
mdefine_line|#define DIB3000MB_RESTART_AGC&t;&t;&t;&t;(1 &lt;&lt; 3)
multiline_comment|/* FFT size */
DECL|macro|DIB3000MB_REG_FFT
mdefine_line|#define DIB3000MB_REG_FFT&t;&t;&t;&t;(     1)
DECL|macro|DIB3000MB_FFT_2K
mdefine_line|#define DIB3000MB_FFT_2K&t;&t;&t;&t;&t;(     0)
DECL|macro|DIB3000MB_FFT_8K
mdefine_line|#define DIB3000MB_FFT_8K&t;&t;&t;&t;&t;(     1)
DECL|macro|DIB3000MB_FFT_AUTO
mdefine_line|#define DIB3000MB_FFT_AUTO&t;&t;&t;&t;&t;(     1)
multiline_comment|/* Guard time */
DECL|macro|DIB3000MB_REG_GUARD_TIME
mdefine_line|#define DIB3000MB_REG_GUARD_TIME&t;&t;(     2)
DECL|macro|DIB3000MB_GUARD_TIME_1_32
mdefine_line|#define DIB3000MB_GUARD_TIME_1_32&t;&t;&t;(     0)
DECL|macro|DIB3000MB_GUARD_TIME_1_16
mdefine_line|#define DIB3000MB_GUARD_TIME_1_16&t;&t;&t;(     1)
DECL|macro|DIB3000MB_GUARD_TIME_1_8
mdefine_line|#define DIB3000MB_GUARD_TIME_1_8&t;&t;&t;(     2)
DECL|macro|DIB3000MB_GUARD_TIME_1_4
mdefine_line|#define DIB3000MB_GUARD_TIME_1_4&t;&t;&t;(     3)
DECL|macro|DIB3000MB_GUARD_TIME_AUTO
mdefine_line|#define DIB3000MB_GUARD_TIME_AUTO&t;&t;&t;(     0)
multiline_comment|/* QAM */
DECL|macro|DIB3000MB_REG_QAM
mdefine_line|#define DIB3000MB_REG_QAM&t;&t;&t;&t;(     3)
DECL|macro|DIB3000MB_QAM_QPSK
mdefine_line|#define DIB3000MB_QAM_QPSK&t;&t;&t;&t;&t;(     0)
DECL|macro|DIB3000MB_QAM_QAM16
mdefine_line|#define DIB3000MB_QAM_QAM16&t;&t;&t;&t;&t;(     1)
DECL|macro|DIB3000MB_QAM_QAM64
mdefine_line|#define DIB3000MB_QAM_QAM64&t;&t;&t;&t;&t;(     2)
DECL|macro|DIB3000MB_QAM_RESERVED
mdefine_line|#define DIB3000MB_QAM_RESERVED&t;&t;&t;&t;(     3)
multiline_comment|/* Alpha coefficient high priority Viterbi algorithm */
DECL|macro|DIB3000MB_REG_VIT_ALPHA
mdefine_line|#define DIB3000MB_REG_VIT_ALPHA&t;&t;&t;(     4)
DECL|macro|DIB3000MB_VIT_ALPHA_OFF
mdefine_line|#define DIB3000MB_VIT_ALPHA_OFF&t;&t;&t;&t;(     0)
DECL|macro|DIB3000MB_VIT_ALPHA_1
mdefine_line|#define DIB3000MB_VIT_ALPHA_1&t;&t;&t;&t;(     1)
DECL|macro|DIB3000MB_VIT_ALPHA_2
mdefine_line|#define DIB3000MB_VIT_ALPHA_2&t;&t;&t;&t;(     2)
DECL|macro|DIB3000MB_VIT_ALPHA_4
mdefine_line|#define DIB3000MB_VIT_ALPHA_4&t;&t;&t;&t;(     4)
DECL|macro|DIB3000MB_VIT_ALPHA_AUTO
mdefine_line|#define DIB3000MB_VIT_ALPHA_AUTO&t;&t;&t;(     7)
multiline_comment|/* spectrum inversion */
DECL|macro|DIB3000MB_REG_DDS_INV
mdefine_line|#define DIB3000MB_REG_DDS_INV&t;&t;&t;(     5)
DECL|macro|DIB3000MB_DDS_INV_OFF
mdefine_line|#define DIB3000MB_DDS_INV_OFF&t;&t;&t;&t;(     0)
DECL|macro|DIB3000MB_DDS_INV_ON
mdefine_line|#define DIB3000MB_DDS_INV_ON&t;&t;&t;&t;(     1)
multiline_comment|/* DDS frequency value (IF position) ad ? values don&squot;t match reg_3000mb.txt */
DECL|macro|DIB3000MB_REG_DDS_FREQ_MSB
mdefine_line|#define DIB3000MB_REG_DDS_FREQ_MSB&t;&t;(     6)
DECL|macro|DIB3000MB_REG_DDS_FREQ_LSB
mdefine_line|#define DIB3000MB_REG_DDS_FREQ_LSB&t;&t;(     7)
DECL|macro|DIB3000MB_DDS_FREQ_MSB
mdefine_line|#define DIB3000MB_DDS_FREQ_MSB&t;&t;&t;&t;(   178)
DECL|macro|DIB3000MB_DDS_FREQ_LSB
mdefine_line|#define DIB3000MB_DDS_FREQ_LSB&t;&t;&t;&t;(  8990)
multiline_comment|/* timing frequency (carrier spacing) */
DECL|macro|DIB3000MB_REG_TIMING_FREQ_MSB
mdefine_line|#define DIB3000MB_REG_TIMING_FREQ_MSB&t;(     8)
DECL|macro|DIB3000MB_REG_TIMING_FREQ_LSB
mdefine_line|#define DIB3000MB_REG_TIMING_FREQ_LSB&t;(     9)
DECL|variable|dib3000mb_reg_timing_freq
r_static
id|u16
id|dib3000mb_reg_timing_freq
(braket
)braket
op_assign
(brace
id|DIB3000MB_REG_TIMING_FREQ_MSB
comma
id|DIB3000MB_REG_TIMING_FREQ_LSB
)brace
suffix:semicolon
DECL|variable|dib3000mb_timing_freq
r_static
id|u16
id|dib3000mb_timing_freq
(braket
)braket
(braket
l_int|2
)braket
op_assign
(brace
(brace
l_int|126
comma
l_int|48873
)brace
comma
multiline_comment|/* 6 MHz */
(brace
l_int|147
comma
l_int|57019
)brace
comma
multiline_comment|/* 7 MHz */
(brace
l_int|168
comma
l_int|65164
)brace
comma
multiline_comment|/* 8 MHz */
)brace
suffix:semicolon
multiline_comment|/* impulse noise parameter */
DECL|macro|DIB3000MB_REG_IMPNOISE_10
mdefine_line|#define DIB3000MB_REG_IMPNOISE_10&t;&t;(    10)
DECL|macro|DIB3000MB_REG_IMPNOISE_11
mdefine_line|#define DIB3000MB_REG_IMPNOISE_11&t;&t;(    11)
DECL|macro|DIB3000MB_REG_IMPNOISE_12
mdefine_line|#define DIB3000MB_REG_IMPNOISE_12&t;&t;(    12)
DECL|macro|DIB3000MB_REG_IMPNOISE_13
mdefine_line|#define DIB3000MB_REG_IMPNOISE_13&t;&t;(    13)
DECL|macro|DIB3000MB_REG_IMPNOISE_14
mdefine_line|#define DIB3000MB_REG_IMPNOISE_14&t;&t;(    14)
DECL|macro|DIB3000MB_REG_IMPNOISE_15
mdefine_line|#define DIB3000MB_REG_IMPNOISE_15&t;&t;(    15)
multiline_comment|/* 36 ??? */
DECL|macro|DIB3000MB_REG_IMPNOISE_36
mdefine_line|#define DIB3000MB_REG_IMPNOISE_36&t;&t;(    36)
DECL|enum|dib3000mb_impulse_noise_type
r_enum
id|dib3000mb_impulse_noise_type
(brace
DECL|enumerator|DIB3000MB_IMPNOISE_OFF
id|DIB3000MB_IMPNOISE_OFF
comma
DECL|enumerator|DIB3000MB_IMPNOISE_MOBILE
id|DIB3000MB_IMPNOISE_MOBILE
comma
DECL|enumerator|DIB3000MB_IMPNOISE_FIXED
id|DIB3000MB_IMPNOISE_FIXED
comma
DECL|enumerator|DIB3000MB_IMPNOISE_DEFAULT
id|DIB3000MB_IMPNOISE_DEFAULT
)brace
suffix:semicolon
DECL|variable|dib3000mb_reg_impulse_noise
r_static
id|u16
id|dib3000mb_reg_impulse_noise
(braket
)braket
op_assign
(brace
id|DIB3000MB_REG_IMPNOISE_10
comma
id|DIB3000MB_REG_IMPNOISE_11
comma
id|DIB3000MB_REG_IMPNOISE_12
comma
id|DIB3000MB_REG_IMPNOISE_15
comma
id|DIB3000MB_REG_IMPNOISE_36
)brace
suffix:semicolon
DECL|variable|dib3000mb_impulse_noise_values
r_static
id|u16
id|dib3000mb_impulse_noise_values
(braket
)braket
(braket
l_int|5
)braket
op_assign
(brace
(brace
l_int|0x0000
comma
l_int|0x0004
comma
l_int|0x0014
comma
l_int|0x01ff
comma
l_int|0x0399
)brace
comma
multiline_comment|/* off */
(brace
l_int|0x0001
comma
l_int|0x0004
comma
l_int|0x0014
comma
l_int|0x01ff
comma
l_int|0x037b
)brace
comma
multiline_comment|/* mobile */
(brace
l_int|0x0001
comma
l_int|0x0004
comma
l_int|0x0020
comma
l_int|0x01bd
comma
l_int|0x0399
)brace
comma
multiline_comment|/* fixed */
(brace
l_int|0x0000
comma
l_int|0x0002
comma
l_int|0x000a
comma
l_int|0x01ff
comma
l_int|0x0399
)brace
comma
multiline_comment|/* default */
)brace
suffix:semicolon
multiline_comment|/*&n; * Dual Automatic-Gain-Control&n; * - gains RF in tuner (AGC1)&n; * - gains IF after filtering (AGC2)&n; */
multiline_comment|/* also from 16 to 18 */
DECL|macro|DIB3000MB_REG_AGC_GAIN_19
mdefine_line|#define DIB3000MB_REG_AGC_GAIN_19&t;&t;(    19)
DECL|macro|DIB3000MB_REG_AGC_GAIN_20
mdefine_line|#define DIB3000MB_REG_AGC_GAIN_20&t;&t;(    20)
DECL|macro|DIB3000MB_REG_AGC_GAIN_21
mdefine_line|#define DIB3000MB_REG_AGC_GAIN_21&t;&t;(    21)
DECL|macro|DIB3000MB_REG_AGC_GAIN_22
mdefine_line|#define DIB3000MB_REG_AGC_GAIN_22&t;&t;(    22)
DECL|macro|DIB3000MB_REG_AGC_GAIN_23
mdefine_line|#define DIB3000MB_REG_AGC_GAIN_23&t;&t;(    23)
DECL|macro|DIB3000MB_REG_AGC_GAIN_24
mdefine_line|#define DIB3000MB_REG_AGC_GAIN_24&t;&t;(    24)
DECL|macro|DIB3000MB_REG_AGC_GAIN_25
mdefine_line|#define DIB3000MB_REG_AGC_GAIN_25&t;&t;(    25)
DECL|macro|DIB3000MB_REG_AGC_GAIN_26
mdefine_line|#define DIB3000MB_REG_AGC_GAIN_26&t;&t;(    26)
DECL|macro|DIB3000MB_REG_AGC_GAIN_27
mdefine_line|#define DIB3000MB_REG_AGC_GAIN_27&t;&t;(    27)
DECL|macro|DIB3000MB_REG_AGC_GAIN_28
mdefine_line|#define DIB3000MB_REG_AGC_GAIN_28&t;&t;(    28)
DECL|macro|DIB3000MB_REG_AGC_GAIN_29
mdefine_line|#define DIB3000MB_REG_AGC_GAIN_29&t;&t;(    29)
DECL|macro|DIB3000MB_REG_AGC_GAIN_30
mdefine_line|#define DIB3000MB_REG_AGC_GAIN_30&t;&t;(    30)
DECL|macro|DIB3000MB_REG_AGC_GAIN_31
mdefine_line|#define DIB3000MB_REG_AGC_GAIN_31&t;&t;(    31)
DECL|macro|DIB3000MB_REG_AGC_GAIN_32
mdefine_line|#define DIB3000MB_REG_AGC_GAIN_32&t;&t;(    32)
DECL|variable|dib3000mb_reg_agc_gain
r_static
id|u16
id|dib3000mb_reg_agc_gain
(braket
)braket
op_assign
(brace
id|DIB3000MB_REG_AGC_GAIN_19
comma
id|DIB3000MB_REG_AGC_GAIN_20
comma
id|DIB3000MB_REG_AGC_GAIN_21
comma
id|DIB3000MB_REG_AGC_GAIN_22
comma
id|DIB3000MB_REG_AGC_GAIN_23
comma
id|DIB3000MB_REG_AGC_GAIN_24
comma
id|DIB3000MB_REG_AGC_GAIN_25
comma
id|DIB3000MB_REG_AGC_GAIN_26
comma
id|DIB3000MB_REG_AGC_GAIN_27
comma
id|DIB3000MB_REG_AGC_GAIN_28
comma
id|DIB3000MB_REG_AGC_GAIN_29
comma
id|DIB3000MB_REG_AGC_GAIN_30
comma
id|DIB3000MB_REG_AGC_GAIN_31
comma
id|DIB3000MB_REG_AGC_GAIN_32
)brace
suffix:semicolon
DECL|variable|dib3000mb_default_agc_gain
r_static
id|u16
id|dib3000mb_default_agc_gain
(braket
)braket
op_assign
(brace
l_int|0x0001
comma
l_int|52429
comma
l_int|623
comma
l_int|128
comma
l_int|166
comma
l_int|195
comma
l_int|61
comma
multiline_comment|/* RF ??? */
l_int|0x0001
comma
l_int|53766
comma
l_int|38011
comma
l_int|0
comma
l_int|90
comma
l_int|33
comma
l_int|23
)brace
suffix:semicolon
multiline_comment|/* IF ??? */
multiline_comment|/* phase noise */
DECL|macro|DIB3000MB_REG_PHASE_NOISE_33
mdefine_line|#define DIB3000MB_REG_PHASE_NOISE_33&t;&t;(    33)
DECL|macro|DIB3000MB_REG_PHASE_NOISE_34
mdefine_line|#define DIB3000MB_REG_PHASE_NOISE_34&t;&t;(    34)
DECL|macro|DIB3000MB_REG_PHASE_NOISE_35
mdefine_line|#define DIB3000MB_REG_PHASE_NOISE_35&t;&t;(    35)
DECL|macro|DIB3000MB_REG_PHASE_NOISE_36
mdefine_line|#define DIB3000MB_REG_PHASE_NOISE_36&t;&t;(    36)
DECL|macro|DIB3000MB_REG_PHASE_NOISE_37
mdefine_line|#define DIB3000MB_REG_PHASE_NOISE_37&t;&t;(    37)
DECL|macro|DIB3000MB_REG_PHASE_NOISE_38
mdefine_line|#define DIB3000MB_REG_PHASE_NOISE_38&t;&t;(    38)
multiline_comment|/* DIB3000MB_REG_PHASE_NOISE_36 is set when setting the impulse noise */
DECL|variable|dib3000mb_reg_phase_noise
r_static
id|u16
id|dib3000mb_reg_phase_noise
(braket
)braket
op_assign
(brace
id|DIB3000MB_REG_PHASE_NOISE_33
comma
id|DIB3000MB_REG_PHASE_NOISE_34
comma
id|DIB3000MB_REG_PHASE_NOISE_35
comma
id|DIB3000MB_REG_PHASE_NOISE_37
comma
id|DIB3000MB_REG_PHASE_NOISE_38
)brace
suffix:semicolon
DECL|variable|dib3000mb_default_noise_phase
r_static
id|u16
id|dib3000mb_default_noise_phase
(braket
)braket
op_assign
(brace
l_int|2
comma
l_int|544
comma
l_int|0
comma
l_int|5
comma
l_int|4
)brace
suffix:semicolon
multiline_comment|/* lock duration */
DECL|macro|DIB3000MB_REG_LOCK_DURATION_39
mdefine_line|#define DIB3000MB_REG_LOCK_DURATION_39&t;(    39)
DECL|macro|DIB3000MB_REG_LOCK_DURATION_40
mdefine_line|#define DIB3000MB_REG_LOCK_DURATION_40&t;(    40)
DECL|variable|dib3000mb_reg_lock_duration
r_static
id|u16
id|dib3000mb_reg_lock_duration
(braket
)braket
op_assign
(brace
id|DIB3000MB_REG_LOCK_DURATION_39
comma
id|DIB3000MB_REG_LOCK_DURATION_40
)brace
suffix:semicolon
DECL|variable|dib3000mb_default_lock_duration
r_static
id|u16
id|dib3000mb_default_lock_duration
(braket
)braket
op_assign
(brace
l_int|135
comma
l_int|135
)brace
suffix:semicolon
multiline_comment|/* AGC loop bandwidth */
DECL|macro|DIB3000MB_REG_AGC_BW_43
mdefine_line|#define DIB3000MB_REG_AGC_BW_43&t;&t;&t;(    43)
DECL|macro|DIB3000MB_REG_AGC_BW_44
mdefine_line|#define DIB3000MB_REG_AGC_BW_44&t;&t;&t;(    44)
DECL|macro|DIB3000MB_REG_AGC_BW_45
mdefine_line|#define DIB3000MB_REG_AGC_BW_45&t;&t;&t;(    45)
DECL|macro|DIB3000MB_REG_AGC_BW_46
mdefine_line|#define DIB3000MB_REG_AGC_BW_46&t;&t;&t;(    46)
DECL|macro|DIB3000MB_REG_AGC_BW_47
mdefine_line|#define DIB3000MB_REG_AGC_BW_47&t;&t;&t;(    47)
DECL|macro|DIB3000MB_REG_AGC_BW_48
mdefine_line|#define DIB3000MB_REG_AGC_BW_48&t;&t;&t;(    48)
DECL|macro|DIB3000MB_REG_AGC_BW_49
mdefine_line|#define DIB3000MB_REG_AGC_BW_49&t;&t;&t;(    49)
DECL|macro|DIB3000MB_REG_AGC_BW_50
mdefine_line|#define DIB3000MB_REG_AGC_BW_50&t;&t;&t;(    50)
DECL|variable|dib3000mb_reg_agc_bandwidth
r_static
id|u16
id|dib3000mb_reg_agc_bandwidth
(braket
)braket
op_assign
(brace
id|DIB3000MB_REG_AGC_BW_43
comma
id|DIB3000MB_REG_AGC_BW_44
comma
id|DIB3000MB_REG_AGC_BW_45
comma
id|DIB3000MB_REG_AGC_BW_46
comma
id|DIB3000MB_REG_AGC_BW_47
comma
id|DIB3000MB_REG_AGC_BW_48
comma
id|DIB3000MB_REG_AGC_BW_49
comma
id|DIB3000MB_REG_AGC_BW_50
)brace
suffix:semicolon
DECL|variable|dib3000mb_agc_bandwidth_low
r_static
id|u16
id|dib3000mb_agc_bandwidth_low
(braket
)braket
op_assign
(brace
l_int|2088
comma
l_int|10
comma
l_int|2088
comma
l_int|10
comma
l_int|3448
comma
l_int|5
comma
l_int|3448
comma
l_int|5
)brace
suffix:semicolon
DECL|variable|dib3000mb_agc_bandwidth_high
r_static
id|u16
id|dib3000mb_agc_bandwidth_high
(braket
)braket
op_assign
(brace
l_int|2349
comma
l_int|5
comma
l_int|2349
comma
l_int|5
comma
l_int|2586
comma
l_int|2
comma
l_int|2586
comma
l_int|2
)brace
suffix:semicolon
multiline_comment|/*&n; * lock0 definition (coff_lock)&n; */
DECL|macro|DIB3000MB_REG_LOCK0_MASK
mdefine_line|#define DIB3000MB_REG_LOCK0_MASK&t;&t;(    51)
DECL|macro|DIB3000MB_LOCK0_DEFAULT
mdefine_line|#define DIB3000MB_LOCK0_DEFAULT&t;&t;&t;&t;(     4)
multiline_comment|/*&n; * lock1 definition (cpil_lock)&n; * for auto search&n; * which values hide behind the lock masks&n; */
DECL|macro|DIB3000MB_REG_LOCK1_MASK
mdefine_line|#define DIB3000MB_REG_LOCK1_MASK&t;&t;(    52)
DECL|macro|DIB3000MB_LOCK1_SEARCH_4
mdefine_line|#define DIB3000MB_LOCK1_SEARCH_4&t;&t;&t;(0x0004)
DECL|macro|DIB3000MB_LOCK1_SEARCH_2048
mdefine_line|#define DIB3000MB_LOCK1_SEARCH_2048&t;&t;&t;(0x0800)
DECL|macro|DIB3000MB_LOCK1_DEFAULT
mdefine_line|#define DIB3000MB_LOCK1_DEFAULT&t;&t;&t;&t;(0x0001)
multiline_comment|/*&n; * lock2 definition (fec_lock) */
DECL|macro|DIB3000MB_REG_LOCK2_MASK
mdefine_line|#define DIB3000MB_REG_LOCK2_MASK&t;&t;(    53)
DECL|macro|DIB3000MB_LOCK2_DEFAULT
mdefine_line|#define DIB3000MB_LOCK2_DEFAULT&t;&t;&t;&t;(0x0080)
multiline_comment|/*&n; * SEQ ? what was that again ... :)&n; * changes when, inversion, guard time and fft is&n; * either automatically detected or not&n; */
DECL|macro|DIB3000MB_REG_SEQ
mdefine_line|#define DIB3000MB_REG_SEQ&t;&t;&t;&t;(    54)
multiline_comment|/* all values have been set manually */
DECL|variable|dib3000mb_seq
r_static
id|u16
id|dib3000mb_seq
(braket
l_int|2
)braket
(braket
l_int|2
)braket
(braket
l_int|2
)braket
op_assign
multiline_comment|/* fft,gua,   inv   */
(brace
multiline_comment|/* fft */
(brace
multiline_comment|/* gua */
(brace
l_int|0
comma
l_int|1
)brace
comma
multiline_comment|/*  0   0   { 0,1 } */
(brace
l_int|3
comma
l_int|9
)brace
comma
multiline_comment|/*  0   1   { 0,1 } */
)brace
comma
(brace
(brace
l_int|2
comma
l_int|5
)brace
comma
multiline_comment|/*  1   0   { 0,1 } */
(brace
l_int|6
comma
l_int|11
)brace
comma
multiline_comment|/*  1   1   { 0,1 } */
)brace
)brace
suffix:semicolon
multiline_comment|/* bandwidth */
DECL|macro|DIB3000MB_REG_BW_55
mdefine_line|#define DIB3000MB_REG_BW_55&t;&t;&t;&t;(    55)
DECL|macro|DIB3000MB_REG_BW_56
mdefine_line|#define DIB3000MB_REG_BW_56&t;&t;&t;&t;(    56)
DECL|macro|DIB3000MB_REG_BW_57
mdefine_line|#define DIB3000MB_REG_BW_57&t;&t;&t;&t;(    57)
DECL|macro|DIB3000MB_REG_BW_58
mdefine_line|#define DIB3000MB_REG_BW_58&t;&t;&t;&t;(    58)
DECL|macro|DIB3000MB_REG_BW_59
mdefine_line|#define DIB3000MB_REG_BW_59&t;&t;&t;&t;(    59)
DECL|macro|DIB3000MB_REG_BW_60
mdefine_line|#define DIB3000MB_REG_BW_60&t;&t;&t;&t;(    60)
DECL|macro|DIB3000MB_REG_BW_61
mdefine_line|#define DIB3000MB_REG_BW_61&t;&t;&t;&t;(    61)
DECL|macro|DIB3000MB_REG_BW_62
mdefine_line|#define DIB3000MB_REG_BW_62&t;&t;&t;&t;(    62)
DECL|macro|DIB3000MB_REG_BW_63
mdefine_line|#define DIB3000MB_REG_BW_63&t;&t;&t;&t;(    63)
DECL|macro|DIB3000MB_REG_BW_64
mdefine_line|#define DIB3000MB_REG_BW_64&t;&t;&t;&t;(    64)
DECL|macro|DIB3000MB_REG_BW_65
mdefine_line|#define DIB3000MB_REG_BW_65&t;&t;&t;&t;(    65)
DECL|macro|DIB3000MB_REG_BW_66
mdefine_line|#define DIB3000MB_REG_BW_66&t;&t;&t;&t;(    66)
DECL|macro|DIB3000MB_REG_BW_67
mdefine_line|#define DIB3000MB_REG_BW_67&t;&t;&t;&t;(    67)
DECL|variable|dib3000mb_reg_bandwidth
r_static
id|u16
id|dib3000mb_reg_bandwidth
(braket
)braket
op_assign
(brace
id|DIB3000MB_REG_BW_55
comma
id|DIB3000MB_REG_BW_56
comma
id|DIB3000MB_REG_BW_57
comma
id|DIB3000MB_REG_BW_58
comma
id|DIB3000MB_REG_BW_59
comma
id|DIB3000MB_REG_BW_60
comma
id|DIB3000MB_REG_BW_61
comma
id|DIB3000MB_REG_BW_62
comma
id|DIB3000MB_REG_BW_63
comma
id|DIB3000MB_REG_BW_64
comma
id|DIB3000MB_REG_BW_65
comma
id|DIB3000MB_REG_BW_66
comma
id|DIB3000MB_REG_BW_67
)brace
suffix:semicolon
DECL|variable|dib3000mb_bandwidth_6mhz
r_static
id|u16
id|dib3000mb_bandwidth_6mhz
(braket
)braket
op_assign
(brace
l_int|0
comma
l_int|33
comma
l_int|53312
comma
l_int|112
comma
l_int|46635
comma
l_int|563
comma
l_int|36565
comma
l_int|0
comma
l_int|1000
comma
l_int|0
comma
l_int|1010
comma
l_int|1
comma
l_int|45264
)brace
suffix:semicolon
DECL|variable|dib3000mb_bandwidth_7mhz
r_static
id|u16
id|dib3000mb_bandwidth_7mhz
(braket
)braket
op_assign
(brace
l_int|0
comma
l_int|28
comma
l_int|64421
comma
l_int|96
comma
l_int|39973
comma
l_int|483
comma
l_int|3255
comma
l_int|0
comma
l_int|1000
comma
l_int|0
comma
l_int|1010
comma
l_int|1
comma
l_int|45264
)brace
suffix:semicolon
DECL|variable|dib3000mb_bandwidth_8mhz
r_static
id|u16
id|dib3000mb_bandwidth_8mhz
(braket
)braket
op_assign
(brace
l_int|0
comma
l_int|25
comma
l_int|23600
comma
l_int|84
comma
l_int|34976
comma
l_int|422
comma
l_int|43808
comma
l_int|0
comma
l_int|1000
comma
l_int|0
comma
l_int|1010
comma
l_int|1
comma
l_int|45264
)brace
suffix:semicolon
DECL|macro|DIB3000MB_REG_UNK_68
mdefine_line|#define DIB3000MB_REG_UNK_68&t;&t;&t;&t;(    68)
DECL|macro|DIB3000MB_UNK_68
mdefine_line|#define DIB3000MB_UNK_68&t;&t;&t;&t;&t;&t;(     0)
DECL|macro|DIB3000MB_REG_UNK_69
mdefine_line|#define DIB3000MB_REG_UNK_69&t;&t;&t;&t;(    69)
DECL|macro|DIB3000MB_UNK_69
mdefine_line|#define DIB3000MB_UNK_69&t;&t;&t;&t;&t;&t;(     0)
DECL|macro|DIB3000MB_REG_UNK_71
mdefine_line|#define DIB3000MB_REG_UNK_71&t;&t;&t;&t;(    71)
DECL|macro|DIB3000MB_UNK_71
mdefine_line|#define DIB3000MB_UNK_71&t;&t;&t;&t;&t;&t;(     0)
DECL|macro|DIB3000MB_REG_UNK_77
mdefine_line|#define DIB3000MB_REG_UNK_77&t;&t;&t;&t;(    77)
DECL|macro|DIB3000MB_UNK_77
mdefine_line|#define DIB3000MB_UNK_77&t;&t;&t;&t;&t;&t;(     6)
DECL|macro|DIB3000MB_REG_UNK_78
mdefine_line|#define DIB3000MB_REG_UNK_78&t;&t;&t;&t;(    78)
DECL|macro|DIB3000MB_UNK_78
mdefine_line|#define DIB3000MB_UNK_78&t;&t;&t;&t;&t;&t;(0x0080)
multiline_comment|/* isi */
DECL|macro|DIB3000MB_REG_ISI
mdefine_line|#define DIB3000MB_REG_ISI&t;&t;&t;&t;(    79)
DECL|macro|DIB3000MB_ISI_ACTIVATE
mdefine_line|#define DIB3000MB_ISI_ACTIVATE&t;&t;&t;&t;(     0)
DECL|macro|DIB3000MB_ISI_INHIBIT
mdefine_line|#define DIB3000MB_ISI_INHIBIT&t;&t;&t;&t;(     1)
multiline_comment|/* sync impovement */
DECL|macro|DIB3000MB_REG_SYNC_IMPROVEMENT
mdefine_line|#define DIB3000MB_REG_SYNC_IMPROVEMENT&t;(    84)
DECL|macro|DIB3000MB_SYNC_IMPROVE_2K_1_8
mdefine_line|#define DIB3000MB_SYNC_IMPROVE_2K_1_8&t;&t;(     3)
DECL|macro|DIB3000MB_SYNC_IMPROVE_DEFAULT
mdefine_line|#define DIB3000MB_SYNC_IMPROVE_DEFAULT&t;&t;(     0)
multiline_comment|/* phase noise compensation inhibition */
DECL|macro|DIB3000MB_REG_PHASE_NOISE
mdefine_line|#define DIB3000MB_REG_PHASE_NOISE&t;&t;(    87)
DECL|macro|DIB3000MB_PHASE_NOISE_DEFAULT
mdefine_line|#define DIB3000MB_PHASE_NOISE_DEFAULT&t;(     0)
DECL|macro|DIB3000MB_REG_UNK_92
mdefine_line|#define DIB3000MB_REG_UNK_92&t;&t;&t;&t;(    92)
DECL|macro|DIB3000MB_UNK_92
mdefine_line|#define DIB3000MB_UNK_92&t;&t;&t;&t;&t;&t;(0x0080)
DECL|macro|DIB3000MB_REG_UNK_96
mdefine_line|#define DIB3000MB_REG_UNK_96&t;&t;&t;&t;(    96)
DECL|macro|DIB3000MB_UNK_96
mdefine_line|#define DIB3000MB_UNK_96&t;&t;&t;&t;&t;&t;(0x0010)
DECL|macro|DIB3000MB_REG_UNK_97
mdefine_line|#define DIB3000MB_REG_UNK_97&t;&t;&t;&t;(    97)
DECL|macro|DIB3000MB_UNK_97
mdefine_line|#define DIB3000MB_UNK_97&t;&t;&t;&t;&t;&t;(0x0009)
multiline_comment|/* mobile mode ??? */
DECL|macro|DIB3000MB_REG_MOBILE_MODE
mdefine_line|#define DIB3000MB_REG_MOBILE_MODE&t;&t;(   101)
DECL|macro|DIB3000MB_MOBILE_MODE_ON
mdefine_line|#define DIB3000MB_MOBILE_MODE_ON&t;&t;&t;&t;(     1)
DECL|macro|DIB3000MB_MOBILE_MODE_OFF
mdefine_line|#define DIB3000MB_MOBILE_MODE_OFF&t;&t;&t;(     0)
DECL|macro|DIB3000MB_REG_UNK_106
mdefine_line|#define DIB3000MB_REG_UNK_106&t;&t;&t;(   106)
DECL|macro|DIB3000MB_UNK_106
mdefine_line|#define DIB3000MB_UNK_106&t;&t;&t;&t;&t;(0x0080)
DECL|macro|DIB3000MB_REG_UNK_107
mdefine_line|#define DIB3000MB_REG_UNK_107&t;&t;&t;(   107)
DECL|macro|DIB3000MB_UNK_107
mdefine_line|#define DIB3000MB_UNK_107&t;&t;&t;&t;&t;(0x0080)
DECL|macro|DIB3000MB_REG_UNK_108
mdefine_line|#define DIB3000MB_REG_UNK_108&t;&t;&t;(   108)
DECL|macro|DIB3000MB_UNK_108
mdefine_line|#define DIB3000MB_UNK_108&t;&t;&t;&t;&t;(0x0080)
multiline_comment|/* fft */
DECL|macro|DIB3000MB_REG_UNK_121
mdefine_line|#define DIB3000MB_REG_UNK_121&t;&t;&t;(   121)
DECL|macro|DIB3000MB_UNK_121_2K
mdefine_line|#define DIB3000MB_UNK_121_2K&t;&t;&t;&t;(     7)
DECL|macro|DIB3000MB_UNK_121_DEFAULT
mdefine_line|#define DIB3000MB_UNK_121_DEFAULT&t;&t;&t;(     5)
DECL|macro|DIB3000MB_REG_UNK_122
mdefine_line|#define DIB3000MB_REG_UNK_122&t;&t;&t;(   122)
DECL|macro|DIB3000MB_UNK_122
mdefine_line|#define DIB3000MB_UNK_122&t;&t;&t;&t;&t;(  2867)
multiline_comment|/* QAM for mobile mode */
DECL|macro|DIB3000MB_REG_MOBILE_MODE_QAM
mdefine_line|#define DIB3000MB_REG_MOBILE_MODE_QAM&t;(   126)
DECL|macro|DIB3000MB_MOBILE_MODE_QAM_64
mdefine_line|#define DIB3000MB_MOBILE_MODE_QAM_64&t;&t;&t;(     3)
DECL|macro|DIB3000MB_MOBILE_MODE_QAM_QPSK_16
mdefine_line|#define DIB3000MB_MOBILE_MODE_QAM_QPSK_16&t;(     1)
DECL|macro|DIB3000MB_MOBILE_MODE_QAM_OFF
mdefine_line|#define DIB3000MB_MOBILE_MODE_QAM_OFF&t;&t;(     0)
multiline_comment|/*&n; * data diversity when having more than one chip on-board&n; * see also DIB3000MB_OUTPUT_MODE_DATA_DIVERSITY&n; */
DECL|macro|DIB3000MB_REG_DATA_IN_DIVERSITY
mdefine_line|#define DIB3000MB_REG_DATA_IN_DIVERSITY&t;&t;(   127)
DECL|macro|DIB3000MB_DATA_DIVERSITY_IN_OFF
mdefine_line|#define DIB3000MB_DATA_DIVERSITY_IN_OFF&t;&t;&t;(     0)
DECL|macro|DIB3000MB_DATA_DIVERSITY_IN_ON
mdefine_line|#define DIB3000MB_DATA_DIVERSITY_IN_ON&t;&t;&t;(     2)
multiline_comment|/* vit hrch */
DECL|macro|DIB3000MB_REG_VIT_HRCH
mdefine_line|#define DIB3000MB_REG_VIT_HRCH&t;&t;&t;(   128)
DECL|macro|DIB3000MB_VIT_HRCH_ON
mdefine_line|#define DIB3000MB_VIT_HRCH_ON&t;&t;&t;&t;(     1)
DECL|macro|DIB3000MB_VIT_HRCH_OFF
mdefine_line|#define DIB3000MB_VIT_HRCH_OFF&t;&t;&t;&t;(     0)
multiline_comment|/* vit code rate */
DECL|macro|DIB3000MB_REG_VIT_CODE_RATE
mdefine_line|#define DIB3000MB_REG_VIT_CODE_RATE&t;&t;(   129)
multiline_comment|/* forward error correction code rates */
DECL|macro|DIB3000MB_FEC_1_2
mdefine_line|#define DIB3000MB_FEC_1_2&t;&t;&t;&t;&t;(     1)
DECL|macro|DIB3000MB_FEC_2_3
mdefine_line|#define DIB3000MB_FEC_2_3&t;&t;&t;&t;&t;(     2)
DECL|macro|DIB3000MB_FEC_3_4
mdefine_line|#define DIB3000MB_FEC_3_4&t;&t;&t;&t;&t;(     3)
DECL|macro|DIB3000MB_FEC_5_6
mdefine_line|#define DIB3000MB_FEC_5_6&t;&t;&t;&t;&t;(     5)
DECL|macro|DIB3000MB_FEC_7_8
mdefine_line|#define DIB3000MB_FEC_7_8&t;&t;&t;&t;&t;(     7)
multiline_comment|/* vit select hp */
DECL|macro|DIB3000MB_REG_VIT_HP
mdefine_line|#define DIB3000MB_REG_VIT_HP&t;&t;&t;(   130)
DECL|macro|DIB3000MB_VIT_LP
mdefine_line|#define DIB3000MB_VIT_LP&t;&t;&t;&t;&t;(     0)
DECL|macro|DIB3000MB_VIT_HP
mdefine_line|#define DIB3000MB_VIT_HP&t;&t;&t;&t;&t;(     1)
multiline_comment|/* time frame for Bit-Error-Rate calculation */
DECL|macro|DIB3000MB_REG_BERLEN
mdefine_line|#define DIB3000MB_REG_BERLEN&t;&t;&t;(   135)
DECL|macro|DIB3000MB_BERLEN_LONG
mdefine_line|#define DIB3000MB_BERLEN_LONG&t;&t;&t;&t;(     0)
DECL|macro|DIB3000MB_BERLEN_DEFAULT
mdefine_line|#define DIB3000MB_BERLEN_DEFAULT&t;&t;&t;(     1)
DECL|macro|DIB3000MB_BERLEN_MEDIUM
mdefine_line|#define DIB3000MB_BERLEN_MEDIUM&t;&t;&t;&t;(     2)
DECL|macro|DIB3000MB_BERLEN_SHORT
mdefine_line|#define DIB3000MB_BERLEN_SHORT&t;&t;&t;&t;(     3)
multiline_comment|/* 142 - 152 FIFO parameters&n; * which is what ?&n; */
DECL|macro|DIB3000MB_REG_FIFO_142
mdefine_line|#define DIB3000MB_REG_FIFO_142&t;&t;&t;(   142)
DECL|macro|DIB3000MB_FIFO_142
mdefine_line|#define DIB3000MB_FIFO_142&t;&t;&t;&t;&t;(     0)
multiline_comment|/* MPEG2 TS output mode */
DECL|macro|DIB3000MB_REG_MPEG2_OUT_MODE
mdefine_line|#define DIB3000MB_REG_MPEG2_OUT_MODE&t;(   143)
DECL|macro|DIB3000MB_MPEG2_OUT_MODE_204
mdefine_line|#define DIB3000MB_MPEG2_OUT_MODE_204&t;&t;(     0)
DECL|macro|DIB3000MB_MPEG2_OUT_MODE_188
mdefine_line|#define DIB3000MB_MPEG2_OUT_MODE_188&t;&t;(     1)
DECL|macro|DIB3000MB_REG_FIFO_144
mdefine_line|#define DIB3000MB_REG_FIFO_144&t;&t;&t;(   144)
DECL|macro|DIB3000MB_FIFO_144
mdefine_line|#define DIB3000MB_FIFO_144&t;&t;&t;&t;&t;(     1)
DECL|macro|DIB3000MB_REG_FIFO
mdefine_line|#define DIB3000MB_REG_FIFO&t;&t;&t;&t;(   145)
DECL|macro|DIB3000MB_FIFO_INHIBIT
mdefine_line|#define DIB3000MB_FIFO_INHIBIT&t;&t;&t;&t;(     1)
DECL|macro|DIB3000MB_FIFO_ACTIVATE
mdefine_line|#define DIB3000MB_FIFO_ACTIVATE&t;&t;&t;&t;(     0)
DECL|macro|DIB3000MB_REG_FIFO_146
mdefine_line|#define DIB3000MB_REG_FIFO_146&t;&t;&t;(   146)
DECL|macro|DIB3000MB_FIFO_146
mdefine_line|#define DIB3000MB_FIFO_146&t;&t;&t;&t;&t;(     3)
DECL|macro|DIB3000MB_REG_FIFO_147
mdefine_line|#define DIB3000MB_REG_FIFO_147&t;&t;&t;(   147)
DECL|macro|DIB3000MB_FIFO_147
mdefine_line|#define DIB3000MB_FIFO_147&t;&t;&t;&t;&t;(0x0100)
multiline_comment|/*&n; * pidfilter&n; * it is not a hardware pidfilter but a filter which drops all pids&n; * except the ones set. Necessary because of the limited USB1.1 bandwidth.&n; */
DECL|macro|DIB3000MB_REG_FILTER_PID_0
mdefine_line|#define DIB3000MB_REG_FILTER_PID_0&t;&t;(   153)
DECL|macro|DIB3000MB_REG_FILTER_PID_1
mdefine_line|#define DIB3000MB_REG_FILTER_PID_1&t;&t;(   154)
DECL|macro|DIB3000MB_REG_FILTER_PID_2
mdefine_line|#define DIB3000MB_REG_FILTER_PID_2&t;&t;(   155)
DECL|macro|DIB3000MB_REG_FILTER_PID_3
mdefine_line|#define DIB3000MB_REG_FILTER_PID_3&t;&t;(   156)
DECL|macro|DIB3000MB_REG_FILTER_PID_4
mdefine_line|#define DIB3000MB_REG_FILTER_PID_4&t;&t;(   157)
DECL|macro|DIB3000MB_REG_FILTER_PID_5
mdefine_line|#define DIB3000MB_REG_FILTER_PID_5&t;&t;(   158)
DECL|macro|DIB3000MB_REG_FILTER_PID_6
mdefine_line|#define DIB3000MB_REG_FILTER_PID_6&t;&t;(   159)
DECL|macro|DIB3000MB_REG_FILTER_PID_7
mdefine_line|#define DIB3000MB_REG_FILTER_PID_7&t;&t;(   160)
DECL|macro|DIB3000MB_REG_FILTER_PID_8
mdefine_line|#define DIB3000MB_REG_FILTER_PID_8&t;&t;(   161)
DECL|macro|DIB3000MB_REG_FILTER_PID_9
mdefine_line|#define DIB3000MB_REG_FILTER_PID_9&t;&t;(   162)
DECL|macro|DIB3000MB_REG_FILTER_PID_10
mdefine_line|#define DIB3000MB_REG_FILTER_PID_10&t;&t;(   163)
DECL|macro|DIB3000MB_REG_FILTER_PID_11
mdefine_line|#define DIB3000MB_REG_FILTER_PID_11&t;&t;(   164)
DECL|macro|DIB3000MB_REG_FILTER_PID_12
mdefine_line|#define DIB3000MB_REG_FILTER_PID_12&t;&t;(   165)
DECL|macro|DIB3000MB_REG_FILTER_PID_13
mdefine_line|#define DIB3000MB_REG_FILTER_PID_13&t;&t;(   166)
DECL|macro|DIB3000MB_REG_FILTER_PID_14
mdefine_line|#define DIB3000MB_REG_FILTER_PID_14&t;&t;(   167)
DECL|macro|DIB3000MB_REG_FILTER_PID_15
mdefine_line|#define DIB3000MB_REG_FILTER_PID_15&t;&t;(   168)
DECL|macro|DIB3000MB_ACTIVATE_FILTERING
mdefine_line|#define DIB3000MB_ACTIVATE_FILTERING&t;&t;&t;(0x2000)
multiline_comment|/*&n; * output mode&n; * USB devices have to use &squot;slave&squot;-mode&n; * see also DIB3000MB_REG_ELECT_OUT_MODE&n; */
DECL|macro|DIB3000MB_REG_OUTPUT_MODE
mdefine_line|#define DIB3000MB_REG_OUTPUT_MODE&t;&t;(   169)
DECL|macro|DIB3000MB_OUTPUT_MODE_GATED_CLK
mdefine_line|#define DIB3000MB_OUTPUT_MODE_GATED_CLK&t;&t;(     0)
DECL|macro|DIB3000MB_OUTPUT_MODE_CONT_CLK
mdefine_line|#define DIB3000MB_OUTPUT_MODE_CONT_CLK&t;&t;(     1)
DECL|macro|DIB3000MB_OUTPUT_MODE_SERIAL
mdefine_line|#define DIB3000MB_OUTPUT_MODE_SERIAL&t;&t;(     2)
DECL|macro|DIB3000MB_OUTPUT_MODE_DATA_DIVERSITY
mdefine_line|#define DIB3000MB_OUTPUT_MODE_DATA_DIVERSITY&t;(     5)
DECL|macro|DIB3000MB_OUTPUT_MODE_SLAVE
mdefine_line|#define DIB3000MB_OUTPUT_MODE_SLAVE&t;&t;&t;(     6)
multiline_comment|/* irq event mask */
DECL|macro|DIB3000MB_REG_IRQ_EVENT_MASK
mdefine_line|#define DIB3000MB_REG_IRQ_EVENT_MASK&t;&t;(   170)
DECL|macro|DIB3000MB_IRQ_EVENT_MASK
mdefine_line|#define DIB3000MB_IRQ_EVENT_MASK&t;&t;&t;&t;(     0)
multiline_comment|/* filter coefficients */
DECL|macro|DIB3000MB_REG_FILTER_COEF_171
mdefine_line|#define DIB3000MB_REG_FILTER_COEF_171&t;(   171)
DECL|macro|DIB3000MB_REG_FILTER_COEF_172
mdefine_line|#define DIB3000MB_REG_FILTER_COEF_172&t;(   172)
DECL|macro|DIB3000MB_REG_FILTER_COEF_173
mdefine_line|#define DIB3000MB_REG_FILTER_COEF_173&t;(   173)
DECL|macro|DIB3000MB_REG_FILTER_COEF_174
mdefine_line|#define DIB3000MB_REG_FILTER_COEF_174&t;(   174)
DECL|macro|DIB3000MB_REG_FILTER_COEF_175
mdefine_line|#define DIB3000MB_REG_FILTER_COEF_175&t;(   175)
DECL|macro|DIB3000MB_REG_FILTER_COEF_176
mdefine_line|#define DIB3000MB_REG_FILTER_COEF_176&t;(   176)
DECL|macro|DIB3000MB_REG_FILTER_COEF_177
mdefine_line|#define DIB3000MB_REG_FILTER_COEF_177&t;(   177)
DECL|macro|DIB3000MB_REG_FILTER_COEF_178
mdefine_line|#define DIB3000MB_REG_FILTER_COEF_178&t;(   178)
DECL|macro|DIB3000MB_REG_FILTER_COEF_179
mdefine_line|#define DIB3000MB_REG_FILTER_COEF_179&t;(   179)
DECL|macro|DIB3000MB_REG_FILTER_COEF_180
mdefine_line|#define DIB3000MB_REG_FILTER_COEF_180&t;(   180)
DECL|macro|DIB3000MB_REG_FILTER_COEF_181
mdefine_line|#define DIB3000MB_REG_FILTER_COEF_181&t;(   181)
DECL|macro|DIB3000MB_REG_FILTER_COEF_182
mdefine_line|#define DIB3000MB_REG_FILTER_COEF_182&t;(   182)
DECL|macro|DIB3000MB_REG_FILTER_COEF_183
mdefine_line|#define DIB3000MB_REG_FILTER_COEF_183&t;(   183)
DECL|macro|DIB3000MB_REG_FILTER_COEF_184
mdefine_line|#define DIB3000MB_REG_FILTER_COEF_184&t;(   184)
DECL|macro|DIB3000MB_REG_FILTER_COEF_185
mdefine_line|#define DIB3000MB_REG_FILTER_COEF_185&t;(   185)
DECL|macro|DIB3000MB_REG_FILTER_COEF_186
mdefine_line|#define DIB3000MB_REG_FILTER_COEF_186&t;(   186)
DECL|macro|DIB3000MB_REG_FILTER_COEF_187
mdefine_line|#define DIB3000MB_REG_FILTER_COEF_187&t;(   187)
DECL|macro|DIB3000MB_REG_FILTER_COEF_188
mdefine_line|#define DIB3000MB_REG_FILTER_COEF_188&t;(   188)
DECL|macro|DIB3000MB_REG_FILTER_COEF_189
mdefine_line|#define DIB3000MB_REG_FILTER_COEF_189&t;(   189)
DECL|macro|DIB3000MB_REG_FILTER_COEF_190
mdefine_line|#define DIB3000MB_REG_FILTER_COEF_190&t;(   190)
DECL|macro|DIB3000MB_REG_FILTER_COEF_191
mdefine_line|#define DIB3000MB_REG_FILTER_COEF_191&t;(   191)
DECL|macro|DIB3000MB_REG_FILTER_COEF_192
mdefine_line|#define DIB3000MB_REG_FILTER_COEF_192&t;(   192)
DECL|macro|DIB3000MB_REG_FILTER_COEF_193
mdefine_line|#define DIB3000MB_REG_FILTER_COEF_193&t;(   193)
DECL|macro|DIB3000MB_REG_FILTER_COEF_194
mdefine_line|#define DIB3000MB_REG_FILTER_COEF_194&t;(   194)
DECL|variable|dib3000mb_reg_filter_coeffs
r_static
id|u16
id|dib3000mb_reg_filter_coeffs
(braket
)braket
op_assign
(brace
id|DIB3000MB_REG_FILTER_COEF_171
comma
id|DIB3000MB_REG_FILTER_COEF_172
comma
id|DIB3000MB_REG_FILTER_COEF_173
comma
id|DIB3000MB_REG_FILTER_COEF_174
comma
id|DIB3000MB_REG_FILTER_COEF_175
comma
id|DIB3000MB_REG_FILTER_COEF_176
comma
id|DIB3000MB_REG_FILTER_COEF_177
comma
id|DIB3000MB_REG_FILTER_COEF_178
comma
id|DIB3000MB_REG_FILTER_COEF_179
comma
id|DIB3000MB_REG_FILTER_COEF_180
comma
id|DIB3000MB_REG_FILTER_COEF_181
comma
id|DIB3000MB_REG_FILTER_COEF_182
comma
id|DIB3000MB_REG_FILTER_COEF_183
comma
id|DIB3000MB_REG_FILTER_COEF_184
comma
id|DIB3000MB_REG_FILTER_COEF_185
comma
id|DIB3000MB_REG_FILTER_COEF_186
comma
id|DIB3000MB_REG_FILTER_COEF_188
comma
id|DIB3000MB_REG_FILTER_COEF_189
comma
id|DIB3000MB_REG_FILTER_COEF_190
comma
id|DIB3000MB_REG_FILTER_COEF_191
comma
id|DIB3000MB_REG_FILTER_COEF_192
comma
id|DIB3000MB_REG_FILTER_COEF_194
)brace
suffix:semicolon
DECL|variable|dib3000mb_filter_coeffs
r_static
id|u16
id|dib3000mb_filter_coeffs
(braket
)braket
op_assign
(brace
l_int|226
comma
l_int|160
comma
l_int|29
comma
l_int|979
comma
l_int|998
comma
l_int|19
comma
l_int|22
comma
l_int|1019
comma
l_int|1006
comma
l_int|1022
comma
l_int|12
comma
l_int|6
comma
l_int|1017
comma
l_int|1017
comma
l_int|3
comma
l_int|6
comma
l_int|1019
comma
l_int|1021
comma
l_int|2
comma
l_int|3
comma
l_int|1
comma
l_int|0
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * mobile algorithm (when you are moving with your device)&n; * but not faster than 90 km/h&n; */
DECL|macro|DIB3000MB_REG_MOBILE_ALGO
mdefine_line|#define DIB3000MB_REG_MOBILE_ALGO&t;&t;(   195)
DECL|macro|DIB3000MB_MOBILE_ALGO_ON
mdefine_line|#define DIB3000MB_MOBILE_ALGO_ON&t;&t;&t;(     0)
DECL|macro|DIB3000MB_MOBILE_ALGO_OFF
mdefine_line|#define DIB3000MB_MOBILE_ALGO_OFF&t;&t;&t;(     1)
multiline_comment|/* multiple demodulators algorithm */
DECL|macro|DIB3000MB_REG_MULTI_DEMOD_MSB
mdefine_line|#define DIB3000MB_REG_MULTI_DEMOD_MSB&t;(   206)
DECL|macro|DIB3000MB_REG_MULTI_DEMOD_LSB
mdefine_line|#define DIB3000MB_REG_MULTI_DEMOD_LSB&t;(   207)
multiline_comment|/* terminator, no more demods */
DECL|macro|DIB3000MB_MULTI_DEMOD_MSB
mdefine_line|#define DIB3000MB_MULTI_DEMOD_MSB&t;&t;&t;( 32767)
DECL|macro|DIB3000MB_MULTI_DEMOD_LSB
mdefine_line|#define DIB3000MB_MULTI_DEMOD_LSB&t;&t;&t;(  4095)
multiline_comment|/* bring the device into a known  */
DECL|macro|DIB3000MB_REG_RESET_DEVICE
mdefine_line|#define DIB3000MB_REG_RESET_DEVICE&t;&t;(  1024)
DECL|macro|DIB3000MB_RESET_DEVICE
mdefine_line|#define DIB3000MB_RESET_DEVICE&t;&t;&t;&t;(0x812c)
DECL|macro|DIB3000MB_RESET_DEVICE_RST
mdefine_line|#define DIB3000MB_RESET_DEVICE_RST&t;&t;&t;(     0)
multiline_comment|/* identification registers, manufactor an the device */
DECL|macro|DIB3000MB_REG_MANUFACTOR_ID
mdefine_line|#define DIB3000MB_REG_MANUFACTOR_ID&t;&t;(  1025)
DECL|macro|DIB3000MB_MANUFACTOR_ID_DIBCOM
mdefine_line|#define DIB3000MB_MANUFACTOR_ID_DIBCOM&t;&t;(0x01B3)
DECL|macro|DIB3000MB_REG_DEVICE_ID
mdefine_line|#define DIB3000MB_REG_DEVICE_ID&t;&t;&t;(  1026)
DECL|macro|DIB3000MB_DEVICE_ID
mdefine_line|#define DIB3000MB_DEVICE_ID&t;&t;&t;&t;&t;(0x3000)
multiline_comment|/* hardware clock configuration */
DECL|macro|DIB3000MB_REG_CLOCK
mdefine_line|#define DIB3000MB_REG_CLOCK&t;&t;&t;&t;(  1027)
DECL|macro|DIB3000MB_CLOCK_DEFAULT
mdefine_line|#define DIB3000MB_CLOCK_DEFAULT&t;&t;&t;&t;(0x9000)
DECL|macro|DIB3000MB_CLOCK_DIVERSITY
mdefine_line|#define DIB3000MB_CLOCK_DIVERSITY&t;&t;&t;(0x92b0)
multiline_comment|/* power down config */
DECL|macro|DIB3000MB_REG_POWER_CONTROL
mdefine_line|#define DIB3000MB_REG_POWER_CONTROL&t;&t;(  1028)
DECL|macro|DIB3000MB_POWER_DOWN
mdefine_line|#define DIB3000MB_POWER_DOWN&t;&t;&t;&t;(     1)
DECL|macro|DIB3000MB_POWER_UP
mdefine_line|#define DIB3000MB_POWER_UP&t;&t;&t;&t;&t;(     0)
multiline_comment|/* electrical output mode */
DECL|macro|DIB3000MB_REG_ELECT_OUT_MODE
mdefine_line|#define DIB3000MB_REG_ELECT_OUT_MODE&t;(  1029)
DECL|macro|DIB3000MB_ELECT_OUT_MODE_OFF
mdefine_line|#define DIB3000MB_ELECT_OUT_MODE_OFF&t;&t;(     0)
DECL|macro|DIB3000MB_ELECT_OUT_MODE_ON
mdefine_line|#define DIB3000MB_ELECT_OUT_MODE_ON&t;&t;&t;(     1)
multiline_comment|/* set the tuner i2c address */
DECL|macro|DIB3000MB_REG_TUNER
mdefine_line|#define DIB3000MB_REG_TUNER&t;&t;&t;&t;(  1089)
DECL|macro|DIB3000MB_TUNER_ADDR_DEFAULT
mdefine_line|#define DIB3000MB_TUNER_ADDR_DEFAULT&t;&t;(   194)
DECL|macro|DIB3000MB_ACTIVATE_TUNER_XFER
mdefine_line|#define DIB3000MB_ACTIVATE_TUNER_XFER(a)&t;(0xffff &amp; (a &lt;&lt; 7))
DECL|macro|DIB3000MB_DEACTIVATE_TUNER_XFER
mdefine_line|#define DIB3000MB_DEACTIVATE_TUNER_XFER(a)&t;(0xffff &amp; ((a &lt;&lt; 7) + 0x80))
multiline_comment|/* monitoring registers (read only) */
multiline_comment|/* agc loop locked (size: 1) */
DECL|macro|DIB3000MB_REG_AGC_LOCK
mdefine_line|#define DIB3000MB_REG_AGC_LOCK&t;&t;&t;(   324)
multiline_comment|/* agc power (size: 16) */
DECL|macro|DIB3000MB_REG_AGC_POWER
mdefine_line|#define DIB3000MB_REG_AGC_POWER&t;&t;&t;(   325)
multiline_comment|/* agc1 value (16) */
DECL|macro|DIB3000MB_REG_AGC1_VALUE
mdefine_line|#define DIB3000MB_REG_AGC1_VALUE&t;&t;(   326)
multiline_comment|/* agc2 value (16) */
DECL|macro|DIB3000MB_REG_AGC2_VALUE
mdefine_line|#define DIB3000MB_REG_AGC2_VALUE&t;&t;(   327)
multiline_comment|/* total RF power (16), can be used for signal strength */
DECL|macro|DIB3000MB_REG_RF_POWER
mdefine_line|#define DIB3000MB_REG_RF_POWER&t;&t;&t;(   328)
multiline_comment|/* dds_frequency with offset (24) */
DECL|macro|DIB3000MB_REG_DDS_VALUE_MSB
mdefine_line|#define DIB3000MB_REG_DDS_VALUE_MSB&t;&t;(   339)
DECL|macro|DIB3000MB_REG_DDS_VALUE_LSB
mdefine_line|#define DIB3000MB_REG_DDS_VALUE_LSB&t;&t;(   340)
multiline_comment|/* timing offset signed (24) */
DECL|macro|DIB3000MB_REG_TIMING_OFFSET_MSB
mdefine_line|#define DIB3000MB_REG_TIMING_OFFSET_MSB&t;(   341)
DECL|macro|DIB3000MB_REG_TIMING_OFFSET_LSB
mdefine_line|#define DIB3000MB_REG_TIMING_OFFSET_LSB&t;(   342)
multiline_comment|/* fft start position (13) */
DECL|macro|DIB3000MB_REG_FFT_WINDOW_POS
mdefine_line|#define DIB3000MB_REG_FFT_WINDOW_POS&t;(   353)
multiline_comment|/* carriers locked (1) */
DECL|macro|DIB3000MB_REG_CARRIER_LOCK
mdefine_line|#define DIB3000MB_REG_CARRIER_LOCK&t;&t;(   355)
multiline_comment|/* noise power (24) */
DECL|macro|DIB3000MB_REG_NOISE_POWER_MSB
mdefine_line|#define DIB3000MB_REG_NOISE_POWER_MSB&t;(   372)
DECL|macro|DIB3000MB_REG_NOISE_POWER_LSB
mdefine_line|#define DIB3000MB_REG_NOISE_POWER_LSB&t;(   373)
DECL|macro|DIB3000MB_REG_MOBILE_NOISE_MSB
mdefine_line|#define DIB3000MB_REG_MOBILE_NOISE_MSB&t;(   374)
DECL|macro|DIB3000MB_REG_MOBILE_NOISE_LSB
mdefine_line|#define DIB3000MB_REG_MOBILE_NOISE_LSB&t;(   375)
multiline_comment|/*&n; * signal power (16), this and the above can be&n; * used to calculate the signal/noise - ratio&n; */
DECL|macro|DIB3000MB_REG_SIGNAL_POWER
mdefine_line|#define DIB3000MB_REG_SIGNAL_POWER&t;&t;(   380)
multiline_comment|/* mer (24) */
DECL|macro|DIB3000MB_REG_MER_MSB
mdefine_line|#define DIB3000MB_REG_MER_MSB&t;&t;&t;(   381)
DECL|macro|DIB3000MB_REG_MER_LSB
mdefine_line|#define DIB3000MB_REG_MER_LSB&t;&t;&t;(   382)
multiline_comment|/*&n; * Transmission Parameter Signalling (TPS)&n; * the following registers can be used to get TPS-information.&n; * The values are according to the DVB-T standard.&n; */
multiline_comment|/* TPS locked (1) */
DECL|macro|DIB3000MB_REG_TPS_LOCK
mdefine_line|#define DIB3000MB_REG_TPS_LOCK&t;&t;&t;(   394)
multiline_comment|/* QAM from TPS (2) (values according to DIB3000MB_REG_QAM) */
DECL|macro|DIB3000MB_REG_TPS_QAM
mdefine_line|#define DIB3000MB_REG_TPS_QAM&t;&t;&t;(   398)
multiline_comment|/* hierarchy from TPS (1) */
DECL|macro|DIB3000MB_REG_TPS_HRCH
mdefine_line|#define DIB3000MB_REG_TPS_HRCH&t;&t;&t;(   399)
multiline_comment|/* alpha from TPS (3) (values according to DIB3000MB_REG_VIT_ALPHA) */
DECL|macro|DIB3000MB_REG_TPS_VIT_ALPHA
mdefine_line|#define DIB3000MB_REG_TPS_VIT_ALPHA&t;&t;(   400)
multiline_comment|/* code rate high priority from TPS (3) (values according to DIB3000MB_FEC_*) */
DECL|macro|DIB3000MB_REG_TPS_CODE_RATE_HP
mdefine_line|#define DIB3000MB_REG_TPS_CODE_RATE_HP&t;(   401)
multiline_comment|/* code rate low priority from TPS (3) if DIB3000MB_REG_TPS_VIT_ALPHA */
DECL|macro|DIB3000MB_REG_TPS_CODE_RATE_LP
mdefine_line|#define DIB3000MB_REG_TPS_CODE_RATE_LP&t;(   402)
multiline_comment|/* guard time from TPS (2) (values according to DIB3000MB_REG_GUARD_TIME */
DECL|macro|DIB3000MB_REG_TPS_GUARD_TIME
mdefine_line|#define DIB3000MB_REG_TPS_GUARD_TIME&t;(   403)
multiline_comment|/* fft size from TPS (2) (values according to DIB3000MB_REG_FFT) */
DECL|macro|DIB3000MB_REG_TPS_FFT
mdefine_line|#define DIB3000MB_REG_TPS_FFT&t;&t;&t;(   404)
multiline_comment|/* cell id from TPS (16) */
DECL|macro|DIB3000MB_REG_TPS_CELL_ID
mdefine_line|#define DIB3000MB_REG_TPS_CELL_ID&t;&t;(   406)
multiline_comment|/* TPS (68) */
DECL|macro|DIB3000MB_REG_TPS_1
mdefine_line|#define DIB3000MB_REG_TPS_1&t;&t;&t;&t;(   408)
DECL|macro|DIB3000MB_REG_TPS_2
mdefine_line|#define DIB3000MB_REG_TPS_2&t;&t;&t;&t;(   409)
DECL|macro|DIB3000MB_REG_TPS_3
mdefine_line|#define DIB3000MB_REG_TPS_3&t;&t;&t;&t;(   410)
DECL|macro|DIB3000MB_REG_TPS_4
mdefine_line|#define DIB3000MB_REG_TPS_4&t;&t;&t;&t;(   411)
DECL|macro|DIB3000MB_REG_TPS_5
mdefine_line|#define DIB3000MB_REG_TPS_5&t;&t;&t;&t;(   412)
multiline_comment|/* bit error rate (before RS correction) (21) */
DECL|macro|DIB3000MB_REG_BER_MSB
mdefine_line|#define DIB3000MB_REG_BER_MSB&t;&t;&t;(   414)
DECL|macro|DIB3000MB_REG_BER_LSB
mdefine_line|#define DIB3000MB_REG_BER_LSB&t;&t;&t;(   415)
multiline_comment|/* packet error rate (uncorrected TS packets) (16) */
DECL|macro|DIB3000MB_REG_PACKET_ERROR_RATE
mdefine_line|#define DIB3000MB_REG_PACKET_ERROR_RATE&t;(   417)
multiline_comment|/* uncorrected packet count (16) */
DECL|macro|DIB3000MB_REG_UNC
mdefine_line|#define DIB3000MB_REG_UNC&t;&t;&t;&t;(   420)
multiline_comment|/* viterbi locked (1) */
DECL|macro|DIB3000MB_REG_VIT_LCK
mdefine_line|#define DIB3000MB_REG_VIT_LCK&t;&t;&t;(   421)
multiline_comment|/* viterbi inidcator (16) */
DECL|macro|DIB3000MB_REG_VIT_INDICATOR
mdefine_line|#define DIB3000MB_REG_VIT_INDICATOR&t;&t;(   422)
multiline_comment|/* transport stream sync lock (1) */
DECL|macro|DIB3000MB_REG_TS_SYNC_LOCK
mdefine_line|#define DIB3000MB_REG_TS_SYNC_LOCK&t;&t;(   423)
multiline_comment|/* transport stream RS lock (1) */
DECL|macro|DIB3000MB_REG_TS_RS_LOCK
mdefine_line|#define DIB3000MB_REG_TS_RS_LOCK&t;&t;(   424)
multiline_comment|/* lock mask 0 value (1) */
DECL|macro|DIB3000MB_REG_LOCK0_VALUE
mdefine_line|#define DIB3000MB_REG_LOCK0_VALUE&t;&t;(   425)
multiline_comment|/* lock mask 1 value (1) */
DECL|macro|DIB3000MB_REG_LOCK1_VALUE
mdefine_line|#define DIB3000MB_REG_LOCK1_VALUE&t;&t;(   426)
multiline_comment|/* lock mask 2 value (1) */
DECL|macro|DIB3000MB_REG_LOCK2_VALUE
mdefine_line|#define DIB3000MB_REG_LOCK2_VALUE&t;&t;(   427)
multiline_comment|/* interrupt pending for auto search */
DECL|macro|DIB3000MB_REG_AS_IRQ_PENDING
mdefine_line|#define DIB3000MB_REG_AS_IRQ_PENDING&t;(   434)
macro_line|#endif
eof
