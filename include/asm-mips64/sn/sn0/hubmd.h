multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Derived from IRIX &lt;sys/SN/SN0/hubmd.h&gt;, revision 1.59.&n; *&n; * Copyright (C) 1992 - 1997, 1999 Silicon Graphics, Inc.&n; * Copyright (C) 1999 by Ralf Baechle&n; */
macro_line|#ifndef&t;_ASM_SN_SN0_HUBMD_H
DECL|macro|_ASM_SN_SN0_HUBMD_H
mdefine_line|#define&t;_ASM_SN_SN0_HUBMD_H
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n; * Hub Memory/Directory interface registers&n; */
DECL|macro|CACHE_SLINE_SIZE
mdefine_line|#define CACHE_SLINE_SIZE        128&t;/* Secondary cache line size on SN0 */
DECL|macro|MAX_REGIONS
mdefine_line|#define&t;MAX_REGIONS&t;&t;64
multiline_comment|/* Hardware page size and shift */
DECL|macro|MD_PAGE_SIZE
mdefine_line|#define MD_PAGE_SIZE&t;&t;4096&t; /* Page size in bytes&t;&t;    */
DECL|macro|MD_PAGE_NUM_SHFT
mdefine_line|#define MD_PAGE_NUM_SHFT&t;12&t; /* Address to page number shift    */
multiline_comment|/* Register offsets from LOCAL_HUB or REMOTE_HUB */
DECL|macro|MD_BASE
mdefine_line|#define MD_BASE&t;&t;&t;0x200000
DECL|macro|MD_BASE_PERF
mdefine_line|#define MD_BASE_PERF&t;&t;0x210000
DECL|macro|MD_BASE_JUNK
mdefine_line|#define MD_BASE_JUNK&t;&t;0x220000
DECL|macro|MD_IO_PROTECT
mdefine_line|#define MD_IO_PROTECT&t;&t;0x200000 /* MD and core register protection */
DECL|macro|MD_IO_PROT_OVRRD
mdefine_line|#define MD_IO_PROT_OVRRD&t;0x200008 /* Clear my bit in MD_IO_PROTECT   */
DECL|macro|MD_HSPEC_PROTECT
mdefine_line|#define MD_HSPEC_PROTECT&t;0x200010 /* BDDIR, LBOOT, RBOOT protection  */
DECL|macro|MD_MEMORY_CONFIG
mdefine_line|#define MD_MEMORY_CONFIG&t;0x200018 /* Memory/Directory DIMM control   */
DECL|macro|MD_REFRESH_CONTROL
mdefine_line|#define&t;MD_REFRESH_CONTROL&t;0x200020 /* Memory/Directory refresh ctrl   */
DECL|macro|MD_FANDOP_CAC_STAT
mdefine_line|#define&t;MD_FANDOP_CAC_STAT&t;0x200028 /* Fetch-and-op cache status &t;    */
DECL|macro|MD_MIG_DIFF_THRESH
mdefine_line|#define&t;MD_MIG_DIFF_THRESH&t;0x200030 /* Page migr. count diff thresh.   */
DECL|macro|MD_MIG_VALUE_THRESH
mdefine_line|#define&t;MD_MIG_VALUE_THRESH&t;0x200038 /* Page migr. count abs. thresh.   */
DECL|macro|MD_MIG_CANDIDATE
mdefine_line|#define&t;MD_MIG_CANDIDATE&t;0x200040 /* Latest page migration candidate */
DECL|macro|MD_MIG_CANDIDATE_CLR
mdefine_line|#define&t;MD_MIG_CANDIDATE_CLR&t;0x200048 /* Clear page migration candidate  */
DECL|macro|MD_DIR_ERROR
mdefine_line|#define MD_DIR_ERROR&t;&t;0x200050 /* Directory DIMM error &t;    */
DECL|macro|MD_DIR_ERROR_CLR
mdefine_line|#define MD_DIR_ERROR_CLR&t;0x200058 /* Directory DIMM error clear &t;    */
DECL|macro|MD_PROTOCOL_ERROR
mdefine_line|#define MD_PROTOCOL_ERROR&t;0x200060 /* Directory protocol error &t;    */
DECL|macro|MD_PROTOCOL_ERROR_CLR
mdefine_line|#define MD_PROTOCOL_ERROR_CLR&t;0x200068 /* Directory protocol error clear  */
DECL|macro|MD_MEM_ERROR
mdefine_line|#define MD_MEM_ERROR&t;&t;0x200070 /* Memory DIMM error &t;&t;    */
DECL|macro|MD_MEM_ERROR_CLR
mdefine_line|#define MD_MEM_ERROR_CLR&t;0x200078 /* Memory DIMM error clear &t;    */
DECL|macro|MD_MISC_ERROR
mdefine_line|#define MD_MISC_ERROR&t;&t;0x200080 /* Miscellaneous MD error &t;    */
DECL|macro|MD_MISC_ERROR_CLR
mdefine_line|#define MD_MISC_ERROR_CLR&t;0x200088 /* Miscellaneous MD error clear    */
DECL|macro|MD_MEM_DIMM_INIT
mdefine_line|#define MD_MEM_DIMM_INIT&t;0x200090 /* Memory DIMM mode initization.   */
DECL|macro|MD_DIR_DIMM_INIT
mdefine_line|#define MD_DIR_DIMM_INIT&t;0x200098 /* Directory DIMM mode init. &t;    */
DECL|macro|MD_MOQ_SIZE
mdefine_line|#define MD_MOQ_SIZE&t;&t;0x2000a0 /* MD outgoing queue size &t;    */
DECL|macro|MD_MLAN_CTL
mdefine_line|#define MD_MLAN_CTL&t;&t;0x2000a8 /* NIC (Microlan) control register */
DECL|macro|MD_PERF_SEL
mdefine_line|#define MD_PERF_SEL&t;&t;0x210000 /* Select perf monitor events &t;    */
DECL|macro|MD_PERF_CNT0
mdefine_line|#define MD_PERF_CNT0&t;&t;0x210010 /* Performance counter 0 &t;    */
DECL|macro|MD_PERF_CNT1
mdefine_line|#define MD_PERF_CNT1&t;&t;0x210018 /* Performance counter 1 &t;    */
DECL|macro|MD_PERF_CNT2
mdefine_line|#define MD_PERF_CNT2&t;&t;0x210020 /* Performance counter 2 &t;    */
DECL|macro|MD_PERF_CNT3
mdefine_line|#define MD_PERF_CNT3&t;&t;0x210028 /* Performance counter 3 &t;    */
DECL|macro|MD_PERF_CNT4
mdefine_line|#define MD_PERF_CNT4&t;&t;0x210030 /* Performance counter 4 &t;    */
DECL|macro|MD_PERF_CNT5
mdefine_line|#define MD_PERF_CNT5&t;&t;0x210038 /* Performance counter 5 &t;    */
DECL|macro|MD_UREG0_0
mdefine_line|#define MD_UREG0_0&t;&t;0x220000 /* uController/UART 0 register     */
DECL|macro|MD_UREG0_1
mdefine_line|#define MD_UREG0_1&t;&t;0x220008 /* uController/UART 0 register     */
DECL|macro|MD_UREG0_2
mdefine_line|#define MD_UREG0_2&t;&t;0x220010 /* uController/UART 0 register     */
DECL|macro|MD_UREG0_3
mdefine_line|#define MD_UREG0_3&t;&t;0x220018 /* uController/UART 0 register     */
DECL|macro|MD_UREG0_4
mdefine_line|#define MD_UREG0_4&t;&t;0x220020 /* uController/UART 0 register     */
DECL|macro|MD_UREG0_5
mdefine_line|#define MD_UREG0_5&t;&t;0x220028 /* uController/UART 0 register     */
DECL|macro|MD_UREG0_6
mdefine_line|#define MD_UREG0_6&t;&t;0x220030 /* uController/UART 0 register     */
DECL|macro|MD_UREG0_7
mdefine_line|#define MD_UREG0_7&t;&t;0x220038 /* uController/UART 0 register     */
DECL|macro|MD_SLOTID_USTAT
mdefine_line|#define MD_SLOTID_USTAT&t;&t;0x220048 /* Hub slot ID &amp; UART/uCtlr status */
DECL|macro|MD_LED0
mdefine_line|#define MD_LED0&t;&t;&t;0x220050 /* Eight-bit LED for CPU A &t;    */
DECL|macro|MD_LED1
mdefine_line|#define MD_LED1&t;&t;&t;0x220058 /* Eight-bit LED for CPU B &t;    */
DECL|macro|MD_UREG1_0
mdefine_line|#define MD_UREG1_0&t;&t;0x220080 /* uController/UART 1 register     */
DECL|macro|MD_UREG1_1
mdefine_line|#define MD_UREG1_1&t;&t;0x220088 /* uController/UART 1 register     */
DECL|macro|MD_UREG1_2
mdefine_line|#define MD_UREG1_2&t;&t;0x220090 /* uController/UART 1 register     */
DECL|macro|MD_UREG1_3
mdefine_line|#define MD_UREG1_3&t;&t;0x220098 /* uController/UART 1 register     */
DECL|macro|MD_UREG1_4
mdefine_line|#define MD_UREG1_4&t;&t;0x2200a0 /* uController/UART 1 register     */
DECL|macro|MD_UREG1_5
mdefine_line|#define MD_UREG1_5&t;&t;0x2200a8 /* uController/UART 1 register     */
DECL|macro|MD_UREG1_6
mdefine_line|#define MD_UREG1_6&t;&t;0x2200b0 /* uController/UART 1 register     */
DECL|macro|MD_UREG1_7
mdefine_line|#define MD_UREG1_7&t;&t;0x2200b8 /* uController/UART 1 register     */
DECL|macro|MD_UREG1_8
mdefine_line|#define MD_UREG1_8&t;&t;0x2200c0 /* uController/UART 1 register     */
DECL|macro|MD_UREG1_9
mdefine_line|#define MD_UREG1_9&t;&t;0x2200c8 /* uController/UART 1 register     */
DECL|macro|MD_UREG1_10
mdefine_line|#define MD_UREG1_10&t;&t;0x2200d0 /* uController/UART 1 register     */
DECL|macro|MD_UREG1_11
mdefine_line|#define MD_UREG1_11&t;&t;0x2200d8 /* uController/UART 1 register     */
DECL|macro|MD_UREG1_12
mdefine_line|#define MD_UREG1_12&t;&t;0x2200e0 /* uController/UART 1 register     */
DECL|macro|MD_UREG1_13
mdefine_line|#define MD_UREG1_13&t;&t;0x2200e8 /* uController/UART 1 register     */
DECL|macro|MD_UREG1_14
mdefine_line|#define MD_UREG1_14&t;&t;0x2200f0 /* uController/UART 1 register     */
DECL|macro|MD_UREG1_15
mdefine_line|#define MD_UREG1_15&t;&t;0x2200f8 /* uController/UART 1 register     */
macro_line|#ifdef CONFIG_SGI_SN0_N_MODE
DECL|macro|MD_MEM_BANKS
mdefine_line|#define MD_MEM_BANKS&t;&t;4&t; /* 4 banks of memory max in N mode */
macro_line|#else
DECL|macro|MD_MEM_BANKS
mdefine_line|#define MD_MEM_BANKS&t;&t;8&t; /* 8 banks of memory max in M mode */
macro_line|#endif
multiline_comment|/*&n; * MD_MEMORY_CONFIG fields&n; *&n; *   MD_SIZE_xxx are useful for representing the size of a SIMM or bank&n; *   (SIMM pair).  They correspond to the values needed for the bit&n; *   triplets (MMC_BANK_MASK) in the MD_MEMORY_CONFIG register for bank size.&n; *   Bits not used by the MD are used by software.&n; */
DECL|macro|MD_SIZE_EMPTY
mdefine_line|#define MD_SIZE_EMPTY&t;&t;0&t;/* Valid in MEMORY_CONFIG           */
DECL|macro|MD_SIZE_8MB
mdefine_line|#define MD_SIZE_8MB&t;&t;1
DECL|macro|MD_SIZE_16MB
mdefine_line|#define MD_SIZE_16MB&t;&t;2
DECL|macro|MD_SIZE_32MB
mdefine_line|#define MD_SIZE_32MB&t;&t;3&t;/* Broken in Hub 1&t;&t;    */
DECL|macro|MD_SIZE_64MB
mdefine_line|#define MD_SIZE_64MB&t;&t;4&t;/* Valid in MEMORY_CONFIG           */
DECL|macro|MD_SIZE_128MB
mdefine_line|#define MD_SIZE_128MB&t;&t;5&t;/* Valid in MEMORY_CONFIG           */
DECL|macro|MD_SIZE_256MB
mdefine_line|#define MD_SIZE_256MB&t;&t;6
DECL|macro|MD_SIZE_512MB
mdefine_line|#define MD_SIZE_512MB&t;&t;7&t;/* Valid in MEMORY_CONFIG           */
DECL|macro|MD_SIZE_1GB
mdefine_line|#define MD_SIZE_1GB&t;&t;8
DECL|macro|MD_SIZE_2GB
mdefine_line|#define MD_SIZE_2GB&t;&t;9
DECL|macro|MD_SIZE_4GB
mdefine_line|#define MD_SIZE_4GB&t;&t;10
DECL|macro|MD_SIZE_BYTES
mdefine_line|#define MD_SIZE_BYTES(size)&t;((size) == 0 ? 0 : 0x400000L &lt;&lt; (size))
DECL|macro|MD_SIZE_MBYTES
mdefine_line|#define MD_SIZE_MBYTES(size)&t;((size) == 0 ? 0 :   4&t;     &lt;&lt; (size))
DECL|macro|MMC_FPROM_CYC_SHFT
mdefine_line|#define MMC_FPROM_CYC_SHFT&t;49&t;/* Have to use UINT64_CAST, instead */
DECL|macro|MMC_FPROM_CYC_MASK
mdefine_line|#define MMC_FPROM_CYC_MASK&t;(UINT64_CAST 31 &lt;&lt; 49)&t;/* of &squot;L&squot; suffix,   */
DECL|macro|MMC_FPROM_WR_SHFT
mdefine_line|#define MMC_FPROM_WR_SHFT&t;44&t;&t;&t;/* for assembler    */
DECL|macro|MMC_FPROM_WR_MASK
mdefine_line|#define MMC_FPROM_WR_MASK&t;(UINT64_CAST 31 &lt;&lt; 44)
DECL|macro|MMC_UCTLR_CYC_SHFT
mdefine_line|#define MMC_UCTLR_CYC_SHFT&t;39
DECL|macro|MMC_UCTLR_CYC_MASK
mdefine_line|#define MMC_UCTLR_CYC_MASK&t;(UINT64_CAST 31 &lt;&lt; 39)
DECL|macro|MMC_UCTLR_WR_SHFT
mdefine_line|#define MMC_UCTLR_WR_SHFT&t;34
DECL|macro|MMC_UCTLR_WR_MASK
mdefine_line|#define MMC_UCTLR_WR_MASK&t;(UINT64_CAST 31 &lt;&lt; 34)
DECL|macro|MMC_DIMM0_SEL_SHFT
mdefine_line|#define MMC_DIMM0_SEL_SHFT&t;32
DECL|macro|MMC_DIMM0_SEL_MASK
mdefine_line|#define MMC_DIMM0_SEL_MASK&t;(UINT64_CAST 3 &lt;&lt; 32)
DECL|macro|MMC_IO_PROT_EN_SHFT
mdefine_line|#define MMC_IO_PROT_EN_SHFT&t;31
DECL|macro|MMC_IO_PROT_EN_MASK
mdefine_line|#define MMC_IO_PROT_EN_MASK&t;(UINT64_CAST 1 &lt;&lt; 31)
DECL|macro|MMC_IO_PROT
mdefine_line|#define MMC_IO_PROT&t;&t;(UINT64_CAST 1 &lt;&lt; 31)
DECL|macro|MMC_ARB_MLSS_SHFT
mdefine_line|#define MMC_ARB_MLSS_SHFT&t;30
DECL|macro|MMC_ARB_MLSS_MASK
mdefine_line|#define MMC_ARB_MLSS_MASK&t;(UINT64_CAST 1 &lt;&lt; 30)
DECL|macro|MMC_ARB_MLSS
mdefine_line|#define MMC_ARB_MLSS&t;&t;(UINT64_CAST 1 &lt;&lt; 30)
DECL|macro|MMC_IGNORE_ECC_SHFT
mdefine_line|#define MMC_IGNORE_ECC_SHFT&t;29
DECL|macro|MMC_IGNORE_ECC_MASK
mdefine_line|#define MMC_IGNORE_ECC_MASK&t;(UINT64_CAST 1 &lt;&lt; 29)
DECL|macro|MMC_IGNORE_ECC
mdefine_line|#define MMC_IGNORE_ECC&t;&t;(UINT64_CAST 1 &lt;&lt; 29)
DECL|macro|MMC_DIR_PREMIUM_SHFT
mdefine_line|#define MMC_DIR_PREMIUM_SHFT&t;28
DECL|macro|MMC_DIR_PREMIUM_MASK
mdefine_line|#define MMC_DIR_PREMIUM_MASK&t;(UINT64_CAST 1 &lt;&lt; 28)
DECL|macro|MMC_DIR_PREMIUM
mdefine_line|#define MMC_DIR_PREMIUM&t;&t;(UINT64_CAST 1 &lt;&lt; 28)
DECL|macro|MMC_REPLY_GUAR_SHFT
mdefine_line|#define MMC_REPLY_GUAR_SHFT&t;24
DECL|macro|MMC_REPLY_GUAR_MASK
mdefine_line|#define MMC_REPLY_GUAR_MASK&t;(UINT64_CAST 15 &lt;&lt; 24)
DECL|macro|MMC_BANK_SHFT
mdefine_line|#define MMC_BANK_SHFT(_b)&t;((_b) * 3)
DECL|macro|MMC_BANK_MASK
mdefine_line|#define MMC_BANK_MASK(_b)&t;(UINT64_CAST 7 &lt;&lt; MMC_BANK_SHFT(_b))
DECL|macro|MMC_BANK_ALL_MASK
mdefine_line|#define MMC_BANK_ALL_MASK&t;0xffffff
DECL|macro|MMC_RESET_DEFAULTS
mdefine_line|#define MMC_RESET_DEFAULTS&t;(UINT64_CAST 0x0f &lt;&lt; MMC_FPROM_CYC_SHFT | &bslash;&n;&t;&t;&t;&t; UINT64_CAST 0x07 &lt;&lt; MMC_FPROM_WR_SHFT | &bslash;&n;&t;&t;&t;&t; UINT64_CAST 0x1f &lt;&lt; MMC_UCTLR_CYC_SHFT | &bslash;&n;&t;&t;&t;&t; UINT64_CAST 0x0f &lt;&lt; MMC_UCTLR_WR_SHFT | &bslash;&n;&t;&t;&t;&t; MMC_IGNORE_ECC | MMC_DIR_PREMIUM | &bslash;&n;&t;&t;&t;&t; UINT64_CAST 0x0f &lt;&lt; MMC_REPLY_GUAR_SHFT | &bslash;&n;&t;&t;&t;&t; MMC_BANK_ALL_MASK)
multiline_comment|/* MD_REFRESH_CONTROL fields */
DECL|macro|MRC_ENABLE_SHFT
mdefine_line|#define MRC_ENABLE_SHFT&t;&t;63
DECL|macro|MRC_ENABLE_MASK
mdefine_line|#define MRC_ENABLE_MASK&t;&t;(UINT64_CAST 1 &lt;&lt; 63)
DECL|macro|MRC_ENABLE
mdefine_line|#define MRC_ENABLE&t;&t;(UINT64_CAST 1 &lt;&lt; 63)
DECL|macro|MRC_COUNTER_SHFT
mdefine_line|#define MRC_COUNTER_SHFT&t;12
DECL|macro|MRC_COUNTER_MASK
mdefine_line|#define MRC_COUNTER_MASK&t;(UINT64_CAST 0xfff &lt;&lt; 12)
DECL|macro|MRC_CNT_THRESH_MASK
mdefine_line|#define MRC_CNT_THRESH_MASK&t;0xfff
DECL|macro|MRC_RESET_DEFAULTS
mdefine_line|#define MRC_RESET_DEFAULTS&t;(UINT64_CAST 0x400)
multiline_comment|/* MD_MEM_DIMM_INIT and MD_DIR_DIMM_INIT fields */
DECL|macro|MDI_SELECT_SHFT
mdefine_line|#define MDI_SELECT_SHFT&t;&t;32
DECL|macro|MDI_SELECT_MASK
mdefine_line|#define MDI_SELECT_MASK&t;&t;(UINT64_CAST 0x0f &lt;&lt; 32)
DECL|macro|MDI_DIMM_MODE_MASK
mdefine_line|#define MDI_DIMM_MODE_MASK&t;(UINT64_CAST 0xfff)
multiline_comment|/* MD_MOQ_SIZE fields */
DECL|macro|MMS_RP_SIZE_SHFT
mdefine_line|#define MMS_RP_SIZE_SHFT&t;8
DECL|macro|MMS_RP_SIZE_MASK
mdefine_line|#define MMS_RP_SIZE_MASK&t;(UINT64_CAST 0x3f &lt;&lt; 8)
DECL|macro|MMS_RQ_SIZE_SHFT
mdefine_line|#define MMS_RQ_SIZE_SHFT&t;0
DECL|macro|MMS_RQ_SIZE_MASK
mdefine_line|#define MMS_RQ_SIZE_MASK&t;(UINT64_CAST 0x1f)
DECL|macro|MMS_RESET_DEFAULTS
mdefine_line|#define MMS_RESET_DEFAULTS&t;(0x32 &lt;&lt; 8 | 0x12)
multiline_comment|/* MD_FANDOP_CAC_STAT fields */
DECL|macro|MFC_VALID_SHFT
mdefine_line|#define MFC_VALID_SHFT&t;&t;63
DECL|macro|MFC_VALID_MASK
mdefine_line|#define MFC_VALID_MASK&t;&t;(UINT64_CAST 1 &lt;&lt; 63)
DECL|macro|MFC_VALID
mdefine_line|#define MFC_VALID&t;&t;(UINT64_CAST 1 &lt;&lt; 63)
DECL|macro|MFC_ADDR_SHFT
mdefine_line|#define MFC_ADDR_SHFT&t;&t;6
DECL|macro|MFC_ADDR_MASK
mdefine_line|#define MFC_ADDR_MASK&t;&t;(UINT64_CAST 0x3ffffff)
multiline_comment|/* MD_MLAN_CTL fields */
DECL|macro|MLAN_PHI1_SHFT
mdefine_line|#define MLAN_PHI1_SHFT&t;&t;27
DECL|macro|MLAN_PHI1_MASK
mdefine_line|#define MLAN_PHI1_MASK&t;&t;(UINT64_CAST 0x7f &lt;&lt; 27)
DECL|macro|MLAN_PHI0_SHFT
mdefine_line|#define MLAN_PHI0_SHFT&t;&t;20
DECL|macro|MLAN_PHI0_MASK
mdefine_line|#define MLAN_PHI0_MASK&t;&t;(UINT64_CAST 0x7f &lt;&lt; 27)
DECL|macro|MLAN_PULSE_SHFT
mdefine_line|#define MLAN_PULSE_SHFT&t;&t;10
DECL|macro|MLAN_PULSE_MASK
mdefine_line|#define MLAN_PULSE_MASK&t;&t;(UINT64_CAST 0x3ff &lt;&lt; 10)
DECL|macro|MLAN_SAMPLE_SHFT
mdefine_line|#define MLAN_SAMPLE_SHFT&t;2
DECL|macro|MLAN_SAMPLE_MASK
mdefine_line|#define MLAN_SAMPLE_MASK&t;(UINT64_CAST 0xff &lt;&lt; 2)
DECL|macro|MLAN_DONE_SHFT
mdefine_line|#define MLAN_DONE_SHFT&t;&t;1
DECL|macro|MLAN_DONE_MASK
mdefine_line|#define MLAN_DONE_MASK&t;&t;2
DECL|macro|MLAN_DONE
mdefine_line|#define MLAN_DONE&t;&t;(UINT64_CAST 0x02)
DECL|macro|MLAN_RD_DATA
mdefine_line|#define MLAN_RD_DATA&t;&t;(UINT64_CAST 0x01)
DECL|macro|MLAN_RESET_DEFAULTS
mdefine_line|#define MLAN_RESET_DEFAULTS&t;(UINT64_CAST 0x31 &lt;&lt; MLAN_PHI1_SHFT | &bslash;&n;&t;&t;&t;&t; UINT64_CAST 0x31 &lt;&lt; MLAN_PHI0_SHFT)
multiline_comment|/* MD_SLOTID_USTAT bit definitions */
DECL|macro|MSU_CORECLK_TST_SHFT
mdefine_line|#define MSU_CORECLK_TST_SHFT&t;7&t;/* You don&squot;t wanna know             */
DECL|macro|MSU_CORECLK_TST_MASK
mdefine_line|#define MSU_CORECLK_TST_MASK&t;(UINT64_CAST 1 &lt;&lt; 7)
DECL|macro|MSU_CORECLK_TST
mdefine_line|#define MSU_CORECLK_TST&t;&t;(UINT64_CAST 1 &lt;&lt; 7)
DECL|macro|MSU_CORECLK_SHFT
mdefine_line|#define MSU_CORECLK_SHFT&t;6&t;/* You don&squot;t wanna know             */
DECL|macro|MSU_CORECLK_MASK
mdefine_line|#define MSU_CORECLK_MASK&t;(UINT64_CAST 1 &lt;&lt; 6)
DECL|macro|MSU_CORECLK
mdefine_line|#define MSU_CORECLK&t;&t;(UINT64_CAST 1 &lt;&lt; 6)
DECL|macro|MSU_NETSYNC_SHFT
mdefine_line|#define MSU_NETSYNC_SHFT&t;5&t;/* You don&squot;t wanna know             */
DECL|macro|MSU_NETSYNC_MASK
mdefine_line|#define MSU_NETSYNC_MASK&t;(UINT64_CAST 1 &lt;&lt; 5)
DECL|macro|MSU_NETSYNC
mdefine_line|#define MSU_NETSYNC&t;&t;(UINT64_CAST 1 &lt;&lt; 5)
DECL|macro|MSU_FPROMRDY_SHFT
mdefine_line|#define MSU_FPROMRDY_SHFT&t;4&t;/* Flash PROM ready bit &t;    */
DECL|macro|MSU_FPROMRDY_MASK
mdefine_line|#define MSU_FPROMRDY_MASK&t;(UINT64_CAST 1 &lt;&lt; 4)
DECL|macro|MSU_FPROMRDY
mdefine_line|#define MSU_FPROMRDY&t;&t;(UINT64_CAST 1 &lt;&lt; 4)
DECL|macro|MSU_I2CINTR_SHFT
mdefine_line|#define MSU_I2CINTR_SHFT&t;&t;3&t;/* I2C interrupt bit   */
DECL|macro|MSU_I2CINTR_MASK
mdefine_line|#define MSU_I2CINTR_MASK&t;&t;(UINT64_CAST 1 &lt;&lt; 3)
DECL|macro|MSU_I2CINTR
mdefine_line|#define MSU_I2CINTR&t;&t;(UINT64_CAST 1 &lt;&lt; 3)
DECL|macro|MSU_SLOTID_MASK
mdefine_line|#define MSU_SLOTID_MASK&t;&t;0xff
DECL|macro|MSU_SN0_SLOTID_SHFT
mdefine_line|#define MSU_SN0_SLOTID_SHFT&t;0&t;/* Slot ID&t;&t;&t;    */
DECL|macro|MSU_SN0_SLOTID_MASK
mdefine_line|#define MSU_SN0_SLOTID_MASK&t;(UINT64_CAST 7)
DECL|macro|MSU_SN00_SLOTID_SHFT
mdefine_line|#define MSU_SN00_SLOTID_SHFT&t;7
DECL|macro|MSU_SN00_SLOTID_MASK
mdefine_line|#define MSU_SN00_SLOTID_MASK&t;(UINT64_CAST 0x80)
DECL|macro|MSU_PIMM_PSC_SHFT
mdefine_line|#define&t;MSU_PIMM_PSC_SHFT&t;4
DECL|macro|MSU_PIMM_PSC_MASK
mdefine_line|#define&t;MSU_PIMM_PSC_MASK&t;(0xf &lt;&lt; MSU_PIMM_PSC_SHFT)
multiline_comment|/* MD_MIG_DIFF_THRESH bit definitions */
DECL|macro|MD_MIG_DIFF_THRES_VALID_MASK
mdefine_line|#define MD_MIG_DIFF_THRES_VALID_MASK (UINT64_CAST 0x1 &lt;&lt; 63)
DECL|macro|MD_MIG_DIFF_THRES_VALID_SHFT
mdefine_line|#define MD_MIG_DIFF_THRES_VALID_SHFT 63
DECL|macro|MD_MIG_DIFF_THRES_VALUE_MASK
mdefine_line|#define MD_MIG_DIFF_THRES_VALUE_MASK (UINT64_CAST 0xfffff)
multiline_comment|/* MD_MIG_VALUE_THRESH bit definitions */
DECL|macro|MD_MIG_VALUE_THRES_VALID_MASK
mdefine_line|#define MD_MIG_VALUE_THRES_VALID_MASK (UINT64_CAST 0x1 &lt;&lt; 63)
DECL|macro|MD_MIG_VALUE_THRES_VALID_SHFT
mdefine_line|#define MD_MIG_VALUE_THRES_VALID_SHFT 63
DECL|macro|MD_MIG_VALUE_THRES_VALUE_MASK
mdefine_line|#define MD_MIG_VALUE_THRES_VALUE_MASK (UINT64_CAST 0xfffff)
multiline_comment|/* MD_MIG_CANDIDATE bit definitions */
DECL|macro|MD_MIG_CANDIDATE_VALID_MASK
mdefine_line|#define MD_MIG_CANDIDATE_VALID_MASK (UINT64_CAST 0x1 &lt;&lt; 63)
DECL|macro|MD_MIG_CANDIDATE_VALID_SHFT
mdefine_line|#define MD_MIG_CANDIDATE_VALID_SHFT 63
DECL|macro|MD_MIG_CANDIDATE_TYPE_MASK
mdefine_line|#define MD_MIG_CANDIDATE_TYPE_MASK (UINT64_CAST 0x1 &lt;&lt; 30)
DECL|macro|MD_MIG_CANDIDATE_TYPE_SHFT
mdefine_line|#define MD_MIG_CANDIDATE_TYPE_SHFT 30
DECL|macro|MD_MIG_CANDIDATE_OVERRUN_MASK
mdefine_line|#define MD_MIG_CANDIDATE_OVERRUN_MASK (UINT64_CAST 0x1 &lt;&lt; 29)
DECL|macro|MD_MIG_CANDIDATE_OVERRUN_SHFT
mdefine_line|#define MD_MIG_CANDIDATE_OVERRUN_SHFT 29
DECL|macro|MD_MIG_CANDIDATE_INITIATOR_MASK
mdefine_line|#define MD_MIG_CANDIDATE_INITIATOR_MASK (UINT64_CAST 0x7ff &lt;&lt; 18)
DECL|macro|MD_MIG_CANDIDATE_INITIATOR_SHFT
mdefine_line|#define MD_MIG_CANDIDATE_INITIATOR_SHFT 18
DECL|macro|MD_MIG_CANDIDATE_NODEID_MASK
mdefine_line|#define MD_MIG_CANDIDATE_NODEID_MASK (UINT64_CAST 0x1ff &lt;&lt; 20)
DECL|macro|MD_MIG_CANDIDATE_NODEID_SHFT
mdefine_line|#define MD_MIG_CANDIDATE_NODEID_SHFT 20
DECL|macro|MD_MIG_CANDIDATE_ADDR_MASK
mdefine_line|#define MD_MIG_CANDIDATE_ADDR_MASK (UINT64_CAST 0x3ffff)
DECL|macro|MD_MIG_CANDIDATE_ADDR_SHFT
mdefine_line|#define MD_MIG_CANDIDATE_ADDR_SHFT 14  /* The address starts at bit 14 */
multiline_comment|/* Other MD definitions */
DECL|macro|MD_BANK_SHFT
mdefine_line|#define MD_BANK_SHFT&t;&t;29&t;&t;&t;/* log2(512 MB)     */
DECL|macro|MD_BANK_MASK
mdefine_line|#define MD_BANK_MASK&t;&t;(UINT64_CAST 7 &lt;&lt; 29)
DECL|macro|MD_BANK_SIZE
mdefine_line|#define MD_BANK_SIZE&t;&t;(UINT64_CAST 1 &lt;&lt; MD_BANK_SHFT)&t;  /* 512 MB */
DECL|macro|MD_BANK_OFFSET
mdefine_line|#define MD_BANK_OFFSET(_b)&t;(UINT64_CAST (_b) &lt;&lt; MD_BANK_SHFT)
multiline_comment|/*&n; * The following definitions cover the bit field definitions for the&n; * various MD registers.  For multi-bit registers, we define both&n; * a shift amount and a mask value.  By convention, if you want to&n; * isolate a field, you should mask the field and then shift it down,&n; * since this makes the masks useful without a shift.&n; */
multiline_comment|/* Directory entry states for both premium and standard SIMMs. */
DECL|macro|MD_DIR_SHARED
mdefine_line|#define MD_DIR_SHARED&t;&t;(UINT64_CAST 0x0)&t;/* 000 */
DECL|macro|MD_DIR_POISONED
mdefine_line|#define MD_DIR_POISONED&t;&t;(UINT64_CAST 0x1)&t;/* 001 */
DECL|macro|MD_DIR_EXCLUSIVE
mdefine_line|#define MD_DIR_EXCLUSIVE&t;(UINT64_CAST 0x2)&t;/* 010 */
DECL|macro|MD_DIR_BUSY_SHARED
mdefine_line|#define MD_DIR_BUSY_SHARED&t;(UINT64_CAST 0x3)&t;/* 011 */
DECL|macro|MD_DIR_BUSY_EXCL
mdefine_line|#define MD_DIR_BUSY_EXCL&t;(UINT64_CAST 0x4)&t;/* 100 */
DECL|macro|MD_DIR_WAIT
mdefine_line|#define MD_DIR_WAIT&t;&t;(UINT64_CAST 0x5)&t;/* 101 */
DECL|macro|MD_DIR_UNOWNED
mdefine_line|#define MD_DIR_UNOWNED&t;&t;(UINT64_CAST 0x7)&t;/* 111 */
multiline_comment|/*&n; * The MD_DIR_FORCE_ECC bit can be added directory entry write data&n; * to forcing the ECC to be written as-is instead of recalculated.&n; */
DECL|macro|MD_DIR_FORCE_ECC
mdefine_line|#define MD_DIR_FORCE_ECC&t;(UINT64_CAST 1 &lt;&lt; 63)
multiline_comment|/*&n; * Premium SIMM directory entry shifts and masks.  Each is valid only in the&n; * context(s) indicated, where A, B, and C indicate the directory entry format&n; * as shown, and low and/or high indicates which double-word of the entry.&n; *&n; * Format A:  STATE = shared, FINE = 1&n; * Format B:  STATE = shared, FINE = 0&n; * Format C:  STATE != shared (FINE must be 0)&n; */
DECL|macro|MD_PDIR_MASK
mdefine_line|#define MD_PDIR_MASK&t;&t;0xffffffffffff&t;&t;/* Whole entry &t;    */
DECL|macro|MD_PDIR_ECC_SHFT
mdefine_line|#define MD_PDIR_ECC_SHFT&t;0&t;&t;&t;/* ABC low or high  */
DECL|macro|MD_PDIR_ECC_MASK
mdefine_line|#define MD_PDIR_ECC_MASK&t;0x7f
DECL|macro|MD_PDIR_PRIO_SHFT
mdefine_line|#define MD_PDIR_PRIO_SHFT&t;8&t;&t;&t;/* ABC low &t;    */
DECL|macro|MD_PDIR_PRIO_MASK
mdefine_line|#define MD_PDIR_PRIO_MASK&t;(0xf &lt;&lt; 8)
DECL|macro|MD_PDIR_AX_SHFT
mdefine_line|#define MD_PDIR_AX_SHFT&t;&t;7&t;&t;&t;/* ABC low &t;    */
DECL|macro|MD_PDIR_AX_MASK
mdefine_line|#define MD_PDIR_AX_MASK&t;&t;(1 &lt;&lt; 7)
DECL|macro|MD_PDIR_AX
mdefine_line|#define MD_PDIR_AX&t;&t;(1 &lt;&lt; 7)
DECL|macro|MD_PDIR_FINE_SHFT
mdefine_line|#define MD_PDIR_FINE_SHFT&t;12&t;&t;&t;/* ABC low &t;    */
DECL|macro|MD_PDIR_FINE_MASK
mdefine_line|#define MD_PDIR_FINE_MASK&t;(1 &lt;&lt; 12)
DECL|macro|MD_PDIR_FINE
mdefine_line|#define MD_PDIR_FINE&t;&t;(1 &lt;&lt; 12)
DECL|macro|MD_PDIR_OCT_SHFT
mdefine_line|#define MD_PDIR_OCT_SHFT&t;13&t;&t;&t;/* A low &t;    */
DECL|macro|MD_PDIR_OCT_MASK
mdefine_line|#define MD_PDIR_OCT_MASK&t;(7 &lt;&lt; 13)
DECL|macro|MD_PDIR_STATE_SHFT
mdefine_line|#define MD_PDIR_STATE_SHFT&t;13&t;&t;&t;/* BC low &t;    */
DECL|macro|MD_PDIR_STATE_MASK
mdefine_line|#define MD_PDIR_STATE_MASK&t;(7 &lt;&lt; 13)
DECL|macro|MD_PDIR_ONECNT_SHFT
mdefine_line|#define MD_PDIR_ONECNT_SHFT&t;16&t;&t;&t;/* BC low &t;    */
DECL|macro|MD_PDIR_ONECNT_MASK
mdefine_line|#define MD_PDIR_ONECNT_MASK&t;(0x3f &lt;&lt; 16)
DECL|macro|MD_PDIR_PTR_SHFT
mdefine_line|#define MD_PDIR_PTR_SHFT&t;22&t;&t;&t;/* C low &t;    */
DECL|macro|MD_PDIR_PTR_MASK
mdefine_line|#define MD_PDIR_PTR_MASK&t;(UINT64_CAST 0x7ff &lt;&lt; 22)
DECL|macro|MD_PDIR_VECMSB_SHFT
mdefine_line|#define MD_PDIR_VECMSB_SHFT&t;22&t;&t;&t;/* AB low &t;    */
DECL|macro|MD_PDIR_VECMSB_BITMASK
mdefine_line|#define MD_PDIR_VECMSB_BITMASK&t;0x3ffffff
DECL|macro|MD_PDIR_VECMSB_BITSHFT
mdefine_line|#define MD_PDIR_VECMSB_BITSHFT&t;27
DECL|macro|MD_PDIR_VECMSB_MASK
mdefine_line|#define MD_PDIR_VECMSB_MASK&t;(UINT64_CAST MD_PDIR_VECMSB_BITMASK &lt;&lt; 22)
DECL|macro|MD_PDIR_CWOFF_SHFT
mdefine_line|#define MD_PDIR_CWOFF_SHFT&t;7&t;&t;&t;/* C high &t;    */
DECL|macro|MD_PDIR_CWOFF_MASK
mdefine_line|#define MD_PDIR_CWOFF_MASK&t;(7 &lt;&lt; 7)
DECL|macro|MD_PDIR_VECLSB_SHFT
mdefine_line|#define MD_PDIR_VECLSB_SHFT&t;10&t;&t;&t;/* AB high &t;    */
DECL|macro|MD_PDIR_VECLSB_BITMASK
mdefine_line|#define MD_PDIR_VECLSB_BITMASK&t;(UINT64_CAST 0x3fffffffff)
DECL|macro|MD_PDIR_VECLSB_BITSHFT
mdefine_line|#define MD_PDIR_VECLSB_BITSHFT&t;0
DECL|macro|MD_PDIR_VECLSB_MASK
mdefine_line|#define MD_PDIR_VECLSB_MASK&t;(MD_PDIR_VECLSB_BITMASK &lt;&lt; 10)
multiline_comment|/*&n; * Directory initialization values&n; */
DECL|macro|MD_PDIR_INIT_LO
mdefine_line|#define MD_PDIR_INIT_LO&t;&t;(MD_DIR_UNOWNED &lt;&lt; MD_PDIR_STATE_SHFT | &bslash;&n;&t;&t;&t;&t; MD_PDIR_AX)
DECL|macro|MD_PDIR_INIT_HI
mdefine_line|#define MD_PDIR_INIT_HI&t;&t;0
DECL|macro|MD_PDIR_INIT_PROT
mdefine_line|#define MD_PDIR_INIT_PROT&t;(MD_PROT_RW &lt;&lt; MD_PPROT_IO_SHFT | &bslash;&n;&t;&t;&t;&t; MD_PROT_RW &lt;&lt; MD_PPROT_SHFT)
multiline_comment|/*&n; * Standard SIMM directory entry shifts and masks.  Each is valid only in the&n; * context(s) indicated, where A and C indicate the directory entry format&n; * as shown, and low and/or high indicates which double-word of the entry.&n; *&n; * Format A:  STATE == shared&n; * Format C:  STATE != shared&n; */
DECL|macro|MD_SDIR_MASK
mdefine_line|#define MD_SDIR_MASK&t;&t;0xffff&t;&t;&t;/* Whole entry &t;    */
DECL|macro|MD_SDIR_ECC_SHFT
mdefine_line|#define MD_SDIR_ECC_SHFT&t;0&t;&t;&t;/* AC low or high   */
DECL|macro|MD_SDIR_ECC_MASK
mdefine_line|#define MD_SDIR_ECC_MASK&t;0x1f
DECL|macro|MD_SDIR_PRIO_SHFT
mdefine_line|#define MD_SDIR_PRIO_SHFT&t;6&t;&t;&t;/* AC low &t;    */
DECL|macro|MD_SDIR_PRIO_MASK
mdefine_line|#define MD_SDIR_PRIO_MASK&t;(1 &lt;&lt; 6)
DECL|macro|MD_SDIR_AX_SHFT
mdefine_line|#define MD_SDIR_AX_SHFT&t;&t;5&t;&t;&t;/* AC low &t;    */
DECL|macro|MD_SDIR_AX_MASK
mdefine_line|#define MD_SDIR_AX_MASK&t;&t;(1 &lt;&lt; 5)
DECL|macro|MD_SDIR_AX
mdefine_line|#define MD_SDIR_AX&t;&t;(1 &lt;&lt; 5)
DECL|macro|MD_SDIR_STATE_SHFT
mdefine_line|#define MD_SDIR_STATE_SHFT&t;7&t;&t;&t;/* AC low &t;    */
DECL|macro|MD_SDIR_STATE_MASK
mdefine_line|#define MD_SDIR_STATE_MASK&t;(7 &lt;&lt; 7)
DECL|macro|MD_SDIR_PTR_SHFT
mdefine_line|#define MD_SDIR_PTR_SHFT&t;10&t;&t;&t;/* C low &t;    */
DECL|macro|MD_SDIR_PTR_MASK
mdefine_line|#define MD_SDIR_PTR_MASK&t;(0x3f &lt;&lt; 10)
DECL|macro|MD_SDIR_CWOFF_SHFT
mdefine_line|#define MD_SDIR_CWOFF_SHFT&t;5&t;&t;&t;/* C high &t;    */
DECL|macro|MD_SDIR_CWOFF_MASK
mdefine_line|#define MD_SDIR_CWOFF_MASK&t;(7 &lt;&lt; 5)
DECL|macro|MD_SDIR_VECMSB_SHFT
mdefine_line|#define MD_SDIR_VECMSB_SHFT&t;11&t;&t;&t;/* A low &t;    */
DECL|macro|MD_SDIR_VECMSB_BITMASK
mdefine_line|#define MD_SDIR_VECMSB_BITMASK&t;0x1f
DECL|macro|MD_SDIR_VECMSB_BITSHFT
mdefine_line|#define MD_SDIR_VECMSB_BITSHFT&t;7
DECL|macro|MD_SDIR_VECMSB_MASK
mdefine_line|#define MD_SDIR_VECMSB_MASK&t;(MD_SDIR_VECMSB_BITMASK &lt;&lt; 11)
DECL|macro|MD_SDIR_VECLSB_SHFT
mdefine_line|#define MD_SDIR_VECLSB_SHFT&t;5&t;&t;&t;/* A high &t;    */
DECL|macro|MD_SDIR_VECLSB_BITMASK
mdefine_line|#define MD_SDIR_VECLSB_BITMASK&t;0x7ff
DECL|macro|MD_SDIR_VECLSB_BITSHFT
mdefine_line|#define MD_SDIR_VECLSB_BITSHFT&t;0
DECL|macro|MD_SDIR_VECLSB_MASK
mdefine_line|#define MD_SDIR_VECLSB_MASK&t;(MD_SDIR_VECLSB_BITMASK &lt;&lt; 5)
multiline_comment|/*&n; * Directory initialization values&n; */
DECL|macro|MD_SDIR_INIT_LO
mdefine_line|#define MD_SDIR_INIT_LO&t;&t;(MD_DIR_UNOWNED &lt;&lt; MD_SDIR_STATE_SHFT | &bslash;&n;&t;&t;&t;&t; MD_SDIR_AX)
DECL|macro|MD_SDIR_INIT_HI
mdefine_line|#define MD_SDIR_INIT_HI&t;&t;0
DECL|macro|MD_SDIR_INIT_PROT
mdefine_line|#define MD_SDIR_INIT_PROT&t;(MD_PROT_RW &lt;&lt; MD_SPROT_SHFT)
multiline_comment|/* Protection and migration field values */
DECL|macro|MD_PROT_RW
mdefine_line|#define MD_PROT_RW&t;&t;(UINT64_CAST 0x6)
DECL|macro|MD_PROT_RO
mdefine_line|#define MD_PROT_RO&t;&t;(UINT64_CAST 0x3)
DECL|macro|MD_PROT_NO
mdefine_line|#define MD_PROT_NO&t;&t;(UINT64_CAST 0x0)
DECL|macro|MD_PROT_BAD
mdefine_line|#define MD_PROT_BAD&t;&t;(UINT64_CAST 0x5)
multiline_comment|/* Premium SIMM protection entry shifts and masks. */
DECL|macro|MD_PPROT_SHFT
mdefine_line|#define MD_PPROT_SHFT&t;&t;0&t;&t;&t;/* Prot. field &t;    */
DECL|macro|MD_PPROT_MASK
mdefine_line|#define MD_PPROT_MASK&t;&t;7
DECL|macro|MD_PPROT_MIGMD_SHFT
mdefine_line|#define MD_PPROT_MIGMD_SHFT&t;3&t;&t;&t;/* Migration mode   */
DECL|macro|MD_PPROT_MIGMD_MASK
mdefine_line|#define MD_PPROT_MIGMD_MASK&t;(3 &lt;&lt; 3)
DECL|macro|MD_PPROT_REFCNT_SHFT
mdefine_line|#define MD_PPROT_REFCNT_SHFT&t;5&t;&t;&t;/* Reference count  */
DECL|macro|MD_PPROT_REFCNT_WIDTH
mdefine_line|#define MD_PPROT_REFCNT_WIDTH&t;0x7ffff
DECL|macro|MD_PPROT_REFCNT_MASK
mdefine_line|#define MD_PPROT_REFCNT_MASK&t;(MD_PPROT_REFCNT_WIDTH &lt;&lt; 5)
DECL|macro|MD_PPROT_IO_SHFT
mdefine_line|#define MD_PPROT_IO_SHFT&t;45&t;&t;&t;/* I/O Prot field   */
DECL|macro|MD_PPROT_IO_MASK
mdefine_line|#define MD_PPROT_IO_MASK&t;(UINT64_CAST 7 &lt;&lt; 45)
multiline_comment|/* Standard SIMM protection entry shifts and masks. */
DECL|macro|MD_SPROT_SHFT
mdefine_line|#define MD_SPROT_SHFT&t;&t;0&t;&t;&t;/* Prot. field &t;    */
DECL|macro|MD_SPROT_MASK
mdefine_line|#define MD_SPROT_MASK&t;&t;7
DECL|macro|MD_SPROT_MIGMD_SHFT
mdefine_line|#define MD_SPROT_MIGMD_SHFT&t;3&t;&t;&t;/* Migration mode   */
DECL|macro|MD_SPROT_MIGMD_MASK
mdefine_line|#define MD_SPROT_MIGMD_MASK&t;(3 &lt;&lt; 3)
DECL|macro|MD_SPROT_REFCNT_SHFT
mdefine_line|#define MD_SPROT_REFCNT_SHFT&t;5&t;&t;&t;/* Reference count  */
DECL|macro|MD_SPROT_REFCNT_WIDTH
mdefine_line|#define MD_SPROT_REFCNT_WIDTH&t;0x7ff
DECL|macro|MD_SPROT_REFCNT_MASK
mdefine_line|#define MD_SPROT_REFCNT_MASK&t;(MD_SPROT_REFCNT_WIDTH &lt;&lt; 5)
multiline_comment|/* Migration modes used in protection entries */
DECL|macro|MD_PROT_MIGMD_IREL
mdefine_line|#define MD_PROT_MIGMD_IREL&t;(UINT64_CAST 0x3 &lt;&lt; 3)
DECL|macro|MD_PROT_MIGMD_IABS
mdefine_line|#define MD_PROT_MIGMD_IABS&t;(UINT64_CAST 0x2 &lt;&lt; 3)
DECL|macro|MD_PROT_MIGMD_PREL
mdefine_line|#define MD_PROT_MIGMD_PREL&t;(UINT64_CAST 0x1 &lt;&lt; 3)
DECL|macro|MD_PROT_MIGMD_OFF
mdefine_line|#define MD_PROT_MIGMD_OFF&t;(UINT64_CAST 0x0 &lt;&lt; 3)
multiline_comment|/*&n; * Operations on page migration threshold register&n; */
macro_line|#if _LANGUAGE_C
macro_line|#ifndef _STANDALONE
multiline_comment|/*&n; * LED register macros&n; */
DECL|macro|CPU_LED_ADDR
mdefine_line|#define CPU_LED_ADDR(_nasid, _slice)&t;&t;&t;&t;&t;   &bslash;&n;&t;(private.p_sn00 ?&t;&t;&t;&t;&t;&t;   &bslash;&n;&t; REMOTE_HUB_ADDR((_nasid), MD_UREG1_0 +&t;((_slice) &lt;&lt; 5)) :&t;   &bslash;&n;&t; REMOTE_HUB_ADDR((_nasid), MD_LED0    + ((_slice) &lt;&lt; 3)))
DECL|macro|SET_CPU_LEDS
mdefine_line|#define SET_CPU_LEDS(_nasid, _slice,  _val)&t;&t;&t;&t;   &bslash;&n;&t;(HUB_S(CPU_LED_ADDR(_nasid, _slice), (_val)))
DECL|macro|SET_MY_LEDS
mdefine_line|#define SET_MY_LEDS(_v) &t;&t;&t;&t;&t;&t;   &bslash;&n;&t;SET_CPU_LEDS(get_nasid(), get_slice(), (_v))
multiline_comment|/*&n; * Operations on Memory/Directory DIMM control register&n; */
DECL|macro|DIRTYPE_PREMIUM
mdefine_line|#define DIRTYPE_PREMIUM 1
DECL|macro|DIRTYPE_STANDARD
mdefine_line|#define DIRTYPE_STANDARD 0
DECL|macro|MD_MEMORY_CONFIG_DIR_TYPE_GET
mdefine_line|#define MD_MEMORY_CONFIG_DIR_TYPE_GET(region) (&bslash;&n;&t;(REMOTE_HUB_L(region, MD_MEMORY_CONFIG) &amp; MMC_DIR_PREMIUM_MASK) &gt;&gt; &bslash;&n;&t;MMC_DIR_PREMIUM_SHFT)
multiline_comment|/*&n; * Operations on page migration count difference and absolute threshold&n; * registers&n; */
DECL|macro|MD_MIG_DIFF_THRESH_GET
mdefine_line|#define MD_MIG_DIFF_THRESH_GET(region) ( &bslash;&n;&t;REMOTE_HUB_L((region), MD_MIG_DIFF_THRESH) &amp; &bslash;&n;&t;MD_MIG_DIFF_THRES_VALUE_MASK)
DECL|macro|MD_MIG_DIFF_THRESH_SET
mdefine_line|#define MD_MIG_DIFF_THRESH_SET(region, value) (&t;&t;&t;&t;&bslash;&n;&t;REMOTE_HUB_S((region), MD_MIG_DIFF_THRESH,&t;&t;&t;&bslash;&n;&t;&t;MD_MIG_DIFF_THRES_VALID_MASK | (value)))
DECL|macro|MD_MIG_DIFF_THRESH_DISABLE
mdefine_line|#define MD_MIG_DIFF_THRESH_DISABLE(region) (&t;&t;&t;&bslash;&n;&t;REMOTE_HUB_S((region), MD_MIG_DIFF_THRESH,&t;&t;&t;&bslash;&n;&t;&t;REMOTE_HUB_L((region), MD_MIG_DIFF_THRESH)&t;&t;&bslash;&n;&t;&t;&t;     &amp; ~MD_MIG_DIFF_THRES_VALID_MASK))
DECL|macro|MD_MIG_DIFF_THRESH_ENABLE
mdefine_line|#define MD_MIG_DIFF_THRESH_ENABLE(region) (&t;&t;&t;&bslash;&n;&t;REMOTE_HUB_S((region), MD_MIG_DIFF_THRESH,&t;&t;&t;&bslash;&n;&t;&t;REMOTE_HUB_L((region), MD_MIG_DIFF_THRESH)&t;&t;&bslash;&n;&t;&t;&t;     | MD_MIG_DIFF_THRES_VALID_MASK))
DECL|macro|MD_MIG_DIFF_THRESH_IS_ENABLED
mdefine_line|#define MD_MIG_DIFF_THRESH_IS_ENABLED(region) (&t;&t;&t;&t;&bslash;&n;&t;REMOTE_HUB_L((region), MD_MIG_DIFF_THRESH) &amp;&t;&t;&t;&bslash;&n;&t;       MD_MIG_DIFF_THRES_VALID_MASK)
DECL|macro|MD_MIG_VALUE_THRESH_GET
mdefine_line|#define MD_MIG_VALUE_THRESH_GET(region) (&t;&t;&t;&t;&bslash;&n;&t;REMOTE_HUB_L((region), MD_MIG_VALUE_THRESH) &amp;  &bslash;&n;&t;MD_MIG_VALUE_THRES_VALUE_MASK)
DECL|macro|MD_MIG_VALUE_THRESH_SET
mdefine_line|#define MD_MIG_VALUE_THRESH_SET(region, value) (&t;&t;&t;&bslash;&n;&t;REMOTE_HUB_S((region), MD_MIG_VALUE_THRESH,&t;&t;&t;&bslash;&n;&t;&t;MD_MIG_VALUE_THRES_VALID_MASK | (value)))
DECL|macro|MD_MIG_VALUE_THRESH_DISABLE
mdefine_line|#define MD_MIG_VALUE_THRESH_DISABLE(region) (&t;&t;&t;&bslash;&n;&t;REMOTE_HUB_S((region), MD_MIG_VALUE_THRESH,&t;&t;&t;&bslash;&n;&t;&t;REMOTE_HUB_L(region, MD_MIG_VALUE_THRESH)&t;&t;&bslash;&n;&t;&t;&t;     &amp; ~MD_MIG_VALUE_THRES_VALID_MASK))
DECL|macro|MD_MIG_VALUE_THRESH_ENABLE
mdefine_line|#define MD_MIG_VALUE_THRESH_ENABLE(region) (&t;&t;&t;&bslash;&n;&t;REMOTE_HUB_S((region), MD_MIG_VALUE_THRESH,&t;&t;&t;&bslash;&n;&t;&t;REMOTE_HUB_L((region), MD_MIG_VALUE_THRESH)&t;&t;&bslash;&n;&t;&t;&t;     | MD_MIG_VALUE_THRES_VALID_MASK))
DECL|macro|MD_MIG_VALUE_THRESH_IS_ENABLED
mdefine_line|#define MD_MIG_VALUE_THRESH_IS_ENABLED(region) (&t;&t;&t;&bslash;&n;&t;REMOTE_HUB_L((region), MD_MIG_VALUE_THRESH) &amp;&t;&t;&t; &bslash;&n;&t;       MD_MIG_VALUE_THRES_VALID_MASK)
multiline_comment|/*&n; * Operations on page migration candidate register&n; */
DECL|macro|MD_MIG_CANDIDATE_GET
mdefine_line|#define MD_MIG_CANDIDATE_GET(my_region_id) ( &bslash;&n;&t;REMOTE_HUB_L((my_region_id), MD_MIG_CANDIDATE_CLR))
DECL|macro|MD_MIG_CANDIDATE_HWPFN
mdefine_line|#define MD_MIG_CANDIDATE_HWPFN(value) ((value) &amp; MD_MIG_CANDIDATE_ADDR_MASK)
DECL|macro|MD_MIG_CANDIDATE_NODEID
mdefine_line|#define MD_MIG_CANDIDATE_NODEID(value) ( &bslash;&n;&t;((value) &amp; MD_MIG_CANDIDATE_NODEID_MASK) &gt;&gt; MD_MIG_CANDIDATE_NODEID_SHFT)
DECL|macro|MD_MIG_CANDIDATE_TYPE
mdefine_line|#define MD_MIG_CANDIDATE_TYPE(value) ( &bslash;&n;&t;((value) &amp; MD_MIG_CANDIDATE_TYPE_MASK) &gt;&gt; MD_MIG_CANDIDATE_TYPE_SHFT)
DECL|macro|MD_MIG_CANDIDATE_VALID
mdefine_line|#define MD_MIG_CANDIDATE_VALID(value) ( &bslash;&n;&t;((value) &amp; MD_MIG_CANDIDATE_VALID_MASK) &gt;&gt; MD_MIG_CANDIDATE_VALID_SHFT)
multiline_comment|/*&n; * Macros to retrieve fields in the protection entry&n; */
multiline_comment|/* for Premium SIMM */
DECL|macro|MD_PPROT_REFCNT_GET
mdefine_line|#define MD_PPROT_REFCNT_GET(value) ( &bslash;&n;&t;((value) &amp; MD_PPROT_REFCNT_MASK) &gt;&gt; MD_PPROT_REFCNT_SHFT)
DECL|macro|MD_PPROT_MIGMD_GET
mdefine_line|#define MD_PPROT_MIGMD_GET(value) ( &bslash;&n;&t;((value) &amp; MD_PPROT_MIGMD_MASK) &gt;&gt; MD_PPROT_MIGMD_SHFT)
multiline_comment|/* for Standard SIMM */
DECL|macro|MD_SPROT_REFCNT_GET
mdefine_line|#define MD_SPROT_REFCNT_GET(value) ( &bslash;&n;&t;((value) &amp; MD_SPROT_REFCNT_MASK) &gt;&gt; MD_SPROT_REFCNT_SHFT)
DECL|macro|MD_SPROT_MIGMD_GET
mdefine_line|#define MD_SPROT_MIGMD_GET(value) ( &bslash;&n;&t;((value) &amp; MD_SPROT_MIGMD_MASK) &gt;&gt; MD_SPROT_MIGMD_SHFT)
macro_line|#endif /* _STANDALONE */
multiline_comment|/*&n; * Format of dir_error, mem_error, protocol_error and misc_error registers&n; */
DECL|struct|dir_error_reg
r_struct
id|dir_error_reg
(brace
DECL|member|uce_vld
id|u64
id|uce_vld
suffix:colon
l_int|1
comma
multiline_comment|/*    63: valid directory uce &t;*/
DECL|member|ae_vld
id|ae_vld
suffix:colon
l_int|1
comma
multiline_comment|/*    62: valid dir prot ecc error */
DECL|member|ce_vld
id|ce_vld
suffix:colon
l_int|1
comma
multiline_comment|/*    61: valid correctable ECC err*/
DECL|member|rsvd1
id|rsvd1
suffix:colon
l_int|19
comma
multiline_comment|/* 60-42: reserved&t;&t;*/
DECL|member|bad_prot
id|bad_prot
suffix:colon
l_int|3
comma
multiline_comment|/* 41-39: encoding, bad access rights*/
DECL|member|bad_syn
id|bad_syn
suffix:colon
l_int|7
comma
multiline_comment|/* 38-32: bad dir syndrome&t;*/
DECL|member|rsvd2
id|rsvd2
suffix:colon
l_int|2
comma
multiline_comment|/* 31-30: reserved&t;&t;*/
DECL|member|hspec_addr
id|hspec_addr
suffix:colon
l_int|27
comma
multiline_comment|/* 29-03: bddir space bad entry */
DECL|member|uce_ovr
id|uce_ovr
suffix:colon
l_int|1
comma
multiline_comment|/*     2: multiple dir uce&squot;s&t;*/
DECL|member|ae_ovr
id|ae_ovr
suffix:colon
l_int|1
comma
multiline_comment|/*     1: multiple prot ecc errs*/
DECL|member|ce_ovr
id|ce_ovr
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/*     0: multiple correctable errs */
)brace
suffix:semicolon
DECL|union|md_dir_error
r_typedef
r_union
id|md_dir_error
(brace
DECL|member|derr_reg
id|u64
id|derr_reg
suffix:semicolon
multiline_comment|/* the entire register &t;&t;*/
DECL|member|derr_fmt
r_struct
id|dir_error_reg
id|derr_fmt
suffix:semicolon
multiline_comment|/* the register format&t;&t;*/
DECL|typedef|md_dir_error_t
)brace
id|md_dir_error_t
suffix:semicolon
DECL|struct|mem_error_reg
r_struct
id|mem_error_reg
(brace
DECL|member|uce_vld
id|u64
id|uce_vld
suffix:colon
l_int|1
comma
multiline_comment|/*    63: valid memory uce &t;*/
DECL|member|ce_vld
id|ce_vld
suffix:colon
l_int|1
comma
multiline_comment|/*    62: valid correctable ECC err*/
DECL|member|rsvd1
id|rsvd1
suffix:colon
l_int|22
comma
multiline_comment|/* 61-40: reserved&t;&t;*/
DECL|member|bad_syn
id|bad_syn
suffix:colon
l_int|8
comma
multiline_comment|/* 39-32: bad mem ecc syndrome&t;*/
DECL|member|address
id|address
suffix:colon
l_int|29
comma
multiline_comment|/* 31-03: bad entry pointer&t;*/
DECL|member|rsvd2
id|rsvd2
suffix:colon
l_int|1
comma
multiline_comment|/*     2: reserved&t;&t;*/
DECL|member|uce_ovr
id|uce_ovr
suffix:colon
l_int|1
comma
multiline_comment|/*     1: multiple mem uce&squot;s&t;*/
DECL|member|ce_ovr
id|ce_ovr
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/*     0: multiple correctable errs */
)brace
suffix:semicolon
DECL|union|md_mem_error
r_typedef
r_union
id|md_mem_error
(brace
DECL|member|merr_reg
id|u64
id|merr_reg
suffix:semicolon
multiline_comment|/* the entire register &t;&t;*/
DECL|member|merr_fmt
r_struct
id|mem_error_reg
id|merr_fmt
suffix:semicolon
multiline_comment|/* format of the mem_error reg  */
DECL|typedef|md_mem_error_t
)brace
id|md_mem_error_t
suffix:semicolon
DECL|struct|proto_error_reg
r_struct
id|proto_error_reg
(brace
DECL|member|valid
id|u64
id|valid
suffix:colon
l_int|1
comma
multiline_comment|/*    63: valid protocol error&t;*/
DECL|member|rsvd1
id|rsvd1
suffix:colon
l_int|2
comma
multiline_comment|/* 62-61: reserved&t;&t;*/
DECL|member|initiator
id|initiator
suffix:colon
l_int|11
comma
multiline_comment|/* 60-50: id of request initiator*/
DECL|member|backoff
id|backoff
suffix:colon
l_int|2
comma
multiline_comment|/* 49-48: backoff control&t;*/
DECL|member|msg_type
id|msg_type
suffix:colon
l_int|8
comma
multiline_comment|/* 47-40: type of request&t;*/
DECL|member|access
id|access
suffix:colon
l_int|2
comma
multiline_comment|/* 39-38: access rights of initiator*/
DECL|member|priority
id|priority
suffix:colon
l_int|1
comma
multiline_comment|/*    37: priority level of requestor*/
DECL|member|dir_state
id|dir_state
suffix:colon
l_int|4
comma
multiline_comment|/* 36-33: state of directory&t;*/
DECL|member|pointer_me
id|pointer_me
suffix:colon
l_int|1
comma
multiline_comment|/*    32: initiator same as dir ptr */
DECL|member|address
id|address
suffix:colon
l_int|29
comma
multiline_comment|/* 31-03: request address&t;*/
DECL|member|rsvd2
id|rsvd2
suffix:colon
l_int|2
comma
multiline_comment|/* 02-01: reserved&t;&t;*/
DECL|member|overrun
id|overrun
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/*     0: multiple protocol errs */
)brace
suffix:semicolon
DECL|union|md_proto_error
r_typedef
r_union
id|md_proto_error
(brace
DECL|member|perr_reg
id|u64
id|perr_reg
suffix:semicolon
multiline_comment|/* the entire register &t;&t;*/
DECL|member|perr_fmt
r_struct
id|proto_error_reg
id|perr_fmt
suffix:semicolon
multiline_comment|/* format of the register&t;*/
DECL|typedef|md_proto_error_t
)brace
id|md_proto_error_t
suffix:semicolon
DECL|struct|md_sdir_high_fmt
r_struct
id|md_sdir_high_fmt
(brace
DECL|member|sd_hi_bvec
r_int
r_int
id|sd_hi_bvec
suffix:colon
l_int|11
comma
DECL|member|sd_hi_ecc
id|sd_hi_ecc
suffix:colon
l_int|5
suffix:semicolon
)brace
suffix:semicolon
DECL|union|md_sdir_high
r_typedef
r_union
id|md_sdir_high
(brace
multiline_comment|/* The 16 bits of standard directory, upper word */
DECL|member|sd_hi_val
r_int
r_int
id|sd_hi_val
suffix:semicolon
DECL|member|sd_hi_fmt
r_struct
id|md_sdir_high_fmt
id|sd_hi_fmt
suffix:semicolon
DECL|typedef|md_sdir_high_t
)brace
id|md_sdir_high_t
suffix:semicolon
DECL|struct|md_sdir_low_shared_fmt
r_struct
id|md_sdir_low_shared_fmt
(brace
multiline_comment|/* The meaning of lower directory, shared */
DECL|member|sds_lo_bvec
r_int
r_int
id|sds_lo_bvec
suffix:colon
l_int|5
comma
DECL|member|sds_lo_unused
id|sds_lo_unused
suffix:colon
l_int|1
comma
DECL|member|sds_lo_state
id|sds_lo_state
suffix:colon
l_int|3
comma
DECL|member|sds_lo_prio
id|sds_lo_prio
suffix:colon
l_int|1
comma
DECL|member|sds_lo_ax
id|sds_lo_ax
suffix:colon
l_int|1
comma
DECL|member|sds_lo_ecc
id|sds_lo_ecc
suffix:colon
l_int|5
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|md_sdir_low_exclusive_fmt
r_struct
id|md_sdir_low_exclusive_fmt
(brace
multiline_comment|/* The meaning of lower directory, exclusive */
DECL|member|sde_lo_ptr
r_int
r_int
id|sde_lo_ptr
suffix:colon
l_int|6
comma
DECL|member|sde_lo_state
id|sde_lo_state
suffix:colon
l_int|3
comma
DECL|member|sde_lo_prio
id|sde_lo_prio
suffix:colon
l_int|1
comma
DECL|member|sde_lo_ax
id|sde_lo_ax
suffix:colon
l_int|1
comma
DECL|member|sde_lo_ecc
id|sde_lo_ecc
suffix:colon
l_int|5
suffix:semicolon
)brace
suffix:semicolon
DECL|union|md_sdir_low
r_typedef
r_union
id|md_sdir_low
(brace
multiline_comment|/* The 16 bits of standard directory, lower word */
DECL|member|sd_lo_val
r_int
r_int
id|sd_lo_val
suffix:semicolon
DECL|member|sde_lo_fmt
r_struct
id|md_sdir_low_exclusive_fmt
id|sde_lo_fmt
suffix:semicolon
DECL|member|sds_lo_fmt
r_struct
id|md_sdir_low_shared_fmt
id|sds_lo_fmt
suffix:semicolon
DECL|typedef|md_sdir_low_t
)brace
id|md_sdir_low_t
suffix:semicolon
DECL|struct|md_pdir_high_fmt
r_struct
id|md_pdir_high_fmt
(brace
DECL|member|pd_hi_unused
id|u64
id|pd_hi_unused
suffix:colon
l_int|16
comma
DECL|member|pd_hi_bvec
id|pd_hi_bvec
suffix:colon
l_int|38
comma
DECL|member|pd_hi_unused1
id|pd_hi_unused1
suffix:colon
l_int|3
comma
DECL|member|pd_hi_ecc
id|pd_hi_ecc
suffix:colon
l_int|7
suffix:semicolon
)brace
suffix:semicolon
DECL|union|md_pdir_high
r_typedef
r_union
id|md_pdir_high
(brace
multiline_comment|/* The 48 bits of standard directory, upper word */
DECL|member|pd_hi_val
id|u64
id|pd_hi_val
suffix:semicolon
DECL|member|pd_hi_fmt
r_struct
id|md_pdir_high_fmt
id|pd_hi_fmt
suffix:semicolon
DECL|typedef|md_pdir_high_t
)brace
id|md_pdir_high_t
suffix:semicolon
DECL|struct|md_pdir_low_shared_fmt
r_struct
id|md_pdir_low_shared_fmt
(brace
multiline_comment|/* The meaning of lower directory, shared */
DECL|member|pds_lo_unused
id|u64
id|pds_lo_unused
suffix:colon
l_int|16
comma
DECL|member|pds_lo_bvec
id|pds_lo_bvec
suffix:colon
l_int|26
comma
DECL|member|pds_lo_cnt
id|pds_lo_cnt
suffix:colon
l_int|6
comma
DECL|member|pds_lo_state
id|pds_lo_state
suffix:colon
l_int|3
comma
DECL|member|pds_lo_ste
id|pds_lo_ste
suffix:colon
l_int|1
comma
DECL|member|pds_lo_prio
id|pds_lo_prio
suffix:colon
l_int|4
comma
DECL|member|pds_lo_ax
id|pds_lo_ax
suffix:colon
l_int|1
comma
DECL|member|pds_lo_ecc
id|pds_lo_ecc
suffix:colon
l_int|7
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|md_pdir_low_exclusive_fmt
r_struct
id|md_pdir_low_exclusive_fmt
(brace
multiline_comment|/* The meaning of lower directory, exclusive */
DECL|member|pde_lo_unused
id|u64
id|pde_lo_unused
suffix:colon
l_int|31
comma
DECL|member|pde_lo_ptr
id|pde_lo_ptr
suffix:colon
l_int|11
comma
DECL|member|pde_lo_unused1
id|pde_lo_unused1
suffix:colon
l_int|6
comma
DECL|member|pde_lo_state
id|pde_lo_state
suffix:colon
l_int|3
comma
DECL|member|pde_lo_ste
id|pde_lo_ste
suffix:colon
l_int|1
comma
DECL|member|pde_lo_prio
id|pde_lo_prio
suffix:colon
l_int|4
comma
DECL|member|pde_lo_ax
id|pde_lo_ax
suffix:colon
l_int|1
comma
DECL|member|pde_lo_ecc
id|pde_lo_ecc
suffix:colon
l_int|7
suffix:semicolon
)brace
suffix:semicolon
DECL|union|md_pdir_loent
r_typedef
r_union
id|md_pdir_loent
(brace
multiline_comment|/* The 48 bits of premium directory, lower word */
DECL|member|pd_lo_val
id|u64
id|pd_lo_val
suffix:semicolon
DECL|member|pde_lo_fmt
r_struct
id|md_pdir_low_exclusive_fmt
id|pde_lo_fmt
suffix:semicolon
DECL|member|pds_lo_fmt
r_struct
id|md_pdir_low_shared_fmt
id|pds_lo_fmt
suffix:semicolon
DECL|typedef|md_pdir_low_t
)brace
id|md_pdir_low_t
suffix:semicolon
multiline_comment|/*&n; *   the following two &quot;union&quot; definitions and two&n; *   &quot;struct&quot; definitions are used in vmdump.c to&n; *   represent directory memory information.&n; */
DECL|union|md_dir_high
r_typedef
r_union
id|md_dir_high
(brace
DECL|member|md_sdir_high
id|md_sdir_high_t
id|md_sdir_high
suffix:semicolon
DECL|member|md_pdir_high
id|md_pdir_high_t
id|md_pdir_high
suffix:semicolon
DECL|typedef|md_dir_high_t
)brace
id|md_dir_high_t
suffix:semicolon
DECL|union|md_dir_low
r_typedef
r_union
id|md_dir_low
(brace
DECL|member|md_sdir_low
id|md_sdir_low_t
id|md_sdir_low
suffix:semicolon
DECL|member|md_pdir_low
id|md_pdir_low_t
id|md_pdir_low
suffix:semicolon
DECL|typedef|md_dir_low_t
)brace
id|md_dir_low_t
suffix:semicolon
DECL|struct|bddir_entry
r_typedef
r_struct
id|bddir_entry
(brace
DECL|member|md_dir_low
id|md_dir_low_t
id|md_dir_low
suffix:semicolon
DECL|member|md_dir_high
id|md_dir_high_t
id|md_dir_high
suffix:semicolon
DECL|typedef|bddir_entry_t
)brace
id|bddir_entry_t
suffix:semicolon
DECL|struct|dir_mem_entry
r_typedef
r_struct
id|dir_mem_entry
(brace
DECL|member|prcpf
id|u64
id|prcpf
(braket
id|MAX_REGIONS
)braket
suffix:semicolon
DECL|member|directory_words
id|bddir_entry_t
id|directory_words
(braket
id|MD_PAGE_SIZE
op_div
id|CACHE_SLINE_SIZE
)braket
suffix:semicolon
DECL|typedef|dir_mem_entry_t
)brace
id|dir_mem_entry_t
suffix:semicolon
DECL|union|md_perf_sel
r_typedef
r_union
id|md_perf_sel
(brace
DECL|member|perf_sel_reg
id|u64
id|perf_sel_reg
suffix:semicolon
r_struct
(brace
DECL|member|perf_rsvd
id|u64
id|perf_rsvd
suffix:colon
l_int|60
comma
DECL|member|perf_en
id|perf_en
suffix:colon
l_int|1
comma
DECL|member|perf_sel
id|perf_sel
suffix:colon
l_int|3
suffix:semicolon
DECL|member|perf_sel_bits
)brace
id|perf_sel_bits
suffix:semicolon
DECL|typedef|md_perf_sel_t
)brace
id|md_perf_sel_t
suffix:semicolon
DECL|union|md_perf_cnt
r_typedef
r_union
id|md_perf_cnt
(brace
DECL|member|perf_cnt
id|u64
id|perf_cnt
suffix:semicolon
r_struct
(brace
DECL|member|perf_rsvd
id|u64
id|perf_rsvd
suffix:colon
l_int|44
comma
DECL|member|perf_cnt
id|perf_cnt
suffix:colon
l_int|20
suffix:semicolon
DECL|member|perf_cnt_bits
)brace
id|perf_cnt_bits
suffix:semicolon
DECL|typedef|md_perf_cnt_t
)brace
id|md_perf_cnt_t
suffix:semicolon
macro_line|#endif /* _LANGUAGE_C */
DECL|macro|DIR_ERROR_VALID_MASK
mdefine_line|#define DIR_ERROR_VALID_MASK&t;0xe000000000000000
DECL|macro|DIR_ERROR_VALID_SHFT
mdefine_line|#define DIR_ERROR_VALID_SHFT&t;61
DECL|macro|DIR_ERROR_VALID_UCE
mdefine_line|#define DIR_ERROR_VALID_UCE&t;0x8000000000000000
DECL|macro|DIR_ERROR_VALID_AE
mdefine_line|#define DIR_ERROR_VALID_AE&t;0x4000000000000000
DECL|macro|DIR_ERROR_VALID_CE
mdefine_line|#define DIR_ERROR_VALID_CE&t;0x2000000000000000
DECL|macro|MEM_ERROR_VALID_MASK
mdefine_line|#define MEM_ERROR_VALID_MASK&t;0xc000000000000000
DECL|macro|MEM_ERROR_VALID_SHFT
mdefine_line|#define MEM_ERROR_VALID_SHFT&t;62
DECL|macro|MEM_ERROR_VALID_UCE
mdefine_line|#define MEM_ERROR_VALID_UCE&t;0x8000000000000000
DECL|macro|MEM_ERROR_VALID_CE
mdefine_line|#define MEM_ERROR_VALID_CE&t;0x4000000000000000
DECL|macro|PROTO_ERROR_VALID_MASK
mdefine_line|#define PROTO_ERROR_VALID_MASK&t;0x8000000000000000
DECL|macro|MISC_ERROR_VALID_MASK
mdefine_line|#define MISC_ERROR_VALID_MASK&t;0x3ff
multiline_comment|/*&n; * Mask for hspec address that is stored in the dir error register.&n; * This represents bits 29 through 3.&n; */
DECL|macro|DIR_ERR_HSPEC_MASK
mdefine_line|#define DIR_ERR_HSPEC_MASK&t;0x3ffffff8
DECL|macro|ERROR_HSPEC_MASK
mdefine_line|#define ERROR_HSPEC_MASK&t;0x3ffffff8
DECL|macro|ERROR_HSPEC_SHFT
mdefine_line|#define ERROR_HSPEC_SHFT&t;3
DECL|macro|ERROR_ADDR_MASK
mdefine_line|#define ERROR_ADDR_MASK&t;&t;0xfffffff8
DECL|macro|ERROR_ADDR_SHFT
mdefine_line|#define ERROR_ADDR_SHFT&t;&t;3
multiline_comment|/*&n; * MD_MISC_ERROR register defines.&n; */
DECL|macro|MMCE_VALID_MASK
mdefine_line|#define MMCE_VALID_MASK&t;&t;0x3ff
DECL|macro|MMCE_ILL_MSG_SHFT
mdefine_line|#define MMCE_ILL_MSG_SHFT&t;8
DECL|macro|MMCE_ILL_MSG_MASK
mdefine_line|#define MMCE_ILL_MSG_MASK&t;(UINT64_CAST 0x03 &lt;&lt; MMCE_ILL_MSG_SHFT)
DECL|macro|MMCE_ILL_REV_SHFT
mdefine_line|#define MMCE_ILL_REV_SHFT&t;6
DECL|macro|MMCE_ILL_REV_MASK
mdefine_line|#define MMCE_ILL_REV_MASK&t;(UINT64_CAST 0x03 &lt;&lt; MMCE_ILL_REV_SHFT)
DECL|macro|MMCE_LONG_PACK_SHFT
mdefine_line|#define MMCE_LONG_PACK_SHFT&t;4
DECL|macro|MMCE_LONG_PACK_MASK
mdefine_line|#define MMCE_LONG_PACK_MASK&t;(UINT64_CAST 0x03 &lt;&lt; MMCE_lONG_PACK_SHFT)
DECL|macro|MMCE_SHORT_PACK_SHFT
mdefine_line|#define MMCE_SHORT_PACK_SHFT&t;2
DECL|macro|MMCE_SHORT_PACK_MASK
mdefine_line|#define MMCE_SHORT_PACK_MASK&t;(UINT64_CAST 0x03 &lt;&lt; MMCE_SHORT_PACK_SHFT)
DECL|macro|MMCE_BAD_DATA_SHFT
mdefine_line|#define MMCE_BAD_DATA_SHFT&t;0
DECL|macro|MMCE_BAD_DATA_MASK
mdefine_line|#define MMCE_BAD_DATA_MASK&t;(UINT64_CAST 0x03 &lt;&lt; MMCE_BAD_DATA_SHFT)
DECL|macro|MD_PERF_COUNTERS
mdefine_line|#define MD_PERF_COUNTERS&t;6
DECL|macro|MD_PERF_SETS
mdefine_line|#define MD_PERF_SETS&t;&t;6
DECL|macro|MEM_DIMM_MASK
mdefine_line|#define MEM_DIMM_MASK&t;&t;&t;&t;0xe0000000
DECL|macro|MEM_DIMM_SHFT
mdefine_line|#define MEM_DIMM_SHFT&t;&t;&t;&t;29
macro_line|#endif /* _ASM_SN_SN0_HUBMD_H */
eof
