multiline_comment|/*&n; * IUCV special message driver&n; *&n; * Copyright (C) 2003 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; * Author(s): Martin Schwidefsky (schwidefsky@de.ibm.com)&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;asm/cpcmd.h&gt;
macro_line|#include &lt;asm/ebcdic.h&gt;
macro_line|#include &quot;iucv.h&quot;
DECL|struct|smsg_callback
r_struct
id|smsg_callback
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|prefix
r_char
op_star
id|prefix
suffix:semicolon
DECL|member|len
r_int
id|len
suffix:semicolon
DECL|member|callback
r_void
(paren
op_star
id|callback
)paren
(paren
r_char
op_star
id|str
)paren
suffix:semicolon
)brace
suffix:semicolon
id|MODULE_AUTHOR
(paren
l_string|&quot;(C) 2003 IBM Corporation by Martin Schwidefsky (schwidefsky@de.ibm.com)&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
(paren
l_string|&quot;Linux for S/390 IUCV special message driver&quot;
)paren
suffix:semicolon
DECL|variable|smsg_handle
r_static
id|iucv_handle_t
id|smsg_handle
suffix:semicolon
DECL|variable|smsg_pathid
r_static
r_int
r_int
id|smsg_pathid
suffix:semicolon
DECL|variable|smsg_list_lock
r_static
id|spinlock_t
id|smsg_list_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|variable|smsg_list
r_static
r_struct
id|list_head
id|smsg_list
op_assign
id|LIST_HEAD_INIT
c_func
(paren
id|smsg_list
)paren
suffix:semicolon
r_static
r_void
DECL|function|smsg_connection_complete
id|smsg_connection_complete
c_func
(paren
id|iucv_ConnectionComplete
op_star
id|eib
comma
r_void
op_star
id|pgm_data
)paren
(brace
)brace
r_static
r_void
DECL|function|smsg_message_pending
id|smsg_message_pending
c_func
(paren
id|iucv_MessagePending
op_star
id|eib
comma
r_void
op_star
id|pgm_data
)paren
(brace
r_struct
id|smsg_callback
op_star
id|cb
suffix:semicolon
r_int
r_char
op_star
id|msg
suffix:semicolon
r_int
r_int
id|len
suffix:semicolon
r_int
id|rc
suffix:semicolon
id|len
op_assign
id|eib-&gt;ln1msg2.ipbfln1f
suffix:semicolon
id|msg
op_assign
id|kmalloc
c_func
(paren
id|len
op_plus
l_int|1
comma
id|GFP_ATOMIC
op_or
id|GFP_DMA
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|msg
)paren
(brace
id|iucv_reject
c_func
(paren
id|eib-&gt;ippathid
comma
id|eib-&gt;ipmsgid
comma
id|eib-&gt;iptrgcls
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|rc
op_assign
id|iucv_receive
c_func
(paren
id|eib-&gt;ippathid
comma
id|eib-&gt;ipmsgid
comma
id|eib-&gt;iptrgcls
comma
id|msg
comma
id|len
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_eq
l_int|0
)paren
(brace
id|msg
(braket
id|len
)braket
op_assign
l_int|0
suffix:semicolon
id|EBCASC
c_func
(paren
id|msg
comma
id|len
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|smsg_list_lock
)paren
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|cb
comma
op_amp
id|smsg_list
comma
id|list
)paren
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|msg
op_plus
l_int|8
comma
id|cb-&gt;prefix
comma
id|cb-&gt;len
)paren
op_eq
l_int|0
)paren
(brace
id|cb
op_member_access_from_pointer
id|callback
c_func
(paren
id|msg
op_plus
l_int|8
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|smsg_list_lock
)paren
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|msg
)paren
suffix:semicolon
)brace
DECL|variable|smsg_ops
r_static
id|iucv_interrupt_ops_t
id|smsg_ops
op_assign
(brace
dot
id|ConnectionComplete
op_assign
id|smsg_connection_complete
comma
dot
id|MessagePending
op_assign
id|smsg_message_pending
comma
)brace
suffix:semicolon
DECL|variable|smsg_driver
r_static
r_struct
id|device_driver
id|smsg_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;SMSGIUCV&quot;
comma
dot
id|bus
op_assign
op_amp
id|iucv_bus
comma
)brace
suffix:semicolon
r_int
DECL|function|smsg_register_callback
id|smsg_register_callback
c_func
(paren
r_char
op_star
id|prefix
comma
r_void
(paren
op_star
id|callback
)paren
(paren
r_char
op_star
id|str
)paren
)paren
(brace
r_struct
id|smsg_callback
op_star
id|cb
suffix:semicolon
id|cb
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|smsg_callback
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cb
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|cb-&gt;prefix
op_assign
id|prefix
suffix:semicolon
id|cb-&gt;len
op_assign
id|strlen
c_func
(paren
id|prefix
)paren
suffix:semicolon
id|cb-&gt;callback
op_assign
id|callback
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|smsg_list_lock
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|cb-&gt;list
comma
op_amp
id|smsg_list
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|smsg_list_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_void
DECL|function|smsg_unregister_callback
id|smsg_unregister_callback
c_func
(paren
r_char
op_star
id|prefix
comma
r_void
(paren
op_star
id|callback
)paren
(paren
r_char
op_star
id|str
)paren
)paren
(brace
r_struct
id|smsg_callback
op_star
id|cb
comma
op_star
id|tmp
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|smsg_list_lock
)paren
suffix:semicolon
id|cb
op_assign
l_int|0
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|tmp
comma
op_amp
id|smsg_list
comma
id|list
)paren
r_if
c_cond
(paren
id|tmp-&gt;callback
op_eq
id|callback
op_logical_and
id|strcmp
c_func
(paren
id|tmp-&gt;prefix
comma
id|prefix
)paren
op_eq
l_int|0
)paren
(brace
id|cb
op_assign
id|tmp
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|cb-&gt;list
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|smsg_list_lock
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|cb
)paren
suffix:semicolon
)brace
r_static
r_void
id|__exit
DECL|function|smsg_exit
id|smsg_exit
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|smsg_handle
OG
l_int|0
)paren
(brace
id|cpcmd
c_func
(paren
l_string|&quot;SET SMSG OFF&quot;
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
id|iucv_sever
c_func
(paren
id|smsg_pathid
comma
l_int|0
)paren
suffix:semicolon
id|iucv_unregister_program
c_func
(paren
id|smsg_handle
)paren
suffix:semicolon
id|driver_unregister
c_func
(paren
op_amp
id|smsg_driver
)paren
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
r_static
r_int
id|__init
DECL|function|smsg_init
id|smsg_init
c_func
(paren
r_void
)paren
(brace
r_static
r_int
r_char
id|pgmmask
(braket
l_int|24
)braket
op_assign
(brace
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
comma
l_int|0xff
)brace
suffix:semicolon
r_int
id|rc
suffix:semicolon
id|rc
op_assign
id|driver_register
c_func
(paren
op_amp
id|smsg_driver
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;SMSGIUCV: failed to register driver.&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
id|smsg_handle
op_assign
id|iucv_register_program
c_func
(paren
l_string|&quot;SMSGIUCV        &quot;
comma
l_string|&quot;*MSG    &quot;
comma
id|pgmmask
comma
op_amp
id|smsg_ops
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|smsg_handle
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;SMSGIUCV: failed to register to iucv&quot;
)paren
suffix:semicolon
id|driver_unregister
c_func
(paren
op_amp
id|smsg_driver
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
multiline_comment|/* better errno ? */
)brace
id|rc
op_assign
id|iucv_connect
(paren
op_amp
id|smsg_pathid
comma
l_int|1
comma
l_int|0
comma
l_string|&quot;*MSG    &quot;
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|smsg_handle
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;SMSGIUCV: failed to connect to *MSG&quot;
)paren
suffix:semicolon
id|iucv_unregister_program
c_func
(paren
id|smsg_handle
)paren
suffix:semicolon
id|driver_unregister
c_func
(paren
op_amp
id|smsg_driver
)paren
suffix:semicolon
id|smsg_handle
op_assign
l_int|0
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|cpcmd
c_func
(paren
l_string|&quot;SET SMSG IUCV&quot;
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|smsg_init
id|module_init
c_func
(paren
id|smsg_init
)paren
suffix:semicolon
DECL|variable|smsg_exit
id|module_exit
c_func
(paren
id|smsg_exit
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|smsg_register_callback
id|EXPORT_SYMBOL
c_func
(paren
id|smsg_register_callback
)paren
suffix:semicolon
DECL|variable|smsg_unregister_callback
id|EXPORT_SYMBOL
c_func
(paren
id|smsg_unregister_callback
)paren
suffix:semicolon
eof
