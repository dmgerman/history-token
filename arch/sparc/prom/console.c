multiline_comment|/* $Id: console.c,v 1.25 2001/10/30 04:54:22 davem Exp $&n; * console.c: Routines that deal with sending and receiving IO&n; *            to/from the current console device using the PROM.&n; *&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; * Copyright (C) 1998 Pete Zaitcev &lt;zaitcev@yahoo.com&gt;&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;asm/openprom.h&gt;
macro_line|#include &lt;asm/sun4prom.h&gt;
macro_line|#include &lt;asm/oplib.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/string.h&gt;
r_extern
r_void
id|restore_current
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|variable|con_name_jmc
r_static
r_char
id|con_name_jmc
(braket
)braket
op_assign
l_string|&quot;/obio/su@&quot;
suffix:semicolon
multiline_comment|/* &quot;/obio/su@0,3002f8&quot;; */
DECL|macro|CON_SIZE_JMC
mdefine_line|#define CON_SIZE_JMC&t;(sizeof(con_name_jmc))
multiline_comment|/* Non blocking get character from console input device, returns -1&n; * if no input was taken.  This can be used for polling.&n; */
r_int
DECL|function|prom_nbgetchar
id|prom_nbgetchar
c_func
(paren
r_void
)paren
(brace
r_static
r_char
id|inc
suffix:semicolon
r_int
id|i
op_assign
op_minus
l_int|1
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|prom_lock
comma
id|flags
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|prom_vers
)paren
(brace
r_case
id|PROM_V0
suffix:colon
r_case
id|PROM_SUN4
suffix:colon
id|i
op_assign
(paren
op_star
(paren
id|romvec-&gt;pv_nbgetchar
)paren
)paren
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PROM_V2
suffix:colon
r_case
id|PROM_V3
suffix:colon
r_if
c_cond
(paren
(paren
op_star
(paren
id|romvec-&gt;pv_v2devops
)paren
dot
id|v2_dev_read
)paren
(paren
op_star
id|romvec-&gt;pv_v2bootargs.fd_stdin
comma
op_amp
id|inc
comma
l_int|0x1
)paren
op_eq
l_int|1
)paren
(brace
id|i
op_assign
id|inc
suffix:semicolon
)brace
r_else
(brace
id|i
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
id|i
op_assign
op_minus
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
suffix:semicolon
id|restore_current
c_func
(paren
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|prom_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|i
suffix:semicolon
multiline_comment|/* Ugh, we could spin forever on unsupported proms ;( */
)brace
multiline_comment|/* Non blocking put character to console device, returns -1 if&n; * unsuccessful.&n; */
r_int
DECL|function|prom_nbputchar
id|prom_nbputchar
c_func
(paren
r_char
id|c
)paren
(brace
r_static
r_char
id|outc
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
id|i
op_assign
op_minus
l_int|1
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|prom_lock
comma
id|flags
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|prom_vers
)paren
(brace
r_case
id|PROM_V0
suffix:colon
r_case
id|PROM_SUN4
suffix:colon
id|i
op_assign
(paren
op_star
(paren
id|romvec-&gt;pv_nbputchar
)paren
)paren
(paren
id|c
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PROM_V2
suffix:colon
r_case
id|PROM_V3
suffix:colon
id|outc
op_assign
id|c
suffix:semicolon
r_if
c_cond
(paren
(paren
op_star
(paren
id|romvec-&gt;pv_v2devops
)paren
dot
id|v2_dev_write
)paren
(paren
op_star
id|romvec-&gt;pv_v2bootargs.fd_stdout
comma
op_amp
id|outc
comma
l_int|0x1
)paren
op_eq
l_int|1
)paren
(brace
id|i
op_assign
l_int|0
suffix:semicolon
)brace
r_else
id|i
op_assign
op_minus
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|i
op_assign
op_minus
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
suffix:semicolon
id|restore_current
c_func
(paren
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|prom_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|i
suffix:semicolon
multiline_comment|/* Ugh, we could spin forever on unsupported proms ;( */
)brace
multiline_comment|/* Blocking version of get character routine above. */
r_char
DECL|function|prom_getchar
id|prom_getchar
c_func
(paren
r_void
)paren
(brace
r_int
id|character
suffix:semicolon
r_while
c_loop
(paren
(paren
id|character
op_assign
id|prom_nbgetchar
c_func
(paren
)paren
)paren
op_eq
op_minus
l_int|1
)paren
(brace
suffix:semicolon
)brace
r_return
(paren
r_char
)paren
id|character
suffix:semicolon
)brace
multiline_comment|/* Blocking version of put character routine above. */
r_void
DECL|function|prom_putchar
id|prom_putchar
c_func
(paren
r_char
id|c
)paren
(brace
r_while
c_loop
(paren
id|prom_nbputchar
c_func
(paren
id|c
)paren
op_eq
op_minus
l_int|1
)paren
(brace
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
multiline_comment|/* Query for input device type */
r_enum
id|prom_input_device
DECL|function|prom_query_input_device
id|prom_query_input_device
c_func
(paren
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
id|st_p
suffix:semicolon
r_char
id|propb
(braket
l_int|64
)braket
suffix:semicolon
r_char
op_star
id|p
suffix:semicolon
r_switch
c_cond
(paren
id|prom_vers
)paren
(brace
r_case
id|PROM_V0
suffix:colon
r_case
id|PROM_V2
suffix:colon
r_case
id|PROM_SUN4
suffix:colon
r_default
suffix:colon
(brace
)brace
r_switch
c_cond
(paren
op_star
id|romvec-&gt;pv_stdin
)paren
(brace
r_case
id|PROMDEV_KBD
suffix:colon
r_return
id|PROMDEV_IKBD
suffix:semicolon
r_case
id|PROMDEV_TTYA
suffix:colon
r_return
id|PROMDEV_ITTYA
suffix:semicolon
r_case
id|PROMDEV_TTYB
suffix:colon
r_return
id|PROMDEV_ITTYB
suffix:semicolon
r_default
suffix:colon
r_return
id|PROMDEV_I_UNK
suffix:semicolon
)brace
suffix:semicolon
r_case
id|PROM_V3
suffix:colon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|prom_lock
comma
id|flags
)paren
suffix:semicolon
id|st_p
op_assign
(paren
op_star
id|romvec-&gt;pv_v2devops.v2_inst2pkg
)paren
(paren
op_star
id|romvec-&gt;pv_v2bootargs.fd_stdin
)paren
suffix:semicolon
id|restore_current
c_func
(paren
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|prom_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|prom_node_has_property
c_func
(paren
id|st_p
comma
l_string|&quot;keyboard&quot;
)paren
)paren
(brace
r_return
id|PROMDEV_IKBD
suffix:semicolon
)brace
r_if
c_cond
(paren
id|prom_getproperty
c_func
(paren
id|st_p
comma
l_string|&quot;name&quot;
comma
id|propb
comma
r_sizeof
(paren
id|propb
)paren
)paren
op_ne
op_minus
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|propb
comma
l_string|&quot;keyboard&quot;
comma
r_sizeof
(paren
l_string|&quot;serial&quot;
)paren
)paren
op_eq
l_int|0
)paren
(brace
r_return
id|PROMDEV_IKBD
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|prom_getproperty
c_func
(paren
id|st_p
comma
l_string|&quot;device_type&quot;
comma
id|propb
comma
r_sizeof
(paren
id|propb
)paren
)paren
op_ne
op_minus
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|propb
comma
l_string|&quot;serial&quot;
comma
r_sizeof
(paren
l_string|&quot;serial&quot;
)paren
)paren
)paren
(brace
r_return
id|PROMDEV_I_UNK
suffix:semicolon
)brace
)brace
id|prom_getproperty
c_func
(paren
id|prom_root_node
comma
l_string|&quot;stdin-path&quot;
comma
id|propb
comma
r_sizeof
(paren
id|propb
)paren
)paren
suffix:semicolon
id|p
op_assign
id|propb
suffix:semicolon
r_while
c_loop
(paren
op_star
id|p
)paren
(brace
id|p
op_increment
suffix:semicolon
)brace
id|p
op_sub_assign
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|p
(braket
l_int|0
)braket
op_eq
l_char|&squot;:&squot;
)paren
(brace
r_if
c_cond
(paren
id|p
(braket
l_int|1
)braket
op_eq
l_char|&squot;a&squot;
)paren
(brace
r_return
id|PROMDEV_ITTYA
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|p
(braket
l_int|1
)braket
op_eq
l_char|&squot;b&squot;
)paren
(brace
r_return
id|PROMDEV_ITTYB
suffix:semicolon
)brace
)brace
r_return
id|PROMDEV_I_UNK
suffix:semicolon
)brace
)brace
multiline_comment|/* Query for output device type */
r_enum
id|prom_output_device
DECL|function|prom_query_output_device
id|prom_query_output_device
c_func
(paren
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
id|st_p
suffix:semicolon
r_char
id|propb
(braket
l_int|64
)braket
suffix:semicolon
r_char
op_star
id|p
suffix:semicolon
r_int
id|propl
suffix:semicolon
r_switch
c_cond
(paren
id|prom_vers
)paren
(brace
r_case
id|PROM_V0
suffix:colon
r_case
id|PROM_SUN4
suffix:colon
r_switch
c_cond
(paren
op_star
id|romvec-&gt;pv_stdin
)paren
(brace
r_case
id|PROMDEV_SCREEN
suffix:colon
r_return
id|PROMDEV_OSCREEN
suffix:semicolon
r_case
id|PROMDEV_TTYA
suffix:colon
r_return
id|PROMDEV_OTTYA
suffix:semicolon
r_case
id|PROMDEV_TTYB
suffix:colon
r_return
id|PROMDEV_OTTYB
suffix:semicolon
)brace
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PROM_V2
suffix:colon
r_case
id|PROM_V3
suffix:colon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|prom_lock
comma
id|flags
)paren
suffix:semicolon
id|st_p
op_assign
(paren
op_star
id|romvec-&gt;pv_v2devops.v2_inst2pkg
)paren
(paren
op_star
id|romvec-&gt;pv_v2bootargs.fd_stdout
)paren
suffix:semicolon
id|restore_current
c_func
(paren
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|prom_lock
comma
id|flags
)paren
suffix:semicolon
id|propl
op_assign
id|prom_getproperty
c_func
(paren
id|st_p
comma
l_string|&quot;device_type&quot;
comma
id|propb
comma
r_sizeof
(paren
id|propb
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|propl
op_ge
l_int|0
op_logical_and
id|propl
op_eq
r_sizeof
(paren
l_string|&quot;display&quot;
)paren
op_logical_and
id|strncmp
c_func
(paren
l_string|&quot;display&quot;
comma
id|propb
comma
r_sizeof
(paren
l_string|&quot;display&quot;
)paren
)paren
op_eq
l_int|0
)paren
(brace
r_return
id|PROMDEV_OSCREEN
suffix:semicolon
)brace
r_if
c_cond
(paren
id|prom_vers
op_eq
id|PROM_V3
)paren
(brace
r_if
c_cond
(paren
id|propl
op_ge
l_int|0
op_logical_and
id|strncmp
c_func
(paren
l_string|&quot;serial&quot;
comma
id|propb
comma
r_sizeof
(paren
l_string|&quot;serial&quot;
)paren
)paren
op_ne
l_int|0
)paren
(brace
r_return
id|PROMDEV_O_UNK
suffix:semicolon
)brace
id|prom_getproperty
c_func
(paren
id|prom_root_node
comma
l_string|&quot;stdout-path&quot;
comma
id|propb
comma
r_sizeof
(paren
id|propb
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|propb
comma
id|con_name_jmc
comma
id|CON_SIZE_JMC
)paren
op_eq
l_int|0
)paren
(brace
r_return
id|PROMDEV_OTTYA
suffix:semicolon
)brace
id|p
op_assign
id|propb
suffix:semicolon
r_while
c_loop
(paren
op_star
id|p
)paren
(brace
id|p
op_increment
suffix:semicolon
)brace
id|p
op_sub_assign
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|p
(braket
l_int|0
)braket
op_eq
l_char|&squot;:&squot;
)paren
(brace
r_if
c_cond
(paren
id|p
(braket
l_int|1
)braket
op_eq
l_char|&squot;a&squot;
)paren
(brace
r_return
id|PROMDEV_OTTYA
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|p
(braket
l_int|1
)braket
op_eq
l_char|&squot;b&squot;
)paren
(brace
r_return
id|PROMDEV_OTTYB
suffix:semicolon
)brace
)brace
)brace
r_else
(brace
r_switch
c_cond
(paren
op_star
id|romvec-&gt;pv_stdin
)paren
(brace
r_case
id|PROMDEV_TTYA
suffix:colon
r_return
id|PROMDEV_OTTYA
suffix:semicolon
r_case
id|PROMDEV_TTYB
suffix:colon
r_return
id|PROMDEV_OTTYB
suffix:semicolon
)brace
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
suffix:semicolon
)brace
suffix:semicolon
r_return
id|PROMDEV_O_UNK
suffix:semicolon
)brace
eof
