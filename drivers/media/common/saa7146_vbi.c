macro_line|#include &lt;media/saa7146_vv.h&gt;
macro_line|#if LINUX_VERSION_CODE &lt; KERNEL_VERSION(2,5,51)
DECL|macro|KBUILD_MODNAME
mdefine_line|#define KBUILD_MODNAME saa7146
macro_line|#endif
DECL|variable|vbi_pixel_to_capture
r_static
r_int
id|vbi_pixel_to_capture
op_assign
l_int|720
op_star
l_int|2
suffix:semicolon
r_static
DECL|function|vbi_workaround
r_int
id|vbi_workaround
c_func
(paren
r_struct
id|saa7146_dev
op_star
id|dev
)paren
(brace
r_struct
id|saa7146_vv
op_star
id|vv
op_assign
id|dev-&gt;vv_data
suffix:semicolon
id|u32
op_star
id|cpu
suffix:semicolon
id|dma_addr_t
id|dma_addr
suffix:semicolon
r_int
id|i
comma
id|index
suffix:semicolon
id|DECLARE_WAITQUEUE
c_func
(paren
id|wait
comma
id|current
)paren
suffix:semicolon
id|DEB_VBI
c_func
(paren
(paren
l_string|&quot;dev:%p&bslash;n&quot;
comma
id|dev
)paren
)paren
suffix:semicolon
multiline_comment|/* once again, a bug in the saa7146: the brs acquisition&n;&t;   is buggy and especially the BXO-counter does not work&n;&t;   as specified. there is this workaround, but please&n;&t;   don&squot;t let me explain it. ;-) */
id|cpu
op_assign
id|pci_alloc_consistent
c_func
(paren
id|dev-&gt;pci
comma
l_int|4096
comma
op_amp
id|dma_addr
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|NULL
op_eq
id|cpu
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
multiline_comment|/* setup some basic programming, just for the workaround */
id|saa7146_write
c_func
(paren
id|dev
comma
id|BASE_EVEN3
comma
id|dma_addr
)paren
suffix:semicolon
id|saa7146_write
c_func
(paren
id|dev
comma
id|BASE_ODD3
comma
id|dma_addr
op_plus
id|vbi_pixel_to_capture
)paren
suffix:semicolon
id|saa7146_write
c_func
(paren
id|dev
comma
id|PROT_ADDR3
comma
id|dma_addr
op_plus
l_int|4096
)paren
suffix:semicolon
id|saa7146_write
c_func
(paren
id|dev
comma
id|PITCH3
comma
id|vbi_pixel_to_capture
)paren
suffix:semicolon
id|saa7146_write
c_func
(paren
id|dev
comma
id|BASE_PAGE3
comma
l_int|0x0
)paren
suffix:semicolon
id|saa7146_write
c_func
(paren
id|dev
comma
id|NUM_LINE_BYTE3
comma
(paren
l_int|2
op_lshift
l_int|16
)paren
op_or
(paren
(paren
id|vbi_pixel_to_capture
)paren
op_lshift
l_int|0
)paren
)paren
suffix:semicolon
id|saa7146_write
c_func
(paren
id|dev
comma
id|MC2
comma
id|MASK_04
op_or
id|MASK_20
)paren
suffix:semicolon
multiline_comment|/* we have to do the workaround two times to be sure that&n;&t;   everything is ok */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|2
suffix:semicolon
id|i
op_increment
)paren
(brace
multiline_comment|/* indicate to the irq handler that we do the workaround */
id|saa7146_write
c_func
(paren
id|dev
comma
id|MC2
comma
id|MASK_31
op_or
id|MASK_15
)paren
suffix:semicolon
id|saa7146_write
c_func
(paren
id|dev
comma
id|NUM_LINE_BYTE3
comma
(paren
l_int|1
op_lshift
l_int|16
)paren
op_or
(paren
l_int|2
op_lshift
l_int|0
)paren
)paren
suffix:semicolon
id|saa7146_write
c_func
(paren
id|dev
comma
id|MC2
comma
id|MASK_04
op_or
id|MASK_20
)paren
suffix:semicolon
id|index
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* load brs-control register */
id|dev-&gt;rps1
(braket
id|index
op_increment
)braket
op_assign
id|CMD_WR_REG
op_or
(paren
l_int|1
op_lshift
l_int|8
)paren
op_or
(paren
id|BRS_CTRL
op_div
l_int|4
)paren
suffix:semicolon
multiline_comment|/* BXO = 1h, BRS to outbound */
id|dev-&gt;rps1
(braket
id|index
op_increment
)braket
op_assign
l_int|0xc000008c
suffix:semicolon
multiline_comment|/* wait for vbi_a */
id|dev-&gt;rps1
(braket
id|index
op_increment
)braket
op_assign
id|CMD_PAUSE
op_or
id|MASK_10
suffix:semicolon
multiline_comment|/* upload brs */
id|dev-&gt;rps1
(braket
id|index
op_increment
)braket
op_assign
id|CMD_UPLOAD
op_or
id|MASK_08
suffix:semicolon
multiline_comment|/* load brs-control register */
id|dev-&gt;rps1
(braket
id|index
op_increment
)braket
op_assign
id|CMD_WR_REG
op_or
(paren
l_int|1
op_lshift
l_int|8
)paren
op_or
(paren
id|BRS_CTRL
op_div
l_int|4
)paren
suffix:semicolon
multiline_comment|/* BYO = 1, BXO = NQBIL (=1728 for PAL, for NTSC this is 858*2) - NumByte3 (=1440) = 288 */
id|dev-&gt;rps1
(braket
id|index
op_increment
)braket
op_assign
(paren
(paren
l_int|1728
op_minus
(paren
id|vbi_pixel_to_capture
)paren
)paren
op_lshift
l_int|7
)paren
op_or
id|MASK_19
suffix:semicolon
multiline_comment|/* wait for brs_done */
id|dev-&gt;rps1
(braket
id|index
op_increment
)braket
op_assign
id|CMD_PAUSE
op_or
id|MASK_08
suffix:semicolon
multiline_comment|/* upload brs */
id|dev-&gt;rps1
(braket
id|index
op_increment
)braket
op_assign
id|CMD_UPLOAD
op_or
id|MASK_08
suffix:semicolon
multiline_comment|/* load video-dma3 NumLines3 and NumBytes3 */
id|dev-&gt;rps1
(braket
id|index
op_increment
)braket
op_assign
id|CMD_WR_REG
op_or
(paren
l_int|1
op_lshift
l_int|8
)paren
op_or
(paren
id|NUM_LINE_BYTE3
op_div
l_int|4
)paren
suffix:semicolon
multiline_comment|/* dev-&gt;vbi_count*2 lines, 720 pixel (= 1440 Bytes) */
id|dev-&gt;rps1
(braket
id|index
op_increment
)braket
op_assign
(paren
l_int|2
op_lshift
l_int|16
)paren
op_or
(paren
id|vbi_pixel_to_capture
)paren
suffix:semicolon
multiline_comment|/* load brs-control register */
id|dev-&gt;rps1
(braket
id|index
op_increment
)braket
op_assign
id|CMD_WR_REG
op_or
(paren
l_int|1
op_lshift
l_int|8
)paren
op_or
(paren
id|BRS_CTRL
op_div
l_int|4
)paren
suffix:semicolon
multiline_comment|/* Set BRS right: note: this is an experimental value for BXO (=&gt; PAL!) */
id|dev-&gt;rps1
(braket
id|index
op_increment
)braket
op_assign
(paren
l_int|540
op_lshift
l_int|7
)paren
op_or
(paren
l_int|5
op_lshift
l_int|19
)paren
suffix:semicolon
singleline_comment|// 5 == vbi_start  
multiline_comment|/* wait for brs_done */
id|dev-&gt;rps1
(braket
id|index
op_increment
)braket
op_assign
id|CMD_PAUSE
op_or
id|MASK_08
suffix:semicolon
multiline_comment|/* upload brs and video-dma3*/
id|dev-&gt;rps1
(braket
id|index
op_increment
)braket
op_assign
id|CMD_UPLOAD
op_or
id|MASK_08
op_or
id|MASK_04
suffix:semicolon
multiline_comment|/* load mc2 register: enable dma3 */
id|dev-&gt;rps1
(braket
id|index
op_increment
)braket
op_assign
id|CMD_WR_REG
op_or
(paren
l_int|1
op_lshift
l_int|8
)paren
op_or
(paren
id|MC1
op_div
l_int|4
)paren
suffix:semicolon
id|dev-&gt;rps1
(braket
id|index
op_increment
)braket
op_assign
id|MASK_20
op_or
id|MASK_04
suffix:semicolon
multiline_comment|/* generate interrupt */
id|dev-&gt;rps1
(braket
id|index
op_increment
)braket
op_assign
id|CMD_INTERRUPT
suffix:semicolon
multiline_comment|/* stop rps1 */
id|dev-&gt;rps1
(braket
id|index
op_increment
)braket
op_assign
id|CMD_STOP
suffix:semicolon
multiline_comment|/* enable rps1 irqs */
id|IER_ENABLE
c_func
(paren
id|dev
comma
id|MASK_28
)paren
suffix:semicolon
multiline_comment|/* prepare to wait to be woken up by the irq-handler */
id|add_wait_queue
c_func
(paren
op_amp
id|vv-&gt;vbi_wq
comma
op_amp
id|wait
)paren
suffix:semicolon
id|current-&gt;state
op_assign
id|TASK_INTERRUPTIBLE
suffix:semicolon
multiline_comment|/* start rps1 to enable workaround */
id|saa7146_write
c_func
(paren
id|dev
comma
id|RPS_ADDR1
comma
id|virt_to_bus
c_func
(paren
op_amp
id|dev-&gt;rps1
(braket
l_int|0
)braket
)paren
)paren
suffix:semicolon
id|saa7146_write
c_func
(paren
id|dev
comma
id|MC1
comma
(paren
id|MASK_13
op_or
id|MASK_29
)paren
)paren
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
id|DEB_VBI
c_func
(paren
(paren
l_string|&quot;brs bug workaround %d/1.&bslash;n&quot;
comma
id|i
)paren
)paren
suffix:semicolon
id|remove_wait_queue
c_func
(paren
op_amp
id|vv-&gt;vbi_wq
comma
op_amp
id|wait
)paren
suffix:semicolon
id|current-&gt;state
op_assign
id|TASK_RUNNING
suffix:semicolon
multiline_comment|/* disable rps1 irqs */
id|IER_DISABLE
c_func
(paren
id|dev
comma
id|MASK_28
)paren
suffix:semicolon
multiline_comment|/* stop video-dma3 */
id|saa7146_write
c_func
(paren
id|dev
comma
id|MC1
comma
id|MASK_20
)paren
suffix:semicolon
r_if
c_cond
(paren
id|signal_pending
c_func
(paren
id|current
)paren
)paren
(brace
id|DEB_VBI
c_func
(paren
(paren
l_string|&quot;aborted.&bslash;n&quot;
)paren
)paren
suffix:semicolon
multiline_comment|/* stop rps1 for sure */
id|saa7146_write
c_func
(paren
id|dev
comma
id|MC1
comma
id|MASK_29
)paren
suffix:semicolon
id|pci_free_consistent
c_func
(paren
id|dev-&gt;pci
comma
l_int|4096
comma
id|cpu
comma
id|dma_addr
)paren
suffix:semicolon
r_return
op_minus
id|EINTR
suffix:semicolon
)brace
)brace
id|pci_free_consistent
c_func
(paren
id|dev-&gt;pci
comma
l_int|4096
comma
id|cpu
comma
id|dma_addr
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|saa7146_set_vbi_capture
r_void
id|saa7146_set_vbi_capture
c_func
(paren
r_struct
id|saa7146_dev
op_star
id|dev
comma
r_struct
id|saa7146_buf
op_star
id|buf
comma
r_struct
id|saa7146_buf
op_star
id|next
)paren
(brace
r_struct
id|saa7146_vv
op_star
id|vv
op_assign
id|dev-&gt;vv_data
suffix:semicolon
r_struct
id|saa7146_video_dma
id|vdma3
suffix:semicolon
r_int
id|count
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|e_wait
op_assign
id|vv-&gt;current_hps_sync
op_eq
id|SAA7146_HPS_SYNC_PORT_A
ques
c_cond
id|CMD_E_FID_A
suffix:colon
id|CMD_E_FID_B
suffix:semicolon
r_int
r_int
id|o_wait
op_assign
id|vv-&gt;current_hps_sync
op_eq
id|SAA7146_HPS_SYNC_PORT_A
ques
c_cond
id|CMD_O_FID_A
suffix:colon
id|CMD_O_FID_B
suffix:semicolon
multiline_comment|/*&n;&t;vdma3.base_even&t;= (u32)dev-&gt;ov_fb.base+2048*70;&n;&t;vdma3.base_odd&t;= (u32)dev-&gt;ov_fb.base;&n;&t;vdma3.prot_addr&t;= (u32)dev-&gt;ov_fb.base+2048*164;&n;&t;vdma3.pitch&t;= 2048;&n;&t;vdma3.base_page&t;= 0;&n;&t;vdma3.num_line_byte = (64&lt;&lt;16)|((vbi_pixel_to_capture)&lt;&lt;0); // set above!&n;*/
id|vdma3.base_even
op_assign
id|buf-&gt;pt
(braket
l_int|2
)braket
dot
id|offset
suffix:semicolon
id|vdma3.base_odd
op_assign
id|buf-&gt;pt
(braket
l_int|2
)braket
dot
id|offset
op_plus
l_int|16
op_star
id|vbi_pixel_to_capture
suffix:semicolon
id|vdma3.prot_addr
op_assign
id|buf-&gt;pt
(braket
l_int|2
)braket
dot
id|offset
op_plus
l_int|16
op_star
l_int|2
op_star
id|vbi_pixel_to_capture
suffix:semicolon
id|vdma3.pitch
op_assign
id|vbi_pixel_to_capture
suffix:semicolon
id|vdma3.base_page
op_assign
id|buf-&gt;pt
(braket
l_int|2
)braket
dot
id|dma
op_or
id|ME1
suffix:semicolon
id|vdma3.num_line_byte
op_assign
(paren
l_int|16
op_lshift
l_int|16
)paren
op_or
id|vbi_pixel_to_capture
suffix:semicolon
id|saa7146_write_out_dma
c_func
(paren
id|dev
comma
l_int|3
comma
op_amp
id|vdma3
)paren
suffix:semicolon
multiline_comment|/* write beginning of rps-program */
id|count
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* wait for o_fid_a/b / e_fid_a/b toggle only if bit 1 is not set */
multiline_comment|/* we don&squot;t wait here for the first field anymore. this is different from the video&n;&t;   capture and might cause that the first buffer is only half filled (with only&n;&t;   one field). but since this is some sort of streaming data, this is not that negative.&n;&t;   but by doing this, we can use the whole engine from video-buf.c... */
multiline_comment|/*&n;&t;dev-&gt;rps1[ count++ ] = CMD_PAUSE | CMD_OAN | CMD_SIG1 | e_wait;&n;&t;dev-&gt;rps1[ count++ ] = CMD_PAUSE | CMD_OAN | CMD_SIG1 | o_wait;&n;*/
multiline_comment|/* set bit 1 */
id|dev-&gt;rps1
(braket
id|count
op_increment
)braket
op_assign
id|CMD_WR_REG
op_or
(paren
l_int|1
op_lshift
l_int|8
)paren
op_or
(paren
id|MC2
op_div
l_int|4
)paren
suffix:semicolon
id|dev-&gt;rps1
(braket
id|count
op_increment
)braket
op_assign
id|MASK_28
op_or
id|MASK_12
suffix:semicolon
multiline_comment|/* turn on video-dma3 */
id|dev-&gt;rps1
(braket
id|count
op_increment
)braket
op_assign
id|CMD_WR_REG_MASK
op_or
(paren
id|MC1
op_div
l_int|4
)paren
suffix:semicolon
id|dev-&gt;rps1
(braket
id|count
op_increment
)braket
op_assign
id|MASK_04
op_or
id|MASK_20
suffix:semicolon
multiline_comment|/* =&gt; mask */
id|dev-&gt;rps1
(braket
id|count
op_increment
)braket
op_assign
id|MASK_04
op_or
id|MASK_20
suffix:semicolon
multiline_comment|/* =&gt; values */
multiline_comment|/* wait for o_fid_a/b / e_fid_a/b toggle */
id|dev-&gt;rps1
(braket
id|count
op_increment
)braket
op_assign
id|CMD_PAUSE
op_or
id|o_wait
suffix:semicolon
id|dev-&gt;rps1
(braket
id|count
op_increment
)braket
op_assign
id|CMD_PAUSE
op_or
id|e_wait
suffix:semicolon
multiline_comment|/* generate interrupt */
id|dev-&gt;rps1
(braket
id|count
op_increment
)braket
op_assign
id|CMD_INTERRUPT
suffix:semicolon
multiline_comment|/* stop */
id|dev-&gt;rps1
(braket
id|count
op_increment
)braket
op_assign
id|CMD_STOP
suffix:semicolon
multiline_comment|/* enable rps1 irqs */
id|IER_ENABLE
c_func
(paren
id|dev
comma
id|MASK_28
)paren
suffix:semicolon
multiline_comment|/* write the address of the rps-program */
id|saa7146_write
c_func
(paren
id|dev
comma
id|RPS_ADDR1
comma
id|virt_to_bus
c_func
(paren
op_amp
id|dev-&gt;rps1
(braket
l_int|0
)braket
)paren
)paren
suffix:semicolon
multiline_comment|/* turn on rps */
id|saa7146_write
c_func
(paren
id|dev
comma
id|MC1
comma
(paren
id|MASK_13
op_or
id|MASK_29
)paren
)paren
suffix:semicolon
)brace
r_static
DECL|function|buffer_activate
r_int
id|buffer_activate
c_func
(paren
r_struct
id|saa7146_dev
op_star
id|dev
comma
r_struct
id|saa7146_buf
op_star
id|buf
comma
r_struct
id|saa7146_buf
op_star
id|next
)paren
(brace
r_struct
id|saa7146_vv
op_star
id|vv
op_assign
id|dev-&gt;vv_data
suffix:semicolon
id|buf-&gt;vb.state
op_assign
id|STATE_ACTIVE
suffix:semicolon
id|DEB_VBI
c_func
(paren
(paren
l_string|&quot;dev:%p, buf:%p, next:%p&bslash;n&quot;
comma
id|dev
comma
id|buf
comma
id|next
)paren
)paren
suffix:semicolon
id|saa7146_set_vbi_capture
c_func
(paren
id|dev
comma
id|buf
comma
id|next
)paren
suffix:semicolon
id|mod_timer
c_func
(paren
op_amp
id|vv-&gt;vbi_q.timeout
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
r_static
DECL|function|buffer_prepare
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
id|saa7146_fh
op_star
id|fh
op_assign
id|file-&gt;private_data
suffix:semicolon
r_struct
id|saa7146_dev
op_star
id|dev
op_assign
id|fh-&gt;dev
suffix:semicolon
r_struct
id|saa7146_buf
op_star
id|buf
op_assign
(paren
r_struct
id|saa7146_buf
op_star
)paren
id|vb
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
r_int
id|lines
comma
id|llength
comma
id|size
suffix:semicolon
id|lines
op_assign
l_int|16
op_star
l_int|2
suffix:semicolon
multiline_comment|/* 2 fields */
id|llength
op_assign
id|vbi_pixel_to_capture
suffix:semicolon
id|size
op_assign
id|lines
op_star
id|llength
suffix:semicolon
id|DEB_VBI
c_func
(paren
(paren
l_string|&quot;vb:%p&bslash;n&quot;
comma
id|vb
)paren
)paren
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
(brace
id|DEB_VBI
c_func
(paren
(paren
l_string|&quot;size mismatch.&bslash;n&quot;
)paren
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
id|buf-&gt;vb.size
op_ne
id|size
)paren
id|saa7146_dma_free
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
id|buf-&gt;vb.field
op_assign
id|field
suffix:semicolon
singleline_comment|// FIXME: check this
id|saa7146_pgtable_free
c_func
(paren
id|dev-&gt;pci
comma
op_amp
id|buf-&gt;pt
(braket
l_int|2
)braket
)paren
suffix:semicolon
id|saa7146_pgtable_alloc
c_func
(paren
id|dev-&gt;pci
comma
op_amp
id|buf-&gt;pt
(braket
l_int|2
)braket
)paren
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
id|saa7146_pgtable_build_single
c_func
(paren
id|dev-&gt;pci
comma
op_amp
id|buf-&gt;pt
(braket
l_int|2
)braket
comma
id|buf-&gt;vb.dma.sglist
comma
id|buf-&gt;vb.dma.sglen
)paren
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
r_return
l_int|0
suffix:semicolon
id|oops
suffix:colon
id|DEB_VBI
c_func
(paren
(paren
l_string|&quot;error out.&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|saa7146_dma_free
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
r_int
id|llength
comma
id|lines
suffix:semicolon
id|lines
op_assign
l_int|16
op_star
l_int|2
suffix:semicolon
multiline_comment|/* 2 fields */
id|llength
op_assign
id|vbi_pixel_to_capture
suffix:semicolon
op_star
id|size
op_assign
id|lines
op_star
id|llength
suffix:semicolon
op_star
id|count
op_assign
l_int|2
suffix:semicolon
id|DEB_VBI
c_func
(paren
(paren
l_string|&quot;count:%d, size:%d&bslash;n&quot;
comma
op_star
id|count
comma
op_star
id|size
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
DECL|function|buffer_queue
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
id|saa7146_fh
op_star
id|fh
op_assign
id|file-&gt;private_data
suffix:semicolon
r_struct
id|saa7146_dev
op_star
id|dev
op_assign
id|fh-&gt;dev
suffix:semicolon
r_struct
id|saa7146_vv
op_star
id|vv
op_assign
id|dev-&gt;vv_data
suffix:semicolon
r_struct
id|saa7146_buf
op_star
id|buf
op_assign
(paren
r_struct
id|saa7146_buf
op_star
)paren
id|vb
suffix:semicolon
id|DEB_VBI
c_func
(paren
(paren
l_string|&quot;vb:%p&bslash;n&quot;
comma
id|vb
)paren
)paren
suffix:semicolon
id|saa7146_buffer_queue
c_func
(paren
id|dev
comma
op_amp
id|vv-&gt;vbi_q
comma
id|buf
)paren
suffix:semicolon
)brace
r_static
DECL|function|buffer_release
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
id|saa7146_fh
op_star
id|fh
op_assign
id|file-&gt;private_data
suffix:semicolon
r_struct
id|saa7146_dev
op_star
id|dev
op_assign
id|fh-&gt;dev
suffix:semicolon
r_struct
id|saa7146_buf
op_star
id|buf
op_assign
(paren
r_struct
id|saa7146_buf
op_star
)paren
id|vb
suffix:semicolon
id|DEB_VBI
c_func
(paren
(paren
l_string|&quot;vb:%p&bslash;n&quot;
comma
id|vb
)paren
)paren
suffix:semicolon
id|saa7146_dma_free
c_func
(paren
id|dev
comma
id|buf
)paren
suffix:semicolon
)brace
r_static
DECL|variable|vbi_qops
r_struct
id|videobuf_queue_ops
id|vbi_qops
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
r_static
DECL|function|vbi_stop
r_void
id|vbi_stop
c_func
(paren
r_struct
id|saa7146_fh
op_star
id|fh
)paren
(brace
r_struct
id|saa7146_dev
op_star
id|dev
op_assign
id|fh-&gt;dev
suffix:semicolon
r_struct
id|saa7146_vv
op_star
id|vv
op_assign
id|dev-&gt;vv_data
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|DEB_VBI
c_func
(paren
(paren
l_string|&quot;dev:%p, fh:%p&bslash;n&quot;
comma
id|dev
comma
id|fh
)paren
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|dev-&gt;slock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/* disable rps1  */
id|saa7146_write
c_func
(paren
id|dev
comma
id|MC1
comma
id|MASK_29
)paren
suffix:semicolon
multiline_comment|/* disable rps1 irqs */
id|IER_DISABLE
c_func
(paren
id|dev
comma
id|MASK_28
)paren
suffix:semicolon
multiline_comment|/* shut down dma 3 transfers */
id|saa7146_write
c_func
(paren
id|dev
comma
id|MC1
comma
id|MASK_20
)paren
suffix:semicolon
id|vv-&gt;vbi_streaming
op_assign
l_int|NULL
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|dev-&gt;slock
comma
id|flags
)paren
suffix:semicolon
)brace
r_static
DECL|function|vbi_read_timeout
r_void
id|vbi_read_timeout
c_func
(paren
r_int
r_int
id|data
)paren
(brace
r_struct
id|saa7146_fh
op_star
id|fh
op_assign
(paren
r_struct
id|saa7146_fh
op_star
)paren
id|data
suffix:semicolon
r_struct
id|saa7146_dev
op_star
id|dev
op_assign
id|fh-&gt;dev
suffix:semicolon
id|DEB_VBI
c_func
(paren
(paren
l_string|&quot;dev:%p, fh:%p&bslash;n&quot;
comma
id|dev
comma
id|fh
)paren
)paren
suffix:semicolon
id|vbi_stop
c_func
(paren
id|fh
)paren
suffix:semicolon
)brace
r_static
DECL|function|vbi_init
r_void
id|vbi_init
c_func
(paren
r_struct
id|saa7146_dev
op_star
id|dev
comma
r_struct
id|saa7146_vv
op_star
id|vv
)paren
(brace
id|DEB_VBI
c_func
(paren
(paren
l_string|&quot;dev:%p&bslash;n&quot;
comma
id|dev
)paren
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|vv-&gt;vbi_q.queue
)paren
suffix:semicolon
id|init_timer
c_func
(paren
op_amp
id|vv-&gt;vbi_q.timeout
)paren
suffix:semicolon
id|vv-&gt;vbi_q.timeout.function
op_assign
id|saa7146_buffer_timeout
suffix:semicolon
id|vv-&gt;vbi_q.timeout.data
op_assign
(paren
r_int
r_int
)paren
(paren
op_amp
id|vv-&gt;vbi_q
)paren
suffix:semicolon
id|vv-&gt;vbi_q.dev
op_assign
id|dev
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|vv-&gt;vbi_wq
)paren
suffix:semicolon
)brace
r_static
DECL|function|vbi_open
r_void
id|vbi_open
c_func
(paren
r_struct
id|saa7146_dev
op_star
id|dev
comma
r_struct
id|saa7146_fh
op_star
id|fh
)paren
(brace
id|DEB_VBI
c_func
(paren
(paren
l_string|&quot;dev:%p, fh:%p&bslash;n&quot;
comma
id|dev
comma
id|fh
)paren
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|fh-&gt;vbi_fmt
comma
l_int|0
comma
r_sizeof
(paren
id|fh-&gt;vbi_fmt
)paren
)paren
suffix:semicolon
id|fh-&gt;vbi_fmt.sampling_rate
op_assign
l_int|27000000
suffix:semicolon
id|fh-&gt;vbi_fmt.offset
op_assign
l_int|248
suffix:semicolon
multiline_comment|/* todo */
id|fh-&gt;vbi_fmt.samples_per_line
op_assign
id|vbi_pixel_to_capture
suffix:semicolon
id|fh-&gt;vbi_fmt.sample_format
op_assign
id|V4L2_PIX_FMT_GREY
suffix:semicolon
multiline_comment|/* fixme: this only works for PAL */
id|fh-&gt;vbi_fmt.start
(braket
l_int|0
)braket
op_assign
l_int|5
suffix:semicolon
id|fh-&gt;vbi_fmt.count
(braket
l_int|0
)braket
op_assign
l_int|16
suffix:semicolon
id|fh-&gt;vbi_fmt.start
(braket
l_int|1
)braket
op_assign
l_int|312
suffix:semicolon
id|fh-&gt;vbi_fmt.count
(braket
l_int|1
)braket
op_assign
l_int|16
suffix:semicolon
id|videobuf_queue_init
c_func
(paren
op_amp
id|fh-&gt;vbi_q
comma
op_amp
id|vbi_qops
comma
id|dev-&gt;pci
comma
op_amp
id|dev-&gt;slock
comma
id|V4L2_BUF_TYPE_VBI_CAPTURE
comma
id|V4L2_FIELD_SEQ_TB
comma
singleline_comment|// FIXME: does this really work?
r_sizeof
(paren
r_struct
id|saa7146_buf
)paren
)paren
suffix:semicolon
id|init_MUTEX
c_func
(paren
op_amp
id|fh-&gt;vbi_q.lock
)paren
suffix:semicolon
id|init_timer
c_func
(paren
op_amp
id|fh-&gt;vbi_read_timeout
)paren
suffix:semicolon
id|fh-&gt;vbi_read_timeout.function
op_assign
id|vbi_read_timeout
suffix:semicolon
id|fh-&gt;vbi_read_timeout.data
op_assign
(paren
r_int
r_int
)paren
id|fh
suffix:semicolon
id|vbi_workaround
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
r_static
DECL|function|vbi_close
r_void
id|vbi_close
c_func
(paren
r_struct
id|saa7146_dev
op_star
id|dev
comma
r_struct
id|saa7146_fh
op_star
id|fh
comma
r_struct
id|file
op_star
id|file
)paren
(brace
r_struct
id|saa7146_vv
op_star
id|vv
op_assign
id|dev-&gt;vv_data
suffix:semicolon
id|DEB_VBI
c_func
(paren
(paren
l_string|&quot;dev:%p, fh:%p&bslash;n&quot;
comma
id|dev
comma
id|fh
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fh
op_eq
id|vv-&gt;vbi_streaming
)paren
(brace
id|vbi_stop
c_func
(paren
id|fh
)paren
suffix:semicolon
)brace
)brace
r_static
DECL|function|vbi_irq_done
r_void
id|vbi_irq_done
c_func
(paren
r_struct
id|saa7146_dev
op_star
id|dev
comma
r_int
r_int
id|status
)paren
(brace
r_struct
id|saa7146_vv
op_star
id|vv
op_assign
id|dev-&gt;vv_data
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
id|vv-&gt;vbi_q.curr
)paren
(brace
id|DEB_VBI
c_func
(paren
(paren
l_string|&quot;dev:%p, curr:%p&bslash;n&quot;
comma
id|dev
comma
id|vv-&gt;vbi_q.curr
)paren
)paren
suffix:semicolon
multiline_comment|/* this must be += 2, one count for each field */
id|vv-&gt;vbi_fieldcount
op_add_assign
l_int|2
suffix:semicolon
id|vv-&gt;vbi_q.curr-&gt;vb.field_count
op_assign
id|vv-&gt;vbi_fieldcount
suffix:semicolon
id|saa7146_buffer_finish
c_func
(paren
id|dev
comma
op_amp
id|vv-&gt;vbi_q
comma
id|STATE_DONE
)paren
suffix:semicolon
)brace
r_else
(brace
id|DEB_VBI
c_func
(paren
(paren
l_string|&quot;dev:%p&bslash;n&quot;
comma
id|dev
)paren
)paren
suffix:semicolon
)brace
id|saa7146_buffer_next
c_func
(paren
id|dev
comma
op_amp
id|vv-&gt;vbi_q
comma
l_int|1
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|dev-&gt;slock
)paren
suffix:semicolon
)brace
r_static
DECL|function|vbi_read
id|ssize_t
id|vbi_read
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
id|saa7146_fh
op_star
id|fh
op_assign
id|file-&gt;private_data
suffix:semicolon
r_struct
id|saa7146_dev
op_star
id|dev
op_assign
id|fh-&gt;dev
suffix:semicolon
r_struct
id|saa7146_vv
op_star
id|vv
op_assign
id|dev-&gt;vv_data
suffix:semicolon
id|ssize_t
id|ret
op_assign
l_int|0
suffix:semicolon
id|DEB_VBI
c_func
(paren
(paren
l_string|&quot;dev:%p, fh:%p&bslash;n&quot;
comma
id|dev
comma
id|fh
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|NULL
op_eq
id|vv-&gt;vbi_streaming
)paren
(brace
singleline_comment|// fixme: check if dma3 is available
singleline_comment|// fixme: activate vbi engine here if necessary. (really?)
id|vv-&gt;vbi_streaming
op_assign
id|fh
suffix:semicolon
)brace
r_if
c_cond
(paren
id|fh
op_ne
id|vv-&gt;vbi_streaming
)paren
(brace
id|DEB_VBI
c_func
(paren
(paren
l_string|&quot;open %p is already using vbi capture.&quot;
comma
id|vv-&gt;vbi_streaming
)paren
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|mod_timer
c_func
(paren
op_amp
id|fh-&gt;vbi_read_timeout
comma
id|jiffies
op_plus
id|BUFFER_TIMEOUT
)paren
suffix:semicolon
id|ret
op_assign
id|videobuf_read_stream
c_func
(paren
id|file
comma
op_amp
id|fh-&gt;vbi_q
comma
id|data
comma
id|count
comma
id|ppos
comma
l_int|1
)paren
suffix:semicolon
multiline_comment|/*&n;&t;printk(&quot;BASE_ODD3:      0x%08x&bslash;n&quot;, saa7146_read(dev, BASE_ODD3));&n;&t;printk(&quot;BASE_EVEN3:     0x%08x&bslash;n&quot;, saa7146_read(dev, BASE_EVEN3));&n;&t;printk(&quot;PROT_ADDR3:     0x%08x&bslash;n&quot;, saa7146_read(dev, PROT_ADDR3));&n;&t;printk(&quot;PITCH3:         0x%08x&bslash;n&quot;, saa7146_read(dev, PITCH3));&n;&t;printk(&quot;BASE_PAGE3:     0x%08x&bslash;n&quot;, saa7146_read(dev, BASE_PAGE3));&n;&t;printk(&quot;NUM_LINE_BYTE3: 0x%08x&bslash;n&quot;, saa7146_read(dev, NUM_LINE_BYTE3));&n;&t;printk(&quot;BRS_CTRL:       0x%08x&bslash;n&quot;, saa7146_read(dev, BRS_CTRL));&n;*/
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|saa7146_vbi_uops
r_struct
id|saa7146_use_ops
id|saa7146_vbi_uops
op_assign
(brace
dot
id|init
op_assign
id|vbi_init
comma
dot
id|open
op_assign
id|vbi_open
comma
dot
id|release
op_assign
id|vbi_close
comma
dot
id|irq_done
op_assign
id|vbi_irq_done
comma
dot
id|read
op_assign
id|vbi_read
comma
)brace
suffix:semicolon
DECL|variable|saa7146_vbi_uops
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|saa7146_vbi_uops
)paren
suffix:semicolon
eof
