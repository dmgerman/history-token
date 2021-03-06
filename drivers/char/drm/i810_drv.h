multiline_comment|/* i810_drv.h -- Private header for the Matrox g200/g400 driver -*- linux-c -*-&n; * Created: Mon Dec 13 01:50:01 1999 by jhartmann@precisioninsight.com&n; *&n; * Copyright 1999 Precision Insight, Inc., Cedar Park, Texas.&n; * Copyright 2000 VA Linux Systems, Inc., Sunnyvale, California.&n; * All rights reserved.&n; *&n; * Permission is hereby granted, free of charge, to any person obtaining a&n; * copy of this software and associated documentation files (the &quot;Software&quot;),&n; * to deal in the Software without restriction, including without limitation&n; * the rights to use, copy, modify, merge, publish, distribute, sublicense,&n; * and/or sell copies of the Software, and to permit persons to whom the&n; * Software is furnished to do so, subject to the following conditions:&n; *&n; * The above copyright notice and this permission notice (including the next&n; * paragraph) shall be included in all copies or substantial portions of the&n; * Software.&n; *&n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR&n; * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n; * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL&n; * PRECISION INSIGHT AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR&n; * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,&n; * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER&n; * DEALINGS IN THE SOFTWARE.&n; *&n; * Authors: Rickard E. (Rik) Faith &lt;faith@valinux.com&gt;&n; * &t;    Jeff Hartmann &lt;jhartmann@valinux.com&gt;&n; *&n; */
macro_line|#ifndef _I810_DRV_H_
DECL|macro|_I810_DRV_H_
mdefine_line|#define _I810_DRV_H_
multiline_comment|/* General customization:&n; */
DECL|macro|DRIVER_AUTHOR
mdefine_line|#define DRIVER_AUTHOR&t;&t;&quot;VA Linux Systems Inc.&quot;
DECL|macro|DRIVER_NAME
mdefine_line|#define DRIVER_NAME&t;&t;&quot;i810&quot;
DECL|macro|DRIVER_DESC
mdefine_line|#define DRIVER_DESC&t;&t;&quot;Intel i810&quot;
DECL|macro|DRIVER_DATE
mdefine_line|#define DRIVER_DATE&t;&t;&quot;20030605&quot;
multiline_comment|/* Interface history&n; *&n; * 1.1   - XFree86 4.1&n; * 1.2   - XvMC interfaces&n; *       - XFree86 4.2&n; * 1.2.1 - Disable copying code (leave stub ioctls for backwards compatibility)&n; *       - Remove requirement for interrupt (leave stubs again)&n; * 1.3   - Add page flipping.&n; * 1.4   - fix DRM interface&n; */
DECL|macro|DRIVER_MAJOR
mdefine_line|#define DRIVER_MAJOR&t;&t;1
DECL|macro|DRIVER_MINOR
mdefine_line|#define DRIVER_MINOR&t;&t;4
DECL|macro|DRIVER_PATCHLEVEL
mdefine_line|#define DRIVER_PATCHLEVEL&t;0
DECL|struct|drm_i810_buf_priv
r_typedef
r_struct
id|drm_i810_buf_priv
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
op_star
r_virtual
suffix:semicolon
DECL|member|kernel_virtual
r_void
op_star
id|kernel_virtual
suffix:semicolon
DECL|typedef|drm_i810_buf_priv_t
)brace
id|drm_i810_buf_priv_t
suffix:semicolon
DECL|struct|_drm_i810_ring_buffer
r_typedef
r_struct
id|_drm_i810_ring_buffer
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
DECL|typedef|drm_i810_ring_buffer_t
)brace
id|drm_i810_ring_buffer_t
suffix:semicolon
DECL|struct|drm_i810_private
r_typedef
r_struct
id|drm_i810_private
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
id|drm_i810_sarea_t
op_star
id|sarea_priv
suffix:semicolon
DECL|member|ring
id|drm_i810_ring_buffer_t
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
DECL|member|overlay_offset
r_int
id|overlay_offset
suffix:semicolon
DECL|member|overlay_physical
r_int
id|overlay_physical
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
DECL|member|front_offset
r_int
id|front_offset
suffix:semicolon
DECL|typedef|drm_i810_private_t
)brace
id|drm_i810_private_t
suffix:semicolon
multiline_comment|/* i810_dma.c */
r_extern
r_void
id|i810_reclaim_buffers
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
id|i810_mmap_buffers
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
id|i810_driver_dma_quiescent
c_func
(paren
id|drm_device_t
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_void
id|i810_driver_release
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
r_void
id|i810_driver_pretakedown
c_func
(paren
id|drm_device_t
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_void
id|i810_driver_prerelease
c_func
(paren
id|drm_device_t
op_star
id|dev
comma
id|DRMFILE
id|filp
)paren
suffix:semicolon
DECL|macro|I810_BASE
mdefine_line|#define I810_BASE(reg)&t;&t;((unsigned long) &bslash;&n;&t;&t;&t;&t;dev_priv-&gt;mmio_map-&gt;handle)
DECL|macro|I810_ADDR
mdefine_line|#define I810_ADDR(reg)&t;&t;(I810_BASE(reg) + reg)
DECL|macro|I810_DEREF
mdefine_line|#define I810_DEREF(reg)&t;&t;*(__volatile__ int *)I810_ADDR(reg)
DECL|macro|I810_READ
mdefine_line|#define I810_READ(reg)&t;&t;I810_DEREF(reg)
DECL|macro|I810_WRITE
mdefine_line|#define I810_WRITE(reg,val) &t;do { I810_DEREF(reg) = val; } while (0)
DECL|macro|I810_DEREF16
mdefine_line|#define I810_DEREF16(reg)&t;*(__volatile__ u16 *)I810_ADDR(reg)
DECL|macro|I810_READ16
mdefine_line|#define I810_READ16(reg)&t;I810_DEREF16(reg)
DECL|macro|I810_WRITE16
mdefine_line|#define I810_WRITE16(reg,val)&t;do { I810_DEREF16(reg) = val; } while (0)
DECL|macro|I810_VERBOSE
mdefine_line|#define I810_VERBOSE 0
DECL|macro|RING_LOCALS
mdefine_line|#define RING_LOCALS&t;unsigned int outring, ringmask; &bslash;&n;                        volatile char *virt;
DECL|macro|BEGIN_LP_RING
mdefine_line|#define BEGIN_LP_RING(n) do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (I810_VERBOSE)                                               &bslash;&n;           DRM_DEBUG(&quot;BEGIN_LP_RING(%d) in %s&bslash;n&quot;, n, __FUNCTION__);&t;&bslash;&n;&t;if (dev_priv-&gt;ring.space &lt; n*4)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;i810_wait_ring(dev, n*4);&t;&t;&t;&t;&bslash;&n;&t;dev_priv-&gt;ring.space -= n*4;&t;&t;&t;&t;&t;&bslash;&n;&t;outring = dev_priv-&gt;ring.tail;&t;&t;&t;&t;&t;&bslash;&n;&t;ringmask = dev_priv-&gt;ring.tail_mask;&t;&t;&t;&t;&bslash;&n;&t;virt = dev_priv-&gt;ring.virtual_start;&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|ADVANCE_LP_RING
mdefine_line|#define ADVANCE_LP_RING() do {&t;&t;&t;&t;        &bslash;&n;&t;if (I810_VERBOSE) DRM_DEBUG(&quot;ADVANCE_LP_RING&bslash;n&quot;);    &t;&bslash;&n;&t;dev_priv-&gt;ring.tail = outring;&t;&t;        &t;&bslash;&n;&t;I810_WRITE(LP_RING + RING_TAIL, outring);&t;        &bslash;&n;} while(0)
DECL|macro|OUT_RING
mdefine_line|#define OUT_RING(n) do {  &t;&t;&t;&t;                &bslash;&n;&t;if (I810_VERBOSE) DRM_DEBUG(&quot;   OUT_RING %x&bslash;n&quot;, (int)(n));&t;&bslash;&n;&t;*(volatile unsigned int *)(virt + outring) = n;&t;                &bslash;&n;&t;outring += 4;&t;&t;&t;&t;&t;                &bslash;&n;&t;outring &amp;= ringmask;&t;&t;&t;                        &bslash;&n;} while (0)
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
DECL|macro|I810REG_HWSTAM
mdefine_line|#define I810REG_HWSTAM&t;&t;0x02098
DECL|macro|I810REG_INT_IDENTITY_R
mdefine_line|#define I810REG_INT_IDENTITY_R&t;0x020a4
DECL|macro|I810REG_INT_MASK_R
mdefine_line|#define I810REG_INT_MASK_R &t;0x020a8
DECL|macro|I810REG_INT_ENABLE_R
mdefine_line|#define I810REG_INT_ENABLE_R&t;0x020a0
DECL|macro|LP_RING
mdefine_line|#define LP_RING     &t;&t;0x2030
DECL|macro|HP_RING
mdefine_line|#define HP_RING     &t;&t;0x2040
DECL|macro|RING_TAIL
mdefine_line|#define RING_TAIL      &t;&t;0x00
DECL|macro|TAIL_ADDR
mdefine_line|#define TAIL_ADDR&t;&t;0x000FFFF8
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
mdefine_line|#define START_ADDR          &t;0x00FFFFF8
DECL|macro|RING_LEN
mdefine_line|#define RING_LEN       &t;&t;0x0C
DECL|macro|RING_NR_PAGES
mdefine_line|#define RING_NR_PAGES       &t;0x000FF000
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
DECL|macro|GFX_OP_COLOR_FACTOR
mdefine_line|#define GFX_OP_COLOR_FACTOR      ((0x3&lt;&lt;29)|(0x1d&lt;&lt;24)|(0x1&lt;&lt;16)|0x0)
DECL|macro|GFX_OP_STIPPLE
mdefine_line|#define GFX_OP_STIPPLE           ((0x3&lt;&lt;29)|(0x1d&lt;&lt;24)|(0x83&lt;&lt;16))
DECL|macro|GFX_OP_MAP_INFO
mdefine_line|#define GFX_OP_MAP_INFO          ((0x3&lt;&lt;29)|(0x1d&lt;&lt;24)|0x2)
DECL|macro|GFX_OP_DESTBUFFER_VARS
mdefine_line|#define GFX_OP_DESTBUFFER_VARS   ((0x3&lt;&lt;29)|(0x1d&lt;&lt;24)|(0x85&lt;&lt;16)|0x0)
DECL|macro|GFX_OP_DRAWRECT_INFO
mdefine_line|#define GFX_OP_DRAWRECT_INFO     ((0x3&lt;&lt;29)|(0x1d&lt;&lt;24)|(0x80&lt;&lt;16)|(0x3))
DECL|macro|GFX_OP_PRIMITIVE
mdefine_line|#define GFX_OP_PRIMITIVE         ((0x3&lt;&lt;29)|(0x1f&lt;&lt;24))
DECL|macro|CMD_OP_Z_BUFFER_INFO
mdefine_line|#define CMD_OP_Z_BUFFER_INFO     ((0x0&lt;&lt;29)|(0x16&lt;&lt;23))
DECL|macro|CMD_OP_DESTBUFFER_INFO
mdefine_line|#define CMD_OP_DESTBUFFER_INFO   ((0x0&lt;&lt;29)|(0x15&lt;&lt;23))
DECL|macro|CMD_OP_FRONTBUFFER_INFO
mdefine_line|#define CMD_OP_FRONTBUFFER_INFO  ((0x0&lt;&lt;29)|(0x14&lt;&lt;23))
DECL|macro|CMD_OP_WAIT_FOR_EVENT
mdefine_line|#define CMD_OP_WAIT_FOR_EVENT    ((0x0&lt;&lt;29)|(0x03&lt;&lt;23))
DECL|macro|BR00_BITBLT_CLIENT
mdefine_line|#define BR00_BITBLT_CLIENT   0x40000000
DECL|macro|BR00_OP_COLOR_BLT
mdefine_line|#define BR00_OP_COLOR_BLT    0x10000000
DECL|macro|BR00_OP_SRC_COPY_BLT
mdefine_line|#define BR00_OP_SRC_COPY_BLT 0x10C00000
DECL|macro|BR13_SOLID_PATTERN
mdefine_line|#define BR13_SOLID_PATTERN   0x80000000
DECL|macro|WAIT_FOR_PLANE_A_SCANLINES
mdefine_line|#define WAIT_FOR_PLANE_A_SCANLINES (1&lt;&lt;1) 
DECL|macro|WAIT_FOR_PLANE_A_FLIP
mdefine_line|#define WAIT_FOR_PLANE_A_FLIP      (1&lt;&lt;2) 
DECL|macro|WAIT_FOR_VBLANK
mdefine_line|#define WAIT_FOR_VBLANK (1&lt;&lt;3)
macro_line|#endif
eof
