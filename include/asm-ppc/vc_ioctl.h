multiline_comment|/*&n; * BK Id: SCCS/s.vc_ioctl.h 1.5 05/17/01 18:14:26 cort&n; */
macro_line|#ifndef _LINUX_VC_IOCTL_H
DECL|macro|_LINUX_VC_IOCTL_H
mdefine_line|#define _LINUX_VC_IOCTL_H
DECL|struct|vc_mode
r_struct
id|vc_mode
(brace
DECL|member|height
r_int
id|height
suffix:semicolon
DECL|member|width
r_int
id|width
suffix:semicolon
DECL|member|depth
r_int
id|depth
suffix:semicolon
DECL|member|pitch
r_int
id|pitch
suffix:semicolon
DECL|member|mode
r_int
id|mode
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|fb_address
r_int
r_int
id|fb_address
suffix:semicolon
DECL|member|cmap_adr_address
r_int
r_int
id|cmap_adr_address
suffix:semicolon
DECL|member|cmap_data_address
r_int
r_int
id|cmap_data_address
suffix:semicolon
DECL|member|disp_reg_address
r_int
r_int
id|disp_reg_address
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|VC_GETMODE
mdefine_line|#define VC_GETMODE&t;0x7667
DECL|macro|VC_SETMODE
mdefine_line|#define VC_SETMODE&t;0x7668
DECL|macro|VC_INQMODE
mdefine_line|#define VC_INQMODE&t;0x7669
DECL|macro|VC_SETCMAP
mdefine_line|#define VC_SETCMAP      0x766a
DECL|macro|VC_GETCMAP
mdefine_line|#define VC_GETCMAP      0x766b
DECL|macro|VC_POWERMODE
mdefine_line|#define VC_POWERMODE&t;0x766c
multiline_comment|/* Values for the argument to the VC_POWERMODE ioctl */
DECL|macro|VC_POWERMODE_INQUIRY
mdefine_line|#define VC_POWERMODE_INQUIRY&t;(-1)
DECL|macro|VESA_NO_BLANKING
mdefine_line|#define VESA_NO_BLANKING&t;0
DECL|macro|VESA_VSYNC_SUSPEND
mdefine_line|#define VESA_VSYNC_SUSPEND&t;1
DECL|macro|VESA_HSYNC_SUSPEND
mdefine_line|#define VESA_HSYNC_SUSPEND&t;2
DECL|macro|VESA_POWERDOWN
mdefine_line|#define VESA_POWERDOWN&t;&t;3
macro_line|#ifdef __KERNEL__
r_extern
r_int
id|console_getmode
c_func
(paren
r_struct
id|vc_mode
op_star
)paren
suffix:semicolon
r_extern
r_int
id|console_setmode
c_func
(paren
r_struct
id|vc_mode
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|console_setcmap
c_func
(paren
r_int
comma
r_int
r_char
op_star
comma
r_int
r_char
op_star
comma
r_int
r_char
op_star
)paren
suffix:semicolon
r_extern
r_int
id|console_powermode
c_func
(paren
r_int
)paren
suffix:semicolon
r_extern
r_struct
id|vc_mode
id|display_info
suffix:semicolon
r_extern
r_struct
id|fb_info
op_star
id|console_fb_info
suffix:semicolon
macro_line|#endif
macro_line|#endif /* _LINUX_VC_IOCTL_H */
eof
