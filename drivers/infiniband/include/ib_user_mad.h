multiline_comment|/*&n; * Copyright (c) 2004 Topspin Communications.  All rights reserved.&n; *&n; * This software is available to you under a choice of one of two&n; * licenses.  You may choose to be licensed under the terms of the GNU&n; * General Public License (GPL) Version 2, available from the file&n; * COPYING in the main directory of this source tree, or the&n; * OpenIB.org BSD license below:&n; *&n; *     Redistribution and use in source and binary forms, with or&n; *     without modification, are permitted provided that the following&n; *     conditions are met:&n; *&n; *      - Redistributions of source code must retain the above&n; *        copyright notice, this list of conditions and the following&n; *        disclaimer.&n; *&n; *      - Redistributions in binary form must reproduce the above&n; *        copyright notice, this list of conditions and the following&n; *        disclaimer in the documentation and/or other materials&n; *        provided with the distribution.&n; *&n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND,&n; * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF&n; * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND&n; * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS&n; * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN&n; * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN&n; * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE&n; * SOFTWARE.&n; *&n; * $Id: ib_user_mad.h 1389 2004-12-27 22:56:47Z roland $&n; */
macro_line|#ifndef IB_USER_MAD_H
DECL|macro|IB_USER_MAD_H
mdefine_line|#define IB_USER_MAD_H
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/ioctl.h&gt;
multiline_comment|/*&n; * Increment this value if any changes that break userspace ABI&n; * compatibility are made.&n; */
DECL|macro|IB_USER_MAD_ABI_VERSION
mdefine_line|#define IB_USER_MAD_ABI_VERSION&t;2
multiline_comment|/*&n; * Make sure that all structs defined in this file remain laid out so&n; * that they pack the same way on 32-bit and 64-bit architectures (to&n; * avoid incompatibility between 32-bit userspace and 64-bit kernels).&n; */
multiline_comment|/**&n; * ib_user_mad - MAD packet&n; * @data - Contents of MAD&n; * @id - ID of agent MAD received with/to be sent with&n; * @status - 0 on successful receive, ETIMEDOUT if no response&n; *   received (transaction ID in data[] will be set to TID of original&n; *   request) (ignored on send)&n; * @timeout_ms - Milliseconds to wait for response (unset on receive)&n; * @qpn - Remote QP number received from/to be sent to&n; * @qkey - Remote Q_Key to be sent with (unset on receive)&n; * @lid - Remote lid received from/to be sent to&n; * @sl - Service level received with/to be sent with&n; * @path_bits - Local path bits received with/to be sent with&n; * @grh_present - If set, GRH was received/should be sent&n; * @gid_index - Local GID index to send with (unset on receive)&n; * @hop_limit - Hop limit in GRH&n; * @traffic_class - Traffic class in GRH&n; * @gid - Remote GID in GRH&n; * @flow_label - Flow label in GRH&n; *&n; * All multi-byte quantities are stored in network (big endian) byte order.&n; */
DECL|struct|ib_user_mad
r_struct
id|ib_user_mad
(brace
DECL|member|data
id|__u8
id|data
(braket
l_int|256
)braket
suffix:semicolon
DECL|member|id
id|__u32
id|id
suffix:semicolon
DECL|member|status
id|__u32
id|status
suffix:semicolon
DECL|member|timeout_ms
id|__u32
id|timeout_ms
suffix:semicolon
DECL|member|qpn
id|__u32
id|qpn
suffix:semicolon
DECL|member|qkey
id|__u32
id|qkey
suffix:semicolon
DECL|member|lid
id|__u16
id|lid
suffix:semicolon
DECL|member|sl
id|__u8
id|sl
suffix:semicolon
DECL|member|path_bits
id|__u8
id|path_bits
suffix:semicolon
DECL|member|grh_present
id|__u8
id|grh_present
suffix:semicolon
DECL|member|gid_index
id|__u8
id|gid_index
suffix:semicolon
DECL|member|hop_limit
id|__u8
id|hop_limit
suffix:semicolon
DECL|member|traffic_class
id|__u8
id|traffic_class
suffix:semicolon
DECL|member|gid
id|__u8
id|gid
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|flow_label
id|__u32
id|flow_label
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/**&n; * ib_user_mad_reg_req - MAD registration request&n; * @id - Set by the kernel; used to identify agent in future requests.&n; * @qpn - Queue pair number; must be 0 or 1.&n; * @method_mask - The caller will receive unsolicited MADs for any method&n; *   where @method_mask = 1.&n; * @mgmt_class - Indicates which management class of MADs should be receive&n; *   by the caller.  This field is only required if the user wishes to&n; *   receive unsolicited MADs, otherwise it should be 0.&n; * @mgmt_class_version - Indicates which version of MADs for the given&n; *   management class to receive.&n; * @oui: Indicates IEEE OUI when mgmt_class is a vendor class&n; *   in the range from 0x30 to 0x4f. Otherwise not used.&n; */
DECL|struct|ib_user_mad_reg_req
r_struct
id|ib_user_mad_reg_req
(brace
DECL|member|id
id|__u32
id|id
suffix:semicolon
DECL|member|method_mask
id|__u32
id|method_mask
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|qpn
id|__u8
id|qpn
suffix:semicolon
DECL|member|mgmt_class
id|__u8
id|mgmt_class
suffix:semicolon
DECL|member|mgmt_class_version
id|__u8
id|mgmt_class_version
suffix:semicolon
DECL|member|oui
id|__u8
id|oui
(braket
l_int|3
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|IB_IOCTL_MAGIC
mdefine_line|#define IB_IOCTL_MAGIC&t;&t;0x1b
DECL|macro|IB_USER_MAD_REGISTER_AGENT
mdefine_line|#define IB_USER_MAD_REGISTER_AGENT&t;_IOWR(IB_IOCTL_MAGIC, 1, &bslash;&n;&t;&t;&t;&t;&t;      struct ib_user_mad_reg_req)
DECL|macro|IB_USER_MAD_UNREGISTER_AGENT
mdefine_line|#define IB_USER_MAD_UNREGISTER_AGENT&t;_IOW(IB_IOCTL_MAGIC, 2, __u32)
macro_line|#endif /* IB_USER_MAD_H */
eof
