multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * SGI/Newport video card ioctl definitions&n; */
macro_line|#ifndef _ASM_NG1_H
DECL|macro|_ASM_NG1_H
mdefine_line|#define _ASM_NG1_H
r_typedef
r_struct
(brace
DECL|member|flags
r_int
id|flags
suffix:semicolon
DECL|member|w
DECL|member|h
id|__u16
id|w
comma
id|h
suffix:semicolon
DECL|member|fields_sec
id|__u16
id|fields_sec
suffix:semicolon
DECL|typedef|ng1_vof_info_t
)brace
id|ng1_vof_info_t
suffix:semicolon
DECL|struct|ng1_info
r_struct
id|ng1_info
(brace
DECL|member|gfx_info
r_struct
id|gfx_info
id|gfx_info
suffix:semicolon
DECL|member|boardrev
id|__u8
id|boardrev
suffix:semicolon
DECL|member|rex3rev
id|__u8
id|rex3rev
suffix:semicolon
DECL|member|vc2rev
id|__u8
id|vc2rev
suffix:semicolon
DECL|member|monitortype
id|__u8
id|monitortype
suffix:semicolon
DECL|member|videoinstalled
id|__u8
id|videoinstalled
suffix:semicolon
DECL|member|mcrev
id|__u8
id|mcrev
suffix:semicolon
DECL|member|bitplanes
id|__u8
id|bitplanes
suffix:semicolon
DECL|member|xmap9rev
id|__u8
id|xmap9rev
suffix:semicolon
DECL|member|cmaprev
id|__u8
id|cmaprev
suffix:semicolon
DECL|member|ng1_vof_info
id|ng1_vof_info_t
id|ng1_vof_info
suffix:semicolon
DECL|member|bt445rev
id|__u8
id|bt445rev
suffix:semicolon
DECL|member|paneltype
id|__u8
id|paneltype
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|GFX_NAME_NEWPORT
mdefine_line|#define GFX_NAME_NEWPORT &quot;NG1&quot;
multiline_comment|/* ioctls */
DECL|macro|NG1_SET_CURSOR_HOTSPOT
mdefine_line|#define NG1_SET_CURSOR_HOTSPOT 21001
DECL|struct|ng1_set_cursor_hotspot
r_struct
id|ng1_set_cursor_hotspot
(brace
DECL|member|xhot
r_int
r_int
id|xhot
suffix:semicolon
DECL|member|yhot
r_int
r_int
id|yhot
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|NG1_SETDISPLAYMODE
mdefine_line|#define NG1_SETDISPLAYMODE     21006
DECL|struct|ng1_setdisplaymode_args
r_struct
id|ng1_setdisplaymode_args
(brace
DECL|member|wid
r_int
id|wid
suffix:semicolon
DECL|member|mode
r_int
r_int
id|mode
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|NG1_SETGAMMARAMP0
mdefine_line|#define NG1_SETGAMMARAMP0      21007
DECL|struct|ng1_setgammaramp_args
r_struct
id|ng1_setgammaramp_args
(brace
DECL|member|red
r_int
r_char
id|red
(braket
l_int|256
)braket
suffix:semicolon
DECL|member|green
r_int
r_char
id|green
(braket
l_int|256
)braket
suffix:semicolon
DECL|member|blue
r_int
r_char
id|blue
(braket
l_int|256
)braket
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* _ASM_NG1_H */
eof
