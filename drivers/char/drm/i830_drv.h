multiline_comment|/* i830_drv.h -- Private header for the I830 driver -*- linux-c -*-&n; * Created: Mon Dec 13 01:50:01 1999 by jhartmann@precisioninsight.com&n; *&n; * Copyright 1999 Precision Insight, Inc., Cedar Park, Texas.&n; * Copyright 2000 VA Linux Systems, Inc., Sunnyvale, California.&n; * All rights reserved.&n; *&n; * Permission is hereby granted, free of charge, to any person obtaining a&n; * copy of this software and associated documentation files (the &quot;Software&quot;),&n; * to deal in the Software without restriction, including without limitation&n; * the rights to use, copy, modify, merge, publish, distribute, sublicense,&n; * and/or sell copies of the Software, and to permit persons to whom the&n; * Software is furnished to do so, subject to the following conditions:&n; * &n; * The above copyright notice and this permission notice (including the next&n; * paragraph) shall be included in all copies or substantial portions of the&n; * Software.&n; * &n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR&n; * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n; * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL&n; * PRECISION INSIGHT AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR&n; * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,&n; * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER&n; * DEALINGS IN THE SOFTWARE.&n; *&n; * Authors: Rickard E. (Rik) Faith &lt;faith@valinux.com&gt;&n; * &t;    Jeff Hartmann &lt;jhartmann@valinux.com&gt;&n; *&n; */
macro_line|#ifndef _I830_DRV_H_
DECL|macro|_I830_DRV_H_
mdefine_line|#define _I830_DRV_H_
multiline_comment|/* General customization:&n; */
DECL|macro|DRIVER_AUTHOR
mdefine_line|#define DRIVER_AUTHOR&t;&t;&quot;VA Linux Systems Inc.&quot;
DECL|macro|DRIVER_NAME
mdefine_line|#define DRIVER_NAME&t;&t;&quot;i830&quot;
DECL|macro|DRIVER_DESC
mdefine_line|#define DRIVER_DESC&t;&t;&quot;Intel 830M&quot;
DECL|macro|DRIVER_DATE
mdefine_line|#define DRIVER_DATE&t;&t;&quot;20021108&quot;
multiline_comment|/* Interface history:&n; *&n; * 1.1: Original.&n; * 1.2: ?&n; * 1.3: New irq emit/wait ioctls.&n; *      New pageflip ioctl.&n; *      New getparam ioctl.&n; *      State for texunits 3&amp;4 in sarea.&n; *      New (alternative) layout for texture state.&n; */
DECL|macro|DRIVER_MAJOR
mdefine_line|#define DRIVER_MAJOR&t;&t;1
DECL|macro|DRIVER_MINOR
mdefine_line|#define DRIVER_MINOR&t;&t;3
DECL|macro|DRIVER_PATCHLEVEL
mdefine_line|#define DRIVER_PATCHLEVEL&t;2
multiline_comment|/* Driver will work either way: IRQ&squot;s save cpu time when waiting for&n; * the card, but are subject to subtle interactions between bios,&n; * hardware and the driver.&n; */
multiline_comment|/* XXX: Add vblank support? */
DECL|macro|USE_IRQS
mdefine_line|#define USE_IRQS 0
DECL|struct|drm_i830_buf_priv
r_typedef
r_struct
id|drm_i830_buf_priv
(brace
DECL|member|in_use
id|u32
op_star
id|in_use
suffix:semicolon
DECL|member|my_use_idx
r_int
id|my_use_idx
suffix:semicolon
DECL|member|currently_mapped
r_int
id|currently_mapped
suffix:semicolon
DECL|member|virtual
r_void
id|__user
op_star
r_virtual
suffix:semicolon
DECL|member|kernel_virtual
r_void
op_star
id|kernel_virtual
suffix:semicolon
DECL|typedef|drm_i830_buf_priv_t
)brace
id|drm_i830_buf_priv_t
suffix:semicolon
DECL|struct|_drm_i830_ring_buffer
r_typedef
r_struct
id|_drm_i830_ring_buffer
(brace
DECL|member|tail_mask
r_int
id|tail_mask
suffix:semicolon
DECL|member|Start
r_int
r_int
id|Start
suffix:semicolon
DECL|member|End
r_int
r_int
id|End
suffix:semicolon
DECL|member|Size
r_int
r_int
id|Size
suffix:semicolon
DECL|member|virtual_start
id|u8
op_star
id|virtual_start
suffix:semicolon
DECL|member|head
r_int
id|head
suffix:semicolon
DECL|member|tail
r_int
id|tail
suffix:semicolon
DECL|member|space
r_int
id|space
suffix:semicolon
DECL|typedef|drm_i830_ring_buffer_t
)brace
id|drm_i830_ring_buffer_t
suffix:semicolon
DECL|struct|drm_i830_private
r_typedef
r_struct
id|drm_i830_private
(brace
DECL|member|sarea_map
id|drm_map_t
op_star
id|sarea_map
suffix:semicolon
DECL|member|mmio_map
id|drm_map_t
op_star
id|mmio_map
suffix:semicolon
DECL|member|sarea_priv
id|drm_i830_sarea_t
op_star
id|sarea_priv
suffix:semicolon
DECL|member|ring
id|drm_i830_ring_buffer_t
id|ring
suffix:semicolon
DECL|member|hw_status_page
r_void
op_star
id|hw_status_page
suffix:semicolon
DECL|member|counter
r_int
r_int
id|counter
suffix:semicolon
DECL|member|dma_status_page
id|dma_addr_t
id|dma_status_page
suffix:semicolon
DECL|member|mmap_buffer
id|drm_buf_t
op_star
id|mmap_buffer
suffix:semicolon
DECL|member|front_di1
DECL|member|back_di1
DECL|member|zi1
id|u32
id|front_di1
comma
id|back_di1
comma
id|zi1
suffix:semicolon
DECL|member|back_offset
r_int
id|back_offset
suffix:semicolon
DECL|member|depth_offset
r_int
id|depth_offset
suffix:semicolon
DECL|member|front_offset
r_int
id|front_offset
suffix:semicolon
DECL|member|w
DECL|member|h
r_int
id|w
comma
id|h
suffix:semicolon
DECL|member|pitch
r_int
id|pitch
suffix:semicolon
DECL|member|back_pitch
r_int
id|back_pitch
suffix:semicolon
DECL|member|depth_pitch
r_int
id|depth_pitch
suffix:semicolon
DECL|member|cpp
r_int
r_int
id|cpp
suffix:semicolon
DECL|member|do_boxes
r_int
id|do_boxes
suffix:semicolon
DECL|member|dma_used
r_int
id|dma_used
suffix:semicolon
DECL|member|current_page
r_int
id|current_page
suffix:semicolon
DECL|member|page_flipping
r_int
id|page_flipping
suffix:semicolon
DECL|member|irq_queue
id|wait_queue_head_t
id|irq_queue
suffix:semicolon
DECL|member|irq_received
id|atomic_t
id|irq_received
suffix:semicolon
DECL|member|irq_emitted
id|atomic_t
id|irq_emitted
suffix:semicolon
DECL|member|use_mi_batchbuffer_start
r_int
id|use_mi_batchbuffer_start
suffix:semicolon
DECL|typedef|drm_i830_private_t
)brace
id|drm_i830_private_t
suffix:semicolon
multiline_comment|/* i830_dma.c */
r_extern
r_int
id|i830_dma_schedule
c_func
(paren
id|drm_device_t
op_star
id|dev
comma
r_int
id|locked
)paren
suffix:semicolon
r_extern
r_int
id|i830_getbuf
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
id|filp
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
r_extern
r_int
id|i830_dma_init
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
id|filp
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
r_extern
r_int
id|i830_dma_cleanup
c_func
(paren
id|drm_device_t
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_int
id|i830_flush_ioctl
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
id|filp
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
r_extern
r_void
id|i830_reclaim_buffers
c_func
(paren
r_struct
id|file
op_star
id|filp
)paren
suffix:semicolon
r_extern
r_int
id|i830_getage
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
id|filp
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
r_extern
r_int
id|i830_mmap_buffers
c_func
(paren
r_struct
id|file
op_star
id|filp
comma
r_struct
id|vm_area_struct
op_star
id|vma
)paren
suffix:semicolon
r_extern
r_int
id|i830_copybuf
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
id|filp
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
r_extern
r_int
id|i830_docopy
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
id|filp
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
r_extern
r_void
id|i830_dma_quiescent
c_func
(paren
id|drm_device_t
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_int
id|i830_dma_vertex
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
id|filp
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
r_extern
r_int
id|i830_swap_bufs
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
id|filp
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
r_extern
r_int
id|i830_clear_bufs
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
id|filp
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
r_extern
r_int
id|i830_flip_bufs
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
id|filp
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
r_extern
r_int
id|i830_getparam
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
id|filp
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
r_extern
r_int
id|i830_setparam
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
id|filp
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
multiline_comment|/* i830_irq.c */
r_extern
r_int
id|i830_irq_emit
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
id|filp
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
r_extern
r_int
id|i830_irq_wait
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
id|filp
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
r_extern
r_int
id|i830_wait_irq
c_func
(paren
id|drm_device_t
op_star
id|dev
comma
r_int
id|irq_nr
)paren
suffix:semicolon
r_extern
r_int
id|i830_emit_irq
c_func
(paren
id|drm_device_t
op_star
id|dev
)paren
suffix:semicolon
r_extern
id|irqreturn_t
id|i830_driver_irq_handler
c_func
(paren
id|DRM_IRQ_ARGS
)paren
suffix:semicolon
r_extern
r_void
id|i830_driver_irq_preinstall
c_func
(paren
id|drm_device_t
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_void
id|i830_driver_irq_postinstall
c_func
(paren
id|drm_device_t
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_void
id|i830_driver_irq_uninstall
c_func
(paren
id|drm_device_t
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_void
id|i830_driver_pretakedown
c_func
(paren
id|drm_device_t
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_void
id|i830_driver_release
c_func
(paren
id|drm_device_t
op_star
id|dev
comma
r_struct
id|file
op_star
id|filp
)paren
suffix:semicolon
r_extern
r_int
id|i830_driver_dma_quiescent
c_func
(paren
id|drm_device_t
op_star
id|dev
)paren
suffix:semicolon
DECL|macro|I830_BASE
mdefine_line|#define I830_BASE(reg)&t;&t;((unsigned long) &bslash;&n;&t;&t;&t;&t;dev_priv-&gt;mmio_map-&gt;handle)
DECL|macro|I830_ADDR
mdefine_line|#define I830_ADDR(reg)&t;&t;(I830_BASE(reg) + reg)
DECL|macro|I830_DEREF
mdefine_line|#define I830_DEREF(reg)&t;&t;*(__volatile__ unsigned int *)I830_ADDR(reg)
DECL|macro|I830_READ
mdefine_line|#define I830_READ(reg)&t;&t;readl((volatile u32 *)I830_ADDR(reg))
DECL|macro|I830_WRITE
mdefine_line|#define I830_WRITE(reg,val) &t;writel(val, (volatile u32 *)I830_ADDR(reg))
DECL|macro|I830_DEREF16
mdefine_line|#define I830_DEREF16(reg)&t;*(__volatile__ u16 *)I830_ADDR(reg)
DECL|macro|I830_READ16
mdefine_line|#define I830_READ16(reg) &t;I830_DEREF16(reg)
DECL|macro|I830_WRITE16
mdefine_line|#define I830_WRITE16(reg,val)&t;do { I830_DEREF16(reg) = val; } while (0)
DECL|macro|I830_VERBOSE
mdefine_line|#define I830_VERBOSE 0
DECL|macro|RING_LOCALS
mdefine_line|#define RING_LOCALS&t;unsigned int outring, ringmask, outcount; &bslash;&n;                        volatile char *virt;
DECL|macro|BEGIN_LP_RING
mdefine_line|#define BEGIN_LP_RING(n) do {&t;&t;&t;&t;&bslash;&n;&t;if (I830_VERBOSE)&t;&t;&t;&t;&bslash;&n;&t;&t;printk(&quot;BEGIN_LP_RING(%d) in %s&bslash;n&quot;,&t;&bslash;&n;&t;&t;&t;  n, __FUNCTION__);&t;&t;&bslash;&n;&t;if (dev_priv-&gt;ring.space &lt; n*4)&t;&t;&t;&bslash;&n;&t;&t;i830_wait_ring(dev, n*4, __FUNCTION__);&t;&t;&bslash;&n;&t;outcount = 0;&t;&t;&t;&t;&t;&bslash;&n;&t;outring = dev_priv-&gt;ring.tail;&t;&t;&t;&bslash;&n;&t;ringmask = dev_priv-&gt;ring.tail_mask;&t;&t;&bslash;&n;&t;virt = dev_priv-&gt;ring.virtual_start;&t;&t;&bslash;&n;} while (0)
DECL|macro|OUT_RING
mdefine_line|#define OUT_RING(n) do {&t;&t;&t;&t;&t;&bslash;&n;&t;if (I830_VERBOSE) printk(&quot;   OUT_RING %x&bslash;n&quot;, (int)(n));&t;&bslash;&n;&t;*(volatile unsigned int *)(virt + outring) = n;&t;&t;&bslash;&n;        outcount++;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;outring += 4;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;outring &amp;= ringmask;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|ADVANCE_LP_RING
mdefine_line|#define ADVANCE_LP_RING() do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (I830_VERBOSE) printk(&quot;ADVANCE_LP_RING %x&bslash;n&quot;, outring);&t;&bslash;&n;&t;dev_priv-&gt;ring.tail = outring;&t;&t;&t;&t;&t;&bslash;&n;&t;dev_priv-&gt;ring.space -= outcount * 4;&t;&t;&t;&t;&bslash;&n;&t;I830_WRITE(LP_RING + RING_TAIL, outring);&t;&t;&t;&bslash;&n;} while(0)
r_extern
r_int
id|i830_wait_ring
c_func
(paren
id|drm_device_t
op_star
id|dev
comma
r_int
id|n
comma
r_const
r_char
op_star
id|caller
)paren
suffix:semicolon
DECL|macro|GFX_OP_USER_INTERRUPT
mdefine_line|#define GFX_OP_USER_INTERRUPT &t;&t;((0&lt;&lt;29)|(2&lt;&lt;23))
DECL|macro|GFX_OP_BREAKPOINT_INTERRUPT
mdefine_line|#define GFX_OP_BREAKPOINT_INTERRUPT&t;((0&lt;&lt;29)|(1&lt;&lt;23))
DECL|macro|CMD_REPORT_HEAD
mdefine_line|#define CMD_REPORT_HEAD&t;&t;&t;(7&lt;&lt;23)
DECL|macro|CMD_STORE_DWORD_IDX
mdefine_line|#define CMD_STORE_DWORD_IDX&t;&t;((0x21&lt;&lt;23) | 0x1)
DECL|macro|CMD_OP_BATCH_BUFFER
mdefine_line|#define CMD_OP_BATCH_BUFFER  ((0x0&lt;&lt;29)|(0x30&lt;&lt;23)|0x1)
DECL|macro|STATE3D_LOAD_STATE_IMMEDIATE_2
mdefine_line|#define STATE3D_LOAD_STATE_IMMEDIATE_2      ((0x3&lt;&lt;29)|(0x1d&lt;&lt;24)|(0x03&lt;&lt;16))
DECL|macro|LOAD_TEXTURE_MAP0
mdefine_line|#define LOAD_TEXTURE_MAP0                   (1&lt;&lt;11)
DECL|macro|INST_PARSER_CLIENT
mdefine_line|#define INST_PARSER_CLIENT   0x00000000
DECL|macro|INST_OP_FLUSH
mdefine_line|#define INST_OP_FLUSH        0x02000000
DECL|macro|INST_FLUSH_MAP_CACHE
mdefine_line|#define INST_FLUSH_MAP_CACHE 0x00000001
DECL|macro|BB1_START_ADDR_MASK
mdefine_line|#define BB1_START_ADDR_MASK   (~0x7)
DECL|macro|BB1_PROTECTED
mdefine_line|#define BB1_PROTECTED         (1&lt;&lt;0)
DECL|macro|BB1_UNPROTECTED
mdefine_line|#define BB1_UNPROTECTED       (0&lt;&lt;0)
DECL|macro|BB2_END_ADDR_MASK
mdefine_line|#define BB2_END_ADDR_MASK     (~0x7)
DECL|macro|I830REG_HWSTAM
mdefine_line|#define I830REG_HWSTAM&t;&t;0x02098
DECL|macro|I830REG_INT_IDENTITY_R
mdefine_line|#define I830REG_INT_IDENTITY_R&t;0x020a4
DECL|macro|I830REG_INT_MASK_R
mdefine_line|#define I830REG_INT_MASK_R &t;0x020a8
DECL|macro|I830REG_INT_ENABLE_R
mdefine_line|#define I830REG_INT_ENABLE_R&t;0x020a0
DECL|macro|I830_IRQ_RESERVED
mdefine_line|#define I830_IRQ_RESERVED ((1&lt;&lt;13)|(3&lt;&lt;2))
DECL|macro|LP_RING
mdefine_line|#define LP_RING     &t;&t;0x2030
DECL|macro|HP_RING
mdefine_line|#define HP_RING     &t;&t;0x2040
DECL|macro|RING_TAIL
mdefine_line|#define RING_TAIL      &t;&t;0x00
DECL|macro|TAIL_ADDR
mdefine_line|#define TAIL_ADDR&t;&t;0x001FFFF8
DECL|macro|RING_HEAD
mdefine_line|#define RING_HEAD      &t;&t;0x04
DECL|macro|HEAD_WRAP_COUNT
mdefine_line|#define HEAD_WRAP_COUNT     &t;0xFFE00000
DECL|macro|HEAD_WRAP_ONE
mdefine_line|#define HEAD_WRAP_ONE       &t;0x00200000
DECL|macro|HEAD_ADDR
mdefine_line|#define HEAD_ADDR           &t;0x001FFFFC
DECL|macro|RING_START
mdefine_line|#define RING_START     &t;&t;0x08
DECL|macro|START_ADDR
mdefine_line|#define START_ADDR          &t;0x0xFFFFF000
DECL|macro|RING_LEN
mdefine_line|#define RING_LEN       &t;&t;0x0C
DECL|macro|RING_NR_PAGES
mdefine_line|#define RING_NR_PAGES       &t;0x001FF000 
DECL|macro|RING_REPORT_MASK
mdefine_line|#define RING_REPORT_MASK    &t;0x00000006
DECL|macro|RING_REPORT_64K
mdefine_line|#define RING_REPORT_64K     &t;0x00000002
DECL|macro|RING_REPORT_128K
mdefine_line|#define RING_REPORT_128K    &t;0x00000004
DECL|macro|RING_NO_REPORT
mdefine_line|#define RING_NO_REPORT      &t;0x00000000
DECL|macro|RING_VALID_MASK
mdefine_line|#define RING_VALID_MASK     &t;0x00000001
DECL|macro|RING_VALID
mdefine_line|#define RING_VALID          &t;0x00000001
DECL|macro|RING_INVALID
mdefine_line|#define RING_INVALID        &t;0x00000000
DECL|macro|GFX_OP_SCISSOR
mdefine_line|#define GFX_OP_SCISSOR         ((0x3&lt;&lt;29)|(0x1c&lt;&lt;24)|(0x10&lt;&lt;19))
DECL|macro|SC_UPDATE_SCISSOR
mdefine_line|#define SC_UPDATE_SCISSOR       (0x1&lt;&lt;1)
DECL|macro|SC_ENABLE_MASK
mdefine_line|#define SC_ENABLE_MASK          (0x1&lt;&lt;0)
DECL|macro|SC_ENABLE
mdefine_line|#define SC_ENABLE               (0x1&lt;&lt;0)
DECL|macro|GFX_OP_SCISSOR_INFO
mdefine_line|#define GFX_OP_SCISSOR_INFO    ((0x3&lt;&lt;29)|(0x1d&lt;&lt;24)|(0x81&lt;&lt;16)|(0x1))
DECL|macro|SCI_YMIN_MASK
mdefine_line|#define SCI_YMIN_MASK      (0xffff&lt;&lt;16)
DECL|macro|SCI_XMIN_MASK
mdefine_line|#define SCI_XMIN_MASK      (0xffff&lt;&lt;0)
DECL|macro|SCI_YMAX_MASK
mdefine_line|#define SCI_YMAX_MASK      (0xffff&lt;&lt;16)
DECL|macro|SCI_XMAX_MASK
mdefine_line|#define SCI_XMAX_MASK      (0xffff&lt;&lt;0)
DECL|macro|GFX_OP_SCISSOR_ENABLE
mdefine_line|#define GFX_OP_SCISSOR_ENABLE&t; ((0x3&lt;&lt;29)|(0x1c&lt;&lt;24)|(0x10&lt;&lt;19))
DECL|macro|GFX_OP_SCISSOR_RECT
mdefine_line|#define GFX_OP_SCISSOR_RECT&t; ((0x3&lt;&lt;29)|(0x1d&lt;&lt;24)|(0x81&lt;&lt;16)|1)
DECL|macro|GFX_OP_COLOR_FACTOR
mdefine_line|#define GFX_OP_COLOR_FACTOR      ((0x3&lt;&lt;29)|(0x1d&lt;&lt;24)|(0x1&lt;&lt;16)|0x0)
DECL|macro|GFX_OP_STIPPLE
mdefine_line|#define GFX_OP_STIPPLE           ((0x3&lt;&lt;29)|(0x1d&lt;&lt;24)|(0x83&lt;&lt;16))
DECL|macro|GFX_OP_MAP_INFO
mdefine_line|#define GFX_OP_MAP_INFO          ((0x3&lt;&lt;29)|(0x1d&lt;&lt;24)|0x4)
DECL|macro|GFX_OP_DESTBUFFER_VARS
mdefine_line|#define GFX_OP_DESTBUFFER_VARS   ((0x3&lt;&lt;29)|(0x1d&lt;&lt;24)|(0x85&lt;&lt;16)|0x0)
DECL|macro|GFX_OP_DRAWRECT_INFO
mdefine_line|#define GFX_OP_DRAWRECT_INFO     ((0x3&lt;&lt;29)|(0x1d&lt;&lt;24)|(0x80&lt;&lt;16)|(0x3))
DECL|macro|GFX_OP_PRIMITIVE
mdefine_line|#define GFX_OP_PRIMITIVE         ((0x3&lt;&lt;29)|(0x1f&lt;&lt;24))
DECL|macro|CMD_OP_DESTBUFFER_INFO
mdefine_line|#define CMD_OP_DESTBUFFER_INFO&t; ((0x3&lt;&lt;29)|(0x1d&lt;&lt;24)|(0x8e&lt;&lt;16)|1)
DECL|macro|CMD_OP_DISPLAYBUFFER_INFO
mdefine_line|#define CMD_OP_DISPLAYBUFFER_INFO ((0x0&lt;&lt;29)|(0x14&lt;&lt;23)|2)
DECL|macro|ASYNC_FLIP
mdefine_line|#define ASYNC_FLIP                (1&lt;&lt;22)
DECL|macro|CMD_3D
mdefine_line|#define CMD_3D                          (0x3&lt;&lt;29)
DECL|macro|STATE3D_CONST_BLEND_COLOR_CMD
mdefine_line|#define STATE3D_CONST_BLEND_COLOR_CMD   (CMD_3D|(0x1d&lt;&lt;24)|(0x88&lt;&lt;16))
DECL|macro|STATE3D_MAP_COORD_SETBIND_CMD
mdefine_line|#define STATE3D_MAP_COORD_SETBIND_CMD   (CMD_3D|(0x1d&lt;&lt;24)|(0x02&lt;&lt;16))
DECL|macro|BR00_BITBLT_CLIENT
mdefine_line|#define BR00_BITBLT_CLIENT   0x40000000
DECL|macro|BR00_OP_COLOR_BLT
mdefine_line|#define BR00_OP_COLOR_BLT    0x10000000
DECL|macro|BR00_OP_SRC_COPY_BLT
mdefine_line|#define BR00_OP_SRC_COPY_BLT 0x10C00000
DECL|macro|BR13_SOLID_PATTERN
mdefine_line|#define BR13_SOLID_PATTERN   0x80000000
DECL|macro|BUF_3D_ID_COLOR_BACK
mdefine_line|#define BUF_3D_ID_COLOR_BACK    (0x3&lt;&lt;24)
DECL|macro|BUF_3D_ID_DEPTH
mdefine_line|#define BUF_3D_ID_DEPTH         (0x7&lt;&lt;24)
DECL|macro|BUF_3D_USE_FENCE
mdefine_line|#define BUF_3D_USE_FENCE        (1&lt;&lt;23)
DECL|macro|BUF_3D_PITCH
mdefine_line|#define BUF_3D_PITCH(x)         (((x)/4)&lt;&lt;2)
DECL|macro|CMD_OP_MAP_PALETTE_LOAD
mdefine_line|#define CMD_OP_MAP_PALETTE_LOAD&t;((3&lt;&lt;29)|(0x1d&lt;&lt;24)|(0x82&lt;&lt;16)|255)
DECL|macro|MAP_PALETTE_NUM
mdefine_line|#define MAP_PALETTE_NUM(x)&t;((x&lt;&lt;8) &amp; (1&lt;&lt;8))
DECL|macro|MAP_PALETTE_BOTH
mdefine_line|#define MAP_PALETTE_BOTH&t;(1&lt;&lt;11)
DECL|macro|XY_COLOR_BLT_CMD
mdefine_line|#define XY_COLOR_BLT_CMD&t;&t;((2&lt;&lt;29)|(0x50&lt;&lt;22)|0x4)
DECL|macro|XY_COLOR_BLT_WRITE_ALPHA
mdefine_line|#define XY_COLOR_BLT_WRITE_ALPHA&t;(1&lt;&lt;21)
DECL|macro|XY_COLOR_BLT_WRITE_RGB
mdefine_line|#define XY_COLOR_BLT_WRITE_RGB&t;&t;(1&lt;&lt;20)
DECL|macro|XY_SRC_COPY_BLT_CMD
mdefine_line|#define XY_SRC_COPY_BLT_CMD             ((2&lt;&lt;29)|(0x53&lt;&lt;22)|6)
DECL|macro|XY_SRC_COPY_BLT_WRITE_ALPHA
mdefine_line|#define XY_SRC_COPY_BLT_WRITE_ALPHA     (1&lt;&lt;21)
DECL|macro|XY_SRC_COPY_BLT_WRITE_RGB
mdefine_line|#define XY_SRC_COPY_BLT_WRITE_RGB       (1&lt;&lt;20)
DECL|macro|MI_BATCH_BUFFER
mdefine_line|#define MI_BATCH_BUFFER &t;((0x30&lt;&lt;23)|1)
DECL|macro|MI_BATCH_BUFFER_START
mdefine_line|#define MI_BATCH_BUFFER_START &t;(0x31&lt;&lt;23)
DECL|macro|MI_BATCH_BUFFER_END
mdefine_line|#define MI_BATCH_BUFFER_END &t;(0xA&lt;&lt;23)
DECL|macro|MI_BATCH_NON_SECURE
mdefine_line|#define MI_BATCH_NON_SECURE&t;(1)
DECL|macro|MI_WAIT_FOR_EVENT
mdefine_line|#define MI_WAIT_FOR_EVENT       ((0x3&lt;&lt;23))
DECL|macro|MI_WAIT_FOR_PLANE_A_FLIP
mdefine_line|#define MI_WAIT_FOR_PLANE_A_FLIP      (1&lt;&lt;2) 
DECL|macro|MI_WAIT_FOR_PLANE_A_SCANLINES
mdefine_line|#define MI_WAIT_FOR_PLANE_A_SCANLINES (1&lt;&lt;1) 
DECL|macro|MI_LOAD_SCAN_LINES_INCL
mdefine_line|#define MI_LOAD_SCAN_LINES_INCL  ((0x12&lt;&lt;23))
macro_line|#endif
eof
