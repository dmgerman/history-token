multiline_comment|/*&n; *&t;linux/arch/alpha/kernel/err_marvel.c&n; *&n; *&t;Copyright (C) 2001 Jeff Wiedemeier (Compaq Computer Corporation)&n; *&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/console.h&gt;
macro_line|#include &lt;asm/core_marvel.h&gt;
macro_line|#include &lt;asm/hwrpb.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#include &quot;err_impl.h&quot;
macro_line|#include &quot;proto.h&quot;
r_void
DECL|function|marvel_machine_check
id|marvel_machine_check
c_func
(paren
id|u64
id|vector
comma
id|u64
id|la_ptr
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|el_subpacket
op_star
id|el_ptr
op_assign
(paren
r_struct
id|el_subpacket
op_star
)paren
id|la_ptr
suffix:semicolon
multiline_comment|/*&n;&t; * Sync the processor&n;&t; */
id|mb
c_func
(paren
)paren
suffix:semicolon
id|draina
c_func
(paren
)paren
suffix:semicolon
id|el_process_subpacket
c_func
(paren
id|el_ptr
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|vector
)paren
(brace
r_case
id|SCB_Q_SYSEVENT
suffix:colon
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;MARVEL SYSEVENT %ld&bslash;n&quot;
comma
id|vector
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SCB_Q_SYSMCHK
suffix:colon
r_case
id|SCB_Q_SYSERR
suffix:colon
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;MARVEL SYSMCHK/ERR %ld&bslash;n&quot;
comma
id|vector
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* Don&squot;t know it - pass it up.  */
r_return
id|ev7_machine_check
c_func
(paren
id|vector
comma
id|la_ptr
comma
id|regs
)paren
suffix:semicolon
)brace
multiline_comment|/* Release the logout frame.  */
id|wrmces
c_func
(paren
l_int|0x7
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
)brace
r_void
DECL|function|marvel_register_error_handlers
id|marvel_register_error_handlers
c_func
(paren
r_void
)paren
(brace
id|ev7_register_error_handlers
c_func
(paren
)paren
suffix:semicolon
)brace
eof
