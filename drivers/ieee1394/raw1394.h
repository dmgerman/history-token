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
mdefine_line|#define RAW1394_REQ_ASYNC_READ    100
DECL|macro|RAW1394_REQ_ASYNC_WRITE
mdefine_line|#define RAW1394_REQ_ASYNC_WRITE   101
DECL|macro|RAW1394_REQ_LOCK
mdefine_line|#define RAW1394_REQ_LOCK          102
DECL|macro|RAW1394_REQ_LOCK64
mdefine_line|#define RAW1394_REQ_LOCK64        103
DECL|macro|RAW1394_REQ_ISO_SEND
mdefine_line|#define RAW1394_REQ_ISO_SEND      104
DECL|macro|RAW1394_REQ_ISO_LISTEN
mdefine_line|#define RAW1394_REQ_ISO_LISTEN    200
DECL|macro|RAW1394_REQ_FCP_LISTEN
mdefine_line|#define RAW1394_REQ_FCP_LISTEN    201
DECL|macro|RAW1394_REQ_RESET_BUS
mdefine_line|#define RAW1394_REQ_RESET_BUS     202
multiline_comment|/* kernel to user */
DECL|macro|RAW1394_REQ_BUS_RESET
mdefine_line|#define RAW1394_REQ_BUS_RESET     10000
DECL|macro|RAW1394_REQ_ISO_RECEIVE
mdefine_line|#define RAW1394_REQ_ISO_RECEIVE   10001
DECL|macro|RAW1394_REQ_FCP_REQUEST
mdefine_line|#define RAW1394_REQ_FCP_REQUEST   10002
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
DECL|member|fcp_buffer
id|u8
op_star
id|fcp_buffer
suffix:semicolon
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
DECL|member|tq
r_struct
id|tq_struct
id|tq
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
