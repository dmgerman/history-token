multiline_comment|/* ------------------------------------------------------------------------- */
multiline_comment|/* i2c-algo-bit.c i2c driver algorithms for bit-shift adapters&t;&t;     */
multiline_comment|/* ------------------------------------------------------------------------- */
multiline_comment|/*   Copyright (C) 1995-2000 Simon G. Vogl&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&t;&t;     */
multiline_comment|/* ------------------------------------------------------------------------- */
multiline_comment|/* With some changes from Ky&#xfffd;sti M&#xfffd;lkki &lt;kmalkki@cc.hut.fi&gt; and even&n;   Frodo Looijaard &lt;frodol@dds.nl&gt; */
multiline_comment|/* $Id: i2c-algo-bit.c,v 1.44 2003/01/21 08:08:16 kmalkki Exp $ */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/i2c.h&gt;
macro_line|#include &lt;linux/i2c-algo-bit.h&gt;
multiline_comment|/* ----- global defines ----------------------------------------------- */
DECL|macro|DEB
mdefine_line|#define DEB(x) if (i2c_debug&gt;=1) x;
DECL|macro|DEB2
mdefine_line|#define DEB2(x) if (i2c_debug&gt;=2) x;
DECL|macro|DEBSTAT
mdefine_line|#define DEBSTAT(x) if (i2c_debug&gt;=3) x; /* print several statistical values*/
DECL|macro|DEBPROTO
mdefine_line|#define DEBPROTO(x) if (i2c_debug&gt;=9) { x; }
multiline_comment|/* debug the protocol by showing transferred bits */
multiline_comment|/* ----- global variables ---------------------------------------------&t;*/
multiline_comment|/* module parameters:&n; */
DECL|variable|i2c_debug
r_static
r_int
id|i2c_debug
suffix:semicolon
DECL|variable|bit_test
r_static
r_int
id|bit_test
suffix:semicolon
multiline_comment|/* see if the line-setting functions work&t;*/
multiline_comment|/* --- setting states on the bus with the right timing: ---------------&t;*/
DECL|macro|setsda
mdefine_line|#define setsda(adap,val) adap-&gt;setsda(adap-&gt;data, val)
DECL|macro|setscl
mdefine_line|#define setscl(adap,val) adap-&gt;setscl(adap-&gt;data, val)
DECL|macro|getsda
mdefine_line|#define getsda(adap) adap-&gt;getsda(adap-&gt;data)
DECL|macro|getscl
mdefine_line|#define getscl(adap) adap-&gt;getscl(adap-&gt;data)
DECL|function|sdalo
r_static
r_inline
r_void
id|sdalo
c_func
(paren
r_struct
id|i2c_algo_bit_data
op_star
id|adap
)paren
(brace
id|setsda
c_func
(paren
id|adap
comma
l_int|0
)paren
suffix:semicolon
id|udelay
c_func
(paren
id|adap-&gt;udelay
)paren
suffix:semicolon
)brace
DECL|function|sdahi
r_static
r_inline
r_void
id|sdahi
c_func
(paren
r_struct
id|i2c_algo_bit_data
op_star
id|adap
)paren
(brace
id|setsda
c_func
(paren
id|adap
comma
l_int|1
)paren
suffix:semicolon
id|udelay
c_func
(paren
id|adap-&gt;udelay
)paren
suffix:semicolon
)brace
DECL|function|scllo
r_static
r_inline
r_void
id|scllo
c_func
(paren
r_struct
id|i2c_algo_bit_data
op_star
id|adap
)paren
(brace
id|setscl
c_func
(paren
id|adap
comma
l_int|0
)paren
suffix:semicolon
id|udelay
c_func
(paren
id|adap-&gt;udelay
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Raise scl line, and do checking for delays. This is necessary for slower&n; * devices.&n; */
DECL|function|sclhi
r_static
r_inline
r_int
id|sclhi
c_func
(paren
r_struct
id|i2c_algo_bit_data
op_star
id|adap
)paren
(brace
r_int
r_int
id|start
suffix:semicolon
id|setscl
c_func
(paren
id|adap
comma
l_int|1
)paren
suffix:semicolon
multiline_comment|/* Not all adapters have scl sense line... */
r_if
c_cond
(paren
id|adap-&gt;getscl
op_eq
l_int|NULL
)paren
r_return
l_int|0
suffix:semicolon
id|start
op_assign
id|jiffies
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|getscl
c_func
(paren
id|adap
)paren
)paren
(brace
multiline_comment|/* the hw knows how to read the clock line,&n; &t;&t; * so we wait until it actually gets high.&n; &t;&t; * This is safer as some chips may hold it low&n; &t;&t; * while they are processing data internally. &n; &t;&t; */
r_if
c_cond
(paren
id|time_after_eq
c_func
(paren
id|jiffies
comma
id|start
op_plus
id|adap-&gt;timeout
)paren
)paren
(brace
r_return
op_minus
id|ETIMEDOUT
suffix:semicolon
)brace
id|cond_resched
c_func
(paren
)paren
suffix:semicolon
)brace
id|DEBSTAT
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;needed %ld jiffies&bslash;n&quot;
comma
id|jiffies
op_minus
id|start
)paren
)paren
suffix:semicolon
id|udelay
c_func
(paren
id|adap-&gt;udelay
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* --- other auxiliary functions --------------------------------------&t;*/
DECL|function|i2c_start
r_static
r_void
id|i2c_start
c_func
(paren
r_struct
id|i2c_algo_bit_data
op_star
id|adap
)paren
(brace
multiline_comment|/* assert: scl, sda are high */
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
id|sdalo
c_func
(paren
id|adap
)paren
suffix:semicolon
id|scllo
c_func
(paren
id|adap
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
id|i2c_algo_bit_data
op_star
id|adap
)paren
(brace
multiline_comment|/* scl, sda may not be high */
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
id|setsda
c_func
(paren
id|adap
comma
l_int|1
)paren
suffix:semicolon
id|sclhi
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
id|sdalo
c_func
(paren
id|adap
)paren
suffix:semicolon
id|scllo
c_func
(paren
id|adap
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
id|i2c_algo_bit_data
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
multiline_comment|/* assert: scl is low */
id|sdalo
c_func
(paren
id|adap
)paren
suffix:semicolon
id|sclhi
c_func
(paren
id|adap
)paren
suffix:semicolon
id|sdahi
c_func
(paren
id|adap
)paren
suffix:semicolon
)brace
multiline_comment|/* send a byte without start cond., look for arbitration, &n;   check ackn. from slave */
multiline_comment|/* returns:&n; * 1 if the device acknowledged&n; * 0 if the device did not ack&n; * -ETIMEDOUT if an error occurred (while raising the scl line)&n; */
DECL|function|i2c_outb
r_static
r_int
id|i2c_outb
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|i2c_adap
comma
r_char
id|c
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
id|sb
suffix:semicolon
r_int
id|ack
suffix:semicolon
r_struct
id|i2c_algo_bit_data
op_star
id|adap
op_assign
id|i2c_adap-&gt;algo_data
suffix:semicolon
multiline_comment|/* assert: scl is low */
r_for
c_loop
(paren
id|i
op_assign
l_int|7
suffix:semicolon
id|i
op_ge
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
(brace
id|sb
op_assign
id|c
op_amp
(paren
l_int|1
op_lshift
id|i
)paren
suffix:semicolon
id|setsda
c_func
(paren
id|adap
comma
id|sb
)paren
suffix:semicolon
id|udelay
c_func
(paren
id|adap-&gt;udelay
)paren
suffix:semicolon
id|DEBPROTO
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%d&quot;
comma
id|sb
op_ne
l_int|0
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sclhi
c_func
(paren
id|adap
)paren
OL
l_int|0
)paren
(brace
multiline_comment|/* timed out */
id|sdahi
c_func
(paren
id|adap
)paren
suffix:semicolon
multiline_comment|/* we don&squot;t want to block the net */
id|DEB2
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot; i2c_outb: 0x%02x, timeout at bit #%d&bslash;n&quot;
comma
id|c
op_amp
l_int|0xff
comma
id|i
)paren
)paren
suffix:semicolon
r_return
op_minus
id|ETIMEDOUT
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* do arbitration here: &n;&t;&t; * if ( sb &amp;&amp; ! getsda(adap) ) -&gt; ouch! Get out of here.&n;&t;&t; */
id|setscl
c_func
(paren
id|adap
comma
l_int|0
)paren
suffix:semicolon
id|udelay
c_func
(paren
id|adap-&gt;udelay
)paren
suffix:semicolon
)brace
id|sdahi
c_func
(paren
id|adap
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sclhi
c_func
(paren
id|adap
)paren
OL
l_int|0
)paren
(brace
multiline_comment|/* timeout */
id|DEB2
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot; i2c_outb: 0x%02x, timeout at ack&bslash;n&quot;
comma
id|c
op_amp
l_int|0xff
)paren
)paren
suffix:semicolon
r_return
op_minus
id|ETIMEDOUT
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* read ack: SDA should be pulled down by slave */
id|ack
op_assign
id|getsda
c_func
(paren
id|adap
)paren
suffix:semicolon
multiline_comment|/* ack: sda is pulled low -&gt;success.&t; */
id|DEB2
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot; i2c_outb: 0x%02x , getsda() = %d&bslash;n&quot;
comma
id|c
op_amp
l_int|0xff
comma
id|ack
)paren
)paren
suffix:semicolon
id|DEBPROTO
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;[%2.2x]&quot;
comma
id|c
op_amp
l_int|0xff
)paren
)paren
suffix:semicolon
id|DEBPROTO
c_func
(paren
r_if
(paren
l_int|0
op_eq
id|ack
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot; A &quot;
)paren
suffix:semicolon
)brace
r_else
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot; NA &quot;
)paren
)paren
suffix:semicolon
id|scllo
c_func
(paren
id|adap
)paren
suffix:semicolon
r_return
l_int|0
op_eq
id|ack
suffix:semicolon
multiline_comment|/* return 1 if device acked&t; */
multiline_comment|/* assert: scl is low (sda undef) */
)brace
DECL|function|i2c_inb
r_static
r_int
id|i2c_inb
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|i2c_adap
)paren
(brace
multiline_comment|/* read byte via i2c port, without start/stop sequence&t;*/
multiline_comment|/* acknowledge is sent in i2c_read.&t;&t;&t;*/
r_int
id|i
suffix:semicolon
r_int
r_char
id|indata
op_assign
l_int|0
suffix:semicolon
r_struct
id|i2c_algo_bit_data
op_star
id|adap
op_assign
id|i2c_adap-&gt;algo_data
suffix:semicolon
multiline_comment|/* assert: scl is low */
id|sdahi
c_func
(paren
id|adap
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
l_int|8
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|sclhi
c_func
(paren
id|adap
)paren
OL
l_int|0
)paren
(brace
multiline_comment|/* timeout */
id|DEB2
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot; i2c_inb: timeout at bit #%d&bslash;n&quot;
comma
l_int|7
op_minus
id|i
)paren
)paren
suffix:semicolon
r_return
op_minus
id|ETIMEDOUT
suffix:semicolon
)brace
suffix:semicolon
id|indata
op_mul_assign
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|getsda
c_func
(paren
id|adap
)paren
)paren
id|indata
op_or_assign
l_int|0x01
suffix:semicolon
id|scllo
c_func
(paren
id|adap
)paren
suffix:semicolon
)brace
multiline_comment|/* assert: scl is low */
id|DEB2
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;i2c_inb: 0x%02x&bslash;n&quot;
comma
id|indata
op_amp
l_int|0xff
)paren
)paren
suffix:semicolon
id|DEBPROTO
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot; 0x%02x&quot;
comma
id|indata
op_amp
l_int|0xff
)paren
)paren
suffix:semicolon
r_return
(paren
r_int
)paren
(paren
id|indata
op_amp
l_int|0xff
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Sanity check for the adapter hardware - check the reaction of&n; * the bus lines only if it seems to be idle.&n; */
DECL|function|test_bus
r_static
r_int
id|test_bus
c_func
(paren
r_struct
id|i2c_algo_bit_data
op_star
id|adap
comma
r_char
op_star
id|name
)paren
(brace
r_int
id|scl
comma
id|sda
suffix:semicolon
id|sda
op_assign
id|getsda
c_func
(paren
id|adap
)paren
suffix:semicolon
r_if
c_cond
(paren
id|adap-&gt;getscl
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;i2c-algo-bit.o: Warning: Adapter can&squot;t read from clock line - skipping test.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|scl
op_assign
id|getscl
c_func
(paren
id|adap
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;i2c-algo-bit.o: Adapter: %s scl: %d  sda: %d -- testing...&bslash;n&quot;
comma
id|name
comma
id|getscl
c_func
(paren
id|adap
)paren
comma
id|getsda
c_func
(paren
id|adap
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|scl
op_logical_or
op_logical_neg
id|sda
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot; i2c-algo-bit.o: %s seems to be busy.&bslash;n&quot;
comma
id|name
)paren
suffix:semicolon
r_goto
id|bailout
suffix:semicolon
)brace
id|sdalo
c_func
(paren
id|adap
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;i2c-algo-bit.o:1 scl: %d  sda: %d &bslash;n&quot;
comma
id|getscl
c_func
(paren
id|adap
)paren
comma
id|getsda
c_func
(paren
id|adap
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_ne
id|getsda
c_func
(paren
id|adap
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;i2c-algo-bit.o: %s SDA stuck high!&bslash;n&quot;
comma
id|name
)paren
suffix:semicolon
id|sdahi
c_func
(paren
id|adap
)paren
suffix:semicolon
r_goto
id|bailout
suffix:semicolon
)brace
r_if
c_cond
(paren
l_int|0
op_eq
id|getscl
c_func
(paren
id|adap
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;i2c-algo-bit.o: %s SCL unexpected low while pulling SDA low!&bslash;n&quot;
comma
id|name
)paren
suffix:semicolon
r_goto
id|bailout
suffix:semicolon
)brace
id|sdahi
c_func
(paren
id|adap
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;i2c-algo-bit.o:2 scl: %d  sda: %d &bslash;n&quot;
comma
id|getscl
c_func
(paren
id|adap
)paren
comma
id|getsda
c_func
(paren
id|adap
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_eq
id|getsda
c_func
(paren
id|adap
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;i2c-algo-bit.o: %s SDA stuck low!&bslash;n&quot;
comma
id|name
)paren
suffix:semicolon
id|sdahi
c_func
(paren
id|adap
)paren
suffix:semicolon
r_goto
id|bailout
suffix:semicolon
)brace
r_if
c_cond
(paren
l_int|0
op_eq
id|getscl
c_func
(paren
id|adap
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;i2c-algo-bit.o: %s SCL unexpected low while SDA high!&bslash;n&quot;
comma
id|name
)paren
suffix:semicolon
r_goto
id|bailout
suffix:semicolon
)brace
id|scllo
c_func
(paren
id|adap
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;i2c-algo-bit.o:3 scl: %d  sda: %d &bslash;n&quot;
comma
id|getscl
c_func
(paren
id|adap
)paren
comma
id|getsda
c_func
(paren
id|adap
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_ne
id|getscl
c_func
(paren
id|adap
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;i2c-algo-bit.o: %s SCL stuck high!&bslash;n&quot;
comma
id|name
)paren
suffix:semicolon
id|sclhi
c_func
(paren
id|adap
)paren
suffix:semicolon
r_goto
id|bailout
suffix:semicolon
)brace
r_if
c_cond
(paren
l_int|0
op_eq
id|getsda
c_func
(paren
id|adap
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;i2c-algo-bit.o: %s SDA unexpected low while pulling SCL low!&bslash;n&quot;
comma
id|name
)paren
suffix:semicolon
r_goto
id|bailout
suffix:semicolon
)brace
id|sclhi
c_func
(paren
id|adap
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;i2c-algo-bit.o:4 scl: %d  sda: %d &bslash;n&quot;
comma
id|getscl
c_func
(paren
id|adap
)paren
comma
id|getsda
c_func
(paren
id|adap
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_eq
id|getscl
c_func
(paren
id|adap
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;i2c-algo-bit.o: %s SCL stuck low!&bslash;n&quot;
comma
id|name
)paren
suffix:semicolon
id|sclhi
c_func
(paren
id|adap
)paren
suffix:semicolon
r_goto
id|bailout
suffix:semicolon
)brace
r_if
c_cond
(paren
l_int|0
op_eq
id|getsda
c_func
(paren
id|adap
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;i2c-algo-bit.o: %s SDA unexpected low while SCL high!&bslash;n&quot;
comma
id|name
)paren
suffix:semicolon
r_goto
id|bailout
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;i2c-algo-bit.o: %s passed test.&bslash;n&quot;
comma
id|name
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|bailout
suffix:colon
id|sdahi
c_func
(paren
id|adap
)paren
suffix:semicolon
id|sclhi
c_func
(paren
id|adap
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
multiline_comment|/* ----- Utility functions&n; */
multiline_comment|/* try_address tries to contact a chip for a number of&n; * times before it gives up.&n; * return values:&n; * 1 chip answered&n; * 0 chip did not answer&n; * -x transmission error&n; */
DECL|function|try_address
r_static
r_inline
r_int
id|try_address
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|i2c_adap
comma
r_int
r_char
id|addr
comma
r_int
id|retries
)paren
(brace
r_struct
id|i2c_algo_bit_data
op_star
id|adap
op_assign
id|i2c_adap-&gt;algo_data
suffix:semicolon
r_int
id|i
comma
id|ret
op_assign
op_minus
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
op_le
id|retries
suffix:semicolon
id|i
op_increment
)paren
(brace
id|ret
op_assign
id|i2c_outb
c_func
(paren
id|i2c_adap
comma
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
l_int|1
)paren
r_break
suffix:semicolon
multiline_comment|/* success! */
id|i2c_stop
c_func
(paren
id|adap
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|5
multiline_comment|/*adap-&gt;udelay*/
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
op_eq
id|retries
)paren
multiline_comment|/* no success */
r_break
suffix:semicolon
id|i2c_start
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
l_string|&quot;i2c-algo-bit.o: Used %d tries to %s client at 0x%02x : %s&bslash;n&quot;
comma
id|i
op_plus
l_int|1
comma
id|addr
op_amp
l_int|1
ques
c_cond
l_string|&quot;read&quot;
suffix:colon
l_string|&quot;write&quot;
comma
id|addr
op_rshift
l_int|1
comma
id|ret
op_eq
l_int|1
ques
c_cond
l_string|&quot;success&quot;
suffix:colon
id|ret
op_eq
l_int|0
ques
c_cond
l_string|&quot;no ack&quot;
suffix:colon
l_string|&quot;failed, timeout?&quot;
)paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|sendbytes
r_static
r_int
id|sendbytes
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
id|msg
)paren
(brace
r_struct
id|i2c_algo_bit_data
op_star
id|adap
op_assign
id|i2c_adap-&gt;algo_data
suffix:semicolon
r_char
id|c
suffix:semicolon
r_const
r_char
op_star
id|temp
op_assign
id|msg-&gt;buf
suffix:semicolon
r_int
id|count
op_assign
id|msg-&gt;len
suffix:semicolon
r_int
r_int
id|nak_ok
op_assign
id|msg-&gt;flags
op_amp
id|I2C_M_IGNORE_NAK
suffix:semicolon
r_int
id|retval
suffix:semicolon
r_int
id|wrcount
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|count
OG
l_int|0
)paren
(brace
id|c
op_assign
op_star
id|temp
suffix:semicolon
id|DEB2
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;i2c-algo-bit.o: %s sendbytes: writing %2.2X&bslash;n&quot;
comma
id|i2c_adap-&gt;name
comma
id|c
op_amp
l_int|0xff
)paren
)paren
suffix:semicolon
id|retval
op_assign
id|i2c_outb
c_func
(paren
id|i2c_adap
comma
id|c
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|retval
OG
l_int|0
)paren
op_logical_or
(paren
id|nak_ok
op_logical_and
(paren
id|retval
op_eq
l_int|0
)paren
)paren
)paren
(brace
multiline_comment|/* ok or ignored NAK */
id|count
op_decrement
suffix:semicolon
id|temp
op_increment
suffix:semicolon
id|wrcount
op_increment
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* arbitration or no acknowledge */
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;i2c-algo-bit.o: %s sendbytes: error - bailout.&bslash;n&quot;
comma
id|i2c_adap-&gt;name
)paren
suffix:semicolon
id|i2c_stop
c_func
(paren
id|adap
)paren
suffix:semicolon
r_return
(paren
id|retval
OL
l_int|0
)paren
ques
c_cond
id|retval
suffix:colon
op_minus
id|EFAULT
suffix:semicolon
multiline_comment|/* got a better one ?? */
)brace
macro_line|#if 0
multiline_comment|/* from asm/delay.h */
id|__delay
c_func
(paren
id|adap-&gt;mdelay
op_star
(paren
id|loops_per_sec
op_div
l_int|1000
)paren
)paren
suffix:semicolon
macro_line|#endif
)brace
r_return
id|wrcount
suffix:semicolon
)brace
DECL|function|readbytes
r_static
r_inline
r_int
id|readbytes
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
id|msg
)paren
(brace
r_int
id|inval
suffix:semicolon
r_int
id|rdcount
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* counts bytes read */
r_struct
id|i2c_algo_bit_data
op_star
id|adap
op_assign
id|i2c_adap-&gt;algo_data
suffix:semicolon
r_char
op_star
id|temp
op_assign
id|msg-&gt;buf
suffix:semicolon
r_int
id|count
op_assign
id|msg-&gt;len
suffix:semicolon
r_while
c_loop
(paren
id|count
OG
l_int|0
)paren
(brace
id|inval
op_assign
id|i2c_inb
c_func
(paren
id|i2c_adap
)paren
suffix:semicolon
multiline_comment|/*printk(&quot;%#02x &quot;,inval); if ( ! (count % 16) ) printk(&quot;&bslash;n&quot;); */
r_if
c_cond
(paren
id|inval
op_ge
l_int|0
)paren
(brace
op_star
id|temp
op_assign
id|inval
suffix:semicolon
id|rdcount
op_increment
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* read timed out */
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;i2c-algo-bit.o: readbytes: i2c_inb timed out.&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|count
OG
l_int|1
)paren
(brace
multiline_comment|/* send ack */
id|sdalo
c_func
(paren
id|adap
)paren
suffix:semicolon
id|DEBPROTO
c_func
(paren
id|printk
c_func
(paren
l_string|&quot; Am &quot;
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|sdahi
c_func
(paren
id|adap
)paren
suffix:semicolon
multiline_comment|/* neg. ack on last byte */
id|DEBPROTO
c_func
(paren
id|printk
c_func
(paren
l_string|&quot; NAm &quot;
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sclhi
c_func
(paren
id|adap
)paren
OL
l_int|0
)paren
(brace
multiline_comment|/* timeout */
id|sdahi
c_func
(paren
id|adap
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;i2c-algo-bit.o: readbytes: Timeout at ack&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ETIMEDOUT
suffix:semicolon
)brace
suffix:semicolon
id|scllo
c_func
(paren
id|adap
)paren
suffix:semicolon
id|sdahi
c_func
(paren
id|adap
)paren
suffix:semicolon
id|temp
op_increment
suffix:semicolon
id|count
op_decrement
suffix:semicolon
)brace
r_return
id|rdcount
suffix:semicolon
)brace
multiline_comment|/* doAddress initiates the transfer by generating the start condition (in&n; * try_address) and transmits the address in the necessary format to handle&n; * reads, writes as well as 10bit-addresses.&n; * returns:&n; *  0 everything went okay, the chip ack&squot;ed, or IGNORE_NAK flag was set&n; * -x an error occurred (like: -EREMOTEIO if the device did not answer, or&n; *&t;-ETIMEDOUT, for example if the lines are stuck...) &n; */
DECL|function|bit_doAddress
r_static
r_inline
r_int
id|bit_doAddress
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
id|msg
)paren
(brace
r_int
r_int
id|flags
op_assign
id|msg-&gt;flags
suffix:semicolon
r_int
r_int
id|nak_ok
op_assign
id|msg-&gt;flags
op_amp
id|I2C_M_IGNORE_NAK
suffix:semicolon
r_struct
id|i2c_algo_bit_data
op_star
id|adap
op_assign
id|i2c_adap-&gt;algo_data
suffix:semicolon
r_int
r_char
id|addr
suffix:semicolon
r_int
id|ret
comma
id|retries
suffix:semicolon
id|retries
op_assign
id|nak_ok
ques
c_cond
l_int|0
suffix:colon
id|i2c_adap-&gt;retries
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
id|i2c_adap
comma
id|addr
comma
id|retries
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_ne
l_int|1
)paren
op_logical_and
op_logical_neg
id|nak_ok
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
id|ret
op_assign
id|i2c_outb
c_func
(paren
id|i2c_adap
comma
id|msg-&gt;addr
op_amp
l_int|0x7f
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_ne
l_int|1
)paren
op_logical_and
op_logical_neg
id|nak_ok
)paren
(brace
multiline_comment|/* the chip did not ack / xmission error occurred */
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
id|i2c_adap
comma
id|addr
comma
id|retries
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_ne
l_int|1
)paren
op_logical_and
op_logical_neg
id|nak_ok
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
id|ret
op_assign
id|try_address
c_func
(paren
id|i2c_adap
comma
id|addr
comma
id|retries
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_ne
l_int|1
)paren
op_logical_and
op_logical_neg
id|nak_ok
)paren
r_return
op_minus
id|EREMOTEIO
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|bit_xfer
r_static
r_int
id|bit_xfer
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|i2c_adap
comma
r_struct
id|i2c_msg
id|msgs
(braket
)braket
comma
r_int
id|num
)paren
(brace
r_struct
id|i2c_msg
op_star
id|pmsg
suffix:semicolon
r_struct
id|i2c_algo_bit_data
op_star
id|adap
op_assign
id|i2c_adap-&gt;algo_data
suffix:semicolon
r_int
id|i
comma
id|ret
suffix:semicolon
r_int
r_int
id|nak_ok
suffix:semicolon
id|i2c_start
c_func
(paren
id|adap
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
id|nak_ok
op_assign
id|pmsg-&gt;flags
op_amp
id|I2C_M_IGNORE_NAK
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|pmsg-&gt;flags
op_amp
id|I2C_M_NOSTART
)paren
)paren
(brace
r_if
c_cond
(paren
id|i
)paren
(brace
id|i2c_repstart
c_func
(paren
id|adap
)paren
suffix:semicolon
)brace
id|ret
op_assign
id|bit_doAddress
c_func
(paren
id|i2c_adap
comma
id|pmsg
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_ne
l_int|0
)paren
op_logical_and
op_logical_neg
id|nak_ok
)paren
(brace
id|DEB2
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;i2c-algo-bit.o: NAK from device addr %2.2x msg #%d&bslash;n&quot;
comma
id|msgs
(braket
id|i
)braket
dot
id|addr
comma
id|i
)paren
)paren
suffix:semicolon
r_return
(paren
id|ret
OL
l_int|0
)paren
ques
c_cond
id|ret
suffix:colon
op_minus
id|EREMOTEIO
suffix:semicolon
)brace
)brace
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
id|readbytes
c_func
(paren
id|i2c_adap
comma
id|pmsg
)paren
suffix:semicolon
id|DEB2
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;i2c-algo-bit.o: read %d bytes.&bslash;n&quot;
comma
id|ret
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
id|pmsg-&gt;len
)paren
(brace
r_return
(paren
id|ret
OL
l_int|0
)paren
ques
c_cond
id|ret
suffix:colon
op_minus
id|EREMOTEIO
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/* write bytes from buffer */
id|ret
op_assign
id|sendbytes
c_func
(paren
id|i2c_adap
comma
id|pmsg
)paren
suffix:semicolon
id|DEB2
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;i2c-algo-bit.o: wrote %d bytes.&bslash;n&quot;
comma
id|ret
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
id|pmsg-&gt;len
)paren
(brace
r_return
(paren
id|ret
OL
l_int|0
)paren
ques
c_cond
id|ret
suffix:colon
op_minus
id|EREMOTEIO
suffix:semicolon
)brace
)brace
)brace
id|i2c_stop
c_func
(paren
id|adap
)paren
suffix:semicolon
r_return
id|num
suffix:semicolon
)brace
DECL|function|bit_func
r_static
id|u32
id|bit_func
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|adap
)paren
(brace
r_return
id|I2C_FUNC_SMBUS_EMUL
op_or
id|I2C_FUNC_10BIT_ADDR
op_or
id|I2C_FUNC_PROTOCOL_MANGLING
suffix:semicolon
)brace
multiline_comment|/* -----exported algorithm data: -------------------------------------&t;*/
DECL|variable|i2c_bit_algo
r_static
r_struct
id|i2c_algorithm
id|i2c_bit_algo
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;Bit-shift algorithm&quot;
comma
dot
id|id
op_assign
id|I2C_ALGO_BIT
comma
dot
id|master_xfer
op_assign
id|bit_xfer
comma
dot
id|functionality
op_assign
id|bit_func
comma
)brace
suffix:semicolon
multiline_comment|/* &n; * registering functions to load algorithms at runtime &n; */
DECL|function|i2c_bit_add_bus
r_int
id|i2c_bit_add_bus
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|adap
)paren
(brace
r_struct
id|i2c_algo_bit_data
op_star
id|bit_adap
op_assign
id|adap-&gt;algo_data
suffix:semicolon
r_if
c_cond
(paren
id|bit_test
)paren
(brace
r_int
id|ret
op_assign
id|test_bus
c_func
(paren
id|bit_adap
comma
id|adap-&gt;name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|DEB2
c_func
(paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;i2c-algo-bit.o: hw routines for %s registered.&bslash;n&quot;
comma
id|adap-&gt;name
)paren
)paren
suffix:semicolon
multiline_comment|/* register new adapter to i2c module... */
id|adap-&gt;id
op_or_assign
id|i2c_bit_algo.id
suffix:semicolon
id|adap-&gt;algo
op_assign
op_amp
id|i2c_bit_algo
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
id|i2c_add_adapter
c_func
(paren
id|adap
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|i2c_bit_del_bus
r_int
id|i2c_bit_del_bus
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
DECL|variable|i2c_bit_add_bus
id|EXPORT_SYMBOL
c_func
(paren
id|i2c_bit_add_bus
)paren
suffix:semicolon
DECL|variable|i2c_bit_del_bus
id|EXPORT_SYMBOL
c_func
(paren
id|i2c_bit_del_bus
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Simon G. Vogl &lt;simon@tk.uni-linz.ac.at&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;I2C-Bus bit-banging algorithm&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|bit_test
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|i2c_debug
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|bit_test
comma
l_string|&quot;Test the lines of the bus to see if it is stuck&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|i2c_debug
comma
l_string|&quot;debug level - 0 off; 1 normal; 2,3 more verbose; 9 bit-protocol&quot;
)paren
suffix:semicolon
eof
