multiline_comment|/* smc-ultra.c: A SMC Ultra ethernet driver for linux. */
multiline_comment|/*&n;&t;This is a driver for the SMC Ultra and SMC EtherEZ ISA ethercards.&n;&n;&t;Written 1993-1998 by Donald Becker.&n;&n;&t;Copyright 1993 United States Government as represented by the&n;&t;Director, National Security Agency.&n;&n;&t;This software may be used and distributed according to the terms&n;&t;of the GNU General Public License, incorporated herein by reference.&n;&n;&t;The author may be reached as becker@scyld.com, or C/O&n;&t;Scyld Computing Corporation&n;&t;410 Severn Ave., Suite 210&n;&t;Annapolis MD 21403&n;&n;&t;This driver uses the cards in the 8390-compatible mode.&n;&t;Most of the run-time complexity is handled by the generic code in&n;&t;8390.c.  The code in this file is responsible for&n;&n;&t;&t;ultra_probe()&t; &t;Detecting and initializing the card.&n;&t;&t;ultra_probe1()&n;&t;&t;ultra_probe_isapnp()&n;&n;&t;&t;ultra_open()&t;&t;The card-specific details of starting, stopping&n;&t;&t;ultra_reset_8390()&t;and resetting the 8390 NIC core.&n;&t;&t;ultra_close()&n;&n;&t;&t;ultra_block_input()&t;&t;Routines for reading and writing blocks of&n;&t;&t;ultra_block_output()&t;packet buffer memory.&n;&t;&t;ultra_pio_input()&n;&t;&t;ultra_pio_output()&n;&n;&t;This driver enables the shared memory only when doing the actual data&n;&t;transfers to avoid a bug in early version of the card that corrupted&n;&t;data transferred by a AHA1542.&n;&n;&t;This driver now supports the programmed-I/O (PIO) data transfer mode of&n;&t;the EtherEZ. It does not use the non-8390-compatible &quot;Altego&quot; mode.&n;&t;That support (if available) is in smc-ez.c.&n;&n;&t;Changelog:&n;&n;&t;Paul Gortmaker&t;: multiple card support for module users.&n;&t;Donald Becker&t;: 4/17/96 PIO support, minor potential problems avoided.&n;&t;Donald Becker&t;: 6/6/96 correctly set auto-wrap bit.&n;&t;Alexander Sotirov : 1/20/01 Added support for ISAPnP cards&n;&n;&t;Note about the ISA PnP support:&n;&n;&t;This driver can not autoprobe for more than one SMC EtherEZ PnP card.&n;&t;You have to configure the second card manually through the /proc/isapnp&n;&t;interface and then load the module with an explicit io=0x___ option.&n;*/
DECL|variable|version
r_static
r_const
r_char
id|version
(braket
)braket
op_assign
l_string|&quot;smc-ultra.c:v2.02 2/3/98 Donald Becker (becker@cesdis.gsfc.nasa.gov)&bslash;n&quot;
suffix:semicolon
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/isapnp.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/etherdevice.h&gt;
macro_line|#include &quot;8390.h&quot;
multiline_comment|/* A zero-terminated list of I/O addresses to be probed. */
DECL|variable|__initdata
r_static
r_int
r_int
id|ultra_portlist
(braket
)braket
id|__initdata
op_assign
(brace
l_int|0x200
comma
l_int|0x220
comma
l_int|0x240
comma
l_int|0x280
comma
l_int|0x300
comma
l_int|0x340
comma
l_int|0x380
comma
l_int|0
)brace
suffix:semicolon
r_int
id|ultra_probe
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
id|ultra_probe1
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
macro_line|#ifdef __ISAPNP__
r_static
r_int
id|ultra_probe_isapnp
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
macro_line|#endif
r_static
r_int
id|ultra_open
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
id|ultra_reset_8390
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
id|ultra_get_8390_hdr
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
id|ultra_block_input
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
id|ultra_block_output
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
suffix:semicolon
r_static
r_void
id|ultra_pio_get_hdr
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
id|ultra_pio_input
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
id|ultra_pio_output
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
suffix:semicolon
r_static
r_int
id|ultra_close_card
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
macro_line|#ifdef __ISAPNP__
DECL|variable|__initdata
r_static
r_struct
id|isapnp_device_id
id|ultra_device_ids
(braket
)braket
id|__initdata
op_assign
(brace
(brace
id|ISAPNP_VENDOR
c_func
(paren
l_char|&squot;S&squot;
comma
l_char|&squot;M&squot;
comma
l_char|&squot;C&squot;
)paren
comma
id|ISAPNP_FUNCTION
c_func
(paren
l_int|0x8416
)paren
comma
id|ISAPNP_VENDOR
c_func
(paren
l_char|&squot;S&squot;
comma
l_char|&squot;M&squot;
comma
l_char|&squot;C&squot;
)paren
comma
id|ISAPNP_FUNCTION
c_func
(paren
l_int|0x8416
)paren
comma
(paren
r_int
)paren
l_string|&quot;SMC EtherEZ (8416)&quot;
)brace
comma
(brace
)brace
multiline_comment|/* terminate list */
)brace
suffix:semicolon
id|MODULE_DEVICE_TABLE
c_func
(paren
id|isapnp
comma
id|ultra_device_ids
)paren
suffix:semicolon
macro_line|#endif
"&f;"
DECL|macro|START_PG
mdefine_line|#define START_PG&t;&t;0x00&t;/* First page of TX buffer */
DECL|macro|ULTRA_CMDREG
mdefine_line|#define ULTRA_CMDREG&t;0&t;&t;/* Offset to ASIC command register. */
DECL|macro|ULTRA_RESET
mdefine_line|#define&t; ULTRA_RESET&t;0x80&t;/* Board reset, in ULTRA_CMDREG. */
DECL|macro|ULTRA_MEMENB
mdefine_line|#define&t; ULTRA_MEMENB&t;0x40&t;/* Enable the shared memory. */
DECL|macro|IOPD
mdefine_line|#define IOPD&t;0x02&t;&t;&t;/* I/O Pipe Data (16 bits), PIO operation. */
DECL|macro|IOPA
mdefine_line|#define IOPA&t;0x07&t;&t;&t;/* I/O Pipe Address for PIO operation. */
DECL|macro|ULTRA_NIC_OFFSET
mdefine_line|#define ULTRA_NIC_OFFSET  16&t;/* NIC register offset from the base_addr. */
DECL|macro|ULTRA_IO_EXTENT
mdefine_line|#define ULTRA_IO_EXTENT 32
DECL|macro|EN0_ERWCNT
mdefine_line|#define EN0_ERWCNT&t;&t;0x08&t;/* Early receive warning count. */
"&f;"
multiline_comment|/*&t;Probe for the Ultra.  This looks like a 8013 with the station&n;&t;address PROM at I/O ports &lt;base&gt;+8 to &lt;base&gt;+13, with a checksum&n;&t;following.&n;*/
DECL|function|ultra_probe
r_int
id|__init
id|ultra_probe
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
id|ultra_probe1
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
macro_line|#ifdef __ISAPNP__
multiline_comment|/* Look for any installed ISAPnP cards */
r_if
c_cond
(paren
id|isapnp_present
c_func
(paren
)paren
op_logical_and
(paren
id|ultra_probe_isapnp
c_func
(paren
id|dev
)paren
op_eq
l_int|0
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;smc-ultra.c: No ISAPnP cards found, trying standard ones...&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|ultra_portlist
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
id|ultra_probe1
c_func
(paren
id|dev
comma
id|ultra_portlist
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
DECL|function|ultra_probe1
r_static
r_int
id|__init
id|ultra_probe1
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
id|retval
suffix:semicolon
r_int
id|checksum
op_assign
l_int|0
suffix:semicolon
r_const
r_char
op_star
id|model_name
suffix:semicolon
r_int
r_char
id|eeprom_irq
op_assign
l_int|0
suffix:semicolon
r_static
r_int
id|version_printed
suffix:semicolon
multiline_comment|/* Values from various config regs. */
r_int
r_char
id|num_pages
comma
id|irqreg
comma
id|addr
comma
id|piomode
suffix:semicolon
r_int
r_char
id|idreg
op_assign
id|inb
c_func
(paren
id|ioaddr
op_plus
l_int|7
)paren
suffix:semicolon
r_int
r_char
id|reg4
op_assign
id|inb
c_func
(paren
id|ioaddr
op_plus
l_int|4
)paren
op_amp
l_int|0x7f
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
id|ULTRA_IO_EXTENT
comma
id|dev-&gt;name
)paren
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
multiline_comment|/* Check the ID nibble. */
r_if
c_cond
(paren
(paren
id|idreg
op_amp
l_int|0xF0
)paren
op_ne
l_int|0x20
multiline_comment|/* SMC Ultra */
op_logical_and
(paren
id|idreg
op_amp
l_int|0xF0
)paren
op_ne
l_int|0x40
)paren
(brace
multiline_comment|/* SMC EtherEZ */
id|retval
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/* Select the station address register set. */
id|outb
c_func
(paren
id|reg4
comma
id|ioaddr
op_plus
l_int|4
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
(paren
id|checksum
op_amp
l_int|0xff
)paren
op_ne
l_int|0xFF
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
id|model_name
op_assign
(paren
id|idreg
op_amp
l_int|0xF0
)paren
op_eq
l_int|0x20
ques
c_cond
l_string|&quot;SMC Ultra&quot;
suffix:colon
l_string|&quot;SMC EtherEZ&quot;
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s: %s at %#3x,&quot;
comma
id|dev-&gt;name
comma
id|model_name
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
multiline_comment|/* Switch from the station address to the alternate register set and&n;&t;   read the useful registers there. */
id|outb
c_func
(paren
l_int|0x80
op_or
id|reg4
comma
id|ioaddr
op_plus
l_int|4
)paren
suffix:semicolon
multiline_comment|/* Enabled FINE16 mode to avoid BIOS ROM width mismatches @ reboot. */
id|outb
c_func
(paren
l_int|0x80
op_or
id|inb
c_func
(paren
id|ioaddr
op_plus
l_int|0x0c
)paren
comma
id|ioaddr
op_plus
l_int|0x0c
)paren
suffix:semicolon
id|piomode
op_assign
id|inb
c_func
(paren
id|ioaddr
op_plus
l_int|0x8
)paren
suffix:semicolon
id|addr
op_assign
id|inb
c_func
(paren
id|ioaddr
op_plus
l_int|0xb
)paren
suffix:semicolon
id|irqreg
op_assign
id|inb
c_func
(paren
id|ioaddr
op_plus
l_int|0xd
)paren
suffix:semicolon
multiline_comment|/* Switch back to the station address register set so that the MS-DOS driver&n;&t;   can find the card after a warm boot. */
id|outb
c_func
(paren
id|reg4
comma
id|ioaddr
op_plus
l_int|4
)paren
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
r_char
id|irqmap
(braket
)braket
op_assign
(brace
l_int|0
comma
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
)brace
suffix:semicolon
r_int
id|irq
suffix:semicolon
multiline_comment|/* The IRQ bits are split. */
id|irq
op_assign
id|irqmap
(braket
(paren
(paren
id|irqreg
op_amp
l_int|0x40
)paren
op_rshift
l_int|4
)paren
op_plus
(paren
(paren
id|irqreg
op_amp
l_int|0x0c
)paren
op_rshift
l_int|2
)paren
)braket
suffix:semicolon
r_if
c_cond
(paren
id|irq
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;, failed to detect IRQ line.&bslash;n&quot;
)paren
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
id|dev-&gt;irq
op_assign
id|irq
suffix:semicolon
id|eeprom_irq
op_assign
l_int|1
suffix:semicolon
)brace
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
l_string|&quot;, no memory for dev-&gt;priv.&bslash;n&quot;
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
multiline_comment|/* The 8390 isn&squot;t at the base address, so fake the offset */
id|dev-&gt;base_addr
op_assign
id|ioaddr
op_plus
id|ULTRA_NIC_OFFSET
suffix:semicolon
(brace
r_int
id|addr_tbl
(braket
l_int|4
)braket
op_assign
(brace
l_int|0x0C0000
comma
l_int|0x0E0000
comma
l_int|0xFC0000
comma
l_int|0xFE0000
)brace
suffix:semicolon
r_int
id|num_pages_tbl
(braket
l_int|4
)braket
op_assign
(brace
l_int|0x20
comma
l_int|0x40
comma
l_int|0x80
comma
l_int|0xff
)brace
suffix:semicolon
id|dev-&gt;mem_start
op_assign
(paren
(paren
id|addr
op_amp
l_int|0x0f
)paren
op_lshift
l_int|13
)paren
op_plus
id|addr_tbl
(braket
(paren
id|addr
op_rshift
l_int|6
)paren
op_amp
l_int|3
)braket
suffix:semicolon
id|num_pages
op_assign
id|num_pages_tbl
(braket
(paren
id|addr
op_rshift
l_int|4
)paren
op_amp
l_int|3
)braket
suffix:semicolon
)brace
id|ei_status.name
op_assign
id|model_name
suffix:semicolon
id|ei_status.word16
op_assign
l_int|1
suffix:semicolon
id|ei_status.tx_start_page
op_assign
id|START_PG
suffix:semicolon
id|ei_status.rx_start_page
op_assign
id|START_PG
op_plus
id|TX_PAGES
suffix:semicolon
id|ei_status.stop_page
op_assign
id|num_pages
suffix:semicolon
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
(paren
id|ei_status.stop_page
op_minus
id|START_PG
)paren
op_star
l_int|256
suffix:semicolon
r_if
c_cond
(paren
id|piomode
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;,%s IRQ %d programmed-I/O mode.&bslash;n&quot;
comma
id|eeprom_irq
ques
c_cond
l_string|&quot;EEPROM&quot;
suffix:colon
l_string|&quot;assigned &quot;
comma
id|dev-&gt;irq
)paren
suffix:semicolon
id|ei_status.block_input
op_assign
op_amp
id|ultra_pio_input
suffix:semicolon
id|ei_status.block_output
op_assign
op_amp
id|ultra_pio_output
suffix:semicolon
id|ei_status.get_8390_hdr
op_assign
op_amp
id|ultra_pio_get_hdr
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;,%s IRQ %d memory %#lx-%#lx.&bslash;n&quot;
comma
id|eeprom_irq
ques
c_cond
l_string|&quot;&quot;
suffix:colon
l_string|&quot;assigned &quot;
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
id|ei_status.block_input
op_assign
op_amp
id|ultra_block_input
suffix:semicolon
id|ei_status.block_output
op_assign
op_amp
id|ultra_block_output
suffix:semicolon
id|ei_status.get_8390_hdr
op_assign
op_amp
id|ultra_get_8390_hdr
suffix:semicolon
)brace
id|ei_status.reset_8390
op_assign
op_amp
id|ultra_reset_8390
suffix:semicolon
id|dev-&gt;open
op_assign
op_amp
id|ultra_open
suffix:semicolon
id|dev-&gt;stop
op_assign
op_amp
id|ultra_close_card
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
id|ULTRA_IO_EXTENT
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
macro_line|#ifdef __ISAPNP__
DECL|function|ultra_probe_isapnp
r_static
r_int
id|__init
id|ultra_probe_isapnp
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
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|ultra_device_ids
(braket
id|i
)braket
dot
id|vendor
op_ne
l_int|0
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|pci_dev
op_star
id|idev
op_assign
l_int|NULL
suffix:semicolon
r_while
c_loop
(paren
(paren
id|idev
op_assign
id|isapnp_find_dev
c_func
(paren
l_int|NULL
comma
id|ultra_device_ids
(braket
id|i
)braket
dot
id|vendor
comma
id|ultra_device_ids
(braket
id|i
)braket
dot
id|function
comma
id|idev
)paren
)paren
)paren
(brace
multiline_comment|/* Avoid already found cards from previous calls */
r_if
c_cond
(paren
id|idev
op_member_access_from_pointer
id|prepare
c_func
(paren
id|idev
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|idev
op_member_access_from_pointer
id|activate
c_func
(paren
id|idev
)paren
)paren
r_continue
suffix:semicolon
multiline_comment|/* if no irq, search for next */
r_if
c_cond
(paren
id|idev-&gt;irq_resource
(braket
l_int|0
)braket
dot
id|start
op_eq
l_int|0
)paren
r_continue
suffix:semicolon
multiline_comment|/* found it */
id|dev-&gt;base_addr
op_assign
id|idev-&gt;resource
(braket
l_int|0
)braket
dot
id|start
suffix:semicolon
id|dev-&gt;irq
op_assign
id|idev-&gt;irq_resource
(braket
l_int|0
)braket
dot
id|start
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;smc-ultra.c: ISAPnP reports %s at i/o %#lx, irq %d.&bslash;n&quot;
comma
(paren
r_char
op_star
)paren
id|ultra_device_ids
(braket
id|i
)braket
dot
id|driver_data
comma
id|dev-&gt;base_addr
comma
id|dev-&gt;irq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ultra_probe1
c_func
(paren
id|dev
comma
id|dev-&gt;base_addr
)paren
op_ne
l_int|0
)paren
(brace
multiline_comment|/* Shouldn&squot;t happen. */
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;smc-ultra.c: Probe of ISAPnP card at %#lx failed.&bslash;n&quot;
comma
id|dev-&gt;base_addr
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
id|ei_status.priv
op_assign
(paren
r_int
r_int
)paren
id|idev
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|idev
)paren
r_continue
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
macro_line|#endif
r_static
r_int
DECL|function|ultra_open
id|ultra_open
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
suffix:semicolon
r_int
id|ioaddr
op_assign
id|dev-&gt;base_addr
op_minus
id|ULTRA_NIC_OFFSET
suffix:semicolon
multiline_comment|/* ASIC addr */
r_int
r_char
id|irq2reg
(braket
)braket
op_assign
(brace
l_int|0
comma
l_int|0
comma
l_int|0x04
comma
l_int|0x08
comma
l_int|0
comma
l_int|0x0C
comma
l_int|0
comma
l_int|0x40
comma
l_int|0
comma
l_int|0x04
comma
l_int|0x44
comma
l_int|0x48
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0x4C
comma
)brace
suffix:semicolon
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
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_return
id|retval
suffix:semicolon
id|outb
c_func
(paren
l_int|0x00
comma
id|ioaddr
)paren
suffix:semicolon
multiline_comment|/* Disable shared memory for safety. */
id|outb
c_func
(paren
l_int|0x80
comma
id|ioaddr
op_plus
l_int|5
)paren
suffix:semicolon
multiline_comment|/* Set the IRQ line. */
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
id|outb
c_func
(paren
(paren
id|inb
c_func
(paren
id|ioaddr
op_plus
l_int|13
)paren
op_amp
op_complement
l_int|0x4C
)paren
op_or
id|irq2reg
(braket
id|dev-&gt;irq
)braket
comma
id|ioaddr
op_plus
l_int|13
)paren
suffix:semicolon
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
op_amp
l_int|0x7f
comma
id|ioaddr
op_plus
l_int|4
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ei_status.block_input
op_eq
op_amp
id|ultra_pio_input
)paren
(brace
id|outb
c_func
(paren
l_int|0x11
comma
id|ioaddr
op_plus
l_int|6
)paren
suffix:semicolon
multiline_comment|/* Enable interrupts and PIO. */
id|outb
c_func
(paren
l_int|0x01
comma
id|ioaddr
op_plus
l_int|0x19
)paren
suffix:semicolon
multiline_comment|/* Enable ring read auto-wrap. */
)brace
r_else
id|outb
c_func
(paren
l_int|0x01
comma
id|ioaddr
op_plus
l_int|6
)paren
suffix:semicolon
multiline_comment|/* Enable interrupts and memory. */
multiline_comment|/* Set the early receive warning level in window 0 high enough not&n;&t;   to receive ERW interrupts. */
id|outb_p
c_func
(paren
id|E8390_NODMA
op_plus
id|E8390_PAGE0
comma
id|dev-&gt;base_addr
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0xff
comma
id|dev-&gt;base_addr
op_plus
id|EN0_ERWCNT
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
DECL|function|ultra_reset_8390
id|ultra_reset_8390
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_int
id|cmd_port
op_assign
id|dev-&gt;base_addr
op_minus
id|ULTRA_NIC_OFFSET
suffix:semicolon
multiline_comment|/* ASIC base addr */
id|outb
c_func
(paren
id|ULTRA_RESET
comma
id|cmd_port
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
l_string|&quot;resetting Ultra, t=%ld...&quot;
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
l_int|0x00
comma
id|cmd_port
)paren
suffix:semicolon
multiline_comment|/* Disable shared memory for safety. */
id|outb
c_func
(paren
l_int|0x80
comma
id|cmd_port
op_plus
l_int|5
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ei_status.block_input
op_eq
op_amp
id|ultra_pio_input
)paren
id|outb
c_func
(paren
l_int|0x11
comma
id|cmd_port
op_plus
l_int|6
)paren
suffix:semicolon
multiline_comment|/* Enable interrupts and PIO. */
r_else
id|outb
c_func
(paren
l_int|0x01
comma
id|cmd_port
op_plus
l_int|6
)paren
suffix:semicolon
multiline_comment|/* Enable interrupts and memory. */
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
DECL|function|ultra_get_8390_hdr
id|ultra_get_8390_hdr
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
r_int
id|hdr_start
op_assign
id|dev-&gt;mem_start
op_plus
(paren
(paren
id|ring_page
op_minus
id|START_PG
)paren
op_lshift
l_int|8
)paren
suffix:semicolon
id|outb
c_func
(paren
id|ULTRA_MEMENB
comma
id|dev-&gt;base_addr
op_minus
id|ULTRA_NIC_OFFSET
)paren
suffix:semicolon
multiline_comment|/* shmem on */
macro_line|#ifdef notdef
multiline_comment|/* Officially this is what we are doing, but the readl() is faster */
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
id|outb
c_func
(paren
l_int|0x00
comma
id|dev-&gt;base_addr
op_minus
id|ULTRA_NIC_OFFSET
)paren
suffix:semicolon
multiline_comment|/* shmem off */
)brace
multiline_comment|/* Block input and output are easy on shared memory ethercards, the only&n;   complication is when the ring buffer wraps. */
r_static
r_void
DECL|function|ultra_block_input
id|ultra_block_input
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
r_int
id|xfer_start
op_assign
id|dev-&gt;mem_start
op_plus
id|ring_offset
op_minus
(paren
id|START_PG
op_lshift
l_int|8
)paren
suffix:semicolon
multiline_comment|/* Enable shared memory. */
id|outb
c_func
(paren
id|ULTRA_MEMENB
comma
id|dev-&gt;base_addr
op_minus
id|ULTRA_NIC_OFFSET
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
id|outb
c_func
(paren
l_int|0x00
comma
id|dev-&gt;base_addr
op_minus
id|ULTRA_NIC_OFFSET
)paren
suffix:semicolon
multiline_comment|/* Disable memory. */
)brace
r_static
r_void
DECL|function|ultra_block_output
id|ultra_block_output
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
id|shmem
op_assign
id|dev-&gt;mem_start
op_plus
(paren
(paren
id|start_page
op_minus
id|START_PG
)paren
op_lshift
l_int|8
)paren
suffix:semicolon
multiline_comment|/* Enable shared memory. */
id|outb
c_func
(paren
id|ULTRA_MEMENB
comma
id|dev-&gt;base_addr
op_minus
id|ULTRA_NIC_OFFSET
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
l_int|0x00
comma
id|dev-&gt;base_addr
op_minus
id|ULTRA_NIC_OFFSET
)paren
suffix:semicolon
multiline_comment|/* Disable memory. */
)brace
multiline_comment|/* The identical operations for programmed I/O cards.&n;   The PIO model is trivial to use: the 16 bit start address is written&n;   byte-sequentially to IOPA, with no intervening I/O operations, and the&n;   data is read or written to the IOPD data port.&n;   The only potential complication is that the address register is shared&n;   and must be always be rewritten between each read/write direction change.&n;   This is no problem for us, as the 8390 code ensures that we are single&n;   threaded. */
DECL|function|ultra_pio_get_hdr
r_static
r_void
id|ultra_pio_get_hdr
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
op_minus
id|ULTRA_NIC_OFFSET
suffix:semicolon
multiline_comment|/* ASIC addr */
id|outb
c_func
(paren
l_int|0x00
comma
id|ioaddr
op_plus
id|IOPA
)paren
suffix:semicolon
multiline_comment|/* Set the address, LSB first. */
id|outb
c_func
(paren
id|ring_page
comma
id|ioaddr
op_plus
id|IOPA
)paren
suffix:semicolon
id|insw
c_func
(paren
id|ioaddr
op_plus
id|IOPD
comma
id|hdr
comma
r_sizeof
(paren
r_struct
id|e8390_pkt_hdr
)paren
op_rshift
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|ultra_pio_input
r_static
r_void
id|ultra_pio_input
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
op_minus
id|ULTRA_NIC_OFFSET
suffix:semicolon
multiline_comment|/* ASIC addr */
r_char
op_star
id|buf
op_assign
id|skb-&gt;data
suffix:semicolon
multiline_comment|/* For now set the address again, although it should already be correct. */
id|outb
c_func
(paren
id|ring_offset
comma
id|ioaddr
op_plus
id|IOPA
)paren
suffix:semicolon
multiline_comment|/* Set the address, LSB first. */
id|outb
c_func
(paren
id|ring_offset
op_rshift
l_int|8
comma
id|ioaddr
op_plus
id|IOPA
)paren
suffix:semicolon
multiline_comment|/* We know skbuffs are padded to at least word alignment. */
id|insw
c_func
(paren
id|ioaddr
op_plus
id|IOPD
comma
id|buf
comma
(paren
id|count
op_plus
l_int|1
)paren
op_rshift
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|ultra_pio_output
r_static
r_void
id|ultra_pio_output
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
id|ioaddr
op_assign
id|dev-&gt;base_addr
op_minus
id|ULTRA_NIC_OFFSET
suffix:semicolon
multiline_comment|/* ASIC addr */
id|outb
c_func
(paren
l_int|0x00
comma
id|ioaddr
op_plus
id|IOPA
)paren
suffix:semicolon
multiline_comment|/* Set the address, LSB first. */
id|outb
c_func
(paren
id|start_page
comma
id|ioaddr
op_plus
id|IOPA
)paren
suffix:semicolon
multiline_comment|/* An extra odd byte is OK here as well. */
id|outsw
c_func
(paren
id|ioaddr
op_plus
id|IOPD
comma
id|buf
comma
(paren
id|count
op_plus
l_int|1
)paren
op_rshift
l_int|1
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|ultra_close_card
id|ultra_close_card
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
id|ULTRA_NIC_OFFSET
suffix:semicolon
multiline_comment|/* CMDREG */
id|netif_stop_queue
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
l_string|&quot;%s: Shutting down ethercard.&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
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
id|NS8390_init
c_func
(paren
id|dev
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* We should someday disable shared memory and change to 8-bit mode&n;&t;   &quot;just in case&quot;... */
r_return
l_int|0
suffix:semicolon
)brace
"&f;"
macro_line|#ifdef MODULE
DECL|macro|MAX_ULTRA_CARDS
mdefine_line|#define MAX_ULTRA_CARDS&t;4&t;/* Max number of Ultra cards per module */
DECL|variable|dev_ultra
r_static
r_struct
id|net_device
id|dev_ultra
(braket
id|MAX_ULTRA_CARDS
)braket
suffix:semicolon
DECL|variable|io
r_static
r_int
id|io
(braket
id|MAX_ULTRA_CARDS
)braket
suffix:semicolon
DECL|variable|irq
r_static
r_int
id|irq
(braket
id|MAX_ULTRA_CARDS
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
id|MAX_ULTRA_CARDS
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
id|MAX_ULTRA_CARDS
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
l_string|&quot;IRQ number(s) (assigned)&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;SMC Ultra/EtherEZ ISA/PnP Ethernet driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|EXPORT_NO_SYMBOLS
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
id|MAX_ULTRA_CARDS
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
id|dev_ultra
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
id|dev-&gt;init
op_assign
id|ultra_probe
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
l_string|&quot;smc-ultra.c: Presently autoprobing (not recommended) for a single card.&bslash;n&quot;
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
l_string|&quot;smc-ultra.c: No SMC Ultra card found (i/o = 0x%x).&bslash;n&quot;
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
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Got at least one. */
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
id|MAX_ULTRA_CARDS
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
id|dev_ultra
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
multiline_comment|/* NB: ultra_close_card() does free_irq */
r_int
id|ioaddr
op_assign
id|dev-&gt;base_addr
op_minus
id|ULTRA_NIC_OFFSET
suffix:semicolon
macro_line|#ifdef __ISAPNP__
r_struct
id|pci_dev
op_star
id|idev
op_assign
(paren
r_struct
id|pci_dev
op_star
)paren
id|ei_status.priv
suffix:semicolon
r_if
c_cond
(paren
id|idev
)paren
id|idev
op_member_access_from_pointer
id|deactivate
c_func
(paren
id|idev
)paren
suffix:semicolon
macro_line|#endif
id|unregister_netdev
c_func
(paren
id|dev
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|ioaddr
comma
id|ULTRA_IO_EXTENT
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|dev-&gt;priv
)paren
suffix:semicolon
)brace
)brace
)brace
macro_line|#endif /* MODULE */
"&f;"
multiline_comment|/*&n; * Local variables:&n; *  compile-command: &quot;gcc -D__KERNEL__ -Wall -O6 -I/usr/src/linux/net/inet -c smc-ultra.c&quot;&n; *  version-control: t&n; *  kept-new-versions: 5&n; *  c-indent-level: 4&n; *  c-basic-offset: 4&n; *  tab-width: 4&n; * End:&n; */
eof
