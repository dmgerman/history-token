multiline_comment|/*&n; * highmem.h: virtual kernel memory mappings for high memory&n; *&n; * Used in CONFIG_HIGHMEM systems for memory pages which&n; * are not addressable by direct kernel virtual addresses.&n; *&n; * Copyright (C) 1999 Gerhard Wichert, Siemens AG&n; *&t;&t;      Gerhard.Wichert@pdb.siemens.de&n; *&n; *&n; * Redesigned the x86 32-bit VM architecture to deal with&n; * up to 16 Terabyte physical memory. With current x86 CPUs&n; * we now support up to 64 Gigabytes physical RAM.&n; *&n; * Copyright (C) 1999 Ingo Molnar &lt;mingo@redhat.com&gt;&n; */
macro_line|#ifndef _ASM_HIGHMEM_H
DECL|macro|_ASM_HIGHMEM_H
mdefine_line|#define _ASM_HIGHMEM_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/kmap_types.h&gt;
multiline_comment|/* undef for production */
DECL|macro|HIGHMEM_DEBUG
mdefine_line|#define HIGHMEM_DEBUG 1
multiline_comment|/* declarations for highmem.c */
r_extern
r_int
r_int
id|highstart_pfn
comma
id|highend_pfn
suffix:semicolon
r_extern
id|pte_t
op_star
id|kmap_pte
suffix:semicolon
r_extern
id|pgprot_t
id|kmap_prot
suffix:semicolon
r_extern
id|pte_t
op_star
id|pkmap_page_table
suffix:semicolon
multiline_comment|/*&n; * Right now we initialize only a single pte table. It can be extended&n; * easily, subsequent pte tables have to be allocated in one physical&n; * chunk of RAM.&n; */
DECL|macro|PKMAP_BASE
mdefine_line|#define PKMAP_BASE (0xfe000000UL)
DECL|macro|LAST_PKMAP
mdefine_line|#define LAST_PKMAP 1024
DECL|macro|LAST_PKMAP_MASK
mdefine_line|#define LAST_PKMAP_MASK (LAST_PKMAP-1)
DECL|macro|PKMAP_NR
mdefine_line|#define PKMAP_NR(virt)  ((virt-PKMAP_BASE) &gt;&gt; PAGE_SHIFT)
DECL|macro|PKMAP_ADDR
mdefine_line|#define PKMAP_ADDR(nr)  (PKMAP_BASE + ((nr) &lt;&lt; PAGE_SHIFT))
r_extern
r_void
op_star
id|kmap_high
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
suffix:semicolon
r_extern
r_void
id|kunmap_high
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
suffix:semicolon
multiline_comment|/*&n; * CONFIG_LIMITED_DMA is for systems with DMA limitations such as Momentum&squot;s&n; * Jaguar ATX.  This option exploits the highmem code in the kernel so is&n; * always enabled together with CONFIG_HIGHMEM but at this time doesn&squot;t&n; * actually add highmem functionality.&n; */
macro_line|#ifdef CONFIG_LIMITED_DMA
multiline_comment|/*&n; * These are the default functions for the no-highmem case from&n; * &lt;linux/highmem.h&gt;&n; */
DECL|function|kmap
r_static
r_inline
r_void
op_star
id|kmap
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
(brace
id|might_sleep
c_func
(paren
)paren
suffix:semicolon
r_return
id|page_address
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
DECL|macro|kunmap
mdefine_line|#define kunmap(page) do { (void) (page); } while (0)
DECL|function|kmap_atomic
r_static
r_inline
r_void
op_star
id|kmap_atomic
c_func
(paren
r_struct
id|page
op_star
id|page
comma
r_enum
id|km_type
id|type
)paren
(brace
r_return
id|page_address
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
DECL|function|kunmap_atomic
r_static
r_inline
r_void
id|kunmap_atomic
c_func
(paren
r_void
op_star
id|kvaddr
comma
r_enum
id|km_type
id|type
)paren
(brace
)brace
DECL|macro|kmap_atomic_to_page
mdefine_line|#define kmap_atomic_to_page(ptr) virt_to_page(ptr)
DECL|macro|flush_cache_kmaps
mdefine_line|#define flush_cache_kmaps()&t;do { } while (0)
macro_line|#else /* LIMITED_DMA */
r_extern
r_void
op_star
id|__kmap
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
suffix:semicolon
r_extern
r_void
id|__kunmap
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
suffix:semicolon
r_extern
r_void
op_star
id|__kmap_atomic
c_func
(paren
r_struct
id|page
op_star
id|page
comma
r_enum
id|km_type
id|type
)paren
suffix:semicolon
r_extern
r_void
id|__kunmap_atomic
c_func
(paren
r_void
op_star
id|kvaddr
comma
r_enum
id|km_type
id|type
)paren
suffix:semicolon
r_extern
r_struct
id|page
op_star
id|__kmap_atomic_to_page
c_func
(paren
r_void
op_star
id|ptr
)paren
suffix:semicolon
DECL|macro|kmap
mdefine_line|#define kmap&t;&t;&t;__kmap
DECL|macro|kunmap
mdefine_line|#define kunmap&t;&t;&t;__kunmap
DECL|macro|kmap_atomic
mdefine_line|#define kmap_atomic&t;&t;__kmap_atomic
DECL|macro|kunmap_atomic
mdefine_line|#define kunmap_atomic&t;&t;__kunmap_atomic
DECL|macro|kmap_atomic_to_page
mdefine_line|#define kmap_atomic_to_page&t;__kmap_atomic_to_page
DECL|macro|flush_cache_kmaps
mdefine_line|#define flush_cache_kmaps()&t;flush_cache_all()
macro_line|#endif /* LIMITED_DMA */
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _ASM_HIGHMEM_H */
eof
