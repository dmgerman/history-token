multiline_comment|/*&n; * Copyright (c) 2004 Mellanox Technologies Ltd.  All rights reserved.&n; * Copyright (c) 2004 Infinicon Corporation.  All rights reserved.&n; * Copyright (c) 2004 Intel Corporation.  All rights reserved.&n; * Copyright (c) 2004 Topspin Corporation.  All rights reserved.&n; * Copyright (c) 2004 Voltaire Corporation.  All rights reserved.&n; *&n; * This software is available to you under a choice of one of two&n; * licenses.  You may choose to be licensed under the terms of the GNU&n; * General Public License (GPL) Version 2, available from the file&n; * COPYING in the main directory of this source tree, or the&n; * OpenIB.org BSD license below:&n; *&n; *     Redistribution and use in source and binary forms, with or&n; *     without modification, are permitted provided that the following&n; *     conditions are met:&n; *&n; *      - Redistributions of source code must retain the above&n; *        copyright notice, this list of conditions and the following&n; *        disclaimer.&n; *&n; *      - Redistributions in binary form must reproduce the above&n; *        copyright notice, this list of conditions and the following&n; *        disclaimer in the documentation and/or other materials&n; *        provided with the distribution.&n; *&n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND,&n; * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF&n; * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND&n; * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS&n; * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN&n; * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN&n; * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE&n; * SOFTWARE.&n; *&n; * $Id: agent.h 1389 2004-12-27 22:56:47Z roland $&n; */
macro_line|#ifndef __AGENT_H_
DECL|macro|__AGENT_H_
mdefine_line|#define __AGENT_H_
r_extern
id|spinlock_t
id|ib_agent_port_list_lock
suffix:semicolon
r_extern
r_int
id|ib_agent_port_open
c_func
(paren
r_struct
id|ib_device
op_star
id|device
comma
r_int
id|port_num
)paren
suffix:semicolon
r_extern
r_int
id|ib_agent_port_close
c_func
(paren
r_struct
id|ib_device
op_star
id|device
comma
r_int
id|port_num
)paren
suffix:semicolon
r_extern
r_int
id|agent_send
c_func
(paren
r_struct
id|ib_mad_private
op_star
id|mad
comma
r_struct
id|ib_grh
op_star
id|grh
comma
r_struct
id|ib_wc
op_star
id|wc
comma
r_struct
id|ib_device
op_star
id|device
comma
r_int
id|port_num
)paren
suffix:semicolon
macro_line|#endif&t;/* __AGENT_H_ */
eof
