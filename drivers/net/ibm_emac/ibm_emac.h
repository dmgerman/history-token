multiline_comment|/*&n; * ibm_emac.h&n; *&n; *&n; *      Armin Kuster akuster@mvista.com&n; *      June, 2002&n; *&n; * Copyright 2002 MontaVista Softare Inc.&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; */
macro_line|#ifndef _IBM_EMAC_H_
DECL|macro|_IBM_EMAC_H_
mdefine_line|#define _IBM_EMAC_H_
multiline_comment|/* General defines needed for the driver */
multiline_comment|/* Emac */
DECL|struct|emac_regs
r_typedef
r_struct
id|emac_regs
(brace
DECL|member|em0mr0
id|u32
id|em0mr0
suffix:semicolon
DECL|member|em0mr1
id|u32
id|em0mr1
suffix:semicolon
DECL|member|em0tmr0
id|u32
id|em0tmr0
suffix:semicolon
DECL|member|em0tmr1
id|u32
id|em0tmr1
suffix:semicolon
DECL|member|em0rmr
id|u32
id|em0rmr
suffix:semicolon
DECL|member|em0isr
id|u32
id|em0isr
suffix:semicolon
DECL|member|em0iser
id|u32
id|em0iser
suffix:semicolon
DECL|member|em0iahr
id|u32
id|em0iahr
suffix:semicolon
DECL|member|em0ialr
id|u32
id|em0ialr
suffix:semicolon
DECL|member|em0vtpid
id|u32
id|em0vtpid
suffix:semicolon
DECL|member|em0vtci
id|u32
id|em0vtci
suffix:semicolon
DECL|member|em0ptr
id|u32
id|em0ptr
suffix:semicolon
DECL|member|em0iaht1
id|u32
id|em0iaht1
suffix:semicolon
DECL|member|em0iaht2
id|u32
id|em0iaht2
suffix:semicolon
DECL|member|em0iaht3
id|u32
id|em0iaht3
suffix:semicolon
DECL|member|em0iaht4
id|u32
id|em0iaht4
suffix:semicolon
DECL|member|em0gaht1
id|u32
id|em0gaht1
suffix:semicolon
DECL|member|em0gaht2
id|u32
id|em0gaht2
suffix:semicolon
DECL|member|em0gaht3
id|u32
id|em0gaht3
suffix:semicolon
DECL|member|em0gaht4
id|u32
id|em0gaht4
suffix:semicolon
DECL|member|em0lsah
id|u32
id|em0lsah
suffix:semicolon
DECL|member|em0lsal
id|u32
id|em0lsal
suffix:semicolon
DECL|member|em0ipgvr
id|u32
id|em0ipgvr
suffix:semicolon
DECL|member|em0stacr
id|u32
id|em0stacr
suffix:semicolon
DECL|member|em0trtr
id|u32
id|em0trtr
suffix:semicolon
DECL|member|em0rwmr
id|u32
id|em0rwmr
suffix:semicolon
DECL|typedef|emac_t
)brace
id|emac_t
suffix:semicolon
multiline_comment|/* MODE REG 0 */
DECL|macro|EMAC_M0_RXI
mdefine_line|#define EMAC_M0_RXI&t;&t;&t;0x80000000
DECL|macro|EMAC_M0_TXI
mdefine_line|#define EMAC_M0_TXI&t;&t;&t;0x40000000
DECL|macro|EMAC_M0_SRST
mdefine_line|#define EMAC_M0_SRST&t;&t;&t;0x20000000
DECL|macro|EMAC_M0_TXE
mdefine_line|#define EMAC_M0_TXE&t;&t;&t;0x10000000
DECL|macro|EMAC_M0_RXE
mdefine_line|#define EMAC_M0_RXE&t;&t;&t;0x08000000
DECL|macro|EMAC_M0_WKE
mdefine_line|#define EMAC_M0_WKE&t;&t;&t;0x04000000
multiline_comment|/* MODE Reg 1 */
DECL|macro|EMAC_M1_FDE
mdefine_line|#define EMAC_M1_FDE&t;&t;&t;0x80000000
DECL|macro|EMAC_M1_ILE
mdefine_line|#define EMAC_M1_ILE&t;&t;&t;0x40000000
DECL|macro|EMAC_M1_VLE
mdefine_line|#define EMAC_M1_VLE&t;&t;&t;0x20000000
DECL|macro|EMAC_M1_EIFC
mdefine_line|#define EMAC_M1_EIFC&t;&t;&t;0x10000000
DECL|macro|EMAC_M1_APP
mdefine_line|#define EMAC_M1_APP&t;&t;&t;0x08000000
DECL|macro|EMAC_M1_AEMI
mdefine_line|#define EMAC_M1_AEMI&t;&t;&t;0x02000000
DECL|macro|EMAC_M1_IST
mdefine_line|#define EMAC_M1_IST&t;&t;&t;0x01000000
DECL|macro|EMAC_M1_MF_1000GPCS
mdefine_line|#define EMAC_M1_MF_1000GPCS&t;&t;0x00c00000&t;/* Internal GPCS */
DECL|macro|EMAC_M1_MF_1000MBPS
mdefine_line|#define EMAC_M1_MF_1000MBPS&t;&t;0x00800000&t;/* External GPCS */
DECL|macro|EMAC_M1_MF_100MBPS
mdefine_line|#define EMAC_M1_MF_100MBPS&t;&t;0x00400000
DECL|macro|EMAC_M1_RFS_16K
mdefine_line|#define EMAC_M1_RFS_16K                 0x00280000&t;/* 000 for 512 byte */
DECL|macro|EMAC_M1_TR
mdefine_line|#define EMAC_M1_TR&t;&t;&t;0x00008000
macro_line|#ifdef CONFIG_IBM_EMAC4
DECL|macro|EMAC_M1_RFS_8K
mdefine_line|#define EMAC_M1_RFS_8K                  0x00200000
DECL|macro|EMAC_M1_RFS_4K
mdefine_line|#define EMAC_M1_RFS_4K                  0x00180000
DECL|macro|EMAC_M1_RFS_2K
mdefine_line|#define EMAC_M1_RFS_2K                  0x00100000
DECL|macro|EMAC_M1_RFS_1K
mdefine_line|#define EMAC_M1_RFS_1K                  0x00080000
DECL|macro|EMAC_M1_TX_FIFO_16K
mdefine_line|#define EMAC_M1_TX_FIFO_16K             0x00050000&t;/* 0&squot;s for 512 byte */
DECL|macro|EMAC_M1_TX_FIFO_8K
mdefine_line|#define EMAC_M1_TX_FIFO_8K              0x00040000
DECL|macro|EMAC_M1_TX_FIFO_4K
mdefine_line|#define EMAC_M1_TX_FIFO_4K              0x00030000
DECL|macro|EMAC_M1_TX_FIFO_2K
mdefine_line|#define EMAC_M1_TX_FIFO_2K              0x00020000
DECL|macro|EMAC_M1_TX_FIFO_1K
mdefine_line|#define EMAC_M1_TX_FIFO_1K              0x00010000
DECL|macro|EMAC_M1_TX_TR
mdefine_line|#define EMAC_M1_TX_TR                   0x00008000
DECL|macro|EMAC_M1_TX_MWSW
mdefine_line|#define EMAC_M1_TX_MWSW                 0x00001000&t;/* 0 wait for status */
DECL|macro|EMAC_M1_JUMBO_ENABLE
mdefine_line|#define EMAC_M1_JUMBO_ENABLE            0x00000800&t;/* Upt to 9Kr status */
DECL|macro|EMAC_M1_OPB_CLK_66
mdefine_line|#define EMAC_M1_OPB_CLK_66              0x00000008&t;/* 66Mhz */
DECL|macro|EMAC_M1_OPB_CLK_83
mdefine_line|#define EMAC_M1_OPB_CLK_83              0x00000010&t;/* 83Mhz */
DECL|macro|EMAC_M1_OPB_CLK_100
mdefine_line|#define EMAC_M1_OPB_CLK_100             0x00000018&t;/* 100Mhz */
DECL|macro|EMAC_M1_OPB_CLK_100P
mdefine_line|#define EMAC_M1_OPB_CLK_100P            0x00000020&t;/* 100Mhz+ */
macro_line|#else&t;&t;&t;&t;/* CONFIG_IBM_EMAC4 */
DECL|macro|EMAC_M1_RFS_4K
mdefine_line|#define EMAC_M1_RFS_4K&t;&t;&t;0x00300000&t;/* ~4k for 512 byte */
DECL|macro|EMAC_M1_RFS_2K
mdefine_line|#define EMAC_M1_RFS_2K&t;&t;&t;0x00200000
DECL|macro|EMAC_M1_RFS_1K
mdefine_line|#define EMAC_M1_RFS_1K&t;&t;&t;0x00100000
DECL|macro|EMAC_M1_TX_FIFO_2K
mdefine_line|#define EMAC_M1_TX_FIFO_2K&t;&t;0x00080000&t;/* 0&squot;s for 512 byte */
DECL|macro|EMAC_M1_TX_FIFO_1K
mdefine_line|#define EMAC_M1_TX_FIFO_1K&t;&t;0x00040000
DECL|macro|EMAC_M1_TR0_DEPEND
mdefine_line|#define EMAC_M1_TR0_DEPEND&t;&t;0x00010000&t;/* 0&squot;x for single packet */
DECL|macro|EMAC_M1_TR1_DEPEND
mdefine_line|#define EMAC_M1_TR1_DEPEND&t;&t;0x00004000
DECL|macro|EMAC_M1_TR1_MULTI
mdefine_line|#define EMAC_M1_TR1_MULTI&t;&t;0x00002000
DECL|macro|EMAC_M1_JUMBO_ENABLE
mdefine_line|#define EMAC_M1_JUMBO_ENABLE&t;&t;0x00001000
macro_line|#endif&t;&t;&t;&t;/* CONFIG_IBM_EMAC4 */
DECL|macro|EMAC_M1_BASE
mdefine_line|#define EMAC_M1_BASE&t;&t;&t;(EMAC_M1_TX_FIFO_2K | &bslash;&n;&t;&t;&t;&t;&t;EMAC_M1_APP | &bslash;&n;&t;&t;&t;&t;&t;EMAC_M1_TR | EMAC_M1_VLE)
multiline_comment|/* Transmit Mode Register 0 */
DECL|macro|EMAC_TMR0_GNP0
mdefine_line|#define EMAC_TMR0_GNP0&t;&t;&t;0x80000000
DECL|macro|EMAC_TMR0_GNP1
mdefine_line|#define EMAC_TMR0_GNP1&t;&t;&t;0x40000000
DECL|macro|EMAC_TMR0_GNPD
mdefine_line|#define EMAC_TMR0_GNPD&t;&t;&t;0x20000000
DECL|macro|EMAC_TMR0_FC
mdefine_line|#define EMAC_TMR0_FC&t;&t;&t;0x10000000
DECL|macro|EMAC_TMR0_TFAE_2_32
mdefine_line|#define EMAC_TMR0_TFAE_2_32&t;&t;0x00000001
DECL|macro|EMAC_TMR0_TFAE_4_64
mdefine_line|#define EMAC_TMR0_TFAE_4_64&t;&t;0x00000002
DECL|macro|EMAC_TMR0_TFAE_8_128
mdefine_line|#define EMAC_TMR0_TFAE_8_128&t;&t;0x00000003
DECL|macro|EMAC_TMR0_TFAE_16_256
mdefine_line|#define EMAC_TMR0_TFAE_16_256&t;&t;0x00000004
DECL|macro|EMAC_TMR0_TFAE_32_512
mdefine_line|#define EMAC_TMR0_TFAE_32_512&t;&t;0x00000005
DECL|macro|EMAC_TMR0_TFAE_64_1024
mdefine_line|#define EMAC_TMR0_TFAE_64_1024&t;&t;0x00000006
DECL|macro|EMAC_TMR0_TFAE_128_2048
mdefine_line|#define EMAC_TMR0_TFAE_128_2048&t;&t;0x00000007
multiline_comment|/* Receive Mode Register */
DECL|macro|EMAC_RMR_SP
mdefine_line|#define EMAC_RMR_SP&t;&t;&t;0x80000000
DECL|macro|EMAC_RMR_SFCS
mdefine_line|#define EMAC_RMR_SFCS&t;&t;&t;0x40000000
DECL|macro|EMAC_RMR_ARRP
mdefine_line|#define EMAC_RMR_ARRP&t;&t;&t;0x20000000
DECL|macro|EMAC_RMR_ARP
mdefine_line|#define EMAC_RMR_ARP&t;&t;&t;0x10000000
DECL|macro|EMAC_RMR_AROP
mdefine_line|#define EMAC_RMR_AROP&t;&t;&t;0x08000000
DECL|macro|EMAC_RMR_ARPI
mdefine_line|#define EMAC_RMR_ARPI&t;&t;&t;0x04000000
DECL|macro|EMAC_RMR_PPP
mdefine_line|#define EMAC_RMR_PPP&t;&t;&t;0x02000000
DECL|macro|EMAC_RMR_PME
mdefine_line|#define EMAC_RMR_PME&t;&t;&t;0x01000000
DECL|macro|EMAC_RMR_PMME
mdefine_line|#define EMAC_RMR_PMME&t;&t;&t;0x00800000
DECL|macro|EMAC_RMR_IAE
mdefine_line|#define EMAC_RMR_IAE&t;&t;&t;0x00400000
DECL|macro|EMAC_RMR_MIAE
mdefine_line|#define EMAC_RMR_MIAE&t;&t;&t;0x00200000
DECL|macro|EMAC_RMR_BAE
mdefine_line|#define EMAC_RMR_BAE&t;&t;&t;0x00100000
DECL|macro|EMAC_RMR_MAE
mdefine_line|#define EMAC_RMR_MAE&t;&t;&t;0x00080000
DECL|macro|EMAC_RMR_RFAF_2_32
mdefine_line|#define EMAC_RMR_RFAF_2_32&t;&t;0x00000001
DECL|macro|EMAC_RMR_RFAF_4_64
mdefine_line|#define EMAC_RMR_RFAF_4_64&t;&t;0x00000002
DECL|macro|EMAC_RMR_RFAF_8_128
mdefine_line|#define EMAC_RMR_RFAF_8_128&t;&t;0x00000003
DECL|macro|EMAC_RMR_RFAF_16_256
mdefine_line|#define EMAC_RMR_RFAF_16_256&t;&t;0x00000004
DECL|macro|EMAC_RMR_RFAF_32_512
mdefine_line|#define EMAC_RMR_RFAF_32_512&t;&t;0x00000005
DECL|macro|EMAC_RMR_RFAF_64_1024
mdefine_line|#define EMAC_RMR_RFAF_64_1024&t;&t;0x00000006
DECL|macro|EMAC_RMR_RFAF_128_2048
mdefine_line|#define EMAC_RMR_RFAF_128_2048&t;&t;0x00000007
DECL|macro|EMAC_RMR_BASE
mdefine_line|#define EMAC_RMR_BASE&t;&t;&t;(EMAC_RMR_IAE | EMAC_RMR_BAE)
multiline_comment|/* Interrupt Status &amp; enable Regs */
DECL|macro|EMAC_ISR_OVR
mdefine_line|#define EMAC_ISR_OVR&t;&t;&t;0x02000000
DECL|macro|EMAC_ISR_PP
mdefine_line|#define EMAC_ISR_PP&t;&t;&t;0x01000000
DECL|macro|EMAC_ISR_BP
mdefine_line|#define EMAC_ISR_BP&t;&t;&t;0x00800000
DECL|macro|EMAC_ISR_RP
mdefine_line|#define EMAC_ISR_RP&t;&t;&t;0x00400000
DECL|macro|EMAC_ISR_SE
mdefine_line|#define EMAC_ISR_SE&t;&t;&t;0x00200000
DECL|macro|EMAC_ISR_ALE
mdefine_line|#define EMAC_ISR_ALE&t;&t;&t;0x00100000
DECL|macro|EMAC_ISR_BFCS
mdefine_line|#define EMAC_ISR_BFCS&t;&t;&t;0x00080000
DECL|macro|EMAC_ISR_PTLE
mdefine_line|#define EMAC_ISR_PTLE&t;&t;&t;0x00040000
DECL|macro|EMAC_ISR_ORE
mdefine_line|#define EMAC_ISR_ORE&t;&t;&t;0x00020000
DECL|macro|EMAC_ISR_IRE
mdefine_line|#define EMAC_ISR_IRE&t;&t;&t;0x00010000
DECL|macro|EMAC_ISR_DBDM
mdefine_line|#define EMAC_ISR_DBDM&t;&t;&t;0x00000200
DECL|macro|EMAC_ISR_DB0
mdefine_line|#define EMAC_ISR_DB0&t;&t;&t;0x00000100
DECL|macro|EMAC_ISR_SE0
mdefine_line|#define EMAC_ISR_SE0&t;&t;&t;0x00000080
DECL|macro|EMAC_ISR_TE0
mdefine_line|#define EMAC_ISR_TE0&t;&t;&t;0x00000040
DECL|macro|EMAC_ISR_DB1
mdefine_line|#define EMAC_ISR_DB1&t;&t;&t;0x00000020
DECL|macro|EMAC_ISR_SE1
mdefine_line|#define EMAC_ISR_SE1&t;&t;&t;0x00000010
DECL|macro|EMAC_ISR_TE1
mdefine_line|#define EMAC_ISR_TE1&t;&t;&t;0x00000008
DECL|macro|EMAC_ISR_MOS
mdefine_line|#define EMAC_ISR_MOS&t;&t;&t;0x00000002
DECL|macro|EMAC_ISR_MOF
mdefine_line|#define EMAC_ISR_MOF&t;&t;&t;0x00000001
multiline_comment|/* STA CONTROL REG */
DECL|macro|EMAC_STACR_OC
mdefine_line|#define EMAC_STACR_OC&t;&t;&t;0x00008000
DECL|macro|EMAC_STACR_PHYE
mdefine_line|#define EMAC_STACR_PHYE&t;&t;&t;0x00004000
DECL|macro|EMAC_STACR_WRITE
mdefine_line|#define EMAC_STACR_WRITE&t;&t;0x00002000
DECL|macro|EMAC_STACR_READ
mdefine_line|#define EMAC_STACR_READ&t;&t;&t;0x00001000
DECL|macro|EMAC_STACR_CLK_83MHZ
mdefine_line|#define EMAC_STACR_CLK_83MHZ&t;&t;0x00000800&t;/* 0&squot;s for 50Mhz */
DECL|macro|EMAC_STACR_CLK_66MHZ
mdefine_line|#define EMAC_STACR_CLK_66MHZ&t;&t;0x00000400
DECL|macro|EMAC_STACR_CLK_100MHZ
mdefine_line|#define EMAC_STACR_CLK_100MHZ&t;&t;0x00000C00
multiline_comment|/* Transmit Request Threshold Register */
DECL|macro|EMAC_TRTR_1600
mdefine_line|#define EMAC_TRTR_1600&t;&t;&t;0x18000000&t;/* 0&squot;s for 64 Bytes */
DECL|macro|EMAC_TRTR_1024
mdefine_line|#define EMAC_TRTR_1024&t;&t;&t;0x0f000000
DECL|macro|EMAC_TRTR_512
mdefine_line|#define EMAC_TRTR_512&t;&t;&t;0x07000000
DECL|macro|EMAC_TRTR_256
mdefine_line|#define EMAC_TRTR_256&t;&t;&t;0x03000000
DECL|macro|EMAC_TRTR_192
mdefine_line|#define EMAC_TRTR_192&t;&t;&t;0x10000000
DECL|macro|EMAC_TRTR_128
mdefine_line|#define EMAC_TRTR_128&t;&t;&t;0x01000000
DECL|macro|EMAC_TX_CTRL_GFCS
mdefine_line|#define EMAC_TX_CTRL_GFCS&t;&t;0x0200
DECL|macro|EMAC_TX_CTRL_GP
mdefine_line|#define EMAC_TX_CTRL_GP&t;&t;&t;0x0100
DECL|macro|EMAC_TX_CTRL_ISA
mdefine_line|#define EMAC_TX_CTRL_ISA&t;&t;0x0080
DECL|macro|EMAC_TX_CTRL_RSA
mdefine_line|#define EMAC_TX_CTRL_RSA&t;&t;0x0040
DECL|macro|EMAC_TX_CTRL_IVT
mdefine_line|#define EMAC_TX_CTRL_IVT&t;&t;0x0020
DECL|macro|EMAC_TX_CTRL_RVT
mdefine_line|#define EMAC_TX_CTRL_RVT&t;&t;0x0010
DECL|macro|EMAC_TX_CTRL_TAH_CSUM
mdefine_line|#define EMAC_TX_CTRL_TAH_CSUM&t;&t;0x000e&t;/* TAH only */
DECL|macro|EMAC_TX_CTRL_TAH_SEG4
mdefine_line|#define EMAC_TX_CTRL_TAH_SEG4&t;&t;0x000a&t;/* TAH only */
DECL|macro|EMAC_TX_CTRL_TAH_SEG3
mdefine_line|#define EMAC_TX_CTRL_TAH_SEG3&t;&t;0x0008&t;/* TAH only */
DECL|macro|EMAC_TX_CTRL_TAH_SEG2
mdefine_line|#define EMAC_TX_CTRL_TAH_SEG2&t;&t;0x0006&t;/* TAH only */
DECL|macro|EMAC_TX_CTRL_TAH_SEG1
mdefine_line|#define EMAC_TX_CTRL_TAH_SEG1&t;&t;0x0004&t;/* TAH only */
DECL|macro|EMAC_TX_CTRL_TAH_SEG0
mdefine_line|#define EMAC_TX_CTRL_TAH_SEG0&t;&t;0x0002&t;/* TAH only */
DECL|macro|EMAC_TX_CTRL_TAH_DIS
mdefine_line|#define EMAC_TX_CTRL_TAH_DIS&t;&t;0x0000&t;/* TAH only */
DECL|macro|EMAC_TX_CTRL_DFLT
mdefine_line|#define EMAC_TX_CTRL_DFLT ( &bslash;&n;&t;MAL_TX_CTRL_INTR | EMAC_TX_CTRL_GFCS | EMAC_TX_CTRL_GP )
multiline_comment|/* madmal transmit status / Control bits */
DECL|macro|EMAC_TX_ST_BFCS
mdefine_line|#define EMAC_TX_ST_BFCS&t;&t;&t;0x0200
DECL|macro|EMAC_TX_ST_BPP
mdefine_line|#define EMAC_TX_ST_BPP&t;&t;&t;0x0100
DECL|macro|EMAC_TX_ST_LCS
mdefine_line|#define EMAC_TX_ST_LCS&t;&t;&t;0x0080
DECL|macro|EMAC_TX_ST_ED
mdefine_line|#define EMAC_TX_ST_ED&t;&t;&t;0x0040
DECL|macro|EMAC_TX_ST_EC
mdefine_line|#define EMAC_TX_ST_EC&t;&t;&t;0x0020
DECL|macro|EMAC_TX_ST_LC
mdefine_line|#define EMAC_TX_ST_LC&t;&t;&t;0x0010
DECL|macro|EMAC_TX_ST_MC
mdefine_line|#define EMAC_TX_ST_MC&t;&t;&t;0x0008
DECL|macro|EMAC_TX_ST_SC
mdefine_line|#define EMAC_TX_ST_SC&t;&t;&t;0x0004
DECL|macro|EMAC_TX_ST_UR
mdefine_line|#define EMAC_TX_ST_UR&t;&t;&t;0x0002
DECL|macro|EMAC_TX_ST_SQE
mdefine_line|#define EMAC_TX_ST_SQE&t;&t;&t;0x0001
multiline_comment|/* madmal receive status / Control bits */
DECL|macro|EMAC_RX_ST_OE
mdefine_line|#define EMAC_RX_ST_OE&t;&t;&t;0x0200
DECL|macro|EMAC_RX_ST_PP
mdefine_line|#define EMAC_RX_ST_PP&t;&t;&t;0x0100
DECL|macro|EMAC_RX_ST_BP
mdefine_line|#define EMAC_RX_ST_BP&t;&t;&t;0x0080
DECL|macro|EMAC_RX_ST_RP
mdefine_line|#define EMAC_RX_ST_RP&t;&t;&t;0x0040
DECL|macro|EMAC_RX_ST_SE
mdefine_line|#define EMAC_RX_ST_SE&t;&t;&t;0x0020
DECL|macro|EMAC_RX_ST_AE
mdefine_line|#define EMAC_RX_ST_AE&t;&t;&t;0x0010
DECL|macro|EMAC_RX_ST_BFCS
mdefine_line|#define EMAC_RX_ST_BFCS&t;&t;&t;0x0008
DECL|macro|EMAC_RX_ST_PTL
mdefine_line|#define EMAC_RX_ST_PTL&t;&t;&t;0x0004
DECL|macro|EMAC_RX_ST_ORE
mdefine_line|#define EMAC_RX_ST_ORE&t;&t;&t;0x0002
DECL|macro|EMAC_RX_ST_IRE
mdefine_line|#define EMAC_RX_ST_IRE&t;&t;&t;0x0001
DECL|macro|EMAC_BAD_RX_PACKET
mdefine_line|#define EMAC_BAD_RX_PACKET&t;&t;0x02ff
DECL|macro|EMAC_CSUM_VER_ERROR
mdefine_line|#define EMAC_CSUM_VER_ERROR&t;&t;0x0003
multiline_comment|/* identify a bad rx packet dependent on emac features */
macro_line|#ifdef CONFIG_IBM_EMAC4
DECL|macro|EMAC_IS_BAD_RX_PACKET
mdefine_line|#define EMAC_IS_BAD_RX_PACKET(desc) &bslash;&n;&t;(((desc &amp; (EMAC_BAD_RX_PACKET &amp; ~EMAC_CSUM_VER_ERROR)) || &bslash;&n;&t;((desc &amp; EMAC_CSUM_VER_ERROR) == EMAC_RX_ST_ORE) || &bslash;&n;&t;((desc &amp; EMAC_CSUM_VER_ERROR) == EMAC_RX_ST_IRE)))
macro_line|#else
DECL|macro|EMAC_IS_BAD_RX_PACKET
mdefine_line|#define EMAC_IS_BAD_RX_PACKET(desc) &bslash;&n;&t; (desc &amp; EMAC_BAD_RX_PACKET)
macro_line|#endif
multiline_comment|/* SoC implementation specific EMAC register defaults */
macro_line|#if defined(CONFIG_440GP)
DECL|macro|EMAC_RWMR_DEFAULT
mdefine_line|#define EMAC_RWMR_DEFAULT&t;&t;0x80009000
DECL|macro|EMAC_TMR0_DEFAULT
mdefine_line|#define EMAC_TMR0_DEFAULT&t;&t;0x00000000
DECL|macro|EMAC_TMR1_DEFAULT
mdefine_line|#define EMAC_TMR1_DEFAULT&t;&t;0xf8640000
macro_line|#elif defined(CONFIG_440GX)
DECL|macro|EMAC_RWMR_DEFAULT
mdefine_line|#define EMAC_RWMR_DEFAULT&t;&t;0x1000a200
DECL|macro|EMAC_TMR0_DEFAULT
mdefine_line|#define EMAC_TMR0_DEFAULT&t;&t;EMAC_TMR0_TFAE_2_32
DECL|macro|EMAC_TMR1_DEFAULT
mdefine_line|#define EMAC_TMR1_DEFAULT&t;&t;0xa00f0000
macro_line|#else
DECL|macro|EMAC_RWMR_DEFAULT
mdefine_line|#define EMAC_RWMR_DEFAULT&t;&t;0x0f002000
DECL|macro|EMAC_TMR0_DEFAULT
mdefine_line|#define EMAC_TMR0_DEFAULT&t;&t;0x00000000
DECL|macro|EMAC_TMR1_DEFAULT
mdefine_line|#define EMAC_TMR1_DEFAULT&t;&t;0x380f0000
macro_line|#endif&t;&t;&t;&t;/* CONFIG_440GP */
multiline_comment|/* Revision specific EMAC register defaults */
macro_line|#ifdef CONFIG_IBM_EMAC4
DECL|macro|EMAC_M1_DEFAULT
mdefine_line|#define EMAC_M1_DEFAULT&t;&t;&t;(EMAC_M1_BASE | &bslash;&n;&t;&t;&t;&t;&t;EMAC_M1_OPB_CLK_83 | &bslash;&n;&t;&t;&t;&t;&t;EMAC_M1_TX_MWSW)
DECL|macro|EMAC_RMR_DEFAULT
mdefine_line|#define EMAC_RMR_DEFAULT&t;&t;(EMAC_RMR_BASE | &bslash;&n;&t;&t;&t;&t;&t;EMAC_RMR_RFAF_128_2048)
DECL|macro|EMAC_TMR0_XMIT
mdefine_line|#define EMAC_TMR0_XMIT&t;&t;&t;(EMAC_TMR0_GNP0 | &bslash;&n;&t;&t;&t;&t;&t;EMAC_TMR0_DEFAULT)
DECL|macro|EMAC_TRTR_DEFAULT
mdefine_line|#define EMAC_TRTR_DEFAULT&t;&t;EMAC_TRTR_1024
macro_line|#else&t;&t;&t;&t;/* !CONFIG_IBM_EMAC4 */
DECL|macro|EMAC_M1_DEFAULT
mdefine_line|#define EMAC_M1_DEFAULT&t;&t;&t;EMAC_M1_BASE
DECL|macro|EMAC_RMR_DEFAULT
mdefine_line|#define EMAC_RMR_DEFAULT&t;&t;EMAC_RMR_BASE
DECL|macro|EMAC_TMR0_XMIT
mdefine_line|#define EMAC_TMR0_XMIT&t;&t;&t;EMAC_TMR0_GNP0
DECL|macro|EMAC_TRTR_DEFAULT
mdefine_line|#define EMAC_TRTR_DEFAULT&t;&t;EMAC_TRTR_1600
macro_line|#endif&t;&t;&t;&t;/* CONFIG_IBM_EMAC4 */
macro_line|#endif
eof
