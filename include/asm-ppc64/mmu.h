multiline_comment|/*&n; * PowerPC memory management structures&n; *&n; * Dave Engebretsen &amp; Mike Corrigan &lt;{engebret|mikejc}@us.ibm.com&gt;&n; *   PPC64 rework.&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _PPC64_MMU_H_
DECL|macro|_PPC64_MMU_H_
mdefine_line|#define _PPC64_MMU_H_
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/* Time to allow for more things here */
DECL|typedef|mm_context_id_t
r_typedef
r_int
r_int
id|mm_context_id_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|id
id|mm_context_id_t
id|id
suffix:semicolon
macro_line|#ifdef CONFIG_HUGETLB_PAGE
DECL|member|htlb_segs
id|u16
id|htlb_segs
suffix:semicolon
multiline_comment|/* bitmask */
macro_line|#endif
DECL|typedef|mm_context_t
)brace
id|mm_context_t
suffix:semicolon
macro_line|#ifdef CONFIG_HUGETLB_PAGE
DECL|macro|KERNEL_LOW_HPAGES
mdefine_line|#define KERNEL_LOW_HPAGES&t;.htlb_segs = 0,
macro_line|#else
DECL|macro|KERNEL_LOW_HPAGES
mdefine_line|#define KERNEL_LOW_HPAGES
macro_line|#endif
DECL|macro|KERNEL_CONTEXT
mdefine_line|#define KERNEL_CONTEXT(ea) ({ &bslash;&n;&t;&t;mm_context_t ctx = { .id = REGION_ID(ea), KERNEL_LOW_HPAGES}; &bslash;&n;&t;&t;ctx; })
r_typedef
r_struct
(brace
DECL|member|esid
r_int
r_int
id|esid
suffix:colon
l_int|36
suffix:semicolon
multiline_comment|/* Effective segment ID */
DECL|member|resv0
r_int
r_int
id|resv0
suffix:colon
l_int|20
suffix:semicolon
multiline_comment|/* Reserved */
DECL|member|v
r_int
r_int
id|v
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Entry valid (v=1) or invalid */
DECL|member|resv1
r_int
r_int
id|resv1
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Reserved */
DECL|member|ks
r_int
r_int
id|ks
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Supervisor (privileged) state storage key */
DECL|member|kp
r_int
r_int
id|kp
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Problem state storage key */
DECL|member|n
r_int
r_int
id|n
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* No-execute if n=1 */
DECL|member|resv2
r_int
r_int
id|resv2
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* padding to a 64b boundary */
DECL|typedef|ste_dword0
)brace
id|ste_dword0
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|vsid
r_int
r_int
id|vsid
suffix:colon
l_int|52
suffix:semicolon
multiline_comment|/* Virtual segment ID */
DECL|member|resv0
r_int
r_int
id|resv0
suffix:colon
l_int|12
suffix:semicolon
multiline_comment|/* Padding to a 64b boundary */
DECL|typedef|ste_dword1
)brace
id|ste_dword1
suffix:semicolon
DECL|struct|_STE
r_typedef
r_struct
id|_STE
(brace
r_union
(brace
DECL|member|dword0
r_int
r_int
id|dword0
suffix:semicolon
DECL|member|dw0
id|ste_dword0
id|dw0
suffix:semicolon
DECL|member|dw0
)brace
id|dw0
suffix:semicolon
r_union
(brace
DECL|member|dword1
r_int
r_int
id|dword1
suffix:semicolon
DECL|member|dw1
id|ste_dword1
id|dw1
suffix:semicolon
DECL|member|dw1
)brace
id|dw1
suffix:semicolon
DECL|typedef|STE
)brace
id|STE
suffix:semicolon
multiline_comment|/* Hardware Page Table Entry */
DECL|macro|HPTES_PER_GROUP
mdefine_line|#define HPTES_PER_GROUP 8
r_typedef
r_struct
(brace
DECL|member|avpn
r_int
r_int
id|avpn
suffix:colon
l_int|57
suffix:semicolon
multiline_comment|/* vsid | api == avpn  */
r_int
r_int
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* Software use */
DECL|member|bolted
r_int
r_int
id|bolted
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* HPTE is &quot;bolted&quot; */
DECL|member|lock
r_int
r_int
id|lock
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* lock on pSeries SMP */
DECL|member|l
r_int
r_int
id|l
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Virtual page is large (L=1) or 4 KB (L=0) */
DECL|member|h
r_int
r_int
id|h
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Hash function identifier */
DECL|member|v
r_int
r_int
id|v
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Valid (v=1) or invalid (v=0) */
DECL|typedef|Hpte_dword0
)brace
id|Hpte_dword0
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|pp0
r_int
r_int
id|pp0
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Page protection bit 0 */
DECL|member|ts
r_int
r_int
id|ts
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Tag set bit */
DECL|member|rpn
r_int
r_int
id|rpn
suffix:colon
l_int|50
suffix:semicolon
multiline_comment|/* Real page number */
r_int
r_int
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* Reserved */
DECL|member|ac
r_int
r_int
id|ac
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Address compare */
DECL|member|r
r_int
r_int
id|r
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Referenced */
DECL|member|c
r_int
r_int
id|c
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Changed */
DECL|member|w
r_int
r_int
id|w
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Write-thru cache mode */
DECL|member|i
r_int
r_int
id|i
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Cache inhibited */
DECL|member|m
r_int
r_int
id|m
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Memory coherence required */
DECL|member|g
r_int
r_int
id|g
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Guarded */
DECL|member|n
r_int
r_int
id|n
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* No-execute */
DECL|member|pp
r_int
r_int
id|pp
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* Page protection bits 1:2 */
DECL|typedef|Hpte_dword1
)brace
id|Hpte_dword1
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|padding
r_char
id|padding
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* padding */
r_int
r_int
suffix:colon
l_int|6
suffix:semicolon
multiline_comment|/* padding */
DECL|member|flags
r_int
r_int
id|flags
suffix:colon
l_int|10
suffix:semicolon
multiline_comment|/* HPTE flags */
DECL|typedef|Hpte_dword1_flags
)brace
id|Hpte_dword1_flags
suffix:semicolon
r_typedef
r_struct
(brace
r_union
(brace
DECL|member|dword0
r_int
r_int
id|dword0
suffix:semicolon
DECL|member|dw0
id|Hpte_dword0
id|dw0
suffix:semicolon
DECL|member|dw0
)brace
id|dw0
suffix:semicolon
r_union
(brace
DECL|member|dword1
r_int
r_int
id|dword1
suffix:semicolon
DECL|member|dw1
id|Hpte_dword1
id|dw1
suffix:semicolon
DECL|member|flags
id|Hpte_dword1_flags
id|flags
suffix:semicolon
DECL|member|dw1
)brace
id|dw1
suffix:semicolon
DECL|typedef|HPTE
)brace
id|HPTE
suffix:semicolon
multiline_comment|/* Values for PP (assumes Ks=0, Kp=1) */
multiline_comment|/* pp0 will always be 0 for linux     */
DECL|macro|PP_RWXX
mdefine_line|#define PP_RWXX&t;0&t;/* Supervisor read/write, User none */
DECL|macro|PP_RWRX
mdefine_line|#define PP_RWRX 1&t;/* Supervisor read/write, User read */
DECL|macro|PP_RWRW
mdefine_line|#define PP_RWRW 2&t;/* Supervisor read/write, User read/write */
DECL|macro|PP_RXRX
mdefine_line|#define PP_RXRX 3&t;/* Supervisor read,       User read */
r_typedef
r_struct
(brace
DECL|member|htab
id|HPTE
op_star
id|htab
suffix:semicolon
DECL|member|htab_num_ptegs
r_int
r_int
id|htab_num_ptegs
suffix:semicolon
DECL|member|htab_hash_mask
r_int
r_int
id|htab_hash_mask
suffix:semicolon
DECL|member|next_round_robin
r_int
r_int
id|next_round_robin
suffix:semicolon
DECL|member|last_kernel_address
r_int
r_int
id|last_kernel_address
suffix:semicolon
DECL|typedef|HTAB
)brace
id|HTAB
suffix:semicolon
r_extern
id|HTAB
id|htab_data
suffix:semicolon
r_void
id|invalidate_hpte
c_func
(paren
r_int
r_int
id|slot
)paren
suffix:semicolon
r_int
id|select_hpte_slot
c_func
(paren
r_int
r_int
id|vpn
)paren
suffix:semicolon
r_void
id|create_valid_hpte
c_func
(paren
r_int
r_int
id|slot
comma
r_int
r_int
id|vpn
comma
r_int
r_int
id|prpn
comma
r_int
id|hash
comma
r_void
op_star
id|ptep
comma
r_int
id|hpteflags
comma
r_int
id|bolted
)paren
suffix:semicolon
DECL|macro|PD_SHIFT
mdefine_line|#define PD_SHIFT (10+12)&t;&t;/* Page directory */
DECL|macro|PD_MASK
mdefine_line|#define PD_MASK  0x02FF
DECL|macro|PT_SHIFT
mdefine_line|#define PT_SHIFT (12)&t;&t;&t;/* Page Table */
DECL|macro|PT_MASK
mdefine_line|#define PT_MASK  0x02FF
DECL|macro|LARGE_PAGE_SHIFT
mdefine_line|#define LARGE_PAGE_SHIFT 24
DECL|function|hpt_hash
r_static
r_inline
r_int
r_int
id|hpt_hash
c_func
(paren
r_int
r_int
id|vpn
comma
r_int
id|large
)paren
(brace
r_int
r_int
id|vsid
suffix:semicolon
r_int
r_int
id|page
suffix:semicolon
r_if
c_cond
(paren
id|large
)paren
(brace
id|vsid
op_assign
id|vpn
op_rshift
l_int|4
suffix:semicolon
id|page
op_assign
id|vpn
op_amp
l_int|0xf
suffix:semicolon
)brace
r_else
(brace
id|vsid
op_assign
id|vpn
op_rshift
l_int|16
suffix:semicolon
id|page
op_assign
id|vpn
op_amp
l_int|0xffff
suffix:semicolon
)brace
r_return
(paren
id|vsid
op_amp
l_int|0x7fffffffffUL
)paren
op_xor
id|page
suffix:semicolon
)brace
DECL|function|__tlbie
r_static
r_inline
r_void
id|__tlbie
c_func
(paren
r_int
r_int
id|va
comma
r_int
id|large
)paren
(brace
multiline_comment|/* clear top 16 bits, non SLS segment */
id|va
op_and_assign
op_complement
(paren
l_int|0xffffULL
op_lshift
l_int|48
)paren
suffix:semicolon
r_if
c_cond
(paren
id|large
)paren
id|asm
r_volatile
(paren
l_string|&quot;tlbie %0,1&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|va
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_else
id|asm
r_volatile
(paren
l_string|&quot;tlbie %0,0&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|va
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
DECL|function|tlbie
r_static
r_inline
r_void
id|tlbie
c_func
(paren
r_int
r_int
id|va
comma
r_int
id|large
)paren
(brace
id|asm
r_volatile
(paren
l_string|&quot;ptesync&quot;
suffix:colon
suffix:colon
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
id|__tlbie
c_func
(paren
id|va
comma
id|large
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;eieio; tlbsync; ptesync&quot;
suffix:colon
suffix:colon
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
DECL|function|__tlbiel
r_static
r_inline
r_void
id|__tlbiel
c_func
(paren
r_int
r_int
id|va
)paren
(brace
multiline_comment|/* clear top 16 bits, non SLS segment */
id|va
op_and_assign
op_complement
(paren
l_int|0xffffULL
op_lshift
l_int|48
)paren
suffix:semicolon
multiline_comment|/* &n;&t; * Thanks to Alan Modra we are now able to use machine specific &n;&t; * assembly instructions (like tlbiel) by using the gas -many flag.&n;&t; * However we have to support older toolchains so for the moment &n;&t; * we hardwire it.&n;&t; */
macro_line|#if 0
id|asm
r_volatile
(paren
l_string|&quot;tlbiel %0&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|va
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
macro_line|#else
id|asm
r_volatile
(paren
l_string|&quot;.long 0x7c000224 | (%0 &lt;&lt; 11)&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|va
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|function|tlbiel
r_static
r_inline
r_void
id|tlbiel
c_func
(paren
r_int
r_int
id|va
)paren
(brace
id|asm
r_volatile
(paren
l_string|&quot;ptesync&quot;
suffix:colon
suffix:colon
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
id|__tlbiel
c_func
(paren
id|va
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;ptesync&quot;
suffix:colon
suffix:colon
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Handle a fault by adding an HPTE. If the address can&squot;t be determined&n; * to be valid via Linux page tables, return 1. If handled return 0&n; */
r_extern
r_int
id|__hash_page
c_func
(paren
r_int
r_int
id|ea
comma
r_int
r_int
id|access
comma
r_int
r_int
id|vsid
comma
id|pte_t
op_star
id|ptep
comma
r_int
r_int
id|trap
comma
r_int
id|local
)paren
suffix:semicolon
r_extern
r_void
id|htab_finish_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* __ASSEMBLY__ */
multiline_comment|/*&n; * Location of cpu0&squot;s segment table&n; */
DECL|macro|STAB0_PAGE
mdefine_line|#define STAB0_PAGE&t;0x9
DECL|macro|STAB0_PHYS_ADDR
mdefine_line|#define STAB0_PHYS_ADDR&t;(STAB0_PAGE&lt;&lt;PAGE_SHIFT)
DECL|macro|STAB0_VIRT_ADDR
mdefine_line|#define STAB0_VIRT_ADDR&t;(KERNELBASE+STAB0_PHYS_ADDR)
DECL|macro|SLB_NUM_BOLTED
mdefine_line|#define SLB_NUM_BOLTED&t;&t;2
DECL|macro|SLB_CACHE_ENTRIES
mdefine_line|#define SLB_CACHE_ENTRIES&t;8
multiline_comment|/* Bits in the SLB ESID word */
DECL|macro|SLB_ESID_V
mdefine_line|#define SLB_ESID_V&t;&t;0x0000000008000000&t;/* entry is valid */
multiline_comment|/* Bits in the SLB VSID word */
DECL|macro|SLB_VSID_SHIFT
mdefine_line|#define SLB_VSID_SHIFT&t;&t;12
DECL|macro|SLB_VSID_KS
mdefine_line|#define SLB_VSID_KS&t;&t;0x0000000000000800
DECL|macro|SLB_VSID_KP
mdefine_line|#define SLB_VSID_KP&t;&t;0x0000000000000400
DECL|macro|SLB_VSID_N
mdefine_line|#define SLB_VSID_N&t;&t;0x0000000000000200&t;/* no-execute */
DECL|macro|SLB_VSID_L
mdefine_line|#define SLB_VSID_L&t;&t;0x0000000000000100&t;/* largepage (4M) */
DECL|macro|SLB_VSID_C
mdefine_line|#define SLB_VSID_C&t;&t;0x0000000000000080&t;/* class */
DECL|macro|SLB_VSID_KERNEL
mdefine_line|#define SLB_VSID_KERNEL&t;&t;(SLB_VSID_KP|SLB_VSID_C)
DECL|macro|SLB_VSID_USER
mdefine_line|#define SLB_VSID_USER&t;&t;(SLB_VSID_KP|SLB_VSID_KS)
DECL|macro|VSID_RANDOMIZER
mdefine_line|#define VSID_RANDOMIZER ASM_CONST(42470972311)
DECL|macro|VSID_MASK
mdefine_line|#define VSID_MASK&t;0xfffffffffUL
multiline_comment|/* Because we never access addresses below KERNELBASE as kernel&n; * addresses, this VSID is never used for anything real, and will&n; * never have pages hashed into it */
DECL|macro|BAD_VSID
mdefine_line|#define BAD_VSID&t;ASM_CONST(0)
multiline_comment|/* Block size masks */
DECL|macro|BL_128K
mdefine_line|#define BL_128K&t;0x000
DECL|macro|BL_256K
mdefine_line|#define BL_256K 0x001
DECL|macro|BL_512K
mdefine_line|#define BL_512K 0x003
DECL|macro|BL_1M
mdefine_line|#define BL_1M   0x007
DECL|macro|BL_2M
mdefine_line|#define BL_2M   0x00F
DECL|macro|BL_4M
mdefine_line|#define BL_4M   0x01F
DECL|macro|BL_8M
mdefine_line|#define BL_8M   0x03F
DECL|macro|BL_16M
mdefine_line|#define BL_16M  0x07F
DECL|macro|BL_32M
mdefine_line|#define BL_32M  0x0FF
DECL|macro|BL_64M
mdefine_line|#define BL_64M  0x1FF
DECL|macro|BL_128M
mdefine_line|#define BL_128M 0x3FF
DECL|macro|BL_256M
mdefine_line|#define BL_256M 0x7FF
multiline_comment|/* Used to set up SDR1 register */
DECL|macro|HASH_TABLE_SIZE_64K
mdefine_line|#define HASH_TABLE_SIZE_64K&t;0x00010000
DECL|macro|HASH_TABLE_SIZE_128K
mdefine_line|#define HASH_TABLE_SIZE_128K&t;0x00020000
DECL|macro|HASH_TABLE_SIZE_256K
mdefine_line|#define HASH_TABLE_SIZE_256K&t;0x00040000
DECL|macro|HASH_TABLE_SIZE_512K
mdefine_line|#define HASH_TABLE_SIZE_512K&t;0x00080000
DECL|macro|HASH_TABLE_SIZE_1M
mdefine_line|#define HASH_TABLE_SIZE_1M&t;0x00100000
DECL|macro|HASH_TABLE_SIZE_2M
mdefine_line|#define HASH_TABLE_SIZE_2M&t;0x00200000
DECL|macro|HASH_TABLE_SIZE_4M
mdefine_line|#define HASH_TABLE_SIZE_4M&t;0x00400000
DECL|macro|HASH_TABLE_MASK_64K
mdefine_line|#define HASH_TABLE_MASK_64K&t;0x000   
DECL|macro|HASH_TABLE_MASK_128K
mdefine_line|#define HASH_TABLE_MASK_128K&t;0x001   
DECL|macro|HASH_TABLE_MASK_256K
mdefine_line|#define HASH_TABLE_MASK_256K&t;0x003   
DECL|macro|HASH_TABLE_MASK_512K
mdefine_line|#define HASH_TABLE_MASK_512K&t;0x007
DECL|macro|HASH_TABLE_MASK_1M
mdefine_line|#define HASH_TABLE_MASK_1M&t;0x00F   
DECL|macro|HASH_TABLE_MASK_2M
mdefine_line|#define HASH_TABLE_MASK_2M&t;0x01F   
DECL|macro|HASH_TABLE_MASK_4M
mdefine_line|#define HASH_TABLE_MASK_4M&t;0x03F   
multiline_comment|/* These are the Ks and Kp from the PowerPC books.  For proper operation,&n; * Ks = 0, Kp = 1.&n; */
DECL|macro|MI_AP
mdefine_line|#define MI_AP&t;&t;786
DECL|macro|MI_Ks
mdefine_line|#define MI_Ks&t;&t;0x80000000&t;/* Should not be set */
DECL|macro|MI_Kp
mdefine_line|#define MI_Kp&t;&t;0x40000000&t;/* Should always be set */
multiline_comment|/* The effective page number register.  When read, contains the information&n; * about the last instruction TLB miss.  When MI_RPN is written, bits in&n; * this register are used to create the TLB entry.&n; */
DECL|macro|MI_EPN
mdefine_line|#define MI_EPN&t;&t;787
DECL|macro|MI_EPNMASK
mdefine_line|#define MI_EPNMASK&t;0xfffff000&t;/* Effective page number for entry */
DECL|macro|MI_EVALID
mdefine_line|#define MI_EVALID&t;0x00000200&t;/* Entry is valid */
DECL|macro|MI_ASIDMASK
mdefine_line|#define MI_ASIDMASK&t;0x0000000f&t;/* ASID match value */
multiline_comment|/* Reset value is undefined */
multiline_comment|/* A &quot;level 1&quot; or &quot;segment&quot; or whatever you want to call it register.&n; * For the instruction TLB, it contains bits that get loaded into the&n; * TLB entry when the MI_RPN is written.&n; */
DECL|macro|MI_TWC
mdefine_line|#define MI_TWC&t;&t;789
DECL|macro|MI_APG
mdefine_line|#define MI_APG&t;&t;0x000001e0&t;/* Access protection group (0) */
DECL|macro|MI_GUARDED
mdefine_line|#define MI_GUARDED&t;0x00000010&t;/* Guarded storage */
DECL|macro|MI_PSMASK
mdefine_line|#define MI_PSMASK&t;0x0000000c&t;/* Mask of page size bits */
DECL|macro|MI_PS8MEG
mdefine_line|#define MI_PS8MEG&t;0x0000000c&t;/* 8M page size */
DECL|macro|MI_PS512K
mdefine_line|#define MI_PS512K&t;0x00000004&t;/* 512K page size */
DECL|macro|MI_PS4K_16K
mdefine_line|#define MI_PS4K_16K&t;0x00000000&t;/* 4K or 16K page size */
DECL|macro|MI_SVALID
mdefine_line|#define MI_SVALID&t;0x00000001&t;/* Segment entry is valid */
multiline_comment|/* Reset value is undefined */
multiline_comment|/* Real page number.  Defined by the pte.  Writing this register&n; * causes a TLB entry to be created for the instruction TLB, using&n; * additional information from the MI_EPN, and MI_TWC registers.&n; */
DECL|macro|MI_RPN
mdefine_line|#define MI_RPN&t;&t;790
multiline_comment|/* Define an RPN value for mapping kernel memory to large virtual&n; * pages for boot initialization.  This has real page number of 0,&n; * large page size, shared page, cache enabled, and valid.&n; * Also mark all subpages valid and write access.&n; */
DECL|macro|MI_BOOTINIT
mdefine_line|#define MI_BOOTINIT&t;0x000001fd
DECL|macro|MD_CTR
mdefine_line|#define MD_CTR&t;&t;792&t;/* Data TLB control register */
DECL|macro|MD_GPM
mdefine_line|#define MD_GPM&t;&t;0x80000000&t;/* Set domain manager mode */
DECL|macro|MD_PPM
mdefine_line|#define MD_PPM&t;&t;0x40000000&t;/* Set subpage protection */
DECL|macro|MD_CIDEF
mdefine_line|#define MD_CIDEF&t;0x20000000&t;/* Set cache inhibit when MMU dis */
DECL|macro|MD_WTDEF
mdefine_line|#define MD_WTDEF&t;0x10000000&t;/* Set writethrough when MMU dis */
DECL|macro|MD_RSV4I
mdefine_line|#define MD_RSV4I&t;0x08000000&t;/* Reserve 4 TLB entries */
DECL|macro|MD_TWAM
mdefine_line|#define MD_TWAM&t;&t;0x04000000&t;/* Use 4K page hardware assist */
DECL|macro|MD_PPCS
mdefine_line|#define MD_PPCS&t;&t;0x02000000&t;/* Use MI_RPN prob/priv state */
DECL|macro|MD_IDXMASK
mdefine_line|#define MD_IDXMASK&t;0x00001f00&t;/* TLB index to be loaded */
DECL|macro|MD_RESETVAL
mdefine_line|#define MD_RESETVAL&t;0x04000000&t;/* Value of register at reset */
DECL|macro|M_CASID
mdefine_line|#define M_CASID&t;&t;793&t;/* Address space ID (context) to match */
DECL|macro|MC_ASIDMASK
mdefine_line|#define MC_ASIDMASK&t;0x0000000f&t;/* Bits used for ASID value */
multiline_comment|/* These are the Ks and Kp from the PowerPC books.  For proper operation,&n; * Ks = 0, Kp = 1.&n; */
DECL|macro|MD_AP
mdefine_line|#define MD_AP&t;&t;794
DECL|macro|MD_Ks
mdefine_line|#define MD_Ks&t;&t;0x80000000&t;/* Should not be set */
DECL|macro|MD_Kp
mdefine_line|#define MD_Kp&t;&t;0x40000000&t;/* Should always be set */
multiline_comment|/* The effective page number register.  When read, contains the information&n; * about the last instruction TLB miss.  When MD_RPN is written, bits in&n; * this register are used to create the TLB entry.&n; */
DECL|macro|MD_EPN
mdefine_line|#define MD_EPN&t;&t;795
DECL|macro|MD_EPNMASK
mdefine_line|#define MD_EPNMASK&t;0xfffff000&t;/* Effective page number for entry */
DECL|macro|MD_EVALID
mdefine_line|#define MD_EVALID&t;0x00000200&t;/* Entry is valid */
DECL|macro|MD_ASIDMASK
mdefine_line|#define MD_ASIDMASK&t;0x0000000f&t;/* ASID match value */
multiline_comment|/* Reset value is undefined */
multiline_comment|/* The pointer to the base address of the first level page table.&n; * During a software tablewalk, reading this register provides the address&n; * of the entry associated with MD_EPN.&n; */
DECL|macro|M_TWB
mdefine_line|#define M_TWB&t;&t;796
DECL|macro|M_L1TB
mdefine_line|#define&t;M_L1TB&t;&t;0xfffff000&t;/* Level 1 table base address */
DECL|macro|M_L1INDX
mdefine_line|#define M_L1INDX&t;0x00000ffc&t;/* Level 1 index, when read */
multiline_comment|/* Reset value is undefined */
multiline_comment|/* A &quot;level 1&quot; or &quot;segment&quot; or whatever you want to call it register.&n; * For the data TLB, it contains bits that get loaded into the TLB entry&n; * when the MD_RPN is written.  It is also provides the hardware assist&n; * for finding the PTE address during software tablewalk.&n; */
DECL|macro|MD_TWC
mdefine_line|#define MD_TWC&t;&t;797
DECL|macro|MD_L2TB
mdefine_line|#define MD_L2TB&t;&t;0xfffff000&t;/* Level 2 table base address */
DECL|macro|MD_L2INDX
mdefine_line|#define MD_L2INDX&t;0xfffffe00&t;/* Level 2 index (*pte), when read */
DECL|macro|MD_APG
mdefine_line|#define MD_APG&t;&t;0x000001e0&t;/* Access protection group (0) */
DECL|macro|MD_GUARDED
mdefine_line|#define MD_GUARDED&t;0x00000010&t;/* Guarded storage */
DECL|macro|MD_PSMASK
mdefine_line|#define MD_PSMASK&t;0x0000000c&t;/* Mask of page size bits */
DECL|macro|MD_PS8MEG
mdefine_line|#define MD_PS8MEG&t;0x0000000c&t;/* 8M page size */
DECL|macro|MD_PS512K
mdefine_line|#define MD_PS512K&t;0x00000004&t;/* 512K page size */
DECL|macro|MD_PS4K_16K
mdefine_line|#define MD_PS4K_16K&t;0x00000000&t;/* 4K or 16K page size */
DECL|macro|MD_WT
mdefine_line|#define MD_WT&t;&t;0x00000002&t;/* Use writethrough page attribute */
DECL|macro|MD_SVALID
mdefine_line|#define MD_SVALID&t;0x00000001&t;/* Segment entry is valid */
multiline_comment|/* Reset value is undefined */
multiline_comment|/* Real page number.  Defined by the pte.  Writing this register&n; * causes a TLB entry to be created for the data TLB, using&n; * additional information from the MD_EPN, and MD_TWC registers.&n; */
DECL|macro|MD_RPN
mdefine_line|#define MD_RPN&t;&t;798
multiline_comment|/* This is a temporary storage register that could be used to save&n; * a processor working register during a tablewalk.&n; */
DECL|macro|M_TW
mdefine_line|#define M_TW&t;&t;799
macro_line|#endif /* _PPC64_MMU_H_ */
eof
