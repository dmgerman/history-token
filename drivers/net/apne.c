multiline_comment|/*&n; * Amiga Linux/68k 8390 based PCMCIA Ethernet Driver for the Amiga 1200&n; *&n; * (C) Copyright 1997 Alain Malek&n; *                    (Alain.Malek@cryogen.com)&n; *&n; * ----------------------------------------------------------------------------&n; *&n; * This program is based on&n; *&n; * ne.c:       A general non-shared-memory NS8390 ethernet driver for linux&n; *             Written 1992-94 by Donald Becker.&n; *&n; * 8390.c:     A general NS8390 ethernet driver core for linux.&n; *             Written 1992-94 by Donald Becker.&n; *&n; * cnetdevice: A Sana-II ethernet driver for AmigaOS&n; *             Written by Bruce Abbott (bhabbott@inhb.co.nz)&n; *&n; * ----------------------------------------------------------------------------&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file COPYING in the main directory of the Linux&n; * distribution for more details.&n; *&n; * ----------------------------------------------------------------------------&n; *&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/etherdevice.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/amigaints.h&gt;
macro_line|#include &lt;asm/amigahw.h&gt;
macro_line|#include &lt;asm/amigayle.h&gt;
macro_line|#include &lt;asm/amipcmcia.h&gt;
macro_line|#include &quot;8390.h&quot;
multiline_comment|/* ---- No user-serviceable parts below ---- */
DECL|macro|NE_BASE
mdefine_line|#define NE_BASE&t; (dev-&gt;base_addr)
DECL|macro|NE_CMD
mdefine_line|#define NE_CMD&t; &t;&t;0x00
DECL|macro|NE_DATAPORT
mdefine_line|#define NE_DATAPORT&t;&t;0x10            /* NatSemi-defined port window offset. */
DECL|macro|NE_RESET
mdefine_line|#define NE_RESET&t;&t;0x1f            /* Issue a read to reset, a write to clear. */
DECL|macro|NE_IO_EXTENT
mdefine_line|#define NE_IO_EXTENT&t;        0x20
DECL|macro|NE_EN0_ISR
mdefine_line|#define NE_EN0_ISR&t;&t;0x07
DECL|macro|NE_EN0_DCFG
mdefine_line|#define NE_EN0_DCFG&t;&t;0x0e
DECL|macro|NE_EN0_RSARLO
mdefine_line|#define NE_EN0_RSARLO&t;        0x08
DECL|macro|NE_EN0_RSARHI
mdefine_line|#define NE_EN0_RSARHI&t;        0x09
DECL|macro|NE_EN0_RCNTLO
mdefine_line|#define NE_EN0_RCNTLO&t;        0x0a
DECL|macro|NE_EN0_RXCR
mdefine_line|#define NE_EN0_RXCR&t;&t;0x0c
DECL|macro|NE_EN0_TXCR
mdefine_line|#define NE_EN0_TXCR&t;&t;0x0d
DECL|macro|NE_EN0_RCNTHI
mdefine_line|#define NE_EN0_RCNTHI&t;        0x0b
DECL|macro|NE_EN0_IMR
mdefine_line|#define NE_EN0_IMR&t;&t;0x0f
DECL|macro|NE1SM_START_PG
mdefine_line|#define NE1SM_START_PG&t;0x20&t;/* First page of TX buffer */
DECL|macro|NE1SM_STOP_PG
mdefine_line|#define NE1SM_STOP_PG &t;0x40&t;/* Last page +1 of RX ring */
DECL|macro|NESM_START_PG
mdefine_line|#define NESM_START_PG&t;0x40&t;/* First page of TX buffer */
DECL|macro|NESM_STOP_PG
mdefine_line|#define NESM_STOP_PG&t;0x80&t;/* Last page +1 of RX ring */
r_struct
id|net_device
op_star
id|__init
id|apne_probe
c_func
(paren
r_int
id|unit
)paren
suffix:semicolon
r_static
r_int
id|apne_probe1
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
id|apne_open
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_int
id|apne_close
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
id|apne_reset_8390
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
id|apne_get_8390_hdr
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
r_void
id|apne_block_input
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
id|apne_block_output
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
id|irqreturn_t
id|apne_interrupt
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_static
r_int
id|init_pcmcia
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* IO base address used for nic */
DECL|macro|IOBASE
mdefine_line|#define IOBASE 0x300
multiline_comment|/*&n;   use MANUAL_CONFIG and MANUAL_OFFSET for enabling IO by hand&n;   you can find the values to use by looking at the cnet.device&n;   config file example (the default values are for the CNET40BC card)&n;*/
multiline_comment|/*&n;#define MANUAL_CONFIG 0x20&n;#define MANUAL_OFFSET 0x3f8&n;&n;#define MANUAL_HWADDR0 0x00&n;#define MANUAL_HWADDR1 0x12&n;#define MANUAL_HWADDR2 0x34&n;#define MANUAL_HWADDR3 0x56&n;#define MANUAL_HWADDR4 0x78&n;#define MANUAL_HWADDR5 0x9a&n;*/
DECL|variable|version
r_static
r_const
r_char
id|version
(braket
)braket
op_assign
l_string|&quot;apne.c:v1.1 7/10/98 Alain Malek (Alain.Malek@cryogen.ch)&bslash;n&quot;
suffix:semicolon
DECL|variable|apne_owned
r_static
r_int
id|apne_owned
suffix:semicolon
multiline_comment|/* signal if card already owned */
DECL|function|apne_probe
r_struct
id|net_device
op_star
id|__init
id|apne_probe
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
suffix:semicolon
macro_line|#ifndef MANUAL_CONFIG
r_char
id|tuple
(braket
l_int|8
)braket
suffix:semicolon
macro_line|#endif
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
id|apne_owned
)paren
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|ENODEV
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|AMIGAHW_PRESENT
c_func
(paren
id|PCMCIA
)paren
)paren
)paren
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|ENODEV
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Looking for PCMCIA ethernet card : &quot;
)paren
suffix:semicolon
multiline_comment|/* check if a card is inserted */
r_if
c_cond
(paren
op_logical_neg
(paren
id|PCMCIA_INSERTED
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;NO PCMCIA card inserted&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|ENODEV
)paren
suffix:semicolon
)brace
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
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|ENOMEM
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unit
op_ge
l_int|0
)paren
(brace
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
)brace
id|SET_MODULE_OWNER
c_func
(paren
id|dev
)paren
suffix:semicolon
multiline_comment|/* disable pcmcia irq for readtuple */
id|pcmcia_disable_irq
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifndef MANUAL_CONFIG
r_if
c_cond
(paren
(paren
id|pcmcia_copy_tuple
c_func
(paren
id|CISTPL_FUNCID
comma
id|tuple
comma
l_int|8
)paren
OL
l_int|3
)paren
op_logical_or
(paren
id|tuple
(braket
l_int|2
)braket
op_ne
id|CISTPL_FUNCID_NETWORK
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;not an ethernet card&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* XXX: shouldn&squot;t we re-enable irq here? */
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
op_minus
id|ENODEV
)paren
suffix:semicolon
)brace
macro_line|#endif
id|printk
c_func
(paren
l_string|&quot;ethernet PCMCIA card inserted&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|init_pcmcia
c_func
(paren
)paren
)paren
(brace
multiline_comment|/* XXX: shouldn&squot;t we re-enable irq here? */
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
op_minus
id|ENODEV
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|request_region
c_func
(paren
id|IOBASE
comma
l_int|0x20
comma
id|dev-&gt;name
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
id|ERR_PTR
c_func
(paren
op_minus
id|EBUSY
)paren
suffix:semicolon
)brace
id|err
op_assign
id|apne_probe1
c_func
(paren
id|dev
comma
id|IOBASE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
id|release_region
c_func
(paren
id|IOBASE
comma
l_int|0x20
)paren
suffix:semicolon
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
op_logical_neg
id|err
)paren
r_return
id|dev
suffix:semicolon
id|pcmcia_disable_irq
c_func
(paren
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|IRQ_AMIGA_PORTS
comma
id|dev
)paren
suffix:semicolon
id|pcmcia_reset
c_func
(paren
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|IOBASE
comma
l_int|0x20
)paren
suffix:semicolon
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
DECL|function|apne_probe1
r_static
r_int
id|__init
id|apne_probe1
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
suffix:semicolon
r_int
r_char
id|SA_prom
(braket
l_int|32
)braket
suffix:semicolon
r_int
id|wordlength
op_assign
l_int|2
suffix:semicolon
r_const
r_char
op_star
id|name
op_assign
l_int|NULL
suffix:semicolon
r_int
id|start_page
comma
id|stop_page
suffix:semicolon
macro_line|#ifndef MANUAL_HWADDR0
r_int
id|neX000
comma
id|ctron
suffix:semicolon
macro_line|#endif
r_static
r_int
id|version_printed
suffix:semicolon
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
id|printk
c_func
(paren
l_string|&quot;PCMCIA NE*000 ethercard probe&quot;
)paren
suffix:semicolon
multiline_comment|/* Reset card. Who knows what dain-bramaged state it was left in. */
(brace
r_int
r_int
id|reset_start_time
op_assign
id|jiffies
suffix:semicolon
id|outb
c_func
(paren
id|inb
c_func
(paren
id|ioaddr
op_plus
id|NE_RESET
)paren
comma
id|ioaddr
op_plus
id|NE_RESET
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|inb
c_func
(paren
id|ioaddr
op_plus
id|NE_EN0_ISR
)paren
op_amp
id|ENISR_RESET
)paren
op_eq
l_int|0
)paren
r_if
c_cond
(paren
id|jiffies
op_minus
id|reset_start_time
OG
l_int|2
op_star
id|HZ
op_div
l_int|100
)paren
(brace
id|printk
c_func
(paren
l_string|&quot; not found (no reset ack).&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|outb
c_func
(paren
l_int|0xff
comma
id|ioaddr
op_plus
id|NE_EN0_ISR
)paren
suffix:semicolon
multiline_comment|/* Ack all intr. */
)brace
macro_line|#ifndef MANUAL_HWADDR0
multiline_comment|/* Read the 16 bytes of station address PROM.&n;       We must first initialize registers, similar to NS8390_init(eifdev, 0).&n;       We can&squot;t reliably read the SAPROM address without this.&n;       (I learned the hard way!). */
(brace
r_struct
(brace
r_int
r_int
id|value
comma
id|offset
suffix:semicolon
)brace
id|program_seq
(braket
)braket
op_assign
(brace
(brace
id|E8390_NODMA
op_plus
id|E8390_PAGE0
op_plus
id|E8390_STOP
comma
id|NE_CMD
)brace
comma
multiline_comment|/* Select page 0*/
(brace
l_int|0x48
comma
id|NE_EN0_DCFG
)brace
comma
multiline_comment|/* Set byte-wide (0x48) access. */
(brace
l_int|0x00
comma
id|NE_EN0_RCNTLO
)brace
comma
multiline_comment|/* Clear the count regs. */
(brace
l_int|0x00
comma
id|NE_EN0_RCNTHI
)brace
comma
(brace
l_int|0x00
comma
id|NE_EN0_IMR
)brace
comma
multiline_comment|/* Mask completion irq. */
(brace
l_int|0xFF
comma
id|NE_EN0_ISR
)brace
comma
(brace
id|E8390_RXOFF
comma
id|NE_EN0_RXCR
)brace
comma
multiline_comment|/* 0x20  Set to monitor */
(brace
id|E8390_TXOFF
comma
id|NE_EN0_TXCR
)brace
comma
multiline_comment|/* 0x02  and loopback mode. */
(brace
l_int|32
comma
id|NE_EN0_RCNTLO
)brace
comma
(brace
l_int|0x00
comma
id|NE_EN0_RCNTHI
)brace
comma
(brace
l_int|0x00
comma
id|NE_EN0_RSARLO
)brace
comma
multiline_comment|/* DMA starting at 0x0000. */
(brace
l_int|0x00
comma
id|NE_EN0_RSARHI
)brace
comma
(brace
id|E8390_RREAD
op_plus
id|E8390_START
comma
id|NE_CMD
)brace
comma
)brace
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
r_sizeof
(paren
id|program_seq
)paren
op_div
r_sizeof
(paren
id|program_seq
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
id|outb
c_func
(paren
id|program_seq
(braket
id|i
)braket
dot
id|value
comma
id|ioaddr
op_plus
id|program_seq
(braket
id|i
)braket
dot
id|offset
)paren
suffix:semicolon
)brace
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|32
multiline_comment|/*sizeof(SA_prom)*/
suffix:semicolon
id|i
op_add_assign
l_int|2
)paren
(brace
id|SA_prom
(braket
id|i
)braket
op_assign
id|inb
c_func
(paren
id|ioaddr
op_plus
id|NE_DATAPORT
)paren
suffix:semicolon
id|SA_prom
(braket
id|i
op_plus
l_int|1
)braket
op_assign
id|inb
c_func
(paren
id|ioaddr
op_plus
id|NE_DATAPORT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|SA_prom
(braket
id|i
)braket
op_ne
id|SA_prom
(braket
id|i
op_plus
l_int|1
)braket
)paren
id|wordlength
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&t;At this point, wordlength *only* tells us if the SA_prom is doubled&n;&t;up or not because some broken PCI cards don&squot;t respect the byte-wide&n;&t;request in program_seq above, and hence don&squot;t have doubled up values. &n;&t;These broken cards would otherwise be detected as an ne1000.  */
r_if
c_cond
(paren
id|wordlength
op_eq
l_int|2
)paren
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|16
suffix:semicolon
id|i
op_increment
)paren
id|SA_prom
(braket
id|i
)braket
op_assign
id|SA_prom
(braket
id|i
op_plus
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|wordlength
op_eq
l_int|2
)paren
(brace
multiline_comment|/* We must set the 8390 for word mode. */
id|outb
c_func
(paren
l_int|0x49
comma
id|ioaddr
op_plus
id|NE_EN0_DCFG
)paren
suffix:semicolon
id|start_page
op_assign
id|NESM_START_PG
suffix:semicolon
id|stop_page
op_assign
id|NESM_STOP_PG
suffix:semicolon
)brace
r_else
(brace
id|start_page
op_assign
id|NE1SM_START_PG
suffix:semicolon
id|stop_page
op_assign
id|NE1SM_STOP_PG
suffix:semicolon
)brace
id|neX000
op_assign
(paren
id|SA_prom
(braket
l_int|14
)braket
op_eq
l_int|0x57
op_logical_and
id|SA_prom
(braket
l_int|15
)braket
op_eq
l_int|0x57
)paren
suffix:semicolon
id|ctron
op_assign
(paren
id|SA_prom
(braket
l_int|0
)braket
op_eq
l_int|0x00
op_logical_and
id|SA_prom
(braket
l_int|1
)braket
op_eq
l_int|0x00
op_logical_and
id|SA_prom
(braket
l_int|2
)braket
op_eq
l_int|0x1d
)paren
suffix:semicolon
multiline_comment|/* Set up the rest of the parameters. */
r_if
c_cond
(paren
id|neX000
)paren
(brace
id|name
op_assign
(paren
id|wordlength
op_eq
l_int|2
)paren
ques
c_cond
l_string|&quot;NE2000&quot;
suffix:colon
l_string|&quot;NE1000&quot;
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|ctron
)paren
(brace
id|name
op_assign
(paren
id|wordlength
op_eq
l_int|2
)paren
ques
c_cond
l_string|&quot;Ctron-8&quot;
suffix:colon
l_string|&quot;Ctron-16&quot;
suffix:semicolon
id|start_page
op_assign
l_int|0x01
suffix:semicolon
id|stop_page
op_assign
(paren
id|wordlength
op_eq
l_int|2
)paren
ques
c_cond
l_int|0x40
suffix:colon
l_int|0x20
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot; not found.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
macro_line|#else
id|wordlength
op_assign
l_int|2
suffix:semicolon
multiline_comment|/* We must set the 8390 for word mode. */
id|outb
c_func
(paren
l_int|0x49
comma
id|ioaddr
op_plus
id|NE_EN0_DCFG
)paren
suffix:semicolon
id|start_page
op_assign
id|NESM_START_PG
suffix:semicolon
id|stop_page
op_assign
id|NESM_STOP_PG
suffix:semicolon
id|SA_prom
(braket
l_int|0
)braket
op_assign
id|MANUAL_HWADDR0
suffix:semicolon
id|SA_prom
(braket
l_int|1
)braket
op_assign
id|MANUAL_HWADDR1
suffix:semicolon
id|SA_prom
(braket
l_int|2
)braket
op_assign
id|MANUAL_HWADDR2
suffix:semicolon
id|SA_prom
(braket
l_int|3
)braket
op_assign
id|MANUAL_HWADDR3
suffix:semicolon
id|SA_prom
(braket
l_int|4
)braket
op_assign
id|MANUAL_HWADDR4
suffix:semicolon
id|SA_prom
(braket
l_int|5
)braket
op_assign
id|MANUAL_HWADDR5
suffix:semicolon
id|name
op_assign
l_string|&quot;NE2000&quot;
suffix:semicolon
macro_line|#endif
id|dev-&gt;base_addr
op_assign
id|ioaddr
suffix:semicolon
multiline_comment|/* Install the Interrupt handler */
id|i
op_assign
id|request_irq
c_func
(paren
id|IRQ_AMIGA_PORTS
comma
id|apne_interrupt
comma
id|SA_SHIRQ
comma
id|dev-&gt;name
comma
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
)paren
r_return
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
id|ETHER_ADDR_LEN
suffix:semicolon
id|i
op_increment
)paren
(brace
id|printk
c_func
(paren
l_string|&quot; %2.2x&quot;
comma
id|SA_prom
(braket
id|i
)braket
)paren
suffix:semicolon
id|dev-&gt;dev_addr
(braket
id|i
)braket
op_assign
id|SA_prom
(braket
id|i
)braket
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;&bslash;n%s: %s found.&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|name
)paren
suffix:semicolon
id|ei_status.name
op_assign
id|name
suffix:semicolon
id|ei_status.tx_start_page
op_assign
id|start_page
suffix:semicolon
id|ei_status.stop_page
op_assign
id|stop_page
suffix:semicolon
id|ei_status.word16
op_assign
(paren
id|wordlength
op_eq
l_int|2
)paren
suffix:semicolon
id|ei_status.rx_start_page
op_assign
id|start_page
op_plus
id|TX_PAGES
suffix:semicolon
id|ei_status.reset_8390
op_assign
op_amp
id|apne_reset_8390
suffix:semicolon
id|ei_status.block_input
op_assign
op_amp
id|apne_block_input
suffix:semicolon
id|ei_status.block_output
op_assign
op_amp
id|apne_block_output
suffix:semicolon
id|ei_status.get_8390_hdr
op_assign
op_amp
id|apne_get_8390_hdr
suffix:semicolon
id|dev-&gt;open
op_assign
op_amp
id|apne_open
suffix:semicolon
id|dev-&gt;stop
op_assign
op_amp
id|apne_close
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
id|pcmcia_ack_int
c_func
(paren
id|pcmcia_get_intreq
c_func
(paren
)paren
)paren
suffix:semicolon
multiline_comment|/* ack PCMCIA int req */
id|pcmcia_enable_irq
c_func
(paren
)paren
suffix:semicolon
id|apne_owned
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|apne_open
id|apne_open
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
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
r_int
DECL|function|apne_close
id|apne_close
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
multiline_comment|/* Hard reset the card.  This used to pause for the same period that a&n;   8390 reset command required, but that shouldn&squot;t be necessary. */
r_static
r_void
DECL|function|apne_reset_8390
id|apne_reset_8390
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
id|reset_start_time
op_assign
id|jiffies
suffix:semicolon
id|init_pcmcia
c_func
(paren
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
l_string|&quot;resetting the 8390 t=%ld...&quot;
comma
id|jiffies
)paren
suffix:semicolon
id|outb
c_func
(paren
id|inb
c_func
(paren
id|NE_BASE
op_plus
id|NE_RESET
)paren
comma
id|NE_BASE
op_plus
id|NE_RESET
)paren
suffix:semicolon
id|ei_status.txing
op_assign
l_int|0
suffix:semicolon
id|ei_status.dmaing
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* This check _should_not_ be necessary, omit eventually. */
r_while
c_loop
(paren
(paren
id|inb
c_func
(paren
id|NE_BASE
op_plus
id|NE_EN0_ISR
)paren
op_amp
id|ENISR_RESET
)paren
op_eq
l_int|0
)paren
r_if
c_cond
(paren
id|jiffies
op_minus
id|reset_start_time
OG
l_int|2
op_star
id|HZ
op_div
l_int|100
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: ne_reset_8390() did not complete.&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|outb
c_func
(paren
id|ENISR_RESET
comma
id|NE_BASE
op_plus
id|NE_EN0_ISR
)paren
suffix:semicolon
multiline_comment|/* Ack intr. */
)brace
multiline_comment|/* Grab the 8390 specific header. Similar to the block_input routine, but&n;   we don&squot;t need to be concerned with ring wrap as the header will be at&n;   the start of a page, so we optimize accordingly. */
r_static
r_void
DECL|function|apne_get_8390_hdr
id|apne_get_8390_hdr
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
id|nic_base
op_assign
id|dev-&gt;base_addr
suffix:semicolon
r_int
id|cnt
suffix:semicolon
r_char
op_star
id|ptrc
suffix:semicolon
r_int
op_star
id|ptrs
suffix:semicolon
multiline_comment|/* This *shouldn&squot;t* happen. If it does, it&squot;s the last thing you&squot;ll see */
r_if
c_cond
(paren
id|ei_status.dmaing
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: DMAing conflict in ne_get_8390_hdr &quot;
l_string|&quot;[DMAstat:%d][irqlock:%d][intr:%d].&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|ei_status.dmaing
comma
id|ei_status.irqlock
comma
id|dev-&gt;irq
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|ei_status.dmaing
op_or_assign
l_int|0x01
suffix:semicolon
id|outb
c_func
(paren
id|E8390_NODMA
op_plus
id|E8390_PAGE0
op_plus
id|E8390_START
comma
id|nic_base
op_plus
id|NE_CMD
)paren
suffix:semicolon
id|outb
c_func
(paren
id|ENISR_RDC
comma
id|nic_base
op_plus
id|NE_EN0_ISR
)paren
suffix:semicolon
id|outb
c_func
(paren
r_sizeof
(paren
r_struct
id|e8390_pkt_hdr
)paren
comma
id|nic_base
op_plus
id|NE_EN0_RCNTLO
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0
comma
id|nic_base
op_plus
id|NE_EN0_RCNTHI
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0
comma
id|nic_base
op_plus
id|NE_EN0_RSARLO
)paren
suffix:semicolon
multiline_comment|/* On page boundary */
id|outb
c_func
(paren
id|ring_page
comma
id|nic_base
op_plus
id|NE_EN0_RSARHI
)paren
suffix:semicolon
id|outb
c_func
(paren
id|E8390_RREAD
op_plus
id|E8390_START
comma
id|nic_base
op_plus
id|NE_CMD
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ei_status.word16
)paren
(brace
id|ptrs
op_assign
(paren
r_int
op_star
)paren
id|hdr
suffix:semicolon
r_for
c_loop
(paren
id|cnt
op_assign
l_int|0
suffix:semicolon
id|cnt
OL
(paren
r_sizeof
(paren
r_struct
id|e8390_pkt_hdr
)paren
op_rshift
l_int|1
)paren
suffix:semicolon
id|cnt
op_increment
)paren
(brace
op_star
id|ptrs
op_increment
op_assign
id|inw
c_func
(paren
id|NE_BASE
op_plus
id|NE_DATAPORT
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
id|ptrc
op_assign
(paren
r_char
op_star
)paren
id|hdr
suffix:semicolon
r_for
c_loop
(paren
id|cnt
op_assign
l_int|0
suffix:semicolon
id|cnt
OL
r_sizeof
(paren
r_struct
id|e8390_pkt_hdr
)paren
suffix:semicolon
id|cnt
op_increment
)paren
(brace
op_star
id|ptrc
op_increment
op_assign
id|inb
c_func
(paren
id|NE_BASE
op_plus
id|NE_DATAPORT
)paren
suffix:semicolon
)brace
)brace
id|outb
c_func
(paren
id|ENISR_RDC
comma
id|nic_base
op_plus
id|NE_EN0_ISR
)paren
suffix:semicolon
multiline_comment|/* Ack intr. */
id|ei_status.dmaing
op_and_assign
op_complement
l_int|0x01
suffix:semicolon
id|le16_to_cpus
c_func
(paren
op_amp
id|hdr-&gt;count
)paren
suffix:semicolon
)brace
multiline_comment|/* Block input and output, similar to the Crynwr packet driver.  If you&n;   are porting to a new ethercard, look at the packet driver source for hints.&n;   The NEx000 doesn&squot;t share the on-board packet memory -- you have to put&n;   the packet out through the &quot;remote DMA&quot; dataport using outb. */
r_static
r_void
DECL|function|apne_block_input
id|apne_block_input
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
id|nic_base
op_assign
id|dev-&gt;base_addr
suffix:semicolon
r_char
op_star
id|buf
op_assign
id|skb-&gt;data
suffix:semicolon
r_char
op_star
id|ptrc
suffix:semicolon
r_int
op_star
id|ptrs
suffix:semicolon
r_int
id|cnt
suffix:semicolon
multiline_comment|/* This *shouldn&squot;t* happen. If it does, it&squot;s the last thing you&squot;ll see */
r_if
c_cond
(paren
id|ei_status.dmaing
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: DMAing conflict in ne_block_input &quot;
l_string|&quot;[DMAstat:%d][irqlock:%d][intr:%d].&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|ei_status.dmaing
comma
id|ei_status.irqlock
comma
id|dev-&gt;irq
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|ei_status.dmaing
op_or_assign
l_int|0x01
suffix:semicolon
id|outb
c_func
(paren
id|E8390_NODMA
op_plus
id|E8390_PAGE0
op_plus
id|E8390_START
comma
id|nic_base
op_plus
id|NE_CMD
)paren
suffix:semicolon
id|outb
c_func
(paren
id|ENISR_RDC
comma
id|nic_base
op_plus
id|NE_EN0_ISR
)paren
suffix:semicolon
id|outb
c_func
(paren
id|count
op_amp
l_int|0xff
comma
id|nic_base
op_plus
id|NE_EN0_RCNTLO
)paren
suffix:semicolon
id|outb
c_func
(paren
id|count
op_rshift
l_int|8
comma
id|nic_base
op_plus
id|NE_EN0_RCNTHI
)paren
suffix:semicolon
id|outb
c_func
(paren
id|ring_offset
op_amp
l_int|0xff
comma
id|nic_base
op_plus
id|NE_EN0_RSARLO
)paren
suffix:semicolon
id|outb
c_func
(paren
id|ring_offset
op_rshift
l_int|8
comma
id|nic_base
op_plus
id|NE_EN0_RSARHI
)paren
suffix:semicolon
id|outb
c_func
(paren
id|E8390_RREAD
op_plus
id|E8390_START
comma
id|nic_base
op_plus
id|NE_CMD
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ei_status.word16
)paren
(brace
id|ptrs
op_assign
(paren
r_int
op_star
)paren
id|buf
suffix:semicolon
r_for
c_loop
(paren
id|cnt
op_assign
l_int|0
suffix:semicolon
id|cnt
OL
(paren
id|count
op_rshift
l_int|1
)paren
suffix:semicolon
id|cnt
op_increment
)paren
op_star
id|ptrs
op_increment
op_assign
id|inw
c_func
(paren
id|NE_BASE
op_plus
id|NE_DATAPORT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|count
op_amp
l_int|0x01
)paren
(brace
id|buf
(braket
id|count
op_minus
l_int|1
)braket
op_assign
id|inb
c_func
(paren
id|NE_BASE
op_plus
id|NE_DATAPORT
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
id|ptrc
op_assign
(paren
r_char
op_star
)paren
id|buf
suffix:semicolon
r_for
c_loop
(paren
id|cnt
op_assign
l_int|0
suffix:semicolon
id|cnt
OL
id|count
suffix:semicolon
id|cnt
op_increment
)paren
op_star
id|ptrc
op_increment
op_assign
id|inb
c_func
(paren
id|NE_BASE
op_plus
id|NE_DATAPORT
)paren
suffix:semicolon
)brace
id|outb
c_func
(paren
id|ENISR_RDC
comma
id|nic_base
op_plus
id|NE_EN0_ISR
)paren
suffix:semicolon
multiline_comment|/* Ack intr. */
id|ei_status.dmaing
op_and_assign
op_complement
l_int|0x01
suffix:semicolon
)brace
r_static
r_void
DECL|function|apne_block_output
id|apne_block_output
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
r_const
r_int
id|start_page
)paren
(brace
r_int
id|nic_base
op_assign
id|NE_BASE
suffix:semicolon
r_int
r_int
id|dma_start
suffix:semicolon
r_char
op_star
id|ptrc
suffix:semicolon
r_int
op_star
id|ptrs
suffix:semicolon
r_int
id|cnt
suffix:semicolon
multiline_comment|/* Round the count up for word writes.  Do we need to do this?&n;       What effect will an odd byte count have on the 8390?&n;       I should check someday. */
r_if
c_cond
(paren
id|ei_status.word16
op_logical_and
(paren
id|count
op_amp
l_int|0x01
)paren
)paren
id|count
op_increment
suffix:semicolon
multiline_comment|/* This *shouldn&squot;t* happen. If it does, it&squot;s the last thing you&squot;ll see */
r_if
c_cond
(paren
id|ei_status.dmaing
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: DMAing conflict in ne_block_output.&quot;
l_string|&quot;[DMAstat:%d][irqlock:%d][intr:%d]&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|ei_status.dmaing
comma
id|ei_status.irqlock
comma
id|dev-&gt;irq
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|ei_status.dmaing
op_or_assign
l_int|0x01
suffix:semicolon
multiline_comment|/* We should already be in page 0, but to be safe... */
id|outb
c_func
(paren
id|E8390_PAGE0
op_plus
id|E8390_START
op_plus
id|E8390_NODMA
comma
id|nic_base
op_plus
id|NE_CMD
)paren
suffix:semicolon
id|outb
c_func
(paren
id|ENISR_RDC
comma
id|nic_base
op_plus
id|NE_EN0_ISR
)paren
suffix:semicolon
multiline_comment|/* Now the normal output. */
id|outb
c_func
(paren
id|count
op_amp
l_int|0xff
comma
id|nic_base
op_plus
id|NE_EN0_RCNTLO
)paren
suffix:semicolon
id|outb
c_func
(paren
id|count
op_rshift
l_int|8
comma
id|nic_base
op_plus
id|NE_EN0_RCNTHI
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x00
comma
id|nic_base
op_plus
id|NE_EN0_RSARLO
)paren
suffix:semicolon
id|outb
c_func
(paren
id|start_page
comma
id|nic_base
op_plus
id|NE_EN0_RSARHI
)paren
suffix:semicolon
id|outb
c_func
(paren
id|E8390_RWRITE
op_plus
id|E8390_START
comma
id|nic_base
op_plus
id|NE_CMD
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ei_status.word16
)paren
(brace
id|ptrs
op_assign
(paren
r_int
op_star
)paren
id|buf
suffix:semicolon
r_for
c_loop
(paren
id|cnt
op_assign
l_int|0
suffix:semicolon
id|cnt
OL
id|count
op_rshift
l_int|1
suffix:semicolon
id|cnt
op_increment
)paren
id|outw
c_func
(paren
op_star
id|ptrs
op_increment
comma
id|NE_BASE
op_plus
id|NE_DATAPORT
)paren
suffix:semicolon
)brace
r_else
(brace
id|ptrc
op_assign
(paren
r_char
op_star
)paren
id|buf
suffix:semicolon
r_for
c_loop
(paren
id|cnt
op_assign
l_int|0
suffix:semicolon
id|cnt
OL
id|count
suffix:semicolon
id|cnt
op_increment
)paren
id|outb
c_func
(paren
op_star
id|ptrc
op_increment
comma
id|NE_BASE
op_plus
id|NE_DATAPORT
)paren
suffix:semicolon
)brace
id|dma_start
op_assign
id|jiffies
suffix:semicolon
r_while
c_loop
(paren
(paren
id|inb
c_func
(paren
id|NE_BASE
op_plus
id|NE_EN0_ISR
)paren
op_amp
id|ENISR_RDC
)paren
op_eq
l_int|0
)paren
r_if
c_cond
(paren
id|jiffies
op_minus
id|dma_start
OG
l_int|2
op_star
id|HZ
op_div
l_int|100
)paren
(brace
multiline_comment|/* 20ms */
id|printk
c_func
(paren
l_string|&quot;%s: timeout waiting for Tx RDC.&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
id|apne_reset_8390
c_func
(paren
id|dev
)paren
suffix:semicolon
id|NS8390_init
c_func
(paren
id|dev
comma
l_int|1
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|outb
c_func
(paren
id|ENISR_RDC
comma
id|nic_base
op_plus
id|NE_EN0_ISR
)paren
suffix:semicolon
multiline_comment|/* Ack intr. */
id|ei_status.dmaing
op_and_assign
op_complement
l_int|0x01
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|apne_interrupt
r_static
id|irqreturn_t
id|apne_interrupt
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
r_char
id|pcmcia_intreq
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|gayle.inten
op_amp
id|GAYLE_IRQ_IRQ
)paren
)paren
r_return
id|IRQ_NONE
suffix:semicolon
id|pcmcia_intreq
op_assign
id|pcmcia_get_intreq
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|pcmcia_intreq
op_amp
id|GAYLE_IRQ_IRQ
)paren
)paren
(brace
id|pcmcia_ack_int
c_func
(paren
id|pcmcia_intreq
)paren
suffix:semicolon
r_return
id|IRQ_NONE
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ei_debug
OG
l_int|3
)paren
id|printk
c_func
(paren
l_string|&quot;pcmcia intreq = %x&bslash;n&quot;
comma
id|pcmcia_intreq
)paren
suffix:semicolon
id|pcmcia_disable_irq
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* to get rid of the sti() within ei_interrupt */
id|ei_interrupt
c_func
(paren
id|irq
comma
id|dev_id
comma
id|regs
)paren
suffix:semicolon
id|pcmcia_ack_int
c_func
(paren
id|pcmcia_get_intreq
c_func
(paren
)paren
)paren
suffix:semicolon
id|pcmcia_enable_irq
c_func
(paren
)paren
suffix:semicolon
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
macro_line|#ifdef MODULE
DECL|variable|apne_dev
r_static
r_struct
id|net_device
op_star
id|apne_dev
suffix:semicolon
DECL|function|init_module
r_int
id|init_module
c_func
(paren
r_void
)paren
(brace
id|apne_dev
op_assign
id|apne_probe
c_func
(paren
op_minus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|apne_dev
)paren
)paren
r_return
id|PTR_ERR
c_func
(paren
id|apne_dev
)paren
suffix:semicolon
r_return
l_int|0
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
id|unregister_netdev
c_func
(paren
id|apne_dev
)paren
suffix:semicolon
id|pcmcia_disable_irq
c_func
(paren
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|IRQ_AMIGA_PORTS
comma
id|apne_dev
)paren
suffix:semicolon
id|pcmcia_reset
c_func
(paren
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|IOBASE
comma
l_int|0x20
)paren
suffix:semicolon
id|free_netdev
c_func
(paren
id|apne_dev
)paren
suffix:semicolon
)brace
macro_line|#endif
DECL|function|init_pcmcia
r_static
r_int
id|init_pcmcia
c_func
(paren
r_void
)paren
(brace
id|u_char
id|config
suffix:semicolon
macro_line|#ifndef MANUAL_CONFIG
id|u_char
id|tuple
(braket
l_int|32
)braket
suffix:semicolon
r_int
id|offset_len
suffix:semicolon
macro_line|#endif
id|u_long
id|offset
suffix:semicolon
id|pcmcia_reset
c_func
(paren
)paren
suffix:semicolon
id|pcmcia_program_voltage
c_func
(paren
id|PCMCIA_0V
)paren
suffix:semicolon
id|pcmcia_access_speed
c_func
(paren
id|PCMCIA_SPEED_250NS
)paren
suffix:semicolon
id|pcmcia_write_enable
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef MANUAL_CONFIG
id|config
op_assign
id|MANUAL_CONFIG
suffix:semicolon
macro_line|#else
multiline_comment|/* get and write config byte to enable IO port */
r_if
c_cond
(paren
id|pcmcia_copy_tuple
c_func
(paren
id|CISTPL_CFTABLE_ENTRY
comma
id|tuple
comma
l_int|32
)paren
OL
l_int|3
)paren
r_return
l_int|0
suffix:semicolon
id|config
op_assign
id|tuple
(braket
l_int|2
)braket
op_amp
l_int|0x3f
suffix:semicolon
macro_line|#endif
macro_line|#ifdef MANUAL_OFFSET
id|offset
op_assign
id|MANUAL_OFFSET
suffix:semicolon
macro_line|#else
r_if
c_cond
(paren
id|pcmcia_copy_tuple
c_func
(paren
id|CISTPL_CONFIG
comma
id|tuple
comma
l_int|32
)paren
OL
l_int|6
)paren
r_return
l_int|0
suffix:semicolon
id|offset_len
op_assign
(paren
id|tuple
(braket
l_int|2
)braket
op_amp
l_int|0x3
)paren
op_plus
l_int|1
suffix:semicolon
id|offset
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|offset_len
op_decrement
)paren
(brace
id|offset
op_assign
(paren
id|offset
op_lshift
l_int|8
)paren
op_or
id|tuple
(braket
l_int|4
op_plus
id|offset_len
)braket
suffix:semicolon
)brace
macro_line|#endif
id|out_8
c_func
(paren
id|GAYLE_ATTRIBUTE
op_plus
id|offset
comma
id|config
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
