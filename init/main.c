multiline_comment|/*&n; *  linux/init/main.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; *&n; *  GK 2/5/95  -  Changed to support mounting root fs via NFS&n; *  Added initrd &amp; change_root: Werner Almesberger &amp; Hans Lermen, Feb &squot;96&n; *  Moan early if gcc is old, avoiding bogus kernels - Paul Gortmaker, May &squot;96&n; *  Simplified starting of init:  Michael A. Griffith &lt;grif@acm.org&gt; &n; */
DECL|macro|__KERNEL_SYSCALLS__
mdefine_line|#define __KERNEL_SYSCALLS__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/devfs_fs_kernel.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/ctype.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/utsname.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &lt;linux/hdreg.h&gt;
macro_line|#include &lt;linux/iobuf.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/percpu.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/security.h&gt;
macro_line|#include &lt;linux/workqueue.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/bugs.h&gt;
macro_line|#if defined(CONFIG_ARCH_S390)
macro_line|#include &lt;asm/s390mach.h&gt;
macro_line|#endif
macro_line|#ifdef CONFIG_X86_LOCAL_APIC
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#endif
multiline_comment|/*&n; * Versions of gcc older than that listed below may actually compile&n; * and link okay, but the end product can have subtle run time bugs.&n; * To avoid associated bogus bug reports, we flatly refuse to compile&n; * with a gcc that is known to be too old from the very beginning.&n; */
macro_line|#if __GNUC__ &lt; 2 || (__GNUC__ == 2 &amp;&amp; __GNUC_MINOR__ &lt; 91)
macro_line|#error Sorry, your GCC is too old. It builds incorrect kernels.
macro_line|#endif
r_extern
r_char
id|_stext
comma
id|_etext
suffix:semicolon
r_extern
r_char
op_star
id|linux_banner
suffix:semicolon
r_static
r_int
id|init
c_func
(paren
r_void
op_star
)paren
suffix:semicolon
r_extern
r_void
id|init_IRQ
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|init_modules
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|sock_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|fork_init
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|mca_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|sbus_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|sysctl_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|signals_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|buffer_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|pidhash_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|pte_chain_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|radix_tree_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|free_initmem
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_TC
r_extern
r_void
id|tc_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if defined(CONFIG_SYSVIPC)
r_extern
r_void
id|ipc_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Are we up and running (ie do we have all the infrastructure&n; * set up)&n; */
DECL|variable|system_running
r_int
id|system_running
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n; * Boot command-line arguments&n; */
DECL|macro|MAX_INIT_ARGS
mdefine_line|#define MAX_INIT_ARGS 8
DECL|macro|MAX_INIT_ENVS
mdefine_line|#define MAX_INIT_ENVS 8
r_extern
r_void
id|time_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|softirq_init
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|variable|rows
DECL|variable|cols
r_int
id|rows
comma
id|cols
suffix:semicolon
DECL|variable|execute_command
r_char
op_star
id|execute_command
suffix:semicolon
multiline_comment|/* Setup configured maximum number of CPUs to activate */
DECL|variable|max_cpus
r_static
r_int
r_int
id|max_cpus
op_assign
id|UINT_MAX
suffix:semicolon
multiline_comment|/*&n; * Setup routine for controlling SMP activation&n; *&n; * Command-line option of &quot;nosmp&quot; or &quot;maxcpus=0&quot; will disable SMP&n; * activation entirely (the MPS table probe still happens, though).&n; *&n; * Command-line option of &quot;maxcpus=&lt;NUM&gt;&quot;, where &lt;NUM&gt; is an integer&n; * greater than 0, limits the maximum number of CPUs activated in&n; * SMP mode to &lt;NUM&gt;.&n; */
DECL|function|nosmp
r_static
r_int
id|__init
id|nosmp
c_func
(paren
r_char
op_star
id|str
)paren
(brace
id|max_cpus
op_assign
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;nosmp&quot;
comma
id|nosmp
)paren
suffix:semicolon
DECL|function|maxcpus
r_static
r_int
id|__init
id|maxcpus
c_func
(paren
r_char
op_star
id|str
)paren
(brace
id|get_option
c_func
(paren
op_amp
id|str
comma
op_amp
id|max_cpus
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;maxcpus=&quot;
comma
id|maxcpus
)paren
suffix:semicolon
DECL|variable|argv_init
r_static
r_char
op_star
id|argv_init
(braket
id|MAX_INIT_ARGS
op_plus
l_int|2
)braket
op_assign
(brace
l_string|&quot;init&quot;
comma
l_int|NULL
comma
)brace
suffix:semicolon
DECL|variable|envp_init
r_char
op_star
id|envp_init
(braket
id|MAX_INIT_ENVS
op_plus
l_int|2
)braket
op_assign
(brace
l_string|&quot;HOME=/&quot;
comma
l_string|&quot;TERM=linux&quot;
comma
l_int|NULL
comma
)brace
suffix:semicolon
DECL|function|profile_setup
r_static
r_int
id|__init
id|profile_setup
c_func
(paren
r_char
op_star
id|str
)paren
(brace
r_int
id|par
suffix:semicolon
r_if
c_cond
(paren
id|get_option
c_func
(paren
op_amp
id|str
comma
op_amp
id|par
)paren
)paren
id|prof_shift
op_assign
id|par
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;profile=&quot;
comma
id|profile_setup
)paren
suffix:semicolon
DECL|function|checksetup
r_static
r_int
id|__init
id|checksetup
c_func
(paren
r_char
op_star
id|line
)paren
(brace
r_struct
id|kernel_param
op_star
id|p
suffix:semicolon
id|p
op_assign
op_amp
id|__setup_start
suffix:semicolon
r_do
(brace
r_int
id|n
op_assign
id|strlen
c_func
(paren
id|p-&gt;str
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|line
comma
id|p-&gt;str
comma
id|n
)paren
)paren
(brace
r_if
c_cond
(paren
id|p
op_member_access_from_pointer
id|setup_func
c_func
(paren
id|line
op_plus
id|n
)paren
)paren
r_return
l_int|1
suffix:semicolon
)brace
id|p
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
id|p
OL
op_amp
id|__setup_end
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* this should be approx 2 Bo*oMips to start (note initial shift), and will&n;   still work even if initially too large, it will just take slightly longer */
DECL|variable|loops_per_jiffy
r_int
r_int
id|loops_per_jiffy
op_assign
(paren
l_int|1
op_lshift
l_int|12
)paren
suffix:semicolon
multiline_comment|/* This is the number of bits of precision for the loops_per_jiffy.  Each&n;   bit takes on average 1.5/HZ seconds.  This (like the original) is a little&n;   better than 1% */
DECL|macro|LPS_PREC
mdefine_line|#define LPS_PREC 8
DECL|function|calibrate_delay
r_void
id|__init
id|calibrate_delay
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|ticks
comma
id|loopbit
suffix:semicolon
r_int
id|lps_precision
op_assign
id|LPS_PREC
suffix:semicolon
id|loops_per_jiffy
op_assign
(paren
l_int|1
op_lshift
l_int|12
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Calibrating delay loop... &quot;
)paren
suffix:semicolon
r_while
c_loop
(paren
id|loops_per_jiffy
op_lshift_assign
l_int|1
)paren
(brace
multiline_comment|/* wait for &quot;start of&quot; clock tick */
id|ticks
op_assign
id|jiffies
suffix:semicolon
r_while
c_loop
(paren
id|ticks
op_eq
id|jiffies
)paren
multiline_comment|/* nothing */
suffix:semicolon
multiline_comment|/* Go .. */
id|ticks
op_assign
id|jiffies
suffix:semicolon
id|__delay
c_func
(paren
id|loops_per_jiffy
)paren
suffix:semicolon
id|ticks
op_assign
id|jiffies
op_minus
id|ticks
suffix:semicolon
r_if
c_cond
(paren
id|ticks
)paren
r_break
suffix:semicolon
)brace
multiline_comment|/* Do a binary approximation to get loops_per_jiffy set to equal one clock&n;   (up to lps_precision bits) */
id|loops_per_jiffy
op_rshift_assign
l_int|1
suffix:semicolon
id|loopbit
op_assign
id|loops_per_jiffy
suffix:semicolon
r_while
c_loop
(paren
id|lps_precision
op_decrement
op_logical_and
(paren
id|loopbit
op_rshift_assign
l_int|1
)paren
)paren
(brace
id|loops_per_jiffy
op_or_assign
id|loopbit
suffix:semicolon
id|ticks
op_assign
id|jiffies
suffix:semicolon
r_while
c_loop
(paren
id|ticks
op_eq
id|jiffies
)paren
suffix:semicolon
id|ticks
op_assign
id|jiffies
suffix:semicolon
id|__delay
c_func
(paren
id|loops_per_jiffy
)paren
suffix:semicolon
r_if
c_cond
(paren
id|jiffies
op_ne
id|ticks
)paren
multiline_comment|/* longer than 1 tick */
id|loops_per_jiffy
op_and_assign
op_complement
id|loopbit
suffix:semicolon
)brace
multiline_comment|/* Round the value and print it */
id|printk
c_func
(paren
l_string|&quot;%lu.%02lu BogoMIPS&bslash;n&quot;
comma
id|loops_per_jiffy
op_div
(paren
l_int|500000
op_div
id|HZ
)paren
comma
(paren
id|loops_per_jiffy
op_div
(paren
l_int|5000
op_div
id|HZ
)paren
)paren
op_mod
l_int|100
)paren
suffix:semicolon
)brace
DECL|function|debug_kernel
r_static
r_int
id|__init
id|debug_kernel
c_func
(paren
r_char
op_star
id|str
)paren
(brace
r_if
c_cond
(paren
op_star
id|str
)paren
r_return
l_int|0
suffix:semicolon
id|console_loglevel
op_assign
l_int|10
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|quiet_kernel
r_static
r_int
id|__init
id|quiet_kernel
c_func
(paren
r_char
op_star
id|str
)paren
(brace
r_if
c_cond
(paren
op_star
id|str
)paren
r_return
l_int|0
suffix:semicolon
id|console_loglevel
op_assign
l_int|4
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;debug&quot;
comma
id|debug_kernel
)paren
suffix:semicolon
id|__setup
c_func
(paren
l_string|&quot;quiet&quot;
comma
id|quiet_kernel
)paren
suffix:semicolon
multiline_comment|/*&n; * This is a simple kernel command line parsing function: it parses&n; * the command line, and fills in the arguments/environment to init&n; * as appropriate. Any cmd-line option is taken to be an environment&n; * variable if it contains the character &squot;=&squot;.&n; *&n; * This routine also checks for options meant for the kernel.&n; * These options are not given to init - they are for internal kernel use only.&n; */
DECL|function|parse_options
r_static
r_void
id|__init
id|parse_options
c_func
(paren
r_char
op_star
id|line
)paren
(brace
r_char
op_star
id|next
comma
op_star
id|quote
suffix:semicolon
r_int
id|args
comma
id|envs
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|line
)paren
r_return
suffix:semicolon
id|args
op_assign
l_int|0
suffix:semicolon
id|envs
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* TERM is set to &squot;linux&squot; by default */
id|next
op_assign
id|line
suffix:semicolon
r_while
c_loop
(paren
(paren
id|line
op_assign
id|next
)paren
op_ne
l_int|NULL
)paren
(brace
id|quote
op_assign
id|strchr
c_func
(paren
id|line
comma
l_char|&squot;&quot;&squot;
)paren
suffix:semicolon
id|next
op_assign
id|strchr
c_func
(paren
id|line
comma
l_char|&squot; &squot;
)paren
suffix:semicolon
r_while
c_loop
(paren
id|next
op_ne
l_int|NULL
op_logical_and
id|quote
op_ne
l_int|NULL
op_logical_and
id|quote
OL
id|next
)paren
(brace
multiline_comment|/* we found a left quote before the next blank&n;                         * now we have to find the matching right quote&n;                         */
id|next
op_assign
id|strchr
c_func
(paren
id|quote
op_plus
l_int|1
comma
l_char|&squot;&quot;&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|next
op_ne
l_int|NULL
)paren
(brace
id|quote
op_assign
id|strchr
c_func
(paren
id|next
op_plus
l_int|1
comma
l_char|&squot;&quot;&squot;
)paren
suffix:semicolon
id|next
op_assign
id|strchr
c_func
(paren
id|next
op_plus
l_int|1
comma
l_char|&squot; &squot;
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|next
op_ne
l_int|NULL
)paren
op_star
id|next
op_increment
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|line
comma
l_string|&quot;init=&quot;
comma
l_int|5
)paren
)paren
(brace
id|line
op_add_assign
l_int|5
suffix:semicolon
id|execute_command
op_assign
id|line
suffix:semicolon
multiline_comment|/* In case LILO is going to boot us with default command line,&n;&t;&t;&t; * it prepends &quot;auto&quot; before the whole cmdline which makes&n;&t;&t;&t; * the shell think it should execute a script with such name.&n;&t;&t;&t; * So we ignore all arguments entered _before_ init=... [MJ]&n;&t;&t;&t; */
id|args
op_assign
l_int|0
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|checksetup
c_func
(paren
id|line
)paren
)paren
r_continue
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Then check if it&squot;s an environment variable or&n;&t;&t; * an option.&n;&t;&t; */
r_if
c_cond
(paren
id|strchr
c_func
(paren
id|line
comma
l_char|&squot;=&squot;
)paren
)paren
(brace
r_if
c_cond
(paren
id|envs
op_ge
id|MAX_INIT_ENVS
)paren
r_break
suffix:semicolon
id|envp_init
(braket
op_increment
id|envs
)braket
op_assign
id|line
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|args
op_ge
id|MAX_INIT_ARGS
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_star
id|line
)paren
id|argv_init
(braket
op_increment
id|args
)braket
op_assign
id|line
suffix:semicolon
)brace
)brace
id|argv_init
(braket
id|args
op_plus
l_int|1
)braket
op_assign
l_int|NULL
suffix:semicolon
id|envp_init
(braket
id|envs
op_plus
l_int|1
)braket
op_assign
l_int|NULL
suffix:semicolon
)brace
r_extern
r_void
id|setup_arch
c_func
(paren
r_char
op_star
op_star
)paren
suffix:semicolon
r_extern
r_void
id|cpu_idle
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#ifndef CONFIG_SMP
macro_line|#ifdef CONFIG_X86_LOCAL_APIC
DECL|function|smp_init
r_static
r_void
id|__init
id|smp_init
c_func
(paren
r_void
)paren
(brace
id|APIC_init_uniprocessor
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#else
DECL|macro|smp_init
mdefine_line|#define smp_init()&t;do { } while (0)
macro_line|#endif
DECL|function|setup_per_cpu_areas
r_static
r_inline
r_void
id|setup_per_cpu_areas
c_func
(paren
r_void
)paren
(brace
)brace
DECL|function|smp_prepare_cpus
r_static
r_inline
r_void
id|smp_prepare_cpus
c_func
(paren
r_int
r_int
id|maxcpus
)paren
(brace
)brace
macro_line|#else
macro_line|#ifdef __GENERIC_PER_CPU
DECL|variable|__per_cpu_offset
r_int
r_int
id|__per_cpu_offset
(braket
id|NR_CPUS
)braket
suffix:semicolon
DECL|function|setup_per_cpu_areas
r_static
r_void
id|__init
id|setup_per_cpu_areas
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|size
comma
id|i
suffix:semicolon
r_char
op_star
id|ptr
suffix:semicolon
multiline_comment|/* Created by linker magic */
r_extern
r_char
id|__per_cpu_start
(braket
)braket
comma
id|__per_cpu_end
(braket
)braket
suffix:semicolon
multiline_comment|/* Copy section for each CPU (we discard the original) */
id|size
op_assign
id|ALIGN
c_func
(paren
id|__per_cpu_end
op_minus
id|__per_cpu_start
comma
id|SMP_CACHE_BYTES
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|size
)paren
r_return
suffix:semicolon
id|ptr
op_assign
id|alloc_bootmem
c_func
(paren
id|size
op_star
id|NR_CPUS
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
id|NR_CPUS
suffix:semicolon
id|i
op_increment
comma
id|ptr
op_add_assign
id|size
)paren
(brace
id|__per_cpu_offset
(braket
id|i
)braket
op_assign
id|ptr
op_minus
id|__per_cpu_start
suffix:semicolon
id|memcpy
c_func
(paren
id|ptr
comma
id|__per_cpu_start
comma
id|size
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif /* !__GENERIC_PER_CPU */
multiline_comment|/* Called by boot processor to activate the rest. */
DECL|function|smp_init
r_static
r_void
id|__init
id|smp_init
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|i
suffix:semicolon
multiline_comment|/* FIXME: This should be done in userspace --RR */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NR_CPUS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|num_online_cpus
c_func
(paren
)paren
op_ge
id|max_cpus
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|cpu_possible
c_func
(paren
id|i
)paren
op_logical_and
op_logical_neg
id|cpu_online
c_func
(paren
id|i
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Bringing up %i&bslash;n&quot;
comma
id|i
)paren
suffix:semicolon
id|cpu_up
c_func
(paren
id|i
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Any cleanup work */
id|printk
c_func
(paren
l_string|&quot;CPUS done %u&bslash;n&quot;
comma
id|max_cpus
)paren
suffix:semicolon
id|smp_cpus_done
c_func
(paren
id|max_cpus
)paren
suffix:semicolon
macro_line|#if 0
multiline_comment|/* Get other processors into their bootup holding patterns. */
id|smp_threads_ready
op_assign
l_int|1
suffix:semicolon
id|smp_commence
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
)brace
macro_line|#endif
multiline_comment|/*&n; * We need to finalize in a non-__init function or else race conditions&n; * between the root thread and the init thread may cause start_kernel to&n; * be reaped by free_initmem before the root thread has proceeded to&n; * cpu_idle.&n; */
DECL|function|rest_init
r_static
r_void
id|rest_init
c_func
(paren
r_void
)paren
(brace
id|kernel_thread
c_func
(paren
id|init
comma
l_int|NULL
comma
id|CLONE_KERNEL
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
id|cpu_idle
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Activate the first processor.&n; */
DECL|function|start_kernel
id|asmlinkage
r_void
id|__init
id|start_kernel
c_func
(paren
r_void
)paren
(brace
r_char
op_star
id|command_line
suffix:semicolon
r_extern
r_char
id|saved_command_line
(braket
)braket
suffix:semicolon
multiline_comment|/*&n; * Interrupts are still disabled. Do necessary setups, then&n; * enable them&n; */
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
id|linux_banner
)paren
suffix:semicolon
id|setup_arch
c_func
(paren
op_amp
id|command_line
)paren
suffix:semicolon
id|setup_per_cpu_areas
c_func
(paren
)paren
suffix:semicolon
id|build_all_zonelists
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Kernel command line: %s&bslash;n&quot;
comma
id|saved_command_line
)paren
suffix:semicolon
id|parse_options
c_func
(paren
id|command_line
)paren
suffix:semicolon
id|trap_init
c_func
(paren
)paren
suffix:semicolon
id|init_IRQ
c_func
(paren
)paren
suffix:semicolon
id|sched_init
c_func
(paren
)paren
suffix:semicolon
id|softirq_init
c_func
(paren
)paren
suffix:semicolon
id|time_init
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * HACK ALERT! This is early. We&squot;re enabling the console before&n;&t; * we&squot;ve done PCI setups etc, and console_init() must be aware of&n;&t; * this. But we do want output early, in case something goes wrong.&n;&t; */
id|console_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_MODULES
id|init_modules
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|prof_shift
)paren
(brace
r_int
r_int
id|size
suffix:semicolon
multiline_comment|/* only text is profiled */
id|prof_len
op_assign
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
suffix:semicolon
id|prof_len
op_rshift_assign
id|prof_shift
suffix:semicolon
id|size
op_assign
id|prof_len
op_star
r_sizeof
(paren
r_int
r_int
)paren
op_plus
id|PAGE_SIZE
op_minus
l_int|1
suffix:semicolon
id|prof_buffer
op_assign
(paren
r_int
r_int
op_star
)paren
id|alloc_bootmem
c_func
(paren
id|size
)paren
suffix:semicolon
)brace
id|kmem_cache_init
c_func
(paren
)paren
suffix:semicolon
id|local_irq_enable
c_func
(paren
)paren
suffix:semicolon
id|calibrate_delay
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
r_if
c_cond
(paren
id|initrd_start
op_logical_and
op_logical_neg
id|initrd_below_start_ok
op_logical_and
id|initrd_start
OL
id|min_low_pfn
op_lshift
id|PAGE_SHIFT
)paren
(brace
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;initrd overwritten (0x%08lx &lt; 0x%08lx) - &quot;
l_string|&quot;disabling it.&bslash;n&quot;
comma
id|initrd_start
comma
id|min_low_pfn
op_lshift
id|PAGE_SHIFT
)paren
suffix:semicolon
id|initrd_start
op_assign
l_int|0
suffix:semicolon
)brace
macro_line|#endif
id|mem_init
c_func
(paren
)paren
suffix:semicolon
id|kmem_cache_sizes_init
c_func
(paren
)paren
suffix:semicolon
id|pidhash_init
c_func
(paren
)paren
suffix:semicolon
id|pgtable_cache_init
c_func
(paren
)paren
suffix:semicolon
id|pte_chain_init
c_func
(paren
)paren
suffix:semicolon
id|fork_init
c_func
(paren
id|num_physpages
)paren
suffix:semicolon
id|proc_caches_init
c_func
(paren
)paren
suffix:semicolon
id|security_scaffolding_startup
c_func
(paren
)paren
suffix:semicolon
id|buffer_init
c_func
(paren
)paren
suffix:semicolon
id|vfs_caches_init
c_func
(paren
id|num_physpages
)paren
suffix:semicolon
id|radix_tree_init
c_func
(paren
)paren
suffix:semicolon
id|signals_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PROC_FS
id|proc_root_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if defined(CONFIG_SYSVIPC)
id|ipc_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|check_bugs
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;POSIX conformance testing by UNIFIX&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* &n;&t; *&t;We count on the initial thread going ok &n;&t; *&t;Like idlers init is an unlocked kernel thread, which will&n;&t; *&t;make syscalls (and thus be locked).&n;&t; */
id|init_idle
c_func
(paren
id|current
comma
id|smp_processor_id
c_func
(paren
)paren
)paren
suffix:semicolon
multiline_comment|/* Do the rest non-__init&squot;ed, we&squot;re now alive */
id|rest_init
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|variable|child_reaper
r_struct
id|task_struct
op_star
id|child_reaper
op_assign
op_amp
id|init_task
suffix:semicolon
DECL|function|do_initcalls
r_static
r_void
id|__init
id|do_initcalls
c_func
(paren
r_void
)paren
(brace
id|initcall_t
op_star
id|call
suffix:semicolon
id|call
op_assign
op_amp
id|__initcall_start
suffix:semicolon
r_do
(brace
(paren
op_star
id|call
)paren
(paren
)paren
suffix:semicolon
id|call
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
id|call
OL
op_amp
id|__initcall_end
)paren
suffix:semicolon
multiline_comment|/* Make sure there is no pending stuff from the initcall sequence */
id|flush_scheduled_work
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Ok, the machine is now initialized. None of the devices&n; * have been touched yet, but the CPU subsystem is up and&n; * running, and memory and process management works.&n; *&n; * Now we can finally start doing some real work..&n; */
DECL|function|do_basic_setup
r_static
r_void
id|__init
id|do_basic_setup
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_SYSCTL
id|sysctl_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t; * Ok, at this point all CPU&squot;s should be initialized, so&n;&t; * we can start looking into devices..&n;&t; */
macro_line|#if defined(CONFIG_ARCH_S390)
id|s390_init_machine_check
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Networking initialization needs a process context */
id|sock_init
c_func
(paren
)paren
suffix:semicolon
id|init_workqueues
c_func
(paren
)paren
suffix:semicolon
id|do_initcalls
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|do_pre_smp_initcalls
r_static
r_void
id|do_pre_smp_initcalls
c_func
(paren
r_void
)paren
(brace
r_extern
r_int
id|spawn_ksoftirqd
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
r_extern
r_int
id|migration_init
c_func
(paren
r_void
)paren
suffix:semicolon
id|migration_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|spawn_ksoftirqd
c_func
(paren
)paren
suffix:semicolon
)brace
r_extern
r_void
id|prepare_namespace
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|init
r_static
r_int
id|init
c_func
(paren
r_void
op_star
id|unused
)paren
(brace
r_static
r_char
op_star
id|argv_sh
(braket
)braket
op_assign
(brace
l_string|&quot;sh&quot;
comma
l_int|NULL
comma
)brace
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Tell the world that we&squot;re going to be the grim&n;&t; * reaper of innocent orphaned children.&n;&t; *&n;&t; * We don&squot;t want people to have to make incorrect&n;&t; * assumptions about where in the task array this&n;&t; * can be found.&n;&t; */
id|child_reaper
op_assign
id|current
suffix:semicolon
multiline_comment|/* Sets up cpus_possible() */
id|smp_prepare_cpus
c_func
(paren
id|max_cpus
)paren
suffix:semicolon
id|do_pre_smp_initcalls
c_func
(paren
)paren
suffix:semicolon
id|smp_init
c_func
(paren
)paren
suffix:semicolon
id|do_basic_setup
c_func
(paren
)paren
suffix:semicolon
id|prepare_namespace
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Ok, we have completed the initial bootup, and&n;&t; * we&squot;re essentially up and running. Get rid of the&n;&t; * initmem segments and start the user-mode stuff..&n;&t; */
id|free_initmem
c_func
(paren
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
id|system_running
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|open
c_func
(paren
l_string|&quot;/dev/console&quot;
comma
id|O_RDWR
comma
l_int|0
)paren
OL
l_int|0
)paren
id|printk
c_func
(paren
l_string|&quot;Warning: unable to open an initial console.&bslash;n&quot;
)paren
suffix:semicolon
(paren
r_void
)paren
id|dup
c_func
(paren
l_int|0
)paren
suffix:semicolon
(paren
r_void
)paren
id|dup
c_func
(paren
l_int|0
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * We try each of these until one succeeds.&n;&t; *&n;&t; * The Bourne shell can be used instead of init if we are &n;&t; * trying to recover a really broken machine.&n;&t; */
r_if
c_cond
(paren
id|execute_command
)paren
id|execve
c_func
(paren
id|execute_command
comma
id|argv_init
comma
id|envp_init
)paren
suffix:semicolon
id|execve
c_func
(paren
l_string|&quot;/sbin/init&quot;
comma
id|argv_init
comma
id|envp_init
)paren
suffix:semicolon
id|execve
c_func
(paren
l_string|&quot;/etc/init&quot;
comma
id|argv_init
comma
id|envp_init
)paren
suffix:semicolon
id|execve
c_func
(paren
l_string|&quot;/bin/init&quot;
comma
id|argv_init
comma
id|envp_init
)paren
suffix:semicolon
id|execve
c_func
(paren
l_string|&quot;/bin/sh&quot;
comma
id|argv_sh
comma
id|envp_init
)paren
suffix:semicolon
id|panic
c_func
(paren
l_string|&quot;No init found.  Try passing init= option to kernel.&quot;
)paren
suffix:semicolon
)brace
eof
