multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * This is the user-visible SGI GFX interface.&n; *&n; * This must be used verbatim into the GNU libc.  It does not include&n; * any kernel-only bits on it.  &n; *&n; * miguel@nuclecu.unam.mx&n; */
macro_line|#ifndef _ASM_GFX_H
DECL|macro|_ASM_GFX_H
mdefine_line|#define _ASM_GFX_H
multiline_comment|/* The iocls, yes, they do not make sense, but such is life */
DECL|macro|GFX_BASE
mdefine_line|#define GFX_BASE             100
DECL|macro|GFX_GETNUM_BOARDS
mdefine_line|#define GFX_GETNUM_BOARDS    (GFX_BASE + 1)
DECL|macro|GFX_GETBOARD_INFO
mdefine_line|#define GFX_GETBOARD_INFO    (GFX_BASE + 2)
DECL|macro|GFX_ATTACH_BOARD
mdefine_line|#define GFX_ATTACH_BOARD     (GFX_BASE + 3)
DECL|macro|GFX_DETACH_BOARD
mdefine_line|#define GFX_DETACH_BOARD     (GFX_BASE + 4)
DECL|macro|GFX_IS_MANAGED
mdefine_line|#define GFX_IS_MANAGED       (GFX_BASE + 5)
DECL|macro|GFX_MAPALL
mdefine_line|#define GFX_MAPALL           (GFX_BASE + 10)
DECL|macro|GFX_LABEL
mdefine_line|#define GFX_LABEL            (GFX_BASE + 11)
DECL|macro|GFX_INFO_NAME_SIZE
mdefine_line|#define GFX_INFO_NAME_SIZE  16
DECL|macro|GFX_INFO_LABEL_SIZE
mdefine_line|#define GFX_INFO_LABEL_SIZE 16
DECL|struct|gfx_info
r_struct
id|gfx_info
(brace
DECL|member|name
r_char
id|name
(braket
id|GFX_INFO_NAME_SIZE
)braket
suffix:semicolon
multiline_comment|/* board name */
DECL|member|label
r_char
id|label
(braket
id|GFX_INFO_LABEL_SIZE
)braket
suffix:semicolon
multiline_comment|/* label name */
DECL|member|xpmax
DECL|member|ypmax
r_int
r_int
r_int
id|xpmax
comma
id|ypmax
suffix:semicolon
multiline_comment|/* screen resolution */
DECL|member|lenght
r_int
r_int
id|lenght
suffix:semicolon
multiline_comment|/* size of a complete gfx_info for this board */
)brace
suffix:semicolon
DECL|struct|gfx_getboardinfo_args
r_struct
id|gfx_getboardinfo_args
(brace
DECL|member|board
r_int
r_int
id|board
suffix:semicolon
multiline_comment|/* board number.  starting from zero */
DECL|member|buf
r_void
op_star
id|buf
suffix:semicolon
multiline_comment|/* pointer to gfx_info */
DECL|member|len
r_int
r_int
id|len
suffix:semicolon
multiline_comment|/* buffer size of buf */
)brace
suffix:semicolon
DECL|struct|gfx_attach_board_args
r_struct
id|gfx_attach_board_args
(brace
DECL|member|board
r_int
r_int
id|board
suffix:semicolon
multiline_comment|/* board number, starting from zero */
DECL|member|vaddr
r_void
op_star
id|vaddr
suffix:semicolon
multiline_comment|/* address where the board registers should be mapped */
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
multiline_comment|/* umap.c */
r_extern
r_void
id|remove_mapping
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_struct
id|task_struct
op_star
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
op_star
id|vmalloc_uncached
(paren
r_int
r_int
id|size
)paren
suffix:semicolon
r_extern
r_int
id|vmap_page_range
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|from
comma
r_int
r_int
id|size
comma
r_int
r_int
id|vaddr
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif /* _ASM_GFX_H */
eof
