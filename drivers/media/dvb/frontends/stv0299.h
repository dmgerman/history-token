multiline_comment|/*&n;    Driver for ST STV0299 demodulator&n;&n;    Copyright (C) 2001-2002 Convergence Integrated Media GmbH&n;&t;&lt;ralph@convergence.de&gt;,&n;&t;&lt;holger@convergence.de&gt;,&n;&t;&lt;js@convergence.de&gt;&n;&n;&n;    Philips SU1278/SH&n;&n;    Copyright (C) 2002 by Peter Schildmann &lt;peter.schildmann@web.de&gt;&n;&n;&n;    LG TDQF-S001F&n;&n;    Copyright (C) 2002 Felix Domke &lt;tmbinc@elitedvb.net&gt;&n;&t;&t;     &amp; Andreas Oberritter &lt;obi@linuxtv.org&gt;&n;&n;&n;    Support for Samsung TBMU24112IMB used on Technisat SkyStar2 rev. 2.6B&n;&n;    Copyright (C) 2003 Vadim Catana &lt;skystar@moldova.cc&gt;:&n;&n;    Support for Philips SU1278 on Technotrend hardware&n;&n;    Copyright (C) 2004 Andrew de Quincey &lt;adq_dvb@lidskialf.net&gt;&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n;*/
macro_line|#ifndef STV0299_H
DECL|macro|STV0299_H
mdefine_line|#define STV0299_H
macro_line|#include &lt;linux/dvb/frontend.h&gt;
macro_line|#include &quot;dvb_frontend.h&quot;
DECL|macro|STV0229_LOCKOUTPUT_0
mdefine_line|#define STV0229_LOCKOUTPUT_0  0
DECL|macro|STV0229_LOCKOUTPUT_1
mdefine_line|#define STV0229_LOCKOUTPUT_1  1
DECL|macro|STV0229_LOCKOUTPUT_CF
mdefine_line|#define STV0229_LOCKOUTPUT_CF 2
DECL|macro|STV0229_LOCKOUTPUT_LK
mdefine_line|#define STV0229_LOCKOUTPUT_LK 3
DECL|macro|STV0299_VOLT13_OP0
mdefine_line|#define STV0299_VOLT13_OP0 0
DECL|macro|STV0299_VOLT13_OP1
mdefine_line|#define STV0299_VOLT13_OP1 1
DECL|struct|stv0299_config
r_struct
id|stv0299_config
(brace
multiline_comment|/* the demodulator&squot;s i2c address */
DECL|member|demod_address
id|u8
id|demod_address
suffix:semicolon
multiline_comment|/* inittab - array of pairs of values.&n;&t; * First of each pair is the register, second is the value.&n;&t; * List should be terminated with an 0xff, 0xff pair.&n;&t; */
DECL|member|inittab
id|u8
op_star
id|inittab
suffix:semicolon
multiline_comment|/* master clock to use */
DECL|member|mclk
id|u32
id|mclk
suffix:semicolon
multiline_comment|/* does the inversion require inversion? */
DECL|member|invert
id|u8
id|invert
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Should the enhanced tuning code be used? */
DECL|member|enhanced_tuning
id|u8
id|enhanced_tuning
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Skip reinitialisation? */
DECL|member|skip_reinit
id|u8
id|skip_reinit
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* LOCK OUTPUT setting */
DECL|member|lock_output
id|u8
id|lock_output
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* Is 13v controlled by OP0 or OP1? */
DECL|member|volt13_op0_op1
id|u8
id|volt13_op0_op1
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* minimum delay before retuning */
DECL|member|min_delay_ms
r_int
id|min_delay_ms
suffix:semicolon
multiline_comment|/* Set the symbol rate */
DECL|member|set_symbol_rate
r_int
(paren
op_star
id|set_symbol_rate
)paren
(paren
r_struct
id|dvb_frontend
op_star
id|fe
comma
id|u32
id|srate
comma
id|u32
id|ratio
)paren
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
r_int
id|stv0299_writereg
(paren
r_struct
id|dvb_frontend
op_star
id|fe
comma
id|u8
id|reg
comma
id|u8
id|data
)paren
suffix:semicolon
r_extern
r_struct
id|dvb_frontend
op_star
id|stv0299_attach
c_func
(paren
r_const
r_struct
id|stv0299_config
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
singleline_comment|// STV0299_H
eof
