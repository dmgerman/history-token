multiline_comment|/*&n; * Copyright (c) 2004 Mellanox Technologies Ltd.  All rights reserved.&n; * Copyright (c) 2004 Infinicon Corporation.  All rights reserved.&n; * Copyright (c) 2004 Intel Corporation.  All rights reserved.&n; * Copyright (c) 2004 Topspin Corporation.  All rights reserved.&n; * Copyright (c) 2004 Voltaire Corporation.  All rights reserved.&n; *&n; * This software is available to you under a choice of one of two&n; * licenses.  You may choose to be licensed under the terms of the GNU&n; * General Public License (GPL) Version 2, available from the file&n; * COPYING in the main directory of this source tree, or the&n; * OpenIB.org BSD license below:&n; *&n; *     Redistribution and use in source and binary forms, with or&n; *     without modification, are permitted provided that the following&n; *     conditions are met:&n; *&n; *      - Redistributions of source code must retain the above&n; *        copyright notice, this list of conditions and the following&n; *        disclaimer.&n; *&n; *      - Redistributions in binary form must reproduce the above&n; *        copyright notice, this list of conditions and the following&n; *        disclaimer in the documentation and/or other materials&n; *        provided with the distribution.&n; *&n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND,&n; * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF&n; * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND&n; * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS&n; * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN&n; * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN&n; * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE&n; * SOFTWARE.&n; *&n; * $Id: agent_priv.h 1389 2004-12-27 22:56:47Z roland $&n; */
macro_line|#ifndef __IB_AGENT_PRIV_H__
DECL|macro|__IB_AGENT_PRIV_H__
mdefine_line|#define __IB_AGENT_PRIV_H__
macro_line|#include &lt;linux/pci.h&gt;
DECL|macro|SPFX
mdefine_line|#define SPFX &quot;ib_agent: &quot;
DECL|struct|ib_agent_send_wr
r_struct
id|ib_agent_send_wr
(brace
DECL|member|send_list
r_struct
id|list_head
id|send_list
suffix:semicolon
DECL|member|ah
r_struct
id|ib_ah
op_star
id|ah
suffix:semicolon
DECL|member|mad
r_struct
id|ib_mad_private
op_star
id|mad
suffix:semicolon
id|DECLARE_PCI_UNMAP_ADDR
c_func
(paren
id|mapping
)paren
)brace
suffix:semicolon
DECL|struct|ib_agent_port_private
r_struct
id|ib_agent_port_private
(brace
DECL|member|port_list
r_struct
id|list_head
id|port_list
suffix:semicolon
DECL|member|send_posted_list
r_struct
id|list_head
id|send_posted_list
suffix:semicolon
DECL|member|send_list_lock
id|spinlock_t
id|send_list_lock
suffix:semicolon
DECL|member|port_num
r_int
id|port_num
suffix:semicolon
DECL|member|dr_smp_agent
r_struct
id|ib_mad_agent
op_star
id|dr_smp_agent
suffix:semicolon
multiline_comment|/* DR SM class */
DECL|member|lr_smp_agent
r_struct
id|ib_mad_agent
op_star
id|lr_smp_agent
suffix:semicolon
multiline_comment|/* LR SM class */
DECL|member|perf_mgmt_agent
r_struct
id|ib_mad_agent
op_star
id|perf_mgmt_agent
suffix:semicolon
multiline_comment|/* PerfMgmt class */
DECL|member|mr
r_struct
id|ib_mr
op_star
id|mr
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif&t;/* __IB_AGENT_PRIV_H__ */
eof
