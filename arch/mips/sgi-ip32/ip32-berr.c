multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1994, 1995, 1996, 1999, 2000 by Ralf Baechle&n; * Copyright (C) 1999, 2000 by Silicon Graphics&n; * Copyright (C) 2002  Maciej W. Rozycki&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;asm/traps.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/addrspace.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/tlbdebug.h&gt;
DECL|function|ip32_be_handler
r_int
id|ip32_be_handler
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
id|is_fixup
)paren
(brace
r_int
id|data
op_assign
id|regs-&gt;cp0_cause
op_amp
l_int|4
suffix:semicolon
r_if
c_cond
(paren
id|is_fixup
)paren
r_return
id|MIPS_BE_FIXUP
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Got %cbe at 0x%lx&bslash;n&quot;
comma
id|data
ques
c_cond
l_char|&squot;d&squot;
suffix:colon
l_char|&squot;i&squot;
comma
id|regs-&gt;cp0_epc
)paren
suffix:semicolon
id|show_regs
c_func
(paren
id|regs
)paren
suffix:semicolon
id|dump_tlb_all
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
suffix:semicolon
)brace
id|force_sig
c_func
(paren
id|SIGBUS
comma
id|current
)paren
suffix:semicolon
)brace
DECL|function|ip32_be_init
r_void
id|__init
id|ip32_be_init
c_func
(paren
r_void
)paren
(brace
id|board_be_handler
op_assign
id|ip32_be_handler
suffix:semicolon
)brace
eof
