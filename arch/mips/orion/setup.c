multiline_comment|/*&n; * Catch-all for Orion-specific code that doesn&squot;t fit easily elsewhere.&n; *   -- Cort&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/hdreg.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/user.h&gt;
macro_line|#include &lt;linux/utsname.h&gt;
macro_line|#include &lt;linux/a.out.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#ifdef CONFIG_BLK_DEV_RAM
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#endif
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#ifdef CONFIG_RTC
macro_line|#include &lt;linux/timex.h&gt;
macro_line|#endif
macro_line|#include &lt;asm/asm.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/cachectl.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/stackframe.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/cpu.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;asm/addrspace.h&gt;
macro_line|#include &lt;asm/mc146818rtc.h&gt;
macro_line|#include &lt;asm/orion.h&gt;
DECL|variable|arcs_cmdline
r_char
id|arcs_cmdline
(braket
id|CL_SIZE
)braket
op_assign
(brace
l_string|&quot;console=ttyS0,19200&quot;
)brace
suffix:semicolon
r_extern
r_int
id|_end
suffix:semicolon
DECL|function|orion_rtc_read_data
r_static
r_int
r_char
id|orion_rtc_read_data
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|orion_rtc_write_data
r_static
r_void
id|orion_rtc_write_data
c_func
(paren
r_int
r_char
id|data
comma
r_int
r_int
id|addr
)paren
(brace
)brace
DECL|function|orion_rtc_bcd_mode
r_static
r_int
id|orion_rtc_bcd_mode
c_func
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|orion_rtc_ops
r_struct
id|rtc_ops
id|orion_rtc_ops
op_assign
(brace
op_amp
id|orion_rtc_read_data
comma
op_amp
id|orion_rtc_write_data
comma
op_amp
id|orion_rtc_bcd_mode
)brace
suffix:semicolon
r_extern
r_void
id|InitCIB
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|InitQpic
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|InitCupid
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|orion_setup
r_void
id|__init
id|orion_setup
c_func
(paren
r_void
)paren
(brace
r_extern
r_void
(paren
op_star
id|board_time_init
)paren
(paren
r_struct
id|irqaction
op_star
id|irq
)paren
suffix:semicolon
r_void
id|orion_time_init
c_func
(paren
r_struct
id|irqaction
op_star
)paren
suffix:semicolon
id|rtc_ops
op_assign
op_amp
id|orion_rtc_ops
suffix:semicolon
id|board_time_init
op_assign
id|orion_time_init
suffix:semicolon
id|mips_io_port_base
op_assign
id|GT64120_BASE
suffix:semicolon
id|InitCIB
c_func
(paren
)paren
suffix:semicolon
id|InitQpic
c_func
(paren
)paren
suffix:semicolon
id|InitCupid
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|macro|PFN_UP
mdefine_line|#define PFN_UP(x)&t;(((x) + PAGE_SIZE-1) &gt;&gt; PAGE_SHIFT)
DECL|macro|PFN_ALIGN
mdefine_line|#define PFN_ALIGN(x)&t;(((unsigned long)(x) + (PAGE_SIZE - 1)) &amp; PAGE_MASK)
DECL|variable|mem_size
r_int
r_int
id|mem_size
suffix:semicolon
DECL|function|prom_init
r_int
id|__init
id|prom_init
c_func
(paren
r_int
id|a
comma
r_char
op_star
op_star
id|b
comma
r_char
op_star
op_star
id|c
comma
r_int
op_star
id|d
)paren
(brace
r_int
r_int
id|free_start
comma
id|free_end
comma
id|start_pfn
comma
id|bootmap_size
suffix:semicolon
r_extern
r_int
r_int
id|orion_initrd_start
(braket
)braket
comma
id|orion_initrd_size
suffix:semicolon
id|mips_machgroup
op_assign
id|MACH_GROUP_ORION
suffix:semicolon
multiline_comment|/* 64 MB non-upgradable */
id|mem_size
op_assign
l_int|64
op_lshift
l_int|20
suffix:semicolon
id|free_start
op_assign
id|PHYSADDR
c_func
(paren
id|PFN_ALIGN
c_func
(paren
op_amp
id|_end
)paren
)paren
suffix:semicolon
id|free_end
op_assign
id|mem_size
suffix:semicolon
id|start_pfn
op_assign
id|PFN_UP
c_func
(paren
(paren
r_int
r_int
)paren
op_amp
id|_end
)paren
suffix:semicolon
multiline_comment|/* Register all the contiguous memory with the bootmem allocator&n;&t;   and free it.  Be careful about the bootmem freemap.  */
id|bootmap_size
op_assign
id|init_bootmem
c_func
(paren
id|start_pfn
comma
id|mem_size
op_rshift
id|PAGE_SHIFT
)paren
suffix:semicolon
multiline_comment|/* Free the entire available memory after the _end symbol.  */
id|free_start
op_add_assign
id|bootmap_size
suffix:semicolon
id|free_bootmem
c_func
(paren
id|free_start
comma
id|free_end
op_minus
id|free_start
)paren
suffix:semicolon
id|initrd_start
op_assign
(paren
id|ulong
)paren
id|orion_initrd_start
suffix:semicolon
id|initrd_end
op_assign
(paren
id|ulong
)paren
id|orion_initrd_start
op_plus
(paren
id|ulong
)paren
id|orion_initrd_size
suffix:semicolon
id|initrd_below_start_ok
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|prom_free_prom_memory
r_void
id|prom_free_prom_memory
(paren
r_void
)paren
(brace
)brace
DECL|function|page_is_ram
r_int
id|page_is_ram
c_func
(paren
r_int
r_int
id|pagenr
)paren
(brace
r_if
c_cond
(paren
id|pagenr
OL
(paren
id|mem_size
op_rshift
id|PAGE_SHIFT
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
