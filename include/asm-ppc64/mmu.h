multiline_comment|/*&n; * PowerPC memory management structures&n; *&n; * Dave Engebretsen &amp; Mike Corrigan &lt;{engebret|mikejc}@us.ibm.com&gt;&n; *   PPC64 rework.&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _PPC64_MMU_H_
DECL|macro|_PPC64_MMU_H_
mdefine_line|#define _PPC64_MMU_H_
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;linux/stringify.h&gt;
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
DECL|member|huge_pgdir
id|pgd_t
op_star
id|huge_pgdir
suffix:semicolon
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
DECL|macro|STE_ESID_V
mdefine_line|#define STE_ESID_V&t;0x80
DECL|macro|STE_ESID_KS
mdefine_line|#define STE_ESID_KS&t;0x20
DECL|macro|STE_ESID_KP
mdefine_line|#define STE_ESID_KP&t;0x10
DECL|macro|STE_ESID_N
mdefine_line|#define STE_ESID_N&t;0x08
DECL|macro|STE_VSID_SHIFT
mdefine_line|#define STE_VSID_SHIFT&t;12
DECL|struct|stab_entry
r_struct
id|stab_entry
(brace
DECL|member|esid_data
r_int
r_int
id|esid_data
suffix:semicolon
DECL|member|vsid_data
r_int
r_int
id|vsid_data
suffix:semicolon
)brace
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
r_extern
id|HPTE
op_star
id|htab_address
suffix:semicolon
r_extern
r_int
r_int
id|htab_hash_mask
suffix:semicolon
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
(brace
id|va
op_and_assign
id|HPAGE_MASK
suffix:semicolon
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
)brace
r_else
(brace
id|va
op_and_assign
id|PAGE_MASK
suffix:semicolon
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
id|va
op_and_assign
id|PAGE_MASK
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
mdefine_line|#define SLB_NUM_BOLTED&t;&t;3
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
DECL|macro|VSID_MULTIPLIER
mdefine_line|#define VSID_MULTIPLIER&t;ASM_CONST(200730139)&t;/* 28-bit prime */
DECL|macro|VSID_BITS
mdefine_line|#define VSID_BITS&t;36
DECL|macro|VSID_MODULUS
mdefine_line|#define VSID_MODULUS&t;((1UL&lt;&lt;VSID_BITS)-1)
DECL|macro|CONTEXT_BITS
mdefine_line|#define CONTEXT_BITS&t;20
DECL|macro|USER_ESID_BITS
mdefine_line|#define USER_ESID_BITS&t;15
multiline_comment|/*&n; * This macro generates asm code to compute the VSID scramble&n; * function.  Used in slb_allocate() and do_stab_bolted.  The function&n; * computed is: (protovsid*VSID_MULTIPLIER) % VSID_MODULUS&n; *&n; *&t;rt = register continaing the proto-VSID and into which the&n; *&t;&t;VSID will be stored&n; *&t;rx = scratch register (clobbered)&n; *&n; * &t;- rt and rx must be different registers&n; * &t;- The answer will end up in the low 36 bits of rt.  The higher&n; * &t;  bits may contain other garbage, so you may need to mask the&n; * &t;  result.&n; */
DECL|macro|ASM_VSID_SCRAMBLE
mdefine_line|#define ASM_VSID_SCRAMBLE(rt, rx)&t;&bslash;&n;&t;lis&t;rx,VSID_MULTIPLIER@h;&t;&t;&t;&t;&t;&bslash;&n;&t;ori&t;rx,rx,VSID_MULTIPLIER@l;&t;&t;&t;&t;&bslash;&n;&t;mulld&t;rt,rt,rx;&t;&t;/* rt = rt * MULTIPLIER */&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;srdi&t;rx,rt,VSID_BITS;&t;&t;&t;&t;&t;&bslash;&n;&t;clrldi&t;rt,rt,(64-VSID_BITS);&t;&t;&t;&t;&t;&bslash;&n;&t;add&t;rt,rt,rx;&t;&t;/* add high and low bits */&t;&bslash;&n;&t;/* Now, r3 == VSID (mod 2^36-1), and lies between 0 and&t;&t;&bslash;&n;&t; * 2^36-1+2^28-1.  That in particular means that if r3 &gt;=&t;&bslash;&n;&t; * 2^36-1, then r3+1 has the 2^36 bit set.  So, if r3+1 has&t;&bslash;&n;&t; * the bit clear, r3 already has the answer we want, if it&t;&bslash;&n;&t; * doesn&squot;t, the answer is the low 36 bits of r3+1.  So in all&t;&bslash;&n;&t; * cases the answer is the low 36 bits of (r3 + ((r3+1) &gt;&gt; 36))*/&bslash;&n;&t;addi&t;rx,rt,1;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;srdi&t;rx,rx,VSID_BITS;&t;/* extract 2^36 bit */&t;&t;&bslash;&n;&t;add&t;rt,rt,rx
macro_line|#endif /* _PPC64_MMU_H_ */
eof
