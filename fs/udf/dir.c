multiline_comment|/*&n; * dir.c&n; *&n; * PURPOSE&n; *  Directory handling routines for the OSTA-UDF(tm) filesystem.&n; *&n; * CONTACTS&n; *&t;E-mail regarding any portion of the Linux UDF file system should be&n; *&t;directed to the development team mailing list (run by majordomo):&n; *&t;&t;linux_udf@hpesjro.fc.hp.com&n; *&n; * COPYRIGHT&n; *&t;This file is distributed under the terms of the GNU General Public&n; *&t;License (GPL). Copies of the GPL can be obtained from:&n; *&t;&t;ftp://prep.ai.mit.edu/pub/gnu/GPL&n; *&t;Each contributing author retains all rights to their own work.&n; *&n; *  (C) 1998-2001 Ben Fennema&n; *&n; * HISTORY&n; *&n; *  10/05/98 dgb  Split directory operations into its own file&n; *                Implemented directory reads via do_udf_readdir&n; *  10/06/98      Made directory operations work!&n; *  11/17/98      Rewrote directory to support ICBTAG_FLAG_AD_LONG&n; *  11/25/98 blf  Rewrote directory handling (readdir+lookup) to support reading&n; *                across blocks.&n; *  12/12/98      Split out the lookup code to namei.c. bulk of directory&n; *                code now in directory.c:udf_fileident_read.&n; */
macro_line|#include &quot;udfdecl.h&quot;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/buffer_head.h&gt;
macro_line|#include &quot;udf_i.h&quot;
macro_line|#include &quot;udf_sb.h&quot;
multiline_comment|/* Prototypes for file operations */
r_static
r_int
id|udf_readdir
c_func
(paren
r_struct
id|file
op_star
comma
r_void
op_star
comma
id|filldir_t
)paren
suffix:semicolon
r_static
r_int
id|do_udf_readdir
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
comma
id|filldir_t
comma
r_void
op_star
)paren
suffix:semicolon
multiline_comment|/* readdir and lookup functions */
DECL|variable|udf_dir_operations
r_struct
id|file_operations
id|udf_dir_operations
op_assign
(brace
dot
id|read
op_assign
id|generic_read_dir
comma
dot
id|readdir
op_assign
id|udf_readdir
comma
dot
id|ioctl
op_assign
id|udf_ioctl
comma
dot
id|fsync
op_assign
id|udf_fsync_file
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * udf_readdir&n; *&n; * PURPOSE&n; *&t;Read a directory entry.&n; *&n; * DESCRIPTION&n; *&t;Optional - sys_getdents() will return -ENOTDIR if this routine is not&n; *&t;available.&n; *&n; *&t;Refer to sys_getdents() in fs/readdir.c&n; *&t;sys_getdents() -&gt; .&n; *&n; * PRE-CONDITIONS&n; *&t;filp&t;&t;&t;Pointer to directory file.&n; *&t;buf&t;&t;&t;Pointer to directory entry buffer.&n; *&t;filldir&t;&t;&t;Pointer to filldir function.&n; *&n; * POST-CONDITIONS&n; *&t;&lt;return&gt;&t;&t;&gt;=0 on success.&n; *&n; * HISTORY&n; *&t;July 1, 1997 - Andrew E. Mileski&n; *&t;Written, tested, and released.&n; */
DECL|function|udf_readdir
r_int
id|udf_readdir
c_func
(paren
r_struct
id|file
op_star
id|filp
comma
r_void
op_star
id|dirent
comma
id|filldir_t
id|filldir
)paren
(brace
r_struct
id|inode
op_star
id|dir
op_assign
id|filp-&gt;f_dentry-&gt;d_inode
suffix:semicolon
r_int
id|result
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|filp-&gt;f_pos
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|filldir
c_func
(paren
id|dirent
comma
l_string|&quot;.&quot;
comma
l_int|1
comma
id|filp-&gt;f_pos
comma
id|dir-&gt;i_ino
comma
id|DT_DIR
)paren
OL
l_int|0
)paren
(brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|filp-&gt;f_pos
op_increment
suffix:semicolon
)brace
id|result
op_assign
id|do_udf_readdir
c_func
(paren
id|dir
comma
id|filp
comma
id|filldir
comma
id|dirent
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
r_static
r_int
DECL|function|do_udf_readdir
id|do_udf_readdir
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_struct
id|file
op_star
id|filp
comma
id|filldir_t
id|filldir
comma
r_void
op_star
id|dirent
)paren
(brace
r_struct
id|udf_fileident_bh
id|fibh
suffix:semicolon
r_struct
id|fileIdentDesc
op_star
id|fi
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|fileIdentDesc
id|cfi
suffix:semicolon
r_int
id|block
comma
id|iblock
suffix:semicolon
id|loff_t
id|nf_pos
op_assign
id|filp-&gt;f_pos
op_minus
l_int|1
suffix:semicolon
r_int
id|flen
suffix:semicolon
r_char
id|fname
(braket
l_int|255
)braket
suffix:semicolon
r_char
op_star
id|nameptr
suffix:semicolon
r_uint16
id|liu
suffix:semicolon
r_uint8
id|lfi
suffix:semicolon
id|loff_t
id|size
op_assign
(paren
id|udf_ext0_offset
c_func
(paren
id|dir
)paren
op_plus
id|dir-&gt;i_size
)paren
op_rshift
l_int|2
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
op_assign
l_int|NULL
comma
op_star
id|tmp
comma
op_star
id|bha
(braket
l_int|16
)braket
suffix:semicolon
id|lb_addr
id|bloc
comma
id|eloc
suffix:semicolon
r_uint32
id|extoffset
comma
id|elen
comma
id|offset
suffix:semicolon
r_int
id|i
comma
id|num
suffix:semicolon
r_int
r_int
id|dt_type
suffix:semicolon
r_if
c_cond
(paren
id|nf_pos
op_ge
id|size
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|nf_pos
op_eq
l_int|0
)paren
id|nf_pos
op_assign
(paren
id|udf_ext0_offset
c_func
(paren
id|dir
)paren
op_rshift
l_int|2
)paren
suffix:semicolon
id|fibh.soffset
op_assign
id|fibh.eoffset
op_assign
(paren
id|nf_pos
op_amp
(paren
(paren
id|dir-&gt;i_sb-&gt;s_blocksize
op_minus
l_int|1
)paren
op_rshift
l_int|2
)paren
)paren
op_lshift
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|UDF_I_ALLOCTYPE
c_func
(paren
id|dir
)paren
op_eq
id|ICBTAG_FLAG_AD_IN_ICB
)paren
id|fibh.sbh
op_assign
id|fibh.ebh
op_assign
l_int|NULL
suffix:semicolon
r_else
r_if
c_cond
(paren
id|inode_bmap
c_func
(paren
id|dir
comma
id|nf_pos
op_rshift
(paren
id|dir-&gt;i_sb-&gt;s_blocksize_bits
op_minus
l_int|2
)paren
comma
op_amp
id|bloc
comma
op_amp
id|extoffset
comma
op_amp
id|eloc
comma
op_amp
id|elen
comma
op_amp
id|offset
comma
op_amp
id|bh
)paren
op_eq
(paren
id|EXT_RECORDED_ALLOCATED
op_rshift
l_int|30
)paren
)paren
(brace
id|offset
op_rshift_assign
id|dir-&gt;i_sb-&gt;s_blocksize_bits
suffix:semicolon
id|block
op_assign
id|udf_get_lb_pblock
c_func
(paren
id|dir-&gt;i_sb
comma
id|eloc
comma
id|offset
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
op_increment
id|offset
op_lshift
id|dir-&gt;i_sb-&gt;s_blocksize_bits
)paren
OL
id|elen
)paren
(brace
r_if
c_cond
(paren
id|UDF_I_ALLOCTYPE
c_func
(paren
id|dir
)paren
op_eq
id|ICBTAG_FLAG_AD_SHORT
)paren
id|extoffset
op_sub_assign
r_sizeof
(paren
id|short_ad
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|UDF_I_ALLOCTYPE
c_func
(paren
id|dir
)paren
op_eq
id|ICBTAG_FLAG_AD_LONG
)paren
id|extoffset
op_sub_assign
r_sizeof
(paren
id|long_ad
)paren
suffix:semicolon
)brace
r_else
id|offset
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|fibh.sbh
op_assign
id|fibh.ebh
op_assign
id|udf_tread
c_func
(paren
id|dir-&gt;i_sb
comma
id|block
)paren
)paren
)paren
(brace
id|udf_release_data
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|offset
op_amp
(paren
(paren
l_int|16
op_rshift
(paren
id|dir-&gt;i_sb-&gt;s_blocksize_bits
op_minus
l_int|9
)paren
)paren
op_minus
l_int|1
)paren
)paren
)paren
(brace
id|i
op_assign
l_int|16
op_rshift
(paren
id|dir-&gt;i_sb-&gt;s_blocksize_bits
op_minus
l_int|9
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
op_plus
id|offset
OG
(paren
id|elen
op_rshift
id|dir-&gt;i_sb-&gt;s_blocksize_bits
)paren
)paren
id|i
op_assign
(paren
id|elen
op_rshift
id|dir-&gt;i_sb-&gt;s_blocksize_bits
)paren
op_minus
id|offset
suffix:semicolon
r_for
c_loop
(paren
id|num
op_assign
l_int|0
suffix:semicolon
id|i
OG
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
(brace
id|block
op_assign
id|udf_get_lb_pblock
c_func
(paren
id|dir-&gt;i_sb
comma
id|eloc
comma
id|offset
op_plus
id|i
)paren
suffix:semicolon
id|tmp
op_assign
id|udf_tgetblk
c_func
(paren
id|dir-&gt;i_sb
comma
id|block
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_logical_and
op_logical_neg
id|buffer_uptodate
c_func
(paren
id|tmp
)paren
op_logical_and
op_logical_neg
id|buffer_locked
c_func
(paren
id|tmp
)paren
)paren
id|bha
(braket
id|num
op_increment
)braket
op_assign
id|tmp
suffix:semicolon
r_else
id|brelse
c_func
(paren
id|tmp
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|num
)paren
(brace
id|ll_rw_block
c_func
(paren
id|READA
comma
id|num
comma
id|bha
)paren
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
id|num
suffix:semicolon
id|i
op_increment
)paren
id|brelse
c_func
(paren
id|bha
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
)brace
)brace
r_else
(brace
id|udf_release_data
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
op_minus
id|ENOENT
suffix:semicolon
)brace
r_while
c_loop
(paren
id|nf_pos
OL
id|size
)paren
(brace
id|filp-&gt;f_pos
op_assign
id|nf_pos
op_plus
l_int|1
suffix:semicolon
id|fi
op_assign
id|udf_fileident_read
c_func
(paren
id|dir
comma
op_amp
id|nf_pos
comma
op_amp
id|fibh
comma
op_amp
id|cfi
comma
op_amp
id|bloc
comma
op_amp
id|extoffset
comma
op_amp
id|eloc
comma
op_amp
id|elen
comma
op_amp
id|offset
comma
op_amp
id|bh
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fi
)paren
(brace
r_if
c_cond
(paren
id|fibh.sbh
op_ne
id|fibh.ebh
)paren
id|udf_release_data
c_func
(paren
id|fibh.ebh
)paren
suffix:semicolon
id|udf_release_data
c_func
(paren
id|fibh.sbh
)paren
suffix:semicolon
id|udf_release_data
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|liu
op_assign
id|le16_to_cpu
c_func
(paren
id|cfi.lengthOfImpUse
)paren
suffix:semicolon
id|lfi
op_assign
id|cfi.lengthFileIdent
suffix:semicolon
r_if
c_cond
(paren
id|fibh.sbh
op_eq
id|fibh.ebh
)paren
id|nameptr
op_assign
id|fi-&gt;fileIdent
op_plus
id|liu
suffix:semicolon
r_else
(brace
r_int
id|poffset
suffix:semicolon
multiline_comment|/* Unpaded ending offset */
id|poffset
op_assign
id|fibh.soffset
op_plus
r_sizeof
(paren
r_struct
id|fileIdentDesc
)paren
op_plus
id|liu
op_plus
id|lfi
suffix:semicolon
r_if
c_cond
(paren
id|poffset
op_ge
id|lfi
)paren
id|nameptr
op_assign
(paren
r_char
op_star
)paren
(paren
id|fibh.ebh-&gt;b_data
op_plus
id|poffset
op_minus
id|lfi
)paren
suffix:semicolon
r_else
(brace
id|nameptr
op_assign
id|fname
suffix:semicolon
id|memcpy
c_func
(paren
id|nameptr
comma
id|fi-&gt;fileIdent
op_plus
id|liu
comma
id|lfi
op_minus
id|poffset
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|nameptr
op_plus
id|lfi
op_minus
id|poffset
comma
id|fibh.ebh-&gt;b_data
comma
id|poffset
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
(paren
id|cfi.fileCharacteristics
op_amp
id|FID_FILE_CHAR_DELETED
)paren
op_ne
l_int|0
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|UDF_QUERY_FLAG
c_func
(paren
id|dir-&gt;i_sb
comma
id|UDF_FLAG_UNDELETE
)paren
)paren
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|cfi.fileCharacteristics
op_amp
id|FID_FILE_CHAR_HIDDEN
)paren
op_ne
l_int|0
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|UDF_QUERY_FLAG
c_func
(paren
id|dir-&gt;i_sb
comma
id|UDF_FLAG_UNHIDE
)paren
)paren
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cfi.fileCharacteristics
op_amp
id|FID_FILE_CHAR_PARENT
)paren
(brace
id|iblock
op_assign
id|parent_ino
c_func
(paren
id|filp-&gt;f_dentry
)paren
suffix:semicolon
id|flen
op_assign
l_int|2
suffix:semicolon
id|memcpy
c_func
(paren
id|fname
comma
l_string|&quot;..&quot;
comma
id|flen
)paren
suffix:semicolon
id|dt_type
op_assign
id|DT_DIR
suffix:semicolon
)brace
r_else
(brace
id|iblock
op_assign
id|udf_get_lb_pblock
c_func
(paren
id|dir-&gt;i_sb
comma
id|lelb_to_cpu
c_func
(paren
id|cfi.icb.extLocation
)paren
comma
l_int|0
)paren
suffix:semicolon
id|flen
op_assign
id|udf_get_filename
c_func
(paren
id|dir-&gt;i_sb
comma
id|nameptr
comma
id|fname
comma
id|lfi
)paren
suffix:semicolon
id|dt_type
op_assign
id|DT_UNKNOWN
suffix:semicolon
)brace
r_if
c_cond
(paren
id|flen
)paren
(brace
r_if
c_cond
(paren
id|filldir
c_func
(paren
id|dirent
comma
id|fname
comma
id|flen
comma
id|filp-&gt;f_pos
comma
id|iblock
comma
id|dt_type
)paren
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|fibh.sbh
op_ne
id|fibh.ebh
)paren
id|udf_release_data
c_func
(paren
id|fibh.ebh
)paren
suffix:semicolon
id|udf_release_data
c_func
(paren
id|fibh.sbh
)paren
suffix:semicolon
id|udf_release_data
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/* end while */
id|filp-&gt;f_pos
op_assign
id|nf_pos
op_plus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|fibh.sbh
op_ne
id|fibh.ebh
)paren
id|udf_release_data
c_func
(paren
id|fibh.ebh
)paren
suffix:semicolon
id|udf_release_data
c_func
(paren
id|fibh.sbh
)paren
suffix:semicolon
id|udf_release_data
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
