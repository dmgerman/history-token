multiline_comment|/*&n; * cpia_usb CPiA USB driver&n; *&n; * Supports CPiA based parallel port Video Camera&squot;s.&n; *&n; * Copyright (C) 1999        Jochen Scharrlach &lt;Jochen.Scharrlach@schwaben.de&gt;&n; * Copyright (C) 1999, 2000  Johannes Erdfelt &lt;johannes@erdfelt.com&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/usb.h&gt;
macro_line|#include &quot;cpia.h&quot;
DECL|macro|USB_REQ_CPIA_GRAB_FRAME
mdefine_line|#define USB_REQ_CPIA_GRAB_FRAME&t;&t;&t;0xC1
DECL|macro|USB_REQ_CPIA_UPLOAD_FRAME
mdefine_line|#define USB_REQ_CPIA_UPLOAD_FRAME&t;&t;0xC2
DECL|macro|WAIT_FOR_NEXT_FRAME
mdefine_line|#define  WAIT_FOR_NEXT_FRAME&t;&t;&t;0
DECL|macro|FORCE_FRAME_UPLOAD
mdefine_line|#define  FORCE_FRAME_UPLOAD&t;&t;&t;1
DECL|macro|FRAMES_PER_DESC
mdefine_line|#define FRAMES_PER_DESC&t;&t;10
DECL|macro|FRAME_SIZE_PER_DESC
mdefine_line|#define FRAME_SIZE_PER_DESC&t;960&t;/* Shouldn&squot;t be hardcoded */
DECL|macro|CPIA_NUMSBUF
mdefine_line|#define CPIA_NUMSBUF&t;&t;2
DECL|macro|STREAM_BUF_SIZE
mdefine_line|#define STREAM_BUF_SIZE&t;&t;(PAGE_SIZE * 4)
DECL|macro|SCRATCH_BUF_SIZE
mdefine_line|#define SCRATCH_BUF_SIZE&t;(STREAM_BUF_SIZE * 2)
DECL|struct|cpia_sbuf
r_struct
id|cpia_sbuf
(brace
DECL|member|data
r_char
op_star
id|data
suffix:semicolon
DECL|member|urb
r_struct
id|urb
op_star
id|urb
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|FRAMEBUF_LEN
mdefine_line|#define FRAMEBUF_LEN (CPIA_MAX_FRAME_SIZE+100)
DECL|enum|framebuf_status
r_enum
id|framebuf_status
(brace
DECL|enumerator|FRAME_EMPTY
id|FRAME_EMPTY
comma
DECL|enumerator|FRAME_READING
id|FRAME_READING
comma
DECL|enumerator|FRAME_READY
id|FRAME_READY
comma
DECL|enumerator|FRAME_ERROR
id|FRAME_ERROR
comma
)brace
suffix:semicolon
DECL|struct|framebuf
r_struct
id|framebuf
(brace
DECL|member|length
r_int
id|length
suffix:semicolon
DECL|member|status
r_enum
id|framebuf_status
id|status
suffix:semicolon
DECL|member|data
id|u8
id|data
(braket
id|FRAMEBUF_LEN
)braket
suffix:semicolon
DECL|member|next
r_struct
id|framebuf
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|usb_cpia
r_struct
id|usb_cpia
(brace
multiline_comment|/* Device structure */
DECL|member|dev
r_struct
id|usb_device
op_star
id|dev
suffix:semicolon
DECL|member|iface
r_int
r_char
id|iface
suffix:semicolon
DECL|member|wq_stream
id|wait_queue_head_t
id|wq_stream
suffix:semicolon
DECL|member|cursbuf
r_int
id|cursbuf
suffix:semicolon
multiline_comment|/* Current receiving sbuf */
DECL|member|sbuf
r_struct
id|cpia_sbuf
id|sbuf
(braket
id|CPIA_NUMSBUF
)braket
suffix:semicolon
multiline_comment|/* Double buffering */
DECL|member|streaming
r_int
id|streaming
suffix:semicolon
DECL|member|open
r_int
id|open
suffix:semicolon
DECL|member|present
r_int
id|present
suffix:semicolon
DECL|member|buffers
r_struct
id|framebuf
op_star
id|buffers
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|curbuff
DECL|member|workbuff
r_struct
id|framebuf
op_star
id|curbuff
comma
op_star
id|workbuff
suffix:semicolon
)brace
suffix:semicolon
r_static
r_int
id|cpia_usb_open
c_func
(paren
r_void
op_star
id|privdata
)paren
suffix:semicolon
r_static
r_int
id|cpia_usb_registerCallback
c_func
(paren
r_void
op_star
id|privdata
comma
r_void
(paren
op_star
id|cb
)paren
(paren
r_void
op_star
id|cbdata
)paren
comma
r_void
op_star
id|cbdata
)paren
suffix:semicolon
r_static
r_int
id|cpia_usb_transferCmd
c_func
(paren
r_void
op_star
id|privdata
comma
id|u8
op_star
id|command
comma
id|u8
op_star
id|data
)paren
suffix:semicolon
r_static
r_int
id|cpia_usb_streamStart
c_func
(paren
r_void
op_star
id|privdata
)paren
suffix:semicolon
r_static
r_int
id|cpia_usb_streamStop
c_func
(paren
r_void
op_star
id|privdata
)paren
suffix:semicolon
r_static
r_int
id|cpia_usb_streamRead
c_func
(paren
r_void
op_star
id|privdata
comma
id|u8
op_star
id|frame
comma
r_int
id|noblock
)paren
suffix:semicolon
r_static
r_int
id|cpia_usb_close
c_func
(paren
r_void
op_star
id|privdata
)paren
suffix:semicolon
DECL|macro|ABOUT
mdefine_line|#define ABOUT &quot;USB driver for Vision CPiA based cameras&quot;
DECL|variable|cpia_usb_ops
r_static
r_struct
id|cpia_camera_ops
id|cpia_usb_ops
op_assign
(brace
id|cpia_usb_open
comma
id|cpia_usb_registerCallback
comma
id|cpia_usb_transferCmd
comma
id|cpia_usb_streamStart
comma
id|cpia_usb_streamStop
comma
id|cpia_usb_streamRead
comma
id|cpia_usb_close
comma
l_int|0
comma
id|THIS_MODULE
)brace
suffix:semicolon
DECL|variable|cam_list
r_static
r_struct
id|cam_data
op_star
id|cam_list
suffix:semicolon
DECL|variable|cam_list_lock_usb
r_static
id|spinlock_t
id|cam_list_lock_usb
suffix:semicolon
DECL|function|cpia_usb_complete
r_static
r_void
id|cpia_usb_complete
c_func
(paren
r_struct
id|urb
op_star
id|urb
)paren
(brace
r_int
id|i
suffix:semicolon
r_char
op_star
id|cdata
suffix:semicolon
r_struct
id|usb_cpia
op_star
id|ucpia
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|urb
op_logical_or
op_logical_neg
id|urb-&gt;context
)paren
r_return
suffix:semicolon
id|ucpia
op_assign
(paren
r_struct
id|usb_cpia
op_star
)paren
id|urb-&gt;context
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ucpia-&gt;dev
op_logical_or
op_logical_neg
id|ucpia-&gt;streaming
op_logical_or
op_logical_neg
id|ucpia-&gt;present
op_logical_or
op_logical_neg
id|ucpia-&gt;open
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|ucpia-&gt;workbuff-&gt;status
op_eq
id|FRAME_EMPTY
)paren
(brace
id|ucpia-&gt;workbuff-&gt;status
op_assign
id|FRAME_READING
suffix:semicolon
id|ucpia-&gt;workbuff-&gt;length
op_assign
l_int|0
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|urb-&gt;number_of_packets
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
id|n
op_assign
id|urb-&gt;iso_frame_desc
(braket
id|i
)braket
dot
id|actual_length
suffix:semicolon
r_int
id|st
op_assign
id|urb-&gt;iso_frame_desc
(braket
id|i
)braket
dot
id|status
suffix:semicolon
id|cdata
op_assign
id|urb-&gt;transfer_buffer
op_plus
id|urb-&gt;iso_frame_desc
(braket
id|i
)braket
dot
id|offset
suffix:semicolon
r_if
c_cond
(paren
id|st
)paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;cpia data error: [%d] len=%d, status=%X&bslash;n&quot;
comma
id|i
comma
id|n
comma
id|st
)paren
suffix:semicolon
r_if
c_cond
(paren
id|FRAMEBUF_LEN
OL
id|ucpia-&gt;workbuff-&gt;length
op_plus
id|n
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;cpia: scratch buf overflow!scr_len: %d, n: %d&bslash;n&quot;
comma
id|ucpia-&gt;workbuff-&gt;length
comma
id|n
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|n
)paren
(brace
r_if
c_cond
(paren
(paren
id|ucpia-&gt;workbuff-&gt;length
OG
l_int|0
)paren
op_logical_or
(paren
l_int|0x19
op_eq
id|cdata
(braket
l_int|0
)braket
op_logical_and
l_int|0x68
op_eq
id|cdata
(braket
l_int|1
)braket
)paren
)paren
(brace
id|memcpy
c_func
(paren
id|ucpia-&gt;workbuff-&gt;data
op_plus
id|ucpia-&gt;workbuff-&gt;length
comma
id|cdata
comma
id|n
)paren
suffix:semicolon
id|ucpia-&gt;workbuff-&gt;length
op_add_assign
id|n
suffix:semicolon
)brace
r_else
id|DBG
c_func
(paren
l_string|&quot;Ignoring packet!&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|ucpia-&gt;workbuff-&gt;length
OG
l_int|4
op_logical_and
l_int|0xff
op_eq
id|ucpia-&gt;workbuff-&gt;data
(braket
id|ucpia-&gt;workbuff-&gt;length
op_minus
l_int|1
)braket
op_logical_and
l_int|0xff
op_eq
id|ucpia-&gt;workbuff-&gt;data
(braket
id|ucpia-&gt;workbuff-&gt;length
op_minus
l_int|2
)braket
op_logical_and
l_int|0xff
op_eq
id|ucpia-&gt;workbuff-&gt;data
(braket
id|ucpia-&gt;workbuff-&gt;length
op_minus
l_int|3
)braket
op_logical_and
l_int|0xff
op_eq
id|ucpia-&gt;workbuff-&gt;data
(braket
id|ucpia-&gt;workbuff-&gt;length
op_minus
l_int|4
)braket
)paren
(brace
id|ucpia-&gt;workbuff-&gt;status
op_assign
id|FRAME_READY
suffix:semicolon
id|ucpia-&gt;curbuff
op_assign
id|ucpia-&gt;workbuff
suffix:semicolon
id|ucpia-&gt;workbuff
op_assign
id|ucpia-&gt;workbuff-&gt;next
suffix:semicolon
id|ucpia-&gt;workbuff-&gt;status
op_assign
id|FRAME_EMPTY
suffix:semicolon
id|ucpia-&gt;workbuff-&gt;length
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|waitqueue_active
c_func
(paren
op_amp
id|ucpia-&gt;wq_stream
)paren
)paren
id|wake_up_interruptible
c_func
(paren
op_amp
id|ucpia-&gt;wq_stream
)paren
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/* resubmit */
id|urb-&gt;dev
op_assign
id|ucpia-&gt;dev
suffix:semicolon
r_if
c_cond
(paren
(paren
id|i
op_assign
id|usb_submit_urb
c_func
(paren
id|urb
comma
id|GFP_ATOMIC
)paren
)paren
op_ne
l_int|0
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: usb_submit_urb ret %d&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|i
)paren
suffix:semicolon
)brace
DECL|function|cpia_usb_open
r_static
r_int
id|cpia_usb_open
c_func
(paren
r_void
op_star
id|privdata
)paren
(brace
r_struct
id|usb_cpia
op_star
id|ucpia
op_assign
(paren
r_struct
id|usb_cpia
op_star
)paren
id|privdata
suffix:semicolon
r_struct
id|urb
op_star
id|urb
suffix:semicolon
r_int
id|ret
comma
id|retval
op_assign
l_int|0
comma
id|fx
comma
id|err
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ucpia
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|ucpia-&gt;sbuf
(braket
l_int|0
)braket
dot
id|data
op_assign
id|kmalloc
c_func
(paren
id|FRAMES_PER_DESC
op_star
id|FRAME_SIZE_PER_DESC
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ucpia-&gt;sbuf
(braket
l_int|0
)braket
dot
id|data
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|ucpia-&gt;sbuf
(braket
l_int|1
)braket
dot
id|data
op_assign
id|kmalloc
c_func
(paren
id|FRAMES_PER_DESC
op_star
id|FRAME_SIZE_PER_DESC
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ucpia-&gt;sbuf
(braket
l_int|1
)braket
dot
id|data
)paren
(brace
id|retval
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|error_0
suffix:semicolon
)brace
id|ret
op_assign
id|usb_set_interface
c_func
(paren
id|ucpia-&gt;dev
comma
id|ucpia-&gt;iface
comma
l_int|3
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;cpia_usb_open: usb_set_interface error (ret = %d)&bslash;n&quot;
comma
id|ret
)paren
suffix:semicolon
id|retval
op_assign
op_minus
id|EBUSY
suffix:semicolon
r_goto
id|error_1
suffix:semicolon
)brace
id|ucpia-&gt;buffers
(braket
l_int|0
)braket
op_member_access_from_pointer
id|status
op_assign
id|FRAME_EMPTY
suffix:semicolon
id|ucpia-&gt;buffers
(braket
l_int|0
)braket
op_member_access_from_pointer
id|length
op_assign
l_int|0
suffix:semicolon
id|ucpia-&gt;buffers
(braket
l_int|1
)braket
op_member_access_from_pointer
id|status
op_assign
id|FRAME_EMPTY
suffix:semicolon
id|ucpia-&gt;buffers
(braket
l_int|1
)braket
op_member_access_from_pointer
id|length
op_assign
l_int|0
suffix:semicolon
id|ucpia-&gt;buffers
(braket
l_int|2
)braket
op_member_access_from_pointer
id|status
op_assign
id|FRAME_EMPTY
suffix:semicolon
id|ucpia-&gt;buffers
(braket
l_int|2
)braket
op_member_access_from_pointer
id|length
op_assign
l_int|0
suffix:semicolon
id|ucpia-&gt;curbuff
op_assign
id|ucpia-&gt;buffers
(braket
l_int|0
)braket
suffix:semicolon
id|ucpia-&gt;workbuff
op_assign
id|ucpia-&gt;buffers
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* We double buffer the Iso lists, and also know the polling&n;&t; * interval is every frame (1 == (1 &lt;&lt; (bInterval -1))).&n;&t; */
id|urb
op_assign
id|usb_alloc_urb
c_func
(paren
id|FRAMES_PER_DESC
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|urb
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;cpia_init_isoc: usb_alloc_urb 0&bslash;n&quot;
)paren
suffix:semicolon
id|retval
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|error_1
suffix:semicolon
)brace
id|ucpia-&gt;sbuf
(braket
l_int|0
)braket
dot
id|urb
op_assign
id|urb
suffix:semicolon
id|urb-&gt;dev
op_assign
id|ucpia-&gt;dev
suffix:semicolon
id|urb-&gt;context
op_assign
id|ucpia
suffix:semicolon
id|urb-&gt;pipe
op_assign
id|usb_rcvisocpipe
c_func
(paren
id|ucpia-&gt;dev
comma
l_int|1
)paren
suffix:semicolon
id|urb-&gt;transfer_flags
op_assign
id|USB_ISO_ASAP
suffix:semicolon
id|urb-&gt;transfer_buffer
op_assign
id|ucpia-&gt;sbuf
(braket
l_int|0
)braket
dot
id|data
suffix:semicolon
id|urb-&gt;complete
op_assign
id|cpia_usb_complete
suffix:semicolon
id|urb-&gt;number_of_packets
op_assign
id|FRAMES_PER_DESC
suffix:semicolon
id|urb-&gt;interval
op_assign
l_int|1
suffix:semicolon
id|urb-&gt;transfer_buffer_length
op_assign
id|FRAME_SIZE_PER_DESC
op_star
id|FRAMES_PER_DESC
suffix:semicolon
r_for
c_loop
(paren
id|fx
op_assign
l_int|0
suffix:semicolon
id|fx
OL
id|FRAMES_PER_DESC
suffix:semicolon
id|fx
op_increment
)paren
(brace
id|urb-&gt;iso_frame_desc
(braket
id|fx
)braket
dot
id|offset
op_assign
id|FRAME_SIZE_PER_DESC
op_star
id|fx
suffix:semicolon
id|urb-&gt;iso_frame_desc
(braket
id|fx
)braket
dot
id|length
op_assign
id|FRAME_SIZE_PER_DESC
suffix:semicolon
)brace
id|urb
op_assign
id|usb_alloc_urb
c_func
(paren
id|FRAMES_PER_DESC
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|urb
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;cpia_init_isoc: usb_alloc_urb 1&bslash;n&quot;
)paren
suffix:semicolon
id|retval
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|error_urb0
suffix:semicolon
)brace
id|ucpia-&gt;sbuf
(braket
l_int|1
)braket
dot
id|urb
op_assign
id|urb
suffix:semicolon
id|urb-&gt;dev
op_assign
id|ucpia-&gt;dev
suffix:semicolon
id|urb-&gt;context
op_assign
id|ucpia
suffix:semicolon
id|urb-&gt;pipe
op_assign
id|usb_rcvisocpipe
c_func
(paren
id|ucpia-&gt;dev
comma
l_int|1
)paren
suffix:semicolon
id|urb-&gt;transfer_flags
op_assign
id|USB_ISO_ASAP
suffix:semicolon
id|urb-&gt;transfer_buffer
op_assign
id|ucpia-&gt;sbuf
(braket
l_int|1
)braket
dot
id|data
suffix:semicolon
id|urb-&gt;complete
op_assign
id|cpia_usb_complete
suffix:semicolon
id|urb-&gt;number_of_packets
op_assign
id|FRAMES_PER_DESC
suffix:semicolon
id|urb-&gt;interval
op_assign
l_int|1
suffix:semicolon
id|urb-&gt;transfer_buffer_length
op_assign
id|FRAME_SIZE_PER_DESC
op_star
id|FRAMES_PER_DESC
suffix:semicolon
r_for
c_loop
(paren
id|fx
op_assign
l_int|0
suffix:semicolon
id|fx
OL
id|FRAMES_PER_DESC
suffix:semicolon
id|fx
op_increment
)paren
(brace
id|urb-&gt;iso_frame_desc
(braket
id|fx
)braket
dot
id|offset
op_assign
id|FRAME_SIZE_PER_DESC
op_star
id|fx
suffix:semicolon
id|urb-&gt;iso_frame_desc
(braket
id|fx
)braket
dot
id|length
op_assign
id|FRAME_SIZE_PER_DESC
suffix:semicolon
)brace
multiline_comment|/* queue the ISO urbs, and resubmit in the completion handler */
id|err
op_assign
id|usb_submit_urb
c_func
(paren
id|ucpia-&gt;sbuf
(braket
l_int|0
)braket
dot
id|urb
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;cpia_init_isoc: usb_submit_urb 0 ret %d&bslash;n&quot;
comma
id|err
)paren
suffix:semicolon
r_goto
id|error_urb1
suffix:semicolon
)brace
id|err
op_assign
id|usb_submit_urb
c_func
(paren
id|ucpia-&gt;sbuf
(braket
l_int|1
)braket
dot
id|urb
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;cpia_init_isoc: usb_submit_urb 1 ret %d&bslash;n&quot;
comma
id|err
)paren
suffix:semicolon
r_goto
id|error_urb1
suffix:semicolon
)brace
id|ucpia-&gt;streaming
op_assign
l_int|1
suffix:semicolon
id|ucpia-&gt;open
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|error_urb1
suffix:colon
multiline_comment|/* free urb 1 */
id|usb_free_urb
c_func
(paren
id|ucpia-&gt;sbuf
(braket
l_int|1
)braket
dot
id|urb
)paren
suffix:semicolon
id|ucpia-&gt;sbuf
(braket
l_int|1
)braket
dot
id|urb
op_assign
l_int|NULL
suffix:semicolon
id|error_urb0
suffix:colon
multiline_comment|/* free urb 0 */
id|usb_free_urb
c_func
(paren
id|ucpia-&gt;sbuf
(braket
l_int|0
)braket
dot
id|urb
)paren
suffix:semicolon
id|ucpia-&gt;sbuf
(braket
l_int|0
)braket
dot
id|urb
op_assign
l_int|NULL
suffix:semicolon
id|error_1
suffix:colon
id|kfree
(paren
id|ucpia-&gt;sbuf
(braket
l_int|1
)braket
dot
id|data
)paren
suffix:semicolon
id|ucpia-&gt;sbuf
(braket
l_int|1
)braket
dot
id|data
op_assign
l_int|NULL
suffix:semicolon
id|error_0
suffix:colon
id|kfree
(paren
id|ucpia-&gt;sbuf
(braket
l_int|0
)braket
dot
id|data
)paren
suffix:semicolon
id|ucpia-&gt;sbuf
(braket
l_int|0
)braket
dot
id|data
op_assign
l_int|NULL
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
singleline_comment|//
singleline_comment|// convenience functions
singleline_comment|//
multiline_comment|/****************************************************************************&n; *&n; *  WritePacket&n; *&n; ***************************************************************************/
DECL|function|WritePacket
r_static
r_int
id|WritePacket
c_func
(paren
r_struct
id|usb_device
op_star
id|udev
comma
r_const
id|u8
op_star
id|packet
comma
id|u8
op_star
id|buf
comma
r_int
id|size
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|packet
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
id|usb_control_msg
c_func
(paren
id|udev
comma
id|usb_sndctrlpipe
c_func
(paren
id|udev
comma
l_int|0
)paren
comma
id|packet
(braket
l_int|1
)braket
op_plus
(paren
id|packet
(braket
l_int|0
)braket
op_lshift
l_int|8
)paren
comma
id|USB_TYPE_VENDOR
op_or
id|USB_RECIP_DEVICE
comma
id|packet
(braket
l_int|2
)braket
op_plus
(paren
id|packet
(braket
l_int|3
)braket
op_lshift
l_int|8
)paren
comma
id|packet
(braket
l_int|4
)braket
op_plus
(paren
id|packet
(braket
l_int|5
)braket
op_lshift
l_int|8
)paren
comma
id|buf
comma
id|size
comma
id|HZ
)paren
suffix:semicolon
)brace
multiline_comment|/****************************************************************************&n; *&n; *  ReadPacket&n; *&n; ***************************************************************************/
DECL|function|ReadPacket
r_static
r_int
id|ReadPacket
c_func
(paren
r_struct
id|usb_device
op_star
id|udev
comma
id|u8
op_star
id|packet
comma
id|u8
op_star
id|buf
comma
r_int
id|size
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|packet
op_logical_or
id|size
op_le
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
id|usb_control_msg
c_func
(paren
id|udev
comma
id|usb_rcvctrlpipe
c_func
(paren
id|udev
comma
l_int|0
)paren
comma
id|packet
(braket
l_int|1
)braket
op_plus
(paren
id|packet
(braket
l_int|0
)braket
op_lshift
l_int|8
)paren
comma
id|USB_DIR_IN
op_or
id|USB_TYPE_VENDOR
op_or
id|USB_RECIP_DEVICE
comma
id|packet
(braket
l_int|2
)braket
op_plus
(paren
id|packet
(braket
l_int|3
)braket
op_lshift
l_int|8
)paren
comma
id|packet
(braket
l_int|4
)braket
op_plus
(paren
id|packet
(braket
l_int|5
)braket
op_lshift
l_int|8
)paren
comma
id|buf
comma
id|size
comma
id|HZ
)paren
suffix:semicolon
)brace
DECL|function|cpia_usb_transferCmd
r_static
r_int
id|cpia_usb_transferCmd
c_func
(paren
r_void
op_star
id|privdata
comma
id|u8
op_star
id|command
comma
id|u8
op_star
id|data
)paren
(brace
r_int
id|err
op_assign
l_int|0
suffix:semicolon
r_int
id|databytes
suffix:semicolon
r_struct
id|usb_cpia
op_star
id|ucpia
op_assign
(paren
r_struct
id|usb_cpia
op_star
)paren
id|privdata
suffix:semicolon
r_struct
id|usb_device
op_star
id|udev
op_assign
id|ucpia-&gt;dev
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|udev
)paren
(brace
id|DBG
c_func
(paren
l_string|&quot;Internal driver error: udev is NULL&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|command
)paren
(brace
id|DBG
c_func
(paren
l_string|&quot;Internal driver error: command is NULL&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|databytes
op_assign
(paren
(paren
(paren
r_int
)paren
id|command
(braket
l_int|7
)braket
)paren
op_lshift
l_int|8
)paren
op_or
id|command
(braket
l_int|6
)braket
suffix:semicolon
r_if
c_cond
(paren
id|command
(braket
l_int|0
)braket
op_eq
id|DATA_IN
)paren
(brace
id|u8
id|buffer
(braket
l_int|8
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|data
)paren
(brace
id|DBG
c_func
(paren
l_string|&quot;Internal driver error: data is NULL&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|err
op_assign
id|ReadPacket
c_func
(paren
id|udev
comma
id|command
comma
id|buffer
comma
l_int|8
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
id|memcpy
c_func
(paren
id|data
comma
id|buffer
comma
id|databytes
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|command
(braket
l_int|0
)braket
op_eq
id|DATA_OUT
)paren
(brace
id|WritePacket
c_func
(paren
id|udev
comma
id|command
comma
id|data
comma
id|databytes
)paren
suffix:semicolon
)brace
r_else
(brace
id|DBG
c_func
(paren
l_string|&quot;Unexpected first byte of command: %x&bslash;n&quot;
comma
id|command
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cpia_usb_registerCallback
r_static
r_int
id|cpia_usb_registerCallback
c_func
(paren
r_void
op_star
id|privdata
comma
r_void
(paren
op_star
id|cb
)paren
(paren
r_void
op_star
id|cbdata
)paren
comma
r_void
op_star
id|cbdata
)paren
(brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
DECL|function|cpia_usb_streamStart
r_static
r_int
id|cpia_usb_streamStart
c_func
(paren
r_void
op_star
id|privdata
)paren
(brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
DECL|function|cpia_usb_streamStop
r_static
r_int
id|cpia_usb_streamStop
c_func
(paren
r_void
op_star
id|privdata
)paren
(brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
DECL|function|cpia_usb_streamRead
r_static
r_int
id|cpia_usb_streamRead
c_func
(paren
r_void
op_star
id|privdata
comma
id|u8
op_star
id|frame
comma
r_int
id|noblock
)paren
(brace
r_struct
id|usb_cpia
op_star
id|ucpia
op_assign
(paren
r_struct
id|usb_cpia
op_star
)paren
id|privdata
suffix:semicolon
r_struct
id|framebuf
op_star
id|mybuff
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ucpia
op_logical_or
op_logical_neg
id|ucpia-&gt;present
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|ucpia-&gt;curbuff-&gt;status
op_ne
id|FRAME_READY
)paren
id|interruptible_sleep_on
c_func
(paren
op_amp
id|ucpia-&gt;wq_stream
)paren
suffix:semicolon
r_else
id|DBG
c_func
(paren
l_string|&quot;Frame already waiting!&bslash;n&quot;
)paren
suffix:semicolon
id|mybuff
op_assign
id|ucpia-&gt;curbuff
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mybuff
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|mybuff-&gt;status
op_ne
id|FRAME_READY
op_logical_or
id|mybuff-&gt;length
OL
l_int|4
)paren
(brace
id|DBG
c_func
(paren
l_string|&quot;Something went wrong!&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|memcpy
c_func
(paren
id|frame
comma
id|mybuff-&gt;data
comma
id|mybuff-&gt;length
)paren
suffix:semicolon
id|mybuff-&gt;status
op_assign
id|FRAME_EMPTY
suffix:semicolon
multiline_comment|/*   DBG(&quot;read done, %d bytes, Header: %x/%x, Footer: %x%x%x%x&bslash;n&quot;,  */
multiline_comment|/*       mybuff-&gt;length, frame[0], frame[1], */
multiline_comment|/*       frame[mybuff-&gt;length-4], frame[mybuff-&gt;length-3],  */
multiline_comment|/*       frame[mybuff-&gt;length-2], frame[mybuff-&gt;length-1]); */
r_return
id|mybuff-&gt;length
suffix:semicolon
)brace
DECL|function|cpia_usb_free_resources
r_static
r_void
id|cpia_usb_free_resources
c_func
(paren
r_struct
id|usb_cpia
op_star
id|ucpia
comma
r_int
r_try
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|ucpia-&gt;streaming
)paren
r_return
suffix:semicolon
id|ucpia-&gt;streaming
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Set packet size to 0 */
r_if
c_cond
(paren
r_try
)paren
(brace
r_int
id|ret
suffix:semicolon
id|ret
op_assign
id|usb_set_interface
c_func
(paren
id|ucpia-&gt;dev
comma
id|ucpia-&gt;iface
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;usb_set_interface error (ret = %d)&bslash;n&quot;
comma
id|ret
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
multiline_comment|/* Unschedule all of the iso td&squot;s */
r_if
c_cond
(paren
id|ucpia-&gt;sbuf
(braket
l_int|1
)braket
dot
id|urb
)paren
(brace
id|usb_unlink_urb
c_func
(paren
id|ucpia-&gt;sbuf
(braket
l_int|1
)braket
dot
id|urb
)paren
suffix:semicolon
id|usb_free_urb
c_func
(paren
id|ucpia-&gt;sbuf
(braket
l_int|1
)braket
dot
id|urb
)paren
suffix:semicolon
id|ucpia-&gt;sbuf
(braket
l_int|1
)braket
dot
id|urb
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ucpia-&gt;sbuf
(braket
l_int|1
)braket
dot
id|data
)paren
(brace
id|kfree
c_func
(paren
id|ucpia-&gt;sbuf
(braket
l_int|1
)braket
dot
id|data
)paren
suffix:semicolon
id|ucpia-&gt;sbuf
(braket
l_int|1
)braket
dot
id|data
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ucpia-&gt;sbuf
(braket
l_int|0
)braket
dot
id|urb
)paren
(brace
id|usb_unlink_urb
c_func
(paren
id|ucpia-&gt;sbuf
(braket
l_int|0
)braket
dot
id|urb
)paren
suffix:semicolon
id|usb_free_urb
c_func
(paren
id|ucpia-&gt;sbuf
(braket
l_int|0
)braket
dot
id|urb
)paren
suffix:semicolon
id|ucpia-&gt;sbuf
(braket
l_int|0
)braket
dot
id|urb
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ucpia-&gt;sbuf
(braket
l_int|0
)braket
dot
id|data
)paren
(brace
id|kfree
c_func
(paren
id|ucpia-&gt;sbuf
(braket
l_int|0
)braket
dot
id|data
)paren
suffix:semicolon
id|ucpia-&gt;sbuf
(braket
l_int|0
)braket
dot
id|data
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
DECL|function|cpia_usb_close
r_static
r_int
id|cpia_usb_close
c_func
(paren
r_void
op_star
id|privdata
)paren
(brace
r_struct
id|usb_cpia
op_star
id|ucpia
op_assign
(paren
r_struct
id|usb_cpia
op_star
)paren
id|privdata
suffix:semicolon
id|ucpia-&gt;open
op_assign
l_int|0
suffix:semicolon
id|cpia_usb_free_resources
c_func
(paren
id|ucpia
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ucpia-&gt;present
)paren
id|kfree
c_func
(paren
id|ucpia
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cpia_usb_init
r_int
id|cpia_usb_init
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* return -ENODEV; */
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Probing and initializing */
DECL|function|cpia_probe
r_static
r_int
id|cpia_probe
c_func
(paren
r_struct
id|usb_interface
op_star
id|intf
comma
r_const
r_struct
id|usb_device_id
op_star
id|id
)paren
(brace
r_struct
id|usb_device
op_star
id|udev
op_assign
id|interface_to_usbdev
c_func
(paren
id|intf
)paren
suffix:semicolon
r_struct
id|usb_interface_descriptor
op_star
id|interface
suffix:semicolon
r_struct
id|usb_cpia
op_star
id|ucpia
suffix:semicolon
r_struct
id|cam_data
op_star
id|cam
suffix:semicolon
r_int
id|ret
suffix:semicolon
multiline_comment|/* A multi-config CPiA camera? */
r_if
c_cond
(paren
id|udev-&gt;descriptor.bNumConfigurations
op_ne
l_int|1
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|interface
op_assign
op_amp
id|intf-&gt;altsetting
(braket
l_int|0
)braket
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;USB CPiA camera found&bslash;n&quot;
)paren
suffix:semicolon
id|ucpia
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|ucpia
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ucpia
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;couldn&squot;t kmalloc cpia struct&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|memset
c_func
(paren
id|ucpia
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|ucpia
)paren
)paren
suffix:semicolon
id|ucpia-&gt;dev
op_assign
id|udev
suffix:semicolon
id|ucpia-&gt;iface
op_assign
id|interface-&gt;bInterfaceNumber
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|ucpia-&gt;wq_stream
)paren
suffix:semicolon
id|ucpia-&gt;buffers
(braket
l_int|0
)braket
op_assign
id|vmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|ucpia-&gt;buffers
(braket
l_int|0
)braket
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ucpia-&gt;buffers
(braket
l_int|0
)braket
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;couldn&squot;t vmalloc frame buffer 0&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|fail_alloc_0
suffix:semicolon
)brace
id|ucpia-&gt;buffers
(braket
l_int|1
)braket
op_assign
id|vmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|ucpia-&gt;buffers
(braket
l_int|1
)braket
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ucpia-&gt;buffers
(braket
l_int|1
)braket
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;couldn&squot;t vmalloc frame buffer 1&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|fail_alloc_1
suffix:semicolon
)brace
id|ucpia-&gt;buffers
(braket
l_int|2
)braket
op_assign
id|vmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|ucpia-&gt;buffers
(braket
l_int|2
)braket
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ucpia-&gt;buffers
(braket
l_int|2
)braket
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;couldn&squot;t vmalloc frame buffer 2&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|fail_alloc_2
suffix:semicolon
)brace
id|ucpia-&gt;buffers
(braket
l_int|0
)braket
op_member_access_from_pointer
id|next
op_assign
id|ucpia-&gt;buffers
(braket
l_int|1
)braket
suffix:semicolon
id|ucpia-&gt;buffers
(braket
l_int|1
)braket
op_member_access_from_pointer
id|next
op_assign
id|ucpia-&gt;buffers
(braket
l_int|2
)braket
suffix:semicolon
id|ucpia-&gt;buffers
(braket
l_int|2
)braket
op_member_access_from_pointer
id|next
op_assign
id|ucpia-&gt;buffers
(braket
l_int|0
)braket
suffix:semicolon
id|ret
op_assign
id|usb_set_interface
c_func
(paren
id|udev
comma
id|ucpia-&gt;iface
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;cpia_probe: usb_set_interface error (ret = %d)&bslash;n&quot;
comma
id|ret
)paren
suffix:semicolon
multiline_comment|/* goto fail_all; */
)brace
multiline_comment|/* Before register_camera, important */
id|ucpia-&gt;present
op_assign
l_int|1
suffix:semicolon
id|cam
op_assign
id|cpia_register_camera
c_func
(paren
op_amp
id|cpia_usb_ops
comma
id|ucpia
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cam
)paren
(brace
id|LOG
c_func
(paren
l_string|&quot;failed to cpia_register_camera&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|fail_all
suffix:semicolon
)brace
id|spin_lock
c_func
(paren
op_amp
id|cam_list_lock_usb
)paren
suffix:semicolon
id|cpia_add_to_list
c_func
(paren
op_amp
id|cam_list
comma
op_amp
id|cam
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|cam_list_lock_usb
)paren
suffix:semicolon
id|dev_set_drvdata
c_func
(paren
op_amp
id|intf-&gt;dev
comma
id|cam
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|fail_all
suffix:colon
id|vfree
c_func
(paren
id|ucpia-&gt;buffers
(braket
l_int|2
)braket
)paren
suffix:semicolon
id|ucpia-&gt;buffers
(braket
l_int|2
)braket
op_assign
l_int|NULL
suffix:semicolon
id|fail_alloc_2
suffix:colon
id|vfree
c_func
(paren
id|ucpia-&gt;buffers
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|ucpia-&gt;buffers
(braket
l_int|1
)braket
op_assign
l_int|NULL
suffix:semicolon
id|fail_alloc_1
suffix:colon
id|vfree
c_func
(paren
id|ucpia-&gt;buffers
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|ucpia-&gt;buffers
(braket
l_int|0
)braket
op_assign
l_int|NULL
suffix:semicolon
id|fail_alloc_0
suffix:colon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_static
r_void
id|cpia_disconnect
c_func
(paren
r_struct
id|usb_interface
op_star
id|intf
)paren
suffix:semicolon
DECL|variable|cpia_id_table
r_static
r_struct
id|usb_device_id
id|cpia_id_table
(braket
)braket
op_assign
(brace
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x0553
comma
l_int|0x0002
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x0813
comma
l_int|0x0001
)paren
)brace
comma
(brace
)brace
multiline_comment|/* Terminating entry */
)brace
suffix:semicolon
id|MODULE_DEVICE_TABLE
(paren
id|usb
comma
id|cpia_id_table
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|cpia_driver
r_static
r_struct
id|usb_driver
id|cpia_driver
op_assign
(brace
id|name
suffix:colon
l_string|&quot;cpia&quot;
comma
id|probe
suffix:colon
id|cpia_probe
comma
id|disconnect
suffix:colon
id|cpia_disconnect
comma
id|id_table
suffix:colon
id|cpia_id_table
comma
)brace
suffix:semicolon
multiline_comment|/* don&squot;t use dev, it may be NULL! (see usb_cpia_cleanup) */
multiline_comment|/* _disconnect from usb_cpia_cleanup is not necessary since usb_deregister */
multiline_comment|/* will do it for us as well as passing a udev structure - jerdfelt */
DECL|function|cpia_disconnect
r_static
r_void
id|cpia_disconnect
c_func
(paren
r_struct
id|usb_interface
op_star
id|intf
)paren
(brace
r_struct
id|cam_data
op_star
id|cam
op_assign
id|dev_get_drvdata
c_func
(paren
op_amp
id|intf-&gt;dev
)paren
suffix:semicolon
r_struct
id|usb_cpia
op_star
id|ucpia
suffix:semicolon
r_struct
id|usb_device
op_star
id|udev
suffix:semicolon
id|dev_set_drvdata
c_func
(paren
op_amp
id|intf-&gt;dev
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cam
)paren
r_return
suffix:semicolon
id|ucpia
op_assign
(paren
r_struct
id|usb_cpia
op_star
)paren
id|cam-&gt;lowlevel_data
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|cam_list_lock_usb
)paren
suffix:semicolon
id|cpia_remove_from_list
c_func
(paren
op_amp
id|cam
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|cam_list_lock_usb
)paren
suffix:semicolon
multiline_comment|/* Don&squot;t even try to reset the altsetting if we&squot;re disconnected */
id|cpia_usb_free_resources
c_func
(paren
id|ucpia
comma
l_int|0
)paren
suffix:semicolon
id|ucpia-&gt;present
op_assign
l_int|0
suffix:semicolon
id|cpia_unregister_camera
c_func
(paren
id|cam
)paren
suffix:semicolon
id|ucpia-&gt;curbuff-&gt;status
op_assign
id|FRAME_ERROR
suffix:semicolon
r_if
c_cond
(paren
id|waitqueue_active
c_func
(paren
op_amp
id|ucpia-&gt;wq_stream
)paren
)paren
id|wake_up_interruptible
c_func
(paren
op_amp
id|ucpia-&gt;wq_stream
)paren
suffix:semicolon
id|udev
op_assign
id|interface_to_usbdev
c_func
(paren
id|intf
)paren
suffix:semicolon
id|usb_driver_release_interface
c_func
(paren
op_amp
id|cpia_driver
comma
op_amp
id|udev-&gt;actconfig-&gt;interface
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|ucpia-&gt;curbuff
op_assign
id|ucpia-&gt;workbuff
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|ucpia-&gt;buffers
(braket
l_int|2
)braket
)paren
(brace
id|vfree
c_func
(paren
id|ucpia-&gt;buffers
(braket
l_int|2
)braket
)paren
suffix:semicolon
id|ucpia-&gt;buffers
(braket
l_int|2
)braket
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ucpia-&gt;buffers
(braket
l_int|1
)braket
)paren
(brace
id|vfree
c_func
(paren
id|ucpia-&gt;buffers
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|ucpia-&gt;buffers
(braket
l_int|1
)braket
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ucpia-&gt;buffers
(braket
l_int|0
)braket
)paren
(brace
id|vfree
c_func
(paren
id|ucpia-&gt;buffers
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|ucpia-&gt;buffers
(braket
l_int|0
)braket
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|ucpia-&gt;open
)paren
(brace
id|kfree
c_func
(paren
id|ucpia
)paren
suffix:semicolon
id|cam-&gt;lowlevel_data
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
DECL|function|usb_cpia_init
r_static
r_int
id|__init
id|usb_cpia_init
c_func
(paren
r_void
)paren
(brace
id|cam_list
op_assign
l_int|NULL
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|cam_list_lock_usb
)paren
suffix:semicolon
r_return
id|usb_register
c_func
(paren
op_amp
id|cpia_driver
)paren
suffix:semicolon
)brace
DECL|function|usb_cpia_cleanup
r_static
r_void
id|__exit
id|usb_cpia_cleanup
c_func
(paren
r_void
)paren
(brace
multiline_comment|/*&n;&t;struct cam_data *cam;&n;&n;&t;while ((cam = cam_list) != NULL)&n;&t;&t;cpia_disconnect(NULL, cam);&n;*/
id|usb_deregister
c_func
(paren
op_amp
id|cpia_driver
)paren
suffix:semicolon
)brace
DECL|variable|usb_cpia_init
id|module_init
(paren
id|usb_cpia_init
)paren
suffix:semicolon
DECL|variable|usb_cpia_cleanup
id|module_exit
(paren
id|usb_cpia_cleanup
)paren
suffix:semicolon
eof
