multiline_comment|/*******************************************************************************&n;&n;  &n;  Copyright(c) 1999 - 2002 Intel Corporation. All rights reserved.&n;  &n;  This program is free software; you can redistribute it and/or modify it &n;  under the terms of the GNU General Public License as published by the Free &n;  Software Foundation; either version 2 of the License, or (at your option) &n;  any later version.&n;  &n;  This program is distributed in the hope that it will be useful, but WITHOUT &n;  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or &n;  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for &n;  more details.&n;  &n;  You should have received a copy of the GNU General Public License along with&n;  this program; if not, write to the Free Software Foundation, Inc., 59 &n;  Temple Place - Suite 330, Boston, MA  02111-1307, USA.&n;  &n;  The full GNU General Public License is included in this distribution in the&n;  file called LICENSE.&n;  &n;  Contact Information:&n;  Linux NICS &lt;linux.nics@intel.com&gt;&n;  Intel Corporation, 5200 N.E. Elam Young Parkway, Hillsboro, OR 97124-6497&n;&n;*******************************************************************************/
multiline_comment|/* Linux PRO/1000 Ethernet Driver main header file */
macro_line|#ifndef _E1000_H_
DECL|macro|_E1000_H_
mdefine_line|#define _E1000_H_
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/etherdevice.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;linux/capability.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/ip.h&gt;
macro_line|#include &lt;linux/tcp.h&gt;
macro_line|#include &lt;linux/udp.h&gt;
macro_line|#include &lt;net/pkt_sched.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/reboot.h&gt;
macro_line|#include &lt;net/checksum.h&gt;
macro_line|#include &lt;linux/workqueue.h&gt;
macro_line|#include &lt;linux/ethtool.h&gt;
macro_line|#include &lt;linux/if_vlan.h&gt;
DECL|macro|BAR_0
mdefine_line|#define BAR_0&t;&t;0
DECL|macro|BAR_1
mdefine_line|#define BAR_1&t;&t;1
DECL|macro|BAR_5
mdefine_line|#define BAR_5&t;&t;5
DECL|macro|PCI_DMA_64BIT
mdefine_line|#define PCI_DMA_64BIT&t;0xffffffffffffffffULL
DECL|macro|PCI_DMA_32BIT
mdefine_line|#define PCI_DMA_32BIT&t;0x00000000ffffffffULL
r_struct
id|e1000_adapter
suffix:semicolon
macro_line|#include &quot;e1000_hw.h&quot;
macro_line|#if DBG
DECL|macro|E1000_DBG
mdefine_line|#define E1000_DBG(args...) printk(KERN_DEBUG &quot;e1000: &quot; args)
macro_line|#else
DECL|macro|E1000_DBG
mdefine_line|#define E1000_DBG(args...)
macro_line|#endif
DECL|macro|E1000_ERR
mdefine_line|#define E1000_ERR(args...) printk(KERN_ERR &quot;e1000: &quot; args)
DECL|macro|E1000_MAX_INTR
mdefine_line|#define E1000_MAX_INTR 10
multiline_comment|/* Supported Rx Buffer Sizes */
DECL|macro|E1000_RXBUFFER_2048
mdefine_line|#define E1000_RXBUFFER_2048  2048
DECL|macro|E1000_RXBUFFER_4096
mdefine_line|#define E1000_RXBUFFER_4096  4096
DECL|macro|E1000_RXBUFFER_8192
mdefine_line|#define E1000_RXBUFFER_8192  8192
DECL|macro|E1000_RXBUFFER_16384
mdefine_line|#define E1000_RXBUFFER_16384 16384
multiline_comment|/* Flow Control High-Watermark: 43464 bytes */
DECL|macro|E1000_FC_HIGH_THRESH
mdefine_line|#define E1000_FC_HIGH_THRESH 0xA9C8
multiline_comment|/* Flow Control Low-Watermark: 43456 bytes */
DECL|macro|E1000_FC_LOW_THRESH
mdefine_line|#define E1000_FC_LOW_THRESH 0xA9C0
multiline_comment|/* Flow Control Pause Time: 858 usec */
DECL|macro|E1000_FC_PAUSE_TIME
mdefine_line|#define E1000_FC_PAUSE_TIME 0x0680
multiline_comment|/* How many Tx Descriptors do we need to call netif_wake_queue ? */
DECL|macro|E1000_TX_QUEUE_WAKE
mdefine_line|#define E1000_TX_QUEUE_WAKE&t;16
multiline_comment|/* How many Rx Buffers do we bundle into one write to the hardware ? */
DECL|macro|E1000_RX_BUFFER_WRITE
mdefine_line|#define E1000_RX_BUFFER_WRITE&t;16
DECL|macro|E1000_JUMBO_PBA
mdefine_line|#define E1000_JUMBO_PBA      0x00000028
DECL|macro|E1000_DEFAULT_PBA
mdefine_line|#define E1000_DEFAULT_PBA    0x00000030
DECL|macro|AUTO_ALL_MODES
mdefine_line|#define AUTO_ALL_MODES       0
multiline_comment|/* only works for sizes that are powers of 2 */
DECL|macro|E1000_ROUNDUP
mdefine_line|#define E1000_ROUNDUP(i, size) ((i) = (((i) + (size) - 1) &amp; ~((size) - 1)))
multiline_comment|/* wrapper around a pointer to a socket buffer,&n; * so a DMA handle can be stored along with the buffer */
DECL|struct|e1000_buffer
r_struct
id|e1000_buffer
(brace
DECL|member|skb
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
DECL|member|dma
r_uint64
id|dma
suffix:semicolon
DECL|member|length
r_int
r_int
id|length
suffix:semicolon
DECL|member|time_stamp
r_int
r_int
id|time_stamp
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|e1000_desc_ring
r_struct
id|e1000_desc_ring
(brace
multiline_comment|/* pointer to the descriptor ring memory */
DECL|member|desc
r_void
op_star
id|desc
suffix:semicolon
multiline_comment|/* physical address of the descriptor ring */
DECL|member|dma
id|dma_addr_t
id|dma
suffix:semicolon
multiline_comment|/* length of descriptor ring in bytes */
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
multiline_comment|/* number of descriptors in the ring */
DECL|member|count
r_int
r_int
id|count
suffix:semicolon
multiline_comment|/* next descriptor to associate a buffer with */
DECL|member|next_to_use
r_int
r_int
id|next_to_use
suffix:semicolon
multiline_comment|/* next descriptor to check for DD status bit */
DECL|member|next_to_clean
r_int
r_int
id|next_to_clean
suffix:semicolon
multiline_comment|/* array of buffer information structs */
DECL|member|buffer_info
r_struct
id|e1000_buffer
op_star
id|buffer_info
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|E1000_DESC_UNUSED
mdefine_line|#define E1000_DESC_UNUSED(R) &bslash;&n;((((R)-&gt;next_to_clean + (R)-&gt;count) - ((R)-&gt;next_to_use + 1)) % ((R)-&gt;count))
DECL|macro|E1000_GET_DESC
mdefine_line|#define E1000_GET_DESC(R, i, type)&t;(&amp;(((struct type *)((R).desc))[i]))
DECL|macro|E1000_RX_DESC
mdefine_line|#define E1000_RX_DESC(R, i)&t;&t;E1000_GET_DESC(R, i, e1000_rx_desc)
DECL|macro|E1000_TX_DESC
mdefine_line|#define E1000_TX_DESC(R, i)&t;&t;E1000_GET_DESC(R, i, e1000_tx_desc)
DECL|macro|E1000_CONTEXT_DESC
mdefine_line|#define E1000_CONTEXT_DESC(R, i)&t;E1000_GET_DESC(R, i, e1000_context_desc)
multiline_comment|/* board specific private data structure */
DECL|struct|e1000_adapter
r_struct
id|e1000_adapter
(brace
DECL|member|watchdog_timer
r_struct
id|timer_list
id|watchdog_timer
suffix:semicolon
DECL|member|phy_info_timer
r_struct
id|timer_list
id|phy_info_timer
suffix:semicolon
macro_line|#ifdef CONFIG_PROC_FS
DECL|member|proc_list_head
r_struct
id|list_head
id|proc_list_head
suffix:semicolon
macro_line|#endif
DECL|member|vlgrp
r_struct
id|vlan_group
op_star
id|vlgrp
suffix:semicolon
DECL|member|id_string
r_char
op_star
id|id_string
suffix:semicolon
DECL|member|bd_number
r_uint32
id|bd_number
suffix:semicolon
DECL|member|rx_buffer_len
r_uint32
id|rx_buffer_len
suffix:semicolon
DECL|member|part_num
r_uint32
id|part_num
suffix:semicolon
DECL|member|wol
r_uint32
id|wol
suffix:semicolon
DECL|member|link_speed
r_uint16
id|link_speed
suffix:semicolon
DECL|member|link_duplex
r_uint16
id|link_duplex
suffix:semicolon
DECL|member|stats_lock
id|spinlock_t
id|stats_lock
suffix:semicolon
DECL|member|irq_sem
id|atomic_t
id|irq_sem
suffix:semicolon
DECL|member|tx_timeout_task
r_struct
id|work_struct
id|tx_timeout_task
suffix:semicolon
DECL|member|blink_timer
r_struct
id|timer_list
id|blink_timer
suffix:semicolon
DECL|member|led_status
r_int
r_int
id|led_status
suffix:semicolon
multiline_comment|/* TX */
DECL|member|tx_ring
r_struct
id|e1000_desc_ring
id|tx_ring
suffix:semicolon
DECL|member|txd_cmd
r_uint32
id|txd_cmd
suffix:semicolon
DECL|member|tx_int_delay
r_uint32
id|tx_int_delay
suffix:semicolon
DECL|member|tx_abs_int_delay
r_uint32
id|tx_abs_int_delay
suffix:semicolon
DECL|member|max_data_per_txd
r_int
id|max_data_per_txd
suffix:semicolon
multiline_comment|/* RX */
DECL|member|rx_ring
r_struct
id|e1000_desc_ring
id|rx_ring
suffix:semicolon
DECL|member|hw_csum_err
r_uint64
id|hw_csum_err
suffix:semicolon
DECL|member|hw_csum_good
r_uint64
id|hw_csum_good
suffix:semicolon
DECL|member|rx_int_delay
r_uint32
id|rx_int_delay
suffix:semicolon
DECL|member|rx_abs_int_delay
r_uint32
id|rx_abs_int_delay
suffix:semicolon
DECL|member|rx_csum
id|boolean_t
id|rx_csum
suffix:semicolon
multiline_comment|/* OS defined structs */
DECL|member|netdev
r_struct
id|net_device
op_star
id|netdev
suffix:semicolon
DECL|member|pdev
r_struct
id|pci_dev
op_star
id|pdev
suffix:semicolon
DECL|member|net_stats
r_struct
id|net_device_stats
id|net_stats
suffix:semicolon
multiline_comment|/* structs defined in e1000_hw.h */
DECL|member|hw
r_struct
id|e1000_hw
id|hw
suffix:semicolon
DECL|member|stats
r_struct
id|e1000_hw_stats
id|stats
suffix:semicolon
DECL|member|phy_info
r_struct
id|e1000_phy_info
id|phy_info
suffix:semicolon
DECL|member|phy_stats
r_struct
id|e1000_phy_stats
id|phy_stats
suffix:semicolon
DECL|member|pci_state
r_uint32
id|pci_state
(braket
l_int|16
)braket
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* _E1000_H_ */
eof
