multiline_comment|/*&n; *  Kernel Probes (KProbes)&n; *  kernel/kprobes.c&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.&n; *&n; * Copyright (C) IBM Corporation, 2002, 2004&n; *&n; * 2002-Oct&t;Created by Vamsi Krishna S &lt;vamsi_krishna@in.ibm.com&gt; Kernel&n; *&t;&t;Probes initial implementation (includes suggestions from&n; *&t;&t;Rusty Russell).&n; * 2004-Aug&t;Updated by Prasanna S Panchamukhi &lt;prasanna@in.ibm.com&gt; with&n; *&t;&t;hlists and exceptions notifier as suggested by Andi Kleen.&n; * 2004-July&t;Suparna Bhattacharya &lt;suparna@in.ibm.com&gt; added jumper probes&n; *&t;&t;interface to access function arguments.&n; * 2004-Sep&t;Prasanna S Panchamukhi &lt;prasanna@in.ibm.com&gt; Changed Kprobes&n; *&t;&t;exceptions notifier to be first on the priority list.&n; */
macro_line|#include &lt;linux/kprobes.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/hash.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;asm/cacheflush.h&gt;
macro_line|#include &lt;asm/errno.h&gt;
macro_line|#include &lt;asm/kdebug.h&gt;
DECL|macro|KPROBE_HASH_BITS
mdefine_line|#define KPROBE_HASH_BITS 6
DECL|macro|KPROBE_TABLE_SIZE
mdefine_line|#define KPROBE_TABLE_SIZE (1 &lt;&lt; KPROBE_HASH_BITS)
DECL|variable|kprobe_table
r_static
r_struct
id|hlist_head
id|kprobe_table
(braket
id|KPROBE_TABLE_SIZE
)braket
suffix:semicolon
DECL|variable|kprobe_cpu
r_int
r_int
id|kprobe_cpu
op_assign
id|NR_CPUS
suffix:semicolon
r_static
id|DEFINE_SPINLOCK
c_func
(paren
id|kprobe_lock
)paren
suffix:semicolon
multiline_comment|/* Locks kprobe: irqs must be disabled */
DECL|function|lock_kprobes
r_void
id|lock_kprobes
c_func
(paren
r_void
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|kprobe_lock
)paren
suffix:semicolon
id|kprobe_cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|unlock_kprobes
r_void
id|unlock_kprobes
c_func
(paren
r_void
)paren
(brace
id|kprobe_cpu
op_assign
id|NR_CPUS
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|kprobe_lock
)paren
suffix:semicolon
)brace
multiline_comment|/* You have to be holding the kprobe_lock */
DECL|function|get_kprobe
r_struct
id|kprobe
op_star
id|get_kprobe
c_func
(paren
r_void
op_star
id|addr
)paren
(brace
r_struct
id|hlist_head
op_star
id|head
suffix:semicolon
r_struct
id|hlist_node
op_star
id|node
suffix:semicolon
id|head
op_assign
op_amp
id|kprobe_table
(braket
id|hash_ptr
c_func
(paren
id|addr
comma
id|KPROBE_HASH_BITS
)paren
)braket
suffix:semicolon
id|hlist_for_each
c_func
(paren
id|node
comma
id|head
)paren
(brace
r_struct
id|kprobe
op_star
id|p
op_assign
id|hlist_entry
c_func
(paren
id|node
comma
r_struct
id|kprobe
comma
id|hlist
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;addr
op_eq
id|addr
)paren
r_return
id|p
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|register_kprobe
r_int
id|register_kprobe
c_func
(paren
r_struct
id|kprobe
op_star
id|p
)paren
(brace
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|flags
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|arch_prepare_kprobe
c_func
(paren
id|p
)paren
)paren
op_ne
l_int|0
)paren
(brace
r_goto
id|rm_kprobe
suffix:semicolon
)brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|kprobe_lock
comma
id|flags
)paren
suffix:semicolon
id|INIT_HLIST_NODE
c_func
(paren
op_amp
id|p-&gt;hlist
)paren
suffix:semicolon
r_if
c_cond
(paren
id|get_kprobe
c_func
(paren
id|p-&gt;addr
)paren
)paren
(brace
id|ret
op_assign
op_minus
id|EEXIST
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|arch_copy_kprobe
c_func
(paren
id|p
)paren
suffix:semicolon
id|hlist_add_head
c_func
(paren
op_amp
id|p-&gt;hlist
comma
op_amp
id|kprobe_table
(braket
id|hash_ptr
c_func
(paren
id|p-&gt;addr
comma
id|KPROBE_HASH_BITS
)paren
)braket
)paren
suffix:semicolon
id|p-&gt;opcode
op_assign
op_star
id|p-&gt;addr
suffix:semicolon
op_star
id|p-&gt;addr
op_assign
id|BREAKPOINT_INSTRUCTION
suffix:semicolon
id|flush_icache_range
c_func
(paren
(paren
r_int
r_int
)paren
id|p-&gt;addr
comma
(paren
r_int
r_int
)paren
id|p-&gt;addr
op_plus
r_sizeof
(paren
id|kprobe_opcode_t
)paren
)paren
suffix:semicolon
id|out
suffix:colon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|kprobe_lock
comma
id|flags
)paren
suffix:semicolon
id|rm_kprobe
suffix:colon
r_if
c_cond
(paren
id|ret
op_eq
op_minus
id|EEXIST
)paren
id|arch_remove_kprobe
c_func
(paren
id|p
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|unregister_kprobe
r_void
id|unregister_kprobe
c_func
(paren
r_struct
id|kprobe
op_star
id|p
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|arch_remove_kprobe
c_func
(paren
id|p
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|kprobe_lock
comma
id|flags
)paren
suffix:semicolon
op_star
id|p-&gt;addr
op_assign
id|p-&gt;opcode
suffix:semicolon
id|hlist_del
c_func
(paren
op_amp
id|p-&gt;hlist
)paren
suffix:semicolon
id|flush_icache_range
c_func
(paren
(paren
r_int
r_int
)paren
id|p-&gt;addr
comma
(paren
r_int
r_int
)paren
id|p-&gt;addr
op_plus
r_sizeof
(paren
id|kprobe_opcode_t
)paren
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|kprobe_lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|variable|kprobe_exceptions_nb
r_static
r_struct
id|notifier_block
id|kprobe_exceptions_nb
op_assign
(brace
dot
id|notifier_call
op_assign
id|kprobe_exceptions_notify
comma
dot
id|priority
op_assign
l_int|0x7fffffff
multiline_comment|/* we need to notified first */
)brace
suffix:semicolon
DECL|function|register_jprobe
r_int
id|register_jprobe
c_func
(paren
r_struct
id|jprobe
op_star
id|jp
)paren
(brace
multiline_comment|/* Todo: Verify probepoint is a function entry point */
id|jp-&gt;kp.pre_handler
op_assign
id|setjmp_pre_handler
suffix:semicolon
id|jp-&gt;kp.break_handler
op_assign
id|longjmp_break_handler
suffix:semicolon
r_return
id|register_kprobe
c_func
(paren
op_amp
id|jp-&gt;kp
)paren
suffix:semicolon
)brace
DECL|function|unregister_jprobe
r_void
id|unregister_jprobe
c_func
(paren
r_struct
id|jprobe
op_star
id|jp
)paren
(brace
id|unregister_kprobe
c_func
(paren
op_amp
id|jp-&gt;kp
)paren
suffix:semicolon
)brace
DECL|function|init_kprobes
r_static
r_int
id|__init
id|init_kprobes
c_func
(paren
r_void
)paren
(brace
r_int
id|i
comma
id|err
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* FIXME allocate the probe table, currently defined statically */
multiline_comment|/* initialize all list heads */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|KPROBE_TABLE_SIZE
suffix:semicolon
id|i
op_increment
)paren
id|INIT_HLIST_HEAD
c_func
(paren
op_amp
id|kprobe_table
(braket
id|i
)braket
)paren
suffix:semicolon
id|err
op_assign
id|register_die_notifier
c_func
(paren
op_amp
id|kprobe_exceptions_nb
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|variable|init_kprobes
id|__initcall
c_func
(paren
id|init_kprobes
)paren
suffix:semicolon
DECL|variable|register_kprobe
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|register_kprobe
)paren
suffix:semicolon
DECL|variable|unregister_kprobe
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|unregister_kprobe
)paren
suffix:semicolon
DECL|variable|register_jprobe
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|register_jprobe
)paren
suffix:semicolon
DECL|variable|unregister_jprobe
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|unregister_jprobe
)paren
suffix:semicolon
DECL|variable|jprobe_return
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|jprobe_return
)paren
suffix:semicolon
eof
