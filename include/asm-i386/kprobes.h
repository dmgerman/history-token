macro_line|#ifndef _ASM_KPROBES_H
DECL|macro|_ASM_KPROBES_H
mdefine_line|#define _ASM_KPROBES_H
multiline_comment|/*&n; *  Kernel Probes (KProbes)&n; *  include/asm-i386/kprobes.h&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.&n; *&n; * Copyright (C) IBM Corporation, 2002, 2004&n; *&n; * 2002-Oct&t;Created by Vamsi Krishna S &lt;vamsi_krishna@in.ibm.com&gt; Kernel&n; *&t;&t;Probes initial implementation ( includes suggestions from&n; *&t;&t;Rusty Russell).&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
r_struct
id|pt_regs
suffix:semicolon
DECL|typedef|kprobe_opcode_t
r_typedef
id|u8
id|kprobe_opcode_t
suffix:semicolon
DECL|macro|BREAKPOINT_INSTRUCTION
mdefine_line|#define BREAKPOINT_INSTRUCTION&t;0xcc
DECL|macro|MAX_INSN_SIZE
mdefine_line|#define MAX_INSN_SIZE 16
multiline_comment|/* trap3/1 are intr gates for kprobes.  So, restore the status of IF,&n; * if necessary, before executing the original int3/1 (trap) handler.&n; */
DECL|function|restore_interrupts
r_static
r_inline
r_void
id|restore_interrupts
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_if
c_cond
(paren
id|regs-&gt;eflags
op_amp
id|IF_MASK
)paren
id|local_irq_enable
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_KPROBES
r_extern
r_int
id|kprobe_exceptions_notify
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
id|data
)paren
suffix:semicolon
macro_line|#else&t;&t;&t;&t;/* !CONFIG_KPROBES */
DECL|function|kprobe_exceptions_notify
r_static
r_inline
r_int
id|kprobe_exceptions_notify
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
id|data
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
macro_line|#endif&t;&t;&t;&t;/* _ASM_KPROBES_H */
eof
