multiline_comment|/*&n; *  Amiga Linux/m68k and Linux/PPC Zorro NS8390 Ethernet Driver&n; *&n; *  (C) Copyright 1998-2000 by some Elitist 680x0 Users(TM)&n; *&n; *  ---------------------------------------------------------------------------&n; *&n; *  This program is based on all the other NE2000 drivers for Linux&n; *&n; *  ---------------------------------------------------------------------------&n; *&n; *  This file is subject to the terms and conditions of the GNU General Public&n; *  License.  See the file COPYING in the main directory of the Linux&n; *  distribution for more details.&n; *&n; *  ---------------------------------------------------------------------------&n; *&n; *  The Ariadne II and X-Surf are Zorro-II boards containing Realtek RTL8019AS&n; *  Ethernet Controllers.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/etherdevice.h&gt;
macro_line|#include &lt;linux/zorro.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/amigaints.h&gt;
macro_line|#include &lt;asm/amigahw.h&gt;
macro_line|#include &quot;8390.h&quot;
DECL|macro|NE_BASE
mdefine_line|#define NE_BASE&t;&t;(dev-&gt;base_addr)
DECL|macro|NE_CMD
mdefine_line|#define NE_CMD&t;&t;(0x00*2)
DECL|macro|NE_DATAPORT
mdefine_line|#define NE_DATAPORT&t;(0x10*2)&t;/* NatSemi-defined port window offset. */
DECL|macro|NE_RESET
mdefine_line|#define NE_RESET&t;(0x1f*2)&t;/* Issue a read to reset, a write to clear. */
DECL|macro|NE_IO_EXTENT
mdefine_line|#define NE_IO_EXTENT&t;(0x20*2)
DECL|macro|NE_EN0_ISR
mdefine_line|#define NE_EN0_ISR&t;(0x07*2)
DECL|macro|NE_EN0_DCFG
mdefine_line|#define NE_EN0_DCFG&t;(0x0e*2)
DECL|macro|NE_EN0_RSARLO
mdefine_line|#define NE_EN0_RSARLO&t;(0x08*2)
DECL|macro|NE_EN0_RSARHI
mdefine_line|#define NE_EN0_RSARHI&t;(0x09*2)
DECL|macro|NE_EN0_RCNTLO
mdefine_line|#define NE_EN0_RCNTLO&t;(0x0a*2)
DECL|macro|NE_EN0_RXCR
mdefine_line|#define NE_EN0_RXCR&t;(0x0c*2)
DECL|macro|NE_EN0_TXCR
mdefine_line|#define NE_EN0_TXCR&t;(0x0d*2)
DECL|macro|NE_EN0_RCNTHI
mdefine_line|#define NE_EN0_RCNTHI&t;(0x0b*2)
DECL|macro|NE_EN0_IMR
mdefine_line|#define NE_EN0_IMR&t;(0x0f*2)
DECL|macro|NESM_START_PG
mdefine_line|#define NESM_START_PG&t;0x40&t;/* First page of TX buffer */
DECL|macro|NESM_STOP_PG
mdefine_line|#define NESM_STOP_PG&t;0x80&t;/* Last page +1 of RX ring */
DECL|macro|WORDSWAP
mdefine_line|#define WORDSWAP(a)&t;((((a)&gt;&gt;8)&amp;0xff) | ((a)&lt;&lt;8))
DECL|struct|card_info
r_static
r_struct
id|card_info
(brace
DECL|member|id
id|zorro_id
id|id
suffix:semicolon
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|offset
r_int
r_int
id|offset
suffix:semicolon
DECL|variable|__initdata
)brace
id|cards
(braket
)braket
id|__initdata
op_assign
(brace
(brace
id|ZORRO_PROD_VILLAGE_TRONIC_ARIADNE2
comma
l_string|&quot;Ariadne II&quot;
comma
l_int|0x0600
)brace
comma
(brace
id|ZORRO_PROD_INDIVIDUAL_COMPUTERS_X_SURF
comma
l_string|&quot;X-Surf&quot;
comma
l_int|0x8600
)brace
comma
)brace
suffix:semicolon
r_static
r_int
id|__devinit
id|zorro8390_init_one
c_func
(paren
r_struct
id|zorro_dev
op_star
id|z
comma
r_const
r_struct
id|zorro_device_id
op_star
id|ent
)paren
suffix:semicolon
r_static
r_int
id|__devinit
id|zorro8390_init
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
r_int
id|board
comma
r_const
r_char
op_star
id|name
comma
r_int
r_int
id|ioaddr
)paren
suffix:semicolon
r_static
r_int
id|zorro8390_open
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
id|zorro8390_close
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
id|zorro8390_reset_8390
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
id|zorro8390_get_8390_hdr
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
id|zorro8390_block_input
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
id|zorro8390_block_output
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
id|__devexit
id|zorro8390_remove_one
c_func
(paren
r_struct
id|zorro_dev
op_star
id|z
)paren
suffix:semicolon
DECL|variable|__devinitdata
r_static
r_struct
id|zorro_device_id
id|zorro8390_zorro_tbl
(braket
)braket
id|__devinitdata
op_assign
(brace
(brace
id|ZORRO_PROD_VILLAGE_TRONIC_ARIADNE2
comma
)brace
comma
(brace
id|ZORRO_PROD_INDIVIDUAL_COMPUTERS_X_SURF
comma
)brace
comma
(brace
l_int|0
)brace
)brace
suffix:semicolon
DECL|variable|zorro8390_driver
r_static
r_struct
id|zorro_driver
id|zorro8390_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;zorro8390&quot;
comma
dot
id|id_table
op_assign
id|zorro8390_zorro_tbl
comma
dot
id|probe
op_assign
id|zorro8390_init_one
comma
dot
id|remove
op_assign
id|__devexit_p
c_func
(paren
id|zorro8390_remove_one
)paren
comma
)brace
suffix:semicolon
DECL|function|zorro8390_init_one
r_static
r_int
id|__devinit
id|zorro8390_init_one
c_func
(paren
r_struct
id|zorro_dev
op_star
id|z
comma
r_const
r_struct
id|zorro_device_id
op_star
id|ent
)paren
(brace
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
r_int
r_int
id|board
comma
id|ioaddr
suffix:semicolon
r_int
id|err
comma
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|ARRAY_SIZE
c_func
(paren
id|cards
)paren
op_minus
l_int|1
suffix:semicolon
id|i
op_ge
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
r_if
c_cond
(paren
id|z-&gt;id
op_eq
id|cards
(braket
id|i
)braket
dot
id|id
)paren
r_break
suffix:semicolon
id|board
op_assign
id|z-&gt;resource.start
suffix:semicolon
id|ioaddr
op_assign
id|board
op_plus
id|cards
(braket
id|i
)braket
dot
id|offset
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
r_return
op_minus
id|ENOMEM
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
op_logical_neg
id|request_mem_region
c_func
(paren
id|ioaddr
comma
id|NE_IO_EXTENT
op_star
l_int|2
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
op_minus
id|EBUSY
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|err
op_assign
id|zorro8390_init
c_func
(paren
id|dev
comma
id|board
comma
id|cards
(braket
id|i
)braket
dot
id|name
comma
id|ZTWO_VADDR
c_func
(paren
id|ioaddr
)paren
)paren
)paren
)paren
(brace
id|release_mem_region
c_func
(paren
id|ioaddr
comma
id|NE_IO_EXTENT
op_star
l_int|2
)paren
suffix:semicolon
id|free_netdev
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
id|zorro_set_drvdata
c_func
(paren
id|z
comma
id|dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|zorro8390_init
r_static
r_int
id|__devinit
id|zorro8390_init
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
r_int
id|board
comma
r_const
r_char
op_star
id|name
comma
r_int
r_int
id|ioaddr
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
id|err
suffix:semicolon
r_int
r_char
id|SA_prom
(braket
l_int|32
)braket
suffix:semicolon
r_int
id|start_page
comma
id|stop_page
suffix:semicolon
r_static
id|u32
id|zorro8390_offsets
(braket
l_int|16
)braket
op_assign
(brace
l_int|0x00
comma
l_int|0x02
comma
l_int|0x04
comma
l_int|0x06
comma
l_int|0x08
comma
l_int|0x0a
comma
l_int|0x0c
comma
l_int|0x0e
comma
l_int|0x10
comma
l_int|0x12
comma
l_int|0x14
comma
l_int|0x16
comma
l_int|0x18
comma
l_int|0x1a
comma
l_int|0x1c
comma
l_int|0x1e
comma
)brace
suffix:semicolon
multiline_comment|/* Reset card. Who knows what dain-bramaged state it was left in. */
(brace
r_int
r_int
id|reset_start_time
op_assign
id|jiffies
suffix:semicolon
id|z_writeb
c_func
(paren
id|z_readb
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
id|z_readb
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
id|z_writeb
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
multiline_comment|/* Read the 16 bytes of station address PROM.&n;       We must first initialize registers, similar to NS8390_init(eifdev, 0).&n;       We can&squot;t reliably read the SAPROM address without this.&n;       (I learned the hard way!). */
(brace
r_struct
(brace
id|u32
id|value
suffix:semicolon
id|u32
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
id|z_writeb
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
l_int|16
suffix:semicolon
id|i
op_increment
)paren
(brace
id|SA_prom
(braket
id|i
)braket
op_assign
id|z_readb
c_func
(paren
id|ioaddr
op_plus
id|NE_DATAPORT
)paren
suffix:semicolon
(paren
r_void
)paren
id|z_readb
c_func
(paren
id|ioaddr
op_plus
id|NE_DATAPORT
)paren
suffix:semicolon
)brace
multiline_comment|/* We must set the 8390 for word mode. */
id|z_writeb
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
id|dev-&gt;base_addr
op_assign
id|ioaddr
suffix:semicolon
id|dev-&gt;irq
op_assign
id|IRQ_AMIGA_PORTS
suffix:semicolon
multiline_comment|/* Install the Interrupt handler */
id|i
op_assign
id|request_irq
c_func
(paren
id|IRQ_AMIGA_PORTS
comma
id|ei_interrupt
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
macro_line|#ifdef DEBUG
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
macro_line|#endif
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
l_string|&quot;%s: %s at 0x%08lx, Ethernet Address &quot;
l_string|&quot;%02x:%02x:%02x:%02x:%02x:%02x&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|name
comma
id|board
comma
id|dev-&gt;dev_addr
(braket
l_int|0
)braket
comma
id|dev-&gt;dev_addr
(braket
l_int|1
)braket
comma
id|dev-&gt;dev_addr
(braket
l_int|2
)braket
comma
id|dev-&gt;dev_addr
(braket
l_int|3
)braket
comma
id|dev-&gt;dev_addr
(braket
l_int|4
)braket
comma
id|dev-&gt;dev_addr
(braket
l_int|5
)braket
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
l_int|1
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
id|zorro8390_reset_8390
suffix:semicolon
id|ei_status.block_input
op_assign
op_amp
id|zorro8390_block_input
suffix:semicolon
id|ei_status.block_output
op_assign
op_amp
id|zorro8390_block_output
suffix:semicolon
id|ei_status.get_8390_hdr
op_assign
op_amp
id|zorro8390_get_8390_hdr
suffix:semicolon
id|ei_status.reg_offset
op_assign
id|zorro8390_offsets
suffix:semicolon
id|dev-&gt;open
op_assign
op_amp
id|zorro8390_open
suffix:semicolon
id|dev-&gt;stop
op_assign
op_amp
id|zorro8390_close
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
id|free_irq
c_func
(paren
id|IRQ_AMIGA_PORTS
comma
id|dev
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|zorro8390_open
r_static
r_int
id|zorro8390_open
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
DECL|function|zorro8390_close
r_static
r_int
id|zorro8390_close
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
DECL|function|zorro8390_reset_8390
r_static
r_void
id|zorro8390_reset_8390
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
id|z_writeb
c_func
(paren
id|z_readb
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
id|z_readb
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
id|z_writeb
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
DECL|function|zorro8390_get_8390_hdr
r_static
r_void
id|zorro8390_get_8390_hdr
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
l_string|&quot;[DMAstat:%d][irqlock:%d].&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|ei_status.dmaing
comma
id|ei_status.irqlock
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|ei_status.dmaing
op_or_assign
l_int|0x01
suffix:semicolon
id|z_writeb
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
id|z_writeb
c_func
(paren
id|ENISR_RDC
comma
id|nic_base
op_plus
id|NE_EN0_ISR
)paren
suffix:semicolon
id|z_writeb
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
id|z_writeb
c_func
(paren
l_int|0
comma
id|nic_base
op_plus
id|NE_EN0_RCNTHI
)paren
suffix:semicolon
id|z_writeb
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
id|z_writeb
c_func
(paren
id|ring_page
comma
id|nic_base
op_plus
id|NE_EN0_RSARHI
)paren
suffix:semicolon
id|z_writeb
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
op_star
id|ptrs
op_increment
op_assign
id|z_readw
c_func
(paren
id|NE_BASE
op_plus
id|NE_DATAPORT
)paren
suffix:semicolon
id|z_writeb
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
id|hdr-&gt;count
op_assign
id|WORDSWAP
c_func
(paren
id|hdr-&gt;count
)paren
suffix:semicolon
id|ei_status.dmaing
op_and_assign
op_complement
l_int|0x01
suffix:semicolon
)brace
multiline_comment|/* Block input and output, similar to the Crynwr packet driver.  If you&n;   are porting to a new ethercard, look at the packet driver source for hints.&n;   The NEx000 doesn&squot;t share the on-board packet memory -- you have to put&n;   the packet out through the &quot;remote DMA&quot; dataport using z_writeb. */
DECL|function|zorro8390_block_input
r_static
r_void
id|zorro8390_block_input
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
l_string|&quot;[DMAstat:%d][irqlock:%d].&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|ei_status.dmaing
comma
id|ei_status.irqlock
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|ei_status.dmaing
op_or_assign
l_int|0x01
suffix:semicolon
id|z_writeb
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
id|z_writeb
c_func
(paren
id|ENISR_RDC
comma
id|nic_base
op_plus
id|NE_EN0_ISR
)paren
suffix:semicolon
id|z_writeb
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
id|z_writeb
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
id|z_writeb
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
id|z_writeb
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
id|z_writeb
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
id|z_readw
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
id|buf
(braket
id|count
op_minus
l_int|1
)braket
op_assign
id|z_readb
c_func
(paren
id|NE_BASE
op_plus
id|NE_DATAPORT
)paren
suffix:semicolon
id|z_writeb
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
DECL|function|zorro8390_block_output
r_static
r_void
id|zorro8390_block_output
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
id|count
op_amp
l_int|0x01
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
l_string|&quot;[DMAstat:%d][irqlock:%d]&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|ei_status.dmaing
comma
id|ei_status.irqlock
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
id|z_writeb
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
id|z_writeb
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
id|z_writeb
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
id|z_writeb
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
id|z_writeb
c_func
(paren
l_int|0x00
comma
id|nic_base
op_plus
id|NE_EN0_RSARLO
)paren
suffix:semicolon
id|z_writeb
c_func
(paren
id|start_page
comma
id|nic_base
op_plus
id|NE_EN0_RSARHI
)paren
suffix:semicolon
id|z_writeb
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
id|z_writew
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
id|dma_start
op_assign
id|jiffies
suffix:semicolon
r_while
c_loop
(paren
(paren
id|z_readb
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
id|zorro8390_reset_8390
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
id|z_writeb
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
DECL|function|zorro8390_remove_one
r_static
r_void
id|__devexit
id|zorro8390_remove_one
c_func
(paren
r_struct
id|zorro_dev
op_star
id|z
)paren
(brace
r_struct
id|net_device
op_star
id|dev
op_assign
id|zorro_get_drvdata
c_func
(paren
id|z
)paren
suffix:semicolon
id|unregister_netdev
c_func
(paren
id|dev
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
id|release_mem_region
c_func
(paren
id|ZTWO_PADDR
c_func
(paren
id|dev-&gt;base_addr
)paren
comma
id|NE_IO_EXTENT
op_star
l_int|2
)paren
suffix:semicolon
id|free_netdev
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
DECL|function|zorro8390_init_module
r_static
r_int
id|__init
id|zorro8390_init_module
c_func
(paren
r_void
)paren
(brace
r_return
id|zorro_module_init
c_func
(paren
op_amp
id|zorro8390_driver
)paren
suffix:semicolon
)brace
DECL|function|zorro8390_cleanup_module
r_static
r_void
id|__exit
id|zorro8390_cleanup_module
c_func
(paren
r_void
)paren
(brace
id|zorro_unregister_driver
c_func
(paren
op_amp
id|zorro8390_driver
)paren
suffix:semicolon
)brace
DECL|variable|zorro8390_init_module
id|module_init
c_func
(paren
id|zorro8390_init_module
)paren
suffix:semicolon
DECL|variable|zorro8390_cleanup_module
id|module_exit
c_func
(paren
id|zorro8390_cleanup_module
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
