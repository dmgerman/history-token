multiline_comment|/*&n; *   Copyright (c) International Business Machines Corp., 2000-2002&n; *&n; *   This program is free software;  you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY;  without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See&n; *   the GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program;  if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; */
macro_line|#ifndef H_JFS_XATTR
DECL|macro|H_JFS_XATTR
mdefine_line|#define H_JFS_XATTR
multiline_comment|/*&n; * jfs_ea_list describe the on-disk format of the extended attributes.&n; * I know the null-terminator is redundant since namelen is stored, but&n; * I am maintaining compatibility with OS/2 where possible.&n; */
DECL|struct|jfs_ea
r_struct
id|jfs_ea
(brace
DECL|member|flag
id|u8
id|flag
suffix:semicolon
multiline_comment|/* Unused? */
DECL|member|namelen
id|u8
id|namelen
suffix:semicolon
multiline_comment|/* Length of name */
DECL|member|valuelen
id|__le16
id|valuelen
suffix:semicolon
multiline_comment|/* Length of value */
DECL|member|name
r_char
id|name
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* Attribute name (includes null-terminator) */
)brace
suffix:semicolon
multiline_comment|/* Value immediately follows name */
DECL|struct|jfs_ea_list
r_struct
id|jfs_ea_list
(brace
DECL|member|size
id|__le32
id|size
suffix:semicolon
multiline_comment|/* overall size */
DECL|member|ea
r_struct
id|jfs_ea
id|ea
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* Variable length list */
)brace
suffix:semicolon
multiline_comment|/* Macros for defining maxiumum number of bytes supported for EAs */
DECL|macro|MAXEASIZE
mdefine_line|#define MAXEASIZE&t;65535
DECL|macro|MAXEALISTSIZE
mdefine_line|#define MAXEALISTSIZE&t;MAXEASIZE
multiline_comment|/*&n; * some macros for dealing with variable length EA lists.&n; */
DECL|macro|EA_SIZE
mdefine_line|#define EA_SIZE(ea) &bslash;&n;&t;(sizeof (struct jfs_ea) + (ea)-&gt;namelen + 1 + &bslash;&n;&t; le16_to_cpu((ea)-&gt;valuelen))
DECL|macro|NEXT_EA
mdefine_line|#define&t;NEXT_EA(ea) ((struct jfs_ea *) (((char *) (ea)) + (EA_SIZE (ea))))
DECL|macro|FIRST_EA
mdefine_line|#define&t;FIRST_EA(ealist) ((ealist)-&gt;ea)
DECL|macro|EALIST_SIZE
mdefine_line|#define&t;EALIST_SIZE(ealist) le32_to_cpu((ealist)-&gt;size)
DECL|macro|END_EALIST
mdefine_line|#define&t;END_EALIST(ealist) &bslash;&n;&t;((struct jfs_ea *) (((char *) (ealist)) + EALIST_SIZE(ealist)))
r_extern
r_int
id|__jfs_setxattr
c_func
(paren
r_struct
id|inode
op_star
comma
r_const
r_char
op_star
comma
r_const
r_void
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|jfs_setxattr
c_func
(paren
r_struct
id|dentry
op_star
comma
r_const
r_char
op_star
comma
r_const
r_void
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
id|ssize_t
id|__jfs_getxattr
c_func
(paren
r_struct
id|inode
op_star
comma
r_const
r_char
op_star
comma
r_void
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
id|ssize_t
id|jfs_getxattr
c_func
(paren
r_struct
id|dentry
op_star
comma
r_const
r_char
op_star
comma
r_void
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
id|ssize_t
id|jfs_listxattr
c_func
(paren
r_struct
id|dentry
op_star
comma
r_char
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|jfs_removexattr
c_func
(paren
r_struct
id|dentry
op_star
comma
r_const
r_char
op_star
)paren
suffix:semicolon
macro_line|#endif&t;/* H_JFS_XATTR */
eof
