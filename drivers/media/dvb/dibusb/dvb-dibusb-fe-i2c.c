multiline_comment|/*&n; * dvb-dibusb-fe-i2c.c is part of the driver for mobile USB Budget DVB-T devices&n; * based on reference design made by DiBcom (http://www.dibcom.fr/)&n; *&n; * Copyright (C) 2004-5 Patrick Boettcher (patrick.boettcher@desy.de)&n; *&n; * see dvb-dibusb-core.c for more copyright details.&n; *&n; * This file contains functions for attaching, initializing of an appropriate&n; * demodulator/frontend. I2C-stuff is also located here.&n; *&n; */
macro_line|#include &quot;dvb-dibusb.h&quot;
macro_line|#include &lt;linux/usb.h&gt;
DECL|function|dibusb_i2c_msg
r_static
r_int
id|dibusb_i2c_msg
c_func
(paren
r_struct
id|usb_dibusb
op_star
id|dib
comma
id|u8
id|addr
comma
id|u8
op_star
id|wbuf
comma
id|u16
id|wlen
comma
id|u8
op_star
id|rbuf
comma
id|u16
id|rlen
)paren
(brace
id|u8
id|sndbuf
(braket
id|wlen
op_plus
l_int|4
)braket
suffix:semicolon
multiline_comment|/* lead(1) devaddr,direction(1) addr(2) data(wlen) (len(2) (when reading)) */
multiline_comment|/* write only ? */
r_int
id|wo
op_assign
(paren
id|rbuf
op_eq
l_int|NULL
op_logical_or
id|rlen
op_eq
l_int|0
)paren
comma
id|len
op_assign
l_int|2
op_plus
id|wlen
op_plus
(paren
id|wo
ques
c_cond
l_int|0
suffix:colon
l_int|2
)paren
suffix:semicolon
id|sndbuf
(braket
l_int|0
)braket
op_assign
id|wo
ques
c_cond
id|DIBUSB_REQ_I2C_WRITE
suffix:colon
id|DIBUSB_REQ_I2C_READ
suffix:semicolon
id|sndbuf
(braket
l_int|1
)braket
op_assign
(paren
id|addr
op_lshift
l_int|1
)paren
op_or
(paren
id|wo
ques
c_cond
l_int|0
suffix:colon
l_int|1
)paren
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|sndbuf
(braket
l_int|2
)braket
comma
id|wbuf
comma
id|wlen
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|wo
)paren
(brace
id|sndbuf
(braket
id|wlen
op_plus
l_int|2
)braket
op_assign
(paren
id|rlen
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
suffix:semicolon
id|sndbuf
(braket
id|wlen
op_plus
l_int|3
)braket
op_assign
id|rlen
op_amp
l_int|0xff
suffix:semicolon
)brace
r_return
id|dibusb_readwrite_usb
c_func
(paren
id|dib
comma
id|sndbuf
comma
id|len
comma
id|rbuf
comma
id|rlen
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * I2C master xfer function&n; */
DECL|function|dibusb_i2c_xfer
r_static
r_int
id|dibusb_i2c_xfer
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|adap
comma
r_struct
id|i2c_msg
op_star
id|msg
comma
r_int
id|num
)paren
(brace
r_struct
id|usb_dibusb
op_star
id|dib
op_assign
id|i2c_get_adapdata
c_func
(paren
id|adap
)paren
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|down_interruptible
c_func
(paren
op_amp
id|dib-&gt;i2c_sem
)paren
OL
l_int|0
)paren
r_return
op_minus
id|EAGAIN
suffix:semicolon
r_if
c_cond
(paren
id|num
OG
l_int|2
)paren
id|warn
c_func
(paren
l_string|&quot;more than 2 i2c messages at a time is not handled yet. TODO.&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|num
suffix:semicolon
id|i
op_increment
)paren
(brace
multiline_comment|/* write/read request */
r_if
c_cond
(paren
id|i
op_plus
l_int|1
OL
id|num
op_logical_and
(paren
id|msg
(braket
id|i
op_plus
l_int|1
)braket
dot
id|flags
op_amp
id|I2C_M_RD
)paren
)paren
(brace
r_if
c_cond
(paren
id|dibusb_i2c_msg
c_func
(paren
id|dib
comma
id|msg
(braket
id|i
)braket
dot
id|addr
comma
id|msg
(braket
id|i
)braket
dot
id|buf
comma
id|msg
(braket
id|i
)braket
dot
id|len
comma
id|msg
(braket
id|i
op_plus
l_int|1
)braket
dot
id|buf
comma
id|msg
(braket
id|i
op_plus
l_int|1
)braket
dot
id|len
)paren
OL
l_int|0
)paren
r_break
suffix:semicolon
id|i
op_increment
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|dibusb_i2c_msg
c_func
(paren
id|dib
comma
id|msg
(braket
id|i
)braket
dot
id|addr
comma
id|msg
(braket
id|i
)braket
dot
id|buf
comma
id|msg
(braket
id|i
)braket
dot
id|len
comma
l_int|NULL
comma
l_int|0
)paren
OL
l_int|0
)paren
r_break
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
id|dib-&gt;i2c_sem
)paren
suffix:semicolon
r_return
id|i
suffix:semicolon
)brace
DECL|function|dibusb_i2c_func
r_static
id|u32
id|dibusb_i2c_func
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|adapter
)paren
(brace
r_return
id|I2C_FUNC_I2C
suffix:semicolon
)brace
DECL|variable|dibusb_algo
r_static
r_struct
id|i2c_algorithm
id|dibusb_algo
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;DiBcom USB i2c algorithm&quot;
comma
dot
id|id
op_assign
id|I2C_ALGO_BIT
comma
dot
id|master_xfer
op_assign
id|dibusb_i2c_xfer
comma
dot
id|functionality
op_assign
id|dibusb_i2c_func
comma
)brace
suffix:semicolon
r_static
r_int
id|dibusb_general_demod_init
c_func
(paren
r_struct
id|dvb_frontend
op_star
id|fe
)paren
suffix:semicolon
r_static
id|u8
id|dibusb_general_pll_addr
c_func
(paren
r_struct
id|dvb_frontend
op_star
id|fe
)paren
suffix:semicolon
r_static
r_int
id|dibusb_general_pll_init
c_func
(paren
r_struct
id|dvb_frontend
op_star
id|fe
comma
id|u8
id|pll_buf
(braket
l_int|5
)braket
)paren
suffix:semicolon
r_static
r_int
id|dibusb_general_pll_set
c_func
(paren
r_struct
id|dvb_frontend
op_star
id|fe
comma
r_struct
id|dvb_frontend_parameters
op_star
id|params
comma
id|u8
id|pll_buf
(braket
l_int|5
)braket
)paren
suffix:semicolon
DECL|variable|mt352_hanftek_umt_010_config
r_static
r_struct
id|mt352_config
id|mt352_hanftek_umt_010_config
op_assign
(brace
dot
id|demod_address
op_assign
l_int|0x1e
comma
dot
id|demod_init
op_assign
id|dibusb_general_demod_init
comma
dot
id|pll_set
op_assign
id|dibusb_general_pll_set
comma
)brace
suffix:semicolon
DECL|function|dibusb_tuner_quirk
r_static
r_int
id|dibusb_tuner_quirk
c_func
(paren
r_struct
id|usb_dibusb
op_star
id|dib
)paren
(brace
r_switch
c_cond
(paren
id|dib-&gt;dibdev-&gt;dev_cl-&gt;id
)paren
(brace
r_case
id|DIBUSB1_1
suffix:colon
multiline_comment|/* some these device have the ENV77H11D5 and some the THOMSON CABLE */
r_case
id|DIBUSB1_1_AN2235
suffix:colon
(brace
multiline_comment|/* actually its this device, but in warm state they are indistinguishable */
r_struct
id|dibusb_tuner
op_star
id|t
suffix:semicolon
id|u8
id|b
(braket
l_int|2
)braket
op_assign
(brace
l_int|0
comma
l_int|0
)brace
comma
id|b2
(braket
l_int|1
)braket
suffix:semicolon
r_struct
id|i2c_msg
id|msg
(braket
l_int|2
)braket
op_assign
(brace
(brace
dot
id|flags
op_assign
l_int|0
comma
dot
id|buf
op_assign
id|b
comma
dot
id|len
op_assign
l_int|2
)brace
comma
(brace
dot
id|flags
op_assign
id|I2C_M_RD
comma
dot
id|buf
op_assign
id|b2
comma
dot
id|len
op_assign
l_int|1
)brace
comma
)brace
suffix:semicolon
id|t
op_assign
op_amp
id|dibusb_tuner
(braket
id|DIBUSB_TUNER_COFDM_PANASONIC_ENV77H11D5
)braket
suffix:semicolon
id|msg
(braket
l_int|0
)braket
dot
id|addr
op_assign
id|msg
(braket
l_int|1
)braket
dot
id|addr
op_assign
id|t-&gt;pll_addr
suffix:semicolon
r_if
c_cond
(paren
id|dib-&gt;xfer_ops.tuner_pass_ctrl
op_ne
l_int|NULL
)paren
id|dib-&gt;xfer_ops
dot
id|tuner_pass_ctrl
c_func
(paren
id|dib-&gt;fe
comma
l_int|1
comma
id|t-&gt;pll_addr
)paren
suffix:semicolon
id|dibusb_i2c_xfer
c_func
(paren
op_amp
id|dib-&gt;i2c_adap
comma
id|msg
comma
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dib-&gt;xfer_ops.tuner_pass_ctrl
op_ne
l_int|NULL
)paren
id|dib-&gt;xfer_ops
dot
id|tuner_pass_ctrl
c_func
(paren
id|dib-&gt;fe
comma
l_int|0
comma
id|t-&gt;pll_addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|b2
(braket
l_int|0
)braket
op_eq
l_int|0xfe
)paren
id|info
c_func
(paren
l_string|&quot;this device has the Thomson Cable onboard. Which is default.&quot;
)paren
suffix:semicolon
r_else
(brace
id|dib-&gt;tuner
op_assign
id|t
suffix:semicolon
id|info
c_func
(paren
l_string|&quot;this device has the Panasonic ENV77H11D5 onboard.&quot;
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
r_default
suffix:colon
r_break
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* there is a ugly pid_filter in the firmware of the umt devices, it is accessible&n; * by i2c address 0x8. Don&squot;t know how to deactivate it and how many rows it has.&n; */
DECL|function|dibusb_umt_pid_control
r_static
r_int
id|dibusb_umt_pid_control
c_func
(paren
r_struct
id|dvb_frontend
op_star
id|fe
comma
r_int
id|index
comma
r_int
id|pid
comma
r_int
id|onoff
)paren
(brace
r_struct
id|usb_dibusb
op_star
id|dib
op_assign
id|fe-&gt;dvb-&gt;priv
suffix:semicolon
id|u8
id|b
(braket
l_int|3
)braket
suffix:semicolon
id|b
(braket
l_int|0
)braket
op_assign
id|index
suffix:semicolon
r_if
c_cond
(paren
id|onoff
)paren
(brace
id|b
(braket
l_int|1
)braket
op_assign
(paren
id|pid
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
suffix:semicolon
id|b
(braket
l_int|2
)braket
op_assign
id|pid
op_amp
l_int|0xff
suffix:semicolon
)brace
r_else
(brace
id|b
(braket
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
id|b
(braket
l_int|2
)braket
op_assign
l_int|0
suffix:semicolon
)brace
id|dibusb_i2c_msg
c_func
(paren
id|dib
comma
l_int|0x8
comma
id|b
comma
l_int|3
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
id|dibusb_set_streaming_mode
c_func
(paren
id|dib
comma
l_int|0
)paren
suffix:semicolon
id|dibusb_set_streaming_mode
c_func
(paren
id|dib
comma
l_int|1
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dibusb_fe_init
r_int
id|dibusb_fe_init
c_func
(paren
r_struct
id|usb_dibusb
op_star
id|dib
)paren
(brace
r_struct
id|dib3000_config
id|demod_cfg
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|dib-&gt;init_state
op_amp
id|DIBUSB_STATE_I2C
)paren
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
r_sizeof
(paren
id|dib-&gt;dibdev-&gt;dev_cl-&gt;demod-&gt;i2c_addrs
)paren
op_div
r_sizeof
(paren
r_int
r_char
)paren
op_logical_and
id|dib-&gt;dibdev-&gt;dev_cl-&gt;demod-&gt;i2c_addrs
(braket
id|i
)braket
op_ne
l_int|0
suffix:semicolon
id|i
op_increment
)paren
(brace
id|demod_cfg.demod_address
op_assign
id|dib-&gt;dibdev-&gt;dev_cl-&gt;demod-&gt;i2c_addrs
(braket
id|i
)braket
suffix:semicolon
id|demod_cfg.pll_addr
op_assign
id|dibusb_general_pll_addr
suffix:semicolon
id|demod_cfg.pll_set
op_assign
id|dibusb_general_pll_set
suffix:semicolon
id|demod_cfg.pll_init
op_assign
id|dibusb_general_pll_init
suffix:semicolon
r_switch
c_cond
(paren
id|dib-&gt;dibdev-&gt;dev_cl-&gt;demod-&gt;id
)paren
(brace
r_case
id|DIBUSB_DIB3000MB
suffix:colon
id|dib-&gt;fe
op_assign
id|dib3000mb_attach
c_func
(paren
op_amp
id|demod_cfg
comma
op_amp
id|dib-&gt;i2c_adap
comma
op_amp
id|dib-&gt;xfer_ops
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DIBUSB_DIB3000MC
suffix:colon
id|dib-&gt;fe
op_assign
id|dib3000mc_attach
c_func
(paren
op_amp
id|demod_cfg
comma
op_amp
id|dib-&gt;i2c_adap
comma
op_amp
id|dib-&gt;xfer_ops
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DIBUSB_MT352
suffix:colon
id|mt352_hanftek_umt_010_config.demod_address
op_assign
id|dib-&gt;dibdev-&gt;dev_cl-&gt;demod-&gt;i2c_addrs
(braket
id|i
)braket
suffix:semicolon
id|dib-&gt;fe
op_assign
id|mt352_attach
c_func
(paren
op_amp
id|mt352_hanftek_umt_010_config
comma
op_amp
id|dib-&gt;i2c_adap
)paren
suffix:semicolon
id|dib-&gt;xfer_ops.pid_ctrl
op_assign
id|dibusb_umt_pid_control
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dib-&gt;fe
op_ne
l_int|NULL
)paren
(brace
id|info
c_func
(paren
l_string|&quot;found demodulator at i2c address 0x%x&quot;
comma
id|dib-&gt;dibdev-&gt;dev_cl-&gt;demod-&gt;i2c_addrs
(braket
id|i
)braket
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/* if a frontend was found */
r_if
c_cond
(paren
id|dib-&gt;fe
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|dib-&gt;fe-&gt;ops-&gt;sleep
op_ne
l_int|NULL
)paren
id|dib-&gt;fe_sleep
op_assign
id|dib-&gt;fe-&gt;ops-&gt;sleep
suffix:semicolon
id|dib-&gt;fe-&gt;ops-&gt;sleep
op_assign
id|dibusb_hw_sleep
suffix:semicolon
r_if
c_cond
(paren
id|dib-&gt;fe-&gt;ops-&gt;init
op_ne
l_int|NULL
)paren
id|dib-&gt;fe_init
op_assign
id|dib-&gt;fe-&gt;ops-&gt;init
suffix:semicolon
id|dib-&gt;fe-&gt;ops-&gt;init
op_assign
id|dibusb_hw_wakeup
suffix:semicolon
multiline_comment|/* setting the default tuner */
id|dib-&gt;tuner
op_assign
id|dib-&gt;dibdev-&gt;dev_cl-&gt;tuner
suffix:semicolon
multiline_comment|/* check which tuner is mounted on this device, in case this is unsure */
id|dibusb_tuner_quirk
c_func
(paren
id|dib
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|dib-&gt;fe
op_eq
l_int|NULL
)paren
(brace
id|err
c_func
(paren
l_string|&quot;A frontend driver was not found for device &squot;%s&squot;.&quot;
comma
id|dib-&gt;dibdev-&gt;name
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|dvb_register_frontend
c_func
(paren
id|dib-&gt;adapter
comma
id|dib-&gt;fe
)paren
)paren
(brace
id|err
c_func
(paren
l_string|&quot;Frontend registration failed.&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dib-&gt;fe-&gt;ops-&gt;release
)paren
id|dib-&gt;fe-&gt;ops
op_member_access_from_pointer
id|release
c_func
(paren
id|dib-&gt;fe
)paren
suffix:semicolon
id|dib-&gt;fe
op_assign
l_int|NULL
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dibusb_fe_exit
r_int
id|dibusb_fe_exit
c_func
(paren
r_struct
id|usb_dibusb
op_star
id|dib
)paren
(brace
r_if
c_cond
(paren
id|dib-&gt;fe
op_ne
l_int|NULL
)paren
id|dvb_unregister_frontend
c_func
(paren
id|dib-&gt;fe
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dibusb_i2c_init
r_int
id|dibusb_i2c_init
c_func
(paren
r_struct
id|usb_dibusb
op_star
id|dib
)paren
(brace
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
id|dib-&gt;adapter-&gt;priv
op_assign
id|dib
suffix:semicolon
id|strncpy
c_func
(paren
id|dib-&gt;i2c_adap.name
comma
id|dib-&gt;dibdev-&gt;name
comma
id|I2C_NAME_SIZE
)paren
suffix:semicolon
macro_line|#ifdef I2C_ADAP_CLASS_TV_DIGITAL
id|dib-&gt;i2c_adap
dot
r_class
op_assign
id|I2C_ADAP_CLASS_TV_DIGITAL
comma
macro_line|#else
id|dib-&gt;i2c_adap
dot
r_class
op_assign
id|I2C_CLASS_TV_DIGITAL
comma
macro_line|#endif
id|dib-&gt;i2c_adap.algo
op_assign
op_amp
id|dibusb_algo
suffix:semicolon
id|dib-&gt;i2c_adap.algo_data
op_assign
l_int|NULL
suffix:semicolon
id|dib-&gt;i2c_adap.id
op_assign
id|I2C_ALGO_BIT
suffix:semicolon
id|i2c_set_adapdata
c_func
(paren
op_amp
id|dib-&gt;i2c_adap
comma
id|dib
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|i2c_add_adapter
c_func
(paren
op_amp
id|dib-&gt;i2c_adap
)paren
)paren
OL
l_int|0
)paren
id|err
c_func
(paren
l_string|&quot;could not add i2c adapter&quot;
)paren
suffix:semicolon
id|dib-&gt;init_state
op_or_assign
id|DIBUSB_STATE_I2C
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|dibusb_i2c_exit
r_int
id|dibusb_i2c_exit
c_func
(paren
r_struct
id|usb_dibusb
op_star
id|dib
)paren
(brace
r_if
c_cond
(paren
id|dib-&gt;init_state
op_amp
id|DIBUSB_STATE_I2C
)paren
id|i2c_del_adapter
c_func
(paren
op_amp
id|dib-&gt;i2c_adap
)paren
suffix:semicolon
id|dib-&gt;init_state
op_and_assign
op_complement
id|DIBUSB_STATE_I2C
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* pll stuff, maybe removed soon (thx to Gerd/Andrew in advance) */
DECL|function|thomson_cable_eu_pll_set
r_static
r_int
id|thomson_cable_eu_pll_set
c_func
(paren
r_struct
id|dvb_frontend_parameters
op_star
id|fep
comma
id|u8
id|pllbuf
(braket
l_int|4
)braket
)paren
(brace
id|u32
id|tfreq
op_assign
(paren
id|fep-&gt;frequency
op_plus
l_int|36125000
)paren
op_div
l_int|62500
suffix:semicolon
r_int
id|vu
comma
id|p0
comma
id|p1
comma
id|p2
suffix:semicolon
r_if
c_cond
(paren
id|fep-&gt;frequency
OG
l_int|403250000
)paren
id|vu
op_assign
l_int|1
comma
id|p2
op_assign
l_int|1
comma
id|p1
op_assign
l_int|0
comma
id|p0
op_assign
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
id|fep-&gt;frequency
OG
l_int|115750000
)paren
id|vu
op_assign
l_int|0
comma
id|p2
op_assign
l_int|1
comma
id|p1
op_assign
l_int|1
comma
id|p0
op_assign
l_int|0
suffix:semicolon
r_else
r_if
c_cond
(paren
id|fep-&gt;frequency
OG
l_int|44250000
)paren
id|vu
op_assign
l_int|0
comma
id|p2
op_assign
l_int|0
comma
id|p1
op_assign
l_int|1
comma
id|p0
op_assign
l_int|1
suffix:semicolon
r_else
r_return
op_minus
id|EINVAL
suffix:semicolon
id|pllbuf
(braket
l_int|0
)braket
op_assign
(paren
id|tfreq
op_rshift
l_int|8
)paren
op_amp
l_int|0x7f
suffix:semicolon
id|pllbuf
(braket
l_int|1
)braket
op_assign
id|tfreq
op_amp
l_int|0xff
suffix:semicolon
id|pllbuf
(braket
l_int|2
)braket
op_assign
l_int|0x8e
suffix:semicolon
id|pllbuf
(braket
l_int|3
)braket
op_assign
(paren
id|vu
op_lshift
l_int|7
)paren
op_or
(paren
id|p2
op_lshift
l_int|2
)paren
op_or
(paren
id|p1
op_lshift
l_int|1
)paren
op_or
id|p0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|panasonic_cofdm_env57h1xd5_pll_set
r_static
r_int
id|panasonic_cofdm_env57h1xd5_pll_set
c_func
(paren
r_struct
id|dvb_frontend_parameters
op_star
id|fep
comma
id|u8
id|pllbuf
(braket
l_int|4
)braket
)paren
(brace
id|u32
id|freq
op_assign
id|fep-&gt;frequency
suffix:semicolon
id|u32
id|tfreq
op_assign
(paren
(paren
id|freq
op_plus
l_int|36125000
)paren
op_star
l_int|6
op_plus
l_int|500000
)paren
op_div
l_int|1000000
suffix:semicolon
id|u8
id|TA
comma
id|T210
comma
id|R210
comma
id|ctrl1
comma
id|cp210
comma
id|p4321
suffix:semicolon
r_if
c_cond
(paren
id|freq
OG
l_int|858000000
)paren
(brace
id|err
c_func
(paren
l_string|&quot;frequency cannot be larger than 858 MHz.&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
singleline_comment|// contol data 1 : 1 | T/A=1 | T2,T1,T0 = 0,0,0 | R2,R1,R0 = 0,1,0
id|TA
op_assign
l_int|1
suffix:semicolon
id|T210
op_assign
l_int|0
suffix:semicolon
id|R210
op_assign
l_int|0x2
suffix:semicolon
id|ctrl1
op_assign
(paren
l_int|1
op_lshift
l_int|7
)paren
op_or
(paren
id|TA
op_lshift
l_int|6
)paren
op_or
(paren
id|T210
op_lshift
l_int|3
)paren
op_or
id|R210
suffix:semicolon
singleline_comment|// ********    CHARGE PUMP CONFIG vs RF FREQUENCIES     *****************
r_if
c_cond
(paren
id|freq
OL
l_int|470000000
)paren
id|cp210
op_assign
l_int|2
suffix:semicolon
singleline_comment|// VHF Low and High band ch E12 to E4 to E12
r_else
r_if
c_cond
(paren
id|freq
OL
l_int|526000000
)paren
id|cp210
op_assign
l_int|4
suffix:semicolon
singleline_comment|// UHF band Ch E21 to E27
r_else
singleline_comment|// if (freq &lt; 862000000)
id|cp210
op_assign
l_int|5
suffix:semicolon
singleline_comment|// UHF band ch E28 to E69
singleline_comment|//*********************    BW select  *******************************
r_if
c_cond
(paren
id|freq
OL
l_int|153000000
)paren
id|p4321
op_assign
l_int|1
suffix:semicolon
singleline_comment|// BW selected for VHF low
r_else
r_if
c_cond
(paren
id|freq
OL
l_int|470000000
)paren
id|p4321
op_assign
l_int|2
suffix:semicolon
singleline_comment|// BW selected for VHF high E5 to E12
r_else
singleline_comment|// if (freq &lt; 862000000)
id|p4321
op_assign
l_int|4
suffix:semicolon
singleline_comment|// BW selection for UHF E21 to E69
id|pllbuf
(braket
l_int|0
)braket
op_assign
(paren
id|tfreq
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
suffix:semicolon
id|pllbuf
(braket
l_int|1
)braket
op_assign
(paren
id|tfreq
op_rshift
l_int|0
)paren
op_amp
l_int|0xff
suffix:semicolon
id|pllbuf
(braket
l_int|2
)braket
op_assign
l_int|0xff
op_amp
id|ctrl1
suffix:semicolon
id|pllbuf
(braket
l_int|3
)braket
op_assign
(paren
id|cp210
op_lshift
l_int|5
)paren
op_or
(paren
id|p4321
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;&t;&t;    7&t;6&t;&t;5&t;4&t;3&t;2&t;1&t;0&n; * Address Byte             1&t;1&t;&t;0&t;0&t;0&t;MA1&t;MA0&t;R/~W=0&n; *&n; * Program divider byte 1   0&t;n14&t;&t;n13&t;n12&t;n11&t;n10&t;n9&t;n8&n; * Program divider byte 2&t;n7&t;n6&t;&t;n5&t;n4&t;n3&t;n2&t;n1&t;n0&n; *&n; * Control byte 1           1&t;T/A=1&t;T2&t;T1&t;T0&t;R2&t;R1&t;R0&n; *                          1&t;T/A=0&t;0&t;0&t;ATC&t;AL2&t;AL1&t;AL0&n; *&n; * Control byte 2           CP2&t;CP1&t;&t;CP0&t;BS5&t;BS4&t;BS3&t;BS2&t;BS1&n; *&n; * MA0/1 = programmable address bits&n; * R/~W  = read/write bit (0 for writing)&n; * N14-0 = programmable LO frequency&n; *&n; * T/A   = test AGC bit (0 = next 6 bits AGC setting,&n; *                       1 = next 6 bits test and reference divider ratio settings)&n; * T2-0  = test bits&n; * R2-0  = reference divider ratio and programmable frequency step&n; * ATC   = AGC current setting and time constant&n; *         ATC = 0: AGC current = 220nA, AGC time constant = 2s&n; *         ATC = 1: AGC current = 9uA, AGC time constant = 50ms&n; * AL2-0 = AGC take-over point bits&n; * CP2-0 = charge pump current&n; * BS5-1 = PMOS ports control bits;&n; *             BSn = 0 corresponding port is off, high-impedance state (at power-on)&n; *             BSn = 1 corresponding port is on&n; */
DECL|function|panasonic_cofdm_env77h11d5_tda6650_init
r_static
r_int
id|panasonic_cofdm_env77h11d5_tda6650_init
c_func
(paren
r_struct
id|dvb_frontend
op_star
id|fe
comma
id|u8
id|pllbuf
(braket
l_int|4
)braket
)paren
(brace
id|pllbuf
(braket
l_int|0
)braket
op_assign
l_int|0x0b
suffix:semicolon
id|pllbuf
(braket
l_int|1
)braket
op_assign
l_int|0xf5
suffix:semicolon
id|pllbuf
(braket
l_int|2
)braket
op_assign
l_int|0x85
suffix:semicolon
id|pllbuf
(braket
l_int|3
)braket
op_assign
l_int|0xab
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|panasonic_cofdm_env77h11d5_tda6650_set
r_static
r_int
id|panasonic_cofdm_env77h11d5_tda6650_set
(paren
r_struct
id|dvb_frontend_parameters
op_star
id|fep
comma
id|u8
id|pllbuf
(braket
l_int|4
)braket
)paren
(brace
r_int
id|tuner_frequency
op_assign
l_int|0
suffix:semicolon
id|u8
id|band
comma
id|cp
comma
id|filter
suffix:semicolon
singleline_comment|// determine charge pump
id|tuner_frequency
op_assign
id|fep-&gt;frequency
op_plus
l_int|36166000
suffix:semicolon
r_if
c_cond
(paren
id|tuner_frequency
OL
l_int|87000000
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_else
r_if
c_cond
(paren
id|tuner_frequency
OL
l_int|130000000
)paren
id|cp
op_assign
l_int|3
suffix:semicolon
r_else
r_if
c_cond
(paren
id|tuner_frequency
OL
l_int|160000000
)paren
id|cp
op_assign
l_int|5
suffix:semicolon
r_else
r_if
c_cond
(paren
id|tuner_frequency
OL
l_int|200000000
)paren
id|cp
op_assign
l_int|6
suffix:semicolon
r_else
r_if
c_cond
(paren
id|tuner_frequency
OL
l_int|290000000
)paren
id|cp
op_assign
l_int|3
suffix:semicolon
r_else
r_if
c_cond
(paren
id|tuner_frequency
OL
l_int|420000000
)paren
id|cp
op_assign
l_int|5
suffix:semicolon
r_else
r_if
c_cond
(paren
id|tuner_frequency
OL
l_int|480000000
)paren
id|cp
op_assign
l_int|6
suffix:semicolon
r_else
r_if
c_cond
(paren
id|tuner_frequency
OL
l_int|620000000
)paren
id|cp
op_assign
l_int|3
suffix:semicolon
r_else
r_if
c_cond
(paren
id|tuner_frequency
OL
l_int|830000000
)paren
id|cp
op_assign
l_int|5
suffix:semicolon
r_else
r_if
c_cond
(paren
id|tuner_frequency
OL
l_int|895000000
)paren
id|cp
op_assign
l_int|7
suffix:semicolon
r_else
r_return
op_minus
id|EINVAL
suffix:semicolon
singleline_comment|// determine band
r_if
c_cond
(paren
id|fep-&gt;frequency
OL
l_int|49000000
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_else
r_if
c_cond
(paren
id|fep-&gt;frequency
OL
l_int|161000000
)paren
id|band
op_assign
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
id|fep-&gt;frequency
OL
l_int|444000000
)paren
id|band
op_assign
l_int|2
suffix:semicolon
r_else
r_if
c_cond
(paren
id|fep-&gt;frequency
OL
l_int|861000000
)paren
id|band
op_assign
l_int|4
suffix:semicolon
r_else
r_return
op_minus
id|EINVAL
suffix:semicolon
singleline_comment|// setup PLL filter
r_switch
c_cond
(paren
id|fep-&gt;u.ofdm.bandwidth
)paren
(brace
r_case
id|BANDWIDTH_6_MHZ
suffix:colon
r_case
id|BANDWIDTH_7_MHZ
suffix:colon
id|filter
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|BANDWIDTH_8_MHZ
suffix:colon
id|filter
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
singleline_comment|// calculate divisor
singleline_comment|// ((36166000+((1000000/6)/2)) + Finput)/(1000000/6)
id|tuner_frequency
op_assign
(paren
(paren
(paren
id|fep-&gt;frequency
op_div
l_int|1000
)paren
op_star
l_int|6
)paren
op_plus
l_int|217496
)paren
op_div
l_int|1000
suffix:semicolon
singleline_comment|// setup tuner buffer
id|pllbuf
(braket
l_int|0
)braket
op_assign
(paren
id|tuner_frequency
op_rshift
l_int|8
)paren
op_amp
l_int|0x7f
suffix:semicolon
id|pllbuf
(braket
l_int|1
)braket
op_assign
id|tuner_frequency
op_amp
l_int|0xff
suffix:semicolon
id|pllbuf
(braket
l_int|2
)braket
op_assign
l_int|0xca
suffix:semicolon
id|pllbuf
(braket
l_int|3
)braket
op_assign
(paren
id|cp
op_lshift
l_int|5
)paren
op_or
(paren
id|filter
op_lshift
l_int|3
)paren
op_or
id|band
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;&t;&t;    7&t;6&t;5&t;4&t;3&t;2&t;1&t;0&n; * Address Byte             1&t;1&t;0&t;0&t;0&t;MA1&t;MA0&t;R/~W=0&n; *&n; * Program divider byte 1   0&t;n14&t;n13&t;n12&t;n11&t;n10&t;n9&t;n8&n; * Program divider byte 2&t;n7&t;n6&t;n5&t;n4&t;n3&t;n2&t;n1&t;n0&n; *&n; * Control byte             1&t;CP&t;T2&t;T1&t;T0&t;RSA&t;RSB&t;OS&n; *&n; * Band Switch byte         X&t;X&t;X&t;P4&t;P3&t;P2&t;P1&t;P0&n; *&n; * Auxiliary byte           ATC&t;AL2&t;AL1&t;AL0&t;0&t;0&t;0&t;0&n; *&n; * Address: MA1&t;MA0&t;Address&n; *          0&t;0&t;c0&n; *          0&t;1&t;c2 (always valid)&n; *          1&t;0&t;c4&n; *          1&t;1&t;c6&n; *&n; *&n; *&n; */
DECL|function|lg_tdtp_e102p_tua6034
r_static
r_int
id|lg_tdtp_e102p_tua6034
c_func
(paren
r_struct
id|dvb_frontend_parameters
op_star
id|fep
comma
id|u8
id|pllbuf
(braket
l_int|4
)braket
)paren
(brace
id|u32
id|div
suffix:semicolon
id|u8
id|p3210
comma
id|p4
suffix:semicolon
DECL|macro|TUNER_MUL
mdefine_line|#define TUNER_MUL 62500
id|div
op_assign
(paren
id|fep-&gt;frequency
op_plus
l_int|36125000
op_plus
id|TUNER_MUL
op_div
l_int|2
)paren
op_div
id|TUNER_MUL
suffix:semicolon
r_if
c_cond
(paren
id|fep-&gt;frequency
OL
l_int|174500000
)paren
id|p3210
op_assign
l_int|1
suffix:semicolon
singleline_comment|// not supported by the tdtp_e102p
r_else
r_if
c_cond
(paren
id|fep-&gt;frequency
OL
l_int|230000000
)paren
singleline_comment|// VHF
id|p3210
op_assign
l_int|2
suffix:semicolon
r_else
id|p3210
op_assign
l_int|4
suffix:semicolon
r_if
c_cond
(paren
id|fep-&gt;u.ofdm.bandwidth
op_eq
id|BANDWIDTH_7_MHZ
)paren
id|p4
op_assign
l_int|0
suffix:semicolon
r_else
id|p4
op_assign
l_int|1
suffix:semicolon
id|pllbuf
(braket
l_int|0
)braket
op_assign
(paren
id|div
op_rshift
l_int|8
)paren
op_amp
l_int|0x7f
suffix:semicolon
id|pllbuf
(braket
l_int|1
)braket
op_assign
id|div
op_amp
l_int|0xff
suffix:semicolon
id|pllbuf
(braket
l_int|2
)braket
op_assign
l_int|0xce
suffix:semicolon
id|pllbuf
(braket
l_int|3
)braket
op_assign
(paren
id|p4
op_lshift
l_int|4
)paren
op_or
id|p3210
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|lg_tdtp_e102p_mt352_demod_init
r_static
r_int
id|lg_tdtp_e102p_mt352_demod_init
c_func
(paren
r_struct
id|dvb_frontend
op_star
id|fe
)paren
(brace
r_static
id|u8
id|mt352_clock_config
(braket
)braket
op_assign
(brace
l_int|0x89
comma
l_int|0xb0
comma
l_int|0x2d
)brace
suffix:semicolon
r_static
id|u8
id|mt352_reset
(braket
)braket
op_assign
(brace
l_int|0x50
comma
l_int|0x80
)brace
suffix:semicolon
r_static
id|u8
id|mt352_mclk_ratio
(braket
)braket
op_assign
(brace
l_int|0x8b
comma
l_int|0x00
)brace
suffix:semicolon
r_static
id|u8
id|mt352_adc_ctl_1_cfg
(braket
)braket
op_assign
(brace
l_int|0x8E
comma
l_int|0x40
)brace
suffix:semicolon
r_static
id|u8
id|mt352_agc_cfg
(braket
)braket
op_assign
(brace
l_int|0x67
comma
l_int|0x14
comma
l_int|0x22
)brace
suffix:semicolon
r_static
id|u8
id|mt352_sec_agc_cfg
(braket
)braket
op_assign
(brace
l_int|0x69
comma
l_int|0x00
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0x00
comma
l_int|0xff
comma
l_int|0x00
comma
l_int|0x40
comma
l_int|0x40
)brace
suffix:semicolon
r_static
id|u8
id|mt352_unk
(braket
)braket
op_assign
(brace
l_int|0xb5
comma
l_int|0x7a
)brace
suffix:semicolon
r_static
id|u8
id|mt352_acq_ctl
(braket
)braket
op_assign
(brace
l_int|0x53
comma
l_int|0x5f
)brace
suffix:semicolon
r_static
id|u8
id|mt352_input_freq_1
(braket
)braket
op_assign
(brace
l_int|0x56
comma
l_int|0xf1
comma
l_int|0x05
)brace
suffix:semicolon
singleline_comment|//&t;static u8 mt352_capt_range_cfg[] = { 0x75, 0x32 };
id|mt352_write
c_func
(paren
id|fe
comma
id|mt352_clock_config
comma
r_sizeof
(paren
id|mt352_clock_config
)paren
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|2000
)paren
suffix:semicolon
id|mt352_write
c_func
(paren
id|fe
comma
id|mt352_reset
comma
r_sizeof
(paren
id|mt352_reset
)paren
)paren
suffix:semicolon
id|mt352_write
c_func
(paren
id|fe
comma
id|mt352_mclk_ratio
comma
r_sizeof
(paren
id|mt352_mclk_ratio
)paren
)paren
suffix:semicolon
id|mt352_write
c_func
(paren
id|fe
comma
id|mt352_adc_ctl_1_cfg
comma
r_sizeof
(paren
id|mt352_adc_ctl_1_cfg
)paren
)paren
suffix:semicolon
id|mt352_write
c_func
(paren
id|fe
comma
id|mt352_agc_cfg
comma
r_sizeof
(paren
id|mt352_agc_cfg
)paren
)paren
suffix:semicolon
id|mt352_write
c_func
(paren
id|fe
comma
id|mt352_sec_agc_cfg
comma
r_sizeof
(paren
id|mt352_sec_agc_cfg
)paren
)paren
suffix:semicolon
id|mt352_write
c_func
(paren
id|fe
comma
id|mt352_unk
comma
r_sizeof
(paren
id|mt352_unk
)paren
)paren
suffix:semicolon
id|mt352_write
c_func
(paren
id|fe
comma
id|mt352_acq_ctl
comma
r_sizeof
(paren
id|mt352_acq_ctl
)paren
)paren
suffix:semicolon
id|mt352_write
c_func
(paren
id|fe
comma
id|mt352_input_freq_1
comma
r_sizeof
(paren
id|mt352_input_freq_1
)paren
)paren
suffix:semicolon
singleline_comment|//&t;mt352_write(fe, mt352_capt_range_cfg, sizeof(mt352_capt_range_cfg));
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dibusb_general_demod_init
r_static
r_int
id|dibusb_general_demod_init
c_func
(paren
r_struct
id|dvb_frontend
op_star
id|fe
)paren
(brace
r_struct
id|usb_dibusb
op_star
id|dib
op_assign
(paren
r_struct
id|usb_dibusb
op_star
)paren
id|fe-&gt;dvb-&gt;priv
suffix:semicolon
r_switch
c_cond
(paren
id|dib-&gt;dibdev-&gt;dev_cl-&gt;id
)paren
(brace
r_case
id|UMT2_0
suffix:colon
r_return
id|lg_tdtp_e102p_mt352_demod_init
c_func
(paren
id|fe
)paren
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* other device classes do not have device specific demod inits */
r_break
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dibusb_general_pll_addr
r_static
id|u8
id|dibusb_general_pll_addr
c_func
(paren
r_struct
id|dvb_frontend
op_star
id|fe
)paren
(brace
r_struct
id|usb_dibusb
op_star
id|dib
op_assign
(paren
r_struct
id|usb_dibusb
op_star
)paren
id|fe-&gt;dvb-&gt;priv
suffix:semicolon
r_return
id|dib-&gt;tuner-&gt;pll_addr
suffix:semicolon
)brace
DECL|function|dibusb_pll_i2c_helper
r_static
r_int
id|dibusb_pll_i2c_helper
c_func
(paren
r_struct
id|usb_dibusb
op_star
id|dib
comma
id|u8
id|pll_buf
(braket
l_int|5
)braket
comma
id|u8
id|buf
(braket
l_int|4
)braket
)paren
(brace
r_if
c_cond
(paren
id|pll_buf
op_eq
l_int|NULL
)paren
(brace
r_struct
id|i2c_msg
id|msg
op_assign
(brace
dot
id|addr
op_assign
id|dib-&gt;tuner-&gt;pll_addr
comma
dot
id|flags
op_assign
l_int|0
comma
dot
id|buf
op_assign
id|buf
comma
dot
id|len
op_assign
r_sizeof
(paren
id|buf
)paren
)brace
suffix:semicolon
r_if
c_cond
(paren
id|i2c_transfer
(paren
op_amp
id|dib-&gt;i2c_adap
comma
op_amp
id|msg
comma
l_int|1
)paren
op_ne
l_int|1
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|msleep
c_func
(paren
l_int|1
)paren
suffix:semicolon
)brace
r_else
(brace
id|pll_buf
(braket
l_int|0
)braket
op_assign
id|dib-&gt;tuner-&gt;pll_addr
op_lshift
l_int|1
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|pll_buf
(braket
l_int|1
)braket
comma
id|buf
comma
l_int|4
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dibusb_general_pll_init
r_static
r_int
id|dibusb_general_pll_init
c_func
(paren
r_struct
id|dvb_frontend
op_star
id|fe
comma
id|u8
id|pll_buf
(braket
l_int|5
)braket
)paren
(brace
r_struct
id|usb_dibusb
op_star
id|dib
op_assign
(paren
r_struct
id|usb_dibusb
op_star
)paren
id|fe-&gt;dvb-&gt;priv
suffix:semicolon
id|u8
id|buf
(braket
l_int|4
)braket
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|dib-&gt;tuner-&gt;id
)paren
(brace
r_case
id|DIBUSB_TUNER_COFDM_PANASONIC_ENV77H11D5
suffix:colon
id|ret
op_assign
id|panasonic_cofdm_env77h11d5_tda6650_init
c_func
(paren
id|fe
comma
id|buf
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ret
)paren
r_return
id|ret
suffix:semicolon
r_return
id|dibusb_pll_i2c_helper
c_func
(paren
id|dib
comma
id|pll_buf
comma
id|buf
)paren
suffix:semicolon
)brace
DECL|function|dibusb_general_pll_set
r_static
r_int
id|dibusb_general_pll_set
c_func
(paren
r_struct
id|dvb_frontend
op_star
id|fe
comma
r_struct
id|dvb_frontend_parameters
op_star
id|fep
comma
id|u8
id|pll_buf
(braket
l_int|5
)braket
)paren
(brace
r_struct
id|usb_dibusb
op_star
id|dib
op_assign
(paren
r_struct
id|usb_dibusb
op_star
)paren
id|fe-&gt;dvb-&gt;priv
suffix:semicolon
id|u8
id|buf
(braket
l_int|4
)braket
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|dib-&gt;tuner-&gt;id
)paren
(brace
r_case
id|DIBUSB_TUNER_CABLE_THOMSON
suffix:colon
id|ret
op_assign
id|thomson_cable_eu_pll_set
c_func
(paren
id|fep
comma
id|buf
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DIBUSB_TUNER_COFDM_PANASONIC_ENV57H1XD5
suffix:colon
id|ret
op_assign
id|panasonic_cofdm_env57h1xd5_pll_set
c_func
(paren
id|fep
comma
id|buf
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DIBUSB_TUNER_CABLE_LG_TDTP_E102P
suffix:colon
id|ret
op_assign
id|lg_tdtp_e102p_tua6034
c_func
(paren
id|fep
comma
id|buf
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DIBUSB_TUNER_COFDM_PANASONIC_ENV77H11D5
suffix:colon
id|ret
op_assign
id|panasonic_cofdm_env77h11d5_tda6650_set
c_func
(paren
id|fep
comma
id|buf
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|warn
c_func
(paren
l_string|&quot;no pll programming routine found for tuner %d.&bslash;n&quot;
comma
id|dib-&gt;tuner-&gt;id
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ret
)paren
r_return
id|ret
suffix:semicolon
r_return
id|dibusb_pll_i2c_helper
c_func
(paren
id|dib
comma
id|pll_buf
comma
id|buf
)paren
suffix:semicolon
)brace
eof
