multiline_comment|/*&n; * arch/v850/kernel/setup.c -- Arch-dependent initialization functions&n; *&n; *  Copyright (C) 2001,02  NEC Corporation&n; *  Copyright (C) 2001,02  Miles Bader &lt;miles@gnu.org&gt;&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.&n; *&n; * Written by Miles Bader &lt;miles@gnu.org&gt;&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/reboot.h&gt;
macro_line|#include &lt;linux/personality.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/root_dev.h&gt;
macro_line|#include &lt;linux/mtd/mtd.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &quot;mach.h&quot;
multiline_comment|/* These symbols are all defined in the linker map to delineate various&n;   statically allocated regions of memory.  */
r_extern
r_char
id|_intv_start
comma
id|_intv_end
suffix:semicolon
multiline_comment|/* `kram&squot; is only used if the kernel uses part of normal user RAM.  */
r_extern
r_char
id|_kram_start
id|__attribute__
(paren
(paren
id|__weak__
)paren
)paren
suffix:semicolon
r_extern
r_char
id|_kram_end
id|__attribute__
(paren
(paren
id|__weak__
)paren
)paren
suffix:semicolon
r_extern
r_char
id|_init_start
comma
id|_init_end
suffix:semicolon
r_extern
r_char
id|_bootmap
suffix:semicolon
r_extern
r_char
id|_stext
comma
id|_etext
comma
id|_sdata
comma
id|_edata
comma
id|_sbss
comma
id|_ebss
suffix:semicolon
multiline_comment|/* Many platforms use an embedded root image.  */
r_extern
r_char
id|_root_fs_image_start
id|__attribute__
(paren
(paren
id|__weak__
)paren
)paren
suffix:semicolon
r_extern
r_char
id|_root_fs_image_end
id|__attribute__
(paren
(paren
id|__weak__
)paren
)paren
suffix:semicolon
DECL|variable|command_line
r_char
id|command_line
(braket
l_int|512
)braket
suffix:semicolon
DECL|variable|saved_command_line
r_char
id|saved_command_line
(braket
l_int|512
)braket
suffix:semicolon
multiline_comment|/* Memory not used by the kernel.  */
DECL|variable|total_ram_pages
r_static
r_int
r_int
id|total_ram_pages
suffix:semicolon
multiline_comment|/* System RAM.  */
DECL|variable|ram_start
DECL|variable|ram_len
r_static
r_int
r_int
id|ram_start
op_assign
l_int|0
comma
id|ram_len
op_assign
l_int|0
suffix:semicolon
DECL|macro|ADDR_TO_PAGE_UP
mdefine_line|#define ADDR_TO_PAGE_UP(x)   ((((unsigned long)x) + PAGE_SIZE-1) &gt;&gt; PAGE_SHIFT)
DECL|macro|ADDR_TO_PAGE
mdefine_line|#define ADDR_TO_PAGE(x)&t;     (((unsigned long)x) &gt;&gt; PAGE_SHIFT)
DECL|macro|PAGE_TO_ADDR
mdefine_line|#define PAGE_TO_ADDR(x)&t;     (((unsigned long)x) &lt;&lt; PAGE_SHIFT)
r_static
r_void
id|init_mem_alloc
(paren
r_int
r_int
id|ram_start
comma
r_int
r_int
id|ram_len
)paren
suffix:semicolon
r_void
id|set_mem_root
(paren
r_void
op_star
id|addr
comma
r_int
id|len
comma
r_char
op_star
id|cmd_line
)paren
suffix:semicolon
DECL|function|setup_arch
r_void
id|__init
id|setup_arch
(paren
r_char
op_star
op_star
id|cmdline
)paren
(brace
multiline_comment|/* Keep a copy of command line */
op_star
id|cmdline
op_assign
id|command_line
suffix:semicolon
id|memcpy
(paren
id|saved_command_line
comma
id|command_line
comma
r_sizeof
id|saved_command_line
)paren
suffix:semicolon
id|saved_command_line
(braket
r_sizeof
id|saved_command_line
op_minus
l_int|1
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|console_verbose
(paren
)paren
suffix:semicolon
id|init_mm.start_code
op_assign
(paren
r_int
r_int
)paren
op_amp
id|_stext
suffix:semicolon
id|init_mm.end_code
op_assign
(paren
r_int
r_int
)paren
op_amp
id|_etext
suffix:semicolon
id|init_mm.end_data
op_assign
(paren
r_int
r_int
)paren
op_amp
id|_edata
suffix:semicolon
id|init_mm.brk
op_assign
(paren
r_int
r_int
)paren
op_amp
id|_kram_end
suffix:semicolon
multiline_comment|/* Find out what mem this machine has.  */
id|mach_get_physical_ram
(paren
op_amp
id|ram_start
comma
op_amp
id|ram_len
)paren
suffix:semicolon
multiline_comment|/* ... and tell the kernel about it.  */
id|init_mem_alloc
(paren
id|ram_start
comma
id|ram_len
)paren
suffix:semicolon
id|printk
(paren
id|KERN_INFO
l_string|&quot;CPU: %s&bslash;nPlatform: %s&bslash;n&quot;
comma
id|CPU_MODEL_LONG
comma
id|PLATFORM_LONG
)paren
suffix:semicolon
multiline_comment|/* do machine-specific setups.  */
id|mach_setup
(paren
id|cmdline
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_MTD
r_if
c_cond
(paren
op_logical_neg
id|ROOT_DEV
op_logical_and
op_amp
id|_root_fs_image_end
OG
op_amp
id|_root_fs_image_start
)paren
id|set_mem_root
(paren
op_amp
id|_root_fs_image_start
comma
op_amp
id|_root_fs_image_end
op_minus
op_amp
id|_root_fs_image_start
comma
op_star
id|cmdline
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|function|trap_init
r_void
id|__init
id|trap_init
(paren
r_void
)paren
(brace
)brace
macro_line|#ifdef CONFIG_MTD
multiline_comment|/* Set the root filesystem to be the given memory region.&n;   Some parameter may be appended to CMD_LINE.  */
DECL|function|set_mem_root
r_void
id|set_mem_root
(paren
r_void
op_star
id|addr
comma
r_int
id|len
comma
r_char
op_star
id|cmd_line
)paren
(brace
multiline_comment|/* The only way to pass info to the MTD slram driver is via&n;&t;   the command line.  */
r_if
c_cond
(paren
op_star
id|cmd_line
)paren
(brace
id|cmd_line
op_add_assign
id|strlen
(paren
id|cmd_line
)paren
suffix:semicolon
op_star
id|cmd_line
op_increment
op_assign
l_char|&squot; &squot;
suffix:semicolon
)brace
id|sprintf
(paren
id|cmd_line
comma
l_string|&quot;slram=root,0x%x,+0x%x&quot;
comma
(paren
id|u32
)paren
id|addr
comma
(paren
id|u32
)paren
id|len
)paren
suffix:semicolon
id|ROOT_DEV
op_assign
id|MKDEV
(paren
id|MTD_BLOCK_MAJOR
comma
l_int|0
)paren
suffix:semicolon
)brace
macro_line|#endif
"&f;"
DECL|function|irq_nop
r_static
r_void
id|irq_nop
(paren
r_int
id|irq
)paren
(brace
)brace
DECL|function|irq_zero
r_static
r_int
id|irq_zero
(paren
r_int
id|irq
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|nmi_end
r_static
r_void
id|nmi_end
(paren
r_int
id|irq
)paren
(brace
r_if
c_cond
(paren
id|irq
op_ne
id|IRQ_NMI
(paren
l_int|0
)paren
)paren
(brace
id|printk
(paren
id|KERN_CRIT
l_string|&quot;NMI %d is unrecoverable; restarting...&quot;
comma
id|irq
op_minus
id|IRQ_NMI
(paren
l_int|0
)paren
)paren
suffix:semicolon
id|machine_restart
(paren
l_int|0
)paren
suffix:semicolon
)brace
)brace
DECL|variable|nmi_irq_type
r_static
r_struct
id|hw_interrupt_type
id|nmi_irq_type
op_assign
(brace
l_string|&quot;NMI&quot;
comma
id|irq_zero
comma
multiline_comment|/* startup */
id|irq_nop
comma
multiline_comment|/* shutdown */
id|irq_nop
comma
multiline_comment|/* enable */
id|irq_nop
comma
multiline_comment|/* disable */
id|irq_nop
comma
multiline_comment|/* ack */
id|nmi_end
comma
multiline_comment|/* end */
)brace
suffix:semicolon
DECL|function|init_IRQ
r_void
id|__init
id|init_IRQ
(paren
r_void
)paren
(brace
id|init_irq_handlers
(paren
l_int|0
comma
id|NUM_MACH_IRQS
comma
l_int|1
comma
l_int|0
)paren
suffix:semicolon
id|init_irq_handlers
(paren
id|IRQ_NMI
(paren
l_int|0
)paren
comma
id|NUM_NMIS
comma
l_int|1
comma
op_amp
id|nmi_irq_type
)paren
suffix:semicolon
id|mach_init_irqs
(paren
)paren
suffix:semicolon
)brace
"&f;"
DECL|function|mem_init
r_void
id|__init
id|mem_init
(paren
r_void
)paren
(brace
id|max_mapnr
op_assign
id|MAP_NR
(paren
id|ram_start
op_plus
id|ram_len
)paren
suffix:semicolon
id|num_physpages
op_assign
id|ADDR_TO_PAGE
(paren
id|ram_len
)paren
suffix:semicolon
id|total_ram_pages
op_assign
id|free_all_bootmem
(paren
)paren
suffix:semicolon
id|printk
(paren
id|KERN_INFO
l_string|&quot;Memory: %luK/%luK available&quot;
l_string|&quot; (%luK kernel code, %luK data)&bslash;n&quot;
comma
id|PAGE_TO_ADDR
(paren
id|nr_free_pages
c_func
(paren
)paren
)paren
op_div
l_int|1024
comma
id|ram_len
op_div
l_int|1024
comma
(paren
(paren
r_int
r_int
)paren
op_amp
id|_etext
op_minus
(paren
r_int
r_int
)paren
op_amp
id|_stext
)paren
op_div
l_int|1024
comma
(paren
(paren
r_int
r_int
)paren
op_amp
id|_ebss
op_minus
(paren
r_int
r_int
)paren
op_amp
id|_sdata
)paren
op_div
l_int|1024
)paren
suffix:semicolon
)brace
DECL|function|free_initmem
r_void
id|free_initmem
(paren
r_void
)paren
(brace
r_int
r_int
id|ram_end
op_assign
id|ram_start
op_plus
id|ram_len
suffix:semicolon
r_int
r_int
id|start
op_assign
id|PAGE_ALIGN
(paren
(paren
r_int
r_int
)paren
(paren
op_amp
id|_init_start
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|start
op_ge
id|ram_start
op_logical_and
id|start
OL
id|ram_end
)paren
(brace
r_int
r_int
id|addr
suffix:semicolon
r_int
r_int
id|end
op_assign
id|PAGE_ALIGN
(paren
(paren
r_int
r_int
)paren
(paren
op_amp
id|_init_end
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|end
OG
id|ram_end
)paren
id|end
op_assign
id|ram_end
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Freeing unused kernel memory: %ldK freed&bslash;n&quot;
comma
(paren
id|end
op_minus
id|start
)paren
op_div
l_int|1024
)paren
suffix:semicolon
r_for
c_loop
(paren
id|addr
op_assign
id|start
suffix:semicolon
id|addr
OL
id|end
suffix:semicolon
id|addr
op_add_assign
id|PAGE_SIZE
)paren
(brace
r_struct
id|page
op_star
id|page
op_assign
id|virt_to_page
(paren
id|addr
)paren
suffix:semicolon
id|ClearPageReserved
(paren
id|page
)paren
suffix:semicolon
id|set_page_count
(paren
id|page
comma
l_int|1
)paren
suffix:semicolon
id|__free_page
(paren
id|page
)paren
suffix:semicolon
id|total_ram_pages
op_increment
suffix:semicolon
)brace
)brace
)brace
"&f;"
multiline_comment|/* Initialize the `bootmem allocator&squot;.  RAM_START and RAM_LEN identify&n;   what RAM may be used.  */
r_static
r_void
id|__init
DECL|function|init_bootmem_alloc
id|init_bootmem_alloc
(paren
r_int
r_int
id|ram_start
comma
r_int
r_int
id|ram_len
)paren
(brace
multiline_comment|/* The part of the kernel that&squot;s in the same managed RAM space&n;&t;   used for general allocation.  */
r_int
r_int
id|kram_start
op_assign
(paren
r_int
r_int
)paren
op_amp
id|_kram_start
suffix:semicolon
r_int
r_int
id|kram_end
op_assign
(paren
r_int
r_int
)paren
op_amp
id|_kram_end
suffix:semicolon
multiline_comment|/* End of the managed RAM space.  */
r_int
r_int
id|ram_end
op_assign
id|ram_start
op_plus
id|ram_len
suffix:semicolon
multiline_comment|/* Address range of the interrupt vector table.  */
r_int
r_int
id|intv_start
op_assign
(paren
r_int
r_int
)paren
op_amp
id|_intv_start
suffix:semicolon
r_int
r_int
id|intv_end
op_assign
(paren
r_int
r_int
)paren
op_amp
id|_intv_end
suffix:semicolon
multiline_comment|/* True if the interrupt vectors are in the managed RAM area.  */
r_int
id|intv_in_ram
op_assign
(paren
id|intv_end
OG
id|ram_start
op_logical_and
id|intv_start
OL
id|ram_end
)paren
suffix:semicolon
multiline_comment|/* True if the interrupt vectors are inside the kernel&squot;s RAM.  */
r_int
id|intv_in_kram
op_assign
(paren
id|intv_end
OG
id|kram_start
op_logical_and
id|intv_start
OL
id|kram_end
)paren
suffix:semicolon
multiline_comment|/* A pointer to an optional function that reserves platform-specific&n;&t;   memory regions.  We declare the pointer `volatile&squot; to avoid gcc&n;&t;   turning the call into a static call (the problem is that since&n;&t;   it&squot;s a weak symbol, a static call may end up trying to reference&n;&t;   the location 0x0, which is not always reachable).  */
r_void
(paren
op_star
r_volatile
id|mrb
)paren
(paren
r_void
)paren
op_assign
id|mach_reserve_bootmem
suffix:semicolon
multiline_comment|/* The bootmem allocator&squot;s allocation bitmap.  */
r_int
r_int
id|bootmap
op_assign
(paren
r_int
r_int
)paren
op_amp
id|_bootmap
suffix:semicolon
r_int
r_int
id|bootmap_len
suffix:semicolon
multiline_comment|/* Round bootmap location up to next page.  */
id|bootmap
op_assign
id|PAGE_TO_ADDR
(paren
id|ADDR_TO_PAGE_UP
(paren
id|bootmap
)paren
)paren
suffix:semicolon
multiline_comment|/* Initialize bootmem allocator.  */
id|bootmap_len
op_assign
id|init_bootmem_node
(paren
id|NODE_DATA
(paren
l_int|0
)paren
comma
id|ADDR_TO_PAGE
(paren
id|bootmap
)paren
comma
id|ADDR_TO_PAGE
(paren
id|PAGE_OFFSET
)paren
comma
id|ADDR_TO_PAGE
(paren
id|ram_end
)paren
)paren
suffix:semicolon
multiline_comment|/* Now make the RAM actually allocatable (it starts out `reserved&squot;). */
id|free_bootmem
(paren
id|ram_start
comma
id|ram_len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|kram_end
OG
id|kram_start
)paren
multiline_comment|/* Reserve the RAM part of the kernel&squot;s address space, so it&n;&t;&t;   doesn&squot;t get allocated.  */
id|reserve_bootmem
(paren
id|kram_start
comma
id|kram_end
op_minus
id|kram_start
)paren
suffix:semicolon
r_if
c_cond
(paren
id|intv_in_ram
op_logical_and
op_logical_neg
id|intv_in_kram
)paren
multiline_comment|/* Reserve the interrupt vector space.  */
id|reserve_bootmem
(paren
id|intv_start
comma
id|intv_end
op_minus
id|intv_start
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bootmap
op_ge
id|ram_start
op_logical_and
id|bootmap
OL
id|ram_end
)paren
multiline_comment|/* Reserve the bootmap space.  */
id|reserve_bootmem
(paren
id|bootmap
comma
id|bootmap_len
)paren
suffix:semicolon
multiline_comment|/* Reserve the memory used by the root filesystem image if it&squot;s&n;&t;   in RAM.  */
r_if
c_cond
(paren
op_amp
id|_root_fs_image_end
OG
op_amp
id|_root_fs_image_start
op_logical_and
(paren
r_int
r_int
)paren
op_amp
id|_root_fs_image_start
op_ge
id|ram_start
op_logical_and
(paren
r_int
r_int
)paren
op_amp
id|_root_fs_image_start
OL
id|ram_end
)paren
id|reserve_bootmem
(paren
(paren
r_int
r_int
)paren
op_amp
id|_root_fs_image_start
comma
op_amp
id|_root_fs_image_end
op_minus
op_amp
id|_root_fs_image_start
)paren
suffix:semicolon
multiline_comment|/* Let the platform-dependent code reserve some too.  */
r_if
c_cond
(paren
id|mrb
)paren
(paren
op_star
id|mrb
)paren
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Tell the kernel about what RAM it may use for memory allocation.  */
r_static
r_void
id|__init
DECL|function|init_mem_alloc
id|init_mem_alloc
(paren
r_int
r_int
id|ram_start
comma
r_int
r_int
id|ram_len
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
r_int
id|zones_size
(braket
id|MAX_NR_ZONES
)braket
suffix:semicolon
id|init_bootmem_alloc
(paren
id|ram_start
comma
id|ram_len
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
id|MAX_NR_ZONES
suffix:semicolon
id|i
op_increment
)paren
id|zones_size
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* We stuff all the memory into one area, which includes the&n;&t;   initial gap from PAGE_OFFSET to ram_start.  */
id|zones_size
(braket
id|ZONE_DMA
)braket
op_assign
id|ADDR_TO_PAGE
(paren
id|ram_len
op_plus
(paren
id|ram_start
op_minus
id|PAGE_OFFSET
)paren
)paren
suffix:semicolon
id|free_area_init_node
(paren
l_int|0
comma
id|NODE_DATA
c_func
(paren
l_int|0
)paren
comma
l_int|0
comma
id|zones_size
comma
id|ADDR_TO_PAGE
(paren
id|PAGE_OFFSET
)paren
comma
l_int|0
)paren
suffix:semicolon
id|mem_map
op_assign
id|NODE_DATA
c_func
(paren
l_int|0
)paren
op_member_access_from_pointer
id|node_mem_map
suffix:semicolon
)brace
eof
