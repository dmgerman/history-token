macro_line|#ifndef IEEE1394_RAW1394_H
DECL|macro|IEEE1394_RAW1394_H
mdefine_line|#define IEEE1394_RAW1394_H
DECL|macro|RAW1394_DEVICE_MAJOR
mdefine_line|#define RAW1394_DEVICE_MAJOR      171
DECL|macro|RAW1394_DEVICE_NAME
mdefine_line|#define RAW1394_DEVICE_NAME       &quot;raw1394&quot;
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
id|nodeid_t
id|destination_nodeid
suffix:semicolon
DECL|member|source_nodeid
id|nodeid_t
id|source_nodeid
suffix:semicolon
DECL|member|destination_offset
id|nodeaddr_t
id|destination_offset
suffix:semicolon
DECL|member|tlabel
id|u8
id|tlabel
suffix:semicolon
DECL|member|tcode
id|u8
id|tcode
suffix:semicolon
DECL|member|extended_transaction_code
id|u_int8_t
id|extended_transaction_code
suffix:semicolon
DECL|member|generation
id|u_int32_t
id|generation
suffix:semicolon
DECL|member|buffer_length
id|arm_length_t
id|buffer_length
suffix:semicolon
DECL|member|buffer
id|byte_t
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
r_int
id|response_code
suffix:semicolon
DECL|member|buffer_length
id|arm_length_t
id|buffer_length
suffix:semicolon
DECL|member|buffer
id|byte_t
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
multiline_comment|/* ioctls */
DECL|macro|RAW1394_ISO_XMIT_INIT
mdefine_line|#define RAW1394_ISO_XMIT_INIT        1  /* arg: raw1394_iso_status* */
DECL|macro|RAW1394_ISO_RECV_INIT
mdefine_line|#define RAW1394_ISO_RECV_INIT        2  /* arg: raw1394_iso_status* */
DECL|macro|RAW1394_ISO_RECV_START
mdefine_line|#define RAW1394_ISO_RECV_START       3  /* arg: int, starting cycle */
DECL|macro|RAW1394_ISO_XMIT_START
mdefine_line|#define RAW1394_ISO_XMIT_START       8  /* arg: int[2], { starting cycle, prebuffer } */
DECL|macro|RAW1394_ISO_STOP
mdefine_line|#define RAW1394_ISO_STOP             4
DECL|macro|RAW1394_ISO_GET_STATUS
mdefine_line|#define RAW1394_ISO_GET_STATUS       5  /* arg: raw1394_iso_status* */
DECL|macro|RAW1394_ISO_PRODUCE_CONSUME
mdefine_line|#define RAW1394_ISO_PRODUCE_CONSUME  6  /* arg: int, # of packets */
DECL|macro|RAW1394_ISO_SHUTDOWN
mdefine_line|#define RAW1394_ISO_SHUTDOWN         7
multiline_comment|/* per-packet metadata embedded in the ringbuffer */
multiline_comment|/* must be identical to hpsb_iso_packet_info in iso.h! */
DECL|struct|raw1394_iso_packet_info
r_struct
id|raw1394_iso_packet_info
(brace
DECL|member|len
r_int
r_int
id|len
suffix:semicolon
DECL|member|cycle
r_int
r_int
id|cycle
suffix:semicolon
DECL|member|channel
r_int
r_char
id|channel
suffix:semicolon
multiline_comment|/* recv only */
DECL|member|tag
r_int
r_char
id|tag
suffix:semicolon
DECL|member|sy
r_int
r_char
id|sy
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|raw1394_iso_config
r_struct
id|raw1394_iso_config
(brace
DECL|member|buf_packets
r_int
r_int
id|buf_packets
suffix:semicolon
DECL|member|max_packet_size
r_int
r_int
id|max_packet_size
suffix:semicolon
DECL|member|channel
r_int
id|channel
suffix:semicolon
DECL|member|speed
r_int
id|speed
suffix:semicolon
multiline_comment|/* xmit only */
DECL|member|irq_interval
r_int
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
multiline_comment|/* byte offset between successive packets in the buffer */
DECL|member|buf_stride
r_int
id|buf_stride
suffix:semicolon
multiline_comment|/* byte offset of data payload within each packet */
DECL|member|packet_data_offset
r_int
id|packet_data_offset
suffix:semicolon
multiline_comment|/* byte offset of struct iso_packet_info within each packet */
DECL|member|packet_info_offset
r_int
id|packet_info_offset
suffix:semicolon
multiline_comment|/* index of next packet to fill with data (ISO transmission)&n;&t;   or next packet containing data recieved (ISO reception) */
DECL|member|first_packet
r_int
r_int
id|first_packet
suffix:semicolon
multiline_comment|/* number of packets waiting to be filled with data (ISO transmission)&n;&t;   or containing data received (ISO reception) */
DECL|member|n_packets
r_int
r_int
id|n_packets
suffix:semicolon
multiline_comment|/* approximate number of packets dropped due to overflow or&n;&t;   underflow of the packet buffer (a value of zero guarantees&n;&t;   that no packets have been dropped) */
DECL|member|overflows
r_int
r_int
id|overflows
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
DECL|struct|iso_block_store
r_struct
id|iso_block_store
(brace
DECL|member|refcount
id|atomic_t
id|refcount
suffix:semicolon
DECL|member|data_size
r_int
id|data_size
suffix:semicolon
DECL|member|data
id|quadlet_t
id|data
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|enum|raw1394_iso_state
DECL|enumerator|RAW1394_ISO_INACTIVE
r_enum
id|raw1394_iso_state
(brace
id|RAW1394_ISO_INACTIVE
op_assign
l_int|0
comma
DECL|enumerator|RAW1394_ISO_RECV
id|RAW1394_ISO_RECV
op_assign
l_int|1
comma
DECL|enumerator|RAW1394_ISO_XMIT
id|RAW1394_ISO_XMIT
op_assign
l_int|2
)brace
suffix:semicolon
DECL|struct|file_info
r_struct
id|file_info
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|enumerator|opened
DECL|enumerator|initialized
DECL|enumerator|connected
DECL|member|state
r_enum
(brace
id|opened
comma
id|initialized
comma
id|connected
)brace
id|state
suffix:semicolon
DECL|member|protocol_version
r_int
r_int
id|protocol_version
suffix:semicolon
DECL|member|host
r_struct
id|hpsb_host
op_star
id|host
suffix:semicolon
DECL|member|req_pending
r_struct
id|list_head
id|req_pending
suffix:semicolon
DECL|member|req_complete
r_struct
id|list_head
id|req_complete
suffix:semicolon
DECL|member|complete_sem
r_struct
id|semaphore
id|complete_sem
suffix:semicolon
DECL|member|reqlists_lock
id|spinlock_t
id|reqlists_lock
suffix:semicolon
DECL|member|poll_wait_complete
id|wait_queue_head_t
id|poll_wait_complete
suffix:semicolon
DECL|member|addr_list
r_struct
id|list_head
id|addr_list
suffix:semicolon
DECL|member|fcp_buffer
id|u8
op_star
id|fcp_buffer
suffix:semicolon
multiline_comment|/* old ISO API */
DECL|member|listen_channels
id|u64
id|listen_channels
suffix:semicolon
DECL|member|iso_buffer
id|quadlet_t
op_star
id|iso_buffer
suffix:semicolon
DECL|member|iso_buffer_length
r_int
id|iso_buffer_length
suffix:semicolon
DECL|member|notification
id|u8
id|notification
suffix:semicolon
multiline_comment|/* (busreset-notification) RAW1394_NOTIFY_OFF/ON */
multiline_comment|/* new rawiso API */
DECL|member|iso_state
r_enum
id|raw1394_iso_state
id|iso_state
suffix:semicolon
DECL|member|iso_handle
r_struct
id|hpsb_iso
op_star
id|iso_handle
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|arm_addr
r_struct
id|arm_addr
(brace
DECL|member|addr_list
r_struct
id|list_head
id|addr_list
suffix:semicolon
multiline_comment|/* file_info list */
DECL|member|start
DECL|member|end
id|u64
id|start
comma
id|end
suffix:semicolon
DECL|member|arm_tag
id|u64
id|arm_tag
suffix:semicolon
DECL|member|access_rights
id|u8
id|access_rights
suffix:semicolon
DECL|member|notification_options
id|u8
id|notification_options
suffix:semicolon
DECL|member|client_transactions
id|u8
id|client_transactions
suffix:semicolon
DECL|member|recvb
id|u64
id|recvb
suffix:semicolon
DECL|member|rec_length
id|u16
id|rec_length
suffix:semicolon
DECL|member|addr_space_buffer
id|u8
op_star
id|addr_space_buffer
suffix:semicolon
multiline_comment|/* accessed by read/write/lock */
)brace
suffix:semicolon
DECL|struct|pending_request
r_struct
id|pending_request
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|file_info
r_struct
id|file_info
op_star
id|file_info
suffix:semicolon
DECL|member|packet
r_struct
id|hpsb_packet
op_star
id|packet
suffix:semicolon
DECL|member|ibs
r_struct
id|iso_block_store
op_star
id|ibs
suffix:semicolon
DECL|member|data
id|quadlet_t
op_star
id|data
suffix:semicolon
DECL|member|free_data
r_int
id|free_data
suffix:semicolon
DECL|member|req
r_struct
id|raw1394_request
id|req
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|host_info
r_struct
id|host_info
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|host
r_struct
id|hpsb_host
op_star
id|host
suffix:semicolon
DECL|member|file_info_list
r_struct
id|list_head
id|file_info_list
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* IEEE1394_RAW1394_H */
eof
