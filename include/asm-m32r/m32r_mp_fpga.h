macro_line|#ifndef _ASM_M32R_M32R_MP_FPGA_
DECL|macro|_ASM_M32R_M32R_MP_FPGA_
mdefine_line|#define _ASM_M32R_M32R_MP_FPGA_
multiline_comment|/*&n; * Renesas M32R-MP-FPGA&n; *&n; * Copyright (c) 2002  Hitoshi Yamamoto&n; * Copyright (c) 2003, 2004  Renesas Technology Corp.&n; */
multiline_comment|/*&n; * ========================================================&n; * M32R-MP-FPGA Memory Map&n; * ========================================================&n; * 0x00000000 : Block#0 : 64[MB]&n; *              0x03E00000 : SFR&n; *                           0x03E00000 : reserved&n; *                           0x03EF0000 : FPGA&n; *                           0x03EF1000 : reserved&n; *                           0x03EF4000 : CKM&n; *                           0x03EF4000 : BSELC&n; *                           0x03EF5000 : reserved&n; *                           0x03EFC000 : MFT&n; *                           0x03EFD000 : SIO&n; *                           0x03EFE000 : reserved&n; *                           0x03EFF000 : ICU&n; *              0x03F00000 : Internal SRAM 64[KB]&n; *              0x03F10000 : reserved&n; * --------------------------------------------------------&n; * 0x04000000 : Block#1 : 64[MB]&n; *              0x04000000 : Debug board SRAM 4[MB]&n; *              0x04400000 : reserved&n; * --------------------------------------------------------&n; * 0x08000000 : Block#2 : 64[MB]&n; * --------------------------------------------------------&n; * 0x0C000000 : Block#3 : 64[MB]&n; * --------------------------------------------------------&n; * 0x10000000 : Block#4 : 64[MB]&n; * --------------------------------------------------------&n; * 0x14000000 : Block#5 : 64[MB]&n; * --------------------------------------------------------&n; * 0x18000000 : Block#6 : 64[MB]&n; * --------------------------------------------------------&n; * 0x1C000000 : Block#7 : 64[MB]&n; * --------------------------------------------------------&n; * 0xFE000000 : TLB&n; *              0xFE000000 : ITLB&n; *              0xFE000080 : reserved&n; *              0xFE000800 : DTLB&n; *              0xFE000880 : reserved&n; * --------------------------------------------------------&n; * 0xFF000000 : System area&n; *              0xFFFF0000 : MMU&n; *              0xFFFF0030 : reserved&n; *              0xFFFF8000 : Debug function&n; *              0xFFFFA000 : reserved&n; *              0xFFFFC000 : CPU control&n; * 0xFFFFFFFF&n; * ========================================================&n; */
multiline_comment|/*======================================================================*&n; * Special Function Register&n; *======================================================================*/
DECL|macro|M32R_SFR_OFFSET
mdefine_line|#define M32R_SFR_OFFSET  (0x00E00000)  /* 0x03E00000-0x03EFFFFF 1[MB] */
multiline_comment|/*&n; * FPGA registers.&n; */
DECL|macro|M32R_FPGA_TOP
mdefine_line|#define M32R_FPGA_TOP  (0x000F0000+M32R_SFR_OFFSET)
DECL|macro|M32R_FPGA_NUM_OF_CPUS_PORTL
mdefine_line|#define M32R_FPGA_NUM_OF_CPUS_PORTL  (0x00+M32R_FPGA_TOP)
DECL|macro|M32R_FPGA_CPU_NAME0_PORTL
mdefine_line|#define M32R_FPGA_CPU_NAME0_PORTL    (0x10+M32R_FPGA_TOP)
DECL|macro|M32R_FPGA_CPU_NAME1_PORTL
mdefine_line|#define M32R_FPGA_CPU_NAME1_PORTL    (0x14+M32R_FPGA_TOP)
DECL|macro|M32R_FPGA_CPU_NAME2_PORTL
mdefine_line|#define M32R_FPGA_CPU_NAME2_PORTL    (0x18+M32R_FPGA_TOP)
DECL|macro|M32R_FPGA_CPU_NAME3_PORTL
mdefine_line|#define M32R_FPGA_CPU_NAME3_PORTL    (0x1C+M32R_FPGA_TOP)
DECL|macro|M32R_FPGA_MODEL_ID0_PORTL
mdefine_line|#define M32R_FPGA_MODEL_ID0_PORTL    (0x20+M32R_FPGA_TOP)
DECL|macro|M32R_FPGA_MODEL_ID1_PORTL
mdefine_line|#define M32R_FPGA_MODEL_ID1_PORTL    (0x24+M32R_FPGA_TOP)
DECL|macro|M32R_FPGA_MODEL_ID2_PORTL
mdefine_line|#define M32R_FPGA_MODEL_ID2_PORTL    (0x28+M32R_FPGA_TOP)
DECL|macro|M32R_FPGA_MODEL_ID3_PORTL
mdefine_line|#define M32R_FPGA_MODEL_ID3_PORTL    (0x2C+M32R_FPGA_TOP)
DECL|macro|M32R_FPGA_VERSION0_PORTL
mdefine_line|#define M32R_FPGA_VERSION0_PORTL     (0x30+M32R_FPGA_TOP)
DECL|macro|M32R_FPGA_VERSION1_PORTL
mdefine_line|#define M32R_FPGA_VERSION1_PORTL     (0x34+M32R_FPGA_TOP)
multiline_comment|/*&n; * Clock and Power Manager registers.&n; */
DECL|macro|M32R_CPM_OFFSET
mdefine_line|#define M32R_CPM_OFFSET  (0x000F4000+M32R_SFR_OFFSET)
DECL|macro|M32R_CPM_CPUCLKCR_PORTL
mdefine_line|#define M32R_CPM_CPUCLKCR_PORTL  (0x00+M32R_CPM_OFFSET)
DECL|macro|M32R_CPM_CLKMOD_PORTL
mdefine_line|#define M32R_CPM_CLKMOD_PORTL    (0x04+M32R_CPM_OFFSET)
DECL|macro|M32R_CPM_PLLCR_PORTL
mdefine_line|#define M32R_CPM_PLLCR_PORTL     (0x08+M32R_CPM_OFFSET)
multiline_comment|/*&n; * Block SELect Controller registers.&n; */
DECL|macro|M32R_BSELC_OFFSET
mdefine_line|#define M32R_BSELC_OFFSET  (0x000F5000+M32R_SFR_OFFSET)
DECL|macro|M32R_BSEL0_CR0_PORTL
mdefine_line|#define M32R_BSEL0_CR0_PORTL  (0x000+M32R_BSELC_OFFSET)
DECL|macro|M32R_BSEL0_CR1_PORTL
mdefine_line|#define M32R_BSEL0_CR1_PORTL  (0x004+M32R_BSELC_OFFSET)
DECL|macro|M32R_BSEL1_CR0_PORTL
mdefine_line|#define M32R_BSEL1_CR0_PORTL  (0x100+M32R_BSELC_OFFSET)
DECL|macro|M32R_BSEL1_CR1_PORTL
mdefine_line|#define M32R_BSEL1_CR1_PORTL  (0x104+M32R_BSELC_OFFSET)
DECL|macro|M32R_BSEL2_CR0_PORTL
mdefine_line|#define M32R_BSEL2_CR0_PORTL  (0x200+M32R_BSELC_OFFSET)
DECL|macro|M32R_BSEL2_CR1_PORTL
mdefine_line|#define M32R_BSEL2_CR1_PORTL  (0x204+M32R_BSELC_OFFSET)
DECL|macro|M32R_BSEL3_CR0_PORTL
mdefine_line|#define M32R_BSEL3_CR0_PORTL  (0x300+M32R_BSELC_OFFSET)
DECL|macro|M32R_BSEL3_CR1_PORTL
mdefine_line|#define M32R_BSEL3_CR1_PORTL  (0x304+M32R_BSELC_OFFSET)
DECL|macro|M32R_BSEL4_CR0_PORTL
mdefine_line|#define M32R_BSEL4_CR0_PORTL  (0x400+M32R_BSELC_OFFSET)
DECL|macro|M32R_BSEL4_CR1_PORTL
mdefine_line|#define M32R_BSEL4_CR1_PORTL  (0x404+M32R_BSELC_OFFSET)
DECL|macro|M32R_BSEL5_CR0_PORTL
mdefine_line|#define M32R_BSEL5_CR0_PORTL  (0x500+M32R_BSELC_OFFSET)
DECL|macro|M32R_BSEL5_CR1_PORTL
mdefine_line|#define M32R_BSEL5_CR1_PORTL  (0x504+M32R_BSELC_OFFSET)
DECL|macro|M32R_BSEL6_CR0_PORTL
mdefine_line|#define M32R_BSEL6_CR0_PORTL  (0x600+M32R_BSELC_OFFSET)
DECL|macro|M32R_BSEL6_CR1_PORTL
mdefine_line|#define M32R_BSEL6_CR1_PORTL  (0x604+M32R_BSELC_OFFSET)
DECL|macro|M32R_BSEL7_CR0_PORTL
mdefine_line|#define M32R_BSEL7_CR0_PORTL  (0x700+M32R_BSELC_OFFSET)
DECL|macro|M32R_BSEL7_CR1_PORTL
mdefine_line|#define M32R_BSEL7_CR1_PORTL  (0x704+M32R_BSELC_OFFSET)
multiline_comment|/*&n; * Multi Function Timer registers.&n; */
DECL|macro|M32R_MFT_OFFSET
mdefine_line|#define M32R_MFT_OFFSET        (0x000FC000+M32R_SFR_OFFSET)
DECL|macro|M32R_MFTCR_PORTL
mdefine_line|#define M32R_MFTCR_PORTL       (0x000+M32R_MFT_OFFSET)  /* MFT control */
DECL|macro|M32R_MFTRPR_PORTL
mdefine_line|#define M32R_MFTRPR_PORTL      (0x004+M32R_MFT_OFFSET)  /* MFT real port */
DECL|macro|M32R_MFT0_OFFSET
mdefine_line|#define M32R_MFT0_OFFSET       (0x100+M32R_MFT_OFFSET)
DECL|macro|M32R_MFT0MOD_PORTL
mdefine_line|#define M32R_MFT0MOD_PORTL     (0x00+M32R_MFT0_OFFSET)  /* MFT0 mode */
DECL|macro|M32R_MFT0BOS_PORTL
mdefine_line|#define M32R_MFT0BOS_PORTL     (0x04+M32R_MFT0_OFFSET)  /* MFT0 b-port output status */
DECL|macro|M32R_MFT0CUT_PORTL
mdefine_line|#define M32R_MFT0CUT_PORTL     (0x08+M32R_MFT0_OFFSET)  /* MFT0 count */
DECL|macro|M32R_MFT0RLD_PORTL
mdefine_line|#define M32R_MFT0RLD_PORTL     (0x0C+M32R_MFT0_OFFSET)  /* MFT0 reload */
DECL|macro|M32R_MFT0CMPRLD_PORTL
mdefine_line|#define M32R_MFT0CMPRLD_PORTL  (0x10+M32R_MFT0_OFFSET)  /* MFT0 compare reload */
DECL|macro|M32R_MFT1_OFFSET
mdefine_line|#define M32R_MFT1_OFFSET       (0x200+M32R_MFT_OFFSET)
DECL|macro|M32R_MFT1MOD_PORTL
mdefine_line|#define M32R_MFT1MOD_PORTL     (0x00+M32R_MFT1_OFFSET)  /* MFT1 mode */
DECL|macro|M32R_MFT1BOS_PORTL
mdefine_line|#define M32R_MFT1BOS_PORTL     (0x04+M32R_MFT1_OFFSET)  /* MFT1 b-port output status */
DECL|macro|M32R_MFT1CUT_PORTL
mdefine_line|#define M32R_MFT1CUT_PORTL     (0x08+M32R_MFT1_OFFSET)  /* MFT1 count */
DECL|macro|M32R_MFT1RLD_PORTL
mdefine_line|#define M32R_MFT1RLD_PORTL     (0x0C+M32R_MFT1_OFFSET)  /* MFT1 reload */
DECL|macro|M32R_MFT1CMPRLD_PORTL
mdefine_line|#define M32R_MFT1CMPRLD_PORTL  (0x10+M32R_MFT1_OFFSET)  /* MFT1 compare reload */
DECL|macro|M32R_MFT2_OFFSET
mdefine_line|#define M32R_MFT2_OFFSET       (0x300+M32R_MFT_OFFSET)
DECL|macro|M32R_MFT2MOD_PORTL
mdefine_line|#define M32R_MFT2MOD_PORTL     (0x00+M32R_MFT2_OFFSET)  /* MFT2 mode */
DECL|macro|M32R_MFT2BOS_PORTL
mdefine_line|#define M32R_MFT2BOS_PORTL     (0x04+M32R_MFT2_OFFSET)  /* MFT2 b-port output status */
DECL|macro|M32R_MFT2CUT_PORTL
mdefine_line|#define M32R_MFT2CUT_PORTL     (0x08+M32R_MFT2_OFFSET)  /* MFT2 count */
DECL|macro|M32R_MFT2RLD_PORTL
mdefine_line|#define M32R_MFT2RLD_PORTL     (0x0C+M32R_MFT2_OFFSET)  /* MFT2 reload */
DECL|macro|M32R_MFT2CMPRLD_PORTL
mdefine_line|#define M32R_MFT2CMPRLD_PORTL  (0x10+M32R_MFT2_OFFSET)  /* MFT2 compare reload */
DECL|macro|M32R_MFT3_OFFSET
mdefine_line|#define M32R_MFT3_OFFSET       (0x400+M32R_MFT_OFFSET)
DECL|macro|M32R_MFT3MOD_PORTL
mdefine_line|#define M32R_MFT3MOD_PORTL     (0x00+M32R_MFT3_OFFSET)  /* MFT3 mode */
DECL|macro|M32R_MFT3BOS_PORTL
mdefine_line|#define M32R_MFT3BOS_PORTL     (0x04+M32R_MFT3_OFFSET)  /* MFT3 b-port output status */
DECL|macro|M32R_MFT3CUT_PORTL
mdefine_line|#define M32R_MFT3CUT_PORTL     (0x08+M32R_MFT3_OFFSET)  /* MFT3 count */
DECL|macro|M32R_MFT3RLD_PORTL
mdefine_line|#define M32R_MFT3RLD_PORTL     (0x0C+M32R_MFT3_OFFSET)  /* MFT3 reload */
DECL|macro|M32R_MFT3CMPRLD_PORTL
mdefine_line|#define M32R_MFT3CMPRLD_PORTL  (0x10+M32R_MFT3_OFFSET)  /* MFT3 compare reload */
DECL|macro|M32R_MFT4_OFFSET
mdefine_line|#define M32R_MFT4_OFFSET       (0x500+M32R_MFT_OFFSET)
DECL|macro|M32R_MFT4MOD_PORTL
mdefine_line|#define M32R_MFT4MOD_PORTL     (0x00+M32R_MFT4_OFFSET)  /* MFT4 mode */
DECL|macro|M32R_MFT4BOS_PORTL
mdefine_line|#define M32R_MFT4BOS_PORTL     (0x04+M32R_MFT4_OFFSET)  /* MFT4 b-port output status */
DECL|macro|M32R_MFT4CUT_PORTL
mdefine_line|#define M32R_MFT4CUT_PORTL     (0x08+M32R_MFT4_OFFSET)  /* MFT4 count */
DECL|macro|M32R_MFT4RLD_PORTL
mdefine_line|#define M32R_MFT4RLD_PORTL     (0x0C+M32R_MFT4_OFFSET)  /* MFT4 reload */
DECL|macro|M32R_MFT4CMPRLD_PORTL
mdefine_line|#define M32R_MFT4CMPRLD_PORTL  (0x10+M32R_MFT4_OFFSET)  /* MFT4 compare reload */
DECL|macro|M32R_MFT5_OFFSET
mdefine_line|#define M32R_MFT5_OFFSET       (0x600+M32R_MFT_OFFSET)
DECL|macro|M32R_MFT5MOD_PORTL
mdefine_line|#define M32R_MFT5MOD_PORTL     (0x00+M32R_MFT5_OFFSET)  /* MFT4 mode */
DECL|macro|M32R_MFT5BOS_PORTL
mdefine_line|#define M32R_MFT5BOS_PORTL     (0x04+M32R_MFT5_OFFSET)  /* MFT4 b-port output status */
DECL|macro|M32R_MFT5CUT_PORTL
mdefine_line|#define M32R_MFT5CUT_PORTL     (0x08+M32R_MFT5_OFFSET)  /* MFT4 count */
DECL|macro|M32R_MFT5RLD_PORTL
mdefine_line|#define M32R_MFT5RLD_PORTL     (0x0C+M32R_MFT5_OFFSET)  /* MFT4 reload */
DECL|macro|M32R_MFT5CMPRLD_PORTL
mdefine_line|#define M32R_MFT5CMPRLD_PORTL  (0x10+M32R_MFT5_OFFSET)  /* MFT4 compare reload */
DECL|macro|M32R_MFTCR_MFT0MSK
mdefine_line|#define M32R_MFTCR_MFT0MSK  (1UL&lt;&lt;15)  /* b16 */
DECL|macro|M32R_MFTCR_MFT1MSK
mdefine_line|#define M32R_MFTCR_MFT1MSK  (1UL&lt;&lt;14)  /* b17 */
DECL|macro|M32R_MFTCR_MFT2MSK
mdefine_line|#define M32R_MFTCR_MFT2MSK  (1UL&lt;&lt;13)  /* b18 */
DECL|macro|M32R_MFTCR_MFT3MSK
mdefine_line|#define M32R_MFTCR_MFT3MSK  (1UL&lt;&lt;12)  /* b19 */
DECL|macro|M32R_MFTCR_MFT4MSK
mdefine_line|#define M32R_MFTCR_MFT4MSK  (1UL&lt;&lt;11)  /* b20 */
DECL|macro|M32R_MFTCR_MFT5MSK
mdefine_line|#define M32R_MFTCR_MFT5MSK  (1UL&lt;&lt;10)  /* b21 */
DECL|macro|M32R_MFTCR_MFT0EN
mdefine_line|#define M32R_MFTCR_MFT0EN   (1UL&lt;&lt;7)   /* b24 */
DECL|macro|M32R_MFTCR_MFT1EN
mdefine_line|#define M32R_MFTCR_MFT1EN   (1UL&lt;&lt;6)   /* b25 */
DECL|macro|M32R_MFTCR_MFT2EN
mdefine_line|#define M32R_MFTCR_MFT2EN   (1UL&lt;&lt;5)   /* b26 */
DECL|macro|M32R_MFTCR_MFT3EN
mdefine_line|#define M32R_MFTCR_MFT3EN   (1UL&lt;&lt;4)   /* b27 */
DECL|macro|M32R_MFTCR_MFT4EN
mdefine_line|#define M32R_MFTCR_MFT4EN   (1UL&lt;&lt;3)   /* b28 */
DECL|macro|M32R_MFTCR_MFT5EN
mdefine_line|#define M32R_MFTCR_MFT5EN   (1UL&lt;&lt;2)   /* b29 */
DECL|macro|M32R_MFTMOD_CC_MASK
mdefine_line|#define M32R_MFTMOD_CC_MASK    (1UL&lt;&lt;15)  /* b16 */
DECL|macro|M32R_MFTMOD_TCCR
mdefine_line|#define M32R_MFTMOD_TCCR       (1UL&lt;&lt;13)  /* b18 */
DECL|macro|M32R_MFTMOD_GTSEL000
mdefine_line|#define M32R_MFTMOD_GTSEL000   (0UL&lt;&lt;8)   /* b21-23 : 000 */
DECL|macro|M32R_MFTMOD_GTSEL001
mdefine_line|#define M32R_MFTMOD_GTSEL001   (1UL&lt;&lt;8)   /* b21-23 : 001 */
DECL|macro|M32R_MFTMOD_GTSEL010
mdefine_line|#define M32R_MFTMOD_GTSEL010   (2UL&lt;&lt;8)   /* b21-23 : 010 */
DECL|macro|M32R_MFTMOD_GTSEL011
mdefine_line|#define M32R_MFTMOD_GTSEL011   (3UL&lt;&lt;8)   /* b21-23 : 011 */
DECL|macro|M32R_MFTMOD_GTSEL110
mdefine_line|#define M32R_MFTMOD_GTSEL110   (6UL&lt;&lt;8)   /* b21-23 : 110 */
DECL|macro|M32R_MFTMOD_GTSEL111
mdefine_line|#define M32R_MFTMOD_GTSEL111   (7UL&lt;&lt;8)   /* b21-23 : 111 */
DECL|macro|M32R_MFTMOD_CMSEL
mdefine_line|#define M32R_MFTMOD_CMSEL      (1UL&lt;&lt;3)   /* b28 */
DECL|macro|M32R_MFTMOD_CSSEL000
mdefine_line|#define M32R_MFTMOD_CSSEL000   (0UL&lt;&lt;0)   /* b29-b31 : 000 */
DECL|macro|M32R_MFTMOD_CSSEL001
mdefine_line|#define M32R_MFTMOD_CSSEL001   (1UL&lt;&lt;0)   /* b29-b31 : 001 */
DECL|macro|M32R_MFTMOD_CSSEL010
mdefine_line|#define M32R_MFTMOD_CSSEL010   (2UL&lt;&lt;0)   /* b29-b31 : 010 */
DECL|macro|M32R_MFTMOD_CSSEL011
mdefine_line|#define M32R_MFTMOD_CSSEL011   (3UL&lt;&lt;0)   /* b29-b31 : 011 */
DECL|macro|M32R_MFTMOD_CSSEL100
mdefine_line|#define M32R_MFTMOD_CSSEL100   (4UL&lt;&lt;0)   /* b29-b31 : 100 */
DECL|macro|M32R_MFTMOD_CSSEL110
mdefine_line|#define M32R_MFTMOD_CSSEL110   (6UL&lt;&lt;0)   /* b29-b31 : 110 */
multiline_comment|/*&n; * Serial I/O registers.&n; */
DECL|macro|M32R_SIO_OFFSET
mdefine_line|#define M32R_SIO_OFFSET  (0x000FD000+M32R_SFR_OFFSET)
DECL|macro|M32R_SIO0_CR_PORTL
mdefine_line|#define M32R_SIO0_CR_PORTL     (0x000+M32R_SIO_OFFSET)
DECL|macro|M32R_SIO0_MOD0_PORTL
mdefine_line|#define M32R_SIO0_MOD0_PORTL   (0x004+M32R_SIO_OFFSET)
DECL|macro|M32R_SIO0_MOD1_PORTL
mdefine_line|#define M32R_SIO0_MOD1_PORTL   (0x008+M32R_SIO_OFFSET)
DECL|macro|M32R_SIO0_STS_PORTL
mdefine_line|#define M32R_SIO0_STS_PORTL    (0x00C+M32R_SIO_OFFSET)
DECL|macro|M32R_SIO0_TRCR_PORTL
mdefine_line|#define M32R_SIO0_TRCR_PORTL   (0x010+M32R_SIO_OFFSET)
DECL|macro|M32R_SIO0_BAUR_PORTL
mdefine_line|#define M32R_SIO0_BAUR_PORTL   (0x014+M32R_SIO_OFFSET)
DECL|macro|M32R_SIO0_RBAUR_PORTL
mdefine_line|#define M32R_SIO0_RBAUR_PORTL  (0x018+M32R_SIO_OFFSET)
DECL|macro|M32R_SIO0_TXB_PORTL
mdefine_line|#define M32R_SIO0_TXB_PORTL    (0x01C+M32R_SIO_OFFSET)
DECL|macro|M32R_SIO0_RXB_PORTL
mdefine_line|#define M32R_SIO0_RXB_PORTL    (0x020+M32R_SIO_OFFSET)
multiline_comment|/*&n; * Interrupt Control Unit registers.&n; */
DECL|macro|M32R_ICU_OFFSET
mdefine_line|#define M32R_ICU_OFFSET  (0x000FF000+M32R_SFR_OFFSET)
DECL|macro|M32R_ICU_ISTS_PORTL
mdefine_line|#define M32R_ICU_ISTS_PORTL     (0x004+M32R_ICU_OFFSET)
DECL|macro|M32R_ICU_IREQ0_PORTL
mdefine_line|#define M32R_ICU_IREQ0_PORTL    (0x008+M32R_ICU_OFFSET)
DECL|macro|M32R_ICU_IREQ1_PORTL
mdefine_line|#define M32R_ICU_IREQ1_PORTL    (0x00C+M32R_ICU_OFFSET)
DECL|macro|M32R_ICU_SBICR_PORTL
mdefine_line|#define M32R_ICU_SBICR_PORTL    (0x018+M32R_ICU_OFFSET)
DECL|macro|M32R_ICU_IMASK_PORTL
mdefine_line|#define M32R_ICU_IMASK_PORTL    (0x01C+M32R_ICU_OFFSET)
DECL|macro|M32R_ICU_CR1_PORTL
mdefine_line|#define M32R_ICU_CR1_PORTL      (0x200+M32R_ICU_OFFSET)  /* INT0 */
DECL|macro|M32R_ICU_CR2_PORTL
mdefine_line|#define M32R_ICU_CR2_PORTL      (0x204+M32R_ICU_OFFSET)  /* INT1 */
DECL|macro|M32R_ICU_CR3_PORTL
mdefine_line|#define M32R_ICU_CR3_PORTL      (0x208+M32R_ICU_OFFSET)  /* INT2 */
DECL|macro|M32R_ICU_CR4_PORTL
mdefine_line|#define M32R_ICU_CR4_PORTL      (0x20C+M32R_ICU_OFFSET)  /* INT3 */
DECL|macro|M32R_ICU_CR5_PORTL
mdefine_line|#define M32R_ICU_CR5_PORTL      (0x210+M32R_ICU_OFFSET)  /* INT4 */
DECL|macro|M32R_ICU_CR6_PORTL
mdefine_line|#define M32R_ICU_CR6_PORTL      (0x214+M32R_ICU_OFFSET)  /* INT5 */
DECL|macro|M32R_ICU_CR7_PORTL
mdefine_line|#define M32R_ICU_CR7_PORTL      (0x218+M32R_ICU_OFFSET)  /* INT6 */
DECL|macro|M32R_ICU_CR8_PORTL
mdefine_line|#define M32R_ICU_CR8_PORTL      (0x218+M32R_ICU_OFFSET)  /* INT7 */
DECL|macro|M32R_ICU_CR32_PORTL
mdefine_line|#define M32R_ICU_CR32_PORTL     (0x27C+M32R_ICU_OFFSET)  /* SIO0 RX */
DECL|macro|M32R_ICU_CR33_PORTL
mdefine_line|#define M32R_ICU_CR33_PORTL     (0x280+M32R_ICU_OFFSET)  /* SIO0 TX */
DECL|macro|M32R_ICU_CR40_PORTL
mdefine_line|#define M32R_ICU_CR40_PORTL     (0x29C+M32R_ICU_OFFSET)  /* DMAC0 */
DECL|macro|M32R_ICU_CR41_PORTL
mdefine_line|#define M32R_ICU_CR41_PORTL     (0x2A0+M32R_ICU_OFFSET)  /* DMAC1 */
DECL|macro|M32R_ICU_CR48_PORTL
mdefine_line|#define M32R_ICU_CR48_PORTL     (0x2BC+M32R_ICU_OFFSET)  /* MFT0 */
DECL|macro|M32R_ICU_CR49_PORTL
mdefine_line|#define M32R_ICU_CR49_PORTL     (0x2C0+M32R_ICU_OFFSET)  /* MFT1 */
DECL|macro|M32R_ICU_CR50_PORTL
mdefine_line|#define M32R_ICU_CR50_PORTL     (0x2C4+M32R_ICU_OFFSET)  /* MFT2 */
DECL|macro|M32R_ICU_CR51_PORTL
mdefine_line|#define M32R_ICU_CR51_PORTL     (0x2C8+M32R_ICU_OFFSET)  /* MFT3 */
DECL|macro|M32R_ICU_CR52_PORTL
mdefine_line|#define M32R_ICU_CR52_PORTL     (0x2CC+M32R_ICU_OFFSET)  /* MFT4 */
DECL|macro|M32R_ICU_CR53_PORTL
mdefine_line|#define M32R_ICU_CR53_PORTL     (0x2D0+M32R_ICU_OFFSET)  /* MFT5 */
DECL|macro|M32R_ICU_IPICR0_PORTL
mdefine_line|#define M32R_ICU_IPICR0_PORTL   (0x2DC+M32R_ICU_OFFSET)  /* IPI0 */
DECL|macro|M32R_ICU_IPICR1_PORTL
mdefine_line|#define M32R_ICU_IPICR1_PORTL   (0x2E0+M32R_ICU_OFFSET)  /* IPI1 */
DECL|macro|M32R_ICU_IPICR2_PORTL
mdefine_line|#define M32R_ICU_IPICR2_PORTL   (0x2E4+M32R_ICU_OFFSET)  /* IPI2 */
DECL|macro|M32R_ICU_IPICR3_PORTL
mdefine_line|#define M32R_ICU_IPICR3_PORTL   (0x2E8+M32R_ICU_OFFSET)  /* IPI3 */
DECL|macro|M32R_ICU_IPICR4_PORTL
mdefine_line|#define M32R_ICU_IPICR4_PORTL   (0x2EC+M32R_ICU_OFFSET)  /* IPI4 */
DECL|macro|M32R_ICU_IPICR5_PORTL
mdefine_line|#define M32R_ICU_IPICR5_PORTL   (0x2F0+M32R_ICU_OFFSET)  /* IPI5 */
DECL|macro|M32R_ICU_IPICR6_PORTL
mdefine_line|#define M32R_ICU_IPICR6_PORTL   (0x2F4+M32R_ICU_OFFSET)  /* IPI6 */
DECL|macro|M32R_ICU_IPICR7_PORTL
mdefine_line|#define M32R_ICU_IPICR7_PORTL   (0x2FC+M32R_ICU_OFFSET)  /* IPI7 */
DECL|macro|M32R_ICUISTS_VECB
mdefine_line|#define M32R_ICUISTS_VECB(val)  ((val&gt;&gt;28) &amp; 0xF)
DECL|macro|M32R_ICUISTS_ISN
mdefine_line|#define M32R_ICUISTS_ISN(val)   ((val&gt;&gt;22) &amp; 0x3F)
DECL|macro|M32R_ICUISTS_PIML
mdefine_line|#define M32R_ICUISTS_PIML(val)  ((val&gt;&gt;16) &amp; 0x7)
DECL|macro|M32R_ICUIMASK_IMSK0
mdefine_line|#define M32R_ICUIMASK_IMSK0  (0UL&lt;&lt;16)  /* b13-b15: Disable interrupt */
DECL|macro|M32R_ICUIMASK_IMSK1
mdefine_line|#define M32R_ICUIMASK_IMSK1  (1UL&lt;&lt;16)  /* b13-b15: Enable level 0 interrupt */
DECL|macro|M32R_ICUIMASK_IMSK2
mdefine_line|#define M32R_ICUIMASK_IMSK2  (2UL&lt;&lt;16)  /* b13-b15: Enable level 0,1 interrupt */
DECL|macro|M32R_ICUIMASK_IMSK3
mdefine_line|#define M32R_ICUIMASK_IMSK3  (3UL&lt;&lt;16)  /* b13-b15: Enable level 0-2 interrupt */
DECL|macro|M32R_ICUIMASK_IMSK4
mdefine_line|#define M32R_ICUIMASK_IMSK4  (4UL&lt;&lt;16)  /* b13-b15: Enable level 0-3 interrupt */
DECL|macro|M32R_ICUIMASK_IMSK5
mdefine_line|#define M32R_ICUIMASK_IMSK5  (5UL&lt;&lt;16)  /* b13-b15: Enable level 0-4 interrupt */
DECL|macro|M32R_ICUIMASK_IMSK6
mdefine_line|#define M32R_ICUIMASK_IMSK6  (6UL&lt;&lt;16)  /* b13-b15: Enable level 0-5 interrupt */
DECL|macro|M32R_ICUIMASK_IMSK7
mdefine_line|#define M32R_ICUIMASK_IMSK7  (7UL&lt;&lt;16)  /* b13-b15: Enable level 0-6 interrupt */
DECL|macro|M32R_ICUCR_IEN
mdefine_line|#define M32R_ICUCR_IEN      (1UL&lt;&lt;12)  /* b19: Interrupt enable */
DECL|macro|M32R_ICUCR_IRQ
mdefine_line|#define M32R_ICUCR_IRQ      (1UL&lt;&lt;8)   /* b23: Interrupt request */
DECL|macro|M32R_ICUCR_ISMOD00
mdefine_line|#define M32R_ICUCR_ISMOD00  (0UL&lt;&lt;4)   /* b26-b27: Interrupt sense mode Edge HtoL */
DECL|macro|M32R_ICUCR_ISMOD01
mdefine_line|#define M32R_ICUCR_ISMOD01  (1UL&lt;&lt;4)   /* b26-b27: Interrupt sense mode Level L */
DECL|macro|M32R_ICUCR_ISMOD10
mdefine_line|#define M32R_ICUCR_ISMOD10  (2UL&lt;&lt;4)   /* b26-b27: Interrupt sense mode Edge LtoH*/
DECL|macro|M32R_ICUCR_ISMOD11
mdefine_line|#define M32R_ICUCR_ISMOD11  (3UL&lt;&lt;4)   /* b26-b27: Interrupt sense mode Level H */
DECL|macro|M32R_ICUCR_ILEVEL0
mdefine_line|#define M32R_ICUCR_ILEVEL0  (0UL&lt;&lt;0)   /* b29-b31: Interrupt priority level 0 */
DECL|macro|M32R_ICUCR_ILEVEL1
mdefine_line|#define M32R_ICUCR_ILEVEL1  (1UL&lt;&lt;0)   /* b29-b31: Interrupt priority level 1 */
DECL|macro|M32R_ICUCR_ILEVEL2
mdefine_line|#define M32R_ICUCR_ILEVEL2  (2UL&lt;&lt;0)   /* b29-b31: Interrupt priority level 2 */
DECL|macro|M32R_ICUCR_ILEVEL3
mdefine_line|#define M32R_ICUCR_ILEVEL3  (3UL&lt;&lt;0)   /* b29-b31: Interrupt priority level 3 */
DECL|macro|M32R_ICUCR_ILEVEL4
mdefine_line|#define M32R_ICUCR_ILEVEL4  (4UL&lt;&lt;0)   /* b29-b31: Interrupt priority level 4 */
DECL|macro|M32R_ICUCR_ILEVEL5
mdefine_line|#define M32R_ICUCR_ILEVEL5  (5UL&lt;&lt;0)   /* b29-b31: Interrupt priority level 5 */
DECL|macro|M32R_ICUCR_ILEVEL6
mdefine_line|#define M32R_ICUCR_ILEVEL6  (6UL&lt;&lt;0)   /* b29-b31: Interrupt priority level 6 */
DECL|macro|M32R_ICUCR_ILEVEL7
mdefine_line|#define M32R_ICUCR_ILEVEL7  (7UL&lt;&lt;0)   /* b29-b31: Disable interrupt */
DECL|macro|M32R_ICUCR_ILEVEL_MASK
mdefine_line|#define M32R_ICUCR_ILEVEL_MASK  (7UL)
DECL|macro|M32R_IRQ_INT0
mdefine_line|#define M32R_IRQ_INT0    (1)   /* INT0 */
DECL|macro|M32R_IRQ_INT1
mdefine_line|#define M32R_IRQ_INT1    (2)   /* INT1 */
DECL|macro|M32R_IRQ_INT2
mdefine_line|#define M32R_IRQ_INT2    (3)   /* INT2 */
DECL|macro|M32R_IRQ_INT3
mdefine_line|#define M32R_IRQ_INT3    (4)   /* INT3 */
DECL|macro|M32R_IRQ_INT4
mdefine_line|#define M32R_IRQ_INT4    (5)   /* INT4 */
DECL|macro|M32R_IRQ_INT5
mdefine_line|#define M32R_IRQ_INT5    (6)   /* INT5 */
DECL|macro|M32R_IRQ_INT6
mdefine_line|#define M32R_IRQ_INT6    (7)   /* INT6 */
DECL|macro|M32R_IRQ_INT7
mdefine_line|#define M32R_IRQ_INT7    (8)   /* INT7 */
DECL|macro|M32R_IRQ_MFT0
mdefine_line|#define M32R_IRQ_MFT0    (16)  /* MFT0 */
DECL|macro|M32R_IRQ_MFT1
mdefine_line|#define M32R_IRQ_MFT1    (17)  /* MFT1 */
DECL|macro|M32R_IRQ_MFT2
mdefine_line|#define M32R_IRQ_MFT2    (18)  /* MFT2 */
DECL|macro|M32R_IRQ_MFT3
mdefine_line|#define M32R_IRQ_MFT3    (19)  /* MFT3 */
DECL|macro|M32R_IRQ_MFT4
mdefine_line|#define M32R_IRQ_MFT4    (20)  /* MFT4 */
DECL|macro|M32R_IRQ_MFT5
mdefine_line|#define M32R_IRQ_MFT5    (21)  /* MFT5 */
DECL|macro|M32R_IRQ_DMAC0
mdefine_line|#define M32R_IRQ_DMAC0   (32)  /* DMAC0 */
DECL|macro|M32R_IRQ_DMAC1
mdefine_line|#define M32R_IRQ_DMAC1   (33)  /* DMAC1 */
DECL|macro|M32R_IRQ_SIO0_R
mdefine_line|#define M32R_IRQ_SIO0_R  (48)  /* SIO0 receive */
DECL|macro|M32R_IRQ_SIO0_S
mdefine_line|#define M32R_IRQ_SIO0_S  (49)  /* SIO0 send    */
DECL|macro|M32R_IRQ_SIO1_R
mdefine_line|#define M32R_IRQ_SIO1_R  (50)  /* SIO1 send    */
DECL|macro|M32R_IRQ_SIO1_S
mdefine_line|#define M32R_IRQ_SIO1_S  (51)  /* SIO1 receive */
DECL|macro|M32R_IRQ_IPI0
mdefine_line|#define M32R_IRQ_IPI0    (56)  /* IPI0 */
DECL|macro|M32R_IRQ_IPI1
mdefine_line|#define M32R_IRQ_IPI1    (57)  /* IPI1 */
DECL|macro|M32R_IRQ_IPI2
mdefine_line|#define M32R_IRQ_IPI2    (58)  /* IPI2 */
DECL|macro|M32R_IRQ_IPI3
mdefine_line|#define M32R_IRQ_IPI3    (59)  /* IPI3 */
DECL|macro|M32R_IRQ_IPI4
mdefine_line|#define M32R_IRQ_IPI4    (60)  /* IPI4 */
DECL|macro|M32R_IRQ_IPI5
mdefine_line|#define M32R_IRQ_IPI5    (61)  /* IPI5 */
DECL|macro|M32R_IRQ_IPI6
mdefine_line|#define M32R_IRQ_IPI6    (62)  /* IPI6 */
DECL|macro|M32R_IRQ_IPI7
mdefine_line|#define M32R_IRQ_IPI7    (63)  /* IPI7 */
multiline_comment|/*======================================================================*&n; * CPU&n; *======================================================================*/
DECL|macro|M32R_CPUID_PORTL
mdefine_line|#define M32R_CPUID_PORTL   (0xFFFFFFE0)
DECL|macro|M32R_MCICAR_PORTL
mdefine_line|#define M32R_MCICAR_PORTL  (0xFFFFFFF0)
DECL|macro|M32R_MCDCAR_PORTL
mdefine_line|#define M32R_MCDCAR_PORTL  (0xFFFFFFF4)
DECL|macro|M32R_MCCR_PORTL
mdefine_line|#define M32R_MCCR_PORTL    (0xFFFFFFFC)
macro_line|#endif  /* _ASM_M32R_M32R_MP_FPGA_ */
eof
