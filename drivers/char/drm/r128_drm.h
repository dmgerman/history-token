multiline_comment|/* r128_drm.h -- Public header for the r128 driver -*- linux-c -*-&n; * Created: Wed Apr  5 19:24:19 2000 by kevin@precisioninsight.com&n; *&n; * Copyright 2000 Precision Insight, Inc., Cedar Park, Texas.&n; * Copyright 2000 VA Linux Systems, Inc., Sunnyvale, California.&n; * All rights reserved.&n; *&n; * Permission is hereby granted, free of charge, to any person obtaining a&n; * copy of this software and associated documentation files (the &quot;Software&quot;),&n; * to deal in the Software without restriction, including without limitation&n; * the rights to use, copy, modify, merge, publish, distribute, sublicense,&n; * and/or sell copies of the Software, and to permit persons to whom the&n; * Software is furnished to do so, subject to the following conditions:&n; *&n; * The above copyright notice and this permission notice (including the next&n; * paragraph) shall be included in all copies or substantial portions of the&n; * Software.&n; *&n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR&n; * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n; * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL&n; * PRECISION INSIGHT AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR&n; * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,&n; * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER&n; * DEALINGS IN THE SOFTWARE.&n; *&n; * Authors:&n; *    Gareth Hughes &lt;gareth@valinux.com&gt;&n; *    Kevin E. Martin &lt;martin@valinux.com&gt;&n; */
macro_line|#ifndef __R128_DRM_H__
DECL|macro|__R128_DRM_H__
mdefine_line|#define __R128_DRM_H__
multiline_comment|/* WARNING: If you change any of these defines, make sure to change the&n; * defines in the X server file (r128_sarea.h)&n; */
macro_line|#ifndef __R128_SAREA_DEFINES__
DECL|macro|__R128_SAREA_DEFINES__
mdefine_line|#define __R128_SAREA_DEFINES__
multiline_comment|/* What needs to be changed for the current vertex buffer?&n; */
DECL|macro|R128_UPLOAD_CONTEXT
mdefine_line|#define R128_UPLOAD_CONTEXT&t;&t;0x001
DECL|macro|R128_UPLOAD_SETUP
mdefine_line|#define R128_UPLOAD_SETUP&t;&t;0x002
DECL|macro|R128_UPLOAD_TEX0
mdefine_line|#define R128_UPLOAD_TEX0&t;&t;0x004
DECL|macro|R128_UPLOAD_TEX1
mdefine_line|#define R128_UPLOAD_TEX1&t;&t;0x008
DECL|macro|R128_UPLOAD_TEX0IMAGES
mdefine_line|#define R128_UPLOAD_TEX0IMAGES&t;&t;0x010
DECL|macro|R128_UPLOAD_TEX1IMAGES
mdefine_line|#define R128_UPLOAD_TEX1IMAGES&t;&t;0x020
DECL|macro|R128_UPLOAD_CORE
mdefine_line|#define R128_UPLOAD_CORE&t;&t;0x040
DECL|macro|R128_UPLOAD_MASKS
mdefine_line|#define R128_UPLOAD_MASKS&t;&t;0x080
DECL|macro|R128_UPLOAD_WINDOW
mdefine_line|#define R128_UPLOAD_WINDOW&t;&t;0x100
DECL|macro|R128_UPLOAD_CLIPRECTS
mdefine_line|#define R128_UPLOAD_CLIPRECTS&t;&t;0x200&t;/* handled client-side */
DECL|macro|R128_REQUIRE_QUIESCENCE
mdefine_line|#define R128_REQUIRE_QUIESCENCE&t;&t;0x400
DECL|macro|R128_UPLOAD_ALL
mdefine_line|#define R128_UPLOAD_ALL&t;&t;&t;0x7ff
DECL|macro|R128_FRONT
mdefine_line|#define R128_FRONT&t;&t;&t;0x1
DECL|macro|R128_BACK
mdefine_line|#define R128_BACK&t;&t;&t;0x2
DECL|macro|R128_DEPTH
mdefine_line|#define R128_DEPTH&t;&t;&t;0x4
multiline_comment|/* Primitive types&n; */
DECL|macro|R128_POINTS
mdefine_line|#define R128_POINTS&t;&t;&t;0x1
DECL|macro|R128_LINES
mdefine_line|#define R128_LINES&t;&t;&t;0x2
DECL|macro|R128_LINE_STRIP
mdefine_line|#define R128_LINE_STRIP&t;&t;&t;0x3
DECL|macro|R128_TRIANGLES
mdefine_line|#define R128_TRIANGLES&t;&t;&t;0x4
DECL|macro|R128_TRIANGLE_FAN
mdefine_line|#define R128_TRIANGLE_FAN&t;&t;0x5
DECL|macro|R128_TRIANGLE_STRIP
mdefine_line|#define R128_TRIANGLE_STRIP&t;&t;0x6
multiline_comment|/* Vertex/indirect buffer size&n; */
DECL|macro|R128_BUFFER_SIZE
mdefine_line|#define R128_BUFFER_SIZE&t;&t;16384
multiline_comment|/* Byte offsets for indirect buffer data&n; */
DECL|macro|R128_INDEX_PRIM_OFFSET
mdefine_line|#define R128_INDEX_PRIM_OFFSET&t;&t;20
DECL|macro|R128_HOSTDATA_BLIT_OFFSET
mdefine_line|#define R128_HOSTDATA_BLIT_OFFSET&t;32
multiline_comment|/* Keep these small for testing.&n; */
DECL|macro|R128_NR_SAREA_CLIPRECTS
mdefine_line|#define R128_NR_SAREA_CLIPRECTS&t;&t;12
multiline_comment|/* There are 2 heaps (local/AGP).  Each region within a heap is a&n; *  minimum of 64k, and there are at most 64 of them per heap.&n; */
DECL|macro|R128_LOCAL_TEX_HEAP
mdefine_line|#define R128_LOCAL_TEX_HEAP&t;&t;0
DECL|macro|R128_AGP_TEX_HEAP
mdefine_line|#define R128_AGP_TEX_HEAP&t;&t;1
DECL|macro|R128_NR_TEX_HEAPS
mdefine_line|#define R128_NR_TEX_HEAPS&t;&t;2
DECL|macro|R128_NR_TEX_REGIONS
mdefine_line|#define R128_NR_TEX_REGIONS&t;&t;64
DECL|macro|R128_LOG_TEX_GRANULARITY
mdefine_line|#define R128_LOG_TEX_GRANULARITY&t;16
DECL|macro|R128_NR_CONTEXT_REGS
mdefine_line|#define R128_NR_CONTEXT_REGS&t;&t;12
DECL|macro|R128_MAX_TEXTURE_LEVELS
mdefine_line|#define R128_MAX_TEXTURE_LEVELS&t;&t;11
DECL|macro|R128_MAX_TEXTURE_UNITS
mdefine_line|#define R128_MAX_TEXTURE_UNITS&t;&t;2
macro_line|#endif /* __R128_SAREA_DEFINES__ */
r_typedef
r_struct
(brace
multiline_comment|/* Context state - can be written in one large chunk */
DECL|member|dst_pitch_offset_c
r_int
r_int
id|dst_pitch_offset_c
suffix:semicolon
DECL|member|dp_gui_master_cntl_c
r_int
r_int
id|dp_gui_master_cntl_c
suffix:semicolon
DECL|member|sc_top_left_c
r_int
r_int
id|sc_top_left_c
suffix:semicolon
DECL|member|sc_bottom_right_c
r_int
r_int
id|sc_bottom_right_c
suffix:semicolon
DECL|member|z_offset_c
r_int
r_int
id|z_offset_c
suffix:semicolon
DECL|member|z_pitch_c
r_int
r_int
id|z_pitch_c
suffix:semicolon
DECL|member|z_sten_cntl_c
r_int
r_int
id|z_sten_cntl_c
suffix:semicolon
DECL|member|tex_cntl_c
r_int
r_int
id|tex_cntl_c
suffix:semicolon
DECL|member|misc_3d_state_cntl_reg
r_int
r_int
id|misc_3d_state_cntl_reg
suffix:semicolon
DECL|member|texture_clr_cmp_clr_c
r_int
r_int
id|texture_clr_cmp_clr_c
suffix:semicolon
DECL|member|texture_clr_cmp_msk_c
r_int
r_int
id|texture_clr_cmp_msk_c
suffix:semicolon
DECL|member|fog_color_c
r_int
r_int
id|fog_color_c
suffix:semicolon
multiline_comment|/* Texture state */
DECL|member|tex_size_pitch_c
r_int
r_int
id|tex_size_pitch_c
suffix:semicolon
DECL|member|constant_color_c
r_int
r_int
id|constant_color_c
suffix:semicolon
multiline_comment|/* Setup state */
DECL|member|pm4_vc_fpu_setup
r_int
r_int
id|pm4_vc_fpu_setup
suffix:semicolon
DECL|member|setup_cntl
r_int
r_int
id|setup_cntl
suffix:semicolon
multiline_comment|/* Mask state */
DECL|member|dp_write_mask
r_int
r_int
id|dp_write_mask
suffix:semicolon
DECL|member|sten_ref_mask_c
r_int
r_int
id|sten_ref_mask_c
suffix:semicolon
DECL|member|plane_3d_mask_c
r_int
r_int
id|plane_3d_mask_c
suffix:semicolon
multiline_comment|/* Window state */
DECL|member|window_xy_offset
r_int
r_int
id|window_xy_offset
suffix:semicolon
multiline_comment|/* Core state */
DECL|member|scale_3d_cntl
r_int
r_int
id|scale_3d_cntl
suffix:semicolon
DECL|typedef|drm_r128_context_regs_t
)brace
id|drm_r128_context_regs_t
suffix:semicolon
multiline_comment|/* Setup registers for each texture unit&n; */
r_typedef
r_struct
(brace
DECL|member|tex_cntl
r_int
r_int
id|tex_cntl
suffix:semicolon
DECL|member|tex_combine_cntl
r_int
r_int
id|tex_combine_cntl
suffix:semicolon
DECL|member|tex_size_pitch
r_int
r_int
id|tex_size_pitch
suffix:semicolon
DECL|member|tex_offset
r_int
r_int
id|tex_offset
(braket
id|R128_MAX_TEXTURE_LEVELS
)braket
suffix:semicolon
DECL|member|tex_border_color
r_int
r_int
id|tex_border_color
suffix:semicolon
DECL|typedef|drm_r128_texture_regs_t
)brace
id|drm_r128_texture_regs_t
suffix:semicolon
DECL|struct|drm_r128_sarea
r_typedef
r_struct
id|drm_r128_sarea
(brace
multiline_comment|/* The channel for communication of state information to the kernel&n;&t; * on firing a vertex buffer.&n;&t; */
DECL|member|context_state
id|drm_r128_context_regs_t
id|context_state
suffix:semicolon
DECL|member|tex_state
id|drm_r128_texture_regs_t
id|tex_state
(braket
id|R128_MAX_TEXTURE_UNITS
)braket
suffix:semicolon
DECL|member|dirty
r_int
r_int
id|dirty
suffix:semicolon
DECL|member|vertsize
r_int
r_int
id|vertsize
suffix:semicolon
DECL|member|vc_format
r_int
r_int
id|vc_format
suffix:semicolon
multiline_comment|/* The current cliprects, or a subset thereof.&n;&t; */
DECL|member|boxes
id|drm_clip_rect_t
id|boxes
(braket
id|R128_NR_SAREA_CLIPRECTS
)braket
suffix:semicolon
DECL|member|nbox
r_int
r_int
id|nbox
suffix:semicolon
multiline_comment|/* Counters for client-side throttling of rendering clients.&n;&t; */
DECL|member|last_frame
r_int
r_int
id|last_frame
suffix:semicolon
DECL|member|last_dispatch
r_int
r_int
id|last_dispatch
suffix:semicolon
DECL|member|tex_list
id|drm_tex_region_t
id|tex_list
(braket
id|R128_NR_TEX_HEAPS
)braket
(braket
id|R128_NR_TEX_REGIONS
op_plus
l_int|1
)braket
suffix:semicolon
DECL|member|tex_age
r_int
id|tex_age
(braket
id|R128_NR_TEX_HEAPS
)braket
suffix:semicolon
DECL|member|ctx_owner
r_int
id|ctx_owner
suffix:semicolon
DECL|typedef|drm_r128_sarea_t
)brace
id|drm_r128_sarea_t
suffix:semicolon
multiline_comment|/* WARNING: If you change any of these defines, make sure to change the&n; * defines in the Xserver file (xf86drmR128.h)&n; */
multiline_comment|/* Rage 128 specific ioctls&n; * The device specific ioctl range is 0x40 to 0x79.&n; */
DECL|macro|DRM_IOCTL_R128_INIT
mdefine_line|#define DRM_IOCTL_R128_INIT&t;&t;DRM_IOW( 0x40, drm_r128_init_t)
DECL|macro|DRM_IOCTL_R128_CCE_START
mdefine_line|#define DRM_IOCTL_R128_CCE_START&t;DRM_IO(  0x41)
DECL|macro|DRM_IOCTL_R128_CCE_STOP
mdefine_line|#define DRM_IOCTL_R128_CCE_STOP&t;&t;DRM_IOW( 0x42, drm_r128_cce_stop_t)
DECL|macro|DRM_IOCTL_R128_CCE_RESET
mdefine_line|#define DRM_IOCTL_R128_CCE_RESET&t;DRM_IO(  0x43)
DECL|macro|DRM_IOCTL_R128_CCE_IDLE
mdefine_line|#define DRM_IOCTL_R128_CCE_IDLE&t;&t;DRM_IO(  0x44)
DECL|macro|DRM_IOCTL_R128_RESET
mdefine_line|#define DRM_IOCTL_R128_RESET&t;&t;DRM_IO(  0x46)
DECL|macro|DRM_IOCTL_R128_SWAP
mdefine_line|#define DRM_IOCTL_R128_SWAP&t;&t;DRM_IO(  0x47)
DECL|macro|DRM_IOCTL_R128_CLEAR
mdefine_line|#define DRM_IOCTL_R128_CLEAR&t;&t;DRM_IOW( 0x48, drm_r128_clear_t)
DECL|macro|DRM_IOCTL_R128_VERTEX
mdefine_line|#define DRM_IOCTL_R128_VERTEX&t;&t;DRM_IOW( 0x49, drm_r128_vertex_t)
DECL|macro|DRM_IOCTL_R128_INDICES
mdefine_line|#define DRM_IOCTL_R128_INDICES&t;&t;DRM_IOW( 0x4a, drm_r128_indices_t)
DECL|macro|DRM_IOCTL_R128_BLIT
mdefine_line|#define DRM_IOCTL_R128_BLIT&t;&t;DRM_IOW( 0x4b, drm_r128_blit_t)
DECL|macro|DRM_IOCTL_R128_DEPTH
mdefine_line|#define DRM_IOCTL_R128_DEPTH&t;&t;DRM_IOW( 0x4c, drm_r128_depth_t)
DECL|macro|DRM_IOCTL_R128_STIPPLE
mdefine_line|#define DRM_IOCTL_R128_STIPPLE&t;&t;DRM_IOW( 0x4d, drm_r128_stipple_t)
DECL|macro|DRM_IOCTL_R128_INDIRECT
mdefine_line|#define DRM_IOCTL_R128_INDIRECT&t;&t;DRM_IOWR(0x4f, drm_r128_indirect_t)
DECL|macro|DRM_IOCTL_R128_FULLSCREEN
mdefine_line|#define DRM_IOCTL_R128_FULLSCREEN&t;DRM_IOW( 0x50, drm_r128_fullscreen_t)
DECL|macro|DRM_IOCTL_R128_CLEAR2
mdefine_line|#define DRM_IOCTL_R128_CLEAR2&t;&t;DRM_IOW( 0x51, drm_r128_clear2_t)
DECL|struct|drm_r128_init
r_typedef
r_struct
id|drm_r128_init
(brace
r_enum
(brace
DECL|enumerator|R128_INIT_CCE
id|R128_INIT_CCE
op_assign
l_int|0x01
comma
DECL|enumerator|R128_CLEANUP_CCE
id|R128_CLEANUP_CCE
op_assign
l_int|0x02
DECL|member|func
)brace
id|func
suffix:semicolon
macro_line|#if CONFIG_XFREE86_VERSION &lt; XFREE86_VERSION(4,1,0,0)
DECL|member|sarea_priv_offset
r_int
id|sarea_priv_offset
suffix:semicolon
macro_line|#else
DECL|member|sarea_priv_offset
r_int
r_int
id|sarea_priv_offset
suffix:semicolon
macro_line|#endif
DECL|member|is_pci
r_int
id|is_pci
suffix:semicolon
DECL|member|cce_mode
r_int
id|cce_mode
suffix:semicolon
DECL|member|cce_secure
r_int
id|cce_secure
suffix:semicolon
DECL|member|ring_size
r_int
id|ring_size
suffix:semicolon
DECL|member|usec_timeout
r_int
id|usec_timeout
suffix:semicolon
DECL|member|fb_bpp
r_int
r_int
id|fb_bpp
suffix:semicolon
DECL|member|front_offset
DECL|member|front_pitch
r_int
r_int
id|front_offset
comma
id|front_pitch
suffix:semicolon
DECL|member|back_offset
DECL|member|back_pitch
r_int
r_int
id|back_offset
comma
id|back_pitch
suffix:semicolon
DECL|member|depth_bpp
r_int
r_int
id|depth_bpp
suffix:semicolon
DECL|member|depth_offset
DECL|member|depth_pitch
r_int
r_int
id|depth_offset
comma
id|depth_pitch
suffix:semicolon
DECL|member|span_offset
r_int
r_int
id|span_offset
suffix:semicolon
macro_line|#if CONFIG_XFREE86_VERSION &lt; XFREE86_VERSION(4,1,0,0)
DECL|member|fb_offset
r_int
r_int
id|fb_offset
suffix:semicolon
DECL|member|mmio_offset
r_int
r_int
id|mmio_offset
suffix:semicolon
DECL|member|ring_offset
r_int
r_int
id|ring_offset
suffix:semicolon
DECL|member|ring_rptr_offset
r_int
r_int
id|ring_rptr_offset
suffix:semicolon
DECL|member|buffers_offset
r_int
r_int
id|buffers_offset
suffix:semicolon
DECL|member|agp_textures_offset
r_int
r_int
id|agp_textures_offset
suffix:semicolon
macro_line|#else
DECL|member|fb_offset
r_int
r_int
id|fb_offset
suffix:semicolon
DECL|member|mmio_offset
r_int
r_int
id|mmio_offset
suffix:semicolon
DECL|member|ring_offset
r_int
r_int
id|ring_offset
suffix:semicolon
DECL|member|ring_rptr_offset
r_int
r_int
id|ring_rptr_offset
suffix:semicolon
DECL|member|buffers_offset
r_int
r_int
id|buffers_offset
suffix:semicolon
DECL|member|agp_textures_offset
r_int
r_int
id|agp_textures_offset
suffix:semicolon
macro_line|#endif
DECL|typedef|drm_r128_init_t
)brace
id|drm_r128_init_t
suffix:semicolon
DECL|struct|drm_r128_cce_stop
r_typedef
r_struct
id|drm_r128_cce_stop
(brace
DECL|member|flush
r_int
id|flush
suffix:semicolon
DECL|member|idle
r_int
id|idle
suffix:semicolon
DECL|typedef|drm_r128_cce_stop_t
)brace
id|drm_r128_cce_stop_t
suffix:semicolon
DECL|struct|drm_r128_clear
r_typedef
r_struct
id|drm_r128_clear
(brace
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
macro_line|#if CONFIG_XFREE86_VERSION &lt; XFREE86_VERSION(4,1,0,0)
DECL|member|x
DECL|member|y
DECL|member|w
DECL|member|h
r_int
id|x
comma
id|y
comma
id|w
comma
id|h
suffix:semicolon
macro_line|#endif
DECL|member|clear_color
r_int
r_int
id|clear_color
suffix:semicolon
DECL|member|clear_depth
r_int
r_int
id|clear_depth
suffix:semicolon
macro_line|#if CONFIG_XFREE86_VERSION &gt;= XFREE86_VERSION(4,1,0,0)
DECL|member|color_mask
r_int
r_int
id|color_mask
suffix:semicolon
DECL|member|depth_mask
r_int
r_int
id|depth_mask
suffix:semicolon
macro_line|#endif
DECL|typedef|drm_r128_clear_t
)brace
id|drm_r128_clear_t
suffix:semicolon
DECL|struct|drm_r128_vertex
r_typedef
r_struct
id|drm_r128_vertex
(brace
DECL|member|prim
r_int
id|prim
suffix:semicolon
DECL|member|idx
r_int
id|idx
suffix:semicolon
multiline_comment|/* Index of vertex buffer */
DECL|member|count
r_int
id|count
suffix:semicolon
multiline_comment|/* Number of vertices in buffer */
DECL|member|discard
r_int
id|discard
suffix:semicolon
multiline_comment|/* Client finished with buffer? */
DECL|typedef|drm_r128_vertex_t
)brace
id|drm_r128_vertex_t
suffix:semicolon
DECL|struct|drm_r128_indices
r_typedef
r_struct
id|drm_r128_indices
(brace
DECL|member|prim
r_int
id|prim
suffix:semicolon
DECL|member|idx
r_int
id|idx
suffix:semicolon
DECL|member|start
r_int
id|start
suffix:semicolon
DECL|member|end
r_int
id|end
suffix:semicolon
DECL|member|discard
r_int
id|discard
suffix:semicolon
multiline_comment|/* Client finished with buffer? */
DECL|typedef|drm_r128_indices_t
)brace
id|drm_r128_indices_t
suffix:semicolon
DECL|struct|drm_r128_blit
r_typedef
r_struct
id|drm_r128_blit
(brace
DECL|member|idx
r_int
id|idx
suffix:semicolon
DECL|member|pitch
r_int
id|pitch
suffix:semicolon
DECL|member|offset
r_int
id|offset
suffix:semicolon
DECL|member|format
r_int
id|format
suffix:semicolon
DECL|member|x
DECL|member|y
r_int
r_int
id|x
comma
id|y
suffix:semicolon
DECL|member|width
DECL|member|height
r_int
r_int
id|width
comma
id|height
suffix:semicolon
DECL|typedef|drm_r128_blit_t
)brace
id|drm_r128_blit_t
suffix:semicolon
DECL|struct|drm_r128_depth
r_typedef
r_struct
id|drm_r128_depth
(brace
r_enum
(brace
DECL|enumerator|R128_WRITE_SPAN
id|R128_WRITE_SPAN
op_assign
l_int|0x01
comma
DECL|enumerator|R128_WRITE_PIXELS
id|R128_WRITE_PIXELS
op_assign
l_int|0x02
comma
DECL|enumerator|R128_READ_SPAN
id|R128_READ_SPAN
op_assign
l_int|0x03
comma
DECL|enumerator|R128_READ_PIXELS
id|R128_READ_PIXELS
op_assign
l_int|0x04
DECL|member|func
)brace
id|func
suffix:semicolon
DECL|member|n
r_int
id|n
suffix:semicolon
DECL|member|x
r_int
op_star
id|x
suffix:semicolon
DECL|member|y
r_int
op_star
id|y
suffix:semicolon
DECL|member|buffer
r_int
r_int
op_star
id|buffer
suffix:semicolon
DECL|member|mask
r_int
r_char
op_star
id|mask
suffix:semicolon
DECL|typedef|drm_r128_depth_t
)brace
id|drm_r128_depth_t
suffix:semicolon
DECL|struct|drm_r128_stipple
r_typedef
r_struct
id|drm_r128_stipple
(brace
DECL|member|mask
r_int
r_int
op_star
id|mask
suffix:semicolon
DECL|typedef|drm_r128_stipple_t
)brace
id|drm_r128_stipple_t
suffix:semicolon
DECL|struct|drm_r128_indirect
r_typedef
r_struct
id|drm_r128_indirect
(brace
DECL|member|idx
r_int
id|idx
suffix:semicolon
DECL|member|start
r_int
id|start
suffix:semicolon
DECL|member|end
r_int
id|end
suffix:semicolon
DECL|member|discard
r_int
id|discard
suffix:semicolon
DECL|typedef|drm_r128_indirect_t
)brace
id|drm_r128_indirect_t
suffix:semicolon
DECL|struct|drm_r128_fullscreen
r_typedef
r_struct
id|drm_r128_fullscreen
(brace
r_enum
(brace
DECL|enumerator|R128_INIT_FULLSCREEN
id|R128_INIT_FULLSCREEN
op_assign
l_int|0x01
comma
DECL|enumerator|R128_CLEANUP_FULLSCREEN
id|R128_CLEANUP_FULLSCREEN
op_assign
l_int|0x02
DECL|member|func
)brace
id|func
suffix:semicolon
DECL|typedef|drm_r128_fullscreen_t
)brace
id|drm_r128_fullscreen_t
suffix:semicolon
macro_line|#endif
eof
