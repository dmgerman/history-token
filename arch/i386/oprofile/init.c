multiline_comment|/**&n; * @file init.c&n; *&n; * @remark Copyright 2002 OProfile authors&n; * @remark Read the file COPYING&n; *&n; * @author John Levon &lt;levon@movementarian.org&gt;&n; */
macro_line|#include &lt;linux/oprofile.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
multiline_comment|/* We support CPUs that have performance counters like the Pentium Pro&n; * with the NMI mode driver.&n; */
r_extern
r_int
id|nmi_init
c_func
(paren
r_struct
id|oprofile_operations
op_star
op_star
id|ops
)paren
suffix:semicolon
r_extern
r_void
id|nmi_exit
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|oprofile_arch_init
r_int
id|__init
id|oprofile_arch_init
c_func
(paren
r_struct
id|oprofile_operations
op_star
op_star
id|ops
)paren
(brace
macro_line|#ifdef CONFIG_X86_LOCAL_APIC
r_return
id|nmi_init
c_func
(paren
id|ops
)paren
suffix:semicolon
macro_line|#else
r_return
op_minus
id|ENODEV
suffix:semicolon
macro_line|#endif
)brace
DECL|function|oprofile_arch_exit
r_void
id|__exit
id|oprofile_arch_exit
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_X86_LOCAL_APIC
id|nmi_exit
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
)brace
eof
