multiline_comment|/*&n; * linux/kernel/irq/proc.c&n; *&n; * Copyright (C) 1992, 1998-2004 Linus Torvalds, Ingo Molnar&n; *&n; * This file contains the /proc/irq/ handling code.&n; */
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
DECL|variable|root_irq_dir
DECL|variable|irq_dir
r_static
r_struct
id|proc_dir_entry
op_star
id|root_irq_dir
comma
op_star
id|irq_dir
(braket
id|NR_IRQS
)braket
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
multiline_comment|/*&n; * The /proc/irq/&lt;irq&gt;/smp_affinity values:&n; */
DECL|variable|smp_affinity_entry
r_static
r_struct
id|proc_dir_entry
op_star
id|smp_affinity_entry
(braket
id|NR_IRQS
)braket
suffix:semicolon
r_void
id|__attribute__
c_func
(paren
(paren
id|weak
)paren
)paren
DECL|function|proc_set_irq_affinity
id|proc_set_irq_affinity
c_func
(paren
r_int
r_int
id|irq
comma
id|cpumask_t
id|mask_val
)paren
(brace
id|irq_affinity
(braket
id|irq
)braket
op_assign
id|mask_val
suffix:semicolon
id|irq_desc
(braket
id|irq
)braket
dot
id|handler
op_member_access_from_pointer
id|set_affinity
c_func
(paren
id|irq
comma
id|mask_val
)paren
suffix:semicolon
)brace
DECL|function|irq_affinity_read_proc
r_static
r_int
id|irq_affinity_read_proc
c_func
(paren
r_char
op_star
id|page
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|off
comma
r_int
id|count
comma
r_int
op_star
id|eof
comma
r_void
op_star
id|data
)paren
(brace
r_int
id|len
op_assign
id|cpumask_scnprintf
c_func
(paren
id|page
comma
id|count
comma
id|irq_affinity
(braket
(paren
r_int
)paren
id|data
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|count
op_minus
id|len
OL
l_int|2
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|page
op_plus
id|len
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
DECL|variable|no_irq_affinity
r_int
id|no_irq_affinity
suffix:semicolon
DECL|function|irq_affinity_write_proc
r_static
r_int
id|irq_affinity_write_proc
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
id|buffer
comma
r_int
r_int
id|count
comma
r_void
op_star
id|data
)paren
(brace
r_int
r_int
id|irq
op_assign
(paren
r_int
)paren
(paren
r_int
)paren
id|data
comma
id|full_count
op_assign
id|count
comma
id|err
suffix:semicolon
id|cpumask_t
id|new_value
comma
id|tmp
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|irq_desc
(braket
id|irq
)braket
dot
id|handler-&gt;set_affinity
op_logical_or
id|no_irq_affinity
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|err
op_assign
id|cpumask_parse
c_func
(paren
id|buffer
comma
id|count
comma
id|new_value
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_return
id|err
suffix:semicolon
multiline_comment|/*&n;&t; * Do not allow disabling IRQs completely - it&squot;s a too easy&n;&t; * way to make the system unusable accidentally :-) At least&n;&t; * one online CPU still has to be targeted.&n;&t; */
id|cpus_and
c_func
(paren
id|tmp
comma
id|new_value
comma
id|cpu_online_map
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cpus_empty
c_func
(paren
id|tmp
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|proc_set_irq_affinity
c_func
(paren
id|irq
comma
id|new_value
)paren
suffix:semicolon
r_return
id|full_count
suffix:semicolon
)brace
macro_line|#endif
DECL|macro|MAX_NAMELEN
mdefine_line|#define MAX_NAMELEN 128
DECL|function|name_unique
r_static
r_int
id|name_unique
c_func
(paren
r_int
r_int
id|irq
comma
r_struct
id|irqaction
op_star
id|new_action
)paren
(brace
r_struct
id|irq_desc
op_star
id|desc
op_assign
id|irq_desc
op_plus
id|irq
suffix:semicolon
r_struct
id|irqaction
op_star
id|action
suffix:semicolon
r_for
c_loop
(paren
id|action
op_assign
id|desc-&gt;action
suffix:semicolon
id|action
suffix:semicolon
id|action
op_assign
id|action-&gt;next
)paren
r_if
c_cond
(paren
(paren
id|action
op_ne
id|new_action
)paren
op_logical_and
id|action-&gt;name
op_logical_and
op_logical_neg
id|strcmp
c_func
(paren
id|new_action-&gt;name
comma
id|action-&gt;name
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|register_handler_proc
r_void
id|register_handler_proc
c_func
(paren
r_int
r_int
id|irq
comma
r_struct
id|irqaction
op_star
id|action
)paren
(brace
r_char
id|name
(braket
id|MAX_NAMELEN
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|irq_dir
(braket
id|irq
)braket
op_logical_or
id|action-&gt;dir
op_logical_or
op_logical_neg
id|action-&gt;name
op_logical_or
op_logical_neg
id|name_unique
c_func
(paren
id|irq
comma
id|action
)paren
)paren
r_return
suffix:semicolon
id|memset
c_func
(paren
id|name
comma
l_int|0
comma
id|MAX_NAMELEN
)paren
suffix:semicolon
id|snprintf
c_func
(paren
id|name
comma
id|MAX_NAMELEN
comma
l_string|&quot;%s&quot;
comma
id|action-&gt;name
)paren
suffix:semicolon
multiline_comment|/* create /proc/irq/1234/handler/ */
id|action-&gt;dir
op_assign
id|proc_mkdir
c_func
(paren
id|name
comma
id|irq_dir
(braket
id|irq
)braket
)paren
suffix:semicolon
)brace
DECL|macro|MAX_NAMELEN
macro_line|#undef MAX_NAMELEN
DECL|macro|MAX_NAMELEN
mdefine_line|#define MAX_NAMELEN 10
DECL|function|register_irq_proc
r_void
id|register_irq_proc
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_char
id|name
(braket
id|MAX_NAMELEN
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|root_irq_dir
op_logical_or
(paren
id|irq_desc
(braket
id|irq
)braket
dot
id|handler
op_eq
op_amp
id|no_irq_type
)paren
op_logical_or
id|irq_dir
(braket
id|irq
)braket
)paren
r_return
suffix:semicolon
id|memset
c_func
(paren
id|name
comma
l_int|0
comma
id|MAX_NAMELEN
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|name
comma
l_string|&quot;%d&quot;
comma
id|irq
)paren
suffix:semicolon
multiline_comment|/* create /proc/irq/1234 */
id|irq_dir
(braket
id|irq
)braket
op_assign
id|proc_mkdir
c_func
(paren
id|name
comma
id|root_irq_dir
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
(brace
r_struct
id|proc_dir_entry
op_star
id|entry
suffix:semicolon
multiline_comment|/* create /proc/irq/&lt;irq&gt;/smp_affinity */
id|entry
op_assign
id|create_proc_entry
c_func
(paren
l_string|&quot;smp_affinity&quot;
comma
l_int|0600
comma
id|irq_dir
(braket
id|irq
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|entry
)paren
(brace
id|entry-&gt;nlink
op_assign
l_int|1
suffix:semicolon
id|entry-&gt;data
op_assign
(paren
r_void
op_star
)paren
(paren
r_int
)paren
id|irq
suffix:semicolon
id|entry-&gt;read_proc
op_assign
id|irq_affinity_read_proc
suffix:semicolon
id|entry-&gt;write_proc
op_assign
id|irq_affinity_write_proc
suffix:semicolon
)brace
id|smp_affinity_entry
(braket
id|irq
)braket
op_assign
id|entry
suffix:semicolon
)brace
macro_line|#endif
)brace
DECL|macro|MAX_NAMELEN
macro_line|#undef MAX_NAMELEN
DECL|function|unregister_handler_proc
r_void
id|unregister_handler_proc
c_func
(paren
r_int
r_int
id|irq
comma
r_struct
id|irqaction
op_star
id|action
)paren
(brace
r_if
c_cond
(paren
id|action-&gt;dir
)paren
id|remove_proc_entry
c_func
(paren
id|action-&gt;dir-&gt;name
comma
id|irq_dir
(braket
id|irq
)braket
)paren
suffix:semicolon
)brace
DECL|function|init_irq_proc
r_void
id|init_irq_proc
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/* create /proc/irq */
id|root_irq_dir
op_assign
id|proc_mkdir
c_func
(paren
l_string|&quot;irq&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|root_irq_dir
)paren
r_return
suffix:semicolon
multiline_comment|/*&n;&t; * Create entries for all existing IRQs.&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NR_IRQS
suffix:semicolon
id|i
op_increment
)paren
id|register_irq_proc
c_func
(paren
id|i
)paren
suffix:semicolon
)brace
eof
