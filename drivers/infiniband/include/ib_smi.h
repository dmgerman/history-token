multiline_comment|/*&n; * Copyright (c) 2004 Mellanox Technologies Ltd.  All rights reserved.&n; * Copyright (c) 2004 Infinicon Corporation.  All rights reserved.&n; * Copyright (c) 2004 Intel Corporation.  All rights reserved.&n; * Copyright (c) 2004 Topspin Corporation.  All rights reserved.&n; * Copyright (c) 2004 Voltaire Corporation.  All rights reserved.&n; *&n; * This software is available to you under a choice of one of two&n; * licenses.  You may choose to be licensed under the terms of the GNU&n; * General Public License (GPL) Version 2, available from the file&n; * COPYING in the main directory of this source tree, or the&n; * OpenIB.org BSD license below:&n; *&n; *     Redistribution and use in source and binary forms, with or&n; *     without modification, are permitted provided that the following&n; *     conditions are met:&n; *&n; *      - Redistributions of source code must retain the above&n; *        copyright notice, this list of conditions and the following&n; *        disclaimer.&n; *&n; *      - Redistributions in binary form must reproduce the above&n; *        copyright notice, this list of conditions and the following&n; *        disclaimer in the documentation and/or other materials&n; *        provided with the distribution.&n; *&n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND,&n; * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF&n; * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND&n; * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS&n; * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN&n; * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN&n; * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE&n; * SOFTWARE.&n; *&n; * $Id: ib_smi.h 1389 2004-12-27 22:56:47Z roland $&n; */
macro_line|#if !defined( IB_SMI_H )
DECL|macro|IB_SMI_H
mdefine_line|#define IB_SMI_H
macro_line|#include &lt;ib_mad.h&gt;
DECL|macro|IB_LID_PERMISSIVE
mdefine_line|#define IB_LID_PERMISSIVE&t;&t;&t;0xFFFF
DECL|macro|IB_SMP_DATA_SIZE
mdefine_line|#define IB_SMP_DATA_SIZE&t;&t;&t;64
DECL|macro|IB_SMP_MAX_PATH_HOPS
mdefine_line|#define IB_SMP_MAX_PATH_HOPS&t;&t;&t;64
DECL|struct|ib_smp
r_struct
id|ib_smp
(brace
DECL|member|base_version
id|u8
id|base_version
suffix:semicolon
DECL|member|mgmt_class
id|u8
id|mgmt_class
suffix:semicolon
DECL|member|class_version
id|u8
id|class_version
suffix:semicolon
DECL|member|method
id|u8
id|method
suffix:semicolon
DECL|member|status
id|u16
id|status
suffix:semicolon
DECL|member|hop_ptr
id|u8
id|hop_ptr
suffix:semicolon
DECL|member|hop_cnt
id|u8
id|hop_cnt
suffix:semicolon
DECL|member|tid
id|u64
id|tid
suffix:semicolon
DECL|member|attr_id
id|u16
id|attr_id
suffix:semicolon
DECL|member|resv
id|u16
id|resv
suffix:semicolon
DECL|member|attr_mod
id|u32
id|attr_mod
suffix:semicolon
DECL|member|mkey
id|u64
id|mkey
suffix:semicolon
DECL|member|dr_slid
id|u16
id|dr_slid
suffix:semicolon
DECL|member|dr_dlid
id|u16
id|dr_dlid
suffix:semicolon
DECL|member|reserved
id|u8
id|reserved
(braket
l_int|28
)braket
suffix:semicolon
DECL|member|data
id|u8
id|data
(braket
id|IB_SMP_DATA_SIZE
)braket
suffix:semicolon
DECL|member|initial_path
id|u8
id|initial_path
(braket
id|IB_SMP_MAX_PATH_HOPS
)braket
suffix:semicolon
DECL|member|return_path
id|u8
id|return_path
(braket
id|IB_SMP_MAX_PATH_HOPS
)braket
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|macro|IB_SMP_DIRECTION
mdefine_line|#define IB_SMP_DIRECTION&t;&t;&t;__constant_htons(0x8000)
multiline_comment|/* Subnet management attributes */
DECL|macro|IB_SMP_ATTR_NOTICE
mdefine_line|#define IB_SMP_ATTR_NOTICE&t;&t;&t;__constant_htons(0x0002)
DECL|macro|IB_SMP_ATTR_NODE_DESC
mdefine_line|#define IB_SMP_ATTR_NODE_DESC&t;&t;&t;__constant_htons(0x0010)
DECL|macro|IB_SMP_ATTR_NODE_INFO
mdefine_line|#define IB_SMP_ATTR_NODE_INFO&t;&t;&t;__constant_htons(0x0011)
DECL|macro|IB_SMP_ATTR_SWITCH_INFO
mdefine_line|#define IB_SMP_ATTR_SWITCH_INFO&t;&t;&t;__constant_htons(0x0012)
DECL|macro|IB_SMP_ATTR_GUID_INFO
mdefine_line|#define IB_SMP_ATTR_GUID_INFO&t;&t;&t;__constant_htons(0x0014)
DECL|macro|IB_SMP_ATTR_PORT_INFO
mdefine_line|#define IB_SMP_ATTR_PORT_INFO&t;&t;&t;__constant_htons(0x0015)
DECL|macro|IB_SMP_ATTR_PKEY_TABLE
mdefine_line|#define IB_SMP_ATTR_PKEY_TABLE&t;&t;&t;__constant_htons(0x0016)
DECL|macro|IB_SMP_ATTR_SL_TO_VL_TABLE
mdefine_line|#define IB_SMP_ATTR_SL_TO_VL_TABLE&t;&t;__constant_htons(0x0017)
DECL|macro|IB_SMP_ATTR_VL_ARB_TABLE
mdefine_line|#define IB_SMP_ATTR_VL_ARB_TABLE&t;&t;__constant_htons(0x0018)
DECL|macro|IB_SMP_ATTR_LINEAR_FORWARD_TABLE
mdefine_line|#define IB_SMP_ATTR_LINEAR_FORWARD_TABLE&t;__constant_htons(0x0019)
DECL|macro|IB_SMP_ATTR_RANDOM_FORWARD_TABLE
mdefine_line|#define IB_SMP_ATTR_RANDOM_FORWARD_TABLE&t;__constant_htons(0x001A)
DECL|macro|IB_SMP_ATTR_MCAST_FORWARD_TABLE
mdefine_line|#define IB_SMP_ATTR_MCAST_FORWARD_TABLE&t;&t;__constant_htons(0x001B)
DECL|macro|IB_SMP_ATTR_SM_INFO
mdefine_line|#define IB_SMP_ATTR_SM_INFO&t;&t;&t;__constant_htons(0x0020)
DECL|macro|IB_SMP_ATTR_VENDOR_DIAG
mdefine_line|#define IB_SMP_ATTR_VENDOR_DIAG&t;&t;&t;__constant_htons(0x0030)
DECL|macro|IB_SMP_ATTR_LED_INFO
mdefine_line|#define IB_SMP_ATTR_LED_INFO&t;&t;&t;__constant_htons(0x0031)
DECL|macro|IB_SMP_ATTR_VENDOR_MASK
mdefine_line|#define IB_SMP_ATTR_VENDOR_MASK&t;&t;&t;__constant_htons(0xFF00)
r_static
r_inline
id|u8
DECL|function|ib_get_smp_direction
id|ib_get_smp_direction
c_func
(paren
r_struct
id|ib_smp
op_star
id|smp
)paren
(brace
r_return
(paren
(paren
id|smp-&gt;status
op_amp
id|IB_SMP_DIRECTION
)paren
op_eq
id|IB_SMP_DIRECTION
)paren
suffix:semicolon
)brace
macro_line|#endif /* IB_SMI_H */
eof
