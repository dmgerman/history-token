multiline_comment|/*&n;    Driver for VES1893 and VES1993 QPSK Demodulators&n;&n;    Copyright (C) 1999 Convergence Integrated Media GmbH &lt;ralph@convergence.de&gt;&n;    Copyright (C) 2001 Ronny Strutz &lt;3des@elitedvb.de&gt;&n;    Copyright (C) 2002 Dennis Noermann &lt;dennis.noermann@noernet.de&gt;&n;    Copyright (C) 2002-2003 Andreas Oberritter &lt;obi@linuxtv.org&gt;&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n;*/
macro_line|#ifndef VES1X93_H
DECL|macro|VES1X93_H
mdefine_line|#define VES1X93_H
macro_line|#include &lt;linux/dvb/frontend.h&gt;
DECL|struct|ves1x93_config
r_struct
id|ves1x93_config
(brace
multiline_comment|/* the demodulator&squot;s i2c address */
DECL|member|demod_address
id|u8
id|demod_address
suffix:semicolon
multiline_comment|/* value of XIN to use */
DECL|member|xin
id|u32
id|xin
suffix:semicolon
multiline_comment|/* should PWM be inverted? */
DECL|member|invert_pwm
id|u8
id|invert_pwm
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* PLL maintenance */
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
)paren
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|dvb_frontend
op_star
id|ves1x93_attach
c_func
(paren
r_const
r_struct
id|ves1x93_config
op_star
id|config
comma
r_struct
id|i2c_adapter
op_star
id|i2c
)paren
suffix:semicolon
macro_line|#endif 
singleline_comment|// VES1X93_H
eof
