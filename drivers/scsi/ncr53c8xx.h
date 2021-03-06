multiline_comment|/******************************************************************************&n;**  Device driver for the PCI-SCSI NCR538XX controller family.&n;**&n;**  Copyright (C) 1994  Wolfgang Stanglmeier&n;**&n;**  This program is free software; you can redistribute it and/or modify&n;**  it under the terms of the GNU General Public License as published by&n;**  the Free Software Foundation; either version 2 of the License, or&n;**  (at your option) any later version.&n;**&n;**  This program is distributed in the hope that it will be useful,&n;**  but WITHOUT ANY WARRANTY; without even the implied warranty of&n;**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;**  GNU General Public License for more details.&n;**&n;**  You should have received a copy of the GNU General Public License&n;**  along with this program; if not, write to the Free Software&n;**  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;**&n;**-----------------------------------------------------------------------------&n;**&n;**  This driver has been ported to Linux from the FreeBSD NCR53C8XX driver&n;**  and is currently maintained by&n;**&n;**          Gerard Roudier              &lt;groudier@free.fr&gt;&n;**&n;**  Being given that this driver originates from the FreeBSD version, and&n;**  in order to keep synergy on both, any suggested enhancements and corrections&n;**  received on Linux are automatically a potential candidate for the FreeBSD &n;**  version.&n;**&n;**  The original driver has been written for 386bsd and FreeBSD by&n;**          Wolfgang Stanglmeier        &lt;wolf@cologne.de&gt;&n;**          Stefan Esser                &lt;se@mi.Uni-Koeln.de&gt;&n;**&n;**  And has been ported to NetBSD by&n;**          Charles M. Hannum           &lt;mycroft@gnu.ai.mit.edu&gt;&n;**&n;*******************************************************************************&n;*/
macro_line|#ifndef NCR53C8XX_H
DECL|macro|NCR53C8XX_H
mdefine_line|#define NCR53C8XX_H
macro_line|#include &lt;scsi/scsi_host.h&gt;
macro_line|#include &quot;sym53c8xx_defs.h&quot;
multiline_comment|/*&n;&t;Build a scatter/gather entry.&n;&t;see sym53c8xx_2/sym_hipd.h for more detailed sym_build_sge()&n;&t;implementation ;)&n; */
DECL|macro|ncr_build_sge
mdefine_line|#define ncr_build_sge(np, data, badd, len)&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(data)-&gt;addr = cpu_to_scr(badd);&t;&bslash;&n;&t;(data)-&gt;size = cpu_to_scr(len);&t;&t;&bslash;&n;} while (0)
multiline_comment|/*==========================================================&n;**&n;**&t;Structures used by the detection routine to transmit &n;**&t;device configuration to the attach function.&n;**&n;**==========================================================&n;*/
DECL|struct|ncr_slot
r_struct
id|ncr_slot
(brace
DECL|member|base
id|u_long
id|base
suffix:semicolon
DECL|member|base_2
id|u_long
id|base_2
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
r_void
id|__iomem
op_star
id|base_v
suffix:semicolon
DECL|member|base_2_v
r_void
id|__iomem
op_star
id|base_2_v
suffix:semicolon
DECL|member|irq
r_int
id|irq
suffix:semicolon
multiline_comment|/* port and reg fields to use INB, OUTB macros */
DECL|member|reg
r_volatile
r_struct
id|ncr_reg
id|__iomem
op_star
id|reg
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*==========================================================&n;**&n;**&t;Structure used by detection routine to save data on &n;**&t;each detected board for attach.&n;**&n;**==========================================================&n;*/
DECL|struct|ncr_device
r_struct
id|ncr_device
(brace
DECL|member|dev
r_struct
id|device
op_star
id|dev
suffix:semicolon
DECL|member|slot
r_struct
id|ncr_slot
id|slot
suffix:semicolon
DECL|member|chip
r_struct
id|ncr_chip
id|chip
suffix:semicolon
DECL|member|host_id
id|u_char
id|host_id
suffix:semicolon
DECL|member|differential
id|u8
id|differential
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|Scsi_Host
op_star
id|ncr_attach
c_func
(paren
r_struct
id|scsi_host_template
op_star
id|tpnt
comma
r_int
id|unit
comma
r_struct
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
r_extern
r_int
id|ncr53c8xx_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|ncr53c8xx_exit
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* NCR53C8XX_H */
eof
