multiline_comment|/* mga_drm.h -- Public header for the Matrox g200/g400 driver -*- linux-c -*-&n; * Created: Tue Jan 25 01:50:01 1999 by jhartmann@precisioninsight.com&n; *&n; * Copyright 1999 Precision Insight, Inc., Cedar Park, Texas.&n; * Copyright 2000 VA Linux Systems, Inc., Sunnyvale, California.&n; * All rights reserved.&n; *&n; * Permission is hereby granted, free of charge, to any person obtaining a&n; * copy of this software and associated documentation files (the &quot;Software&quot;),&n; * to deal in the Software without restriction, including without limitation&n; * the rights to use, copy, modify, merge, publish, distribute, sublicense,&n; * and/or sell copies of the Software, and to permit persons to whom the&n; * Software is furnished to do so, subject to the following conditions:&n; * &n; * The above copyright notice and this permission notice (including the next&n; * paragraph) shall be included in all copies or substantial portions of the&n; * Software.&n; * &n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR&n; * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n; * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL&n; * PRECISION INSIGHT AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR&n; * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,&n; * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER&n; * DEALINGS IN THE SOFTWARE.&n; *&n; * Authors: Jeff Hartmann &lt;jhartmann@valinux.com&gt;&n; *          Keith Whitwell &lt;keithw@valinux.com&gt;&n; *&n; */
macro_line|#ifndef _MGA_DRM_H_
DECL|macro|_MGA_DRM_H_
mdefine_line|#define _MGA_DRM_H_
multiline_comment|/* WARNING: If you change any of these defines, make sure to change the&n; * defines in the Xserver file (xf86drmMga.h)&n; */
macro_line|#ifndef _MGA_DEFINES_
DECL|macro|_MGA_DEFINES_
mdefine_line|#define _MGA_DEFINES_
DECL|macro|MGA_F
mdefine_line|#define MGA_F  0x1&t;&t;/* fog */
DECL|macro|MGA_A
mdefine_line|#define MGA_A  0x2&t;&t;/* alpha */
DECL|macro|MGA_S
mdefine_line|#define MGA_S  0x4&t;&t;/* specular */
DECL|macro|MGA_T2
mdefine_line|#define MGA_T2 0x8&t;&t;/* multitexture */
DECL|macro|MGA_WARP_TGZ
mdefine_line|#define MGA_WARP_TGZ            0
DECL|macro|MGA_WARP_TGZF
mdefine_line|#define MGA_WARP_TGZF           (MGA_F)
DECL|macro|MGA_WARP_TGZA
mdefine_line|#define MGA_WARP_TGZA           (MGA_A)
DECL|macro|MGA_WARP_TGZAF
mdefine_line|#define MGA_WARP_TGZAF          (MGA_F|MGA_A)
DECL|macro|MGA_WARP_TGZS
mdefine_line|#define MGA_WARP_TGZS           (MGA_S)
DECL|macro|MGA_WARP_TGZSF
mdefine_line|#define MGA_WARP_TGZSF          (MGA_S|MGA_F)
DECL|macro|MGA_WARP_TGZSA
mdefine_line|#define MGA_WARP_TGZSA          (MGA_S|MGA_A)
DECL|macro|MGA_WARP_TGZSAF
mdefine_line|#define MGA_WARP_TGZSAF         (MGA_S|MGA_F|MGA_A)
DECL|macro|MGA_WARP_T2GZ
mdefine_line|#define MGA_WARP_T2GZ           (MGA_T2)
DECL|macro|MGA_WARP_T2GZF
mdefine_line|#define MGA_WARP_T2GZF          (MGA_T2|MGA_F)
DECL|macro|MGA_WARP_T2GZA
mdefine_line|#define MGA_WARP_T2GZA          (MGA_T2|MGA_A)
DECL|macro|MGA_WARP_T2GZAF
mdefine_line|#define MGA_WARP_T2GZAF         (MGA_T2|MGA_A|MGA_F)
DECL|macro|MGA_WARP_T2GZS
mdefine_line|#define MGA_WARP_T2GZS          (MGA_T2|MGA_S)
DECL|macro|MGA_WARP_T2GZSF
mdefine_line|#define MGA_WARP_T2GZSF         (MGA_T2|MGA_S|MGA_F)
DECL|macro|MGA_WARP_T2GZSA
mdefine_line|#define MGA_WARP_T2GZSA         (MGA_T2|MGA_S|MGA_A)
DECL|macro|MGA_WARP_T2GZSAF
mdefine_line|#define MGA_WARP_T2GZSAF        (MGA_T2|MGA_S|MGA_F|MGA_A)
DECL|macro|MGA_MAX_G400_PIPES
mdefine_line|#define MGA_MAX_G400_PIPES 16
DECL|macro|MGA_MAX_G200_PIPES
mdefine_line|#define MGA_MAX_G200_PIPES  8&t;/* no multitex */
DECL|macro|MGA_MAX_WARP_PIPES
mdefine_line|#define MGA_MAX_WARP_PIPES MGA_MAX_G400_PIPES
DECL|macro|MGA_CARD_TYPE_G200
mdefine_line|#define MGA_CARD_TYPE_G200 1
DECL|macro|MGA_CARD_TYPE_G400
mdefine_line|#define MGA_CARD_TYPE_G400 2
DECL|macro|MGA_FRONT
mdefine_line|#define MGA_FRONT   0x1
DECL|macro|MGA_BACK
mdefine_line|#define MGA_BACK    0x2
DECL|macro|MGA_DEPTH
mdefine_line|#define MGA_DEPTH   0x4
multiline_comment|/* 3d state excluding texture units:&n; */
DECL|macro|MGA_CTXREG_DSTORG
mdefine_line|#define MGA_CTXREG_DSTORG     0&t;/* validated */
DECL|macro|MGA_CTXREG_MACCESS
mdefine_line|#define MGA_CTXREG_MACCESS    1&t;
DECL|macro|MGA_CTXREG_PLNWT
mdefine_line|#define MGA_CTXREG_PLNWT      2 &t;
DECL|macro|MGA_CTXREG_DWGCTL
mdefine_line|#define MGA_CTXREG_DWGCTL     3&t;
DECL|macro|MGA_CTXREG_ALPHACTRL
mdefine_line|#define MGA_CTXREG_ALPHACTRL  4
DECL|macro|MGA_CTXREG_FOGCOLOR
mdefine_line|#define MGA_CTXREG_FOGCOLOR   5
DECL|macro|MGA_CTXREG_WFLAG
mdefine_line|#define MGA_CTXREG_WFLAG      6
DECL|macro|MGA_CTXREG_TDUAL0
mdefine_line|#define MGA_CTXREG_TDUAL0     7
DECL|macro|MGA_CTXREG_TDUAL1
mdefine_line|#define MGA_CTXREG_TDUAL1     8
DECL|macro|MGA_CTXREG_FCOL
mdefine_line|#define MGA_CTXREG_FCOL       9
DECL|macro|MGA_CTXREG_STENCIL
mdefine_line|#define MGA_CTXREG_STENCIL    10
DECL|macro|MGA_CTXREG_STENCILCTL
mdefine_line|#define MGA_CTXREG_STENCILCTL 11
DECL|macro|MGA_CTX_SETUP_SIZE
mdefine_line|#define MGA_CTX_SETUP_SIZE    12
multiline_comment|/* 2d state&n; */
DECL|macro|MGA_2DREG_PITCH
mdefine_line|#define MGA_2DREG_PITCH &t;0
DECL|macro|MGA_2D_SETUP_SIZE
mdefine_line|#define MGA_2D_SETUP_SIZE &t;1
multiline_comment|/* Each texture unit has a state:&n; */
DECL|macro|MGA_TEXREG_CTL
mdefine_line|#define MGA_TEXREG_CTL        0
DECL|macro|MGA_TEXREG_CTL2
mdefine_line|#define MGA_TEXREG_CTL2       1
DECL|macro|MGA_TEXREG_FILTER
mdefine_line|#define MGA_TEXREG_FILTER     2
DECL|macro|MGA_TEXREG_BORDERCOL
mdefine_line|#define MGA_TEXREG_BORDERCOL  3
DECL|macro|MGA_TEXREG_ORG
mdefine_line|#define MGA_TEXREG_ORG        4 /* validated */
DECL|macro|MGA_TEXREG_ORG1
mdefine_line|#define MGA_TEXREG_ORG1       5
DECL|macro|MGA_TEXREG_ORG2
mdefine_line|#define MGA_TEXREG_ORG2       6
DECL|macro|MGA_TEXREG_ORG3
mdefine_line|#define MGA_TEXREG_ORG3       7
DECL|macro|MGA_TEXREG_ORG4
mdefine_line|#define MGA_TEXREG_ORG4       8
DECL|macro|MGA_TEXREG_WIDTH
mdefine_line|#define MGA_TEXREG_WIDTH      9
DECL|macro|MGA_TEXREG_HEIGHT
mdefine_line|#define MGA_TEXREG_HEIGHT     10
DECL|macro|MGA_TEX_SETUP_SIZE
mdefine_line|#define MGA_TEX_SETUP_SIZE    11
multiline_comment|/* What needs to be changed for the current vertex dma buffer?&n; */
DECL|macro|MGA_UPLOAD_CTX
mdefine_line|#define MGA_UPLOAD_CTX        0x1
DECL|macro|MGA_UPLOAD_TEX0
mdefine_line|#define MGA_UPLOAD_TEX0       0x2
DECL|macro|MGA_UPLOAD_TEX1
mdefine_line|#define MGA_UPLOAD_TEX1       0x4
DECL|macro|MGA_UPLOAD_PIPE
mdefine_line|#define MGA_UPLOAD_PIPE       0x8
DECL|macro|MGA_UPLOAD_TEX0IMAGE
mdefine_line|#define MGA_UPLOAD_TEX0IMAGE  0x10 /* handled client-side */
DECL|macro|MGA_UPLOAD_TEX1IMAGE
mdefine_line|#define MGA_UPLOAD_TEX1IMAGE  0x20 /* handled client-side */
DECL|macro|MGA_UPLOAD_2D
mdefine_line|#define MGA_UPLOAD_2D &t;      0x40
DECL|macro|MGA_WAIT_AGE
mdefine_line|#define MGA_WAIT_AGE          0x80 /* handled client-side */
DECL|macro|MGA_UPLOAD_CLIPRECTS
mdefine_line|#define MGA_UPLOAD_CLIPRECTS  0x100 /* handled client-side */
DECL|macro|MGA_DMA_FLUSH
mdefine_line|#define MGA_DMA_FLUSH&t;      0x200 /* set when someone gets the lock&n;                                       quiescent */
multiline_comment|/* 32 buffers of 64k each, total 2 meg.&n; */
DECL|macro|MGA_DMA_BUF_ORDER
mdefine_line|#define MGA_DMA_BUF_ORDER     16
DECL|macro|MGA_DMA_BUF_SZ
mdefine_line|#define MGA_DMA_BUF_SZ        (1&lt;&lt;MGA_DMA_BUF_ORDER)
DECL|macro|MGA_DMA_BUF_NR
mdefine_line|#define MGA_DMA_BUF_NR        31
multiline_comment|/* Keep these small for testing.&n; */
DECL|macro|MGA_NR_SAREA_CLIPRECTS
mdefine_line|#define MGA_NR_SAREA_CLIPRECTS 8
multiline_comment|/* 2 heaps (1 for card, 1 for agp), each divided into upto 128&n; * regions, subject to a minimum region size of (1&lt;&lt;16) == 64k. &n; *&n; * Clients may subdivide regions internally, but when sharing between&n; * clients, the region size is the minimum granularity. &n; */
DECL|macro|MGA_CARD_HEAP
mdefine_line|#define MGA_CARD_HEAP 0
DECL|macro|MGA_AGP_HEAP
mdefine_line|#define MGA_AGP_HEAP  1
DECL|macro|MGA_NR_TEX_HEAPS
mdefine_line|#define MGA_NR_TEX_HEAPS 2
DECL|macro|MGA_NR_TEX_REGIONS
mdefine_line|#define MGA_NR_TEX_REGIONS 16
DECL|macro|MGA_LOG_MIN_TEX_REGION_SIZE
mdefine_line|#define MGA_LOG_MIN_TEX_REGION_SIZE 16
macro_line|#endif
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
DECL|member|reserved_map_agpstart
r_int
id|reserved_map_agpstart
suffix:semicolon
DECL|member|reserved_map_idx
r_int
id|reserved_map_idx
suffix:semicolon
DECL|member|buffer_map_idx
r_int
id|buffer_map_idx
suffix:semicolon
DECL|member|sarea_priv_offset
r_int
id|sarea_priv_offset
suffix:semicolon
DECL|member|primary_size
r_int
id|primary_size
suffix:semicolon
DECL|member|warp_ucode_size
r_int
id|warp_ucode_size
suffix:semicolon
DECL|member|frontOffset
r_int
r_int
id|frontOffset
suffix:semicolon
DECL|member|backOffset
r_int
r_int
id|backOffset
suffix:semicolon
DECL|member|depthOffset
r_int
r_int
id|depthOffset
suffix:semicolon
DECL|member|textureOffset
r_int
r_int
id|textureOffset
suffix:semicolon
DECL|member|textureSize
r_int
r_int
id|textureSize
suffix:semicolon
DECL|member|agpTextureOffset
r_int
r_int
id|agpTextureOffset
suffix:semicolon
DECL|member|agpTextureSize
r_int
r_int
id|agpTextureSize
suffix:semicolon
DECL|member|cpp
r_int
r_int
id|cpp
suffix:semicolon
DECL|member|stride
r_int
r_int
id|stride
suffix:semicolon
DECL|member|sgram
r_int
id|sgram
suffix:semicolon
DECL|member|chipset
r_int
id|chipset
suffix:semicolon
DECL|member|WarpIndex
id|drm_mga_warp_index_t
id|WarpIndex
(braket
id|MGA_MAX_WARP_PIPES
)braket
suffix:semicolon
DECL|member|mAccess
r_int
r_int
id|mAccess
suffix:semicolon
DECL|typedef|drm_mga_init_t
)brace
id|drm_mga_init_t
suffix:semicolon
multiline_comment|/* Warning: if you change the sarea structure, you must change the Xserver&n; * structures as well */
DECL|struct|_drm_mga_tex_region
r_typedef
r_struct
id|_drm_mga_tex_region
(brace
DECL|member|next
DECL|member|prev
r_int
r_char
id|next
comma
id|prev
suffix:semicolon
DECL|member|in_use
r_int
r_char
id|in_use
suffix:semicolon
DECL|member|age
r_int
r_int
id|age
suffix:semicolon
DECL|typedef|drm_mga_tex_region_t
)brace
id|drm_mga_tex_region_t
suffix:semicolon
DECL|struct|_drm_mga_sarea
r_typedef
r_struct
id|_drm_mga_sarea
(brace
multiline_comment|/* The channel for communication of state information to the kernel&n;&t; * on firing a vertex dma buffer.&n;&t; */
DECL|member|ContextState
r_int
r_int
id|ContextState
(braket
id|MGA_CTX_SETUP_SIZE
)braket
suffix:semicolon
DECL|member|ServerState
r_int
r_int
id|ServerState
(braket
id|MGA_2D_SETUP_SIZE
)braket
suffix:semicolon
DECL|member|TexState
r_int
r_int
id|TexState
(braket
l_int|2
)braket
(braket
id|MGA_TEX_SETUP_SIZE
)braket
suffix:semicolon
DECL|member|WarpPipe
r_int
r_int
id|WarpPipe
suffix:semicolon
DECL|member|dirty
r_int
r_int
id|dirty
suffix:semicolon
DECL|member|nbox
r_int
r_int
id|nbox
suffix:semicolon
DECL|member|boxes
id|drm_clip_rect_t
id|boxes
(braket
id|MGA_NR_SAREA_CLIPRECTS
)braket
suffix:semicolon
multiline_comment|/* Information about the most recently used 3d drawable.  The&n;&t; * client fills in the req_* fields, the server fills in the &n;&t; * exported_ fields and puts the cliprects into boxes, above.&n;&t; *&n;&t; * The client clears the exported_drawable field before&n;&t; * clobbering the boxes data.&n;&t; */
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
multiline_comment|/* LRU lists for texture memory in agp space and on the card&n;&t; */
DECL|member|texList
id|drm_mga_tex_region_t
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
DECL|member|vertexsize
r_int
id|vertexsize
suffix:semicolon
DECL|typedef|drm_mga_sarea_t
)brace
id|drm_mga_sarea_t
suffix:semicolon
multiline_comment|/* Device specific ioctls:&n; */
DECL|struct|_drm_mga_clear
r_typedef
r_struct
id|_drm_mga_clear
(brace
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
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|member|clear_depth_mask
r_int
r_int
id|clear_depth_mask
suffix:semicolon
DECL|member|clear_color_mask
r_int
r_int
id|clear_color_mask
suffix:semicolon
DECL|typedef|drm_mga_clear_t
)brace
id|drm_mga_clear_t
suffix:semicolon
DECL|struct|_drm_mga_swap
r_typedef
r_struct
id|_drm_mga_swap
(brace
DECL|member|dummy
r_int
id|dummy
suffix:semicolon
DECL|typedef|drm_mga_swap_t
)brace
id|drm_mga_swap_t
suffix:semicolon
DECL|struct|_drm_mga_iload
r_typedef
r_struct
id|_drm_mga_iload
(brace
DECL|member|idx
r_int
id|idx
suffix:semicolon
DECL|member|length
r_int
id|length
suffix:semicolon
DECL|member|destOrg
r_int
r_int
id|destOrg
suffix:semicolon
DECL|typedef|drm_mga_iload_t
)brace
id|drm_mga_iload_t
suffix:semicolon
DECL|struct|_drm_mga_vertex
r_typedef
r_struct
id|_drm_mga_vertex
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
DECL|struct|_drm_mga_indices
r_typedef
r_struct
id|_drm_mga_indices
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
macro_line|#endif
eof
