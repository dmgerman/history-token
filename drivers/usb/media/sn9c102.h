multiline_comment|/***************************************************************************&n; * V4L2 driver for SN9C10x PC Camera Controllers                           *&n; *                                                                         *&n; * Copyright (C) 2004-2005 by Luca Risolia &lt;luca.risolia@studio.unibo.it&gt;  *&n; *                                                                         *&n; * This program is free software; you can redistribute it and/or modify    *&n; * it under the terms of the GNU General Public License as published by    *&n; * the Free Software Foundation; either version 2 of the License, or       *&n; * (at your option) any later version.                                     *&n; *                                                                         *&n; * This program is distributed in the hope that it will be useful,         *&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of          *&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *&n; * GNU General Public License for more details.                            *&n; *                                                                         *&n; * You should have received a copy of the GNU General Public License       *&n; * along with this program; if not, write to the Free Software             *&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.               *&n; ***************************************************************************/
macro_line|#ifndef _SN9C102_H_
DECL|macro|_SN9C102_H_
mdefine_line|#define _SN9C102_H_
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/usb.h&gt;
macro_line|#include &lt;linux/videodev.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/param.h&gt;
macro_line|#include &lt;linux/rwsem.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
macro_line|#include &quot;sn9c102_sensor.h&quot;
multiline_comment|/*****************************************************************************/
DECL|macro|SN9C102_DEBUG
mdefine_line|#define SN9C102_DEBUG
DECL|macro|SN9C102_DEBUG_LEVEL
mdefine_line|#define SN9C102_DEBUG_LEVEL       2
DECL|macro|SN9C102_MAX_DEVICES
mdefine_line|#define SN9C102_MAX_DEVICES       64
DECL|macro|SN9C102_PRESERVE_IMGSCALE
mdefine_line|#define SN9C102_PRESERVE_IMGSCALE 0
DECL|macro|SN9C102_FORCE_MUNMAP
mdefine_line|#define SN9C102_FORCE_MUNMAP      0
DECL|macro|SN9C102_MAX_FRAMES
mdefine_line|#define SN9C102_MAX_FRAMES        32
DECL|macro|SN9C102_URBS
mdefine_line|#define SN9C102_URBS              2
DECL|macro|SN9C102_ISO_PACKETS
mdefine_line|#define SN9C102_ISO_PACKETS       7
DECL|macro|SN9C102_ALTERNATE_SETTING
mdefine_line|#define SN9C102_ALTERNATE_SETTING 8
DECL|macro|SN9C102_URB_TIMEOUT
mdefine_line|#define SN9C102_URB_TIMEOUT       msecs_to_jiffies(2 * SN9C102_ISO_PACKETS)
DECL|macro|SN9C102_CTRL_TIMEOUT
mdefine_line|#define SN9C102_CTRL_TIMEOUT      msecs_to_jiffies(300)
multiline_comment|/*****************************************************************************/
DECL|macro|SN9C102_MODULE_NAME
mdefine_line|#define SN9C102_MODULE_NAME     &quot;V4L2 driver for SN9C10x PC Camera Controllers&quot;
DECL|macro|SN9C102_MODULE_AUTHOR
mdefine_line|#define SN9C102_MODULE_AUTHOR   &quot;(C) 2004 Luca Risolia&quot;
DECL|macro|SN9C102_AUTHOR_EMAIL
mdefine_line|#define SN9C102_AUTHOR_EMAIL    &quot;&lt;luca.risolia@studio.unibo.it&gt;&quot;
DECL|macro|SN9C102_MODULE_LICENSE
mdefine_line|#define SN9C102_MODULE_LICENSE  &quot;GPL&quot;
DECL|macro|SN9C102_MODULE_VERSION
mdefine_line|#define SN9C102_MODULE_VERSION  &quot;1:1.22&quot;
DECL|macro|SN9C102_MODULE_VERSION_CODE
mdefine_line|#define SN9C102_MODULE_VERSION_CODE  KERNEL_VERSION(1, 0, 22)
DECL|enum|sn9c102_bridge
r_enum
id|sn9c102_bridge
(brace
DECL|enumerator|BRIDGE_SN9C101
id|BRIDGE_SN9C101
op_assign
l_int|0x01
comma
DECL|enumerator|BRIDGE_SN9C102
id|BRIDGE_SN9C102
op_assign
l_int|0x02
comma
DECL|enumerator|BRIDGE_SN9C103
id|BRIDGE_SN9C103
op_assign
l_int|0x04
comma
)brace
suffix:semicolon
id|SN9C102_ID_TABLE
id|SN9C102_SENSOR_TABLE
DECL|enum|sn9c102_frame_state
r_enum
id|sn9c102_frame_state
(brace
DECL|enumerator|F_UNUSED
id|F_UNUSED
comma
DECL|enumerator|F_QUEUED
id|F_QUEUED
comma
DECL|enumerator|F_GRABBING
id|F_GRABBING
comma
DECL|enumerator|F_DONE
id|F_DONE
comma
DECL|enumerator|F_ERROR
id|F_ERROR
comma
)brace
suffix:semicolon
DECL|struct|sn9c102_frame_t
r_struct
id|sn9c102_frame_t
(brace
DECL|member|bufmem
r_void
op_star
id|bufmem
suffix:semicolon
DECL|member|buf
r_struct
id|v4l2_buffer
id|buf
suffix:semicolon
DECL|member|state
r_enum
id|sn9c102_frame_state
id|state
suffix:semicolon
DECL|member|frame
r_struct
id|list_head
id|frame
suffix:semicolon
DECL|member|vma_use_count
r_int
r_int
id|vma_use_count
suffix:semicolon
)brace
suffix:semicolon
DECL|enum|sn9c102_dev_state
r_enum
id|sn9c102_dev_state
(brace
DECL|enumerator|DEV_INITIALIZED
id|DEV_INITIALIZED
op_assign
l_int|0x01
comma
DECL|enumerator|DEV_DISCONNECTED
id|DEV_DISCONNECTED
op_assign
l_int|0x02
comma
DECL|enumerator|DEV_MISCONFIGURED
id|DEV_MISCONFIGURED
op_assign
l_int|0x04
comma
)brace
suffix:semicolon
DECL|enum|sn9c102_io_method
r_enum
id|sn9c102_io_method
(brace
DECL|enumerator|IO_NONE
id|IO_NONE
comma
DECL|enumerator|IO_READ
id|IO_READ
comma
DECL|enumerator|IO_MMAP
id|IO_MMAP
comma
)brace
suffix:semicolon
DECL|enum|sn9c102_stream_state
r_enum
id|sn9c102_stream_state
(brace
DECL|enumerator|STREAM_OFF
id|STREAM_OFF
comma
DECL|enumerator|STREAM_INTERRUPT
id|STREAM_INTERRUPT
comma
DECL|enumerator|STREAM_ON
id|STREAM_ON
comma
)brace
suffix:semicolon
DECL|typedef|sn9c102_sof_header_t
r_typedef
r_char
id|sn9c102_sof_header_t
(braket
l_int|12
)braket
suffix:semicolon
DECL|typedef|sn9c102_eof_header_t
r_typedef
r_char
id|sn9c102_eof_header_t
(braket
l_int|4
)braket
suffix:semicolon
DECL|struct|sn9c102_sysfs_attr
r_struct
id|sn9c102_sysfs_attr
(brace
DECL|member|reg
DECL|member|i2c_reg
id|u8
id|reg
comma
id|i2c_reg
suffix:semicolon
DECL|member|frame_header
id|sn9c102_sof_header_t
id|frame_header
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|sn9c102_module_param
r_struct
id|sn9c102_module_param
(brace
DECL|member|force_munmap
id|u8
id|force_munmap
suffix:semicolon
)brace
suffix:semicolon
r_static
id|DECLARE_MUTEX
c_func
(paren
id|sn9c102_sysfs_lock
)paren
suffix:semicolon
r_static
id|DECLARE_RWSEM
c_func
(paren
id|sn9c102_disconnect
)paren
suffix:semicolon
DECL|struct|sn9c102_device
r_struct
id|sn9c102_device
(brace
DECL|member|dev
r_struct
id|device
id|dev
suffix:semicolon
DECL|member|v4ldev
r_struct
id|video_device
op_star
id|v4ldev
suffix:semicolon
DECL|member|bridge
r_enum
id|sn9c102_bridge
id|bridge
suffix:semicolon
DECL|member|sensor
r_struct
id|sn9c102_sensor
op_star
id|sensor
suffix:semicolon
DECL|member|usbdev
r_struct
id|usb_device
op_star
id|usbdev
suffix:semicolon
DECL|member|urb
r_struct
id|urb
op_star
id|urb
(braket
id|SN9C102_URBS
)braket
suffix:semicolon
DECL|member|transfer_buffer
r_void
op_star
id|transfer_buffer
(braket
id|SN9C102_URBS
)braket
suffix:semicolon
DECL|member|control_buffer
id|u8
op_star
id|control_buffer
suffix:semicolon
DECL|member|frame_current
DECL|member|frame
r_struct
id|sn9c102_frame_t
op_star
id|frame_current
comma
id|frame
(braket
id|SN9C102_MAX_FRAMES
)braket
suffix:semicolon
DECL|member|inqueue
DECL|member|outqueue
r_struct
id|list_head
id|inqueue
comma
id|outqueue
suffix:semicolon
DECL|member|frame_count
DECL|member|nbuffers
DECL|member|nreadbuffers
id|u32
id|frame_count
comma
id|nbuffers
comma
id|nreadbuffers
suffix:semicolon
DECL|member|io
r_enum
id|sn9c102_io_method
id|io
suffix:semicolon
DECL|member|stream
r_enum
id|sn9c102_stream_state
id|stream
suffix:semicolon
DECL|member|compression
r_struct
id|v4l2_jpegcompression
id|compression
suffix:semicolon
DECL|member|sysfs
r_struct
id|sn9c102_sysfs_attr
id|sysfs
suffix:semicolon
DECL|member|sof_header
id|sn9c102_sof_header_t
id|sof_header
suffix:semicolon
DECL|member|reg
id|u16
id|reg
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|module_param
r_struct
id|sn9c102_module_param
id|module_param
suffix:semicolon
DECL|member|state
r_enum
id|sn9c102_dev_state
id|state
suffix:semicolon
DECL|member|users
id|u8
id|users
suffix:semicolon
DECL|member|dev_sem
DECL|member|fileop_sem
r_struct
id|semaphore
id|dev_sem
comma
id|fileop_sem
suffix:semicolon
DECL|member|queue_lock
id|spinlock_t
id|queue_lock
suffix:semicolon
DECL|member|open
DECL|member|wait_frame
DECL|member|wait_stream
id|wait_queue_head_t
id|open
comma
id|wait_frame
comma
id|wait_stream
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*****************************************************************************/
r_void
DECL|function|sn9c102_attach_sensor
id|sn9c102_attach_sensor
c_func
(paren
r_struct
id|sn9c102_device
op_star
id|cam
comma
r_struct
id|sn9c102_sensor
op_star
id|sensor
)paren
(brace
id|cam-&gt;sensor
op_assign
id|sensor
suffix:semicolon
id|cam-&gt;sensor-&gt;dev
op_assign
op_amp
id|cam-&gt;dev
suffix:semicolon
id|cam-&gt;sensor-&gt;usbdev
op_assign
id|cam-&gt;usbdev
suffix:semicolon
)brace
multiline_comment|/*****************************************************************************/
DECL|macro|DBG
macro_line|#undef DBG
DECL|macro|KDBG
macro_line|#undef KDBG
macro_line|#ifdef SN9C102_DEBUG
DECL|macro|DBG
macro_line|#&t;define DBG(level, fmt, args...)                                       &bslash;&n;{                                                                             &bslash;&n;&t;if (debug &gt;= (level)) {                                               &bslash;&n;&t;&t;if ((level) == 1)                                             &bslash;&n;&t;&t;&t;dev_err(&amp;cam-&gt;dev, fmt &quot;&bslash;n&quot;, ## args);                &bslash;&n;&t;&t;else if ((level) == 2)                                        &bslash;&n;&t;&t;&t;dev_info(&amp;cam-&gt;dev, fmt &quot;&bslash;n&quot;, ## args);               &bslash;&n;&t;&t;else if ((level) &gt;= 3)                                        &bslash;&n;&t;&t;&t;dev_info(&amp;cam-&gt;dev, &quot;[%s:%d] &quot; fmt &quot;&bslash;n&quot;,              &bslash;&n;&t;&t;&t;         __FUNCTION__, __LINE__ , ## args);           &bslash;&n;&t;}                                                                     &bslash;&n;}
DECL|macro|KDBG
macro_line|#&t;define KDBG(level, fmt, args...)                                      &bslash;&n;{                                                                             &bslash;&n;&t;if (debug &gt;= (level)) {                                               &bslash;&n;&t;&t;if ((level) == 1 || (level) == 2)                             &bslash;&n;&t;&t;&t;pr_info(&quot;sn9c102: &quot; fmt &quot;&bslash;n&quot;, ## args);               &bslash;&n;&t;&t;else if ((level) == 3)                                        &bslash;&n;&t;&t;&t;pr_debug(&quot;sn9c102: [%s:%d] &quot; fmt &quot;&bslash;n&quot;, __FUNCTION__,  &bslash;&n;&t;&t;&t;         __LINE__ , ## args);                         &bslash;&n;&t;}                                                                     &bslash;&n;}
macro_line|#else
DECL|macro|KDBG
macro_line|#&t;define KDBG(level, fmt, args...) do {;} while(0);
DECL|macro|DBG
macro_line|#&t;define DBG(level, fmt, args...) do {;} while(0);
macro_line|#endif
DECL|macro|PDBG
macro_line|#undef PDBG
DECL|macro|PDBG
mdefine_line|#define PDBG(fmt, args...)                                                    &bslash;&n;dev_info(&amp;cam-&gt;dev, &quot;[%s:%d] &quot; fmt &quot;&bslash;n&quot;, __FUNCTION__, __LINE__ , ## args);
DECL|macro|PDBGG
macro_line|#undef PDBGG
DECL|macro|PDBGG
mdefine_line|#define PDBGG(fmt, args...) do {;} while(0); /* placeholder */
macro_line|#endif /* _SN9C102_H_ */
eof
