multiline_comment|/*&n; * arch/ppc/kernel/harrier.h&n; *&n; * Definitions for Motorola MCG Harrier North Bridge &amp; Memory controller&n; *&n; * Author: Dale Farnsworth&n; *         dale.farnsworth@mvista.com&n; *&n; * Copyright 2001 MontaVista Software Inc.&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; */
macro_line|#ifndef __ASMPPC_HARRIER_H
DECL|macro|__ASMPPC_HARRIER_H
mdefine_line|#define __ASMPPC_HARRIER_H
macro_line|#include &lt;asm/pci-bridge.h&gt;
DECL|macro|HARRIER_VEND_DEV_ID
mdefine_line|#define&t;HARRIER_VEND_DEV_ID&t;&t;&t;0x480b1057
multiline_comment|/*&n; * Define outbound register offsets.&n; */
DECL|macro|HARRIER_OTAD0_OFF
mdefine_line|#define HARRIER_OTAD0_OFF&t;&t;&t;0x220
DECL|macro|HARRIER_OTOF0_OFF
mdefine_line|#define HARRIER_OTOF0_OFF&t;&t;&t;0x224
DECL|macro|HARRIER_OTAD1_OFF
mdefine_line|#define HARRIER_OTAD1_OFF&t;&t;&t;0x228
DECL|macro|HARRIER_OTOF1_OFF
mdefine_line|#define HARRIER_OTOF1_OFF&t;&t;&t;0x22c
DECL|macro|HARRIER_OTAD2_OFF
mdefine_line|#define HARRIER_OTAD2_OFF&t;&t;&t;0x230
DECL|macro|HARRIER_OTOF2_OFF
mdefine_line|#define HARRIER_OTOF2_OFF&t;&t;&t;0x234
DECL|macro|HARRIER_OTAD3_OFF
mdefine_line|#define HARRIER_OTAD3_OFF&t;&t;&t;0x238
DECL|macro|HARRIER_OTOF3_OFF
mdefine_line|#define HARRIER_OTOF3_OFF&t;&t;&t;0x23c
multiline_comment|/*&n; * Define inbound register offsets.&n; */
DECL|macro|HARRIER_ITSZ0_OFF
mdefine_line|#define HARRIER_ITSZ0_OFF&t;&t;&t;0x348
DECL|macro|HARRIER_ITSZ1_OFF
mdefine_line|#define HARRIER_ITSZ1_OFF&t;&t;&t;0x350
DECL|macro|HARRIER_ITSZ2_OFF
mdefine_line|#define HARRIER_ITSZ2_OFF&t;&t;&t;0x358
DECL|macro|HARRIER_ITSZ3_OFF
mdefine_line|#define HARRIER_ITSZ3_OFF&t;&t;&t;0x360
multiline_comment|/*&n; * Define the Memory Controller register offsets.&n; */
DECL|macro|HARRIER_SDBA_OFF
mdefine_line|#define HARRIER_SDBA_OFF&t;&t;&t;0x110
DECL|macro|HARRIER_SDBB_OFF
mdefine_line|#define HARRIER_SDBB_OFF&t;&t;&t;0x114
DECL|macro|HARRIER_SDBC_OFF
mdefine_line|#define HARRIER_SDBC_OFF&t;&t;&t;0x118
DECL|macro|HARRIER_SDBD_OFF
mdefine_line|#define HARRIER_SDBD_OFF&t;&t;&t;0x11c
DECL|macro|HARRIER_SDBE_OFF
mdefine_line|#define HARRIER_SDBE_OFF&t;&t;&t;0x120
DECL|macro|HARRIER_SDBF_OFF
mdefine_line|#define HARRIER_SDBF_OFF&t;&t;&t;0x124
DECL|macro|HARRIER_SDBG_OFF
mdefine_line|#define HARRIER_SDBG_OFF&t;&t;&t;0x128
DECL|macro|HARRIER_SDBH_OFF
mdefine_line|#define HARRIER_SDBH_OFF&t;&t;&t;0x12c
DECL|macro|HARRIER_SDB_ENABLE
mdefine_line|#define HARRIER_SDB_ENABLE&t;&t;&t;0x00000100
DECL|macro|HARRIER_SDB_SIZE_MASK
mdefine_line|#define HARRIER_SDB_SIZE_MASK&t;&t;&t;0xf
DECL|macro|HARRIER_SDB_SIZE_SHIFT
mdefine_line|#define HARRIER_SDB_SIZE_SHIFT&t;&t;&t;16
DECL|macro|HARRIER_SDB_BASE_MASK
mdefine_line|#define HARRIER_SDB_BASE_MASK&t;&t;&t;0xff
DECL|macro|HARRIER_SDB_BASE_SHIFT
mdefine_line|#define HARRIER_SDB_BASE_SHIFT&t;&t;&t;24
DECL|macro|HARRIER_SERIAL_0_OFF
mdefine_line|#define HARRIER_SERIAL_0_OFF&t;&t;&t;0xc0
DECL|macro|HARRIER_REVI_OFF
mdefine_line|#define HARRIER_REVI_OFF&t;&t;&t;0x05
DECL|macro|HARRIER_UCTL_OFF
mdefine_line|#define HARRIER_UCTL_OFF&t;&t;&t;0xd0
DECL|macro|HARRIER_XTAL64_MASK
mdefine_line|#define HARRIER_XTAL64_MASK&t;&t;&t;0x02
DECL|macro|HARRIER_MISC_CSR_OFF
mdefine_line|#define HARRIER_MISC_CSR_OFF&t;&t;&t;0x1c
DECL|macro|HARRIER_RSTOUT_MASK
mdefine_line|#define HARRIER_RSTOUT_MASK&t;&t;&t;0x01
DECL|macro|HARRIER_MBAR_OFF
mdefine_line|#define HARRIER_MBAR_OFF&t;&t;&t;0xe0
DECL|macro|HARRIER_MPIC_CSR_OFF
mdefine_line|#define HARRIER_MPIC_CSR_OFF&t;&t;&t;0xe4
DECL|macro|HARRIER_MPIC_OPI_ENABLE
mdefine_line|#define HARRIER_MPIC_OPI_ENABLE&t;&t;&t;0x40
DECL|macro|HARRIER_MPIC_IFEVP_OFF
mdefine_line|#define HARRIER_MPIC_IFEVP_OFF&t;&t;&t;0x10200
DECL|macro|HARRIER_MPIC_IFEDE_OFF
mdefine_line|#define HARRIER_MPIC_IFEDE_OFF&t;&t;&t;0x10210
DECL|macro|HARRIER_FEEN_OFF
mdefine_line|#define HARRIER_FEEN_OFF&t;&t;&t;0x40
DECL|macro|HARRIER_FEST_OFF
mdefine_line|#define HARRIER_FEST_OFF&t;&t;&t;0x44
DECL|macro|HARRIER_FEMA_OFF
mdefine_line|#define HARRIER_FEMA_OFF&t;&t;&t;0x48
DECL|macro|HARRIER_FE_DMA
mdefine_line|#define HARRIER_FE_DMA&t;&t;&t;&t;0x80
DECL|macro|HARRIER_FE_MIDB
mdefine_line|#define HARRIER_FE_MIDB&t;&t;&t;&t;0x40
DECL|macro|HARRIER_FE_MIM0
mdefine_line|#define HARRIER_FE_MIM0&t;&t;&t;&t;0x20
DECL|macro|HARRIER_FE_MIM1
mdefine_line|#define HARRIER_FE_MIM1&t;&t;&t;&t;0x10
DECL|macro|HARRIER_FE_MIP
mdefine_line|#define HARRIER_FE_MIP&t;&t;&t;&t;0x08
DECL|macro|HARRIER_FE_UA0
mdefine_line|#define HARRIER_FE_UA0&t;&t;&t;&t;0x04
DECL|macro|HARRIER_FE_UA1
mdefine_line|#define HARRIER_FE_UA1&t;&t;&t;&t;0x02
DECL|macro|HARRIER_FE_ABT
mdefine_line|#define HARRIER_FE_ABT&t;&t;&t;&t;0x01
r_int
id|harrier_init
c_func
(paren
r_struct
id|pci_controller
op_star
id|hose
comma
id|uint
id|ppc_reg_base
comma
id|ulong
id|processor_pci_mem_start
comma
id|ulong
id|processor_pci_mem_end
comma
id|ulong
id|processor_pci_io_start
comma
id|ulong
id|processor_pci_io_end
comma
id|ulong
id|processor_mpic_base
)paren
suffix:semicolon
r_int
r_int
id|harrier_get_mem_size
c_func
(paren
id|uint
id|smc_base
)paren
suffix:semicolon
r_int
id|harrier_mpic_init
c_func
(paren
r_int
r_int
id|pci_mem_offset
)paren
suffix:semicolon
macro_line|#endif /* __ASMPPC_HARRIER_H */
eof
