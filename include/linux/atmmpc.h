macro_line|#ifndef _ATMMPC_H_
DECL|macro|_ATMMPC_H_
mdefine_line|#define _ATMMPC_H_
macro_line|#include &lt;linux/atmapi.h&gt;
macro_line|#include &lt;linux/atmioc.h&gt;
macro_line|#include &lt;linux/atm.h&gt;
DECL|macro|ATMMPC_CTRL
mdefine_line|#define ATMMPC_CTRL _IO(&squot;a&squot;, ATMIOC_MPOA)
DECL|macro|ATMMPC_DATA
mdefine_line|#define ATMMPC_DATA _IO(&squot;a&squot;, ATMIOC_MPOA+1)
DECL|macro|MPC_SOCKET_INGRESS
mdefine_line|#define MPC_SOCKET_INGRESS 1
DECL|macro|MPC_SOCKET_EGRESS
mdefine_line|#define MPC_SOCKET_EGRESS  2
DECL|struct|atmmpc_ioc
r_struct
id|atmmpc_ioc
(brace
DECL|member|dev_num
r_int
id|dev_num
suffix:semicolon
DECL|member|ipaddr
r_uint32
id|ipaddr
suffix:semicolon
multiline_comment|/* the IP address of the shortcut    */
DECL|member|type
r_int
id|type
suffix:semicolon
multiline_comment|/* ingress or egress                 */
)brace
suffix:semicolon
DECL|struct|in_ctrl_info
r_typedef
r_struct
id|in_ctrl_info
(brace
DECL|member|Last_NHRP_CIE_code
r_uint8
id|Last_NHRP_CIE_code
suffix:semicolon
DECL|member|Last_Q2931_cause_value
r_uint8
id|Last_Q2931_cause_value
suffix:semicolon
DECL|member|eg_MPC_ATM_addr
r_uint8
id|eg_MPC_ATM_addr
(braket
id|ATM_ESA_LEN
)braket
suffix:semicolon
DECL|member|tag
r_uint32
id|tag
suffix:semicolon
DECL|member|in_dst_ip
r_uint32
id|in_dst_ip
suffix:semicolon
multiline_comment|/* IP address this ingress MPC sends packets to */
DECL|member|holding_time
r_uint16
id|holding_time
suffix:semicolon
DECL|member|request_id
r_uint32
id|request_id
suffix:semicolon
DECL|typedef|in_ctrl_info
)brace
id|in_ctrl_info
suffix:semicolon
DECL|struct|eg_ctrl_info
r_typedef
r_struct
id|eg_ctrl_info
(brace
DECL|member|DLL_header
r_uint8
id|DLL_header
(braket
l_int|256
)braket
suffix:semicolon
DECL|member|DH_length
r_uint8
id|DH_length
suffix:semicolon
DECL|member|cache_id
r_uint32
id|cache_id
suffix:semicolon
DECL|member|tag
r_uint32
id|tag
suffix:semicolon
DECL|member|mps_ip
r_uint32
id|mps_ip
suffix:semicolon
DECL|member|eg_dst_ip
r_uint32
id|eg_dst_ip
suffix:semicolon
multiline_comment|/* IP address to which ingress MPC sends packets */
DECL|member|in_MPC_data_ATM_addr
r_uint8
id|in_MPC_data_ATM_addr
(braket
id|ATM_ESA_LEN
)braket
suffix:semicolon
DECL|member|holding_time
r_uint16
id|holding_time
suffix:semicolon
DECL|typedef|eg_ctrl_info
)brace
id|eg_ctrl_info
suffix:semicolon
DECL|struct|mpc_parameters
r_struct
id|mpc_parameters
(brace
DECL|member|mpc_p1
r_uint16
id|mpc_p1
suffix:semicolon
multiline_comment|/* Shortcut-Setup Frame Count    */
DECL|member|mpc_p2
r_uint16
id|mpc_p2
suffix:semicolon
multiline_comment|/* Shortcut-Setup Frame Time     */
DECL|member|mpc_p3
r_uint8
id|mpc_p3
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* Flow-detection Protocols      */
DECL|member|mpc_p4
r_uint16
id|mpc_p4
suffix:semicolon
multiline_comment|/* MPC Initial Retry Time        */
DECL|member|mpc_p5
r_uint16
id|mpc_p5
suffix:semicolon
multiline_comment|/* MPC Retry Time Maximum        */
DECL|member|mpc_p6
r_uint16
id|mpc_p6
suffix:semicolon
multiline_comment|/* Hold Down Time                */
)brace
suffix:semicolon
DECL|struct|k_message
r_struct
id|k_message
(brace
DECL|member|type
r_uint16
id|type
suffix:semicolon
DECL|member|ip_mask
r_uint32
id|ip_mask
suffix:semicolon
DECL|member|MPS_ctrl
r_uint8
id|MPS_ctrl
(braket
id|ATM_ESA_LEN
)braket
suffix:semicolon
r_union
(brace
DECL|member|in_info
id|in_ctrl_info
id|in_info
suffix:semicolon
DECL|member|eg_info
id|eg_ctrl_info
id|eg_info
suffix:semicolon
DECL|member|params
r_struct
id|mpc_parameters
id|params
suffix:semicolon
DECL|member|content
)brace
id|content
suffix:semicolon
DECL|member|qos
r_struct
id|atm_qos
id|qos
suffix:semicolon
DECL|variable|__ATM_API_ALIGN
)brace
id|__ATM_API_ALIGN
suffix:semicolon
DECL|struct|llc_snap_hdr
r_struct
id|llc_snap_hdr
(brace
multiline_comment|/* RFC 1483 LLC/SNAP encapsulation for routed IP PDUs */
DECL|member|dsap
r_uint8
id|dsap
suffix:semicolon
multiline_comment|/* Destination Service Access Point (0xAA)     */
DECL|member|ssap
r_uint8
id|ssap
suffix:semicolon
multiline_comment|/* Source Service Access Point      (0xAA)     */
DECL|member|ui
r_uint8
id|ui
suffix:semicolon
multiline_comment|/* Unnumbered Information           (0x03)     */
DECL|member|org
r_uint8
id|org
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* Organizational identification    (0x000000) */
DECL|member|type
r_uint8
id|type
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Ether type (for IP)              (0x0800)   */
)brace
suffix:semicolon
multiline_comment|/* TLVs this MPC recognizes */
DECL|macro|TLV_MPOA_DEVICE_TYPE
mdefine_line|#define TLV_MPOA_DEVICE_TYPE         0x00a03e2a  
multiline_comment|/* MPOA device types in MPOA Device Type TLV */
DECL|macro|NON_MPOA
mdefine_line|#define NON_MPOA    0
DECL|macro|MPS
mdefine_line|#define MPS         1
DECL|macro|MPC
mdefine_line|#define MPC         2
DECL|macro|MPS_AND_MPC
mdefine_line|#define MPS_AND_MPC 3
multiline_comment|/* MPC parameter defaults */
DECL|macro|MPC_P1
mdefine_line|#define MPC_P1 10  /* Shortcut-Setup Frame Count  */ 
DECL|macro|MPC_P2
mdefine_line|#define MPC_P2 1   /* Shortcut-Setup Frame Time   */
DECL|macro|MPC_P3
mdefine_line|#define MPC_P3 0   /* Flow-detection Protocols    */
DECL|macro|MPC_P4
mdefine_line|#define MPC_P4 5   /* MPC Initial Retry Time      */
DECL|macro|MPC_P5
mdefine_line|#define MPC_P5 40  /* MPC Retry Time Maximum      */
DECL|macro|MPC_P6
mdefine_line|#define MPC_P6 160 /* Hold Down Time              */
DECL|macro|HOLDING_TIME_DEFAULT
mdefine_line|#define HOLDING_TIME_DEFAULT 1200 /* same as MPS-p7 */
multiline_comment|/* MPC constants */
DECL|macro|MPC_C1
mdefine_line|#define MPC_C1 2   /* Retry Time Multiplier       */
DECL|macro|MPC_C2
mdefine_line|#define MPC_C2 60  /* Initial Keep-Alive Lifetime */
multiline_comment|/* Message types - to MPOA daemon */
DECL|macro|SND_MPOA_RES_RQST
mdefine_line|#define SND_MPOA_RES_RQST    201
DECL|macro|SET_MPS_CTRL_ADDR
mdefine_line|#define SET_MPS_CTRL_ADDR    202
DECL|macro|SND_MPOA_RES_RTRY
mdefine_line|#define SND_MPOA_RES_RTRY    203 /* Different type in a retry due to req id         */
DECL|macro|STOP_KEEP_ALIVE_SM
mdefine_line|#define STOP_KEEP_ALIVE_SM   204
DECL|macro|EGRESS_ENTRY_REMOVED
mdefine_line|#define EGRESS_ENTRY_REMOVED 205
DECL|macro|SND_EGRESS_PURGE
mdefine_line|#define SND_EGRESS_PURGE     206
DECL|macro|DIE
mdefine_line|#define DIE                  207 /* tell the daemon to exit()                       */
DECL|macro|DATA_PLANE_PURGE
mdefine_line|#define DATA_PLANE_PURGE     208 /* Data plane purge because of egress cache hit miss or dead MPS */
DECL|macro|OPEN_INGRESS_SVC
mdefine_line|#define OPEN_INGRESS_SVC     209
multiline_comment|/* Message types - from MPOA daemon */
DECL|macro|MPOA_TRIGGER_RCVD
mdefine_line|#define MPOA_TRIGGER_RCVD     101
DECL|macro|MPOA_RES_REPLY_RCVD
mdefine_line|#define MPOA_RES_REPLY_RCVD   102
DECL|macro|INGRESS_PURGE_RCVD
mdefine_line|#define INGRESS_PURGE_RCVD    103
DECL|macro|EGRESS_PURGE_RCVD
mdefine_line|#define EGRESS_PURGE_RCVD     104
DECL|macro|MPS_DEATH
mdefine_line|#define MPS_DEATH             105
DECL|macro|CACHE_IMPOS_RCVD
mdefine_line|#define CACHE_IMPOS_RCVD      106
DECL|macro|SET_MPC_CTRL_ADDR
mdefine_line|#define SET_MPC_CTRL_ADDR     107 /* Our MPC&squot;s control ATM address   */
DECL|macro|SET_MPS_MAC_ADDR
mdefine_line|#define SET_MPS_MAC_ADDR      108
DECL|macro|CLEAN_UP_AND_EXIT
mdefine_line|#define CLEAN_UP_AND_EXIT     109
DECL|macro|SET_MPC_PARAMS
mdefine_line|#define SET_MPC_PARAMS        110 /* MPC configuration parameters    */
multiline_comment|/* Message types - bidirectional */
DECL|macro|RELOAD
mdefine_line|#define RELOAD                301 /* kill -HUP the daemon for reload */
macro_line|#endif /* _ATMMPC_H_ */
eof
