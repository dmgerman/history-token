multiline_comment|/*&n; * at76c651.c&n; *&n; * Atmel DVB-C Frontend Driver (at76c651)&n; *&n; * Copyright (C) 2001 fnbrd &lt;fnbrd@gmx.de&gt;&n; *             &amp; 2002-2004 Andreas Oberritter &lt;obi@linuxtv.org&gt;&n; *             &amp; 2003 Wolfram Joost &lt;dbox2@frokaschwei.de&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; * AT76C651&n; * http://www.nalanda.nitc.ac.in/industry/datasheets/atmel/acrobat/doc1293.pdf&n; * http://www.atmel.com/atmel/acrobat/doc1320.pdf&n; */
macro_line|#ifndef AT76C651_H
DECL|macro|AT76C651_H
mdefine_line|#define AT76C651_H
macro_line|#include &lt;linux/dvb/frontend.h&gt;
DECL|struct|at76c651_config
r_struct
id|at76c651_config
(brace
multiline_comment|/* the demodulator&squot;s i2c address */
DECL|member|demod_address
id|u8
id|demod_address
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
id|at76c651_attach
c_func
(paren
r_const
r_struct
id|at76c651_config
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
singleline_comment|// AT76C651_H
eof
