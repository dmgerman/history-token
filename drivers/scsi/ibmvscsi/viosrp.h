multiline_comment|/*****************************************************************************/
multiline_comment|/* srp.h -- SCSI RDMA Protocol definitions                                   */
multiline_comment|/*                                                                           */
multiline_comment|/* Written By: Colin Devilbis, IBM Corporation                               */
multiline_comment|/*                                                                           */
multiline_comment|/* Copyright (C) 2003 IBM Corporation                                        */
multiline_comment|/*                                                                           */
multiline_comment|/* This program is free software; you can redistribute it and/or modify      */
multiline_comment|/* it under the terms of the GNU General Public License as published by      */
multiline_comment|/* the Free Software Foundation; either version 2 of the License, or         */
multiline_comment|/* (at your option) any later version.                                       */
multiline_comment|/*                                                                           */
multiline_comment|/* This program is distributed in the hope that it will be useful,           */
multiline_comment|/* but WITHOUT ANY WARRANTY; without even the implied warranty of            */
multiline_comment|/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             */
multiline_comment|/* GNU General Public License for more details.                              */
multiline_comment|/*                                                                           */
multiline_comment|/* You should have received a copy of the GNU General Public License         */
multiline_comment|/* along with this program; if not, write to the Free Software               */
multiline_comment|/* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA */
multiline_comment|/*                                                                           */
multiline_comment|/*                                                                           */
multiline_comment|/* This file contains structures and definitions for IBM RPA (RS/6000        */
multiline_comment|/* platform architecture) implementation of the SRP (SCSI RDMA Protocol)     */
multiline_comment|/* standard.  SRP is used on IBM iSeries and pSeries platforms to send SCSI  */
multiline_comment|/* commands between logical partitions.                                      */
multiline_comment|/*                                                                           */
multiline_comment|/* SRP Information Units (IUs) are sent on a &quot;Command/Response Queue&quot; (CRQ)  */
multiline_comment|/* between partitions.  The definitions in this file are architected,        */
multiline_comment|/* and cannot be changed without breaking compatibility with other versions  */
multiline_comment|/* of Linux and other operating systems (AIX, OS/400) that talk this protocol*/
multiline_comment|/* between logical partitions                                                */
multiline_comment|/*****************************************************************************/
macro_line|#ifndef VIOSRP_H
DECL|macro|VIOSRP_H
mdefine_line|#define VIOSRP_H
macro_line|#include &quot;srp.h&quot;
DECL|enum|viosrp_crq_formats
r_enum
id|viosrp_crq_formats
(brace
DECL|enumerator|VIOSRP_SRP_FORMAT
id|VIOSRP_SRP_FORMAT
op_assign
l_int|0x01
comma
DECL|enumerator|VIOSRP_MAD_FORMAT
id|VIOSRP_MAD_FORMAT
op_assign
l_int|0x02
comma
DECL|enumerator|VIOSRP_OS400_FORMAT
id|VIOSRP_OS400_FORMAT
op_assign
l_int|0x03
comma
DECL|enumerator|VIOSRP_AIX_FORMAT
id|VIOSRP_AIX_FORMAT
op_assign
l_int|0x04
comma
DECL|enumerator|VIOSRP_LINUX_FORMAT
id|VIOSRP_LINUX_FORMAT
op_assign
l_int|0x06
comma
DECL|enumerator|VIOSRP_INLINE_FORMAT
id|VIOSRP_INLINE_FORMAT
op_assign
l_int|0x07
)brace
suffix:semicolon
DECL|struct|viosrp_crq
r_struct
id|viosrp_crq
(brace
DECL|member|valid
id|u8
id|valid
suffix:semicolon
multiline_comment|/* used by RPA */
DECL|member|format
id|u8
id|format
suffix:semicolon
multiline_comment|/* SCSI vs out-of-band */
DECL|member|reserved
id|u8
id|reserved
suffix:semicolon
DECL|member|status
id|u8
id|status
suffix:semicolon
multiline_comment|/* non-scsi failure? (e.g. DMA failure) */
DECL|member|timeout
id|u16
id|timeout
suffix:semicolon
multiline_comment|/* in seconds */
DECL|member|IU_length
id|u16
id|IU_length
suffix:semicolon
multiline_comment|/* in bytes */
DECL|member|IU_data_ptr
id|u64
id|IU_data_ptr
suffix:semicolon
multiline_comment|/* the TCE for transferring data */
)brace
suffix:semicolon
multiline_comment|/* MADs are Management requests above and beyond the IUs defined in the SRP&n; * standard.  &n; */
DECL|enum|viosrp_mad_types
r_enum
id|viosrp_mad_types
(brace
DECL|enumerator|VIOSRP_EMPTY_IU_TYPE
id|VIOSRP_EMPTY_IU_TYPE
op_assign
l_int|0x01
comma
DECL|enumerator|VIOSRP_ERROR_LOG_TYPE
id|VIOSRP_ERROR_LOG_TYPE
op_assign
l_int|0x02
comma
DECL|enumerator|VIOSRP_ADAPTER_INFO_TYPE
id|VIOSRP_ADAPTER_INFO_TYPE
op_assign
l_int|0x03
comma
DECL|enumerator|VIOSRP_HOST_CONFIG_TYPE
id|VIOSRP_HOST_CONFIG_TYPE
op_assign
l_int|0x04
)brace
suffix:semicolon
multiline_comment|/* &n; * Common MAD header&n; */
DECL|struct|mad_common
r_struct
id|mad_common
(brace
DECL|member|type
id|u32
id|type
suffix:semicolon
DECL|member|status
id|u16
id|status
suffix:semicolon
DECL|member|length
id|u16
id|length
suffix:semicolon
DECL|member|tag
id|u64
id|tag
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * All SRP (and MAD) requests normally flow from the&n; * client to the server.  There is no way for the server to send&n; * an asynchronous message back to the client.  The Empty IU is used&n; * to hang out a meaningless request to the server so that it can respond&n; * asynchrouously with something like a SCSI AER &n; */
DECL|struct|viosrp_empty_iu
r_struct
id|viosrp_empty_iu
(brace
DECL|member|common
r_struct
id|mad_common
id|common
suffix:semicolon
DECL|member|buffer
id|u64
id|buffer
suffix:semicolon
DECL|member|port
id|u32
id|port
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|viosrp_error_log
r_struct
id|viosrp_error_log
(brace
DECL|member|common
r_struct
id|mad_common
id|common
suffix:semicolon
DECL|member|buffer
id|u64
id|buffer
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|viosrp_adapter_info
r_struct
id|viosrp_adapter_info
(brace
DECL|member|common
r_struct
id|mad_common
id|common
suffix:semicolon
DECL|member|buffer
id|u64
id|buffer
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|viosrp_host_config
r_struct
id|viosrp_host_config
(brace
DECL|member|common
r_struct
id|mad_common
id|common
suffix:semicolon
DECL|member|buffer
id|u64
id|buffer
suffix:semicolon
)brace
suffix:semicolon
DECL|union|mad_iu
r_union
id|mad_iu
(brace
DECL|member|empty_iu
r_struct
id|viosrp_empty_iu
id|empty_iu
suffix:semicolon
DECL|member|error_log
r_struct
id|viosrp_error_log
id|error_log
suffix:semicolon
DECL|member|adapter_info
r_struct
id|viosrp_adapter_info
id|adapter_info
suffix:semicolon
DECL|member|host_config
r_struct
id|viosrp_host_config
id|host_config
suffix:semicolon
)brace
suffix:semicolon
DECL|union|viosrp_iu
r_union
id|viosrp_iu
(brace
DECL|member|srp
r_union
id|srp_iu
id|srp
suffix:semicolon
DECL|member|mad
r_union
id|mad_iu
id|mad
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|mad_adapter_info_data
r_struct
id|mad_adapter_info_data
(brace
DECL|member|srp_version
r_char
id|srp_version
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|partition_name
r_char
id|partition_name
(braket
l_int|96
)braket
suffix:semicolon
DECL|member|partition_number
id|u32
id|partition_number
suffix:semicolon
DECL|member|mad_version
id|u32
id|mad_version
suffix:semicolon
DECL|member|os_type
id|u32
id|os_type
suffix:semicolon
DECL|member|port_max_txu
id|u32
id|port_max_txu
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* per-port maximum transfer */
)brace
suffix:semicolon
macro_line|#endif
eof
