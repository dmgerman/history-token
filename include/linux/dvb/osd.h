multiline_comment|/* &n; * osd.h&n; *&n; * Copyright (C) 2001 Ralph  Metzler &lt;ralph@convergence.de&gt;&n; *                  &amp; Marcus Metzler &lt;marcus@convergence.de&gt;&n;                      for convergence integrated media GmbH&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Lesser Public License&n; * as published by the Free Software Foundation; either version 2.1&n; * of the License, or (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU Lesser General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.&n; *&n; */
macro_line|#ifndef _DVBOSD_H_
DECL|macro|_DVBOSD_H_
mdefine_line|#define _DVBOSD_H_
macro_line|#include &lt;linux/compiler.h&gt;
r_typedef
r_enum
(brace
singleline_comment|// All functions return -2 on &quot;not open&quot;
DECL|enumerator|OSD_Close
id|OSD_Close
op_assign
l_int|1
comma
singleline_comment|// ()
singleline_comment|// Disables OSD and releases the buffers
singleline_comment|// returns 0 on success
DECL|enumerator|OSD_Open
id|OSD_Open
comma
singleline_comment|// (x0,y0,x1,y1,BitPerPixel[2/4/8](color&amp;0x0F),mix[0..15](color&amp;0xF0))
singleline_comment|// Opens OSD with this size and bit depth
singleline_comment|// returns 0 on success, -1 on DRAM allocation error, -2 on &quot;already open&quot;
DECL|enumerator|OSD_Show
id|OSD_Show
comma
singleline_comment|// ()
singleline_comment|// enables OSD mode
singleline_comment|// returns 0 on success
DECL|enumerator|OSD_Hide
id|OSD_Hide
comma
singleline_comment|// ()
singleline_comment|// disables OSD mode
singleline_comment|// returns 0 on success
DECL|enumerator|OSD_Clear
id|OSD_Clear
comma
singleline_comment|// ()
singleline_comment|// Sets all pixel to color 0
singleline_comment|// returns 0 on success
DECL|enumerator|OSD_Fill
id|OSD_Fill
comma
singleline_comment|// (color)
singleline_comment|// Sets all pixel to color &lt;col&gt;
singleline_comment|// returns 0 on success
DECL|enumerator|OSD_SetColor
id|OSD_SetColor
comma
singleline_comment|// (color,R{x0},G{y0},B{x1},opacity{y1})
singleline_comment|// set palette entry &lt;num&gt; to &lt;r,g,b&gt;, &lt;mix&gt; and &lt;trans&gt; apply
singleline_comment|// R,G,B: 0..255
singleline_comment|// R=Red, G=Green, B=Blue
singleline_comment|// opacity=0:      pixel opacity 0% (only video pixel shows)
singleline_comment|// opacity=1..254: pixel opacity as specified in header
singleline_comment|// opacity=255:    pixel opacity 100% (only OSD pixel shows)
singleline_comment|// returns 0 on success, -1 on error
DECL|enumerator|OSD_SetPalette
id|OSD_SetPalette
comma
singleline_comment|// (firstcolor{color},lastcolor{x0},data)
singleline_comment|// Set a number of entries in the palette
singleline_comment|// sets the entries &quot;firstcolor&quot; through &quot;lastcolor&quot; from the array &quot;data&quot;
singleline_comment|// data has 4 byte for each color:
singleline_comment|// R,G,B, and a opacity value: 0-&gt;transparent, 1..254-&gt;mix, 255-&gt;pixel
DECL|enumerator|OSD_SetTrans
id|OSD_SetTrans
comma
singleline_comment|// (transparency{color})
singleline_comment|// Sets transparency of mixed pixel (0..15)
singleline_comment|// returns 0 on success
DECL|enumerator|OSD_SetPixel
id|OSD_SetPixel
comma
singleline_comment|// (x0,y0,color)
singleline_comment|// sets pixel &lt;x&gt;,&lt;y&gt; to color number &lt;col&gt;
singleline_comment|// returns 0 on success, -1 on error
DECL|enumerator|OSD_GetPixel
id|OSD_GetPixel
comma
singleline_comment|// (x0,y0)
singleline_comment|// returns color number of pixel &lt;x&gt;,&lt;y&gt;,  or -1
DECL|enumerator|OSD_SetRow
id|OSD_SetRow
comma
singleline_comment|// (x0,y0,x1,data)
singleline_comment|// fills pixels x0,y through  x1,y with the content of data[]
singleline_comment|// returns 0 on success, -1 on clipping all pixel (no pixel drawn)
DECL|enumerator|OSD_SetBlock
id|OSD_SetBlock
comma
singleline_comment|// (x0,y0,x1,y1,increment{color},data)
singleline_comment|// fills pixels x0,y0 through  x1,y1 with the content of data[]
singleline_comment|// inc contains the width of one line in the data block,
singleline_comment|// inc&lt;=0 uses blockwidth as linewidth
singleline_comment|// returns 0 on success, -1 on clipping all pixel
DECL|enumerator|OSD_FillRow
id|OSD_FillRow
comma
singleline_comment|// (x0,y0,x1,color)
singleline_comment|// fills pixels x0,y through  x1,y with the color &lt;col&gt;
singleline_comment|// returns 0 on success, -1 on clipping all pixel
DECL|enumerator|OSD_FillBlock
id|OSD_FillBlock
comma
singleline_comment|// (x0,y0,x1,y1,color)
singleline_comment|// fills pixels x0,y0 through  x1,y1 with the color &lt;col&gt;
singleline_comment|// returns 0 on success, -1 on clipping all pixel
DECL|enumerator|OSD_Line
id|OSD_Line
comma
singleline_comment|// (x0,y0,x1,y1,color)
singleline_comment|// draw a line from x0,y0 to x1,y1 with the color &lt;col&gt;
singleline_comment|// returns 0 on success
DECL|enumerator|OSD_Query
id|OSD_Query
comma
singleline_comment|// (x0,y0,x1,y1,xasp{color}}), yasp=11
singleline_comment|// fills parameters with the picture dimensions and the pixel aspect ratio
singleline_comment|// returns 0 on success
DECL|enumerator|OSD_Test
id|OSD_Test
comma
singleline_comment|// ()
singleline_comment|// draws a test picture. for debugging purposes only
singleline_comment|// returns 0 on success
singleline_comment|// TODO: remove &quot;test&quot; in final version
DECL|enumerator|OSD_Text
id|OSD_Text
comma
singleline_comment|// (x0,y0,size,color,text)
DECL|enumerator|OSD_SetWindow
id|OSD_SetWindow
comma
singleline_comment|//  (x0) set window with number 0&lt;x0&lt;8 as current
DECL|enumerator|OSD_MoveWindow
id|OSD_MoveWindow
comma
singleline_comment|//  move current window to (x0, y0)  
DECL|enumerator|OSD_OpenRaw
id|OSD_OpenRaw
comma
singleline_comment|// Open other types of OSD windows
DECL|typedef|OSD_Command
)brace
id|OSD_Command
suffix:semicolon
DECL|struct|osd_cmd_s
r_typedef
r_struct
id|osd_cmd_s
(brace
DECL|member|cmd
id|OSD_Command
id|cmd
suffix:semicolon
DECL|member|x0
r_int
id|x0
suffix:semicolon
DECL|member|y0
r_int
id|y0
suffix:semicolon
DECL|member|x1
r_int
id|x1
suffix:semicolon
DECL|member|y1
r_int
id|y1
suffix:semicolon
DECL|member|color
r_int
id|color
suffix:semicolon
DECL|member|data
r_void
id|__user
op_star
id|data
suffix:semicolon
DECL|typedef|osd_cmd_t
)brace
id|osd_cmd_t
suffix:semicolon
multiline_comment|/* OSD_OpenRaw: set &squot;color&squot; to desired window type */
r_typedef
r_enum
(brace
DECL|enumerator|OSD_BITMAP1
id|OSD_BITMAP1
comma
multiline_comment|/* 1 bit bitmap */
DECL|enumerator|OSD_BITMAP2
id|OSD_BITMAP2
comma
multiline_comment|/* 2 bit bitmap */
DECL|enumerator|OSD_BITMAP4
id|OSD_BITMAP4
comma
multiline_comment|/* 4 bit bitmap */
DECL|enumerator|OSD_BITMAP8
id|OSD_BITMAP8
comma
multiline_comment|/* 8 bit bitmap */
DECL|enumerator|OSD_BITMAP1HR
id|OSD_BITMAP1HR
comma
multiline_comment|/* 1 Bit bitmap half resolution */
DECL|enumerator|OSD_BITMAP2HR
id|OSD_BITMAP2HR
comma
multiline_comment|/* 2 bit bitmap half resolution */
DECL|enumerator|OSD_BITMAP4HR
id|OSD_BITMAP4HR
comma
multiline_comment|/* 4 bit bitmap half resolution */
DECL|enumerator|OSD_BITMAP8HR
id|OSD_BITMAP8HR
comma
multiline_comment|/* 8 bit bitmap half resolution */
DECL|enumerator|OSD_YCRCB422
id|OSD_YCRCB422
comma
multiline_comment|/* 4:2:2 YCRCB Graphic Display */
DECL|enumerator|OSD_YCRCB444
id|OSD_YCRCB444
comma
multiline_comment|/* 4:4:4 YCRCB Graphic Display */
DECL|enumerator|OSD_YCRCB444HR
id|OSD_YCRCB444HR
comma
multiline_comment|/* 4:4:4 YCRCB graphic half resolution */
DECL|enumerator|OSD_VIDEOTSIZE
id|OSD_VIDEOTSIZE
comma
multiline_comment|/* True Size Normal MPEG Video Display */
DECL|enumerator|OSD_VIDEOHSIZE
id|OSD_VIDEOHSIZE
comma
multiline_comment|/* MPEG Video Display Half Resolution */
DECL|enumerator|OSD_VIDEOQSIZE
id|OSD_VIDEOQSIZE
comma
multiline_comment|/* MPEG Video Display Quarter Resolution */
DECL|enumerator|OSD_VIDEODSIZE
id|OSD_VIDEODSIZE
comma
multiline_comment|/* MPEG Video Display Double Resolution */
DECL|enumerator|OSD_VIDEOTHSIZE
id|OSD_VIDEOTHSIZE
comma
multiline_comment|/* True Size MPEG Video Display Half Resolution */
DECL|enumerator|OSD_VIDEOTQSIZE
id|OSD_VIDEOTQSIZE
comma
multiline_comment|/* True Size MPEG Video Display Quarter Resolution*/
DECL|enumerator|OSD_VIDEOTDSIZE
id|OSD_VIDEOTDSIZE
comma
multiline_comment|/* True Size MPEG Video Display Double Resolution */
DECL|enumerator|OSD_VIDEONSIZE
id|OSD_VIDEONSIZE
comma
multiline_comment|/* Full Size MPEG Video Display */
DECL|enumerator|OSD_CURSOR
id|OSD_CURSOR
multiline_comment|/* Cursor */
DECL|typedef|osd_raw_window_t
)brace
id|osd_raw_window_t
suffix:semicolon
DECL|struct|osd_cap_s
r_typedef
r_struct
id|osd_cap_s
(brace
DECL|member|cmd
r_int
id|cmd
suffix:semicolon
DECL|macro|OSD_CAP_MEMSIZE
mdefine_line|#define OSD_CAP_MEMSIZE         1  /* memory size */
DECL|member|val
r_int
id|val
suffix:semicolon
DECL|typedef|osd_cap_t
)brace
id|osd_cap_t
suffix:semicolon
DECL|macro|OSD_SEND_CMD
mdefine_line|#define OSD_SEND_CMD       _IOW(&squot;o&squot;, 160, osd_cmd_t)
DECL|macro|OSD_GET_CAPABILITY
mdefine_line|#define OSD_GET_CAPABILITY      _IOR(&squot;o&squot;, 161, osd_cap_t)
macro_line|#endif
eof
