macro_line|#ifndef _I810_DRM_H_
DECL|macro|_I810_DRM_H_
mdefine_line|#define _I810_DRM_H_
multiline_comment|/* WARNING: These defines must be the same as what the Xserver uses.&n; * if you change them, you must change the defines in the Xserver.&n; */
macro_line|#ifndef _I810_DEFINES_
DECL|macro|_I810_DEFINES_
mdefine_line|#define _I810_DEFINES_
DECL|macro|I810_DMA_BUF_ORDER
mdefine_line|#define I810_DMA_BUF_ORDER&t;&t;12
DECL|macro|I810_DMA_BUF_SZ
mdefine_line|#define I810_DMA_BUF_SZ &t;&t;(1&lt;&lt;I810_DMA_BUF_ORDER)
DECL|macro|I810_DMA_BUF_NR
mdefine_line|#define I810_DMA_BUF_NR &t;&t;256
DECL|macro|I810_NR_SAREA_CLIPRECTS
mdefine_line|#define I810_NR_SAREA_CLIPRECTS &t;8
multiline_comment|/* Each region is a minimum of 64k, and there are at most 64 of them.&n; */
DECL|macro|I810_NR_TEX_REGIONS
mdefine_line|#define I810_NR_TEX_REGIONS 64
DECL|macro|I810_LOG_MIN_TEX_REGION_SIZE
mdefine_line|#define I810_LOG_MIN_TEX_REGION_SIZE 16
macro_line|#endif
DECL|macro|I810_UPLOAD_TEX0IMAGE
mdefine_line|#define I810_UPLOAD_TEX0IMAGE  0x1 /* handled clientside */
DECL|macro|I810_UPLOAD_TEX1IMAGE
mdefine_line|#define I810_UPLOAD_TEX1IMAGE  0x2 /* handled clientside */
DECL|macro|I810_UPLOAD_CTX
mdefine_line|#define I810_UPLOAD_CTX        0x4
DECL|macro|I810_UPLOAD_BUFFERS
mdefine_line|#define I810_UPLOAD_BUFFERS    0x8
DECL|macro|I810_UPLOAD_TEX0
mdefine_line|#define I810_UPLOAD_TEX0       0x10
DECL|macro|I810_UPLOAD_TEX1
mdefine_line|#define I810_UPLOAD_TEX1       0x20
DECL|macro|I810_UPLOAD_CLIPRECTS
mdefine_line|#define I810_UPLOAD_CLIPRECTS  0x40
multiline_comment|/* Indices into buf.Setup where various bits of state are mirrored per&n; * context and per buffer.  These can be fired at the card as a unit,&n; * or in a piecewise fashion as required.&n; */
multiline_comment|/* Destbuffer state &n; *    - backbuffer linear offset and pitch -- invarient in the current dri&n; *    - zbuffer linear offset and pitch -- also invarient&n; *    - drawing origin in back and depth buffers.&n; *&n; * Keep the depth/back buffer state here to acommodate private buffers&n; * in the future.&n; */
DECL|macro|I810_DESTREG_DI0
mdefine_line|#define I810_DESTREG_DI0  0&t;/* CMD_OP_DESTBUFFER_INFO (2 dwords) */
DECL|macro|I810_DESTREG_DI1
mdefine_line|#define I810_DESTREG_DI1  1
DECL|macro|I810_DESTREG_DV0
mdefine_line|#define I810_DESTREG_DV0  2&t;/* GFX_OP_DESTBUFFER_VARS (2 dwords) */
DECL|macro|I810_DESTREG_DV1
mdefine_line|#define I810_DESTREG_DV1  3
DECL|macro|I810_DESTREG_DR0
mdefine_line|#define I810_DESTREG_DR0  4&t;/* GFX_OP_DRAWRECT_INFO (4 dwords) */
DECL|macro|I810_DESTREG_DR1
mdefine_line|#define I810_DESTREG_DR1  5
DECL|macro|I810_DESTREG_DR2
mdefine_line|#define I810_DESTREG_DR2  6
DECL|macro|I810_DESTREG_DR3
mdefine_line|#define I810_DESTREG_DR3  7
DECL|macro|I810_DESTREG_DR4
mdefine_line|#define I810_DESTREG_DR4  8
DECL|macro|I810_DEST_SETUP_SIZE
mdefine_line|#define I810_DEST_SETUP_SIZE 10
multiline_comment|/* Context state&n; */
DECL|macro|I810_CTXREG_CF0
mdefine_line|#define I810_CTXREG_CF0   0&t;/* GFX_OP_COLOR_FACTOR */
DECL|macro|I810_CTXREG_CF1
mdefine_line|#define I810_CTXREG_CF1   1&t;
DECL|macro|I810_CTXREG_ST0
mdefine_line|#define I810_CTXREG_ST0   2     /* GFX_OP_STIPPLE */
DECL|macro|I810_CTXREG_ST1
mdefine_line|#define I810_CTXREG_ST1   3
DECL|macro|I810_CTXREG_VF
mdefine_line|#define I810_CTXREG_VF    4&t;/* GFX_OP_VERTEX_FMT */
DECL|macro|I810_CTXREG_MT
mdefine_line|#define I810_CTXREG_MT    5&t;/* GFX_OP_MAP_TEXELS */
DECL|macro|I810_CTXREG_MC0
mdefine_line|#define I810_CTXREG_MC0   6&t;/* GFX_OP_MAP_COLOR_STAGES - stage 0 */
DECL|macro|I810_CTXREG_MC1
mdefine_line|#define I810_CTXREG_MC1   7     /* GFX_OP_MAP_COLOR_STAGES - stage 1 */
DECL|macro|I810_CTXREG_MC2
mdefine_line|#define I810_CTXREG_MC2   8&t;/* GFX_OP_MAP_COLOR_STAGES - stage 2 */
DECL|macro|I810_CTXREG_MA0
mdefine_line|#define I810_CTXREG_MA0   9&t;/* GFX_OP_MAP_ALPHA_STAGES - stage 0 */
DECL|macro|I810_CTXREG_MA1
mdefine_line|#define I810_CTXREG_MA1   10&t;/* GFX_OP_MAP_ALPHA_STAGES - stage 1 */
DECL|macro|I810_CTXREG_MA2
mdefine_line|#define I810_CTXREG_MA2   11&t;/* GFX_OP_MAP_ALPHA_STAGES - stage 2 */
DECL|macro|I810_CTXREG_SDM
mdefine_line|#define I810_CTXREG_SDM   12&t;/* GFX_OP_SRC_DEST_MONO */
DECL|macro|I810_CTXREG_FOG
mdefine_line|#define I810_CTXREG_FOG   13&t;/* GFX_OP_FOG_COLOR */
DECL|macro|I810_CTXREG_B1
mdefine_line|#define I810_CTXREG_B1    14&t;/* GFX_OP_BOOL_1 */
DECL|macro|I810_CTXREG_B2
mdefine_line|#define I810_CTXREG_B2    15&t;/* GFX_OP_BOOL_2 */
DECL|macro|I810_CTXREG_LCS
mdefine_line|#define I810_CTXREG_LCS   16&t;/* GFX_OP_LINEWIDTH_CULL_SHADE_MODE */
DECL|macro|I810_CTXREG_PV
mdefine_line|#define I810_CTXREG_PV    17&t;/* GFX_OP_PV_RULE -- Invarient! */
DECL|macro|I810_CTXREG_ZA
mdefine_line|#define I810_CTXREG_ZA    18&t;/* GFX_OP_ZBIAS_ALPHAFUNC */
DECL|macro|I810_CTXREG_AA
mdefine_line|#define I810_CTXREG_AA    19&t;/* GFX_OP_ANTIALIAS */
DECL|macro|I810_CTX_SETUP_SIZE
mdefine_line|#define I810_CTX_SETUP_SIZE 20 
multiline_comment|/* Texture state (per tex unit)&n; */
DECL|macro|I810_TEXREG_MI0
mdefine_line|#define I810_TEXREG_MI0  0&t;/* GFX_OP_MAP_INFO (4 dwords) */
DECL|macro|I810_TEXREG_MI1
mdefine_line|#define I810_TEXREG_MI1  1&t;
DECL|macro|I810_TEXREG_MI2
mdefine_line|#define I810_TEXREG_MI2  2&t;
DECL|macro|I810_TEXREG_MI3
mdefine_line|#define I810_TEXREG_MI3  3&t;
DECL|macro|I810_TEXREG_MF
mdefine_line|#define I810_TEXREG_MF   4&t;/* GFX_OP_MAP_FILTER */
DECL|macro|I810_TEXREG_MLC
mdefine_line|#define I810_TEXREG_MLC  5&t;/* GFX_OP_MAP_LOD_CTL */
DECL|macro|I810_TEXREG_MLL
mdefine_line|#define I810_TEXREG_MLL  6&t;/* GFX_OP_MAP_LOD_LIMITS */
DECL|macro|I810_TEXREG_MCS
mdefine_line|#define I810_TEXREG_MCS  7&t;/* GFX_OP_MAP_COORD_SETS ??? */
DECL|macro|I810_TEX_SETUP_SIZE
mdefine_line|#define I810_TEX_SETUP_SIZE 8
multiline_comment|/* Flags for clear ioctl&n; */
DECL|macro|I810_FRONT
mdefine_line|#define I810_FRONT   0x1
DECL|macro|I810_BACK
mdefine_line|#define I810_BACK    0x2
DECL|macro|I810_DEPTH
mdefine_line|#define I810_DEPTH   0x4
DECL|struct|_drm_i810_init
r_typedef
r_struct
id|_drm_i810_init
(brace
r_enum
(brace
DECL|enumerator|I810_INIT_DMA
id|I810_INIT_DMA
op_assign
l_int|0x01
comma
DECL|enumerator|I810_CLEANUP_DMA
id|I810_CLEANUP_DMA
op_assign
l_int|0x02
DECL|member|func
)brace
id|func
suffix:semicolon
macro_line|#if CONFIG_XFREE86_VERSION &lt; XFREE86_VERSION(4,1,0,0)
DECL|member|ring_map_idx
r_int
id|ring_map_idx
suffix:semicolon
DECL|member|buffer_map_idx
r_int
id|buffer_map_idx
suffix:semicolon
macro_line|#else
DECL|member|mmio_offset
r_int
r_int
id|mmio_offset
suffix:semicolon
DECL|member|buffers_offset
r_int
r_int
id|buffers_offset
suffix:semicolon
macro_line|#endif
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
DECL|member|overlay_offset
r_int
r_int
id|overlay_offset
suffix:semicolon
DECL|member|overlay_physical
r_int
r_int
id|overlay_physical
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
DECL|typedef|drm_i810_init_t
)brace
id|drm_i810_init_t
suffix:semicolon
multiline_comment|/* Warning: If you change the SAREA structure you must change the Xserver&n; * structure as well */
DECL|struct|_drm_i810_tex_region
r_typedef
r_struct
id|_drm_i810_tex_region
(brace
DECL|member|next
DECL|member|prev
r_int
r_char
id|next
comma
id|prev
suffix:semicolon
multiline_comment|/* indices to form a circular LRU  */
DECL|member|in_use
r_int
r_char
id|in_use
suffix:semicolon
multiline_comment|/* owned by a client, or free? */
DECL|member|age
r_int
id|age
suffix:semicolon
multiline_comment|/* tracked by clients to update local LRU&squot;s */
DECL|typedef|drm_i810_tex_region_t
)brace
id|drm_i810_tex_region_t
suffix:semicolon
DECL|struct|_drm_i810_sarea
r_typedef
r_struct
id|_drm_i810_sarea
(brace
DECL|member|ContextState
r_int
r_int
id|ContextState
(braket
id|I810_CTX_SETUP_SIZE
)braket
suffix:semicolon
DECL|member|BufferState
r_int
r_int
id|BufferState
(braket
id|I810_DEST_SETUP_SIZE
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
id|I810_TEX_SETUP_SIZE
)braket
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
id|I810_NR_SAREA_CLIPRECTS
)braket
suffix:semicolon
multiline_comment|/* Maintain an LRU of contiguous regions of texture space.  If&n;&t; * you think you own a region of texture memory, and it has an&n;&t; * age different to the one you set, then you are mistaken and&n;&t; * it has been stolen by another client.  If global texAge&n;&t; * hasn&squot;t changed, there is no need to walk the list.&n;&t; *&n;&t; * These regions can be used as a proxy for the fine-grained&n;&t; * texture information of other clients - by maintaining them&n;&t; * in the same lru which is used to age their own textures,&n;&t; * clients have an approximate lru for the whole of global&n;&t; * texture space, and can make informed decisions as to which&n;&t; * areas to kick out.  There is no need to choose whether to&n;&t; * kick out your own texture or someone else&squot;s - simply eject&n;&t; * them all in LRU order.  &n;&t; */
DECL|member|texList
id|drm_i810_tex_region_t
id|texList
(braket
id|I810_NR_TEX_REGIONS
op_plus
l_int|1
)braket
suffix:semicolon
multiline_comment|/* Last elt is sentinal */
DECL|member|texAge
r_int
id|texAge
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
DECL|member|last_quiescent
r_int
id|last_quiescent
suffix:semicolon
multiline_comment|/*  */
DECL|member|ctxOwner
r_int
id|ctxOwner
suffix:semicolon
multiline_comment|/* last context to upload state */
DECL|member|vertex_prim
r_int
id|vertex_prim
suffix:semicolon
DECL|typedef|drm_i810_sarea_t
)brace
id|drm_i810_sarea_t
suffix:semicolon
multiline_comment|/* WARNING: If you change any of these defines, make sure to change the&n; * defines in the Xserver file (xf86drmMga.h)&n; */
multiline_comment|/* i810 specific ioctls&n; * The device specific ioctl range is 0x40 to 0x79.&n; */
DECL|macro|DRM_IOCTL_I810_INIT
mdefine_line|#define DRM_IOCTL_I810_INIT&t;&t;DRM_IOW( 0x40, drm_i810_init_t)
DECL|macro|DRM_IOCTL_I810_VERTEX
mdefine_line|#define DRM_IOCTL_I810_VERTEX&t;&t;DRM_IOW( 0x41, drm_i810_vertex_t)
DECL|macro|DRM_IOCTL_I810_CLEAR
mdefine_line|#define DRM_IOCTL_I810_CLEAR&t;&t;DRM_IOW( 0x42, drm_i810_clear_t)
DECL|macro|DRM_IOCTL_I810_FLUSH
mdefine_line|#define DRM_IOCTL_I810_FLUSH&t;&t;DRM_IO(  0x43)
DECL|macro|DRM_IOCTL_I810_GETAGE
mdefine_line|#define DRM_IOCTL_I810_GETAGE&t;&t;DRM_IO(  0x44)
DECL|macro|DRM_IOCTL_I810_GETBUF
mdefine_line|#define DRM_IOCTL_I810_GETBUF&t;&t;DRM_IOWR(0x45, drm_i810_dma_t)
DECL|macro|DRM_IOCTL_I810_SWAP
mdefine_line|#define DRM_IOCTL_I810_SWAP&t;&t;DRM_IO(  0x46)
DECL|macro|DRM_IOCTL_I810_COPY
mdefine_line|#define DRM_IOCTL_I810_COPY&t;&t;DRM_IOW( 0x47, drm_i810_copy_t)
DECL|macro|DRM_IOCTL_I810_DOCOPY
mdefine_line|#define DRM_IOCTL_I810_DOCOPY&t;&t;DRM_IO(  0x48)
DECL|macro|DRM_IOCTL_I810_OV0INFO
mdefine_line|#define DRM_IOCTL_I810_OV0INFO&t;&t;DRM_IOR( 0x49, drm_i810_overlay_t)
DECL|macro|DRM_IOCTL_I810_FSTATUS
mdefine_line|#define DRM_IOCTL_I810_FSTATUS&t;&t;DRM_IO ( 0x4a)
DECL|macro|DRM_IOCTL_I810_OV0FLIP
mdefine_line|#define DRM_IOCTL_I810_OV0FLIP&t;&t;DRM_IO ( 0x4b)
DECL|macro|DRM_IOCTL_I810_MC
mdefine_line|#define DRM_IOCTL_I810_MC&t;&t;DRM_IOW( 0x4c, drm_i810_mc_t)
DECL|macro|DRM_IOCTL_I810_RSTATUS
mdefine_line|#define DRM_IOCTL_I810_RSTATUS&t;&t;DRM_IO ( 0x4d )
DECL|struct|_drm_i810_clear
r_typedef
r_struct
id|_drm_i810_clear
(brace
DECL|member|clear_color
r_int
id|clear_color
suffix:semicolon
DECL|member|clear_depth
r_int
id|clear_depth
suffix:semicolon
DECL|member|flags
r_int
id|flags
suffix:semicolon
DECL|typedef|drm_i810_clear_t
)brace
id|drm_i810_clear_t
suffix:semicolon
multiline_comment|/* These may be placeholders if we have more cliprects than&n; * I810_NR_SAREA_CLIPRECTS.  In that case, the client sets discard to&n; * false, indicating that the buffer will be dispatched again with a&n; * new set of cliprects.&n; */
DECL|struct|_drm_i810_vertex
r_typedef
r_struct
id|_drm_i810_vertex
(brace
DECL|member|idx
r_int
id|idx
suffix:semicolon
multiline_comment|/* buffer index */
DECL|member|used
r_int
id|used
suffix:semicolon
multiline_comment|/* nr bytes in use */
DECL|member|discard
r_int
id|discard
suffix:semicolon
multiline_comment|/* client is finished with the buffer? */
DECL|typedef|drm_i810_vertex_t
)brace
id|drm_i810_vertex_t
suffix:semicolon
DECL|struct|_drm_i810_copy_t
r_typedef
r_struct
id|_drm_i810_copy_t
(brace
DECL|member|idx
r_int
id|idx
suffix:semicolon
multiline_comment|/* buffer index */
DECL|member|used
r_int
id|used
suffix:semicolon
multiline_comment|/* nr bytes in use */
DECL|member|address
r_void
op_star
id|address
suffix:semicolon
multiline_comment|/* Address to copy from */
DECL|typedef|drm_i810_copy_t
)brace
id|drm_i810_copy_t
suffix:semicolon
DECL|macro|PR_TRIANGLES
mdefine_line|#define PR_TRIANGLES         (0x0&lt;&lt;18)
DECL|macro|PR_TRISTRIP_0
mdefine_line|#define PR_TRISTRIP_0        (0x1&lt;&lt;18)
DECL|macro|PR_TRISTRIP_1
mdefine_line|#define PR_TRISTRIP_1        (0x2&lt;&lt;18)
DECL|macro|PR_TRIFAN
mdefine_line|#define PR_TRIFAN            (0x3&lt;&lt;18)
DECL|macro|PR_POLYGON
mdefine_line|#define PR_POLYGON           (0x4&lt;&lt;18)
DECL|macro|PR_LINES
mdefine_line|#define PR_LINES             (0x5&lt;&lt;18)
DECL|macro|PR_LINESTRIP
mdefine_line|#define PR_LINESTRIP         (0x6&lt;&lt;18)
DECL|macro|PR_RECTS
mdefine_line|#define PR_RECTS             (0x7&lt;&lt;18)
DECL|macro|PR_MASK
mdefine_line|#define PR_MASK              (0x7&lt;&lt;18)
DECL|struct|drm_i810_dma
r_typedef
r_struct
id|drm_i810_dma
(brace
DECL|member|virtual
r_void
op_star
r_virtual
suffix:semicolon
DECL|member|request_idx
r_int
id|request_idx
suffix:semicolon
DECL|member|request_size
r_int
id|request_size
suffix:semicolon
DECL|member|granted
r_int
id|granted
suffix:semicolon
DECL|typedef|drm_i810_dma_t
)brace
id|drm_i810_dma_t
suffix:semicolon
DECL|struct|_drm_i810_overlay_t
r_typedef
r_struct
id|_drm_i810_overlay_t
(brace
DECL|member|offset
r_int
r_int
id|offset
suffix:semicolon
multiline_comment|/* Address of the Overlay Regs */
DECL|member|physical
r_int
r_int
id|physical
suffix:semicolon
DECL|typedef|drm_i810_overlay_t
)brace
id|drm_i810_overlay_t
suffix:semicolon
DECL|struct|_drm_i810_mc
r_typedef
r_struct
id|_drm_i810_mc
(brace
DECL|member|idx
r_int
id|idx
suffix:semicolon
multiline_comment|/* buffer index */
DECL|member|used
r_int
id|used
suffix:semicolon
multiline_comment|/* nr bytes in use */
DECL|member|num_blocks
r_int
id|num_blocks
suffix:semicolon
multiline_comment|/* number of GFXBlocks */
DECL|member|length
r_int
op_star
id|length
suffix:semicolon
multiline_comment|/* List of lengths for GFXBlocks (FUTURE)*/
DECL|member|last_render
r_int
r_int
id|last_render
suffix:semicolon
multiline_comment|/* Last Render Request */
DECL|typedef|drm_i810_mc_t
)brace
id|drm_i810_mc_t
suffix:semicolon
macro_line|#endif /* _I810_DRM_H_ */
eof
