multiline_comment|/*&n; * kernel/ksysfs.c - sysfs attributes in /sys/kernel, which&n; * &t;&t;     are not related to any other subsystem&n; *&n; * Copyright (C) 2004 Kay Sievers &lt;kay.sievers@vrfy.org&gt;&n; * &n; * This file is release under the GPLv2&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kobject.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/sysfs.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
DECL|macro|KERNEL_ATTR_RO
mdefine_line|#define KERNEL_ATTR_RO(_name) &bslash;&n;static struct subsys_attribute _name##_attr = __ATTR_RO(_name)
DECL|macro|KERNEL_ATTR_RW
mdefine_line|#define KERNEL_ATTR_RW(_name) &bslash;&n;static struct subsys_attribute _name##_attr = &bslash;&n;&t;__ATTR(_name, 0644, _name##_show, _name##_store)
macro_line|#ifdef CONFIG_HOTPLUG
DECL|function|hotplug_seqnum_show
r_static
id|ssize_t
id|hotplug_seqnum_show
c_func
(paren
r_struct
id|subsystem
op_star
id|subsys
comma
r_char
op_star
id|page
)paren
(brace
r_return
id|sprintf
c_func
(paren
id|page
comma
l_string|&quot;%llu&bslash;n&quot;
comma
(paren
r_int
r_int
r_int
)paren
id|hotplug_seqnum
)paren
suffix:semicolon
)brace
DECL|variable|hotplug_seqnum
id|KERNEL_ATTR_RO
c_func
(paren
id|hotplug_seqnum
)paren
suffix:semicolon
macro_line|#endif
r_static
id|decl_subsys
c_func
(paren
id|kernel
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
DECL|variable|kernel_attrs
r_static
r_struct
id|attribute
op_star
id|kernel_attrs
(braket
)braket
op_assign
(brace
macro_line|#ifdef CONFIG_HOTPLUG
op_amp
id|hotplug_seqnum_attr.attr
comma
macro_line|#endif
l_int|NULL
)brace
suffix:semicolon
DECL|variable|kernel_attr_group
r_static
r_struct
id|attribute_group
id|kernel_attr_group
op_assign
(brace
dot
id|attrs
op_assign
id|kernel_attrs
comma
)brace
suffix:semicolon
DECL|function|ksysfs_init
r_static
r_int
id|__init
id|ksysfs_init
c_func
(paren
r_void
)paren
(brace
r_int
id|error
op_assign
id|subsystem_register
c_func
(paren
op_amp
id|kernel_subsys
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
id|error
op_assign
id|sysfs_create_group
c_func
(paren
op_amp
id|kernel_subsys.kset.kobj
comma
op_amp
id|kernel_attr_group
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|variable|ksysfs_init
id|core_initcall
c_func
(paren
id|ksysfs_init
)paren
suffix:semicolon
eof
