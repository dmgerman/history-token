multiline_comment|/*&n; * mcs01_pci.h&n; *&n; * Carsten Langgaard, carstenl@mips.com&n; * Copyright (C) 2002 MIPS Technologies, Inc.  All rights reserved.&n; *&n; * ########################################################################&n; *&n; * PCI Register definitions for the MIPS System Controller.&n; */
macro_line|#ifndef MSC01_PCI_H
DECL|macro|MSC01_PCI_H
mdefine_line|#define MSC01_PCI_H
multiline_comment|/*****************************************************************************&n; * Register offset addresses&n; ****************************************************************************/
DECL|macro|MSC01_PCI_ID_OFS
mdefine_line|#define MSC01_PCI_ID_OFS&t;&t;0x0000
DECL|macro|MSC01_PCI_SC2PMBASL_OFS
mdefine_line|#define MSC01_PCI_SC2PMBASL_OFS&t;&t;0x0208
DECL|macro|MSC01_PCI_SC2PMMSKL_OFS
mdefine_line|#define MSC01_PCI_SC2PMMSKL_OFS&t;&t;0x0218
DECL|macro|MSC01_PCI_SC2PMMAPL_OFS
mdefine_line|#define MSC01_PCI_SC2PMMAPL_OFS&t;&t;0x0228
DECL|macro|MSC01_PCI_SC2PIOBASL_OFS
mdefine_line|#define MSC01_PCI_SC2PIOBASL_OFS&t;0x0248
DECL|macro|MSC01_PCI_SC2PIOMSKL_OFS
mdefine_line|#define MSC01_PCI_SC2PIOMSKL_OFS&t;0x0258
DECL|macro|MSC01_PCI_SC2PIOMAPL_OFS
mdefine_line|#define MSC01_PCI_SC2PIOMAPL_OFS&t;0x0268
DECL|macro|MSC01_PCI_P2SCMSKL_OFS
mdefine_line|#define MSC01_PCI_P2SCMSKL_OFS&t;&t;0x0308
DECL|macro|MSC01_PCI_P2SCMAPL_OFS
mdefine_line|#define MSC01_PCI_P2SCMAPL_OFS&t;&t;0x0318
DECL|macro|MSC01_PCI_INTCFG_OFS
mdefine_line|#define MSC01_PCI_INTCFG_OFS&t;&t;0x0600
DECL|macro|MSC01_PCI_INTSTAT_OFS
mdefine_line|#define MSC01_PCI_INTSTAT_OFS&t;&t;0x0608
DECL|macro|MSC01_PCI_CFGADDR_OFS
mdefine_line|#define MSC01_PCI_CFGADDR_OFS&t;&t;0x0610
DECL|macro|MSC01_PCI_CFGDATA_OFS
mdefine_line|#define MSC01_PCI_CFGDATA_OFS&t;&t;0x0618
DECL|macro|MSC01_PCI_IACK_OFS
mdefine_line|#define MSC01_PCI_IACK_OFS&t;&t;0x0620
DECL|macro|MSC01_PCI_HEAD0_OFS
mdefine_line|#define MSC01_PCI_HEAD0_OFS&t;&t;0x2000  /* DevID, VendorID */
DECL|macro|MSC01_PCI_HEAD1_OFS
mdefine_line|#define MSC01_PCI_HEAD1_OFS&t;&t;0x2008  /* Status, Command */
DECL|macro|MSC01_PCI_HEAD2_OFS
mdefine_line|#define MSC01_PCI_HEAD2_OFS&t;&t;0x2010  /* Class code, RevID */
DECL|macro|MSC01_PCI_HEAD3_OFS
mdefine_line|#define MSC01_PCI_HEAD3_OFS&t;&t;0x2018  /* bist, header, latency */
DECL|macro|MSC01_PCI_HEAD4_OFS
mdefine_line|#define MSC01_PCI_HEAD4_OFS&t;&t;0x2020  /* BAR 0 */
DECL|macro|MSC01_PCI_HEAD5_OFS
mdefine_line|#define MSC01_PCI_HEAD5_OFS&t;&t;0x2028  /* BAR 1 */
DECL|macro|MSC01_PCI_HEAD6_OFS
mdefine_line|#define MSC01_PCI_HEAD6_OFS&t;&t;0x2030  /* BAR 2 */
DECL|macro|MSC01_PCI_HEAD7_OFS
mdefine_line|#define MSC01_PCI_HEAD7_OFS&t;&t;0x2038  /* BAR 3 */
DECL|macro|MSC01_PCI_HEAD8_OFS
mdefine_line|#define MSC01_PCI_HEAD8_OFS&t;&t;0x2040  /* BAR 4 */
DECL|macro|MSC01_PCI_HEAD9_OFS
mdefine_line|#define MSC01_PCI_HEAD9_OFS&t;&t;0x2048  /* BAR 5 */
DECL|macro|MSC01_PCI_HEAD10_OFS
mdefine_line|#define MSC01_PCI_HEAD10_OFS&t;&t;0x2050  /* CardBus CIS Ptr */
DECL|macro|MSC01_PCI_HEAD11_OFS
mdefine_line|#define MSC01_PCI_HEAD11_OFS&t;&t;0x2058  /* SubSystem ID, -VendorID */
DECL|macro|MSC01_PCI_HEAD12_OFS
mdefine_line|#define MSC01_PCI_HEAD12_OFS&t;&t;0x2060  /* ROM BAR */
DECL|macro|MSC01_PCI_HEAD13_OFS
mdefine_line|#define MSC01_PCI_HEAD13_OFS&t;&t;0x2068  /* Capabilities ptr */
DECL|macro|MSC01_PCI_HEAD14_OFS
mdefine_line|#define MSC01_PCI_HEAD14_OFS&t;&t;0x2070  /* reserved */
DECL|macro|MSC01_PCI_HEAD15_OFS
mdefine_line|#define MSC01_PCI_HEAD15_OFS&t;&t;0x2078  /* Maxl, ming, intpin, int */
DECL|macro|MSC01_PCI_BAR0_OFS
mdefine_line|#define MSC01_PCI_BAR0_OFS&t;&t;0x2220
DECL|macro|MSC01_PCI_CFG_OFS
mdefine_line|#define MSC01_PCI_CFG_OFS&t;&t;0x2380
DECL|macro|MSC01_PCI_SWAP_OFS
mdefine_line|#define MSC01_PCI_SWAP_OFS&t;&t;0x2388
multiline_comment|/*****************************************************************************&n; * Register encodings&n; ****************************************************************************/
DECL|macro|MSC01_PCI_ID_ID_SHF
mdefine_line|#define MSC01_PCI_ID_ID_SHF&t;&t;16
DECL|macro|MSC01_PCI_ID_ID_MSK
mdefine_line|#define MSC01_PCI_ID_ID_MSK&t;&t;0x00ff0000
DECL|macro|MSC01_PCI_ID_ID_HOSTBRIDGE
mdefine_line|#define MSC01_PCI_ID_ID_HOSTBRIDGE&t;82
DECL|macro|MSC01_PCI_ID_MAR_SHF
mdefine_line|#define MSC01_PCI_ID_MAR_SHF&t;&t;8
DECL|macro|MSC01_PCI_ID_MAR_MSK
mdefine_line|#define MSC01_PCI_ID_MAR_MSK&t;&t;0x0000ff00
DECL|macro|MSC01_PCI_ID_MIR_SHF
mdefine_line|#define MSC01_PCI_ID_MIR_SHF&t;&t;0
DECL|macro|MSC01_PCI_ID_MIR_MSK
mdefine_line|#define MSC01_PCI_ID_MIR_MSK&t;&t;0x000000ff
DECL|macro|MSC01_PCI_SC2PMBASL_BAS_SHF
mdefine_line|#define MSC01_PCI_SC2PMBASL_BAS_SHF&t;24
DECL|macro|MSC01_PCI_SC2PMBASL_BAS_MSK
mdefine_line|#define MSC01_PCI_SC2PMBASL_BAS_MSK&t;0xff000000
DECL|macro|MSC01_PCI_SC2PMMSKL_MSK_SHF
mdefine_line|#define MSC01_PCI_SC2PMMSKL_MSK_SHF&t;24
DECL|macro|MSC01_PCI_SC2PMMSKL_MSK_MSK
mdefine_line|#define MSC01_PCI_SC2PMMSKL_MSK_MSK&t;0xff000000
DECL|macro|MSC01_PCI_SC2PMMAPL_MAP_SHF
mdefine_line|#define MSC01_PCI_SC2PMMAPL_MAP_SHF&t;24
DECL|macro|MSC01_PCI_SC2PMMAPL_MAP_MSK
mdefine_line|#define MSC01_PCI_SC2PMMAPL_MAP_MSK&t;0xff000000
DECL|macro|MSC01_PCI_SC2PIOBASL_BAS_SHF
mdefine_line|#define MSC01_PCI_SC2PIOBASL_BAS_SHF&t;24
DECL|macro|MSC01_PCI_SC2PIOBASL_BAS_MSK
mdefine_line|#define MSC01_PCI_SC2PIOBASL_BAS_MSK&t;0xff000000
DECL|macro|MSC01_PCI_SC2PIOMSKL_MSK_SHF
mdefine_line|#define MSC01_PCI_SC2PIOMSKL_MSK_SHF&t;24
DECL|macro|MSC01_PCI_SC2PIOMSKL_MSK_MSK
mdefine_line|#define MSC01_PCI_SC2PIOMSKL_MSK_MSK&t;0xff000000
DECL|macro|MSC01_PCI_SC2PIOMAPL_MAP_SHF
mdefine_line|#define MSC01_PCI_SC2PIOMAPL_MAP_SHF&t;24
DECL|macro|MSC01_PCI_SC2PIOMAPL_MAP_MSK
mdefine_line|#define MSC01_PCI_SC2PIOMAPL_MAP_MSK&t;0xff000000
DECL|macro|MSC01_PCI_P2SCMSKL_MSK_SHF
mdefine_line|#define MSC01_PCI_P2SCMSKL_MSK_SHF&t;24
DECL|macro|MSC01_PCI_P2SCMSKL_MSK_MSK
mdefine_line|#define MSC01_PCI_P2SCMSKL_MSK_MSK&t;0xff000000
DECL|macro|MSC01_PCI_P2SCMAPL_MAP_SHF
mdefine_line|#define MSC01_PCI_P2SCMAPL_MAP_SHF&t;24
DECL|macro|MSC01_PCI_P2SCMAPL_MAP_MSK
mdefine_line|#define MSC01_PCI_P2SCMAPL_MAP_MSK&t;0xff000000
DECL|macro|MSC01_PCI_INTCFG_RST_SHF
mdefine_line|#define MSC01_PCI_INTCFG_RST_SHF        10
DECL|macro|MSC01_PCI_INTCFG_RST_MSK
mdefine_line|#define MSC01_PCI_INTCFG_RST_MSK        0x00000400
DECL|macro|MSC01_PCI_INTCFG_RST_BIT
mdefine_line|#define MSC01_PCI_INTCFG_RST_BIT        0x00000400
DECL|macro|MSC01_PCI_INTCFG_MWE_SHF
mdefine_line|#define MSC01_PCI_INTCFG_MWE_SHF        9
DECL|macro|MSC01_PCI_INTCFG_MWE_MSK
mdefine_line|#define MSC01_PCI_INTCFG_MWE_MSK        0x00000200
DECL|macro|MSC01_PCI_INTCFG_MWE_BIT
mdefine_line|#define MSC01_PCI_INTCFG_MWE_BIT        0x00000200
DECL|macro|MSC01_PCI_INTCFG_DTO_SHF
mdefine_line|#define MSC01_PCI_INTCFG_DTO_SHF        8
DECL|macro|MSC01_PCI_INTCFG_DTO_MSK
mdefine_line|#define MSC01_PCI_INTCFG_DTO_MSK        0x00000100
DECL|macro|MSC01_PCI_INTCFG_DTO_BIT
mdefine_line|#define MSC01_PCI_INTCFG_DTO_BIT        0x00000100
DECL|macro|MSC01_PCI_INTCFG_MA_SHF
mdefine_line|#define MSC01_PCI_INTCFG_MA_SHF         7
DECL|macro|MSC01_PCI_INTCFG_MA_MSK
mdefine_line|#define MSC01_PCI_INTCFG_MA_MSK         0x00000080
DECL|macro|MSC01_PCI_INTCFG_MA_BIT
mdefine_line|#define MSC01_PCI_INTCFG_MA_BIT         0x00000080
DECL|macro|MSC01_PCI_INTCFG_TA_SHF
mdefine_line|#define MSC01_PCI_INTCFG_TA_SHF         6
DECL|macro|MSC01_PCI_INTCFG_TA_MSK
mdefine_line|#define MSC01_PCI_INTCFG_TA_MSK         0x00000040
DECL|macro|MSC01_PCI_INTCFG_TA_BIT
mdefine_line|#define MSC01_PCI_INTCFG_TA_BIT         0x00000040
DECL|macro|MSC01_PCI_INTCFG_RTY_SHF
mdefine_line|#define MSC01_PCI_INTCFG_RTY_SHF        5
DECL|macro|MSC01_PCI_INTCFG_RTY_MSK
mdefine_line|#define MSC01_PCI_INTCFG_RTY_MSK        0x00000020
DECL|macro|MSC01_PCI_INTCFG_RTY_BIT
mdefine_line|#define MSC01_PCI_INTCFG_RTY_BIT        0x00000020
DECL|macro|MSC01_PCI_INTCFG_MWP_SHF
mdefine_line|#define MSC01_PCI_INTCFG_MWP_SHF        4
DECL|macro|MSC01_PCI_INTCFG_MWP_MSK
mdefine_line|#define MSC01_PCI_INTCFG_MWP_MSK        0x00000010
DECL|macro|MSC01_PCI_INTCFG_MWP_BIT
mdefine_line|#define MSC01_PCI_INTCFG_MWP_BIT        0x00000010
DECL|macro|MSC01_PCI_INTCFG_MRP_SHF
mdefine_line|#define MSC01_PCI_INTCFG_MRP_SHF        3
DECL|macro|MSC01_PCI_INTCFG_MRP_MSK
mdefine_line|#define MSC01_PCI_INTCFG_MRP_MSK        0x00000008
DECL|macro|MSC01_PCI_INTCFG_MRP_BIT
mdefine_line|#define MSC01_PCI_INTCFG_MRP_BIT        0x00000008
DECL|macro|MSC01_PCI_INTCFG_SWP_SHF
mdefine_line|#define MSC01_PCI_INTCFG_SWP_SHF        2
DECL|macro|MSC01_PCI_INTCFG_SWP_MSK
mdefine_line|#define MSC01_PCI_INTCFG_SWP_MSK        0x00000004
DECL|macro|MSC01_PCI_INTCFG_SWP_BIT
mdefine_line|#define MSC01_PCI_INTCFG_SWP_BIT        0x00000004
DECL|macro|MSC01_PCI_INTCFG_SRP_SHF
mdefine_line|#define MSC01_PCI_INTCFG_SRP_SHF        1
DECL|macro|MSC01_PCI_INTCFG_SRP_MSK
mdefine_line|#define MSC01_PCI_INTCFG_SRP_MSK        0x00000002
DECL|macro|MSC01_PCI_INTCFG_SRP_BIT
mdefine_line|#define MSC01_PCI_INTCFG_SRP_BIT        0x00000002
DECL|macro|MSC01_PCI_INTCFG_SE_SHF
mdefine_line|#define MSC01_PCI_INTCFG_SE_SHF         0
DECL|macro|MSC01_PCI_INTCFG_SE_MSK
mdefine_line|#define MSC01_PCI_INTCFG_SE_MSK         0x00000001
DECL|macro|MSC01_PCI_INTCFG_SE_BIT
mdefine_line|#define MSC01_PCI_INTCFG_SE_BIT         0x00000001
DECL|macro|MSC01_PCI_INTSTAT_RST_SHF
mdefine_line|#define MSC01_PCI_INTSTAT_RST_SHF       10
DECL|macro|MSC01_PCI_INTSTAT_RST_MSK
mdefine_line|#define MSC01_PCI_INTSTAT_RST_MSK       0x00000400
DECL|macro|MSC01_PCI_INTSTAT_RST_BIT
mdefine_line|#define MSC01_PCI_INTSTAT_RST_BIT       0x00000400
DECL|macro|MSC01_PCI_INTSTAT_MWE_SHF
mdefine_line|#define MSC01_PCI_INTSTAT_MWE_SHF       9
DECL|macro|MSC01_PCI_INTSTAT_MWE_MSK
mdefine_line|#define MSC01_PCI_INTSTAT_MWE_MSK       0x00000200
DECL|macro|MSC01_PCI_INTSTAT_MWE_BIT
mdefine_line|#define MSC01_PCI_INTSTAT_MWE_BIT       0x00000200
DECL|macro|MSC01_PCI_INTSTAT_DTO_SHF
mdefine_line|#define MSC01_PCI_INTSTAT_DTO_SHF       8
DECL|macro|MSC01_PCI_INTSTAT_DTO_MSK
mdefine_line|#define MSC01_PCI_INTSTAT_DTO_MSK       0x00000100
DECL|macro|MSC01_PCI_INTSTAT_DTO_BIT
mdefine_line|#define MSC01_PCI_INTSTAT_DTO_BIT       0x00000100
DECL|macro|MSC01_PCI_INTSTAT_MA_SHF
mdefine_line|#define MSC01_PCI_INTSTAT_MA_SHF        7
DECL|macro|MSC01_PCI_INTSTAT_MA_MSK
mdefine_line|#define MSC01_PCI_INTSTAT_MA_MSK        0x00000080
DECL|macro|MSC01_PCI_INTSTAT_MA_BIT
mdefine_line|#define MSC01_PCI_INTSTAT_MA_BIT        0x00000080
DECL|macro|MSC01_PCI_INTSTAT_TA_SHF
mdefine_line|#define MSC01_PCI_INTSTAT_TA_SHF        6
DECL|macro|MSC01_PCI_INTSTAT_TA_MSK
mdefine_line|#define MSC01_PCI_INTSTAT_TA_MSK        0x00000040
DECL|macro|MSC01_PCI_INTSTAT_TA_BIT
mdefine_line|#define MSC01_PCI_INTSTAT_TA_BIT        0x00000040
DECL|macro|MSC01_PCI_INTSTAT_RTY_SHF
mdefine_line|#define MSC01_PCI_INTSTAT_RTY_SHF       5
DECL|macro|MSC01_PCI_INTSTAT_RTY_MSK
mdefine_line|#define MSC01_PCI_INTSTAT_RTY_MSK       0x00000020
DECL|macro|MSC01_PCI_INTSTAT_RTY_BIT
mdefine_line|#define MSC01_PCI_INTSTAT_RTY_BIT       0x00000020
DECL|macro|MSC01_PCI_INTSTAT_MWP_SHF
mdefine_line|#define MSC01_PCI_INTSTAT_MWP_SHF       4
DECL|macro|MSC01_PCI_INTSTAT_MWP_MSK
mdefine_line|#define MSC01_PCI_INTSTAT_MWP_MSK       0x00000010
DECL|macro|MSC01_PCI_INTSTAT_MWP_BIT
mdefine_line|#define MSC01_PCI_INTSTAT_MWP_BIT       0x00000010
DECL|macro|MSC01_PCI_INTSTAT_MRP_SHF
mdefine_line|#define MSC01_PCI_INTSTAT_MRP_SHF       3
DECL|macro|MSC01_PCI_INTSTAT_MRP_MSK
mdefine_line|#define MSC01_PCI_INTSTAT_MRP_MSK       0x00000008
DECL|macro|MSC01_PCI_INTSTAT_MRP_BIT
mdefine_line|#define MSC01_PCI_INTSTAT_MRP_BIT       0x00000008
DECL|macro|MSC01_PCI_INTSTAT_SWP_SHF
mdefine_line|#define MSC01_PCI_INTSTAT_SWP_SHF       2
DECL|macro|MSC01_PCI_INTSTAT_SWP_MSK
mdefine_line|#define MSC01_PCI_INTSTAT_SWP_MSK       0x00000004
DECL|macro|MSC01_PCI_INTSTAT_SWP_BIT
mdefine_line|#define MSC01_PCI_INTSTAT_SWP_BIT       0x00000004
DECL|macro|MSC01_PCI_INTSTAT_SRP_SHF
mdefine_line|#define MSC01_PCI_INTSTAT_SRP_SHF       1
DECL|macro|MSC01_PCI_INTSTAT_SRP_MSK
mdefine_line|#define MSC01_PCI_INTSTAT_SRP_MSK       0x00000002
DECL|macro|MSC01_PCI_INTSTAT_SRP_BIT
mdefine_line|#define MSC01_PCI_INTSTAT_SRP_BIT       0x00000002
DECL|macro|MSC01_PCI_INTSTAT_SE_SHF
mdefine_line|#define MSC01_PCI_INTSTAT_SE_SHF        0
DECL|macro|MSC01_PCI_INTSTAT_SE_MSK
mdefine_line|#define MSC01_PCI_INTSTAT_SE_MSK        0x00000001
DECL|macro|MSC01_PCI_INTSTAT_SE_BIT
mdefine_line|#define MSC01_PCI_INTSTAT_SE_BIT        0x00000001
DECL|macro|MSC01_PCI_CFGADDR_BNUM_SHF
mdefine_line|#define MSC01_PCI_CFGADDR_BNUM_SHF&t;16
DECL|macro|MSC01_PCI_CFGADDR_BNUM_MSK
mdefine_line|#define MSC01_PCI_CFGADDR_BNUM_MSK&t;0x00ff0000
DECL|macro|MSC01_PCI_CFGADDR_DNUM_SHF
mdefine_line|#define MSC01_PCI_CFGADDR_DNUM_SHF&t;11
DECL|macro|MSC01_PCI_CFGADDR_DNUM_MSK
mdefine_line|#define MSC01_PCI_CFGADDR_DNUM_MSK&t;0x0000f800
DECL|macro|MSC01_PCI_CFGADDR_FNUM_SHF
mdefine_line|#define MSC01_PCI_CFGADDR_FNUM_SHF&t;8
DECL|macro|MSC01_PCI_CFGADDR_FNUM_MSK
mdefine_line|#define MSC01_PCI_CFGADDR_FNUM_MSK&t;0x00000700
DECL|macro|MSC01_PCI_CFGADDR_RNUM_SHF
mdefine_line|#define MSC01_PCI_CFGADDR_RNUM_SHF&t;2
DECL|macro|MSC01_PCI_CFGADDR_RNUM_MSK
mdefine_line|#define MSC01_PCI_CFGADDR_RNUM_MSK&t;0x000000fc
DECL|macro|MSC01_PCI_CFGDATA_DATA_SHF
mdefine_line|#define MSC01_PCI_CFGDATA_DATA_SHF&t;0
DECL|macro|MSC01_PCI_CFGDATA_DATA_MSK
mdefine_line|#define MSC01_PCI_CFGDATA_DATA_MSK&t;0xffffffff
multiline_comment|/* The defines below are ONLY valid for a MEM bar! */
DECL|macro|MSC01_PCI_BAR0_SIZE_SHF
mdefine_line|#define MSC01_PCI_BAR0_SIZE_SHF&t;        4
DECL|macro|MSC01_PCI_BAR0_SIZE_MSK
mdefine_line|#define MSC01_PCI_BAR0_SIZE_MSK&t;        0xfffffff0
DECL|macro|MSC01_PCI_BAR0_P_SHF
mdefine_line|#define MSC01_PCI_BAR0_P_SHF&t;        3
DECL|macro|MSC01_PCI_BAR0_P_MSK
mdefine_line|#define MSC01_PCI_BAR0_P_MSK&t;        0x00000008
DECL|macro|MSC01_PCI_BAR0_P_BIT
mdefine_line|#define MSC01_PCI_BAR0_P_BIT&t;        MSC01_PCI_BAR0_P_MSK
DECL|macro|MSC01_PCI_BAR0_D_SHF
mdefine_line|#define MSC01_PCI_BAR0_D_SHF&t;        1
DECL|macro|MSC01_PCI_BAR0_D_MSK
mdefine_line|#define MSC01_PCI_BAR0_D_MSK&t;        0x00000006
DECL|macro|MSC01_PCI_BAR0_T_SHF
mdefine_line|#define MSC01_PCI_BAR0_T_SHF&t;        0
DECL|macro|MSC01_PCI_BAR0_T_MSK
mdefine_line|#define MSC01_PCI_BAR0_T_MSK&t;        0x00000001
DECL|macro|MSC01_PCI_BAR0_T_BIT
mdefine_line|#define MSC01_PCI_BAR0_T_BIT&t;        MSC01_PCI_BAR0_T_MSK
DECL|macro|MSC01_PCI_CFG_RA_SHF
mdefine_line|#define MSC01_PCI_CFG_RA_SHF&t;        17
DECL|macro|MSC01_PCI_CFG_RA_MSK
mdefine_line|#define MSC01_PCI_CFG_RA_MSK&t;        0x00020000
DECL|macro|MSC01_PCI_CFG_RA_BIT
mdefine_line|#define MSC01_PCI_CFG_RA_BIT&t;        MSC01_PCI_CFG_RA_MSK
DECL|macro|MSC01_PCI_CFG_G_SHF
mdefine_line|#define MSC01_PCI_CFG_G_SHF&t;        16
DECL|macro|MSC01_PCI_CFG_G_MSK
mdefine_line|#define MSC01_PCI_CFG_G_MSK&t;        0x00010000
DECL|macro|MSC01_PCI_CFG_G_BIT
mdefine_line|#define MSC01_PCI_CFG_G_BIT&t;        MSC01_PCI_CFG_G_MSK
DECL|macro|MSC01_PCI_CFG_EN_SHF
mdefine_line|#define MSC01_PCI_CFG_EN_SHF&t;        15
DECL|macro|MSC01_PCI_CFG_EN_MSK
mdefine_line|#define MSC01_PCI_CFG_EN_MSK&t;        0x00008000
DECL|macro|MSC01_PCI_CFG_EN_BIT
mdefine_line|#define MSC01_PCI_CFG_EN_BIT&t;        MSC01_PCI_CFG_EN_MSK
DECL|macro|MSC01_PCI_CFG_MAXRTRY_SHF
mdefine_line|#define MSC01_PCI_CFG_MAXRTRY_SHF       0
DECL|macro|MSC01_PCI_CFG_MAXRTRY_MSK
mdefine_line|#define MSC01_PCI_CFG_MAXRTRY_MSK       0x000000ff
DECL|macro|MSC01_PCI_SWAP_IO_SHF
mdefine_line|#define MSC01_PCI_SWAP_IO_SHF&t;&t;18
DECL|macro|MSC01_PCI_SWAP_IO_MSK
mdefine_line|#define MSC01_PCI_SWAP_IO_MSK&t;&t;0x000c0000
DECL|macro|MSC01_PCI_SWAP_MEM_SHF
mdefine_line|#define MSC01_PCI_SWAP_MEM_SHF&t;&t;16
DECL|macro|MSC01_PCI_SWAP_MEM_MSK
mdefine_line|#define MSC01_PCI_SWAP_MEM_MSK&t;&t;0x00030000
DECL|macro|MSC01_PCI_SWAP_BAR0_SHF
mdefine_line|#define MSC01_PCI_SWAP_BAR0_SHF&t;&t;0
DECL|macro|MSC01_PCI_SWAP_BAR0_MSK
mdefine_line|#define MSC01_PCI_SWAP_BAR0_MSK&t;&t;0x00000003
DECL|macro|MSC01_PCI_SWAP_NOSWAP
mdefine_line|#define MSC01_PCI_SWAP_NOSWAP&t;&t;0
DECL|macro|MSC01_PCI_SWAP_BYTESWAP
mdefine_line|#define MSC01_PCI_SWAP_BYTESWAP&t;&t;1
multiline_comment|/*****************************************************************************&n; * Registers absolute addresses&n; ****************************************************************************/
DECL|macro|MSC01_PCI_ID
mdefine_line|#define MSC01_PCI_ID            (MSC01_PCI_REG_BASE + MSC01_PCI_ID_OFS)
DECL|macro|MSC01_PCI_SC2PMBASL
mdefine_line|#define MSC01_PCI_SC2PMBASL     (MSC01_PCI_REG_BASE + MSC01_PCI_SC2PMBASL_OFS)
DECL|macro|MSC01_PCI_SC2PMMSKL
mdefine_line|#define MSC01_PCI_SC2PMMSKL     (MSC01_PCI_REG_BASE + MSC01_PCI_SC2PMMSKL_OFS)
DECL|macro|MSC01_PCI_SC2PMMAPL
mdefine_line|#define MSC01_PCI_SC2PMMAPL     (MSC01_PCI_REG_BASE + MSC01_PCI_SC2PMMAPL_OFS)
DECL|macro|MSC01_PCI_SC2PIOBASL
mdefine_line|#define MSC01_PCI_SC2PIOBASL    (MSC01_PCI_REG_BASE + MSC01_PCI_SC2PIOBASL_OFS)
DECL|macro|MSC01_PCI_SC2PIOMSKL
mdefine_line|#define MSC01_PCI_SC2PIOMSKL    (MSC01_PCI_REG_BASE + MSC01_PCI_SC2PIOMSKL_OFS)
DECL|macro|MSC01_PCI_SC2PIOMAPL
mdefine_line|#define MSC01_PCI_SC2PIOMAPL    (MSC01_PCI_REG_BASE + MSC01_PCI_SC2PIOMAPL_OFS)
DECL|macro|MSC01_PCI_P2SCMSKL
mdefine_line|#define MSC01_PCI_P2SCMSKL      (MSC01_PCI_REG_BASE + MSC01_PCI_P2SCMSKL_OFS)
DECL|macro|MSC01_PCI_P2SCMAPL
mdefine_line|#define MSC01_PCI_P2SCMAPL      (MSC01_PCI_REG_BASE + MSC01_PCI_P2SCMAPL_OFS)
DECL|macro|MSC01_PCI_INTCFG
mdefine_line|#define MSC01_PCI_INTCFG        (MSC01_PCI_REG_BASE + MSC01_PCI_INTCFG_OFS)
DECL|macro|MSC01_PCI_INTSTAT
mdefine_line|#define MSC01_PCI_INTSTAT       (MSC01_PCI_REG_BASE + MSC01_PCI_INTSTAT_OFS)
DECL|macro|MSC01_PCI_CFGADDR
mdefine_line|#define MSC01_PCI_CFGADDR       (MSC01_PCI_REG_BASE + MSC01_PCI_CFGADDR_OFS)
DECL|macro|MSC01_PCI_CFGDATA
mdefine_line|#define MSC01_PCI_CFGDATA       (MSC01_PCI_REG_BASE + MSC01_PCI_CFGDATA_OFS)
DECL|macro|MSC01_PCI_IACK
mdefine_line|#define MSC01_PCI_IACK&t;&t;(MSC01_PCI_REG_BASE + MSC01_PCI_IACK_OFS)
DECL|macro|MSC01_PCI_HEAD0
mdefine_line|#define MSC01_PCI_HEAD0&t;&t;(MSC01_PCI_REG_BASE + MSC01_PCI_HEAD0_OFS)
DECL|macro|MSC01_PCI_HEAD1
mdefine_line|#define MSC01_PCI_HEAD1&t;&t;(MSC01_PCI_REG_BASE + MSC01_PCI_HEAD1_OFS)
DECL|macro|MSC01_PCI_HEAD2
mdefine_line|#define MSC01_PCI_HEAD2&t;&t;(MSC01_PCI_REG_BASE + MSC01_PCI_HEAD2_OFS)
DECL|macro|MSC01_PCI_HEAD3
mdefine_line|#define MSC01_PCI_HEAD3&t;&t;(MSC01_PCI_REG_BASE + MSC01_PCI_HEAD3_OFS)
DECL|macro|MSC01_PCI_HEAD4
mdefine_line|#define MSC01_PCI_HEAD4&t;&t;(MSC01_PCI_REG_BASE + MSC01_PCI_HEAD4_OFS)
DECL|macro|MSC01_PCI_HEAD5
mdefine_line|#define MSC01_PCI_HEAD5&t;&t;(MSC01_PCI_REG_BASE + MSC01_PCI_HEAD5_OFS)
DECL|macro|MSC01_PCI_HEAD6
mdefine_line|#define MSC01_PCI_HEAD6&t;&t;(MSC01_PCI_REG_BASE + MSC01_PCI_HEAD6_OFS)
DECL|macro|MSC01_PCI_HEAD7
mdefine_line|#define MSC01_PCI_HEAD7&t;&t;(MSC01_PCI_REG_BASE + MSC01_PCI_HEAD7_OFS)
DECL|macro|MSC01_PCI_HEAD8
mdefine_line|#define MSC01_PCI_HEAD8&t;&t;(MSC01_PCI_REG_BASE + MSC01_PCI_HEAD8_OFS)
DECL|macro|MSC01_PCI_HEAD9
mdefine_line|#define MSC01_PCI_HEAD9&t;&t;(MSC01_PCI_REG_BASE + MSC01_PCI_HEAD9_OFS)
DECL|macro|MSC01_PCI_HEAD10
mdefine_line|#define MSC01_PCI_HEAD10&t;(MSC01_PCI_REG_BASE + MSC01_PCI_HEAD10_OFS)
DECL|macro|MSC01_PCI_HEAD11
mdefine_line|#define MSC01_PCI_HEAD11&t;(MSC01_PCI_REG_BASE + MSC01_PCI_HEAD11_OFS)
DECL|macro|MSC01_PCI_HEAD12
mdefine_line|#define MSC01_PCI_HEAD12&t;(MSC01_PCI_REG_BASE + MSC01_PCI_HEAD11_OFS)
DECL|macro|MSC01_PCI_HEAD13
mdefine_line|#define MSC01_PCI_HEAD13&t;(MSC01_PCI_REG_BASE + MSC01_PCI_HEAD11_OFS)
DECL|macro|MSC01_PCI_HEAD14
mdefine_line|#define MSC01_PCI_HEAD14&t;(MSC01_PCI_REG_BASE + MSC01_PCI_HEAD11_OFS)
DECL|macro|MSC01_PCI_HEAD15
mdefine_line|#define MSC01_PCI_HEAD15        (MSC01_PCI_REG_BASE + MSC01_PCI_HEAD11_OFS)
DECL|macro|MSC01_PCI_BAR0
mdefine_line|#define MSC01_PCI_BAR0&t;&t;(MSC01_PCI_REG_BASE + MSC01_PCI_BAR0_OFS)
DECL|macro|MSC01_PCI_CFG
mdefine_line|#define MSC01_PCI_CFG&t;&t;(MSC01_PCI_REG_BASE + MSC01_PCI_CFG_OFS)
DECL|macro|MSC01_PCI_SWAP
mdefine_line|#define MSC01_PCI_SWAP&t;&t;(MSC01_PCI_REG_BASE + MSC01_PCI_SWAP_OFS)
macro_line|#endif
multiline_comment|/*****************************************************************************&n; *  End of msc01_pci.h&n; *****************************************************************************/
eof
