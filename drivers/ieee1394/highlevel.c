multiline_comment|/*&n; * IEEE 1394 for Linux&n; *&n; * Copyright (C) 1999 Andreas E. Bombe&n; *&n; * This code is licensed under the GPL.  See the file COPYING in the root&n; * directory of the kernel sources for details.&n; *&n; *&n; * Contributions:&n; *&n; * Christian Toegel &lt;christian.toegel@gmx.at&gt;&n; *        unregister address space&n; *&n; * Manfred Weihs &lt;weihs@ict.tuwien.ac.at&gt;&n; *        unregister address space&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &quot;ieee1394.h&quot;
macro_line|#include &quot;ieee1394_types.h&quot;
macro_line|#include &quot;hosts.h&quot;
macro_line|#include &quot;ieee1394_core.h&quot;
macro_line|#include &quot;highlevel.h&quot;
macro_line|#include &quot;nodemgr.h&quot;
DECL|struct|hl_host_info
r_struct
id|hl_host_info
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|host
r_struct
id|hpsb_host
op_star
id|host
suffix:semicolon
DECL|member|size
r_int
id|size
suffix:semicolon
DECL|member|key
r_int
r_int
id|key
suffix:semicolon
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
)brace
suffix:semicolon
r_static
id|LIST_HEAD
c_func
(paren
id|hl_drivers
)paren
suffix:semicolon
r_static
id|DECLARE_RWSEM
c_func
(paren
id|hl_drivers_sem
)paren
suffix:semicolon
r_static
id|LIST_HEAD
c_func
(paren
id|hl_irqs
)paren
suffix:semicolon
DECL|variable|hl_irqs_lock
r_static
id|rwlock_t
id|hl_irqs_lock
op_assign
id|RW_LOCK_UNLOCKED
suffix:semicolon
r_static
id|LIST_HEAD
c_func
(paren
id|addr_space
)paren
suffix:semicolon
DECL|variable|addr_space_lock
r_static
id|rwlock_t
id|addr_space_lock
op_assign
id|RW_LOCK_UNLOCKED
suffix:semicolon
multiline_comment|/* addr_space list will have zero and max already included as bounds */
DECL|variable|dummy_ops
r_static
r_struct
id|hpsb_address_ops
id|dummy_ops
op_assign
(brace
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
)brace
suffix:semicolon
DECL|variable|dummy_zero_addr
DECL|variable|dummy_max_addr
r_static
r_struct
id|hpsb_address_serve
id|dummy_zero_addr
comma
id|dummy_max_addr
suffix:semicolon
DECL|function|hl_get_hostinfo
r_static
r_struct
id|hl_host_info
op_star
id|hl_get_hostinfo
c_func
(paren
r_struct
id|hpsb_highlevel
op_star
id|hl
comma
r_struct
id|hpsb_host
op_star
id|host
)paren
(brace
r_struct
id|hl_host_info
op_star
id|hi
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|list_head
op_star
id|lh
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hl
op_logical_or
op_logical_neg
id|host
)paren
r_return
l_int|NULL
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|hl-&gt;host_info_lock
)paren
suffix:semicolon
id|list_for_each
(paren
id|lh
comma
op_amp
id|hl-&gt;host_info_list
)paren
(brace
id|hi
op_assign
id|list_entry
c_func
(paren
id|lh
comma
r_struct
id|hl_host_info
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hi-&gt;host
op_eq
id|host
)paren
r_break
suffix:semicolon
id|hi
op_assign
l_int|NULL
suffix:semicolon
)brace
id|read_unlock
c_func
(paren
op_amp
id|hl-&gt;host_info_lock
)paren
suffix:semicolon
r_return
id|hi
suffix:semicolon
)brace
multiline_comment|/* Returns a per host/driver data structure that was previously stored by&n; * hpsb_create_hostinfo. */
DECL|function|hpsb_get_hostinfo
r_void
op_star
id|hpsb_get_hostinfo
c_func
(paren
r_struct
id|hpsb_highlevel
op_star
id|hl
comma
r_struct
id|hpsb_host
op_star
id|host
)paren
(brace
r_struct
id|hl_host_info
op_star
id|hi
op_assign
id|hl_get_hostinfo
c_func
(paren
id|hl
comma
id|host
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hi
)paren
r_return
id|hi-&gt;data
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* If size is zero, then the return here is only valid for error checking */
DECL|function|hpsb_create_hostinfo
r_void
op_star
id|hpsb_create_hostinfo
c_func
(paren
r_struct
id|hpsb_highlevel
op_star
id|hl
comma
r_struct
id|hpsb_host
op_star
id|host
comma
r_int
id|data_size
)paren
(brace
r_struct
id|hl_host_info
op_star
id|hi
suffix:semicolon
r_void
op_star
id|data
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|hi
op_assign
id|hl_get_hostinfo
c_func
(paren
id|hl
comma
id|host
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hi
)paren
(brace
id|HPSB_ERR
c_func
(paren
l_string|&quot;%s called hpsb_create_hostinfo when hostinfo already exists&quot;
comma
id|hl-&gt;name
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|hi
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|hi
)paren
op_plus
id|data_size
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hi
)paren
r_return
l_int|NULL
suffix:semicolon
id|memset
c_func
(paren
id|hi
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|hi
)paren
op_plus
id|data_size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|data_size
)paren
(brace
id|data
op_assign
id|hi-&gt;data
op_assign
id|hi
op_plus
l_int|1
suffix:semicolon
id|hi-&gt;size
op_assign
id|data_size
suffix:semicolon
)brace
r_else
id|data
op_assign
id|hi
suffix:semicolon
id|hi-&gt;host
op_assign
id|host
suffix:semicolon
id|write_lock_irqsave
c_func
(paren
op_amp
id|hl-&gt;host_info_lock
comma
id|flags
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|hi-&gt;list
comma
op_amp
id|hl-&gt;host_info_list
)paren
suffix:semicolon
id|write_unlock_irqrestore
c_func
(paren
op_amp
id|hl-&gt;host_info_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|data
suffix:semicolon
)brace
DECL|function|hpsb_set_hostinfo
r_int
id|hpsb_set_hostinfo
c_func
(paren
r_struct
id|hpsb_highlevel
op_star
id|hl
comma
r_struct
id|hpsb_host
op_star
id|host
comma
r_void
op_star
id|data
)paren
(brace
r_struct
id|hl_host_info
op_star
id|hi
suffix:semicolon
id|hi
op_assign
id|hl_get_hostinfo
c_func
(paren
id|hl
comma
id|host
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hi
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|hi-&gt;size
op_logical_and
op_logical_neg
id|hi-&gt;data
)paren
(brace
id|hi-&gt;data
op_assign
id|data
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_else
id|HPSB_ERR
c_func
(paren
l_string|&quot;%s called hpsb_set_hostinfo when hostinfo already has data&quot;
comma
id|hl-&gt;name
)paren
suffix:semicolon
)brace
r_else
id|HPSB_ERR
c_func
(paren
l_string|&quot;%s called hpsb_set_hostinfo when no hostinfo exists&quot;
comma
id|hl-&gt;name
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|hpsb_destroy_hostinfo
r_void
id|hpsb_destroy_hostinfo
c_func
(paren
r_struct
id|hpsb_highlevel
op_star
id|hl
comma
r_struct
id|hpsb_host
op_star
id|host
)paren
(brace
r_struct
id|hl_host_info
op_star
id|hi
suffix:semicolon
id|hi
op_assign
id|hl_get_hostinfo
c_func
(paren
id|hl
comma
id|host
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hi
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|write_lock_irqsave
c_func
(paren
op_amp
id|hl-&gt;host_info_lock
comma
id|flags
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|hi-&gt;list
)paren
suffix:semicolon
id|write_unlock_irqrestore
c_func
(paren
op_amp
id|hl-&gt;host_info_lock
comma
id|flags
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|hi
)paren
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
DECL|function|hpsb_set_hostinfo_key
r_void
id|hpsb_set_hostinfo_key
c_func
(paren
r_struct
id|hpsb_highlevel
op_star
id|hl
comma
r_struct
id|hpsb_host
op_star
id|host
comma
r_int
r_int
id|key
)paren
(brace
r_struct
id|hl_host_info
op_star
id|hi
suffix:semicolon
id|hi
op_assign
id|hl_get_hostinfo
c_func
(paren
id|hl
comma
id|host
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hi
)paren
id|hi-&gt;key
op_assign
id|key
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|hpsb_get_hostinfo_key
r_int
r_int
id|hpsb_get_hostinfo_key
c_func
(paren
r_struct
id|hpsb_highlevel
op_star
id|hl
comma
r_struct
id|hpsb_host
op_star
id|host
)paren
(brace
r_struct
id|hl_host_info
op_star
id|hi
suffix:semicolon
id|hi
op_assign
id|hl_get_hostinfo
c_func
(paren
id|hl
comma
id|host
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hi
)paren
r_return
id|hi-&gt;key
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hpsb_get_hostinfo_bykey
r_void
op_star
id|hpsb_get_hostinfo_bykey
c_func
(paren
r_struct
id|hpsb_highlevel
op_star
id|hl
comma
r_int
r_int
id|key
)paren
(brace
r_struct
id|list_head
op_star
id|lh
suffix:semicolon
r_struct
id|hl_host_info
op_star
id|hi
suffix:semicolon
r_void
op_star
id|data
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hl
)paren
r_return
l_int|NULL
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|hl-&gt;host_info_lock
)paren
suffix:semicolon
id|list_for_each
(paren
id|lh
comma
op_amp
id|hl-&gt;host_info_list
)paren
(brace
id|hi
op_assign
id|list_entry
c_func
(paren
id|lh
comma
r_struct
id|hl_host_info
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hi-&gt;key
op_eq
id|key
)paren
(brace
id|data
op_assign
id|hi-&gt;data
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|read_unlock
c_func
(paren
op_amp
id|hl-&gt;host_info_lock
)paren
suffix:semicolon
r_return
id|data
suffix:semicolon
)brace
DECL|function|hpsb_get_host_bykey
r_struct
id|hpsb_host
op_star
id|hpsb_get_host_bykey
c_func
(paren
r_struct
id|hpsb_highlevel
op_star
id|hl
comma
r_int
r_int
id|key
)paren
(brace
r_struct
id|list_head
op_star
id|lh
suffix:semicolon
r_struct
id|hl_host_info
op_star
id|hi
suffix:semicolon
r_struct
id|hpsb_host
op_star
id|host
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hl
)paren
r_return
l_int|NULL
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|hl-&gt;host_info_lock
)paren
suffix:semicolon
id|list_for_each
(paren
id|lh
comma
op_amp
id|hl-&gt;host_info_list
)paren
(brace
id|hi
op_assign
id|list_entry
c_func
(paren
id|lh
comma
r_struct
id|hl_host_info
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hi-&gt;key
op_eq
id|key
)paren
(brace
id|host
op_assign
id|hi-&gt;host
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|read_unlock
c_func
(paren
op_amp
id|hl-&gt;host_info_lock
)paren
suffix:semicolon
r_return
id|host
suffix:semicolon
)brace
DECL|function|highlevel_for_each_host_reg
r_static
r_int
id|highlevel_for_each_host_reg
c_func
(paren
r_struct
id|hpsb_host
op_star
id|host
comma
r_void
op_star
id|__data
)paren
(brace
r_struct
id|hpsb_highlevel
op_star
id|hl
op_assign
id|__data
suffix:semicolon
id|hl
op_member_access_from_pointer
id|add_host
c_func
(paren
id|host
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hpsb_register_highlevel
r_void
id|hpsb_register_highlevel
c_func
(paren
r_struct
id|hpsb_highlevel
op_star
id|hl
)paren
(brace
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|hl-&gt;addr_list
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|hl-&gt;host_info_list
)paren
suffix:semicolon
id|rwlock_init
c_func
(paren
op_amp
id|hl-&gt;host_info_lock
)paren
suffix:semicolon
id|down_write
c_func
(paren
op_amp
id|hl_drivers_sem
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|hl-&gt;hl_list
comma
op_amp
id|hl_drivers
)paren
suffix:semicolon
id|up_write
c_func
(paren
op_amp
id|hl_drivers_sem
)paren
suffix:semicolon
id|write_lock
c_func
(paren
op_amp
id|hl_irqs_lock
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|hl-&gt;irq_list
comma
op_amp
id|hl_irqs
)paren
suffix:semicolon
id|write_unlock
c_func
(paren
op_amp
id|hl_irqs_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hl-&gt;add_host
)paren
id|nodemgr_for_each_host
c_func
(paren
id|hl
comma
id|highlevel_for_each_host_reg
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|highlevel_for_each_host_unreg
r_static
r_int
id|highlevel_for_each_host_unreg
c_func
(paren
r_struct
id|hpsb_host
op_star
id|host
comma
r_void
op_star
id|__data
)paren
(brace
r_struct
id|hpsb_highlevel
op_star
id|hl
op_assign
id|__data
suffix:semicolon
id|hl
op_member_access_from_pointer
id|remove_host
c_func
(paren
id|host
)paren
suffix:semicolon
id|hpsb_destroy_hostinfo
c_func
(paren
id|hl
comma
id|host
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hpsb_unregister_highlevel
r_void
id|hpsb_unregister_highlevel
c_func
(paren
r_struct
id|hpsb_highlevel
op_star
id|hl
)paren
(brace
r_struct
id|list_head
op_star
id|lh
comma
op_star
id|next
suffix:semicolon
r_struct
id|hpsb_address_serve
op_star
id|as
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|write_lock_irqsave
c_func
(paren
op_amp
id|addr_space_lock
comma
id|flags
)paren
suffix:semicolon
id|list_for_each_safe
(paren
id|lh
comma
id|next
comma
op_amp
id|hl-&gt;addr_list
)paren
(brace
id|as
op_assign
id|list_entry
c_func
(paren
id|lh
comma
r_struct
id|hpsb_address_serve
comma
id|addr_list
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|as-&gt;as_list
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|as
)paren
suffix:semicolon
)brace
id|write_unlock_irqrestore
c_func
(paren
op_amp
id|addr_space_lock
comma
id|flags
)paren
suffix:semicolon
id|write_lock
c_func
(paren
op_amp
id|hl_irqs_lock
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|hl-&gt;irq_list
)paren
suffix:semicolon
id|write_unlock
c_func
(paren
op_amp
id|hl_irqs_lock
)paren
suffix:semicolon
id|down_write
c_func
(paren
op_amp
id|hl_drivers_sem
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|hl-&gt;hl_list
)paren
suffix:semicolon
id|up_write
c_func
(paren
op_amp
id|hl_drivers_sem
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hl-&gt;remove_host
)paren
id|nodemgr_for_each_host
c_func
(paren
id|hl
comma
id|highlevel_for_each_host_unreg
)paren
suffix:semicolon
)brace
DECL|function|hpsb_register_addrspace
r_int
id|hpsb_register_addrspace
c_func
(paren
r_struct
id|hpsb_highlevel
op_star
id|hl
comma
r_struct
id|hpsb_host
op_star
id|host
comma
r_struct
id|hpsb_address_ops
op_star
id|ops
comma
id|u64
id|start
comma
id|u64
id|end
)paren
(brace
r_struct
id|hpsb_address_serve
op_star
id|as
suffix:semicolon
r_struct
id|list_head
op_star
id|entry
suffix:semicolon
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
id|start
op_or
id|end
)paren
op_amp
l_int|3
)paren
op_logical_or
(paren
id|start
op_ge
id|end
)paren
op_logical_or
(paren
id|end
OG
l_int|0x1000000000000ULL
)paren
)paren
(brace
id|HPSB_ERR
c_func
(paren
l_string|&quot;%s called with invalid addresses&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|as
op_assign
(paren
r_struct
id|hpsb_address_serve
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|hpsb_address_serve
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|as
op_eq
l_int|NULL
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|as-&gt;as_list
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|as-&gt;addr_list
)paren
suffix:semicolon
id|as-&gt;op
op_assign
id|ops
suffix:semicolon
id|as-&gt;start
op_assign
id|start
suffix:semicolon
id|as-&gt;end
op_assign
id|end
suffix:semicolon
id|write_lock_irqsave
c_func
(paren
op_amp
id|addr_space_lock
comma
id|flags
)paren
suffix:semicolon
id|entry
op_assign
id|host-&gt;addr_space.next
suffix:semicolon
r_while
c_loop
(paren
id|list_entry
c_func
(paren
id|entry
comma
r_struct
id|hpsb_address_serve
comma
id|as_list
)paren
op_member_access_from_pointer
id|end
op_le
id|start
)paren
(brace
r_if
c_cond
(paren
id|list_entry
c_func
(paren
id|entry-&gt;next
comma
r_struct
id|hpsb_address_serve
comma
id|as_list
)paren
op_member_access_from_pointer
id|start
op_ge
id|end
)paren
(brace
id|list_add
c_func
(paren
op_amp
id|as-&gt;as_list
comma
id|entry
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|as-&gt;addr_list
comma
op_amp
id|hl-&gt;addr_list
)paren
suffix:semicolon
id|retval
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
id|entry
op_assign
id|entry-&gt;next
suffix:semicolon
)brace
id|write_unlock_irqrestore
c_func
(paren
op_amp
id|addr_space_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
op_eq
l_int|0
)paren
(brace
id|kfree
c_func
(paren
id|as
)paren
suffix:semicolon
)brace
r_return
id|retval
suffix:semicolon
)brace
DECL|function|hpsb_unregister_addrspace
r_int
id|hpsb_unregister_addrspace
c_func
(paren
r_struct
id|hpsb_highlevel
op_star
id|hl
comma
r_struct
id|hpsb_host
op_star
id|host
comma
id|u64
id|start
)paren
(brace
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
r_struct
id|hpsb_address_serve
op_star
id|as
suffix:semicolon
r_struct
id|list_head
op_star
id|entry
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|write_lock_irqsave
c_func
(paren
op_amp
id|addr_space_lock
comma
id|flags
)paren
suffix:semicolon
id|entry
op_assign
id|hl-&gt;addr_list.next
suffix:semicolon
r_while
c_loop
(paren
id|entry
op_ne
op_amp
id|hl-&gt;addr_list
)paren
(brace
id|as
op_assign
id|list_entry
c_func
(paren
id|entry
comma
r_struct
id|hpsb_address_serve
comma
id|addr_list
)paren
suffix:semicolon
id|entry
op_assign
id|entry-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|as-&gt;start
op_eq
id|start
op_logical_and
id|as-&gt;host
op_eq
id|host
)paren
(brace
id|list_del
c_func
(paren
op_amp
id|as-&gt;as_list
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|as-&gt;addr_list
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|as
)paren
suffix:semicolon
id|retval
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|write_unlock_irqrestore
c_func
(paren
op_amp
id|addr_space_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|hpsb_listen_channel
r_int
id|hpsb_listen_channel
c_func
(paren
r_struct
id|hpsb_highlevel
op_star
id|hl
comma
r_struct
id|hpsb_host
op_star
id|host
comma
r_int
r_int
id|channel
)paren
(brace
r_if
c_cond
(paren
id|channel
OG
l_int|63
)paren
(brace
id|HPSB_ERR
c_func
(paren
l_string|&quot;%s called with invalid channel&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|host-&gt;iso_listen_count
(braket
id|channel
)braket
op_increment
op_eq
l_int|0
)paren
(brace
r_return
id|host-&gt;driver
op_member_access_from_pointer
id|devctl
c_func
(paren
id|host
comma
id|ISO_LISTEN_CHANNEL
comma
id|channel
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hpsb_unlisten_channel
r_void
id|hpsb_unlisten_channel
c_func
(paren
r_struct
id|hpsb_highlevel
op_star
id|hl
comma
r_struct
id|hpsb_host
op_star
id|host
comma
r_int
r_int
id|channel
)paren
(brace
r_if
c_cond
(paren
id|channel
OG
l_int|63
)paren
(brace
id|HPSB_ERR
c_func
(paren
l_string|&quot;%s called with invalid channel&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
op_decrement
id|host-&gt;iso_listen_count
(braket
id|channel
)braket
op_eq
l_int|0
)paren
(brace
id|host-&gt;driver
op_member_access_from_pointer
id|devctl
c_func
(paren
id|host
comma
id|ISO_UNLISTEN_CHANNEL
comma
id|channel
)paren
suffix:semicolon
)brace
)brace
DECL|function|init_hpsb_highlevel
r_static
r_void
id|init_hpsb_highlevel
c_func
(paren
r_struct
id|hpsb_host
op_star
id|host
)paren
(brace
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|dummy_zero_addr.as_list
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|dummy_zero_addr.addr_list
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|dummy_max_addr.as_list
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|dummy_max_addr.addr_list
)paren
suffix:semicolon
id|dummy_zero_addr.op
op_assign
id|dummy_max_addr.op
op_assign
op_amp
id|dummy_ops
suffix:semicolon
id|dummy_zero_addr.start
op_assign
id|dummy_zero_addr.end
op_assign
l_int|0
suffix:semicolon
id|dummy_max_addr.start
op_assign
id|dummy_max_addr.end
op_assign
(paren
(paren
id|u64
)paren
l_int|1
)paren
op_lshift
l_int|48
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|dummy_zero_addr.as_list
comma
op_amp
id|host-&gt;addr_space
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|dummy_max_addr.as_list
comma
op_amp
id|host-&gt;addr_space
)paren
suffix:semicolon
)brace
DECL|function|highlevel_add_host
r_void
id|highlevel_add_host
c_func
(paren
r_struct
id|hpsb_host
op_star
id|host
)paren
(brace
r_struct
id|hpsb_highlevel
op_star
id|hl
suffix:semicolon
id|init_hpsb_highlevel
c_func
(paren
id|host
)paren
suffix:semicolon
id|down_read
c_func
(paren
op_amp
id|hl_drivers_sem
)paren
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|hl
comma
op_amp
id|hl_drivers
comma
id|hl_list
)paren
(brace
r_if
c_cond
(paren
id|hl-&gt;add_host
)paren
id|hl
op_member_access_from_pointer
id|add_host
c_func
(paren
id|host
)paren
suffix:semicolon
)brace
id|up_read
c_func
(paren
op_amp
id|hl_drivers_sem
)paren
suffix:semicolon
)brace
DECL|function|highlevel_remove_host
r_void
id|highlevel_remove_host
c_func
(paren
r_struct
id|hpsb_host
op_star
id|host
)paren
(brace
r_struct
id|hpsb_highlevel
op_star
id|hl
suffix:semicolon
r_struct
id|list_head
op_star
id|lh
comma
op_star
id|next
suffix:semicolon
r_struct
id|hpsb_address_serve
op_star
id|as
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|down_read
c_func
(paren
op_amp
id|hl_drivers_sem
)paren
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|hl
comma
op_amp
id|hl_drivers
comma
id|hl_list
)paren
(brace
r_if
c_cond
(paren
id|hl-&gt;remove_host
)paren
(brace
id|hl
op_member_access_from_pointer
id|remove_host
c_func
(paren
id|host
)paren
suffix:semicolon
id|hpsb_destroy_hostinfo
c_func
(paren
id|hl
comma
id|host
)paren
suffix:semicolon
)brace
)brace
id|up_read
c_func
(paren
op_amp
id|hl_drivers_sem
)paren
suffix:semicolon
multiline_comment|/* Free up 1394 address space left behind by high level drivers. */
id|write_lock_irqsave
c_func
(paren
op_amp
id|addr_space_lock
comma
id|flags
)paren
suffix:semicolon
id|list_for_each_safe
(paren
id|lh
comma
id|next
comma
op_amp
id|host-&gt;addr_space
)paren
(brace
id|as
op_assign
id|list_entry
c_func
(paren
id|lh
comma
r_struct
id|hpsb_address_serve
comma
id|as_list
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|as-&gt;addr_list
)paren
)paren
(brace
id|list_del
c_func
(paren
op_amp
id|as-&gt;addr_list
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|as
)paren
suffix:semicolon
)brace
)brace
id|write_unlock_irqrestore
c_func
(paren
op_amp
id|addr_space_lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|highlevel_host_reset
r_void
id|highlevel_host_reset
c_func
(paren
r_struct
id|hpsb_host
op_star
id|host
)paren
(brace
r_struct
id|hpsb_highlevel
op_star
id|hl
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|hl_irqs_lock
)paren
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|hl
comma
op_amp
id|hl_irqs
comma
id|irq_list
)paren
(brace
r_if
c_cond
(paren
id|hl-&gt;host_reset
)paren
id|hl
op_member_access_from_pointer
id|host_reset
c_func
(paren
id|host
)paren
suffix:semicolon
)brace
id|read_unlock
c_func
(paren
op_amp
id|hl_irqs_lock
)paren
suffix:semicolon
)brace
DECL|function|highlevel_iso_receive
r_void
id|highlevel_iso_receive
c_func
(paren
r_struct
id|hpsb_host
op_star
id|host
comma
r_void
op_star
id|data
comma
r_int
id|length
)paren
(brace
r_struct
id|hpsb_highlevel
op_star
id|hl
suffix:semicolon
r_int
id|channel
op_assign
(paren
(paren
(paren
id|quadlet_t
op_star
)paren
id|data
)paren
(braket
l_int|0
)braket
op_rshift
l_int|8
)paren
op_amp
l_int|0x3f
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|hl_irqs_lock
)paren
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|hl
comma
op_amp
id|hl_irqs
comma
id|irq_list
)paren
(brace
r_if
c_cond
(paren
id|hl-&gt;iso_receive
)paren
id|hl
op_member_access_from_pointer
id|iso_receive
c_func
(paren
id|host
comma
id|channel
comma
id|data
comma
id|length
)paren
suffix:semicolon
)brace
id|read_unlock
c_func
(paren
op_amp
id|hl_irqs_lock
)paren
suffix:semicolon
)brace
DECL|function|highlevel_fcp_request
r_void
id|highlevel_fcp_request
c_func
(paren
r_struct
id|hpsb_host
op_star
id|host
comma
r_int
id|nodeid
comma
r_int
id|direction
comma
r_void
op_star
id|data
comma
r_int
id|length
)paren
(brace
r_struct
id|hpsb_highlevel
op_star
id|hl
suffix:semicolon
r_int
id|cts
op_assign
(paren
(paren
id|quadlet_t
op_star
)paren
id|data
)paren
(braket
l_int|0
)braket
op_rshift
l_int|4
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|hl_irqs_lock
)paren
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|hl
comma
op_amp
id|hl_irqs
comma
id|irq_list
)paren
(brace
r_if
c_cond
(paren
id|hl-&gt;fcp_request
)paren
id|hl
op_member_access_from_pointer
id|fcp_request
c_func
(paren
id|host
comma
id|nodeid
comma
id|direction
comma
id|cts
comma
id|data
comma
id|length
)paren
suffix:semicolon
)brace
id|read_unlock
c_func
(paren
op_amp
id|hl_irqs_lock
)paren
suffix:semicolon
)brace
DECL|function|highlevel_read
r_int
id|highlevel_read
c_func
(paren
r_struct
id|hpsb_host
op_star
id|host
comma
r_int
id|nodeid
comma
r_void
op_star
id|data
comma
id|u64
id|addr
comma
r_int
r_int
id|length
comma
id|u16
id|flags
)paren
(brace
r_struct
id|hpsb_address_serve
op_star
id|as
suffix:semicolon
r_struct
id|list_head
op_star
id|entry
suffix:semicolon
r_int
r_int
id|partlength
suffix:semicolon
r_int
id|rcode
op_assign
id|RCODE_ADDRESS_ERROR
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|addr_space_lock
)paren
suffix:semicolon
id|entry
op_assign
id|host-&gt;addr_space.next
suffix:semicolon
id|as
op_assign
id|list_entry
c_func
(paren
id|entry
comma
r_struct
id|hpsb_address_serve
comma
id|as_list
)paren
suffix:semicolon
r_while
c_loop
(paren
id|as-&gt;start
op_le
id|addr
)paren
(brace
r_if
c_cond
(paren
id|as-&gt;end
OG
id|addr
)paren
(brace
id|partlength
op_assign
id|min
c_func
(paren
id|as-&gt;end
op_minus
id|addr
comma
(paren
id|u64
)paren
id|length
)paren
suffix:semicolon
r_if
c_cond
(paren
id|as-&gt;op-&gt;read
)paren
(brace
id|rcode
op_assign
id|as-&gt;op
op_member_access_from_pointer
id|read
c_func
(paren
id|host
comma
id|nodeid
comma
id|data
comma
id|addr
comma
id|partlength
comma
id|flags
)paren
suffix:semicolon
)brace
r_else
(brace
id|rcode
op_assign
id|RCODE_TYPE_ERROR
suffix:semicolon
)brace
(paren
id|u8
op_star
)paren
id|data
op_add_assign
id|partlength
suffix:semicolon
id|length
op_sub_assign
id|partlength
suffix:semicolon
id|addr
op_add_assign
id|partlength
suffix:semicolon
r_if
c_cond
(paren
(paren
id|rcode
op_ne
id|RCODE_COMPLETE
)paren
op_logical_or
op_logical_neg
id|length
)paren
(brace
r_break
suffix:semicolon
)brace
)brace
id|entry
op_assign
id|entry-&gt;next
suffix:semicolon
id|as
op_assign
id|list_entry
c_func
(paren
id|entry
comma
r_struct
id|hpsb_address_serve
comma
id|as_list
)paren
suffix:semicolon
)brace
id|read_unlock
c_func
(paren
op_amp
id|addr_space_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|length
op_logical_and
(paren
id|rcode
op_eq
id|RCODE_COMPLETE
)paren
)paren
(brace
id|rcode
op_assign
id|RCODE_ADDRESS_ERROR
suffix:semicolon
)brace
r_return
id|rcode
suffix:semicolon
)brace
DECL|function|highlevel_write
r_int
id|highlevel_write
c_func
(paren
r_struct
id|hpsb_host
op_star
id|host
comma
r_int
id|nodeid
comma
r_int
id|destid
comma
r_void
op_star
id|data
comma
id|u64
id|addr
comma
r_int
r_int
id|length
comma
id|u16
id|flags
)paren
(brace
r_struct
id|hpsb_address_serve
op_star
id|as
suffix:semicolon
r_struct
id|list_head
op_star
id|entry
suffix:semicolon
r_int
r_int
id|partlength
suffix:semicolon
r_int
id|rcode
op_assign
id|RCODE_ADDRESS_ERROR
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|addr_space_lock
)paren
suffix:semicolon
id|entry
op_assign
id|host-&gt;addr_space.next
suffix:semicolon
id|as
op_assign
id|list_entry
c_func
(paren
id|entry
comma
r_struct
id|hpsb_address_serve
comma
id|as_list
)paren
suffix:semicolon
r_while
c_loop
(paren
id|as-&gt;start
op_le
id|addr
)paren
(brace
r_if
c_cond
(paren
id|as-&gt;end
OG
id|addr
)paren
(brace
id|partlength
op_assign
id|min
c_func
(paren
id|as-&gt;end
op_minus
id|addr
comma
(paren
id|u64
)paren
id|length
)paren
suffix:semicolon
r_if
c_cond
(paren
id|as-&gt;op-&gt;write
)paren
(brace
id|rcode
op_assign
id|as-&gt;op
op_member_access_from_pointer
id|write
c_func
(paren
id|host
comma
id|nodeid
comma
id|destid
comma
id|data
comma
id|addr
comma
id|partlength
comma
id|flags
)paren
suffix:semicolon
)brace
r_else
(brace
id|rcode
op_assign
id|RCODE_TYPE_ERROR
suffix:semicolon
)brace
(paren
id|u8
op_star
)paren
id|data
op_add_assign
id|partlength
suffix:semicolon
id|length
op_sub_assign
id|partlength
suffix:semicolon
id|addr
op_add_assign
id|partlength
suffix:semicolon
r_if
c_cond
(paren
(paren
id|rcode
op_ne
id|RCODE_COMPLETE
)paren
op_logical_or
op_logical_neg
id|length
)paren
(brace
r_break
suffix:semicolon
)brace
)brace
id|entry
op_assign
id|entry-&gt;next
suffix:semicolon
id|as
op_assign
id|list_entry
c_func
(paren
id|entry
comma
r_struct
id|hpsb_address_serve
comma
id|as_list
)paren
suffix:semicolon
)brace
id|read_unlock
c_func
(paren
op_amp
id|addr_space_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|length
op_logical_and
(paren
id|rcode
op_eq
id|RCODE_COMPLETE
)paren
)paren
(brace
id|rcode
op_assign
id|RCODE_ADDRESS_ERROR
suffix:semicolon
)brace
r_return
id|rcode
suffix:semicolon
)brace
DECL|function|highlevel_lock
r_int
id|highlevel_lock
c_func
(paren
r_struct
id|hpsb_host
op_star
id|host
comma
r_int
id|nodeid
comma
id|quadlet_t
op_star
id|store
comma
id|u64
id|addr
comma
id|quadlet_t
id|data
comma
id|quadlet_t
id|arg
comma
r_int
id|ext_tcode
comma
id|u16
id|flags
)paren
(brace
r_struct
id|hpsb_address_serve
op_star
id|as
suffix:semicolon
r_struct
id|list_head
op_star
id|entry
suffix:semicolon
r_int
id|rcode
op_assign
id|RCODE_ADDRESS_ERROR
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|addr_space_lock
)paren
suffix:semicolon
id|entry
op_assign
id|host-&gt;addr_space.next
suffix:semicolon
id|as
op_assign
id|list_entry
c_func
(paren
id|entry
comma
r_struct
id|hpsb_address_serve
comma
id|as_list
)paren
suffix:semicolon
r_while
c_loop
(paren
id|as-&gt;start
op_le
id|addr
)paren
(brace
r_if
c_cond
(paren
id|as-&gt;end
OG
id|addr
)paren
(brace
r_if
c_cond
(paren
id|as-&gt;op-&gt;lock
)paren
(brace
id|rcode
op_assign
id|as-&gt;op
op_member_access_from_pointer
id|lock
c_func
(paren
id|host
comma
id|nodeid
comma
id|store
comma
id|addr
comma
id|data
comma
id|arg
comma
id|ext_tcode
comma
id|flags
)paren
suffix:semicolon
)brace
r_else
(brace
id|rcode
op_assign
id|RCODE_TYPE_ERROR
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
id|entry
op_assign
id|entry-&gt;next
suffix:semicolon
id|as
op_assign
id|list_entry
c_func
(paren
id|entry
comma
r_struct
id|hpsb_address_serve
comma
id|as_list
)paren
suffix:semicolon
)brace
id|read_unlock
c_func
(paren
op_amp
id|addr_space_lock
)paren
suffix:semicolon
r_return
id|rcode
suffix:semicolon
)brace
DECL|function|highlevel_lock64
r_int
id|highlevel_lock64
c_func
(paren
r_struct
id|hpsb_host
op_star
id|host
comma
r_int
id|nodeid
comma
id|octlet_t
op_star
id|store
comma
id|u64
id|addr
comma
id|octlet_t
id|data
comma
id|octlet_t
id|arg
comma
r_int
id|ext_tcode
comma
id|u16
id|flags
)paren
(brace
r_struct
id|hpsb_address_serve
op_star
id|as
suffix:semicolon
r_struct
id|list_head
op_star
id|entry
suffix:semicolon
r_int
id|rcode
op_assign
id|RCODE_ADDRESS_ERROR
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|addr_space_lock
)paren
suffix:semicolon
id|entry
op_assign
id|host-&gt;addr_space.next
suffix:semicolon
id|as
op_assign
id|list_entry
c_func
(paren
id|entry
comma
r_struct
id|hpsb_address_serve
comma
id|as_list
)paren
suffix:semicolon
r_while
c_loop
(paren
id|as-&gt;start
op_le
id|addr
)paren
(brace
r_if
c_cond
(paren
id|as-&gt;end
OG
id|addr
)paren
(brace
r_if
c_cond
(paren
id|as-&gt;op-&gt;lock64
)paren
(brace
id|rcode
op_assign
id|as-&gt;op
op_member_access_from_pointer
id|lock64
c_func
(paren
id|host
comma
id|nodeid
comma
id|store
comma
id|addr
comma
id|data
comma
id|arg
comma
id|ext_tcode
comma
id|flags
)paren
suffix:semicolon
)brace
r_else
(brace
id|rcode
op_assign
id|RCODE_TYPE_ERROR
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
id|entry
op_assign
id|entry-&gt;next
suffix:semicolon
id|as
op_assign
id|list_entry
c_func
(paren
id|entry
comma
r_struct
id|hpsb_address_serve
comma
id|as_list
)paren
suffix:semicolon
)brace
id|read_unlock
c_func
(paren
op_amp
id|addr_space_lock
)paren
suffix:semicolon
r_return
id|rcode
suffix:semicolon
)brace
eof
