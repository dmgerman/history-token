multiline_comment|/*&n; *  linux/drivers/video/kyro/STG4000OverlayDevice.c&n; *&n; *  Copyright (C) 2000 Imagination Technologies Ltd&n; *  Copyright (C) 2002 STMicroelectronics&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file COPYING in the main directory of this archive&n; * for more details.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &quot;STG4000Reg.h&quot;
multiline_comment|/* HW Defines */
DECL|macro|STG4000_NO_SCALING
mdefine_line|#define STG4000_NO_SCALING    0x800
DECL|macro|STG4000_NO_DECIMATION
mdefine_line|#define STG4000_NO_DECIMATION 0xFFFFFFFF
multiline_comment|/* Primary surface */
DECL|macro|STG4000_PRIM_NUM_PIX
mdefine_line|#define STG4000_PRIM_NUM_PIX   5
DECL|macro|STG4000_PRIM_ALIGN
mdefine_line|#define STG4000_PRIM_ALIGN     4
DECL|macro|STG4000_PRIM_ADDR_BITS
mdefine_line|#define STG4000_PRIM_ADDR_BITS 20
DECL|macro|STG4000_PRIM_MIN_WIDTH
mdefine_line|#define STG4000_PRIM_MIN_WIDTH  640
DECL|macro|STG4000_PRIM_MAX_WIDTH
mdefine_line|#define STG4000_PRIM_MAX_WIDTH  1600
DECL|macro|STG4000_PRIM_MIN_HEIGHT
mdefine_line|#define STG4000_PRIM_MIN_HEIGHT 480
DECL|macro|STG4000_PRIM_MAX_HEIGHT
mdefine_line|#define STG4000_PRIM_MAX_HEIGHT 1200
multiline_comment|/* Overlay surface */
DECL|macro|STG4000_OVRL_NUM_PIX
mdefine_line|#define STG4000_OVRL_NUM_PIX   4
DECL|macro|STG4000_OVRL_ALIGN
mdefine_line|#define STG4000_OVRL_ALIGN     2
DECL|macro|STG4000_OVRL_ADDR_BITS
mdefine_line|#define STG4000_OVRL_ADDR_BITS 20
DECL|macro|STG4000_OVRL_NUM_MODES
mdefine_line|#define STG4000_OVRL_NUM_MODES 5
DECL|macro|STG4000_OVRL_MIN_WIDTH
mdefine_line|#define STG4000_OVRL_MIN_WIDTH  0
DECL|macro|STG4000_OVRL_MAX_WIDTH
mdefine_line|#define STG4000_OVRL_MAX_WIDTH  720
DECL|macro|STG4000_OVRL_MIN_HEIGHT
mdefine_line|#define STG4000_OVRL_MIN_HEIGHT 0
DECL|macro|STG4000_OVRL_MAX_HEIGHT
mdefine_line|#define STG4000_OVRL_MAX_HEIGHT 576
multiline_comment|/* Decimation and Scaling */
DECL|variable|adwDecim8
r_static
id|u32
id|adwDecim8
(braket
l_int|33
)braket
op_assign
(brace
l_int|0xffffffff
comma
l_int|0xfffeffff
comma
l_int|0xffdffbff
comma
l_int|0xfefefeff
comma
l_int|0xfdf7efbf
comma
l_int|0xfbdf7bdf
comma
l_int|0xf7bbddef
comma
l_int|0xeeeeeeef
comma
l_int|0xeeddbb77
comma
l_int|0xedb76db7
comma
l_int|0xdb6db6db
comma
l_int|0xdb5b5b5b
comma
l_int|0xdab5ad6b
comma
l_int|0xd5ab55ab
comma
l_int|0xd555aaab
comma
l_int|0xaaaaaaab
comma
l_int|0xaaaa5555
comma
l_int|0xaa952a55
comma
l_int|0xa94a5295
comma
l_int|0xa5252525
comma
l_int|0xa4924925
comma
l_int|0x92491249
comma
l_int|0x91224489
comma
l_int|0x91111111
comma
l_int|0x90884211
comma
l_int|0x88410821
comma
l_int|0x88102041
comma
l_int|0x81010101
comma
l_int|0x80800801
comma
l_int|0x80010001
comma
l_int|0x80000001
comma
l_int|0x00000001
comma
l_int|0x00000000
)brace
suffix:semicolon
DECL|struct|_OVRL_SRC_DEST
r_typedef
r_struct
id|_OVRL_SRC_DEST
(brace
multiline_comment|/*clipped on-screen pixel position of overlay */
DECL|member|ulDstX1
id|u32
id|ulDstX1
suffix:semicolon
DECL|member|ulDstY1
id|u32
id|ulDstY1
suffix:semicolon
DECL|member|ulDstX2
id|u32
id|ulDstX2
suffix:semicolon
DECL|member|ulDstY2
id|u32
id|ulDstY2
suffix:semicolon
multiline_comment|/*clipped pixel pos of source data within buffer thses need to be 128 bit word aligned */
DECL|member|ulSrcX1
id|u32
id|ulSrcX1
suffix:semicolon
DECL|member|ulSrcY1
id|u32
id|ulSrcY1
suffix:semicolon
DECL|member|ulSrcX2
id|u32
id|ulSrcX2
suffix:semicolon
DECL|member|ulSrcY2
id|u32
id|ulSrcY2
suffix:semicolon
multiline_comment|/* on-screen pixel position of overlay */
DECL|member|lDstX1
id|s32
id|lDstX1
suffix:semicolon
DECL|member|lDstY1
id|s32
id|lDstY1
suffix:semicolon
DECL|member|lDstX2
id|s32
id|lDstX2
suffix:semicolon
DECL|member|lDstY2
id|s32
id|lDstY2
suffix:semicolon
DECL|typedef|OVRL_SRC_DEST
)brace
id|OVRL_SRC_DEST
suffix:semicolon
DECL|variable|ovlWidth
DECL|variable|ovlHeight
DECL|variable|ovlStride
r_static
id|u32
id|ovlWidth
comma
id|ovlHeight
comma
id|ovlStride
suffix:semicolon
DECL|variable|ovlLinear
r_static
r_int
id|ovlLinear
suffix:semicolon
DECL|function|ResetOverlayRegisters
r_void
id|ResetOverlayRegisters
c_func
(paren
r_volatile
id|STG4000REG
id|__iomem
op_star
id|pSTGReg
)paren
(brace
id|u32
id|tmp
suffix:semicolon
multiline_comment|/* Set Overlay address to default */
id|tmp
op_assign
id|STG_READ_REG
c_func
(paren
id|DACOverlayAddr
)paren
suffix:semicolon
id|CLEAR_BITS_FRM_TO
c_func
(paren
l_int|0
comma
l_int|20
)paren
suffix:semicolon
id|CLEAR_BIT
c_func
(paren
l_int|31
)paren
suffix:semicolon
id|STG_WRITE_REG
c_func
(paren
id|DACOverlayAddr
comma
id|tmp
)paren
suffix:semicolon
multiline_comment|/* Set Overlay U address */
id|tmp
op_assign
id|STG_READ_REG
c_func
(paren
id|DACOverlayUAddr
)paren
suffix:semicolon
id|CLEAR_BITS_FRM_TO
c_func
(paren
l_int|0
comma
l_int|20
)paren
suffix:semicolon
id|STG_WRITE_REG
c_func
(paren
id|DACOverlayUAddr
comma
id|tmp
)paren
suffix:semicolon
multiline_comment|/* Set Overlay V address */
id|tmp
op_assign
id|STG_READ_REG
c_func
(paren
id|DACOverlayVAddr
)paren
suffix:semicolon
id|CLEAR_BITS_FRM_TO
c_func
(paren
l_int|0
comma
l_int|20
)paren
suffix:semicolon
id|STG_WRITE_REG
c_func
(paren
id|DACOverlayVAddr
comma
id|tmp
)paren
suffix:semicolon
multiline_comment|/* Set Overlay Size */
id|tmp
op_assign
id|STG_READ_REG
c_func
(paren
id|DACOverlaySize
)paren
suffix:semicolon
id|CLEAR_BITS_FRM_TO
c_func
(paren
l_int|0
comma
l_int|10
)paren
suffix:semicolon
id|CLEAR_BITS_FRM_TO
c_func
(paren
l_int|12
comma
l_int|31
)paren
suffix:semicolon
id|STG_WRITE_REG
c_func
(paren
id|DACOverlaySize
comma
id|tmp
)paren
suffix:semicolon
multiline_comment|/* Set Overlay Vt Decimation */
id|tmp
op_assign
id|STG4000_NO_DECIMATION
suffix:semicolon
id|STG_WRITE_REG
c_func
(paren
id|DACOverlayVtDec
comma
id|tmp
)paren
suffix:semicolon
multiline_comment|/* Set Overlay format to default value */
id|tmp
op_assign
id|STG_READ_REG
c_func
(paren
id|DACPixelFormat
)paren
suffix:semicolon
id|CLEAR_BITS_FRM_TO
c_func
(paren
l_int|4
comma
l_int|7
)paren
suffix:semicolon
id|CLEAR_BITS_FRM_TO
c_func
(paren
l_int|16
comma
l_int|22
)paren
suffix:semicolon
id|STG_WRITE_REG
c_func
(paren
id|DACPixelFormat
comma
id|tmp
)paren
suffix:semicolon
multiline_comment|/* Set Vertical scaling to default */
id|tmp
op_assign
id|STG_READ_REG
c_func
(paren
id|DACVerticalScal
)paren
suffix:semicolon
id|CLEAR_BITS_FRM_TO
c_func
(paren
l_int|0
comma
l_int|11
)paren
suffix:semicolon
id|CLEAR_BITS_FRM_TO
c_func
(paren
l_int|16
comma
l_int|22
)paren
suffix:semicolon
id|tmp
op_or_assign
id|STG4000_NO_SCALING
suffix:semicolon
multiline_comment|/* Set to no scaling */
id|STG_WRITE_REG
c_func
(paren
id|DACVerticalScal
comma
id|tmp
)paren
suffix:semicolon
multiline_comment|/* Set Horizontal Scaling to default */
id|tmp
op_assign
id|STG_READ_REG
c_func
(paren
id|DACHorizontalScal
)paren
suffix:semicolon
id|CLEAR_BITS_FRM_TO
c_func
(paren
l_int|0
comma
l_int|11
)paren
suffix:semicolon
id|CLEAR_BITS_FRM_TO
c_func
(paren
l_int|16
comma
l_int|17
)paren
suffix:semicolon
id|tmp
op_or_assign
id|STG4000_NO_SCALING
suffix:semicolon
multiline_comment|/* Set to no scaling */
id|STG_WRITE_REG
c_func
(paren
id|DACHorizontalScal
comma
id|tmp
)paren
suffix:semicolon
multiline_comment|/* Set Blend mode to Alpha Blend */
multiline_comment|/* ????? SG 08/11/2001 Surely this isn&squot;t the alpha blend mode,&n;&t;   hopefully its overwrite&n;&t; */
id|tmp
op_assign
id|STG_READ_REG
c_func
(paren
id|DACBlendCtrl
)paren
suffix:semicolon
id|CLEAR_BITS_FRM_TO
c_func
(paren
l_int|0
comma
l_int|30
)paren
suffix:semicolon
id|tmp
op_assign
(paren
id|GRAPHICS_MODE
op_lshift
l_int|28
)paren
suffix:semicolon
id|STG_WRITE_REG
c_func
(paren
id|DACBlendCtrl
comma
id|tmp
)paren
suffix:semicolon
)brace
DECL|function|CreateOverlaySurface
r_int
id|CreateOverlaySurface
c_func
(paren
r_volatile
id|STG4000REG
id|__iomem
op_star
id|pSTGReg
comma
id|u32
id|inWidth
comma
id|u32
id|inHeight
comma
r_int
id|bLinear
comma
id|u32
id|ulOverlayOffset
comma
id|u32
op_star
id|retStride
comma
id|u32
op_star
id|retUVStride
)paren
(brace
id|u32
id|tmp
suffix:semicolon
id|u32
id|ulStride
suffix:semicolon
r_if
c_cond
(paren
id|inWidth
OG
id|STG4000_OVRL_MAX_WIDTH
op_logical_or
id|inHeight
OG
id|STG4000_OVRL_MAX_HEIGHT
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/* Stride in 16 byte words - 16Bpp */
r_if
c_cond
(paren
id|bLinear
)paren
(brace
multiline_comment|/* Format is 16bits so num 16 byte words is width/8 */
r_if
c_cond
(paren
(paren
id|inWidth
op_amp
l_int|0x7
)paren
op_eq
l_int|0
)paren
(brace
multiline_comment|/* inWidth % 8 */
id|ulStride
op_assign
(paren
id|inWidth
op_div
l_int|8
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Round up to next 16byte boundary */
id|ulStride
op_assign
(paren
(paren
id|inWidth
op_plus
l_int|8
)paren
op_div
l_int|8
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/* Y component is 8bits so num 16 byte words is width/16 */
r_if
c_cond
(paren
(paren
id|inWidth
op_amp
l_int|0xf
)paren
op_eq
l_int|0
)paren
(brace
multiline_comment|/* inWidth % 16 */
id|ulStride
op_assign
(paren
id|inWidth
op_div
l_int|16
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Round up to next 16byte boundary */
id|ulStride
op_assign
(paren
(paren
id|inWidth
op_plus
l_int|16
)paren
op_div
l_int|16
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Set Overlay address and Format mode */
id|tmp
op_assign
id|STG_READ_REG
c_func
(paren
id|DACOverlayAddr
)paren
suffix:semicolon
id|CLEAR_BITS_FRM_TO
c_func
(paren
l_int|0
comma
l_int|20
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bLinear
)paren
(brace
id|CLEAR_BIT
c_func
(paren
l_int|31
)paren
suffix:semicolon
multiline_comment|/* Overlay format to Linear */
)brace
r_else
(brace
id|tmp
op_or_assign
id|SET_BIT
c_func
(paren
l_int|31
)paren
suffix:semicolon
multiline_comment|/* Overlay format to Planer */
)brace
multiline_comment|/* Only bits 24:4 of the Overlay address */
id|tmp
op_or_assign
(paren
id|ulOverlayOffset
op_rshift
l_int|4
)paren
suffix:semicolon
id|STG_WRITE_REG
c_func
(paren
id|DACOverlayAddr
comma
id|tmp
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bLinear
)paren
(brace
id|u32
id|uvSize
op_assign
(paren
id|inWidth
op_amp
l_int|0x1
)paren
ques
c_cond
(paren
id|inWidth
op_plus
l_int|1
op_div
l_int|2
)paren
suffix:colon
(paren
id|inWidth
op_div
l_int|2
)paren
suffix:semicolon
id|u32
id|uvStride
suffix:semicolon
id|u32
id|ulOffset
suffix:semicolon
multiline_comment|/* Y component is 8bits so num 32 byte words is width/32 */
r_if
c_cond
(paren
(paren
id|uvSize
op_amp
l_int|0xf
)paren
op_eq
l_int|0
)paren
(brace
multiline_comment|/* inWidth % 16 */
id|uvStride
op_assign
(paren
id|uvSize
op_div
l_int|16
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Round up to next 32byte boundary */
id|uvStride
op_assign
(paren
(paren
id|uvSize
op_plus
l_int|16
)paren
op_div
l_int|16
)paren
suffix:semicolon
)brace
id|ulOffset
op_assign
id|ulOverlayOffset
op_plus
(paren
id|inHeight
op_star
(paren
id|ulStride
op_star
l_int|16
)paren
)paren
suffix:semicolon
multiline_comment|/* Align U,V data to 32byte boundary */
r_if
c_cond
(paren
(paren
id|ulOffset
op_amp
l_int|0x1f
)paren
op_ne
l_int|0
)paren
id|ulOffset
op_assign
(paren
id|ulOffset
op_plus
l_int|32L
)paren
op_amp
l_int|0xffffffE0L
suffix:semicolon
id|tmp
op_assign
id|STG_READ_REG
c_func
(paren
id|DACOverlayUAddr
)paren
suffix:semicolon
id|CLEAR_BITS_FRM_TO
c_func
(paren
l_int|0
comma
l_int|20
)paren
suffix:semicolon
id|tmp
op_or_assign
(paren
id|ulOffset
op_rshift
l_int|4
)paren
suffix:semicolon
id|STG_WRITE_REG
c_func
(paren
id|DACOverlayUAddr
comma
id|tmp
)paren
suffix:semicolon
id|ulOffset
op_add_assign
(paren
id|inHeight
op_div
l_int|2
)paren
op_star
(paren
id|uvStride
op_star
l_int|16
)paren
suffix:semicolon
multiline_comment|/* Align U,V data to 32byte boundary */
r_if
c_cond
(paren
(paren
id|ulOffset
op_amp
l_int|0x1f
)paren
op_ne
l_int|0
)paren
id|ulOffset
op_assign
(paren
id|ulOffset
op_plus
l_int|32L
)paren
op_amp
l_int|0xffffffE0L
suffix:semicolon
id|tmp
op_assign
id|STG_READ_REG
c_func
(paren
id|DACOverlayVAddr
)paren
suffix:semicolon
id|CLEAR_BITS_FRM_TO
c_func
(paren
l_int|0
comma
l_int|20
)paren
suffix:semicolon
id|tmp
op_or_assign
(paren
id|ulOffset
op_rshift
l_int|4
)paren
suffix:semicolon
id|STG_WRITE_REG
c_func
(paren
id|DACOverlayVAddr
comma
id|tmp
)paren
suffix:semicolon
op_star
id|retUVStride
op_assign
id|uvStride
op_star
l_int|16
suffix:semicolon
)brace
multiline_comment|/* Set Overlay YUV pixel format&n;&t; * Make sure that LUT not used - ??????&n;&t; */
id|tmp
op_assign
id|STG_READ_REG
c_func
(paren
id|DACPixelFormat
)paren
suffix:semicolon
multiline_comment|/* Only support Planer or UYVY linear formats */
id|CLEAR_BITS_FRM_TO
c_func
(paren
l_int|4
comma
l_int|9
)paren
suffix:semicolon
id|STG_WRITE_REG
c_func
(paren
id|DACPixelFormat
comma
id|tmp
)paren
suffix:semicolon
id|ovlWidth
op_assign
id|inWidth
suffix:semicolon
id|ovlHeight
op_assign
id|inHeight
suffix:semicolon
id|ovlStride
op_assign
id|ulStride
suffix:semicolon
id|ovlLinear
op_assign
id|bLinear
suffix:semicolon
op_star
id|retStride
op_assign
id|ulStride
op_lshift
l_int|4
suffix:semicolon
multiline_comment|/* In bytes */
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|SetOverlayBlendMode
r_int
id|SetOverlayBlendMode
c_func
(paren
r_volatile
id|STG4000REG
id|__iomem
op_star
id|pSTGReg
comma
id|OVRL_BLEND_MODE
id|mode
comma
id|u32
id|ulAlpha
comma
id|u32
id|ulColorKey
)paren
(brace
id|u32
id|tmp
suffix:semicolon
id|tmp
op_assign
id|STG_READ_REG
c_func
(paren
id|DACBlendCtrl
)paren
suffix:semicolon
id|CLEAR_BITS_FRM_TO
c_func
(paren
l_int|28
comma
l_int|30
)paren
suffix:semicolon
id|tmp
op_or_assign
(paren
id|mode
op_lshift
l_int|28
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|mode
)paren
(brace
r_case
id|COLOR_KEY
suffix:colon
id|CLEAR_BITS_FRM_TO
c_func
(paren
l_int|0
comma
l_int|23
)paren
suffix:semicolon
id|tmp
op_or_assign
(paren
id|ulColorKey
op_amp
l_int|0x00FFFFFF
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|GLOBAL_ALPHA
suffix:colon
id|CLEAR_BITS_FRM_TO
c_func
(paren
l_int|24
comma
l_int|27
)paren
suffix:semicolon
id|tmp
op_or_assign
(paren
(paren
id|ulAlpha
op_amp
l_int|0xF
)paren
op_lshift
l_int|24
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CK_PIXEL_ALPHA
suffix:colon
id|CLEAR_BITS_FRM_TO
c_func
(paren
l_int|0
comma
l_int|23
)paren
suffix:semicolon
id|tmp
op_or_assign
(paren
id|ulColorKey
op_amp
l_int|0x00FFFFFF
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CK_GLOBAL_ALPHA
suffix:colon
id|CLEAR_BITS_FRM_TO
c_func
(paren
l_int|0
comma
l_int|23
)paren
suffix:semicolon
id|tmp
op_or_assign
(paren
id|ulColorKey
op_amp
l_int|0x00FFFFFF
)paren
suffix:semicolon
id|CLEAR_BITS_FRM_TO
c_func
(paren
l_int|24
comma
l_int|27
)paren
suffix:semicolon
id|tmp
op_or_assign
(paren
(paren
id|ulAlpha
op_amp
l_int|0xF
)paren
op_lshift
l_int|24
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|GRAPHICS_MODE
suffix:colon
r_case
id|PER_PIXEL_ALPHA
suffix:colon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|STG_WRITE_REG
c_func
(paren
id|DACBlendCtrl
comma
id|tmp
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|EnableOverlayPlane
r_void
id|EnableOverlayPlane
c_func
(paren
r_volatile
id|STG4000REG
id|__iomem
op_star
id|pSTGReg
)paren
(brace
id|u32
id|tmp
suffix:semicolon
multiline_comment|/* Enable Overlay */
id|tmp
op_assign
id|STG_READ_REG
c_func
(paren
id|DACPixelFormat
)paren
suffix:semicolon
id|tmp
op_or_assign
id|SET_BIT
c_func
(paren
l_int|7
)paren
suffix:semicolon
id|STG_WRITE_REG
c_func
(paren
id|DACPixelFormat
comma
id|tmp
)paren
suffix:semicolon
multiline_comment|/* Set video stream control */
id|tmp
op_assign
id|STG_READ_REG
c_func
(paren
id|DACStreamCtrl
)paren
suffix:semicolon
id|tmp
op_or_assign
id|SET_BIT
c_func
(paren
l_int|1
)paren
suffix:semicolon
multiline_comment|/* video stream */
id|STG_WRITE_REG
c_func
(paren
id|DACStreamCtrl
comma
id|tmp
)paren
suffix:semicolon
)brace
DECL|function|Overlap
r_static
id|u32
id|Overlap
c_func
(paren
id|u32
id|ulBits
comma
id|u32
id|ulPattern
)paren
(brace
id|u32
id|ulCount
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|ulBits
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|ulPattern
op_amp
l_int|1
)paren
)paren
id|ulCount
op_increment
suffix:semicolon
id|ulBits
op_decrement
suffix:semicolon
id|ulPattern
op_assign
id|ulPattern
op_rshift
l_int|1
suffix:semicolon
)brace
r_return
id|ulCount
suffix:semicolon
)brace
DECL|function|SetOverlayViewPort
r_int
id|SetOverlayViewPort
c_func
(paren
r_volatile
id|STG4000REG
id|__iomem
op_star
id|pSTGReg
comma
id|u32
id|left
comma
id|u32
id|top
comma
id|u32
id|right
comma
id|u32
id|bottom
)paren
(brace
id|OVRL_SRC_DEST
id|srcDest
suffix:semicolon
id|u32
id|ulSrcTop
comma
id|ulSrcBottom
suffix:semicolon
id|u32
id|ulSrc
comma
id|ulDest
suffix:semicolon
id|u32
id|ulFxScale
comma
id|ulFxOffset
suffix:semicolon
id|u32
id|ulHeight
comma
id|ulWidth
suffix:semicolon
id|u32
id|ulPattern
suffix:semicolon
id|u32
id|ulDecimate
comma
id|ulDecimated
suffix:semicolon
id|u32
id|ulApplied
suffix:semicolon
id|u32
id|ulDacXScale
comma
id|ulDacYScale
suffix:semicolon
id|u32
id|ulScale
suffix:semicolon
id|u32
id|ulLeft
comma
id|ulRight
suffix:semicolon
id|u32
id|ulSrcLeft
comma
id|ulSrcRight
suffix:semicolon
id|u32
id|ulScaleLeft
comma
id|ulScaleRight
suffix:semicolon
id|u32
id|ulhDecim
suffix:semicolon
id|u32
id|ulsVal
suffix:semicolon
id|u32
id|ulVertDecFactor
suffix:semicolon
r_int
id|bResult
suffix:semicolon
id|u32
id|ulClipOff
op_assign
l_int|0
suffix:semicolon
id|u32
id|ulBits
op_assign
l_int|0
suffix:semicolon
id|u32
id|ulsAdd
op_assign
l_int|0
suffix:semicolon
id|u32
id|tmp
comma
id|ulStride
suffix:semicolon
id|u32
id|ulExcessPixels
comma
id|ulClip
comma
id|ulExtraLines
suffix:semicolon
id|srcDest.ulSrcX1
op_assign
l_int|0
suffix:semicolon
id|srcDest.ulSrcY1
op_assign
l_int|0
suffix:semicolon
id|srcDest.ulSrcX2
op_assign
id|ovlWidth
op_minus
l_int|1
suffix:semicolon
id|srcDest.ulSrcY2
op_assign
id|ovlHeight
op_minus
l_int|1
suffix:semicolon
id|srcDest.ulDstX1
op_assign
id|left
suffix:semicolon
id|srcDest.ulDstY1
op_assign
id|top
suffix:semicolon
id|srcDest.ulDstX2
op_assign
id|right
suffix:semicolon
id|srcDest.ulDstY2
op_assign
id|bottom
suffix:semicolon
id|srcDest.lDstX1
op_assign
id|srcDest.ulDstX1
suffix:semicolon
id|srcDest.lDstY1
op_assign
id|srcDest.ulDstY1
suffix:semicolon
id|srcDest.lDstX2
op_assign
id|srcDest.ulDstX2
suffix:semicolon
id|srcDest.lDstY2
op_assign
id|srcDest.ulDstY2
suffix:semicolon
multiline_comment|/************* Vertical decimation/scaling ******************/
multiline_comment|/* Get Src Top and Bottom */
id|ulSrcTop
op_assign
id|srcDest.ulSrcY1
suffix:semicolon
id|ulSrcBottom
op_assign
id|srcDest.ulSrcY2
suffix:semicolon
id|ulSrc
op_assign
id|ulSrcBottom
op_minus
id|ulSrcTop
suffix:semicolon
id|ulDest
op_assign
id|srcDest.lDstY2
op_minus
id|srcDest.lDstY1
suffix:semicolon
multiline_comment|/* on-screen overlay */
r_if
c_cond
(paren
id|ulSrc
op_le
l_int|1
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* First work out the position we are to display as offset from the&n;&t; * source of the buffer&n;&t; */
id|ulFxScale
op_assign
(paren
id|ulDest
op_lshift
l_int|11
)paren
op_div
id|ulSrc
suffix:semicolon
multiline_comment|/* fixed point scale factor */
id|ulFxOffset
op_assign
(paren
id|srcDest.lDstY2
op_minus
id|srcDest.ulDstY2
)paren
op_lshift
l_int|11
suffix:semicolon
id|ulSrcBottom
op_assign
id|ulSrcBottom
op_minus
(paren
id|ulFxOffset
op_div
id|ulFxScale
)paren
suffix:semicolon
id|ulSrc
op_assign
id|ulSrcBottom
op_minus
id|ulSrcTop
suffix:semicolon
id|ulHeight
op_assign
id|ulSrc
suffix:semicolon
id|ulDest
op_assign
id|srcDest.ulDstY2
op_minus
(paren
id|srcDest.ulDstY1
op_minus
l_int|1
)paren
suffix:semicolon
id|ulPattern
op_assign
id|adwDecim8
(braket
id|ulBits
)braket
suffix:semicolon
multiline_comment|/* At this point ulSrc represents the input decimator */
r_if
c_cond
(paren
id|ulSrc
OG
id|ulDest
)paren
(brace
id|ulDecimate
op_assign
id|ulSrc
op_minus
id|ulDest
suffix:semicolon
id|ulBits
op_assign
l_int|0
suffix:semicolon
id|ulApplied
op_assign
id|ulSrc
op_div
l_int|32
suffix:semicolon
r_while
c_loop
(paren
(paren
(paren
id|ulBits
op_star
id|ulApplied
)paren
op_plus
id|Overlap
c_func
(paren
(paren
id|ulSrc
op_mod
l_int|32
)paren
comma
id|adwDecim8
(braket
id|ulBits
)braket
)paren
)paren
OL
id|ulDecimate
)paren
id|ulBits
op_increment
suffix:semicolon
id|ulPattern
op_assign
id|adwDecim8
(braket
id|ulBits
)braket
suffix:semicolon
id|ulDecimated
op_assign
(paren
id|ulBits
op_star
id|ulApplied
)paren
op_plus
id|Overlap
c_func
(paren
(paren
id|ulSrc
op_mod
l_int|32
)paren
comma
id|ulPattern
)paren
suffix:semicolon
id|ulSrc
op_assign
id|ulSrc
op_minus
id|ulDecimated
suffix:semicolon
multiline_comment|/* the number number of lines that will go into the scaler */
)brace
r_if
c_cond
(paren
id|ulBits
op_logical_and
(paren
id|ulBits
op_ne
l_int|32
)paren
)paren
(brace
id|ulVertDecFactor
op_assign
(paren
l_int|63
op_minus
id|ulBits
)paren
op_div
(paren
l_int|32
op_minus
id|ulBits
)paren
suffix:semicolon
multiline_comment|/* vertical decimation factor scaled up to nearest integer */
)brace
r_else
(brace
id|ulVertDecFactor
op_assign
l_int|1
suffix:semicolon
)brace
id|ulDacYScale
op_assign
(paren
(paren
id|ulSrc
op_minus
l_int|1
)paren
op_star
l_int|2048
)paren
op_div
(paren
id|ulDest
op_plus
l_int|1
)paren
suffix:semicolon
id|tmp
op_assign
id|STG_READ_REG
c_func
(paren
id|DACOverlayVtDec
)paren
suffix:semicolon
multiline_comment|/* Decimation */
id|CLEAR_BITS_FRM_TO
c_func
(paren
l_int|0
comma
l_int|31
)paren
suffix:semicolon
id|tmp
op_assign
id|ulPattern
suffix:semicolon
id|STG_WRITE_REG
c_func
(paren
id|DACOverlayVtDec
comma
id|tmp
)paren
suffix:semicolon
multiline_comment|/***************** Horizontal decimation/scaling ***************************/
multiline_comment|/*&n;&t; * Now we handle the horizontal case, this is a simplified verison of&n;&t; * the vertical case in that we decimate by factors of 2.  as we are&n;&t; * working in words we should always be able to decimate by these&n;&t; * factors.  as we always have to have a buffer which is aligned to a&n;&t; * whole number of 128 bit words, we must align the left side to the&n;&t; * lowest to the next lowest 128 bit boundary, and the right hand edge&n;&t; * to the next largets boundary, (in a similar way to how we didi it in&n;&t; * PMX1) as the left and right hand edges are aligned to these&n;&t; * boundaries normally this only becomes an issue when we are chopping&n;&t; * of one of the sides We shall work out vertical stuff first&n;&t; */
id|ulSrc
op_assign
id|srcDest.ulSrcX2
op_minus
id|srcDest.ulSrcX1
suffix:semicolon
id|ulDest
op_assign
id|srcDest.lDstX2
op_minus
id|srcDest.lDstX1
suffix:semicolon
macro_line|#ifdef _OLDCODE
id|ulLeft
op_assign
id|srcDest.ulDstX1
suffix:semicolon
id|ulRight
op_assign
id|srcDest.ulDstX2
suffix:semicolon
macro_line|#else
r_if
c_cond
(paren
id|srcDest.ulDstX1
OG
l_int|2
)paren
(brace
id|ulLeft
op_assign
id|srcDest.ulDstX1
op_plus
l_int|2
suffix:semicolon
id|ulRight
op_assign
id|srcDest.ulDstX2
op_plus
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|ulLeft
op_assign
id|srcDest.ulDstX1
suffix:semicolon
id|ulRight
op_assign
id|srcDest.ulDstX2
op_plus
l_int|1
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* first work out the position we are to display as offset from the source of the buffer */
id|bResult
op_assign
l_int|1
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
id|ulDest
op_eq
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* source pixels per dest pixel &lt;&lt;11 */
id|ulFxScale
op_assign
(paren
(paren
id|ulSrc
op_minus
l_int|1
)paren
op_lshift
l_int|11
)paren
op_div
(paren
id|ulDest
)paren
suffix:semicolon
multiline_comment|/* then number of destination pixels out we are */
id|ulFxOffset
op_assign
id|ulFxScale
op_star
(paren
(paren
id|srcDest.ulDstX1
op_minus
id|srcDest.lDstX1
)paren
op_plus
id|ulClipOff
)paren
suffix:semicolon
id|ulFxOffset
op_rshift_assign
l_int|11
suffix:semicolon
multiline_comment|/* this replaces the code which was making a decision as to use either ulFxOffset or ulSrcX1 */
id|ulSrcLeft
op_assign
id|srcDest.ulSrcX1
op_plus
id|ulFxOffset
suffix:semicolon
multiline_comment|/* then number of destination pixels out we are */
id|ulFxOffset
op_assign
id|ulFxScale
op_star
(paren
id|srcDest.lDstX2
op_minus
id|srcDest.ulDstX2
)paren
suffix:semicolon
id|ulFxOffset
op_rshift_assign
l_int|11
suffix:semicolon
id|ulSrcRight
op_assign
id|srcDest.ulSrcX2
op_minus
id|ulFxOffset
suffix:semicolon
multiline_comment|/*&n;&t;&t; * we must align these to our 128 bit boundaries. we shall&n;&t;&t; * round down the pixel pos to the nearest 8 pixels.&n;&t;&t; */
id|ulScaleLeft
op_assign
id|ulSrcLeft
suffix:semicolon
id|ulScaleRight
op_assign
id|ulSrcRight
suffix:semicolon
multiline_comment|/* shift fxscale until it is in the range of the scaler */
id|ulhDecim
op_assign
l_int|0
suffix:semicolon
id|ulScale
op_assign
(paren
(paren
(paren
id|ulSrcRight
op_minus
id|ulSrcLeft
)paren
op_minus
l_int|1
)paren
op_lshift
(paren
l_int|11
op_minus
id|ulhDecim
)paren
)paren
op_div
(paren
id|ulRight
op_minus
id|ulLeft
op_plus
l_int|2
)paren
suffix:semicolon
r_while
c_loop
(paren
id|ulScale
OG
l_int|0x800
)paren
(brace
id|ulhDecim
op_increment
suffix:semicolon
id|ulScale
op_assign
(paren
(paren
(paren
id|ulSrcRight
op_minus
id|ulSrcLeft
)paren
op_minus
l_int|1
)paren
op_lshift
(paren
l_int|11
op_minus
id|ulhDecim
)paren
)paren
op_div
(paren
id|ulRight
op_minus
id|ulLeft
op_plus
l_int|2
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * to try and get the best values We first try and use&n;&t;&t; * src/dwdest for the scale factor, then we move onto src-1&n;&t;&t; *&n;&t;&t; * we want to check to see if we will need to clip data, if so&n;&t;&t; * then we should clip our source so that we don&squot;t need to&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|ovlLinear
)paren
(brace
id|ulSrcLeft
op_and_assign
op_complement
l_int|0x1f
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * we must align the right hand edge to the next 32&n;&t;&t;&t; * pixel` boundary, must be on a 256 boundary so u, and&n;&t;&t;&t; * v are 128 bit aligned&n;&t;&t;&t; */
id|ulSrcRight
op_assign
(paren
id|ulSrcRight
op_plus
l_int|0x1f
)paren
op_amp
op_complement
l_int|0x1f
suffix:semicolon
)brace
r_else
(brace
id|ulSrcLeft
op_and_assign
op_complement
l_int|0x7
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * we must align the right hand edge to the next&n;&t;&t;&t; * 8pixel` boundary&n;&t;&t;&t; */
id|ulSrcRight
op_assign
(paren
id|ulSrcRight
op_plus
l_int|0x7
)paren
op_amp
op_complement
l_int|0x7
suffix:semicolon
)brace
multiline_comment|/* this is the input size line store needs to cope with */
id|ulWidth
op_assign
id|ulSrcRight
op_minus
id|ulSrcLeft
suffix:semicolon
multiline_comment|/*&n;&t;&t; * use unclipped value to work out scale factror this is the&n;&t;&t; * scale factor we want we shall now work out the horizonal&n;&t;&t; * decimation and scaling&n;&t;&t; */
id|ulsVal
op_assign
(paren
(paren
id|ulWidth
op_div
l_int|8
)paren
op_rshift
id|ulhDecim
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ulWidth
op_ne
(paren
id|ulsVal
op_lshift
id|ulhDecim
)paren
op_star
l_int|8
)paren
)paren
id|ulsAdd
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* input pixels to scaler; */
id|ulSrc
op_assign
id|ulWidth
op_rshift
id|ulhDecim
suffix:semicolon
r_if
c_cond
(paren
id|ulSrc
op_le
l_int|2
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|ulExcessPixels
op_assign
(paren
(paren
(paren
(paren
id|ulScaleLeft
op_minus
id|ulSrcLeft
)paren
)paren
op_lshift
(paren
l_int|11
op_minus
id|ulhDecim
)paren
)paren
op_div
id|ulScale
)paren
suffix:semicolon
id|ulClip
op_assign
(paren
id|ulSrc
op_lshift
l_int|11
)paren
op_div
id|ulScale
suffix:semicolon
id|ulClip
op_sub_assign
(paren
id|ulRight
op_minus
id|ulLeft
)paren
suffix:semicolon
id|ulClip
op_add_assign
id|ulExcessPixels
suffix:semicolon
r_if
c_cond
(paren
id|ulClip
)paren
id|ulClip
op_decrement
suffix:semicolon
multiline_comment|/* We may need to do more here if we really have a HW rev &lt; 5 */
)brace
r_while
c_loop
(paren
op_logical_neg
id|bResult
)paren
suffix:semicolon
id|ulExtraLines
op_assign
(paren
l_int|1
op_lshift
id|ulhDecim
)paren
op_star
id|ulVertDecFactor
suffix:semicolon
id|ulExtraLines
op_add_assign
l_int|64
suffix:semicolon
id|ulHeight
op_add_assign
id|ulExtraLines
suffix:semicolon
id|ulDacXScale
op_assign
id|ulScale
suffix:semicolon
id|tmp
op_assign
id|STG_READ_REG
c_func
(paren
id|DACVerticalScal
)paren
suffix:semicolon
id|CLEAR_BITS_FRM_TO
c_func
(paren
l_int|0
comma
l_int|11
)paren
suffix:semicolon
id|CLEAR_BITS_FRM_TO
c_func
(paren
l_int|16
comma
l_int|22
)paren
suffix:semicolon
multiline_comment|/* Vertical Scaling */
multiline_comment|/* Calculate new output line stride, this is always the number of 422&n;&t;   words in the line buffer, so it doesn&squot;t matter if the&n;&t;   mode is 420. Then set the vertical scale register.&n;&t; */
id|ulStride
op_assign
(paren
id|ulWidth
op_rshift
(paren
id|ulhDecim
op_plus
l_int|3
)paren
)paren
op_plus
id|ulsAdd
suffix:semicolon
id|tmp
op_or_assign
(paren
(paren
id|ulStride
op_lshift
l_int|16
)paren
op_or
(paren
id|ulDacYScale
)paren
)paren
suffix:semicolon
multiline_comment|/* DAC_LS_CTRL = stride */
id|STG_WRITE_REG
c_func
(paren
id|DACVerticalScal
comma
id|tmp
)paren
suffix:semicolon
multiline_comment|/* Now set up the overlay size using the modified width and height&n;&t;   from decimate and scaling calculations&n;&t; */
id|tmp
op_assign
id|STG_READ_REG
c_func
(paren
id|DACOverlaySize
)paren
suffix:semicolon
id|CLEAR_BITS_FRM_TO
c_func
(paren
l_int|0
comma
l_int|10
)paren
suffix:semicolon
id|CLEAR_BITS_FRM_TO
c_func
(paren
l_int|12
comma
l_int|31
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ovlLinear
)paren
(brace
id|tmp
op_or_assign
(paren
id|ovlStride
op_or
(paren
(paren
id|ulHeight
op_plus
l_int|1
)paren
op_lshift
l_int|12
)paren
op_or
(paren
(paren
(paren
id|ulWidth
op_div
l_int|8
)paren
op_minus
l_int|1
)paren
op_lshift
l_int|23
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|tmp
op_or_assign
(paren
id|ovlStride
op_or
(paren
(paren
id|ulHeight
op_plus
l_int|1
)paren
op_lshift
l_int|12
)paren
op_or
(paren
(paren
(paren
id|ulWidth
op_div
l_int|32
)paren
op_minus
l_int|1
)paren
op_lshift
l_int|23
)paren
)paren
suffix:semicolon
)brace
id|STG_WRITE_REG
c_func
(paren
id|DACOverlaySize
comma
id|tmp
)paren
suffix:semicolon
multiline_comment|/* Set Video Window Start */
id|tmp
op_assign
(paren
(paren
id|ulLeft
op_lshift
l_int|16
)paren
)paren
op_or
(paren
id|srcDest.ulDstY1
)paren
suffix:semicolon
id|STG_WRITE_REG
c_func
(paren
id|DACVidWinStart
comma
id|tmp
)paren
suffix:semicolon
multiline_comment|/* Set Video Window End */
id|tmp
op_assign
(paren
(paren
id|ulRight
)paren
op_lshift
l_int|16
)paren
op_or
(paren
id|srcDest.ulDstY2
)paren
suffix:semicolon
id|STG_WRITE_REG
c_func
(paren
id|DACVidWinEnd
comma
id|tmp
)paren
suffix:semicolon
multiline_comment|/* Finally set up the rest of the overlay regs in the order&n;&t;   done in the IMG driver&n;&t; */
id|tmp
op_assign
id|STG_READ_REG
c_func
(paren
id|DACPixelFormat
)paren
suffix:semicolon
id|tmp
op_assign
(paren
(paren
id|ulExcessPixels
op_lshift
l_int|16
)paren
op_or
id|tmp
)paren
op_amp
l_int|0x7fffffff
suffix:semicolon
id|STG_WRITE_REG
c_func
(paren
id|DACPixelFormat
comma
id|tmp
)paren
suffix:semicolon
id|tmp
op_assign
id|STG_READ_REG
c_func
(paren
id|DACHorizontalScal
)paren
suffix:semicolon
id|CLEAR_BITS_FRM_TO
c_func
(paren
l_int|0
comma
l_int|11
)paren
suffix:semicolon
id|CLEAR_BITS_FRM_TO
c_func
(paren
l_int|16
comma
l_int|17
)paren
suffix:semicolon
id|tmp
op_or_assign
(paren
(paren
id|ulhDecim
op_lshift
l_int|16
)paren
op_or
(paren
id|ulDacXScale
)paren
)paren
suffix:semicolon
id|STG_WRITE_REG
c_func
(paren
id|DACHorizontalScal
comma
id|tmp
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
