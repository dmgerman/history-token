multiline_comment|/* wd.c: A WD80x3 ethernet driver for linux. */
multiline_comment|/*&n;&t;Written 1993-94 by Donald Becker.&n;&n;&t;Copyright 1993 United States Government as represented by the&n;&t;Director, National Security Agency.&n;&n;&t;This software may be used and distributed according to the terms&n;&t;of the GNU General Public License, incorporated herein by reference.&n;&n;&t;The author may be reached as becker@scyld.com, or C/O&n;&t;Scyld Computing Corporation&n;&t;410 Severn Ave., Suite 210&n;&t;Annapolis MD 21403&n;&n;&t;This is a driver for WD8003 and WD8013 &quot;compatible&quot; ethercards.&n;&n;&t;Thanks to Russ Nelson (nelson@crnwyr.com) for loaning me a WD8013.&n;&n;&t;Changelog:&n;&n;&t;Paul Gortmaker&t;: multiple card support for module users, support&n;&t;&t;&t;  for non-standard memory sizes.&n;&n;&n;*/
DECL|variable|version
r_static
r_const
r_char
id|version
(braket
)braket
op_assign
l_string|&quot;wd.c:v1.10 9/23/94 Donald Becker (becker@cesdis.gsfc.nasa.gov)&bslash;n&quot;
suffix:semicolon
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/etherdevice.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &quot;8390.h&quot;
DECL|macro|DRV_NAME
mdefine_line|#define DRV_NAME &quot;wd&quot;
multiline_comment|/* A zero-terminated list of I/O addresses to be probed. */
DECL|variable|__initdata
r_static
r_int
r_int
id|wd_portlist
(braket
)braket
id|__initdata
op_assign
(brace
l_int|0x300
comma
l_int|0x280
comma
l_int|0x380
comma
l_int|0x240
comma
l_int|0
)brace
suffix:semicolon
r_static
r_int
id|wd_probe1
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
id|wd_open
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
id|wd_reset_8390
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
id|wd_get_8390_hdr
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
id|wd_block_input
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
id|wd_block_output
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
r_int
id|wd_close
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
"&f;"
DECL|macro|WD_START_PG
mdefine_line|#define WD_START_PG&t;&t;0x00&t;/* First page of TX buffer */
DECL|macro|WD03_STOP_PG
mdefine_line|#define WD03_STOP_PG&t;0x20&t;/* Last page +1 of RX ring */
DECL|macro|WD13_STOP_PG
mdefine_line|#define WD13_STOP_PG&t;0x40&t;/* Last page +1 of RX ring */
DECL|macro|WD_CMDREG
mdefine_line|#define WD_CMDREG&t;&t;0&t;&t;/* Offset to ASIC command register. */
DECL|macro|WD_RESET
mdefine_line|#define&t; WD_RESET&t;&t;0x80&t;/* Board reset, in WD_CMDREG. */
DECL|macro|WD_MEMENB
mdefine_line|#define&t; WD_MEMENB&t;&t;0x40&t;/* Enable the shared memory. */
DECL|macro|WD_CMDREG5
mdefine_line|#define WD_CMDREG5&t;&t;5&t;&t;/* Offset to 16-bit-only ASIC register 5. */
DECL|macro|ISA16
mdefine_line|#define&t; ISA16&t;&t;&t;0x80&t;/* Enable 16 bit access from the ISA bus. */
DECL|macro|NIC16
mdefine_line|#define&t; NIC16&t;&t;&t;0x40&t;/* Enable 16 bit access from the 8390. */
DECL|macro|WD_NIC_OFFSET
mdefine_line|#define WD_NIC_OFFSET&t;16&t;&t;/* Offset to the 8390 from the base_addr. */
DECL|macro|WD_IO_EXTENT
mdefine_line|#define WD_IO_EXTENT&t;32
"&f;"
multiline_comment|/*&t;Probe for the WD8003 and WD8013.  These cards have the station&n;&t;address PROM at I/O ports &lt;base&gt;+8 to &lt;base&gt;+13, with a checksum&n;&t;following. A Soundblaster can have the same checksum as an WDethercard,&n;&t;so we have an extra exclusionary check for it.&n;&n;&t;The wd_probe1() routine initializes the card and fills the&n;&t;station address field. */
DECL|function|do_wd_probe
r_static
r_int
id|__init
id|do_wd_probe
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
r_struct
id|resource
op_star
id|r
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
r_int
id|mem_start
op_assign
id|dev-&gt;mem_start
suffix:semicolon
r_int
id|mem_end
op_assign
id|dev-&gt;mem_end
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
(brace
multiline_comment|/* Check a user specified location. */
id|r
op_assign
id|request_region
c_func
(paren
id|base_addr
comma
id|WD_IO_EXTENT
comma
l_string|&quot;wd-probe&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r
op_eq
l_int|NULL
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|i
op_assign
id|wd_probe1
c_func
(paren
id|dev
comma
id|base_addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ne
l_int|0
)paren
id|release_region
c_func
(paren
id|base_addr
comma
id|WD_IO_EXTENT
)paren
suffix:semicolon
r_else
id|r-&gt;name
op_assign
id|dev-&gt;name
suffix:semicolon
r_return
id|i
suffix:semicolon
)brace
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
id|wd_portlist
(braket
id|i
)braket
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
id|ioaddr
op_assign
id|wd_portlist
(braket
id|i
)braket
suffix:semicolon
id|r
op_assign
id|request_region
c_func
(paren
id|ioaddr
comma
id|WD_IO_EXTENT
comma
l_string|&quot;wd-probe&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r
op_eq
l_int|NULL
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|wd_probe1
c_func
(paren
id|dev
comma
id|ioaddr
)paren
op_eq
l_int|0
)paren
(brace
id|r-&gt;name
op_assign
id|dev-&gt;name
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|release_region
c_func
(paren
id|ioaddr
comma
id|WD_IO_EXTENT
)paren
suffix:semicolon
id|dev-&gt;irq
op_assign
id|irq
suffix:semicolon
id|dev-&gt;mem_start
op_assign
id|mem_start
suffix:semicolon
id|dev-&gt;mem_end
op_assign
id|mem_end
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
op_minus
id|WD_NIC_OFFSET
comma
id|WD_IO_EXTENT
)paren
suffix:semicolon
)brace
macro_line|#ifndef MODULE
DECL|function|wd_probe
r_struct
id|net_device
op_star
id|__init
id|wd_probe
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
id|do_wd_probe
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
DECL|function|wd_probe1
r_static
r_int
id|__init
id|wd_probe1
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
id|checksum
op_assign
l_int|0
suffix:semicolon
r_int
id|ancient
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* An old card without config registers. */
r_int
id|word16
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* 0 = 8 bit, 1 = 16 bit */
r_const
r_char
op_star
id|model_name
suffix:semicolon
r_static
r_int
id|version_printed
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
id|checksum
op_add_assign
id|inb
c_func
(paren
id|ioaddr
op_plus
l_int|8
op_plus
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inb
c_func
(paren
id|ioaddr
op_plus
l_int|8
)paren
op_eq
l_int|0xff
multiline_comment|/* Extra check to avoid soundcard. */
op_logical_or
id|inb
c_func
(paren
id|ioaddr
op_plus
l_int|9
)paren
op_eq
l_int|0xff
op_logical_or
(paren
id|checksum
op_amp
l_int|0xff
)paren
op_ne
l_int|0xFF
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
multiline_comment|/* Check for semi-valid mem_start/end values if supplied. */
r_if
c_cond
(paren
(paren
id|dev-&gt;mem_start
op_mod
l_int|0x2000
)paren
op_logical_or
(paren
id|dev-&gt;mem_end
op_mod
l_int|0x2000
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;wd.c: user supplied mem_start or mem_end not on 8kB boundary - ignored.&bslash;n&quot;
)paren
suffix:semicolon
id|dev-&gt;mem_start
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;mem_end
op_assign
l_int|0
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
id|printk
c_func
(paren
l_string|&quot;%s: WD80x3 at %#3x,&quot;
comma
id|dev-&gt;name
comma
id|ioaddr
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
l_string|&quot; %2.2X&quot;
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
l_int|8
op_plus
id|i
)paren
)paren
suffix:semicolon
multiline_comment|/* The following PureData probe code was contributed by&n;&t;   Mike Jagdis &lt;jaggy@purplet.demon.co.uk&gt;. Puredata does software&n;&t;   configuration differently from others so we have to check for them.&n;&t;   This detects an 8 bit, 16 bit or dumb (Toshiba, jumpered) card.&n;&t;   */
r_if
c_cond
(paren
id|inb
c_func
(paren
id|ioaddr
op_plus
l_int|0
)paren
op_eq
l_char|&squot;P&squot;
op_logical_and
id|inb
c_func
(paren
id|ioaddr
op_plus
l_int|1
)paren
op_eq
l_char|&squot;D&squot;
)paren
(brace
r_int
r_char
id|reg5
op_assign
id|inb
c_func
(paren
id|ioaddr
op_plus
l_int|5
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|inb
c_func
(paren
id|ioaddr
op_plus
l_int|2
)paren
)paren
(brace
r_case
l_int|0x03
suffix:colon
id|word16
op_assign
l_int|0
suffix:semicolon
id|model_name
op_assign
l_string|&quot;PDI8023-8&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x05
suffix:colon
id|word16
op_assign
l_int|0
suffix:semicolon
id|model_name
op_assign
l_string|&quot;PDUC8023&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x0a
suffix:colon
id|word16
op_assign
l_int|1
suffix:semicolon
id|model_name
op_assign
l_string|&quot;PDI8023-16&quot;
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* Either 0x01 (dumb) or they&squot;ve released a new version. */
r_default
suffix:colon
id|word16
op_assign
l_int|0
suffix:semicolon
id|model_name
op_assign
l_string|&quot;PDI8023&quot;
suffix:semicolon
r_break
suffix:semicolon
)brace
id|dev-&gt;mem_start
op_assign
(paren
(paren
id|reg5
op_amp
l_int|0x1c
)paren
op_plus
l_int|0xc0
)paren
op_lshift
l_int|12
suffix:semicolon
id|dev-&gt;irq
op_assign
(paren
id|reg5
op_amp
l_int|0xe0
)paren
op_eq
l_int|0xe0
ques
c_cond
l_int|10
suffix:colon
(paren
id|reg5
op_rshift
l_int|5
)paren
op_plus
l_int|1
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* End of PureData probe */
multiline_comment|/* This method of checking for a 16-bit board is borrowed from the&n;&t;&t;   we.c driver.  A simpler method is just to look in ASIC reg. 0x03.&n;&t;&t;   I&squot;m comparing the two method in alpha test to make certain they&n;&t;&t;   return the same result. */
multiline_comment|/* Check for the old 8 bit board - it has register 0/8 aliasing.&n;&t;&t;   Do NOT check i&gt;=6 here -- it hangs the old 8003 boards! */
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
id|inb
c_func
(paren
id|ioaddr
op_plus
id|i
)paren
op_ne
id|inb
c_func
(paren
id|ioaddr
op_plus
l_int|8
op_plus
id|i
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ge
l_int|6
)paren
(brace
id|ancient
op_assign
l_int|1
suffix:semicolon
id|model_name
op_assign
l_string|&quot;WD8003-old&quot;
suffix:semicolon
id|word16
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
r_int
id|tmp
op_assign
id|inb
c_func
(paren
id|ioaddr
op_plus
l_int|1
)paren
suffix:semicolon
multiline_comment|/* fiddle with 16bit bit */
id|outb
c_func
(paren
id|tmp
op_xor
l_int|0x01
comma
id|ioaddr
op_plus
l_int|1
)paren
suffix:semicolon
multiline_comment|/* attempt to clear 16bit bit */
r_if
c_cond
(paren
(paren
(paren
id|inb
c_func
(paren
id|ioaddr
op_plus
l_int|1
)paren
op_amp
l_int|0x01
)paren
op_eq
l_int|0x01
)paren
multiline_comment|/* A 16 bit card */
op_logical_and
(paren
id|tmp
op_amp
l_int|0x01
)paren
op_eq
l_int|0x01
)paren
(brace
multiline_comment|/* In a 16 slot. */
r_int
id|asic_reg5
op_assign
id|inb
c_func
(paren
id|ioaddr
op_plus
id|WD_CMDREG5
)paren
suffix:semicolon
multiline_comment|/* Magic to set ASIC to word-wide mode. */
id|outb
c_func
(paren
id|NIC16
op_or
(paren
id|asic_reg5
op_amp
l_int|0x1f
)paren
comma
id|ioaddr
op_plus
id|WD_CMDREG5
)paren
suffix:semicolon
id|outb
c_func
(paren
id|tmp
comma
id|ioaddr
op_plus
l_int|1
)paren
suffix:semicolon
id|model_name
op_assign
l_string|&quot;WD8013&quot;
suffix:semicolon
id|word16
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* We have a 16bit board here! */
)brace
r_else
(brace
id|model_name
op_assign
l_string|&quot;WD8003&quot;
suffix:semicolon
id|word16
op_assign
l_int|0
suffix:semicolon
)brace
id|outb
c_func
(paren
id|tmp
comma
id|ioaddr
op_plus
l_int|1
)paren
suffix:semicolon
multiline_comment|/* Restore original reg1 value. */
)brace
macro_line|#ifndef final_version
r_if
c_cond
(paren
op_logical_neg
id|ancient
op_logical_and
(paren
id|inb
c_func
(paren
id|ioaddr
op_plus
l_int|1
)paren
op_amp
l_int|0x01
)paren
op_ne
(paren
id|word16
op_amp
l_int|0x01
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;&bslash;nWD80?3: Bus width conflict, %d (probe) != %d (reg report).&quot;
comma
id|word16
ques
c_cond
l_int|16
suffix:colon
l_int|8
comma
(paren
id|inb
c_func
(paren
id|ioaddr
op_plus
l_int|1
)paren
op_amp
l_int|0x01
)paren
ques
c_cond
l_int|16
suffix:colon
l_int|8
)paren
suffix:semicolon
macro_line|#endif
)brace
macro_line|#if defined(WD_SHMEM) &amp;&amp; WD_SHMEM &gt; 0x80000
multiline_comment|/* Allow a compile-time override.&t; */
id|dev-&gt;mem_start
op_assign
id|WD_SHMEM
suffix:semicolon
macro_line|#else
r_if
c_cond
(paren
id|dev-&gt;mem_start
op_eq
l_int|0
)paren
(brace
multiline_comment|/* Sanity and old 8003 check */
r_int
id|reg0
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
id|reg0
op_eq
l_int|0xff
op_logical_or
id|reg0
op_eq
l_int|0
)paren
(brace
multiline_comment|/* Future plan: this could check a few likely locations first. */
id|dev-&gt;mem_start
op_assign
l_int|0xd0000
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; assigning address %#lx&quot;
comma
id|dev-&gt;mem_start
)paren
suffix:semicolon
)brace
r_else
(brace
r_int
id|high_addr_bits
op_assign
id|inb
c_func
(paren
id|ioaddr
op_plus
id|WD_CMDREG5
)paren
op_amp
l_int|0x1f
suffix:semicolon
multiline_comment|/* Some boards don&squot;t have the register 5 -- it returns 0xff. */
r_if
c_cond
(paren
id|high_addr_bits
op_eq
l_int|0x1f
op_logical_or
id|word16
op_eq
l_int|0
)paren
id|high_addr_bits
op_assign
l_int|0x01
suffix:semicolon
id|dev-&gt;mem_start
op_assign
(paren
(paren
id|reg0
op_amp
l_int|0x3f
)paren
op_lshift
l_int|13
)paren
op_plus
(paren
id|high_addr_bits
op_lshift
l_int|19
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
multiline_comment|/* The 8390 isn&squot;t at the base address -- the ASIC regs are there! */
id|dev-&gt;base_addr
op_assign
id|ioaddr
op_plus
id|WD_NIC_OFFSET
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
id|irqmap
(braket
)braket
op_assign
(brace
l_int|9
comma
l_int|3
comma
l_int|5
comma
l_int|7
comma
l_int|10
comma
l_int|11
comma
l_int|15
comma
l_int|4
)brace
suffix:semicolon
r_int
id|reg1
op_assign
id|inb
c_func
(paren
id|ioaddr
op_plus
l_int|1
)paren
suffix:semicolon
r_int
id|reg4
op_assign
id|inb
c_func
(paren
id|ioaddr
op_plus
l_int|4
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ancient
op_logical_or
id|reg1
op_eq
l_int|0xff
)paren
(brace
multiline_comment|/* Ack!! No way to read the IRQ! */
r_int
id|nic_addr
op_assign
id|ioaddr
op_plus
id|WD_NIC_OFFSET
suffix:semicolon
r_int
r_int
id|irq_mask
suffix:semicolon
multiline_comment|/* We have an old-style ethercard that doesn&squot;t report its IRQ&n;&t;&t;&t;   line.  Do autoirq to find the IRQ line. Note that this IS NOT&n;&t;&t;&t;   a reliable way to trigger an interrupt. */
id|outb_p
c_func
(paren
id|E8390_NODMA
op_plus
id|E8390_STOP
comma
id|nic_addr
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x00
comma
id|nic_addr
op_plus
id|EN0_IMR
)paren
suffix:semicolon
multiline_comment|/* Disable all intrs. */
id|irq_mask
op_assign
id|probe_irq_on
c_func
(paren
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0xff
comma
id|nic_addr
op_plus
id|EN0_IMR
)paren
suffix:semicolon
multiline_comment|/* Enable all interrupts. */
id|outb_p
c_func
(paren
l_int|0x00
comma
id|nic_addr
op_plus
id|EN0_RCNTLO
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0x00
comma
id|nic_addr
op_plus
id|EN0_RCNTHI
)paren
suffix:semicolon
id|outb
c_func
(paren
id|E8390_RREAD
op_plus
id|E8390_START
comma
id|nic_addr
)paren
suffix:semicolon
multiline_comment|/* Trigger it... */
id|mdelay
c_func
(paren
l_int|20
)paren
suffix:semicolon
id|dev-&gt;irq
op_assign
id|probe_irq_off
c_func
(paren
id|irq_mask
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0x00
comma
id|nic_addr
op_plus
id|EN0_IMR
)paren
suffix:semicolon
multiline_comment|/* Mask all intrs. again. */
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
l_string|&quot; autoirq is %d&quot;
comma
id|dev-&gt;irq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;irq
OL
l_int|2
)paren
id|dev-&gt;irq
op_assign
id|word16
ques
c_cond
l_int|10
suffix:colon
l_int|5
suffix:semicolon
)brace
r_else
id|dev-&gt;irq
op_assign
id|irqmap
(braket
(paren
(paren
id|reg4
op_rshift
l_int|5
)paren
op_amp
l_int|0x03
)paren
op_plus
(paren
id|reg1
op_amp
l_int|0x04
)paren
)braket
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|dev-&gt;irq
op_eq
l_int|2
)paren
multiline_comment|/* Fixup bogosity: IRQ2 is really IRQ9 */
id|dev-&gt;irq
op_assign
l_int|9
suffix:semicolon
multiline_comment|/* Snarf the interrupt now.  There&squot;s no point in waiting since we cannot&n;&t;   share and the board will usually be enabled. */
id|i
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
id|i
)paren
(brace
id|printk
(paren
l_string|&quot; unable to get IRQ %d.&bslash;n&quot;
comma
id|dev-&gt;irq
)paren
suffix:semicolon
r_return
id|i
suffix:semicolon
)brace
multiline_comment|/* OK, were are certain this is going to work.  Setup the device. */
id|ei_status.name
op_assign
id|model_name
suffix:semicolon
id|ei_status.word16
op_assign
id|word16
suffix:semicolon
id|ei_status.tx_start_page
op_assign
id|WD_START_PG
suffix:semicolon
id|ei_status.rx_start_page
op_assign
id|WD_START_PG
op_plus
id|TX_PAGES
suffix:semicolon
multiline_comment|/* Don&squot;t map in the shared memory until the board is actually opened. */
id|ei_status.rmem_start
op_assign
id|dev-&gt;mem_start
op_plus
id|TX_PAGES
op_star
l_int|256
suffix:semicolon
multiline_comment|/* Some cards (eg WD8003EBT) can be jumpered for more (32k!) memory. */
r_if
c_cond
(paren
id|dev-&gt;mem_end
op_ne
l_int|0
)paren
(brace
id|ei_status.stop_page
op_assign
(paren
id|dev-&gt;mem_end
op_minus
id|dev-&gt;mem_start
)paren
op_div
l_int|256
suffix:semicolon
)brace
r_else
(brace
id|ei_status.stop_page
op_assign
id|word16
ques
c_cond
id|WD13_STOP_PG
suffix:colon
id|WD03_STOP_PG
suffix:semicolon
id|dev-&gt;mem_end
op_assign
id|dev-&gt;mem_start
op_plus
(paren
id|ei_status.stop_page
op_minus
id|WD_START_PG
)paren
op_star
l_int|256
suffix:semicolon
)brace
id|ei_status.rmem_end
op_assign
id|dev-&gt;mem_end
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; %s, IRQ %d, shared memory at %#lx-%#lx.&bslash;n&quot;
comma
id|model_name
comma
id|dev-&gt;irq
comma
id|dev-&gt;mem_start
comma
id|dev-&gt;mem_end
op_minus
l_int|1
)paren
suffix:semicolon
id|ei_status.reset_8390
op_assign
op_amp
id|wd_reset_8390
suffix:semicolon
id|ei_status.block_input
op_assign
op_amp
id|wd_block_input
suffix:semicolon
id|ei_status.block_output
op_assign
op_amp
id|wd_block_output
suffix:semicolon
id|ei_status.get_8390_hdr
op_assign
op_amp
id|wd_get_8390_hdr
suffix:semicolon
id|dev-&gt;open
op_assign
op_amp
id|wd_open
suffix:semicolon
id|dev-&gt;stop
op_assign
op_amp
id|wd_close
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
macro_line|#if 1
multiline_comment|/* Enable interrupt generation on softconfig cards -- M.U */
multiline_comment|/* .. but possibly potentially unsafe - Donald */
r_if
c_cond
(paren
id|inb
c_func
(paren
id|ioaddr
op_plus
l_int|14
)paren
op_amp
l_int|0x20
)paren
id|outb
c_func
(paren
id|inb
c_func
(paren
id|ioaddr
op_plus
l_int|4
)paren
op_or
l_int|0x80
comma
id|ioaddr
op_plus
l_int|4
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|wd_open
id|wd_open
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
op_minus
id|WD_NIC_OFFSET
suffix:semicolon
multiline_comment|/* WD_CMDREG */
multiline_comment|/* Map in the shared memory. Always set register 0 last to remain&n;&t; compatible with very old boards. */
id|ei_status.reg0
op_assign
(paren
(paren
id|dev-&gt;mem_start
op_rshift
l_int|13
)paren
op_amp
l_int|0x3f
)paren
op_or
id|WD_MEMENB
suffix:semicolon
id|ei_status.reg5
op_assign
(paren
(paren
id|dev-&gt;mem_start
op_rshift
l_int|19
)paren
op_amp
l_int|0x1f
)paren
op_or
id|NIC16
suffix:semicolon
r_if
c_cond
(paren
id|ei_status.word16
)paren
id|outb
c_func
(paren
id|ei_status.reg5
comma
id|ioaddr
op_plus
id|WD_CMDREG5
)paren
suffix:semicolon
id|outb
c_func
(paren
id|ei_status.reg0
comma
id|ioaddr
)paren
suffix:semicolon
multiline_comment|/* WD_CMDREG */
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
DECL|function|wd_reset_8390
id|wd_reset_8390
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_int
id|wd_cmd_port
op_assign
id|dev-&gt;base_addr
op_minus
id|WD_NIC_OFFSET
suffix:semicolon
multiline_comment|/* WD_CMDREG */
id|outb
c_func
(paren
id|WD_RESET
comma
id|wd_cmd_port
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
l_string|&quot;resetting the WD80x3 t=%lu...&quot;
comma
id|jiffies
)paren
suffix:semicolon
id|ei_status.txing
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Set up the ASIC registers, just in case something changed them. */
id|outb
c_func
(paren
(paren
(paren
(paren
id|dev-&gt;mem_start
op_rshift
l_int|13
)paren
op_amp
l_int|0x3f
)paren
op_or
id|WD_MEMENB
)paren
comma
id|wd_cmd_port
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ei_status.word16
)paren
id|outb
c_func
(paren
id|NIC16
op_or
(paren
(paren
id|dev-&gt;mem_start
op_rshift
l_int|19
)paren
op_amp
l_int|0x1f
)paren
comma
id|wd_cmd_port
op_plus
id|WD_CMDREG5
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
DECL|function|wd_get_8390_hdr
id|wd_get_8390_hdr
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
id|wd_cmdreg
op_assign
id|dev-&gt;base_addr
op_minus
id|WD_NIC_OFFSET
suffix:semicolon
multiline_comment|/* WD_CMDREG */
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
id|WD_START_PG
)paren
op_lshift
l_int|8
)paren
suffix:semicolon
multiline_comment|/* We&squot;ll always get a 4 byte header read followed by a packet read, so&n;&t;   we enable 16 bit mode before the header, and disable after the body. */
r_if
c_cond
(paren
id|ei_status.word16
)paren
id|outb
c_func
(paren
id|ISA16
op_or
id|ei_status.reg5
comma
id|wd_cmdreg
op_plus
id|WD_CMDREG5
)paren
suffix:semicolon
macro_line|#ifdef __BIG_ENDIAN
multiline_comment|/* Officially this is what we are doing, but the readl() is faster */
multiline_comment|/* unfortunately it isn&squot;t endian aware of the struct               */
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
id|hdr-&gt;count
op_assign
id|le16_to_cpu
c_func
(paren
id|hdr-&gt;count
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
id|isa_readl
c_func
(paren
id|hdr_start
)paren
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/* Block input and output are easy on shared memory ethercards, and trivial&n;   on the Western digital card where there is no choice of how to do it.&n;   The only complications are that the ring buffer wraps, and need to map&n;   switch between 8- and 16-bit modes. */
r_static
r_void
DECL|function|wd_block_input
id|wd_block_input
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
id|wd_cmdreg
op_assign
id|dev-&gt;base_addr
op_minus
id|WD_NIC_OFFSET
suffix:semicolon
multiline_comment|/* WD_CMDREG */
r_int
r_int
id|xfer_start
op_assign
id|dev-&gt;mem_start
op_plus
id|ring_offset
op_minus
(paren
id|WD_START_PG
op_lshift
l_int|8
)paren
suffix:semicolon
r_if
c_cond
(paren
id|xfer_start
op_plus
id|count
OG
id|ei_status.rmem_end
)paren
(brace
multiline_comment|/* We must wrap the input move. */
r_int
id|semi_count
op_assign
id|ei_status.rmem_end
op_minus
id|xfer_start
suffix:semicolon
id|isa_memcpy_fromio
c_func
(paren
id|skb-&gt;data
comma
id|xfer_start
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
id|ei_status.rmem_start
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
id|xfer_start
comma
id|count
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/* Turn off 16 bit access so that reboot works.&t; ISA brain-damage */
r_if
c_cond
(paren
id|ei_status.word16
)paren
id|outb
c_func
(paren
id|ei_status.reg5
comma
id|wd_cmdreg
op_plus
id|WD_CMDREG5
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|wd_block_output
id|wd_block_output
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
id|wd_cmdreg
op_assign
id|dev-&gt;base_addr
op_minus
id|WD_NIC_OFFSET
suffix:semicolon
multiline_comment|/* WD_CMDREG */
r_int
id|shmem
op_assign
id|dev-&gt;mem_start
op_plus
(paren
(paren
id|start_page
op_minus
id|WD_START_PG
)paren
op_lshift
l_int|8
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ei_status.word16
)paren
(brace
multiline_comment|/* Turn on and off 16 bit access so that reboot works. */
id|outb
c_func
(paren
id|ISA16
op_or
id|ei_status.reg5
comma
id|wd_cmdreg
op_plus
id|WD_CMDREG5
)paren
suffix:semicolon
id|isa_memcpy_toio
c_func
(paren
id|shmem
comma
id|buf
comma
id|count
)paren
suffix:semicolon
id|outb
c_func
(paren
id|ei_status.reg5
comma
id|wd_cmdreg
op_plus
id|WD_CMDREG5
)paren
suffix:semicolon
)brace
r_else
id|isa_memcpy_toio
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
r_static
r_int
DECL|function|wd_close
id|wd_close
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_int
id|wd_cmdreg
op_assign
id|dev-&gt;base_addr
op_minus
id|WD_NIC_OFFSET
suffix:semicolon
multiline_comment|/* WD_CMDREG */
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
multiline_comment|/* Change from 16-bit to 8-bit shared memory so reboot works. */
r_if
c_cond
(paren
id|ei_status.word16
)paren
id|outb
c_func
(paren
id|ei_status.reg5
comma
id|wd_cmdreg
op_plus
id|WD_CMDREG5
)paren
suffix:semicolon
multiline_comment|/* And disable the shared memory. */
id|outb
c_func
(paren
id|ei_status.reg0
op_amp
op_complement
id|WD_MEMENB
comma
id|wd_cmdreg
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
"&f;"
macro_line|#ifdef MODULE
DECL|macro|MAX_WD_CARDS
mdefine_line|#define MAX_WD_CARDS&t;4&t;/* Max number of wd cards per module */
DECL|variable|dev_wd
r_static
r_struct
id|net_device
op_star
id|dev_wd
(braket
id|MAX_WD_CARDS
)braket
suffix:semicolon
DECL|variable|io
r_static
r_int
id|io
(braket
id|MAX_WD_CARDS
)braket
suffix:semicolon
DECL|variable|irq
r_static
r_int
id|irq
(braket
id|MAX_WD_CARDS
)braket
suffix:semicolon
DECL|variable|mem
r_static
r_int
id|mem
(braket
id|MAX_WD_CARDS
)braket
suffix:semicolon
DECL|variable|mem_end
r_static
r_int
id|mem_end
(braket
id|MAX_WD_CARDS
)braket
suffix:semicolon
multiline_comment|/* for non std. mem size */
id|module_param_array
c_func
(paren
id|io
comma
r_int
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
id|module_param_array
c_func
(paren
id|irq
comma
r_int
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
id|module_param_array
c_func
(paren
id|mem
comma
r_int
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
id|module_param_array
c_func
(paren
id|mem_end
comma
r_int
comma
l_int|NULL
comma
l_int|0
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
l_string|&quot;IRQ number(s) (ignored for PureData boards)&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|mem
comma
l_string|&quot;memory base address(es)(ignored for PureData boards)&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|mem_end
comma
l_string|&quot;memory end address(es)&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;ISA Western Digital wd8003/wd8013 ; SMC Elite, Elite16 ethernet driver&quot;
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
id|MAX_WD_CARDS
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
l_string|&quot;wd.c: Presently autoprobing (not recommended) for a single card.&bslash;n&quot;
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
id|dev-&gt;mem_end
op_assign
id|mem_end
(braket
id|this_dev
)braket
suffix:semicolon
r_if
c_cond
(paren
id|do_wd_probe
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
id|dev_wd
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
l_string|&quot;wd.c: No wd80x3 card found (i/o = 0x%x).&bslash;n&quot;
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
id|MAX_WD_CARDS
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
id|dev_wd
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
