multiline_comment|/*&n; * Linux ARCnet driver - COM20020 chipset support&n; * &n; * Written 1997 by David Woodhouse.&n; * Written 1994-1999 by Avery Pennarun.&n; * Written 1999-2000 by Martin Mares &lt;mj@ucw.cz&gt;.&n; * Derived from skeleton.c by Donald Becker.&n; *&n; * Special thanks to Contemporary Controls, Inc. (www.ccontrols.com)&n; *  for sponsoring the further development of this driver.&n; *&n; * **********************&n; *&n; * The original copyright of skeleton.c was as follows:&n; *&n; * skeleton.c Written 1993 by Donald Becker.&n; * Copyright 1993 United States Government as represented by the&n; * Director, National Security Agency.  This software may only be used&n; * and distributed according to the terms of the GNU General Public License as&n; * modified by SRC, incorporated herein by reference.&n; *&n; * **********************&n; *&n; * For more details, see drivers/net/arcnet.c&n; *&n; * **********************&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/moduleparam.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;linux/arcdevice.h&gt;
macro_line|#include &lt;linux/com20020.h&gt;
macro_line|#include &lt;asm/io.h&gt;
DECL|macro|VERSION
mdefine_line|#define VERSION &quot;arcnet: COM20020 ISA support (by David Woodhouse et al.)&bslash;n&quot;
multiline_comment|/*&n; * We cannot (yet) probe for an IO mapped card, although we can check that&n; * it&squot;s where we were told it was, and even do autoirq.&n; */
DECL|function|com20020isa_probe
r_static
r_int
id|__init
id|com20020isa_probe
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_int
id|ioaddr
suffix:semicolon
r_int
r_int
id|airqmask
suffix:semicolon
r_struct
id|arcnet_local
op_star
id|lp
op_assign
id|dev-&gt;priv
suffix:semicolon
r_int
id|err
suffix:semicolon
id|BUGLVL
c_func
(paren
id|D_NORMAL
)paren
id|printk
c_func
(paren
id|VERSION
)paren
suffix:semicolon
id|ioaddr
op_assign
id|dev-&gt;base_addr
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ioaddr
)paren
(brace
id|BUGMSG
c_func
(paren
id|D_NORMAL
comma
l_string|&quot;No autoprobe (yet) for IO mapped cards; you &quot;
l_string|&quot;must specify the base address!&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|request_region
c_func
(paren
id|ioaddr
comma
id|ARCNET_TOTAL_SIZE
comma
l_string|&quot;arcnet (COM20020)&quot;
)paren
)paren
(brace
id|BUGMSG
c_func
(paren
id|D_NORMAL
comma
l_string|&quot;IO region %xh-%xh already allocated.&bslash;n&quot;
comma
id|ioaddr
comma
id|ioaddr
op_plus
id|ARCNET_TOTAL_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ASTATUS
c_func
(paren
)paren
op_eq
l_int|0xFF
)paren
(brace
id|BUGMSG
c_func
(paren
id|D_NORMAL
comma
l_string|&quot;IO address %x empty&bslash;n&quot;
comma
id|ioaddr
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|com20020_check
c_func
(paren
id|dev
)paren
)paren
(brace
id|err
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;irq
)paren
(brace
multiline_comment|/* if we do this, we&squot;re sure to get an IRQ since the&n;&t;&t; * card has just reset and the NORXflag is on until&n;&t;&t; * we tell it to start receiving.&n;&t;&t; */
id|BUGMSG
c_func
(paren
id|D_INIT_REASONS
comma
l_string|&quot;intmask was %02Xh&bslash;n&quot;
comma
id|inb
c_func
(paren
id|_INTMASK
)paren
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0
comma
id|_INTMASK
)paren
suffix:semicolon
id|airqmask
op_assign
id|probe_irq_on
c_func
(paren
)paren
suffix:semicolon
id|outb
c_func
(paren
id|NORXflag
comma
id|_INTMASK
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0
comma
id|_INTMASK
)paren
suffix:semicolon
id|dev-&gt;irq
op_assign
id|probe_irq_off
c_func
(paren
id|airqmask
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;irq
op_le
l_int|0
)paren
(brace
id|BUGMSG
c_func
(paren
id|D_INIT_REASONS
comma
l_string|&quot;Autoprobe IRQ failed first time&bslash;n&quot;
)paren
suffix:semicolon
id|airqmask
op_assign
id|probe_irq_on
c_func
(paren
)paren
suffix:semicolon
id|outb
c_func
(paren
id|NORXflag
comma
id|_INTMASK
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|5
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0
comma
id|_INTMASK
)paren
suffix:semicolon
id|dev-&gt;irq
op_assign
id|probe_irq_off
c_func
(paren
id|airqmask
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;irq
op_le
l_int|0
)paren
(brace
id|BUGMSG
c_func
(paren
id|D_NORMAL
comma
l_string|&quot;Autoprobe IRQ failed.&bslash;n&quot;
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
)brace
)brace
id|lp-&gt;card_name
op_assign
l_string|&quot;ISA COM20020&quot;
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|com20020_found
c_func
(paren
id|dev
comma
l_int|0
)paren
)paren
op_ne
l_int|0
)paren
r_goto
id|out
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|out
suffix:colon
id|release_region
c_func
(paren
id|ioaddr
comma
id|ARCNET_TOTAL_SIZE
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|variable|node
r_static
r_int
id|node
op_assign
l_int|0
suffix:semicolon
DECL|variable|io
r_static
r_int
id|io
op_assign
l_int|0x0
suffix:semicolon
multiline_comment|/* &lt;--- EDIT THESE LINES FOR YOUR CONFIGURATION */
DECL|variable|irq
r_static
r_int
id|irq
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* or use the insmod io= irq= shmem= options */
DECL|variable|device
r_static
r_char
id|device
(braket
l_int|9
)braket
suffix:semicolon
multiline_comment|/* use eg. device=&quot;arc1&quot; to change name */
DECL|variable|timeout
r_static
r_int
id|timeout
op_assign
l_int|3
suffix:semicolon
DECL|variable|backplane
r_static
r_int
id|backplane
op_assign
l_int|0
suffix:semicolon
DECL|variable|clockp
r_static
r_int
id|clockp
op_assign
l_int|0
suffix:semicolon
DECL|variable|clockm
r_static
r_int
id|clockm
op_assign
l_int|0
suffix:semicolon
id|module_param
c_func
(paren
id|node
comma
r_int
comma
l_int|0
)paren
suffix:semicolon
id|module_param
c_func
(paren
id|io
comma
r_int
comma
l_int|0
)paren
suffix:semicolon
id|module_param
c_func
(paren
id|irq
comma
r_int
comma
l_int|0
)paren
suffix:semicolon
id|module_param_string
c_func
(paren
id|device
comma
id|device
comma
r_sizeof
(paren
id|device
)paren
comma
l_int|0
)paren
suffix:semicolon
id|module_param
c_func
(paren
id|timeout
comma
r_int
comma
l_int|0
)paren
suffix:semicolon
id|module_param
c_func
(paren
id|backplane
comma
r_int
comma
l_int|0
)paren
suffix:semicolon
id|module_param
c_func
(paren
id|clockp
comma
r_int
comma
l_int|0
)paren
suffix:semicolon
id|module_param
c_func
(paren
id|clockm
comma
r_int
comma
l_int|0
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|my_dev
r_static
r_struct
id|net_device
op_star
id|my_dev
suffix:semicolon
DECL|function|com20020_init
r_static
r_int
id|__init
id|com20020_init
c_func
(paren
r_void
)paren
(brace
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
r_struct
id|arcnet_local
op_star
id|lp
suffix:semicolon
id|dev
op_assign
id|alloc_arcdev
c_func
(paren
id|device
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
id|node
op_logical_and
id|node
op_ne
l_int|0xff
)paren
id|dev-&gt;dev_addr
(braket
l_int|0
)braket
op_assign
id|node
suffix:semicolon
id|lp
op_assign
id|dev-&gt;priv
suffix:semicolon
id|lp-&gt;backplane
op_assign
id|backplane
suffix:semicolon
id|lp-&gt;clockp
op_assign
id|clockp
op_amp
l_int|7
suffix:semicolon
id|lp-&gt;clockm
op_assign
id|clockm
op_amp
l_int|3
suffix:semicolon
id|lp-&gt;timeout
op_assign
id|timeout
op_amp
l_int|3
suffix:semicolon
id|lp-&gt;hw.owner
op_assign
id|THIS_MODULE
suffix:semicolon
id|dev-&gt;base_addr
op_assign
id|io
suffix:semicolon
id|dev-&gt;irq
op_assign
id|irq
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;irq
op_eq
l_int|2
)paren
id|dev-&gt;irq
op_assign
l_int|9
suffix:semicolon
r_if
c_cond
(paren
id|com20020isa_probe
c_func
(paren
id|dev
)paren
)paren
(brace
id|free_netdev
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|my_dev
op_assign
id|dev
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|com20020_exit
r_static
r_void
id|__exit
id|com20020_exit
c_func
(paren
r_void
)paren
(brace
id|unregister_netdev
c_func
(paren
id|my_dev
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|my_dev-&gt;irq
comma
id|my_dev
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|my_dev-&gt;base_addr
comma
id|ARCNET_TOTAL_SIZE
)paren
suffix:semicolon
id|free_netdev
c_func
(paren
id|my_dev
)paren
suffix:semicolon
)brace
macro_line|#ifndef MODULE
DECL|function|com20020isa_setup
r_static
r_int
id|__init
id|com20020isa_setup
c_func
(paren
r_char
op_star
id|s
)paren
(brace
r_int
id|ints
(braket
l_int|8
)braket
suffix:semicolon
id|s
op_assign
id|get_options
c_func
(paren
id|s
comma
l_int|8
comma
id|ints
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ints
(braket
l_int|0
)braket
)paren
r_return
l_int|1
suffix:semicolon
r_switch
c_cond
(paren
id|ints
(braket
l_int|0
)braket
)paren
(brace
r_default
suffix:colon
multiline_comment|/* ERROR */
id|printk
c_func
(paren
l_string|&quot;com90xx: Too many arguments.&bslash;n&quot;
)paren
suffix:semicolon
r_case
l_int|6
suffix:colon
multiline_comment|/* Timeout */
id|timeout
op_assign
id|ints
(braket
l_int|6
)braket
suffix:semicolon
r_case
l_int|5
suffix:colon
multiline_comment|/* CKP value */
id|clockp
op_assign
id|ints
(braket
l_int|5
)braket
suffix:semicolon
r_case
l_int|4
suffix:colon
multiline_comment|/* Backplane flag */
id|backplane
op_assign
id|ints
(braket
l_int|4
)braket
suffix:semicolon
r_case
l_int|3
suffix:colon
multiline_comment|/* Node ID */
id|node
op_assign
id|ints
(braket
l_int|3
)braket
suffix:semicolon
r_case
l_int|2
suffix:colon
multiline_comment|/* IRQ */
id|irq
op_assign
id|ints
(braket
l_int|2
)braket
suffix:semicolon
r_case
l_int|1
suffix:colon
multiline_comment|/* IO address */
id|io
op_assign
id|ints
(braket
l_int|1
)braket
suffix:semicolon
)brace
r_if
c_cond
(paren
op_star
id|s
)paren
id|snprintf
c_func
(paren
id|device
comma
r_sizeof
(paren
id|device
)paren
comma
l_string|&quot;%s&quot;
comma
id|s
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;com20020=&quot;
comma
id|com20020isa_setup
)paren
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* MODULE */
id|module_init
c_func
(paren
id|com20020_init
)paren
id|module_exit
c_func
(paren
id|com20020_exit
)paren
eof
