multiline_comment|/*&n; *  linux/fs/sysv/ialloc.c&n; *&n; *  minix/bitmap.c&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; *&n; *  ext/freelists.c&n; *  Copyright (C) 1992  Remy Card (card@masi.ibp.fr)&n; *&n; *  xenix/alloc.c&n; *  Copyright (C) 1992  Doug Evans&n; *&n; *  coh/alloc.c&n; *  Copyright (C) 1993  Pascal Haible, Bruno Haible&n; *&n; *  sysv/ialloc.c&n; *  Copyright (C) 1993  Bruno Haible&n; *&n; *  This file contains code for allocating/freeing inodes.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/locks.h&gt;
macro_line|#include &quot;sysv.h&quot;
multiline_comment|/* We don&squot;t trust the value of&n;   sb-&gt;sv_sbd2-&gt;s_tinode = *sb-&gt;sv_sb_total_free_inodes&n;   but we nevertheless keep it up to date. */
multiline_comment|/* An inode on disk is considered free if both i_mode == 0 and i_nlink == 0. */
multiline_comment|/* return &amp;sb-&gt;sv_sb_fic_inodes[i] = &amp;sbd-&gt;s_inode[i]; */
r_static
r_inline
id|sysv_ino_t
op_star
DECL|function|sv_sb_fic_inode
id|sv_sb_fic_inode
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
r_int
id|i
)paren
(brace
r_struct
id|sysv_sb_info
op_star
id|sbi
op_assign
id|SYSV_SB
c_func
(paren
id|sb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sbi-&gt;s_bh1
op_eq
id|sbi-&gt;s_bh2
)paren
r_return
op_amp
id|sbi-&gt;s_sb_fic_inodes
(braket
id|i
)braket
suffix:semicolon
r_else
(brace
multiline_comment|/* 512 byte Xenix FS */
r_int
r_int
id|offset
op_assign
m_offsetof
(paren
r_struct
id|xenix_super_block
comma
id|s_inode
(braket
id|i
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|offset
OL
l_int|512
)paren
r_return
(paren
id|sysv_ino_t
op_star
)paren
(paren
id|sbi-&gt;s_sbd1
op_plus
id|offset
)paren
suffix:semicolon
r_else
r_return
(paren
id|sysv_ino_t
op_star
)paren
(paren
id|sbi-&gt;s_sbd2
op_plus
id|offset
)paren
suffix:semicolon
)brace
)brace
r_struct
id|sysv_inode
op_star
DECL|function|sysv_raw_inode
id|sysv_raw_inode
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
id|ino
comma
r_struct
id|buffer_head
op_star
op_star
id|bh
)paren
(brace
r_struct
id|sysv_sb_info
op_star
id|sbi
op_assign
id|SYSV_SB
c_func
(paren
id|sb
)paren
suffix:semicolon
r_struct
id|sysv_inode
op_star
id|res
suffix:semicolon
r_int
id|block
op_assign
id|sbi-&gt;s_firstinodezone
op_plus
id|sbi-&gt;s_block_base
suffix:semicolon
id|block
op_add_assign
(paren
id|ino
op_minus
l_int|1
)paren
op_rshift
id|sbi-&gt;s_inodes_per_block_bits
suffix:semicolon
op_star
id|bh
op_assign
id|sb_bread
c_func
(paren
id|sb
comma
id|block
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|bh
)paren
r_return
l_int|NULL
suffix:semicolon
id|res
op_assign
(paren
r_struct
id|sysv_inode
op_star
)paren
(paren
op_star
id|bh
)paren
op_member_access_from_pointer
id|b_data
suffix:semicolon
r_return
id|res
op_plus
(paren
(paren
id|ino
op_minus
l_int|1
)paren
op_amp
id|sbi-&gt;s_inodes_per_block_1
)paren
suffix:semicolon
)brace
DECL|function|refill_free_cache
r_static
r_int
id|refill_free_cache
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_struct
id|sysv_sb_info
op_star
id|sbi
op_assign
id|SYSV_SB
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
id|sysv_inode
op_star
id|raw_inode
suffix:semicolon
r_int
id|i
op_assign
l_int|0
comma
id|ino
suffix:semicolon
id|ino
op_assign
id|SYSV_ROOT_INO
op_plus
l_int|1
suffix:semicolon
id|raw_inode
op_assign
id|sysv_raw_inode
c_func
(paren
id|sb
comma
id|ino
comma
op_amp
id|bh
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|raw_inode
)paren
r_goto
id|out
suffix:semicolon
r_while
c_loop
(paren
id|ino
op_le
id|sbi-&gt;s_ninodes
)paren
(brace
r_if
c_cond
(paren
id|raw_inode-&gt;i_mode
op_eq
l_int|0
op_logical_and
id|raw_inode-&gt;i_nlink
op_eq
l_int|0
)paren
(brace
op_star
id|sv_sb_fic_inode
c_func
(paren
id|sb
comma
id|i
op_increment
)paren
op_assign
id|cpu_to_fs16
c_func
(paren
id|SYSV_SB
c_func
(paren
id|sb
)paren
comma
id|ino
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
op_eq
id|sbi-&gt;s_fic_size
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|ino
op_increment
op_amp
id|sbi-&gt;s_inodes_per_block_1
)paren
op_eq
l_int|0
)paren
(brace
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|raw_inode
op_assign
id|sysv_raw_inode
c_func
(paren
id|sb
comma
id|ino
comma
op_amp
id|bh
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|raw_inode
)paren
r_goto
id|out
suffix:semicolon
)brace
r_else
id|raw_inode
op_increment
suffix:semicolon
)brace
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|i
suffix:semicolon
)brace
DECL|function|sysv_free_inode
r_void
id|sysv_free_inode
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
id|sysv_sb_info
op_star
id|sbi
op_assign
id|SYSV_SB
c_func
(paren
id|sb
)paren
suffix:semicolon
r_int
r_int
id|ino
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_struct
id|sysv_inode
op_star
id|raw_inode
suffix:semicolon
r_int
id|count
suffix:semicolon
id|sb
op_assign
id|inode-&gt;i_sb
suffix:semicolon
id|ino
op_assign
id|inode-&gt;i_ino
suffix:semicolon
r_if
c_cond
(paren
id|ino
op_le
id|SYSV_ROOT_INO
op_logical_or
id|ino
OG
id|sbi-&gt;s_ninodes
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;sysv_free_inode: inode 0,1,2 or nonexistent inode&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|raw_inode
op_assign
id|sysv_raw_inode
c_func
(paren
id|sb
comma
id|ino
comma
op_amp
id|bh
)paren
suffix:semicolon
id|clear_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|raw_inode
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;sysv_free_inode: unable to read inode block on device &quot;
l_string|&quot;%s&bslash;n&quot;
comma
id|inode-&gt;i_sb-&gt;s_id
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|lock_super
c_func
(paren
id|sb
)paren
suffix:semicolon
id|count
op_assign
id|fs16_to_cpu
c_func
(paren
id|sbi
comma
op_star
id|sbi-&gt;s_sb_fic_count
)paren
suffix:semicolon
r_if
c_cond
(paren
id|count
OL
id|sbi-&gt;s_fic_size
)paren
(brace
op_star
id|sv_sb_fic_inode
c_func
(paren
id|sb
comma
id|count
op_increment
)paren
op_assign
id|cpu_to_fs16
c_func
(paren
id|sbi
comma
id|ino
)paren
suffix:semicolon
op_star
id|sbi-&gt;s_sb_fic_count
op_assign
id|cpu_to_fs16
c_func
(paren
id|sbi
comma
id|count
)paren
suffix:semicolon
)brace
id|fs16_add
c_func
(paren
id|sbi
comma
id|sbi-&gt;s_sb_total_free_inodes
comma
l_int|1
)paren
suffix:semicolon
id|dirty_sb
c_func
(paren
id|sb
)paren
suffix:semicolon
id|memset
c_func
(paren
id|raw_inode
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|sysv_inode
)paren
)paren
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|bh
)paren
suffix:semicolon
id|unlock_super
c_func
(paren
id|sb
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
)brace
DECL|function|sysv_new_inode
r_struct
id|inode
op_star
id|sysv_new_inode
c_func
(paren
r_const
r_struct
id|inode
op_star
id|dir
comma
id|mode_t
id|mode
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
id|sysv_sb_info
op_star
id|sbi
op_assign
id|SYSV_SB
c_func
(paren
id|sb
)paren
suffix:semicolon
r_struct
id|inode
op_star
id|inode
suffix:semicolon
id|u16
id|ino
suffix:semicolon
r_int
id|count
suffix:semicolon
id|inode
op_assign
id|new_inode
c_func
(paren
id|sb
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
)paren
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|ENOMEM
)paren
suffix:semicolon
id|lock_super
c_func
(paren
id|sb
)paren
suffix:semicolon
id|count
op_assign
id|fs16_to_cpu
c_func
(paren
id|sbi
comma
op_star
id|sbi-&gt;s_sb_fic_count
)paren
suffix:semicolon
r_if
c_cond
(paren
id|count
op_eq
l_int|0
op_logical_or
(paren
op_star
id|sv_sb_fic_inode
c_func
(paren
id|sb
comma
id|count
op_minus
l_int|1
)paren
op_eq
l_int|0
)paren
)paren
(brace
id|count
op_assign
id|refill_free_cache
c_func
(paren
id|sb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|count
op_eq
l_int|0
)paren
(brace
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
id|unlock_super
c_func
(paren
id|sb
)paren
suffix:semicolon
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|ENOSPC
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Now count &gt; 0. */
id|ino
op_assign
op_star
id|sv_sb_fic_inode
c_func
(paren
id|sb
comma
op_decrement
id|count
)paren
suffix:semicolon
op_star
id|sbi-&gt;s_sb_fic_count
op_assign
id|cpu_to_fs16
c_func
(paren
id|sbi
comma
id|count
)paren
suffix:semicolon
id|fs16_add
c_func
(paren
id|sbi
comma
id|sbi-&gt;s_sb_total_free_inodes
comma
op_minus
l_int|1
)paren
suffix:semicolon
id|dirty_sb
c_func
(paren
id|sb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dir-&gt;i_mode
op_amp
id|S_ISGID
)paren
(brace
id|inode-&gt;i_gid
op_assign
id|dir-&gt;i_gid
suffix:semicolon
r_if
c_cond
(paren
id|S_ISDIR
c_func
(paren
id|mode
)paren
)paren
id|mode
op_or_assign
id|S_ISGID
suffix:semicolon
)brace
r_else
id|inode-&gt;i_gid
op_assign
id|current-&gt;fsgid
suffix:semicolon
id|inode-&gt;i_uid
op_assign
id|current-&gt;fsuid
suffix:semicolon
id|inode-&gt;i_ino
op_assign
id|fs16_to_cpu
c_func
(paren
id|sbi
comma
id|ino
)paren
suffix:semicolon
id|inode-&gt;i_mtime
op_assign
id|inode-&gt;i_atime
op_assign
id|inode-&gt;i_ctime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|inode-&gt;i_blocks
op_assign
id|inode-&gt;i_blksize
op_assign
l_int|0
suffix:semicolon
id|memset
c_func
(paren
id|SYSV_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_data
comma
l_int|0
comma
r_sizeof
(paren
id|SYSV_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_data
)paren
)paren
suffix:semicolon
id|SYSV_I
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|i_dir_start_lookup
op_assign
l_int|0
suffix:semicolon
id|insert_inode_hash
c_func
(paren
id|inode
)paren
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
id|inode-&gt;i_mode
op_assign
id|mode
suffix:semicolon
multiline_comment|/* for sysv_write_inode() */
id|sysv_write_inode
c_func
(paren
id|inode
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* ensure inode not allocated again */
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
multiline_comment|/* cleared by sysv_write_inode() */
multiline_comment|/* That&squot;s it. */
id|unlock_super
c_func
(paren
id|sb
)paren
suffix:semicolon
r_return
id|inode
suffix:semicolon
)brace
DECL|function|sysv_count_free_inodes
r_int
r_int
id|sysv_count_free_inodes
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_struct
id|sysv_sb_info
op_star
id|sbi
op_assign
id|SYSV_SB
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
id|sysv_inode
op_star
id|raw_inode
suffix:semicolon
r_int
id|ino
comma
id|count
comma
id|sb_count
suffix:semicolon
id|lock_super
c_func
(paren
id|sb
)paren
suffix:semicolon
id|sb_count
op_assign
id|fs16_to_cpu
c_func
(paren
id|sbi
comma
op_star
id|sbi-&gt;s_sb_total_free_inodes
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|0
)paren
r_goto
id|trust_sb
suffix:semicolon
multiline_comment|/* this causes a lot of disk traffic ... */
id|count
op_assign
l_int|0
suffix:semicolon
id|ino
op_assign
id|SYSV_ROOT_INO
op_plus
l_int|1
suffix:semicolon
id|raw_inode
op_assign
id|sysv_raw_inode
c_func
(paren
id|sb
comma
id|ino
comma
op_amp
id|bh
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|raw_inode
)paren
r_goto
id|Eio
suffix:semicolon
r_while
c_loop
(paren
id|ino
op_le
id|sbi-&gt;s_ninodes
)paren
(brace
r_if
c_cond
(paren
id|raw_inode-&gt;i_mode
op_eq
l_int|0
op_logical_and
id|raw_inode-&gt;i_nlink
op_eq
l_int|0
)paren
id|count
op_increment
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ino
op_increment
op_amp
id|sbi-&gt;s_inodes_per_block_1
)paren
op_eq
l_int|0
)paren
(brace
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|raw_inode
op_assign
id|sysv_raw_inode
c_func
(paren
id|sb
comma
id|ino
comma
op_amp
id|bh
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|raw_inode
)paren
r_goto
id|Eio
suffix:semicolon
)brace
r_else
id|raw_inode
op_increment
suffix:semicolon
)brace
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_if
c_cond
(paren
id|count
op_ne
id|sb_count
)paren
r_goto
id|Einval
suffix:semicolon
id|out
suffix:colon
id|unlock_super
c_func
(paren
id|sb
)paren
suffix:semicolon
r_return
id|count
suffix:semicolon
id|Einval
suffix:colon
id|printk
c_func
(paren
l_string|&quot;sysv_count_free_inodes: &quot;
l_string|&quot;free inode count was %d, correcting to %d&bslash;n&quot;
comma
id|sb_count
comma
id|count
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|sb-&gt;s_flags
op_amp
id|MS_RDONLY
)paren
)paren
(brace
op_star
id|sbi-&gt;s_sb_total_free_inodes
op_assign
id|cpu_to_fs16
c_func
(paren
id|SYSV_SB
c_func
(paren
id|sb
)paren
comma
id|count
)paren
suffix:semicolon
id|dirty_sb
c_func
(paren
id|sb
)paren
suffix:semicolon
)brace
r_goto
id|out
suffix:semicolon
id|Eio
suffix:colon
id|printk
c_func
(paren
l_string|&quot;sysv_count_free_inodes: unable to read inode table&bslash;n&quot;
)paren
suffix:semicolon
id|trust_sb
suffix:colon
id|count
op_assign
id|sb_count
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
eof
