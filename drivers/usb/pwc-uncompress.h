multiline_comment|/* (C) 1999-2001 Nemosoft Unv. (webcam@smcc.demon.nl)&n;&n;   This program is free software; you can redistribute it and/or modify&n;   it under the terms of the GNU General Public License as published by&n;   the Free Software Foundation; either version 2 of the License, or&n;   (at your option) any later version.&n;&n;   This program is distributed in the hope that it will be useful,&n;   but WITHOUT ANY WARRANTY; without even the implied warranty of&n;   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;   GNU General Public License for more details.&n;&n;   You should have received a copy of the GNU General Public License&n;   along with this program; if not, write to the Free Software&n;   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n;*/
macro_line|#ifndef PWC_DEC_H
DECL|macro|PWC_DEC_H
mdefine_line|#define PWC_DEC_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#ifdef __cplusplus
r_extern
l_string|&quot;C&quot;
(brace
macro_line|#endif
multiline_comment|/* The decompressor structure. &n;   Every type of decompressor registers itself with the main module. &n;   When a device is opened, it looks up the correct compressor, and&n;   uses that when a compressed video mode is requested.&n; */
DECL|struct|pwc_decompressor
r_struct
id|pwc_decompressor
(brace
DECL|member|type
r_int
id|type
suffix:semicolon
multiline_comment|/* type of camera (645, 646, etc) */
DECL|member|init
r_int
(paren
op_star
id|init
)paren
(paren
r_int
id|release
comma
r_void
op_star
id|buffer
comma
r_void
op_star
op_star
id|data
)paren
suffix:semicolon
multiline_comment|/* Initialization routine; should be called after each set_video_mode */
DECL|member|exit
r_void
(paren
op_star
m_exit
)paren
(paren
r_void
op_star
op_star
id|data
)paren
suffix:semicolon
multiline_comment|/* Cleanup routine */
DECL|member|decompress
r_int
(paren
op_star
id|decompress
)paren
(paren
r_void
op_star
id|data
comma
r_int
id|width
comma
r_int
id|height
comma
r_int
id|bandlength
comma
r_void
op_star
id|dst
comma
r_void
op_star
id|src
comma
r_int
id|planar
)paren
suffix:semicolon
multiline_comment|/* The decompression routine itself */
DECL|member|lock
r_void
(paren
op_star
id|lock
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* make sure module cannot be unloaded */
DECL|member|unlock
r_void
(paren
op_star
id|unlock
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* release lock on module */
DECL|member|pwcd_list
r_struct
id|list_head
id|pwcd_list
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Our structure version number. Is set to the version number major */
r_extern
r_const
r_int
id|pwc_decompressor_version
suffix:semicolon
multiline_comment|/* Adds decompressor to list, based on its &squot;type&squot; field (which matches the &squot;type&squot; field in pwc_device; ignores any double requests */
r_extern
r_void
id|pwc_register_decompressor
c_func
(paren
r_struct
id|pwc_decompressor
op_star
id|pwcd
)paren
suffix:semicolon
multiline_comment|/* Removes decompressor, based on the type number */
r_extern
r_void
id|pwc_unregister_decompressor
c_func
(paren
r_int
id|type
)paren
suffix:semicolon
multiline_comment|/* Returns pointer to decompressor struct, or NULL if it doesn&squot;t exist */
r_extern
r_struct
id|pwc_decompressor
op_star
id|pwc_find_decompressor
c_func
(paren
r_int
id|type
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_USB_PWCX
multiline_comment|/* If the decompressor is compiled in, we must call these manually */
r_extern
r_int
id|usb_pwcx_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|usb_pwcx_exit
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef __cplusplus
)brace
macro_line|#endif
macro_line|#endif
eof
