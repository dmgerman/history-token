multiline_comment|/*&n; * udf_fs_i.h&n; *&n; * This file is intended for the Linux kernel/module. &n; *&n; * CONTACTS&n; *&t;E-mail regarding any portion of the Linux UDF file system should be&n; *&t;directed to the development team mailing list (run by majordomo):&n; *&t;&t;linux_udf@hpesjro.fc.hp.com&n; *&n; * COPYRIGHT&n; *&t;This file is distributed under the terms of the GNU General Public&n; *&t;License (GPL). Copies of the GPL can be obtained from:&n; *&t;&t;ftp://prep.ai.mit.edu/pub/gnu/GPL&n; *&t;Each contributing author retains all rights to their own work.&n; */
macro_line|#if !defined(_LINUX_UDF_FS_I_H)
DECL|macro|_LINUX_UDF_FS_I_H
mdefine_line|#define _LINUX_UDF_FS_I_H
macro_line|#ifdef __KERNEL__
macro_line|#ifndef _LINUX_UDF_167_H
r_typedef
r_struct
(brace
DECL|member|logicalBlockNum
id|__u32
id|logicalBlockNum
suffix:semicolon
DECL|member|partitionReferenceNum
id|__u16
id|partitionReferenceNum
suffix:semicolon
DECL|typedef|lb_addr
)brace
id|lb_addr
suffix:semicolon
macro_line|#endif
DECL|struct|udf_inode_info
r_struct
id|udf_inode_info
(brace
DECL|member|i_uatime
r_int
id|i_uatime
suffix:semicolon
DECL|member|i_umtime
r_int
id|i_umtime
suffix:semicolon
DECL|member|i_uctime
r_int
id|i_uctime
suffix:semicolon
multiline_comment|/* Physical address of inode */
DECL|member|i_location
id|lb_addr
id|i_location
suffix:semicolon
DECL|member|i_unique
id|__u64
id|i_unique
suffix:semicolon
DECL|member|i_lenEAttr
id|__u32
id|i_lenEAttr
suffix:semicolon
DECL|member|i_lenAlloc
id|__u32
id|i_lenAlloc
suffix:semicolon
DECL|member|i_lenExtents
id|__u64
id|i_lenExtents
suffix:semicolon
DECL|member|i_next_alloc_block
id|__u32
id|i_next_alloc_block
suffix:semicolon
DECL|member|i_next_alloc_goal
id|__u32
id|i_next_alloc_goal
suffix:semicolon
DECL|member|i_alloc_type
r_int
id|i_alloc_type
suffix:colon
l_int|3
suffix:semicolon
DECL|member|i_extended_fe
r_int
id|i_extended_fe
suffix:colon
l_int|1
suffix:semicolon
DECL|member|i_strat_4096
r_int
id|i_strat_4096
suffix:colon
l_int|1
suffix:semicolon
DECL|member|i_new_inode
r_int
id|i_new_inode
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved
r_int
id|reserved
suffix:colon
l_int|26
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
multiline_comment|/* exported IOCTLs, we have &squot;l&squot;, 0x40-0x7f */
DECL|macro|UDF_GETEASIZE
mdefine_line|#define UDF_GETEASIZE   _IOR(&squot;l&squot;, 0x40, int)
DECL|macro|UDF_GETEABLOCK
mdefine_line|#define UDF_GETEABLOCK  _IOR(&squot;l&squot;, 0x41, void *)
DECL|macro|UDF_GETVOLIDENT
mdefine_line|#define UDF_GETVOLIDENT _IOR(&squot;l&squot;, 0x42, void *)
DECL|macro|UDF_RELOCATE_BLOCKS
mdefine_line|#define UDF_RELOCATE_BLOCKS _IOWR(&squot;l&squot;, 0x43, long)
macro_line|#endif /* !defined(_LINUX_UDF_FS_I_H) */
eof
