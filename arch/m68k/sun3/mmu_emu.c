multiline_comment|/*&n;** Tablewalk MMU emulator&n;**&n;** by Toshiyasu Morita&n;**&n;** Started 1/16/98 @ 2:22 am&n;*/
macro_line|#include &lt;linux/mman.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;linux/bitops.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/traps.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/sun3mmu.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/oplib.h&gt;
macro_line|#include &lt;asm/mmu_context.h&gt;
macro_line|#include &lt;asm/dvma.h&gt;
r_extern
r_void
id|prom_reboot
(paren
r_char
op_star
)paren
id|__attribute__
(paren
(paren
id|__noreturn__
)paren
)paren
suffix:semicolon
DECL|macro|DEBUG_MMU_EMU
macro_line|#undef DEBUG_MMU_EMU
DECL|macro|DEBUG_PROM_MAPS
mdefine_line|#define DEBUG_PROM_MAPS
multiline_comment|/*&n;** Defines&n;*/
DECL|macro|CONTEXTS_NUM
mdefine_line|#define CONTEXTS_NUM&t;&t;8
DECL|macro|SEGMAPS_PER_CONTEXT_NUM
mdefine_line|#define SEGMAPS_PER_CONTEXT_NUM 2048
DECL|macro|PAGES_PER_SEGMENT
mdefine_line|#define PAGES_PER_SEGMENT&t;16
DECL|macro|PMEGS_NUM
mdefine_line|#define PMEGS_NUM&t;&t;256
DECL|macro|PMEG_MASK
mdefine_line|#define PMEG_MASK&t;&t;0xFF
multiline_comment|/*&n;** Globals&n;*/
DECL|variable|vmalloc_end
r_int
r_int
id|vmalloc_end
suffix:semicolon
DECL|variable|pmeg_vaddr
r_int
r_int
id|pmeg_vaddr
(braket
id|PMEGS_NUM
)braket
suffix:semicolon
DECL|variable|pmeg_alloc
r_int
r_char
id|pmeg_alloc
(braket
id|PMEGS_NUM
)braket
suffix:semicolon
DECL|variable|pmeg_ctx
r_int
r_char
id|pmeg_ctx
(braket
id|PMEGS_NUM
)braket
suffix:semicolon
multiline_comment|/* pointers to the mm structs for each task in each&n;   context. 0xffffffff is a marker for kernel context */
DECL|variable|ctx_alloc
r_struct
id|mm_struct
op_star
id|ctx_alloc
(braket
id|CONTEXTS_NUM
)braket
op_assign
(brace
(braket
l_int|0
)braket
op_assign
(paren
r_struct
id|mm_struct
op_star
)paren
l_int|0xffffffff
)brace
suffix:semicolon
multiline_comment|/* has this context been mmdrop&squot;d? */
DECL|variable|ctx_avail
r_static
r_int
r_char
id|ctx_avail
op_assign
id|CONTEXTS_NUM
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* array of pages to be marked off for the rom when we do mem_init later */
multiline_comment|/* 256 pages lets the rom take up to 2mb of physical ram..  I really&n;   hope it never wants mote than that. */
DECL|variable|rom_pages
r_int
r_int
id|rom_pages
(braket
l_int|256
)braket
suffix:semicolon
multiline_comment|/* Print a PTE value in symbolic form. For debugging. */
DECL|function|print_pte
r_void
id|print_pte
(paren
id|pte_t
id|pte
)paren
(brace
macro_line|#if 0
multiline_comment|/* Verbose version. */
r_int
r_int
id|val
op_assign
id|pte_val
(paren
id|pte
)paren
suffix:semicolon
id|printk
(paren
l_string|&quot; pte=%lx [addr=%lx&quot;
comma
id|val
comma
(paren
id|val
op_amp
id|SUN3_PAGE_PGNUM_MASK
)paren
op_lshift
id|PAGE_SHIFT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|val
op_amp
id|SUN3_PAGE_VALID
)paren
id|printk
(paren
l_string|&quot; valid&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|val
op_amp
id|SUN3_PAGE_WRITEABLE
)paren
id|printk
(paren
l_string|&quot; write&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|val
op_amp
id|SUN3_PAGE_SYSTEM
)paren
id|printk
(paren
l_string|&quot; sys&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|val
op_amp
id|SUN3_PAGE_NOCACHE
)paren
id|printk
(paren
l_string|&quot; nocache&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|val
op_amp
id|SUN3_PAGE_ACCESSED
)paren
id|printk
(paren
l_string|&quot; accessed&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|val
op_amp
id|SUN3_PAGE_MODIFIED
)paren
id|printk
(paren
l_string|&quot; modified&quot;
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|val
op_amp
id|SUN3_PAGE_TYPE_MASK
)paren
(brace
r_case
id|SUN3_PAGE_TYPE_MEMORY
suffix:colon
id|printk
(paren
l_string|&quot; memory&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SUN3_PAGE_TYPE_IO
suffix:colon
id|printk
(paren
l_string|&quot; io&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SUN3_PAGE_TYPE_VME16
suffix:colon
id|printk
(paren
l_string|&quot; vme16&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SUN3_PAGE_TYPE_VME32
suffix:colon
id|printk
(paren
l_string|&quot; vme32&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|printk
(paren
l_string|&quot;]&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#else
multiline_comment|/* Terse version. More likely to fit on a line. */
r_int
r_int
id|val
op_assign
id|pte_val
(paren
id|pte
)paren
suffix:semicolon
r_char
id|flags
(braket
l_int|7
)braket
comma
op_star
id|type
suffix:semicolon
id|flags
(braket
l_int|0
)braket
op_assign
(paren
id|val
op_amp
id|SUN3_PAGE_VALID
)paren
ques
c_cond
l_char|&squot;v&squot;
suffix:colon
l_char|&squot;-&squot;
suffix:semicolon
id|flags
(braket
l_int|1
)braket
op_assign
(paren
id|val
op_amp
id|SUN3_PAGE_WRITEABLE
)paren
ques
c_cond
l_char|&squot;w&squot;
suffix:colon
l_char|&squot;-&squot;
suffix:semicolon
id|flags
(braket
l_int|2
)braket
op_assign
(paren
id|val
op_amp
id|SUN3_PAGE_SYSTEM
)paren
ques
c_cond
l_char|&squot;s&squot;
suffix:colon
l_char|&squot;-&squot;
suffix:semicolon
id|flags
(braket
l_int|3
)braket
op_assign
(paren
id|val
op_amp
id|SUN3_PAGE_NOCACHE
)paren
ques
c_cond
l_char|&squot;x&squot;
suffix:colon
l_char|&squot;-&squot;
suffix:semicolon
id|flags
(braket
l_int|4
)braket
op_assign
(paren
id|val
op_amp
id|SUN3_PAGE_ACCESSED
)paren
ques
c_cond
l_char|&squot;a&squot;
suffix:colon
l_char|&squot;-&squot;
suffix:semicolon
id|flags
(braket
l_int|5
)braket
op_assign
(paren
id|val
op_amp
id|SUN3_PAGE_MODIFIED
)paren
ques
c_cond
l_char|&squot;m&squot;
suffix:colon
l_char|&squot;-&squot;
suffix:semicolon
id|flags
(braket
l_int|6
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_switch
c_cond
(paren
id|val
op_amp
id|SUN3_PAGE_TYPE_MASK
)paren
(brace
r_case
id|SUN3_PAGE_TYPE_MEMORY
suffix:colon
id|type
op_assign
l_string|&quot;memory&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SUN3_PAGE_TYPE_IO
suffix:colon
id|type
op_assign
l_string|&quot;io&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SUN3_PAGE_TYPE_VME16
suffix:colon
id|type
op_assign
l_string|&quot;vme16&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SUN3_PAGE_TYPE_VME32
suffix:colon
id|type
op_assign
l_string|&quot;vme32&quot;
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|type
op_assign
l_string|&quot;unknown?&quot;
suffix:semicolon
r_break
suffix:semicolon
)brace
id|printk
(paren
l_string|&quot; pte=%08lx [%07lx %s %s]&bslash;n&quot;
comma
id|val
comma
(paren
id|val
op_amp
id|SUN3_PAGE_PGNUM_MASK
)paren
op_lshift
id|PAGE_SHIFT
comma
id|flags
comma
id|type
)paren
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/* Print the PTE value for a given virtual address. For debugging. */
DECL|function|print_pte_vaddr
r_void
id|print_pte_vaddr
(paren
r_int
r_int
id|vaddr
)paren
(brace
id|printk
(paren
l_string|&quot; vaddr=%lx [%02lx]&quot;
comma
id|vaddr
comma
id|sun3_get_segmap
(paren
id|vaddr
)paren
)paren
suffix:semicolon
id|print_pte
(paren
id|__pte
(paren
id|sun3_get_pte
(paren
id|vaddr
)paren
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Initialise the MMU emulator.&n; */
DECL|function|mmu_emu_init
r_void
id|mmu_emu_init
c_func
(paren
r_int
r_int
id|bootmem_end
)paren
(brace
r_int
r_int
id|seg
comma
id|num
suffix:semicolon
r_int
id|i
comma
id|j
suffix:semicolon
id|memset
c_func
(paren
id|rom_pages
comma
l_int|0
comma
r_sizeof
(paren
id|rom_pages
)paren
)paren
suffix:semicolon
id|memset
c_func
(paren
id|pmeg_vaddr
comma
l_int|0
comma
r_sizeof
(paren
id|pmeg_vaddr
)paren
)paren
suffix:semicolon
id|memset
c_func
(paren
id|pmeg_alloc
comma
l_int|0
comma
r_sizeof
(paren
id|pmeg_alloc
)paren
)paren
suffix:semicolon
id|memset
c_func
(paren
id|pmeg_ctx
comma
l_int|0
comma
r_sizeof
(paren
id|pmeg_ctx
)paren
)paren
suffix:semicolon
multiline_comment|/* pmeg align the end of bootmem, adding another pmeg,&n;&t; * later bootmem allocations will likely need it */
id|bootmem_end
op_assign
(paren
id|bootmem_end
op_plus
(paren
l_int|2
op_star
id|SUN3_PMEG_SIZE
)paren
)paren
op_amp
op_complement
id|SUN3_PMEG_MASK
suffix:semicolon
multiline_comment|/* mark all of the pmegs used thus far as reserved */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|__pa
c_func
(paren
id|bootmem_end
)paren
op_div
id|SUN3_PMEG_SIZE
suffix:semicolon
op_increment
id|i
)paren
id|pmeg_alloc
(braket
id|i
)braket
op_assign
l_int|2
suffix:semicolon
multiline_comment|/* I&squot;m thinking that most of the top pmeg&squot;s are going to be&n;&t;   used for something, and we probably shouldn&squot;t risk it */
r_for
c_loop
(paren
id|num
op_assign
l_int|0xf0
suffix:semicolon
id|num
op_le
l_int|0xff
suffix:semicolon
id|num
op_increment
)paren
(brace
id|pmeg_alloc
(braket
id|num
)braket
op_assign
l_int|2
suffix:semicolon
)brace
multiline_comment|/* liberate all existing mappings in the rest of kernel space */
r_for
c_loop
(paren
id|seg
op_assign
id|bootmem_end
suffix:semicolon
id|seg
OL
l_int|0x0f800000
suffix:semicolon
id|seg
op_add_assign
id|SUN3_PMEG_SIZE
)paren
(brace
id|i
op_assign
id|sun3_get_segmap
c_func
(paren
id|seg
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pmeg_alloc
(braket
id|i
)braket
)paren
(brace
macro_line|#ifdef DEBUG_MMU_EMU
id|printk
c_func
(paren
l_string|&quot;freed: &quot;
)paren
suffix:semicolon
id|print_pte_vaddr
(paren
id|seg
)paren
suffix:semicolon
macro_line|#endif
id|sun3_put_segmap
c_func
(paren
id|seg
comma
id|SUN3_INVALID_PMEG
)paren
suffix:semicolon
)brace
)brace
id|j
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|num
op_assign
l_int|0
comma
id|seg
op_assign
l_int|0x0F800000
suffix:semicolon
id|seg
OL
l_int|0x10000000
suffix:semicolon
id|seg
op_add_assign
l_int|16
op_star
id|PAGE_SIZE
)paren
(brace
r_if
c_cond
(paren
id|sun3_get_segmap
(paren
id|seg
)paren
op_ne
id|SUN3_INVALID_PMEG
)paren
(brace
macro_line|#ifdef DEBUG_PROM_MAPS
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|16
suffix:semicolon
id|i
op_increment
)paren
(brace
id|printk
(paren
l_string|&quot;mapped:&quot;
)paren
suffix:semicolon
id|print_pte_vaddr
(paren
id|seg
op_plus
(paren
id|i
op_star
id|PAGE_SIZE
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
macro_line|#endif
singleline_comment|// the lowest mapping here is the end of our
singleline_comment|// vmalloc region
r_if
c_cond
(paren
op_logical_neg
id|vmalloc_end
)paren
(brace
id|vmalloc_end
op_assign
id|seg
suffix:semicolon
)brace
singleline_comment|// mark the segmap alloc&squot;d, and reserve any
singleline_comment|// of the first 0xbff pages the hardware is
singleline_comment|// already using...  does any sun3 support &gt; 24mb?
id|pmeg_alloc
(braket
id|sun3_get_segmap
c_func
(paren
id|seg
)paren
)braket
op_assign
l_int|2
suffix:semicolon
)brace
)brace
id|dvma_init
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* blank everything below the kernel, and we&squot;ve got the base&n;&t;   mapping to start all the contexts off with... */
r_for
c_loop
(paren
id|seg
op_assign
l_int|0
suffix:semicolon
id|seg
OL
id|PAGE_OFFSET
suffix:semicolon
id|seg
op_add_assign
id|SUN3_PMEG_SIZE
)paren
(brace
id|sun3_put_segmap
c_func
(paren
id|seg
comma
id|SUN3_INVALID_PMEG
)paren
suffix:semicolon
)brace
id|set_fs
c_func
(paren
id|MAKE_MM_SEG
c_func
(paren
l_int|3
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|seg
op_assign
l_int|0
suffix:semicolon
id|seg
OL
l_int|0x10000000
suffix:semicolon
id|seg
op_add_assign
id|SUN3_PMEG_SIZE
)paren
(brace
id|i
op_assign
id|sun3_get_segmap
c_func
(paren
id|seg
)paren
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|1
suffix:semicolon
id|j
OL
id|CONTEXTS_NUM
suffix:semicolon
id|j
op_increment
)paren
(brace
(paren
op_star
(paren
id|romvec-&gt;pv_setctxt
)paren
)paren
(paren
id|j
comma
(paren
r_void
op_star
)paren
id|seg
comma
id|i
)paren
suffix:semicolon
)brace
)brace
id|set_fs
c_func
(paren
id|KERNEL_DS
)paren
suffix:semicolon
)brace
multiline_comment|/* erase the mappings for a dead context.  Uses the pg_dir for hints&n;   as the pmeg tables proved somewhat unreliable, and unmapping all of&n;   TASK_SIZE was much slower and no more stable. */
multiline_comment|/* todo: find a better way to keep track of the pmegs used by a&n;   context for when they&squot;re cleared */
DECL|function|clear_context
r_void
id|clear_context
c_func
(paren
r_int
r_int
id|context
)paren
(brace
r_int
r_char
id|oldctx
suffix:semicolon
r_int
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|context
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|ctx_alloc
(braket
id|context
)braket
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;clear_context: context not allocated&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|ctx_alloc
(braket
id|context
)braket
op_member_access_from_pointer
id|context
op_assign
id|SUN3_INVALID_CONTEXT
suffix:semicolon
id|ctx_alloc
(braket
id|context
)braket
op_assign
(paren
r_struct
id|mm_struct
op_star
)paren
l_int|0
suffix:semicolon
id|ctx_avail
op_increment
suffix:semicolon
)brace
id|oldctx
op_assign
id|sun3_get_context
c_func
(paren
)paren
suffix:semicolon
id|sun3_put_context
c_func
(paren
id|context
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|SUN3_INVALID_PMEG
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
id|pmeg_ctx
(braket
id|i
)braket
op_eq
id|context
)paren
op_logical_and
(paren
id|pmeg_alloc
(braket
id|i
)braket
op_eq
l_int|1
)paren
)paren
(brace
id|sun3_put_segmap
c_func
(paren
id|pmeg_vaddr
(braket
id|i
)braket
comma
id|SUN3_INVALID_PMEG
)paren
suffix:semicolon
id|pmeg_ctx
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
id|pmeg_alloc
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
id|pmeg_vaddr
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
)brace
)brace
id|sun3_put_context
c_func
(paren
id|oldctx
)paren
suffix:semicolon
)brace
multiline_comment|/* gets an empty context.  if full, kills the next context listed to&n;   die first */
multiline_comment|/* This context invalidation scheme is, well, totally arbitrary, I&squot;m&n;   sure it could be much more intellegent...  but it gets the job done&n;   for now without much overhead in making it&squot;s decision. */
multiline_comment|/* todo: come up with optimized scheme for flushing contexts */
DECL|function|get_free_context
r_int
r_int
id|get_free_context
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
r_int
r_int
r_new
op_assign
l_int|1
suffix:semicolon
r_static
r_int
r_char
id|next_to_die
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ctx_avail
)paren
(brace
multiline_comment|/* kill someone to get our context */
r_new
op_assign
id|next_to_die
suffix:semicolon
id|clear_context
c_func
(paren
r_new
)paren
suffix:semicolon
id|next_to_die
op_assign
(paren
id|next_to_die
op_plus
l_int|1
)paren
op_amp
l_int|0x7
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|next_to_die
)paren
(brace
id|next_to_die
op_increment
suffix:semicolon
)brace
)brace
r_else
(brace
r_while
c_loop
(paren
r_new
OL
id|CONTEXTS_NUM
)paren
(brace
r_if
c_cond
(paren
id|ctx_alloc
(braket
r_new
)braket
)paren
(brace
r_new
op_increment
suffix:semicolon
)brace
r_else
r_break
suffix:semicolon
)brace
singleline_comment|// check to make sure one was really free...
r_if
c_cond
(paren
r_new
op_eq
id|CONTEXTS_NUM
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;get_free_context: failed to find free context&quot;
)paren
suffix:semicolon
)brace
)brace
id|ctx_alloc
(braket
r_new
)braket
op_assign
id|mm
suffix:semicolon
id|ctx_avail
op_decrement
suffix:semicolon
r_return
r_new
suffix:semicolon
)brace
multiline_comment|/*&n; * Dynamically select a `spare&squot; PMEG and use it to map virtual `vaddr&squot; in&n; * `context&squot;. Maintain internal PMEG management structures. This doesn&squot;t&n; * actually map the physical address, but does clear the old mappings.&n; */
singleline_comment|//todo: better allocation scheme? but is extra complexity worthwhile?
singleline_comment|//todo: only clear old entries if necessary? how to tell?
DECL|function|mmu_emu_map_pmeg
r_inline
r_void
id|mmu_emu_map_pmeg
(paren
r_int
id|context
comma
r_int
id|vaddr
)paren
(brace
r_static
r_int
r_char
id|curr_pmeg
op_assign
l_int|128
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/* Round address to PMEG boundary. */
id|vaddr
op_and_assign
op_complement
id|SUN3_PMEG_MASK
suffix:semicolon
multiline_comment|/* Find a spare one. */
r_while
c_loop
(paren
id|pmeg_alloc
(braket
id|curr_pmeg
)braket
op_eq
l_int|2
)paren
op_increment
id|curr_pmeg
suffix:semicolon
macro_line|#ifdef DEBUG_MMU_EMU
id|printk
c_func
(paren
l_string|&quot;mmu_emu_map_pmeg: pmeg %x to context %d vaddr %x&bslash;n&quot;
comma
id|curr_pmeg
comma
id|context
comma
id|vaddr
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Invalidate old mapping for the pmeg, if any */
r_if
c_cond
(paren
id|pmeg_alloc
(braket
id|curr_pmeg
)braket
op_eq
l_int|1
)paren
(brace
id|sun3_put_context
c_func
(paren
id|pmeg_ctx
(braket
id|curr_pmeg
)braket
)paren
suffix:semicolon
id|sun3_put_segmap
(paren
id|pmeg_vaddr
(braket
id|curr_pmeg
)braket
comma
id|SUN3_INVALID_PMEG
)paren
suffix:semicolon
id|sun3_put_context
c_func
(paren
id|context
)paren
suffix:semicolon
)brace
multiline_comment|/* Update PMEG management structures. */
singleline_comment|// don&squot;t take pmeg&squot;s away from the kernel...
r_if
c_cond
(paren
id|vaddr
op_ge
id|PAGE_OFFSET
)paren
(brace
multiline_comment|/* map kernel pmegs into all contexts */
r_int
r_char
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|CONTEXTS_NUM
suffix:semicolon
id|i
op_increment
)paren
(brace
id|sun3_put_context
c_func
(paren
id|i
)paren
suffix:semicolon
id|sun3_put_segmap
(paren
id|vaddr
comma
id|curr_pmeg
)paren
suffix:semicolon
)brace
id|sun3_put_context
c_func
(paren
id|context
)paren
suffix:semicolon
id|pmeg_alloc
(braket
id|curr_pmeg
)braket
op_assign
l_int|2
suffix:semicolon
id|pmeg_ctx
(braket
id|curr_pmeg
)braket
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|pmeg_alloc
(braket
id|curr_pmeg
)braket
op_assign
l_int|1
suffix:semicolon
id|pmeg_ctx
(braket
id|curr_pmeg
)braket
op_assign
id|context
suffix:semicolon
id|sun3_put_segmap
(paren
id|vaddr
comma
id|curr_pmeg
)paren
suffix:semicolon
)brace
id|pmeg_vaddr
(braket
id|curr_pmeg
)braket
op_assign
id|vaddr
suffix:semicolon
multiline_comment|/* Set hardware mapping and clear the old PTE entries. */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|SUN3_PMEG_SIZE
suffix:semicolon
id|i
op_add_assign
id|SUN3_PTE_SIZE
)paren
id|sun3_put_pte
(paren
id|vaddr
op_plus
id|i
comma
id|SUN3_PAGE_SYSTEM
)paren
suffix:semicolon
multiline_comment|/* Consider a different one next time. */
op_increment
id|curr_pmeg
suffix:semicolon
)brace
multiline_comment|/*&n; * Handle a pagefault at virtual address `vaddr&squot;; check if there should be a&n; * page there (specifically, whether the software pagetables indicate that&n; * there is). This is necessary due to the limited size of the second-level&n; * Sun3 hardware pagetables (256 groups of 16 pages). If there should be a&n; * mapping present, we select a `spare&squot; PMEG and use it to create a mapping.&n; * `read_flag&squot; is nonzero for a read fault; zero for a write. Returns nonzero&n; * if we successfully handled the fault.&n; */
singleline_comment|//todo: should we bump minor pagefault counter? if so, here or in caller?
singleline_comment|//todo: possibly inline this into bus_error030 in &lt;asm/buserror.h&gt; ?
singleline_comment|// kernel_fault is set when a kernel page couldn&squot;t be demand mapped,
singleline_comment|// and forces another try using the kernel page table.  basically a
singleline_comment|// hack so that vmalloc would work correctly.
DECL|function|mmu_emu_handle_fault
r_int
id|mmu_emu_handle_fault
(paren
r_int
r_int
id|vaddr
comma
r_int
id|read_flag
comma
r_int
id|kernel_fault
)paren
(brace
r_int
r_int
id|segment
comma
id|offset
suffix:semicolon
r_int
r_char
id|context
suffix:semicolon
id|pte_t
op_star
id|pte
suffix:semicolon
id|pgd_t
op_star
id|crp
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;mm
op_eq
l_int|NULL
)paren
(brace
id|crp
op_assign
id|swapper_pg_dir
suffix:semicolon
id|context
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|context
op_assign
id|current-&gt;mm-&gt;context
suffix:semicolon
r_if
c_cond
(paren
id|kernel_fault
)paren
(brace
id|crp
op_assign
id|swapper_pg_dir
suffix:semicolon
)brace
r_else
id|crp
op_assign
id|current-&gt;mm-&gt;pgd
suffix:semicolon
)brace
macro_line|#ifdef DEBUG_MMU_EMU
id|printk
(paren
l_string|&quot;mmu_emu_handle_fault: vaddr=%lx type=%s crp=%p&bslash;n&quot;
comma
id|vaddr
comma
id|read_flag
ques
c_cond
l_string|&quot;read&quot;
suffix:colon
l_string|&quot;write&quot;
comma
id|crp
)paren
suffix:semicolon
macro_line|#endif
id|segment
op_assign
(paren
id|vaddr
op_rshift
id|SUN3_PMEG_SIZE_BITS
)paren
op_amp
l_int|0x7FF
suffix:semicolon
id|offset
op_assign
(paren
id|vaddr
op_rshift
id|SUN3_PTE_SIZE_BITS
)paren
op_amp
l_int|0xF
suffix:semicolon
macro_line|#ifdef DEBUG_MMU_EMU
id|printk
(paren
l_string|&quot;mmu_emu_handle_fault: segment=%lx offset=%lx&bslash;n&quot;
comma
id|segment
comma
id|offset
)paren
suffix:semicolon
macro_line|#endif
id|pte
op_assign
(paren
id|pte_t
op_star
)paren
id|pgd_val
(paren
op_star
(paren
id|crp
op_plus
id|segment
)paren
)paren
suffix:semicolon
singleline_comment|//todo: next line should check for valid pmd properly.
r_if
c_cond
(paren
op_logical_neg
id|pte
)paren
(brace
singleline_comment|//                printk (&quot;mmu_emu_handle_fault: invalid pmd&bslash;n&quot;);
r_return
l_int|0
suffix:semicolon
)brace
id|pte
op_assign
(paren
id|pte_t
op_star
)paren
id|__va
(paren
(paren
r_int
r_int
)paren
(paren
id|pte
op_plus
id|offset
)paren
)paren
suffix:semicolon
multiline_comment|/* Make sure this is a valid page */
r_if
c_cond
(paren
op_logical_neg
(paren
id|pte_val
(paren
op_star
id|pte
)paren
op_amp
id|SUN3_PAGE_VALID
)paren
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Make sure there&squot;s a pmeg allocated for the page */
r_if
c_cond
(paren
id|sun3_get_segmap
(paren
id|vaddr
op_amp
op_complement
id|SUN3_PMEG_MASK
)paren
op_eq
id|SUN3_INVALID_PMEG
)paren
id|mmu_emu_map_pmeg
(paren
id|context
comma
id|vaddr
)paren
suffix:semicolon
multiline_comment|/* Write the pte value to hardware MMU */
id|sun3_put_pte
(paren
id|vaddr
op_amp
id|PAGE_MASK
comma
id|pte_val
(paren
op_star
id|pte
)paren
)paren
suffix:semicolon
multiline_comment|/* Update software copy of the pte value */
singleline_comment|// I&squot;m not sure this is necessary. If this is required, we ought to simply
singleline_comment|// copy this out when we reuse the PMEG or at some other convenient time.
singleline_comment|// Doing it here is fairly meaningless, anyway, as we only know about the
singleline_comment|// first access to a given page. --m
r_if
c_cond
(paren
op_logical_neg
id|read_flag
)paren
(brace
r_if
c_cond
(paren
id|pte_val
(paren
op_star
id|pte
)paren
op_amp
id|SUN3_PAGE_WRITEABLE
)paren
id|pte_val
(paren
op_star
id|pte
)paren
op_or_assign
(paren
id|SUN3_PAGE_ACCESSED
op_or
id|SUN3_PAGE_MODIFIED
)paren
suffix:semicolon
r_else
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Write-protect error. */
)brace
r_else
id|pte_val
(paren
op_star
id|pte
)paren
op_or_assign
id|SUN3_PAGE_ACCESSED
suffix:semicolon
macro_line|#ifdef DEBUG_MMU_EMU
id|printk
(paren
l_string|&quot;seg:%d crp:%p -&gt;&quot;
comma
id|get_fs
c_func
(paren
)paren
dot
id|seg
comma
id|crp
)paren
suffix:semicolon
id|print_pte_vaddr
(paren
id|vaddr
)paren
suffix:semicolon
id|printk
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|1
suffix:semicolon
)brace
eof
