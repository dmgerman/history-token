multiline_comment|/*&n; *  linux/fs/sysv/inode.c&n; *&n; *  minix/inode.c&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; *&n; *  xenix/inode.c&n; *  Copyright (C) 1992  Doug Evans&n; *&n; *  coh/inode.c&n; *  Copyright (C) 1993  Pascal Haible, Bruno Haible&n; *&n; *  sysv/inode.c&n; *  Copyright (C) 1993  Paul B. Monday&n; *&n; *  sysv/inode.c&n; *  Copyright (C) 1993  Bruno Haible&n; *  Copyright (C) 1997, 1998  Krzysztof G. Baranowski&n; *&n; *  This file contains code for read/parsing the superblock.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/sysv_fs.h&gt;
macro_line|#include &lt;linux/init.h&gt;
multiline_comment|/*&n; * The following functions try to recognize specific filesystems.&n; *&n; * We recognize:&n; * - Xenix FS by its magic number.&n; * - SystemV FS by its magic number.&n; * - Coherent FS by its funny fname/fpack field.&n; * - SCO AFS by s_nfree == 0xffff&n; * - V7 FS has no distinguishing features.&n; *&n; * We discriminate among SystemV4 and SystemV2 FS by the assumption that&n; * the time stamp is not &lt; 01-01-1980.&n; */
r_enum
(brace
DECL|enumerator|JAN_1_1980
id|JAN_1_1980
op_assign
(paren
l_int|10
op_star
l_int|365
op_plus
l_int|2
)paren
op_star
l_int|24
op_star
l_int|60
op_star
l_int|60
)brace
suffix:semicolon
DECL|function|detected_xenix
r_static
r_void
id|detected_xenix
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
id|bh1
op_assign
id|sb-&gt;sv_bh1
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh2
op_assign
id|sb-&gt;sv_bh2
suffix:semicolon
r_struct
id|xenix_super_block
op_star
id|sbd1
suffix:semicolon
r_struct
id|xenix_super_block
op_star
id|sbd2
suffix:semicolon
r_if
c_cond
(paren
id|bh1
op_ne
id|bh2
)paren
id|sbd1
op_assign
id|sbd2
op_assign
(paren
r_struct
id|xenix_super_block
op_star
)paren
id|bh1-&gt;b_data
suffix:semicolon
r_else
(brace
multiline_comment|/* block size = 512, so bh1 != bh2 */
id|sbd1
op_assign
(paren
r_struct
id|xenix_super_block
op_star
)paren
id|bh1-&gt;b_data
suffix:semicolon
id|sbd2
op_assign
(paren
r_struct
id|xenix_super_block
op_star
)paren
(paren
id|bh2-&gt;b_data
op_minus
l_int|512
)paren
suffix:semicolon
)brace
id|sb-&gt;sv_link_max
op_assign
id|XENIX_LINK_MAX
suffix:semicolon
id|sb-&gt;sv_fic_size
op_assign
id|XENIX_NICINOD
suffix:semicolon
id|sb-&gt;sv_flc_size
op_assign
id|XENIX_NICFREE
suffix:semicolon
id|sb-&gt;sv_sbd1
op_assign
(paren
r_char
op_star
)paren
id|sbd1
suffix:semicolon
id|sb-&gt;sv_sbd2
op_assign
(paren
r_char
op_star
)paren
id|sbd2
suffix:semicolon
id|sb-&gt;sv_sb_fic_count
op_assign
op_amp
id|sbd1-&gt;s_ninode
suffix:semicolon
id|sb-&gt;sv_sb_fic_inodes
op_assign
op_amp
id|sbd1-&gt;s_inode
(braket
l_int|0
)braket
suffix:semicolon
id|sb-&gt;sv_sb_total_free_inodes
op_assign
op_amp
id|sbd2-&gt;s_tinode
suffix:semicolon
id|sb-&gt;sv_bcache_count
op_assign
op_amp
id|sbd1-&gt;s_nfree
suffix:semicolon
id|sb-&gt;sv_bcache
op_assign
op_amp
id|sbd1-&gt;s_free
(braket
l_int|0
)braket
suffix:semicolon
id|sb-&gt;sv_free_blocks
op_assign
op_amp
id|sbd2-&gt;s_tfree
suffix:semicolon
id|sb-&gt;sv_sb_time
op_assign
op_amp
id|sbd2-&gt;s_time
suffix:semicolon
id|sb-&gt;sv_firstdatazone
op_assign
id|fs16_to_cpu
c_func
(paren
id|sb
comma
id|sbd1-&gt;s_isize
)paren
suffix:semicolon
id|sb-&gt;sv_nzones
op_assign
id|fs32_to_cpu
c_func
(paren
id|sb
comma
id|sbd1-&gt;s_fsize
)paren
suffix:semicolon
)brace
DECL|function|detected_sysv4
r_static
r_void
id|detected_sysv4
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_struct
id|sysv4_super_block
op_star
id|sbd
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh1
op_assign
id|sb-&gt;sv_bh1
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh2
op_assign
id|sb-&gt;sv_bh2
suffix:semicolon
r_if
c_cond
(paren
id|bh1
op_eq
id|bh2
)paren
id|sbd
op_assign
(paren
r_struct
id|sysv4_super_block
op_star
)paren
(paren
id|bh1-&gt;b_data
op_plus
id|BLOCK_SIZE
op_div
l_int|2
)paren
suffix:semicolon
r_else
id|sbd
op_assign
(paren
r_struct
id|sysv4_super_block
op_star
)paren
id|bh2-&gt;b_data
suffix:semicolon
id|sb-&gt;sv_link_max
op_assign
id|SYSV_LINK_MAX
suffix:semicolon
id|sb-&gt;sv_fic_size
op_assign
id|SYSV_NICINOD
suffix:semicolon
id|sb-&gt;sv_flc_size
op_assign
id|SYSV_NICFREE
suffix:semicolon
id|sb-&gt;sv_sbd1
op_assign
(paren
r_char
op_star
)paren
id|sbd
suffix:semicolon
id|sb-&gt;sv_sbd2
op_assign
(paren
r_char
op_star
)paren
id|sbd
suffix:semicolon
id|sb-&gt;sv_sb_fic_count
op_assign
op_amp
id|sbd-&gt;s_ninode
suffix:semicolon
id|sb-&gt;sv_sb_fic_inodes
op_assign
op_amp
id|sbd-&gt;s_inode
(braket
l_int|0
)braket
suffix:semicolon
id|sb-&gt;sv_sb_total_free_inodes
op_assign
op_amp
id|sbd-&gt;s_tinode
suffix:semicolon
id|sb-&gt;sv_bcache_count
op_assign
op_amp
id|sbd-&gt;s_nfree
suffix:semicolon
id|sb-&gt;sv_bcache
op_assign
op_amp
id|sbd-&gt;s_free
(braket
l_int|0
)braket
suffix:semicolon
id|sb-&gt;sv_free_blocks
op_assign
op_amp
id|sbd-&gt;s_tfree
suffix:semicolon
id|sb-&gt;sv_sb_time
op_assign
op_amp
id|sbd-&gt;s_time
suffix:semicolon
id|sb-&gt;sv_sb_state
op_assign
op_amp
id|sbd-&gt;s_state
suffix:semicolon
id|sb-&gt;sv_firstdatazone
op_assign
id|fs16_to_cpu
c_func
(paren
id|sb
comma
id|sbd-&gt;s_isize
)paren
suffix:semicolon
id|sb-&gt;sv_nzones
op_assign
id|fs32_to_cpu
c_func
(paren
id|sb
comma
id|sbd-&gt;s_fsize
)paren
suffix:semicolon
)brace
DECL|function|detected_sysv2
r_static
r_void
id|detected_sysv2
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_struct
id|sysv2_super_block
op_star
id|sbd
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh1
op_assign
id|sb-&gt;sv_bh1
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh2
op_assign
id|sb-&gt;sv_bh2
suffix:semicolon
r_if
c_cond
(paren
id|bh1
op_eq
id|bh2
)paren
id|sbd
op_assign
(paren
r_struct
id|sysv2_super_block
op_star
)paren
(paren
id|bh1-&gt;b_data
op_plus
id|BLOCK_SIZE
op_div
l_int|2
)paren
suffix:semicolon
r_else
id|sbd
op_assign
(paren
r_struct
id|sysv2_super_block
op_star
)paren
id|bh2-&gt;b_data
suffix:semicolon
id|sb-&gt;sv_link_max
op_assign
id|SYSV_LINK_MAX
suffix:semicolon
id|sb-&gt;sv_fic_size
op_assign
id|SYSV_NICINOD
suffix:semicolon
id|sb-&gt;sv_flc_size
op_assign
id|SYSV_NICFREE
suffix:semicolon
id|sb-&gt;sv_sbd1
op_assign
(paren
r_char
op_star
)paren
id|sbd
suffix:semicolon
id|sb-&gt;sv_sbd2
op_assign
(paren
r_char
op_star
)paren
id|sbd
suffix:semicolon
id|sb-&gt;sv_sb_fic_count
op_assign
op_amp
id|sbd-&gt;s_ninode
suffix:semicolon
id|sb-&gt;sv_sb_fic_inodes
op_assign
op_amp
id|sbd-&gt;s_inode
(braket
l_int|0
)braket
suffix:semicolon
id|sb-&gt;sv_sb_total_free_inodes
op_assign
op_amp
id|sbd-&gt;s_tinode
suffix:semicolon
id|sb-&gt;sv_bcache_count
op_assign
op_amp
id|sbd-&gt;s_nfree
suffix:semicolon
id|sb-&gt;sv_bcache
op_assign
op_amp
id|sbd-&gt;s_free
(braket
l_int|0
)braket
suffix:semicolon
id|sb-&gt;sv_free_blocks
op_assign
op_amp
id|sbd-&gt;s_tfree
suffix:semicolon
id|sb-&gt;sv_sb_time
op_assign
op_amp
id|sbd-&gt;s_time
suffix:semicolon
id|sb-&gt;sv_sb_state
op_assign
op_amp
id|sbd-&gt;s_state
suffix:semicolon
id|sb-&gt;sv_firstdatazone
op_assign
id|fs16_to_cpu
c_func
(paren
id|sb
comma
id|sbd-&gt;s_isize
)paren
suffix:semicolon
id|sb-&gt;sv_nzones
op_assign
id|fs32_to_cpu
c_func
(paren
id|sb
comma
id|sbd-&gt;s_fsize
)paren
suffix:semicolon
)brace
DECL|function|detected_coherent
r_static
r_void
id|detected_coherent
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_struct
id|coh_super_block
op_star
id|sbd
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh1
op_assign
id|sb-&gt;sv_bh1
suffix:semicolon
id|sbd
op_assign
(paren
r_struct
id|coh_super_block
op_star
)paren
id|bh1-&gt;b_data
suffix:semicolon
id|sb-&gt;sv_link_max
op_assign
id|COH_LINK_MAX
suffix:semicolon
id|sb-&gt;sv_fic_size
op_assign
id|COH_NICINOD
suffix:semicolon
id|sb-&gt;sv_flc_size
op_assign
id|COH_NICFREE
suffix:semicolon
id|sb-&gt;sv_sbd1
op_assign
(paren
r_char
op_star
)paren
id|sbd
suffix:semicolon
id|sb-&gt;sv_sbd2
op_assign
(paren
r_char
op_star
)paren
id|sbd
suffix:semicolon
id|sb-&gt;sv_sb_fic_count
op_assign
op_amp
id|sbd-&gt;s_ninode
suffix:semicolon
id|sb-&gt;sv_sb_fic_inodes
op_assign
op_amp
id|sbd-&gt;s_inode
(braket
l_int|0
)braket
suffix:semicolon
id|sb-&gt;sv_sb_total_free_inodes
op_assign
op_amp
id|sbd-&gt;s_tinode
suffix:semicolon
id|sb-&gt;sv_bcache_count
op_assign
op_amp
id|sbd-&gt;s_nfree
suffix:semicolon
id|sb-&gt;sv_bcache
op_assign
op_amp
id|sbd-&gt;s_free
(braket
l_int|0
)braket
suffix:semicolon
id|sb-&gt;sv_free_blocks
op_assign
op_amp
id|sbd-&gt;s_tfree
suffix:semicolon
id|sb-&gt;sv_sb_time
op_assign
op_amp
id|sbd-&gt;s_time
suffix:semicolon
id|sb-&gt;sv_firstdatazone
op_assign
id|fs16_to_cpu
c_func
(paren
id|sb
comma
id|sbd-&gt;s_isize
)paren
suffix:semicolon
id|sb-&gt;sv_nzones
op_assign
id|fs32_to_cpu
c_func
(paren
id|sb
comma
id|sbd-&gt;s_fsize
)paren
suffix:semicolon
)brace
DECL|function|detected_v7
r_static
r_void
id|detected_v7
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
id|bh2
op_assign
id|sb-&gt;sv_bh2
suffix:semicolon
r_struct
id|v7_super_block
op_star
id|sbd
op_assign
(paren
r_struct
id|v7_super_block
op_star
)paren
id|bh2-&gt;b_data
suffix:semicolon
id|sb-&gt;sv_link_max
op_assign
id|V7_LINK_MAX
suffix:semicolon
id|sb-&gt;sv_fic_size
op_assign
id|V7_NICINOD
suffix:semicolon
id|sb-&gt;sv_flc_size
op_assign
id|V7_NICFREE
suffix:semicolon
id|sb-&gt;sv_sbd1
op_assign
(paren
r_char
op_star
)paren
id|sbd
suffix:semicolon
id|sb-&gt;sv_sbd2
op_assign
(paren
r_char
op_star
)paren
id|sbd
suffix:semicolon
id|sb-&gt;sv_sb_fic_count
op_assign
op_amp
id|sbd-&gt;s_ninode
suffix:semicolon
id|sb-&gt;sv_sb_fic_inodes
op_assign
op_amp
id|sbd-&gt;s_inode
(braket
l_int|0
)braket
suffix:semicolon
id|sb-&gt;sv_sb_total_free_inodes
op_assign
op_amp
id|sbd-&gt;s_tinode
suffix:semicolon
id|sb-&gt;sv_bcache_count
op_assign
op_amp
id|sbd-&gt;s_nfree
suffix:semicolon
id|sb-&gt;sv_bcache
op_assign
op_amp
id|sbd-&gt;s_free
(braket
l_int|0
)braket
suffix:semicolon
id|sb-&gt;sv_free_blocks
op_assign
op_amp
id|sbd-&gt;s_tfree
suffix:semicolon
id|sb-&gt;sv_sb_time
op_assign
op_amp
id|sbd-&gt;s_time
suffix:semicolon
id|sb-&gt;sv_firstdatazone
op_assign
id|fs16_to_cpu
c_func
(paren
id|sb
comma
id|sbd-&gt;s_isize
)paren
suffix:semicolon
id|sb-&gt;sv_nzones
op_assign
id|fs32_to_cpu
c_func
(paren
id|sb
comma
id|sbd-&gt;s_fsize
)paren
suffix:semicolon
)brace
DECL|function|detect_xenix
r_static
r_int
id|detect_xenix
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
(brace
r_struct
id|xenix_super_block
op_star
id|sbd
op_assign
(paren
r_struct
id|xenix_super_block
op_star
)paren
id|bh-&gt;b_data
suffix:semicolon
r_if
c_cond
(paren
id|sbd-&gt;s_magic
op_eq
id|cpu_to_le32
c_func
(paren
l_int|0x2b5544
)paren
)paren
id|sb-&gt;sv_bytesex
op_assign
id|BYTESEX_LE
suffix:semicolon
r_else
r_if
c_cond
(paren
id|sbd-&gt;s_magic
op_eq
id|cpu_to_be32
c_func
(paren
l_int|0x2b5544
)paren
)paren
id|sb-&gt;sv_bytesex
op_assign
id|BYTESEX_BE
suffix:semicolon
r_else
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|sbd-&gt;s_type
OG
l_int|2
op_logical_or
id|sbd-&gt;s_type
OL
l_int|1
)paren
r_return
l_int|0
suffix:semicolon
id|sb-&gt;sv_type
op_assign
id|FSTYPE_XENIX
suffix:semicolon
r_return
id|sbd-&gt;s_type
suffix:semicolon
)brace
DECL|function|detect_sysv
r_static
r_int
id|detect_sysv
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
(brace
multiline_comment|/* All relevant fields are at the same offsets in R2 and R4 */
r_struct
id|sysv4_super_block
op_star
id|sbd
suffix:semicolon
id|sbd
op_assign
(paren
r_struct
id|sysv4_super_block
op_star
)paren
(paren
id|bh-&gt;b_data
op_plus
id|BLOCK_SIZE
op_div
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sbd-&gt;s_magic
op_eq
id|cpu_to_le32
c_func
(paren
l_int|0xfd187e20
)paren
)paren
id|sb-&gt;sv_bytesex
op_assign
id|BYTESEX_LE
suffix:semicolon
r_else
r_if
c_cond
(paren
id|sbd-&gt;s_magic
op_eq
id|cpu_to_be32
c_func
(paren
l_int|0xfd187e20
)paren
)paren
id|sb-&gt;sv_bytesex
op_assign
id|BYTESEX_BE
suffix:semicolon
r_else
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|fs16_to_cpu
c_func
(paren
id|sb
comma
id|sbd-&gt;s_nfree
)paren
op_eq
l_int|0xffff
)paren
(brace
id|sb-&gt;sv_type
op_assign
id|FSTYPE_AFS
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
id|printk
c_func
(paren
l_string|&quot;SysV FS: SCO EAFS on %s detected, &quot;
l_string|&quot;forcing read-only mode.&bslash;n&quot;
comma
id|bdevname
c_func
(paren
id|sb-&gt;s_dev
)paren
)paren
suffix:semicolon
id|sb-&gt;s_flags
op_or_assign
id|MS_RDONLY
suffix:semicolon
)brace
r_return
id|sbd-&gt;s_type
suffix:semicolon
)brace
r_if
c_cond
(paren
id|fs32_to_cpu
c_func
(paren
id|sb
comma
id|sbd-&gt;s_time
)paren
OL
id|JAN_1_1980
)paren
(brace
multiline_comment|/* this is likely to happen on SystemV2 FS */
r_if
c_cond
(paren
id|sbd-&gt;s_type
OG
l_int|3
op_logical_or
id|sbd-&gt;s_type
OL
l_int|1
)paren
r_return
l_int|0
suffix:semicolon
id|sb-&gt;sv_type
op_assign
id|FSTYPE_SYSV2
suffix:semicolon
r_return
id|sbd-&gt;s_type
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|sbd-&gt;s_type
OG
l_int|3
op_logical_or
id|sbd-&gt;s_type
OL
l_int|1
)paren
op_logical_and
(paren
id|sbd-&gt;s_type
OG
l_int|0x30
op_logical_or
id|sbd-&gt;s_type
OL
l_int|0x10
)paren
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* On Interactive Unix (ISC) Version 4.0/3.x s_type field = 0x10,&n;&t;   0x20 or 0x30 indicates that symbolic links and the 14-character&n;&t;   filename limit is gone. Due to lack of information about this&n;           feature read-only mode seems to be a reasonable approach... -KGB */
r_if
c_cond
(paren
id|sbd-&gt;s_type
op_ge
l_int|0x10
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;SysV FS: can&squot;t handle long file names on %s, &quot;
l_string|&quot;forcing read-only mode.&bslash;n&quot;
comma
id|kdevname
c_func
(paren
id|sb-&gt;s_dev
)paren
)paren
suffix:semicolon
id|sb-&gt;s_flags
op_or_assign
id|MS_RDONLY
suffix:semicolon
)brace
id|sb-&gt;sv_type
op_assign
id|FSTYPE_SYSV4
suffix:semicolon
r_return
id|sbd-&gt;s_type
op_ge
l_int|0x10
ques
c_cond
(paren
id|sbd-&gt;s_type
op_rshift
l_int|4
)paren
suffix:colon
id|sbd-&gt;s_type
suffix:semicolon
)brace
DECL|function|detect_coherent
r_static
r_int
id|detect_coherent
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
(brace
r_struct
id|coh_super_block
op_star
id|sbd
suffix:semicolon
id|sbd
op_assign
(paren
r_struct
id|coh_super_block
op_star
)paren
(paren
id|bh-&gt;b_data
op_plus
id|BLOCK_SIZE
op_div
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|memcmp
c_func
(paren
id|sbd-&gt;s_fname
comma
l_string|&quot;noname&quot;
comma
l_int|6
)paren
op_logical_and
id|memcmp
c_func
(paren
id|sbd-&gt;s_fname
comma
l_string|&quot;xxxxx &quot;
comma
l_int|6
)paren
)paren
op_logical_or
(paren
id|memcmp
c_func
(paren
id|sbd-&gt;s_fpack
comma
l_string|&quot;nopack&quot;
comma
l_int|6
)paren
op_logical_and
id|memcmp
c_func
(paren
id|sbd-&gt;s_fpack
comma
l_string|&quot;xxxxx&bslash;n&quot;
comma
l_int|6
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|sb-&gt;sv_bytesex
op_assign
id|BYTESEX_PDP
suffix:semicolon
id|sb-&gt;sv_type
op_assign
id|FSTYPE_COH
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|detect_sysv_odd
r_static
r_int
id|detect_sysv_odd
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
(brace
r_int
id|size
op_assign
id|detect_sysv
c_func
(paren
id|sb
comma
id|bh
)paren
suffix:semicolon
r_return
id|size
OG
l_int|2
ques
c_cond
l_int|0
suffix:colon
id|size
suffix:semicolon
)brace
r_static
r_struct
(brace
DECL|member|block
r_int
id|block
suffix:semicolon
DECL|member|test
r_int
(paren
op_star
id|test
)paren
(paren
r_struct
id|super_block
op_star
comma
r_struct
id|buffer_head
op_star
)paren
suffix:semicolon
DECL|variable|flavours
)brace
id|flavours
(braket
)braket
op_assign
(brace
(brace
l_int|1
comma
id|detect_xenix
)brace
comma
(brace
l_int|0
comma
id|detect_sysv
)brace
comma
(brace
l_int|0
comma
id|detect_coherent
)brace
comma
(brace
l_int|9
comma
id|detect_sysv_odd
)brace
comma
(brace
l_int|15
comma
id|detect_sysv_odd
)brace
comma
(brace
l_int|18
comma
id|detect_sysv
)brace
comma
)brace
suffix:semicolon
DECL|variable|flavour_names
r_static
r_char
op_star
id|flavour_names
(braket
)braket
op_assign
(brace
(braket
id|FSTYPE_XENIX
)braket
l_string|&quot;Xenix&quot;
comma
(braket
id|FSTYPE_SYSV4
)braket
l_string|&quot;SystemV&quot;
comma
(braket
id|FSTYPE_SYSV2
)braket
l_string|&quot;SystemV Release 2&quot;
comma
(braket
id|FSTYPE_COH
)braket
l_string|&quot;Coherent&quot;
comma
(braket
id|FSTYPE_V7
)braket
l_string|&quot;V7&quot;
comma
(braket
id|FSTYPE_AFS
)braket
l_string|&quot;AFS&quot;
comma
)brace
suffix:semicolon
DECL|variable|flavour_setup
r_static
r_void
(paren
op_star
id|flavour_setup
(braket
)braket
)paren
(paren
r_struct
id|super_block
op_star
)paren
op_assign
(brace
(braket
id|FSTYPE_XENIX
)braket
id|detected_xenix
comma
(braket
id|FSTYPE_SYSV4
)braket
id|detected_sysv4
comma
(braket
id|FSTYPE_SYSV2
)braket
id|detected_sysv2
comma
(braket
id|FSTYPE_COH
)braket
id|detected_coherent
comma
(braket
id|FSTYPE_V7
)braket
id|detected_v7
comma
(braket
id|FSTYPE_AFS
)braket
id|detected_sysv4
comma
)brace
suffix:semicolon
DECL|function|complete_read_super
r_static
r_int
id|complete_read_super
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
id|silent
comma
r_int
id|size
)paren
(brace
r_struct
id|inode
op_star
id|root_inode
suffix:semicolon
r_char
op_star
id|found
op_assign
id|flavour_names
(braket
id|sb-&gt;sv_type
)braket
suffix:semicolon
id|u_char
id|n_bits
op_assign
id|size
op_plus
l_int|8
suffix:semicolon
r_int
id|bsize
op_assign
l_int|1
op_lshift
id|n_bits
suffix:semicolon
r_int
id|bsize_4
op_assign
id|bsize
op_rshift
l_int|2
suffix:semicolon
id|sb-&gt;sv_firstinodezone
op_assign
l_int|2
suffix:semicolon
id|flavour_setup
(braket
id|sb-&gt;sv_type
)braket
(paren
id|sb
)paren
suffix:semicolon
id|sb-&gt;sv_truncate
op_assign
l_int|1
suffix:semicolon
id|sb-&gt;sv_ndatazones
op_assign
id|sb-&gt;sv_nzones
op_minus
id|sb-&gt;sv_firstdatazone
suffix:semicolon
id|sb-&gt;sv_inodes_per_block
op_assign
id|bsize
op_rshift
l_int|6
suffix:semicolon
id|sb-&gt;sv_inodes_per_block_1
op_assign
(paren
id|bsize
op_rshift
l_int|6
)paren
op_minus
l_int|1
suffix:semicolon
id|sb-&gt;sv_inodes_per_block_bits
op_assign
id|n_bits
op_minus
l_int|6
suffix:semicolon
id|sb-&gt;sv_ind_per_block
op_assign
id|bsize_4
suffix:semicolon
id|sb-&gt;sv_ind_per_block_2
op_assign
id|bsize_4
op_star
id|bsize_4
suffix:semicolon
id|sb-&gt;sv_toobig_block
op_assign
l_int|10
op_plus
id|bsize_4
op_star
(paren
l_int|1
op_plus
id|bsize_4
op_star
(paren
l_int|1
op_plus
id|bsize_4
)paren
)paren
suffix:semicolon
id|sb-&gt;sv_ind_per_block_bits
op_assign
id|n_bits
op_minus
l_int|2
suffix:semicolon
id|sb-&gt;sv_ninodes
op_assign
(paren
id|sb-&gt;sv_firstdatazone
op_minus
id|sb-&gt;sv_firstinodezone
)paren
op_lshift
id|sb-&gt;sv_inodes_per_block_bits
suffix:semicolon
id|sb-&gt;s_blocksize
op_assign
id|bsize
suffix:semicolon
id|sb-&gt;s_blocksize_bits
op_assign
id|n_bits
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|silent
)paren
id|printk
c_func
(paren
l_string|&quot;VFS: Found a %s FS (block size = %ld) on device %s&bslash;n&quot;
comma
id|found
comma
id|sb-&gt;s_blocksize
comma
id|bdevname
c_func
(paren
id|sb-&gt;s_dev
)paren
)paren
suffix:semicolon
id|sb-&gt;s_magic
op_assign
id|SYSV_MAGIC_BASE
op_plus
id|sb-&gt;sv_type
suffix:semicolon
multiline_comment|/* set up enough so that it can read an inode */
id|sb-&gt;s_op
op_assign
op_amp
id|sysv_sops
suffix:semicolon
id|root_inode
op_assign
id|iget
c_func
(paren
id|sb
comma
id|SYSV_ROOT_INO
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|root_inode
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;SysV FS: get root inode failed&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|sb-&gt;s_root
op_assign
id|d_alloc_root
c_func
(paren
id|root_inode
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sb-&gt;s_root
)paren
(brace
id|iput
c_func
(paren
id|root_inode
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;SysV FS: get root dentry failed&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sb-&gt;sv_truncate
)paren
id|sb-&gt;s_root-&gt;d_op
op_assign
op_amp
id|sysv_dentry_operations
suffix:semicolon
id|sb-&gt;s_flags
op_or_assign
id|MS_RDONLY
suffix:semicolon
id|sb-&gt;s_dirt
op_assign
l_int|1
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|sysv_read_super
r_static
r_struct
id|super_block
op_star
id|sysv_read_super
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_void
op_star
id|data
comma
r_int
id|silent
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh1
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
op_assign
l_int|NULL
suffix:semicolon
id|kdev_t
id|dev
op_assign
id|sb-&gt;s_dev
suffix:semicolon
r_int
r_int
id|blocknr
suffix:semicolon
r_int
id|size
op_assign
l_int|0
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
l_int|1024
op_ne
r_sizeof
(paren
r_struct
id|xenix_super_block
)paren
)paren
id|panic
c_func
(paren
l_string|&quot;Xenix FS: bad super-block size&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
l_int|512
op_ne
r_sizeof
(paren
r_struct
id|sysv4_super_block
)paren
)paren
op_logical_or
(paren
l_int|512
op_ne
r_sizeof
(paren
r_struct
id|sysv2_super_block
)paren
)paren
)paren
id|panic
c_func
(paren
l_string|&quot;SystemV FS: bad super-block size&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|500
op_ne
r_sizeof
(paren
r_struct
id|coh_super_block
)paren
)paren
id|panic
c_func
(paren
l_string|&quot;Coherent FS: bad super-block size&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|64
op_ne
r_sizeof
(paren
r_struct
id|sysv_inode
)paren
)paren
id|panic
c_func
(paren
l_string|&quot;sysv fs: bad i-node size&quot;
)paren
suffix:semicolon
id|set_blocksize
c_func
(paren
id|dev
comma
id|BLOCK_SIZE
)paren
suffix:semicolon
id|sb-&gt;s_blocksize
op_assign
id|BLOCK_SIZE
suffix:semicolon
id|sb-&gt;sv_block_base
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
r_sizeof
(paren
id|flavours
)paren
op_div
r_sizeof
(paren
id|flavours
(braket
l_int|0
)braket
)paren
op_logical_and
op_logical_neg
id|size
suffix:semicolon
id|i
op_increment
)paren
(brace
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|bh
op_assign
id|sb_bread
c_func
(paren
id|sb
comma
id|flavours
(braket
id|i
)braket
dot
id|block
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
r_continue
suffix:semicolon
id|size
op_assign
id|flavours
(braket
id|i
)braket
dot
id|test
c_func
(paren
id|sb
comma
id|bh
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|size
)paren
r_goto
id|Eunknown
suffix:semicolon
r_switch
c_cond
(paren
id|size
)paren
(brace
r_case
l_int|1
suffix:colon
id|blocknr
op_assign
id|bh-&gt;b_blocknr
op_lshift
l_int|1
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|set_blocksize
c_func
(paren
id|dev
comma
l_int|512
)paren
suffix:semicolon
id|sb-&gt;s_blocksize
op_assign
l_int|512
suffix:semicolon
id|bh1
op_assign
id|sb_bread
c_func
(paren
id|sb
comma
id|blocknr
)paren
suffix:semicolon
id|bh
op_assign
id|sb_bread
c_func
(paren
id|sb
comma
id|blocknr
op_plus
l_int|1
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|bh1
op_assign
id|bh
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|blocknr
op_assign
id|bh-&gt;b_blocknr
op_rshift
l_int|1
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|set_blocksize
c_func
(paren
id|dev
comma
l_int|2048
)paren
suffix:semicolon
id|sb-&gt;s_blocksize
op_assign
l_int|2048
suffix:semicolon
id|bh1
op_assign
id|bh
op_assign
id|sb_bread
c_func
(paren
id|sb
comma
id|blocknr
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_goto
id|Ebadsize
suffix:semicolon
)brace
r_if
c_cond
(paren
id|bh
op_logical_and
id|bh1
)paren
(brace
id|sb-&gt;sv_bh1
op_assign
id|bh1
suffix:semicolon
id|sb-&gt;sv_bh2
op_assign
id|bh
suffix:semicolon
r_if
c_cond
(paren
id|complete_read_super
c_func
(paren
id|sb
comma
id|silent
comma
id|size
)paren
)paren
r_return
id|sb
suffix:semicolon
)brace
id|brelse
c_func
(paren
id|bh1
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|set_blocksize
c_func
(paren
id|sb-&gt;s_dev
comma
id|BLOCK_SIZE
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;oldfs: cannot read superblock&bslash;n&quot;
)paren
suffix:semicolon
id|failed
suffix:colon
r_return
l_int|NULL
suffix:semicolon
id|Eunknown
suffix:colon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|silent
)paren
id|printk
c_func
(paren
l_string|&quot;VFS: unable to find oldfs superblock on device %s&bslash;n&quot;
comma
id|bdevname
c_func
(paren
id|dev
)paren
)paren
suffix:semicolon
r_goto
id|failed
suffix:semicolon
id|Ebadsize
suffix:colon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|silent
)paren
id|printk
c_func
(paren
l_string|&quot;VFS: oldfs: unsupported block size (%dKb)&bslash;n&quot;
comma
l_int|1
op_lshift
(paren
id|size
op_minus
l_int|2
)paren
)paren
suffix:semicolon
r_goto
id|failed
suffix:semicolon
)brace
DECL|function|v7_read_super
r_static
r_struct
id|super_block
op_star
id|v7_read_super
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_void
op_star
id|data
comma
r_int
id|silent
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh
comma
op_star
id|bh2
op_assign
l_int|NULL
suffix:semicolon
id|kdev_t
id|dev
op_assign
id|sb-&gt;s_dev
suffix:semicolon
r_struct
id|v7_super_block
op_star
id|v7sb
suffix:semicolon
r_struct
id|sysv_inode
op_star
id|v7i
suffix:semicolon
r_if
c_cond
(paren
l_int|440
op_ne
r_sizeof
(paren
r_struct
id|v7_super_block
)paren
)paren
id|panic
c_func
(paren
l_string|&quot;V7 FS: bad super-block size&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|64
op_ne
r_sizeof
(paren
r_struct
id|sysv_inode
)paren
)paren
id|panic
c_func
(paren
l_string|&quot;sysv fs: bad i-node size&quot;
)paren
suffix:semicolon
id|sb-&gt;sv_type
op_assign
id|FSTYPE_V7
suffix:semicolon
id|sb-&gt;sv_bytesex
op_assign
id|BYTESEX_PDP
suffix:semicolon
id|set_blocksize
c_func
(paren
id|dev
comma
l_int|512
)paren
suffix:semicolon
id|sb-&gt;s_blocksize
op_assign
l_int|512
suffix:semicolon
r_if
c_cond
(paren
(paren
id|bh
op_assign
id|sb_bread
c_func
(paren
id|sb
comma
l_int|1
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|silent
)paren
id|printk
c_func
(paren
l_string|&quot;VFS: unable to read V7 FS superblock on &quot;
l_string|&quot;device %s.&bslash;n&quot;
comma
id|bdevname
c_func
(paren
id|dev
)paren
)paren
suffix:semicolon
r_goto
id|failed
suffix:semicolon
)brace
multiline_comment|/* plausibility check on superblock */
id|v7sb
op_assign
(paren
r_struct
id|v7_super_block
op_star
)paren
id|bh-&gt;b_data
suffix:semicolon
r_if
c_cond
(paren
id|fs16_to_cpu
c_func
(paren
id|sb
comma
id|v7sb-&gt;s_nfree
)paren
OG
id|V7_NICFREE
op_logical_or
id|fs16_to_cpu
c_func
(paren
id|sb
comma
id|v7sb-&gt;s_ninode
)paren
OG
id|V7_NICINOD
op_logical_or
id|fs32_to_cpu
c_func
(paren
id|sb
comma
id|v7sb-&gt;s_time
)paren
op_eq
l_int|0
)paren
r_goto
id|failed
suffix:semicolon
multiline_comment|/* plausibility check on root inode: it is a directory,&n;&t;   with a nonzero size that is a multiple of 16 */
r_if
c_cond
(paren
(paren
id|bh2
op_assign
id|sb_bread
c_func
(paren
id|sb
comma
l_int|2
)paren
)paren
op_eq
l_int|NULL
)paren
r_goto
id|failed
suffix:semicolon
id|v7i
op_assign
(paren
r_struct
id|sysv_inode
op_star
)paren
(paren
id|bh2-&gt;b_data
op_plus
l_int|64
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|fs16_to_cpu
c_func
(paren
id|sb
comma
id|v7i-&gt;i_mode
)paren
op_amp
op_complement
l_int|0777
)paren
op_ne
id|S_IFDIR
op_logical_or
(paren
id|fs32_to_cpu
c_func
(paren
id|sb
comma
id|v7i-&gt;i_size
)paren
op_eq
l_int|0
)paren
op_logical_or
(paren
id|fs32_to_cpu
c_func
(paren
id|sb
comma
id|v7i-&gt;i_size
)paren
op_amp
l_int|017
)paren
op_ne
l_int|0
)paren
r_goto
id|failed
suffix:semicolon
id|brelse
c_func
(paren
id|bh2
)paren
suffix:semicolon
id|sb-&gt;sv_bh1
op_assign
id|bh
suffix:semicolon
id|sb-&gt;sv_bh2
op_assign
id|bh
suffix:semicolon
r_if
c_cond
(paren
id|complete_read_super
c_func
(paren
id|sb
comma
id|silent
comma
l_int|1
)paren
)paren
r_return
id|sb
suffix:semicolon
id|failed
suffix:colon
id|brelse
c_func
(paren
id|bh2
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* Every kernel module contains stuff like this. */
r_static
id|DECLARE_FSTYPE_DEV
c_func
(paren
id|sysv_fs_type
comma
l_string|&quot;sysv&quot;
comma
id|sysv_read_super
)paren
suffix:semicolon
r_static
id|DECLARE_FSTYPE_DEV
c_func
(paren
id|v7_fs_type
comma
l_string|&quot;v7&quot;
comma
id|v7_read_super
)paren
suffix:semicolon
DECL|function|init_sysv_fs
r_static
r_int
id|__init
id|init_sysv_fs
c_func
(paren
r_void
)paren
(brace
r_int
id|err
op_assign
id|register_filesystem
c_func
(paren
op_amp
id|sysv_fs_type
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|err
)paren
id|err
op_assign
id|register_filesystem
c_func
(paren
op_amp
id|v7_fs_type
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|exit_sysv_fs
r_static
r_void
id|__exit
id|exit_sysv_fs
c_func
(paren
r_void
)paren
(brace
id|unregister_filesystem
c_func
(paren
op_amp
id|sysv_fs_type
)paren
suffix:semicolon
id|unregister_filesystem
c_func
(paren
op_amp
id|v7_fs_type
)paren
suffix:semicolon
)brace
id|EXPORT_NO_SYMBOLS
suffix:semicolon
id|module_init
c_func
(paren
id|init_sysv_fs
)paren
id|module_exit
c_func
(paren
id|exit_sysv_fs
)paren
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
