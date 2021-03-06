multiline_comment|/*&n; *  c 2001 PPC 64 Team, IBM Corp&n; *&n; *      This program is free software; you can redistribute it and/or&n; *      modify it under the terms of the GNU General Public License&n; *      as published by the Free Software Foundation; either version&n; *      2 of the License, or (at your option) any later version.&n; *&n; * /proc/ppc64/rtas/firmware_flash interface&n; *&n; * This file implements a firmware_flash interface to pump a firmware&n; * image into the kernel.  At reboot time rtas_restart() will see the&n; * firmware image and flash it as it reboots (see rtas.c).&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;asm/delay.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/rtas.h&gt;
DECL|macro|MODULE_VERS
mdefine_line|#define MODULE_VERS &quot;1.0&quot;
DECL|macro|MODULE_NAME
mdefine_line|#define MODULE_NAME &quot;rtas_flash&quot;
DECL|macro|FIRMWARE_FLASH_NAME
mdefine_line|#define FIRMWARE_FLASH_NAME &quot;firmware_flash&quot;   
DECL|macro|FIRMWARE_UPDATE_NAME
mdefine_line|#define FIRMWARE_UPDATE_NAME &quot;firmware_update&quot;
DECL|macro|MANAGE_FLASH_NAME
mdefine_line|#define MANAGE_FLASH_NAME &quot;manage_flash&quot;
DECL|macro|VALIDATE_FLASH_NAME
mdefine_line|#define VALIDATE_FLASH_NAME &quot;validate_flash&quot;
multiline_comment|/* General RTAS Status Codes */
DECL|macro|RTAS_RC_SUCCESS
mdefine_line|#define RTAS_RC_SUCCESS  0
DECL|macro|RTAS_RC_HW_ERR
mdefine_line|#define RTAS_RC_HW_ERR&t;-1
DECL|macro|RTAS_RC_BUSY
mdefine_line|#define RTAS_RC_BUSY&t;-2
multiline_comment|/* Flash image status values */
DECL|macro|FLASH_AUTH
mdefine_line|#define FLASH_AUTH           -9002 /* RTAS Not Service Authority Partition */
DECL|macro|FLASH_NO_OP
mdefine_line|#define FLASH_NO_OP          -1099 /* No operation initiated by user */&t;
DECL|macro|FLASH_IMG_SHORT
mdefine_line|#define FLASH_IMG_SHORT&t;     -1005 /* Flash image shorter than expected */
DECL|macro|FLASH_IMG_BAD_LEN
mdefine_line|#define FLASH_IMG_BAD_LEN    -1004 /* Bad length value in flash list block */
DECL|macro|FLASH_IMG_NULL_DATA
mdefine_line|#define FLASH_IMG_NULL_DATA  -1003 /* Bad data value in flash list block */
DECL|macro|FLASH_IMG_READY
mdefine_line|#define FLASH_IMG_READY      0     /* Firmware img ready for flash on reboot */
multiline_comment|/* Manage image status values */
DECL|macro|MANAGE_AUTH
mdefine_line|#define MANAGE_AUTH          -9002 /* RTAS Not Service Authority Partition */
DECL|macro|MANAGE_ACTIVE_ERR
mdefine_line|#define MANAGE_ACTIVE_ERR    -9001 /* RTAS Cannot Overwrite Active Img */
DECL|macro|MANAGE_NO_OP
mdefine_line|#define MANAGE_NO_OP         -1099 /* No operation initiated by user */
DECL|macro|MANAGE_PARAM_ERR
mdefine_line|#define MANAGE_PARAM_ERR     -3    /* RTAS Parameter Error */
DECL|macro|MANAGE_HW_ERR
mdefine_line|#define MANAGE_HW_ERR        -1    /* RTAS Hardware Error */
multiline_comment|/* Validate image status values */
DECL|macro|VALIDATE_AUTH
mdefine_line|#define VALIDATE_AUTH          -9002 /* RTAS Not Service Authority Partition */
DECL|macro|VALIDATE_NO_OP
mdefine_line|#define VALIDATE_NO_OP         -1099 /* No operation initiated by the user */
DECL|macro|VALIDATE_INCOMPLETE
mdefine_line|#define VALIDATE_INCOMPLETE    -1002 /* User copied &lt; VALIDATE_BUF_SIZE */
DECL|macro|VALIDATE_READY
mdefine_line|#define VALIDATE_READY&t;       -1001 /* Firmware image ready for validation */
DECL|macro|VALIDATE_PARAM_ERR
mdefine_line|#define VALIDATE_PARAM_ERR     -3    /* RTAS Parameter Error */
DECL|macro|VALIDATE_HW_ERR
mdefine_line|#define VALIDATE_HW_ERR        -1    /* RTAS Hardware Error */
DECL|macro|VALIDATE_TMP_UPDATE
mdefine_line|#define VALIDATE_TMP_UPDATE    0     /* Validate Return Status */
DECL|macro|VALIDATE_FLASH_AUTH
mdefine_line|#define VALIDATE_FLASH_AUTH    1     /* Validate Return Status */
DECL|macro|VALIDATE_INVALID_IMG
mdefine_line|#define VALIDATE_INVALID_IMG   2     /* Validate Return Status */
DECL|macro|VALIDATE_CUR_UNKNOWN
mdefine_line|#define VALIDATE_CUR_UNKNOWN   3     /* Validate Return Status */
DECL|macro|VALIDATE_TMP_COMMIT_DL
mdefine_line|#define VALIDATE_TMP_COMMIT_DL 4     /* Validate Return Status */
DECL|macro|VALIDATE_TMP_COMMIT
mdefine_line|#define VALIDATE_TMP_COMMIT    5     /* Validate Return Status */
DECL|macro|VALIDATE_TMP_UPDATE_DL
mdefine_line|#define VALIDATE_TMP_UPDATE_DL 6     /* Validate Return Status */
multiline_comment|/* ibm,manage-flash-image operation tokens */
DECL|macro|RTAS_REJECT_TMP_IMG
mdefine_line|#define RTAS_REJECT_TMP_IMG   0
DECL|macro|RTAS_COMMIT_TMP_IMG
mdefine_line|#define RTAS_COMMIT_TMP_IMG   1
multiline_comment|/* Array sizes */
DECL|macro|VALIDATE_BUF_SIZE
mdefine_line|#define VALIDATE_BUF_SIZE 4096    
DECL|macro|RTAS_MSG_MAXLEN
mdefine_line|#define RTAS_MSG_MAXLEN   64
multiline_comment|/* Local copy of the flash block list.&n; * We only allow one open of the flash proc file and create this&n; * list as we go.  This list will be put in the kernel&squot;s&n; * rtas_firmware_flash_list global var once it is fully read.&n; *&n; * For convenience as we build the list we use virtual addrs,&n; * we do not fill in the version number, and the length field&n; * is treated as the number of entries currently in the block&n; * (i.e. not a byte count).  This is all fixed on release.&n; */
multiline_comment|/* Status int must be first member of struct */
DECL|struct|rtas_update_flash_t
r_struct
id|rtas_update_flash_t
(brace
DECL|member|status
r_int
id|status
suffix:semicolon
multiline_comment|/* Flash update status */
DECL|member|flist
r_struct
id|flash_block_list
op_star
id|flist
suffix:semicolon
multiline_comment|/* Local copy of flash block list */
)brace
suffix:semicolon
multiline_comment|/* Status int must be first member of struct */
DECL|struct|rtas_manage_flash_t
r_struct
id|rtas_manage_flash_t
(brace
DECL|member|status
r_int
id|status
suffix:semicolon
multiline_comment|/* Returned status */
DECL|member|op
r_int
r_int
id|op
suffix:semicolon
multiline_comment|/* Reject or commit image */
)brace
suffix:semicolon
multiline_comment|/* Status int must be first member of struct */
DECL|struct|rtas_validate_flash_t
r_struct
id|rtas_validate_flash_t
(brace
DECL|member|status
r_int
id|status
suffix:semicolon
multiline_comment|/* Returned status */
DECL|member|buf
r_char
id|buf
(braket
id|VALIDATE_BUF_SIZE
)braket
suffix:semicolon
multiline_comment|/* Candidate image buffer */
DECL|member|buf_size
r_int
r_int
id|buf_size
suffix:semicolon
multiline_comment|/* Size of image buf */
DECL|member|update_results
r_int
r_int
id|update_results
suffix:semicolon
multiline_comment|/* Update results token */
)brace
suffix:semicolon
r_static
id|DEFINE_SPINLOCK
c_func
(paren
id|flash_file_open_lock
)paren
suffix:semicolon
DECL|variable|firmware_flash_pde
r_static
r_struct
id|proc_dir_entry
op_star
id|firmware_flash_pde
suffix:semicolon
DECL|variable|firmware_update_pde
r_static
r_struct
id|proc_dir_entry
op_star
id|firmware_update_pde
suffix:semicolon
DECL|variable|validate_pde
r_static
r_struct
id|proc_dir_entry
op_star
id|validate_pde
suffix:semicolon
DECL|variable|manage_pde
r_static
r_struct
id|proc_dir_entry
op_star
id|manage_pde
suffix:semicolon
multiline_comment|/* Do simple sanity checks on the flash image. */
DECL|function|flash_list_valid
r_static
r_int
id|flash_list_valid
c_func
(paren
r_struct
id|flash_block_list
op_star
id|flist
)paren
(brace
r_struct
id|flash_block_list
op_star
id|f
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
r_int
id|block_size
comma
id|image_size
suffix:semicolon
multiline_comment|/* Paranoid self test here.  We also collect the image size. */
id|image_size
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|f
op_assign
id|flist
suffix:semicolon
id|f
suffix:semicolon
id|f
op_assign
id|f-&gt;next
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|f-&gt;num_blocks
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|f-&gt;blocks
(braket
id|i
)braket
dot
id|data
op_eq
l_int|NULL
)paren
(brace
r_return
id|FLASH_IMG_NULL_DATA
suffix:semicolon
)brace
id|block_size
op_assign
id|f-&gt;blocks
(braket
id|i
)braket
dot
id|length
suffix:semicolon
r_if
c_cond
(paren
id|block_size
op_le
l_int|0
op_logical_or
id|block_size
OG
id|PAGE_SIZE
)paren
(brace
r_return
id|FLASH_IMG_BAD_LEN
suffix:semicolon
)brace
id|image_size
op_add_assign
id|block_size
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|image_size
OL
(paren
l_int|256
op_lshift
l_int|10
)paren
)paren
(brace
r_if
c_cond
(paren
id|image_size
OL
l_int|2
)paren
r_return
id|FLASH_NO_OP
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;FLASH: flash image with %ld bytes stored for hardware flash on reboot&bslash;n&quot;
comma
id|image_size
)paren
suffix:semicolon
r_return
id|FLASH_IMG_READY
suffix:semicolon
)brace
DECL|function|free_flash_list
r_static
r_void
id|free_flash_list
c_func
(paren
r_struct
id|flash_block_list
op_star
id|f
)paren
(brace
r_struct
id|flash_block_list
op_star
id|next
suffix:semicolon
r_int
id|i
suffix:semicolon
r_while
c_loop
(paren
id|f
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|f-&gt;num_blocks
suffix:semicolon
id|i
op_increment
)paren
id|free_page
c_func
(paren
(paren
r_int
r_int
)paren
(paren
id|f-&gt;blocks
(braket
id|i
)braket
dot
id|data
)paren
)paren
suffix:semicolon
id|next
op_assign
id|f-&gt;next
suffix:semicolon
id|free_page
c_func
(paren
(paren
r_int
r_int
)paren
id|f
)paren
suffix:semicolon
id|f
op_assign
id|next
suffix:semicolon
)brace
)brace
DECL|function|rtas_flash_release
r_static
r_int
id|rtas_flash_release
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
id|file
)paren
(brace
r_struct
id|proc_dir_entry
op_star
id|dp
op_assign
id|PDE
c_func
(paren
id|file-&gt;f_dentry-&gt;d_inode
)paren
suffix:semicolon
r_struct
id|rtas_update_flash_t
op_star
id|uf
suffix:semicolon
id|uf
op_assign
(paren
r_struct
id|rtas_update_flash_t
op_star
)paren
id|dp-&gt;data
suffix:semicolon
r_if
c_cond
(paren
id|uf-&gt;flist
)paren
(brace
multiline_comment|/* File was opened in write mode for a new flash attempt */
multiline_comment|/* Clear saved list */
r_if
c_cond
(paren
id|rtas_firmware_flash_list.next
)paren
(brace
id|free_flash_list
c_func
(paren
id|rtas_firmware_flash_list.next
)paren
suffix:semicolon
id|rtas_firmware_flash_list.next
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|uf-&gt;status
op_ne
id|FLASH_AUTH
)paren
id|uf-&gt;status
op_assign
id|flash_list_valid
c_func
(paren
id|uf-&gt;flist
)paren
suffix:semicolon
r_if
c_cond
(paren
id|uf-&gt;status
op_eq
id|FLASH_IMG_READY
)paren
id|rtas_firmware_flash_list.next
op_assign
id|uf-&gt;flist
suffix:semicolon
r_else
id|free_flash_list
c_func
(paren
id|uf-&gt;flist
)paren
suffix:semicolon
id|uf-&gt;flist
op_assign
l_int|NULL
suffix:semicolon
)brace
id|atomic_dec
c_func
(paren
op_amp
id|dp-&gt;count
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|get_flash_status_msg
r_static
r_void
id|get_flash_status_msg
c_func
(paren
r_int
id|status
comma
r_char
op_star
id|buf
)paren
(brace
r_char
op_star
id|msg
suffix:semicolon
r_switch
c_cond
(paren
id|status
)paren
(brace
r_case
id|FLASH_AUTH
suffix:colon
id|msg
op_assign
l_string|&quot;error: this partition does not have service authority&bslash;n&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FLASH_NO_OP
suffix:colon
id|msg
op_assign
l_string|&quot;info: no firmware image for flash&bslash;n&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FLASH_IMG_SHORT
suffix:colon
id|msg
op_assign
l_string|&quot;error: flash image short&bslash;n&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FLASH_IMG_BAD_LEN
suffix:colon
id|msg
op_assign
l_string|&quot;error: internal error bad length&bslash;n&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FLASH_IMG_NULL_DATA
suffix:colon
id|msg
op_assign
l_string|&quot;error: internal error null data&bslash;n&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FLASH_IMG_READY
suffix:colon
id|msg
op_assign
l_string|&quot;ready: firmware image ready for flash on reboot&bslash;n&quot;
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;error: unexpected status value %d&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|strcpy
c_func
(paren
id|buf
comma
id|msg
)paren
suffix:semicolon
)brace
multiline_comment|/* Reading the proc file will show status (not the firmware contents) */
DECL|function|rtas_flash_read
r_static
id|ssize_t
id|rtas_flash_read
c_func
(paren
r_struct
id|file
op_star
id|file
comma
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
r_struct
id|proc_dir_entry
op_star
id|dp
op_assign
id|PDE
c_func
(paren
id|file-&gt;f_dentry-&gt;d_inode
)paren
suffix:semicolon
r_struct
id|rtas_update_flash_t
op_star
id|uf
suffix:semicolon
r_char
id|msg
(braket
id|RTAS_MSG_MAXLEN
)braket
suffix:semicolon
r_int
id|msglen
suffix:semicolon
id|uf
op_assign
(paren
r_struct
id|rtas_update_flash_t
op_star
)paren
id|dp-&gt;data
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|dp-&gt;name
comma
id|FIRMWARE_FLASH_NAME
)paren
)paren
(brace
id|get_flash_status_msg
c_func
(paren
id|uf-&gt;status
comma
id|msg
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* FIRMWARE_UPDATE_NAME */
id|sprintf
c_func
(paren
id|msg
comma
l_string|&quot;%d&bslash;n&quot;
comma
id|uf-&gt;status
)paren
suffix:semicolon
)brace
id|msglen
op_assign
id|strlen
c_func
(paren
id|msg
)paren
suffix:semicolon
r_if
c_cond
(paren
id|msglen
OG
id|count
)paren
id|msglen
op_assign
id|count
suffix:semicolon
r_if
c_cond
(paren
id|ppos
op_logical_and
op_star
id|ppos
op_ne
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* be cheap */
r_if
c_cond
(paren
op_logical_neg
id|access_ok
c_func
(paren
id|VERIFY_WRITE
comma
id|buf
comma
id|msglen
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|buf
comma
id|msg
comma
id|msglen
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|ppos
)paren
op_star
id|ppos
op_assign
id|msglen
suffix:semicolon
r_return
id|msglen
suffix:semicolon
)brace
multiline_comment|/* We could be much more efficient here.  But to keep this function&n; * simple we allocate a page to the block list no matter how small the&n; * count is.  If the system is low on memory it will be just as well&n; * that we fail....&n; */
DECL|function|rtas_flash_write
r_static
id|ssize_t
id|rtas_flash_write
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
id|buffer
comma
r_int
id|count
comma
id|loff_t
op_star
id|off
)paren
(brace
r_struct
id|proc_dir_entry
op_star
id|dp
op_assign
id|PDE
c_func
(paren
id|file-&gt;f_dentry-&gt;d_inode
)paren
suffix:semicolon
r_struct
id|rtas_update_flash_t
op_star
id|uf
suffix:semicolon
r_char
op_star
id|p
suffix:semicolon
r_int
id|next_free
suffix:semicolon
r_struct
id|flash_block_list
op_star
id|fl
suffix:semicolon
id|uf
op_assign
(paren
r_struct
id|rtas_update_flash_t
op_star
)paren
id|dp-&gt;data
suffix:semicolon
r_if
c_cond
(paren
id|uf-&gt;status
op_eq
id|FLASH_AUTH
op_logical_or
id|count
op_eq
l_int|0
)paren
r_return
id|count
suffix:semicolon
multiline_comment|/* discard data */
multiline_comment|/* In the case that the image is not ready for flashing, the memory&n;&t; * allocated for the block list will be freed upon the release of the &n;&t; * proc file&n;&t; */
r_if
c_cond
(paren
id|uf-&gt;flist
op_eq
l_int|NULL
)paren
(brace
id|uf-&gt;flist
op_assign
(paren
r_struct
id|flash_block_list
op_star
)paren
id|get_zeroed_page
c_func
(paren
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|uf-&gt;flist
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|fl
op_assign
id|uf-&gt;flist
suffix:semicolon
r_while
c_loop
(paren
id|fl-&gt;next
)paren
id|fl
op_assign
id|fl-&gt;next
suffix:semicolon
multiline_comment|/* seek to last block_list for append */
id|next_free
op_assign
id|fl-&gt;num_blocks
suffix:semicolon
r_if
c_cond
(paren
id|next_free
op_eq
id|FLASH_BLOCKS_PER_NODE
)paren
(brace
multiline_comment|/* Need to allocate another block_list */
id|fl-&gt;next
op_assign
(paren
r_struct
id|flash_block_list
op_star
)paren
id|get_zeroed_page
c_func
(paren
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fl-&gt;next
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|fl
op_assign
id|fl-&gt;next
suffix:semicolon
id|next_free
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|count
OG
id|PAGE_SIZE
)paren
id|count
op_assign
id|PAGE_SIZE
suffix:semicolon
id|p
op_assign
(paren
r_char
op_star
)paren
id|get_zeroed_page
c_func
(paren
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|p
comma
id|buffer
comma
id|count
)paren
)paren
(brace
id|free_page
c_func
(paren
(paren
r_int
r_int
)paren
id|p
)paren
suffix:semicolon
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|fl-&gt;blocks
(braket
id|next_free
)braket
dot
id|data
op_assign
id|p
suffix:semicolon
id|fl-&gt;blocks
(braket
id|next_free
)braket
dot
id|length
op_assign
id|count
suffix:semicolon
id|fl-&gt;num_blocks
op_increment
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
DECL|function|rtas_excl_open
r_static
r_int
id|rtas_excl_open
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
id|file
)paren
(brace
r_struct
id|proc_dir_entry
op_star
id|dp
op_assign
id|PDE
c_func
(paren
id|inode
)paren
suffix:semicolon
multiline_comment|/* Enforce exclusive open with use count of PDE */
id|spin_lock
c_func
(paren
op_amp
id|flash_file_open_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|dp-&gt;count
)paren
OG
l_int|1
)paren
(brace
id|spin_unlock
c_func
(paren
op_amp
id|flash_file_open_lock
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|atomic_inc
c_func
(paren
op_amp
id|dp-&gt;count
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|flash_file_open_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|rtas_excl_release
r_static
r_int
id|rtas_excl_release
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
id|file
)paren
(brace
r_struct
id|proc_dir_entry
op_star
id|dp
op_assign
id|PDE
c_func
(paren
id|inode
)paren
suffix:semicolon
id|atomic_dec
c_func
(paren
op_amp
id|dp-&gt;count
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|manage_flash
r_static
r_void
id|manage_flash
c_func
(paren
r_struct
id|rtas_manage_flash_t
op_star
id|args_buf
)paren
(brace
r_int
r_int
id|wait_time
suffix:semicolon
id|s32
id|rc
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
id|rc
op_assign
id|rtas_call
c_func
(paren
id|rtas_token
c_func
(paren
l_string|&quot;ibm,manage-flash-image&quot;
)paren
comma
l_int|1
comma
l_int|1
comma
l_int|NULL
comma
id|args_buf-&gt;op
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_eq
id|RTAS_RC_BUSY
)paren
id|udelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|rtas_is_extended_busy
c_func
(paren
id|rc
)paren
)paren
(brace
id|wait_time
op_assign
id|rtas_extended_busy_delay_time
c_func
(paren
id|rc
)paren
suffix:semicolon
id|udelay
c_func
(paren
id|wait_time
op_star
l_int|1000
)paren
suffix:semicolon
)brace
r_else
r_break
suffix:semicolon
)brace
id|args_buf-&gt;status
op_assign
id|rc
suffix:semicolon
)brace
DECL|function|manage_flash_read
r_static
id|ssize_t
id|manage_flash_read
c_func
(paren
r_struct
id|file
op_star
id|file
comma
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
r_struct
id|proc_dir_entry
op_star
id|dp
op_assign
id|PDE
c_func
(paren
id|file-&gt;f_dentry-&gt;d_inode
)paren
suffix:semicolon
r_struct
id|rtas_manage_flash_t
op_star
id|args_buf
suffix:semicolon
r_char
id|msg
(braket
id|RTAS_MSG_MAXLEN
)braket
suffix:semicolon
r_int
id|msglen
suffix:semicolon
id|args_buf
op_assign
(paren
r_struct
id|rtas_manage_flash_t
op_star
)paren
id|dp-&gt;data
suffix:semicolon
r_if
c_cond
(paren
id|args_buf
op_eq
l_int|NULL
)paren
r_return
l_int|0
suffix:semicolon
id|msglen
op_assign
id|sprintf
c_func
(paren
id|msg
comma
l_string|&quot;%d&bslash;n&quot;
comma
id|args_buf-&gt;status
)paren
suffix:semicolon
r_if
c_cond
(paren
id|msglen
OG
id|count
)paren
id|msglen
op_assign
id|count
suffix:semicolon
r_if
c_cond
(paren
id|ppos
op_logical_and
op_star
id|ppos
op_ne
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* be cheap */
r_if
c_cond
(paren
op_logical_neg
id|access_ok
c_func
(paren
id|VERIFY_WRITE
comma
id|buf
comma
id|msglen
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|buf
comma
id|msg
comma
id|msglen
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|ppos
)paren
op_star
id|ppos
op_assign
id|msglen
suffix:semicolon
r_return
id|msglen
suffix:semicolon
)brace
DECL|function|manage_flash_write
r_static
id|ssize_t
id|manage_flash_write
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
id|off
)paren
(brace
r_struct
id|proc_dir_entry
op_star
id|dp
op_assign
id|PDE
c_func
(paren
id|file-&gt;f_dentry-&gt;d_inode
)paren
suffix:semicolon
r_struct
id|rtas_manage_flash_t
op_star
id|args_buf
suffix:semicolon
r_const
r_char
id|reject_str
(braket
)braket
op_assign
l_string|&quot;0&quot;
suffix:semicolon
r_const
r_char
id|commit_str
(braket
)braket
op_assign
l_string|&quot;1&quot;
suffix:semicolon
r_char
id|stkbuf
(braket
l_int|10
)braket
suffix:semicolon
r_int
id|op
suffix:semicolon
id|args_buf
op_assign
(paren
r_struct
id|rtas_manage_flash_t
op_star
)paren
id|dp-&gt;data
suffix:semicolon
r_if
c_cond
(paren
(paren
id|args_buf-&gt;status
op_eq
id|MANAGE_AUTH
)paren
op_logical_or
(paren
id|count
op_eq
l_int|0
)paren
)paren
r_return
id|count
suffix:semicolon
id|op
op_assign
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|buf
)paren
(brace
r_if
c_cond
(paren
id|count
OG
l_int|9
)paren
id|count
op_assign
l_int|9
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
(paren
id|stkbuf
comma
id|buf
comma
id|count
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|stkbuf
comma
id|reject_str
comma
id|strlen
c_func
(paren
id|reject_str
)paren
)paren
op_eq
l_int|0
)paren
id|op
op_assign
id|RTAS_REJECT_TMP_IMG
suffix:semicolon
r_else
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|stkbuf
comma
id|commit_str
comma
id|strlen
c_func
(paren
id|commit_str
)paren
)paren
op_eq
l_int|0
)paren
id|op
op_assign
id|RTAS_COMMIT_TMP_IMG
suffix:semicolon
)brace
r_if
c_cond
(paren
id|op
op_eq
op_minus
l_int|1
)paren
multiline_comment|/* buf is empty, or contains invalid string */
r_return
op_minus
id|EINVAL
suffix:semicolon
id|args_buf-&gt;op
op_assign
id|op
suffix:semicolon
id|manage_flash
c_func
(paren
id|args_buf
)paren
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
DECL|function|validate_flash
r_static
r_void
id|validate_flash
c_func
(paren
r_struct
id|rtas_validate_flash_t
op_star
id|args_buf
)paren
(brace
r_int
id|token
op_assign
id|rtas_token
c_func
(paren
l_string|&quot;ibm,validate-flash-image&quot;
)paren
suffix:semicolon
r_int
r_int
id|wait_time
suffix:semicolon
r_int
id|update_results
suffix:semicolon
id|s32
id|rc
suffix:semicolon
id|rc
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|rtas_data_buf_lock
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|rtas_data_buf
comma
id|args_buf-&gt;buf
comma
id|VALIDATE_BUF_SIZE
)paren
suffix:semicolon
id|rc
op_assign
id|rtas_call
c_func
(paren
id|token
comma
l_int|2
comma
l_int|2
comma
op_amp
id|update_results
comma
(paren
id|u32
)paren
id|__pa
c_func
(paren
id|rtas_data_buf
)paren
comma
id|args_buf-&gt;buf_size
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|args_buf-&gt;buf
comma
id|rtas_data_buf
comma
id|VALIDATE_BUF_SIZE
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|rtas_data_buf_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_eq
id|RTAS_RC_BUSY
)paren
id|udelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|rtas_is_extended_busy
c_func
(paren
id|rc
)paren
)paren
(brace
id|wait_time
op_assign
id|rtas_extended_busy_delay_time
c_func
(paren
id|rc
)paren
suffix:semicolon
id|udelay
c_func
(paren
id|wait_time
op_star
l_int|1000
)paren
suffix:semicolon
)brace
r_else
r_break
suffix:semicolon
)brace
id|args_buf-&gt;status
op_assign
id|rc
suffix:semicolon
id|args_buf-&gt;update_results
op_assign
id|update_results
suffix:semicolon
)brace
DECL|function|get_validate_flash_msg
r_static
r_int
id|get_validate_flash_msg
c_func
(paren
r_struct
id|rtas_validate_flash_t
op_star
id|args_buf
comma
r_char
op_star
id|msg
)paren
(brace
r_int
id|n
suffix:semicolon
r_if
c_cond
(paren
id|args_buf-&gt;status
op_ge
id|VALIDATE_TMP_UPDATE
)paren
(brace
id|n
op_assign
id|sprintf
c_func
(paren
id|msg
comma
l_string|&quot;%d&bslash;n&quot;
comma
id|args_buf-&gt;update_results
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|args_buf-&gt;update_results
op_ge
id|VALIDATE_CUR_UNKNOWN
)paren
op_logical_or
(paren
id|args_buf-&gt;update_results
op_eq
id|VALIDATE_TMP_UPDATE
)paren
)paren
id|n
op_add_assign
id|sprintf
c_func
(paren
id|msg
op_plus
id|n
comma
l_string|&quot;%s&bslash;n&quot;
comma
id|args_buf-&gt;buf
)paren
suffix:semicolon
)brace
r_else
(brace
id|n
op_assign
id|sprintf
c_func
(paren
id|msg
comma
l_string|&quot;%d&bslash;n&quot;
comma
id|args_buf-&gt;status
)paren
suffix:semicolon
)brace
r_return
id|n
suffix:semicolon
)brace
DECL|function|validate_flash_read
r_static
id|ssize_t
id|validate_flash_read
c_func
(paren
r_struct
id|file
op_star
id|file
comma
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
r_struct
id|proc_dir_entry
op_star
id|dp
op_assign
id|PDE
c_func
(paren
id|file-&gt;f_dentry-&gt;d_inode
)paren
suffix:semicolon
r_struct
id|rtas_validate_flash_t
op_star
id|args_buf
suffix:semicolon
r_char
id|msg
(braket
id|RTAS_MSG_MAXLEN
)braket
suffix:semicolon
r_int
id|msglen
suffix:semicolon
id|args_buf
op_assign
(paren
r_struct
id|rtas_validate_flash_t
op_star
)paren
id|dp-&gt;data
suffix:semicolon
r_if
c_cond
(paren
id|ppos
op_logical_and
op_star
id|ppos
op_ne
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* be cheap */
id|msglen
op_assign
id|get_validate_flash_msg
c_func
(paren
id|args_buf
comma
id|msg
)paren
suffix:semicolon
r_if
c_cond
(paren
id|msglen
OG
id|count
)paren
id|msglen
op_assign
id|count
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|access_ok
c_func
(paren
id|VERIFY_WRITE
comma
id|buf
comma
id|msglen
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|buf
comma
id|msg
comma
id|msglen
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|ppos
)paren
op_star
id|ppos
op_assign
id|msglen
suffix:semicolon
r_return
id|msglen
suffix:semicolon
)brace
DECL|function|validate_flash_write
r_static
id|ssize_t
id|validate_flash_write
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
id|off
)paren
(brace
r_struct
id|proc_dir_entry
op_star
id|dp
op_assign
id|PDE
c_func
(paren
id|file-&gt;f_dentry-&gt;d_inode
)paren
suffix:semicolon
r_struct
id|rtas_validate_flash_t
op_star
id|args_buf
suffix:semicolon
r_int
id|rc
suffix:semicolon
id|args_buf
op_assign
(paren
r_struct
id|rtas_validate_flash_t
op_star
)paren
id|dp-&gt;data
suffix:semicolon
r_if
c_cond
(paren
id|dp-&gt;data
op_eq
l_int|NULL
)paren
(brace
id|dp-&gt;data
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|rtas_validate_flash_t
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dp-&gt;data
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
multiline_comment|/* We are only interested in the first 4K of the&n;&t; * candidate image */
r_if
c_cond
(paren
(paren
op_star
id|off
op_ge
id|VALIDATE_BUF_SIZE
)paren
op_logical_or
(paren
id|args_buf-&gt;status
op_eq
id|VALIDATE_AUTH
)paren
)paren
(brace
op_star
id|off
op_add_assign
id|count
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
r_if
c_cond
(paren
op_star
id|off
op_plus
id|count
op_ge
id|VALIDATE_BUF_SIZE
)paren
(brace
id|count
op_assign
id|VALIDATE_BUF_SIZE
op_minus
op_star
id|off
suffix:semicolon
id|args_buf-&gt;status
op_assign
id|VALIDATE_READY
suffix:semicolon
)brace
r_else
(brace
id|args_buf-&gt;status
op_assign
id|VALIDATE_INCOMPLETE
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|access_ok
c_func
(paren
id|VERIFY_READ
comma
id|buf
comma
id|count
)paren
)paren
(brace
id|rc
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|args_buf-&gt;buf
op_plus
op_star
id|off
comma
id|buf
comma
id|count
)paren
)paren
(brace
id|rc
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
op_star
id|off
op_add_assign
id|count
suffix:semicolon
id|rc
op_assign
id|count
suffix:semicolon
id|done
suffix:colon
r_if
c_cond
(paren
id|rc
OL
l_int|0
)paren
(brace
id|kfree
c_func
(paren
id|dp-&gt;data
)paren
suffix:semicolon
id|dp-&gt;data
op_assign
l_int|NULL
suffix:semicolon
)brace
r_return
id|rc
suffix:semicolon
)brace
DECL|function|validate_flash_release
r_static
r_int
id|validate_flash_release
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
id|file
)paren
(brace
r_struct
id|proc_dir_entry
op_star
id|dp
op_assign
id|PDE
c_func
(paren
id|file-&gt;f_dentry-&gt;d_inode
)paren
suffix:semicolon
r_struct
id|rtas_validate_flash_t
op_star
id|args_buf
suffix:semicolon
id|args_buf
op_assign
(paren
r_struct
id|rtas_validate_flash_t
op_star
)paren
id|dp-&gt;data
suffix:semicolon
r_if
c_cond
(paren
id|args_buf-&gt;status
op_eq
id|VALIDATE_READY
)paren
(brace
id|args_buf-&gt;buf_size
op_assign
id|VALIDATE_BUF_SIZE
suffix:semicolon
id|validate_flash
c_func
(paren
id|args_buf
)paren
suffix:semicolon
)brace
multiline_comment|/* The matching atomic_inc was in rtas_excl_open() */
id|atomic_dec
c_func
(paren
op_amp
id|dp-&gt;count
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|remove_flash_pde
r_static
r_void
id|remove_flash_pde
c_func
(paren
r_struct
id|proc_dir_entry
op_star
id|dp
)paren
(brace
r_if
c_cond
(paren
id|dp
)paren
(brace
r_if
c_cond
(paren
id|dp-&gt;data
op_ne
l_int|NULL
)paren
id|kfree
c_func
(paren
id|dp-&gt;data
)paren
suffix:semicolon
id|dp-&gt;owner
op_assign
l_int|NULL
suffix:semicolon
id|remove_proc_entry
c_func
(paren
id|dp-&gt;name
comma
id|dp-&gt;parent
)paren
suffix:semicolon
)brace
)brace
DECL|function|initialize_flash_pde_data
r_static
r_int
id|initialize_flash_pde_data
c_func
(paren
r_const
r_char
op_star
id|rtas_call_name
comma
r_int
id|buf_size
comma
r_struct
id|proc_dir_entry
op_star
id|dp
)paren
(brace
r_int
op_star
id|status
suffix:semicolon
r_int
id|token
suffix:semicolon
id|dp-&gt;data
op_assign
id|kmalloc
c_func
(paren
id|buf_size
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dp-&gt;data
op_eq
l_int|NULL
)paren
(brace
id|remove_flash_pde
c_func
(paren
id|dp
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|memset
c_func
(paren
id|dp-&gt;data
comma
l_int|0
comma
id|buf_size
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * This code assumes that the status int is the first member of the&n;&t; * struct &n;&t; */
id|status
op_assign
(paren
r_int
op_star
)paren
id|dp-&gt;data
suffix:semicolon
id|token
op_assign
id|rtas_token
c_func
(paren
id|rtas_call_name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|token
op_eq
id|RTAS_UNKNOWN_SERVICE
)paren
op_star
id|status
op_assign
id|FLASH_AUTH
suffix:semicolon
r_else
op_star
id|status
op_assign
id|FLASH_NO_OP
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|create_flash_pde
r_static
r_struct
id|proc_dir_entry
op_star
id|create_flash_pde
c_func
(paren
r_const
r_char
op_star
id|filename
comma
r_struct
id|file_operations
op_star
id|fops
)paren
(brace
r_struct
id|proc_dir_entry
op_star
id|ent
op_assign
l_int|NULL
suffix:semicolon
id|ent
op_assign
id|create_proc_entry
c_func
(paren
id|filename
comma
id|S_IRUSR
op_or
id|S_IWUSR
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ent
op_ne
l_int|NULL
)paren
(brace
id|ent-&gt;nlink
op_assign
l_int|1
suffix:semicolon
id|ent-&gt;proc_fops
op_assign
id|fops
suffix:semicolon
id|ent-&gt;owner
op_assign
id|THIS_MODULE
suffix:semicolon
)brace
r_return
id|ent
suffix:semicolon
)brace
DECL|variable|rtas_flash_operations
r_static
r_struct
id|file_operations
id|rtas_flash_operations
op_assign
(brace
dot
id|read
op_assign
id|rtas_flash_read
comma
dot
id|write
op_assign
id|rtas_flash_write
comma
dot
id|open
op_assign
id|rtas_excl_open
comma
dot
id|release
op_assign
id|rtas_flash_release
comma
)brace
suffix:semicolon
DECL|variable|manage_flash_operations
r_static
r_struct
id|file_operations
id|manage_flash_operations
op_assign
(brace
dot
id|read
op_assign
id|manage_flash_read
comma
dot
id|write
op_assign
id|manage_flash_write
comma
dot
id|open
op_assign
id|rtas_excl_open
comma
dot
id|release
op_assign
id|rtas_excl_release
comma
)brace
suffix:semicolon
DECL|variable|validate_flash_operations
r_static
r_struct
id|file_operations
id|validate_flash_operations
op_assign
(brace
dot
id|read
op_assign
id|validate_flash_read
comma
dot
id|write
op_assign
id|validate_flash_write
comma
dot
id|open
op_assign
id|rtas_excl_open
comma
dot
id|release
op_assign
id|validate_flash_release
comma
)brace
suffix:semicolon
DECL|function|rtas_flash_init
r_int
id|__init
id|rtas_flash_init
c_func
(paren
r_void
)paren
(brace
r_int
id|rc
suffix:semicolon
r_if
c_cond
(paren
id|rtas_token
c_func
(paren
l_string|&quot;ibm,update-flash-64-and-reboot&quot;
)paren
op_eq
id|RTAS_UNKNOWN_SERVICE
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;rtas_flash: no firmware flash support&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|firmware_flash_pde
op_assign
id|create_flash_pde
c_func
(paren
l_string|&quot;ppc64/rtas/&quot;
id|FIRMWARE_FLASH_NAME
comma
op_amp
id|rtas_flash_operations
)paren
suffix:semicolon
r_if
c_cond
(paren
id|firmware_flash_pde
op_eq
l_int|NULL
)paren
(brace
id|rc
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|cleanup
suffix:semicolon
)brace
id|rc
op_assign
id|initialize_flash_pde_data
c_func
(paren
l_string|&quot;ibm,update-flash-64-and-reboot&quot;
comma
r_sizeof
(paren
r_struct
id|rtas_update_flash_t
)paren
comma
id|firmware_flash_pde
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_ne
l_int|0
)paren
r_goto
id|cleanup
suffix:semicolon
id|firmware_update_pde
op_assign
id|create_flash_pde
c_func
(paren
l_string|&quot;ppc64/rtas/&quot;
id|FIRMWARE_UPDATE_NAME
comma
op_amp
id|rtas_flash_operations
)paren
suffix:semicolon
r_if
c_cond
(paren
id|firmware_update_pde
op_eq
l_int|NULL
)paren
(brace
id|rc
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|cleanup
suffix:semicolon
)brace
id|rc
op_assign
id|initialize_flash_pde_data
c_func
(paren
l_string|&quot;ibm,update-flash-64-and-reboot&quot;
comma
r_sizeof
(paren
r_struct
id|rtas_update_flash_t
)paren
comma
id|firmware_update_pde
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_ne
l_int|0
)paren
r_goto
id|cleanup
suffix:semicolon
id|validate_pde
op_assign
id|create_flash_pde
c_func
(paren
l_string|&quot;ppc64/rtas/&quot;
id|VALIDATE_FLASH_NAME
comma
op_amp
id|validate_flash_operations
)paren
suffix:semicolon
r_if
c_cond
(paren
id|validate_pde
op_eq
l_int|NULL
)paren
(brace
id|rc
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|cleanup
suffix:semicolon
)brace
id|rc
op_assign
id|initialize_flash_pde_data
c_func
(paren
l_string|&quot;ibm,validate-flash-image&quot;
comma
r_sizeof
(paren
r_struct
id|rtas_validate_flash_t
)paren
comma
id|validate_pde
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_ne
l_int|0
)paren
r_goto
id|cleanup
suffix:semicolon
id|manage_pde
op_assign
id|create_flash_pde
c_func
(paren
l_string|&quot;ppc64/rtas/&quot;
id|MANAGE_FLASH_NAME
comma
op_amp
id|manage_flash_operations
)paren
suffix:semicolon
r_if
c_cond
(paren
id|manage_pde
op_eq
l_int|NULL
)paren
(brace
id|rc
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|cleanup
suffix:semicolon
)brace
id|rc
op_assign
id|initialize_flash_pde_data
c_func
(paren
l_string|&quot;ibm,manage-flash-image&quot;
comma
r_sizeof
(paren
r_struct
id|rtas_manage_flash_t
)paren
comma
id|manage_pde
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_ne
l_int|0
)paren
r_goto
id|cleanup
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|cleanup
suffix:colon
id|remove_flash_pde
c_func
(paren
id|firmware_flash_pde
)paren
suffix:semicolon
id|remove_flash_pde
c_func
(paren
id|firmware_update_pde
)paren
suffix:semicolon
id|remove_flash_pde
c_func
(paren
id|validate_pde
)paren
suffix:semicolon
id|remove_flash_pde
c_func
(paren
id|manage_pde
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
DECL|function|rtas_flash_cleanup
r_void
id|__exit
id|rtas_flash_cleanup
c_func
(paren
r_void
)paren
(brace
id|remove_flash_pde
c_func
(paren
id|firmware_flash_pde
)paren
suffix:semicolon
id|remove_flash_pde
c_func
(paren
id|firmware_update_pde
)paren
suffix:semicolon
id|remove_flash_pde
c_func
(paren
id|validate_pde
)paren
suffix:semicolon
id|remove_flash_pde
c_func
(paren
id|manage_pde
)paren
suffix:semicolon
)brace
DECL|variable|rtas_flash_init
id|module_init
c_func
(paren
id|rtas_flash_init
)paren
suffix:semicolon
DECL|variable|rtas_flash_cleanup
id|module_exit
c_func
(paren
id|rtas_flash_cleanup
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
