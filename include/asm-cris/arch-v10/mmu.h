multiline_comment|/*&n; * CRIS MMU constants and PTE layout&n; */
macro_line|#ifndef _CRIS_ARCH_MMU_H
DECL|macro|_CRIS_ARCH_MMU_H
mdefine_line|#define _CRIS_ARCH_MMU_H
multiline_comment|/* type used in struct mm to couple an MMU context to an active mm */
DECL|typedef|mm_context_t
r_typedef
r_int
r_int
id|mm_context_t
suffix:semicolon
multiline_comment|/* kernel memory segments */
DECL|macro|KSEG_F
mdefine_line|#define KSEG_F 0xf0000000UL
DECL|macro|KSEG_E
mdefine_line|#define KSEG_E 0xe0000000UL
DECL|macro|KSEG_D
mdefine_line|#define KSEG_D 0xd0000000UL
DECL|macro|KSEG_C
mdefine_line|#define KSEG_C 0xc0000000UL
DECL|macro|KSEG_B
mdefine_line|#define KSEG_B 0xb0000000UL
DECL|macro|KSEG_A
mdefine_line|#define KSEG_A 0xa0000000UL
DECL|macro|KSEG_9
mdefine_line|#define KSEG_9 0x90000000UL
DECL|macro|KSEG_8
mdefine_line|#define KSEG_8 0x80000000UL
DECL|macro|KSEG_7
mdefine_line|#define KSEG_7 0x70000000UL
DECL|macro|KSEG_6
mdefine_line|#define KSEG_6 0x60000000UL
DECL|macro|KSEG_5
mdefine_line|#define KSEG_5 0x50000000UL
DECL|macro|KSEG_4
mdefine_line|#define KSEG_4 0x40000000UL
DECL|macro|KSEG_3
mdefine_line|#define KSEG_3 0x30000000UL
DECL|macro|KSEG_2
mdefine_line|#define KSEG_2 0x20000000UL
DECL|macro|KSEG_1
mdefine_line|#define KSEG_1 0x10000000UL
DECL|macro|KSEG_0
mdefine_line|#define KSEG_0 0x00000000UL
multiline_comment|/* CRIS PTE bits (see R_TLB_LO in the register description)&n; *&n; *   Bit:  31-13 12-------4    3        2       1       0  &n; *         ________________________________________________&n; *        | pfn | reserved | global | valid | kernel | we  |&n; *        |_____|__________|________|_______|________|_____|&n; *&n; * (pfn = physical frame number)&n; */
multiline_comment|/* Real HW-based PTE bits. We use some synonym names so that&n; * things become less confusing in combination with the SW-based&n; * bits further below.&n; *&n; */
DECL|macro|_PAGE_WE
mdefine_line|#define _PAGE_WE&t;   (1&lt;&lt;0) /* page is write-enabled */
DECL|macro|_PAGE_SILENT_WRITE
mdefine_line|#define _PAGE_SILENT_WRITE (1&lt;&lt;0) /* synonym */
DECL|macro|_PAGE_KERNEL
mdefine_line|#define _PAGE_KERNEL&t;   (1&lt;&lt;1) /* page is kernel only */
DECL|macro|_PAGE_VALID
mdefine_line|#define _PAGE_VALID&t;   (1&lt;&lt;2) /* page is valid */
DECL|macro|_PAGE_SILENT_READ
mdefine_line|#define _PAGE_SILENT_READ  (1&lt;&lt;2) /* synonym */
DECL|macro|_PAGE_GLOBAL
mdefine_line|#define _PAGE_GLOBAL       (1&lt;&lt;3) /* global page - context is ignored */
multiline_comment|/* Bits the HW doesn&squot;t care about but the kernel uses them in SW */
DECL|macro|_PAGE_PRESENT
mdefine_line|#define _PAGE_PRESENT   (1&lt;&lt;4)  /* page present in memory */
DECL|macro|_PAGE_FILE
mdefine_line|#define _PAGE_FILE      (1&lt;&lt;5)  /* set: pagecache, unset: swap (when !PRESENT) */
DECL|macro|_PAGE_ACCESSED
mdefine_line|#define _PAGE_ACCESSED&t;(1&lt;&lt;5)  /* simulated in software using valid bit */
DECL|macro|_PAGE_MODIFIED
mdefine_line|#define _PAGE_MODIFIED&t;(1&lt;&lt;6)  /* simulated in software using we bit */
DECL|macro|_PAGE_READ
mdefine_line|#define _PAGE_READ      (1&lt;&lt;7)  /* read-enabled */
DECL|macro|_PAGE_WRITE
mdefine_line|#define _PAGE_WRITE     (1&lt;&lt;8)  /* write-enabled */
multiline_comment|/* Define some higher level generic page attributes. */
DECL|macro|__READABLE
mdefine_line|#define __READABLE      (_PAGE_READ | _PAGE_SILENT_READ | _PAGE_ACCESSED)
DECL|macro|__WRITEABLE
mdefine_line|#define __WRITEABLE     (_PAGE_WRITE | _PAGE_SILENT_WRITE | _PAGE_MODIFIED)
DECL|macro|_PAGE_TABLE
mdefine_line|#define _PAGE_TABLE     (_PAGE_PRESENT | __READABLE | __WRITEABLE)
DECL|macro|_PAGE_CHG_MASK
mdefine_line|#define _PAGE_CHG_MASK  (PAGE_MASK | _PAGE_ACCESSED | _PAGE_MODIFIED)
DECL|macro|PAGE_NONE
mdefine_line|#define PAGE_NONE       __pgprot(_PAGE_PRESENT | _PAGE_ACCESSED)
DECL|macro|PAGE_SHARED
mdefine_line|#define PAGE_SHARED     __pgprot(_PAGE_PRESENT | __READABLE | _PAGE_WRITE | &bslash;&n;&t;&t;&t;&t; _PAGE_ACCESSED)
DECL|macro|PAGE_COPY
mdefine_line|#define PAGE_COPY       __pgprot(_PAGE_PRESENT | __READABLE)  
singleline_comment|// | _PAGE_COW
DECL|macro|PAGE_READONLY
mdefine_line|#define PAGE_READONLY   __pgprot(_PAGE_PRESENT | __READABLE)
DECL|macro|PAGE_KERNEL
mdefine_line|#define PAGE_KERNEL     __pgprot(_PAGE_GLOBAL | _PAGE_KERNEL | &bslash;&n;&t;&t;&t;&t; _PAGE_PRESENT | __READABLE | __WRITEABLE)
DECL|macro|_KERNPG_TABLE
mdefine_line|#define _KERNPG_TABLE   (_PAGE_TABLE | _PAGE_KERNEL)
multiline_comment|/*&n; * CRIS can&squot;t do page protection for execute, and considers read the same.&n; * Also, write permissions imply read permissions. This is the closest we can&n; * get..&n; */
DECL|macro|__P000
mdefine_line|#define __P000&t;PAGE_NONE
DECL|macro|__P001
mdefine_line|#define __P001&t;PAGE_READONLY
DECL|macro|__P010
mdefine_line|#define __P010&t;PAGE_COPY
DECL|macro|__P011
mdefine_line|#define __P011&t;PAGE_COPY
DECL|macro|__P100
mdefine_line|#define __P100&t;PAGE_READONLY
DECL|macro|__P101
mdefine_line|#define __P101&t;PAGE_READONLY
DECL|macro|__P110
mdefine_line|#define __P110&t;PAGE_COPY
DECL|macro|__P111
mdefine_line|#define __P111&t;PAGE_COPY
DECL|macro|__S000
mdefine_line|#define __S000&t;PAGE_NONE
DECL|macro|__S001
mdefine_line|#define __S001&t;PAGE_READONLY
DECL|macro|__S010
mdefine_line|#define __S010&t;PAGE_SHARED
DECL|macro|__S011
mdefine_line|#define __S011&t;PAGE_SHARED
DECL|macro|__S100
mdefine_line|#define __S100&t;PAGE_READONLY
DECL|macro|__S101
mdefine_line|#define __S101&t;PAGE_READONLY
DECL|macro|__S110
mdefine_line|#define __S110&t;PAGE_SHARED
DECL|macro|__S111
mdefine_line|#define __S111&t;PAGE_SHARED
DECL|macro|PTE_FILE_MAX_BITS
mdefine_line|#define PTE_FILE_MAX_BITS&t;26
macro_line|#endif
eof
