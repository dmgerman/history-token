multiline_comment|/*&n; * misc.c&n; *&n; * PURPOSE&n; *&t;Miscellaneous routines for the OSTA-UDF(tm) filesystem.&n; *&n; * CONTACTS&n; *&t;E-mail regarding any portion of the Linux UDF file system should be&n; *&t;directed to the development team mailing list (run by majordomo):&n; *&t;&t;linux_udf@hpesjro.fc.hp.com&n; *&n; * COPYRIGHT&n; *&t;This file is distributed under the terms of the GNU General Public&n; *&t;License (GPL). Copies of the GPL can be obtained from:&n; *&t;&t;ftp://prep.ai.mit.edu/pub/gnu/GPL&n; *&t;Each contributing author retains all rights to their own work.&n; *&n; *  (C) 1998 Dave Boynton&n; *  (C) 1998-2004 Ben Fennema&n; *  (C) 1999-2000 Stelias Computing Inc&n; *&n; * HISTORY&n; *&n; *  04/19/99 blf  partial support for reading/writing specific EA&squot;s&n; */
macro_line|#include &quot;udfdecl.h&quot;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/udf_fs.h&gt;
macro_line|#include &lt;linux/buffer_head.h&gt;
macro_line|#include &quot;udf_i.h&quot;
macro_line|#include &quot;udf_sb.h&quot;
r_struct
id|buffer_head
op_star
DECL|function|udf_tgetblk
id|udf_tgetblk
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
id|block
)paren
(brace
r_if
c_cond
(paren
id|UDF_QUERY_FLAG
c_func
(paren
id|sb
comma
id|UDF_FLAG_VARCONV
)paren
)paren
r_return
id|sb_getblk
c_func
(paren
id|sb
comma
id|udf_fixed_to_variable
c_func
(paren
id|block
)paren
)paren
suffix:semicolon
r_else
r_return
id|sb_getblk
c_func
(paren
id|sb
comma
id|block
)paren
suffix:semicolon
)brace
r_struct
id|buffer_head
op_star
DECL|function|udf_tread
id|udf_tread
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
id|block
)paren
(brace
r_if
c_cond
(paren
id|UDF_QUERY_FLAG
c_func
(paren
id|sb
comma
id|UDF_FLAG_VARCONV
)paren
)paren
r_return
id|sb_bread
c_func
(paren
id|sb
comma
id|udf_fixed_to_variable
c_func
(paren
id|block
)paren
)paren
suffix:semicolon
r_else
r_return
id|sb_bread
c_func
(paren
id|sb
comma
id|block
)paren
suffix:semicolon
)brace
r_struct
id|genericFormat
op_star
DECL|function|udf_add_extendedattr
id|udf_add_extendedattr
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_uint32
id|size
comma
r_uint32
id|type
comma
r_uint8
id|loc
)paren
(brace
r_uint8
op_star
id|ea
op_assign
l_int|NULL
comma
op_star
id|ad
op_assign
l_int|NULL
suffix:semicolon
r_int
id|offset
suffix:semicolon
r_uint16
id|crclen
suffix:semicolon
r_int
id|i
suffix:semicolon
id|ea
op_assign
id|UDF_I_DATA
c_func
(paren
id|inode
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
id|ad
op_assign
id|UDF_I_DATA
c_func
(paren
id|inode
)paren
op_plus
id|UDF_I_LENEATTR
c_func
(paren
id|inode
)paren
suffix:semicolon
r_else
(brace
id|ad
op_assign
id|ea
suffix:semicolon
id|size
op_add_assign
r_sizeof
(paren
r_struct
id|extendedAttrHeaderDesc
)paren
suffix:semicolon
)brace
id|offset
op_assign
id|inode-&gt;i_sb-&gt;s_blocksize
op_minus
id|udf_file_entry_alloc_offset
c_func
(paren
id|inode
)paren
op_minus
id|UDF_I_LENALLOC
c_func
(paren
id|inode
)paren
suffix:semicolon
multiline_comment|/* TODO - Check for FreeEASpace */
r_if
c_cond
(paren
id|loc
op_amp
l_int|0x01
op_logical_and
id|offset
op_ge
id|size
)paren
(brace
r_struct
id|extendedAttrHeaderDesc
op_star
id|eahd
suffix:semicolon
id|eahd
op_assign
(paren
r_struct
id|extendedAttrHeaderDesc
op_star
)paren
id|ea
suffix:semicolon
r_if
c_cond
(paren
id|UDF_I_LENALLOC
c_func
(paren
id|inode
)paren
)paren
(brace
id|memmove
c_func
(paren
op_amp
id|ad
(braket
id|size
)braket
comma
id|ad
comma
id|UDF_I_LENALLOC
c_func
(paren
id|inode
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|UDF_I_LENEATTR
c_func
(paren
id|inode
)paren
)paren
(brace
multiline_comment|/* check checksum/crc */
r_if
c_cond
(paren
id|le16_to_cpu
c_func
(paren
id|eahd-&gt;descTag.tagIdent
)paren
op_ne
id|TAG_IDENT_EAHD
op_logical_or
id|le32_to_cpu
c_func
(paren
id|eahd-&gt;descTag.tagLocation
)paren
op_ne
id|UDF_I_LOCATION
c_func
(paren
id|inode
)paren
dot
id|logicalBlockNum
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
)brace
r_else
(brace
id|size
op_sub_assign
r_sizeof
(paren
r_struct
id|extendedAttrHeaderDesc
)paren
suffix:semicolon
id|UDF_I_LENEATTR
c_func
(paren
id|inode
)paren
op_add_assign
r_sizeof
(paren
r_struct
id|extendedAttrHeaderDesc
)paren
suffix:semicolon
id|eahd-&gt;descTag.tagIdent
op_assign
id|cpu_to_le16
c_func
(paren
id|TAG_IDENT_EAHD
)paren
suffix:semicolon
r_if
c_cond
(paren
id|UDF_SB_UDFREV
c_func
(paren
id|inode-&gt;i_sb
)paren
op_ge
l_int|0x0200
)paren
id|eahd-&gt;descTag.descVersion
op_assign
id|cpu_to_le16
c_func
(paren
l_int|3
)paren
suffix:semicolon
r_else
id|eahd-&gt;descTag.descVersion
op_assign
id|cpu_to_le16
c_func
(paren
l_int|2
)paren
suffix:semicolon
id|eahd-&gt;descTag.tagSerialNum
op_assign
id|cpu_to_le16
c_func
(paren
id|UDF_SB_SERIALNUM
c_func
(paren
id|inode-&gt;i_sb
)paren
)paren
suffix:semicolon
id|eahd-&gt;descTag.tagLocation
op_assign
id|cpu_to_le32
c_func
(paren
id|UDF_I_LOCATION
c_func
(paren
id|inode
)paren
dot
id|logicalBlockNum
)paren
suffix:semicolon
id|eahd-&gt;impAttrLocation
op_assign
id|cpu_to_le32
c_func
(paren
l_int|0xFFFFFFFF
)paren
suffix:semicolon
id|eahd-&gt;appAttrLocation
op_assign
id|cpu_to_le32
c_func
(paren
l_int|0xFFFFFFFF
)paren
suffix:semicolon
)brace
id|offset
op_assign
id|UDF_I_LENEATTR
c_func
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|type
OL
l_int|2048
)paren
(brace
r_if
c_cond
(paren
id|le32_to_cpu
c_func
(paren
id|eahd-&gt;appAttrLocation
)paren
OL
id|UDF_I_LENEATTR
c_func
(paren
id|inode
)paren
)paren
(brace
r_uint32
id|aal
op_assign
id|le32_to_cpu
c_func
(paren
id|eahd-&gt;appAttrLocation
)paren
suffix:semicolon
id|memmove
c_func
(paren
op_amp
id|ea
(braket
id|offset
op_minus
id|aal
op_plus
id|size
)braket
comma
op_amp
id|ea
(braket
id|aal
)braket
comma
id|offset
op_minus
id|aal
)paren
suffix:semicolon
id|offset
op_sub_assign
id|aal
suffix:semicolon
id|eahd-&gt;appAttrLocation
op_assign
id|cpu_to_le32
c_func
(paren
id|aal
op_plus
id|size
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|le32_to_cpu
c_func
(paren
id|eahd-&gt;impAttrLocation
)paren
OL
id|UDF_I_LENEATTR
c_func
(paren
id|inode
)paren
)paren
(brace
r_uint32
id|ial
op_assign
id|le32_to_cpu
c_func
(paren
id|eahd-&gt;impAttrLocation
)paren
suffix:semicolon
id|memmove
c_func
(paren
op_amp
id|ea
(braket
id|offset
op_minus
id|ial
op_plus
id|size
)braket
comma
op_amp
id|ea
(braket
id|ial
)braket
comma
id|offset
op_minus
id|ial
)paren
suffix:semicolon
id|offset
op_sub_assign
id|ial
suffix:semicolon
id|eahd-&gt;impAttrLocation
op_assign
id|cpu_to_le32
c_func
(paren
id|ial
op_plus
id|size
)paren
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|type
OL
l_int|65536
)paren
(brace
r_if
c_cond
(paren
id|le32_to_cpu
c_func
(paren
id|eahd-&gt;appAttrLocation
)paren
OL
id|UDF_I_LENEATTR
c_func
(paren
id|inode
)paren
)paren
(brace
r_uint32
id|aal
op_assign
id|le32_to_cpu
c_func
(paren
id|eahd-&gt;appAttrLocation
)paren
suffix:semicolon
id|memmove
c_func
(paren
op_amp
id|ea
(braket
id|offset
op_minus
id|aal
op_plus
id|size
)braket
comma
op_amp
id|ea
(braket
id|aal
)braket
comma
id|offset
op_minus
id|aal
)paren
suffix:semicolon
id|offset
op_sub_assign
id|aal
suffix:semicolon
id|eahd-&gt;appAttrLocation
op_assign
id|cpu_to_le32
c_func
(paren
id|aal
op_plus
id|size
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* rewrite CRC + checksum of eahd */
id|crclen
op_assign
r_sizeof
(paren
r_struct
id|extendedAttrHeaderDesc
)paren
op_minus
r_sizeof
(paren
id|tag
)paren
suffix:semicolon
id|eahd-&gt;descTag.descCRCLength
op_assign
id|cpu_to_le16
c_func
(paren
id|crclen
)paren
suffix:semicolon
id|eahd-&gt;descTag.descCRC
op_assign
id|cpu_to_le16
c_func
(paren
id|udf_crc
c_func
(paren
(paren
r_char
op_star
)paren
id|eahd
op_plus
r_sizeof
(paren
id|tag
)paren
comma
id|crclen
comma
l_int|0
)paren
)paren
suffix:semicolon
id|eahd-&gt;descTag.tagChecksum
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
l_int|16
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|i
op_ne
l_int|4
)paren
id|eahd-&gt;descTag.tagChecksum
op_add_assign
(paren
(paren
r_uint8
op_star
)paren
op_amp
(paren
id|eahd-&gt;descTag
)paren
)paren
(braket
id|i
)braket
suffix:semicolon
id|UDF_I_LENEATTR
c_func
(paren
id|inode
)paren
op_add_assign
id|size
suffix:semicolon
r_return
(paren
r_struct
id|genericFormat
op_star
)paren
op_amp
id|ea
(braket
id|offset
)braket
suffix:semicolon
)brace
r_if
c_cond
(paren
id|loc
op_amp
l_int|0x02
)paren
(brace
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
r_struct
id|genericFormat
op_star
DECL|function|udf_get_extendedattr
id|udf_get_extendedattr
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_uint32
id|type
comma
r_uint8
id|subtype
)paren
(brace
r_struct
id|genericFormat
op_star
id|gaf
suffix:semicolon
r_uint8
op_star
id|ea
op_assign
l_int|NULL
suffix:semicolon
r_uint32
id|offset
suffix:semicolon
id|ea
op_assign
id|UDF_I_DATA
c_func
(paren
id|inode
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
(brace
r_struct
id|extendedAttrHeaderDesc
op_star
id|eahd
suffix:semicolon
id|eahd
op_assign
(paren
r_struct
id|extendedAttrHeaderDesc
op_star
)paren
id|ea
suffix:semicolon
multiline_comment|/* check checksum/crc */
r_if
c_cond
(paren
id|le16_to_cpu
c_func
(paren
id|eahd-&gt;descTag.tagIdent
)paren
op_ne
id|TAG_IDENT_EAHD
op_logical_or
id|le32_to_cpu
c_func
(paren
id|eahd-&gt;descTag.tagLocation
)paren
op_ne
id|UDF_I_LOCATION
c_func
(paren
id|inode
)paren
dot
id|logicalBlockNum
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|type
OL
l_int|2048
)paren
id|offset
op_assign
r_sizeof
(paren
r_struct
id|extendedAttrHeaderDesc
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|type
OL
l_int|65536
)paren
id|offset
op_assign
id|le32_to_cpu
c_func
(paren
id|eahd-&gt;impAttrLocation
)paren
suffix:semicolon
r_else
id|offset
op_assign
id|le32_to_cpu
c_func
(paren
id|eahd-&gt;appAttrLocation
)paren
suffix:semicolon
r_while
c_loop
(paren
id|offset
OL
id|UDF_I_LENEATTR
c_func
(paren
id|inode
)paren
)paren
(brace
id|gaf
op_assign
(paren
r_struct
id|genericFormat
op_star
)paren
op_amp
id|ea
(braket
id|offset
)braket
suffix:semicolon
r_if
c_cond
(paren
id|le32_to_cpu
c_func
(paren
id|gaf-&gt;attrType
)paren
op_eq
id|type
op_logical_and
id|gaf-&gt;attrSubtype
op_eq
id|subtype
)paren
r_return
id|gaf
suffix:semicolon
r_else
id|offset
op_add_assign
id|le32_to_cpu
c_func
(paren
id|gaf-&gt;attrLength
)paren
suffix:semicolon
)brace
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; * udf_read_tagged&n; *&n; * PURPOSE&n; *&t;Read the first block of a tagged descriptor.&n; *&n; * HISTORY&n; *&t;July 1, 1997 - Andrew E. Mileski&n; *&t;Written, tested, and released.&n; */
r_struct
id|buffer_head
op_star
DECL|function|udf_read_tagged
id|udf_read_tagged
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_uint32
id|block
comma
r_uint32
id|location
comma
r_uint16
op_star
id|ident
)paren
(brace
id|tag
op_star
id|tag_p
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
op_assign
l_int|NULL
suffix:semicolon
r_register
r_uint8
id|checksum
suffix:semicolon
r_register
r_int
id|i
suffix:semicolon
multiline_comment|/* Read the block */
r_if
c_cond
(paren
id|block
op_eq
l_int|0xFFFFFFFF
)paren
r_return
l_int|NULL
suffix:semicolon
id|bh
op_assign
id|udf_tread
c_func
(paren
id|sb
comma
id|block
op_plus
id|UDF_SB_SESSION
c_func
(paren
id|sb
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
l_string|&quot;block=%d, location=%d: read failed&bslash;n&quot;
comma
id|block
op_plus
id|UDF_SB_SESSION
c_func
(paren
id|sb
)paren
comma
id|location
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|tag_p
op_assign
(paren
id|tag
op_star
)paren
(paren
id|bh-&gt;b_data
)paren
suffix:semicolon
op_star
id|ident
op_assign
id|le16_to_cpu
c_func
(paren
id|tag_p-&gt;tagIdent
)paren
suffix:semicolon
r_if
c_cond
(paren
id|location
op_ne
id|le32_to_cpu
c_func
(paren
id|tag_p-&gt;tagLocation
)paren
)paren
(brace
id|udf_debug
c_func
(paren
l_string|&quot;location mismatch block %u, tag %u != %u&bslash;n&quot;
comma
id|block
op_plus
id|UDF_SB_SESSION
c_func
(paren
id|sb
)paren
comma
id|le32_to_cpu
c_func
(paren
id|tag_p-&gt;tagLocation
)paren
comma
id|location
)paren
suffix:semicolon
r_goto
id|error_out
suffix:semicolon
)brace
multiline_comment|/* Verify the tag checksum */
id|checksum
op_assign
l_int|0U
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
l_int|4
suffix:semicolon
id|i
op_increment
)paren
id|checksum
op_add_assign
(paren
r_uint8
)paren
(paren
id|bh-&gt;b_data
(braket
id|i
)braket
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|5
suffix:semicolon
id|i
OL
l_int|16
suffix:semicolon
id|i
op_increment
)paren
id|checksum
op_add_assign
(paren
r_uint8
)paren
(paren
id|bh-&gt;b_data
(braket
id|i
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|checksum
op_ne
id|tag_p-&gt;tagChecksum
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;udf: tag checksum failed block %d&bslash;n&quot;
comma
id|block
)paren
suffix:semicolon
r_goto
id|error_out
suffix:semicolon
)brace
multiline_comment|/* Verify the tag version */
r_if
c_cond
(paren
id|le16_to_cpu
c_func
(paren
id|tag_p-&gt;descVersion
)paren
op_ne
l_int|0x0002U
op_logical_and
id|le16_to_cpu
c_func
(paren
id|tag_p-&gt;descVersion
)paren
op_ne
l_int|0x0003U
)paren
(brace
id|udf_debug
c_func
(paren
l_string|&quot;tag version 0x%04x != 0x0002 || 0x0003 block %d&bslash;n&quot;
comma
id|le16_to_cpu
c_func
(paren
id|tag_p-&gt;descVersion
)paren
comma
id|block
)paren
suffix:semicolon
r_goto
id|error_out
suffix:semicolon
)brace
multiline_comment|/* Verify the descriptor CRC */
r_if
c_cond
(paren
id|le16_to_cpu
c_func
(paren
id|tag_p-&gt;descCRCLength
)paren
op_plus
r_sizeof
(paren
id|tag
)paren
OG
id|sb-&gt;s_blocksize
op_logical_or
id|le16_to_cpu
c_func
(paren
id|tag_p-&gt;descCRC
)paren
op_eq
id|udf_crc
c_func
(paren
id|bh-&gt;b_data
op_plus
r_sizeof
(paren
id|tag
)paren
comma
id|le16_to_cpu
c_func
(paren
id|tag_p-&gt;descCRCLength
)paren
comma
l_int|0
)paren
)paren
(brace
r_return
id|bh
suffix:semicolon
)brace
id|udf_debug
c_func
(paren
l_string|&quot;Crc failure block %d: crc = %d, crclen = %d&bslash;n&quot;
comma
id|block
op_plus
id|UDF_SB_SESSION
c_func
(paren
id|sb
)paren
comma
id|le16_to_cpu
c_func
(paren
id|tag_p-&gt;descCRC
)paren
comma
id|le16_to_cpu
c_func
(paren
id|tag_p-&gt;descCRCLength
)paren
)paren
suffix:semicolon
id|error_out
suffix:colon
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
r_struct
id|buffer_head
op_star
DECL|function|udf_read_ptagged
id|udf_read_ptagged
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
id|lb_addr
id|loc
comma
r_uint32
id|offset
comma
r_uint16
op_star
id|ident
)paren
(brace
r_return
id|udf_read_tagged
c_func
(paren
id|sb
comma
id|udf_get_lb_pblock
c_func
(paren
id|sb
comma
id|loc
comma
id|offset
)paren
comma
id|loc.logicalBlockNum
op_plus
id|offset
comma
id|ident
)paren
suffix:semicolon
)brace
DECL|function|udf_release_data
r_void
id|udf_release_data
c_func
(paren
r_struct
id|buffer_head
op_star
id|bh
)paren
(brace
r_if
c_cond
(paren
id|bh
)paren
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
)brace
DECL|function|udf_update_tag
r_void
id|udf_update_tag
c_func
(paren
r_char
op_star
id|data
comma
r_int
id|length
)paren
(brace
id|tag
op_star
id|tptr
op_assign
(paren
id|tag
op_star
)paren
id|data
suffix:semicolon
r_int
id|i
suffix:semicolon
id|length
op_sub_assign
r_sizeof
(paren
id|tag
)paren
suffix:semicolon
id|tptr-&gt;tagChecksum
op_assign
l_int|0
suffix:semicolon
id|tptr-&gt;descCRCLength
op_assign
id|le16_to_cpu
c_func
(paren
id|length
)paren
suffix:semicolon
id|tptr-&gt;descCRC
op_assign
id|le16_to_cpu
c_func
(paren
id|udf_crc
c_func
(paren
id|data
op_plus
r_sizeof
(paren
id|tag
)paren
comma
id|length
comma
l_int|0
)paren
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
l_int|16
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|i
op_ne
l_int|4
)paren
id|tptr-&gt;tagChecksum
op_add_assign
(paren
r_uint8
)paren
(paren
id|data
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
DECL|function|udf_new_tag
r_void
id|udf_new_tag
c_func
(paren
r_char
op_star
id|data
comma
r_uint16
id|ident
comma
r_uint16
id|version
comma
r_uint16
id|snum
comma
r_uint32
id|loc
comma
r_int
id|length
)paren
(brace
id|tag
op_star
id|tptr
op_assign
(paren
id|tag
op_star
)paren
id|data
suffix:semicolon
id|tptr-&gt;tagIdent
op_assign
id|le16_to_cpu
c_func
(paren
id|ident
)paren
suffix:semicolon
id|tptr-&gt;descVersion
op_assign
id|le16_to_cpu
c_func
(paren
id|version
)paren
suffix:semicolon
id|tptr-&gt;tagSerialNum
op_assign
id|le16_to_cpu
c_func
(paren
id|snum
)paren
suffix:semicolon
id|tptr-&gt;tagLocation
op_assign
id|le32_to_cpu
c_func
(paren
id|loc
)paren
suffix:semicolon
id|udf_update_tag
c_func
(paren
id|data
comma
id|length
)paren
suffix:semicolon
)brace
eof
