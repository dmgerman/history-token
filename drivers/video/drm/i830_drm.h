macro_line|#ifndef _I830_DRM_H_
DECL|macro|_I830_DRM_H_
mdefine_line|#define _I830_DRM_H_
multiline_comment|/* WARNING: These defines must be the same as what the Xserver uses.&n; * if you change them, you must change the defines in the Xserver.&n; */
macro_line|#ifndef _I830_DEFINES_
DECL|macro|_I830_DEFINES_
mdefine_line|#define _I830_DEFINES_
DECL|macro|I830_DMA_BUF_ORDER
mdefine_line|#define I830_DMA_BUF_ORDER&t;&t;12
DECL|macro|I830_DMA_BUF_SZ
mdefine_line|#define I830_DMA_BUF_SZ &t;&t;(1&lt;&lt;I830_DMA_BUF_ORDER)
DECL|macro|I830_DMA_BUF_NR
mdefine_line|#define I830_DMA_BUF_NR &t;&t;256
DECL|macro|I830_NR_SAREA_CLIPRECTS
mdefine_line|#define I830_NR_SAREA_CLIPRECTS &t;8
multiline_comment|/* Each region is a minimum of 64k, and there are at most 64 of them.&n; */
DECL|macro|I830_NR_TEX_REGIONS
mdefine_line|#define I830_NR_TEX_REGIONS 64
DECL|macro|I830_LOG_MIN_TEX_REGION_SIZE
mdefine_line|#define I830_LOG_MIN_TEX_REGION_SIZE 16
multiline_comment|/* if defining I830_ENABLE_4_TEXTURES, do it in i830_3d_reg.h, too */
macro_line|#if !defined(I830_ENABLE_4_TEXTURES)
DECL|macro|I830_TEXTURE_COUNT
mdefine_line|#define I830_TEXTURE_COUNT&t;2
DECL|macro|I830_TEXBLEND_COUNT
mdefine_line|#define I830_TEXBLEND_COUNT&t;2&t;/* always same as TEXTURE_COUNT? */
macro_line|#else /* defined(I830_ENABLE_4_TEXTURES) */
DECL|macro|I830_TEXTURE_COUNT
mdefine_line|#define I830_TEXTURE_COUNT&t;4
DECL|macro|I830_TEXBLEND_COUNT
mdefine_line|#define I830_TEXBLEND_COUNT&t;4&t;/* always same as TEXTURE_COUNT? */
macro_line|#endif /* I830_ENABLE_4_TEXTURES */
DECL|macro|I830_TEXBLEND_SIZE
mdefine_line|#define I830_TEXBLEND_SIZE&t;12&t;/* (4 args + op) * 2 + COLOR_FACTOR */
DECL|macro|I830_UPLOAD_CTX
mdefine_line|#define I830_UPLOAD_CTX&t;&t;&t;0x1
DECL|macro|I830_UPLOAD_BUFFERS
mdefine_line|#define I830_UPLOAD_BUFFERS&t;&t;0x2
DECL|macro|I830_UPLOAD_CLIPRECTS
mdefine_line|#define I830_UPLOAD_CLIPRECTS&t;&t;0x4
DECL|macro|I830_UPLOAD_TEX0_IMAGE
mdefine_line|#define I830_UPLOAD_TEX0_IMAGE&t;&t;0x100 /* handled clientside */
DECL|macro|I830_UPLOAD_TEX0_CUBE
mdefine_line|#define I830_UPLOAD_TEX0_CUBE&t;&t;0x200 /* handled clientside */
DECL|macro|I830_UPLOAD_TEX1_IMAGE
mdefine_line|#define I830_UPLOAD_TEX1_IMAGE&t;&t;0x400 /* handled clientside */
DECL|macro|I830_UPLOAD_TEX1_CUBE
mdefine_line|#define I830_UPLOAD_TEX1_CUBE&t;&t;0x800 /* handled clientside */
DECL|macro|I830_UPLOAD_TEX2_IMAGE
mdefine_line|#define I830_UPLOAD_TEX2_IMAGE&t;&t;0x1000 /* handled clientside */
DECL|macro|I830_UPLOAD_TEX2_CUBE
mdefine_line|#define I830_UPLOAD_TEX2_CUBE&t;&t;0x2000 /* handled clientside */
DECL|macro|I830_UPLOAD_TEX3_IMAGE
mdefine_line|#define I830_UPLOAD_TEX3_IMAGE&t;&t;0x4000 /* handled clientside */
DECL|macro|I830_UPLOAD_TEX3_CUBE
mdefine_line|#define I830_UPLOAD_TEX3_CUBE&t;&t;0x8000 /* handled clientside */
DECL|macro|I830_UPLOAD_TEX_N_IMAGE
mdefine_line|#define I830_UPLOAD_TEX_N_IMAGE(n)&t;(0x100 &lt;&lt; (n * 2))
DECL|macro|I830_UPLOAD_TEX_N_CUBE
mdefine_line|#define I830_UPLOAD_TEX_N_CUBE(n)&t;(0x200 &lt;&lt; (n * 2))
DECL|macro|I830_UPLOAD_TEXIMAGE_MASK
mdefine_line|#define I830_UPLOAD_TEXIMAGE_MASK&t;0xff00
DECL|macro|I830_UPLOAD_TEX0
mdefine_line|#define I830_UPLOAD_TEX0&t;&t;&t;0x10000
DECL|macro|I830_UPLOAD_TEX1
mdefine_line|#define I830_UPLOAD_TEX1&t;&t;&t;0x20000
DECL|macro|I830_UPLOAD_TEX2
mdefine_line|#define I830_UPLOAD_TEX2&t;&t;&t;0x40000
DECL|macro|I830_UPLOAD_TEX3
mdefine_line|#define I830_UPLOAD_TEX3&t;&t;&t;0x80000
DECL|macro|I830_UPLOAD_TEX_N
mdefine_line|#define I830_UPLOAD_TEX_N(n)&t;&t;(0x10000 &lt;&lt; (n))
DECL|macro|I830_UPLOAD_TEX_MASK
mdefine_line|#define I830_UPLOAD_TEX_MASK&t;&t;0xf0000
DECL|macro|I830_UPLOAD_TEXBLEND0
mdefine_line|#define I830_UPLOAD_TEXBLEND0&t;&t;0x100000
DECL|macro|I830_UPLOAD_TEXBLEND1
mdefine_line|#define I830_UPLOAD_TEXBLEND1&t;&t;0x200000
DECL|macro|I830_UPLOAD_TEXBLEND2
mdefine_line|#define I830_UPLOAD_TEXBLEND2&t;&t;0x400000
DECL|macro|I830_UPLOAD_TEXBLEND3
mdefine_line|#define I830_UPLOAD_TEXBLEND3&t;&t;0x800000
DECL|macro|I830_UPLOAD_TEXBLEND_N
mdefine_line|#define I830_UPLOAD_TEXBLEND_N(n)&t;(0x100000 &lt;&lt; (n))
DECL|macro|I830_UPLOAD_TEXBLEND_MASK
mdefine_line|#define I830_UPLOAD_TEXBLEND_MASK&t;0xf00000
DECL|macro|I830_UPLOAD_TEX_PALETTE_N
mdefine_line|#define I830_UPLOAD_TEX_PALETTE_N(n)    (0x1000000 &lt;&lt; (n))
DECL|macro|I830_UPLOAD_TEX_PALETTE_SHARED
mdefine_line|#define I830_UPLOAD_TEX_PALETTE_SHARED&t;0x4000000
multiline_comment|/* Indices into buf.Setup where various bits of state are mirrored per&n; * context and per buffer.  These can be fired at the card as a unit,&n; * or in a piecewise fashion as required.&n; */
multiline_comment|/* Destbuffer state &n; *    - backbuffer linear offset and pitch -- invarient in the current dri&n; *    - zbuffer linear offset and pitch -- also invarient&n; *    - drawing origin in back and depth buffers.&n; *&n; * Keep the depth/back buffer state here to acommodate private buffers&n; * in the future.&n; */
DECL|macro|I830_DESTREG_CBUFADDR
mdefine_line|#define I830_DESTREG_CBUFADDR 0
multiline_comment|/* Invarient */
DECL|macro|I830_DESTREG_DBUFADDR
mdefine_line|#define I830_DESTREG_DBUFADDR 1
DECL|macro|I830_DESTREG_DV0
mdefine_line|#define I830_DESTREG_DV0 2
DECL|macro|I830_DESTREG_DV1
mdefine_line|#define I830_DESTREG_DV1 3
DECL|macro|I830_DESTREG_SENABLE
mdefine_line|#define I830_DESTREG_SENABLE 4
DECL|macro|I830_DESTREG_SR0
mdefine_line|#define I830_DESTREG_SR0 5
DECL|macro|I830_DESTREG_SR1
mdefine_line|#define I830_DESTREG_SR1 6
DECL|macro|I830_DESTREG_SR2
mdefine_line|#define I830_DESTREG_SR2 7
DECL|macro|I830_DESTREG_DR0
mdefine_line|#define I830_DESTREG_DR0 8
DECL|macro|I830_DESTREG_DR1
mdefine_line|#define I830_DESTREG_DR1 9
DECL|macro|I830_DESTREG_DR2
mdefine_line|#define I830_DESTREG_DR2 10
DECL|macro|I830_DESTREG_DR3
mdefine_line|#define I830_DESTREG_DR3 11
DECL|macro|I830_DESTREG_DR4
mdefine_line|#define I830_DESTREG_DR4 12
DECL|macro|I830_DEST_SETUP_SIZE
mdefine_line|#define I830_DEST_SETUP_SIZE 13
multiline_comment|/* Context state&n; */
DECL|macro|I830_CTXREG_STATE1
mdefine_line|#define I830_CTXREG_STATE1&t;&t;0
DECL|macro|I830_CTXREG_STATE2
mdefine_line|#define I830_CTXREG_STATE2&t;&t;1
DECL|macro|I830_CTXREG_STATE3
mdefine_line|#define I830_CTXREG_STATE3&t;&t;2
DECL|macro|I830_CTXREG_STATE4
mdefine_line|#define I830_CTXREG_STATE4&t;&t;3
DECL|macro|I830_CTXREG_STATE5
mdefine_line|#define I830_CTXREG_STATE5&t;&t;4
DECL|macro|I830_CTXREG_IALPHAB
mdefine_line|#define I830_CTXREG_IALPHAB&t;&t;5
DECL|macro|I830_CTXREG_STENCILTST
mdefine_line|#define I830_CTXREG_STENCILTST&t;&t;6
DECL|macro|I830_CTXREG_ENABLES_1
mdefine_line|#define I830_CTXREG_ENABLES_1&t;&t;7
DECL|macro|I830_CTXREG_ENABLES_2
mdefine_line|#define I830_CTXREG_ENABLES_2&t;&t;8
DECL|macro|I830_CTXREG_AA
mdefine_line|#define I830_CTXREG_AA&t;&t;&t;9
DECL|macro|I830_CTXREG_FOGCOLOR
mdefine_line|#define I830_CTXREG_FOGCOLOR&t;&t;10
DECL|macro|I830_CTXREG_BLENDCOLR0
mdefine_line|#define I830_CTXREG_BLENDCOLR0&t;&t;11
DECL|macro|I830_CTXREG_BLENDCOLR
mdefine_line|#define I830_CTXREG_BLENDCOLR&t;&t;12 /* Dword 1 of 2 dword command */
DECL|macro|I830_CTXREG_VF
mdefine_line|#define I830_CTXREG_VF&t;&t;&t;13
DECL|macro|I830_CTXREG_VF2
mdefine_line|#define I830_CTXREG_VF2&t;&t;&t;14
DECL|macro|I830_CTXREG_MCSB0
mdefine_line|#define I830_CTXREG_MCSB0&t;&t;15
DECL|macro|I830_CTXREG_MCSB1
mdefine_line|#define I830_CTXREG_MCSB1&t;&t;16
DECL|macro|I830_CTX_SETUP_SIZE
mdefine_line|#define I830_CTX_SETUP_SIZE&t;&t;17
multiline_comment|/* Texture state (per tex unit)&n; */
DECL|macro|I830_TEXREG_MI0
mdefine_line|#define I830_TEXREG_MI0&t;0&t;/* GFX_OP_MAP_INFO (6 dwords) */
DECL|macro|I830_TEXREG_MI1
mdefine_line|#define I830_TEXREG_MI1&t;1
DECL|macro|I830_TEXREG_MI2
mdefine_line|#define I830_TEXREG_MI2&t;2
DECL|macro|I830_TEXREG_MI3
mdefine_line|#define I830_TEXREG_MI3&t;3
DECL|macro|I830_TEXREG_MI4
mdefine_line|#define I830_TEXREG_MI4&t;4
DECL|macro|I830_TEXREG_MI5
mdefine_line|#define I830_TEXREG_MI5&t;5
DECL|macro|I830_TEXREG_MF
mdefine_line|#define I830_TEXREG_MF&t;6&t;/* GFX_OP_MAP_FILTER */
DECL|macro|I830_TEXREG_MLC
mdefine_line|#define I830_TEXREG_MLC&t;7&t;/* GFX_OP_MAP_LOD_CTL */
DECL|macro|I830_TEXREG_MLL
mdefine_line|#define I830_TEXREG_MLL&t;8&t;/* GFX_OP_MAP_LOD_LIMITS */
DECL|macro|I830_TEXREG_MCS
mdefine_line|#define I830_TEXREG_MCS&t;9&t;/* GFX_OP_MAP_COORD_SETS */
DECL|macro|I830_TEX_SETUP_SIZE
mdefine_line|#define I830_TEX_SETUP_SIZE 10
DECL|macro|I830_FRONT
mdefine_line|#define I830_FRONT   0x1
DECL|macro|I830_BACK
mdefine_line|#define I830_BACK    0x2
DECL|macro|I830_DEPTH
mdefine_line|#define I830_DEPTH   0x4
macro_line|#endif /* _I830_DEFINES_ */
DECL|struct|_drm_i830_init
r_typedef
r_struct
id|_drm_i830_init
(brace
r_enum
(brace
DECL|enumerator|I830_INIT_DMA
id|I830_INIT_DMA
op_assign
l_int|0x01
comma
DECL|enumerator|I830_CLEANUP_DMA
id|I830_CLEANUP_DMA
op_assign
l_int|0x02
DECL|member|func
)brace
id|func
suffix:semicolon
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
DECL|typedef|drm_i830_init_t
)brace
id|drm_i830_init_t
suffix:semicolon
multiline_comment|/* Warning: If you change the SAREA structure you must change the Xserver&n; * structure as well */
DECL|struct|_drm_i830_tex_region
r_typedef
r_struct
id|_drm_i830_tex_region
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
DECL|typedef|drm_i830_tex_region_t
)brace
id|drm_i830_tex_region_t
suffix:semicolon
DECL|struct|_drm_i830_sarea
r_typedef
r_struct
id|_drm_i830_sarea
(brace
DECL|member|ContextState
r_int
r_int
id|ContextState
(braket
id|I830_CTX_SETUP_SIZE
)braket
suffix:semicolon
DECL|member|BufferState
r_int
r_int
id|BufferState
(braket
id|I830_DEST_SETUP_SIZE
)braket
suffix:semicolon
DECL|member|TexState
r_int
r_int
id|TexState
(braket
id|I830_TEXTURE_COUNT
)braket
(braket
id|I830_TEX_SETUP_SIZE
)braket
suffix:semicolon
DECL|member|TexBlendState
r_int
r_int
id|TexBlendState
(braket
id|I830_TEXBLEND_COUNT
)braket
(braket
id|I830_TEXBLEND_SIZE
)braket
suffix:semicolon
DECL|member|TexBlendStateWordsUsed
r_int
r_int
id|TexBlendStateWordsUsed
(braket
id|I830_TEXBLEND_COUNT
)braket
suffix:semicolon
DECL|member|Palette
r_int
r_int
id|Palette
(braket
l_int|2
)braket
(braket
l_int|256
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
id|I830_NR_SAREA_CLIPRECTS
)braket
suffix:semicolon
multiline_comment|/* Maintain an LRU of contiguous regions of texture space.  If&n;&t; * you think you own a region of texture memory, and it has an&n;&t; * age different to the one you set, then you are mistaken and&n;&t; * it has been stolen by another client.  If global texAge&n;&t; * hasn&squot;t changed, there is no need to walk the list.&n;&t; *&n;&t; * These regions can be used as a proxy for the fine-grained&n;&t; * texture information of other clients - by maintaining them&n;&t; * in the same lru which is used to age their own textures,&n;&t; * clients have an approximate lru for the whole of global&n;&t; * texture space, and can make informed decisions as to which&n;&t; * areas to kick out.  There is no need to choose whether to&n;&t; * kick out your own texture or someone else&squot;s - simply eject&n;&t; * them all in LRU order.  &n;&t; */
DECL|member|texList
id|drm_i830_tex_region_t
id|texList
(braket
id|I830_NR_TEX_REGIONS
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
DECL|typedef|drm_i830_sarea_t
)brace
id|drm_i830_sarea_t
suffix:semicolon
multiline_comment|/* I830 specific ioctls&n; * The device specific ioctl range is 0x40 to 0x79.&n; */
DECL|macro|DRM_IOCTL_I830_INIT
mdefine_line|#define DRM_IOCTL_I830_INIT&t;&t;DRM_IOW( 0x40, drm_i830_init_t)
DECL|macro|DRM_IOCTL_I830_VERTEX
mdefine_line|#define DRM_IOCTL_I830_VERTEX&t;&t;DRM_IOW( 0x41, drm_i830_vertex_t)
DECL|macro|DRM_IOCTL_I830_CLEAR
mdefine_line|#define DRM_IOCTL_I830_CLEAR&t;&t;DRM_IOW( 0x42, drm_i830_clear_t)
DECL|macro|DRM_IOCTL_I830_FLUSH
mdefine_line|#define DRM_IOCTL_I830_FLUSH&t;&t;DRM_IO ( 0x43)
DECL|macro|DRM_IOCTL_I830_GETAGE
mdefine_line|#define DRM_IOCTL_I830_GETAGE&t;&t;DRM_IO ( 0x44)
DECL|macro|DRM_IOCTL_I830_GETBUF
mdefine_line|#define DRM_IOCTL_I830_GETBUF&t;&t;DRM_IOWR(0x45, drm_i830_dma_t)
DECL|macro|DRM_IOCTL_I830_SWAP
mdefine_line|#define DRM_IOCTL_I830_SWAP&t;&t;DRM_IO ( 0x46)
DECL|macro|DRM_IOCTL_I830_COPY
mdefine_line|#define DRM_IOCTL_I830_COPY&t;&t;DRM_IOW( 0x47, drm_i830_copy_t)
DECL|macro|DRM_IOCTL_I830_DOCOPY
mdefine_line|#define DRM_IOCTL_I830_DOCOPY&t;&t;DRM_IO ( 0x48)
DECL|struct|_drm_i830_clear
r_typedef
r_struct
id|_drm_i830_clear
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
DECL|member|clear_colormask
r_int
r_int
id|clear_colormask
suffix:semicolon
DECL|member|clear_depthmask
r_int
r_int
id|clear_depthmask
suffix:semicolon
DECL|typedef|drm_i830_clear_t
)brace
id|drm_i830_clear_t
suffix:semicolon
multiline_comment|/* These may be placeholders if we have more cliprects than&n; * I830_NR_SAREA_CLIPRECTS.  In that case, the client sets discard to&n; * false, indicating that the buffer will be dispatched again with a&n; * new set of cliprects.&n; */
DECL|struct|_drm_i830_vertex
r_typedef
r_struct
id|_drm_i830_vertex
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
DECL|typedef|drm_i830_vertex_t
)brace
id|drm_i830_vertex_t
suffix:semicolon
DECL|struct|_drm_i830_copy_t
r_typedef
r_struct
id|_drm_i830_copy_t
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
DECL|typedef|drm_i830_copy_t
)brace
id|drm_i830_copy_t
suffix:semicolon
DECL|struct|drm_i830_dma
r_typedef
r_struct
id|drm_i830_dma
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
DECL|typedef|drm_i830_dma_t
)brace
id|drm_i830_dma_t
suffix:semicolon
macro_line|#endif /* _I830_DRM_H_ */
eof
