multiline_comment|/*&n; *  &n; *  Copyright (C) 2002 Intersil Americas Inc.&n; *  Copyright (C) 2004 Aurelien Alleaume &lt;slts@free.fr&gt;&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; *&n; */
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/etherdevice.h&gt;
macro_line|#include &lt;linux/if_arp.h&gt;
macro_line|#include &quot;isl_38xx.h&quot;
macro_line|#include &quot;islpci_eth.h&quot;
macro_line|#include &quot;islpci_mgt.h&quot;
macro_line|#include &quot;oid_mgt.h&quot;
multiline_comment|/******************************************************************************&n;    Network Interface functions&n;******************************************************************************/
r_void
DECL|function|islpci_eth_cleanup_transmit
id|islpci_eth_cleanup_transmit
c_func
(paren
id|islpci_private
op_star
id|priv
comma
id|isl38xx_control_block
op_star
id|control_block
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
id|u32
id|index
suffix:semicolon
multiline_comment|/* compare the control block read pointer with the free pointer */
r_while
c_loop
(paren
id|priv-&gt;free_data_tx
op_ne
id|le32_to_cpu
c_func
(paren
id|control_block
op_member_access_from_pointer
id|device_curr_frag
(braket
id|ISL38XX_CB_TX_DATA_LQ
)braket
)paren
)paren
(brace
multiline_comment|/* read the index of the first fragment to be freed */
id|index
op_assign
id|priv-&gt;free_data_tx
op_mod
id|ISL38XX_CB_TX_QSIZE
suffix:semicolon
multiline_comment|/* check for holes in the arrays caused by multi fragment frames &n;&t;&t; * searching for the last fragment of a frame */
r_if
c_cond
(paren
id|priv-&gt;pci_map_tx_address
(braket
id|index
)braket
op_ne
(paren
id|dma_addr_t
)paren
l_int|NULL
)paren
(brace
multiline_comment|/* entry is the last fragment of a frame&n;&t;&t;&t; * free the skb structure and unmap pci memory */
id|skb
op_assign
id|priv-&gt;data_low_tx
(braket
id|index
)braket
suffix:semicolon
macro_line|#if VERBOSE &gt; SHOW_ERROR_MESSAGES
id|DEBUG
c_func
(paren
id|SHOW_TRACING
comma
l_string|&quot;cleanup skb %p skb-&gt;data %p skb-&gt;len %u truesize %u&bslash;n &quot;
comma
id|skb
comma
id|skb-&gt;data
comma
id|skb-&gt;len
comma
id|skb-&gt;truesize
)paren
suffix:semicolon
macro_line|#endif
id|pci_unmap_single
c_func
(paren
id|priv-&gt;pdev
comma
id|priv-&gt;pci_map_tx_address
(braket
id|index
)braket
comma
id|skb-&gt;len
comma
id|PCI_DMA_TODEVICE
)paren
suffix:semicolon
id|dev_kfree_skb_irq
c_func
(paren
id|skb
)paren
suffix:semicolon
id|skb
op_assign
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* increment the free data low queue pointer */
id|priv-&gt;free_data_tx
op_increment
suffix:semicolon
)brace
)brace
r_int
DECL|function|islpci_eth_transmit
id|islpci_eth_transmit
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|net_device
op_star
id|ndev
)paren
(brace
id|islpci_private
op_star
id|priv
op_assign
id|netdev_priv
c_func
(paren
id|ndev
)paren
suffix:semicolon
id|isl38xx_control_block
op_star
id|cb
op_assign
id|priv-&gt;control_block
suffix:semicolon
id|u32
id|index
suffix:semicolon
id|dma_addr_t
id|pci_map_address
suffix:semicolon
r_int
id|frame_size
suffix:semicolon
id|isl38xx_fragment
op_star
id|fragment
suffix:semicolon
r_int
id|offset
suffix:semicolon
r_struct
id|sk_buff
op_star
id|newskb
suffix:semicolon
r_int
id|newskb_offset
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
r_char
id|wds_mac
(braket
l_int|6
)braket
suffix:semicolon
id|u32
id|curr_frag
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
macro_line|#if VERBOSE &gt; SHOW_ERROR_MESSAGES
id|DEBUG
c_func
(paren
id|SHOW_FUNCTION_CALLS
comma
l_string|&quot;islpci_eth_transmit &bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* lock the driver code */
id|spin_lock_irqsave
c_func
(paren
op_amp
id|priv-&gt;slock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/* determine the amount of fragments needed to store the frame */
id|frame_size
op_assign
id|skb-&gt;len
OL
id|ETH_ZLEN
ques
c_cond
id|ETH_ZLEN
suffix:colon
id|skb-&gt;len
suffix:semicolon
r_if
c_cond
(paren
id|init_wds
)paren
id|frame_size
op_add_assign
l_int|6
suffix:semicolon
multiline_comment|/* check whether the destination queue has enough fragments for the frame */
id|curr_frag
op_assign
id|le32_to_cpu
c_func
(paren
id|cb-&gt;driver_curr_frag
(braket
id|ISL38XX_CB_TX_DATA_LQ
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|curr_frag
op_minus
id|priv-&gt;free_data_tx
op_ge
id|ISL38XX_CB_TX_QSIZE
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: transmit device queue full when awake&bslash;n&quot;
comma
id|ndev-&gt;name
)paren
suffix:semicolon
id|netif_stop_queue
c_func
(paren
id|ndev
)paren
suffix:semicolon
multiline_comment|/* trigger the device */
id|isl38xx_w32_flush
c_func
(paren
id|priv-&gt;device_base
comma
id|ISL38XX_DEV_INT_UPDATE
comma
id|ISL38XX_DEV_INT_REG
)paren
suffix:semicolon
id|udelay
c_func
(paren
id|ISL38XX_WRITEIO_DELAY
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|EBUSY
suffix:semicolon
r_goto
id|drop_free
suffix:semicolon
)brace
multiline_comment|/* Check alignment and WDS frame formatting. The start of the packet should&n;&t; * be aligned on a 4-byte boundary. If WDS is enabled add another 6 bytes&n;&t; * and add WDS address information */
r_if
c_cond
(paren
(paren
(paren
r_int
)paren
id|skb-&gt;data
op_amp
l_int|0x03
)paren
op_or
id|init_wds
)paren
(brace
multiline_comment|/* get the number of bytes to add and re-allign */
id|offset
op_assign
(paren
l_int|4
op_minus
(paren
r_int
)paren
id|skb-&gt;data
)paren
op_amp
l_int|0x03
suffix:semicolon
id|offset
op_add_assign
id|init_wds
ques
c_cond
l_int|6
suffix:colon
l_int|0
suffix:semicolon
multiline_comment|/* check whether the current skb can be used  */
r_if
c_cond
(paren
op_logical_neg
id|skb_cloned
c_func
(paren
id|skb
)paren
op_logical_and
(paren
id|skb_tailroom
c_func
(paren
id|skb
)paren
op_ge
id|offset
)paren
)paren
(brace
r_int
r_char
op_star
id|src
op_assign
id|skb-&gt;data
suffix:semicolon
macro_line|#if VERBOSE &gt; SHOW_ERROR_MESSAGES
id|DEBUG
c_func
(paren
id|SHOW_TRACING
comma
l_string|&quot;skb offset %i wds %i&bslash;n&quot;
comma
id|offset
comma
id|init_wds
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* align the buffer on 4-byte boundary */
id|skb_reserve
c_func
(paren
id|skb
comma
(paren
l_int|4
op_minus
(paren
r_int
)paren
id|skb-&gt;data
)paren
op_amp
l_int|0x03
)paren
suffix:semicolon
r_if
c_cond
(paren
id|init_wds
)paren
(brace
multiline_comment|/* wds requires an additional address field of 6 bytes */
id|skb_put
c_func
(paren
id|skb
comma
l_int|6
)paren
suffix:semicolon
macro_line|#ifdef ISLPCI_ETH_DEBUG
id|printk
c_func
(paren
l_string|&quot;islpci_eth_transmit:wds_mac&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
id|memmove
c_func
(paren
id|skb-&gt;data
op_plus
l_int|6
comma
id|src
comma
id|skb-&gt;len
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|skb-&gt;data
comma
id|wds_mac
comma
l_int|6
)paren
suffix:semicolon
)brace
r_else
(brace
id|memmove
c_func
(paren
id|skb-&gt;data
comma
id|src
comma
id|skb-&gt;len
)paren
suffix:semicolon
)brace
macro_line|#if VERBOSE &gt; SHOW_ERROR_MESSAGES
id|DEBUG
c_func
(paren
id|SHOW_TRACING
comma
l_string|&quot;memmove %p %p %i &bslash;n&quot;
comma
id|skb-&gt;data
comma
id|src
comma
id|skb-&gt;len
)paren
suffix:semicolon
macro_line|#endif
)brace
r_else
(brace
id|newskb
op_assign
id|dev_alloc_skb
c_func
(paren
id|init_wds
ques
c_cond
id|skb-&gt;len
op_plus
l_int|6
suffix:colon
id|skb-&gt;len
)paren
suffix:semicolon
id|newskb_offset
op_assign
(paren
l_int|4
op_minus
(paren
r_int
)paren
id|newskb-&gt;data
)paren
op_amp
l_int|0x03
suffix:semicolon
multiline_comment|/* Check if newskb-&gt;data is aligned */
r_if
c_cond
(paren
id|newskb_offset
)paren
id|skb_reserve
c_func
(paren
id|newskb
comma
id|newskb_offset
)paren
suffix:semicolon
id|skb_put
c_func
(paren
id|newskb
comma
id|init_wds
ques
c_cond
id|skb-&gt;len
op_plus
l_int|6
suffix:colon
id|skb-&gt;len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|init_wds
)paren
(brace
id|memcpy
c_func
(paren
id|newskb-&gt;data
op_plus
l_int|6
comma
id|skb-&gt;data
comma
id|skb-&gt;len
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|newskb-&gt;data
comma
id|wds_mac
comma
l_int|6
)paren
suffix:semicolon
macro_line|#ifdef ISLPCI_ETH_DEBUG
id|printk
c_func
(paren
l_string|&quot;islpci_eth_transmit:wds_mac&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
)brace
r_else
id|memcpy
c_func
(paren
id|newskb-&gt;data
comma
id|skb-&gt;data
comma
id|skb-&gt;len
)paren
suffix:semicolon
macro_line|#if VERBOSE &gt; SHOW_ERROR_MESSAGES
id|DEBUG
c_func
(paren
id|SHOW_TRACING
comma
l_string|&quot;memcpy %p %p %i wds %i&bslash;n&quot;
comma
id|newskb-&gt;data
comma
id|skb-&gt;data
comma
id|skb-&gt;len
comma
id|init_wds
)paren
suffix:semicolon
macro_line|#endif
id|newskb-&gt;dev
op_assign
id|skb-&gt;dev
suffix:semicolon
id|dev_kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
id|skb
op_assign
id|newskb
suffix:semicolon
)brace
)brace
multiline_comment|/* display the buffer contents for debugging */
macro_line|#if VERBOSE &gt; SHOW_ERROR_MESSAGES
id|DEBUG
c_func
(paren
id|SHOW_BUFFER_CONTENTS
comma
l_string|&quot;&bslash;ntx %p &quot;
comma
id|skb-&gt;data
)paren
suffix:semicolon
id|display_buffer
c_func
(paren
(paren
r_char
op_star
)paren
id|skb-&gt;data
comma
id|skb-&gt;len
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* map the skb buffer to pci memory for DMA operation */
id|pci_map_address
op_assign
id|pci_map_single
c_func
(paren
id|priv-&gt;pdev
comma
(paren
r_void
op_star
)paren
id|skb-&gt;data
comma
id|skb-&gt;len
comma
id|PCI_DMA_TODEVICE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pci_map_address
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: cannot map buffer to PCI&bslash;n&quot;
comma
id|ndev-&gt;name
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|drop_free
suffix:semicolon
)brace
multiline_comment|/* Place the fragment in the control block structure. */
id|index
op_assign
id|curr_frag
op_mod
id|ISL38XX_CB_TX_QSIZE
suffix:semicolon
id|fragment
op_assign
op_amp
id|cb-&gt;tx_data_low
(braket
id|index
)braket
suffix:semicolon
id|priv-&gt;pci_map_tx_address
(braket
id|index
)braket
op_assign
id|pci_map_address
suffix:semicolon
multiline_comment|/* store the skb address for future freeing  */
id|priv-&gt;data_low_tx
(braket
id|index
)braket
op_assign
id|skb
suffix:semicolon
multiline_comment|/* set the proper fragment start address and size information */
id|fragment-&gt;size
op_assign
id|cpu_to_le16
c_func
(paren
id|frame_size
)paren
suffix:semicolon
id|fragment-&gt;flags
op_assign
id|cpu_to_le16
c_func
(paren
l_int|0
)paren
suffix:semicolon
multiline_comment|/* set to 1 if more fragments */
id|fragment-&gt;address
op_assign
id|cpu_to_le32
c_func
(paren
id|pci_map_address
)paren
suffix:semicolon
id|curr_frag
op_increment
suffix:semicolon
multiline_comment|/* The fragment address in the control block must have been&n;&t; * written before announcing the frame buffer to device. */
id|wmb
c_func
(paren
)paren
suffix:semicolon
id|cb-&gt;driver_curr_frag
(braket
id|ISL38XX_CB_TX_DATA_LQ
)braket
op_assign
id|cpu_to_le32
c_func
(paren
id|curr_frag
)paren
suffix:semicolon
r_if
c_cond
(paren
id|curr_frag
op_minus
id|priv-&gt;free_data_tx
op_plus
id|ISL38XX_MIN_QTHRESHOLD
OG
id|ISL38XX_CB_TX_QSIZE
)paren
(brace
multiline_comment|/* stop sends from upper layers */
id|netif_stop_queue
c_func
(paren
id|ndev
)paren
suffix:semicolon
multiline_comment|/* set the full flag for the transmission queue */
id|priv-&gt;data_low_tx_full
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/* trigger the device */
id|islpci_trigger
c_func
(paren
id|priv
)paren
suffix:semicolon
multiline_comment|/* unlock the driver code */
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|priv-&gt;slock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/* set the transmission time */
id|ndev-&gt;trans_start
op_assign
id|jiffies
suffix:semicolon
id|priv-&gt;statistics.tx_packets
op_increment
suffix:semicolon
id|priv-&gt;statistics.tx_bytes
op_add_assign
id|skb-&gt;len
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|drop_free
suffix:colon
multiline_comment|/* free the skbuf structure before aborting */
id|dev_kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
id|skb
op_assign
l_int|NULL
suffix:semicolon
id|priv-&gt;statistics.tx_dropped
op_increment
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|priv-&gt;slock
comma
id|flags
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|islpci_monitor_rx
id|islpci_monitor_rx
c_func
(paren
id|islpci_private
op_star
id|priv
comma
r_struct
id|sk_buff
op_star
op_star
id|skb
)paren
(brace
multiline_comment|/* The card reports full 802.11 packets but with a 20 bytes&n;&t; * header and without the FCS. But there a is a bit that&n;&t; * indicates if the packet is corrupted :-) */
r_struct
id|rfmon_header
op_star
id|hdr
op_assign
(paren
r_struct
id|rfmon_header
op_star
)paren
(paren
op_star
id|skb
)paren
op_member_access_from_pointer
id|data
suffix:semicolon
r_if
c_cond
(paren
id|hdr-&gt;flags
op_amp
l_int|0x01
)paren
multiline_comment|/* This one is bad. Drop it ! */
r_return
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|priv-&gt;ndev-&gt;type
op_eq
id|ARPHRD_IEEE80211_PRISM
)paren
(brace
r_struct
id|avs_80211_1_header
op_star
id|avs
suffix:semicolon
multiline_comment|/* extract the relevant data from the header */
id|u32
id|clock
op_assign
id|hdr-&gt;clock
suffix:semicolon
id|u8
id|rate
op_assign
id|hdr-&gt;rate
suffix:semicolon
id|u16
id|freq
op_assign
id|be16_to_cpu
c_func
(paren
id|hdr-&gt;freq
)paren
suffix:semicolon
id|u8
id|rssi
op_assign
id|hdr-&gt;rssi
suffix:semicolon
id|skb_pull
c_func
(paren
op_star
id|skb
comma
r_sizeof
(paren
r_struct
id|rfmon_header
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb_headroom
c_func
(paren
op_star
id|skb
)paren
OL
r_sizeof
(paren
r_struct
id|avs_80211_1_header
)paren
)paren
(brace
r_struct
id|sk_buff
op_star
id|newskb
op_assign
id|skb_copy_expand
c_func
(paren
op_star
id|skb
comma
r_sizeof
(paren
r_struct
id|avs_80211_1_header
)paren
comma
l_int|0
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|newskb
)paren
(brace
id|kfree_skb
c_func
(paren
op_star
id|skb
)paren
suffix:semicolon
op_star
id|skb
op_assign
id|newskb
suffix:semicolon
)brace
r_else
r_return
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* This behavior is not very subtile... */
)brace
multiline_comment|/* make room for the new header and fill it. */
id|avs
op_assign
(paren
r_struct
id|avs_80211_1_header
op_star
)paren
id|skb_push
c_func
(paren
op_star
id|skb
comma
r_sizeof
(paren
r_struct
id|avs_80211_1_header
)paren
)paren
suffix:semicolon
id|avs-&gt;version
op_assign
id|htonl
c_func
(paren
id|P80211CAPTURE_VERSION
)paren
suffix:semicolon
id|avs-&gt;length
op_assign
id|htonl
c_func
(paren
r_sizeof
(paren
r_struct
id|avs_80211_1_header
)paren
)paren
suffix:semicolon
id|avs-&gt;mactime
op_assign
id|__cpu_to_be64
c_func
(paren
id|clock
)paren
suffix:semicolon
id|avs-&gt;hosttime
op_assign
id|__cpu_to_be64
c_func
(paren
id|jiffies
)paren
suffix:semicolon
id|avs-&gt;phytype
op_assign
id|htonl
c_func
(paren
l_int|6
)paren
suffix:semicolon
multiline_comment|/*OFDM: 6 for (g), 8 for (a) */
id|avs-&gt;channel
op_assign
id|htonl
c_func
(paren
id|channel_of_freq
c_func
(paren
id|freq
)paren
)paren
suffix:semicolon
id|avs-&gt;datarate
op_assign
id|htonl
c_func
(paren
id|rate
op_star
l_int|5
)paren
suffix:semicolon
id|avs-&gt;antenna
op_assign
id|htonl
c_func
(paren
l_int|0
)paren
suffix:semicolon
multiline_comment|/*unknown */
id|avs-&gt;priority
op_assign
id|htonl
c_func
(paren
l_int|0
)paren
suffix:semicolon
multiline_comment|/*unknown */
id|avs-&gt;ssi_type
op_assign
id|htonl
c_func
(paren
l_int|2
)paren
suffix:semicolon
multiline_comment|/*2: dBm, 3: raw RSSI */
id|avs-&gt;ssi_signal
op_assign
id|htonl
c_func
(paren
id|rssi
)paren
suffix:semicolon
id|avs-&gt;ssi_noise
op_assign
id|htonl
c_func
(paren
id|priv-&gt;local_iwstatistics.qual.noise
)paren
suffix:semicolon
multiline_comment|/*better than &squot;undefined&squot;, I assume */
id|avs-&gt;preamble
op_assign
id|htonl
c_func
(paren
l_int|0
)paren
suffix:semicolon
multiline_comment|/*unknown */
id|avs-&gt;encoding
op_assign
id|htonl
c_func
(paren
l_int|0
)paren
suffix:semicolon
multiline_comment|/*unknown */
)brace
r_else
id|skb_pull
c_func
(paren
op_star
id|skb
comma
r_sizeof
(paren
r_struct
id|rfmon_header
)paren
)paren
suffix:semicolon
(paren
op_star
id|skb
)paren
op_member_access_from_pointer
id|protocol
op_assign
id|htons
c_func
(paren
id|ETH_P_802_2
)paren
suffix:semicolon
(paren
op_star
id|skb
)paren
op_member_access_from_pointer
id|mac.raw
op_assign
(paren
op_star
id|skb
)paren
op_member_access_from_pointer
id|data
suffix:semicolon
(paren
op_star
id|skb
)paren
op_member_access_from_pointer
id|pkt_type
op_assign
id|PACKET_OTHERHOST
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_int
DECL|function|islpci_eth_receive
id|islpci_eth_receive
c_func
(paren
id|islpci_private
op_star
id|priv
)paren
(brace
r_struct
id|net_device
op_star
id|ndev
op_assign
id|priv-&gt;ndev
suffix:semicolon
id|isl38xx_control_block
op_star
id|control_block
op_assign
id|priv-&gt;control_block
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
id|u16
id|size
suffix:semicolon
id|u32
id|index
comma
id|offset
suffix:semicolon
r_int
r_char
op_star
id|src
suffix:semicolon
r_int
id|discard
op_assign
l_int|0
suffix:semicolon
macro_line|#if VERBOSE &gt; SHOW_ERROR_MESSAGES
id|DEBUG
c_func
(paren
id|SHOW_FUNCTION_CALLS
comma
l_string|&quot;islpci_eth_receive &bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* the device has written an Ethernet frame in the data area&n;&t; * of the sk_buff without updating the structure, do it now */
id|index
op_assign
id|priv-&gt;free_data_rx
op_mod
id|ISL38XX_CB_RX_QSIZE
suffix:semicolon
id|size
op_assign
id|le16_to_cpu
c_func
(paren
id|control_block-&gt;rx_data_low
(braket
id|index
)braket
dot
id|size
)paren
suffix:semicolon
id|skb
op_assign
id|priv-&gt;data_low_rx
(braket
id|index
)braket
suffix:semicolon
id|offset
op_assign
(paren
(paren
r_int
r_int
)paren
id|le32_to_cpu
c_func
(paren
id|control_block-&gt;rx_data_low
(braket
id|index
)braket
dot
id|address
)paren
op_minus
(paren
r_int
r_int
)paren
id|skb-&gt;data
)paren
op_amp
l_int|3
suffix:semicolon
macro_line|#if VERBOSE &gt; SHOW_ERROR_MESSAGES
id|DEBUG
c_func
(paren
id|SHOW_TRACING
comma
l_string|&quot;frq-&gt;addr %x skb-&gt;data %p skb-&gt;len %u offset %u truesize %u&bslash;n &quot;
comma
id|control_block-&gt;rx_data_low
(braket
id|priv-&gt;free_data_rx
)braket
dot
id|address
comma
id|skb-&gt;data
comma
id|skb-&gt;len
comma
id|offset
comma
id|skb-&gt;truesize
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* delete the streaming DMA mapping before processing the skb */
id|pci_unmap_single
c_func
(paren
id|priv-&gt;pdev
comma
id|priv-&gt;pci_map_rx_address
(braket
id|index
)braket
comma
id|MAX_FRAGMENT_SIZE_RX
op_plus
l_int|2
comma
id|PCI_DMA_FROMDEVICE
)paren
suffix:semicolon
multiline_comment|/* update the skb structure and allign the buffer */
id|skb_put
c_func
(paren
id|skb
comma
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|offset
)paren
(brace
multiline_comment|/* shift the buffer allocation offset bytes to get the right frame */
id|skb_pull
c_func
(paren
id|skb
comma
l_int|2
)paren
suffix:semicolon
id|skb_put
c_func
(paren
id|skb
comma
l_int|2
)paren
suffix:semicolon
)brace
macro_line|#if VERBOSE &gt; SHOW_ERROR_MESSAGES
multiline_comment|/* display the buffer contents for debugging */
id|DEBUG
c_func
(paren
id|SHOW_BUFFER_CONTENTS
comma
l_string|&quot;&bslash;nrx %p &quot;
comma
id|skb-&gt;data
)paren
suffix:semicolon
id|display_buffer
c_func
(paren
(paren
r_char
op_star
)paren
id|skb-&gt;data
comma
id|skb-&gt;len
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* check whether WDS is enabled and whether the data frame is a WDS frame */
r_if
c_cond
(paren
id|init_wds
)paren
(brace
multiline_comment|/* WDS enabled, check for the wds address on the first 6 bytes of the buffer */
id|src
op_assign
id|skb-&gt;data
op_plus
l_int|6
suffix:semicolon
id|memmove
c_func
(paren
id|skb-&gt;data
comma
id|src
comma
id|skb-&gt;len
op_minus
l_int|6
)paren
suffix:semicolon
id|skb_trim
c_func
(paren
id|skb
comma
id|skb-&gt;len
op_minus
l_int|6
)paren
suffix:semicolon
)brace
macro_line|#if VERBOSE &gt; SHOW_ERROR_MESSAGES
id|DEBUG
c_func
(paren
id|SHOW_TRACING
comma
l_string|&quot;Fragment size %i in skb at %p&bslash;n&quot;
comma
id|size
comma
id|skb
)paren
suffix:semicolon
id|DEBUG
c_func
(paren
id|SHOW_TRACING
comma
l_string|&quot;Skb data at %p, length %i&bslash;n&quot;
comma
id|skb-&gt;data
comma
id|skb-&gt;len
)paren
suffix:semicolon
multiline_comment|/* display the buffer contents for debugging */
id|DEBUG
c_func
(paren
id|SHOW_BUFFER_CONTENTS
comma
l_string|&quot;&bslash;nrx %p &quot;
comma
id|skb-&gt;data
)paren
suffix:semicolon
id|display_buffer
c_func
(paren
(paren
r_char
op_star
)paren
id|skb-&gt;data
comma
id|skb-&gt;len
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* do some additional sk_buff and network layer parameters */
id|skb-&gt;dev
op_assign
id|ndev
suffix:semicolon
multiline_comment|/* take care of monitor mode and spy monitoring. */
r_if
c_cond
(paren
id|priv-&gt;iw_mode
op_eq
id|IW_MODE_MONITOR
)paren
id|discard
op_assign
id|islpci_monitor_rx
c_func
(paren
id|priv
comma
op_amp
id|skb
)paren
suffix:semicolon
r_else
(brace
r_if
c_cond
(paren
id|skb-&gt;data
(braket
l_int|2
op_star
id|ETH_ALEN
)braket
op_eq
l_int|0
)paren
(brace
multiline_comment|/* The packet has a rx_annex. Read it for spy monitoring, Then&n;&t;&t;&t; * remove it, while keeping the 2 leading MAC addr.&n;&t;&t;&t; */
r_struct
id|iw_quality
id|wstats
suffix:semicolon
r_struct
id|rx_annex_header
op_star
id|annex
op_assign
(paren
r_struct
id|rx_annex_header
op_star
)paren
id|skb-&gt;data
suffix:semicolon
id|wstats.level
op_assign
id|annex-&gt;rfmon.rssi
suffix:semicolon
multiline_comment|/* The noise value can be a bit outdated if nobody&squot;s &n;&t;&t;&t; * reading wireless stats... */
id|wstats.noise
op_assign
id|priv-&gt;local_iwstatistics.qual.noise
suffix:semicolon
id|wstats.qual
op_assign
id|wstats.level
op_minus
id|wstats.noise
suffix:semicolon
id|wstats.updated
op_assign
l_int|0x07
suffix:semicolon
multiline_comment|/* Update spy records */
id|wireless_spy_update
c_func
(paren
id|ndev
comma
id|annex-&gt;addr2
comma
op_amp
id|wstats
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|skb-&gt;data
op_plus
r_sizeof
(paren
r_struct
id|rfmon_header
)paren
comma
id|skb-&gt;data
comma
l_int|2
op_star
id|ETH_ALEN
)paren
suffix:semicolon
id|skb_pull
c_func
(paren
id|skb
comma
r_sizeof
(paren
r_struct
id|rfmon_header
)paren
)paren
suffix:semicolon
)brace
id|skb-&gt;protocol
op_assign
id|eth_type_trans
c_func
(paren
id|skb
comma
id|ndev
)paren
suffix:semicolon
)brace
id|skb-&gt;ip_summed
op_assign
id|CHECKSUM_NONE
suffix:semicolon
id|priv-&gt;statistics.rx_packets
op_increment
suffix:semicolon
id|priv-&gt;statistics.rx_bytes
op_add_assign
id|size
suffix:semicolon
multiline_comment|/* deliver the skb to the network layer */
macro_line|#ifdef ISLPCI_ETH_DEBUG
id|printk
(paren
l_string|&quot;islpci_eth_receive:netif_rx %2.2X %2.2X %2.2X %2.2X %2.2X %2.2X&bslash;n&quot;
comma
id|skb-&gt;data
(braket
l_int|0
)braket
comma
id|skb-&gt;data
(braket
l_int|1
)braket
comma
id|skb-&gt;data
(braket
l_int|2
)braket
comma
id|skb-&gt;data
(braket
l_int|3
)braket
comma
id|skb-&gt;data
(braket
l_int|4
)braket
comma
id|skb-&gt;data
(braket
l_int|5
)braket
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|discard
)paren
(brace
id|dev_kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
id|skb
op_assign
l_int|NULL
suffix:semicolon
)brace
r_else
id|netif_rx
c_func
(paren
id|skb
)paren
suffix:semicolon
multiline_comment|/* increment the read index for the rx data low queue */
id|priv-&gt;free_data_rx
op_increment
suffix:semicolon
multiline_comment|/* add one or more sk_buff structures */
r_while
c_loop
(paren
id|index
op_assign
id|le32_to_cpu
c_func
(paren
id|control_block
op_member_access_from_pointer
id|driver_curr_frag
(braket
id|ISL38XX_CB_RX_DATA_LQ
)braket
)paren
comma
id|index
op_minus
id|priv-&gt;free_data_rx
OL
id|ISL38XX_CB_RX_QSIZE
)paren
(brace
multiline_comment|/* allocate an sk_buff for received data frames storage&n;&t;&t; * include any required allignment operations */
r_if
c_cond
(paren
id|skb
op_assign
id|dev_alloc_skb
c_func
(paren
id|MAX_FRAGMENT_SIZE_RX
op_plus
l_int|2
)paren
comma
id|skb
op_eq
l_int|NULL
)paren
(brace
multiline_comment|/* error allocating an sk_buff structure elements */
id|DEBUG
c_func
(paren
id|SHOW_ERROR_MESSAGES
comma
l_string|&quot;Error allocating skb &bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* store the new skb structure pointer */
id|index
op_assign
id|index
op_mod
id|ISL38XX_CB_RX_QSIZE
suffix:semicolon
id|priv-&gt;data_low_rx
(braket
id|index
)braket
op_assign
id|skb
suffix:semicolon
macro_line|#if VERBOSE &gt; SHOW_ERROR_MESSAGES
id|DEBUG
c_func
(paren
id|SHOW_TRACING
comma
l_string|&quot;new alloc skb %p skb-&gt;data %p skb-&gt;len %u index %u truesize %u&bslash;n &quot;
comma
id|skb
comma
id|skb-&gt;data
comma
id|skb-&gt;len
comma
id|index
comma
id|skb-&gt;truesize
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* set the streaming DMA mapping for proper PCI bus operation */
id|priv-&gt;pci_map_rx_address
(braket
id|index
)braket
op_assign
id|pci_map_single
c_func
(paren
id|priv-&gt;pdev
comma
(paren
r_void
op_star
)paren
id|skb-&gt;data
comma
id|MAX_FRAGMENT_SIZE_RX
op_plus
l_int|2
comma
id|PCI_DMA_FROMDEVICE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|priv-&gt;pci_map_rx_address
(braket
id|index
)braket
op_eq
(paren
id|dma_addr_t
)paren
l_int|NULL
)paren
(brace
multiline_comment|/* error mapping the buffer to device accessable memory address */
id|DEBUG
c_func
(paren
id|SHOW_ERROR_MESSAGES
comma
l_string|&quot;Error mapping DMA address&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* free the skbuf structure before aborting */
id|dev_kfree_skb
c_func
(paren
(paren
r_struct
id|sk_buff
op_star
)paren
id|skb
)paren
suffix:semicolon
id|skb
op_assign
l_int|NULL
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* update the fragment address */
id|control_block-&gt;rx_data_low
(braket
id|index
)braket
dot
id|address
op_assign
id|cpu_to_le32
c_func
(paren
(paren
id|u32
)paren
id|priv
op_member_access_from_pointer
id|pci_map_rx_address
(braket
id|index
)braket
)paren
suffix:semicolon
id|wmb
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* increment the driver read pointer */
id|add_le32p
c_func
(paren
(paren
id|u32
op_star
)paren
op_amp
id|control_block
op_member_access_from_pointer
id|driver_curr_frag
(braket
id|ISL38XX_CB_RX_DATA_LQ
)braket
comma
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/* trigger the device */
id|islpci_trigger
c_func
(paren
id|priv
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_void
DECL|function|islpci_do_reset_and_wake
id|islpci_do_reset_and_wake
c_func
(paren
r_void
op_star
id|data
)paren
(brace
id|islpci_private
op_star
id|priv
op_assign
(paren
id|islpci_private
op_star
)paren
id|data
suffix:semicolon
id|islpci_reset
c_func
(paren
id|priv
comma
l_int|1
)paren
suffix:semicolon
id|netif_wake_queue
c_func
(paren
id|priv-&gt;ndev
)paren
suffix:semicolon
id|priv-&gt;reset_task_pending
op_assign
l_int|0
suffix:semicolon
)brace
r_void
DECL|function|islpci_eth_tx_timeout
id|islpci_eth_tx_timeout
c_func
(paren
r_struct
id|net_device
op_star
id|ndev
)paren
(brace
id|islpci_private
op_star
id|priv
op_assign
id|netdev_priv
c_func
(paren
id|ndev
)paren
suffix:semicolon
r_struct
id|net_device_stats
op_star
id|statistics
op_assign
op_amp
id|priv-&gt;statistics
suffix:semicolon
multiline_comment|/* increment the transmit error counter */
id|statistics-&gt;tx_errors
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|priv-&gt;reset_task_pending
)paren
(brace
id|priv-&gt;reset_task_pending
op_assign
l_int|1
suffix:semicolon
id|netif_stop_queue
c_func
(paren
id|ndev
)paren
suffix:semicolon
id|schedule_work
c_func
(paren
op_amp
id|priv-&gt;reset_task
)paren
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
eof
