multiline_comment|/***************************************************************************&bslash;&n;|*                                                                           *|&n;|*       Copyright 2003 NVIDIA, Corporation.  All rights reserved.           *|&n;|*                                                                           *|&n;|*     NOTICE TO USER:   The source code  is copyrighted under  U.S. and     *|&n;|*     international laws.  Users and possessors of this source code are     *|&n;|*     hereby granted a nonexclusive,  royalty-free copyright license to     *|&n;|*     use this code in individual and commercial software.                  *|&n;|*                                                                           *|&n;|*     Any use of this source code must include,  in the user documenta-     *|&n;|*     tion and  internal comments to the code,  notices to the end user     *|&n;|*     as follows:                                                           *|&n;|*                                                                           *|&n;|*       Copyright 2003 NVIDIA, Corporation.  All rights reserved.           *|&n;|*                                                                           *|&n;|*     NVIDIA, CORPORATION MAKES NO REPRESENTATION ABOUT THE SUITABILITY     *|&n;|*     OF  THIS SOURCE  CODE  FOR ANY PURPOSE.  IT IS  PROVIDED  &quot;AS IS&quot;     *|&n;|*     WITHOUT EXPRESS OR IMPLIED WARRANTY OF ANY KIND.  NVIDIA, CORPOR-     *|&n;|*     ATION DISCLAIMS ALL WARRANTIES  WITH REGARD  TO THIS SOURCE CODE,     *|&n;|*     INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY, NONINFRINGE-     *|&n;|*     MENT,  AND FITNESS  FOR A PARTICULAR PURPOSE.   IN NO EVENT SHALL     *|&n;|*     NVIDIA, CORPORATION  BE LIABLE FOR ANY SPECIAL,  INDIRECT,  INCI-     *|&n;|*     DENTAL, OR CONSEQUENTIAL DAMAGES,  OR ANY DAMAGES  WHATSOEVER RE-     *|&n;|*     SULTING FROM LOSS OF USE,  DATA OR PROFITS,  WHETHER IN AN ACTION     *|&n;|*     OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,  ARISING OUT OF     *|&n;|*     OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOURCE CODE.     *|&n;|*                                                                           *|&n;|*     U.S. Government  End  Users.   This source code  is a &quot;commercial     *|&n;|*     item,&quot;  as that  term is  defined at  48 C.F.R. 2.101 (OCT 1995),     *|&n;|*     consisting  of &quot;commercial  computer  software&quot;  and  &quot;commercial     *|&n;|*     computer  software  documentation,&quot;  as such  terms  are  used in     *|&n;|*     48 C.F.R. 12.212 (SEPT 1995)  and is provided to the U.S. Govern-     *|&n;|*     ment only as  a commercial end item.   Consistent with  48 C.F.R.     *|&n;|*     12.212 and  48 C.F.R. 227.7202-1 through  227.7202-4 (JUNE 1995),     *|&n;|*     all U.S. Government End Users  acquire the source code  with only     *|&n;|*     those rights set forth herein.                                        *|&n;|*                                                                           *|&n; &bslash;***************************************************************************/
multiline_comment|/*&n; * GPL Licensing Note - According to Mark Vojkovich, author of the Xorg/&n; * XFree86 &squot;nv&squot; driver, this source code is provided under MIT-style licensing&n; * where the source code is provided &quot;as is&quot; without warranty of any kind.&n; * The only usage restriction is for the copyright notices to be retained&n; * whenever code is used.&n; *&n; * Antonino Daplas &lt;adaplas@pol.net&gt; 2005-03-11&n; */
DECL|macro|SURFACE_FORMAT
mdefine_line|#define SURFACE_FORMAT                                              0x00000300
DECL|macro|SURFACE_FORMAT_DEPTH8
mdefine_line|#define SURFACE_FORMAT_DEPTH8                                       0x00000001
DECL|macro|SURFACE_FORMAT_DEPTH15
mdefine_line|#define SURFACE_FORMAT_DEPTH15                                      0x00000002
DECL|macro|SURFACE_FORMAT_DEPTH16
mdefine_line|#define SURFACE_FORMAT_DEPTH16                                      0x00000004
DECL|macro|SURFACE_FORMAT_DEPTH24
mdefine_line|#define SURFACE_FORMAT_DEPTH24                                      0x00000006
DECL|macro|SURFACE_PITCH
mdefine_line|#define SURFACE_PITCH                                               0x00000304
DECL|macro|SURFACE_PITCH_SRC
mdefine_line|#define SURFACE_PITCH_SRC                                           15:0
DECL|macro|SURFACE_PITCH_DST
mdefine_line|#define SURFACE_PITCH_DST                                           31:16
DECL|macro|SURFACE_OFFSET_SRC
mdefine_line|#define SURFACE_OFFSET_SRC                                          0x00000308
DECL|macro|SURFACE_OFFSET_DST
mdefine_line|#define SURFACE_OFFSET_DST                                          0x0000030C
DECL|macro|ROP_SET
mdefine_line|#define ROP_SET                                                     0x00002300
DECL|macro|PATTERN_FORMAT
mdefine_line|#define PATTERN_FORMAT                                              0x00004300
DECL|macro|PATTERN_FORMAT_DEPTH8
mdefine_line|#define PATTERN_FORMAT_DEPTH8                                       0x00000003
DECL|macro|PATTERN_FORMAT_DEPTH16
mdefine_line|#define PATTERN_FORMAT_DEPTH16                                      0x00000001
DECL|macro|PATTERN_FORMAT_DEPTH24
mdefine_line|#define PATTERN_FORMAT_DEPTH24                                      0x00000003
DECL|macro|PATTERN_COLOR_0
mdefine_line|#define PATTERN_COLOR_0                                             0x00004310
DECL|macro|PATTERN_COLOR_1
mdefine_line|#define PATTERN_COLOR_1                                             0x00004314
DECL|macro|PATTERN_PATTERN_0
mdefine_line|#define PATTERN_PATTERN_0                                           0x00004318
DECL|macro|PATTERN_PATTERN_1
mdefine_line|#define PATTERN_PATTERN_1                                           0x0000431C
DECL|macro|CLIP_POINT
mdefine_line|#define CLIP_POINT                                                  0x00006300
DECL|macro|CLIP_POINT_X
mdefine_line|#define CLIP_POINT_X                                                15:0
DECL|macro|CLIP_POINT_Y
mdefine_line|#define CLIP_POINT_Y                                                31:16
DECL|macro|CLIP_SIZE
mdefine_line|#define CLIP_SIZE                                                   0x00006304
DECL|macro|CLIP_SIZE_WIDTH
mdefine_line|#define CLIP_SIZE_WIDTH                                             15:0
DECL|macro|CLIP_SIZE_HEIGHT
mdefine_line|#define CLIP_SIZE_HEIGHT                                            31:16
DECL|macro|LINE_FORMAT
mdefine_line|#define LINE_FORMAT                                                 0x00008300
DECL|macro|LINE_FORMAT_DEPTH8
mdefine_line|#define LINE_FORMAT_DEPTH8                                          0x00000003
DECL|macro|LINE_FORMAT_DEPTH16
mdefine_line|#define LINE_FORMAT_DEPTH16                                         0x00000001
DECL|macro|LINE_FORMAT_DEPTH24
mdefine_line|#define LINE_FORMAT_DEPTH24                                         0x00000003
DECL|macro|LINE_COLOR
mdefine_line|#define LINE_COLOR                                                  0x00008304
DECL|macro|LINE_MAX_LINES
mdefine_line|#define LINE_MAX_LINES                                              16
DECL|macro|LINE_LINES
mdefine_line|#define LINE_LINES(i)                                               0x00008400&bslash;&n;                                                                    +(i)*8
DECL|macro|LINE_LINES_POINT0_X
mdefine_line|#define LINE_LINES_POINT0_X                                         15:0
DECL|macro|LINE_LINES_POINT0_Y
mdefine_line|#define LINE_LINES_POINT0_Y                                         31:16
DECL|macro|LINE_LINES_POINT1_X
mdefine_line|#define LINE_LINES_POINT1_X                                         47:32
DECL|macro|LINE_LINES_POINT1_Y
mdefine_line|#define LINE_LINES_POINT1_Y                                         63:48
DECL|macro|BLIT_POINT_SRC
mdefine_line|#define BLIT_POINT_SRC                                              0x0000A300
DECL|macro|BLIT_POINT_SRC_X
mdefine_line|#define BLIT_POINT_SRC_X                                            15:0
DECL|macro|BLIT_POINT_SRC_Y
mdefine_line|#define BLIT_POINT_SRC_Y                                            31:16
DECL|macro|BLIT_POINT_DST
mdefine_line|#define BLIT_POINT_DST                                              0x0000A304
DECL|macro|BLIT_POINT_DST_X
mdefine_line|#define BLIT_POINT_DST_X                                            15:0
DECL|macro|BLIT_POINT_DST_Y
mdefine_line|#define BLIT_POINT_DST_Y                                            31:16
DECL|macro|BLIT_SIZE
mdefine_line|#define BLIT_SIZE                                                   0x0000A308
DECL|macro|BLIT_SIZE_WIDTH
mdefine_line|#define BLIT_SIZE_WIDTH                                             15:0
DECL|macro|BLIT_SIZE_HEIGHT
mdefine_line|#define BLIT_SIZE_HEIGHT                                            31:16
DECL|macro|RECT_FORMAT
mdefine_line|#define RECT_FORMAT                                                 0x0000C300
DECL|macro|RECT_FORMAT_DEPTH8
mdefine_line|#define RECT_FORMAT_DEPTH8                                          0x00000003
DECL|macro|RECT_FORMAT_DEPTH16
mdefine_line|#define RECT_FORMAT_DEPTH16                                         0x00000001
DECL|macro|RECT_FORMAT_DEPTH24
mdefine_line|#define RECT_FORMAT_DEPTH24                                         0x00000003
DECL|macro|RECT_SOLID_COLOR
mdefine_line|#define RECT_SOLID_COLOR                                            0x0000C3FC
DECL|macro|RECT_SOLID_RECTS_MAX_RECTS
mdefine_line|#define RECT_SOLID_RECTS_MAX_RECTS                                  32
DECL|macro|RECT_SOLID_RECTS
mdefine_line|#define RECT_SOLID_RECTS(i)                                         0x0000C400&bslash;&n;                                                                    +(i)*8
DECL|macro|RECT_SOLID_RECTS_Y
mdefine_line|#define RECT_SOLID_RECTS_Y                                          15:0
DECL|macro|RECT_SOLID_RECTS_X
mdefine_line|#define RECT_SOLID_RECTS_X                                          31:16
DECL|macro|RECT_SOLID_RECTS_HEIGHT
mdefine_line|#define RECT_SOLID_RECTS_HEIGHT                                     47:32
DECL|macro|RECT_SOLID_RECTS_WIDTH
mdefine_line|#define RECT_SOLID_RECTS_WIDTH                                      63:48
DECL|macro|RECT_EXPAND_ONE_COLOR_CLIP
mdefine_line|#define RECT_EXPAND_ONE_COLOR_CLIP                                  0x0000C7EC
DECL|macro|RECT_EXPAND_ONE_COLOR_CLIP_POINT0_X
mdefine_line|#define RECT_EXPAND_ONE_COLOR_CLIP_POINT0_X                         15:0
DECL|macro|RECT_EXPAND_ONE_COLOR_CLIP_POINT0_Y
mdefine_line|#define RECT_EXPAND_ONE_COLOR_CLIP_POINT0_Y                         31:16
DECL|macro|RECT_EXPAND_ONE_COLOR_CLIP_POINT1_X
mdefine_line|#define RECT_EXPAND_ONE_COLOR_CLIP_POINT1_X                         47:32
DECL|macro|RECT_EXPAND_ONE_COLOR_CLIP_POINT1_Y
mdefine_line|#define RECT_EXPAND_ONE_COLOR_CLIP_POINT1_Y                         63:48
DECL|macro|RECT_EXPAND_ONE_COLOR_COLOR
mdefine_line|#define RECT_EXPAND_ONE_COLOR_COLOR                                 0x0000C7F4
DECL|macro|RECT_EXPAND_ONE_COLOR_SIZE
mdefine_line|#define RECT_EXPAND_ONE_COLOR_SIZE                                  0x0000C7F8
DECL|macro|RECT_EXPAND_ONE_COLOR_SIZE_WIDTH
mdefine_line|#define RECT_EXPAND_ONE_COLOR_SIZE_WIDTH                            15:0
DECL|macro|RECT_EXPAND_ONE_COLOR_SIZE_HEIGHT
mdefine_line|#define RECT_EXPAND_ONE_COLOR_SIZE_HEIGHT                           31:16
DECL|macro|RECT_EXPAND_ONE_COLOR_POINT
mdefine_line|#define RECT_EXPAND_ONE_COLOR_POINT                                 0x0000C7FC
DECL|macro|RECT_EXPAND_ONE_COLOR_POINT_X
mdefine_line|#define RECT_EXPAND_ONE_COLOR_POINT_X                               15:0
DECL|macro|RECT_EXPAND_ONE_COLOR_POINT_Y
mdefine_line|#define RECT_EXPAND_ONE_COLOR_POINT_Y                               31:16
DECL|macro|RECT_EXPAND_ONE_COLOR_DATA_MAX_DWORDS
mdefine_line|#define RECT_EXPAND_ONE_COLOR_DATA_MAX_DWORDS                       128
DECL|macro|RECT_EXPAND_ONE_COLOR_DATA
mdefine_line|#define RECT_EXPAND_ONE_COLOR_DATA(i)                               0x0000C800&bslash;&n;                                                                    +(i)*4
DECL|macro|RECT_EXPAND_TWO_COLOR_CLIP
mdefine_line|#define RECT_EXPAND_TWO_COLOR_CLIP                                  0x0000CBE4
DECL|macro|RECT_EXPAND_TWO_COLOR_CLIP_POINT0_X
mdefine_line|#define RECT_EXPAND_TWO_COLOR_CLIP_POINT0_X                         15:0
DECL|macro|RECT_EXPAND_TWO_COLOR_CLIP_POINT0_Y
mdefine_line|#define RECT_EXPAND_TWO_COLOR_CLIP_POINT0_Y                         31:16
DECL|macro|RECT_EXPAND_TWO_COLOR_CLIP_POINT1_X
mdefine_line|#define RECT_EXPAND_TWO_COLOR_CLIP_POINT1_X                         47:32
DECL|macro|RECT_EXPAND_TWO_COLOR_CLIP_POINT1_Y
mdefine_line|#define RECT_EXPAND_TWO_COLOR_CLIP_POINT1_Y                         63:48
DECL|macro|RECT_EXPAND_TWO_COLOR_COLOR_0
mdefine_line|#define RECT_EXPAND_TWO_COLOR_COLOR_0                               0x0000CBEC
DECL|macro|RECT_EXPAND_TWO_COLOR_COLOR_1
mdefine_line|#define RECT_EXPAND_TWO_COLOR_COLOR_1                               0x0000CBF0
DECL|macro|RECT_EXPAND_TWO_COLOR_SIZE_IN
mdefine_line|#define RECT_EXPAND_TWO_COLOR_SIZE_IN                               0x0000CBF4
DECL|macro|RECT_EXPAND_TWO_COLOR_SIZE_IN_WIDTH
mdefine_line|#define RECT_EXPAND_TWO_COLOR_SIZE_IN_WIDTH                         15:0
DECL|macro|RECT_EXPAND_TWO_COLOR_SIZE_IN_HEIGHT
mdefine_line|#define RECT_EXPAND_TWO_COLOR_SIZE_IN_HEIGHT                        31:16
DECL|macro|RECT_EXPAND_TWO_COLOR_SIZE_OUT
mdefine_line|#define RECT_EXPAND_TWO_COLOR_SIZE_OUT                              0x0000CBF8
DECL|macro|RECT_EXPAND_TWO_COLOR_SIZE_OUT_WIDTH
mdefine_line|#define RECT_EXPAND_TWO_COLOR_SIZE_OUT_WIDTH                        15:0
DECL|macro|RECT_EXPAND_TWO_COLOR_SIZE_OUT_HEIGHT
mdefine_line|#define RECT_EXPAND_TWO_COLOR_SIZE_OUT_HEIGHT                       31:16
DECL|macro|RECT_EXPAND_TWO_COLOR_POINT
mdefine_line|#define RECT_EXPAND_TWO_COLOR_POINT                                 0x0000CBFC
DECL|macro|RECT_EXPAND_TWO_COLOR_POINT_X
mdefine_line|#define RECT_EXPAND_TWO_COLOR_POINT_X                               15:0
DECL|macro|RECT_EXPAND_TWO_COLOR_POINT_Y
mdefine_line|#define RECT_EXPAND_TWO_COLOR_POINT_Y                               31:16
DECL|macro|RECT_EXPAND_TWO_COLOR_DATA_MAX_DWORDS
mdefine_line|#define RECT_EXPAND_TWO_COLOR_DATA_MAX_DWORDS                       128
DECL|macro|RECT_EXPAND_TWO_COLOR_DATA
mdefine_line|#define RECT_EXPAND_TWO_COLOR_DATA(i)                               0x0000CC00&bslash;&n;                                                                    +(i)*4
DECL|macro|STRETCH_BLIT_FORMAT
mdefine_line|#define STRETCH_BLIT_FORMAT                                         0x0000E300
DECL|macro|STRETCH_BLIT_FORMAT_DEPTH8
mdefine_line|#define STRETCH_BLIT_FORMAT_DEPTH8                                  0x00000004
DECL|macro|STRETCH_BLIT_FORMAT_DEPTH16
mdefine_line|#define STRETCH_BLIT_FORMAT_DEPTH16                                 0x00000007
DECL|macro|STRETCH_BLIT_FORMAT_DEPTH24
mdefine_line|#define STRETCH_BLIT_FORMAT_DEPTH24                                 0x00000004
DECL|macro|STRETCH_BLIT_FORMAT_X8R8G8B8
mdefine_line|#define STRETCH_BLIT_FORMAT_X8R8G8B8                                0x00000004
DECL|macro|STRETCH_BLIT_FORMAT_YUYV
mdefine_line|#define STRETCH_BLIT_FORMAT_YUYV                                    0x00000005
DECL|macro|STRETCH_BLIT_FORMAT_UYVY
mdefine_line|#define STRETCH_BLIT_FORMAT_UYVY                                    0x00000006
DECL|macro|STRETCH_BLIT_CLIP_POINT
mdefine_line|#define STRETCH_BLIT_CLIP_POINT                                     0x0000E308
DECL|macro|STRETCH_BLIT_CLIP_POINT_X
mdefine_line|#define STRETCH_BLIT_CLIP_POINT_X                                   15:0
DECL|macro|STRETCH_BLIT_CLIP_POINT_Y
mdefine_line|#define STRETCH_BLIT_CLIP_POINT_Y                                   31:16
DECL|macro|STRETCH_BLIT_CLIP_POINT
mdefine_line|#define STRETCH_BLIT_CLIP_POINT                                     0x0000E308
DECL|macro|STRETCH_BLIT_CLIP_SIZE
mdefine_line|#define STRETCH_BLIT_CLIP_SIZE                                      0x0000E30C
DECL|macro|STRETCH_BLIT_CLIP_SIZE_WIDTH
mdefine_line|#define STRETCH_BLIT_CLIP_SIZE_WIDTH                                15:0
DECL|macro|STRETCH_BLIT_CLIP_SIZE_HEIGHT
mdefine_line|#define STRETCH_BLIT_CLIP_SIZE_HEIGHT                               31:16
DECL|macro|STRETCH_BLIT_DST_POINT
mdefine_line|#define STRETCH_BLIT_DST_POINT                                      0x0000E310
DECL|macro|STRETCH_BLIT_DST_POINT_X
mdefine_line|#define STRETCH_BLIT_DST_POINT_X                                    15:0
DECL|macro|STRETCH_BLIT_DST_POINT_Y
mdefine_line|#define STRETCH_BLIT_DST_POINT_Y                                    31:16
DECL|macro|STRETCH_BLIT_DST_SIZE
mdefine_line|#define STRETCH_BLIT_DST_SIZE                                       0x0000E314
DECL|macro|STRETCH_BLIT_DST_SIZE_WIDTH
mdefine_line|#define STRETCH_BLIT_DST_SIZE_WIDTH                                 15:0
DECL|macro|STRETCH_BLIT_DST_SIZE_HEIGHT
mdefine_line|#define STRETCH_BLIT_DST_SIZE_HEIGHT                                31:16
DECL|macro|STRETCH_BLIT_DU_DX
mdefine_line|#define STRETCH_BLIT_DU_DX                                          0x0000E318
DECL|macro|STRETCH_BLIT_DV_DY
mdefine_line|#define STRETCH_BLIT_DV_DY                                          0x0000E31C
DECL|macro|STRETCH_BLIT_SRC_SIZE
mdefine_line|#define STRETCH_BLIT_SRC_SIZE                                       0x0000E400
DECL|macro|STRETCH_BLIT_SRC_SIZE_WIDTH
mdefine_line|#define STRETCH_BLIT_SRC_SIZE_WIDTH                                 15:0
DECL|macro|STRETCH_BLIT_SRC_SIZE_HEIGHT
mdefine_line|#define STRETCH_BLIT_SRC_SIZE_HEIGHT                                31:16
DECL|macro|STRETCH_BLIT_SRC_FORMAT
mdefine_line|#define STRETCH_BLIT_SRC_FORMAT                                     0x0000E404
DECL|macro|STRETCH_BLIT_SRC_FORMAT_PITCH
mdefine_line|#define STRETCH_BLIT_SRC_FORMAT_PITCH                               15:0
DECL|macro|STRETCH_BLIT_SRC_FORMAT_ORIGIN
mdefine_line|#define STRETCH_BLIT_SRC_FORMAT_ORIGIN                              23:16
DECL|macro|STRETCH_BLIT_SRC_FORMAT_ORIGIN_CENTER
mdefine_line|#define STRETCH_BLIT_SRC_FORMAT_ORIGIN_CENTER                       0x00000001
DECL|macro|STRETCH_BLIT_SRC_FORMAT_ORIGIN_CORNER
mdefine_line|#define STRETCH_BLIT_SRC_FORMAT_ORIGIN_CORNER                       0x00000002
DECL|macro|STRETCH_BLIT_SRC_FORMAT_FILTER
mdefine_line|#define STRETCH_BLIT_SRC_FORMAT_FILTER                              31:24
DECL|macro|STRETCH_BLIT_SRC_FORMAT_FILTER_POINT_SAMPLE
mdefine_line|#define STRETCH_BLIT_SRC_FORMAT_FILTER_POINT_SAMPLE                 0x00000000
DECL|macro|STRETCH_BLIT_SRC_FORMAT_FILTER_BILINEAR
mdefine_line|#define STRETCH_BLIT_SRC_FORMAT_FILTER_BILINEAR                     0x00000001
DECL|macro|STRETCH_BLIT_SRC_OFFSET
mdefine_line|#define STRETCH_BLIT_SRC_OFFSET                                     0x0000E408
DECL|macro|STRETCH_BLIT_SRC_POINT
mdefine_line|#define STRETCH_BLIT_SRC_POINT                                      0x0000E40C
DECL|macro|STRETCH_BLIT_SRC_POINT_U
mdefine_line|#define STRETCH_BLIT_SRC_POINT_U                                    15:0
DECL|macro|STRETCH_BLIT_SRC_POINT_V
mdefine_line|#define STRETCH_BLIT_SRC_POINT_V                                    31:16
eof
