multiline_comment|/* &n;        comm.c    (c) 1997-8  Grant R. Guenther &lt;grant@torque.net&gt;&n;                              Under the terms of the GNU General Public License.&n;&n;&t;comm.c is a low-level protocol driver for some older models&n;&t;of the DataStor &quot;Commuter&quot; parallel to IDE adapter.  Some of&n;&t;the parallel port devices marketed by Arista currently&n;&t;use this adapter.&n;*/
multiline_comment|/* Changes:&n;&n;&t;1.01&t;GRG 1998.05.05  init_proto, release_proto&n;&n;*/
DECL|macro|COMM_VERSION
mdefine_line|#define COMM_VERSION      &quot;1.01&quot;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &quot;paride.h&quot;
multiline_comment|/* mode codes:  0  nybble reads, 8-bit writes&n;                1  8-bit reads and writes&n;                2  8-bit EPP mode&n;*/
DECL|macro|j44
mdefine_line|#define j44(a,b)&t;(((a&gt;&gt;3)&amp;0x0f)|((b&lt;&lt;1)&amp;0xf0))
DECL|macro|P1
mdefine_line|#define P1&t;w2(5);w2(0xd);w2(0xd);w2(5);w2(4);
DECL|macro|P2
mdefine_line|#define P2&t;w2(5);w2(7);w2(7);w2(5);w2(4);
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
DECL|function|comm_read_regr
r_static
r_int
id|comm_read_regr
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
id|l
comma
id|h
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
id|P1
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
id|w0
c_func
(paren
l_int|0x80
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
r_case
l_int|1
suffix:colon
id|w0
c_func
(paren
id|r
op_plus
l_int|0x20
)paren
suffix:semicolon
id|P1
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
l_int|0x26
)paren
suffix:semicolon
id|h
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
id|h
suffix:semicolon
r_case
l_int|2
suffix:colon
r_case
l_int|3
suffix:colon
r_case
l_int|4
suffix:colon
id|w3
c_func
(paren
id|r
op_plus
l_int|0x20
)paren
suffix:semicolon
id|r1
c_func
(paren
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|0x24
)paren
suffix:semicolon
id|h
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
id|h
suffix:semicolon
)brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|comm_write_regr
r_static
r_void
id|comm_write_regr
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
id|w0
c_func
(paren
id|r
)paren
suffix:semicolon
id|P1
suffix:semicolon
id|w0
c_func
(paren
id|val
)paren
suffix:semicolon
id|P2
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
r_case
l_int|3
suffix:colon
r_case
l_int|4
suffix:colon
id|w3
c_func
(paren
id|r
)paren
suffix:semicolon
id|r1
c_func
(paren
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
DECL|function|comm_connect
r_static
r_void
id|comm_connect
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
id|w0
c_func
(paren
l_int|0xff
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
l_int|4
)paren
suffix:semicolon
id|w0
c_func
(paren
l_int|0xaa
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
l_int|4
)paren
suffix:semicolon
id|w0
c_func
(paren
l_int|0x00
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
l_int|4
)paren
suffix:semicolon
id|w0
c_func
(paren
l_int|0x87
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
l_int|4
)paren
suffix:semicolon
id|w0
c_func
(paren
l_int|0xe0
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
DECL|function|comm_disconnect
r_static
r_void
id|comm_disconnect
(paren
id|PIA
op_star
id|pi
)paren
(brace
id|w2
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|w2
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
DECL|function|comm_read_block
r_static
r_void
id|comm_read_block
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
id|i
comma
id|l
comma
id|h
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
l_int|0x48
)paren
suffix:semicolon
id|P1
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
id|count
suffix:semicolon
id|i
op_increment
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
id|w0
c_func
(paren
l_int|0x80
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
id|buf
(braket
id|i
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
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|w0
c_func
(paren
l_int|0x68
)paren
suffix:semicolon
id|P1
suffix:semicolon
id|w0
c_func
(paren
l_int|0
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
id|count
suffix:semicolon
id|i
op_increment
)paren
(brace
id|w2
c_func
(paren
l_int|0x26
)paren
suffix:semicolon
id|buf
(braket
id|i
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
l_int|0x24
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
l_int|2
suffix:colon
id|w3
c_func
(paren
l_int|0x68
)paren
suffix:semicolon
id|r1
c_func
(paren
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
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|count
suffix:semicolon
id|i
op_increment
)paren
id|buf
(braket
id|i
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
l_int|3
suffix:colon
id|w3
c_func
(paren
l_int|0x68
)paren
suffix:semicolon
id|r1
c_func
(paren
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
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|count
op_div
l_int|2
suffix:semicolon
id|i
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
id|i
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
l_int|0x68
)paren
suffix:semicolon
id|r1
c_func
(paren
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
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|count
op_div
l_int|4
suffix:semicolon
id|i
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
id|i
)braket
op_assign
id|r4l
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
multiline_comment|/* NB: Watch out for the byte swapped writes ! */
DECL|function|comm_write_block
r_static
r_void
id|comm_write_block
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
id|w0
c_func
(paren
l_int|0x68
)paren
suffix:semicolon
id|P1
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
l_int|5
)paren
suffix:semicolon
id|w0
c_func
(paren
id|buf
(braket
id|k
op_xor
l_int|1
)braket
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|7
)paren
suffix:semicolon
)brace
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
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|w3
c_func
(paren
l_int|0x48
)paren
suffix:semicolon
id|r1
c_func
(paren
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
op_xor
l_int|1
)braket
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
l_int|0x48
)paren
suffix:semicolon
id|r1
c_func
(paren
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
id|pi_swab16
c_func
(paren
id|buf
comma
id|k
)paren
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
l_int|0x48
)paren
suffix:semicolon
id|r1
c_func
(paren
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
id|pi_swab32
c_func
(paren
id|buf
comma
id|k
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
DECL|function|comm_log_adapter
r_static
r_void
id|comm_log_adapter
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
l_int|5
)braket
op_assign
(brace
l_string|&quot;4-bit&quot;
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
id|printk
c_func
(paren
l_string|&quot;%s: comm %s, DataStor Commuter at 0x%x, &quot;
comma
id|pi-&gt;device
comma
id|COMM_VERSION
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
DECL|variable|comm
r_static
r_struct
id|pi_protocol
id|comm
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|name
op_assign
l_string|&quot;comm&quot;
comma
dot
id|max_mode
op_assign
l_int|5
comma
dot
id|epp_first
op_assign
l_int|2
comma
dot
id|default_delay
op_assign
l_int|1
comma
dot
id|max_units
op_assign
l_int|1
comma
dot
id|write_regr
op_assign
id|comm_write_regr
comma
dot
id|read_regr
op_assign
id|comm_read_regr
comma
dot
id|write_block
op_assign
id|comm_write_block
comma
dot
id|read_block
op_assign
id|comm_read_block
comma
dot
id|connect
op_assign
id|comm_connect
comma
dot
id|disconnect
op_assign
id|comm_disconnect
comma
dot
id|log_adapter
op_assign
id|comm_log_adapter
comma
)brace
suffix:semicolon
DECL|function|comm_init
r_static
r_int
id|__init
id|comm_init
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
id|comm
)paren
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|comm_exit
r_static
r_void
id|__exit
id|comm_exit
c_func
(paren
r_void
)paren
(brace
id|pi_unregister
c_func
(paren
op_amp
id|comm
)paren
suffix:semicolon
)brace
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|module_init
c_func
(paren
id|comm_init
)paren
id|module_exit
c_func
(paren
id|comm_exit
)paren
eof
