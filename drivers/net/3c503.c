multiline_comment|/* 3c503.c: A shared-memory NS8390 ethernet driver for linux. */
multiline_comment|/*&n;    Written 1992-94 by Donald Becker.&n;&n;    Copyright 1993 United States Government as represented by the&n;    Director, National Security Agency.  This software may be used and&n;    distributed according to the terms of the GNU General Public License,&n;    incorporated herein by reference.&n;&n;    The author may be reached as becker@CESDIS.gsfc.nasa.gov, or C/O&n;    Center of Excellence in Space Data and Information Sciences&n;       Code 930.5, Goddard Space Flight Center, Greenbelt MD 20771&n;&n;    This driver should work with the 3c503 and 3c503/16.  It should be used&n;    in shared memory mode for best performance, although it may also work&n;    in programmed-I/O mode.&n;&n;    Sources:&n;    EtherLink II Technical Reference Manual,&n;    EtherLink II/16 Technical Reference Manual Supplement,&n;    3Com Corporation, 5400 Bayfront Plaza, Santa Clara CA 95052-8145&n;&n;    The Crynwr 3c503 packet driver.&n;&n;    Changelog:&n;&n;    Paul Gortmaker&t;: add support for the 2nd 8kB of RAM on 16 bit cards.&n;    Paul Gortmaker&t;: multiple card support for module users.&n;    rjohnson@analogic.com : Fix up PIO interface for efficient operation.&n;&n;*/
DECL|variable|version
r_static
r_const
r_char
id|version
(braket
)braket
op_assign
l_string|&quot;3c503.c:v1.10 9/23/93  Donald Becker (becker@cesdis.gsfc.nasa.gov)&bslash;n&quot;
suffix:semicolon
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/etherdevice.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#include &quot;8390.h&quot;
macro_line|#include &quot;3c503.h&quot;
DECL|macro|WRD_COUNT
mdefine_line|#define WRD_COUNT 4
r_int
id|el2_probe
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
id|el2_pio_probe
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
id|el2_probe1
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
multiline_comment|/* A zero-terminated list of I/O addresses to be probed in PIO mode. */
DECL|variable|__initdata
r_static
r_int
r_int
id|netcard_portlist
(braket
)braket
id|__initdata
op_assign
(brace
l_int|0x300
comma
l_int|0x310
comma
l_int|0x330
comma
l_int|0x350
comma
l_int|0x250
comma
l_int|0x280
comma
l_int|0x2a0
comma
l_int|0x2e0
comma
l_int|0
)brace
suffix:semicolon
DECL|macro|EL2_IO_EXTENT
mdefine_line|#define EL2_IO_EXTENT&t;16
r_static
r_int
id|el2_open
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
id|el2_close
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
id|el2_reset_8390
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
id|el2_init_card
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
id|el2_block_output
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
id|el2_block_input
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
id|el2_get_8390_hdr
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
"&f;"
multiline_comment|/* This routine probes for a memory-mapped 3c503 board by looking for&n;   the &quot;location register&quot; at the end of the jumpered boot PROM space.&n;   This works even if a PROM isn&squot;t there.&n;&n;   If the ethercard isn&squot;t found there is an optional probe for&n;   ethercard jumpered to programmed-I/O mode.&n;   */
r_int
id|__init
DECL|function|el2_probe
id|el2_probe
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
id|addr
comma
id|addrs
(braket
)braket
op_assign
(brace
l_int|0xddffe
comma
l_int|0xd9ffe
comma
l_int|0xcdffe
comma
l_int|0xc9ffe
comma
l_int|0
)brace
suffix:semicolon
r_int
id|base_addr
op_assign
id|dev-&gt;base_addr
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
id|el2_probe1
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
id|addr
op_assign
id|addrs
suffix:semicolon
op_star
id|addr
suffix:semicolon
id|addr
op_increment
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
r_int
id|base_bits
op_assign
id|isa_readb
c_func
(paren
op_star
id|addr
)paren
suffix:semicolon
multiline_comment|/* Find first set bit. */
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
comma
id|base_bits
op_rshift_assign
l_int|1
)paren
r_if
c_cond
(paren
id|base_bits
op_amp
l_int|0x1
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|base_bits
op_ne
l_int|1
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|el2_probe1
c_func
(paren
id|dev
comma
id|netcard_portlist
(braket
id|i
)braket
)paren
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#if ! defined(no_probe_nonshared_memory)
r_return
id|el2_pio_probe
c_func
(paren
id|dev
)paren
suffix:semicolon
macro_line|#else
r_return
op_minus
id|ENODEV
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/*  Try all of the locations that aren&squot;t obviously empty.  This touches&n;    a lot of locations, and is much riskier than the code above. */
r_static
r_int
id|__init
DECL|function|el2_pio_probe
id|el2_pio_probe
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
id|base_addr
op_assign
id|dev
ques
c_cond
id|dev-&gt;base_addr
suffix:colon
l_int|0
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
id|el2_probe1
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
id|i
op_assign
l_int|0
suffix:semicolon
id|netcard_portlist
(braket
id|i
)braket
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|el2_probe1
c_func
(paren
id|dev
comma
id|netcard_portlist
(braket
id|i
)braket
)paren
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
multiline_comment|/* Probe for the Etherlink II card at I/O port base IOADDR,&n;   returning non-zero on success.  If found, set the station&n;   address and memory parameters in DEVICE. */
r_static
r_int
id|__init
DECL|function|el2_probe1
id|el2_probe1
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
id|iobase_reg
comma
id|membase_reg
comma
id|saved_406
comma
id|wordlength
comma
id|retval
suffix:semicolon
r_static
r_int
id|version_printed
suffix:semicolon
r_int
r_int
id|vendor_id
suffix:semicolon
multiline_comment|/* FIXME: code reads ioaddr + 0x400, we request ioaddr + 16 */
r_if
c_cond
(paren
op_logical_neg
id|request_region
c_func
(paren
id|ioaddr
comma
id|EL2_IO_EXTENT
comma
id|dev-&gt;name
)paren
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
multiline_comment|/* Reset and/or avoid any lurking NE2000 */
r_if
c_cond
(paren
id|inb
c_func
(paren
id|ioaddr
op_plus
l_int|0x408
)paren
op_eq
l_int|0xff
)paren
(brace
id|mdelay
c_func
(paren
l_int|1
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
multiline_comment|/* We verify that it&squot;s a 3C503 board by checking the first three octets&n;       of its ethernet address. */
id|iobase_reg
op_assign
id|inb
c_func
(paren
id|ioaddr
op_plus
l_int|0x403
)paren
suffix:semicolon
id|membase_reg
op_assign
id|inb
c_func
(paren
id|ioaddr
op_plus
l_int|0x404
)paren
suffix:semicolon
multiline_comment|/* ASIC location registers should be 0 or have only a single bit set. */
r_if
c_cond
(paren
(paren
id|iobase_reg
op_amp
(paren
id|iobase_reg
op_minus
l_int|1
)paren
)paren
op_logical_or
(paren
id|membase_reg
op_amp
(paren
id|membase_reg
op_minus
l_int|1
)paren
)paren
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
id|saved_406
op_assign
id|inb_p
c_func
(paren
id|ioaddr
op_plus
l_int|0x406
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|ECNTRL_RESET
op_or
id|ECNTRL_THIN
comma
id|ioaddr
op_plus
l_int|0x406
)paren
suffix:semicolon
multiline_comment|/* Reset it... */
id|outb_p
c_func
(paren
id|ECNTRL_THIN
comma
id|ioaddr
op_plus
l_int|0x406
)paren
suffix:semicolon
multiline_comment|/* Map the station addr PROM into the lower I/O ports. We now check&n;       for both the old and new 3Com prefix */
id|outb
c_func
(paren
id|ECNTRL_SAPROM
op_or
id|ECNTRL_THIN
comma
id|ioaddr
op_plus
l_int|0x406
)paren
suffix:semicolon
id|vendor_id
op_assign
id|inb
c_func
(paren
id|ioaddr
)paren
op_star
l_int|0x10000
op_plus
id|inb
c_func
(paren
id|ioaddr
op_plus
l_int|1
)paren
op_star
l_int|0x100
op_plus
id|inb
c_func
(paren
id|ioaddr
op_plus
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|vendor_id
op_ne
id|OLD_3COM_ID
)paren
op_logical_and
(paren
id|vendor_id
op_ne
id|NEW_3COM_ID
)paren
)paren
(brace
multiline_comment|/* Restore the register we frobbed. */
id|outb
c_func
(paren
id|saved_406
comma
id|ioaddr
op_plus
l_int|0x406
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
id|dev-&gt;base_addr
op_assign
id|ioaddr
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
l_string|&quot;3c503: unable to allocate memory for dev-&gt;priv.&bslash;n&quot;
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
id|printk
c_func
(paren
l_string|&quot;%s: 3c503 at i/o base %#3x, node &quot;
comma
id|dev-&gt;name
comma
id|ioaddr
)paren
suffix:semicolon
multiline_comment|/* Retrieve and print the ethernet address. */
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
l_string|&quot; %2.2x&quot;
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
id|i
)paren
)paren
suffix:semicolon
multiline_comment|/* Map the 8390 back into the window. */
id|outb
c_func
(paren
id|ECNTRL_THIN
comma
id|ioaddr
op_plus
l_int|0x406
)paren
suffix:semicolon
multiline_comment|/* Check for EL2/16 as described in tech. man. */
id|outb_p
c_func
(paren
id|E8390_PAGE0
comma
id|ioaddr
op_plus
id|E8390_CMD
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0
comma
id|ioaddr
op_plus
id|EN0_DCFG
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|E8390_PAGE2
comma
id|ioaddr
op_plus
id|E8390_CMD
)paren
suffix:semicolon
id|wordlength
op_assign
id|inb_p
c_func
(paren
id|ioaddr
op_plus
id|EN0_DCFG
)paren
op_amp
id|ENDCFG_WTS
suffix:semicolon
id|outb_p
c_func
(paren
id|E8390_PAGE0
comma
id|ioaddr
op_plus
id|E8390_CMD
)paren
suffix:semicolon
multiline_comment|/* Probe for, turn on and clear the board&squot;s shared memory. */
r_if
c_cond
(paren
id|ei_debug
OG
l_int|2
)paren
id|printk
c_func
(paren
l_string|&quot; memory jumpers %2.2x &quot;
comma
id|membase_reg
)paren
suffix:semicolon
id|outb
c_func
(paren
id|EGACFR_NORM
comma
id|ioaddr
op_plus
l_int|0x405
)paren
suffix:semicolon
multiline_comment|/* Enable RAM */
multiline_comment|/* This should be probed for (or set via an ioctl()) at run-time.&n;       Right now we use a sleazy hack to pass in the interface number&n;       at boot-time via the low bits of the mem_end field.  That value is&n;       unused, and the low bits would be discarded even if it was used. */
macro_line|#if defined(EI8390_THICK) || defined(EL2_AUI)
id|ei_status.interface_num
op_assign
l_int|1
suffix:semicolon
macro_line|#else
id|ei_status.interface_num
op_assign
id|dev-&gt;mem_end
op_amp
l_int|0xf
suffix:semicolon
macro_line|#endif
id|printk
c_func
(paren
l_string|&quot;, using %sternal xcvr.&bslash;n&quot;
comma
id|ei_status.interface_num
op_eq
l_int|0
ques
c_cond
l_string|&quot;in&quot;
suffix:colon
l_string|&quot;ex&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|membase_reg
op_amp
l_int|0xf0
)paren
op_eq
l_int|0
)paren
(brace
id|dev-&gt;mem_start
op_assign
l_int|0
suffix:semicolon
id|ei_status.name
op_assign
l_string|&quot;3c503-PIO&quot;
suffix:semicolon
)brace
r_else
(brace
id|dev-&gt;mem_start
op_assign
(paren
(paren
id|membase_reg
op_amp
l_int|0xc0
)paren
ques
c_cond
l_int|0xD8000
suffix:colon
l_int|0xC8000
)paren
op_plus
(paren
(paren
id|membase_reg
op_amp
l_int|0xA0
)paren
ques
c_cond
l_int|0x4000
suffix:colon
l_int|0
)paren
suffix:semicolon
DECL|macro|EL2_MEMSIZE
mdefine_line|#define EL2_MEMSIZE (EL2_MB1_STOP_PG - EL2_MB1_START_PG)*256
macro_line|#ifdef EL2MEMTEST
multiline_comment|/* This has never found an error, but someone might care.&n;&t;   Note that it only tests the 2nd 8kB on 16kB 3c503/16&n;&t;   cards between card addr. 0x2000 and 0x3fff. */
(brace
multiline_comment|/* Check the card&squot;s memory. */
r_int
r_int
id|mem_base
op_assign
id|dev-&gt;mem_start
suffix:semicolon
r_int
r_int
id|test_val
op_assign
l_int|0xbbadf00d
suffix:semicolon
id|isa_writel
c_func
(paren
l_int|0xba5eba5e
comma
id|mem_base
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
r_sizeof
(paren
id|test_val
)paren
suffix:semicolon
id|i
OL
id|EL2_MEMSIZE
suffix:semicolon
id|i
op_add_assign
r_sizeof
(paren
id|test_val
)paren
)paren
(brace
id|isa_writel
c_func
(paren
id|test_val
comma
id|mem_base
op_plus
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
id|isa_readl
c_func
(paren
id|mem_base
)paren
op_ne
l_int|0xba5eba5e
op_logical_or
id|isa_readl
c_func
(paren
id|mem_base
op_plus
id|i
)paren
op_ne
id|test_val
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;3c503: memory failure or memory address conflict.&bslash;n&quot;
)paren
suffix:semicolon
id|dev-&gt;mem_start
op_assign
l_int|0
suffix:semicolon
id|ei_status.name
op_assign
l_string|&quot;3c503-PIO&quot;
suffix:semicolon
r_break
suffix:semicolon
)brace
id|test_val
op_add_assign
l_int|0x55555555
suffix:semicolon
id|isa_writel
c_func
(paren
l_int|0
comma
id|mem_base
op_plus
id|i
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif  /* EL2MEMTEST */
r_if
c_cond
(paren
id|dev-&gt;mem_start
)paren
id|dev-&gt;mem_end
op_assign
id|dev-&gt;rmem_end
op_assign
id|dev-&gt;mem_start
op_plus
id|EL2_MEMSIZE
suffix:semicolon
r_if
c_cond
(paren
id|wordlength
)paren
(brace
multiline_comment|/* No Tx pages to skip over to get to Rx */
id|dev-&gt;rmem_start
op_assign
id|dev-&gt;mem_start
suffix:semicolon
id|ei_status.name
op_assign
l_string|&quot;3c503/16&quot;
suffix:semicolon
)brace
r_else
(brace
id|dev-&gt;rmem_start
op_assign
id|TX_PAGES
op_star
l_int|256
op_plus
id|dev-&gt;mem_start
suffix:semicolon
id|ei_status.name
op_assign
l_string|&quot;3c503&quot;
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t;Divide up the memory on the card. This is the same regardless of&n;&t;whether shared-mem or PIO is used. For 16 bit cards (16kB RAM),&n;&t;we use the entire 8k of bank1 for an Rx ring. We only use 3k&n;&t;of the bank0 for 2 full size Tx packet slots. For 8 bit cards,&n;&t;(8kB RAM) we use 3kB of bank1 for two Tx slots, and the remaining&n;&t;5kB for an Rx ring.  */
r_if
c_cond
(paren
id|wordlength
)paren
(brace
id|ei_status.tx_start_page
op_assign
id|EL2_MB0_START_PG
suffix:semicolon
id|ei_status.rx_start_page
op_assign
id|EL2_MB1_START_PG
suffix:semicolon
)brace
r_else
(brace
id|ei_status.tx_start_page
op_assign
id|EL2_MB1_START_PG
suffix:semicolon
id|ei_status.rx_start_page
op_assign
id|EL2_MB1_START_PG
op_plus
id|TX_PAGES
suffix:semicolon
)brace
multiline_comment|/* Finish setting the board&squot;s parameters. */
id|ei_status.stop_page
op_assign
id|EL2_MB1_STOP_PG
suffix:semicolon
id|ei_status.word16
op_assign
id|wordlength
suffix:semicolon
id|ei_status.reset_8390
op_assign
op_amp
id|el2_reset_8390
suffix:semicolon
id|ei_status.get_8390_hdr
op_assign
op_amp
id|el2_get_8390_hdr
suffix:semicolon
id|ei_status.block_input
op_assign
op_amp
id|el2_block_input
suffix:semicolon
id|ei_status.block_output
op_assign
op_amp
id|el2_block_output
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
r_else
r_if
c_cond
(paren
id|dev-&gt;irq
OG
l_int|5
op_logical_and
id|dev-&gt;irq
op_ne
l_int|9
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;3c503: configured interrupt %d invalid, will use autoIRQ.&bslash;n&quot;
comma
id|dev-&gt;irq
)paren
suffix:semicolon
id|dev-&gt;irq
op_assign
l_int|0
suffix:semicolon
)brace
id|ei_status.saved_irq
op_assign
id|dev-&gt;irq
suffix:semicolon
id|dev-&gt;open
op_assign
op_amp
id|el2_open
suffix:semicolon
id|dev-&gt;stop
op_assign
op_amp
id|el2_close
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;mem_start
)paren
id|printk
c_func
(paren
l_string|&quot;%s: %s - %dkB RAM, 8kB shared mem window at %#6lx-%#6lx.&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|ei_status.name
comma
(paren
id|wordlength
op_plus
l_int|1
)paren
op_lshift
l_int|3
comma
id|dev-&gt;mem_start
comma
id|dev-&gt;mem_end
op_minus
l_int|1
)paren
suffix:semicolon
r_else
(brace
id|ei_status.tx_start_page
op_assign
id|EL2_MB1_START_PG
suffix:semicolon
id|ei_status.rx_start_page
op_assign
id|EL2_MB1_START_PG
op_plus
id|TX_PAGES
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n%s: %s, %dkB RAM, using programmed I/O (REJUMPER for SHARED MEMORY).&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|ei_status.name
comma
(paren
id|wordlength
op_plus
l_int|1
)paren
op_lshift
l_int|3
)paren
suffix:semicolon
)brace
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
id|EL2_IO_EXTENT
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
"&f;"
r_static
r_int
DECL|function|el2_open
id|el2_open
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_int
id|retval
op_assign
op_minus
id|EAGAIN
suffix:semicolon
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
l_int|5
comma
l_int|9
comma
l_int|3
comma
l_int|4
comma
l_int|0
)brace
suffix:semicolon
r_int
op_star
id|irqp
op_assign
id|irqlist
suffix:semicolon
id|outb
c_func
(paren
id|EGACFR_NORM
comma
id|E33G_GACFR
)paren
suffix:semicolon
multiline_comment|/* Enable RAM and interrupts. */
r_do
(brace
r_if
c_cond
(paren
id|request_irq
(paren
op_star
id|irqp
comma
l_int|NULL
comma
l_int|0
comma
l_string|&quot;bogus&quot;
comma
id|dev
)paren
op_ne
op_minus
id|EBUSY
)paren
(brace
multiline_comment|/* Twinkle the interrupt, and check if it&squot;s seen. */
r_int
r_int
id|cookie
op_assign
id|probe_irq_on
c_func
(paren
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0x04
op_lshift
(paren
(paren
op_star
id|irqp
op_eq
l_int|9
)paren
ques
c_cond
l_int|2
suffix:colon
op_star
id|irqp
)paren
comma
id|E33G_IDCFR
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0x00
comma
id|E33G_IDCFR
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|irqp
op_eq
id|probe_irq_off
c_func
(paren
id|cookie
)paren
multiline_comment|/* It&squot;s a good IRQ line! */
op_logical_and
(paren
(paren
id|retval
op_assign
id|request_irq
c_func
(paren
id|dev-&gt;irq
op_assign
op_star
id|irqp
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
op_eq
l_int|0
)paren
)paren
r_break
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
op_star
op_increment
id|irqp
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|irqp
op_eq
l_int|0
)paren
(brace
id|outb
c_func
(paren
id|EGACFR_IRQOFF
comma
id|E33G_GACFR
)paren
suffix:semicolon
multiline_comment|/* disable interrupts. */
r_return
id|retval
suffix:semicolon
)brace
)brace
r_else
(brace
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
(brace
r_return
id|retval
suffix:semicolon
)brace
)brace
id|el2_init_card
c_func
(paren
id|dev
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
r_int
DECL|function|el2_close
id|el2_close
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
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
id|outb
c_func
(paren
id|EGACFR_IRQOFF
comma
id|E33G_GACFR
)paren
suffix:semicolon
multiline_comment|/* disable interrupts. */
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
multiline_comment|/* This is called whenever we have a unrecoverable failure:&n;       transmit timeout&n;       Bad ring buffer packet header&n; */
r_static
r_void
DECL|function|el2_reset_8390
id|el2_reset_8390
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
(brace
id|printk
c_func
(paren
l_string|&quot;%s: Resetting the 3c503 board...&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%#lx=%#02x %#lx=%#02x %#lx=%#02x...&quot;
comma
id|E33G_IDCFR
comma
id|inb
c_func
(paren
id|E33G_IDCFR
)paren
comma
id|E33G_CNTRL
comma
id|inb
c_func
(paren
id|E33G_CNTRL
)paren
comma
id|E33G_GACFR
comma
id|inb
c_func
(paren
id|E33G_GACFR
)paren
)paren
suffix:semicolon
)brace
id|outb_p
c_func
(paren
id|ECNTRL_RESET
op_or
id|ECNTRL_THIN
comma
id|E33G_CNTRL
)paren
suffix:semicolon
id|ei_status.txing
op_assign
l_int|0
suffix:semicolon
id|outb_p
c_func
(paren
id|ei_status.interface_num
op_eq
l_int|0
ques
c_cond
id|ECNTRL_THIN
suffix:colon
id|ECNTRL_AUI
comma
id|E33G_CNTRL
)paren
suffix:semicolon
id|el2_init_card
c_func
(paren
id|dev
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
l_string|&quot;done&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* Initialize the 3c503 GA registers after a reset. */
r_static
r_void
DECL|function|el2_init_card
id|el2_init_card
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
multiline_comment|/* Unmap the station PROM and select the DIX or BNC connector. */
id|outb_p
c_func
(paren
id|ei_status.interface_num
op_eq
l_int|0
ques
c_cond
id|ECNTRL_THIN
suffix:colon
id|ECNTRL_AUI
comma
id|E33G_CNTRL
)paren
suffix:semicolon
multiline_comment|/* Set ASIC copy of rx&squot;s first and last+1 buffer pages */
multiline_comment|/* These must be the same as in the 8390. */
id|outb
c_func
(paren
id|ei_status.rx_start_page
comma
id|E33G_STARTPG
)paren
suffix:semicolon
id|outb
c_func
(paren
id|ei_status.stop_page
comma
id|E33G_STOPPG
)paren
suffix:semicolon
multiline_comment|/* Point the vector pointer registers somewhere ?harmless?. */
id|outb
c_func
(paren
l_int|0xff
comma
id|E33G_VP2
)paren
suffix:semicolon
multiline_comment|/* Point at the ROM restart location 0xffff0 */
id|outb
c_func
(paren
l_int|0xff
comma
id|E33G_VP1
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x00
comma
id|E33G_VP0
)paren
suffix:semicolon
multiline_comment|/* Turn off all interrupts until we&squot;re opened. */
id|outb_p
c_func
(paren
l_int|0x00
comma
id|dev-&gt;base_addr
op_plus
id|EN0_IMR
)paren
suffix:semicolon
multiline_comment|/* Enable IRQs iff started. */
id|outb
c_func
(paren
id|EGACFR_NORM
comma
id|E33G_GACFR
)paren
suffix:semicolon
multiline_comment|/* Set the interrupt line. */
id|outb_p
c_func
(paren
(paren
l_int|0x04
op_lshift
(paren
id|dev-&gt;irq
op_eq
l_int|9
ques
c_cond
l_int|2
suffix:colon
id|dev-&gt;irq
)paren
)paren
comma
id|E33G_IDCFR
)paren
suffix:semicolon
id|outb_p
c_func
(paren
(paren
id|WRD_COUNT
op_lshift
l_int|1
)paren
comma
id|E33G_DRQCNT
)paren
suffix:semicolon
multiline_comment|/* Set burst size to 8 */
id|outb_p
c_func
(paren
l_int|0x20
comma
id|E33G_DMAAH
)paren
suffix:semicolon
multiline_comment|/* Put a valid addr in the GA DMA */
id|outb_p
c_func
(paren
l_int|0x00
comma
id|E33G_DMAAL
)paren
suffix:semicolon
r_return
suffix:semicolon
multiline_comment|/* We always succeed */
)brace
multiline_comment|/*&n; * Either use the shared memory (if enabled on the board) or put the packet&n; * out through the ASIC FIFO.&n; */
r_static
r_void
DECL|function|el2_block_output
id|el2_block_output
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
r_int
r_int
op_star
id|wrd
suffix:semicolon
r_int
id|boguscount
suffix:semicolon
multiline_comment|/* timeout counter */
r_int
r_int
id|word
suffix:semicolon
multiline_comment|/* temporary for better machine code */
r_if
c_cond
(paren
id|ei_status.word16
)paren
multiline_comment|/* Tx packets go into bank 0 on EL2/16 card */
id|outb
c_func
(paren
id|EGACFR_RSEL
op_or
id|EGACFR_TCM
comma
id|E33G_GACFR
)paren
suffix:semicolon
r_else
id|outb
c_func
(paren
id|EGACFR_NORM
comma
id|E33G_GACFR
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;mem_start
)paren
(brace
multiline_comment|/* Shared memory transfer */
r_int
r_int
id|dest_addr
op_assign
id|dev-&gt;mem_start
op_plus
(paren
(paren
id|start_page
op_minus
id|ei_status.tx_start_page
)paren
op_lshift
l_int|8
)paren
suffix:semicolon
id|isa_memcpy_toio
c_func
(paren
id|dest_addr
comma
id|buf
comma
id|count
)paren
suffix:semicolon
id|outb
c_func
(paren
id|EGACFR_NORM
comma
id|E33G_GACFR
)paren
suffix:semicolon
multiline_comment|/* Back to bank1 in case on bank0 */
r_return
suffix:semicolon
)brace
multiline_comment|/*&n; *  No shared memory, put the packet out the other way.&n; *  Set up then start the internal memory transfer to Tx Start Page&n; */
id|word
op_assign
(paren
r_int
r_int
)paren
id|start_page
suffix:semicolon
id|outb
c_func
(paren
id|word
op_amp
l_int|0xFF
comma
id|E33G_DMAAH
)paren
suffix:semicolon
id|outb
c_func
(paren
id|word
op_rshift
l_int|8
comma
id|E33G_DMAAL
)paren
suffix:semicolon
id|outb_p
c_func
(paren
(paren
id|ei_status.interface_num
ques
c_cond
id|ECNTRL_AUI
suffix:colon
id|ECNTRL_THIN
)paren
op_or
id|ECNTRL_OUTPUT
op_or
id|ECNTRL_START
comma
id|E33G_CNTRL
)paren
suffix:semicolon
multiline_comment|/*&n; *  Here I am going to write data to the FIFO as quickly as possible.&n; *  Note that E33G_FIFOH is defined incorrectly. It is really&n; *  E33G_FIFOL, the lowest port address for both the byte and&n; *  word write. Variable &squot;count&squot; is NOT checked. Caller must supply a&n; *  valid count. Note that I may write a harmless extra byte to the&n; *  8390 if the byte-count was not even.&n; */
id|wrd
op_assign
(paren
r_int
r_int
r_int
op_star
)paren
id|buf
suffix:semicolon
id|count
op_assign
(paren
id|count
op_plus
l_int|1
)paren
op_rshift
l_int|1
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|boguscount
op_assign
l_int|0x1000
suffix:semicolon
r_while
c_loop
(paren
(paren
id|inb
c_func
(paren
id|E33G_STATUS
)paren
op_amp
id|ESTAT_DPRDY
)paren
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|boguscount
op_decrement
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: FIFO blocked in el2_block_output.&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
id|el2_reset_8390
c_func
(paren
id|dev
)paren
suffix:semicolon
r_goto
id|blocked
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|count
OG
id|WRD_COUNT
)paren
(brace
id|outsw
c_func
(paren
id|E33G_FIFOH
comma
id|wrd
comma
id|WRD_COUNT
)paren
suffix:semicolon
id|wrd
op_add_assign
id|WRD_COUNT
suffix:semicolon
id|count
op_sub_assign
id|WRD_COUNT
suffix:semicolon
)brace
r_else
(brace
id|outsw
c_func
(paren
id|E33G_FIFOH
comma
id|wrd
comma
id|count
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|blocked
suffix:colon
suffix:semicolon
id|outb_p
c_func
(paren
id|ei_status.interface_num
op_eq
l_int|0
ques
c_cond
id|ECNTRL_THIN
suffix:colon
id|ECNTRL_AUI
comma
id|E33G_CNTRL
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Read the 4 byte, page aligned 8390 specific header. */
r_static
r_void
DECL|function|el2_get_8390_hdr
id|el2_get_8390_hdr
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
id|boguscount
suffix:semicolon
r_int
r_int
id|hdr_start
op_assign
id|dev-&gt;mem_start
op_plus
(paren
(paren
id|ring_page
op_minus
id|EL2_MB1_START_PG
)paren
op_lshift
l_int|8
)paren
suffix:semicolon
r_int
r_int
id|word
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;mem_start
)paren
(brace
multiline_comment|/* Use the shared memory. */
id|isa_memcpy_fromio
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
r_return
suffix:semicolon
)brace
multiline_comment|/*&n; *  No shared memory, use programmed I/O.&n; */
id|word
op_assign
(paren
r_int
r_int
)paren
id|ring_page
suffix:semicolon
id|outb
c_func
(paren
id|word
op_amp
l_int|0xFF
comma
id|E33G_DMAAH
)paren
suffix:semicolon
id|outb
c_func
(paren
id|word
op_rshift
l_int|8
comma
id|E33G_DMAAL
)paren
suffix:semicolon
id|outb_p
c_func
(paren
(paren
id|ei_status.interface_num
op_eq
l_int|0
ques
c_cond
id|ECNTRL_THIN
suffix:colon
id|ECNTRL_AUI
)paren
op_or
id|ECNTRL_INPUT
op_or
id|ECNTRL_START
comma
id|E33G_CNTRL
)paren
suffix:semicolon
id|boguscount
op_assign
l_int|0x1000
suffix:semicolon
r_while
c_loop
(paren
(paren
id|inb
c_func
(paren
id|E33G_STATUS
)paren
op_amp
id|ESTAT_DPRDY
)paren
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|boguscount
op_decrement
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: FIFO blocked in el2_get_8390_hdr.&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
id|memset
c_func
(paren
id|hdr
comma
l_int|0x00
comma
r_sizeof
(paren
r_struct
id|e8390_pkt_hdr
)paren
)paren
suffix:semicolon
id|el2_reset_8390
c_func
(paren
id|dev
)paren
suffix:semicolon
r_goto
id|blocked
suffix:semicolon
)brace
)brace
id|insw
c_func
(paren
id|E33G_FIFOH
comma
id|hdr
comma
(paren
r_sizeof
(paren
r_struct
id|e8390_pkt_hdr
)paren
)paren
op_rshift
l_int|1
)paren
suffix:semicolon
id|blocked
suffix:colon
suffix:semicolon
id|outb_p
c_func
(paren
id|ei_status.interface_num
op_eq
l_int|0
ques
c_cond
id|ECNTRL_THIN
suffix:colon
id|ECNTRL_AUI
comma
id|E33G_CNTRL
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|el2_block_input
id|el2_block_input
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
id|boguscount
op_assign
l_int|0
suffix:semicolon
r_int
r_int
r_int
op_star
id|buf
suffix:semicolon
r_int
r_int
id|word
suffix:semicolon
r_int
id|end_of_ring
op_assign
id|dev-&gt;rmem_end
suffix:semicolon
multiline_comment|/* Maybe enable shared memory just be to be safe... nahh.*/
r_if
c_cond
(paren
id|dev-&gt;mem_start
)paren
(brace
multiline_comment|/* Use the shared memory. */
id|ring_offset
op_sub_assign
(paren
id|EL2_MB1_START_PG
op_lshift
l_int|8
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;mem_start
op_plus
id|ring_offset
op_plus
id|count
OG
id|end_of_ring
)paren
(brace
multiline_comment|/* We must wrap the input move. */
r_int
id|semi_count
op_assign
id|end_of_ring
op_minus
(paren
id|dev-&gt;mem_start
op_plus
id|ring_offset
)paren
suffix:semicolon
id|isa_memcpy_fromio
c_func
(paren
id|skb-&gt;data
comma
id|dev-&gt;mem_start
op_plus
id|ring_offset
comma
id|semi_count
)paren
suffix:semicolon
id|count
op_sub_assign
id|semi_count
suffix:semicolon
id|isa_memcpy_fromio
c_func
(paren
id|skb-&gt;data
op_plus
id|semi_count
comma
id|dev-&gt;rmem_start
comma
id|count
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Packet is in one chunk -- we can copy + cksum. */
id|isa_eth_io_copy_and_sum
c_func
(paren
id|skb
comma
id|dev-&gt;mem_start
op_plus
id|ring_offset
comma
id|count
comma
l_int|0
)paren
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
multiline_comment|/*&n; *  No shared memory, use programmed I/O.&n; */
id|word
op_assign
(paren
r_int
r_int
)paren
id|ring_offset
suffix:semicolon
id|outb
c_func
(paren
id|word
op_rshift
l_int|8
comma
id|E33G_DMAAH
)paren
suffix:semicolon
id|outb
c_func
(paren
id|word
op_amp
l_int|0xFF
comma
id|E33G_DMAAL
)paren
suffix:semicolon
id|outb_p
c_func
(paren
(paren
id|ei_status.interface_num
op_eq
l_int|0
ques
c_cond
id|ECNTRL_THIN
suffix:colon
id|ECNTRL_AUI
)paren
op_or
id|ECNTRL_INPUT
op_or
id|ECNTRL_START
comma
id|E33G_CNTRL
)paren
suffix:semicolon
multiline_comment|/*&n; *  Here I also try to get data as fast as possible. I am betting that I&n; *  can read one extra byte without clobbering anything in the kernel because&n; *  this would only occur on an odd byte-count and allocation of skb-&gt;data&n; *  is word-aligned. Variable &squot;count&squot; is NOT checked. Caller must check&n; *  for a valid count.&n; *  [This is currently quite safe.... but if one day the 3c503 explodes&n; *   you know where to come looking ;)]&n; */
id|buf
op_assign
(paren
r_int
r_int
r_int
op_star
)paren
id|skb-&gt;data
suffix:semicolon
id|count
op_assign
(paren
id|count
op_plus
l_int|1
)paren
op_rshift
l_int|1
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|boguscount
op_assign
l_int|0x1000
suffix:semicolon
r_while
c_loop
(paren
(paren
id|inb
c_func
(paren
id|E33G_STATUS
)paren
op_amp
id|ESTAT_DPRDY
)paren
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|boguscount
op_decrement
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: FIFO blocked in el2_block_input.&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
id|el2_reset_8390
c_func
(paren
id|dev
)paren
suffix:semicolon
r_goto
id|blocked
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|count
OG
id|WRD_COUNT
)paren
(brace
id|insw
c_func
(paren
id|E33G_FIFOH
comma
id|buf
comma
id|WRD_COUNT
)paren
suffix:semicolon
id|buf
op_add_assign
id|WRD_COUNT
suffix:semicolon
id|count
op_sub_assign
id|WRD_COUNT
suffix:semicolon
)brace
r_else
(brace
id|insw
c_func
(paren
id|E33G_FIFOH
comma
id|buf
comma
id|count
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|blocked
suffix:colon
suffix:semicolon
id|outb_p
c_func
(paren
id|ei_status.interface_num
op_eq
l_int|0
ques
c_cond
id|ECNTRL_THIN
suffix:colon
id|ECNTRL_AUI
comma
id|E33G_CNTRL
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
macro_line|#ifdef MODULE
DECL|macro|MAX_EL2_CARDS
mdefine_line|#define MAX_EL2_CARDS&t;4&t;/* Max number of EL2 cards per module */
DECL|variable|dev_el2
r_static
r_struct
id|net_device
id|dev_el2
(braket
id|MAX_EL2_CARDS
)braket
suffix:semicolon
DECL|variable|io
r_static
r_int
id|io
(braket
id|MAX_EL2_CARDS
)braket
suffix:semicolon
DECL|variable|irq
r_static
r_int
id|irq
(braket
id|MAX_EL2_CARDS
)braket
suffix:semicolon
DECL|variable|xcvr
r_static
r_int
id|xcvr
(braket
id|MAX_EL2_CARDS
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
id|MAX_EL2_CARDS
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
id|MAX_EL2_CARDS
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
id|MAX_EL2_CARDS
)paren
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|io
comma
l_string|&quot;EtherLink II I/O base address(es)&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|irq
comma
l_string|&quot;EtherLink II IRQ number(s) (assigned)&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|xcvr
comma
l_string|&quot;EtherLink II tranceiver(s) (0=internal, 1=external)&quot;
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
id|MAX_EL2_CARDS
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
op_amp
id|dev_el2
(braket
id|this_dev
)braket
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
id|dev-&gt;mem_end
op_assign
id|xcvr
(braket
id|this_dev
)braket
suffix:semicolon
multiline_comment|/* low 4bits = xcvr sel. */
id|dev-&gt;init
op_assign
id|el2_probe
suffix:semicolon
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
l_string|&quot;3c503.c: Presently autoprobing (not recommended) for a single card.&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|register_netdev
c_func
(paren
id|dev
)paren
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;3c503.c: No 3c503 card found (i/o = 0x%x).&bslash;n&quot;
comma
id|io
(braket
id|this_dev
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|found
op_ne
l_int|0
)paren
(brace
multiline_comment|/* Got at least one. */
r_return
l_int|0
suffix:semicolon
)brace
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
id|found
op_increment
suffix:semicolon
)brace
r_return
l_int|0
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
id|MAX_EL2_CARDS
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
op_amp
id|dev_el2
(braket
id|this_dev
)braket
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;priv
op_ne
l_int|NULL
)paren
(brace
r_void
op_star
id|priv
op_assign
id|dev-&gt;priv
suffix:semicolon
multiline_comment|/* NB: el2_close() handles free_irq */
id|release_region
c_func
(paren
id|dev-&gt;base_addr
comma
id|EL2_IO_EXTENT
)paren
suffix:semicolon
id|unregister_netdev
c_func
(paren
id|dev
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|priv
)paren
suffix:semicolon
)brace
)brace
)brace
macro_line|#endif /* MODULE */
"&f;"
multiline_comment|/*&n; * Local variables:&n; *  version-control: t&n; *  kept-new-versions: 5&n; *  c-indent-level: 4&n; * End:&n; */
eof
