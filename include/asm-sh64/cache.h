macro_line|#ifndef __ASM_SH64_CACHE_H
DECL|macro|__ASM_SH64_CACHE_H
mdefine_line|#define __ASM_SH64_CACHE_H
multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * include/asm-sh64/cache.h&n; *&n; * Copyright (C) 2000, 2001  Paolo Alberelli&n; * Copyright (C) 2003, 2004  Paul Mundt&n; *&n; */
macro_line|#include &lt;asm/cacheflush.h&gt;
DECL|macro|L1_CACHE_SHIFT
mdefine_line|#define L1_CACHE_SHIFT&t;&t;5
multiline_comment|/* bytes per L1 cache line */
DECL|macro|L1_CACHE_BYTES
mdefine_line|#define L1_CACHE_BYTES&t;&t;(1 &lt;&lt; L1_CACHE_SHIFT)
DECL|macro|L1_CACHE_ALIGN_MASK
mdefine_line|#define L1_CACHE_ALIGN_MASK&t;(~(L1_CACHE_BYTES - 1))
DECL|macro|L1_CACHE_ALIGN
mdefine_line|#define L1_CACHE_ALIGN(x)&t;(((x)+(L1_CACHE_BYTES - 1)) &amp; L1_CACHE_ALIGN_MASK)
DECL|macro|L1_CACHE_SIZE_BYTES
mdefine_line|#define L1_CACHE_SIZE_BYTES&t;(L1_CACHE_BYTES &lt;&lt; 10)
multiline_comment|/* Largest L1 which this arch supports */
DECL|macro|L1_CACHE_SHIFT_MAX
mdefine_line|#define L1_CACHE_SHIFT_MAX&t;5
macro_line|#ifdef MODULE
DECL|macro|__cacheline_aligned
mdefine_line|#define __cacheline_aligned __attribute__((__aligned__(L1_CACHE_BYTES)))
macro_line|#else
DECL|macro|__cacheline_aligned
mdefine_line|#define __cacheline_aligned&t;&t;&t;&t;&t;&bslash;&n;  __attribute__((__aligned__(L1_CACHE_BYTES),&t;&t;&t;&bslash;&n;&t;&t; __section__(&quot;.data.cacheline_aligned&quot;)))
macro_line|#endif
multiline_comment|/*&n; * Control Registers.&n; */
DECL|macro|ICCR_BASE
mdefine_line|#define ICCR_BASE&t;0x01600000&t;/* Instruction Cache Control Register */
DECL|macro|ICCR_REG0
mdefine_line|#define ICCR_REG0&t;0&t;&t;/* Register 0 offset */
DECL|macro|ICCR_REG1
mdefine_line|#define ICCR_REG1&t;1&t;&t;/* Register 1 offset */
DECL|macro|ICCR0
mdefine_line|#define ICCR0&t;&t;ICCR_BASE+ICCR_REG0
DECL|macro|ICCR1
mdefine_line|#define ICCR1&t;&t;ICCR_BASE+ICCR_REG1
DECL|macro|ICCR0_OFF
mdefine_line|#define ICCR0_OFF&t;0x0&t;&t;/* Set ICACHE off */
DECL|macro|ICCR0_ON
mdefine_line|#define ICCR0_ON&t;0x1&t;&t;/* Set ICACHE on */
DECL|macro|ICCR0_ICI
mdefine_line|#define ICCR0_ICI&t;0x2&t;&t;/* Invalidate all in IC */
DECL|macro|ICCR1_NOLOCK
mdefine_line|#define ICCR1_NOLOCK&t;0x0&t;&t;/* Set No Locking */
DECL|macro|OCCR_BASE
mdefine_line|#define OCCR_BASE&t;0x01E00000&t;/* Operand Cache Control Register */
DECL|macro|OCCR_REG0
mdefine_line|#define OCCR_REG0&t;0&t;&t;/* Register 0 offset */
DECL|macro|OCCR_REG1
mdefine_line|#define OCCR_REG1&t;1&t;&t;/* Register 1 offset */
DECL|macro|OCCR0
mdefine_line|#define OCCR0&t;&t;OCCR_BASE+OCCR_REG0
DECL|macro|OCCR1
mdefine_line|#define OCCR1&t;&t;OCCR_BASE+OCCR_REG1
DECL|macro|OCCR0_OFF
mdefine_line|#define OCCR0_OFF&t;0x0&t;&t;/* Set OCACHE off */
DECL|macro|OCCR0_ON
mdefine_line|#define OCCR0_ON&t;0x1&t;&t;/* Set OCACHE on */
DECL|macro|OCCR0_OCI
mdefine_line|#define OCCR0_OCI&t;0x2&t;&t;/* Invalidate all in OC */
DECL|macro|OCCR0_WT
mdefine_line|#define OCCR0_WT&t;0x4&t;&t;/* Set OCACHE in WT Mode */
DECL|macro|OCCR0_WB
mdefine_line|#define OCCR0_WB&t;0x0&t;&t;/* Set OCACHE in WB Mode */
DECL|macro|OCCR1_NOLOCK
mdefine_line|#define OCCR1_NOLOCK&t;0x0&t;&t;/* Set No Locking */
multiline_comment|/*&n; * SH-5&n; * A bit of description here, for neff=32.&n; *&n; *                               |&lt;--- tag  (19 bits) ---&gt;|&n; * +-----------------------------+-----------------+------+----------+------+&n; * |                             |                 | ways |set index |offset|&n; * +-----------------------------+-----------------+------+----------+------+&n; *                                ^                 2 bits   8 bits   5 bits&n; *                                +- Bit 31&n; *&n; * Cacheline size is based on offset: 5 bits = 32 bytes per line&n; * A cache line is identified by a tag + set but OCACHETAG/ICACHETAG&n; * have a broader space for registers. These are outlined by&n; * CACHE_?C_*_STEP below.&n; *&n; */
multiline_comment|/* Valid and Dirty bits */
DECL|macro|SH_CACHE_VALID
mdefine_line|#define SH_CACHE_VALID&t;&t;(1LL&lt;&lt;0)
DECL|macro|SH_CACHE_UPDATED
mdefine_line|#define SH_CACHE_UPDATED&t;(1LL&lt;&lt;57)
multiline_comment|/* Cache flags */
DECL|macro|SH_CACHE_MODE_WT
mdefine_line|#define SH_CACHE_MODE_WT&t;(1LL&lt;&lt;0)
DECL|macro|SH_CACHE_MODE_WB
mdefine_line|#define SH_CACHE_MODE_WB&t;(1LL&lt;&lt;1)
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/*&n; * Cache information structure.&n; *&n; * Defined for both I and D cache, per-processor.&n; */
DECL|struct|cache_info
r_struct
id|cache_info
(brace
DECL|member|ways
r_int
r_int
id|ways
suffix:semicolon
DECL|member|sets
r_int
r_int
id|sets
suffix:semicolon
DECL|member|linesz
r_int
r_int
id|linesz
suffix:semicolon
DECL|member|way_shift
r_int
r_int
id|way_shift
suffix:semicolon
DECL|member|entry_shift
r_int
r_int
id|entry_shift
suffix:semicolon
DECL|member|set_shift
r_int
r_int
id|set_shift
suffix:semicolon
DECL|member|way_step_shift
r_int
r_int
id|way_step_shift
suffix:semicolon
DECL|member|asid_shift
r_int
r_int
id|asid_shift
suffix:semicolon
DECL|member|way_ofs
r_int
r_int
id|way_ofs
suffix:semicolon
DECL|member|asid_mask
r_int
r_int
id|asid_mask
suffix:semicolon
DECL|member|idx_mask
r_int
r_int
id|idx_mask
suffix:semicolon
DECL|member|epn_mask
r_int
r_int
id|epn_mask
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* __ASSEMBLY__ */
multiline_comment|/* Instruction cache */
DECL|macro|CACHE_IC_ADDRESS_ARRAY
mdefine_line|#define CACHE_IC_ADDRESS_ARRAY 0x01000000
multiline_comment|/* Operand Cache */
DECL|macro|CACHE_OC_ADDRESS_ARRAY
mdefine_line|#define CACHE_OC_ADDRESS_ARRAY 0x01800000
multiline_comment|/* These declarations relate to cache &squot;synonyms&squot; in the operand cache.  A&n;   &squot;synonym&squot; occurs where effective address bits overlap between those used for&n;   indexing the cache sets and those passed to the MMU for translation.  In the&n;   case of SH5-101 &amp; SH5-103, only bit 12 is affected for 4k pages. */
DECL|macro|CACHE_OC_N_SYNBITS
mdefine_line|#define CACHE_OC_N_SYNBITS  1               /* Number of synonym bits */
DECL|macro|CACHE_OC_SYN_SHIFT
mdefine_line|#define CACHE_OC_SYN_SHIFT  12
multiline_comment|/* Mask to select synonym bit(s) */
DECL|macro|CACHE_OC_SYN_MASK
mdefine_line|#define CACHE_OC_SYN_MASK   (((1UL&lt;&lt;CACHE_OC_N_SYNBITS)-1)&lt;&lt;CACHE_OC_SYN_SHIFT)
multiline_comment|/*&n; * Instruction cache can&squot;t be invalidated based on physical addresses.&n; * No Instruction Cache defines required, then.&n; */
macro_line|#endif /* __ASM_SH64_CACHE_H */
eof
