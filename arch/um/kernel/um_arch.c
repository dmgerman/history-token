multiline_comment|/* &n; * Copyright (C) 2000, 2002 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#include &quot;linux/config.h&quot;
macro_line|#include &quot;linux/kernel.h&quot;
macro_line|#include &quot;linux/sched.h&quot;
macro_line|#include &quot;linux/notifier.h&quot;
macro_line|#include &quot;linux/mm.h&quot;
macro_line|#include &quot;linux/types.h&quot;
macro_line|#include &quot;linux/tty.h&quot;
macro_line|#include &quot;linux/init.h&quot;
macro_line|#include &quot;linux/bootmem.h&quot;
macro_line|#include &quot;linux/spinlock.h&quot;
macro_line|#include &quot;linux/utsname.h&quot;
macro_line|#include &quot;linux/sysrq.h&quot;
macro_line|#include &quot;linux/seq_file.h&quot;
macro_line|#include &quot;linux/delay.h&quot;
macro_line|#include &quot;asm/page.h&quot;
macro_line|#include &quot;asm/pgtable.h&quot;
macro_line|#include &quot;asm/ptrace.h&quot;
macro_line|#include &quot;asm/elf.h&quot;
macro_line|#include &quot;asm/user.h&quot;
macro_line|#include &quot;ubd_user.h&quot;
macro_line|#include &quot;asm/current.h&quot;
macro_line|#include &quot;user_util.h&quot;
macro_line|#include &quot;kern_util.h&quot;
macro_line|#include &quot;kern.h&quot;
macro_line|#include &quot;mprot.h&quot;
macro_line|#include &quot;mem_user.h&quot;
macro_line|#include &quot;mem.h&quot;
macro_line|#include &quot;umid.h&quot;
macro_line|#include &quot;initrd.h&quot;
macro_line|#include &quot;init.h&quot;
macro_line|#include &quot;os.h&quot;
macro_line|#include &quot;choose-mode.h&quot;
macro_line|#include &quot;mode_kern.h&quot;
macro_line|#include &quot;mode.h&quot;
DECL|macro|DEFAULT_COMMAND_LINE
mdefine_line|#define DEFAULT_COMMAND_LINE &quot;root=6200&quot;
DECL|variable|boot_cpu_data
r_struct
id|cpuinfo_um
id|boot_cpu_data
op_assign
(brace
dot
id|loops_per_jiffy
op_assign
l_int|0
comma
dot
id|ipi_pipe
op_assign
(brace
op_minus
l_int|1
comma
op_minus
l_int|1
)brace
)brace
suffix:semicolon
DECL|function|thread_saved_pc
r_int
r_int
id|thread_saved_pc
c_func
(paren
r_struct
id|task_struct
op_star
id|task
)paren
(brace
r_return
id|os_process_pc
c_func
(paren
id|CHOOSE_MODE_PROC
c_func
(paren
id|thread_pid_tt
comma
id|thread_pid_skas
comma
id|thread
)paren
)paren
suffix:semicolon
)brace
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
r_int
id|index
suffix:semicolon
id|index
op_assign
(paren
r_struct
id|cpuinfo_um
op_star
)paren
id|v
op_minus
id|cpu_data
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
r_if
c_cond
(paren
op_logical_neg
(paren
id|cpu_online_map
op_amp
(paren
l_int|1
op_lshift
id|index
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
macro_line|#endif
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;bogomips&bslash;t: %lu.%02lu&bslash;n&quot;
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
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;host&bslash;t&bslash;t: %s&bslash;n&quot;
comma
id|host_info
)paren
suffix:semicolon
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
id|cpu_data
op_plus
op_star
id|pos
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
id|start
suffix:colon
id|c_start
comma
id|next
suffix:colon
id|c_next
comma
id|stop
suffix:colon
id|c_stop
comma
id|show
suffix:colon
id|show_cpuinfo
comma
)brace
suffix:semicolon
DECL|function|__bad_pagetable
id|pte_t
op_star
id|__bad_pagetable
c_func
(paren
r_void
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;Someone should implement __bad_pagetable&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* Set in linux_main */
DECL|variable|host_task_size
r_int
r_int
id|host_task_size
suffix:semicolon
DECL|variable|task_size
r_int
r_int
id|task_size
suffix:semicolon
DECL|variable|uml_start
r_int
r_int
id|uml_start
suffix:semicolon
multiline_comment|/* Set in early boot */
DECL|variable|uml_physmem
r_int
r_int
id|uml_physmem
suffix:semicolon
DECL|variable|uml_reserved
r_int
r_int
id|uml_reserved
suffix:semicolon
DECL|variable|start_vm
r_int
r_int
id|start_vm
suffix:semicolon
DECL|variable|end_vm
r_int
r_int
id|end_vm
suffix:semicolon
DECL|variable|ncpus
r_int
id|ncpus
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Pointer set in linux_main, the array itself is private to each thread,&n; * and changed at address space creation time so this poses no concurrency&n; * problems.&n; */
DECL|variable|argv1_begin
r_static
r_char
op_star
id|argv1_begin
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|argv1_end
r_static
r_char
op_star
id|argv1_end
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* Set in early boot */
DECL|variable|__initdata
r_static
r_int
id|have_root
id|__initdata
op_assign
l_int|0
suffix:semicolon
DECL|variable|physmem_size
r_int
id|physmem_size
op_assign
l_int|32
op_star
l_int|1024
op_star
l_int|1024
suffix:semicolon
DECL|function|set_cmdline
r_void
id|set_cmdline
c_func
(paren
r_char
op_star
id|cmd
)paren
(brace
r_char
op_star
id|umid
comma
op_star
id|ptr
suffix:semicolon
r_if
c_cond
(paren
id|CHOOSE_MODE
c_func
(paren
id|honeypot
comma
l_int|0
)paren
)paren
(brace
r_return
suffix:semicolon
)brace
id|umid
op_assign
id|get_umid
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|umid
op_ne
l_int|NULL
)paren
(brace
id|snprintf
c_func
(paren
id|argv1_begin
comma
(paren
id|argv1_end
op_minus
id|argv1_begin
)paren
op_star
r_sizeof
(paren
op_star
id|ptr
)paren
comma
l_string|&quot;(%s)&quot;
comma
id|umid
)paren
suffix:semicolon
id|ptr
op_assign
op_amp
id|argv1_begin
(braket
id|strlen
c_func
(paren
id|argv1_begin
)paren
)braket
suffix:semicolon
)brace
r_else
id|ptr
op_assign
id|argv1_begin
suffix:semicolon
id|snprintf
c_func
(paren
id|ptr
comma
(paren
id|argv1_end
op_minus
id|ptr
)paren
op_star
r_sizeof
(paren
op_star
id|ptr
)paren
comma
l_string|&quot; [%s]&quot;
comma
id|cmd
)paren
suffix:semicolon
id|memset
c_func
(paren
id|argv1_begin
op_plus
id|strlen
c_func
(paren
id|argv1_begin
)paren
comma
l_char|&squot;&bslash;0&squot;
comma
id|argv1_end
op_minus
id|argv1_begin
op_minus
id|strlen
c_func
(paren
id|argv1_begin
)paren
)paren
suffix:semicolon
)brace
DECL|variable|usage_string
r_static
r_char
op_star
id|usage_string
op_assign
l_string|&quot;User Mode Linux v%s&bslash;n&quot;
l_string|&quot;&t;available at http://user-mode-linux.sourceforge.net/&bslash;n&bslash;n&quot;
suffix:semicolon
DECL|function|uml_version_setup
r_static
r_int
id|__init
id|uml_version_setup
c_func
(paren
r_char
op_star
id|line
comma
r_int
op_star
id|add
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|system_utsname.release
)paren
suffix:semicolon
m_exit
(paren
l_int|0
)paren
suffix:semicolon
)brace
id|__uml_setup
c_func
(paren
l_string|&quot;--version&quot;
comma
id|uml_version_setup
comma
l_string|&quot;--version&bslash;n&quot;
l_string|&quot;    Prints the version number of the kernel.&bslash;n&bslash;n&quot;
)paren
suffix:semicolon
DECL|function|uml_root_setup
r_static
r_int
id|__init
id|uml_root_setup
c_func
(paren
r_char
op_star
id|line
comma
r_int
op_star
id|add
)paren
(brace
id|have_root
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|__uml_setup
c_func
(paren
l_string|&quot;root=&quot;
comma
id|uml_root_setup
comma
l_string|&quot;root=&lt;file containing the root fs&gt;&bslash;n&quot;
l_string|&quot;    This is actually used by the generic kernel in exactly the same&bslash;n&quot;
l_string|&quot;    way as in any other kernel. If you configure a number of block&bslash;n&quot;
l_string|&quot;    devices and want to boot off something other than ubd0, you &bslash;n&quot;
l_string|&quot;    would use something like:&bslash;n&quot;
l_string|&quot;        root=/dev/ubd5&bslash;n&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
DECL|function|uml_ncpus_setup
r_static
r_int
id|__init
id|uml_ncpus_setup
c_func
(paren
r_char
op_star
id|line
comma
r_int
op_star
id|add
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|sscanf
c_func
(paren
id|line
comma
l_string|&quot;%d&quot;
comma
op_amp
id|ncpus
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Couldn&squot;t parse [%s]&bslash;n&quot;
comma
id|line
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
id|__uml_setup
c_func
(paren
l_string|&quot;ncpus=&quot;
comma
id|uml_ncpus_setup
comma
l_string|&quot;ncpus=&lt;# of desired CPUs&gt;&bslash;n&quot;
l_string|&quot;    This tells an SMP kernel how many virtual processors to start.&bslash;n&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
DECL|variable|force_tt
r_int
id|force_tt
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
id|defined
c_func
(paren
id|CONFIG_MODE_TT
)paren
op_logical_and
id|defined
c_func
(paren
id|CONFIG_MODE_SKAS
)paren
op_plus
mdefine_line|#define DEFAULT_TT 0
DECL|function|mode_tt_setup
r_static
r_int
id|__init
id|mode_tt_setup
c_func
(paren
r_char
op_star
id|line
comma
r_int
op_star
id|add
)paren
(brace
id|force_tt
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|__uml_setup
c_func
(paren
l_string|&quot;mode=tt&quot;
comma
id|mode_tt_setup
comma
l_string|&quot;mode=tt&bslash;n&quot;
l_string|&quot;    When both CONFIG_MODE_TT and CONFIG_MODE_SKAS are enabled, this option&bslash;n&quot;
l_string|&quot;    forces UML to run in tt (tracing thread) mode.  It is not the default&bslash;n&quot;
l_string|&quot;    because it&squot;s slower and less secure than skas mode.&bslash;n&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#else
macro_line|#ifdef CONFIG_MODE_SKAS
DECL|macro|DEFAULT_TT
mdefine_line|#define DEFAULT_TT 0
macro_line|#else
macro_line|#ifdef CONFIG_MODE_TT
DECL|macro|DEFAULT_TT
mdefine_line|#define DEFAULT_TT 1
macro_line|#else
macro_line|#error Either CONFIG_MODE_TT or CONFIG_MODE_SKAS must be enabled
macro_line|#endif
macro_line|#endif
macro_line|#endif
DECL|variable|mode_tt
r_int
id|mode_tt
op_assign
id|DEFAULT_TT
suffix:semicolon
DECL|function|Usage
r_static
r_int
id|__init
id|Usage
c_func
(paren
r_char
op_star
id|line
comma
r_int
op_star
id|add
)paren
(brace
r_const
r_char
op_star
op_star
id|p
suffix:semicolon
id|printf
c_func
(paren
id|usage_string
comma
id|system_utsname.release
)paren
suffix:semicolon
id|p
op_assign
op_amp
id|__uml_help_start
suffix:semicolon
r_while
c_loop
(paren
id|p
OL
op_amp
id|__uml_help_end
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;%s&quot;
comma
op_star
id|p
)paren
suffix:semicolon
id|p
op_increment
suffix:semicolon
)brace
m_exit
(paren
l_int|0
)paren
suffix:semicolon
)brace
id|__uml_setup
c_func
(paren
l_string|&quot;--help&quot;
comma
id|Usage
comma
l_string|&quot;--help&bslash;n&quot;
l_string|&quot;    Prints this message.&bslash;n&bslash;n&quot;
)paren
suffix:semicolon
DECL|function|uml_checksetup
r_static
r_int
id|__init
id|uml_checksetup
c_func
(paren
r_char
op_star
id|line
comma
r_int
op_star
id|add
)paren
(brace
r_struct
id|uml_param
op_star
id|p
suffix:semicolon
id|p
op_assign
op_amp
id|__uml_setup_start
suffix:semicolon
r_while
c_loop
(paren
id|p
OL
op_amp
id|__uml_setup_end
)paren
(brace
r_int
id|n
suffix:semicolon
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
comma
id|add
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
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|uml_postsetup
r_static
r_void
id|__init
id|uml_postsetup
c_func
(paren
r_void
)paren
(brace
id|initcall_t
op_star
id|p
suffix:semicolon
id|p
op_assign
op_amp
id|__uml_postsetup_start
suffix:semicolon
r_while
c_loop
(paren
id|p
OL
op_amp
id|__uml_postsetup_end
)paren
(brace
(paren
op_star
id|p
)paren
(paren
)paren
suffix:semicolon
id|p
op_increment
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
multiline_comment|/* Set during early boot */
DECL|variable|brk_start
r_int
r_int
id|brk_start
suffix:semicolon
DECL|variable|kernel_vm_reserved
r_static
r_struct
id|vm_reserved
id|kernel_vm_reserved
suffix:semicolon
DECL|macro|MIN_VMALLOC
mdefine_line|#define MIN_VMALLOC (32 * 1024 * 1024)
DECL|function|linux_main
r_int
id|linux_main
c_func
(paren
r_int
id|argc
comma
r_char
op_star
op_star
id|argv
)paren
(brace
r_int
r_int
id|avail
suffix:semicolon
r_int
r_int
id|virtmem_size
comma
id|max_physmem
suffix:semicolon
r_int
r_int
id|i
comma
id|add
comma
id|err
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
id|argc
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
id|i
op_eq
l_int|1
)paren
op_logical_and
(paren
id|argv
(braket
id|i
)braket
(braket
l_int|0
)braket
op_eq
l_char|&squot; &squot;
)paren
)paren
(brace
r_continue
suffix:semicolon
)brace
id|add
op_assign
l_int|1
suffix:semicolon
id|uml_checksetup
c_func
(paren
id|argv
(braket
id|i
)braket
comma
op_amp
id|add
)paren
suffix:semicolon
r_if
c_cond
(paren
id|add
)paren
(brace
id|add_arg
c_func
(paren
id|saved_command_line
comma
id|argv
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|have_root
op_eq
l_int|0
)paren
(brace
id|add_arg
c_func
(paren
id|saved_command_line
comma
id|DEFAULT_COMMAND_LINE
)paren
suffix:semicolon
)brace
id|mode_tt
op_assign
id|force_tt
ques
c_cond
l_int|1
suffix:colon
op_logical_neg
id|can_do_skas
c_func
(paren
)paren
suffix:semicolon
id|uml_start
op_assign
id|CHOOSE_MODE_PROC
c_func
(paren
id|set_task_sizes_tt
comma
id|set_task_sizes_skas
comma
l_int|0
comma
op_amp
id|host_task_size
comma
op_amp
id|task_size
)paren
suffix:semicolon
id|brk_start
op_assign
(paren
r_int
r_int
)paren
id|sbrk
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|CHOOSE_MODE_PROC
c_func
(paren
id|before_mem_tt
comma
id|before_mem_skas
comma
id|brk_start
)paren
suffix:semicolon
id|uml_physmem
op_assign
id|uml_start
suffix:semicolon
multiline_comment|/* Reserve up to 4M after the current brk */
id|uml_reserved
op_assign
id|ROUND_4M
c_func
(paren
id|brk_start
)paren
op_plus
(paren
l_int|1
op_lshift
l_int|22
)paren
suffix:semicolon
id|setup_machinename
c_func
(paren
id|system_utsname.machine
)paren
suffix:semicolon
id|argv1_begin
op_assign
id|argv
(braket
l_int|1
)braket
suffix:semicolon
id|argv1_end
op_assign
op_amp
id|argv
(braket
l_int|1
)braket
(braket
id|strlen
c_func
(paren
id|argv
(braket
l_int|1
)braket
)paren
)braket
suffix:semicolon
id|set_usable_vm
c_func
(paren
id|uml_physmem
comma
id|get_kmem_end
c_func
(paren
)paren
)paren
suffix:semicolon
id|highmem
op_assign
l_int|0
suffix:semicolon
id|max_physmem
op_assign
id|get_kmem_end
c_func
(paren
)paren
op_minus
id|uml_physmem
op_minus
id|MIN_VMALLOC
suffix:semicolon
r_if
c_cond
(paren
id|physmem_size
OG
id|max_physmem
)paren
(brace
id|highmem
op_assign
id|physmem_size
op_minus
id|max_physmem
suffix:semicolon
id|physmem_size
op_sub_assign
id|highmem
suffix:semicolon
)brace
id|high_physmem
op_assign
id|uml_physmem
op_plus
id|physmem_size
suffix:semicolon
id|high_memory
op_assign
(paren
r_void
op_star
)paren
id|high_physmem
suffix:semicolon
id|start_vm
op_assign
id|VMALLOC_START
suffix:semicolon
id|setup_physmem
c_func
(paren
id|uml_physmem
comma
id|uml_reserved
comma
id|physmem_size
)paren
suffix:semicolon
id|virtmem_size
op_assign
id|physmem_size
suffix:semicolon
id|avail
op_assign
id|get_kmem_end
c_func
(paren
)paren
op_minus
id|start_vm
suffix:semicolon
r_if
c_cond
(paren
id|physmem_size
OG
id|avail
)paren
(brace
id|virtmem_size
op_assign
id|avail
suffix:semicolon
)brace
id|end_vm
op_assign
id|start_vm
op_plus
id|virtmem_size
suffix:semicolon
r_if
c_cond
(paren
id|virtmem_size
OL
id|physmem_size
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;Kernel virtual memory size shrunk to %ld bytes&bslash;n&quot;
comma
id|virtmem_size
)paren
suffix:semicolon
)brace
id|err
op_assign
id|reserve_vm
c_func
(paren
id|high_physmem
comma
id|end_vm
comma
op_amp
id|kernel_vm_reserved
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;Failed to reserve VM area for kernel VM&bslash;n&quot;
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
id|uml_postsetup
c_func
(paren
)paren
suffix:semicolon
id|init_task.thread.kernel_stack
op_assign
(paren
r_int
r_int
)paren
op_amp
id|init_thread_info
op_plus
l_int|2
op_star
id|PAGE_SIZE
suffix:semicolon
id|task_protections
c_func
(paren
(paren
r_int
r_int
)paren
op_amp
id|init_thread_info
)paren
suffix:semicolon
r_return
id|CHOOSE_MODE
c_func
(paren
id|start_uml_tt
c_func
(paren
)paren
comma
id|start_uml_skas
c_func
(paren
)paren
)paren
suffix:semicolon
)brace
DECL|function|panic_exit
r_static
r_int
id|panic_exit
c_func
(paren
r_struct
id|notifier_block
op_star
id|self
comma
r_int
r_int
id|unused1
comma
r_void
op_star
id|unused2
)paren
(brace
macro_line|#ifdef CONFIG_SYSRQ
id|handle_sysrq
c_func
(paren
l_char|&squot;p&squot;
comma
op_amp
id|current-&gt;thread.regs
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
macro_line|#endif
id|machine_halt
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|panic_exit_notifier
r_static
r_struct
id|notifier_block
id|panic_exit_notifier
op_assign
(brace
id|notifier_call
suffix:colon
id|panic_exit
comma
id|next
suffix:colon
l_int|NULL
comma
id|priority
suffix:colon
l_int|0
)brace
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
id|notifier_chain_register
c_func
(paren
op_amp
id|panic_notifier_list
comma
op_amp
id|panic_exit_notifier
)paren
suffix:semicolon
id|paging_init
c_func
(paren
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|command_line
comma
id|saved_command_line
)paren
suffix:semicolon
op_star
id|cmdline_p
op_assign
id|command_line
suffix:semicolon
id|setup_hostinfo
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|check_bugs
r_void
id|__init
id|check_bugs
c_func
(paren
r_void
)paren
(brace
id|arch_check_bugs
c_func
(paren
)paren
suffix:semicolon
id|check_ptrace
c_func
(paren
)paren
suffix:semicolon
id|check_sigio
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
