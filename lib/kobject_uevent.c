multiline_comment|/*&n; * kernel userspace event delivery&n; *&n; * Copyright (C) 2004 Red Hat, Inc.  All rights reserved.&n; * Copyright (C) 2004 Novell, Inc.  All rights reserved.&n; * Copyright (C) 2004 IBM, Inc. All rights reserved.&n; *&n; * Licensed under the GNU GPL v2.&n; *&n; * Authors:&n; *&t;Robert Love&t;&t;&lt;rml@novell.com&gt;&n; *&t;Kay Sievers&t;&t;&lt;kay.sievers@vrfy.org&gt;&n; *&t;Arjan van de Ven&t;&lt;arjanv@redhat.com&gt;&n; *&t;Greg Kroah-Hartman&t;&lt;greg@kroah.com&gt;&n; */
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/netlink.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/kobject_uevent.h&gt;
macro_line|#include &lt;linux/kobject.h&gt;
macro_line|#include &lt;net/sock.h&gt;
multiline_comment|/* &n; * These must match up with the values for enum kobject_action&n; * as found in include/linux/kobject_uevent.h&n; */
DECL|variable|actions
r_static
r_char
op_star
id|actions
(braket
)braket
op_assign
(brace
l_string|&quot;add&quot;
comma
multiline_comment|/* 0x00 */
l_string|&quot;remove&quot;
comma
multiline_comment|/* 0x01 */
l_string|&quot;change&quot;
comma
multiline_comment|/* 0x02 */
l_string|&quot;mount&quot;
comma
multiline_comment|/* 0x03 */
l_string|&quot;umount&quot;
comma
multiline_comment|/* 0x04 */
)brace
suffix:semicolon
DECL|function|action_to_string
r_static
r_char
op_star
id|action_to_string
c_func
(paren
r_enum
id|kobject_action
id|action
)paren
(brace
r_if
c_cond
(paren
id|action
op_ge
id|KOBJ_MAX_ACTION
)paren
r_return
l_int|NULL
suffix:semicolon
r_else
r_return
id|actions
(braket
id|action
)braket
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_KOBJECT_UEVENT
DECL|variable|uevent_sock
r_static
r_struct
id|sock
op_star
id|uevent_sock
suffix:semicolon
multiline_comment|/**&n; * send_uevent - notify userspace by sending event trough netlink socket&n; *&n; * @signal: signal name&n; * @obj: object path (kobject)&n; * @buf: buffer used to pass auxiliary data like the hotplug environment&n; * @buflen:&n; * gfp_mask:&n; */
DECL|function|send_uevent
r_static
r_int
id|send_uevent
c_func
(paren
r_const
r_char
op_star
id|signal
comma
r_const
r_char
op_star
id|obj
comma
r_const
r_void
op_star
id|buf
comma
r_int
id|buflen
comma
r_int
id|gfp_mask
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_char
op_star
id|pos
suffix:semicolon
r_int
id|len
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|uevent_sock
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|len
op_assign
id|strlen
c_func
(paren
id|signal
)paren
op_plus
l_int|1
suffix:semicolon
id|len
op_add_assign
id|strlen
c_func
(paren
id|obj
)paren
op_plus
l_int|1
suffix:semicolon
id|len
op_add_assign
id|buflen
suffix:semicolon
id|skb
op_assign
id|alloc_skb
c_func
(paren
id|len
comma
id|gfp_mask
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|skb
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|pos
op_assign
id|skb_put
c_func
(paren
id|skb
comma
id|len
)paren
suffix:semicolon
id|pos
op_add_assign
id|sprintf
c_func
(paren
id|pos
comma
l_string|&quot;%s@%s&quot;
comma
id|signal
comma
id|obj
)paren
op_plus
l_int|1
suffix:semicolon
id|memcpy
c_func
(paren
id|pos
comma
id|buf
comma
id|buflen
)paren
suffix:semicolon
r_return
id|netlink_broadcast
c_func
(paren
id|uevent_sock
comma
id|skb
comma
l_int|0
comma
l_int|1
comma
id|gfp_mask
)paren
suffix:semicolon
)brace
DECL|function|do_kobject_uevent
r_static
r_int
id|do_kobject_uevent
c_func
(paren
r_struct
id|kobject
op_star
id|kobj
comma
r_enum
id|kobject_action
id|action
comma
r_struct
id|attribute
op_star
id|attr
comma
r_int
id|gfp_mask
)paren
(brace
r_char
op_star
id|path
suffix:semicolon
r_char
op_star
id|attrpath
suffix:semicolon
r_char
op_star
id|signal
suffix:semicolon
r_int
id|len
suffix:semicolon
r_int
id|rc
op_assign
op_minus
id|ENOMEM
suffix:semicolon
id|path
op_assign
id|kobject_get_path
c_func
(paren
id|kobj
comma
id|gfp_mask
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|path
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|signal
op_assign
id|action_to_string
c_func
(paren
id|action
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|signal
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|attr
)paren
(brace
id|len
op_assign
id|strlen
c_func
(paren
id|path
)paren
suffix:semicolon
id|len
op_add_assign
id|strlen
c_func
(paren
id|attr-&gt;name
)paren
op_plus
l_int|2
suffix:semicolon
id|attrpath
op_assign
id|kmalloc
c_func
(paren
id|len
comma
id|gfp_mask
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|attrpath
)paren
r_goto
m_exit
suffix:semicolon
id|sprintf
c_func
(paren
id|attrpath
comma
l_string|&quot;%s/%s&quot;
comma
id|path
comma
id|attr-&gt;name
)paren
suffix:semicolon
id|rc
op_assign
id|send_uevent
c_func
(paren
id|signal
comma
id|attrpath
comma
l_int|NULL
comma
l_int|0
comma
id|gfp_mask
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|attrpath
)paren
suffix:semicolon
)brace
r_else
(brace
id|rc
op_assign
id|send_uevent
c_func
(paren
id|signal
comma
id|path
comma
l_int|NULL
comma
l_int|0
comma
id|gfp_mask
)paren
suffix:semicolon
)brace
m_exit
suffix:colon
id|kfree
c_func
(paren
id|path
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
multiline_comment|/**&n; * kobject_uevent - notify userspace by sending event through netlink socket&n; * &n; * @signal: signal name&n; * @kobj: struct kobject that the event is happening to&n; * @attr: optional struct attribute the event belongs to&n; */
DECL|function|kobject_uevent
r_int
id|kobject_uevent
c_func
(paren
r_struct
id|kobject
op_star
id|kobj
comma
r_enum
id|kobject_action
id|action
comma
r_struct
id|attribute
op_star
id|attr
)paren
(brace
r_return
id|do_kobject_uevent
c_func
(paren
id|kobj
comma
id|action
comma
id|attr
comma
id|GFP_KERNEL
)paren
suffix:semicolon
)brace
DECL|variable|kobject_uevent
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|kobject_uevent
)paren
suffix:semicolon
DECL|function|kobject_uevent_atomic
r_int
id|kobject_uevent_atomic
c_func
(paren
r_struct
id|kobject
op_star
id|kobj
comma
r_enum
id|kobject_action
id|action
comma
r_struct
id|attribute
op_star
id|attr
)paren
(brace
r_return
id|do_kobject_uevent
c_func
(paren
id|kobj
comma
id|action
comma
id|attr
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
)brace
DECL|variable|kobject_uevent_atomic
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|kobject_uevent_atomic
)paren
suffix:semicolon
DECL|function|kobject_uevent_init
r_static
r_int
id|__init
id|kobject_uevent_init
c_func
(paren
r_void
)paren
(brace
id|uevent_sock
op_assign
id|netlink_kernel_create
c_func
(paren
id|NETLINK_KOBJECT_UEVENT
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|uevent_sock
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;kobject_uevent: unable to create netlink socket!&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|kobject_uevent_init
id|core_initcall
c_func
(paren
id|kobject_uevent_init
)paren
suffix:semicolon
macro_line|#else
DECL|function|send_uevent
r_static
r_inline
r_int
id|send_uevent
c_func
(paren
r_const
r_char
op_star
id|signal
comma
r_const
r_char
op_star
id|obj
comma
r_const
r_void
op_star
id|buf
comma
r_int
id|buflen
comma
r_int
id|gfp_mask
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_KOBJECT_UEVENT */
macro_line|#ifdef CONFIG_HOTPLUG
DECL|variable|hotplug_seqnum
id|u64
id|hotplug_seqnum
suffix:semicolon
DECL|variable|sequence_lock
r_static
id|spinlock_t
id|sequence_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|macro|BUFFER_SIZE
mdefine_line|#define BUFFER_SIZE&t;1024&t;/* should be enough memory for the env */
DECL|macro|NUM_ENVP
mdefine_line|#define NUM_ENVP&t;32&t;/* number of env pointers */
multiline_comment|/**&n; * kobject_hotplug - notify userspace by executing /sbin/hotplug&n; *&n; * @action: action that is happening (usually &quot;ADD&quot; or &quot;REMOVE&quot;)&n; * @kobj: struct kobject that the action is happening to&n; */
DECL|function|kobject_hotplug
r_void
id|kobject_hotplug
c_func
(paren
r_struct
id|kobject
op_star
id|kobj
comma
r_enum
id|kobject_action
id|action
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
r_char
op_star
id|action_string
suffix:semicolon
id|u64
id|seq
suffix:semicolon
r_struct
id|kobject
op_star
id|top_kobj
op_assign
id|kobj
suffix:semicolon
r_struct
id|kset
op_star
id|kset
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
id|kset
op_assign
id|top_kobj-&gt;kset
suffix:semicolon
r_else
r_return
suffix:semicolon
multiline_comment|/* If the kset has a filter operation, call it.&n;&t;   Skip the event, if the filter returns zero. */
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
id|action_string
op_assign
id|action_to_string
c_func
(paren
id|action
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|action_string
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
l_int|NULL
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
id|action_string
)paren
op_plus
l_int|1
suffix:semicolon
id|kobj_path
op_assign
id|kobject_get_path
c_func
(paren
id|kobj
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
id|spin_lock
c_func
(paren
op_amp
id|sequence_lock
)paren
suffix:semicolon
id|seq
op_assign
op_increment
id|hotplug_seqnum
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|sequence_lock
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
c_func
(paren
id|scratch
comma
l_string|&quot;SEQNUM=%lld&quot;
comma
(paren
r_int
r_int
)paren
id|seq
)paren
op_plus
l_int|1
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
l_string|&quot;SUBSYSTEM=%s&quot;
comma
id|name
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
l_string|&quot;%s: %s %s %s %s %s %s %s&bslash;n&quot;
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
comma
id|envp
(braket
l_int|4
)braket
)paren
suffix:semicolon
id|send_uevent
c_func
(paren
id|action_string
comma
id|kobj_path
comma
id|buffer
comma
id|scratch
op_minus
id|buffer
comma
id|GFP_KERNEL
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
r_goto
m_exit
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
DECL|variable|kobject_hotplug
id|EXPORT_SYMBOL
c_func
(paren
id|kobject_hotplug
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_HOTPLUG */
eof
