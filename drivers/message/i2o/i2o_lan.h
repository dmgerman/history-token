multiline_comment|/*&n; *   &t;i2o_lan.h&t;&t;&t;I2O LAN Class definitions&n; *&n; *      I2O LAN CLASS OSM       &t;May 26th 2000&n; *&n; *      (C) Copyright 1999, 2000&t;University of Helsinki,&n; *&t;&t;&t;&t;&t;Department of Computer Science&n; *&n; *      This code is still under development / test.&n; *&n; *&t;Author:&t;&t;Auvo H&#xfffd;kkinen &lt;Auvo.Hakkinen@cs.Helsinki.FI&gt;&n; *&t;&t;&t;Juha Siev&#xfffd;nen &lt;Juha.Sievanen@cs.Helsinki.FI&gt;&n; *&t;&t;&t;Taneli V&#xfffd;h&#xfffd;kangas &lt;Taneli.Vahakangas@cs.Helsinki.FI&gt;&n; */
macro_line|#ifndef _I2O_LAN_H
DECL|macro|_I2O_LAN_H
mdefine_line|#define _I2O_LAN_H
multiline_comment|/* Default values for tunable parameters first */
DECL|macro|I2O_LAN_MAX_BUCKETS_OUT
mdefine_line|#define I2O_LAN_MAX_BUCKETS_OUT 96
DECL|macro|I2O_LAN_BUCKET_THRESH
mdefine_line|#define I2O_LAN_BUCKET_THRESH&t;18&t;/* 9 buckets in one message */
DECL|macro|I2O_LAN_RX_COPYBREAK
mdefine_line|#define I2O_LAN_RX_COPYBREAK&t;200
DECL|macro|I2O_LAN_TX_TIMEOUT
mdefine_line|#define I2O_LAN_TX_TIMEOUT &t;(1*HZ)
DECL|macro|I2O_LAN_TX_BATCH_MODE
mdefine_line|#define I2O_LAN_TX_BATCH_MODE&t;2&t;/* 2=automatic, 1=on, 0=off */
DECL|macro|I2O_LAN_EVENT_MASK
mdefine_line|#define I2O_LAN_EVENT_MASK&t;0&t;/* 0=None, 0xFFC00002=All */
multiline_comment|/* LAN types */
DECL|macro|I2O_LAN_ETHERNET
mdefine_line|#define I2O_LAN_ETHERNET&t;0x0030
DECL|macro|I2O_LAN_100VG
mdefine_line|#define I2O_LAN_100VG&t;&t;0x0040
DECL|macro|I2O_LAN_TR
mdefine_line|#define I2O_LAN_TR&t;&t;0x0050
DECL|macro|I2O_LAN_FDDI
mdefine_line|#define I2O_LAN_FDDI&t;&t;0x0060
DECL|macro|I2O_LAN_FIBRE_CHANNEL
mdefine_line|#define I2O_LAN_FIBRE_CHANNEL&t;0x0070
DECL|macro|I2O_LAN_UNKNOWN
mdefine_line|#define I2O_LAN_UNKNOWN&t;&t;0x00000000
multiline_comment|/* Connector types */
multiline_comment|/* Ethernet */
DECL|macro|I2O_LAN_AUI
mdefine_line|#define I2O_LAN_AUI&t;&t;(I2O_LAN_ETHERNET &lt;&lt; 4) + 0x00000001
DECL|macro|I2O_LAN_10BASE5
mdefine_line|#define I2O_LAN_10BASE5&t;&t;(I2O_LAN_ETHERNET &lt;&lt; 4) + 0x00000002
DECL|macro|I2O_LAN_FIORL
mdefine_line|#define I2O_LAN_FIORL&t;&t;(I2O_LAN_ETHERNET &lt;&lt; 4) + 0x00000003
DECL|macro|I2O_LAN_10BASE2
mdefine_line|#define I2O_LAN_10BASE2&t;&t;(I2O_LAN_ETHERNET &lt;&lt; 4) + 0x00000004
DECL|macro|I2O_LAN_10BROAD36
mdefine_line|#define I2O_LAN_10BROAD36&t;(I2O_LAN_ETHERNET &lt;&lt; 4) + 0x00000005
DECL|macro|I2O_LAN_10BASE_T
mdefine_line|#define I2O_LAN_10BASE_T&t;(I2O_LAN_ETHERNET &lt;&lt; 4) + 0x00000006
DECL|macro|I2O_LAN_10BASE_FP
mdefine_line|#define I2O_LAN_10BASE_FP&t;(I2O_LAN_ETHERNET &lt;&lt; 4) + 0x00000007
DECL|macro|I2O_LAN_10BASE_FB
mdefine_line|#define I2O_LAN_10BASE_FB&t;(I2O_LAN_ETHERNET &lt;&lt; 4) + 0x00000008
DECL|macro|I2O_LAN_10BASE_FL
mdefine_line|#define I2O_LAN_10BASE_FL&t;(I2O_LAN_ETHERNET &lt;&lt; 4) + 0x00000009
DECL|macro|I2O_LAN_100BASE_TX
mdefine_line|#define I2O_LAN_100BASE_TX&t;(I2O_LAN_ETHERNET &lt;&lt; 4) + 0x0000000A
DECL|macro|I2O_LAN_100BASE_FX
mdefine_line|#define I2O_LAN_100BASE_FX&t;(I2O_LAN_ETHERNET &lt;&lt; 4) + 0x0000000B
DECL|macro|I2O_LAN_100BASE_T4
mdefine_line|#define I2O_LAN_100BASE_T4&t;(I2O_LAN_ETHERNET &lt;&lt; 4) + 0x0000000C
DECL|macro|I2O_LAN_1000BASE_SX
mdefine_line|#define I2O_LAN_1000BASE_SX&t;(I2O_LAN_ETHERNET &lt;&lt; 4) + 0x0000000D
DECL|macro|I2O_LAN_1000BASE_LX
mdefine_line|#define I2O_LAN_1000BASE_LX&t;(I2O_LAN_ETHERNET &lt;&lt; 4) + 0x0000000E
DECL|macro|I2O_LAN_1000BASE_CX
mdefine_line|#define I2O_LAN_1000BASE_CX&t;(I2O_LAN_ETHERNET &lt;&lt; 4) + 0x0000000F
DECL|macro|I2O_LAN_1000BASE_T
mdefine_line|#define I2O_LAN_1000BASE_T&t;(I2O_LAN_ETHERNET &lt;&lt; 4) + 0x00000010
multiline_comment|/* AnyLAN */
DECL|macro|I2O_LAN_100VG_ETHERNET
mdefine_line|#define I2O_LAN_100VG_ETHERNET&t;(I2O_LAN_100VG &lt;&lt; 4) + 0x00000001
DECL|macro|I2O_LAN_100VG_TR
mdefine_line|#define I2O_LAN_100VG_TR&t;(I2O_LAN_100VG &lt;&lt; 4) + 0x00000002
multiline_comment|/* Token Ring */
DECL|macro|I2O_LAN_4MBIT
mdefine_line|#define I2O_LAN_4MBIT&t;&t;(I2O_LAN_TR &lt;&lt; 4) + 0x00000001
DECL|macro|I2O_LAN_16MBIT
mdefine_line|#define I2O_LAN_16MBIT&t;&t;(I2O_LAN_TR &lt;&lt; 4) + 0x00000002
multiline_comment|/* FDDI */
DECL|macro|I2O_LAN_125MBAUD
mdefine_line|#define I2O_LAN_125MBAUD&t;(I2O_LAN_FDDI &lt;&lt; 4) + 0x00000001
multiline_comment|/* Fibre Channel */
DECL|macro|I2O_LAN_POINT_POINT
mdefine_line|#define I2O_LAN_POINT_POINT&t;(I2O_LAN_FIBRE_CHANNEL &lt;&lt; 4) + 0x00000001
DECL|macro|I2O_LAN_ARB_LOOP
mdefine_line|#define I2O_LAN_ARB_LOOP&t;(I2O_LAN_FIBRE_CHANNEL &lt;&lt; 4) + 0x00000002
DECL|macro|I2O_LAN_PUBLIC_LOOP
mdefine_line|#define I2O_LAN_PUBLIC_LOOP&t;(I2O_LAN_FIBRE_CHANNEL &lt;&lt; 4) + 0x00000003
DECL|macro|I2O_LAN_FABRIC
mdefine_line|#define I2O_LAN_FABRIC&t;&t;(I2O_LAN_FIBRE_CHANNEL &lt;&lt; 4) + 0x00000004
DECL|macro|I2O_LAN_EMULATION
mdefine_line|#define I2O_LAN_EMULATION&t;0x00000F00
DECL|macro|I2O_LAN_OTHER
mdefine_line|#define I2O_LAN_OTHER&t;&t;0x00000F01
DECL|macro|I2O_LAN_DEFAULT
mdefine_line|#define I2O_LAN_DEFAULT&t;&t;0xFFFFFFFF
multiline_comment|/* LAN class functions */
DECL|macro|LAN_PACKET_SEND
mdefine_line|#define LAN_PACKET_SEND&t;&t;0x3B
DECL|macro|LAN_SDU_SEND
mdefine_line|#define LAN_SDU_SEND&t;&t;0x3D
DECL|macro|LAN_RECEIVE_POST
mdefine_line|#define LAN_RECEIVE_POST&t;0x3E
DECL|macro|LAN_RESET
mdefine_line|#define LAN_RESET&t;&t;0x35
DECL|macro|LAN_SUSPEND
mdefine_line|#define LAN_SUSPEND&t;&t;0x37
multiline_comment|/* LAN DetailedStatusCode defines */
DECL|macro|I2O_LAN_DSC_SUCCESS
mdefine_line|#define I2O_LAN_DSC_SUCCESS&t;&t;&t;0x00
DECL|macro|I2O_LAN_DSC_DEVICE_FAILURE
mdefine_line|#define I2O_LAN_DSC_DEVICE_FAILURE&t;&t;0x01
DECL|macro|I2O_LAN_DSC_DESTINATION_NOT_FOUND
mdefine_line|#define I2O_LAN_DSC_DESTINATION_NOT_FOUND&t;0x02
DECL|macro|I2O_LAN_DSC_TRANSMIT_ERROR
mdefine_line|#define&t;I2O_LAN_DSC_TRANSMIT_ERROR&t;&t;0x03
DECL|macro|I2O_LAN_DSC_TRANSMIT_ABORTED
mdefine_line|#define I2O_LAN_DSC_TRANSMIT_ABORTED&t;&t;0x04
DECL|macro|I2O_LAN_DSC_RECEIVE_ERROR
mdefine_line|#define I2O_LAN_DSC_RECEIVE_ERROR&t;&t;0x05
DECL|macro|I2O_LAN_DSC_RECEIVE_ABORTED
mdefine_line|#define I2O_LAN_DSC_RECEIVE_ABORTED&t;&t;0x06
DECL|macro|I2O_LAN_DSC_DMA_ERROR
mdefine_line|#define I2O_LAN_DSC_DMA_ERROR&t;&t;&t;0x07
DECL|macro|I2O_LAN_DSC_BAD_PACKET_DETECTED
mdefine_line|#define I2O_LAN_DSC_BAD_PACKET_DETECTED&t;&t;0x08
DECL|macro|I2O_LAN_DSC_OUT_OF_MEMORY
mdefine_line|#define I2O_LAN_DSC_OUT_OF_MEMORY&t;&t;0x09
DECL|macro|I2O_LAN_DSC_BUCKET_OVERRUN
mdefine_line|#define I2O_LAN_DSC_BUCKET_OVERRUN&t;&t;0x0A
DECL|macro|I2O_LAN_DSC_IOP_INTERNAL_ERROR
mdefine_line|#define I2O_LAN_DSC_IOP_INTERNAL_ERROR&t;&t;0x0B
DECL|macro|I2O_LAN_DSC_CANCELED
mdefine_line|#define I2O_LAN_DSC_CANCELED&t;&t;&t;0x0C
DECL|macro|I2O_LAN_DSC_INVALID_TRANSACTION_CONTEXT
mdefine_line|#define I2O_LAN_DSC_INVALID_TRANSACTION_CONTEXT&t;0x0D
DECL|macro|I2O_LAN_DSC_DEST_ADDRESS_DETECTED
mdefine_line|#define I2O_LAN_DSC_DEST_ADDRESS_DETECTED&t;0x0E
DECL|macro|I2O_LAN_DSC_DEST_ADDRESS_OMITTED
mdefine_line|#define I2O_LAN_DSC_DEST_ADDRESS_OMITTED&t;0x0F
DECL|macro|I2O_LAN_DSC_PARTIAL_PACKET_RETURNED
mdefine_line|#define I2O_LAN_DSC_PARTIAL_PACKET_RETURNED&t;0x10
DECL|macro|I2O_LAN_DSC_SUSPENDED
mdefine_line|#define I2O_LAN_DSC_SUSPENDED&t;&t;&t;0x11
DECL|struct|i2o_packet_info
r_struct
id|i2o_packet_info
(brace
DECL|member|offset
id|u32
id|offset
suffix:colon
l_int|24
suffix:semicolon
DECL|member|flags
id|u32
id|flags
suffix:colon
l_int|8
suffix:semicolon
DECL|member|len
id|u32
id|len
suffix:colon
l_int|24
suffix:semicolon
DECL|member|status
id|u32
id|status
suffix:colon
l_int|8
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|i2o_bucket_descriptor
r_struct
id|i2o_bucket_descriptor
(brace
DECL|member|context
id|u32
id|context
suffix:semicolon
multiline_comment|/* FIXME: 64bit support */
DECL|member|packet_info
r_struct
id|i2o_packet_info
id|packet_info
(braket
l_int|1
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Event Indicator Mask Flags for LAN OSM */
DECL|macro|I2O_LAN_EVT_LINK_DOWN
mdefine_line|#define I2O_LAN_EVT_LINK_DOWN&t;&t;0x01
DECL|macro|I2O_LAN_EVT_LINK_UP
mdefine_line|#define I2O_LAN_EVT_LINK_UP&t;&t;0x02
DECL|macro|I2O_LAN_EVT_MEDIA_CHANGE
mdefine_line|#define I2O_LAN_EVT_MEDIA_CHANGE &t;0x04
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/fddidevice.h&gt;
DECL|struct|i2o_lan_local
r_struct
id|i2o_lan_local
(brace
DECL|member|unit
id|u8
id|unit
suffix:semicolon
DECL|member|i2o_dev
r_struct
id|i2o_device
op_star
id|i2o_dev
suffix:semicolon
DECL|member|stats
r_struct
id|fddi_statistics
id|stats
suffix:semicolon
multiline_comment|/* see also struct net_device_stats */
DECL|member|type_trans
r_int
r_int
(paren
op_star
id|type_trans
)paren
(paren
r_struct
id|sk_buff
op_star
comma
r_struct
id|net_device
op_star
)paren
suffix:semicolon
DECL|member|buckets_out
id|atomic_t
id|buckets_out
suffix:semicolon
multiline_comment|/* nbr of unused buckets on DDM */
DECL|member|tx_out
id|atomic_t
id|tx_out
suffix:semicolon
multiline_comment|/* outstanding TXes */
DECL|member|tx_count
id|u8
id|tx_count
suffix:semicolon
multiline_comment|/* packets in one TX message frame */
DECL|member|tx_max_out
id|u16
id|tx_max_out
suffix:semicolon
multiline_comment|/* DDM&squot;s Tx queue len */
DECL|member|sgl_max
id|u8
id|sgl_max
suffix:semicolon
multiline_comment|/* max SGLs in one message frame */
DECL|member|m
id|u32
id|m
suffix:semicolon
multiline_comment|/* IOP address of the batch msg frame */
DECL|member|i2o_batch_send_task
r_struct
id|tq_struct
id|i2o_batch_send_task
suffix:semicolon
DECL|member|send_active
r_int
id|send_active
suffix:semicolon
DECL|member|i2o_fbl
r_struct
id|sk_buff
op_star
op_star
id|i2o_fbl
suffix:semicolon
multiline_comment|/* Free bucket list (to reuse skbs) */
DECL|member|i2o_fbl_tail
r_int
id|i2o_fbl_tail
suffix:semicolon
DECL|member|fbl_lock
id|spinlock_t
id|fbl_lock
suffix:semicolon
DECL|member|tx_lock
id|spinlock_t
id|tx_lock
suffix:semicolon
DECL|member|max_size_mc_table
id|u32
id|max_size_mc_table
suffix:semicolon
multiline_comment|/* max number of multicast addresses */
multiline_comment|/* LAN OSM configurable parameters are here: */
DECL|member|max_buckets_out
id|u16
id|max_buckets_out
suffix:semicolon
multiline_comment|/* max nbr of buckets to send to DDM */
DECL|member|bucket_thresh
id|u16
id|bucket_thresh
suffix:semicolon
multiline_comment|/* send more when this many used */
DECL|member|rx_copybreak
id|u16
id|rx_copybreak
suffix:semicolon
DECL|member|tx_batch_mode
id|u8
id|tx_batch_mode
suffix:semicolon
multiline_comment|/* Set when using batch mode sends */
DECL|member|i2o_event_mask
id|u32
id|i2o_event_mask
suffix:semicolon
multiline_comment|/* To turn on interesting event flags */
)brace
suffix:semicolon
macro_line|#endif /* _I2O_LAN_H */
eof
