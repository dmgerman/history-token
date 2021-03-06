multiline_comment|/* $Id: page.h,v 1.55 2000/10/30 21:01:41 davem Exp $&n; * page.h:  Various defines and such for MMU operations on the Sparc for&n; *          the Linux kernel.&n; *&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef _SPARC_PAGE_H
DECL|macro|_SPARC_PAGE_H
mdefine_line|#define _SPARC_PAGE_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_SUN4
DECL|macro|PAGE_SHIFT
mdefine_line|#define PAGE_SHIFT   13
macro_line|#else
DECL|macro|PAGE_SHIFT
mdefine_line|#define PAGE_SHIFT   12
macro_line|#endif
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/* I have my suspicions... -DaveM */
DECL|macro|PAGE_SIZE
mdefine_line|#define PAGE_SIZE    (1UL &lt;&lt; PAGE_SHIFT)
macro_line|#else
DECL|macro|PAGE_SIZE
mdefine_line|#define PAGE_SIZE    (1 &lt;&lt; PAGE_SHIFT)
macro_line|#endif
DECL|macro|PAGE_MASK
mdefine_line|#define PAGE_MASK    (~(PAGE_SIZE-1))
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;asm/btfixup.h&gt;
macro_line|#ifndef __ASSEMBLY__
DECL|macro|clear_page
mdefine_line|#define clear_page(page)&t; memset((void *)(page), 0, PAGE_SIZE)
DECL|macro|copy_page
mdefine_line|#define copy_page(to,from) &t;memcpy((void *)(to), (void *)(from), PAGE_SIZE)
DECL|macro|clear_user_page
mdefine_line|#define clear_user_page(addr, vaddr, page)&t;&bslash;&n;&t;do { &t;clear_page(addr);&t;&t;&bslash;&n;&t;&t;sparc_flush_page_to_ram(page);&t;&bslash;&n;&t;} while (0)
DECL|macro|copy_user_page
mdefine_line|#define copy_user_page(to, from, vaddr, page)&t;&bslash;&n;&t;do {&t;copy_page(to, from);&t;&t;&bslash;&n;&t;&t;sparc_flush_page_to_ram(page);&t;&bslash;&n;&t;} while (0)
multiline_comment|/* The following structure is used to hold the physical&n; * memory configuration of the machine.  This is filled in&n; * probe_memory() and is later used by mem_init() to set up&n; * mem_map[].  We statically allocate SPARC_PHYS_BANKS of&n; * these structs, this is arbitrary.  The entry after the&n; * last valid one has num_bytes==0.&n; */
DECL|struct|sparc_phys_banks
r_struct
id|sparc_phys_banks
(brace
DECL|member|base_addr
r_int
r_int
id|base_addr
suffix:semicolon
DECL|member|num_bytes
r_int
r_int
id|num_bytes
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|SPARC_PHYS_BANKS
mdefine_line|#define SPARC_PHYS_BANKS 32
r_extern
r_struct
id|sparc_phys_banks
id|sp_banks
(braket
id|SPARC_PHYS_BANKS
op_plus
l_int|1
)braket
suffix:semicolon
multiline_comment|/* Cache alias structure.  Entry is valid if context != -1. */
DECL|struct|cache_palias
r_struct
id|cache_palias
(brace
DECL|member|vaddr
r_int
r_int
id|vaddr
suffix:semicolon
DECL|member|context
r_int
id|context
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|cache_palias
op_star
id|sparc_aliases
suffix:semicolon
multiline_comment|/* passing structs on the Sparc slow us down tremendously... */
multiline_comment|/* #define STRICT_MM_TYPECHECKS */
macro_line|#ifdef STRICT_MM_TYPECHECKS
multiline_comment|/*&n; * These are used to make use of C type-checking..&n; */
DECL|member|pte
DECL|typedef|pte_t
r_typedef
r_struct
(brace
r_int
r_int
id|pte
suffix:semicolon
)brace
id|pte_t
suffix:semicolon
DECL|member|iopte
DECL|typedef|iopte_t
r_typedef
r_struct
(brace
r_int
r_int
id|iopte
suffix:semicolon
)brace
id|iopte_t
suffix:semicolon
DECL|member|pmdv
DECL|typedef|pmd_t
r_typedef
r_struct
(brace
r_int
r_int
id|pmdv
(braket
l_int|16
)braket
suffix:semicolon
)brace
id|pmd_t
suffix:semicolon
DECL|member|pgd
DECL|typedef|pgd_t
r_typedef
r_struct
(brace
r_int
r_int
id|pgd
suffix:semicolon
)brace
id|pgd_t
suffix:semicolon
DECL|member|ctxd
DECL|typedef|ctxd_t
r_typedef
r_struct
(brace
r_int
r_int
id|ctxd
suffix:semicolon
)brace
id|ctxd_t
suffix:semicolon
DECL|member|pgprot
DECL|typedef|pgprot_t
r_typedef
r_struct
(brace
r_int
r_int
id|pgprot
suffix:semicolon
)brace
id|pgprot_t
suffix:semicolon
DECL|member|iopgprot
DECL|typedef|iopgprot_t
r_typedef
r_struct
(brace
r_int
r_int
id|iopgprot
suffix:semicolon
)brace
id|iopgprot_t
suffix:semicolon
DECL|macro|pte_val
mdefine_line|#define pte_val(x)&t;((x).pte)
DECL|macro|iopte_val
mdefine_line|#define iopte_val(x)&t;((x).iopte)
DECL|macro|pmd_val
mdefine_line|#define pmd_val(x)      ((x).pmdv[0])
DECL|macro|pgd_val
mdefine_line|#define pgd_val(x)&t;((x).pgd)
DECL|macro|ctxd_val
mdefine_line|#define ctxd_val(x)&t;((x).ctxd)
DECL|macro|pgprot_val
mdefine_line|#define pgprot_val(x)&t;((x).pgprot)
DECL|macro|iopgprot_val
mdefine_line|#define iopgprot_val(x)&t;((x).iopgprot)
DECL|macro|__pte
mdefine_line|#define __pte(x)&t;((pte_t) { (x) } )
DECL|macro|__iopte
mdefine_line|#define __iopte(x)&t;((iopte_t) { (x) } )
multiline_comment|/* #define __pmd(x)        ((pmd_t) { (x) } ) */
multiline_comment|/* XXX procedure with loop */
DECL|macro|__pgd
mdefine_line|#define __pgd(x)&t;((pgd_t) { (x) } )
DECL|macro|__ctxd
mdefine_line|#define __ctxd(x)&t;((ctxd_t) { (x) } )
DECL|macro|__pgprot
mdefine_line|#define __pgprot(x)&t;((pgprot_t) { (x) } )
DECL|macro|__iopgprot
mdefine_line|#define __iopgprot(x)&t;((iopgprot_t) { (x) } )
macro_line|#else
multiline_comment|/*&n; * .. while these make it easier on the compiler&n; */
DECL|typedef|pte_t
r_typedef
r_int
r_int
id|pte_t
suffix:semicolon
DECL|typedef|iopte_t
r_typedef
r_int
r_int
id|iopte_t
suffix:semicolon
DECL|member|pmdv
DECL|typedef|pmd_t
r_typedef
r_struct
(brace
r_int
r_int
id|pmdv
(braket
l_int|16
)braket
suffix:semicolon
)brace
id|pmd_t
suffix:semicolon
DECL|typedef|pgd_t
r_typedef
r_int
r_int
id|pgd_t
suffix:semicolon
DECL|typedef|ctxd_t
r_typedef
r_int
r_int
id|ctxd_t
suffix:semicolon
DECL|typedef|pgprot_t
r_typedef
r_int
r_int
id|pgprot_t
suffix:semicolon
DECL|typedef|iopgprot_t
r_typedef
r_int
r_int
id|iopgprot_t
suffix:semicolon
DECL|macro|pte_val
mdefine_line|#define pte_val(x)&t;(x)
DECL|macro|iopte_val
mdefine_line|#define iopte_val(x)&t;(x)
DECL|macro|pmd_val
mdefine_line|#define pmd_val(x)      ((x).pmdv[0])
DECL|macro|pgd_val
mdefine_line|#define pgd_val(x)&t;(x)
DECL|macro|ctxd_val
mdefine_line|#define ctxd_val(x)&t;(x)
DECL|macro|pgprot_val
mdefine_line|#define pgprot_val(x)&t;(x)
DECL|macro|iopgprot_val
mdefine_line|#define iopgprot_val(x)&t;(x)
DECL|macro|__pte
mdefine_line|#define __pte(x)&t;(x)
DECL|macro|__iopte
mdefine_line|#define __iopte(x)&t;(x)
multiline_comment|/* #define __pmd(x)        (x) */
multiline_comment|/* XXX later */
DECL|macro|__pgd
mdefine_line|#define __pgd(x)&t;(x)
DECL|macro|__ctxd
mdefine_line|#define __ctxd(x)&t;(x)
DECL|macro|__pgprot
mdefine_line|#define __pgprot(x)&t;(x)
DECL|macro|__iopgprot
mdefine_line|#define __iopgprot(x)&t;(x)
macro_line|#endif
r_extern
r_int
r_int
id|sparc_unmapped_base
suffix:semicolon
id|BTFIXUPDEF_SETHI
c_func
(paren
id|sparc_unmapped_base
)paren
DECL|macro|TASK_UNMAPPED_BASE
mdefine_line|#define TASK_UNMAPPED_BASE&t;BTFIXUP_SETHI(sparc_unmapped_base)
multiline_comment|/* Pure 2^n version of get_order */
DECL|function|get_order
r_extern
id|__inline__
r_int
id|get_order
c_func
(paren
r_int
r_int
id|size
)paren
(brace
r_int
id|order
suffix:semicolon
id|size
op_assign
(paren
id|size
op_minus
l_int|1
)paren
op_rshift
(paren
id|PAGE_SHIFT
op_minus
l_int|1
)paren
suffix:semicolon
id|order
op_assign
op_minus
l_int|1
suffix:semicolon
r_do
(brace
id|size
op_rshift_assign
l_int|1
suffix:semicolon
id|order
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
id|size
)paren
suffix:semicolon
r_return
id|order
suffix:semicolon
)brace
macro_line|#else /* !(__ASSEMBLY__) */
DECL|macro|__pgprot
mdefine_line|#define __pgprot(x)&t;(x)
macro_line|#endif /* !(__ASSEMBLY__) */
multiline_comment|/* to align the pointer to the (next) page boundary */
DECL|macro|PAGE_ALIGN
mdefine_line|#define PAGE_ALIGN(addr)  (((addr)+PAGE_SIZE-1)&amp;PAGE_MASK)
DECL|macro|PAGE_OFFSET
mdefine_line|#define PAGE_OFFSET&t;0xf0000000
macro_line|#ifndef __ASSEMBLY__
r_extern
r_int
r_int
id|phys_base
suffix:semicolon
r_extern
r_int
r_int
id|pfn_base
suffix:semicolon
macro_line|#endif
DECL|macro|__pa
mdefine_line|#define __pa(x)&t;&t;&t;((unsigned long)(x) - PAGE_OFFSET + phys_base)
DECL|macro|__va
mdefine_line|#define __va(x)&t;&t;&t;((void *)((unsigned long) (x) - phys_base + PAGE_OFFSET))
DECL|macro|virt_to_phys
mdefine_line|#define virt_to_phys&t;&t;__pa
DECL|macro|phys_to_virt
mdefine_line|#define phys_to_virt&t;&t;__va
DECL|macro|pfn_to_page
mdefine_line|#define pfn_to_page(pfn)&t;(mem_map + ((pfn)-(pfn_base)))
DECL|macro|page_to_pfn
mdefine_line|#define page_to_pfn(page)&t;((unsigned long)(((page) - mem_map) + pfn_base))
DECL|macro|virt_to_page
mdefine_line|#define virt_to_page(kaddr)&t;(mem_map + ((((unsigned long)(kaddr)-PAGE_OFFSET)&gt;&gt;PAGE_SHIFT)))
DECL|macro|pfn_valid
mdefine_line|#define pfn_valid(pfn)&t;&t;(((pfn) &gt;= (pfn_base)) &amp;&amp; (((pfn)-(pfn_base)) &lt; max_mapnr))
DECL|macro|virt_addr_valid
mdefine_line|#define virt_addr_valid(kaddr)&t;((((unsigned long)(kaddr)-PAGE_OFFSET)&gt;&gt;PAGE_SHIFT) &lt; max_mapnr)
DECL|macro|VM_DATA_DEFAULT_FLAGS
mdefine_line|#define VM_DATA_DEFAULT_FLAGS&t;(VM_READ | VM_WRITE | VM_EXEC | &bslash;&n;&t;&t;&t;&t; VM_MAYREAD | VM_MAYWRITE | VM_MAYEXEC)
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _SPARC_PAGE_H */
eof
