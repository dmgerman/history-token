macro_line|#ifndef __ALPHA_T2__H__
DECL|macro|__ALPHA_T2__H__
mdefine_line|#define __ALPHA_T2__H__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/compiler.h&gt;
multiline_comment|/*&n; * T2 is the internal name for the core logic chipset which provides&n; * memory controller and PCI access for the SABLE-based systems.&n; *&n; * This file is based on:&n; *&n; * SABLE I/O Specification&n; * Revision/Update Information: 1.3&n; *&n; * jestabro@amt.tay1.dec.com Initial Version.&n; *&n; */
DECL|macro|T2_MEM_R1_MASK
mdefine_line|#define T2_MEM_R1_MASK 0x03ffffff  /* Mem sparse region 1 mask is 26 bits */
multiline_comment|/* GAMMA-SABLE is a SABLE with EV5-based CPUs */
DECL|macro|_GAMMA_BIAS
mdefine_line|#define _GAMMA_BIAS&t;&t;0x8000000000UL
macro_line|#if defined(CONFIG_ALPHA_GENERIC)
DECL|macro|GAMMA_BIAS
mdefine_line|#define GAMMA_BIAS&t;&t;alpha_mv.sys.t2.gamma_bias
macro_line|#elif defined(CONFIG_ALPHA_GAMMA)
DECL|macro|GAMMA_BIAS
mdefine_line|#define GAMMA_BIAS&t;&t;_GAMMA_BIAS
macro_line|#else
DECL|macro|GAMMA_BIAS
mdefine_line|#define GAMMA_BIAS&t;&t;0
macro_line|#endif
multiline_comment|/*&n; * Memory spaces:&n; */
DECL|macro|T2_CONF
mdefine_line|#define T2_CONF&t;&t;        (IDENT_ADDR + GAMMA_BIAS + 0x390000000UL)
DECL|macro|T2_IO
mdefine_line|#define T2_IO&t;&t;&t;(IDENT_ADDR + GAMMA_BIAS + 0x3a0000000UL)
DECL|macro|T2_SPARSE_MEM
mdefine_line|#define T2_SPARSE_MEM&t;&t;(IDENT_ADDR + GAMMA_BIAS + 0x200000000UL)
DECL|macro|T2_DENSE_MEM
mdefine_line|#define T2_DENSE_MEM&t;        (IDENT_ADDR + GAMMA_BIAS + 0x3c0000000UL)
DECL|macro|T2_IOCSR
mdefine_line|#define T2_IOCSR&t;&t;(IDENT_ADDR + GAMMA_BIAS + 0x38e000000UL)
DECL|macro|T2_CERR1
mdefine_line|#define T2_CERR1&t;&t;(IDENT_ADDR + GAMMA_BIAS + 0x38e000020UL)
DECL|macro|T2_CERR2
mdefine_line|#define T2_CERR2&t;&t;(IDENT_ADDR + GAMMA_BIAS + 0x38e000040UL)
DECL|macro|T2_CERR3
mdefine_line|#define T2_CERR3&t;&t;(IDENT_ADDR + GAMMA_BIAS + 0x38e000060UL)
DECL|macro|T2_PERR1
mdefine_line|#define T2_PERR1&t;&t;(IDENT_ADDR + GAMMA_BIAS + 0x38e000080UL)
DECL|macro|T2_PERR2
mdefine_line|#define T2_PERR2&t;&t;(IDENT_ADDR + GAMMA_BIAS + 0x38e0000a0UL)
DECL|macro|T2_PSCR
mdefine_line|#define T2_PSCR&t;&t;&t;(IDENT_ADDR + GAMMA_BIAS + 0x38e0000c0UL)
DECL|macro|T2_HAE_1
mdefine_line|#define T2_HAE_1&t;&t;(IDENT_ADDR + GAMMA_BIAS + 0x38e0000e0UL)
DECL|macro|T2_HAE_2
mdefine_line|#define T2_HAE_2&t;&t;(IDENT_ADDR + GAMMA_BIAS + 0x38e000100UL)
DECL|macro|T2_HBASE
mdefine_line|#define T2_HBASE&t;&t;(IDENT_ADDR + GAMMA_BIAS + 0x38e000120UL)
DECL|macro|T2_WBASE1
mdefine_line|#define T2_WBASE1&t;&t;(IDENT_ADDR + GAMMA_BIAS + 0x38e000140UL)
DECL|macro|T2_WMASK1
mdefine_line|#define T2_WMASK1&t;&t;(IDENT_ADDR + GAMMA_BIAS + 0x38e000160UL)
DECL|macro|T2_TBASE1
mdefine_line|#define T2_TBASE1&t;&t;(IDENT_ADDR + GAMMA_BIAS + 0x38e000180UL)
DECL|macro|T2_WBASE2
mdefine_line|#define T2_WBASE2&t;&t;(IDENT_ADDR + GAMMA_BIAS + 0x38e0001a0UL)
DECL|macro|T2_WMASK2
mdefine_line|#define T2_WMASK2&t;&t;(IDENT_ADDR + GAMMA_BIAS + 0x38e0001c0UL)
DECL|macro|T2_TBASE2
mdefine_line|#define T2_TBASE2&t;&t;(IDENT_ADDR + GAMMA_BIAS + 0x38e0001e0UL)
DECL|macro|T2_TLBBR
mdefine_line|#define T2_TLBBR&t;&t;(IDENT_ADDR + GAMMA_BIAS + 0x38e000200UL)
DECL|macro|T2_HAE_3
mdefine_line|#define T2_HAE_3&t;&t;(IDENT_ADDR + GAMMA_BIAS + 0x38e000240UL)
DECL|macro|T2_HAE_4
mdefine_line|#define T2_HAE_4&t;&t;(IDENT_ADDR + GAMMA_BIAS + 0x38e000260UL)
DECL|macro|T2_HAE_ADDRESS
mdefine_line|#define T2_HAE_ADDRESS&t;&t;T2_HAE_1
multiline_comment|/*  T2 CSRs are in the non-cachable primary IO space from 3.8000.0000 to&n; 3.8fff.ffff&n; *&n; *  +--------------+ 3 8000 0000&n; *  | CPU 0 CSRs   |&n; *  +--------------+ 3 8100 0000&n; *  | CPU 1 CSRs   |&n; *  +--------------+ 3 8200 0000&n; *  | CPU 2 CSRs   |&n; *  +--------------+ 3 8300 0000&n; *  | CPU 3 CSRs   |&n; *  +--------------+ 3 8400 0000&n; *  | CPU Reserved |&n; *  +--------------+ 3 8700 0000&n; *  | Mem Reserved |&n; *  +--------------+ 3 8800 0000&n; *  | Mem 0 CSRs   |&n; *  +--------------+ 3 8900 0000&n; *  | Mem 1 CSRs   |&n; *  +--------------+ 3 8a00 0000&n; *  | Mem 2 CSRs   |&n; *  +--------------+ 3 8b00 0000&n; *  | Mem 3 CSRs   |&n; *  +--------------+ 3 8c00 0000&n; *  | Mem Reserved |&n; *  +--------------+ 3 8e00 0000&n; *  | PCI Bridge   |&n; *  +--------------+ 3 8f00 0000&n; *  | Expansion IO |&n; *  +--------------+ 3 9000 0000&n; *&n; *&n; */
DECL|macro|T2_CPU0_BASE
mdefine_line|#define T2_CPU0_BASE            (IDENT_ADDR + GAMMA_BIAS + 0x380000000L)
DECL|macro|T2_CPU1_BASE
mdefine_line|#define T2_CPU1_BASE            (IDENT_ADDR + GAMMA_BIAS + 0x381000000L)
DECL|macro|T2_CPU2_BASE
mdefine_line|#define T2_CPU2_BASE            (IDENT_ADDR + GAMMA_BIAS + 0x382000000L)
DECL|macro|T2_CPU3_BASE
mdefine_line|#define T2_CPU3_BASE            (IDENT_ADDR + GAMMA_BIAS + 0x383000000L)
DECL|macro|T2_MEM0_BASE
mdefine_line|#define T2_MEM0_BASE            (IDENT_ADDR + GAMMA_BIAS + 0x388000000L)
DECL|macro|T2_MEM1_BASE
mdefine_line|#define T2_MEM1_BASE            (IDENT_ADDR + GAMMA_BIAS + 0x389000000L)
DECL|macro|T2_MEM2_BASE
mdefine_line|#define T2_MEM2_BASE            (IDENT_ADDR + GAMMA_BIAS + 0x38a000000L)
DECL|macro|T2_MEM3_BASE
mdefine_line|#define T2_MEM3_BASE            (IDENT_ADDR + GAMMA_BIAS + 0x38b000000L)
multiline_comment|/*&n; * Sable CPU Module CSRS&n; *&n; * These are CSRs for hardware other than the CPU chip on the CPU module.&n; * The CPU module has Backup Cache control logic, Cbus control logic, and&n; * interrupt control logic on it.  There is a duplicate tag store to speed&n; * up maintaining cache coherency.&n; */
DECL|struct|sable_cpu_csr
r_struct
id|sable_cpu_csr
(brace
DECL|member|bcc
DECL|member|fill_00
r_int
r_int
id|bcc
suffix:semicolon
r_int
id|fill_00
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* Backup Cache Control */
DECL|member|bcce
DECL|member|fill_01
r_int
r_int
id|bcce
suffix:semicolon
r_int
id|fill_01
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* Backup Cache Correctable Error */
DECL|member|bccea
DECL|member|fill_02
r_int
r_int
id|bccea
suffix:semicolon
r_int
id|fill_02
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* B-Cache Corr Err Address Latch */
DECL|member|bcue
DECL|member|fill_03
r_int
r_int
id|bcue
suffix:semicolon
r_int
id|fill_03
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* B-Cache Uncorrectable Error */
DECL|member|bcuea
DECL|member|fill_04
r_int
r_int
id|bcuea
suffix:semicolon
r_int
id|fill_04
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* B-Cache Uncorr Err Addr Latch */
DECL|member|dter
DECL|member|fill_05
r_int
r_int
id|dter
suffix:semicolon
r_int
id|fill_05
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* Duplicate Tag Error */
DECL|member|cbctl
DECL|member|fill_06
r_int
r_int
id|cbctl
suffix:semicolon
r_int
id|fill_06
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* CBus Control */
DECL|member|cbe
DECL|member|fill_07
r_int
r_int
id|cbe
suffix:semicolon
r_int
id|fill_07
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* CBus Error */
DECL|member|cbeal
DECL|member|fill_08
r_int
r_int
id|cbeal
suffix:semicolon
r_int
id|fill_08
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* CBus Error Addr Latch low */
DECL|member|cbeah
DECL|member|fill_09
r_int
r_int
id|cbeah
suffix:semicolon
r_int
id|fill_09
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* CBus Error Addr Latch high */
DECL|member|pmbx
DECL|member|fill_10
r_int
r_int
id|pmbx
suffix:semicolon
r_int
id|fill_10
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* Processor Mailbox */
DECL|member|ipir
DECL|member|fill_11
r_int
r_int
id|ipir
suffix:semicolon
r_int
id|fill_11
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* Inter-Processor Int Request */
DECL|member|sic
DECL|member|fill_12
r_int
r_int
id|sic
suffix:semicolon
r_int
id|fill_12
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* System Interrupt Clear */
DECL|member|adlk
DECL|member|fill_13
r_int
r_int
id|adlk
suffix:semicolon
r_int
id|fill_13
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* Address Lock (LDxL/STxC) */
DECL|member|madrl
DECL|member|fill_14
r_int
r_int
id|madrl
suffix:semicolon
r_int
id|fill_14
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* CBus Miss Address */
DECL|member|rev
DECL|member|fill_15
r_int
r_int
id|rev
suffix:semicolon
r_int
id|fill_15
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* CMIC Revision */
)brace
suffix:semicolon
multiline_comment|/*&n; * Data structure for handling T2 machine checks:&n; */
DECL|struct|el_t2_frame_header
r_struct
id|el_t2_frame_header
(brace
DECL|member|elcf_fid
r_int
r_int
id|elcf_fid
suffix:semicolon
multiline_comment|/* Frame ID (from above) */
DECL|member|elcf_size
r_int
r_int
id|elcf_size
suffix:semicolon
multiline_comment|/* Size of frame in bytes */
)brace
suffix:semicolon
DECL|struct|el_t2_procdata_mcheck
r_struct
id|el_t2_procdata_mcheck
(brace
DECL|member|elfmc_paltemp
r_int
r_int
id|elfmc_paltemp
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* PAL TEMP REGS. */
multiline_comment|/* EV4-specific fields */
DECL|member|elfmc_exc_addr
r_int
r_int
id|elfmc_exc_addr
suffix:semicolon
multiline_comment|/* Addr of excepting insn. */
DECL|member|elfmc_exc_sum
r_int
r_int
id|elfmc_exc_sum
suffix:semicolon
multiline_comment|/* Summary of arith traps. */
DECL|member|elfmc_exc_mask
r_int
r_int
id|elfmc_exc_mask
suffix:semicolon
multiline_comment|/* Exception mask (from exc_sum). */
DECL|member|elfmc_iccsr
r_int
r_int
id|elfmc_iccsr
suffix:semicolon
multiline_comment|/* IBox hardware enables. */
DECL|member|elfmc_pal_base
r_int
r_int
id|elfmc_pal_base
suffix:semicolon
multiline_comment|/* Base address for PALcode. */
DECL|member|elfmc_hier
r_int
r_int
id|elfmc_hier
suffix:semicolon
multiline_comment|/* Hardware Interrupt Enable. */
DECL|member|elfmc_hirr
r_int
r_int
id|elfmc_hirr
suffix:semicolon
multiline_comment|/* Hardware Interrupt Request. */
DECL|member|elfmc_mm_csr
r_int
r_int
id|elfmc_mm_csr
suffix:semicolon
multiline_comment|/* D-stream fault info. */
DECL|member|elfmc_dc_stat
r_int
r_int
id|elfmc_dc_stat
suffix:semicolon
multiline_comment|/* D-cache status (ECC/Parity Err). */
DECL|member|elfmc_dc_addr
r_int
r_int
id|elfmc_dc_addr
suffix:semicolon
multiline_comment|/* EV3 Phys Addr for ECC/DPERR. */
DECL|member|elfmc_abox_ctl
r_int
r_int
id|elfmc_abox_ctl
suffix:semicolon
multiline_comment|/* ABox Control Register. */
DECL|member|elfmc_biu_stat
r_int
r_int
id|elfmc_biu_stat
suffix:semicolon
multiline_comment|/* BIU Status. */
DECL|member|elfmc_biu_addr
r_int
r_int
id|elfmc_biu_addr
suffix:semicolon
multiline_comment|/* BUI Address. */
DECL|member|elfmc_biu_ctl
r_int
r_int
id|elfmc_biu_ctl
suffix:semicolon
multiline_comment|/* BIU Control. */
DECL|member|elfmc_fill_syndrome
r_int
r_int
id|elfmc_fill_syndrome
suffix:semicolon
multiline_comment|/* For correcting ECC errors. */
DECL|member|elfmc_fill_addr
r_int
r_int
id|elfmc_fill_addr
suffix:semicolon
multiline_comment|/* Cache block which was being read. */
DECL|member|elfmc_va
r_int
r_int
id|elfmc_va
suffix:semicolon
multiline_comment|/* Effective VA of fault or miss. */
DECL|member|elfmc_bc_tag
r_int
r_int
id|elfmc_bc_tag
suffix:semicolon
multiline_comment|/* Backup Cache Tag Probe Results. */
)brace
suffix:semicolon
multiline_comment|/*&n; * Sable processor specific Machine Check Data segment.&n; */
DECL|struct|el_t2_logout_header
r_struct
id|el_t2_logout_header
(brace
DECL|member|elfl_size
r_int
r_int
id|elfl_size
suffix:semicolon
multiline_comment|/* size in bytes of logout area. */
DECL|member|elfl_sbz1
r_int
id|elfl_sbz1
suffix:colon
l_int|31
suffix:semicolon
multiline_comment|/* Should be zero. */
DECL|member|elfl_retry
r_char
id|elfl_retry
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Retry flag. */
DECL|member|elfl_procoffset
r_int
r_int
id|elfl_procoffset
suffix:semicolon
multiline_comment|/* Processor-specific offset. */
DECL|member|elfl_sysoffset
r_int
r_int
id|elfl_sysoffset
suffix:semicolon
multiline_comment|/* Offset of system-specific. */
DECL|member|elfl_error_type
r_int
r_int
id|elfl_error_type
suffix:semicolon
multiline_comment|/* PAL error type code. */
DECL|member|elfl_frame_rev
r_int
r_int
id|elfl_frame_rev
suffix:semicolon
multiline_comment|/* PAL Frame revision. */
)brace
suffix:semicolon
DECL|struct|el_t2_sysdata_mcheck
r_struct
id|el_t2_sysdata_mcheck
(brace
DECL|member|elcmc_bcc
r_int
r_int
id|elcmc_bcc
suffix:semicolon
multiline_comment|/* CSR 0 */
DECL|member|elcmc_bcce
r_int
r_int
id|elcmc_bcce
suffix:semicolon
multiline_comment|/* CSR 1 */
DECL|member|elcmc_bccea
r_int
r_int
id|elcmc_bccea
suffix:semicolon
multiline_comment|/* CSR 2 */
DECL|member|elcmc_bcue
r_int
r_int
id|elcmc_bcue
suffix:semicolon
multiline_comment|/* CSR 3 */
DECL|member|elcmc_bcuea
r_int
r_int
id|elcmc_bcuea
suffix:semicolon
multiline_comment|/* CSR 4 */
DECL|member|elcmc_dter
r_int
r_int
id|elcmc_dter
suffix:semicolon
multiline_comment|/* CSR 5 */
DECL|member|elcmc_cbctl
r_int
r_int
id|elcmc_cbctl
suffix:semicolon
multiline_comment|/* CSR 6 */
DECL|member|elcmc_cbe
r_int
r_int
id|elcmc_cbe
suffix:semicolon
multiline_comment|/* CSR 7 */
DECL|member|elcmc_cbeal
r_int
r_int
id|elcmc_cbeal
suffix:semicolon
multiline_comment|/* CSR 8 */
DECL|member|elcmc_cbeah
r_int
r_int
id|elcmc_cbeah
suffix:semicolon
multiline_comment|/* CSR 9 */
DECL|member|elcmc_pmbx
r_int
r_int
id|elcmc_pmbx
suffix:semicolon
multiline_comment|/* CSR 10 */
DECL|member|elcmc_ipir
r_int
r_int
id|elcmc_ipir
suffix:semicolon
multiline_comment|/* CSR 11 */
DECL|member|elcmc_sic
r_int
r_int
id|elcmc_sic
suffix:semicolon
multiline_comment|/* CSR 12 */
DECL|member|elcmc_adlk
r_int
r_int
id|elcmc_adlk
suffix:semicolon
multiline_comment|/* CSR 13 */
DECL|member|elcmc_madrl
r_int
r_int
id|elcmc_madrl
suffix:semicolon
multiline_comment|/* CSR 14 */
DECL|member|elcmc_crrev4
r_int
r_int
id|elcmc_crrev4
suffix:semicolon
multiline_comment|/* CSR 15 */
)brace
suffix:semicolon
multiline_comment|/*&n; * Sable memory error frame - sable pfms section 3.42&n; */
DECL|struct|el_t2_data_memory
r_struct
id|el_t2_data_memory
(brace
DECL|member|elcm_hdr
r_struct
id|el_t2_frame_header
id|elcm_hdr
suffix:semicolon
multiline_comment|/* ID$MEM-FERR = 0x08 */
DECL|member|elcm_module
r_int
r_int
id|elcm_module
suffix:semicolon
multiline_comment|/* Module id. */
DECL|member|elcm_res04
r_int
r_int
id|elcm_res04
suffix:semicolon
multiline_comment|/* Reserved. */
DECL|member|elcm_merr
r_int
r_int
id|elcm_merr
suffix:semicolon
multiline_comment|/* CSR0: Error Reg 1. */
DECL|member|elcm_mcmd1
r_int
r_int
id|elcm_mcmd1
suffix:semicolon
multiline_comment|/* CSR1: Command Trap 1. */
DECL|member|elcm_mcmd2
r_int
r_int
id|elcm_mcmd2
suffix:semicolon
multiline_comment|/* CSR2: Command Trap 2. */
DECL|member|elcm_mconf
r_int
r_int
id|elcm_mconf
suffix:semicolon
multiline_comment|/* CSR3: Configuration. */
DECL|member|elcm_medc1
r_int
r_int
id|elcm_medc1
suffix:semicolon
multiline_comment|/* CSR4: EDC Status 1. */
DECL|member|elcm_medc2
r_int
r_int
id|elcm_medc2
suffix:semicolon
multiline_comment|/* CSR5: EDC Status 2. */
DECL|member|elcm_medcc
r_int
r_int
id|elcm_medcc
suffix:semicolon
multiline_comment|/* CSR6: EDC Control. */
DECL|member|elcm_msctl
r_int
r_int
id|elcm_msctl
suffix:semicolon
multiline_comment|/* CSR7: Stream Buffer Control. */
DECL|member|elcm_mref
r_int
r_int
id|elcm_mref
suffix:semicolon
multiline_comment|/* CSR8: Refresh Control. */
DECL|member|elcm_filter
r_int
r_int
id|elcm_filter
suffix:semicolon
multiline_comment|/* CSR9: CRD Filter Control. */
)brace
suffix:semicolon
multiline_comment|/*&n; * Sable other CPU error frame - sable pfms section 3.43&n; */
DECL|struct|el_t2_data_other_cpu
r_struct
id|el_t2_data_other_cpu
(brace
DECL|member|elco_cpuid
r_int
id|elco_cpuid
suffix:semicolon
multiline_comment|/* CPU ID */
DECL|member|elco_res02
r_int
id|elco_res02
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|elco_bcc
r_int
r_int
id|elco_bcc
suffix:semicolon
multiline_comment|/* CSR 0 */
DECL|member|elco_bcce
r_int
r_int
id|elco_bcce
suffix:semicolon
multiline_comment|/* CSR 1 */
DECL|member|elco_bccea
r_int
r_int
id|elco_bccea
suffix:semicolon
multiline_comment|/* CSR 2 */
DECL|member|elco_bcue
r_int
r_int
id|elco_bcue
suffix:semicolon
multiline_comment|/* CSR 3 */
DECL|member|elco_bcuea
r_int
r_int
id|elco_bcuea
suffix:semicolon
multiline_comment|/* CSR 4 */
DECL|member|elco_dter
r_int
r_int
id|elco_dter
suffix:semicolon
multiline_comment|/* CSR 5 */
DECL|member|elco_cbctl
r_int
r_int
id|elco_cbctl
suffix:semicolon
multiline_comment|/* CSR 6 */
DECL|member|elco_cbe
r_int
r_int
id|elco_cbe
suffix:semicolon
multiline_comment|/* CSR 7 */
DECL|member|elco_cbeal
r_int
r_int
id|elco_cbeal
suffix:semicolon
multiline_comment|/* CSR 8 */
DECL|member|elco_cbeah
r_int
r_int
id|elco_cbeah
suffix:semicolon
multiline_comment|/* CSR 9 */
DECL|member|elco_pmbx
r_int
r_int
id|elco_pmbx
suffix:semicolon
multiline_comment|/* CSR 10 */
DECL|member|elco_ipir
r_int
r_int
id|elco_ipir
suffix:semicolon
multiline_comment|/* CSR 11 */
DECL|member|elco_sic
r_int
r_int
id|elco_sic
suffix:semicolon
multiline_comment|/* CSR 12 */
DECL|member|elco_adlk
r_int
r_int
id|elco_adlk
suffix:semicolon
multiline_comment|/* CSR 13 */
DECL|member|elco_madrl
r_int
r_int
id|elco_madrl
suffix:semicolon
multiline_comment|/* CSR 14 */
DECL|member|elco_crrev4
r_int
r_int
id|elco_crrev4
suffix:semicolon
multiline_comment|/* CSR 15 */
)brace
suffix:semicolon
multiline_comment|/*&n; * Sable other CPU error frame - sable pfms section 3.44&n; */
DECL|struct|el_t2_data_t2
r_struct
id|el_t2_data_t2
(brace
DECL|member|elct_hdr
r_struct
id|el_t2_frame_header
id|elct_hdr
suffix:semicolon
multiline_comment|/* ID$T2-FRAME */
DECL|member|elct_iocsr
r_int
r_int
id|elct_iocsr
suffix:semicolon
multiline_comment|/* IO Control and Status Register */
DECL|member|elct_cerr1
r_int
r_int
id|elct_cerr1
suffix:semicolon
multiline_comment|/* Cbus Error Register 1 */
DECL|member|elct_cerr2
r_int
r_int
id|elct_cerr2
suffix:semicolon
multiline_comment|/* Cbus Error Register 2 */
DECL|member|elct_cerr3
r_int
r_int
id|elct_cerr3
suffix:semicolon
multiline_comment|/* Cbus Error Register 3 */
DECL|member|elct_perr1
r_int
r_int
id|elct_perr1
suffix:semicolon
multiline_comment|/* PCI Error Register 1 */
DECL|member|elct_perr2
r_int
r_int
id|elct_perr2
suffix:semicolon
multiline_comment|/* PCI Error Register 2 */
DECL|member|elct_hae0_1
r_int
r_int
id|elct_hae0_1
suffix:semicolon
multiline_comment|/* High Address Extension Register 1 */
DECL|member|elct_hae0_2
r_int
r_int
id|elct_hae0_2
suffix:semicolon
multiline_comment|/* High Address Extension Register 2 */
DECL|member|elct_hbase
r_int
r_int
id|elct_hbase
suffix:semicolon
multiline_comment|/* High Base Register */
DECL|member|elct_wbase1
r_int
r_int
id|elct_wbase1
suffix:semicolon
multiline_comment|/* Window Base Register 1 */
DECL|member|elct_wmask1
r_int
r_int
id|elct_wmask1
suffix:semicolon
multiline_comment|/* Window Mask Register 1 */
DECL|member|elct_tbase1
r_int
r_int
id|elct_tbase1
suffix:semicolon
multiline_comment|/* Translated Base Register 1 */
DECL|member|elct_wbase2
r_int
r_int
id|elct_wbase2
suffix:semicolon
multiline_comment|/* Window Base Register 2 */
DECL|member|elct_wmask2
r_int
r_int
id|elct_wmask2
suffix:semicolon
multiline_comment|/* Window Mask Register 2 */
DECL|member|elct_tbase2
r_int
r_int
id|elct_tbase2
suffix:semicolon
multiline_comment|/* Translated Base Register 2 */
DECL|member|elct_tdr0
r_int
r_int
id|elct_tdr0
suffix:semicolon
multiline_comment|/* TLB Data Register 0 */
DECL|member|elct_tdr1
r_int
r_int
id|elct_tdr1
suffix:semicolon
multiline_comment|/* TLB Data Register 1 */
DECL|member|elct_tdr2
r_int
r_int
id|elct_tdr2
suffix:semicolon
multiline_comment|/* TLB Data Register 2 */
DECL|member|elct_tdr3
r_int
r_int
id|elct_tdr3
suffix:semicolon
multiline_comment|/* TLB Data Register 3 */
DECL|member|elct_tdr4
r_int
r_int
id|elct_tdr4
suffix:semicolon
multiline_comment|/* TLB Data Register 4 */
DECL|member|elct_tdr5
r_int
r_int
id|elct_tdr5
suffix:semicolon
multiline_comment|/* TLB Data Register 5 */
DECL|member|elct_tdr6
r_int
r_int
id|elct_tdr6
suffix:semicolon
multiline_comment|/* TLB Data Register 6 */
DECL|member|elct_tdr7
r_int
r_int
id|elct_tdr7
suffix:semicolon
multiline_comment|/* TLB Data Register 7 */
)brace
suffix:semicolon
multiline_comment|/*&n; * Sable error log data structure - sable pfms section 3.40&n; */
DECL|struct|el_t2_data_corrected
r_struct
id|el_t2_data_corrected
(brace
DECL|member|elcpb_biu_stat
r_int
r_int
id|elcpb_biu_stat
suffix:semicolon
DECL|member|elcpb_biu_addr
r_int
r_int
id|elcpb_biu_addr
suffix:semicolon
DECL|member|elcpb_biu_ctl
r_int
r_int
id|elcpb_biu_ctl
suffix:semicolon
DECL|member|elcpb_fill_syndrome
r_int
r_int
id|elcpb_fill_syndrome
suffix:semicolon
DECL|member|elcpb_fill_addr
r_int
r_int
id|elcpb_fill_addr
suffix:semicolon
DECL|member|elcpb_bc_tag
r_int
r_int
id|elcpb_bc_tag
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Sable error log data structure&n; * Note there are 4 memory slots on sable (see t2.h)&n; */
DECL|struct|el_t2_frame_mcheck
r_struct
id|el_t2_frame_mcheck
(brace
DECL|member|elfmc_header
r_struct
id|el_t2_frame_header
id|elfmc_header
suffix:semicolon
multiline_comment|/* ID$P-FRAME_MCHECK */
DECL|member|elfmc_hdr
r_struct
id|el_t2_logout_header
id|elfmc_hdr
suffix:semicolon
DECL|member|elfmc_procdata
r_struct
id|el_t2_procdata_mcheck
id|elfmc_procdata
suffix:semicolon
DECL|member|elfmc_sysdata
r_struct
id|el_t2_sysdata_mcheck
id|elfmc_sysdata
suffix:semicolon
DECL|member|elfmc_t2data
r_struct
id|el_t2_data_t2
id|elfmc_t2data
suffix:semicolon
DECL|member|elfmc_memdata
r_struct
id|el_t2_data_memory
id|elfmc_memdata
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|elfmc_footer
r_struct
id|el_t2_frame_header
id|elfmc_footer
suffix:semicolon
multiline_comment|/* empty */
)brace
suffix:semicolon
multiline_comment|/*&n; * Sable error log data structures on memory errors&n; */
DECL|struct|el_t2_frame_corrected
r_struct
id|el_t2_frame_corrected
(brace
DECL|member|elfcc_header
r_struct
id|el_t2_frame_header
id|elfcc_header
suffix:semicolon
multiline_comment|/* ID$P-BC-COR */
DECL|member|elfcc_hdr
r_struct
id|el_t2_logout_header
id|elfcc_hdr
suffix:semicolon
DECL|member|elfcc_procdata
r_struct
id|el_t2_data_corrected
id|elfcc_procdata
suffix:semicolon
multiline_comment|/*&t;struct el_t2_data_t2 elfcc_t2data;&t;&t;*/
multiline_comment|/*&t;struct el_t2_data_memory elfcc_memdata[4];&t;*/
DECL|member|elfcc_footer
r_struct
id|el_t2_frame_header
id|elfcc_footer
suffix:semicolon
multiline_comment|/* empty */
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __EXTERN_INLINE
DECL|macro|__EXTERN_INLINE
mdefine_line|#define __EXTERN_INLINE extern inline
DECL|macro|__IO_EXTERN_INLINE
mdefine_line|#define __IO_EXTERN_INLINE
macro_line|#endif
multiline_comment|/*&n; * I/O functions:&n; *&n; * T2 (the core logic PCI/memory support chipset for the SABLE&n; * series of processors uses a sparse address mapping scheme to&n; * get at PCI memory and I/O.&n; */
DECL|macro|vip
mdefine_line|#define vip&t;volatile int *
DECL|macro|vuip
mdefine_line|#define vuip&t;volatile unsigned int *
DECL|function|t2_inb
id|__EXTERN_INLINE
r_int
r_int
id|t2_inb
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_int
id|result
op_assign
op_star
(paren
id|vip
)paren
(paren
(paren
id|addr
op_lshift
l_int|5
)paren
op_plus
id|T2_IO
op_plus
l_int|0x00
)paren
suffix:semicolon
r_return
id|__kernel_extbl
c_func
(paren
id|result
comma
id|addr
op_amp
l_int|3
)paren
suffix:semicolon
)brace
DECL|function|t2_outb
id|__EXTERN_INLINE
r_void
id|t2_outb
c_func
(paren
r_int
r_char
id|b
comma
r_int
r_int
id|addr
)paren
(brace
r_int
r_int
id|w
suffix:semicolon
id|w
op_assign
id|__kernel_insbl
c_func
(paren
id|b
comma
id|addr
op_amp
l_int|3
)paren
suffix:semicolon
op_star
(paren
id|vuip
)paren
(paren
(paren
id|addr
op_lshift
l_int|5
)paren
op_plus
id|T2_IO
op_plus
l_int|0x00
)paren
op_assign
id|w
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|t2_inw
id|__EXTERN_INLINE
r_int
r_int
id|t2_inw
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_int
id|result
op_assign
op_star
(paren
id|vip
)paren
(paren
(paren
id|addr
op_lshift
l_int|5
)paren
op_plus
id|T2_IO
op_plus
l_int|0x08
)paren
suffix:semicolon
r_return
id|__kernel_extwl
c_func
(paren
id|result
comma
id|addr
op_amp
l_int|3
)paren
suffix:semicolon
)brace
DECL|function|t2_outw
id|__EXTERN_INLINE
r_void
id|t2_outw
c_func
(paren
r_int
r_int
id|b
comma
r_int
r_int
id|addr
)paren
(brace
r_int
r_int
id|w
suffix:semicolon
id|w
op_assign
id|__kernel_inswl
c_func
(paren
id|b
comma
id|addr
op_amp
l_int|3
)paren
suffix:semicolon
op_star
(paren
id|vuip
)paren
(paren
(paren
id|addr
op_lshift
l_int|5
)paren
op_plus
id|T2_IO
op_plus
l_int|0x08
)paren
op_assign
id|w
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|t2_inl
id|__EXTERN_INLINE
r_int
r_int
id|t2_inl
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_return
op_star
(paren
id|vuip
)paren
(paren
(paren
id|addr
op_lshift
l_int|5
)paren
op_plus
id|T2_IO
op_plus
l_int|0x18
)paren
suffix:semicolon
)brace
DECL|function|t2_outl
id|__EXTERN_INLINE
r_void
id|t2_outl
c_func
(paren
r_int
r_int
id|b
comma
r_int
r_int
id|addr
)paren
(brace
op_star
(paren
id|vuip
)paren
(paren
(paren
id|addr
op_lshift
l_int|5
)paren
op_plus
id|T2_IO
op_plus
l_int|0x18
)paren
op_assign
id|b
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Memory functions.&n; *&n; * For reading and writing 8 and 16 bit quantities we need to&n; * go through one of the three sparse address mapping regions&n; * and use the HAE_MEM CSR to provide some bits of the address.&n; * The following few routines use only sparse address region 1&n; * which gives 1Gbyte of accessible space which relates exactly&n; * to the amount of PCI memory mapping *into* system address space.&n; * See p 6-17 of the specification but it looks something like this:&n; *&n; * 21164 Address:&n; *&n; *          3         2         1&n; * 9876543210987654321098765432109876543210&n; * 1ZZZZ0.PCI.QW.Address............BBLL&n; *&n; * ZZ = SBZ&n; * BB = Byte offset&n; * LL = Transfer length&n; *&n; * PCI Address:&n; *&n; * 3         2         1&n; * 10987654321098765432109876543210&n; * HHH....PCI.QW.Address........ 00&n; *&n; * HHH = 31:29 HAE_MEM CSR&n; *&n; */
DECL|function|t2_readb
id|__EXTERN_INLINE
r_int
r_int
id|t2_readb
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_int
r_int
id|result
comma
id|msb
suffix:semicolon
id|msb
op_assign
id|addr
op_amp
l_int|0xE0000000
suffix:semicolon
id|addr
op_and_assign
id|T2_MEM_R1_MASK
suffix:semicolon
id|set_hae
c_func
(paren
id|msb
)paren
suffix:semicolon
id|result
op_assign
op_star
(paren
id|vip
)paren
(paren
(paren
id|addr
op_lshift
l_int|5
)paren
op_plus
id|T2_SPARSE_MEM
op_plus
l_int|0x00
)paren
suffix:semicolon
r_return
id|__kernel_extbl
c_func
(paren
id|result
comma
id|addr
op_amp
l_int|3
)paren
suffix:semicolon
)brace
DECL|function|t2_readw
id|__EXTERN_INLINE
r_int
r_int
id|t2_readw
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_int
r_int
id|result
comma
id|msb
suffix:semicolon
id|msb
op_assign
id|addr
op_amp
l_int|0xE0000000
suffix:semicolon
id|addr
op_and_assign
id|T2_MEM_R1_MASK
suffix:semicolon
id|set_hae
c_func
(paren
id|msb
)paren
suffix:semicolon
id|result
op_assign
op_star
(paren
id|vuip
)paren
(paren
(paren
id|addr
op_lshift
l_int|5
)paren
op_plus
id|T2_SPARSE_MEM
op_plus
l_int|0x08
)paren
suffix:semicolon
r_return
id|__kernel_extwl
c_func
(paren
id|result
comma
id|addr
op_amp
l_int|3
)paren
suffix:semicolon
)brace
multiline_comment|/* On SABLE with T2, we must use SPARSE memory even for 32-bit access. */
DECL|function|t2_readl
id|__EXTERN_INLINE
r_int
r_int
id|t2_readl
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_int
r_int
id|msb
suffix:semicolon
id|msb
op_assign
id|addr
op_amp
l_int|0xE0000000
suffix:semicolon
id|addr
op_and_assign
id|T2_MEM_R1_MASK
suffix:semicolon
id|set_hae
c_func
(paren
id|msb
)paren
suffix:semicolon
r_return
op_star
(paren
id|vuip
)paren
(paren
(paren
id|addr
op_lshift
l_int|5
)paren
op_plus
id|T2_SPARSE_MEM
op_plus
l_int|0x18
)paren
suffix:semicolon
)brace
DECL|function|t2_readq
id|__EXTERN_INLINE
r_int
r_int
id|t2_readq
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_int
r_int
id|r0
comma
id|r1
comma
id|work
comma
id|msb
suffix:semicolon
id|msb
op_assign
id|addr
op_amp
l_int|0xE0000000
suffix:semicolon
id|addr
op_and_assign
id|T2_MEM_R1_MASK
suffix:semicolon
id|set_hae
c_func
(paren
id|msb
)paren
suffix:semicolon
id|work
op_assign
(paren
id|addr
op_lshift
l_int|5
)paren
op_plus
id|T2_SPARSE_MEM
op_plus
l_int|0x18
suffix:semicolon
id|r0
op_assign
op_star
(paren
id|vuip
)paren
(paren
id|work
)paren
suffix:semicolon
id|r1
op_assign
op_star
(paren
id|vuip
)paren
(paren
id|work
op_plus
(paren
l_int|4
op_lshift
l_int|5
)paren
)paren
suffix:semicolon
r_return
id|r1
op_lshift
l_int|32
op_or
id|r0
suffix:semicolon
)brace
DECL|function|t2_writeb
id|__EXTERN_INLINE
r_void
id|t2_writeb
c_func
(paren
r_int
r_char
id|b
comma
r_int
r_int
id|addr
)paren
(brace
r_int
r_int
id|msb
comma
id|w
suffix:semicolon
id|msb
op_assign
id|addr
op_amp
l_int|0xE0000000
suffix:semicolon
id|addr
op_and_assign
id|T2_MEM_R1_MASK
suffix:semicolon
id|set_hae
c_func
(paren
id|msb
)paren
suffix:semicolon
id|w
op_assign
id|__kernel_insbl
c_func
(paren
id|b
comma
id|addr
op_amp
l_int|3
)paren
suffix:semicolon
op_star
(paren
id|vuip
)paren
(paren
(paren
id|addr
op_lshift
l_int|5
)paren
op_plus
id|T2_SPARSE_MEM
op_plus
l_int|0x00
)paren
op_assign
id|w
suffix:semicolon
)brace
DECL|function|t2_writew
id|__EXTERN_INLINE
r_void
id|t2_writew
c_func
(paren
r_int
r_int
id|b
comma
r_int
r_int
id|addr
)paren
(brace
r_int
r_int
id|msb
comma
id|w
suffix:semicolon
id|msb
op_assign
id|addr
op_amp
l_int|0xE0000000
suffix:semicolon
id|addr
op_and_assign
id|T2_MEM_R1_MASK
suffix:semicolon
id|set_hae
c_func
(paren
id|msb
)paren
suffix:semicolon
id|w
op_assign
id|__kernel_inswl
c_func
(paren
id|b
comma
id|addr
op_amp
l_int|3
)paren
suffix:semicolon
op_star
(paren
id|vuip
)paren
(paren
(paren
id|addr
op_lshift
l_int|5
)paren
op_plus
id|T2_SPARSE_MEM
op_plus
l_int|0x08
)paren
op_assign
id|w
suffix:semicolon
)brace
multiline_comment|/* On SABLE with T2, we must use SPARSE memory even for 32-bit access. */
DECL|function|t2_writel
id|__EXTERN_INLINE
r_void
id|t2_writel
c_func
(paren
r_int
r_int
id|b
comma
r_int
r_int
id|addr
)paren
(brace
r_int
r_int
id|msb
suffix:semicolon
id|msb
op_assign
id|addr
op_amp
l_int|0xE0000000
suffix:semicolon
id|addr
op_and_assign
id|T2_MEM_R1_MASK
suffix:semicolon
id|set_hae
c_func
(paren
id|msb
)paren
suffix:semicolon
op_star
(paren
id|vuip
)paren
(paren
(paren
id|addr
op_lshift
l_int|5
)paren
op_plus
id|T2_SPARSE_MEM
op_plus
l_int|0x18
)paren
op_assign
id|b
suffix:semicolon
)brace
DECL|function|t2_writeq
id|__EXTERN_INLINE
r_void
id|t2_writeq
c_func
(paren
r_int
r_int
id|b
comma
r_int
r_int
id|addr
)paren
(brace
r_int
r_int
id|msb
comma
id|work
suffix:semicolon
id|msb
op_assign
id|addr
op_amp
l_int|0xE0000000
suffix:semicolon
id|addr
op_and_assign
id|T2_MEM_R1_MASK
suffix:semicolon
id|set_hae
c_func
(paren
id|msb
)paren
suffix:semicolon
id|work
op_assign
(paren
id|addr
op_lshift
l_int|5
)paren
op_plus
id|T2_SPARSE_MEM
op_plus
l_int|0x18
suffix:semicolon
op_star
(paren
id|vuip
)paren
id|work
op_assign
id|b
suffix:semicolon
op_star
(paren
id|vuip
)paren
(paren
id|work
op_plus
(paren
l_int|4
op_lshift
l_int|5
)paren
)paren
op_assign
id|b
op_rshift
l_int|32
suffix:semicolon
)brace
DECL|function|t2_ioremap
id|__EXTERN_INLINE
r_int
r_int
id|t2_ioremap
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_return
id|addr
suffix:semicolon
)brace
DECL|function|t2_is_ioaddr
id|__EXTERN_INLINE
r_int
id|t2_is_ioaddr
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_return
(paren
r_int
)paren
id|addr
op_ge
l_int|0
suffix:semicolon
)brace
DECL|macro|vip
macro_line|#undef vip
DECL|macro|vuip
macro_line|#undef vuip
macro_line|#ifdef __WANT_IO_DEF
DECL|macro|__inb
mdefine_line|#define __inb(p)&t;&t;t2_inb((unsigned long)(p))
DECL|macro|__inw
mdefine_line|#define __inw(p)&t;&t;t2_inw((unsigned long)(p))
DECL|macro|__inl
mdefine_line|#define __inl(p)&t;&t;t2_inl((unsigned long)(p))
DECL|macro|__outb
mdefine_line|#define __outb(x,p)&t;&t;t2_outb((x),(unsigned long)(p))
DECL|macro|__outw
mdefine_line|#define __outw(x,p)&t;&t;t2_outw((x),(unsigned long)(p))
DECL|macro|__outl
mdefine_line|#define __outl(x,p)&t;&t;t2_outl((x),(unsigned long)(p))
DECL|macro|__readb
mdefine_line|#define __readb(a)&t;&t;t2_readb((unsigned long)(a))
DECL|macro|__readw
mdefine_line|#define __readw(a)&t;&t;t2_readw((unsigned long)(a))
DECL|macro|__readl
mdefine_line|#define __readl(a)&t;&t;t2_readl((unsigned long)(a))
DECL|macro|__readq
mdefine_line|#define __readq(a)&t;&t;t2_readq((unsigned long)(a))
DECL|macro|__writeb
mdefine_line|#define __writeb(x,a)&t;&t;t2_writeb((x),(unsigned long)(a))
DECL|macro|__writew
mdefine_line|#define __writew(x,a)&t;&t;t2_writew((x),(unsigned long)(a))
DECL|macro|__writel
mdefine_line|#define __writel(x,a)&t;&t;t2_writel((x),(unsigned long)(a))
DECL|macro|__writeq
mdefine_line|#define __writeq(x,a)&t;&t;t2_writeq((x),(unsigned long)(a))
DECL|macro|__ioremap
mdefine_line|#define __ioremap(a)&t;&t;t2_ioremap((unsigned long)(a))
DECL|macro|__is_ioaddr
mdefine_line|#define __is_ioaddr(a)&t;&t;t2_is_ioaddr((unsigned long)(a))
macro_line|#endif /* __WANT_IO_DEF */
macro_line|#ifdef __IO_EXTERN_INLINE
DECL|macro|__EXTERN_INLINE
macro_line|#undef __EXTERN_INLINE
DECL|macro|__IO_EXTERN_INLINE
macro_line|#undef __IO_EXTERN_INLINE
macro_line|#endif
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __ALPHA_T2__H__ */
eof
