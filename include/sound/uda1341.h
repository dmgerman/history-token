multiline_comment|/*&n; *  linux/include/linux/l3/uda1341.h&n; *&n; * Philips UDA1341 mixer device driver for ALSA&n; *&n; * Copyright (c) 2002 Tomas Kasparek &lt;tomas.kasparek@seznam.cz&gt;&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License.&n; *&n; * History:&n; *&n; * 2002-03-13 Tomas Kasparek Initial release - based on uda1341.h from OSS&n; * 2002-03-30 Tomas Kasparek Proc filesystem support, complete mixer and DSP&n; *                           features support&n; */
multiline_comment|/* $Id: uda1341.h,v 1.2 2002/04/17 07:53:22 perex Exp $ */
DECL|macro|UDA1341_ALSA_NAME
mdefine_line|#define UDA1341_ALSA_NAME &quot;snd-uda1341&quot;
multiline_comment|/*&n; * UDA1341 L3 address and command types&n; */
DECL|macro|UDA1341_L3ADDR
mdefine_line|#define UDA1341_L3ADDR&t;&t;5
DECL|macro|UDA1341_DATA0
mdefine_line|#define UDA1341_DATA0&t;&t;(UDA1341_L3ADDR &lt;&lt; 2 | 0)
DECL|macro|UDA1341_DATA1
mdefine_line|#define UDA1341_DATA1&t;&t;(UDA1341_L3ADDR &lt;&lt; 2 | 1)
DECL|macro|UDA1341_STATUS
mdefine_line|#define UDA1341_STATUS&t;&t;(UDA1341_L3ADDR &lt;&lt; 2 | 2)
DECL|enum|uda1341_onoff
r_enum
id|uda1341_onoff
(brace
DECL|enumerator|OFF
id|OFF
op_assign
l_int|0
comma
DECL|enumerator|ON
id|ON
comma
)brace
suffix:semicolon
DECL|variable|onoff_names
r_const
r_char
op_star
id|onoff_names
(braket
)braket
op_assign
(brace
l_string|&quot;Off&quot;
comma
l_string|&quot;On&quot;
comma
)brace
suffix:semicolon
DECL|enum|uda1341_format
r_enum
id|uda1341_format
(brace
DECL|enumerator|I2S
id|I2S
op_assign
l_int|0
comma
DECL|enumerator|LSB16
id|LSB16
comma
DECL|enumerator|LSB18
id|LSB18
comma
DECL|enumerator|LSB20
id|LSB20
comma
DECL|enumerator|MSB
id|MSB
comma
DECL|enumerator|LSB16MSB
id|LSB16MSB
comma
DECL|enumerator|LSB18MSB
id|LSB18MSB
comma
DECL|enumerator|LSB20MSB
id|LSB20MSB
comma
)brace
suffix:semicolon
DECL|variable|format_names
r_const
r_char
op_star
id|format_names
(braket
)braket
op_assign
(brace
l_string|&quot;I2S-bus&quot;
comma
l_string|&quot;LSB 16bits&quot;
comma
l_string|&quot;LSB 18bits&quot;
comma
l_string|&quot;LSB 20bits&quot;
comma
l_string|&quot;MSB&quot;
comma
l_string|&quot;in LSB 16bits/out MSB&quot;
comma
l_string|&quot;in LSB 18bits/out MSB&quot;
comma
l_string|&quot;in LSB 20bits/out MSB&quot;
comma
)brace
suffix:semicolon
DECL|enum|uda1341_fs
r_enum
id|uda1341_fs
(brace
DECL|enumerator|F512
id|F512
op_assign
l_int|0
comma
DECL|enumerator|F384
id|F384
comma
DECL|enumerator|F256
id|F256
comma
DECL|enumerator|Funused
id|Funused
comma
)brace
suffix:semicolon
DECL|variable|fs_names
r_const
r_char
op_star
id|fs_names
(braket
)braket
op_assign
(brace
l_string|&quot;512*fs&quot;
comma
l_string|&quot;384*fs&quot;
comma
l_string|&quot;256*fs&quot;
comma
l_string|&quot;Unused - bad value!&quot;
comma
)brace
suffix:semicolon
DECL|enum|uda1341_peak
r_enum
id|uda1341_peak
(brace
DECL|enumerator|BEFORE
id|BEFORE
op_assign
l_int|0
comma
DECL|enumerator|AFTER
id|AFTER
comma
)brace
suffix:semicolon
DECL|variable|peak_names
r_const
r_char
op_star
id|peak_names
(braket
)braket
op_assign
(brace
l_string|&quot;before&quot;
comma
l_string|&quot;after&quot;
comma
)brace
suffix:semicolon
DECL|enum|uda1341_filter
r_enum
id|uda1341_filter
(brace
DECL|enumerator|FLAT
id|FLAT
op_assign
l_int|0
comma
DECL|enumerator|MIN
id|MIN
comma
DECL|enumerator|MIN2
id|MIN2
comma
DECL|enumerator|MAX
id|MAX
comma
)brace
suffix:semicolon
DECL|variable|filter_names
r_const
r_char
op_star
id|filter_names
(braket
)braket
op_assign
(brace
l_string|&quot;flat&quot;
comma
l_string|&quot;min&quot;
comma
l_string|&quot;min&quot;
comma
l_string|&quot;max&quot;
comma
)brace
suffix:semicolon
DECL|variable|bass_values
r_const
r_char
op_star
id|bass_values
(braket
)braket
(braket
l_int|16
)braket
op_assign
(brace
(brace
l_string|&quot;0 dB&quot;
comma
l_string|&quot;0 dB&quot;
comma
l_string|&quot;0 dB&quot;
comma
l_string|&quot;0 dB&quot;
comma
l_string|&quot;0 dB&quot;
comma
l_string|&quot;0 dB&quot;
comma
l_string|&quot;0 dB&quot;
comma
l_string|&quot;0 dB&quot;
comma
l_string|&quot;0 dB&quot;
comma
l_string|&quot;0 dB&quot;
comma
l_string|&quot;0 dB&quot;
comma
l_string|&quot;0 dB&quot;
comma
l_string|&quot;0 dB&quot;
comma
l_string|&quot;0 dB&quot;
comma
l_string|&quot;0 dB&quot;
comma
l_string|&quot;undefined&quot;
comma
)brace
comma
singleline_comment|//flat
(brace
l_string|&quot;0 dB&quot;
comma
l_string|&quot;2 dB&quot;
comma
l_string|&quot;4 dB&quot;
comma
l_string|&quot;6 dB&quot;
comma
l_string|&quot;8 dB&quot;
comma
l_string|&quot;10 dB&quot;
comma
l_string|&quot;12 dB&quot;
comma
l_string|&quot;14 dB&quot;
comma
l_string|&quot;16 dB&quot;
comma
l_string|&quot;18 dB&quot;
comma
l_string|&quot;18 dB&quot;
comma
l_string|&quot;18 dB&quot;
comma
l_string|&quot;18 dB&quot;
comma
l_string|&quot;18 dB&quot;
comma
l_string|&quot;18 dB&quot;
comma
l_string|&quot;undefined&quot;
comma
)brace
comma
singleline_comment|// min
(brace
l_string|&quot;0 dB&quot;
comma
l_string|&quot;2 dB&quot;
comma
l_string|&quot;4 dB&quot;
comma
l_string|&quot;6 dB&quot;
comma
l_string|&quot;8 dB&quot;
comma
l_string|&quot;10 dB&quot;
comma
l_string|&quot;12 dB&quot;
comma
l_string|&quot;14 dB&quot;
comma
l_string|&quot;16 dB&quot;
comma
l_string|&quot;18 dB&quot;
comma
l_string|&quot;18 dB&quot;
comma
l_string|&quot;18 dB&quot;
comma
l_string|&quot;18 dB&quot;
comma
l_string|&quot;18 dB&quot;
comma
l_string|&quot;18 dB&quot;
comma
l_string|&quot;undefined&quot;
comma
)brace
comma
singleline_comment|// min
(brace
l_string|&quot;0 dB&quot;
comma
l_string|&quot;2 dB&quot;
comma
l_string|&quot;4 dB&quot;
comma
l_string|&quot;6 dB&quot;
comma
l_string|&quot;8 dB&quot;
comma
l_string|&quot;10 dB&quot;
comma
l_string|&quot;12 dB&quot;
comma
l_string|&quot;14 dB&quot;
comma
l_string|&quot;16 dB&quot;
comma
l_string|&quot;18 dB&quot;
comma
l_string|&quot;20 dB&quot;
comma
l_string|&quot;22 dB&quot;
comma
l_string|&quot;24 dB&quot;
comma
l_string|&quot;24 dB&quot;
comma
l_string|&quot;24 dB&quot;
comma
l_string|&quot;undefined&quot;
comma
)brace
comma
singleline_comment|// max
)brace
suffix:semicolon
DECL|enum|uda1341_mixer
r_enum
id|uda1341_mixer
(brace
DECL|enumerator|DOUBLE
id|DOUBLE
comma
DECL|enumerator|LINE
id|LINE
comma
DECL|enumerator|MIC
id|MIC
comma
DECL|enumerator|MIXER
id|MIXER
comma
)brace
suffix:semicolon
DECL|variable|mixer_names
r_const
r_char
op_star
id|mixer_names
(braket
)braket
op_assign
(brace
l_string|&quot;double differential&quot;
comma
l_string|&quot;input channel 1 (line in)&quot;
comma
l_string|&quot;input channel 2 (microphone)&quot;
comma
l_string|&quot;digital mixer&quot;
comma
)brace
suffix:semicolon
DECL|enum|uda1341_deemp
r_enum
id|uda1341_deemp
(brace
DECL|enumerator|NONE
id|NONE
comma
DECL|enumerator|D32
id|D32
comma
DECL|enumerator|D44
id|D44
comma
DECL|enumerator|D48
id|D48
comma
)brace
suffix:semicolon
DECL|variable|deemp_names
r_const
r_char
op_star
id|deemp_names
(braket
)braket
op_assign
(brace
l_string|&quot;none&quot;
comma
l_string|&quot;32 kHz&quot;
comma
l_string|&quot;44.1 kHz&quot;
comma
l_string|&quot;48 kHz&quot;
comma
)brace
suffix:semicolon
DECL|variable|mic_sens_value
r_const
r_char
op_star
id|mic_sens_value
(braket
)braket
op_assign
(brace
l_string|&quot;-3 dB&quot;
comma
l_string|&quot;0 dB&quot;
comma
l_string|&quot;3 dB&quot;
comma
l_string|&quot;9 dB&quot;
comma
l_string|&quot;15 dB&quot;
comma
l_string|&quot;21 dB&quot;
comma
l_string|&quot;27 dB&quot;
comma
l_string|&quot;not used&quot;
comma
)brace
suffix:semicolon
DECL|variable|AGC_atime
r_const
r_int
r_int
id|AGC_atime
(braket
)braket
op_assign
(brace
l_int|11
comma
l_int|16
comma
l_int|11
comma
l_int|16
comma
l_int|21
comma
l_int|11
comma
l_int|16
comma
l_int|21
comma
)brace
suffix:semicolon
DECL|variable|AGC_dtime
r_const
r_int
r_int
id|AGC_dtime
(braket
)braket
op_assign
(brace
l_int|100
comma
l_int|100
comma
l_int|200
comma
l_int|200
comma
l_int|200
comma
l_int|400
comma
l_int|400
comma
l_int|400
comma
)brace
suffix:semicolon
DECL|variable|AGC_level
r_const
r_char
op_star
id|AGC_level
(braket
)braket
op_assign
(brace
l_string|&quot;-9.0&quot;
comma
l_string|&quot;-11.5&quot;
comma
l_string|&quot;-15.0&quot;
comma
l_string|&quot;-17.5&quot;
comma
)brace
suffix:semicolon
DECL|variable|ig_small_value
r_const
r_char
op_star
id|ig_small_value
(braket
)braket
op_assign
(brace
l_string|&quot;-3.0&quot;
comma
l_string|&quot;-2.5&quot;
comma
l_string|&quot;-2.0&quot;
comma
l_string|&quot;-1.5&quot;
comma
l_string|&quot;-1.0&quot;
comma
l_string|&quot;-0.5&quot;
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * this was computed as peak_value[i] = pow((63-i)*1.42,1.013)&n; *&n; * UDA1341 datasheet on page 21: Peak value (dB) = (Peak level - 63.5)*5*log2&n; * There is an tabel with these values [level]=value: [3]=-90.31, [7]=-84.29&n; * [61]=-2.78, [62] = -1.48, [63] = 0.0&n; * I tried to compute it, but using but even using logarithm with base either 10 or 2&n; * i was&squot;n able to get values in the table from the formula. So I constructed another&n; * formula (see above) to interpolate the values as good as possible. If there is some&n; * mistake, please contact me on tomas.kasparek@seznam.cz. Thanks.&n; * UDA1341TS datasheet is available at:&n; *   http://www-us9.semiconductors.com/acrobat/datasheets/UDA1341TS_3.pdf &n; */
DECL|variable|peak_value
r_const
r_char
op_star
id|peak_value
(braket
)braket
op_assign
(brace
l_string|&quot;-INF dB&quot;
comma
l_string|&quot;N.A.&quot;
comma
l_string|&quot;N.A&quot;
comma
l_string|&quot;90.31 dB&quot;
comma
l_string|&quot;N.A.&quot;
comma
l_string|&quot;N.A.&quot;
comma
l_string|&quot;N.A.&quot;
comma
l_string|&quot;-84.29 dB&quot;
comma
l_string|&quot;-82.65 dB&quot;
comma
l_string|&quot;-81.13 dB&quot;
comma
l_string|&quot;-79.61 dB&quot;
comma
l_string|&quot;-78.09 dB&quot;
comma
l_string|&quot;-76.57 dB&quot;
comma
l_string|&quot;-75.05 dB&quot;
comma
l_string|&quot;-73.53 dB&quot;
comma
l_string|&quot;-72.01 dB&quot;
comma
l_string|&quot;-70.49 dB&quot;
comma
l_string|&quot;-68.97 dB&quot;
comma
l_string|&quot;-67.45 dB&quot;
comma
l_string|&quot;-65.93 dB&quot;
comma
l_string|&quot;-64.41 dB&quot;
comma
l_string|&quot;-62.90 dB&quot;
comma
l_string|&quot;-61.38 dB&quot;
comma
l_string|&quot;-59.86 dB&quot;
comma
l_string|&quot;-58.35 dB&quot;
comma
l_string|&quot;-56.83 dB&quot;
comma
l_string|&quot;-55.32 dB&quot;
comma
l_string|&quot;-53.80 dB&quot;
comma
l_string|&quot;-52.29 dB&quot;
comma
l_string|&quot;-50.78 dB&quot;
comma
l_string|&quot;-49.26 dB&quot;
comma
l_string|&quot;-47.75 dB&quot;
comma
l_string|&quot;-46.24 dB&quot;
comma
l_string|&quot;-44.73 dB&quot;
comma
l_string|&quot;-43.22 dB&quot;
comma
l_string|&quot;-41.71 dB&quot;
comma
l_string|&quot;-40.20 dB&quot;
comma
l_string|&quot;-38.69 dB&quot;
comma
l_string|&quot;-37.19 dB&quot;
comma
l_string|&quot;-35.68 dB&quot;
comma
l_string|&quot;-34.17 dB&quot;
comma
l_string|&quot;-32.67 dB&quot;
comma
l_string|&quot;-31.17 dB&quot;
comma
l_string|&quot;-29.66 dB&quot;
comma
l_string|&quot;-28.16 dB&quot;
comma
l_string|&quot;-26.66 dB&quot;
comma
l_string|&quot;-25.16 dB&quot;
comma
l_string|&quot;-23.66 dB&quot;
comma
l_string|&quot;-22.16 dB&quot;
comma
l_string|&quot;-20.67 dB&quot;
comma
l_string|&quot;-19.17 dB&quot;
comma
l_string|&quot;-17.68 dB&quot;
comma
l_string|&quot;-16.19 dB&quot;
comma
l_string|&quot;-14.70 dB&quot;
comma
l_string|&quot;-13.21 dB&quot;
comma
l_string|&quot;-11.72 dB&quot;
comma
l_string|&quot;-10.24 dB&quot;
comma
l_string|&quot;-8.76 dB&quot;
comma
l_string|&quot;-7.28 dB&quot;
comma
l_string|&quot;-5.81 dB&quot;
comma
l_string|&quot;-4.34 dB&quot;
comma
l_string|&quot;-2.88 dB&quot;
comma
l_string|&quot;-1.43 dB&quot;
comma
l_string|&quot;0.00 dB&quot;
comma
)brace
suffix:semicolon
DECL|enum|uda1341_config
r_enum
id|uda1341_config
(brace
DECL|enumerator|CMD_READ_REG
id|CMD_READ_REG
op_assign
l_int|0
comma
DECL|enumerator|CMD_RESET
id|CMD_RESET
comma
DECL|enumerator|CMD_FS
id|CMD_FS
comma
DECL|enumerator|CMD_FORMAT
id|CMD_FORMAT
comma
DECL|enumerator|CMD_OGAIN
id|CMD_OGAIN
comma
DECL|enumerator|CMD_IGAIN
id|CMD_IGAIN
comma
DECL|enumerator|CMD_DAC
id|CMD_DAC
comma
DECL|enumerator|CMD_ADC
id|CMD_ADC
comma
DECL|enumerator|CMD_VOLUME
id|CMD_VOLUME
comma
DECL|enumerator|CMD_BASS
id|CMD_BASS
comma
DECL|enumerator|CMD_TREBBLE
id|CMD_TREBBLE
comma
DECL|enumerator|CMD_PEAK
id|CMD_PEAK
comma
DECL|enumerator|CMD_DEEMP
id|CMD_DEEMP
comma
DECL|enumerator|CMD_MUTE
id|CMD_MUTE
comma
DECL|enumerator|CMD_FILTER
id|CMD_FILTER
comma
DECL|enumerator|CMD_CH1
id|CMD_CH1
comma
DECL|enumerator|CMD_CH2
id|CMD_CH2
comma
DECL|enumerator|CMD_MIC
id|CMD_MIC
comma
DECL|enumerator|CMD_MIXER
id|CMD_MIXER
comma
DECL|enumerator|CMD_AGC
id|CMD_AGC
comma
DECL|enumerator|CMD_IG
id|CMD_IG
comma
DECL|enumerator|CMD_AGC_TIME
id|CMD_AGC_TIME
comma
DECL|enumerator|CMD_AGC_LEVEL
id|CMD_AGC_LEVEL
comma
DECL|enumerator|CMD_LAST
id|CMD_LAST
comma
)brace
suffix:semicolon
DECL|enum|write_through
r_enum
id|write_through
(brace
singleline_comment|//used in update_bits (write_cfg) to avoid l3_write - just update local copy of regs.
DECL|enumerator|REGS_ONLY
id|REGS_ONLY
op_assign
l_int|0
comma
singleline_comment|//update local regs and write value to uda1341 - do l3_write
DECL|enumerator|FLUSH
id|FLUSH
comma
)brace
suffix:semicolon
r_int
id|__init
id|snd_chip_uda1341_mixer_new
c_func
(paren
id|snd_card_t
op_star
id|card
comma
r_struct
id|l3_client
op_star
op_star
id|clnt
)paren
suffix:semicolon
r_void
id|__init
id|snd_chip_uda1341_mixer_del
c_func
(paren
id|snd_card_t
op_star
id|card
)paren
suffix:semicolon
macro_line|#ifdef DEBUG_MODE
DECL|macro|DEBUG
mdefine_line|#define DEBUG(format, args...)      do{printk(format, ##args);}while(0)
macro_line|#else
DECL|macro|DEBUG
mdefine_line|#define DEBUG(format, args...)      /* nothing */
macro_line|#endif
macro_line|#ifdef DEBUG_FUNCTION_NAMES
DECL|macro|DEBUG_NAME
mdefine_line|#define DEBUG_NAME(format, args...)     do{printk(format, ##args);}while(0)
macro_line|#else
DECL|macro|DEBUG_NAME
mdefine_line|#define DEBUG_NAME(format, args...)     /* nothing */
macro_line|#endif
multiline_comment|/*&n; * Local variables:&n; * indent-tabs-mode: t&n; * End:&n; */
eof
