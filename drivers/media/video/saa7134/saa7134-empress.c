multiline_comment|/*&n; * $Id: saa7134-empress.c,v 1.3 2004/11/07 13:17:15 kraxel Exp $&n; *&n; * (c) 2004 Gerd Knorr &lt;kraxel@bytesex.org&gt; [SuSE Labs]&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &quot;saa7134-reg.h&quot;
macro_line|#include &quot;saa7134.h&quot;
macro_line|#include &lt;media/saa6752hs.h&gt;
multiline_comment|/* ------------------------------------------------------------------ */
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Gerd Knorr &lt;kraxel@bytesex.org&gt; [SuSE Labs]&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|empress_nr
r_static
r_int
r_int
id|empress_nr
(braket
)braket
op_assign
(brace
(braket
l_int|0
dot
dot
dot
(paren
id|SAA7134_MAXBOARDS
op_minus
l_int|1
)paren
)braket
op_assign
id|UNSET
)brace
suffix:semicolon
id|module_param_array
c_func
(paren
id|empress_nr
comma
r_int
comma
l_int|NULL
comma
l_int|0444
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|empress_nr
comma
l_string|&quot;ts device number&quot;
)paren
suffix:semicolon
DECL|variable|debug
r_static
r_int
r_int
id|debug
op_assign
l_int|0
suffix:semicolon
id|module_param
c_func
(paren
id|debug
comma
r_int
comma
l_int|0644
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|debug
comma
l_string|&quot;enable debug messages&quot;
)paren
suffix:semicolon
DECL|macro|dprintk
mdefine_line|#define dprintk(fmt, arg...)&t;if (debug)&t;&t;&t;&bslash;&n;&t;printk(KERN_DEBUG &quot;%s/empress: &quot; fmt, dev-&gt;name , ## arg)
multiline_comment|/* ------------------------------------------------------------------ */
DECL|function|ts_reset_encoder
r_static
r_void
id|ts_reset_encoder
c_func
(paren
r_struct
id|saa7134_dev
op_star
id|dev
)paren
(brace
id|saa_writeb
c_func
(paren
id|SAA7134_SPECIAL_MODE
comma
l_int|0x00
)paren
suffix:semicolon
id|msleep
c_func
(paren
l_int|10
)paren
suffix:semicolon
id|saa_writeb
c_func
(paren
id|SAA7134_SPECIAL_MODE
comma
l_int|0x01
)paren
suffix:semicolon
id|msleep
c_func
(paren
l_int|100
)paren
suffix:semicolon
)brace
DECL|function|ts_init_encoder
r_static
r_int
id|ts_init_encoder
c_func
(paren
r_struct
id|saa7134_dev
op_star
id|dev
comma
r_void
op_star
id|arg
)paren
(brace
id|ts_reset_encoder
c_func
(paren
id|dev
)paren
suffix:semicolon
id|saa7134_i2c_call_clients
c_func
(paren
id|dev
comma
id|MPEG_SETPARAMS
comma
id|arg
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* ------------------------------------------------------------------ */
DECL|function|ts_open
r_static
r_int
id|ts_open
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
(brace
r_int
id|minor
op_assign
id|iminor
c_func
(paren
id|inode
)paren
suffix:semicolon
r_struct
id|saa7134_dev
op_star
id|h
comma
op_star
id|dev
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|list_head
op_star
id|list
suffix:semicolon
r_int
id|err
suffix:semicolon
id|list_for_each
c_func
(paren
id|list
comma
op_amp
id|saa7134_devlist
)paren
(brace
id|h
op_assign
id|list_entry
c_func
(paren
id|list
comma
r_struct
id|saa7134_dev
comma
id|devlist
)paren
suffix:semicolon
r_if
c_cond
(paren
id|h-&gt;empress_dev
op_logical_and
id|h-&gt;empress_dev-&gt;minor
op_eq
id|minor
)paren
id|dev
op_assign
id|h
suffix:semicolon
)brace
r_if
c_cond
(paren
l_int|NULL
op_eq
id|dev
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;open minor=%d&bslash;n&quot;
comma
id|minor
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|dev-&gt;empress_tsq.lock
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|EBUSY
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;empress_users
)paren
r_goto
id|done
suffix:semicolon
id|dev-&gt;empress_users
op_increment
suffix:semicolon
id|file-&gt;private_data
op_assign
id|dev
suffix:semicolon
id|ts_init_encoder
c_func
(paren
id|dev
comma
l_int|NULL
)paren
suffix:semicolon
id|err
op_assign
l_int|0
suffix:semicolon
id|done
suffix:colon
id|up
c_func
(paren
op_amp
id|dev-&gt;empress_tsq.lock
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|ts_release
r_static
r_int
id|ts_release
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
(brace
r_struct
id|saa7134_dev
op_star
id|dev
op_assign
id|file-&gt;private_data
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;empress_tsq.streaming
)paren
id|videobuf_streamoff
c_func
(paren
op_amp
id|dev-&gt;empress_tsq
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|dev-&gt;empress_tsq.lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;empress_tsq.reading
)paren
id|videobuf_read_stop
c_func
(paren
op_amp
id|dev-&gt;empress_tsq
)paren
suffix:semicolon
id|dev-&gt;empress_users
op_decrement
suffix:semicolon
multiline_comment|/* stop the encoder */
id|ts_reset_encoder
c_func
(paren
id|dev
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|dev-&gt;empress_tsq.lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|ts_read
id|ts_read
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_char
id|__user
op_star
id|data
comma
r_int
id|count
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_struct
id|saa7134_dev
op_star
id|dev
op_assign
id|file-&gt;private_data
suffix:semicolon
r_return
id|videobuf_read_stream
c_func
(paren
op_amp
id|dev-&gt;empress_tsq
comma
id|data
comma
id|count
comma
id|ppos
comma
l_int|0
comma
id|file-&gt;f_flags
op_amp
id|O_NONBLOCK
)paren
suffix:semicolon
)brace
r_static
r_int
r_int
DECL|function|ts_poll
id|ts_poll
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_struct
id|poll_table_struct
op_star
id|wait
)paren
(brace
r_struct
id|saa7134_dev
op_star
id|dev
op_assign
id|file-&gt;private_data
suffix:semicolon
r_return
id|videobuf_poll_stream
c_func
(paren
id|file
comma
op_amp
id|dev-&gt;empress_tsq
comma
id|wait
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|ts_mmap
id|ts_mmap
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_struct
id|vm_area_struct
op_star
id|vma
)paren
(brace
r_struct
id|saa7134_dev
op_star
id|dev
op_assign
id|file-&gt;private_data
suffix:semicolon
r_return
id|videobuf_mmap_mapper
c_func
(paren
op_amp
id|dev-&gt;empress_tsq
comma
id|vma
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This function is _not_ called directly, but from&n; * video_generic_ioctl (and maybe others).  userspace&n; * copying is done already, arg is a kernel pointer.&n; */
DECL|function|ts_do_ioctl
r_static
r_int
id|ts_do_ioctl
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
comma
r_int
r_int
id|cmd
comma
r_void
op_star
id|arg
)paren
(brace
r_struct
id|saa7134_dev
op_star
id|dev
op_assign
id|file-&gt;private_data
suffix:semicolon
r_if
c_cond
(paren
id|debug
OG
l_int|1
)paren
id|saa7134_print_ioctl
c_func
(paren
id|dev-&gt;name
comma
id|cmd
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|VIDIOC_QUERYCAP
suffix:colon
(brace
r_struct
id|v4l2_capability
op_star
id|cap
op_assign
id|arg
suffix:semicolon
id|memset
c_func
(paren
id|cap
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|cap
)paren
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|cap-&gt;driver
comma
l_string|&quot;saa7134&quot;
)paren
suffix:semicolon
id|strlcpy
c_func
(paren
id|cap-&gt;card
comma
id|saa7134_boards
(braket
id|dev-&gt;board
)braket
dot
id|name
comma
r_sizeof
(paren
id|cap-&gt;card
)paren
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|cap-&gt;bus_info
comma
l_string|&quot;PCI:%s&quot;
comma
id|pci_name
c_func
(paren
id|dev-&gt;pci
)paren
)paren
suffix:semicolon
id|cap-&gt;version
op_assign
id|SAA7134_VERSION_CODE
suffix:semicolon
id|cap-&gt;capabilities
op_assign
id|V4L2_CAP_VIDEO_CAPTURE
op_or
id|V4L2_CAP_READWRITE
op_or
id|V4L2_CAP_STREAMING
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* --- input switching --------------------------------------- */
r_case
id|VIDIOC_ENUMINPUT
suffix:colon
(brace
r_struct
id|v4l2_input
op_star
id|i
op_assign
id|arg
suffix:semicolon
r_if
c_cond
(paren
id|i-&gt;index
op_ne
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|i-&gt;type
op_assign
id|V4L2_INPUT_TYPE_CAMERA
suffix:semicolon
id|strcpy
c_func
(paren
id|i-&gt;name
comma
l_string|&quot;CCIR656&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|VIDIOC_G_INPUT
suffix:colon
(brace
r_int
op_star
id|i
op_assign
id|arg
suffix:semicolon
op_star
id|i
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|VIDIOC_S_INPUT
suffix:colon
(brace
r_int
op_star
id|i
op_assign
id|arg
suffix:semicolon
r_if
c_cond
(paren
op_star
id|i
op_ne
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* --- capture ioctls ---------------------------------------- */
r_case
id|VIDIOC_ENUM_FMT
suffix:colon
(brace
r_struct
id|v4l2_fmtdesc
op_star
id|f
op_assign
id|arg
suffix:semicolon
r_int
id|index
suffix:semicolon
id|index
op_assign
id|f-&gt;index
suffix:semicolon
r_if
c_cond
(paren
id|index
op_ne
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|memset
c_func
(paren
id|f
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|f
)paren
)paren
suffix:semicolon
id|f-&gt;index
op_assign
id|index
suffix:semicolon
id|strlcpy
c_func
(paren
id|f-&gt;description
comma
l_string|&quot;MPEG TS&quot;
comma
r_sizeof
(paren
id|f-&gt;description
)paren
)paren
suffix:semicolon
id|f-&gt;type
op_assign
id|V4L2_BUF_TYPE_VIDEO_CAPTURE
suffix:semicolon
id|f-&gt;pixelformat
op_assign
id|V4L2_PIX_FMT_MPEG
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|VIDIOC_G_FMT
suffix:colon
(brace
r_struct
id|v4l2_format
op_star
id|f
op_assign
id|arg
suffix:semicolon
id|memset
c_func
(paren
id|f
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|f
)paren
)paren
suffix:semicolon
id|f-&gt;type
op_assign
id|V4L2_BUF_TYPE_VIDEO_CAPTURE
suffix:semicolon
multiline_comment|/* FIXME: translate subsampling type EMPRESS into&n;&t;&t; *        width/height: */
id|f-&gt;fmt.pix.width
op_assign
l_int|720
suffix:semicolon
multiline_comment|/* D1 */
id|f-&gt;fmt.pix.height
op_assign
l_int|576
suffix:semicolon
id|f-&gt;fmt.pix.pixelformat
op_assign
id|V4L2_PIX_FMT_MPEG
suffix:semicolon
id|f-&gt;fmt.pix.sizeimage
op_assign
id|TS_PACKET_SIZE
op_star
id|dev-&gt;ts.nr_packets
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|VIDIOC_S_FMT
suffix:colon
(brace
r_struct
id|v4l2_format
op_star
id|f
op_assign
id|arg
suffix:semicolon
r_if
c_cond
(paren
id|f-&gt;type
op_ne
id|V4L2_BUF_TYPE_VIDEO_CAPTURE
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/*&n;&t;&t;  FIXME: translate and round width/height into EMPRESS&n;&t;&t;  subsample type:&n;&n;&t;&t;          type  |   PAL   |  NTSC&n;&t;&t;&t;---------------------------&n;&t;&t;&t;  SIF   | 352x288 | 352x240&n;&t;&t;&t; 1/2 D1 | 352x576 | 352x480&n;&t;&t;&t; 2/3 D1 | 480x576 | 480x480&n;&t;&t;&t;  D1    | 720x576 | 720x480&n;&t;&t;*/
id|f-&gt;fmt.pix.width
op_assign
l_int|720
suffix:semicolon
multiline_comment|/* D1 */
id|f-&gt;fmt.pix.height
op_assign
l_int|576
suffix:semicolon
id|f-&gt;fmt.pix.pixelformat
op_assign
id|V4L2_PIX_FMT_MPEG
suffix:semicolon
id|f-&gt;fmt.pix.sizeimage
op_assign
id|TS_PACKET_SIZE
op_star
id|dev-&gt;ts.nr_packets
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|VIDIOC_REQBUFS
suffix:colon
r_return
id|videobuf_reqbufs
c_func
(paren
op_amp
id|dev-&gt;empress_tsq
comma
id|arg
)paren
suffix:semicolon
r_case
id|VIDIOC_QUERYBUF
suffix:colon
r_return
id|videobuf_querybuf
c_func
(paren
op_amp
id|dev-&gt;empress_tsq
comma
id|arg
)paren
suffix:semicolon
r_case
id|VIDIOC_QBUF
suffix:colon
r_return
id|videobuf_qbuf
c_func
(paren
op_amp
id|dev-&gt;empress_tsq
comma
id|arg
)paren
suffix:semicolon
r_case
id|VIDIOC_DQBUF
suffix:colon
r_return
id|videobuf_dqbuf
c_func
(paren
op_amp
id|dev-&gt;empress_tsq
comma
id|arg
comma
id|file-&gt;f_flags
op_amp
id|O_NONBLOCK
)paren
suffix:semicolon
r_case
id|VIDIOC_STREAMON
suffix:colon
r_return
id|videobuf_streamon
c_func
(paren
op_amp
id|dev-&gt;empress_tsq
)paren
suffix:semicolon
r_case
id|VIDIOC_STREAMOFF
suffix:colon
r_return
id|videobuf_streamoff
c_func
(paren
op_amp
id|dev-&gt;empress_tsq
)paren
suffix:semicolon
r_case
id|VIDIOC_QUERYCTRL
suffix:colon
r_case
id|VIDIOC_G_CTRL
suffix:colon
r_case
id|VIDIOC_S_CTRL
suffix:colon
r_return
id|saa7134_common_ioctl
c_func
(paren
id|dev
comma
id|cmd
comma
id|arg
)paren
suffix:semicolon
r_case
id|MPEG_SETPARAMS
suffix:colon
r_return
id|ts_init_encoder
c_func
(paren
id|dev
comma
id|arg
)paren
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|ENOIOCTLCMD
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ts_ioctl
r_static
r_int
id|ts_ioctl
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
r_return
id|video_usercopy
c_func
(paren
id|inode
comma
id|file
comma
id|cmd
comma
id|arg
comma
id|ts_do_ioctl
)paren
suffix:semicolon
)brace
DECL|variable|ts_fops
r_static
r_struct
id|file_operations
id|ts_fops
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|open
op_assign
id|ts_open
comma
dot
id|release
op_assign
id|ts_release
comma
dot
id|read
op_assign
id|ts_read
comma
dot
id|poll
op_assign
id|ts_poll
comma
dot
id|mmap
op_assign
id|ts_mmap
comma
dot
id|ioctl
op_assign
id|ts_ioctl
comma
dot
id|llseek
op_assign
id|no_llseek
comma
)brace
suffix:semicolon
multiline_comment|/* ----------------------------------------------------------- */
DECL|variable|saa7134_empress_template
r_static
r_struct
id|video_device
id|saa7134_empress_template
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;saa7134-empress&quot;
comma
dot
id|type
op_assign
l_int|0
multiline_comment|/* FIXME */
comma
dot
id|type2
op_assign
l_int|0
multiline_comment|/* FIXME */
comma
dot
id|hardware
op_assign
l_int|0
comma
dot
id|fops
op_assign
op_amp
id|ts_fops
comma
dot
id|minor
op_assign
op_minus
l_int|1
comma
)brace
suffix:semicolon
DECL|function|empress_init
r_static
r_int
id|empress_init
c_func
(paren
r_struct
id|saa7134_dev
op_star
id|dev
)paren
(brace
r_int
id|err
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;%s: %s&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|dev-&gt;empress_dev
op_assign
id|video_device_alloc
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|NULL
op_eq
id|dev-&gt;empress_dev
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
op_star
(paren
id|dev-&gt;empress_dev
)paren
op_assign
id|saa7134_empress_template
suffix:semicolon
id|dev-&gt;empress_dev-&gt;dev
op_assign
op_amp
id|dev-&gt;pci-&gt;dev
suffix:semicolon
id|dev-&gt;empress_dev-&gt;release
op_assign
id|video_device_release
suffix:semicolon
id|snprintf
c_func
(paren
id|dev-&gt;empress_dev-&gt;name
comma
r_sizeof
(paren
id|dev-&gt;empress_dev-&gt;name
)paren
comma
l_string|&quot;%s empress (%s)&quot;
comma
id|dev-&gt;name
comma
id|saa7134_boards
(braket
id|dev-&gt;board
)braket
dot
id|name
)paren
suffix:semicolon
id|err
op_assign
id|video_register_device
c_func
(paren
id|dev-&gt;empress_dev
comma
id|VFL_TYPE_GRABBER
comma
id|empress_nr
(braket
id|dev-&gt;nr
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: can&squot;t register video device&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
id|video_device_release
c_func
(paren
id|dev-&gt;empress_dev
)paren
suffix:semicolon
id|dev-&gt;empress_dev
op_assign
l_int|NULL
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: registered device video%d [mpeg]&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|dev-&gt;empress_dev-&gt;minor
op_amp
l_int|0x1f
)paren
suffix:semicolon
id|videobuf_queue_init
c_func
(paren
op_amp
id|dev-&gt;empress_tsq
comma
op_amp
id|saa7134_ts_qops
comma
id|dev-&gt;pci
comma
op_amp
id|dev-&gt;slock
comma
id|V4L2_BUF_TYPE_VIDEO_CAPTURE
comma
id|V4L2_FIELD_ALTERNATE
comma
r_sizeof
(paren
r_struct
id|saa7134_buf
)paren
comma
id|dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|empress_fini
r_static
r_int
id|empress_fini
c_func
(paren
r_struct
id|saa7134_dev
op_star
id|dev
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;%s: %s&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|NULL
op_eq
id|dev-&gt;empress_dev
)paren
r_return
l_int|0
suffix:semicolon
id|video_unregister_device
c_func
(paren
id|dev-&gt;empress_dev
)paren
suffix:semicolon
id|dev-&gt;empress_dev
op_assign
l_int|NULL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|empress_ops
r_static
r_struct
id|saa7134_mpeg_ops
id|empress_ops
op_assign
(brace
dot
id|type
op_assign
id|SAA7134_MPEG_EMPRESS
comma
dot
id|init
op_assign
id|empress_init
comma
dot
id|fini
op_assign
id|empress_fini
comma
)brace
suffix:semicolon
DECL|function|empress_register
r_static
r_int
id|__init
id|empress_register
c_func
(paren
r_void
)paren
(brace
r_return
id|saa7134_ts_register
c_func
(paren
op_amp
id|empress_ops
)paren
suffix:semicolon
)brace
DECL|function|empress_unregister
r_static
r_void
id|__exit
id|empress_unregister
c_func
(paren
r_void
)paren
(brace
id|saa7134_ts_unregister
c_func
(paren
op_amp
id|empress_ops
)paren
suffix:semicolon
)brace
DECL|variable|empress_register
id|module_init
c_func
(paren
id|empress_register
)paren
suffix:semicolon
DECL|variable|empress_unregister
id|module_exit
c_func
(paren
id|empress_unregister
)paren
suffix:semicolon
multiline_comment|/* ----------------------------------------------------------- */
multiline_comment|/*&n; * Local variables:&n; * c-basic-offset: 8&n; * End:&n; */
eof
