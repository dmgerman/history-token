multiline_comment|/*&n; * Copyright (c) 2001-2002 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.&t; Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#ifndef __XFS_ACL_H__
DECL|macro|__XFS_ACL_H__
mdefine_line|#define __XFS_ACL_H__
multiline_comment|/*&n; * Access Control Lists&n; */
DECL|typedef|xfs_acl_perm_t
r_typedef
id|__uint16_t
id|xfs_acl_perm_t
suffix:semicolon
DECL|typedef|xfs_acl_type_t
r_typedef
id|__int32_t
id|xfs_acl_type_t
suffix:semicolon
DECL|typedef|xfs_acl_tag_t
r_typedef
id|__int32_t
id|xfs_acl_tag_t
suffix:semicolon
DECL|typedef|xfs_acl_id_t
r_typedef
id|__int32_t
id|xfs_acl_id_t
suffix:semicolon
DECL|macro|XFS_ACL_MAX_ENTRIES
mdefine_line|#define XFS_ACL_MAX_ENTRIES 25
DECL|macro|XFS_ACL_NOT_PRESENT
mdefine_line|#define XFS_ACL_NOT_PRESENT (-1)
DECL|struct|xfs_acl_entry
r_typedef
r_struct
id|xfs_acl_entry
(brace
DECL|member|ae_tag
id|xfs_acl_tag_t
id|ae_tag
suffix:semicolon
DECL|member|ae_id
id|xfs_acl_id_t
id|ae_id
suffix:semicolon
DECL|member|ae_perm
id|xfs_acl_perm_t
id|ae_perm
suffix:semicolon
DECL|typedef|xfs_acl_entry_t
)brace
id|xfs_acl_entry_t
suffix:semicolon
DECL|struct|xfs_acl
r_typedef
r_struct
id|xfs_acl
(brace
DECL|member|acl_cnt
id|__int32_t
id|acl_cnt
suffix:semicolon
DECL|member|acl_entry
id|xfs_acl_entry_t
id|acl_entry
(braket
id|XFS_ACL_MAX_ENTRIES
)braket
suffix:semicolon
DECL|typedef|xfs_acl_t
)brace
id|xfs_acl_t
suffix:semicolon
multiline_comment|/* On-disk XFS extended attribute names */
DECL|macro|SGI_ACL_FILE
mdefine_line|#define SGI_ACL_FILE&t;&quot;SGI_ACL_FILE&quot;
DECL|macro|SGI_ACL_DEFAULT
mdefine_line|#define SGI_ACL_DEFAULT &quot;SGI_ACL_DEFAULT&quot;
DECL|macro|SGI_ACL_FILE_SIZE
mdefine_line|#define SGI_ACL_FILE_SIZE&t;(sizeof(SGI_ACL_FILE)-1)
DECL|macro|SGI_ACL_DEFAULT_SIZE
mdefine_line|#define SGI_ACL_DEFAULT_SIZE&t;(sizeof(SGI_ACL_DEFAULT)-1)
macro_line|#ifdef __KERNEL__
macro_line|#ifdef CONFIG_FS_POSIX_ACL
r_struct
id|vattr
suffix:semicolon
r_struct
id|vnode
suffix:semicolon
r_struct
id|xfs_inode
suffix:semicolon
r_extern
r_int
id|xfs_acl_inherit
c_func
(paren
r_struct
id|vnode
op_star
comma
r_struct
id|vattr
op_star
comma
id|xfs_acl_t
op_star
)paren
suffix:semicolon
r_extern
r_int
id|xfs_acl_iaccess
c_func
(paren
r_struct
id|xfs_inode
op_star
comma
id|mode_t
comma
id|cred_t
op_star
)paren
suffix:semicolon
r_extern
r_int
id|xfs_acl_get
c_func
(paren
r_struct
id|vnode
op_star
comma
id|xfs_acl_t
op_star
comma
id|xfs_acl_t
op_star
)paren
suffix:semicolon
r_extern
r_int
id|xfs_acl_set
c_func
(paren
r_struct
id|vnode
op_star
comma
id|xfs_acl_t
op_star
comma
id|xfs_acl_t
op_star
)paren
suffix:semicolon
r_extern
r_int
id|xfs_acl_vtoacl
c_func
(paren
r_struct
id|vnode
op_star
comma
id|xfs_acl_t
op_star
comma
id|xfs_acl_t
op_star
)paren
suffix:semicolon
r_extern
r_int
id|xfs_acl_vhasacl_access
c_func
(paren
r_struct
id|vnode
op_star
)paren
suffix:semicolon
r_extern
r_int
id|xfs_acl_vhasacl_default
c_func
(paren
r_struct
id|vnode
op_star
)paren
suffix:semicolon
r_extern
r_int
id|xfs_acl_vset
c_func
(paren
r_struct
id|vnode
op_star
comma
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
id|xfs_acl_vget
c_func
(paren
r_struct
id|vnode
op_star
comma
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
id|xfs_acl_vremove
c_func
(paren
r_struct
id|vnode
op_star
id|vp
comma
r_int
)paren
suffix:semicolon
r_extern
r_struct
id|kmem_zone
op_star
id|xfs_acl_zone
suffix:semicolon
DECL|macro|_ACL_TYPE_ACCESS
mdefine_line|#define _ACL_TYPE_ACCESS&t;1
DECL|macro|_ACL_TYPE_DEFAULT
mdefine_line|#define _ACL_TYPE_DEFAULT&t;2
DECL|macro|_ACL_PERM_INVALID
mdefine_line|#define _ACL_PERM_INVALID(perm) ((perm) &amp; ~(ACL_READ|ACL_WRITE|ACL_EXECUTE))
DECL|macro|_ACL_DECL
mdefine_line|#define _ACL_DECL(a)&t;&t;xfs_acl_t *(a) = NULL
DECL|macro|_ACL_ALLOC
mdefine_line|#define _ACL_ALLOC(a)&t;&t;((a) = kmem_zone_alloc(xfs_acl_zone, KM_SLEEP))
DECL|macro|_ACL_FREE
mdefine_line|#define _ACL_FREE(a)&t;&t;((a)? kmem_zone_free(xfs_acl_zone, (a)) : 0)
DECL|macro|_ACL_ZONE_INIT
mdefine_line|#define _ACL_ZONE_INIT(z,name)&t;((z) = kmem_zone_init(sizeof(xfs_acl_t), name))
DECL|macro|_ACL_ZONE_DESTROY
mdefine_line|#define _ACL_ZONE_DESTROY(z)&t;(kmem_cache_destroy(z))
DECL|macro|_ACL_INHERIT
mdefine_line|#define _ACL_INHERIT(c,v,d)&t;(xfs_acl_inherit(c,v,d))
DECL|macro|_ACL_GET_ACCESS
mdefine_line|#define _ACL_GET_ACCESS(pv,pa)&t;(xfs_acl_vtoacl(pv,pa,NULL) == 0)
DECL|macro|_ACL_GET_DEFAULT
mdefine_line|#define _ACL_GET_DEFAULT(pv,pd) (xfs_acl_vtoacl(pv,NULL,pd) == 0)
DECL|macro|_ACL_ACCESS_EXISTS
mdefine_line|#define _ACL_ACCESS_EXISTS&t;xfs_acl_vhasacl_access
DECL|macro|_ACL_DEFAULT_EXISTS
mdefine_line|#define _ACL_DEFAULT_EXISTS&t;xfs_acl_vhasacl_default
DECL|macro|_ACL_XFS_IACCESS
mdefine_line|#define _ACL_XFS_IACCESS(i,m,c) (XFS_IFORK_Q(i) ? xfs_acl_iaccess(i,m,c) : -1)
macro_line|#else
DECL|macro|xfs_acl_vset
mdefine_line|#define xfs_acl_vset(v,p,sz,t)&t;(-EOPNOTSUPP)
DECL|macro|xfs_acl_vget
mdefine_line|#define xfs_acl_vget(v,p,sz,t)&t;(-EOPNOTSUPP)
DECL|macro|xfs_acl_vremove
mdefine_line|#define xfs_acl_vremove(v,t)&t;(-EOPNOTSUPP)
DECL|macro|_ACL_DECL
mdefine_line|#define _ACL_DECL(a)&t;&t;((void)0)
DECL|macro|_ACL_ALLOC
mdefine_line|#define _ACL_ALLOC(a)&t;&t;(1)&t;/* successfully allocate nothing */
DECL|macro|_ACL_FREE
mdefine_line|#define _ACL_FREE(a)&t;&t;((void)0)
DECL|macro|_ACL_ZONE_INIT
mdefine_line|#define _ACL_ZONE_INIT(z,name)&t;((void)0)
DECL|macro|_ACL_ZONE_DESTROY
mdefine_line|#define _ACL_ZONE_DESTROY(z)&t;((void)0)
DECL|macro|_ACL_INHERIT
mdefine_line|#define _ACL_INHERIT(c,v,d)&t;(0)
DECL|macro|_ACL_GET_ACCESS
mdefine_line|#define _ACL_GET_ACCESS(pv,pa)&t;(0)
DECL|macro|_ACL_GET_DEFAULT
mdefine_line|#define _ACL_GET_DEFAULT(pv,pd) (0)
DECL|macro|_ACL_ACCESS_EXISTS
mdefine_line|#define _ACL_ACCESS_EXISTS&t;(NULL)
DECL|macro|_ACL_DEFAULT_EXISTS
mdefine_line|#define _ACL_DEFAULT_EXISTS&t;(NULL)
DECL|macro|_ACL_XFS_IACCESS
mdefine_line|#define _ACL_XFS_IACCESS(i,m,c) (-1)
macro_line|#endif
macro_line|#endif&t;/* __KERNEL__ */
macro_line|#endif&t;/* __XFS_ACL_H__ */
eof
