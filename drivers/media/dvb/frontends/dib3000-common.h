multiline_comment|/*&n; * .h-files for the common use of the frontend drivers made by DiBcom&n; * DiBcom 3000-MB/MC/P&n; *&n; * DiBcom (http://www.dibcom.fr/)&n; *&n; * Copyright (C) 2004-5 Patrick Boettcher (patrick.boettcher@desy.de)&n; *&n; * based on GPL code from DibCom, which has&n; *&n; * Copyright (C) 2004 Amaury Demol for DiBcom (ademol@dibcom.fr)&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License as&n; *&t;published by the Free Software Foundation, version 2.&n; *&n; * Acknowledgements&n; *&n; *  Amaury Demol (ademol@dibcom.fr) from DiBcom for providing specs and driver&n; *  sources, on which this driver (and the dvb-dibusb) are based.&n; *&n; * see Documentation/dvb/README.dibusb for more information&n; *&n; */
macro_line|#ifndef DIB3000_COMMON_H
DECL|macro|DIB3000_COMMON_H
mdefine_line|#define DIB3000_COMMON_H
macro_line|#include &quot;dvb_frontend.h&quot;
macro_line|#include &quot;dib3000.h&quot;
multiline_comment|/* info and err, taken from usb.h, if there is anything available like by default. */
DECL|macro|err
mdefine_line|#define err(format, arg...) printk(KERN_ERR &quot;dib3000mX: &quot; format &quot;&bslash;n&quot; , ## arg)
DECL|macro|info
mdefine_line|#define info(format, arg...) printk(KERN_INFO &quot;dib3000mX: &quot; format &quot;&bslash;n&quot; , ## arg)
DECL|macro|warn
mdefine_line|#define warn(format, arg...) printk(KERN_WARNING &quot;dib3000mX: &quot; format &quot;&bslash;n&quot; , ## arg)
multiline_comment|/* frontend state */
DECL|struct|dib3000_state
r_struct
id|dib3000_state
(brace
DECL|member|i2c
r_struct
id|i2c_adapter
op_star
id|i2c
suffix:semicolon
DECL|member|ops
r_struct
id|dvb_frontend_ops
id|ops
suffix:semicolon
multiline_comment|/* configuration settings */
DECL|member|config
r_struct
id|dib3000_config
id|config
suffix:semicolon
DECL|member|frontend
r_struct
id|dvb_frontend
id|frontend
suffix:semicolon
DECL|member|timing_offset
r_int
id|timing_offset
suffix:semicolon
DECL|member|timing_offset_comp_done
r_int
id|timing_offset_comp_done
suffix:semicolon
DECL|member|last_tuned_bw
id|fe_bandwidth_t
id|last_tuned_bw
suffix:semicolon
DECL|member|last_tuned_freq
id|u32
id|last_tuned_freq
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* commonly used methods by the dib3000mb/mc/p frontend */
r_extern
r_int
id|dib3000_read_reg
c_func
(paren
r_struct
id|dib3000_state
op_star
id|state
comma
id|u16
id|reg
)paren
suffix:semicolon
r_extern
r_int
id|dib3000_write_reg
c_func
(paren
r_struct
id|dib3000_state
op_star
id|state
comma
id|u16
id|reg
comma
id|u16
id|val
)paren
suffix:semicolon
r_extern
r_int
id|dib3000_search_status
c_func
(paren
id|u16
id|irq
comma
id|u16
id|lock
)paren
suffix:semicolon
multiline_comment|/* handy shortcuts */
DECL|macro|rd
mdefine_line|#define rd(reg) dib3000_read_reg(state,reg)
DECL|macro|wr
mdefine_line|#define wr(reg,val) if (dib3000_write_reg(state,reg,val)) &bslash;&n;&t;{ err(&quot;while sending 0x%04x to 0x%04x.&quot;,val,reg); return -EREMOTEIO; }
DECL|macro|wr_foreach
mdefine_line|#define wr_foreach(a,v) { int i; &bslash;&n;&t;if (sizeof(a) != sizeof(v)) &bslash;&n;&t;&t;err(&quot;sizeof: %d %d is different&quot;,sizeof(a),sizeof(v));&bslash;&n;&t;for (i=0; i &lt; sizeof(a)/sizeof(u16); i++) &bslash;&n;&t;&t;wr(a[i],v[i]); &bslash;&n;&t;}
DECL|macro|set_or
mdefine_line|#define set_or(reg,val) wr(reg,rd(reg) | val)
DECL|macro|set_and
mdefine_line|#define set_and(reg,val) wr(reg,rd(reg) &amp; val)
multiline_comment|/* debug */
macro_line|#ifdef CONFIG_DVB_DIBCOM_DEBUG
DECL|macro|dprintk
mdefine_line|#define dprintk(level,args...) &bslash;&n;    do { if ((debug &amp; level)) { printk(args); } } while (0)
macro_line|#else
DECL|macro|dprintk
mdefine_line|#define dprintk(args...) do { } while (0)
macro_line|#endif
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
mdefine_line|#define DIB3000_TUNER_WRITE_ENABLE(a)&t;(0xffff &amp; (a &lt;&lt; 8))
DECL|macro|DIB3000_TUNER_WRITE_DISABLE
mdefine_line|#define DIB3000_TUNER_WRITE_DISABLE(a)&t;(0xffff &amp; ((a &lt;&lt; 8) | (1 &lt;&lt; 7)))
multiline_comment|/* for auto search */
r_extern
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
