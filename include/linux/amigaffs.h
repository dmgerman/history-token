macro_line|#ifndef AMIGAFFS_H
DECL|macro|AMIGAFFS_H
mdefine_line|#define AMIGAFFS_H
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/locks.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
multiline_comment|/* AmigaOS allows file names with up to 30 characters length.&n; * Names longer than that will be silently truncated. If you&n; * want to disallow this, comment out the following #define.&n; * Creating filesystem objects with longer names will then&n; * result in an error (ENAMETOOLONG).&n; */
multiline_comment|/*#define AFFS_NO_TRUNCATE */
multiline_comment|/* Ugly macros make the code more pretty. */
DECL|macro|GET_END_PTR
mdefine_line|#define GET_END_PTR(st,p,sz)&t;&t; ((st *)((char *)(p)+((sz)-sizeof(st))))
DECL|macro|AFFS_GET_HASHENTRY
mdefine_line|#define AFFS_GET_HASHENTRY(data,hashkey) be32_to_cpu(((struct dir_front *)data)-&gt;hashtable[hashkey])
DECL|macro|AFFS_BLOCK
mdefine_line|#define AFFS_BLOCK(sb, bh, blk)&t;&t;(AFFS_HEAD(bh)-&gt;table[(sb)-&gt;u.affs_sb.s_hashsize-1-(blk)])
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
id|set_blocksize
c_func
(paren
id|sb-&gt;s_dev
comma
id|size
)paren
suffix:semicolon
id|sb-&gt;s_blocksize
op_assign
id|size
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
id|KERN_DEBUG
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
id|AFFS_SB-&gt;s_reserved
op_logical_and
id|block
OL
id|AFFS_SB-&gt;s_partition_size
)paren
r_return
id|bread
c_func
(paren
id|sb-&gt;s_dev
comma
id|block
comma
id|sb-&gt;s_blocksize
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
id|KERN_DEBUG
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
id|AFFS_SB-&gt;s_reserved
op_logical_and
id|block
OL
id|AFFS_SB-&gt;s_partition_size
)paren
r_return
id|getblk
c_func
(paren
id|sb-&gt;s_dev
comma
id|block
comma
id|sb-&gt;s_blocksize
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
id|KERN_DEBUG
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
id|AFFS_SB-&gt;s_reserved
op_logical_and
id|block
OL
id|AFFS_SB-&gt;s_partition_size
)paren
(brace
id|bh
op_assign
id|getblk
c_func
(paren
id|sb-&gt;s_dev
comma
id|block
comma
id|sb-&gt;s_blocksize
)paren
suffix:semicolon
id|wait_on_buffer
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
id|mark_buffer_uptodate
c_func
(paren
id|bh
comma
l_int|1
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
id|KERN_DEBUG
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
id|AFFS_SB-&gt;s_reserved
op_logical_and
id|block
OL
id|AFFS_SB-&gt;s_partition_size
)paren
(brace
id|bh
op_assign
id|getblk
c_func
(paren
id|sb-&gt;s_dev
comma
id|block
comma
id|sb-&gt;s_blocksize
)paren
suffix:semicolon
id|wait_on_buffer
c_func
(paren
id|bh
)paren
suffix:semicolon
id|mark_buffer_uptodate
c_func
(paren
id|bh
comma
l_int|1
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
id|KERN_DEBUG
l_string|&quot;affs_brelse: %ld&bslash;n&quot;
comma
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
id|u32
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
id|u32
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
id|u32
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
id|u32
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
id|AFFS_INODE-&gt;i_link_lock
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
id|AFFS_INODE-&gt;i_link_lock
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
id|AFFS_INODE-&gt;i_hash_lock
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
id|AFFS_INODE-&gt;i_hash_lock
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
id|AFFS_INODE-&gt;i_ext_lock
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
id|AFFS_INODE-&gt;i_ext_lock
)paren
suffix:semicolon
)brace
DECL|macro|MIN
mdefine_line|#define MIN(a, b) ({&t;&t;&bslash;&n;&t;typeof(a) _a = (a);&t;&bslash;&n;&t;typeof(b) _b = (b);&t;&bslash;&n;&t;_a &lt; _b ? _a : _b;&t;&bslash;&n;})&t;
macro_line|#ifdef __LITTLE_ENDIAN
DECL|macro|BO_EXBITS
mdefine_line|#define BO_EXBITS&t;0x18UL
macro_line|#elif defined(__BIG_ENDIAN)
DECL|macro|BO_EXBITS
mdefine_line|#define BO_EXBITS&t;0x00UL
macro_line|#else
macro_line|#error Endianness must be known for affs to work.
macro_line|#endif
DECL|macro|FS_OFS
mdefine_line|#define FS_OFS&t;&t;0x444F5300
DECL|macro|FS_FFS
mdefine_line|#define FS_FFS&t;&t;0x444F5301
DECL|macro|FS_INTLOFS
mdefine_line|#define FS_INTLOFS&t;0x444F5302
DECL|macro|FS_INTLFFS
mdefine_line|#define FS_INTLFFS&t;0x444F5303
DECL|macro|FS_DCOFS
mdefine_line|#define FS_DCOFS&t;0x444F5304
DECL|macro|FS_DCFFS
mdefine_line|#define FS_DCFFS&t;0x444F5305
DECL|macro|MUFS_FS
mdefine_line|#define MUFS_FS&t;&t;0x6d754653   /* &squot;muFS&squot; */
DECL|macro|MUFS_OFS
mdefine_line|#define MUFS_OFS&t;0x6d754600   /* &squot;muF&bslash;0&squot; */
DECL|macro|MUFS_FFS
mdefine_line|#define MUFS_FFS&t;0x6d754601   /* &squot;muF&bslash;1&squot; */
DECL|macro|MUFS_INTLOFS
mdefine_line|#define MUFS_INTLOFS&t;0x6d754602   /* &squot;muF&bslash;2&squot; */
DECL|macro|MUFS_INTLFFS
mdefine_line|#define MUFS_INTLFFS&t;0x6d754603   /* &squot;muF&bslash;3&squot; */
DECL|macro|MUFS_DCOFS
mdefine_line|#define MUFS_DCOFS&t;0x6d754604   /* &squot;muF&bslash;4&squot; */
DECL|macro|MUFS_DCFFS
mdefine_line|#define MUFS_DCFFS&t;0x6d754605   /* &squot;muF&bslash;5&squot; */
DECL|macro|T_SHORT
mdefine_line|#define T_SHORT&t;&t;2
DECL|macro|T_LIST
mdefine_line|#define T_LIST&t;&t;16
DECL|macro|T_DATA
mdefine_line|#define T_DATA&t;&t;8
DECL|macro|ST_LINKFILE
mdefine_line|#define ST_LINKFILE&t;-4
DECL|macro|ST_FILE
mdefine_line|#define ST_FILE&t;&t;-3
DECL|macro|ST_ROOT
mdefine_line|#define ST_ROOT&t;&t;1
DECL|macro|ST_USERDIR
mdefine_line|#define ST_USERDIR&t;2
DECL|macro|ST_SOFTLINK
mdefine_line|#define ST_SOFTLINK&t;3
DECL|macro|ST_LINKDIR
mdefine_line|#define ST_LINKDIR&t;4
DECL|macro|AFFS_ROOT_BMAPS
mdefine_line|#define AFFS_ROOT_BMAPS&t;&t;25
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
DECL|struct|affs_date
r_struct
id|affs_date
(brace
DECL|member|days
id|u32
id|days
suffix:semicolon
DECL|member|mins
id|u32
id|mins
suffix:semicolon
DECL|member|ticks
id|u32
id|ticks
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|affs_short_date
r_struct
id|affs_short_date
(brace
DECL|member|days
id|u16
id|days
suffix:semicolon
DECL|member|mins
id|u16
id|mins
suffix:semicolon
DECL|member|ticks
id|u16
id|ticks
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|affs_root_head
r_struct
id|affs_root_head
(brace
DECL|member|ptype
id|u32
id|ptype
suffix:semicolon
DECL|member|spare1
id|u32
id|spare1
suffix:semicolon
DECL|member|spare2
id|u32
id|spare2
suffix:semicolon
DECL|member|hash_size
id|u32
id|hash_size
suffix:semicolon
DECL|member|spare3
id|u32
id|spare3
suffix:semicolon
DECL|member|checksum
id|u32
id|checksum
suffix:semicolon
DECL|member|hashtable
id|u32
id|hashtable
(braket
l_int|1
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|affs_root_tail
r_struct
id|affs_root_tail
(brace
DECL|member|bm_flag
id|u32
id|bm_flag
suffix:semicolon
DECL|member|bm_blk
id|u32
id|bm_blk
(braket
id|AFFS_ROOT_BMAPS
)braket
suffix:semicolon
DECL|member|bm_ext
id|u32
id|bm_ext
suffix:semicolon
DECL|member|root_change
r_struct
id|affs_date
id|root_change
suffix:semicolon
DECL|member|disk_name
id|u8
id|disk_name
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|spare1
id|u32
id|spare1
suffix:semicolon
DECL|member|spare2
id|u32
id|spare2
suffix:semicolon
DECL|member|disk_change
r_struct
id|affs_date
id|disk_change
suffix:semicolon
DECL|member|disk_create
r_struct
id|affs_date
id|disk_create
suffix:semicolon
DECL|member|spare3
id|u32
id|spare3
suffix:semicolon
DECL|member|spare4
id|u32
id|spare4
suffix:semicolon
DECL|member|dcache
id|u32
id|dcache
suffix:semicolon
DECL|member|stype
id|u32
id|stype
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|affs_head
r_struct
id|affs_head
(brace
DECL|member|ptype
id|u32
id|ptype
suffix:semicolon
DECL|member|key
id|u32
id|key
suffix:semicolon
DECL|member|block_count
id|u32
id|block_count
suffix:semicolon
DECL|member|spare1
id|u32
id|spare1
suffix:semicolon
DECL|member|first_data
id|u32
id|first_data
suffix:semicolon
DECL|member|checksum
id|u32
id|checksum
suffix:semicolon
DECL|member|table
id|u32
id|table
(braket
l_int|1
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|affs_tail
r_struct
id|affs_tail
(brace
DECL|member|spare1
id|u32
id|spare1
suffix:semicolon
DECL|member|uid
id|u16
id|uid
suffix:semicolon
DECL|member|gid
id|u16
id|gid
suffix:semicolon
DECL|member|protect
id|u32
id|protect
suffix:semicolon
DECL|member|size
id|u32
id|size
suffix:semicolon
DECL|member|comment
id|u8
id|comment
(braket
l_int|92
)braket
suffix:semicolon
DECL|member|change
r_struct
id|affs_date
id|change
suffix:semicolon
DECL|member|name
id|u8
id|name
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|spare2
id|u32
id|spare2
suffix:semicolon
DECL|member|original
id|u32
id|original
suffix:semicolon
DECL|member|link_chain
id|u32
id|link_chain
suffix:semicolon
DECL|member|spare
id|u32
id|spare
(braket
l_int|5
)braket
suffix:semicolon
DECL|member|hash_chain
id|u32
id|hash_chain
suffix:semicolon
DECL|member|parent
id|u32
id|parent
suffix:semicolon
DECL|member|extension
id|u32
id|extension
suffix:semicolon
DECL|member|stype
id|u32
id|stype
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|slink_front
r_struct
id|slink_front
(brace
DECL|member|ptype
id|u32
id|ptype
suffix:semicolon
DECL|member|key
id|u32
id|key
suffix:semicolon
DECL|member|spare1
id|u32
id|spare1
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|checksum
id|u32
id|checksum
suffix:semicolon
DECL|member|symname
id|u8
id|symname
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* depends on block size */
)brace
suffix:semicolon
DECL|struct|affs_data_head
r_struct
id|affs_data_head
(brace
DECL|member|ptype
id|u32
id|ptype
suffix:semicolon
DECL|member|key
id|u32
id|key
suffix:semicolon
DECL|member|sequence
id|u32
id|sequence
suffix:semicolon
DECL|member|size
id|u32
id|size
suffix:semicolon
DECL|member|next
id|u32
id|next
suffix:semicolon
DECL|member|checksum
id|u32
id|checksum
suffix:semicolon
DECL|member|data
id|u8
id|data
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* depends on block size */
)brace
suffix:semicolon
multiline_comment|/* Permission bits */
DECL|macro|FIBF_OTR_READ
mdefine_line|#define FIBF_OTR_READ&t;&t;0x8000
DECL|macro|FIBF_OTR_WRITE
mdefine_line|#define FIBF_OTR_WRITE&t;&t;0x4000
DECL|macro|FIBF_OTR_EXECUTE
mdefine_line|#define FIBF_OTR_EXECUTE&t;0x2000
DECL|macro|FIBF_OTR_DELETE
mdefine_line|#define FIBF_OTR_DELETE&t;&t;0x1000
DECL|macro|FIBF_GRP_READ
mdefine_line|#define FIBF_GRP_READ&t;&t;0x0800
DECL|macro|FIBF_GRP_WRITE
mdefine_line|#define FIBF_GRP_WRITE&t;&t;0x0400
DECL|macro|FIBF_GRP_EXECUTE
mdefine_line|#define FIBF_GRP_EXECUTE&t;0x0200
DECL|macro|FIBF_GRP_DELETE
mdefine_line|#define FIBF_GRP_DELETE&t;&t;0x0100
DECL|macro|FIBF_HIDDEN
mdefine_line|#define FIBF_HIDDEN&t;&t;0x0080
DECL|macro|FIBF_SCRIPT
mdefine_line|#define FIBF_SCRIPT&t;&t;0x0040
DECL|macro|FIBF_PURE
mdefine_line|#define FIBF_PURE&t;&t;0x0020&t;&t;/* no use under linux */
DECL|macro|FIBF_ARCHIVED
mdefine_line|#define FIBF_ARCHIVED&t;&t;0x0010&t;&t;/* never set, always cleared on write */
DECL|macro|FIBF_NOREAD
mdefine_line|#define FIBF_NOREAD&t;&t;0x0008&t;&t;/* 0 means allowed */
DECL|macro|FIBF_NOWRITE
mdefine_line|#define FIBF_NOWRITE&t;&t;0x0004&t;&t;/* 0 means allowed */
DECL|macro|FIBF_NOEXECUTE
mdefine_line|#define FIBF_NOEXECUTE&t;&t;0x0002&t;&t;/* 0 means allowed, ignored under linux */
DECL|macro|FIBF_NODELETE
mdefine_line|#define FIBF_NODELETE&t;&t;0x0001&t;&t;/* 0 means allowed */
DECL|macro|FIBF_OWNER
mdefine_line|#define FIBF_OWNER&t;&t;0x000F&t;&t;/* Bits pertaining to owner */
DECL|macro|FIBF_MASK
mdefine_line|#define FIBF_MASK&t;&t;0xEE0E&t;&t;/* Bits modified by Linux */
macro_line|#endif
eof
