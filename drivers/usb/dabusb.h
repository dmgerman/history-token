DECL|macro|_BULK_DATA_LEN
mdefine_line|#define _BULK_DATA_LEN 64
r_typedef
r_struct
(brace
DECL|member|data
r_int
r_char
id|data
(braket
id|_BULK_DATA_LEN
)braket
suffix:semicolon
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
DECL|member|pipe
r_int
r_int
id|pipe
suffix:semicolon
DECL|typedef|bulk_transfer_t
DECL|typedef|pbulk_transfer_t
)brace
id|bulk_transfer_t
comma
op_star
id|pbulk_transfer_t
suffix:semicolon
DECL|macro|DABUSB_MINOR
mdefine_line|#define DABUSB_MINOR 240&t;&t;/* some unassigned USB minor */
DECL|macro|DABUSB_VERSION
mdefine_line|#define DABUSB_VERSION 0x1000
DECL|macro|IOCTL_DAB_BULK
mdefine_line|#define IOCTL_DAB_BULK              _IOWR(&squot;d&squot;, 0x30, bulk_transfer_t)
DECL|macro|IOCTL_DAB_OVERRUNS
mdefine_line|#define IOCTL_DAB_OVERRUNS&t;    _IOR(&squot;d&squot;,  0x15, int)
DECL|macro|IOCTL_DAB_VERSION
mdefine_line|#define IOCTL_DAB_VERSION           _IOR(&squot;d&squot;, 0x3f, int) 
macro_line|#ifdef __KERNEL__
DECL|enumerator|_stopped
DECL|enumerator|_started
DECL|typedef|driver_state_t
r_typedef
r_enum
(brace
id|_stopped
op_assign
l_int|0
comma
id|_started
)brace
id|driver_state_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|mutex
r_struct
id|semaphore
id|mutex
suffix:semicolon
DECL|member|usbdev
r_struct
id|usb_device
op_star
id|usbdev
suffix:semicolon
DECL|member|wait
id|wait_queue_head_t
id|wait
suffix:semicolon
DECL|member|remove_ok
id|wait_queue_head_t
id|remove_ok
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|pending_io
id|atomic_t
id|pending_io
suffix:semicolon
DECL|member|state
id|driver_state_t
id|state
suffix:semicolon
DECL|member|remove_pending
r_int
id|remove_pending
suffix:semicolon
DECL|member|got_mem
r_int
id|got_mem
suffix:semicolon
DECL|member|total_buffer_size
r_int
id|total_buffer_size
suffix:semicolon
DECL|member|overruns
r_int
r_int
id|overruns
suffix:semicolon
DECL|member|readptr
r_int
id|readptr
suffix:semicolon
DECL|member|opened
r_int
id|opened
suffix:semicolon
DECL|member|free_buff_list
r_struct
id|list_head
id|free_buff_list
suffix:semicolon
DECL|member|rec_buff_list
r_struct
id|list_head
id|rec_buff_list
suffix:semicolon
DECL|typedef|dabusb_t
DECL|typedef|pdabusb_t
)brace
id|dabusb_t
comma
op_star
id|pdabusb_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|s
id|pdabusb_t
id|s
suffix:semicolon
DECL|member|purb
id|purb_t
id|purb
suffix:semicolon
DECL|member|buff_list
r_struct
id|list_head
id|buff_list
suffix:semicolon
DECL|typedef|buff_t
DECL|typedef|pbuff_t
)brace
id|buff_t
comma
op_star
id|pbuff_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|wait
id|wait_queue_head_t
id|wait
suffix:semicolon
DECL|typedef|bulk_completion_context_t
DECL|typedef|pbulk_completion_context_t
)brace
id|bulk_completion_context_t
comma
op_star
id|pbulk_completion_context_t
suffix:semicolon
DECL|macro|_DABUSB_IF
mdefine_line|#define _DABUSB_IF 2
DECL|macro|_DABUSB_ISOPIPE
mdefine_line|#define _DABUSB_ISOPIPE 0x09
DECL|macro|_ISOPIPESIZE
mdefine_line|#define _ISOPIPESIZE&t;16384
DECL|macro|_BULK_DATA_LEN
mdefine_line|#define _BULK_DATA_LEN 64
singleline_comment|// Vendor specific request code for Anchor Upload/Download
singleline_comment|// This one is implemented in the core
DECL|macro|ANCHOR_LOAD_INTERNAL
mdefine_line|#define ANCHOR_LOAD_INTERNAL  0xA0
singleline_comment|// EZ-USB Control and Status Register.  Bit 0 controls 8051 reset
DECL|macro|CPUCS_REG
mdefine_line|#define CPUCS_REG    0x7F92
DECL|macro|_TOTAL_BUFFERS
mdefine_line|#define _TOTAL_BUFFERS 384
DECL|macro|MAX_INTEL_HEX_RECORD_LENGTH
mdefine_line|#define MAX_INTEL_HEX_RECORD_LENGTH 16
macro_line|#ifndef _BYTE_DEFINED
DECL|macro|_BYTE_DEFINED
mdefine_line|#define _BYTE_DEFINED
DECL|typedef|BYTE
r_typedef
r_int
r_char
id|BYTE
suffix:semicolon
macro_line|#endif 
singleline_comment|// !_BYTE_DEFINED
macro_line|#ifndef _WORD_DEFINED
DECL|macro|_WORD_DEFINED
mdefine_line|#define _WORD_DEFINED
DECL|typedef|WORD
r_typedef
r_int
r_int
id|WORD
suffix:semicolon
macro_line|#endif 
singleline_comment|// !_WORD_DEFINED
DECL|struct|_INTEL_HEX_RECORD
r_typedef
r_struct
id|_INTEL_HEX_RECORD
(brace
DECL|member|Length
id|BYTE
id|Length
suffix:semicolon
DECL|member|Address
id|WORD
id|Address
suffix:semicolon
DECL|member|Type
id|BYTE
id|Type
suffix:semicolon
DECL|member|Data
id|BYTE
id|Data
(braket
id|MAX_INTEL_HEX_RECORD_LENGTH
)braket
suffix:semicolon
DECL|typedef|INTEL_HEX_RECORD
DECL|typedef|PINTEL_HEX_RECORD
)brace
id|INTEL_HEX_RECORD
comma
op_star
id|PINTEL_HEX_RECORD
suffix:semicolon
macro_line|#endif
eof
