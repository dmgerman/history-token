multiline_comment|/* ac3200.c: A driver for the Ansel Communications EISA ethernet adaptor. */
multiline_comment|/*&n;&t;Written 1993, 1994 by Donald Becker.&n;&t;Copyright 1993 United States Government as represented by the Director,&n;&t;National Security Agency.  This software may only be used and distributed&n;&t;according to the terms of the GNU General Public License as modified by SRC,&n;&t;incorporated herein by reference.&n;&n;&t;The author may be reached as becker@scyld.com, or C/O&n;&t;Scyld Computing Corporation&n;&t;410 Severn Ave., Suite 210&n;&t;Annapolis MD 21403&n;&n;&t;This is driver for the Ansel Communications Model 3200 EISA Ethernet LAN&n;&t;Adapter.  The programming information is from the users manual, as related&n;&t;by glee@ardnassak.math.clemson.edu.&n;&n;&t;Changelog:&n;&n;&t;Paul Gortmaker 05/98&t;: add support for shared mem above 1MB.&n;&n;  */
DECL|variable|version
r_static
r_const
r_char
id|version
(braket
)braket
op_assign
l_string|&quot;ac3200.c:v1.01 7/1/94 Donald Becker (becker@cesdis.gsfc.nasa.gov)&bslash;n&quot;
suffix:semicolon
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/eisa.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/etherdevice.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &quot;8390.h&quot;
DECL|macro|DRV_NAME
mdefine_line|#define DRV_NAME&t;&quot;ac3200&quot;
multiline_comment|/* Offsets from the base address. */
DECL|macro|AC_NIC_BASE
mdefine_line|#define AC_NIC_BASE&t;0x00
DECL|macro|AC_SA_PROM
mdefine_line|#define AC_SA_PROM&t;0x16&t;&t;&t;/* The station address PROM. */
DECL|macro|AC_ADDR0
mdefine_line|#define AC_ADDR0&t;0x00&t;&t;&t;/* Prefix station address values. */
DECL|macro|AC_ADDR1
mdefine_line|#define AC_ADDR1&t;0x40&t;&t;&t;
DECL|macro|AC_ADDR2
mdefine_line|#define AC_ADDR2&t;0x90
DECL|macro|AC_ID_PORT
mdefine_line|#define AC_ID_PORT&t;0xC80
DECL|macro|AC_EISA_ID
mdefine_line|#define AC_EISA_ID&t;0x0110d305
DECL|macro|AC_RESET_PORT
mdefine_line|#define AC_RESET_PORT&t;0xC84
DECL|macro|AC_RESET
mdefine_line|#define AC_RESET&t;0x00
DECL|macro|AC_ENABLE
mdefine_line|#define AC_ENABLE&t;0x01
DECL|macro|AC_CONFIG
mdefine_line|#define AC_CONFIG&t;0xC90&t;/* The configuration port. */
DECL|macro|AC_IO_EXTENT
mdefine_line|#define AC_IO_EXTENT 0x20
multiline_comment|/* Actually accessed is:&n;&t;&t;&t;&t;&t;&t;&t;&t; * AC_NIC_BASE (0-15)&n;&t;&t;&t;&t;&t;&t;&t;&t; * AC_SA_PROM (0-5)&n;&t;&t;&t;&t;&t;&t;&t;&t; * AC_ID_PORT (0-3)&n;&t;&t;&t;&t;&t;&t;&t;&t; * AC_RESET_PORT&n;&t;&t;&t;&t;&t;&t;&t;&t; * AC_CONFIG&n;&t;&t;&t;&t;&t;&t;&t;&t; */
multiline_comment|/* Decoding of the configuration register. */
DECL|variable|__initdata
r_static
r_int
r_char
id|config2irqmap
(braket
l_int|8
)braket
id|__initdata
op_assign
(brace
l_int|15
comma
l_int|12
comma
l_int|11
comma
l_int|10
comma
l_int|9
comma
l_int|7
comma
l_int|5
comma
l_int|3
)brace
suffix:semicolon
DECL|variable|addrmap
r_static
r_int
id|addrmap
(braket
l_int|8
)braket
op_assign
(brace
l_int|0xFF0000
comma
l_int|0xFE0000
comma
l_int|0xFD0000
comma
l_int|0xFFF0000
comma
l_int|0xFFE0000
comma
l_int|0xFFC0000
comma
l_int|0xD0000
comma
l_int|0
)brace
suffix:semicolon
DECL|variable|port_name
r_static
r_const
r_char
op_star
id|port_name
(braket
l_int|4
)braket
op_assign
(brace
l_string|&quot;10baseT&quot;
comma
l_string|&quot;invalid&quot;
comma
l_string|&quot;AUI&quot;
comma
l_string|&quot;10base2&quot;
)brace
suffix:semicolon
DECL|macro|config2irq
mdefine_line|#define config2irq(configval)&t;config2irqmap[((configval) &gt;&gt; 3) &amp; 7]
DECL|macro|config2mem
mdefine_line|#define config2mem(configval)&t;addrmap[(configval) &amp; 7]
DECL|macro|config2name
mdefine_line|#define config2name(configval)&t;port_name[((configval) &gt;&gt; 6) &amp; 3]
multiline_comment|/* First and last 8390 pages. */
DECL|macro|AC_START_PG
mdefine_line|#define AC_START_PG&t;&t;0x00&t;/* First page of 8390 TX buffer */
DECL|macro|AC_STOP_PG
mdefine_line|#define AC_STOP_PG&t;&t;0x80&t;/* Last page +1 of the 8390 RX ring */
r_static
r_int
id|ac_probe1
c_func
(paren
r_int
id|ioaddr
comma
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_int
id|ac_open
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_void
id|ac_reset_8390
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_void
id|ac_block_input
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|count
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
id|ring_offset
)paren
suffix:semicolon
r_static
r_void
id|ac_block_output
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_const
r_int
id|count
comma
r_const
r_int
r_char
op_star
id|buf
comma
r_const
r_int
id|start_page
)paren
suffix:semicolon
r_static
r_void
id|ac_get_8390_hdr
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_struct
id|e8390_pkt_hdr
op_star
id|hdr
comma
r_int
id|ring_page
)paren
suffix:semicolon
r_static
r_int
id|ac_close_card
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
"&f;"
multiline_comment|/*&t;Probe for the AC3200.&n;&n;&t;The AC3200 can be identified by either the EISA configuration registers,&n;&t;or the unique value in the station address PROM.&n;&t;*/
DECL|function|do_ac3200_probe
r_static
r_int
id|__init
id|do_ac3200_probe
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_int
r_int
id|ioaddr
op_assign
id|dev-&gt;base_addr
suffix:semicolon
r_int
id|irq
op_assign
id|dev-&gt;irq
suffix:semicolon
r_int
id|mem_start
op_assign
id|dev-&gt;mem_start
suffix:semicolon
id|SET_MODULE_OWNER
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ioaddr
OG
l_int|0x1ff
)paren
multiline_comment|/* Check a single specified location. */
r_return
id|ac_probe1
c_func
(paren
id|ioaddr
comma
id|dev
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|ioaddr
OG
l_int|0
)paren
multiline_comment|/* Don&squot;t probe at all. */
r_return
op_minus
id|ENXIO
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|EISA_bus
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
r_for
c_loop
(paren
id|ioaddr
op_assign
l_int|0x1000
suffix:semicolon
id|ioaddr
OL
l_int|0x9000
suffix:semicolon
id|ioaddr
op_add_assign
l_int|0x1000
)paren
(brace
r_if
c_cond
(paren
id|ac_probe1
c_func
(paren
id|ioaddr
comma
id|dev
)paren
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|dev-&gt;irq
op_assign
id|irq
suffix:semicolon
id|dev-&gt;mem_start
op_assign
id|mem_start
suffix:semicolon
)brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
DECL|function|cleanup_card
r_static
r_void
id|cleanup_card
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
multiline_comment|/* Someday free_irq may be in ac_close_card() */
id|free_irq
c_func
(paren
id|dev-&gt;irq
comma
id|dev
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|dev-&gt;base_addr
comma
id|AC_IO_EXTENT
)paren
suffix:semicolon
id|iounmap
c_func
(paren
id|ei_status.mem
)paren
suffix:semicolon
)brace
macro_line|#ifndef MODULE
DECL|function|ac3200_probe
r_struct
id|net_device
op_star
id|__init
id|ac3200_probe
c_func
(paren
r_int
id|unit
)paren
(brace
r_struct
id|net_device
op_star
id|dev
op_assign
id|alloc_ei_netdev
c_func
(paren
)paren
suffix:semicolon
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|ENOMEM
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|dev-&gt;name
comma
l_string|&quot;eth%d&quot;
comma
id|unit
)paren
suffix:semicolon
id|netdev_boot_setup_check
c_func
(paren
id|dev
)paren
suffix:semicolon
id|err
op_assign
id|do_ac3200_probe
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|out
suffix:semicolon
id|err
op_assign
id|register_netdev
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|out1
suffix:semicolon
r_return
id|dev
suffix:semicolon
id|out1
suffix:colon
id|cleanup_card
c_func
(paren
id|dev
)paren
suffix:semicolon
id|out
suffix:colon
id|free_netdev
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
id|ERR_PTR
c_func
(paren
id|err
)paren
suffix:semicolon
)brace
macro_line|#endif
DECL|function|ac_probe1
r_static
r_int
id|__init
id|ac_probe1
c_func
(paren
r_int
id|ioaddr
comma
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_int
id|i
comma
id|retval
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|request_region
c_func
(paren
id|ioaddr
comma
id|AC_IO_EXTENT
comma
id|DRV_NAME
)paren
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
r_if
c_cond
(paren
id|inb_p
c_func
(paren
id|ioaddr
op_plus
id|AC_ID_PORT
)paren
op_eq
l_int|0xff
)paren
(brace
id|retval
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
id|inl
c_func
(paren
id|ioaddr
op_plus
id|AC_ID_PORT
)paren
op_ne
id|AC_EISA_ID
)paren
(brace
id|retval
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
macro_line|#ifndef final_version
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;AC3200 ethercard configuration register is %#02x,&quot;
l_string|&quot; EISA ID %02x %02x %02x %02x.&bslash;n&quot;
comma
id|inb
c_func
(paren
id|ioaddr
op_plus
id|AC_CONFIG
)paren
comma
id|inb
c_func
(paren
id|ioaddr
op_plus
id|AC_ID_PORT
op_plus
l_int|0
)paren
comma
id|inb
c_func
(paren
id|ioaddr
op_plus
id|AC_ID_PORT
op_plus
l_int|1
)paren
comma
id|inb
c_func
(paren
id|ioaddr
op_plus
id|AC_ID_PORT
op_plus
l_int|2
)paren
comma
id|inb
c_func
(paren
id|ioaddr
op_plus
id|AC_ID_PORT
op_plus
l_int|3
)paren
)paren
suffix:semicolon
macro_line|#endif
id|printk
c_func
(paren
l_string|&quot;AC3200 in EISA slot %d, node&quot;
comma
id|ioaddr
op_div
l_int|0x1000
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
l_int|6
suffix:semicolon
id|i
op_increment
)paren
(brace
id|printk
c_func
(paren
l_string|&quot; %02x&quot;
comma
id|dev-&gt;dev_addr
(braket
id|i
)braket
op_assign
id|inb
c_func
(paren
id|ioaddr
op_plus
id|AC_SA_PROM
op_plus
id|i
)paren
)paren
suffix:semicolon
)brace
macro_line|#if 0
multiline_comment|/* Check the vendor ID/prefix. Redundant after checking the EISA ID */
r_if
c_cond
(paren
id|inb
c_func
(paren
id|ioaddr
op_plus
id|AC_SA_PROM
op_plus
l_int|0
)paren
op_ne
id|AC_ADDR0
op_logical_or
id|inb
c_func
(paren
id|ioaddr
op_plus
id|AC_SA_PROM
op_plus
l_int|1
)paren
op_ne
id|AC_ADDR1
op_logical_or
id|inb
c_func
(paren
id|ioaddr
op_plus
id|AC_SA_PROM
op_plus
l_int|2
)paren
op_ne
id|AC_ADDR2
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;, not found (invalid prefix).&bslash;n&quot;
)paren
suffix:semicolon
id|retval
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* Assign and allocate the interrupt now. */
r_if
c_cond
(paren
id|dev-&gt;irq
op_eq
l_int|0
)paren
(brace
id|dev-&gt;irq
op_assign
id|config2irq
c_func
(paren
id|inb
c_func
(paren
id|ioaddr
op_plus
id|AC_CONFIG
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;, using&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|dev-&gt;irq
op_assign
id|irq_canonicalize
c_func
(paren
id|dev-&gt;irq
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;, assigning&quot;
)paren
suffix:semicolon
)brace
id|retval
op_assign
id|request_irq
c_func
(paren
id|dev-&gt;irq
comma
id|ei_interrupt
comma
l_int|0
comma
id|DRV_NAME
comma
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
(brace
id|printk
(paren
l_string|&quot; nothing! Unable to get IRQ %d.&bslash;n&quot;
comma
id|dev-&gt;irq
)paren
suffix:semicolon
r_goto
id|out1
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot; IRQ %d, %s port&bslash;n&quot;
comma
id|dev-&gt;irq
comma
id|port_name
(braket
id|dev-&gt;if_port
)braket
)paren
suffix:semicolon
id|dev-&gt;base_addr
op_assign
id|ioaddr
suffix:semicolon
macro_line|#ifdef notyet
r_if
c_cond
(paren
id|dev-&gt;mem_start
)paren
(brace
multiline_comment|/* Override the value from the board. */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|7
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|addrmap
(braket
id|i
)braket
op_eq
id|dev-&gt;mem_start
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ge
l_int|7
)paren
id|i
op_assign
l_int|0
suffix:semicolon
id|outb
c_func
(paren
(paren
id|inb
c_func
(paren
id|ioaddr
op_plus
id|AC_CONFIG
)paren
op_amp
op_complement
l_int|7
)paren
op_or
id|i
comma
id|ioaddr
op_plus
id|AC_CONFIG
)paren
suffix:semicolon
)brace
macro_line|#endif
id|dev-&gt;if_port
op_assign
id|inb
c_func
(paren
id|ioaddr
op_plus
id|AC_CONFIG
)paren
op_rshift
l_int|6
suffix:semicolon
id|dev-&gt;mem_start
op_assign
id|config2mem
c_func
(paren
id|inb
c_func
(paren
id|ioaddr
op_plus
id|AC_CONFIG
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s: AC3200 at %#3x with %dkB memory at physical address %#lx.&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|ioaddr
comma
id|AC_STOP_PG
op_div
l_int|4
comma
id|dev-&gt;mem_start
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *  BEWARE!! Some dain-bramaged EISA SCUs will allow you to put&n;&t; *  the card mem within the region covered by `normal&squot; RAM  !!!&n;&t; *&n;&t; *  ioremap() will fail in that case.&n;&t; */
id|ei_status.mem
op_assign
id|ioremap
c_func
(paren
id|dev-&gt;mem_start
comma
id|AC_STOP_PG
op_star
l_int|0x100
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ei_status.mem
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;ac3200.c: Unable to remap card memory above 1MB !!&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;ac3200.c: Try using EISA SCU to set memory below 1MB.&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;ac3200.c: Driver NOT installed.&bslash;n&quot;
)paren
suffix:semicolon
id|retval
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|out1
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;ac3200.c: remapped %dkB card memory to virtual address %p&bslash;n&quot;
comma
id|AC_STOP_PG
op_div
l_int|4
comma
id|ei_status.mem
)paren
suffix:semicolon
id|dev-&gt;mem_start
op_assign
(paren
r_int
r_int
)paren
id|ei_status.mem
suffix:semicolon
id|dev-&gt;mem_end
op_assign
id|dev-&gt;mem_start
op_plus
(paren
id|AC_STOP_PG
op_minus
id|AC_START_PG
)paren
op_star
l_int|256
suffix:semicolon
id|ei_status.name
op_assign
l_string|&quot;AC3200&quot;
suffix:semicolon
id|ei_status.tx_start_page
op_assign
id|AC_START_PG
suffix:semicolon
id|ei_status.rx_start_page
op_assign
id|AC_START_PG
op_plus
id|TX_PAGES
suffix:semicolon
id|ei_status.stop_page
op_assign
id|AC_STOP_PG
suffix:semicolon
id|ei_status.word16
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|ei_debug
OG
l_int|0
)paren
id|printk
c_func
(paren
id|version
)paren
suffix:semicolon
id|ei_status.reset_8390
op_assign
op_amp
id|ac_reset_8390
suffix:semicolon
id|ei_status.block_input
op_assign
op_amp
id|ac_block_input
suffix:semicolon
id|ei_status.block_output
op_assign
op_amp
id|ac_block_output
suffix:semicolon
id|ei_status.get_8390_hdr
op_assign
op_amp
id|ac_get_8390_hdr
suffix:semicolon
id|dev-&gt;open
op_assign
op_amp
id|ac_open
suffix:semicolon
id|dev-&gt;stop
op_assign
op_amp
id|ac_close_card
suffix:semicolon
macro_line|#ifdef CONFIG_NET_POLL_CONTROLLER
id|dev-&gt;poll_controller
op_assign
id|ei_poll
suffix:semicolon
macro_line|#endif
id|NS8390_init
c_func
(paren
id|dev
comma
l_int|0
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|out1
suffix:colon
id|free_irq
c_func
(paren
id|dev-&gt;irq
comma
id|dev
)paren
suffix:semicolon
id|out
suffix:colon
id|release_region
c_func
(paren
id|ioaddr
comma
id|AC_IO_EXTENT
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|ac_open
r_static
r_int
id|ac_open
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
macro_line|#ifdef notyet
multiline_comment|/* Someday we may enable the IRQ and shared memory here. */
r_int
id|ioaddr
op_assign
id|dev-&gt;base_addr
suffix:semicolon
macro_line|#endif
id|ei_open
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ac_reset_8390
r_static
r_void
id|ac_reset_8390
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
id|ushort
id|ioaddr
op_assign
id|dev-&gt;base_addr
suffix:semicolon
id|outb
c_func
(paren
id|AC_RESET
comma
id|ioaddr
op_plus
id|AC_RESET_PORT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ei_debug
OG
l_int|1
)paren
id|printk
c_func
(paren
l_string|&quot;resetting AC3200, t=%ld...&quot;
comma
id|jiffies
)paren
suffix:semicolon
id|ei_status.txing
op_assign
l_int|0
suffix:semicolon
id|outb
c_func
(paren
id|AC_ENABLE
comma
id|ioaddr
op_plus
id|AC_RESET_PORT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ei_debug
OG
l_int|1
)paren
id|printk
c_func
(paren
l_string|&quot;reset done&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Grab the 8390 specific header. Similar to the block_input routine, but&n;   we don&squot;t need to be concerned with ring wrap as the header will be at&n;   the start of a page, so we optimize accordingly. */
r_static
r_void
DECL|function|ac_get_8390_hdr
id|ac_get_8390_hdr
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_struct
id|e8390_pkt_hdr
op_star
id|hdr
comma
r_int
id|ring_page
)paren
(brace
r_void
id|__iomem
op_star
id|hdr_start
op_assign
id|ei_status.mem
op_plus
(paren
(paren
id|ring_page
op_minus
id|AC_START_PG
)paren
op_lshift
l_int|8
)paren
suffix:semicolon
id|memcpy_fromio
c_func
(paren
id|hdr
comma
id|hdr_start
comma
r_sizeof
(paren
r_struct
id|e8390_pkt_hdr
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*  Block input and output are easy on shared memory ethercards, the only&n;&t;complication is when the ring buffer wraps. */
DECL|function|ac_block_input
r_static
r_void
id|ac_block_input
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|count
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
id|ring_offset
)paren
(brace
r_void
id|__iomem
op_star
id|start
op_assign
id|ei_status.mem
op_plus
id|ring_offset
op_minus
id|AC_START_PG
op_star
l_int|256
suffix:semicolon
r_if
c_cond
(paren
id|ring_offset
op_plus
id|count
OG
id|AC_STOP_PG
op_star
l_int|256
)paren
(brace
multiline_comment|/* We must wrap the input move. */
r_int
id|semi_count
op_assign
id|AC_STOP_PG
op_star
l_int|256
op_minus
id|ring_offset
suffix:semicolon
id|memcpy_fromio
c_func
(paren
id|skb-&gt;data
comma
id|start
comma
id|semi_count
)paren
suffix:semicolon
id|count
op_sub_assign
id|semi_count
suffix:semicolon
id|memcpy_fromio
c_func
(paren
id|skb-&gt;data
op_plus
id|semi_count
comma
id|ei_status.mem
op_plus
id|TX_PAGES
op_star
l_int|256
comma
id|count
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Packet is in one chunk -- we can copy + cksum. */
id|eth_io_copy_and_sum
c_func
(paren
id|skb
comma
id|start
comma
id|count
comma
l_int|0
)paren
suffix:semicolon
)brace
)brace
DECL|function|ac_block_output
r_static
r_void
id|ac_block_output
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|count
comma
r_const
r_int
r_char
op_star
id|buf
comma
r_int
id|start_page
)paren
(brace
r_void
id|__iomem
op_star
id|shmem
op_assign
id|ei_status.mem
op_plus
(paren
(paren
id|start_page
op_minus
id|AC_START_PG
)paren
op_lshift
l_int|8
)paren
suffix:semicolon
id|memcpy_toio
c_func
(paren
id|shmem
comma
id|buf
comma
id|count
)paren
suffix:semicolon
)brace
DECL|function|ac_close_card
r_static
r_int
id|ac_close_card
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_if
c_cond
(paren
id|ei_debug
OG
l_int|1
)paren
id|printk
c_func
(paren
l_string|&quot;%s: Shutting down ethercard.&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
macro_line|#ifdef notyet
multiline_comment|/* We should someday disable shared memory and interrupts. */
id|outb
c_func
(paren
l_int|0x00
comma
id|ioaddr
op_plus
l_int|6
)paren
suffix:semicolon
multiline_comment|/* Disable interrupts. */
id|free_irq
c_func
(paren
id|dev-&gt;irq
comma
id|dev
)paren
suffix:semicolon
macro_line|#endif
id|ei_close
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef MODULE
DECL|macro|MAX_AC32_CARDS
mdefine_line|#define MAX_AC32_CARDS&t;4&t;/* Max number of AC32 cards per module */
DECL|variable|dev_ac32
r_static
r_struct
id|net_device
op_star
id|dev_ac32
(braket
id|MAX_AC32_CARDS
)braket
suffix:semicolon
DECL|variable|io
r_static
r_int
id|io
(braket
id|MAX_AC32_CARDS
)braket
suffix:semicolon
DECL|variable|irq
r_static
r_int
id|irq
(braket
id|MAX_AC32_CARDS
)braket
suffix:semicolon
DECL|variable|mem
r_static
r_int
id|mem
(braket
id|MAX_AC32_CARDS
)braket
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|io
comma
l_string|&quot;1-&quot;
id|__MODULE_STRING
c_func
(paren
id|MAX_AC32_CARDS
)paren
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|irq
comma
l_string|&quot;1-&quot;
id|__MODULE_STRING
c_func
(paren
id|MAX_AC32_CARDS
)paren
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|mem
comma
l_string|&quot;1-&quot;
id|__MODULE_STRING
c_func
(paren
id|MAX_AC32_CARDS
)paren
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|io
comma
l_string|&quot;I/O base address(es)&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|irq
comma
l_string|&quot;IRQ number(s)&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|mem
comma
l_string|&quot;Memory base address(es)&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Ansel AC3200 EISA ethernet driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
r_int
DECL|function|init_module
id|init_module
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
r_int
id|this_dev
comma
id|found
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|this_dev
op_assign
l_int|0
suffix:semicolon
id|this_dev
OL
id|MAX_AC32_CARDS
suffix:semicolon
id|this_dev
op_increment
)paren
(brace
r_if
c_cond
(paren
id|io
(braket
id|this_dev
)braket
op_eq
l_int|0
op_logical_and
id|this_dev
op_ne
l_int|0
)paren
r_break
suffix:semicolon
id|dev
op_assign
id|alloc_ei_netdev
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
r_break
suffix:semicolon
id|dev-&gt;irq
op_assign
id|irq
(braket
id|this_dev
)braket
suffix:semicolon
id|dev-&gt;base_addr
op_assign
id|io
(braket
id|this_dev
)braket
suffix:semicolon
id|dev-&gt;mem_start
op_assign
id|mem
(braket
id|this_dev
)braket
suffix:semicolon
multiline_comment|/* Currently ignored by driver */
r_if
c_cond
(paren
id|do_ac3200_probe
c_func
(paren
id|dev
)paren
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|register_netdev
c_func
(paren
id|dev
)paren
op_eq
l_int|0
)paren
(brace
id|dev_ac32
(braket
id|found
op_increment
)braket
op_assign
id|dev
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|cleanup_card
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
id|free_netdev
c_func
(paren
id|dev
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;ac3200.c: No ac3200 card found (i/o = 0x%x).&bslash;n&quot;
comma
id|io
(braket
id|this_dev
)braket
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|found
)paren
r_return
l_int|0
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
r_void
DECL|function|cleanup_module
id|cleanup_module
c_func
(paren
r_void
)paren
(brace
r_int
id|this_dev
suffix:semicolon
r_for
c_loop
(paren
id|this_dev
op_assign
l_int|0
suffix:semicolon
id|this_dev
OL
id|MAX_AC32_CARDS
suffix:semicolon
id|this_dev
op_increment
)paren
(brace
r_struct
id|net_device
op_star
id|dev
op_assign
id|dev_ac32
(braket
id|this_dev
)braket
suffix:semicolon
r_if
c_cond
(paren
id|dev
)paren
(brace
id|unregister_netdev
c_func
(paren
id|dev
)paren
suffix:semicolon
id|cleanup_card
c_func
(paren
id|dev
)paren
suffix:semicolon
id|free_netdev
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
)brace
)brace
macro_line|#endif /* MODULE */
eof
