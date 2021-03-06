multiline_comment|/*&n;    $Id: bttv-vbi.c,v 1.9 2005/01/13 17:22:33 kraxel Exp $&n;&n;    bttv - Bt848 frame grabber driver&n;    vbi interface&n;&n;    (c) 2002 Gerd Knorr &lt;kraxel@bytesex.org&gt;&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;*/
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/moduleparam.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/kdev_t.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &quot;bttvp.h&quot;
DECL|macro|VBI_DEFLINES
mdefine_line|#define VBI_DEFLINES 16
DECL|macro|VBI_MAXLINES
mdefine_line|#define VBI_MAXLINES 32
DECL|variable|vbibufs
r_static
r_int
r_int
id|vbibufs
op_assign
l_int|4
suffix:semicolon
DECL|variable|vbi_debug
r_static
r_int
r_int
id|vbi_debug
op_assign
l_int|0
suffix:semicolon
id|module_param
c_func
(paren
id|vbibufs
comma
r_int
comma
l_int|0444
)paren
suffix:semicolon
id|module_param
c_func
(paren
id|vbi_debug
comma
r_int
comma
l_int|0644
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|vbibufs
comma
l_string|&quot;number of vbi buffers, range 2-32, default 4&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|vbi_debug
comma
l_string|&quot;vbi code debug messages, default is 0 (no)&quot;
)paren
suffix:semicolon
macro_line|#ifdef dprintk
DECL|macro|dprintk
macro_line|# undef dprintk
macro_line|#endif
DECL|macro|dprintk
mdefine_line|#define dprintk(fmt, arg...)&t;if (vbi_debug) &bslash;&n;&t;printk(KERN_DEBUG &quot;bttv%d/vbi: &quot; fmt, btv-&gt;c.nr , ## arg)
multiline_comment|/* ----------------------------------------------------------------------- */
multiline_comment|/* vbi risc code + mm                                                      */
r_static
r_int
DECL|function|vbi_buffer_risc
id|vbi_buffer_risc
c_func
(paren
r_struct
id|bttv
op_star
id|btv
comma
r_struct
id|bttv_buffer
op_star
id|buf
comma
r_int
id|lines
)paren
(brace
r_int
id|bpl
op_assign
l_int|2048
suffix:semicolon
id|bttv_risc_packed
c_func
(paren
id|btv
comma
op_amp
id|buf-&gt;top
comma
id|buf-&gt;vb.dma.sglist
comma
l_int|0
comma
id|bpl
op_minus
l_int|4
comma
l_int|4
comma
id|lines
)paren
suffix:semicolon
id|bttv_risc_packed
c_func
(paren
id|btv
comma
op_amp
id|buf-&gt;bottom
comma
id|buf-&gt;vb.dma.sglist
comma
id|lines
op_star
id|bpl
comma
id|bpl
op_minus
l_int|4
comma
l_int|4
comma
id|lines
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|vbi_buffer_setup
r_static
r_int
id|vbi_buffer_setup
c_func
(paren
r_struct
id|videobuf_queue
op_star
id|q
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
id|bttv_fh
op_star
id|fh
op_assign
id|q-&gt;priv_data
suffix:semicolon
r_struct
id|bttv
op_star
id|btv
op_assign
id|fh-&gt;btv
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
id|size
op_assign
id|fh-&gt;lines
op_star
l_int|2
op_star
l_int|2048
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;setup: lines=%d&bslash;n&quot;
comma
id|fh-&gt;lines
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|vbi_buffer_prepare
r_static
r_int
id|vbi_buffer_prepare
c_func
(paren
r_struct
id|videobuf_queue
op_star
id|q
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
id|bttv_fh
op_star
id|fh
op_assign
id|q-&gt;priv_data
suffix:semicolon
r_struct
id|bttv
op_star
id|btv
op_assign
id|fh-&gt;btv
suffix:semicolon
r_struct
id|bttv_buffer
op_star
id|buf
op_assign
id|container_of
c_func
(paren
id|vb
comma
r_struct
id|bttv_buffer
comma
id|vb
)paren
suffix:semicolon
r_int
id|rc
suffix:semicolon
id|buf-&gt;vb.size
op_assign
id|fh-&gt;lines
op_star
l_int|2
op_star
l_int|2048
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
id|buf-&gt;vb.size
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|STATE_NEEDS_INIT
op_eq
id|buf-&gt;vb.state
)paren
(brace
r_if
c_cond
(paren
l_int|0
op_ne
(paren
id|rc
op_assign
id|videobuf_iolock
c_func
(paren
id|btv-&gt;c.pci
comma
op_amp
id|buf-&gt;vb
comma
l_int|NULL
)paren
)paren
)paren
r_goto
id|fail
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_ne
(paren
id|rc
op_assign
id|vbi_buffer_risc
c_func
(paren
id|btv
comma
id|buf
comma
id|fh-&gt;lines
)paren
)paren
)paren
r_goto
id|fail
suffix:semicolon
)brace
id|buf-&gt;vb.state
op_assign
id|STATE_PREPARED
suffix:semicolon
id|buf-&gt;vb.field
op_assign
id|field
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;buf prepare %p: top=%p bottom=%p field=%s&bslash;n&quot;
comma
id|vb
comma
op_amp
id|buf-&gt;top
comma
op_amp
id|buf-&gt;bottom
comma
id|v4l2_field_names
(braket
id|buf-&gt;vb.field
)braket
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|fail
suffix:colon
id|bttv_dma_free
c_func
(paren
id|btv
comma
id|buf
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
r_static
r_void
DECL|function|vbi_buffer_queue
id|vbi_buffer_queue
c_func
(paren
r_struct
id|videobuf_queue
op_star
id|q
comma
r_struct
id|videobuf_buffer
op_star
id|vb
)paren
(brace
r_struct
id|bttv_fh
op_star
id|fh
op_assign
id|q-&gt;priv_data
suffix:semicolon
r_struct
id|bttv
op_star
id|btv
op_assign
id|fh-&gt;btv
suffix:semicolon
r_struct
id|bttv_buffer
op_star
id|buf
op_assign
id|container_of
c_func
(paren
id|vb
comma
r_struct
id|bttv_buffer
comma
id|vb
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;queue %p&bslash;n&quot;
comma
id|vb
)paren
suffix:semicolon
id|buf-&gt;vb.state
op_assign
id|STATE_QUEUED
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|buf-&gt;vb.queue
comma
op_amp
id|btv-&gt;vcapture
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|NULL
op_eq
id|btv-&gt;cvbi
)paren
(brace
id|fh-&gt;btv-&gt;loop_irq
op_or_assign
l_int|4
suffix:semicolon
id|bttv_set_dma
c_func
(paren
id|btv
comma
l_int|0x0c
)paren
suffix:semicolon
)brace
)brace
DECL|function|vbi_buffer_release
r_static
r_void
id|vbi_buffer_release
c_func
(paren
r_struct
id|videobuf_queue
op_star
id|q
comma
r_struct
id|videobuf_buffer
op_star
id|vb
)paren
(brace
r_struct
id|bttv_fh
op_star
id|fh
op_assign
id|q-&gt;priv_data
suffix:semicolon
r_struct
id|bttv
op_star
id|btv
op_assign
id|fh-&gt;btv
suffix:semicolon
r_struct
id|bttv_buffer
op_star
id|buf
op_assign
id|container_of
c_func
(paren
id|vb
comma
r_struct
id|bttv_buffer
comma
id|vb
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;free %p&bslash;n&quot;
comma
id|vb
)paren
suffix:semicolon
id|bttv_dma_free
c_func
(paren
id|fh-&gt;btv
comma
id|buf
)paren
suffix:semicolon
)brace
DECL|variable|bttv_vbi_qops
r_struct
id|videobuf_queue_ops
id|bttv_vbi_qops
op_assign
(brace
dot
id|buf_setup
op_assign
id|vbi_buffer_setup
comma
dot
id|buf_prepare
op_assign
id|vbi_buffer_prepare
comma
dot
id|buf_queue
op_assign
id|vbi_buffer_queue
comma
dot
id|buf_release
op_assign
id|vbi_buffer_release
comma
)brace
suffix:semicolon
multiline_comment|/* ----------------------------------------------------------------------- */
DECL|function|bttv_vbi_setlines
r_void
id|bttv_vbi_setlines
c_func
(paren
r_struct
id|bttv_fh
op_star
id|fh
comma
r_struct
id|bttv
op_star
id|btv
comma
r_int
id|lines
)paren
(brace
r_int
id|vdelay
suffix:semicolon
r_if
c_cond
(paren
id|lines
OL
l_int|1
)paren
id|lines
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|lines
OG
id|VBI_MAXLINES
)paren
id|lines
op_assign
id|VBI_MAXLINES
suffix:semicolon
id|fh-&gt;lines
op_assign
id|lines
suffix:semicolon
id|vdelay
op_assign
id|btread
c_func
(paren
id|BT848_E_VDELAY_LO
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vdelay
OL
id|lines
op_star
l_int|2
)paren
(brace
id|vdelay
op_assign
id|lines
op_star
l_int|2
suffix:semicolon
id|btwrite
c_func
(paren
id|vdelay
comma
id|BT848_E_VDELAY_LO
)paren
suffix:semicolon
id|btwrite
c_func
(paren
id|vdelay
comma
id|BT848_O_VDELAY_LO
)paren
suffix:semicolon
)brace
)brace
DECL|function|bttv_vbi_try_fmt
r_void
id|bttv_vbi_try_fmt
c_func
(paren
r_struct
id|bttv_fh
op_star
id|fh
comma
r_struct
id|v4l2_format
op_star
id|f
)paren
(brace
r_const
r_struct
id|bttv_tvnorm
op_star
id|tvnorm
suffix:semicolon
id|u32
id|start0
comma
id|start1
suffix:semicolon
id|s32
id|count0
comma
id|count1
comma
id|count
suffix:semicolon
id|tvnorm
op_assign
op_amp
id|bttv_tvnorms
(braket
id|fh-&gt;btv-&gt;tvnorm
)braket
suffix:semicolon
id|f-&gt;type
op_assign
id|V4L2_BUF_TYPE_VBI_CAPTURE
suffix:semicolon
id|f-&gt;fmt.vbi.sampling_rate
op_assign
id|tvnorm-&gt;Fsc
suffix:semicolon
id|f-&gt;fmt.vbi.samples_per_line
op_assign
l_int|2048
suffix:semicolon
id|f-&gt;fmt.vbi.sample_format
op_assign
id|V4L2_PIX_FMT_GREY
suffix:semicolon
id|f-&gt;fmt.vbi.offset
op_assign
l_int|244
suffix:semicolon
id|f-&gt;fmt.vbi.flags
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|fh-&gt;btv-&gt;tvnorm
)paren
(brace
r_case
l_int|1
suffix:colon
multiline_comment|/* NTSC */
id|start0
op_assign
l_int|10
suffix:semicolon
id|start1
op_assign
l_int|273
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0
suffix:colon
multiline_comment|/* PAL */
r_case
l_int|2
suffix:colon
multiline_comment|/* SECAM */
r_default
suffix:colon
id|start0
op_assign
l_int|7
suffix:semicolon
id|start1
op_assign
l_int|320
suffix:semicolon
)brace
id|count0
op_assign
(paren
id|f-&gt;fmt.vbi.start
(braket
l_int|0
)braket
op_plus
id|f-&gt;fmt.vbi.count
(braket
l_int|0
)braket
)paren
op_minus
id|start0
suffix:semicolon
id|count1
op_assign
(paren
id|f-&gt;fmt.vbi.start
(braket
l_int|1
)braket
op_plus
id|f-&gt;fmt.vbi.count
(braket
l_int|1
)braket
)paren
op_minus
id|start1
suffix:semicolon
id|count
op_assign
id|max
c_func
(paren
id|count0
comma
id|count1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|count
OG
id|VBI_MAXLINES
)paren
id|count
op_assign
id|VBI_MAXLINES
suffix:semicolon
r_if
c_cond
(paren
id|count
OL
l_int|1
)paren
id|count
op_assign
l_int|1
suffix:semicolon
id|f-&gt;fmt.vbi.start
(braket
l_int|0
)braket
op_assign
id|start0
suffix:semicolon
id|f-&gt;fmt.vbi.start
(braket
l_int|1
)braket
op_assign
id|start1
suffix:semicolon
id|f-&gt;fmt.vbi.count
(braket
l_int|0
)braket
op_assign
id|count
suffix:semicolon
id|f-&gt;fmt.vbi.count
(braket
l_int|1
)braket
op_assign
id|count
suffix:semicolon
)brace
DECL|function|bttv_vbi_get_fmt
r_void
id|bttv_vbi_get_fmt
c_func
(paren
r_struct
id|bttv_fh
op_star
id|fh
comma
r_struct
id|v4l2_format
op_star
id|f
)paren
(brace
r_const
r_struct
id|bttv_tvnorm
op_star
id|tvnorm
suffix:semicolon
id|tvnorm
op_assign
op_amp
id|bttv_tvnorms
(braket
id|fh-&gt;btv-&gt;tvnorm
)braket
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
id|V4L2_BUF_TYPE_VBI_CAPTURE
suffix:semicolon
id|f-&gt;fmt.vbi.sampling_rate
op_assign
id|tvnorm-&gt;Fsc
suffix:semicolon
id|f-&gt;fmt.vbi.samples_per_line
op_assign
l_int|2048
suffix:semicolon
id|f-&gt;fmt.vbi.sample_format
op_assign
id|V4L2_PIX_FMT_GREY
suffix:semicolon
id|f-&gt;fmt.vbi.offset
op_assign
l_int|244
suffix:semicolon
id|f-&gt;fmt.vbi.count
(braket
l_int|0
)braket
op_assign
id|fh-&gt;lines
suffix:semicolon
id|f-&gt;fmt.vbi.count
(braket
l_int|1
)braket
op_assign
id|fh-&gt;lines
suffix:semicolon
id|f-&gt;fmt.vbi.flags
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|fh-&gt;btv-&gt;tvnorm
)paren
(brace
r_case
l_int|1
suffix:colon
multiline_comment|/* NTSC */
id|f-&gt;fmt.vbi.start
(braket
l_int|0
)braket
op_assign
l_int|10
suffix:semicolon
id|f-&gt;fmt.vbi.start
(braket
l_int|1
)braket
op_assign
l_int|273
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0
suffix:colon
multiline_comment|/* PAL */
r_case
l_int|2
suffix:colon
multiline_comment|/* SECAM */
r_default
suffix:colon
id|f-&gt;fmt.vbi.start
(braket
l_int|0
)braket
op_assign
l_int|7
suffix:semicolon
id|f-&gt;fmt.vbi.start
(braket
l_int|1
)braket
op_assign
l_int|319
suffix:semicolon
)brace
)brace
multiline_comment|/* ----------------------------------------------------------------------- */
multiline_comment|/*&n; * Local variables:&n; * c-basic-offset: 8&n; * End:&n; */
eof
