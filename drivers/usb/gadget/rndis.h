multiline_comment|/* &n; * RNDIS&t;Definitions for Remote NDIS&n; * &n; * Version:&t;$Id: rndis.h,v 1.15 2004/03/25 21:33:46 robert Exp $&n; * &n; * Authors:&t;Benedikt Spranger, Pengutronix&n; * &t;&t;Robert Schwebel, Pengutronix&n; * &n; * &t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;version 2, as published by the Free Software Foundation. &n; * &n; *&t;&t;This software was originally developed in conformance with&n; *&t;&t;Microsoft&squot;s Remote NDIS Specification License Agreement.&n; */
macro_line|#ifndef _LINUX_RNDIS_H
DECL|macro|_LINUX_RNDIS_H
mdefine_line|#define _LINUX_RNDIS_H
macro_line|#include &quot;ndis.h&quot;
DECL|macro|RNDIS_MAXIMUM_FRAME_SIZE
mdefine_line|#define RNDIS_MAXIMUM_FRAME_SIZE&t;1518
DECL|macro|RNDIS_MAX_TOTAL_SIZE
mdefine_line|#define RNDIS_MAX_TOTAL_SIZE&t;&t;1558
multiline_comment|/* Remote NDIS Versions */
DECL|macro|RNDIS_MAJOR_VERSION
mdefine_line|#define RNDIS_MAJOR_VERSION&t;&t;1
DECL|macro|RNDIS_MINOR_VERSION
mdefine_line|#define RNDIS_MINOR_VERSION&t;&t;0
multiline_comment|/* Status Values */
DECL|macro|RNDIS_STATUS_SUCCESS
mdefine_line|#define RNDIS_STATUS_SUCCESS&t;&t;0x00000000U&t;/* Success           */
DECL|macro|RNDIS_STATUS_FAILURE
mdefine_line|#define RNDIS_STATUS_FAILURE&t;&t;0xC0000001U&t;/* Unspecified error */
DECL|macro|RNDIS_STATUS_INVALID_DATA
mdefine_line|#define RNDIS_STATUS_INVALID_DATA&t;0xC0010015U&t;/* Invalid data      */
DECL|macro|RNDIS_STATUS_NOT_SUPPORTED
mdefine_line|#define RNDIS_STATUS_NOT_SUPPORTED&t;0xC00000BBU&t;/* Unsupported request */
DECL|macro|RNDIS_STATUS_MEDIA_CONNECT
mdefine_line|#define RNDIS_STATUS_MEDIA_CONNECT&t;0x4001000BU&t;/* Device connected  */
DECL|macro|RNDIS_STATUS_MEDIA_DISCONNECT
mdefine_line|#define RNDIS_STATUS_MEDIA_DISCONNECT&t;0x4001000CU&t;/* Device disconnected */
multiline_comment|/* For all not specified status messages:&n; * RNDIS_STATUS_Xxx -&gt; NDIS_STATUS_Xxx &n; */
multiline_comment|/* Message Set for Connectionless (802.3) Devices */
DECL|macro|REMOTE_NDIS_INIZIALIZE_MSG
mdefine_line|#define REMOTE_NDIS_INIZIALIZE_MSG&t;0x00000002U&t;/* Initialize device */
DECL|macro|REMOTE_NDIS_HALT_MSG
mdefine_line|#define REMOTE_NDIS_HALT_MSG&t;&t;0x00000003U
DECL|macro|REMOTE_NDIS_QUERY_MSG
mdefine_line|#define REMOTE_NDIS_QUERY_MSG&t;&t;0x00000004U
DECL|macro|REMOTE_NDIS_SET_MSG
mdefine_line|#define REMOTE_NDIS_SET_MSG&t;&t;0x00000005U
DECL|macro|REMOTE_NDIS_RESET_MSG
mdefine_line|#define REMOTE_NDIS_RESET_MSG&t;&t;0x00000006U
DECL|macro|REMOTE_NDIS_INDICATE_STATUS_MSG
mdefine_line|#define REMOTE_NDIS_INDICATE_STATUS_MSG&t;0x00000007U
DECL|macro|REMOTE_NDIS_KEEPALIVE_MSG
mdefine_line|#define REMOTE_NDIS_KEEPALIVE_MSG&t;0x00000008U
multiline_comment|/* Message completion */
DECL|macro|REMOTE_NDIS_INITIALIZE_CMPLT
mdefine_line|#define REMOTE_NDIS_INITIALIZE_CMPLT&t;0x80000002U
DECL|macro|REMOTE_NDIS_QUERY_CMPLT
mdefine_line|#define REMOTE_NDIS_QUERY_CMPLT&t;&t;0x80000004U
DECL|macro|REMOTE_NDIS_SET_CMPLT
mdefine_line|#define REMOTE_NDIS_SET_CMPLT&t;&t;0x80000005U
DECL|macro|REMOTE_NDIS_RESET_CMPLT
mdefine_line|#define REMOTE_NDIS_RESET_CMPLT&t;&t;0x80000006U
DECL|macro|REMOTE_NDIS_KEEPALIVE_CMPLT
mdefine_line|#define REMOTE_NDIS_KEEPALIVE_CMPLT&t;0x80000008U
multiline_comment|/* Device Flags */
DECL|macro|RNDIS_DF_CONNECTIONLESS
mdefine_line|#define RNDIS_DF_CONNECTIONLESS&t;&t;0x00000001U
DECL|macro|RNDIS_DF_CONNECTION_ORIENTED
mdefine_line|#define RNDIS_DF_CONNECTION_ORIENTED&t;0x00000002U
DECL|macro|RNDIS_MEDIUM_802_3
mdefine_line|#define RNDIS_MEDIUM_802_3&t;&t;0x00000000U
multiline_comment|/* supported OIDs */
DECL|variable|oid_supported_list
r_static
r_const
id|u32
id|oid_supported_list
(braket
)braket
op_assign
(brace
multiline_comment|/* mandatory general */
multiline_comment|/* the general stuff */
id|OID_GEN_SUPPORTED_LIST
comma
id|OID_GEN_HARDWARE_STATUS
comma
id|OID_GEN_MEDIA_SUPPORTED
comma
id|OID_GEN_MEDIA_IN_USE
comma
id|OID_GEN_MAXIMUM_FRAME_SIZE
comma
id|OID_GEN_LINK_SPEED
comma
id|OID_GEN_TRANSMIT_BUFFER_SPACE
comma
id|OID_GEN_TRANSMIT_BLOCK_SIZE
comma
id|OID_GEN_RECEIVE_BLOCK_SIZE
comma
id|OID_GEN_VENDOR_ID
comma
id|OID_GEN_VENDOR_DESCRIPTION
comma
id|OID_GEN_VENDOR_DRIVER_VERSION
comma
id|OID_GEN_CURRENT_PACKET_FILTER
comma
id|OID_GEN_MAXIMUM_TOTAL_SIZE
comma
id|OID_GEN_MAC_OPTIONS
comma
id|OID_GEN_MEDIA_CONNECT_STATUS
comma
id|OID_GEN_PHYSICAL_MEDIUM
comma
id|OID_GEN_RNDIS_CONFIG_PARAMETER
comma
multiline_comment|/* the statistical stuff */
id|OID_GEN_XMIT_OK
comma
id|OID_GEN_RCV_OK
comma
id|OID_GEN_XMIT_ERROR
comma
id|OID_GEN_RCV_ERROR
comma
id|OID_GEN_RCV_NO_BUFFER
comma
id|OID_GEN_DIRECTED_BYTES_XMIT
comma
id|OID_GEN_DIRECTED_FRAMES_XMIT
comma
id|OID_GEN_MULTICAST_BYTES_XMIT
comma
id|OID_GEN_MULTICAST_FRAMES_XMIT
comma
id|OID_GEN_BROADCAST_BYTES_XMIT
comma
id|OID_GEN_BROADCAST_FRAMES_XMIT
comma
id|OID_GEN_DIRECTED_BYTES_RCV
comma
id|OID_GEN_DIRECTED_FRAMES_RCV
comma
id|OID_GEN_MULTICAST_BYTES_RCV
comma
id|OID_GEN_MULTICAST_FRAMES_RCV
comma
id|OID_GEN_BROADCAST_BYTES_RCV
comma
id|OID_GEN_BROADCAST_FRAMES_RCV
comma
id|OID_GEN_RCV_CRC_ERROR
comma
id|OID_GEN_TRANSMIT_QUEUE_LENGTH
comma
multiline_comment|/* mandatory 802.3 */
multiline_comment|/* the general stuff */
id|OID_802_3_PERMANENT_ADDRESS
comma
id|OID_802_3_CURRENT_ADDRESS
comma
id|OID_802_3_MULTICAST_LIST
comma
id|OID_802_3_MAC_OPTIONS
comma
id|OID_802_3_MAXIMUM_LIST_SIZE
comma
multiline_comment|/* the statistical stuff */
id|OID_802_3_RCV_ERROR_ALIGNMENT
comma
id|OID_802_3_XMIT_ONE_COLLISION
comma
id|OID_802_3_XMIT_MORE_COLLISIONS
)brace
suffix:semicolon
DECL|struct|rndis_init_msg_type
r_typedef
r_struct
id|rndis_init_msg_type
(brace
DECL|member|MessageType
id|u32
id|MessageType
suffix:semicolon
DECL|member|MessageLength
id|u32
id|MessageLength
suffix:semicolon
DECL|member|RequestID
id|u32
id|RequestID
suffix:semicolon
DECL|member|MajorVersion
id|u32
id|MajorVersion
suffix:semicolon
DECL|member|MinorVersion
id|u32
id|MinorVersion
suffix:semicolon
DECL|member|MaxTransferSize
id|u32
id|MaxTransferSize
suffix:semicolon
DECL|typedef|rndis_init_msg_type
)brace
id|rndis_init_msg_type
suffix:semicolon
DECL|struct|rndis_init_cmplt_type
r_typedef
r_struct
id|rndis_init_cmplt_type
(brace
DECL|member|MessageType
id|u32
id|MessageType
suffix:semicolon
DECL|member|MessageLength
id|u32
id|MessageLength
suffix:semicolon
DECL|member|RequestID
id|u32
id|RequestID
suffix:semicolon
DECL|member|Status
id|u32
id|Status
suffix:semicolon
DECL|member|MajorVersion
id|u32
id|MajorVersion
suffix:semicolon
DECL|member|MinorVersion
id|u32
id|MinorVersion
suffix:semicolon
DECL|member|DeviceFlags
id|u32
id|DeviceFlags
suffix:semicolon
DECL|member|Medium
id|u32
id|Medium
suffix:semicolon
DECL|member|MaxPacketsPerTransfer
id|u32
id|MaxPacketsPerTransfer
suffix:semicolon
DECL|member|MaxTransferSize
id|u32
id|MaxTransferSize
suffix:semicolon
DECL|member|PacketAlignmentFactor
id|u32
id|PacketAlignmentFactor
suffix:semicolon
DECL|member|AFListOffset
id|u32
id|AFListOffset
suffix:semicolon
DECL|member|AFListSize
id|u32
id|AFListSize
suffix:semicolon
DECL|typedef|rndis_init_cmplt_type
)brace
id|rndis_init_cmplt_type
suffix:semicolon
DECL|struct|rndis_halt_msg_type
r_typedef
r_struct
id|rndis_halt_msg_type
(brace
DECL|member|MessageType
id|u32
id|MessageType
suffix:semicolon
DECL|member|MessageLength
id|u32
id|MessageLength
suffix:semicolon
DECL|member|RequestID
id|u32
id|RequestID
suffix:semicolon
DECL|typedef|rndis_halt_msg_type
)brace
id|rndis_halt_msg_type
suffix:semicolon
DECL|struct|rndis_query_msg_type
r_typedef
r_struct
id|rndis_query_msg_type
(brace
DECL|member|MessageType
id|u32
id|MessageType
suffix:semicolon
DECL|member|MessageLength
id|u32
id|MessageLength
suffix:semicolon
DECL|member|RequestID
id|u32
id|RequestID
suffix:semicolon
DECL|member|OID
id|u32
id|OID
suffix:semicolon
DECL|member|InformationBufferLength
id|u32
id|InformationBufferLength
suffix:semicolon
DECL|member|InformationBufferOffset
id|u32
id|InformationBufferOffset
suffix:semicolon
DECL|member|DeviceVcHandle
id|u32
id|DeviceVcHandle
suffix:semicolon
DECL|typedef|rndis_query_msg_type
)brace
id|rndis_query_msg_type
suffix:semicolon
DECL|struct|rndis_query_cmplt_type
r_typedef
r_struct
id|rndis_query_cmplt_type
(brace
DECL|member|MessageType
id|u32
id|MessageType
suffix:semicolon
DECL|member|MessageLength
id|u32
id|MessageLength
suffix:semicolon
DECL|member|RequestID
id|u32
id|RequestID
suffix:semicolon
DECL|member|Status
id|u32
id|Status
suffix:semicolon
DECL|member|InformationBufferLength
id|u32
id|InformationBufferLength
suffix:semicolon
DECL|member|InformationBufferOffset
id|u32
id|InformationBufferOffset
suffix:semicolon
DECL|typedef|rndis_query_cmplt_type
)brace
id|rndis_query_cmplt_type
suffix:semicolon
DECL|struct|rndis_set_msg_type
r_typedef
r_struct
id|rndis_set_msg_type
(brace
DECL|member|MessageType
id|u32
id|MessageType
suffix:semicolon
DECL|member|MessageLength
id|u32
id|MessageLength
suffix:semicolon
DECL|member|RequestID
id|u32
id|RequestID
suffix:semicolon
DECL|member|OID
id|u32
id|OID
suffix:semicolon
DECL|member|InformationBufferLength
id|u32
id|InformationBufferLength
suffix:semicolon
DECL|member|InformationBufferOffset
id|u32
id|InformationBufferOffset
suffix:semicolon
DECL|member|DeviceVcHandle
id|u32
id|DeviceVcHandle
suffix:semicolon
DECL|typedef|rndis_set_msg_type
)brace
id|rndis_set_msg_type
suffix:semicolon
DECL|struct|rndis_set_cmplt_type
r_typedef
r_struct
id|rndis_set_cmplt_type
(brace
DECL|member|MessageType
id|u32
id|MessageType
suffix:semicolon
DECL|member|MessageLength
id|u32
id|MessageLength
suffix:semicolon
DECL|member|RequestID
id|u32
id|RequestID
suffix:semicolon
DECL|member|Status
id|u32
id|Status
suffix:semicolon
DECL|typedef|rndis_set_cmplt_type
)brace
id|rndis_set_cmplt_type
suffix:semicolon
DECL|struct|rndis_reset_msg_type
r_typedef
r_struct
id|rndis_reset_msg_type
(brace
DECL|member|MessageType
id|u32
id|MessageType
suffix:semicolon
DECL|member|MessageLength
id|u32
id|MessageLength
suffix:semicolon
DECL|member|Reserved
id|u32
id|Reserved
suffix:semicolon
DECL|typedef|rndis_reset_msg_type
)brace
id|rndis_reset_msg_type
suffix:semicolon
DECL|struct|rndis_reset_cmplt_type
r_typedef
r_struct
id|rndis_reset_cmplt_type
(brace
DECL|member|MessageType
id|u32
id|MessageType
suffix:semicolon
DECL|member|MessageLength
id|u32
id|MessageLength
suffix:semicolon
DECL|member|Status
id|u32
id|Status
suffix:semicolon
DECL|member|AddressingReset
id|u32
id|AddressingReset
suffix:semicolon
DECL|typedef|rndis_reset_cmplt_type
)brace
id|rndis_reset_cmplt_type
suffix:semicolon
DECL|struct|rndis_indicate_status_msg_type
r_typedef
r_struct
id|rndis_indicate_status_msg_type
(brace
DECL|member|MessageType
id|u32
id|MessageType
suffix:semicolon
DECL|member|MessageLength
id|u32
id|MessageLength
suffix:semicolon
DECL|member|Status
id|u32
id|Status
suffix:semicolon
DECL|member|StatusBufferLength
id|u32
id|StatusBufferLength
suffix:semicolon
DECL|member|StatusBufferOffset
id|u32
id|StatusBufferOffset
suffix:semicolon
DECL|typedef|rndis_indicate_status_msg_type
)brace
id|rndis_indicate_status_msg_type
suffix:semicolon
DECL|struct|rndis_keepalive_msg_type
r_typedef
r_struct
id|rndis_keepalive_msg_type
(brace
DECL|member|MessageType
id|u32
id|MessageType
suffix:semicolon
DECL|member|MessageLength
id|u32
id|MessageLength
suffix:semicolon
DECL|member|RequestID
id|u32
id|RequestID
suffix:semicolon
DECL|typedef|rndis_keepalive_msg_type
)brace
id|rndis_keepalive_msg_type
suffix:semicolon
DECL|struct|rndis_keepalive_cmplt_type
r_typedef
r_struct
id|rndis_keepalive_cmplt_type
(brace
DECL|member|MessageType
id|u32
id|MessageType
suffix:semicolon
DECL|member|MessageLength
id|u32
id|MessageLength
suffix:semicolon
DECL|member|RequestID
id|u32
id|RequestID
suffix:semicolon
DECL|member|Status
id|u32
id|Status
suffix:semicolon
DECL|typedef|rndis_keepalive_cmplt_type
)brace
id|rndis_keepalive_cmplt_type
suffix:semicolon
DECL|struct|rndis_packet_msg_type
r_struct
id|rndis_packet_msg_type
(brace
DECL|member|MessageType
id|u32
id|MessageType
suffix:semicolon
DECL|member|MessageLength
id|u32
id|MessageLength
suffix:semicolon
DECL|member|DataOffset
id|u32
id|DataOffset
suffix:semicolon
DECL|member|DataLength
id|u32
id|DataLength
suffix:semicolon
DECL|member|OOBDataOffset
id|u32
id|OOBDataOffset
suffix:semicolon
DECL|member|OOBDataLength
id|u32
id|OOBDataLength
suffix:semicolon
DECL|member|NumOOBDataElements
id|u32
id|NumOOBDataElements
suffix:semicolon
DECL|member|PerPacketInfoOffset
id|u32
id|PerPacketInfoOffset
suffix:semicolon
DECL|member|PerPacketInfoLength
id|u32
id|PerPacketInfoLength
suffix:semicolon
DECL|member|VcHandle
id|u32
id|VcHandle
suffix:semicolon
DECL|member|Reserved
id|u32
id|Reserved
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|rndis_config_parameter
r_struct
id|rndis_config_parameter
(brace
DECL|member|ParameterNameOffset
id|u32
id|ParameterNameOffset
suffix:semicolon
DECL|member|ParameterNameLength
id|u32
id|ParameterNameLength
suffix:semicolon
DECL|member|ParameterType
id|u32
id|ParameterType
suffix:semicolon
DECL|member|ParameterValueOffset
id|u32
id|ParameterValueOffset
suffix:semicolon
DECL|member|ParameterValueLength
id|u32
id|ParameterValueLength
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* implementation specific */
DECL|enum|rndis_state
r_enum
id|rndis_state
(brace
DECL|enumerator|RNDIS_UNINITIALIZED
id|RNDIS_UNINITIALIZED
comma
DECL|enumerator|RNDIS_INITIALIZED
id|RNDIS_INITIALIZED
comma
DECL|enumerator|RNDIS_DATA_INITIALIZED
id|RNDIS_DATA_INITIALIZED
comma
)brace
suffix:semicolon
DECL|struct|rndis_resp_t
r_typedef
r_struct
id|rndis_resp_t
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|buf
id|u8
op_star
id|buf
suffix:semicolon
DECL|member|length
id|u32
id|length
suffix:semicolon
DECL|member|send
r_int
id|send
suffix:semicolon
DECL|typedef|rndis_resp_t
)brace
id|rndis_resp_t
suffix:semicolon
DECL|struct|rndis_params
r_typedef
r_struct
id|rndis_params
(brace
DECL|member|confignr
id|u8
id|confignr
suffix:semicolon
DECL|member|used
r_int
id|used
suffix:semicolon
DECL|member|state
r_enum
id|rndis_state
id|state
suffix:semicolon
DECL|member|medium
id|u32
id|medium
suffix:semicolon
DECL|member|speed
id|u32
id|speed
suffix:semicolon
DECL|member|media_state
id|u32
id|media_state
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
op_star
id|stats
suffix:semicolon
DECL|member|vendorID
id|u32
id|vendorID
suffix:semicolon
DECL|member|vendorDescr
r_const
r_char
op_star
id|vendorDescr
suffix:semicolon
DECL|member|ack
r_int
(paren
op_star
id|ack
)paren
(paren
r_struct
id|net_device
op_star
)paren
suffix:semicolon
DECL|member|resp_queue
r_struct
id|list_head
id|resp_queue
suffix:semicolon
DECL|typedef|rndis_params
)brace
id|rndis_params
suffix:semicolon
multiline_comment|/* RNDIS Message parser and other useless functions */
r_int
id|rndis_msg_parser
(paren
id|u8
id|configNr
comma
id|u8
op_star
id|buf
)paren
suffix:semicolon
r_int
id|rndis_register
(paren
r_int
(paren
op_star
id|rndis_control_ack
)paren
(paren
r_struct
id|net_device
op_star
)paren
)paren
suffix:semicolon
r_void
id|rndis_deregister
(paren
r_int
id|configNr
)paren
suffix:semicolon
r_int
id|rndis_set_param_dev
(paren
id|u8
id|configNr
comma
r_struct
id|net_device
op_star
id|dev
comma
r_struct
id|net_device_stats
op_star
id|stats
)paren
suffix:semicolon
r_int
id|rndis_set_param_vendor
(paren
id|u8
id|configNr
comma
id|u32
id|vendorID
comma
r_const
r_char
op_star
id|vendorDescr
)paren
suffix:semicolon
r_int
id|rndis_set_param_medium
(paren
id|u8
id|configNr
comma
id|u32
id|medium
comma
id|u32
id|speed
)paren
suffix:semicolon
r_void
id|rndis_add_hdr
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_int
id|rndis_rm_hdr
(paren
id|u8
op_star
id|buf
comma
id|u32
op_star
id|length
)paren
suffix:semicolon
id|u8
op_star
id|rndis_get_next_response
(paren
r_int
id|configNr
comma
id|u32
op_star
id|length
)paren
suffix:semicolon
r_void
id|rndis_free_response
(paren
r_int
id|configNr
comma
id|u8
op_star
id|buf
)paren
suffix:semicolon
r_int
id|rndis_signal_connect
(paren
r_int
id|configNr
)paren
suffix:semicolon
r_int
id|rndis_signal_disconnect
(paren
r_int
id|configNr
)paren
suffix:semicolon
r_int
id|rndis_state
(paren
r_int
id|configNr
)paren
suffix:semicolon
r_int
id|__init
id|rndis_init
(paren
r_void
)paren
suffix:semicolon
r_void
id|__exit
id|rndis_exit
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif  /* _LINUX_RNDIS_H */
eof
