multiline_comment|/*&n; * Compaq Hot Plug Controller Driver&n; *&n; * Copyright (C) 1995,2001 Compaq Computer Corporation&n; * Copyright (C) 2001 Greg Kroah-Hartman (greg@kroah.com)&n; * Copyright (C) 2001 IBM Corp.&n; *&n; * All rights reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or (at&n; * your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, GOOD TITLE or&n; * NON INFRINGEMENT.  See the GNU General Public License for more&n; * details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; * Send feedback to &lt;greg@kroah.com&gt;&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/workqueue.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &quot;cpqphp.h&quot;
macro_line|#include &quot;cpqphp_nvram.h&quot;
DECL|macro|ROM_INT15_PHY_ADDR
mdefine_line|#define ROM_INT15_PHY_ADDR&t;&t;0x0FF859
DECL|macro|READ_EV
mdefine_line|#define READ_EV&t;&t;&t;&t;0xD8A4
DECL|macro|WRITE_EV
mdefine_line|#define WRITE_EV&t;&t;&t;0xD8A5
DECL|struct|register_foo
r_struct
id|register_foo
(brace
r_union
(brace
DECL|member|lword
r_int
r_int
id|lword
suffix:semicolon
multiline_comment|/* eax */
DECL|member|word
r_int
r_int
id|word
suffix:semicolon
multiline_comment|/* ax */
r_struct
(brace
DECL|member|low
r_int
r_char
id|low
suffix:semicolon
multiline_comment|/* al */
DECL|member|high
r_int
r_char
id|high
suffix:semicolon
multiline_comment|/* ah */
DECL|member|byte
)brace
id|byte
suffix:semicolon
DECL|member|data
)brace
id|data
suffix:semicolon
DECL|member|opcode
r_int
r_char
id|opcode
suffix:semicolon
multiline_comment|/* see below */
DECL|member|length
r_int
r_int
id|length
suffix:semicolon
multiline_comment|/* if the reg. is a pointer, how much data */
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|all_reg
r_struct
id|all_reg
(brace
DECL|member|eax_reg
r_struct
id|register_foo
id|eax_reg
suffix:semicolon
DECL|member|ebx_reg
r_struct
id|register_foo
id|ebx_reg
suffix:semicolon
DECL|member|ecx_reg
r_struct
id|register_foo
id|ecx_reg
suffix:semicolon
DECL|member|edx_reg
r_struct
id|register_foo
id|edx_reg
suffix:semicolon
DECL|member|edi_reg
r_struct
id|register_foo
id|edi_reg
suffix:semicolon
DECL|member|esi_reg
r_struct
id|register_foo
id|esi_reg
suffix:semicolon
DECL|member|eflags_reg
r_struct
id|register_foo
id|eflags_reg
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|ev_hrt_header
r_struct
id|ev_hrt_header
(brace
DECL|member|Version
id|u8
id|Version
suffix:semicolon
DECL|member|num_of_ctrl
id|u8
id|num_of_ctrl
suffix:semicolon
DECL|member|next
id|u8
id|next
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ev_hrt_ctrl
r_struct
id|ev_hrt_ctrl
(brace
DECL|member|bus
id|u8
id|bus
suffix:semicolon
DECL|member|device
id|u8
id|device
suffix:semicolon
DECL|member|function
id|u8
id|function
suffix:semicolon
DECL|member|mem_avail
id|u8
id|mem_avail
suffix:semicolon
DECL|member|p_mem_avail
id|u8
id|p_mem_avail
suffix:semicolon
DECL|member|io_avail
id|u8
id|io_avail
suffix:semicolon
DECL|member|bus_avail
id|u8
id|bus_avail
suffix:semicolon
DECL|member|next
id|u8
id|next
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|evbuffer_init
r_static
id|u8
id|evbuffer_init
suffix:semicolon
DECL|variable|evbuffer_length
r_static
id|u8
id|evbuffer_length
suffix:semicolon
DECL|variable|evbuffer
r_static
id|u8
id|evbuffer
(braket
l_int|1024
)braket
suffix:semicolon
DECL|variable|compaq_int15_entry_point
r_static
r_void
op_star
id|compaq_int15_entry_point
suffix:semicolon
DECL|variable|int15_lock
r_static
id|spinlock_t
id|int15_lock
suffix:semicolon
multiline_comment|/* lock for ordering int15_bios_call() */
multiline_comment|/* This is a series of function that deals with&n;   setting &amp; getting the hotplug resource table in some environment variable.&n;*/
multiline_comment|/*&n; * We really shouldn&squot;t be doing this unless there is a _very_ good reason to!!!&n; * greg k-h&n; */
DECL|function|add_byte
r_static
id|u32
id|add_byte
c_func
(paren
id|u32
op_star
op_star
id|p_buffer
comma
id|u8
id|value
comma
id|u32
op_star
id|used
comma
id|u32
op_star
id|avail
)paren
(brace
id|u8
op_star
op_star
id|tByte
suffix:semicolon
r_if
c_cond
(paren
(paren
op_star
id|used
op_plus
l_int|1
)paren
OG
op_star
id|avail
)paren
r_return
l_int|1
suffix:semicolon
op_star
(paren
(paren
id|u8
op_star
)paren
op_star
id|p_buffer
)paren
op_assign
id|value
suffix:semicolon
id|tByte
op_assign
(paren
id|u8
op_star
op_star
)paren
id|p_buffer
suffix:semicolon
(paren
op_star
id|tByte
)paren
op_increment
suffix:semicolon
op_star
id|used
op_add_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|add_dword
r_static
id|u32
id|add_dword
c_func
(paren
id|u32
op_star
op_star
id|p_buffer
comma
id|u32
id|value
comma
id|u32
op_star
id|used
comma
id|u32
op_star
id|avail
)paren
(brace
r_if
c_cond
(paren
(paren
op_star
id|used
op_plus
l_int|4
)paren
OG
op_star
id|avail
)paren
r_return
l_int|1
suffix:semicolon
op_star
op_star
id|p_buffer
op_assign
id|value
suffix:semicolon
(paren
op_star
id|p_buffer
)paren
op_increment
suffix:semicolon
op_star
id|used
op_add_assign
l_int|4
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * check_for_compaq_ROM&n; *&n; * this routine verifies that the ROM OEM string is &squot;COMPAQ&squot;&n; *&n; * returns 0 for non-Compaq ROM, 1 for Compaq ROM&n; */
DECL|function|check_for_compaq_ROM
r_static
r_int
id|check_for_compaq_ROM
(paren
r_void
id|__iomem
op_star
id|rom_start
)paren
(brace
id|u8
id|temp1
comma
id|temp2
comma
id|temp3
comma
id|temp4
comma
id|temp5
comma
id|temp6
suffix:semicolon
r_int
id|result
op_assign
l_int|0
suffix:semicolon
id|temp1
op_assign
id|readb
c_func
(paren
id|rom_start
op_plus
l_int|0xffea
op_plus
l_int|0
)paren
suffix:semicolon
id|temp2
op_assign
id|readb
c_func
(paren
id|rom_start
op_plus
l_int|0xffea
op_plus
l_int|1
)paren
suffix:semicolon
id|temp3
op_assign
id|readb
c_func
(paren
id|rom_start
op_plus
l_int|0xffea
op_plus
l_int|2
)paren
suffix:semicolon
id|temp4
op_assign
id|readb
c_func
(paren
id|rom_start
op_plus
l_int|0xffea
op_plus
l_int|3
)paren
suffix:semicolon
id|temp5
op_assign
id|readb
c_func
(paren
id|rom_start
op_plus
l_int|0xffea
op_plus
l_int|4
)paren
suffix:semicolon
id|temp6
op_assign
id|readb
c_func
(paren
id|rom_start
op_plus
l_int|0xffea
op_plus
l_int|5
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|temp1
op_eq
l_char|&squot;C&squot;
)paren
op_logical_and
(paren
id|temp2
op_eq
l_char|&squot;O&squot;
)paren
op_logical_and
(paren
id|temp3
op_eq
l_char|&squot;M&squot;
)paren
op_logical_and
(paren
id|temp4
op_eq
l_char|&squot;P&squot;
)paren
op_logical_and
(paren
id|temp5
op_eq
l_char|&squot;A&squot;
)paren
op_logical_and
(paren
id|temp6
op_eq
l_char|&squot;Q&squot;
)paren
)paren
(brace
id|result
op_assign
l_int|1
suffix:semicolon
)brace
id|dbg
(paren
l_string|&quot;%s - returned %d&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|result
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|function|access_EV
r_static
id|u32
id|access_EV
(paren
id|u16
id|operation
comma
id|u8
op_star
id|ev_name
comma
id|u8
op_star
id|buffer
comma
id|u32
op_star
id|buf_size
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
id|op
op_assign
id|operation
suffix:semicolon
r_int
id|ret_val
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|compaq_int15_entry_point
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|int15_lock
comma
id|flags
)paren
suffix:semicolon
id|__asm__
(paren
l_string|&quot;xorl   %%ebx,%%ebx&bslash;n&quot;
"&bslash;"
l_string|&quot;xorl    %%edx,%%edx&bslash;n&quot;
"&bslash;"
l_string|&quot;pushf&bslash;n&quot;
"&bslash;"
l_string|&quot;push %%cs&bslash;n&quot;
"&bslash;"
l_string|&quot;cli&bslash;n&quot;
"&bslash;"
l_string|&quot;call *%6&bslash;n&quot;
suffix:colon
l_string|&quot;=c&quot;
(paren
op_star
id|buf_size
)paren
comma
l_string|&quot;=a&quot;
(paren
id|ret_val
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|op
)paren
comma
l_string|&quot;c&quot;
(paren
op_star
id|buf_size
)paren
comma
l_string|&quot;S&quot;
(paren
id|ev_name
)paren
comma
l_string|&quot;D&quot;
(paren
id|buffer
)paren
comma
l_string|&quot;m&quot;
(paren
id|compaq_int15_entry_point
)paren
suffix:colon
l_string|&quot;%ebx&quot;
comma
l_string|&quot;%edx&quot;
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|int15_lock
comma
id|flags
)paren
suffix:semicolon
r_return
(paren
id|ret_val
op_amp
l_int|0xFF00
)paren
op_rshift
l_int|8
suffix:semicolon
)brace
multiline_comment|/*&n; * load_HRT&n; *&n; * Read the hot plug Resource Table from NVRAM&n; */
DECL|function|load_HRT
r_static
r_int
id|load_HRT
(paren
r_void
id|__iomem
op_star
id|rom_start
)paren
(brace
id|u32
id|available
suffix:semicolon
id|u32
id|temp_dword
suffix:semicolon
id|u8
id|temp_byte
op_assign
l_int|0xFF
suffix:semicolon
id|u32
id|rc
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|check_for_compaq_ROM
c_func
(paren
id|rom_start
)paren
)paren
(brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|available
op_assign
l_int|1024
suffix:semicolon
singleline_comment|// Now load the EV
id|temp_dword
op_assign
id|available
suffix:semicolon
id|rc
op_assign
id|access_EV
c_func
(paren
id|READ_EV
comma
l_string|&quot;CQTHPS&quot;
comma
id|evbuffer
comma
op_amp
id|temp_dword
)paren
suffix:semicolon
id|evbuffer_length
op_assign
id|temp_dword
suffix:semicolon
singleline_comment|// We&squot;re maintaining the resource lists so write FF to invalidate old info
id|temp_dword
op_assign
l_int|1
suffix:semicolon
id|rc
op_assign
id|access_EV
c_func
(paren
id|WRITE_EV
comma
l_string|&quot;CQTHPS&quot;
comma
op_amp
id|temp_byte
comma
op_amp
id|temp_dword
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
multiline_comment|/*&n; * store_HRT&n; *&n; * Save the hot plug Resource Table in NVRAM&n; */
DECL|function|store_HRT
r_static
id|u32
id|store_HRT
(paren
r_void
id|__iomem
op_star
id|rom_start
)paren
(brace
id|u32
op_star
id|buffer
suffix:semicolon
id|u32
op_star
id|pFill
suffix:semicolon
id|u32
id|usedbytes
suffix:semicolon
id|u32
id|available
suffix:semicolon
id|u32
id|temp_dword
suffix:semicolon
id|u32
id|rc
suffix:semicolon
id|u8
id|loop
suffix:semicolon
id|u8
id|numCtrl
op_assign
l_int|0
suffix:semicolon
r_struct
id|controller
op_star
id|ctrl
suffix:semicolon
r_struct
id|pci_resource
op_star
id|resNode
suffix:semicolon
r_struct
id|ev_hrt_header
op_star
id|p_EV_header
suffix:semicolon
r_struct
id|ev_hrt_ctrl
op_star
id|p_ev_ctrl
suffix:semicolon
id|available
op_assign
l_int|1024
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|check_for_compaq_ROM
c_func
(paren
id|rom_start
)paren
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
id|buffer
op_assign
(paren
id|u32
op_star
)paren
id|evbuffer
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buffer
)paren
r_return
l_int|1
suffix:semicolon
id|pFill
op_assign
id|buffer
suffix:semicolon
id|usedbytes
op_assign
l_int|0
suffix:semicolon
id|p_EV_header
op_assign
(paren
r_struct
id|ev_hrt_header
op_star
)paren
id|pFill
suffix:semicolon
id|ctrl
op_assign
id|cpqhp_ctrl_list
suffix:semicolon
singleline_comment|// The revision of this structure
id|rc
op_assign
id|add_byte
c_func
(paren
op_amp
id|pFill
comma
l_int|1
op_plus
id|ctrl-&gt;push_flag
comma
op_amp
id|usedbytes
comma
op_amp
id|available
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
r_return
id|rc
suffix:semicolon
singleline_comment|// The number of controllers
id|rc
op_assign
id|add_byte
c_func
(paren
op_amp
id|pFill
comma
l_int|1
comma
op_amp
id|usedbytes
comma
op_amp
id|available
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
r_return
id|rc
suffix:semicolon
r_while
c_loop
(paren
id|ctrl
)paren
(brace
id|p_ev_ctrl
op_assign
(paren
r_struct
id|ev_hrt_ctrl
op_star
)paren
id|pFill
suffix:semicolon
id|numCtrl
op_increment
suffix:semicolon
singleline_comment|// The bus number
id|rc
op_assign
id|add_byte
c_func
(paren
op_amp
id|pFill
comma
id|ctrl-&gt;bus
comma
op_amp
id|usedbytes
comma
op_amp
id|available
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
r_return
id|rc
suffix:semicolon
singleline_comment|// The device Number
id|rc
op_assign
id|add_byte
c_func
(paren
op_amp
id|pFill
comma
id|PCI_SLOT
c_func
(paren
id|ctrl-&gt;pci_dev-&gt;devfn
)paren
comma
op_amp
id|usedbytes
comma
op_amp
id|available
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
r_return
id|rc
suffix:semicolon
singleline_comment|// The function Number
id|rc
op_assign
id|add_byte
c_func
(paren
op_amp
id|pFill
comma
id|PCI_FUNC
c_func
(paren
id|ctrl-&gt;pci_dev-&gt;devfn
)paren
comma
op_amp
id|usedbytes
comma
op_amp
id|available
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
r_return
id|rc
suffix:semicolon
singleline_comment|// Skip the number of available entries
id|rc
op_assign
id|add_dword
c_func
(paren
op_amp
id|pFill
comma
l_int|0
comma
op_amp
id|usedbytes
comma
op_amp
id|available
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
r_return
id|rc
suffix:semicolon
singleline_comment|// Figure out memory Available
id|resNode
op_assign
id|ctrl-&gt;mem_head
suffix:semicolon
id|loop
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|resNode
)paren
(brace
id|loop
op_increment
suffix:semicolon
singleline_comment|// base
id|rc
op_assign
id|add_dword
c_func
(paren
op_amp
id|pFill
comma
id|resNode-&gt;base
comma
op_amp
id|usedbytes
comma
op_amp
id|available
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
r_return
id|rc
suffix:semicolon
singleline_comment|// length
id|rc
op_assign
id|add_dword
c_func
(paren
op_amp
id|pFill
comma
id|resNode-&gt;length
comma
op_amp
id|usedbytes
comma
op_amp
id|available
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
r_return
id|rc
suffix:semicolon
id|resNode
op_assign
id|resNode-&gt;next
suffix:semicolon
)brace
singleline_comment|// Fill in the number of entries
id|p_ev_ctrl-&gt;mem_avail
op_assign
id|loop
suffix:semicolon
singleline_comment|// Figure out prefetchable memory Available
id|resNode
op_assign
id|ctrl-&gt;p_mem_head
suffix:semicolon
id|loop
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|resNode
)paren
(brace
id|loop
op_increment
suffix:semicolon
singleline_comment|// base
id|rc
op_assign
id|add_dword
c_func
(paren
op_amp
id|pFill
comma
id|resNode-&gt;base
comma
op_amp
id|usedbytes
comma
op_amp
id|available
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
r_return
id|rc
suffix:semicolon
singleline_comment|// length
id|rc
op_assign
id|add_dword
c_func
(paren
op_amp
id|pFill
comma
id|resNode-&gt;length
comma
op_amp
id|usedbytes
comma
op_amp
id|available
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
r_return
id|rc
suffix:semicolon
id|resNode
op_assign
id|resNode-&gt;next
suffix:semicolon
)brace
singleline_comment|// Fill in the number of entries
id|p_ev_ctrl-&gt;p_mem_avail
op_assign
id|loop
suffix:semicolon
singleline_comment|// Figure out IO Available
id|resNode
op_assign
id|ctrl-&gt;io_head
suffix:semicolon
id|loop
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|resNode
)paren
(brace
id|loop
op_increment
suffix:semicolon
singleline_comment|// base
id|rc
op_assign
id|add_dword
c_func
(paren
op_amp
id|pFill
comma
id|resNode-&gt;base
comma
op_amp
id|usedbytes
comma
op_amp
id|available
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
r_return
id|rc
suffix:semicolon
singleline_comment|// length
id|rc
op_assign
id|add_dword
c_func
(paren
op_amp
id|pFill
comma
id|resNode-&gt;length
comma
op_amp
id|usedbytes
comma
op_amp
id|available
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
r_return
id|rc
suffix:semicolon
id|resNode
op_assign
id|resNode-&gt;next
suffix:semicolon
)brace
singleline_comment|// Fill in the number of entries
id|p_ev_ctrl-&gt;io_avail
op_assign
id|loop
suffix:semicolon
singleline_comment|// Figure out bus Available
id|resNode
op_assign
id|ctrl-&gt;bus_head
suffix:semicolon
id|loop
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|resNode
)paren
(brace
id|loop
op_increment
suffix:semicolon
singleline_comment|// base
id|rc
op_assign
id|add_dword
c_func
(paren
op_amp
id|pFill
comma
id|resNode-&gt;base
comma
op_amp
id|usedbytes
comma
op_amp
id|available
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
r_return
id|rc
suffix:semicolon
singleline_comment|// length
id|rc
op_assign
id|add_dword
c_func
(paren
op_amp
id|pFill
comma
id|resNode-&gt;length
comma
op_amp
id|usedbytes
comma
op_amp
id|available
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
r_return
id|rc
suffix:semicolon
id|resNode
op_assign
id|resNode-&gt;next
suffix:semicolon
)brace
singleline_comment|// Fill in the number of entries
id|p_ev_ctrl-&gt;bus_avail
op_assign
id|loop
suffix:semicolon
id|ctrl
op_assign
id|ctrl-&gt;next
suffix:semicolon
)brace
id|p_EV_header-&gt;num_of_ctrl
op_assign
id|numCtrl
suffix:semicolon
singleline_comment|// Now store the EV
id|temp_dword
op_assign
id|usedbytes
suffix:semicolon
id|rc
op_assign
id|access_EV
c_func
(paren
id|WRITE_EV
comma
l_string|&quot;CQTHPS&quot;
comma
(paren
id|u8
op_star
)paren
id|buffer
comma
op_amp
id|temp_dword
)paren
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;usedbytes = 0x%x, length = 0x%x&bslash;n&quot;
comma
id|usedbytes
comma
id|temp_dword
)paren
suffix:semicolon
id|evbuffer_length
op_assign
id|temp_dword
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
(brace
id|err
c_func
(paren
id|msg_unable_to_save
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|compaq_nvram_init
r_void
id|compaq_nvram_init
(paren
r_void
id|__iomem
op_star
id|rom_start
)paren
(brace
r_if
c_cond
(paren
id|rom_start
)paren
(brace
id|compaq_int15_entry_point
op_assign
(paren
id|rom_start
op_plus
id|ROM_INT15_PHY_ADDR
op_minus
id|ROM_PHY_ADDR
)paren
suffix:semicolon
)brace
id|dbg
c_func
(paren
l_string|&quot;int15 entry  = %p&bslash;n&quot;
comma
id|compaq_int15_entry_point
)paren
suffix:semicolon
multiline_comment|/* initialize our int15 lock */
id|spin_lock_init
c_func
(paren
op_amp
id|int15_lock
)paren
suffix:semicolon
)brace
DECL|function|compaq_nvram_load
r_int
id|compaq_nvram_load
(paren
r_void
id|__iomem
op_star
id|rom_start
comma
r_struct
id|controller
op_star
id|ctrl
)paren
(brace
id|u8
id|bus
comma
id|device
comma
id|function
suffix:semicolon
id|u8
id|nummem
comma
id|numpmem
comma
id|numio
comma
id|numbus
suffix:semicolon
id|u32
id|rc
suffix:semicolon
id|u8
op_star
id|p_byte
suffix:semicolon
r_struct
id|pci_resource
op_star
id|mem_node
suffix:semicolon
r_struct
id|pci_resource
op_star
id|p_mem_node
suffix:semicolon
r_struct
id|pci_resource
op_star
id|io_node
suffix:semicolon
r_struct
id|pci_resource
op_star
id|bus_node
suffix:semicolon
r_struct
id|ev_hrt_ctrl
op_star
id|p_ev_ctrl
suffix:semicolon
r_struct
id|ev_hrt_header
op_star
id|p_EV_header
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|evbuffer_init
)paren
(brace
singleline_comment|// Read the resource list information in from NVRAM
r_if
c_cond
(paren
id|load_HRT
c_func
(paren
id|rom_start
)paren
)paren
id|memset
(paren
id|evbuffer
comma
l_int|0
comma
l_int|1024
)paren
suffix:semicolon
id|evbuffer_init
op_assign
l_int|1
suffix:semicolon
)brace
singleline_comment|// If we saved information in NVRAM, use it now
id|p_EV_header
op_assign
(paren
r_struct
id|ev_hrt_header
op_star
)paren
id|evbuffer
suffix:semicolon
singleline_comment|// The following code is for systems where version 1.0 of this
singleline_comment|// driver has been loaded, but doesn&squot;t support the hardware.
singleline_comment|// In that case, the driver would incorrectly store something
singleline_comment|// in NVRAM.
r_if
c_cond
(paren
(paren
id|p_EV_header-&gt;Version
op_eq
l_int|2
)paren
op_logical_or
(paren
(paren
id|p_EV_header-&gt;Version
op_eq
l_int|1
)paren
op_logical_and
op_logical_neg
id|ctrl-&gt;push_flag
)paren
)paren
(brace
id|p_byte
op_assign
op_amp
(paren
id|p_EV_header-&gt;next
)paren
suffix:semicolon
id|p_ev_ctrl
op_assign
(paren
r_struct
id|ev_hrt_ctrl
op_star
)paren
op_amp
(paren
id|p_EV_header-&gt;next
)paren
suffix:semicolon
id|p_byte
op_add_assign
l_int|3
suffix:semicolon
r_if
c_cond
(paren
id|p_byte
OG
(paren
(paren
id|u8
op_star
)paren
id|p_EV_header
op_plus
id|evbuffer_length
)paren
)paren
r_return
l_int|2
suffix:semicolon
id|bus
op_assign
id|p_ev_ctrl-&gt;bus
suffix:semicolon
id|device
op_assign
id|p_ev_ctrl-&gt;device
suffix:semicolon
id|function
op_assign
id|p_ev_ctrl-&gt;function
suffix:semicolon
r_while
c_loop
(paren
(paren
id|bus
op_ne
id|ctrl-&gt;bus
)paren
op_logical_or
(paren
id|device
op_ne
id|PCI_SLOT
c_func
(paren
id|ctrl-&gt;pci_dev-&gt;devfn
)paren
)paren
op_logical_or
(paren
id|function
op_ne
id|PCI_FUNC
c_func
(paren
id|ctrl-&gt;pci_dev-&gt;devfn
)paren
)paren
)paren
(brace
id|nummem
op_assign
id|p_ev_ctrl-&gt;mem_avail
suffix:semicolon
id|numpmem
op_assign
id|p_ev_ctrl-&gt;p_mem_avail
suffix:semicolon
id|numio
op_assign
id|p_ev_ctrl-&gt;io_avail
suffix:semicolon
id|numbus
op_assign
id|p_ev_ctrl-&gt;bus_avail
suffix:semicolon
id|p_byte
op_add_assign
l_int|4
suffix:semicolon
r_if
c_cond
(paren
id|p_byte
OG
(paren
(paren
id|u8
op_star
)paren
id|p_EV_header
op_plus
id|evbuffer_length
)paren
)paren
r_return
l_int|2
suffix:semicolon
singleline_comment|// Skip forward to the next entry
id|p_byte
op_add_assign
(paren
id|nummem
op_plus
id|numpmem
op_plus
id|numio
op_plus
id|numbus
)paren
op_star
l_int|8
suffix:semicolon
r_if
c_cond
(paren
id|p_byte
OG
(paren
(paren
id|u8
op_star
)paren
id|p_EV_header
op_plus
id|evbuffer_length
)paren
)paren
r_return
l_int|2
suffix:semicolon
id|p_ev_ctrl
op_assign
(paren
r_struct
id|ev_hrt_ctrl
op_star
)paren
id|p_byte
suffix:semicolon
id|p_byte
op_add_assign
l_int|3
suffix:semicolon
r_if
c_cond
(paren
id|p_byte
OG
(paren
(paren
id|u8
op_star
)paren
id|p_EV_header
op_plus
id|evbuffer_length
)paren
)paren
r_return
l_int|2
suffix:semicolon
id|bus
op_assign
id|p_ev_ctrl-&gt;bus
suffix:semicolon
id|device
op_assign
id|p_ev_ctrl-&gt;device
suffix:semicolon
id|function
op_assign
id|p_ev_ctrl-&gt;function
suffix:semicolon
)brace
id|nummem
op_assign
id|p_ev_ctrl-&gt;mem_avail
suffix:semicolon
id|numpmem
op_assign
id|p_ev_ctrl-&gt;p_mem_avail
suffix:semicolon
id|numio
op_assign
id|p_ev_ctrl-&gt;io_avail
suffix:semicolon
id|numbus
op_assign
id|p_ev_ctrl-&gt;bus_avail
suffix:semicolon
id|p_byte
op_add_assign
l_int|4
suffix:semicolon
r_if
c_cond
(paren
id|p_byte
OG
(paren
(paren
id|u8
op_star
)paren
id|p_EV_header
op_plus
id|evbuffer_length
)paren
)paren
r_return
l_int|2
suffix:semicolon
r_while
c_loop
(paren
id|nummem
op_decrement
)paren
(brace
id|mem_node
op_assign
(paren
r_struct
id|pci_resource
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|pci_resource
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mem_node
)paren
r_break
suffix:semicolon
id|mem_node-&gt;base
op_assign
op_star
(paren
id|u32
op_star
)paren
id|p_byte
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;mem base = %8.8x&bslash;n&quot;
comma
id|mem_node-&gt;base
)paren
suffix:semicolon
id|p_byte
op_add_assign
l_int|4
suffix:semicolon
r_if
c_cond
(paren
id|p_byte
OG
(paren
(paren
id|u8
op_star
)paren
id|p_EV_header
op_plus
id|evbuffer_length
)paren
)paren
(brace
id|kfree
c_func
(paren
id|mem_node
)paren
suffix:semicolon
r_return
l_int|2
suffix:semicolon
)brace
id|mem_node-&gt;length
op_assign
op_star
(paren
id|u32
op_star
)paren
id|p_byte
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;mem length = %8.8x&bslash;n&quot;
comma
id|mem_node-&gt;length
)paren
suffix:semicolon
id|p_byte
op_add_assign
l_int|4
suffix:semicolon
r_if
c_cond
(paren
id|p_byte
OG
(paren
(paren
id|u8
op_star
)paren
id|p_EV_header
op_plus
id|evbuffer_length
)paren
)paren
(brace
id|kfree
c_func
(paren
id|mem_node
)paren
suffix:semicolon
r_return
l_int|2
suffix:semicolon
)brace
id|mem_node-&gt;next
op_assign
id|ctrl-&gt;mem_head
suffix:semicolon
id|ctrl-&gt;mem_head
op_assign
id|mem_node
suffix:semicolon
)brace
r_while
c_loop
(paren
id|numpmem
op_decrement
)paren
(brace
id|p_mem_node
op_assign
(paren
r_struct
id|pci_resource
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|pci_resource
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p_mem_node
)paren
r_break
suffix:semicolon
id|p_mem_node-&gt;base
op_assign
op_star
(paren
id|u32
op_star
)paren
id|p_byte
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;pre-mem base = %8.8x&bslash;n&quot;
comma
id|p_mem_node-&gt;base
)paren
suffix:semicolon
id|p_byte
op_add_assign
l_int|4
suffix:semicolon
r_if
c_cond
(paren
id|p_byte
OG
(paren
(paren
id|u8
op_star
)paren
id|p_EV_header
op_plus
id|evbuffer_length
)paren
)paren
(brace
id|kfree
c_func
(paren
id|p_mem_node
)paren
suffix:semicolon
r_return
l_int|2
suffix:semicolon
)brace
id|p_mem_node-&gt;length
op_assign
op_star
(paren
id|u32
op_star
)paren
id|p_byte
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;pre-mem length = %8.8x&bslash;n&quot;
comma
id|p_mem_node-&gt;length
)paren
suffix:semicolon
id|p_byte
op_add_assign
l_int|4
suffix:semicolon
r_if
c_cond
(paren
id|p_byte
OG
(paren
(paren
id|u8
op_star
)paren
id|p_EV_header
op_plus
id|evbuffer_length
)paren
)paren
(brace
id|kfree
c_func
(paren
id|p_mem_node
)paren
suffix:semicolon
r_return
l_int|2
suffix:semicolon
)brace
id|p_mem_node-&gt;next
op_assign
id|ctrl-&gt;p_mem_head
suffix:semicolon
id|ctrl-&gt;p_mem_head
op_assign
id|p_mem_node
suffix:semicolon
)brace
r_while
c_loop
(paren
id|numio
op_decrement
)paren
(brace
id|io_node
op_assign
(paren
r_struct
id|pci_resource
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|pci_resource
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|io_node
)paren
r_break
suffix:semicolon
id|io_node-&gt;base
op_assign
op_star
(paren
id|u32
op_star
)paren
id|p_byte
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;io base = %8.8x&bslash;n&quot;
comma
id|io_node-&gt;base
)paren
suffix:semicolon
id|p_byte
op_add_assign
l_int|4
suffix:semicolon
r_if
c_cond
(paren
id|p_byte
OG
(paren
(paren
id|u8
op_star
)paren
id|p_EV_header
op_plus
id|evbuffer_length
)paren
)paren
(brace
id|kfree
c_func
(paren
id|io_node
)paren
suffix:semicolon
r_return
l_int|2
suffix:semicolon
)brace
id|io_node-&gt;length
op_assign
op_star
(paren
id|u32
op_star
)paren
id|p_byte
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;io length = %8.8x&bslash;n&quot;
comma
id|io_node-&gt;length
)paren
suffix:semicolon
id|p_byte
op_add_assign
l_int|4
suffix:semicolon
r_if
c_cond
(paren
id|p_byte
OG
(paren
(paren
id|u8
op_star
)paren
id|p_EV_header
op_plus
id|evbuffer_length
)paren
)paren
(brace
id|kfree
c_func
(paren
id|io_node
)paren
suffix:semicolon
r_return
l_int|2
suffix:semicolon
)brace
id|io_node-&gt;next
op_assign
id|ctrl-&gt;io_head
suffix:semicolon
id|ctrl-&gt;io_head
op_assign
id|io_node
suffix:semicolon
)brace
r_while
c_loop
(paren
id|numbus
op_decrement
)paren
(brace
id|bus_node
op_assign
(paren
r_struct
id|pci_resource
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|pci_resource
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bus_node
)paren
r_break
suffix:semicolon
id|bus_node-&gt;base
op_assign
op_star
(paren
id|u32
op_star
)paren
id|p_byte
suffix:semicolon
id|p_byte
op_add_assign
l_int|4
suffix:semicolon
r_if
c_cond
(paren
id|p_byte
OG
(paren
(paren
id|u8
op_star
)paren
id|p_EV_header
op_plus
id|evbuffer_length
)paren
)paren
(brace
id|kfree
c_func
(paren
id|bus_node
)paren
suffix:semicolon
r_return
l_int|2
suffix:semicolon
)brace
id|bus_node-&gt;length
op_assign
op_star
(paren
id|u32
op_star
)paren
id|p_byte
suffix:semicolon
id|p_byte
op_add_assign
l_int|4
suffix:semicolon
r_if
c_cond
(paren
id|p_byte
OG
(paren
(paren
id|u8
op_star
)paren
id|p_EV_header
op_plus
id|evbuffer_length
)paren
)paren
(brace
id|kfree
c_func
(paren
id|bus_node
)paren
suffix:semicolon
r_return
l_int|2
suffix:semicolon
)brace
id|bus_node-&gt;next
op_assign
id|ctrl-&gt;bus_head
suffix:semicolon
id|ctrl-&gt;bus_head
op_assign
id|bus_node
suffix:semicolon
)brace
singleline_comment|// If all of the following fail, we don&squot;t have any resources for
singleline_comment|// hot plug add
id|rc
op_assign
l_int|1
suffix:semicolon
id|rc
op_and_assign
id|cpqhp_resource_sort_and_combine
c_func
(paren
op_amp
(paren
id|ctrl-&gt;mem_head
)paren
)paren
suffix:semicolon
id|rc
op_and_assign
id|cpqhp_resource_sort_and_combine
c_func
(paren
op_amp
(paren
id|ctrl-&gt;p_mem_head
)paren
)paren
suffix:semicolon
id|rc
op_and_assign
id|cpqhp_resource_sort_and_combine
c_func
(paren
op_amp
(paren
id|ctrl-&gt;io_head
)paren
)paren
suffix:semicolon
id|rc
op_and_assign
id|cpqhp_resource_sort_and_combine
c_func
(paren
op_amp
(paren
id|ctrl-&gt;bus_head
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
r_return
id|rc
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
(paren
id|evbuffer
(braket
l_int|0
)braket
op_ne
l_int|0
)paren
op_logical_and
(paren
op_logical_neg
id|ctrl-&gt;push_flag
)paren
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|compaq_nvram_store
r_int
id|compaq_nvram_store
(paren
r_void
id|__iomem
op_star
id|rom_start
)paren
(brace
r_int
id|rc
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|rom_start
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
id|evbuffer_init
)paren
(brace
id|rc
op_assign
id|store_HRT
c_func
(paren
id|rom_start
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
(brace
id|err
c_func
(paren
id|msg_unable_to_save
)paren
suffix:semicolon
)brace
)brace
r_return
id|rc
suffix:semicolon
)brace
eof
