multiline_comment|/******************************************************************************&n;**  Device driver for the PCI-SCSI NCR538XX controller family.&n;**&n;**  Copyright (C) 1994  Wolfgang Stanglmeier&n;**&n;**  This program is free software; you can redistribute it and/or modify&n;**  it under the terms of the GNU General Public License as published by&n;**  the Free Software Foundation; either version 2 of the License, or&n;**  (at your option) any later version.&n;**&n;**  This program is distributed in the hope that it will be useful,&n;**  but WITHOUT ANY WARRANTY; without even the implied warranty of&n;**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;**  GNU General Public License for more details.&n;**&n;**  You should have received a copy of the GNU General Public License&n;**  along with this program; if not, write to the Free Software&n;**  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;**&n;**-----------------------------------------------------------------------------&n;**&n;**  This driver has been ported to Linux from the FreeBSD NCR53C8XX driver&n;**  and is currently maintained by&n;**&n;**          Gerard Roudier              &lt;groudier@free.fr&gt;&n;**&n;**  Being given that this driver originates from the FreeBSD version, and&n;**  in order to keep synergy on both, any suggested enhancements and corrections&n;**  received on Linux are automatically a potential candidate for the FreeBSD &n;**  version.&n;**&n;**  The original driver has been written for 386bsd and FreeBSD by&n;**          Wolfgang Stanglmeier        &lt;wolf@cologne.de&gt;&n;**          Stefan Esser                &lt;se@mi.Uni-Koeln.de&gt;&n;**&n;**  And has been ported to NetBSD by&n;**          Charles M. Hannum           &lt;mycroft@gnu.ai.mit.edu&gt;&n;**&n;*******************************************************************************&n;*/
macro_line|#ifndef NCR53C8XX_H
DECL|macro|NCR53C8XX_H
mdefine_line|#define NCR53C8XX_H
multiline_comment|/*&n;**&t;Define the BSD style u_int32 and u_int64 type.&n;**&t;Are in fact u_int32_t and u_int64_t :-)&n;*/
DECL|typedef|u_int32
r_typedef
id|u32
id|u_int32
suffix:semicolon
DECL|typedef|u_int64
r_typedef
id|u64
id|u_int64
suffix:semicolon
DECL|typedef|vm_offset_t
r_typedef
id|u_long
id|vm_offset_t
suffix:semicolon
macro_line|#include &quot;sym53c8xx_defs.h&quot;
multiline_comment|/*==========================================================&n;**&n;**&t;Structures used by the detection routine to transmit &n;**&t;device configuration to the attach function.&n;**&n;**==========================================================&n;*/
r_typedef
r_struct
(brace
DECL|member|bus
r_int
id|bus
suffix:semicolon
DECL|member|device_fn
id|u_char
id|device_fn
suffix:semicolon
DECL|member|base
id|u_long
id|base
suffix:semicolon
DECL|member|base_2
id|u_long
id|base_2
suffix:semicolon
DECL|member|io_port
id|u_long
id|io_port
suffix:semicolon
DECL|member|base_c
id|u_long
id|base_c
suffix:semicolon
DECL|member|base_2_c
id|u_long
id|base_2_c
suffix:semicolon
DECL|member|base_v
id|u_long
id|base_v
suffix:semicolon
DECL|member|base_2_v
id|u_long
id|base_2_v
suffix:semicolon
DECL|member|irq
r_int
id|irq
suffix:semicolon
multiline_comment|/* port and reg fields to use INB, OUTB macros */
DECL|member|base_io
id|u_long
id|base_io
suffix:semicolon
DECL|member|reg
r_volatile
r_struct
id|ncr_reg
op_star
id|reg
suffix:semicolon
DECL|typedef|ncr_slot
)brace
id|ncr_slot
suffix:semicolon
multiline_comment|/*==========================================================&n;**&n;**&t;Structure used to store the NVRAM content.&n;**&n;**==========================================================&n;*/
r_typedef
r_struct
(brace
DECL|member|type
r_int
id|type
suffix:semicolon
DECL|macro|SCSI_NCR_SYMBIOS_NVRAM
mdefine_line|#define&t;SCSI_NCR_SYMBIOS_NVRAM&t;(1)
DECL|macro|SCSI_NCR_TEKRAM_NVRAM
mdefine_line|#define&t;SCSI_NCR_TEKRAM_NVRAM&t;(2)
macro_line|#ifdef&t;SCSI_NCR_NVRAM_SUPPORT
r_union
(brace
DECL|member|Symbios
id|Symbios_nvram
id|Symbios
suffix:semicolon
DECL|member|Tekram
id|Tekram_nvram
id|Tekram
suffix:semicolon
DECL|member|data
)brace
id|data
suffix:semicolon
macro_line|#endif
DECL|typedef|ncr_nvram
)brace
id|ncr_nvram
suffix:semicolon
multiline_comment|/*==========================================================&n;**&n;**&t;Structure used by detection routine to save data on &n;**&t;each detected board for attach.&n;**&n;**==========================================================&n;*/
r_typedef
r_struct
(brace
DECL|member|dev
r_struct
id|device
op_star
id|dev
suffix:semicolon
DECL|member|slot
id|ncr_slot
id|slot
suffix:semicolon
DECL|member|chip
id|ncr_chip
id|chip
suffix:semicolon
DECL|member|nvram
id|ncr_nvram
op_star
id|nvram
suffix:semicolon
DECL|member|host_id
id|u_char
id|host_id
suffix:semicolon
macro_line|#ifdef&t;SCSI_NCR_PQS_PDS_SUPPORT
DECL|member|pqs_pds
id|u_char
id|pqs_pds
suffix:semicolon
macro_line|#endif
DECL|member|differential
id|__u8
id|differential
suffix:semicolon
DECL|member|attach_done
r_int
id|attach_done
suffix:semicolon
DECL|typedef|ncr_device
)brace
id|ncr_device
suffix:semicolon
r_extern
r_struct
id|Scsi_Host
op_star
id|ncr_attach
(paren
id|Scsi_Host_Template
op_star
id|tpnt
comma
r_int
id|unit
comma
id|ncr_device
op_star
id|device
)paren
suffix:semicolon
r_extern
r_int
id|ncr53c8xx_release
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|host
)paren
suffix:semicolon
id|irqreturn_t
id|ncr53c8xx_intr
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
macro_line|#endif /* NCR53C8XX_H */
eof
