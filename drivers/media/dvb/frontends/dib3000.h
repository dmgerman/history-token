multiline_comment|/*&n; * public header file of the frontend drivers for mobile DVB-T demodulators&n; * DiBcom 3000M-B and DiBcom 3000P/M-C (http://www.dibcom.fr/)&n; *&n; * Copyright (C) 2004-5 Patrick Boettcher (patrick.boettcher@desy.de)&n; *&n; * based on GPL code from DibCom, which has&n; *&n; * Copyright (C) 2004 Amaury Demol for DiBcom (ademol@dibcom.fr)&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License as&n; *&t;published by the Free Software Foundation, version 2.&n; *&n; * Acknowledgements&n; *&n; *  Amaury Demol (ademol@dibcom.fr) from DiBcom for providing specs and driver&n; *  sources, on which this driver (and the dvb-dibusb) are based.&n; *&n; * see Documentation/dvb/README.dibusb for more information&n; *&n; */
macro_line|#ifndef DIB3000_H
DECL|macro|DIB3000_H
mdefine_line|#define DIB3000_H
macro_line|#include &lt;linux/dvb/frontend.h&gt;
DECL|struct|dib3000_config
r_struct
id|dib3000_config
(brace
multiline_comment|/* the demodulator&squot;s i2c address */
DECL|member|demod_address
id|u8
id|demod_address
suffix:semicolon
multiline_comment|/* PLL maintenance and the i2c address of the PLL */
DECL|member|pll_addr
id|u8
(paren
op_star
id|pll_addr
)paren
(paren
r_struct
id|dvb_frontend
op_star
id|fe
)paren
suffix:semicolon
DECL|member|pll_init
r_int
(paren
op_star
id|pll_init
)paren
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
DECL|member|pll_set
r_int
(paren
op_star
id|pll_set
)paren
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
)brace
suffix:semicolon
DECL|struct|dib_fe_xfer_ops
r_struct
id|dib_fe_xfer_ops
(brace
multiline_comment|/* pid and transfer handling is done in the demodulator */
DECL|member|pid_parse
r_int
(paren
op_star
id|pid_parse
)paren
(paren
r_struct
id|dvb_frontend
op_star
id|fe
comma
r_int
id|onoff
)paren
suffix:semicolon
DECL|member|fifo_ctrl
r_int
(paren
op_star
id|fifo_ctrl
)paren
(paren
r_struct
id|dvb_frontend
op_star
id|fe
comma
r_int
id|onoff
)paren
suffix:semicolon
DECL|member|pid_ctrl
r_int
(paren
op_star
id|pid_ctrl
)paren
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
suffix:semicolon
DECL|member|tuner_pass_ctrl
r_int
(paren
op_star
id|tuner_pass_ctrl
)paren
(paren
r_struct
id|dvb_frontend
op_star
id|fe
comma
r_int
id|onoff
comma
id|u8
id|pll_ctrl
)paren
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|dvb_frontend
op_star
id|dib3000mb_attach
c_func
(paren
r_const
r_struct
id|dib3000_config
op_star
id|config
comma
r_struct
id|i2c_adapter
op_star
id|i2c
comma
r_struct
id|dib_fe_xfer_ops
op_star
id|xfer_ops
)paren
suffix:semicolon
r_extern
r_struct
id|dvb_frontend
op_star
id|dib3000mc_attach
c_func
(paren
r_const
r_struct
id|dib3000_config
op_star
id|config
comma
r_struct
id|i2c_adapter
op_star
id|i2c
comma
r_struct
id|dib_fe_xfer_ops
op_star
id|xfer_ops
)paren
suffix:semicolon
macro_line|#endif 
singleline_comment|// DIB3000_H
eof
