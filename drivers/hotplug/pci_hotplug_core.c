multiline_comment|/*&n; * PCI HotPlug Controller Core&n; *&n; * Copyright (c) 2001-2002 Greg Kroah-Hartman (greg@kroah.com)&n; * Copyright (c) 2001-2002 IBM Corp.&n; *&n; * All rights reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or (at&n; * your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, GOOD TITLE or&n; * NON INFRINGEMENT.  See the GNU General Public License for more&n; * details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; * Send feedback to &lt;greg@kroah.com&gt;&n; *&n; * Filesystem portion based on work done by Pat Mochel on ddfs/driverfs&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/mount.h&gt;
macro_line|#include &lt;linux/namei.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/dnotify.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/kobject.h&gt;
macro_line|#include &lt;linux/sysfs.h&gt;
macro_line|#include &quot;pci_hotplug.h&quot;
macro_line|#if !defined(CONFIG_HOTPLUG_PCI_MODULE)
DECL|macro|MY_NAME
mdefine_line|#define MY_NAME&t;&quot;pci_hotplug&quot;
macro_line|#else
DECL|macro|MY_NAME
mdefine_line|#define MY_NAME&t;THIS_MODULE-&gt;name
macro_line|#endif
DECL|macro|dbg
mdefine_line|#define dbg(fmt, arg...) do { if (debug) printk(KERN_DEBUG &quot;%s: %s: &quot; fmt , MY_NAME , __FUNCTION__ , ## arg); } while (0)
DECL|macro|err
mdefine_line|#define err(format, arg...) printk(KERN_ERR &quot;%s: &quot; format , MY_NAME , ## arg)
DECL|macro|info
mdefine_line|#define info(format, arg...) printk(KERN_INFO &quot;%s: &quot; format , MY_NAME , ## arg)
DECL|macro|warn
mdefine_line|#define warn(format, arg...) printk(KERN_WARNING &quot;%s: &quot; format , MY_NAME , ## arg)
multiline_comment|/* local variables */
DECL|variable|debug
r_static
r_int
id|debug
suffix:semicolon
DECL|macro|DRIVER_VERSION
mdefine_line|#define DRIVER_VERSION&t;&quot;0.5&quot;
DECL|macro|DRIVER_AUTHOR
mdefine_line|#define DRIVER_AUTHOR&t;&quot;Greg Kroah-Hartman &lt;greg@kroah.com&gt;, Scott Murray &lt;scottm@somanetworks.com&gt;&quot;
DECL|macro|DRIVER_DESC
mdefine_line|#define DRIVER_DESC&t;&quot;PCI Hot Plug PCI Core&quot;
singleline_comment|//////////////////////////////////////////////////////////////////
DECL|variable|list_lock
r_static
id|spinlock_t
id|list_lock
suffix:semicolon
r_static
id|LIST_HEAD
c_func
(paren
id|pci_hotplug_slot_list
)paren
suffix:semicolon
DECL|variable|hotplug_slots_subsys
r_static
r_struct
id|subsystem
id|hotplug_slots_subsys
suffix:semicolon
DECL|function|hotplug_slot_attr_show
r_static
id|ssize_t
id|hotplug_slot_attr_show
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
id|buf
)paren
(brace
r_struct
id|hotplug_slot
op_star
id|slot
op_assign
id|container_of
c_func
(paren
id|kobj
comma
r_struct
id|hotplug_slot
comma
id|kobj
)paren
suffix:semicolon
r_struct
id|hotplug_slot_attribute
op_star
id|attribute
op_assign
id|container_of
c_func
(paren
id|attr
comma
r_struct
id|hotplug_slot_attribute
comma
id|attr
)paren
suffix:semicolon
r_return
id|attribute-&gt;show
ques
c_cond
id|attribute
op_member_access_from_pointer
id|show
c_func
(paren
id|slot
comma
id|buf
)paren
suffix:colon
l_int|0
suffix:semicolon
)brace
DECL|function|hotplug_slot_attr_store
r_static
id|ssize_t
id|hotplug_slot_attr_store
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
id|buf
comma
r_int
id|len
)paren
(brace
r_struct
id|hotplug_slot
op_star
id|slot
op_assign
id|container_of
c_func
(paren
id|kobj
comma
r_struct
id|hotplug_slot
comma
id|kobj
)paren
suffix:semicolon
r_struct
id|hotplug_slot_attribute
op_star
id|attribute
op_assign
id|container_of
c_func
(paren
id|attr
comma
r_struct
id|hotplug_slot_attribute
comma
id|attr
)paren
suffix:semicolon
r_return
id|attribute-&gt;store
ques
c_cond
id|attribute
op_member_access_from_pointer
id|store
c_func
(paren
id|slot
comma
id|buf
comma
id|len
)paren
suffix:colon
l_int|0
suffix:semicolon
)brace
DECL|variable|hotplug_slot_sysfs_ops
r_static
r_struct
id|sysfs_ops
id|hotplug_slot_sysfs_ops
op_assign
(brace
dot
id|show
op_assign
id|hotplug_slot_attr_show
comma
dot
id|store
op_assign
id|hotplug_slot_attr_store
comma
)brace
suffix:semicolon
DECL|variable|hotplug_slot_ktype
r_static
r_struct
id|kobj_type
id|hotplug_slot_ktype
op_assign
(brace
dot
id|sysfs_ops
op_assign
op_amp
id|hotplug_slot_sysfs_ops
)brace
suffix:semicolon
DECL|variable|decl_subsys
r_static
id|decl_subsys
c_func
(paren
id|hotplug_slots
comma
op_amp
id|hotplug_slot_ktype
)paren
suffix:semicolon
multiline_comment|/* these strings match up with the values in pci_bus_speed */
DECL|variable|pci_bus_speed_strings
r_static
r_char
op_star
id|pci_bus_speed_strings
(braket
)braket
op_assign
(brace
l_string|&quot;33 MHz PCI&quot;
comma
multiline_comment|/* 0x00 */
l_string|&quot;66 MHz PCI&quot;
comma
multiline_comment|/* 0x01 */
l_string|&quot;66 MHz PCIX&quot;
comma
multiline_comment|/* 0x02 */
l_string|&quot;100 MHz PCIX&quot;
comma
multiline_comment|/* 0x03 */
l_string|&quot;133 MHz PCIX&quot;
comma
multiline_comment|/* 0x04 */
l_int|NULL
comma
multiline_comment|/* 0x05 */
l_int|NULL
comma
multiline_comment|/* 0x06 */
l_int|NULL
comma
multiline_comment|/* 0x07 */
l_int|NULL
comma
multiline_comment|/* 0x08 */
l_string|&quot;66 MHz PCIX 266&quot;
comma
multiline_comment|/* 0x09 */
l_string|&quot;100 MHz PCIX 266&quot;
comma
multiline_comment|/* 0x0a */
l_string|&quot;133 MHz PCIX 266&quot;
comma
multiline_comment|/* 0x0b */
l_int|NULL
comma
multiline_comment|/* 0x0c */
l_int|NULL
comma
multiline_comment|/* 0x0d */
l_int|NULL
comma
multiline_comment|/* 0x0e */
l_int|NULL
comma
multiline_comment|/* 0x0f */
l_int|NULL
comma
multiline_comment|/* 0x10 */
l_string|&quot;66 MHz PCIX 533&quot;
comma
multiline_comment|/* 0x11 */
l_string|&quot;100 MHz PCIX 533&quot;
comma
multiline_comment|/* 0x12 */
l_string|&quot;133 MHz PCIX 533&quot;
comma
multiline_comment|/* 0x13 */
)brace
suffix:semicolon
macro_line|#ifdef CONFIG_HOTPLUG_PCI_CPCI
r_extern
r_int
id|cpci_hotplug_init
c_func
(paren
r_int
id|debug
)paren
suffix:semicolon
r_extern
r_void
id|cpci_hotplug_exit
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#else
DECL|function|cpci_hotplug_init
r_static
r_inline
r_int
id|cpci_hotplug_init
c_func
(paren
r_int
id|debug
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cpci_hotplug_exit
r_static
r_inline
r_void
id|cpci_hotplug_exit
c_func
(paren
r_void
)paren
(brace
)brace
macro_line|#endif
multiline_comment|/* Weee, fun with macros... */
DECL|macro|GET_STATUS
mdefine_line|#define GET_STATUS(name,type)&t;&bslash;&n;static int get_##name (struct hotplug_slot *slot, type *value)&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;struct hotplug_slot_ops *ops = slot-&gt;ops;&t;&t;&t;&bslash;&n;&t;int retval = 0;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (try_module_get(ops-&gt;owner)) {&t;&t;&t;&t;&bslash;&n;&t;&t;if (ops-&gt;get_##name)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;retval = ops-&gt;get_##name (slot, value);&t;&t;&bslash;&n;&t;&t;else&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;*value = slot-&gt;info-&gt;name;&t;&t;&t;&bslash;&n;&t;&t;module_put(ops-&gt;owner);&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;return retval;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;}
id|GET_STATUS
c_func
(paren
id|power_status
comma
id|u8
)paren
id|GET_STATUS
c_func
(paren
id|attention_status
comma
id|u8
)paren
id|GET_STATUS
c_func
(paren
id|latch_status
comma
id|u8
)paren
id|GET_STATUS
c_func
(paren
id|adapter_status
comma
id|u8
)paren
id|GET_STATUS
c_func
(paren
id|max_bus_speed
comma
r_enum
id|pci_bus_speed
)paren
id|GET_STATUS
c_func
(paren
id|cur_bus_speed
comma
r_enum
id|pci_bus_speed
)paren
DECL|function|power_read_file
r_static
id|ssize_t
id|power_read_file
(paren
r_struct
id|hotplug_slot
op_star
id|slot
comma
r_char
op_star
id|buf
)paren
(brace
r_int
id|retval
suffix:semicolon
id|u8
id|value
suffix:semicolon
id|retval
op_assign
id|get_power_status
(paren
id|slot
comma
op_amp
id|value
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_goto
m_exit
suffix:semicolon
id|retval
op_assign
id|sprintf
(paren
id|buf
comma
l_string|&quot;%d&bslash;n&quot;
comma
id|value
)paren
suffix:semicolon
m_exit
suffix:colon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|power_write_file
r_static
id|ssize_t
id|power_write_file
(paren
r_struct
id|hotplug_slot
op_star
id|slot
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|count
)paren
(brace
r_int
r_int
id|lpower
suffix:semicolon
id|u8
id|power
suffix:semicolon
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
id|lpower
op_assign
id|simple_strtoul
(paren
id|buf
comma
l_int|NULL
comma
l_int|10
)paren
suffix:semicolon
id|power
op_assign
(paren
id|u8
)paren
(paren
id|lpower
op_amp
l_int|0xff
)paren
suffix:semicolon
id|dbg
(paren
l_string|&quot;power = %d&bslash;n&quot;
comma
id|power
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|try_module_get
c_func
(paren
id|slot-&gt;ops-&gt;owner
)paren
)paren
(brace
id|retval
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
m_exit
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|power
)paren
(brace
r_case
l_int|0
suffix:colon
r_if
c_cond
(paren
id|slot-&gt;ops-&gt;disable_slot
)paren
id|retval
op_assign
id|slot-&gt;ops
op_member_access_from_pointer
id|disable_slot
c_func
(paren
id|slot
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
r_if
c_cond
(paren
id|slot-&gt;ops-&gt;enable_slot
)paren
id|retval
op_assign
id|slot-&gt;ops
op_member_access_from_pointer
id|enable_slot
c_func
(paren
id|slot
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|err
(paren
l_string|&quot;Illegal value specified for power&bslash;n&quot;
)paren
suffix:semicolon
id|retval
op_assign
op_minus
id|EINVAL
suffix:semicolon
)brace
id|module_put
c_func
(paren
id|slot-&gt;ops-&gt;owner
)paren
suffix:semicolon
m_exit
suffix:colon
r_if
c_cond
(paren
id|retval
)paren
r_return
id|retval
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
DECL|variable|hotplug_slot_attr_power
r_static
r_struct
id|hotplug_slot_attribute
id|hotplug_slot_attr_power
op_assign
(brace
dot
id|attr
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;power&quot;
comma
dot
id|mode
op_assign
id|S_IFREG
op_or
id|S_IRUGO
op_or
id|S_IWUSR
)brace
comma
dot
id|show
op_assign
id|power_read_file
comma
dot
id|store
op_assign
id|power_write_file
)brace
suffix:semicolon
DECL|function|attention_read_file
r_static
id|ssize_t
id|attention_read_file
(paren
r_struct
id|hotplug_slot
op_star
id|slot
comma
r_char
op_star
id|buf
)paren
(brace
r_int
id|retval
suffix:semicolon
id|u8
id|value
suffix:semicolon
id|retval
op_assign
id|get_attention_status
(paren
id|slot
comma
op_amp
id|value
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_goto
m_exit
suffix:semicolon
id|retval
op_assign
id|sprintf
(paren
id|buf
comma
l_string|&quot;%d&bslash;n&quot;
comma
id|value
)paren
suffix:semicolon
m_exit
suffix:colon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|attention_write_file
r_static
id|ssize_t
id|attention_write_file
(paren
r_struct
id|hotplug_slot
op_star
id|slot
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|count
)paren
(brace
r_int
r_int
id|lattention
suffix:semicolon
id|u8
id|attention
suffix:semicolon
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
id|lattention
op_assign
id|simple_strtoul
(paren
id|buf
comma
l_int|NULL
comma
l_int|10
)paren
suffix:semicolon
id|attention
op_assign
(paren
id|u8
)paren
(paren
id|lattention
op_amp
l_int|0xff
)paren
suffix:semicolon
id|dbg
(paren
l_string|&quot; - attention = %d&bslash;n&quot;
comma
id|attention
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|try_module_get
c_func
(paren
id|slot-&gt;ops-&gt;owner
)paren
)paren
(brace
id|retval
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
m_exit
suffix:semicolon
)brace
r_if
c_cond
(paren
id|slot-&gt;ops-&gt;set_attention_status
)paren
id|retval
op_assign
id|slot-&gt;ops
op_member_access_from_pointer
id|set_attention_status
c_func
(paren
id|slot
comma
id|attention
)paren
suffix:semicolon
id|module_put
c_func
(paren
id|slot-&gt;ops-&gt;owner
)paren
suffix:semicolon
m_exit
suffix:colon
r_if
c_cond
(paren
id|retval
)paren
r_return
id|retval
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
DECL|variable|hotplug_slot_attr_attention
r_static
r_struct
id|hotplug_slot_attribute
id|hotplug_slot_attr_attention
op_assign
(brace
dot
id|attr
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;attention&quot;
comma
dot
id|mode
op_assign
id|S_IFREG
op_or
id|S_IRUGO
op_or
id|S_IWUSR
)brace
comma
dot
id|show
op_assign
id|attention_read_file
comma
dot
id|store
op_assign
id|attention_write_file
)brace
suffix:semicolon
DECL|function|latch_read_file
r_static
id|ssize_t
id|latch_read_file
(paren
r_struct
id|hotplug_slot
op_star
id|slot
comma
r_char
op_star
id|buf
)paren
(brace
r_int
id|retval
suffix:semicolon
id|u8
id|value
suffix:semicolon
id|retval
op_assign
id|get_latch_status
(paren
id|slot
comma
op_amp
id|value
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_goto
m_exit
suffix:semicolon
id|retval
op_assign
id|sprintf
(paren
id|buf
comma
l_string|&quot;%d&bslash;n&quot;
comma
id|value
)paren
suffix:semicolon
m_exit
suffix:colon
r_return
id|retval
suffix:semicolon
)brace
DECL|variable|hotplug_slot_attr_latch
r_static
r_struct
id|hotplug_slot_attribute
id|hotplug_slot_attr_latch
op_assign
(brace
dot
id|attr
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;latch&quot;
comma
dot
id|mode
op_assign
id|S_IFREG
op_or
id|S_IRUGO
op_or
id|S_IWUSR
)brace
comma
dot
id|show
op_assign
id|latch_read_file
comma
)brace
suffix:semicolon
DECL|function|presence_read_file
r_static
id|ssize_t
id|presence_read_file
(paren
r_struct
id|hotplug_slot
op_star
id|slot
comma
r_char
op_star
id|buf
)paren
(brace
r_int
id|retval
suffix:semicolon
id|u8
id|value
suffix:semicolon
id|retval
op_assign
id|get_adapter_status
(paren
id|slot
comma
op_amp
id|value
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_goto
m_exit
suffix:semicolon
id|retval
op_assign
id|sprintf
(paren
id|buf
comma
l_string|&quot;%d&bslash;n&quot;
comma
id|value
)paren
suffix:semicolon
m_exit
suffix:colon
r_return
id|retval
suffix:semicolon
)brace
DECL|variable|hotplug_slot_attr_presence
r_static
r_struct
id|hotplug_slot_attribute
id|hotplug_slot_attr_presence
op_assign
(brace
dot
id|attr
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;adapter&quot;
comma
dot
id|mode
op_assign
id|S_IFREG
op_or
id|S_IRUGO
op_or
id|S_IWUSR
)brace
comma
dot
id|show
op_assign
id|presence_read_file
comma
)brace
suffix:semicolon
DECL|variable|unknown_speed
r_static
r_char
op_star
id|unknown_speed
op_assign
l_string|&quot;Unknown bus speed&quot;
suffix:semicolon
DECL|function|max_bus_speed_read_file
r_static
id|ssize_t
id|max_bus_speed_read_file
(paren
r_struct
id|hotplug_slot
op_star
id|slot
comma
r_char
op_star
id|buf
)paren
(brace
r_char
op_star
id|speed_string
suffix:semicolon
r_int
id|retval
suffix:semicolon
r_enum
id|pci_bus_speed
id|value
suffix:semicolon
id|retval
op_assign
id|get_max_bus_speed
(paren
id|slot
comma
op_amp
id|value
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_goto
m_exit
suffix:semicolon
r_if
c_cond
(paren
id|value
op_eq
id|PCI_SPEED_UNKNOWN
)paren
id|speed_string
op_assign
id|unknown_speed
suffix:semicolon
r_else
id|speed_string
op_assign
id|pci_bus_speed_strings
(braket
id|value
)braket
suffix:semicolon
id|retval
op_assign
id|sprintf
(paren
id|buf
comma
l_string|&quot;%s&bslash;n&quot;
comma
id|speed_string
)paren
suffix:semicolon
m_exit
suffix:colon
r_return
id|retval
suffix:semicolon
)brace
DECL|variable|hotplug_slot_attr_max_bus_speed
r_static
r_struct
id|hotplug_slot_attribute
id|hotplug_slot_attr_max_bus_speed
op_assign
(brace
dot
id|attr
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;max_bus_speed&quot;
comma
dot
id|mode
op_assign
id|S_IFREG
op_or
id|S_IRUGO
op_or
id|S_IWUSR
)brace
comma
dot
id|show
op_assign
id|max_bus_speed_read_file
comma
)brace
suffix:semicolon
DECL|function|cur_bus_speed_read_file
r_static
id|ssize_t
id|cur_bus_speed_read_file
(paren
r_struct
id|hotplug_slot
op_star
id|slot
comma
r_char
op_star
id|buf
)paren
(brace
r_char
op_star
id|speed_string
suffix:semicolon
r_int
id|retval
suffix:semicolon
r_enum
id|pci_bus_speed
id|value
suffix:semicolon
id|retval
op_assign
id|get_cur_bus_speed
(paren
id|slot
comma
op_amp
id|value
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_goto
m_exit
suffix:semicolon
r_if
c_cond
(paren
id|value
op_eq
id|PCI_SPEED_UNKNOWN
)paren
id|speed_string
op_assign
id|unknown_speed
suffix:semicolon
r_else
id|speed_string
op_assign
id|pci_bus_speed_strings
(braket
id|value
)braket
suffix:semicolon
id|retval
op_assign
id|sprintf
(paren
id|buf
comma
l_string|&quot;%s&bslash;n&quot;
comma
id|speed_string
)paren
suffix:semicolon
m_exit
suffix:colon
r_return
id|retval
suffix:semicolon
)brace
DECL|variable|hotplug_slot_attr_cur_bus_speed
r_static
r_struct
id|hotplug_slot_attribute
id|hotplug_slot_attr_cur_bus_speed
op_assign
(brace
dot
id|attr
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;cur_bus_speed&quot;
comma
dot
id|mode
op_assign
id|S_IFREG
op_or
id|S_IRUGO
op_or
id|S_IWUSR
)brace
comma
dot
id|show
op_assign
id|cur_bus_speed_read_file
comma
)brace
suffix:semicolon
DECL|function|test_write_file
r_static
id|ssize_t
id|test_write_file
(paren
r_struct
id|hotplug_slot
op_star
id|slot
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|count
)paren
(brace
r_int
r_int
id|ltest
suffix:semicolon
id|u32
id|test
suffix:semicolon
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
id|ltest
op_assign
id|simple_strtoul
(paren
id|buf
comma
l_int|NULL
comma
l_int|10
)paren
suffix:semicolon
id|test
op_assign
(paren
id|u32
)paren
(paren
id|ltest
op_amp
l_int|0xffffffff
)paren
suffix:semicolon
id|dbg
(paren
l_string|&quot;test = %d&bslash;n&quot;
comma
id|test
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|try_module_get
c_func
(paren
id|slot-&gt;ops-&gt;owner
)paren
)paren
(brace
id|retval
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
m_exit
suffix:semicolon
)brace
r_if
c_cond
(paren
id|slot-&gt;ops-&gt;hardware_test
)paren
id|retval
op_assign
id|slot-&gt;ops
op_member_access_from_pointer
id|hardware_test
c_func
(paren
id|slot
comma
id|test
)paren
suffix:semicolon
id|module_put
c_func
(paren
id|slot-&gt;ops-&gt;owner
)paren
suffix:semicolon
m_exit
suffix:colon
r_if
c_cond
(paren
id|retval
)paren
r_return
id|retval
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
DECL|variable|hotplug_slot_attr_test
r_static
r_struct
id|hotplug_slot_attribute
id|hotplug_slot_attr_test
op_assign
(brace
dot
id|attr
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;test&quot;
comma
dot
id|mode
op_assign
id|S_IFREG
op_or
id|S_IRUGO
op_or
id|S_IWUSR
)brace
comma
dot
id|store
op_assign
id|test_write_file
)brace
suffix:semicolon
DECL|function|fs_add_slot
r_static
r_int
id|fs_add_slot
(paren
r_struct
id|hotplug_slot
op_star
id|slot
)paren
(brace
r_if
c_cond
(paren
(paren
id|slot-&gt;ops-&gt;enable_slot
)paren
op_logical_or
(paren
id|slot-&gt;ops-&gt;disable_slot
)paren
op_logical_or
(paren
id|slot-&gt;ops-&gt;get_power_status
)paren
)paren
id|sysfs_create_file
c_func
(paren
op_amp
id|slot-&gt;kobj
comma
op_amp
id|hotplug_slot_attr_power.attr
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|slot-&gt;ops-&gt;set_attention_status
)paren
op_logical_or
(paren
id|slot-&gt;ops-&gt;get_attention_status
)paren
)paren
id|sysfs_create_file
c_func
(paren
op_amp
id|slot-&gt;kobj
comma
op_amp
id|hotplug_slot_attr_attention.attr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|slot-&gt;ops-&gt;get_latch_status
)paren
id|sysfs_create_file
c_func
(paren
op_amp
id|slot-&gt;kobj
comma
op_amp
id|hotplug_slot_attr_latch.attr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|slot-&gt;ops-&gt;get_adapter_status
)paren
id|sysfs_create_file
c_func
(paren
op_amp
id|slot-&gt;kobj
comma
op_amp
id|hotplug_slot_attr_presence.attr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|slot-&gt;ops-&gt;get_max_bus_speed
)paren
id|sysfs_create_file
c_func
(paren
op_amp
id|slot-&gt;kobj
comma
op_amp
id|hotplug_slot_attr_max_bus_speed.attr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|slot-&gt;ops-&gt;get_cur_bus_speed
)paren
id|sysfs_create_file
c_func
(paren
op_amp
id|slot-&gt;kobj
comma
op_amp
id|hotplug_slot_attr_cur_bus_speed.attr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|slot-&gt;ops-&gt;hardware_test
)paren
id|sysfs_create_file
c_func
(paren
op_amp
id|slot-&gt;kobj
comma
op_amp
id|hotplug_slot_attr_test.attr
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|fs_remove_slot
r_static
r_void
id|fs_remove_slot
(paren
r_struct
id|hotplug_slot
op_star
id|slot
)paren
(brace
r_if
c_cond
(paren
(paren
id|slot-&gt;ops-&gt;enable_slot
)paren
op_logical_or
(paren
id|slot-&gt;ops-&gt;disable_slot
)paren
op_logical_or
(paren
id|slot-&gt;ops-&gt;get_power_status
)paren
)paren
id|sysfs_remove_file
c_func
(paren
op_amp
id|slot-&gt;kobj
comma
op_amp
id|hotplug_slot_attr_power.attr
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|slot-&gt;ops-&gt;set_attention_status
)paren
op_logical_or
(paren
id|slot-&gt;ops-&gt;get_attention_status
)paren
)paren
id|sysfs_remove_file
c_func
(paren
op_amp
id|slot-&gt;kobj
comma
op_amp
id|hotplug_slot_attr_attention.attr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|slot-&gt;ops-&gt;get_latch_status
)paren
id|sysfs_remove_file
c_func
(paren
op_amp
id|slot-&gt;kobj
comma
op_amp
id|hotplug_slot_attr_latch.attr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|slot-&gt;ops-&gt;get_adapter_status
)paren
id|sysfs_remove_file
c_func
(paren
op_amp
id|slot-&gt;kobj
comma
op_amp
id|hotplug_slot_attr_presence.attr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|slot-&gt;ops-&gt;get_max_bus_speed
)paren
id|sysfs_remove_file
c_func
(paren
op_amp
id|slot-&gt;kobj
comma
op_amp
id|hotplug_slot_attr_max_bus_speed.attr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|slot-&gt;ops-&gt;get_cur_bus_speed
)paren
id|sysfs_remove_file
c_func
(paren
op_amp
id|slot-&gt;kobj
comma
op_amp
id|hotplug_slot_attr_cur_bus_speed.attr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|slot-&gt;ops-&gt;hardware_test
)paren
id|sysfs_remove_file
c_func
(paren
op_amp
id|slot-&gt;kobj
comma
op_amp
id|hotplug_slot_attr_test.attr
)paren
suffix:semicolon
)brace
DECL|function|get_slot_from_name
r_static
r_struct
id|hotplug_slot
op_star
id|get_slot_from_name
(paren
r_const
r_char
op_star
id|name
)paren
(brace
r_struct
id|hotplug_slot
op_star
id|slot
suffix:semicolon
r_struct
id|list_head
op_star
id|tmp
suffix:semicolon
id|list_for_each
(paren
id|tmp
comma
op_amp
id|pci_hotplug_slot_list
)paren
(brace
id|slot
op_assign
id|list_entry
(paren
id|tmp
comma
r_struct
id|hotplug_slot
comma
id|slot_list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|slot-&gt;name
comma
id|name
)paren
op_eq
l_int|0
)paren
r_return
id|slot
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/**&n; * pci_hp_register - register a hotplug_slot with the PCI hotplug subsystem&n; * @slot: pointer to the &amp;struct hotplug_slot to register&n; *&n; * Registers a hotplug slot with the pci hotplug subsystem, which will allow&n; * userspace interaction to the slot.&n; *&n; * Returns 0 if successful, anything else for an error.&n; */
DECL|function|pci_hp_register
r_int
id|pci_hp_register
(paren
r_struct
id|hotplug_slot
op_star
id|slot
)paren
(brace
r_int
id|result
suffix:semicolon
r_if
c_cond
(paren
id|slot
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
(paren
id|slot-&gt;info
op_eq
l_int|NULL
)paren
op_logical_or
(paren
id|slot-&gt;ops
op_eq
l_int|NULL
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* make sure we have not already registered this slot */
id|spin_lock
(paren
op_amp
id|list_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|get_slot_from_name
(paren
id|slot-&gt;name
)paren
op_ne
l_int|NULL
)paren
(brace
id|spin_unlock
(paren
op_amp
id|list_lock
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|strncpy
c_func
(paren
id|slot-&gt;kobj.name
comma
id|slot-&gt;name
comma
id|KOBJ_NAME_LEN
)paren
suffix:semicolon
id|kobj_set_kset_s
c_func
(paren
id|slot
comma
id|hotplug_slots_subsys
)paren
suffix:semicolon
r_if
c_cond
(paren
id|kobject_register
c_func
(paren
op_amp
id|slot-&gt;kobj
)paren
)paren
(brace
id|err
c_func
(paren
l_string|&quot;Unable to register kobject&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|list_add
(paren
op_amp
id|slot-&gt;slot_list
comma
op_amp
id|pci_hotplug_slot_list
)paren
suffix:semicolon
id|spin_unlock
(paren
op_amp
id|list_lock
)paren
suffix:semicolon
id|result
op_assign
id|fs_add_slot
(paren
id|slot
)paren
suffix:semicolon
id|dbg
(paren
l_string|&quot;Added slot %s to the list&bslash;n&quot;
comma
id|slot-&gt;name
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
multiline_comment|/**&n; * pci_hp_deregister - deregister a hotplug_slot with the PCI hotplug subsystem&n; * @slot: pointer to the &amp;struct hotplug_slot to deregister&n; *&n; * The @slot must have been registered with the pci hotplug subsystem&n; * previously with a call to pci_hp_register().&n; *&n; * Returns 0 if successful, anything else for an error.&n; */
DECL|function|pci_hp_deregister
r_int
id|pci_hp_deregister
(paren
r_struct
id|hotplug_slot
op_star
id|slot
)paren
(brace
r_struct
id|hotplug_slot
op_star
id|temp
suffix:semicolon
r_if
c_cond
(paren
id|slot
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
multiline_comment|/* make sure we have this slot in our list before trying to delete it */
id|spin_lock
(paren
op_amp
id|list_lock
)paren
suffix:semicolon
id|temp
op_assign
id|get_slot_from_name
(paren
id|slot-&gt;name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|temp
op_ne
id|slot
)paren
(brace
id|spin_unlock
(paren
op_amp
id|list_lock
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|list_del
(paren
op_amp
id|slot-&gt;slot_list
)paren
suffix:semicolon
id|spin_unlock
(paren
op_amp
id|list_lock
)paren
suffix:semicolon
id|fs_remove_slot
(paren
id|slot
)paren
suffix:semicolon
id|dbg
(paren
l_string|&quot;Removed slot %s from the list&bslash;n&quot;
comma
id|slot-&gt;name
)paren
suffix:semicolon
id|kobject_unregister
c_func
(paren
op_amp
id|slot-&gt;kobj
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * pci_hp_change_slot_info - changes the slot&squot;s information structure in the core&n; * @slot: pointer to the slot whose info has changed&n; * @info: pointer to the info copy into the slot&squot;s info structure&n; *&n; * @slot must have been registered with the pci &n; * hotplug subsystem previously with a call to pci_hp_register().&n; *&n; * Returns 0 if successful, anything else for an error.&n; * Not supported by sysfs now.&n; */
DECL|function|pci_hp_change_slot_info
r_int
id|pci_hp_change_slot_info
(paren
r_struct
id|hotplug_slot
op_star
id|slot
comma
r_struct
id|hotplug_slot_info
op_star
id|info
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pci_hotplug_init
r_static
r_int
id|__init
id|pci_hotplug_init
(paren
r_void
)paren
(brace
r_int
id|result
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|list_lock
)paren
suffix:semicolon
id|kset_set_kset_s
c_func
(paren
op_amp
id|hotplug_slots_subsys
comma
id|pci_bus_type.subsys
)paren
suffix:semicolon
id|result
op_assign
id|subsystem_register
c_func
(paren
op_amp
id|hotplug_slots_subsys
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
(brace
id|err
c_func
(paren
l_string|&quot;Register subsys with error %d&bslash;n&quot;
comma
id|result
)paren
suffix:semicolon
r_goto
m_exit
suffix:semicolon
)brace
id|result
op_assign
id|cpci_hotplug_init
c_func
(paren
id|debug
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
(brace
id|err
(paren
l_string|&quot;cpci_hotplug_init with error %d&bslash;n&quot;
comma
id|result
)paren
suffix:semicolon
r_goto
id|err_subsys
suffix:semicolon
)brace
id|info
(paren
id|DRIVER_DESC
l_string|&quot; version: &quot;
id|DRIVER_VERSION
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_goto
m_exit
suffix:semicolon
id|err_subsys
suffix:colon
id|subsystem_unregister
c_func
(paren
op_amp
id|hotplug_slots_subsys
)paren
suffix:semicolon
m_exit
suffix:colon
r_return
id|result
suffix:semicolon
)brace
DECL|function|pci_hotplug_exit
r_static
r_void
id|__exit
id|pci_hotplug_exit
(paren
r_void
)paren
(brace
id|cpci_hotplug_exit
c_func
(paren
)paren
suffix:semicolon
id|subsystem_unregister
c_func
(paren
op_amp
id|hotplug_slots_subsys
)paren
suffix:semicolon
)brace
DECL|variable|pci_hotplug_init
id|module_init
c_func
(paren
id|pci_hotplug_init
)paren
suffix:semicolon
DECL|variable|pci_hotplug_exit
id|module_exit
c_func
(paren
id|pci_hotplug_exit
)paren
suffix:semicolon
DECL|variable|DRIVER_AUTHOR
id|MODULE_AUTHOR
c_func
(paren
id|DRIVER_AUTHOR
)paren
suffix:semicolon
DECL|variable|DRIVER_DESC
id|MODULE_DESCRIPTION
c_func
(paren
id|DRIVER_DESC
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|debug
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|debug
comma
l_string|&quot;Debugging mode enabled or not&quot;
)paren
suffix:semicolon
DECL|variable|pci_hp_register
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|pci_hp_register
)paren
suffix:semicolon
DECL|variable|pci_hp_deregister
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|pci_hp_deregister
)paren
suffix:semicolon
DECL|variable|pci_hp_change_slot_info
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|pci_hp_change_slot_info
)paren
suffix:semicolon
eof
