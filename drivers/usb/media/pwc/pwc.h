multiline_comment|/* (C) 1999-2003 Nemosoft Unv.&n;   (C) 2004      Luc Saillard (luc@saillard.org)&n;&n;   NOTE: this version of pwc is an unofficial (modified) release of pwc &amp; pcwx&n;   driver and thus may have bugs that are not present in the original version.&n;   Please send bug reports and support requests to &lt;luc@saillard.org&gt;.&n;   The decompression routines have been implemented by reverse-engineering the&n;   Nemosoft binary pwcx module. Caveat emptor.&n;&n;   This program is free software; you can redistribute it and/or modify&n;   it under the terms of the GNU General Public License as published by&n;   the Free Software Foundation; either version 2 of the License, or&n;   (at your option) any later version.&n;&n;   This program is distributed in the hope that it will be useful,&n;   but WITHOUT ANY WARRANTY; without even the implied warranty of&n;   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;   GNU General Public License for more details.&n;&n;   You should have received a copy of the GNU General Public License&n;   along with this program; if not, write to the Free Software&n;   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n;*/
macro_line|#ifndef PWC_H
DECL|macro|PWC_H
mdefine_line|#define PWC_H
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/usb.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/videodev.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
macro_line|#include &lt;asm/errno.h&gt;
macro_line|#include &quot;pwc-uncompress.h&quot;
macro_line|#include &quot;pwc-ioctl.h&quot;
multiline_comment|/* Defines and structures for the Philips webcam */
multiline_comment|/* Used for checking memory corruption/pointer validation */
DECL|macro|PWC_MAGIC
mdefine_line|#define PWC_MAGIC 0x89DC10ABUL
DECL|macro|PWC_MAGIC
macro_line|#undef PWC_MAGIC
multiline_comment|/* Turn some debugging options on/off */
DECL|macro|PWC_DEBUG
mdefine_line|#define PWC_DEBUG 0
multiline_comment|/* Trace certain actions in the driver */
DECL|macro|TRACE_MODULE
mdefine_line|#define TRACE_MODULE&t;0x0001
DECL|macro|TRACE_PROBE
mdefine_line|#define TRACE_PROBE&t;0x0002
DECL|macro|TRACE_OPEN
mdefine_line|#define TRACE_OPEN&t;0x0004
DECL|macro|TRACE_READ
mdefine_line|#define TRACE_READ&t;0x0008
DECL|macro|TRACE_MEMORY
mdefine_line|#define TRACE_MEMORY&t;0x0010
DECL|macro|TRACE_FLOW
mdefine_line|#define TRACE_FLOW&t;0x0020
DECL|macro|TRACE_SIZE
mdefine_line|#define TRACE_SIZE&t;0x0040
DECL|macro|TRACE_PWCX
mdefine_line|#define TRACE_PWCX&t;0x0080
DECL|macro|TRACE_SEQUENCE
mdefine_line|#define TRACE_SEQUENCE&t;0x1000
DECL|macro|Trace
mdefine_line|#define Trace(R, A...) if (pwc_trace &amp; R) printk(KERN_DEBUG PWC_NAME &quot; &quot; A)
DECL|macro|Debug
mdefine_line|#define Debug(A...) printk(KERN_DEBUG PWC_NAME &quot; &quot; A)
DECL|macro|Info
mdefine_line|#define Info(A...)  printk(KERN_INFO  PWC_NAME &quot; &quot; A)
DECL|macro|Err
mdefine_line|#define Err(A...)   printk(KERN_ERR   PWC_NAME &quot; &quot; A)
multiline_comment|/* Defines for ToUCam cameras */
DECL|macro|TOUCAM_HEADER_SIZE
mdefine_line|#define TOUCAM_HEADER_SIZE&t;&t;8
DECL|macro|TOUCAM_TRAILER_SIZE
mdefine_line|#define TOUCAM_TRAILER_SIZE&t;&t;4
DECL|macro|FEATURE_MOTOR_PANTILT
mdefine_line|#define FEATURE_MOTOR_PANTILT&t;&t;0x0001
multiline_comment|/* Version block */
DECL|macro|PWC_MAJOR
mdefine_line|#define PWC_MAJOR&t;9
DECL|macro|PWC_MINOR
mdefine_line|#define PWC_MINOR&t;0
DECL|macro|PWC_VERSION
mdefine_line|#define PWC_VERSION &t;&quot;9.0.2-unofficial&quot;
DECL|macro|PWC_NAME
mdefine_line|#define PWC_NAME &t;&quot;pwc&quot;
multiline_comment|/* Turn certain features on/off */
DECL|macro|PWC_INT_PIPE
mdefine_line|#define PWC_INT_PIPE 0
multiline_comment|/* Ignore errors in the first N frames, to allow for startup delays */
DECL|macro|FRAME_LOWMARK
mdefine_line|#define FRAME_LOWMARK 5
multiline_comment|/* Size and number of buffers for the ISO pipe. */
DECL|macro|MAX_ISO_BUFS
mdefine_line|#define MAX_ISO_BUFS&t;&t;2
DECL|macro|ISO_FRAMES_PER_DESC
mdefine_line|#define ISO_FRAMES_PER_DESC&t;10
DECL|macro|ISO_MAX_FRAME_SIZE
mdefine_line|#define ISO_MAX_FRAME_SIZE&t;960
DECL|macro|ISO_BUFFER_SIZE
mdefine_line|#define ISO_BUFFER_SIZE &t;(ISO_FRAMES_PER_DESC * ISO_MAX_FRAME_SIZE)
multiline_comment|/* Frame buffers: contains compressed or uncompressed video data. */
DECL|macro|MAX_FRAMES
mdefine_line|#define MAX_FRAMES&t;&t;5
multiline_comment|/* Maximum size after decompression is 640x480 YUV data, 1.5 * 640 * 480 */
DECL|macro|PWC_FRAME_SIZE
mdefine_line|#define PWC_FRAME_SIZE &t;&t;(460800 + TOUCAM_HEADER_SIZE + TOUCAM_TRAILER_SIZE)
multiline_comment|/* Absolute maximum number of buffers available for mmap() */
DECL|macro|MAX_IMAGES
mdefine_line|#define MAX_IMAGES &t;&t;10
multiline_comment|/* The following structures were based on cpia.h. Why reinvent the wheel? :-) */
DECL|struct|pwc_iso_buf
r_struct
id|pwc_iso_buf
(brace
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
DECL|member|length
r_int
id|length
suffix:semicolon
DECL|member|read
r_int
id|read
suffix:semicolon
DECL|member|urb
r_struct
id|urb
op_star
id|urb
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* intermediate buffers with raw data from the USB cam */
DECL|struct|pwc_frame_buf
r_struct
id|pwc_frame_buf
(brace
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
DECL|member|filled
r_volatile
r_int
id|filled
suffix:semicolon
multiline_comment|/* number of bytes filled */
DECL|member|next
r_struct
id|pwc_frame_buf
op_star
id|next
suffix:semicolon
multiline_comment|/* list */
macro_line|#if PWC_DEBUG
DECL|member|sequence
r_int
id|sequence
suffix:semicolon
multiline_comment|/* Sequence number */
macro_line|#endif
)brace
suffix:semicolon
DECL|struct|pwc_device
r_struct
id|pwc_device
(brace
DECL|member|vdev
r_struct
id|video_device
op_star
id|vdev
suffix:semicolon
macro_line|#ifdef PWC_MAGIC
DECL|member|magic
r_int
id|magic
suffix:semicolon
macro_line|#endif
multiline_comment|/* Pointer to our usb_device */
DECL|member|udev
r_struct
id|usb_device
op_star
id|udev
suffix:semicolon
DECL|member|type
r_int
id|type
suffix:semicolon
multiline_comment|/* type of cam (645, 646, 675, 680, 690, 720, 730, 740, 750) */
DECL|member|release
r_int
id|release
suffix:semicolon
multiline_comment|/* release number */
DECL|member|features
r_int
id|features
suffix:semicolon
multiline_comment|/* feature bits */
DECL|member|serial
r_char
id|serial
(braket
l_int|30
)braket
suffix:semicolon
multiline_comment|/* serial number (string) */
DECL|member|error_status
r_int
id|error_status
suffix:semicolon
multiline_comment|/* set when something goes wrong with the cam (unplugged, USB errors) */
DECL|member|usb_init
r_int
id|usb_init
suffix:semicolon
multiline_comment|/* set when the cam has been initialized over USB */
multiline_comment|/*** Video data ***/
DECL|member|vopen
r_int
id|vopen
suffix:semicolon
multiline_comment|/* flag */
DECL|member|vendpoint
r_int
id|vendpoint
suffix:semicolon
multiline_comment|/* video isoc endpoint */
DECL|member|vcinterface
r_int
id|vcinterface
suffix:semicolon
multiline_comment|/* video control interface */
DECL|member|valternate
r_int
id|valternate
suffix:semicolon
multiline_comment|/* alternate interface needed */
DECL|member|vframes
DECL|member|vsize
r_int
id|vframes
comma
id|vsize
suffix:semicolon
multiline_comment|/* frames-per-second &amp; size (see PSZ_*) */
DECL|member|vpalette
r_int
id|vpalette
suffix:semicolon
multiline_comment|/* palette: 420P, RAW or RGBBAYER */
DECL|member|vframe_count
r_int
id|vframe_count
suffix:semicolon
multiline_comment|/* received frames */
DECL|member|vframes_dumped
r_int
id|vframes_dumped
suffix:semicolon
multiline_comment|/* counter for dumped frames */
DECL|member|vframes_error
r_int
id|vframes_error
suffix:semicolon
multiline_comment|/* frames received in error */
DECL|member|vmax_packet_size
r_int
id|vmax_packet_size
suffix:semicolon
multiline_comment|/* USB maxpacket size */
DECL|member|vlast_packet_size
r_int
id|vlast_packet_size
suffix:semicolon
multiline_comment|/* for frame synchronisation */
DECL|member|visoc_errors
r_int
id|visoc_errors
suffix:semicolon
multiline_comment|/* number of contiguous ISOC errors */
DECL|member|vcompression
r_int
id|vcompression
suffix:semicolon
multiline_comment|/* desired compression factor */
DECL|member|vbandlength
r_int
id|vbandlength
suffix:semicolon
multiline_comment|/* compressed band length; 0 is uncompressed */
DECL|member|vsnapshot
r_char
id|vsnapshot
suffix:semicolon
multiline_comment|/* snapshot mode */
DECL|member|vsync
r_char
id|vsync
suffix:semicolon
multiline_comment|/* used by isoc handler */
DECL|member|vmirror
r_char
id|vmirror
suffix:semicolon
multiline_comment|/* for ToUCaM series */
DECL|member|cmd_len
r_int
id|cmd_len
suffix:semicolon
DECL|member|cmd_buf
r_int
r_char
id|cmd_buf
(braket
l_int|13
)braket
suffix:semicolon
multiline_comment|/* The image acquisition requires 3 to 4 steps:&n;      1. data is gathered in short packets from the USB controller&n;      2. data is synchronized and packed into a frame buffer&n;      3a. in case data is compressed, decompress it directly into image buffer&n;      3b. in case data is uncompressed, copy into image buffer with viewport&n;      4. data is transferred to the user process&n;&n;      Note that MAX_ISO_BUFS != MAX_FRAMES != MAX_IMAGES....&n;      We have in effect a back-to-back-double-buffer system.&n;    */
multiline_comment|/* 1: isoc */
DECL|member|sbuf
r_struct
id|pwc_iso_buf
id|sbuf
(braket
id|MAX_ISO_BUFS
)braket
suffix:semicolon
DECL|member|iso_init
r_char
id|iso_init
suffix:semicolon
multiline_comment|/* 2: frame */
DECL|member|fbuf
r_struct
id|pwc_frame_buf
op_star
id|fbuf
suffix:semicolon
multiline_comment|/* all frames */
DECL|member|empty_frames
DECL|member|empty_frames_tail
r_struct
id|pwc_frame_buf
op_star
id|empty_frames
comma
op_star
id|empty_frames_tail
suffix:semicolon
multiline_comment|/* all empty frames */
DECL|member|full_frames
DECL|member|full_frames_tail
r_struct
id|pwc_frame_buf
op_star
id|full_frames
comma
op_star
id|full_frames_tail
suffix:semicolon
multiline_comment|/* all filled frames */
DECL|member|fill_frame
r_struct
id|pwc_frame_buf
op_star
id|fill_frame
suffix:semicolon
multiline_comment|/* frame currently being filled */
DECL|member|read_frame
r_struct
id|pwc_frame_buf
op_star
id|read_frame
suffix:semicolon
multiline_comment|/* frame currently read by user process */
DECL|member|frame_header_size
DECL|member|frame_trailer_size
r_int
id|frame_header_size
comma
id|frame_trailer_size
suffix:semicolon
DECL|member|frame_size
r_int
id|frame_size
suffix:semicolon
DECL|member|frame_total_size
r_int
id|frame_total_size
suffix:semicolon
multiline_comment|/* including header &amp; trailer */
DECL|member|drop_frames
r_int
id|drop_frames
suffix:semicolon
macro_line|#if PWC_DEBUG
DECL|member|sequence
r_int
id|sequence
suffix:semicolon
multiline_comment|/* Debugging aid */
macro_line|#endif
multiline_comment|/* 3: decompression */
DECL|member|decompressor
r_struct
id|pwc_decompressor
op_star
id|decompressor
suffix:semicolon
multiline_comment|/* function block with decompression routines */
DECL|member|decompress_data
r_void
op_star
id|decompress_data
suffix:semicolon
multiline_comment|/* private data for decompression engine */
multiline_comment|/* 4: image */
multiline_comment|/* We have an &squot;image&squot; and a &squot;view&squot;, where &squot;image&squot; is the fixed-size image&n;      as delivered by the camera, and &squot;view&squot; is the size requested by the&n;      program. The camera image is centered in this viewport, laced with&n;      a gray or black border. view_min &lt;= image &lt;= view &lt;= view_max;&n;    */
DECL|member|image_mask
r_int
id|image_mask
suffix:semicolon
multiline_comment|/* bitmask of supported sizes */
DECL|member|view_min
DECL|member|view_max
r_struct
id|pwc_coord
id|view_min
comma
id|view_max
suffix:semicolon
multiline_comment|/* minimum and maximum viewable sizes */
DECL|member|abs_max
r_struct
id|pwc_coord
id|abs_max
suffix:semicolon
multiline_comment|/* maximum supported size with compression */
DECL|member|image
DECL|member|view
r_struct
id|pwc_coord
id|image
comma
id|view
suffix:semicolon
multiline_comment|/* image and viewport size */
DECL|member|offset
r_struct
id|pwc_coord
id|offset
suffix:semicolon
multiline_comment|/* offset within the viewport */
DECL|member|image_data
r_void
op_star
id|image_data
suffix:semicolon
multiline_comment|/* total buffer, which is subdivided into ... */
DECL|member|image_ptr
r_void
op_star
id|image_ptr
(braket
id|MAX_IMAGES
)braket
suffix:semicolon
multiline_comment|/* ...several images... */
DECL|member|fill_image
r_int
id|fill_image
suffix:semicolon
multiline_comment|/* ...which are rotated. */
DECL|member|len_per_image
r_int
id|len_per_image
suffix:semicolon
multiline_comment|/* length per image */
DECL|member|image_read_pos
r_int
id|image_read_pos
suffix:semicolon
multiline_comment|/* In case we read data in pieces, keep track of were we are in the imagebuffer */
DECL|member|image_used
r_int
id|image_used
(braket
id|MAX_IMAGES
)braket
suffix:semicolon
multiline_comment|/* For MCAPTURE and SYNC */
DECL|member|modlock
r_struct
id|semaphore
id|modlock
suffix:semicolon
multiline_comment|/* to prevent races in video_open(), etc */
DECL|member|ptrlock
id|spinlock_t
id|ptrlock
suffix:semicolon
multiline_comment|/* for manipulating the buffer pointers */
multiline_comment|/*** motorized pan/tilt feature */
DECL|member|angle_range
r_struct
id|pwc_mpt_range
id|angle_range
suffix:semicolon
DECL|member|pan_angle
r_int
id|pan_angle
suffix:semicolon
multiline_comment|/* in degrees * 100 */
DECL|member|tilt_angle
r_int
id|tilt_angle
suffix:semicolon
multiline_comment|/* absolute angle; 0,0 is home position */
multiline_comment|/*** Misc. data ***/
DECL|member|frameq
id|wait_queue_head_t
id|frameq
suffix:semicolon
multiline_comment|/* When waiting for a frame to finish... */
macro_line|#if PWC_INT_PIPE
DECL|member|usb_int_handler
r_void
op_star
id|usb_int_handler
suffix:semicolon
multiline_comment|/* for the interrupt endpoint */
macro_line|#endif
)brace
suffix:semicolon
macro_line|#ifdef __cplusplus
r_extern
l_string|&quot;C&quot;
(brace
macro_line|#endif
multiline_comment|/* Global variables */
r_extern
r_int
id|pwc_trace
suffix:semicolon
r_extern
r_int
id|pwc_preferred_compression
suffix:semicolon
multiline_comment|/** functions in pwc-if.c */
r_int
id|pwc_try_video_mode
c_func
(paren
r_struct
id|pwc_device
op_star
id|pdev
comma
r_int
id|width
comma
r_int
id|height
comma
r_int
id|new_fps
comma
r_int
id|new_compression
comma
r_int
id|new_snapshot
)paren
suffix:semicolon
multiline_comment|/** Functions in pwc-misc.c */
multiline_comment|/* sizes in pixels */
r_extern
r_struct
id|pwc_coord
id|pwc_image_sizes
(braket
id|PSZ_MAX
)braket
suffix:semicolon
r_int
id|pwc_decode_size
c_func
(paren
r_struct
id|pwc_device
op_star
id|pdev
comma
r_int
id|width
comma
r_int
id|height
)paren
suffix:semicolon
r_void
id|pwc_construct
c_func
(paren
r_struct
id|pwc_device
op_star
id|pdev
)paren
suffix:semicolon
multiline_comment|/** Functions in pwc-ctrl.c */
multiline_comment|/* Request a certain video mode. Returns &lt; 0 if not possible */
r_extern
r_int
id|pwc_set_video_mode
c_func
(paren
r_struct
id|pwc_device
op_star
id|pdev
comma
r_int
id|width
comma
r_int
id|height
comma
r_int
id|frames
comma
r_int
id|compression
comma
r_int
id|snapshot
)paren
suffix:semicolon
multiline_comment|/* Calculate the number of bytes per image (not frame) */
r_extern
r_void
id|pwc_set_image_buffer_size
c_func
(paren
r_struct
id|pwc_device
op_star
id|pdev
)paren
suffix:semicolon
multiline_comment|/* Various controls; should be obvious. Value 0..65535, or &lt; 0 on error */
r_extern
r_int
id|pwc_get_brightness
c_func
(paren
r_struct
id|pwc_device
op_star
id|pdev
)paren
suffix:semicolon
r_extern
r_int
id|pwc_set_brightness
c_func
(paren
r_struct
id|pwc_device
op_star
id|pdev
comma
r_int
id|value
)paren
suffix:semicolon
r_extern
r_int
id|pwc_get_contrast
c_func
(paren
r_struct
id|pwc_device
op_star
id|pdev
)paren
suffix:semicolon
r_extern
r_int
id|pwc_set_contrast
c_func
(paren
r_struct
id|pwc_device
op_star
id|pdev
comma
r_int
id|value
)paren
suffix:semicolon
r_extern
r_int
id|pwc_get_gamma
c_func
(paren
r_struct
id|pwc_device
op_star
id|pdev
)paren
suffix:semicolon
r_extern
r_int
id|pwc_set_gamma
c_func
(paren
r_struct
id|pwc_device
op_star
id|pdev
comma
r_int
id|value
)paren
suffix:semicolon
r_extern
r_int
id|pwc_get_saturation
c_func
(paren
r_struct
id|pwc_device
op_star
id|pdev
)paren
suffix:semicolon
r_extern
r_int
id|pwc_set_saturation
c_func
(paren
r_struct
id|pwc_device
op_star
id|pdev
comma
r_int
id|value
)paren
suffix:semicolon
r_extern
r_int
id|pwc_set_leds
c_func
(paren
r_struct
id|pwc_device
op_star
id|pdev
comma
r_int
id|on_value
comma
r_int
id|off_value
)paren
suffix:semicolon
r_extern
r_int
id|pwc_get_leds
c_func
(paren
r_struct
id|pwc_device
op_star
id|pdev
comma
r_int
op_star
id|on_value
comma
r_int
op_star
id|off_value
)paren
suffix:semicolon
r_extern
r_int
id|pwc_get_cmos_sensor
c_func
(paren
r_struct
id|pwc_device
op_star
id|pdev
comma
r_int
op_star
id|sensor
)paren
suffix:semicolon
multiline_comment|/* Power down or up the camera; not supported by all models */
r_extern
r_int
id|pwc_camera_power
c_func
(paren
r_struct
id|pwc_device
op_star
id|pdev
comma
r_int
id|power
)paren
suffix:semicolon
multiline_comment|/* Private ioctl()s; see pwc-ioctl.h */
r_extern
r_int
id|pwc_ioctl
c_func
(paren
r_struct
id|pwc_device
op_star
id|pdev
comma
r_int
r_int
id|cmd
comma
r_void
op_star
id|arg
)paren
suffix:semicolon
multiline_comment|/** pwc-uncompress.c */
multiline_comment|/* Expand frame to image, possibly including decompression. Uses read_frame and fill_image */
r_extern
r_int
id|pwc_decompress
c_func
(paren
r_struct
id|pwc_device
op_star
id|pdev
)paren
suffix:semicolon
macro_line|#ifdef __cplusplus
)brace
macro_line|#endif
macro_line|#endif
eof
