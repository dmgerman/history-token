multiline_comment|/*&n; *  linux/arch/m68knommu/mm/fault.c&n; *&n; *  Copyright (C) 1998  D. Jeff Dionne &lt;jeff@lineo.ca&gt;,&n; *  Copyright (C) 2000  Lineo, Inc.  (www.lineo.com) &n; *&n; *  Based on:&n; *&n; *  linux/arch/m68k/mm/fault.c&n; *&n; *  Copyright (C) 1995  Hamish Macdonald&n; */
macro_line|#include &lt;linux/mman.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
r_extern
r_void
id|die_if_kernel
c_func
(paren
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
multiline_comment|/*&n; * This routine handles page faults.  It determines the problem, and&n; * then passes it off to one of the appropriate routines.&n; *&n; * error_code:&n; *&t;bit 0 == 0 means no page found, 1 means protection fault&n; *&t;bit 1 == 0 means read, 1 means write&n; *&n; * If this routine detects a bad access, it returns 1, otherwise it&n; * returns 0.&n; */
DECL|function|do_page_fault
id|asmlinkage
r_int
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
id|address
comma
r_int
r_int
id|error_code
)paren
(brace
macro_line|#ifdef DEBUG
id|printk
(paren
l_string|&quot;regs-&gt;sr=%#x, regs-&gt;pc=%#lx, address=%#lx, %ld&bslash;n&quot;
comma
id|regs-&gt;sr
comma
id|regs-&gt;pc
comma
id|address
comma
id|error_code
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t; * Oops. The kernel tried to access some bad page. We&squot;ll have to&n;&t; * terminate things with extreme prejudice.&n;&t; */
r_if
c_cond
(paren
(paren
r_int
r_int
)paren
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
id|printk
c_func
(paren
id|KERN_ALERT
l_string|&quot;Unable to handle kernel access&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; at virtual address %08lx&bslash;n&quot;
comma
id|address
)paren
suffix:semicolon
id|die_if_kernel
c_func
(paren
l_string|&quot;Oops&quot;
comma
id|regs
comma
id|error_code
)paren
suffix:semicolon
id|do_exit
c_func
(paren
id|SIGKILL
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
eof
