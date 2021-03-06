multiline_comment|/*&n; * file.c - operations for regular (text) files.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/dnotify.h&gt;
macro_line|#include &lt;linux/kobject.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
macro_line|#include &quot;sysfs.h&quot;
DECL|macro|to_subsys
mdefine_line|#define to_subsys(k) container_of(k,struct subsystem,kset.kobj)
DECL|macro|to_sattr
mdefine_line|#define to_sattr(a) container_of(a,struct subsys_attribute,attr)
multiline_comment|/**&n; * Subsystem file operations.&n; * These operations allow subsystems to have files that can be &n; * read/written. &n; */
r_static
id|ssize_t
DECL|function|subsys_attr_show
id|subsys_attr_show
c_func
(paren
r_struct
id|kobject
op_star
id|kobj
comma
r_struct
id|attribute
op_star
id|attr
comma
r_char
op_star
id|page
)paren
(brace
r_struct
id|subsystem
op_star
id|s
op_assign
id|to_subsys
c_func
(paren
id|kobj
)paren
suffix:semicolon
r_struct
id|subsys_attribute
op_star
id|sattr
op_assign
id|to_sattr
c_func
(paren
id|attr
)paren
suffix:semicolon
id|ssize_t
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|sattr-&gt;show
)paren
id|ret
op_assign
id|sattr
op_member_access_from_pointer
id|show
c_func
(paren
id|s
comma
id|page
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|subsys_attr_store
id|subsys_attr_store
c_func
(paren
r_struct
id|kobject
op_star
id|kobj
comma
r_struct
id|attribute
op_star
id|attr
comma
r_const
r_char
op_star
id|page
comma
r_int
id|count
)paren
(brace
r_struct
id|subsystem
op_star
id|s
op_assign
id|to_subsys
c_func
(paren
id|kobj
)paren
suffix:semicolon
r_struct
id|subsys_attribute
op_star
id|sattr
op_assign
id|to_sattr
c_func
(paren
id|attr
)paren
suffix:semicolon
id|ssize_t
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|sattr-&gt;store
)paren
id|ret
op_assign
id|sattr
op_member_access_from_pointer
id|store
c_func
(paren
id|s
comma
id|page
comma
id|count
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|subsys_sysfs_ops
r_static
r_struct
id|sysfs_ops
id|subsys_sysfs_ops
op_assign
(brace
dot
id|show
op_assign
id|subsys_attr_show
comma
dot
id|store
op_assign
id|subsys_attr_store
comma
)brace
suffix:semicolon
DECL|struct|sysfs_buffer
r_struct
id|sysfs_buffer
(brace
DECL|member|count
r_int
id|count
suffix:semicolon
DECL|member|pos
id|loff_t
id|pos
suffix:semicolon
DECL|member|page
r_char
op_star
id|page
suffix:semicolon
DECL|member|ops
r_struct
id|sysfs_ops
op_star
id|ops
suffix:semicolon
DECL|member|sem
r_struct
id|semaphore
id|sem
suffix:semicolon
DECL|member|needs_read_fill
r_int
id|needs_read_fill
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/**&n; *&t;fill_read_buffer - allocate and fill buffer from object.&n; *&t;@dentry:&t;dentry pointer.&n; *&t;@buffer:&t;data buffer for file.&n; *&n; *&t;Allocate @buffer-&gt;page, if it hasn&squot;t been already, then call the&n; *&t;kobject&squot;s show() method to fill the buffer with this attribute&squot;s &n; *&t;data. &n; *&t;This is called only once, on the file&squot;s first read. &n; */
DECL|function|fill_read_buffer
r_static
r_int
id|fill_read_buffer
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_struct
id|sysfs_buffer
op_star
id|buffer
)paren
(brace
r_struct
id|attribute
op_star
id|attr
op_assign
id|to_attr
c_func
(paren
id|dentry
)paren
suffix:semicolon
r_struct
id|kobject
op_star
id|kobj
op_assign
id|to_kobj
c_func
(paren
id|dentry-&gt;d_parent
)paren
suffix:semicolon
r_struct
id|sysfs_ops
op_star
id|ops
op_assign
id|buffer-&gt;ops
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
id|ssize_t
id|count
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buffer-&gt;page
)paren
id|buffer-&gt;page
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
id|buffer-&gt;page
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|count
op_assign
id|ops
op_member_access_from_pointer
id|show
c_func
(paren
id|kobj
comma
id|attr
comma
id|buffer-&gt;page
)paren
suffix:semicolon
id|buffer-&gt;needs_read_fill
op_assign
l_int|0
suffix:semicolon
id|BUG_ON
c_func
(paren
id|count
OG
(paren
id|ssize_t
)paren
id|PAGE_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|count
op_ge
l_int|0
)paren
id|buffer-&gt;count
op_assign
id|count
suffix:semicolon
r_else
id|ret
op_assign
id|count
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;flush_read_buffer - push buffer to userspace.&n; *&t;@buffer:&t;data buffer for file.&n; *&t;@userbuf:&t;user-passed buffer.&n; *&t;@count:&t;&t;number of bytes requested.&n; *&t;@ppos:&t;&t;file position.&n; *&n; *&t;Copy the buffer we filled in fill_read_buffer() to userspace.&n; *&t;This is done at the reader&squot;s leisure, copying and advancing &n; *&t;the amount they specify each time.&n; *&t;This may be called continuously until the buffer is empty.&n; */
DECL|function|flush_read_buffer
r_static
r_int
id|flush_read_buffer
c_func
(paren
r_struct
id|sysfs_buffer
op_star
id|buffer
comma
r_char
id|__user
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
r_if
c_cond
(paren
op_star
id|ppos
OG
id|buffer-&gt;count
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|count
OG
(paren
id|buffer-&gt;count
op_minus
op_star
id|ppos
)paren
)paren
id|count
op_assign
id|buffer-&gt;count
op_minus
op_star
id|ppos
suffix:semicolon
id|error
op_assign
id|copy_to_user
c_func
(paren
id|buf
comma
id|buffer-&gt;page
op_plus
op_star
id|ppos
comma
id|count
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
op_star
id|ppos
op_add_assign
id|count
suffix:semicolon
r_return
id|error
ques
c_cond
op_minus
id|EFAULT
suffix:colon
id|count
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;sysfs_read_file - read an attribute. &n; *&t;@file:&t;file pointer.&n; *&t;@buf:&t;buffer to fill.&n; *&t;@count:&t;number of bytes to read.&n; *&t;@ppos:&t;starting offset in file.&n; *&n; *&t;Userspace wants to read an attribute file. The attribute descriptor&n; *&t;is in the file&squot;s -&gt;d_fsdata. The target object is in the directory&squot;s&n; *&t;-&gt;d_fsdata.&n; *&n; *&t;We call fill_read_buffer() to allocate and fill the buffer from the&n; *&t;object&squot;s show() method exactly once (if the read is happening from&n; *&t;the beginning of the file). That should fill the entire buffer with&n; *&t;all the data the object has to offer for that attribute.&n; *&t;We then call flush_read_buffer() to copy the buffer to userspace&n; *&t;in the increments specified.&n; */
r_static
id|ssize_t
DECL|function|sysfs_read_file
id|sysfs_read_file
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_char
id|__user
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
id|sysfs_buffer
op_star
id|buffer
op_assign
id|file-&gt;private_data
suffix:semicolon
id|ssize_t
id|retval
op_assign
l_int|0
suffix:semicolon
id|down
c_func
(paren
op_amp
id|buffer-&gt;sem
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buffer-&gt;needs_read_fill
)paren
(brace
r_if
c_cond
(paren
(paren
id|retval
op_assign
id|fill_read_buffer
c_func
(paren
id|file-&gt;f_dentry
comma
id|buffer
)paren
)paren
)paren
r_goto
id|out
suffix:semicolon
)brace
id|pr_debug
c_func
(paren
l_string|&quot;%s: count = %d, ppos = %lld, buf = %s&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|count
comma
op_star
id|ppos
comma
id|buffer-&gt;page
)paren
suffix:semicolon
id|retval
op_assign
id|flush_read_buffer
c_func
(paren
id|buffer
comma
id|buf
comma
id|count
comma
id|ppos
)paren
suffix:semicolon
id|out
suffix:colon
id|up
c_func
(paren
op_amp
id|buffer-&gt;sem
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;fill_write_buffer - copy buffer from userspace.&n; *&t;@buffer:&t;data buffer for file.&n; *&t;@userbuf:&t;data from user.&n; *&t;@count:&t;&t;number of bytes in @userbuf.&n; *&n; *&t;Allocate @buffer-&gt;page if it hasn&squot;t been already, then&n; *&t;copy the user-supplied buffer into it.&n; */
r_static
r_int
DECL|function|fill_write_buffer
id|fill_write_buffer
c_func
(paren
r_struct
id|sysfs_buffer
op_star
id|buffer
comma
r_const
r_char
id|__user
op_star
id|buf
comma
r_int
id|count
)paren
(brace
r_int
id|error
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buffer-&gt;page
)paren
id|buffer-&gt;page
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
id|buffer-&gt;page
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
id|count
op_ge
id|PAGE_SIZE
)paren
id|count
op_assign
id|PAGE_SIZE
op_minus
l_int|1
suffix:semicolon
id|error
op_assign
id|copy_from_user
c_func
(paren
id|buffer-&gt;page
comma
id|buf
comma
id|count
)paren
suffix:semicolon
id|buffer-&gt;needs_read_fill
op_assign
l_int|1
suffix:semicolon
r_return
id|error
ques
c_cond
op_minus
id|EFAULT
suffix:colon
id|count
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;flush_write_buffer - push buffer to kobject.&n; *&t;@file:&t;&t;file pointer.&n; *&t;@buffer:&t;data buffer for file.&n; *&n; *&t;Get the correct pointers for the kobject and the attribute we&squot;re&n; *&t;dealing with, then call the store() method for the attribute, &n; *&t;passing the buffer that we acquired in fill_write_buffer().&n; */
r_static
r_int
DECL|function|flush_write_buffer
id|flush_write_buffer
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_struct
id|sysfs_buffer
op_star
id|buffer
comma
r_int
id|count
)paren
(brace
r_struct
id|attribute
op_star
id|attr
op_assign
id|to_attr
c_func
(paren
id|dentry
)paren
suffix:semicolon
r_struct
id|kobject
op_star
id|kobj
op_assign
id|to_kobj
c_func
(paren
id|dentry-&gt;d_parent
)paren
suffix:semicolon
r_struct
id|sysfs_ops
op_star
id|ops
op_assign
id|buffer-&gt;ops
suffix:semicolon
r_return
id|ops
op_member_access_from_pointer
id|store
c_func
(paren
id|kobj
comma
id|attr
comma
id|buffer-&gt;page
comma
id|count
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;sysfs_write_file - write an attribute.&n; *&t;@file:&t;file pointer&n; *&t;@buf:&t;data to write&n; *&t;@count:&t;number of bytes&n; *&t;@ppos:&t;starting offset&n; *&n; *&t;Similar to sysfs_read_file(), though working in the opposite direction.&n; *&t;We allocate and fill the data from the user in fill_write_buffer(),&n; *&t;then push it to the kobject in flush_write_buffer().&n; *&t;There is no easy way for us to know if userspace is only doing a partial&n; *&t;write, so we don&squot;t support them. We expect the entire buffer to come&n; *&t;on the first write. &n; *&t;Hint: if you&squot;re writing a value, first read the file, modify only the&n; *&t;the value you&squot;re changing, then write entire buffer back. &n; */
r_static
id|ssize_t
DECL|function|sysfs_write_file
id|sysfs_write_file
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_char
id|__user
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
id|sysfs_buffer
op_star
id|buffer
op_assign
id|file-&gt;private_data
suffix:semicolon
id|ssize_t
id|len
suffix:semicolon
id|down
c_func
(paren
op_amp
id|buffer-&gt;sem
)paren
suffix:semicolon
id|len
op_assign
id|fill_write_buffer
c_func
(paren
id|buffer
comma
id|buf
comma
id|count
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
l_int|0
)paren
id|len
op_assign
id|flush_write_buffer
c_func
(paren
id|file-&gt;f_dentry
comma
id|buffer
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
l_int|0
)paren
op_star
id|ppos
op_add_assign
id|len
suffix:semicolon
id|up
c_func
(paren
op_amp
id|buffer-&gt;sem
)paren
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
DECL|function|check_perm
r_static
r_int
id|check_perm
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
id|kobject
op_star
id|kobj
op_assign
id|sysfs_get_kobject
c_func
(paren
id|file-&gt;f_dentry-&gt;d_parent
)paren
suffix:semicolon
r_struct
id|attribute
op_star
id|attr
op_assign
id|to_attr
c_func
(paren
id|file-&gt;f_dentry
)paren
suffix:semicolon
r_struct
id|sysfs_buffer
op_star
id|buffer
suffix:semicolon
r_struct
id|sysfs_ops
op_star
id|ops
op_assign
l_int|NULL
suffix:semicolon
r_int
id|error
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|kobj
op_logical_or
op_logical_neg
id|attr
)paren
r_goto
id|Einval
suffix:semicolon
multiline_comment|/* Grab the module reference for this attribute if we have one */
r_if
c_cond
(paren
op_logical_neg
id|try_module_get
c_func
(paren
id|attr-&gt;owner
)paren
)paren
(brace
id|error
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|Done
suffix:semicolon
)brace
multiline_comment|/* if the kobject has no ktype, then we assume that it is a subsystem&n;&t; * itself, and use ops for it.&n;&t; */
r_if
c_cond
(paren
id|kobj-&gt;kset
op_logical_and
id|kobj-&gt;kset-&gt;ktype
)paren
id|ops
op_assign
id|kobj-&gt;kset-&gt;ktype-&gt;sysfs_ops
suffix:semicolon
r_else
r_if
c_cond
(paren
id|kobj-&gt;ktype
)paren
id|ops
op_assign
id|kobj-&gt;ktype-&gt;sysfs_ops
suffix:semicolon
r_else
id|ops
op_assign
op_amp
id|subsys_sysfs_ops
suffix:semicolon
multiline_comment|/* No sysfs operations, either from having no subsystem,&n;&t; * or the subsystem have no operations.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|ops
)paren
r_goto
id|Eaccess
suffix:semicolon
multiline_comment|/* File needs write support.&n;&t; * The inode&squot;s perms must say it&squot;s ok, &n;&t; * and we must have a store method.&n;&t; */
r_if
c_cond
(paren
id|file-&gt;f_mode
op_amp
id|FMODE_WRITE
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|inode-&gt;i_mode
op_amp
id|S_IWUGO
)paren
op_logical_or
op_logical_neg
id|ops-&gt;store
)paren
r_goto
id|Eaccess
suffix:semicolon
)brace
multiline_comment|/* File needs read support.&n;&t; * The inode&squot;s perms must say it&squot;s ok, and we there&n;&t; * must be a show method for it.&n;&t; */
r_if
c_cond
(paren
id|file-&gt;f_mode
op_amp
id|FMODE_READ
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|inode-&gt;i_mode
op_amp
id|S_IRUGO
)paren
op_logical_or
op_logical_neg
id|ops-&gt;show
)paren
r_goto
id|Eaccess
suffix:semicolon
)brace
multiline_comment|/* No error? Great, allocate a buffer for the file, and store it&n;&t; * it in file-&gt;private_data for easy access.&n;&t; */
id|buffer
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|sysfs_buffer
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buffer
)paren
(brace
id|memset
c_func
(paren
id|buffer
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|sysfs_buffer
)paren
)paren
suffix:semicolon
id|init_MUTEX
c_func
(paren
op_amp
id|buffer-&gt;sem
)paren
suffix:semicolon
id|buffer-&gt;needs_read_fill
op_assign
l_int|1
suffix:semicolon
id|buffer-&gt;ops
op_assign
id|ops
suffix:semicolon
id|file-&gt;private_data
op_assign
id|buffer
suffix:semicolon
)brace
r_else
id|error
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|Done
suffix:semicolon
id|Einval
suffix:colon
id|error
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|Done
suffix:semicolon
id|Eaccess
suffix:colon
id|error
op_assign
op_minus
id|EACCES
suffix:semicolon
id|module_put
c_func
(paren
id|attr-&gt;owner
)paren
suffix:semicolon
id|Done
suffix:colon
r_if
c_cond
(paren
id|error
op_logical_and
id|kobj
)paren
id|kobject_put
c_func
(paren
id|kobj
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|function|sysfs_open_file
r_static
r_int
id|sysfs_open_file
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
r_return
id|check_perm
c_func
(paren
id|inode
comma
id|filp
)paren
suffix:semicolon
)brace
DECL|function|sysfs_release
r_static
r_int
id|sysfs_release
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
id|kobject
op_star
id|kobj
op_assign
id|to_kobj
c_func
(paren
id|filp-&gt;f_dentry-&gt;d_parent
)paren
suffix:semicolon
r_struct
id|attribute
op_star
id|attr
op_assign
id|to_attr
c_func
(paren
id|filp-&gt;f_dentry
)paren
suffix:semicolon
r_struct
id|module
op_star
id|owner
op_assign
id|attr-&gt;owner
suffix:semicolon
r_struct
id|sysfs_buffer
op_star
id|buffer
op_assign
id|filp-&gt;private_data
suffix:semicolon
r_if
c_cond
(paren
id|kobj
)paren
id|kobject_put
c_func
(paren
id|kobj
)paren
suffix:semicolon
multiline_comment|/* After this point, attr should not be accessed. */
id|module_put
c_func
(paren
id|owner
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buffer
)paren
(brace
r_if
c_cond
(paren
id|buffer-&gt;page
)paren
id|free_page
c_func
(paren
(paren
r_int
r_int
)paren
id|buffer-&gt;page
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|buffer
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|sysfs_file_operations
r_struct
id|file_operations
id|sysfs_file_operations
op_assign
(brace
dot
id|read
op_assign
id|sysfs_read_file
comma
dot
id|write
op_assign
id|sysfs_write_file
comma
dot
id|llseek
op_assign
id|generic_file_llseek
comma
dot
id|open
op_assign
id|sysfs_open_file
comma
dot
id|release
op_assign
id|sysfs_release
comma
)brace
suffix:semicolon
DECL|function|sysfs_add_file
r_int
id|sysfs_add_file
c_func
(paren
r_struct
id|dentry
op_star
id|dir
comma
r_const
r_struct
id|attribute
op_star
id|attr
comma
r_int
id|type
)paren
(brace
r_struct
id|sysfs_dirent
op_star
id|parent_sd
op_assign
id|dir-&gt;d_fsdata
suffix:semicolon
id|umode_t
id|mode
op_assign
(paren
id|attr-&gt;mode
op_amp
id|S_IALLUGO
)paren
op_or
id|S_IFREG
suffix:semicolon
r_int
id|error
op_assign
l_int|0
suffix:semicolon
id|down
c_func
(paren
op_amp
id|dir-&gt;d_inode-&gt;i_sem
)paren
suffix:semicolon
id|error
op_assign
id|sysfs_make_dirent
c_func
(paren
id|parent_sd
comma
l_int|NULL
comma
(paren
r_void
op_star
)paren
id|attr
comma
id|mode
comma
id|type
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|dir-&gt;d_inode-&gt;i_sem
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;sysfs_create_file - create an attribute file for an object.&n; *&t;@kobj:&t;object we&squot;re creating for. &n; *&t;@attr:&t;atrribute descriptor.&n; */
DECL|function|sysfs_create_file
r_int
id|sysfs_create_file
c_func
(paren
r_struct
id|kobject
op_star
id|kobj
comma
r_const
r_struct
id|attribute
op_star
id|attr
)paren
(brace
id|BUG_ON
c_func
(paren
op_logical_neg
id|kobj
op_logical_or
op_logical_neg
id|kobj-&gt;dentry
op_logical_or
op_logical_neg
id|attr
)paren
suffix:semicolon
r_return
id|sysfs_add_file
c_func
(paren
id|kobj-&gt;dentry
comma
id|attr
comma
id|SYSFS_KOBJ_ATTR
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * sysfs_update_file - update the modified timestamp on an object attribute.&n; * @kobj: object we&squot;re acting for.&n; * @attr: attribute descriptor.&n; *&n; * Also call dnotify for the dentry, which lots of userspace programs&n; * use.&n; */
DECL|function|sysfs_update_file
r_int
id|sysfs_update_file
c_func
(paren
r_struct
id|kobject
op_star
id|kobj
comma
r_const
r_struct
id|attribute
op_star
id|attr
)paren
(brace
r_struct
id|dentry
op_star
id|dir
op_assign
id|kobj-&gt;dentry
suffix:semicolon
r_struct
id|dentry
op_star
id|victim
suffix:semicolon
r_int
id|res
op_assign
op_minus
id|ENOENT
suffix:semicolon
id|down
c_func
(paren
op_amp
id|dir-&gt;d_inode-&gt;i_sem
)paren
suffix:semicolon
id|victim
op_assign
id|sysfs_get_dentry
c_func
(paren
id|dir
comma
id|attr-&gt;name
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|IS_ERR
c_func
(paren
id|victim
)paren
)paren
(brace
multiline_comment|/* make sure dentry is really there */
r_if
c_cond
(paren
id|victim-&gt;d_inode
op_logical_and
(paren
id|victim-&gt;d_parent-&gt;d_inode
op_eq
id|dir-&gt;d_inode
)paren
)paren
(brace
id|victim-&gt;d_inode-&gt;i_mtime
op_assign
id|CURRENT_TIME
suffix:semicolon
id|dnotify_parent
c_func
(paren
id|victim
comma
id|DN_MODIFY
)paren
suffix:semicolon
multiline_comment|/**&n;&t;&t;&t; * Drop reference from initial sysfs_get_dentry().&n;&t;&t;&t; */
id|dput
c_func
(paren
id|victim
)paren
suffix:semicolon
id|res
op_assign
l_int|0
suffix:semicolon
)brace
r_else
id|d_drop
c_func
(paren
id|victim
)paren
suffix:semicolon
multiline_comment|/**&n;&t;&t; * Drop the reference acquired from sysfs_get_dentry() above.&n;&t;&t; */
id|dput
c_func
(paren
id|victim
)paren
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
id|dir-&gt;d_inode-&gt;i_sem
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;sysfs_remove_file - remove an object attribute.&n; *&t;@kobj:&t;object we&squot;re acting for.&n; *&t;@attr:&t;attribute descriptor.&n; *&n; *&t;Hash the attribute name and kill the victim.&n; */
DECL|function|sysfs_remove_file
r_void
id|sysfs_remove_file
c_func
(paren
r_struct
id|kobject
op_star
id|kobj
comma
r_const
r_struct
id|attribute
op_star
id|attr
)paren
(brace
id|sysfs_hash_and_remove
c_func
(paren
id|kobj-&gt;dentry
comma
id|attr-&gt;name
)paren
suffix:semicolon
)brace
DECL|variable|sysfs_create_file
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|sysfs_create_file
)paren
suffix:semicolon
DECL|variable|sysfs_remove_file
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|sysfs_remove_file
)paren
suffix:semicolon
DECL|variable|sysfs_update_file
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|sysfs_update_file
)paren
suffix:semicolon
eof
