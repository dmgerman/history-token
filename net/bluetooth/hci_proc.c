multiline_comment|/* &n;   BlueZ - Bluetooth protocol stack for Linux&n;   Copyright (C) 2000-2001 Qualcomm Incorporated&n;&n;   Written 2000,2001 by Maxim Krasnyansky &lt;maxk@qualcomm.com&gt;&n;&n;   This program is free software; you can redistribute it and/or modify&n;   it under the terms of the GNU General Public License version 2 as&n;   published by the Free Software Foundation;&n;&n;   THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS&n;   OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n;   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT OF THIRD PARTY RIGHTS.&n;   IN NO EVENT SHALL THE COPYRIGHT HOLDER(S) AND AUTHOR(S) BE LIABLE FOR ANY&n;   CLAIM, OR ANY SPECIAL INDIRECT OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES &n;   WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN &n;   ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF &n;   OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.&n;&n;   ALL LIABILITY, INCLUDING LIABILITY FOR INFRINGEMENT OF ANY PATENTS, &n;   COPYRIGHTS, TRADEMARKS OR OTHER RIGHTS, RELATING TO USE OF THIS &n;   SOFTWARE IS DISCLAIMED.&n;*/
multiline_comment|/*&n; * Bluetooth HCI Proc FS support.&n; *&n; * $Id: hci_proc.c,v 1.0 2002/04/17 17:37:16 maxk Exp $&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;net/bluetooth/bluetooth.h&gt;
macro_line|#include &lt;net/bluetooth/hci_core.h&gt;
macro_line|#ifndef CONFIG_BT_HCI_CORE_DEBUG
DECL|macro|BT_DBG
macro_line|#undef  BT_DBG
DECL|macro|BT_DBG
mdefine_line|#define BT_DBG( A... )
macro_line|#endif
macro_line|#ifdef CONFIG_PROC_FS
DECL|variable|proc_bt_hci
r_struct
id|proc_dir_entry
op_star
id|proc_bt_hci
suffix:semicolon
DECL|function|hci_seq_open
r_static
r_int
id|hci_seq_open
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_struct
id|seq_operations
op_star
id|op
comma
r_void
op_star
id|priv
)paren
(brace
r_struct
id|seq_file
op_star
id|seq
suffix:semicolon
r_if
c_cond
(paren
id|seq_open
c_func
(paren
id|file
comma
id|op
)paren
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|seq
op_assign
id|file-&gt;private_data
suffix:semicolon
id|seq
op_member_access_from_pointer
r_private
op_assign
id|priv
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|inq_seq_start
r_static
r_void
op_star
id|inq_seq_start
c_func
(paren
r_struct
id|seq_file
op_star
id|seq
comma
id|loff_t
op_star
id|pos
)paren
(brace
r_struct
id|hci_dev
op_star
id|hdev
op_assign
id|seq
op_member_access_from_pointer
r_private
suffix:semicolon
r_struct
id|inquiry_entry
op_star
id|inq
suffix:semicolon
id|loff_t
id|l
op_assign
op_star
id|pos
suffix:semicolon
id|hci_dev_lock_bh
c_func
(paren
id|hdev
)paren
suffix:semicolon
r_for
c_loop
(paren
id|inq
op_assign
id|hdev-&gt;inq_cache.list
suffix:semicolon
id|inq
suffix:semicolon
id|inq
op_assign
id|inq-&gt;next
)paren
r_if
c_cond
(paren
op_logical_neg
id|l
op_decrement
)paren
r_return
id|inq
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|inq_seq_next
r_static
r_void
op_star
id|inq_seq_next
c_func
(paren
r_struct
id|seq_file
op_star
id|seq
comma
r_void
op_star
id|e
comma
id|loff_t
op_star
id|pos
)paren
(brace
r_struct
id|inquiry_entry
op_star
id|inq
op_assign
id|e
suffix:semicolon
r_return
id|inq-&gt;next
suffix:semicolon
)brace
DECL|function|inq_seq_stop
r_static
r_void
id|inq_seq_stop
c_func
(paren
r_struct
id|seq_file
op_star
id|seq
comma
r_void
op_star
id|e
)paren
(brace
r_struct
id|hci_dev
op_star
id|hdev
op_assign
id|seq
op_member_access_from_pointer
r_private
suffix:semicolon
id|hci_dev_unlock_bh
c_func
(paren
id|hdev
)paren
suffix:semicolon
)brace
DECL|function|inq_seq_show
r_static
r_int
id|inq_seq_show
c_func
(paren
r_struct
id|seq_file
op_star
id|seq
comma
r_void
op_star
id|e
)paren
(brace
r_struct
id|inquiry_entry
op_star
id|inq
op_assign
id|e
suffix:semicolon
r_struct
id|inquiry_info
op_star
id|info
op_assign
op_amp
id|inq-&gt;info
suffix:semicolon
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot;%s %d %d %d 0x%.2x%.2x%.2x 0x%.4x %u&bslash;n&quot;
comma
id|batostr
c_func
(paren
op_amp
id|info-&gt;bdaddr
)paren
comma
id|info-&gt;pscan_rep_mode
comma
id|info-&gt;pscan_period_mode
comma
id|info-&gt;pscan_mode
comma
id|info-&gt;dev_class
(braket
l_int|0
)braket
comma
id|info-&gt;dev_class
(braket
l_int|1
)braket
comma
id|info-&gt;dev_class
(braket
l_int|2
)braket
comma
id|info-&gt;clock_offset
comma
id|inq-&gt;timestamp
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|inq_seq_ops
r_static
r_struct
id|seq_operations
id|inq_seq_ops
op_assign
(brace
dot
id|start
op_assign
id|inq_seq_start
comma
dot
id|next
op_assign
id|inq_seq_next
comma
dot
id|stop
op_assign
id|inq_seq_stop
comma
dot
id|show
op_assign
id|inq_seq_show
)brace
suffix:semicolon
DECL|function|inq_seq_open
r_static
r_int
id|inq_seq_open
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
(brace
r_return
id|hci_seq_open
c_func
(paren
id|file
comma
op_amp
id|inq_seq_ops
comma
id|PDE
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|data
)paren
suffix:semicolon
)brace
DECL|variable|inq_seq_fops
r_static
r_struct
id|file_operations
id|inq_seq_fops
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|open
op_assign
id|inq_seq_open
comma
dot
id|read
op_assign
id|seq_read
comma
dot
id|llseek
op_assign
id|seq_lseek
comma
dot
id|release
op_assign
id|seq_release
comma
)brace
suffix:semicolon
DECL|function|hci_dev_proc_init
r_int
id|hci_dev_proc_init
c_func
(paren
r_struct
id|hci_dev
op_star
id|hdev
)paren
(brace
r_struct
id|proc_dir_entry
op_star
id|e
suffix:semicolon
r_char
id|id
(braket
l_int|10
)braket
suffix:semicolon
id|sprintf
c_func
(paren
id|id
comma
l_string|&quot;%d&quot;
comma
id|hdev-&gt;id
)paren
suffix:semicolon
id|hdev-&gt;proc
op_assign
id|proc_mkdir
c_func
(paren
id|id
comma
id|proc_bt_hci
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hdev-&gt;proc
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|e
op_assign
id|create_proc_entry
c_func
(paren
l_string|&quot;inquiry_cache&quot;
comma
id|S_IRUGO
comma
id|hdev-&gt;proc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|e
)paren
(brace
id|e-&gt;proc_fops
op_assign
op_amp
id|inq_seq_fops
suffix:semicolon
id|e-&gt;data
op_assign
(paren
r_void
op_star
)paren
id|hdev
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hci_dev_proc_cleanup
r_void
id|hci_dev_proc_cleanup
c_func
(paren
r_struct
id|hci_dev
op_star
id|hdev
)paren
(brace
r_char
id|id
(braket
l_int|10
)braket
suffix:semicolon
id|sprintf
c_func
(paren
id|id
comma
l_string|&quot;%d&quot;
comma
id|hdev-&gt;id
)paren
suffix:semicolon
id|remove_proc_entry
c_func
(paren
l_string|&quot;inquiry_cache&quot;
comma
id|hdev-&gt;proc
)paren
suffix:semicolon
id|remove_proc_entry
c_func
(paren
id|id
comma
id|proc_bt_hci
)paren
suffix:semicolon
)brace
DECL|function|hci_proc_init
r_int
id|__init
id|hci_proc_init
c_func
(paren
r_void
)paren
(brace
id|proc_bt_hci
op_assign
id|proc_mkdir
c_func
(paren
l_string|&quot;hci&quot;
comma
id|proc_bt
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hci_proc_cleanup
r_void
id|__exit
id|hci_proc_cleanup
c_func
(paren
r_void
)paren
(brace
id|remove_proc_entry
c_func
(paren
l_string|&quot;hci&quot;
comma
id|proc_bt
)paren
suffix:semicolon
)brace
macro_line|#else /* CONFIG_PROC_FS */
DECL|function|hci_dev_proc_init
r_int
id|hci_dev_proc_init
c_func
(paren
r_struct
id|hci_dev
op_star
id|hdev
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hci_dev_proc_cleanup
r_void
id|hci_dev_proc_cleanup
c_func
(paren
r_struct
id|hci_dev
op_star
id|hdev
)paren
(brace
r_return
suffix:semicolon
)brace
DECL|function|hci_proc_init
r_int
id|__init
id|hci_proc_init
c_func
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hci_proc_cleanup
r_void
id|__exit
id|hci_proc_cleanup
c_func
(paren
r_void
)paren
(brace
r_return
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_PROC_FS */
eof
