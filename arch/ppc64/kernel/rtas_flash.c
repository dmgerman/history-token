multiline_comment|/*&n; *  c 2001 PPC 64 Team, IBM Corp&n; *&n; *      This program is free software; you can redistribute it and/or&n; *      modify it under the terms of the GNU General Public License&n; *      as published by the Free Software Foundation; either version&n; *      2 of the License, or (at your option) any later version.&n; *&n; * /proc/ppc64/rtas/firmware_flash interface&n; *&n; * This file implements a firmware_flash interface to pump a firmware&n; * image into the kernel.  At reboot time rtas_restart() will see the&n; * firmware image and flash it as it reboots (see rtas.c).&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/rtas.h&gt;
DECL|macro|MODULE_VERSION
mdefine_line|#define MODULE_VERSION &quot;1.0&quot;
DECL|macro|MODULE_NAME
mdefine_line|#define MODULE_NAME &quot;rtas_flash&quot;
DECL|macro|FIRMWARE_FLASH_NAME
mdefine_line|#define FIRMWARE_FLASH_NAME &quot;firmware_flash&quot;
multiline_comment|/* Local copy of the flash block list.&n; * We only allow one open of the flash proc file and create this&n; * list as we go.  This list will be put in the kernel&squot;s&n; * rtas_firmware_flash_list global var once it is fully read.&n; *&n; * For convenience as we build the list we use virtual addrs,&n; * we do not fill in the version number, and the length field&n; * is treated as the number of entries currently in the block&n; * (i.e. not a byte count).  This is all fixed on release.&n; */
DECL|variable|flist
r_static
r_struct
id|flash_block_list
op_star
id|flist
suffix:semicolon
DECL|variable|flash_msg
r_static
r_char
op_star
id|flash_msg
suffix:semicolon
DECL|variable|flash_possible
r_static
r_int
id|flash_possible
suffix:semicolon
DECL|function|rtas_flash_open
r_static
r_int
id|rtas_flash_open
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
r_if
c_cond
(paren
(paren
id|file-&gt;f_mode
op_amp
id|FMODE_WRITE
)paren
op_logical_and
id|flash_possible
)paren
(brace
r_if
c_cond
(paren
id|flist
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|flist
op_assign
(paren
r_struct
id|flash_block_list
op_star
)paren
id|get_free_page
c_func
(paren
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|flist
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
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
id|flash_msg
op_assign
l_int|NULL
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
id|flash_msg
op_assign
l_string|&quot;error: internal error null data&bslash;n&quot;
suffix:semicolon
r_return
l_int|0
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
id|flash_msg
op_assign
l_string|&quot;error: internal error bad length&bslash;n&quot;
suffix:semicolon
r_return
l_int|0
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
id|flash_msg
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* allow &quot;clear&quot; of image */
r_else
id|flash_msg
op_assign
l_string|&quot;error: flash image short&bslash;n&quot;
suffix:semicolon
r_return
l_int|0
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
l_int|1
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
r_if
c_cond
(paren
id|flist
)paren
(brace
multiline_comment|/* Always clear saved list on a new attempt. */
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
id|flash_list_valid
c_func
(paren
id|flist
)paren
)paren
id|rtas_firmware_flash_list.next
op_assign
id|flist
suffix:semicolon
r_else
id|free_flash_list
c_func
(paren
id|flist
)paren
suffix:semicolon
id|flist
op_assign
l_int|NULL
suffix:semicolon
)brace
r_return
l_int|0
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
r_int
id|error
suffix:semicolon
r_char
op_star
id|msg
suffix:semicolon
r_int
id|msglen
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|flash_possible
)paren
(brace
id|msg
op_assign
l_string|&quot;error: this partition does not have service authority&bslash;n&quot;
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|flist
)paren
(brace
id|msg
op_assign
l_string|&quot;info: this file is busy for write by some process&bslash;n&quot;
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|flash_msg
)paren
(brace
id|msg
op_assign
id|flash_msg
suffix:semicolon
multiline_comment|/* message from last flash attempt */
)brace
r_else
r_if
c_cond
(paren
id|rtas_firmware_flash_list.next
)paren
(brace
id|msg
op_assign
l_string|&quot;ready: firmware image ready for flash on reboot&bslash;n&quot;
suffix:semicolon
)brace
r_else
(brace
id|msg
op_assign
l_string|&quot;info: no firmware image for flash&bslash;n&quot;
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
id|error
op_assign
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
id|buf
comma
id|msglen
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|copy_to_user
c_func
(paren
id|buf
comma
id|msg
comma
id|msglen
)paren
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
r_int
id|len
op_assign
id|count
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
op_assign
id|flist
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|flash_possible
op_logical_or
id|len
op_eq
l_int|0
)paren
r_return
id|len
suffix:semicolon
multiline_comment|/* discard data */
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
id|get_free_page
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
id|len
OG
id|PAGE_SIZE
)paren
id|len
op_assign
id|PAGE_SIZE
suffix:semicolon
id|p
op_assign
(paren
r_char
op_star
)paren
id|get_free_page
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
id|len
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
id|len
suffix:semicolon
id|fl-&gt;num_blocks
op_increment
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
DECL|variable|rtas_flash_operations
r_static
r_struct
id|file_operations
id|rtas_flash_operations
op_assign
(brace
id|read
suffix:colon
id|rtas_flash_read
comma
id|write
suffix:colon
id|rtas_flash_write
comma
id|open
suffix:colon
id|rtas_flash_open
comma
id|release
suffix:colon
id|rtas_flash_release
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
r_struct
id|proc_dir_entry
op_star
id|ent
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rtas_proc_dir
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;rtas proc dir does not already exist&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOENT
suffix:semicolon
)brace
r_if
c_cond
(paren
id|rtas_token
c_func
(paren
l_string|&quot;ibm,update-flash-64-and-reboot&quot;
)paren
op_ne
id|RTAS_UNKNOWN_SERVICE
)paren
id|flash_possible
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ent
op_assign
id|create_proc_entry
c_func
(paren
id|FIRMWARE_FLASH_NAME
comma
id|S_IRUSR
op_or
id|S_IWUSR
comma
id|rtas_proc_dir
)paren
)paren
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
op_amp
id|rtas_flash_operations
suffix:semicolon
id|ent-&gt;owner
op_assign
id|THIS_MODULE
suffix:semicolon
)brace
r_return
l_int|0
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
r_if
c_cond
(paren
op_logical_neg
id|rtas_proc_dir
)paren
r_return
suffix:semicolon
id|remove_proc_entry
c_func
(paren
id|FIRMWARE_FLASH_NAME
comma
id|rtas_proc_dir
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
