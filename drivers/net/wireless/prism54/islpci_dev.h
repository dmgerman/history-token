multiline_comment|/*&n; *  &n; *  Copyright (C) 2002 Intersil Americas Inc. &n; *  Copyright (C) 2003 Herbert Valerio Riedel &lt;hvr@gnu.org&gt;&n; *  Copyright (C) 2003 Luis R. Rodriguez &lt;mcgrof@ruslug.rutgers.edu&gt;&n; *  Copyright (C) 2003 Aurelien Alleaume &lt;slts@free.fr&gt;&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; *&n; */
macro_line|#ifndef _ISLPCI_DEV_H
DECL|macro|_ISLPCI_DEV_H
mdefine_line|#define _ISLPCI_DEV_H
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/wireless.h&gt;
macro_line|#include &lt;net/iw_handler.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &quot;isl_38xx.h&quot;
macro_line|#include &quot;isl_oid.h&quot;
macro_line|#include &quot;islpci_mgt.h&quot;
multiline_comment|/* some states might not be superflous and may be removed when&n;   design is finalized (hvr) */
r_typedef
r_enum
(brace
DECL|enumerator|PRV_STATE_OFF
id|PRV_STATE_OFF
op_assign
l_int|0
comma
multiline_comment|/* this means hw_unavailable is != 0 */
DECL|enumerator|PRV_STATE_PREBOOT
id|PRV_STATE_PREBOOT
comma
multiline_comment|/* we are in a pre-boot state (empty RAM) */
DECL|enumerator|PRV_STATE_BOOT
id|PRV_STATE_BOOT
comma
multiline_comment|/* boot state (fw upload, run fw) */
DECL|enumerator|PRV_STATE_POSTBOOT
id|PRV_STATE_POSTBOOT
comma
multiline_comment|/* after boot state, need reset now */
DECL|enumerator|PRV_STATE_PREINIT
id|PRV_STATE_PREINIT
comma
multiline_comment|/* pre-init state */
DECL|enumerator|PRV_STATE_INIT
id|PRV_STATE_INIT
comma
multiline_comment|/* init state (restore MIB backup to device) */
DECL|enumerator|PRV_STATE_READY
id|PRV_STATE_READY
comma
multiline_comment|/* driver&amp;device are in operational state */
DECL|enumerator|PRV_STATE_SLEEP
id|PRV_STATE_SLEEP
multiline_comment|/* device in sleep mode */
DECL|typedef|islpci_state_t
)brace
id|islpci_state_t
suffix:semicolon
multiline_comment|/* ACL using MAC address */
DECL|struct|mac_entry
r_struct
id|mac_entry
(brace
DECL|member|_list
r_struct
id|list_head
id|_list
suffix:semicolon
DECL|member|addr
r_char
id|addr
(braket
id|ETH_ALEN
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|islpci_acl
r_struct
id|islpci_acl
(brace
DECL|enumerator|MAC_POLICY_OPEN
DECL|enumerator|MAC_POLICY_ACCEPT
DECL|enumerator|MAC_POLICY_REJECT
DECL|member|policy
r_enum
(brace
id|MAC_POLICY_OPEN
op_assign
l_int|0
comma
id|MAC_POLICY_ACCEPT
op_assign
l_int|1
comma
id|MAC_POLICY_REJECT
op_assign
l_int|2
)brace
id|policy
suffix:semicolon
DECL|member|mac_list
r_struct
id|list_head
id|mac_list
suffix:semicolon
multiline_comment|/* a list of mac_entry */
DECL|member|size
r_int
id|size
suffix:semicolon
multiline_comment|/* size of queue */
DECL|member|sem
r_struct
id|semaphore
id|sem
suffix:semicolon
multiline_comment|/* accessed in ioctls and trap_work */
)brace
suffix:semicolon
DECL|struct|islpci_membuf
r_struct
id|islpci_membuf
(brace
DECL|member|size
r_int
id|size
suffix:semicolon
multiline_comment|/* size of memory */
DECL|member|mem
r_void
op_star
id|mem
suffix:semicolon
multiline_comment|/* address of memory as seen by CPU */
DECL|member|pci_addr
id|dma_addr_t
id|pci_addr
suffix:semicolon
multiline_comment|/* address of memory as seen by device */
)brace
suffix:semicolon
DECL|macro|MAX_BSS_WPA_IE_COUNT
mdefine_line|#define MAX_BSS_WPA_IE_COUNT 64
DECL|macro|MAX_WPA_IE_LEN
mdefine_line|#define MAX_WPA_IE_LEN 64
DECL|struct|islpci_bss_wpa_ie
r_struct
id|islpci_bss_wpa_ie
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|last_update
r_int
r_int
id|last_update
suffix:semicolon
DECL|member|bssid
id|u8
id|bssid
(braket
id|ETH_ALEN
)braket
suffix:semicolon
DECL|member|wpa_ie
id|u8
id|wpa_ie
(braket
id|MAX_WPA_IE_LEN
)braket
suffix:semicolon
DECL|member|wpa_ie_len
r_int
id|wpa_ie_len
suffix:semicolon
)brace
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|slock
id|spinlock_t
id|slock
suffix:semicolon
multiline_comment|/* generic spinlock; */
DECL|member|priv_oid
id|u32
id|priv_oid
suffix:semicolon
multiline_comment|/* our mib cache */
DECL|member|iw_mode
id|u32
id|iw_mode
suffix:semicolon
DECL|member|mib_sem
r_struct
id|rw_semaphore
id|mib_sem
suffix:semicolon
DECL|member|mib
r_void
op_star
op_star
id|mib
suffix:semicolon
DECL|member|nickname
r_char
id|nickname
(braket
id|IW_ESSID_MAX_SIZE
op_plus
l_int|1
)braket
suffix:semicolon
multiline_comment|/* Take care of the wireless stats */
DECL|member|stats_work
r_struct
id|work_struct
id|stats_work
suffix:semicolon
DECL|member|stats_sem
r_struct
id|semaphore
id|stats_sem
suffix:semicolon
multiline_comment|/* remember when we last updated the stats */
DECL|member|stats_timestamp
r_int
r_int
id|stats_timestamp
suffix:semicolon
multiline_comment|/* The first is accessed under semaphore locking.&n;&t; * The second is the clean one we return to iwconfig.&n;&t; */
DECL|member|local_iwstatistics
r_struct
id|iw_statistics
id|local_iwstatistics
suffix:semicolon
DECL|member|iwstatistics
r_struct
id|iw_statistics
id|iwstatistics
suffix:semicolon
DECL|member|spy_data
r_struct
id|iw_spy_data
id|spy_data
suffix:semicolon
multiline_comment|/* iwspy support */
macro_line|#if WIRELESS_EXT &gt; 16
DECL|member|wireless_data
r_struct
id|iw_public_data
id|wireless_data
suffix:semicolon
macro_line|#endif /* WIRELESS_EXT &gt; 16 */
DECL|member|monitor_type
r_int
id|monitor_type
suffix:semicolon
multiline_comment|/* ARPHRD_IEEE80211 or ARPHRD_IEEE80211_PRISM */
DECL|member|acl
r_struct
id|islpci_acl
id|acl
suffix:semicolon
multiline_comment|/* PCI bus allocation &amp; configuration members */
DECL|member|pdev
r_struct
id|pci_dev
op_star
id|pdev
suffix:semicolon
multiline_comment|/* PCI structure information */
DECL|member|firmware
r_char
id|firmware
(braket
l_int|33
)braket
suffix:semicolon
DECL|member|device_base
r_void
id|__iomem
op_star
id|device_base
suffix:semicolon
multiline_comment|/* ioremapped device base address */
multiline_comment|/* consistent DMA region */
DECL|member|driver_mem_address
r_void
op_star
id|driver_mem_address
suffix:semicolon
multiline_comment|/* base DMA address */
DECL|member|device_host_address
id|dma_addr_t
id|device_host_address
suffix:semicolon
multiline_comment|/* base DMA address (bus address) */
DECL|member|device_psm_buffer
id|dma_addr_t
id|device_psm_buffer
suffix:semicolon
multiline_comment|/* host memory for PSM buffering (bus address) */
multiline_comment|/* our network_device structure  */
DECL|member|ndev
r_struct
id|net_device
op_star
id|ndev
suffix:semicolon
multiline_comment|/* device queue interface members */
DECL|member|control_block
r_struct
id|isl38xx_cb
op_star
id|control_block
suffix:semicolon
multiline_comment|/* device control block &n;&t;&t;&t;&t;&t;&t;&t;   (== driver_mem_address!) */
multiline_comment|/* Each queue has three indexes:&n;&t; *   free/index_mgmt/data_rx/tx (called index, see below),&n;&t; *   driver_curr_frag, and device_curr_frag (in the control block)&n;&t; * All indexes are ever-increasing, but interpreted modulo the&n;&t; * device queue size when used.&n;&t; *   index &lt;= device_curr_frag &lt;= driver_curr_frag  at all times&n;&t; * For rx queues, [index, device_curr_frag) contains fragments&n;&t; * that the interrupt processing needs to handle (owned by driver).&n;&t; * [device_curr_frag, driver_curr_frag) is the free space in the&n;&t; * rx queue, waiting for data (owned by device).  The driver&n;&t; * increments driver_curr_frag to indicate to the device that more&n;&t; * buffers are available.&n;&t; * If device_curr_frag == driver_curr_frag, no more rx buffers are&n;&t; * available, and the rx DMA engine of the device is halted.&n;&t; * For tx queues, [index, device_curr_frag) contains fragments&n;&t; * where tx is done; they need to be freed (owned by driver).&n;&t; * [device_curr_frag, driver_curr_frag) contains the frames&n;&t; * that are being transferred (owned by device).  The driver&n;&t; * increments driver_curr_frag to indicate that more tx work&n;&t; * needs to be done.&n;&t; */
DECL|member|index_mgmt_rx
id|u32
id|index_mgmt_rx
suffix:semicolon
multiline_comment|/* real index mgmt rx queue */
DECL|member|index_mgmt_tx
id|u32
id|index_mgmt_tx
suffix:semicolon
multiline_comment|/* read index mgmt tx queue */
DECL|member|free_data_rx
id|u32
id|free_data_rx
suffix:semicolon
multiline_comment|/* free pointer data rx queue */
DECL|member|free_data_tx
id|u32
id|free_data_tx
suffix:semicolon
multiline_comment|/* free pointer data tx queue */
DECL|member|data_low_tx_full
id|u32
id|data_low_tx_full
suffix:semicolon
multiline_comment|/* full detected flag */
multiline_comment|/* frame memory buffers for the device queues */
DECL|member|mgmt_tx
r_struct
id|islpci_membuf
id|mgmt_tx
(braket
id|ISL38XX_CB_MGMT_QSIZE
)braket
suffix:semicolon
DECL|member|mgmt_rx
r_struct
id|islpci_membuf
id|mgmt_rx
(braket
id|ISL38XX_CB_MGMT_QSIZE
)braket
suffix:semicolon
DECL|member|data_low_tx
r_struct
id|sk_buff
op_star
id|data_low_tx
(braket
id|ISL38XX_CB_TX_QSIZE
)braket
suffix:semicolon
DECL|member|data_low_rx
r_struct
id|sk_buff
op_star
id|data_low_rx
(braket
id|ISL38XX_CB_RX_QSIZE
)braket
suffix:semicolon
DECL|member|pci_map_tx_address
id|dma_addr_t
id|pci_map_tx_address
(braket
id|ISL38XX_CB_TX_QSIZE
)braket
suffix:semicolon
DECL|member|pci_map_rx_address
id|dma_addr_t
id|pci_map_rx_address
(braket
id|ISL38XX_CB_RX_QSIZE
)braket
suffix:semicolon
multiline_comment|/* driver network interface members */
DECL|member|statistics
r_struct
id|net_device_stats
id|statistics
suffix:semicolon
multiline_comment|/* wait for a reset interrupt */
DECL|member|reset_done
id|wait_queue_head_t
id|reset_done
suffix:semicolon
multiline_comment|/* used by islpci_mgt_transaction */
DECL|member|mgmt_sem
r_struct
id|semaphore
id|mgmt_sem
suffix:semicolon
multiline_comment|/* serialize access to mailbox and wqueue */
DECL|member|mgmt_received
r_struct
id|islpci_mgmtframe
op_star
id|mgmt_received
suffix:semicolon
multiline_comment|/* mbox for incoming frame */
DECL|member|mgmt_wqueue
id|wait_queue_head_t
id|mgmt_wqueue
suffix:semicolon
multiline_comment|/* waitqueue for mbox */
multiline_comment|/* state machine */
DECL|member|state
id|islpci_state_t
id|state
suffix:semicolon
DECL|member|state_off
r_int
id|state_off
suffix:semicolon
multiline_comment|/* enumeration of off-state, if 0 then&n;&t;&t;&t;&t; * we&squot;re not in any off-state */
multiline_comment|/* WPA stuff */
DECL|member|wpa
r_int
id|wpa
suffix:semicolon
multiline_comment|/* WPA mode enabled */
DECL|member|bss_wpa_list
r_struct
id|list_head
id|bss_wpa_list
suffix:semicolon
DECL|member|num_bss_wpa
r_int
id|num_bss_wpa
suffix:semicolon
DECL|member|wpa_sem
r_struct
id|semaphore
id|wpa_sem
suffix:semicolon
DECL|member|reset_task
r_struct
id|work_struct
id|reset_task
suffix:semicolon
DECL|member|reset_task_pending
r_int
id|reset_task_pending
suffix:semicolon
DECL|typedef|islpci_private
)brace
id|islpci_private
suffix:semicolon
r_static
r_inline
id|islpci_state_t
DECL|function|islpci_get_state
id|islpci_get_state
c_func
(paren
id|islpci_private
op_star
id|priv
)paren
(brace
multiline_comment|/* lock */
r_return
id|priv-&gt;state
suffix:semicolon
multiline_comment|/* unlock */
)brace
id|islpci_state_t
id|islpci_set_state
c_func
(paren
id|islpci_private
op_star
id|priv
comma
id|islpci_state_t
id|new_state
)paren
suffix:semicolon
DECL|macro|ISLPCI_TX_TIMEOUT
mdefine_line|#define ISLPCI_TX_TIMEOUT               (2*HZ)
id|irqreturn_t
id|islpci_interrupt
c_func
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
r_int
id|prism54_post_setup
c_func
(paren
id|islpci_private
op_star
comma
r_int
)paren
suffix:semicolon
r_int
id|islpci_reset
c_func
(paren
id|islpci_private
op_star
comma
r_int
)paren
suffix:semicolon
r_static
r_inline
r_void
DECL|function|islpci_trigger
id|islpci_trigger
c_func
(paren
id|islpci_private
op_star
id|priv
)paren
(brace
id|isl38xx_trigger_device
c_func
(paren
id|islpci_get_state
c_func
(paren
id|priv
)paren
op_eq
id|PRV_STATE_SLEEP
comma
id|priv-&gt;device_base
)paren
suffix:semicolon
)brace
r_struct
id|net_device_stats
op_star
id|islpci_statistics
c_func
(paren
r_struct
id|net_device
op_star
)paren
suffix:semicolon
r_int
id|islpci_free_memory
c_func
(paren
id|islpci_private
op_star
)paren
suffix:semicolon
r_struct
id|net_device
op_star
id|islpci_setup
c_func
(paren
r_struct
id|pci_dev
op_star
)paren
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* _ISLPCI_DEV_H */
eof
