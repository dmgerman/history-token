multiline_comment|/*&n; * Copyright (c) 2000-2002 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.&t; Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#ifndef __XFS_IOPS_H__
DECL|macro|__XFS_IOPS_H__
mdefine_line|#define __XFS_IOPS_H__
multiline_comment|/*&n; * Extended system attributes.&n; * So far only POSIX ACLs are supported, but this will need to&n; * grow in time (capabilities, mandatory access control, etc).&n; */
DECL|macro|XFS_SYSTEM_NAMESPACE
mdefine_line|#define XFS_SYSTEM_NAMESPACE&t;SYSTEM_POSIXACL
multiline_comment|/*&n; * Define a table of the namespaces XFS supports&n; */
DECL|typedef|xattr_exists_t
r_typedef
r_int
(paren
op_star
id|xattr_exists_t
)paren
(paren
id|vnode_t
op_star
)paren
suffix:semicolon
DECL|struct|xattr_namespace
r_typedef
r_struct
id|xattr_namespace
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|namelen
r_int
r_int
id|namelen
suffix:semicolon
DECL|member|exists
id|xattr_exists_t
id|exists
suffix:semicolon
DECL|typedef|xattr_namespace_t
)brace
id|xattr_namespace_t
suffix:semicolon
DECL|macro|SYSTEM_NAMES
mdefine_line|#define SYSTEM_NAMES&t;0
DECL|macro|ROOT_NAMES
mdefine_line|#define ROOT_NAMES&t;1
DECL|macro|USER_NAMES
mdefine_line|#define USER_NAMES&t;2
r_extern
r_struct
id|xattr_namespace
op_star
id|xfs_namespaces
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|linvfs_file_inode_operations
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|linvfs_dir_inode_operations
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|linvfs_symlink_inode_operations
suffix:semicolon
r_extern
r_struct
id|file_operations
id|linvfs_file_operations
suffix:semicolon
r_extern
r_struct
id|file_operations
id|linvfs_dir_operations
suffix:semicolon
r_extern
r_struct
id|address_space_operations
id|linvfs_aops
suffix:semicolon
r_extern
r_int
id|linvfs_get_block
c_func
(paren
r_struct
id|inode
op_star
comma
id|sector_t
comma
r_struct
id|buffer_head
op_star
comma
r_int
)paren
suffix:semicolon
macro_line|#endif /* __XFS_IOPS_H__ */
eof
