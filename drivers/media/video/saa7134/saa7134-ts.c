multiline_comment|/*&n; * device driver for philips saa7134 based TV cards&n; * video4linux video interface&n; *&n; * (c) 2001,02 Gerd Knorr &lt;kraxel@bytesex.org&gt; [SuSE Labs]&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
DECL|macro|__NO_VERSION__
mdefine_line|#define __NO_VERSION__ 1
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &quot;saa7134-reg.h&quot;
macro_line|#include &quot;saa7134.h&quot;
multiline_comment|/* ------------------------------------------------------------------ */
DECL|variable|ts_debug
r_static
r_int
r_int
id|ts_debug
op_assign
l_int|0
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|ts_debug
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|ts_debug
comma
l_string|&quot;enable debug messages [ts]&quot;
)paren
suffix:semicolon
DECL|variable|tsbufs
r_static
r_int
r_int
id|tsbufs
op_assign
l_int|4
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|tsbufs
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|tsbufs
comma
l_string|&quot;number of ts buffers, range 2-32&quot;
)paren
suffix:semicolon
DECL|macro|TS_PACKET_SIZE
mdefine_line|#define TS_PACKET_SIZE 188 /* TS packets 188 bytes */
DECL|macro|TS_NR_PACKETS
mdefine_line|#define TS_NR_PACKETS 312
DECL|macro|dprintk
mdefine_line|#define dprintk(fmt, arg...)&t;if (ts_debug) &bslash;&n;&t;printk(KERN_DEBUG &quot;%s/ts: &quot; fmt, dev-&gt;name, ## arg)
multiline_comment|/* ------------------------------------------------------------------ */
DECL|function|buffer_activate
r_static
r_int
id|buffer_activate
c_func
(paren
r_struct
id|saa7134_dev
op_star
id|dev
comma
r_struct
id|saa7134_buf
op_star
id|buf
comma
r_struct
id|saa7134_buf
op_star
id|next
)paren
(brace
id|u32
id|control
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;buffer_activate [%p]&bslash;n&quot;
comma
id|buf
)paren
suffix:semicolon
id|buf-&gt;vb.state
op_assign
id|STATE_ACTIVE
suffix:semicolon
multiline_comment|/* dma: setup channel 5 (= TS) */
id|control
op_assign
id|SAA7134_RS_CONTROL_BURST_16
op_or
id|SAA7134_RS_CONTROL_ME
op_or
(paren
id|buf-&gt;pt-&gt;dma
op_rshift
l_int|12
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|NULL
op_eq
id|next
)paren
id|next
op_assign
id|buf
suffix:semicolon
r_if
c_cond
(paren
id|V4L2_FIELD_TOP
op_eq
id|buf-&gt;vb.field
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;[top]     buf=%p next=%p&quot;
comma
id|buf
comma
id|next
)paren
suffix:semicolon
id|saa_writel
c_func
(paren
id|SAA7134_RS_BA1
c_func
(paren
l_int|5
)paren
comma
id|saa7134_buffer_base
c_func
(paren
id|buf
)paren
)paren
suffix:semicolon
id|saa_writel
c_func
(paren
id|SAA7134_RS_BA2
c_func
(paren
l_int|5
)paren
comma
id|saa7134_buffer_base
c_func
(paren
id|next
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|dprintk
c_func
(paren
l_string|&quot;[bottom]  buf=%p next=%p&quot;
comma
id|buf
comma
id|next
)paren
suffix:semicolon
id|saa_writel
c_func
(paren
id|SAA7134_RS_BA1
c_func
(paren
l_int|5
)paren
comma
id|saa7134_buffer_base
c_func
(paren
id|next
)paren
)paren
suffix:semicolon
id|saa_writel
c_func
(paren
id|SAA7134_RS_BA2
c_func
(paren
l_int|5
)paren
comma
id|saa7134_buffer_base
c_func
(paren
id|buf
)paren
)paren
suffix:semicolon
)brace
id|saa_writel
c_func
(paren
id|SAA7134_RS_PITCH
c_func
(paren
l_int|5
)paren
comma
id|TS_PACKET_SIZE
)paren
suffix:semicolon
id|saa_writel
c_func
(paren
id|SAA7134_RS_CONTROL
c_func
(paren
l_int|5
)paren
comma
id|control
)paren
suffix:semicolon
multiline_comment|/* start DMA */
id|saa7134_set_dmabits
c_func
(paren
id|dev
)paren
suffix:semicolon
id|mod_timer
c_func
(paren
op_amp
id|dev-&gt;ts_q.timeout
comma
id|jiffies
op_plus
id|BUFFER_TIMEOUT
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|buffer_prepare
r_static
r_int
id|buffer_prepare
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_struct
id|videobuf_buffer
op_star
id|vb
comma
r_enum
id|v4l2_field
id|field
)paren
(brace
r_struct
id|saa7134_dev
op_star
id|dev
op_assign
id|file-&gt;private_data
suffix:semicolon
r_struct
id|saa7134_buf
op_star
id|buf
op_assign
(paren
r_struct
id|saa7134_buf
op_star
)paren
id|vb
suffix:semicolon
r_int
id|lines
comma
id|llength
comma
id|size
comma
id|err
suffix:semicolon
id|llength
op_assign
id|TS_PACKET_SIZE
suffix:semicolon
id|lines
op_assign
id|TS_NR_PACKETS
suffix:semicolon
id|size
op_assign
id|lines
op_star
id|llength
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_ne
id|buf-&gt;vb.baddr
op_logical_and
id|buf-&gt;vb.bsize
OL
id|size
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|buf-&gt;vb.size
op_ne
id|size
)paren
(brace
id|saa7134_dma_free
c_func
(paren
id|dev
comma
id|buf
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|STATE_NEEDS_INIT
op_eq
id|buf-&gt;vb.state
)paren
(brace
id|buf-&gt;vb.width
op_assign
id|llength
suffix:semicolon
id|buf-&gt;vb.height
op_assign
id|lines
suffix:semicolon
id|buf-&gt;vb.size
op_assign
id|size
suffix:semicolon
id|buf-&gt;pt
op_assign
op_amp
id|dev-&gt;ts.pt_ts
suffix:semicolon
id|err
op_assign
id|videobuf_iolock
c_func
(paren
id|dev-&gt;pci
comma
op_amp
id|buf-&gt;vb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|oops
suffix:semicolon
id|err
op_assign
id|saa7134_pgtable_build
c_func
(paren
id|dev-&gt;pci
comma
id|buf-&gt;pt
comma
id|buf-&gt;vb.dma.sglist
comma
id|buf-&gt;vb.dma.sglen
comma
id|saa7134_buffer_startpage
c_func
(paren
id|buf
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|oops
suffix:semicolon
)brace
id|buf-&gt;vb.state
op_assign
id|STATE_PREPARED
suffix:semicolon
id|buf-&gt;top_seen
op_assign
l_int|0
suffix:semicolon
id|buf-&gt;activate
op_assign
id|buffer_activate
suffix:semicolon
id|buf-&gt;vb.field
op_assign
id|field
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|oops
suffix:colon
id|saa7134_dma_free
c_func
(paren
id|dev
comma
id|buf
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
r_static
r_int
DECL|function|buffer_setup
id|buffer_setup
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_int
op_star
id|count
comma
r_int
op_star
id|size
)paren
(brace
op_star
id|size
op_assign
id|TS_PACKET_SIZE
op_star
id|TS_NR_PACKETS
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_eq
op_star
id|count
)paren
op_star
id|count
op_assign
id|tsbufs
suffix:semicolon
op_star
id|count
op_assign
id|saa7134_buffer_count
c_func
(paren
op_star
id|size
comma
op_star
id|count
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|buffer_queue
r_static
r_void
id|buffer_queue
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_struct
id|videobuf_buffer
op_star
id|vb
)paren
(brace
r_struct
id|saa7134_dev
op_star
id|dev
op_assign
id|file-&gt;private_data
suffix:semicolon
r_struct
id|saa7134_buf
op_star
id|buf
op_assign
(paren
r_struct
id|saa7134_buf
op_star
)paren
id|vb
suffix:semicolon
id|saa7134_buffer_queue
c_func
(paren
id|dev
comma
op_amp
id|dev-&gt;ts_q
comma
id|buf
)paren
suffix:semicolon
)brace
DECL|function|buffer_release
r_static
r_void
id|buffer_release
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_struct
id|videobuf_buffer
op_star
id|vb
)paren
(brace
r_struct
id|saa7134_dev
op_star
id|dev
op_assign
id|file-&gt;private_data
suffix:semicolon
r_struct
id|saa7134_buf
op_star
id|buf
op_assign
(paren
r_struct
id|saa7134_buf
op_star
)paren
id|vb
suffix:semicolon
id|saa7134_dma_free
c_func
(paren
id|dev
comma
id|buf
)paren
suffix:semicolon
)brace
DECL|variable|ts_qops
r_static
r_struct
id|videobuf_queue_ops
id|ts_qops
op_assign
(brace
dot
id|buf_setup
op_assign
id|buffer_setup
comma
dot
id|buf_prepare
op_assign
id|buffer_prepare
comma
dot
id|buf_queue
op_assign
id|buffer_queue
comma
dot
id|buf_release
op_assign
id|buffer_release
comma
)brace
suffix:semicolon
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
r_int
id|minor
op_assign
id|minor
c_func
(paren
id|inode-&gt;i_rdev
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
id|h-&gt;ts_dev.minor
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
id|dev-&gt;ts.ts.lock
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
id|dev-&gt;ts.users
)paren
r_goto
id|done
suffix:semicolon
id|dev-&gt;ts.users
op_increment
suffix:semicolon
id|file-&gt;private_data
op_assign
id|dev
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
id|dev-&gt;ts.ts.lock
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
id|dev-&gt;ts.ts.streaming
)paren
id|videobuf_streamoff
c_func
(paren
id|file
comma
op_amp
id|dev-&gt;ts.ts
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|dev-&gt;ts.ts.lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;ts.ts.reading
)paren
id|videobuf_read_stop
c_func
(paren
id|file
comma
op_amp
id|dev-&gt;ts.ts
)paren
suffix:semicolon
id|dev-&gt;ts.users
op_decrement
suffix:semicolon
id|up
c_func
(paren
op_amp
id|dev-&gt;ts.ts.lock
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
id|file
comma
op_amp
id|dev-&gt;ts.ts
comma
id|data
comma
id|count
comma
id|ppos
comma
l_int|0
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
id|dev-&gt;ts.ts
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
id|vma
comma
op_amp
id|dev-&gt;ts.ts
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
id|ts_debug
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
id|strncpy
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
id|dev-&gt;pci-&gt;slot_name
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
id|strncpy
c_func
(paren
id|f-&gt;description
comma
l_string|&quot;MPEG TS&quot;
comma
l_int|31
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
id|TS_NR_PACKETS
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
multiline_comment|/* &n;&t;&t;  FIXME: translate and round width/height into EMPRESS&n;&t;&t;  subsample type:&n;&t;&t; &n;&t;&t;          type  |   PAL   |  NTSC &n;&t;&t;&t;---------------------------&n;&t;&t;&t;  SIF   | 352x288 | 352x240&n;&t;&t;&t; 1/2 D1 | 352x576 | 352x480&n;&t;&t;&t; 2/3 D1 | 480x576 | 480x480&n;&t;&t;&t;  D1    | 720x576 | 720x480&n;&t;&t;*/
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
id|TS_NR_PACKETS
suffix:semicolon
)brace
r_case
id|VIDIOC_REQBUFS
suffix:colon
r_return
id|videobuf_reqbufs
c_func
(paren
id|file
comma
op_amp
id|dev-&gt;ts.ts
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
id|dev-&gt;ts.ts
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
id|file
comma
op_amp
id|dev-&gt;ts.ts
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
id|file
comma
op_amp
id|dev-&gt;ts.ts
comma
id|arg
)paren
suffix:semicolon
r_case
id|VIDIOC_STREAMON
suffix:colon
r_return
id|videobuf_streamon
c_func
(paren
id|file
comma
op_amp
id|dev-&gt;ts.ts
)paren
suffix:semicolon
r_case
id|VIDIOC_STREAMOFF
suffix:colon
r_return
id|videobuf_streamoff
c_func
(paren
id|file
comma
op_amp
id|dev-&gt;ts.ts
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
multiline_comment|/* exported stuff                                              */
DECL|variable|saa7134_ts_template
r_struct
id|video_device
id|saa7134_ts_template
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;saa7134-ts&quot;
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
DECL|function|saa7134_ts_init
r_int
id|saa7134_ts_init
c_func
(paren
r_struct
id|saa7134_dev
op_star
id|dev
)paren
(brace
multiline_comment|/* sanitycheck insmod options */
r_if
c_cond
(paren
id|tsbufs
OL
l_int|2
)paren
id|tsbufs
op_assign
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|tsbufs
OG
id|VIDEO_MAX_FRAME
)paren
id|tsbufs
op_assign
id|VIDEO_MAX_FRAME
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|dev-&gt;ts_q.queue
)paren
suffix:semicolon
id|init_timer
c_func
(paren
op_amp
id|dev-&gt;ts_q.timeout
)paren
suffix:semicolon
id|dev-&gt;ts_q.timeout.function
op_assign
id|saa7134_buffer_timeout
suffix:semicolon
id|dev-&gt;ts_q.timeout.data
op_assign
(paren
r_int
r_int
)paren
(paren
op_amp
id|dev-&gt;ts_q
)paren
suffix:semicolon
id|dev-&gt;ts_q.dev
op_assign
id|dev
suffix:semicolon
id|videobuf_queue_init
c_func
(paren
op_amp
id|dev-&gt;ts.ts
comma
op_amp
id|ts_qops
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
)paren
suffix:semicolon
id|saa7134_pgtable_alloc
c_func
(paren
id|dev-&gt;pci
comma
op_amp
id|dev-&gt;ts.pt_ts
)paren
suffix:semicolon
multiline_comment|/* init TS hw */
id|saa_writeb
c_func
(paren
id|SAA7134_TS_SERIAL1
comma
l_int|0x00
)paren
suffix:semicolon
multiline_comment|/* deactivate TS softreset */
id|saa_writeb
c_func
(paren
id|SAA7134_TS_PARALLEL
comma
l_int|0xec
)paren
suffix:semicolon
multiline_comment|/* TSSOP high active, TSVAL high active, TSLOCK ignored */
id|saa_writeb
c_func
(paren
id|SAA7134_TS_PARALLEL_SERIAL
comma
(paren
id|TS_PACKET_SIZE
op_minus
l_int|1
)paren
)paren
suffix:semicolon
id|saa_writeb
c_func
(paren
id|SAA7134_TS_DMA0
comma
(paren
(paren
id|TS_NR_PACKETS
op_minus
l_int|1
)paren
op_amp
l_int|0xff
)paren
)paren
suffix:semicolon
id|saa_writeb
c_func
(paren
id|SAA7134_TS_DMA1
comma
(paren
(paren
(paren
id|TS_NR_PACKETS
op_minus
l_int|1
)paren
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
)paren
)paren
suffix:semicolon
id|saa_writeb
c_func
(paren
id|SAA7134_TS_DMA2
comma
(paren
(paren
(paren
(paren
id|TS_NR_PACKETS
op_minus
l_int|1
)paren
op_rshift
l_int|16
)paren
op_amp
l_int|0x3f
)paren
op_or
l_int|0x00
)paren
)paren
suffix:semicolon
multiline_comment|/* TSNOPIT=0, TSCOLAP=0 */
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|saa7134_ts_fini
r_int
id|saa7134_ts_fini
c_func
(paren
r_struct
id|saa7134_dev
op_star
id|dev
)paren
(brace
multiline_comment|/* nothing */
id|saa7134_pgtable_free
c_func
(paren
id|dev-&gt;pci
comma
op_amp
id|dev-&gt;ts.pt_ts
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|saa7134_irq_ts_done
r_void
id|saa7134_irq_ts_done
c_func
(paren
r_struct
id|saa7134_dev
op_star
id|dev
comma
r_int
r_int
id|status
)paren
(brace
r_enum
id|v4l2_field
id|field
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|dev-&gt;slock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;ts_q.curr
)paren
(brace
id|field
op_assign
id|dev-&gt;video_q.curr-&gt;vb.field
suffix:semicolon
r_if
c_cond
(paren
id|field
op_eq
id|V4L2_FIELD_TOP
)paren
(brace
r_if
c_cond
(paren
(paren
id|status
op_amp
l_int|0x100000
)paren
op_ne
l_int|0x100000
)paren
r_goto
id|done
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
(paren
id|status
op_amp
l_int|0x100000
)paren
op_ne
l_int|0x000000
)paren
r_goto
id|done
suffix:semicolon
)brace
id|saa7134_buffer_finish
c_func
(paren
id|dev
comma
op_amp
id|dev-&gt;ts_q
comma
id|STATE_DONE
)paren
suffix:semicolon
)brace
id|saa7134_buffer_next
c_func
(paren
id|dev
comma
op_amp
id|dev-&gt;ts_q
)paren
suffix:semicolon
id|done
suffix:colon
id|spin_unlock
c_func
(paren
op_amp
id|dev-&gt;slock
)paren
suffix:semicolon
)brace
multiline_comment|/* ----------------------------------------------------------- */
multiline_comment|/*&n; * Local variables:&n; * c-basic-offset: 8&n; * End:&n; */
eof
