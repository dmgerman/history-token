multiline_comment|/*&n; * &n; * ATM Lan Emulation Daemon vs. driver interface&n; *&n; * carnil@cs.tut.fi&n; *&n; */
macro_line|#ifndef _ATMLEC_H_
DECL|macro|_ATMLEC_H_
mdefine_line|#define _ATMLEC_H_
macro_line|#include &lt;linux/atmapi.h&gt;
macro_line|#include &lt;linux/atmioc.h&gt;
macro_line|#include &lt;linux/atm.h&gt;
macro_line|#include &lt;linux/if_ether.h&gt;
multiline_comment|/* ATM lec daemon control socket */
DECL|macro|ATMLEC_CTRL
mdefine_line|#define ATMLEC_CTRL _IO(&squot;a&squot;,ATMIOC_LANE)
DECL|macro|ATMLEC_DATA
mdefine_line|#define ATMLEC_DATA _IO(&squot;a&squot;,ATMIOC_LANE+1)
DECL|macro|ATMLEC_MCAST
mdefine_line|#define ATMLEC_MCAST _IO(&squot;a&squot;,ATMIOC_LANE+2)
multiline_comment|/* Maximum number of LEC interfaces (tweakable) */
DECL|macro|MAX_LEC_ITF
mdefine_line|#define MAX_LEC_ITF 48
multiline_comment|/* From the total of MAX_LEC_ITF, last NUM_TR_DEVS are reserved for Token Ring.&n; * E.g. if MAX_LEC_ITF = 48 and NUM_TR_DEVS = 8, then lec0-lec39 are for&n; * Ethernet ELANs and lec40-lec47 are for Token Ring ELANS.&n; */
DECL|macro|NUM_TR_DEVS
mdefine_line|#define NUM_TR_DEVS 8
r_typedef
r_enum
(brace
DECL|enumerator|l_set_mac_addr
DECL|enumerator|l_del_mac_addr
id|l_set_mac_addr
comma
id|l_del_mac_addr
comma
DECL|enumerator|l_svc_setup
id|l_svc_setup
comma
DECL|enumerator|l_addr_delete
DECL|enumerator|l_topology_change
id|l_addr_delete
comma
id|l_topology_change
comma
DECL|enumerator|l_flush_complete
DECL|enumerator|l_arp_update
id|l_flush_complete
comma
id|l_arp_update
comma
DECL|enumerator|l_narp_req
id|l_narp_req
comma
multiline_comment|/* LANE2 mandates the use of this */
DECL|enumerator|l_config
DECL|enumerator|l_flush_tran_id
id|l_config
comma
id|l_flush_tran_id
comma
DECL|enumerator|l_set_lecid
DECL|enumerator|l_arp_xmt
id|l_set_lecid
comma
id|l_arp_xmt
comma
DECL|enumerator|l_rdesc_arp_xmt
id|l_rdesc_arp_xmt
comma
DECL|enumerator|l_associate_req
id|l_associate_req
comma
DECL|enumerator|l_should_bridge
id|l_should_bridge
multiline_comment|/* should we bridge this MAC? */
DECL|typedef|atmlec_msg_type
)brace
id|atmlec_msg_type
suffix:semicolon
DECL|macro|ATMLEC_MSG_TYPE_MAX
mdefine_line|#define ATMLEC_MSG_TYPE_MAX l_should_bridge
DECL|struct|atmlec_config_msg
r_struct
id|atmlec_config_msg
(brace
DECL|member|maximum_unknown_frame_count
r_int
r_int
id|maximum_unknown_frame_count
suffix:semicolon
DECL|member|max_unknown_frame_time
r_int
r_int
id|max_unknown_frame_time
suffix:semicolon
DECL|member|max_retry_count
r_int
r_int
id|max_retry_count
suffix:semicolon
DECL|member|aging_time
r_int
r_int
id|aging_time
suffix:semicolon
DECL|member|forward_delay_time
r_int
r_int
id|forward_delay_time
suffix:semicolon
DECL|member|arp_response_time
r_int
r_int
id|arp_response_time
suffix:semicolon
DECL|member|flush_timeout
r_int
r_int
id|flush_timeout
suffix:semicolon
DECL|member|path_switching_delay
r_int
r_int
id|path_switching_delay
suffix:semicolon
DECL|member|lane_version
r_int
r_int
id|lane_version
suffix:semicolon
multiline_comment|/* LANE2: 1 for LANEv1, 2 for LANEv2 */
DECL|member|mtu
r_int
id|mtu
suffix:semicolon
DECL|member|is_proxy
r_int
id|is_proxy
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|atmlec_msg
r_struct
id|atmlec_msg
(brace
DECL|member|type
id|atmlec_msg_type
id|type
suffix:semicolon
DECL|member|sizeoftlvs
r_int
id|sizeoftlvs
suffix:semicolon
multiline_comment|/* LANE2: if != 0, tlvs follow */
r_union
(brace
r_struct
(brace
DECL|member|mac_addr
r_int
r_char
id|mac_addr
(braket
id|ETH_ALEN
)braket
suffix:semicolon
DECL|member|atm_addr
r_int
r_char
id|atm_addr
(braket
id|ATM_ESA_LEN
)braket
suffix:semicolon
DECL|member|flag
r_int
r_int
id|flag
suffix:semicolon
multiline_comment|/* Topology_change flag, &n;                                              remoteflag, permanent flag,&n;                                              lecid, transaction id */
DECL|member|targetless_le_arp
r_int
r_int
id|targetless_le_arp
suffix:semicolon
multiline_comment|/* LANE2 */
DECL|member|no_source_le_narp
r_int
r_int
id|no_source_le_narp
suffix:semicolon
multiline_comment|/* LANE2 */
DECL|member|normal
)brace
id|normal
suffix:semicolon
DECL|member|config
r_struct
id|atmlec_config_msg
id|config
suffix:semicolon
r_struct
(brace
DECL|member|lec_id
r_uint16
id|lec_id
suffix:semicolon
multiline_comment|/* requestor lec_id  */
DECL|member|tran_id
r_uint32
id|tran_id
suffix:semicolon
multiline_comment|/* transaction id    */
DECL|member|mac_addr
r_int
r_char
id|mac_addr
(braket
id|ETH_ALEN
)braket
suffix:semicolon
multiline_comment|/* dst mac addr      */
DECL|member|atm_addr
r_int
r_char
id|atm_addr
(braket
id|ATM_ESA_LEN
)braket
suffix:semicolon
multiline_comment|/* reqestor ATM addr */
DECL|member|proxy
)brace
id|proxy
suffix:semicolon
multiline_comment|/* For mapping LE_ARP requests to responses. Filled by */
DECL|member|content
)brace
id|content
suffix:semicolon
multiline_comment|/* zeppelin, returned by kernel. Used only when proxying */
DECL|variable|__ATM_API_ALIGN
)brace
id|__ATM_API_ALIGN
suffix:semicolon
DECL|struct|atmlec_ioc
r_struct
id|atmlec_ioc
(brace
DECL|member|dev_num
r_int
id|dev_num
suffix:semicolon
DECL|member|atm_addr
r_int
r_char
id|atm_addr
(braket
id|ATM_ESA_LEN
)braket
suffix:semicolon
DECL|member|receive
r_int
r_char
id|receive
suffix:semicolon
multiline_comment|/* 1= receive vcc, 0 = send vcc */
)brace
suffix:semicolon
macro_line|#endif /* _ATMLEC_H_ */
eof
