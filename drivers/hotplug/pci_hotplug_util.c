multiline_comment|/*&n; * PCI HotPlug Utility functions&n; *&n; * Copyright (c) 1995,2001 Compaq Computer Corporation&n; * Copyright (c) 2001 Greg Kroah-Hartman (greg@kroah.com)&n; * Copyright (c) 2001 IBM Corp.&n; *&n; * All rights reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or (at&n; * your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, GOOD TITLE or&n; * NON INFRINGEMENT.  See the GNU General Public License for more&n; * details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; * Send feedback to &lt;greg@kroah.com&gt;&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
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
multiline_comment|/*&n; * This is code that scans the pci buses.&n; * Every bus and every function is presented to a custom&n; * function that can act upon it.&n; */
DECL|function|pci_visit_bus
r_static
r_int
id|pci_visit_bus
(paren
r_struct
id|pci_visit
op_star
id|fn
comma
r_struct
id|pci_bus_wrapped
op_star
id|wrapped_bus
comma
r_struct
id|pci_dev_wrapped
op_star
id|wrapped_parent
)paren
(brace
r_struct
id|list_head
op_star
id|ln
suffix:semicolon
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
r_struct
id|pci_dev_wrapped
id|wrapped_dev
suffix:semicolon
r_int
id|result
op_assign
l_int|0
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;scanning bus %02x&bslash;n&quot;
comma
id|wrapped_bus-&gt;bus-&gt;number
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fn-&gt;pre_visit_pci_bus
)paren
(brace
id|result
op_assign
id|fn
op_member_access_from_pointer
id|pre_visit_pci_bus
c_func
(paren
id|wrapped_bus
comma
id|wrapped_parent
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
r_return
id|result
suffix:semicolon
)brace
id|ln
op_assign
id|wrapped_bus-&gt;bus-&gt;devices.next
suffix:semicolon
r_while
c_loop
(paren
id|ln
op_ne
op_amp
id|wrapped_bus-&gt;bus-&gt;devices
)paren
(brace
id|dev
op_assign
id|pci_dev_b
c_func
(paren
id|ln
)paren
suffix:semicolon
id|ln
op_assign
id|ln-&gt;next
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|wrapped_dev
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|pci_dev_wrapped
)paren
)paren
suffix:semicolon
id|wrapped_dev.dev
op_assign
id|dev
suffix:semicolon
id|result
op_assign
id|pci_visit_dev
c_func
(paren
id|fn
comma
op_amp
id|wrapped_dev
comma
id|wrapped_bus
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
r_return
id|result
suffix:semicolon
)brace
r_if
c_cond
(paren
id|fn-&gt;post_visit_pci_bus
)paren
id|result
op_assign
id|fn
op_member_access_from_pointer
id|post_visit_pci_bus
c_func
(paren
id|wrapped_bus
comma
id|wrapped_parent
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|function|pci_visit_bridge
r_static
r_int
id|pci_visit_bridge
(paren
r_struct
id|pci_visit
op_star
id|fn
comma
r_struct
id|pci_dev_wrapped
op_star
id|wrapped_dev
comma
r_struct
id|pci_bus_wrapped
op_star
id|wrapped_parent
)paren
(brace
r_struct
id|pci_bus
op_star
id|bus
op_assign
id|wrapped_dev-&gt;dev-&gt;subordinate
suffix:semicolon
r_struct
id|pci_bus_wrapped
id|wrapped_bus
suffix:semicolon
r_int
id|result
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|wrapped_bus
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|pci_bus_wrapped
)paren
)paren
suffix:semicolon
id|wrapped_bus.bus
op_assign
id|bus
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;scanning bridge %02x, %02x&bslash;n&quot;
comma
id|wrapped_dev-&gt;dev-&gt;devfn
op_rshift
l_int|3
comma
id|wrapped_dev-&gt;dev-&gt;devfn
op_amp
l_int|0x7
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fn-&gt;visit_pci_dev
)paren
(brace
id|result
op_assign
id|fn
op_member_access_from_pointer
id|visit_pci_dev
c_func
(paren
id|wrapped_dev
comma
id|wrapped_parent
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
r_return
id|result
suffix:semicolon
)brace
id|result
op_assign
id|pci_visit_bus
c_func
(paren
id|fn
comma
op_amp
id|wrapped_bus
comma
id|wrapped_dev
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|function|pci_visit_dev
r_int
id|pci_visit_dev
(paren
r_struct
id|pci_visit
op_star
id|fn
comma
r_struct
id|pci_dev_wrapped
op_star
id|wrapped_dev
comma
r_struct
id|pci_bus_wrapped
op_star
id|wrapped_parent
)paren
(brace
r_struct
id|pci_dev
op_star
id|dev
op_assign
id|wrapped_dev
ques
c_cond
id|wrapped_dev-&gt;dev
suffix:colon
l_int|NULL
suffix:semicolon
r_int
id|result
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|fn-&gt;pre_visit_pci_dev
)paren
(brace
id|result
op_assign
id|fn
op_member_access_from_pointer
id|pre_visit_pci_dev
c_func
(paren
id|wrapped_dev
comma
id|wrapped_parent
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
r_return
id|result
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|dev
op_member_access_from_pointer
r_class
op_rshift
l_int|8
)paren
(brace
r_case
id|PCI_CLASS_BRIDGE_PCI
suffix:colon
id|result
op_assign
id|pci_visit_bridge
c_func
(paren
id|fn
comma
id|wrapped_dev
comma
id|wrapped_parent
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
r_return
id|result
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|dbg
c_func
(paren
l_string|&quot;scanning device %02x, %02x&bslash;n&quot;
comma
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
comma
id|PCI_FUNC
c_func
(paren
id|dev-&gt;devfn
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fn-&gt;visit_pci_dev
)paren
(brace
id|result
op_assign
id|fn-&gt;visit_pci_dev
(paren
id|wrapped_dev
comma
id|wrapped_parent
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
r_return
id|result
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|fn-&gt;post_visit_pci_dev
)paren
id|result
op_assign
id|fn
op_member_access_from_pointer
id|post_visit_pci_dev
c_func
(paren
id|wrapped_dev
comma
id|wrapped_parent
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|variable|pci_visit_dev
id|EXPORT_SYMBOL
c_func
(paren
id|pci_visit_dev
)paren
suffix:semicolon
eof
