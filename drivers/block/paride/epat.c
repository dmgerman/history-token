multiline_comment|/* &n;        epat.c  (c) 1997-8  Grant R. Guenther &lt;grant@torque.net&gt;&n;                            Under the terms of the GNU General Public License.&n;&n;&t;This is the low level protocol driver for the EPAT parallel&n;        to IDE adapter from Shuttle Technologies.  This adapter is&n;        used in many popular parallel port disk products such as the&n;        SyQuest EZ drives, the Avatar Shark and the Imation SuperDisk.&n;&t;&n;*/
multiline_comment|/* Changes:&n;&n;        1.01    GRG 1998.05.06 init_proto, release_proto&n;        1.02    Joshua b. Jore CPP(renamed), epat_connect, epat_disconnect&n;&n;*/
DECL|macro|EPAT_VERSION
mdefine_line|#define EPAT_VERSION      &quot;1.02&quot;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &quot;paride.h&quot;
DECL|macro|j44
mdefine_line|#define j44(a,b)&t;&t;(((a&gt;&gt;4)&amp;0x0f)+(b&amp;0xf0))
DECL|macro|j53
mdefine_line|#define j53(a,b)&t;&t;(((a&gt;&gt;3)&amp;0x1f)+((b&lt;&lt;4)&amp;0xe0))
multiline_comment|/* cont =  0   IDE register file&n;   cont =  1   IDE control registers&n;   cont =  2   internal EPAT registers&n;*/
DECL|variable|cont_map
r_static
r_int
id|cont_map
(braket
l_int|3
)braket
op_assign
(brace
l_int|0x18
comma
l_int|0x10
comma
l_int|0
)brace
suffix:semicolon
DECL|function|epat_write_regr
r_static
r_void
id|epat_write_regr
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
id|w0
c_func
(paren
l_int|0x60
op_plus
id|r
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|1
)paren
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
l_int|4
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
r_case
l_int|4
suffix:colon
r_case
l_int|5
suffix:colon
id|w3
c_func
(paren
l_int|0x40
op_plus
id|r
)paren
suffix:semicolon
id|w4
c_func
(paren
id|val
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
DECL|function|epat_read_regr
r_static
r_int
id|epat_read_regr
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
id|a
comma
id|b
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
r_switch
c_cond
(paren
id|pi-&gt;mode
)paren
(brace
r_case
l_int|0
suffix:colon
id|w0
c_func
(paren
id|r
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|3
)paren
suffix:semicolon
id|a
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
id|b
op_assign
id|r1
c_func
(paren
)paren
suffix:semicolon
r_return
id|j44
c_func
(paren
id|a
comma
id|b
)paren
suffix:semicolon
r_case
l_int|1
suffix:colon
id|w0
c_func
(paren
l_int|0x40
op_plus
id|r
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|4
)paren
suffix:semicolon
id|a
op_assign
id|r1
c_func
(paren
)paren
suffix:semicolon
id|b
op_assign
id|r2
c_func
(paren
)paren
suffix:semicolon
id|w0
c_func
(paren
l_int|0xff
)paren
suffix:semicolon
r_return
id|j53
c_func
(paren
id|a
comma
id|b
)paren
suffix:semicolon
r_case
l_int|2
suffix:colon
id|w0
c_func
(paren
l_int|0x20
op_plus
id|r
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|0x25
)paren
suffix:semicolon
id|a
op_assign
id|r0
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
id|a
suffix:semicolon
r_case
l_int|3
suffix:colon
r_case
l_int|4
suffix:colon
r_case
l_int|5
suffix:colon
id|w3
c_func
(paren
id|r
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|0x24
)paren
suffix:semicolon
id|a
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
r_return
id|a
suffix:semicolon
)brace
r_return
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* never gets here */
)brace
DECL|function|epat_read_block
r_static
r_void
id|epat_read_block
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
comma
id|ph
comma
id|a
comma
id|b
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
id|w0
c_func
(paren
l_int|7
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|3
)paren
suffix:semicolon
id|w0
c_func
(paren
l_int|0xff
)paren
suffix:semicolon
id|ph
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
id|count
suffix:semicolon
id|k
op_increment
)paren
(brace
r_if
c_cond
(paren
id|k
op_eq
id|count
op_minus
l_int|1
)paren
id|w0
c_func
(paren
l_int|0xfd
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|6
op_plus
id|ph
)paren
suffix:semicolon
id|a
op_assign
id|r1
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|a
op_amp
l_int|8
)paren
id|b
op_assign
id|a
suffix:semicolon
r_else
(brace
id|w2
c_func
(paren
l_int|4
op_plus
id|ph
)paren
suffix:semicolon
id|b
op_assign
id|r1
c_func
(paren
)paren
suffix:semicolon
)brace
id|buf
(braket
id|k
)braket
op_assign
id|j44
c_func
(paren
id|a
comma
id|b
)paren
suffix:semicolon
id|ph
op_assign
l_int|1
op_minus
id|ph
suffix:semicolon
)brace
id|w0
c_func
(paren
l_int|0
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
l_int|1
suffix:colon
id|w0
c_func
(paren
l_int|0x47
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|5
)paren
suffix:semicolon
id|w0
c_func
(paren
l_int|0xff
)paren
suffix:semicolon
id|ph
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
id|count
suffix:semicolon
id|k
op_increment
)paren
(brace
r_if
c_cond
(paren
id|k
op_eq
id|count
op_minus
l_int|1
)paren
id|w0
c_func
(paren
l_int|0xfd
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|4
op_plus
id|ph
)paren
suffix:semicolon
id|a
op_assign
id|r1
c_func
(paren
)paren
suffix:semicolon
id|b
op_assign
id|r2
c_func
(paren
)paren
suffix:semicolon
id|buf
(braket
id|k
)braket
op_assign
id|j53
c_func
(paren
id|a
comma
id|b
)paren
suffix:semicolon
id|ph
op_assign
l_int|1
op_minus
id|ph
suffix:semicolon
)brace
id|w0
c_func
(paren
l_int|0
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
id|w0
c_func
(paren
l_int|0x27
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|0x25
)paren
suffix:semicolon
id|w0
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|ph
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
id|count
op_minus
l_int|1
suffix:semicolon
id|k
op_increment
)paren
(brace
id|w2
c_func
(paren
l_int|0x24
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
l_int|1
op_minus
id|ph
suffix:semicolon
)brace
id|w2
c_func
(paren
l_int|0x26
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|0x27
)paren
suffix:semicolon
id|buf
(braket
id|count
op_minus
l_int|1
)braket
op_assign
id|r0
c_func
(paren
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|0x25
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
id|w3
c_func
(paren
l_int|0x80
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|0x24
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
op_minus
l_int|1
suffix:semicolon
id|k
op_increment
)paren
(brace
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
)brace
id|w2
c_func
(paren
l_int|4
)paren
suffix:semicolon
id|w3
c_func
(paren
l_int|0xa0
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|0x24
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
id|w3
c_func
(paren
l_int|0x80
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|0x24
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
(brace
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
)brace
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
id|w2
c_func
(paren
l_int|4
)paren
suffix:semicolon
id|w3
c_func
(paren
l_int|0xa0
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|0x24
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
id|w3
c_func
(paren
l_int|0x80
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|0x24
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
(brace
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
)brace
r_for
c_loop
(paren
id|k
op_assign
id|count
op_minus
l_int|4
suffix:semicolon
id|k
OL
id|count
op_minus
l_int|1
suffix:semicolon
id|k
op_increment
)paren
(brace
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
)brace
id|w2
c_func
(paren
l_int|4
)paren
suffix:semicolon
id|w3
c_func
(paren
l_int|0xa0
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|0x24
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
DECL|function|epat_write_block
r_static
r_void
id|epat_write_block
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
id|ph
comma
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
id|w0
c_func
(paren
l_int|0x67
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|5
)paren
suffix:semicolon
id|ph
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
l_int|4
op_plus
id|ph
)paren
suffix:semicolon
id|ph
op_assign
l_int|1
op_minus
id|ph
suffix:semicolon
)brace
id|w2
c_func
(paren
l_int|7
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
id|w3
c_func
(paren
l_int|0xc0
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
id|w4
c_func
(paren
id|buf
(braket
id|k
)braket
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
l_int|4
suffix:colon
id|w3
c_func
(paren
l_int|0xc0
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
(paren
id|count
op_div
l_int|2
)paren
suffix:semicolon
id|k
op_increment
)paren
(brace
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
l_int|5
suffix:colon
id|w3
c_func
(paren
l_int|0xc0
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
(paren
id|count
op_div
l_int|4
)paren
suffix:semicolon
id|k
op_increment
)paren
(brace
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
)brace
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
multiline_comment|/* these macros access the EPAT registers in native addressing */
DECL|macro|WR
mdefine_line|#define&t;WR(r,v)&t;&t;epat_write_regr(pi,2,r,v)
DECL|macro|RR
mdefine_line|#define&t;RR(r)&t;&t;(epat_read_regr(pi,2,r))
multiline_comment|/* and these access the IDE task file */
DECL|macro|WRi
mdefine_line|#define WRi(r,v)         epat_write_regr(pi,0,r,v)
DECL|macro|RRi
mdefine_line|#define RRi(r)           (epat_read_regr(pi,0,r))
multiline_comment|/* FIXME:  the CPP stuff should be fixed to handle multiple EPATs on a chain */
DECL|macro|CPP
mdefine_line|#define CPP(x) &t;w2(4);w0(0x22);w0(0xaa);w0(0x55);w0(0);w0(0xff);&bslash;&n;                w0(0x87);w0(0x78);w0(x);w2(4);w2(5);w2(4);w0(0xff);
DECL|function|epat_connect
r_static
r_void
id|epat_connect
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
macro_line|#ifdef CONFIG_PARIDE_EPATC8
multiline_comment|/* Initialize the chip */
id|CPP
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|CPP
c_func
(paren
l_int|0x40
)paren
suffix:semicolon
id|CPP
c_func
(paren
l_int|0xe0
)paren
suffix:semicolon
id|w0
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|4
)paren
suffix:semicolon
id|WR
c_func
(paren
l_int|0x8
comma
l_int|0x12
)paren
suffix:semicolon
id|WR
c_func
(paren
l_int|0xc
comma
l_int|0x14
)paren
suffix:semicolon
id|WR
c_func
(paren
l_int|0x12
comma
l_int|0x10
)paren
suffix:semicolon
id|WR
c_func
(paren
l_int|0xe
comma
l_int|0xf
)paren
suffix:semicolon
id|WR
c_func
(paren
l_int|0xf
comma
l_int|4
)paren
suffix:semicolon
multiline_comment|/* WR(0xe,0xa);WR(0xf,4); */
id|WR
c_func
(paren
l_int|0xe
comma
l_int|0xd
)paren
suffix:semicolon
id|WR
c_func
(paren
l_int|0xf
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* CPP(0x30); */
multiline_comment|/* Connect to the chip */
id|CPP
c_func
(paren
l_int|0xe0
)paren
suffix:semicolon
id|w0
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|4
)paren
suffix:semicolon
multiline_comment|/* Idle into SPP */
r_if
c_cond
(paren
id|pi-&gt;mode
op_ge
l_int|3
)paren
(brace
id|w0
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|4
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|0xc
)paren
suffix:semicolon
multiline_comment|/* Request EPP */
id|w0
c_func
(paren
l_int|0x40
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
id|w2
c_func
(paren
l_int|4
)paren
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
l_int|4
)paren
suffix:semicolon
)brace
macro_line|#else
id|CPP
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|CPP
c_func
(paren
l_int|0xe0
)paren
suffix:semicolon
id|w0
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|4
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pi-&gt;mode
op_ge
l_int|3
)paren
(brace
id|w0
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|4
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|0xc
)paren
suffix:semicolon
id|w0
c_func
(paren
l_int|0x40
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
id|w2
c_func
(paren
l_int|4
)paren
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
l_int|4
)paren
suffix:semicolon
)brace
id|WR
c_func
(paren
l_int|8
comma
l_int|0x10
)paren
suffix:semicolon
id|WR
c_func
(paren
l_int|0xc
comma
l_int|0x14
)paren
suffix:semicolon
id|WR
c_func
(paren
l_int|0xa
comma
l_int|0x38
)paren
suffix:semicolon
id|WR
c_func
(paren
l_int|0x12
comma
l_int|0x10
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|function|epat_disconnect
r_static
r_void
id|epat_disconnect
(paren
id|PIA
op_star
id|pi
)paren
(brace
id|CPP
c_func
(paren
l_int|0x30
)paren
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
DECL|function|epat_test_proto
r_static
r_int
id|epat_test_proto
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
id|k
comma
id|j
comma
id|f
comma
id|cc
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
id|epat_connect
c_func
(paren
id|pi
)paren
suffix:semicolon
id|cc
op_assign
id|RR
c_func
(paren
l_int|0xd
)paren
suffix:semicolon
id|epat_disconnect
c_func
(paren
id|pi
)paren
suffix:semicolon
id|epat_connect
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
id|WRi
c_func
(paren
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
id|WRi
c_func
(paren
l_int|2
comma
id|k
op_xor
l_int|0xaa
)paren
suffix:semicolon
id|WRi
c_func
(paren
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
id|RRi
c_func
(paren
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
id|epat_disconnect
c_func
(paren
id|pi
)paren
suffix:semicolon
id|f
op_assign
l_int|0
suffix:semicolon
id|epat_connect
c_func
(paren
id|pi
)paren
suffix:semicolon
id|WR
c_func
(paren
l_int|0x13
comma
l_int|1
)paren
suffix:semicolon
id|WR
c_func
(paren
l_int|0x13
comma
l_int|0
)paren
suffix:semicolon
id|WR
c_func
(paren
l_int|0xa
comma
l_int|0x11
)paren
suffix:semicolon
id|epat_read_block
c_func
(paren
id|pi
comma
id|scratch
comma
l_int|512
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
r_if
c_cond
(paren
(paren
id|scratch
(braket
l_int|2
op_star
id|k
)braket
op_amp
l_int|0xff
)paren
op_ne
id|k
)paren
id|f
op_increment
suffix:semicolon
r_if
c_cond
(paren
(paren
id|scratch
(braket
l_int|2
op_star
id|k
op_plus
l_int|1
)braket
op_amp
l_int|0xff
)paren
op_ne
(paren
l_int|0xff
op_minus
id|k
)paren
)paren
id|f
op_increment
suffix:semicolon
)brace
id|epat_disconnect
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
l_string|&quot;%s: epat: port 0x%x, mode %d, ccr %x, test=(%d,%d,%d)&bslash;n&quot;
comma
id|pi-&gt;device
comma
id|pi-&gt;port
comma
id|pi-&gt;mode
comma
id|cc
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
id|f
)paren
suffix:semicolon
)brace
r_return
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
op_logical_or
id|f
suffix:semicolon
)brace
DECL|function|epat_log_adapter
r_static
r_void
id|epat_log_adapter
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
id|ver
suffix:semicolon
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
l_string|&quot;5/3&quot;
comma
l_string|&quot;8-bit&quot;
comma
l_string|&quot;EPP-8&quot;
comma
l_string|&quot;EPP-16&quot;
comma
l_string|&quot;EPP-32&quot;
)brace
suffix:semicolon
id|epat_connect
c_func
(paren
id|pi
)paren
suffix:semicolon
id|WR
c_func
(paren
l_int|0xa
comma
l_int|0x38
)paren
suffix:semicolon
multiline_comment|/* read the version code */
id|ver
op_assign
id|RR
c_func
(paren
l_int|0xb
)paren
suffix:semicolon
id|epat_disconnect
c_func
(paren
id|pi
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s: epat %s, Shuttle EPAT chip %x at 0x%x, &quot;
comma
id|pi-&gt;device
comma
id|EPAT_VERSION
comma
id|ver
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
DECL|function|epat_init_proto
r_static
r_void
id|epat_init_proto
c_func
(paren
id|PIA
op_star
id|pi
)paren
(brace
id|MOD_INC_USE_COUNT
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;epat_init_proto&quot;
)paren
suffix:semicolon
)brace
DECL|function|epat_release_proto
r_static
r_void
id|epat_release_proto
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
DECL|variable|epat
r_struct
id|pi_protocol
id|epat
op_assign
(brace
l_string|&quot;epat&quot;
comma
l_int|0
comma
l_int|6
comma
l_int|3
comma
l_int|1
comma
l_int|1
comma
id|epat_write_regr
comma
id|epat_read_regr
comma
id|epat_write_block
comma
id|epat_read_block
comma
id|epat_connect
comma
id|epat_disconnect
comma
l_int|0
comma
l_int|0
comma
id|epat_test_proto
comma
id|epat_log_adapter
comma
id|epat_init_proto
comma
id|epat_release_proto
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
id|epat
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
id|epat
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* end of epat.c */
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
