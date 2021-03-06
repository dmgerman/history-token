multiline_comment|/* $Id: p1275.c,v 1.22 2001/10/18 09:40:00 davem Exp $&n; * p1275.c: Sun IEEE 1275 PROM low level interface routines&n; *&n; * Copyright (C) 1996,1997 Jakub Jelinek (jj@sunsite.mff.cuni.cz)&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;asm/openprom.h&gt;
macro_line|#include &lt;asm/oplib.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/spitfire.h&gt;
macro_line|#include &lt;asm/pstate.h&gt;
r_struct
(brace
DECL|member|prom_callback
r_int
id|prom_callback
suffix:semicolon
multiline_comment|/* 0x00 */
DECL|member|prom_cif_handler
r_void
(paren
op_star
id|prom_cif_handler
)paren
(paren
r_int
op_star
)paren
suffix:semicolon
multiline_comment|/* 0x08 */
DECL|member|prom_cif_stack
r_int
r_int
id|prom_cif_stack
suffix:semicolon
multiline_comment|/* 0x10 */
DECL|member|prom_args
r_int
r_int
id|prom_args
(braket
l_int|23
)braket
suffix:semicolon
multiline_comment|/* 0x18 */
DECL|member|prom_buffer
r_char
id|prom_buffer
(braket
l_int|3000
)braket
suffix:semicolon
DECL|variable|p1275buf
)brace
id|p1275buf
suffix:semicolon
r_extern
r_void
id|prom_world
c_func
(paren
r_int
)paren
suffix:semicolon
r_extern
r_void
id|prom_cif_interface
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|prom_cif_callback
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|spitfire_get_primary_context
r_static
r_inline
r_int
r_int
id|spitfire_get_primary_context
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|ctx
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;ldxa&t;[%1] %2, %0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|ctx
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|PRIMARY_CONTEXT
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_DMMU
)paren
)paren
suffix:semicolon
r_return
id|ctx
suffix:semicolon
)brace
multiline_comment|/*&n; * This provides SMP safety on the p1275buf. prom_callback() drops this lock&n; * to allow recursuve acquisition.&n; */
DECL|variable|prom_entry_lock
id|DEFINE_SPINLOCK
c_func
(paren
id|prom_entry_lock
)paren
suffix:semicolon
DECL|function|p1275_cmd
r_int
id|p1275_cmd
(paren
r_char
op_star
id|service
comma
r_int
id|fmt
comma
dot
dot
dot
)paren
(brace
r_char
op_star
id|p
comma
op_star
id|q
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
id|nargs
comma
id|nrets
comma
id|i
suffix:semicolon
id|va_list
id|list
suffix:semicolon
r_int
id|attrs
comma
id|x
suffix:semicolon
id|p
op_assign
id|p1275buf.prom_buffer
suffix:semicolon
id|BUG_ON
c_func
(paren
(paren
id|spitfire_get_primary_context
c_func
(paren
)paren
op_amp
id|CTX_NR_MASK
)paren
op_ne
l_int|0
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|prom_entry_lock
comma
id|flags
)paren
suffix:semicolon
id|p1275buf.prom_args
(braket
l_int|0
)braket
op_assign
(paren
r_int
r_int
)paren
id|p
suffix:semicolon
multiline_comment|/* service */
id|strcpy
(paren
id|p
comma
id|service
)paren
suffix:semicolon
id|p
op_assign
(paren
r_char
op_star
)paren
(paren
(paren
(paren
r_int
)paren
(paren
id|strchr
(paren
id|p
comma
l_int|0
)paren
op_plus
l_int|8
)paren
)paren
op_amp
op_complement
l_int|7
)paren
suffix:semicolon
id|p1275buf.prom_args
(braket
l_int|1
)braket
op_assign
id|nargs
op_assign
(paren
id|fmt
op_amp
l_int|0x0f
)paren
suffix:semicolon
multiline_comment|/* nargs */
id|p1275buf.prom_args
(braket
l_int|2
)braket
op_assign
id|nrets
op_assign
(paren
(paren
id|fmt
op_amp
l_int|0xf0
)paren
op_rshift
l_int|4
)paren
suffix:semicolon
multiline_comment|/* nrets */
id|attrs
op_assign
id|fmt
op_rshift
l_int|8
suffix:semicolon
id|va_start
c_func
(paren
id|list
comma
id|fmt
)paren
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
id|nargs
suffix:semicolon
id|i
op_increment
comma
id|attrs
op_rshift_assign
l_int|3
)paren
(brace
r_switch
c_cond
(paren
id|attrs
op_amp
l_int|0x7
)paren
(brace
r_case
id|P1275_ARG_NUMBER
suffix:colon
id|p1275buf.prom_args
(braket
id|i
op_plus
l_int|3
)braket
op_assign
(paren
r_int
)paren
id|va_arg
c_func
(paren
id|list
comma
r_int
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|P1275_ARG_IN_64B
suffix:colon
id|p1275buf.prom_args
(braket
id|i
op_plus
l_int|3
)braket
op_assign
id|va_arg
c_func
(paren
id|list
comma
r_int
r_int
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|P1275_ARG_IN_STRING
suffix:colon
id|strcpy
(paren
id|p
comma
id|va_arg
c_func
(paren
id|list
comma
r_char
op_star
)paren
)paren
suffix:semicolon
id|p1275buf.prom_args
(braket
id|i
op_plus
l_int|3
)braket
op_assign
(paren
r_int
r_int
)paren
id|p
suffix:semicolon
id|p
op_assign
(paren
r_char
op_star
)paren
(paren
(paren
(paren
r_int
)paren
(paren
id|strchr
(paren
id|p
comma
l_int|0
)paren
op_plus
l_int|8
)paren
)paren
op_amp
op_complement
l_int|7
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|P1275_ARG_OUT_BUF
suffix:colon
(paren
r_void
)paren
id|va_arg
c_func
(paren
id|list
comma
r_char
op_star
)paren
suffix:semicolon
id|p1275buf.prom_args
(braket
id|i
op_plus
l_int|3
)braket
op_assign
(paren
r_int
r_int
)paren
id|p
suffix:semicolon
id|x
op_assign
id|va_arg
c_func
(paren
id|list
comma
r_int
)paren
suffix:semicolon
id|i
op_increment
suffix:semicolon
id|attrs
op_rshift_assign
l_int|3
suffix:semicolon
id|p
op_assign
(paren
r_char
op_star
)paren
(paren
(paren
(paren
r_int
)paren
(paren
id|p
op_plus
(paren
r_int
)paren
id|x
op_plus
l_int|7
)paren
)paren
op_amp
op_complement
l_int|7
)paren
suffix:semicolon
id|p1275buf.prom_args
(braket
id|i
op_plus
l_int|3
)braket
op_assign
id|x
suffix:semicolon
r_break
suffix:semicolon
r_case
id|P1275_ARG_IN_BUF
suffix:colon
id|q
op_assign
id|va_arg
c_func
(paren
id|list
comma
r_char
op_star
)paren
suffix:semicolon
id|p1275buf.prom_args
(braket
id|i
op_plus
l_int|3
)braket
op_assign
(paren
r_int
r_int
)paren
id|p
suffix:semicolon
id|x
op_assign
id|va_arg
c_func
(paren
id|list
comma
r_int
)paren
suffix:semicolon
id|i
op_increment
suffix:semicolon
id|attrs
op_rshift_assign
l_int|3
suffix:semicolon
id|memcpy
(paren
id|p
comma
id|q
comma
(paren
r_int
)paren
id|x
)paren
suffix:semicolon
id|p
op_assign
(paren
r_char
op_star
)paren
(paren
(paren
(paren
r_int
)paren
(paren
id|p
op_plus
(paren
r_int
)paren
id|x
op_plus
l_int|7
)paren
)paren
op_amp
op_complement
l_int|7
)paren
suffix:semicolon
id|p1275buf.prom_args
(braket
id|i
op_plus
l_int|3
)braket
op_assign
id|x
suffix:semicolon
r_break
suffix:semicolon
r_case
id|P1275_ARG_OUT_32B
suffix:colon
(paren
r_void
)paren
id|va_arg
c_func
(paren
id|list
comma
r_char
op_star
)paren
suffix:semicolon
id|p1275buf.prom_args
(braket
id|i
op_plus
l_int|3
)braket
op_assign
(paren
r_int
r_int
)paren
id|p
suffix:semicolon
id|p
op_add_assign
l_int|32
suffix:semicolon
r_break
suffix:semicolon
r_case
id|P1275_ARG_IN_FUNCTION
suffix:colon
id|p1275buf.prom_args
(braket
id|i
op_plus
l_int|3
)braket
op_assign
(paren
r_int
r_int
)paren
id|prom_cif_callback
suffix:semicolon
id|p1275buf.prom_callback
op_assign
id|va_arg
c_func
(paren
id|list
comma
r_int
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|va_end
c_func
(paren
id|list
)paren
suffix:semicolon
id|prom_world
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|prom_cif_interface
c_func
(paren
)paren
suffix:semicolon
id|prom_world
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|attrs
op_assign
id|fmt
op_rshift
l_int|8
suffix:semicolon
id|va_start
c_func
(paren
id|list
comma
id|fmt
)paren
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
id|nargs
suffix:semicolon
id|i
op_increment
comma
id|attrs
op_rshift_assign
l_int|3
)paren
(brace
r_switch
c_cond
(paren
id|attrs
op_amp
l_int|0x7
)paren
(brace
r_case
id|P1275_ARG_NUMBER
suffix:colon
(paren
r_void
)paren
id|va_arg
c_func
(paren
id|list
comma
r_int
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|P1275_ARG_IN_STRING
suffix:colon
(paren
r_void
)paren
id|va_arg
c_func
(paren
id|list
comma
r_char
op_star
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|P1275_ARG_IN_FUNCTION
suffix:colon
(paren
r_void
)paren
id|va_arg
c_func
(paren
id|list
comma
r_int
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|P1275_ARG_IN_BUF
suffix:colon
(paren
r_void
)paren
id|va_arg
c_func
(paren
id|list
comma
r_char
op_star
)paren
suffix:semicolon
(paren
r_void
)paren
id|va_arg
c_func
(paren
id|list
comma
r_int
)paren
suffix:semicolon
id|i
op_increment
suffix:semicolon
id|attrs
op_rshift_assign
l_int|3
suffix:semicolon
r_break
suffix:semicolon
r_case
id|P1275_ARG_OUT_BUF
suffix:colon
id|p
op_assign
id|va_arg
c_func
(paren
id|list
comma
r_char
op_star
)paren
suffix:semicolon
id|x
op_assign
id|va_arg
c_func
(paren
id|list
comma
r_int
)paren
suffix:semicolon
id|memcpy
(paren
id|p
comma
(paren
r_char
op_star
)paren
(paren
id|p1275buf.prom_args
(braket
id|i
op_plus
l_int|3
)braket
)paren
comma
(paren
r_int
)paren
id|x
)paren
suffix:semicolon
id|i
op_increment
suffix:semicolon
id|attrs
op_rshift_assign
l_int|3
suffix:semicolon
r_break
suffix:semicolon
r_case
id|P1275_ARG_OUT_32B
suffix:colon
id|p
op_assign
id|va_arg
c_func
(paren
id|list
comma
r_char
op_star
)paren
suffix:semicolon
id|memcpy
(paren
id|p
comma
(paren
r_char
op_star
)paren
(paren
id|p1275buf.prom_args
(braket
id|i
op_plus
l_int|3
)braket
)paren
comma
l_int|32
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|va_end
c_func
(paren
id|list
)paren
suffix:semicolon
id|x
op_assign
id|p1275buf.prom_args
(braket
id|nargs
op_plus
l_int|3
)braket
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|prom_entry_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|x
suffix:semicolon
)brace
DECL|function|prom_cif_init
r_void
id|prom_cif_init
c_func
(paren
r_void
op_star
id|cif_handler
comma
r_void
op_star
id|cif_stack
)paren
(brace
id|p1275buf.prom_cif_handler
op_assign
(paren
r_void
(paren
op_star
)paren
(paren
r_int
op_star
)paren
)paren
id|cif_handler
suffix:semicolon
id|p1275buf.prom_cif_stack
op_assign
(paren
r_int
r_int
)paren
id|cif_stack
suffix:semicolon
)brace
eof
