multiline_comment|/*&n; * .h-files for the common use of the frontend drivers made by DiBcom&n; * DiBcom 3000-MB/MC/P&n; *&n; * DiBcom (http://www.dibcom.fr/)&n; *&n; * Copyright (C) 2004 Patrick Boettcher (patrick.boettcher@desy.de)&n; *&n; * based on GPL code from DibCom, which has&n; *&n; * Copyright (C) 2004 Amaury Demol for DiBcom (ademol@dibcom.fr)&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License as&n; *&t;published by the Free Software Foundation, version 2.&n; *&n; * Acknowledgements&n; *&n; *  Amaury Demol (ademol@dibcom.fr) from DiBcom for providing specs and driver&n; *  sources, on which this driver (and the dvb-dibusb) are based.&n; *&n; * see Documentation/dvb/README.dibusb for more information&n; *&n; */
macro_line|#ifndef DIB3000_COMMON_H
DECL|macro|DIB3000_COMMON_H
mdefine_line|#define DIB3000_COMMON_H
multiline_comment|/* info and err, taken from usb.h, if there is anything available like by default,&n; * please change !&n; */
DECL|macro|err
mdefine_line|#define err(format, arg...) printk(KERN_ERR &quot;%s: &quot; format &quot;&bslash;n&quot; , __FILE__ , ## arg)
DECL|macro|info
mdefine_line|#define info(format, arg...) printk(KERN_INFO &quot;%s: &quot; format &quot;&bslash;n&quot; , __FILE__ , ## arg)
DECL|macro|warn
mdefine_line|#define warn(format, arg...) printk(KERN_WARNING &quot;%s: &quot; format &quot;&bslash;n&quot; , __FILE__ , ## arg)
multiline_comment|/* a PID for the pid_filter list, when in use */
DECL|struct|dib3000_pid
r_struct
id|dib3000_pid
(brace
DECL|member|pid
id|u16
id|pid
suffix:semicolon
DECL|member|active
r_int
id|active
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* mask for enabling a specific pid for the pid_filter */
DECL|macro|DIB3000_ACTIVATE_PID_FILTERING
mdefine_line|#define DIB3000_ACTIVATE_PID_FILTERING&t;(0x2000)
multiline_comment|/* common values for tuning */
DECL|macro|DIB3000_ALPHA_0
mdefine_line|#define DIB3000_ALPHA_0&t;&t;&t;&t;&t;(     0)
DECL|macro|DIB3000_ALPHA_1
mdefine_line|#define DIB3000_ALPHA_1&t;&t;&t;&t;&t;(     1)
DECL|macro|DIB3000_ALPHA_2
mdefine_line|#define DIB3000_ALPHA_2&t;&t;&t;&t;&t;(     2)
DECL|macro|DIB3000_ALPHA_4
mdefine_line|#define DIB3000_ALPHA_4&t;&t;&t;&t;&t;(     4)
DECL|macro|DIB3000_CONSTELLATION_QPSK
mdefine_line|#define DIB3000_CONSTELLATION_QPSK&t;&t;(     0)
DECL|macro|DIB3000_CONSTELLATION_16QAM
mdefine_line|#define DIB3000_CONSTELLATION_16QAM&t;&t;(     1)
DECL|macro|DIB3000_CONSTELLATION_64QAM
mdefine_line|#define DIB3000_CONSTELLATION_64QAM&t;&t;(     2)
DECL|macro|DIB3000_GUARD_TIME_1_32
mdefine_line|#define DIB3000_GUARD_TIME_1_32&t;&t;&t;(     0)
DECL|macro|DIB3000_GUARD_TIME_1_16
mdefine_line|#define DIB3000_GUARD_TIME_1_16&t;&t;&t;(     1)
DECL|macro|DIB3000_GUARD_TIME_1_8
mdefine_line|#define DIB3000_GUARD_TIME_1_8&t;&t;&t;(     2)
DECL|macro|DIB3000_GUARD_TIME_1_4
mdefine_line|#define DIB3000_GUARD_TIME_1_4&t;&t;&t;(     3)
DECL|macro|DIB3000_TRANSMISSION_MODE_2K
mdefine_line|#define DIB3000_TRANSMISSION_MODE_2K&t;(     0)
DECL|macro|DIB3000_TRANSMISSION_MODE_8K
mdefine_line|#define DIB3000_TRANSMISSION_MODE_8K&t;(     1)
DECL|macro|DIB3000_SELECT_LP
mdefine_line|#define DIB3000_SELECT_LP&t;&t;&t;&t;(     0)
DECL|macro|DIB3000_SELECT_HP
mdefine_line|#define DIB3000_SELECT_HP&t;&t;&t;&t;(     1)
DECL|macro|DIB3000_FEC_1_2
mdefine_line|#define DIB3000_FEC_1_2&t;&t;&t;&t;&t;(     1)
DECL|macro|DIB3000_FEC_2_3
mdefine_line|#define DIB3000_FEC_2_3&t;&t;&t;&t;&t;(     2)
DECL|macro|DIB3000_FEC_3_4
mdefine_line|#define DIB3000_FEC_3_4&t;&t;&t;&t;&t;(     3)
DECL|macro|DIB3000_FEC_5_6
mdefine_line|#define DIB3000_FEC_5_6&t;&t;&t;&t;&t;(     5)
DECL|macro|DIB3000_FEC_7_8
mdefine_line|#define DIB3000_FEC_7_8&t;&t;&t;&t;&t;(     7)
DECL|macro|DIB3000_HRCH_OFF
mdefine_line|#define DIB3000_HRCH_OFF&t;&t;&t;&t;(     0)
DECL|macro|DIB3000_HRCH_ON
mdefine_line|#define DIB3000_HRCH_ON&t;&t;&t;&t;&t;(     1)
DECL|macro|DIB3000_DDS_INVERSION_OFF
mdefine_line|#define DIB3000_DDS_INVERSION_OFF&t;&t;(     0)
DECL|macro|DIB3000_DDS_INVERSION_ON
mdefine_line|#define DIB3000_DDS_INVERSION_ON&t;&t;(     1)
DECL|macro|DIB3000_TUNER_WRITE_ENABLE
mdefine_line|#define DIB3000_TUNER_WRITE_ENABLE(a)&t;(0xffff &amp; (a &lt;&lt; 7))
DECL|macro|DIB3000_TUNER_WRITE_DISABLE
mdefine_line|#define DIB3000_TUNER_WRITE_DISABLE(a)&t;(0xffff &amp; ((a &lt;&lt; 7) | (1 &lt;&lt; 7)))
multiline_comment|/* for auto search */
DECL|variable|dib3000_seq
r_static
id|u16
id|dib3000_seq
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
DECL|macro|DIB3000_REG_MANUFACTOR_ID
mdefine_line|#define DIB3000_REG_MANUFACTOR_ID&t;&t;(  1025)
DECL|macro|DIB3000_I2C_ID_DIBCOM
mdefine_line|#define DIB3000_I2C_ID_DIBCOM&t;&t;&t;(0x01b3)
DECL|macro|DIB3000_REG_DEVICE_ID
mdefine_line|#define DIB3000_REG_DEVICE_ID&t;&t;&t;(  1026)
DECL|macro|DIB3000MB_DEVICE_ID
mdefine_line|#define DIB3000MB_DEVICE_ID&t;&t;&t;&t;(0x3000)
DECL|macro|DIB3000MC_DEVICE_ID
mdefine_line|#define DIB3000MC_DEVICE_ID&t;&t;&t;&t;(0x3001)
DECL|macro|DIB3000P_DEVICE_ID
mdefine_line|#define DIB3000P_DEVICE_ID&t;&t;&t;&t;(0x3002)
macro_line|#endif 
singleline_comment|// DIB3000_COMMON_H
eof
