multiline_comment|/*&n; *  coda_fs_i.h&n; *&n; *  Copyright (C) 1998 Carnegie Mellon University&n; *&n; */
macro_line|#ifndef _LINUX_CODA_FS_I
DECL|macro|_LINUX_CODA_FS_I
mdefine_line|#define _LINUX_CODA_FS_I
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/coda.h&gt;
multiline_comment|/*&n; * coda fs inode data&n; */
DECL|struct|coda_inode_info
r_struct
id|coda_inode_info
(brace
DECL|member|c_fid
r_struct
id|ViceFid
id|c_fid
suffix:semicolon
multiline_comment|/* Coda identifier */
DECL|member|c_flags
id|u_short
id|c_flags
suffix:semicolon
multiline_comment|/* flags (see below) */
DECL|member|c_cilist
r_struct
id|list_head
id|c_cilist
suffix:semicolon
multiline_comment|/* list of all coda inodes */
DECL|member|c_mapcount
r_int
r_int
id|c_mapcount
suffix:semicolon
multiline_comment|/* nr of times this inode is mapped */
DECL|member|c_cached_epoch
r_int
r_int
id|c_cached_epoch
suffix:semicolon
multiline_comment|/* epoch for cached permissions */
DECL|member|c_uid
id|vuid_t
id|c_uid
suffix:semicolon
multiline_comment|/* fsuid for cached permissions */
DECL|member|c_cached_perm
r_int
r_int
id|c_cached_perm
suffix:semicolon
multiline_comment|/* cached access permissions */
DECL|member|vfs_inode
r_struct
id|inode
id|vfs_inode
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * coda fs file private data&n; */
DECL|macro|CODA_MAGIC
mdefine_line|#define CODA_MAGIC 0xC0DAC0DA
DECL|struct|coda_file_info
r_struct
id|coda_file_info
(brace
DECL|member|cfi_magic
r_int
id|cfi_magic
suffix:semicolon
multiline_comment|/* magic number */
DECL|member|cfi_container
r_struct
id|file
op_star
id|cfi_container
suffix:semicolon
multiline_comment|/* container file for this cnode */
DECL|member|cfi_mapcount
r_int
r_int
id|cfi_mapcount
suffix:semicolon
multiline_comment|/* nr of times this file is mapped */
)brace
suffix:semicolon
DECL|macro|CODA_FTOC
mdefine_line|#define CODA_FTOC(file) ((struct coda_file_info *)((file)-&gt;private_data))
multiline_comment|/* flags */
DECL|macro|C_VATTR
mdefine_line|#define C_VATTR       0x1   /* Validity of vattr in inode */
DECL|macro|C_FLUSH
mdefine_line|#define C_FLUSH       0x2   /* used after a flush */
DECL|macro|C_DYING
mdefine_line|#define C_DYING       0x4   /* from venus (which died) */
DECL|macro|C_PURGE
mdefine_line|#define C_PURGE       0x8
r_int
id|coda_cnode_make
c_func
(paren
r_struct
id|inode
op_star
op_star
comma
r_struct
id|ViceFid
op_star
comma
r_struct
id|super_block
op_star
)paren
suffix:semicolon
r_struct
id|inode
op_star
id|coda_iget
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|ViceFid
op_star
id|fid
comma
r_struct
id|coda_vattr
op_star
id|attr
)paren
suffix:semicolon
r_int
id|coda_cnode_makectl
c_func
(paren
r_struct
id|inode
op_star
op_star
id|inode
comma
r_struct
id|super_block
op_star
id|sb
)paren
suffix:semicolon
r_struct
id|inode
op_star
id|coda_fid_to_inode
c_func
(paren
id|ViceFid
op_star
id|fid
comma
r_struct
id|super_block
op_star
id|sb
)paren
suffix:semicolon
r_void
id|coda_replace_fid
c_func
(paren
r_struct
id|inode
op_star
comma
id|ViceFid
op_star
comma
id|ViceFid
op_star
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif
eof
