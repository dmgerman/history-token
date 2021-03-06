multiline_comment|/*&n; *  Driver for Zarlink DVB-T MT352 demodulator&n; *&n; *  Written by Holger Waechtler &lt;holger@qanu.de&gt;&n; *&t; and Daniel Mack &lt;daniel@qanu.de&gt;&n; *&n; *  AVerMedia AVerTV DVB-T 771 support by&n; *       Wolfram Joost &lt;dbox2@frokaschwei.de&gt;&n; *&n; *  Support for Samsung TDTC9251DH01C(M) tuner&n; *  Copyright (C) 2004 Antonio Mancuso &lt;antonio.mancuso@digitaltelevision.it&gt;&n; *                     Amauri  Celani  &lt;acelani@essegi.net&gt;&n; *&n; *  DVICO FusionHDTV DVB-T1 and DVICO FusionHDTV DVB-T Lite support by&n; *       Christopher Pascoe &lt;c.pascoe@itee.uq.edu.au&gt;&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.=&n; */
macro_line|#ifndef MT352_H
DECL|macro|MT352_H
mdefine_line|#define MT352_H
macro_line|#include &lt;linux/dvb/frontend.h&gt;
DECL|struct|mt352_config
r_struct
id|mt352_config
(brace
multiline_comment|/* the demodulator&squot;s i2c address */
DECL|member|demod_address
id|u8
id|demod_address
suffix:semicolon
multiline_comment|/* frequencies in kHz */
DECL|member|adc_clock
r_int
id|adc_clock
suffix:semicolon
singleline_comment|// default: 20480
DECL|member|if2
r_int
id|if2
suffix:semicolon
singleline_comment|// default: 36166
multiline_comment|/* set if no pll is connected to the secondary i2c bus */
DECL|member|no_tuner
r_int
id|no_tuner
suffix:semicolon
multiline_comment|/* Initialise the demodulator and PLL. Cannot be NULL */
DECL|member|demod_init
r_int
(paren
op_star
id|demod_init
)paren
(paren
r_struct
id|dvb_frontend
op_star
id|fe
)paren
suffix:semicolon
multiline_comment|/* PLL setup - fill out the supplied 5 byte buffer with your PLL settings.&n;&t; * byte0: Set to pll i2c address (nonlinux; left shifted by 1)&n;&t; * byte1-4: PLL configuration.&n;&t; */
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
op_star
id|pllbuf
)paren
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|dvb_frontend
op_star
id|mt352_attach
c_func
(paren
r_const
r_struct
id|mt352_config
op_star
id|config
comma
r_struct
id|i2c_adapter
op_star
id|i2c
)paren
suffix:semicolon
r_extern
r_int
id|mt352_write
c_func
(paren
r_struct
id|dvb_frontend
op_star
id|fe
comma
id|u8
op_star
id|ibuf
comma
r_int
id|ilen
)paren
suffix:semicolon
r_extern
r_int
id|mt352_read
c_func
(paren
r_struct
id|dvb_frontend
op_star
id|fe
comma
id|u8
id|reg
)paren
suffix:semicolon
macro_line|#endif 
singleline_comment|// MT352_H
multiline_comment|/*&n; * Local variables:&n; * c-basic-offset: 8&n; * End:&n; */
eof
