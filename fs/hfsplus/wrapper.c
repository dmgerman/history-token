multiline_comment|/*&n; *  linux/fs/hfsplus/wrapper.c&n; *&n; * Copyright (C) 2001&n; * Brad Boyer (flar@allandria.com)&n; * (C) 2003 Ardis Technologies &lt;roman@ardistech.com&gt;&n; *&n; * Handling of HFS wrappers around HFS+ volumes&n; */
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/cdrom.h&gt;
macro_line|#include &lt;linux/genhd.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;asm/unaligned.h&gt;
macro_line|#include &quot;hfsplus_fs.h&quot;
macro_line|#include &quot;hfsplus_raw.h&quot;
DECL|struct|hfsplus_wd
r_struct
id|hfsplus_wd
(brace
DECL|member|ablk_size
id|u32
id|ablk_size
suffix:semicolon
DECL|member|ablk_start
id|u16
id|ablk_start
suffix:semicolon
DECL|member|embed_start
id|u16
id|embed_start
suffix:semicolon
DECL|member|embed_count
id|u16
id|embed_count
suffix:semicolon
)brace
suffix:semicolon
DECL|function|hfsplus_read_mdb
r_static
r_int
id|hfsplus_read_mdb
c_func
(paren
r_void
op_star
id|bufptr
comma
r_struct
id|hfsplus_wd
op_star
id|wd
)paren
(brace
id|u32
id|extent
suffix:semicolon
id|u16
id|attrib
suffix:semicolon
r_if
c_cond
(paren
id|be16_to_cpu
c_func
(paren
op_star
(paren
id|__be16
op_star
)paren
(paren
id|bufptr
op_plus
id|HFSP_WRAPOFF_EMBEDSIG
)paren
)paren
op_ne
id|HFSPLUS_VOLHEAD_SIG
)paren
r_return
l_int|0
suffix:semicolon
id|attrib
op_assign
id|be16_to_cpu
c_func
(paren
op_star
(paren
id|__be16
op_star
)paren
(paren
id|bufptr
op_plus
id|HFSP_WRAPOFF_ATTRIB
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|attrib
op_amp
id|HFSP_WRAP_ATTRIB_SLOCK
)paren
op_logical_or
op_logical_neg
(paren
id|attrib
op_amp
id|HFSP_WRAP_ATTRIB_SPARED
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|wd-&gt;ablk_size
op_assign
id|be32_to_cpu
c_func
(paren
op_star
(paren
id|__be32
op_star
)paren
(paren
id|bufptr
op_plus
id|HFSP_WRAPOFF_ABLKSIZE
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|wd-&gt;ablk_size
OL
id|HFSPLUS_SECTOR_SIZE
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|wd-&gt;ablk_size
op_mod
id|HFSPLUS_SECTOR_SIZE
)paren
r_return
l_int|0
suffix:semicolon
id|wd-&gt;ablk_start
op_assign
id|be16_to_cpu
c_func
(paren
op_star
(paren
id|__be16
op_star
)paren
(paren
id|bufptr
op_plus
id|HFSP_WRAPOFF_ABLKSTART
)paren
)paren
suffix:semicolon
id|extent
op_assign
id|be32_to_cpu
c_func
(paren
id|get_unaligned
c_func
(paren
(paren
id|__be32
op_star
)paren
(paren
id|bufptr
op_plus
id|HFSP_WRAPOFF_EMBEDEXT
)paren
)paren
)paren
suffix:semicolon
id|wd-&gt;embed_start
op_assign
(paren
id|extent
op_rshift
l_int|16
)paren
op_amp
l_int|0xFFFF
suffix:semicolon
id|wd-&gt;embed_count
op_assign
id|extent
op_amp
l_int|0xFFFF
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|hfsplus_get_last_session
r_static
r_int
id|hfsplus_get_last_session
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
id|sector_t
op_star
id|start
comma
id|sector_t
op_star
id|size
)paren
(brace
r_struct
id|cdrom_multisession
id|ms_info
suffix:semicolon
r_struct
id|cdrom_tocentry
id|te
suffix:semicolon
r_int
id|res
suffix:semicolon
multiline_comment|/* default values */
op_star
id|start
op_assign
l_int|0
suffix:semicolon
op_star
id|size
op_assign
id|sb-&gt;s_bdev-&gt;bd_inode-&gt;i_size
op_rshift
l_int|9
suffix:semicolon
r_if
c_cond
(paren
id|HFSPLUS_SB
c_func
(paren
id|sb
)paren
dot
id|session
op_ge
l_int|0
)paren
(brace
id|te.cdte_track
op_assign
id|HFSPLUS_SB
c_func
(paren
id|sb
)paren
dot
id|session
suffix:semicolon
id|te.cdte_format
op_assign
id|CDROM_LBA
suffix:semicolon
id|res
op_assign
id|ioctl_by_bdev
c_func
(paren
id|sb-&gt;s_bdev
comma
id|CDROMREADTOCENTRY
comma
(paren
r_int
r_int
)paren
op_amp
id|te
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|res
op_logical_and
(paren
id|te.cdte_ctrl
op_amp
id|CDROM_DATA_TRACK
)paren
op_eq
l_int|4
)paren
(brace
op_star
id|start
op_assign
(paren
id|sector_t
)paren
id|te.cdte_addr.lba
op_lshift
l_int|2
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;HFS: Invalid session number or type of track&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|ms_info.addr_format
op_assign
id|CDROM_LBA
suffix:semicolon
id|res
op_assign
id|ioctl_by_bdev
c_func
(paren
id|sb-&gt;s_bdev
comma
id|CDROMMULTISESSION
comma
(paren
r_int
r_int
)paren
op_amp
id|ms_info
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|res
op_logical_and
id|ms_info.xa_flag
)paren
op_star
id|start
op_assign
(paren
id|sector_t
)paren
id|ms_info.addr.lba
op_lshift
l_int|2
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Find the volume header and fill in some minimum bits in superblock */
multiline_comment|/* Takes in super block, returns true if good data read */
DECL|function|hfsplus_read_wrapper
r_int
id|hfsplus_read_wrapper
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
id|hfsplus_vh
op_star
id|vhdr
suffix:semicolon
r_struct
id|hfsplus_wd
id|wd
suffix:semicolon
id|sector_t
id|part_start
comma
id|part_size
suffix:semicolon
id|u32
id|blocksize
suffix:semicolon
id|blocksize
op_assign
id|sb_min_blocksize
c_func
(paren
id|sb
comma
id|HFSPLUS_SECTOR_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|blocksize
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|hfsplus_get_last_session
c_func
(paren
id|sb
comma
op_amp
id|part_start
comma
op_amp
id|part_size
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
id|bh
op_assign
id|sb_bread512
c_func
(paren
id|sb
comma
id|part_start
op_plus
id|HFSPLUS_VOLHEAD_SECTOR
comma
id|vhdr
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
r_return
op_minus
id|EIO
suffix:semicolon
r_if
c_cond
(paren
id|vhdr-&gt;signature
op_eq
id|cpu_to_be16
c_func
(paren
id|HFSP_WRAP_MAGIC
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|hfsplus_read_mdb
c_func
(paren
id|vhdr
comma
op_amp
id|wd
)paren
)paren
r_goto
id|error
suffix:semicolon
id|wd.ablk_size
op_rshift_assign
id|HFSPLUS_SECTOR_SHIFT
suffix:semicolon
id|part_start
op_add_assign
id|wd.ablk_start
op_plus
id|wd.embed_start
op_star
id|wd.ablk_size
suffix:semicolon
id|part_size
op_assign
id|wd.embed_count
op_star
id|wd.ablk_size
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|bh
op_assign
id|sb_bread512
c_func
(paren
id|sb
comma
id|part_start
op_plus
id|HFSPLUS_VOLHEAD_SECTOR
comma
id|vhdr
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_if
c_cond
(paren
id|vhdr-&gt;signature
op_eq
id|cpu_to_be16
c_func
(paren
id|HFSPLUS_VOLHEAD_SIG
)paren
)paren
r_break
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
multiline_comment|/* check for a partition block&n;&t;&t; * (should do this only for cdrom/loop though)&n;&t;&t; */
r_if
c_cond
(paren
id|hfs_part_find
c_func
(paren
id|sb
comma
op_amp
id|part_start
comma
op_amp
id|part_size
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|blocksize
op_assign
id|be32_to_cpu
c_func
(paren
id|vhdr-&gt;blocksize
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
multiline_comment|/* block size must be at least as large as a sector&n;&t; * and a multiple of 2&n;&t; */
r_if
c_cond
(paren
id|blocksize
OL
id|HFSPLUS_SECTOR_SIZE
op_logical_or
(paren
(paren
id|blocksize
op_minus
l_int|1
)paren
op_amp
id|blocksize
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|HFSPLUS_SB
c_func
(paren
id|sb
)paren
dot
id|alloc_blksz
op_assign
id|blocksize
suffix:semicolon
id|HFSPLUS_SB
c_func
(paren
id|sb
)paren
dot
id|alloc_blksz_shift
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
(paren
id|blocksize
op_rshift_assign
l_int|1
)paren
op_ne
l_int|0
)paren
id|HFSPLUS_SB
c_func
(paren
id|sb
)paren
dot
id|alloc_blksz_shift
op_increment
suffix:semicolon
id|blocksize
op_assign
id|min
c_func
(paren
id|HFSPLUS_SB
c_func
(paren
id|sb
)paren
dot
id|alloc_blksz
comma
(paren
id|u32
)paren
id|PAGE_SIZE
)paren
suffix:semicolon
multiline_comment|/* align block size to block offset */
r_while
c_loop
(paren
id|part_start
op_amp
(paren
(paren
id|blocksize
op_rshift
id|HFSPLUS_SECTOR_SHIFT
)paren
op_minus
l_int|1
)paren
)paren
id|blocksize
op_rshift_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|sb_set_blocksize
c_func
(paren
id|sb
comma
id|blocksize
)paren
op_ne
id|blocksize
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;HFS+: unable to blocksize to %u!&bslash;n&quot;
comma
id|blocksize
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|HFSPLUS_SB
c_func
(paren
id|sb
)paren
dot
id|blockoffset
op_assign
id|part_start
op_rshift
(paren
id|sb-&gt;s_blocksize_bits
op_minus
id|HFSPLUS_SECTOR_SHIFT
)paren
suffix:semicolon
id|HFSPLUS_SB
c_func
(paren
id|sb
)paren
dot
id|sect_count
op_assign
id|part_size
suffix:semicolon
id|HFSPLUS_SB
c_func
(paren
id|sb
)paren
dot
id|fs_shift
op_assign
id|HFSPLUS_SB
c_func
(paren
id|sb
)paren
dot
id|alloc_blksz_shift
op_minus
id|sb-&gt;s_blocksize_bits
suffix:semicolon
id|bh
op_assign
id|sb_bread512
c_func
(paren
id|sb
comma
id|part_start
op_plus
id|HFSPLUS_VOLHEAD_SECTOR
comma
id|vhdr
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
r_return
op_minus
id|EIO
suffix:semicolon
multiline_comment|/* should still be the same... */
r_if
c_cond
(paren
id|be16_to_cpu
c_func
(paren
id|vhdr-&gt;signature
)paren
op_ne
id|HFSPLUS_VOLHEAD_SIG
)paren
r_goto
id|error
suffix:semicolon
id|HFSPLUS_SB
c_func
(paren
id|sb
)paren
dot
id|s_vhbh
op_assign
id|bh
suffix:semicolon
id|HFSPLUS_SB
c_func
(paren
id|sb
)paren
dot
id|s_vhdr
op_assign
id|vhdr
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|error
suffix:colon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
eof
