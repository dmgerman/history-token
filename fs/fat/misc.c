multiline_comment|/*&n; *  linux/fs/fat/misc.c&n; *&n; *  Written 1992,1993 by Werner Almesberger&n; *  22/11/2000 - Fixed fat_date_unix2dos for dates earlier than 01/01/1980&n; *&t;&t; and date_dos2unix for date==0 by Igor Zhbanov(bsg@uniyar.ac.ru)&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/msdos_fs.h&gt;
macro_line|#include &lt;linux/buffer_head.h&gt;
multiline_comment|/*&n; * fat_fs_panic reports a severe file system problem and sets the file system&n; * read-only. The file system can be made writable again by remounting it.&n; */
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
id|va_list
id|args
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;FAT: Filesystem panic (dev %s)&bslash;n&quot;
comma
id|s-&gt;s_id
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;    &quot;
)paren
suffix:semicolon
id|va_start
c_func
(paren
id|args
comma
id|fmt
)paren
suffix:semicolon
id|vprintk
c_func
(paren
id|fmt
comma
id|args
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|args
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|s-&gt;s_flags
op_amp
id|MS_RDONLY
)paren
)paren
(brace
id|s-&gt;s_flags
op_or_assign
id|MS_RDONLY
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;    File system has been set read-only&bslash;n&quot;
)paren
suffix:semicolon
)brace
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
id|sbi-&gt;fat_bits
op_ne
l_int|32
)paren
r_return
suffix:semicolon
id|bh
op_assign
id|sb_bread
c_func
(paren
id|sb
comma
id|sbi-&gt;fsinfo_sector
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
id|KERN_ERR
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
id|KERN_ERR
l_string|&quot;FAT: Did not find valid FSINFO signature.&bslash;n&quot;
l_string|&quot;     Found signature1 0x%08x signature2 0x%08x&quot;
l_string|&quot; (sector = %lu)&bslash;n&quot;
comma
id|le32_to_cpu
c_func
(paren
id|fsinfo-&gt;signature1
)paren
comma
id|le32_to_cpu
c_func
(paren
id|fsinfo-&gt;signature2
)paren
comma
id|sbi-&gt;fsinfo_sector
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|sbi-&gt;free_clusters
op_ne
op_minus
l_int|1
)paren
id|fsinfo-&gt;free_clusters
op_assign
id|cpu_to_le32
c_func
(paren
id|sbi-&gt;free_clusters
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sbi-&gt;prev_free
op_ne
op_minus
l_int|1
)paren
id|fsinfo-&gt;next_cluster
op_assign
id|cpu_to_le32
c_func
(paren
id|sbi-&gt;prev_free
)paren
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|bh
)paren
suffix:semicolon
)brace
id|brelse
c_func
(paren
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
id|ret
comma
id|count
comma
id|limit
comma
id|new_dclus
comma
id|new_fclus
comma
id|last
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
multiline_comment|/* &n;&t; * We must locate the last cluster of the file to add this new&n;&t; * one (new_dclus) to the end of the link list (the FAT).&n;&t; *&n;&t; * In order to confirm that the cluster chain is valid, we&n;&t; * find out EOF first.&n;&t; */
id|last
op_assign
id|new_fclus
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|MSDOS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_start
)paren
(brace
r_int
id|ret
comma
id|fclus
comma
id|dclus
suffix:semicolon
id|ret
op_assign
id|fat_get_cluster
c_func
(paren
id|inode
comma
id|FAT_ENT_EOF
comma
op_amp
id|fclus
comma
op_amp
id|dclus
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_return
id|ret
suffix:semicolon
id|new_fclus
op_assign
id|fclus
op_plus
l_int|1
suffix:semicolon
id|last
op_assign
id|dclus
suffix:semicolon
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
op_plus
l_int|2
suffix:semicolon
id|new_dclus
op_assign
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|prev_free
op_plus
l_int|1
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
id|clusters
suffix:semicolon
id|count
op_increment
comma
id|new_dclus
op_increment
)paren
(brace
id|new_dclus
op_assign
id|new_dclus
op_mod
id|limit
suffix:semicolon
r_if
c_cond
(paren
id|new_dclus
OL
l_int|2
)paren
id|new_dclus
op_assign
l_int|2
suffix:semicolon
id|ret
op_assign
id|fat_access
c_func
(paren
id|sb
comma
id|new_dclus
comma
op_minus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
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
id|ret
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|ret
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
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|clusters
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
id|ret
op_assign
id|fat_access
c_func
(paren
id|sb
comma
id|new_dclus
comma
id|FAT_ENT_EOF
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
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
id|ret
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
id|new_dclus
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
id|ret
op_assign
id|fat_access
c_func
(paren
id|sb
comma
id|last
comma
id|new_dclus
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_return
id|ret
suffix:semicolon
singleline_comment|//&t;&t;fat_cache_add(inode, new_fclus, new_dclus);
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
id|new_dclus
suffix:semicolon
id|MSDOS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_logstart
op_assign
id|new_dclus
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
id|new_fclus
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
id|fat_fs_panic
c_func
(paren
id|sb
comma
l_string|&quot;clusters badly computed (%d != %lu)&quot;
comma
id|new_fclus
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
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|cluster_size
op_rshift
l_int|9
suffix:semicolon
r_return
id|new_dclus
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
id|nr
comma
id|sec_per_clus
op_assign
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|sec_per_clus
suffix:semicolon
id|sector_t
id|sector
comma
id|last_sector
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
(paren
(paren
id|sector_t
)paren
id|nr
op_minus
l_int|2
)paren
op_star
id|sec_per_clus
op_plus
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|data_start
suffix:semicolon
id|last_sector
op_assign
id|sector
op_plus
id|sec_per_clus
suffix:semicolon
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
(paren
id|bh
op_assign
id|sb_getblk
c_func
(paren
id|sb
comma
id|sector
)paren
)paren
)paren
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
id|set_buffer_uptodate
c_func
(paren
id|bh
)paren
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
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
id|brelse
c_func
(paren
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
(paren
id|loff_t
)paren
id|sb-&gt;s_blocksize
op_minus
l_int|1
)paren
suffix:semicolon
)brace
id|inode-&gt;i_size
op_add_assign
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|cluster_size
suffix:semicolon
id|MSDOS_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|mmu_private
op_add_assign
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|cluster_size
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
id|__le16
op_star
id|time
comma
id|__le16
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
id|cpu_to_le16
c_func
(paren
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
id|cpu_to_le16
c_func
(paren
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
)paren
suffix:semicolon
)brace
DECL|variable|fat_date_unix2dos
id|EXPORT_SYMBOL
c_func
(paren
id|fat_date_unix2dos
)paren
suffix:semicolon
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
id|loff_t
op_star
id|i_pos
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
id|sector_t
id|phys
comma
id|iblock
suffix:semicolon
id|loff_t
id|offset
suffix:semicolon
r_int
id|err
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
id|brelse
c_func
(paren
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
id|err
op_assign
id|fat_bmap
c_func
(paren
id|dir
comma
id|iblock
comma
op_amp
id|phys
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
op_logical_or
op_logical_neg
id|phys
)paren
r_return
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* beyond EOF or error */
op_star
id|bh
op_assign
id|sb_bread
c_func
(paren
id|sb
comma
id|phys
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
id|KERN_ERR
l_string|&quot;FAT: Directory bread(block %llu) failed&bslash;n&quot;
comma
(paren
r_int
r_int
r_int
)paren
id|phys
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
id|i_pos
op_assign
(paren
(paren
id|loff_t
)paren
id|phys
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
DECL|variable|fat__get_entry
id|EXPORT_SYMBOL
c_func
(paren
id|fat__get_entry
)paren
suffix:semicolon
eof
