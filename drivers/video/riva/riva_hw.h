multiline_comment|/***************************************************************************&bslash;&n;|*                                                                           *|&n;|*       Copyright 1993-1999 NVIDIA, Corporation.  All rights reserved.      *|&n;|*                                                                           *|&n;|*     NOTICE TO USER:   The source code  is copyrighted under  U.S. and     *|&n;|*     international laws.  Users and possessors of this source code are     *|&n;|*     hereby granted a nonexclusive,  royalty-free copyright license to     *|&n;|*     use this code in individual and commercial software.                  *|&n;|*                                                                           *|&n;|*     Any use of this source code must include,  in the user documenta-     *|&n;|*     tion and  internal comments to the code,  notices to the end user     *|&n;|*     as follows:                                                           *|&n;|*                                                                           *|&n;|*       Copyright 1993-1999 NVIDIA, Corporation.  All rights reserved.      *|&n;|*                                                                           *|&n;|*     NVIDIA, CORPORATION MAKES NO REPRESENTATION ABOUT THE SUITABILITY     *|&n;|*     OF  THIS SOURCE  CODE  FOR ANY PURPOSE.  IT IS  PROVIDED  &quot;AS IS&quot;     *|&n;|*     WITHOUT EXPRESS OR IMPLIED WARRANTY OF ANY KIND.  NVIDIA, CORPOR-     *|&n;|*     ATION DISCLAIMS ALL WARRANTIES  WITH REGARD  TO THIS SOURCE CODE,     *|&n;|*     INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY, NONINFRINGE-     *|&n;|*     MENT,  AND FITNESS  FOR A PARTICULAR PURPOSE.   IN NO EVENT SHALL     *|&n;|*     NVIDIA, CORPORATION  BE LIABLE FOR ANY SPECIAL,  INDIRECT,  INCI-     *|&n;|*     DENTAL, OR CONSEQUENTIAL DAMAGES,  OR ANY DAMAGES  WHATSOEVER RE-     *|&n;|*     SULTING FROM LOSS OF USE,  DATA OR PROFITS,  WHETHER IN AN ACTION     *|&n;|*     OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,  ARISING OUT OF     *|&n;|*     OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOURCE CODE.     *|&n;|*                                                                           *|&n;|*     U.S. Government  End  Users.   This source code  is a &quot;commercial     *|&n;|*     item,&quot;  as that  term is  defined at  48 C.F.R. 2.101 (OCT 1995),     *|&n;|*     consisting  of &quot;commercial  computer  software&quot;  and  &quot;commercial     *|&n;|*     computer  software  documentation,&quot;  as such  terms  are  used in     *|&n;|*     48 C.F.R. 12.212 (SEPT 1995)  and is provided to the U.S. Govern-     *|&n;|*     ment only as  a commercial end item.   Consistent with  48 C.F.R.     *|&n;|*     12.212 and  48 C.F.R. 227.7202-1 through  227.7202-4 (JUNE 1995),     *|&n;|*     all U.S. Government End Users  acquire the source code  with only     *|&n;|*     those rights set forth herein.                                        *|&n;|*                                                                           *|&n;&bslash;***************************************************************************/
multiline_comment|/*&n; * GPL licensing note -- nVidia is allowing a liberal interpretation of&n; * the documentation restriction above, to merely say that this nVidia&squot;s&n; * copyright and disclaimer should be included with all code derived&n; * from this source.  -- Jeff Garzik &lt;jgarzik@mandrakesoft.com&gt;, 01/Nov/99 &n; */
multiline_comment|/* $XFree86: xc/programs/Xserver/hw/xfree86/drivers/nv/riva_hw.h,v 1.6 2000/02/08 17:19:12 dawes Exp $ */
macro_line|#ifndef __RIVA_HW_H__
DECL|macro|__RIVA_HW_H__
mdefine_line|#define __RIVA_HW_H__
DECL|macro|RIVA_SW_VERSION
mdefine_line|#define RIVA_SW_VERSION 0x00010003
multiline_comment|/*&n; * Typedefs to force certain sized values.&n; */
DECL|typedef|U008
r_typedef
r_int
r_char
id|U008
suffix:semicolon
DECL|typedef|U016
r_typedef
r_int
r_int
id|U016
suffix:semicolon
DECL|typedef|U032
r_typedef
r_int
r_int
id|U032
suffix:semicolon
multiline_comment|/*&n; * HW access macros.&n; */
DECL|macro|NV_WR08
mdefine_line|#define NV_WR08(p,i,d)  (((U008 *)(p))[i]=(d))
DECL|macro|NV_RD08
mdefine_line|#define NV_RD08(p,i)    (((U008 *)(p))[i])
DECL|macro|NV_WR16
mdefine_line|#define NV_WR16(p,i,d)  (((U016 *)(p))[(i)/2]=(d))
DECL|macro|NV_RD16
mdefine_line|#define NV_RD16(p,i)    (((U016 *)(p))[(i)/2])
DECL|macro|NV_WR32
mdefine_line|#define NV_WR32(p,i,d)  (((U032 *)(p))[(i)/4]=(d))
DECL|macro|NV_RD32
mdefine_line|#define NV_RD32(p,i)    (((U032 *)(p))[(i)/4])
DECL|macro|VGA_WR08
mdefine_line|#define VGA_WR08(p,i,d) NV_WR08(p,i,d)
DECL|macro|VGA_RD08
mdefine_line|#define VGA_RD08(p,i)   NV_RD08(p,i)
multiline_comment|/*&n; * Define supported architectures.&n; */
DECL|macro|NV_ARCH_03
mdefine_line|#define NV_ARCH_03  0x03
DECL|macro|NV_ARCH_04
mdefine_line|#define NV_ARCH_04  0x04
DECL|macro|NV_ARCH_10
mdefine_line|#define NV_ARCH_10  0x10
DECL|macro|NV_ARCH_20
mdefine_line|#define NV_ARCH_20  0x20
multiline_comment|/***************************************************************************&bslash;&n;*                                                                           *&n;*                             FIFO registers.                               *&n;*                                                                           *&n;&bslash;***************************************************************************/
multiline_comment|/*&n; * Raster OPeration. Windows style ROP3.&n; */
r_typedef
r_volatile
r_struct
(brace
DECL|member|reserved00
id|U032
id|reserved00
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|FifoFree
id|U016
id|FifoFree
suffix:semicolon
DECL|member|Nop
id|U016
id|Nop
suffix:semicolon
DECL|member|reserved01
id|U032
id|reserved01
(braket
l_int|0x0BB
)braket
suffix:semicolon
DECL|member|Rop3
id|U032
id|Rop3
suffix:semicolon
DECL|typedef|RivaRop
)brace
id|RivaRop
suffix:semicolon
multiline_comment|/*&n; * 8X8 Monochrome pattern.&n; */
r_typedef
r_volatile
r_struct
(brace
DECL|member|reserved00
id|U032
id|reserved00
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|FifoFree
id|U016
id|FifoFree
suffix:semicolon
DECL|member|Nop
id|U016
id|Nop
suffix:semicolon
DECL|member|reserved01
id|U032
id|reserved01
(braket
l_int|0x0BD
)braket
suffix:semicolon
DECL|member|Shape
id|U032
id|Shape
suffix:semicolon
DECL|member|reserved03
id|U032
id|reserved03
(braket
l_int|0x001
)braket
suffix:semicolon
DECL|member|Color0
id|U032
id|Color0
suffix:semicolon
DECL|member|Color1
id|U032
id|Color1
suffix:semicolon
DECL|member|Monochrome
id|U032
id|Monochrome
(braket
l_int|2
)braket
suffix:semicolon
DECL|typedef|RivaPattern
)brace
id|RivaPattern
suffix:semicolon
multiline_comment|/*&n; * Scissor clip rectangle.&n; */
r_typedef
r_volatile
r_struct
(brace
DECL|member|reserved00
id|U032
id|reserved00
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|FifoFree
id|U016
id|FifoFree
suffix:semicolon
DECL|member|Nop
id|U016
id|Nop
suffix:semicolon
DECL|member|reserved01
id|U032
id|reserved01
(braket
l_int|0x0BB
)braket
suffix:semicolon
DECL|member|TopLeft
id|U032
id|TopLeft
suffix:semicolon
DECL|member|WidthHeight
id|U032
id|WidthHeight
suffix:semicolon
DECL|typedef|RivaClip
)brace
id|RivaClip
suffix:semicolon
multiline_comment|/*&n; * 2D filled rectangle.&n; */
r_typedef
r_volatile
r_struct
(brace
DECL|member|reserved00
id|U032
id|reserved00
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|FifoFree
id|U016
id|FifoFree
suffix:semicolon
DECL|member|Nop
id|U016
id|Nop
(braket
l_int|1
)braket
suffix:semicolon
DECL|member|reserved01
id|U032
id|reserved01
(braket
l_int|0x0BC
)braket
suffix:semicolon
DECL|member|Color
id|U032
id|Color
suffix:semicolon
DECL|member|reserved03
id|U032
id|reserved03
(braket
l_int|0x03E
)braket
suffix:semicolon
DECL|member|TopLeft
id|U032
id|TopLeft
suffix:semicolon
DECL|member|WidthHeight
id|U032
id|WidthHeight
suffix:semicolon
DECL|typedef|RivaRectangle
)brace
id|RivaRectangle
suffix:semicolon
multiline_comment|/*&n; * 2D screen-screen BLT.&n; */
r_typedef
r_volatile
r_struct
(brace
DECL|member|reserved00
id|U032
id|reserved00
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|FifoFree
id|U016
id|FifoFree
suffix:semicolon
DECL|member|Nop
id|U016
id|Nop
suffix:semicolon
DECL|member|reserved01
id|U032
id|reserved01
(braket
l_int|0x0BB
)braket
suffix:semicolon
DECL|member|TopLeftSrc
id|U032
id|TopLeftSrc
suffix:semicolon
DECL|member|TopLeftDst
id|U032
id|TopLeftDst
suffix:semicolon
DECL|member|WidthHeight
id|U032
id|WidthHeight
suffix:semicolon
DECL|typedef|RivaScreenBlt
)brace
id|RivaScreenBlt
suffix:semicolon
multiline_comment|/*&n; * 2D pixel BLT.&n; */
r_typedef
r_volatile
r_struct
(brace
DECL|member|reserved00
id|U032
id|reserved00
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|FifoFree
id|U016
id|FifoFree
suffix:semicolon
DECL|member|Nop
id|U016
id|Nop
(braket
l_int|1
)braket
suffix:semicolon
DECL|member|reserved01
id|U032
id|reserved01
(braket
l_int|0x0BC
)braket
suffix:semicolon
DECL|member|TopLeft
id|U032
id|TopLeft
suffix:semicolon
DECL|member|WidthHeight
id|U032
id|WidthHeight
suffix:semicolon
DECL|member|WidthHeightIn
id|U032
id|WidthHeightIn
suffix:semicolon
DECL|member|reserved02
id|U032
id|reserved02
(braket
l_int|0x03C
)braket
suffix:semicolon
DECL|member|Pixels
id|U032
id|Pixels
suffix:semicolon
DECL|typedef|RivaPixmap
)brace
id|RivaPixmap
suffix:semicolon
multiline_comment|/*&n; * Filled rectangle combined with monochrome expand.  Useful for glyphs.&n; */
r_typedef
r_volatile
r_struct
(brace
DECL|member|reserved00
id|U032
id|reserved00
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|FifoFree
id|U016
id|FifoFree
suffix:semicolon
DECL|member|Nop
id|U016
id|Nop
suffix:semicolon
DECL|member|reserved01
id|U032
id|reserved01
(braket
l_int|0x0BB
)braket
suffix:semicolon
DECL|member|reserved03
id|U032
id|reserved03
(braket
(paren
l_int|0x040
)paren
op_minus
l_int|1
)braket
suffix:semicolon
DECL|member|Color1A
id|U032
id|Color1A
suffix:semicolon
r_struct
(brace
DECL|member|TopLeft
id|U032
id|TopLeft
suffix:semicolon
DECL|member|WidthHeight
id|U032
id|WidthHeight
suffix:semicolon
DECL|member|UnclippedRectangle
)brace
id|UnclippedRectangle
(braket
l_int|64
)braket
suffix:semicolon
DECL|member|reserved04
id|U032
id|reserved04
(braket
(paren
l_int|0x080
)paren
op_minus
l_int|3
)braket
suffix:semicolon
r_struct
(brace
DECL|member|TopLeft
id|U032
id|TopLeft
suffix:semicolon
DECL|member|BottomRight
id|U032
id|BottomRight
suffix:semicolon
DECL|member|ClipB
)brace
id|ClipB
suffix:semicolon
DECL|member|Color1B
id|U032
id|Color1B
suffix:semicolon
r_struct
(brace
DECL|member|TopLeft
id|U032
id|TopLeft
suffix:semicolon
DECL|member|BottomRight
id|U032
id|BottomRight
suffix:semicolon
DECL|member|ClippedRectangle
)brace
id|ClippedRectangle
(braket
l_int|64
)braket
suffix:semicolon
DECL|member|reserved05
id|U032
id|reserved05
(braket
(paren
l_int|0x080
)paren
op_minus
l_int|5
)braket
suffix:semicolon
r_struct
(brace
DECL|member|TopLeft
id|U032
id|TopLeft
suffix:semicolon
DECL|member|BottomRight
id|U032
id|BottomRight
suffix:semicolon
DECL|member|ClipC
)brace
id|ClipC
suffix:semicolon
DECL|member|Color1C
id|U032
id|Color1C
suffix:semicolon
DECL|member|WidthHeightC
id|U032
id|WidthHeightC
suffix:semicolon
DECL|member|PointC
id|U032
id|PointC
suffix:semicolon
DECL|member|MonochromeData1C
id|U032
id|MonochromeData1C
suffix:semicolon
DECL|member|reserved06
id|U032
id|reserved06
(braket
(paren
l_int|0x080
)paren
op_plus
l_int|121
)braket
suffix:semicolon
r_struct
(brace
DECL|member|TopLeft
id|U032
id|TopLeft
suffix:semicolon
DECL|member|BottomRight
id|U032
id|BottomRight
suffix:semicolon
DECL|member|ClipD
)brace
id|ClipD
suffix:semicolon
DECL|member|Color1D
id|U032
id|Color1D
suffix:semicolon
DECL|member|WidthHeightInD
id|U032
id|WidthHeightInD
suffix:semicolon
DECL|member|WidthHeightOutD
id|U032
id|WidthHeightOutD
suffix:semicolon
DECL|member|PointD
id|U032
id|PointD
suffix:semicolon
DECL|member|MonochromeData1D
id|U032
id|MonochromeData1D
suffix:semicolon
DECL|member|reserved07
id|U032
id|reserved07
(braket
(paren
l_int|0x080
)paren
op_plus
l_int|120
)braket
suffix:semicolon
r_struct
(brace
DECL|member|TopLeft
id|U032
id|TopLeft
suffix:semicolon
DECL|member|BottomRight
id|U032
id|BottomRight
suffix:semicolon
DECL|member|ClipE
)brace
id|ClipE
suffix:semicolon
DECL|member|Color0E
id|U032
id|Color0E
suffix:semicolon
DECL|member|Color1E
id|U032
id|Color1E
suffix:semicolon
DECL|member|WidthHeightInE
id|U032
id|WidthHeightInE
suffix:semicolon
DECL|member|WidthHeightOutE
id|U032
id|WidthHeightOutE
suffix:semicolon
DECL|member|PointE
id|U032
id|PointE
suffix:semicolon
DECL|member|MonochromeData01E
id|U032
id|MonochromeData01E
suffix:semicolon
DECL|typedef|RivaBitmap
)brace
id|RivaBitmap
suffix:semicolon
multiline_comment|/*&n; * 3D textured, Z buffered triangle.&n; */
r_typedef
r_volatile
r_struct
(brace
DECL|member|reserved00
id|U032
id|reserved00
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|FifoFree
id|U016
id|FifoFree
suffix:semicolon
DECL|member|Nop
id|U016
id|Nop
suffix:semicolon
DECL|member|reserved01
id|U032
id|reserved01
(braket
l_int|0x0BC
)braket
suffix:semicolon
DECL|member|TextureOffset
id|U032
id|TextureOffset
suffix:semicolon
DECL|member|TextureFormat
id|U032
id|TextureFormat
suffix:semicolon
DECL|member|TextureFilter
id|U032
id|TextureFilter
suffix:semicolon
DECL|member|FogColor
id|U032
id|FogColor
suffix:semicolon
multiline_comment|/* This is a problem on LynxOS */
macro_line|#ifdef Control
DECL|macro|Control
macro_line|#undef Control
macro_line|#endif
DECL|member|Control
id|U032
id|Control
suffix:semicolon
DECL|member|AlphaTest
id|U032
id|AlphaTest
suffix:semicolon
DECL|member|reserved02
id|U032
id|reserved02
(braket
l_int|0x339
)braket
suffix:semicolon
DECL|member|FogAndIndex
id|U032
id|FogAndIndex
suffix:semicolon
DECL|member|Color
id|U032
id|Color
suffix:semicolon
DECL|member|ScreenX
r_float
id|ScreenX
suffix:semicolon
DECL|member|ScreenY
r_float
id|ScreenY
suffix:semicolon
DECL|member|ScreenZ
r_float
id|ScreenZ
suffix:semicolon
DECL|member|EyeM
r_float
id|EyeM
suffix:semicolon
DECL|member|TextureS
r_float
id|TextureS
suffix:semicolon
DECL|member|TextureT
r_float
id|TextureT
suffix:semicolon
DECL|typedef|RivaTexturedTriangle03
)brace
id|RivaTexturedTriangle03
suffix:semicolon
r_typedef
r_volatile
r_struct
(brace
DECL|member|reserved00
id|U032
id|reserved00
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|FifoFree
id|U016
id|FifoFree
suffix:semicolon
DECL|member|Nop
id|U016
id|Nop
suffix:semicolon
DECL|member|reserved01
id|U032
id|reserved01
(braket
l_int|0x0BB
)braket
suffix:semicolon
DECL|member|ColorKey
id|U032
id|ColorKey
suffix:semicolon
DECL|member|TextureOffset
id|U032
id|TextureOffset
suffix:semicolon
DECL|member|TextureFormat
id|U032
id|TextureFormat
suffix:semicolon
DECL|member|TextureFilter
id|U032
id|TextureFilter
suffix:semicolon
DECL|member|Blend
id|U032
id|Blend
suffix:semicolon
multiline_comment|/* This is a problem on LynxOS */
macro_line|#ifdef Control
DECL|macro|Control
macro_line|#undef Control
macro_line|#endif
DECL|member|Control
id|U032
id|Control
suffix:semicolon
DECL|member|FogColor
id|U032
id|FogColor
suffix:semicolon
DECL|member|reserved02
id|U032
id|reserved02
(braket
l_int|0x39
)braket
suffix:semicolon
r_struct
(brace
DECL|member|ScreenX
r_float
id|ScreenX
suffix:semicolon
DECL|member|ScreenY
r_float
id|ScreenY
suffix:semicolon
DECL|member|ScreenZ
r_float
id|ScreenZ
suffix:semicolon
DECL|member|EyeM
r_float
id|EyeM
suffix:semicolon
DECL|member|Color
id|U032
id|Color
suffix:semicolon
DECL|member|Specular
id|U032
id|Specular
suffix:semicolon
DECL|member|TextureS
r_float
id|TextureS
suffix:semicolon
DECL|member|TextureT
r_float
id|TextureT
suffix:semicolon
DECL|member|Vertex
)brace
id|Vertex
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|DrawTriangle3D
id|U032
id|DrawTriangle3D
suffix:semicolon
DECL|typedef|RivaTexturedTriangle05
)brace
id|RivaTexturedTriangle05
suffix:semicolon
multiline_comment|/*&n; * 2D line.&n; */
r_typedef
r_volatile
r_struct
(brace
DECL|member|reserved00
id|U032
id|reserved00
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|FifoFree
id|U016
id|FifoFree
suffix:semicolon
DECL|member|Nop
id|U016
id|Nop
(braket
l_int|1
)braket
suffix:semicolon
DECL|member|reserved01
id|U032
id|reserved01
(braket
l_int|0x0BC
)braket
suffix:semicolon
DECL|member|Color
id|U032
id|Color
suffix:semicolon
multiline_comment|/* source color               0304-0307*/
DECL|member|Reserved02
id|U032
id|Reserved02
(braket
l_int|0x03e
)braket
suffix:semicolon
r_struct
(brace
multiline_comment|/* start aliased methods in array   0400-    */
DECL|member|point0
id|U032
id|point0
suffix:semicolon
multiline_comment|/* y_x S16_S16 in pixels            0-   3*/
DECL|member|point1
id|U032
id|point1
suffix:semicolon
multiline_comment|/* y_x S16_S16 in pixels            4-   7*/
DECL|member|Lin
)brace
id|Lin
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* end of aliased methods in array      -047f*/
r_struct
(brace
multiline_comment|/* start aliased methods in array   0480-    */
DECL|member|point0X
id|U032
id|point0X
suffix:semicolon
multiline_comment|/* in pixels, 0 at left                0-   3*/
DECL|member|point0Y
id|U032
id|point0Y
suffix:semicolon
multiline_comment|/* in pixels, 0 at top                 4-   7*/
DECL|member|point1X
id|U032
id|point1X
suffix:semicolon
multiline_comment|/* in pixels, 0 at left                8-   b*/
DECL|member|point1Y
id|U032
id|point1Y
suffix:semicolon
multiline_comment|/* in pixels, 0 at top                 c-   f*/
DECL|member|Lin32
)brace
id|Lin32
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* end of aliased methods in array      -04ff*/
DECL|member|PolyLin
id|U032
id|PolyLin
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* y_x S16_S16 in pixels         0500-057f*/
r_struct
(brace
multiline_comment|/* start aliased methods in array   0580-    */
DECL|member|x
id|U032
id|x
suffix:semicolon
multiline_comment|/* in pixels, 0 at left                0-   3*/
DECL|member|y
id|U032
id|y
suffix:semicolon
multiline_comment|/* in pixels, 0 at top                 4-   7*/
DECL|member|PolyLin32
)brace
id|PolyLin32
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* end of aliased methods in array      -05ff*/
r_struct
(brace
multiline_comment|/* start aliased methods in array   0600-    */
DECL|member|color
id|U032
id|color
suffix:semicolon
multiline_comment|/* source color                     0-   3*/
DECL|member|point
id|U032
id|point
suffix:semicolon
multiline_comment|/* y_x S16_S16 in pixels            4-   7*/
DECL|member|ColorPolyLin
)brace
id|ColorPolyLin
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* end of aliased methods in array      -067f*/
DECL|typedef|RivaLine
)brace
id|RivaLine
suffix:semicolon
multiline_comment|/*&n; * 2D/3D surfaces&n; */
r_typedef
r_volatile
r_struct
(brace
DECL|member|reserved00
id|U032
id|reserved00
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|FifoFree
id|U016
id|FifoFree
suffix:semicolon
DECL|member|Nop
id|U016
id|Nop
suffix:semicolon
DECL|member|reserved01
id|U032
id|reserved01
(braket
l_int|0x0BE
)braket
suffix:semicolon
DECL|member|Offset
id|U032
id|Offset
suffix:semicolon
DECL|typedef|RivaSurface
)brace
id|RivaSurface
suffix:semicolon
r_typedef
r_volatile
r_struct
(brace
DECL|member|reserved00
id|U032
id|reserved00
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|FifoFree
id|U016
id|FifoFree
suffix:semicolon
DECL|member|Nop
id|U016
id|Nop
suffix:semicolon
DECL|member|reserved01
id|U032
id|reserved01
(braket
l_int|0x0BD
)braket
suffix:semicolon
DECL|member|Pitch
id|U032
id|Pitch
suffix:semicolon
DECL|member|RenderBufferOffset
id|U032
id|RenderBufferOffset
suffix:semicolon
DECL|member|ZBufferOffset
id|U032
id|ZBufferOffset
suffix:semicolon
DECL|typedef|RivaSurface3D
)brace
id|RivaSurface3D
suffix:semicolon
multiline_comment|/***************************************************************************&bslash;&n;*                                                                           *&n;*                        Virtualized RIVA H/W interface.                    *&n;*                                                                           *&n;&bslash;***************************************************************************/
r_struct
id|_riva_hw_inst
suffix:semicolon
r_struct
id|_riva_hw_state
suffix:semicolon
multiline_comment|/*&n; * Virtialized chip interface. Makes RIVA 128 and TNT look alike.&n; */
DECL|struct|_riva_hw_inst
r_typedef
r_struct
id|_riva_hw_inst
(brace
multiline_comment|/*&n;     * Chip specific settings.&n;     */
DECL|member|Architecture
id|U032
id|Architecture
suffix:semicolon
DECL|member|Version
id|U032
id|Version
suffix:semicolon
DECL|member|CrystalFreqKHz
id|U032
id|CrystalFreqKHz
suffix:semicolon
DECL|member|RamAmountKBytes
id|U032
id|RamAmountKBytes
suffix:semicolon
DECL|member|MaxVClockFreqKHz
id|U032
id|MaxVClockFreqKHz
suffix:semicolon
DECL|member|RamBandwidthKBytesPerSec
id|U032
id|RamBandwidthKBytesPerSec
suffix:semicolon
DECL|member|EnableIRQ
id|U032
id|EnableIRQ
suffix:semicolon
DECL|member|IO
id|U032
id|IO
suffix:semicolon
DECL|member|VBlankBit
id|U032
id|VBlankBit
suffix:semicolon
DECL|member|FifoFreeCount
id|U032
id|FifoFreeCount
suffix:semicolon
DECL|member|FifoEmptyCount
id|U032
id|FifoEmptyCount
suffix:semicolon
multiline_comment|/*&n;     * Non-FIFO registers.&n;     */
DECL|member|PCRTC
r_volatile
id|U032
op_star
id|PCRTC
suffix:semicolon
DECL|member|PRAMDAC
r_volatile
id|U032
op_star
id|PRAMDAC
suffix:semicolon
DECL|member|PFB
r_volatile
id|U032
op_star
id|PFB
suffix:semicolon
DECL|member|PFIFO
r_volatile
id|U032
op_star
id|PFIFO
suffix:semicolon
DECL|member|PGRAPH
r_volatile
id|U032
op_star
id|PGRAPH
suffix:semicolon
DECL|member|PEXTDEV
r_volatile
id|U032
op_star
id|PEXTDEV
suffix:semicolon
DECL|member|PTIMER
r_volatile
id|U032
op_star
id|PTIMER
suffix:semicolon
DECL|member|PMC
r_volatile
id|U032
op_star
id|PMC
suffix:semicolon
DECL|member|PRAMIN
r_volatile
id|U032
op_star
id|PRAMIN
suffix:semicolon
DECL|member|FIFO
r_volatile
id|U032
op_star
id|FIFO
suffix:semicolon
DECL|member|CURSOR
r_volatile
id|U032
op_star
id|CURSOR
suffix:semicolon
DECL|member|CURSORPOS
r_volatile
id|U032
op_star
id|CURSORPOS
suffix:semicolon
DECL|member|VBLANKENABLE
r_volatile
id|U032
op_star
id|VBLANKENABLE
suffix:semicolon
DECL|member|VBLANK
r_volatile
id|U032
op_star
id|VBLANK
suffix:semicolon
DECL|member|PCIO
r_volatile
id|U008
op_star
id|PCIO
suffix:semicolon
DECL|member|PVIO
r_volatile
id|U008
op_star
id|PVIO
suffix:semicolon
DECL|member|PDIO
r_volatile
id|U008
op_star
id|PDIO
suffix:semicolon
multiline_comment|/*&n;     * Common chip functions.&n;     */
DECL|member|Busy
r_int
(paren
op_star
id|Busy
)paren
(paren
r_struct
id|_riva_hw_inst
op_star
)paren
suffix:semicolon
DECL|member|CalcStateExt
r_void
(paren
op_star
id|CalcStateExt
)paren
(paren
r_struct
id|_riva_hw_inst
op_star
comma
r_struct
id|_riva_hw_state
op_star
comma
r_int
comma
r_int
comma
r_int
comma
r_int
comma
r_int
comma
r_int
comma
r_int
comma
r_int
comma
r_int
comma
r_int
comma
r_int
comma
r_int
comma
r_int
)paren
suffix:semicolon
DECL|member|LoadStateExt
r_void
(paren
op_star
id|LoadStateExt
)paren
(paren
r_struct
id|_riva_hw_inst
op_star
comma
r_struct
id|_riva_hw_state
op_star
)paren
suffix:semicolon
DECL|member|UnloadStateExt
r_void
(paren
op_star
id|UnloadStateExt
)paren
(paren
r_struct
id|_riva_hw_inst
op_star
comma
r_struct
id|_riva_hw_state
op_star
)paren
suffix:semicolon
DECL|member|SetStartAddress
r_void
(paren
op_star
id|SetStartAddress
)paren
(paren
r_struct
id|_riva_hw_inst
op_star
comma
id|U032
)paren
suffix:semicolon
DECL|member|SetSurfaces2D
r_void
(paren
op_star
id|SetSurfaces2D
)paren
(paren
r_struct
id|_riva_hw_inst
op_star
comma
id|U032
comma
id|U032
)paren
suffix:semicolon
DECL|member|SetSurfaces3D
r_void
(paren
op_star
id|SetSurfaces3D
)paren
(paren
r_struct
id|_riva_hw_inst
op_star
comma
id|U032
comma
id|U032
)paren
suffix:semicolon
DECL|member|ShowHideCursor
r_int
(paren
op_star
id|ShowHideCursor
)paren
(paren
r_struct
id|_riva_hw_inst
op_star
comma
r_int
)paren
suffix:semicolon
DECL|member|LockUnlock
r_void
(paren
op_star
id|LockUnlock
)paren
(paren
r_struct
id|_riva_hw_inst
op_star
comma
r_int
)paren
suffix:semicolon
multiline_comment|/*&n;     * Current extended mode settings.&n;     */
DECL|member|CurrentState
r_struct
id|_riva_hw_state
op_star
id|CurrentState
suffix:semicolon
multiline_comment|/*&n;     * FIFO registers.&n;     */
DECL|member|Rop
id|RivaRop
op_star
id|Rop
suffix:semicolon
DECL|member|Patt
id|RivaPattern
op_star
id|Patt
suffix:semicolon
DECL|member|Clip
id|RivaClip
op_star
id|Clip
suffix:semicolon
DECL|member|Pixmap
id|RivaPixmap
op_star
id|Pixmap
suffix:semicolon
DECL|member|Blt
id|RivaScreenBlt
op_star
id|Blt
suffix:semicolon
DECL|member|Bitmap
id|RivaBitmap
op_star
id|Bitmap
suffix:semicolon
DECL|member|Line
id|RivaLine
op_star
id|Line
suffix:semicolon
DECL|member|Tri03
id|RivaTexturedTriangle03
op_star
id|Tri03
suffix:semicolon
DECL|member|Tri05
id|RivaTexturedTriangle05
op_star
id|Tri05
suffix:semicolon
DECL|typedef|RIVA_HW_INST
)brace
id|RIVA_HW_INST
suffix:semicolon
multiline_comment|/*&n; * Extended mode state information.&n; */
DECL|struct|_riva_hw_state
r_typedef
r_struct
id|_riva_hw_state
(brace
DECL|member|bpp
id|U032
id|bpp
suffix:semicolon
DECL|member|width
id|U032
id|width
suffix:semicolon
DECL|member|height
id|U032
id|height
suffix:semicolon
DECL|member|repaint0
id|U032
id|repaint0
suffix:semicolon
DECL|member|repaint1
id|U032
id|repaint1
suffix:semicolon
DECL|member|screen
id|U032
id|screen
suffix:semicolon
DECL|member|pixel
id|U032
id|pixel
suffix:semicolon
DECL|member|horiz
id|U032
id|horiz
suffix:semicolon
DECL|member|arbitration0
id|U032
id|arbitration0
suffix:semicolon
DECL|member|arbitration1
id|U032
id|arbitration1
suffix:semicolon
DECL|member|vpll
id|U032
id|vpll
suffix:semicolon
DECL|member|pllsel
id|U032
id|pllsel
suffix:semicolon
DECL|member|general
id|U032
id|general
suffix:semicolon
DECL|member|config
id|U032
id|config
suffix:semicolon
DECL|member|cursor0
id|U032
id|cursor0
suffix:semicolon
DECL|member|cursor1
id|U032
id|cursor1
suffix:semicolon
DECL|member|cursor2
id|U032
id|cursor2
suffix:semicolon
DECL|member|offset0
id|U032
id|offset0
suffix:semicolon
DECL|member|offset1
id|U032
id|offset1
suffix:semicolon
DECL|member|offset2
id|U032
id|offset2
suffix:semicolon
DECL|member|offset3
id|U032
id|offset3
suffix:semicolon
DECL|member|pitch0
id|U032
id|pitch0
suffix:semicolon
DECL|member|pitch1
id|U032
id|pitch1
suffix:semicolon
DECL|member|pitch2
id|U032
id|pitch2
suffix:semicolon
DECL|member|pitch3
id|U032
id|pitch3
suffix:semicolon
DECL|typedef|RIVA_HW_STATE
)brace
id|RIVA_HW_STATE
suffix:semicolon
multiline_comment|/*&n; * External routines.&n; */
r_int
id|RivaGetConfig
c_func
(paren
id|RIVA_HW_INST
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * FIFO Free Count. Should attempt to yield processor if RIVA is busy.&n; */
DECL|macro|RIVA_FIFO_FREE
mdefine_line|#define RIVA_FIFO_FREE(hwinst,hwptr,cnt)                           &bslash;&n;{                                                                  &bslash;&n;   while ((hwinst).FifoFreeCount &lt; (cnt))                          &bslash;&n;&t;(hwinst).FifoFreeCount = (hwinst).hwptr-&gt;FifoFree &gt;&gt; 2;        &bslash;&n;   (hwinst).FifoFreeCount -= (cnt);                                &bslash;&n;}
macro_line|#endif /* __RIVA_HW_H__ */
eof
