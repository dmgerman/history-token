multiline_comment|/*&n; *  drivers/s390/char/tape_char.c&n; *    character device frontend for tape device driver&n; *&n; *  S390 and zSeries version&n; *    Copyright (C) 2001,2002 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Carsten Otte &lt;cotte@de.ibm.com&gt;&n; *&t;&t; Michael Holzheu &lt;holzheu@de.ibm.com&gt;&n; *&t;&t; Tuan Ngo-Anh &lt;ngoanh@de.ibm.com&gt;&n; *&t;&t; Martin Schwidefsky &lt;schwidefsky@de.ibm.com&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/mtio.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &quot;tape.h&quot;
macro_line|#include &quot;tape_std.h&quot;
macro_line|#include &quot;tape_class.h&quot;
DECL|macro|PRINTK_HEADER
mdefine_line|#define PRINTK_HEADER &quot;TAPE_CHAR: &quot;
DECL|macro|TAPECHAR_MAJOR
mdefine_line|#define TAPECHAR_MAJOR&t;&t;0&t;/* get dynamic major */
multiline_comment|/*&n; * file operation structure for tape character frontend&n; */
r_static
id|ssize_t
id|tapechar_read
c_func
(paren
r_struct
id|file
op_star
comma
r_char
id|__user
op_star
comma
r_int
comma
id|loff_t
op_star
)paren
suffix:semicolon
r_static
id|ssize_t
id|tapechar_write
c_func
(paren
r_struct
id|file
op_star
comma
r_const
r_char
id|__user
op_star
comma
r_int
comma
id|loff_t
op_star
)paren
suffix:semicolon
r_static
r_int
id|tapechar_open
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
)paren
suffix:semicolon
r_static
r_int
id|tapechar_release
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
)paren
suffix:semicolon
r_static
r_int
id|tapechar_ioctl
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
DECL|variable|tape_fops
r_static
r_struct
id|file_operations
id|tape_fops
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|read
op_assign
id|tapechar_read
comma
dot
id|write
op_assign
id|tapechar_write
comma
dot
id|ioctl
op_assign
id|tapechar_ioctl
comma
dot
id|open
op_assign
id|tapechar_open
comma
dot
id|release
op_assign
id|tapechar_release
comma
)brace
suffix:semicolon
DECL|variable|tapechar_major
r_static
r_int
id|tapechar_major
op_assign
id|TAPECHAR_MAJOR
suffix:semicolon
multiline_comment|/*&n; * This function is called for every new tapedevice&n; */
r_int
DECL|function|tapechar_setup_device
id|tapechar_setup_device
c_func
(paren
r_struct
id|tape_device
op_star
id|device
)paren
(brace
r_char
id|device_name
(braket
l_int|20
)braket
suffix:semicolon
id|sprintf
c_func
(paren
id|device_name
comma
l_string|&quot;ntibm%i&quot;
comma
id|device-&gt;first_minor
op_div
l_int|2
)paren
suffix:semicolon
id|device-&gt;nt
op_assign
id|register_tape_dev
c_func
(paren
op_amp
id|device-&gt;cdev-&gt;dev
comma
id|MKDEV
c_func
(paren
id|tapechar_major
comma
id|device-&gt;first_minor
)paren
comma
op_amp
id|tape_fops
comma
id|device_name
comma
l_string|&quot;non-rewinding&quot;
)paren
suffix:semicolon
id|device_name
(braket
l_int|0
)braket
op_assign
l_char|&squot;r&squot;
suffix:semicolon
id|device-&gt;rt
op_assign
id|register_tape_dev
c_func
(paren
op_amp
id|device-&gt;cdev-&gt;dev
comma
id|MKDEV
c_func
(paren
id|tapechar_major
comma
id|device-&gt;first_minor
op_plus
l_int|1
)paren
comma
op_amp
id|tape_fops
comma
id|device_name
comma
l_string|&quot;rewinding&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_void
DECL|function|tapechar_cleanup_device
id|tapechar_cleanup_device
c_func
(paren
r_struct
id|tape_device
op_star
id|device
)paren
(brace
id|unregister_tape_dev
c_func
(paren
id|device-&gt;rt
)paren
suffix:semicolon
id|device-&gt;rt
op_assign
l_int|NULL
suffix:semicolon
id|unregister_tape_dev
c_func
(paren
id|device-&gt;nt
)paren
suffix:semicolon
id|device-&gt;nt
op_assign
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; * Terminate write command (we write two TMs and skip backward over last)&n; * This ensures that the tape is always correctly terminated.&n; * When the user writes afterwards a new file, he will overwrite the&n; * second TM and therefore one TM will remain to separate the&n; * two files on the tape...&n; */
r_static
r_inline
r_void
DECL|function|tapechar_terminate_write
id|tapechar_terminate_write
c_func
(paren
r_struct
id|tape_device
op_star
id|device
)paren
(brace
r_if
c_cond
(paren
id|tape_mtop
c_func
(paren
id|device
comma
id|MTWEOF
comma
l_int|1
)paren
op_eq
l_int|0
op_logical_and
id|tape_mtop
c_func
(paren
id|device
comma
id|MTWEOF
comma
l_int|1
)paren
op_eq
l_int|0
)paren
id|tape_mtop
c_func
(paren
id|device
comma
id|MTBSR
comma
l_int|1
)paren
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|tapechar_check_idalbuffer
id|tapechar_check_idalbuffer
c_func
(paren
r_struct
id|tape_device
op_star
id|device
comma
r_int
id|block_size
)paren
(brace
r_struct
id|idal_buffer
op_star
r_new
suffix:semicolon
r_if
c_cond
(paren
id|device-&gt;char_data.idal_buf
op_ne
l_int|NULL
op_logical_and
id|device-&gt;char_data.idal_buf-&gt;size
op_eq
id|block_size
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|block_size
OG
id|MAX_BLOCKSIZE
)paren
(brace
id|DBF_EVENT
c_func
(paren
l_int|3
comma
l_string|&quot;Invalid blocksize (%zd &gt; %d)&bslash;n&quot;
comma
id|block_size
comma
id|MAX_BLOCKSIZE
)paren
suffix:semicolon
id|PRINT_ERR
c_func
(paren
l_string|&quot;Invalid blocksize (%zd&gt; %d)&bslash;n&quot;
comma
id|block_size
comma
id|MAX_BLOCKSIZE
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/* The current idal buffer is not correct. Allocate a new one. */
r_new
op_assign
id|idal_buffer_alloc
c_func
(paren
id|block_size
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
r_new
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
id|device-&gt;char_data.idal_buf
op_ne
l_int|NULL
)paren
id|idal_buffer_free
c_func
(paren
id|device-&gt;char_data.idal_buf
)paren
suffix:semicolon
id|device-&gt;char_data.idal_buf
op_assign
r_new
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Tape device read function&n; */
id|ssize_t
DECL|function|tapechar_read
id|tapechar_read
c_func
(paren
r_struct
id|file
op_star
id|filp
comma
r_char
id|__user
op_star
id|data
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
id|tape_device
op_star
id|device
suffix:semicolon
r_struct
id|tape_request
op_star
id|request
suffix:semicolon
r_int
id|block_size
suffix:semicolon
r_int
id|rc
suffix:semicolon
id|DBF_EVENT
c_func
(paren
l_int|6
comma
l_string|&quot;TCHAR:read&bslash;n&quot;
)paren
suffix:semicolon
id|device
op_assign
(paren
r_struct
id|tape_device
op_star
)paren
id|filp-&gt;private_data
suffix:semicolon
multiline_comment|/* Check position. */
r_if
c_cond
(paren
id|ppos
op_ne
op_amp
id|filp-&gt;f_pos
)paren
(brace
multiline_comment|/*&n;&t;&t; * &quot;A request was outside the capabilities of the device.&quot;&n;&t;&t; * This check uses internal knowledge about how pread and&n;&t;&t; * read work...&n;&t;&t; */
id|DBF_EVENT
c_func
(paren
l_int|6
comma
l_string|&quot;TCHAR:ppos wrong&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EOVERFLOW
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * If the tape isn&squot;t terminated yet, do it now. And since we then&n;&t; * are at the end of the tape there wouldn&squot;t be anything to read&n;&t; * anyways. So we return immediatly.&n;&t; */
r_if
c_cond
(paren
id|device-&gt;required_tapemarks
)paren
(brace
r_return
id|tape_std_terminate_write
c_func
(paren
id|device
)paren
suffix:semicolon
)brace
multiline_comment|/* Find out block size to use */
r_if
c_cond
(paren
id|device-&gt;char_data.block_size
op_ne
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|count
OL
id|device-&gt;char_data.block_size
)paren
(brace
id|DBF_EVENT
c_func
(paren
l_int|3
comma
l_string|&quot;TCHAR:read smaller than block &quot;
l_string|&quot;size was requested&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|block_size
op_assign
id|device-&gt;char_data.block_size
suffix:semicolon
)brace
r_else
(brace
id|block_size
op_assign
id|count
suffix:semicolon
)brace
id|rc
op_assign
id|tapechar_check_idalbuffer
c_func
(paren
id|device
comma
id|block_size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
r_return
id|rc
suffix:semicolon
macro_line|#ifdef CONFIG_S390_TAPE_BLOCK
multiline_comment|/* Changes position. */
id|device-&gt;blk_data.medium_changed
op_assign
l_int|1
suffix:semicolon
macro_line|#endif
id|DBF_EVENT
c_func
(paren
l_int|6
comma
l_string|&quot;TCHAR:nbytes: %lx&bslash;n&quot;
comma
id|block_size
)paren
suffix:semicolon
multiline_comment|/* Let the discipline build the ccw chain. */
id|request
op_assign
id|device-&gt;discipline
op_member_access_from_pointer
id|read_block
c_func
(paren
id|device
comma
id|block_size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|request
)paren
)paren
r_return
id|PTR_ERR
c_func
(paren
id|request
)paren
suffix:semicolon
multiline_comment|/* Execute it. */
id|rc
op_assign
id|tape_do_io
c_func
(paren
id|device
comma
id|request
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_eq
l_int|0
)paren
(brace
id|rc
op_assign
id|block_size
op_minus
id|request-&gt;rescnt
suffix:semicolon
id|DBF_EVENT
c_func
(paren
l_int|6
comma
l_string|&quot;TCHAR:rbytes:  %x&bslash;n&quot;
comma
id|rc
)paren
suffix:semicolon
id|filp-&gt;f_pos
op_add_assign
id|rc
suffix:semicolon
multiline_comment|/* Copy data from idal buffer to user space. */
r_if
c_cond
(paren
id|idal_buffer_to_user
c_func
(paren
id|device-&gt;char_data.idal_buf
comma
id|data
comma
id|rc
)paren
op_ne
l_int|0
)paren
id|rc
op_assign
op_minus
id|EFAULT
suffix:semicolon
)brace
id|tape_free_request
c_func
(paren
id|request
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
multiline_comment|/*&n; * Tape device write function&n; */
id|ssize_t
DECL|function|tapechar_write
id|tapechar_write
c_func
(paren
r_struct
id|file
op_star
id|filp
comma
r_const
r_char
id|__user
op_star
id|data
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
id|tape_device
op_star
id|device
suffix:semicolon
r_struct
id|tape_request
op_star
id|request
suffix:semicolon
r_int
id|block_size
suffix:semicolon
r_int
id|written
suffix:semicolon
r_int
id|nblocks
suffix:semicolon
r_int
id|i
comma
id|rc
suffix:semicolon
id|DBF_EVENT
c_func
(paren
l_int|6
comma
l_string|&quot;TCHAR:write&bslash;n&quot;
)paren
suffix:semicolon
id|device
op_assign
(paren
r_struct
id|tape_device
op_star
)paren
id|filp-&gt;private_data
suffix:semicolon
multiline_comment|/* Check position */
r_if
c_cond
(paren
id|ppos
op_ne
op_amp
id|filp-&gt;f_pos
)paren
(brace
multiline_comment|/* &quot;A request was outside the capabilities of the device.&quot; */
id|DBF_EVENT
c_func
(paren
l_int|6
comma
l_string|&quot;TCHAR:ppos wrong&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EOVERFLOW
suffix:semicolon
)brace
multiline_comment|/* Find out block size and number of blocks */
r_if
c_cond
(paren
id|device-&gt;char_data.block_size
op_ne
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|count
OL
id|device-&gt;char_data.block_size
)paren
(brace
id|DBF_EVENT
c_func
(paren
l_int|3
comma
l_string|&quot;TCHAR:write smaller than block &quot;
l_string|&quot;size was requested&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|block_size
op_assign
id|device-&gt;char_data.block_size
suffix:semicolon
id|nblocks
op_assign
id|count
op_div
id|block_size
suffix:semicolon
)brace
r_else
(brace
id|block_size
op_assign
id|count
suffix:semicolon
id|nblocks
op_assign
l_int|1
suffix:semicolon
)brace
id|rc
op_assign
id|tapechar_check_idalbuffer
c_func
(paren
id|device
comma
id|block_size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
r_return
id|rc
suffix:semicolon
macro_line|#ifdef CONFIG_S390_TAPE_BLOCK
multiline_comment|/* Changes position. */
id|device-&gt;blk_data.medium_changed
op_assign
l_int|1
suffix:semicolon
macro_line|#endif
id|DBF_EVENT
c_func
(paren
l_int|6
comma
l_string|&quot;TCHAR:nbytes: %lx&bslash;n&quot;
comma
id|block_size
)paren
suffix:semicolon
id|DBF_EVENT
c_func
(paren
l_int|6
comma
l_string|&quot;TCHAR:nblocks: %x&bslash;n&quot;
comma
id|nblocks
)paren
suffix:semicolon
multiline_comment|/* Let the discipline build the ccw chain. */
id|request
op_assign
id|device-&gt;discipline
op_member_access_from_pointer
id|write_block
c_func
(paren
id|device
comma
id|block_size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|request
)paren
)paren
r_return
id|PTR_ERR
c_func
(paren
id|request
)paren
suffix:semicolon
id|rc
op_assign
l_int|0
suffix:semicolon
id|written
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
id|nblocks
suffix:semicolon
id|i
op_increment
)paren
(brace
multiline_comment|/* Copy data from user space to idal buffer. */
r_if
c_cond
(paren
id|idal_buffer_from_user
c_func
(paren
id|device-&gt;char_data.idal_buf
comma
id|data
comma
id|block_size
)paren
)paren
(brace
id|rc
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_break
suffix:semicolon
)brace
id|rc
op_assign
id|tape_do_io
c_func
(paren
id|device
comma
id|request
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
r_break
suffix:semicolon
id|DBF_EVENT
c_func
(paren
l_int|6
comma
l_string|&quot;TCHAR:wbytes: %lx&bslash;n&quot;
comma
id|block_size
op_minus
id|request-&gt;rescnt
)paren
suffix:semicolon
id|filp-&gt;f_pos
op_add_assign
id|block_size
op_minus
id|request-&gt;rescnt
suffix:semicolon
id|written
op_add_assign
id|block_size
op_minus
id|request-&gt;rescnt
suffix:semicolon
r_if
c_cond
(paren
id|request-&gt;rescnt
op_ne
l_int|0
)paren
r_break
suffix:semicolon
id|data
op_add_assign
id|block_size
suffix:semicolon
)brace
id|tape_free_request
c_func
(paren
id|request
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_eq
op_minus
id|ENOSPC
)paren
(brace
multiline_comment|/*&n;&t;&t; * Ok, the device has no more space. It has NOT written&n;&t;&t; * the block.&n;&t;&t; */
r_if
c_cond
(paren
id|device-&gt;discipline-&gt;process_eov
)paren
id|device-&gt;discipline
op_member_access_from_pointer
id|process_eov
c_func
(paren
id|device
)paren
suffix:semicolon
r_if
c_cond
(paren
id|written
OG
l_int|0
)paren
id|rc
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * After doing a write we always need two tapemarks to correctly&n;&t; * terminate the tape (one to terminate the file, the second to&n;&t; * flag the end of recorded data.&n;&t; * Since process_eov positions the tape in front of the written&n;&t; * tapemark it doesn&squot;t hurt to write two marks again.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|rc
)paren
id|device-&gt;required_tapemarks
op_assign
l_int|2
suffix:semicolon
r_return
id|rc
ques
c_cond
id|rc
suffix:colon
id|written
suffix:semicolon
)brace
multiline_comment|/*&n; * Character frontend tape device open function.&n; */
r_int
DECL|function|tapechar_open
id|tapechar_open
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
r_struct
id|tape_device
op_star
id|device
suffix:semicolon
r_int
id|minor
comma
id|rc
suffix:semicolon
id|DBF_EVENT
c_func
(paren
l_int|6
comma
l_string|&quot;TCHAR:open: %i:%i&bslash;n&quot;
comma
id|imajor
c_func
(paren
id|filp-&gt;f_dentry-&gt;d_inode
)paren
comma
id|iminor
c_func
(paren
id|filp-&gt;f_dentry-&gt;d_inode
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|imajor
c_func
(paren
id|filp-&gt;f_dentry-&gt;d_inode
)paren
op_ne
id|tapechar_major
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|minor
op_assign
id|iminor
c_func
(paren
id|filp-&gt;f_dentry-&gt;d_inode
)paren
suffix:semicolon
id|device
op_assign
id|tape_get_device
c_func
(paren
id|minor
op_div
id|TAPE_MINORS_PER_DEV
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|device
)paren
)paren
(brace
id|DBF_EVENT
c_func
(paren
l_int|3
comma
l_string|&quot;TCHAR:open: tape_get_device() failed&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|PTR_ERR
c_func
(paren
id|device
)paren
suffix:semicolon
)brace
id|rc
op_assign
id|tape_open
c_func
(paren
id|device
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_eq
l_int|0
)paren
(brace
id|filp-&gt;private_data
op_assign
id|device
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|tape_put_device
c_func
(paren
id|device
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
multiline_comment|/*&n; * Character frontend tape device release function.&n; */
r_int
DECL|function|tapechar_release
id|tapechar_release
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
r_struct
id|tape_device
op_star
id|device
suffix:semicolon
id|DBF_EVENT
c_func
(paren
l_int|6
comma
l_string|&quot;TCHAR:release: %x&bslash;n&quot;
comma
id|iminor
c_func
(paren
id|inode
)paren
)paren
suffix:semicolon
id|device
op_assign
(paren
r_struct
id|tape_device
op_star
)paren
id|filp-&gt;private_data
suffix:semicolon
multiline_comment|/*&n;&t; * If this is the rewinding tape minor then rewind. In that case we&n;&t; * write all required tapemarks. Otherwise only one to terminate the&n;&t; * file.&n;&t; */
r_if
c_cond
(paren
(paren
id|iminor
c_func
(paren
id|inode
)paren
op_amp
l_int|1
)paren
op_ne
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|device-&gt;required_tapemarks
)paren
id|tape_std_terminate_write
c_func
(paren
id|device
)paren
suffix:semicolon
id|tape_mtop
c_func
(paren
id|device
comma
id|MTREW
comma
l_int|1
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|device-&gt;required_tapemarks
OG
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|tape_mtop
c_func
(paren
id|device
comma
id|MTWEOF
comma
l_int|1
)paren
op_eq
l_int|0
)paren
id|device-&gt;required_tapemarks
op_decrement
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|device-&gt;char_data.idal_buf
op_ne
l_int|NULL
)paren
(brace
id|idal_buffer_free
c_func
(paren
id|device-&gt;char_data.idal_buf
)paren
suffix:semicolon
id|device-&gt;char_data.idal_buf
op_assign
l_int|NULL
suffix:semicolon
)brace
id|tape_release
c_func
(paren
id|device
)paren
suffix:semicolon
id|filp-&gt;private_data
op_assign
id|tape_put_device
c_func
(paren
id|device
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Tape device io controls.&n; */
r_static
r_int
DECL|function|tapechar_ioctl
id|tapechar_ioctl
c_func
(paren
r_struct
id|inode
op_star
id|inp
comma
r_struct
id|file
op_star
id|filp
comma
r_int
r_int
id|no
comma
r_int
r_int
id|data
)paren
(brace
r_struct
id|tape_device
op_star
id|device
suffix:semicolon
r_int
id|rc
suffix:semicolon
id|DBF_EVENT
c_func
(paren
l_int|6
comma
l_string|&quot;TCHAR:ioct&bslash;n&quot;
)paren
suffix:semicolon
id|device
op_assign
(paren
r_struct
id|tape_device
op_star
)paren
id|filp-&gt;private_data
suffix:semicolon
r_if
c_cond
(paren
id|no
op_eq
id|MTIOCTOP
)paren
(brace
r_struct
id|mtop
id|op
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|op
comma
(paren
r_char
id|__user
op_star
)paren
id|data
comma
r_sizeof
(paren
id|op
)paren
)paren
op_ne
l_int|0
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|op.mt_count
OL
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Operations that change tape position should write final&n;&t;&t; * tapemarks.&n;&t;&t; */
r_switch
c_cond
(paren
id|op.mt_op
)paren
(brace
r_case
id|MTFSF
suffix:colon
r_case
id|MTBSF
suffix:colon
r_case
id|MTFSR
suffix:colon
r_case
id|MTBSR
suffix:colon
r_case
id|MTREW
suffix:colon
r_case
id|MTOFFL
suffix:colon
r_case
id|MTEOM
suffix:colon
r_case
id|MTRETEN
suffix:colon
r_case
id|MTBSFM
suffix:colon
r_case
id|MTFSFM
suffix:colon
r_case
id|MTSEEK
suffix:colon
macro_line|#ifdef CONFIG_S390_TAPE_BLOCK
id|device-&gt;blk_data.medium_changed
op_assign
l_int|1
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|device-&gt;required_tapemarks
)paren
id|tape_std_terminate_write
c_func
(paren
id|device
)paren
suffix:semicolon
r_default
suffix:colon
suffix:semicolon
)brace
id|rc
op_assign
id|tape_mtop
c_func
(paren
id|device
comma
id|op.mt_op
comma
id|op.mt_count
)paren
suffix:semicolon
r_if
c_cond
(paren
id|op.mt_op
op_eq
id|MTWEOF
op_logical_and
id|rc
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|op.mt_count
OG
id|device-&gt;required_tapemarks
)paren
id|device-&gt;required_tapemarks
op_assign
l_int|0
suffix:semicolon
r_else
id|device-&gt;required_tapemarks
op_sub_assign
id|op.mt_count
suffix:semicolon
)brace
r_return
id|rc
suffix:semicolon
)brace
r_if
c_cond
(paren
id|no
op_eq
id|MTIOCPOS
)paren
(brace
multiline_comment|/* MTIOCPOS: query the tape position. */
r_struct
id|mtpos
id|pos
suffix:semicolon
id|rc
op_assign
id|tape_mtop
c_func
(paren
id|device
comma
id|MTTELL
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
OL
l_int|0
)paren
r_return
id|rc
suffix:semicolon
id|pos.mt_blkno
op_assign
id|rc
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
r_char
id|__user
op_star
)paren
id|data
comma
op_amp
id|pos
comma
r_sizeof
(paren
id|pos
)paren
)paren
op_ne
l_int|0
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|no
op_eq
id|MTIOCGET
)paren
(brace
multiline_comment|/* MTIOCGET: query the tape drive status. */
r_struct
id|mtget
id|get
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|get
comma
l_int|0
comma
r_sizeof
(paren
id|get
)paren
)paren
suffix:semicolon
id|get.mt_type
op_assign
id|MT_ISUNKNOWN
suffix:semicolon
id|get.mt_resid
op_assign
l_int|0
multiline_comment|/* device-&gt;devstat.rescnt */
suffix:semicolon
id|get.mt_dsreg
op_assign
id|device-&gt;tape_state
suffix:semicolon
multiline_comment|/* FIXME: mt_gstat, mt_erreg, mt_fileno */
id|get.mt_gstat
op_assign
l_int|0
suffix:semicolon
id|get.mt_erreg
op_assign
l_int|0
suffix:semicolon
id|get.mt_fileno
op_assign
l_int|0
suffix:semicolon
id|get.mt_gstat
op_assign
id|device-&gt;tape_generic_status
suffix:semicolon
r_if
c_cond
(paren
id|device-&gt;medium_state
op_eq
id|MS_LOADED
)paren
(brace
id|rc
op_assign
id|tape_mtop
c_func
(paren
id|device
comma
id|MTTELL
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
OL
l_int|0
)paren
r_return
id|rc
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_eq
l_int|0
)paren
id|get.mt_gstat
op_or_assign
id|GMT_BOT
c_func
(paren
op_complement
l_int|0
)paren
suffix:semicolon
id|get.mt_blkno
op_assign
id|rc
suffix:semicolon
)brace
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
r_char
id|__user
op_star
)paren
id|data
comma
op_amp
id|get
comma
r_sizeof
(paren
id|get
)paren
)paren
op_ne
l_int|0
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Try the discipline ioctl function. */
r_if
c_cond
(paren
id|device-&gt;discipline-&gt;ioctl_fn
op_eq
l_int|NULL
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
id|device-&gt;discipline
op_member_access_from_pointer
id|ioctl_fn
c_func
(paren
id|device
comma
id|no
comma
id|data
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Initialize character device frontend.&n; */
r_int
DECL|function|tapechar_init
id|tapechar_init
(paren
r_void
)paren
(brace
id|dev_t
id|dev
suffix:semicolon
r_if
c_cond
(paren
id|alloc_chrdev_region
c_func
(paren
op_amp
id|dev
comma
l_int|0
comma
l_int|256
comma
l_string|&quot;tape&quot;
)paren
op_ne
l_int|0
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|tapechar_major
op_assign
id|MAJOR
c_func
(paren
id|dev
)paren
suffix:semicolon
id|PRINT_INFO
c_func
(paren
l_string|&quot;tape gets major %d for character devices&bslash;n&quot;
comma
id|MAJOR
c_func
(paren
id|dev
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * cleanup&n; */
r_void
DECL|function|tapechar_exit
id|tapechar_exit
c_func
(paren
r_void
)paren
(brace
id|PRINT_INFO
c_func
(paren
l_string|&quot;tape releases major %d for character devices&bslash;n&quot;
comma
id|tapechar_major
)paren
suffix:semicolon
id|unregister_chrdev_region
c_func
(paren
id|MKDEV
c_func
(paren
id|tapechar_major
comma
l_int|0
)paren
comma
l_int|256
)paren
suffix:semicolon
)brace
eof
