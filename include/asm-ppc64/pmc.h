multiline_comment|/* &n; * pmc.h&n; * Copyright (C) 2001  Dave Engebretsen &amp; Mike Corrigan IBM Corporation.&n; *&n; * The PPC64 PMC subsystem encompases both the hardware PMC registers and &n; * a set of software event counters.  An interface is provided via the&n; * proc filesystem which can be used to access this subsystem.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; * &n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
multiline_comment|/* Start Change Log&n; * 2001/06/05 : engebret : Created.&n; * End Change Log &n; */
macro_line|#ifndef _PPC64_TYPES_H
macro_line|#include        &lt;asm/types.h&gt;
macro_line|#endif
macro_line|#ifndef _PMC_H
DECL|macro|_PMC_H
mdefine_line|#define _PMC_H
DECL|macro|STAB_ENTRY_MAX
mdefine_line|#define STAB_ENTRY_MAX 64
DECL|struct|_pmc_hw
r_struct
id|_pmc_hw
(brace
DECL|member|mmcr0
id|u64
id|mmcr0
suffix:semicolon
DECL|member|mmcr1
id|u64
id|mmcr1
suffix:semicolon
DECL|member|mmcra
id|u64
id|mmcra
suffix:semicolon
DECL|member|pmc1
id|u64
id|pmc1
suffix:semicolon
DECL|member|pmc2
id|u64
id|pmc2
suffix:semicolon
DECL|member|pmc3
id|u64
id|pmc3
suffix:semicolon
DECL|member|pmc4
id|u64
id|pmc4
suffix:semicolon
DECL|member|pmc5
id|u64
id|pmc5
suffix:semicolon
DECL|member|pmc6
id|u64
id|pmc6
suffix:semicolon
DECL|member|pmc7
id|u64
id|pmc7
suffix:semicolon
DECL|member|pmc8
id|u64
id|pmc8
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|_pmc_sw
r_struct
id|_pmc_sw
(brace
DECL|member|stab_faults
id|u64
id|stab_faults
suffix:semicolon
multiline_comment|/* Count of faults on the stab      */
DECL|member|stab_capacity_castouts
id|u64
id|stab_capacity_castouts
suffix:semicolon
multiline_comment|/* Count of castouts from the stab  */
DECL|member|stab_invalidations
id|u64
id|stab_invalidations
suffix:semicolon
multiline_comment|/* Count of invalidations from the  */
multiline_comment|/*   stab, not including castouts   */
DECL|member|stab_entry_use
id|u64
id|stab_entry_use
(braket
id|STAB_ENTRY_MAX
)braket
suffix:semicolon
DECL|member|htab_primary_overflows
id|u64
id|htab_primary_overflows
suffix:semicolon
DECL|member|htab_capacity_castouts
id|u64
id|htab_capacity_castouts
suffix:semicolon
DECL|member|htab_read_to_write_fault
id|u64
id|htab_read_to_write_fault
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|PMC_HW_TEXT_ENTRY_COUNT
mdefine_line|#define PMC_HW_TEXT_ENTRY_COUNT (sizeof(struct _pmc_hw) / sizeof(u64))
DECL|macro|PMC_SW_TEXT_ENTRY_COUNT
mdefine_line|#define PMC_SW_TEXT_ENTRY_COUNT (sizeof(struct _pmc_sw) / sizeof(u64))
DECL|macro|PMC_TEXT_ENTRY_SIZE
mdefine_line|#define PMC_TEXT_ENTRY_SIZE  64
DECL|struct|_pmc_sw_text
r_struct
id|_pmc_sw_text
(brace
DECL|member|buffer
r_char
id|buffer
(braket
id|PMC_SW_TEXT_ENTRY_COUNT
op_star
id|PMC_TEXT_ENTRY_SIZE
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|_pmc_hw_text
r_struct
id|_pmc_hw_text
(brace
DECL|member|buffer
r_char
id|buffer
(braket
id|PMC_HW_TEXT_ENTRY_COUNT
op_star
id|PMC_TEXT_ENTRY_SIZE
)braket
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|_pmc_sw
id|pmc_sw_system
suffix:semicolon
r_extern
r_struct
id|_pmc_sw
id|pmc_sw_cpu
(braket
)braket
suffix:semicolon
r_extern
r_struct
id|_pmc_sw_text
id|pmc_sw_text
suffix:semicolon
r_extern
r_struct
id|_pmc_hw_text
id|pmc_hw_text
suffix:semicolon
r_extern
r_char
op_star
id|ppc64_pmc_stab
c_func
(paren
r_int
id|file
)paren
suffix:semicolon
r_extern
r_char
op_star
id|ppc64_pmc_htab
c_func
(paren
r_int
id|file
)paren
suffix:semicolon
r_extern
r_char
op_star
id|ppc64_pmc_hw
c_func
(paren
r_int
id|file
)paren
suffix:semicolon
macro_line|#if 1
DECL|macro|PMC_SW_PROCESSOR
mdefine_line|#define PMC_SW_PROCESSOR(F)      pmc_sw_cpu[smp_processor_id()].F++
DECL|macro|PMC_SW_PROCESSOR_A
mdefine_line|#define PMC_SW_PROCESSOR_A(F, E) (pmc_sw_cpu[smp_processor_id()].F[(E)])++
DECL|macro|PMC_SW_SYSTEM
mdefine_line|#define PMC_SW_SYSTEM(F)         pmc_sw_system.F++
macro_line|#else
DECL|macro|PMC_SW_PROCESSOR
mdefine_line|#define PMC_SW_PROCESSOR(F)   do {;} while (0)
DECL|macro|PMC_SW_PROCESSOR_A
mdefine_line|#define PMC_SW_PROCESSOR_A(F) do {;} while (0)
DECL|macro|PMC_SW_SYSTEM
mdefine_line|#define PMC_SW_SYSTEM(F)      do {;} while (0)
macro_line|#endif
DECL|macro|MMCR0
mdefine_line|#define MMCR0 795
DECL|macro|MMCR1
mdefine_line|#define MMCR1 798
DECL|macro|MMCRA
mdefine_line|#define MMCRA 786
DECL|macro|PMC1
mdefine_line|#define PMC1  787
DECL|macro|PMC2
mdefine_line|#define PMC2  788
DECL|macro|PMC3
mdefine_line|#define PMC3  789
DECL|macro|PMC4
mdefine_line|#define PMC4  790
DECL|macro|PMC5
mdefine_line|#define PMC5  791
DECL|macro|PMC6
mdefine_line|#define PMC6  792
DECL|macro|PMC7
mdefine_line|#define PMC7  793
DECL|macro|PMC8
mdefine_line|#define PMC8  794
DECL|macro|PMC_CONTROL_CPI
mdefine_line|#define PMC_CONTROL_CPI 1
DECL|macro|PMC_CONTROL_TLB
mdefine_line|#define PMC_CONTROL_TLB 2
macro_line|#endif /* _PMC_H */
eof
