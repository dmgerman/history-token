multiline_comment|/*&n; * kobject.c - library routines for handling generic kernel objects&n; *&n; * Copyright (c) 2002-2003 Patrick Mochel &lt;mochel@osdl.org&gt;&n; *&n; */
DECL|macro|DEBUG
macro_line|#undef DEBUG
macro_line|#include &lt;linux/kobject.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
multiline_comment|/* This lock can be removed entirely when the sysfs_init() code is cleaned up&n; * to not try to reference itself before it is initialized. */
DECL|variable|kobj_lock
r_static
id|spinlock_t
id|kobj_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
multiline_comment|/**&n; *&t;populate_dir - populate directory with attributes.&n; *&t;@kobj:&t;object we&squot;re working on.&n; *&n; *&t;Most subsystems have a set of default attributes that &n; *&t;are associated with an object that registers with them.&n; *&t;This is a helper called during object registration that &n; *&t;loops through the default attributes of the subsystem &n; *&t;and creates attributes files for them in sysfs.&n; *&n; */
DECL|function|populate_dir
r_static
r_int
id|populate_dir
c_func
(paren
r_struct
id|kobject
op_star
id|kobj
)paren
(brace
r_struct
id|kobj_type
op_star
id|t
op_assign
id|get_ktype
c_func
(paren
id|kobj
)paren
suffix:semicolon
r_struct
id|attribute
op_star
id|attr
suffix:semicolon
r_int
id|error
op_assign
l_int|0
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|t
op_logical_and
id|t-&gt;default_attrs
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
(paren
id|attr
op_assign
id|t-&gt;default_attrs
(braket
id|i
)braket
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
id|error
op_assign
id|sysfs_create_file
c_func
(paren
id|kobj
comma
id|attr
)paren
)paren
)paren
r_break
suffix:semicolon
)brace
)brace
r_return
id|error
suffix:semicolon
)brace
DECL|function|create_dir
r_static
r_int
id|create_dir
c_func
(paren
r_struct
id|kobject
op_star
id|kobj
)paren
(brace
r_int
id|error
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|strlen
c_func
(paren
id|kobj-&gt;name
)paren
)paren
(brace
id|error
op_assign
id|sysfs_create_dir
c_func
(paren
id|kobj
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
(brace
r_if
c_cond
(paren
(paren
id|error
op_assign
id|populate_dir
c_func
(paren
id|kobj
)paren
)paren
)paren
id|sysfs_remove_dir
c_func
(paren
id|kobj
)paren
suffix:semicolon
)brace
)brace
r_return
id|error
suffix:semicolon
)brace
DECL|function|to_kobj
r_static
r_inline
r_struct
id|kobject
op_star
id|to_kobj
c_func
(paren
r_struct
id|list_head
op_star
id|entry
)paren
(brace
r_return
id|container_of
c_func
(paren
id|entry
comma
r_struct
id|kobject
comma
id|entry
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_HOTPLUG
DECL|function|get_kobj_path_length
r_static
r_int
id|get_kobj_path_length
c_func
(paren
r_struct
id|kset
op_star
id|kset
comma
r_struct
id|kobject
op_star
id|kobj
)paren
(brace
r_int
id|length
op_assign
l_int|1
suffix:semicolon
r_struct
id|kobject
op_star
id|parent
op_assign
id|kobj
suffix:semicolon
multiline_comment|/* walk up the ancestors until we hit the one pointing to the &n;&t; * root.&n;&t; * Add 1 to strlen for leading &squot;/&squot; of each level.&n;&t; */
r_do
(brace
id|length
op_add_assign
id|strlen
(paren
id|parent-&gt;name
)paren
op_plus
l_int|1
suffix:semicolon
id|parent
op_assign
id|parent-&gt;parent
suffix:semicolon
)brace
r_while
c_loop
(paren
id|parent
)paren
suffix:semicolon
r_return
id|length
suffix:semicolon
)brace
DECL|function|fill_kobj_path
r_static
r_void
id|fill_kobj_path
c_func
(paren
r_struct
id|kset
op_star
id|kset
comma
r_struct
id|kobject
op_star
id|kobj
comma
r_char
op_star
id|path
comma
r_int
id|length
)paren
(brace
r_struct
id|kobject
op_star
id|parent
suffix:semicolon
op_decrement
id|length
suffix:semicolon
r_for
c_loop
(paren
id|parent
op_assign
id|kobj
suffix:semicolon
id|parent
suffix:semicolon
id|parent
op_assign
id|parent-&gt;parent
)paren
(brace
r_int
id|cur
op_assign
id|strlen
(paren
id|parent-&gt;name
)paren
suffix:semicolon
multiline_comment|/* back up enough to print this name with &squot;/&squot; */
id|length
op_sub_assign
id|cur
suffix:semicolon
id|strncpy
(paren
id|path
op_plus
id|length
comma
id|parent-&gt;name
comma
id|cur
)paren
suffix:semicolon
op_star
(paren
id|path
op_plus
op_decrement
id|length
)paren
op_assign
l_char|&squot;/&squot;
suffix:semicolon
)brace
id|pr_debug
c_func
(paren
l_string|&quot;%s: path = &squot;%s&squot;&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|path
)paren
suffix:semicolon
)brace
DECL|macro|BUFFER_SIZE
mdefine_line|#define BUFFER_SIZE&t;1024&t;/* should be enough memory for the env */
DECL|macro|NUM_ENVP
mdefine_line|#define NUM_ENVP&t;32&t;/* number of env pointers */
DECL|function|kset_hotplug
r_static
r_void
id|kset_hotplug
c_func
(paren
r_const
r_char
op_star
id|action
comma
r_struct
id|kset
op_star
id|kset
comma
r_struct
id|kobject
op_star
id|kobj
)paren
(brace
r_char
op_star
id|argv
(braket
l_int|3
)braket
suffix:semicolon
r_char
op_star
op_star
id|envp
op_assign
l_int|NULL
suffix:semicolon
r_char
op_star
id|buffer
op_assign
l_int|NULL
suffix:semicolon
r_char
op_star
id|scratch
suffix:semicolon
r_int
id|i
op_assign
l_int|0
suffix:semicolon
r_int
id|retval
suffix:semicolon
r_int
id|kobj_path_length
suffix:semicolon
r_char
op_star
id|kobj_path
op_assign
l_int|NULL
suffix:semicolon
r_char
op_star
id|name
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* If the kset has a filter operation, call it. If it returns&n;&t;   failure, no hotplug event is required. */
r_if
c_cond
(paren
id|kset-&gt;hotplug_ops-&gt;filter
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|kset-&gt;hotplug_ops
op_member_access_from_pointer
id|filter
c_func
(paren
id|kset
comma
id|kobj
)paren
)paren
r_return
suffix:semicolon
)brace
id|pr_debug
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hotplug_path
(braket
l_int|0
)braket
)paren
r_return
suffix:semicolon
id|envp
op_assign
id|kmalloc
c_func
(paren
id|NUM_ENVP
op_star
r_sizeof
(paren
r_char
op_star
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|envp
)paren
r_return
suffix:semicolon
id|memset
(paren
id|envp
comma
l_int|0x00
comma
id|NUM_ENVP
op_star
r_sizeof
(paren
r_char
op_star
)paren
)paren
suffix:semicolon
id|buffer
op_assign
id|kmalloc
c_func
(paren
id|BUFFER_SIZE
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buffer
)paren
r_goto
m_exit
suffix:semicolon
r_if
c_cond
(paren
id|kset-&gt;hotplug_ops-&gt;name
)paren
id|name
op_assign
id|kset-&gt;hotplug_ops
op_member_access_from_pointer
id|name
c_func
(paren
id|kset
comma
id|kobj
)paren
suffix:semicolon
r_if
c_cond
(paren
id|name
op_eq
l_int|NULL
)paren
id|name
op_assign
id|kset-&gt;kobj.name
suffix:semicolon
id|argv
(braket
l_int|0
)braket
op_assign
id|hotplug_path
suffix:semicolon
id|argv
(braket
l_int|1
)braket
op_assign
id|name
suffix:semicolon
id|argv
(braket
l_int|2
)braket
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* minimal command environment */
id|envp
(braket
id|i
op_increment
)braket
op_assign
l_string|&quot;HOME=/&quot;
suffix:semicolon
id|envp
(braket
id|i
op_increment
)braket
op_assign
l_string|&quot;PATH=/sbin:/bin:/usr/sbin:/usr/bin&quot;
suffix:semicolon
id|scratch
op_assign
id|buffer
suffix:semicolon
id|envp
(braket
id|i
op_increment
)braket
op_assign
id|scratch
suffix:semicolon
id|scratch
op_add_assign
id|sprintf
c_func
(paren
id|scratch
comma
l_string|&quot;ACTION=%s&quot;
comma
id|action
)paren
op_plus
l_int|1
suffix:semicolon
id|kobj_path_length
op_assign
id|get_kobj_path_length
(paren
id|kset
comma
id|kobj
)paren
suffix:semicolon
id|kobj_path
op_assign
id|kmalloc
(paren
id|kobj_path_length
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|kobj_path
)paren
r_goto
m_exit
suffix:semicolon
id|memset
(paren
id|kobj_path
comma
l_int|0x00
comma
id|kobj_path_length
)paren
suffix:semicolon
id|fill_kobj_path
(paren
id|kset
comma
id|kobj
comma
id|kobj_path
comma
id|kobj_path_length
)paren
suffix:semicolon
id|envp
(braket
id|i
op_increment
)braket
op_assign
id|scratch
suffix:semicolon
id|scratch
op_add_assign
id|sprintf
(paren
id|scratch
comma
l_string|&quot;DEVPATH=%s&quot;
comma
id|kobj_path
)paren
op_plus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|kset-&gt;hotplug_ops-&gt;hotplug
)paren
(brace
multiline_comment|/* have the kset specific function add its stuff */
id|retval
op_assign
id|kset-&gt;hotplug_ops-&gt;hotplug
(paren
id|kset
comma
id|kobj
comma
op_amp
id|envp
(braket
id|i
)braket
comma
id|NUM_ENVP
op_minus
id|i
comma
id|scratch
comma
id|BUFFER_SIZE
op_minus
(paren
id|scratch
op_minus
id|buffer
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
(brace
id|pr_debug
(paren
l_string|&quot;%s - hotplug() returned %d&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|retval
)paren
suffix:semicolon
r_goto
m_exit
suffix:semicolon
)brace
)brace
id|pr_debug
(paren
l_string|&quot;%s: %s %s %s %s %s %s&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|argv
(braket
l_int|0
)braket
comma
id|argv
(braket
l_int|1
)braket
comma
id|envp
(braket
l_int|0
)braket
comma
id|envp
(braket
l_int|1
)braket
comma
id|envp
(braket
l_int|2
)braket
comma
id|envp
(braket
l_int|3
)braket
)paren
suffix:semicolon
id|retval
op_assign
id|call_usermodehelper
(paren
id|argv
(braket
l_int|0
)braket
comma
id|argv
comma
id|envp
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
id|pr_debug
(paren
l_string|&quot;%s - call_usermodehelper returned %d&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|retval
)paren
suffix:semicolon
m_exit
suffix:colon
id|kfree
c_func
(paren
id|kobj_path
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|buffer
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|envp
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
macro_line|#else
DECL|function|kset_hotplug
r_static
r_void
id|kset_hotplug
c_func
(paren
r_const
r_char
op_star
id|action
comma
r_struct
id|kset
op_star
id|kset
comma
r_struct
id|kobject
op_star
id|kobj
)paren
(brace
r_return
suffix:semicolon
)brace
macro_line|#endif&t;/* CONFIG_HOTPLUG */
multiline_comment|/**&n; *&t;kobject_init - initialize object.&n; *&t;@kobj:&t;object in question.&n; */
DECL|function|kobject_init
r_void
id|kobject_init
c_func
(paren
r_struct
id|kobject
op_star
id|kobj
)paren
(brace
id|atomic_set
c_func
(paren
op_amp
id|kobj-&gt;refcount
comma
l_int|1
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|kobj-&gt;entry
)paren
suffix:semicolon
id|kobj-&gt;kset
op_assign
id|kset_get
c_func
(paren
id|kobj-&gt;kset
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;unlink - remove kobject from kset list.&n; *&t;@kobj:&t;kobject.&n; *&n; *&t;Remove the kobject from the kset list and decrement&n; *&t;its parent&squot;s refcount.&n; *&t;This is separated out, so we can use it in both &n; *&t;kobject_del() and kobject_add() on error.&n; */
DECL|function|unlink
r_static
r_void
id|unlink
c_func
(paren
r_struct
id|kobject
op_star
id|kobj
)paren
(brace
r_if
c_cond
(paren
id|kobj-&gt;kset
)paren
(brace
id|down_write
c_func
(paren
op_amp
id|kobj-&gt;kset-&gt;subsys-&gt;rwsem
)paren
suffix:semicolon
id|list_del_init
c_func
(paren
op_amp
id|kobj-&gt;entry
)paren
suffix:semicolon
id|up_write
c_func
(paren
op_amp
id|kobj-&gt;kset-&gt;subsys-&gt;rwsem
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|kobj-&gt;parent
)paren
id|kobject_put
c_func
(paren
id|kobj-&gt;parent
)paren
suffix:semicolon
id|kobject_put
c_func
(paren
id|kobj
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;kobject_add - add an object to the hierarchy.&n; *&t;@kobj:&t;object.&n; */
DECL|function|kobject_add
r_int
id|kobject_add
c_func
(paren
r_struct
id|kobject
op_star
id|kobj
)paren
(brace
r_int
id|error
op_assign
l_int|0
suffix:semicolon
r_struct
id|kobject
op_star
id|parent
suffix:semicolon
r_struct
id|kobject
op_star
id|top_kobj
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|kobj
op_assign
id|kobject_get
c_func
(paren
id|kobj
)paren
)paren
)paren
r_return
op_minus
id|ENOENT
suffix:semicolon
id|parent
op_assign
id|kobject_get
c_func
(paren
id|kobj-&gt;parent
)paren
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;kobject %s: registering. parent: %s, set: %s&bslash;n&quot;
comma
id|kobj-&gt;name
comma
id|parent
ques
c_cond
id|parent-&gt;name
suffix:colon
l_string|&quot;&lt;NULL&gt;&quot;
comma
id|kobj-&gt;kset
ques
c_cond
id|kobj-&gt;kset-&gt;kobj.name
suffix:colon
l_string|&quot;&lt;NULL&gt;&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|kobj-&gt;kset
)paren
(brace
id|down_write
c_func
(paren
op_amp
id|kobj-&gt;kset-&gt;subsys-&gt;rwsem
)paren
suffix:semicolon
r_if
c_cond
(paren
id|parent
)paren
id|list_add_tail
c_func
(paren
op_amp
id|kobj-&gt;entry
comma
op_amp
id|parent-&gt;entry
)paren
suffix:semicolon
r_else
(brace
id|list_add_tail
c_func
(paren
op_amp
id|kobj-&gt;entry
comma
op_amp
id|kobj-&gt;kset-&gt;list
)paren
suffix:semicolon
id|kobj-&gt;parent
op_assign
id|kobject_get
c_func
(paren
op_amp
id|kobj-&gt;kset-&gt;kobj
)paren
suffix:semicolon
)brace
id|up_write
c_func
(paren
op_amp
id|kobj-&gt;kset-&gt;subsys-&gt;rwsem
)paren
suffix:semicolon
)brace
id|error
op_assign
id|create_dir
c_func
(paren
id|kobj
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
id|unlink
c_func
(paren
id|kobj
)paren
suffix:semicolon
r_else
(brace
multiline_comment|/* If this kobj does not belong to a kset,&n;&t;&t;   try to find a parent that does. */
id|top_kobj
op_assign
id|kobj
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|top_kobj-&gt;kset
op_logical_and
id|top_kobj-&gt;parent
)paren
(brace
r_do
(brace
id|top_kobj
op_assign
id|top_kobj-&gt;parent
suffix:semicolon
)brace
r_while
c_loop
(paren
op_logical_neg
id|top_kobj-&gt;kset
op_logical_and
id|top_kobj-&gt;parent
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|top_kobj-&gt;kset
op_logical_and
id|top_kobj-&gt;kset-&gt;hotplug_ops
)paren
id|kset_hotplug
c_func
(paren
l_string|&quot;add&quot;
comma
id|top_kobj-&gt;kset
comma
id|kobj
)paren
suffix:semicolon
)brace
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;kobject_register - initialize and add an object.&n; *&t;@kobj:&t;object in question.&n; */
DECL|function|kobject_register
r_int
id|kobject_register
c_func
(paren
r_struct
id|kobject
op_star
id|kobj
)paren
(brace
r_int
id|error
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|kobj
)paren
(brace
id|kobject_init
c_func
(paren
id|kobj
)paren
suffix:semicolon
id|error
op_assign
id|kobject_add
c_func
(paren
id|kobj
)paren
suffix:semicolon
id|WARN_ON
c_func
(paren
id|error
)paren
suffix:semicolon
)brace
r_else
id|error
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;kobject_del - unlink kobject from hierarchy.&n; * &t;@kobj:&t;object.&n; */
DECL|function|kobject_del
r_void
id|kobject_del
c_func
(paren
r_struct
id|kobject
op_star
id|kobj
)paren
(brace
r_struct
id|kobject
op_star
id|top_kobj
suffix:semicolon
multiline_comment|/* If this kobj does not belong to a kset,&n;&t;   try to find a parent that does. */
id|top_kobj
op_assign
id|kobj
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|top_kobj-&gt;kset
op_logical_and
id|top_kobj-&gt;parent
)paren
(brace
r_do
(brace
id|top_kobj
op_assign
id|top_kobj-&gt;parent
suffix:semicolon
)brace
r_while
c_loop
(paren
op_logical_neg
id|top_kobj-&gt;kset
op_logical_and
id|top_kobj-&gt;parent
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|top_kobj-&gt;kset
op_logical_and
id|top_kobj-&gt;kset-&gt;hotplug_ops
)paren
id|kset_hotplug
c_func
(paren
l_string|&quot;remove&quot;
comma
id|top_kobj-&gt;kset
comma
id|kobj
)paren
suffix:semicolon
id|sysfs_remove_dir
c_func
(paren
id|kobj
)paren
suffix:semicolon
id|unlink
c_func
(paren
id|kobj
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;kobject_unregister - remove object from hierarchy and decrement refcount.&n; *&t;@kobj:&t;object going away.&n; */
DECL|function|kobject_unregister
r_void
id|kobject_unregister
c_func
(paren
r_struct
id|kobject
op_star
id|kobj
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;kobject %s: unregistering&bslash;n&quot;
comma
id|kobj-&gt;name
)paren
suffix:semicolon
id|kobject_del
c_func
(paren
id|kobj
)paren
suffix:semicolon
id|kobject_put
c_func
(paren
id|kobj
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;kobject_get - increment refcount for object.&n; *&t;@kobj:&t;object.&n; */
DECL|function|kobject_get
r_struct
id|kobject
op_star
id|kobject_get
c_func
(paren
r_struct
id|kobject
op_star
id|kobj
)paren
(brace
r_struct
id|kobject
op_star
id|ret
op_assign
id|kobj
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|kobj_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|kobj
op_logical_and
id|atomic_read
c_func
(paren
op_amp
id|kobj-&gt;refcount
)paren
OG
l_int|0
)paren
id|atomic_inc
c_func
(paren
op_amp
id|kobj-&gt;refcount
)paren
suffix:semicolon
r_else
id|ret
op_assign
l_int|NULL
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|kobj_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;kobject_cleanup - free kobject resources. &n; *&t;@kobj:&t;object.&n; */
DECL|function|kobject_cleanup
r_void
id|kobject_cleanup
c_func
(paren
r_struct
id|kobject
op_star
id|kobj
)paren
(brace
r_struct
id|kobj_type
op_star
id|t
op_assign
id|get_ktype
c_func
(paren
id|kobj
)paren
suffix:semicolon
r_struct
id|kset
op_star
id|s
op_assign
id|kobj-&gt;kset
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;kobject %s: cleaning up&bslash;n&quot;
comma
id|kobj-&gt;name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|t
op_logical_and
id|t-&gt;release
)paren
id|t
op_member_access_from_pointer
id|release
c_func
(paren
id|kobj
)paren
suffix:semicolon
r_if
c_cond
(paren
id|s
)paren
id|kset_put
c_func
(paren
id|s
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;kobject_put - decrement refcount for object.&n; *&t;@kobj:&t;object.&n; *&n; *&t;Decrement the refcount, and if 0, call kobject_cleanup().&n; */
DECL|function|kobject_put
r_void
id|kobject_put
c_func
(paren
r_struct
id|kobject
op_star
id|kobj
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|atomic_dec_and_lock
c_func
(paren
op_amp
id|kobj-&gt;refcount
comma
op_amp
id|kobj_lock
)paren
)paren
(brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|kobj_lock
comma
id|flags
)paren
suffix:semicolon
id|kobject_cleanup
c_func
(paren
id|kobj
)paren
suffix:semicolon
)brace
r_else
(brace
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/**&n; *&t;kset_init - initialize a kset for use&n; *&t;@k:&t;kset &n; */
DECL|function|kset_init
r_void
id|kset_init
c_func
(paren
r_struct
id|kset
op_star
id|k
)paren
(brace
id|kobject_init
c_func
(paren
op_amp
id|k-&gt;kobj
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|k-&gt;list
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;kset_add - add a kset object to the hierarchy.&n; *&t;@k:&t;kset.&n; *&n; *&t;Simply, this adds the kset&squot;s embedded kobject to the &n; *&t;hierarchy. &n; *&t;We also try to make sure that the kset&squot;s embedded kobject&n; *&t;has a parent before it is added. We only care if the embedded&n; *&t;kobject is not part of a kset itself, since kobject_add()&n; *&t;assigns a parent in that case. &n; *&t;If that is the case, and the kset has a controlling subsystem,&n; *&t;then we set the kset&squot;s parent to be said subsystem. &n; */
DECL|function|kset_add
r_int
id|kset_add
c_func
(paren
r_struct
id|kset
op_star
id|k
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|k-&gt;kobj.parent
op_logical_and
op_logical_neg
id|k-&gt;kobj.kset
op_logical_and
id|k-&gt;subsys
)paren
id|k-&gt;kobj.parent
op_assign
op_amp
id|k-&gt;subsys-&gt;kset.kobj
suffix:semicolon
r_return
id|kobject_add
c_func
(paren
op_amp
id|k-&gt;kobj
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;kset_register - initialize and add a kset.&n; *&t;@k:&t;kset.&n; */
DECL|function|kset_register
r_int
id|kset_register
c_func
(paren
r_struct
id|kset
op_star
id|k
)paren
(brace
id|kset_init
c_func
(paren
id|k
)paren
suffix:semicolon
r_return
id|kset_add
c_func
(paren
id|k
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;kset_unregister - remove a kset.&n; *&t;@k:&t;kset.&n; */
DECL|function|kset_unregister
r_void
id|kset_unregister
c_func
(paren
r_struct
id|kset
op_star
id|k
)paren
(brace
id|kobject_unregister
c_func
(paren
op_amp
id|k-&gt;kobj
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;kset_find_obj - search for object in kset.&n; *&t;@kset:&t;kset we&squot;re looking in.&n; *&t;@name:&t;object&squot;s name.&n; *&n; *&t;Lock kset via @kset-&gt;subsys, and iterate over @kset-&gt;list,&n; *&t;looking for a matching kobject. Return object if found.&n; */
DECL|function|kset_find_obj
r_struct
id|kobject
op_star
id|kset_find_obj
c_func
(paren
r_struct
id|kset
op_star
id|kset
comma
r_const
r_char
op_star
id|name
)paren
(brace
r_struct
id|list_head
op_star
id|entry
suffix:semicolon
r_struct
id|kobject
op_star
id|ret
op_assign
l_int|NULL
suffix:semicolon
id|down_read
c_func
(paren
op_amp
id|kset-&gt;subsys-&gt;rwsem
)paren
suffix:semicolon
id|list_for_each
c_func
(paren
id|entry
comma
op_amp
id|kset-&gt;list
)paren
(brace
r_struct
id|kobject
op_star
id|k
op_assign
id|to_kobj
c_func
(paren
id|entry
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|k-&gt;name
comma
id|name
)paren
)paren
(brace
id|ret
op_assign
id|k
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|up_read
c_func
(paren
op_amp
id|kset-&gt;subsys-&gt;rwsem
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|subsystem_init
r_void
id|subsystem_init
c_func
(paren
r_struct
id|subsystem
op_star
id|s
)paren
(brace
id|init_rwsem
c_func
(paren
op_amp
id|s-&gt;rwsem
)paren
suffix:semicolon
id|kset_init
c_func
(paren
op_amp
id|s-&gt;kset
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;subsystem_register - register a subsystem.&n; *&t;@s:&t;the subsystem we&squot;re registering.&n; *&n; *&t;Once we register the subsystem, we want to make sure that &n; *&t;the kset points back to this subsystem for correct usage of &n; *&t;the rwsem. &n; */
DECL|function|subsystem_register
r_int
id|subsystem_register
c_func
(paren
r_struct
id|subsystem
op_star
id|s
)paren
(brace
r_int
id|error
suffix:semicolon
id|subsystem_init
c_func
(paren
id|s
)paren
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;subsystem %s: registering&bslash;n&quot;
comma
id|s-&gt;kset.kobj.name
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|error
op_assign
id|kset_add
c_func
(paren
op_amp
id|s-&gt;kset
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|s-&gt;kset.subsys
)paren
id|s-&gt;kset.subsys
op_assign
id|s
suffix:semicolon
)brace
r_return
id|error
suffix:semicolon
)brace
DECL|function|subsystem_unregister
r_void
id|subsystem_unregister
c_func
(paren
r_struct
id|subsystem
op_star
id|s
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;subsystem %s: unregistering&bslash;n&quot;
comma
id|s-&gt;kset.kobj.name
)paren
suffix:semicolon
id|kset_unregister
c_func
(paren
op_amp
id|s-&gt;kset
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;subsystem_create_file - export sysfs attribute file.&n; *&t;@s:&t;subsystem.&n; *&t;@a:&t;subsystem attribute descriptor.&n; */
DECL|function|subsys_create_file
r_int
id|subsys_create_file
c_func
(paren
r_struct
id|subsystem
op_star
id|s
comma
r_struct
id|subsys_attribute
op_star
id|a
)paren
(brace
r_int
id|error
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|subsys_get
c_func
(paren
id|s
)paren
)paren
(brace
id|error
op_assign
id|sysfs_create_file
c_func
(paren
op_amp
id|s-&gt;kset.kobj
comma
op_amp
id|a-&gt;attr
)paren
suffix:semicolon
id|subsys_put
c_func
(paren
id|s
)paren
suffix:semicolon
)brace
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;subsystem_remove_file - remove sysfs attribute file.&n; *&t;@s:&t;subsystem.&n; *&t;@a:&t;attribute desciptor.&n; */
DECL|function|subsys_remove_file
r_void
id|subsys_remove_file
c_func
(paren
r_struct
id|subsystem
op_star
id|s
comma
r_struct
id|subsys_attribute
op_star
id|a
)paren
(brace
r_if
c_cond
(paren
id|subsys_get
c_func
(paren
id|s
)paren
)paren
(brace
id|sysfs_remove_file
c_func
(paren
op_amp
id|s-&gt;kset.kobj
comma
op_amp
id|a-&gt;attr
)paren
suffix:semicolon
id|subsys_put
c_func
(paren
id|s
)paren
suffix:semicolon
)brace
)brace
DECL|variable|kobject_init
id|EXPORT_SYMBOL
c_func
(paren
id|kobject_init
)paren
suffix:semicolon
DECL|variable|kobject_register
id|EXPORT_SYMBOL
c_func
(paren
id|kobject_register
)paren
suffix:semicolon
DECL|variable|kobject_unregister
id|EXPORT_SYMBOL
c_func
(paren
id|kobject_unregister
)paren
suffix:semicolon
DECL|variable|kobject_get
id|EXPORT_SYMBOL
c_func
(paren
id|kobject_get
)paren
suffix:semicolon
DECL|variable|kobject_put
id|EXPORT_SYMBOL
c_func
(paren
id|kobject_put
)paren
suffix:semicolon
DECL|variable|kset_find_obj
id|EXPORT_SYMBOL
c_func
(paren
id|kset_find_obj
)paren
suffix:semicolon
DECL|variable|subsystem_init
id|EXPORT_SYMBOL
c_func
(paren
id|subsystem_init
)paren
suffix:semicolon
DECL|variable|subsystem_register
id|EXPORT_SYMBOL
c_func
(paren
id|subsystem_register
)paren
suffix:semicolon
DECL|variable|subsystem_unregister
id|EXPORT_SYMBOL
c_func
(paren
id|subsystem_unregister
)paren
suffix:semicolon
DECL|variable|subsys_create_file
id|EXPORT_SYMBOL
c_func
(paren
id|subsys_create_file
)paren
suffix:semicolon
DECL|variable|subsys_remove_file
id|EXPORT_SYMBOL
c_func
(paren
id|subsys_remove_file
)paren
suffix:semicolon
eof
