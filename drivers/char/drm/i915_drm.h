macro_line|#ifndef _I915_DRM_H_
DECL|macro|_I915_DRM_H_
mdefine_line|#define _I915_DRM_H_
multiline_comment|/* Please note that modifications to all structs defined here are&n; * subject to backwards-compatibility constraints.&n; */
macro_line|#include &quot;drm.h&quot;
multiline_comment|/* Each region is a minimum of 16k, and there are at most 255 of them.&n; */
DECL|macro|I915_NR_TEX_REGIONS
mdefine_line|#define I915_NR_TEX_REGIONS 255&t;/* table size 2k - maximum due to use&n;&t;&t;&t;&t; * of chars for next/prev indices */
DECL|macro|I915_LOG_MIN_TEX_REGION_SIZE
mdefine_line|#define I915_LOG_MIN_TEX_REGION_SIZE 14
DECL|struct|_drm_i915_init
r_typedef
r_struct
id|_drm_i915_init
(brace
r_enum
(brace
DECL|enumerator|I915_INIT_DMA
id|I915_INIT_DMA
op_assign
l_int|0x01
comma
DECL|enumerator|I915_CLEANUP_DMA
id|I915_CLEANUP_DMA
op_assign
l_int|0x02
comma
DECL|enumerator|I915_RESUME_DMA
id|I915_RESUME_DMA
op_assign
l_int|0x03
DECL|member|func
)brace
id|func
suffix:semicolon
DECL|member|mmio_offset
r_int
r_int
id|mmio_offset
suffix:semicolon
DECL|member|sarea_priv_offset
r_int
id|sarea_priv_offset
suffix:semicolon
DECL|member|ring_start
r_int
r_int
id|ring_start
suffix:semicolon
DECL|member|ring_end
r_int
r_int
id|ring_end
suffix:semicolon
DECL|member|ring_size
r_int
r_int
id|ring_size
suffix:semicolon
DECL|member|front_offset
r_int
r_int
id|front_offset
suffix:semicolon
DECL|member|back_offset
r_int
r_int
id|back_offset
suffix:semicolon
DECL|member|depth_offset
r_int
r_int
id|depth_offset
suffix:semicolon
DECL|member|w
r_int
r_int
id|w
suffix:semicolon
DECL|member|h
r_int
r_int
id|h
suffix:semicolon
DECL|member|pitch
r_int
r_int
id|pitch
suffix:semicolon
DECL|member|pitch_bits
r_int
r_int
id|pitch_bits
suffix:semicolon
DECL|member|back_pitch
r_int
r_int
id|back_pitch
suffix:semicolon
DECL|member|depth_pitch
r_int
r_int
id|depth_pitch
suffix:semicolon
DECL|member|cpp
r_int
r_int
id|cpp
suffix:semicolon
DECL|member|chipset
r_int
r_int
id|chipset
suffix:semicolon
DECL|typedef|drm_i915_init_t
)brace
id|drm_i915_init_t
suffix:semicolon
DECL|struct|_drm_i915_sarea
r_typedef
r_struct
id|_drm_i915_sarea
(brace
DECL|member|texList
id|drm_tex_region_t
id|texList
(braket
id|I915_NR_TEX_REGIONS
op_plus
l_int|1
)braket
suffix:semicolon
DECL|member|last_upload
r_int
id|last_upload
suffix:semicolon
multiline_comment|/* last time texture was uploaded */
DECL|member|last_enqueue
r_int
id|last_enqueue
suffix:semicolon
multiline_comment|/* last time a buffer was enqueued */
DECL|member|last_dispatch
r_int
id|last_dispatch
suffix:semicolon
multiline_comment|/* age of the most recently dispatched buffer */
DECL|member|ctxOwner
r_int
id|ctxOwner
suffix:semicolon
multiline_comment|/* last context to upload state */
DECL|member|texAge
r_int
id|texAge
suffix:semicolon
DECL|member|pf_enabled
r_int
id|pf_enabled
suffix:semicolon
multiline_comment|/* is pageflipping allowed? */
DECL|member|pf_active
r_int
id|pf_active
suffix:semicolon
DECL|member|pf_current_page
r_int
id|pf_current_page
suffix:semicolon
multiline_comment|/* which buffer is being displayed? */
DECL|member|perf_boxes
r_int
id|perf_boxes
suffix:semicolon
multiline_comment|/* performance boxes to be displayed */
DECL|typedef|drm_i915_sarea_t
)brace
id|drm_i915_sarea_t
suffix:semicolon
multiline_comment|/* Flags for perf_boxes&n; */
DECL|macro|I915_BOX_RING_EMPTY
mdefine_line|#define I915_BOX_RING_EMPTY    0x1
DECL|macro|I915_BOX_FLIP
mdefine_line|#define I915_BOX_FLIP          0x2
DECL|macro|I915_BOX_WAIT
mdefine_line|#define I915_BOX_WAIT          0x4
DECL|macro|I915_BOX_TEXTURE_LOAD
mdefine_line|#define I915_BOX_TEXTURE_LOAD  0x8
DECL|macro|I915_BOX_LOST_CONTEXT
mdefine_line|#define I915_BOX_LOST_CONTEXT  0x10
multiline_comment|/* I915 specific ioctls&n; * The device specific ioctl range is 0x40 to 0x79.&n; */
DECL|macro|DRM_I915_INIT
mdefine_line|#define DRM_I915_INIT&t;&t;0x00
DECL|macro|DRM_I915_FLUSH
mdefine_line|#define DRM_I915_FLUSH&t;&t;0x01
DECL|macro|DRM_I915_FLIP
mdefine_line|#define DRM_I915_FLIP&t;&t;0x02
DECL|macro|DRM_I915_BATCHBUFFER
mdefine_line|#define DRM_I915_BATCHBUFFER&t;0x03
DECL|macro|DRM_I915_IRQ_EMIT
mdefine_line|#define DRM_I915_IRQ_EMIT&t;0x04
DECL|macro|DRM_I915_IRQ_WAIT
mdefine_line|#define DRM_I915_IRQ_WAIT&t;0x05
DECL|macro|DRM_I915_GETPARAM
mdefine_line|#define DRM_I915_GETPARAM&t;0x06
DECL|macro|DRM_I915_SETPARAM
mdefine_line|#define DRM_I915_SETPARAM&t;0x07
DECL|macro|DRM_I915_ALLOC
mdefine_line|#define DRM_I915_ALLOC&t;&t;0x08
DECL|macro|DRM_I915_FREE
mdefine_line|#define DRM_I915_FREE&t;&t;0x09
DECL|macro|DRM_I915_INIT_HEAP
mdefine_line|#define DRM_I915_INIT_HEAP&t;0x0a
DECL|macro|DRM_I915_CMDBUFFER
mdefine_line|#define DRM_I915_CMDBUFFER&t;0x0b
DECL|macro|DRM_IOCTL_I915_INIT
mdefine_line|#define DRM_IOCTL_I915_INIT&t;&t;DRM_IOW( DRM_COMMAND_BASE + DRM_I915_INIT, drm_i915_init_t)
DECL|macro|DRM_IOCTL_I915_FLUSH
mdefine_line|#define DRM_IOCTL_I915_FLUSH&t;&t;DRM_IO ( DRM_COMMAND_BASE + DRM_I915_FLUSH)
DECL|macro|DRM_IOCTL_I915_FLIP
mdefine_line|#define DRM_IOCTL_I915_FLIP&t;&t;DRM_IO ( DRM_COMMAND_BASE + DRM_I915_FLIP)
DECL|macro|DRM_IOCTL_I915_BATCHBUFFER
mdefine_line|#define DRM_IOCTL_I915_BATCHBUFFER&t;DRM_IOW( DRM_COMMAND_BASE + DRM_I915_BATCHBUFFER, drm_i915_batchbuffer_t)
DECL|macro|DRM_IOCTL_I915_IRQ_EMIT
mdefine_line|#define DRM_IOCTL_I915_IRQ_EMIT         DRM_IOWR(DRM_COMMAND_BASE + DRM_I915_IRQ_EMIT, drm_i915_irq_emit_t)
DECL|macro|DRM_IOCTL_I915_IRQ_WAIT
mdefine_line|#define DRM_IOCTL_I915_IRQ_WAIT         DRM_IOW( DRM_COMMAND_BASE + DRM_I915_IRQ_WAIT, drm_i915_irq_wait_t)
DECL|macro|DRM_IOCTL_I915_GETPARAM
mdefine_line|#define DRM_IOCTL_I915_GETPARAM         DRM_IOWR(DRM_COMMAND_BASE + DRM_I915_GETPARAM, drm_i915_getparam_t)
DECL|macro|DRM_IOCTL_I915_SETPARAM
mdefine_line|#define DRM_IOCTL_I915_SETPARAM         DRM_IOW( DRM_COMMAND_BASE + DRM_I915_SETPARAM, drm_i915_setparam_t)
DECL|macro|DRM_IOCTL_I915_ALLOC
mdefine_line|#define DRM_IOCTL_I915_ALLOC            DRM_IOWR(DRM_COMMAND_BASE + DRM_I915_ALLOC, drm_i915_mem_alloc_t)
DECL|macro|DRM_IOCTL_I915_FREE
mdefine_line|#define DRM_IOCTL_I915_FREE             DRM_IOW( DRM_COMMAND_BASE + DRM_I915_FREE, drm_i915_mem_free_t)
DECL|macro|DRM_IOCTL_I915_INIT_HEAP
mdefine_line|#define DRM_IOCTL_I915_INIT_HEAP        DRM_IOW( DRM_COMMAND_BASE + DRM_I915_INIT_HEAP, drm_i915_mem_init_heap_t)
DECL|macro|DRM_IOCTL_I915_CMDBUFFER
mdefine_line|#define DRM_IOCTL_I915_CMDBUFFER&t;DRM_IOW( DRM_COMMAND_BASE + DRM_I915_CMDBUFFER, drm_i915_cmdbuffer_t)
multiline_comment|/* Allow drivers to submit batchbuffers directly to hardware, relying&n; * on the security mechanisms provided by hardware.&n; */
DECL|struct|_drm_i915_batchbuffer
r_typedef
r_struct
id|_drm_i915_batchbuffer
(brace
DECL|member|start
r_int
id|start
suffix:semicolon
multiline_comment|/* agp offset */
DECL|member|used
r_int
id|used
suffix:semicolon
multiline_comment|/* nr bytes in use */
DECL|member|DR1
r_int
id|DR1
suffix:semicolon
multiline_comment|/* hw flags for GFX_OP_DRAWRECT_INFO */
DECL|member|DR4
r_int
id|DR4
suffix:semicolon
multiline_comment|/* window origin for GFX_OP_DRAWRECT_INFO */
DECL|member|num_cliprects
r_int
id|num_cliprects
suffix:semicolon
multiline_comment|/* mulitpass with multiple cliprects? */
DECL|member|cliprects
id|drm_clip_rect_t
id|__user
op_star
id|cliprects
suffix:semicolon
multiline_comment|/* pointer to userspace cliprects */
DECL|typedef|drm_i915_batchbuffer_t
)brace
id|drm_i915_batchbuffer_t
suffix:semicolon
multiline_comment|/* As above, but pass a pointer to userspace buffer which can be&n; * validated by the kernel prior to sending to hardware.&n; */
DECL|struct|_drm_i915_cmdbuffer
r_typedef
r_struct
id|_drm_i915_cmdbuffer
(brace
DECL|member|buf
r_char
id|__user
op_star
id|buf
suffix:semicolon
multiline_comment|/* pointer to userspace command buffer */
DECL|member|sz
r_int
id|sz
suffix:semicolon
multiline_comment|/* nr bytes in buf */
DECL|member|DR1
r_int
id|DR1
suffix:semicolon
multiline_comment|/* hw flags for GFX_OP_DRAWRECT_INFO */
DECL|member|DR4
r_int
id|DR4
suffix:semicolon
multiline_comment|/* window origin for GFX_OP_DRAWRECT_INFO */
DECL|member|num_cliprects
r_int
id|num_cliprects
suffix:semicolon
multiline_comment|/* mulitpass with multiple cliprects? */
DECL|member|cliprects
id|drm_clip_rect_t
id|__user
op_star
id|cliprects
suffix:semicolon
multiline_comment|/* pointer to userspace cliprects */
DECL|typedef|drm_i915_cmdbuffer_t
)brace
id|drm_i915_cmdbuffer_t
suffix:semicolon
multiline_comment|/* Userspace can request &amp; wait on irq&squot;s:&n; */
DECL|struct|drm_i915_irq_emit
r_typedef
r_struct
id|drm_i915_irq_emit
(brace
DECL|member|irq_seq
r_int
id|__user
op_star
id|irq_seq
suffix:semicolon
DECL|typedef|drm_i915_irq_emit_t
)brace
id|drm_i915_irq_emit_t
suffix:semicolon
DECL|struct|drm_i915_irq_wait
r_typedef
r_struct
id|drm_i915_irq_wait
(brace
DECL|member|irq_seq
r_int
id|irq_seq
suffix:semicolon
DECL|typedef|drm_i915_irq_wait_t
)brace
id|drm_i915_irq_wait_t
suffix:semicolon
multiline_comment|/* Ioctl to query kernel params:&n; */
DECL|macro|I915_PARAM_IRQ_ACTIVE
mdefine_line|#define I915_PARAM_IRQ_ACTIVE            1
DECL|macro|I915_PARAM_ALLOW_BATCHBUFFER
mdefine_line|#define I915_PARAM_ALLOW_BATCHBUFFER     2
DECL|struct|drm_i915_getparam
r_typedef
r_struct
id|drm_i915_getparam
(brace
DECL|member|param
r_int
id|param
suffix:semicolon
DECL|member|value
r_int
id|__user
op_star
id|value
suffix:semicolon
DECL|typedef|drm_i915_getparam_t
)brace
id|drm_i915_getparam_t
suffix:semicolon
multiline_comment|/* Ioctl to set kernel params:&n; */
DECL|macro|I915_SETPARAM_USE_MI_BATCHBUFFER_START
mdefine_line|#define I915_SETPARAM_USE_MI_BATCHBUFFER_START            1
DECL|macro|I915_SETPARAM_TEX_LRU_LOG_GRANULARITY
mdefine_line|#define I915_SETPARAM_TEX_LRU_LOG_GRANULARITY             2
DECL|macro|I915_SETPARAM_ALLOW_BATCHBUFFER
mdefine_line|#define I915_SETPARAM_ALLOW_BATCHBUFFER                   3
DECL|struct|drm_i915_setparam
r_typedef
r_struct
id|drm_i915_setparam
(brace
DECL|member|param
r_int
id|param
suffix:semicolon
DECL|member|value
r_int
id|value
suffix:semicolon
DECL|typedef|drm_i915_setparam_t
)brace
id|drm_i915_setparam_t
suffix:semicolon
multiline_comment|/* A memory manager for regions of shared memory:&n; */
DECL|macro|I915_MEM_REGION_AGP
mdefine_line|#define I915_MEM_REGION_AGP 1
DECL|struct|drm_i915_mem_alloc
r_typedef
r_struct
id|drm_i915_mem_alloc
(brace
DECL|member|region
r_int
id|region
suffix:semicolon
DECL|member|alignment
r_int
id|alignment
suffix:semicolon
DECL|member|size
r_int
id|size
suffix:semicolon
DECL|member|region_offset
r_int
id|__user
op_star
id|region_offset
suffix:semicolon
multiline_comment|/* offset from start of fb or agp */
DECL|typedef|drm_i915_mem_alloc_t
)brace
id|drm_i915_mem_alloc_t
suffix:semicolon
DECL|struct|drm_i915_mem_free
r_typedef
r_struct
id|drm_i915_mem_free
(brace
DECL|member|region
r_int
id|region
suffix:semicolon
DECL|member|region_offset
r_int
id|region_offset
suffix:semicolon
DECL|typedef|drm_i915_mem_free_t
)brace
id|drm_i915_mem_free_t
suffix:semicolon
DECL|struct|drm_i915_mem_init_heap
r_typedef
r_struct
id|drm_i915_mem_init_heap
(brace
DECL|member|region
r_int
id|region
suffix:semicolon
DECL|member|size
r_int
id|size
suffix:semicolon
DECL|member|start
r_int
id|start
suffix:semicolon
DECL|typedef|drm_i915_mem_init_heap_t
)brace
id|drm_i915_mem_init_heap_t
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* _I915_DRM_H_ */
eof
