multiline_comment|/*&n; * ndis.h &n; * &n; * ntddndis.h modified by Benedikt Spranger &lt;b.spranger@pengutronix.de&gt;&n; * &n; * Thanks to the cygwin development team, &n; * espacially to Casper S. Hornstrup &lt;chorns@users.sourceforge.net&gt;&n; * &n; * THIS SOFTWARE IS NOT COPYRIGHTED&n; *&n; * This source code is offered for use in the public domain. You may&n; * use, modify or distribute it freely.&n; *&n; * This code is distributed in the hope that it will be useful but&n; * WITHOUT ANY WARRANTY. ALL WARRANTIES, EXPRESS OR IMPLIED ARE HEREBY&n; * DISCLAIMED. This includes but is not limited to warranties of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; */
macro_line|#ifndef _LINUX_NDIS_H
DECL|macro|_LINUX_NDIS_H
mdefine_line|#define _LINUX_NDIS_H
DECL|macro|NDIS_STATUS_MULTICAST_FULL
mdefine_line|#define NDIS_STATUS_MULTICAST_FULL&t;  0xC0010009
DECL|macro|NDIS_STATUS_MULTICAST_EXISTS
mdefine_line|#define NDIS_STATUS_MULTICAST_EXISTS      0xC001000A
DECL|macro|NDIS_STATUS_MULTICAST_NOT_FOUND
mdefine_line|#define NDIS_STATUS_MULTICAST_NOT_FOUND   0xC001000B
DECL|enum|NDIS_DEVICE_POWER_STATE
r_enum
id|NDIS_DEVICE_POWER_STATE
(brace
DECL|enumerator|NdisDeviceStateUnspecified
id|NdisDeviceStateUnspecified
op_assign
l_int|0
comma
DECL|enumerator|NdisDeviceStateD0
id|NdisDeviceStateD0
comma
DECL|enumerator|NdisDeviceStateD1
id|NdisDeviceStateD1
comma
DECL|enumerator|NdisDeviceStateD2
id|NdisDeviceStateD2
comma
DECL|enumerator|NdisDeviceStateD3
id|NdisDeviceStateD3
comma
DECL|enumerator|NdisDeviceStateMaximum
id|NdisDeviceStateMaximum
)brace
suffix:semicolon
DECL|struct|NDIS_PM_WAKE_UP_CAPABILITIES
r_struct
id|NDIS_PM_WAKE_UP_CAPABILITIES
(brace
DECL|member|MinMagicPacketWakeUp
r_enum
id|NDIS_DEVICE_POWER_STATE
id|MinMagicPacketWakeUp
suffix:semicolon
DECL|member|MinPatternWakeUp
r_enum
id|NDIS_DEVICE_POWER_STATE
id|MinPatternWakeUp
suffix:semicolon
DECL|member|MinLinkChangeWakeUp
r_enum
id|NDIS_DEVICE_POWER_STATE
id|MinLinkChangeWakeUp
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* NDIS_PNP_CAPABILITIES.Flags constants */
DECL|macro|NDIS_DEVICE_WAKE_UP_ENABLE
mdefine_line|#define NDIS_DEVICE_WAKE_UP_ENABLE                0x00000001
DECL|macro|NDIS_DEVICE_WAKE_ON_PATTERN_MATCH_ENABLE
mdefine_line|#define NDIS_DEVICE_WAKE_ON_PATTERN_MATCH_ENABLE  0x00000002
DECL|macro|NDIS_DEVICE_WAKE_ON_MAGIC_PACKET_ENABLE
mdefine_line|#define NDIS_DEVICE_WAKE_ON_MAGIC_PACKET_ENABLE   0x00000004
DECL|struct|NDIS_PNP_CAPABILITIES
r_struct
id|NDIS_PNP_CAPABILITIES
(brace
DECL|member|Flags
id|u32
id|Flags
suffix:semicolon
DECL|member|WakeUpCapabilities
r_struct
id|NDIS_PM_WAKE_UP_CAPABILITIES
id|WakeUpCapabilities
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|NDIS_PM_PACKET_PATTERN
r_struct
id|NDIS_PM_PACKET_PATTERN
(brace
DECL|member|Priority
id|u32
id|Priority
suffix:semicolon
DECL|member|Reserved
id|u32
id|Reserved
suffix:semicolon
DECL|member|MaskSize
id|u32
id|MaskSize
suffix:semicolon
DECL|member|PatternOffset
id|u32
id|PatternOffset
suffix:semicolon
DECL|member|PatternSize
id|u32
id|PatternSize
suffix:semicolon
DECL|member|PatternFlags
id|u32
id|PatternFlags
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Required Object IDs (OIDs) */
DECL|macro|OID_GEN_SUPPORTED_LIST
mdefine_line|#define OID_GEN_SUPPORTED_LIST            0x00010101
DECL|macro|OID_GEN_HARDWARE_STATUS
mdefine_line|#define OID_GEN_HARDWARE_STATUS           0x00010102
DECL|macro|OID_GEN_MEDIA_SUPPORTED
mdefine_line|#define OID_GEN_MEDIA_SUPPORTED           0x00010103
DECL|macro|OID_GEN_MEDIA_IN_USE
mdefine_line|#define OID_GEN_MEDIA_IN_USE              0x00010104
DECL|macro|OID_GEN_MAXIMUM_LOOKAHEAD
mdefine_line|#define OID_GEN_MAXIMUM_LOOKAHEAD         0x00010105
DECL|macro|OID_GEN_MAXIMUM_FRAME_SIZE
mdefine_line|#define OID_GEN_MAXIMUM_FRAME_SIZE        0x00010106
DECL|macro|OID_GEN_LINK_SPEED
mdefine_line|#define OID_GEN_LINK_SPEED                0x00010107
DECL|macro|OID_GEN_TRANSMIT_BUFFER_SPACE
mdefine_line|#define OID_GEN_TRANSMIT_BUFFER_SPACE     0x00010108
DECL|macro|OID_GEN_RECEIVE_BUFFER_SPACE
mdefine_line|#define OID_GEN_RECEIVE_BUFFER_SPACE      0x00010109
DECL|macro|OID_GEN_TRANSMIT_BLOCK_SIZE
mdefine_line|#define OID_GEN_TRANSMIT_BLOCK_SIZE       0x0001010A
DECL|macro|OID_GEN_RECEIVE_BLOCK_SIZE
mdefine_line|#define OID_GEN_RECEIVE_BLOCK_SIZE        0x0001010B
DECL|macro|OID_GEN_VENDOR_ID
mdefine_line|#define OID_GEN_VENDOR_ID                 0x0001010C
DECL|macro|OID_GEN_VENDOR_DESCRIPTION
mdefine_line|#define OID_GEN_VENDOR_DESCRIPTION        0x0001010D
DECL|macro|OID_GEN_CURRENT_PACKET_FILTER
mdefine_line|#define OID_GEN_CURRENT_PACKET_FILTER     0x0001010E
DECL|macro|OID_GEN_CURRENT_LOOKAHEAD
mdefine_line|#define OID_GEN_CURRENT_LOOKAHEAD         0x0001010F
DECL|macro|OID_GEN_DRIVER_VERSION
mdefine_line|#define OID_GEN_DRIVER_VERSION            0x00010110
DECL|macro|OID_GEN_MAXIMUM_TOTAL_SIZE
mdefine_line|#define OID_GEN_MAXIMUM_TOTAL_SIZE        0x00010111
DECL|macro|OID_GEN_PROTOCOL_OPTIONS
mdefine_line|#define OID_GEN_PROTOCOL_OPTIONS          0x00010112
DECL|macro|OID_GEN_MAC_OPTIONS
mdefine_line|#define OID_GEN_MAC_OPTIONS               0x00010113
DECL|macro|OID_GEN_MEDIA_CONNECT_STATUS
mdefine_line|#define OID_GEN_MEDIA_CONNECT_STATUS      0x00010114
DECL|macro|OID_GEN_MAXIMUM_SEND_PACKETS
mdefine_line|#define OID_GEN_MAXIMUM_SEND_PACKETS      0x00010115
DECL|macro|OID_GEN_VENDOR_DRIVER_VERSION
mdefine_line|#define OID_GEN_VENDOR_DRIVER_VERSION     0x00010116
DECL|macro|OID_GEN_SUPPORTED_GUIDS
mdefine_line|#define OID_GEN_SUPPORTED_GUIDS           0x00010117
DECL|macro|OID_GEN_NETWORK_LAYER_ADDRESSES
mdefine_line|#define OID_GEN_NETWORK_LAYER_ADDRESSES   0x00010118
DECL|macro|OID_GEN_TRANSPORT_HEADER_OFFSET
mdefine_line|#define OID_GEN_TRANSPORT_HEADER_OFFSET   0x00010119
DECL|macro|OID_GEN_MACHINE_NAME
mdefine_line|#define OID_GEN_MACHINE_NAME              0x0001021A
DECL|macro|OID_GEN_RNDIS_CONFIG_PARAMETER
mdefine_line|#define OID_GEN_RNDIS_CONFIG_PARAMETER    0x0001021B
DECL|macro|OID_GEN_VLAN_ID
mdefine_line|#define OID_GEN_VLAN_ID                   0x0001021C
multiline_comment|/* Optional OIDs */
DECL|macro|OID_GEN_MEDIA_CAPABILITIES
mdefine_line|#define OID_GEN_MEDIA_CAPABILITIES        0x00010201
DECL|macro|OID_GEN_PHYSICAL_MEDIUM
mdefine_line|#define OID_GEN_PHYSICAL_MEDIUM           0x00010202
multiline_comment|/* Required statistics OIDs */
DECL|macro|OID_GEN_XMIT_OK
mdefine_line|#define OID_GEN_XMIT_OK                   0x00020101
DECL|macro|OID_GEN_RCV_OK
mdefine_line|#define OID_GEN_RCV_OK                    0x00020102
DECL|macro|OID_GEN_XMIT_ERROR
mdefine_line|#define OID_GEN_XMIT_ERROR                0x00020103
DECL|macro|OID_GEN_RCV_ERROR
mdefine_line|#define OID_GEN_RCV_ERROR                 0x00020104
DECL|macro|OID_GEN_RCV_NO_BUFFER
mdefine_line|#define OID_GEN_RCV_NO_BUFFER             0x00020105
multiline_comment|/* Optional statistics OIDs */
DECL|macro|OID_GEN_DIRECTED_BYTES_XMIT
mdefine_line|#define OID_GEN_DIRECTED_BYTES_XMIT       0x00020201
DECL|macro|OID_GEN_DIRECTED_FRAMES_XMIT
mdefine_line|#define OID_GEN_DIRECTED_FRAMES_XMIT      0x00020202
DECL|macro|OID_GEN_MULTICAST_BYTES_XMIT
mdefine_line|#define OID_GEN_MULTICAST_BYTES_XMIT      0x00020203
DECL|macro|OID_GEN_MULTICAST_FRAMES_XMIT
mdefine_line|#define OID_GEN_MULTICAST_FRAMES_XMIT     0x00020204
DECL|macro|OID_GEN_BROADCAST_BYTES_XMIT
mdefine_line|#define OID_GEN_BROADCAST_BYTES_XMIT      0x00020205
DECL|macro|OID_GEN_BROADCAST_FRAMES_XMIT
mdefine_line|#define OID_GEN_BROADCAST_FRAMES_XMIT     0x00020206
DECL|macro|OID_GEN_DIRECTED_BYTES_RCV
mdefine_line|#define OID_GEN_DIRECTED_BYTES_RCV        0x00020207
DECL|macro|OID_GEN_DIRECTED_FRAMES_RCV
mdefine_line|#define OID_GEN_DIRECTED_FRAMES_RCV       0x00020208
DECL|macro|OID_GEN_MULTICAST_BYTES_RCV
mdefine_line|#define OID_GEN_MULTICAST_BYTES_RCV       0x00020209
DECL|macro|OID_GEN_MULTICAST_FRAMES_RCV
mdefine_line|#define OID_GEN_MULTICAST_FRAMES_RCV      0x0002020A
DECL|macro|OID_GEN_BROADCAST_BYTES_RCV
mdefine_line|#define OID_GEN_BROADCAST_BYTES_RCV       0x0002020B
DECL|macro|OID_GEN_BROADCAST_FRAMES_RCV
mdefine_line|#define OID_GEN_BROADCAST_FRAMES_RCV      0x0002020C
DECL|macro|OID_GEN_RCV_CRC_ERROR
mdefine_line|#define OID_GEN_RCV_CRC_ERROR             0x0002020D
DECL|macro|OID_GEN_TRANSMIT_QUEUE_LENGTH
mdefine_line|#define OID_GEN_TRANSMIT_QUEUE_LENGTH     0x0002020E
DECL|macro|OID_GEN_GET_TIME_CAPS
mdefine_line|#define OID_GEN_GET_TIME_CAPS             0x0002020F
DECL|macro|OID_GEN_GET_NETCARD_TIME
mdefine_line|#define OID_GEN_GET_NETCARD_TIME          0x00020210
DECL|macro|OID_GEN_NETCARD_LOAD
mdefine_line|#define OID_GEN_NETCARD_LOAD              0x00020211
DECL|macro|OID_GEN_DEVICE_PROFILE
mdefine_line|#define OID_GEN_DEVICE_PROFILE            0x00020212
DECL|macro|OID_GEN_INIT_TIME_MS
mdefine_line|#define OID_GEN_INIT_TIME_MS              0x00020213
DECL|macro|OID_GEN_RESET_COUNTS
mdefine_line|#define OID_GEN_RESET_COUNTS              0x00020214
DECL|macro|OID_GEN_MEDIA_SENSE_COUNTS
mdefine_line|#define OID_GEN_MEDIA_SENSE_COUNTS        0x00020215
DECL|macro|OID_GEN_FRIENDLY_NAME
mdefine_line|#define OID_GEN_FRIENDLY_NAME             0x00020216
DECL|macro|OID_GEN_MINIPORT_INFO
mdefine_line|#define OID_GEN_MINIPORT_INFO             0x00020217
DECL|macro|OID_GEN_RESET_VERIFY_PARAMETERS
mdefine_line|#define OID_GEN_RESET_VERIFY_PARAMETERS   0x00020218
multiline_comment|/* IEEE 802.3 (Ethernet) OIDs */
DECL|macro|NDIS_802_3_MAC_OPTION_PRIORITY
mdefine_line|#define NDIS_802_3_MAC_OPTION_PRIORITY    0x00000001
DECL|macro|OID_802_3_PERMANENT_ADDRESS
mdefine_line|#define OID_802_3_PERMANENT_ADDRESS       0x01010101
DECL|macro|OID_802_3_CURRENT_ADDRESS
mdefine_line|#define OID_802_3_CURRENT_ADDRESS         0x01010102
DECL|macro|OID_802_3_MULTICAST_LIST
mdefine_line|#define OID_802_3_MULTICAST_LIST          0x01010103
DECL|macro|OID_802_3_MAXIMUM_LIST_SIZE
mdefine_line|#define OID_802_3_MAXIMUM_LIST_SIZE       0x01010104
DECL|macro|OID_802_3_MAC_OPTIONS
mdefine_line|#define OID_802_3_MAC_OPTIONS             0x01010105
DECL|macro|OID_802_3_RCV_ERROR_ALIGNMENT
mdefine_line|#define OID_802_3_RCV_ERROR_ALIGNMENT     0x01020101
DECL|macro|OID_802_3_XMIT_ONE_COLLISION
mdefine_line|#define OID_802_3_XMIT_ONE_COLLISION      0x01020102
DECL|macro|OID_802_3_XMIT_MORE_COLLISIONS
mdefine_line|#define OID_802_3_XMIT_MORE_COLLISIONS    0x01020103
DECL|macro|OID_802_3_XMIT_DEFERRED
mdefine_line|#define OID_802_3_XMIT_DEFERRED           0x01020201
DECL|macro|OID_802_3_XMIT_MAX_COLLISIONS
mdefine_line|#define OID_802_3_XMIT_MAX_COLLISIONS     0x01020202
DECL|macro|OID_802_3_RCV_OVERRUN
mdefine_line|#define OID_802_3_RCV_OVERRUN             0x01020203
DECL|macro|OID_802_3_XMIT_UNDERRUN
mdefine_line|#define OID_802_3_XMIT_UNDERRUN           0x01020204
DECL|macro|OID_802_3_XMIT_HEARTBEAT_FAILURE
mdefine_line|#define OID_802_3_XMIT_HEARTBEAT_FAILURE  0x01020205
DECL|macro|OID_802_3_XMIT_TIMES_CRS_LOST
mdefine_line|#define OID_802_3_XMIT_TIMES_CRS_LOST     0x01020206
DECL|macro|OID_802_3_XMIT_LATE_COLLISIONS
mdefine_line|#define OID_802_3_XMIT_LATE_COLLISIONS    0x01020207
multiline_comment|/* OID_GEN_MINIPORT_INFO constants */
DECL|macro|NDIS_MINIPORT_BUS_MASTER
mdefine_line|#define NDIS_MINIPORT_BUS_MASTER                      0x00000001
DECL|macro|NDIS_MINIPORT_WDM_DRIVER
mdefine_line|#define NDIS_MINIPORT_WDM_DRIVER                      0x00000002
DECL|macro|NDIS_MINIPORT_SG_LIST
mdefine_line|#define NDIS_MINIPORT_SG_LIST                         0x00000004
DECL|macro|NDIS_MINIPORT_SUPPORTS_MEDIA_QUERY
mdefine_line|#define NDIS_MINIPORT_SUPPORTS_MEDIA_QUERY            0x00000008
DECL|macro|NDIS_MINIPORT_INDICATES_PACKETS
mdefine_line|#define NDIS_MINIPORT_INDICATES_PACKETS               0x00000010
DECL|macro|NDIS_MINIPORT_IGNORE_PACKET_QUEUE
mdefine_line|#define NDIS_MINIPORT_IGNORE_PACKET_QUEUE             0x00000020
DECL|macro|NDIS_MINIPORT_IGNORE_REQUEST_QUEUE
mdefine_line|#define NDIS_MINIPORT_IGNORE_REQUEST_QUEUE            0x00000040
DECL|macro|NDIS_MINIPORT_IGNORE_TOKEN_RING_ERRORS
mdefine_line|#define NDIS_MINIPORT_IGNORE_TOKEN_RING_ERRORS        0x00000080
DECL|macro|NDIS_MINIPORT_INTERMEDIATE_DRIVER
mdefine_line|#define NDIS_MINIPORT_INTERMEDIATE_DRIVER             0x00000100
DECL|macro|NDIS_MINIPORT_IS_NDIS_5
mdefine_line|#define NDIS_MINIPORT_IS_NDIS_5                       0x00000200
DECL|macro|NDIS_MINIPORT_IS_CO
mdefine_line|#define NDIS_MINIPORT_IS_CO                           0x00000400
DECL|macro|NDIS_MINIPORT_DESERIALIZE
mdefine_line|#define NDIS_MINIPORT_DESERIALIZE                     0x00000800
DECL|macro|NDIS_MINIPORT_REQUIRES_MEDIA_POLLING
mdefine_line|#define NDIS_MINIPORT_REQUIRES_MEDIA_POLLING          0x00001000
DECL|macro|NDIS_MINIPORT_SUPPORTS_MEDIA_SENSE
mdefine_line|#define NDIS_MINIPORT_SUPPORTS_MEDIA_SENSE            0x00002000
DECL|macro|NDIS_MINIPORT_NETBOOT_CARD
mdefine_line|#define NDIS_MINIPORT_NETBOOT_CARD                    0x00004000
DECL|macro|NDIS_MINIPORT_PM_SUPPORTED
mdefine_line|#define NDIS_MINIPORT_PM_SUPPORTED                    0x00008000
DECL|macro|NDIS_MINIPORT_SUPPORTS_MAC_ADDRESS_OVERWRITE
mdefine_line|#define NDIS_MINIPORT_SUPPORTS_MAC_ADDRESS_OVERWRITE  0x00010000
DECL|macro|NDIS_MINIPORT_USES_SAFE_BUFFER_APIS
mdefine_line|#define NDIS_MINIPORT_USES_SAFE_BUFFER_APIS           0x00020000
DECL|macro|NDIS_MINIPORT_HIDDEN
mdefine_line|#define NDIS_MINIPORT_HIDDEN                          0x00040000
DECL|macro|NDIS_MINIPORT_SWENUM
mdefine_line|#define NDIS_MINIPORT_SWENUM                          0x00080000
DECL|macro|NDIS_MINIPORT_SURPRISE_REMOVE_OK
mdefine_line|#define NDIS_MINIPORT_SURPRISE_REMOVE_OK              0x00100000
DECL|macro|NDIS_MINIPORT_NO_HALT_ON_SUSPEND
mdefine_line|#define NDIS_MINIPORT_NO_HALT_ON_SUSPEND              0x00200000
DECL|macro|NDIS_MINIPORT_HARDWARE_DEVICE
mdefine_line|#define NDIS_MINIPORT_HARDWARE_DEVICE                 0x00400000
DECL|macro|NDIS_MINIPORT_SUPPORTS_CANCEL_SEND_PACKETS
mdefine_line|#define NDIS_MINIPORT_SUPPORTS_CANCEL_SEND_PACKETS    0x00800000
DECL|macro|NDIS_MINIPORT_64BITS_DMA
mdefine_line|#define NDIS_MINIPORT_64BITS_DMA                      0x01000000
DECL|macro|NDIS_MEDIUM_802_3
mdefine_line|#define NDIS_MEDIUM_802_3&t;&t;0x00000000
DECL|macro|NDIS_MEDIUM_802_5
mdefine_line|#define NDIS_MEDIUM_802_5&t;&t;0x00000001
DECL|macro|NDIS_MEDIUM_FDDI
mdefine_line|#define NDIS_MEDIUM_FDDI&t;&t;0x00000002
DECL|macro|NDIS_MEDIUM_WAN
mdefine_line|#define NDIS_MEDIUM_WAN&t;&t;&t;0x00000003
DECL|macro|NDIS_MEDIUM_LOCAL_TALK
mdefine_line|#define NDIS_MEDIUM_LOCAL_TALK&t;&t;0x00000004
DECL|macro|NDIS_MEDIUM_DIX
mdefine_line|#define NDIS_MEDIUM_DIX&t;&t;&t;0x00000005
DECL|macro|NDIS_MEDIUM_ARCENT_RAW
mdefine_line|#define NDIS_MEDIUM_ARCENT_RAW&t;&t;0x00000006
DECL|macro|NDIS_MEDIUM_ARCENT_878_2
mdefine_line|#define NDIS_MEDIUM_ARCENT_878_2&t;0x00000007
DECL|macro|NDIS_MEDIUM_ATM
mdefine_line|#define NDIS_MEDIUM_ATM&t;&t;&t;0x00000008
DECL|macro|NDIS_MEDIUM_WIRELESS_LAN
mdefine_line|#define NDIS_MEDIUM_WIRELESS_LAN&t;0x00000009
DECL|macro|NDIS_MEDIUM_IRDA
mdefine_line|#define NDIS_MEDIUM_IRDA&t;&t;0x0000000A
DECL|macro|NDIS_MEDIUM_BPC
mdefine_line|#define NDIS_MEDIUM_BPC&t;&t;&t;0x0000000B
DECL|macro|NDIS_MEDIUM_CO_WAN
mdefine_line|#define NDIS_MEDIUM_CO_WAN&t;&t;0x0000000C
DECL|macro|NDIS_MEDIUM_1394
mdefine_line|#define NDIS_MEDIUM_1394&t;&t;0x0000000D
DECL|macro|NDIS_PACKET_TYPE_DIRECTED
mdefine_line|#define NDIS_PACKET_TYPE_DIRECTED&t;0x00000001
DECL|macro|NDIS_PACKET_TYPE_MULTICAST
mdefine_line|#define NDIS_PACKET_TYPE_MULTICAST&t;0x00000002
DECL|macro|NDIS_PACKET_TYPE_ALL_MULTICAST
mdefine_line|#define NDIS_PACKET_TYPE_ALL_MULTICAST&t;0x00000004
DECL|macro|NDIS_PACKET_TYPE_BROADCAST
mdefine_line|#define NDIS_PACKET_TYPE_BROADCAST&t;0x00000008
DECL|macro|NDIS_PACKET_TYPE_SOURCE_ROUTING
mdefine_line|#define NDIS_PACKET_TYPE_SOURCE_ROUTING&t;0x00000010
DECL|macro|NDIS_PACKET_TYPE_PROMISCUOUS
mdefine_line|#define NDIS_PACKET_TYPE_PROMISCUOUS&t;0x00000020
DECL|macro|NDIS_PACKET_TYPE_SMT
mdefine_line|#define NDIS_PACKET_TYPE_SMT&t;&t;0x00000040
DECL|macro|NDIS_PACKET_TYPE_ALL_LOCAL
mdefine_line|#define NDIS_PACKET_TYPE_ALL_LOCAL&t;0x00000080
DECL|macro|NDIS_PACKET_TYPE_GROUP
mdefine_line|#define NDIS_PACKET_TYPE_GROUP&t;&t;0x00000100
DECL|macro|NDIS_PACKET_TYPE_ALL_FUNCTIONAL
mdefine_line|#define NDIS_PACKET_TYPE_ALL_FUNCTIONAL&t;0x00000200
DECL|macro|NDIS_PACKET_TYPE_FUNCTIONAL
mdefine_line|#define NDIS_PACKET_TYPE_FUNCTIONAL&t;0x00000400
DECL|macro|NDIS_PACKET_TYPE_MAC_FRAME
mdefine_line|#define NDIS_PACKET_TYPE_MAC_FRAME&t;0x00000800
DECL|macro|NDIS_MEDIA_STATE_CONNECTED
mdefine_line|#define NDIS_MEDIA_STATE_CONNECTED&t;0x00000000
DECL|macro|NDIS_MEDIA_STATE_DISCONNECTED
mdefine_line|#define NDIS_MEDIA_STATE_DISCONNECTED&t;0x00000001
DECL|macro|NDIS_MAC_OPTION_COPY_LOOKAHEAD_DATA
mdefine_line|#define NDIS_MAC_OPTION_COPY_LOOKAHEAD_DATA     0x00000001
DECL|macro|NDIS_MAC_OPTION_RECEIVE_SERIALIZED
mdefine_line|#define NDIS_MAC_OPTION_RECEIVE_SERIALIZED      0x00000002
DECL|macro|NDIS_MAC_OPTION_TRANSFERS_NOT_PEND
mdefine_line|#define NDIS_MAC_OPTION_TRANSFERS_NOT_PEND      0x00000004
DECL|macro|NDIS_MAC_OPTION_NO_LOOPBACK
mdefine_line|#define NDIS_MAC_OPTION_NO_LOOPBACK             0x00000008
DECL|macro|NDIS_MAC_OPTION_FULL_DUPLEX
mdefine_line|#define NDIS_MAC_OPTION_FULL_DUPLEX             0x00000010
DECL|macro|NDIS_MAC_OPTION_EOTX_INDICATION
mdefine_line|#define NDIS_MAC_OPTION_EOTX_INDICATION         0x00000020
DECL|macro|NDIS_MAC_OPTION_8021P_PRIORITY
mdefine_line|#define NDIS_MAC_OPTION_8021P_PRIORITY          0x00000040
DECL|macro|NDIS_MAC_OPTION_RESERVED
mdefine_line|#define NDIS_MAC_OPTION_RESERVED                0x80000000
macro_line|#endif /* _LINUX_NDIS_H */
eof
