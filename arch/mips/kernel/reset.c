multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2001 by Ralf Baechle&n; * Copyright (C) 2001 MIPS Technologies, Inc.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/reboot.h&gt;
macro_line|#include &lt;asm/reboot.h&gt;
multiline_comment|/*&n; * Urgs ...  Too many MIPS machines to handle this in a generic way.&n; * So handle all using function pointers to machine specific&n; * functions.&n; */
DECL|variable|_machine_restart
r_void
(paren
op_star
id|_machine_restart
)paren
(paren
r_char
op_star
id|command
)paren
suffix:semicolon
DECL|variable|_machine_halt
r_void
(paren
op_star
id|_machine_halt
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|variable|_machine_power_off
r_void
(paren
op_star
id|_machine_power_off
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|function|machine_restart
r_void
id|machine_restart
c_func
(paren
r_char
op_star
id|command
)paren
(brace
id|_machine_restart
c_func
(paren
id|command
)paren
suffix:semicolon
)brace
DECL|variable|machine_restart
id|EXPORT_SYMBOL
c_func
(paren
id|machine_restart
)paren
suffix:semicolon
DECL|function|machine_halt
r_void
id|machine_halt
c_func
(paren
r_void
)paren
(brace
id|_machine_halt
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|variable|machine_halt
id|EXPORT_SYMBOL
c_func
(paren
id|machine_halt
)paren
suffix:semicolon
DECL|function|machine_power_off
r_void
id|machine_power_off
c_func
(paren
r_void
)paren
(brace
id|_machine_power_off
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|variable|machine_power_off
id|EXPORT_SYMBOL
c_func
(paren
id|machine_power_off
)paren
suffix:semicolon
eof
