multiline_comment|/* &n;&t;frpw.c&t;(c) 1996-8  Grant R. Guenther &lt;grant@torque.net&gt;&n;&t;&t;            Under the terms of the GNU General Public License&n;&n;&t;frpw.c is a low-level protocol driver for the Freecom &quot;Power&quot;&n;&t;parallel port IDE adapter.&n;&t;&n;&t;Some applications of this adapter may require a &quot;printer&quot; reset&n;&t;prior to loading the driver.  This can be done by loading and&n;&t;unloading the &quot;lp&quot; driver, or it can be done by this driver&n;&t;if you define FRPW_HARD_RESET.  The latter is not recommended&n;&t;as it may upset devices on other ports.&n;&n;*/
multiline_comment|/* Changes:&n;&n;        1.01    GRG 1998.05.06 init_proto, release_proto&n;&t;&t;&t;       fix chip detect&n;&t;&t;&t;       added EPP-16 and EPP-32&n;&t;1.02    GRG 1998.09.23 added hard reset to initialisation process&n;&t;1.03    GRG 1998.12.14 made hard reset conditional&n;&n;*/
DECL|macro|FRPW_VERSION
mdefine_line|#define&t;FRPW_VERSION&t;&quot;1.03&quot; 
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &quot;paride.h&quot;
DECL|macro|cec4
mdefine_line|#define cec4&t;&t;w2(0xc);w2(0xe);w2(0xe);w2(0xc);w2(4);w2(4);w2(4);
DECL|macro|j44
mdefine_line|#define j44(l,h)&t;(((l&gt;&gt;4)&amp;0x0f)|(h&amp;0xf0))
multiline_comment|/* cont = 0 - access the IDE register file &n;   cont = 1 - access the IDE command set &n;*/
DECL|variable|cont_map
r_static
r_int
id|cont_map
(braket
l_int|2
)braket
op_assign
(brace
l_int|0x08
comma
l_int|0x10
)brace
suffix:semicolon
DECL|function|frpw_read_regr
r_static
r_int
id|frpw_read_regr
c_func
(paren
id|PIA
op_star
id|pi
comma
r_int
id|cont
comma
r_int
id|regr
)paren
(brace
r_int
id|h
comma
id|l
comma
id|r
suffix:semicolon
id|r
op_assign
id|regr
op_plus
id|cont_map
(braket
id|cont
)braket
suffix:semicolon
id|w2
c_func
(paren
l_int|4
)paren
suffix:semicolon
id|w0
c_func
(paren
id|r
)paren
suffix:semicolon
id|cec4
suffix:semicolon
id|w2
c_func
(paren
l_int|6
)paren
suffix:semicolon
id|l
op_assign
id|r1
c_func
(paren
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|4
)paren
suffix:semicolon
id|h
op_assign
id|r1
c_func
(paren
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|4
)paren
suffix:semicolon
r_return
id|j44
c_func
(paren
id|l
comma
id|h
)paren
suffix:semicolon
)brace
DECL|function|frpw_write_regr
r_static
r_void
id|frpw_write_regr
c_func
(paren
id|PIA
op_star
id|pi
comma
r_int
id|cont
comma
r_int
id|regr
comma
r_int
id|val
)paren
(brace
r_int
id|r
suffix:semicolon
id|r
op_assign
id|regr
op_plus
id|cont_map
(braket
id|cont
)braket
suffix:semicolon
id|w2
c_func
(paren
l_int|4
)paren
suffix:semicolon
id|w0
c_func
(paren
id|r
)paren
suffix:semicolon
id|cec4
suffix:semicolon
id|w0
c_func
(paren
id|val
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|5
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|7
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|5
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|4
)paren
suffix:semicolon
)brace
DECL|function|frpw_read_block_int
r_static
r_void
id|frpw_read_block_int
c_func
(paren
id|PIA
op_star
id|pi
comma
r_char
op_star
id|buf
comma
r_int
id|count
comma
r_int
id|regr
)paren
(brace
r_int
id|h
comma
id|l
comma
id|k
comma
id|ph
suffix:semicolon
r_switch
c_cond
(paren
id|pi-&gt;mode
)paren
(brace
r_case
l_int|0
suffix:colon
id|w2
c_func
(paren
l_int|4
)paren
suffix:semicolon
id|w0
c_func
(paren
id|regr
)paren
suffix:semicolon
id|cec4
suffix:semicolon
r_for
c_loop
(paren
id|k
op_assign
l_int|0
suffix:semicolon
id|k
OL
id|count
suffix:semicolon
id|k
op_increment
)paren
(brace
id|w2
c_func
(paren
l_int|6
)paren
suffix:semicolon
id|l
op_assign
id|r1
c_func
(paren
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|4
)paren
suffix:semicolon
id|h
op_assign
id|r1
c_func
(paren
)paren
suffix:semicolon
id|buf
(braket
id|k
)braket
op_assign
id|j44
c_func
(paren
id|l
comma
id|h
)paren
suffix:semicolon
)brace
id|w2
c_func
(paren
l_int|4
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|ph
op_assign
l_int|2
suffix:semicolon
id|w2
c_func
(paren
l_int|4
)paren
suffix:semicolon
id|w0
c_func
(paren
id|regr
op_plus
l_int|0xc0
)paren
suffix:semicolon
id|cec4
suffix:semicolon
id|w0
c_func
(paren
l_int|0xff
)paren
suffix:semicolon
r_for
c_loop
(paren
id|k
op_assign
l_int|0
suffix:semicolon
id|k
OL
id|count
suffix:semicolon
id|k
op_increment
)paren
(brace
id|w2
c_func
(paren
l_int|0xa4
op_plus
id|ph
)paren
suffix:semicolon
id|buf
(braket
id|k
)braket
op_assign
id|r0
c_func
(paren
)paren
suffix:semicolon
id|ph
op_assign
l_int|2
op_minus
id|ph
suffix:semicolon
)brace
id|w2
c_func
(paren
l_int|0xac
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|0xa4
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|4
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|w2
c_func
(paren
l_int|4
)paren
suffix:semicolon
id|w0
c_func
(paren
id|regr
op_plus
l_int|0x80
)paren
suffix:semicolon
id|cec4
suffix:semicolon
r_for
c_loop
(paren
id|k
op_assign
l_int|0
suffix:semicolon
id|k
OL
id|count
suffix:semicolon
id|k
op_increment
)paren
id|buf
(braket
id|k
)braket
op_assign
id|r4
c_func
(paren
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|0xac
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|0xa4
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|4
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|w2
c_func
(paren
l_int|4
)paren
suffix:semicolon
id|w0
c_func
(paren
id|regr
op_plus
l_int|0x80
)paren
suffix:semicolon
id|cec4
suffix:semicolon
r_for
c_loop
(paren
id|k
op_assign
l_int|0
suffix:semicolon
id|k
OL
id|count
op_minus
l_int|2
suffix:semicolon
id|k
op_increment
)paren
id|buf
(braket
id|k
)braket
op_assign
id|r4
c_func
(paren
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|0xac
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|0xa4
)paren
suffix:semicolon
id|buf
(braket
id|count
op_minus
l_int|2
)braket
op_assign
id|r4
c_func
(paren
)paren
suffix:semicolon
id|buf
(braket
id|count
op_minus
l_int|1
)braket
op_assign
id|r4
c_func
(paren
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|4
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
id|w2
c_func
(paren
l_int|4
)paren
suffix:semicolon
id|w0
c_func
(paren
id|regr
op_plus
l_int|0x80
)paren
suffix:semicolon
id|cec4
suffix:semicolon
r_for
c_loop
(paren
id|k
op_assign
l_int|0
suffix:semicolon
id|k
OL
(paren
id|count
op_div
l_int|2
)paren
op_minus
l_int|1
suffix:semicolon
id|k
op_increment
)paren
(paren
(paren
id|u16
op_star
)paren
id|buf
)paren
(braket
id|k
)braket
op_assign
id|r4w
c_func
(paren
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|0xac
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|0xa4
)paren
suffix:semicolon
id|buf
(braket
id|count
op_minus
l_int|2
)braket
op_assign
id|r4
c_func
(paren
)paren
suffix:semicolon
id|buf
(braket
id|count
op_minus
l_int|1
)braket
op_assign
id|r4
c_func
(paren
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|4
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|5
suffix:colon
id|w2
c_func
(paren
l_int|4
)paren
suffix:semicolon
id|w0
c_func
(paren
id|regr
op_plus
l_int|0x80
)paren
suffix:semicolon
id|cec4
suffix:semicolon
r_for
c_loop
(paren
id|k
op_assign
l_int|0
suffix:semicolon
id|k
OL
(paren
id|count
op_div
l_int|4
)paren
op_minus
l_int|1
suffix:semicolon
id|k
op_increment
)paren
(paren
(paren
id|u32
op_star
)paren
id|buf
)paren
(braket
id|k
)braket
op_assign
id|r4l
c_func
(paren
)paren
suffix:semicolon
id|buf
(braket
id|count
op_minus
l_int|4
)braket
op_assign
id|r4
c_func
(paren
)paren
suffix:semicolon
id|buf
(braket
id|count
op_minus
l_int|3
)braket
op_assign
id|r4
c_func
(paren
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|0xac
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|0xa4
)paren
suffix:semicolon
id|buf
(braket
id|count
op_minus
l_int|2
)braket
op_assign
id|r4
c_func
(paren
)paren
suffix:semicolon
id|buf
(braket
id|count
op_minus
l_int|1
)braket
op_assign
id|r4
c_func
(paren
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|4
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
DECL|function|frpw_read_block
r_static
r_void
id|frpw_read_block
c_func
(paren
id|PIA
op_star
id|pi
comma
r_char
op_star
id|buf
comma
r_int
id|count
)paren
(brace
id|frpw_read_block_int
c_func
(paren
id|pi
comma
id|buf
comma
id|count
comma
l_int|0x08
)paren
suffix:semicolon
)brace
DECL|function|frpw_write_block
r_static
r_void
id|frpw_write_block
c_func
(paren
id|PIA
op_star
id|pi
comma
r_char
op_star
id|buf
comma
r_int
id|count
)paren
(brace
r_int
id|k
suffix:semicolon
r_switch
c_cond
(paren
id|pi-&gt;mode
)paren
(brace
r_case
l_int|0
suffix:colon
r_case
l_int|1
suffix:colon
r_case
l_int|2
suffix:colon
id|w2
c_func
(paren
l_int|4
)paren
suffix:semicolon
id|w0
c_func
(paren
l_int|8
)paren
suffix:semicolon
id|cec4
suffix:semicolon
id|w2
c_func
(paren
l_int|5
)paren
suffix:semicolon
r_for
c_loop
(paren
id|k
op_assign
l_int|0
suffix:semicolon
id|k
OL
id|count
suffix:semicolon
id|k
op_increment
)paren
(brace
id|w0
c_func
(paren
id|buf
(braket
id|k
)braket
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|7
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|5
)paren
suffix:semicolon
)brace
id|w2
c_func
(paren
l_int|4
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|w2
c_func
(paren
l_int|4
)paren
suffix:semicolon
id|w0
c_func
(paren
l_int|0xc8
)paren
suffix:semicolon
id|cec4
suffix:semicolon
id|w2
c_func
(paren
l_int|5
)paren
suffix:semicolon
r_for
c_loop
(paren
id|k
op_assign
l_int|0
suffix:semicolon
id|k
OL
id|count
suffix:semicolon
id|k
op_increment
)paren
id|w4
c_func
(paren
id|buf
(braket
id|k
)braket
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|4
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
id|w2
c_func
(paren
l_int|4
)paren
suffix:semicolon
id|w0
c_func
(paren
l_int|0xc8
)paren
suffix:semicolon
id|cec4
suffix:semicolon
id|w2
c_func
(paren
l_int|5
)paren
suffix:semicolon
r_for
c_loop
(paren
id|k
op_assign
l_int|0
suffix:semicolon
id|k
OL
id|count
op_div
l_int|2
suffix:semicolon
id|k
op_increment
)paren
id|w4w
c_func
(paren
(paren
(paren
id|u16
op_star
)paren
id|buf
)paren
(braket
id|k
)braket
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|4
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|5
suffix:colon
id|w2
c_func
(paren
l_int|4
)paren
suffix:semicolon
id|w0
c_func
(paren
l_int|0xc8
)paren
suffix:semicolon
id|cec4
suffix:semicolon
id|w2
c_func
(paren
l_int|5
)paren
suffix:semicolon
r_for
c_loop
(paren
id|k
op_assign
l_int|0
suffix:semicolon
id|k
OL
id|count
op_div
l_int|4
suffix:semicolon
id|k
op_increment
)paren
id|w4l
c_func
(paren
(paren
(paren
id|u32
op_star
)paren
id|buf
)paren
(braket
id|k
)braket
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|4
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
DECL|function|frpw_connect
r_static
r_void
id|frpw_connect
(paren
id|PIA
op_star
id|pi
)paren
(brace
id|pi-&gt;saved_r0
op_assign
id|r0
c_func
(paren
)paren
suffix:semicolon
id|pi-&gt;saved_r2
op_assign
id|r2
c_func
(paren
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|4
)paren
suffix:semicolon
)brace
DECL|function|frpw_disconnect
r_static
r_void
id|frpw_disconnect
(paren
id|PIA
op_star
id|pi
)paren
(brace
id|w2
c_func
(paren
l_int|4
)paren
suffix:semicolon
id|w0
c_func
(paren
l_int|0x20
)paren
suffix:semicolon
id|cec4
suffix:semicolon
id|w0
c_func
(paren
id|pi-&gt;saved_r0
)paren
suffix:semicolon
id|w2
c_func
(paren
id|pi-&gt;saved_r2
)paren
suffix:semicolon
)brace
multiline_comment|/* Stub logic to see if PNP string is available - used to distinguish&n;   between the Xilinx and ASIC implementations of the Freecom adapter.&n;*/
DECL|function|frpw_test_pnp
r_static
r_int
id|frpw_test_pnp
(paren
id|PIA
op_star
id|pi
)paren
multiline_comment|/*  returns chip_type:   0 = Xilinx, 1 = ASIC   */
(brace
r_int
id|olddelay
comma
id|a
comma
id|b
suffix:semicolon
macro_line|#ifdef FRPW_HARD_RESET
id|w0
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|8
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|50
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|0xc
)paren
suffix:semicolon
multiline_comment|/* parallel bus reset */
id|mdelay
c_func
(paren
l_int|1500
)paren
suffix:semicolon
macro_line|#endif
id|olddelay
op_assign
id|pi-&gt;delay
suffix:semicolon
id|pi-&gt;delay
op_assign
l_int|10
suffix:semicolon
id|pi-&gt;saved_r0
op_assign
id|r0
c_func
(paren
)paren
suffix:semicolon
id|pi-&gt;saved_r2
op_assign
id|r2
c_func
(paren
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|4
)paren
suffix:semicolon
id|w0
c_func
(paren
l_int|4
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|6
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|7
)paren
suffix:semicolon
id|a
op_assign
id|r1
c_func
(paren
)paren
op_amp
l_int|0xff
suffix:semicolon
id|w2
c_func
(paren
l_int|4
)paren
suffix:semicolon
id|b
op_assign
id|r1
c_func
(paren
)paren
op_amp
l_int|0xff
suffix:semicolon
id|w2
c_func
(paren
l_int|0xc
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|0xe
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|4
)paren
suffix:semicolon
id|pi-&gt;delay
op_assign
id|olddelay
suffix:semicolon
id|w0
c_func
(paren
id|pi-&gt;saved_r0
)paren
suffix:semicolon
id|w2
c_func
(paren
id|pi-&gt;saved_r2
)paren
suffix:semicolon
r_return
(paren
(paren
op_complement
id|a
op_amp
l_int|0x40
)paren
op_logical_and
(paren
id|b
op_amp
l_int|0x40
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* We use the pi-&gt;private to remember the result of the PNP test.&n;   To make this work, private = port*2 + chip.  Yes, I know it&squot;s&n;   a hack :-(&n;*/
DECL|function|frpw_test_proto
r_static
r_int
id|frpw_test_proto
c_func
(paren
id|PIA
op_star
id|pi
comma
r_char
op_star
id|scratch
comma
r_int
id|verbose
)paren
(brace
r_int
id|j
comma
id|k
comma
id|r
suffix:semicolon
r_int
id|e
(braket
l_int|2
)braket
op_assign
(brace
l_int|0
comma
l_int|0
)brace
suffix:semicolon
r_if
c_cond
(paren
(paren
id|pi
op_member_access_from_pointer
r_private
op_rshift
l_int|1
)paren
op_ne
id|pi-&gt;port
)paren
id|pi
op_member_access_from_pointer
r_private
op_assign
id|frpw_test_pnp
c_func
(paren
id|pi
)paren
op_plus
l_int|2
op_star
id|pi-&gt;port
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
id|pi
op_member_access_from_pointer
r_private
op_mod
l_int|2
)paren
op_eq
l_int|0
)paren
op_logical_and
(paren
id|pi-&gt;mode
OG
l_int|2
)paren
)paren
(brace
r_if
c_cond
(paren
id|verbose
)paren
id|printk
c_func
(paren
l_string|&quot;%s: frpw: Xilinx does not support mode %d&bslash;n&quot;
comma
id|pi-&gt;device
comma
id|pi-&gt;mode
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
(paren
id|pi
op_member_access_from_pointer
r_private
op_mod
l_int|2
)paren
op_eq
l_int|1
)paren
op_logical_and
(paren
id|pi-&gt;mode
op_eq
l_int|2
)paren
)paren
(brace
r_if
c_cond
(paren
id|verbose
)paren
id|printk
c_func
(paren
l_string|&quot;%s: frpw: ASIC does not support mode 2&bslash;n&quot;
comma
id|pi-&gt;device
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|frpw_connect
c_func
(paren
id|pi
)paren
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
l_int|2
suffix:semicolon
id|j
op_increment
)paren
(brace
id|frpw_write_regr
c_func
(paren
id|pi
comma
l_int|0
comma
l_int|6
comma
l_int|0xa0
op_plus
id|j
op_star
l_int|0x10
)paren
suffix:semicolon
r_for
c_loop
(paren
id|k
op_assign
l_int|0
suffix:semicolon
id|k
OL
l_int|256
suffix:semicolon
id|k
op_increment
)paren
(brace
id|frpw_write_regr
c_func
(paren
id|pi
comma
l_int|0
comma
l_int|2
comma
id|k
op_xor
l_int|0xaa
)paren
suffix:semicolon
id|frpw_write_regr
c_func
(paren
id|pi
comma
l_int|0
comma
l_int|3
comma
id|k
op_xor
l_int|0x55
)paren
suffix:semicolon
r_if
c_cond
(paren
id|frpw_read_regr
c_func
(paren
id|pi
comma
l_int|0
comma
l_int|2
)paren
op_ne
(paren
id|k
op_xor
l_int|0xaa
)paren
)paren
id|e
(braket
id|j
)braket
op_increment
suffix:semicolon
)brace
)brace
id|frpw_disconnect
c_func
(paren
id|pi
)paren
suffix:semicolon
id|frpw_connect
c_func
(paren
id|pi
)paren
suffix:semicolon
id|frpw_read_block_int
c_func
(paren
id|pi
comma
id|scratch
comma
l_int|512
comma
l_int|0x10
)paren
suffix:semicolon
id|r
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|k
op_assign
l_int|0
suffix:semicolon
id|k
OL
l_int|128
suffix:semicolon
id|k
op_increment
)paren
r_if
c_cond
(paren
id|scratch
(braket
id|k
)braket
op_ne
id|k
)paren
id|r
op_increment
suffix:semicolon
id|frpw_disconnect
c_func
(paren
id|pi
)paren
suffix:semicolon
r_if
c_cond
(paren
id|verbose
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: frpw: port 0x%x, chip %d, mode %d, test=(%d,%d,%d)&bslash;n&quot;
comma
id|pi-&gt;device
comma
id|pi-&gt;port
comma
(paren
id|pi
op_member_access_from_pointer
r_private
op_mod
l_int|2
)paren
comma
id|pi-&gt;mode
comma
id|e
(braket
l_int|0
)braket
comma
id|e
(braket
l_int|1
)braket
comma
id|r
)paren
suffix:semicolon
)brace
r_return
(paren
id|r
op_logical_or
(paren
id|e
(braket
l_int|0
)braket
op_logical_and
id|e
(braket
l_int|1
)braket
)paren
)paren
suffix:semicolon
)brace
DECL|function|frpw_log_adapter
r_static
r_void
id|frpw_log_adapter
c_func
(paren
id|PIA
op_star
id|pi
comma
r_char
op_star
id|scratch
comma
r_int
id|verbose
)paren
(brace
r_char
op_star
id|mode_string
(braket
l_int|6
)braket
op_assign
(brace
l_string|&quot;4-bit&quot;
comma
l_string|&quot;8-bit&quot;
comma
l_string|&quot;EPP&quot;
comma
l_string|&quot;EPP-8&quot;
comma
l_string|&quot;EPP-16&quot;
comma
l_string|&quot;EPP-32&quot;
)brace
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s: frpw %s, Freecom (%s) adapter at 0x%x, &quot;
comma
id|pi-&gt;device
comma
id|FRPW_VERSION
comma
(paren
(paren
id|pi
op_member_access_from_pointer
r_private
op_mod
l_int|2
)paren
op_eq
l_int|0
)paren
ques
c_cond
l_string|&quot;Xilinx&quot;
suffix:colon
l_string|&quot;ASIC&quot;
comma
id|pi-&gt;port
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;mode %d (%s), delay %d&bslash;n&quot;
comma
id|pi-&gt;mode
comma
id|mode_string
(braket
id|pi-&gt;mode
)braket
comma
id|pi-&gt;delay
)paren
suffix:semicolon
)brace
DECL|function|frpw_init_proto
r_static
r_void
id|frpw_init_proto
c_func
(paren
id|PIA
op_star
id|pi
)paren
(brace
id|MOD_INC_USE_COUNT
suffix:semicolon
id|pi
op_member_access_from_pointer
r_private
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|frpw_release_proto
r_static
r_void
id|frpw_release_proto
c_func
(paren
id|PIA
op_star
id|pi
)paren
(brace
id|MOD_DEC_USE_COUNT
suffix:semicolon
)brace
DECL|variable|frpw
r_struct
id|pi_protocol
id|frpw
op_assign
(brace
l_string|&quot;frpw&quot;
comma
l_int|0
comma
l_int|6
comma
l_int|2
comma
l_int|2
comma
l_int|1
comma
id|frpw_write_regr
comma
id|frpw_read_regr
comma
id|frpw_write_block
comma
id|frpw_read_block
comma
id|frpw_connect
comma
id|frpw_disconnect
comma
l_int|0
comma
l_int|0
comma
id|frpw_test_proto
comma
id|frpw_log_adapter
comma
id|frpw_init_proto
comma
id|frpw_release_proto
)brace
suffix:semicolon
macro_line|#ifdef MODULE
DECL|function|init_module
r_int
id|init_module
c_func
(paren
r_void
)paren
(brace
r_return
id|pi_register
c_func
(paren
op_amp
id|frpw
)paren
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|cleanup_module
r_void
id|cleanup_module
c_func
(paren
r_void
)paren
(brace
id|pi_unregister
c_func
(paren
op_amp
id|frpw
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* end of frpw.c */
eof
