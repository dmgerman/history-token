multiline_comment|/*&n; * support.c -  Specific support functions&n; *&n; * Copyright (C) 1997 Martin von L&#xfffd;wis&n; * Copyright (C) 1997 R&#xfffd;gis Duchesne&n; * Copyright (C) 2001 Anton Altaparmakov (AIA)&n; */
macro_line|#include &quot;ntfstypes.h&quot;
macro_line|#include &quot;struct.h&quot;
macro_line|#include &quot;support.h&quot;
macro_line|#include &lt;stdarg.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/locks.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &quot;util.h&quot;
macro_line|#include &quot;inode.h&quot;
macro_line|#include &quot;macros.h&quot;
macro_line|#include &lt;linux/nls.h&gt;
DECL|variable|print_buf
r_static
r_char
id|print_buf
(braket
l_int|1024
)braket
suffix:semicolon
macro_line|#ifdef DEBUG
macro_line|#include &quot;sysctl.h&quot;
macro_line|#include &lt;linux/kernel.h&gt;
multiline_comment|/* Debugging output */
DECL|function|ntfs_debug
r_void
id|ntfs_debug
c_func
(paren
r_int
id|mask
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
id|ap
suffix:semicolon
multiline_comment|/* Filter it with the debugging level required */
r_if
c_cond
(paren
id|ntdebug
op_amp
id|mask
)paren
(brace
id|va_start
c_func
(paren
id|ap
comma
id|fmt
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|print_buf
comma
id|KERN_DEBUG
l_string|&quot;NTFS: &quot;
)paren
suffix:semicolon
id|vsprintf
c_func
(paren
id|print_buf
op_plus
l_int|9
comma
id|fmt
comma
id|ap
)paren
suffix:semicolon
id|printk
c_func
(paren
id|print_buf
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|ap
)paren
suffix:semicolon
)brace
)brace
macro_line|#ifndef ntfs_malloc
multiline_comment|/* Verbose kmalloc */
DECL|function|ntfs_malloc
r_void
op_star
id|ntfs_malloc
c_func
(paren
r_int
id|size
)paren
(brace
r_void
op_star
id|ret
suffix:semicolon
id|ret
op_assign
id|kmalloc
c_func
(paren
id|size
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|ntfs_debug
c_func
(paren
id|DEBUG_MALLOC
comma
l_string|&quot;Allocating %x at %p&bslash;n&quot;
comma
id|size
comma
id|ret
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifndef ntfs_free
multiline_comment|/* Verbose kfree() */
DECL|function|ntfs_free
r_void
id|ntfs_free
c_func
(paren
r_void
op_star
id|block
)paren
(brace
id|ntfs_debug
c_func
(paren
id|DEBUG_MALLOC
comma
l_string|&quot;Freeing memory at %p&bslash;n&quot;
comma
id|block
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|block
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#else /* End of DEBUG functions. Normal ones below... */
macro_line|#ifndef ntfs_malloc
DECL|function|ntfs_malloc
r_void
op_star
id|ntfs_malloc
c_func
(paren
r_int
id|size
)paren
(brace
r_return
id|kmalloc
c_func
(paren
id|size
comma
id|GFP_KERNEL
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifndef ntfs_free
DECL|function|ntfs_free
r_void
id|ntfs_free
c_func
(paren
r_void
op_star
id|block
)paren
(brace
id|kfree
c_func
(paren
id|block
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#endif /* DEBUG */
DECL|function|ntfs_bzero
r_void
id|ntfs_bzero
c_func
(paren
r_void
op_star
id|s
comma
r_int
id|n
)paren
(brace
id|memset
c_func
(paren
id|s
comma
l_int|0
comma
id|n
)paren
suffix:semicolon
)brace
multiline_comment|/* These functions deliberately return no value. It is dest, anyway,&n;   and not used anywhere in the NTFS code.  */
DECL|function|ntfs_memcpy
r_void
id|ntfs_memcpy
c_func
(paren
r_void
op_star
id|dest
comma
r_const
r_void
op_star
id|src
comma
id|ntfs_size_t
id|n
)paren
(brace
id|memcpy
c_func
(paren
id|dest
comma
id|src
comma
id|n
)paren
suffix:semicolon
)brace
DECL|function|ntfs_memmove
r_void
id|ntfs_memmove
c_func
(paren
r_void
op_star
id|dest
comma
r_const
r_void
op_star
id|src
comma
id|ntfs_size_t
id|n
)paren
(brace
id|memmove
c_func
(paren
id|dest
comma
id|src
comma
id|n
)paren
suffix:semicolon
)brace
multiline_comment|/* Warn that an error occurred. */
DECL|function|ntfs_error
r_void
id|ntfs_error
c_func
(paren
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
id|ap
suffix:semicolon
id|va_start
c_func
(paren
id|ap
comma
id|fmt
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|print_buf
comma
id|KERN_ERR
l_string|&quot;NTFS: &quot;
)paren
suffix:semicolon
id|vsprintf
c_func
(paren
id|print_buf
op_plus
l_int|9
comma
id|fmt
comma
id|ap
)paren
suffix:semicolon
id|printk
c_func
(paren
id|print_buf
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|ap
)paren
suffix:semicolon
)brace
DECL|function|ntfs_read_mft_record
r_int
id|ntfs_read_mft_record
c_func
(paren
id|ntfs_volume
op_star
id|vol
comma
r_int
id|mftno
comma
r_char
op_star
id|buf
)paren
(brace
r_int
id|error
suffix:semicolon
id|ntfs_io
id|io
suffix:semicolon
id|ntfs_debug
c_func
(paren
id|DEBUG_OTHER
comma
l_string|&quot;read_mft_record 0x%x&bslash;n&quot;
comma
id|mftno
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mftno
op_eq
id|FILE_Mft
)paren
(brace
id|ntfs_memcpy
c_func
(paren
id|buf
comma
id|vol-&gt;mft
comma
id|vol-&gt;mft_record_size
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|vol-&gt;mft_ino
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;NTFS: mft_ino is NULL. Something is terribly &quot;
l_string|&quot;wrong here!&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODATA
suffix:semicolon
)brace
id|io.fn_put
op_assign
id|ntfs_put
suffix:semicolon
id|io.fn_get
op_assign
l_int|0
suffix:semicolon
id|io.param
op_assign
id|buf
suffix:semicolon
id|io.size
op_assign
id|vol-&gt;mft_record_size
suffix:semicolon
id|ntfs_debug
c_func
(paren
id|DEBUG_OTHER
comma
l_string|&quot;read_mft_record: calling ntfs_read_attr with: &quot;
l_string|&quot;mftno = 0x%x, vol-&gt;mft_record_size_bits = 0x%x, &quot;
l_string|&quot;mftno &lt;&lt; vol-&gt;mft_record_size_bits = 0x%Lx&bslash;n&quot;
comma
id|mftno
comma
id|vol-&gt;mft_record_size_bits
comma
(paren
id|__s64
)paren
id|mftno
op_lshift
id|vol-&gt;mft_record_size_bits
)paren
suffix:semicolon
id|error
op_assign
id|ntfs_read_attr
c_func
(paren
id|vol-&gt;mft_ino
comma
id|vol-&gt;at_data
comma
l_int|NULL
comma
(paren
id|__s64
)paren
id|mftno
op_lshift
id|vol-&gt;mft_record_size_bits
comma
op_amp
id|io
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
op_logical_or
(paren
id|io.size
op_ne
id|vol-&gt;mft_record_size
)paren
)paren
(brace
id|ntfs_debug
c_func
(paren
id|DEBUG_OTHER
comma
l_string|&quot;read_mft_record: read 0x%x failed &quot;
l_string|&quot;(%d,%d,%d)&bslash;n&quot;
comma
id|mftno
comma
id|error
comma
id|io.size
comma
id|vol-&gt;mft_record_size
)paren
suffix:semicolon
r_return
id|error
ques
c_cond
id|error
suffix:colon
op_minus
id|ENODATA
suffix:semicolon
)brace
id|ntfs_debug
c_func
(paren
id|DEBUG_OTHER
comma
l_string|&quot;read_mft_record: finished read 0x%x&bslash;n&quot;
comma
id|mftno
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ntfs_check_mft_record
c_func
(paren
id|vol
comma
id|buf
)paren
)paren
(brace
multiline_comment|/* FIXME: This is incomplete behaviour. We might be able to&n;&t;&t; * recover at this stage. ntfs_check_mft_record() is too&n;&t;&t; * conservative at aborting it&squot;s operations. It is OK for&n;&t;&t; * now as we just can&squot;t handle some on disk structures&n;&t;&t; * this way. (AIA) */
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;NTFS: Invalid MFT record for 0x%x&bslash;n&quot;
comma
id|mftno
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|ntfs_debug
c_func
(paren
id|DEBUG_OTHER
comma
l_string|&quot;read_mft_record: Done 0x%x&bslash;n&quot;
comma
id|mftno
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ntfs_getput_clusters
r_int
id|ntfs_getput_clusters
c_func
(paren
id|ntfs_volume
op_star
id|vol
comma
r_int
id|cluster
comma
id|ntfs_size_t
id|start_offs
comma
id|ntfs_io
op_star
id|buf
)paren
(brace
r_struct
id|super_block
op_star
id|sb
op_assign
id|NTFS_SB
c_func
(paren
id|vol
)paren
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_int
id|length
op_assign
id|buf-&gt;size
suffix:semicolon
r_int
id|error
op_assign
l_int|0
suffix:semicolon
id|ntfs_size_t
id|to_copy
suffix:semicolon
id|ntfs_debug
c_func
(paren
id|DEBUG_OTHER
comma
l_string|&quot;%s_clusters %d %d %d&bslash;n&quot;
comma
id|buf-&gt;do_read
ques
c_cond
l_string|&quot;get&quot;
suffix:colon
l_string|&quot;put&quot;
comma
id|cluster
comma
id|start_offs
comma
id|length
)paren
suffix:semicolon
id|to_copy
op_assign
id|vol-&gt;cluster_size
op_minus
id|start_offs
suffix:semicolon
r_while
c_loop
(paren
id|length
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|bh
op_assign
id|sb_bread
c_func
(paren
id|sb
comma
id|cluster
)paren
)paren
)paren
(brace
id|ntfs_debug
c_func
(paren
id|DEBUG_OTHER
comma
l_string|&quot;%s failed&bslash;n&quot;
comma
id|buf-&gt;do_read
ques
c_cond
l_string|&quot;Reading&quot;
suffix:colon
l_string|&quot;Writing&quot;
)paren
suffix:semicolon
id|error
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|error_ret
suffix:semicolon
)brace
r_if
c_cond
(paren
id|to_copy
OG
id|length
)paren
id|to_copy
op_assign
id|length
suffix:semicolon
id|lock_buffer
c_func
(paren
id|bh
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buf-&gt;do_read
)paren
(brace
id|buf
op_member_access_from_pointer
id|fn_put
c_func
(paren
id|buf
comma
id|bh-&gt;b_data
op_plus
id|start_offs
comma
id|to_copy
)paren
suffix:semicolon
id|unlock_buffer
c_func
(paren
id|bh
)paren
suffix:semicolon
)brace
r_else
(brace
id|buf
op_member_access_from_pointer
id|fn_get
c_func
(paren
id|bh-&gt;b_data
op_plus
id|start_offs
comma
id|buf
comma
id|to_copy
)paren
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|bh
)paren
suffix:semicolon
id|unlock_buffer
c_func
(paren
id|bh
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * Note: We treat synchronous IO on a per volume basis&n;&t;&t;&t; * disregarding flags of individual inodes. This can&n;&t;&t;&t; * lead to some strange write ordering effects upon a&n;&t;&t;&t; * remount with a change in the sync flag but it should&n;&t;&t;&t; * not break anything. [Except if the system crashes&n;&t;&t;&t; * at that point in time but there would be more thigs&n;&t;&t;&t; * to worry about than that in that case...]. (AIA)&n;&t;&t;&t; */
r_if
c_cond
(paren
id|sb-&gt;s_flags
op_amp
id|MS_SYNCHRONOUS
)paren
(brace
id|ll_rw_block
c_func
(paren
id|WRITE
comma
l_int|1
comma
op_amp
id|bh
)paren
suffix:semicolon
id|wait_on_buffer
c_func
(paren
id|bh
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buffer_req
c_func
(paren
id|bh
)paren
op_logical_and
op_logical_neg
id|buffer_uptodate
c_func
(paren
id|bh
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;IO error syncing NTFS &quot;
l_string|&quot;cluster [%s:%i]&bslash;n&quot;
comma
id|sb-&gt;s_id
comma
id|cluster
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|error
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|error_ret
suffix:semicolon
)brace
)brace
)brace
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|length
op_sub_assign
id|to_copy
suffix:semicolon
id|start_offs
op_assign
l_int|0
suffix:semicolon
id|to_copy
op_assign
id|vol-&gt;cluster_size
suffix:semicolon
id|cluster
op_increment
suffix:semicolon
)brace
id|error_ret
suffix:colon
r_return
id|error
suffix:semicolon
)brace
DECL|function|ntfs_now
id|ntfs_time64_t
id|ntfs_now
c_func
(paren
r_void
)paren
(brace
r_return
id|ntfs_unixutc2ntutc
c_func
(paren
id|CURRENT_TIME
)paren
suffix:semicolon
)brace
DECL|function|ntfs_dupuni2map
r_int
id|ntfs_dupuni2map
c_func
(paren
id|ntfs_volume
op_star
id|vol
comma
id|ntfs_u16
op_star
id|in
comma
r_int
id|in_len
comma
r_char
op_star
op_star
id|out
comma
r_int
op_star
id|out_len
)paren
(brace
r_int
id|i
comma
id|o
comma
id|chl
comma
id|chi
suffix:semicolon
r_char
op_star
id|result
comma
op_star
id|buf
comma
id|charbuf
(braket
id|NLS_MAX_CHARSET_SIZE
)braket
suffix:semicolon
r_struct
id|nls_table
op_star
id|nls
op_assign
id|vol-&gt;nls_map
suffix:semicolon
id|result
op_assign
id|ntfs_malloc
c_func
(paren
id|in_len
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|result
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
op_star
id|out_len
op_assign
id|in_len
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|o
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|in_len
suffix:semicolon
id|i
op_increment
)paren
(brace
multiline_comment|/* FIXME: Byte order? */
m_wchar_t
id|uni
op_assign
id|in
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
(paren
id|chl
op_assign
id|nls
op_member_access_from_pointer
id|uni2char
c_func
(paren
id|uni
comma
id|charbuf
comma
id|NLS_MAX_CHARSET_SIZE
)paren
)paren
OG
l_int|0
)paren
(brace
multiline_comment|/* Adjust result buffer. */
r_if
c_cond
(paren
id|chl
OG
l_int|1
)paren
(brace
id|buf
op_assign
id|ntfs_malloc
c_func
(paren
op_star
id|out_len
op_plus
id|chl
op_minus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buf
)paren
(brace
id|i
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|err_ret
suffix:semicolon
)brace
id|memcpy
c_func
(paren
id|buf
comma
id|result
comma
id|o
)paren
suffix:semicolon
id|ntfs_free
c_func
(paren
id|result
)paren
suffix:semicolon
id|result
op_assign
id|buf
suffix:semicolon
op_star
id|out_len
op_add_assign
(paren
id|chl
op_minus
l_int|1
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|chi
op_assign
l_int|0
suffix:semicolon
id|chi
OL
id|chl
suffix:semicolon
id|chi
op_increment
)paren
id|result
(braket
id|o
op_increment
)braket
op_assign
id|charbuf
(braket
id|chi
)braket
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Invalid character. */
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;NTFS: Unicode name contains a &quot;
l_string|&quot;character that cannot be converted &quot;
l_string|&quot;to chosen character set. Remount &quot;
l_string|&quot;with utf8 encoding and this should &quot;
l_string|&quot;work.&bslash;n&quot;
)paren
suffix:semicolon
id|i
op_assign
op_minus
id|EILSEQ
suffix:semicolon
r_goto
id|err_ret
suffix:semicolon
)brace
)brace
id|result
(braket
op_star
id|out_len
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
op_star
id|out
op_assign
id|result
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|err_ret
suffix:colon
id|ntfs_free
c_func
(paren
id|result
)paren
suffix:semicolon
op_star
id|out_len
op_assign
l_int|0
suffix:semicolon
op_star
id|out
op_assign
l_int|NULL
suffix:semicolon
r_return
id|i
suffix:semicolon
)brace
DECL|function|ntfs_dupmap2uni
r_int
id|ntfs_dupmap2uni
c_func
(paren
id|ntfs_volume
op_star
id|vol
comma
r_char
op_star
id|in
comma
r_int
id|in_len
comma
id|ntfs_u16
op_star
op_star
id|out
comma
r_int
op_star
id|out_len
)paren
(brace
r_int
id|i
comma
id|o
suffix:semicolon
id|ntfs_u16
op_star
id|result
suffix:semicolon
r_struct
id|nls_table
op_star
id|nls
op_assign
id|vol-&gt;nls_map
suffix:semicolon
op_star
id|out
op_assign
id|result
op_assign
id|ntfs_malloc
c_func
(paren
l_int|2
op_star
id|in_len
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|result
)paren
(brace
op_star
id|out_len
op_assign
l_int|0
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
op_star
id|out_len
op_assign
id|in_len
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|o
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|in_len
suffix:semicolon
id|i
op_increment
comma
id|o
op_increment
)paren
(brace
m_wchar_t
id|uni
suffix:semicolon
r_int
id|charlen
suffix:semicolon
id|charlen
op_assign
id|nls
op_member_access_from_pointer
id|char2uni
c_func
(paren
op_amp
id|in
(braket
id|i
)braket
comma
id|in_len
op_minus
id|i
comma
op_amp
id|uni
)paren
suffix:semicolon
r_if
c_cond
(paren
id|charlen
OL
l_int|0
)paren
(brace
id|i
op_assign
id|charlen
suffix:semicolon
r_goto
id|err_ret
suffix:semicolon
)brace
op_star
id|out_len
op_sub_assign
id|charlen
op_minus
l_int|1
suffix:semicolon
id|i
op_add_assign
id|charlen
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* FIXME: Byte order? */
id|result
(braket
id|o
)braket
op_assign
id|uni
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|result
(braket
id|o
)braket
)paren
(brace
id|i
op_assign
op_minus
id|EILSEQ
suffix:semicolon
r_goto
id|err_ret
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
id|err_ret
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;NTFS: Name contains a character that cannot be &quot;
l_string|&quot;converted to Unicode.&bslash;n&quot;
)paren
suffix:semicolon
id|ntfs_free
c_func
(paren
id|result
)paren
suffix:semicolon
op_star
id|out_len
op_assign
l_int|0
suffix:semicolon
op_star
id|out
op_assign
l_int|NULL
suffix:semicolon
r_return
id|i
suffix:semicolon
)brace
eof
