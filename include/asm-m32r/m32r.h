macro_line|#ifndef _ASM_M32R_M32R_H_
DECL|macro|_ASM_M32R_M32R_H_
mdefine_line|#define _ASM_M32R_M32R_H_
multiline_comment|/*&n; * Mitsubishi M32R processor&n; * Copyright (C) 1997-2002, Mitsubishi Electric Corporation&n; */
multiline_comment|/* $Id$ */
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/* Chip type */
macro_line|#if defined(CONFIG_CHIP_XNUX_MP) || defined(CONFIG_CHIP_XNUX2_MP)
macro_line|#include &lt;asm/m32r_mp_fpga.h&gt;
macro_line|#elif defined(CONFIG_CHIP_VDEC2) || defined(CONFIG_CHIP_XNUX2) &bslash;&n;&t;|| defined(CONFIG_CHIP_M32700) || defined(CONFIG_CHIP_M32102) &bslash;&n;        || defined(CONFIG_CHIP_OPSP)
macro_line|#include &lt;asm/m32102.h&gt;
macro_line|#include &lt;asm/m32102peri.h&gt;
macro_line|#endif
multiline_comment|/* Platform type */
macro_line|#if defined(CONFIG_PLAT_M32700UT)
macro_line|#include &lt;asm/m32700ut/m32700ut_pld.h&gt;
macro_line|#include &lt;asm/m32700ut/m32700ut_lan.h&gt;
macro_line|#include &lt;asm/m32700ut/m32700ut_lcd.h&gt;
macro_line|#endif  /* CONFIG_PLAT_M32700UT */
macro_line|#if defined(CONFIG_PLAT_OPSPUT)
macro_line|#include &lt;asm/opsput/opsput_pld.h&gt;
macro_line|#include &lt;asm/opsput/opsput_lan.h&gt;
macro_line|#include &lt;asm/opsput/opsput_lcd.h&gt;
macro_line|#endif  /* CONFIG_PLAT_OPSPUT */
macro_line|#if defined(CONFIG_PLAT_MAPPI2)
macro_line|#include &lt;asm/mappi2/mappi2_pld.h&gt;
macro_line|#endif&t;/* CONFIG_PLAT_MAPPI2 */
macro_line|#if defined(CONFIG_PLAT_USRV)
macro_line|#include &lt;asm/m32700ut/m32700ut_pld.h&gt;
macro_line|#endif
multiline_comment|/*&n; * M32R Register&n; */
multiline_comment|/*&n; * MMU Register&n; */
DECL|macro|MMU_REG_BASE
mdefine_line|#define MMU_REG_BASE&t;(0xffff0000)
DECL|macro|ITLB_BASE
mdefine_line|#define ITLB_BASE&t;(0xfe000000)
DECL|macro|DTLB_BASE
mdefine_line|#define DTLB_BASE&t;(0xfe000800)
DECL|macro|NR_TLB_ENTRIES
mdefine_line|#define NR_TLB_ENTRIES&t;CONFIG_TLB_ENTRIES
DECL|macro|MATM
mdefine_line|#define MATM&t;MMU_REG_BASE&t;&t;/* MMU Address Translation Mode&n;&t;&t;&t;&t;&t;   Register */
DECL|macro|MPSZ
mdefine_line|#define MPSZ&t;(0x04 + MMU_REG_BASE)&t;/* MMU Page Size Designation Register */
DECL|macro|MASID
mdefine_line|#define MASID&t;(0x08 + MMU_REG_BASE)&t;/* MMU Address Space ID Register */
DECL|macro|MESTS
mdefine_line|#define MESTS&t;(0x0c + MMU_REG_BASE)&t;/* MMU Exception Status Register */
DECL|macro|MDEVA
mdefine_line|#define MDEVA&t;(0x10 + MMU_REG_BASE)&t;/* MMU Operand Exception Virtual&n;&t;&t;&t;&t;&t;   Address Register */
DECL|macro|MDEVP
mdefine_line|#define MDEVP&t;(0x14 + MMU_REG_BASE)&t;/* MMU Operand Exception Virtual Page&n;&t;&t;&t;&t;&t;   Number Register */
DECL|macro|MPTB
mdefine_line|#define MPTB&t;(0x18 + MMU_REG_BASE)&t;/* MMU Page Table Base Register */
DECL|macro|MSVA
mdefine_line|#define MSVA&t;(0x20 + MMU_REG_BASE)&t;/* MMU Search Virtual Address&n;&t;&t;&t;&t;&t;   Register */
DECL|macro|MTOP
mdefine_line|#define MTOP&t;(0x24 + MMU_REG_BASE)&t;/* MMU TLB Operation Register */
DECL|macro|MIDXI
mdefine_line|#define MIDXI&t;(0x28 + MMU_REG_BASE)&t;/* MMU Index Register for&n;&t;&t;&t;&t;&t;   Instruciton */
DECL|macro|MIDXD
mdefine_line|#define MIDXD&t;(0x2c + MMU_REG_BASE)&t;/* MMU Index Register for Operand */
DECL|macro|MATM_offset
mdefine_line|#define MATM_offset&t;(MATM - MMU_REG_BASE)
DECL|macro|MPSZ_offset
mdefine_line|#define MPSZ_offset&t;(MPSZ - MMU_REG_BASE)
DECL|macro|MASID_offset
mdefine_line|#define MASID_offset&t;(MASID - MMU_REG_BASE)
DECL|macro|MESTS_offset
mdefine_line|#define MESTS_offset&t;(MESTS - MMU_REG_BASE)
DECL|macro|MDEVA_offset
mdefine_line|#define MDEVA_offset&t;(MDEVA - MMU_REG_BASE)
DECL|macro|MDEVP_offset
mdefine_line|#define MDEVP_offset&t;(MDEVP - MMU_REG_BASE)
DECL|macro|MPTB_offset
mdefine_line|#define MPTB_offset&t;(MPTB - MMU_REG_BASE)
DECL|macro|MSVA_offset
mdefine_line|#define MSVA_offset&t;(MSVA - MMU_REG_BASE)
DECL|macro|MTOP_offset
mdefine_line|#define MTOP_offset&t;(MTOP - MMU_REG_BASE)
DECL|macro|MIDXI_offset
mdefine_line|#define MIDXI_offset&t;(MIDXI - MMU_REG_BASE)
DECL|macro|MIDXD_offset
mdefine_line|#define MIDXD_offset&t;(MIDXD - MMU_REG_BASE)
DECL|macro|MESTS_IT
mdefine_line|#define MESTS_IT&t;(1 &lt;&lt; 0)&t;/* Instruction TLB miss */
DECL|macro|MESTS_IA
mdefine_line|#define MESTS_IA&t;(1 &lt;&lt; 1)&t;/* Instruction Access Exception */
DECL|macro|MESTS_DT
mdefine_line|#define MESTS_DT&t;(1 &lt;&lt; 4)&t;/* Operand TLB miss */
DECL|macro|MESTS_DA
mdefine_line|#define MESTS_DA&t;(1 &lt;&lt; 5)&t;/* Operand Access Exception */
DECL|macro|MESTS_DRW
mdefine_line|#define MESTS_DRW&t;(1 &lt;&lt; 6)&t;/* Operand Write Exception Flag */
multiline_comment|/*&n; * PSW (Processor Status Word)&n; */
multiline_comment|/* PSW bit */
DECL|macro|M32R_PSW_BIT_SM
mdefine_line|#define M32R_PSW_BIT_SM   (7)    /* Stack Mode */
DECL|macro|M32R_PSW_BIT_IE
mdefine_line|#define M32R_PSW_BIT_IE   (6)    /* Interrupt Enable */
DECL|macro|M32R_PSW_BIT_PM
mdefine_line|#define M32R_PSW_BIT_PM   (3)    /* Processor Mode [0:Supervisor,1:User] */
DECL|macro|M32R_PSW_BIT_C
mdefine_line|#define M32R_PSW_BIT_C    (0)    /* Condition */
DECL|macro|M32R_PSW_BIT_BSM
mdefine_line|#define M32R_PSW_BIT_BSM  (7+8)  /* Backup Stack Mode */
DECL|macro|M32R_PSW_BIT_BIE
mdefine_line|#define M32R_PSW_BIT_BIE  (6+8)  /* Backup Interrupt Enable */
DECL|macro|M32R_PSW_BIT_BPM
mdefine_line|#define M32R_PSW_BIT_BPM  (3+8)  /* Backup Processor Mode */
DECL|macro|M32R_PSW_BIT_BC
mdefine_line|#define M32R_PSW_BIT_BC   (0+8)  /* Backup Condition */
multiline_comment|/* PSW bit map */
DECL|macro|M32R_PSW_SM
mdefine_line|#define M32R_PSW_SM   (1UL&lt;&lt; M32R_PSW_BIT_SM)   /* Stack Mode */
DECL|macro|M32R_PSW_IE
mdefine_line|#define M32R_PSW_IE   (1UL&lt;&lt; M32R_PSW_BIT_IE)   /* Interrupt Enable */
DECL|macro|M32R_PSW_PM
mdefine_line|#define M32R_PSW_PM   (1UL&lt;&lt; M32R_PSW_BIT_PM)   /* Processor Mode */
DECL|macro|M32R_PSW_C
mdefine_line|#define M32R_PSW_C    (1UL&lt;&lt; M32R_PSW_BIT_C)    /* Condition */
DECL|macro|M32R_PSW_BSM
mdefine_line|#define M32R_PSW_BSM  (1UL&lt;&lt; M32R_PSW_BIT_BSM)  /* Backup Stack Mode */
DECL|macro|M32R_PSW_BIE
mdefine_line|#define M32R_PSW_BIE  (1UL&lt;&lt; M32R_PSW_BIT_BIE)  /* Backup Interrupt Enable */
DECL|macro|M32R_PSW_BPM
mdefine_line|#define M32R_PSW_BPM  (1UL&lt;&lt; M32R_PSW_BIT_BPM)  /* Backup Processor Mode */
DECL|macro|M32R_PSW_BC
mdefine_line|#define M32R_PSW_BC   (1UL&lt;&lt; M32R_PSW_BIT_BC)   /* Backup Condition */
multiline_comment|/*&n; * Direct address to SFR&n; */
macro_line|#include &lt;asm/page.h&gt;
macro_line|#ifdef CONFIG_MMU
DECL|macro|NONCACHE_OFFSET
mdefine_line|#define NONCACHE_OFFSET  __PAGE_OFFSET+0x20000000
macro_line|#else
DECL|macro|NONCACHE_OFFSET
mdefine_line|#define NONCACHE_OFFSET  __PAGE_OFFSET
macro_line|#endif /* CONFIG_MMU */
DECL|macro|M32R_ICU_ISTS_ADDR
mdefine_line|#define M32R_ICU_ISTS_ADDR  M32R_ICU_ISTS_PORTL+NONCACHE_OFFSET
DECL|macro|M32R_ICU_IPICR_ADDR
mdefine_line|#define M32R_ICU_IPICR_ADDR  M32R_ICU_IPICR0_PORTL+NONCACHE_OFFSET
DECL|macro|M32R_ICU_IMASK_ADDR
mdefine_line|#define M32R_ICU_IMASK_ADDR  M32R_ICU_IMASK_PORTL+NONCACHE_OFFSET
DECL|macro|M32R_FPGA_CPU_NAME_ADDR
mdefine_line|#define M32R_FPGA_CPU_NAME_ADDR  M32R_FPGA_CPU_NAME0_PORTL+NONCACHE_OFFSET
DECL|macro|M32R_FPGA_MODEL_ID_ADDR
mdefine_line|#define M32R_FPGA_MODEL_ID_ADDR  M32R_FPGA_MODEL_ID0_PORTL+NONCACHE_OFFSET
DECL|macro|M32R_FPGA_VERSION_ADDR
mdefine_line|#define M32R_FPGA_VERSION_ADDR   M32R_FPGA_VERSION0_PORTL+NONCACHE_OFFSET
macro_line|#endif /* _ASM_M32R_M32R_H_ */
eof
