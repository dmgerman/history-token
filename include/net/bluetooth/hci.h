multiline_comment|/* &n;   BlueZ - Bluetooth protocol stack for Linux&n;   Copyright (C) 2000-2001 Qualcomm Incorporated&n;&n;   Written 2000,2001 by Maxim Krasnyansky &lt;maxk@qualcomm.com&gt;&n;&n;   This program is free software; you can redistribute it and/or modify&n;   it under the terms of the GNU General Public License version 2 as&n;   published by the Free Software Foundation;&n;&n;   THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS&n;   OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n;   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT OF THIRD PARTY RIGHTS.&n;   IN NO EVENT SHALL THE COPYRIGHT HOLDER(S) AND AUTHOR(S) BE LIABLE FOR ANY&n;   CLAIM, OR ANY SPECIAL INDIRECT OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES &n;   WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN &n;   ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF &n;   OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.&n;&n;   ALL LIABILITY, INCLUDING LIABILITY FOR INFRINGEMENT OF ANY PATENTS, &n;   COPYRIGHTS, TRADEMARKS OR OTHER RIGHTS, RELATING TO USE OF THIS &n;   SOFTWARE IS DISCLAIMED.&n;*/
multiline_comment|/*&n; *  $Id: hci.h,v 1.4 2002/04/18 22:26:15 maxk Exp $&n; */
macro_line|#ifndef __HCI_H
DECL|macro|__HCI_H
mdefine_line|#define __HCI_H
DECL|macro|HCI_MAX_ACL_SIZE
mdefine_line|#define HCI_MAX_ACL_SIZE&t;1024
DECL|macro|HCI_MAX_SCO_SIZE
mdefine_line|#define HCI_MAX_SCO_SIZE&t;255
DECL|macro|HCI_MAX_EVENT_SIZE
mdefine_line|#define HCI_MAX_EVENT_SIZE&t;260
DECL|macro|HCI_MAX_FRAME_SIZE
mdefine_line|#define HCI_MAX_FRAME_SIZE&t;(HCI_MAX_ACL_SIZE + 4)
multiline_comment|/* HCI dev events */
DECL|macro|HCI_DEV_REG
mdefine_line|#define HCI_DEV_REG&t;1
DECL|macro|HCI_DEV_UNREG
mdefine_line|#define HCI_DEV_UNREG   2
DECL|macro|HCI_DEV_UP
mdefine_line|#define HCI_DEV_UP&t;3
DECL|macro|HCI_DEV_DOWN
mdefine_line|#define HCI_DEV_DOWN&t;4
multiline_comment|/* HCI device types */
DECL|macro|HCI_VHCI
mdefine_line|#define HCI_VHCI&t;0
DECL|macro|HCI_USB
mdefine_line|#define HCI_USB&t;&t;1
DECL|macro|HCI_PCCARD
mdefine_line|#define HCI_PCCARD&t;2
DECL|macro|HCI_UART
mdefine_line|#define HCI_UART &t;3
DECL|macro|HCI_RS232
mdefine_line|#define HCI_RS232 &t;4
multiline_comment|/* HCI device flags */
r_enum
(brace
DECL|enumerator|HCI_UP
id|HCI_UP
comma
DECL|enumerator|HCI_INIT
id|HCI_INIT
comma
DECL|enumerator|HCI_RUNNING
id|HCI_RUNNING
comma
DECL|enumerator|HCI_PSCAN
id|HCI_PSCAN
comma
DECL|enumerator|HCI_ISCAN
id|HCI_ISCAN
comma
DECL|enumerator|HCI_AUTH
id|HCI_AUTH
comma
DECL|enumerator|HCI_ENCRYPT
id|HCI_ENCRYPT
comma
DECL|enumerator|HCI_INQUIRY
id|HCI_INQUIRY
comma
DECL|enumerator|HCI_RAW
id|HCI_RAW
)brace
suffix:semicolon
multiline_comment|/* HCI ioctl defines */
DECL|macro|HCIDEVUP
mdefine_line|#define HCIDEVUP        _IOW(&squot;H&squot;, 201, int)
DECL|macro|HCIDEVDOWN
mdefine_line|#define HCIDEVDOWN      _IOW(&squot;H&squot;, 202, int)
DECL|macro|HCIDEVRESET
mdefine_line|#define HCIDEVRESET     _IOW(&squot;H&squot;, 203, int)
DECL|macro|HCIDEVRESTAT
mdefine_line|#define HCIDEVRESTAT    _IOW(&squot;H&squot;, 204, int)
DECL|macro|HCIGETDEVLIST
mdefine_line|#define HCIGETDEVLIST   _IOR(&squot;H&squot;, 210, int)
DECL|macro|HCIGETDEVINFO
mdefine_line|#define HCIGETDEVINFO   _IOR(&squot;H&squot;, 211, int)
DECL|macro|HCIGETCONNLIST
mdefine_line|#define HCIGETCONNLIST  _IOR(&squot;H&squot;, 212, int)
DECL|macro|HCIGETCONNINFO
mdefine_line|#define HCIGETCONNINFO  _IOR(&squot;H&squot;, 213, int)
DECL|macro|HCISETRAW
mdefine_line|#define HCISETRAW       _IOW(&squot;H&squot;, 220, int)
DECL|macro|HCISETSCAN
mdefine_line|#define HCISETSCAN      _IOW(&squot;H&squot;, 221, int)
DECL|macro|HCISETAUTH
mdefine_line|#define HCISETAUTH      _IOW(&squot;H&squot;, 222, int)
DECL|macro|HCISETENCRYPT
mdefine_line|#define HCISETENCRYPT   _IOW(&squot;H&squot;, 223, int)
DECL|macro|HCISETPTYPE
mdefine_line|#define HCISETPTYPE     _IOW(&squot;H&squot;, 224, int)
DECL|macro|HCISETLINKPOL
mdefine_line|#define HCISETLINKPOL   _IOW(&squot;H&squot;, 225, int)
DECL|macro|HCISETLINKMODE
mdefine_line|#define HCISETLINKMODE  _IOW(&squot;H&squot;, 226, int)
DECL|macro|HCISETACLMTU
mdefine_line|#define HCISETACLMTU    _IOW(&squot;H&squot;, 227, int)
DECL|macro|HCISETSCOMTU
mdefine_line|#define HCISETSCOMTU    _IOW(&squot;H&squot;, 228, int)
DECL|macro|HCIINQUIRY
mdefine_line|#define HCIINQUIRY      _IOR(&squot;H&squot;, 240, int)
multiline_comment|/* HCI timeouts */
DECL|macro|HCI_CONN_TIMEOUT
mdefine_line|#define HCI_CONN_TIMEOUT &t;(HZ * 40)
DECL|macro|HCI_DISCONN_TIMEOUT
mdefine_line|#define HCI_DISCONN_TIMEOUT &t;(HZ * 2)
DECL|macro|HCI_CONN_IDLE_TIMEOUT
mdefine_line|#define HCI_CONN_IDLE_TIMEOUT&t;(HZ * 60)
multiline_comment|/* HCI Packet types */
DECL|macro|HCI_COMMAND_PKT
mdefine_line|#define HCI_COMMAND_PKT&t;&t;0x01
DECL|macro|HCI_ACLDATA_PKT
mdefine_line|#define HCI_ACLDATA_PKT &t;0x02
DECL|macro|HCI_SCODATA_PKT
mdefine_line|#define HCI_SCODATA_PKT &t;0x03
DECL|macro|HCI_EVENT_PKT
mdefine_line|#define HCI_EVENT_PKT&t;&t;0x04
DECL|macro|HCI_UNKNOWN_PKT
mdefine_line|#define HCI_UNKNOWN_PKT&t;&t;0xff
multiline_comment|/* HCI Packet types */
DECL|macro|HCI_DM1
mdefine_line|#define HCI_DM1 &t;0x0008
DECL|macro|HCI_DM3
mdefine_line|#define HCI_DM3 &t;0x0400
DECL|macro|HCI_DM5
mdefine_line|#define HCI_DM5 &t;0x4000
DECL|macro|HCI_DH1
mdefine_line|#define HCI_DH1 &t;0x0010
DECL|macro|HCI_DH3
mdefine_line|#define HCI_DH3 &t;0x0800
DECL|macro|HCI_DH5
mdefine_line|#define HCI_DH5 &t;0x8000
DECL|macro|HCI_HV1
mdefine_line|#define HCI_HV1&t;&t;0x0020
DECL|macro|HCI_HV2
mdefine_line|#define HCI_HV2&t;&t;0x0040
DECL|macro|HCI_HV3
mdefine_line|#define HCI_HV3&t;&t;0x0080
DECL|macro|SCO_PTYPE_MASK
mdefine_line|#define SCO_PTYPE_MASK&t;(HCI_HV1 | HCI_HV2 | HCI_HV3)
DECL|macro|ACL_PTYPE_MASK
mdefine_line|#define ACL_PTYPE_MASK&t;(~SCO_PTYPE_MASK)
multiline_comment|/* ACL flags */
DECL|macro|ACL_CONT
mdefine_line|#define ACL_CONT&t;&t;0x0001
DECL|macro|ACL_START
mdefine_line|#define ACL_START&t;&t;0x0002
DECL|macro|ACL_ACTIVE_BCAST
mdefine_line|#define ACL_ACTIVE_BCAST&t;0x0010
DECL|macro|ACL_PICO_BCAST
mdefine_line|#define ACL_PICO_BCAST&t;&t;0x0020
multiline_comment|/* Baseband links */
DECL|macro|SCO_LINK
mdefine_line|#define SCO_LINK&t;0x00
DECL|macro|ACL_LINK
mdefine_line|#define ACL_LINK&t;0x01
multiline_comment|/* LMP features */
DECL|macro|LMP_3SLOT
mdefine_line|#define LMP_3SLOT&t;0x01
DECL|macro|LMP_5SLOT
mdefine_line|#define LMP_5SLOT&t;0x02
DECL|macro|LMP_ENCRYPT
mdefine_line|#define LMP_ENCRYPT&t;0x04
DECL|macro|LMP_SOFFSET
mdefine_line|#define LMP_SOFFSET&t;0x08
DECL|macro|LMP_TACCURACY
mdefine_line|#define LMP_TACCURACY&t;0x10
DECL|macro|LMP_RSWITCH
mdefine_line|#define LMP_RSWITCH&t;0x20
DECL|macro|LMP_HOLD
mdefine_line|#define LMP_HOLD&t;0x40
DECL|macro|LMP_SNIF
mdefine_line|#define LMP_SNIF&t;0x80
DECL|macro|LMP_PARK
mdefine_line|#define LMP_PARK&t;0x01
DECL|macro|LMP_RSSI
mdefine_line|#define LMP_RSSI&t;0x02
DECL|macro|LMP_QUALITY
mdefine_line|#define LMP_QUALITY&t;0x04
DECL|macro|LMP_SCO
mdefine_line|#define LMP_SCO&t;&t;0x08
DECL|macro|LMP_HV2
mdefine_line|#define LMP_HV2&t;&t;0x10
DECL|macro|LMP_HV3
mdefine_line|#define LMP_HV3&t;&t;0x20
DECL|macro|LMP_ULAW
mdefine_line|#define LMP_ULAW&t;0x40
DECL|macro|LMP_ALAW
mdefine_line|#define LMP_ALAW&t;0x80
DECL|macro|LMP_CVSD
mdefine_line|#define LMP_CVSD&t;0x01
DECL|macro|LMP_PSCHEME
mdefine_line|#define LMP_PSCHEME&t;0x02
DECL|macro|LMP_PCONTROL
mdefine_line|#define LMP_PCONTROL&t;0x04
multiline_comment|/* Link policies */
DECL|macro|HCI_LP_RSWITCH
mdefine_line|#define HCI_LP_RSWITCH&t;0x0001
DECL|macro|HCI_LP_HOLD
mdefine_line|#define HCI_LP_HOLD&t;0x0002
DECL|macro|HCI_LP_SNIFF
mdefine_line|#define HCI_LP_SNIFF&t;0x0004
DECL|macro|HCI_LP_PARK
mdefine_line|#define HCI_LP_PARK&t;0x0008
multiline_comment|/* Link mode */
DECL|macro|HCI_LM_ACCEPT
mdefine_line|#define HCI_LM_ACCEPT&t;0x8000
DECL|macro|HCI_LM_MASTER
mdefine_line|#define HCI_LM_MASTER&t;0x0001
DECL|macro|HCI_LM_AUTH
mdefine_line|#define HCI_LM_AUTH&t;0x0002
DECL|macro|HCI_LM_ENCRYPT
mdefine_line|#define HCI_LM_ENCRYPT&t;0x0004
DECL|macro|HCI_LM_TRUSTED
mdefine_line|#define HCI_LM_TRUSTED&t;0x0008
multiline_comment|/* -----  HCI Commands ----- */
multiline_comment|/* OGF &amp; OCF values */
multiline_comment|/* Informational Parameters */
DECL|macro|OGF_INFO_PARAM
mdefine_line|#define OGF_INFO_PARAM&t;0x04
DECL|macro|OCF_READ_LOCAL_VERSION
mdefine_line|#define OCF_READ_LOCAL_VERSION&t;0x0001
r_typedef
r_struct
(brace
DECL|member|status
id|__u8
id|status
suffix:semicolon
DECL|member|hci_ver
id|__u8
id|hci_ver
suffix:semicolon
DECL|member|hci_rev
id|__u16
id|hci_rev
suffix:semicolon
DECL|member|lmp_ver
id|__u8
id|lmp_ver
suffix:semicolon
DECL|member|manufacturer
id|__u16
id|manufacturer
suffix:semicolon
DECL|member|lmp_subver
id|__u16
id|lmp_subver
suffix:semicolon
DECL|typedef|read_local_version_rp
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|read_local_version_rp
suffix:semicolon
DECL|macro|READ_LOCAL_VERSION_RP_SIZE
mdefine_line|#define READ_LOCAL_VERSION_RP_SIZE 9
DECL|macro|OCF_READ_LOCAL_FEATURES
mdefine_line|#define OCF_READ_LOCAL_FEATURES&t;0x0003
r_typedef
r_struct
(brace
DECL|member|status
id|__u8
id|status
suffix:semicolon
DECL|member|features
id|__u8
id|features
(braket
l_int|8
)braket
suffix:semicolon
DECL|typedef|read_local_features_rp
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|read_local_features_rp
suffix:semicolon
DECL|macro|OCF_READ_BUFFER_SIZE
mdefine_line|#define OCF_READ_BUFFER_SIZE&t;0x0005
r_typedef
r_struct
(brace
DECL|member|status
id|__u8
id|status
suffix:semicolon
DECL|member|acl_mtu
id|__u16
id|acl_mtu
suffix:semicolon
DECL|member|sco_mtu
id|__u8
id|sco_mtu
suffix:semicolon
DECL|member|acl_max_pkt
id|__u16
id|acl_max_pkt
suffix:semicolon
DECL|member|sco_max_pkt
id|__u16
id|sco_max_pkt
suffix:semicolon
DECL|typedef|read_buffer_size_rp
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|read_buffer_size_rp
suffix:semicolon
DECL|macro|OCF_READ_BD_ADDR
mdefine_line|#define OCF_READ_BD_ADDR&t;0x0009
r_typedef
r_struct
(brace
DECL|member|status
id|__u8
id|status
suffix:semicolon
DECL|member|bdaddr
id|bdaddr_t
id|bdaddr
suffix:semicolon
DECL|typedef|read_bd_addr_rp
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|read_bd_addr_rp
suffix:semicolon
multiline_comment|/* Host Controller and Baseband */
DECL|macro|OGF_HOST_CTL
mdefine_line|#define OGF_HOST_CTL&t;0x03
DECL|macro|OCF_RESET
mdefine_line|#define OCF_RESET&t;&t;0x0003
DECL|macro|OCF_READ_AUTH_ENABLE
mdefine_line|#define OCF_READ_AUTH_ENABLE&t;0x001F
DECL|macro|OCF_WRITE_AUTH_ENABLE
mdefine_line|#define OCF_WRITE_AUTH_ENABLE&t;0x0020
DECL|macro|AUTH_DISABLED
mdefine_line|#define AUTH_DISABLED&t;&t;0x00
DECL|macro|AUTH_ENABLED
mdefine_line|#define AUTH_ENABLED&t;&t;0x01
DECL|macro|OCF_READ_ENCRYPT_MODE
mdefine_line|#define OCF_READ_ENCRYPT_MODE&t;0x0021
DECL|macro|OCF_WRITE_ENCRYPT_MODE
mdefine_line|#define OCF_WRITE_ENCRYPT_MODE&t;0x0022
DECL|macro|ENCRYPT_DISABLED
mdefine_line|#define ENCRYPT_DISABLED&t;0x00
DECL|macro|ENCRYPT_P2P
mdefine_line|#define ENCRYPT_P2P&t;&t;0x01
DECL|macro|ENCRYPT_BOTH
mdefine_line|#define ENCRYPT_BOTH&t;&t;0x02
DECL|macro|OCF_WRITE_CA_TIMEOUT
mdefine_line|#define OCF_WRITE_CA_TIMEOUT  &t;0x0016&t;
DECL|macro|OCF_WRITE_PG_TIMEOUT
mdefine_line|#define OCF_WRITE_PG_TIMEOUT  &t;0x0018
DECL|macro|OCF_WRITE_SCAN_ENABLE
mdefine_line|#define OCF_WRITE_SCAN_ENABLE &t;0x001A
DECL|macro|SCAN_DISABLED
mdefine_line|#define SCAN_DISABLED&t;&t;0x00
DECL|macro|SCAN_INQUIRY
mdefine_line|#define SCAN_INQUIRY&t;&t;0x01
DECL|macro|SCAN_PAGE
mdefine_line|#define SCAN_PAGE&t;&t;0x02
DECL|macro|OCF_SET_EVENT_FLT
mdefine_line|#define OCF_SET_EVENT_FLT&t;0x0005
r_typedef
r_struct
(brace
DECL|member|flt_type
id|__u8
id|flt_type
suffix:semicolon
DECL|member|cond_type
id|__u8
id|cond_type
suffix:semicolon
DECL|member|condition
id|__u8
id|condition
(braket
l_int|0
)braket
suffix:semicolon
DECL|typedef|set_event_flt_cp
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|set_event_flt_cp
suffix:semicolon
DECL|macro|SET_EVENT_FLT_CP_SIZE
mdefine_line|#define SET_EVENT_FLT_CP_SIZE 2
multiline_comment|/* Filter types */
DECL|macro|FLT_CLEAR_ALL
mdefine_line|#define FLT_CLEAR_ALL&t;0x00
DECL|macro|FLT_INQ_RESULT
mdefine_line|#define FLT_INQ_RESULT&t;0x01
DECL|macro|FLT_CONN_SETUP
mdefine_line|#define FLT_CONN_SETUP&t;0x02
multiline_comment|/* CONN_SETUP Condition types */
DECL|macro|CONN_SETUP_ALLOW_ALL
mdefine_line|#define CONN_SETUP_ALLOW_ALL&t;0x00
DECL|macro|CONN_SETUP_ALLOW_CLASS
mdefine_line|#define CONN_SETUP_ALLOW_CLASS&t;0x01
DECL|macro|CONN_SETUP_ALLOW_BDADDR
mdefine_line|#define CONN_SETUP_ALLOW_BDADDR&t;0x02
multiline_comment|/* CONN_SETUP Conditions */
DECL|macro|CONN_SETUP_AUTO_OFF
mdefine_line|#define CONN_SETUP_AUTO_OFF&t;0x01
DECL|macro|CONN_SETUP_AUTO_ON
mdefine_line|#define CONN_SETUP_AUTO_ON&t;0x02
DECL|macro|OCF_CHANGE_LOCAL_NAME
mdefine_line|#define OCF_CHANGE_LOCAL_NAME&t;0x0013
r_typedef
r_struct
(brace
DECL|member|name
id|__u8
id|name
(braket
l_int|248
)braket
suffix:semicolon
DECL|typedef|change_local_name_cp
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|change_local_name_cp
suffix:semicolon
DECL|macro|CHANGE_LOCAL_NAME_CP_SIZE
mdefine_line|#define CHANGE_LOCAL_NAME_CP_SIZE 248 
DECL|macro|OCF_READ_LOCAL_NAME
mdefine_line|#define OCF_READ_LOCAL_NAME&t;0x0014
r_typedef
r_struct
(brace
DECL|member|status
id|__u8
id|status
suffix:semicolon
DECL|member|name
id|__u8
id|name
(braket
l_int|248
)braket
suffix:semicolon
DECL|typedef|read_local_name_rp
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|read_local_name_rp
suffix:semicolon
DECL|macro|READ_LOCAL_NAME_RP_SIZE
mdefine_line|#define READ_LOCAL_NAME_RP_SIZE 249 
DECL|macro|OCF_READ_CLASS_OF_DEV
mdefine_line|#define OCF_READ_CLASS_OF_DEV&t;0x0023
r_typedef
r_struct
(brace
DECL|member|status
id|__u8
id|status
suffix:semicolon
DECL|member|dev_class
id|__u8
id|dev_class
(braket
l_int|3
)braket
suffix:semicolon
DECL|typedef|read_class_of_dev_rp
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|read_class_of_dev_rp
suffix:semicolon
DECL|macro|READ_CLASS_OF_DEV_RP_SIZE
mdefine_line|#define READ_CLASS_OF_DEV_RP_SIZE 4 
DECL|macro|OCF_WRITE_CLASS_OF_DEV
mdefine_line|#define OCF_WRITE_CLASS_OF_DEV&t;0x0024
r_typedef
r_struct
(brace
DECL|member|dev_class
id|__u8
id|dev_class
(braket
l_int|3
)braket
suffix:semicolon
DECL|typedef|write_class_of_dev_cp
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|write_class_of_dev_cp
suffix:semicolon
DECL|macro|WRITE_CLASS_OF_DEV_CP_SIZE
mdefine_line|#define WRITE_CLASS_OF_DEV_CP_SIZE 3
DECL|macro|OCF_HOST_BUFFER_SIZE
mdefine_line|#define OCF_HOST_BUFFER_SIZE&t;0x0033
r_typedef
r_struct
(brace
DECL|member|acl_mtu
id|__u16
id|acl_mtu
suffix:semicolon
DECL|member|sco_mtu
id|__u8
id|sco_mtu
suffix:semicolon
DECL|member|acl_max_pkt
id|__u16
id|acl_max_pkt
suffix:semicolon
DECL|member|sco_max_pkt
id|__u16
id|sco_max_pkt
suffix:semicolon
DECL|typedef|host_buffer_size_cp
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|host_buffer_size_cp
suffix:semicolon
DECL|macro|HOST_BUFFER_SIZE_CP_SIZE
mdefine_line|#define HOST_BUFFER_SIZE_CP_SIZE 7
multiline_comment|/* Link Control */
DECL|macro|OGF_LINK_CTL
mdefine_line|#define OGF_LINK_CTL&t;0x01 
DECL|macro|OCF_CREATE_CONN
mdefine_line|#define OCF_CREATE_CONN&t;&t;0x0005
r_typedef
r_struct
(brace
DECL|member|bdaddr
id|bdaddr_t
id|bdaddr
suffix:semicolon
DECL|member|pkt_type
id|__u16
id|pkt_type
suffix:semicolon
DECL|member|pscan_rep_mode
id|__u8
id|pscan_rep_mode
suffix:semicolon
DECL|member|pscan_mode
id|__u8
id|pscan_mode
suffix:semicolon
DECL|member|clock_offset
id|__u16
id|clock_offset
suffix:semicolon
DECL|member|role_switch
id|__u8
id|role_switch
suffix:semicolon
DECL|typedef|create_conn_cp
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|create_conn_cp
suffix:semicolon
DECL|macro|CREATE_CONN_CP_SIZE
mdefine_line|#define CREATE_CONN_CP_SIZE 13
DECL|macro|OCF_ACCEPT_CONN_REQ
mdefine_line|#define OCF_ACCEPT_CONN_REQ&t;0x0009
r_typedef
r_struct
(brace
DECL|member|bdaddr
id|bdaddr_t
id|bdaddr
suffix:semicolon
DECL|member|role
id|__u8
id|role
suffix:semicolon
DECL|typedef|accept_conn_req_cp
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|accept_conn_req_cp
suffix:semicolon
DECL|macro|ACCEPT_CONN_REQ_CP_SIZE
mdefine_line|#define ACCEPT_CONN_REQ_CP_SIZE&t;7
DECL|macro|OCF_REJECT_CONN_REQ
mdefine_line|#define OCF_REJECT_CONN_REQ&t;0x000a
r_typedef
r_struct
(brace
DECL|member|bdaddr
id|bdaddr_t
id|bdaddr
suffix:semicolon
DECL|member|reason
id|__u8
id|reason
suffix:semicolon
DECL|typedef|reject_conn_req_cp
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|reject_conn_req_cp
suffix:semicolon
DECL|macro|REJECT_CONN_REQ_CP_SIZE
mdefine_line|#define REJECT_CONN_REQ_CP_SIZE&t;7
DECL|macro|OCF_DISCONNECT
mdefine_line|#define OCF_DISCONNECT&t;0x0006
r_typedef
r_struct
(brace
DECL|member|handle
id|__u16
id|handle
suffix:semicolon
DECL|member|reason
id|__u8
id|reason
suffix:semicolon
DECL|typedef|disconnect_cp
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|disconnect_cp
suffix:semicolon
DECL|macro|DISCONNECT_CP_SIZE
mdefine_line|#define DISCONNECT_CP_SIZE 3
DECL|macro|OCF_ADD_SCO
mdefine_line|#define OCF_ADD_SCO&t;0x0007
r_typedef
r_struct
(brace
DECL|member|handle
id|__u16
id|handle
suffix:semicolon
DECL|member|pkt_type
id|__u16
id|pkt_type
suffix:semicolon
DECL|typedef|add_sco_cp
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|add_sco_cp
suffix:semicolon
DECL|macro|ADD_SCO_CP_SIZE
mdefine_line|#define ADD_SCO_CP_SIZE 4
DECL|macro|OCF_INQUIRY
mdefine_line|#define OCF_INQUIRY&t;&t;0x0001
r_typedef
r_struct
(brace
DECL|member|lap
id|__u8
id|lap
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|length
id|__u8
id|length
suffix:semicolon
DECL|member|num_rsp
id|__u8
id|num_rsp
suffix:semicolon
DECL|typedef|inquiry_cp
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|inquiry_cp
suffix:semicolon
DECL|macro|INQUIRY_CP_SIZE
mdefine_line|#define INQUIRY_CP_SIZE 5
r_typedef
r_struct
(brace
DECL|member|status
id|__u8
id|status
suffix:semicolon
DECL|member|bdaddr
id|bdaddr_t
id|bdaddr
suffix:semicolon
DECL|typedef|status_bdaddr_rp
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|status_bdaddr_rp
suffix:semicolon
DECL|macro|STATUS_BDADDR_RP_SIZE
mdefine_line|#define STATUS_BDADDR_RP_SIZE 7
DECL|macro|OCF_LINK_KEY_REPLY
mdefine_line|#define OCF_LINK_KEY_REPLY&t;0x000B
DECL|macro|OCF_LINK_KEY_NEG_REPLY
mdefine_line|#define OCF_LINK_KEY_NEG_REPLY&t;0x000C
r_typedef
r_struct
(brace
DECL|member|bdaddr
id|bdaddr_t
id|bdaddr
suffix:semicolon
DECL|member|link_key
id|__u8
id|link_key
(braket
l_int|16
)braket
suffix:semicolon
DECL|typedef|link_key_reply_cp
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|link_key_reply_cp
suffix:semicolon
DECL|macro|LINK_KEY_REPLY_CP_SIZE
mdefine_line|#define LINK_KEY_REPLY_CP_SIZE 22
DECL|macro|OCF_PIN_CODE_REPLY
mdefine_line|#define OCF_PIN_CODE_REPLY&t;0x000D
DECL|macro|OCF_PIN_CODE_NEG_REPLY
mdefine_line|#define OCF_PIN_CODE_NEG_REPLY&t;0x000E
r_typedef
r_struct
(brace
DECL|member|bdaddr
id|bdaddr_t
id|bdaddr
suffix:semicolon
DECL|member|pin_len
id|__u8
id|pin_len
suffix:semicolon
DECL|member|pin_code
id|__u8
id|pin_code
(braket
l_int|16
)braket
suffix:semicolon
DECL|typedef|pin_code_reply_cp
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|pin_code_reply_cp
suffix:semicolon
DECL|macro|PIN_CODE_REPLY_CP_SIZE
mdefine_line|#define PIN_CODE_REPLY_CP_SIZE 23
DECL|macro|OCF_CHANGE_CONN_PTYPE
mdefine_line|#define OCF_CHANGE_CONN_PTYPE&t;0x000F
r_typedef
r_struct
(brace
DECL|member|handle
id|__u16
id|handle
suffix:semicolon
DECL|member|pkt_type
id|__u16
id|pkt_type
suffix:semicolon
DECL|typedef|change_conn_ptype_cp
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|change_conn_ptype_cp
suffix:semicolon
DECL|macro|CHANGE_CONN_PTYPE_CP_SIZE
mdefine_line|#define CHANGE_CONN_PTYPE_CP_SIZE 4
DECL|macro|OCF_AUTH_REQUESTED
mdefine_line|#define OCF_AUTH_REQUESTED&t;0x0011
r_typedef
r_struct
(brace
DECL|member|handle
id|__u16
id|handle
suffix:semicolon
DECL|typedef|auth_requested_cp
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|auth_requested_cp
suffix:semicolon
DECL|macro|AUTH_REQUESTED_CP_SIZE
mdefine_line|#define AUTH_REQUESTED_CP_SIZE 2
DECL|macro|OCF_SET_CONN_ENCRYPT
mdefine_line|#define OCF_SET_CONN_ENCRYPT&t;0x0013
r_typedef
r_struct
(brace
DECL|member|handle
id|__u16
id|handle
suffix:semicolon
DECL|member|encrypt
id|__u8
id|encrypt
suffix:semicolon
DECL|typedef|set_conn_encrypt_cp
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|set_conn_encrypt_cp
suffix:semicolon
DECL|macro|SET_CONN_ENCRYPT_CP_SIZE
mdefine_line|#define SET_CONN_ENCRYPT_CP_SIZE 3
DECL|macro|OCF_REMOTE_NAME_REQ
mdefine_line|#define OCF_REMOTE_NAME_REQ&t;0x0019
r_typedef
r_struct
(brace
DECL|member|bdaddr
id|bdaddr_t
id|bdaddr
suffix:semicolon
DECL|member|pscan_rep_mode
id|__u8
id|pscan_rep_mode
suffix:semicolon
DECL|member|pscan_mode
id|__u8
id|pscan_mode
suffix:semicolon
DECL|member|clock_offset
id|__u16
id|clock_offset
suffix:semicolon
DECL|typedef|remote_name_req_cp
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|remote_name_req_cp
suffix:semicolon
DECL|macro|REMOTE_NAME_REQ_CP_SIZE
mdefine_line|#define REMOTE_NAME_REQ_CP_SIZE 10
DECL|macro|OCF_READ_REMOTE_FEATURES
mdefine_line|#define OCF_READ_REMOTE_FEATURES 0x001B
r_typedef
r_struct
(brace
DECL|member|handle
id|__u16
id|handle
suffix:semicolon
DECL|typedef|read_remote_features_cp
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|read_remote_features_cp
suffix:semicolon
DECL|macro|READ_REMOTE_FEATURES_CP_SIZE
mdefine_line|#define READ_REMOTE_FEATURES_CP_SIZE 2
DECL|macro|OCF_READ_REMOTE_VERSION
mdefine_line|#define OCF_READ_REMOTE_VERSION 0x001D
r_typedef
r_struct
(brace
DECL|member|handle
id|__u16
id|handle
suffix:semicolon
DECL|typedef|read_remote_version_cp
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|read_remote_version_cp
suffix:semicolon
DECL|macro|READ_REMOTE_VERSION_CP_SIZE
mdefine_line|#define READ_REMOTE_VERSION_CP_SIZE 2
multiline_comment|/* Link Policy */
DECL|macro|OGF_LINK_POLICY
mdefine_line|#define OGF_LINK_POLICY&t; 0x02   
DECL|macro|OCF_ROLE_DISCOVERY
mdefine_line|#define OCF_ROLE_DISCOVERY&t;0x0009
r_typedef
r_struct
(brace
DECL|member|handle
id|__u16
id|handle
suffix:semicolon
DECL|typedef|role_discovery_cp
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|role_discovery_cp
suffix:semicolon
DECL|macro|ROLE_DISCOVERY_CP_SIZE
mdefine_line|#define ROLE_DISCOVERY_CP_SIZE 2
r_typedef
r_struct
(brace
DECL|member|status
id|__u8
id|status
suffix:semicolon
DECL|member|handle
id|__u16
id|handle
suffix:semicolon
DECL|member|role
id|__u8
id|role
suffix:semicolon
DECL|typedef|role_discovery_rp
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|role_discovery_rp
suffix:semicolon
DECL|macro|ROLE_DISCOVERY_RP_SIZE
mdefine_line|#define ROLE_DISCOVERY_RP_SIZE 4
DECL|macro|OCF_READ_LINK_POLICY
mdefine_line|#define OCF_READ_LINK_POLICY&t;0x000C
r_typedef
r_struct
(brace
DECL|member|handle
id|__u16
id|handle
suffix:semicolon
DECL|typedef|read_link_policy_cp
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|read_link_policy_cp
suffix:semicolon
DECL|macro|READ_LINK_POLICY_CP_SIZE
mdefine_line|#define READ_LINK_POLICY_CP_SIZE 2
r_typedef
r_struct
(brace
DECL|member|status
id|__u8
id|status
suffix:semicolon
DECL|member|handle
id|__u16
id|handle
suffix:semicolon
DECL|member|policy
id|__u16
id|policy
suffix:semicolon
DECL|typedef|read_link_policy_rp
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|read_link_policy_rp
suffix:semicolon
DECL|macro|READ_LINK_POLICY_RP_SIZE
mdefine_line|#define READ_LINK_POLICY_RP_SIZE 5
DECL|macro|OCF_SWITCH_ROLE
mdefine_line|#define OCF_SWITCH_ROLE&t;0x000B
r_typedef
r_struct
(brace
DECL|member|bdaddr
id|bdaddr_t
id|bdaddr
suffix:semicolon
DECL|member|role
id|__u8
id|role
suffix:semicolon
DECL|typedef|switch_role_cp
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|switch_role_cp
suffix:semicolon
DECL|macro|SWITCH_ROLE_CP_SIZE
mdefine_line|#define SWITCH_ROLE_CP_SIZE 7
DECL|macro|OCF_WRITE_LINK_POLICY
mdefine_line|#define OCF_WRITE_LINK_POLICY&t;0x000D
r_typedef
r_struct
(brace
DECL|member|handle
id|__u16
id|handle
suffix:semicolon
DECL|member|policy
id|__u16
id|policy
suffix:semicolon
DECL|typedef|write_link_policy_cp
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|write_link_policy_cp
suffix:semicolon
DECL|macro|WRITE_LINK_POLICY_CP_SIZE
mdefine_line|#define WRITE_LINK_POLICY_CP_SIZE 4
r_typedef
r_struct
(brace
DECL|member|status
id|__u8
id|status
suffix:semicolon
DECL|member|handle
id|__u16
id|handle
suffix:semicolon
DECL|typedef|write_link_policy_rp
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|write_link_policy_rp
suffix:semicolon
DECL|macro|WRITE_LINK_POLICY_RP_SIZE
mdefine_line|#define WRITE_LINK_POLICY_RP_SIZE 3
multiline_comment|/* Status params */
DECL|macro|OGF_STATUS_PARAM
mdefine_line|#define OGF_STATUS_PARAM &t;0x05
multiline_comment|/* ---- HCI Events ---- */
DECL|macro|EVT_INQUIRY_COMPLETE
mdefine_line|#define EVT_INQUIRY_COMPLETE &t;0x01
DECL|macro|EVT_INQUIRY_RESULT
mdefine_line|#define EVT_INQUIRY_RESULT &t;0x02
r_typedef
r_struct
(brace
DECL|member|bdaddr
id|bdaddr_t
id|bdaddr
suffix:semicolon
DECL|member|pscan_rep_mode
id|__u8
id|pscan_rep_mode
suffix:semicolon
DECL|member|pscan_period_mode
id|__u8
id|pscan_period_mode
suffix:semicolon
DECL|member|pscan_mode
id|__u8
id|pscan_mode
suffix:semicolon
DECL|member|dev_class
id|__u8
id|dev_class
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|clock_offset
id|__u16
id|clock_offset
suffix:semicolon
DECL|typedef|inquiry_info
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|inquiry_info
suffix:semicolon
DECL|macro|INQUIRY_INFO_SIZE
mdefine_line|#define INQUIRY_INFO_SIZE 14
DECL|macro|EVT_CONN_COMPLETE
mdefine_line|#define EVT_CONN_COMPLETE &t;0x03
r_typedef
r_struct
(brace
DECL|member|status
id|__u8
id|status
suffix:semicolon
DECL|member|handle
id|__u16
id|handle
suffix:semicolon
DECL|member|bdaddr
id|bdaddr_t
id|bdaddr
suffix:semicolon
DECL|member|link_type
id|__u8
id|link_type
suffix:semicolon
DECL|member|encr_mode
id|__u8
id|encr_mode
suffix:semicolon
DECL|typedef|evt_conn_complete
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|evt_conn_complete
suffix:semicolon
DECL|macro|EVT_CONN_COMPLETE_SIZE
mdefine_line|#define EVT_CONN_COMPLETE_SIZE 13
DECL|macro|EVT_CONN_REQUEST
mdefine_line|#define EVT_CONN_REQUEST&t;0x04
r_typedef
r_struct
(brace
DECL|member|bdaddr
id|bdaddr_t
id|bdaddr
suffix:semicolon
DECL|member|dev_class
id|__u8
id|dev_class
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|link_type
id|__u8
id|link_type
suffix:semicolon
DECL|typedef|evt_conn_request
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|evt_conn_request
suffix:semicolon
DECL|macro|EVT_CONN_REQUEST_SIZE
mdefine_line|#define EVT_CONN_REQUEST_SIZE 10
DECL|macro|EVT_DISCONN_COMPLETE
mdefine_line|#define EVT_DISCONN_COMPLETE&t;0x05
r_typedef
r_struct
(brace
DECL|member|status
id|__u8
id|status
suffix:semicolon
DECL|member|handle
id|__u16
id|handle
suffix:semicolon
DECL|member|reason
id|__u8
id|reason
suffix:semicolon
DECL|typedef|evt_disconn_complete
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|evt_disconn_complete
suffix:semicolon
DECL|macro|EVT_DISCONN_COMPLETE_SIZE
mdefine_line|#define EVT_DISCONN_COMPLETE_SIZE 4
DECL|macro|EVT_AUTH_COMPLETE
mdefine_line|#define EVT_AUTH_COMPLETE&t;0x06
r_typedef
r_struct
(brace
DECL|member|status
id|__u8
id|status
suffix:semicolon
DECL|member|handle
id|__u16
id|handle
suffix:semicolon
DECL|typedef|evt_auth_complete
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|evt_auth_complete
suffix:semicolon
DECL|macro|EVT_AUTH_COMPLETE_SIZE
mdefine_line|#define EVT_AUTH_COMPLETE_SIZE 3
DECL|macro|EVT_REMOTE_NAME_REQ_COMPLETE
mdefine_line|#define EVT_REMOTE_NAME_REQ_COMPLETE&t;0x07
r_typedef
r_struct
(brace
DECL|member|status
id|__u8
id|status
suffix:semicolon
DECL|member|bdaddr
id|bdaddr_t
id|bdaddr
suffix:semicolon
DECL|member|name
id|__u8
id|name
(braket
l_int|248
)braket
suffix:semicolon
DECL|typedef|evt_remote_name_req_complete
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|evt_remote_name_req_complete
suffix:semicolon
DECL|macro|EVT_REMOTE_NAME_REQ_COMPLETE_SIZE
mdefine_line|#define EVT_REMOTE_NAME_REQ_COMPLETE_SIZE 255
DECL|macro|EVT_ENCRYPT_CHANGE
mdefine_line|#define EVT_ENCRYPT_CHANGE&t;0x08
r_typedef
r_struct
(brace
DECL|member|status
id|__u8
id|status
suffix:semicolon
DECL|member|handle
id|__u16
id|handle
suffix:semicolon
DECL|member|encrypt
id|__u8
id|encrypt
suffix:semicolon
DECL|typedef|evt_encrypt_change
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|evt_encrypt_change
suffix:semicolon
DECL|macro|EVT_ENCRYPT_CHANGE_SIZE
mdefine_line|#define EVT_ENCRYPT_CHANGE_SIZE 5
DECL|macro|EVT_QOS_SETUP_COMPLETE
mdefine_line|#define EVT_QOS_SETUP_COMPLETE 0x0D
r_typedef
r_struct
(brace
DECL|member|service_type
id|__u8
id|service_type
suffix:semicolon
DECL|member|token_rate
id|__u32
id|token_rate
suffix:semicolon
DECL|member|peak_bandwidth
id|__u32
id|peak_bandwidth
suffix:semicolon
DECL|member|latency
id|__u32
id|latency
suffix:semicolon
DECL|member|delay_variation
id|__u32
id|delay_variation
suffix:semicolon
DECL|typedef|hci_qos
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|hci_qos
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|status
id|__u8
id|status
suffix:semicolon
DECL|member|handle
id|__u16
id|handle
suffix:semicolon
DECL|member|qos
id|hci_qos
id|qos
suffix:semicolon
DECL|typedef|evt_qos_setup_complete
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|evt_qos_setup_complete
suffix:semicolon
DECL|macro|EVT_QOS_SETUP_COMPLETE_SIZE
mdefine_line|#define EVT_QOS_SETUP_COMPLETE_SIZE 20
DECL|macro|EVT_CMD_COMPLETE
mdefine_line|#define EVT_CMD_COMPLETE &t;0x0e
r_typedef
r_struct
(brace
DECL|member|ncmd
id|__u8
id|ncmd
suffix:semicolon
DECL|member|opcode
id|__u16
id|opcode
suffix:semicolon
DECL|typedef|evt_cmd_complete
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|evt_cmd_complete
suffix:semicolon
DECL|macro|EVT_CMD_COMPLETE_SIZE
mdefine_line|#define EVT_CMD_COMPLETE_SIZE 3
DECL|macro|EVT_CMD_STATUS
mdefine_line|#define EVT_CMD_STATUS &t;&t;0x0f
r_typedef
r_struct
(brace
DECL|member|status
id|__u8
id|status
suffix:semicolon
DECL|member|ncmd
id|__u8
id|ncmd
suffix:semicolon
DECL|member|opcode
id|__u16
id|opcode
suffix:semicolon
DECL|typedef|evt_cmd_status
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|evt_cmd_status
suffix:semicolon
DECL|macro|EVT_CMD_STATUS_SIZE
mdefine_line|#define EVT_CMD_STATUS_SIZE 4
DECL|macro|EVT_NUM_COMP_PKTS
mdefine_line|#define EVT_NUM_COMP_PKTS&t;0x13
r_typedef
r_struct
(brace
DECL|member|num_hndl
id|__u8
id|num_hndl
suffix:semicolon
multiline_comment|/* variable length part */
DECL|typedef|evt_num_comp_pkts
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|evt_num_comp_pkts
suffix:semicolon
DECL|macro|EVT_NUM_COMP_PKTS_SIZE
mdefine_line|#define EVT_NUM_COMP_PKTS_SIZE 1
DECL|macro|EVT_ROLE_CHANGE
mdefine_line|#define EVT_ROLE_CHANGE&t;&t;0x12
r_typedef
r_struct
(brace
DECL|member|status
id|__u8
id|status
suffix:semicolon
DECL|member|bdaddr
id|bdaddr_t
id|bdaddr
suffix:semicolon
DECL|member|role
id|__u8
id|role
suffix:semicolon
DECL|typedef|evt_role_change
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|evt_role_change
suffix:semicolon
DECL|macro|EVT_ROLE_CHANGE_SIZE
mdefine_line|#define EVT_ROLE_CHANGE_SIZE 1
DECL|macro|EVT_PIN_CODE_REQ
mdefine_line|#define EVT_PIN_CODE_REQ        0x16
r_typedef
r_struct
(brace
DECL|member|bdaddr
id|bdaddr_t
id|bdaddr
suffix:semicolon
DECL|typedef|evt_pin_code_req
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|evt_pin_code_req
suffix:semicolon
DECL|macro|EVT_PIN_CODE_REQ_SIZE
mdefine_line|#define EVT_PIN_CODE_REQ_SIZE 6
DECL|macro|EVT_LINK_KEY_REQ
mdefine_line|#define EVT_LINK_KEY_REQ        0x17
r_typedef
r_struct
(brace
DECL|member|bdaddr
id|bdaddr_t
id|bdaddr
suffix:semicolon
DECL|typedef|evt_link_key_req
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|evt_link_key_req
suffix:semicolon
DECL|macro|EVT_LINK_KEY_REQ_SIZE
mdefine_line|#define EVT_LINK_KEY_REQ_SIZE 6
DECL|macro|EVT_LINK_KEY_NOTIFY
mdefine_line|#define EVT_LINK_KEY_NOTIFY&t;0x18
r_typedef
r_struct
(brace
DECL|member|bdaddr
id|bdaddr_t
id|bdaddr
suffix:semicolon
DECL|member|link_key
id|__u8
id|link_key
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|key_type
id|__u8
id|key_type
suffix:semicolon
DECL|typedef|evt_link_key_notify
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|evt_link_key_notify
suffix:semicolon
DECL|macro|EVT_LINK_KEY_NOTIFY_SIZE
mdefine_line|#define EVT_LINK_KEY_NOTIFY_SIZE 23
DECL|macro|EVT_READ_REMOTE_FEATURES_COMPLETE
mdefine_line|#define EVT_READ_REMOTE_FEATURES_COMPLETE 0x0B
r_typedef
r_struct
(brace
DECL|member|status
id|__u8
id|status
suffix:semicolon
DECL|member|handle
id|__u16
id|handle
suffix:semicolon
DECL|member|features
id|__u8
id|features
(braket
l_int|8
)braket
suffix:semicolon
DECL|typedef|evt_read_remote_features_complete
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|evt_read_remote_features_complete
suffix:semicolon
DECL|macro|EVT_READ_REMOTE_FEATURES_COMPLETE_SIZE
mdefine_line|#define EVT_READ_REMOTE_FEATURES_COMPLETE_SIZE 11
DECL|macro|EVT_READ_REMOTE_VERSION_COMPLETE
mdefine_line|#define EVT_READ_REMOTE_VERSION_COMPLETE 0x0C
r_typedef
r_struct
(brace
DECL|member|status
id|__u8
id|status
suffix:semicolon
DECL|member|handle
id|__u16
id|handle
suffix:semicolon
DECL|member|lmp_ver
id|__u8
id|lmp_ver
suffix:semicolon
DECL|member|manufacturer
id|__u16
id|manufacturer
suffix:semicolon
DECL|member|lmp_subver
id|__u16
id|lmp_subver
suffix:semicolon
DECL|typedef|evt_read_remote_version_complete
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|evt_read_remote_version_complete
suffix:semicolon
DECL|macro|EVT_READ_REMOTE_VERSION_COMPLETE_SIZE
mdefine_line|#define EVT_READ_REMOTE_VERSION_COMPLETE_SIZE 8
multiline_comment|/* Internal events generated by BlueZ stack */
DECL|macro|EVT_STACK_INTERNAL
mdefine_line|#define EVT_STACK_INTERNAL&t;0xfd
r_typedef
r_struct
(brace
DECL|member|type
id|__u16
id|type
suffix:semicolon
DECL|member|data
id|__u8
id|data
(braket
l_int|0
)braket
suffix:semicolon
DECL|typedef|evt_stack_internal
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|evt_stack_internal
suffix:semicolon
DECL|macro|EVT_STACK_INTERNAL_SIZE
mdefine_line|#define EVT_STACK_INTERNAL_SIZE 2
DECL|macro|EVT_SI_DEVICE
mdefine_line|#define EVT_SI_DEVICE  &t;0x01
r_typedef
r_struct
(brace
DECL|member|event
id|__u16
id|event
suffix:semicolon
DECL|member|dev_id
id|__u16
id|dev_id
suffix:semicolon
DECL|typedef|evt_si_device
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|evt_si_device
suffix:semicolon
DECL|macro|EVT_SI_DEVICE_SIZE
mdefine_line|#define EVT_SI_DEVICE_SIZE 4
DECL|macro|EVT_SI_SECURITY
mdefine_line|#define EVT_SI_SECURITY&t;0x02
r_typedef
r_struct
(brace
DECL|member|event
id|__u16
id|event
suffix:semicolon
DECL|member|proto
id|__u16
id|proto
suffix:semicolon
DECL|member|subproto
id|__u16
id|subproto
suffix:semicolon
DECL|member|incomming
id|__u8
id|incomming
suffix:semicolon
DECL|typedef|evt_si_security
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|evt_si_security
suffix:semicolon
multiline_comment|/* --------  HCI Packet structures  -------- */
DECL|macro|HCI_TYPE_LEN
mdefine_line|#define HCI_TYPE_LEN&t;1
r_typedef
r_struct
(brace
DECL|member|opcode
id|__u16
id|opcode
suffix:semicolon
multiline_comment|/* OCF &amp; OGF */
DECL|member|plen
id|__u8
id|plen
suffix:semicolon
DECL|typedef|hci_command_hdr
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|hci_command_hdr
suffix:semicolon
DECL|macro|HCI_COMMAND_HDR_SIZE
mdefine_line|#define HCI_COMMAND_HDR_SIZE &t;3
r_typedef
r_struct
(brace
DECL|member|evt
id|__u8
id|evt
suffix:semicolon
DECL|member|plen
id|__u8
id|plen
suffix:semicolon
DECL|typedef|hci_event_hdr
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|hci_event_hdr
suffix:semicolon
DECL|macro|HCI_EVENT_HDR_SIZE
mdefine_line|#define HCI_EVENT_HDR_SIZE &t;2
r_typedef
r_struct
(brace
DECL|member|handle
id|__u16
id|handle
suffix:semicolon
multiline_comment|/* Handle &amp; Flags(PB, BC) */
DECL|member|dlen
id|__u16
id|dlen
suffix:semicolon
DECL|typedef|hci_acl_hdr
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|hci_acl_hdr
suffix:semicolon
DECL|macro|HCI_ACL_HDR_SIZE
mdefine_line|#define HCI_ACL_HDR_SIZE &t;4
r_typedef
r_struct
(brace
DECL|member|handle
id|__u16
id|handle
suffix:semicolon
DECL|member|dlen
id|__u8
id|dlen
suffix:semicolon
DECL|typedef|hci_sco_hdr
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|hci_sco_hdr
suffix:semicolon
DECL|macro|HCI_SCO_HDR_SIZE
mdefine_line|#define HCI_SCO_HDR_SIZE &t;3
multiline_comment|/* Command opcode pack/unpack */
DECL|macro|cmd_opcode_pack
mdefine_line|#define cmd_opcode_pack(ogf, ocf)&t;(__u16)((ocf &amp; 0x03ff)|(ogf &lt;&lt; 10))
DECL|macro|cmd_opcode_ogf
mdefine_line|#define cmd_opcode_ogf(op)&t;&t;(op &gt;&gt; 10)
DECL|macro|cmd_opcode_ocf
mdefine_line|#define cmd_opcode_ocf(op)&t;&t;(op &amp; 0x03ff)
multiline_comment|/* ACL handle and flags pack/unpack */
DECL|macro|acl_handle_pack
mdefine_line|#define acl_handle_pack(h, f)&t;(__u16)((h &amp; 0x0fff)|(f &lt;&lt; 12))
DECL|macro|acl_handle
mdefine_line|#define acl_handle(h)&t;&t;(h &amp; 0x0fff)
DECL|macro|acl_flags
mdefine_line|#define acl_flags(h)&t;&t;(h &gt;&gt; 12)
multiline_comment|/* HCI Socket options */
DECL|macro|HCI_DATA_DIR
mdefine_line|#define HCI_DATA_DIR&t;1
DECL|macro|HCI_FILTER
mdefine_line|#define HCI_FILTER&t;2
DECL|macro|HCI_TIME_STAMP
mdefine_line|#define HCI_TIME_STAMP&t;3
multiline_comment|/* HCI CMSG flags */
DECL|macro|HCI_CMSG_DIR
mdefine_line|#define HCI_CMSG_DIR&t;0x0001
DECL|macro|HCI_CMSG_TSTAMP
mdefine_line|#define HCI_CMSG_TSTAMP&t;0x0002
DECL|struct|sockaddr_hci
r_struct
id|sockaddr_hci
(brace
DECL|member|hci_family
id|sa_family_t
id|hci_family
suffix:semicolon
DECL|member|hci_dev
r_int
r_int
id|hci_dev
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|HCI_DEV_NONE
mdefine_line|#define HCI_DEV_NONE&t;0xffff
DECL|struct|hci_filter
r_struct
id|hci_filter
(brace
DECL|member|type_mask
id|__u32
id|type_mask
suffix:semicolon
DECL|member|event_mask
id|__u32
id|event_mask
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|opcode
id|__u16
id|opcode
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|HCI_FLT_TYPE_BITS
mdefine_line|#define HCI_FLT_TYPE_BITS&t;31
DECL|macro|HCI_FLT_EVENT_BITS
mdefine_line|#define HCI_FLT_EVENT_BITS&t;63
DECL|macro|HCI_FLT_OGF_BITS
mdefine_line|#define HCI_FLT_OGF_BITS&t;63
DECL|macro|HCI_FLT_OCF_BITS
mdefine_line|#define HCI_FLT_OCF_BITS&t;127
macro_line|#if BITS_PER_LONG == 64
DECL|function|hci_set_bit
r_static
r_inline
r_void
id|hci_set_bit
c_func
(paren
r_int
id|nr
comma
r_void
op_star
id|addr
)paren
(brace
op_star
(paren
(paren
id|__u32
op_star
)paren
id|addr
op_plus
(paren
id|nr
op_rshift
l_int|5
)paren
)paren
op_or_assign
(paren
(paren
id|__u32
)paren
l_int|1
op_lshift
(paren
id|nr
op_amp
l_int|31
)paren
)paren
suffix:semicolon
)brace
DECL|function|hci_test_bit
r_static
r_inline
r_int
id|hci_test_bit
c_func
(paren
r_int
id|nr
comma
r_void
op_star
id|addr
)paren
(brace
r_return
op_star
(paren
(paren
id|__u32
op_star
)paren
id|addr
op_plus
(paren
id|nr
op_rshift
l_int|5
)paren
)paren
op_amp
(paren
(paren
id|__u32
)paren
l_int|1
op_lshift
(paren
id|nr
op_amp
l_int|31
)paren
)paren
suffix:semicolon
)brace
macro_line|#else
DECL|macro|hci_set_bit
mdefine_line|#define hci_set_bit&t;set_bit
DECL|macro|hci_test_bit
mdefine_line|#define hci_test_bit&t;test_bit
macro_line|#endif
multiline_comment|/* Ioctl requests structures */
DECL|struct|hci_dev_stats
r_struct
id|hci_dev_stats
(brace
DECL|member|err_rx
id|__u32
id|err_rx
suffix:semicolon
DECL|member|err_tx
id|__u32
id|err_tx
suffix:semicolon
DECL|member|cmd_tx
id|__u32
id|cmd_tx
suffix:semicolon
DECL|member|evt_rx
id|__u32
id|evt_rx
suffix:semicolon
DECL|member|acl_tx
id|__u32
id|acl_tx
suffix:semicolon
DECL|member|acl_rx
id|__u32
id|acl_rx
suffix:semicolon
DECL|member|sco_tx
id|__u32
id|sco_tx
suffix:semicolon
DECL|member|sco_rx
id|__u32
id|sco_rx
suffix:semicolon
DECL|member|byte_rx
id|__u32
id|byte_rx
suffix:semicolon
DECL|member|byte_tx
id|__u32
id|byte_tx
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|hci_dev_info
r_struct
id|hci_dev_info
(brace
DECL|member|dev_id
id|__u16
id|dev_id
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|bdaddr
id|bdaddr_t
id|bdaddr
suffix:semicolon
DECL|member|flags
id|__u32
id|flags
suffix:semicolon
DECL|member|type
id|__u8
id|type
suffix:semicolon
DECL|member|features
id|__u8
id|features
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|pkt_type
id|__u32
id|pkt_type
suffix:semicolon
DECL|member|link_policy
id|__u32
id|link_policy
suffix:semicolon
DECL|member|link_mode
id|__u32
id|link_mode
suffix:semicolon
DECL|member|acl_mtu
id|__u16
id|acl_mtu
suffix:semicolon
DECL|member|acl_pkts
id|__u16
id|acl_pkts
suffix:semicolon
DECL|member|sco_mtu
id|__u16
id|sco_mtu
suffix:semicolon
DECL|member|sco_pkts
id|__u16
id|sco_pkts
suffix:semicolon
DECL|member|stat
r_struct
id|hci_dev_stats
id|stat
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|hci_conn_info
r_struct
id|hci_conn_info
(brace
DECL|member|handle
id|__u16
id|handle
suffix:semicolon
DECL|member|bdaddr
id|bdaddr_t
id|bdaddr
suffix:semicolon
DECL|member|type
id|__u8
id|type
suffix:semicolon
DECL|member|out
id|__u8
id|out
suffix:semicolon
DECL|member|state
id|__u16
id|state
suffix:semicolon
DECL|member|link_mode
id|__u32
id|link_mode
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|hci_dev_req
r_struct
id|hci_dev_req
(brace
DECL|member|dev_id
id|__u16
id|dev_id
suffix:semicolon
DECL|member|dev_opt
id|__u32
id|dev_opt
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|hci_dev_list_req
r_struct
id|hci_dev_list_req
(brace
DECL|member|dev_num
id|__u16
id|dev_num
suffix:semicolon
DECL|member|dev_req
r_struct
id|hci_dev_req
id|dev_req
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* hci_dev_req structures */
)brace
suffix:semicolon
DECL|struct|hci_conn_list_req
r_struct
id|hci_conn_list_req
(brace
DECL|member|dev_id
id|__u16
id|dev_id
suffix:semicolon
DECL|member|conn_num
id|__u16
id|conn_num
suffix:semicolon
DECL|member|conn_info
r_struct
id|hci_conn_info
id|conn_info
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|hci_conn_info_req
r_struct
id|hci_conn_info_req
(brace
DECL|member|bdaddr
id|bdaddr_t
id|bdaddr
suffix:semicolon
DECL|member|type
id|__u8
id|type
suffix:semicolon
DECL|member|conn_info
r_struct
id|hci_conn_info
id|conn_info
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|hci_inquiry_req
r_struct
id|hci_inquiry_req
(brace
DECL|member|dev_id
id|__u16
id|dev_id
suffix:semicolon
DECL|member|flags
id|__u16
id|flags
suffix:semicolon
DECL|member|lap
id|__u8
id|lap
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|length
id|__u8
id|length
suffix:semicolon
DECL|member|num_rsp
id|__u8
id|num_rsp
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|IREQ_CACHE_FLUSH
mdefine_line|#define IREQ_CACHE_FLUSH 0x0001
DECL|struct|hci_remotename_req
r_struct
id|hci_remotename_req
(brace
DECL|member|dev_id
id|__u16
id|dev_id
suffix:semicolon
DECL|member|flags
id|__u16
id|flags
suffix:semicolon
DECL|member|bdaddr
id|bdaddr_t
id|bdaddr
suffix:semicolon
DECL|member|name
id|__u8
id|name
(braket
l_int|248
)braket
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* __HCI_H */
eof
