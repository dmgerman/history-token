multiline_comment|/* &n;   BlueZ - Bluetooth protocol stack for Linux&n;   Copyright (C) 2000-2001 Qualcomm Incorporated&n;&n;   Written 2000,2001 by Maxim Krasnyansky &lt;maxk@qualcomm.com&gt;&n;&n;   This program is free software; you can redistribute it and/or modify&n;   it under the terms of the GNU General Public License version 2 as&n;   published by the Free Software Foundation;&n;&n;   THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS&n;   OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n;   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT OF THIRD PARTY RIGHTS.&n;   IN NO EVENT SHALL THE COPYRIGHT HOLDER(S) AND AUTHOR(S) BE LIABLE FOR ANY&n;   CLAIM, OR ANY SPECIAL INDIRECT OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES &n;   WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN &n;   ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF &n;   OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.&n;&n;   ALL LIABILITY, INCLUDING LIABILITY FOR INFRINGEMENT OF ANY PATENTS, &n;   COPYRIGHTS, TRADEMARKS OR OTHER RIGHTS, RELATING TO USE OF THIS &n;   SOFTWARE IS DISCLAIMED.&n;*/
multiline_comment|/*&n; *  $Id: hci.h,v 1.15 2001/08/05 06:02:15 maxk Exp $&n; */
macro_line|#ifndef __HCI_H
DECL|macro|__HCI_H
mdefine_line|#define __HCI_H
macro_line|#include &lt;asm/byteorder.h&gt;
DECL|macro|HCI_MAX_DEV
mdefine_line|#define HCI_MAX_DEV &t;8
DECL|macro|HCI_MAX_FRAME_SIZE
mdefine_line|#define HCI_MAX_FRAME_SIZE&t;2048
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
DECL|macro|HCI_UART
mdefine_line|#define HCI_UART &t;0
DECL|macro|HCI_USB
mdefine_line|#define HCI_USB&t;&t;1
DECL|macro|HCI_VHCI
mdefine_line|#define HCI_VHCI&t;2
multiline_comment|/* HCI device modes */
DECL|macro|HCI_NORMAL
mdefine_line|#define HCI_NORMAL &t;0x0001
DECL|macro|HCI_RAW
mdefine_line|#define HCI_RAW&t;&t;0x0002
DECL|macro|HCI_MODE_MASK
mdefine_line|#define HCI_MODE_MASK   (HCI_NORMAL | HCI_RAW)
DECL|macro|HCI_SOCK
mdefine_line|#define HCI_SOCK&t;0x1000
multiline_comment|/* HCI device states */
DECL|macro|HCI_INIT
mdefine_line|#define HCI_INIT&t;0x0010
DECL|macro|HCI_UP
mdefine_line|#define HCI_UP &t;&t;0x0020
DECL|macro|HCI_RUNNING
mdefine_line|#define HCI_RUNNING&t;0x0040
multiline_comment|/* HCI device flags */
DECL|macro|HCI_PSCAN
mdefine_line|#define HCI_PSCAN&t;0x0100
DECL|macro|HCI_ISCAN
mdefine_line|#define HCI_ISCAN&t;0x0200
DECL|macro|HCI_AUTH
mdefine_line|#define HCI_AUTH&t;0x0400
multiline_comment|/* HCI Ioctl defines */
DECL|macro|HCIDEVUP
mdefine_line|#define HCIDEVUP        _IOW(&squot;H&squot;, 201, int)
DECL|macro|HCIDEVDOWN
mdefine_line|#define HCIDEVDOWN      _IOW(&squot;H&squot;, 202, int)
DECL|macro|HCIDEVRESET
mdefine_line|#define HCIDEVRESET     _IOW(&squot;H&squot;, 203, int)
DECL|macro|HCIRESETSTAT
mdefine_line|#define HCIRESETSTAT    _IOW(&squot;H&squot;, 204, int)
DECL|macro|HCIGETINFO
mdefine_line|#define HCIGETINFO      _IOR(&squot;H&squot;, 205, int)
DECL|macro|HCIGETDEVLIST
mdefine_line|#define HCIGETDEVLIST   _IOR(&squot;H&squot;, 206, int)
DECL|macro|HCISETRAW
mdefine_line|#define HCISETRAW       _IOW(&squot;H&squot;, 207, int)
DECL|macro|HCISETSCAN
mdefine_line|#define HCISETSCAN      _IOW(&squot;H&squot;, 208, int)
DECL|macro|HCISETAUTH
mdefine_line|#define HCISETAUTH      _IOW(&squot;H&squot;, 209, int)
DECL|macro|HCIINQUIRY
mdefine_line|#define HCIINQUIRY      _IOR(&squot;H&squot;, 210, int)
DECL|macro|HCISETPTYPE
mdefine_line|#define HCISETPTYPE     _IOW(&squot;H&squot;, 211, int)
DECL|macro|HCIGETCONNLIST
mdefine_line|#define HCIGETCONNLIST  _IOR(&squot;H&squot;, 212, int)
macro_line|#ifndef __NO_HCI_DEFS
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
DECL|member|man_name
id|__u16
id|man_name
suffix:semicolon
DECL|member|lmp_sub
id|__u16
id|lmp_sub
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
DECL|macro|OCF_WRITE_AUTH_ENABLE
mdefine_line|#define OCF_WRITE_AUTH_ENABLE&t;0x0020
DECL|macro|AUTH_DISABLED
mdefine_line|#define AUTH_DISABLED&t;&t;&t;0x00
DECL|macro|AUTH_ENABLED
mdefine_line|#define AUTH_ENABLED&t;&t;&t;0x01
DECL|macro|OCF_WRITE_CA_TIMEOUT
mdefine_line|#define OCF_WRITE_CA_TIMEOUT  &t;0x0016&t;
DECL|macro|OCF_WRITE_PG_TIMEOUT
mdefine_line|#define OCF_WRITE_PG_TIMEOUT  &t;0x0018
DECL|macro|OCF_WRITE_SCAN_ENABLE
mdefine_line|#define OCF_WRITE_SCAN_ENABLE &t;0x001A
DECL|macro|SCANS_DISABLED
mdefine_line|#define SCANS_DISABLED&t;&t;0x00
DECL|macro|IS_ENA_PS_DIS
mdefine_line|#define IS_ENA_PS_DIS&t;&t;0x01
DECL|macro|IS_DIS_PS_ENA
mdefine_line|#define IS_DIS_PS_ENA&t;&t;0x02
DECL|macro|IS_ENA_PS_ENA
mdefine_line|#define IS_ENA_PS_ENA&t;&t;0x03
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
multiline_comment|/* Link Control */
DECL|macro|OGF_LINK_CTL
mdefine_line|#define OGF_LINK_CTL&t;0x01 
DECL|macro|OCF_CREATE_CONN
mdefine_line|#define OCF_CREATE_CONN&t;0x0005
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
DECL|member|lenght
id|__u8
id|lenght
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
DECL|macro|OGF_LINK_POLICY
mdefine_line|#define OGF_LINK_POLICY&t; &t;0x02   /* Link Policy */
multiline_comment|/* --------- HCI Events --------- */
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
DECL|member|class
id|__u8
r_class
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
multiline_comment|/* variable lenght part */
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
DECL|macro|EVT_HCI_DEV_EVENT
mdefine_line|#define EVT_HCI_DEV_EVENT&t;0xfd
r_typedef
r_struct
(brace
DECL|member|event
id|__u16
id|event
suffix:semicolon
DECL|member|param
id|__u16
id|param
suffix:semicolon
DECL|typedef|evt_hci_dev_event
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|evt_hci_dev_event
suffix:semicolon
DECL|macro|EVT_HCI_DEV_EVENT_SIZE
mdefine_line|#define EVT_HCI_DEV_EVENT_SIZE 4
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
macro_line|#endif /* _NO_HCI_DEFS */
multiline_comment|/* HCI Socket options */
DECL|macro|HCI_DATA_DIR
mdefine_line|#define HCI_DATA_DIR&t;0x0001
DECL|macro|HCI_FILTER
mdefine_line|#define HCI_FILTER&t;0x0002
multiline_comment|/* HCI CMSG flags */
DECL|macro|HCI_CMSG_DIR
mdefine_line|#define HCI_CMSG_DIR&t;0x0001
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
DECL|member|acl_mtu
id|__u16
id|acl_mtu
suffix:semicolon
DECL|member|acl_max
id|__u16
id|acl_max
suffix:semicolon
DECL|member|sco_mtu
id|__u16
id|sco_mtu
suffix:semicolon
DECL|member|sco_max
id|__u16
id|sco_max
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
macro_line|#endif /* __HCI_H */
eof
