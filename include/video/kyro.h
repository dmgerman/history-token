multiline_comment|/*&n; *  linux/drivers/video/kyro/kryo.h&n; *&n; *  Copyright (C) 2002 STMicroelectronics&n; *  Copyright (C) 2004 Paul Mundt&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file COPYING in the main directory of this archive&n; * for more details.&n; */
macro_line|#ifndef _KYRO_H
DECL|macro|_KYRO_H
mdefine_line|#define _KYRO_H
DECL|struct|kyrofb_info
r_struct
id|kyrofb_info
(brace
DECL|member|regbase
r_void
id|__iomem
op_star
id|regbase
suffix:semicolon
DECL|member|HTot
id|u32
id|HTot
suffix:semicolon
multiline_comment|/* Hor Total Time    */
DECL|member|HFP
id|u32
id|HFP
suffix:semicolon
multiline_comment|/* Hor Front Porch   */
DECL|member|HST
id|u32
id|HST
suffix:semicolon
multiline_comment|/* Hor Sync Time     */
DECL|member|HBP
id|u32
id|HBP
suffix:semicolon
multiline_comment|/* Hor Back Porch    */
DECL|member|HSP
id|s32
id|HSP
suffix:semicolon
multiline_comment|/* Hor Sync Polarity */
DECL|member|VTot
id|u32
id|VTot
suffix:semicolon
multiline_comment|/* Ver Total Time    */
DECL|member|VFP
id|u32
id|VFP
suffix:semicolon
multiline_comment|/* Ver Front Porch   */
DECL|member|VST
id|u32
id|VST
suffix:semicolon
multiline_comment|/* Ver Sync Time     */
DECL|member|VBP
id|u32
id|VBP
suffix:semicolon
multiline_comment|/* Ver Back Porch    */
DECL|member|VSP
id|s32
id|VSP
suffix:semicolon
multiline_comment|/* Ver Sync Polarity */
DECL|member|XRES
id|u32
id|XRES
suffix:semicolon
multiline_comment|/* X Resolution      */
DECL|member|YRES
id|u32
id|YRES
suffix:semicolon
multiline_comment|/* Y Resolution      */
DECL|member|VFREQ
id|u32
id|VFREQ
suffix:semicolon
multiline_comment|/* Ver Frequency     */
DECL|member|PIXCLK
id|u32
id|PIXCLK
suffix:semicolon
multiline_comment|/* Pixel Clock       */
DECL|member|HCLK
id|u32
id|HCLK
suffix:semicolon
multiline_comment|/* Hor Clock         */
multiline_comment|/* Usefull to hold depth here for Linux */
DECL|member|PIXDEPTH
id|u8
id|PIXDEPTH
suffix:semicolon
macro_line|#ifdef CONFIG_MTRR
DECL|member|mtrr_handle
r_int
id|mtrr_handle
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
r_extern
r_int
id|kyro_dev_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|kyro_dev_reset
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_char
op_star
id|kyro_dev_physical_fb_ptr
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_char
op_star
id|kyro_dev_virtual_fb_ptr
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
op_star
id|kyro_dev_physical_regs_ptr
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
op_star
id|kyro_dev_virtual_regs_ptr
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_int
id|kyro_dev_fb_size
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_int
id|kyro_dev_regs_size
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|kyro_dev_overlay_create
c_func
(paren
id|u32
id|width
comma
id|u32
id|height
comma
r_int
id|bLinear
)paren
suffix:semicolon
r_extern
id|u32
id|kyro_dev_overlay_offset
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|kyro_dev_overlay_viewport_set
c_func
(paren
id|u32
id|x
comma
id|u32
id|y
comma
id|u32
id|width
comma
id|u32
id|height
)paren
suffix:semicolon
multiline_comment|/*&n; * benedict.gaster@superh.com&n; * Added the follow IOCTLS for the creation of overlay services...&n; */
DECL|macro|KYRO_IOC_MAGIC
mdefine_line|#define KYRO_IOC_MAGIC &squot;k&squot;
DECL|macro|KYRO_IOCTL_OVERLAY_CREATE
mdefine_line|#define KYRO_IOCTL_OVERLAY_CREATE       _IO(KYRO_IOC_MAGIC, 0)
DECL|macro|KYRO_IOCTL_OVERLAY_VIEWPORT_SET
mdefine_line|#define KYRO_IOCTL_OVERLAY_VIEWPORT_SET _IO(KYRO_IOC_MAGIC, 1)
DECL|macro|KYRO_IOCTL_SET_VIDEO_MODE
mdefine_line|#define KYRO_IOCTL_SET_VIDEO_MODE       _IO(KYRO_IOC_MAGIC, 2)
DECL|macro|KYRO_IOCTL_UVSTRIDE
mdefine_line|#define KYRO_IOCTL_UVSTRIDE             _IO(KYRO_IOC_MAGIC, 3)
DECL|macro|KYRO_IOCTL_OVERLAY_OFFSET
mdefine_line|#define KYRO_IOCTL_OVERLAY_OFFSET       _IO(KYRO_IOC_MAGIC, 4)
DECL|macro|KYRO_IOCTL_STRIDE
mdefine_line|#define KYRO_IOCTL_STRIDE               _IO(KYRO_IOC_MAGIC, 5)
multiline_comment|/*&n; * The follow 3 structures are used to pass data from user space into the kernel&n; * for the creation of overlay surfaces and setting the video mode.&n; */
DECL|struct|_OVERLAY_CREATE
r_typedef
r_struct
id|_OVERLAY_CREATE
(brace
DECL|member|ulWidth
id|u32
id|ulWidth
suffix:semicolon
DECL|member|ulHeight
id|u32
id|ulHeight
suffix:semicolon
DECL|member|bLinear
r_int
id|bLinear
suffix:semicolon
DECL|typedef|overlay_create
)brace
id|overlay_create
suffix:semicolon
DECL|struct|_OVERLAY_VIEWPORT_SET
r_typedef
r_struct
id|_OVERLAY_VIEWPORT_SET
(brace
DECL|member|xOrgin
id|u32
id|xOrgin
suffix:semicolon
DECL|member|yOrgin
id|u32
id|yOrgin
suffix:semicolon
DECL|member|xSize
id|u32
id|xSize
suffix:semicolon
DECL|member|ySize
id|u32
id|ySize
suffix:semicolon
DECL|typedef|overlay_viewport_set
)brace
id|overlay_viewport_set
suffix:semicolon
DECL|struct|_SET_VIDEO_MODE
r_typedef
r_struct
id|_SET_VIDEO_MODE
(brace
DECL|member|ulWidth
id|u32
id|ulWidth
suffix:semicolon
DECL|member|ulHeight
id|u32
id|ulHeight
suffix:semicolon
DECL|member|ulScan
id|u32
id|ulScan
suffix:semicolon
DECL|member|displayDepth
id|u8
id|displayDepth
suffix:semicolon
DECL|member|bLinear
r_int
id|bLinear
suffix:semicolon
DECL|typedef|set_video_mode
)brace
id|set_video_mode
suffix:semicolon
macro_line|#endif /* _KYRO_H */
eof
