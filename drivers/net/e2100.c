multiline_comment|/* e2100.c: A Cabletron E2100 series ethernet driver for linux. */
multiline_comment|/*&n;&t;Written 1993-1994 by Donald Becker.&n;&n;&t;Copyright 1994 by Donald Becker.&n;&t;Copyright 1993 United States Government as represented by the&n;&t;Director, National Security Agency.  This software may be used and&n;&t;distributed according to the terms of the GNU General Public License,&n;&t;incorporated herein by reference.&n;&n;&t;This is a driver for the Cabletron E2100 series ethercards.&n;&n;&t;The Author may be reached as becker@scyld.com, or C/O&n;&t;Scyld Computing Corporation&n;&t;410 Severn Ave., Suite 210&n;&t;Annapolis MD 21403&n;&n;&t;The E2100 series ethercard is a fairly generic shared memory 8390&n;&t;implementation.  The only unusual aspect is the way the shared memory&n;&t;registers are set: first you do an inb() in what is normally the&n;&t;station address region, and the low three bits of next outb() *address*&n;&t;is used&t;as the write value for that register.  Either someone wasn&squot;t&n;&t;too used to dem bit en bites, or they were trying to obfuscate the&n;&t;programming interface.&n;&n;&t;There is an additional complication when setting the window on the packet&n;&t;buffer.  You must first do a read into the packet buffer region with the&n;&t;low 8 address bits the address setting the page for the start of the packet&n;&t;buffer window, and then do the above operation.  See mem_on() for details.&n;&n;&t;One bug on the chip is that even a hard reset won&squot;t disable the memory&n;&t;window, usually resulting in a hung machine if mem_off() isn&squot;t called.&n;&t;If this happens, you must power down the machine for about 30 seconds.&n;*/
DECL|variable|version
r_static
r_const
r_char
id|version
(braket
)braket
op_assign
l_string|&quot;e2100.c:v1.01 7/21/94 Donald Becker (becker@cesdis.gsfc.nasa.gov)&bslash;n&quot;
suffix:semicolon
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/etherdevice.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &quot;8390.h&quot;
DECL|variable|e21_probe_list
r_static
r_int
id|e21_probe_list
(braket
)braket
op_assign
(brace
l_int|0x300
comma
l_int|0x280
comma
l_int|0x380
comma
l_int|0x220
comma
l_int|0
)brace
suffix:semicolon
multiline_comment|/* Offsets from the base_addr.&n;   Read from the ASIC register, and the low three bits of the next outb()&n;   address is used to set the corresponding register. */
DECL|macro|E21_NIC_OFFSET
mdefine_line|#define E21_NIC_OFFSET  0&t;&t;/* Offset to the 8390 NIC. */
DECL|macro|E21_ASIC
mdefine_line|#define E21_ASIC&t;&t;0x10
DECL|macro|E21_MEM_ENABLE
mdefine_line|#define E21_MEM_ENABLE&t;0x10
DECL|macro|E21_MEM_ON
mdefine_line|#define  E21_MEM_ON&t;&t;0x05&t;/* Enable memory in 16 bit mode. */
DECL|macro|E21_MEM_ON_8
mdefine_line|#define  E21_MEM_ON_8&t;0x07&t;/* Enable memory in  8 bit mode. */
DECL|macro|E21_MEM_BASE
mdefine_line|#define E21_MEM_BASE&t;0x11
DECL|macro|E21_IRQ_LOW
mdefine_line|#define E21_IRQ_LOW&t;&t;0x12&t;/* The low three bits of the IRQ number. */
DECL|macro|E21_IRQ_HIGH
mdefine_line|#define E21_IRQ_HIGH&t;0x14&t;/* The high IRQ bit and media select ...  */
DECL|macro|E21_MEDIA
mdefine_line|#define E21_MEDIA&t;&t;0x14&t;/* (alias). */
DECL|macro|E21_ALT_IFPORT
mdefine_line|#define  E21_ALT_IFPORT 0x02&t;/* Set to use the other (BNC,AUI) port. */
DECL|macro|E21_BIG_MEM
mdefine_line|#define  E21_BIG_MEM&t;0x04&t;/* Use a bigger (64K) buffer (we don&squot;t) */
DECL|macro|E21_SAPROM
mdefine_line|#define E21_SAPROM&t;&t;0x10&t;/* Offset to station address data. */
DECL|macro|E21_IO_EXTENT
mdefine_line|#define E21_IO_EXTENT&t; 0x20
DECL|function|mem_on
r_static
r_inline
r_void
id|mem_on
c_func
(paren
r_int
id|port
comma
r_volatile
r_char
op_star
id|mem_base
comma
r_int
r_char
id|start_page
)paren
(brace
multiline_comment|/* This is a little weird: set the shared memory window by doing a&n;&t;   read.  The low address bits specify the starting page. */
id|readb
c_func
(paren
id|mem_base
op_plus
id|start_page
)paren
suffix:semicolon
id|inb
c_func
(paren
id|port
op_plus
id|E21_MEM_ENABLE
)paren
suffix:semicolon
id|outb
c_func
(paren
id|E21_MEM_ON
comma
id|port
op_plus
id|E21_MEM_ENABLE
op_plus
id|E21_MEM_ON
)paren
suffix:semicolon
)brace
DECL|function|mem_off
r_static
r_inline
r_void
id|mem_off
c_func
(paren
r_int
id|port
)paren
(brace
id|inb
c_func
(paren
id|port
op_plus
id|E21_MEM_ENABLE
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x00
comma
id|port
op_plus
id|E21_MEM_ENABLE
)paren
suffix:semicolon
)brace
multiline_comment|/* In other drivers I put the TX pages first, but the E2100 window circuitry&n;   is designed to have a 4K Tx region last. The windowing circuitry wraps the&n;   window at 0x2fff-&gt;0x0000 so that the packets at e.g. 0x2f00 in the RX ring&n;   appear contiguously in the window. */
DECL|macro|E21_RX_START_PG
mdefine_line|#define E21_RX_START_PG&t;&t;0x00&t;/* First page of RX buffer */
DECL|macro|E21_RX_STOP_PG
mdefine_line|#define E21_RX_STOP_PG&t;&t;0x30&t;/* Last page +1 of RX ring */
DECL|macro|E21_BIG_RX_STOP_PG
mdefine_line|#define E21_BIG_RX_STOP_PG&t;0xF0&t;/* Last page +1 of RX ring */
DECL|macro|E21_TX_START_PG
mdefine_line|#define E21_TX_START_PG&t;&t;E21_RX_STOP_PG&t;/* First page of TX buffer */
r_static
r_int
id|e21_probe1
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|ioaddr
)paren
suffix:semicolon
r_static
r_int
id|e21_open
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
id|e21_reset_8390
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
id|e21_block_input
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
id|e21_block_output
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
suffix:semicolon
r_static
r_void
id|e21_get_8390_hdr
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
id|e21_close
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
"&f;"
multiline_comment|/*  Probe for the E2100 series ethercards.  These cards have an 8390 at the&n;&t;base address and the station address at both offset 0x10 and 0x18.  I read&n;&t;the station address from offset 0x18 to avoid the dataport of NE2000&n;&t;ethercards, and look for Ctron&squot;s unique ID (first three octets of the&n;&t;station address).&n; */
DECL|function|do_e2100_probe
r_static
r_int
id|__init
id|do_e2100_probe
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_int
op_star
id|port
suffix:semicolon
r_int
id|base_addr
op_assign
id|dev-&gt;base_addr
suffix:semicolon
r_int
id|irq
op_assign
id|dev-&gt;irq
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
id|base_addr
OG
l_int|0x1ff
)paren
multiline_comment|/* Check a single specified location. */
r_return
id|e21_probe1
c_func
(paren
id|dev
comma
id|base_addr
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|base_addr
op_ne
l_int|0
)paren
multiline_comment|/* Don&squot;t probe at all. */
r_return
op_minus
id|ENXIO
suffix:semicolon
r_for
c_loop
(paren
id|port
op_assign
id|e21_probe_list
suffix:semicolon
op_star
id|port
suffix:semicolon
id|port
op_increment
)paren
(brace
id|dev-&gt;irq
op_assign
id|irq
suffix:semicolon
r_if
c_cond
(paren
id|e21_probe1
c_func
(paren
id|dev
comma
op_star
id|port
)paren
op_eq
l_int|0
)paren
r_return
l_int|0
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
r_void
op_star
id|priv
op_assign
id|dev-&gt;priv
suffix:semicolon
multiline_comment|/* NB: e21_close() handles free_irq */
id|release_region
c_func
(paren
id|dev-&gt;base_addr
comma
id|E21_IO_EXTENT
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|priv
)paren
suffix:semicolon
)brace
DECL|function|e2100_probe
r_struct
id|net_device
op_star
id|__init
id|e2100_probe
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
id|alloc_etherdev
c_func
(paren
l_int|0
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
id|dev-&gt;priv
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* until all 8390-based use alloc_etherdev() */
id|err
op_assign
id|do_e2100_probe
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
DECL|function|e21_probe1
r_static
r_int
id|__init
id|e21_probe1
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|ioaddr
)paren
(brace
r_int
id|i
comma
id|status
comma
id|retval
suffix:semicolon
r_int
r_char
op_star
id|station_addr
op_assign
id|dev-&gt;dev_addr
suffix:semicolon
r_static
r_int
id|version_printed
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
id|E21_IO_EXTENT
comma
id|dev-&gt;name
)paren
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
multiline_comment|/* First check the station address for the Ctron prefix. */
r_if
c_cond
(paren
id|inb
c_func
(paren
id|ioaddr
op_plus
id|E21_SAPROM
op_plus
l_int|0
)paren
op_ne
l_int|0x00
op_logical_or
id|inb
c_func
(paren
id|ioaddr
op_plus
id|E21_SAPROM
op_plus
l_int|1
)paren
op_ne
l_int|0x00
op_logical_or
id|inb
c_func
(paren
id|ioaddr
op_plus
id|E21_SAPROM
op_plus
l_int|2
)paren
op_ne
l_int|0x1d
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
multiline_comment|/* Verify by making certain that there is a 8390 at there. */
id|outb
c_func
(paren
id|E8390_NODMA
op_plus
id|E8390_STOP
comma
id|ioaddr
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
multiline_comment|/* we want to delay one I/O cycle - which is 2MHz */
id|status
op_assign
id|inb
c_func
(paren
id|ioaddr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_ne
l_int|0x21
op_logical_and
id|status
op_ne
l_int|0x23
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
multiline_comment|/* Read the station address PROM.  */
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
id|station_addr
(braket
id|i
)braket
op_assign
id|inb
c_func
(paren
id|ioaddr
op_plus
id|E21_SAPROM
op_plus
id|i
)paren
suffix:semicolon
id|inb
c_func
(paren
id|ioaddr
op_plus
id|E21_MEDIA
)paren
suffix:semicolon
multiline_comment|/* Point to media selection. */
id|outb
c_func
(paren
l_int|0
comma
id|ioaddr
op_plus
id|E21_ASIC
)paren
suffix:semicolon
multiline_comment|/* and disable the secondary interface. */
r_if
c_cond
(paren
id|ei_debug
op_logical_and
id|version_printed
op_increment
op_eq
l_int|0
)paren
id|printk
c_func
(paren
id|version
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
id|printk
c_func
(paren
l_string|&quot; %02X&quot;
comma
id|station_addr
(braket
id|i
)braket
)paren
suffix:semicolon
multiline_comment|/* Allocate dev-&gt;priv and fill in 8390 specific dev fields. */
r_if
c_cond
(paren
id|ethdev_init
c_func
(paren
id|dev
)paren
)paren
(brace
id|printk
(paren
l_string|&quot; unable to get memory for dev-&gt;priv.&bslash;n&quot;
)paren
suffix:semicolon
id|retval
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dev-&gt;irq
OL
l_int|2
)paren
(brace
r_int
id|irqlist
(braket
)braket
op_assign
(brace
l_int|15
comma
l_int|11
comma
l_int|10
comma
l_int|12
comma
l_int|5
comma
l_int|9
comma
l_int|3
comma
l_int|4
)brace
comma
id|i
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
r_if
c_cond
(paren
id|request_irq
(paren
id|irqlist
(braket
id|i
)braket
comma
l_int|NULL
comma
l_int|0
comma
l_string|&quot;bogus&quot;
comma
l_int|NULL
)paren
op_ne
op_minus
id|EBUSY
)paren
(brace
id|dev-&gt;irq
op_assign
id|irqlist
(braket
id|i
)braket
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
op_ge
l_int|8
)paren
(brace
id|printk
c_func
(paren
l_string|&quot; unable to get IRQ %d.&bslash;n&quot;
comma
id|dev-&gt;irq
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|dev-&gt;priv
)paren
suffix:semicolon
id|dev-&gt;priv
op_assign
l_int|NULL
suffix:semicolon
id|retval
op_assign
op_minus
id|EAGAIN
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|dev-&gt;irq
op_eq
l_int|2
)paren
multiline_comment|/* Fixup luser bogosity: IRQ2 is really IRQ9 */
id|dev-&gt;irq
op_assign
l_int|9
suffix:semicolon
multiline_comment|/* The 8390 is at the base address. */
id|dev-&gt;base_addr
op_assign
id|ioaddr
suffix:semicolon
id|ei_status.name
op_assign
l_string|&quot;E2100&quot;
suffix:semicolon
id|ei_status.word16
op_assign
l_int|1
suffix:semicolon
id|ei_status.tx_start_page
op_assign
id|E21_TX_START_PG
suffix:semicolon
id|ei_status.rx_start_page
op_assign
id|E21_RX_START_PG
suffix:semicolon
id|ei_status.stop_page
op_assign
id|E21_RX_STOP_PG
suffix:semicolon
id|ei_status.saved_irq
op_assign
id|dev-&gt;irq
suffix:semicolon
multiline_comment|/* Check the media port used.  The port can be passed in on the&n;&t;   low mem_end bits. */
r_if
c_cond
(paren
id|dev-&gt;mem_end
op_amp
l_int|15
)paren
id|dev-&gt;if_port
op_assign
id|dev-&gt;mem_end
op_amp
l_int|7
suffix:semicolon
r_else
(brace
id|dev-&gt;if_port
op_assign
l_int|0
suffix:semicolon
id|inb
c_func
(paren
id|ioaddr
op_plus
id|E21_MEDIA
)paren
suffix:semicolon
multiline_comment|/* Turn automatic media detection on. */
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
r_if
c_cond
(paren
id|station_addr
(braket
id|i
)braket
op_ne
id|inb
c_func
(paren
id|ioaddr
op_plus
id|E21_SAPROM
op_plus
l_int|8
op_plus
id|i
)paren
)paren
(brace
id|dev-&gt;if_port
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/* Never map in the E21 shared memory unless you are actively using it.&n;&t;   Also, the shared memory has effective only one setting -- spread all&n;&t;   over the 128K region! */
r_if
c_cond
(paren
id|dev-&gt;mem_start
op_eq
l_int|0
)paren
id|dev-&gt;mem_start
op_assign
l_int|0xd0000
suffix:semicolon
macro_line|#ifdef notdef
multiline_comment|/* These values are unused.  The E2100 has a 2K window into the packet&n;&t;   buffer.  The window can be set to start on any page boundary. */
id|ei_status.rmem_start
op_assign
id|dev-&gt;mem_start
op_plus
id|TX_PAGES
op_star
l_int|256
suffix:semicolon
id|dev-&gt;mem_end
op_assign
id|ei_status.rmem_end
op_assign
id|dev-&gt;mem_start
op_plus
l_int|2
op_star
l_int|1024
suffix:semicolon
macro_line|#endif
id|printk
c_func
(paren
l_string|&quot;, IRQ %d, %s media, memory @ %#lx.&bslash;n&quot;
comma
id|dev-&gt;irq
comma
id|dev-&gt;if_port
ques
c_cond
l_string|&quot;secondary&quot;
suffix:colon
l_string|&quot;primary&quot;
comma
id|dev-&gt;mem_start
)paren
suffix:semicolon
id|ei_status.reset_8390
op_assign
op_amp
id|e21_reset_8390
suffix:semicolon
id|ei_status.block_input
op_assign
op_amp
id|e21_block_input
suffix:semicolon
id|ei_status.block_output
op_assign
op_amp
id|e21_block_output
suffix:semicolon
id|ei_status.get_8390_hdr
op_assign
op_amp
id|e21_get_8390_hdr
suffix:semicolon
id|dev-&gt;open
op_assign
op_amp
id|e21_open
suffix:semicolon
id|dev-&gt;stop
op_assign
op_amp
id|e21_close
suffix:semicolon
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
id|out
suffix:colon
id|release_region
c_func
(paren
id|ioaddr
comma
id|E21_IO_EXTENT
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
r_static
r_int
DECL|function|e21_open
id|e21_open
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
op_assign
id|dev-&gt;base_addr
suffix:semicolon
r_int
id|retval
suffix:semicolon
r_if
c_cond
(paren
(paren
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
id|dev-&gt;name
comma
id|dev
)paren
)paren
)paren
r_return
id|retval
suffix:semicolon
multiline_comment|/* Set the interrupt line and memory base on the hardware. */
id|inb
c_func
(paren
id|ioaddr
op_plus
id|E21_IRQ_LOW
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0
comma
id|ioaddr
op_plus
id|E21_ASIC
op_plus
(paren
id|dev-&gt;irq
op_amp
l_int|7
)paren
)paren
suffix:semicolon
id|inb
c_func
(paren
id|ioaddr
op_plus
id|E21_IRQ_HIGH
)paren
suffix:semicolon
multiline_comment|/* High IRQ bit, and if_port. */
id|outb
c_func
(paren
l_int|0
comma
id|ioaddr
op_plus
id|E21_ASIC
op_plus
(paren
id|dev-&gt;irq
OG
l_int|7
ques
c_cond
l_int|1
suffix:colon
l_int|0
)paren
op_plus
(paren
id|dev-&gt;if_port
ques
c_cond
id|E21_ALT_IFPORT
suffix:colon
l_int|0
)paren
)paren
suffix:semicolon
id|inb
c_func
(paren
id|ioaddr
op_plus
id|E21_MEM_BASE
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0
comma
id|ioaddr
op_plus
id|E21_ASIC
op_plus
(paren
(paren
id|dev-&gt;mem_start
op_rshift
l_int|17
)paren
op_amp
l_int|7
)paren
)paren
suffix:semicolon
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
r_static
r_void
DECL|function|e21_reset_8390
id|e21_reset_8390
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
op_assign
id|dev-&gt;base_addr
suffix:semicolon
id|outb
c_func
(paren
l_int|0x01
comma
id|ioaddr
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
l_string|&quot;resetting the E2180x3 t=%ld...&quot;
comma
id|jiffies
)paren
suffix:semicolon
id|ei_status.txing
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Set up the ASIC registers, just in case something changed them. */
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
multiline_comment|/* Grab the 8390 specific header. We put the 2k window so the header page&n;   appears at the start of the shared memory. */
r_static
r_void
DECL|function|e21_get_8390_hdr
id|e21_get_8390_hdr
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
r_int
id|ioaddr
op_assign
id|dev-&gt;base_addr
suffix:semicolon
r_char
op_star
id|shared_mem
op_assign
(paren
r_char
op_star
)paren
id|dev-&gt;mem_start
suffix:semicolon
id|mem_on
c_func
(paren
id|ioaddr
comma
id|shared_mem
comma
id|ring_page
)paren
suffix:semicolon
macro_line|#ifdef notdef
multiline_comment|/* Officially this is what we are doing, but the readl() is faster */
id|memcpy_fromio
c_func
(paren
id|hdr
comma
id|shared_mem
comma
r_sizeof
(paren
r_struct
id|e8390_pkt_hdr
)paren
)paren
suffix:semicolon
macro_line|#else
(paren
(paren
r_int
r_int
op_star
)paren
id|hdr
)paren
(braket
l_int|0
)braket
op_assign
id|readl
c_func
(paren
id|shared_mem
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Turn off memory access: we would need to reprogram the window anyway. */
id|mem_off
c_func
(paren
id|ioaddr
)paren
suffix:semicolon
)brace
multiline_comment|/*  Block input and output are easy on shared memory ethercards.&n;&t;The E21xx makes block_input() especially easy by wrapping the top&n;&t;ring buffer to the bottom automatically. */
r_static
r_void
DECL|function|e21_block_input
id|e21_block_input
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
r_int
id|ioaddr
op_assign
id|dev-&gt;base_addr
suffix:semicolon
r_char
op_star
id|shared_mem
op_assign
(paren
r_char
op_star
)paren
id|dev-&gt;mem_start
suffix:semicolon
id|mem_on
c_func
(paren
id|ioaddr
comma
id|shared_mem
comma
(paren
id|ring_offset
op_rshift
l_int|8
)paren
)paren
suffix:semicolon
multiline_comment|/* Packet is always in one chunk -- we can copy + cksum. */
id|eth_io_copy_and_sum
c_func
(paren
id|skb
comma
id|dev-&gt;mem_start
op_plus
(paren
id|ring_offset
op_amp
l_int|0xff
)paren
comma
id|count
comma
l_int|0
)paren
suffix:semicolon
id|mem_off
c_func
(paren
id|ioaddr
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|e21_block_output
id|e21_block_output
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
r_int
id|ioaddr
op_assign
id|dev-&gt;base_addr
suffix:semicolon
r_volatile
r_char
op_star
id|shared_mem
op_assign
(paren
r_char
op_star
)paren
id|dev-&gt;mem_start
suffix:semicolon
multiline_comment|/* Set the shared memory window start by doing a read, with the low address&n;&t;   bits specifying the starting page. */
id|readb
c_func
(paren
id|shared_mem
op_plus
id|start_page
)paren
suffix:semicolon
id|mem_on
c_func
(paren
id|ioaddr
comma
id|shared_mem
comma
id|start_page
)paren
suffix:semicolon
id|memcpy_toio
c_func
(paren
id|shared_mem
comma
id|buf
comma
id|count
)paren
suffix:semicolon
id|mem_off
c_func
(paren
id|ioaddr
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|e21_close
id|e21_close
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
op_assign
id|dev-&gt;base_addr
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
l_string|&quot;%s: Shutting down ethercard.&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|dev-&gt;irq
comma
id|dev
)paren
suffix:semicolon
id|dev-&gt;irq
op_assign
id|ei_status.saved_irq
suffix:semicolon
multiline_comment|/* Shut off the interrupt line and secondary interface. */
id|inb
c_func
(paren
id|ioaddr
op_plus
id|E21_IRQ_LOW
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0
comma
id|ioaddr
op_plus
id|E21_ASIC
)paren
suffix:semicolon
id|inb
c_func
(paren
id|ioaddr
op_plus
id|E21_IRQ_HIGH
)paren
suffix:semicolon
multiline_comment|/* High IRQ bit, and if_port. */
id|outb
c_func
(paren
l_int|0
comma
id|ioaddr
op_plus
id|E21_ASIC
)paren
suffix:semicolon
id|ei_close
c_func
(paren
id|dev
)paren
suffix:semicolon
multiline_comment|/* Double-check that the memory has been turned off, because really&n;&t;   really bad things happen if it isn&squot;t. */
id|mem_off
c_func
(paren
id|ioaddr
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
"&f;"
macro_line|#ifdef MODULE
DECL|macro|MAX_E21_CARDS
mdefine_line|#define MAX_E21_CARDS&t;4&t;/* Max number of E21 cards per module */
DECL|variable|dev_e21
r_static
r_struct
id|net_device
op_star
id|dev_e21
(braket
id|MAX_E21_CARDS
)braket
suffix:semicolon
DECL|variable|io
r_static
r_int
id|io
(braket
id|MAX_E21_CARDS
)braket
suffix:semicolon
DECL|variable|irq
r_static
r_int
id|irq
(braket
id|MAX_E21_CARDS
)braket
suffix:semicolon
DECL|variable|mem
r_static
r_int
id|mem
(braket
id|MAX_E21_CARDS
)braket
suffix:semicolon
DECL|variable|xcvr
r_static
r_int
id|xcvr
(braket
id|MAX_E21_CARDS
)braket
suffix:semicolon
multiline_comment|/* choose int. or ext. xcvr */
id|MODULE_PARM
c_func
(paren
id|io
comma
l_string|&quot;1-&quot;
id|__MODULE_STRING
c_func
(paren
id|MAX_E21_CARDS
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
id|MAX_E21_CARDS
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
id|MAX_E21_CARDS
)paren
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|xcvr
comma
l_string|&quot;1-&quot;
id|__MODULE_STRING
c_func
(paren
id|MAX_E21_CARDS
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
l_string|&quot; memory base address(es)&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|xcvr
comma
l_string|&quot;transceiver(s) (0=internal, 1=external)&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Cabletron E2100 ISA ethernet driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
multiline_comment|/* This is set up so that only a single autoprobe takes place per call.&n;ISA device autoprobes on a running machine are not recommended. */
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
id|MAX_E21_CARDS
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
)paren
(brace
r_if
c_cond
(paren
id|this_dev
op_ne
l_int|0
)paren
r_break
suffix:semicolon
multiline_comment|/* only autoprobe 1st one */
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;e2100.c: Presently autoprobing (not recommended) for a single card.&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|dev
op_assign
id|alloc_etherdev
c_func
(paren
l_int|0
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
id|dev-&gt;priv
op_assign
l_int|NULL
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
id|dev-&gt;mem_end
op_assign
id|xcvr
(braket
id|this_dev
)braket
suffix:semicolon
multiline_comment|/* low 4bits = xcvr sel. */
r_if
c_cond
(paren
id|do_e2100_probe
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
id|dev_e21
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
l_string|&quot;e2100.c: No E2100 card found (i/o = 0x%x).&bslash;n&quot;
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
id|MAX_E21_CARDS
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
id|dev_e21
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
