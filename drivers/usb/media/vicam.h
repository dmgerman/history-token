multiline_comment|/*&n; *&n; * Vista Imaging ViCAM / 3Com HomeConnect Usermode Driver&n; * Christopher L Cheney (C) 2001&n; * &n; */
macro_line|#ifndef __LINUX_VICAM_H
DECL|macro|__LINUX_VICAM_H
mdefine_line|#define __LINUX_VICAM_H
macro_line|#ifdef CONFIG_USB_DEBUG
DECL|variable|debug
r_static
r_int
id|debug
op_assign
l_int|1
suffix:semicolon
macro_line|#else
DECL|variable|debug
r_static
r_int
id|debug
suffix:semicolon
macro_line|#endif
multiline_comment|/* Use our own dbg macro */
DECL|macro|dbg
macro_line|#undef dbg
DECL|macro|dbg
mdefine_line|#define dbg(format, arg...) do { if (debug) printk(KERN_DEBUG __FILE__ &quot;: &quot; format &quot;&bslash;n&quot; , ## arg); } while (0)
DECL|macro|VICAM_NUMFRAMES
mdefine_line|#define VICAM_NUMFRAMES 30
DECL|macro|VICAM_NUMSBUF
mdefine_line|#define VICAM_NUMSBUF 1
multiline_comment|/* USB REQUEST NUMBERS */
DECL|macro|VICAM_REQ_VENDOR
mdefine_line|#define VICAM_REQ_VENDOR&t;0xff
DECL|macro|VICAM_REQ_CAMERA_POWER
mdefine_line|#define VICAM_REQ_CAMERA_POWER&t;0x50
DECL|macro|VICAM_REQ_CAPTURE
mdefine_line|#define VICAM_REQ_CAPTURE&t;0x51
DECL|macro|VICAM_REQ_LED_CONTROL
mdefine_line|#define VICAM_REQ_LED_CONTROL&t;0x55
DECL|macro|VICAM_REQ_GET_SOMETHIN
mdefine_line|#define VICAM_REQ_GET_SOMETHIN&t;0x56
multiline_comment|/* not required but lets you know camera is on */
multiline_comment|/* camera must be on to turn on led */
multiline_comment|/* 0x01 always on  0x03 on when picture taken (flashes) */
DECL|struct|picture_parm
r_struct
id|picture_parm
(brace
DECL|member|width
r_int
id|width
suffix:semicolon
DECL|member|height
r_int
id|height
suffix:semicolon
DECL|member|brightness
r_int
id|brightness
suffix:semicolon
DECL|member|hue
r_int
id|hue
suffix:semicolon
DECL|member|colour
r_int
id|colour
suffix:semicolon
DECL|member|contrast
r_int
id|contrast
suffix:semicolon
DECL|member|whiteness
r_int
id|whiteness
suffix:semicolon
DECL|member|depth
r_int
id|depth
suffix:semicolon
DECL|member|palette
r_int
id|palette
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|vicam_scratch
r_struct
id|vicam_scratch
(brace
DECL|member|data
r_int
r_char
op_star
id|data
suffix:semicolon
DECL|member|state
r_volatile
r_int
id|state
suffix:semicolon
DECL|member|offset
r_int
id|offset
suffix:semicolon
DECL|member|length
r_int
id|length
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Structure to hold all of our device specific stuff */
DECL|struct|usb_vicam
r_struct
id|usb_vicam
(brace
DECL|member|vdev
r_struct
id|video_device
id|vdev
suffix:semicolon
DECL|member|udev
r_struct
id|usb_device
op_star
id|udev
suffix:semicolon
DECL|member|open_count
r_int
id|open_count
suffix:semicolon
multiline_comment|/* number of times this port has been opened */
DECL|member|sem
r_struct
id|semaphore
id|sem
suffix:semicolon
multiline_comment|/* locks this structure */
DECL|member|wait
id|wait_queue_head_t
id|wait
suffix:semicolon
multiline_comment|/* Processes waiting */
DECL|member|streaming
r_int
id|streaming
suffix:semicolon
multiline_comment|/* v4l stuff */
DECL|member|camera_name
r_char
op_star
id|camera_name
suffix:semicolon
DECL|member|fbuf
r_char
op_star
id|fbuf
suffix:semicolon
DECL|member|urb
r_struct
id|urb
op_star
id|urb
(braket
id|VICAM_NUMSBUF
)braket
suffix:semicolon
DECL|member|sizes
r_int
id|sizes
suffix:semicolon
DECL|member|width
r_int
op_star
id|width
suffix:semicolon
DECL|member|height
r_int
op_star
id|height
suffix:semicolon
DECL|member|maxframesize
r_int
id|maxframesize
suffix:semicolon
DECL|member|win
r_struct
id|picture_parm
id|win
suffix:semicolon
DECL|member|proc_entry
r_struct
id|proc_dir_entry
op_star
id|proc_entry
suffix:semicolon
multiline_comment|/* /proc/se401/videoX */
DECL|member|readurb
r_struct
id|urb
op_star
id|readurb
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
eof
