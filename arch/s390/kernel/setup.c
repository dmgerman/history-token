multiline_comment|/*&n; *  arch/s390/kernel/setup.c&n; *&n; *  S390 version&n; *    Copyright (C) 1999,2000 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Hartmut Penner (hp@de.ibm.com),&n; *               Martin Schwidefsky (schwidefsky@de.ibm.com)&n; *&n; *  Derived from &quot;arch/i386/kernel/setup.c&quot;&n; *    Copyright (C) 1995, Linus Torvalds&n; */
multiline_comment|/*&n; * This file handles the architecture-dependent parts of initialization&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/user.h&gt;
macro_line|#include &lt;linux/a.out.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/initrd.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;linux/root_dev.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#include &lt;asm/mmu_context.h&gt;
macro_line|#include &lt;asm/cpcmd.h&gt;
macro_line|#include &lt;asm/lowcore.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
multiline_comment|/*&n; * Machine setup..&n; */
DECL|variable|console_mode
r_int
r_int
id|console_mode
op_assign
l_int|0
suffix:semicolon
DECL|variable|console_devno
r_int
r_int
id|console_devno
op_assign
op_minus
l_int|1
suffix:semicolon
DECL|variable|console_irq
r_int
r_int
id|console_irq
op_assign
op_minus
l_int|1
suffix:semicolon
DECL|variable|memory_size
r_int
r_int
id|memory_size
op_assign
l_int|0
suffix:semicolon
DECL|variable|machine_flags
r_int
r_int
id|machine_flags
op_assign
l_int|0
suffix:semicolon
DECL|variable|default_storage_key
r_int
r_int
id|default_storage_key
op_assign
l_int|0
suffix:semicolon
r_struct
(brace
DECL|member|addr
DECL|member|size
DECL|member|type
r_int
r_int
id|addr
comma
id|size
comma
id|type
suffix:semicolon
DECL|variable|memory_chunk
)brace
id|memory_chunk
(braket
id|MEMORY_CHUNKS
)braket
op_assign
(brace
(brace
l_int|0
)brace
)brace
suffix:semicolon
DECL|macro|CHUNK_READ_WRITE
mdefine_line|#define CHUNK_READ_WRITE 0
DECL|macro|CHUNK_READ_ONLY
mdefine_line|#define CHUNK_READ_ONLY 1
DECL|variable|__cpu_logical_map
r_volatile
r_int
id|__cpu_logical_map
(braket
id|NR_CPUS
)braket
suffix:semicolon
multiline_comment|/* logical cpu to cpu address */
multiline_comment|/*&n; * Setup options&n; */
r_extern
r_int
id|_text
comma
id|_etext
comma
id|_edata
comma
id|_end
suffix:semicolon
multiline_comment|/*&n; * This is set up by the setup-routine at boot-time&n; * for S390 need to find out, what we have to setup&n; * using address 0x10400 ...&n; */
macro_line|#include &lt;asm/setup.h&gt;
DECL|variable|command_line
r_static
r_char
id|command_line
(braket
id|COMMAND_LINE_SIZE
)braket
op_assign
(brace
l_int|0
comma
)brace
suffix:semicolon
DECL|variable|code_resource
r_static
r_struct
id|resource
id|code_resource
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;Kernel code&quot;
comma
dot
id|flags
op_assign
id|IORESOURCE_BUSY
op_or
id|IORESOURCE_MEM
comma
)brace
suffix:semicolon
DECL|variable|data_resource
r_static
r_struct
id|resource
id|data_resource
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;Kernel data&quot;
comma
dot
id|flags
op_assign
id|IORESOURCE_BUSY
op_or
id|IORESOURCE_MEM
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * cpu_init() initializes state that is per-CPU.&n; */
DECL|function|cpu_init
r_void
id|__devinit
id|cpu_init
(paren
r_void
)paren
(brace
r_int
id|addr
op_assign
id|hard_smp_processor_id
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;         * Store processor id in lowcore (used e.g. in timer_interrupt)&n;         */
id|asm
r_volatile
(paren
l_string|&quot;stidp %0&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|S390_lowcore.cpu_data.cpu_id
)paren
)paren
suffix:semicolon
id|S390_lowcore.cpu_data.cpu_addr
op_assign
id|addr
suffix:semicolon
multiline_comment|/*&n;         * Force FPU initialization:&n;         */
id|clear_thread_flag
c_func
(paren
id|TIF_USEDFPU
)paren
suffix:semicolon
id|clear_used_math
c_func
(paren
)paren
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|init_mm.mm_count
)paren
suffix:semicolon
id|current-&gt;active_mm
op_assign
op_amp
id|init_mm
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;mm
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|enter_lazy_tlb
c_func
(paren
op_amp
id|init_mm
comma
id|current
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * VM halt and poweroff setup routines&n; */
DECL|variable|vmhalt_cmd
r_char
id|vmhalt_cmd
(braket
l_int|128
)braket
op_assign
l_string|&quot;&quot;
suffix:semicolon
DECL|variable|vmpoff_cmd
r_char
id|vmpoff_cmd
(braket
l_int|128
)braket
op_assign
l_string|&quot;&quot;
suffix:semicolon
DECL|function|strncpy_skip_quote
r_static
r_inline
r_void
id|strncpy_skip_quote
c_func
(paren
r_char
op_star
id|dst
comma
r_char
op_star
id|src
comma
r_int
id|n
)paren
(brace
r_int
id|sx
comma
id|dx
suffix:semicolon
id|dx
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|sx
op_assign
l_int|0
suffix:semicolon
id|src
(braket
id|sx
)braket
op_ne
l_int|0
suffix:semicolon
id|sx
op_increment
)paren
(brace
r_if
c_cond
(paren
id|src
(braket
id|sx
)braket
op_eq
l_char|&squot;&quot;&squot;
)paren
r_continue
suffix:semicolon
id|dst
(braket
id|dx
op_increment
)braket
op_assign
id|src
(braket
id|sx
)braket
suffix:semicolon
r_if
c_cond
(paren
id|dx
op_ge
id|n
)paren
r_break
suffix:semicolon
)brace
)brace
DECL|function|vmhalt_setup
r_static
r_int
id|__init
id|vmhalt_setup
c_func
(paren
r_char
op_star
id|str
)paren
(brace
id|strncpy_skip_quote
c_func
(paren
id|vmhalt_cmd
comma
id|str
comma
l_int|127
)paren
suffix:semicolon
id|vmhalt_cmd
(braket
l_int|127
)braket
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
l_string|&quot;vmhalt=&quot;
comma
id|vmhalt_setup
)paren
suffix:semicolon
DECL|function|vmpoff_setup
r_static
r_int
id|__init
id|vmpoff_setup
c_func
(paren
r_char
op_star
id|str
)paren
(brace
id|strncpy_skip_quote
c_func
(paren
id|vmpoff_cmd
comma
id|str
comma
l_int|127
)paren
suffix:semicolon
id|vmpoff_cmd
(braket
l_int|127
)braket
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
l_string|&quot;vmpoff=&quot;
comma
id|vmpoff_setup
)paren
suffix:semicolon
multiline_comment|/*&n; * condev= and conmode= setup parameter.&n; */
DECL|function|condev_setup
r_static
r_int
id|__init
id|condev_setup
c_func
(paren
r_char
op_star
id|str
)paren
(brace
r_int
id|vdev
suffix:semicolon
id|vdev
op_assign
id|simple_strtoul
c_func
(paren
id|str
comma
op_amp
id|str
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vdev
op_ge
l_int|0
op_logical_and
id|vdev
OL
l_int|65536
)paren
(brace
id|console_devno
op_assign
id|vdev
suffix:semicolon
id|console_irq
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;condev=&quot;
comma
id|condev_setup
)paren
suffix:semicolon
DECL|function|conmode_setup
r_static
r_int
id|__init
id|conmode_setup
c_func
(paren
r_char
op_star
id|str
)paren
(brace
macro_line|#if defined(CONFIG_SCLP_CONSOLE)
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|str
comma
l_string|&quot;hwc&quot;
comma
l_int|4
)paren
op_eq
l_int|0
op_logical_or
id|strncmp
c_func
(paren
id|str
comma
l_string|&quot;sclp&quot;
comma
l_int|5
)paren
op_eq
l_int|0
)paren
id|SET_CONSOLE_SCLP
suffix:semicolon
macro_line|#endif
macro_line|#if defined(CONFIG_TN3215_CONSOLE)
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|str
comma
l_string|&quot;3215&quot;
comma
l_int|5
)paren
op_eq
l_int|0
)paren
id|SET_CONSOLE_3215
suffix:semicolon
macro_line|#endif
macro_line|#if defined(CONFIG_TN3270_CONSOLE)
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|str
comma
l_string|&quot;3270&quot;
comma
l_int|5
)paren
op_eq
l_int|0
)paren
id|SET_CONSOLE_3270
suffix:semicolon
macro_line|#endif
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;conmode=&quot;
comma
id|conmode_setup
)paren
suffix:semicolon
DECL|function|conmode_default
r_static
r_void
id|__init
id|conmode_default
c_func
(paren
r_void
)paren
(brace
r_char
id|query_buffer
(braket
l_int|1024
)braket
suffix:semicolon
r_char
op_star
id|ptr
suffix:semicolon
r_if
c_cond
(paren
id|MACHINE_IS_VM
)paren
(brace
id|__cpcmd
c_func
(paren
l_string|&quot;QUERY CONSOLE&quot;
comma
id|query_buffer
comma
l_int|1024
)paren
suffix:semicolon
id|console_devno
op_assign
id|simple_strtoul
c_func
(paren
id|query_buffer
op_plus
l_int|5
comma
l_int|NULL
comma
l_int|16
)paren
suffix:semicolon
id|ptr
op_assign
id|strstr
c_func
(paren
id|query_buffer
comma
l_string|&quot;SUBCHANNEL =&quot;
)paren
suffix:semicolon
id|console_irq
op_assign
id|simple_strtoul
c_func
(paren
id|ptr
op_plus
l_int|13
comma
l_int|NULL
comma
l_int|16
)paren
suffix:semicolon
id|__cpcmd
c_func
(paren
l_string|&quot;QUERY TERM&quot;
comma
id|query_buffer
comma
l_int|1024
)paren
suffix:semicolon
id|ptr
op_assign
id|strstr
c_func
(paren
id|query_buffer
comma
l_string|&quot;CONMODE&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Set the conmode to 3215 so that the device recognition &n;&t;&t; * will set the cu_type of the console to 3215. If the&n;&t;&t; * conmode is 3270 and we don&squot;t set it back then both&n;&t;&t; * 3215 and the 3270 driver will try to access the console&n;&t;&t; * device (3215 as console and 3270 as normal tty).&n;&t;&t; */
id|__cpcmd
c_func
(paren
l_string|&quot;TERM CONMODE 3215&quot;
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ptr
op_eq
l_int|NULL
)paren
(brace
macro_line|#if defined(CONFIG_SCLP_CONSOLE)
id|SET_CONSOLE_SCLP
suffix:semicolon
macro_line|#endif
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|ptr
op_plus
l_int|8
comma
l_string|&quot;3270&quot;
comma
l_int|4
)paren
op_eq
l_int|0
)paren
(brace
macro_line|#if defined(CONFIG_TN3270_CONSOLE)
id|SET_CONSOLE_3270
suffix:semicolon
macro_line|#elif defined(CONFIG_TN3215_CONSOLE)
id|SET_CONSOLE_3215
suffix:semicolon
macro_line|#elif defined(CONFIG_SCLP_CONSOLE)
id|SET_CONSOLE_SCLP
suffix:semicolon
macro_line|#endif
)brace
r_else
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|ptr
op_plus
l_int|8
comma
l_string|&quot;3215&quot;
comma
l_int|4
)paren
op_eq
l_int|0
)paren
(brace
macro_line|#if defined(CONFIG_TN3215_CONSOLE)
id|SET_CONSOLE_3215
suffix:semicolon
macro_line|#elif defined(CONFIG_TN3270_CONSOLE)
id|SET_CONSOLE_3270
suffix:semicolon
macro_line|#elif defined(CONFIG_SCLP_CONSOLE)
id|SET_CONSOLE_SCLP
suffix:semicolon
macro_line|#endif
)brace
)brace
r_else
r_if
c_cond
(paren
id|MACHINE_IS_P390
)paren
(brace
macro_line|#if defined(CONFIG_TN3215_CONSOLE)
id|SET_CONSOLE_3215
suffix:semicolon
macro_line|#elif defined(CONFIG_TN3270_CONSOLE)
id|SET_CONSOLE_3270
suffix:semicolon
macro_line|#endif
)brace
r_else
(brace
macro_line|#if defined(CONFIG_SCLP_CONSOLE)
id|SET_CONSOLE_SCLP
suffix:semicolon
macro_line|#endif
)brace
)brace
macro_line|#ifdef CONFIG_SMP
r_extern
r_void
id|machine_restart_smp
c_func
(paren
r_char
op_star
)paren
suffix:semicolon
r_extern
r_void
id|machine_halt_smp
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|machine_power_off_smp
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|variable|_machine_restart
r_void
(paren
op_star
id|_machine_restart
)paren
(paren
r_char
op_star
id|command
)paren
op_assign
id|machine_restart_smp
suffix:semicolon
DECL|variable|_machine_halt
r_void
(paren
op_star
id|_machine_halt
)paren
(paren
r_void
)paren
op_assign
id|machine_halt_smp
suffix:semicolon
DECL|variable|_machine_power_off
r_void
(paren
op_star
id|_machine_power_off
)paren
(paren
r_void
)paren
op_assign
id|machine_power_off_smp
suffix:semicolon
macro_line|#else
multiline_comment|/*&n; * Reboot, halt and power_off routines for non SMP.&n; */
r_extern
r_void
id|reipl
c_func
(paren
r_int
r_int
id|devno
)paren
suffix:semicolon
DECL|function|do_machine_restart_nonsmp
r_static
r_void
id|do_machine_restart_nonsmp
c_func
(paren
r_char
op_star
id|__unused
)paren
(brace
r_if
c_cond
(paren
id|MACHINE_IS_VM
)paren
id|cpcmd
(paren
l_string|&quot;IPL&quot;
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
r_else
id|reipl
(paren
l_int|0x10000
op_or
id|S390_lowcore.ipl_device
)paren
suffix:semicolon
)brace
DECL|function|do_machine_halt_nonsmp
r_static
r_void
id|do_machine_halt_nonsmp
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|MACHINE_IS_VM
op_logical_and
id|strlen
c_func
(paren
id|vmhalt_cmd
)paren
OG
l_int|0
)paren
id|cpcmd
c_func
(paren
id|vmhalt_cmd
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
id|signal_processor
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
comma
id|sigp_stop_and_store_status
)paren
suffix:semicolon
)brace
DECL|function|do_machine_power_off_nonsmp
r_static
r_void
id|do_machine_power_off_nonsmp
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|MACHINE_IS_VM
op_logical_and
id|strlen
c_func
(paren
id|vmpoff_cmd
)paren
OG
l_int|0
)paren
id|cpcmd
c_func
(paren
id|vmpoff_cmd
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
id|signal_processor
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
comma
id|sigp_stop_and_store_status
)paren
suffix:semicolon
)brace
DECL|variable|_machine_restart
r_void
(paren
op_star
id|_machine_restart
)paren
(paren
r_char
op_star
id|command
)paren
op_assign
id|do_machine_restart_nonsmp
suffix:semicolon
DECL|variable|_machine_halt
r_void
(paren
op_star
id|_machine_halt
)paren
(paren
r_void
)paren
op_assign
id|do_machine_halt_nonsmp
suffix:semicolon
DECL|variable|_machine_power_off
r_void
(paren
op_star
id|_machine_power_off
)paren
(paren
r_void
)paren
op_assign
id|do_machine_power_off_nonsmp
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Reboot, halt and power_off stubs. They just call _machine_restart,&n; * _machine_halt or _machine_power_off. &n; */
DECL|function|machine_restart
r_void
id|machine_restart
c_func
(paren
r_char
op_star
id|command
)paren
(brace
id|console_unblank
c_func
(paren
)paren
suffix:semicolon
id|_machine_restart
c_func
(paren
id|command
)paren
suffix:semicolon
)brace
DECL|variable|machine_restart
id|EXPORT_SYMBOL
c_func
(paren
id|machine_restart
)paren
suffix:semicolon
DECL|function|machine_halt
r_void
id|machine_halt
c_func
(paren
r_void
)paren
(brace
id|console_unblank
c_func
(paren
)paren
suffix:semicolon
id|_machine_halt
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|variable|machine_halt
id|EXPORT_SYMBOL
c_func
(paren
id|machine_halt
)paren
suffix:semicolon
DECL|function|machine_power_off
r_void
id|machine_power_off
c_func
(paren
r_void
)paren
(brace
id|console_unblank
c_func
(paren
)paren
suffix:semicolon
id|_machine_power_off
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|variable|machine_power_off
id|EXPORT_SYMBOL
c_func
(paren
id|machine_power_off
)paren
suffix:semicolon
multiline_comment|/*&n; * Setup function called from init/main.c just after the banner&n; * was printed.&n; */
r_extern
r_char
id|_pstart
comma
id|_pend
comma
id|_stext
suffix:semicolon
DECL|function|setup_arch
r_void
id|__init
id|setup_arch
c_func
(paren
r_char
op_star
op_star
id|cmdline_p
)paren
(brace
r_int
r_int
id|bootmap_size
suffix:semicolon
r_int
r_int
id|memory_start
comma
id|memory_end
suffix:semicolon
r_char
id|c
op_assign
l_char|&squot; &squot;
comma
id|cn
comma
op_star
id|to
op_assign
id|command_line
comma
op_star
id|from
op_assign
id|COMMAND_LINE
suffix:semicolon
r_int
r_int
id|start_pfn
comma
id|end_pfn
suffix:semicolon
r_static
r_int
r_int
id|smptrap
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|delay
op_assign
l_int|0
suffix:semicolon
r_struct
id|_lowcore
op_star
id|lc
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|smptrap
)paren
r_return
suffix:semicolon
id|smptrap
op_assign
l_int|1
suffix:semicolon
multiline_comment|/*&n;         * print what head.S has found out about the machine &n;         */
macro_line|#ifndef CONFIG_ARCH_S390X
id|printk
c_func
(paren
(paren
id|MACHINE_IS_VM
)paren
ques
c_cond
l_string|&quot;We are running under VM (31 bit mode)&bslash;n&quot;
suffix:colon
l_string|&quot;We are running native (31 bit mode)&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
(paren
id|MACHINE_HAS_IEEE
)paren
ques
c_cond
l_string|&quot;This machine has an IEEE fpu&bslash;n&quot;
suffix:colon
l_string|&quot;This machine has no IEEE fpu&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#else /* CONFIG_ARCH_S390X */
id|printk
c_func
(paren
(paren
id|MACHINE_IS_VM
)paren
ques
c_cond
l_string|&quot;We are running under VM (64 bit mode)&bslash;n&quot;
suffix:colon
l_string|&quot;We are running native (64 bit mode)&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_ARCH_S390X */
id|ROOT_DEV
op_assign
id|Root_RAM0
suffix:semicolon
id|memory_start
op_assign
(paren
r_int
r_int
)paren
op_amp
id|_end
suffix:semicolon
multiline_comment|/* fixit if use $CODELO etc*/
macro_line|#ifndef CONFIG_ARCH_S390X
id|memory_end
op_assign
id|memory_size
op_amp
op_complement
l_int|0x400000UL
suffix:semicolon
multiline_comment|/* align memory end to 4MB */
multiline_comment|/*&n;         * We need some free virtual space to be able to do vmalloc.&n;         * On a machine with 2GB memory we make sure that we have at&n;         * least 128 MB free space for vmalloc.&n;         */
r_if
c_cond
(paren
id|memory_end
OG
l_int|1920
op_star
l_int|1024
op_star
l_int|1024
)paren
id|memory_end
op_assign
l_int|1920
op_star
l_int|1024
op_star
l_int|1024
suffix:semicolon
macro_line|#else /* CONFIG_ARCH_S390X */
id|memory_end
op_assign
id|memory_size
op_amp
op_complement
l_int|0x200000UL
suffix:semicolon
multiline_comment|/* detected in head.s */
macro_line|#endif /* CONFIG_ARCH_S390X */
id|init_mm.start_code
op_assign
id|PAGE_OFFSET
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
id|_end
suffix:semicolon
id|code_resource.start
op_assign
(paren
r_int
r_int
)paren
op_amp
id|_text
suffix:semicolon
id|code_resource.end
op_assign
(paren
r_int
r_int
)paren
op_amp
id|_etext
op_minus
l_int|1
suffix:semicolon
id|data_resource.start
op_assign
(paren
r_int
r_int
)paren
op_amp
id|_etext
suffix:semicolon
id|data_resource.end
op_assign
(paren
r_int
r_int
)paren
op_amp
id|_edata
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* Save unparsed command line copy for /proc/cmdline */
id|memcpy
c_func
(paren
id|saved_command_line
comma
id|COMMAND_LINE
comma
id|COMMAND_LINE_SIZE
)paren
suffix:semicolon
id|saved_command_line
(braket
id|COMMAND_LINE_SIZE
op_minus
l_int|1
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
multiline_comment|/*&n;                 * &quot;mem=XXX[kKmM]&quot; sets memsize &n;                 */
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot; &squot;
op_logical_and
id|strncmp
c_func
(paren
id|from
comma
l_string|&quot;mem=&quot;
comma
l_int|4
)paren
op_eq
l_int|0
)paren
(brace
id|memory_end
op_assign
id|simple_strtoul
c_func
(paren
id|from
op_plus
l_int|4
comma
op_amp
id|from
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|from
op_eq
l_char|&squot;K&squot;
op_logical_or
op_star
id|from
op_eq
l_char|&squot;k&squot;
)paren
(brace
id|memory_end
op_assign
id|memory_end
op_lshift
l_int|10
suffix:semicolon
id|from
op_increment
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_star
id|from
op_eq
l_char|&squot;M&squot;
op_logical_or
op_star
id|from
op_eq
l_char|&squot;m&squot;
)paren
(brace
id|memory_end
op_assign
id|memory_end
op_lshift
l_int|20
suffix:semicolon
id|from
op_increment
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;                 * &quot;ipldelay=XXX[sm]&quot; sets ipl delay in seconds or minutes&n;                 */
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot; &squot;
op_logical_and
id|strncmp
c_func
(paren
id|from
comma
l_string|&quot;ipldelay=&quot;
comma
l_int|9
)paren
op_eq
l_int|0
)paren
(brace
id|delay
op_assign
id|simple_strtoul
c_func
(paren
id|from
op_plus
l_int|9
comma
op_amp
id|from
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|from
op_eq
l_char|&squot;s&squot;
op_logical_or
op_star
id|from
op_eq
l_char|&squot;S&squot;
)paren
(brace
id|delay
op_assign
id|delay
op_star
l_int|1000000
suffix:semicolon
id|from
op_increment
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_star
id|from
op_eq
l_char|&squot;m&squot;
op_logical_or
op_star
id|from
op_eq
l_char|&squot;M&squot;
)paren
(brace
id|delay
op_assign
id|delay
op_star
l_int|60
op_star
l_int|1000000
suffix:semicolon
id|from
op_increment
suffix:semicolon
)brace
multiline_comment|/* now wait for the requested amount of time */
id|udelay
c_func
(paren
id|delay
)paren
suffix:semicolon
)brace
id|cn
op_assign
op_star
(paren
id|from
op_increment
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cn
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|cn
op_eq
l_char|&squot;&bslash;n&squot;
)paren
id|cn
op_assign
l_char|&squot; &squot;
suffix:semicolon
multiline_comment|/* replace newlines with space */
r_if
c_cond
(paren
id|cn
op_eq
l_int|0x0d
)paren
id|cn
op_assign
l_char|&squot; &squot;
suffix:semicolon
multiline_comment|/* replace 0x0d with space */
r_if
c_cond
(paren
id|cn
op_eq
l_char|&squot; &squot;
op_logical_and
id|c
op_eq
l_char|&squot; &squot;
)paren
r_continue
suffix:semicolon
multiline_comment|/* remove additional spaces */
id|c
op_assign
id|cn
suffix:semicolon
r_if
c_cond
(paren
id|to
op_minus
id|command_line
op_ge
id|COMMAND_LINE_SIZE
)paren
r_break
suffix:semicolon
op_star
(paren
id|to
op_increment
)paren
op_assign
id|c
suffix:semicolon
)brace
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot; &squot;
op_logical_and
id|to
OG
id|command_line
)paren
id|to
op_decrement
suffix:semicolon
op_star
id|to
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
op_star
id|cmdline_p
op_assign
id|command_line
suffix:semicolon
multiline_comment|/*&n;&t; * partially used pages are not usable - thus&n;&t; * we are rounding upwards:&n;&t; */
id|start_pfn
op_assign
(paren
id|__pa
c_func
(paren
op_amp
id|_end
)paren
op_plus
id|PAGE_SIZE
op_minus
l_int|1
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|end_pfn
op_assign
id|max_pfn
op_assign
id|memory_end
op_rshift
id|PAGE_SHIFT
suffix:semicolon
multiline_comment|/*&n;&t; * Initialize the boot-time allocator (with low memory only):&n;&t; */
id|bootmap_size
op_assign
id|init_bootmem
c_func
(paren
id|start_pfn
comma
id|end_pfn
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Register RAM areas with the bootmem allocator.&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
template_param
l_int|0
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
r_int
id|start_chunk
comma
id|end_chunk
suffix:semicolon
r_if
c_cond
(paren
id|memory_chunk
(braket
id|i
)braket
dot
id|type
op_ne
id|CHUNK_READ_WRITE
)paren
r_continue
suffix:semicolon
id|start_chunk
op_assign
(paren
id|memory_chunk
(braket
id|i
)braket
dot
id|addr
op_plus
id|PAGE_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
id|start_chunk
op_rshift_assign
id|PAGE_SHIFT
suffix:semicolon
id|end_chunk
op_assign
(paren
id|memory_chunk
(braket
id|i
)braket
dot
id|addr
op_plus
id|memory_chunk
(braket
id|i
)braket
dot
id|size
)paren
suffix:semicolon
id|end_chunk
op_rshift_assign
id|PAGE_SHIFT
suffix:semicolon
r_if
c_cond
(paren
id|start_chunk
OL
id|start_pfn
)paren
id|start_chunk
op_assign
id|start_pfn
suffix:semicolon
r_if
c_cond
(paren
id|end_chunk
OG
id|end_pfn
)paren
id|end_chunk
op_assign
id|end_pfn
suffix:semicolon
r_if
c_cond
(paren
id|start_chunk
OL
id|end_chunk
)paren
id|free_bootmem
c_func
(paren
id|start_chunk
op_lshift
id|PAGE_SHIFT
comma
(paren
id|end_chunk
op_minus
id|start_chunk
)paren
op_lshift
id|PAGE_SHIFT
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;         * Reserve the bootmem bitmap itself as well. We do this in two&n;         * steps (first step was init_bootmem()) because this catches&n;         * the (very unlikely) case of us accidentally initializing the&n;         * bootmem allocator with an invalid RAM area.&n;         */
id|reserve_bootmem
c_func
(paren
id|start_pfn
op_lshift
id|PAGE_SHIFT
comma
id|bootmap_size
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
r_if
c_cond
(paren
id|INITRD_START
)paren
(brace
r_if
c_cond
(paren
id|INITRD_START
op_plus
id|INITRD_SIZE
op_le
id|memory_end
)paren
(brace
id|reserve_bootmem
c_func
(paren
id|INITRD_START
comma
id|INITRD_SIZE
)paren
suffix:semicolon
id|initrd_start
op_assign
id|INITRD_START
suffix:semicolon
id|initrd_end
op_assign
id|initrd_start
op_plus
id|INITRD_SIZE
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;initrd extends beyond end of memory &quot;
l_string|&quot;(0x%08lx &gt; 0x%08lx)&bslash;ndisabling initrd&bslash;n&quot;
comma
id|initrd_start
op_plus
id|INITRD_SIZE
comma
id|memory_end
)paren
suffix:semicolon
id|initrd_start
op_assign
id|initrd_end
op_assign
l_int|0
suffix:semicolon
)brace
)brace
macro_line|#endif
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
template_param
l_int|0
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|resource
op_star
id|res
suffix:semicolon
id|res
op_assign
id|alloc_bootmem_low
c_func
(paren
r_sizeof
(paren
r_struct
id|resource
)paren
)paren
suffix:semicolon
id|res-&gt;flags
op_assign
id|IORESOURCE_BUSY
op_or
id|IORESOURCE_MEM
suffix:semicolon
r_switch
c_cond
(paren
id|memory_chunk
(braket
id|i
)braket
dot
id|type
)paren
(brace
r_case
id|CHUNK_READ_WRITE
suffix:colon
id|res-&gt;name
op_assign
l_string|&quot;System RAM&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CHUNK_READ_ONLY
suffix:colon
id|res-&gt;name
op_assign
l_string|&quot;System ROM&quot;
suffix:semicolon
id|res-&gt;flags
op_or_assign
id|IORESOURCE_READONLY
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|res-&gt;name
op_assign
l_string|&quot;reserved&quot;
suffix:semicolon
)brace
id|res-&gt;start
op_assign
id|memory_chunk
(braket
id|i
)braket
dot
id|addr
suffix:semicolon
id|res-&gt;end
op_assign
id|memory_chunk
(braket
id|i
)braket
dot
id|addr
op_plus
id|memory_chunk
(braket
id|i
)braket
dot
id|size
op_minus
l_int|1
suffix:semicolon
id|request_resource
c_func
(paren
op_amp
id|iomem_resource
comma
id|res
)paren
suffix:semicolon
id|request_resource
c_func
(paren
id|res
comma
op_amp
id|code_resource
)paren
suffix:semicolon
id|request_resource
c_func
(paren
id|res
comma
op_amp
id|data_resource
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;         * Setup lowcore for boot cpu&n;         */
macro_line|#ifndef CONFIG_ARCH_S390X
id|lc
op_assign
(paren
r_struct
id|_lowcore
op_star
)paren
id|__alloc_bootmem
c_func
(paren
id|PAGE_SIZE
comma
id|PAGE_SIZE
comma
l_int|0
)paren
suffix:semicolon
id|memset
c_func
(paren
id|lc
comma
l_int|0
comma
id|PAGE_SIZE
)paren
suffix:semicolon
macro_line|#else /* CONFIG_ARCH_S390X */
id|lc
op_assign
(paren
r_struct
id|_lowcore
op_star
)paren
id|__alloc_bootmem
c_func
(paren
l_int|2
op_star
id|PAGE_SIZE
comma
l_int|2
op_star
id|PAGE_SIZE
comma
l_int|0
)paren
suffix:semicolon
id|memset
c_func
(paren
id|lc
comma
l_int|0
comma
l_int|2
op_star
id|PAGE_SIZE
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_ARCH_S390X */
id|lc-&gt;restart_psw.mask
op_assign
id|PSW_BASE_BITS
suffix:semicolon
id|lc-&gt;restart_psw.addr
op_assign
id|PSW_ADDR_AMODE
op_or
(paren
r_int
r_int
)paren
id|restart_int_handler
suffix:semicolon
id|lc-&gt;external_new_psw.mask
op_assign
id|PSW_KERNEL_BITS
suffix:semicolon
id|lc-&gt;external_new_psw.addr
op_assign
id|PSW_ADDR_AMODE
op_or
(paren
r_int
r_int
)paren
id|ext_int_handler
suffix:semicolon
id|lc-&gt;svc_new_psw.mask
op_assign
id|PSW_KERNEL_BITS
op_or
id|PSW_MASK_IO
op_or
id|PSW_MASK_EXT
suffix:semicolon
id|lc-&gt;svc_new_psw.addr
op_assign
id|PSW_ADDR_AMODE
op_or
(paren
r_int
r_int
)paren
id|system_call
suffix:semicolon
id|lc-&gt;program_new_psw.mask
op_assign
id|PSW_KERNEL_BITS
suffix:semicolon
id|lc-&gt;program_new_psw.addr
op_assign
id|PSW_ADDR_AMODE
op_or
(paren
r_int
r_int
)paren
id|pgm_check_handler
suffix:semicolon
id|lc-&gt;mcck_new_psw.mask
op_assign
id|PSW_KERNEL_BITS
suffix:semicolon
id|lc-&gt;mcck_new_psw.addr
op_assign
id|PSW_ADDR_AMODE
op_or
(paren
r_int
r_int
)paren
id|mcck_int_handler
suffix:semicolon
id|lc-&gt;io_new_psw.mask
op_assign
id|PSW_KERNEL_BITS
suffix:semicolon
id|lc-&gt;io_new_psw.addr
op_assign
id|PSW_ADDR_AMODE
op_or
(paren
r_int
r_int
)paren
id|io_int_handler
suffix:semicolon
id|lc-&gt;ipl_device
op_assign
id|S390_lowcore.ipl_device
suffix:semicolon
id|lc-&gt;jiffy_timer
op_assign
op_minus
l_int|1LL
suffix:semicolon
id|lc-&gt;kernel_stack
op_assign
(paren
(paren
r_int
r_int
)paren
op_amp
id|init_thread_union
)paren
op_plus
id|THREAD_SIZE
suffix:semicolon
id|lc-&gt;async_stack
op_assign
(paren
r_int
r_int
)paren
id|__alloc_bootmem
c_func
(paren
id|ASYNC_SIZE
comma
id|ASYNC_SIZE
comma
l_int|0
)paren
op_plus
id|ASYNC_SIZE
suffix:semicolon
macro_line|#ifdef CONFIG_CHECK_STACK
id|lc-&gt;panic_stack
op_assign
(paren
r_int
r_int
)paren
id|__alloc_bootmem
c_func
(paren
id|PAGE_SIZE
comma
id|PAGE_SIZE
comma
l_int|0
)paren
op_plus
id|PAGE_SIZE
suffix:semicolon
macro_line|#endif
id|lc-&gt;current_task
op_assign
(paren
r_int
r_int
)paren
id|init_thread_union.thread_info.task
suffix:semicolon
id|lc-&gt;thread_info
op_assign
(paren
r_int
r_int
)paren
op_amp
id|init_thread_union
suffix:semicolon
macro_line|#ifdef CONFIG_ARCH_S390X
r_if
c_cond
(paren
id|MACHINE_HAS_DIAG44
)paren
id|lc-&gt;diag44_opcode
op_assign
l_int|0x83000044
suffix:semicolon
r_else
id|lc-&gt;diag44_opcode
op_assign
l_int|0x07000700
suffix:semicolon
macro_line|#endif /* CONFIG_ARCH_S390X */
id|set_prefix
c_func
(paren
(paren
id|u32
)paren
(paren
r_int
r_int
)paren
id|lc
)paren
suffix:semicolon
id|cpu_init
c_func
(paren
)paren
suffix:semicolon
id|__cpu_logical_map
(braket
l_int|0
)braket
op_assign
id|S390_lowcore.cpu_data.cpu_addr
suffix:semicolon
multiline_comment|/*&n;&t; * Create kernel page tables and switch to virtual addressing.&n;&t; */
id|paging_init
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Setup default console */
id|conmode_default
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|print_cpu_info
r_void
id|print_cpu_info
c_func
(paren
r_struct
id|cpuinfo_S390
op_star
id|cpuinfo
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;cpu %d &quot;
macro_line|#ifdef CONFIG_SMP
l_string|&quot;phys_idx=%d &quot;
macro_line|#endif
l_string|&quot;vers=%02X ident=%06X machine=%04X unused=%04X&bslash;n&quot;
comma
id|cpuinfo-&gt;cpu_nr
comma
macro_line|#ifdef CONFIG_SMP
id|cpuinfo-&gt;cpu_addr
comma
macro_line|#endif
id|cpuinfo-&gt;cpu_id.version
comma
id|cpuinfo-&gt;cpu_id.ident
comma
id|cpuinfo-&gt;cpu_id.machine
comma
id|cpuinfo-&gt;cpu_id.unused
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * show_cpuinfo - Get information on one CPU for use by procfs.&n; */
DECL|function|show_cpuinfo
r_static
r_int
id|show_cpuinfo
c_func
(paren
r_struct
id|seq_file
op_star
id|m
comma
r_void
op_star
id|v
)paren
(brace
r_struct
id|cpuinfo_S390
op_star
id|cpuinfo
suffix:semicolon
r_int
r_int
id|n
op_assign
(paren
r_int
r_int
)paren
id|v
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|n
)paren
(brace
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;vendor_id       : IBM/S390&bslash;n&quot;
l_string|&quot;# processors    : %i&bslash;n&quot;
l_string|&quot;bogomips per cpu: %lu.%02lu&bslash;n&quot;
comma
id|num_online_cpus
c_func
(paren
)paren
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
r_if
c_cond
(paren
id|cpu_online
c_func
(paren
id|n
)paren
)paren
(brace
macro_line|#ifdef CONFIG_SMP
r_if
c_cond
(paren
id|smp_processor_id
c_func
(paren
)paren
op_eq
id|n
)paren
id|cpuinfo
op_assign
op_amp
id|S390_lowcore.cpu_data
suffix:semicolon
r_else
id|cpuinfo
op_assign
op_amp
id|lowcore_ptr
(braket
id|n
)braket
op_member_access_from_pointer
id|cpu_data
suffix:semicolon
macro_line|#else
id|cpuinfo
op_assign
op_amp
id|S390_lowcore.cpu_data
suffix:semicolon
macro_line|#endif
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;processor %li: &quot;
l_string|&quot;version = %02X,  &quot;
l_string|&quot;identification = %06X,  &quot;
l_string|&quot;machine = %04X&bslash;n&quot;
comma
id|n
comma
id|cpuinfo-&gt;cpu_id.version
comma
id|cpuinfo-&gt;cpu_id.ident
comma
id|cpuinfo-&gt;cpu_id.machine
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|c_start
r_static
r_void
op_star
id|c_start
c_func
(paren
r_struct
id|seq_file
op_star
id|m
comma
id|loff_t
op_star
id|pos
)paren
(brace
r_return
op_star
id|pos
OL
id|NR_CPUS
ques
c_cond
(paren
r_void
op_star
)paren
(paren
(paren
r_int
r_int
)paren
op_star
id|pos
op_plus
l_int|1
)paren
suffix:colon
l_int|NULL
suffix:semicolon
)brace
DECL|function|c_next
r_static
r_void
op_star
id|c_next
c_func
(paren
r_struct
id|seq_file
op_star
id|m
comma
r_void
op_star
id|v
comma
id|loff_t
op_star
id|pos
)paren
(brace
op_increment
op_star
id|pos
suffix:semicolon
r_return
id|c_start
c_func
(paren
id|m
comma
id|pos
)paren
suffix:semicolon
)brace
DECL|function|c_stop
r_static
r_void
id|c_stop
c_func
(paren
r_struct
id|seq_file
op_star
id|m
comma
r_void
op_star
id|v
)paren
(brace
)brace
DECL|variable|cpuinfo_op
r_struct
id|seq_operations
id|cpuinfo_op
op_assign
(brace
dot
id|start
op_assign
id|c_start
comma
dot
id|next
op_assign
id|c_next
comma
dot
id|stop
op_assign
id|c_stop
comma
dot
id|show
op_assign
id|show_cpuinfo
comma
)brace
suffix:semicolon
eof
