multiline_comment|/* radeon_drm.h -- Public header for the radeon driver -*- linux-c -*-&n; *&n; * Copyright 2000 Precision Insight, Inc., Cedar Park, Texas.&n; * Copyright 2000 VA Linux Systems, Inc., Fremont, California.&n; * Copyright 2002 Tungsten Graphics, Inc., Cedar Park, Texas.&n; * All rights reserved.&n; *&n; * Permission is hereby granted, free of charge, to any person obtaining a&n; * copy of this software and associated documentation files (the &quot;Software&quot;),&n; * to deal in the Software without restriction, including without limitation&n; * the rights to use, copy, modify, merge, publish, distribute, sublicense,&n; * and/or sell copies of the Software, and to permit persons to whom the&n; * Software is furnished to do so, subject to the following conditions:&n; *&n; * The above copyright notice and this permission notice (including the next&n; * paragraph) shall be included in all copies or substantial portions of the&n; * Software.&n; *&n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR&n; * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n; * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL&n; * PRECISION INSIGHT AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR&n; * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,&n; * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER&n; * DEALINGS IN THE SOFTWARE.&n; *&n; * Authors:&n; *    Kevin E. Martin &lt;martin@valinux.com&gt;&n; *    Gareth Hughes &lt;gareth@valinux.com&gt;&n; *    Keith Whitwell &lt;keith@tungstengraphics.com&gt;&n; */
macro_line|#ifndef __RADEON_DRM_H__
DECL|macro|__RADEON_DRM_H__
mdefine_line|#define __RADEON_DRM_H__
multiline_comment|/* WARNING: If you change any of these defines, make sure to change the&n; * defines in the X server file (radeon_sarea.h)&n; */
macro_line|#ifndef __RADEON_SAREA_DEFINES__
DECL|macro|__RADEON_SAREA_DEFINES__
mdefine_line|#define __RADEON_SAREA_DEFINES__
multiline_comment|/* Old style state flags, required for sarea interface (1.1 and 1.2&n; * clears) and 1.2 drm_vertex2 ioctl.&n; */
DECL|macro|RADEON_UPLOAD_CONTEXT
mdefine_line|#define RADEON_UPLOAD_CONTEXT&t;&t;0x00000001
DECL|macro|RADEON_UPLOAD_VERTFMT
mdefine_line|#define RADEON_UPLOAD_VERTFMT&t;&t;0x00000002
DECL|macro|RADEON_UPLOAD_LINE
mdefine_line|#define RADEON_UPLOAD_LINE&t;&t;0x00000004
DECL|macro|RADEON_UPLOAD_BUMPMAP
mdefine_line|#define RADEON_UPLOAD_BUMPMAP&t;&t;0x00000008
DECL|macro|RADEON_UPLOAD_MASKS
mdefine_line|#define RADEON_UPLOAD_MASKS&t;&t;0x00000010
DECL|macro|RADEON_UPLOAD_VIEWPORT
mdefine_line|#define RADEON_UPLOAD_VIEWPORT&t;&t;0x00000020
DECL|macro|RADEON_UPLOAD_SETUP
mdefine_line|#define RADEON_UPLOAD_SETUP&t;&t;0x00000040
DECL|macro|RADEON_UPLOAD_TCL
mdefine_line|#define RADEON_UPLOAD_TCL&t;&t;0x00000080
DECL|macro|RADEON_UPLOAD_MISC
mdefine_line|#define RADEON_UPLOAD_MISC&t;&t;0x00000100
DECL|macro|RADEON_UPLOAD_TEX0
mdefine_line|#define RADEON_UPLOAD_TEX0&t;&t;0x00000200
DECL|macro|RADEON_UPLOAD_TEX1
mdefine_line|#define RADEON_UPLOAD_TEX1&t;&t;0x00000400
DECL|macro|RADEON_UPLOAD_TEX2
mdefine_line|#define RADEON_UPLOAD_TEX2&t;&t;0x00000800
DECL|macro|RADEON_UPLOAD_TEX0IMAGES
mdefine_line|#define RADEON_UPLOAD_TEX0IMAGES&t;0x00001000
DECL|macro|RADEON_UPLOAD_TEX1IMAGES
mdefine_line|#define RADEON_UPLOAD_TEX1IMAGES&t;0x00002000
DECL|macro|RADEON_UPLOAD_TEX2IMAGES
mdefine_line|#define RADEON_UPLOAD_TEX2IMAGES&t;0x00004000
DECL|macro|RADEON_UPLOAD_CLIPRECTS
mdefine_line|#define RADEON_UPLOAD_CLIPRECTS&t;&t;0x00008000 /* handled client-side */
DECL|macro|RADEON_REQUIRE_QUIESCENCE
mdefine_line|#define RADEON_REQUIRE_QUIESCENCE&t;0x00010000
DECL|macro|RADEON_UPLOAD_ZBIAS
mdefine_line|#define RADEON_UPLOAD_ZBIAS&t;&t;0x00020000 /* version 1.2 and newer */
DECL|macro|RADEON_UPLOAD_ALL
mdefine_line|#define RADEON_UPLOAD_ALL&t;&t;0x003effff
DECL|macro|RADEON_UPLOAD_CONTEXT_ALL
mdefine_line|#define RADEON_UPLOAD_CONTEXT_ALL       0x003e01ff
multiline_comment|/* New style per-packet identifiers for use in cmd_buffer ioctl with&n; * the RADEON_EMIT_PACKET command.  Comments relate new packets to old&n; * state bits and the packet size:&n; */
DECL|macro|RADEON_EMIT_PP_MISC
mdefine_line|#define RADEON_EMIT_PP_MISC                         0 /* context/7 */
DECL|macro|RADEON_EMIT_PP_CNTL
mdefine_line|#define RADEON_EMIT_PP_CNTL                         1 /* context/3 */
DECL|macro|RADEON_EMIT_RB3D_COLORPITCH
mdefine_line|#define RADEON_EMIT_RB3D_COLORPITCH                 2 /* context/1 */
DECL|macro|RADEON_EMIT_RE_LINE_PATTERN
mdefine_line|#define RADEON_EMIT_RE_LINE_PATTERN                 3 /* line/2 */
DECL|macro|RADEON_EMIT_SE_LINE_WIDTH
mdefine_line|#define RADEON_EMIT_SE_LINE_WIDTH                   4 /* line/1 */
DECL|macro|RADEON_EMIT_PP_LUM_MATRIX
mdefine_line|#define RADEON_EMIT_PP_LUM_MATRIX                   5 /* bumpmap/1 */
DECL|macro|RADEON_EMIT_PP_ROT_MATRIX_0
mdefine_line|#define RADEON_EMIT_PP_ROT_MATRIX_0                 6 /* bumpmap/2 */
DECL|macro|RADEON_EMIT_RB3D_STENCILREFMASK
mdefine_line|#define RADEON_EMIT_RB3D_STENCILREFMASK             7 /* masks/3 */
DECL|macro|RADEON_EMIT_SE_VPORT_XSCALE
mdefine_line|#define RADEON_EMIT_SE_VPORT_XSCALE                 8 /* viewport/6 */
DECL|macro|RADEON_EMIT_SE_CNTL
mdefine_line|#define RADEON_EMIT_SE_CNTL                         9 /* setup/2 */
DECL|macro|RADEON_EMIT_SE_CNTL_STATUS
mdefine_line|#define RADEON_EMIT_SE_CNTL_STATUS                  10 /* setup/1 */
DECL|macro|RADEON_EMIT_RE_MISC
mdefine_line|#define RADEON_EMIT_RE_MISC                         11 /* misc/1 */
DECL|macro|RADEON_EMIT_PP_TXFILTER_0
mdefine_line|#define RADEON_EMIT_PP_TXFILTER_0                   12 /* tex0/6 */
DECL|macro|RADEON_EMIT_PP_BORDER_COLOR_0
mdefine_line|#define RADEON_EMIT_PP_BORDER_COLOR_0               13 /* tex0/1 */
DECL|macro|RADEON_EMIT_PP_TXFILTER_1
mdefine_line|#define RADEON_EMIT_PP_TXFILTER_1                   14 /* tex1/6 */
DECL|macro|RADEON_EMIT_PP_BORDER_COLOR_1
mdefine_line|#define RADEON_EMIT_PP_BORDER_COLOR_1               15 /* tex1/1 */
DECL|macro|RADEON_EMIT_PP_TXFILTER_2
mdefine_line|#define RADEON_EMIT_PP_TXFILTER_2                   16 /* tex2/6 */
DECL|macro|RADEON_EMIT_PP_BORDER_COLOR_2
mdefine_line|#define RADEON_EMIT_PP_BORDER_COLOR_2               17 /* tex2/1 */
DECL|macro|RADEON_EMIT_SE_ZBIAS_FACTOR
mdefine_line|#define RADEON_EMIT_SE_ZBIAS_FACTOR                 18 /* zbias/2 */
DECL|macro|RADEON_EMIT_SE_TCL_OUTPUT_VTX_FMT
mdefine_line|#define RADEON_EMIT_SE_TCL_OUTPUT_VTX_FMT           19 /* tcl/11 */
DECL|macro|RADEON_EMIT_SE_TCL_MATERIAL_EMMISSIVE_RED
mdefine_line|#define RADEON_EMIT_SE_TCL_MATERIAL_EMMISSIVE_RED   20 /* material/17 */
DECL|macro|R200_EMIT_PP_TXCBLEND_0
mdefine_line|#define R200_EMIT_PP_TXCBLEND_0                     21 /* tex0/4 */
DECL|macro|R200_EMIT_PP_TXCBLEND_1
mdefine_line|#define R200_EMIT_PP_TXCBLEND_1                     22 /* tex1/4 */
DECL|macro|R200_EMIT_PP_TXCBLEND_2
mdefine_line|#define R200_EMIT_PP_TXCBLEND_2                     23 /* tex2/4 */
DECL|macro|R200_EMIT_PP_TXCBLEND_3
mdefine_line|#define R200_EMIT_PP_TXCBLEND_3                     24 /* tex3/4 */
DECL|macro|R200_EMIT_PP_TXCBLEND_4
mdefine_line|#define R200_EMIT_PP_TXCBLEND_4                     25 /* tex4/4 */
DECL|macro|R200_EMIT_PP_TXCBLEND_5
mdefine_line|#define R200_EMIT_PP_TXCBLEND_5                     26 /* tex5/4 */
DECL|macro|R200_EMIT_PP_TXCBLEND_6
mdefine_line|#define R200_EMIT_PP_TXCBLEND_6                     27 /* /4 */
DECL|macro|R200_EMIT_PP_TXCBLEND_7
mdefine_line|#define R200_EMIT_PP_TXCBLEND_7                     28 /* /4 */
DECL|macro|R200_EMIT_TCL_LIGHT_MODEL_CTL_0
mdefine_line|#define R200_EMIT_TCL_LIGHT_MODEL_CTL_0             29 /* tcl/7 */
DECL|macro|R200_EMIT_TFACTOR_0
mdefine_line|#define R200_EMIT_TFACTOR_0                         30 /* tf/7 */
DECL|macro|R200_EMIT_VTX_FMT_0
mdefine_line|#define R200_EMIT_VTX_FMT_0                         31 /* vtx/5 */
DECL|macro|R200_EMIT_VAP_CTL
mdefine_line|#define R200_EMIT_VAP_CTL                           32 /* vap/1 */
DECL|macro|R200_EMIT_MATRIX_SELECT_0
mdefine_line|#define R200_EMIT_MATRIX_SELECT_0                   33 /* msl/5 */
DECL|macro|R200_EMIT_TEX_PROC_CTL_2
mdefine_line|#define R200_EMIT_TEX_PROC_CTL_2                    34 /* tcg/5 */
DECL|macro|R200_EMIT_TCL_UCP_VERT_BLEND_CTL
mdefine_line|#define R200_EMIT_TCL_UCP_VERT_BLEND_CTL            35 /* tcl/1 */
DECL|macro|R200_EMIT_PP_TXFILTER_0
mdefine_line|#define R200_EMIT_PP_TXFILTER_0                     36 /* tex0/6 */
DECL|macro|R200_EMIT_PP_TXFILTER_1
mdefine_line|#define R200_EMIT_PP_TXFILTER_1                     37 /* tex1/6 */
DECL|macro|R200_EMIT_PP_TXFILTER_2
mdefine_line|#define R200_EMIT_PP_TXFILTER_2                     38 /* tex2/6 */
DECL|macro|R200_EMIT_PP_TXFILTER_3
mdefine_line|#define R200_EMIT_PP_TXFILTER_3                     39 /* tex3/6 */
DECL|macro|R200_EMIT_PP_TXFILTER_4
mdefine_line|#define R200_EMIT_PP_TXFILTER_4                     40 /* tex4/6 */
DECL|macro|R200_EMIT_PP_TXFILTER_5
mdefine_line|#define R200_EMIT_PP_TXFILTER_5                     41 /* tex5/6 */
DECL|macro|R200_EMIT_PP_TXOFFSET_0
mdefine_line|#define R200_EMIT_PP_TXOFFSET_0                     42 /* tex0/1 */
DECL|macro|R200_EMIT_PP_TXOFFSET_1
mdefine_line|#define R200_EMIT_PP_TXOFFSET_1                     43 /* tex1/1 */
DECL|macro|R200_EMIT_PP_TXOFFSET_2
mdefine_line|#define R200_EMIT_PP_TXOFFSET_2                     44 /* tex2/1 */
DECL|macro|R200_EMIT_PP_TXOFFSET_3
mdefine_line|#define R200_EMIT_PP_TXOFFSET_3                     45 /* tex3/1 */
DECL|macro|R200_EMIT_PP_TXOFFSET_4
mdefine_line|#define R200_EMIT_PP_TXOFFSET_4                     46 /* tex4/1 */
DECL|macro|R200_EMIT_PP_TXOFFSET_5
mdefine_line|#define R200_EMIT_PP_TXOFFSET_5                     47 /* tex5/1 */
DECL|macro|R200_EMIT_VTE_CNTL
mdefine_line|#define R200_EMIT_VTE_CNTL                          48 /* vte/1 */
DECL|macro|R200_EMIT_OUTPUT_VTX_COMP_SEL
mdefine_line|#define R200_EMIT_OUTPUT_VTX_COMP_SEL               49 /* vtx/1 */
DECL|macro|R200_EMIT_PP_TAM_DEBUG3
mdefine_line|#define R200_EMIT_PP_TAM_DEBUG3                     50 /* tam/1 */
DECL|macro|R200_EMIT_PP_CNTL_X
mdefine_line|#define R200_EMIT_PP_CNTL_X                         51 /* cst/1 */
DECL|macro|R200_EMIT_RB3D_DEPTHXY_OFFSET
mdefine_line|#define R200_EMIT_RB3D_DEPTHXY_OFFSET               52 /* cst/1 */
DECL|macro|R200_EMIT_RE_AUX_SCISSOR_CNTL
mdefine_line|#define R200_EMIT_RE_AUX_SCISSOR_CNTL               53 /* cst/1 */
DECL|macro|R200_EMIT_RE_SCISSOR_TL_0
mdefine_line|#define R200_EMIT_RE_SCISSOR_TL_0                   54 /* cst/2 */
DECL|macro|R200_EMIT_RE_SCISSOR_TL_1
mdefine_line|#define R200_EMIT_RE_SCISSOR_TL_1                   55 /* cst/2 */
DECL|macro|R200_EMIT_RE_SCISSOR_TL_2
mdefine_line|#define R200_EMIT_RE_SCISSOR_TL_2                   56 /* cst/2 */
DECL|macro|R200_EMIT_SE_VAP_CNTL_STATUS
mdefine_line|#define R200_EMIT_SE_VAP_CNTL_STATUS                57 /* cst/1 */
DECL|macro|R200_EMIT_SE_VTX_STATE_CNTL
mdefine_line|#define R200_EMIT_SE_VTX_STATE_CNTL                 58 /* cst/1 */
DECL|macro|R200_EMIT_RE_POINTSIZE
mdefine_line|#define R200_EMIT_RE_POINTSIZE                      59 /* cst/1 */
DECL|macro|R200_EMIT_TCL_INPUT_VTX_VECTOR_ADDR_0
mdefine_line|#define R200_EMIT_TCL_INPUT_VTX_VECTOR_ADDR_0       60 /* cst/4 */
DECL|macro|R200_EMIT_PP_CUBIC_FACES_0
mdefine_line|#define R200_EMIT_PP_CUBIC_FACES_0                  61
DECL|macro|R200_EMIT_PP_CUBIC_OFFSETS_0
mdefine_line|#define R200_EMIT_PP_CUBIC_OFFSETS_0                62
DECL|macro|R200_EMIT_PP_CUBIC_FACES_1
mdefine_line|#define R200_EMIT_PP_CUBIC_FACES_1                  63
DECL|macro|R200_EMIT_PP_CUBIC_OFFSETS_1
mdefine_line|#define R200_EMIT_PP_CUBIC_OFFSETS_1                64
DECL|macro|R200_EMIT_PP_CUBIC_FACES_2
mdefine_line|#define R200_EMIT_PP_CUBIC_FACES_2                  65
DECL|macro|R200_EMIT_PP_CUBIC_OFFSETS_2
mdefine_line|#define R200_EMIT_PP_CUBIC_OFFSETS_2                66
DECL|macro|R200_EMIT_PP_CUBIC_FACES_3
mdefine_line|#define R200_EMIT_PP_CUBIC_FACES_3                  67
DECL|macro|R200_EMIT_PP_CUBIC_OFFSETS_3
mdefine_line|#define R200_EMIT_PP_CUBIC_OFFSETS_3                68
DECL|macro|R200_EMIT_PP_CUBIC_FACES_4
mdefine_line|#define R200_EMIT_PP_CUBIC_FACES_4                  69
DECL|macro|R200_EMIT_PP_CUBIC_OFFSETS_4
mdefine_line|#define R200_EMIT_PP_CUBIC_OFFSETS_4                70
DECL|macro|R200_EMIT_PP_CUBIC_FACES_5
mdefine_line|#define R200_EMIT_PP_CUBIC_FACES_5                  71
DECL|macro|R200_EMIT_PP_CUBIC_OFFSETS_5
mdefine_line|#define R200_EMIT_PP_CUBIC_OFFSETS_5                72
DECL|macro|RADEON_EMIT_PP_TEX_SIZE_0
mdefine_line|#define RADEON_EMIT_PP_TEX_SIZE_0                   73
DECL|macro|RADEON_EMIT_PP_TEX_SIZE_1
mdefine_line|#define RADEON_EMIT_PP_TEX_SIZE_1                   74
DECL|macro|RADEON_EMIT_PP_TEX_SIZE_2
mdefine_line|#define RADEON_EMIT_PP_TEX_SIZE_2                   75
DECL|macro|RADEON_MAX_STATE_PACKETS
mdefine_line|#define RADEON_MAX_STATE_PACKETS                    76
multiline_comment|/* Commands understood by cmd_buffer ioctl.  More can be added but&n; * obviously these can&squot;t be removed or changed:&n; */
DECL|macro|RADEON_CMD_PACKET
mdefine_line|#define RADEON_CMD_PACKET      1 /* emit one of the register packets above */
DECL|macro|RADEON_CMD_SCALARS
mdefine_line|#define RADEON_CMD_SCALARS     2 /* emit scalar data */
DECL|macro|RADEON_CMD_VECTORS
mdefine_line|#define RADEON_CMD_VECTORS     3 /* emit vector data */
DECL|macro|RADEON_CMD_DMA_DISCARD
mdefine_line|#define RADEON_CMD_DMA_DISCARD 4 /* discard current dma buf */
DECL|macro|RADEON_CMD_PACKET3
mdefine_line|#define RADEON_CMD_PACKET3     5 /* emit hw packet */
DECL|macro|RADEON_CMD_PACKET3_CLIP
mdefine_line|#define RADEON_CMD_PACKET3_CLIP 6 /* emit hw packet wrapped in cliprects */
DECL|macro|RADEON_CMD_SCALARS2
mdefine_line|#define RADEON_CMD_SCALARS2     7 /* r200 stopgap */
DECL|macro|RADEON_CMD_WAIT
mdefine_line|#define RADEON_CMD_WAIT         8 /* emit hw wait commands -- note:&n;&t;&t;&t;&t;   *  doesn&squot;t make the cpu wait, just&n;&t;&t;&t;&t;   *  the graphics hardware */
r_typedef
r_union
(brace
DECL|member|i
r_int
id|i
suffix:semicolon
r_struct
(brace
DECL|member|cmd_type
DECL|member|pad0
DECL|member|pad1
DECL|member|pad2
r_int
r_char
id|cmd_type
comma
id|pad0
comma
id|pad1
comma
id|pad2
suffix:semicolon
DECL|member|header
)brace
id|header
suffix:semicolon
r_struct
(brace
DECL|member|cmd_type
DECL|member|packet_id
DECL|member|pad0
DECL|member|pad1
r_int
r_char
id|cmd_type
comma
id|packet_id
comma
id|pad0
comma
id|pad1
suffix:semicolon
DECL|member|packet
)brace
id|packet
suffix:semicolon
r_struct
(brace
DECL|member|cmd_type
DECL|member|offset
DECL|member|stride
DECL|member|count
r_int
r_char
id|cmd_type
comma
id|offset
comma
id|stride
comma
id|count
suffix:semicolon
DECL|member|scalars
)brace
id|scalars
suffix:semicolon
r_struct
(brace
DECL|member|cmd_type
DECL|member|offset
DECL|member|stride
DECL|member|count
r_int
r_char
id|cmd_type
comma
id|offset
comma
id|stride
comma
id|count
suffix:semicolon
DECL|member|vectors
)brace
id|vectors
suffix:semicolon
r_struct
(brace
DECL|member|cmd_type
DECL|member|buf_idx
DECL|member|pad0
DECL|member|pad1
r_int
r_char
id|cmd_type
comma
id|buf_idx
comma
id|pad0
comma
id|pad1
suffix:semicolon
DECL|member|dma
)brace
id|dma
suffix:semicolon
r_struct
(brace
DECL|member|cmd_type
DECL|member|flags
DECL|member|pad0
DECL|member|pad1
r_int
r_char
id|cmd_type
comma
id|flags
comma
id|pad0
comma
id|pad1
suffix:semicolon
DECL|member|wait
)brace
id|wait
suffix:semicolon
DECL|typedef|drm_radeon_cmd_header_t
)brace
id|drm_radeon_cmd_header_t
suffix:semicolon
DECL|macro|RADEON_WAIT_2D
mdefine_line|#define RADEON_WAIT_2D  0x1
DECL|macro|RADEON_WAIT_3D
mdefine_line|#define RADEON_WAIT_3D  0x2
DECL|macro|RADEON_FRONT
mdefine_line|#define RADEON_FRONT&t;&t;&t;0x1
DECL|macro|RADEON_BACK
mdefine_line|#define RADEON_BACK&t;&t;&t;0x2
DECL|macro|RADEON_DEPTH
mdefine_line|#define RADEON_DEPTH&t;&t;&t;0x4
DECL|macro|RADEON_STENCIL
mdefine_line|#define RADEON_STENCIL                  0x8
multiline_comment|/* Primitive types&n; */
DECL|macro|RADEON_POINTS
mdefine_line|#define RADEON_POINTS&t;&t;&t;0x1
DECL|macro|RADEON_LINES
mdefine_line|#define RADEON_LINES&t;&t;&t;0x2
DECL|macro|RADEON_LINE_STRIP
mdefine_line|#define RADEON_LINE_STRIP&t;&t;0x3
DECL|macro|RADEON_TRIANGLES
mdefine_line|#define RADEON_TRIANGLES&t;&t;0x4
DECL|macro|RADEON_TRIANGLE_FAN
mdefine_line|#define RADEON_TRIANGLE_FAN&t;&t;0x5
DECL|macro|RADEON_TRIANGLE_STRIP
mdefine_line|#define RADEON_TRIANGLE_STRIP&t;&t;0x6
multiline_comment|/* Vertex/indirect buffer size&n; */
DECL|macro|RADEON_BUFFER_SIZE
mdefine_line|#define RADEON_BUFFER_SIZE&t;&t;65536
multiline_comment|/* Byte offsets for indirect buffer data&n; */
DECL|macro|RADEON_INDEX_PRIM_OFFSET
mdefine_line|#define RADEON_INDEX_PRIM_OFFSET&t;20
DECL|macro|RADEON_SCRATCH_REG_OFFSET
mdefine_line|#define RADEON_SCRATCH_REG_OFFSET&t;32
DECL|macro|RADEON_NR_SAREA_CLIPRECTS
mdefine_line|#define RADEON_NR_SAREA_CLIPRECTS&t;12
multiline_comment|/* There are 2 heaps (local/GART).  Each region within a heap is a&n; * minimum of 64k, and there are at most 64 of them per heap.&n; */
DECL|macro|RADEON_LOCAL_TEX_HEAP
mdefine_line|#define RADEON_LOCAL_TEX_HEAP&t;&t;0
DECL|macro|RADEON_GART_TEX_HEAP
mdefine_line|#define RADEON_GART_TEX_HEAP&t;&t;1
DECL|macro|RADEON_NR_TEX_HEAPS
mdefine_line|#define RADEON_NR_TEX_HEAPS&t;&t;2
DECL|macro|RADEON_NR_TEX_REGIONS
mdefine_line|#define RADEON_NR_TEX_REGIONS&t;&t;64
DECL|macro|RADEON_LOG_TEX_GRANULARITY
mdefine_line|#define RADEON_LOG_TEX_GRANULARITY&t;16
DECL|macro|RADEON_MAX_TEXTURE_LEVELS
mdefine_line|#define RADEON_MAX_TEXTURE_LEVELS&t;12
DECL|macro|RADEON_MAX_TEXTURE_UNITS
mdefine_line|#define RADEON_MAX_TEXTURE_UNITS&t;3
macro_line|#endif /* __RADEON_SAREA_DEFINES__ */
r_typedef
r_struct
(brace
DECL|member|red
r_int
r_int
id|red
suffix:semicolon
DECL|member|green
r_int
r_int
id|green
suffix:semicolon
DECL|member|blue
r_int
r_int
id|blue
suffix:semicolon
DECL|member|alpha
r_int
r_int
id|alpha
suffix:semicolon
DECL|typedef|radeon_color_regs_t
)brace
id|radeon_color_regs_t
suffix:semicolon
r_typedef
r_struct
(brace
multiline_comment|/* Context state */
DECL|member|pp_misc
r_int
r_int
id|pp_misc
suffix:semicolon
multiline_comment|/* 0x1c14 */
DECL|member|pp_fog_color
r_int
r_int
id|pp_fog_color
suffix:semicolon
DECL|member|re_solid_color
r_int
r_int
id|re_solid_color
suffix:semicolon
DECL|member|rb3d_blendcntl
r_int
r_int
id|rb3d_blendcntl
suffix:semicolon
DECL|member|rb3d_depthoffset
r_int
r_int
id|rb3d_depthoffset
suffix:semicolon
DECL|member|rb3d_depthpitch
r_int
r_int
id|rb3d_depthpitch
suffix:semicolon
DECL|member|rb3d_zstencilcntl
r_int
r_int
id|rb3d_zstencilcntl
suffix:semicolon
DECL|member|pp_cntl
r_int
r_int
id|pp_cntl
suffix:semicolon
multiline_comment|/* 0x1c38 */
DECL|member|rb3d_cntl
r_int
r_int
id|rb3d_cntl
suffix:semicolon
DECL|member|rb3d_coloroffset
r_int
r_int
id|rb3d_coloroffset
suffix:semicolon
DECL|member|re_width_height
r_int
r_int
id|re_width_height
suffix:semicolon
DECL|member|rb3d_colorpitch
r_int
r_int
id|rb3d_colorpitch
suffix:semicolon
DECL|member|se_cntl
r_int
r_int
id|se_cntl
suffix:semicolon
multiline_comment|/* Vertex format state */
DECL|member|se_coord_fmt
r_int
r_int
id|se_coord_fmt
suffix:semicolon
multiline_comment|/* 0x1c50 */
multiline_comment|/* Line state */
DECL|member|re_line_pattern
r_int
r_int
id|re_line_pattern
suffix:semicolon
multiline_comment|/* 0x1cd0 */
DECL|member|re_line_state
r_int
r_int
id|re_line_state
suffix:semicolon
DECL|member|se_line_width
r_int
r_int
id|se_line_width
suffix:semicolon
multiline_comment|/* 0x1db8 */
multiline_comment|/* Bumpmap state */
DECL|member|pp_lum_matrix
r_int
r_int
id|pp_lum_matrix
suffix:semicolon
multiline_comment|/* 0x1d00 */
DECL|member|pp_rot_matrix_0
r_int
r_int
id|pp_rot_matrix_0
suffix:semicolon
multiline_comment|/* 0x1d58 */
DECL|member|pp_rot_matrix_1
r_int
r_int
id|pp_rot_matrix_1
suffix:semicolon
multiline_comment|/* Mask state */
DECL|member|rb3d_stencilrefmask
r_int
r_int
id|rb3d_stencilrefmask
suffix:semicolon
multiline_comment|/* 0x1d7c */
DECL|member|rb3d_ropcntl
r_int
r_int
id|rb3d_ropcntl
suffix:semicolon
DECL|member|rb3d_planemask
r_int
r_int
id|rb3d_planemask
suffix:semicolon
multiline_comment|/* Viewport state */
DECL|member|se_vport_xscale
r_int
r_int
id|se_vport_xscale
suffix:semicolon
multiline_comment|/* 0x1d98 */
DECL|member|se_vport_xoffset
r_int
r_int
id|se_vport_xoffset
suffix:semicolon
DECL|member|se_vport_yscale
r_int
r_int
id|se_vport_yscale
suffix:semicolon
DECL|member|se_vport_yoffset
r_int
r_int
id|se_vport_yoffset
suffix:semicolon
DECL|member|se_vport_zscale
r_int
r_int
id|se_vport_zscale
suffix:semicolon
DECL|member|se_vport_zoffset
r_int
r_int
id|se_vport_zoffset
suffix:semicolon
multiline_comment|/* Setup state */
DECL|member|se_cntl_status
r_int
r_int
id|se_cntl_status
suffix:semicolon
multiline_comment|/* 0x2140 */
multiline_comment|/* Misc state */
DECL|member|re_top_left
r_int
r_int
id|re_top_left
suffix:semicolon
multiline_comment|/* 0x26c0 */
DECL|member|re_misc
r_int
r_int
id|re_misc
suffix:semicolon
DECL|typedef|drm_radeon_context_regs_t
)brace
id|drm_radeon_context_regs_t
suffix:semicolon
r_typedef
r_struct
(brace
multiline_comment|/* Zbias state */
DECL|member|se_zbias_factor
r_int
r_int
id|se_zbias_factor
suffix:semicolon
multiline_comment|/* 0x1dac */
DECL|member|se_zbias_constant
r_int
r_int
id|se_zbias_constant
suffix:semicolon
DECL|typedef|drm_radeon_context2_regs_t
)brace
id|drm_radeon_context2_regs_t
suffix:semicolon
multiline_comment|/* Setup registers for each texture unit&n; */
r_typedef
r_struct
(brace
DECL|member|pp_txfilter
r_int
r_int
id|pp_txfilter
suffix:semicolon
DECL|member|pp_txformat
r_int
r_int
id|pp_txformat
suffix:semicolon
DECL|member|pp_txoffset
r_int
r_int
id|pp_txoffset
suffix:semicolon
DECL|member|pp_txcblend
r_int
r_int
id|pp_txcblend
suffix:semicolon
DECL|member|pp_txablend
r_int
r_int
id|pp_txablend
suffix:semicolon
DECL|member|pp_tfactor
r_int
r_int
id|pp_tfactor
suffix:semicolon
DECL|member|pp_border_color
r_int
r_int
id|pp_border_color
suffix:semicolon
DECL|typedef|drm_radeon_texture_regs_t
)brace
id|drm_radeon_texture_regs_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|start
r_int
r_int
id|start
suffix:semicolon
DECL|member|finish
r_int
r_int
id|finish
suffix:semicolon
DECL|member|prim
r_int
r_int
id|prim
suffix:colon
l_int|8
suffix:semicolon
DECL|member|stateidx
r_int
r_int
id|stateidx
suffix:colon
l_int|8
suffix:semicolon
DECL|member|numverts
r_int
r_int
id|numverts
suffix:colon
l_int|16
suffix:semicolon
multiline_comment|/* overloaded as offset/64 for elt prims */
DECL|member|vc_format
r_int
r_int
id|vc_format
suffix:semicolon
multiline_comment|/* vertex format */
DECL|typedef|drm_radeon_prim_t
)brace
id|drm_radeon_prim_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|context
id|drm_radeon_context_regs_t
id|context
suffix:semicolon
DECL|member|tex
id|drm_radeon_texture_regs_t
id|tex
(braket
id|RADEON_MAX_TEXTURE_UNITS
)braket
suffix:semicolon
DECL|member|context2
id|drm_radeon_context2_regs_t
id|context2
suffix:semicolon
DECL|member|dirty
r_int
r_int
id|dirty
suffix:semicolon
DECL|typedef|drm_radeon_state_t
)brace
id|drm_radeon_state_t
suffix:semicolon
r_typedef
r_struct
(brace
multiline_comment|/* The channel for communication of state information to the&n;&t; * kernel on firing a vertex buffer with either of the&n;&t; * obsoleted vertex/index ioctls.&n;&t; */
DECL|member|context_state
id|drm_radeon_context_regs_t
id|context_state
suffix:semicolon
DECL|member|tex_state
id|drm_radeon_texture_regs_t
id|tex_state
(braket
id|RADEON_MAX_TEXTURE_UNITS
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
id|RADEON_NR_SAREA_CLIPRECTS
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
DECL|member|last_clear
r_int
r_int
id|last_clear
suffix:semicolon
DECL|member|tex_list
id|drm_tex_region_t
id|tex_list
(braket
id|RADEON_NR_TEX_HEAPS
)braket
(braket
id|RADEON_NR_TEX_REGIONS
op_plus
l_int|1
)braket
suffix:semicolon
DECL|member|tex_age
r_int
r_int
id|tex_age
(braket
id|RADEON_NR_TEX_HEAPS
)braket
suffix:semicolon
DECL|member|ctx_owner
r_int
id|ctx_owner
suffix:semicolon
DECL|member|pfState
r_int
id|pfState
suffix:semicolon
multiline_comment|/* number of 3d windows (0,1,2ormore) */
DECL|member|pfCurrentPage
r_int
id|pfCurrentPage
suffix:semicolon
multiline_comment|/* which buffer is being displayed? */
DECL|member|crtc2_base
r_int
id|crtc2_base
suffix:semicolon
multiline_comment|/* CRTC2 frame offset */
DECL|typedef|drm_radeon_sarea_t
)brace
id|drm_radeon_sarea_t
suffix:semicolon
multiline_comment|/* WARNING: If you change any of these defines, make sure to change the&n; * defines in the Xserver file (xf86drmRadeon.h)&n; *&n; * KW: actually it&squot;s illegal to change any of this (backwards compatibility).&n; */
multiline_comment|/* Radeon specific ioctls&n; * The device specific ioctl range is 0x40 to 0x79.&n; */
DECL|macro|DRM_IOCTL_RADEON_CP_INIT
mdefine_line|#define DRM_IOCTL_RADEON_CP_INIT    DRM_IOW( 0x40, drm_radeon_init_t)
DECL|macro|DRM_IOCTL_RADEON_CP_START
mdefine_line|#define DRM_IOCTL_RADEON_CP_START   DRM_IO(  0x41)
DECL|macro|DRM_IOCTL_RADEON_CP_STOP
mdefine_line|#define DRM_IOCTL_RADEON_CP_STOP    DRM_IOW( 0x42, drm_radeon_cp_stop_t)
DECL|macro|DRM_IOCTL_RADEON_CP_RESET
mdefine_line|#define DRM_IOCTL_RADEON_CP_RESET   DRM_IO(  0x43)
DECL|macro|DRM_IOCTL_RADEON_CP_IDLE
mdefine_line|#define DRM_IOCTL_RADEON_CP_IDLE    DRM_IO(  0x44)
DECL|macro|DRM_IOCTL_RADEON_RESET
mdefine_line|#define DRM_IOCTL_RADEON_RESET      DRM_IO(  0x45)
DECL|macro|DRM_IOCTL_RADEON_FULLSCREEN
mdefine_line|#define DRM_IOCTL_RADEON_FULLSCREEN DRM_IOW( 0x46, drm_radeon_fullscreen_t)
DECL|macro|DRM_IOCTL_RADEON_SWAP
mdefine_line|#define DRM_IOCTL_RADEON_SWAP       DRM_IO(  0x47)
DECL|macro|DRM_IOCTL_RADEON_CLEAR
mdefine_line|#define DRM_IOCTL_RADEON_CLEAR      DRM_IOW( 0x48, drm_radeon_clear_t)
DECL|macro|DRM_IOCTL_RADEON_VERTEX
mdefine_line|#define DRM_IOCTL_RADEON_VERTEX     DRM_IOW( 0x49, drm_radeon_vertex_t)
DECL|macro|DRM_IOCTL_RADEON_INDICES
mdefine_line|#define DRM_IOCTL_RADEON_INDICES    DRM_IOW( 0x4a, drm_radeon_indices_t)
DECL|macro|DRM_IOCTL_RADEON_STIPPLE
mdefine_line|#define DRM_IOCTL_RADEON_STIPPLE    DRM_IOW( 0x4c, drm_radeon_stipple_t)
DECL|macro|DRM_IOCTL_RADEON_INDIRECT
mdefine_line|#define DRM_IOCTL_RADEON_INDIRECT   DRM_IOWR(0x4d, drm_radeon_indirect_t)
DECL|macro|DRM_IOCTL_RADEON_TEXTURE
mdefine_line|#define DRM_IOCTL_RADEON_TEXTURE    DRM_IOWR(0x4e, drm_radeon_texture_t)
DECL|macro|DRM_IOCTL_RADEON_VERTEX2
mdefine_line|#define DRM_IOCTL_RADEON_VERTEX2    DRM_IOW( 0x4f, drm_radeon_vertex2_t)
DECL|macro|DRM_IOCTL_RADEON_CMDBUF
mdefine_line|#define DRM_IOCTL_RADEON_CMDBUF     DRM_IOW( 0x50, drm_radeon_cmd_buffer_t)
DECL|macro|DRM_IOCTL_RADEON_GETPARAM
mdefine_line|#define DRM_IOCTL_RADEON_GETPARAM   DRM_IOWR(0x51, drm_radeon_getparam_t)
DECL|macro|DRM_IOCTL_RADEON_FLIP
mdefine_line|#define DRM_IOCTL_RADEON_FLIP&t;    DRM_IO(  0x52)
DECL|macro|DRM_IOCTL_RADEON_ALLOC
mdefine_line|#define DRM_IOCTL_RADEON_ALLOC      DRM_IOWR( 0x53, drm_radeon_mem_alloc_t)
DECL|macro|DRM_IOCTL_RADEON_FREE
mdefine_line|#define DRM_IOCTL_RADEON_FREE       DRM_IOW( 0x54, drm_radeon_mem_free_t)
DECL|macro|DRM_IOCTL_RADEON_INIT_HEAP
mdefine_line|#define DRM_IOCTL_RADEON_INIT_HEAP  DRM_IOW( 0x55, drm_radeon_mem_init_heap_t)
DECL|macro|DRM_IOCTL_RADEON_IRQ_EMIT
mdefine_line|#define DRM_IOCTL_RADEON_IRQ_EMIT   DRM_IOWR( 0x56, drm_radeon_irq_emit_t)
DECL|macro|DRM_IOCTL_RADEON_IRQ_WAIT
mdefine_line|#define DRM_IOCTL_RADEON_IRQ_WAIT   DRM_IOW( 0x57, drm_radeon_irq_wait_t)
multiline_comment|/* added by Charl P. Botha - see radeon_cp.c for details */
DECL|macro|DRM_IOCTL_RADEON_CP_RESUME
mdefine_line|#define DRM_IOCTL_RADEON_CP_RESUME  DRM_IO(0x58)
DECL|macro|DRM_IOCTL_RADEON_SETPARAM
mdefine_line|#define DRM_IOCTL_RADEON_SETPARAM   DRM_IOW( 0x59, drm_radeon_setparam_t)
DECL|struct|drm_radeon_init
r_typedef
r_struct
id|drm_radeon_init
(brace
r_enum
(brace
DECL|enumerator|RADEON_INIT_CP
id|RADEON_INIT_CP
op_assign
l_int|0x01
comma
DECL|enumerator|RADEON_CLEANUP_CP
id|RADEON_CLEANUP_CP
op_assign
l_int|0x02
comma
DECL|enumerator|RADEON_INIT_R200_CP
id|RADEON_INIT_R200_CP
op_assign
l_int|0x03
DECL|member|func
)brace
id|func
suffix:semicolon
DECL|member|sarea_priv_offset
r_int
r_int
id|sarea_priv_offset
suffix:semicolon
DECL|member|is_pci
r_int
id|is_pci
suffix:semicolon
DECL|member|cp_mode
r_int
id|cp_mode
suffix:semicolon
DECL|member|gart_size
r_int
id|gart_size
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
DECL|member|gart_textures_offset
r_int
r_int
id|gart_textures_offset
suffix:semicolon
DECL|typedef|drm_radeon_init_t
)brace
id|drm_radeon_init_t
suffix:semicolon
DECL|struct|drm_radeon_cp_stop
r_typedef
r_struct
id|drm_radeon_cp_stop
(brace
DECL|member|flush
r_int
id|flush
suffix:semicolon
DECL|member|idle
r_int
id|idle
suffix:semicolon
DECL|typedef|drm_radeon_cp_stop_t
)brace
id|drm_radeon_cp_stop_t
suffix:semicolon
DECL|struct|drm_radeon_fullscreen
r_typedef
r_struct
id|drm_radeon_fullscreen
(brace
r_enum
(brace
DECL|enumerator|RADEON_INIT_FULLSCREEN
id|RADEON_INIT_FULLSCREEN
op_assign
l_int|0x01
comma
DECL|enumerator|RADEON_CLEANUP_FULLSCREEN
id|RADEON_CLEANUP_FULLSCREEN
op_assign
l_int|0x02
DECL|member|func
)brace
id|func
suffix:semicolon
DECL|typedef|drm_radeon_fullscreen_t
)brace
id|drm_radeon_fullscreen_t
suffix:semicolon
DECL|macro|CLEAR_X1
mdefine_line|#define CLEAR_X1&t;0
DECL|macro|CLEAR_Y1
mdefine_line|#define CLEAR_Y1&t;1
DECL|macro|CLEAR_X2
mdefine_line|#define CLEAR_X2&t;2
DECL|macro|CLEAR_Y2
mdefine_line|#define CLEAR_Y2&t;3
DECL|macro|CLEAR_DEPTH
mdefine_line|#define CLEAR_DEPTH&t;4
DECL|union|drm_radeon_clear_rect
r_typedef
r_union
id|drm_radeon_clear_rect
(brace
DECL|member|f
r_float
id|f
(braket
l_int|5
)braket
suffix:semicolon
DECL|member|ui
r_int
r_int
id|ui
(braket
l_int|5
)braket
suffix:semicolon
DECL|typedef|drm_radeon_clear_rect_t
)brace
id|drm_radeon_clear_rect_t
suffix:semicolon
DECL|struct|drm_radeon_clear
r_typedef
r_struct
id|drm_radeon_clear
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
multiline_comment|/* misnamed field:  should be stencil */
DECL|member|depth_boxes
id|drm_radeon_clear_rect_t
op_star
id|depth_boxes
suffix:semicolon
DECL|typedef|drm_radeon_clear_t
)brace
id|drm_radeon_clear_t
suffix:semicolon
DECL|struct|drm_radeon_vertex
r_typedef
r_struct
id|drm_radeon_vertex
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
DECL|typedef|drm_radeon_vertex_t
)brace
id|drm_radeon_vertex_t
suffix:semicolon
DECL|struct|drm_radeon_indices
r_typedef
r_struct
id|drm_radeon_indices
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
DECL|typedef|drm_radeon_indices_t
)brace
id|drm_radeon_indices_t
suffix:semicolon
multiline_comment|/* v1.2 - obsoletes drm_radeon_vertex and drm_radeon_indices&n; *      - allows multiple primitives and state changes in a single ioctl&n; *      - supports driver change to emit native primitives&n; */
DECL|struct|drm_radeon_vertex2
r_typedef
r_struct
id|drm_radeon_vertex2
(brace
DECL|member|idx
r_int
id|idx
suffix:semicolon
multiline_comment|/* Index of vertex buffer */
DECL|member|discard
r_int
id|discard
suffix:semicolon
multiline_comment|/* Client finished with buffer? */
DECL|member|nr_states
r_int
id|nr_states
suffix:semicolon
DECL|member|state
id|drm_radeon_state_t
op_star
id|state
suffix:semicolon
DECL|member|nr_prims
r_int
id|nr_prims
suffix:semicolon
DECL|member|prim
id|drm_radeon_prim_t
op_star
id|prim
suffix:semicolon
DECL|typedef|drm_radeon_vertex2_t
)brace
id|drm_radeon_vertex2_t
suffix:semicolon
multiline_comment|/* v1.3 - obsoletes drm_radeon_vertex2&n; *      - allows arbitarily large cliprect list &n; *      - allows updating of tcl packet, vector and scalar state&n; *      - allows memory-efficient description of state updates&n; *      - allows state to be emitted without a primitive &n; *           (for clears, ctx switches)&n; *      - allows more than one dma buffer to be referenced per ioctl&n; *      - supports tcl driver&n; *      - may be extended in future versions with new cmd types, packets&n; */
DECL|struct|drm_radeon_cmd_buffer
r_typedef
r_struct
id|drm_radeon_cmd_buffer
(brace
DECL|member|bufsz
r_int
id|bufsz
suffix:semicolon
DECL|member|buf
r_char
op_star
id|buf
suffix:semicolon
DECL|member|nbox
r_int
id|nbox
suffix:semicolon
DECL|member|boxes
id|drm_clip_rect_t
op_star
id|boxes
suffix:semicolon
DECL|typedef|drm_radeon_cmd_buffer_t
)brace
id|drm_radeon_cmd_buffer_t
suffix:semicolon
DECL|struct|drm_radeon_tex_image
r_typedef
r_struct
id|drm_radeon_tex_image
(brace
DECL|member|x
DECL|member|y
r_int
r_int
id|x
comma
id|y
suffix:semicolon
multiline_comment|/* Blit coordinates */
DECL|member|width
DECL|member|height
r_int
r_int
id|width
comma
id|height
suffix:semicolon
DECL|member|data
r_const
r_void
op_star
id|data
suffix:semicolon
DECL|typedef|drm_radeon_tex_image_t
)brace
id|drm_radeon_tex_image_t
suffix:semicolon
DECL|struct|drm_radeon_texture
r_typedef
r_struct
id|drm_radeon_texture
(brace
DECL|member|offset
r_int
r_int
id|offset
suffix:semicolon
DECL|member|pitch
r_int
id|pitch
suffix:semicolon
DECL|member|format
r_int
id|format
suffix:semicolon
DECL|member|width
r_int
id|width
suffix:semicolon
multiline_comment|/* Texture image coordinates */
DECL|member|height
r_int
id|height
suffix:semicolon
DECL|member|image
id|drm_radeon_tex_image_t
op_star
id|image
suffix:semicolon
DECL|typedef|drm_radeon_texture_t
)brace
id|drm_radeon_texture_t
suffix:semicolon
DECL|struct|drm_radeon_stipple
r_typedef
r_struct
id|drm_radeon_stipple
(brace
DECL|member|mask
r_int
r_int
op_star
id|mask
suffix:semicolon
DECL|typedef|drm_radeon_stipple_t
)brace
id|drm_radeon_stipple_t
suffix:semicolon
DECL|struct|drm_radeon_indirect
r_typedef
r_struct
id|drm_radeon_indirect
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
DECL|typedef|drm_radeon_indirect_t
)brace
id|drm_radeon_indirect_t
suffix:semicolon
multiline_comment|/* 1.3: An ioctl to get parameters that aren&squot;t available to the 3d&n; * client any other way.  &n; */
DECL|macro|RADEON_PARAM_GART_BUFFER_OFFSET
mdefine_line|#define RADEON_PARAM_GART_BUFFER_OFFSET    1 /* card offset of 1st GART buffer */
DECL|macro|RADEON_PARAM_LAST_FRAME
mdefine_line|#define RADEON_PARAM_LAST_FRAME            2
DECL|macro|RADEON_PARAM_LAST_DISPATCH
mdefine_line|#define RADEON_PARAM_LAST_DISPATCH         3
DECL|macro|RADEON_PARAM_LAST_CLEAR
mdefine_line|#define RADEON_PARAM_LAST_CLEAR            4
multiline_comment|/* Added with DRM version 1.6. */
DECL|macro|RADEON_PARAM_IRQ_NR
mdefine_line|#define RADEON_PARAM_IRQ_NR                5
DECL|macro|RADEON_PARAM_GART_BASE
mdefine_line|#define RADEON_PARAM_GART_BASE             6 /* card offset of GART base */
multiline_comment|/* Added with DRM version 1.8. */
DECL|macro|RADEON_PARAM_REGISTER_HANDLE
mdefine_line|#define RADEON_PARAM_REGISTER_HANDLE       7 /* for drmMap() */
DECL|macro|RADEON_PARAM_STATUS_HANDLE
mdefine_line|#define RADEON_PARAM_STATUS_HANDLE         8
DECL|macro|RADEON_PARAM_SAREA_HANDLE
mdefine_line|#define RADEON_PARAM_SAREA_HANDLE          9
DECL|macro|RADEON_PARAM_GART_TEX_HANDLE
mdefine_line|#define RADEON_PARAM_GART_TEX_HANDLE       10
DECL|macro|RADEON_PARAM_SCRATCH_OFFSET
mdefine_line|#define RADEON_PARAM_SCRATCH_OFFSET        11
DECL|struct|drm_radeon_getparam
r_typedef
r_struct
id|drm_radeon_getparam
(brace
DECL|member|param
r_int
id|param
suffix:semicolon
DECL|member|value
r_int
op_star
id|value
suffix:semicolon
DECL|typedef|drm_radeon_getparam_t
)brace
id|drm_radeon_getparam_t
suffix:semicolon
multiline_comment|/* 1.6: Set up a memory manager for regions of shared memory:&n; */
DECL|macro|RADEON_MEM_REGION_GART
mdefine_line|#define RADEON_MEM_REGION_GART 1
DECL|macro|RADEON_MEM_REGION_FB
mdefine_line|#define RADEON_MEM_REGION_FB   2
DECL|struct|drm_radeon_mem_alloc
r_typedef
r_struct
id|drm_radeon_mem_alloc
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
op_star
id|region_offset
suffix:semicolon
multiline_comment|/* offset from start of fb or GART */
DECL|typedef|drm_radeon_mem_alloc_t
)brace
id|drm_radeon_mem_alloc_t
suffix:semicolon
DECL|struct|drm_radeon_mem_free
r_typedef
r_struct
id|drm_radeon_mem_free
(brace
DECL|member|region
r_int
id|region
suffix:semicolon
DECL|member|region_offset
r_int
id|region_offset
suffix:semicolon
DECL|typedef|drm_radeon_mem_free_t
)brace
id|drm_radeon_mem_free_t
suffix:semicolon
DECL|struct|drm_radeon_mem_init_heap
r_typedef
r_struct
id|drm_radeon_mem_init_heap
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
DECL|typedef|drm_radeon_mem_init_heap_t
)brace
id|drm_radeon_mem_init_heap_t
suffix:semicolon
multiline_comment|/* 1.6: Userspace can request &amp; wait on irq&squot;s:&n; */
DECL|struct|drm_radeon_irq_emit
r_typedef
r_struct
id|drm_radeon_irq_emit
(brace
DECL|member|irq_seq
r_int
op_star
id|irq_seq
suffix:semicolon
DECL|typedef|drm_radeon_irq_emit_t
)brace
id|drm_radeon_irq_emit_t
suffix:semicolon
DECL|struct|drm_radeon_irq_wait
r_typedef
r_struct
id|drm_radeon_irq_wait
(brace
DECL|member|irq_seq
r_int
id|irq_seq
suffix:semicolon
DECL|typedef|drm_radeon_irq_wait_t
)brace
id|drm_radeon_irq_wait_t
suffix:semicolon
multiline_comment|/* 1.10: Clients tell the DRM where they think the framebuffer is located in&n; * the card&squot;s address space, via a new generic ioctl to set parameters&n; */
DECL|struct|drm_radeon_setparam
r_typedef
r_struct
id|drm_radeon_setparam
(brace
DECL|member|param
r_int
r_int
id|param
suffix:semicolon
DECL|member|value
r_int64
id|value
suffix:semicolon
DECL|typedef|drm_radeon_setparam_t
)brace
id|drm_radeon_setparam_t
suffix:semicolon
DECL|macro|RADEON_SETPARAM_FB_LOCATION
mdefine_line|#define RADEON_SETPARAM_FB_LOCATION    1 /* determined framebuffer location */
macro_line|#endif
eof
