multiline_comment|/*&n; *  setup.c, Setup for the ZAO Networks Capcella.&n; *&n; *  Copyright (C) 2002-2004  Yoichi Yuasa &lt;yuasa@hh.iij4u.or.jp&gt;&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/vr41xx/vr41xx.h&gt;
DECL|function|get_system_type
r_const
r_char
op_star
id|get_system_type
c_func
(paren
r_void
)paren
(brace
r_return
l_string|&quot;ZAO Networks Capcella&quot;
suffix:semicolon
)brace
DECL|function|zao_capcella_setup
r_static
r_int
id|zao_capcella_setup
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_SERIAL_8250
id|vr41xx_select_siu_interface
c_func
(paren
id|SIU_RS232C
comma
id|IRDA_NONE
)paren
suffix:semicolon
id|vr41xx_siu_init
c_func
(paren
)paren
suffix:semicolon
id|vr41xx_dsiu_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|zao_capcella_setup
id|early_initcall
c_func
(paren
id|zao_capcella_setup
)paren
suffix:semicolon
eof
