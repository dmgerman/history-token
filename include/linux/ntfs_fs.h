macro_line|#ifndef _LINUX_NTFS_FS_H
DECL|macro|_LINUX_NTFS_FS_H
mdefine_line|#define _LINUX_NTFS_FS_H
macro_line|#include &lt;asm/byteorder.h&gt;
DECL|macro|NTFS_SECTOR_BITS
mdefine_line|#define NTFS_SECTOR_BITS 9
DECL|macro|NTFS_SECTOR_SIZE
mdefine_line|#define NTFS_SECTOR_SIZE 512
multiline_comment|/*&n; * Attribute flags (16-bit).&n; */
r_typedef
r_enum
(brace
DECL|enumerator|ATTR_IS_COMPRESSED
id|ATTR_IS_COMPRESSED
op_assign
id|cpu_to_le16
c_func
(paren
l_int|0x0001
)paren
comma
DECL|enumerator|ATTR_COMPRESSION_MASK
id|ATTR_COMPRESSION_MASK
op_assign
id|cpu_to_le16
c_func
(paren
l_int|0x00ff
)paren
comma
multiline_comment|/* Compression method&n;&t;&t;&t;&t;&t;&t;&t; * mask. Also, first&n;&t;&t;&t;&t;&t;&t;&t; * illegal value. */
DECL|enumerator|ATTR_IS_ENCRYPTED
id|ATTR_IS_ENCRYPTED
op_assign
id|cpu_to_le16
c_func
(paren
l_int|0x4000
)paren
comma
DECL|enumerator|ATTR_IS_SPARSE
id|ATTR_IS_SPARSE
op_assign
id|cpu_to_le16
c_func
(paren
l_int|0x8000
)paren
comma
DECL|typedef|ATTR_FLAGS
)brace
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
id|ATTR_FLAGS
suffix:semicolon
multiline_comment|/*&n; * The two zones from which to allocate clusters.&n; */
r_typedef
r_enum
(brace
DECL|enumerator|MFT_ZONE
id|MFT_ZONE
comma
DECL|enumerator|DATA_ZONE
id|DATA_ZONE
DECL|typedef|NTFS_CLUSTER_ALLOCATION_ZONES
)brace
id|NTFS_CLUSTER_ALLOCATION_ZONES
suffix:semicolon
macro_line|#endif
eof
