multiline_comment|/*&n; *  linux/arch/arm/kernel/fiq.c&n; *&n; *  Copyright (C) 1998 Russell King&n; *  Copyright (C) 1998, 1999 Phil Blundell&n; *&n; *  FIQ support written by Philip Blundell &lt;philb@gnu.org&gt;, 1998.&n; *&n; *  FIQ support re-written by Russell King to be more generic&n; *&n; * We now properly support a method by which the FIQ handlers can&n; * be stacked onto the vector.  We still do not support sharing&n; * the FIQ vector itself.&n; *&n; * Operation is as follows:&n; *  1. Owner A claims FIQ:&n; *     - default_fiq relinquishes control.&n; *  2. Owner A:&n; *     - inserts code.&n; *     - sets any registers,&n; *     - enables FIQ.&n; *  3. Owner B claims FIQ:&n; *     - if owner A has a relinquish function.&n; *       - disable FIQs.&n; *       - saves any registers.&n; *       - returns zero.&n; *  4. Owner B:&n; *     - inserts code.&n; *     - sets any registers,&n; *     - enables FIQ.&n; *  5. Owner B releases FIQ:&n; *     - Owner A is asked to reacquire FIQ:&n; *&t; - inserts code.&n; *&t; - restores saved registers.&n; *&t; - enables FIQ.&n; *  6. Goto 3&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/mman.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;asm/fiq.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
DECL|macro|FIQ_VECTOR
mdefine_line|#define FIQ_VECTOR (vectors_base() + 0x1c)
DECL|variable|no_fiq_insn
r_static
r_int
r_int
id|no_fiq_insn
suffix:semicolon
macro_line|#ifdef CONFIG_CPU_32
DECL|function|unprotect_page_0
r_static
r_inline
r_void
id|unprotect_page_0
c_func
(paren
r_void
)paren
(brace
id|modify_domain
c_func
(paren
id|DOMAIN_USER
comma
id|DOMAIN_MANAGER
)paren
suffix:semicolon
)brace
DECL|function|protect_page_0
r_static
r_inline
r_void
id|protect_page_0
c_func
(paren
r_void
)paren
(brace
id|modify_domain
c_func
(paren
id|DOMAIN_USER
comma
id|DOMAIN_CLIENT
)paren
suffix:semicolon
)brace
macro_line|#else
DECL|macro|unprotect_page_0
mdefine_line|#define unprotect_page_0()
DECL|macro|protect_page_0
mdefine_line|#define protect_page_0()
macro_line|#endif
multiline_comment|/* Default reacquire function&n; * - we always relinquish FIQ control&n; * - we always reacquire FIQ control&n; */
DECL|function|fiq_def_op
r_static
r_int
id|fiq_def_op
c_func
(paren
r_void
op_star
id|ref
comma
r_int
id|relinquish
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|relinquish
)paren
(brace
id|unprotect_page_0
c_func
(paren
)paren
suffix:semicolon
op_star
(paren
r_int
r_int
op_star
)paren
id|FIQ_VECTOR
op_assign
id|no_fiq_insn
suffix:semicolon
id|protect_page_0
c_func
(paren
)paren
suffix:semicolon
id|flush_icache_range
c_func
(paren
id|FIQ_VECTOR
comma
id|FIQ_VECTOR
op_plus
l_int|4
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|default_owner
r_static
r_struct
id|fiq_handler
id|default_owner
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;default&quot;
comma
dot
id|fiq_op
op_assign
id|fiq_def_op
comma
)brace
suffix:semicolon
DECL|variable|current_fiq
r_static
r_struct
id|fiq_handler
op_star
id|current_fiq
op_assign
op_amp
id|default_owner
suffix:semicolon
DECL|function|show_fiq_list
r_int
id|show_fiq_list
c_func
(paren
r_struct
id|seq_file
op_star
id|p
comma
r_void
op_star
id|v
)paren
(brace
r_if
c_cond
(paren
id|current_fiq
op_ne
op_amp
id|default_owner
)paren
id|seq_printf
c_func
(paren
id|p
comma
l_string|&quot;FIQ:              %s&bslash;n&quot;
comma
id|current_fiq-&gt;name
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|set_fiq_handler
r_void
id|set_fiq_handler
c_func
(paren
r_void
op_star
id|start
comma
r_int
r_int
id|length
)paren
(brace
id|unprotect_page_0
c_func
(paren
)paren
suffix:semicolon
id|memcpy
c_func
(paren
(paren
r_void
op_star
)paren
id|FIQ_VECTOR
comma
id|start
comma
id|length
)paren
suffix:semicolon
id|protect_page_0
c_func
(paren
)paren
suffix:semicolon
id|flush_icache_range
c_func
(paren
id|FIQ_VECTOR
comma
id|FIQ_VECTOR
op_plus
id|length
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Taking an interrupt in FIQ mode is death, so both these functions&n; * disable irqs for the duration. &n; */
DECL|function|set_fiq_regs
r_void
id|set_fiq_regs
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_register
r_int
r_int
id|tmp
comma
id|tmp2
suffix:semicolon
id|__asm__
r_volatile
(paren
macro_line|#ifdef CONFIG_CPU_26
"&quot;"
id|mov
op_mod
l_int|0
comma
id|pc
id|bic
op_mod
l_int|1
comma
op_mod
l_int|0
comma
macro_line|#0x3
id|orr
op_mod
l_int|1
comma
op_mod
l_int|1
comma
op_mod
l_int|3
id|teqp
op_mod
l_int|1
comma
macro_line|#0&t;&t;@ select FIQ mode
id|mov
id|r0
comma
id|r0
id|ldmia
op_mod
l_int|2
comma
(brace
id|r8
op_minus
id|r14
)brace
id|teqp
op_mod
l_int|0
comma
macro_line|#0&t;&t;@ return to SVC mode
id|mov
id|r0
comma
id|r0
"&quot;"
macro_line|#endif
macro_line|#ifdef CONFIG_CPU_32
"&quot;"
id|mrs
op_mod
l_int|0
comma
id|cpsr
id|mov
op_mod
l_int|1
comma
op_mod
l_int|3
id|msr
id|cpsr_c
comma
op_mod
l_int|1
"@"
id|select
id|FIQ
id|mode
id|mov
id|r0
comma
id|r0
id|ldmia
op_mod
l_int|2
comma
(brace
id|r8
op_minus
id|r14
)brace
id|msr
id|cpsr_c
comma
op_mod
l_int|0
"@"
r_return
id|to
id|SVC
id|mode
id|mov
id|r0
comma
id|r0
"&quot;"
macro_line|#endif
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|tmp
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|tmp2
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
op_amp
id|regs-&gt;ARM_r8
)paren
comma
l_string|&quot;I&quot;
(paren
id|PSR_I_BIT
op_or
id|PSR_F_BIT
op_or
id|FIQ_MODE
)paren
multiline_comment|/* These registers aren&squot;t modified by the above code in a way&n;&t;   visible to the compiler, but we mark them as clobbers anyway&n;&t;   so that GCC won&squot;t put any of the input or output operands in&n;&t;   them.  */
suffix:colon
l_string|&quot;r8&quot;
comma
l_string|&quot;r9&quot;
comma
l_string|&quot;r10&quot;
comma
l_string|&quot;r11&quot;
comma
l_string|&quot;r12&quot;
comma
l_string|&quot;r13&quot;
comma
l_string|&quot;r14&quot;
)paren
suffix:semicolon
)brace
DECL|function|get_fiq_regs
r_void
id|get_fiq_regs
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_register
r_int
r_int
id|tmp
comma
id|tmp2
suffix:semicolon
id|__asm__
r_volatile
(paren
macro_line|#ifdef CONFIG_CPU_26
"&quot;"
id|mov
op_mod
l_int|0
comma
id|pc
id|bic
op_mod
l_int|1
comma
op_mod
l_int|0
comma
macro_line|#0x3
id|orr
op_mod
l_int|1
comma
op_mod
l_int|1
comma
op_mod
l_int|3
id|teqp
op_mod
l_int|1
comma
macro_line|#0&t;&t;@ select FIQ mode
id|mov
id|r0
comma
id|r0
id|stmia
op_mod
l_int|2
comma
(brace
id|r8
op_minus
id|r14
)brace
id|teqp
op_mod
l_int|0
comma
macro_line|#0&t;&t;@ return to SVC mode
id|mov
id|r0
comma
id|r0
"&quot;"
macro_line|#endif
macro_line|#ifdef CONFIG_CPU_32
"&quot;"
id|mrs
op_mod
l_int|0
comma
id|cpsr
id|mov
op_mod
l_int|1
comma
op_mod
l_int|3
id|msr
id|cpsr_c
comma
op_mod
l_int|1
"@"
id|select
id|FIQ
id|mode
id|mov
id|r0
comma
id|r0
id|stmia
op_mod
l_int|2
comma
(brace
id|r8
op_minus
id|r14
)brace
id|msr
id|cpsr_c
comma
op_mod
l_int|0
"@"
r_return
id|to
id|SVC
id|mode
id|mov
id|r0
comma
id|r0
"&quot;"
macro_line|#endif
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|tmp
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|tmp2
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
op_amp
id|regs-&gt;ARM_r8
)paren
comma
l_string|&quot;I&quot;
(paren
id|PSR_I_BIT
op_or
id|PSR_F_BIT
op_or
id|FIQ_MODE
)paren
multiline_comment|/* These registers aren&squot;t modified by the above code in a way&n;&t;   visible to the compiler, but we mark them as clobbers anyway&n;&t;   so that GCC won&squot;t put any of the input or output operands in&n;&t;   them.  */
suffix:colon
l_string|&quot;r8&quot;
comma
l_string|&quot;r9&quot;
comma
l_string|&quot;r10&quot;
comma
l_string|&quot;r11&quot;
comma
l_string|&quot;r12&quot;
comma
l_string|&quot;r13&quot;
comma
l_string|&quot;r14&quot;
)paren
suffix:semicolon
)brace
DECL|function|claim_fiq
r_int
id|claim_fiq
c_func
(paren
r_struct
id|fiq_handler
op_star
id|f
)paren
(brace
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|current_fiq
)paren
(brace
id|ret
op_assign
op_minus
id|EBUSY
suffix:semicolon
r_if
c_cond
(paren
id|current_fiq-&gt;fiq_op
op_ne
l_int|NULL
)paren
id|ret
op_assign
id|current_fiq
op_member_access_from_pointer
id|fiq_op
c_func
(paren
id|current_fiq-&gt;dev_id
comma
l_int|1
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
(brace
id|f-&gt;next
op_assign
id|current_fiq
suffix:semicolon
id|current_fiq
op_assign
id|f
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|release_fiq
r_void
id|release_fiq
c_func
(paren
r_struct
id|fiq_handler
op_star
id|f
)paren
(brace
r_if
c_cond
(paren
id|current_fiq
op_ne
id|f
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s FIQ trying to release %s FIQ&bslash;n&quot;
comma
id|f-&gt;name
comma
id|current_fiq-&gt;name
)paren
suffix:semicolon
id|dump_stack
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_do
id|current_fiq
op_assign
id|current_fiq-&gt;next
suffix:semicolon
r_while
c_loop
(paren
id|current_fiq
op_member_access_from_pointer
id|fiq_op
c_func
(paren
id|current_fiq-&gt;dev_id
comma
l_int|0
)paren
)paren
suffix:semicolon
)brace
DECL|function|enable_fiq
r_void
id|enable_fiq
c_func
(paren
r_int
id|fiq
)paren
(brace
id|enable_irq
c_func
(paren
id|fiq
op_plus
id|FIQ_START
)paren
suffix:semicolon
)brace
DECL|function|disable_fiq
r_void
id|disable_fiq
c_func
(paren
r_int
id|fiq
)paren
(brace
id|disable_irq
c_func
(paren
id|fiq
op_plus
id|FIQ_START
)paren
suffix:semicolon
)brace
DECL|variable|set_fiq_handler
id|EXPORT_SYMBOL
c_func
(paren
id|set_fiq_handler
)paren
suffix:semicolon
DECL|variable|set_fiq_regs
id|EXPORT_SYMBOL
c_func
(paren
id|set_fiq_regs
)paren
suffix:semicolon
DECL|variable|get_fiq_regs
id|EXPORT_SYMBOL
c_func
(paren
id|get_fiq_regs
)paren
suffix:semicolon
DECL|variable|claim_fiq
id|EXPORT_SYMBOL
c_func
(paren
id|claim_fiq
)paren
suffix:semicolon
DECL|variable|release_fiq
id|EXPORT_SYMBOL
c_func
(paren
id|release_fiq
)paren
suffix:semicolon
DECL|variable|enable_fiq
id|EXPORT_SYMBOL
c_func
(paren
id|enable_fiq
)paren
suffix:semicolon
DECL|variable|disable_fiq
id|EXPORT_SYMBOL
c_func
(paren
id|disable_fiq
)paren
suffix:semicolon
DECL|function|init_FIQ
r_void
id|__init
id|init_FIQ
c_func
(paren
r_void
)paren
(brace
id|no_fiq_insn
op_assign
op_star
(paren
r_int
r_int
op_star
)paren
id|FIQ_VECTOR
suffix:semicolon
id|set_fs
c_func
(paren
id|get_fs
c_func
(paren
)paren
)paren
suffix:semicolon
)brace
eof
