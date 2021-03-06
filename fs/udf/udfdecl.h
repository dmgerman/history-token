macro_line|#ifndef __UDF_DECL_H
DECL|macro|__UDF_DECL_H
mdefine_line|#define __UDF_DECL_H
macro_line|#include &lt;linux/udf_fs.h&gt;
macro_line|#include &quot;ecma_167.h&quot;
macro_line|#include &quot;osta_udf.h&quot;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/udf_fs_i.h&gt;
macro_line|#include &lt;linux/udf_fs_sb.h&gt;
macro_line|#include &lt;linux/buffer_head.h&gt;
macro_line|#include &quot;udfend.h&quot;
DECL|macro|udf_fixed_to_variable
mdefine_line|#define udf_fixed_to_variable(x) ( ( ( (x) &gt;&gt; 5 ) * 39 ) + ( (x) &amp; 0x0000001F ) )
DECL|macro|udf_variable_to_fixed
mdefine_line|#define udf_variable_to_fixed(x) ( ( ( (x) / 39 ) &lt;&lt; 5 ) + ( (x) % 39 ) )
DECL|macro|UDF_EXTENT_LENGTH_MASK
mdefine_line|#define UDF_EXTENT_LENGTH_MASK&t;0x3FFFFFFF
DECL|macro|UDF_EXTENT_FLAG_MASK
mdefine_line|#define UDF_EXTENT_FLAG_MASK&t;0xC0000000
DECL|macro|UDF_NAME_PAD
mdefine_line|#define UDF_NAME_PAD&t;&t;4
DECL|macro|UDF_NAME_LEN
mdefine_line|#define UDF_NAME_LEN&t;&t;256
DECL|macro|UDF_PATH_LEN
mdefine_line|#define UDF_PATH_LEN&t;&t;1023
DECL|macro|udf_file_entry_alloc_offset
mdefine_line|#define udf_file_entry_alloc_offset(inode)&bslash;&n;&t;(UDF_I_USE(inode) ?&bslash;&n;&t;&t;sizeof(struct unallocSpaceEntry) :&bslash;&n;&t;&t;((UDF_I_EFE(inode) ?&bslash;&n;&t;&t;&t;sizeof(struct extendedFileEntry) :&bslash;&n;&t;&t;&t;sizeof(struct fileEntry)) + UDF_I_LENEATTR(inode)))
DECL|macro|udf_ext0_offset
mdefine_line|#define udf_ext0_offset(inode)&bslash;&n;&t;(UDF_I_ALLOCTYPE(inode) == ICBTAG_FLAG_AD_IN_ICB ?&bslash;&n;&t;&t;udf_file_entry_alloc_offset(inode) : 0)
DECL|macro|udf_get_lb_pblock
mdefine_line|#define udf_get_lb_pblock(sb,loc,offset) udf_get_pblock((sb), (loc).logicalBlockNum, (loc).partitionReferenceNum, (offset))
r_struct
id|dentry
suffix:semicolon
r_struct
id|inode
suffix:semicolon
r_struct
id|task_struct
suffix:semicolon
r_struct
id|buffer_head
suffix:semicolon
r_struct
id|super_block
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|udf_dir_inode_operations
suffix:semicolon
r_extern
r_struct
id|file_operations
id|udf_dir_operations
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|udf_file_inode_operations
suffix:semicolon
r_extern
r_struct
id|file_operations
id|udf_file_operations
suffix:semicolon
r_extern
r_struct
id|address_space_operations
id|udf_aops
suffix:semicolon
r_extern
r_struct
id|address_space_operations
id|udf_adinicb_aops
suffix:semicolon
r_extern
r_struct
id|address_space_operations
id|udf_symlink_aops
suffix:semicolon
DECL|struct|udf_fileident_bh
r_struct
id|udf_fileident_bh
(brace
DECL|member|sbh
r_struct
id|buffer_head
op_star
id|sbh
suffix:semicolon
DECL|member|ebh
r_struct
id|buffer_head
op_star
id|ebh
suffix:semicolon
DECL|member|soffset
r_int
id|soffset
suffix:semicolon
DECL|member|eoffset
r_int
id|eoffset
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|udf_vds_record
r_struct
id|udf_vds_record
(brace
DECL|member|block
r_uint32
id|block
suffix:semicolon
DECL|member|volDescSeqNum
r_uint32
id|volDescSeqNum
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|generic_desc
r_struct
id|generic_desc
(brace
DECL|member|descTag
id|tag
id|descTag
suffix:semicolon
DECL|member|volDescSeqNum
id|__le32
id|volDescSeqNum
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ustr
r_struct
id|ustr
(brace
DECL|member|u_cmpID
r_uint8
id|u_cmpID
suffix:semicolon
DECL|member|u_name
r_uint8
id|u_name
(braket
id|UDF_NAME_LEN
op_minus
l_int|2
)braket
suffix:semicolon
DECL|member|u_len
r_uint8
id|u_len
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* super.c */
r_extern
r_void
id|udf_error
c_func
(paren
r_struct
id|super_block
op_star
comma
r_const
r_char
op_star
comma
r_const
r_char
op_star
comma
dot
dot
dot
)paren
suffix:semicolon
r_extern
r_void
id|udf_warning
c_func
(paren
r_struct
id|super_block
op_star
comma
r_const
r_char
op_star
comma
r_const
r_char
op_star
comma
dot
dot
dot
)paren
suffix:semicolon
multiline_comment|/* namei.c */
r_extern
r_int
id|udf_write_fi
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|fileIdentDesc
op_star
comma
r_struct
id|fileIdentDesc
op_star
comma
r_struct
id|udf_fileident_bh
op_star
comma
r_uint8
op_star
comma
r_uint8
op_star
)paren
suffix:semicolon
multiline_comment|/* file.c */
r_extern
r_int
id|udf_ioctl
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
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/* inode.c */
r_extern
r_struct
id|inode
op_star
id|udf_iget
c_func
(paren
r_struct
id|super_block
op_star
comma
id|kernel_lb_addr
)paren
suffix:semicolon
r_extern
r_int
id|udf_sync_inode
c_func
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_void
id|udf_expand_file_adinicb
c_func
(paren
r_struct
id|inode
op_star
comma
r_int
comma
r_int
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|buffer_head
op_star
id|udf_expand_dir_adinicb
c_func
(paren
r_struct
id|inode
op_star
comma
r_int
op_star
comma
r_int
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|buffer_head
op_star
id|udf_bread
c_func
(paren
r_struct
id|inode
op_star
comma
r_int
comma
r_int
comma
r_int
op_star
)paren
suffix:semicolon
r_extern
r_void
id|udf_truncate
c_func
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_void
id|udf_read_inode
c_func
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_void
id|udf_delete_inode
c_func
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_void
id|udf_clear_inode
c_func
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_int
id|udf_write_inode
c_func
(paren
r_struct
id|inode
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|udf_block_map
c_func
(paren
r_struct
id|inode
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int8
id|inode_bmap
c_func
(paren
r_struct
id|inode
op_star
comma
r_int
comma
id|kernel_lb_addr
op_star
comma
r_uint32
op_star
comma
id|kernel_lb_addr
op_star
comma
r_uint32
op_star
comma
r_uint32
op_star
comma
r_struct
id|buffer_head
op_star
op_star
)paren
suffix:semicolon
r_extern
r_int8
id|udf_add_aext
c_func
(paren
r_struct
id|inode
op_star
comma
id|kernel_lb_addr
op_star
comma
r_int
op_star
comma
id|kernel_lb_addr
comma
r_uint32
comma
r_struct
id|buffer_head
op_star
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int8
id|udf_write_aext
c_func
(paren
r_struct
id|inode
op_star
comma
id|kernel_lb_addr
comma
r_int
op_star
comma
id|kernel_lb_addr
comma
r_uint32
comma
r_struct
id|buffer_head
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int8
id|udf_delete_aext
c_func
(paren
r_struct
id|inode
op_star
comma
id|kernel_lb_addr
comma
r_int
comma
id|kernel_lb_addr
comma
r_uint32
comma
r_struct
id|buffer_head
op_star
)paren
suffix:semicolon
r_extern
r_int8
id|udf_next_aext
c_func
(paren
r_struct
id|inode
op_star
comma
id|kernel_lb_addr
op_star
comma
r_int
op_star
comma
id|kernel_lb_addr
op_star
comma
r_uint32
op_star
comma
r_struct
id|buffer_head
op_star
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int8
id|udf_current_aext
c_func
(paren
r_struct
id|inode
op_star
comma
id|kernel_lb_addr
op_star
comma
r_int
op_star
comma
id|kernel_lb_addr
op_star
comma
r_uint32
op_star
comma
r_struct
id|buffer_head
op_star
op_star
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* misc.c */
r_extern
r_struct
id|buffer_head
op_star
id|udf_tgetblk
c_func
(paren
r_struct
id|super_block
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_struct
id|buffer_head
op_star
id|udf_tread
c_func
(paren
r_struct
id|super_block
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_struct
id|genericFormat
op_star
id|udf_add_extendedattr
c_func
(paren
r_struct
id|inode
op_star
comma
r_uint32
comma
r_uint32
comma
r_uint8
)paren
suffix:semicolon
r_extern
r_struct
id|genericFormat
op_star
id|udf_get_extendedattr
c_func
(paren
r_struct
id|inode
op_star
comma
r_uint32
comma
r_uint8
)paren
suffix:semicolon
r_extern
r_struct
id|buffer_head
op_star
id|udf_read_tagged
c_func
(paren
r_struct
id|super_block
op_star
comma
r_uint32
comma
r_uint32
comma
r_uint16
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|buffer_head
op_star
id|udf_read_ptagged
c_func
(paren
r_struct
id|super_block
op_star
comma
id|kernel_lb_addr
comma
r_uint32
comma
r_uint16
op_star
)paren
suffix:semicolon
r_extern
r_void
id|udf_release_data
c_func
(paren
r_struct
id|buffer_head
op_star
)paren
suffix:semicolon
r_extern
r_void
id|udf_update_tag
c_func
(paren
r_char
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|udf_new_tag
c_func
(paren
r_char
op_star
comma
r_uint16
comma
r_uint16
comma
r_uint16
comma
r_uint32
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* lowlevel.c */
r_extern
r_int
r_int
id|udf_get_last_session
c_func
(paren
r_struct
id|super_block
op_star
)paren
suffix:semicolon
r_extern
r_int
r_int
id|udf_get_last_block
c_func
(paren
r_struct
id|super_block
op_star
)paren
suffix:semicolon
multiline_comment|/* partition.c */
r_extern
r_uint32
id|udf_get_pblock
c_func
(paren
r_struct
id|super_block
op_star
comma
r_uint32
comma
r_uint16
comma
r_uint32
)paren
suffix:semicolon
r_extern
r_uint32
id|udf_get_pblock_virt15
c_func
(paren
r_struct
id|super_block
op_star
comma
r_uint32
comma
r_uint16
comma
r_uint32
)paren
suffix:semicolon
r_extern
r_uint32
id|udf_get_pblock_virt20
c_func
(paren
r_struct
id|super_block
op_star
comma
r_uint32
comma
r_uint16
comma
r_uint32
)paren
suffix:semicolon
r_extern
r_uint32
id|udf_get_pblock_spar15
c_func
(paren
r_struct
id|super_block
op_star
comma
r_uint32
comma
r_uint16
comma
r_uint32
)paren
suffix:semicolon
r_extern
r_int
id|udf_relocate_blocks
c_func
(paren
r_struct
id|super_block
op_star
comma
r_int
comma
r_int
op_star
)paren
suffix:semicolon
multiline_comment|/* unicode.c */
r_extern
r_int
id|udf_get_filename
c_func
(paren
r_struct
id|super_block
op_star
comma
r_uint8
op_star
comma
r_uint8
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|udf_put_filename
c_func
(paren
r_struct
id|super_block
op_star
comma
r_const
r_uint8
op_star
comma
r_uint8
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|udf_build_ustr
c_func
(paren
r_struct
id|ustr
op_star
comma
id|dstring
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|udf_CS0toUTF8
c_func
(paren
r_struct
id|ustr
op_star
comma
r_struct
id|ustr
op_star
)paren
suffix:semicolon
multiline_comment|/* ialloc.c */
r_extern
r_void
id|udf_free_inode
c_func
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|inode
op_star
id|udf_new_inode
(paren
r_struct
id|inode
op_star
comma
r_int
comma
r_int
op_star
)paren
suffix:semicolon
multiline_comment|/* truncate.c */
r_extern
r_void
id|udf_discard_prealloc
c_func
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_void
id|udf_truncate_extents
c_func
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
multiline_comment|/* balloc.c */
r_extern
r_void
id|udf_free_blocks
c_func
(paren
r_struct
id|super_block
op_star
comma
r_struct
id|inode
op_star
comma
id|kernel_lb_addr
comma
r_uint32
comma
r_uint32
)paren
suffix:semicolon
r_extern
r_int
id|udf_prealloc_blocks
c_func
(paren
r_struct
id|super_block
op_star
comma
r_struct
id|inode
op_star
comma
r_uint16
comma
r_uint32
comma
r_uint32
)paren
suffix:semicolon
r_extern
r_int
id|udf_new_block
c_func
(paren
r_struct
id|super_block
op_star
comma
r_struct
id|inode
op_star
comma
r_uint16
comma
r_uint32
comma
r_int
op_star
)paren
suffix:semicolon
multiline_comment|/* fsync.c */
r_extern
r_int
id|udf_fsync_file
c_func
(paren
r_struct
id|file
op_star
comma
r_struct
id|dentry
op_star
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* directory.c */
r_extern
r_struct
id|fileIdentDesc
op_star
id|udf_fileident_read
c_func
(paren
r_struct
id|inode
op_star
comma
id|loff_t
op_star
comma
r_struct
id|udf_fileident_bh
op_star
comma
r_struct
id|fileIdentDesc
op_star
comma
id|kernel_lb_addr
op_star
comma
r_uint32
op_star
comma
id|kernel_lb_addr
op_star
comma
r_uint32
op_star
comma
r_uint32
op_star
comma
r_struct
id|buffer_head
op_star
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|fileIdentDesc
op_star
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
suffix:semicolon
r_extern
id|long_ad
op_star
id|udf_get_filelongad
c_func
(paren
r_uint8
op_star
comma
r_int
comma
r_int
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
id|short_ad
op_star
id|udf_get_fileshortad
c_func
(paren
r_uint8
op_star
comma
r_int
comma
r_int
op_star
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* crc.c */
r_extern
r_uint16
id|udf_crc
c_func
(paren
r_uint8
op_star
comma
r_uint32
comma
r_uint16
)paren
suffix:semicolon
multiline_comment|/* udftime.c */
r_extern
id|time_t
op_star
id|udf_stamp_to_time
c_func
(paren
id|time_t
op_star
comma
r_int
op_star
comma
id|kernel_timestamp
)paren
suffix:semicolon
r_extern
id|kernel_timestamp
op_star
id|udf_time_to_stamp
c_func
(paren
id|kernel_timestamp
op_star
comma
r_struct
id|timespec
)paren
suffix:semicolon
macro_line|#endif /* __UDF_DECL_H */
eof
