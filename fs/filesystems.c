multiline_comment|/*&n; *  linux/fs/filesystems.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; *&n; *  table of configured filesystems&n; */
macro_line|#include &lt;linux/syscalls.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/kmod.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
multiline_comment|/*&n; * Handling of filesystem drivers list.&n; * Rules:&n; *&t;Inclusion to/removals from/scanning of list are protected by spinlock.&n; *&t;During the unload module must call unregister_filesystem().&n; *&t;We can access the fields of list element if:&n; *&t;&t;1) spinlock is held or&n; *&t;&t;2) we hold the reference to the module.&n; *&t;The latter can be guaranteed by call of try_module_get(); if it&n; *&t;returned 0 we must skip the element, otherwise we got the reference.&n; *&t;Once the reference is obtained we can drop the spinlock.&n; */
DECL|variable|file_systems
r_static
r_struct
id|file_system_type
op_star
id|file_systems
suffix:semicolon
r_static
id|DEFINE_RWLOCK
c_func
(paren
id|file_systems_lock
)paren
suffix:semicolon
multiline_comment|/* WARNING: This can be used only if we _already_ own a reference */
DECL|function|get_filesystem
r_void
id|get_filesystem
c_func
(paren
r_struct
id|file_system_type
op_star
id|fs
)paren
(brace
id|__module_get
c_func
(paren
id|fs-&gt;owner
)paren
suffix:semicolon
)brace
DECL|function|put_filesystem
r_void
id|put_filesystem
c_func
(paren
r_struct
id|file_system_type
op_star
id|fs
)paren
(brace
id|module_put
c_func
(paren
id|fs-&gt;owner
)paren
suffix:semicolon
)brace
DECL|function|find_filesystem
r_static
r_struct
id|file_system_type
op_star
op_star
id|find_filesystem
c_func
(paren
r_const
r_char
op_star
id|name
)paren
(brace
r_struct
id|file_system_type
op_star
op_star
id|p
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
op_amp
id|file_systems
suffix:semicolon
op_star
id|p
suffix:semicolon
id|p
op_assign
op_amp
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|next
)paren
r_if
c_cond
(paren
id|strcmp
c_func
(paren
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|name
comma
id|name
)paren
op_eq
l_int|0
)paren
r_break
suffix:semicolon
r_return
id|p
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;register_filesystem - register a new filesystem&n; *&t;@fs: the file system structure&n; *&n; *&t;Adds the file system passed to the list of file systems the kernel&n; *&t;is aware of for mount and other syscalls. Returns 0 on success,&n; *&t;or a negative errno code on an error.&n; *&n; *&t;The &amp;struct file_system_type that is passed is linked into the kernel &n; *&t;structures and must not be freed until the file system has been&n; *&t;unregistered.&n; */
DECL|function|register_filesystem
r_int
id|register_filesystem
c_func
(paren
r_struct
id|file_system_type
op_star
id|fs
)paren
(brace
r_int
id|res
op_assign
l_int|0
suffix:semicolon
r_struct
id|file_system_type
op_star
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fs
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|fs-&gt;next
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|fs-&gt;fs_supers
)paren
suffix:semicolon
id|write_lock
c_func
(paren
op_amp
id|file_systems_lock
)paren
suffix:semicolon
id|p
op_assign
id|find_filesystem
c_func
(paren
id|fs-&gt;name
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|p
)paren
id|res
op_assign
op_minus
id|EBUSY
suffix:semicolon
r_else
op_star
id|p
op_assign
id|fs
suffix:semicolon
id|write_unlock
c_func
(paren
op_amp
id|file_systems_lock
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
DECL|variable|register_filesystem
id|EXPORT_SYMBOL
c_func
(paren
id|register_filesystem
)paren
suffix:semicolon
multiline_comment|/**&n; *&t;unregister_filesystem - unregister a file system&n; *&t;@fs: filesystem to unregister&n; *&n; *&t;Remove a file system that was previously successfully registered&n; *&t;with the kernel. An error is returned if the file system is not found.&n; *&t;Zero is returned on a success.&n; *&t;&n; *&t;Once this function has returned the &amp;struct file_system_type structure&n; *&t;may be freed or reused.&n; */
DECL|function|unregister_filesystem
r_int
id|unregister_filesystem
c_func
(paren
r_struct
id|file_system_type
op_star
id|fs
)paren
(brace
r_struct
id|file_system_type
op_star
op_star
id|tmp
suffix:semicolon
id|write_lock
c_func
(paren
op_amp
id|file_systems_lock
)paren
suffix:semicolon
id|tmp
op_assign
op_amp
id|file_systems
suffix:semicolon
r_while
c_loop
(paren
op_star
id|tmp
)paren
(brace
r_if
c_cond
(paren
id|fs
op_eq
op_star
id|tmp
)paren
(brace
op_star
id|tmp
op_assign
id|fs-&gt;next
suffix:semicolon
id|fs-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|write_unlock
c_func
(paren
op_amp
id|file_systems_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|tmp
op_assign
op_amp
(paren
op_star
id|tmp
)paren
op_member_access_from_pointer
id|next
suffix:semicolon
)brace
id|write_unlock
c_func
(paren
op_amp
id|file_systems_lock
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|variable|unregister_filesystem
id|EXPORT_SYMBOL
c_func
(paren
id|unregister_filesystem
)paren
suffix:semicolon
DECL|function|fs_index
r_static
r_int
id|fs_index
c_func
(paren
r_const
r_char
id|__user
op_star
id|__name
)paren
(brace
r_struct
id|file_system_type
op_star
id|tmp
suffix:semicolon
r_char
op_star
id|name
suffix:semicolon
r_int
id|err
comma
id|index
suffix:semicolon
id|name
op_assign
id|getname
c_func
(paren
id|__name
)paren
suffix:semicolon
id|err
op_assign
id|PTR_ERR
c_func
(paren
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|name
)paren
)paren
r_return
id|err
suffix:semicolon
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|file_systems_lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|tmp
op_assign
id|file_systems
comma
id|index
op_assign
l_int|0
suffix:semicolon
id|tmp
suffix:semicolon
id|tmp
op_assign
id|tmp-&gt;next
comma
id|index
op_increment
)paren
(brace
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|tmp-&gt;name
comma
id|name
)paren
op_eq
l_int|0
)paren
(brace
id|err
op_assign
id|index
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|read_unlock
c_func
(paren
op_amp
id|file_systems_lock
)paren
suffix:semicolon
id|putname
c_func
(paren
id|name
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|fs_name
r_static
r_int
id|fs_name
c_func
(paren
r_int
r_int
id|index
comma
r_char
id|__user
op_star
id|buf
)paren
(brace
r_struct
id|file_system_type
op_star
id|tmp
suffix:semicolon
r_int
id|len
comma
id|res
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|file_systems_lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|tmp
op_assign
id|file_systems
suffix:semicolon
id|tmp
suffix:semicolon
id|tmp
op_assign
id|tmp-&gt;next
comma
id|index
op_decrement
)paren
r_if
c_cond
(paren
id|index
op_le
l_int|0
op_logical_and
id|try_module_get
c_func
(paren
id|tmp-&gt;owner
)paren
)paren
r_break
suffix:semicolon
id|read_unlock
c_func
(paren
op_amp
id|file_systems_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tmp
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* OK, we got the reference, so we can safely block */
id|len
op_assign
id|strlen
c_func
(paren
id|tmp-&gt;name
)paren
op_plus
l_int|1
suffix:semicolon
id|res
op_assign
id|copy_to_user
c_func
(paren
id|buf
comma
id|tmp-&gt;name
comma
id|len
)paren
ques
c_cond
op_minus
id|EFAULT
suffix:colon
l_int|0
suffix:semicolon
id|put_filesystem
c_func
(paren
id|tmp
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
DECL|function|fs_maxindex
r_static
r_int
id|fs_maxindex
c_func
(paren
r_void
)paren
(brace
r_struct
id|file_system_type
op_star
id|tmp
suffix:semicolon
r_int
id|index
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|file_systems_lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|tmp
op_assign
id|file_systems
comma
id|index
op_assign
l_int|0
suffix:semicolon
id|tmp
suffix:semicolon
id|tmp
op_assign
id|tmp-&gt;next
comma
id|index
op_increment
)paren
suffix:semicolon
id|read_unlock
c_func
(paren
op_amp
id|file_systems_lock
)paren
suffix:semicolon
r_return
id|index
suffix:semicolon
)brace
multiline_comment|/*&n; * Whee.. Weird sysv syscall. &n; */
DECL|function|sys_sysfs
id|asmlinkage
r_int
id|sys_sysfs
c_func
(paren
r_int
id|option
comma
r_int
r_int
id|arg1
comma
r_int
r_int
id|arg2
)paren
(brace
r_int
id|retval
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_switch
c_cond
(paren
id|option
)paren
(brace
r_case
l_int|1
suffix:colon
id|retval
op_assign
id|fs_index
c_func
(paren
(paren
r_const
r_char
id|__user
op_star
)paren
id|arg1
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|retval
op_assign
id|fs_name
c_func
(paren
id|arg1
comma
(paren
r_char
id|__user
op_star
)paren
id|arg2
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|retval
op_assign
id|fs_maxindex
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|retval
suffix:semicolon
)brace
DECL|function|get_filesystem_list
r_int
id|get_filesystem_list
c_func
(paren
r_char
op_star
id|buf
)paren
(brace
r_int
id|len
op_assign
l_int|0
suffix:semicolon
r_struct
id|file_system_type
op_star
id|tmp
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|file_systems_lock
)paren
suffix:semicolon
id|tmp
op_assign
id|file_systems
suffix:semicolon
r_while
c_loop
(paren
id|tmp
op_logical_and
id|len
OL
id|PAGE_SIZE
op_minus
l_int|80
)paren
(brace
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|len
comma
l_string|&quot;%s&bslash;t%s&bslash;n&quot;
comma
(paren
id|tmp-&gt;fs_flags
op_amp
id|FS_REQUIRES_DEV
)paren
ques
c_cond
l_string|&quot;&quot;
suffix:colon
l_string|&quot;nodev&quot;
comma
id|tmp-&gt;name
)paren
suffix:semicolon
id|tmp
op_assign
id|tmp-&gt;next
suffix:semicolon
)brace
id|read_unlock
c_func
(paren
op_amp
id|file_systems_lock
)paren
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
DECL|function|get_fs_type
r_struct
id|file_system_type
op_star
id|get_fs_type
c_func
(paren
r_const
r_char
op_star
id|name
)paren
(brace
r_struct
id|file_system_type
op_star
id|fs
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|file_systems_lock
)paren
suffix:semicolon
id|fs
op_assign
op_star
(paren
id|find_filesystem
c_func
(paren
id|name
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fs
op_logical_and
op_logical_neg
id|try_module_get
c_func
(paren
id|fs-&gt;owner
)paren
)paren
id|fs
op_assign
l_int|NULL
suffix:semicolon
id|read_unlock
c_func
(paren
op_amp
id|file_systems_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fs
op_logical_and
(paren
id|request_module
c_func
(paren
l_string|&quot;%s&quot;
comma
id|name
)paren
op_eq
l_int|0
)paren
)paren
(brace
id|read_lock
c_func
(paren
op_amp
id|file_systems_lock
)paren
suffix:semicolon
id|fs
op_assign
op_star
(paren
id|find_filesystem
c_func
(paren
id|name
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fs
op_logical_and
op_logical_neg
id|try_module_get
c_func
(paren
id|fs-&gt;owner
)paren
)paren
id|fs
op_assign
l_int|NULL
suffix:semicolon
id|read_unlock
c_func
(paren
op_amp
id|file_systems_lock
)paren
suffix:semicolon
)brace
r_return
id|fs
suffix:semicolon
)brace
DECL|variable|get_fs_type
id|EXPORT_SYMBOL
c_func
(paren
id|get_fs_type
)paren
suffix:semicolon
eof
