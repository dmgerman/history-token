multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1994 - 2002 by Ralf Baechle&n; * Copyright (C) 1999, 2000, 2001 Silicon Graphics, Inc.&n; * Copyright (C) 2002  Maciej W. Rozycki&n; */
macro_line|#ifndef _ASM_PGTABLE_BITS_H
DECL|macro|_ASM_PGTABLE_BITS_H
mdefine_line|#define _ASM_PGTABLE_BITS_H
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n; * Note that we shift the lower 32bits of each EntryLo[01] entry&n; * 6 bits to the left. That way we can convert the PFN into the&n; * physical address by a single &squot;and&squot; operation and gain 6 additional&n; * bits for storing information which isn&squot;t present in a normal&n; * MIPS page table.&n; *&n; * Similar to the Alpha port, we need to keep track of the ref&n; * and mod bits in software.  We have a software &quot;yeah you can read&n; * from this page&quot; bit, and a hardware one which actually lets the&n; * process read from the page.  On the same token we have a software&n; * writable bit and the real hardware one which actually lets the&n; * process write to the page, this keeps a mod bit via the hardware&n; * dirty bit.&n; *&n; * Certain revisions of the R4000 and R5000 have a bug where if a&n; * certain sequence occurs in the last 3 instructions of an executable&n; * page, and the following page is not mapped, the cpu can do&n; * unpredictable things.  The code (when it is written) to deal with&n; * this problem will be in the update_mmu_cache() code for the r4k.&n; */
macro_line|#if defined(CONFIG_CPU_MIPS32) &amp;&amp; defined(CONFIG_64BIT_PHYS_ADDR)
DECL|macro|_PAGE_PRESENT
mdefine_line|#define _PAGE_PRESENT               (1&lt;&lt;6)  /* implemented in software */
DECL|macro|_PAGE_READ
mdefine_line|#define _PAGE_READ                  (1&lt;&lt;7)  /* implemented in software */
DECL|macro|_PAGE_WRITE
mdefine_line|#define _PAGE_WRITE                 (1&lt;&lt;8)  /* implemented in software */
DECL|macro|_PAGE_ACCESSED
mdefine_line|#define _PAGE_ACCESSED              (1&lt;&lt;9)  /* implemented in software */
DECL|macro|_PAGE_MODIFIED
mdefine_line|#define _PAGE_MODIFIED              (1&lt;&lt;10) /* implemented in software */
DECL|macro|_PAGE_FILE
mdefine_line|#define _PAGE_FILE                  (1&lt;&lt;10)  /* set:pagecache unset:swap */
DECL|macro|_PAGE_R4KBUG
mdefine_line|#define _PAGE_R4KBUG                (1&lt;&lt;0)  /* workaround for r4k bug  */
DECL|macro|_PAGE_GLOBAL
mdefine_line|#define _PAGE_GLOBAL                (1&lt;&lt;0)
DECL|macro|_PAGE_VALID
mdefine_line|#define _PAGE_VALID                 (1&lt;&lt;1)
DECL|macro|_PAGE_SILENT_READ
mdefine_line|#define _PAGE_SILENT_READ           (1&lt;&lt;1)  /* synonym                 */
DECL|macro|_PAGE_DIRTY
mdefine_line|#define _PAGE_DIRTY                 (1&lt;&lt;2)  /* The MIPS dirty bit      */
DECL|macro|_PAGE_SILENT_WRITE
mdefine_line|#define _PAGE_SILENT_WRITE          (1&lt;&lt;2)
DECL|macro|_CACHE_MASK
mdefine_line|#define _CACHE_MASK                 (7&lt;&lt;3)
multiline_comment|/* MIPS32 defines only values 2 and 3. The rest are implementation&n; * dependent.&n; */
DECL|macro|_CACHE_UNCACHED
mdefine_line|#define _CACHE_UNCACHED             (2&lt;&lt;3)
DECL|macro|_CACHE_CACHABLE_NONCOHERENT
mdefine_line|#define _CACHE_CACHABLE_NONCOHERENT (3&lt;&lt;3)
DECL|macro|_CACHE_CACHABLE_COW
mdefine_line|#define _CACHE_CACHABLE_COW         (3&lt;&lt;3)  /* Au1x                    */
macro_line|#else
DECL|macro|_PAGE_PRESENT
mdefine_line|#define _PAGE_PRESENT               (1&lt;&lt;0)  /* implemented in software */
DECL|macro|_PAGE_READ
mdefine_line|#define _PAGE_READ                  (1&lt;&lt;1)  /* implemented in software */
DECL|macro|_PAGE_WRITE
mdefine_line|#define _PAGE_WRITE                 (1&lt;&lt;2)  /* implemented in software */
DECL|macro|_PAGE_ACCESSED
mdefine_line|#define _PAGE_ACCESSED              (1&lt;&lt;3)  /* implemented in software */
DECL|macro|_PAGE_MODIFIED
mdefine_line|#define _PAGE_MODIFIED              (1&lt;&lt;4)  /* implemented in software */
DECL|macro|_PAGE_FILE
mdefine_line|#define _PAGE_FILE                  (1&lt;&lt;4)  /* set:pagecache unset:swap */
macro_line|#if defined(CONFIG_CPU_R3000) || defined(CONFIG_CPU_TX39XX)
DECL|macro|_PAGE_GLOBAL
mdefine_line|#define _PAGE_GLOBAL                (1&lt;&lt;8)
DECL|macro|_PAGE_VALID
mdefine_line|#define _PAGE_VALID                 (1&lt;&lt;9)
DECL|macro|_PAGE_SILENT_READ
mdefine_line|#define _PAGE_SILENT_READ           (1&lt;&lt;9)  /* synonym                 */
DECL|macro|_PAGE_DIRTY
mdefine_line|#define _PAGE_DIRTY                 (1&lt;&lt;10) /* The MIPS dirty bit      */
DECL|macro|_PAGE_SILENT_WRITE
mdefine_line|#define _PAGE_SILENT_WRITE          (1&lt;&lt;10)
DECL|macro|_CACHE_UNCACHED
mdefine_line|#define _CACHE_UNCACHED             (1&lt;&lt;11)
DECL|macro|_CACHE_MASK
mdefine_line|#define _CACHE_MASK                 (1&lt;&lt;11)
DECL|macro|_CACHE_CACHABLE_NONCOHERENT
mdefine_line|#define _CACHE_CACHABLE_NONCOHERENT 0
macro_line|#else
DECL|macro|_PAGE_R4KBUG
mdefine_line|#define _PAGE_R4KBUG                (1&lt;&lt;5)  /* workaround for r4k bug  */
DECL|macro|_PAGE_GLOBAL
mdefine_line|#define _PAGE_GLOBAL                (1&lt;&lt;6)
DECL|macro|_PAGE_VALID
mdefine_line|#define _PAGE_VALID                 (1&lt;&lt;7)
DECL|macro|_PAGE_SILENT_READ
mdefine_line|#define _PAGE_SILENT_READ           (1&lt;&lt;7)  /* synonym                 */
DECL|macro|_PAGE_DIRTY
mdefine_line|#define _PAGE_DIRTY                 (1&lt;&lt;8)  /* The MIPS dirty bit      */
DECL|macro|_PAGE_SILENT_WRITE
mdefine_line|#define _PAGE_SILENT_WRITE          (1&lt;&lt;8)
DECL|macro|_CACHE_MASK
mdefine_line|#define _CACHE_MASK                 (7&lt;&lt;9)
macro_line|#ifdef CONFIG_CPU_SB1
multiline_comment|/* No penalty for being coherent on the SB1, so just&n;   use it for &quot;noncoherent&quot; spaces, too.  Shouldn&squot;t hurt. */
DECL|macro|_CACHE_UNCACHED
mdefine_line|#define _CACHE_UNCACHED             (2&lt;&lt;9)
DECL|macro|_CACHE_CACHABLE_COW
mdefine_line|#define _CACHE_CACHABLE_COW         (5&lt;&lt;9)
DECL|macro|_CACHE_CACHABLE_NONCOHERENT
mdefine_line|#define _CACHE_CACHABLE_NONCOHERENT (5&lt;&lt;9)
DECL|macro|_CACHE_UNCACHED_ACCELERATED
mdefine_line|#define _CACHE_UNCACHED_ACCELERATED (7&lt;&lt;9)
macro_line|#elif defined(CONFIG_CPU_RM9000)
DECL|macro|_CACHE_WT
mdefine_line|#define _CACHE_WT&t;&t;&t;(0 &lt;&lt; 9)
DECL|macro|_CACHE_WTWA
mdefine_line|#define _CACHE_WTWA&t;&t;&t;(1 &lt;&lt; 9)
DECL|macro|_CACHE_UC_B
mdefine_line|#define _CACHE_UC_B&t;&t;&t;(2 &lt;&lt; 9)
DECL|macro|_CACHE_WB
mdefine_line|#define _CACHE_WB&t;&t;&t;(3 &lt;&lt; 9)
DECL|macro|_CACHE_CWBEA
mdefine_line|#define _CACHE_CWBEA&t;&t;&t;(4 &lt;&lt; 9)
DECL|macro|_CACHE_CWB
mdefine_line|#define _CACHE_CWB&t;&t;&t;(5 &lt;&lt; 9)
DECL|macro|_CACHE_UCNB
mdefine_line|#define _CACHE_UCNB&t;&t;&t;(6 &lt;&lt; 9)
DECL|macro|_CACHE_FPC
mdefine_line|#define _CACHE_FPC&t;&t;&t;(7 &lt;&lt; 9)
DECL|macro|_CACHE_UNCACHED
mdefine_line|#define _CACHE_UNCACHED&t;&t;&t;_CACHE_UC_B
DECL|macro|_CACHE_CACHABLE_NONCOHERENT
mdefine_line|#define _CACHE_CACHABLE_NONCOHERENT&t;_CACHE_WB
macro_line|#else
DECL|macro|_CACHE_CACHABLE_NO_WA
mdefine_line|#define _CACHE_CACHABLE_NO_WA       (0&lt;&lt;9)  /* R4600 only              */
DECL|macro|_CACHE_CACHABLE_WA
mdefine_line|#define _CACHE_CACHABLE_WA          (1&lt;&lt;9)  /* R4600 only              */
DECL|macro|_CACHE_UNCACHED
mdefine_line|#define _CACHE_UNCACHED             (2&lt;&lt;9)  /* R4[0246]00              */
DECL|macro|_CACHE_CACHABLE_NONCOHERENT
mdefine_line|#define _CACHE_CACHABLE_NONCOHERENT (3&lt;&lt;9)  /* R4[0246]00              */
DECL|macro|_CACHE_CACHABLE_CE
mdefine_line|#define _CACHE_CACHABLE_CE          (4&lt;&lt;9)  /* R4[04]00MC only         */
DECL|macro|_CACHE_CACHABLE_COW
mdefine_line|#define _CACHE_CACHABLE_COW         (5&lt;&lt;9)  /* R4[04]00MC only         */
DECL|macro|_CACHE_CACHABLE_CUW
mdefine_line|#define _CACHE_CACHABLE_CUW         (6&lt;&lt;9)  /* R4[04]00MC only         */
DECL|macro|_CACHE_UNCACHED_ACCELERATED
mdefine_line|#define _CACHE_UNCACHED_ACCELERATED (7&lt;&lt;9)  /* R10000 only             */
macro_line|#endif
macro_line|#endif
macro_line|#endif /* defined(CONFIG_CPU_MIPS32) &amp;&amp; defined(CONFIG_64BIT_PHYS_ADDR) */
DECL|macro|__READABLE
mdefine_line|#define __READABLE&t;(_PAGE_READ | _PAGE_SILENT_READ | _PAGE_ACCESSED)
DECL|macro|__WRITEABLE
mdefine_line|#define __WRITEABLE&t;(_PAGE_WRITE | _PAGE_SILENT_WRITE | _PAGE_MODIFIED)
DECL|macro|_PAGE_CHG_MASK
mdefine_line|#define _PAGE_CHG_MASK  (PAGE_MASK | _PAGE_ACCESSED | _PAGE_MODIFIED | _CACHE_MASK)
macro_line|#ifdef CONFIG_MIPS_UNCACHED
DECL|macro|PAGE_CACHABLE_DEFAULT
mdefine_line|#define PAGE_CACHABLE_DEFAULT&t;_CACHE_UNCACHED
macro_line|#elif defined(CONFIG_DMA_NONCOHERENT)
DECL|macro|PAGE_CACHABLE_DEFAULT
mdefine_line|#define PAGE_CACHABLE_DEFAULT&t;_CACHE_CACHABLE_NONCOHERENT
macro_line|#elif defined(CONFIG_CPU_RM9000)
DECL|macro|PAGE_CACHABLE_DEFAULT
mdefine_line|#define PAGE_CACHABLE_DEFAULT&t;_CACHE_CWB
macro_line|#else
DECL|macro|PAGE_CACHABLE_DEFAULT
mdefine_line|#define PAGE_CACHABLE_DEFAULT&t;_CACHE_CACHABLE_COW
macro_line|#endif
macro_line|#if defined(CONFIG_CPU_MIPS32) &amp;&amp; defined(CONFIG_64BIT_PHYS_ADDR)
DECL|macro|CONF_CM_DEFAULT
mdefine_line|#define CONF_CM_DEFAULT&t;&t;(PAGE_CACHABLE_DEFAULT &gt;&gt; 3)
macro_line|#else
DECL|macro|CONF_CM_DEFAULT
mdefine_line|#define CONF_CM_DEFAULT&t;&t;(PAGE_CACHABLE_DEFAULT &gt;&gt; 9)
macro_line|#endif
macro_line|#endif /* _ASM_PGTABLE_BITS_H */
eof
