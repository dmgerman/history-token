multiline_comment|/*&n; * linux/arch/sh/kernel/led_microdev.c&n; *&n; * Copyright (C) 2002 Stuart Menefy &lt;stuart.menefy@st.com&gt;&n; * Copyright (C) 2003 Richard Curnow (Richard.Curnow@superh.com)&n; *&n; * May be copied or modified under the terms of the GNU General Public&n; * License.  See linux/COPYING for more information.&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/io.h&gt;
DECL|macro|LED_REGISTER
mdefine_line|#define LED_REGISTER 0xa6104d20
DECL|function|mach_led_d9
r_static
r_void
id|mach_led_d9
c_func
(paren
r_int
id|value
)paren
(brace
r_int
r_int
id|reg
suffix:semicolon
id|reg
op_assign
id|ctrl_inl
c_func
(paren
id|LED_REGISTER
)paren
suffix:semicolon
id|reg
op_and_assign
op_complement
l_int|1
suffix:semicolon
id|reg
op_or_assign
(paren
id|value
op_amp
l_int|1
)paren
suffix:semicolon
id|ctrl_outl
c_func
(paren
id|reg
comma
id|LED_REGISTER
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|mach_led_d10
r_static
r_void
id|mach_led_d10
c_func
(paren
r_int
id|value
)paren
(brace
r_int
r_int
id|reg
suffix:semicolon
id|reg
op_assign
id|ctrl_inl
c_func
(paren
id|LED_REGISTER
)paren
suffix:semicolon
id|reg
op_and_assign
op_complement
l_int|2
suffix:semicolon
id|reg
op_or_assign
(paren
(paren
id|value
op_amp
l_int|1
)paren
op_lshift
l_int|1
)paren
suffix:semicolon
id|ctrl_outl
c_func
(paren
id|reg
comma
id|LED_REGISTER
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_HEARTBEAT
macro_line|#include &lt;linux/sched.h&gt;
DECL|variable|banner_table
r_static
r_int
r_char
id|banner_table
(braket
)braket
op_assign
(brace
l_int|0x11
comma
l_int|0x01
comma
l_int|0x11
comma
l_int|0x01
comma
l_int|0x11
comma
l_int|0x03
comma
l_int|0x11
comma
l_int|0x01
comma
l_int|0x11
comma
l_int|0x01
comma
l_int|0x13
comma
l_int|0x03
comma
l_int|0x11
comma
l_int|0x01
comma
l_int|0x13
comma
l_int|0x01
comma
l_int|0x13
comma
l_int|0x01
comma
l_int|0x11
comma
l_int|0x03
comma
l_int|0x11
comma
l_int|0x03
comma
l_int|0x11
comma
l_int|0x01
comma
l_int|0x13
comma
l_int|0x01
comma
l_int|0x11
comma
l_int|0x03
comma
l_int|0x11
comma
l_int|0x01
comma
l_int|0x11
comma
l_int|0x01
comma
l_int|0x11
comma
l_int|0x01
comma
l_int|0x11
comma
l_int|0x07
comma
l_int|0x13
comma
l_int|0x01
comma
l_int|0x13
comma
l_int|0x03
comma
l_int|0x11
comma
l_int|0x01
comma
l_int|0x11
comma
l_int|0x03
comma
l_int|0x13
comma
l_int|0x01
comma
l_int|0x11
comma
l_int|0x01
comma
l_int|0x13
comma
l_int|0x01
comma
l_int|0x11
comma
l_int|0x03
comma
l_int|0x11
comma
l_int|0x01
comma
l_int|0x13
comma
l_int|0x01
comma
l_int|0x11
comma
l_int|0x03
comma
l_int|0x13
comma
l_int|0x01
comma
l_int|0x13
comma
l_int|0x01
comma
l_int|0x13
comma
l_int|0x03
comma
l_int|0x13
comma
l_int|0x01
comma
l_int|0x11
comma
l_int|0x01
comma
l_int|0x11
comma
l_int|0x03
comma
l_int|0x11
comma
l_int|0x03
comma
l_int|0x11
comma
l_int|0x01
comma
l_int|0x11
comma
l_int|0x01
comma
l_int|0x11
comma
l_int|0x01
comma
l_int|0x13
comma
l_int|0x07
comma
l_int|0xff
)brace
suffix:semicolon
DECL|function|banner
r_static
r_void
id|banner
c_func
(paren
r_void
)paren
(brace
r_static
r_int
id|pos
op_assign
l_int|0
suffix:semicolon
r_static
r_int
id|count
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|count
)paren
(brace
id|count
op_decrement
suffix:semicolon
)brace
r_else
(brace
r_int
id|val
op_assign
id|banner_table
(braket
id|pos
)braket
suffix:semicolon
r_if
c_cond
(paren
id|val
op_eq
l_int|0xff
)paren
(brace
id|pos
op_assign
l_int|0
suffix:semicolon
id|val
op_assign
id|banner_table
(braket
id|pos
)braket
suffix:semicolon
)brace
id|pos
op_increment
suffix:semicolon
id|mach_led_d10
c_func
(paren
(paren
id|val
op_rshift
l_int|4
)paren
op_amp
l_int|1
)paren
suffix:semicolon
id|count
op_assign
l_int|10
op_star
(paren
id|val
op_amp
l_int|0xf
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* From heartbeat_harp in the stboards directory */
multiline_comment|/* acts like an actual heart beat -- ie thump-thump-pause... */
DECL|function|microdev_heartbeat
r_void
id|microdev_heartbeat
c_func
(paren
r_void
)paren
(brace
r_static
r_int
id|cnt
op_assign
l_int|0
comma
id|period
op_assign
l_int|0
comma
id|dist
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|cnt
op_eq
l_int|0
op_logical_or
id|cnt
op_eq
id|dist
)paren
id|mach_led_d9
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|cnt
op_eq
l_int|7
op_logical_or
id|cnt
op_eq
id|dist
op_plus
l_int|7
)paren
id|mach_led_d9
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_increment
id|cnt
OG
id|period
)paren
(brace
id|cnt
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* The hyperbolic function below modifies the heartbeat period&n;&t;&t; * length in dependency of the current (5min) load. It goes&n;&t;&t; * through the points f(0)=126, f(1)=86, f(5)=51,&n;&t;&t; * f(inf)-&gt;30. */
id|period
op_assign
(paren
(paren
l_int|672
op_lshift
id|FSHIFT
)paren
op_div
(paren
l_int|5
op_star
id|avenrun
(braket
l_int|0
)braket
op_plus
(paren
l_int|7
op_lshift
id|FSHIFT
)paren
)paren
)paren
op_plus
l_int|30
suffix:semicolon
id|dist
op_assign
id|period
op_div
l_int|4
suffix:semicolon
)brace
id|banner
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
