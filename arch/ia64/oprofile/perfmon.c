multiline_comment|/**&n; * @file perfmon.c&n; *&n; * @remark Copyright 2003 OProfile authors&n; * @remark Read the file COPYING&n; *&n; * @author John Levon &lt;levon@movementarian.org&gt;&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/oprofile.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;asm/perfmon.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/errno.h&gt;
DECL|variable|allow_ints
r_static
r_int
id|allow_ints
suffix:semicolon
r_static
r_int
DECL|function|perfmon_handler
id|perfmon_handler
c_func
(paren
r_struct
id|task_struct
op_star
id|task
comma
r_void
op_star
id|buf
comma
id|pfm_ovfl_arg_t
op_star
id|arg
comma
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
r_int
id|stamp
)paren
(brace
r_int
id|event
op_assign
id|arg-&gt;pmd_eventid
suffix:semicolon
id|arg-&gt;ovfl_ctrl.bits.reset_ovfl_pmds
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* the owner of the oprofile event buffer may have exited&n;&t; * without perfmon being shutdown (e.g. SIGSEGV)&n;&t; */
r_if
c_cond
(paren
id|allow_ints
)paren
id|oprofile_add_sample
c_func
(paren
id|regs
comma
id|event
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|perfmon_start
r_static
r_int
id|perfmon_start
c_func
(paren
r_void
)paren
(brace
id|allow_ints
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|perfmon_stop
r_static
r_void
id|perfmon_stop
c_func
(paren
r_void
)paren
(brace
id|allow_ints
op_assign
l_int|0
suffix:semicolon
)brace
DECL|macro|OPROFILE_FMT_UUID
mdefine_line|#define OPROFILE_FMT_UUID { &bslash;&n;&t;0x77, 0x7a, 0x6e, 0x61, 0x20, 0x65, 0x73, 0x69, 0x74, 0x6e, 0x72, 0x20, 0x61, 0x65, 0x0a, 0x6c }
DECL|variable|oprofile_fmt
r_static
id|pfm_buffer_fmt_t
id|oprofile_fmt
op_assign
(brace
dot
id|fmt_name
op_assign
l_string|&quot;oprofile_format&quot;
comma
dot
id|fmt_uuid
op_assign
id|OPROFILE_FMT_UUID
comma
dot
id|fmt_handler
op_assign
id|perfmon_handler
comma
)brace
suffix:semicolon
DECL|function|get_cpu_type
r_static
r_char
op_star
id|get_cpu_type
c_func
(paren
r_void
)paren
(brace
id|__u8
id|family
op_assign
id|local_cpu_data-&gt;family
suffix:semicolon
r_switch
c_cond
(paren
id|family
)paren
(brace
r_case
l_int|0x07
suffix:colon
r_return
l_string|&quot;ia64/itanium&quot;
suffix:semicolon
r_case
l_int|0x1f
suffix:colon
r_return
l_string|&quot;ia64/itanium2&quot;
suffix:semicolon
r_default
suffix:colon
r_return
l_string|&quot;ia64/ia64&quot;
suffix:semicolon
)brace
)brace
multiline_comment|/* all the ops are handled via userspace for IA64 perfmon */
DECL|variable|using_perfmon
r_static
r_int
id|using_perfmon
suffix:semicolon
DECL|function|perfmon_init
r_int
id|perfmon_init
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
id|pfm_register_buffer_fmt
c_func
(paren
op_amp
id|oprofile_fmt
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|ops-&gt;cpu_type
op_assign
id|get_cpu_type
c_func
(paren
)paren
suffix:semicolon
id|ops-&gt;start
op_assign
id|perfmon_start
suffix:semicolon
id|ops-&gt;stop
op_assign
id|perfmon_stop
suffix:semicolon
id|using_perfmon
op_assign
l_int|1
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;oprofile: using perfmon.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|perfmon_exit
r_void
id|perfmon_exit
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|using_perfmon
)paren
r_return
suffix:semicolon
id|pfm_unregister_buffer_fmt
c_func
(paren
id|oprofile_fmt.fmt_uuid
)paren
suffix:semicolon
)brace
eof
