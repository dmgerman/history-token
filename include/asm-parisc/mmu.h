multiline_comment|/*&n; * parisc mmu structures &n; */
macro_line|#ifndef _PARISC_MMU_H_
DECL|macro|_PARISC_MMU_H_
mdefine_line|#define _PARISC_MMU_H_
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/* Default &quot;unsigned long&quot; context */
DECL|typedef|mm_context_t
r_typedef
r_int
r_int
id|mm_context_t
suffix:semicolon
multiline_comment|/* Hardware Page Table Entry */
DECL|struct|_PTE
r_typedef
r_struct
id|_PTE
(brace
DECL|member|v
r_int
r_int
id|v
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Entry is valid */
DECL|member|tag
r_int
r_int
id|tag
suffix:colon
l_int|31
suffix:semicolon
multiline_comment|/* Unique Tag */
DECL|member|r
r_int
r_int
id|r
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* referenced */
DECL|member|os_1
r_int
r_int
id|os_1
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/*  */
DECL|member|t
r_int
r_int
id|t
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* page reference trap */
DECL|member|d
r_int
r_int
id|d
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* dirty */
DECL|member|b
r_int
r_int
id|b
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* break */
DECL|member|type
r_int
r_int
id|type
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* access type */
DECL|member|pl1
r_int
r_int
id|pl1
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* PL1 (execute) */
DECL|member|pl2
r_int
r_int
id|pl2
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* PL2 (write) */
DECL|member|u
r_int
r_int
id|u
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* uncacheable */
DECL|member|id
r_int
r_int
id|id
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* access id */
DECL|member|os_2
r_int
r_int
id|os_2
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/*  */
DECL|member|os_3
r_int
r_int
id|os_3
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/*  */
DECL|member|res_1
r_int
r_int
id|res_1
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/*  */
DECL|member|phys
r_int
r_int
id|phys
suffix:colon
l_int|20
suffix:semicolon
multiline_comment|/* physical page number */
DECL|member|os_4
r_int
r_int
id|os_4
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/*  */
DECL|member|res_2
r_int
r_int
id|res_2
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/*  */
DECL|member|next
r_int
r_int
id|next
suffix:semicolon
multiline_comment|/* pointer to next page */
DECL|typedef|PTE
)brace
id|PTE
suffix:semicolon
multiline_comment|/*&n; * Simulated two-level MMU.  This structure is used by the kernel&n; * to keep track of MMU mappings and is used to update/maintain&n; * the hardware HASH table which is really a cache of mappings.&n; *&n; * The simulated structures mimic the hardware available on other&n; * platforms, notably the 80x86 and 680x0.&n; */
DECL|struct|_pte
r_typedef
r_struct
id|_pte
(brace
DECL|member|page_num
r_int
r_int
id|page_num
suffix:colon
l_int|20
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:colon
l_int|12
suffix:semicolon
multiline_comment|/* Page flags (some unused bits) */
DECL|typedef|pte
)brace
id|pte
suffix:semicolon
DECL|macro|PD_SHIFT
mdefine_line|#define PD_SHIFT (10+12)&t;&t;/* Page directory */
DECL|macro|PD_MASK
mdefine_line|#define PD_MASK  0x02FF
DECL|macro|PT_SHIFT
mdefine_line|#define PT_SHIFT (12)&t;&t;&t;/* Page Table */
DECL|macro|PT_MASK
mdefine_line|#define PT_MASK  0x02FF
DECL|macro|PG_SHIFT
mdefine_line|#define PG_SHIFT (12)&t;&t;&t;/* Page Entry */
multiline_comment|/* MMU context */
DECL|struct|_MMU_context
r_typedef
r_struct
id|_MMU_context
(brace
DECL|member|pid
r_int
id|pid
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|pmap
id|pte
op_star
op_star
id|pmap
suffix:semicolon
multiline_comment|/* Two-level page-map structure */
DECL|typedef|MMU_context
)brace
id|MMU_context
suffix:semicolon
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#endif /* _PARISC_MMU_H_ */
eof
