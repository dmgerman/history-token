multiline_comment|/*&n; * arch/sh/oprofile/op_model_sh7750.c&n; *&n; * OProfile support for SH7750/SH7750S Performance Counters&n; *&n; * Copyright (C) 2003, 2004  Paul Mundt&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/oprofile.h&gt;
macro_line|#include &lt;linux/profile.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/notifier.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/io.h&gt;
DECL|macro|PM_CR_BASE
mdefine_line|#define PM_CR_BASE&t;0xff000084&t;/* 16-bit */
DECL|macro|PM_CTR_BASE
mdefine_line|#define PM_CTR_BASE&t;0xff100004&t;/* 32-bit */
DECL|macro|PMCR1
mdefine_line|#define PMCR1&t;&t;(PM_CR_BASE  + 0x00)
DECL|macro|PMCR2
mdefine_line|#define PMCR2&t;&t;(PM_CR_BASE  + 0x04)
DECL|macro|PMCTR1H
mdefine_line|#define PMCTR1H&t;&t;(PM_CTR_BASE + 0x00)
DECL|macro|PMCTR1L
mdefine_line|#define PMCTR1L&t;&t;(PM_CTR_BASE + 0x04)
DECL|macro|PMCTR2H
mdefine_line|#define PMCTR2H&t;&t;(PM_CTR_BASE + 0x08)
DECL|macro|PMCTR2L
mdefine_line|#define PMCTR2L&t;&t;(PM_CTR_BASE + 0x0c)
DECL|macro|PMCR_PMM_MASK
mdefine_line|#define PMCR_PMM_MASK&t;0x0000003f
DECL|macro|PMCR_CLKF
mdefine_line|#define PMCR_CLKF&t;0x00000100
DECL|macro|PMCR_PMCLR
mdefine_line|#define PMCR_PMCLR&t;0x00002000
DECL|macro|PMCR_PMST
mdefine_line|#define PMCR_PMST&t;0x00004000
DECL|macro|PMCR_PMEN
mdefine_line|#define PMCR_PMEN&t;0x00008000
DECL|macro|PMCR_ENABLE
mdefine_line|#define PMCR_ENABLE&t;(PMCR_PMST | PMCR_PMEN)
multiline_comment|/*&n; * SH7750/SH7750S have 2 perf counters&n; */
DECL|macro|NR_CNTRS
mdefine_line|#define NR_CNTRS&t;2
r_extern
r_const
r_char
op_star
id|get_cpu_subtype
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|struct|op_counter_config
r_struct
id|op_counter_config
(brace
DECL|member|enabled
r_int
r_int
id|enabled
suffix:semicolon
DECL|member|event
r_int
r_int
id|event
suffix:semicolon
DECL|member|count
r_int
r_int
id|count
suffix:semicolon
multiline_comment|/* Dummy values for userspace tool compliance */
DECL|member|kernel
r_int
r_int
id|kernel
suffix:semicolon
DECL|member|user
r_int
r_int
id|user
suffix:semicolon
DECL|member|unit_mask
r_int
r_int
id|unit_mask
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|ctr
r_static
r_struct
id|op_counter_config
id|ctr
(braket
id|NR_CNTRS
)braket
suffix:semicolon
multiline_comment|/*&n; * There are a number of events supported by each counter (33 in total).&n; * Since we have 2 counters, each counter will take the event code as it&n; * corresponds to the PMCR PMM setting. Each counter can be configured&n; * independently.&n; *&n; *&t;Event Code&t;Description&n; *&t;----------&t;-----------&n; *&n; *&t;0x01&t;&t;Operand read access&n; *&t;0x02&t;&t;Operand write access&n; *&t;0x03&t;&t;UTLB miss&n; *&t;0x04&t;&t;Operand cache read miss&n; *&t;0x05&t;&t;Operand cache write miss&n; *&t;0x06&t;&t;Instruction fetch (w/ cache)&n; *&t;0x07&t;&t;Instruction TLB miss&n; *&t;0x08&t;&t;Instruction cache miss&n; *&t;0x09&t;&t;All operand accesses&n; *&t;0x0a&t;&t;All instruction accesses&n; *&t;0x0b&t;&t;OC RAM operand access&n; *&t;0x0d&t;&t;On-chip I/O space access&n; *&t;0x0e&t;&t;Operand access (r/w)&n; *&t;0x0f&t;&t;Operand cache miss (r/w)&n; *&t;0x10&t;&t;Branch instruction&n; *&t;0x11&t;&t;Branch taken&n; *&t;0x12&t;&t;BSR/BSRF/JSR&n; *&t;0x13&t;&t;Instruction execution&n; *&t;0x14&t;&t;Instruction execution in parallel&n; *&t;0x15&t;&t;FPU Instruction execution&n; *&t;0x16&t;&t;Interrupt&n; *&t;0x17&t;&t;NMI&n; *&t;0x18&t;&t;trapa instruction execution&n; *&t;0x19&t;&t;UBCA match&n; *&t;0x1a&t;&t;UBCB match&n; *&t;0x21&t;&t;Instruction cache fill&n; *&t;0x22&t;&t;Operand cache fill&n; *&t;0x23&t;&t;Elapsed time&n; *&t;0x24&t;&t;Pipeline freeze by I-cache miss&n; *&t;0x25&t;&t;Pipeline freeze by D-cache miss&n; *&t;0x27&t;&t;Pipeline freeze by branch instruction&n; *&t;0x28&t;&t;Pipeline freeze by CPU register&n; *&t;0x29&t;&t;Pipeline freeze by FPU&n; *&n; * Unfortunately we don&squot;t have a native exception or interrupt for counter&n; * overflow (although since these counters can run for 16.3 days without&n; * overflowing, it&squot;s not really necessary).&n; *&n; * OProfile on the other hand likes to have samples taken periodically, so&n; * for now we just piggyback the timer interrupt to get the expected&n; * behavior.&n; */
DECL|function|sh7750_timer_notify
r_static
r_int
id|sh7750_timer_notify
c_func
(paren
r_struct
id|notifier_block
op_star
id|self
comma
r_int
r_int
id|val
comma
r_void
op_star
id|regs
)paren
(brace
id|oprofile_add_sample
c_func
(paren
(paren
r_struct
id|pt_regs
op_star
)paren
id|regs
comma
l_int|0
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|sh7750_timer_notifier
r_static
r_struct
id|notifier_block
id|sh7750_timer_notifier
op_assign
(brace
dot
id|notifier_call
op_assign
id|sh7750_timer_notify
comma
)brace
suffix:semicolon
DECL|function|sh7750_read_counter
r_static
id|u64
id|sh7750_read_counter
c_func
(paren
r_int
id|counter
)paren
(brace
id|u32
id|hi
comma
id|lo
suffix:semicolon
id|hi
op_assign
(paren
id|counter
op_eq
l_int|0
)paren
ques
c_cond
id|ctrl_inl
c_func
(paren
id|PMCTR1H
)paren
suffix:colon
id|ctrl_inl
c_func
(paren
id|PMCTR2H
)paren
suffix:semicolon
id|lo
op_assign
(paren
id|counter
op_eq
l_int|0
)paren
ques
c_cond
id|ctrl_inl
c_func
(paren
id|PMCTR1L
)paren
suffix:colon
id|ctrl_inl
c_func
(paren
id|PMCTR2L
)paren
suffix:semicolon
r_return
(paren
id|u64
)paren
(paren
(paren
id|u64
)paren
(paren
id|hi
op_amp
l_int|0xffff
)paren
op_lshift
l_int|32
)paren
op_or
id|lo
suffix:semicolon
)brace
multiline_comment|/*&n; * Files will be in a path like:&n; *&n; *  /&lt;oprofilefs mount point&gt;/&lt;counter number&gt;/&lt;file&gt;&n; *&n; * So when dealing with &lt;file&gt;, we look to the parent dentry for the counter&n; * number.&n; */
DECL|function|to_counter
r_static
r_inline
r_int
id|to_counter
c_func
(paren
r_struct
id|file
op_star
id|file
)paren
(brace
r_const
r_int
r_char
op_star
id|name
op_assign
id|file-&gt;f_dentry-&gt;d_parent-&gt;d_name.name
suffix:semicolon
r_return
(paren
r_int
)paren
id|simple_strtol
c_func
(paren
id|name
comma
l_int|NULL
comma
l_int|10
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * XXX: We have 48-bit counters, so we&squot;re probably going to want something&n; * more along the lines of oprofilefs_ullong_to_user().. Truncating to&n; * unsigned long works fine for now though, as long as we don&squot;t attempt to&n; * profile for too horribly long.&n; */
DECL|function|sh7750_read_count
r_static
id|ssize_t
id|sh7750_read_count
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_char
id|__user
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_int
id|counter
op_assign
id|to_counter
c_func
(paren
id|file
)paren
suffix:semicolon
id|u64
id|val
op_assign
id|sh7750_read_counter
c_func
(paren
id|counter
)paren
suffix:semicolon
r_return
id|oprofilefs_ulong_to_user
c_func
(paren
(paren
r_int
r_int
)paren
id|val
comma
id|buf
comma
id|count
comma
id|ppos
)paren
suffix:semicolon
)brace
DECL|function|sh7750_write_count
r_static
id|ssize_t
id|sh7750_write_count
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_char
id|__user
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_int
id|counter
op_assign
id|to_counter
c_func
(paren
id|file
)paren
suffix:semicolon
r_int
r_int
id|val
suffix:semicolon
r_if
c_cond
(paren
id|oprofilefs_ulong_from_user
c_func
(paren
op_amp
id|val
comma
id|buf
comma
id|count
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
multiline_comment|/*&n;&t; * Any write will clear the counter, although only 0 should be&n;&t; * written for this purpose, as we do not support setting the&n;&t; * counter to an arbitrary value.&n;&t; */
id|WARN_ON
c_func
(paren
id|val
op_ne
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|counter
op_eq
l_int|0
)paren
(brace
id|ctrl_outw
c_func
(paren
id|ctrl_inw
c_func
(paren
id|PMCR1
)paren
op_or
id|PMCR_PMCLR
comma
id|PMCR1
)paren
suffix:semicolon
)brace
r_else
(brace
id|ctrl_outw
c_func
(paren
id|ctrl_inw
c_func
(paren
id|PMCR2
)paren
op_or
id|PMCR_PMCLR
comma
id|PMCR2
)paren
suffix:semicolon
)brace
r_return
id|count
suffix:semicolon
)brace
DECL|variable|count_fops
r_static
r_struct
id|file_operations
id|count_fops
op_assign
(brace
dot
id|read
op_assign
id|sh7750_read_count
comma
dot
id|write
op_assign
id|sh7750_write_count
comma
)brace
suffix:semicolon
DECL|function|sh7750_perf_counter_create_files
r_static
r_int
id|sh7750_perf_counter_create_files
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|dentry
op_star
id|root
)paren
(brace
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NR_CNTRS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|dentry
op_star
id|dir
suffix:semicolon
r_char
id|buf
(braket
l_int|3
)braket
suffix:semicolon
id|snprintf
c_func
(paren
id|buf
comma
r_sizeof
(paren
id|buf
)paren
comma
l_string|&quot;%d&quot;
comma
id|i
)paren
suffix:semicolon
id|dir
op_assign
id|oprofilefs_mkdir
c_func
(paren
id|sb
comma
id|root
comma
id|buf
)paren
suffix:semicolon
id|oprofilefs_create_ulong
c_func
(paren
id|sb
comma
id|dir
comma
l_string|&quot;enabled&quot;
comma
op_amp
id|ctr
(braket
id|i
)braket
dot
id|enabled
)paren
suffix:semicolon
id|oprofilefs_create_ulong
c_func
(paren
id|sb
comma
id|dir
comma
l_string|&quot;event&quot;
comma
op_amp
id|ctr
(braket
id|i
)braket
dot
id|event
)paren
suffix:semicolon
id|oprofilefs_create_file
c_func
(paren
id|sb
comma
id|dir
comma
l_string|&quot;count&quot;
comma
op_amp
id|count_fops
)paren
suffix:semicolon
multiline_comment|/* Dummy entries */
id|oprofilefs_create_ulong
c_func
(paren
id|sb
comma
id|dir
comma
l_string|&quot;kernel&quot;
comma
op_amp
id|ctr
(braket
id|i
)braket
dot
id|kernel
)paren
suffix:semicolon
id|oprofilefs_create_ulong
c_func
(paren
id|sb
comma
id|dir
comma
l_string|&quot;user&quot;
comma
op_amp
id|ctr
(braket
id|i
)braket
dot
id|user
)paren
suffix:semicolon
id|oprofilefs_create_ulong
c_func
(paren
id|sb
comma
id|dir
comma
l_string|&quot;unit_mask&quot;
comma
op_amp
id|ctr
(braket
id|i
)braket
dot
id|unit_mask
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sh7750_perf_counter_start
r_static
r_int
id|sh7750_perf_counter_start
c_func
(paren
r_void
)paren
(brace
id|u16
id|pmcr
suffix:semicolon
multiline_comment|/* Enable counter 1 */
r_if
c_cond
(paren
id|ctr
(braket
l_int|0
)braket
dot
id|enabled
)paren
(brace
id|pmcr
op_assign
id|ctrl_inw
c_func
(paren
id|PMCR1
)paren
suffix:semicolon
id|WARN_ON
c_func
(paren
id|pmcr
op_amp
id|PMCR_PMEN
)paren
suffix:semicolon
id|pmcr
op_and_assign
op_complement
id|PMCR_PMM_MASK
suffix:semicolon
id|pmcr
op_or_assign
id|ctr
(braket
l_int|0
)braket
dot
id|event
suffix:semicolon
id|ctrl_outw
c_func
(paren
id|pmcr
op_or
id|PMCR_ENABLE
comma
id|PMCR1
)paren
suffix:semicolon
)brace
multiline_comment|/* Enable counter 2 */
r_if
c_cond
(paren
id|ctr
(braket
l_int|1
)braket
dot
id|enabled
)paren
(brace
id|pmcr
op_assign
id|ctrl_inw
c_func
(paren
id|PMCR2
)paren
suffix:semicolon
id|WARN_ON
c_func
(paren
id|pmcr
op_amp
id|PMCR_PMEN
)paren
suffix:semicolon
id|pmcr
op_and_assign
op_complement
id|PMCR_PMM_MASK
suffix:semicolon
id|pmcr
op_or_assign
id|ctr
(braket
l_int|1
)braket
dot
id|event
suffix:semicolon
id|ctrl_outw
c_func
(paren
id|pmcr
op_or
id|PMCR_ENABLE
comma
id|PMCR2
)paren
suffix:semicolon
)brace
r_return
id|register_profile_notifier
c_func
(paren
op_amp
id|sh7750_timer_notifier
)paren
suffix:semicolon
)brace
DECL|function|sh7750_perf_counter_stop
r_static
r_void
id|sh7750_perf_counter_stop
c_func
(paren
r_void
)paren
(brace
id|ctrl_outw
c_func
(paren
id|ctrl_inw
c_func
(paren
id|PMCR1
)paren
op_amp
op_complement
id|PMCR_PMEN
comma
id|PMCR1
)paren
suffix:semicolon
id|ctrl_outw
c_func
(paren
id|ctrl_inw
c_func
(paren
id|PMCR2
)paren
op_amp
op_complement
id|PMCR_PMEN
comma
id|PMCR2
)paren
suffix:semicolon
id|unregister_profile_notifier
c_func
(paren
op_amp
id|sh7750_timer_notifier
)paren
suffix:semicolon
)brace
DECL|variable|sh7750_perf_counter_ops
r_static
r_struct
id|oprofile_operations
id|sh7750_perf_counter_ops
op_assign
(brace
dot
id|create_files
op_assign
id|sh7750_perf_counter_create_files
comma
dot
id|start
op_assign
id|sh7750_perf_counter_start
comma
dot
id|stop
op_assign
id|sh7750_perf_counter_stop
comma
)brace
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
r_if
c_cond
(paren
op_logical_neg
(paren
id|cpu_data-&gt;flags
op_amp
id|CPU_HAS_PERF_COUNTER
)paren
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|sh7750_perf_counter_ops.cpu_type
op_assign
(paren
r_char
op_star
)paren
id|get_cpu_subtype
c_func
(paren
)paren
suffix:semicolon
op_star
id|ops
op_assign
op_amp
id|sh7750_perf_counter_ops
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;oprofile: using SH-4 (%s) performance monitoring.&bslash;n&quot;
comma
id|sh7750_perf_counter_ops.cpu_type
)paren
suffix:semicolon
multiline_comment|/* Clear the counters */
id|ctrl_outw
c_func
(paren
id|ctrl_inw
c_func
(paren
id|PMCR1
)paren
op_or
id|PMCR_PMCLR
comma
id|PMCR1
)paren
suffix:semicolon
id|ctrl_outw
c_func
(paren
id|ctrl_inw
c_func
(paren
id|PMCR2
)paren
op_or
id|PMCR_PMCLR
comma
id|PMCR2
)paren
suffix:semicolon
r_return
l_int|0
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
)brace
eof
