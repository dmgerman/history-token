multiline_comment|/*&n; * BK Id: %F% %I% %G% %U% %#%&n; */
multiline_comment|/*&n; * This file contains the routines for initializing the MMU&n; * on the 4xx series of chips.&n; *  -- paulus&n; * &n; *  Derived from arch/ppc/mm/init.c:&n; *    Copyright (C) 1995-1996 Gary Thomas (gdt@linuxppc.org)&n; *&n; *  Modifications by Paul Mackerras (PowerMac) (paulus@cs.anu.edu.au)&n; *  and Cort Dougan (PReP) (cort@cs.nmt.edu)&n; *    Copyright (C) 1996 Paul Mackerras&n; *  Amiga/APUS changes by Jesper Skov (jskov@cygnus.co.uk).&n; *&n; *  Derived from &quot;arch/i386/mm/init.c&quot;&n; *    Copyright (C) 1991, 1992, 1993, 1994  Linus Torvalds&n; *&n; *  This program is free software; you can redistribute it and/or&n; *  modify it under the terms of the GNU General Public License&n; *  as published by the Free Software Foundation; either version&n; *  2 of the License, or (at your option) any later version.&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/mman.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/swap.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;linux/highmem.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/prom.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/mmu_context.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/mmu.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#include &lt;asm/bootx.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
multiline_comment|/* Used by the 4xx TLB replacement exception handler.&n; * Just needed it declared someplace (and initialized to zero).&n; */
DECL|variable|tlb_4xx_index
r_int
r_int
id|tlb_4xx_index
suffix:semicolon
multiline_comment|/*&n; * MMU_init_hw does the chip-specific initialization of the MMU hardware.&n; */
DECL|function|MMU_init_hw
r_void
id|__init
id|MMU_init_hw
c_func
(paren
r_void
)paren
(brace
multiline_comment|/*&n;&t; * The Zone Protection Register (ZPR) defines how protection will&n;&t; * be applied to every page which is a member of a given zone. At&n;&t; * present, we utilize only two of the 4xx&squot;s zones.&n;&t; * The zone index bits (of ZSEL) in the PTE are used for software&n;&t; * indicators, except the LSB.  For user access, zone 15 is used,&n;&t; * for kernel access, zone 14 is used.  We set all but zone 15&n;&t; * to zero, allowing only kernel access as indicated in the PTE.&n;&t; * For zone 15, we set a 01 binary (a value of 10 will not work)&n;&t; * to allow user access as indicated in the PTE.  This also allows&n;&t; * kernel access as indicated in the PTE.&n;&t; */
id|mtspr
c_func
(paren
id|SPRN_ZPR
comma
l_int|0x00000001
)paren
suffix:semicolon
id|flush_instruction_cache
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Set up the real-mode cache parameters for the exception vector&n;&t; * handlers (which are run in real-mode).&n;&t; */
id|mtspr
c_func
(paren
id|SPRN_DCWR
comma
l_int|0x00000000
)paren
suffix:semicolon
multiline_comment|/* All caching is write-back */
multiline_comment|/*&n;&t; * Cache instruction and data space where the exception&n;&t; * vectors and the kernel live in real-mode.&n;&t; */
id|mtspr
c_func
(paren
id|SPRN_DCCR
comma
l_int|0x80000000
)paren
suffix:semicolon
multiline_comment|/* 128 MB of data space at 0x0. */
id|mtspr
c_func
(paren
id|SPRN_ICCR
comma
l_int|0x80000000
)paren
suffix:semicolon
multiline_comment|/* 128 MB of instr. space at 0x0. */
)brace
eof
