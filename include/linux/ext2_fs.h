multiline_comment|/*&n; *  linux/include/linux/ext2_fs.h&n; *&n; * Copyright (C) 1992, 1993, 1994, 1995&n; * Remy Card (card@masi.ibp.fr)&n; * Laboratoire MASI - Institut Blaise Pascal&n; * Universite Pierre et Marie Curie (Paris VI)&n; *&n; *  from&n; *&n; *  linux/include/linux/minix_fs.h&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; */
macro_line|#ifndef _LINUX_EXT2_FS_H
DECL|macro|_LINUX_EXT2_FS_H
mdefine_line|#define _LINUX_EXT2_FS_H
macro_line|#include &lt;linux/types.h&gt;
multiline_comment|/*&n; * The second extended filesystem constants/structures&n; */
multiline_comment|/*&n; * Define EXT2FS_DEBUG to produce debug messages&n; */
DECL|macro|EXT2FS_DEBUG
macro_line|#undef EXT2FS_DEBUG
multiline_comment|/*&n; * Define EXT2_PREALLOCATE to preallocate data blocks for expanding files&n; */
DECL|macro|EXT2_PREALLOCATE
mdefine_line|#define EXT2_PREALLOCATE
DECL|macro|EXT2_DEFAULT_PREALLOC_BLOCKS
mdefine_line|#define EXT2_DEFAULT_PREALLOC_BLOCKS&t;8
multiline_comment|/*&n; * The second extended file system version&n; */
DECL|macro|EXT2FS_DATE
mdefine_line|#define EXT2FS_DATE&t;&t;&quot;95/08/09&quot;
DECL|macro|EXT2FS_VERSION
mdefine_line|#define EXT2FS_VERSION&t;&t;&quot;0.5b&quot;
multiline_comment|/*&n; * Debug code&n; */
macro_line|#ifdef EXT2FS_DEBUG
DECL|macro|ext2_debug
macro_line|#&t;define ext2_debug(f, a...)&t;{ &bslash;&n;&t;&t;&t;&t;&t;printk (&quot;EXT2-fs DEBUG (%s, %d): %s:&quot;, &bslash;&n;&t;&t;&t;&t;&t;&t;__FILE__, __LINE__, __FUNCTION__); &bslash;&n;&t;&t;&t;&t;  &t;printk (f, ## a); &bslash;&n;&t;&t;&t;&t;&t;}
macro_line|#else
DECL|macro|ext2_debug
macro_line|#&t;define ext2_debug(f, a...)&t;/**/
macro_line|#endif
multiline_comment|/*&n; * Special inode numbers&n; */
DECL|macro|EXT2_BAD_INO
mdefine_line|#define&t;EXT2_BAD_INO&t;&t; 1&t;/* Bad blocks inode */
DECL|macro|EXT2_ROOT_INO
mdefine_line|#define EXT2_ROOT_INO&t;&t; 2&t;/* Root inode */
DECL|macro|EXT2_ACL_IDX_INO
mdefine_line|#define EXT2_ACL_IDX_INO&t; 3&t;/* ACL inode */
DECL|macro|EXT2_ACL_DATA_INO
mdefine_line|#define EXT2_ACL_DATA_INO&t; 4&t;/* ACL inode */
DECL|macro|EXT2_BOOT_LOADER_INO
mdefine_line|#define EXT2_BOOT_LOADER_INO&t; 5&t;/* Boot loader inode */
DECL|macro|EXT2_UNDEL_DIR_INO
mdefine_line|#define EXT2_UNDEL_DIR_INO&t; 6&t;/* Undelete directory inode */
multiline_comment|/* First non-reserved inode for old ext2 filesystems */
DECL|macro|EXT2_GOOD_OLD_FIRST_INO
mdefine_line|#define EXT2_GOOD_OLD_FIRST_INO&t;11
multiline_comment|/*&n; * The second extended file system magic number&n; */
DECL|macro|EXT2_SUPER_MAGIC
mdefine_line|#define EXT2_SUPER_MAGIC&t;0xEF53
multiline_comment|/*&n; * Maximal count of links to a file&n; */
DECL|macro|EXT2_LINK_MAX
mdefine_line|#define EXT2_LINK_MAX&t;&t;32000
multiline_comment|/*&n; * Macro-instructions used to manage several block sizes&n; */
DECL|macro|EXT2_MIN_BLOCK_SIZE
mdefine_line|#define EXT2_MIN_BLOCK_SIZE&t;&t;1024
DECL|macro|EXT2_MAX_BLOCK_SIZE
mdefine_line|#define&t;EXT2_MAX_BLOCK_SIZE&t;&t;4096
DECL|macro|EXT2_MIN_BLOCK_LOG_SIZE
mdefine_line|#define EXT2_MIN_BLOCK_LOG_SIZE&t;&t;  10
macro_line|#ifdef __KERNEL__
DECL|macro|EXT2_BLOCK_SIZE
macro_line|# define EXT2_BLOCK_SIZE(s)&t;&t;((s)-&gt;s_blocksize)
macro_line|#else
DECL|macro|EXT2_BLOCK_SIZE
macro_line|# define EXT2_BLOCK_SIZE(s)&t;&t;(EXT2_MIN_BLOCK_SIZE &lt;&lt; (s)-&gt;s_log_block_size)
macro_line|#endif
DECL|macro|EXT2_ACLE_PER_BLOCK
mdefine_line|#define EXT2_ACLE_PER_BLOCK(s)&t;&t;(EXT2_BLOCK_SIZE(s) / sizeof (struct ext2_acl_entry))
DECL|macro|EXT2_ADDR_PER_BLOCK
mdefine_line|#define&t;EXT2_ADDR_PER_BLOCK(s)&t;&t;(EXT2_BLOCK_SIZE(s) / sizeof (__u32))
macro_line|#ifdef __KERNEL__
DECL|macro|EXT2_BLOCK_SIZE_BITS
macro_line|# define EXT2_BLOCK_SIZE_BITS(s)&t;((s)-&gt;s_blocksize_bits)
macro_line|#else
DECL|macro|EXT2_BLOCK_SIZE_BITS
macro_line|# define EXT2_BLOCK_SIZE_BITS(s)&t;((s)-&gt;s_log_block_size + 10)
macro_line|#endif
macro_line|#ifdef __KERNEL__
DECL|macro|EXT2_ADDR_PER_BLOCK_BITS
mdefine_line|#define&t;EXT2_ADDR_PER_BLOCK_BITS(s)&t;((s)-&gt;u.ext2_sb.s_addr_per_block_bits)
DECL|macro|EXT2_INODE_SIZE
mdefine_line|#define EXT2_INODE_SIZE(s)&t;&t;((s)-&gt;u.ext2_sb.s_inode_size)
DECL|macro|EXT2_FIRST_INO
mdefine_line|#define EXT2_FIRST_INO(s)&t;&t;((s)-&gt;u.ext2_sb.s_first_ino)
macro_line|#else
DECL|macro|EXT2_INODE_SIZE
mdefine_line|#define EXT2_INODE_SIZE(s)&t;(((s)-&gt;s_rev_level == EXT2_GOOD_OLD_REV) ? &bslash;&n;&t;&t;&t;&t; EXT2_GOOD_OLD_INODE_SIZE : &bslash;&n;&t;&t;&t;&t; (s)-&gt;s_inode_size)
DECL|macro|EXT2_FIRST_INO
mdefine_line|#define EXT2_FIRST_INO(s)&t;(((s)-&gt;s_rev_level == EXT2_GOOD_OLD_REV) ? &bslash;&n;&t;&t;&t;&t; EXT2_GOOD_OLD_FIRST_INO : &bslash;&n;&t;&t;&t;&t; (s)-&gt;s_first_ino)
macro_line|#endif
multiline_comment|/*&n; * Macro-instructions used to manage fragments&n; */
DECL|macro|EXT2_MIN_FRAG_SIZE
mdefine_line|#define EXT2_MIN_FRAG_SIZE&t;&t;1024
DECL|macro|EXT2_MAX_FRAG_SIZE
mdefine_line|#define&t;EXT2_MAX_FRAG_SIZE&t;&t;4096
DECL|macro|EXT2_MIN_FRAG_LOG_SIZE
mdefine_line|#define EXT2_MIN_FRAG_LOG_SIZE&t;&t;  10
macro_line|#ifdef __KERNEL__
DECL|macro|EXT2_FRAG_SIZE
macro_line|# define EXT2_FRAG_SIZE(s)&t;&t;((s)-&gt;u.ext2_sb.s_frag_size)
DECL|macro|EXT2_FRAGS_PER_BLOCK
macro_line|# define EXT2_FRAGS_PER_BLOCK(s)&t;((s)-&gt;u.ext2_sb.s_frags_per_block)
macro_line|#else
DECL|macro|EXT2_FRAG_SIZE
macro_line|# define EXT2_FRAG_SIZE(s)&t;&t;(EXT2_MIN_FRAG_SIZE &lt;&lt; (s)-&gt;s_log_frag_size)
DECL|macro|EXT2_FRAGS_PER_BLOCK
macro_line|# define EXT2_FRAGS_PER_BLOCK(s)&t;(EXT2_BLOCK_SIZE(s) / EXT2_FRAG_SIZE(s))
macro_line|#endif
multiline_comment|/*&n; * ACL structures&n; */
DECL|struct|ext2_acl_header
r_struct
id|ext2_acl_header
multiline_comment|/* Header of Access Control Lists */
(brace
DECL|member|aclh_size
id|__u32
id|aclh_size
suffix:semicolon
DECL|member|aclh_file_count
id|__u32
id|aclh_file_count
suffix:semicolon
DECL|member|aclh_acle_count
id|__u32
id|aclh_acle_count
suffix:semicolon
DECL|member|aclh_first_acle
id|__u32
id|aclh_first_acle
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ext2_acl_entry
r_struct
id|ext2_acl_entry
multiline_comment|/* Access Control List Entry */
(brace
DECL|member|acle_size
id|__u32
id|acle_size
suffix:semicolon
DECL|member|acle_perms
id|__u16
id|acle_perms
suffix:semicolon
multiline_comment|/* Access permissions */
DECL|member|acle_type
id|__u16
id|acle_type
suffix:semicolon
multiline_comment|/* Type of entry */
DECL|member|acle_tag
id|__u16
id|acle_tag
suffix:semicolon
multiline_comment|/* User or group identity */
DECL|member|acle_pad1
id|__u16
id|acle_pad1
suffix:semicolon
DECL|member|acle_next
id|__u32
id|acle_next
suffix:semicolon
multiline_comment|/* Pointer on next entry for the */
multiline_comment|/* same inode or on next free entry */
)brace
suffix:semicolon
multiline_comment|/*&n; * Structure of a blocks group descriptor&n; */
DECL|struct|ext2_group_desc
r_struct
id|ext2_group_desc
(brace
DECL|member|bg_block_bitmap
id|__u32
id|bg_block_bitmap
suffix:semicolon
multiline_comment|/* Blocks bitmap block */
DECL|member|bg_inode_bitmap
id|__u32
id|bg_inode_bitmap
suffix:semicolon
multiline_comment|/* Inodes bitmap block */
DECL|member|bg_inode_table
id|__u32
id|bg_inode_table
suffix:semicolon
multiline_comment|/* Inodes table block */
DECL|member|bg_free_blocks_count
id|__u16
id|bg_free_blocks_count
suffix:semicolon
multiline_comment|/* Free blocks count */
DECL|member|bg_free_inodes_count
id|__u16
id|bg_free_inodes_count
suffix:semicolon
multiline_comment|/* Free inodes count */
DECL|member|bg_used_dirs_count
id|__u16
id|bg_used_dirs_count
suffix:semicolon
multiline_comment|/* Directories count */
DECL|member|bg_pad
id|__u16
id|bg_pad
suffix:semicolon
DECL|member|bg_reserved
id|__u32
id|bg_reserved
(braket
l_int|3
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Macro-instructions used to manage group descriptors&n; */
macro_line|#ifdef __KERNEL__
DECL|macro|EXT2_BLOCKS_PER_GROUP
macro_line|# define EXT2_BLOCKS_PER_GROUP(s)&t;((s)-&gt;u.ext2_sb.s_blocks_per_group)
DECL|macro|EXT2_DESC_PER_BLOCK
macro_line|# define EXT2_DESC_PER_BLOCK(s)&t;&t;((s)-&gt;u.ext2_sb.s_desc_per_block)
DECL|macro|EXT2_INODES_PER_GROUP
macro_line|# define EXT2_INODES_PER_GROUP(s)&t;((s)-&gt;u.ext2_sb.s_inodes_per_group)
DECL|macro|EXT2_DESC_PER_BLOCK_BITS
macro_line|# define EXT2_DESC_PER_BLOCK_BITS(s)&t;((s)-&gt;u.ext2_sb.s_desc_per_block_bits)
macro_line|#else
DECL|macro|EXT2_BLOCKS_PER_GROUP
macro_line|# define EXT2_BLOCKS_PER_GROUP(s)&t;((s)-&gt;s_blocks_per_group)
DECL|macro|EXT2_DESC_PER_BLOCK
macro_line|# define EXT2_DESC_PER_BLOCK(s)&t;&t;(EXT2_BLOCK_SIZE(s) / sizeof (struct ext2_group_desc))
DECL|macro|EXT2_INODES_PER_GROUP
macro_line|# define EXT2_INODES_PER_GROUP(s)&t;((s)-&gt;s_inodes_per_group)
macro_line|#endif
multiline_comment|/*&n; * Constants relative to the data blocks&n; */
DECL|macro|EXT2_NDIR_BLOCKS
mdefine_line|#define&t;EXT2_NDIR_BLOCKS&t;&t;12
DECL|macro|EXT2_IND_BLOCK
mdefine_line|#define&t;EXT2_IND_BLOCK&t;&t;&t;EXT2_NDIR_BLOCKS
DECL|macro|EXT2_DIND_BLOCK
mdefine_line|#define&t;EXT2_DIND_BLOCK&t;&t;&t;(EXT2_IND_BLOCK + 1)
DECL|macro|EXT2_TIND_BLOCK
mdefine_line|#define&t;EXT2_TIND_BLOCK&t;&t;&t;(EXT2_DIND_BLOCK + 1)
DECL|macro|EXT2_N_BLOCKS
mdefine_line|#define&t;EXT2_N_BLOCKS&t;&t;&t;(EXT2_TIND_BLOCK + 1)
multiline_comment|/*&n; * Inode flags&n; */
DECL|macro|EXT2_SECRM_FL
mdefine_line|#define&t;EXT2_SECRM_FL&t;&t;&t;0x00000001 /* Secure deletion */
DECL|macro|EXT2_UNRM_FL
mdefine_line|#define&t;EXT2_UNRM_FL&t;&t;&t;0x00000002 /* Undelete */
DECL|macro|EXT2_COMPR_FL
mdefine_line|#define&t;EXT2_COMPR_FL&t;&t;&t;0x00000004 /* Compress file */
DECL|macro|EXT2_SYNC_FL
mdefine_line|#define EXT2_SYNC_FL&t;&t;&t;0x00000008 /* Synchronous updates */
DECL|macro|EXT2_IMMUTABLE_FL
mdefine_line|#define EXT2_IMMUTABLE_FL&t;&t;0x00000010 /* Immutable file */
DECL|macro|EXT2_APPEND_FL
mdefine_line|#define EXT2_APPEND_FL&t;&t;&t;0x00000020 /* writes to file may only append */
DECL|macro|EXT2_NODUMP_FL
mdefine_line|#define EXT2_NODUMP_FL&t;&t;&t;0x00000040 /* do not dump file */
DECL|macro|EXT2_NOATIME_FL
mdefine_line|#define EXT2_NOATIME_FL&t;&t;&t;0x00000080 /* do not update atime */
multiline_comment|/* Reserved for compression usage... */
DECL|macro|EXT2_DIRTY_FL
mdefine_line|#define EXT2_DIRTY_FL&t;&t;&t;0x00000100
DECL|macro|EXT2_COMPRBLK_FL
mdefine_line|#define EXT2_COMPRBLK_FL&t;&t;0x00000200 /* One or more compressed clusters */
DECL|macro|EXT2_NOCOMP_FL
mdefine_line|#define EXT2_NOCOMP_FL&t;&t;&t;0x00000400 /* Don&squot;t compress */
DECL|macro|EXT2_ECOMPR_FL
mdefine_line|#define EXT2_ECOMPR_FL&t;&t;&t;0x00000800 /* Compression error */
multiline_comment|/* End compression flags --- maybe not all used */
DECL|macro|EXT2_BTREE_FL
mdefine_line|#define EXT2_BTREE_FL&t;&t;&t;0x00001000 /* btree format dir */
DECL|macro|EXT2_RESERVED_FL
mdefine_line|#define EXT2_RESERVED_FL&t;&t;0x80000000 /* reserved for ext2 lib */
DECL|macro|EXT2_FL_USER_VISIBLE
mdefine_line|#define EXT2_FL_USER_VISIBLE&t;&t;0x00001FFF /* User visible flags */
DECL|macro|EXT2_FL_USER_MODIFIABLE
mdefine_line|#define EXT2_FL_USER_MODIFIABLE&t;&t;0x000000FF /* User modifiable flags */
multiline_comment|/*&n; * ioctl commands&n; */
DECL|macro|EXT2_IOC_GETFLAGS
mdefine_line|#define&t;EXT2_IOC_GETFLAGS&t;&t;_IOR(&squot;f&squot;, 1, long)
DECL|macro|EXT2_IOC_SETFLAGS
mdefine_line|#define&t;EXT2_IOC_SETFLAGS&t;&t;_IOW(&squot;f&squot;, 2, long)
DECL|macro|EXT2_IOC_GETVERSION
mdefine_line|#define&t;EXT2_IOC_GETVERSION&t;&t;_IOR(&squot;v&squot;, 1, long)
DECL|macro|EXT2_IOC_SETVERSION
mdefine_line|#define&t;EXT2_IOC_SETVERSION&t;&t;_IOW(&squot;v&squot;, 2, long)
multiline_comment|/*&n; * Structure of an inode on the disk&n; */
DECL|struct|ext2_inode
r_struct
id|ext2_inode
(brace
DECL|member|i_mode
id|__u16
id|i_mode
suffix:semicolon
multiline_comment|/* File mode */
DECL|member|i_uid
id|__u16
id|i_uid
suffix:semicolon
multiline_comment|/* Low 16 bits of Owner Uid */
DECL|member|i_size
id|__u32
id|i_size
suffix:semicolon
multiline_comment|/* Size in bytes */
DECL|member|i_atime
id|__u32
id|i_atime
suffix:semicolon
multiline_comment|/* Access time */
DECL|member|i_ctime
id|__u32
id|i_ctime
suffix:semicolon
multiline_comment|/* Creation time */
DECL|member|i_mtime
id|__u32
id|i_mtime
suffix:semicolon
multiline_comment|/* Modification time */
DECL|member|i_dtime
id|__u32
id|i_dtime
suffix:semicolon
multiline_comment|/* Deletion Time */
DECL|member|i_gid
id|__u16
id|i_gid
suffix:semicolon
multiline_comment|/* Low 16 bits of Group Id */
DECL|member|i_links_count
id|__u16
id|i_links_count
suffix:semicolon
multiline_comment|/* Links count */
DECL|member|i_blocks
id|__u32
id|i_blocks
suffix:semicolon
multiline_comment|/* Blocks count */
DECL|member|i_flags
id|__u32
id|i_flags
suffix:semicolon
multiline_comment|/* File flags */
r_union
(brace
r_struct
(brace
DECL|member|l_i_reserved1
id|__u32
id|l_i_reserved1
suffix:semicolon
DECL|member|linux1
)brace
id|linux1
suffix:semicolon
r_struct
(brace
DECL|member|h_i_translator
id|__u32
id|h_i_translator
suffix:semicolon
DECL|member|hurd1
)brace
id|hurd1
suffix:semicolon
r_struct
(brace
DECL|member|m_i_reserved1
id|__u32
id|m_i_reserved1
suffix:semicolon
DECL|member|masix1
)brace
id|masix1
suffix:semicolon
DECL|member|osd1
)brace
id|osd1
suffix:semicolon
multiline_comment|/* OS dependent 1 */
DECL|member|i_block
id|__u32
id|i_block
(braket
id|EXT2_N_BLOCKS
)braket
suffix:semicolon
multiline_comment|/* Pointers to blocks */
DECL|member|i_generation
id|__u32
id|i_generation
suffix:semicolon
multiline_comment|/* File version (for NFS) */
DECL|member|i_file_acl
id|__u32
id|i_file_acl
suffix:semicolon
multiline_comment|/* File ACL */
DECL|member|i_dir_acl
id|__u32
id|i_dir_acl
suffix:semicolon
multiline_comment|/* Directory ACL */
DECL|member|i_faddr
id|__u32
id|i_faddr
suffix:semicolon
multiline_comment|/* Fragment address */
r_union
(brace
r_struct
(brace
DECL|member|l_i_frag
id|__u8
id|l_i_frag
suffix:semicolon
multiline_comment|/* Fragment number */
DECL|member|l_i_fsize
id|__u8
id|l_i_fsize
suffix:semicolon
multiline_comment|/* Fragment size */
DECL|member|i_pad1
id|__u16
id|i_pad1
suffix:semicolon
DECL|member|l_i_uid_high
id|__u16
id|l_i_uid_high
suffix:semicolon
multiline_comment|/* these 2 fields    */
DECL|member|l_i_gid_high
id|__u16
id|l_i_gid_high
suffix:semicolon
multiline_comment|/* were reserved2[0] */
DECL|member|l_i_reserved2
id|__u32
id|l_i_reserved2
suffix:semicolon
DECL|member|linux2
)brace
id|linux2
suffix:semicolon
r_struct
(brace
DECL|member|h_i_frag
id|__u8
id|h_i_frag
suffix:semicolon
multiline_comment|/* Fragment number */
DECL|member|h_i_fsize
id|__u8
id|h_i_fsize
suffix:semicolon
multiline_comment|/* Fragment size */
DECL|member|h_i_mode_high
id|__u16
id|h_i_mode_high
suffix:semicolon
DECL|member|h_i_uid_high
id|__u16
id|h_i_uid_high
suffix:semicolon
DECL|member|h_i_gid_high
id|__u16
id|h_i_gid_high
suffix:semicolon
DECL|member|h_i_author
id|__u32
id|h_i_author
suffix:semicolon
DECL|member|hurd2
)brace
id|hurd2
suffix:semicolon
r_struct
(brace
DECL|member|m_i_frag
id|__u8
id|m_i_frag
suffix:semicolon
multiline_comment|/* Fragment number */
DECL|member|m_i_fsize
id|__u8
id|m_i_fsize
suffix:semicolon
multiline_comment|/* Fragment size */
DECL|member|m_pad1
id|__u16
id|m_pad1
suffix:semicolon
DECL|member|m_i_reserved2
id|__u32
id|m_i_reserved2
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|masix2
)brace
id|masix2
suffix:semicolon
DECL|member|osd2
)brace
id|osd2
suffix:semicolon
multiline_comment|/* OS dependent 2 */
)brace
suffix:semicolon
DECL|macro|i_size_high
mdefine_line|#define i_size_high&t;i_dir_acl
macro_line|#if defined(__KERNEL__) || defined(__linux__)
DECL|macro|i_reserved1
mdefine_line|#define i_reserved1&t;osd1.linux1.l_i_reserved1
DECL|macro|i_frag
mdefine_line|#define i_frag&t;&t;osd2.linux2.l_i_frag
DECL|macro|i_fsize
mdefine_line|#define i_fsize&t;&t;osd2.linux2.l_i_fsize
DECL|macro|i_uid_low
mdefine_line|#define i_uid_low&t;i_uid
DECL|macro|i_gid_low
mdefine_line|#define i_gid_low&t;i_gid
DECL|macro|i_uid_high
mdefine_line|#define i_uid_high&t;osd2.linux2.l_i_uid_high
DECL|macro|i_gid_high
mdefine_line|#define i_gid_high&t;osd2.linux2.l_i_gid_high
DECL|macro|i_reserved2
mdefine_line|#define i_reserved2&t;osd2.linux2.l_i_reserved2
macro_line|#endif
macro_line|#ifdef&t;__hurd__
DECL|macro|i_translator
mdefine_line|#define i_translator&t;osd1.hurd1.h_i_translator
DECL|macro|i_frag
mdefine_line|#define i_frag&t;&t;osd2.hurd2.h_i_frag;
DECL|macro|i_fsize
mdefine_line|#define i_fsize&t;&t;osd2.hurd2.h_i_fsize;
DECL|macro|i_uid_high
mdefine_line|#define i_uid_high&t;osd2.hurd2.h_i_uid_high
DECL|macro|i_gid_high
mdefine_line|#define i_gid_high&t;osd2.hurd2.h_i_gid_high
DECL|macro|i_author
mdefine_line|#define i_author&t;osd2.hurd2.h_i_author
macro_line|#endif
macro_line|#ifdef&t;__masix__
DECL|macro|i_reserved1
mdefine_line|#define i_reserved1&t;osd1.masix1.m_i_reserved1
DECL|macro|i_frag
mdefine_line|#define i_frag&t;&t;osd2.masix2.m_i_frag
DECL|macro|i_fsize
mdefine_line|#define i_fsize&t;&t;osd2.masix2.m_i_fsize
DECL|macro|i_reserved2
mdefine_line|#define i_reserved2&t;osd2.masix2.m_i_reserved2
macro_line|#endif
multiline_comment|/*&n; * File system states&n; */
DECL|macro|EXT2_VALID_FS
mdefine_line|#define&t;EXT2_VALID_FS&t;&t;&t;0x0001&t;/* Unmounted cleanly */
DECL|macro|EXT2_ERROR_FS
mdefine_line|#define&t;EXT2_ERROR_FS&t;&t;&t;0x0002&t;/* Errors detected */
multiline_comment|/*&n; * Mount flags&n; */
DECL|macro|EXT2_MOUNT_CHECK
mdefine_line|#define EXT2_MOUNT_CHECK&t;&t;0x0001&t;/* Do mount-time checks */
DECL|macro|EXT2_MOUNT_GRPID
mdefine_line|#define EXT2_MOUNT_GRPID&t;&t;0x0004&t;/* Create files with directory&squot;s group */
DECL|macro|EXT2_MOUNT_DEBUG
mdefine_line|#define EXT2_MOUNT_DEBUG&t;&t;0x0008&t;/* Some debugging messages */
DECL|macro|EXT2_MOUNT_ERRORS_CONT
mdefine_line|#define EXT2_MOUNT_ERRORS_CONT&t;&t;0x0010&t;/* Continue on errors */
DECL|macro|EXT2_MOUNT_ERRORS_RO
mdefine_line|#define EXT2_MOUNT_ERRORS_RO&t;&t;0x0020&t;/* Remount fs ro on errors */
DECL|macro|EXT2_MOUNT_ERRORS_PANIC
mdefine_line|#define EXT2_MOUNT_ERRORS_PANIC&t;&t;0x0040&t;/* Panic on errors */
DECL|macro|EXT2_MOUNT_MINIX_DF
mdefine_line|#define EXT2_MOUNT_MINIX_DF&t;&t;0x0080&t;/* Mimics the Minix statfs */
DECL|macro|EXT2_MOUNT_NO_UID32
mdefine_line|#define EXT2_MOUNT_NO_UID32&t;&t;0x0200  /* Disable 32-bit UIDs */
DECL|macro|clear_opt
mdefine_line|#define clear_opt(o, opt)&t;&t;o &amp;= ~EXT2_MOUNT_##opt
DECL|macro|set_opt
mdefine_line|#define set_opt(o, opt)&t;&t;&t;o |= EXT2_MOUNT_##opt
DECL|macro|test_opt
mdefine_line|#define test_opt(sb, opt)&t;&t;((sb)-&gt;u.ext2_sb.s_mount_opt &amp; &bslash;&n;&t;&t;&t;&t;&t; EXT2_MOUNT_##opt)
multiline_comment|/*&n; * Maximal mount counts between two filesystem checks&n; */
DECL|macro|EXT2_DFL_MAX_MNT_COUNT
mdefine_line|#define EXT2_DFL_MAX_MNT_COUNT&t;&t;20&t;/* Allow 20 mounts */
DECL|macro|EXT2_DFL_CHECKINTERVAL
mdefine_line|#define EXT2_DFL_CHECKINTERVAL&t;&t;0&t;/* Don&squot;t use interval check */
multiline_comment|/*&n; * Behaviour when detecting errors&n; */
DECL|macro|EXT2_ERRORS_CONTINUE
mdefine_line|#define EXT2_ERRORS_CONTINUE&t;&t;1&t;/* Continue execution */
DECL|macro|EXT2_ERRORS_RO
mdefine_line|#define EXT2_ERRORS_RO&t;&t;&t;2&t;/* Remount fs read-only */
DECL|macro|EXT2_ERRORS_PANIC
mdefine_line|#define EXT2_ERRORS_PANIC&t;&t;3&t;/* Panic */
DECL|macro|EXT2_ERRORS_DEFAULT
mdefine_line|#define EXT2_ERRORS_DEFAULT&t;&t;EXT2_ERRORS_CONTINUE
multiline_comment|/*&n; * Structure of the super block&n; */
DECL|struct|ext2_super_block
r_struct
id|ext2_super_block
(brace
DECL|member|s_inodes_count
id|__u32
id|s_inodes_count
suffix:semicolon
multiline_comment|/* Inodes count */
DECL|member|s_blocks_count
id|__u32
id|s_blocks_count
suffix:semicolon
multiline_comment|/* Blocks count */
DECL|member|s_r_blocks_count
id|__u32
id|s_r_blocks_count
suffix:semicolon
multiline_comment|/* Reserved blocks count */
DECL|member|s_free_blocks_count
id|__u32
id|s_free_blocks_count
suffix:semicolon
multiline_comment|/* Free blocks count */
DECL|member|s_free_inodes_count
id|__u32
id|s_free_inodes_count
suffix:semicolon
multiline_comment|/* Free inodes count */
DECL|member|s_first_data_block
id|__u32
id|s_first_data_block
suffix:semicolon
multiline_comment|/* First Data Block */
DECL|member|s_log_block_size
id|__u32
id|s_log_block_size
suffix:semicolon
multiline_comment|/* Block size */
DECL|member|s_log_frag_size
id|__s32
id|s_log_frag_size
suffix:semicolon
multiline_comment|/* Fragment size */
DECL|member|s_blocks_per_group
id|__u32
id|s_blocks_per_group
suffix:semicolon
multiline_comment|/* # Blocks per group */
DECL|member|s_frags_per_group
id|__u32
id|s_frags_per_group
suffix:semicolon
multiline_comment|/* # Fragments per group */
DECL|member|s_inodes_per_group
id|__u32
id|s_inodes_per_group
suffix:semicolon
multiline_comment|/* # Inodes per group */
DECL|member|s_mtime
id|__u32
id|s_mtime
suffix:semicolon
multiline_comment|/* Mount time */
DECL|member|s_wtime
id|__u32
id|s_wtime
suffix:semicolon
multiline_comment|/* Write time */
DECL|member|s_mnt_count
id|__u16
id|s_mnt_count
suffix:semicolon
multiline_comment|/* Mount count */
DECL|member|s_max_mnt_count
id|__s16
id|s_max_mnt_count
suffix:semicolon
multiline_comment|/* Maximal mount count */
DECL|member|s_magic
id|__u16
id|s_magic
suffix:semicolon
multiline_comment|/* Magic signature */
DECL|member|s_state
id|__u16
id|s_state
suffix:semicolon
multiline_comment|/* File system state */
DECL|member|s_errors
id|__u16
id|s_errors
suffix:semicolon
multiline_comment|/* Behaviour when detecting errors */
DECL|member|s_minor_rev_level
id|__u16
id|s_minor_rev_level
suffix:semicolon
multiline_comment|/* minor revision level */
DECL|member|s_lastcheck
id|__u32
id|s_lastcheck
suffix:semicolon
multiline_comment|/* time of last check */
DECL|member|s_checkinterval
id|__u32
id|s_checkinterval
suffix:semicolon
multiline_comment|/* max. time between checks */
DECL|member|s_creator_os
id|__u32
id|s_creator_os
suffix:semicolon
multiline_comment|/* OS */
DECL|member|s_rev_level
id|__u32
id|s_rev_level
suffix:semicolon
multiline_comment|/* Revision level */
DECL|member|s_def_resuid
id|__u16
id|s_def_resuid
suffix:semicolon
multiline_comment|/* Default uid for reserved blocks */
DECL|member|s_def_resgid
id|__u16
id|s_def_resgid
suffix:semicolon
multiline_comment|/* Default gid for reserved blocks */
multiline_comment|/*&n;&t; * These fields are for EXT2_DYNAMIC_REV superblocks only.&n;&t; *&n;&t; * Note: the difference between the compatible feature set and&n;&t; * the incompatible feature set is that if there is a bit set&n;&t; * in the incompatible feature set that the kernel doesn&squot;t&n;&t; * know about, it should refuse to mount the filesystem.&n;&t; * &n;&t; * e2fsck&squot;s requirements are more strict; if it doesn&squot;t know&n;&t; * about a feature in either the compatible or incompatible&n;&t; * feature set, it must abort and not try to meddle with&n;&t; * things it doesn&squot;t understand...&n;&t; */
DECL|member|s_first_ino
id|__u32
id|s_first_ino
suffix:semicolon
multiline_comment|/* First non-reserved inode */
DECL|member|s_inode_size
id|__u16
id|s_inode_size
suffix:semicolon
multiline_comment|/* size of inode structure */
DECL|member|s_block_group_nr
id|__u16
id|s_block_group_nr
suffix:semicolon
multiline_comment|/* block group # of this superblock */
DECL|member|s_feature_compat
id|__u32
id|s_feature_compat
suffix:semicolon
multiline_comment|/* compatible feature set */
DECL|member|s_feature_incompat
id|__u32
id|s_feature_incompat
suffix:semicolon
multiline_comment|/* incompatible feature set */
DECL|member|s_feature_ro_compat
id|__u32
id|s_feature_ro_compat
suffix:semicolon
multiline_comment|/* readonly-compatible feature set */
DECL|member|s_uuid
id|__u8
id|s_uuid
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* 128-bit uuid for volume */
DECL|member|s_volume_name
r_char
id|s_volume_name
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* volume name */
DECL|member|s_last_mounted
r_char
id|s_last_mounted
(braket
l_int|64
)braket
suffix:semicolon
multiline_comment|/* directory where last mounted */
DECL|member|s_algorithm_usage_bitmap
id|__u32
id|s_algorithm_usage_bitmap
suffix:semicolon
multiline_comment|/* For compression */
multiline_comment|/*&n;&t; * Performance hints.  Directory preallocation should only&n;&t; * happen if the EXT2_COMPAT_PREALLOC flag is on.&n;&t; */
DECL|member|s_prealloc_blocks
id|__u8
id|s_prealloc_blocks
suffix:semicolon
multiline_comment|/* Nr of blocks to try to preallocate*/
DECL|member|s_prealloc_dir_blocks
id|__u8
id|s_prealloc_dir_blocks
suffix:semicolon
multiline_comment|/* Nr to preallocate for dirs */
DECL|member|s_padding1
id|__u16
id|s_padding1
suffix:semicolon
DECL|member|s_reserved
id|__u32
id|s_reserved
(braket
l_int|204
)braket
suffix:semicolon
multiline_comment|/* Padding to the end of the block */
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
DECL|macro|EXT2_SB
mdefine_line|#define EXT2_SB(sb)&t;(&amp;((sb)-&gt;u.ext2_sb))
macro_line|#else
multiline_comment|/* Assume that user mode programs are passing in an ext2fs superblock, not&n; * a kernel struct super_block.  This will allow us to call the feature-test&n; * macros from user land. */
DECL|macro|EXT2_SB
mdefine_line|#define EXT2_SB(sb)&t;(sb)
macro_line|#endif
multiline_comment|/*&n; * Codes for operating systems&n; */
DECL|macro|EXT2_OS_LINUX
mdefine_line|#define EXT2_OS_LINUX&t;&t;0
DECL|macro|EXT2_OS_HURD
mdefine_line|#define EXT2_OS_HURD&t;&t;1
DECL|macro|EXT2_OS_MASIX
mdefine_line|#define EXT2_OS_MASIX&t;&t;2
DECL|macro|EXT2_OS_FREEBSD
mdefine_line|#define EXT2_OS_FREEBSD&t;&t;3
DECL|macro|EXT2_OS_LITES
mdefine_line|#define EXT2_OS_LITES&t;&t;4
multiline_comment|/*&n; * Revision levels&n; */
DECL|macro|EXT2_GOOD_OLD_REV
mdefine_line|#define EXT2_GOOD_OLD_REV&t;0&t;/* The good old (original) format */
DECL|macro|EXT2_DYNAMIC_REV
mdefine_line|#define EXT2_DYNAMIC_REV&t;1 &t;/* V2 format w/ dynamic inode sizes */
DECL|macro|EXT2_CURRENT_REV
mdefine_line|#define EXT2_CURRENT_REV&t;EXT2_GOOD_OLD_REV
DECL|macro|EXT2_MAX_SUPP_REV
mdefine_line|#define EXT2_MAX_SUPP_REV&t;EXT2_DYNAMIC_REV
DECL|macro|EXT2_GOOD_OLD_INODE_SIZE
mdefine_line|#define EXT2_GOOD_OLD_INODE_SIZE 128
multiline_comment|/*&n; * Feature set definitions&n; */
DECL|macro|EXT2_HAS_COMPAT_FEATURE
mdefine_line|#define EXT2_HAS_COMPAT_FEATURE(sb,mask)&t;&t;&t;&bslash;&n;&t;( EXT2_SB(sb)-&gt;s_es-&gt;s_feature_compat &amp; cpu_to_le32(mask) )
DECL|macro|EXT2_HAS_RO_COMPAT_FEATURE
mdefine_line|#define EXT2_HAS_RO_COMPAT_FEATURE(sb,mask)&t;&t;&t;&bslash;&n;&t;( EXT2_SB(sb)-&gt;s_es-&gt;s_feature_ro_compat &amp; cpu_to_le32(mask) )
DECL|macro|EXT2_HAS_INCOMPAT_FEATURE
mdefine_line|#define EXT2_HAS_INCOMPAT_FEATURE(sb,mask)&t;&t;&t;&bslash;&n;&t;( EXT2_SB(sb)-&gt;s_es-&gt;s_feature_incompat &amp; cpu_to_le32(mask) )
DECL|macro|EXT2_SET_COMPAT_FEATURE
mdefine_line|#define EXT2_SET_COMPAT_FEATURE(sb,mask)&t;&t;&t;&bslash;&n;&t;EXT2_SB(sb)-&gt;s_es-&gt;s_feature_compat |= cpu_to_le32(mask)
DECL|macro|EXT2_SET_RO_COMPAT_FEATURE
mdefine_line|#define EXT2_SET_RO_COMPAT_FEATURE(sb,mask)&t;&t;&t;&bslash;&n;&t;EXT2_SB(sb)-&gt;s_es-&gt;s_feature_ro_compat |= cpu_to_le32(mask)
DECL|macro|EXT2_SET_INCOMPAT_FEATURE
mdefine_line|#define EXT2_SET_INCOMPAT_FEATURE(sb,mask)&t;&t;&t;&bslash;&n;&t;EXT2_SB(sb)-&gt;s_es-&gt;s_feature_incompat |= cpu_to_le32(mask)
DECL|macro|EXT2_CLEAR_COMPAT_FEATURE
mdefine_line|#define EXT2_CLEAR_COMPAT_FEATURE(sb,mask)&t;&t;&t;&bslash;&n;&t;EXT2_SB(sb)-&gt;s_es-&gt;s_feature_compat &amp;= ~cpu_to_le32(mask)
DECL|macro|EXT2_CLEAR_RO_COMPAT_FEATURE
mdefine_line|#define EXT2_CLEAR_RO_COMPAT_FEATURE(sb,mask)&t;&t;&t;&bslash;&n;&t;EXT2_SB(sb)-&gt;s_es-&gt;s_feature_ro_compat &amp;= ~cpu_to_le32(mask)
DECL|macro|EXT2_CLEAR_INCOMPAT_FEATURE
mdefine_line|#define EXT2_CLEAR_INCOMPAT_FEATURE(sb,mask)&t;&t;&t;&bslash;&n;&t;EXT2_SB(sb)-&gt;s_es-&gt;s_feature_incompat &amp;= ~cpu_to_le32(mask)
DECL|macro|EXT2_FEATURE_COMPAT_DIR_PREALLOC
mdefine_line|#define EXT2_FEATURE_COMPAT_DIR_PREALLOC&t;0x0001
DECL|macro|EXT2_FEATURE_COMPAT_IMAGIC_INODES
mdefine_line|#define EXT2_FEATURE_COMPAT_IMAGIC_INODES&t;0x0002
DECL|macro|EXT3_FEATURE_COMPAT_HAS_JOURNAL
mdefine_line|#define EXT3_FEATURE_COMPAT_HAS_JOURNAL&t;&t;0x0004
DECL|macro|EXT2_FEATURE_COMPAT_EXT_ATTR
mdefine_line|#define EXT2_FEATURE_COMPAT_EXT_ATTR&t;&t;0x0008
DECL|macro|EXT2_FEATURE_COMPAT_RESIZE_INO
mdefine_line|#define EXT2_FEATURE_COMPAT_RESIZE_INO&t;&t;0x0010
DECL|macro|EXT2_FEATURE_COMPAT_DIR_INDEX
mdefine_line|#define EXT2_FEATURE_COMPAT_DIR_INDEX&t;&t;0x0020
DECL|macro|EXT2_FEATURE_COMPAT_ANY
mdefine_line|#define EXT2_FEATURE_COMPAT_ANY&t;&t;&t;0xffffffff
DECL|macro|EXT2_FEATURE_RO_COMPAT_SPARSE_SUPER
mdefine_line|#define EXT2_FEATURE_RO_COMPAT_SPARSE_SUPER&t;0x0001
DECL|macro|EXT2_FEATURE_RO_COMPAT_LARGE_FILE
mdefine_line|#define EXT2_FEATURE_RO_COMPAT_LARGE_FILE&t;0x0002
DECL|macro|EXT2_FEATURE_RO_COMPAT_BTREE_DIR
mdefine_line|#define EXT2_FEATURE_RO_COMPAT_BTREE_DIR&t;0x0004
DECL|macro|EXT2_FEATURE_RO_COMPAT_ANY
mdefine_line|#define EXT2_FEATURE_RO_COMPAT_ANY&t;&t;0xffffffff
DECL|macro|EXT2_FEATURE_INCOMPAT_COMPRESSION
mdefine_line|#define EXT2_FEATURE_INCOMPAT_COMPRESSION&t;0x0001
DECL|macro|EXT2_FEATURE_INCOMPAT_FILETYPE
mdefine_line|#define EXT2_FEATURE_INCOMPAT_FILETYPE&t;&t;0x0002
DECL|macro|EXT3_FEATURE_INCOMPAT_RECOVER
mdefine_line|#define EXT3_FEATURE_INCOMPAT_RECOVER&t;&t;0x0004
DECL|macro|EXT3_FEATURE_INCOMPAT_JOURNAL_DEV
mdefine_line|#define EXT3_FEATURE_INCOMPAT_JOURNAL_DEV&t;0x0008
DECL|macro|EXT2_FEATURE_INCOMPAT_ANY
mdefine_line|#define EXT2_FEATURE_INCOMPAT_ANY&t;&t;0xffffffff
DECL|macro|EXT2_FEATURE_COMPAT_SUPP
mdefine_line|#define EXT2_FEATURE_COMPAT_SUPP&t;0
DECL|macro|EXT2_FEATURE_INCOMPAT_SUPP
mdefine_line|#define EXT2_FEATURE_INCOMPAT_SUPP&t;EXT2_FEATURE_INCOMPAT_FILETYPE
DECL|macro|EXT2_FEATURE_RO_COMPAT_SUPP
mdefine_line|#define EXT2_FEATURE_RO_COMPAT_SUPP&t;(EXT2_FEATURE_RO_COMPAT_SPARSE_SUPER| &bslash;&n;&t;&t;&t;&t;&t; EXT2_FEATURE_RO_COMPAT_LARGE_FILE| &bslash;&n;&t;&t;&t;&t;&t; EXT2_FEATURE_RO_COMPAT_BTREE_DIR)
DECL|macro|EXT2_FEATURE_RO_COMPAT_UNSUPPORTED
mdefine_line|#define EXT2_FEATURE_RO_COMPAT_UNSUPPORTED&t;~EXT2_FEATURE_RO_COMPAT_SUPP
DECL|macro|EXT2_FEATURE_INCOMPAT_UNSUPPORTED
mdefine_line|#define EXT2_FEATURE_INCOMPAT_UNSUPPORTED&t;~EXT2_FEATURE_INCOMPAT_SUPP
multiline_comment|/*&n; * Default values for user and/or group using reserved blocks&n; */
DECL|macro|EXT2_DEF_RESUID
mdefine_line|#define&t;EXT2_DEF_RESUID&t;&t;0
DECL|macro|EXT2_DEF_RESGID
mdefine_line|#define&t;EXT2_DEF_RESGID&t;&t;0
multiline_comment|/*&n; * Structure of a directory entry&n; */
DECL|macro|EXT2_NAME_LEN
mdefine_line|#define EXT2_NAME_LEN 255
DECL|struct|ext2_dir_entry
r_struct
id|ext2_dir_entry
(brace
DECL|member|inode
id|__u32
id|inode
suffix:semicolon
multiline_comment|/* Inode number */
DECL|member|rec_len
id|__u16
id|rec_len
suffix:semicolon
multiline_comment|/* Directory entry length */
DECL|member|name_len
id|__u16
id|name_len
suffix:semicolon
multiline_comment|/* Name length */
DECL|member|name
r_char
id|name
(braket
id|EXT2_NAME_LEN
)braket
suffix:semicolon
multiline_comment|/* File name */
)brace
suffix:semicolon
multiline_comment|/*&n; * The new version of the directory entry.  Since EXT2 structures are&n; * stored in intel byte order, and the name_len field could never be&n; * bigger than 255 chars, it&squot;s safe to reclaim the extra byte for the&n; * file_type field.&n; */
DECL|struct|ext2_dir_entry_2
r_struct
id|ext2_dir_entry_2
(brace
DECL|member|inode
id|__u32
id|inode
suffix:semicolon
multiline_comment|/* Inode number */
DECL|member|rec_len
id|__u16
id|rec_len
suffix:semicolon
multiline_comment|/* Directory entry length */
DECL|member|name_len
id|__u8
id|name_len
suffix:semicolon
multiline_comment|/* Name length */
DECL|member|file_type
id|__u8
id|file_type
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
id|EXT2_NAME_LEN
)braket
suffix:semicolon
multiline_comment|/* File name */
)brace
suffix:semicolon
multiline_comment|/*&n; * Ext2 directory file types.  Only the low 3 bits are used.  The&n; * other bits are reserved for now.&n; */
r_enum
(brace
DECL|enumerator|EXT2_FT_UNKNOWN
id|EXT2_FT_UNKNOWN
comma
DECL|enumerator|EXT2_FT_REG_FILE
id|EXT2_FT_REG_FILE
comma
DECL|enumerator|EXT2_FT_DIR
id|EXT2_FT_DIR
comma
DECL|enumerator|EXT2_FT_CHRDEV
id|EXT2_FT_CHRDEV
comma
DECL|enumerator|EXT2_FT_BLKDEV
id|EXT2_FT_BLKDEV
comma
DECL|enumerator|EXT2_FT_FIFO
id|EXT2_FT_FIFO
comma
DECL|enumerator|EXT2_FT_SOCK
id|EXT2_FT_SOCK
comma
DECL|enumerator|EXT2_FT_SYMLINK
id|EXT2_FT_SYMLINK
comma
DECL|enumerator|EXT2_FT_MAX
id|EXT2_FT_MAX
)brace
suffix:semicolon
multiline_comment|/*&n; * EXT2_DIR_PAD defines the directory entries boundaries&n; *&n; * NOTE: It must be a multiple of 4&n; */
DECL|macro|EXT2_DIR_PAD
mdefine_line|#define EXT2_DIR_PAD&t;&t; &t;4
DECL|macro|EXT2_DIR_ROUND
mdefine_line|#define EXT2_DIR_ROUND &t;&t;&t;(EXT2_DIR_PAD - 1)
DECL|macro|EXT2_DIR_REC_LEN
mdefine_line|#define EXT2_DIR_REC_LEN(name_len)&t;(((name_len) + 8 + EXT2_DIR_ROUND) &amp; &bslash;&n;&t;&t;&t;&t;&t; ~EXT2_DIR_ROUND)
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * Function prototypes&n; */
multiline_comment|/*&n; * Ok, these declarations are also in &lt;linux/kernel.h&gt; but none of the&n; * ext2 source programs needs to include it so they are duplicated here.&n; */
DECL|macro|NORET_TYPE
macro_line|# define NORET_TYPE    /**/
DECL|macro|ATTRIB_NORET
macro_line|# define ATTRIB_NORET  __attribute__((noreturn))
DECL|macro|NORET_AND
macro_line|# define NORET_AND     noreturn,
multiline_comment|/* balloc.c */
r_extern
r_int
id|ext2_bg_has_super
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
id|group
)paren
suffix:semicolon
r_extern
r_int
r_int
id|ext2_bg_num_gdb
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
id|group
)paren
suffix:semicolon
r_extern
r_int
id|ext2_new_block
(paren
r_struct
id|inode
op_star
comma
r_int
r_int
comma
id|__u32
op_star
comma
id|__u32
op_star
comma
r_int
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ext2_free_blocks
(paren
r_struct
id|inode
op_star
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
r_int
id|ext2_count_free_blocks
(paren
r_struct
id|super_block
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ext2_check_blocks_bitmap
(paren
r_struct
id|super_block
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|ext2_group_desc
op_star
id|ext2_get_group_desc
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
r_int
id|block_group
comma
r_struct
id|buffer_head
op_star
op_star
id|bh
)paren
suffix:semicolon
multiline_comment|/* dir.c */
r_extern
r_int
id|ext2_add_link
(paren
r_struct
id|dentry
op_star
comma
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
id|ino_t
id|ext2_inode_by_name
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|dentry
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ext2_make_empty
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|ext2_dir_entry_2
op_star
id|ext2_find_entry
(paren
r_struct
id|inode
op_star
comma
r_struct
id|dentry
op_star
comma
r_struct
id|page
op_star
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ext2_delete_entry
(paren
r_struct
id|ext2_dir_entry_2
op_star
comma
r_struct
id|page
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ext2_empty_dir
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|ext2_dir_entry_2
op_star
id|ext2_dotdot
(paren
r_struct
id|inode
op_star
comma
r_struct
id|page
op_star
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ext2_set_link
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|ext2_dir_entry_2
op_star
comma
r_struct
id|page
op_star
comma
r_struct
id|inode
op_star
)paren
suffix:semicolon
multiline_comment|/* fsync.c */
r_extern
r_int
id|ext2_sync_file
(paren
r_struct
id|file
op_star
comma
r_struct
id|dentry
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|ext2_fsync_inode
(paren
r_struct
id|inode
op_star
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* ialloc.c */
r_extern
r_struct
id|inode
op_star
id|ext2_new_inode
(paren
r_const
r_struct
id|inode
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|ext2_free_inode
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_int
r_int
id|ext2_count_free_inodes
(paren
r_struct
id|super_block
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ext2_check_inodes_bitmap
(paren
r_struct
id|super_block
op_star
)paren
suffix:semicolon
r_extern
r_int
r_int
id|ext2_count_free
(paren
r_struct
id|buffer_head
op_star
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* inode.c */
r_extern
r_void
id|ext2_read_inode
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ext2_write_inode
(paren
r_struct
id|inode
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|ext2_put_inode
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ext2_delete_inode
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ext2_sync_inode
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ext2_discard_prealloc
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ext2_truncate
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
multiline_comment|/* ioctl.c */
r_extern
r_int
id|ext2_ioctl
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/* super.c */
r_extern
r_void
id|ext2_error
(paren
r_struct
id|super_block
op_star
comma
r_const
r_char
op_star
comma
r_const
r_char
op_star
comma
dot
dot
dot
)paren
id|__attribute__
(paren
(paren
id|format
(paren
id|printf
comma
l_int|3
comma
l_int|4
)paren
)paren
)paren
suffix:semicolon
r_extern
id|NORET_TYPE
r_void
id|ext2_panic
(paren
r_struct
id|super_block
op_star
comma
r_const
r_char
op_star
comma
r_const
r_char
op_star
comma
dot
dot
dot
)paren
id|__attribute__
(paren
(paren
id|NORET_AND
id|format
(paren
id|printf
comma
l_int|3
comma
l_int|4
)paren
)paren
)paren
suffix:semicolon
r_extern
r_void
id|ext2_warning
(paren
r_struct
id|super_block
op_star
comma
r_const
r_char
op_star
comma
r_const
r_char
op_star
comma
dot
dot
dot
)paren
id|__attribute__
(paren
(paren
id|format
(paren
id|printf
comma
l_int|3
comma
l_int|4
)paren
)paren
)paren
suffix:semicolon
r_extern
r_void
id|ext2_update_dynamic_rev
(paren
r_struct
id|super_block
op_star
id|sb
)paren
suffix:semicolon
r_extern
r_void
id|ext2_put_super
(paren
r_struct
id|super_block
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ext2_write_super
(paren
r_struct
id|super_block
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ext2_remount
(paren
r_struct
id|super_block
op_star
comma
r_int
op_star
comma
r_char
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|super_block
op_star
id|ext2_read_super
(paren
r_struct
id|super_block
op_star
comma
r_void
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|ext2_statfs
(paren
r_struct
id|super_block
op_star
comma
r_struct
id|statfs
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * Inodes and files operations&n; */
multiline_comment|/* dir.c */
r_extern
r_struct
id|file_operations
id|ext2_dir_operations
suffix:semicolon
multiline_comment|/* file.c */
r_extern
r_struct
id|inode_operations
id|ext2_file_inode_operations
suffix:semicolon
r_extern
r_struct
id|file_operations
id|ext2_file_operations
suffix:semicolon
multiline_comment|/* inode.c */
r_extern
r_struct
id|address_space_operations
id|ext2_aops
suffix:semicolon
multiline_comment|/* namei.c */
r_extern
r_struct
id|inode_operations
id|ext2_dir_inode_operations
suffix:semicolon
multiline_comment|/* symlink.c */
r_extern
r_struct
id|inode_operations
id|ext2_fast_symlink_inode_operations
suffix:semicolon
macro_line|#endif&t;/* __KERNEL__ */
macro_line|#endif&t;/* _LINUX_EXT2_FS_H */
eof
