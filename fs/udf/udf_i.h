macro_line|#ifndef __LINUX_UDF_I_H
DECL|macro|__LINUX_UDF_I_H
mdefine_line|#define __LINUX_UDF_I_H
macro_line|#include &lt;linux/udf_fs_i.h&gt;
DECL|function|UDF_I
r_static
r_inline
r_struct
id|udf_inode_info
op_star
id|UDF_I
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_return
id|list_entry
c_func
(paren
id|inode
comma
r_struct
id|udf_inode_info
comma
id|vfs_inode
)paren
suffix:semicolon
)brace
DECL|macro|UDF_I_LOCATION
mdefine_line|#define UDF_I_LOCATION(X)&t;( UDF_I(X)-&gt;i_location )
DECL|macro|UDF_I_LENEATTR
mdefine_line|#define UDF_I_LENEATTR(X)&t;( UDF_I(X)-&gt;i_lenEAttr )
DECL|macro|UDF_I_LENALLOC
mdefine_line|#define UDF_I_LENALLOC(X)&t;( UDF_I(X)-&gt;i_lenAlloc )
DECL|macro|UDF_I_LENEXTENTS
mdefine_line|#define UDF_I_LENEXTENTS(X)&t;( UDF_I(X)-&gt;i_lenExtents )
DECL|macro|UDF_I_UNIQUE
mdefine_line|#define UDF_I_UNIQUE(X)&t;&t;( UDF_I(X)-&gt;i_unique )
DECL|macro|UDF_I_ALLOCTYPE
mdefine_line|#define UDF_I_ALLOCTYPE(X)&t;( UDF_I(X)-&gt;i_alloc_type )
DECL|macro|UDF_I_EFE
mdefine_line|#define UDF_I_EFE(X)&t;&t;( UDF_I(X)-&gt;i_efe )
DECL|macro|UDF_I_USE
mdefine_line|#define UDF_I_USE(X)&t;&t;( UDF_I(X)-&gt;i_use )
DECL|macro|UDF_I_STRAT4096
mdefine_line|#define UDF_I_STRAT4096(X)&t;( UDF_I(X)-&gt;i_strat4096 )
DECL|macro|UDF_I_NEXT_ALLOC_BLOCK
mdefine_line|#define UDF_I_NEXT_ALLOC_BLOCK(X)&t;( UDF_I(X)-&gt;i_next_alloc_block )
DECL|macro|UDF_I_NEXT_ALLOC_GOAL
mdefine_line|#define UDF_I_NEXT_ALLOC_GOAL(X)&t;( UDF_I(X)-&gt;i_next_alloc_goal )
DECL|macro|UDF_I_UMTIME
mdefine_line|#define UDF_I_UMTIME(X)&t;&t;( UDF_I(X)-&gt;i_umtime )
DECL|macro|UDF_I_UCTIME
mdefine_line|#define UDF_I_UCTIME(X)&t;&t;( UDF_I(X)-&gt;i_uctime )
DECL|macro|UDF_I_CRTIME
mdefine_line|#define UDF_I_CRTIME(X)&t;&t;( UDF_I(X)-&gt;i_crtime )
DECL|macro|UDF_I_UCRTIME
mdefine_line|#define UDF_I_UCRTIME(X)&t;( UDF_I(X)-&gt;i_ucrtime )
DECL|macro|UDF_I_SAD
mdefine_line|#define UDF_I_SAD(X)&t;&t;( UDF_I(X)-&gt;i_ext.i_sad )
DECL|macro|UDF_I_LAD
mdefine_line|#define UDF_I_LAD(X)&t;&t;( UDF_I(X)-&gt;i_ext.i_lad )
DECL|macro|UDF_I_DATA
mdefine_line|#define UDF_I_DATA(X)&t;&t;( UDF_I(X)-&gt;i_ext.i_data )
macro_line|#endif /* !defined(_LINUX_UDF_I_H) */
eof
