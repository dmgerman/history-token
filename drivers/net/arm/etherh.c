multiline_comment|/*&n; *  linux/drivers/acorn/net/etherh.c&n; *&n; *  Copyright (C) 2000-2002 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * NS8390 I-cubed EtherH and ANT EtherM specific driver&n; * Thanks to I-Cubed for information on their cards.&n; * EtherM conversion (C) 1999 Chris Kemp and Tim Watterton&n; * EtherM integration (C) 2000 Aleph One Ltd (Tak-Shing Chan)&n; * EtherM integration re-engineered by Russell King.&n; *&n; * Changelog:&n; *  08-12-1996&t;RMK&t;1.00&t;Created&n; *&t;&t;RMK&t;1.03&t;Added support for EtherLan500 cards&n; *  23-11-1997&t;RMK&t;1.04&t;Added media autodetection&n; *  16-04-1998&t;RMK&t;1.05&t;Improved media autodetection&n; *  10-02-2000&t;RMK&t;1.06&t;Updated for 2.3.43&n; *  13-05-2000&t;RMK&t;1.07&t;Updated for 2.3.99-pre8&n; *  12-10-1999  CK/TEW&t;&t;EtherM driver first release&n; *  21-12-2000&t;TTC&t;&t;EtherH/EtherM integration&n; *  25-12-2000&t;RMK&t;1.08&t;Clean integration of EtherM into this driver.&n; *  03-01-2002&t;RMK&t;1.09&t;Always enable IRQs if we&squot;re in the nic slot.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/etherdevice.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/ecard.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &quot;../8390.h&quot;
DECL|macro|NET_DEBUG
mdefine_line|#define NET_DEBUG  0
DECL|macro|DEBUG_INIT
mdefine_line|#define DEBUG_INIT 2
DECL|variable|net_debug
r_static
r_int
r_int
id|net_debug
op_assign
id|NET_DEBUG
suffix:semicolon
DECL|struct|etherh_priv
r_struct
id|etherh_priv
(brace
DECL|member|eidev
r_struct
id|ei_device
id|eidev
suffix:semicolon
DECL|member|id
r_int
r_int
id|id
suffix:semicolon
DECL|member|ctrl_port
r_int
r_int
id|ctrl_port
suffix:semicolon
DECL|member|ctrl
r_int
r_int
id|ctrl
suffix:semicolon
)brace
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Russell King&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;EtherH/EtherM driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|__initdata
r_static
r_char
id|version
(braket
)braket
id|__initdata
op_assign
l_string|&quot;EtherH/EtherM Driver (c) 2002 Russell King v1.09&bslash;n&quot;
suffix:semicolon
DECL|macro|ETHERH500_DATAPORT
mdefine_line|#define ETHERH500_DATAPORT&t;0x200&t;/* MEMC */
DECL|macro|ETHERH500_NS8390
mdefine_line|#define ETHERH500_NS8390&t;0x000&t;/* MEMC */
DECL|macro|ETHERH500_CTRLPORT
mdefine_line|#define ETHERH500_CTRLPORT&t;0x200&t;/* IOC  */
DECL|macro|ETHERH600_DATAPORT
mdefine_line|#define ETHERH600_DATAPORT&t;16&t;/* MEMC */
DECL|macro|ETHERH600_NS8390
mdefine_line|#define ETHERH600_NS8390&t;0x200&t;/* MEMC */
DECL|macro|ETHERH600_CTRLPORT
mdefine_line|#define ETHERH600_CTRLPORT&t;0x080&t;/* MEMC */
DECL|macro|ETHERH_CP_IE
mdefine_line|#define ETHERH_CP_IE&t;&t;1
DECL|macro|ETHERH_CP_IF
mdefine_line|#define ETHERH_CP_IF&t;&t;2
DECL|macro|ETHERH_CP_HEARTBEAT
mdefine_line|#define ETHERH_CP_HEARTBEAT&t;2
DECL|macro|ETHERH_TX_START_PAGE
mdefine_line|#define ETHERH_TX_START_PAGE&t;1
DECL|macro|ETHERH_STOP_PAGE
mdefine_line|#define ETHERH_STOP_PAGE&t;127
multiline_comment|/*&n; * These came from CK/TEW&n; */
DECL|macro|ETHERM_DATAPORT
mdefine_line|#define ETHERM_DATAPORT&t;&t;0x080&t;/* MEMC */
DECL|macro|ETHERM_NS8390
mdefine_line|#define ETHERM_NS8390&t;&t;0x200&t;/* MEMC */
DECL|macro|ETHERM_CTRLPORT
mdefine_line|#define ETHERM_CTRLPORT&t;&t;0x08f&t;/* MEMC */
DECL|macro|ETHERM_TX_START_PAGE
mdefine_line|#define ETHERM_TX_START_PAGE&t;64
DECL|macro|ETHERM_STOP_PAGE
mdefine_line|#define ETHERM_STOP_PAGE&t;127
multiline_comment|/* ------------------------------------------------------------------------ */
DECL|function|etherh_set_ctrl
r_static
r_inline
r_void
id|etherh_set_ctrl
c_func
(paren
r_struct
id|etherh_priv
op_star
id|eh
comma
r_int
r_int
id|mask
)paren
(brace
id|eh-&gt;ctrl
op_or_assign
id|mask
suffix:semicolon
id|outb
c_func
(paren
id|eh-&gt;ctrl
comma
id|eh-&gt;ctrl_port
)paren
suffix:semicolon
)brace
DECL|function|etherh_clr_ctrl
r_static
r_inline
r_void
id|etherh_clr_ctrl
c_func
(paren
r_struct
id|etherh_priv
op_star
id|eh
comma
r_int
r_int
id|mask
)paren
(brace
id|eh-&gt;ctrl
op_and_assign
op_complement
id|mask
suffix:semicolon
id|outb
c_func
(paren
id|eh-&gt;ctrl
comma
id|eh-&gt;ctrl_port
)paren
suffix:semicolon
)brace
DECL|function|etherh_get_stat
r_static
r_inline
r_int
r_int
id|etherh_get_stat
c_func
(paren
r_struct
id|etherh_priv
op_star
id|eh
)paren
(brace
r_return
id|inb
c_func
(paren
id|eh-&gt;ctrl_port
)paren
suffix:semicolon
)brace
DECL|function|etherh_irq_enable
r_static
r_void
id|etherh_irq_enable
c_func
(paren
id|ecard_t
op_star
id|ec
comma
r_int
id|irqnr
)paren
(brace
r_struct
id|etherh_priv
op_star
id|eh
op_assign
id|ec-&gt;irq_data
suffix:semicolon
id|etherh_set_ctrl
c_func
(paren
id|eh
comma
id|ETHERH_CP_IE
)paren
suffix:semicolon
)brace
DECL|function|etherh_irq_disable
r_static
r_void
id|etherh_irq_disable
c_func
(paren
id|ecard_t
op_star
id|ec
comma
r_int
id|irqnr
)paren
(brace
r_struct
id|etherh_priv
op_star
id|eh
op_assign
id|ec-&gt;irq_data
suffix:semicolon
id|etherh_clr_ctrl
c_func
(paren
id|eh
comma
id|ETHERH_CP_IE
)paren
suffix:semicolon
)brace
DECL|variable|etherh_ops
r_static
id|expansioncard_ops_t
id|etherh_ops
op_assign
(brace
dot
id|irqenable
op_assign
id|etherh_irq_enable
comma
dot
id|irqdisable
op_assign
id|etherh_irq_disable
comma
)brace
suffix:semicolon
r_static
r_void
DECL|function|etherh_setif
id|etherh_setif
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|etherh_priv
op_star
id|eh
op_assign
(paren
r_struct
id|etherh_priv
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
r_struct
id|ei_device
op_star
id|ei_local
op_assign
op_amp
id|eh-&gt;eidev
suffix:semicolon
r_int
r_int
id|addr
comma
id|flags
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
multiline_comment|/* set the interface type */
r_switch
c_cond
(paren
id|eh-&gt;id
)paren
(brace
r_case
id|PROD_I3_ETHERLAN600
suffix:colon
r_case
id|PROD_I3_ETHERLAN600A
suffix:colon
id|addr
op_assign
id|dev-&gt;base_addr
op_plus
id|EN0_RCNTHI
suffix:semicolon
r_switch
c_cond
(paren
id|dev-&gt;if_port
)paren
(brace
r_case
id|IF_PORT_10BASE2
suffix:colon
id|outb
c_func
(paren
(paren
id|inb
c_func
(paren
id|addr
)paren
op_amp
l_int|0xf8
)paren
op_or
l_int|1
comma
id|addr
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IF_PORT_10BASET
suffix:colon
id|outb
c_func
(paren
(paren
id|inb
c_func
(paren
id|addr
)paren
op_amp
l_int|0xf8
)paren
comma
id|addr
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|PROD_I3_ETHERLAN500
suffix:colon
r_switch
c_cond
(paren
id|dev-&gt;if_port
)paren
(brace
r_case
id|IF_PORT_10BASE2
suffix:colon
id|etherh_clr_ctrl
c_func
(paren
id|eh
comma
id|ETHERH_CP_IF
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IF_PORT_10BASET
suffix:colon
id|etherh_set_ctrl
c_func
(paren
id|eh
comma
id|ETHERH_CP_IF
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|etherh_getifstat
id|etherh_getifstat
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|etherh_priv
op_star
id|eh
op_assign
(paren
r_struct
id|etherh_priv
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
r_struct
id|ei_device
op_star
id|ei_local
op_assign
op_amp
id|eh-&gt;eidev
suffix:semicolon
r_int
id|stat
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|eh-&gt;id
)paren
(brace
r_case
id|PROD_I3_ETHERLAN600
suffix:colon
r_case
id|PROD_I3_ETHERLAN600A
suffix:colon
r_switch
c_cond
(paren
id|dev-&gt;if_port
)paren
(brace
r_case
id|IF_PORT_10BASE2
suffix:colon
id|stat
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IF_PORT_10BASET
suffix:colon
id|stat
op_assign
id|inb
c_func
(paren
id|dev-&gt;base_addr
op_plus
id|EN0_RCNTHI
)paren
op_amp
l_int|4
suffix:semicolon
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|PROD_I3_ETHERLAN500
suffix:colon
r_switch
c_cond
(paren
id|dev-&gt;if_port
)paren
(brace
r_case
id|IF_PORT_10BASE2
suffix:colon
id|stat
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IF_PORT_10BASET
suffix:colon
id|stat
op_assign
id|etherh_get_stat
c_func
(paren
id|eh
)paren
op_amp
id|ETHERH_CP_HEARTBEAT
suffix:semicolon
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
id|stat
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|stat
op_ne
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Configure the interface.  Note that we ignore the other&n; * parts of ifmap, since its mostly meaningless for this driver.&n; */
DECL|function|etherh_set_config
r_static
r_int
id|etherh_set_config
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_struct
id|ifmap
op_star
id|map
)paren
(brace
r_switch
c_cond
(paren
id|map-&gt;port
)paren
(brace
r_case
id|IF_PORT_10BASE2
suffix:colon
r_case
id|IF_PORT_10BASET
suffix:colon
multiline_comment|/*&n;&t;&t; * If the user explicitly sets the interface&n;&t;&t; * media type, turn off automedia detection.&n;&t;&t; */
id|dev-&gt;flags
op_and_assign
op_complement
id|IFF_AUTOMEDIA
suffix:semicolon
id|dev-&gt;if_port
op_assign
id|map-&gt;port
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|etherh_setif
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Reset the 8390 (hard reset).  Note that we can&squot;t actually do this.&n; */
r_static
r_void
DECL|function|etherh_reset
id|etherh_reset
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|ei_device
op_star
id|ei_local
op_assign
(paren
r_struct
id|ei_device
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
id|outb_p
c_func
(paren
id|E8390_NODMA
op_plus
id|E8390_PAGE0
op_plus
id|E8390_STOP
comma
id|dev-&gt;base_addr
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * See if we need to change the interface type.&n;&t; * Note that we use &squot;interface_num&squot; as a flag&n;&t; * to indicate that we need to change the media.&n;&t; */
r_if
c_cond
(paren
id|dev-&gt;flags
op_amp
id|IFF_AUTOMEDIA
op_logical_and
id|ei_local-&gt;interface_num
)paren
(brace
id|ei_local-&gt;interface_num
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;if_port
op_eq
id|IF_PORT_10BASET
)paren
id|dev-&gt;if_port
op_assign
id|IF_PORT_10BASE2
suffix:semicolon
r_else
id|dev-&gt;if_port
op_assign
id|IF_PORT_10BASET
suffix:semicolon
id|etherh_setif
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Write a block of data out to the 8390&n; */
r_static
r_void
DECL|function|etherh_block_output
id|etherh_block_output
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
r_struct
id|ei_device
op_star
id|ei_local
op_assign
(paren
r_struct
id|ei_device
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
r_int
r_int
id|addr
comma
id|dma_addr
suffix:semicolon
r_int
r_int
id|dma_start
suffix:semicolon
r_if
c_cond
(paren
id|ei_local-&gt;dmaing
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: DMAing conflict in etherh_block_input: &quot;
l_string|&quot; DMAstat %d irqlock %d&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|ei_local-&gt;dmaing
comma
id|ei_local-&gt;irqlock
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Make sure we have a round number of bytes if we&squot;re in word mode.&n;&t; */
r_if
c_cond
(paren
id|count
op_amp
l_int|1
op_logical_and
id|ei_local-&gt;word16
)paren
id|count
op_increment
suffix:semicolon
id|ei_local-&gt;dmaing
op_assign
l_int|1
suffix:semicolon
id|addr
op_assign
id|dev-&gt;base_addr
suffix:semicolon
id|dma_addr
op_assign
id|dev-&gt;mem_start
suffix:semicolon
id|count
op_assign
(paren
id|count
op_plus
l_int|1
)paren
op_amp
op_complement
l_int|1
suffix:semicolon
id|outb
(paren
id|E8390_NODMA
op_or
id|E8390_PAGE0
op_or
id|E8390_START
comma
id|addr
op_plus
id|E8390_CMD
)paren
suffix:semicolon
id|outb
(paren
l_int|0x42
comma
id|addr
op_plus
id|EN0_RCNTLO
)paren
suffix:semicolon
id|outb
(paren
l_int|0x00
comma
id|addr
op_plus
id|EN0_RCNTHI
)paren
suffix:semicolon
id|outb
(paren
l_int|0x42
comma
id|addr
op_plus
id|EN0_RSARLO
)paren
suffix:semicolon
id|outb
(paren
l_int|0x00
comma
id|addr
op_plus
id|EN0_RSARHI
)paren
suffix:semicolon
id|outb
(paren
id|E8390_RREAD
op_or
id|E8390_START
comma
id|addr
op_plus
id|E8390_CMD
)paren
suffix:semicolon
id|udelay
(paren
l_int|1
)paren
suffix:semicolon
id|outb
(paren
id|ENISR_RDC
comma
id|addr
op_plus
id|EN0_ISR
)paren
suffix:semicolon
id|outb
(paren
id|count
comma
id|addr
op_plus
id|EN0_RCNTLO
)paren
suffix:semicolon
id|outb
(paren
id|count
op_rshift
l_int|8
comma
id|addr
op_plus
id|EN0_RCNTHI
)paren
suffix:semicolon
id|outb
(paren
l_int|0
comma
id|addr
op_plus
id|EN0_RSARLO
)paren
suffix:semicolon
id|outb
(paren
id|start_page
comma
id|addr
op_plus
id|EN0_RSARHI
)paren
suffix:semicolon
id|outb
(paren
id|E8390_RWRITE
op_or
id|E8390_START
comma
id|addr
op_plus
id|E8390_CMD
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ei_local-&gt;word16
)paren
id|outsw
(paren
id|dma_addr
comma
id|buf
comma
id|count
op_rshift
l_int|1
)paren
suffix:semicolon
r_else
id|outsb
(paren
id|dma_addr
comma
id|buf
comma
id|count
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
id|inb
(paren
id|addr
op_plus
id|EN0_ISR
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
id|KERN_ERR
l_string|&quot;%s: timeout waiting for TX RDC&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
id|etherh_reset
(paren
id|dev
)paren
suffix:semicolon
id|NS8390_init
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
(paren
id|ENISR_RDC
comma
id|addr
op_plus
id|EN0_ISR
)paren
suffix:semicolon
id|ei_local-&gt;dmaing
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Read a block of data from the 8390&n; */
r_static
r_void
DECL|function|etherh_block_input
id|etherh_block_input
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
r_struct
id|ei_device
op_star
id|ei_local
op_assign
(paren
r_struct
id|ei_device
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
r_int
r_int
id|addr
comma
id|dma_addr
suffix:semicolon
r_int
r_char
op_star
id|buf
suffix:semicolon
r_if
c_cond
(paren
id|ei_local-&gt;dmaing
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: DMAing conflict in etherh_block_input: &quot;
l_string|&quot; DMAstat %d irqlock %d&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|ei_local-&gt;dmaing
comma
id|ei_local-&gt;irqlock
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|ei_local-&gt;dmaing
op_assign
l_int|1
suffix:semicolon
id|addr
op_assign
id|dev-&gt;base_addr
suffix:semicolon
id|dma_addr
op_assign
id|dev-&gt;mem_start
suffix:semicolon
id|buf
op_assign
id|skb-&gt;data
suffix:semicolon
id|outb
(paren
id|E8390_NODMA
op_or
id|E8390_PAGE0
op_or
id|E8390_START
comma
id|addr
op_plus
id|E8390_CMD
)paren
suffix:semicolon
id|outb
(paren
id|count
comma
id|addr
op_plus
id|EN0_RCNTLO
)paren
suffix:semicolon
id|outb
(paren
id|count
op_rshift
l_int|8
comma
id|addr
op_plus
id|EN0_RCNTHI
)paren
suffix:semicolon
id|outb
(paren
id|ring_offset
comma
id|addr
op_plus
id|EN0_RSARLO
)paren
suffix:semicolon
id|outb
(paren
id|ring_offset
op_rshift
l_int|8
comma
id|addr
op_plus
id|EN0_RSARHI
)paren
suffix:semicolon
id|outb
(paren
id|E8390_RREAD
op_or
id|E8390_START
comma
id|addr
op_plus
id|E8390_CMD
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ei_local-&gt;word16
)paren
(brace
id|insw
(paren
id|dma_addr
comma
id|buf
comma
id|count
op_rshift
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|count
op_amp
l_int|1
)paren
id|buf
(braket
id|count
op_minus
l_int|1
)braket
op_assign
id|inb
(paren
id|dma_addr
)paren
suffix:semicolon
)brace
r_else
id|insb
(paren
id|dma_addr
comma
id|buf
comma
id|count
)paren
suffix:semicolon
id|outb
(paren
id|ENISR_RDC
comma
id|addr
op_plus
id|EN0_ISR
)paren
suffix:semicolon
id|ei_local-&gt;dmaing
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Read a header from the 8390&n; */
r_static
r_void
DECL|function|etherh_get_header
id|etherh_get_header
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
r_struct
id|ei_device
op_star
id|ei_local
op_assign
(paren
r_struct
id|ei_device
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
r_int
r_int
id|addr
comma
id|dma_addr
suffix:semicolon
r_if
c_cond
(paren
id|ei_local-&gt;dmaing
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: DMAing conflict in etherh_get_header: &quot;
l_string|&quot; DMAstat %d irqlock %d&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|ei_local-&gt;dmaing
comma
id|ei_local-&gt;irqlock
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|ei_local-&gt;dmaing
op_assign
l_int|1
suffix:semicolon
id|addr
op_assign
id|dev-&gt;base_addr
suffix:semicolon
id|dma_addr
op_assign
id|dev-&gt;mem_start
suffix:semicolon
id|outb
(paren
id|E8390_NODMA
op_or
id|E8390_PAGE0
op_or
id|E8390_START
comma
id|addr
op_plus
id|E8390_CMD
)paren
suffix:semicolon
id|outb
(paren
r_sizeof
(paren
op_star
id|hdr
)paren
comma
id|addr
op_plus
id|EN0_RCNTLO
)paren
suffix:semicolon
id|outb
(paren
l_int|0
comma
id|addr
op_plus
id|EN0_RCNTHI
)paren
suffix:semicolon
id|outb
(paren
l_int|0
comma
id|addr
op_plus
id|EN0_RSARLO
)paren
suffix:semicolon
id|outb
(paren
id|ring_page
comma
id|addr
op_plus
id|EN0_RSARHI
)paren
suffix:semicolon
id|outb
(paren
id|E8390_RREAD
op_or
id|E8390_START
comma
id|addr
op_plus
id|E8390_CMD
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ei_local-&gt;word16
)paren
id|insw
(paren
id|dma_addr
comma
id|hdr
comma
r_sizeof
(paren
op_star
id|hdr
)paren
op_rshift
l_int|1
)paren
suffix:semicolon
r_else
id|insb
(paren
id|dma_addr
comma
id|hdr
comma
r_sizeof
(paren
op_star
id|hdr
)paren
)paren
suffix:semicolon
id|outb
(paren
id|ENISR_RDC
comma
id|addr
op_plus
id|EN0_ISR
)paren
suffix:semicolon
id|ei_local-&gt;dmaing
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Open/initialize the board.  This is called (in the current kernel)&n; * sometime after booting when the &squot;ifconfig&squot; program is run.&n; *&n; * This routine should set everything up anew at each open, even&n; * registers that &quot;should&quot; only need to be set once at boot, so that&n; * there is non-reboot way to recover if something goes wrong.&n; */
r_static
r_int
DECL|function|etherh_open
id|etherh_open
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|ei_device
op_star
id|ei_local
op_assign
(paren
r_struct
id|ei_device
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|is_valid_ether_addr
c_func
(paren
id|dev-&gt;dev_addr
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: invalid ethernet MAC address&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
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
r_return
op_minus
id|EAGAIN
suffix:semicolon
multiline_comment|/*&n;&t; * Make sure that we aren&squot;t going to change the&n;&t; * media type on the next reset - we are about to&n;&t; * do automedia manually now.&n;&t; */
id|ei_local-&gt;interface_num
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * If we are doing automedia detection, do it now.&n;&t; * This is more reliable than the 8390&squot;s detection.&n;&t; */
r_if
c_cond
(paren
id|dev-&gt;flags
op_amp
id|IFF_AUTOMEDIA
)paren
(brace
id|dev-&gt;if_port
op_assign
id|IF_PORT_10BASET
suffix:semicolon
id|etherh_setif
c_func
(paren
id|dev
)paren
suffix:semicolon
id|mdelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|etherh_getifstat
c_func
(paren
id|dev
)paren
)paren
(brace
id|dev-&gt;if_port
op_assign
id|IF_PORT_10BASE2
suffix:semicolon
id|etherh_setif
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
)brace
r_else
id|etherh_setif
c_func
(paren
id|dev
)paren
suffix:semicolon
id|etherh_reset
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
multiline_comment|/*&n; * The inverse routine to etherh_open().&n; */
r_static
r_int
DECL|function|etherh_close
id|etherh_close
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
id|ei_close
(paren
id|dev
)paren
suffix:semicolon
id|free_irq
(paren
id|dev-&gt;irq
comma
id|dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Initialisation&n; */
DECL|function|etherh_banner
r_static
r_void
id|__init
id|etherh_banner
c_func
(paren
r_void
)paren
(brace
r_static
r_int
id|version_printed
suffix:semicolon
r_if
c_cond
(paren
id|net_debug
op_logical_and
id|version_printed
op_increment
op_eq
l_int|0
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s&quot;
comma
id|version
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Read the ethernet address string from the on board rom.&n; * This is an ascii string...&n; */
DECL|function|etherh_addr
r_static
r_int
id|__init
id|etherh_addr
c_func
(paren
r_char
op_star
id|addr
comma
r_struct
id|expansion_card
op_star
id|ec
)paren
(brace
r_struct
id|in_chunk_dir
id|cd
suffix:semicolon
r_char
op_star
id|s
suffix:semicolon
r_if
c_cond
(paren
id|ecard_readchunk
c_func
(paren
op_amp
id|cd
comma
id|ec
comma
l_int|0xf5
comma
l_int|0
)paren
op_logical_and
(paren
id|s
op_assign
id|strchr
c_func
(paren
id|cd.d.string
comma
l_char|&squot;(&squot;
)paren
)paren
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
id|i
OL
l_int|6
suffix:semicolon
id|i
op_increment
)paren
(brace
id|addr
(braket
id|i
)braket
op_assign
id|simple_strtoul
c_func
(paren
id|s
op_plus
l_int|1
comma
op_amp
id|s
comma
l_int|0x10
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|s
op_ne
(paren
id|i
op_eq
l_int|5
ques
c_cond
l_char|&squot;)&squot;
suffix:colon
l_char|&squot;:&squot;
)paren
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
op_eq
l_int|6
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
multiline_comment|/*&n; * Create an ethernet address from the system serial number.&n; */
DECL|function|etherm_addr
r_static
r_int
id|__init
id|etherm_addr
c_func
(paren
r_char
op_star
id|addr
)paren
(brace
r_int
r_int
id|serial
suffix:semicolon
r_if
c_cond
(paren
id|system_serial_low
op_eq
l_int|0
op_logical_and
id|system_serial_high
op_eq
l_int|0
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|serial
op_assign
id|system_serial_low
op_or
id|system_serial_high
suffix:semicolon
id|addr
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
id|addr
(braket
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
id|addr
(braket
l_int|2
)braket
op_assign
l_int|0xa4
suffix:semicolon
id|addr
(braket
l_int|3
)braket
op_assign
l_int|0x10
op_plus
(paren
id|serial
op_rshift
l_int|24
)paren
suffix:semicolon
id|addr
(braket
l_int|4
)braket
op_assign
id|serial
op_rshift
l_int|16
suffix:semicolon
id|addr
(braket
l_int|5
)braket
op_assign
id|serial
op_rshift
l_int|8
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|etherh_regoffsets
r_static
id|u32
id|etherh_regoffsets
(braket
l_int|16
)braket
suffix:semicolon
DECL|variable|etherm_regoffsets
r_static
id|u32
id|etherm_regoffsets
(braket
l_int|16
)braket
suffix:semicolon
r_static
r_int
id|__init
DECL|function|etherh_probe
id|etherh_probe
c_func
(paren
r_struct
id|expansion_card
op_star
id|ec
comma
r_const
r_struct
id|ecard_id
op_star
id|id
)paren
(brace
r_struct
id|ei_device
op_star
id|ei_local
suffix:semicolon
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
r_struct
id|etherh_priv
op_star
id|eh
suffix:semicolon
r_const
r_char
op_star
id|dev_type
suffix:semicolon
r_int
id|i
comma
id|size
comma
id|ret
suffix:semicolon
id|etherh_banner
c_func
(paren
)paren
suffix:semicolon
id|dev
op_assign
id|alloc_etherdev
c_func
(paren
r_sizeof
(paren
r_struct
id|etherh_priv
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
(brace
id|ret
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * alloc_etherdev allocs and zeros dev-&gt;priv&n;&t; */
id|eh
op_assign
id|dev-&gt;priv
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|eh-&gt;eidev.page_lock
)paren
suffix:semicolon
id|SET_MODULE_OWNER
c_func
(paren
id|dev
)paren
suffix:semicolon
id|dev-&gt;open
op_assign
id|etherh_open
suffix:semicolon
id|dev-&gt;stop
op_assign
id|etherh_close
suffix:semicolon
id|dev-&gt;set_config
op_assign
id|etherh_set_config
suffix:semicolon
id|dev-&gt;irq
op_assign
id|ec-&gt;irq
suffix:semicolon
id|dev-&gt;base_addr
op_assign
id|ecard_address
c_func
(paren
id|ec
comma
id|ECARD_MEMC
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * IRQ and control port handling&n;&t; */
r_if
c_cond
(paren
id|ec-&gt;irq
op_ne
l_int|11
)paren
(brace
id|ec-&gt;ops
op_assign
op_amp
id|etherh_ops
suffix:semicolon
id|ec-&gt;irq_data
op_assign
id|eh
suffix:semicolon
)brace
id|eh-&gt;ctrl
op_assign
l_int|0
suffix:semicolon
id|eh-&gt;id
op_assign
id|ec-&gt;cid.product
suffix:semicolon
r_switch
c_cond
(paren
id|ec-&gt;cid.product
)paren
(brace
r_case
id|PROD_ANT_ETHERM
suffix:colon
id|etherm_addr
c_func
(paren
id|dev-&gt;dev_addr
)paren
suffix:semicolon
id|dev-&gt;base_addr
op_add_assign
id|ETHERM_NS8390
suffix:semicolon
id|dev-&gt;mem_start
op_assign
id|dev-&gt;base_addr
op_plus
id|ETHERM_DATAPORT
suffix:semicolon
id|eh-&gt;ctrl_port
op_assign
id|dev-&gt;base_addr
op_plus
id|ETHERM_CTRLPORT
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PROD_I3_ETHERLAN500
suffix:colon
id|etherh_addr
c_func
(paren
id|dev-&gt;dev_addr
comma
id|ec
)paren
suffix:semicolon
id|dev-&gt;base_addr
op_add_assign
id|ETHERH500_NS8390
suffix:semicolon
id|dev-&gt;mem_start
op_assign
id|dev-&gt;base_addr
op_plus
id|ETHERH500_DATAPORT
suffix:semicolon
id|eh-&gt;ctrl_port
op_assign
id|ecard_address
(paren
id|ec
comma
id|ECARD_IOC
comma
id|ECARD_FAST
)paren
op_plus
id|ETHERH500_CTRLPORT
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PROD_I3_ETHERLAN600
suffix:colon
r_case
id|PROD_I3_ETHERLAN600A
suffix:colon
id|etherh_addr
c_func
(paren
id|dev-&gt;dev_addr
comma
id|ec
)paren
suffix:semicolon
id|dev-&gt;base_addr
op_add_assign
id|ETHERH600_NS8390
suffix:semicolon
id|dev-&gt;mem_start
op_assign
id|dev-&gt;base_addr
op_plus
id|ETHERH600_DATAPORT
suffix:semicolon
id|eh-&gt;ctrl_port
op_assign
id|dev-&gt;base_addr
op_plus
id|ETHERH600_CTRLPORT
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: unknown card type %x&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|ec-&gt;cid.product
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|free
suffix:semicolon
)brace
id|size
op_assign
l_int|16
suffix:semicolon
r_if
c_cond
(paren
id|ec-&gt;cid.product
op_eq
id|PROD_ANT_ETHERM
)paren
id|size
op_lshift_assign
l_int|3
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
id|size
comma
id|dev-&gt;name
)paren
)paren
(brace
id|ret
op_assign
op_minus
id|EBUSY
suffix:semicolon
r_goto
id|free
suffix:semicolon
)brace
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
id|ret
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|release
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * If we&squot;re in the NIC slot, make sure the IRQ is enabled&n;&t; */
r_if
c_cond
(paren
id|dev-&gt;irq
op_eq
l_int|11
)paren
id|etherh_set_ctrl
c_func
(paren
id|eh
comma
id|ETHERH_CP_IE
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Unfortunately, ethdev_init eventually calls&n;&t; * ether_setup, which re-writes dev-&gt;flags.&n;&t; */
r_switch
c_cond
(paren
id|ec-&gt;cid.product
)paren
(brace
r_case
id|PROD_ANT_ETHERM
suffix:colon
id|dev_type
op_assign
l_string|&quot;ANT EtherM&quot;
suffix:semicolon
id|dev-&gt;if_port
op_assign
id|IF_PORT_UNKNOWN
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PROD_I3_ETHERLAN500
suffix:colon
id|dev_type
op_assign
l_string|&quot;i3 EtherH 500&quot;
suffix:semicolon
id|dev-&gt;if_port
op_assign
id|IF_PORT_UNKNOWN
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PROD_I3_ETHERLAN600
suffix:colon
id|dev_type
op_assign
l_string|&quot;i3 EtherH 600&quot;
suffix:semicolon
id|dev-&gt;flags
op_or_assign
id|IFF_PORTSEL
op_or
id|IFF_AUTOMEDIA
suffix:semicolon
id|dev-&gt;if_port
op_assign
id|IF_PORT_10BASET
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PROD_I3_ETHERLAN600A
suffix:colon
id|dev_type
op_assign
l_string|&quot;i3 EtherH 600A&quot;
suffix:semicolon
id|dev-&gt;flags
op_or_assign
id|IFF_PORTSEL
op_or
id|IFF_AUTOMEDIA
suffix:semicolon
id|dev-&gt;if_port
op_assign
id|IF_PORT_10BASET
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|dev_type
op_assign
l_string|&quot;unknown&quot;
suffix:semicolon
r_break
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: %s in slot %d, &quot;
comma
id|dev-&gt;name
comma
id|dev_type
comma
id|ec-&gt;slot_no
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
l_string|&quot;%2.2x%c&quot;
comma
id|dev-&gt;dev_addr
(braket
id|i
)braket
comma
id|i
op_eq
l_int|5
ques
c_cond
l_char|&squot;&bslash;n&squot;
suffix:colon
l_char|&squot;:&squot;
)paren
suffix:semicolon
id|ei_local
op_assign
(paren
r_struct
id|ei_device
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
r_if
c_cond
(paren
id|ec-&gt;cid.product
op_eq
id|PROD_ANT_ETHERM
)paren
(brace
id|ei_local-&gt;tx_start_page
op_assign
id|ETHERM_TX_START_PAGE
suffix:semicolon
id|ei_local-&gt;stop_page
op_assign
id|ETHERM_STOP_PAGE
suffix:semicolon
id|ei_local-&gt;reg_offset
op_assign
id|etherm_regoffsets
suffix:semicolon
)brace
r_else
(brace
id|ei_local-&gt;tx_start_page
op_assign
id|ETHERH_TX_START_PAGE
suffix:semicolon
id|ei_local-&gt;stop_page
op_assign
id|ETHERH_STOP_PAGE
suffix:semicolon
id|ei_local-&gt;reg_offset
op_assign
id|etherh_regoffsets
suffix:semicolon
)brace
id|ei_local-&gt;name
op_assign
id|dev-&gt;name
suffix:semicolon
id|ei_local-&gt;word16
op_assign
l_int|1
suffix:semicolon
id|ei_local-&gt;rx_start_page
op_assign
id|ei_local-&gt;tx_start_page
op_plus
id|TX_PAGES
suffix:semicolon
id|ei_local-&gt;reset_8390
op_assign
id|etherh_reset
suffix:semicolon
id|ei_local-&gt;block_input
op_assign
id|etherh_block_input
suffix:semicolon
id|ei_local-&gt;block_output
op_assign
id|etherh_block_output
suffix:semicolon
id|ei_local-&gt;get_8390_hdr
op_assign
id|etherh_get_header
suffix:semicolon
id|ei_local-&gt;interface_num
op_assign
l_int|0
suffix:semicolon
id|etherh_reset
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
l_int|0
)paren
suffix:semicolon
id|ret
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
id|ret
)paren
r_goto
id|release
suffix:semicolon
id|ecard_set_drvdata
c_func
(paren
id|ec
comma
id|dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|release
suffix:colon
id|release_region
c_func
(paren
id|dev-&gt;base_addr
comma
l_int|16
)paren
suffix:semicolon
id|free
suffix:colon
id|kfree
c_func
(paren
id|dev
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|etherh_remove
r_static
r_void
id|__devexit
id|etherh_remove
c_func
(paren
r_struct
id|expansion_card
op_star
id|ec
)paren
(brace
r_struct
id|net_device
op_star
id|dev
op_assign
id|ecard_get_drvdata
c_func
(paren
id|ec
)paren
suffix:semicolon
r_int
id|size
op_assign
l_int|16
suffix:semicolon
id|ecard_set_drvdata
c_func
(paren
id|ec
comma
l_int|NULL
)paren
suffix:semicolon
id|unregister_netdev
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ec-&gt;cid.product
op_eq
id|PROD_ANT_ETHERM
)paren
id|size
op_lshift_assign
l_int|3
suffix:semicolon
id|release_region
c_func
(paren
id|dev-&gt;base_addr
comma
id|size
)paren
suffix:semicolon
id|free_netdev
c_func
(paren
id|dev
)paren
suffix:semicolon
id|ec-&gt;ops
op_assign
l_int|NULL
suffix:semicolon
id|kfree
c_func
(paren
id|ec-&gt;irq_data
)paren
suffix:semicolon
)brace
DECL|variable|etherh_ids
r_static
r_const
r_struct
id|ecard_id
id|etherh_ids
(braket
)braket
op_assign
(brace
(brace
id|MANU_ANT
comma
id|PROD_ANT_ETHERM
)brace
comma
(brace
id|MANU_I3
comma
id|PROD_I3_ETHERLAN500
)brace
comma
(brace
id|MANU_I3
comma
id|PROD_I3_ETHERLAN600
)brace
comma
(brace
id|MANU_I3
comma
id|PROD_I3_ETHERLAN600A
)brace
comma
(brace
l_int|0xffff
comma
l_int|0xffff
)brace
)brace
suffix:semicolon
DECL|variable|etherh_driver
r_static
r_struct
id|ecard_driver
id|etherh_driver
op_assign
(brace
dot
id|probe
op_assign
id|etherh_probe
comma
dot
id|remove
op_assign
id|__devexit_p
c_func
(paren
id|etherh_remove
)paren
comma
dot
id|id_table
op_assign
id|etherh_ids
comma
dot
id|drv
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;etherh&quot;
comma
)brace
comma
)brace
suffix:semicolon
DECL|function|etherh_init
r_static
r_int
id|__init
id|etherh_init
c_func
(paren
r_void
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
id|i
OL
l_int|16
suffix:semicolon
id|i
op_increment
)paren
(brace
id|etherh_regoffsets
(braket
id|i
)braket
op_assign
id|i
suffix:semicolon
id|etherm_regoffsets
(braket
id|i
)braket
op_assign
id|i
op_lshift
l_int|3
suffix:semicolon
)brace
r_return
id|ecard_register_driver
c_func
(paren
op_amp
id|etherh_driver
)paren
suffix:semicolon
)brace
DECL|function|etherh_exit
r_static
r_void
id|__exit
id|etherh_exit
c_func
(paren
r_void
)paren
(brace
id|ecard_remove_driver
c_func
(paren
op_amp
id|etherh_driver
)paren
suffix:semicolon
)brace
DECL|variable|etherh_init
id|module_init
c_func
(paren
id|etherh_init
)paren
suffix:semicolon
DECL|variable|etherh_exit
id|module_exit
c_func
(paren
id|etherh_exit
)paren
suffix:semicolon
eof
