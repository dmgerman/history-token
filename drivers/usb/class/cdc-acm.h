multiline_comment|/*&n; *&n; * Includes for cdc-acm.c&n; *&n; * Mainly take from usbnet&squot;s cdc-ether part&n; *&n; */
multiline_comment|/*&n; * CMSPAR, some architectures can&squot;t have space and mark parity.&n; */
macro_line|#ifndef CMSPAR
DECL|macro|CMSPAR
mdefine_line|#define CMSPAR&t;&t;&t;0
macro_line|#endif
multiline_comment|/*&n; * Major and minor numbers.&n; */
DECL|macro|ACM_TTY_MAJOR
mdefine_line|#define ACM_TTY_MAJOR&t;&t;166
DECL|macro|ACM_TTY_MINORS
mdefine_line|#define ACM_TTY_MINORS&t;&t;32
multiline_comment|/*&n; * Requests.&n; */
DECL|macro|USB_RT_ACM
mdefine_line|#define USB_RT_ACM&t;&t;(USB_TYPE_CLASS | USB_RECIP_INTERFACE)
DECL|macro|ACM_REQ_COMMAND
mdefine_line|#define ACM_REQ_COMMAND&t;&t;0x00
DECL|macro|ACM_REQ_RESPONSE
mdefine_line|#define ACM_REQ_RESPONSE&t;0x01
DECL|macro|ACM_REQ_SET_FEATURE
mdefine_line|#define ACM_REQ_SET_FEATURE&t;0x02
DECL|macro|ACM_REQ_GET_FEATURE
mdefine_line|#define ACM_REQ_GET_FEATURE&t;0x03
DECL|macro|ACM_REQ_CLEAR_FEATURE
mdefine_line|#define ACM_REQ_CLEAR_FEATURE&t;0x04
DECL|macro|ACM_REQ_SET_LINE
mdefine_line|#define ACM_REQ_SET_LINE&t;0x20
DECL|macro|ACM_REQ_GET_LINE
mdefine_line|#define ACM_REQ_GET_LINE&t;0x21
DECL|macro|ACM_REQ_SET_CONTROL
mdefine_line|#define ACM_REQ_SET_CONTROL&t;0x22
DECL|macro|ACM_REQ_SEND_BREAK
mdefine_line|#define ACM_REQ_SEND_BREAK&t;0x23
multiline_comment|/*&n; * IRQs.&n; */
DECL|macro|ACM_IRQ_NETWORK
mdefine_line|#define ACM_IRQ_NETWORK&t;&t;0x00
DECL|macro|ACM_IRQ_LINE_STATE
mdefine_line|#define ACM_IRQ_LINE_STATE&t;0x20
multiline_comment|/*&n; * Output control lines.&n; */
DECL|macro|ACM_CTRL_DTR
mdefine_line|#define ACM_CTRL_DTR&t;&t;0x01
DECL|macro|ACM_CTRL_RTS
mdefine_line|#define ACM_CTRL_RTS&t;&t;0x02
multiline_comment|/*&n; * Input control lines and line errors.&n; */
DECL|macro|ACM_CTRL_DCD
mdefine_line|#define ACM_CTRL_DCD&t;&t;0x01
DECL|macro|ACM_CTRL_DSR
mdefine_line|#define ACM_CTRL_DSR&t;&t;0x02
DECL|macro|ACM_CTRL_BRK
mdefine_line|#define ACM_CTRL_BRK&t;&t;0x04
DECL|macro|ACM_CTRL_RI
mdefine_line|#define ACM_CTRL_RI&t;&t;0x08
DECL|macro|ACM_CTRL_FRAMING
mdefine_line|#define ACM_CTRL_FRAMING&t;0x10
DECL|macro|ACM_CTRL_PARITY
mdefine_line|#define ACM_CTRL_PARITY&t;&t;0x20
DECL|macro|ACM_CTRL_OVERRUN
mdefine_line|#define ACM_CTRL_OVERRUN&t;0x40
multiline_comment|/*&n; * Line speed and caracter encoding.&n; */
DECL|struct|acm_line
r_struct
id|acm_line
(brace
DECL|member|speed
id|__le32
id|speed
suffix:semicolon
DECL|member|stopbits
id|__u8
id|stopbits
suffix:semicolon
DECL|member|parity
id|__u8
id|parity
suffix:semicolon
DECL|member|databits
id|__u8
id|databits
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/*&n; * Internal driver structures.&n; */
DECL|struct|acm
r_struct
id|acm
(brace
DECL|member|dev
r_struct
id|usb_device
op_star
id|dev
suffix:semicolon
multiline_comment|/* the corresponding usb device */
DECL|member|control
r_struct
id|usb_interface
op_star
id|control
suffix:semicolon
multiline_comment|/* control interface */
DECL|member|data
r_struct
id|usb_interface
op_star
id|data
suffix:semicolon
multiline_comment|/* data interface */
DECL|member|tty
r_struct
id|tty_struct
op_star
id|tty
suffix:semicolon
multiline_comment|/* the corresponding tty */
DECL|member|ctrlurb
DECL|member|readurb
DECL|member|writeurb
r_struct
id|urb
op_star
id|ctrlurb
comma
op_star
id|readurb
comma
op_star
id|writeurb
suffix:semicolon
multiline_comment|/* urbs */
DECL|member|ctrl_buffer
DECL|member|read_buffer
DECL|member|write_buffer
id|u8
op_star
id|ctrl_buffer
comma
op_star
id|read_buffer
comma
op_star
id|write_buffer
suffix:semicolon
multiline_comment|/* buffers of urbs */
DECL|member|ctrl_dma
DECL|member|read_dma
DECL|member|write_dma
id|dma_addr_t
id|ctrl_dma
comma
id|read_dma
comma
id|write_dma
suffix:semicolon
multiline_comment|/* dma handles of buffers */
DECL|member|line
r_struct
id|acm_line
id|line
suffix:semicolon
multiline_comment|/* line coding (bits, stop, parity) */
DECL|member|work
r_struct
id|work_struct
id|work
suffix:semicolon
multiline_comment|/* work queue entry for line discipline waking up */
DECL|member|bh
r_struct
id|tasklet_struct
id|bh
suffix:semicolon
multiline_comment|/* rx processing */
DECL|member|throttle_lock
id|spinlock_t
id|throttle_lock
suffix:semicolon
multiline_comment|/* synchronize throtteling and read callback */
DECL|member|ctrlin
r_int
r_int
id|ctrlin
suffix:semicolon
multiline_comment|/* input control lines (DCD, DSR, RI, break, overruns) */
DECL|member|ctrlout
r_int
r_int
id|ctrlout
suffix:semicolon
multiline_comment|/* output control lines (DTR, RTS) */
DECL|member|writesize
r_int
r_int
id|writesize
suffix:semicolon
multiline_comment|/* max packet size for the output bulk endpoint */
DECL|member|readsize
DECL|member|ctrlsize
r_int
r_int
id|readsize
comma
id|ctrlsize
suffix:semicolon
multiline_comment|/* buffer sizes for freeing */
DECL|member|used
r_int
r_int
id|used
suffix:semicolon
multiline_comment|/* someone has this acm&squot;s device open */
DECL|member|minor
r_int
r_int
id|minor
suffix:semicolon
multiline_comment|/* acm minor number */
DECL|member|throttle
r_int
r_char
id|throttle
suffix:semicolon
multiline_comment|/* throttled by tty layer */
DECL|member|clocal
r_int
r_char
id|clocal
suffix:semicolon
multiline_comment|/* termios CLOCAL */
DECL|member|ready_for_write
r_int
r_char
id|ready_for_write
suffix:semicolon
multiline_comment|/* write urb can be used */
DECL|member|resubmit_to_unthrottle
r_int
r_char
id|resubmit_to_unthrottle
suffix:semicolon
multiline_comment|/* throtteling has disabled the read urb */
DECL|member|ctrl_caps
r_int
r_int
id|ctrl_caps
suffix:semicolon
multiline_comment|/* control capabilities from the class specific header */
)brace
suffix:semicolon
multiline_comment|/* &quot;Union Functional Descriptor&quot; from CDC spec 5.2.3.X */
DECL|struct|union_desc
r_struct
id|union_desc
(brace
DECL|member|bLength
id|u8
id|bLength
suffix:semicolon
DECL|member|bDescriptorType
id|u8
id|bDescriptorType
suffix:semicolon
DECL|member|bDescriptorSubType
id|u8
id|bDescriptorSubType
suffix:semicolon
DECL|member|bMasterInterface0
id|u8
id|bMasterInterface0
suffix:semicolon
DECL|member|bSlaveInterface0
id|u8
id|bSlaveInterface0
suffix:semicolon
multiline_comment|/* ... and there could be other slave interfaces */
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* class specific descriptor types */
DECL|macro|CDC_HEADER_TYPE
mdefine_line|#define CDC_HEADER_TYPE&t;&t;&t;0x00
DECL|macro|CDC_CALL_MANAGEMENT_TYPE
mdefine_line|#define CDC_CALL_MANAGEMENT_TYPE&t;0x01
DECL|macro|CDC_AC_MANAGEMENT_TYPE
mdefine_line|#define CDC_AC_MANAGEMENT_TYPE&t;&t;0x02
DECL|macro|CDC_UNION_TYPE
mdefine_line|#define CDC_UNION_TYPE&t;&t;&t;0x06
DECL|macro|CDC_COUNTRY_TYPE
mdefine_line|#define CDC_COUNTRY_TYPE&t;&t;0x07
DECL|macro|CDC_DATA_INTERFACE_TYPE
mdefine_line|#define CDC_DATA_INTERFACE_TYPE&t;0x0a
multiline_comment|/* constants describing various quirks and errors */
DECL|macro|NO_UNION_NORMAL
mdefine_line|#define NO_UNION_NORMAL&t;&t;&t;1
eof
