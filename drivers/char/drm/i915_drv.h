multiline_comment|/* i915_drv.h -- Private header for the I915 driver -*- linux-c -*-&n; */
multiline_comment|/**************************************************************************&n; * &n; * Copyright 2003 Tungsten Graphics, Inc., Cedar Park, Texas.&n; * All Rights Reserved.&n; * &n; **************************************************************************/
macro_line|#ifndef _I915_DRV_H_
DECL|macro|_I915_DRV_H_
mdefine_line|#define _I915_DRV_H_
multiline_comment|/* General customization:&n; */
DECL|macro|DRIVER_AUTHOR
mdefine_line|#define DRIVER_AUTHOR&t;&t;&quot;Tungsten Graphics, Inc.&quot;
DECL|macro|DRIVER_NAME
mdefine_line|#define DRIVER_NAME&t;&t;&quot;i915&quot;
DECL|macro|DRIVER_DESC
mdefine_line|#define DRIVER_DESC&t;&t;&quot;Intel Graphics&quot;
DECL|macro|DRIVER_DATE
mdefine_line|#define DRIVER_DATE&t;&t;&quot;20040405&quot;
multiline_comment|/* Interface history:&n; *&n; * 1.1: Original.&n; */
DECL|macro|DRIVER_MAJOR
mdefine_line|#define DRIVER_MAJOR&t;&t;1
DECL|macro|DRIVER_MINOR
mdefine_line|#define DRIVER_MINOR&t;&t;1
DECL|macro|DRIVER_PATCHLEVEL
mdefine_line|#define DRIVER_PATCHLEVEL&t;0
multiline_comment|/* We use our own dma mechanisms, not the drm template code.  However,&n; * the shared IRQ code is useful to us:&n; */
DECL|macro|__HAVE_PM
mdefine_line|#define __HAVE_PM&t;&t;1
DECL|struct|_drm_i915_ring_buffer
r_typedef
r_struct
id|_drm_i915_ring_buffer
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
DECL|member|map
id|drm_local_map_t
id|map
suffix:semicolon
DECL|typedef|drm_i915_ring_buffer_t
)brace
id|drm_i915_ring_buffer_t
suffix:semicolon
DECL|struct|mem_block
r_struct
id|mem_block
(brace
DECL|member|next
r_struct
id|mem_block
op_star
id|next
suffix:semicolon
DECL|member|prev
r_struct
id|mem_block
op_star
id|prev
suffix:semicolon
DECL|member|start
r_int
id|start
suffix:semicolon
DECL|member|size
r_int
id|size
suffix:semicolon
DECL|member|filp
id|DRMFILE
id|filp
suffix:semicolon
multiline_comment|/* 0: free, -1: heap, other: real files */
)brace
suffix:semicolon
DECL|struct|drm_i915_private
r_typedef
r_struct
id|drm_i915_private
(brace
DECL|member|sarea
id|drm_local_map_t
op_star
id|sarea
suffix:semicolon
DECL|member|mmio_map
id|drm_local_map_t
op_star
id|mmio_map
suffix:semicolon
DECL|member|sarea_priv
id|drm_i915_sarea_t
op_star
id|sarea_priv
suffix:semicolon
DECL|member|ring
id|drm_i915_ring_buffer_t
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
DECL|member|back_offset
r_int
id|back_offset
suffix:semicolon
DECL|member|front_offset
r_int
id|front_offset
suffix:semicolon
DECL|member|current_page
r_int
id|current_page
suffix:semicolon
DECL|member|page_flipping
r_int
id|page_flipping
suffix:semicolon
DECL|member|use_mi_batchbuffer_start
r_int
id|use_mi_batchbuffer_start
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
DECL|member|tex_lru_log_granularity
r_int
id|tex_lru_log_granularity
suffix:semicolon
DECL|member|allow_batchbuffer
r_int
id|allow_batchbuffer
suffix:semicolon
DECL|member|agp_heap
r_struct
id|mem_block
op_star
id|agp_heap
suffix:semicolon
DECL|typedef|drm_i915_private_t
)brace
id|drm_i915_private_t
suffix:semicolon
multiline_comment|/* i915_dma.c */
r_extern
r_int
id|i915_dma_init
c_func
(paren
id|DRM_IOCTL_ARGS
)paren
suffix:semicolon
r_extern
r_int
id|i915_dma_cleanup
c_func
(paren
id|drm_device_t
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_int
id|i915_flush_ioctl
c_func
(paren
id|DRM_IOCTL_ARGS
)paren
suffix:semicolon
r_extern
r_int
id|i915_batchbuffer
c_func
(paren
id|DRM_IOCTL_ARGS
)paren
suffix:semicolon
r_extern
r_int
id|i915_flip_bufs
c_func
(paren
id|DRM_IOCTL_ARGS
)paren
suffix:semicolon
r_extern
r_int
id|i915_getparam
c_func
(paren
id|DRM_IOCTL_ARGS
)paren
suffix:semicolon
r_extern
r_int
id|i915_setparam
c_func
(paren
id|DRM_IOCTL_ARGS
)paren
suffix:semicolon
r_extern
r_int
id|i915_cmdbuffer
c_func
(paren
id|DRM_IOCTL_ARGS
)paren
suffix:semicolon
r_extern
r_void
id|i915_kernel_lost_context
c_func
(paren
id|drm_device_t
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_void
id|i915_driver_pretakedown
c_func
(paren
id|drm_device_t
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_void
id|i915_driver_prerelease
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
multiline_comment|/* i915_irq.c */
r_extern
r_int
id|i915_irq_emit
c_func
(paren
id|DRM_IOCTL_ARGS
)paren
suffix:semicolon
r_extern
r_int
id|i915_irq_wait
c_func
(paren
id|DRM_IOCTL_ARGS
)paren
suffix:semicolon
r_extern
r_int
id|i915_wait_irq
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
id|i915_emit_irq
c_func
(paren
id|drm_device_t
op_star
id|dev
)paren
suffix:semicolon
r_extern
id|irqreturn_t
id|i915_driver_irq_handler
c_func
(paren
id|DRM_IRQ_ARGS
)paren
suffix:semicolon
r_extern
r_void
id|i915_driver_irq_preinstall
c_func
(paren
id|drm_device_t
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_void
id|i915_driver_irq_postinstall
c_func
(paren
id|drm_device_t
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_void
id|i915_driver_irq_uninstall
c_func
(paren
id|drm_device_t
op_star
id|dev
)paren
suffix:semicolon
multiline_comment|/* i915_mem.c */
r_extern
r_int
id|i915_mem_alloc
c_func
(paren
id|DRM_IOCTL_ARGS
)paren
suffix:semicolon
r_extern
r_int
id|i915_mem_free
c_func
(paren
id|DRM_IOCTL_ARGS
)paren
suffix:semicolon
r_extern
r_int
id|i915_mem_init_heap
c_func
(paren
id|DRM_IOCTL_ARGS
)paren
suffix:semicolon
r_extern
r_void
id|i915_mem_takedown
c_func
(paren
r_struct
id|mem_block
op_star
op_star
id|heap
)paren
suffix:semicolon
r_extern
r_void
id|i915_mem_release
c_func
(paren
id|drm_device_t
op_star
id|dev
comma
id|DRMFILE
id|filp
comma
r_struct
id|mem_block
op_star
id|heap
)paren
suffix:semicolon
DECL|macro|I915_READ
mdefine_line|#define I915_READ(reg)          DRM_READ32(dev_priv-&gt;mmio_map, reg)
DECL|macro|I915_WRITE
mdefine_line|#define I915_WRITE(reg,val)     DRM_WRITE32(dev_priv-&gt;mmio_map, reg, val)
DECL|macro|I915_READ16
mdefine_line|#define I915_READ16(reg) &t;DRM_READ16(dev_priv-&gt;mmio_map, reg)
DECL|macro|I915_WRITE16
mdefine_line|#define I915_WRITE16(reg,val)&t;DRM_WRITE16(dev_priv-&gt;mmio_map, reg, val)
DECL|macro|I915_VERBOSE
mdefine_line|#define I915_VERBOSE 0
DECL|macro|RING_LOCALS
mdefine_line|#define RING_LOCALS&t;unsigned int outring, ringmask, outcount; &bslash;&n;                        volatile char *virt;
DECL|macro|BEGIN_LP_RING
mdefine_line|#define BEGIN_LP_RING(n) do {&t;&t;&t;&t;&bslash;&n;&t;if (I915_VERBOSE)&t;&t;&t;&t;&bslash;&n;&t;&t;DRM_DEBUG(&quot;BEGIN_LP_RING(%d) in %s&bslash;n&quot;,&t;&bslash;&n;&t;&t;&t;  n, __FUNCTION__);&t;&t;&bslash;&n;&t;if (dev_priv-&gt;ring.space &lt; n*4)&t;&t;&t;&bslash;&n;&t;&t;i915_wait_ring(dev, n*4, __FUNCTION__);&t;&t;&bslash;&n;&t;outcount = 0;&t;&t;&t;&t;&t;&bslash;&n;&t;outring = dev_priv-&gt;ring.tail;&t;&t;&t;&bslash;&n;&t;ringmask = dev_priv-&gt;ring.tail_mask;&t;&t;&bslash;&n;&t;virt = dev_priv-&gt;ring.virtual_start;&t;&t;&bslash;&n;} while (0)
DECL|macro|OUT_RING
mdefine_line|#define OUT_RING(n) do {&t;&t;&t;&t;&t;&bslash;&n;&t;if (I915_VERBOSE) DRM_DEBUG(&quot;   OUT_RING %x&bslash;n&quot;, (int)(n));&t;&bslash;&n;&t;*(volatile unsigned int *)(virt + outring) = n;&t;&t;&bslash;&n;        outcount++;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;outring += 4;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;outring &amp;= ringmask;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|ADVANCE_LP_RING
mdefine_line|#define ADVANCE_LP_RING() do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (I915_VERBOSE) DRM_DEBUG(&quot;ADVANCE_LP_RING %x&bslash;n&quot;, outring);&t;&bslash;&n;&t;dev_priv-&gt;ring.tail = outring;&t;&t;&t;&t;&t;&bslash;&n;&t;dev_priv-&gt;ring.space -= outcount * 4;&t;&t;&t;&t;&bslash;&n;&t;I915_WRITE(LP_RING + RING_TAIL, outring);&t;&t;&t;&bslash;&n;} while(0)
r_extern
r_int
id|i915_wait_ring
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
DECL|macro|I915REG_HWSTAM
mdefine_line|#define I915REG_HWSTAM&t;&t;0x02098
DECL|macro|I915REG_INT_IDENTITY_R
mdefine_line|#define I915REG_INT_IDENTITY_R&t;0x020a4
DECL|macro|I915REG_INT_MASK_R
mdefine_line|#define I915REG_INT_MASK_R &t;0x020a8
DECL|macro|I915REG_INT_ENABLE_R
mdefine_line|#define I915REG_INT_ENABLE_R&t;0x020a0
DECL|macro|SRX_INDEX
mdefine_line|#define SRX_INDEX&t;&t;0x3c4
DECL|macro|SRX_DATA
mdefine_line|#define SRX_DATA&t;&t;0x3c5
DECL|macro|SR01
mdefine_line|#define SR01&t;&t;&t;1
DECL|macro|SR01_SCREEN_OFF
mdefine_line|#define SR01_SCREEN_OFF &t;(1&lt;&lt;5)
DECL|macro|PPCR
mdefine_line|#define PPCR&t;&t;&t;0x61204
DECL|macro|PPCR_ON
mdefine_line|#define PPCR_ON&t;&t;&t;(1&lt;&lt;0)
DECL|macro|ADPA
mdefine_line|#define ADPA&t;&t;&t;0x61100
DECL|macro|ADPA_DPMS_MASK
mdefine_line|#define ADPA_DPMS_MASK&t;&t;(~(3&lt;&lt;10))
DECL|macro|ADPA_DPMS_ON
mdefine_line|#define ADPA_DPMS_ON&t;&t;(0&lt;&lt;10)
DECL|macro|ADPA_DPMS_SUSPEND
mdefine_line|#define ADPA_DPMS_SUSPEND&t;(1&lt;&lt;10)
DECL|macro|ADPA_DPMS_STANDBY
mdefine_line|#define ADPA_DPMS_STANDBY&t;(2&lt;&lt;10)
DECL|macro|ADPA_DPMS_OFF
mdefine_line|#define ADPA_DPMS_OFF&t;&t;(3&lt;&lt;10)
DECL|macro|NOPID
mdefine_line|#define NOPID                   0x2094
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
DECL|macro|CMD_OP_DISPLAYBUFFER_INFO
mdefine_line|#define CMD_OP_DISPLAYBUFFER_INFO ((0x0&lt;&lt;29)|(0x14&lt;&lt;23)|2)
DECL|macro|ASYNC_FLIP
mdefine_line|#define ASYNC_FLIP                (1&lt;&lt;22)
DECL|macro|CMD_OP_DESTBUFFER_INFO
mdefine_line|#define CMD_OP_DESTBUFFER_INFO&t; ((0x3&lt;&lt;29)|(0x1d&lt;&lt;24)|(0x8e&lt;&lt;16)|1)
macro_line|#endif
eof
