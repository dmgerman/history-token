multiline_comment|/*&n; * PCI Express Hot Plug Controller Driver&n; *&n; * Copyright (C) 1995,2001 Compaq Computer Corporation&n; * Copyright (C) 2001,2003 Greg Kroah-Hartman (greg@kroah.com)&n; * Copyright (C) 2001 IBM Corp.&n; *&n; * All rights reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or (at&n; * your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, GOOD TITLE or&n; * NON INFRINGEMENT.  See the GNU General Public License for more&n; * details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; * Send feedback to &lt;greg@kroah.com&gt;&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/workqueue.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &quot;pciehp.h&quot;
multiline_comment|/* A few routines that create sysfs entries for the hot plug controller */
DECL|function|show_ctrl
r_static
id|ssize_t
id|show_ctrl
(paren
r_struct
id|device
op_star
id|dev
comma
r_char
op_star
id|buf
)paren
(brace
r_struct
id|pci_dev
op_star
id|pci_dev
suffix:semicolon
r_struct
id|controller
op_star
id|ctrl
suffix:semicolon
r_char
op_star
id|out
op_assign
id|buf
suffix:semicolon
r_int
id|index
suffix:semicolon
r_struct
id|pci_resource
op_star
id|res
suffix:semicolon
id|pci_dev
op_assign
id|container_of
(paren
id|dev
comma
r_struct
id|pci_dev
comma
id|dev
)paren
suffix:semicolon
id|ctrl
op_assign
id|pci_get_drvdata
c_func
(paren
id|pci_dev
)paren
suffix:semicolon
id|out
op_add_assign
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;Free resources: memory&bslash;n&quot;
)paren
suffix:semicolon
id|index
op_assign
l_int|11
suffix:semicolon
id|res
op_assign
id|ctrl-&gt;mem_head
suffix:semicolon
r_while
c_loop
(paren
id|res
op_logical_and
id|index
op_decrement
)paren
(brace
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;start = %8.8x, length = %8.8x&bslash;n&quot;
comma
id|res-&gt;base
comma
id|res-&gt;length
)paren
suffix:semicolon
id|res
op_assign
id|res-&gt;next
suffix:semicolon
)brace
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;Free resources: prefetchable memory&bslash;n&quot;
)paren
suffix:semicolon
id|index
op_assign
l_int|11
suffix:semicolon
id|res
op_assign
id|ctrl-&gt;p_mem_head
suffix:semicolon
r_while
c_loop
(paren
id|res
op_logical_and
id|index
op_decrement
)paren
(brace
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;start = %8.8x, length = %8.8x&bslash;n&quot;
comma
id|res-&gt;base
comma
id|res-&gt;length
)paren
suffix:semicolon
id|res
op_assign
id|res-&gt;next
suffix:semicolon
)brace
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;Free resources: IO&bslash;n&quot;
)paren
suffix:semicolon
id|index
op_assign
l_int|11
suffix:semicolon
id|res
op_assign
id|ctrl-&gt;io_head
suffix:semicolon
r_while
c_loop
(paren
id|res
op_logical_and
id|index
op_decrement
)paren
(brace
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;start = %8.8x, length = %8.8x&bslash;n&quot;
comma
id|res-&gt;base
comma
id|res-&gt;length
)paren
suffix:semicolon
id|res
op_assign
id|res-&gt;next
suffix:semicolon
)brace
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;Free resources: bus numbers&bslash;n&quot;
)paren
suffix:semicolon
id|index
op_assign
l_int|11
suffix:semicolon
id|res
op_assign
id|ctrl-&gt;bus_head
suffix:semicolon
r_while
c_loop
(paren
id|res
op_logical_and
id|index
op_decrement
)paren
(brace
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;start = %8.8x, length = %8.8x&bslash;n&quot;
comma
id|res-&gt;base
comma
id|res-&gt;length
)paren
suffix:semicolon
id|res
op_assign
id|res-&gt;next
suffix:semicolon
)brace
r_return
id|out
op_minus
id|buf
suffix:semicolon
)brace
r_static
id|DEVICE_ATTR
(paren
id|ctrl
comma
id|S_IRUGO
comma
id|show_ctrl
comma
l_int|NULL
)paren
suffix:semicolon
DECL|function|show_dev
r_static
id|ssize_t
id|show_dev
(paren
r_struct
id|device
op_star
id|dev
comma
r_char
op_star
id|buf
)paren
(brace
r_struct
id|pci_dev
op_star
id|pci_dev
suffix:semicolon
r_struct
id|controller
op_star
id|ctrl
suffix:semicolon
r_char
op_star
id|out
op_assign
id|buf
suffix:semicolon
r_int
id|index
suffix:semicolon
r_struct
id|pci_resource
op_star
id|res
suffix:semicolon
r_struct
id|pci_func
op_star
id|new_slot
suffix:semicolon
r_struct
id|slot
op_star
id|slot
suffix:semicolon
id|pci_dev
op_assign
id|container_of
(paren
id|dev
comma
r_struct
id|pci_dev
comma
id|dev
)paren
suffix:semicolon
id|ctrl
op_assign
id|pci_get_drvdata
c_func
(paren
id|pci_dev
)paren
suffix:semicolon
id|slot
op_assign
id|ctrl-&gt;slot
suffix:semicolon
r_while
c_loop
(paren
id|slot
)paren
(brace
id|new_slot
op_assign
id|pciehp_slot_find
c_func
(paren
id|slot-&gt;bus
comma
id|slot-&gt;device
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|new_slot
)paren
r_break
suffix:semicolon
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;assigned resources: memory&bslash;n&quot;
)paren
suffix:semicolon
id|index
op_assign
l_int|11
suffix:semicolon
id|res
op_assign
id|new_slot-&gt;mem_head
suffix:semicolon
r_while
c_loop
(paren
id|res
op_logical_and
id|index
op_decrement
)paren
(brace
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;start = %8.8x, length = %8.8x&bslash;n&quot;
comma
id|res-&gt;base
comma
id|res-&gt;length
)paren
suffix:semicolon
id|res
op_assign
id|res-&gt;next
suffix:semicolon
)brace
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;assigned resources: prefetchable memory&bslash;n&quot;
)paren
suffix:semicolon
id|index
op_assign
l_int|11
suffix:semicolon
id|res
op_assign
id|new_slot-&gt;p_mem_head
suffix:semicolon
r_while
c_loop
(paren
id|res
op_logical_and
id|index
op_decrement
)paren
(brace
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;start = %8.8x, length = %8.8x&bslash;n&quot;
comma
id|res-&gt;base
comma
id|res-&gt;length
)paren
suffix:semicolon
id|res
op_assign
id|res-&gt;next
suffix:semicolon
)brace
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;assigned resources: IO&bslash;n&quot;
)paren
suffix:semicolon
id|index
op_assign
l_int|11
suffix:semicolon
id|res
op_assign
id|new_slot-&gt;io_head
suffix:semicolon
r_while
c_loop
(paren
id|res
op_logical_and
id|index
op_decrement
)paren
(brace
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;start = %8.8x, length = %8.8x&bslash;n&quot;
comma
id|res-&gt;base
comma
id|res-&gt;length
)paren
suffix:semicolon
id|res
op_assign
id|res-&gt;next
suffix:semicolon
)brace
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;assigned resources: bus numbers&bslash;n&quot;
)paren
suffix:semicolon
id|index
op_assign
l_int|11
suffix:semicolon
id|res
op_assign
id|new_slot-&gt;bus_head
suffix:semicolon
r_while
c_loop
(paren
id|res
op_logical_and
id|index
op_decrement
)paren
(brace
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;start = %8.8x, length = %8.8x&bslash;n&quot;
comma
id|res-&gt;base
comma
id|res-&gt;length
)paren
suffix:semicolon
id|res
op_assign
id|res-&gt;next
suffix:semicolon
)brace
id|slot
op_assign
id|slot-&gt;next
suffix:semicolon
)brace
r_return
id|out
op_minus
id|buf
suffix:semicolon
)brace
r_static
id|DEVICE_ATTR
(paren
id|dev
comma
id|S_IRUGO
comma
id|show_dev
comma
l_int|NULL
)paren
suffix:semicolon
DECL|function|pciehp_create_ctrl_files
r_void
id|pciehp_create_ctrl_files
(paren
r_struct
id|controller
op_star
id|ctrl
)paren
(brace
id|device_create_file
(paren
op_amp
id|ctrl-&gt;pci_dev-&gt;dev
comma
op_amp
id|dev_attr_ctrl
)paren
suffix:semicolon
id|device_create_file
(paren
op_amp
id|ctrl-&gt;pci_dev-&gt;dev
comma
op_amp
id|dev_attr_dev
)paren
suffix:semicolon
)brace
eof
