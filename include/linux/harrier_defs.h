multiline_comment|/*&n; * asm-ppc/harrier_defs.h&n; *&n; * Definitions for Motorola MCG Harrier North Bridge &amp; Memory controller&n; *&n; * Author: Dale Farnsworth&n; *         dale.farnsworth@mvista.com&n; *&n; * Extracted from asm-ppc/harrier.h by:&n; * &t;   Randy Vinson&n; * &t;   rvinson@mvista.com&n; *&n; * Copyright 2001-2002 MontaVista Software Inc.&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; */
macro_line|#ifndef __ASMPPC_HARRIER_DEFS_H
DECL|macro|__ASMPPC_HARRIER_DEFS_H
mdefine_line|#define __ASMPPC_HARRIER_DEFS_H
DECL|macro|HARRIER_DEFAULT_XCSR_BASE
mdefine_line|#define HARRIER_DEFAULT_XCSR_BASE&t;0xfeff0000
DECL|macro|HARRIER_VEND_DEV_ID
mdefine_line|#define HARRIER_VEND_DEV_ID&t;&t;0x1057480b
DECL|macro|HARRIER_VENI_OFF
mdefine_line|#define HARRIER_VENI_OFF&t;&t;0x00
DECL|macro|HARRIER_REVI_OFF
mdefine_line|#define HARRIER_REVI_OFF&t;&t;0x05
DECL|macro|HARRIER_UCTL_OFF
mdefine_line|#define HARRIER_UCTL_OFF&t;&t;0xd0
DECL|macro|HARRIER_XTAL64_MASK
mdefine_line|#define HARRIER_XTAL64_MASK&t;&t;0x02
DECL|macro|HARRIER_MISC_CSR_OFF
mdefine_line|#define HARRIER_MISC_CSR_OFF&t;&t;0x1c
DECL|macro|HARRIER_RSTOUT
mdefine_line|#define HARRIER_RSTOUT&t;&t;&t;0x01000000
DECL|macro|HARRIER_SYSCON
mdefine_line|#define HARRIER_SYSCON&t;&t;&t;0x08000000
DECL|macro|HARRIER_EREADY
mdefine_line|#define HARRIER_EREADY&t;&t;&t;0x10000000
DECL|macro|HARRIER_ERDYS
mdefine_line|#define HARRIER_ERDYS&t;&t;&t;0x20000000
multiline_comment|/* Function exception registers */
DECL|macro|HARRIER_FEEN_OFF
mdefine_line|#define HARRIER_FEEN_OFF&t;&t;0x40&t;/* enable */
DECL|macro|HARRIER_FEST_OFF
mdefine_line|#define HARRIER_FEST_OFF&t;&t;0x44&t;/* status */
DECL|macro|HARRIER_FEMA_OFF
mdefine_line|#define HARRIER_FEMA_OFF&t;&t;0x48&t;/* mask */
DECL|macro|HARRIER_FECL_OFF
mdefine_line|#define HARRIER_FECL_OFF&t;&t;0x4c&t;/* clear */
DECL|macro|HARRIER_FE_DMA
mdefine_line|#define HARRIER_FE_DMA&t;&t;&t;0x80
DECL|macro|HARRIER_FE_MIDB
mdefine_line|#define HARRIER_FE_MIDB&t;&t;&t;0x40
DECL|macro|HARRIER_FE_MIM0
mdefine_line|#define HARRIER_FE_MIM0&t;&t;&t;0x20
DECL|macro|HARRIER_FE_MIM1
mdefine_line|#define HARRIER_FE_MIM1&t;&t;&t;0x10
DECL|macro|HARRIER_FE_MIP
mdefine_line|#define HARRIER_FE_MIP&t;&t;&t;0x08
DECL|macro|HARRIER_FE_UA0
mdefine_line|#define HARRIER_FE_UA0&t;&t;&t;0x04
DECL|macro|HARRIER_FE_UA1
mdefine_line|#define HARRIER_FE_UA1&t;&t;&t;0x02
DECL|macro|HARRIER_FE_ABT
mdefine_line|#define HARRIER_FE_ABT&t;&t;&t;0x01
DECL|macro|HARRIER_SERIAL_0_OFF
mdefine_line|#define HARRIER_SERIAL_0_OFF&t;&t;0xc0
DECL|macro|HARRIER_MBAR_OFF
mdefine_line|#define HARRIER_MBAR_OFF&t;&t;0xe0
DECL|macro|HARRIER_MBAR_MSK
mdefine_line|#define HARRIER_MBAR_MSK&t;&t;0xfffc0000
DECL|macro|HARRIER_MPIC_CSR_OFF
mdefine_line|#define HARRIER_MPIC_CSR_OFF&t;&t;0xe4
DECL|macro|HARRIER_MPIC_OPI_ENABLE
mdefine_line|#define HARRIER_MPIC_OPI_ENABLE&t;&t;0x40
DECL|macro|HARRIER_MPIC_IFEVP_OFF
mdefine_line|#define HARRIER_MPIC_IFEVP_OFF&t;&t;0x10200
DECL|macro|HARRIER_MPIC_IFEVP_VECT_MSK
mdefine_line|#define HARRIER_MPIC_IFEVP_VECT_MSK&t;0xff
DECL|macro|HARRIER_MPIC_IFEDE_OFF
mdefine_line|#define HARRIER_MPIC_IFEDE_OFF&t;&t;0x10210
multiline_comment|/*&n; * Define the Memory Controller register offsets.&n; */
DECL|macro|HARRIER_SDBA_OFF
mdefine_line|#define HARRIER_SDBA_OFF&t;&t;0x110
DECL|macro|HARRIER_SDBB_OFF
mdefine_line|#define HARRIER_SDBB_OFF&t;&t;0x114
DECL|macro|HARRIER_SDBC_OFF
mdefine_line|#define HARRIER_SDBC_OFF&t;&t;0x118
DECL|macro|HARRIER_SDBD_OFF
mdefine_line|#define HARRIER_SDBD_OFF&t;&t;0x11c
DECL|macro|HARRIER_SDBE_OFF
mdefine_line|#define HARRIER_SDBE_OFF&t;&t;0x120
DECL|macro|HARRIER_SDBF_OFF
mdefine_line|#define HARRIER_SDBF_OFF&t;&t;0x124
DECL|macro|HARRIER_SDBG_OFF
mdefine_line|#define HARRIER_SDBG_OFF&t;&t;0x128
DECL|macro|HARRIER_SDBH_OFF
mdefine_line|#define HARRIER_SDBH_OFF&t;&t;0x12c
DECL|macro|HARRIER_SDB_ENABLE
mdefine_line|#define HARRIER_SDB_ENABLE&t;&t;0x00000100
DECL|macro|HARRIER_SDB_SIZE_MASK
mdefine_line|#define HARRIER_SDB_SIZE_MASK&t;&t;0xf
DECL|macro|HARRIER_SDB_SIZE_SHIFT
mdefine_line|#define HARRIER_SDB_SIZE_SHIFT&t;&t;16
DECL|macro|HARRIER_SDB_BASE_MASK
mdefine_line|#define HARRIER_SDB_BASE_MASK&t;&t;0xff
DECL|macro|HARRIER_SDB_BASE_SHIFT
mdefine_line|#define HARRIER_SDB_BASE_SHIFT&t;&t;24
multiline_comment|/*&n; * Define outbound register offsets.&n; */
DECL|macro|HARRIER_OTAD0_OFF
mdefine_line|#define HARRIER_OTAD0_OFF&t;&t;0x220
DECL|macro|HARRIER_OTOF0_OFF
mdefine_line|#define HARRIER_OTOF0_OFF&t;&t;0x224
DECL|macro|HARRIER_OTAD1_OFF
mdefine_line|#define HARRIER_OTAD1_OFF&t;&t;0x228
DECL|macro|HARRIER_OTOF1_OFF
mdefine_line|#define HARRIER_OTOF1_OFF&t;&t;0x22c
DECL|macro|HARRIER_OTAD2_OFF
mdefine_line|#define HARRIER_OTAD2_OFF&t;&t;0x230
DECL|macro|HARRIER_OTOF2_OFF
mdefine_line|#define HARRIER_OTOF2_OFF&t;&t;0x234
DECL|macro|HARRIER_OTAD3_OFF
mdefine_line|#define HARRIER_OTAD3_OFF&t;&t;0x238
DECL|macro|HARRIER_OTOF3_OFF
mdefine_line|#define HARRIER_OTOF3_OFF&t;&t;0x23c
DECL|macro|HARRIER_OTADX_START_MSK
mdefine_line|#define HARRIER_OTADX_START_MSK&t;&t;0xffff0000UL
DECL|macro|HARRIER_OTADX_END_MSK
mdefine_line|#define HARRIER_OTADX_END_MSK&t;&t;0x0000ffffUL
DECL|macro|HARRIER_OTOFX_OFF_MSK
mdefine_line|#define HARRIER_OTOFX_OFF_MSK&t;&t;0xffff0000UL
DECL|macro|HARRIER_OTOFX_ENA
mdefine_line|#define HARRIER_OTOFX_ENA&t;&t;0x80UL
DECL|macro|HARRIER_OTOFX_WPE
mdefine_line|#define HARRIER_OTOFX_WPE&t;&t;0x10UL
DECL|macro|HARRIER_OTOFX_SGE
mdefine_line|#define HARRIER_OTOFX_SGE&t;&t;0x08UL
DECL|macro|HARRIER_OTOFX_RAE
mdefine_line|#define HARRIER_OTOFX_RAE&t;&t;0x04UL
DECL|macro|HARRIER_OTOFX_MEM
mdefine_line|#define HARRIER_OTOFX_MEM&t;&t;0x02UL
DECL|macro|HARRIER_OTOFX_IOM
mdefine_line|#define HARRIER_OTOFX_IOM&t;&t;0x01UL
multiline_comment|/*&n; * Define generic message passing register offsets&n; */
multiline_comment|/* Mirrored registers (visible from both PowerPC and PCI space) */
DECL|macro|HARRIER_XCSR_MP_BASE_OFF
mdefine_line|#define HARRIER_XCSR_MP_BASE_OFF&t;0x290&t;/* base offset in XCSR space */
DECL|macro|HARRIER_PMEP_MP_BASE_OFF
mdefine_line|#define HARRIER_PMEP_MP_BASE_OFF&t;0x100&t;/* base offset in PMEM space */
DECL|macro|HARRIER_MGOM0_OFF
mdefine_line|#define HARRIER_MGOM0_OFF&t;&t;0x00&t;/* outbound msg 0 */
DECL|macro|HARRIER_MGOM1_OFF
mdefine_line|#define HARRIER_MGOM1_OFF&t;&t;0x04&t;/* outbound msg 1 */
DECL|macro|HARRIER_MGOD_OFF
mdefine_line|#define HARRIER_MGOD_OFF&t;&t;0x08&t;/* outbound doorbells */
DECL|macro|HARRIER_MGIM0_OFF
mdefine_line|#define HARRIER_MGIM0_OFF&t;&t;0x10&t;/* inbound msg 0 */
DECL|macro|HARRIER_MGIM1_OFF
mdefine_line|#define HARRIER_MGIM1_OFF&t;&t;0x14&t;/* inbound msg 1 */
DECL|macro|HARRIER_MGID_OFF
mdefine_line|#define HARRIER_MGID_OFF&t;&t;0x18&t;/* inbound doorbells */
multiline_comment|/* PowerPC-only registers */
DECL|macro|HARRIER_MGIDM_OFF
mdefine_line|#define HARRIER_MGIDM_OFF&t;&t;0x20&t;/* inbound doorbell mask */
multiline_comment|/* PCI-only registers */
DECL|macro|HARRIER_PMEP_MGST_OFF
mdefine_line|#define HARRIER_PMEP_MGST_OFF&t;&t;0x20&t;/* (outbound) interrupt status */
DECL|macro|HARRIER_PMEP_MGMS_OFF
mdefine_line|#define HARRIER_PMEP_MGMS_OFF&t;&t;0x24&t;/* (outbound) interrupt mask */
DECL|macro|HARRIER_MG_OMI0
mdefine_line|#define HARRIER_MG_OMI0&t;&t;&t;(1&lt;&lt;4)
DECL|macro|HARRIER_MG_OMI1
mdefine_line|#define HARRIER_MG_OMI1&t;&t;&t;(1&lt;&lt;5)
DECL|macro|HARRIER_PMEP_MGODM_OFF
mdefine_line|#define HARRIER_PMEP_MGODM_OFF&t;&t;0x28&t;/* outbound doorbell mask */
multiline_comment|/*&n; * Define PCI configuration space register offsets&n; */
DECL|macro|HARRIER_XCSR_TO_PCFS_OFF
mdefine_line|#define HARRIER_XCSR_TO_PCFS_OFF&t;0x300
multiline_comment|/*&n; * Define message passing attribute register offset&n; */
DECL|macro|HARRIER_MPAT_OFF
mdefine_line|#define HARRIER_MPAT_OFF&t;&t;0x44
multiline_comment|/*&n; * Define inbound attribute register offsets.&n; */
DECL|macro|HARRIER_ITSZ0_OFF
mdefine_line|#define HARRIER_ITSZ0_OFF&t;&t;0x48
DECL|macro|HARRIER_ITAT0_OFF
mdefine_line|#define HARRIER_ITAT0_OFF&t;&t;0x4c
DECL|macro|HARRIER_ITSZ1_OFF
mdefine_line|#define HARRIER_ITSZ1_OFF&t;&t;0x50
DECL|macro|HARRIER_ITAT1_OFF
mdefine_line|#define HARRIER_ITAT1_OFF&t;&t;0x54
DECL|macro|HARRIER_ITSZ2_OFF
mdefine_line|#define HARRIER_ITSZ2_OFF&t;&t;0x58
DECL|macro|HARRIER_ITAT2_OFF
mdefine_line|#define HARRIER_ITAT2_OFF&t;&t;0x5c
DECL|macro|HARRIER_ITSZ3_OFF
mdefine_line|#define HARRIER_ITSZ3_OFF&t;&t;0x60
DECL|macro|HARRIER_ITAT3_OFF
mdefine_line|#define HARRIER_ITAT3_OFF&t;&t;0x64
multiline_comment|/* inbound translation size constants */
DECL|macro|HARRIER_ITSZ_MSK
mdefine_line|#define HARRIER_ITSZ_MSK&t;&t;0xff
DECL|macro|HARRIER_ITSZ_4KB
mdefine_line|#define HARRIER_ITSZ_4KB&t;&t;0x00
DECL|macro|HARRIER_ITSZ_8KB
mdefine_line|#define HARRIER_ITSZ_8KB&t;&t;0x01
DECL|macro|HARRIER_ITSZ_16KB
mdefine_line|#define HARRIER_ITSZ_16KB&t;&t;0x02
DECL|macro|HARRIER_ITSZ_32KB
mdefine_line|#define HARRIER_ITSZ_32KB&t;&t;0x03
DECL|macro|HARRIER_ITSZ_64KB
mdefine_line|#define HARRIER_ITSZ_64KB&t;&t;0x04
DECL|macro|HARRIER_ITSZ_128KB
mdefine_line|#define HARRIER_ITSZ_128KB&t;&t;0x05
DECL|macro|HARRIER_ITSZ_256KB
mdefine_line|#define HARRIER_ITSZ_256KB&t;&t;0x06
DECL|macro|HARRIER_ITSZ_512KB
mdefine_line|#define HARRIER_ITSZ_512KB&t;&t;0x07
DECL|macro|HARRIER_ITSZ_1MB
mdefine_line|#define HARRIER_ITSZ_1MB&t;&t;0x08
DECL|macro|HARRIER_ITSZ_2MB
mdefine_line|#define HARRIER_ITSZ_2MB&t;&t;0x09
DECL|macro|HARRIER_ITSZ_4MB
mdefine_line|#define HARRIER_ITSZ_4MB&t;&t;0x0A
DECL|macro|HARRIER_ITSZ_8MB
mdefine_line|#define HARRIER_ITSZ_8MB&t;&t;0x0B
DECL|macro|HARRIER_ITSZ_16MB
mdefine_line|#define HARRIER_ITSZ_16MB&t;&t;0x0C
DECL|macro|HARRIER_ITSZ_32MB
mdefine_line|#define HARRIER_ITSZ_32MB&t;&t;0x0D
DECL|macro|HARRIER_ITSZ_64MB
mdefine_line|#define HARRIER_ITSZ_64MB&t;&t;0x0E
DECL|macro|HARRIER_ITSZ_128MB
mdefine_line|#define HARRIER_ITSZ_128MB&t;&t;0x0F
DECL|macro|HARRIER_ITSZ_256MB
mdefine_line|#define HARRIER_ITSZ_256MB&t;&t;0x10
DECL|macro|HARRIER_ITSZ_512MB
mdefine_line|#define HARRIER_ITSZ_512MB&t;&t;0x11
DECL|macro|HARRIER_ITSZ_1GB
mdefine_line|#define HARRIER_ITSZ_1GB&t;&t;0x12
DECL|macro|HARRIER_ITSZ_2GB
mdefine_line|#define HARRIER_ITSZ_2GB&t;&t;0x13
multiline_comment|/* inbound translation offset */
DECL|macro|HARRIER_ITOF_SHIFT
mdefine_line|#define HARRIER_ITOF_SHIFT&t;&t;0x10
DECL|macro|HARRIER_ITOF_MSK
mdefine_line|#define HARRIER_ITOF_MSK&t;&t;0xffff
multiline_comment|/* inbound translation atttributes */
DECL|macro|HARRIER_ITAT_PRE
mdefine_line|#define HARRIER_ITAT_PRE&t;&t;(1&lt;&lt;3)
DECL|macro|HARRIER_ITAT_RAE
mdefine_line|#define HARRIER_ITAT_RAE&t;&t;(1&lt;&lt;4)
DECL|macro|HARRIER_ITAT_WPE
mdefine_line|#define HARRIER_ITAT_WPE&t;&t;(1&lt;&lt;5)
DECL|macro|HARRIER_ITAT_MEM
mdefine_line|#define HARRIER_ITAT_MEM&t;&t;(1&lt;&lt;6)
DECL|macro|HARRIER_ITAT_ENA
mdefine_line|#define HARRIER_ITAT_ENA&t;&t;(1&lt;&lt;7)
DECL|macro|HARRIER_ITAT_GBL
mdefine_line|#define HARRIER_ITAT_GBL&t;&t;(1&lt;&lt;16)
DECL|macro|HARRIER_LBA_OFF
mdefine_line|#define HARRIER_LBA_OFF&t;&t;&t;0x80
DECL|macro|HARRIER_LBA_MSK
mdefine_line|#define HARRIER_LBA_MSK&t;&t;&t;(1&lt;&lt;31)
DECL|macro|HARRIER_XCSR_SIZE
mdefine_line|#define HARRIER_XCSR_SIZE&t;&t;1024
multiline_comment|/* macros to calculate message passing register offsets */
DECL|macro|HARRIER_MP_XCSR
mdefine_line|#define HARRIER_MP_XCSR(x) ((u32)HARRIER_XCSR_MP_BASE_OFF + (u32)x)
DECL|macro|HARRIER_MP_PMEP
mdefine_line|#define HARRIER_MP_PMEP(x) ((u32)HARRIER_PMEP_MP_BASE_OFF + (u32)x)
multiline_comment|/*&n; * Define PCI configuration space register offsets&n; */
DECL|macro|HARRIER_MPBAR_OFF
mdefine_line|#define HARRIER_MPBAR_OFF&t;&t;PCI_BASE_ADDRESS_0
DECL|macro|HARRIER_ITBAR0_OFF
mdefine_line|#define HARRIER_ITBAR0_OFF&t;&t;PCI_BASE_ADDRESS_1
DECL|macro|HARRIER_ITBAR1_OFF
mdefine_line|#define HARRIER_ITBAR1_OFF&t;&t;PCI_BASE_ADDRESS_2
DECL|macro|HARRIER_ITBAR2_OFF
mdefine_line|#define HARRIER_ITBAR2_OFF&t;&t;PCI_BASE_ADDRESS_3
DECL|macro|HARRIER_ITBAR3_OFF
mdefine_line|#define HARRIER_ITBAR3_OFF&t;&t;PCI_BASE_ADDRESS_4
DECL|macro|HARRIER_XCSR_CONFIG
mdefine_line|#define HARRIER_XCSR_CONFIG(x) ((u32)HARRIER_XCSR_TO_PCFS_OFF + (u32)x)
macro_line|#endif&t;&t;&t;&t;/* __ASMPPC_HARRIER_DEFS_H */
eof
