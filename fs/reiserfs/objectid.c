multiline_comment|/*&n; * Copyright 2000 by Hans Reiser, licensing governed by reiserfs/README&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/locks.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/reiserfs_fs.h&gt;
singleline_comment|// find where objectid map starts
DECL|macro|objectid_map
mdefine_line|#define objectid_map(s,rs) (old_format_only (s) ? &bslash;&n;                         (__u32 *)((struct reiserfs_super_block_v1 *)(rs) + 1) :&bslash;&n;&t;&t;&t; (__u32 *)((rs) + 1))
macro_line|#ifdef CONFIG_REISERFS_CHECK
DECL|function|check_objectid_map
r_static
r_void
id|check_objectid_map
(paren
r_struct
id|super_block
op_star
id|s
comma
id|__u32
op_star
id|map
)paren
(brace
r_if
c_cond
(paren
id|le32_to_cpu
(paren
id|map
(braket
l_int|0
)braket
)paren
op_ne
l_int|1
)paren
id|reiserfs_panic
(paren
id|s
comma
l_string|&quot;vs-15010: check_objectid_map: map corrupted: %lx&quot;
comma
(paren
r_int
r_int
r_int
)paren
id|le32_to_cpu
(paren
id|map
(braket
l_int|0
)braket
)paren
)paren
suffix:semicolon
singleline_comment|// FIXME: add something else here
)brace
macro_line|#else
DECL|function|check_objectid_map
r_static
r_void
id|check_objectid_map
(paren
r_struct
id|super_block
op_star
id|s
comma
id|__u32
op_star
id|map
)paren
(brace
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* When we allocate objectids we allocate the first unused objectid.&n;   Each sequence of objectids in use (the odd sequences) is followed&n;   by a sequence of objectids not in use (the even sequences).  We&n;   only need to record the last objectid in each of these sequences&n;   (both the odd and even sequences) in order to fully define the&n;   boundaries of the sequences.  A consequence of allocating the first&n;   objectid not in use is that under most conditions this scheme is&n;   extremely compact.  The exception is immediately after a sequence&n;   of operations which deletes a large number of objects of&n;   non-sequential objectids, and even then it will become compact&n;   again as soon as more objects are created.  Note that many&n;   interesting optimizations of layout could result from complicating&n;   objectid assignment, but we have deferred making them for now. */
multiline_comment|/* get unique object identifier */
DECL|function|reiserfs_get_unused_objectid
id|__u32
id|reiserfs_get_unused_objectid
(paren
r_struct
id|reiserfs_transaction_handle
op_star
id|th
)paren
(brace
r_struct
id|super_block
op_star
id|s
op_assign
id|th-&gt;t_super
suffix:semicolon
r_struct
id|reiserfs_super_block
op_star
id|rs
op_assign
id|SB_DISK_SUPER_BLOCK
(paren
id|s
)paren
suffix:semicolon
id|__u32
op_star
id|map
op_assign
id|objectid_map
(paren
id|s
comma
id|rs
)paren
suffix:semicolon
id|__u32
id|unused_objectid
suffix:semicolon
id|check_objectid_map
(paren
id|s
comma
id|map
)paren
suffix:semicolon
id|reiserfs_prepare_for_journal
c_func
(paren
id|s
comma
id|SB_BUFFER_WITH_SB
c_func
(paren
id|s
)paren
comma
l_int|1
)paren
suffix:semicolon
multiline_comment|/* comment needed -Hans */
id|unused_objectid
op_assign
id|le32_to_cpu
(paren
id|map
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unused_objectid
op_eq
id|U32_MAX
)paren
(brace
id|printk
(paren
l_string|&quot;REISERFS: get_objectid: no more object ids&bslash;n&quot;
)paren
suffix:semicolon
id|reiserfs_restore_prepared_buffer
c_func
(paren
id|s
comma
id|SB_BUFFER_WITH_SB
c_func
(paren
id|s
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* This incrementation allocates the first unused objectid. That&n;       is to say, the first entry on the objectid map is the first&n;       unused objectid, and by incrementing it we use it.  See below&n;       where we check to see if we eliminated a sequence of unused&n;       objectids.... */
id|map
(braket
l_int|1
)braket
op_assign
id|cpu_to_le32
(paren
id|unused_objectid
op_plus
l_int|1
)paren
suffix:semicolon
multiline_comment|/* Now we check to see if we eliminated the last remaining member of&n;       the first even sequence (and can eliminate the sequence by&n;       eliminating its last objectid from oids), and can collapse the&n;       first two odd sequences into one sequence.  If so, then the net&n;       result is to eliminate a pair of objectids from oids.  We do this&n;       by shifting the entire map to the left. */
r_if
c_cond
(paren
id|sb_oid_cursize
c_func
(paren
id|rs
)paren
OG
l_int|2
op_logical_and
id|map
(braket
l_int|1
)braket
op_eq
id|map
(braket
l_int|2
)braket
)paren
(brace
id|memmove
(paren
id|map
op_plus
l_int|1
comma
id|map
op_plus
l_int|3
comma
(paren
id|sb_oid_cursize
c_func
(paren
id|rs
)paren
op_minus
l_int|3
)paren
op_star
r_sizeof
(paren
id|__u32
)paren
)paren
suffix:semicolon
id|set_sb_oid_cursize
c_func
(paren
id|rs
comma
id|sb_oid_cursize
c_func
(paren
id|rs
)paren
op_minus
l_int|2
)paren
suffix:semicolon
)brace
id|journal_mark_dirty
c_func
(paren
id|th
comma
id|s
comma
id|SB_BUFFER_WITH_SB
(paren
id|s
)paren
)paren
suffix:semicolon
id|s-&gt;s_dirt
op_assign
l_int|1
suffix:semicolon
r_return
id|unused_objectid
suffix:semicolon
)brace
multiline_comment|/* makes object identifier unused */
DECL|function|reiserfs_release_objectid
r_void
id|reiserfs_release_objectid
(paren
r_struct
id|reiserfs_transaction_handle
op_star
id|th
comma
id|__u32
id|objectid_to_release
)paren
(brace
r_struct
id|super_block
op_star
id|s
op_assign
id|th-&gt;t_super
suffix:semicolon
r_struct
id|reiserfs_super_block
op_star
id|rs
op_assign
id|SB_DISK_SUPER_BLOCK
(paren
id|s
)paren
suffix:semicolon
id|__u32
op_star
id|map
op_assign
id|objectid_map
(paren
id|s
comma
id|rs
)paren
suffix:semicolon
r_int
id|i
op_assign
l_int|0
suffix:semicolon
singleline_comment|//return;
id|check_objectid_map
(paren
id|s
comma
id|map
)paren
suffix:semicolon
id|reiserfs_prepare_for_journal
c_func
(paren
id|s
comma
id|SB_BUFFER_WITH_SB
c_func
(paren
id|s
)paren
comma
l_int|1
)paren
suffix:semicolon
id|journal_mark_dirty
c_func
(paren
id|th
comma
id|s
comma
id|SB_BUFFER_WITH_SB
(paren
id|s
)paren
)paren
suffix:semicolon
id|s-&gt;s_dirt
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* start at the beginning of the objectid map (i = 0) and go to&n;       the end of it (i = disk_sb-&gt;s_oid_cursize).  Linear search is&n;       what we use, though it is possible that binary search would be&n;       more efficient after performing lots of deletions (which is&n;       when oids is large.)  We only check even i&squot;s. */
r_while
c_loop
(paren
id|i
OL
id|sb_oid_cursize
c_func
(paren
id|rs
)paren
)paren
(brace
r_if
c_cond
(paren
id|objectid_to_release
op_eq
id|le32_to_cpu
(paren
id|map
(braket
id|i
)braket
)paren
)paren
(brace
multiline_comment|/* This incrementation unallocates the objectid. */
singleline_comment|//map[i]++;
id|map
(braket
id|i
)braket
op_assign
id|cpu_to_le32
(paren
id|le32_to_cpu
(paren
id|map
(braket
id|i
)braket
)paren
op_plus
l_int|1
)paren
suffix:semicolon
multiline_comment|/* Did we unallocate the last member of an odd sequence, and can shrink oids? */
r_if
c_cond
(paren
id|map
(braket
id|i
)braket
op_eq
id|map
(braket
id|i
op_plus
l_int|1
)braket
)paren
(brace
multiline_comment|/* shrink objectid map */
id|memmove
(paren
id|map
op_plus
id|i
comma
id|map
op_plus
id|i
op_plus
l_int|2
comma
(paren
id|sb_oid_cursize
c_func
(paren
id|rs
)paren
op_minus
id|i
op_minus
l_int|2
)paren
op_star
r_sizeof
(paren
id|__u32
)paren
)paren
suffix:semicolon
singleline_comment|//disk_sb-&gt;s_oid_cursize -= 2;
id|set_sb_oid_cursize
c_func
(paren
id|rs
comma
id|sb_oid_cursize
c_func
(paren
id|rs
)paren
op_minus
l_int|2
)paren
suffix:semicolon
id|RFALSE
c_func
(paren
id|sb_oid_cursize
c_func
(paren
id|rs
)paren
template_param
id|sb_oid_maxsize
c_func
(paren
id|rs
)paren
comma
l_string|&quot;vs-15005: objectid map corrupted cur_size == %d (max == %d)&quot;
comma
id|sb_oid_cursize
c_func
(paren
id|rs
)paren
comma
id|sb_oid_maxsize
c_func
(paren
id|rs
)paren
)paren
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|objectid_to_release
OG
id|le32_to_cpu
(paren
id|map
(braket
id|i
)braket
)paren
op_logical_and
id|objectid_to_release
OL
id|le32_to_cpu
(paren
id|map
(braket
id|i
op_plus
l_int|1
)braket
)paren
)paren
(brace
multiline_comment|/* size of objectid map is not changed */
r_if
c_cond
(paren
id|objectid_to_release
op_plus
l_int|1
op_eq
id|le32_to_cpu
(paren
id|map
(braket
id|i
op_plus
l_int|1
)braket
)paren
)paren
(brace
singleline_comment|//objectid_map[i+1]--;
id|map
(braket
id|i
op_plus
l_int|1
)braket
op_assign
id|cpu_to_le32
(paren
id|le32_to_cpu
(paren
id|map
(braket
id|i
op_plus
l_int|1
)braket
)paren
op_minus
l_int|1
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* JDM comparing two little-endian values for equality -- safe */
r_if
c_cond
(paren
id|rs-&gt;s_oid_cursize
op_eq
id|rs-&gt;s_oid_maxsize
)paren
(brace
multiline_comment|/* objectid map must be expanded, but there is no space */
id|PROC_INFO_INC
c_func
(paren
id|s
comma
id|leaked_oid
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* expand the objectid map*/
id|memmove
(paren
id|map
op_plus
id|i
op_plus
l_int|3
comma
id|map
op_plus
id|i
op_plus
l_int|1
comma
(paren
id|sb_oid_cursize
c_func
(paren
id|rs
)paren
op_minus
id|i
op_minus
l_int|1
)paren
op_star
r_sizeof
(paren
id|__u32
)paren
)paren
suffix:semicolon
id|map
(braket
id|i
op_plus
l_int|1
)braket
op_assign
id|cpu_to_le32
(paren
id|objectid_to_release
)paren
suffix:semicolon
id|map
(braket
id|i
op_plus
l_int|2
)braket
op_assign
id|cpu_to_le32
(paren
id|objectid_to_release
op_plus
l_int|1
)paren
suffix:semicolon
id|set_sb_oid_cursize
c_func
(paren
id|rs
comma
id|sb_oid_cursize
c_func
(paren
id|rs
)paren
op_plus
l_int|2
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|i
op_add_assign
l_int|2
suffix:semicolon
)brace
id|reiserfs_warning
(paren
l_string|&quot;vs-15010: reiserfs_release_objectid: tried to free free object id (%lu)&quot;
comma
(paren
r_int
r_int
)paren
id|objectid_to_release
)paren
suffix:semicolon
)brace
DECL|function|reiserfs_convert_objectid_map_v1
r_int
id|reiserfs_convert_objectid_map_v1
c_func
(paren
r_struct
id|super_block
op_star
id|s
)paren
(brace
r_struct
id|reiserfs_super_block
op_star
id|disk_sb
op_assign
id|SB_DISK_SUPER_BLOCK
(paren
id|s
)paren
suffix:semicolon
r_int
id|cur_size
op_assign
id|le16_to_cpu
c_func
(paren
id|disk_sb-&gt;s_oid_cursize
)paren
suffix:semicolon
r_int
id|new_size
op_assign
(paren
id|s-&gt;s_blocksize
op_minus
id|SB_SIZE
)paren
op_div
r_sizeof
(paren
id|__u32
)paren
op_div
l_int|2
op_star
l_int|2
suffix:semicolon
r_int
id|old_max
op_assign
id|le16_to_cpu
c_func
(paren
id|disk_sb-&gt;s_oid_maxsize
)paren
suffix:semicolon
r_struct
id|reiserfs_super_block_v1
op_star
id|disk_sb_v1
suffix:semicolon
id|__u32
op_star
id|objectid_map
comma
op_star
id|new_objectid_map
suffix:semicolon
r_int
id|i
suffix:semicolon
id|disk_sb_v1
op_assign
(paren
r_struct
id|reiserfs_super_block_v1
op_star
)paren
(paren
id|SB_BUFFER_WITH_SB
c_func
(paren
id|s
)paren
op_member_access_from_pointer
id|b_data
)paren
suffix:semicolon
id|objectid_map
op_assign
(paren
id|__u32
op_star
)paren
(paren
id|disk_sb_v1
op_plus
l_int|1
)paren
suffix:semicolon
id|new_objectid_map
op_assign
(paren
id|__u32
op_star
)paren
(paren
id|disk_sb
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cur_size
OG
id|new_size
)paren
(brace
multiline_comment|/* mark everyone used that was listed as free at the end of the objectid&n;&t;** map &n;&t;*/
id|objectid_map
(braket
id|new_size
op_minus
l_int|1
)braket
op_assign
id|objectid_map
(braket
id|cur_size
op_minus
l_int|1
)braket
suffix:semicolon
id|disk_sb-&gt;s_oid_cursize
op_assign
id|cpu_to_le16
c_func
(paren
id|new_size
)paren
suffix:semicolon
)brace
multiline_comment|/* move the smaller objectid map past the end of the new super */
r_for
c_loop
(paren
id|i
op_assign
id|new_size
op_minus
l_int|1
suffix:semicolon
id|i
op_ge
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
(brace
id|objectid_map
(braket
id|i
op_plus
(paren
id|old_max
op_minus
id|new_size
)paren
)braket
op_assign
id|objectid_map
(braket
id|i
)braket
suffix:semicolon
)brace
multiline_comment|/* set the max size so we don&squot;t overflow later */
id|disk_sb-&gt;s_oid_maxsize
op_assign
id|cpu_to_le16
c_func
(paren
id|new_size
)paren
suffix:semicolon
multiline_comment|/* finally, zero out the unused chunk of the new super */
id|memset
c_func
(paren
id|disk_sb-&gt;s_unused
comma
l_int|0
comma
r_sizeof
(paren
id|disk_sb-&gt;s_unused
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
