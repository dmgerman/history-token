multiline_comment|/*&n; * Compaq Hot Plug Controller Driver&n; *&n; * Copyright (c) 1995,2001 Compaq Computer Corporation&n; * Copyright (c) 2001 Greg Kroah-Hartman (greg@kroah.com)&n; * Copyright (c) 2001 IBM Corp.&n; *&n; * All rights reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or (at&n; * your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, GOOD TITLE or&n; * NON INFRINGEMENT.  See the GNU General Public License for more&n; * details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; * Send feedback to &lt;greg@kroah.com&gt;&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/workqueue.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &quot;cpqphp.h&quot;
DECL|variable|ctrl_proc_root
r_static
r_struct
id|proc_dir_entry
op_star
id|ctrl_proc_root
suffix:semicolon
multiline_comment|/* A few routines that create proc entries for the hot plug controller */
DECL|function|read_ctrl
r_static
r_int
id|read_ctrl
(paren
r_char
op_star
id|buf
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|offset
comma
r_int
id|len
comma
r_int
op_star
id|eof
comma
r_void
op_star
id|data
)paren
(brace
r_struct
id|controller
op_star
id|ctrl
op_assign
(paren
r_struct
id|controller
op_star
)paren
id|data
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
r_if
c_cond
(paren
id|offset
OG
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* no partial requests */
id|len
op_assign
l_int|0
suffix:semicolon
op_star
id|eof
op_assign
l_int|1
suffix:semicolon
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;hot plug ctrl Info Page&bslash;n&quot;
)paren
suffix:semicolon
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;bus = %d, device = %d, function = %d&bslash;n&quot;
comma
id|ctrl-&gt;bus
comma
id|PCI_SLOT
c_func
(paren
id|ctrl-&gt;pci_dev-&gt;devfn
)paren
comma
id|PCI_FUNC
c_func
(paren
id|ctrl-&gt;pci_dev-&gt;devfn
)paren
)paren
suffix:semicolon
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
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
op_star
id|start
op_assign
id|buf
suffix:semicolon
id|len
op_assign
id|out
op_minus
id|buf
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
DECL|function|read_dev
r_static
r_int
id|read_dev
(paren
r_char
op_star
id|buf
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|offset
comma
r_int
id|len
comma
r_int
op_star
id|eof
comma
r_void
op_star
id|data
)paren
(brace
r_struct
id|controller
op_star
id|ctrl
op_assign
(paren
r_struct
id|controller
op_star
)paren
id|data
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
r_if
c_cond
(paren
id|offset
OG
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* no partial requests */
id|len
op_assign
l_int|0
suffix:semicolon
op_star
id|eof
op_assign
l_int|1
suffix:semicolon
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;hot plug ctrl Info Page&bslash;n&quot;
)paren
suffix:semicolon
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;bus = %d, device = %d, function = %d&bslash;n&quot;
comma
id|ctrl-&gt;bus
comma
id|PCI_SLOT
c_func
(paren
id|ctrl-&gt;pci_dev-&gt;devfn
)paren
comma
id|PCI_FUNC
c_func
(paren
id|ctrl-&gt;pci_dev-&gt;devfn
)paren
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
id|cpqhp_slot_find
c_func
(paren
id|slot-&gt;bus
comma
id|slot-&gt;device
comma
l_int|0
)paren
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
op_star
id|start
op_assign
id|buf
suffix:semicolon
id|len
op_assign
id|out
op_minus
id|buf
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
DECL|function|cpqhp_proc_create_ctrl
r_int
id|cpqhp_proc_create_ctrl
(paren
r_struct
id|controller
op_star
id|ctrl
)paren
(brace
id|strcpy
c_func
(paren
id|ctrl-&gt;proc_name
comma
l_string|&quot;hpca&quot;
)paren
suffix:semicolon
id|ctrl-&gt;proc_name
(braket
l_int|3
)braket
op_assign
l_char|&squot;a&squot;
op_plus
id|ctrl-&gt;bus
suffix:semicolon
id|ctrl-&gt;proc_entry
op_assign
id|create_proc_entry
c_func
(paren
id|ctrl-&gt;proc_name
comma
id|S_IFREG
op_or
id|S_IRUGO
comma
id|ctrl_proc_root
)paren
suffix:semicolon
id|ctrl-&gt;proc_entry-&gt;data
op_assign
id|ctrl
suffix:semicolon
id|ctrl-&gt;proc_entry-&gt;read_proc
op_assign
op_amp
id|read_ctrl
suffix:semicolon
id|strcpy
c_func
(paren
id|ctrl-&gt;proc_name2
comma
l_string|&quot;slot_a&quot;
)paren
suffix:semicolon
id|ctrl-&gt;proc_name2
(braket
l_int|5
)braket
op_assign
l_char|&squot;a&squot;
op_plus
id|ctrl-&gt;bus
suffix:semicolon
id|ctrl-&gt;proc_entry2
op_assign
id|create_proc_entry
c_func
(paren
id|ctrl-&gt;proc_name2
comma
id|S_IFREG
op_or
id|S_IRUGO
comma
id|ctrl_proc_root
)paren
suffix:semicolon
id|ctrl-&gt;proc_entry2-&gt;data
op_assign
id|ctrl
suffix:semicolon
id|ctrl-&gt;proc_entry2-&gt;read_proc
op_assign
op_amp
id|read_dev
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cpqhp_proc_remove_ctrl
r_int
id|cpqhp_proc_remove_ctrl
(paren
r_struct
id|controller
op_star
id|ctrl
)paren
(brace
r_if
c_cond
(paren
id|ctrl-&gt;proc_entry
)paren
id|remove_proc_entry
c_func
(paren
id|ctrl-&gt;proc_name
comma
id|ctrl_proc_root
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ctrl-&gt;proc_entry2
)paren
id|remove_proc_entry
c_func
(paren
id|ctrl-&gt;proc_name2
comma
id|ctrl_proc_root
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cpqhp_proc_init_ctrl
r_int
id|cpqhp_proc_init_ctrl
(paren
r_void
)paren
(brace
id|ctrl_proc_root
op_assign
id|proc_mkdir
c_func
(paren
l_string|&quot;hpc&quot;
comma
id|proc_root_driver
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ctrl_proc_root
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|ctrl_proc_root-&gt;owner
op_assign
id|THIS_MODULE
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cpqhp_proc_destroy_ctrl
r_int
id|cpqhp_proc_destroy_ctrl
(paren
r_void
)paren
(brace
id|remove_proc_entry
c_func
(paren
l_string|&quot;hpc&quot;
comma
id|proc_root_driver
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
