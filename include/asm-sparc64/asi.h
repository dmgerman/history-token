multiline_comment|/* $Id: asi.h,v 1.1 1996/11/20 12:59:45 davem Exp $ */
macro_line|#ifndef _SPARC64_ASI_H
DECL|macro|_SPARC64_ASI_H
mdefine_line|#define _SPARC64_ASI_H
multiline_comment|/* asi.h:  Address Space Identifier values for the V9.&n; *&n; * Copyright (C) 1996 David S. Miller (davem@caip.rutgers.edu)&n; */
multiline_comment|/* V9 Architecture mandary ASIs. */
DECL|macro|ASI_N
mdefine_line|#define ASI_N&t;&t;&t;0x04 /* Nucleus&t;&t;&t;&t;&t;*/
DECL|macro|ASI_NL
mdefine_line|#define ASI_NL&t;&t;&t;0x0c /* Nucleus, little endian&t;&t;&t;*/
DECL|macro|ASI_AIUP
mdefine_line|#define ASI_AIUP&t;&t;0x10 /* Primary, user&t;&t;&t;&t;*/
DECL|macro|ASI_AIUS
mdefine_line|#define ASI_AIUS&t;&t;0x11 /* Secondary, user&t;&t;&t;&t;*/
DECL|macro|ASI_AIUPL
mdefine_line|#define ASI_AIUPL&t;&t;0x18 /* Primary, user, little endian&t;&t;*/
DECL|macro|ASI_AIUSL
mdefine_line|#define ASI_AIUSL&t;&t;0x19 /* Secondary, user, little endian&t;&t;*/
DECL|macro|ASI_P
mdefine_line|#define ASI_P&t;&t;&t;0x80 /* Primary, implicit&t;&t;&t;*/
DECL|macro|ASI_S
mdefine_line|#define ASI_S&t;&t;&t;0x81 /* Secondary, implicit&t;&t;&t;*/
DECL|macro|ASI_PNF
mdefine_line|#define ASI_PNF&t;&t;&t;0x82 /* Primary, no fault&t;&t;&t;*/
DECL|macro|ASI_SNF
mdefine_line|#define ASI_SNF&t;&t;&t;0x83 /* Secondary, no fault&t;&t;&t;*/
DECL|macro|ASI_PL
mdefine_line|#define ASI_PL&t;&t;&t;0x88 /* Primary, implicit, little endian&t;*/
DECL|macro|ASI_SL
mdefine_line|#define ASI_SL&t;&t;&t;0x89 /* Secondary, implicit, little endian&t;*/
DECL|macro|ASI_PNFL
mdefine_line|#define ASI_PNFL&t;&t;0x8a /* Primary, no fault, little endian&t;*/
DECL|macro|ASI_SNFL
mdefine_line|#define ASI_SNFL&t;&t;0x8b /* Secondary, no fault, little endian&t;*/
multiline_comment|/* SpitFire extended ASIs. */
DECL|macro|ASI_PHYS_USE_EC
mdefine_line|#define ASI_PHYS_USE_EC&t;&t;0x14 /* PADDR, E-cachable&t;&t;&t;*/
DECL|macro|ASI_PHYS_BYPASS_EC_E
mdefine_line|#define ASI_PHYS_BYPASS_EC_E&t;0x15 /* PADDR, E-cachable, E-bit&t;&t;*/
DECL|macro|ASI_PHYS_USE_EC_L
mdefine_line|#define ASI_PHYS_USE_EC_L&t;0x1c /* PADDR, E-cachable, little endian&t;*/
DECL|macro|ASI_PHYS_BYPASS_EC_E_L
mdefine_line|#define ASI_PHYS_BYPASS_EC_E_L&t;0x1d /* PADDR, E-cachable, E-bit, little endian&t;*/
DECL|macro|ASI_NUCLEUS_QUAD_LDD
mdefine_line|#define ASI_NUCLEUS_QUAD_LDD&t;0x24 /* Cachable, qword load&t;&t;&t;*/
DECL|macro|ASI_NUCLEUS_QUAD_LDD_L
mdefine_line|#define ASI_NUCLEUS_QUAD_LDD_L&t;0x2c /* Cachable, qword load, little endian &t;*/
DECL|macro|ASI_LSU_CONTROL
mdefine_line|#define ASI_LSU_CONTROL&t;&t;0x45 /* Load-store control unit&t;&t;&t;*/
DECL|macro|ASI_DCACHE_DATA
mdefine_line|#define ASI_DCACHE_DATA&t;&t;0x46 /* Data cache data-ram diag access&t;&t;*/
DECL|macro|ASI_DCACHE_TAG
mdefine_line|#define ASI_DCACHE_TAG&t;&t;0x47 /* Data cache tag/valid ram diag access&t;*/
DECL|macro|ASI_INTR_DISPATCH_STAT
mdefine_line|#define ASI_INTR_DISPATCH_STAT&t;0x48 /* IRQ vector dispatch status&t;&t;*/
DECL|macro|ASI_INTR_RECEIVE
mdefine_line|#define ASI_INTR_RECEIVE&t;0x49 /* IRQ vector receive status&t;&t;*/
DECL|macro|ASI_UPA_CONFIG
mdefine_line|#define ASI_UPA_CONFIG&t;&t;0x4a /* UPA config space&t;&t;&t;*/
DECL|macro|ASI_ESTATE_ERROR_EN
mdefine_line|#define ASI_ESTATE_ERROR_EN&t;0x4b /* E-cache error enable space&t;&t;*/
DECL|macro|ASI_AFSR
mdefine_line|#define ASI_AFSR&t;&t;0x4c /* Async fault status register&t;&t;*/
DECL|macro|ASI_AFAR
mdefine_line|#define ASI_AFAR&t;&t;0x4d /* Async fault address register&t;&t;*/
DECL|macro|ASI_EC_TAG_DATA
mdefine_line|#define ASI_EC_TAG_DATA&t;&t;0x4e /* E-cache tag/valid ram diag access&t;*/
DECL|macro|ASI_IMMU
mdefine_line|#define ASI_IMMU&t;&t;0x50 /* Insn-MMU main register space&t;&t;*/
DECL|macro|ASI_IMMU_TSB_8KB_PTR
mdefine_line|#define ASI_IMMU_TSB_8KB_PTR&t;0x51 /* Insn-MMU 8KB TSB pointer register&t;*/
DECL|macro|ASI_IMMU_TSB_64KB_PTR
mdefine_line|#define ASI_IMMU_TSB_64KB_PTR&t;0x52 /* Insn-MMU 64KB TSB pointer register&t;*/
DECL|macro|ASI_ITLB_DATA_IN
mdefine_line|#define ASI_ITLB_DATA_IN&t;0x54 /* Insn-MMU TLB data in register&t;&t;*/
DECL|macro|ASI_ITLB_DATA_ACCESS
mdefine_line|#define ASI_ITLB_DATA_ACCESS&t;0x55 /* Insn-MMU TLB data access register&t;*/
DECL|macro|ASI_ITLB_TAG_READ
mdefine_line|#define ASI_ITLB_TAG_READ&t;0x56 /* Insn-MMU TLB tag read register&t;&t;*/
DECL|macro|ASI_IMMU_DEMAP
mdefine_line|#define ASI_IMMU_DEMAP&t;&t;0x57 /* Insn-MMU TLB demap&t;&t;&t;*/
DECL|macro|ASI_DMMU
mdefine_line|#define ASI_DMMU&t;&t;0x58 /* Data-MMU main register space&t;&t;*/
DECL|macro|ASI_DMMU_TSB_8KB_PTR
mdefine_line|#define ASI_DMMU_TSB_8KB_PTR&t;0x59 /* Data-MMU 8KB TSB pointer register&t;*/
DECL|macro|ASI_DMMU_TSB_64KB_PTR
mdefine_line|#define ASI_DMMU_TSB_64KB_PTR&t;0x5a /* Data-MMU 16KB TSB pointer register&t;*/
DECL|macro|ASI_DMMU_TSB_DIRECT_PTR
mdefine_line|#define ASI_DMMU_TSB_DIRECT_PTR&t;0x5b /* Data-MMU TSB direct pointer register&t;*/
DECL|macro|ASI_DTLB_DATA_IN
mdefine_line|#define ASI_DTLB_DATA_IN&t;0x5c /* Data-MMU TLB data in register&t;&t;*/
DECL|macro|ASI_DTLB_DATA_ACCESS
mdefine_line|#define ASI_DTLB_DATA_ACCESS&t;0x5d /* Data-MMU TLB data access register&t;*/
DECL|macro|ASI_DTLB_TAG_READ
mdefine_line|#define ASI_DTLB_TAG_READ&t;0x5e /* Data-MMU TLB tag read register&t;&t;*/
DECL|macro|ASI_DMMU_DEMAP
mdefine_line|#define ASI_DMMU_DEMAP&t;&t;0x5f /* Data-MMU TLB demap&t;&t;&t;*/
DECL|macro|ASI_IC_INSTR
mdefine_line|#define ASI_IC_INSTR&t;&t;0x66 /* Insn cache instrucion ram diag access&t;*/
DECL|macro|ASI_IC_TAG
mdefine_line|#define ASI_IC_TAG&t;&t;0x67 /* Insn cache tag/valid ram diag access&t;*/
DECL|macro|ASI_IC_PRE_DECODE
mdefine_line|#define ASI_IC_PRE_DECODE&t;0x6e /* Insn cache pre-decode ram diag access&t;*/
DECL|macro|ASI_IC_NEXT_FIELD
mdefine_line|#define ASI_IC_NEXT_FIELD&t;0x6f /* Insn cache next-field ram diag access&t;*/
DECL|macro|ASI_BLK_AIUP
mdefine_line|#define ASI_BLK_AIUP&t;&t;0x70 /* Primary, user, block load/store&t;&t;*/
DECL|macro|ASI_BLK_AIUS
mdefine_line|#define ASI_BLK_AIUS&t;&t;0x71 /* Secondary, user, block load/store&t;*/
DECL|macro|ASI_EC_W
mdefine_line|#define ASI_EC_W&t;&t;0x76 /* E-cache diag write access&t;&t;*/
DECL|macro|ASI_UDB_ERROR_W
mdefine_line|#define ASI_UDB_ERROR_W&t;&t;0x77 /* External UDB error registers write&t;*/
DECL|macro|ASI_UDB_CONTROL_W
mdefine_line|#define ASI_UDB_CONTROL_W&t;0x77 /* External UDB control registers write&t;*/
DECL|macro|ASI_UDB_INTR_W
mdefine_line|#define ASI_UDB_INTR_W&t;&t;0x77 /* External UDB IRQ vector dispatch write&t;*/
DECL|macro|ASI_BLK_AIUPL
mdefine_line|#define ASI_BLK_AIUPL&t;&t;0x78 /* Primary, user, little, blk ld/st&t;*/
DECL|macro|ASI_BLK_AIUSL
mdefine_line|#define ASI_BLK_AIUSL&t;&t;0x79 /* Secondary, user, little, blk ld/st&t;*/
DECL|macro|ASI_EC_R
mdefine_line|#define ASI_EC_R&t;&t;0x7e /* E-cache diag read access&t;&t;*/
DECL|macro|ASI_UDBH_ERROR_R
mdefine_line|#define ASI_UDBH_ERROR_R&t;0x7f /* External UDB error registers read hi&t;*/
DECL|macro|ASI_UDBL_ERROR_R
mdefine_line|#define ASI_UDBL_ERROR_R&t;0x7f /* External UDB error registers read low&t;*/
DECL|macro|ASI_UDBH_CONTROL_R
mdefine_line|#define ASI_UDBH_CONTROL_R&t;0x7f /* External UDB control registers read hi&t;*/
DECL|macro|ASI_UDBL_CONTROL_R
mdefine_line|#define ASI_UDBL_CONTROL_R&t;0x7f /* External UDB control registers read low&t;*/
DECL|macro|ASI_UDB_INTR_R
mdefine_line|#define ASI_UDB_INTR_R&t;&t;0x7f /* External UDB IRQ vector dispatch read&t;*/
DECL|macro|ASI_PST8_P
mdefine_line|#define ASI_PST8_P&t;&t;0xc0 /* Primary, 8 8-bit, partial&t;&t;*/
DECL|macro|ASI_PST8_S
mdefine_line|#define ASI_PST8_S&t;&t;0xc1 /* Secondary, 8 8-bit, partial&t;&t;*/
DECL|macro|ASI_PST16_P
mdefine_line|#define ASI_PST16_P&t;&t;0xc2 /* Primary, 4 16-bit, partial&t;&t;*/
DECL|macro|ASI_PST16_S
mdefine_line|#define ASI_PST16_S&t;&t;0xc3 /* Seconary, 4 16-bit, partial&t;&t;*/
DECL|macro|ASI_PST32_P
mdefine_line|#define ASI_PST32_P&t;&t;0xc4 /* Primary, 2 32-bit, partial&t;&t;*/
DECL|macro|ASI_PST32_S
mdefine_line|#define ASI_PST32_S&t;&t;0xc5 /* Secondary, 2 32-bit, partial&t;&t;*/
DECL|macro|ASI_PST8_PL
mdefine_line|#define ASI_PST8_PL&t;&t;0xc8 /* Primary, 8 8-bit, partial, little&t;*/
DECL|macro|ASI_PST8_SL
mdefine_line|#define ASI_PST8_SL&t;&t;0xc9 /* Secondary, 8 8-bit, partial, little&t;*/
DECL|macro|ASI_PST16_PL
mdefine_line|#define ASI_PST16_PL&t;&t;0xca /* Primary, 4 16-bit, partial, little&t;*/
DECL|macro|ASI_PST16_SL
mdefine_line|#define ASI_PST16_SL&t;&t;0xcb /* Seconary, 4 16-bit, partial, little&t;*/
DECL|macro|ASI_PST32_PL
mdefine_line|#define ASI_PST32_PL&t;&t;0xcc /* Primary, 2 32-bit, partial, little&t;*/
DECL|macro|ASI_PST32_SL
mdefine_line|#define ASI_PST32_SL&t;&t;0xcd /* Secondary, 2 32-bit, partial, little&t;*/
DECL|macro|ASI_FL8_P
mdefine_line|#define ASI_FL8_P&t;&t;0xd0 /* Primary, 1 8-bit, fpu ld/st&t;&t;*/
DECL|macro|ASI_FL8_S
mdefine_line|#define ASI_FL8_S&t;&t;0xd1 /* Secondary, 1 8-bit, fpu ld/st&t;&t;*/
DECL|macro|ASI_FL16_P
mdefine_line|#define ASI_FL16_P&t;&t;0xd2 /* Primary, 1 16-bit, fpu ld/st&t;&t;*/
DECL|macro|ASI_FL16_S
mdefine_line|#define ASI_FL16_S&t;&t;0xd3 /* Secondary, 1 16-bit, fpu ld/st&t;&t;*/
DECL|macro|ASI_FL8_PL
mdefine_line|#define ASI_FL8_PL&t;&t;0xd8 /* Primary, 1 8-bit, fpu ld/st, little&t;*/
DECL|macro|ASI_FL8_SL
mdefine_line|#define ASI_FL8_SL&t;&t;0xd9 /* Secondary, 1 8-bit, fpu ld/st, little&t;*/
DECL|macro|ASI_FL16_PL
mdefine_line|#define ASI_FL16_PL&t;&t;0xda /* Primary, 1 16-bit, fpu ld/st, little&t;*/
DECL|macro|ASI_FL16_SL
mdefine_line|#define ASI_FL16_SL&t;&t;0xdb /* Secondary, 1 16-bit, fpu ld/st, little&t;*/
DECL|macro|ASI_BLK_COMMIT_P
mdefine_line|#define ASI_BLK_COMMIT_P&t;0xe0 /* Primary, blk store commit&t;&t;*/
DECL|macro|ASI_BLK_COMMIT_S
mdefine_line|#define ASI_BLK_COMMIT_S&t;0xe1 /* Secondary, blk store commit&t;&t;*/
DECL|macro|ASI_BLK_P
mdefine_line|#define ASI_BLK_P&t;&t;0xf0 /* Primary, blk ld/st&t;&t;&t;*/
DECL|macro|ASI_BLK_S
mdefine_line|#define ASI_BLK_S&t;&t;0xf1 /* Secondary, blk ld/st&t;&t;&t;*/
DECL|macro|ASI_BLK_PL
mdefine_line|#define ASI_BLK_PL&t;&t;0xf8 /* Primary, blk ld/st, little&t;&t;*/
DECL|macro|ASI_BLK_SL
mdefine_line|#define ASI_BLK_SL&t;&t;0xf9 /* Secondary, blk ld/st, little&t;&t;*/
macro_line|#endif /* _SPARC64_ASI_H */
eof
