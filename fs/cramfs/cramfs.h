macro_line|#ifndef __CRAMFS_H
DECL|macro|__CRAMFS_H
mdefine_line|#define __CRAMFS_H
DECL|macro|CRAMFS_MAGIC
mdefine_line|#define CRAMFS_MAGIC&t;&t;0x28cd3d45&t;/* some random number */
DECL|macro|CRAMFS_SIGNATURE
mdefine_line|#define CRAMFS_SIGNATURE&t;&quot;Compressed ROMFS&quot;
multiline_comment|/*&n; * Reasonably terse representation of the inode data.&n; */
DECL|struct|cramfs_inode
r_struct
id|cramfs_inode
(brace
DECL|member|mode
DECL|member|uid
id|u32
id|mode
suffix:colon
l_int|16
comma
id|uid
suffix:colon
l_int|16
suffix:semicolon
multiline_comment|/* SIZE for device files is i_rdev */
DECL|member|size
DECL|member|gid
id|u32
id|size
suffix:colon
l_int|24
comma
id|gid
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* NAMELEN is the length of the file name, divided by 4 and&n;           rounded up.  (cramfs doesn&squot;t support hard links.) */
multiline_comment|/* OFFSET: For symlinks and non-empty regular files, this&n;&t;   contains the offset (divided by 4) of the file data in&n;&t;   compressed form (starting with an array of block pointers;&n;&t;   see README).  For non-empty directories it is the offset&n;&t;   (divided by 4) of the inode of the first file in that&n;&t;   directory.  For anything else, offset is zero. */
DECL|member|namelen
DECL|member|offset
id|u32
id|namelen
suffix:colon
l_int|6
comma
id|offset
suffix:colon
l_int|26
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Superblock information at the beginning of the FS.&n; */
DECL|struct|cramfs_super
r_struct
id|cramfs_super
(brace
DECL|member|magic
id|u32
id|magic
suffix:semicolon
multiline_comment|/* 0x28cd3d45 - random number */
DECL|member|size
id|u32
id|size
suffix:semicolon
multiline_comment|/* Not used.  mkcramfs currently&n;                                   writes a constant 1&lt;&lt;16 here. */
DECL|member|flags
id|u32
id|flags
suffix:semicolon
multiline_comment|/* 0 */
DECL|member|future
id|u32
id|future
suffix:semicolon
multiline_comment|/* 0 */
DECL|member|signature
id|u8
id|signature
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* &quot;Compressed ROMFS&quot; */
DECL|member|fsid
id|u8
id|fsid
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* random number */
DECL|member|name
id|u8
id|name
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* user-defined name */
DECL|member|root
r_struct
id|cramfs_inode
id|root
suffix:semicolon
multiline_comment|/* Root inode data */
)brace
suffix:semicolon
multiline_comment|/*&n; * Valid values in super.flags.  Currently we refuse to mount&n; * if (flags &amp; ~CRAMFS_SUPPORTED_FLAGS).  Maybe that should be&n; * changed to test super.future instead.&n; */
DECL|macro|CRAMFS_SUPPORTED_FLAGS
mdefine_line|#define CRAMFS_SUPPORTED_FLAGS (0xff)
multiline_comment|/* Uncompression interfaces to the underlying zlib */
r_int
id|cramfs_uncompress_block
c_func
(paren
r_void
op_star
id|dst
comma
r_int
id|dstlen
comma
r_void
op_star
id|src
comma
r_int
id|srclen
)paren
suffix:semicolon
r_int
id|cramfs_uncompress_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|cramfs_uncompress_exit
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
eof
