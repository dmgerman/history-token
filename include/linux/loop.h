macro_line|#ifndef _LINUX_LOOP_H
DECL|macro|_LINUX_LOOP_H
mdefine_line|#define _LINUX_LOOP_H
multiline_comment|/*&n; * include/linux/loop.h&n; *&n; * Written by Theodore Ts&squot;o, 3/29/93.&n; *&n; * Copyright 1993 by Theodore Ts&squot;o.  Redistribution of this file is&n; * permitted under the GNU General Public License.&n; */
DECL|macro|LO_NAME_SIZE
mdefine_line|#define LO_NAME_SIZE&t;64
DECL|macro|LO_KEY_SIZE
mdefine_line|#define LO_KEY_SIZE&t;32
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/bio.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
multiline_comment|/* Possible states of device */
r_enum
(brace
DECL|enumerator|Lo_unbound
id|Lo_unbound
comma
DECL|enumerator|Lo_bound
id|Lo_bound
comma
DECL|enumerator|Lo_rundown
id|Lo_rundown
comma
)brace
suffix:semicolon
r_struct
id|loop_func_table
suffix:semicolon
DECL|struct|loop_device
r_struct
id|loop_device
(brace
DECL|member|lo_number
r_int
id|lo_number
suffix:semicolon
DECL|member|lo_refcnt
r_int
id|lo_refcnt
suffix:semicolon
DECL|member|lo_offset
r_int
id|lo_offset
suffix:semicolon
DECL|member|lo_flags
r_int
id|lo_flags
suffix:semicolon
DECL|member|transfer
r_int
(paren
op_star
id|transfer
)paren
(paren
r_struct
id|loop_device
op_star
comma
r_int
id|cmd
comma
r_char
op_star
id|raw_buf
comma
r_char
op_star
id|loop_buf
comma
r_int
id|size
comma
id|sector_t
id|real_block
)paren
suffix:semicolon
DECL|member|lo_name
r_char
id|lo_name
(braket
id|LO_NAME_SIZE
)braket
suffix:semicolon
DECL|member|lo_encrypt_key
r_char
id|lo_encrypt_key
(braket
id|LO_KEY_SIZE
)braket
suffix:semicolon
DECL|member|lo_encrypt_key_size
r_int
id|lo_encrypt_key_size
suffix:semicolon
DECL|member|lo_encryption
r_struct
id|loop_func_table
op_star
id|lo_encryption
suffix:semicolon
DECL|member|lo_init
id|__u32
id|lo_init
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|lo_key_owner
id|uid_t
id|lo_key_owner
suffix:semicolon
multiline_comment|/* Who set the key */
DECL|member|ioctl
r_int
(paren
op_star
id|ioctl
)paren
(paren
r_struct
id|loop_device
op_star
comma
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
DECL|member|lo_backing_file
r_struct
id|file
op_star
id|lo_backing_file
suffix:semicolon
DECL|member|lo_device
r_struct
id|block_device
op_star
id|lo_device
suffix:semicolon
DECL|member|lo_blocksize
r_int
id|lo_blocksize
suffix:semicolon
DECL|member|key_data
r_void
op_star
id|key_data
suffix:semicolon
DECL|member|key_reserved
r_char
id|key_reserved
(braket
l_int|48
)braket
suffix:semicolon
multiline_comment|/* for use by the filter modules */
DECL|member|old_gfp_mask
r_int
id|old_gfp_mask
suffix:semicolon
DECL|member|lo_lock
id|spinlock_t
id|lo_lock
suffix:semicolon
DECL|member|lo_bio
r_struct
id|bio
op_star
id|lo_bio
suffix:semicolon
DECL|member|lo_biotail
r_struct
id|bio
op_star
id|lo_biotail
suffix:semicolon
DECL|member|lo_state
r_int
id|lo_state
suffix:semicolon
DECL|member|lo_sem
r_struct
id|semaphore
id|lo_sem
suffix:semicolon
DECL|member|lo_ctl_mutex
r_struct
id|semaphore
id|lo_ctl_mutex
suffix:semicolon
DECL|member|lo_bh_mutex
r_struct
id|semaphore
id|lo_bh_mutex
suffix:semicolon
DECL|member|lo_pending
id|atomic_t
id|lo_pending
suffix:semicolon
DECL|member|lo_queue
id|request_queue_t
id|lo_queue
suffix:semicolon
)brace
suffix:semicolon
DECL|typedef|transfer_proc_t
r_typedef
r_int
(paren
op_star
id|transfer_proc_t
)paren
(paren
r_struct
id|loop_device
op_star
comma
r_int
id|cmd
comma
r_char
op_star
id|raw_buf
comma
r_char
op_star
id|loop_buf
comma
r_int
id|size
comma
r_int
id|real_block
)paren
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
multiline_comment|/*&n; * Loop flags&n; */
DECL|macro|LO_FLAGS_DO_BMAP
mdefine_line|#define LO_FLAGS_DO_BMAP&t;1
DECL|macro|LO_FLAGS_READ_ONLY
mdefine_line|#define LO_FLAGS_READ_ONLY&t;2
macro_line|#include &lt;asm/posix_types.h&gt;&t;/* for __kernel_old_dev_t */
macro_line|#include &lt;asm/types.h&gt;&t;&t;/* for __u64 */
multiline_comment|/* Backwards compatibility version */
DECL|struct|loop_info
r_struct
id|loop_info
(brace
DECL|member|lo_number
r_int
id|lo_number
suffix:semicolon
multiline_comment|/* ioctl r/o */
DECL|member|lo_device
id|__kernel_old_dev_t
id|lo_device
suffix:semicolon
multiline_comment|/* ioctl r/o */
DECL|member|lo_inode
r_int
r_int
id|lo_inode
suffix:semicolon
multiline_comment|/* ioctl r/o */
DECL|member|lo_rdevice
id|__kernel_old_dev_t
id|lo_rdevice
suffix:semicolon
multiline_comment|/* ioctl r/o */
DECL|member|lo_offset
r_int
id|lo_offset
suffix:semicolon
DECL|member|lo_encrypt_type
r_int
id|lo_encrypt_type
suffix:semicolon
DECL|member|lo_encrypt_key_size
r_int
id|lo_encrypt_key_size
suffix:semicolon
multiline_comment|/* ioctl w/o */
DECL|member|lo_flags
r_int
id|lo_flags
suffix:semicolon
multiline_comment|/* ioctl r/o */
DECL|member|lo_name
r_char
id|lo_name
(braket
id|LO_NAME_SIZE
)braket
suffix:semicolon
DECL|member|lo_encrypt_key
r_int
r_char
id|lo_encrypt_key
(braket
id|LO_KEY_SIZE
)braket
suffix:semicolon
multiline_comment|/* ioctl w/o */
DECL|member|lo_init
r_int
r_int
id|lo_init
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|reserved
r_char
id|reserved
(braket
l_int|4
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|loop_info64
r_struct
id|loop_info64
(brace
DECL|member|lo_device
id|__u64
id|lo_device
suffix:semicolon
multiline_comment|/* ioctl r/o */
DECL|member|lo_inode
id|__u64
id|lo_inode
suffix:semicolon
multiline_comment|/* ioctl r/o */
DECL|member|lo_rdevice
id|__u64
id|lo_rdevice
suffix:semicolon
multiline_comment|/* ioctl r/o */
DECL|member|lo_offset
id|__u64
id|lo_offset
suffix:semicolon
DECL|member|lo_number
id|__u32
id|lo_number
suffix:semicolon
multiline_comment|/* ioctl r/o */
DECL|member|lo_encrypt_type
id|__u32
id|lo_encrypt_type
suffix:semicolon
DECL|member|lo_encrypt_key_size
id|__u32
id|lo_encrypt_key_size
suffix:semicolon
multiline_comment|/* ioctl w/o */
DECL|member|lo_flags
id|__u32
id|lo_flags
suffix:semicolon
multiline_comment|/* ioctl r/o */
DECL|member|lo_name
id|__u8
id|lo_name
(braket
id|LO_NAME_SIZE
)braket
suffix:semicolon
DECL|member|lo_encrypt_key
id|__u8
id|lo_encrypt_key
(braket
id|LO_KEY_SIZE
)braket
suffix:semicolon
multiline_comment|/* ioctl w/o */
DECL|member|lo_init
id|__u64
id|lo_init
(braket
l_int|2
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Loop filter types&n; */
DECL|macro|LO_CRYPT_NONE
mdefine_line|#define LO_CRYPT_NONE&t;  0
DECL|macro|LO_CRYPT_XOR
mdefine_line|#define LO_CRYPT_XOR&t;  1
DECL|macro|LO_CRYPT_DES
mdefine_line|#define LO_CRYPT_DES&t;  2
DECL|macro|LO_CRYPT_FISH2
mdefine_line|#define LO_CRYPT_FISH2    3    /* Brand new Twofish encryption */
DECL|macro|LO_CRYPT_BLOW
mdefine_line|#define LO_CRYPT_BLOW     4
DECL|macro|LO_CRYPT_CAST128
mdefine_line|#define LO_CRYPT_CAST128  5
DECL|macro|LO_CRYPT_IDEA
mdefine_line|#define LO_CRYPT_IDEA     6
DECL|macro|LO_CRYPT_DUMMY
mdefine_line|#define LO_CRYPT_DUMMY    9
DECL|macro|LO_CRYPT_SKIPJACK
mdefine_line|#define LO_CRYPT_SKIPJACK 10
DECL|macro|MAX_LO_CRYPT
mdefine_line|#define MAX_LO_CRYPT&t;20
macro_line|#ifdef __KERNEL__
multiline_comment|/* Support for loadable transfer modules */
DECL|struct|loop_func_table
r_struct
id|loop_func_table
(brace
DECL|member|number
r_int
id|number
suffix:semicolon
multiline_comment|/* filter type */
DECL|member|transfer
r_int
(paren
op_star
id|transfer
)paren
(paren
r_struct
id|loop_device
op_star
id|lo
comma
r_int
id|cmd
comma
r_char
op_star
id|raw_buf
comma
r_char
op_star
id|loop_buf
comma
r_int
id|size
comma
id|sector_t
id|real_block
)paren
suffix:semicolon
DECL|member|init
r_int
(paren
op_star
id|init
)paren
(paren
r_struct
id|loop_device
op_star
comma
r_const
r_struct
id|loop_info64
op_star
)paren
suffix:semicolon
multiline_comment|/* release is called from loop_unregister_transfer or clr_fd */
DECL|member|release
r_int
(paren
op_star
id|release
)paren
(paren
r_struct
id|loop_device
op_star
)paren
suffix:semicolon
DECL|member|ioctl
r_int
(paren
op_star
id|ioctl
)paren
(paren
r_struct
id|loop_device
op_star
comma
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
DECL|member|owner
r_struct
id|module
op_star
id|owner
suffix:semicolon
)brace
suffix:semicolon
r_int
id|loop_register_transfer
c_func
(paren
r_struct
id|loop_func_table
op_star
id|funcs
)paren
suffix:semicolon
r_int
id|loop_unregister_transfer
c_func
(paren
r_int
id|number
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * IOCTL commands --- we will commandeer 0x4C (&squot;L&squot;)&n; */
DECL|macro|LOOP_SET_FD
mdefine_line|#define LOOP_SET_FD&t;&t;0x4C00
DECL|macro|LOOP_CLR_FD
mdefine_line|#define LOOP_CLR_FD&t;&t;0x4C01
DECL|macro|LOOP_SET_STATUS
mdefine_line|#define LOOP_SET_STATUS&t;&t;0x4C02
DECL|macro|LOOP_GET_STATUS
mdefine_line|#define LOOP_GET_STATUS&t;&t;0x4C03
DECL|macro|LOOP_SET_STATUS64
mdefine_line|#define LOOP_SET_STATUS64&t;0x4C04
DECL|macro|LOOP_GET_STATUS64
mdefine_line|#define LOOP_GET_STATUS64&t;0x4C05
macro_line|#endif
eof
