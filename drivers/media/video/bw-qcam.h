multiline_comment|/*&n; *&t;Video4Linux bw-qcam driver&n; *&n; *&t;Derived from code..&n; */
multiline_comment|/******************************************************************&n;&n;Copyright (C) 1996 by Scott Laird&n;&n;Permission is hereby granted, free of charge, to any person obtaining&n;a copy of this software and associated documentation files (the&n;&quot;Software&quot;), to deal in the Software without restriction, including&n;without limitation the rights to use, copy, modify, merge, publish,&n;distribute, sublicense, and/or sell copies of the Software, and to&n;permit persons to whom the Software is furnished to do so, subject to&n;the following conditions:&n;&n;The above copyright notice and this permission notice shall be&n;included in all copies or substantial portions of the Software.&n;&n;THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND,&n;EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF&n;MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.&n;IN NO EVENT SHALL SCOTT LAIRD BE LIABLE FOR ANY CLAIM, DAMAGES OR&n;OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,&n;ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR&n;OTHER DEALINGS IN THE SOFTWARE.&n;&n;******************************************************************/
multiline_comment|/* One from column A... */
DECL|macro|QC_NOTSET
mdefine_line|#define QC_NOTSET 0
DECL|macro|QC_UNIDIR
mdefine_line|#define QC_UNIDIR 1
DECL|macro|QC_BIDIR
mdefine_line|#define QC_BIDIR  2
DECL|macro|QC_SERIAL
mdefine_line|#define QC_SERIAL 3
multiline_comment|/* ... and one from column B */
DECL|macro|QC_ANY
mdefine_line|#define QC_ANY          0x00
DECL|macro|QC_FORCE_UNIDIR
mdefine_line|#define QC_FORCE_UNIDIR 0x10
DECL|macro|QC_FORCE_BIDIR
mdefine_line|#define QC_FORCE_BIDIR  0x20
DECL|macro|QC_FORCE_SERIAL
mdefine_line|#define QC_FORCE_SERIAL 0x30
multiline_comment|/* in the port_mode member */
DECL|macro|QC_MODE_MASK
mdefine_line|#define QC_MODE_MASK    0x07
DECL|macro|QC_FORCE_MASK
mdefine_line|#define QC_FORCE_MASK   0x70
DECL|macro|MAX_HEIGHT
mdefine_line|#define MAX_HEIGHT 243
DECL|macro|MAX_WIDTH
mdefine_line|#define MAX_WIDTH 336
multiline_comment|/* Bit fields for status flags */
DECL|macro|QC_PARAM_CHANGE
mdefine_line|#define QC_PARAM_CHANGE&t;0x01 /* Camera status change has occurred */
DECL|struct|qcam_device
r_struct
id|qcam_device
(brace
DECL|member|vdev
r_struct
id|video_device
id|vdev
suffix:semicolon
DECL|member|pdev
r_struct
id|pardevice
op_star
id|pdev
suffix:semicolon
DECL|member|pport
r_struct
id|parport
op_star
id|pport
suffix:semicolon
DECL|member|lock
r_struct
id|semaphore
id|lock
suffix:semicolon
DECL|member|width
DECL|member|height
r_int
id|width
comma
id|height
suffix:semicolon
DECL|member|bpp
r_int
id|bpp
suffix:semicolon
DECL|member|mode
r_int
id|mode
suffix:semicolon
DECL|member|contrast
DECL|member|brightness
DECL|member|whitebal
r_int
id|contrast
comma
id|brightness
comma
id|whitebal
suffix:semicolon
DECL|member|port_mode
r_int
id|port_mode
suffix:semicolon
DECL|member|transfer_scale
r_int
id|transfer_scale
suffix:semicolon
DECL|member|top
DECL|member|left
r_int
id|top
comma
id|left
suffix:semicolon
DECL|member|status
r_int
id|status
suffix:semicolon
DECL|member|saved_bits
r_int
r_int
id|saved_bits
suffix:semicolon
)brace
suffix:semicolon
eof
