multiline_comment|/*&n; * linux/arch/sh/kernel/led_mpc1211.c&n; *&n; * Copyright (C) 2001  Saito.K &amp; Jeanne&n; *&n; * This file contains Interface MPC-1211 specific LED code.&n; */
macro_line|#include &lt;linux/config.h&gt;
DECL|function|mach_led
r_static
r_void
id|mach_led
c_func
(paren
r_int
id|position
comma
r_int
id|value
)paren
(brace
r_volatile
r_int
r_char
op_star
id|p
op_assign
(paren
r_volatile
r_int
r_char
op_star
)paren
l_int|0xa2000000
suffix:semicolon
r_if
c_cond
(paren
id|value
)paren
(brace
op_star
id|p
op_or_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
op_star
id|p
op_and_assign
op_complement
l_int|1
suffix:semicolon
)brace
)brace
macro_line|#ifdef CONFIG_HEARTBEAT
macro_line|#include &lt;linux/sched.h&gt;
multiline_comment|/* Cycle the LED&squot;s in the clasic Knightrider/Sun pattern */
DECL|function|heartbeat_mpc1211
r_void
id|heartbeat_mpc1211
c_func
(paren
r_void
)paren
(brace
r_static
r_int
r_int
id|cnt
op_assign
l_int|0
comma
id|period
op_assign
l_int|0
suffix:semicolon
r_volatile
r_int
r_char
op_star
id|p
op_assign
(paren
r_volatile
r_int
r_char
op_star
)paren
l_int|0xa2000000
suffix:semicolon
r_static
r_int
id|bit
op_assign
l_int|0
comma
id|up
op_assign
l_int|1
suffix:semicolon
id|cnt
op_add_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|cnt
OL
id|period
)paren
(brace
r_return
suffix:semicolon
)brace
id|cnt
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Go through the points (roughly!):&n;&t; * f(0)=10, f(1)=16, f(2)=20, f(5)=35,f(inf)-&gt;110&n;&t; */
id|period
op_assign
l_int|110
op_minus
(paren
(paren
l_int|300
op_lshift
id|FSHIFT
)paren
op_div
(paren
(paren
id|avenrun
(braket
l_int|0
)braket
op_div
l_int|5
)paren
op_plus
(paren
l_int|3
op_lshift
id|FSHIFT
)paren
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|up
)paren
(brace
r_if
c_cond
(paren
id|bit
op_eq
l_int|7
)paren
(brace
id|bit
op_decrement
suffix:semicolon
id|up
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|bit
op_increment
suffix:semicolon
)brace
)brace
r_else
(brace
r_if
c_cond
(paren
id|bit
op_eq
l_int|0
)paren
(brace
id|bit
op_increment
suffix:semicolon
id|up
op_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|bit
op_decrement
suffix:semicolon
)brace
)brace
op_star
id|p
op_assign
l_int|1
op_lshift
id|bit
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_HEARTBEAT */
eof
