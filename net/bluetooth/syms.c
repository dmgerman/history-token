multiline_comment|/* &n;   BlueZ - Bluetooth protocol stack for Linux&n;   Copyright (C) 2000-2001 Qualcomm Incorporated&n;&n;   Written 2000,2001 by Maxim Krasnyansky &lt;maxk@qualcomm.com&gt;&n;&n;   This program is free software; you can redistribute it and/or modify&n;   it under the terms of the GNU General Public License version 2 as&n;   published by the Free Software Foundation;&n;&n;   THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS&n;   OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n;   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT OF THIRD PARTY RIGHTS.&n;   IN NO EVENT SHALL THE COPYRIGHT HOLDER(S) AND AUTHOR(S) BE LIABLE FOR ANY&n;   CLAIM, OR ANY SPECIAL INDIRECT OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES &n;   WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN &n;   ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF &n;   OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.&n;&n;   ALL LIABILITY, INCLUDING LIABILITY FOR INFRINGEMENT OF ANY PATENTS, &n;   COPYRIGHTS, TRADEMARKS OR OTHER RIGHTS, RELATING TO USE OF THIS &n;   SOFTWARE IS DISCLAIMED.&n;*/
multiline_comment|/*&n; * BlueZ symbols.&n; *&n; * $Id: syms.c,v 1.1 2001/07/12 19:31:24 maxk Exp $&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;net/bluetooth/bluetooth.h&gt;
macro_line|#include &lt;net/bluetooth/bluez.h&gt;
macro_line|#include &lt;net/bluetooth/hci_core.h&gt;
multiline_comment|/* HCI Core */
DECL|variable|hci_register_dev
id|EXPORT_SYMBOL
c_func
(paren
id|hci_register_dev
)paren
suffix:semicolon
DECL|variable|hci_unregister_dev
id|EXPORT_SYMBOL
c_func
(paren
id|hci_unregister_dev
)paren
suffix:semicolon
DECL|variable|hci_register_proto
id|EXPORT_SYMBOL
c_func
(paren
id|hci_register_proto
)paren
suffix:semicolon
DECL|variable|hci_unregister_proto
id|EXPORT_SYMBOL
c_func
(paren
id|hci_unregister_proto
)paren
suffix:semicolon
DECL|variable|hci_register_notifier
id|EXPORT_SYMBOL
c_func
(paren
id|hci_register_notifier
)paren
suffix:semicolon
DECL|variable|hci_unregister_notifier
id|EXPORT_SYMBOL
c_func
(paren
id|hci_unregister_notifier
)paren
suffix:semicolon
DECL|variable|hci_connect
id|EXPORT_SYMBOL
c_func
(paren
id|hci_connect
)paren
suffix:semicolon
DECL|variable|hci_disconnect
id|EXPORT_SYMBOL
c_func
(paren
id|hci_disconnect
)paren
suffix:semicolon
DECL|variable|hci_dev_get
id|EXPORT_SYMBOL
c_func
(paren
id|hci_dev_get
)paren
suffix:semicolon
DECL|variable|hci_recv_frame
id|EXPORT_SYMBOL
c_func
(paren
id|hci_recv_frame
)paren
suffix:semicolon
DECL|variable|hci_send_acl
id|EXPORT_SYMBOL
c_func
(paren
id|hci_send_acl
)paren
suffix:semicolon
DECL|variable|hci_send_sco
id|EXPORT_SYMBOL
c_func
(paren
id|hci_send_sco
)paren
suffix:semicolon
DECL|variable|hci_send_raw
id|EXPORT_SYMBOL
c_func
(paren
id|hci_send_raw
)paren
suffix:semicolon
multiline_comment|/* BlueZ lib */
DECL|variable|bluez_dump
id|EXPORT_SYMBOL
c_func
(paren
id|bluez_dump
)paren
suffix:semicolon
DECL|variable|baswap
id|EXPORT_SYMBOL
c_func
(paren
id|baswap
)paren
suffix:semicolon
DECL|variable|batostr
id|EXPORT_SYMBOL
c_func
(paren
id|batostr
)paren
suffix:semicolon
DECL|variable|bterr
id|EXPORT_SYMBOL
c_func
(paren
id|bterr
)paren
suffix:semicolon
multiline_comment|/* BlueZ sockets */
DECL|variable|bluez_sock_register
id|EXPORT_SYMBOL
c_func
(paren
id|bluez_sock_register
)paren
suffix:semicolon
DECL|variable|bluez_sock_unregister
id|EXPORT_SYMBOL
c_func
(paren
id|bluez_sock_unregister
)paren
suffix:semicolon
DECL|variable|bluez_sock_link
id|EXPORT_SYMBOL
c_func
(paren
id|bluez_sock_link
)paren
suffix:semicolon
DECL|variable|bluez_sock_unlink
id|EXPORT_SYMBOL
c_func
(paren
id|bluez_sock_unlink
)paren
suffix:semicolon
eof
