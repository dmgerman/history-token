multiline_comment|/* ------------------------------------------------------------------------- */
multiline_comment|/* i2c-algo-pcf.c i2c driver algorithms for PCF8584 adapters&t;&t;     */
multiline_comment|/* ------------------------------------------------------------------------- */
multiline_comment|/*   Copyright (C) 1995-1997 Simon G. Vogl&n;                   1998-2000 Hans Berglund&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&t;&t;     */
multiline_comment|/* ------------------------------------------------------------------------- */
multiline_comment|/* With some changes from Ky&#xfffd;sti M&#xfffd;lkki &lt;kmalkki@cc.hut.fi&gt; and &n;   Frodo Looijaard &lt;frodol@dds.nl&gt; ,and also from Martin Bailey&n;   &lt;mbailey@littlefeet-inc.com&gt; */
multiline_comment|/* Partially rewriten by Oleg I. Vdovikin &lt;vdovikin@jscc.ru&gt; to handle multiple&n;   messages, proper stop/repstart signaling during receive,&n;   added detect code */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/i2c.h&gt;
macro_line|#include &lt;linux/i2c-algo-pcf.h&gt;
macro_line|#include &quot;i2c-algo-pcf.h&quot;
DECL|macro|DEB2
mdefine_line|#define DEB2(x) if (i2c_debug&gt;=2) x
DECL|macro|DEB3
mdefine_line|#define DEB3(x) if (i2c_debug&gt;=3) x /* print several statistical values*/
DECL|macro|DEBPROTO
mdefine_line|#define DEBPROTO(x) if (i2c_debug&gt;=9) x;
multiline_comment|/* debug the protocol by showing transferred bits */
DECL|macro|DEF_TIMEOUT
mdefine_line|#define DEF_TIMEOUT 16
multiline_comment|/* module parameters:&n; */
DECL|variable|i2c_debug
r_static
r_int
id|i2c_debug
suffix:semicolon
multiline_comment|/* --- setting states on the bus with the right timing: ---------------&t;*/
DECL|macro|set_pcf
mdefine_line|#define set_pcf(adap, ctl, val) adap-&gt;setpcf(adap-&gt;data, ctl, val)
DECL|macro|get_pcf
mdefine_line|#define get_pcf(adap, ctl) adap-&gt;getpcf(adap-&gt;data, ctl)
DECL|macro|get_own
mdefine_line|#define get_own(adap) adap-&gt;getown(adap-&gt;data)
DECL|macro|get_clock
mdefine_line|#define get_clock(adap) adap-&gt;getclock(adap-&gt;data)
DECL|macro|i2c_outb
mdefine_line|#define i2c_outb(adap, val) adap-&gt;setpcf(adap-&gt;data, 0, val)
DECL|macro|i2c_inb
mdefine_line|#define i2c_inb(adap) adap-&gt;getpcf(adap-&gt;data, 0)
multiline_comment|/* --- other auxiliary functions --------------------------------------&t;*/
DECL|function|i2c_start
r_static
r_void
id|i2c_start
c_func
(paren
r_struct
id|i2c_algo_pcf_data
op_star
id|adap
)paren
(brace
id|DEBPROTO
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;S &quot;
)paren
)paren
suffix:semicolon
id|set_pcf
c_func
(paren
id|adap
comma
l_int|1
comma
id|I2C_PCF_START
)paren
suffix:semicolon
)brace
DECL|function|i2c_repstart
r_static
r_void
id|i2c_repstart
c_func
(paren
r_struct
id|i2c_algo_pcf_data
op_star
id|adap
)paren
(brace
id|DEBPROTO
c_func
(paren
id|printk
c_func
(paren
l_string|&quot; Sr &quot;
)paren
)paren
suffix:semicolon
id|set_pcf
c_func
(paren
id|adap
comma
l_int|1
comma
id|I2C_PCF_REPSTART
)paren
suffix:semicolon
)brace
DECL|function|i2c_stop
r_static
r_void
id|i2c_stop
c_func
(paren
r_struct
id|i2c_algo_pcf_data
op_star
id|adap
)paren
(brace
id|DEBPROTO
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;P&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|set_pcf
c_func
(paren
id|adap
comma
l_int|1
comma
id|I2C_PCF_STOP
)paren
suffix:semicolon
)brace
DECL|function|wait_for_bb
r_static
r_int
id|wait_for_bb
c_func
(paren
r_struct
id|i2c_algo_pcf_data
op_star
id|adap
)paren
(brace
r_int
id|timeout
op_assign
id|DEF_TIMEOUT
suffix:semicolon
r_int
id|status
suffix:semicolon
id|status
op_assign
id|get_pcf
c_func
(paren
id|adap
comma
l_int|1
)paren
suffix:semicolon
macro_line|#ifndef STUB_I2C
r_while
c_loop
(paren
id|timeout
op_decrement
op_logical_and
op_logical_neg
(paren
id|status
op_amp
id|I2C_PCF_BB
)paren
)paren
(brace
id|udelay
c_func
(paren
l_int|100
)paren
suffix:semicolon
multiline_comment|/* wait for 100 us */
id|status
op_assign
id|get_pcf
c_func
(paren
id|adap
comma
l_int|1
)paren
suffix:semicolon
)brace
macro_line|#endif
r_if
c_cond
(paren
id|timeout
op_le
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Timeout waiting for Bus Busy&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_return
(paren
id|timeout
op_le
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|wait_for_pin
r_static
r_int
id|wait_for_pin
c_func
(paren
r_struct
id|i2c_algo_pcf_data
op_star
id|adap
comma
r_int
op_star
id|status
)paren
(brace
r_int
id|timeout
op_assign
id|DEF_TIMEOUT
suffix:semicolon
op_star
id|status
op_assign
id|get_pcf
c_func
(paren
id|adap
comma
l_int|1
)paren
suffix:semicolon
macro_line|#ifndef STUB_I2C
r_while
c_loop
(paren
id|timeout
op_decrement
op_logical_and
(paren
op_star
id|status
op_amp
id|I2C_PCF_PIN
)paren
)paren
(brace
id|adap
op_member_access_from_pointer
id|waitforpin
c_func
(paren
)paren
suffix:semicolon
op_star
id|status
op_assign
id|get_pcf
c_func
(paren
id|adap
comma
l_int|1
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_star
id|status
op_amp
id|I2C_PCF_LAB
)paren
(brace
id|DEB2
c_func
(paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;i2c-algo-pcf.o: lost arbitration (CSR 0x%02x)&bslash;n&quot;
comma
op_star
id|status
)paren
)paren
suffix:semicolon
multiline_comment|/* Cleanup from LAB-- reset and enable ESO.&n;&t;&t; * This resets the PCF8584; since we&squot;ve lost the bus, no&n;&t;&t; * further attempts should be made by callers to clean up &n;&t;&t; * (no i2c_stop() etc.)&n;&t;&t; */
id|set_pcf
c_func
(paren
id|adap
comma
l_int|1
comma
id|I2C_PCF_PIN
)paren
suffix:semicolon
id|set_pcf
c_func
(paren
id|adap
comma
l_int|1
comma
id|I2C_PCF_ESO
)paren
suffix:semicolon
multiline_comment|/* TODO: we should pause for a time period sufficient for any&n;&t;&t; * running I2C transaction to complete-- the arbitration&n;&t;&t; * logic won&squot;t work properly until the next START is seen.&n;&t;&t; */
id|DEB2
c_func
(paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;i2c-algo-pcf.o: reset LAB condition (CSR 0x%02x)&bslash;n&quot;
comma
id|get_pcf
c_func
(paren
id|adap
comma
l_int|1
)paren
)paren
)paren
suffix:semicolon
r_return
op_minus
id|EINTR
suffix:semicolon
)brace
macro_line|#endif
r_if
c_cond
(paren
id|timeout
op_le
l_int|0
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_else
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* &n; * This should perform the &squot;PCF8584 initialization sequence&squot; as described&n; * in the Philips IC12 data book (1995, Aug 29).&n; * There should be a 30 clock cycle wait after reset, I assume this&n; * has been fulfilled.&n; * There should be a delay at the end equal to the longest I2C message&n; * to synchronize the BB-bit (in multimaster systems). How long is&n; * this? I assume 1 second is always long enough.&n; *&n; * vdovikin: added detect code for PCF8584&n; */
DECL|function|pcf_init_8584
r_static
r_int
id|pcf_init_8584
(paren
r_struct
id|i2c_algo_pcf_data
op_star
id|adap
)paren
(brace
r_int
r_char
id|temp
suffix:semicolon
id|DEB3
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;i2c-algo-pcf.o: PCF state 0x%02x&bslash;n&quot;
comma
id|get_pcf
c_func
(paren
id|adap
comma
l_int|1
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/* S1=0x80: S0 selected, serial interface off */
id|set_pcf
c_func
(paren
id|adap
comma
l_int|1
comma
id|I2C_PCF_PIN
)paren
suffix:semicolon
multiline_comment|/* check to see S1 now used as R/W ctrl -&n;&t;   PCF8584 does that when ESO is zero */
r_if
c_cond
(paren
(paren
(paren
id|temp
op_assign
id|get_pcf
c_func
(paren
id|adap
comma
l_int|1
)paren
)paren
op_amp
l_int|0x7f
)paren
op_ne
(paren
l_int|0
)paren
)paren
(brace
id|DEB2
c_func
(paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;i2c-algo-pcf.o: PCF detection failed -- can&squot;t select S0 (0x%02x).&bslash;n&quot;
comma
id|temp
)paren
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
multiline_comment|/* definetly not PCF8584 */
)brace
multiline_comment|/* load own address in S0, effective address is (own &lt;&lt; 1)&t;*/
id|i2c_outb
c_func
(paren
id|adap
comma
id|get_own
c_func
(paren
id|adap
)paren
)paren
suffix:semicolon
multiline_comment|/* check it&squot;s really written */
r_if
c_cond
(paren
(paren
id|temp
op_assign
id|i2c_inb
c_func
(paren
id|adap
)paren
)paren
op_ne
id|get_own
c_func
(paren
id|adap
)paren
)paren
(brace
id|DEB2
c_func
(paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;i2c-algo-pcf.o: PCF detection failed -- can&squot;t set S0 (0x%02x).&bslash;n&quot;
comma
id|temp
)paren
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
multiline_comment|/* S1=0xA0, next byte in S2&t;&t;&t;&t;&t;*/
id|set_pcf
c_func
(paren
id|adap
comma
l_int|1
comma
id|I2C_PCF_PIN
op_or
id|I2C_PCF_ES1
)paren
suffix:semicolon
multiline_comment|/* check to see S2 now selected */
r_if
c_cond
(paren
(paren
(paren
id|temp
op_assign
id|get_pcf
c_func
(paren
id|adap
comma
l_int|1
)paren
)paren
op_amp
l_int|0x7f
)paren
op_ne
id|I2C_PCF_ES1
)paren
(brace
id|DEB2
c_func
(paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;i2c-algo-pcf.o: PCF detection failed -- can&squot;t select S2 (0x%02x).&bslash;n&quot;
comma
id|temp
)paren
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
multiline_comment|/* load clock register S2&t;&t;&t;&t;&t;*/
id|i2c_outb
c_func
(paren
id|adap
comma
id|get_clock
c_func
(paren
id|adap
)paren
)paren
suffix:semicolon
multiline_comment|/* check it&squot;s really written, the only 5 lowest bits does matter */
r_if
c_cond
(paren
(paren
(paren
id|temp
op_assign
id|i2c_inb
c_func
(paren
id|adap
)paren
)paren
op_amp
l_int|0x1f
)paren
op_ne
id|get_clock
c_func
(paren
id|adap
)paren
)paren
(brace
id|DEB2
c_func
(paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;i2c-algo-pcf.o: PCF detection failed -- can&squot;t set S2 (0x%02x).&bslash;n&quot;
comma
id|temp
)paren
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
multiline_comment|/* Enable serial interface, idle, S0 selected&t;&t;&t;*/
id|set_pcf
c_func
(paren
id|adap
comma
l_int|1
comma
id|I2C_PCF_IDLE
)paren
suffix:semicolon
multiline_comment|/* check to see PCF is really idled and we can access status register */
r_if
c_cond
(paren
(paren
id|temp
op_assign
id|get_pcf
c_func
(paren
id|adap
comma
l_int|1
)paren
)paren
op_ne
(paren
id|I2C_PCF_PIN
op_or
id|I2C_PCF_BB
)paren
)paren
(brace
id|DEB2
c_func
(paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;i2c-algo-pcf.o: PCF detection failed -- can&squot;t select S1` (0x%02x).&bslash;n&quot;
comma
id|temp
)paren
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;i2c-algo-pcf.o: deteted and initialized PCF8584.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* ----- Utility functions&n; */
DECL|function|try_address
r_static
r_inline
r_int
id|try_address
c_func
(paren
r_struct
id|i2c_algo_pcf_data
op_star
id|adap
comma
r_int
r_char
id|addr
comma
r_int
id|retries
)paren
(brace
r_int
id|i
comma
id|status
comma
id|ret
op_assign
op_minus
l_int|1
suffix:semicolon
r_int
id|wfp
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
id|retries
suffix:semicolon
id|i
op_increment
)paren
(brace
id|i2c_outb
c_func
(paren
id|adap
comma
id|addr
)paren
suffix:semicolon
id|i2c_start
c_func
(paren
id|adap
)paren
suffix:semicolon
id|status
op_assign
id|get_pcf
c_func
(paren
id|adap
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|wfp
op_assign
id|wait_for_pin
c_func
(paren
id|adap
comma
op_amp
id|status
)paren
)paren
op_ge
l_int|0
)paren
(brace
r_if
c_cond
(paren
(paren
id|status
op_amp
id|I2C_PCF_LRB
)paren
op_eq
l_int|0
)paren
(brace
id|i2c_stop
c_func
(paren
id|adap
)paren
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* success! */
)brace
)brace
r_if
c_cond
(paren
id|wfp
op_eq
op_minus
id|EINTR
)paren
(brace
multiline_comment|/* arbitration lost */
id|udelay
c_func
(paren
id|adap-&gt;udelay
)paren
suffix:semicolon
r_return
op_minus
id|EINTR
suffix:semicolon
)brace
id|i2c_stop
c_func
(paren
id|adap
)paren
suffix:semicolon
id|udelay
c_func
(paren
id|adap-&gt;udelay
)paren
suffix:semicolon
)brace
id|DEB2
c_func
(paren
r_if
(paren
id|i
)paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;i2c-algo-pcf.o: needed %d retries for %d&bslash;n&quot;
comma
id|i
comma
id|addr
)paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|pcf_sendbytes
r_static
r_int
id|pcf_sendbytes
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|i2c_adap
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|count
comma
r_int
id|last
)paren
(brace
r_struct
id|i2c_algo_pcf_data
op_star
id|adap
op_assign
id|i2c_adap-&gt;algo_data
suffix:semicolon
r_int
id|wrcount
comma
id|status
comma
id|timeout
suffix:semicolon
r_for
c_loop
(paren
id|wrcount
op_assign
l_int|0
suffix:semicolon
id|wrcount
OL
id|count
suffix:semicolon
op_increment
id|wrcount
)paren
(brace
id|DEB2
c_func
(paren
id|dev_dbg
c_func
(paren
op_amp
id|i2c_adap-&gt;dev
comma
l_string|&quot;i2c_write: writing %2.2X&bslash;n&quot;
comma
id|buf
(braket
id|wrcount
)braket
op_amp
l_int|0xff
)paren
)paren
suffix:semicolon
id|i2c_outb
c_func
(paren
id|adap
comma
id|buf
(braket
id|wrcount
)braket
)paren
suffix:semicolon
id|timeout
op_assign
id|wait_for_pin
c_func
(paren
id|adap
comma
op_amp
id|status
)paren
suffix:semicolon
r_if
c_cond
(paren
id|timeout
)paren
(brace
r_if
c_cond
(paren
id|timeout
op_eq
op_minus
id|EINTR
)paren
(brace
multiline_comment|/* arbitration lost */
r_return
op_minus
id|EINTR
suffix:semicolon
)brace
id|i2c_stop
c_func
(paren
id|adap
)paren
suffix:semicolon
id|dev_err
c_func
(paren
op_amp
id|i2c_adap-&gt;dev
comma
l_string|&quot;i2c_write: error - timeout.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EREMOTEIO
suffix:semicolon
multiline_comment|/* got a better one ?? */
)brace
macro_line|#ifndef STUB_I2C
r_if
c_cond
(paren
id|status
op_amp
id|I2C_PCF_LRB
)paren
(brace
id|i2c_stop
c_func
(paren
id|adap
)paren
suffix:semicolon
id|dev_err
c_func
(paren
op_amp
id|i2c_adap-&gt;dev
comma
l_string|&quot;i2c_write: error - no ack.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EREMOTEIO
suffix:semicolon
multiline_comment|/* got a better one ?? */
)brace
macro_line|#endif
)brace
r_if
c_cond
(paren
id|last
)paren
(brace
id|i2c_stop
c_func
(paren
id|adap
)paren
suffix:semicolon
)brace
r_else
(brace
id|i2c_repstart
c_func
(paren
id|adap
)paren
suffix:semicolon
)brace
r_return
(paren
id|wrcount
)paren
suffix:semicolon
)brace
DECL|function|pcf_readbytes
r_static
r_int
id|pcf_readbytes
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|i2c_adap
comma
r_char
op_star
id|buf
comma
r_int
id|count
comma
r_int
id|last
)paren
(brace
r_int
id|i
comma
id|status
suffix:semicolon
r_struct
id|i2c_algo_pcf_data
op_star
id|adap
op_assign
id|i2c_adap-&gt;algo_data
suffix:semicolon
r_int
id|wfp
suffix:semicolon
multiline_comment|/* increment number of bytes to read by one -- read dummy byte */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
op_le
id|count
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
id|wfp
op_assign
id|wait_for_pin
c_func
(paren
id|adap
comma
op_amp
id|status
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
id|wfp
op_eq
op_minus
id|EINTR
)paren
(brace
multiline_comment|/* arbitration lost */
r_return
op_minus
id|EINTR
suffix:semicolon
)brace
id|i2c_stop
c_func
(paren
id|adap
)paren
suffix:semicolon
id|dev_err
c_func
(paren
op_amp
id|i2c_adap-&gt;dev
comma
l_string|&quot;pcf_readbytes timed out.&bslash;n&quot;
)paren
suffix:semicolon
r_return
(paren
op_minus
l_int|1
)paren
suffix:semicolon
)brace
macro_line|#ifndef STUB_I2C
r_if
c_cond
(paren
(paren
id|status
op_amp
id|I2C_PCF_LRB
)paren
op_logical_and
(paren
id|i
op_ne
id|count
)paren
)paren
(brace
id|i2c_stop
c_func
(paren
id|adap
)paren
suffix:semicolon
id|dev_err
c_func
(paren
op_amp
id|i2c_adap-&gt;dev
comma
l_string|&quot;i2c_read: i2c_inb, No ack.&bslash;n&quot;
)paren
suffix:semicolon
r_return
(paren
op_minus
l_int|1
)paren
suffix:semicolon
)brace
macro_line|#endif
r_if
c_cond
(paren
id|i
op_eq
id|count
op_minus
l_int|1
)paren
(brace
id|set_pcf
c_func
(paren
id|adap
comma
l_int|1
comma
id|I2C_PCF_ESO
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|i
op_eq
id|count
)paren
(brace
r_if
c_cond
(paren
id|last
)paren
(brace
id|i2c_stop
c_func
(paren
id|adap
)paren
suffix:semicolon
)brace
r_else
(brace
id|i2c_repstart
c_func
(paren
id|adap
)paren
suffix:semicolon
)brace
)brace
suffix:semicolon
r_if
c_cond
(paren
id|i
)paren
(brace
id|buf
(braket
id|i
op_minus
l_int|1
)braket
op_assign
id|i2c_inb
c_func
(paren
id|adap
)paren
suffix:semicolon
)brace
r_else
(brace
id|i2c_inb
c_func
(paren
id|adap
)paren
suffix:semicolon
multiline_comment|/* dummy read */
)brace
)brace
r_return
(paren
id|i
op_minus
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|pcf_doAddress
r_static
r_inline
r_int
id|pcf_doAddress
c_func
(paren
r_struct
id|i2c_algo_pcf_data
op_star
id|adap
comma
r_struct
id|i2c_msg
op_star
id|msg
comma
r_int
id|retries
)paren
(brace
r_int
r_int
id|flags
op_assign
id|msg-&gt;flags
suffix:semicolon
r_int
r_char
id|addr
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
(paren
id|flags
op_amp
id|I2C_M_TEN
)paren
)paren
(brace
multiline_comment|/* a ten bit address */
id|addr
op_assign
l_int|0xf0
op_or
(paren
(paren
id|msg-&gt;addr
op_rshift
l_int|7
)paren
op_amp
l_int|0x03
)paren
suffix:semicolon
id|DEB2
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;addr0: %d&bslash;n&quot;
comma
id|addr
)paren
)paren
suffix:semicolon
multiline_comment|/* try extended address code...*/
id|ret
op_assign
id|try_address
c_func
(paren
id|adap
comma
id|addr
comma
id|retries
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ne
l_int|1
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;died at extended address code.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EREMOTEIO
suffix:semicolon
)brace
multiline_comment|/* the remaining 8 bit address */
id|i2c_outb
c_func
(paren
id|adap
comma
id|msg-&gt;addr
op_amp
l_int|0x7f
)paren
suffix:semicolon
multiline_comment|/* Status check comes here */
r_if
c_cond
(paren
id|ret
op_ne
l_int|1
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;died at 2nd address code.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EREMOTEIO
suffix:semicolon
)brace
r_if
c_cond
(paren
id|flags
op_amp
id|I2C_M_RD
)paren
(brace
id|i2c_repstart
c_func
(paren
id|adap
)paren
suffix:semicolon
multiline_comment|/* okay, now switch into reading mode */
id|addr
op_or_assign
l_int|0x01
suffix:semicolon
id|ret
op_assign
id|try_address
c_func
(paren
id|adap
comma
id|addr
comma
id|retries
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ne
l_int|1
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;died at extended address code.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EREMOTEIO
suffix:semicolon
)brace
)brace
)brace
r_else
(brace
multiline_comment|/* normal 7bit address&t;*/
id|addr
op_assign
(paren
id|msg-&gt;addr
op_lshift
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|I2C_M_RD
)paren
id|addr
op_or_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|I2C_M_REV_DIR_ADDR
)paren
id|addr
op_xor_assign
l_int|1
suffix:semicolon
id|i2c_outb
c_func
(paren
id|adap
comma
id|addr
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pcf_xfer
r_static
r_int
id|pcf_xfer
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|i2c_adap
comma
r_struct
id|i2c_msg
op_star
id|msgs
comma
r_int
id|num
)paren
(brace
r_struct
id|i2c_algo_pcf_data
op_star
id|adap
op_assign
id|i2c_adap-&gt;algo_data
suffix:semicolon
r_struct
id|i2c_msg
op_star
id|pmsg
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
comma
id|timeout
comma
id|status
suffix:semicolon
multiline_comment|/* Check for bus busy */
id|timeout
op_assign
id|wait_for_bb
c_func
(paren
id|adap
)paren
suffix:semicolon
r_if
c_cond
(paren
id|timeout
)paren
(brace
id|DEB2
c_func
(paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;i2c-algo-pcf.o: &quot;
l_string|&quot;Timeout waiting for BB in pcf_xfer&bslash;n&quot;
)paren
suffix:semicolon
)paren
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|ret
op_ge
l_int|0
op_logical_and
id|i
OL
id|num
suffix:semicolon
id|i
op_increment
)paren
(brace
id|pmsg
op_assign
op_amp
id|msgs
(braket
id|i
)braket
suffix:semicolon
id|DEB2
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;i2c-algo-pcf.o: Doing %s %d bytes to 0x%02x - %d of %d messages&bslash;n&quot;
comma
id|pmsg-&gt;flags
op_amp
id|I2C_M_RD
ques
c_cond
l_string|&quot;read&quot;
suffix:colon
l_string|&quot;write&quot;
comma
id|pmsg-&gt;len
comma
id|pmsg-&gt;addr
comma
id|i
op_plus
l_int|1
comma
id|num
)paren
suffix:semicolon
)paren
id|ret
op_assign
id|pcf_doAddress
c_func
(paren
id|adap
comma
id|pmsg
comma
id|i2c_adap-&gt;retries
)paren
suffix:semicolon
multiline_comment|/* Send START */
r_if
c_cond
(paren
id|i
op_eq
l_int|0
)paren
(brace
id|i2c_start
c_func
(paren
id|adap
)paren
suffix:semicolon
)brace
multiline_comment|/* Wait for PIN (pending interrupt NOT) */
id|timeout
op_assign
id|wait_for_pin
c_func
(paren
id|adap
comma
op_amp
id|status
)paren
suffix:semicolon
r_if
c_cond
(paren
id|timeout
)paren
(brace
r_if
c_cond
(paren
id|timeout
op_eq
op_minus
id|EINTR
)paren
(brace
multiline_comment|/* arbitration lost */
r_return
(paren
op_minus
id|EINTR
)paren
suffix:semicolon
)brace
id|i2c_stop
c_func
(paren
id|adap
)paren
suffix:semicolon
id|DEB2
c_func
(paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;i2c-algo-pcf.o: Timeout waiting &quot;
l_string|&quot;for PIN(1) in pcf_xfer&bslash;n&quot;
)paren
suffix:semicolon
)paren
r_return
(paren
op_minus
id|EREMOTEIO
)paren
suffix:semicolon
)brace
macro_line|#ifndef STUB_I2C
multiline_comment|/* Check LRB (last rcvd bit - slave ack) */
r_if
c_cond
(paren
id|status
op_amp
id|I2C_PCF_LRB
)paren
(brace
id|i2c_stop
c_func
(paren
id|adap
)paren
suffix:semicolon
id|DEB2
c_func
(paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;i2c-algo-pcf.o: No LRB(1) in pcf_xfer&bslash;n&quot;
)paren
suffix:semicolon
)paren
r_return
(paren
op_minus
id|EREMOTEIO
)paren
suffix:semicolon
)brace
macro_line|#endif
id|DEB3
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;i2c-algo-pcf.o: Msg %d, addr=0x%x, flags=0x%x, len=%d&bslash;n&quot;
comma
id|i
comma
id|msgs
(braket
id|i
)braket
dot
id|addr
comma
id|msgs
(braket
id|i
)braket
dot
id|flags
comma
id|msgs
(braket
id|i
)braket
dot
id|len
)paren
suffix:semicolon
)paren
multiline_comment|/* Read */
r_if
c_cond
(paren
id|pmsg-&gt;flags
op_amp
id|I2C_M_RD
)paren
(brace
multiline_comment|/* read bytes into buffer*/
id|ret
op_assign
id|pcf_readbytes
c_func
(paren
id|i2c_adap
comma
id|pmsg-&gt;buf
comma
id|pmsg-&gt;len
comma
(paren
id|i
op_plus
l_int|1
op_eq
id|num
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ne
id|pmsg-&gt;len
)paren
(brace
id|DEB2
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;i2c-algo-pcf.o: fail: &quot;
l_string|&quot;only read %d bytes.&bslash;n&quot;
comma
id|ret
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|DEB2
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;i2c-algo-pcf.o: read %d bytes.&bslash;n&quot;
comma
id|ret
)paren
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/* Write */
id|ret
op_assign
id|pcf_sendbytes
c_func
(paren
id|i2c_adap
comma
id|pmsg-&gt;buf
comma
id|pmsg-&gt;len
comma
(paren
id|i
op_plus
l_int|1
op_eq
id|num
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ne
id|pmsg-&gt;len
)paren
(brace
id|DEB2
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;i2c-algo-pcf.o: fail: &quot;
l_string|&quot;only wrote %d bytes.&bslash;n&quot;
comma
id|ret
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|DEB2
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;i2c-algo-pcf.o: wrote %d bytes.&bslash;n&quot;
comma
id|ret
)paren
)paren
suffix:semicolon
)brace
)brace
)brace
r_return
(paren
id|i
)paren
suffix:semicolon
)brace
DECL|function|pcf_func
r_static
id|u32
id|pcf_func
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|adap
)paren
(brace
r_return
id|I2C_FUNC_I2C
op_or
id|I2C_FUNC_SMBUS_EMUL
op_or
id|I2C_FUNC_10BIT_ADDR
op_or
id|I2C_FUNC_PROTOCOL_MANGLING
suffix:semicolon
)brace
multiline_comment|/* -----exported algorithm data: -------------------------------------&t;*/
DECL|variable|pcf_algo
r_static
r_struct
id|i2c_algorithm
id|pcf_algo
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;PCF8584 algorithm&quot;
comma
dot
id|id
op_assign
id|I2C_ALGO_PCF
comma
dot
id|master_xfer
op_assign
id|pcf_xfer
comma
dot
id|functionality
op_assign
id|pcf_func
comma
)brace
suffix:semicolon
multiline_comment|/* &n; * registering functions to load algorithms at runtime &n; */
DECL|function|i2c_pcf_add_bus
r_int
id|i2c_pcf_add_bus
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|adap
)paren
(brace
r_struct
id|i2c_algo_pcf_data
op_star
id|pcf_adap
op_assign
id|adap-&gt;algo_data
suffix:semicolon
r_int
id|rval
suffix:semicolon
id|DEB2
c_func
(paren
id|dev_dbg
c_func
(paren
op_amp
id|adap-&gt;dev
comma
l_string|&quot;hw routines registered.&bslash;n&quot;
)paren
)paren
suffix:semicolon
multiline_comment|/* register new adapter to i2c module... */
id|adap-&gt;id
op_or_assign
id|pcf_algo.id
suffix:semicolon
id|adap-&gt;algo
op_assign
op_amp
id|pcf_algo
suffix:semicolon
id|adap-&gt;timeout
op_assign
l_int|100
suffix:semicolon
multiline_comment|/* default values, should&t;*/
id|adap-&gt;retries
op_assign
l_int|3
suffix:semicolon
multiline_comment|/* be replaced by defines&t;*/
id|rval
op_assign
id|pcf_init_8584
c_func
(paren
id|pcf_adap
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rval
)paren
id|i2c_add_adapter
c_func
(paren
id|adap
)paren
suffix:semicolon
r_return
id|rval
suffix:semicolon
)brace
DECL|function|i2c_pcf_del_bus
r_int
id|i2c_pcf_del_bus
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|adap
)paren
(brace
r_return
id|i2c_del_adapter
c_func
(paren
id|adap
)paren
suffix:semicolon
)brace
DECL|variable|i2c_pcf_add_bus
id|EXPORT_SYMBOL
c_func
(paren
id|i2c_pcf_add_bus
)paren
suffix:semicolon
DECL|variable|i2c_pcf_del_bus
id|EXPORT_SYMBOL
c_func
(paren
id|i2c_pcf_del_bus
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Hans Berglund &lt;hb@spacetec.no&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;I2C-Bus PCF8584 algorithm&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|module_param
c_func
(paren
id|i2c_debug
comma
r_int
comma
id|S_IRUGO
op_or
id|S_IWUSR
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|i2c_debug
comma
l_string|&quot;debug level - 0 off; 1 normal; 2,3 more verbose; 9 pcf-protocol&quot;
)paren
suffix:semicolon
eof
