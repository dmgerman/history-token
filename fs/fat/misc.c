multiline_comment|/*&n; *  linux/fs/fat/misc.c&n; *&n; *  Written 1992,1993 by Werner Almesberger&n; *  22/11/2000 - Fixed fat_date_unix2dos for dates earlier than 01/01/1980&n; *&t;&t; and date_dos2unix for date==0 by Igor Zhbanov(bsg@uniyar.ac.ru)&n; */
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/msdos_fs.h&gt;
macro_line|#include &lt;linux/buffer_head.h&gt;
macro_line|#if 0
macro_line|#  define PRINTK(x)&t;printk x
macro_line|#else
DECL|macro|PRINTK
macro_line|#  define PRINTK(x)
macro_line|#endif
DECL|macro|Printk
mdefine_line|#define Printk(x)&t;printk x
multiline_comment|/*&n; * fat_fs_panic reports a severe file system problem and sets the file system&n; * read-only. The file system can be made writable again by remounting it.&n; */
DECL|variable|panic_msg
r_static
r_char
id|panic_msg
(braket
l_int|512
)braket
suffix:semicolon
DECL|function|fat_fs_panic
r_void
id|fat_fs_panic
c_func
(paren
r_struct
id|super_block
op_star
id|s
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
(brace
r_int
id|not_ro
suffix:semicolon
id|va_list
id|args
suffix:semicolon
id|va_start
(paren
id|args
comma
id|fmt
)paren
suffix:semicolon
id|vsnprintf
(paren
id|panic_msg
comma
r_sizeof
(paren
id|panic_msg
)paren
comma
id|fmt
comma
id|args
)paren
suffix:semicolon
id|va_end
(paren
id|args
)paren
suffix:semicolon
id|not_ro
op_assign
op_logical_neg
(paren
id|s-&gt;s_flags
op_amp
id|MS_RDONLY
)paren
suffix:semicolon
r_if
c_cond
(paren
id|not_ro
)paren
id|s-&gt;s_flags
op_or_assign
id|MS_RDONLY
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;FAT: Filesystem panic (dev %s)&bslash;n&quot;
l_string|&quot;    %s&bslash;n&quot;
comma
id|s-&gt;s_id
comma
id|panic_msg
)paren
suffix:semicolon
r_if
c_cond
(paren
id|not_ro
)paren
id|printk
c_func
(paren
l_string|&quot;    File system has been set read-only&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|function|lock_fat
r_void
id|lock_fat
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
id|down
c_func
(paren
op_amp
(paren
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|fat_lock
)paren
)paren
suffix:semicolon
)brace
DECL|function|unlock_fat
r_void
id|unlock_fat
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
id|up
c_func
(paren
op_amp
(paren
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|fat_lock
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Flushes the number of free clusters on FAT32 */
multiline_comment|/* XXX: Need to write one per FSINFO block.  Currently only writes 1 */
DECL|function|fat_clusters_flush
r_void
id|fat_clusters_flush
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_struct
id|fat_boot_fsinfo
op_star
id|fsinfo
suffix:semicolon
r_if
c_cond
(paren
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|fat_bits
op_ne
l_int|32
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|free_clusters
op_eq
op_minus
l_int|1
)paren
r_return
suffix:semicolon
id|bh
op_assign
id|fat_bread
c_func
(paren
id|sb
comma
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|fsinfo_sector
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bh
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;FAT bread failed in fat_clusters_flush&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|fsinfo
op_assign
(paren
r_struct
id|fat_boot_fsinfo
op_star
)paren
id|bh-&gt;b_data
suffix:semicolon
multiline_comment|/* Sanity check */
r_if
c_cond
(paren
op_logical_neg
id|IS_FSINFO
c_func
(paren
id|fsinfo
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;FAT: Did not find valid FSINFO signature.&bslash;n&quot;
l_string|&quot;     Found signature1 0x%08x signature2 0x%08x&quot;
l_string|&quot; (sector = %lu)&bslash;n&quot;
comma
id|CF_LE_L
c_func
(paren
id|fsinfo-&gt;signature1
)paren
comma
id|CF_LE_L
c_func
(paren
id|fsinfo-&gt;signature2
)paren
comma
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|fsinfo_sector
)paren
suffix:semicolon
)brace
r_else
(brace
id|fsinfo-&gt;free_clusters
op_assign
id|CF_LE_L
c_func
(paren
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|free_clusters
)paren
suffix:semicolon
id|fat_mark_buffer_dirty
c_func
(paren
id|sb
comma
id|bh
)paren
suffix:semicolon
)brace
id|fat_brelse
c_func
(paren
id|sb
comma
id|bh
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * fat_add_cluster tries to allocate a new cluster and adds it to the&n; * file represented by inode.&n; */
DECL|function|fat_add_cluster
r_int
id|fat_add_cluster
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_struct
id|super_block
op_star
id|sb
op_assign
id|inode-&gt;i_sb
suffix:semicolon
r_int
id|count
comma
id|nr
comma
id|limit
comma
id|last
comma
id|curr
comma
id|file_cluster
suffix:semicolon
r_int
id|cluster_bits
op_assign
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|cluster_bits
suffix:semicolon
multiline_comment|/* &n;&t; * We must locate the last cluster of the file to add this new&n;&t; * one (nr) to the end of the link list (the FAT).&n;&t; *&n;&t; * In order to confirm that the cluster chain is valid, we&n;&t; * find out EOF first.&n;&t; */
id|nr
op_assign
op_minus
id|EIO
suffix:semicolon
id|last
op_assign
id|file_cluster
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|curr
op_assign
id|MSDOS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_start
)paren
op_ne
l_int|0
)paren
(brace
r_int
id|max_cluster
op_assign
id|MSDOS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|mmu_private
op_rshift
id|cluster_bits
suffix:semicolon
id|fat_cache_lookup
c_func
(paren
id|inode
comma
id|INT_MAX
comma
op_amp
id|last
comma
op_amp
id|curr
)paren
suffix:semicolon
id|file_cluster
op_assign
id|last
suffix:semicolon
r_while
c_loop
(paren
id|curr
op_logical_and
id|curr
op_ne
id|FAT_ENT_EOF
)paren
(brace
id|file_cluster
op_increment
suffix:semicolon
id|curr
op_assign
id|fat_access
c_func
(paren
id|sb
comma
id|last
op_assign
id|curr
comma
op_minus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|curr
OL
l_int|0
)paren
r_return
id|curr
suffix:semicolon
r_else
r_if
c_cond
(paren
id|curr
op_eq
id|FAT_ENT_FREE
)paren
(brace
id|fat_fs_panic
c_func
(paren
id|sb
comma
l_string|&quot;%s: invalid cluster chain&quot;
l_string|&quot; (ino %lu)&quot;
comma
id|__FUNCTION__
comma
id|inode-&gt;i_ino
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|file_cluster
OG
id|max_cluster
)paren
(brace
id|fat_fs_panic
c_func
(paren
id|sb
comma
l_string|&quot;%s: bad cluster counts&quot;
l_string|&quot; (ino %lu)&quot;
comma
id|__FUNCTION__
comma
id|inode-&gt;i_ino
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/* find free FAT entry */
id|lock_fat
c_func
(paren
id|sb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|free_clusters
op_eq
l_int|0
)paren
(brace
id|unlock_fat
c_func
(paren
id|sb
)paren
suffix:semicolon
r_return
op_minus
id|ENOSPC
suffix:semicolon
)brace
id|limit
op_assign
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|clusters
suffix:semicolon
r_for
c_loop
(paren
id|count
op_assign
l_int|0
suffix:semicolon
id|count
OL
id|limit
suffix:semicolon
id|count
op_increment
)paren
(brace
id|nr
op_assign
(paren
(paren
id|count
op_plus
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|prev_free
)paren
op_mod
id|limit
)paren
op_plus
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|fat_access
c_func
(paren
id|sb
comma
id|nr
comma
op_minus
l_int|1
)paren
op_eq
id|FAT_ENT_FREE
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|count
op_ge
id|limit
)paren
(brace
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|free_clusters
op_assign
l_int|0
suffix:semicolon
id|unlock_fat
c_func
(paren
id|sb
)paren
suffix:semicolon
r_return
op_minus
id|ENOSPC
suffix:semicolon
)brace
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|prev_free
op_assign
(paren
id|count
op_plus
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|prev_free
op_plus
l_int|1
)paren
op_mod
id|limit
suffix:semicolon
id|fat_access
c_func
(paren
id|sb
comma
id|nr
comma
id|FAT_ENT_EOF
)paren
suffix:semicolon
r_if
c_cond
(paren
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|free_clusters
op_ne
op_minus
l_int|1
)paren
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|free_clusters
op_decrement
suffix:semicolon
id|fat_clusters_flush
c_func
(paren
id|sb
)paren
suffix:semicolon
id|unlock_fat
c_func
(paren
id|sb
)paren
suffix:semicolon
multiline_comment|/* add new one to the last of the cluster chain */
r_if
c_cond
(paren
id|last
)paren
(brace
id|fat_access
c_func
(paren
id|sb
comma
id|last
comma
id|nr
)paren
suffix:semicolon
id|fat_cache_add
c_func
(paren
id|inode
comma
id|file_cluster
comma
id|nr
)paren
suffix:semicolon
)brace
r_else
(brace
id|MSDOS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_start
op_assign
id|nr
suffix:semicolon
id|MSDOS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_logstart
op_assign
id|nr
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|file_cluster
op_ne
(paren
id|inode-&gt;i_blocks
op_rshift
(paren
id|cluster_bits
op_minus
l_int|9
)paren
)paren
)paren
(brace
id|printk
(paren
l_string|&quot;file_cluster badly computed!!! %d &lt;&gt; %ld&bslash;n&quot;
comma
id|file_cluster
comma
id|inode-&gt;i_blocks
op_rshift
(paren
id|cluster_bits
op_minus
l_int|9
)paren
)paren
suffix:semicolon
id|fat_cache_inval_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
id|inode-&gt;i_blocks
op_add_assign
(paren
l_int|1
op_lshift
id|cluster_bits
)paren
op_rshift
l_int|9
suffix:semicolon
id|out
suffix:colon
r_return
id|nr
suffix:semicolon
)brace
DECL|function|fat_extend_dir
r_struct
id|buffer_head
op_star
id|fat_extend_dir
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_struct
id|super_block
op_star
id|sb
op_assign
id|inode-&gt;i_sb
suffix:semicolon
r_int
id|nr
comma
id|sector
comma
id|last_sector
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
comma
op_star
id|res
op_assign
l_int|NULL
suffix:semicolon
r_int
id|cluster_size
op_assign
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|cluster_size
suffix:semicolon
r_if
c_cond
(paren
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|fat_bits
op_ne
l_int|32
)paren
(brace
r_if
c_cond
(paren
id|inode-&gt;i_ino
op_eq
id|MSDOS_ROOT_INO
)paren
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|ENOSPC
)paren
suffix:semicolon
)brace
id|nr
op_assign
id|fat_add_cluster
c_func
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nr
OL
l_int|0
)paren
r_return
id|ERR_PTR
c_func
(paren
id|nr
)paren
suffix:semicolon
id|sector
op_assign
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|data_start
op_plus
(paren
id|nr
op_minus
l_int|2
)paren
op_star
id|cluster_size
suffix:semicolon
id|last_sector
op_assign
id|sector
op_plus
id|cluster_size
suffix:semicolon
r_if
c_cond
(paren
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|cvf_format
op_logical_and
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|cvf_format-&gt;zero_out_cluster
)paren
(brace
id|res
op_assign
id|ERR_PTR
c_func
(paren
op_minus
id|EIO
)paren
suffix:semicolon
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|cvf_format
op_member_access_from_pointer
id|zero_out_cluster
c_func
(paren
id|inode
comma
id|nr
)paren
suffix:semicolon
)brace
r_else
(brace
r_for
c_loop
(paren
suffix:semicolon
id|sector
OL
id|last_sector
suffix:semicolon
id|sector
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|bh
op_assign
id|fat_getblk
c_func
(paren
id|sb
comma
id|sector
)paren
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;FAT: fat_getblk() failed&bslash;n&quot;
)paren
suffix:semicolon
r_else
(brace
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
id|fat_set_uptodate
c_func
(paren
id|sb
comma
id|bh
comma
l_int|1
)paren
suffix:semicolon
id|fat_mark_buffer_dirty
c_func
(paren
id|sb
comma
id|bh
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|res
)paren
id|res
op_assign
id|bh
suffix:semicolon
r_else
id|fat_brelse
c_func
(paren
id|sb
comma
id|bh
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|res
op_eq
l_int|NULL
)paren
id|res
op_assign
id|ERR_PTR
c_func
(paren
op_minus
id|EIO
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|inode-&gt;i_size
op_amp
(paren
id|sb-&gt;s_blocksize
op_minus
l_int|1
)paren
)paren
(brace
id|fat_fs_panic
c_func
(paren
id|sb
comma
l_string|&quot;Odd directory size&quot;
)paren
suffix:semicolon
id|inode-&gt;i_size
op_assign
(paren
id|inode-&gt;i_size
op_plus
id|sb-&gt;s_blocksize
)paren
op_amp
op_complement
(paren
id|sb-&gt;s_blocksize
op_minus
l_int|1
)paren
suffix:semicolon
)brace
id|inode-&gt;i_size
op_add_assign
l_int|1
op_lshift
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|cluster_bits
suffix:semicolon
id|MSDOS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|mmu_private
op_add_assign
l_int|1
op_lshift
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|cluster_bits
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
multiline_comment|/* Linear day numbers of the respective 1sts in non-leap years. */
DECL|variable|day_n
r_static
r_int
id|day_n
(braket
)braket
op_assign
(brace
l_int|0
comma
l_int|31
comma
l_int|59
comma
l_int|90
comma
l_int|120
comma
l_int|151
comma
l_int|181
comma
l_int|212
comma
l_int|243
comma
l_int|273
comma
l_int|304
comma
l_int|334
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
suffix:semicolon
multiline_comment|/* JanFebMarApr May Jun Jul Aug Sep Oct Nov Dec */
r_extern
r_struct
id|timezone
id|sys_tz
suffix:semicolon
multiline_comment|/* Convert a MS-DOS time/date pair to a UNIX date (seconds since 1 1 70). */
DECL|function|date_dos2unix
r_int
id|date_dos2unix
c_func
(paren
r_int
r_int
id|time
comma
r_int
r_int
id|date
)paren
(brace
r_int
id|month
comma
id|year
comma
id|secs
suffix:semicolon
multiline_comment|/* first subtract and mask after that... Otherwise, if&n;&t;   date == 0, bad things happen */
id|month
op_assign
(paren
(paren
id|date
op_rshift
l_int|5
)paren
op_minus
l_int|1
)paren
op_amp
l_int|15
suffix:semicolon
id|year
op_assign
id|date
op_rshift
l_int|9
suffix:semicolon
id|secs
op_assign
(paren
id|time
op_amp
l_int|31
)paren
op_star
l_int|2
op_plus
l_int|60
op_star
(paren
(paren
id|time
op_rshift
l_int|5
)paren
op_amp
l_int|63
)paren
op_plus
(paren
id|time
op_rshift
l_int|11
)paren
op_star
l_int|3600
op_plus
l_int|86400
op_star
(paren
(paren
id|date
op_amp
l_int|31
)paren
op_minus
l_int|1
op_plus
id|day_n
(braket
id|month
)braket
op_plus
(paren
id|year
op_div
l_int|4
)paren
op_plus
id|year
op_star
l_int|365
op_minus
(paren
(paren
id|year
op_amp
l_int|3
)paren
op_eq
l_int|0
op_logical_and
id|month
OL
l_int|2
ques
c_cond
l_int|1
suffix:colon
l_int|0
)paren
op_plus
l_int|3653
)paren
suffix:semicolon
multiline_comment|/* days since 1.1.70 plus 80&squot;s leap day */
id|secs
op_add_assign
id|sys_tz.tz_minuteswest
op_star
l_int|60
suffix:semicolon
r_return
id|secs
suffix:semicolon
)brace
multiline_comment|/* Convert linear UNIX date to a MS-DOS time/date pair. */
DECL|function|fat_date_unix2dos
r_void
id|fat_date_unix2dos
c_func
(paren
r_int
id|unix_date
comma
r_int
r_int
op_star
id|time
comma
r_int
r_int
op_star
id|date
)paren
(brace
r_int
id|day
comma
id|year
comma
id|nl_day
comma
id|month
suffix:semicolon
id|unix_date
op_sub_assign
id|sys_tz.tz_minuteswest
op_star
l_int|60
suffix:semicolon
multiline_comment|/* Jan 1 GMT 00:00:00 1980. But what about another time zone? */
r_if
c_cond
(paren
id|unix_date
OL
l_int|315532800
)paren
id|unix_date
op_assign
l_int|315532800
suffix:semicolon
op_star
id|time
op_assign
(paren
id|unix_date
op_mod
l_int|60
)paren
op_div
l_int|2
op_plus
(paren
(paren
(paren
id|unix_date
op_div
l_int|60
)paren
op_mod
l_int|60
)paren
op_lshift
l_int|5
)paren
op_plus
(paren
(paren
(paren
id|unix_date
op_div
l_int|3600
)paren
op_mod
l_int|24
)paren
op_lshift
l_int|11
)paren
suffix:semicolon
id|day
op_assign
id|unix_date
op_div
l_int|86400
op_minus
l_int|3652
suffix:semicolon
id|year
op_assign
id|day
op_div
l_int|365
suffix:semicolon
r_if
c_cond
(paren
(paren
id|year
op_plus
l_int|3
)paren
op_div
l_int|4
op_plus
l_int|365
op_star
id|year
OG
id|day
)paren
id|year
op_decrement
suffix:semicolon
id|day
op_sub_assign
(paren
id|year
op_plus
l_int|3
)paren
op_div
l_int|4
op_plus
l_int|365
op_star
id|year
suffix:semicolon
r_if
c_cond
(paren
id|day
op_eq
l_int|59
op_logical_and
op_logical_neg
(paren
id|year
op_amp
l_int|3
)paren
)paren
(brace
id|nl_day
op_assign
id|day
suffix:semicolon
id|month
op_assign
l_int|2
suffix:semicolon
)brace
r_else
(brace
id|nl_day
op_assign
(paren
id|year
op_amp
l_int|3
)paren
op_logical_or
id|day
op_le
l_int|59
ques
c_cond
id|day
suffix:colon
id|day
op_minus
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|month
op_assign
l_int|0
suffix:semicolon
id|month
OL
l_int|12
suffix:semicolon
id|month
op_increment
)paren
r_if
c_cond
(paren
id|day_n
(braket
id|month
)braket
OG
id|nl_day
)paren
r_break
suffix:semicolon
)brace
op_star
id|date
op_assign
id|nl_day
op_minus
id|day_n
(braket
id|month
op_minus
l_int|1
)braket
op_plus
l_int|1
op_plus
(paren
id|month
op_lshift
l_int|5
)paren
op_plus
(paren
id|year
op_lshift
l_int|9
)paren
suffix:semicolon
)brace
multiline_comment|/* Returns the inode number of the directory entry at offset pos. If bh is&n;   non-NULL, it is brelse&squot;d before. Pos is incremented. The buffer header is&n;   returned in bh.&n;   AV. Most often we do it item-by-item. Makes sense to optimize.&n;   AV. OK, there we go: if both bh and de are non-NULL we assume that we just&n;   AV. want the next entry (took one explicit de=NULL in vfat/namei.c).&n;   AV. It&squot;s done in fat_get_entry() (inlined), here the slow case lives.&n;   AV. Additionally, when we return -1 (i.e. reached the end of directory)&n;   AV. we make bh NULL. &n; */
DECL|function|fat__get_entry
r_int
id|fat__get_entry
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
id|loff_t
op_star
id|pos
comma
r_struct
id|buffer_head
op_star
op_star
id|bh
comma
r_struct
id|msdos_dir_entry
op_star
op_star
id|de
comma
r_int
op_star
id|ino
)paren
(brace
r_struct
id|super_block
op_star
id|sb
op_assign
id|dir-&gt;i_sb
suffix:semicolon
r_struct
id|msdos_sb_info
op_star
id|sbi
op_assign
id|MSDOS_SB
c_func
(paren
id|sb
)paren
suffix:semicolon
r_int
id|sector
comma
id|offset
comma
id|iblock
suffix:semicolon
id|next
suffix:colon
id|offset
op_assign
op_star
id|pos
suffix:semicolon
r_if
c_cond
(paren
op_star
id|bh
)paren
id|fat_brelse
c_func
(paren
id|sb
comma
op_star
id|bh
)paren
suffix:semicolon
op_star
id|bh
op_assign
l_int|NULL
suffix:semicolon
id|iblock
op_assign
op_star
id|pos
op_rshift
id|sb-&gt;s_blocksize_bits
suffix:semicolon
id|sector
op_assign
id|fat_bmap
c_func
(paren
id|dir
comma
id|iblock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sector
op_le
l_int|0
)paren
r_return
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* beyond EOF or error */
op_star
id|bh
op_assign
id|fat_bread
c_func
(paren
id|sb
comma
id|sector
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|bh
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;FAT: Directory bread(block %d) failed&bslash;n&quot;
comma
id|sector
)paren
suffix:semicolon
multiline_comment|/* skip this block */
op_star
id|pos
op_assign
(paren
id|iblock
op_plus
l_int|1
)paren
op_lshift
id|sb-&gt;s_blocksize_bits
suffix:semicolon
r_goto
id|next
suffix:semicolon
)brace
id|offset
op_and_assign
id|sb-&gt;s_blocksize
op_minus
l_int|1
suffix:semicolon
op_star
id|pos
op_add_assign
r_sizeof
(paren
r_struct
id|msdos_dir_entry
)paren
suffix:semicolon
op_star
id|de
op_assign
(paren
r_struct
id|msdos_dir_entry
op_star
)paren
(paren
(paren
op_star
id|bh
)paren
op_member_access_from_pointer
id|b_data
op_plus
id|offset
)paren
suffix:semicolon
op_star
id|ino
op_assign
(paren
id|sector
op_lshift
id|sbi-&gt;dir_per_block_bits
)paren
op_plus
(paren
id|offset
op_rshift
id|MSDOS_DIR_BITS
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Now an ugly part: this set of directory scan routines works on clusters&n; * rather than on inodes and sectors. They are necessary to locate the &squot;..&squot;&n; * directory &quot;inode&quot;. raw_scan_sector operates in four modes:&n; *&n; * name     number   ino      action&n; * -------- -------- -------- -------------------------------------------------&n; * non-NULL -        X        Find an entry with that name&n; * NULL     non-NULL non-NULL Find an entry whose data starts at *number&n; * NULL     non-NULL NULL     Count subdirectories in *number. (*)&n; * NULL     NULL     non-NULL Find an empty entry&n; *&n; * (*) The return code should be ignored. It DOES NOT indicate success or&n; *     failure. *number has to be initialized to zero.&n; *&n; * - = not used, X = a value is returned unless NULL&n; *&n; * If res_bh is non-NULL, the buffer is not deallocated but returned to the&n; * caller on success. res_de is set accordingly.&n; *&n; * If cont is non-zero, raw_found continues with the entry after the one&n; * res_bh/res_de point to.&n; */
DECL|macro|RSS_NAME
mdefine_line|#define RSS_NAME /* search for name */ &bslash;&n;    done = !strncmp(data[entry].name,name,MSDOS_NAME) &amp;&amp; &bslash;&n;     !(data[entry].attr &amp; ATTR_VOLUME);
DECL|macro|RSS_START
mdefine_line|#define RSS_START /* search for start cluster */ &bslash;&n;    done = !IS_FREE(data[entry].name) &bslash;&n;      &amp;&amp; ( &bslash;&n;           ( &bslash;&n;             (MSDOS_SB(sb)-&gt;fat_bits != 32) ? 0 : (CF_LE_W(data[entry].starthi) &lt;&lt; 16) &bslash;&n;           ) &bslash;&n;           | CF_LE_W(data[entry].start) &bslash;&n;         ) == *number;
DECL|macro|RSS_FREE
mdefine_line|#define RSS_FREE /* search for free entry */ &bslash;&n;    { &bslash;&n;&t;done = IS_FREE(data[entry].name); &bslash;&n;    }
DECL|macro|RSS_COUNT
mdefine_line|#define RSS_COUNT /* count subdirectories */ &bslash;&n;    { &bslash;&n;&t;done = 0; &bslash;&n;&t;if (!IS_FREE(data[entry].name) &amp;&amp; (data[entry].attr &amp; ATTR_DIR)) &bslash;&n;&t;    (*number)++; &bslash;&n;    }
DECL|function|raw_scan_sector
r_static
r_int
id|raw_scan_sector
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
id|sector
comma
r_const
r_char
op_star
id|name
comma
r_int
op_star
id|number
comma
r_int
op_star
id|ino
comma
r_struct
id|buffer_head
op_star
op_star
id|res_bh
comma
r_struct
id|msdos_dir_entry
op_star
op_star
id|res_de
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_struct
id|msdos_dir_entry
op_star
id|data
suffix:semicolon
r_int
id|entry
comma
id|start
comma
id|done
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|bh
op_assign
id|fat_bread
c_func
(paren
id|sb
comma
id|sector
)paren
)paren
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|data
op_assign
(paren
r_struct
id|msdos_dir_entry
op_star
)paren
id|bh-&gt;b_data
suffix:semicolon
r_for
c_loop
(paren
id|entry
op_assign
l_int|0
suffix:semicolon
id|entry
OL
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|dir_per_block
suffix:semicolon
id|entry
op_increment
)paren
(brace
multiline_comment|/* RSS_COUNT:  if (data[entry].name == name) done=true else done=false. */
r_if
c_cond
(paren
id|name
)paren
(brace
id|RSS_NAME
)brace
r_else
(brace
r_if
c_cond
(paren
op_logical_neg
id|ino
)paren
id|RSS_COUNT
r_else
(brace
r_if
c_cond
(paren
id|number
)paren
id|RSS_START
r_else
id|RSS_FREE
)brace
)brace
r_if
c_cond
(paren
id|done
)paren
(brace
r_if
c_cond
(paren
id|ino
)paren
op_star
id|ino
op_assign
id|sector
op_star
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|dir_per_block
op_plus
id|entry
suffix:semicolon
id|start
op_assign
id|CF_LE_W
c_func
(paren
id|data
(braket
id|entry
)braket
dot
id|start
)paren
suffix:semicolon
r_if
c_cond
(paren
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|fat_bits
op_eq
l_int|32
)paren
(brace
id|start
op_or_assign
(paren
id|CF_LE_W
c_func
(paren
id|data
(braket
id|entry
)braket
dot
id|starthi
)paren
op_lshift
l_int|16
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|res_bh
)paren
id|fat_brelse
c_func
(paren
id|sb
comma
id|bh
)paren
suffix:semicolon
r_else
(brace
op_star
id|res_bh
op_assign
id|bh
suffix:semicolon
op_star
id|res_de
op_assign
op_amp
id|data
(braket
id|entry
)braket
suffix:semicolon
)brace
r_return
id|start
suffix:semicolon
)brace
)brace
id|fat_brelse
c_func
(paren
id|sb
comma
id|bh
)paren
suffix:semicolon
r_return
op_minus
id|ENOENT
suffix:semicolon
)brace
multiline_comment|/*&n; * raw_scan_root performs raw_scan_sector on the root directory until the&n; * requested entry is found or the end of the directory is reached.&n; */
DECL|function|raw_scan_root
r_static
r_int
id|raw_scan_root
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
id|name
comma
r_int
op_star
id|number
comma
r_int
op_star
id|ino
comma
r_struct
id|buffer_head
op_star
op_star
id|res_bh
comma
r_struct
id|msdos_dir_entry
op_star
op_star
id|res_de
)paren
(brace
r_int
id|count
comma
id|cluster
suffix:semicolon
r_for
c_loop
(paren
id|count
op_assign
l_int|0
suffix:semicolon
id|count
OL
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|dir_entries
op_div
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|dir_per_block
suffix:semicolon
id|count
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
id|cluster
op_assign
id|raw_scan_sector
c_func
(paren
id|sb
comma
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|dir_start
op_plus
id|count
comma
id|name
comma
id|number
comma
id|ino
comma
id|res_bh
comma
id|res_de
)paren
)paren
op_ge
l_int|0
)paren
r_return
id|cluster
suffix:semicolon
)brace
r_return
op_minus
id|ENOENT
suffix:semicolon
)brace
multiline_comment|/*&n; * raw_scan_nonroot performs raw_scan_sector on a non-root directory until the&n; * requested entry is found or the end of the directory is reached.&n; */
DECL|function|raw_scan_nonroot
r_static
r_int
id|raw_scan_nonroot
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
id|start
comma
r_const
r_char
op_star
id|name
comma
r_int
op_star
id|number
comma
r_int
op_star
id|ino
comma
r_struct
id|buffer_head
op_star
op_star
id|res_bh
comma
r_struct
id|msdos_dir_entry
op_star
op_star
id|res_de
)paren
(brace
r_int
id|count
comma
id|cluster
suffix:semicolon
r_int
r_int
id|dir_size
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;raw_scan_nonroot: start=%d&bslash;n&quot;
comma
id|start
)paren
suffix:semicolon
macro_line|#endif
r_do
(brace
r_for
c_loop
(paren
id|count
op_assign
l_int|0
suffix:semicolon
id|count
OL
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|cluster_size
suffix:semicolon
id|count
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
id|cluster
op_assign
id|raw_scan_sector
c_func
(paren
id|sb
comma
(paren
id|start
op_minus
l_int|2
)paren
op_star
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|cluster_size
op_plus
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|data_start
op_plus
id|count
comma
id|name
comma
id|number
comma
id|ino
comma
id|res_bh
comma
id|res_de
)paren
)paren
op_ge
l_int|0
)paren
r_return
id|cluster
suffix:semicolon
)brace
id|dir_size
op_add_assign
l_int|1
op_lshift
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|cluster_bits
suffix:semicolon
r_if
c_cond
(paren
id|dir_size
OG
id|FAT_MAX_DIR_SIZE
)paren
(brace
id|fat_fs_panic
c_func
(paren
id|sb
comma
l_string|&quot;Directory %d: &quot;
l_string|&quot;exceeded the maximum size of directory&quot;
comma
id|start
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|start
op_assign
id|fat_access
c_func
(paren
id|sb
comma
id|start
comma
op_minus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|start
OL
l_int|0
)paren
r_return
id|start
suffix:semicolon
r_else
r_if
c_cond
(paren
id|start
op_eq
id|FAT_ENT_FREE
)paren
(brace
id|fat_fs_panic
c_func
(paren
id|sb
comma
l_string|&quot;%s: invalid cluster chain&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;next start: %d&bslash;n&quot;
comma
id|start
)paren
suffix:semicolon
macro_line|#endif
)brace
r_while
c_loop
(paren
id|start
op_ne
id|FAT_ENT_EOF
)paren
suffix:semicolon
r_return
op_minus
id|ENOENT
suffix:semicolon
)brace
multiline_comment|/*&n; * raw_scan performs raw_scan_sector on any sector.&n; *&n; * NOTE: raw_scan must not be used on a directory that is is the process of&n; *       being created.&n; */
DECL|function|raw_scan
r_static
r_int
id|raw_scan
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
id|start
comma
r_const
r_char
op_star
id|name
comma
r_int
op_star
id|number
comma
r_int
op_star
id|ino
comma
r_struct
id|buffer_head
op_star
op_star
id|res_bh
comma
r_struct
id|msdos_dir_entry
op_star
op_star
id|res_de
)paren
(brace
r_if
c_cond
(paren
id|start
)paren
r_return
id|raw_scan_nonroot
c_func
(paren
id|sb
comma
id|start
comma
id|name
comma
id|number
comma
id|ino
comma
id|res_bh
comma
id|res_de
)paren
suffix:semicolon
r_else
r_return
id|raw_scan_root
c_func
(paren
id|sb
comma
id|name
comma
id|number
comma
id|ino
comma
id|res_bh
comma
id|res_de
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * fat_subdirs counts the number of sub-directories of dir. It can be run&n; * on directories being created.&n; */
DECL|function|fat_subdirs
r_int
id|fat_subdirs
c_func
(paren
r_struct
id|inode
op_star
id|dir
)paren
(brace
r_int
id|count
suffix:semicolon
id|count
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|dir-&gt;i_ino
op_eq
id|MSDOS_ROOT_INO
)paren
op_logical_and
(paren
id|MSDOS_SB
c_func
(paren
id|dir-&gt;i_sb
)paren
op_member_access_from_pointer
id|fat_bits
op_ne
l_int|32
)paren
)paren
(brace
(paren
r_void
)paren
id|raw_scan_root
c_func
(paren
id|dir-&gt;i_sb
comma
l_int|NULL
comma
op_amp
id|count
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
(paren
id|dir-&gt;i_ino
op_ne
id|MSDOS_ROOT_INO
)paren
op_logical_and
op_logical_neg
id|MSDOS_I
c_func
(paren
id|dir
)paren
op_member_access_from_pointer
id|i_start
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* in mkdir */
r_else
(paren
r_void
)paren
id|raw_scan_nonroot
c_func
(paren
id|dir-&gt;i_sb
comma
id|MSDOS_I
c_func
(paren
id|dir
)paren
op_member_access_from_pointer
id|i_start
comma
l_int|NULL
comma
op_amp
id|count
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
)brace
r_return
id|count
suffix:semicolon
)brace
multiline_comment|/*&n; * Scans a directory for a given file (name points to its formatted name) or&n; * for an empty directory slot (name is NULL). Returns an error code or zero.&n; */
DECL|function|fat_scan
r_int
id|fat_scan
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_const
r_char
op_star
id|name
comma
r_struct
id|buffer_head
op_star
op_star
id|res_bh
comma
r_struct
id|msdos_dir_entry
op_star
op_star
id|res_de
comma
r_int
op_star
id|ino
)paren
(brace
r_int
id|res
suffix:semicolon
id|res
op_assign
id|raw_scan
c_func
(paren
id|dir-&gt;i_sb
comma
id|MSDOS_I
c_func
(paren
id|dir
)paren
op_member_access_from_pointer
id|i_start
comma
id|name
comma
l_int|NULL
comma
id|ino
comma
id|res_bh
comma
id|res_de
)paren
suffix:semicolon
r_return
id|res
OL
l_int|0
ques
c_cond
id|res
suffix:colon
l_int|0
suffix:semicolon
)brace
eof
