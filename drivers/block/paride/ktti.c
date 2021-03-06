multiline_comment|/* &n;        ktti.c        (c) 1998  Grant R. Guenther &lt;grant@torque.net&gt;&n;                          Under the terms of the GNU General Public License.&n;&n;&t;ktti.c is a low-level protocol driver for the KT Technology&n;&t;parallel port adapter.  This adapter is used in the &quot;PHd&quot; &n;        portable hard-drives.  As far as I can tell, this device&n;&t;supports 4-bit mode _only_.  &n;&n;*/
DECL|macro|KTTI_VERSION
mdefine_line|#define KTTI_VERSION      &quot;1.0&quot;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &quot;paride.h&quot;
DECL|macro|j44
mdefine_line|#define j44(a,b)                (((a&gt;&gt;4)&amp;0x0f)|(b&amp;0xf0))
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
l_int|0x10
comma
l_int|0x08
)brace
suffix:semicolon
DECL|function|ktti_write_regr
r_static
r_void
id|ktti_write_regr
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
id|w0
c_func
(paren
id|r
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|0xb
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|0xa
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|3
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|6
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
l_int|3
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
l_int|6
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|0xb
)paren
suffix:semicolon
)brace
DECL|function|ktti_read_regr
r_static
r_int
id|ktti_read_regr
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
id|w0
c_func
(paren
id|r
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|0xb
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|0xa
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|9
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
l_int|9
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
l_int|0xc
)paren
suffix:semicolon
id|b
op_assign
id|r1
c_func
(paren
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|9
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
l_int|9
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
)brace
DECL|function|ktti_read_block
r_static
r_void
id|ktti_read_block
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
id|a
comma
id|b
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
(brace
id|w0
c_func
(paren
l_int|0x10
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|0xb
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|0xa
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|9
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
l_int|9
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
l_int|0xc
)paren
suffix:semicolon
id|b
op_assign
id|r1
c_func
(paren
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|9
)paren
suffix:semicolon
id|buf
(braket
l_int|2
op_star
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
l_int|0xc
)paren
suffix:semicolon
id|b
op_assign
id|r1
c_func
(paren
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|9
)paren
suffix:semicolon
id|buf
(braket
l_int|2
op_star
id|k
op_plus
l_int|1
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
)brace
)brace
DECL|function|ktti_write_block
r_static
r_void
id|ktti_write_block
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
(brace
id|w0
c_func
(paren
l_int|0x10
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|0xb
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|0xa
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|3
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|6
)paren
suffix:semicolon
id|w0
c_func
(paren
id|buf
(braket
l_int|2
op_star
id|k
)braket
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
id|buf
(braket
l_int|2
op_star
id|k
op_plus
l_int|1
)braket
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
l_int|0xb
)paren
suffix:semicolon
)brace
)brace
DECL|function|ktti_connect
r_static
r_void
id|ktti_connect
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
l_int|0xb
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|0xa
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
l_int|3
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|6
)paren
suffix:semicolon
)brace
DECL|function|ktti_disconnect
r_static
r_void
id|ktti_disconnect
(paren
id|PIA
op_star
id|pi
)paren
(brace
id|w2
c_func
(paren
l_int|0xb
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|0xa
)paren
suffix:semicolon
id|w0
c_func
(paren
l_int|0xa0
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|3
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
DECL|function|ktti_log_adapter
r_static
r_void
id|ktti_log_adapter
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
id|printk
c_func
(paren
l_string|&quot;%s: ktti %s, KT adapter at 0x%x, delay %d&bslash;n&quot;
comma
id|pi-&gt;device
comma
id|KTTI_VERSION
comma
id|pi-&gt;port
comma
id|pi-&gt;delay
)paren
suffix:semicolon
)brace
DECL|variable|ktti
r_static
r_struct
id|pi_protocol
id|ktti
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
l_string|&quot;ktti&quot;
comma
dot
id|max_mode
op_assign
l_int|1
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
id|ktti_write_regr
comma
dot
id|read_regr
op_assign
id|ktti_read_regr
comma
dot
id|write_block
op_assign
id|ktti_write_block
comma
dot
id|read_block
op_assign
id|ktti_read_block
comma
dot
id|connect
op_assign
id|ktti_connect
comma
dot
id|disconnect
op_assign
id|ktti_disconnect
comma
dot
id|log_adapter
op_assign
id|ktti_log_adapter
comma
)brace
suffix:semicolon
DECL|function|ktti_init
r_static
r_int
id|__init
id|ktti_init
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
id|ktti
)paren
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|ktti_exit
r_static
r_void
id|__exit
id|ktti_exit
c_func
(paren
r_void
)paren
(brace
id|pi_unregister
c_func
(paren
op_amp
id|ktti
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
id|ktti_init
)paren
id|module_exit
c_func
(paren
id|ktti_exit
)paren
eof
