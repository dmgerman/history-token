macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/buffer_head.h&gt;
macro_line|#include &lt;linux/affs_fs.h&gt;
macro_line|#include &lt;linux/amigaffs.h&gt;
multiline_comment|/* AmigaOS allows file names with up to 30 characters length.&n; * Names longer than that will be silently truncated. If you&n; * want to disallow this, comment out the following #define.&n; * Creating filesystem objects with longer names will then&n; * result in an error (ENAMETOOLONG).&n; */
multiline_comment|/*#define AFFS_NO_TRUNCATE */
multiline_comment|/* Ugly macros make the code more pretty. */
DECL|macro|GET_END_PTR
mdefine_line|#define GET_END_PTR(st,p,sz)&t;&t; ((st *)((char *)(p)+((sz)-sizeof(st))))
DECL|macro|AFFS_GET_HASHENTRY
mdefine_line|#define AFFS_GET_HASHENTRY(data,hashkey) be32_to_cpu(((struct dir_front *)data)-&gt;hashtable[hashkey])
DECL|macro|AFFS_BLOCK
mdefine_line|#define AFFS_BLOCK(sb, bh, blk)&t;&t;(AFFS_HEAD(bh)-&gt;table[AFFS_SB(sb)-&gt;s_hashsize-1-(blk)])
macro_line|#ifdef __LITTLE_ENDIAN
DECL|macro|BO_EXBITS
mdefine_line|#define BO_EXBITS&t;0x18UL
macro_line|#elif defined(__BIG_ENDIAN)
DECL|macro|BO_EXBITS
mdefine_line|#define BO_EXBITS&t;0x00UL
macro_line|#else
macro_line|#error Endianness must be known for affs to work.
macro_line|#endif
DECL|macro|AFFS_HEAD
mdefine_line|#define AFFS_HEAD(bh)&t;&t;((struct affs_head *)(bh)-&gt;b_data)
DECL|macro|AFFS_TAIL
mdefine_line|#define AFFS_TAIL(sb, bh)&t;((struct affs_tail *)((bh)-&gt;b_data+(sb)-&gt;s_blocksize-sizeof(struct affs_tail)))
DECL|macro|AFFS_ROOT_HEAD
mdefine_line|#define AFFS_ROOT_HEAD(bh)&t;((struct affs_root_head *)(bh)-&gt;b_data)
DECL|macro|AFFS_ROOT_TAIL
mdefine_line|#define AFFS_ROOT_TAIL(sb, bh)&t;((struct affs_root_tail *)((bh)-&gt;b_data+(sb)-&gt;s_blocksize-sizeof(struct affs_root_tail)))
DECL|macro|AFFS_DATA_HEAD
mdefine_line|#define AFFS_DATA_HEAD(bh)&t;((struct affs_data_head *)(bh)-&gt;b_data)
DECL|macro|AFFS_DATA
mdefine_line|#define AFFS_DATA(bh)&t;&t;(((struct affs_data_head *)(bh)-&gt;b_data)-&gt;data)
DECL|macro|AFFS_CACHE_SIZE
mdefine_line|#define AFFS_CACHE_SIZE&t;&t;PAGE_SIZE
DECL|macro|AFFS_MAX_PREALLOC
mdefine_line|#define AFFS_MAX_PREALLOC&t;32
DECL|macro|AFFS_LC_SIZE
mdefine_line|#define AFFS_LC_SIZE&t;&t;(AFFS_CACHE_SIZE/sizeof(u32)/2)
DECL|macro|AFFS_AC_SIZE
mdefine_line|#define AFFS_AC_SIZE&t;&t;(AFFS_CACHE_SIZE/sizeof(struct affs_ext_key)/2)
DECL|macro|AFFS_AC_MASK
mdefine_line|#define AFFS_AC_MASK&t;&t;(AFFS_AC_SIZE-1)
DECL|struct|affs_ext_key
r_struct
id|affs_ext_key
(brace
DECL|member|ext
id|u32
id|ext
suffix:semicolon
multiline_comment|/* idx of the extended block */
DECL|member|key
id|u32
id|key
suffix:semicolon
multiline_comment|/* block number */
)brace
suffix:semicolon
multiline_comment|/*&n; * affs fs inode data in memory&n; */
DECL|struct|affs_inode_info
r_struct
id|affs_inode_info
(brace
DECL|member|i_opencnt
id|u32
id|i_opencnt
suffix:semicolon
DECL|member|i_link_lock
r_struct
id|semaphore
id|i_link_lock
suffix:semicolon
multiline_comment|/* Protects internal inode access. */
DECL|member|i_ext_lock
r_struct
id|semaphore
id|i_ext_lock
suffix:semicolon
multiline_comment|/* Protects internal inode access. */
DECL|macro|i_hash_lock
mdefine_line|#define i_hash_lock i_ext_lock
DECL|member|i_blkcnt
id|u32
id|i_blkcnt
suffix:semicolon
multiline_comment|/* block count */
DECL|member|i_extcnt
id|u32
id|i_extcnt
suffix:semicolon
multiline_comment|/* extended block count */
DECL|member|i_lc
id|u32
op_star
id|i_lc
suffix:semicolon
multiline_comment|/* linear cache of extended blocks */
DECL|member|i_lc_size
id|u32
id|i_lc_size
suffix:semicolon
DECL|member|i_lc_shift
id|u32
id|i_lc_shift
suffix:semicolon
DECL|member|i_lc_mask
id|u32
id|i_lc_mask
suffix:semicolon
DECL|member|i_ac
r_struct
id|affs_ext_key
op_star
id|i_ac
suffix:semicolon
multiline_comment|/* associative cache of extended blocks */
DECL|member|i_ext_last
id|u32
id|i_ext_last
suffix:semicolon
multiline_comment|/* last accessed extended block */
DECL|member|i_ext_bh
r_struct
id|buffer_head
op_star
id|i_ext_bh
suffix:semicolon
multiline_comment|/* bh of last extended block */
DECL|member|mmu_private
id|loff_t
id|mmu_private
suffix:semicolon
DECL|member|i_protect
id|u32
id|i_protect
suffix:semicolon
multiline_comment|/* unused attribute bits */
DECL|member|i_lastalloc
id|u32
id|i_lastalloc
suffix:semicolon
multiline_comment|/* last allocated block */
DECL|member|i_pa_cnt
r_int
id|i_pa_cnt
suffix:semicolon
multiline_comment|/* number of preallocated blocks */
DECL|member|vfs_inode
r_struct
id|inode
id|vfs_inode
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* short cut to get to the affs specific inode data */
DECL|function|AFFS_I
r_static
r_inline
r_struct
id|affs_inode_info
op_star
id|AFFS_I
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
id|affs_inode_info
comma
id|vfs_inode
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * super-block data in memory&n; *&n; * Block numbers are adjusted for their actual size&n; *&n; */
DECL|struct|affs_bm_info
r_struct
id|affs_bm_info
(brace
DECL|member|bm_key
id|u32
id|bm_key
suffix:semicolon
multiline_comment|/* Disk block number */
DECL|member|bm_free
id|u32
id|bm_free
suffix:semicolon
multiline_comment|/* Free blocks in here */
)brace
suffix:semicolon
DECL|struct|affs_sb_info
r_struct
id|affs_sb_info
(brace
DECL|member|s_partition_size
r_int
id|s_partition_size
suffix:semicolon
multiline_comment|/* Partition size in blocks. */
DECL|member|s_reserved
r_int
id|s_reserved
suffix:semicolon
multiline_comment|/* Number of reserved blocks. */
singleline_comment|//u32 s_blksize;&t;&t;&t;/* Initial device blksize */
DECL|member|s_data_blksize
id|u32
id|s_data_blksize
suffix:semicolon
multiline_comment|/* size of the data block w/o header */
DECL|member|s_root_block
id|u32
id|s_root_block
suffix:semicolon
multiline_comment|/* FFS root block number. */
DECL|member|s_hashsize
r_int
id|s_hashsize
suffix:semicolon
multiline_comment|/* Size of hash table. */
DECL|member|s_flags
r_int
r_int
id|s_flags
suffix:semicolon
multiline_comment|/* See below. */
DECL|member|s_uid
id|uid_t
id|s_uid
suffix:semicolon
multiline_comment|/* uid to override */
DECL|member|s_gid
id|gid_t
id|s_gid
suffix:semicolon
multiline_comment|/* gid to override */
DECL|member|s_mode
id|umode_t
id|s_mode
suffix:semicolon
multiline_comment|/* mode to override */
DECL|member|s_root_bh
r_struct
id|buffer_head
op_star
id|s_root_bh
suffix:semicolon
multiline_comment|/* Cached root block. */
DECL|member|s_bmlock
r_struct
id|semaphore
id|s_bmlock
suffix:semicolon
multiline_comment|/* Protects bitmap access. */
DECL|member|s_bitmap
r_struct
id|affs_bm_info
op_star
id|s_bitmap
suffix:semicolon
multiline_comment|/* Bitmap infos. */
DECL|member|s_bmap_count
id|u32
id|s_bmap_count
suffix:semicolon
multiline_comment|/* # of bitmap blocks. */
DECL|member|s_bmap_bits
id|u32
id|s_bmap_bits
suffix:semicolon
multiline_comment|/* # of bits in one bitmap blocks */
DECL|member|s_last_bmap
id|u32
id|s_last_bmap
suffix:semicolon
DECL|member|s_bmap_bh
r_struct
id|buffer_head
op_star
id|s_bmap_bh
suffix:semicolon
DECL|member|s_prefix
r_char
op_star
id|s_prefix
suffix:semicolon
multiline_comment|/* Prefix for volumes and assigns. */
DECL|member|s_prefix_len
r_int
id|s_prefix_len
suffix:semicolon
multiline_comment|/* Length of prefix. */
DECL|member|s_volume
r_char
id|s_volume
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* Volume prefix for absolute symlinks. */
)brace
suffix:semicolon
DECL|macro|SF_INTL
mdefine_line|#define SF_INTL&t;&t;0x0001&t;&t;/* International filesystem. */
DECL|macro|SF_BM_VALID
mdefine_line|#define SF_BM_VALID&t;0x0002&t;&t;/* Bitmap is valid. */
DECL|macro|SF_IMMUTABLE
mdefine_line|#define SF_IMMUTABLE&t;0x0004&t;&t;/* Protection bits cannot be changed */
DECL|macro|SF_QUIET
mdefine_line|#define SF_QUIET&t;0x0008&t;&t;/* chmod errors will be not reported */
DECL|macro|SF_SETUID
mdefine_line|#define SF_SETUID&t;0x0010&t;&t;/* Ignore Amiga uid */
DECL|macro|SF_SETGID
mdefine_line|#define SF_SETGID&t;0x0020&t;&t;/* Ignore Amiga gid */
DECL|macro|SF_SETMODE
mdefine_line|#define SF_SETMODE&t;0x0040&t;&t;/* Ignore Amiga protection bits */
DECL|macro|SF_MUFS
mdefine_line|#define SF_MUFS&t;&t;0x0100&t;&t;/* Use MUFS uid/gid mapping */
DECL|macro|SF_OFS
mdefine_line|#define SF_OFS&t;&t;0x0200&t;&t;/* Old filesystem */
DECL|macro|SF_PREFIX
mdefine_line|#define SF_PREFIX&t;0x0400&t;&t;/* Buffer for prefix is allocated */
DECL|macro|SF_VERBOSE
mdefine_line|#define SF_VERBOSE&t;0x0800&t;&t;/* Talk about fs when mounting */
multiline_comment|/* short cut to get to the affs specific sb data */
DECL|function|AFFS_SB
r_static
r_inline
r_struct
id|affs_sb_info
op_star
id|AFFS_SB
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
multiline_comment|/* amigaffs.c */
r_extern
r_int
id|affs_insert_hash
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|buffer_head
op_star
id|bh
)paren
suffix:semicolon
r_extern
r_int
id|affs_remove_hash
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|buffer_head
op_star
id|rem_bh
)paren
suffix:semicolon
r_extern
r_int
id|affs_remove_header
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
)paren
suffix:semicolon
r_extern
id|u32
id|affs_checksum_block
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|buffer_head
op_star
id|bh
)paren
suffix:semicolon
r_extern
r_void
id|affs_fix_checksum
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|buffer_head
op_star
id|bh
)paren
suffix:semicolon
r_extern
r_void
id|secs_to_datestamp
c_func
(paren
id|time_t
id|secs
comma
r_struct
id|affs_date
op_star
id|ds
)paren
suffix:semicolon
r_extern
id|mode_t
id|prot_to_mode
c_func
(paren
id|u32
id|prot
)paren
suffix:semicolon
r_extern
r_void
id|mode_to_prot
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
suffix:semicolon
r_extern
r_void
id|affs_error
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_const
r_char
op_star
id|function
comma
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
suffix:semicolon
r_extern
r_void
id|affs_warning
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_const
r_char
op_star
id|function
comma
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
suffix:semicolon
r_extern
r_int
id|affs_check_name
c_func
(paren
r_const
r_int
r_char
op_star
id|name
comma
r_int
id|len
)paren
suffix:semicolon
r_extern
r_int
id|affs_copy_name
c_func
(paren
r_int
r_char
op_star
id|bstr
comma
r_struct
id|dentry
op_star
id|dentry
)paren
suffix:semicolon
multiline_comment|/* bitmap. c */
r_extern
id|u32
id|affs_count_free_blocks
c_func
(paren
r_struct
id|super_block
op_star
id|s
)paren
suffix:semicolon
r_extern
r_void
id|affs_free_block
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
id|u32
id|block
)paren
suffix:semicolon
r_extern
id|u32
id|affs_alloc_block
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
id|u32
id|goal
)paren
suffix:semicolon
r_extern
r_int
id|affs_init_bitmap
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
op_star
id|flags
)paren
suffix:semicolon
r_extern
r_void
id|affs_free_bitmap
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
suffix:semicolon
multiline_comment|/* namei.c */
r_extern
r_int
id|affs_hash_name
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_const
id|u8
op_star
id|name
comma
r_int
r_int
id|len
)paren
suffix:semicolon
r_extern
r_struct
id|dentry
op_star
id|affs_lookup
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|dentry
op_star
id|dentry
comma
r_struct
id|nameidata
op_star
)paren
suffix:semicolon
r_extern
r_int
id|affs_unlink
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|dentry
op_star
id|dentry
)paren
suffix:semicolon
r_extern
r_int
id|affs_create
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|dentry
op_star
id|dentry
comma
r_int
id|mode
comma
r_struct
id|nameidata
op_star
)paren
suffix:semicolon
r_extern
r_int
id|affs_mkdir
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|dentry
op_star
id|dentry
comma
r_int
id|mode
)paren
suffix:semicolon
r_extern
r_int
id|affs_rmdir
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|dentry
op_star
id|dentry
)paren
suffix:semicolon
r_extern
r_int
id|affs_link
c_func
(paren
r_struct
id|dentry
op_star
id|olddentry
comma
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|dentry
op_star
id|dentry
)paren
suffix:semicolon
r_extern
r_int
id|affs_symlink
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|dentry
op_star
id|dentry
comma
r_const
r_char
op_star
id|symname
)paren
suffix:semicolon
r_extern
r_int
id|affs_rename
c_func
(paren
r_struct
id|inode
op_star
id|old_dir
comma
r_struct
id|dentry
op_star
id|old_dentry
comma
r_struct
id|inode
op_star
id|new_dir
comma
r_struct
id|dentry
op_star
id|new_dentry
)paren
suffix:semicolon
multiline_comment|/* inode.c */
r_extern
r_int
r_int
id|affs_parent_ino
c_func
(paren
r_struct
id|inode
op_star
id|dir
)paren
suffix:semicolon
r_extern
r_struct
id|inode
op_star
id|affs_new_inode
c_func
(paren
r_struct
id|inode
op_star
id|dir
)paren
suffix:semicolon
r_extern
r_int
id|affs_notify_change
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_struct
id|iattr
op_star
id|attr
)paren
suffix:semicolon
r_extern
r_void
id|affs_put_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
suffix:semicolon
r_extern
r_void
id|affs_delete_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
suffix:semicolon
r_extern
r_void
id|affs_clear_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
suffix:semicolon
r_extern
r_void
id|affs_read_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
suffix:semicolon
r_extern
r_int
id|affs_write_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|affs_add_entry
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|dentry
op_star
id|dentry
comma
id|s32
id|type
)paren
suffix:semicolon
multiline_comment|/* file.c */
r_void
id|affs_free_prealloc
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
suffix:semicolon
r_extern
r_void
id|affs_truncate
c_func
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
multiline_comment|/* dir.c */
r_extern
r_void
id|affs_dir_truncate
c_func
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
multiline_comment|/* jump tables */
r_extern
r_struct
id|inode_operations
id|affs_file_inode_operations
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|affs_dir_inode_operations
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|affs_symlink_inode_operations
suffix:semicolon
r_extern
r_struct
id|file_operations
id|affs_file_operations
suffix:semicolon
r_extern
r_struct
id|file_operations
id|affs_file_operations_ofs
suffix:semicolon
r_extern
r_struct
id|file_operations
id|affs_dir_operations
suffix:semicolon
r_extern
r_struct
id|address_space_operations
id|affs_symlink_aops
suffix:semicolon
r_extern
r_struct
id|address_space_operations
id|affs_aops
suffix:semicolon
r_extern
r_struct
id|address_space_operations
id|affs_aops_ofs
suffix:semicolon
r_extern
r_struct
id|dentry_operations
id|affs_dentry_operations
suffix:semicolon
r_extern
r_struct
id|dentry_operations
id|affs_dentry_operations_intl
suffix:semicolon
r_static
r_inline
r_void
DECL|function|affs_set_blocksize
id|affs_set_blocksize
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
id|size
)paren
(brace
id|sb_set_blocksize
c_func
(paren
id|sb
comma
id|size
)paren
suffix:semicolon
)brace
r_static
r_inline
r_struct
id|buffer_head
op_star
DECL|function|affs_bread
id|affs_bread
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
id|block
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;affs_bread: %d&bslash;n&quot;
comma
id|block
)paren
suffix:semicolon
r_if
c_cond
(paren
id|block
op_ge
id|AFFS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|s_reserved
op_logical_and
id|block
OL
id|AFFS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|s_partition_size
)paren
r_return
id|sb_bread
c_func
(paren
id|sb
comma
id|block
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_static
r_inline
r_struct
id|buffer_head
op_star
DECL|function|affs_getblk
id|affs_getblk
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
id|block
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;affs_getblk: %d&bslash;n&quot;
comma
id|block
)paren
suffix:semicolon
r_if
c_cond
(paren
id|block
op_ge
id|AFFS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|s_reserved
op_logical_and
id|block
OL
id|AFFS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|s_partition_size
)paren
r_return
id|sb_getblk
c_func
(paren
id|sb
comma
id|block
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_static
r_inline
r_struct
id|buffer_head
op_star
DECL|function|affs_getzeroblk
id|affs_getzeroblk
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
id|block
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;affs_getzeroblk: %d&bslash;n&quot;
comma
id|block
)paren
suffix:semicolon
r_if
c_cond
(paren
id|block
op_ge
id|AFFS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|s_reserved
op_logical_and
id|block
OL
id|AFFS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|s_partition_size
)paren
(brace
id|bh
op_assign
id|sb_getblk
c_func
(paren
id|sb
comma
id|block
)paren
suffix:semicolon
id|lock_buffer
c_func
(paren
id|bh
)paren
suffix:semicolon
id|memset
c_func
(paren
id|bh-&gt;b_data
comma
l_int|0
comma
id|sb-&gt;s_blocksize
)paren
suffix:semicolon
id|set_buffer_uptodate
c_func
(paren
id|bh
)paren
suffix:semicolon
id|unlock_buffer
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
id|bh
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
r_static
r_inline
r_struct
id|buffer_head
op_star
DECL|function|affs_getemptyblk
id|affs_getemptyblk
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
id|block
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;affs_getemptyblk: %d&bslash;n&quot;
comma
id|block
)paren
suffix:semicolon
r_if
c_cond
(paren
id|block
op_ge
id|AFFS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|s_reserved
op_logical_and
id|block
OL
id|AFFS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|s_partition_size
)paren
(brace
id|bh
op_assign
id|sb_getblk
c_func
(paren
id|sb
comma
id|block
)paren
suffix:semicolon
id|wait_on_buffer
c_func
(paren
id|bh
)paren
suffix:semicolon
id|set_buffer_uptodate
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
id|bh
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|affs_brelse
id|affs_brelse
c_func
(paren
r_struct
id|buffer_head
op_star
id|bh
)paren
(brace
r_if
c_cond
(paren
id|bh
)paren
id|pr_debug
c_func
(paren
l_string|&quot;affs_brelse: %lld&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|bh-&gt;b_blocknr
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|affs_adjust_checksum
id|affs_adjust_checksum
c_func
(paren
r_struct
id|buffer_head
op_star
id|bh
comma
id|u32
id|val
)paren
(brace
id|u32
id|tmp
op_assign
id|be32_to_cpu
c_func
(paren
(paren
(paren
id|__be32
op_star
)paren
id|bh-&gt;b_data
)paren
(braket
l_int|5
)braket
)paren
suffix:semicolon
(paren
(paren
id|__be32
op_star
)paren
id|bh-&gt;b_data
)paren
(braket
l_int|5
)braket
op_assign
id|cpu_to_be32
c_func
(paren
id|tmp
op_minus
id|val
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|affs_adjust_bitmapchecksum
id|affs_adjust_bitmapchecksum
c_func
(paren
r_struct
id|buffer_head
op_star
id|bh
comma
id|u32
id|val
)paren
(brace
id|u32
id|tmp
op_assign
id|be32_to_cpu
c_func
(paren
(paren
(paren
id|__be32
op_star
)paren
id|bh-&gt;b_data
)paren
(braket
l_int|0
)braket
)paren
suffix:semicolon
(paren
(paren
id|__be32
op_star
)paren
id|bh-&gt;b_data
)paren
(braket
l_int|0
)braket
op_assign
id|cpu_to_be32
c_func
(paren
id|tmp
op_minus
id|val
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|affs_lock_link
id|affs_lock_link
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
id|down
c_func
(paren
op_amp
id|AFFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_link_lock
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|affs_unlock_link
id|affs_unlock_link
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
id|up
c_func
(paren
op_amp
id|AFFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_link_lock
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|affs_lock_dir
id|affs_lock_dir
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
id|down
c_func
(paren
op_amp
id|AFFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_hash_lock
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|affs_unlock_dir
id|affs_unlock_dir
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
id|up
c_func
(paren
op_amp
id|AFFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_hash_lock
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|affs_lock_ext
id|affs_lock_ext
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
id|down
c_func
(paren
op_amp
id|AFFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_ext_lock
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|affs_unlock_ext
id|affs_unlock_ext
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
id|up
c_func
(paren
op_amp
id|AFFS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_ext_lock
)paren
suffix:semicolon
)brace
eof
