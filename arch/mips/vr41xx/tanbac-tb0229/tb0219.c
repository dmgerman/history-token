multiline_comment|/*&n; *  tb0219.c, Setup for the TANBAC TB0219&n; *&n; *  Copyright (C) 2003  Megasolution Inc. &lt;matsu@megasolution.jp&gt;&n; *  Copyright (C) 2004  Yoichi Yuasa &lt;yuasa@hh.iij4u.or.jp&gt;&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/reboot.h&gt;
DECL|macro|TB0219_RESET_REGS
mdefine_line|#define TB0219_RESET_REGS&t;KSEG1ADDR(0x0a00000e)
DECL|macro|tb0219_hard_reset
mdefine_line|#define tb0219_hard_reset()&t;writew(0, TB0219_RESET_REGS)
DECL|function|tanbac_tb0219_restart
r_static
r_void
id|tanbac_tb0219_restart
c_func
(paren
r_char
op_star
id|command
)paren
(brace
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
id|tb0219_hard_reset
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|tanbac_tb0219_setup
r_static
r_int
id|__init
id|tanbac_tb0219_setup
c_func
(paren
r_void
)paren
(brace
id|_machine_restart
op_assign
id|tanbac_tb0219_restart
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|tanbac_tb0219_setup
id|early_initcall
c_func
(paren
id|tanbac_tb0219_setup
)paren
suffix:semicolon
eof
