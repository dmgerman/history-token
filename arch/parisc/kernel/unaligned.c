multiline_comment|/*    $Id: unaligned.c,v 1.1 2002/07/20 16:27:06 rhirst Exp $&n; *&n; *    Unaligned memory access handler&n; *&n; *    Copyright (C) 2001 Randolph Chung &lt;tausq@debian.org&gt;&n; *&n; *    This program is free software; you can redistribute it and/or modify&n; *    it under the terms of the GNU General Public License as published by&n; *    the Free Software Foundation; either version 2, or (at your option)&n; *    any later version.&n; *&n; *    This program is distributed in the hope that it will be useful,&n; *    but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *    GNU General Public License for more details.&n; *&n; *    You should have received a copy of the GNU General Public License&n; *    along with this program; if not, write to the Free Software&n; *    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#include &lt;asm/pdc.h&gt;
multiline_comment|/* #define DEBUG_UNALIGNED 1 */
macro_line|#ifdef DEBUG_UNALIGNED
DECL|macro|DPRINTF
mdefine_line|#define DPRINTF(fmt, args...) do { printk(KERN_DEBUG &quot;%s:%d:%s &quot;, __FILE__, __LINE__, __FUNCTION__ ); printk(KERN_DEBUG fmt, ##args ); } while (0)
macro_line|#else
DECL|macro|DPRINTF
mdefine_line|#define DPRINTF(fmt, args...)
macro_line|#endif
macro_line|#ifdef __LP64__
DECL|macro|RFMT
mdefine_line|#define RFMT &quot;%016lx&quot;
macro_line|#else
DECL|macro|RFMT
mdefine_line|#define RFMT &quot;%08lx&quot;
macro_line|#endif
multiline_comment|/* 1111 1100 0000 0000 0001 0011 1100 0000 */
DECL|macro|OPCODE1
mdefine_line|#define OPCODE1(a,b,c)&t;((a)&lt;&lt;26|(b)&lt;&lt;12|(c)&lt;&lt;6) 
DECL|macro|OPCODE2
mdefine_line|#define OPCODE2(a,b)&t;((a)&lt;&lt;26|(b)&lt;&lt;1)
DECL|macro|OPCODE3
mdefine_line|#define OPCODE3(a,b)&t;((a)&lt;&lt;26|(b)&lt;&lt;2)
DECL|macro|OPCODE4
mdefine_line|#define OPCODE4(a)&t;((a)&lt;&lt;26)
DECL|macro|OPCODE1_MASK
mdefine_line|#define OPCODE1_MASK&t;OPCODE1(0x3f,1,0xf)
DECL|macro|OPCODE2_MASK
mdefine_line|#define OPCODE2_MASK &t;OPCODE2(0x3f,1)
DECL|macro|OPCODE3_MASK
mdefine_line|#define OPCODE3_MASK&t;OPCODE3(0x3f,1)
DECL|macro|OPCODE4_MASK
mdefine_line|#define OPCODE4_MASK    OPCODE4(0x3f)
multiline_comment|/* skip LDB (index) */
DECL|macro|OPCODE_LDH_I
mdefine_line|#define OPCODE_LDH_I&t;OPCODE1(0x03,0,0x1)
DECL|macro|OPCODE_LDW_I
mdefine_line|#define OPCODE_LDW_I&t;OPCODE1(0x03,0,0x2)
DECL|macro|OPCODE_LDD_I
mdefine_line|#define OPCODE_LDD_I&t;OPCODE1(0x03,0,0x3)
DECL|macro|OPCODE_LDDA_I
mdefine_line|#define OPCODE_LDDA_I&t;OPCODE1(0x03,0,0x4)
multiline_comment|/* skip LDCD (index) */
DECL|macro|OPCODE_LDWA_I
mdefine_line|#define OPCODE_LDWA_I&t;OPCODE1(0x03,0,0x6)
multiline_comment|/* skip LDCW (index) */
multiline_comment|/* skip LDB (short) */
DECL|macro|OPCODE_LDH_S
mdefine_line|#define OPCODE_LDH_S&t;OPCODE1(0x03,1,0x1)
DECL|macro|OPCODE_LDW_S
mdefine_line|#define OPCODE_LDW_S&t;OPCODE1(0x03,1,0x2)
DECL|macro|OPCODE_LDD_S
mdefine_line|#define OPCODE_LDD_S&t;OPCODE1(0x03,1,0x3)
DECL|macro|OPCODE_LDDA_S
mdefine_line|#define OPCODE_LDDA_S&t;OPCODE1(0x03,1,0x4)
multiline_comment|/* skip LDCD (short) */
DECL|macro|OPCODE_LDWA_S
mdefine_line|#define OPCODE_LDWA_S&t;OPCODE1(0x03,1,0x6)
multiline_comment|/* skip LDCW (short) */
multiline_comment|/* skip STB */
DECL|macro|OPCODE_STH
mdefine_line|#define OPCODE_STH&t;OPCODE1(0x03,1,0x9)
DECL|macro|OPCODE_STW
mdefine_line|#define OPCODE_STW&t;OPCODE1(0x03,1,0xa)
DECL|macro|OPCODE_STD
mdefine_line|#define OPCODE_STD&t;OPCODE1(0x03,1,0xb)
multiline_comment|/* skip STBY */
multiline_comment|/* skip STDBY */
DECL|macro|OPCODE_STWA
mdefine_line|#define OPCODE_STWA&t;OPCODE1(0x03,1,0xe)
DECL|macro|OPCODE_STDA
mdefine_line|#define OPCODE_STDA&t;OPCODE1(0x03,1,0xf)
DECL|macro|OPCODE_LDD_L
mdefine_line|#define OPCODE_LDD_L&t;OPCODE2(0x14,0)
DECL|macro|OPCODE_FLDD_L
mdefine_line|#define OPCODE_FLDD_L&t;OPCODE2(0x14,1)
DECL|macro|OPCODE_STD_L
mdefine_line|#define OPCODE_STD_L&t;OPCODE2(0x1c,0)
DECL|macro|OPCODE_FSTD_L
mdefine_line|#define OPCODE_FSTD_L&t;OPCODE2(0x1c,1)
DECL|macro|OPCODE_LDW_M
mdefine_line|#define OPCODE_LDW_M&t;OPCODE3(0x17,1)
DECL|macro|OPCODE_FLDW_L
mdefine_line|#define OPCODE_FLDW_L&t;OPCODE3(0x17,0)
DECL|macro|OPCODE_FSTW_L
mdefine_line|#define OPCODE_FSTW_L&t;OPCODE3(0x1f,0)
DECL|macro|OPCODE_STW_M
mdefine_line|#define OPCODE_STW_M&t;OPCODE3(0x1f,1)
DECL|macro|OPCODE_LDH_L
mdefine_line|#define OPCODE_LDH_L    OPCODE4(0x11)
DECL|macro|OPCODE_LDW_L
mdefine_line|#define OPCODE_LDW_L    OPCODE4(0x12)
DECL|macro|OPCODE_LDW_L2
mdefine_line|#define OPCODE_LDW_L2   OPCODE4(0x13)
DECL|macro|OPCODE_STH_L
mdefine_line|#define OPCODE_STH_L    OPCODE4(0x19)
DECL|macro|OPCODE_STW_L
mdefine_line|#define OPCODE_STW_L    OPCODE4(0x1A)
DECL|macro|OPCODE_STW_L2
mdefine_line|#define OPCODE_STW_L2   OPCODE4(0x1B)
r_void
id|die_if_kernel
(paren
r_char
op_star
id|str
comma
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
id|err
)paren
suffix:semicolon
DECL|function|emulate_load
r_static
r_int
id|emulate_load
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
id|len
comma
r_int
id|toreg
)paren
(brace
r_int
r_int
id|saddr
op_assign
id|regs-&gt;ior
suffix:semicolon
r_int
r_int
id|val
op_assign
l_int|0
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|regs-&gt;isr
op_ne
id|regs-&gt;sr
(braket
l_int|7
)braket
)paren
(brace
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;isr verification failed (isr: &quot;
id|RFMT
l_string|&quot;, sr7: &quot;
id|RFMT
l_string|&quot;&bslash;n&quot;
comma
id|regs-&gt;isr
comma
id|regs-&gt;sr
(braket
l_int|7
)braket
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|DPRINTF
c_func
(paren
l_string|&quot;load &quot;
id|RFMT
l_string|&quot;:&quot;
id|RFMT
l_string|&quot; to r%d for %d bytes&bslash;n&quot;
comma
id|regs-&gt;isr
comma
id|regs-&gt;ior
comma
id|toreg
comma
id|len
)paren
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;       mfsp %%sr1, %%r20&bslash;n&quot;
l_string|&quot;       mtsp %6, %%sr1&bslash;n&quot;
l_string|&quot;&t;copy %%r0, %0&bslash;n&quot;
l_string|&quot;0:&t;ldbs,ma&t;1(%%sr1,%4), %%r19&bslash;n&quot;
l_string|&quot;&t;addi -1, %5, %5&bslash;n&quot;
l_string|&quot;&t;cmpib,&gt;= 0, %5, 2f&bslash;n&quot;
l_string|&quot;&t;or %%r19, %0, %0&bslash;n&quot;
l_string|&quot;&t;b 0b&bslash;n&quot;
macro_line|#ifdef __LP64__
l_string|&quot;depd,z %0, 55, 56, %0&bslash;n&quot;
macro_line|#else
l_string|&quot;depw,z %0, 23, 24, %0&bslash;n&quot;
macro_line|#endif
l_string|&quot;1:&t;ldi&t;10, %1&bslash;n&quot;
l_string|&quot;2:     mtsp %%r20, %%sr1&bslash;n&quot;
l_string|&quot;&t;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;
macro_line|#ifdef __LP64__
l_string|&quot;.dword 0b, (1b-0b)&bslash;n&quot;
macro_line|#else
l_string|&quot;.word 0b, (1b-0b)&bslash;n&quot;
macro_line|#endif
l_string|&quot;.previous&bslash;n&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|val
)paren
comma
l_string|&quot;=r&quot;
(paren
id|ret
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|val
)paren
comma
l_string|&quot;1&quot;
(paren
id|ret
)paren
comma
l_string|&quot;r&quot;
(paren
id|saddr
)paren
comma
l_string|&quot;r&quot;
(paren
id|len
)paren
comma
l_string|&quot;r&quot;
(paren
id|regs-&gt;isr
)paren
suffix:colon
l_string|&quot;r19&quot;
comma
l_string|&quot;r20&quot;
)paren
suffix:semicolon
id|DPRINTF
c_func
(paren
l_string|&quot;val = 0x&quot;
id|RFMT
l_string|&quot;&bslash;n&quot;
comma
id|val
)paren
suffix:semicolon
id|regs-&gt;gr
(braket
id|toreg
)braket
op_assign
id|val
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|emulate_store
r_static
r_int
id|emulate_store
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
id|len
comma
r_int
id|frreg
)paren
(brace
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef __LP64__
r_int
r_int
id|val
op_assign
id|regs-&gt;gr
(braket
id|frreg
)braket
op_lshift
(paren
l_int|64
op_minus
(paren
id|len
op_lshift
l_int|3
)paren
)paren
suffix:semicolon
macro_line|#else
r_int
r_int
id|val
op_assign
id|regs-&gt;gr
(braket
id|frreg
)braket
op_lshift
(paren
l_int|32
op_minus
(paren
id|len
op_lshift
l_int|3
)paren
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|regs-&gt;isr
op_ne
id|regs-&gt;sr
(braket
l_int|7
)braket
)paren
(brace
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;isr verification failed (isr: &quot;
id|RFMT
l_string|&quot;, sr7: &quot;
id|RFMT
l_string|&quot;&bslash;n&quot;
comma
id|regs-&gt;isr
comma
id|regs-&gt;sr
(braket
l_int|7
)braket
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|DPRINTF
c_func
(paren
l_string|&quot;store r%d (0x&quot;
id|RFMT
l_string|&quot;) to &quot;
id|RFMT
l_string|&quot;:&quot;
id|RFMT
l_string|&quot; for %d bytes&bslash;n&quot;
comma
id|frreg
comma
id|regs-&gt;gr
(braket
id|frreg
)braket
comma
id|regs-&gt;isr
comma
id|regs-&gt;ior
comma
id|len
)paren
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;       mfsp %%sr1, %%r20&bslash;n&quot;
multiline_comment|/* save sr1 */
l_string|&quot;       mtsp %5, %%sr1&bslash;n&quot;
macro_line|#ifdef __LP64__
l_string|&quot;0:&t;extrd,u %2, 7, 8, %%r19&bslash;n&quot;
macro_line|#else
l_string|&quot;0:&t;extrw,u %2, 7, 8, %%r19&bslash;n&quot;
macro_line|#endif
l_string|&quot;1:&t;stb,ma %%r19, 1(%%sr1, %3)&bslash;n&quot;
l_string|&quot;&t;addi -1, %4, %4&bslash;n&quot;
l_string|&quot;&t;cmpib,&gt;= 0, %4, 3f&bslash;n&quot;
macro_line|#ifdef __LP64__
l_string|&quot;depd,z %2, 55, 56, %2&bslash;n&quot;
macro_line|#else
l_string|&quot;depw,z %2, 23, 24, %2&bslash;n&quot;
macro_line|#endif
l_string|&quot;&t;b 0b&bslash;n&quot;
l_string|&quot;&t;nop&bslash;n&quot;
l_string|&quot;2:&t;ldi 11, %0&bslash;n&quot;
l_string|&quot;3:     mtsp %%r20, %%sr1&bslash;n&quot;
l_string|&quot;&t;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;
macro_line|#ifdef __LP64__
l_string|&quot;.dword 1b, (2b-1b)&bslash;n&quot;
macro_line|#else
l_string|&quot;.word 1b, (2b-1b)&bslash;n&quot;
macro_line|#endif
l_string|&quot;.previous&bslash;n&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|ret
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|ret
)paren
comma
l_string|&quot;r&quot;
(paren
id|val
)paren
comma
l_string|&quot;r&quot;
(paren
id|regs-&gt;ior
)paren
comma
l_string|&quot;r&quot;
(paren
id|len
)paren
comma
l_string|&quot;r&quot;
(paren
id|regs-&gt;isr
)paren
suffix:colon
l_string|&quot;r19&quot;
comma
l_string|&quot;r20&quot;
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|handle_unaligned
r_void
id|handle_unaligned
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
r_int
id|unaligned_count
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|last_time
op_assign
l_int|0
suffix:semicolon
r_int
id|ret
op_assign
op_minus
l_int|1
suffix:semicolon
r_struct
id|siginfo
id|si
suffix:semicolon
multiline_comment|/* if the unaligned access is inside the kernel:&n;&t; *   if the access is caused by a syscall, then we fault the calling&n;&t; *     user process&n;&t; *   otherwise we halt the kernel&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|user_mode
c_func
(paren
id|regs
)paren
)paren
(brace
r_const
r_struct
id|exception_table_entry
op_star
id|fix
suffix:semicolon
multiline_comment|/* see if the offending code have its own&n;&t;&t; * exception handler &n;&t;&t; */
id|fix
op_assign
id|search_exception_table
c_func
(paren
id|regs-&gt;iaoq
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fix
)paren
(brace
multiline_comment|/* lower bits of fix-&gt;skip are flags&n;&t;&t;&t; * upper bits are the handler addr&n;&t;&t;&t; */
r_if
c_cond
(paren
id|fix-&gt;skip
op_amp
l_int|1
)paren
id|regs-&gt;gr
(braket
l_int|8
)braket
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|fix-&gt;skip
op_amp
l_int|2
)paren
id|regs-&gt;gr
(braket
l_int|9
)braket
op_assign
l_int|0
suffix:semicolon
id|regs-&gt;iaoq
(braket
l_int|0
)braket
op_add_assign
(paren
(paren
id|fix-&gt;skip
)paren
op_amp
op_complement
l_int|3
)paren
suffix:semicolon
id|regs-&gt;iaoq
(braket
l_int|1
)braket
op_assign
id|regs-&gt;iaoq
(braket
l_int|0
)braket
op_plus
l_int|4
suffix:semicolon
id|regs-&gt;gr
(braket
l_int|0
)braket
op_and_assign
op_complement
id|PSW_B
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
multiline_comment|/* log a message with pacing */
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
r_if
c_cond
(paren
id|unaligned_count
OG
l_int|5
op_logical_and
id|jiffies
op_minus
id|last_time
OG
l_int|5
op_star
id|HZ
)paren
(brace
id|unaligned_count
op_assign
l_int|0
suffix:semicolon
id|last_time
op_assign
id|jiffies
suffix:semicolon
)brace
r_if
c_cond
(paren
op_increment
id|unaligned_count
OL
l_int|5
)paren
(brace
r_char
id|buf
(braket
l_int|256
)braket
suffix:semicolon
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;%s(%d): unaligned access to 0x&quot;
id|RFMT
l_string|&quot; at ip=0x&quot;
id|RFMT
l_string|&quot;&bslash;n&quot;
comma
id|current-&gt;comm
comma
id|current-&gt;pid
comma
id|regs-&gt;ior
comma
id|regs-&gt;iaoq
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s&quot;
comma
id|buf
)paren
suffix:semicolon
macro_line|#ifdef DEBUG_UNALIGNED
id|show_regs
c_func
(paren
id|regs
)paren
suffix:semicolon
macro_line|#endif&t;&t;
)brace
)brace
multiline_comment|/* TODO: make this cleaner... */
r_switch
c_cond
(paren
id|regs-&gt;iir
op_amp
id|OPCODE1_MASK
)paren
(brace
r_case
id|OPCODE_LDH_I
suffix:colon
r_case
id|OPCODE_LDH_S
suffix:colon
id|ret
op_assign
id|emulate_load
c_func
(paren
id|regs
comma
l_int|2
comma
id|regs-&gt;iir
op_amp
l_int|0x1f
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OPCODE_LDW_I
suffix:colon
r_case
id|OPCODE_LDWA_I
suffix:colon
r_case
id|OPCODE_LDW_S
suffix:colon
r_case
id|OPCODE_LDWA_S
suffix:colon
id|ret
op_assign
id|emulate_load
c_func
(paren
id|regs
comma
l_int|4
comma
id|regs-&gt;iir
op_amp
l_int|0x1f
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OPCODE_LDD_I
suffix:colon
r_case
id|OPCODE_LDDA_I
suffix:colon
r_case
id|OPCODE_LDD_S
suffix:colon
r_case
id|OPCODE_LDDA_S
suffix:colon
id|ret
op_assign
id|emulate_load
c_func
(paren
id|regs
comma
l_int|8
comma
id|regs-&gt;iir
op_amp
l_int|0x1f
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OPCODE_STH
suffix:colon
id|ret
op_assign
id|emulate_store
c_func
(paren
id|regs
comma
l_int|2
comma
(paren
id|regs-&gt;iir
op_rshift
l_int|16
)paren
op_amp
l_int|0x1f
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OPCODE_STW
suffix:colon
r_case
id|OPCODE_STWA
suffix:colon
id|ret
op_assign
id|emulate_store
c_func
(paren
id|regs
comma
l_int|4
comma
(paren
id|regs-&gt;iir
op_rshift
l_int|16
)paren
op_amp
l_int|0x1f
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OPCODE_STD
suffix:colon
r_case
id|OPCODE_STDA
suffix:colon
id|ret
op_assign
id|emulate_store
c_func
(paren
id|regs
comma
l_int|8
comma
(paren
id|regs-&gt;iir
op_rshift
l_int|16
)paren
op_amp
l_int|0x1f
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|regs-&gt;iir
op_amp
id|OPCODE2_MASK
)paren
(brace
r_case
id|OPCODE_LDD_L
suffix:colon
r_case
id|OPCODE_FLDD_L
suffix:colon
id|ret
op_assign
id|emulate_load
c_func
(paren
id|regs
comma
l_int|8
comma
(paren
id|regs-&gt;iir
op_rshift
l_int|16
)paren
op_amp
l_int|0x1f
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OPCODE_STD_L
suffix:colon
r_case
id|OPCODE_FSTD_L
suffix:colon
id|ret
op_assign
id|emulate_store
c_func
(paren
id|regs
comma
l_int|8
comma
(paren
id|regs-&gt;iir
op_rshift
l_int|16
)paren
op_amp
l_int|0x1f
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|regs-&gt;iir
op_amp
id|OPCODE3_MASK
)paren
(brace
r_case
id|OPCODE_LDW_M
suffix:colon
r_case
id|OPCODE_FLDW_L
suffix:colon
id|ret
op_assign
id|emulate_load
c_func
(paren
id|regs
comma
l_int|4
comma
(paren
id|regs-&gt;iir
op_rshift
l_int|16
)paren
op_amp
l_int|0x1f
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OPCODE_FSTW_L
suffix:colon
r_case
id|OPCODE_STW_M
suffix:colon
id|ret
op_assign
id|emulate_store
c_func
(paren
id|regs
comma
l_int|4
comma
(paren
id|regs-&gt;iir
op_rshift
l_int|16
)paren
op_amp
l_int|0x1f
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|regs-&gt;iir
op_amp
id|OPCODE4_MASK
)paren
(brace
r_case
id|OPCODE_LDH_L
suffix:colon
id|ret
op_assign
id|emulate_load
c_func
(paren
id|regs
comma
l_int|2
comma
(paren
id|regs-&gt;iir
op_rshift
l_int|16
)paren
op_amp
l_int|0x1f
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OPCODE_LDW_L
suffix:colon
r_case
id|OPCODE_LDW_L2
suffix:colon
id|ret
op_assign
id|emulate_load
c_func
(paren
id|regs
comma
l_int|4
comma
(paren
id|regs-&gt;iir
op_rshift
l_int|16
)paren
op_amp
l_int|0x1f
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OPCODE_STH_L
suffix:colon
id|ret
op_assign
id|emulate_store
c_func
(paren
id|regs
comma
l_int|2
comma
(paren
id|regs-&gt;iir
op_rshift
l_int|16
)paren
op_amp
l_int|0x1f
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OPCODE_STW_L
suffix:colon
r_case
id|OPCODE_STW_L2
suffix:colon
id|ret
op_assign
id|emulate_store
c_func
(paren
id|regs
comma
l_int|4
comma
(paren
id|regs-&gt;iir
op_rshift
l_int|16
)paren
op_amp
l_int|0x1f
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;Not-handled unaligned insn 0x%08lx&bslash;n&quot;
comma
id|regs-&gt;iir
)paren
suffix:semicolon
id|DPRINTF
c_func
(paren
l_string|&quot;ret = %d&bslash;n&quot;
comma
id|ret
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;Unaligned handler failed, ret = %d&bslash;n&quot;
comma
id|ret
)paren
suffix:semicolon
id|die_if_kernel
c_func
(paren
l_string|&quot;Unaligned data reference&quot;
comma
id|regs
comma
l_int|28
)paren
suffix:semicolon
multiline_comment|/* couldn&squot;t handle it ... */
id|si.si_signo
op_assign
id|SIGBUS
suffix:semicolon
id|si.si_errno
op_assign
l_int|0
suffix:semicolon
id|si.si_code
op_assign
id|BUS_ADRALN
suffix:semicolon
id|si.si_addr
op_assign
(paren
r_void
op_star
)paren
id|regs-&gt;ior
suffix:semicolon
id|force_sig_info
c_func
(paren
id|SIGBUS
comma
op_amp
id|si
comma
id|current
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* else we handled it, advance the PC.... */
id|regs-&gt;iaoq
(braket
l_int|0
)braket
op_assign
id|regs-&gt;iaoq
(braket
l_int|1
)braket
suffix:semicolon
id|regs-&gt;iaoq
(braket
l_int|1
)braket
op_assign
id|regs-&gt;iaoq
(braket
l_int|0
)braket
op_plus
l_int|4
suffix:semicolon
)brace
multiline_comment|/*&n; * NB: check_unaligned() is only used for PCXS processors right&n; * now, so we only check for PA1.1 encodings at this point.&n; */
r_int
DECL|function|check_unaligned
id|check_unaligned
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
r_int
id|align_mask
suffix:semicolon
multiline_comment|/* Get alignment mask */
id|align_mask
op_assign
l_int|0UL
suffix:semicolon
r_switch
c_cond
(paren
id|regs-&gt;iir
op_amp
id|OPCODE1_MASK
)paren
(brace
r_case
id|OPCODE_LDH_I
suffix:colon
r_case
id|OPCODE_LDH_S
suffix:colon
r_case
id|OPCODE_STH
suffix:colon
id|align_mask
op_assign
l_int|1UL
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OPCODE_LDW_I
suffix:colon
r_case
id|OPCODE_LDWA_I
suffix:colon
r_case
id|OPCODE_LDW_S
suffix:colon
r_case
id|OPCODE_LDWA_S
suffix:colon
r_case
id|OPCODE_STW
suffix:colon
r_case
id|OPCODE_STWA
suffix:colon
id|align_mask
op_assign
l_int|3UL
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
(brace
)brace
r_switch
c_cond
(paren
id|regs-&gt;iir
op_amp
id|OPCODE4_MASK
)paren
(brace
r_case
id|OPCODE_LDH_L
suffix:colon
r_case
id|OPCODE_STH_L
suffix:colon
id|align_mask
op_assign
l_int|1UL
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OPCODE_LDW_L
suffix:colon
r_case
id|OPCODE_LDW_L2
suffix:colon
r_case
id|OPCODE_STW_L
suffix:colon
r_case
id|OPCODE_STW_L2
suffix:colon
id|align_mask
op_assign
l_int|3UL
suffix:semicolon
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
r_return
(paren
r_int
)paren
(paren
id|regs-&gt;ior
op_amp
id|align_mask
)paren
suffix:semicolon
)brace
eof
