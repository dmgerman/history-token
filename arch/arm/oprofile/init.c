multiline_comment|/**&n; * @file init.c&n; *&n; * @remark Copyright 2004 Oprofile Authors&n; * @remark Read the file COPYING&n; *&n; * @author Zwane Mwaikambo&n; */
macro_line|#include &lt;linux/oprofile.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &quot;op_arm_model.h&quot;
DECL|function|oprofile_arch_init
r_int
id|__init
id|oprofile_arch_init
c_func
(paren
r_struct
id|oprofile_operations
op_star
id|ops
)paren
(brace
r_int
id|ret
op_assign
op_minus
id|ENODEV
suffix:semicolon
macro_line|#ifdef CONFIG_CPU_XSCALE
id|ret
op_assign
id|pmu_init
c_func
(paren
id|ops
comma
op_amp
id|op_xscale_spec
)paren
suffix:semicolon
macro_line|#endif
r_return
id|ret
suffix:semicolon
)brace
DECL|function|oprofile_arch_exit
r_void
id|oprofile_arch_exit
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_CPU_XSCALE
id|pmu_exit
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
)brace
eof
