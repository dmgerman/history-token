multiline_comment|/*&n; *  linux/include/linux/ext3_fs.h&n; *&n; * Copyright (C) 1992, 1993, 1994, 1995&n; * Remy Card (card@masi.ibp.fr)&n; * Laboratoire MASI - Institut Blaise Pascal&n; * Universite Pierre et Marie Curie (Paris VI)&n; *&n; *  from&n; *&n; *  linux/include/linux/minix_fs.h&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; */
macro_line|#ifndef _LINUX_EXT3_FS_H
DECL|macro|_LINUX_EXT3_FS_H
mdefine_line|#define _LINUX_EXT3_FS_H
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/ext3_fs_i.h&gt;
macro_line|#include &lt;linux/ext3_fs_sb.h&gt;
r_struct
id|statfs
suffix:semicolon
multiline_comment|/*&n; * The second extended filesystem constants/structures&n; */
multiline_comment|/*&n; * Define EXT3FS_DEBUG to produce debug messages&n; */
DECL|macro|EXT3FS_DEBUG
macro_line|#undef EXT3FS_DEBUG
multiline_comment|/*&n; * Define EXT3_RESERVATION to reserve data blocks for expanding files&n; */
DECL|macro|EXT3_DEFAULT_RESERVE_BLOCKS
mdefine_line|#define EXT3_DEFAULT_RESERVE_BLOCKS     8
DECL|macro|EXT3_MAX_RESERVE_BLOCKS
mdefine_line|#define EXT3_MAX_RESERVE_BLOCKS         1024
DECL|macro|EXT3_RESERVE_WINDOW_NOT_ALLOCATED
mdefine_line|#define EXT3_RESERVE_WINDOW_NOT_ALLOCATED 0
multiline_comment|/*&n; * Always enable hashed directories&n; */
DECL|macro|CONFIG_EXT3_INDEX
mdefine_line|#define CONFIG_EXT3_INDEX
multiline_comment|/*&n; * Debug code&n; */
macro_line|#ifdef EXT3FS_DEBUG
DECL|macro|ext3_debug
mdefine_line|#define ext3_debug(f, a...)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;printk (KERN_DEBUG &quot;EXT3-fs DEBUG (%s, %d): %s:&quot;,&t;&bslash;&n;&t;&t;&t;__FILE__, __LINE__, __FUNCTION__);&t;&t;&bslash;&n;&t;&t;printk (KERN_DEBUG f, ## a);&t;&t;&t;&t;&bslash;&n;&t;} while (0)
macro_line|#else
DECL|macro|ext3_debug
mdefine_line|#define ext3_debug(f, a...)&t;do {} while (0)
macro_line|#endif
multiline_comment|/*&n; * Special inodes numbers&n; */
DECL|macro|EXT3_BAD_INO
mdefine_line|#define&t;EXT3_BAD_INO&t;&t; 1&t;/* Bad blocks inode */
DECL|macro|EXT3_ROOT_INO
mdefine_line|#define EXT3_ROOT_INO&t;&t; 2&t;/* Root inode */
DECL|macro|EXT3_BOOT_LOADER_INO
mdefine_line|#define EXT3_BOOT_LOADER_INO&t; 5&t;/* Boot loader inode */
DECL|macro|EXT3_UNDEL_DIR_INO
mdefine_line|#define EXT3_UNDEL_DIR_INO&t; 6&t;/* Undelete directory inode */
DECL|macro|EXT3_RESIZE_INO
mdefine_line|#define EXT3_RESIZE_INO&t;&t; 7&t;/* Reserved group descriptors inode */
DECL|macro|EXT3_JOURNAL_INO
mdefine_line|#define EXT3_JOURNAL_INO&t; 8&t;/* Journal inode */
multiline_comment|/* First non-reserved inode for old ext3 filesystems */
DECL|macro|EXT3_GOOD_OLD_FIRST_INO
mdefine_line|#define EXT3_GOOD_OLD_FIRST_INO&t;11
multiline_comment|/*&n; * The second extended file system magic number&n; */
DECL|macro|EXT3_SUPER_MAGIC
mdefine_line|#define EXT3_SUPER_MAGIC&t;0xEF53
multiline_comment|/*&n; * Maximal count of links to a file&n; */
DECL|macro|EXT3_LINK_MAX
mdefine_line|#define EXT3_LINK_MAX&t;&t;32000
multiline_comment|/*&n; * Macro-instructions used to manage several block sizes&n; */
DECL|macro|EXT3_MIN_BLOCK_SIZE
mdefine_line|#define EXT3_MIN_BLOCK_SIZE&t;&t;1024
DECL|macro|EXT3_MAX_BLOCK_SIZE
mdefine_line|#define&t;EXT3_MAX_BLOCK_SIZE&t;&t;4096
DECL|macro|EXT3_MIN_BLOCK_LOG_SIZE
mdefine_line|#define EXT3_MIN_BLOCK_LOG_SIZE&t;&t;  10
macro_line|#ifdef __KERNEL__
DECL|macro|EXT3_BLOCK_SIZE
macro_line|# define EXT3_BLOCK_SIZE(s)&t;&t;((s)-&gt;s_blocksize)
macro_line|#else
DECL|macro|EXT3_BLOCK_SIZE
macro_line|# define EXT3_BLOCK_SIZE(s)&t;&t;(EXT3_MIN_BLOCK_SIZE &lt;&lt; (s)-&gt;s_log_block_size)
macro_line|#endif
DECL|macro|EXT3_ADDR_PER_BLOCK
mdefine_line|#define&t;EXT3_ADDR_PER_BLOCK(s)&t;&t;(EXT3_BLOCK_SIZE(s) / sizeof (__u32))
macro_line|#ifdef __KERNEL__
DECL|macro|EXT3_BLOCK_SIZE_BITS
macro_line|# define EXT3_BLOCK_SIZE_BITS(s)&t;((s)-&gt;s_blocksize_bits)
macro_line|#else
DECL|macro|EXT3_BLOCK_SIZE_BITS
macro_line|# define EXT3_BLOCK_SIZE_BITS(s)&t;((s)-&gt;s_log_block_size + 10)
macro_line|#endif
macro_line|#ifdef __KERNEL__
DECL|macro|EXT3_ADDR_PER_BLOCK_BITS
mdefine_line|#define&t;EXT3_ADDR_PER_BLOCK_BITS(s)&t;(EXT3_SB(s)-&gt;s_addr_per_block_bits)
DECL|macro|EXT3_INODE_SIZE
mdefine_line|#define EXT3_INODE_SIZE(s)&t;&t;(EXT3_SB(s)-&gt;s_inode_size)
DECL|macro|EXT3_FIRST_INO
mdefine_line|#define EXT3_FIRST_INO(s)&t;&t;(EXT3_SB(s)-&gt;s_first_ino)
macro_line|#else
DECL|macro|EXT3_INODE_SIZE
mdefine_line|#define EXT3_INODE_SIZE(s)&t;(((s)-&gt;s_rev_level == EXT3_GOOD_OLD_REV) ? &bslash;&n;&t;&t;&t;&t; EXT3_GOOD_OLD_INODE_SIZE : &bslash;&n;&t;&t;&t;&t; (s)-&gt;s_inode_size)
DECL|macro|EXT3_FIRST_INO
mdefine_line|#define EXT3_FIRST_INO(s)&t;(((s)-&gt;s_rev_level == EXT3_GOOD_OLD_REV) ? &bslash;&n;&t;&t;&t;&t; EXT3_GOOD_OLD_FIRST_INO : &bslash;&n;&t;&t;&t;&t; (s)-&gt;s_first_ino)
macro_line|#endif
multiline_comment|/*&n; * Macro-instructions used to manage fragments&n; */
DECL|macro|EXT3_MIN_FRAG_SIZE
mdefine_line|#define EXT3_MIN_FRAG_SIZE&t;&t;1024
DECL|macro|EXT3_MAX_FRAG_SIZE
mdefine_line|#define&t;EXT3_MAX_FRAG_SIZE&t;&t;4096
DECL|macro|EXT3_MIN_FRAG_LOG_SIZE
mdefine_line|#define EXT3_MIN_FRAG_LOG_SIZE&t;&t;  10
macro_line|#ifdef __KERNEL__
DECL|macro|EXT3_FRAG_SIZE
macro_line|# define EXT3_FRAG_SIZE(s)&t;&t;(EXT3_SB(s)-&gt;s_frag_size)
DECL|macro|EXT3_FRAGS_PER_BLOCK
macro_line|# define EXT3_FRAGS_PER_BLOCK(s)&t;(EXT3_SB(s)-&gt;s_frags_per_block)
macro_line|#else
DECL|macro|EXT3_FRAG_SIZE
macro_line|# define EXT3_FRAG_SIZE(s)&t;&t;(EXT3_MIN_FRAG_SIZE &lt;&lt; (s)-&gt;s_log_frag_size)
DECL|macro|EXT3_FRAGS_PER_BLOCK
macro_line|# define EXT3_FRAGS_PER_BLOCK(s)&t;(EXT3_BLOCK_SIZE(s) / EXT3_FRAG_SIZE(s))
macro_line|#endif
multiline_comment|/*&n; * Structure of a blocks group descriptor&n; */
DECL|struct|ext3_group_desc
r_struct
id|ext3_group_desc
(brace
DECL|member|bg_block_bitmap
id|__le32
id|bg_block_bitmap
suffix:semicolon
multiline_comment|/* Blocks bitmap block */
DECL|member|bg_inode_bitmap
id|__le32
id|bg_inode_bitmap
suffix:semicolon
multiline_comment|/* Inodes bitmap block */
DECL|member|bg_inode_table
id|__le32
id|bg_inode_table
suffix:semicolon
multiline_comment|/* Inodes table block */
DECL|member|bg_free_blocks_count
id|__le16
id|bg_free_blocks_count
suffix:semicolon
multiline_comment|/* Free blocks count */
DECL|member|bg_free_inodes_count
id|__le16
id|bg_free_inodes_count
suffix:semicolon
multiline_comment|/* Free inodes count */
DECL|member|bg_used_dirs_count
id|__le16
id|bg_used_dirs_count
suffix:semicolon
multiline_comment|/* Directories count */
DECL|member|bg_pad
id|__u16
id|bg_pad
suffix:semicolon
DECL|member|bg_reserved
id|__le32
id|bg_reserved
(braket
l_int|3
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Macro-instructions used to manage group descriptors&n; */
macro_line|#ifdef __KERNEL__
DECL|macro|EXT3_BLOCKS_PER_GROUP
macro_line|# define EXT3_BLOCKS_PER_GROUP(s)&t;(EXT3_SB(s)-&gt;s_blocks_per_group)
DECL|macro|EXT3_DESC_PER_BLOCK
macro_line|# define EXT3_DESC_PER_BLOCK(s)&t;&t;(EXT3_SB(s)-&gt;s_desc_per_block)
DECL|macro|EXT3_INODES_PER_GROUP
macro_line|# define EXT3_INODES_PER_GROUP(s)&t;(EXT3_SB(s)-&gt;s_inodes_per_group)
DECL|macro|EXT3_DESC_PER_BLOCK_BITS
macro_line|# define EXT3_DESC_PER_BLOCK_BITS(s)&t;(EXT3_SB(s)-&gt;s_desc_per_block_bits)
macro_line|#else
DECL|macro|EXT3_BLOCKS_PER_GROUP
macro_line|# define EXT3_BLOCKS_PER_GROUP(s)&t;((s)-&gt;s_blocks_per_group)
DECL|macro|EXT3_DESC_PER_BLOCK
macro_line|# define EXT3_DESC_PER_BLOCK(s)&t;&t;(EXT3_BLOCK_SIZE(s) / sizeof (struct ext3_group_desc))
DECL|macro|EXT3_INODES_PER_GROUP
macro_line|# define EXT3_INODES_PER_GROUP(s)&t;((s)-&gt;s_inodes_per_group)
macro_line|#endif
multiline_comment|/*&n; * Constants relative to the data blocks&n; */
DECL|macro|EXT3_NDIR_BLOCKS
mdefine_line|#define&t;EXT3_NDIR_BLOCKS&t;&t;12
DECL|macro|EXT3_IND_BLOCK
mdefine_line|#define&t;EXT3_IND_BLOCK&t;&t;&t;EXT3_NDIR_BLOCKS
DECL|macro|EXT3_DIND_BLOCK
mdefine_line|#define&t;EXT3_DIND_BLOCK&t;&t;&t;(EXT3_IND_BLOCK + 1)
DECL|macro|EXT3_TIND_BLOCK
mdefine_line|#define&t;EXT3_TIND_BLOCK&t;&t;&t;(EXT3_DIND_BLOCK + 1)
DECL|macro|EXT3_N_BLOCKS
mdefine_line|#define&t;EXT3_N_BLOCKS&t;&t;&t;(EXT3_TIND_BLOCK + 1)
multiline_comment|/*&n; * Inode flags&n; */
DECL|macro|EXT3_SECRM_FL
mdefine_line|#define&t;EXT3_SECRM_FL&t;&t;&t;0x00000001 /* Secure deletion */
DECL|macro|EXT3_UNRM_FL
mdefine_line|#define&t;EXT3_UNRM_FL&t;&t;&t;0x00000002 /* Undelete */
DECL|macro|EXT3_COMPR_FL
mdefine_line|#define&t;EXT3_COMPR_FL&t;&t;&t;0x00000004 /* Compress file */
DECL|macro|EXT3_SYNC_FL
mdefine_line|#define EXT3_SYNC_FL&t;&t;&t;0x00000008 /* Synchronous updates */
DECL|macro|EXT3_IMMUTABLE_FL
mdefine_line|#define EXT3_IMMUTABLE_FL&t;&t;0x00000010 /* Immutable file */
DECL|macro|EXT3_APPEND_FL
mdefine_line|#define EXT3_APPEND_FL&t;&t;&t;0x00000020 /* writes to file may only append */
DECL|macro|EXT3_NODUMP_FL
mdefine_line|#define EXT3_NODUMP_FL&t;&t;&t;0x00000040 /* do not dump file */
DECL|macro|EXT3_NOATIME_FL
mdefine_line|#define EXT3_NOATIME_FL&t;&t;&t;0x00000080 /* do not update atime */
multiline_comment|/* Reserved for compression usage... */
DECL|macro|EXT3_DIRTY_FL
mdefine_line|#define EXT3_DIRTY_FL&t;&t;&t;0x00000100
DECL|macro|EXT3_COMPRBLK_FL
mdefine_line|#define EXT3_COMPRBLK_FL&t;&t;0x00000200 /* One or more compressed clusters */
DECL|macro|EXT3_NOCOMPR_FL
mdefine_line|#define EXT3_NOCOMPR_FL&t;&t;&t;0x00000400 /* Don&squot;t compress */
DECL|macro|EXT3_ECOMPR_FL
mdefine_line|#define EXT3_ECOMPR_FL&t;&t;&t;0x00000800 /* Compression error */
multiline_comment|/* End compression flags --- maybe not all used */
DECL|macro|EXT3_INDEX_FL
mdefine_line|#define EXT3_INDEX_FL&t;&t;&t;0x00001000 /* hash-indexed directory */
DECL|macro|EXT3_IMAGIC_FL
mdefine_line|#define EXT3_IMAGIC_FL&t;&t;&t;0x00002000 /* AFS directory */
DECL|macro|EXT3_JOURNAL_DATA_FL
mdefine_line|#define EXT3_JOURNAL_DATA_FL&t;&t;0x00004000 /* file data should be journaled */
DECL|macro|EXT3_NOTAIL_FL
mdefine_line|#define EXT3_NOTAIL_FL&t;&t;&t;0x00008000 /* file tail should not be merged */
DECL|macro|EXT3_DIRSYNC_FL
mdefine_line|#define EXT3_DIRSYNC_FL&t;&t;&t;0x00010000 /* dirsync behaviour (directories only) */
DECL|macro|EXT3_TOPDIR_FL
mdefine_line|#define EXT3_TOPDIR_FL&t;&t;&t;0x00020000 /* Top of directory hierarchies*/
DECL|macro|EXT3_RESERVED_FL
mdefine_line|#define EXT3_RESERVED_FL&t;&t;0x80000000 /* reserved for ext3 lib */
DECL|macro|EXT3_FL_USER_VISIBLE
mdefine_line|#define EXT3_FL_USER_VISIBLE&t;&t;0x0003DFFF /* User visible flags */
DECL|macro|EXT3_FL_USER_MODIFIABLE
mdefine_line|#define EXT3_FL_USER_MODIFIABLE&t;&t;0x000380FF /* User modifiable flags */
multiline_comment|/*&n; * Inode dynamic state flags&n; */
DECL|macro|EXT3_STATE_JDATA
mdefine_line|#define EXT3_STATE_JDATA&t;&t;0x00000001 /* journaled data exists */
DECL|macro|EXT3_STATE_NEW
mdefine_line|#define EXT3_STATE_NEW&t;&t;&t;0x00000002 /* inode is newly created */
DECL|macro|EXT3_STATE_XATTR
mdefine_line|#define EXT3_STATE_XATTR&t;&t;0x00000004 /* has in-inode xattrs */
multiline_comment|/* Used to pass group descriptor data when online resize is done */
DECL|struct|ext3_new_group_input
r_struct
id|ext3_new_group_input
(brace
DECL|member|group
id|__u32
id|group
suffix:semicolon
multiline_comment|/* Group number for this data */
DECL|member|block_bitmap
id|__u32
id|block_bitmap
suffix:semicolon
multiline_comment|/* Absolute block number of block bitmap */
DECL|member|inode_bitmap
id|__u32
id|inode_bitmap
suffix:semicolon
multiline_comment|/* Absolute block number of inode bitmap */
DECL|member|inode_table
id|__u32
id|inode_table
suffix:semicolon
multiline_comment|/* Absolute block number of inode table start */
DECL|member|blocks_count
id|__u32
id|blocks_count
suffix:semicolon
multiline_comment|/* Total number of blocks in this group */
DECL|member|reserved_blocks
id|__u16
id|reserved_blocks
suffix:semicolon
multiline_comment|/* Number of reserved blocks in this group */
DECL|member|unused
id|__u16
id|unused
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* The struct ext3_new_group_input in kernel space, with free_blocks_count */
DECL|struct|ext3_new_group_data
r_struct
id|ext3_new_group_data
(brace
DECL|member|group
id|__u32
id|group
suffix:semicolon
DECL|member|block_bitmap
id|__u32
id|block_bitmap
suffix:semicolon
DECL|member|inode_bitmap
id|__u32
id|inode_bitmap
suffix:semicolon
DECL|member|inode_table
id|__u32
id|inode_table
suffix:semicolon
DECL|member|blocks_count
id|__u32
id|blocks_count
suffix:semicolon
DECL|member|reserved_blocks
id|__u16
id|reserved_blocks
suffix:semicolon
DECL|member|unused
id|__u16
id|unused
suffix:semicolon
DECL|member|free_blocks_count
id|__u32
id|free_blocks_count
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * ioctl commands&n; */
DECL|macro|EXT3_IOC_GETFLAGS
mdefine_line|#define&t;EXT3_IOC_GETFLAGS&t;&t;_IOR(&squot;f&squot;, 1, long)
DECL|macro|EXT3_IOC_SETFLAGS
mdefine_line|#define&t;EXT3_IOC_SETFLAGS&t;&t;_IOW(&squot;f&squot;, 2, long)
DECL|macro|EXT3_IOC_GETVERSION
mdefine_line|#define&t;EXT3_IOC_GETVERSION&t;&t;_IOR(&squot;f&squot;, 3, long)
DECL|macro|EXT3_IOC_SETVERSION
mdefine_line|#define&t;EXT3_IOC_SETVERSION&t;&t;_IOW(&squot;f&squot;, 4, long)
DECL|macro|EXT3_IOC_GROUP_EXTEND
mdefine_line|#define EXT3_IOC_GROUP_EXTEND&t;&t;_IOW(&squot;f&squot;, 7, unsigned long)
DECL|macro|EXT3_IOC_GROUP_ADD
mdefine_line|#define EXT3_IOC_GROUP_ADD&t;&t;_IOW(&squot;f&squot;, 8,struct ext3_new_group_input)
DECL|macro|EXT3_IOC_GETVERSION_OLD
mdefine_line|#define&t;EXT3_IOC_GETVERSION_OLD&t;&t;_IOR(&squot;v&squot;, 1, long)
DECL|macro|EXT3_IOC_SETVERSION_OLD
mdefine_line|#define&t;EXT3_IOC_SETVERSION_OLD&t;&t;_IOW(&squot;v&squot;, 2, long)
macro_line|#ifdef CONFIG_JBD_DEBUG
DECL|macro|EXT3_IOC_WAIT_FOR_READONLY
mdefine_line|#define EXT3_IOC_WAIT_FOR_READONLY&t;_IOR(&squot;f&squot;, 99, long)
macro_line|#endif
DECL|macro|EXT3_IOC_GETRSVSZ
mdefine_line|#define EXT3_IOC_GETRSVSZ&t;&t;_IOR(&squot;f&squot;, 5, long)
DECL|macro|EXT3_IOC_SETRSVSZ
mdefine_line|#define EXT3_IOC_SETRSVSZ&t;&t;_IOW(&squot;f&squot;, 6, long)
multiline_comment|/*&n; * Structure of an inode on the disk&n; */
DECL|struct|ext3_inode
r_struct
id|ext3_inode
(brace
DECL|member|i_mode
id|__le16
id|i_mode
suffix:semicolon
multiline_comment|/* File mode */
DECL|member|i_uid
id|__le16
id|i_uid
suffix:semicolon
multiline_comment|/* Low 16 bits of Owner Uid */
DECL|member|i_size
id|__le32
id|i_size
suffix:semicolon
multiline_comment|/* Size in bytes */
DECL|member|i_atime
id|__le32
id|i_atime
suffix:semicolon
multiline_comment|/* Access time */
DECL|member|i_ctime
id|__le32
id|i_ctime
suffix:semicolon
multiline_comment|/* Creation time */
DECL|member|i_mtime
id|__le32
id|i_mtime
suffix:semicolon
multiline_comment|/* Modification time */
DECL|member|i_dtime
id|__le32
id|i_dtime
suffix:semicolon
multiline_comment|/* Deletion Time */
DECL|member|i_gid
id|__le16
id|i_gid
suffix:semicolon
multiline_comment|/* Low 16 bits of Group Id */
DECL|member|i_links_count
id|__le16
id|i_links_count
suffix:semicolon
multiline_comment|/* Links count */
DECL|member|i_blocks
id|__le32
id|i_blocks
suffix:semicolon
multiline_comment|/* Blocks count */
DECL|member|i_flags
id|__le32
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
id|__le32
id|i_block
(braket
id|EXT3_N_BLOCKS
)braket
suffix:semicolon
multiline_comment|/* Pointers to blocks */
DECL|member|i_generation
id|__le32
id|i_generation
suffix:semicolon
multiline_comment|/* File version (for NFS) */
DECL|member|i_file_acl
id|__le32
id|i_file_acl
suffix:semicolon
multiline_comment|/* File ACL */
DECL|member|i_dir_acl
id|__le32
id|i_dir_acl
suffix:semicolon
multiline_comment|/* Directory ACL */
DECL|member|i_faddr
id|__le32
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
id|__le16
id|l_i_uid_high
suffix:semicolon
multiline_comment|/* these 2 fields    */
DECL|member|l_i_gid_high
id|__le16
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
DECL|member|i_extra_isize
id|__le16
id|i_extra_isize
suffix:semicolon
DECL|member|i_pad1
id|__le16
id|i_pad1
suffix:semicolon
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
macro_line|#elif defined(__GNU__)
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
macro_line|#elif defined(__masix__)
DECL|macro|i_reserved1
mdefine_line|#define i_reserved1&t;osd1.masix1.m_i_reserved1
DECL|macro|i_frag
mdefine_line|#define i_frag&t;&t;osd2.masix2.m_i_frag
DECL|macro|i_fsize
mdefine_line|#define i_fsize&t;&t;osd2.masix2.m_i_fsize
DECL|macro|i_reserved2
mdefine_line|#define i_reserved2&t;osd2.masix2.m_i_reserved2
macro_line|#endif /* defined(__KERNEL__) || defined(__linux__) */
multiline_comment|/*&n; * File system states&n; */
DECL|macro|EXT3_VALID_FS
mdefine_line|#define&t;EXT3_VALID_FS&t;&t;&t;0x0001&t;/* Unmounted cleanly */
DECL|macro|EXT3_ERROR_FS
mdefine_line|#define&t;EXT3_ERROR_FS&t;&t;&t;0x0002&t;/* Errors detected */
DECL|macro|EXT3_ORPHAN_FS
mdefine_line|#define&t;EXT3_ORPHAN_FS&t;&t;&t;0x0004&t;/* Orphans being recovered */
multiline_comment|/*&n; * Mount flags&n; */
DECL|macro|EXT3_MOUNT_CHECK
mdefine_line|#define EXT3_MOUNT_CHECK&t;&t;0x00001&t;/* Do mount-time checks */
DECL|macro|EXT3_MOUNT_OLDALLOC
mdefine_line|#define EXT3_MOUNT_OLDALLOC&t;&t;0x00002  /* Don&squot;t use the new Orlov allocator */
DECL|macro|EXT3_MOUNT_GRPID
mdefine_line|#define EXT3_MOUNT_GRPID&t;&t;0x00004&t;/* Create files with directory&squot;s group */
DECL|macro|EXT3_MOUNT_DEBUG
mdefine_line|#define EXT3_MOUNT_DEBUG&t;&t;0x00008&t;/* Some debugging messages */
DECL|macro|EXT3_MOUNT_ERRORS_CONT
mdefine_line|#define EXT3_MOUNT_ERRORS_CONT&t;&t;0x00010&t;/* Continue on errors */
DECL|macro|EXT3_MOUNT_ERRORS_RO
mdefine_line|#define EXT3_MOUNT_ERRORS_RO&t;&t;0x00020&t;/* Remount fs ro on errors */
DECL|macro|EXT3_MOUNT_ERRORS_PANIC
mdefine_line|#define EXT3_MOUNT_ERRORS_PANIC&t;&t;0x00040&t;/* Panic on errors */
DECL|macro|EXT3_MOUNT_MINIX_DF
mdefine_line|#define EXT3_MOUNT_MINIX_DF&t;&t;0x00080&t;/* Mimics the Minix statfs */
DECL|macro|EXT3_MOUNT_NOLOAD
mdefine_line|#define EXT3_MOUNT_NOLOAD&t;&t;0x00100&t;/* Don&squot;t use existing journal*/
DECL|macro|EXT3_MOUNT_ABORT
mdefine_line|#define EXT3_MOUNT_ABORT&t;&t;0x00200&t;/* Fatal error detected */
DECL|macro|EXT3_MOUNT_DATA_FLAGS
mdefine_line|#define EXT3_MOUNT_DATA_FLAGS&t;&t;0x00C00&t;/* Mode for data writes: */
DECL|macro|EXT3_MOUNT_JOURNAL_DATA
mdefine_line|#define EXT3_MOUNT_JOURNAL_DATA&t;&t;0x00400&t;/* Write data to journal */
DECL|macro|EXT3_MOUNT_ORDERED_DATA
mdefine_line|#define EXT3_MOUNT_ORDERED_DATA&t;&t;0x00800&t;/* Flush data before commit */
DECL|macro|EXT3_MOUNT_WRITEBACK_DATA
mdefine_line|#define EXT3_MOUNT_WRITEBACK_DATA&t;0x00C00&t;/* No data ordering */
DECL|macro|EXT3_MOUNT_UPDATE_JOURNAL
mdefine_line|#define EXT3_MOUNT_UPDATE_JOURNAL&t;0x01000&t;/* Update the journal format */
DECL|macro|EXT3_MOUNT_NO_UID32
mdefine_line|#define EXT3_MOUNT_NO_UID32&t;&t;0x02000  /* Disable 32-bit UIDs */
DECL|macro|EXT3_MOUNT_XATTR_USER
mdefine_line|#define EXT3_MOUNT_XATTR_USER&t;&t;0x04000&t;/* Extended user attributes */
DECL|macro|EXT3_MOUNT_POSIX_ACL
mdefine_line|#define EXT3_MOUNT_POSIX_ACL&t;&t;0x08000&t;/* POSIX Access Control Lists */
DECL|macro|EXT3_MOUNT_RESERVATION
mdefine_line|#define EXT3_MOUNT_RESERVATION&t;&t;0x10000&t;/* Preallocation */
DECL|macro|EXT3_MOUNT_BARRIER
mdefine_line|#define EXT3_MOUNT_BARRIER&t;&t;0x20000 /* Use block barriers */
multiline_comment|/* Compatibility, for having both ext2_fs.h and ext3_fs.h included at once */
macro_line|#ifndef _LINUX_EXT2_FS_H
DECL|macro|clear_opt
mdefine_line|#define clear_opt(o, opt)&t;&t;o &amp;= ~EXT3_MOUNT_##opt
DECL|macro|set_opt
mdefine_line|#define set_opt(o, opt)&t;&t;&t;o |= EXT3_MOUNT_##opt
DECL|macro|test_opt
mdefine_line|#define test_opt(sb, opt)&t;&t;(EXT3_SB(sb)-&gt;s_mount_opt &amp; &bslash;&n;&t;&t;&t;&t;&t; EXT3_MOUNT_##opt)
macro_line|#else
DECL|macro|EXT2_MOUNT_NOLOAD
mdefine_line|#define EXT2_MOUNT_NOLOAD&t;&t;EXT3_MOUNT_NOLOAD
DECL|macro|EXT2_MOUNT_ABORT
mdefine_line|#define EXT2_MOUNT_ABORT&t;&t;EXT3_MOUNT_ABORT
DECL|macro|EXT2_MOUNT_DATA_FLAGS
mdefine_line|#define EXT2_MOUNT_DATA_FLAGS&t;&t;EXT3_MOUNT_DATA_FLAGS
macro_line|#endif
DECL|macro|ext3_set_bit
mdefine_line|#define ext3_set_bit&t;&t;&t;ext2_set_bit
DECL|macro|ext3_set_bit_atomic
mdefine_line|#define ext3_set_bit_atomic&t;&t;ext2_set_bit_atomic
DECL|macro|ext3_clear_bit
mdefine_line|#define ext3_clear_bit&t;&t;&t;ext2_clear_bit
DECL|macro|ext3_clear_bit_atomic
mdefine_line|#define ext3_clear_bit_atomic&t;&t;ext2_clear_bit_atomic
DECL|macro|ext3_test_bit
mdefine_line|#define ext3_test_bit&t;&t;&t;ext2_test_bit
DECL|macro|ext3_find_first_zero_bit
mdefine_line|#define ext3_find_first_zero_bit&t;ext2_find_first_zero_bit
DECL|macro|ext3_find_next_zero_bit
mdefine_line|#define ext3_find_next_zero_bit&t;&t;ext2_find_next_zero_bit
multiline_comment|/*&n; * Maximal mount counts between two filesystem checks&n; */
DECL|macro|EXT3_DFL_MAX_MNT_COUNT
mdefine_line|#define EXT3_DFL_MAX_MNT_COUNT&t;&t;20&t;/* Allow 20 mounts */
DECL|macro|EXT3_DFL_CHECKINTERVAL
mdefine_line|#define EXT3_DFL_CHECKINTERVAL&t;&t;0&t;/* Don&squot;t use interval check */
multiline_comment|/*&n; * Behaviour when detecting errors&n; */
DECL|macro|EXT3_ERRORS_CONTINUE
mdefine_line|#define EXT3_ERRORS_CONTINUE&t;&t;1&t;/* Continue execution */
DECL|macro|EXT3_ERRORS_RO
mdefine_line|#define EXT3_ERRORS_RO&t;&t;&t;2&t;/* Remount fs read-only */
DECL|macro|EXT3_ERRORS_PANIC
mdefine_line|#define EXT3_ERRORS_PANIC&t;&t;3&t;/* Panic */
DECL|macro|EXT3_ERRORS_DEFAULT
mdefine_line|#define EXT3_ERRORS_DEFAULT&t;&t;EXT3_ERRORS_CONTINUE
multiline_comment|/*&n; * Structure of the super block&n; */
DECL|struct|ext3_super_block
r_struct
id|ext3_super_block
(brace
DECL|member|s_inodes_count
multiline_comment|/*00*/
id|__le32
id|s_inodes_count
suffix:semicolon
multiline_comment|/* Inodes count */
DECL|member|s_blocks_count
id|__le32
id|s_blocks_count
suffix:semicolon
multiline_comment|/* Blocks count */
DECL|member|s_r_blocks_count
id|__le32
id|s_r_blocks_count
suffix:semicolon
multiline_comment|/* Reserved blocks count */
DECL|member|s_free_blocks_count
id|__le32
id|s_free_blocks_count
suffix:semicolon
multiline_comment|/* Free blocks count */
DECL|member|s_free_inodes_count
multiline_comment|/*10*/
id|__le32
id|s_free_inodes_count
suffix:semicolon
multiline_comment|/* Free inodes count */
DECL|member|s_first_data_block
id|__le32
id|s_first_data_block
suffix:semicolon
multiline_comment|/* First Data Block */
DECL|member|s_log_block_size
id|__le32
id|s_log_block_size
suffix:semicolon
multiline_comment|/* Block size */
DECL|member|s_log_frag_size
id|__le32
id|s_log_frag_size
suffix:semicolon
multiline_comment|/* Fragment size */
DECL|member|s_blocks_per_group
multiline_comment|/*20*/
id|__le32
id|s_blocks_per_group
suffix:semicolon
multiline_comment|/* # Blocks per group */
DECL|member|s_frags_per_group
id|__le32
id|s_frags_per_group
suffix:semicolon
multiline_comment|/* # Fragments per group */
DECL|member|s_inodes_per_group
id|__le32
id|s_inodes_per_group
suffix:semicolon
multiline_comment|/* # Inodes per group */
DECL|member|s_mtime
id|__le32
id|s_mtime
suffix:semicolon
multiline_comment|/* Mount time */
DECL|member|s_wtime
multiline_comment|/*30*/
id|__le32
id|s_wtime
suffix:semicolon
multiline_comment|/* Write time */
DECL|member|s_mnt_count
id|__le16
id|s_mnt_count
suffix:semicolon
multiline_comment|/* Mount count */
DECL|member|s_max_mnt_count
id|__le16
id|s_max_mnt_count
suffix:semicolon
multiline_comment|/* Maximal mount count */
DECL|member|s_magic
id|__le16
id|s_magic
suffix:semicolon
multiline_comment|/* Magic signature */
DECL|member|s_state
id|__le16
id|s_state
suffix:semicolon
multiline_comment|/* File system state */
DECL|member|s_errors
id|__le16
id|s_errors
suffix:semicolon
multiline_comment|/* Behaviour when detecting errors */
DECL|member|s_minor_rev_level
id|__le16
id|s_minor_rev_level
suffix:semicolon
multiline_comment|/* minor revision level */
DECL|member|s_lastcheck
multiline_comment|/*40*/
id|__le32
id|s_lastcheck
suffix:semicolon
multiline_comment|/* time of last check */
DECL|member|s_checkinterval
id|__le32
id|s_checkinterval
suffix:semicolon
multiline_comment|/* max. time between checks */
DECL|member|s_creator_os
id|__le32
id|s_creator_os
suffix:semicolon
multiline_comment|/* OS */
DECL|member|s_rev_level
id|__le32
id|s_rev_level
suffix:semicolon
multiline_comment|/* Revision level */
DECL|member|s_def_resuid
multiline_comment|/*50*/
id|__le16
id|s_def_resuid
suffix:semicolon
multiline_comment|/* Default uid for reserved blocks */
DECL|member|s_def_resgid
id|__le16
id|s_def_resgid
suffix:semicolon
multiline_comment|/* Default gid for reserved blocks */
multiline_comment|/*&n;&t; * These fields are for EXT3_DYNAMIC_REV superblocks only.&n;&t; *&n;&t; * Note: the difference between the compatible feature set and&n;&t; * the incompatible feature set is that if there is a bit set&n;&t; * in the incompatible feature set that the kernel doesn&squot;t&n;&t; * know about, it should refuse to mount the filesystem.&n;&t; *&n;&t; * e2fsck&squot;s requirements are more strict; if it doesn&squot;t know&n;&t; * about a feature in either the compatible or incompatible&n;&t; * feature set, it must abort and not try to meddle with&n;&t; * things it doesn&squot;t understand...&n;&t; */
DECL|member|s_first_ino
id|__le32
id|s_first_ino
suffix:semicolon
multiline_comment|/* First non-reserved inode */
DECL|member|s_inode_size
id|__le16
id|s_inode_size
suffix:semicolon
multiline_comment|/* size of inode structure */
DECL|member|s_block_group_nr
id|__le16
id|s_block_group_nr
suffix:semicolon
multiline_comment|/* block group # of this superblock */
DECL|member|s_feature_compat
id|__le32
id|s_feature_compat
suffix:semicolon
multiline_comment|/* compatible feature set */
DECL|member|s_feature_incompat
multiline_comment|/*60*/
id|__le32
id|s_feature_incompat
suffix:semicolon
multiline_comment|/* incompatible feature set */
DECL|member|s_feature_ro_compat
id|__le32
id|s_feature_ro_compat
suffix:semicolon
multiline_comment|/* readonly-compatible feature set */
DECL|member|s_uuid
multiline_comment|/*68*/
id|__u8
id|s_uuid
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* 128-bit uuid for volume */
DECL|member|s_volume_name
multiline_comment|/*78*/
r_char
id|s_volume_name
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* volume name */
DECL|member|s_last_mounted
multiline_comment|/*88*/
r_char
id|s_last_mounted
(braket
l_int|64
)braket
suffix:semicolon
multiline_comment|/* directory where last mounted */
DECL|member|s_algorithm_usage_bitmap
multiline_comment|/*C8*/
id|__le32
id|s_algorithm_usage_bitmap
suffix:semicolon
multiline_comment|/* For compression */
multiline_comment|/*&n;&t; * Performance hints.  Directory preallocation should only&n;&t; * happen if the EXT3_FEATURE_COMPAT_DIR_PREALLOC flag is on.&n;&t; */
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
DECL|member|s_reserved_gdt_blocks
id|__u16
id|s_reserved_gdt_blocks
suffix:semicolon
multiline_comment|/* Per group desc for online growth */
multiline_comment|/*&n;&t; * Journaling support valid if EXT3_FEATURE_COMPAT_HAS_JOURNAL set.&n;&t; */
DECL|member|s_journal_uuid
multiline_comment|/*D0*/
id|__u8
id|s_journal_uuid
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* uuid of journal superblock */
DECL|member|s_journal_inum
multiline_comment|/*E0*/
id|__le32
id|s_journal_inum
suffix:semicolon
multiline_comment|/* inode number of journal file */
DECL|member|s_journal_dev
id|__le32
id|s_journal_dev
suffix:semicolon
multiline_comment|/* device number of journal file */
DECL|member|s_last_orphan
id|__le32
id|s_last_orphan
suffix:semicolon
multiline_comment|/* start of list of inodes to delete */
DECL|member|s_hash_seed
id|__le32
id|s_hash_seed
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* HTREE hash seed */
DECL|member|s_def_hash_version
id|__u8
id|s_def_hash_version
suffix:semicolon
multiline_comment|/* Default hash version to use */
DECL|member|s_reserved_char_pad
id|__u8
id|s_reserved_char_pad
suffix:semicolon
DECL|member|s_reserved_word_pad
id|__u16
id|s_reserved_word_pad
suffix:semicolon
DECL|member|s_default_mount_opts
id|__le32
id|s_default_mount_opts
suffix:semicolon
DECL|member|s_first_meta_bg
id|__le32
id|s_first_meta_bg
suffix:semicolon
multiline_comment|/* First metablock block group */
DECL|member|s_reserved
id|__u32
id|s_reserved
(braket
l_int|190
)braket
suffix:semicolon
multiline_comment|/* Padding to the end of the block */
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
DECL|function|EXT3_SB
r_static
r_inline
r_struct
id|ext3_sb_info
op_star
id|EXT3_SB
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_return
id|sb-&gt;s_fs_info
suffix:semicolon
)brace
DECL|function|EXT3_I
r_static
r_inline
r_struct
id|ext3_inode_info
op_star
id|EXT3_I
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_return
id|container_of
c_func
(paren
id|inode
comma
r_struct
id|ext3_inode_info
comma
id|vfs_inode
)paren
suffix:semicolon
)brace
macro_line|#else
multiline_comment|/* Assume that user mode programs are passing in an ext3fs superblock, not&n; * a kernel struct super_block.  This will allow us to call the feature-test&n; * macros from user land. */
DECL|macro|EXT3_SB
mdefine_line|#define EXT3_SB(sb)&t;(sb)
macro_line|#endif
DECL|macro|NEXT_ORPHAN
mdefine_line|#define NEXT_ORPHAN(inode) EXT3_I(inode)-&gt;i_dtime
multiline_comment|/*&n; * Codes for operating systems&n; */
DECL|macro|EXT3_OS_LINUX
mdefine_line|#define EXT3_OS_LINUX&t;&t;0
DECL|macro|EXT3_OS_HURD
mdefine_line|#define EXT3_OS_HURD&t;&t;1
DECL|macro|EXT3_OS_MASIX
mdefine_line|#define EXT3_OS_MASIX&t;&t;2
DECL|macro|EXT3_OS_FREEBSD
mdefine_line|#define EXT3_OS_FREEBSD&t;&t;3
DECL|macro|EXT3_OS_LITES
mdefine_line|#define EXT3_OS_LITES&t;&t;4
multiline_comment|/*&n; * Revision levels&n; */
DECL|macro|EXT3_GOOD_OLD_REV
mdefine_line|#define EXT3_GOOD_OLD_REV&t;0&t;/* The good old (original) format */
DECL|macro|EXT3_DYNAMIC_REV
mdefine_line|#define EXT3_DYNAMIC_REV&t;1&t;/* V2 format w/ dynamic inode sizes */
DECL|macro|EXT3_CURRENT_REV
mdefine_line|#define EXT3_CURRENT_REV&t;EXT3_GOOD_OLD_REV
DECL|macro|EXT3_MAX_SUPP_REV
mdefine_line|#define EXT3_MAX_SUPP_REV&t;EXT3_DYNAMIC_REV
DECL|macro|EXT3_GOOD_OLD_INODE_SIZE
mdefine_line|#define EXT3_GOOD_OLD_INODE_SIZE 128
multiline_comment|/*&n; * Feature set definitions&n; */
DECL|macro|EXT3_HAS_COMPAT_FEATURE
mdefine_line|#define EXT3_HAS_COMPAT_FEATURE(sb,mask)&t;&t;&t;&bslash;&n;&t;( EXT3_SB(sb)-&gt;s_es-&gt;s_feature_compat &amp; cpu_to_le32(mask) )
DECL|macro|EXT3_HAS_RO_COMPAT_FEATURE
mdefine_line|#define EXT3_HAS_RO_COMPAT_FEATURE(sb,mask)&t;&t;&t;&bslash;&n;&t;( EXT3_SB(sb)-&gt;s_es-&gt;s_feature_ro_compat &amp; cpu_to_le32(mask) )
DECL|macro|EXT3_HAS_INCOMPAT_FEATURE
mdefine_line|#define EXT3_HAS_INCOMPAT_FEATURE(sb,mask)&t;&t;&t;&bslash;&n;&t;( EXT3_SB(sb)-&gt;s_es-&gt;s_feature_incompat &amp; cpu_to_le32(mask) )
DECL|macro|EXT3_SET_COMPAT_FEATURE
mdefine_line|#define EXT3_SET_COMPAT_FEATURE(sb,mask)&t;&t;&t;&bslash;&n;&t;EXT3_SB(sb)-&gt;s_es-&gt;s_feature_compat |= cpu_to_le32(mask)
DECL|macro|EXT3_SET_RO_COMPAT_FEATURE
mdefine_line|#define EXT3_SET_RO_COMPAT_FEATURE(sb,mask)&t;&t;&t;&bslash;&n;&t;EXT3_SB(sb)-&gt;s_es-&gt;s_feature_ro_compat |= cpu_to_le32(mask)
DECL|macro|EXT3_SET_INCOMPAT_FEATURE
mdefine_line|#define EXT3_SET_INCOMPAT_FEATURE(sb,mask)&t;&t;&t;&bslash;&n;&t;EXT3_SB(sb)-&gt;s_es-&gt;s_feature_incompat |= cpu_to_le32(mask)
DECL|macro|EXT3_CLEAR_COMPAT_FEATURE
mdefine_line|#define EXT3_CLEAR_COMPAT_FEATURE(sb,mask)&t;&t;&t;&bslash;&n;&t;EXT3_SB(sb)-&gt;s_es-&gt;s_feature_compat &amp;= ~cpu_to_le32(mask)
DECL|macro|EXT3_CLEAR_RO_COMPAT_FEATURE
mdefine_line|#define EXT3_CLEAR_RO_COMPAT_FEATURE(sb,mask)&t;&t;&t;&bslash;&n;&t;EXT3_SB(sb)-&gt;s_es-&gt;s_feature_ro_compat &amp;= ~cpu_to_le32(mask)
DECL|macro|EXT3_CLEAR_INCOMPAT_FEATURE
mdefine_line|#define EXT3_CLEAR_INCOMPAT_FEATURE(sb,mask)&t;&t;&t;&bslash;&n;&t;EXT3_SB(sb)-&gt;s_es-&gt;s_feature_incompat &amp;= ~cpu_to_le32(mask)
DECL|macro|EXT3_FEATURE_COMPAT_DIR_PREALLOC
mdefine_line|#define EXT3_FEATURE_COMPAT_DIR_PREALLOC&t;0x0001
DECL|macro|EXT3_FEATURE_COMPAT_IMAGIC_INODES
mdefine_line|#define EXT3_FEATURE_COMPAT_IMAGIC_INODES&t;0x0002
DECL|macro|EXT3_FEATURE_COMPAT_HAS_JOURNAL
mdefine_line|#define EXT3_FEATURE_COMPAT_HAS_JOURNAL&t;&t;0x0004
DECL|macro|EXT3_FEATURE_COMPAT_EXT_ATTR
mdefine_line|#define EXT3_FEATURE_COMPAT_EXT_ATTR&t;&t;0x0008
DECL|macro|EXT3_FEATURE_COMPAT_RESIZE_INODE
mdefine_line|#define EXT3_FEATURE_COMPAT_RESIZE_INODE&t;0x0010
DECL|macro|EXT3_FEATURE_COMPAT_DIR_INDEX
mdefine_line|#define EXT3_FEATURE_COMPAT_DIR_INDEX&t;&t;0x0020
DECL|macro|EXT3_FEATURE_RO_COMPAT_SPARSE_SUPER
mdefine_line|#define EXT3_FEATURE_RO_COMPAT_SPARSE_SUPER&t;0x0001
DECL|macro|EXT3_FEATURE_RO_COMPAT_LARGE_FILE
mdefine_line|#define EXT3_FEATURE_RO_COMPAT_LARGE_FILE&t;0x0002
DECL|macro|EXT3_FEATURE_RO_COMPAT_BTREE_DIR
mdefine_line|#define EXT3_FEATURE_RO_COMPAT_BTREE_DIR&t;0x0004
DECL|macro|EXT3_FEATURE_INCOMPAT_COMPRESSION
mdefine_line|#define EXT3_FEATURE_INCOMPAT_COMPRESSION&t;0x0001
DECL|macro|EXT3_FEATURE_INCOMPAT_FILETYPE
mdefine_line|#define EXT3_FEATURE_INCOMPAT_FILETYPE&t;&t;0x0002
DECL|macro|EXT3_FEATURE_INCOMPAT_RECOVER
mdefine_line|#define EXT3_FEATURE_INCOMPAT_RECOVER&t;&t;0x0004 /* Needs recovery */
DECL|macro|EXT3_FEATURE_INCOMPAT_JOURNAL_DEV
mdefine_line|#define EXT3_FEATURE_INCOMPAT_JOURNAL_DEV&t;0x0008 /* Journal device */
DECL|macro|EXT3_FEATURE_INCOMPAT_META_BG
mdefine_line|#define EXT3_FEATURE_INCOMPAT_META_BG&t;&t;0x0010
DECL|macro|EXT3_FEATURE_COMPAT_SUPP
mdefine_line|#define EXT3_FEATURE_COMPAT_SUPP&t;EXT2_FEATURE_COMPAT_EXT_ATTR
DECL|macro|EXT3_FEATURE_INCOMPAT_SUPP
mdefine_line|#define EXT3_FEATURE_INCOMPAT_SUPP&t;(EXT3_FEATURE_INCOMPAT_FILETYPE| &bslash;&n;&t;&t;&t;&t;&t; EXT3_FEATURE_INCOMPAT_RECOVER| &bslash;&n;&t;&t;&t;&t;&t; EXT3_FEATURE_INCOMPAT_META_BG)
DECL|macro|EXT3_FEATURE_RO_COMPAT_SUPP
mdefine_line|#define EXT3_FEATURE_RO_COMPAT_SUPP&t;(EXT3_FEATURE_RO_COMPAT_SPARSE_SUPER| &bslash;&n;&t;&t;&t;&t;&t; EXT3_FEATURE_RO_COMPAT_LARGE_FILE| &bslash;&n;&t;&t;&t;&t;&t; EXT3_FEATURE_RO_COMPAT_BTREE_DIR)
multiline_comment|/*&n; * Default values for user and/or group using reserved blocks&n; */
DECL|macro|EXT3_DEF_RESUID
mdefine_line|#define&t;EXT3_DEF_RESUID&t;&t;0
DECL|macro|EXT3_DEF_RESGID
mdefine_line|#define&t;EXT3_DEF_RESGID&t;&t;0
multiline_comment|/*&n; * Default mount options&n; */
DECL|macro|EXT3_DEFM_DEBUG
mdefine_line|#define EXT3_DEFM_DEBUG&t;&t;0x0001
DECL|macro|EXT3_DEFM_BSDGROUPS
mdefine_line|#define EXT3_DEFM_BSDGROUPS&t;0x0002
DECL|macro|EXT3_DEFM_XATTR_USER
mdefine_line|#define EXT3_DEFM_XATTR_USER&t;0x0004
DECL|macro|EXT3_DEFM_ACL
mdefine_line|#define EXT3_DEFM_ACL&t;&t;0x0008
DECL|macro|EXT3_DEFM_UID16
mdefine_line|#define EXT3_DEFM_UID16&t;&t;0x0010
DECL|macro|EXT3_DEFM_JMODE
mdefine_line|#define EXT3_DEFM_JMODE&t;&t;0x0060
DECL|macro|EXT3_DEFM_JMODE_DATA
mdefine_line|#define EXT3_DEFM_JMODE_DATA&t;0x0020
DECL|macro|EXT3_DEFM_JMODE_ORDERED
mdefine_line|#define EXT3_DEFM_JMODE_ORDERED&t;0x0040
DECL|macro|EXT3_DEFM_JMODE_WBACK
mdefine_line|#define EXT3_DEFM_JMODE_WBACK&t;0x0060
multiline_comment|/*&n; * Structure of a directory entry&n; */
DECL|macro|EXT3_NAME_LEN
mdefine_line|#define EXT3_NAME_LEN 255
DECL|struct|ext3_dir_entry
r_struct
id|ext3_dir_entry
(brace
DECL|member|inode
id|__le32
id|inode
suffix:semicolon
multiline_comment|/* Inode number */
DECL|member|rec_len
id|__le16
id|rec_len
suffix:semicolon
multiline_comment|/* Directory entry length */
DECL|member|name_len
id|__le16
id|name_len
suffix:semicolon
multiline_comment|/* Name length */
DECL|member|name
r_char
id|name
(braket
id|EXT3_NAME_LEN
)braket
suffix:semicolon
multiline_comment|/* File name */
)brace
suffix:semicolon
multiline_comment|/*&n; * The new version of the directory entry.  Since EXT3 structures are&n; * stored in intel byte order, and the name_len field could never be&n; * bigger than 255 chars, it&squot;s safe to reclaim the extra byte for the&n; * file_type field.&n; */
DECL|struct|ext3_dir_entry_2
r_struct
id|ext3_dir_entry_2
(brace
DECL|member|inode
id|__le32
id|inode
suffix:semicolon
multiline_comment|/* Inode number */
DECL|member|rec_len
id|__le16
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
id|EXT3_NAME_LEN
)braket
suffix:semicolon
multiline_comment|/* File name */
)brace
suffix:semicolon
multiline_comment|/*&n; * Ext3 directory file types.  Only the low 3 bits are used.  The&n; * other bits are reserved for now.&n; */
DECL|macro|EXT3_FT_UNKNOWN
mdefine_line|#define EXT3_FT_UNKNOWN&t;&t;0
DECL|macro|EXT3_FT_REG_FILE
mdefine_line|#define EXT3_FT_REG_FILE&t;1
DECL|macro|EXT3_FT_DIR
mdefine_line|#define EXT3_FT_DIR&t;&t;2
DECL|macro|EXT3_FT_CHRDEV
mdefine_line|#define EXT3_FT_CHRDEV&t;&t;3
DECL|macro|EXT3_FT_BLKDEV
mdefine_line|#define EXT3_FT_BLKDEV&t;&t;4
DECL|macro|EXT3_FT_FIFO
mdefine_line|#define EXT3_FT_FIFO&t;&t;5
DECL|macro|EXT3_FT_SOCK
mdefine_line|#define EXT3_FT_SOCK&t;&t;6
DECL|macro|EXT3_FT_SYMLINK
mdefine_line|#define EXT3_FT_SYMLINK&t;&t;7
DECL|macro|EXT3_FT_MAX
mdefine_line|#define EXT3_FT_MAX&t;&t;8
multiline_comment|/*&n; * EXT3_DIR_PAD defines the directory entries boundaries&n; *&n; * NOTE: It must be a multiple of 4&n; */
DECL|macro|EXT3_DIR_PAD
mdefine_line|#define EXT3_DIR_PAD&t;&t;&t;4
DECL|macro|EXT3_DIR_ROUND
mdefine_line|#define EXT3_DIR_ROUND&t;&t;&t;(EXT3_DIR_PAD - 1)
DECL|macro|EXT3_DIR_REC_LEN
mdefine_line|#define EXT3_DIR_REC_LEN(name_len)&t;(((name_len) + 8 + EXT3_DIR_ROUND) &amp; &bslash;&n;&t;&t;&t;&t;&t; ~EXT3_DIR_ROUND)
multiline_comment|/*&n; * Hash Tree Directory indexing&n; * (c) Daniel Phillips, 2001&n; */
macro_line|#ifdef CONFIG_EXT3_INDEX
DECL|macro|is_dx
mdefine_line|#define is_dx(dir) (EXT3_HAS_COMPAT_FEATURE(dir-&gt;i_sb, &bslash;&n;&t;&t;&t;&t;&t;      EXT3_FEATURE_COMPAT_DIR_INDEX) &amp;&amp; &bslash;&n;&t;&t;      (EXT3_I(dir)-&gt;i_flags &amp; EXT3_INDEX_FL))
DECL|macro|EXT3_DIR_LINK_MAX
mdefine_line|#define EXT3_DIR_LINK_MAX(dir) (!is_dx(dir) &amp;&amp; (dir)-&gt;i_nlink &gt;= EXT3_LINK_MAX)
DECL|macro|EXT3_DIR_LINK_EMPTY
mdefine_line|#define EXT3_DIR_LINK_EMPTY(dir) ((dir)-&gt;i_nlink == 2 || (dir)-&gt;i_nlink == 1)
macro_line|#else
DECL|macro|is_dx
mdefine_line|#define is_dx(dir) 0
DECL|macro|EXT3_DIR_LINK_MAX
mdefine_line|#define EXT3_DIR_LINK_MAX(dir) ((dir)-&gt;i_nlink &gt;= EXT3_LINK_MAX)
DECL|macro|EXT3_DIR_LINK_EMPTY
mdefine_line|#define EXT3_DIR_LINK_EMPTY(dir) ((dir)-&gt;i_nlink == 2)
macro_line|#endif
multiline_comment|/* Legal values for the dx_root hash_version field: */
DECL|macro|DX_HASH_LEGACY
mdefine_line|#define DX_HASH_LEGACY&t;&t;0
DECL|macro|DX_HASH_HALF_MD4
mdefine_line|#define DX_HASH_HALF_MD4&t;1
DECL|macro|DX_HASH_TEA
mdefine_line|#define DX_HASH_TEA&t;&t;2
multiline_comment|/* hash info structure used by the directory hash */
DECL|struct|dx_hash_info
r_struct
id|dx_hash_info
(brace
DECL|member|hash
id|u32
id|hash
suffix:semicolon
DECL|member|minor_hash
id|u32
id|minor_hash
suffix:semicolon
DECL|member|hash_version
r_int
id|hash_version
suffix:semicolon
DECL|member|seed
id|u32
op_star
id|seed
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|EXT3_HTREE_EOF
mdefine_line|#define EXT3_HTREE_EOF&t;0x7fffffff
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * Control parameters used by ext3_htree_next_block&n; */
DECL|macro|HASH_NB_ALWAYS
mdefine_line|#define HASH_NB_ALWAYS&t;&t;1
multiline_comment|/*&n; * Describe an inode&squot;s exact location on disk and in memory&n; */
DECL|struct|ext3_iloc
r_struct
id|ext3_iloc
(brace
DECL|member|bh
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
DECL|member|offset
r_int
r_int
id|offset
suffix:semicolon
DECL|member|block_group
r_int
r_int
id|block_group
suffix:semicolon
)brace
suffix:semicolon
DECL|function|ext3_raw_inode
r_static
r_inline
r_struct
id|ext3_inode
op_star
id|ext3_raw_inode
c_func
(paren
r_struct
id|ext3_iloc
op_star
id|iloc
)paren
(brace
r_return
(paren
r_struct
id|ext3_inode
op_star
)paren
(paren
id|iloc-&gt;bh-&gt;b_data
op_plus
id|iloc-&gt;offset
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This structure is stuffed into the struct file&squot;s private_data field&n; * for directories.  It is where we put information so that we can do&n; * readdir operations in hash tree order.&n; */
DECL|struct|dir_private_info
r_struct
id|dir_private_info
(brace
DECL|member|root
r_struct
id|rb_root
id|root
suffix:semicolon
DECL|member|curr_node
r_struct
id|rb_node
op_star
id|curr_node
suffix:semicolon
DECL|member|extra_fname
r_struct
id|fname
op_star
id|extra_fname
suffix:semicolon
DECL|member|last_pos
id|loff_t
id|last_pos
suffix:semicolon
DECL|member|curr_hash
id|__u32
id|curr_hash
suffix:semicolon
DECL|member|curr_minor_hash
id|__u32
id|curr_minor_hash
suffix:semicolon
DECL|member|next_hash
id|__u32
id|next_hash
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Special error return code only used by dx_probe() and its callers.&n; */
DECL|macro|ERR_BAD_DX_DIR
mdefine_line|#define ERR_BAD_DX_DIR&t;-75000
multiline_comment|/*&n; * Function prototypes&n; */
multiline_comment|/*&n; * Ok, these declarations are also in &lt;linux/kernel.h&gt; but none of the&n; * ext3 source programs needs to include it so they are duplicated here.&n; */
DECL|macro|NORET_TYPE
macro_line|# define NORET_TYPE    /**/
DECL|macro|ATTRIB_NORET
macro_line|# define ATTRIB_NORET  __attribute__((noreturn))
DECL|macro|NORET_AND
macro_line|# define NORET_AND     noreturn,
multiline_comment|/* balloc.c */
r_extern
r_int
id|ext3_bg_has_super
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
id|ext3_bg_num_gdb
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
id|ext3_new_block
(paren
id|handle_t
op_star
comma
r_struct
id|inode
op_star
comma
r_int
r_int
comma
r_int
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ext3_free_blocks
(paren
id|handle_t
op_star
comma
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
r_void
id|ext3_free_blocks_sb
(paren
id|handle_t
op_star
comma
r_struct
id|super_block
op_star
comma
r_int
r_int
comma
r_int
r_int
comma
r_int
op_star
)paren
suffix:semicolon
r_extern
r_int
r_int
id|ext3_count_free_blocks
(paren
r_struct
id|super_block
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ext3_check_blocks_bitmap
(paren
r_struct
id|super_block
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|ext3_group_desc
op_star
id|ext3_get_group_desc
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
r_extern
r_int
id|ext3_should_retry_alloc
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
op_star
id|retries
)paren
suffix:semicolon
r_extern
r_void
id|ext3_rsv_window_add
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|ext3_reserve_window_node
op_star
id|rsv
)paren
suffix:semicolon
multiline_comment|/* dir.c */
r_extern
r_int
id|ext3_check_dir_entry
c_func
(paren
r_const
r_char
op_star
comma
r_struct
id|inode
op_star
comma
r_struct
id|ext3_dir_entry_2
op_star
comma
r_struct
id|buffer_head
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
id|ext3_htree_store_dirent
c_func
(paren
r_struct
id|file
op_star
id|dir_file
comma
id|__u32
id|hash
comma
id|__u32
id|minor_hash
comma
r_struct
id|ext3_dir_entry_2
op_star
id|dirent
)paren
suffix:semicolon
r_extern
r_void
id|ext3_htree_free_dir_info
c_func
(paren
r_struct
id|dir_private_info
op_star
id|p
)paren
suffix:semicolon
multiline_comment|/* fsync.c */
r_extern
r_int
id|ext3_sync_file
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
multiline_comment|/* hash.c */
r_extern
r_int
id|ext3fs_dirhash
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_int
id|len
comma
r_struct
id|dx_hash_info
op_star
id|hinfo
)paren
suffix:semicolon
multiline_comment|/* ialloc.c */
r_extern
r_struct
id|inode
op_star
id|ext3_new_inode
(paren
id|handle_t
op_star
comma
r_struct
id|inode
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|ext3_free_inode
(paren
id|handle_t
op_star
comma
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|inode
op_star
id|ext3_orphan_get
(paren
r_struct
id|super_block
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
r_int
id|ext3_count_free_inodes
(paren
r_struct
id|super_block
op_star
)paren
suffix:semicolon
r_extern
r_int
r_int
id|ext3_count_dirs
(paren
r_struct
id|super_block
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ext3_check_inodes_bitmap
(paren
r_struct
id|super_block
op_star
)paren
suffix:semicolon
r_extern
r_int
r_int
id|ext3_count_free
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
r_int
id|ext3_forget
c_func
(paren
id|handle_t
op_star
comma
r_int
comma
r_struct
id|inode
op_star
comma
r_struct
id|buffer_head
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_struct
id|buffer_head
op_star
id|ext3_getblk
(paren
id|handle_t
op_star
comma
r_struct
id|inode
op_star
comma
r_int
comma
r_int
comma
r_int
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|buffer_head
op_star
id|ext3_bread
(paren
id|handle_t
op_star
comma
r_struct
id|inode
op_star
comma
r_int
comma
r_int
comma
r_int
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ext3_read_inode
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ext3_write_inode
(paren
r_struct
id|inode
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|ext3_setattr
(paren
r_struct
id|dentry
op_star
comma
r_struct
id|iattr
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ext3_delete_inode
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ext3_sync_inode
(paren
id|handle_t
op_star
comma
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ext3_discard_reservation
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ext3_dirty_inode
c_func
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ext3_change_inode_journal_flag
c_func
(paren
r_struct
id|inode
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|ext3_get_inode_loc
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|ext3_iloc
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ext3_truncate
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ext3_set_inode_flags
c_func
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ext3_set_aops
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
suffix:semicolon
multiline_comment|/* ioctl.c */
r_extern
r_int
id|ext3_ioctl
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
multiline_comment|/* namei.c */
r_extern
r_int
id|ext3_orphan_add
c_func
(paren
id|handle_t
op_star
comma
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ext3_orphan_del
c_func
(paren
id|handle_t
op_star
comma
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ext3_htree_fill_tree
c_func
(paren
r_struct
id|file
op_star
id|dir_file
comma
id|__u32
id|start_hash
comma
id|__u32
id|start_minor_hash
comma
id|__u32
op_star
id|next_hash
)paren
suffix:semicolon
multiline_comment|/* resize.c */
r_extern
r_int
id|ext3_group_add
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|ext3_new_group_data
op_star
id|input
)paren
suffix:semicolon
r_extern
r_int
id|ext3_group_extend
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|ext3_super_block
op_star
id|es
comma
r_int
r_int
id|n_blocks_count
)paren
suffix:semicolon
multiline_comment|/* super.c */
r_extern
r_void
id|ext3_error
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
id|__ext3_std_error
(paren
r_struct
id|super_block
op_star
comma
r_const
r_char
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|ext3_abort
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
id|ext3_warning
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
id|ext3_update_dynamic_rev
(paren
r_struct
id|super_block
op_star
id|sb
)paren
suffix:semicolon
DECL|macro|ext3_std_error
mdefine_line|#define ext3_std_error(sb, errno)&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if ((errno))&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__ext3_std_error((sb), __FUNCTION__, (errno));&t;&bslash;&n;} while (0)
multiline_comment|/*&n; * Inodes and files operations&n; */
multiline_comment|/* dir.c */
r_extern
r_struct
id|file_operations
id|ext3_dir_operations
suffix:semicolon
multiline_comment|/* file.c */
r_extern
r_struct
id|inode_operations
id|ext3_file_inode_operations
suffix:semicolon
r_extern
r_struct
id|file_operations
id|ext3_file_operations
suffix:semicolon
multiline_comment|/* namei.c */
r_extern
r_struct
id|inode_operations
id|ext3_dir_inode_operations
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|ext3_special_inode_operations
suffix:semicolon
multiline_comment|/* symlink.c */
r_extern
r_struct
id|inode_operations
id|ext3_symlink_inode_operations
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|ext3_fast_symlink_inode_operations
suffix:semicolon
macro_line|#endif&t;/* __KERNEL__ */
macro_line|#endif&t;/* _LINUX_EXT3_FS_H */
eof
