macro_line|#ifndef IEEE1394_RAW1394_H
DECL|macro|IEEE1394_RAW1394_H
mdefine_line|#define IEEE1394_RAW1394_H
multiline_comment|/* header for the raw1394 API that is exported to user-space */
DECL|macro|RAW1394_KERNELAPI_VERSION
mdefine_line|#define RAW1394_KERNELAPI_VERSION 4
multiline_comment|/* state: opened */
DECL|macro|RAW1394_REQ_INITIALIZE
mdefine_line|#define RAW1394_REQ_INITIALIZE    1
multiline_comment|/* state: initialized */
DECL|macro|RAW1394_REQ_LIST_CARDS
mdefine_line|#define RAW1394_REQ_LIST_CARDS    2
DECL|macro|RAW1394_REQ_SET_CARD
mdefine_line|#define RAW1394_REQ_SET_CARD      3
multiline_comment|/* state: connected */
DECL|macro|RAW1394_REQ_ASYNC_READ
mdefine_line|#define RAW1394_REQ_ASYNC_READ      100
DECL|macro|RAW1394_REQ_ASYNC_WRITE
mdefine_line|#define RAW1394_REQ_ASYNC_WRITE     101
DECL|macro|RAW1394_REQ_LOCK
mdefine_line|#define RAW1394_REQ_LOCK            102
DECL|macro|RAW1394_REQ_LOCK64
mdefine_line|#define RAW1394_REQ_LOCK64          103
DECL|macro|RAW1394_REQ_ISO_SEND
mdefine_line|#define RAW1394_REQ_ISO_SEND        104
DECL|macro|RAW1394_REQ_ASYNC_SEND
mdefine_line|#define RAW1394_REQ_ASYNC_SEND      105
DECL|macro|RAW1394_REQ_ASYNC_STREAM
mdefine_line|#define RAW1394_REQ_ASYNC_STREAM    106
DECL|macro|RAW1394_REQ_ISO_LISTEN
mdefine_line|#define RAW1394_REQ_ISO_LISTEN      200
DECL|macro|RAW1394_REQ_FCP_LISTEN
mdefine_line|#define RAW1394_REQ_FCP_LISTEN      201
DECL|macro|RAW1394_REQ_RESET_BUS
mdefine_line|#define RAW1394_REQ_RESET_BUS       202
DECL|macro|RAW1394_REQ_GET_ROM
mdefine_line|#define RAW1394_REQ_GET_ROM         203
DECL|macro|RAW1394_REQ_UPDATE_ROM
mdefine_line|#define RAW1394_REQ_UPDATE_ROM      204
DECL|macro|RAW1394_REQ_ECHO
mdefine_line|#define RAW1394_REQ_ECHO            205
DECL|macro|RAW1394_REQ_ARM_REGISTER
mdefine_line|#define RAW1394_REQ_ARM_REGISTER    300
DECL|macro|RAW1394_REQ_ARM_UNREGISTER
mdefine_line|#define RAW1394_REQ_ARM_UNREGISTER  301
DECL|macro|RAW1394_REQ_RESET_NOTIFY
mdefine_line|#define RAW1394_REQ_RESET_NOTIFY    400
DECL|macro|RAW1394_REQ_PHYPACKET
mdefine_line|#define RAW1394_REQ_PHYPACKET       500
multiline_comment|/* kernel to user */
DECL|macro|RAW1394_REQ_BUS_RESET
mdefine_line|#define RAW1394_REQ_BUS_RESET        10000
DECL|macro|RAW1394_REQ_ISO_RECEIVE
mdefine_line|#define RAW1394_REQ_ISO_RECEIVE      10001
DECL|macro|RAW1394_REQ_FCP_REQUEST
mdefine_line|#define RAW1394_REQ_FCP_REQUEST      10002
DECL|macro|RAW1394_REQ_ARM
mdefine_line|#define RAW1394_REQ_ARM              10003
DECL|macro|RAW1394_REQ_RAWISO_ACTIVITY
mdefine_line|#define RAW1394_REQ_RAWISO_ACTIVITY  10004
multiline_comment|/* error codes */
DECL|macro|RAW1394_ERROR_NONE
mdefine_line|#define RAW1394_ERROR_NONE        0
DECL|macro|RAW1394_ERROR_COMPAT
mdefine_line|#define RAW1394_ERROR_COMPAT      (-1001)
DECL|macro|RAW1394_ERROR_STATE_ORDER
mdefine_line|#define RAW1394_ERROR_STATE_ORDER (-1002)
DECL|macro|RAW1394_ERROR_GENERATION
mdefine_line|#define RAW1394_ERROR_GENERATION  (-1003)
DECL|macro|RAW1394_ERROR_INVALID_ARG
mdefine_line|#define RAW1394_ERROR_INVALID_ARG (-1004)
DECL|macro|RAW1394_ERROR_MEMFAULT
mdefine_line|#define RAW1394_ERROR_MEMFAULT    (-1005)
DECL|macro|RAW1394_ERROR_ALREADY
mdefine_line|#define RAW1394_ERROR_ALREADY     (-1006)
DECL|macro|RAW1394_ERROR_EXCESSIVE
mdefine_line|#define RAW1394_ERROR_EXCESSIVE   (-1020)
DECL|macro|RAW1394_ERROR_UNTIDY_LEN
mdefine_line|#define RAW1394_ERROR_UNTIDY_LEN  (-1021)
DECL|macro|RAW1394_ERROR_SEND_ERROR
mdefine_line|#define RAW1394_ERROR_SEND_ERROR  (-1100)
DECL|macro|RAW1394_ERROR_ABORTED
mdefine_line|#define RAW1394_ERROR_ABORTED     (-1101)
DECL|macro|RAW1394_ERROR_TIMEOUT
mdefine_line|#define RAW1394_ERROR_TIMEOUT     (-1102)
multiline_comment|/* arm_codes */
DECL|macro|ARM_READ
mdefine_line|#define ARM_READ   1
DECL|macro|ARM_WRITE
mdefine_line|#define ARM_WRITE  2
DECL|macro|ARM_LOCK
mdefine_line|#define ARM_LOCK   4
DECL|macro|RAW1394_LONG_RESET
mdefine_line|#define RAW1394_LONG_RESET  0
DECL|macro|RAW1394_SHORT_RESET
mdefine_line|#define RAW1394_SHORT_RESET 1
multiline_comment|/* busresetnotify ... */
DECL|macro|RAW1394_NOTIFY_OFF
mdefine_line|#define RAW1394_NOTIFY_OFF 0
DECL|macro|RAW1394_NOTIFY_ON
mdefine_line|#define RAW1394_NOTIFY_ON  1
macro_line|#include &lt;asm/types.h&gt;
DECL|struct|raw1394_request
r_struct
id|raw1394_request
(brace
DECL|member|type
id|__u32
id|type
suffix:semicolon
DECL|member|error
id|__s32
id|error
suffix:semicolon
DECL|member|misc
id|__u32
id|misc
suffix:semicolon
DECL|member|generation
id|__u32
id|generation
suffix:semicolon
DECL|member|length
id|__u32
id|length
suffix:semicolon
DECL|member|address
id|__u64
id|address
suffix:semicolon
DECL|member|tag
id|__u64
id|tag
suffix:semicolon
DECL|member|sendb
id|__u64
id|sendb
suffix:semicolon
DECL|member|recvb
id|__u64
id|recvb
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|raw1394_khost_list
r_struct
id|raw1394_khost_list
(brace
DECL|member|nodes
id|__u32
id|nodes
suffix:semicolon
DECL|member|name
id|__u8
id|name
(braket
l_int|32
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|arm_request
r_typedef
r_struct
id|arm_request
(brace
DECL|member|destination_nodeid
id|__u16
id|destination_nodeid
suffix:semicolon
DECL|member|source_nodeid
id|__u16
id|source_nodeid
suffix:semicolon
DECL|member|destination_offset
id|__u64
id|destination_offset
suffix:semicolon
DECL|member|tlabel
id|__u8
id|tlabel
suffix:semicolon
DECL|member|tcode
id|__u8
id|tcode
suffix:semicolon
DECL|member|extended_transaction_code
id|__u8
id|extended_transaction_code
suffix:semicolon
DECL|member|generation
id|__u32
id|generation
suffix:semicolon
DECL|member|buffer_length
id|__u16
id|buffer_length
suffix:semicolon
DECL|member|buffer
id|__u8
op_star
id|buffer
suffix:semicolon
DECL|typedef|arm_request_t
)brace
op_star
id|arm_request_t
suffix:semicolon
DECL|struct|arm_response
r_typedef
r_struct
id|arm_response
(brace
DECL|member|response_code
id|__s32
id|response_code
suffix:semicolon
DECL|member|buffer_length
id|__u16
id|buffer_length
suffix:semicolon
DECL|member|buffer
id|__u8
op_star
id|buffer
suffix:semicolon
DECL|typedef|arm_response_t
)brace
op_star
id|arm_response_t
suffix:semicolon
DECL|struct|arm_request_response
r_typedef
r_struct
id|arm_request_response
(brace
DECL|member|request
r_struct
id|arm_request
op_star
id|request
suffix:semicolon
DECL|member|response
r_struct
id|arm_response
op_star
id|response
suffix:semicolon
DECL|typedef|arm_request_response_t
)brace
op_star
id|arm_request_response_t
suffix:semicolon
multiline_comment|/* rawiso API */
macro_line|#include &quot;ieee1394-ioctl.h&quot;
multiline_comment|/* per-packet metadata embedded in the ringbuffer */
multiline_comment|/* must be identical to hpsb_iso_packet_info in iso.h! */
DECL|struct|raw1394_iso_packet_info
r_struct
id|raw1394_iso_packet_info
(brace
DECL|member|offset
id|__u32
id|offset
suffix:semicolon
DECL|member|len
id|__u16
id|len
suffix:semicolon
DECL|member|cycle
id|__u16
id|cycle
suffix:semicolon
multiline_comment|/* recv only */
DECL|member|channel
id|__u8
id|channel
suffix:semicolon
multiline_comment|/* recv only */
DECL|member|tag
id|__u8
id|tag
suffix:semicolon
DECL|member|sy
id|__u8
id|sy
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* argument for RAW1394_ISO_RECV/XMIT_PACKETS ioctls */
DECL|struct|raw1394_iso_packets
r_struct
id|raw1394_iso_packets
(brace
DECL|member|n_packets
id|__u32
id|n_packets
suffix:semicolon
DECL|member|infos
r_struct
id|raw1394_iso_packet_info
op_star
id|infos
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|raw1394_iso_config
r_struct
id|raw1394_iso_config
(brace
multiline_comment|/* size of packet data buffer, in bytes (will be rounded up to PAGE_SIZE) */
DECL|member|data_buf_size
id|__u32
id|data_buf_size
suffix:semicolon
multiline_comment|/* # of packets to buffer */
DECL|member|buf_packets
id|__u32
id|buf_packets
suffix:semicolon
multiline_comment|/* iso channel (set to -1 for multi-channel recv) */
DECL|member|channel
id|__s32
id|channel
suffix:semicolon
multiline_comment|/* xmit only - iso transmission speed */
DECL|member|speed
id|__u8
id|speed
suffix:semicolon
multiline_comment|/* max. latency of buffer, in packets (-1 if you don&squot;t care) */
DECL|member|irq_interval
id|__s32
id|irq_interval
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* argument to RAW1394_ISO_XMIT/RECV_INIT and RAW1394_ISO_GET_STATUS */
DECL|struct|raw1394_iso_status
r_struct
id|raw1394_iso_status
(brace
multiline_comment|/* current settings */
DECL|member|config
r_struct
id|raw1394_iso_config
id|config
suffix:semicolon
multiline_comment|/* number of packets waiting to be filled with data (ISO transmission)&n;&t;   or containing data received (ISO reception) */
DECL|member|n_packets
id|__u32
id|n_packets
suffix:semicolon
multiline_comment|/* approximate number of packets dropped due to overflow or&n;&t;   underflow of the packet buffer (a value of zero guarantees&n;&t;   that no packets have been dropped) */
DECL|member|overflows
id|__u32
id|overflows
suffix:semicolon
multiline_comment|/* cycle number at which next packet will be transmitted;&n;&t;   -1 if not known */
DECL|member|xmit_cycle
id|__s16
id|xmit_cycle
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* IEEE1394_RAW1394_H */
eof
