macro_line|#ifndef __LINUX_UDF_I_H
DECL|macro|__LINUX_UDF_I_H
mdefine_line|#define __LINUX_UDF_I_H
DECL|macro|UDF_I
mdefine_line|#define UDF_I(X)&t;&t;&t;(&amp;((X)-&gt;u.udf_i))
DECL|macro|UDF_I_LOCATION
mdefine_line|#define UDF_I_LOCATION(X)&t;( UDF_I(X)-&gt;i_location )
DECL|macro|UDF_I_LENEATTR
mdefine_line|#define UDF_I_LENEATTR(X)&t;( UDF_I(X)-&gt;i_lenEAttr )
DECL|macro|UDF_I_LENALLOC
mdefine_line|#define UDF_I_LENALLOC(X)&t;( UDF_I(X)-&gt;i_lenAlloc )
DECL|macro|UDF_I_UNIQUE
mdefine_line|#define UDF_I_UNIQUE(X)&t;&t;( UDF_I(X)-&gt;i_unique )
DECL|macro|UDF_I_ALLOCTYPE
mdefine_line|#define UDF_I_ALLOCTYPE(X)&t;( UDF_I(X)-&gt;i_alloc_type )
DECL|macro|UDF_I_EXTENDED_FE
mdefine_line|#define UDF_I_EXTENDED_FE(X)( UDF_I(X)-&gt;i_extended_fe )
DECL|macro|UDF_I_STRAT4096
mdefine_line|#define UDF_I_STRAT4096(X)&t;( UDF_I(X)-&gt;i_strat_4096 )
DECL|macro|UDF_I_NEW_INODE
mdefine_line|#define UDF_I_NEW_INODE(X)&t;( UDF_I(X)-&gt;i_new_inode )
DECL|macro|UDF_I_NEXT_ALLOC_BLOCK
mdefine_line|#define UDF_I_NEXT_ALLOC_BLOCK(X)&t;( UDF_I(X)-&gt;i_next_alloc_block )
DECL|macro|UDF_I_NEXT_ALLOC_GOAL
mdefine_line|#define UDF_I_NEXT_ALLOC_GOAL(X)&t;( UDF_I(X)-&gt;i_next_alloc_goal )
DECL|macro|UDF_I_UATIME
mdefine_line|#define UDF_I_UATIME(X)&t;&t;( UDF_I(X)-&gt;i_uatime )
DECL|macro|UDF_I_UMTIME
mdefine_line|#define UDF_I_UMTIME(X)&t;&t;( UDF_I(X)-&gt;i_umtime )
DECL|macro|UDF_I_UCTIME
mdefine_line|#define UDF_I_UCTIME(X)&t;&t;( UDF_I(X)-&gt;i_uctime )
macro_line|#endif /* !defined(_LINUX_UDF_I_H) */
eof
