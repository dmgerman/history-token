multiline_comment|/*&n;&t;drivers/net/tulip/interrupt.c&n;&n;&t;Maintained by Jeff Garzik &lt;jgarzik@pobox.com&gt;&n;&t;Copyright 2000,2001  The Linux Kernel Team&n;&t;Written/copyright 1994-2001 by Donald Becker.&n;&n;&t;This software may be used and distributed according to the terms&n;&t;of the GNU General Public License, incorporated herein by reference.&n;&n;&t;Please refer to Documentation/DocBook/tulip.{pdf,ps,html}&n;&t;for more information on this driver, or visit the project&n;&t;Web page at http://sourceforge.net/projects/tulip/&n;&n;*/
macro_line|#include &quot;tulip.h&quot;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/etherdevice.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
DECL|variable|tulip_rx_copybreak
r_int
id|tulip_rx_copybreak
suffix:semicolon
DECL|variable|tulip_max_interrupt_work
r_int
r_int
id|tulip_max_interrupt_work
suffix:semicolon
macro_line|#ifdef CONFIG_NET_HW_FLOWCONTROL
DECL|macro|MIT_SIZE
mdefine_line|#define MIT_SIZE 15
DECL|variable|mit_table
r_int
r_int
id|mit_table
(braket
id|MIT_SIZE
op_plus
l_int|1
)braket
op_assign
(brace
multiline_comment|/*  CRS11 21143 hardware Mitigation Control Interrupt&n;            We use only RX mitigation we other techniques for&n;            TX intr. mitigation.&n;&n;           31    Cycle Size (timer control)&n;           30:27 TX timer in 16 * Cycle size&n;           26:24 TX No pkts before Int.&n;           23:20 RX timer in Cycle size&n;           19:17 RX No pkts before Int.&n;           16       Continues Mode (CM)&n;        */
l_int|0x0
comma
multiline_comment|/* IM disabled */
l_int|0x80150000
comma
multiline_comment|/* RX time = 1, RX pkts = 2, CM = 1 */
l_int|0x80150000
comma
l_int|0x80270000
comma
l_int|0x80370000
comma
l_int|0x80490000
comma
l_int|0x80590000
comma
l_int|0x80690000
comma
l_int|0x807B0000
comma
l_int|0x808B0000
comma
l_int|0x809D0000
comma
l_int|0x80AD0000
comma
l_int|0x80BD0000
comma
l_int|0x80CF0000
comma
l_int|0x80DF0000
comma
singleline_comment|//       0x80FF0000      /* RX time = 16, RX pkts = 7, CM = 1 */
l_int|0x80F10000
multiline_comment|/* RX time = 16, RX pkts = 0, CM = 1 */
)brace
suffix:semicolon
macro_line|#endif
DECL|function|tulip_refill_rx
r_int
id|tulip_refill_rx
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|tulip_private
op_star
id|tp
op_assign
(paren
r_struct
id|tulip_private
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
r_int
id|entry
suffix:semicolon
r_int
id|refilled
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Refill the Rx ring buffers. */
r_for
c_loop
(paren
suffix:semicolon
id|tp-&gt;cur_rx
op_minus
id|tp-&gt;dirty_rx
OG
l_int|0
suffix:semicolon
id|tp-&gt;dirty_rx
op_increment
)paren
(brace
id|entry
op_assign
id|tp-&gt;dirty_rx
op_mod
id|RX_RING_SIZE
suffix:semicolon
r_if
c_cond
(paren
id|tp-&gt;rx_buffers
(braket
id|entry
)braket
dot
id|skb
op_eq
l_int|NULL
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
id|dma_addr_t
id|mapping
suffix:semicolon
id|skb
op_assign
id|tp-&gt;rx_buffers
(braket
id|entry
)braket
dot
id|skb
op_assign
id|dev_alloc_skb
c_func
(paren
id|PKT_BUF_SZ
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb
op_eq
l_int|NULL
)paren
r_break
suffix:semicolon
id|mapping
op_assign
id|pci_map_single
c_func
(paren
id|tp-&gt;pdev
comma
id|skb-&gt;tail
comma
id|PKT_BUF_SZ
comma
id|PCI_DMA_FROMDEVICE
)paren
suffix:semicolon
id|tp-&gt;rx_buffers
(braket
id|entry
)braket
dot
id|mapping
op_assign
id|mapping
suffix:semicolon
id|skb-&gt;dev
op_assign
id|dev
suffix:semicolon
multiline_comment|/* Mark as being used by this device. */
id|tp-&gt;rx_ring
(braket
id|entry
)braket
dot
id|buffer1
op_assign
id|cpu_to_le32
c_func
(paren
id|mapping
)paren
suffix:semicolon
id|refilled
op_increment
suffix:semicolon
)brace
id|tp-&gt;rx_ring
(braket
id|entry
)braket
dot
id|status
op_assign
id|cpu_to_le32
c_func
(paren
id|DescOwned
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|tp-&gt;chip_id
op_eq
id|LC82C168
)paren
(brace
r_if
c_cond
(paren
(paren
(paren
id|inl
c_func
(paren
id|dev-&gt;base_addr
op_plus
id|CSR5
)paren
op_rshift
l_int|17
)paren
op_amp
l_int|0x07
)paren
op_eq
l_int|4
)paren
(brace
multiline_comment|/* Rx stopped due to out of buffers,&n;&t;&t;&t; * restart it&n;&t;&t;&t; */
id|outl
c_func
(paren
l_int|0x01
comma
id|dev-&gt;base_addr
op_plus
id|CSR2
)paren
suffix:semicolon
)brace
)brace
r_return
id|refilled
suffix:semicolon
)brace
DECL|function|tulip_rx
r_static
r_int
id|tulip_rx
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|tulip_private
op_star
id|tp
op_assign
(paren
r_struct
id|tulip_private
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
r_int
id|entry
op_assign
id|tp-&gt;cur_rx
op_mod
id|RX_RING_SIZE
suffix:semicolon
r_int
id|rx_work_limit
op_assign
id|tp-&gt;dirty_rx
op_plus
id|RX_RING_SIZE
op_minus
id|tp-&gt;cur_rx
suffix:semicolon
r_int
id|received
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef CONFIG_NET_HW_FLOWCONTROL
r_int
id|drop
op_assign
l_int|0
comma
id|mit_sel
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* that one buffer is needed for mit activation; or might be a&n;   bug in the ring buffer code; check later -- JHS*/
r_if
c_cond
(paren
id|rx_work_limit
op_ge
id|RX_RING_SIZE
)paren
id|rx_work_limit
op_decrement
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|tulip_debug
OG
l_int|4
)paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot; In tulip_rx(), entry %d %8.8x.&bslash;n&quot;
comma
id|entry
comma
id|tp-&gt;rx_ring
(braket
id|entry
)braket
dot
id|status
)paren
suffix:semicolon
multiline_comment|/* If we own the next entry, it is a new packet. Send it up. */
r_while
c_loop
(paren
op_logical_neg
(paren
id|tp-&gt;rx_ring
(braket
id|entry
)braket
dot
id|status
op_amp
id|cpu_to_le32
c_func
(paren
id|DescOwned
)paren
)paren
)paren
(brace
id|s32
id|status
op_assign
id|le32_to_cpu
c_func
(paren
id|tp-&gt;rx_ring
(braket
id|entry
)braket
dot
id|status
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tulip_debug
OG
l_int|5
)paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s: In tulip_rx(), entry %d %8.8x.&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|entry
comma
id|status
)paren
suffix:semicolon
r_if
c_cond
(paren
op_decrement
id|rx_work_limit
OL
l_int|0
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
(paren
id|status
op_amp
l_int|0x38008300
)paren
op_ne
l_int|0x0300
)paren
(brace
r_if
c_cond
(paren
(paren
id|status
op_amp
l_int|0x38000300
)paren
op_ne
l_int|0x0300
)paren
(brace
multiline_comment|/* Ingore earlier buffers. */
r_if
c_cond
(paren
(paren
id|status
op_amp
l_int|0xffff
)paren
op_ne
l_int|0x7fff
)paren
(brace
r_if
c_cond
(paren
id|tulip_debug
OG
l_int|1
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: Oversized Ethernet frame &quot;
l_string|&quot;spanned multiple buffers, status %8.8x!&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|status
)paren
suffix:semicolon
id|tp-&gt;stats.rx_length_errors
op_increment
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|status
op_amp
id|RxDescFatalErr
)paren
(brace
multiline_comment|/* There was a fatal error. */
r_if
c_cond
(paren
id|tulip_debug
OG
l_int|2
)paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s: Receive error, Rx status %8.8x.&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|status
)paren
suffix:semicolon
id|tp-&gt;stats.rx_errors
op_increment
suffix:semicolon
multiline_comment|/* end of a packet.*/
r_if
c_cond
(paren
id|status
op_amp
l_int|0x0890
)paren
id|tp-&gt;stats.rx_length_errors
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
l_int|0x0004
)paren
id|tp-&gt;stats.rx_frame_errors
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
l_int|0x0002
)paren
id|tp-&gt;stats.rx_crc_errors
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
l_int|0x0001
)paren
id|tp-&gt;stats.rx_fifo_errors
op_increment
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/* Omit the four octet CRC from the length. */
r_int
id|pkt_len
op_assign
(paren
(paren
id|status
op_rshift
l_int|16
)paren
op_amp
l_int|0x7ff
)paren
op_minus
l_int|4
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
macro_line|#ifndef final_version
r_if
c_cond
(paren
id|pkt_len
OG
l_int|1518
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: Bogus packet size of %d (%#x).&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|pkt_len
comma
id|pkt_len
)paren
suffix:semicolon
id|pkt_len
op_assign
l_int|1518
suffix:semicolon
id|tp-&gt;stats.rx_length_errors
op_increment
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef CONFIG_NET_HW_FLOWCONTROL
id|drop
op_assign
id|atomic_read
c_func
(paren
op_amp
id|netdev_dropping
)paren
suffix:semicolon
r_if
c_cond
(paren
id|drop
)paren
r_goto
id|throttle
suffix:semicolon
macro_line|#endif
multiline_comment|/* Check if the packet is long enough to accept without copying&n;&t;&t;&t;   to a minimally-sized skbuff. */
r_if
c_cond
(paren
id|pkt_len
OL
id|tulip_rx_copybreak
op_logical_and
(paren
id|skb
op_assign
id|dev_alloc_skb
c_func
(paren
id|pkt_len
op_plus
l_int|2
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
id|skb-&gt;dev
op_assign
id|dev
suffix:semicolon
id|skb_reserve
c_func
(paren
id|skb
comma
l_int|2
)paren
suffix:semicolon
multiline_comment|/* 16 byte align the IP header */
id|pci_dma_sync_single
c_func
(paren
id|tp-&gt;pdev
comma
id|tp-&gt;rx_buffers
(braket
id|entry
)braket
dot
id|mapping
comma
id|pkt_len
comma
id|PCI_DMA_FROMDEVICE
)paren
suffix:semicolon
macro_line|#if ! defined(__alpha__)
id|eth_copy_and_sum
c_func
(paren
id|skb
comma
id|tp-&gt;rx_buffers
(braket
id|entry
)braket
dot
id|skb-&gt;tail
comma
id|pkt_len
comma
l_int|0
)paren
suffix:semicolon
id|skb_put
c_func
(paren
id|skb
comma
id|pkt_len
)paren
suffix:semicolon
macro_line|#else
id|memcpy
c_func
(paren
id|skb_put
c_func
(paren
id|skb
comma
id|pkt_len
)paren
comma
id|tp-&gt;rx_buffers
(braket
id|entry
)braket
dot
id|skb-&gt;tail
comma
id|pkt_len
)paren
suffix:semicolon
macro_line|#endif
)brace
r_else
(brace
multiline_comment|/* Pass up the skb already on the Rx ring. */
r_char
op_star
id|temp
op_assign
id|skb_put
c_func
(paren
id|skb
op_assign
id|tp-&gt;rx_buffers
(braket
id|entry
)braket
dot
id|skb
comma
id|pkt_len
)paren
suffix:semicolon
macro_line|#ifndef final_version
r_if
c_cond
(paren
id|tp-&gt;rx_buffers
(braket
id|entry
)braket
dot
id|mapping
op_ne
id|le32_to_cpu
c_func
(paren
id|tp-&gt;rx_ring
(braket
id|entry
)braket
dot
id|buffer1
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: Internal fault: The skbuff addresses &quot;
l_string|&quot;do not match in tulip_rx: %08x vs. %Lx %p / %p.&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|le32_to_cpu
c_func
(paren
id|tp-&gt;rx_ring
(braket
id|entry
)braket
dot
id|buffer1
)paren
comma
(paren
id|u64
)paren
id|tp-&gt;rx_buffers
(braket
id|entry
)braket
dot
id|mapping
comma
id|skb-&gt;head
comma
id|temp
)paren
suffix:semicolon
)brace
macro_line|#endif
id|pci_unmap_single
c_func
(paren
id|tp-&gt;pdev
comma
id|tp-&gt;rx_buffers
(braket
id|entry
)braket
dot
id|mapping
comma
id|PKT_BUF_SZ
comma
id|PCI_DMA_FROMDEVICE
)paren
suffix:semicolon
id|tp-&gt;rx_buffers
(braket
id|entry
)braket
dot
id|skb
op_assign
l_int|NULL
suffix:semicolon
id|tp-&gt;rx_buffers
(braket
id|entry
)braket
dot
id|mapping
op_assign
l_int|0
suffix:semicolon
)brace
id|skb-&gt;protocol
op_assign
id|eth_type_trans
c_func
(paren
id|skb
comma
id|dev
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_NET_HW_FLOWCONTROL
id|mit_sel
op_assign
macro_line|#endif
id|netif_rx
c_func
(paren
id|skb
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_NET_HW_FLOWCONTROL
r_switch
c_cond
(paren
id|mit_sel
)paren
(brace
r_case
id|NET_RX_SUCCESS
suffix:colon
r_case
id|NET_RX_CN_LOW
suffix:colon
r_case
id|NET_RX_CN_MOD
suffix:colon
r_break
suffix:semicolon
r_case
id|NET_RX_CN_HIGH
suffix:colon
id|rx_work_limit
op_sub_assign
id|NET_RX_CN_HIGH
suffix:semicolon
multiline_comment|/* additional*/
r_break
suffix:semicolon
r_case
id|NET_RX_DROP
suffix:colon
id|rx_work_limit
op_assign
op_minus
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;unknown feedback return code %d&bslash;n&quot;
comma
id|mit_sel
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|drop
op_assign
id|atomic_read
c_func
(paren
op_amp
id|netdev_dropping
)paren
suffix:semicolon
r_if
c_cond
(paren
id|drop
)paren
(brace
id|throttle
suffix:colon
id|rx_work_limit
op_assign
op_minus
l_int|1
suffix:semicolon
id|mit_sel
op_assign
id|NET_RX_DROP
suffix:semicolon
r_if
c_cond
(paren
id|tp-&gt;fc_bit
)paren
(brace
r_int
id|ioaddr
op_assign
id|dev-&gt;base_addr
suffix:semicolon
multiline_comment|/* disable Rx &amp; RxNoBuf ints. */
id|outl
c_func
(paren
id|tulip_tbl
(braket
id|tp-&gt;chip_id
)braket
dot
id|valid_intrs
op_amp
id|RX_A_NBF_STOP
comma
id|ioaddr
op_plus
id|CSR7
)paren
suffix:semicolon
id|set_bit
c_func
(paren
id|tp-&gt;fc_bit
comma
op_amp
id|netdev_fc_xoff
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
id|dev-&gt;last_rx
op_assign
id|jiffies
suffix:semicolon
id|tp-&gt;stats.rx_packets
op_increment
suffix:semicolon
id|tp-&gt;stats.rx_bytes
op_add_assign
id|pkt_len
suffix:semicolon
)brace
id|received
op_increment
suffix:semicolon
id|entry
op_assign
(paren
op_increment
id|tp-&gt;cur_rx
)paren
op_mod
id|RX_RING_SIZE
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_NET_HW_FLOWCONTROL
multiline_comment|/* We use this simplistic scheme for IM. It&squot;s proven by&n;           real life installations. We can have IM enabled&n;           continuesly but this would cause unnecessary latency.&n;           Unfortunely we can&squot;t use all the NET_RX_* feedback here.&n;           This would turn on IM for devices that is not contributing&n;           to backlog congestion with unnecessary latency.&n;&n;           We monitor the device RX-ring and have:&n;&n;           HW Interrupt Mitigation either ON or OFF.&n;&n;           ON:  More then 1 pkt received (per intr.) OR we are dropping&n;           OFF: Only 1 pkt received&n;&n;           Note. We only use min and max (0, 15) settings from mit_table */
r_if
c_cond
(paren
id|tp-&gt;flags
op_amp
id|HAS_INTR_MITIGATION
)paren
(brace
r_if
c_cond
(paren
(paren
id|received
OG
l_int|1
op_logical_or
id|mit_sel
op_eq
id|NET_RX_DROP
)paren
op_logical_and
id|tp-&gt;mit_sel
op_ne
l_int|15
)paren
(brace
id|tp-&gt;mit_sel
op_assign
l_int|15
suffix:semicolon
id|tp-&gt;mit_change
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Force IM change */
)brace
r_if
c_cond
(paren
(paren
id|received
op_le
l_int|1
op_logical_and
id|mit_sel
op_ne
id|NET_RX_DROP
)paren
op_logical_and
id|tp-&gt;mit_sel
op_ne
l_int|0
)paren
(brace
id|tp-&gt;mit_sel
op_assign
l_int|0
suffix:semicolon
id|tp-&gt;mit_change
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Force IM change */
)brace
)brace
r_return
id|RX_RING_SIZE
op_plus
l_int|1
suffix:semicolon
multiline_comment|/* maxrx+1 */
macro_line|#else
r_return
id|received
suffix:semicolon
macro_line|#endif
)brace
DECL|function|phy_interrupt
r_static
r_inline
r_int
r_int
id|phy_interrupt
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
macro_line|#ifdef __hppa__
r_int
id|csr12
op_assign
id|inl
c_func
(paren
id|dev-&gt;base_addr
op_plus
id|CSR12
)paren
op_amp
l_int|0xff
suffix:semicolon
r_struct
id|tulip_private
op_star
id|tp
op_assign
(paren
r_struct
id|tulip_private
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
r_if
c_cond
(paren
id|csr12
op_ne
id|tp-&gt;csr12_shadow
)paren
(brace
multiline_comment|/* ack interrupt */
id|outl
c_func
(paren
id|csr12
op_or
l_int|0x02
comma
id|dev-&gt;base_addr
op_plus
id|CSR12
)paren
suffix:semicolon
id|tp-&gt;csr12_shadow
op_assign
id|csr12
suffix:semicolon
multiline_comment|/* do link change stuff */
id|spin_lock
c_func
(paren
op_amp
id|tp-&gt;lock
)paren
suffix:semicolon
id|tulip_check_duplex
c_func
(paren
id|dev
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|tp-&gt;lock
)paren
suffix:semicolon
multiline_comment|/* clear irq ack bit */
id|outl
c_func
(paren
id|csr12
op_amp
op_complement
l_int|0x02
comma
id|dev-&gt;base_addr
op_plus
id|CSR12
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* The interrupt handler does all of the Rx thread work and cleans up&n;   after the Tx thread. */
DECL|function|tulip_interrupt
id|irqreturn_t
id|tulip_interrupt
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_instance
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|net_device
op_star
id|dev
op_assign
(paren
r_struct
id|net_device
op_star
)paren
id|dev_instance
suffix:semicolon
r_struct
id|tulip_private
op_star
id|tp
op_assign
(paren
r_struct
id|tulip_private
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
r_int
id|ioaddr
op_assign
id|dev-&gt;base_addr
suffix:semicolon
r_int
id|csr5
suffix:semicolon
r_int
id|entry
suffix:semicolon
r_int
id|missed
suffix:semicolon
r_int
id|rx
op_assign
l_int|0
suffix:semicolon
r_int
id|tx
op_assign
l_int|0
suffix:semicolon
r_int
id|oi
op_assign
l_int|0
suffix:semicolon
r_int
id|maxrx
op_assign
id|RX_RING_SIZE
suffix:semicolon
r_int
id|maxtx
op_assign
id|TX_RING_SIZE
suffix:semicolon
r_int
id|maxoi
op_assign
id|TX_RING_SIZE
suffix:semicolon
r_int
r_int
id|work_count
op_assign
id|tulip_max_interrupt_work
suffix:semicolon
r_int
r_int
id|handled
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Let&squot;s see whether the interrupt really is for us */
id|csr5
op_assign
id|inl
c_func
(paren
id|ioaddr
op_plus
id|CSR5
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tp-&gt;flags
op_amp
id|HAS_PHY_IRQ
)paren
id|handled
op_assign
id|phy_interrupt
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|csr5
op_amp
(paren
id|NormalIntr
op_or
id|AbnormalIntr
)paren
)paren
op_eq
l_int|0
)paren
r_return
id|IRQ_RETVAL
c_func
(paren
id|handled
)paren
suffix:semicolon
id|tp-&gt;nir
op_increment
suffix:semicolon
r_do
(brace
multiline_comment|/* Acknowledge all of the current interrupt sources ASAP. */
id|outl
c_func
(paren
id|csr5
op_amp
l_int|0x0001ffff
comma
id|ioaddr
op_plus
id|CSR5
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tulip_debug
OG
l_int|4
)paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s: interrupt  csr5=%#8.8x new csr5=%#8.8x.&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|csr5
comma
id|inl
c_func
(paren
id|dev-&gt;base_addr
op_plus
id|CSR5
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|csr5
op_amp
(paren
id|RxIntr
op_or
id|RxNoBuf
)paren
)paren
(brace
macro_line|#ifdef CONFIG_NET_HW_FLOWCONTROL
r_if
c_cond
(paren
(paren
op_logical_neg
id|tp-&gt;fc_bit
)paren
op_logical_or
(paren
op_logical_neg
id|test_bit
c_func
(paren
id|tp-&gt;fc_bit
comma
op_amp
id|netdev_fc_xoff
)paren
)paren
)paren
macro_line|#endif
id|rx
op_add_assign
id|tulip_rx
c_func
(paren
id|dev
)paren
suffix:semicolon
id|tulip_refill_rx
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|csr5
op_amp
(paren
id|TxNoBuf
op_or
id|TxDied
op_or
id|TxIntr
op_or
id|TimerInt
)paren
)paren
(brace
r_int
r_int
id|dirty_tx
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|tp-&gt;lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|dirty_tx
op_assign
id|tp-&gt;dirty_tx
suffix:semicolon
id|tp-&gt;cur_tx
op_minus
id|dirty_tx
OG
l_int|0
suffix:semicolon
id|dirty_tx
op_increment
)paren
(brace
r_int
id|entry
op_assign
id|dirty_tx
op_mod
id|TX_RING_SIZE
suffix:semicolon
r_int
id|status
op_assign
id|le32_to_cpu
c_func
(paren
id|tp-&gt;tx_ring
(braket
id|entry
)braket
dot
id|status
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
OL
l_int|0
)paren
r_break
suffix:semicolon
multiline_comment|/* It still has not been Txed */
multiline_comment|/* Check for Rx filter setup frames. */
r_if
c_cond
(paren
id|tp-&gt;tx_buffers
(braket
id|entry
)braket
dot
id|skb
op_eq
l_int|NULL
)paren
(brace
multiline_comment|/* test because dummy frames not mapped */
r_if
c_cond
(paren
id|tp-&gt;tx_buffers
(braket
id|entry
)braket
dot
id|mapping
)paren
id|pci_unmap_single
c_func
(paren
id|tp-&gt;pdev
comma
id|tp-&gt;tx_buffers
(braket
id|entry
)braket
dot
id|mapping
comma
r_sizeof
(paren
id|tp-&gt;setup_frame
)paren
comma
id|PCI_DMA_TODEVICE
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|status
op_amp
l_int|0x8000
)paren
(brace
multiline_comment|/* There was an major error, log it. */
macro_line|#ifndef final_version
r_if
c_cond
(paren
id|tulip_debug
OG
l_int|1
)paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s: Transmit error, Tx status %8.8x.&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|status
)paren
suffix:semicolon
macro_line|#endif
id|tp-&gt;stats.tx_errors
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
l_int|0x4104
)paren
id|tp-&gt;stats.tx_aborted_errors
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
l_int|0x0C00
)paren
id|tp-&gt;stats.tx_carrier_errors
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
l_int|0x0200
)paren
id|tp-&gt;stats.tx_window_errors
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
l_int|0x0002
)paren
id|tp-&gt;stats.tx_fifo_errors
op_increment
suffix:semicolon
r_if
c_cond
(paren
(paren
id|status
op_amp
l_int|0x0080
)paren
op_logical_and
id|tp-&gt;full_duplex
op_eq
l_int|0
)paren
id|tp-&gt;stats.tx_heartbeat_errors
op_increment
suffix:semicolon
)brace
r_else
(brace
id|tp-&gt;stats.tx_bytes
op_add_assign
id|tp-&gt;tx_buffers
(braket
id|entry
)braket
dot
id|skb-&gt;len
suffix:semicolon
id|tp-&gt;stats.collisions
op_add_assign
(paren
id|status
op_rshift
l_int|3
)paren
op_amp
l_int|15
suffix:semicolon
id|tp-&gt;stats.tx_packets
op_increment
suffix:semicolon
)brace
id|pci_unmap_single
c_func
(paren
id|tp-&gt;pdev
comma
id|tp-&gt;tx_buffers
(braket
id|entry
)braket
dot
id|mapping
comma
id|tp-&gt;tx_buffers
(braket
id|entry
)braket
dot
id|skb-&gt;len
comma
id|PCI_DMA_TODEVICE
)paren
suffix:semicolon
multiline_comment|/* Free the original skb. */
id|dev_kfree_skb_irq
c_func
(paren
id|tp-&gt;tx_buffers
(braket
id|entry
)braket
dot
id|skb
)paren
suffix:semicolon
id|tp-&gt;tx_buffers
(braket
id|entry
)braket
dot
id|skb
op_assign
l_int|NULL
suffix:semicolon
id|tp-&gt;tx_buffers
(braket
id|entry
)braket
dot
id|mapping
op_assign
l_int|0
suffix:semicolon
id|tx
op_increment
suffix:semicolon
)brace
macro_line|#ifndef final_version
r_if
c_cond
(paren
id|tp-&gt;cur_tx
op_minus
id|dirty_tx
OG
id|TX_RING_SIZE
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: Out-of-sync dirty pointer, %d vs. %d.&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|dirty_tx
comma
id|tp-&gt;cur_tx
)paren
suffix:semicolon
id|dirty_tx
op_add_assign
id|TX_RING_SIZE
suffix:semicolon
)brace
macro_line|#endif
r_if
c_cond
(paren
id|tp-&gt;cur_tx
op_minus
id|dirty_tx
OL
id|TX_RING_SIZE
op_minus
l_int|2
)paren
id|netif_wake_queue
c_func
(paren
id|dev
)paren
suffix:semicolon
id|tp-&gt;dirty_tx
op_assign
id|dirty_tx
suffix:semicolon
r_if
c_cond
(paren
id|csr5
op_amp
id|TxDied
)paren
(brace
r_if
c_cond
(paren
id|tulip_debug
OG
l_int|2
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: The transmitter stopped.&quot;
l_string|&quot;  CSR5 is %x, CSR6 %x, new CSR6 %x.&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|csr5
comma
id|inl
c_func
(paren
id|ioaddr
op_plus
id|CSR6
)paren
comma
id|tp-&gt;csr6
)paren
suffix:semicolon
id|tulip_restart_rxtx
c_func
(paren
id|tp
)paren
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|tp-&gt;lock
)paren
suffix:semicolon
)brace
multiline_comment|/* Log errors. */
r_if
c_cond
(paren
id|csr5
op_amp
id|AbnormalIntr
)paren
(brace
multiline_comment|/* Abnormal error summary bit. */
r_if
c_cond
(paren
id|csr5
op_eq
l_int|0xffffffff
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|csr5
op_amp
id|TxJabber
)paren
id|tp-&gt;stats.tx_errors
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|csr5
op_amp
id|TxFIFOUnderflow
)paren
(brace
r_if
c_cond
(paren
(paren
id|tp-&gt;csr6
op_amp
l_int|0xC000
)paren
op_ne
l_int|0xC000
)paren
id|tp-&gt;csr6
op_add_assign
l_int|0x4000
suffix:semicolon
multiline_comment|/* Bump up the Tx threshold */
r_else
id|tp-&gt;csr6
op_or_assign
l_int|0x00200000
suffix:semicolon
multiline_comment|/* Store-n-forward. */
multiline_comment|/* Restart the transmit process. */
id|tulip_restart_rxtx
c_func
(paren
id|tp
)paren
suffix:semicolon
id|outl
c_func
(paren
l_int|0
comma
id|ioaddr
op_plus
id|CSR1
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|csr5
op_amp
(paren
id|RxDied
op_or
id|RxNoBuf
)paren
)paren
(brace
r_if
c_cond
(paren
id|tp-&gt;flags
op_amp
id|COMET_MAC_ADDR
)paren
(brace
id|outl
c_func
(paren
id|tp-&gt;mc_filter
(braket
l_int|0
)braket
comma
id|ioaddr
op_plus
l_int|0xAC
)paren
suffix:semicolon
id|outl
c_func
(paren
id|tp-&gt;mc_filter
(braket
l_int|1
)braket
comma
id|ioaddr
op_plus
l_int|0xB0
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|csr5
op_amp
id|RxDied
)paren
(brace
multiline_comment|/* Missed a Rx frame. */
id|tp-&gt;stats.rx_missed_errors
op_add_assign
id|inl
c_func
(paren
id|ioaddr
op_plus
id|CSR8
)paren
op_amp
l_int|0xffff
suffix:semicolon
macro_line|#ifdef CONFIG_NET_HW_FLOWCONTROL
r_if
c_cond
(paren
id|tp-&gt;fc_bit
op_logical_and
op_logical_neg
id|test_bit
c_func
(paren
id|tp-&gt;fc_bit
comma
op_amp
id|netdev_fc_xoff
)paren
)paren
(brace
id|tp-&gt;stats.rx_errors
op_increment
suffix:semicolon
id|tulip_start_rxtx
c_func
(paren
id|tp
)paren
suffix:semicolon
)brace
macro_line|#else
id|tp-&gt;stats.rx_errors
op_increment
suffix:semicolon
id|tulip_start_rxtx
c_func
(paren
id|tp
)paren
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/*&n;&t;&t;&t; * NB: t21142_lnk_change() does a del_timer_sync(), so be careful if this&n;&t;&t;&t; * call is ever done under the spinlock&n;&t;&t;&t; */
r_if
c_cond
(paren
id|csr5
op_amp
(paren
id|TPLnkPass
op_or
id|TPLnkFail
op_or
l_int|0x08000000
)paren
)paren
(brace
r_if
c_cond
(paren
id|tp-&gt;link_change
)paren
(paren
id|tp-&gt;link_change
)paren
(paren
id|dev
comma
id|csr5
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|csr5
op_amp
id|SytemError
)paren
(brace
r_int
id|error
op_assign
(paren
id|csr5
op_rshift
l_int|23
)paren
op_amp
l_int|7
suffix:semicolon
multiline_comment|/* oops, we hit a PCI error.  The code produced corresponds&n;&t;&t;&t;&t; * to the reason:&n;&t;&t;&t;&t; *  0 - parity error&n;&t;&t;&t;&t; *  1 - master abort&n;&t;&t;&t;&t; *  2 - target abort&n;&t;&t;&t;&t; * Note that on parity error, we should do a software reset&n;&t;&t;&t;&t; * of the chip to get it back into a sane state (according&n;&t;&t;&t;&t; * to the 21142/3 docs that is).&n;&t;&t;&t;&t; *   -- rmk&n;&t;&t;&t;&t; */
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: (%lu) System Error occurred (%d)&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|tp-&gt;nir
comma
id|error
)paren
suffix:semicolon
)brace
multiline_comment|/* Clear all error sources, included undocumented ones! */
id|outl
c_func
(paren
l_int|0x0800f7ba
comma
id|ioaddr
op_plus
id|CSR5
)paren
suffix:semicolon
id|oi
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|csr5
op_amp
id|TimerInt
)paren
(brace
r_if
c_cond
(paren
id|tulip_debug
OG
l_int|2
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: Re-enabling interrupts, %8.8x.&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|csr5
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_NET_HW_FLOWCONTROL
r_if
c_cond
(paren
id|tp-&gt;fc_bit
op_logical_and
(paren
id|test_bit
c_func
(paren
id|tp-&gt;fc_bit
comma
op_amp
id|netdev_fc_xoff
)paren
)paren
)paren
r_if
c_cond
(paren
id|net_ratelimit
c_func
(paren
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;BUG!! enabling interrupt when FC off (timerintr.) &bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
id|outl
c_func
(paren
id|tulip_tbl
(braket
id|tp-&gt;chip_id
)braket
dot
id|valid_intrs
comma
id|ioaddr
op_plus
id|CSR7
)paren
suffix:semicolon
id|tp-&gt;ttimer
op_assign
l_int|0
suffix:semicolon
id|oi
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|tx
OG
id|maxtx
op_logical_or
id|rx
OG
id|maxrx
op_logical_or
id|oi
OG
id|maxoi
)paren
(brace
r_if
c_cond
(paren
id|tulip_debug
OG
l_int|1
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: Too much work during an interrupt, &quot;
l_string|&quot;csr5=0x%8.8x. (%lu) (%d,%d,%d)&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|csr5
comma
id|tp-&gt;nir
comma
id|tx
comma
id|rx
comma
id|oi
)paren
suffix:semicolon
multiline_comment|/* Acknowledge all interrupt sources. */
id|outl
c_func
(paren
l_int|0x8001ffff
comma
id|ioaddr
op_plus
id|CSR5
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tp-&gt;flags
op_amp
id|HAS_INTR_MITIGATION
)paren
(brace
macro_line|#ifdef CONFIG_NET_HW_FLOWCONTROL
r_if
c_cond
(paren
id|tp-&gt;mit_change
)paren
(brace
id|outl
c_func
(paren
id|mit_table
(braket
id|tp-&gt;mit_sel
)braket
comma
id|ioaddr
op_plus
id|CSR11
)paren
suffix:semicolon
id|tp-&gt;mit_change
op_assign
l_int|0
suffix:semicolon
)brace
macro_line|#else
multiline_comment|/* Josip Loncaric at ICASE did extensive experimentation&n;&t;&t;&t;to develop a good interrupt mitigation setting.*/
id|outl
c_func
(paren
l_int|0x8b240000
comma
id|ioaddr
op_plus
id|CSR11
)paren
suffix:semicolon
macro_line|#endif
)brace
r_else
r_if
c_cond
(paren
id|tp-&gt;chip_id
op_eq
id|LC82C168
)paren
(brace
multiline_comment|/* the LC82C168 doesn&squot;t have a hw timer.*/
id|outl
c_func
(paren
l_int|0x00
comma
id|ioaddr
op_plus
id|CSR7
)paren
suffix:semicolon
id|mod_timer
c_func
(paren
op_amp
id|tp-&gt;timer
comma
id|RUN_AT
c_func
(paren
id|HZ
op_div
l_int|50
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Mask all interrupting sources, set timer to&n;&t;&t;&t;&t;re-enable. */
macro_line|#ifndef CONFIG_NET_HW_FLOWCONTROL
id|outl
c_func
(paren
(paren
(paren
op_complement
id|csr5
)paren
op_amp
l_int|0x0001ebef
)paren
op_or
id|AbnormalIntr
op_or
id|TimerInt
comma
id|ioaddr
op_plus
id|CSR7
)paren
suffix:semicolon
id|outl
c_func
(paren
l_int|0x0012
comma
id|ioaddr
op_plus
id|CSR11
)paren
suffix:semicolon
macro_line|#endif
)brace
r_break
suffix:semicolon
)brace
id|work_count
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|work_count
op_eq
l_int|0
)paren
r_break
suffix:semicolon
id|csr5
op_assign
id|inl
c_func
(paren
id|ioaddr
op_plus
id|CSR5
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|csr5
op_amp
(paren
id|NormalIntr
op_or
id|AbnormalIntr
)paren
)paren
op_ne
l_int|0
)paren
suffix:semicolon
id|tulip_refill_rx
c_func
(paren
id|dev
)paren
suffix:semicolon
multiline_comment|/* check if the card is in suspend mode */
id|entry
op_assign
id|tp-&gt;dirty_rx
op_mod
id|RX_RING_SIZE
suffix:semicolon
r_if
c_cond
(paren
id|tp-&gt;rx_buffers
(braket
id|entry
)braket
dot
id|skb
op_eq
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|tulip_debug
OG
l_int|1
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: in rx suspend mode: (%lu) (tp-&gt;cur_rx = %u, ttimer = %d, rx = %d) go/stay in suspend mode&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|tp-&gt;nir
comma
id|tp-&gt;cur_rx
comma
id|tp-&gt;ttimer
comma
id|rx
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tp-&gt;chip_id
op_eq
id|LC82C168
)paren
(brace
id|outl
c_func
(paren
l_int|0x00
comma
id|ioaddr
op_plus
id|CSR7
)paren
suffix:semicolon
id|mod_timer
c_func
(paren
op_amp
id|tp-&gt;timer
comma
id|RUN_AT
c_func
(paren
id|HZ
op_div
l_int|50
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|tp-&gt;ttimer
op_eq
l_int|0
op_logical_or
(paren
id|inl
c_func
(paren
id|ioaddr
op_plus
id|CSR11
)paren
op_amp
l_int|0xffff
)paren
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|tulip_debug
OG
l_int|1
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: in rx suspend mode: (%lu) set timer&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|tp-&gt;nir
)paren
suffix:semicolon
id|outl
c_func
(paren
id|tulip_tbl
(braket
id|tp-&gt;chip_id
)braket
dot
id|valid_intrs
op_or
id|TimerInt
comma
id|ioaddr
op_plus
id|CSR7
)paren
suffix:semicolon
id|outl
c_func
(paren
id|TimerInt
comma
id|ioaddr
op_plus
id|CSR5
)paren
suffix:semicolon
id|outl
c_func
(paren
l_int|12
comma
id|ioaddr
op_plus
id|CSR11
)paren
suffix:semicolon
id|tp-&gt;ttimer
op_assign
l_int|1
suffix:semicolon
)brace
)brace
)brace
r_if
c_cond
(paren
(paren
id|missed
op_assign
id|inl
c_func
(paren
id|ioaddr
op_plus
id|CSR8
)paren
op_amp
l_int|0x1ffff
)paren
)paren
(brace
id|tp-&gt;stats.rx_dropped
op_add_assign
id|missed
op_amp
l_int|0x10000
ques
c_cond
l_int|0x10000
suffix:colon
id|missed
suffix:semicolon
)brace
r_if
c_cond
(paren
id|tulip_debug
OG
l_int|4
)paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s: exiting interrupt, csr5=%#4.4x.&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|inl
c_func
(paren
id|ioaddr
op_plus
id|CSR5
)paren
)paren
suffix:semicolon
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
eof
