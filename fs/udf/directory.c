multiline_comment|/*&n; * directory.c&n; *&n; * PURPOSE&n; *&t;Directory related functions&n; *&n; * CONTACTS&n; *&t;E-mail regarding any portion of the Linux UDF file system should be&n; *&t;directed to the development team mailing list (run by majordomo):&n; *&t;&t;linux_udf@hpesjro.fc.hp.com&n; *&n; * COPYRIGHT&n; *&t;This file is distributed under the terms of the GNU General Public&n; *&t;License (GPL). Copies of the GPL can be obtained from:&n; *&t;&t;ftp://prep.ai.mit.edu/pub/gnu/GPL&n; *&t;Each contributing author retains all rights to their own work.&n; */
macro_line|#include &quot;udfdecl.h&quot;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/buffer_head.h&gt;
DECL|function|udf_filead_read
r_uint8
op_star
id|udf_filead_read
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_uint8
op_star
id|tmpad
comma
r_uint8
id|ad_size
comma
id|lb_addr
id|fe_loc
comma
r_int
op_star
id|pos
comma
r_int
op_star
id|offset
comma
r_struct
id|buffer_head
op_star
op_star
id|bh
comma
r_int
op_star
id|error
)paren
(brace
r_int
id|loffset
op_assign
op_star
id|offset
suffix:semicolon
r_int
id|block
suffix:semicolon
r_uint8
op_star
id|ad
suffix:semicolon
r_int
id|remainder
suffix:semicolon
op_star
id|error
op_assign
l_int|0
suffix:semicolon
id|ad
op_assign
(paren
r_uint8
op_star
)paren
(paren
op_star
id|bh
)paren
op_member_access_from_pointer
id|b_data
op_plus
op_star
id|offset
suffix:semicolon
op_star
id|offset
op_add_assign
id|ad_size
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ad
)paren
(brace
id|udf_release_data
c_func
(paren
op_star
id|bh
)paren
suffix:semicolon
op_star
id|error
op_assign
l_int|1
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
op_star
id|offset
op_eq
id|dir-&gt;i_sb-&gt;s_blocksize
)paren
(brace
id|udf_release_data
c_func
(paren
op_star
id|bh
)paren
suffix:semicolon
id|block
op_assign
id|udf_get_lb_pblock
c_func
(paren
id|dir-&gt;i_sb
comma
id|fe_loc
comma
op_increment
op_star
id|pos
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|block
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
op_star
id|bh
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
r_return
l_int|NULL
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_star
id|offset
OG
id|dir-&gt;i_sb-&gt;s_blocksize
)paren
(brace
id|ad
op_assign
id|tmpad
suffix:semicolon
id|remainder
op_assign
id|dir-&gt;i_sb-&gt;s_blocksize
op_minus
id|loffset
suffix:semicolon
id|memcpy
c_func
(paren
(paren
r_uint8
op_star
)paren
id|ad
comma
(paren
op_star
id|bh
)paren
op_member_access_from_pointer
id|b_data
op_plus
id|loffset
comma
id|remainder
)paren
suffix:semicolon
id|udf_release_data
c_func
(paren
op_star
id|bh
)paren
suffix:semicolon
id|block
op_assign
id|udf_get_lb_pblock
c_func
(paren
id|dir-&gt;i_sb
comma
id|fe_loc
comma
op_increment
op_star
id|pos
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|block
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
(paren
op_star
id|bh
)paren
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
r_return
l_int|NULL
suffix:semicolon
id|memcpy
c_func
(paren
(paren
r_uint8
op_star
)paren
id|ad
op_plus
id|remainder
comma
(paren
op_star
id|bh
)paren
op_member_access_from_pointer
id|b_data
comma
id|ad_size
op_minus
id|remainder
)paren
suffix:semicolon
op_star
id|offset
op_assign
id|ad_size
op_minus
id|remainder
suffix:semicolon
)brace
r_return
id|ad
suffix:semicolon
)brace
r_struct
id|fileIdentDesc
op_star
DECL|function|udf_fileident_read
id|udf_fileident_read
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
id|loff_t
op_star
id|nf_pos
comma
r_struct
id|udf_fileident_bh
op_star
id|fibh
comma
r_struct
id|fileIdentDesc
op_star
id|cfi
comma
id|lb_addr
op_star
id|bloc
comma
r_uint32
op_star
id|extoffset
comma
id|lb_addr
op_star
id|eloc
comma
r_uint32
op_star
id|elen
comma
r_uint32
op_star
id|offset
comma
r_struct
id|buffer_head
op_star
op_star
id|bh
)paren
(brace
r_struct
id|fileIdentDesc
op_star
id|fi
suffix:semicolon
r_int
id|i
comma
id|num
comma
id|block
suffix:semicolon
r_struct
id|buffer_head
op_star
id|tmp
comma
op_star
id|bha
(braket
l_int|16
)braket
suffix:semicolon
id|fibh-&gt;soffset
op_assign
id|fibh-&gt;eoffset
suffix:semicolon
r_if
c_cond
(paren
id|fibh-&gt;eoffset
op_eq
id|dir-&gt;i_sb-&gt;s_blocksize
)paren
(brace
r_int
id|lextoffset
op_assign
op_star
id|extoffset
suffix:semicolon
r_if
c_cond
(paren
id|udf_next_aext
c_func
(paren
id|dir
comma
id|bloc
comma
id|extoffset
comma
id|eloc
comma
id|elen
comma
id|bh
comma
l_int|1
)paren
op_ne
(paren
id|EXT_RECORDED_ALLOCATED
op_rshift
l_int|30
)paren
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
id|block
op_assign
id|udf_get_lb_pblock
c_func
(paren
id|dir-&gt;i_sb
comma
op_star
id|eloc
comma
op_star
id|offset
)paren
suffix:semicolon
(paren
op_star
id|offset
)paren
op_increment
suffix:semicolon
r_if
c_cond
(paren
(paren
op_star
id|offset
op_lshift
id|dir-&gt;i_sb-&gt;s_blocksize_bits
)paren
op_ge
op_star
id|elen
)paren
op_star
id|offset
op_assign
l_int|0
suffix:semicolon
r_else
op_star
id|extoffset
op_assign
id|lextoffset
suffix:semicolon
id|udf_release_data
c_func
(paren
id|fibh-&gt;sbh
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|fibh-&gt;sbh
op_assign
id|fibh-&gt;ebh
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
r_return
l_int|NULL
suffix:semicolon
id|fibh-&gt;soffset
op_assign
id|fibh-&gt;eoffset
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
op_star
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
op_star
id|offset
OG
(paren
op_star
id|elen
op_rshift
id|dir-&gt;i_sb-&gt;s_blocksize_bits
)paren
)paren
id|i
op_assign
(paren
op_star
id|elen
op_rshift
id|dir-&gt;i_sb-&gt;s_blocksize_bits
)paren
op_minus
op_star
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
op_star
id|eloc
comma
op_star
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
r_if
c_cond
(paren
id|fibh-&gt;sbh
op_ne
id|fibh-&gt;ebh
)paren
(brace
id|udf_release_data
c_func
(paren
id|fibh-&gt;sbh
)paren
suffix:semicolon
id|fibh-&gt;sbh
op_assign
id|fibh-&gt;ebh
suffix:semicolon
)brace
id|fi
op_assign
id|udf_get_fileident
c_func
(paren
id|fibh-&gt;sbh-&gt;b_data
comma
id|dir-&gt;i_sb-&gt;s_blocksize
comma
op_amp
(paren
id|fibh-&gt;eoffset
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fi
)paren
r_return
l_int|NULL
suffix:semicolon
op_star
id|nf_pos
op_add_assign
(paren
(paren
id|fibh-&gt;eoffset
op_minus
id|fibh-&gt;soffset
)paren
op_rshift
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fibh-&gt;eoffset
op_le
id|dir-&gt;i_sb-&gt;s_blocksize
)paren
(brace
id|memcpy
c_func
(paren
(paren
r_uint8
op_star
)paren
id|cfi
comma
(paren
r_uint8
op_star
)paren
id|fi
comma
r_sizeof
(paren
r_struct
id|fileIdentDesc
)paren
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|fibh-&gt;eoffset
OG
id|dir-&gt;i_sb-&gt;s_blocksize
)paren
(brace
r_int
id|lextoffset
op_assign
op_star
id|extoffset
suffix:semicolon
r_if
c_cond
(paren
id|udf_next_aext
c_func
(paren
id|dir
comma
id|bloc
comma
id|extoffset
comma
id|eloc
comma
id|elen
comma
id|bh
comma
l_int|1
)paren
op_ne
(paren
id|EXT_RECORDED_ALLOCATED
op_rshift
l_int|30
)paren
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
id|block
op_assign
id|udf_get_lb_pblock
c_func
(paren
id|dir-&gt;i_sb
comma
op_star
id|eloc
comma
op_star
id|offset
)paren
suffix:semicolon
(paren
op_star
id|offset
)paren
op_increment
suffix:semicolon
r_if
c_cond
(paren
(paren
op_star
id|offset
op_lshift
id|dir-&gt;i_sb-&gt;s_blocksize_bits
)paren
op_ge
op_star
id|elen
)paren
op_star
id|offset
op_assign
l_int|0
suffix:semicolon
r_else
op_star
id|extoffset
op_assign
id|lextoffset
suffix:semicolon
id|fibh-&gt;soffset
op_sub_assign
id|dir-&gt;i_sb-&gt;s_blocksize
suffix:semicolon
id|fibh-&gt;eoffset
op_sub_assign
id|dir-&gt;i_sb-&gt;s_blocksize
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|fibh-&gt;ebh
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
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
r_sizeof
(paren
r_struct
id|fileIdentDesc
)paren
OG
op_minus
id|fibh-&gt;soffset
)paren
(brace
r_int
id|fi_len
suffix:semicolon
id|memcpy
c_func
(paren
(paren
r_uint8
op_star
)paren
id|cfi
comma
(paren
r_uint8
op_star
)paren
id|fi
comma
op_minus
id|fibh-&gt;soffset
)paren
suffix:semicolon
id|memcpy
c_func
(paren
(paren
r_uint8
op_star
)paren
id|cfi
op_minus
id|fibh-&gt;soffset
comma
id|fibh-&gt;ebh-&gt;b_data
comma
r_sizeof
(paren
r_struct
id|fileIdentDesc
)paren
op_plus
id|fibh-&gt;soffset
)paren
suffix:semicolon
id|fi_len
op_assign
(paren
r_sizeof
(paren
r_struct
id|fileIdentDesc
)paren
op_plus
id|cfi-&gt;lengthFileIdent
op_plus
id|le16_to_cpu
c_func
(paren
id|cfi-&gt;lengthOfImpUse
)paren
op_plus
l_int|3
)paren
op_amp
op_complement
l_int|3
suffix:semicolon
op_star
id|nf_pos
op_add_assign
(paren
(paren
id|fi_len
op_minus
(paren
id|fibh-&gt;eoffset
op_minus
id|fibh-&gt;soffset
)paren
)paren
op_rshift
l_int|2
)paren
suffix:semicolon
id|fibh-&gt;eoffset
op_assign
id|fibh-&gt;soffset
op_plus
id|fi_len
suffix:semicolon
)brace
r_else
(brace
id|memcpy
c_func
(paren
(paren
r_uint8
op_star
)paren
id|cfi
comma
(paren
r_uint8
op_star
)paren
id|fi
comma
r_sizeof
(paren
r_struct
id|fileIdentDesc
)paren
)paren
suffix:semicolon
)brace
)brace
r_return
id|fi
suffix:semicolon
)brace
r_struct
id|fileIdentDesc
op_star
DECL|function|udf_get_fileident
id|udf_get_fileident
c_func
(paren
r_void
op_star
id|buffer
comma
r_int
id|bufsize
comma
r_int
op_star
id|offset
)paren
(brace
r_struct
id|fileIdentDesc
op_star
id|fi
suffix:semicolon
r_int
id|lengthThisIdent
suffix:semicolon
r_uint8
op_star
id|ptr
suffix:semicolon
r_int
id|padlen
suffix:semicolon
r_if
c_cond
(paren
(paren
op_logical_neg
id|buffer
)paren
op_logical_or
(paren
op_logical_neg
id|offset
)paren
)paren
(brace
id|udf_debug
c_func
(paren
l_string|&quot;invalidparms&bslash;n, buffer=%p, offset=%p&bslash;n&quot;
comma
id|buffer
comma
id|offset
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|ptr
op_assign
id|buffer
suffix:semicolon
r_if
c_cond
(paren
(paren
op_star
id|offset
OG
l_int|0
)paren
op_logical_and
(paren
op_star
id|offset
OL
id|bufsize
)paren
)paren
(brace
id|ptr
op_add_assign
op_star
id|offset
suffix:semicolon
)brace
id|fi
op_assign
(paren
r_struct
id|fileIdentDesc
op_star
)paren
id|ptr
suffix:semicolon
r_if
c_cond
(paren
id|le16_to_cpu
c_func
(paren
id|fi-&gt;descTag.tagIdent
)paren
op_ne
id|TAG_IDENT_FID
)paren
(brace
id|udf_debug
c_func
(paren
l_string|&quot;0x%x != TAG_IDENT_FID&bslash;n&quot;
comma
id|le16_to_cpu
c_func
(paren
id|fi-&gt;descTag.tagIdent
)paren
)paren
suffix:semicolon
id|udf_debug
c_func
(paren
l_string|&quot;offset: %u sizeof: %lu bufsize: %u&bslash;n&quot;
comma
op_star
id|offset
comma
(paren
r_int
r_int
)paren
r_sizeof
(paren
r_struct
id|fileIdentDesc
)paren
comma
id|bufsize
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
op_star
id|offset
op_plus
r_sizeof
(paren
r_struct
id|fileIdentDesc
)paren
)paren
OG
id|bufsize
)paren
(brace
id|lengthThisIdent
op_assign
r_sizeof
(paren
r_struct
id|fileIdentDesc
)paren
suffix:semicolon
)brace
r_else
id|lengthThisIdent
op_assign
r_sizeof
(paren
r_struct
id|fileIdentDesc
)paren
op_plus
id|fi-&gt;lengthFileIdent
op_plus
id|le16_to_cpu
c_func
(paren
id|fi-&gt;lengthOfImpUse
)paren
suffix:semicolon
multiline_comment|/* we need to figure padding, too! */
id|padlen
op_assign
id|lengthThisIdent
op_mod
id|UDF_NAME_PAD
suffix:semicolon
r_if
c_cond
(paren
id|padlen
)paren
id|lengthThisIdent
op_add_assign
(paren
id|UDF_NAME_PAD
op_minus
id|padlen
)paren
suffix:semicolon
op_star
id|offset
op_assign
op_star
id|offset
op_plus
id|lengthThisIdent
suffix:semicolon
r_return
id|fi
suffix:semicolon
)brace
id|extent_ad
op_star
DECL|function|udf_get_fileextent
id|udf_get_fileextent
c_func
(paren
r_void
op_star
id|buffer
comma
r_int
id|bufsize
comma
r_int
op_star
id|offset
)paren
(brace
id|extent_ad
op_star
id|ext
suffix:semicolon
r_struct
id|fileEntry
op_star
id|fe
suffix:semicolon
r_uint8
op_star
id|ptr
suffix:semicolon
r_if
c_cond
(paren
(paren
op_logical_neg
id|buffer
)paren
op_logical_or
(paren
op_logical_neg
id|offset
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;udf: udf_get_fileextent() invalidparms&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|fe
op_assign
(paren
r_struct
id|fileEntry
op_star
)paren
id|buffer
suffix:semicolon
r_if
c_cond
(paren
id|le16_to_cpu
c_func
(paren
id|fe-&gt;descTag.tagIdent
)paren
op_ne
id|TAG_IDENT_FE
)paren
(brace
id|udf_debug
c_func
(paren
l_string|&quot;0x%x != TAG_IDENT_FE&bslash;n&quot;
comma
id|le16_to_cpu
c_func
(paren
id|fe-&gt;descTag.tagIdent
)paren
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|ptr
op_assign
(paren
r_uint8
op_star
)paren
(paren
id|fe-&gt;extendedAttr
)paren
op_plus
id|le32_to_cpu
c_func
(paren
id|fe-&gt;lengthExtendedAttr
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
op_star
id|offset
OG
l_int|0
)paren
op_logical_and
(paren
op_star
id|offset
OL
id|le32_to_cpu
c_func
(paren
id|fe-&gt;lengthAllocDescs
)paren
)paren
)paren
(brace
id|ptr
op_add_assign
op_star
id|offset
suffix:semicolon
)brace
id|ext
op_assign
(paren
id|extent_ad
op_star
)paren
id|ptr
suffix:semicolon
op_star
id|offset
op_assign
op_star
id|offset
op_plus
r_sizeof
(paren
id|extent_ad
)paren
suffix:semicolon
r_return
id|ext
suffix:semicolon
)brace
id|short_ad
op_star
DECL|function|udf_get_fileshortad
id|udf_get_fileshortad
c_func
(paren
r_void
op_star
id|buffer
comma
r_int
id|maxoffset
comma
r_int
op_star
id|offset
comma
r_int
id|inc
)paren
(brace
id|short_ad
op_star
id|sa
suffix:semicolon
r_uint8
op_star
id|ptr
suffix:semicolon
r_if
c_cond
(paren
(paren
op_logical_neg
id|buffer
)paren
op_logical_or
(paren
op_logical_neg
id|offset
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;udf: udf_get_fileshortad() invalidparms&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|ptr
op_assign
(paren
r_uint8
op_star
)paren
id|buffer
suffix:semicolon
r_if
c_cond
(paren
(paren
op_star
id|offset
OG
l_int|0
)paren
op_logical_and
(paren
op_star
id|offset
OL
id|maxoffset
)paren
)paren
id|ptr
op_add_assign
op_star
id|offset
suffix:semicolon
r_else
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
(paren
id|sa
op_assign
(paren
id|short_ad
op_star
)paren
id|ptr
)paren
op_member_access_from_pointer
id|extLength
op_eq
l_int|0
)paren
r_return
l_int|NULL
suffix:semicolon
r_else
r_if
c_cond
(paren
id|inc
)paren
(paren
op_star
id|offset
)paren
op_add_assign
r_sizeof
(paren
id|short_ad
)paren
suffix:semicolon
r_return
id|sa
suffix:semicolon
)brace
id|long_ad
op_star
DECL|function|udf_get_filelongad
id|udf_get_filelongad
c_func
(paren
r_void
op_star
id|buffer
comma
r_int
id|maxoffset
comma
r_int
op_star
id|offset
comma
r_int
id|inc
)paren
(brace
id|long_ad
op_star
id|la
suffix:semicolon
r_uint8
op_star
id|ptr
suffix:semicolon
r_if
c_cond
(paren
(paren
op_logical_neg
id|buffer
)paren
op_logical_or
op_logical_neg
(paren
id|offset
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;udf: udf_get_filelongad() invalidparms&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|ptr
op_assign
(paren
r_uint8
op_star
)paren
id|buffer
suffix:semicolon
r_if
c_cond
(paren
(paren
op_star
id|offset
OG
l_int|0
)paren
op_logical_and
(paren
op_star
id|offset
OL
id|maxoffset
)paren
)paren
id|ptr
op_add_assign
op_star
id|offset
suffix:semicolon
r_else
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
(paren
id|la
op_assign
(paren
id|long_ad
op_star
)paren
id|ptr
)paren
op_member_access_from_pointer
id|extLength
op_eq
l_int|0
)paren
r_return
l_int|NULL
suffix:semicolon
r_else
r_if
c_cond
(paren
id|inc
)paren
(paren
op_star
id|offset
)paren
op_add_assign
r_sizeof
(paren
id|long_ad
)paren
suffix:semicolon
r_return
id|la
suffix:semicolon
)brace
eof
