multiline_comment|/*&n; *  linux/fs/char_dev.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/devfs_fs_kernel.h&gt;
macro_line|#include &lt;linux/kobject.h&gt;
macro_line|#include &lt;linux/kobj_map.h&gt;
macro_line|#include &lt;linux/cdev.h&gt;
macro_line|#ifdef CONFIG_KMOD
macro_line|#include &lt;linux/kmod.h&gt;
macro_line|#endif
DECL|variable|cdev_map
r_static
r_struct
id|kobj_map
op_star
id|cdev_map
suffix:semicolon
multiline_comment|/* degrade to linked list for small systems */
DECL|macro|MAX_PROBE_HASH
mdefine_line|#define MAX_PROBE_HASH (CONFIG_BASE_SMALL ? 1 : 255)
r_static
id|DEFINE_RWLOCK
c_func
(paren
id|chrdevs_lock
)paren
suffix:semicolon
DECL|struct|char_device_struct
r_static
r_struct
id|char_device_struct
(brace
DECL|member|next
r_struct
id|char_device_struct
op_star
id|next
suffix:semicolon
DECL|member|major
r_int
r_int
id|major
suffix:semicolon
DECL|member|baseminor
r_int
r_int
id|baseminor
suffix:semicolon
DECL|member|minorct
r_int
id|minorct
suffix:semicolon
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|fops
r_struct
id|file_operations
op_star
id|fops
suffix:semicolon
DECL|member|cdev
r_struct
id|cdev
op_star
id|cdev
suffix:semicolon
multiline_comment|/* will die */
DECL|variable|chrdevs
)brace
op_star
id|chrdevs
(braket
id|MAX_PROBE_HASH
)braket
suffix:semicolon
multiline_comment|/* index in the above */
DECL|function|major_to_index
r_static
r_inline
r_int
id|major_to_index
c_func
(paren
r_int
id|major
)paren
(brace
r_return
id|major
op_mod
id|MAX_PROBE_HASH
suffix:semicolon
)brace
multiline_comment|/* get char device names in somewhat random order */
DECL|function|get_chrdev_list
r_int
id|get_chrdev_list
c_func
(paren
r_char
op_star
id|page
)paren
(brace
r_struct
id|char_device_struct
op_star
id|cd
suffix:semicolon
r_int
id|i
comma
id|len
suffix:semicolon
id|len
op_assign
id|sprintf
c_func
(paren
id|page
comma
l_string|&quot;Character devices:&bslash;n&quot;
)paren
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|chrdevs_lock
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
id|ARRAY_SIZE
c_func
(paren
id|chrdevs
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
r_for
c_loop
(paren
id|cd
op_assign
id|chrdevs
(braket
id|i
)braket
suffix:semicolon
id|cd
suffix:semicolon
id|cd
op_assign
id|cd-&gt;next
)paren
id|len
op_add_assign
id|sprintf
c_func
(paren
id|page
op_plus
id|len
comma
l_string|&quot;%3d %s&bslash;n&quot;
comma
id|cd-&gt;major
comma
id|cd-&gt;name
)paren
suffix:semicolon
)brace
id|read_unlock
c_func
(paren
op_amp
id|chrdevs_lock
)paren
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
multiline_comment|/*&n; * Register a single major with a specified minor range.&n; *&n; * If major == 0 this functions will dynamically allocate a major and return&n; * its number.&n; *&n; * If major &gt; 0 this function will attempt to reserve the passed range of&n; * minors and will return zero on success.&n; *&n; * Returns a -ve errno on failure.&n; */
r_static
r_struct
id|char_device_struct
op_star
DECL|function|__register_chrdev_region
id|__register_chrdev_region
c_func
(paren
r_int
r_int
id|major
comma
r_int
r_int
id|baseminor
comma
r_int
id|minorct
comma
r_const
r_char
op_star
id|name
)paren
(brace
r_struct
id|char_device_struct
op_star
id|cd
comma
op_star
op_star
id|cp
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_int
id|i
suffix:semicolon
id|cd
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|char_device_struct
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cd
op_eq
l_int|NULL
)paren
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|ENOMEM
)paren
suffix:semicolon
id|memset
c_func
(paren
id|cd
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|char_device_struct
)paren
)paren
suffix:semicolon
id|write_lock_irq
c_func
(paren
op_amp
id|chrdevs_lock
)paren
suffix:semicolon
multiline_comment|/* temporary */
r_if
c_cond
(paren
id|major
op_eq
l_int|0
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
id|ARRAY_SIZE
c_func
(paren
id|chrdevs
)paren
op_minus
l_int|1
suffix:semicolon
id|i
OG
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
(brace
r_if
c_cond
(paren
id|chrdevs
(braket
id|i
)braket
op_eq
l_int|NULL
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
op_eq
l_int|0
)paren
(brace
id|ret
op_assign
op_minus
id|EBUSY
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|major
op_assign
id|i
suffix:semicolon
id|ret
op_assign
id|major
suffix:semicolon
)brace
id|cd-&gt;major
op_assign
id|major
suffix:semicolon
id|cd-&gt;baseminor
op_assign
id|baseminor
suffix:semicolon
id|cd-&gt;minorct
op_assign
id|minorct
suffix:semicolon
id|cd-&gt;name
op_assign
id|name
suffix:semicolon
id|i
op_assign
id|major_to_index
c_func
(paren
id|major
)paren
suffix:semicolon
r_for
c_loop
(paren
id|cp
op_assign
op_amp
id|chrdevs
(braket
id|i
)braket
suffix:semicolon
op_star
id|cp
suffix:semicolon
id|cp
op_assign
op_amp
(paren
op_star
id|cp
)paren
op_member_access_from_pointer
id|next
)paren
r_if
c_cond
(paren
(paren
op_star
id|cp
)paren
op_member_access_from_pointer
id|major
OG
id|major
op_logical_or
(paren
(paren
op_star
id|cp
)paren
op_member_access_from_pointer
id|major
op_eq
id|major
op_logical_and
(paren
op_star
id|cp
)paren
op_member_access_from_pointer
id|baseminor
op_ge
id|baseminor
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_star
id|cp
op_logical_and
(paren
op_star
id|cp
)paren
op_member_access_from_pointer
id|major
op_eq
id|major
op_logical_and
(paren
op_star
id|cp
)paren
op_member_access_from_pointer
id|baseminor
OL
id|baseminor
op_plus
id|minorct
)paren
(brace
id|ret
op_assign
op_minus
id|EBUSY
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|cd-&gt;next
op_assign
op_star
id|cp
suffix:semicolon
op_star
id|cp
op_assign
id|cd
suffix:semicolon
id|write_unlock_irq
c_func
(paren
op_amp
id|chrdevs_lock
)paren
suffix:semicolon
r_return
id|cd
suffix:semicolon
id|out
suffix:colon
id|write_unlock_irq
c_func
(paren
op_amp
id|chrdevs_lock
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|cd
)paren
suffix:semicolon
r_return
id|ERR_PTR
c_func
(paren
id|ret
)paren
suffix:semicolon
)brace
r_static
r_struct
id|char_device_struct
op_star
DECL|function|__unregister_chrdev_region
id|__unregister_chrdev_region
c_func
(paren
r_int
id|major
comma
r_int
id|baseminor
comma
r_int
id|minorct
)paren
(brace
r_struct
id|char_device_struct
op_star
id|cd
op_assign
l_int|NULL
comma
op_star
op_star
id|cp
suffix:semicolon
r_int
id|i
op_assign
id|major_to_index
c_func
(paren
id|major
)paren
suffix:semicolon
id|write_lock_irq
c_func
(paren
op_amp
id|chrdevs_lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|cp
op_assign
op_amp
id|chrdevs
(braket
id|i
)braket
suffix:semicolon
op_star
id|cp
suffix:semicolon
id|cp
op_assign
op_amp
(paren
op_star
id|cp
)paren
op_member_access_from_pointer
id|next
)paren
r_if
c_cond
(paren
(paren
op_star
id|cp
)paren
op_member_access_from_pointer
id|major
op_eq
id|major
op_logical_and
(paren
op_star
id|cp
)paren
op_member_access_from_pointer
id|baseminor
op_eq
id|baseminor
op_logical_and
(paren
op_star
id|cp
)paren
op_member_access_from_pointer
id|minorct
op_eq
id|minorct
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_star
id|cp
)paren
(brace
id|cd
op_assign
op_star
id|cp
suffix:semicolon
op_star
id|cp
op_assign
id|cd-&gt;next
suffix:semicolon
)brace
id|write_unlock_irq
c_func
(paren
op_amp
id|chrdevs_lock
)paren
suffix:semicolon
r_return
id|cd
suffix:semicolon
)brace
DECL|function|register_chrdev_region
r_int
id|register_chrdev_region
c_func
(paren
id|dev_t
id|from
comma
r_int
id|count
comma
r_const
r_char
op_star
id|name
)paren
(brace
r_struct
id|char_device_struct
op_star
id|cd
suffix:semicolon
id|dev_t
id|to
op_assign
id|from
op_plus
id|count
suffix:semicolon
id|dev_t
id|n
comma
id|next
suffix:semicolon
r_for
c_loop
(paren
id|n
op_assign
id|from
suffix:semicolon
id|n
OL
id|to
suffix:semicolon
id|n
op_assign
id|next
)paren
(brace
id|next
op_assign
id|MKDEV
c_func
(paren
id|MAJOR
c_func
(paren
id|n
)paren
op_plus
l_int|1
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|next
OG
id|to
)paren
id|next
op_assign
id|to
suffix:semicolon
id|cd
op_assign
id|__register_chrdev_region
c_func
(paren
id|MAJOR
c_func
(paren
id|n
)paren
comma
id|MINOR
c_func
(paren
id|n
)paren
comma
id|next
op_minus
id|n
comma
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|cd
)paren
)paren
r_goto
id|fail
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
id|fail
suffix:colon
id|to
op_assign
id|n
suffix:semicolon
r_for
c_loop
(paren
id|n
op_assign
id|from
suffix:semicolon
id|n
OL
id|to
suffix:semicolon
id|n
op_assign
id|next
)paren
(brace
id|next
op_assign
id|MKDEV
c_func
(paren
id|MAJOR
c_func
(paren
id|n
)paren
op_plus
l_int|1
comma
l_int|0
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|__unregister_chrdev_region
c_func
(paren
id|MAJOR
c_func
(paren
id|n
)paren
comma
id|MINOR
c_func
(paren
id|n
)paren
comma
id|next
op_minus
id|n
)paren
)paren
suffix:semicolon
)brace
r_return
id|PTR_ERR
c_func
(paren
id|cd
)paren
suffix:semicolon
)brace
DECL|function|alloc_chrdev_region
r_int
id|alloc_chrdev_region
c_func
(paren
id|dev_t
op_star
id|dev
comma
r_int
id|baseminor
comma
r_int
id|count
comma
r_const
r_char
op_star
id|name
)paren
(brace
r_struct
id|char_device_struct
op_star
id|cd
suffix:semicolon
id|cd
op_assign
id|__register_chrdev_region
c_func
(paren
l_int|0
comma
id|baseminor
comma
id|count
comma
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|cd
)paren
)paren
r_return
id|PTR_ERR
c_func
(paren
id|cd
)paren
suffix:semicolon
op_star
id|dev
op_assign
id|MKDEV
c_func
(paren
id|cd-&gt;major
comma
id|cd-&gt;baseminor
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|register_chrdev
r_int
id|register_chrdev
c_func
(paren
r_int
r_int
id|major
comma
r_const
r_char
op_star
id|name
comma
r_struct
id|file_operations
op_star
id|fops
)paren
(brace
r_struct
id|char_device_struct
op_star
id|cd
suffix:semicolon
r_struct
id|cdev
op_star
id|cdev
suffix:semicolon
r_char
op_star
id|s
suffix:semicolon
r_int
id|err
op_assign
op_minus
id|ENOMEM
suffix:semicolon
id|cd
op_assign
id|__register_chrdev_region
c_func
(paren
id|major
comma
l_int|0
comma
l_int|256
comma
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|cd
)paren
)paren
r_return
id|PTR_ERR
c_func
(paren
id|cd
)paren
suffix:semicolon
id|cdev
op_assign
id|cdev_alloc
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cdev
)paren
r_goto
id|out2
suffix:semicolon
id|cdev-&gt;owner
op_assign
id|fops-&gt;owner
suffix:semicolon
id|cdev-&gt;ops
op_assign
id|fops
suffix:semicolon
id|kobject_set_name
c_func
(paren
op_amp
id|cdev-&gt;kobj
comma
l_string|&quot;%s&quot;
comma
id|name
)paren
suffix:semicolon
r_for
c_loop
(paren
id|s
op_assign
id|strchr
c_func
(paren
id|kobject_name
c_func
(paren
op_amp
id|cdev-&gt;kobj
)paren
comma
l_char|&squot;/&squot;
)paren
suffix:semicolon
id|s
suffix:semicolon
id|s
op_assign
id|strchr
c_func
(paren
id|s
comma
l_char|&squot;/&squot;
)paren
)paren
op_star
id|s
op_assign
l_char|&squot;!&squot;
suffix:semicolon
id|err
op_assign
id|cdev_add
c_func
(paren
id|cdev
comma
id|MKDEV
c_func
(paren
id|cd-&gt;major
comma
l_int|0
)paren
comma
l_int|256
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|out
suffix:semicolon
id|cd-&gt;cdev
op_assign
id|cdev
suffix:semicolon
r_return
id|major
ques
c_cond
l_int|0
suffix:colon
id|cd-&gt;major
suffix:semicolon
id|out
suffix:colon
id|kobject_put
c_func
(paren
op_amp
id|cdev-&gt;kobj
)paren
suffix:semicolon
id|out2
suffix:colon
id|kfree
c_func
(paren
id|__unregister_chrdev_region
c_func
(paren
id|cd-&gt;major
comma
l_int|0
comma
l_int|256
)paren
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|unregister_chrdev_region
r_void
id|unregister_chrdev_region
c_func
(paren
id|dev_t
id|from
comma
r_int
id|count
)paren
(brace
id|dev_t
id|to
op_assign
id|from
op_plus
id|count
suffix:semicolon
id|dev_t
id|n
comma
id|next
suffix:semicolon
r_for
c_loop
(paren
id|n
op_assign
id|from
suffix:semicolon
id|n
OL
id|to
suffix:semicolon
id|n
op_assign
id|next
)paren
(brace
id|next
op_assign
id|MKDEV
c_func
(paren
id|MAJOR
c_func
(paren
id|n
)paren
op_plus
l_int|1
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|next
OG
id|to
)paren
id|next
op_assign
id|to
suffix:semicolon
id|kfree
c_func
(paren
id|__unregister_chrdev_region
c_func
(paren
id|MAJOR
c_func
(paren
id|n
)paren
comma
id|MINOR
c_func
(paren
id|n
)paren
comma
id|next
op_minus
id|n
)paren
)paren
suffix:semicolon
)brace
)brace
DECL|function|unregister_chrdev
r_int
id|unregister_chrdev
c_func
(paren
r_int
r_int
id|major
comma
r_const
r_char
op_star
id|name
)paren
(brace
r_struct
id|char_device_struct
op_star
id|cd
suffix:semicolon
id|cd
op_assign
id|__unregister_chrdev_region
c_func
(paren
id|major
comma
l_int|0
comma
l_int|256
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cd
op_logical_and
id|cd-&gt;cdev
)paren
id|cdev_del
c_func
(paren
id|cd-&gt;cdev
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|cd
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
id|DEFINE_SPINLOCK
c_func
(paren
id|cdev_lock
)paren
suffix:semicolon
DECL|function|cdev_get
r_static
r_struct
id|kobject
op_star
id|cdev_get
c_func
(paren
r_struct
id|cdev
op_star
id|p
)paren
(brace
r_struct
id|module
op_star
id|owner
op_assign
id|p-&gt;owner
suffix:semicolon
r_struct
id|kobject
op_star
id|kobj
suffix:semicolon
r_if
c_cond
(paren
id|owner
op_logical_and
op_logical_neg
id|try_module_get
c_func
(paren
id|owner
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
id|kobj
op_assign
id|kobject_get
c_func
(paren
op_amp
id|p-&gt;kobj
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|kobj
)paren
id|module_put
c_func
(paren
id|owner
)paren
suffix:semicolon
r_return
id|kobj
suffix:semicolon
)brace
DECL|function|cdev_put
r_void
id|cdev_put
c_func
(paren
r_struct
id|cdev
op_star
id|p
)paren
(brace
r_if
c_cond
(paren
id|p
)paren
(brace
id|kobject_put
c_func
(paren
op_amp
id|p-&gt;kobj
)paren
suffix:semicolon
id|module_put
c_func
(paren
id|p-&gt;owner
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Called every time a character special file is opened&n; */
DECL|function|chrdev_open
r_int
id|chrdev_open
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
id|cdev
op_star
id|p
suffix:semicolon
r_struct
id|cdev
op_star
r_new
op_assign
l_int|NULL
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|cdev_lock
)paren
suffix:semicolon
id|p
op_assign
id|inode-&gt;i_cdev
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
)paren
(brace
r_struct
id|kobject
op_star
id|kobj
suffix:semicolon
r_int
id|idx
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|cdev_lock
)paren
suffix:semicolon
id|kobj
op_assign
id|kobj_lookup
c_func
(paren
id|cdev_map
comma
id|inode-&gt;i_rdev
comma
op_amp
id|idx
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|kobj
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
r_new
op_assign
id|container_of
c_func
(paren
id|kobj
comma
r_struct
id|cdev
comma
id|kobj
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|cdev_lock
)paren
suffix:semicolon
id|p
op_assign
id|inode-&gt;i_cdev
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
)paren
(brace
id|inode-&gt;i_cdev
op_assign
id|p
op_assign
r_new
suffix:semicolon
id|inode-&gt;i_cindex
op_assign
id|idx
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|inode-&gt;i_devices
comma
op_amp
id|p-&gt;list
)paren
suffix:semicolon
r_new
op_assign
l_int|NULL
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|cdev_get
c_func
(paren
id|p
)paren
)paren
id|ret
op_assign
op_minus
id|ENXIO
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|cdev_get
c_func
(paren
id|p
)paren
)paren
id|ret
op_assign
op_minus
id|ENXIO
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|cdev_lock
)paren
suffix:semicolon
id|cdev_put
c_func
(paren
r_new
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_return
id|ret
suffix:semicolon
id|filp-&gt;f_op
op_assign
id|fops_get
c_func
(paren
id|p-&gt;ops
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|filp-&gt;f_op
)paren
(brace
id|cdev_put
c_func
(paren
id|p
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
r_if
c_cond
(paren
id|filp-&gt;f_op-&gt;open
)paren
(brace
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|ret
op_assign
id|filp-&gt;f_op
op_member_access_from_pointer
id|open
c_func
(paren
id|inode
comma
id|filp
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ret
)paren
id|cdev_put
c_func
(paren
id|p
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|cd_forget
r_void
id|cd_forget
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|cdev_lock
)paren
suffix:semicolon
id|list_del_init
c_func
(paren
op_amp
id|inode-&gt;i_devices
)paren
suffix:semicolon
id|inode-&gt;i_cdev
op_assign
l_int|NULL
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|cdev_lock
)paren
suffix:semicolon
)brace
DECL|function|cdev_purge
r_void
id|cdev_purge
c_func
(paren
r_struct
id|cdev
op_star
id|cdev
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|cdev_lock
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|cdev-&gt;list
)paren
)paren
(brace
r_struct
id|inode
op_star
id|inode
suffix:semicolon
id|inode
op_assign
id|container_of
c_func
(paren
id|cdev-&gt;list.next
comma
r_struct
id|inode
comma
id|i_devices
)paren
suffix:semicolon
id|list_del_init
c_func
(paren
op_amp
id|inode-&gt;i_devices
)paren
suffix:semicolon
id|inode-&gt;i_cdev
op_assign
l_int|NULL
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|cdev_lock
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Dummy default file-operations: the only thing this does&n; * is contain the open that then fills in the correct operations&n; * depending on the special file...&n; */
DECL|variable|def_chr_fops
r_struct
id|file_operations
id|def_chr_fops
op_assign
(brace
dot
id|open
op_assign
id|chrdev_open
comma
)brace
suffix:semicolon
DECL|function|exact_match
r_static
r_struct
id|kobject
op_star
id|exact_match
c_func
(paren
id|dev_t
id|dev
comma
r_int
op_star
id|part
comma
r_void
op_star
id|data
)paren
(brace
r_struct
id|cdev
op_star
id|p
op_assign
id|data
suffix:semicolon
r_return
op_amp
id|p-&gt;kobj
suffix:semicolon
)brace
DECL|function|exact_lock
r_static
r_int
id|exact_lock
c_func
(paren
id|dev_t
id|dev
comma
r_void
op_star
id|data
)paren
(brace
r_struct
id|cdev
op_star
id|p
op_assign
id|data
suffix:semicolon
r_return
id|cdev_get
c_func
(paren
id|p
)paren
ques
c_cond
l_int|0
suffix:colon
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|cdev_add
r_int
id|cdev_add
c_func
(paren
r_struct
id|cdev
op_star
id|p
comma
id|dev_t
id|dev
comma
r_int
id|count
)paren
(brace
id|p-&gt;dev
op_assign
id|dev
suffix:semicolon
id|p-&gt;count
op_assign
id|count
suffix:semicolon
r_return
id|kobj_map
c_func
(paren
id|cdev_map
comma
id|dev
comma
id|count
comma
l_int|NULL
comma
id|exact_match
comma
id|exact_lock
comma
id|p
)paren
suffix:semicolon
)brace
DECL|function|cdev_unmap
r_static
r_void
id|cdev_unmap
c_func
(paren
id|dev_t
id|dev
comma
r_int
id|count
)paren
(brace
id|kobj_unmap
c_func
(paren
id|cdev_map
comma
id|dev
comma
id|count
)paren
suffix:semicolon
)brace
DECL|function|cdev_del
r_void
id|cdev_del
c_func
(paren
r_struct
id|cdev
op_star
id|p
)paren
(brace
id|cdev_unmap
c_func
(paren
id|p-&gt;dev
comma
id|p-&gt;count
)paren
suffix:semicolon
id|kobject_put
c_func
(paren
op_amp
id|p-&gt;kobj
)paren
suffix:semicolon
)brace
r_static
id|decl_subsys
c_func
(paren
id|cdev
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
DECL|function|cdev_default_release
r_static
r_void
id|cdev_default_release
c_func
(paren
r_struct
id|kobject
op_star
id|kobj
)paren
(brace
r_struct
id|cdev
op_star
id|p
op_assign
id|container_of
c_func
(paren
id|kobj
comma
r_struct
id|cdev
comma
id|kobj
)paren
suffix:semicolon
id|cdev_purge
c_func
(paren
id|p
)paren
suffix:semicolon
)brace
DECL|function|cdev_dynamic_release
r_static
r_void
id|cdev_dynamic_release
c_func
(paren
r_struct
id|kobject
op_star
id|kobj
)paren
(brace
r_struct
id|cdev
op_star
id|p
op_assign
id|container_of
c_func
(paren
id|kobj
comma
r_struct
id|cdev
comma
id|kobj
)paren
suffix:semicolon
id|cdev_purge
c_func
(paren
id|p
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|p
)paren
suffix:semicolon
)brace
DECL|variable|ktype_cdev_default
r_static
r_struct
id|kobj_type
id|ktype_cdev_default
op_assign
(brace
dot
id|release
op_assign
id|cdev_default_release
comma
)brace
suffix:semicolon
DECL|variable|ktype_cdev_dynamic
r_static
r_struct
id|kobj_type
id|ktype_cdev_dynamic
op_assign
(brace
dot
id|release
op_assign
id|cdev_dynamic_release
comma
)brace
suffix:semicolon
DECL|function|cdev_alloc
r_struct
id|cdev
op_star
id|cdev_alloc
c_func
(paren
r_void
)paren
(brace
r_struct
id|cdev
op_star
id|p
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|cdev
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p
)paren
(brace
id|memset
c_func
(paren
id|p
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|cdev
)paren
)paren
suffix:semicolon
id|p-&gt;kobj.ktype
op_assign
op_amp
id|ktype_cdev_dynamic
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|p-&gt;list
)paren
suffix:semicolon
id|kobject_init
c_func
(paren
op_amp
id|p-&gt;kobj
)paren
suffix:semicolon
)brace
r_return
id|p
suffix:semicolon
)brace
DECL|function|cdev_init
r_void
id|cdev_init
c_func
(paren
r_struct
id|cdev
op_star
id|cdev
comma
r_struct
id|file_operations
op_star
id|fops
)paren
(brace
id|memset
c_func
(paren
id|cdev
comma
l_int|0
comma
r_sizeof
op_star
id|cdev
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|cdev-&gt;list
)paren
suffix:semicolon
id|cdev-&gt;kobj.ktype
op_assign
op_amp
id|ktype_cdev_default
suffix:semicolon
id|kobject_init
c_func
(paren
op_amp
id|cdev-&gt;kobj
)paren
suffix:semicolon
id|cdev-&gt;ops
op_assign
id|fops
suffix:semicolon
)brace
DECL|function|base_probe
r_static
r_struct
id|kobject
op_star
id|base_probe
c_func
(paren
id|dev_t
id|dev
comma
r_int
op_star
id|part
comma
r_void
op_star
id|data
)paren
(brace
r_if
c_cond
(paren
id|request_module
c_func
(paren
l_string|&quot;char-major-%d-%d&quot;
comma
id|MAJOR
c_func
(paren
id|dev
)paren
comma
id|MINOR
c_func
(paren
id|dev
)paren
)paren
OG
l_int|0
)paren
multiline_comment|/* Make old-style 2.4 aliases work */
id|request_module
c_func
(paren
l_string|&quot;char-major-%d&quot;
comma
id|MAJOR
c_func
(paren
id|dev
)paren
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|chrdev_init
r_void
id|__init
id|chrdev_init
c_func
(paren
r_void
)paren
(brace
multiline_comment|/*&n; * Keep cdev_subsys around because (and only because) the kobj_map code&n; * depends on the rwsem it contains.  We don&squot;t make it public in sysfs,&n; * however.&n; */
id|subsystem_init
c_func
(paren
op_amp
id|cdev_subsys
)paren
suffix:semicolon
id|cdev_map
op_assign
id|kobj_map_init
c_func
(paren
id|base_probe
comma
op_amp
id|cdev_subsys
)paren
suffix:semicolon
)brace
multiline_comment|/* Let modules do char dev stuff */
DECL|variable|register_chrdev_region
id|EXPORT_SYMBOL
c_func
(paren
id|register_chrdev_region
)paren
suffix:semicolon
DECL|variable|unregister_chrdev_region
id|EXPORT_SYMBOL
c_func
(paren
id|unregister_chrdev_region
)paren
suffix:semicolon
DECL|variable|alloc_chrdev_region
id|EXPORT_SYMBOL
c_func
(paren
id|alloc_chrdev_region
)paren
suffix:semicolon
DECL|variable|cdev_init
id|EXPORT_SYMBOL
c_func
(paren
id|cdev_init
)paren
suffix:semicolon
DECL|variable|cdev_alloc
id|EXPORT_SYMBOL
c_func
(paren
id|cdev_alloc
)paren
suffix:semicolon
DECL|variable|cdev_del
id|EXPORT_SYMBOL
c_func
(paren
id|cdev_del
)paren
suffix:semicolon
DECL|variable|cdev_add
id|EXPORT_SYMBOL
c_func
(paren
id|cdev_add
)paren
suffix:semicolon
DECL|variable|register_chrdev
id|EXPORT_SYMBOL
c_func
(paren
id|register_chrdev
)paren
suffix:semicolon
DECL|variable|unregister_chrdev
id|EXPORT_SYMBOL
c_func
(paren
id|unregister_chrdev
)paren
suffix:semicolon
eof
