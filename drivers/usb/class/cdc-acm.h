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
id|usb_cdc_line_coding
id|line
suffix:semicolon
multiline_comment|/* bits, stop, parity */
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
DECL|macro|CDC_DATA_INTERFACE_TYPE
mdefine_line|#define CDC_DATA_INTERFACE_TYPE&t;0x0a
multiline_comment|/* constants describing various quirks and errors */
DECL|macro|NO_UNION_NORMAL
mdefine_line|#define NO_UNION_NORMAL&t;&t;&t;1
eof
