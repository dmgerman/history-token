macro_line|#ifndef __CODA_PSDEV_H
DECL|macro|__CODA_PSDEV_H
mdefine_line|#define __CODA_PSDEV_H
DECL|macro|CODA_PSDEV_MAJOR
mdefine_line|#define CODA_PSDEV_MAJOR 67
DECL|macro|MAX_CODADEVS
mdefine_line|#define MAX_CODADEVS  5&t;   /* how many do we allow */
DECL|macro|CODA_SUPER_MAGIC
mdefine_line|#define CODA_SUPER_MAGIC&t;0x73757245
r_struct
id|statfs
suffix:semicolon
DECL|struct|coda_sb_info
r_struct
id|coda_sb_info
(brace
DECL|member|sbi_vcomm
r_struct
id|venus_comm
op_star
id|sbi_vcomm
suffix:semicolon
DECL|member|sbi_sb
r_struct
id|super_block
op_star
id|sbi_sb
suffix:semicolon
DECL|member|sbi_cihead
r_struct
id|list_head
id|sbi_cihead
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* communication pending/processing queues */
DECL|struct|venus_comm
r_struct
id|venus_comm
(brace
DECL|member|vc_seq
id|u_long
id|vc_seq
suffix:semicolon
DECL|member|vc_waitq
id|wait_queue_head_t
id|vc_waitq
suffix:semicolon
multiline_comment|/* Venus wait queue */
DECL|member|vc_pending
r_struct
id|list_head
id|vc_pending
suffix:semicolon
DECL|member|vc_processing
r_struct
id|list_head
id|vc_processing
suffix:semicolon
DECL|member|vc_inuse
r_int
id|vc_inuse
suffix:semicolon
DECL|member|vc_sb
r_struct
id|super_block
op_star
id|vc_sb
suffix:semicolon
)brace
suffix:semicolon
DECL|function|coda_sbp
r_static
r_inline
r_struct
id|coda_sb_info
op_star
id|coda_sbp
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_return
(paren
(paren
r_struct
id|coda_sb_info
op_star
)paren
(paren
(paren
id|sb
)paren
op_member_access_from_pointer
id|s_fs_info
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* upcalls */
r_int
id|venus_rootfid
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
id|ViceFid
op_star
id|fidp
)paren
suffix:semicolon
r_int
id|venus_getattr
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|ViceFid
op_star
id|fid
comma
r_struct
id|coda_vattr
op_star
id|attr
)paren
suffix:semicolon
r_int
id|venus_setattr
c_func
(paren
r_struct
id|super_block
op_star
comma
r_struct
id|ViceFid
op_star
comma
r_struct
id|coda_vattr
op_star
)paren
suffix:semicolon
r_int
id|venus_lookup
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|ViceFid
op_star
id|fid
comma
r_const
r_char
op_star
id|name
comma
r_int
id|length
comma
r_int
op_star
id|type
comma
r_struct
id|ViceFid
op_star
id|resfid
)paren
suffix:semicolon
r_int
id|venus_store
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|ViceFid
op_star
id|fid
comma
r_int
id|flags
comma
r_struct
id|coda_cred
op_star
)paren
suffix:semicolon
r_int
id|venus_release
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|ViceFid
op_star
id|fid
comma
r_int
id|flags
)paren
suffix:semicolon
r_int
id|venus_close
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|ViceFid
op_star
id|fid
comma
r_int
id|flags
comma
r_struct
id|coda_cred
op_star
)paren
suffix:semicolon
r_int
id|venus_open
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|ViceFid
op_star
id|fid
comma
r_int
id|flags
comma
r_struct
id|file
op_star
op_star
id|f
)paren
suffix:semicolon
r_int
id|venus_mkdir
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|ViceFid
op_star
id|dirfid
comma
r_const
r_char
op_star
id|name
comma
r_int
id|length
comma
r_struct
id|ViceFid
op_star
id|newfid
comma
r_struct
id|coda_vattr
op_star
id|attrs
)paren
suffix:semicolon
r_int
id|venus_create
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|ViceFid
op_star
id|dirfid
comma
r_const
r_char
op_star
id|name
comma
r_int
id|length
comma
r_int
id|excl
comma
r_int
id|mode
comma
id|dev_t
id|rdev
comma
r_struct
id|ViceFid
op_star
id|newfid
comma
r_struct
id|coda_vattr
op_star
id|attrs
)paren
suffix:semicolon
r_int
id|venus_rmdir
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|ViceFid
op_star
id|dirfid
comma
r_const
r_char
op_star
id|name
comma
r_int
id|length
)paren
suffix:semicolon
r_int
id|venus_remove
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|ViceFid
op_star
id|dirfid
comma
r_const
r_char
op_star
id|name
comma
r_int
id|length
)paren
suffix:semicolon
r_int
id|venus_readlink
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|ViceFid
op_star
id|fid
comma
r_char
op_star
id|buffer
comma
r_int
op_star
id|length
)paren
suffix:semicolon
r_int
id|venus_rename
c_func
(paren
r_struct
id|super_block
op_star
comma
r_struct
id|ViceFid
op_star
id|new_fid
comma
r_struct
id|ViceFid
op_star
id|old_fid
comma
r_int
id|old_length
comma
r_int
id|new_length
comma
r_const
r_char
op_star
id|old_name
comma
r_const
r_char
op_star
id|new_name
)paren
suffix:semicolon
r_int
id|venus_link
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|ViceFid
op_star
id|fid
comma
r_struct
id|ViceFid
op_star
id|dirfid
comma
r_const
r_char
op_star
id|name
comma
r_int
id|len
)paren
suffix:semicolon
r_int
id|venus_symlink
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|ViceFid
op_star
id|fid
comma
r_const
r_char
op_star
id|name
comma
r_int
id|len
comma
r_const
r_char
op_star
id|symname
comma
r_int
id|symlen
)paren
suffix:semicolon
r_int
id|venus_access
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|ViceFid
op_star
id|fid
comma
r_int
id|mask
)paren
suffix:semicolon
r_int
id|venus_pioctl
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|ViceFid
op_star
id|fid
comma
r_int
r_int
id|cmd
comma
r_struct
id|PioctlData
op_star
id|data
)paren
suffix:semicolon
r_int
id|coda_downcall
c_func
(paren
r_int
id|opcode
comma
r_union
id|outputArgs
op_star
id|out
comma
r_struct
id|super_block
op_star
id|sb
)paren
suffix:semicolon
r_int
id|venus_fsync
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|ViceFid
op_star
id|fid
)paren
suffix:semicolon
r_int
id|venus_statfs
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|kstatfs
op_star
id|sfs
)paren
suffix:semicolon
multiline_comment|/* messages between coda filesystem in kernel and Venus */
r_extern
r_int
id|coda_hard
suffix:semicolon
r_extern
r_int
r_int
id|coda_timeout
suffix:semicolon
DECL|struct|upc_req
r_struct
id|upc_req
(brace
DECL|member|uc_chain
r_struct
id|list_head
id|uc_chain
suffix:semicolon
DECL|member|uc_data
id|caddr_t
id|uc_data
suffix:semicolon
DECL|member|uc_flags
id|u_short
id|uc_flags
suffix:semicolon
DECL|member|uc_inSize
id|u_short
id|uc_inSize
suffix:semicolon
multiline_comment|/* Size is at most 5000 bytes */
DECL|member|uc_outSize
id|u_short
id|uc_outSize
suffix:semicolon
DECL|member|uc_opcode
id|u_short
id|uc_opcode
suffix:semicolon
multiline_comment|/* copied from data to save lookup */
DECL|member|uc_unique
r_int
id|uc_unique
suffix:semicolon
DECL|member|uc_sleep
id|wait_queue_head_t
id|uc_sleep
suffix:semicolon
multiline_comment|/* process&squot; wait queue */
DECL|member|uc_posttime
r_int
r_int
id|uc_posttime
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|REQ_ASYNC
mdefine_line|#define REQ_ASYNC  0x1
DECL|macro|REQ_READ
mdefine_line|#define REQ_READ   0x2
DECL|macro|REQ_WRITE
mdefine_line|#define REQ_WRITE  0x4
DECL|macro|REQ_ABORT
mdefine_line|#define REQ_ABORT  0x8
multiline_comment|/*&n; * Statistics&n; */
r_extern
r_struct
id|venus_comm
id|coda_comms
(braket
)braket
suffix:semicolon
macro_line|#endif
eof
