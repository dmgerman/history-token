multiline_comment|/*lcs.h*/
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/workqueue.h&gt;
macro_line|#include &lt;asm/ccwdev.h&gt;
DECL|macro|VERSION_LCS_H
mdefine_line|#define VERSION_LCS_H &quot;$Revision: 1.19 $&quot;
DECL|macro|LCS_DBF_TEXT
mdefine_line|#define LCS_DBF_TEXT(level, name, text) &bslash;&n;&t;do { &bslash;&n;&t;&t;debug_text_event(lcs_dbf_##name, level, text); &bslash;&n;&t;} while (0)
DECL|macro|LCS_DBF_HEX
mdefine_line|#define LCS_DBF_HEX(level,name,addr,len) &bslash;&n;do { &bslash;&n;&t;debug_event(lcs_dbf_##name,level,(void*)(addr),len); &bslash;&n;} while (0)
DECL|macro|LCS_DBF_TEXT_
mdefine_line|#define LCS_DBF_TEXT_(level,name,text...) &bslash;&n;do {                                       &bslash;&n;&t;sprintf(debug_buffer, text);  &bslash;&n;&t;&t;debug_text_event(lcs_dbf_##name,level, debug_buffer);&bslash;&n;} while (0)
multiline_comment|/**&n; * some more definitions for debug or output stuff&n; */
DECL|macro|PRINTK_HEADER
mdefine_line|#define PRINTK_HEADER&t;&t;&quot; lcs: &quot;
multiline_comment|/**&n; *&t;sysfs related stuff&n; */
DECL|macro|CARD_FROM_DEV
mdefine_line|#define CARD_FROM_DEV(cdev) &bslash;&n;&t;(struct lcs_card *) &bslash;&n;&t;((struct ccwgroup_device *)cdev-&gt;dev.driver_data)-&gt;dev.driver_data;
multiline_comment|/**&n; * CCW commands used in this driver&n; */
DECL|macro|LCS_CCW_WRITE
mdefine_line|#define LCS_CCW_WRITE&t;&t;0x01
DECL|macro|LCS_CCW_READ
mdefine_line|#define LCS_CCW_READ&t;&t;0x02
DECL|macro|LCS_CCW_TRANSFER
mdefine_line|#define LCS_CCW_TRANSFER&t;0x08
multiline_comment|/**&n; * LCS device status primitives&n; */
DECL|macro|LCS_CMD_STARTLAN
mdefine_line|#define LCS_CMD_STARTLAN&t;0x01
DECL|macro|LCS_CMD_STOPLAN
mdefine_line|#define LCS_CMD_STOPLAN&t;&t;0x02
DECL|macro|LCS_CMD_LANSTAT
mdefine_line|#define LCS_CMD_LANSTAT&t;&t;0x04
DECL|macro|LCS_CMD_STARTUP
mdefine_line|#define LCS_CMD_STARTUP&t;&t;0x07
DECL|macro|LCS_CMD_SHUTDOWN
mdefine_line|#define LCS_CMD_SHUTDOWN&t;0x08
DECL|macro|LCS_CMD_QIPASSIST
mdefine_line|#define LCS_CMD_QIPASSIST&t;0xb2
DECL|macro|LCS_CMD_SETIPM
mdefine_line|#define LCS_CMD_SETIPM&t;&t;0xb4
DECL|macro|LCS_CMD_DELIPM
mdefine_line|#define LCS_CMD_DELIPM&t;&t;0xb5
DECL|macro|LCS_INITIATOR_TCPIP
mdefine_line|#define LCS_INITIATOR_TCPIP&t;0x00
DECL|macro|LCS_INITIATOR_LGW
mdefine_line|#define LCS_INITIATOR_LGW&t;0x01
DECL|macro|LCS_STD_CMD_SIZE
mdefine_line|#define LCS_STD_CMD_SIZE&t;16
DECL|macro|LCS_MULTICAST_CMD_SIZE
mdefine_line|#define LCS_MULTICAST_CMD_SIZE&t;404
multiline_comment|/**&n; * LCS IPASSIST MASKS,only used when multicast is switched on&n; */
multiline_comment|/* Not supported by LCS */
DECL|macro|LCS_IPASS_ARP_PROCESSING
mdefine_line|#define LCS_IPASS_ARP_PROCESSING&t;0x0001
DECL|macro|LCS_IPASS_IN_CHECKSUM_SUPPORT
mdefine_line|#define LCS_IPASS_IN_CHECKSUM_SUPPORT&t;0x0002
DECL|macro|LCS_IPASS_OUT_CHECKSUM_SUPPORT
mdefine_line|#define LCS_IPASS_OUT_CHECKSUM_SUPPORT&t;0x0004
DECL|macro|LCS_IPASS_IP_FRAG_REASSEMBLY
mdefine_line|#define LCS_IPASS_IP_FRAG_REASSEMBLY&t;0x0008
DECL|macro|LCS_IPASS_IP_FILTERING
mdefine_line|#define LCS_IPASS_IP_FILTERING&t;&t;0x0010
multiline_comment|/* Supported by lcs 3172 */
DECL|macro|LCS_IPASS_IPV6_SUPPORT
mdefine_line|#define LCS_IPASS_IPV6_SUPPORT&t;&t;0x0020
DECL|macro|LCS_IPASS_MULTICAST_SUPPORT
mdefine_line|#define LCS_IPASS_MULTICAST_SUPPORT&t;0x0040
multiline_comment|/**&n; * LCS sense byte definitions&n; */
DECL|macro|LCS_SENSE_INTERFACE_DISCONNECT
mdefine_line|#define LCS_SENSE_INTERFACE_DISCONNECT&t;0x01
DECL|macro|LCS_SENSE_EQUIPMENT_CHECK
mdefine_line|#define LCS_SENSE_EQUIPMENT_CHECK&t;0x10
DECL|macro|LCS_SENSE_BUS_OUT_CHECK
mdefine_line|#define LCS_SENSE_BUS_OUT_CHECK&t;&t;0x20
DECL|macro|LCS_SENSE_INTERVENTION_REQUIRED
mdefine_line|#define LCS_SENSE_INTERVENTION_REQUIRED 0x40
DECL|macro|LCS_SENSE_CMD_REJECT
mdefine_line|#define LCS_SENSE_CMD_REJECT&t;&t;0x80
DECL|macro|LCS_SENSE_RESETTING_EVENT
mdefine_line|#define LCS_SENSE_RESETTING_EVENT&t;0x0080
DECL|macro|LCS_SENSE_DEVICE_ONLINE
mdefine_line|#define LCS_SENSE_DEVICE_ONLINE&t;&t;0x0020
multiline_comment|/**&n; * LCS packet type definitions&n; */
DECL|macro|LCS_FRAME_TYPE_CONTROL
mdefine_line|#define LCS_FRAME_TYPE_CONTROL&t;&t;0
DECL|macro|LCS_FRAME_TYPE_ENET
mdefine_line|#define LCS_FRAME_TYPE_ENET&t;&t;1
DECL|macro|LCS_FRAME_TYPE_TR
mdefine_line|#define LCS_FRAME_TYPE_TR&t;&t;2
DECL|macro|LCS_FRAME_TYPE_FDDI
mdefine_line|#define LCS_FRAME_TYPE_FDDI&t;&t;7
DECL|macro|LCS_FRAME_TYPE_AUTO
mdefine_line|#define LCS_FRAME_TYPE_AUTO&t;&t;-1
multiline_comment|/**&n; * some more definitions,we will sort them later&n; */
DECL|macro|LCS_ILLEGAL_OFFSET
mdefine_line|#define LCS_ILLEGAL_OFFSET&t;&t;0xffff
DECL|macro|LCS_IOBUFFERSIZE
mdefine_line|#define LCS_IOBUFFERSIZE&t;&t;0x5000
DECL|macro|LCS_NUM_BUFFS
mdefine_line|#define LCS_NUM_BUFFS&t;&t;&t;8&t;/* needs to be power of 2 */
DECL|macro|LCS_MAC_LENGTH
mdefine_line|#define LCS_MAC_LENGTH&t;&t;&t;6
DECL|macro|LCS_INVALID_PORT_NO
mdefine_line|#define LCS_INVALID_PORT_NO&t;&t;-1
DECL|macro|LCS_LANCMD_TIMEOUT_DEFAULT
mdefine_line|#define LCS_LANCMD_TIMEOUT_DEFAULT      5
multiline_comment|/**&n; * Multicast state&n; */
DECL|macro|LCS_IPM_STATE_SET_REQUIRED
mdefine_line|#define&t; LCS_IPM_STATE_SET_REQUIRED&t;0
DECL|macro|LCS_IPM_STATE_DEL_REQUIRED
mdefine_line|#define&t; LCS_IPM_STATE_DEL_REQUIRED&t;1
DECL|macro|LCS_IPM_STATE_ON_CARD
mdefine_line|#define&t; LCS_IPM_STATE_ON_CARD&t;&t;2
multiline_comment|/**&n; * LCS IP Assist declarations&n; * seems to be only used for multicast&n; */
DECL|macro|LCS_IPASS_ARP_PROCESSING
mdefine_line|#define&t; LCS_IPASS_ARP_PROCESSING&t;0x0001
DECL|macro|LCS_IPASS_INBOUND_CSUM_SUPP
mdefine_line|#define&t; LCS_IPASS_INBOUND_CSUM_SUPP&t;0x0002
DECL|macro|LCS_IPASS_OUTBOUND_CSUM_SUPP
mdefine_line|#define&t; LCS_IPASS_OUTBOUND_CSUM_SUPP&t;0x0004
DECL|macro|LCS_IPASS_IP_FRAG_REASSEMBLY
mdefine_line|#define&t; LCS_IPASS_IP_FRAG_REASSEMBLY&t;0x0008
DECL|macro|LCS_IPASS_IP_FILTERING
mdefine_line|#define&t; LCS_IPASS_IP_FILTERING&t;&t;0x0010
DECL|macro|LCS_IPASS_IPV6_SUPPORT
mdefine_line|#define&t; LCS_IPASS_IPV6_SUPPORT&t;&t;0x0020
DECL|macro|LCS_IPASS_MULTICAST_SUPPORT
mdefine_line|#define&t; LCS_IPASS_MULTICAST_SUPPORT&t;0x0040
multiline_comment|/**&n; * LCS Buffer states&n; */
DECL|enum|lcs_buffer_states
r_enum
id|lcs_buffer_states
(brace
DECL|enumerator|BUF_STATE_EMPTY
id|BUF_STATE_EMPTY
comma
multiline_comment|/* buffer is empty */
DECL|enumerator|BUF_STATE_LOCKED
id|BUF_STATE_LOCKED
comma
multiline_comment|/* buffer is locked, don&squot;t touch */
DECL|enumerator|BUF_STATE_READY
id|BUF_STATE_READY
comma
multiline_comment|/* buffer is ready for read/write */
DECL|enumerator|BUF_STATE_PROCESSED
id|BUF_STATE_PROCESSED
comma
)brace
suffix:semicolon
multiline_comment|/**&n; * LCS Channel State Machine declarations&n; */
DECL|enum|lcs_channel_states
r_enum
id|lcs_channel_states
(brace
DECL|enumerator|CH_STATE_INIT
id|CH_STATE_INIT
comma
DECL|enumerator|CH_STATE_HALTED
id|CH_STATE_HALTED
comma
DECL|enumerator|CH_STATE_STOPPED
id|CH_STATE_STOPPED
comma
DECL|enumerator|CH_STATE_RUNNING
id|CH_STATE_RUNNING
comma
DECL|enumerator|CH_STATE_SUSPENDED
id|CH_STATE_SUSPENDED
comma
DECL|enumerator|CH_STATE_CLEARED
id|CH_STATE_CLEARED
comma
)brace
suffix:semicolon
multiline_comment|/**&n; * LCS device state machine&n; */
DECL|enum|lcs_dev_states
r_enum
id|lcs_dev_states
(brace
DECL|enumerator|DEV_STATE_DOWN
id|DEV_STATE_DOWN
comma
DECL|enumerator|DEV_STATE_UP
id|DEV_STATE_UP
comma
DECL|enumerator|DEV_STATE_RECOVER
id|DEV_STATE_RECOVER
comma
)brace
suffix:semicolon
DECL|enum|lcs_threads
r_enum
id|lcs_threads
(brace
DECL|enumerator|LCS_SET_MC_THREAD
id|LCS_SET_MC_THREAD
op_assign
l_int|1
comma
DECL|enumerator|LCS_STARTLAN_THREAD
id|LCS_STARTLAN_THREAD
op_assign
l_int|2
comma
DECL|enumerator|LCS_STOPLAN_THREAD
id|LCS_STOPLAN_THREAD
op_assign
l_int|4
comma
DECL|enumerator|LCS_STARTUP_THREAD
id|LCS_STARTUP_THREAD
op_assign
l_int|8
comma
)brace
suffix:semicolon
multiline_comment|/**&n; * LCS struct declarations&n; */
DECL|struct|lcs_header
r_struct
id|lcs_header
(brace
DECL|member|offset
id|__u16
id|offset
suffix:semicolon
DECL|member|type
id|__u8
id|type
suffix:semicolon
DECL|member|slot
id|__u8
id|slot
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|lcs_ip_mac_pair
r_struct
id|lcs_ip_mac_pair
(brace
DECL|member|ip_addr
id|__u32
id|ip_addr
suffix:semicolon
DECL|member|mac_addr
id|__u8
id|mac_addr
(braket
id|LCS_MAC_LENGTH
)braket
suffix:semicolon
DECL|member|reserved
id|__u8
id|reserved
(braket
l_int|2
)braket
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|lcs_ipm_list
r_struct
id|lcs_ipm_list
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|ipm
r_struct
id|lcs_ip_mac_pair
id|ipm
suffix:semicolon
DECL|member|ipm_state
id|__u8
id|ipm_state
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|lcs_cmd
r_struct
id|lcs_cmd
(brace
DECL|member|offset
id|__u16
id|offset
suffix:semicolon
DECL|member|type
id|__u8
id|type
suffix:semicolon
DECL|member|slot
id|__u8
id|slot
suffix:semicolon
DECL|member|cmd_code
id|__u8
id|cmd_code
suffix:semicolon
DECL|member|initiator
id|__u8
id|initiator
suffix:semicolon
DECL|member|sequence_no
id|__u16
id|sequence_no
suffix:semicolon
DECL|member|return_code
id|__u16
id|return_code
suffix:semicolon
r_union
(brace
r_struct
(brace
DECL|member|lan_type
id|__u8
id|lan_type
suffix:semicolon
DECL|member|portno
id|__u8
id|portno
suffix:semicolon
DECL|member|parameter_count
id|__u16
id|parameter_count
suffix:semicolon
DECL|member|operator_flags
id|__u8
id|operator_flags
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|reserved
id|__u8
id|reserved
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|lcs_std_cmd
)brace
id|lcs_std_cmd
suffix:semicolon
r_struct
(brace
DECL|member|unused1
id|__u16
id|unused1
suffix:semicolon
DECL|member|buff_size
id|__u16
id|buff_size
suffix:semicolon
DECL|member|unused2
id|__u8
id|unused2
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|lcs_startup
)brace
id|lcs_startup
suffix:semicolon
r_struct
(brace
DECL|member|lan_type
id|__u8
id|lan_type
suffix:semicolon
DECL|member|portno
id|__u8
id|portno
suffix:semicolon
DECL|member|unused
id|__u8
id|unused
(braket
l_int|10
)braket
suffix:semicolon
DECL|member|mac_addr
id|__u8
id|mac_addr
(braket
id|LCS_MAC_LENGTH
)braket
suffix:semicolon
DECL|member|num_packets_deblocked
id|__u32
id|num_packets_deblocked
suffix:semicolon
DECL|member|num_packets_blocked
id|__u32
id|num_packets_blocked
suffix:semicolon
DECL|member|num_packets_tx_on_lan
id|__u32
id|num_packets_tx_on_lan
suffix:semicolon
DECL|member|num_tx_errors_detected
id|__u32
id|num_tx_errors_detected
suffix:semicolon
DECL|member|num_tx_packets_disgarded
id|__u32
id|num_tx_packets_disgarded
suffix:semicolon
DECL|member|num_packets_rx_from_lan
id|__u32
id|num_packets_rx_from_lan
suffix:semicolon
DECL|member|num_rx_errors_detected
id|__u32
id|num_rx_errors_detected
suffix:semicolon
DECL|member|num_rx_discarded_nobuffs_avail
id|__u32
id|num_rx_discarded_nobuffs_avail
suffix:semicolon
DECL|member|num_rx_packets_too_large
id|__u32
id|num_rx_packets_too_large
suffix:semicolon
DECL|member|lcs_lanstat_cmd
)brace
id|lcs_lanstat_cmd
suffix:semicolon
macro_line|#ifdef CONFIG_IP_MULTICAST
r_struct
(brace
DECL|member|lan_type
id|__u8
id|lan_type
suffix:semicolon
DECL|member|portno
id|__u8
id|portno
suffix:semicolon
DECL|member|num_ip_pairs
id|__u16
id|num_ip_pairs
suffix:semicolon
DECL|member|ip_assists_supported
id|__u16
id|ip_assists_supported
suffix:semicolon
DECL|member|ip_assists_enabled
id|__u16
id|ip_assists_enabled
suffix:semicolon
DECL|member|version
id|__u16
id|version
suffix:semicolon
r_struct
(brace
r_struct
id|lcs_ip_mac_pair
DECL|member|ip_mac_pair
id|ip_mac_pair
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|response_data
id|__u32
id|response_data
suffix:semicolon
)brace
id|lcs_ipass_ctlmsg
id|__attribute
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|lcs_qipassist
)brace
id|lcs_qipassist
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
macro_line|#endif /*CONFIG_IP_MULTICAST */
DECL|member|cmd
)brace
id|cmd
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/**&n; * Forward declarations.&n; */
r_struct
id|lcs_card
suffix:semicolon
r_struct
id|lcs_channel
suffix:semicolon
multiline_comment|/**&n; * Definition of an lcs buffer.&n; */
DECL|struct|lcs_buffer
r_struct
id|lcs_buffer
(brace
DECL|member|state
r_enum
id|lcs_buffer_states
id|state
suffix:semicolon
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
DECL|member|count
r_int
id|count
suffix:semicolon
multiline_comment|/* Callback for completion notification. */
DECL|member|callback
r_void
(paren
op_star
id|callback
)paren
(paren
r_struct
id|lcs_channel
op_star
comma
r_struct
id|lcs_buffer
op_star
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|lcs_reply
r_struct
id|lcs_reply
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|sequence_no
id|__u16
id|sequence_no
suffix:semicolon
DECL|member|refcnt
id|atomic_t
id|refcnt
suffix:semicolon
multiline_comment|/* Callback for completion notification. */
DECL|member|callback
r_void
(paren
op_star
id|callback
)paren
(paren
r_struct
id|lcs_card
op_star
comma
r_struct
id|lcs_cmd
op_star
)paren
suffix:semicolon
DECL|member|wait_q
id|wait_queue_head_t
id|wait_q
suffix:semicolon
DECL|member|card
r_struct
id|lcs_card
op_star
id|card
suffix:semicolon
DECL|member|received
r_int
id|received
suffix:semicolon
DECL|member|rc
r_int
id|rc
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/**&n; * Definition of an lcs channel&n; */
DECL|struct|lcs_channel
r_struct
id|lcs_channel
(brace
DECL|member|state
r_enum
id|lcs_channel_states
id|state
suffix:semicolon
DECL|member|ccwdev
r_struct
id|ccw_device
op_star
id|ccwdev
suffix:semicolon
DECL|member|ccws
r_struct
id|ccw1
id|ccws
(braket
id|LCS_NUM_BUFFS
op_plus
l_int|1
)braket
suffix:semicolon
DECL|member|wait_q
id|wait_queue_head_t
id|wait_q
suffix:semicolon
DECL|member|irq_tasklet
r_struct
id|tasklet_struct
id|irq_tasklet
suffix:semicolon
DECL|member|iob
r_struct
id|lcs_buffer
id|iob
(braket
id|LCS_NUM_BUFFS
)braket
suffix:semicolon
DECL|member|io_idx
r_int
id|io_idx
suffix:semicolon
DECL|member|buf_idx
r_int
id|buf_idx
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/**&n; * definition of the lcs card&n; */
DECL|struct|lcs_card
r_struct
id|lcs_card
(brace
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|ipm_lock
id|spinlock_t
id|ipm_lock
suffix:semicolon
DECL|member|state
r_enum
id|lcs_dev_states
id|state
suffix:semicolon
DECL|member|dev
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
DECL|member|stats
r_struct
id|net_device_stats
id|stats
suffix:semicolon
DECL|member|lan_type_trans
r_int
r_int
(paren
op_star
id|lan_type_trans
)paren
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
DECL|member|read
r_struct
id|lcs_channel
id|read
suffix:semicolon
DECL|member|write
r_struct
id|lcs_channel
id|write
suffix:semicolon
DECL|member|tx_buffer
r_struct
id|lcs_buffer
op_star
id|tx_buffer
suffix:semicolon
DECL|member|tx_emitted
r_int
id|tx_emitted
suffix:semicolon
DECL|member|lancmd_waiters
r_struct
id|list_head
id|lancmd_waiters
suffix:semicolon
DECL|member|lancmd_timeout
r_int
id|lancmd_timeout
suffix:semicolon
DECL|member|kernel_thread_starter
r_struct
id|work_struct
id|kernel_thread_starter
suffix:semicolon
DECL|member|mask_lock
id|spinlock_t
id|mask_lock
suffix:semicolon
DECL|member|thread_start_mask
r_int
r_int
id|thread_start_mask
suffix:semicolon
DECL|member|thread_running_mask
r_int
r_int
id|thread_running_mask
suffix:semicolon
DECL|member|thread_allowed_mask
r_int
r_int
id|thread_allowed_mask
suffix:semicolon
DECL|member|wait_q
id|wait_queue_head_t
id|wait_q
suffix:semicolon
macro_line|#ifdef CONFIG_IP_MULTICAST
DECL|member|ipm_list
r_struct
id|list_head
id|ipm_list
suffix:semicolon
macro_line|#endif
DECL|member|mac
id|__u8
id|mac
(braket
id|LCS_MAC_LENGTH
)braket
suffix:semicolon
DECL|member|ip_assists_supported
id|__u16
id|ip_assists_supported
suffix:semicolon
DECL|member|ip_assists_enabled
id|__u16
id|ip_assists_enabled
suffix:semicolon
DECL|member|lan_type
id|__s8
id|lan_type
suffix:semicolon
DECL|member|pkt_seq
id|__u32
id|pkt_seq
suffix:semicolon
DECL|member|sequence_no
id|__u16
id|sequence_no
suffix:semicolon
DECL|member|portno
id|__s16
id|portno
suffix:semicolon
multiline_comment|/* Some info copied from probeinfo */
DECL|member|device_forced
id|u8
id|device_forced
suffix:semicolon
DECL|member|max_port_no
id|u8
id|max_port_no
suffix:semicolon
DECL|member|hint_port_no
id|u8
id|hint_port_no
suffix:semicolon
DECL|member|port_protocol_no
id|s16
id|port_protocol_no
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|aligned
c_func
(paren
l_int|8
)paren
)paren
)paren
suffix:semicolon
eof
