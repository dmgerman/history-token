multiline_comment|/* &n;   BlueZ - Bluetooth protocol stack for Linux&n;   Copyright (C) 2000-2001 Qualcomm Incorporated&n;&n;   Written 2000,2001 by Maxim Krasnyansky &lt;maxk@qualcomm.com&gt;&n;&n;   This program is free software; you can redistribute it and/or modify&n;   it under the terms of the GNU General Public License version 2 as&n;   published by the Free Software Foundation;&n;&n;   THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS&n;   OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n;   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT OF THIRD PARTY RIGHTS.&n;   IN NO EVENT SHALL THE COPYRIGHT HOLDER(S) AND AUTHOR(S) BE LIABLE FOR ANY&n;   CLAIM, OR ANY SPECIAL INDIRECT OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES &n;   WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN &n;   ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF &n;   OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.&n;&n;   ALL LIABILITY, INCLUDING LIABILITY FOR INFRINGEMENT OF ANY PATENTS, &n;   COPYRIGHTS, TRADEMARKS OR OTHER RIGHTS, RELATING TO USE OF THIS &n;   SOFTWARE IS DISCLAIMED.&n;*/
multiline_comment|/*&n; * $Id: hci_vhci.h,v 1.2 2001/08/01 01:02:20 maxk Exp $&n; */
macro_line|#ifndef __HCI_VHCI_H
DECL|macro|__HCI_VHCI_H
mdefine_line|#define __HCI_VHCI_H
macro_line|#ifdef __KERNEL__
DECL|struct|hci_vhci_struct
r_struct
id|hci_vhci_struct
(brace
DECL|member|hdev
r_struct
id|hci_dev
id|hdev
suffix:semicolon
DECL|member|flags
id|__u32
id|flags
suffix:semicolon
DECL|member|read_wait
id|wait_queue_head_t
id|read_wait
suffix:semicolon
DECL|member|readq
r_struct
id|sk_buff_head
id|readq
suffix:semicolon
DECL|member|fasync
r_struct
id|fasync_struct
op_star
id|fasync
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* VHCI device flags */
DECL|macro|VHCI_FASYNC
mdefine_line|#define VHCI_FASYNC&t;&t;0x0010
macro_line|#endif /* __KERNEL__ */
DECL|macro|VHCI_DEV
mdefine_line|#define VHCI_DEV&t;&quot;/dev/vhci&quot;
DECL|macro|VHCI_MINOR
mdefine_line|#define VHCI_MINOR&t;250
macro_line|#endif /* __HCI_VHCI_H */
eof
