multiline_comment|/*&n; * device driver for philips saa7134 based TV cards&n; * video4linux video interface&n; *&n; * (c) 2001,02 Gerd Knorr &lt;kraxel@bytesex.org&gt; [SuSE Labs]&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &quot;saa7134-reg.h&quot;
macro_line|#include &quot;saa7134.h&quot;
multiline_comment|/* ------------------------------------------------------------------ */
DECL|variable|vbi_debug
r_static
r_int
r_int
id|vbi_debug
op_assign
l_int|0
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|vbi_debug
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|vbi_debug
comma
l_string|&quot;enable debug messages [vbi]&quot;
)paren
suffix:semicolon
DECL|variable|vbibufs
r_static
r_int
r_int
id|vbibufs
op_assign
l_int|4
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|vbibufs
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|vbibufs
comma
l_string|&quot;number of vbi buffers, range 2-32&quot;
)paren
suffix:semicolon
DECL|macro|dprintk
mdefine_line|#define dprintk(fmt, arg...)&t;if (vbi_debug) &bslash;&n;&t;printk(KERN_DEBUG &quot;%s/vbi: &quot; fmt, dev-&gt;name, ## arg)
multiline_comment|/* ------------------------------------------------------------------ */
DECL|macro|VBI_LINE_COUNT
mdefine_line|#define VBI_LINE_COUNT     16
DECL|macro|VBI_LINE_LENGTH
mdefine_line|#define VBI_LINE_LENGTH  2048
DECL|macro|VBI_SCALE
mdefine_line|#define VBI_SCALE       0x200
DECL|function|task_init
r_static
r_void
id|task_init
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
r_int
id|task
)paren
(brace
r_struct
id|saa7134_tvnorm
op_star
id|norm
op_assign
id|dev-&gt;tvnorm
suffix:semicolon
multiline_comment|/* setup video scaler */
id|saa_writeb
c_func
(paren
id|SAA7134_VBI_H_START1
c_func
(paren
id|task
)paren
comma
id|norm-&gt;h_start
op_amp
l_int|0xff
)paren
suffix:semicolon
id|saa_writeb
c_func
(paren
id|SAA7134_VBI_H_START2
c_func
(paren
id|task
)paren
comma
id|norm-&gt;h_start
op_rshift
l_int|8
)paren
suffix:semicolon
id|saa_writeb
c_func
(paren
id|SAA7134_VBI_H_STOP1
c_func
(paren
id|task
)paren
comma
id|norm-&gt;h_stop
op_amp
l_int|0xff
)paren
suffix:semicolon
id|saa_writeb
c_func
(paren
id|SAA7134_VBI_H_STOP2
c_func
(paren
id|task
)paren
comma
id|norm-&gt;h_stop
op_rshift
l_int|8
)paren
suffix:semicolon
id|saa_writeb
c_func
(paren
id|SAA7134_VBI_V_START1
c_func
(paren
id|task
)paren
comma
id|norm-&gt;vbi_v_start
op_amp
l_int|0xff
)paren
suffix:semicolon
id|saa_writeb
c_func
(paren
id|SAA7134_VBI_V_START2
c_func
(paren
id|task
)paren
comma
id|norm-&gt;vbi_v_start
op_rshift
l_int|8
)paren
suffix:semicolon
id|saa_writeb
c_func
(paren
id|SAA7134_VBI_V_STOP1
c_func
(paren
id|task
)paren
comma
id|norm-&gt;vbi_v_stop
op_amp
l_int|0xff
)paren
suffix:semicolon
id|saa_writeb
c_func
(paren
id|SAA7134_VBI_V_STOP2
c_func
(paren
id|task
)paren
comma
id|norm-&gt;vbi_v_stop
op_rshift
l_int|8
)paren
suffix:semicolon
id|saa_writeb
c_func
(paren
id|SAA7134_VBI_H_SCALE_INC1
c_func
(paren
id|task
)paren
comma
id|VBI_SCALE
op_amp
l_int|0xff
)paren
suffix:semicolon
id|saa_writeb
c_func
(paren
id|SAA7134_VBI_H_SCALE_INC2
c_func
(paren
id|task
)paren
comma
id|VBI_SCALE
op_rshift
l_int|8
)paren
suffix:semicolon
id|saa_writeb
c_func
(paren
id|SAA7134_VBI_PHASE_OFFSET_LUMA
c_func
(paren
id|task
)paren
comma
l_int|0x00
)paren
suffix:semicolon
id|saa_writeb
c_func
(paren
id|SAA7134_VBI_PHASE_OFFSET_CHROMA
c_func
(paren
id|task
)paren
comma
l_int|0x00
)paren
suffix:semicolon
id|saa_writeb
c_func
(paren
id|SAA7134_VBI_H_LEN1
c_func
(paren
id|task
)paren
comma
id|buf-&gt;vb.width
op_amp
l_int|0xff
)paren
suffix:semicolon
id|saa_writeb
c_func
(paren
id|SAA7134_VBI_H_LEN2
c_func
(paren
id|task
)paren
comma
id|buf-&gt;vb.width
op_rshift
l_int|8
)paren
suffix:semicolon
id|saa_writeb
c_func
(paren
id|SAA7134_VBI_V_LEN1
c_func
(paren
id|task
)paren
comma
id|buf-&gt;vb.height
op_amp
l_int|0xff
)paren
suffix:semicolon
id|saa_writeb
c_func
(paren
id|SAA7134_VBI_V_LEN2
c_func
(paren
id|task
)paren
comma
id|buf-&gt;vb.height
op_rshift
l_int|8
)paren
suffix:semicolon
id|saa_andorb
c_func
(paren
id|SAA7134_DATA_PATH
c_func
(paren
id|task
)paren
comma
l_int|0xc0
comma
l_int|0x00
)paren
suffix:semicolon
)brace
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
r_int
r_int
id|control
comma
id|base
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
id|buf-&gt;top_seen
op_assign
l_int|0
suffix:semicolon
id|task_init
c_func
(paren
id|dev
comma
id|buf
comma
id|TASK_A
)paren
suffix:semicolon
id|task_init
c_func
(paren
id|dev
comma
id|buf
comma
id|TASK_B
)paren
suffix:semicolon
id|saa_writeb
c_func
(paren
id|SAA7134_OFMT_DATA_A
comma
l_int|0x06
)paren
suffix:semicolon
id|saa_writeb
c_func
(paren
id|SAA7134_OFMT_DATA_B
comma
l_int|0x06
)paren
suffix:semicolon
multiline_comment|/* DMA: setup channel 2+3 (= VBI Task A+B) */
id|base
op_assign
id|saa7134_buffer_base
c_func
(paren
id|buf
)paren
suffix:semicolon
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
id|saa_writel
c_func
(paren
id|SAA7134_RS_BA1
c_func
(paren
l_int|2
)paren
comma
id|base
)paren
suffix:semicolon
id|saa_writel
c_func
(paren
id|SAA7134_RS_BA2
c_func
(paren
l_int|2
)paren
comma
id|base
op_plus
id|buf-&gt;vb.size
op_div
l_int|2
)paren
suffix:semicolon
id|saa_writel
c_func
(paren
id|SAA7134_RS_PITCH
c_func
(paren
l_int|2
)paren
comma
id|buf-&gt;vb.width
)paren
suffix:semicolon
id|saa_writel
c_func
(paren
id|SAA7134_RS_CONTROL
c_func
(paren
l_int|2
)paren
comma
id|control
)paren
suffix:semicolon
id|saa_writel
c_func
(paren
id|SAA7134_RS_BA1
c_func
(paren
l_int|3
)paren
comma
id|base
)paren
suffix:semicolon
id|saa_writel
c_func
(paren
id|SAA7134_RS_BA2
c_func
(paren
l_int|3
)paren
comma
id|base
op_plus
id|buf-&gt;vb.size
op_div
l_int|2
)paren
suffix:semicolon
id|saa_writel
c_func
(paren
id|SAA7134_RS_PITCH
c_func
(paren
l_int|3
)paren
comma
id|buf-&gt;vb.width
)paren
suffix:semicolon
id|saa_writel
c_func
(paren
id|SAA7134_RS_CONTROL
c_func
(paren
l_int|3
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
id|dev-&gt;vbi_q.timeout
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
id|saa7134_fh
op_star
id|fh
op_assign
id|file-&gt;private_data
suffix:semicolon
r_struct
id|saa7134_dev
op_star
id|dev
op_assign
id|fh-&gt;dev
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
r_struct
id|saa7134_tvnorm
op_star
id|norm
op_assign
id|dev-&gt;tvnorm
suffix:semicolon
r_int
r_int
id|lines
comma
id|llength
comma
id|size
suffix:semicolon
r_int
id|err
suffix:semicolon
id|lines
op_assign
id|norm-&gt;vbi_v_stop
op_minus
id|norm-&gt;vbi_v_start
op_plus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|lines
OG
id|VBI_LINE_COUNT
)paren
id|lines
op_assign
id|VBI_LINE_COUNT
suffix:semicolon
macro_line|#if 1
id|llength
op_assign
id|VBI_LINE_LENGTH
suffix:semicolon
macro_line|#else
id|llength
op_assign
(paren
id|norm-&gt;h_stop
op_minus
id|norm-&gt;h_start
op_plus
l_int|1
)paren
op_star
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|llength
OG
id|VBI_LINE_LENGTH
)paren
id|llength
op_assign
id|VBI_LINE_LENGTH
suffix:semicolon
macro_line|#endif
id|size
op_assign
id|lines
op_star
id|llength
op_star
l_int|2
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
id|saa7134_dma_free
c_func
(paren
id|dev
comma
id|buf
)paren
suffix:semicolon
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
id|fh-&gt;pt_vbi
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
r_int
op_star
id|count
comma
r_int
r_int
op_star
id|size
)paren
(brace
r_struct
id|saa7134_fh
op_star
id|fh
op_assign
id|file-&gt;private_data
suffix:semicolon
r_struct
id|saa7134_dev
op_star
id|dev
op_assign
id|fh-&gt;dev
suffix:semicolon
r_int
id|llength
comma
id|lines
suffix:semicolon
id|lines
op_assign
id|dev-&gt;tvnorm-&gt;vbi_v_stop
op_minus
id|dev-&gt;tvnorm-&gt;vbi_v_start
op_plus
l_int|1
suffix:semicolon
macro_line|#if 1
id|llength
op_assign
id|VBI_LINE_LENGTH
suffix:semicolon
macro_line|#else
id|llength
op_assign
(paren
id|norm-&gt;h_stop
op_minus
id|norm-&gt;h_start
op_plus
l_int|1
)paren
op_star
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|llength
OG
id|VBI_LINE_LENGTH
)paren
id|llength
op_assign
id|VBI_LINE_LENGTH
suffix:semicolon
macro_line|#endif
op_star
id|size
op_assign
id|lines
op_star
id|llength
op_star
l_int|2
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
id|vbibufs
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
id|saa7134_fh
op_star
id|fh
op_assign
id|file-&gt;private_data
suffix:semicolon
r_struct
id|saa7134_dev
op_star
id|dev
op_assign
id|fh-&gt;dev
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
id|dev-&gt;vbi_q
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
id|saa7134_fh
op_star
id|fh
op_assign
id|file-&gt;private_data
suffix:semicolon
r_struct
id|saa7134_dev
op_star
id|dev
op_assign
id|fh-&gt;dev
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
DECL|variable|saa7134_vbi_qops
r_struct
id|videobuf_queue_ops
id|saa7134_vbi_qops
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
DECL|function|saa7134_vbi_init
r_int
id|saa7134_vbi_init
c_func
(paren
r_struct
id|saa7134_dev
op_star
id|dev
)paren
(brace
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|dev-&gt;vbi_q.queue
)paren
suffix:semicolon
id|init_timer
c_func
(paren
op_amp
id|dev-&gt;vbi_q.timeout
)paren
suffix:semicolon
id|dev-&gt;vbi_q.timeout.function
op_assign
id|saa7134_buffer_timeout
suffix:semicolon
id|dev-&gt;vbi_q.timeout.data
op_assign
(paren
r_int
r_int
)paren
(paren
op_amp
id|dev-&gt;vbi_q
)paren
suffix:semicolon
id|dev-&gt;vbi_q.dev
op_assign
id|dev
suffix:semicolon
r_if
c_cond
(paren
id|vbibufs
OL
l_int|2
)paren
id|vbibufs
op_assign
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|vbibufs
OG
id|VIDEO_MAX_FRAME
)paren
id|vbibufs
op_assign
id|VIDEO_MAX_FRAME
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|saa7134_vbi_fini
r_int
id|saa7134_vbi_fini
c_func
(paren
r_struct
id|saa7134_dev
op_star
id|dev
)paren
(brace
multiline_comment|/* nothing */
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|saa7134_irq_vbi_done
r_void
id|saa7134_irq_vbi_done
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
id|dev-&gt;vbi_q.curr
)paren
(brace
id|dev-&gt;vbi_fieldcount
op_increment
suffix:semicolon
multiline_comment|/* make sure we have seen both fields */
r_if
c_cond
(paren
(paren
id|status
op_amp
l_int|0x10
)paren
op_eq
l_int|0x00
)paren
(brace
id|dev-&gt;vbi_q.curr-&gt;top_seen
op_assign
l_int|1
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;vbi_q.curr-&gt;top_seen
)paren
r_goto
id|done
suffix:semicolon
id|dev-&gt;vbi_q.curr-&gt;vb.field_count
op_assign
id|dev-&gt;vbi_fieldcount
suffix:semicolon
id|saa7134_buffer_finish
c_func
(paren
id|dev
comma
op_amp
id|dev-&gt;vbi_q
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
id|dev-&gt;vbi_q
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
