multiline_comment|/* mga_drm.h -- Public header for the Matrox g200/g400 driver -*- linux-c -*-&n; * Created: Tue Jan 25 01:50:01 1999 by jhartmann@precisioninsight.com&n; *&n; * Copyright 1999 Precision Insight, Inc., Cedar Park, Texas.&n; * Copyright 2000 VA Linux Systems, Inc., Sunnyvale, California.&n; * All rights reserved.&n; *&n; * Permission is hereby granted, free of charge, to any person obtaining a&n; * copy of this software and associated documentation files (the &quot;Software&quot;),&n; * to deal in the Software without restriction, including without limitation&n; * the rights to use, copy, modify, merge, publish, distribute, sublicense,&n; * and/or sell copies of the Software, and to permit persons to whom the&n; * Software is furnished to do so, subject to the following conditions:&n; *&n; * The above copyright notice and this permission notice (including the next&n; * paragraph) shall be included in all copies or substantial portions of the&n; * Software.&n; *&n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR&n; * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n; * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL&n; * VA LINUX SYSTEMS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR&n; * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,&n; * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR&n; * OTHER DEALINGS IN THE SOFTWARE.&n; *&n; * Authors:&n; *    Jeff Hartmann &lt;jhartmann@valinux.com&gt;&n; *    Keith Whitwell &lt;keithw@valinux.com&gt;&n; *&n; * Rewritten by:&n; *    Gareth Hughes &lt;gareth@valinux.com&gt;&n; */
macro_line|#ifndef __MGA_DRM_H__
DECL|macro|__MGA_DRM_H__
mdefine_line|#define __MGA_DRM_H__
multiline_comment|/* WARNING: If you change any of these defines, make sure to change the&n; * defines in the Xserver file (mga_sarea.h)&n; */
macro_line|#ifndef __MGA_SAREA_DEFINES__
DECL|macro|__MGA_SAREA_DEFINES__
mdefine_line|#define __MGA_SAREA_DEFINES__
multiline_comment|/* WARP pipe flags&n; */
DECL|macro|MGA_F
mdefine_line|#define MGA_F&t;&t;&t;0x1&t;&t;/* fog */
DECL|macro|MGA_A
mdefine_line|#define MGA_A&t;&t;&t;0x2&t;&t;/* alpha */
DECL|macro|MGA_S
mdefine_line|#define MGA_S&t;&t;&t;0x4&t;&t;/* specular */
DECL|macro|MGA_T2
mdefine_line|#define MGA_T2&t;&t;&t;0x8&t;&t;/* multitexture */
DECL|macro|MGA_WARP_TGZ
mdefine_line|#define MGA_WARP_TGZ&t;&t;0
DECL|macro|MGA_WARP_TGZF
mdefine_line|#define MGA_WARP_TGZF&t;&t;(MGA_F)
DECL|macro|MGA_WARP_TGZA
mdefine_line|#define MGA_WARP_TGZA&t;&t;(MGA_A)
DECL|macro|MGA_WARP_TGZAF
mdefine_line|#define MGA_WARP_TGZAF&t;&t;(MGA_F|MGA_A)
DECL|macro|MGA_WARP_TGZS
mdefine_line|#define MGA_WARP_TGZS&t;&t;(MGA_S)
DECL|macro|MGA_WARP_TGZSF
mdefine_line|#define MGA_WARP_TGZSF&t;&t;(MGA_S|MGA_F)
DECL|macro|MGA_WARP_TGZSA
mdefine_line|#define MGA_WARP_TGZSA&t;&t;(MGA_S|MGA_A)
DECL|macro|MGA_WARP_TGZSAF
mdefine_line|#define MGA_WARP_TGZSAF&t;&t;(MGA_S|MGA_F|MGA_A)
DECL|macro|MGA_WARP_T2GZ
mdefine_line|#define MGA_WARP_T2GZ&t;&t;(MGA_T2)
DECL|macro|MGA_WARP_T2GZF
mdefine_line|#define MGA_WARP_T2GZF&t;&t;(MGA_T2|MGA_F)
DECL|macro|MGA_WARP_T2GZA
mdefine_line|#define MGA_WARP_T2GZA&t;&t;(MGA_T2|MGA_A)
DECL|macro|MGA_WARP_T2GZAF
mdefine_line|#define MGA_WARP_T2GZAF&t;&t;(MGA_T2|MGA_A|MGA_F)
DECL|macro|MGA_WARP_T2GZS
mdefine_line|#define MGA_WARP_T2GZS&t;&t;(MGA_T2|MGA_S)
DECL|macro|MGA_WARP_T2GZSF
mdefine_line|#define MGA_WARP_T2GZSF&t;&t;(MGA_T2|MGA_S|MGA_F)
DECL|macro|MGA_WARP_T2GZSA
mdefine_line|#define MGA_WARP_T2GZSA&t;&t;(MGA_T2|MGA_S|MGA_A)
DECL|macro|MGA_WARP_T2GZSAF
mdefine_line|#define MGA_WARP_T2GZSAF&t;(MGA_T2|MGA_S|MGA_F|MGA_A)
DECL|macro|MGA_MAX_G200_PIPES
mdefine_line|#define MGA_MAX_G200_PIPES&t;8&t;&t;/* no multitex */
DECL|macro|MGA_MAX_G400_PIPES
mdefine_line|#define MGA_MAX_G400_PIPES&t;16
DECL|macro|MGA_MAX_WARP_PIPES
mdefine_line|#define MGA_MAX_WARP_PIPES&t;MGA_MAX_G400_PIPES
DECL|macro|MGA_WARP_UCODE_SIZE
mdefine_line|#define MGA_WARP_UCODE_SIZE&t;32768&t;&t;/* in bytes */
DECL|macro|MGA_CARD_TYPE_G200
mdefine_line|#define MGA_CARD_TYPE_G200&t;1
DECL|macro|MGA_CARD_TYPE_G400
mdefine_line|#define MGA_CARD_TYPE_G400&t;2
DECL|macro|MGA_FRONT
mdefine_line|#define MGA_FRONT&t;&t;0x1
DECL|macro|MGA_BACK
mdefine_line|#define MGA_BACK&t;&t;0x2
DECL|macro|MGA_DEPTH
mdefine_line|#define MGA_DEPTH&t;&t;0x4
multiline_comment|/* What needs to be changed for the current vertex dma buffer?&n; */
DECL|macro|MGA_UPLOAD_CONTEXT
mdefine_line|#define MGA_UPLOAD_CONTEXT&t;0x1
DECL|macro|MGA_UPLOAD_TEX0
mdefine_line|#define MGA_UPLOAD_TEX0&t;&t;0x2
DECL|macro|MGA_UPLOAD_TEX1
mdefine_line|#define MGA_UPLOAD_TEX1&t;&t;0x4
DECL|macro|MGA_UPLOAD_PIPE
mdefine_line|#define MGA_UPLOAD_PIPE&t;&t;0x8
DECL|macro|MGA_UPLOAD_TEX0IMAGE
mdefine_line|#define MGA_UPLOAD_TEX0IMAGE&t;0x10 /* handled client-side */
DECL|macro|MGA_UPLOAD_TEX1IMAGE
mdefine_line|#define MGA_UPLOAD_TEX1IMAGE&t;0x20 /* handled client-side */
DECL|macro|MGA_UPLOAD_2D
mdefine_line|#define MGA_UPLOAD_2D&t;&t;0x40
DECL|macro|MGA_WAIT_AGE
mdefine_line|#define MGA_WAIT_AGE&t;&t;0x80 /* handled client-side */
DECL|macro|MGA_UPLOAD_CLIPRECTS
mdefine_line|#define MGA_UPLOAD_CLIPRECTS&t;0x100 /* handled client-side */
macro_line|#if 0
mdefine_line|#define MGA_DMA_FLUSH&t;&t;0x200 /* set when someone gets the lock&n;&t;&t;&t;&t;&t; quiescent */
macro_line|#endif
multiline_comment|/* 32 buffers of 64k each, total 2 meg.&n; */
DECL|macro|MGA_BUFFER_SIZE
mdefine_line|#define MGA_BUFFER_SIZE&t;&t;(1 &lt;&lt; 16)
DECL|macro|MGA_NUM_BUFFERS
mdefine_line|#define MGA_NUM_BUFFERS&t;&t;128
multiline_comment|/* Keep these small for testing.&n; */
DECL|macro|MGA_NR_SAREA_CLIPRECTS
mdefine_line|#define MGA_NR_SAREA_CLIPRECTS&t;8
multiline_comment|/* 2 heaps (1 for card, 1 for agp), each divided into upto 128&n; * regions, subject to a minimum region size of (1&lt;&lt;16) == 64k.&n; *&n; * Clients may subdivide regions internally, but when sharing between&n; * clients, the region size is the minimum granularity.&n; */
DECL|macro|MGA_CARD_HEAP
mdefine_line|#define MGA_CARD_HEAP&t;&t;&t;0
DECL|macro|MGA_AGP_HEAP
mdefine_line|#define MGA_AGP_HEAP&t;&t;&t;1
DECL|macro|MGA_NR_TEX_HEAPS
mdefine_line|#define MGA_NR_TEX_HEAPS&t;&t;2
DECL|macro|MGA_NR_TEX_REGIONS
mdefine_line|#define MGA_NR_TEX_REGIONS&t;&t;16
DECL|macro|MGA_LOG_MIN_TEX_REGION_SIZE
mdefine_line|#define MGA_LOG_MIN_TEX_REGION_SIZE&t;16
macro_line|#endif /* __MGA_SAREA_DEFINES__ */
multiline_comment|/* Setup registers for 3D context&n; */
r_typedef
r_struct
(brace
DECL|member|dstorg
r_int
r_int
id|dstorg
suffix:semicolon
DECL|member|maccess
r_int
r_int
id|maccess
suffix:semicolon
DECL|member|plnwt
r_int
r_int
id|plnwt
suffix:semicolon
DECL|member|dwgctl
r_int
r_int
id|dwgctl
suffix:semicolon
DECL|member|alphactrl
r_int
r_int
id|alphactrl
suffix:semicolon
DECL|member|fogcolor
r_int
r_int
id|fogcolor
suffix:semicolon
DECL|member|wflag
r_int
r_int
id|wflag
suffix:semicolon
DECL|member|tdualstage0
r_int
r_int
id|tdualstage0
suffix:semicolon
DECL|member|tdualstage1
r_int
r_int
id|tdualstage1
suffix:semicolon
DECL|member|fcol
r_int
r_int
id|fcol
suffix:semicolon
DECL|member|stencil
r_int
r_int
id|stencil
suffix:semicolon
DECL|member|stencilctl
r_int
r_int
id|stencilctl
suffix:semicolon
DECL|typedef|drm_mga_context_regs_t
)brace
id|drm_mga_context_regs_t
suffix:semicolon
multiline_comment|/* Setup registers for 2D, X server&n; */
r_typedef
r_struct
(brace
DECL|member|pitch
r_int
r_int
id|pitch
suffix:semicolon
DECL|typedef|drm_mga_server_regs_t
)brace
id|drm_mga_server_regs_t
suffix:semicolon
multiline_comment|/* Setup registers for each texture unit&n; */
r_typedef
r_struct
(brace
DECL|member|texctl
r_int
r_int
id|texctl
suffix:semicolon
DECL|member|texctl2
r_int
r_int
id|texctl2
suffix:semicolon
DECL|member|texfilter
r_int
r_int
id|texfilter
suffix:semicolon
DECL|member|texbordercol
r_int
r_int
id|texbordercol
suffix:semicolon
DECL|member|texorg
r_int
r_int
id|texorg
suffix:semicolon
DECL|member|texwidth
r_int
r_int
id|texwidth
suffix:semicolon
DECL|member|texheight
r_int
r_int
id|texheight
suffix:semicolon
DECL|member|texorg1
r_int
r_int
id|texorg1
suffix:semicolon
DECL|member|texorg2
r_int
r_int
id|texorg2
suffix:semicolon
DECL|member|texorg3
r_int
r_int
id|texorg3
suffix:semicolon
DECL|member|texorg4
r_int
r_int
id|texorg4
suffix:semicolon
DECL|typedef|drm_mga_texture_regs_t
)brace
id|drm_mga_texture_regs_t
suffix:semicolon
multiline_comment|/* General aging mechanism&n; */
r_typedef
r_struct
(brace
DECL|member|head
r_int
r_int
id|head
suffix:semicolon
multiline_comment|/* Position of head pointer          */
DECL|member|wrap
r_int
r_int
id|wrap
suffix:semicolon
multiline_comment|/* Primary DMA wrap count            */
DECL|typedef|drm_mga_age_t
)brace
id|drm_mga_age_t
suffix:semicolon
DECL|struct|_drm_mga_sarea
r_typedef
r_struct
id|_drm_mga_sarea
(brace
multiline_comment|/* The channel for communication of state information to the kernel&n;&t; * on firing a vertex dma buffer.&n;&t; */
DECL|member|context_state
id|drm_mga_context_regs_t
id|context_state
suffix:semicolon
DECL|member|server_state
id|drm_mga_server_regs_t
id|server_state
suffix:semicolon
DECL|member|tex_state
id|drm_mga_texture_regs_t
id|tex_state
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|warp_pipe
r_int
r_int
id|warp_pipe
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
multiline_comment|/* The current cliprects, or a subset thereof.&n;&t; */
DECL|member|boxes
id|drm_clip_rect_t
id|boxes
(braket
id|MGA_NR_SAREA_CLIPRECTS
)braket
suffix:semicolon
DECL|member|nbox
r_int
r_int
id|nbox
suffix:semicolon
multiline_comment|/* Information about the most recently used 3d drawable.  The&n;&t; * client fills in the req_* fields, the server fills in the&n;&t; * exported_ fields and puts the cliprects into boxes, above.&n;&t; *&n;&t; * The client clears the exported_drawable field before&n;&t; * clobbering the boxes data.&n;&t; */
DECL|member|req_drawable
r_int
r_int
id|req_drawable
suffix:semicolon
multiline_comment|/* the X drawable id */
DECL|member|req_draw_buffer
r_int
r_int
id|req_draw_buffer
suffix:semicolon
multiline_comment|/* MGA_FRONT or MGA_BACK */
DECL|member|exported_drawable
r_int
r_int
id|exported_drawable
suffix:semicolon
DECL|member|exported_index
r_int
r_int
id|exported_index
suffix:semicolon
DECL|member|exported_stamp
r_int
r_int
id|exported_stamp
suffix:semicolon
DECL|member|exported_buffers
r_int
r_int
id|exported_buffers
suffix:semicolon
DECL|member|exported_nfront
r_int
r_int
id|exported_nfront
suffix:semicolon
DECL|member|exported_nback
r_int
r_int
id|exported_nback
suffix:semicolon
DECL|member|exported_back_x
DECL|member|exported_front_x
DECL|member|exported_w
r_int
id|exported_back_x
comma
id|exported_front_x
comma
id|exported_w
suffix:semicolon
DECL|member|exported_back_y
DECL|member|exported_front_y
DECL|member|exported_h
r_int
id|exported_back_y
comma
id|exported_front_y
comma
id|exported_h
suffix:semicolon
DECL|member|exported_boxes
id|drm_clip_rect_t
id|exported_boxes
(braket
id|MGA_NR_SAREA_CLIPRECTS
)braket
suffix:semicolon
multiline_comment|/* Counters for aging textures and for client-side throttling.&n;&t; */
DECL|member|status
r_int
r_int
id|status
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|last_wrap
r_int
r_int
id|last_wrap
suffix:semicolon
DECL|member|last_frame
id|drm_mga_age_t
id|last_frame
suffix:semicolon
DECL|member|last_enqueue
r_int
r_int
id|last_enqueue
suffix:semicolon
multiline_comment|/* last time a buffer was enqueued */
DECL|member|last_dispatch
r_int
r_int
id|last_dispatch
suffix:semicolon
multiline_comment|/* age of the most recently dispatched buffer */
DECL|member|last_quiescent
r_int
r_int
id|last_quiescent
suffix:semicolon
multiline_comment|/*  */
multiline_comment|/* LRU lists for texture memory in agp space and on the card.&n;&t; */
DECL|member|texList
id|drm_tex_region_t
id|texList
(braket
id|MGA_NR_TEX_HEAPS
)braket
(braket
id|MGA_NR_TEX_REGIONS
op_plus
l_int|1
)braket
suffix:semicolon
DECL|member|texAge
r_int
r_int
id|texAge
(braket
id|MGA_NR_TEX_HEAPS
)braket
suffix:semicolon
multiline_comment|/* Mechanism to validate card state.&n;&t; */
DECL|member|ctxOwner
r_int
id|ctxOwner
suffix:semicolon
DECL|typedef|drm_mga_sarea_t
)brace
id|drm_mga_sarea_t
suffix:semicolon
multiline_comment|/* WARNING: If you change any of these defines, make sure to change the&n; * defines in the Xserver file (xf86drmMga.h)&n; */
DECL|struct|_drm_mga_warp_index
r_typedef
r_struct
id|_drm_mga_warp_index
(brace
DECL|member|installed
r_int
id|installed
suffix:semicolon
DECL|member|phys_addr
r_int
r_int
id|phys_addr
suffix:semicolon
DECL|member|size
r_int
id|size
suffix:semicolon
DECL|typedef|drm_mga_warp_index_t
)brace
id|drm_mga_warp_index_t
suffix:semicolon
DECL|struct|drm_mga_init
r_typedef
r_struct
id|drm_mga_init
(brace
r_enum
(brace
DECL|enumerator|MGA_INIT_DMA
id|MGA_INIT_DMA
op_assign
l_int|0x01
comma
DECL|enumerator|MGA_CLEANUP_DMA
id|MGA_CLEANUP_DMA
op_assign
l_int|0x02
DECL|member|func
)brace
id|func
suffix:semicolon
DECL|member|sarea_priv_offset
r_int
r_int
id|sarea_priv_offset
suffix:semicolon
DECL|member|chipset
r_int
id|chipset
suffix:semicolon
DECL|member|sgram
r_int
id|sgram
suffix:semicolon
DECL|member|maccess
r_int
r_int
id|maccess
suffix:semicolon
DECL|member|fb_cpp
r_int
r_int
id|fb_cpp
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
DECL|member|depth_cpp
r_int
r_int
id|depth_cpp
suffix:semicolon
DECL|member|depth_offset
DECL|member|depth_pitch
r_int
r_int
id|depth_offset
comma
id|depth_pitch
suffix:semicolon
DECL|member|texture_offset
r_int
r_int
id|texture_offset
(braket
id|MGA_NR_TEX_HEAPS
)braket
suffix:semicolon
DECL|member|texture_size
r_int
r_int
id|texture_size
(braket
id|MGA_NR_TEX_HEAPS
)braket
suffix:semicolon
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
DECL|member|status_offset
r_int
r_int
id|status_offset
suffix:semicolon
DECL|member|warp_offset
r_int
r_int
id|warp_offset
suffix:semicolon
DECL|member|primary_offset
r_int
r_int
id|primary_offset
suffix:semicolon
DECL|member|buffers_offset
r_int
r_int
id|buffers_offset
suffix:semicolon
DECL|typedef|drm_mga_init_t
)brace
id|drm_mga_init_t
suffix:semicolon
DECL|struct|drm_mga_fullscreen
r_typedef
r_struct
id|drm_mga_fullscreen
(brace
r_enum
(brace
DECL|enumerator|MGA_INIT_FULLSCREEN
id|MGA_INIT_FULLSCREEN
op_assign
l_int|0x01
comma
DECL|enumerator|MGA_CLEANUP_FULLSCREEN
id|MGA_CLEANUP_FULLSCREEN
op_assign
l_int|0x02
DECL|member|func
)brace
id|func
suffix:semicolon
DECL|typedef|drm_mga_fullscreen_t
)brace
id|drm_mga_fullscreen_t
suffix:semicolon
DECL|struct|drm_mga_clear
r_typedef
r_struct
id|drm_mga_clear
(brace
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
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
DECL|typedef|drm_mga_clear_t
)brace
id|drm_mga_clear_t
suffix:semicolon
DECL|struct|drm_mga_vertex
r_typedef
r_struct
id|drm_mga_vertex
(brace
DECL|member|idx
r_int
id|idx
suffix:semicolon
multiline_comment|/* buffer to queue */
DECL|member|used
r_int
id|used
suffix:semicolon
multiline_comment|/* bytes in use */
DECL|member|discard
r_int
id|discard
suffix:semicolon
multiline_comment|/* client finished with buffer?  */
DECL|typedef|drm_mga_vertex_t
)brace
id|drm_mga_vertex_t
suffix:semicolon
DECL|struct|drm_mga_indices
r_typedef
r_struct
id|drm_mga_indices
(brace
DECL|member|idx
r_int
id|idx
suffix:semicolon
multiline_comment|/* buffer to queue */
DECL|member|start
r_int
r_int
id|start
suffix:semicolon
DECL|member|end
r_int
r_int
id|end
suffix:semicolon
DECL|member|discard
r_int
id|discard
suffix:semicolon
multiline_comment|/* client finished with buffer?  */
DECL|typedef|drm_mga_indices_t
)brace
id|drm_mga_indices_t
suffix:semicolon
DECL|struct|drm_mga_iload
r_typedef
r_struct
id|drm_mga_iload
(brace
DECL|member|idx
r_int
id|idx
suffix:semicolon
DECL|member|dstorg
r_int
r_int
id|dstorg
suffix:semicolon
DECL|member|length
r_int
r_int
id|length
suffix:semicolon
DECL|typedef|drm_mga_iload_t
)brace
id|drm_mga_iload_t
suffix:semicolon
DECL|struct|_drm_mga_blit
r_typedef
r_struct
id|_drm_mga_blit
(brace
DECL|member|planemask
r_int
r_int
id|planemask
suffix:semicolon
DECL|member|srcorg
r_int
r_int
id|srcorg
suffix:semicolon
DECL|member|dstorg
r_int
r_int
id|dstorg
suffix:semicolon
DECL|member|src_pitch
DECL|member|dst_pitch
r_int
id|src_pitch
comma
id|dst_pitch
suffix:semicolon
DECL|member|delta_sx
DECL|member|delta_sy
r_int
id|delta_sx
comma
id|delta_sy
suffix:semicolon
DECL|member|delta_dx
DECL|member|delta_dy
r_int
id|delta_dx
comma
id|delta_dy
suffix:semicolon
DECL|member|height
DECL|member|ydir
r_int
id|height
comma
id|ydir
suffix:semicolon
multiline_comment|/* flip image vertically */
DECL|member|source_pitch
DECL|member|dest_pitch
r_int
id|source_pitch
comma
id|dest_pitch
suffix:semicolon
DECL|typedef|drm_mga_blit_t
)brace
id|drm_mga_blit_t
suffix:semicolon
macro_line|#endif
eof
