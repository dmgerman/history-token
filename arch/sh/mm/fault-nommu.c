multiline_comment|/* &n; * arch/sh/mm/fault-nommu.c&n; *&n; * Copyright (C) 2002 Paul Mundt&n; *&n; * Based on linux/arch/sh/mm/fault.c:&n; *  Copyright (C) 1999  Niibe Yutaka&n; *&n; * Released under the terms of the GNU GPL v2.0.&n; */
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/mman.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/hardirq.h&gt;
macro_line|#include &lt;asm/mmu_context.h&gt;
macro_line|#include &lt;asm/cacheflush.h&gt;
macro_line|#if defined(CONFIG_SH_KGDB)
macro_line|#include &lt;asm/kgdb.h&gt;
macro_line|#endif
r_extern
r_void
id|die
c_func
(paren
r_const
r_char
op_star
comma
r_struct
id|pt_regs
op_star
comma
r_int
)paren
suffix:semicolon
multiline_comment|/*&n; * This routine handles page faults.  It determines the address,&n; * and the problem, and then passes it off to one of the appropriate&n; * routines.&n; */
DECL|function|do_page_fault
id|asmlinkage
r_void
id|do_page_fault
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
r_int
id|writeaccess
comma
r_int
r_int
id|address
)paren
(brace
macro_line|#if defined(CONFIG_SH_KGDB)
r_if
c_cond
(paren
id|kgdb_nofault
op_logical_and
id|kgdb_bus_err_hook
)paren
id|kgdb_bus_err_hook
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t; * Oops. The kernel tried to access some bad page. We&squot;ll have to&n;&t; * terminate things with extreme prejudice.&n;&t; *&n;&t; */
r_if
c_cond
(paren
id|address
OL
id|PAGE_SIZE
)paren
(brace
id|printk
c_func
(paren
id|KERN_ALERT
l_string|&quot;Unable to handle kernel NULL pointer dereference&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_ALERT
l_string|&quot;Unable to handle kernel paging request&quot;
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot; at virtual address %08lx&bslash;n&quot;
comma
id|address
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ALERT
l_string|&quot;pc = %08lx&bslash;n&quot;
comma
id|regs-&gt;pc
)paren
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;Oops&quot;
comma
id|regs
comma
id|writeaccess
)paren
suffix:semicolon
id|do_exit
c_func
(paren
id|SIGKILL
)paren
suffix:semicolon
)brace
DECL|function|__do_page_fault
id|asmlinkage
r_int
id|__do_page_fault
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
r_int
id|writeaccess
comma
r_int
r_int
id|address
)paren
(brace
macro_line|#if defined(CONFIG_SH_KGDB)
r_if
c_cond
(paren
id|kgdb_nofault
op_logical_and
id|kgdb_bus_err_hook
)paren
id|kgdb_bus_err_hook
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|address
op_ge
id|TASK_SIZE
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
