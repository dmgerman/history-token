multiline_comment|/* &n;        fit2.c        (c) 1998  Grant R. Guenther &lt;grant@torque.net&gt;&n;                          Under the terms of the GNU General Public License.&n;&n;&t;fit2.c is a low-level protocol driver for the older version&n;        of the Fidelity International Technology parallel port adapter.  &n;&t;This adapter is used in their TransDisk 2000 and older TransDisk&n;&t;3000 portable hard-drives.  As far as I can tell, this device&n;&t;supports 4-bit mode _only_.  &n;&n;&t;Newer models of the FIT products use an enhanced protocol.&n;&t;The &quot;fit3&quot; protocol module should support current drives.&n;&n;*/
DECL|macro|FIT2_VERSION
mdefine_line|#define FIT2_VERSION      &quot;1.0&quot;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &quot;paride.h&quot;
DECL|macro|j44
mdefine_line|#define j44(a,b)                (((a&gt;&gt;4)&amp;0x0f)|(b&amp;0xf0))
multiline_comment|/* cont = 0 - access the IDE register file &n;   cont = 1 - access the IDE command set &n;&n;NB:  The FIT adapter does not appear to use the control registers.&n;So, we map ALT_STATUS to STATUS and NO-OP writes to the device&n;control register - this means that IDE reset will not work on these&n;devices.&n;&n;*/
DECL|function|fit2_write_regr
r_static
r_void
id|fit2_write_regr
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
r_if
c_cond
(paren
id|cont
op_eq
l_int|1
)paren
r_return
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
id|regr
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
id|val
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
l_int|0
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|4
)paren
suffix:semicolon
)brace
DECL|function|fit2_read_regr
r_static
r_int
id|fit2_read_regr
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
r_if
c_cond
(paren
id|cont
)paren
(brace
r_if
c_cond
(paren
id|regr
op_ne
l_int|6
)paren
r_return
l_int|0xff
suffix:semicolon
id|r
op_assign
l_int|7
suffix:semicolon
)brace
r_else
id|r
op_assign
id|regr
op_plus
l_int|0x10
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
id|r
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
l_int|5
)paren
suffix:semicolon
id|w0
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|a
op_assign
id|r1
c_func
(paren
)paren
suffix:semicolon
id|w0
c_func
(paren
l_int|1
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
l_int|4
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
DECL|function|fit2_read_block
r_static
r_void
id|fit2_read_block
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
comma
id|c
comma
id|d
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
id|count
op_div
l_int|4
suffix:semicolon
id|k
op_increment
)paren
(brace
id|w2
c_func
(paren
l_int|4
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
l_int|0
)paren
suffix:semicolon
id|a
op_assign
id|r1
c_func
(paren
)paren
suffix:semicolon
id|w0
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|b
op_assign
id|r1
c_func
(paren
)paren
suffix:semicolon
id|w0
c_func
(paren
l_int|3
)paren
suffix:semicolon
id|c
op_assign
id|r1
c_func
(paren
)paren
suffix:semicolon
id|w0
c_func
(paren
l_int|2
)paren
suffix:semicolon
id|d
op_assign
id|r1
c_func
(paren
)paren
suffix:semicolon
id|buf
(braket
l_int|4
op_star
id|k
op_plus
l_int|0
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
id|buf
(braket
l_int|4
op_star
id|k
op_plus
l_int|1
)braket
op_assign
id|j44
c_func
(paren
id|d
comma
id|c
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
l_int|5
)paren
suffix:semicolon
id|a
op_assign
id|r1
c_func
(paren
)paren
suffix:semicolon
id|w0
c_func
(paren
l_int|3
)paren
suffix:semicolon
id|b
op_assign
id|r1
c_func
(paren
)paren
suffix:semicolon
id|w0
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|c
op_assign
id|r1
c_func
(paren
)paren
suffix:semicolon
id|w0
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|d
op_assign
id|r1
c_func
(paren
)paren
suffix:semicolon
id|buf
(braket
l_int|4
op_star
id|k
op_plus
l_int|2
)braket
op_assign
id|j44
c_func
(paren
id|d
comma
id|c
)paren
suffix:semicolon
id|buf
(braket
l_int|4
op_star
id|k
op_plus
l_int|3
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
id|w2
c_func
(paren
l_int|4
)paren
suffix:semicolon
)brace
DECL|function|fit2_write_block
r_static
r_void
id|fit2_write_block
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
id|w2
c_func
(paren
l_int|0xc
)paren
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
id|w2
c_func
(paren
l_int|4
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
l_int|5
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
)brace
id|w2
c_func
(paren
l_int|4
)paren
suffix:semicolon
)brace
DECL|function|fit2_connect
r_static
r_void
id|fit2_connect
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
l_int|0xcc
)paren
suffix:semicolon
)brace
DECL|function|fit2_disconnect
r_static
r_void
id|fit2_disconnect
(paren
id|PIA
op_star
id|pi
)paren
(brace
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
DECL|function|fit2_log_adapter
r_static
r_void
id|fit2_log_adapter
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
l_string|&quot;%s: fit2 %s, FIT 2000 adapter at 0x%x, delay %d&bslash;n&quot;
comma
id|pi-&gt;device
comma
id|FIT2_VERSION
comma
id|pi-&gt;port
comma
id|pi-&gt;delay
)paren
suffix:semicolon
)brace
DECL|function|fit2_init_proto
r_static
r_void
id|fit2_init_proto
c_func
(paren
id|PIA
op_star
id|pi
)paren
(brace
id|MOD_INC_USE_COUNT
suffix:semicolon
)brace
DECL|function|fit2_release_proto
r_static
r_void
id|fit2_release_proto
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
DECL|variable|fit2
r_struct
id|pi_protocol
id|fit2
op_assign
(brace
l_string|&quot;fit2&quot;
comma
l_int|0
comma
l_int|1
comma
l_int|2
comma
l_int|1
comma
l_int|1
comma
id|fit2_write_regr
comma
id|fit2_read_regr
comma
id|fit2_write_block
comma
id|fit2_read_block
comma
id|fit2_connect
comma
id|fit2_disconnect
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|fit2_log_adapter
comma
id|fit2_init_proto
comma
id|fit2_release_proto
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
id|fit2
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
id|fit2
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* end of fit2.c */
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
