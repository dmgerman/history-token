multiline_comment|/*&n; *  linux/arch/arm/mm/alignment.c&n; *&n; *  Copyright (C) 1995  Linus Torvalds&n; *  Modifications for ARM processor (c) 1995-2001 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/compiler.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/unaligned.h&gt;
macro_line|#include &quot;fault.h&quot;
multiline_comment|/*&n; * 32-bit misaligned trap handler (c) 1998 San Mehat (CCC) -July 1998&n; * /proc/sys/debug/alignment, modified and integrated into&n; * Linux 2.1 by Russell King&n; *&n; * Speed optimisations and better fault handling by Russell King.&n; *&n; * *** NOTE ***&n; * This code is not portable to processors with late data abort handling.&n; */
DECL|macro|CODING_BITS
mdefine_line|#define CODING_BITS(i)&t;(i &amp; 0x0e000000)
DECL|macro|LDST_I_BIT
mdefine_line|#define LDST_I_BIT(i)&t;(i &amp; (1 &lt;&lt; 26))&t;&t;/* Immediate constant&t;*/
DECL|macro|LDST_P_BIT
mdefine_line|#define LDST_P_BIT(i)&t;(i &amp; (1 &lt;&lt; 24))&t;&t;/* Preindex&t;&t;*/
DECL|macro|LDST_U_BIT
mdefine_line|#define LDST_U_BIT(i)&t;(i &amp; (1 &lt;&lt; 23))&t;&t;/* Add offset&t;&t;*/
DECL|macro|LDST_W_BIT
mdefine_line|#define LDST_W_BIT(i)&t;(i &amp; (1 &lt;&lt; 21))&t;&t;/* Writeback&t;&t;*/
DECL|macro|LDST_L_BIT
mdefine_line|#define LDST_L_BIT(i)&t;(i &amp; (1 &lt;&lt; 20))&t;&t;/* Load&t;&t;&t;*/
DECL|macro|LDST_P_EQ_U
mdefine_line|#define LDST_P_EQ_U(i)&t;((((i) ^ ((i) &gt;&gt; 1)) &amp; (1 &lt;&lt; 23)) == 0)
DECL|macro|LDSTH_I_BIT
mdefine_line|#define LDSTH_I_BIT(i)&t;(i &amp; (1 &lt;&lt; 22))&t;&t;/* half-word immed&t;*/
DECL|macro|LDM_S_BIT
mdefine_line|#define LDM_S_BIT(i)&t;(i &amp; (1 &lt;&lt; 22))&t;&t;/* write CPSR from SPSR&t;*/
DECL|macro|RN_BITS
mdefine_line|#define RN_BITS(i)&t;((i &gt;&gt; 16) &amp; 15)&t;/* Rn&t;&t;&t;*/
DECL|macro|RD_BITS
mdefine_line|#define RD_BITS(i)&t;((i &gt;&gt; 12) &amp; 15)&t;/* Rd&t;&t;&t;*/
DECL|macro|RM_BITS
mdefine_line|#define RM_BITS(i)&t;(i &amp; 15)&t;&t;/* Rm&t;&t;&t;*/
DECL|macro|REGMASK_BITS
mdefine_line|#define REGMASK_BITS(i)&t;(i &amp; 0xffff)
DECL|macro|OFFSET_BITS
mdefine_line|#define OFFSET_BITS(i)&t;(i &amp; 0x0fff)
DECL|macro|IS_SHIFT
mdefine_line|#define IS_SHIFT(i)&t;(i &amp; 0x0ff0)
DECL|macro|SHIFT_BITS
mdefine_line|#define SHIFT_BITS(i)&t;((i &gt;&gt; 7) &amp; 0x1f)
DECL|macro|SHIFT_TYPE
mdefine_line|#define SHIFT_TYPE(i)&t;(i &amp; 0x60)
DECL|macro|SHIFT_LSL
mdefine_line|#define SHIFT_LSL&t;0x00
DECL|macro|SHIFT_LSR
mdefine_line|#define SHIFT_LSR&t;0x20
DECL|macro|SHIFT_ASR
mdefine_line|#define SHIFT_ASR&t;0x40
DECL|macro|SHIFT_RORRRX
mdefine_line|#define SHIFT_RORRRX&t;0x60
DECL|variable|ai_user
r_static
r_int
r_int
id|ai_user
suffix:semicolon
DECL|variable|ai_sys
r_static
r_int
r_int
id|ai_sys
suffix:semicolon
DECL|variable|ai_skipped
r_static
r_int
r_int
id|ai_skipped
suffix:semicolon
DECL|variable|ai_half
r_static
r_int
r_int
id|ai_half
suffix:semicolon
DECL|variable|ai_word
r_static
r_int
r_int
id|ai_word
suffix:semicolon
DECL|variable|ai_multi
r_static
r_int
r_int
id|ai_multi
suffix:semicolon
DECL|variable|ai_usermode
r_static
r_int
id|ai_usermode
suffix:semicolon
macro_line|#ifdef CONFIG_PROC_FS
DECL|variable|usermode_action
r_static
r_const
r_char
op_star
id|usermode_action
(braket
)braket
op_assign
(brace
l_string|&quot;ignored&quot;
comma
l_string|&quot;warn&quot;
comma
l_string|&quot;fixup&quot;
comma
l_string|&quot;fixup+warn&quot;
comma
l_string|&quot;signal&quot;
comma
l_string|&quot;signal+warn&quot;
)brace
suffix:semicolon
r_static
r_int
DECL|function|proc_alignment_read
id|proc_alignment_read
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
r_char
op_star
id|p
op_assign
id|page
suffix:semicolon
r_int
id|len
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;User:&bslash;t&bslash;t%lu&bslash;n&quot;
comma
id|ai_user
)paren
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;System:&bslash;t&bslash;t%lu&bslash;n&quot;
comma
id|ai_sys
)paren
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;Skipped:&bslash;t%lu&bslash;n&quot;
comma
id|ai_skipped
)paren
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;Half:&bslash;t&bslash;t%lu&bslash;n&quot;
comma
id|ai_half
)paren
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;Word:&bslash;t&bslash;t%lu&bslash;n&quot;
comma
id|ai_word
)paren
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;Multi:&bslash;t&bslash;t%lu&bslash;n&quot;
comma
id|ai_multi
)paren
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;User faults:&bslash;t%i (%s)&bslash;n&quot;
comma
id|ai_usermode
comma
id|usermode_action
(braket
id|ai_usermode
)braket
)paren
suffix:semicolon
id|len
op_assign
(paren
id|p
op_minus
id|page
)paren
op_minus
id|off
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
l_int|0
)paren
id|len
op_assign
l_int|0
suffix:semicolon
op_star
id|eof
op_assign
(paren
id|len
op_le
id|count
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
op_star
id|start
op_assign
id|page
op_plus
id|off
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
DECL|function|proc_alignment_write
r_static
r_int
id|proc_alignment_write
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
r_char
id|mode
suffix:semicolon
r_if
c_cond
(paren
id|count
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|mode
comma
id|buffer
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|mode
op_ge
l_char|&squot;0&squot;
op_logical_and
id|mode
op_le
l_char|&squot;5&squot;
)paren
id|ai_usermode
op_assign
id|mode
op_minus
l_char|&squot;0&squot;
suffix:semicolon
)brace
r_return
id|count
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_PROC_FS */
DECL|union|offset_union
r_union
id|offset_union
(brace
DECL|member|un
r_int
r_int
id|un
suffix:semicolon
DECL|member|sn
r_int
r_int
id|sn
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|TYPE_ERROR
mdefine_line|#define TYPE_ERROR&t;0
DECL|macro|TYPE_FAULT
mdefine_line|#define TYPE_FAULT&t;1
DECL|macro|TYPE_LDST
mdefine_line|#define TYPE_LDST&t;2
DECL|macro|TYPE_DONE
mdefine_line|#define TYPE_DONE&t;3
DECL|macro|__get8_unaligned_check
mdefine_line|#define __get8_unaligned_check(ins,val,addr,err)&t;&bslash;&n;&t;__asm__(&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;1:&t;&quot;ins&quot;&t;%1, [%2], #1&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&quot;2:&bslash;n&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;&t;&t;&bslash;&n;&t;&quot;&t;.align&t;2&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;3:&t;mov&t;%0, #1&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&quot;&t;b&t;2b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.previous&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;&t;&t;&bslash;&n;&t;&quot;&t;.align&t;3&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.long&t;1b, 3b&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&quot;&t;.previous&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;: &quot;=r&quot; (err), &quot;=&amp;r&quot; (val), &quot;=r&quot; (addr)&t;&t;&bslash;&n;&t;: &quot;0&quot; (err), &quot;2&quot; (addr))
DECL|macro|__get16_unaligned_check
mdefine_line|#define __get16_unaligned_check(ins,val,addr)&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;unsigned int err = 0, v, a = addr;&t;&t;&bslash;&n;&t;&t;__get8_unaligned_check(ins,val,a,err);&t;&t;&bslash;&n;&t;&t;__get8_unaligned_check(ins,v,a,err);&t;&t;&bslash;&n;&t;&t;val |= v &lt;&lt; 8;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;if (err)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;goto fault;&t;&t;&t;&t;&bslash;&n;&t;} while (0)
DECL|macro|get16_unaligned_check
mdefine_line|#define get16_unaligned_check(val,addr) &bslash;&n;&t;__get16_unaligned_check(&quot;ldrb&quot;,val,addr)
DECL|macro|get16t_unaligned_check
mdefine_line|#define get16t_unaligned_check(val,addr) &bslash;&n;&t;__get16_unaligned_check(&quot;ldrbt&quot;,val,addr)
DECL|macro|__get32_unaligned_check
mdefine_line|#define __get32_unaligned_check(ins,val,addr)&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;unsigned int err = 0, v, a = addr;&t;&t;&bslash;&n;&t;&t;__get8_unaligned_check(ins,val,a,err);&t;&t;&bslash;&n;&t;&t;__get8_unaligned_check(ins,v,a,err);&t;&t;&bslash;&n;&t;&t;val |= v &lt;&lt; 8;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__get8_unaligned_check(ins,v,a,err);&t;&t;&bslash;&n;&t;&t;val |= v &lt;&lt; 16;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__get8_unaligned_check(ins,v,a,err);&t;&t;&bslash;&n;&t;&t;val |= v &lt;&lt; 24;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;if (err)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;goto fault;&t;&t;&t;&t;&bslash;&n;&t;} while (0)
DECL|macro|get32_unaligned_check
mdefine_line|#define get32_unaligned_check(val,addr) &bslash;&n;&t;__get32_unaligned_check(&quot;ldrb&quot;,val,addr)
DECL|macro|get32t_unaligned_check
mdefine_line|#define get32t_unaligned_check(val,addr) &bslash;&n;&t;__get32_unaligned_check(&quot;ldrbt&quot;,val,addr)
DECL|macro|__put16_unaligned_check
mdefine_line|#define __put16_unaligned_check(ins,val,addr)&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;unsigned int err = 0, v = val, a = addr;&t;&bslash;&n;&t;&t;__asm__(&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;1:&t;&quot;ins&quot;&t;%1, [%2], #1&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;mov&t;%1, %1, lsr #8&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;&quot;2:&t;&quot;ins&quot;&t;%1, [%2]&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;3:&bslash;n&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;&quot;&t;.align&t;2&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;4:&t;mov&t;%0, #1&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;b&t;3b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.previous&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;&quot;&t;.align&t;3&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.long&t;1b, 4b&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.long&t;2b, 4b&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.previous&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=r&quot; (err), &quot;=&amp;r&quot; (v), &quot;=&amp;r&quot; (a)&t;&t;&bslash;&n;&t;&t;: &quot;0&quot; (err), &quot;1&quot; (v), &quot;2&quot; (a));&t;&t;&t;&bslash;&n;&t;&t;if (err)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;goto fault;&t;&t;&t;&t;&bslash;&n;&t;} while (0)
DECL|macro|put16_unaligned_check
mdefine_line|#define put16_unaligned_check(val,addr)  &bslash;&n;&t;__put16_unaligned_check(&quot;strb&quot;,val,addr)
DECL|macro|put16t_unaligned_check
mdefine_line|#define put16t_unaligned_check(val,addr) &bslash;&n;&t;__put16_unaligned_check(&quot;strbt&quot;,val,addr)
DECL|macro|__put32_unaligned_check
mdefine_line|#define __put32_unaligned_check(ins,val,addr)&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;unsigned int err = 0, v = val, a = addr;&t;&bslash;&n;&t;&t;__asm__(&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;1:&t;&quot;ins&quot;&t;%1, [%2], #1&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;mov&t;%1, %1, lsr #8&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;&quot;2:&t;&quot;ins&quot;&t;%1, [%2], #1&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;mov&t;%1, %1, lsr #8&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;&quot;3:&t;&quot;ins&quot;&t;%1, [%2], #1&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;mov&t;%1, %1, lsr #8&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;&quot;4:&t;&quot;ins&quot;&t;%1, [%2]&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;5:&bslash;n&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;&quot;&t;.align&t;2&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;6:&t;mov&t;%0, #1&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;b&t;5b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.previous&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;&quot;&t;.align&t;3&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.long&t;1b, 6b&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.long&t;2b, 6b&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.long&t;3b, 6b&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.long&t;4b, 6b&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.previous&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=r&quot; (err), &quot;=&amp;r&quot; (v), &quot;=&amp;r&quot; (a)&t;&t;&bslash;&n;&t;&t;: &quot;0&quot; (err), &quot;1&quot; (v), &quot;2&quot; (a));&t;&t;&t;&bslash;&n;&t;&t;if (err)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;goto fault;&t;&t;&t;&t;&bslash;&n;&t;} while (0)
DECL|macro|put32_unaligned_check
mdefine_line|#define put32_unaligned_check(val,addr)&t; &bslash;&n;&t;__put32_unaligned_check(&quot;strb&quot;, val, addr)
DECL|macro|put32t_unaligned_check
mdefine_line|#define put32t_unaligned_check(val,addr) &bslash;&n;&t;__put32_unaligned_check(&quot;strbt&quot;, val, addr)
r_static
r_void
DECL|function|do_alignment_finish_ldst
id|do_alignment_finish_ldst
c_func
(paren
r_int
r_int
id|addr
comma
r_int
r_int
id|instr
comma
r_struct
id|pt_regs
op_star
id|regs
comma
r_union
id|offset_union
id|offset
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|LDST_U_BIT
c_func
(paren
id|instr
)paren
)paren
id|offset.un
op_assign
op_minus
id|offset.un
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|LDST_P_BIT
c_func
(paren
id|instr
)paren
)paren
id|addr
op_add_assign
id|offset.un
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|LDST_P_BIT
c_func
(paren
id|instr
)paren
op_logical_or
id|LDST_W_BIT
c_func
(paren
id|instr
)paren
)paren
id|regs-&gt;uregs
(braket
id|RN_BITS
c_func
(paren
id|instr
)paren
)braket
op_assign
id|addr
suffix:semicolon
)brace
r_static
r_int
DECL|function|do_alignment_ldrhstrh
id|do_alignment_ldrhstrh
c_func
(paren
r_int
r_int
id|addr
comma
r_int
r_int
id|instr
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
r_int
id|rd
op_assign
id|RD_BITS
c_func
(paren
id|instr
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|instr
op_amp
l_int|0x01f00ff0
)paren
op_eq
l_int|0x01000090
)paren
r_goto
id|swp
suffix:semicolon
r_if
c_cond
(paren
(paren
id|instr
op_amp
l_int|0x90
)paren
op_ne
l_int|0x90
op_logical_or
(paren
id|instr
op_amp
l_int|0x60
)paren
op_eq
l_int|0
)paren
r_goto
id|bad
suffix:semicolon
id|ai_half
op_add_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|user_mode
c_func
(paren
id|regs
)paren
)paren
r_goto
id|user
suffix:semicolon
r_if
c_cond
(paren
id|LDST_L_BIT
c_func
(paren
id|instr
)paren
)paren
(brace
r_int
r_int
id|val
suffix:semicolon
id|get16_unaligned_check
c_func
(paren
id|val
comma
id|addr
)paren
suffix:semicolon
multiline_comment|/* signed half-word? */
r_if
c_cond
(paren
id|instr
op_amp
l_int|0x40
)paren
id|val
op_assign
(paren
r_int
r_int
)paren
(paren
(paren
r_int
r_int
)paren
id|val
)paren
suffix:semicolon
id|regs-&gt;uregs
(braket
id|rd
)braket
op_assign
id|val
suffix:semicolon
)brace
r_else
id|put16_unaligned_check
c_func
(paren
id|regs-&gt;uregs
(braket
id|rd
)braket
comma
id|addr
)paren
suffix:semicolon
r_return
id|TYPE_LDST
suffix:semicolon
id|user
suffix:colon
r_if
c_cond
(paren
id|LDST_L_BIT
c_func
(paren
id|instr
)paren
)paren
(brace
r_int
r_int
id|val
suffix:semicolon
id|get16t_unaligned_check
c_func
(paren
id|val
comma
id|addr
)paren
suffix:semicolon
multiline_comment|/* signed half-word? */
r_if
c_cond
(paren
id|instr
op_amp
l_int|0x40
)paren
id|val
op_assign
(paren
r_int
r_int
)paren
(paren
(paren
r_int
r_int
)paren
id|val
)paren
suffix:semicolon
id|regs-&gt;uregs
(braket
id|rd
)braket
op_assign
id|val
suffix:semicolon
)brace
r_else
id|put16t_unaligned_check
c_func
(paren
id|regs-&gt;uregs
(braket
id|rd
)braket
comma
id|addr
)paren
suffix:semicolon
r_return
id|TYPE_LDST
suffix:semicolon
id|swp
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Alignment trap: not handling swp instruction&bslash;n&quot;
)paren
suffix:semicolon
id|bad
suffix:colon
r_return
id|TYPE_ERROR
suffix:semicolon
id|fault
suffix:colon
r_return
id|TYPE_FAULT
suffix:semicolon
)brace
r_static
r_int
DECL|function|do_alignment_ldrstr
id|do_alignment_ldrstr
c_func
(paren
r_int
r_int
id|addr
comma
r_int
r_int
id|instr
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
r_int
id|rd
op_assign
id|RD_BITS
c_func
(paren
id|instr
)paren
suffix:semicolon
id|ai_word
op_add_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
(paren
op_logical_neg
id|LDST_P_BIT
c_func
(paren
id|instr
)paren
op_logical_and
id|LDST_W_BIT
c_func
(paren
id|instr
)paren
)paren
op_logical_or
id|user_mode
c_func
(paren
id|regs
)paren
)paren
r_goto
id|trans
suffix:semicolon
r_if
c_cond
(paren
id|LDST_L_BIT
c_func
(paren
id|instr
)paren
)paren
(brace
r_int
r_int
id|val
suffix:semicolon
id|get32_unaligned_check
c_func
(paren
id|val
comma
id|addr
)paren
suffix:semicolon
id|regs-&gt;uregs
(braket
id|rd
)braket
op_assign
id|val
suffix:semicolon
)brace
r_else
id|put32_unaligned_check
c_func
(paren
id|regs-&gt;uregs
(braket
id|rd
)braket
comma
id|addr
)paren
suffix:semicolon
r_return
id|TYPE_LDST
suffix:semicolon
id|trans
suffix:colon
r_if
c_cond
(paren
id|LDST_L_BIT
c_func
(paren
id|instr
)paren
)paren
(brace
r_int
r_int
id|val
suffix:semicolon
id|get32t_unaligned_check
c_func
(paren
id|val
comma
id|addr
)paren
suffix:semicolon
id|regs-&gt;uregs
(braket
id|rd
)braket
op_assign
id|val
suffix:semicolon
)brace
r_else
id|put32t_unaligned_check
c_func
(paren
id|regs-&gt;uregs
(braket
id|rd
)braket
comma
id|addr
)paren
suffix:semicolon
r_return
id|TYPE_LDST
suffix:semicolon
id|fault
suffix:colon
r_return
id|TYPE_FAULT
suffix:semicolon
)brace
multiline_comment|/*&n; * LDM/STM alignment handler.&n; *&n; * There are 4 variants of this instruction:&n; *&n; * B = rn pointer before instruction, A = rn pointer after instruction&n; *              ------ increasing address -----&gt;&n; *&t;        |    | r0 | r1 | ... | rx |    |&n; * PU = 01             B                    A&n; * PU = 11        B                    A&n; * PU = 00        A                    B&n; * PU = 10             A                    B&n; */
r_static
r_int
DECL|function|do_alignment_ldmstm
id|do_alignment_ldmstm
c_func
(paren
r_int
r_int
id|addr
comma
r_int
r_int
id|instr
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
r_int
id|rd
comma
id|rn
comma
id|correction
comma
id|nr_regs
comma
id|regbits
suffix:semicolon
r_int
r_int
id|eaddr
comma
id|newaddr
suffix:semicolon
r_if
c_cond
(paren
id|LDM_S_BIT
c_func
(paren
id|instr
)paren
)paren
r_goto
id|bad
suffix:semicolon
id|correction
op_assign
l_int|4
suffix:semicolon
multiline_comment|/* processor implementation defined */
id|regs-&gt;ARM_pc
op_add_assign
id|correction
suffix:semicolon
id|ai_multi
op_add_assign
l_int|1
suffix:semicolon
multiline_comment|/* count the number of registers in the mask to be transferred */
id|nr_regs
op_assign
id|hweight16
c_func
(paren
id|REGMASK_BITS
c_func
(paren
id|instr
)paren
)paren
op_star
l_int|4
suffix:semicolon
id|rn
op_assign
id|RN_BITS
c_func
(paren
id|instr
)paren
suffix:semicolon
id|newaddr
op_assign
id|eaddr
op_assign
id|regs-&gt;uregs
(braket
id|rn
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|LDST_U_BIT
c_func
(paren
id|instr
)paren
)paren
id|nr_regs
op_assign
op_minus
id|nr_regs
suffix:semicolon
id|newaddr
op_add_assign
id|nr_regs
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|LDST_U_BIT
c_func
(paren
id|instr
)paren
)paren
id|eaddr
op_assign
id|newaddr
suffix:semicolon
r_if
c_cond
(paren
id|LDST_P_EQ_U
c_func
(paren
id|instr
)paren
)paren
multiline_comment|/* U = P */
id|eaddr
op_add_assign
l_int|4
suffix:semicolon
multiline_comment|/* &n;&t; * For alignment faults on the ARM922T/ARM920T the MMU  makes&n;&t; * the FSR (and hence addr) equal to the updated base address&n;&t; * of the multiple access rather than the restored value.&n;&t; * Switch this message off if we&squot;ve got a ARM92[02], otherwise&n;&t; * [ls]dm alignment faults are noisy!&n;&t; */
macro_line|#if !(defined CONFIG_CPU_ARM922T)  &amp;&amp; !(defined CONFIG_CPU_ARM920T)
multiline_comment|/*&n;&t; * This is a &quot;hint&quot; - we already have eaddr worked out by the&n;&t; * processor for us.&n;&t; */
r_if
c_cond
(paren
id|addr
op_ne
id|eaddr
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;LDMSTM: PC = %08lx, instr = %08lx, &quot;
l_string|&quot;addr = %08lx, eaddr = %08lx&bslash;n&quot;
comma
id|instruction_pointer
c_func
(paren
id|regs
)paren
comma
id|instr
comma
id|addr
comma
id|eaddr
)paren
suffix:semicolon
id|show_regs
c_func
(paren
id|regs
)paren
suffix:semicolon
)brace
macro_line|#endif
r_if
c_cond
(paren
id|user_mode
c_func
(paren
id|regs
)paren
)paren
(brace
r_for
c_loop
(paren
id|regbits
op_assign
id|REGMASK_BITS
c_func
(paren
id|instr
)paren
comma
id|rd
op_assign
l_int|0
suffix:semicolon
id|regbits
suffix:semicolon
id|regbits
op_rshift_assign
l_int|1
comma
id|rd
op_add_assign
l_int|1
)paren
r_if
c_cond
(paren
id|regbits
op_amp
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|LDST_L_BIT
c_func
(paren
id|instr
)paren
)paren
(brace
r_int
r_int
id|val
suffix:semicolon
id|get32t_unaligned_check
c_func
(paren
id|val
comma
id|eaddr
)paren
suffix:semicolon
id|regs-&gt;uregs
(braket
id|rd
)braket
op_assign
id|val
suffix:semicolon
)brace
r_else
id|put32t_unaligned_check
c_func
(paren
id|regs-&gt;uregs
(braket
id|rd
)braket
comma
id|eaddr
)paren
suffix:semicolon
id|eaddr
op_add_assign
l_int|4
suffix:semicolon
)brace
)brace
r_else
(brace
r_for
c_loop
(paren
id|regbits
op_assign
id|REGMASK_BITS
c_func
(paren
id|instr
)paren
comma
id|rd
op_assign
l_int|0
suffix:semicolon
id|regbits
suffix:semicolon
id|regbits
op_rshift_assign
l_int|1
comma
id|rd
op_add_assign
l_int|1
)paren
r_if
c_cond
(paren
id|regbits
op_amp
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|LDST_L_BIT
c_func
(paren
id|instr
)paren
)paren
(brace
r_int
r_int
id|val
suffix:semicolon
id|get32_unaligned_check
c_func
(paren
id|val
comma
id|eaddr
)paren
suffix:semicolon
id|regs-&gt;uregs
(braket
id|rd
)braket
op_assign
id|val
suffix:semicolon
)brace
r_else
id|put32_unaligned_check
c_func
(paren
id|regs-&gt;uregs
(braket
id|rd
)braket
comma
id|eaddr
)paren
suffix:semicolon
id|eaddr
op_add_assign
l_int|4
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|LDST_W_BIT
c_func
(paren
id|instr
)paren
)paren
id|regs-&gt;uregs
(braket
id|rn
)braket
op_assign
id|newaddr
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|LDST_L_BIT
c_func
(paren
id|instr
)paren
op_logical_or
op_logical_neg
(paren
id|REGMASK_BITS
c_func
(paren
id|instr
)paren
op_amp
(paren
l_int|1
op_lshift
l_int|15
)paren
)paren
)paren
id|regs-&gt;ARM_pc
op_sub_assign
id|correction
suffix:semicolon
r_return
id|TYPE_DONE
suffix:semicolon
id|fault
suffix:colon
id|regs-&gt;ARM_pc
op_sub_assign
id|correction
suffix:semicolon
r_return
id|TYPE_FAULT
suffix:semicolon
id|bad
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Alignment trap: not handling ldm with s-bit set&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|TYPE_ERROR
suffix:semicolon
)brace
r_static
r_int
DECL|function|do_alignment
id|do_alignment
c_func
(paren
r_int
r_int
id|addr
comma
r_int
r_int
id|fsr
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_union
id|offset_union
id|offset
suffix:semicolon
r_int
r_int
id|instr
comma
id|instrptr
suffix:semicolon
r_int
(paren
op_star
id|handler
)paren
(paren
r_int
r_int
id|addr
comma
r_int
r_int
id|instr
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_int
r_int
id|type
suffix:semicolon
id|instrptr
op_assign
id|instruction_pointer
c_func
(paren
id|regs
)paren
suffix:semicolon
id|instr
op_assign
op_star
(paren
r_int
r_int
op_star
)paren
id|instrptr
suffix:semicolon
r_if
c_cond
(paren
id|user_mode
c_func
(paren
id|regs
)paren
)paren
r_goto
id|user
suffix:semicolon
id|ai_sys
op_add_assign
l_int|1
suffix:semicolon
id|fixup
suffix:colon
id|regs-&gt;ARM_pc
op_add_assign
l_int|4
suffix:semicolon
r_switch
c_cond
(paren
id|CODING_BITS
c_func
(paren
id|instr
)paren
)paren
(brace
r_case
l_int|0x00000000
suffix:colon
multiline_comment|/* ldrh or strh */
r_if
c_cond
(paren
id|LDSTH_I_BIT
c_func
(paren
id|instr
)paren
)paren
id|offset.un
op_assign
(paren
id|instr
op_amp
l_int|0xf00
)paren
op_rshift
l_int|4
op_or
(paren
id|instr
op_amp
l_int|15
)paren
suffix:semicolon
r_else
id|offset.un
op_assign
id|regs-&gt;uregs
(braket
id|RM_BITS
c_func
(paren
id|instr
)paren
)braket
suffix:semicolon
id|handler
op_assign
id|do_alignment_ldrhstrh
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x04000000
suffix:colon
multiline_comment|/* ldr or str immediate */
id|offset.un
op_assign
id|OFFSET_BITS
c_func
(paren
id|instr
)paren
suffix:semicolon
id|handler
op_assign
id|do_alignment_ldrstr
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x06000000
suffix:colon
multiline_comment|/* ldr or str register */
id|offset.un
op_assign
id|regs-&gt;uregs
(braket
id|RM_BITS
c_func
(paren
id|instr
)paren
)braket
suffix:semicolon
r_if
c_cond
(paren
id|IS_SHIFT
c_func
(paren
id|instr
)paren
)paren
(brace
r_int
r_int
id|shiftval
op_assign
id|SHIFT_BITS
c_func
(paren
id|instr
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|SHIFT_TYPE
c_func
(paren
id|instr
)paren
)paren
(brace
r_case
id|SHIFT_LSL
suffix:colon
id|offset.un
op_lshift_assign
id|shiftval
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SHIFT_LSR
suffix:colon
id|offset.un
op_rshift_assign
id|shiftval
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SHIFT_ASR
suffix:colon
id|offset.sn
op_rshift_assign
id|shiftval
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SHIFT_RORRRX
suffix:colon
r_if
c_cond
(paren
id|shiftval
op_eq
l_int|0
)paren
(brace
id|offset.un
op_rshift_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|regs-&gt;ARM_cpsr
op_amp
id|PSR_C_BIT
)paren
id|offset.un
op_or_assign
l_int|1
op_lshift
l_int|31
suffix:semicolon
)brace
r_else
id|offset.un
op_assign
id|offset.un
op_rshift
id|shiftval
op_or
id|offset.un
op_lshift
(paren
l_int|32
op_minus
id|shiftval
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|handler
op_assign
id|do_alignment_ldrstr
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x08000000
suffix:colon
multiline_comment|/* ldm or stm */
id|handler
op_assign
id|do_alignment_ldmstm
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_goto
id|bad
suffix:semicolon
)brace
id|type
op_assign
id|handler
c_func
(paren
id|addr
comma
id|instr
comma
id|regs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|type
op_eq
id|TYPE_ERROR
op_logical_or
id|type
op_eq
id|TYPE_FAULT
)paren
r_goto
id|bad_or_fault
suffix:semicolon
r_if
c_cond
(paren
id|type
op_eq
id|TYPE_LDST
)paren
id|do_alignment_finish_ldst
c_func
(paren
id|addr
comma
id|instr
comma
id|regs
comma
id|offset
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|bad_or_fault
suffix:colon
r_if
c_cond
(paren
id|type
op_eq
id|TYPE_ERROR
)paren
r_goto
id|bad
suffix:semicolon
id|regs-&gt;ARM_pc
op_sub_assign
l_int|4
suffix:semicolon
multiline_comment|/*&n;&t; * We got a fault - fix it up, or die.&n;&t; */
id|do_bad_area
c_func
(paren
id|current
comma
id|current-&gt;mm
comma
id|addr
comma
id|fsr
comma
id|regs
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|bad
suffix:colon
multiline_comment|/*&n;&t; * Oops, we didn&squot;t handle the instruction.&n;&t; */
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Alignment trap: not handling instruction &quot;
l_string|&quot;%08lx at [&lt;%08lx&gt;]&bslash;n&quot;
comma
id|instr
comma
id|instrptr
)paren
suffix:semicolon
id|ai_skipped
op_add_assign
l_int|1
suffix:semicolon
r_return
l_int|1
suffix:semicolon
id|user
suffix:colon
id|ai_user
op_add_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|ai_usermode
op_amp
l_int|1
)paren
id|printk
c_func
(paren
l_string|&quot;Alignment trap: %s (%d) PC=0x%08lx Instr=0x%08lx &quot;
l_string|&quot;Address=0x%08lx FSR 0x%03x&bslash;n&quot;
comma
id|current-&gt;comm
comma
id|current-&gt;pid
comma
id|instrptr
comma
id|instr
comma
id|addr
comma
id|fsr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ai_usermode
op_amp
l_int|2
)paren
r_goto
id|fixup
suffix:semicolon
r_if
c_cond
(paren
id|ai_usermode
op_amp
l_int|4
)paren
id|force_sig
c_func
(paren
id|SIGBUS
comma
id|current
)paren
suffix:semicolon
r_else
id|set_cr
c_func
(paren
id|cr_no_alignment
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * This needs to be done after sysctl_init, otherwise sys/ will be&n; * overwritten.  Actually, this shouldn&squot;t be in sys/ at all since&n; * it isn&squot;t a sysctl, and it doesn&squot;t contain sysctl information.&n; * We now locate it in /proc/cpu/alignment instead.&n; */
DECL|function|alignment_init
r_static
r_int
id|__init
id|alignment_init
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_PROC_FS
r_struct
id|proc_dir_entry
op_star
id|res
suffix:semicolon
id|res
op_assign
id|proc_mkdir
c_func
(paren
l_string|&quot;cpu&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|res
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|res
op_assign
id|create_proc_entry
c_func
(paren
l_string|&quot;alignment&quot;
comma
id|S_IWUSR
op_or
id|S_IRUGO
comma
id|res
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|res
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|res-&gt;read_proc
op_assign
id|proc_alignment_read
suffix:semicolon
id|res-&gt;write_proc
op_assign
id|proc_alignment_write
suffix:semicolon
macro_line|#endif
id|hook_fault_code
c_func
(paren
l_int|1
comma
id|do_alignment
comma
id|SIGILL
comma
l_string|&quot;alignment exception&quot;
)paren
suffix:semicolon
id|hook_fault_code
c_func
(paren
l_int|3
comma
id|do_alignment
comma
id|SIGILL
comma
l_string|&quot;alignment exception&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|alignment_init
id|fs_initcall
c_func
(paren
id|alignment_init
)paren
suffix:semicolon
eof
