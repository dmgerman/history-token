multiline_comment|/*&n;&t;ne3210.c&n;&n;&t;Linux driver for Novell NE3210 EISA Network Adapter&n;&n;&t;Copyright (C) 1998, Paul Gortmaker.&n;&n;&t;This software may be used and distributed according to the terms&n;&t;of the GNU General Public License, incorporated herein by reference.&n;&n;&t;Information and Code Sources:&n;&n;&t;1) Based upon my other EISA 8390 drivers (lne390, es3210, smc-ultra32)&n;&t;2) The existing myriad of other Linux 8390 drivers by Donald Becker.&n;&t;3) Info for getting IRQ and sh-mem gleaned from the EISA cfg file&n;&n;&t;The NE3210 is an EISA shared memory NS8390 implementation.  Shared &n;&t;memory address &gt; 1MB should work with this driver.&n;&n;&t;Note that the .cfg file (3/11/93, v1.0) has AUI and BNC switched &n;&t;around (or perhaps there are some defective/backwards cards ???)&n;&n;&t;This driver WILL NOT WORK FOR THE NE3200 - it is completely different&n;&t;and does not use an 8390 at all.&n;&n;*/
DECL|variable|version
r_static
r_const
r_char
op_star
id|version
op_assign
l_string|&quot;ne3210.c: Driver revision v0.03, 30/09/98&bslash;n&quot;
suffix:semicolon
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/etherdevice.h&gt;
macro_line|#include &quot;8390.h&quot;
r_int
id|ne3210_probe
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
id|ne3210_probe1
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
id|ne3210_open
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
id|ne3210_close
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
id|ne3210_reset_8390
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
id|ne3210_get_8390_hdr
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
id|ne3210_block_input
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
id|ne3210_block_output
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
DECL|macro|NE3210_START_PG
mdefine_line|#define NE3210_START_PG&t;&t;0x00    /* First page of TX buffer&t;*/
DECL|macro|NE3210_STOP_PG
mdefine_line|#define NE3210_STOP_PG&t;&t;0x80    /* Last page +1 of RX ring&t;*/
DECL|macro|NE3210_ID_PORT
mdefine_line|#define NE3210_ID_PORT&t;&t;0xc80&t;/* Same for all EISA cards &t;*/
DECL|macro|NE3210_IO_EXTENT
mdefine_line|#define NE3210_IO_EXTENT&t;0x20
DECL|macro|NE3210_SA_PROM
mdefine_line|#define NE3210_SA_PROM&t;&t;0x16&t;/* Start of e&squot;net addr.&t;&t;*/
DECL|macro|NE3210_RESET_PORT
mdefine_line|#define NE3210_RESET_PORT&t;0xc84
DECL|macro|NE3210_NIC_OFFSET
mdefine_line|#define NE3210_NIC_OFFSET&t;0x00&t;/* Hello, the 8390 is *here*&t;*/
DECL|macro|NE3210_ADDR0
mdefine_line|#define NE3210_ADDR0&t;&t;0x00&t;/* 3 byte vendor prefix&t;&t;*/
DECL|macro|NE3210_ADDR1
mdefine_line|#define NE3210_ADDR1&t;&t;0x00
DECL|macro|NE3210_ADDR2
mdefine_line|#define NE3210_ADDR2&t;&t;0x1b
DECL|macro|NE3210_ID
mdefine_line|#define NE3210_ID&t;0x0118cc3a&t;/* 0x3acc = 1110 10110 01100 =  nvl */
DECL|macro|NE3210_CFG1
mdefine_line|#define NE3210_CFG1&t;&t;0xc84&t;/* NB: 0xc84 is also &quot;reset&quot; port. */
DECL|macro|NE3210_CFG2
mdefine_line|#define NE3210_CFG2&t;&t;0xc90
multiline_comment|/*&n; *&t;You can OR any of the following bits together and assign it&n; *&t;to NE3210_DEBUG to get verbose driver info during operation.&n; *&t;Currently only the probe one is implemented.&n; */
DECL|macro|NE3210_D_PROBE
mdefine_line|#define NE3210_D_PROBE&t;0x01
DECL|macro|NE3210_D_RX_PKT
mdefine_line|#define NE3210_D_RX_PKT&t;0x02
DECL|macro|NE3210_D_TX_PKT
mdefine_line|#define NE3210_D_TX_PKT&t;0x04
DECL|macro|NE3210_D_IRQ
mdefine_line|#define NE3210_D_IRQ&t;0x08
DECL|macro|NE3210_DEBUG
mdefine_line|#define NE3210_DEBUG&t;0x0
DECL|variable|__initdata
r_static
r_int
r_char
id|irq_map
(braket
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
DECL|variable|__initdata
r_static
r_int
r_int
id|shmem_map
(braket
)braket
id|__initdata
op_assign
(brace
l_int|0xff0
comma
l_int|0xfe0
comma
l_int|0xfff0
comma
l_int|0xd8
comma
l_int|0xffe0
comma
l_int|0xffc0
comma
l_int|0xd0
comma
l_int|0x0
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;Probe for the card. The best way is to read the EISA ID if it&n; *&t;is known. Then we can check the prefix of the station address&n; *&t;PROM for a match against the value assigned to Novell.&n; */
DECL|function|ne3210_probe
r_int
id|__init
id|ne3210_probe
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
id|ne3210_probe1
c_func
(paren
id|dev
comma
id|ioaddr
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
(brace
macro_line|#if NE3210_DEBUG &amp; NE3210_D_PROBE
id|printk
c_func
(paren
l_string|&quot;ne3210-debug: Not an EISA bus. Not probing high ports.&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
multiline_comment|/* EISA spec allows for up to 16 slots, but 8 is typical. */
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
r_if
c_cond
(paren
id|ne3210_probe1
c_func
(paren
id|dev
comma
id|ioaddr
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
DECL|function|ne3210_probe1
r_static
r_int
id|__init
id|ne3210_probe1
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
r_int
id|eisa_id
suffix:semicolon
r_const
r_char
op_star
id|ifmap
(braket
)braket
op_assign
(brace
l_string|&quot;UTP&quot;
comma
l_string|&quot;?&quot;
comma
l_string|&quot;BNC&quot;
comma
l_string|&quot;AUI&quot;
)brace
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|request_region
c_func
(paren
id|dev-&gt;base_addr
comma
id|NE3210_IO_EXTENT
comma
id|dev-&gt;name
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
id|NE3210_ID_PORT
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
macro_line|#if NE3210_DEBUG &amp; NE3210_D_PROBE
id|printk
c_func
(paren
l_string|&quot;ne3210-debug: probe at %#x, ID %#8x&bslash;n&quot;
comma
id|ioaddr
comma
id|inl
c_func
(paren
id|ioaddr
op_plus
id|NE3210_ID_PORT
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;ne3210-debug: config regs: %#x %#x&bslash;n&quot;
comma
id|inb
c_func
(paren
id|ioaddr
op_plus
id|NE3210_CFG1
)paren
comma
id|inb
c_func
(paren
id|ioaddr
op_plus
id|NE3210_CFG2
)paren
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&t;Check the EISA ID of the card. */
id|eisa_id
op_assign
id|inl
c_func
(paren
id|ioaddr
op_plus
id|NE3210_ID_PORT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|eisa_id
op_ne
id|NE3210_ID
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
macro_line|#if 0
multiline_comment|/*&t;Check the vendor ID as well. Not really required. */
r_if
c_cond
(paren
id|inb
c_func
(paren
id|ioaddr
op_plus
id|NE3210_SA_PROM
op_plus
l_int|0
)paren
op_ne
id|NE3210_ADDR0
op_logical_or
id|inb
c_func
(paren
id|ioaddr
op_plus
id|NE3210_SA_PROM
op_plus
l_int|1
)paren
op_ne
id|NE3210_ADDR1
op_logical_or
id|inb
c_func
(paren
id|ioaddr
op_plus
id|NE3210_SA_PROM
op_plus
l_int|2
)paren
op_ne
id|NE3210_ADDR2
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ne3210.c: card not found&quot;
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
id|ETHER_ADDR_LEN
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
id|inb
c_func
(paren
id|ioaddr
op_plus
id|NE3210_SA_PROM
op_plus
id|i
)paren
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot; (invalid prefix).&bslash;n&quot;
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
l_string|&quot;ne3210.c: unable to allocate memory for dev-&gt;priv!&bslash;n&quot;
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
l_string|&quot;ne3210.c: NE3210 in EISA slot %d, media: %s, addr:&quot;
comma
id|ioaddr
op_div
l_int|0x1000
comma
id|ifmap
(braket
id|inb
c_func
(paren
id|ioaddr
op_plus
id|NE3210_CFG2
)paren
op_rshift
l_int|6
)braket
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
id|ETHER_ADDR_LEN
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
(paren
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
id|NE3210_SA_PROM
op_plus
id|i
)paren
)paren
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;.&bslash;nne3210.c: &quot;
)paren
suffix:semicolon
multiline_comment|/* Snarf the interrupt now. CFG file has them all listed as `edge&squot; with share=NO */
r_if
c_cond
(paren
id|dev-&gt;irq
op_eq
l_int|0
)paren
(brace
r_int
r_char
id|irq_reg
op_assign
id|inb
c_func
(paren
id|ioaddr
op_plus
id|NE3210_CFG2
)paren
op_rshift
l_int|3
suffix:semicolon
id|dev-&gt;irq
op_assign
id|irq_map
(braket
id|irq_reg
op_amp
l_int|0x07
)braket
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;using&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* This is useless unless we reprogram the card here too */
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
multiline_comment|/* Doh! */
id|printk
c_func
(paren
l_string|&quot;assigning&quot;
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot; IRQ %d,&quot;
comma
id|dev-&gt;irq
)paren
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
(brace
id|printk
(paren
l_string|&quot; unable to get IRQ %d.&bslash;n&quot;
comma
id|dev-&gt;irq
)paren
suffix:semicolon
r_goto
id|out1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dev-&gt;mem_start
op_eq
l_int|0
)paren
(brace
r_int
r_char
id|mem_reg
op_assign
id|inb
c_func
(paren
id|ioaddr
op_plus
id|NE3210_CFG2
)paren
op_amp
l_int|0x07
suffix:semicolon
id|dev-&gt;mem_start
op_assign
id|shmem_map
(braket
id|mem_reg
)braket
op_star
l_int|0x1000
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; using &quot;
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Should check for value in shmem_map and reprogram the card to use it */
id|dev-&gt;mem_start
op_and_assign
l_int|0xfff8000
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; assigning &quot;
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;%dkB memory at physical address %#lx&bslash;n&quot;
comma
id|NE3210_STOP_PG
op_div
l_int|4
comma
id|dev-&gt;mem_start
)paren
suffix:semicolon
multiline_comment|/*&n;&t;   BEWARE!! Some dain-bramaged EISA SCUs will allow you to put&n;&t;   the card mem within the region covered by `normal&squot; RAM  !!!&n;&t;*/
r_if
c_cond
(paren
id|dev-&gt;mem_start
OG
l_int|1024
op_star
l_int|1024
)paren
(brace
multiline_comment|/* phys addr &gt; 1MB */
r_if
c_cond
(paren
id|dev-&gt;mem_start
OL
id|virt_to_bus
c_func
(paren
id|high_memory
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;ne3210.c: Card RAM overlaps with normal memory!!!&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;ne3210.c: Use EISA SCU to set card memory below 1MB,&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;ne3210.c: or to an address above 0x%lx.&bslash;n&quot;
comma
id|virt_to_bus
c_func
(paren
id|high_memory
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;ne3210.c: Driver NOT installed.&bslash;n&quot;
)paren
suffix:semicolon
id|retval
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|out2
suffix:semicolon
)brace
id|dev-&gt;mem_start
op_assign
(paren
r_int
r_int
)paren
id|ioremap
c_func
(paren
id|dev-&gt;mem_start
comma
id|NE3210_STOP_PG
op_star
l_int|0x100
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;mem_start
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;ne3210.c: Unable to remap card memory above 1MB !!&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;ne3210.c: Try using EISA SCU to set memory below 1MB.&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;ne3210.c: Driver NOT installed.&bslash;n&quot;
)paren
suffix:semicolon
id|retval
op_assign
op_minus
id|EAGAIN
suffix:semicolon
r_goto
id|out2
suffix:semicolon
)brace
id|ei_status.reg0
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Use as remap flag */
id|printk
c_func
(paren
l_string|&quot;ne3210.c: remapped %dkB card memory to virtual address %#lx&bslash;n&quot;
comma
id|NE3210_STOP_PG
op_div
l_int|4
comma
id|dev-&gt;mem_start
)paren
suffix:semicolon
)brace
id|dev-&gt;mem_end
op_assign
id|dev-&gt;rmem_end
op_assign
id|dev-&gt;mem_start
op_plus
(paren
id|NE3210_STOP_PG
op_minus
id|NE3210_START_PG
)paren
op_star
l_int|256
suffix:semicolon
id|dev-&gt;rmem_start
op_assign
id|dev-&gt;mem_start
op_plus
id|TX_PAGES
op_star
l_int|256
suffix:semicolon
multiline_comment|/* The 8390 offset is zero for the NE3210 */
id|dev-&gt;base_addr
op_assign
id|ioaddr
suffix:semicolon
id|ei_status.name
op_assign
l_string|&quot;NE3210&quot;
suffix:semicolon
id|ei_status.tx_start_page
op_assign
id|NE3210_START_PG
suffix:semicolon
id|ei_status.rx_start_page
op_assign
id|NE3210_START_PG
op_plus
id|TX_PAGES
suffix:semicolon
id|ei_status.stop_page
op_assign
id|NE3210_STOP_PG
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
id|ne3210_reset_8390
suffix:semicolon
id|ei_status.block_input
op_assign
op_amp
id|ne3210_block_input
suffix:semicolon
id|ei_status.block_output
op_assign
op_amp
id|ne3210_block_output
suffix:semicolon
id|ei_status.get_8390_hdr
op_assign
op_amp
id|ne3210_get_8390_hdr
suffix:semicolon
id|dev-&gt;open
op_assign
op_amp
id|ne3210_open
suffix:semicolon
id|dev-&gt;stop
op_assign
op_amp
id|ne3210_close
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
id|out2
suffix:colon
id|free_irq
c_func
(paren
id|dev-&gt;irq
comma
id|dev
)paren
suffix:semicolon
id|out1
suffix:colon
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
id|out
suffix:colon
id|release_region
c_func
(paren
id|ioaddr
comma
id|NE3210_IO_EXTENT
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Reset by toggling the &quot;Board Enable&quot; bits (bit 2 and 0).&n; */
DECL|function|ne3210_reset_8390
r_static
r_void
id|ne3210_reset_8390
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
id|outb
c_func
(paren
l_int|0x04
comma
id|ioaddr
op_plus
id|NE3210_RESET_PORT
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
l_string|&quot;%s: resetting the NE3210...&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
id|mdelay
c_func
(paren
l_int|2
)paren
suffix:semicolon
id|ei_status.txing
op_assign
l_int|0
suffix:semicolon
id|outb
c_func
(paren
l_int|0x01
comma
id|ioaddr
op_plus
id|NE3210_RESET_PORT
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
multiline_comment|/*&n; *&t;Note: In the following three functions is the implicit assumption&n; *&t;that the associated memcpy will only use &quot;rep; movsl&quot; as long as&n; *&t;we keep the counts as some multiple of doublewords. This is a&n; *&t;requirement of the hardware, and also prevents us from using&n; *&t;eth_io_copy_and_sum() since we can&squot;t guarantee it will limit&n; *&t;itself to doubleword access.&n; */
multiline_comment|/*&n; *&t;Grab the 8390 specific header. Similar to the block_input routine, but&n; *&t;we don&squot;t need to be concerned with ring wrap as the header will be at&n; *&t;the start of a page, so we optimize accordingly. (A single doubleword.)&n; */
r_static
r_void
DECL|function|ne3210_get_8390_hdr
id|ne3210_get_8390_hdr
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
id|NE3210_START_PG
)paren
op_lshift
l_int|8
)paren
suffix:semicolon
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
(paren
id|hdr-&gt;count
op_plus
l_int|3
)paren
op_amp
op_complement
l_int|3
suffix:semicolon
multiline_comment|/* Round up allocation. */
)brace
multiline_comment|/*&t;&n; *&t;Block input and output are easy on shared memory ethercards, the only&n; *&t;complication is when the ring buffer wraps. The count will already&n; *&t;be rounded up to a doubleword value via ne3210_get_8390_hdr() above.&n; */
DECL|function|ne3210_block_input
r_static
r_void
id|ne3210_block_input
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
id|NE3210_START_PG
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
id|dev-&gt;rmem_end
)paren
(brace
multiline_comment|/* Packet wraps over end of ring buffer. */
r_int
id|semi_count
op_assign
id|dev-&gt;rmem_end
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
id|dev-&gt;rmem_start
comma
id|count
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Packet is in one chunk. */
id|isa_memcpy_fromio
c_func
(paren
id|skb-&gt;data
comma
id|xfer_start
comma
id|count
)paren
suffix:semicolon
)brace
)brace
DECL|function|ne3210_block_output
r_static
r_void
id|ne3210_block_output
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
id|NE3210_START_PG
)paren
op_lshift
l_int|8
)paren
suffix:semicolon
id|count
op_assign
(paren
id|count
op_plus
l_int|3
)paren
op_amp
op_complement
l_int|3
suffix:semicolon
multiline_comment|/* Round up to doubleword */
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
DECL|function|ne3210_open
r_static
r_int
id|ne3210_open
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
DECL|function|ne3210_close
r_static
r_int
id|ne3210_close
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
macro_line|#ifdef MODULE
DECL|macro|MAX_NE3210_CARDS
mdefine_line|#define MAX_NE3210_CARDS&t;4&t;/* Max number of NE3210 cards per module */
DECL|variable|dev_ne3210
r_static
r_struct
id|net_device
id|dev_ne3210
(braket
id|MAX_NE3210_CARDS
)braket
suffix:semicolon
DECL|variable|io
r_static
r_int
id|io
(braket
id|MAX_NE3210_CARDS
)braket
suffix:semicolon
DECL|variable|irq
r_static
r_int
id|irq
(braket
id|MAX_NE3210_CARDS
)braket
suffix:semicolon
DECL|variable|mem
r_static
r_int
id|mem
(braket
id|MAX_NE3210_CARDS
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
id|MAX_NE3210_CARDS
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
id|MAX_NE3210_CARDS
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
id|MAX_NE3210_CARDS
)paren
l_string|&quot;i&quot;
)paren
suffix:semicolon
DECL|function|init_module
r_int
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
id|MAX_NE3210_CARDS
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
id|dev_ne3210
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
id|dev-&gt;mem_start
op_assign
id|mem
(braket
id|this_dev
)braket
suffix:semicolon
id|dev-&gt;init
op_assign
id|ne3210_probe
suffix:semicolon
multiline_comment|/* Default is to only install one card. */
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
l_string|&quot;ne3210.c: No NE3210 card found (i/o = 0x%x).&bslash;n&quot;
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
DECL|function|cleanup_module
r_void
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
id|MAX_NE3210_CARDS
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
id|dev_ne3210
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
id|NE3210_IO_EXTENT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ei_status.reg0
)paren
id|iounmap
c_func
(paren
(paren
r_void
op_star
)paren
id|dev-&gt;mem_start
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
id|dev-&gt;priv
)paren
suffix:semicolon
id|dev-&gt;priv
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
)brace
macro_line|#endif /* MODULE */
eof
