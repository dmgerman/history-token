multiline_comment|/*&n; * include/linux/buffer_head.h&n; *&n; * Everything to do with buffer_heads.&n; */
macro_line|#ifndef _LINUX_BUFFER_HEAD_H
DECL|macro|_LINUX_BUFFER_HEAD_H
mdefine_line|#define _LINUX_BUFFER_HEAD_H
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/linkage.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
DECL|enum|bh_state_bits
r_enum
id|bh_state_bits
(brace
DECL|enumerator|BH_Uptodate
id|BH_Uptodate
comma
multiline_comment|/* Contains valid data */
DECL|enumerator|BH_Dirty
id|BH_Dirty
comma
multiline_comment|/* Is dirty */
DECL|enumerator|BH_Lock
id|BH_Lock
comma
multiline_comment|/* Is locked */
DECL|enumerator|BH_Req
id|BH_Req
comma
multiline_comment|/* Has been submitted for I/O */
DECL|enumerator|BH_Mapped
id|BH_Mapped
comma
multiline_comment|/* Has a disk mapping */
DECL|enumerator|BH_New
id|BH_New
comma
multiline_comment|/* Disk mapping was newly created by get_block */
DECL|enumerator|BH_Async_Read
id|BH_Async_Read
comma
multiline_comment|/* Is under end_buffer_async_read I/O */
DECL|enumerator|BH_Async_Write
id|BH_Async_Write
comma
multiline_comment|/* Is under end_buffer_async_write I/O */
DECL|enumerator|BH_JBD
id|BH_JBD
comma
multiline_comment|/* Has an attached ext3 journal_head */
DECL|enumerator|BH_Boundary
id|BH_Boundary
comma
multiline_comment|/* Block is followed by a discontiguity */
DECL|enumerator|BH_PrivateStart
id|BH_PrivateStart
comma
multiline_comment|/* not a state bit, but the first bit available&n;&t;&t;&t; * for private allocation by other entities&n;&t;&t;&t; */
)brace
suffix:semicolon
DECL|macro|MAX_BUF_PER_PAGE
mdefine_line|#define MAX_BUF_PER_PAGE (PAGE_CACHE_SIZE / 512)
r_struct
id|page
suffix:semicolon
r_struct
id|kiobuf
suffix:semicolon
r_struct
id|buffer_head
suffix:semicolon
r_struct
id|address_space
suffix:semicolon
DECL|typedef|bh_end_io_t
r_typedef
r_void
(paren
id|bh_end_io_t
)paren
(paren
r_struct
id|buffer_head
op_star
id|bh
comma
r_int
id|uptodate
)paren
suffix:semicolon
multiline_comment|/*&n; * Keep related fields in common cachelines.  The most commonly accessed&n; * field (b_state) goes at the start so the compiler does not generate&n; * indexed addressing for it.&n; */
DECL|struct|buffer_head
r_struct
id|buffer_head
(brace
multiline_comment|/* First cache line: */
DECL|member|b_state
r_int
r_int
id|b_state
suffix:semicolon
multiline_comment|/* buffer state bitmap (see above) */
DECL|member|b_count
id|atomic_t
id|b_count
suffix:semicolon
multiline_comment|/* users using this block */
DECL|member|b_this_page
r_struct
id|buffer_head
op_star
id|b_this_page
suffix:semicolon
multiline_comment|/* circular list of page&squot;s buffers */
DECL|member|b_page
r_struct
id|page
op_star
id|b_page
suffix:semicolon
multiline_comment|/* the page this bh is mapped to */
DECL|member|b_blocknr
id|sector_t
id|b_blocknr
suffix:semicolon
multiline_comment|/* block number */
DECL|member|b_size
id|u32
id|b_size
suffix:semicolon
multiline_comment|/* block size */
DECL|member|b_data
r_char
op_star
id|b_data
suffix:semicolon
multiline_comment|/* pointer to data block */
DECL|member|b_bdev
r_struct
id|block_device
op_star
id|b_bdev
suffix:semicolon
DECL|member|b_end_io
id|bh_end_io_t
op_star
id|b_end_io
suffix:semicolon
multiline_comment|/* I/O completion */
DECL|member|b_private
r_void
op_star
id|b_private
suffix:semicolon
multiline_comment|/* reserved for b_end_io */
DECL|member|b_assoc_buffers
r_struct
id|list_head
id|b_assoc_buffers
suffix:semicolon
multiline_comment|/* associated with another mapping */
)brace
suffix:semicolon
multiline_comment|/*&n; * macro tricks to expand the set_buffer_foo(), clear_buffer_foo()&n; * and buffer_foo() functions.&n; */
DECL|macro|BUFFER_FNS
mdefine_line|#define BUFFER_FNS(bit, name)&t;&t;&t;&t;&t;&t;&bslash;&n;static inline void set_buffer_##name(struct buffer_head *bh)&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;set_bit(BH_##bit, &amp;(bh)-&gt;b_state);&t;&t;&t;&t;&bslash;&n;}&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;static inline void clear_buffer_##name(struct buffer_head *bh)&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;clear_bit(BH_##bit, &amp;(bh)-&gt;b_state);&t;&t;&t;&t;&bslash;&n;}&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;static inline int buffer_##name(struct buffer_head *bh)&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;return test_bit(BH_##bit, &amp;(bh)-&gt;b_state);&t;&t;&t;&bslash;&n;}
multiline_comment|/*&n; * test_set_buffer_foo() and test_clear_buffer_foo()&n; */
DECL|macro|TAS_BUFFER_FNS
mdefine_line|#define TAS_BUFFER_FNS(bit, name)&t;&t;&t;&t;&t;&bslash;&n;static inline int test_set_buffer_##name(struct buffer_head *bh)&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;return test_and_set_bit(BH_##bit, &amp;(bh)-&gt;b_state);&t;&t;&bslash;&n;}&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;static inline int test_clear_buffer_##name(struct buffer_head *bh)&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;return test_and_clear_bit(BH_##bit, &amp;(bh)-&gt;b_state);&t;&t;&bslash;&n;}&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;
multiline_comment|/*&n; * Emit the buffer bitops functions.   Note that there are also functions&n; * of the form &quot;mark_buffer_foo()&quot;.  These are higher-level functions which&n; * do something in addition to setting a b_state bit.&n; */
id|BUFFER_FNS
c_func
(paren
id|Uptodate
comma
id|uptodate
)paren
id|BUFFER_FNS
c_func
(paren
id|Dirty
comma
id|dirty
)paren
id|TAS_BUFFER_FNS
c_func
(paren
id|Dirty
comma
id|dirty
)paren
id|BUFFER_FNS
c_func
(paren
id|Lock
comma
id|locked
)paren
id|TAS_BUFFER_FNS
c_func
(paren
id|Lock
comma
id|locked
)paren
id|BUFFER_FNS
c_func
(paren
id|Req
comma
id|req
)paren
id|BUFFER_FNS
c_func
(paren
id|Mapped
comma
id|mapped
)paren
id|BUFFER_FNS
c_func
(paren
id|New
comma
r_new
)paren
id|BUFFER_FNS
c_func
(paren
id|Async_Read
comma
id|async_read
)paren
id|BUFFER_FNS
c_func
(paren
id|Async_Write
comma
id|async_write
)paren
id|BUFFER_FNS
c_func
(paren
id|Boundary
comma
id|boundary
)paren
multiline_comment|/*&n; * FIXME: this is used only by bh_kmap, which is used only by RAID5.&n; * Move all that stuff into raid5.c&n; */
DECL|macro|bh_offset
mdefine_line|#define bh_offset(bh)&t;&t;((unsigned long)(bh)-&gt;b_data &amp; ~PAGE_MASK)
DECL|macro|touch_buffer
mdefine_line|#define touch_buffer(bh)&t;mark_page_accessed(bh-&gt;b_page)
multiline_comment|/* If we *know* page-&gt;private refers to buffer_heads */
DECL|macro|page_buffers
mdefine_line|#define page_buffers(page)&t;&t;&t;&t;&t;&bslash;&n;&t;({&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;if (!PagePrivate(page))&t;&t;&t;&t;&bslash;&n;&t;&t;&t;BUG();&t;&t;&t;&t;&t;&bslash;&n;&t;&t;((struct buffer_head *)(page)-&gt;private);&t;&bslash;&n;&t;})
DECL|macro|page_has_buffers
mdefine_line|#define page_has_buffers(page)&t;PagePrivate(page)
DECL|macro|set_page_buffers
mdefine_line|#define set_page_buffers(page, buffers)&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;SetPagePrivate(page);&t;&t;&t;&t;&bslash;&n;&t;&t;page-&gt;private = (unsigned long)buffers;&t;&t;&bslash;&n;&t;} while (0)
DECL|macro|clear_page_buffers
mdefine_line|#define clear_page_buffers(page)&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;ClearPagePrivate(page);&t;&t;&t;&t;&bslash;&n;&t;&t;page-&gt;private = 0;&t;&t;&t;&t;&bslash;&n;&t;} while (0)
DECL|macro|invalidate_buffers
mdefine_line|#define invalidate_buffers(dev)&t;__invalidate_buffers((dev), 0)
DECL|macro|destroy_buffers
mdefine_line|#define destroy_buffers(dev)&t;__invalidate_buffers((dev), 1)
multiline_comment|/*&n; * Declarations&n; */
r_void
id|FASTCALL
c_func
(paren
id|mark_buffer_dirty
c_func
(paren
r_struct
id|buffer_head
op_star
id|bh
)paren
)paren
suffix:semicolon
r_void
id|init_buffer
c_func
(paren
r_struct
id|buffer_head
op_star
comma
id|bh_end_io_t
op_star
comma
r_void
op_star
)paren
suffix:semicolon
DECL|variable|set_bh_page
r_void
id|set_bh_page
c_func
(paren
r_struct
id|buffer_head
op_star
id|bh
comma
r_struct
id|page
op_star
id|page
comma
r_int
r_int
id|offset
)paren
suffix:semicolon
r_int
id|try_to_free_buffers
c_func
(paren
r_struct
id|page
op_star
)paren
suffix:semicolon
r_void
id|create_empty_buffers
c_func
(paren
r_struct
id|page
op_star
comma
r_int
r_int
comma
r_int
r_int
id|b_state
)paren
suffix:semicolon
r_void
id|end_buffer_io_sync
c_func
(paren
r_struct
id|buffer_head
op_star
id|bh
comma
r_int
id|uptodate
)paren
suffix:semicolon
multiline_comment|/* Things to do with buffers at mapping-&gt;private_list */
r_void
id|buffer_insert_list
c_func
(paren
id|spinlock_t
op_star
id|lock
comma
r_struct
id|buffer_head
op_star
comma
r_struct
id|list_head
op_star
)paren
suffix:semicolon
r_void
id|mark_buffer_dirty_inode
c_func
(paren
r_struct
id|buffer_head
op_star
id|bh
comma
r_struct
id|inode
op_star
id|inode
)paren
suffix:semicolon
r_int
id|write_mapping_buffers
c_func
(paren
r_struct
id|address_space
op_star
id|mapping
)paren
suffix:semicolon
r_int
id|inode_has_buffers
c_func
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_void
id|invalidate_inode_buffers
c_func
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_int
id|fsync_buffers_list
c_func
(paren
id|spinlock_t
op_star
id|lock
comma
r_struct
id|list_head
op_star
)paren
suffix:semicolon
r_int
id|sync_mapping_buffers
c_func
(paren
r_struct
id|address_space
op_star
id|mapping
)paren
suffix:semicolon
r_void
id|mark_buffer_async_read
c_func
(paren
r_struct
id|buffer_head
op_star
id|bh
)paren
suffix:semicolon
r_void
id|mark_buffer_async_write
c_func
(paren
r_struct
id|buffer_head
op_star
id|bh
)paren
suffix:semicolon
r_void
id|invalidate_bdev
c_func
(paren
r_struct
id|block_device
op_star
comma
r_int
)paren
suffix:semicolon
r_void
id|__invalidate_buffers
c_func
(paren
id|kdev_t
id|dev
comma
r_int
)paren
suffix:semicolon
r_int
id|sync_blockdev
c_func
(paren
r_struct
id|block_device
op_star
id|bdev
)paren
suffix:semicolon
r_void
id|__wait_on_buffer
c_func
(paren
r_struct
id|buffer_head
op_star
)paren
suffix:semicolon
r_void
id|sleep_on_buffer
c_func
(paren
r_struct
id|buffer_head
op_star
id|bh
)paren
suffix:semicolon
r_void
id|wake_up_buffer
c_func
(paren
r_struct
id|buffer_head
op_star
id|bh
)paren
suffix:semicolon
r_int
id|fsync_dev
c_func
(paren
id|kdev_t
)paren
suffix:semicolon
r_int
id|fsync_bdev
c_func
(paren
r_struct
id|block_device
op_star
)paren
suffix:semicolon
r_int
id|fsync_super
c_func
(paren
r_struct
id|super_block
op_star
)paren
suffix:semicolon
r_int
id|fsync_no_super
c_func
(paren
r_struct
id|block_device
op_star
)paren
suffix:semicolon
r_struct
id|buffer_head
op_star
id|__get_hash_table
c_func
(paren
r_struct
id|block_device
op_star
comma
id|sector_t
comma
r_int
)paren
suffix:semicolon
r_struct
id|buffer_head
op_star
id|__getblk
c_func
(paren
r_struct
id|block_device
op_star
comma
id|sector_t
comma
r_int
)paren
suffix:semicolon
r_void
id|__brelse
c_func
(paren
r_struct
id|buffer_head
op_star
)paren
suffix:semicolon
r_void
id|__bforget
c_func
(paren
r_struct
id|buffer_head
op_star
)paren
suffix:semicolon
r_struct
id|buffer_head
op_star
id|__bread
c_func
(paren
r_struct
id|block_device
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_void
id|wakeup_bdflush
c_func
(paren
r_void
)paren
suffix:semicolon
r_struct
id|buffer_head
op_star
id|alloc_buffer_head
c_func
(paren
r_int
id|async
)paren
suffix:semicolon
r_void
id|free_buffer_head
c_func
(paren
r_struct
id|buffer_head
op_star
id|bh
)paren
suffix:semicolon
r_int
id|brw_page
c_func
(paren
r_int
comma
r_struct
id|page
op_star
comma
r_struct
id|block_device
op_star
comma
id|sector_t
(braket
)braket
comma
r_int
)paren
suffix:semicolon
r_void
id|FASTCALL
c_func
(paren
id|unlock_buffer
c_func
(paren
r_struct
id|buffer_head
op_star
id|bh
)paren
)paren
suffix:semicolon
multiline_comment|/*&n; * Generic address_space_operations implementations for buffer_head-backed&n; * address_spaces.&n; */
r_int
id|try_to_release_page
c_func
(paren
r_struct
id|page
op_star
id|page
comma
r_int
id|gfp_mask
)paren
suffix:semicolon
r_int
id|block_flushpage
c_func
(paren
r_struct
id|page
op_star
id|page
comma
r_int
r_int
id|offset
)paren
suffix:semicolon
r_int
id|block_symlink
c_func
(paren
r_struct
id|inode
op_star
comma
r_const
r_char
op_star
comma
r_int
)paren
suffix:semicolon
r_int
id|block_write_full_page
c_func
(paren
r_struct
id|page
op_star
comma
id|get_block_t
op_star
)paren
suffix:semicolon
r_int
id|block_read_full_page
c_func
(paren
r_struct
id|page
op_star
comma
id|get_block_t
op_star
)paren
suffix:semicolon
r_int
id|block_prepare_write
c_func
(paren
r_struct
id|page
op_star
comma
r_int
comma
r_int
comma
id|get_block_t
op_star
)paren
suffix:semicolon
r_int
id|cont_prepare_write
c_func
(paren
r_struct
id|page
op_star
comma
r_int
comma
r_int
comma
id|get_block_t
op_star
comma
r_int
r_int
op_star
)paren
suffix:semicolon
r_int
id|generic_cont_expand
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
id|loff_t
id|size
)paren
suffix:semicolon
r_int
id|block_commit_write
c_func
(paren
r_struct
id|page
op_star
id|page
comma
r_int
id|from
comma
r_int
id|to
)paren
suffix:semicolon
r_int
id|block_sync_page
c_func
(paren
r_struct
id|page
op_star
)paren
suffix:semicolon
id|sector_t
id|generic_block_bmap
c_func
(paren
r_struct
id|address_space
op_star
comma
id|sector_t
comma
id|get_block_t
op_star
)paren
suffix:semicolon
r_int
id|generic_commit_write
c_func
(paren
r_struct
id|file
op_star
comma
r_struct
id|page
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_int
id|block_truncate_page
c_func
(paren
r_struct
id|address_space
op_star
comma
id|loff_t
comma
id|get_block_t
op_star
)paren
suffix:semicolon
r_int
id|generic_direct_IO
c_func
(paren
r_int
comma
r_struct
id|inode
op_star
comma
r_struct
id|kiobuf
op_star
comma
r_int
r_int
comma
r_int
comma
id|get_block_t
op_star
)paren
suffix:semicolon
r_int
id|file_fsync
c_func
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
DECL|macro|OSYNC_METADATA
mdefine_line|#define OSYNC_METADATA&t;(1&lt;&lt;0)
DECL|macro|OSYNC_DATA
mdefine_line|#define OSYNC_DATA&t;(1&lt;&lt;1)
DECL|macro|OSYNC_INODE
mdefine_line|#define OSYNC_INODE&t;(1&lt;&lt;2)
r_int
id|generic_osync_inode
c_func
(paren
r_struct
id|inode
op_star
comma
r_int
)paren
suffix:semicolon
multiline_comment|/*&n; * inline definitions&n; */
DECL|function|get_bh
r_static
r_inline
r_void
id|get_bh
c_func
(paren
r_struct
id|buffer_head
op_star
id|bh
)paren
(brace
id|atomic_inc
c_func
(paren
op_amp
(paren
id|bh
)paren
op_member_access_from_pointer
id|b_count
)paren
suffix:semicolon
)brace
DECL|function|put_bh
r_static
r_inline
r_void
id|put_bh
c_func
(paren
r_struct
id|buffer_head
op_star
id|bh
)paren
(brace
id|smp_mb__before_atomic_dec
c_func
(paren
)paren
suffix:semicolon
id|atomic_dec
c_func
(paren
op_amp
id|bh-&gt;b_count
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * If an error happens during the make_request, this function&n; * has to be recalled. It marks the buffer as clean and not&n; * uptodate, and it notifys the upper layer about the end&n; * of the I/O.&n; */
DECL|function|buffer_IO_error
r_static
r_inline
r_void
id|buffer_IO_error
c_func
(paren
r_struct
id|buffer_head
op_star
id|bh
)paren
(brace
id|clear_buffer_dirty
c_func
(paren
id|bh
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * b_end_io has to clear the BH_Uptodate bitflag in the read error&n;&t; * case, however buffer contents are not necessarily bad if a&n;&t; * write fails&n;&t; */
id|bh
op_member_access_from_pointer
id|b_end_io
c_func
(paren
id|bh
comma
id|buffer_uptodate
c_func
(paren
id|bh
)paren
)paren
suffix:semicolon
)brace
DECL|function|brelse
r_static
r_inline
r_void
id|brelse
c_func
(paren
r_struct
id|buffer_head
op_star
id|buf
)paren
(brace
r_if
c_cond
(paren
id|buf
)paren
id|__brelse
c_func
(paren
id|buf
)paren
suffix:semicolon
)brace
DECL|function|bforget
r_static
r_inline
r_void
id|bforget
c_func
(paren
r_struct
id|buffer_head
op_star
id|buf
)paren
(brace
r_if
c_cond
(paren
id|buf
)paren
id|__bforget
c_func
(paren
id|buf
)paren
suffix:semicolon
)brace
DECL|function|sb_bread
r_static
r_inline
r_struct
id|buffer_head
op_star
id|sb_bread
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
r_return
id|__bread
c_func
(paren
id|sb-&gt;s_bdev
comma
id|block
comma
id|sb-&gt;s_blocksize
)paren
suffix:semicolon
)brace
DECL|function|sb_getblk
r_static
r_inline
r_struct
id|buffer_head
op_star
id|sb_getblk
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
r_return
id|__getblk
c_func
(paren
id|sb-&gt;s_bdev
comma
id|block
comma
id|sb-&gt;s_blocksize
)paren
suffix:semicolon
)brace
r_static
r_inline
r_struct
id|buffer_head
op_star
DECL|function|sb_get_hash_table
id|sb_get_hash_table
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
r_return
id|__get_hash_table
c_func
(paren
id|sb-&gt;s_bdev
comma
id|block
comma
id|sb-&gt;s_blocksize
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|map_bh
id|map_bh
c_func
(paren
r_struct
id|buffer_head
op_star
id|bh
comma
r_struct
id|super_block
op_star
id|sb
comma
r_int
id|block
)paren
(brace
id|set_buffer_mapped
c_func
(paren
id|bh
)paren
suffix:semicolon
id|bh-&gt;b_bdev
op_assign
id|sb-&gt;s_bdev
suffix:semicolon
id|bh-&gt;b_blocknr
op_assign
id|block
suffix:semicolon
)brace
DECL|function|wait_on_buffer
r_static
r_inline
r_void
id|wait_on_buffer
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
id|buffer_locked
c_func
(paren
id|bh
)paren
)paren
id|__wait_on_buffer
c_func
(paren
id|bh
)paren
suffix:semicolon
)brace
DECL|function|lock_buffer
r_static
r_inline
r_void
id|lock_buffer
c_func
(paren
r_struct
id|buffer_head
op_star
id|bh
)paren
(brace
r_while
c_loop
(paren
id|test_set_buffer_locked
c_func
(paren
id|bh
)paren
)paren
id|__wait_on_buffer
c_func
(paren
id|bh
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Debug&n; */
r_void
id|__buffer_error
c_func
(paren
r_char
op_star
id|file
comma
r_int
id|line
)paren
suffix:semicolon
DECL|macro|buffer_error
mdefine_line|#define buffer_error() __buffer_error(__FILE__, __LINE__)
macro_line|#endif /* _LINUX_BUFFER_HEAD_H */
eof
