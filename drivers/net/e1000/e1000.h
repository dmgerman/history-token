multiline_comment|/*******************************************************************************&n;&n;  This software program is available to you under a choice of one of two&n;  licenses. You may choose to be licensed under either the GNU General Public&n;  License 2.0, June 1991, available at http://www.fsf.org/copyleft/gpl.html,&n;  or the Intel BSD + Patent License, the text of which follows:&n;  &n;  Recipient has requested a license and Intel Corporation (&quot;Intel&quot;) is willing&n;  to grant a license for the software entitled Linux Base Driver for the&n;  Intel(R) PRO/1000 Family of Adapters (e1000) (the &quot;Software&quot;) being provided&n;  by Intel Corporation. The following definitions apply to this license:&n;  &n;  &quot;Licensed Patents&quot; means patent claims licensable by Intel Corporation which&n;  are necessarily infringed by the use of sale of the Software alone or when&n;  combined with the operating system referred to below.&n;  &n;  &quot;Recipient&quot; means the party to whom Intel delivers this Software.&n;  &n;  &quot;Licensee&quot; means Recipient and those third parties that receive a license to&n;  any operating system available under the GNU General Public License 2.0 or&n;  later.&n;  &n;  Copyright (c) 1999 - 2002 Intel Corporation.&n;  All rights reserved.&n;  &n;  The license is provided to Recipient and Recipient&squot;s Licensees under the&n;  following terms.&n;  &n;  Redistribution and use in source and binary forms of the Software, with or&n;  without modification, are permitted provided that the following conditions&n;  are met:&n;  &n;  Redistributions of source code of the Software may retain the above&n;  copyright notice, this list of conditions and the following disclaimer.&n;  &n;  Redistributions in binary form of the Software may reproduce the above&n;  copyright notice, this list of conditions and the following disclaimer in&n;  the documentation and/or materials provided with the distribution.&n;  &n;  Neither the name of Intel Corporation nor the names of its contributors&n;  shall be used to endorse or promote products derived from this Software&n;  without specific prior written permission.&n;  &n;  Intel hereby grants Recipient and Licensees a non-exclusive, worldwide,&n;  royalty-free patent license under Licensed Patents to make, use, sell, offer&n;  to sell, import and otherwise transfer the Software, if any, in source code&n;  and object code form. This license shall include changes to the Software&n;  that are error corrections or other minor changes to the Software that do&n;  not add functionality or features when the Software is incorporated in any&n;  version of an operating system that has been distributed under the GNU&n;  General Public License 2.0 or later. This patent license shall apply to the&n;  combination of the Software and any operating system licensed under the GNU&n;  General Public License 2.0 or later if, at the time Intel provides the&n;  Software to Recipient, such addition of the Software to the then publicly&n;  available versions of such operating systems available under the GNU General&n;  Public License 2.0 or later (whether in gold, beta or alpha form) causes&n;  such combination to be covered by the Licensed Patents. The patent license&n;  shall not apply to any other combinations which include the Software. NO&n;  hardware per se is licensed hereunder.&n;  &n;  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS &quot;AS IS&quot;&n;  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE&n;  IMPLIED WARRANTIES OF MECHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE&n;  ARE DISCLAIMED. IN NO EVENT SHALL INTEL OR IT CONTRIBUTORS BE LIABLE FOR ANY&n;  DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES&n;  (INCLUDING, BUT NOT LIMITED, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;&n;  ANY LOSS OF USE; DATA, OR PROFITS; OR BUSINESS INTERUPTION) HOWEVER CAUSED&n;  AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY OR&n;  TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE&n;  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n;&n;*******************************************************************************/
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
macro_line|#include &lt;asm/uaccess.h&gt;
r_struct
id|e1000_adapter
suffix:semicolon
macro_line|#include &quot;e1000_hw.h&quot;
DECL|macro|BAR_0
mdefine_line|#define BAR_0 0
macro_line|#if DBG
DECL|macro|E1000_DBG
mdefine_line|#define E1000_DBG(args...) printk(KERN_DEBUG &quot;e1000: &quot; args)
macro_line|#else
DECL|macro|E1000_DBG
mdefine_line|#define E1000_DBG(args...)
macro_line|#endif
DECL|macro|E1000_ERR
mdefine_line|#define E1000_ERR(args...) printk(KERN_ERR &quot;e1000: &quot; args)
macro_line|#ifdef CONFIG_PPC
DECL|macro|E1000_MAX_INTR
mdefine_line|#define E1000_MAX_INTR 1
macro_line|#else
DECL|macro|E1000_MAX_INTR
mdefine_line|#define E1000_MAX_INTR 10
macro_line|#endif
multiline_comment|/* Supported Rx Buffer Sizes */
DECL|macro|E1000_RXBUFFER_2048
mdefine_line|#define E1000_RXBUFFER_2048  2048
DECL|macro|E1000_RXBUFFER_4096
mdefine_line|#define E1000_RXBUFFER_4096  4096
DECL|macro|E1000_RXBUFFER_8192
mdefine_line|#define E1000_RXBUFFER_8192  8192
DECL|macro|E1000_RXBUFFER_16384
mdefine_line|#define E1000_RXBUFFER_16384 16384
multiline_comment|/* How many Tx Descriptors do we need to call netif_wake_queue ? */
DECL|macro|E1000_TX_QUEUE_WAKE
mdefine_line|#define E1000_TX_QUEUE_WAKE 16
DECL|macro|E1000_JUMBO_PBA
mdefine_line|#define E1000_JUMBO_PBA      0x00000028
DECL|macro|E1000_DEFAULT_PBA
mdefine_line|#define E1000_DEFAULT_PBA    0x00000030
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
DECL|member|rx_csum
id|boolean_t
id|rx_csum
suffix:semicolon
multiline_comment|/* TX */
DECL|member|tx_ring
r_struct
id|e1000_desc_ring
id|tx_ring
suffix:semicolon
DECL|member|trans_finish
r_int
r_int
id|trans_finish
suffix:semicolon
DECL|member|tx_lock
id|spinlock_t
id|tx_lock
suffix:semicolon
DECL|member|txd_cmd
r_uint32
id|txd_cmd
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
)brace
suffix:semicolon
macro_line|#endif /* _E1000_H_ */
eof
