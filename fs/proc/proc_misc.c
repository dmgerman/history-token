multiline_comment|/*&n; *  linux/fs/proc/proc_misc.c&n; *&n; *  linux/fs/proc/array.c&n; *  Copyright (C) 1992  by Linus Torvalds&n; *  based on ideas by Darren Senn&n; *&n; *  This used to be the part of array.c. See the rest of history and credits&n; *  there. I took this into a separate file and switched the thing to generic&n; *  proc_file_inode_operations, leaving in array.c only per-process stuff.&n; *  Inumbers allocation made dynamic (via create_proc_entry()).  AV, May 1999.&n; *&n; * Changes:&n; * Fulton Green      :  Encapsulated position metric calculations.&n; *&t;&t;&t;&lt;kernel@FultonGreen.com&gt;&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mman.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/swap.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/io.h&gt;
DECL|macro|LOAD_INT
mdefine_line|#define LOAD_INT(x) ((x) &gt;&gt; FSHIFT)
DECL|macro|LOAD_FRAC
mdefine_line|#define LOAD_FRAC(x) LOAD_INT(((x) &amp; (FIXED_1-1)) * 100)
multiline_comment|/*&n; * Warning: stuff below (imported functions) assumes that its output will fit&n; * into one page. For some of those functions it may be wrong. Moreover, we&n; * have a way to deal with that gracefully. Right now I used straightforward&n; * wrappers, but this needs further analysis wrt potential overflows.&n; */
r_extern
r_int
id|get_cpuinfo
c_func
(paren
r_char
op_star
)paren
suffix:semicolon
r_extern
r_int
id|get_hardware_list
c_func
(paren
r_char
op_star
)paren
suffix:semicolon
r_extern
r_int
id|get_stram_list
c_func
(paren
r_char
op_star
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_DEBUG_MALLOC
r_extern
r_int
id|get_malloc
c_func
(paren
r_char
op_star
id|buffer
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_MODULES
r_extern
r_int
id|get_module_list
c_func
(paren
r_char
op_star
)paren
suffix:semicolon
r_extern
r_int
id|get_ksyms_list
c_func
(paren
r_char
op_star
comma
r_char
op_star
op_star
comma
id|off_t
comma
r_int
)paren
suffix:semicolon
macro_line|#endif
r_extern
r_int
id|get_device_list
c_func
(paren
r_char
op_star
)paren
suffix:semicolon
r_extern
r_int
id|get_partition_list
c_func
(paren
r_char
op_star
comma
r_char
op_star
op_star
comma
id|off_t
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|get_filesystem_list
c_func
(paren
r_char
op_star
)paren
suffix:semicolon
r_extern
r_int
id|get_filesystem_info
c_func
(paren
r_char
op_star
)paren
suffix:semicolon
r_extern
r_int
id|get_exec_domain_list
c_func
(paren
r_char
op_star
)paren
suffix:semicolon
r_extern
r_int
id|get_irq_list
c_func
(paren
r_char
op_star
)paren
suffix:semicolon
r_extern
r_int
id|get_dma_list
c_func
(paren
r_char
op_star
)paren
suffix:semicolon
r_extern
r_int
id|get_locks_status
(paren
r_char
op_star
comma
r_char
op_star
op_star
comma
id|off_t
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|get_swaparea_info
(paren
r_char
op_star
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SGI_DS1286
r_extern
r_int
id|get_ds1286_status
c_func
(paren
r_char
op_star
)paren
suffix:semicolon
macro_line|#endif
DECL|function|proc_calc_metrics
r_static
r_int
id|proc_calc_metrics
c_func
(paren
r_char
op_star
id|page
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|off
comma
r_int
id|count
comma
r_int
op_star
id|eof
comma
r_int
id|len
)paren
(brace
r_if
c_cond
(paren
id|len
op_le
id|off
op_plus
id|count
)paren
op_star
id|eof
op_assign
l_int|1
suffix:semicolon
op_star
id|start
op_assign
id|page
op_plus
id|off
suffix:semicolon
id|len
op_sub_assign
id|off
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
id|count
)paren
id|len
op_assign
id|count
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
l_int|0
)paren
id|len
op_assign
l_int|0
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
DECL|function|loadavg_read_proc
r_static
r_int
id|loadavg_read_proc
c_func
(paren
r_char
op_star
id|page
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|off
comma
r_int
id|count
comma
r_int
op_star
id|eof
comma
r_void
op_star
id|data
)paren
(brace
r_int
id|a
comma
id|b
comma
id|c
suffix:semicolon
r_int
id|len
suffix:semicolon
id|a
op_assign
id|avenrun
(braket
l_int|0
)braket
op_plus
(paren
id|FIXED_1
op_div
l_int|200
)paren
suffix:semicolon
id|b
op_assign
id|avenrun
(braket
l_int|1
)braket
op_plus
(paren
id|FIXED_1
op_div
l_int|200
)paren
suffix:semicolon
id|c
op_assign
id|avenrun
(braket
l_int|2
)braket
op_plus
(paren
id|FIXED_1
op_div
l_int|200
)paren
suffix:semicolon
id|len
op_assign
id|sprintf
c_func
(paren
id|page
comma
l_string|&quot;%d.%02d %d.%02d %d.%02d %d/%d %d&bslash;n&quot;
comma
id|LOAD_INT
c_func
(paren
id|a
)paren
comma
id|LOAD_FRAC
c_func
(paren
id|a
)paren
comma
id|LOAD_INT
c_func
(paren
id|b
)paren
comma
id|LOAD_FRAC
c_func
(paren
id|b
)paren
comma
id|LOAD_INT
c_func
(paren
id|c
)paren
comma
id|LOAD_FRAC
c_func
(paren
id|c
)paren
comma
id|nr_running
comma
id|nr_threads
comma
id|last_pid
)paren
suffix:semicolon
r_return
id|proc_calc_metrics
c_func
(paren
id|page
comma
id|start
comma
id|off
comma
id|count
comma
id|eof
comma
id|len
)paren
suffix:semicolon
)brace
DECL|function|uptime_read_proc
r_static
r_int
id|uptime_read_proc
c_func
(paren
r_char
op_star
id|page
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|off
comma
r_int
id|count
comma
r_int
op_star
id|eof
comma
r_void
op_star
id|data
)paren
(brace
r_int
r_int
id|uptime
suffix:semicolon
r_int
r_int
id|idle
suffix:semicolon
r_int
id|len
suffix:semicolon
id|uptime
op_assign
id|jiffies
suffix:semicolon
id|idle
op_assign
id|init_tasks
(braket
l_int|0
)braket
op_member_access_from_pointer
id|times.tms_utime
op_plus
id|init_tasks
(braket
l_int|0
)braket
op_member_access_from_pointer
id|times.tms_stime
suffix:semicolon
multiline_comment|/* The formula for the fraction parts really is ((t * 100) / HZ) % 100, but&n;&t;   that would overflow about every five days at HZ == 100.&n;&t;   Therefore the identity a = (a / b) * b + a % b is used so that it is&n;&t;   calculated as (((t / HZ) * 100) + ((t % HZ) * 100) / HZ) % 100.&n;&t;   The part in front of the &squot;+&squot; always evaluates as 0 (mod 100). All divisions&n;&t;   in the above formulas are truncating. For HZ being a power of 10, the&n;&t;   calculations simplify to the version in the #else part (if the printf&n;&t;   format is adapted to the same number of digits as zeroes in HZ.&n;&t; */
macro_line|#if HZ!=100
id|len
op_assign
id|sprintf
c_func
(paren
id|page
comma
l_string|&quot;%lu.%02lu %lu.%02lu&bslash;n&quot;
comma
id|uptime
op_div
id|HZ
comma
(paren
(paren
(paren
id|uptime
op_mod
id|HZ
)paren
op_star
l_int|100
)paren
op_div
id|HZ
)paren
op_mod
l_int|100
comma
id|idle
op_div
id|HZ
comma
(paren
(paren
(paren
id|idle
op_mod
id|HZ
)paren
op_star
l_int|100
)paren
op_div
id|HZ
)paren
op_mod
l_int|100
)paren
suffix:semicolon
macro_line|#else
id|len
op_assign
id|sprintf
c_func
(paren
id|page
comma
l_string|&quot;%lu.%02lu %lu.%02lu&bslash;n&quot;
comma
id|uptime
op_div
id|HZ
comma
id|uptime
op_mod
id|HZ
comma
id|idle
op_div
id|HZ
comma
id|idle
op_mod
id|HZ
)paren
suffix:semicolon
macro_line|#endif
r_return
id|proc_calc_metrics
c_func
(paren
id|page
comma
id|start
comma
id|off
comma
id|count
comma
id|eof
comma
id|len
)paren
suffix:semicolon
)brace
DECL|function|meminfo_read_proc
r_static
r_int
id|meminfo_read_proc
c_func
(paren
r_char
op_star
id|page
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|off
comma
r_int
id|count
comma
r_int
op_star
id|eof
comma
r_void
op_star
id|data
)paren
(brace
r_struct
id|sysinfo
id|i
suffix:semicolon
r_int
id|len
suffix:semicolon
multiline_comment|/*&n; * display in kilobytes.&n; */
DECL|macro|K
mdefine_line|#define K(x) ((x) &lt;&lt; (PAGE_SHIFT - 10))
DECL|macro|B
mdefine_line|#define B(x) ((x) &lt;&lt; PAGE_SHIFT)
id|si_meminfo
c_func
(paren
op_amp
id|i
)paren
suffix:semicolon
id|si_swapinfo
c_func
(paren
op_amp
id|i
)paren
suffix:semicolon
id|len
op_assign
id|sprintf
c_func
(paren
id|page
comma
l_string|&quot;        total:    used:    free:  shared: buffers:  cached:&bslash;n&quot;
l_string|&quot;Mem:  %8lu %8lu %8lu %8lu %8lu %8u&bslash;n&quot;
l_string|&quot;Swap: %8lu %8lu %8lu&bslash;n&quot;
comma
id|B
c_func
(paren
id|i.totalram
)paren
comma
id|B
c_func
(paren
id|i.totalram
op_minus
id|i.freeram
)paren
comma
id|B
c_func
(paren
id|i.freeram
)paren
comma
id|B
c_func
(paren
id|i.sharedram
)paren
comma
id|B
c_func
(paren
id|i.bufferram
)paren
comma
id|B
c_func
(paren
id|atomic_read
c_func
(paren
op_amp
id|page_cache_size
)paren
)paren
comma
id|B
c_func
(paren
id|i.totalswap
)paren
comma
id|B
c_func
(paren
id|i.totalswap
op_minus
id|i.freeswap
)paren
comma
id|B
c_func
(paren
id|i.freeswap
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Tagged format, for easy grepping and expansion.&n;&t; * The above will go away eventually, once the tools&n;&t; * have been updated.&n;&t; */
id|len
op_add_assign
id|sprintf
c_func
(paren
id|page
op_plus
id|len
comma
l_string|&quot;MemTotal:     %8lu kB&bslash;n&quot;
l_string|&quot;MemFree:      %8lu kB&bslash;n&quot;
l_string|&quot;MemShared:    %8lu kB&bslash;n&quot;
l_string|&quot;Buffers:      %8lu kB&bslash;n&quot;
l_string|&quot;Cached:       %8lu kB&bslash;n&quot;
l_string|&quot;SwapCached:   %8lu kB&bslash;n&quot;
l_string|&quot;Active:       %8u kB&bslash;n&quot;
l_string|&quot;Inact_dirty:  %8u kB&bslash;n&quot;
l_string|&quot;Inact_clean:  %8u kB&bslash;n&quot;
l_string|&quot;Inact_target: %8lu kB&bslash;n&quot;
l_string|&quot;HighTotal:    %8lu kB&bslash;n&quot;
l_string|&quot;HighFree:     %8lu kB&bslash;n&quot;
l_string|&quot;LowTotal:     %8lu kB&bslash;n&quot;
l_string|&quot;LowFree:      %8lu kB&bslash;n&quot;
l_string|&quot;SwapTotal:    %8lu kB&bslash;n&quot;
l_string|&quot;SwapFree:     %8lu kB&bslash;n&quot;
comma
id|K
c_func
(paren
id|i.totalram
)paren
comma
id|K
c_func
(paren
id|i.freeram
)paren
comma
id|K
c_func
(paren
id|i.sharedram
)paren
comma
id|K
c_func
(paren
id|i.bufferram
)paren
comma
id|K
c_func
(paren
id|atomic_read
c_func
(paren
op_amp
id|page_cache_size
)paren
op_minus
id|swapper_space.nrpages
)paren
comma
id|K
c_func
(paren
id|swapper_space.nrpages
)paren
comma
id|K
c_func
(paren
id|nr_active_pages
)paren
comma
id|K
c_func
(paren
id|nr_inactive_dirty_pages
)paren
comma
id|K
c_func
(paren
id|nr_inactive_clean_pages
c_func
(paren
)paren
)paren
comma
id|K
c_func
(paren
id|inactive_target
)paren
comma
id|K
c_func
(paren
id|i.totalhigh
)paren
comma
id|K
c_func
(paren
id|i.freehigh
)paren
comma
id|K
c_func
(paren
id|i.totalram
op_minus
id|i.totalhigh
)paren
comma
id|K
c_func
(paren
id|i.freeram
op_minus
id|i.freehigh
)paren
comma
id|K
c_func
(paren
id|i.totalswap
)paren
comma
id|K
c_func
(paren
id|i.freeswap
)paren
)paren
suffix:semicolon
r_return
id|proc_calc_metrics
c_func
(paren
id|page
comma
id|start
comma
id|off
comma
id|count
comma
id|eof
comma
id|len
)paren
suffix:semicolon
DECL|macro|B
macro_line|#undef B
DECL|macro|K
macro_line|#undef K
)brace
DECL|function|version_read_proc
r_static
r_int
id|version_read_proc
c_func
(paren
r_char
op_star
id|page
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|off
comma
r_int
id|count
comma
r_int
op_star
id|eof
comma
r_void
op_star
id|data
)paren
(brace
r_extern
r_char
op_star
id|linux_banner
suffix:semicolon
r_int
id|len
suffix:semicolon
id|strcpy
c_func
(paren
id|page
comma
id|linux_banner
)paren
suffix:semicolon
id|len
op_assign
id|strlen
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
id|proc_calc_metrics
c_func
(paren
id|page
comma
id|start
comma
id|off
comma
id|count
comma
id|eof
comma
id|len
)paren
suffix:semicolon
)brace
DECL|function|cpuinfo_read_proc
r_static
r_int
id|cpuinfo_read_proc
c_func
(paren
r_char
op_star
id|page
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|off
comma
r_int
id|count
comma
r_int
op_star
id|eof
comma
r_void
op_star
id|data
)paren
(brace
r_int
id|len
op_assign
id|get_cpuinfo
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
id|proc_calc_metrics
c_func
(paren
id|page
comma
id|start
comma
id|off
comma
id|count
comma
id|eof
comma
id|len
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_PROC_HARDWARE
DECL|function|hardware_read_proc
r_static
r_int
id|hardware_read_proc
c_func
(paren
r_char
op_star
id|page
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|off
comma
r_int
id|count
comma
r_int
op_star
id|eof
comma
r_void
op_star
id|data
)paren
(brace
r_int
id|len
op_assign
id|get_hardware_list
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
id|proc_calc_metrics
c_func
(paren
id|page
comma
id|start
comma
id|off
comma
id|count
comma
id|eof
comma
id|len
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef CONFIG_STRAM_PROC
DECL|function|stram_read_proc
r_static
r_int
id|stram_read_proc
c_func
(paren
r_char
op_star
id|page
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|off
comma
r_int
id|count
comma
r_int
op_star
id|eof
comma
r_void
op_star
id|data
)paren
(brace
r_int
id|len
op_assign
id|get_stram_list
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
id|proc_calc_metrics
c_func
(paren
id|page
comma
id|start
comma
id|off
comma
id|count
comma
id|eof
comma
id|len
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef CONFIG_DEBUG_MALLOC
DECL|function|malloc_read_proc
r_static
r_int
id|malloc_read_proc
c_func
(paren
r_char
op_star
id|page
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|off
comma
r_int
id|count
comma
r_int
op_star
id|eof
comma
r_void
op_star
id|data
)paren
(brace
r_int
id|len
op_assign
id|get_malloc
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
id|proc_calc_metrics
c_func
(paren
id|page
comma
id|start
comma
id|off
comma
id|count
comma
id|eof
comma
id|len
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef CONFIG_MODULES
DECL|function|modules_read_proc
r_static
r_int
id|modules_read_proc
c_func
(paren
r_char
op_star
id|page
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|off
comma
r_int
id|count
comma
r_int
op_star
id|eof
comma
r_void
op_star
id|data
)paren
(brace
r_int
id|len
op_assign
id|get_module_list
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
id|proc_calc_metrics
c_func
(paren
id|page
comma
id|start
comma
id|off
comma
id|count
comma
id|eof
comma
id|len
)paren
suffix:semicolon
)brace
DECL|function|ksyms_read_proc
r_static
r_int
id|ksyms_read_proc
c_func
(paren
r_char
op_star
id|page
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|off
comma
r_int
id|count
comma
r_int
op_star
id|eof
comma
r_void
op_star
id|data
)paren
(brace
r_int
id|len
op_assign
id|get_ksyms_list
c_func
(paren
id|page
comma
id|start
comma
id|off
comma
id|count
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
id|count
)paren
op_star
id|eof
op_assign
l_int|1
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
macro_line|#endif
DECL|function|kstat_read_proc
r_static
r_int
id|kstat_read_proc
c_func
(paren
r_char
op_star
id|page
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|off
comma
r_int
id|count
comma
r_int
op_star
id|eof
comma
r_void
op_star
id|data
)paren
(brace
r_int
id|i
comma
id|len
suffix:semicolon
r_extern
r_int
r_int
id|total_forks
suffix:semicolon
r_int
r_int
id|jif
op_assign
id|jiffies
suffix:semicolon
r_int
r_int
id|sum
op_assign
l_int|0
comma
id|user
op_assign
l_int|0
comma
id|nice
op_assign
l_int|0
comma
id|system
op_assign
l_int|0
suffix:semicolon
r_int
id|major
comma
id|disk
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
id|smp_num_cpus
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
id|cpu
op_assign
id|cpu_logical_map
c_func
(paren
id|i
)paren
comma
id|j
suffix:semicolon
id|user
op_add_assign
id|kstat.per_cpu_user
(braket
id|cpu
)braket
suffix:semicolon
id|nice
op_add_assign
id|kstat.per_cpu_nice
(braket
id|cpu
)braket
suffix:semicolon
id|system
op_add_assign
id|kstat.per_cpu_system
(braket
id|cpu
)braket
suffix:semicolon
macro_line|#if !defined(CONFIG_ARCH_S390)
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|NR_IRQS
suffix:semicolon
id|j
op_increment
)paren
id|sum
op_add_assign
id|kstat.irqs
(braket
id|cpu
)braket
(braket
id|j
)braket
suffix:semicolon
macro_line|#endif
)brace
id|len
op_assign
id|sprintf
c_func
(paren
id|page
comma
l_string|&quot;cpu  %u %u %u %lu&bslash;n&quot;
comma
id|user
comma
id|nice
comma
id|system
comma
id|jif
op_star
id|smp_num_cpus
op_minus
(paren
id|user
op_plus
id|nice
op_plus
id|system
)paren
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
id|smp_num_cpus
suffix:semicolon
id|i
op_increment
)paren
id|len
op_add_assign
id|sprintf
c_func
(paren
id|page
op_plus
id|len
comma
l_string|&quot;cpu%d %u %u %u %lu&bslash;n&quot;
comma
id|i
comma
id|kstat.per_cpu_user
(braket
id|cpu_logical_map
c_func
(paren
id|i
)paren
)braket
comma
id|kstat.per_cpu_nice
(braket
id|cpu_logical_map
c_func
(paren
id|i
)paren
)braket
comma
id|kstat.per_cpu_system
(braket
id|cpu_logical_map
c_func
(paren
id|i
)paren
)braket
comma
id|jif
op_minus
(paren
id|kstat.per_cpu_user
(braket
id|cpu_logical_map
c_func
(paren
id|i
)paren
)braket
"&bslash;"
op_plus
id|kstat.per_cpu_nice
(braket
id|cpu_logical_map
c_func
(paren
id|i
)paren
)braket
"&bslash;"
op_plus
id|kstat.per_cpu_system
(braket
id|cpu_logical_map
c_func
(paren
id|i
)paren
)braket
)paren
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|page
op_plus
id|len
comma
l_string|&quot;page %u %u&bslash;n&quot;
l_string|&quot;swap %u %u&bslash;n&quot;
l_string|&quot;intr %u&quot;
comma
id|kstat.pgpgin
op_rshift
l_int|1
comma
id|kstat.pgpgout
op_rshift
l_int|1
comma
id|kstat.pswpin
comma
id|kstat.pswpout
comma
id|sum
)paren
suffix:semicolon
macro_line|#if !defined(CONFIG_ARCH_S390)
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NR_IRQS
suffix:semicolon
id|i
op_increment
)paren
id|len
op_add_assign
id|sprintf
c_func
(paren
id|page
op_plus
id|len
comma
l_string|&quot; %u&quot;
comma
id|kstat_irqs
c_func
(paren
id|i
)paren
)paren
suffix:semicolon
macro_line|#endif
id|len
op_add_assign
id|sprintf
c_func
(paren
id|page
op_plus
id|len
comma
l_string|&quot;&bslash;ndisk_io: &quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|major
op_assign
l_int|0
suffix:semicolon
id|major
OL
id|DK_MAX_MAJOR
suffix:semicolon
id|major
op_increment
)paren
(brace
r_for
c_loop
(paren
id|disk
op_assign
l_int|0
suffix:semicolon
id|disk
OL
id|DK_MAX_DISK
suffix:semicolon
id|disk
op_increment
)paren
(brace
r_int
id|active
op_assign
id|kstat.dk_drive
(braket
id|major
)braket
(braket
id|disk
)braket
op_plus
id|kstat.dk_drive_rblk
(braket
id|major
)braket
(braket
id|disk
)braket
op_plus
id|kstat.dk_drive_wblk
(braket
id|major
)braket
(braket
id|disk
)braket
suffix:semicolon
r_if
c_cond
(paren
id|active
)paren
id|len
op_add_assign
id|sprintf
c_func
(paren
id|page
op_plus
id|len
comma
l_string|&quot;(%u,%u):(%u,%u,%u,%u,%u) &quot;
comma
id|major
comma
id|disk
comma
id|kstat.dk_drive
(braket
id|major
)braket
(braket
id|disk
)braket
comma
id|kstat.dk_drive_rio
(braket
id|major
)braket
(braket
id|disk
)braket
comma
id|kstat.dk_drive_rblk
(braket
id|major
)braket
(braket
id|disk
)braket
comma
id|kstat.dk_drive_wio
(braket
id|major
)braket
(braket
id|disk
)braket
comma
id|kstat.dk_drive_wblk
(braket
id|major
)braket
(braket
id|disk
)braket
)paren
suffix:semicolon
)brace
)brace
id|len
op_add_assign
id|sprintf
c_func
(paren
id|page
op_plus
id|len
comma
l_string|&quot;&bslash;nctxt %u&bslash;n&quot;
l_string|&quot;btime %lu&bslash;n&quot;
l_string|&quot;processes %lu&bslash;n&quot;
comma
id|kstat.context_swtch
comma
id|xtime.tv_sec
op_minus
id|jif
op_div
id|HZ
comma
id|total_forks
)paren
suffix:semicolon
r_return
id|proc_calc_metrics
c_func
(paren
id|page
comma
id|start
comma
id|off
comma
id|count
comma
id|eof
comma
id|len
)paren
suffix:semicolon
)brace
DECL|function|devices_read_proc
r_static
r_int
id|devices_read_proc
c_func
(paren
r_char
op_star
id|page
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|off
comma
r_int
id|count
comma
r_int
op_star
id|eof
comma
r_void
op_star
id|data
)paren
(brace
r_int
id|len
op_assign
id|get_device_list
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
id|proc_calc_metrics
c_func
(paren
id|page
comma
id|start
comma
id|off
comma
id|count
comma
id|eof
comma
id|len
)paren
suffix:semicolon
)brace
DECL|function|partitions_read_proc
r_static
r_int
id|partitions_read_proc
c_func
(paren
r_char
op_star
id|page
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|off
comma
r_int
id|count
comma
r_int
op_star
id|eof
comma
r_void
op_star
id|data
)paren
(brace
r_int
id|len
op_assign
id|get_partition_list
c_func
(paren
id|page
comma
id|start
comma
id|off
comma
id|count
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
id|count
)paren
op_star
id|eof
op_assign
l_int|1
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
macro_line|#if !defined(CONFIG_ARCH_S390)
DECL|function|interrupts_read_proc
r_static
r_int
id|interrupts_read_proc
c_func
(paren
r_char
op_star
id|page
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|off
comma
r_int
id|count
comma
r_int
op_star
id|eof
comma
r_void
op_star
id|data
)paren
(brace
r_int
id|len
op_assign
id|get_irq_list
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
id|proc_calc_metrics
c_func
(paren
id|page
comma
id|start
comma
id|off
comma
id|count
comma
id|eof
comma
id|len
)paren
suffix:semicolon
)brace
macro_line|#endif
DECL|function|filesystems_read_proc
r_static
r_int
id|filesystems_read_proc
c_func
(paren
r_char
op_star
id|page
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|off
comma
r_int
id|count
comma
r_int
op_star
id|eof
comma
r_void
op_star
id|data
)paren
(brace
r_int
id|len
op_assign
id|get_filesystem_list
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
id|proc_calc_metrics
c_func
(paren
id|page
comma
id|start
comma
id|off
comma
id|count
comma
id|eof
comma
id|len
)paren
suffix:semicolon
)brace
DECL|function|dma_read_proc
r_static
r_int
id|dma_read_proc
c_func
(paren
r_char
op_star
id|page
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|off
comma
r_int
id|count
comma
r_int
op_star
id|eof
comma
r_void
op_star
id|data
)paren
(brace
r_int
id|len
op_assign
id|get_dma_list
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
id|proc_calc_metrics
c_func
(paren
id|page
comma
id|start
comma
id|off
comma
id|count
comma
id|eof
comma
id|len
)paren
suffix:semicolon
)brace
DECL|function|ioports_read_proc
r_static
r_int
id|ioports_read_proc
c_func
(paren
r_char
op_star
id|page
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|off
comma
r_int
id|count
comma
r_int
op_star
id|eof
comma
r_void
op_star
id|data
)paren
(brace
r_int
id|len
op_assign
id|get_ioport_list
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
id|proc_calc_metrics
c_func
(paren
id|page
comma
id|start
comma
id|off
comma
id|count
comma
id|eof
comma
id|len
)paren
suffix:semicolon
)brace
DECL|function|cmdline_read_proc
r_static
r_int
id|cmdline_read_proc
c_func
(paren
r_char
op_star
id|page
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|off
comma
r_int
id|count
comma
r_int
op_star
id|eof
comma
r_void
op_star
id|data
)paren
(brace
r_extern
r_char
id|saved_command_line
(braket
)braket
suffix:semicolon
r_int
id|len
suffix:semicolon
id|len
op_assign
id|sprintf
c_func
(paren
id|page
comma
l_string|&quot;%s&bslash;n&quot;
comma
id|saved_command_line
)paren
suffix:semicolon
id|len
op_assign
id|strlen
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
id|proc_calc_metrics
c_func
(paren
id|page
comma
id|start
comma
id|off
comma
id|count
comma
id|eof
comma
id|len
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_SGI_DS1286
DECL|function|ds1286_read_proc
r_static
r_int
id|ds1286_read_proc
c_func
(paren
r_char
op_star
id|page
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|off
comma
r_int
id|count
comma
r_int
op_star
id|eof
comma
r_void
op_star
id|data
)paren
(brace
r_int
id|len
op_assign
id|get_ds1286_status
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
id|proc_calc_metrics
c_func
(paren
id|page
comma
id|start
comma
id|off
comma
id|count
comma
id|eof
comma
id|len
)paren
suffix:semicolon
)brace
macro_line|#endif
DECL|function|locks_read_proc
r_static
r_int
id|locks_read_proc
c_func
(paren
r_char
op_star
id|page
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|off
comma
r_int
id|count
comma
r_int
op_star
id|eof
comma
r_void
op_star
id|data
)paren
(brace
r_int
id|len
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|len
op_assign
id|get_locks_status
c_func
(paren
id|page
comma
id|start
comma
id|off
comma
id|count
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
id|count
)paren
op_star
id|eof
op_assign
l_int|1
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
DECL|function|mounts_read_proc
r_static
r_int
id|mounts_read_proc
c_func
(paren
r_char
op_star
id|page
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|off
comma
r_int
id|count
comma
r_int
op_star
id|eof
comma
r_void
op_star
id|data
)paren
(brace
r_int
id|len
op_assign
id|get_filesystem_info
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
id|proc_calc_metrics
c_func
(paren
id|page
comma
id|start
comma
id|off
comma
id|count
comma
id|eof
comma
id|len
)paren
suffix:semicolon
)brace
DECL|function|execdomains_read_proc
r_static
r_int
id|execdomains_read_proc
c_func
(paren
r_char
op_star
id|page
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|off
comma
r_int
id|count
comma
r_int
op_star
id|eof
comma
r_void
op_star
id|data
)paren
(brace
r_int
id|len
op_assign
id|get_exec_domain_list
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
id|proc_calc_metrics
c_func
(paren
id|page
comma
id|start
comma
id|off
comma
id|count
comma
id|eof
comma
id|len
)paren
suffix:semicolon
)brace
DECL|function|swaps_read_proc
r_static
r_int
id|swaps_read_proc
c_func
(paren
r_char
op_star
id|page
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|off
comma
r_int
id|count
comma
r_int
op_star
id|eof
comma
r_void
op_star
id|data
)paren
(brace
r_int
id|len
op_assign
id|get_swaparea_info
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
id|proc_calc_metrics
c_func
(paren
id|page
comma
id|start
comma
id|off
comma
id|count
comma
id|eof
comma
id|len
)paren
suffix:semicolon
)brace
DECL|function|memory_read_proc
r_static
r_int
id|memory_read_proc
c_func
(paren
r_char
op_star
id|page
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|off
comma
r_int
id|count
comma
r_int
op_star
id|eof
comma
r_void
op_star
id|data
)paren
(brace
r_int
id|len
op_assign
id|get_mem_list
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
id|proc_calc_metrics
c_func
(paren
id|page
comma
id|start
comma
id|off
comma
id|count
comma
id|eof
comma
id|len
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This function accesses profiling information. The returned data is&n; * binary: the sampling step and the actual contents of the profile&n; * buffer. Use of the program readprofile is recommended in order to&n; * get meaningful info out of these data.&n; */
DECL|function|read_profile
r_static
id|ssize_t
id|read_profile
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_char
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_int
r_int
id|p
op_assign
op_star
id|ppos
suffix:semicolon
id|ssize_t
id|read
suffix:semicolon
r_char
op_star
id|pnt
suffix:semicolon
r_int
r_int
id|sample_step
op_assign
l_int|1
op_lshift
id|prof_shift
suffix:semicolon
r_if
c_cond
(paren
id|p
op_ge
(paren
id|prof_len
op_plus
l_int|1
)paren
op_star
r_sizeof
(paren
r_int
r_int
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|count
OG
(paren
id|prof_len
op_plus
l_int|1
)paren
op_star
r_sizeof
(paren
r_int
r_int
)paren
op_minus
id|p
)paren
id|count
op_assign
(paren
id|prof_len
op_plus
l_int|1
)paren
op_star
r_sizeof
(paren
r_int
r_int
)paren
op_minus
id|p
suffix:semicolon
id|read
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|p
template_param
l_int|0
)paren
(brace
id|put_user
c_func
(paren
op_star
(paren
(paren
r_char
op_star
)paren
(paren
op_amp
id|sample_step
)paren
op_plus
id|p
)paren
comma
id|buf
)paren
suffix:semicolon
id|buf
op_increment
suffix:semicolon
id|p
op_increment
suffix:semicolon
id|count
op_decrement
suffix:semicolon
id|read
op_increment
suffix:semicolon
)brace
id|pnt
op_assign
(paren
r_char
op_star
)paren
id|prof_buffer
op_plus
id|p
op_minus
r_sizeof
(paren
r_int
r_int
)paren
suffix:semicolon
id|copy_to_user
c_func
(paren
id|buf
comma
(paren
r_void
op_star
)paren
id|pnt
comma
id|count
)paren
suffix:semicolon
id|read
op_add_assign
id|count
suffix:semicolon
op_star
id|ppos
op_add_assign
id|read
suffix:semicolon
r_return
id|read
suffix:semicolon
)brace
multiline_comment|/*&n; * Writing to /proc/profile resets the counters&n; *&n; * Writing a &squot;profiling multiplier&squot; value into it also re-sets the profiling&n; * interrupt frequency, on architectures that support this.&n; */
DECL|function|write_profile
r_static
id|ssize_t
id|write_profile
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|ppos
)paren
(brace
macro_line|#ifdef CONFIG_SMP
r_extern
r_int
id|setup_profiling_timer
(paren
r_int
r_int
id|multiplier
)paren
suffix:semicolon
r_if
c_cond
(paren
id|count
op_eq
r_sizeof
(paren
r_int
)paren
)paren
(brace
r_int
r_int
id|multiplier
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|multiplier
comma
id|buf
comma
r_sizeof
(paren
r_int
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|setup_profiling_timer
c_func
(paren
id|multiplier
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
macro_line|#endif
id|memset
c_func
(paren
id|prof_buffer
comma
l_int|0
comma
id|prof_len
op_star
r_sizeof
(paren
op_star
id|prof_buffer
)paren
)paren
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
DECL|variable|proc_profile_operations
r_static
r_struct
id|file_operations
id|proc_profile_operations
op_assign
(brace
id|read
suffix:colon
id|read_profile
comma
id|write
suffix:colon
id|write_profile
comma
)brace
suffix:semicolon
DECL|variable|proc_root_kcore
r_struct
id|proc_dir_entry
op_star
id|proc_root_kcore
suffix:semicolon
DECL|function|proc_misc_init
r_void
id|__init
id|proc_misc_init
c_func
(paren
r_void
)paren
(brace
r_struct
id|proc_dir_entry
op_star
id|entry
suffix:semicolon
r_static
r_struct
(brace
r_char
op_star
id|name
suffix:semicolon
r_int
(paren
op_star
id|read_proc
)paren
(paren
r_char
op_star
comma
r_char
op_star
op_star
comma
id|off_t
comma
r_int
comma
r_int
op_star
comma
r_void
op_star
)paren
suffix:semicolon
)brace
op_star
id|p
comma
id|simple_ones
(braket
)braket
op_assign
(brace
(brace
l_string|&quot;loadavg&quot;
comma
id|loadavg_read_proc
)brace
comma
(brace
l_string|&quot;uptime&quot;
comma
id|uptime_read_proc
)brace
comma
(brace
l_string|&quot;meminfo&quot;
comma
id|meminfo_read_proc
)brace
comma
(brace
l_string|&quot;version&quot;
comma
id|version_read_proc
)brace
comma
(brace
l_string|&quot;cpuinfo&quot;
comma
id|cpuinfo_read_proc
)brace
comma
macro_line|#ifdef CONFIG_PROC_HARDWARE
(brace
l_string|&quot;hardware&quot;
comma
id|hardware_read_proc
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_STRAM_PROC
(brace
l_string|&quot;stram&quot;
comma
id|stram_read_proc
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_DEBUG_MALLOC
(brace
l_string|&quot;malloc&quot;
comma
id|malloc_read_proc
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_MODULES
(brace
l_string|&quot;modules&quot;
comma
id|modules_read_proc
)brace
comma
(brace
l_string|&quot;ksyms&quot;
comma
id|ksyms_read_proc
)brace
comma
macro_line|#endif
(brace
l_string|&quot;stat&quot;
comma
id|kstat_read_proc
)brace
comma
(brace
l_string|&quot;devices&quot;
comma
id|devices_read_proc
)brace
comma
(brace
l_string|&quot;partitions&quot;
comma
id|partitions_read_proc
)brace
comma
macro_line|#if !defined(CONFIG_ARCH_S390)
(brace
l_string|&quot;interrupts&quot;
comma
id|interrupts_read_proc
)brace
comma
macro_line|#endif
(brace
l_string|&quot;filesystems&quot;
comma
id|filesystems_read_proc
)brace
comma
(brace
l_string|&quot;dma&quot;
comma
id|dma_read_proc
)brace
comma
(brace
l_string|&quot;ioports&quot;
comma
id|ioports_read_proc
)brace
comma
(brace
l_string|&quot;cmdline&quot;
comma
id|cmdline_read_proc
)brace
comma
macro_line|#ifdef CONFIG_SGI_DS1286
(brace
l_string|&quot;rtc&quot;
comma
id|ds1286_read_proc
)brace
comma
macro_line|#endif
(brace
l_string|&quot;locks&quot;
comma
id|locks_read_proc
)brace
comma
(brace
l_string|&quot;mounts&quot;
comma
id|mounts_read_proc
)brace
comma
(brace
l_string|&quot;swaps&quot;
comma
id|swaps_read_proc
)brace
comma
(brace
l_string|&quot;iomem&quot;
comma
id|memory_read_proc
)brace
comma
(brace
l_string|&quot;execdomains&quot;
comma
id|execdomains_read_proc
)brace
comma
(brace
l_int|NULL
comma
)brace
)brace
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|simple_ones
suffix:semicolon
id|p-&gt;name
suffix:semicolon
id|p
op_increment
)paren
id|create_proc_read_entry
c_func
(paren
id|p-&gt;name
comma
l_int|0
comma
l_int|NULL
comma
id|p-&gt;read_proc
comma
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/* And now for trickier ones */
id|entry
op_assign
id|create_proc_entry
c_func
(paren
l_string|&quot;kmsg&quot;
comma
id|S_IRUSR
comma
op_amp
id|proc_root
)paren
suffix:semicolon
r_if
c_cond
(paren
id|entry
)paren
id|entry-&gt;proc_fops
op_assign
op_amp
id|proc_kmsg_operations
suffix:semicolon
id|proc_root_kcore
op_assign
id|create_proc_entry
c_func
(paren
l_string|&quot;kcore&quot;
comma
id|S_IRUSR
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|proc_root_kcore
)paren
(brace
id|proc_root_kcore-&gt;proc_fops
op_assign
op_amp
id|proc_kcore_operations
suffix:semicolon
id|proc_root_kcore-&gt;size
op_assign
(paren
r_int
)paren
id|high_memory
op_minus
id|PAGE_OFFSET
op_plus
id|PAGE_SIZE
suffix:semicolon
)brace
r_if
c_cond
(paren
id|prof_shift
)paren
(brace
id|entry
op_assign
id|create_proc_entry
c_func
(paren
l_string|&quot;profile&quot;
comma
id|S_IWUSR
op_or
id|S_IRUGO
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|entry
)paren
(brace
id|entry-&gt;proc_fops
op_assign
op_amp
id|proc_profile_operations
suffix:semicolon
id|entry-&gt;size
op_assign
(paren
l_int|1
op_plus
id|prof_len
)paren
op_star
r_sizeof
(paren
r_int
r_int
)paren
suffix:semicolon
)brace
)brace
macro_line|#ifdef __powerpc__
(brace
r_extern
r_struct
id|file_operations
id|ppc_htab_operations
suffix:semicolon
id|entry
op_assign
id|create_proc_entry
c_func
(paren
l_string|&quot;ppc_htab&quot;
comma
id|S_IRUGO
op_or
id|S_IWUSR
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|entry
)paren
id|entry-&gt;proc_fops
op_assign
op_amp
id|ppc_htab_operations
suffix:semicolon
)brace
macro_line|#endif
id|entry
op_assign
id|create_proc_read_entry
c_func
(paren
l_string|&quot;slabinfo&quot;
comma
id|S_IWUSR
op_or
id|S_IRUGO
comma
l_int|NULL
comma
id|slabinfo_read_proc
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|entry
)paren
id|entry-&gt;write_proc
op_assign
id|slabinfo_write_proc
suffix:semicolon
)brace
eof
