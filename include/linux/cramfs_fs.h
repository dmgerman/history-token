macro_line|#ifndef __CRAMFS_H
DECL|macro|__CRAMFS_H
mdefine_line|#define __CRAMFS_H
macro_line|#ifndef __KERNEL__
DECL|typedef|u8
r_typedef
r_int
r_char
id|u8
suffix:semicolon
DECL|typedef|u16
r_typedef
r_int
r_int
id|u16
suffix:semicolon
DECL|typedef|u32
r_typedef
r_int
r_int
id|u32
suffix:semicolon
macro_line|#endif
DECL|macro|CRAMFS_MAGIC
mdefine_line|#define CRAMFS_MAGIC&t;&t;0x28cd3d45&t;/* some random number */
DECL|macro|CRAMFS_SIGNATURE
mdefine_line|#define CRAMFS_SIGNATURE&t;&quot;Compressed ROMFS&quot;
multiline_comment|/*&n; * Width of various bitfields in struct cramfs_inode.&n; * Primarily used to generate warnings in mkcramfs.&n; */
DECL|macro|CRAMFS_MODE_WIDTH
mdefine_line|#define CRAMFS_MODE_WIDTH 16
DECL|macro|CRAMFS_UID_WIDTH
mdefine_line|#define CRAMFS_UID_WIDTH 16
DECL|macro|CRAMFS_SIZE_WIDTH
mdefine_line|#define CRAMFS_SIZE_WIDTH 24
DECL|macro|CRAMFS_GID_WIDTH
mdefine_line|#define CRAMFS_GID_WIDTH 8
DECL|macro|CRAMFS_NAMELEN_WIDTH
mdefine_line|#define CRAMFS_NAMELEN_WIDTH 6
DECL|macro|CRAMFS_OFFSET_WIDTH
mdefine_line|#define CRAMFS_OFFSET_WIDTH 26
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
id|CRAMFS_MODE_WIDTH
comma
id|uid
suffix:colon
id|CRAMFS_UID_WIDTH
suffix:semicolon
multiline_comment|/* SIZE for device files is i_rdev */
DECL|member|size
DECL|member|gid
id|u32
id|size
suffix:colon
id|CRAMFS_SIZE_WIDTH
comma
id|gid
suffix:colon
id|CRAMFS_GID_WIDTH
suffix:semicolon
multiline_comment|/* NAMELEN is the length of the file name, divided by 4 and&n;           rounded up.  (cramfs doesn&squot;t support hard links.) */
multiline_comment|/* OFFSET: For symlinks and non-empty regular files, this&n;&t;   contains the offset (divided by 4) of the file data in&n;&t;   compressed form (starting with an array of block pointers;&n;&t;   see README).  For non-empty directories it is the offset&n;&t;   (divided by 4) of the inode of the first file in that&n;&t;   directory.  For anything else, offset is zero. */
DECL|member|namelen
DECL|member|offset
id|u32
id|namelen
suffix:colon
id|CRAMFS_NAMELEN_WIDTH
comma
id|offset
suffix:colon
id|CRAMFS_OFFSET_WIDTH
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|cramfs_info
r_struct
id|cramfs_info
(brace
DECL|member|crc
id|u32
id|crc
suffix:semicolon
DECL|member|edition
id|u32
id|edition
suffix:semicolon
DECL|member|blocks
id|u32
id|blocks
suffix:semicolon
DECL|member|files
id|u32
id|files
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
multiline_comment|/* length in bytes */
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
r_struct
id|cramfs_info
id|fsid
suffix:semicolon
multiline_comment|/* unique filesystem info */
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
multiline_comment|/*&n; * Feature flags&n; *&n; * 0x00000000 - 0x000000ff: features that work for all past kernels&n; * 0x00000100 - 0xffffffff: features that don&squot;t work for past kernels&n; */
DECL|macro|CRAMFS_FLAG_FSID_VERSION_2
mdefine_line|#define CRAMFS_FLAG_FSID_VERSION_2&t;0x00000001&t;/* fsid version #2 */
DECL|macro|CRAMFS_FLAG_SORTED_DIRS
mdefine_line|#define CRAMFS_FLAG_SORTED_DIRS&t;&t;0x00000002&t;/* sorted dirs */
DECL|macro|CRAMFS_FLAG_HOLES
mdefine_line|#define CRAMFS_FLAG_HOLES&t;&t;0x00000100&t;/* support for holes */
DECL|macro|CRAMFS_FLAG_WRONG_SIGNATURE
mdefine_line|#define CRAMFS_FLAG_WRONG_SIGNATURE&t;0x00000200&t;/* reserved */
DECL|macro|CRAMFS_FLAG_SHIFTED_ROOT_OFFSET
mdefine_line|#define CRAMFS_FLAG_SHIFTED_ROOT_OFFSET&t;0x00000400&t;/* shifted root fs */
multiline_comment|/*&n; * Valid values in super.flags.  Currently we refuse to mount&n; * if (flags &amp; ~CRAMFS_SUPPORTED_FLAGS).  Maybe that should be&n; * changed to test super.future instead.&n; */
DECL|macro|CRAMFS_SUPPORTED_FLAGS
mdefine_line|#define CRAMFS_SUPPORTED_FLAGS (0x7ff)
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
