multiline_comment|/*&n; * file.c&n; *&n; * PURPOSE&n; *  File handling routines for the OSTA-UDF(tm) filesystem.&n; *&n; * CONTACTS&n; *  E-mail regarding any portion of the Linux UDF file system should be&n; *  directed to the development team mailing list (run by majordomo):&n; *    linux_udf@hpesjro.fc.hp.com&n; *&n; * COPYRIGHT&n; *  This file is distributed under the terms of the GNU General Public&n; *  License (GPL). Copies of the GPL can be obtained from:&n; *    ftp://prep.ai.mit.edu/pub/gnu/GPL&n; *  Each contributing author retains all rights to their own work.&n; *&n; *  (C) 1998-1999 Dave Boynton&n; *  (C) 1998-2001 Ben Fennema&n; *  (C) 1999-2000 Stelias Computing Inc&n; *&n; * HISTORY&n; *&n; *  10/02/98 dgb  Attempt to integrate into udf.o&n; *  10/07/98      Switched to using generic_readpage, etc., like isofs&n; *                And it works!&n; *  12/06/98 blf  Added udf_file_read. uses generic_file_read for all cases but&n; *                ICBTAG_FLAG_AD_IN_ICB.&n; *  04/06/99      64 bit file handling on 32 bit systems taken from ext2 file.c&n; *  05/12/99      Preliminary file write support&n; */
macro_line|#include &quot;udfdecl.h&quot;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/udf_fs.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt; /* memset */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/locks.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &quot;udf_i.h&quot;
macro_line|#include &quot;udf_sb.h&quot;
DECL|function|udf_adinicb_readpage
r_static
r_int
id|udf_adinicb_readpage
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_struct
id|page
op_star
id|page
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|page-&gt;mapping-&gt;host
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_int
id|block
suffix:semicolon
r_char
op_star
id|kaddr
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|PageLocked
c_func
(paren
id|page
)paren
)paren
id|PAGE_BUG
c_func
(paren
id|page
)paren
suffix:semicolon
id|kaddr
op_assign
id|kmap
c_func
(paren
id|page
)paren
suffix:semicolon
id|memset
c_func
(paren
id|kaddr
comma
l_int|0
comma
id|PAGE_CACHE_SIZE
)paren
suffix:semicolon
id|block
op_assign
id|udf_get_lb_pblock
c_func
(paren
id|inode-&gt;i_sb
comma
id|UDF_I_LOCATION
c_func
(paren
id|inode
)paren
comma
l_int|0
)paren
suffix:semicolon
id|bh
op_assign
id|sb_bread
c_func
(paren
id|inode-&gt;i_sb
comma
id|block
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
(brace
id|SetPageError
c_func
(paren
id|page
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|memcpy
c_func
(paren
id|kaddr
comma
id|bh-&gt;b_data
op_plus
id|udf_ext0_offset
c_func
(paren
id|inode
)paren
comma
id|inode-&gt;i_size
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|flush_dcache_page
c_func
(paren
id|page
)paren
suffix:semicolon
id|SetPageUptodate
c_func
(paren
id|page
)paren
suffix:semicolon
id|out
suffix:colon
id|kunmap
c_func
(paren
id|page
)paren
suffix:semicolon
id|unlock_page
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|udf_adinicb_writepage
r_static
r_int
id|udf_adinicb_writepage
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|page-&gt;mapping-&gt;host
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_int
id|block
suffix:semicolon
r_char
op_star
id|kaddr
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|PageLocked
c_func
(paren
id|page
)paren
)paren
id|PAGE_BUG
c_func
(paren
id|page
)paren
suffix:semicolon
id|kaddr
op_assign
id|kmap
c_func
(paren
id|page
)paren
suffix:semicolon
id|block
op_assign
id|udf_get_lb_pblock
c_func
(paren
id|inode-&gt;i_sb
comma
id|UDF_I_LOCATION
c_func
(paren
id|inode
)paren
comma
l_int|0
)paren
suffix:semicolon
id|bh
op_assign
id|sb_bread
c_func
(paren
id|inode-&gt;i_sb
comma
id|block
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
(brace
id|SetPageError
c_func
(paren
id|page
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|memcpy
c_func
(paren
id|bh-&gt;b_data
op_plus
id|udf_ext0_offset
c_func
(paren
id|inode
)paren
comma
id|kaddr
comma
id|inode-&gt;i_size
)paren
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|bh
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|SetPageUptodate
c_func
(paren
id|page
)paren
suffix:semicolon
id|out
suffix:colon
id|kunmap
c_func
(paren
id|page
)paren
suffix:semicolon
id|unlock_page
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|udf_adinicb_prepare_write
r_static
r_int
id|udf_adinicb_prepare_write
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_struct
id|page
op_star
id|page
comma
r_int
id|offset
comma
r_int
id|to
)paren
(brace
id|kmap
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|udf_adinicb_commit_write
r_static
r_int
id|udf_adinicb_commit_write
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_struct
id|page
op_star
id|page
comma
r_int
id|offset
comma
r_int
id|to
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|page-&gt;mapping-&gt;host
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_int
id|block
suffix:semicolon
r_char
op_star
id|kaddr
op_assign
id|page_address
c_func
(paren
id|page
)paren
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
id|block
op_assign
id|udf_get_lb_pblock
c_func
(paren
id|inode-&gt;i_sb
comma
id|UDF_I_LOCATION
c_func
(paren
id|inode
)paren
comma
l_int|0
)paren
suffix:semicolon
id|bh
op_assign
id|sb_bread
c_func
(paren
id|inode-&gt;i_sb
comma
id|block
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
(brace
id|SetPageError
c_func
(paren
id|page
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|memcpy
c_func
(paren
id|bh-&gt;b_data
op_plus
id|udf_file_entry_alloc_offset
c_func
(paren
id|inode
)paren
op_plus
id|offset
comma
id|kaddr
op_plus
id|offset
comma
id|to
op_minus
id|offset
)paren
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|bh
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|SetPageUptodate
c_func
(paren
id|page
)paren
suffix:semicolon
id|out
suffix:colon
id|kunmap
c_func
(paren
id|page
)paren
suffix:semicolon
multiline_comment|/* only one page here */
r_if
c_cond
(paren
id|to
OG
id|inode-&gt;i_size
)paren
id|inode-&gt;i_size
op_assign
id|to
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|variable|udf_adinicb_aops
r_struct
id|address_space_operations
id|udf_adinicb_aops
op_assign
(brace
id|readpage
suffix:colon
id|udf_adinicb_readpage
comma
id|writepage
suffix:colon
id|udf_adinicb_writepage
comma
id|sync_page
suffix:colon
id|block_sync_page
comma
id|prepare_write
suffix:colon
id|udf_adinicb_prepare_write
comma
id|commit_write
suffix:colon
id|udf_adinicb_commit_write
comma
)brace
suffix:semicolon
DECL|function|udf_file_write
r_static
id|ssize_t
id|udf_file_write
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|ppos
)paren
(brace
id|ssize_t
id|retval
suffix:semicolon
r_struct
id|inode
op_star
id|inode
op_assign
id|file-&gt;f_dentry-&gt;d_inode
suffix:semicolon
r_int
id|err
comma
id|pos
suffix:semicolon
r_if
c_cond
(paren
id|UDF_I_ALLOCTYPE
c_func
(paren
id|inode
)paren
op_eq
id|ICBTAG_FLAG_AD_IN_ICB
)paren
(brace
r_if
c_cond
(paren
id|file-&gt;f_flags
op_amp
id|O_APPEND
)paren
id|pos
op_assign
id|inode-&gt;i_size
suffix:semicolon
r_else
id|pos
op_assign
op_star
id|ppos
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;i_sb-&gt;s_blocksize
OL
(paren
id|udf_file_entry_alloc_offset
c_func
(paren
id|inode
)paren
op_plus
id|pos
op_plus
id|count
)paren
)paren
(brace
id|udf_expand_file_adinicb
c_func
(paren
id|inode
comma
id|pos
op_plus
id|count
comma
op_amp
id|err
)paren
suffix:semicolon
r_if
c_cond
(paren
id|UDF_I_ALLOCTYPE
c_func
(paren
id|inode
)paren
op_eq
id|ICBTAG_FLAG_AD_IN_ICB
)paren
(brace
id|udf_debug
c_func
(paren
l_string|&quot;udf_expand_adinicb: err=%d&bslash;n&quot;
comma
id|err
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
)brace
r_else
(brace
r_if
c_cond
(paren
id|pos
op_plus
id|count
OG
id|inode-&gt;i_size
)paren
id|UDF_I_LENALLOC
c_func
(paren
id|inode
)paren
op_assign
id|pos
op_plus
id|count
suffix:semicolon
r_else
id|UDF_I_LENALLOC
c_func
(paren
id|inode
)paren
op_assign
id|inode-&gt;i_size
suffix:semicolon
)brace
)brace
id|retval
op_assign
id|generic_file_write
c_func
(paren
id|file
comma
id|buf
comma
id|count
comma
id|ppos
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
OG
l_int|0
)paren
(brace
id|UDF_I_UCTIME
c_func
(paren
id|inode
)paren
op_assign
id|UDF_I_UMTIME
c_func
(paren
id|inode
)paren
op_assign
id|CURRENT_UTIME
suffix:semicolon
id|mark_inode_dirty
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/*&n; * udf_ioctl&n; *&n; * PURPOSE&n; *&t;Issue an ioctl.&n; *&n; * DESCRIPTION&n; *&t;Optional - sys_ioctl() will return -ENOTTY if this routine is not&n; *&t;available, and the ioctl cannot be handled without filesystem help.&n; *&n; *&t;sys_ioctl() handles these ioctls that apply only to regular files:&n; *&t;&t;FIBMAP [requires udf_block_map()], FIGETBSZ, FIONREAD&n; *&t;These ioctls are also handled by sys_ioctl():&n; *&t;&t;FIOCLEX, FIONCLEX, FIONBIO, FIOASYNC&n; *&t;All other ioctls are passed to the filesystem.&n; *&n; *&t;Refer to sys_ioctl() in fs/ioctl.c&n; *&t;sys_ioctl() -&gt; .&n; *&n; * PRE-CONDITIONS&n; *&t;inode&t;&t;&t;Pointer to inode that ioctl was issued on.&n; *&t;filp&t;&t;&t;Pointer to file that ioctl was issued on.&n; *&t;cmd&t;&t;&t;The ioctl command.&n; *&t;arg&t;&t;&t;The ioctl argument [can be interpreted as a&n; *&t;&t;&t;&t;user-space pointer if desired].&n; *&n; * POST-CONDITIONS&n; *&t;&lt;return&gt;&t;&t;Success (&gt;=0) or an error code (&lt;=0) that&n; *&t;&t;&t;&t;sys_ioctl() will return.&n; *&n; * HISTORY&n; *&t;July 1, 1997 - Andrew E. Mileski&n; *&t;Written, tested, and released.&n; */
DECL|function|udf_ioctl
r_int
id|udf_ioctl
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|filp
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
r_int
id|result
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
op_assign
l_int|NULL
suffix:semicolon
id|long_ad
id|eaicb
suffix:semicolon
r_uint8
op_star
id|ea
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|permission
c_func
(paren
id|inode
comma
id|MAY_READ
)paren
op_ne
l_int|0
)paren
(brace
id|udf_debug
c_func
(paren
l_string|&quot;no permission to access inode %lu&bslash;n&quot;
comma
id|inode-&gt;i_ino
)paren
suffix:semicolon
r_return
op_minus
id|EPERM
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|arg
)paren
(brace
id|udf_debug
c_func
(paren
l_string|&quot;invalid argument to udf_ioctl&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/* first, do ioctls that don&squot;t need to udf_read */
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|UDF_GETVOLIDENT
suffix:colon
r_return
id|copy_to_user
c_func
(paren
(paren
r_char
op_star
)paren
id|arg
comma
id|UDF_SB_VOLIDENT
c_func
(paren
id|inode-&gt;i_sb
)paren
comma
l_int|32
)paren
ques
c_cond
op_minus
id|EFAULT
suffix:colon
l_int|0
suffix:semicolon
r_case
id|UDF_RELOCATE_BLOCKS
suffix:colon
(brace
r_int
id|old
comma
r_new
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
)paren
r_return
op_minus
id|EACCES
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|old
comma
(paren
r_int
op_star
)paren
id|arg
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
(paren
id|result
op_assign
id|udf_relocate_blocks
c_func
(paren
id|inode-&gt;i_sb
comma
id|old
comma
op_amp
r_new
)paren
)paren
op_eq
l_int|0
)paren
id|result
op_assign
id|put_user
c_func
(paren
r_new
comma
(paren
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
)brace
multiline_comment|/* ok, we need to read the inode */
id|bh
op_assign
id|udf_tread
c_func
(paren
id|inode-&gt;i_sb
comma
id|udf_get_lb_pblock
c_func
(paren
id|inode-&gt;i_sb
comma
id|UDF_I_LOCATION
c_func
(paren
id|inode
)paren
comma
l_int|0
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
(brace
id|udf_debug
c_func
(paren
l_string|&quot;bread failed (inode=%ld)&bslash;n&quot;
comma
id|inode-&gt;i_ino
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
id|UDF_I_EXTENDED_FE
c_func
(paren
id|inode
)paren
op_eq
l_int|0
)paren
(brace
r_struct
id|fileEntry
op_star
id|fe
suffix:semicolon
id|fe
op_assign
(paren
r_struct
id|fileEntry
op_star
)paren
id|bh-&gt;b_data
suffix:semicolon
id|eaicb
op_assign
id|lela_to_cpu
c_func
(paren
id|fe-&gt;extendedAttrICB
)paren
suffix:semicolon
r_if
c_cond
(paren
id|UDF_I_LENEATTR
c_func
(paren
id|inode
)paren
)paren
id|ea
op_assign
id|fe-&gt;extendedAttr
suffix:semicolon
)brace
r_else
(brace
r_struct
id|extendedFileEntry
op_star
id|efe
suffix:semicolon
id|efe
op_assign
(paren
r_struct
id|extendedFileEntry
op_star
)paren
id|bh-&gt;b_data
suffix:semicolon
id|eaicb
op_assign
id|lela_to_cpu
c_func
(paren
id|efe-&gt;extendedAttrICB
)paren
suffix:semicolon
r_if
c_cond
(paren
id|UDF_I_LENEATTR
c_func
(paren
id|inode
)paren
)paren
id|ea
op_assign
id|efe-&gt;extendedAttr
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|UDF_GETEASIZE
suffix:colon
id|result
op_assign
id|put_user
c_func
(paren
id|UDF_I_LENEATTR
c_func
(paren
id|inode
)paren
comma
(paren
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|UDF_GETEABLOCK
suffix:colon
id|result
op_assign
id|copy_to_user
c_func
(paren
(paren
r_char
op_star
)paren
id|arg
comma
id|ea
comma
id|UDF_I_LENEATTR
c_func
(paren
id|inode
)paren
)paren
ques
c_cond
op_minus
id|EFAULT
suffix:colon
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
id|udf_release_data
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
multiline_comment|/*&n; * udf_release_file&n; *&n; * PURPOSE&n; *  Called when all references to the file are closed&n; *&n; * DESCRIPTION&n; *  Discard prealloced blocks&n; *&n; * HISTORY&n; *&n; */
DECL|function|udf_release_file
r_static
r_int
id|udf_release_file
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|filp
)paren
(brace
r_if
c_cond
(paren
id|filp-&gt;f_mode
op_amp
id|FMODE_WRITE
)paren
(brace
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|udf_discard_prealloc
c_func
(paren
id|inode
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * udf_open_file&n; *&n; * PURPOSE&n; *  Called when an inode is about to be open.&n; *&n; * DESCRIPTION&n; *  Use this to disallow opening RW large files on 32 bit systems.&n; *  On 64 bit systems we force on O_LARGEFILE in sys_open.&n; *&n; * HISTORY&n; *&n; */
DECL|function|udf_open_file
r_static
r_int
id|udf_open_file
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|filp
)paren
(brace
r_if
c_cond
(paren
(paren
id|inode-&gt;i_size
op_amp
l_int|0xFFFFFFFF80000000ULL
)paren
op_logical_and
op_logical_neg
(paren
id|filp-&gt;f_flags
op_amp
id|O_LARGEFILE
)paren
)paren
r_return
op_minus
id|EFBIG
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|udf_file_operations
r_struct
id|file_operations
id|udf_file_operations
op_assign
(brace
id|read
suffix:colon
id|generic_file_read
comma
id|ioctl
suffix:colon
id|udf_ioctl
comma
id|open
suffix:colon
id|udf_open_file
comma
id|mmap
suffix:colon
id|generic_file_mmap
comma
id|write
suffix:colon
id|udf_file_write
comma
id|release
suffix:colon
id|udf_release_file
comma
id|fsync
suffix:colon
id|udf_fsync_file
comma
)brace
suffix:semicolon
DECL|variable|udf_file_inode_operations
r_struct
id|inode_operations
id|udf_file_inode_operations
op_assign
(brace
id|truncate
suffix:colon
id|udf_truncate
comma
)brace
suffix:semicolon
eof
