macro_line|#include &lt;media/saa7146_vv.h&gt;
DECL|macro|BOARD_CAN_DO_VBI
mdefine_line|#define BOARD_CAN_DO_VBI(dev)   (dev-&gt;revision != 0 &amp;&amp; dev-&gt;vv_data-&gt;vbi_minor != -1) 
multiline_comment|/********************************************************************************/
multiline_comment|/* common dma functions */
DECL|function|saa7146_dma_free
r_void
id|saa7146_dma_free
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
)paren
(brace
id|DEB_EE
c_func
(paren
(paren
l_string|&quot;dev:%p, buf:%p&bslash;n&quot;
comma
id|dev
comma
id|buf
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|in_interrupt
c_func
(paren
)paren
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|videobuf_waiton
c_func
(paren
op_amp
id|buf-&gt;vb
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
id|videobuf_dma_pci_unmap
c_func
(paren
id|dev-&gt;pci
comma
op_amp
id|buf-&gt;vb.dma
)paren
suffix:semicolon
id|videobuf_dma_free
c_func
(paren
op_amp
id|buf-&gt;vb.dma
)paren
suffix:semicolon
id|buf-&gt;vb.state
op_assign
id|STATE_NEEDS_INIT
suffix:semicolon
)brace
multiline_comment|/********************************************************************************/
multiline_comment|/* common buffer functions */
DECL|function|saa7146_buffer_queue
r_int
id|saa7146_buffer_queue
c_func
(paren
r_struct
id|saa7146_dev
op_star
id|dev
comma
r_struct
id|saa7146_dmaqueue
op_star
id|q
comma
r_struct
id|saa7146_buf
op_star
id|buf
)paren
(brace
macro_line|#if DEBUG_SPINLOCKS
id|BUG_ON
c_func
(paren
op_logical_neg
id|spin_is_locked
c_func
(paren
op_amp
id|dev-&gt;slock
)paren
)paren
suffix:semicolon
macro_line|#endif
id|DEB_EE
c_func
(paren
(paren
l_string|&quot;dev:%p, dmaq:%p, buf:%p&bslash;n&quot;
comma
id|dev
comma
id|q
comma
id|buf
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|NULL
op_eq
id|q
)paren
(brace
id|ERR
c_func
(paren
(paren
l_string|&quot;internal error: fatal NULL pointer for q.&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
l_int|NULL
op_eq
id|q-&gt;curr
)paren
(brace
id|q-&gt;curr
op_assign
id|buf
suffix:semicolon
id|DEB_D
c_func
(paren
(paren
l_string|&quot;immediately activating buffer %p&bslash;n&quot;
comma
id|buf
)paren
)paren
suffix:semicolon
id|buf
op_member_access_from_pointer
id|activate
c_func
(paren
id|dev
comma
id|buf
comma
l_int|NULL
)paren
suffix:semicolon
)brace
r_else
(brace
id|list_add_tail
c_func
(paren
op_amp
id|buf-&gt;vb.queue
comma
op_amp
id|q-&gt;queue
)paren
suffix:semicolon
id|buf-&gt;vb.state
op_assign
id|STATE_QUEUED
suffix:semicolon
id|DEB_D
c_func
(paren
(paren
l_string|&quot;adding buffer %p to queue. (active buffer present)&bslash;n&quot;
comma
id|buf
)paren
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|saa7146_buffer_finish
r_void
id|saa7146_buffer_finish
c_func
(paren
r_struct
id|saa7146_dev
op_star
id|dev
comma
r_struct
id|saa7146_dmaqueue
op_star
id|q
comma
r_int
id|state
)paren
(brace
macro_line|#if DEBUG_SPINLOCKS
id|BUG_ON
c_func
(paren
op_logical_neg
id|spin_is_locked
c_func
(paren
op_amp
id|dev-&gt;slock
)paren
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
l_int|NULL
op_eq
id|q-&gt;curr
)paren
(brace
id|ERR
c_func
(paren
(paren
l_string|&quot;internal error: fatal NULL pointer for q-&gt;curr.&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|DEB_EE
c_func
(paren
(paren
l_string|&quot;dev:%p, dmaq:%p, state:%d&bslash;n&quot;
comma
id|dev
comma
id|q
comma
id|state
)paren
)paren
suffix:semicolon
multiline_comment|/* finish current buffer */
id|q-&gt;curr-&gt;vb.state
op_assign
id|state
suffix:semicolon
id|do_gettimeofday
c_func
(paren
op_amp
id|q-&gt;curr-&gt;vb.ts
)paren
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|q-&gt;curr-&gt;vb.done
)paren
suffix:semicolon
id|q-&gt;curr
op_assign
l_int|NULL
suffix:semicolon
)brace
DECL|function|saa7146_buffer_next
r_void
id|saa7146_buffer_next
c_func
(paren
r_struct
id|saa7146_dev
op_star
id|dev
comma
r_struct
id|saa7146_dmaqueue
op_star
id|q
comma
r_int
id|vbi
)paren
(brace
r_struct
id|saa7146_buf
op_star
id|buf
comma
op_star
id|next
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
l_int|NULL
op_eq
id|q
)paren
(brace
id|ERR
c_func
(paren
(paren
l_string|&quot;internal error: fatal NULL pointer for q.&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|DEB_EE
c_func
(paren
(paren
l_string|&quot;dev:%p, dmaq:%p, vbi:%d&bslash;n&quot;
comma
id|dev
comma
id|q
comma
id|vbi
)paren
)paren
suffix:semicolon
macro_line|#if DEBUG_SPINLOCKS
id|BUG_ON
c_func
(paren
op_logical_neg
id|spin_is_locked
c_func
(paren
op_amp
id|dev-&gt;slock
)paren
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|q-&gt;queue
)paren
)paren
(brace
multiline_comment|/* activate next one from queue */
id|buf
op_assign
id|list_entry
c_func
(paren
id|q-&gt;queue.next
comma
r_struct
id|saa7146_buf
comma
id|vb.queue
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|buf-&gt;vb.queue
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|q-&gt;queue
)paren
)paren
id|next
op_assign
id|list_entry
c_func
(paren
id|q-&gt;queue.next
comma
r_struct
id|saa7146_buf
comma
id|vb.queue
)paren
suffix:semicolon
id|q-&gt;curr
op_assign
id|buf
suffix:semicolon
id|DEB_D
c_func
(paren
(paren
l_string|&quot;next buffer: buf:%p, prev:%p, next:%p&bslash;n&quot;
comma
id|buf
comma
id|q-&gt;queue.prev
comma
id|q-&gt;queue.next
)paren
)paren
suffix:semicolon
id|buf
op_member_access_from_pointer
id|activate
c_func
(paren
id|dev
comma
id|buf
comma
id|next
)paren
suffix:semicolon
)brace
r_else
(brace
id|DEB_D
c_func
(paren
(paren
l_string|&quot;no next buffer. stopping.&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_ne
id|vbi
)paren
(brace
multiline_comment|/* turn off video-dma3 */
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
)brace
r_else
(brace
multiline_comment|/* nothing to do -- just prevent next video-dma1 transfer&n;&t;&t;&t;   by lowering the protection address */
singleline_comment|// fixme: fix this for vflip != 0
id|saa7146_write
c_func
(paren
id|dev
comma
id|PROT_ADDR1
comma
l_int|0
)paren
suffix:semicolon
id|saa7146_write
c_func
(paren
id|dev
comma
id|MC2
comma
(paren
id|MASK_02
op_or
id|MASK_18
)paren
)paren
suffix:semicolon
multiline_comment|/* write the address of the rps-program */
id|saa7146_write
c_func
(paren
id|dev
comma
id|RPS_ADDR0
comma
id|dev-&gt;d_rps0.dma_handle
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
id|MASK_12
op_or
id|MASK_28
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t;printk(&quot;vdma%d.base_even:     0x%08x&bslash;n&quot;, 1,saa7146_read(dev,BASE_EVEN1));&n;&t;&t;&t;printk(&quot;vdma%d.base_odd:      0x%08x&bslash;n&quot;, 1,saa7146_read(dev,BASE_ODD1));&n;&t;&t;&t;printk(&quot;vdma%d.prot_addr:     0x%08x&bslash;n&quot;, 1,saa7146_read(dev,PROT_ADDR1));&n;&t;&t;&t;printk(&quot;vdma%d.base_page:     0x%08x&bslash;n&quot;, 1,saa7146_read(dev,BASE_PAGE1));&n;&t;&t;&t;printk(&quot;vdma%d.pitch:         0x%08x&bslash;n&quot;, 1,saa7146_read(dev,PITCH1));&n;&t;&t;&t;printk(&quot;vdma%d.num_line_byte: 0x%08x&bslash;n&quot;, 1,saa7146_read(dev,NUM_LINE_BYTE1));&n;*/
)brace
id|del_timer
c_func
(paren
op_amp
id|q-&gt;timeout
)paren
suffix:semicolon
)brace
)brace
DECL|function|saa7146_buffer_timeout
r_void
id|saa7146_buffer_timeout
c_func
(paren
r_int
r_int
id|data
)paren
(brace
r_struct
id|saa7146_dmaqueue
op_star
id|q
op_assign
(paren
r_struct
id|saa7146_dmaqueue
op_star
)paren
id|data
suffix:semicolon
r_struct
id|saa7146_dev
op_star
id|dev
op_assign
id|q-&gt;dev
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|DEB_EE
c_func
(paren
(paren
l_string|&quot;dev:%p, dmaq:%p&bslash;n&quot;
comma
id|dev
comma
id|q
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
r_if
c_cond
(paren
id|q-&gt;curr
)paren
(brace
id|DEB_D
c_func
(paren
(paren
l_string|&quot;timeout on %p&bslash;n&quot;
comma
id|q-&gt;curr
)paren
)paren
suffix:semicolon
id|saa7146_buffer_finish
c_func
(paren
id|dev
comma
id|q
comma
id|STATE_ERROR
)paren
suffix:semicolon
)brace
multiline_comment|/* we don&squot;t restart the transfer here like other drivers do. when&n;&t;   a streaming capture is disabled, the timeout function will be&n;&t;   called for the current buffer. if we activate the next buffer now,&n;&t;   we mess up our capture logic. if a timeout occurs on another buffer,&n;&t;   then something is seriously broken before, so no need to buffer the&n;&t;   next capture IMHO... */
multiline_comment|/*&n;&t;saa7146_buffer_next(dev,q);&n;*/
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
multiline_comment|/********************************************************************************/
multiline_comment|/* file operations */
DECL|function|fops_open
r_static
r_int
id|fops_open
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
id|iminor
c_func
(paren
id|inode
)paren
suffix:semicolon
r_struct
id|saa7146_dev
op_star
id|h
op_assign
l_int|NULL
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
r_struct
id|saa7146_fh
op_star
id|fh
op_assign
l_int|NULL
suffix:semicolon
r_int
id|result
op_assign
l_int|0
suffix:semicolon
r_enum
id|v4l2_buf_type
id|type
op_assign
id|V4L2_BUF_TYPE_VIDEO_CAPTURE
suffix:semicolon
id|DEB_EE
c_func
(paren
(paren
l_string|&quot;inode:%p, file:%p, minor:%d&bslash;n&quot;
comma
id|inode
comma
id|file
comma
id|minor
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|down_interruptible
c_func
(paren
op_amp
id|saa7146_devices_lock
)paren
)paren
r_return
op_minus
id|ERESTARTSYS
suffix:semicolon
id|list_for_each
c_func
(paren
id|list
comma
op_amp
id|saa7146_devices
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
id|saa7146_dev
comma
id|item
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|NULL
op_eq
id|h-&gt;vv_data
)paren
(brace
id|DEB_D
c_func
(paren
(paren
l_string|&quot;device %p has not registered video devices.&bslash;n&quot;
comma
id|h
)paren
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|DEB_D
c_func
(paren
(paren
l_string|&quot;trying: %p @ major %d,%d&bslash;n&quot;
comma
id|h
comma
id|h-&gt;vv_data-&gt;video_minor
comma
id|h-&gt;vv_data-&gt;vbi_minor
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|h-&gt;vv_data-&gt;video_minor
op_eq
id|minor
)paren
(brace
id|dev
op_assign
id|h
suffix:semicolon
)brace
r_if
c_cond
(paren
id|h-&gt;vv_data-&gt;vbi_minor
op_eq
id|minor
)paren
(brace
id|type
op_assign
id|V4L2_BUF_TYPE_VBI_CAPTURE
suffix:semicolon
id|dev
op_assign
id|h
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
l_int|NULL
op_eq
id|dev
)paren
(brace
id|DEB_S
c_func
(paren
(paren
l_string|&quot;no such video device.&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|result
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|DEB_D
c_func
(paren
(paren
l_string|&quot;using: %p&bslash;n&quot;
comma
id|dev
)paren
)paren
suffix:semicolon
multiline_comment|/* check if an extension is registered */
r_if
c_cond
(paren
l_int|NULL
op_eq
id|dev-&gt;ext
)paren
(brace
id|DEB_S
c_func
(paren
(paren
l_string|&quot;no extension registered for this device.&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|result
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/* allocate per open data */
id|fh
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|fh
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|NULL
op_eq
id|fh
)paren
(brace
id|DEB_S
c_func
(paren
(paren
l_string|&quot;cannot allocate memory for per open data.&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|result
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|memset
c_func
(paren
id|fh
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|fh
)paren
)paren
suffix:semicolon
singleline_comment|// FIXME: do we need to increase *our* usage count?
r_if
c_cond
(paren
l_int|0
op_eq
id|try_module_get
c_func
(paren
id|dev-&gt;ext-&gt;module
)paren
)paren
(brace
id|result
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|file-&gt;private_data
op_assign
id|fh
suffix:semicolon
id|fh-&gt;dev
op_assign
id|dev
suffix:semicolon
id|fh-&gt;type
op_assign
id|type
suffix:semicolon
id|saa7146_video_uops
dot
id|open
c_func
(paren
id|dev
comma
id|fh
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_ne
id|BOARD_CAN_DO_VBI
c_func
(paren
id|dev
)paren
)paren
(brace
id|saa7146_vbi_uops
dot
id|open
c_func
(paren
id|dev
comma
id|fh
)paren
suffix:semicolon
)brace
id|result
op_assign
l_int|0
suffix:semicolon
id|out
suffix:colon
r_if
c_cond
(paren
id|fh
op_ne
l_int|0
op_logical_and
id|result
op_ne
l_int|0
)paren
(brace
id|kfree
c_func
(paren
id|fh
)paren
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
id|saa7146_devices_lock
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|function|fops_release
r_static
r_int
id|fops_release
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
id|DEB_EE
c_func
(paren
(paren
l_string|&quot;inode:%p, file:%p&bslash;n&quot;
comma
id|inode
comma
id|file
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|down_interruptible
c_func
(paren
op_amp
id|saa7146_devices_lock
)paren
)paren
r_return
op_minus
id|ERESTARTSYS
suffix:semicolon
id|saa7146_video_uops
dot
id|release
c_func
(paren
id|dev
comma
id|fh
comma
id|file
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_ne
id|BOARD_CAN_DO_VBI
c_func
(paren
id|dev
)paren
)paren
(brace
id|saa7146_vbi_uops
dot
id|release
c_func
(paren
id|dev
comma
id|fh
comma
id|file
)paren
suffix:semicolon
)brace
id|module_put
c_func
(paren
id|dev-&gt;ext-&gt;module
)paren
suffix:semicolon
id|file-&gt;private_data
op_assign
l_int|NULL
suffix:semicolon
id|kfree
c_func
(paren
id|fh
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|saa7146_devices_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_int
id|saa7146_video_do_ioctl
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
suffix:semicolon
DECL|function|fops_ioctl
r_static
r_int
id|fops_ioctl
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
multiline_comment|/*&n;&t;DEB_EE((&quot;inode:%p, file:%p, cmd:%d, arg:%li&bslash;n&quot;,inode, file, cmd, arg));&n;*/
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
id|saa7146_video_do_ioctl
)paren
suffix:semicolon
)brace
DECL|function|fops_mmap
r_static
r_int
id|fops_mmap
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
id|saa7146_fh
op_star
id|fh
op_assign
id|file-&gt;private_data
suffix:semicolon
r_struct
id|videobuf_queue
op_star
id|q
suffix:semicolon
r_switch
c_cond
(paren
id|fh-&gt;type
)paren
(brace
r_case
id|V4L2_BUF_TYPE_VIDEO_CAPTURE
suffix:colon
(brace
id|DEB_EE
c_func
(paren
(paren
l_string|&quot;V4L2_BUF_TYPE_VIDEO_CAPTURE: file:%p, vma:%p&bslash;n&quot;
comma
id|file
comma
id|vma
)paren
)paren
suffix:semicolon
id|q
op_assign
op_amp
id|fh-&gt;video_q
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|V4L2_BUF_TYPE_VBI_CAPTURE
suffix:colon
(brace
id|DEB_EE
c_func
(paren
(paren
l_string|&quot;V4L2_BUF_TYPE_VBI_CAPTURE: file:%p, vma:%p&bslash;n&quot;
comma
id|file
comma
id|vma
)paren
)paren
suffix:semicolon
id|q
op_assign
op_amp
id|fh-&gt;vbi_q
suffix:semicolon
r_break
suffix:semicolon
)brace
r_default
suffix:colon
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
id|videobuf_mmap_mapper
c_func
(paren
id|vma
comma
id|q
)paren
suffix:semicolon
)brace
DECL|function|fops_poll
r_static
r_int
r_int
id|fops_poll
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
id|saa7146_fh
op_star
id|fh
op_assign
id|file-&gt;private_data
suffix:semicolon
r_struct
id|videobuf_buffer
op_star
id|buf
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|videobuf_queue
op_star
id|q
suffix:semicolon
id|DEB_EE
c_func
(paren
(paren
l_string|&quot;file:%p, poll:%p&bslash;n&quot;
comma
id|file
comma
id|wait
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|V4L2_BUF_TYPE_VBI_CAPTURE
op_eq
id|fh-&gt;type
)paren
(brace
r_if
c_cond
(paren
l_int|0
op_eq
id|fh-&gt;vbi_q.streaming
)paren
(brace
r_return
id|videobuf_poll_stream
c_func
(paren
id|file
comma
op_amp
id|fh-&gt;vbi_q
comma
id|wait
)paren
suffix:semicolon
)brace
id|q
op_assign
op_amp
id|fh-&gt;vbi_q
suffix:semicolon
)brace
r_else
(brace
id|DEB_D
c_func
(paren
(paren
l_string|&quot;using video queue.&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|q
op_assign
op_amp
id|fh-&gt;video_q
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|q-&gt;stream
)paren
)paren
id|buf
op_assign
id|list_entry
c_func
(paren
id|q-&gt;stream.next
comma
r_struct
id|videobuf_buffer
comma
id|stream
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buf
)paren
(brace
id|DEB_D
c_func
(paren
(paren
l_string|&quot;buf == NULL!&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_return
id|POLLERR
suffix:semicolon
)brace
id|poll_wait
c_func
(paren
id|file
comma
op_amp
id|buf-&gt;done
comma
id|wait
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buf-&gt;state
op_eq
id|STATE_DONE
op_logical_or
id|buf-&gt;state
op_eq
id|STATE_ERROR
)paren
(brace
id|DEB_D
c_func
(paren
(paren
l_string|&quot;poll succeeded!&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_return
id|POLLIN
op_or
id|POLLRDNORM
suffix:semicolon
)brace
id|DEB_D
c_func
(paren
(paren
l_string|&quot;nothing to poll for, buf-&gt;state:%d&bslash;n&quot;
comma
id|buf-&gt;state
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|fops_read
r_static
id|ssize_t
id|fops_read
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
r_switch
c_cond
(paren
id|fh-&gt;type
)paren
(brace
r_case
id|V4L2_BUF_TYPE_VIDEO_CAPTURE
suffix:colon
(brace
id|DEB_EE
c_func
(paren
(paren
l_string|&quot;V4L2_BUF_TYPE_VIDEO_CAPTURE: file:%p, data:%p, count:%lun&quot;
comma
id|file
comma
id|data
comma
(paren
r_int
r_int
)paren
id|count
)paren
)paren
suffix:semicolon
r_return
id|saa7146_video_uops
dot
id|read
c_func
(paren
id|file
comma
id|data
comma
id|count
comma
id|ppos
)paren
suffix:semicolon
)brace
r_case
id|V4L2_BUF_TYPE_VBI_CAPTURE
suffix:colon
(brace
id|DEB_EE
c_func
(paren
(paren
l_string|&quot;V4L2_BUF_TYPE_VBI_CAPTURE: file:%p, data:%p, count:%lu&bslash;n&quot;
comma
id|file
comma
id|data
comma
(paren
r_int
r_int
)paren
id|count
)paren
)paren
suffix:semicolon
r_return
id|saa7146_vbi_uops
dot
id|read
c_func
(paren
id|file
comma
id|data
comma
id|count
comma
id|ppos
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
DECL|variable|video_fops
r_static
r_struct
id|file_operations
id|video_fops
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
id|fops_open
comma
dot
id|release
op_assign
id|fops_release
comma
dot
id|read
op_assign
id|fops_read
comma
dot
id|poll
op_assign
id|fops_poll
comma
dot
id|mmap
op_assign
id|fops_mmap
comma
dot
id|ioctl
op_assign
id|fops_ioctl
comma
dot
id|llseek
op_assign
id|no_llseek
comma
)brace
suffix:semicolon
DECL|function|vv_callback
r_void
id|vv_callback
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
id|u32
id|isr
op_assign
id|status
suffix:semicolon
id|DEB_EE
c_func
(paren
(paren
l_string|&quot;dev:%p, isr:0x%08x&bslash;n&quot;
comma
id|dev
comma
(paren
id|u32
)paren
id|status
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_ne
(paren
id|isr
op_amp
(paren
id|MASK_27
)paren
)paren
)paren
(brace
id|DEB_INT
c_func
(paren
(paren
l_string|&quot;irq: RPS0 (0x%08x).&bslash;n&quot;
comma
id|isr
)paren
)paren
suffix:semicolon
id|saa7146_video_uops
dot
id|irq_done
c_func
(paren
id|dev
comma
id|isr
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
l_int|0
op_ne
(paren
id|isr
op_amp
(paren
id|MASK_28
)paren
)paren
)paren
(brace
id|u32
id|mc2
op_assign
id|saa7146_read
c_func
(paren
id|dev
comma
id|MC2
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_ne
(paren
id|mc2
op_amp
id|MASK_15
)paren
)paren
(brace
id|DEB_INT
c_func
(paren
(paren
l_string|&quot;irq: RPS1 vbi workaround (0x%08x).&bslash;n&quot;
comma
id|isr
)paren
)paren
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|dev-&gt;vv_data-&gt;vbi_wq
)paren
suffix:semicolon
id|saa7146_write
c_func
(paren
id|dev
comma
id|MC2
comma
id|MASK_31
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|DEB_INT
c_func
(paren
(paren
l_string|&quot;irq: RPS1 (0x%08x).&bslash;n&quot;
comma
id|isr
)paren
)paren
suffix:semicolon
id|saa7146_vbi_uops
dot
id|irq_done
c_func
(paren
id|dev
comma
id|isr
)paren
suffix:semicolon
)brace
)brace
DECL|variable|device_template
r_static
r_struct
id|video_device
id|device_template
op_assign
(brace
dot
id|hardware
op_assign
id|VID_HARDWARE_SAA7146
comma
dot
id|fops
op_assign
op_amp
id|video_fops
comma
dot
id|minor
op_assign
op_minus
l_int|1
comma
)brace
suffix:semicolon
DECL|function|saa7146_vv_init
r_int
id|saa7146_vv_init
c_func
(paren
r_struct
id|saa7146_dev
op_star
id|dev
comma
r_struct
id|saa7146_ext_vv
op_star
id|ext_vv
)paren
(brace
r_struct
id|saa7146_vv
op_star
id|vv
op_assign
id|kmalloc
(paren
r_sizeof
(paren
r_struct
id|saa7146_vv
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|NULL
op_eq
id|vv
)paren
(brace
id|ERR
c_func
(paren
(paren
l_string|&quot;out of memory. aborting.&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|memset
c_func
(paren
id|vv
comma
l_int|0x0
comma
r_sizeof
(paren
op_star
id|vv
)paren
)paren
suffix:semicolon
id|DEB_EE
c_func
(paren
(paren
l_string|&quot;dev:%p&bslash;n&quot;
comma
id|dev
)paren
)paren
suffix:semicolon
multiline_comment|/* save per-device extension data (one extension can&n;&t;   handle different devices that might need different&n;&t;   configuration data) */
id|dev-&gt;ext_vv_data
op_assign
id|ext_vv
suffix:semicolon
id|vv-&gt;video_minor
op_assign
op_minus
l_int|1
suffix:semicolon
id|vv-&gt;vbi_minor
op_assign
op_minus
l_int|1
suffix:semicolon
id|vv-&gt;d_clipping.cpu_addr
op_assign
id|pci_alloc_consistent
c_func
(paren
id|dev-&gt;pci
comma
id|SAA7146_CLIPPING_MEM
comma
op_amp
id|vv-&gt;d_clipping.dma_handle
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|NULL
op_eq
id|vv-&gt;d_clipping.cpu_addr
)paren
(brace
id|ERR
c_func
(paren
(paren
l_string|&quot;out of memory. aborting.&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|vv
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|memset
c_func
(paren
id|vv-&gt;d_clipping.cpu_addr
comma
l_int|0x0
comma
id|SAA7146_CLIPPING_MEM
)paren
suffix:semicolon
id|saa7146_video_uops
dot
id|init
c_func
(paren
id|dev
comma
id|vv
)paren
suffix:semicolon
id|saa7146_vbi_uops
dot
id|init
c_func
(paren
id|dev
comma
id|vv
)paren
suffix:semicolon
id|dev-&gt;vv_data
op_assign
id|vv
suffix:semicolon
id|dev-&gt;vv_callback
op_assign
op_amp
id|vv_callback
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|saa7146_vv_release
r_int
id|saa7146_vv_release
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
id|DEB_EE
c_func
(paren
(paren
l_string|&quot;dev:%p&bslash;n&quot;
comma
id|dev
)paren
)paren
suffix:semicolon
id|pci_free_consistent
c_func
(paren
id|dev-&gt;pci
comma
id|SAA7146_RPS_MEM
comma
id|vv-&gt;d_clipping.cpu_addr
comma
id|vv-&gt;d_clipping.dma_handle
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|vv
)paren
suffix:semicolon
id|dev-&gt;vv_data
op_assign
l_int|NULL
suffix:semicolon
id|dev-&gt;vv_callback
op_assign
l_int|NULL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|saa7146_register_device
r_int
id|saa7146_register_device
c_func
(paren
r_struct
id|video_device
op_star
id|vid
comma
r_struct
id|saa7146_dev
op_star
id|dev
comma
r_char
op_star
id|name
comma
r_int
id|type
)paren
(brace
r_struct
id|saa7146_vv
op_star
id|vv
op_assign
id|dev-&gt;vv_data
suffix:semicolon
id|DEB_EE
c_func
(paren
(paren
l_string|&quot;dev:%p, name:&squot;%s&squot;&bslash;n&quot;
comma
id|dev
comma
id|name
)paren
)paren
suffix:semicolon
op_star
id|vid
op_assign
id|device_template
suffix:semicolon
id|strlcpy
c_func
(paren
id|vid-&gt;name
comma
id|name
comma
r_sizeof
(paren
id|vid-&gt;name
)paren
)paren
suffix:semicolon
id|vid-&gt;priv
op_assign
id|dev
suffix:semicolon
singleline_comment|// fixme: -1 should be an insmod parameter *for the extension* (like &quot;video_nr&quot;);
r_if
c_cond
(paren
id|video_register_device
c_func
(paren
id|vid
comma
id|type
comma
op_minus
l_int|1
)paren
OL
l_int|0
)paren
(brace
id|ERR
c_func
(paren
(paren
l_string|&quot;cannot register vbi v4l2 device. skipping.&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|VFL_TYPE_GRABBER
op_eq
id|type
)paren
(brace
id|vv-&gt;video_minor
op_assign
id|vid-&gt;minor
suffix:semicolon
id|INFO
c_func
(paren
(paren
l_string|&quot;%s: registered device video%d [v4l2]&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|vid-&gt;minor
op_amp
l_int|0x1f
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|vv-&gt;vbi_minor
op_assign
id|vid-&gt;minor
suffix:semicolon
id|INFO
c_func
(paren
(paren
l_string|&quot;%s: registered device vbi%d [v4l2]&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|vid-&gt;minor
op_amp
l_int|0x1f
)paren
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|saa7146_unregister_device
r_int
id|saa7146_unregister_device
c_func
(paren
r_struct
id|video_device
op_star
id|vid
comma
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
id|DEB_EE
c_func
(paren
(paren
l_string|&quot;dev:%p&bslash;n&quot;
comma
id|dev
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|VFL_TYPE_GRABBER
op_eq
id|vid-&gt;type
)paren
(brace
id|vv-&gt;video_minor
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|vv-&gt;vbi_minor
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
id|video_unregister_device
c_func
(paren
id|vid
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|saa7146_vv_init_module
r_static
r_int
id|__init
id|saa7146_vv_init_module
c_func
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|saa7146_vv_cleanup_module
r_static
r_void
id|__exit
id|saa7146_vv_cleanup_module
c_func
(paren
r_void
)paren
(brace
)brace
DECL|variable|saa7146_vv_init_module
id|module_init
c_func
(paren
id|saa7146_vv_init_module
)paren
suffix:semicolon
DECL|variable|saa7146_vv_cleanup_module
id|module_exit
c_func
(paren
id|saa7146_vv_cleanup_module
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Michael Hunold &lt;michael@mihu.de&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;video4linux driver for saa7146-based hardware&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
