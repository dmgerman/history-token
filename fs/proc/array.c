multiline_comment|/*&n; *  linux/fs/proc/array.c&n; *&n; *  Copyright (C) 1992  by Linus Torvalds&n; *  based on ideas by Darren Senn&n; *&n; * Fixes:&n; * Michael. K. Johnson: stat,statm extensions.&n; *                      &lt;johnsonm@stolaf.edu&gt;&n; *&n; * Pauline Middelink :  Made cmdline,envline only break at &squot;&bslash;0&squot;s, to&n; *                      make sure SET_PROCTITLE works. Also removed&n; *                      bad &squot;!&squot; which forced address recalculation for&n; *                      EVERY character on the current page.&n; *                      &lt;middelin@polyware.iaf.nl&gt;&n; *&n; * Danny ter Haar    :&t;added cpuinfo&n; *&t;&t;&t;&lt;dth@cistron.nl&gt;&n; *&n; * Alessandro Rubini :  profile extension.&n; *                      &lt;rubini@ipvvis.unipv.it&gt;&n; *&n; * Jeff Tranter      :  added BogoMips field to cpuinfo&n; *                      &lt;Jeff_Tranter@Mitel.COM&gt;&n; *&n; * Bruno Haible      :  remove 4K limit for the maps file&n; *&t;&t;&t;&lt;haible@ma2s2.mathematik.uni-karlsruhe.de&gt;&n; *&n; * Yves Arrouye      :  remove removal of trailing spaces in get_array.&n; *&t;&t;&t;&lt;Yves.Arrouye@marin.fdn.fr&gt;&n; *&n; * Jerome Forissier  :  added per-CPU time information to /proc/stat&n; *                      and /proc/&lt;pid&gt;/cpu extension&n; *                      &lt;forissier@isia.cma.fr&gt;&n; *&t;&t;&t;- Incorporation and non-SMP safe operation&n; *&t;&t;&t;of forissier patch in 2.1.78 by&n; *&t;&t;&t;Hans Marcus &lt;crowbar@concepts.nl&gt;&n; *&n; * aeb@cwi.nl        :  /proc/partitions&n; *&n; *&n; * Alan Cox&t;     :  security fixes.&n; *&t;&t;&t;&lt;Alan.Cox@linux.org&gt;&n; *&n; * Al Viro           :  safe handling of mm_struct&n; *&n; * Gerhard Wichert   :  added BIGMEM support&n; * Siemens AG           &lt;Gerhard.Wichert@pdb.siemens.de&gt;&n; *&n; * Al Viro &amp; Jeff Garzik :  moved most of the thing into base.c and&n; *&t;&t;&t; :  proc_misc.c. The rest may eventually go into&n; *&t;&t;&t; :  base.c too.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mman.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/swap.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/highmem.h&gt;
macro_line|#include &lt;linux/file.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
multiline_comment|/* Gcc optimizes away &quot;strlen(x)&quot; for constant x */
DECL|macro|ADDBUF
mdefine_line|#define ADDBUF(buffer, string) &bslash;&n;do { memcpy(buffer, string, strlen(string)); &bslash;&n;     buffer += strlen(string); } while (0)
DECL|function|task_name
r_static
r_inline
r_char
op_star
id|task_name
c_func
(paren
r_struct
id|task_struct
op_star
id|p
comma
r_char
op_star
id|buf
)paren
(brace
r_int
id|i
suffix:semicolon
r_char
op_star
id|name
suffix:semicolon
id|ADDBUF
c_func
(paren
id|buf
comma
l_string|&quot;Name:&bslash;t&quot;
)paren
suffix:semicolon
id|name
op_assign
id|p-&gt;comm
suffix:semicolon
id|i
op_assign
r_sizeof
(paren
id|p-&gt;comm
)paren
suffix:semicolon
r_do
(brace
r_int
r_char
id|c
op_assign
op_star
id|name
suffix:semicolon
id|name
op_increment
suffix:semicolon
id|i
op_decrement
suffix:semicolon
op_star
id|buf
op_assign
id|c
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|c
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;&bslash;&bslash;&squot;
)paren
(brace
id|buf
(braket
l_int|1
)braket
op_assign
id|c
suffix:semicolon
id|buf
op_add_assign
l_int|2
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;&bslash;n&squot;
)paren
(brace
id|buf
(braket
l_int|0
)braket
op_assign
l_char|&squot;&bslash;&bslash;&squot;
suffix:semicolon
id|buf
(braket
l_int|1
)braket
op_assign
l_char|&squot;n&squot;
suffix:semicolon
id|buf
op_add_assign
l_int|2
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|buf
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
id|i
)paren
suffix:semicolon
op_star
id|buf
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
r_return
id|buf
op_plus
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * The task state array is a strange &quot;bitmap&quot; of&n; * reasons to sleep. Thus &quot;running&quot; is zero, and&n; * you can test for combinations of others with&n; * simple bit tests.&n; */
DECL|variable|task_state_array
r_static
r_const
r_char
op_star
id|task_state_array
(braket
)braket
op_assign
(brace
l_string|&quot;R (running)&quot;
comma
multiline_comment|/*  0 */
l_string|&quot;S (sleeping)&quot;
comma
multiline_comment|/*  1 */
l_string|&quot;D (disk sleep)&quot;
comma
multiline_comment|/*  2 */
l_string|&quot;Z (zombie)&quot;
comma
multiline_comment|/*  4 */
l_string|&quot;T (stopped)&quot;
comma
multiline_comment|/*  8 */
l_string|&quot;W (paging)&quot;
multiline_comment|/* 16 */
)brace
suffix:semicolon
DECL|function|get_task_state
r_static
r_inline
r_const
r_char
op_star
id|get_task_state
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
)paren
(brace
r_int
r_int
id|state
op_assign
id|tsk-&gt;state
op_amp
(paren
id|TASK_RUNNING
op_or
id|TASK_INTERRUPTIBLE
op_or
id|TASK_UNINTERRUPTIBLE
op_or
id|TASK_ZOMBIE
op_or
id|TASK_STOPPED
)paren
suffix:semicolon
r_const
r_char
op_star
op_star
id|p
op_assign
op_amp
id|task_state_array
(braket
l_int|0
)braket
suffix:semicolon
r_while
c_loop
(paren
id|state
)paren
(brace
id|p
op_increment
suffix:semicolon
id|state
op_rshift_assign
l_int|1
suffix:semicolon
)brace
r_return
op_star
id|p
suffix:semicolon
)brace
DECL|function|task_state
r_static
r_inline
r_char
op_star
id|task_state
c_func
(paren
r_struct
id|task_struct
op_star
id|p
comma
r_char
op_star
id|buffer
)paren
(brace
r_int
id|g
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|tasklist_lock
)paren
suffix:semicolon
id|buffer
op_add_assign
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;State:&bslash;t%s&bslash;n&quot;
l_string|&quot;Tgid:&bslash;t%d&bslash;n&quot;
l_string|&quot;Pid:&bslash;t%d&bslash;n&quot;
l_string|&quot;PPid:&bslash;t%d&bslash;n&quot;
l_string|&quot;TracerPid:&bslash;t%d&bslash;n&quot;
l_string|&quot;Uid:&bslash;t%d&bslash;t%d&bslash;t%d&bslash;t%d&bslash;n&quot;
l_string|&quot;Gid:&bslash;t%d&bslash;t%d&bslash;t%d&bslash;t%d&bslash;n&quot;
comma
id|get_task_state
c_func
(paren
id|p
)paren
comma
id|p-&gt;tgid
comma
id|p-&gt;pid
comma
id|p-&gt;pid
ques
c_cond
id|p-&gt;real_parent-&gt;pid
suffix:colon
l_int|0
comma
l_int|0
comma
id|p-&gt;uid
comma
id|p-&gt;euid
comma
id|p-&gt;suid
comma
id|p-&gt;fsuid
comma
id|p-&gt;gid
comma
id|p-&gt;egid
comma
id|p-&gt;sgid
comma
id|p-&gt;fsgid
)paren
suffix:semicolon
id|read_unlock
c_func
(paren
op_amp
id|tasklist_lock
)paren
suffix:semicolon
id|task_lock
c_func
(paren
id|p
)paren
suffix:semicolon
id|buffer
op_add_assign
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;FDSize:&bslash;t%d&bslash;n&quot;
l_string|&quot;Groups:&bslash;t&quot;
comma
id|p-&gt;files
ques
c_cond
id|p-&gt;files-&gt;max_fds
suffix:colon
l_int|0
)paren
suffix:semicolon
id|task_unlock
c_func
(paren
id|p
)paren
suffix:semicolon
r_for
c_loop
(paren
id|g
op_assign
l_int|0
suffix:semicolon
id|g
OL
id|p-&gt;ngroups
suffix:semicolon
id|g
op_increment
)paren
id|buffer
op_add_assign
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;%d &quot;
comma
id|p-&gt;groups
(braket
id|g
)braket
)paren
suffix:semicolon
id|buffer
op_add_assign
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|buffer
suffix:semicolon
)brace
DECL|function|task_mem
r_static
r_inline
r_char
op_star
id|task_mem
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_char
op_star
id|buffer
)paren
(brace
r_struct
id|vm_area_struct
op_star
id|vma
suffix:semicolon
r_int
r_int
id|data
op_assign
l_int|0
comma
id|stack
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|exec
op_assign
l_int|0
comma
id|lib
op_assign
l_int|0
suffix:semicolon
id|down_read
c_func
(paren
op_amp
id|mm-&gt;mmap_sem
)paren
suffix:semicolon
r_for
c_loop
(paren
id|vma
op_assign
id|mm-&gt;mmap
suffix:semicolon
id|vma
suffix:semicolon
id|vma
op_assign
id|vma-&gt;vm_next
)paren
(brace
r_int
r_int
id|len
op_assign
(paren
id|vma-&gt;vm_end
op_minus
id|vma-&gt;vm_start
)paren
op_rshift
l_int|10
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|vma-&gt;vm_file
)paren
(brace
id|data
op_add_assign
id|len
suffix:semicolon
r_if
c_cond
(paren
id|vma-&gt;vm_flags
op_amp
id|VM_GROWSDOWN
)paren
id|stack
op_add_assign
id|len
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|vma-&gt;vm_flags
op_amp
id|VM_WRITE
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|vma-&gt;vm_flags
op_amp
id|VM_EXEC
)paren
(brace
id|exec
op_add_assign
id|len
suffix:semicolon
r_if
c_cond
(paren
id|vma-&gt;vm_flags
op_amp
id|VM_EXECUTABLE
)paren
r_continue
suffix:semicolon
id|lib
op_add_assign
id|len
suffix:semicolon
)brace
)brace
id|buffer
op_add_assign
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;VmSize:&bslash;t%8lu kB&bslash;n&quot;
l_string|&quot;VmLck:&bslash;t%8lu kB&bslash;n&quot;
l_string|&quot;VmRSS:&bslash;t%8lu kB&bslash;n&quot;
l_string|&quot;VmData:&bslash;t%8lu kB&bslash;n&quot;
l_string|&quot;VmStk:&bslash;t%8lu kB&bslash;n&quot;
l_string|&quot;VmExe:&bslash;t%8lu kB&bslash;n&quot;
l_string|&quot;VmLib:&bslash;t%8lu kB&bslash;n&quot;
comma
id|mm-&gt;total_vm
op_lshift
(paren
id|PAGE_SHIFT
op_minus
l_int|10
)paren
comma
id|mm-&gt;locked_vm
op_lshift
(paren
id|PAGE_SHIFT
op_minus
l_int|10
)paren
comma
id|mm-&gt;rss
op_lshift
(paren
id|PAGE_SHIFT
op_minus
l_int|10
)paren
comma
id|data
op_minus
id|stack
comma
id|stack
comma
id|exec
op_minus
id|lib
comma
id|lib
)paren
suffix:semicolon
id|up_read
c_func
(paren
op_amp
id|mm-&gt;mmap_sem
)paren
suffix:semicolon
r_return
id|buffer
suffix:semicolon
)brace
DECL|function|collect_sigign_sigcatch
r_static
r_void
id|collect_sigign_sigcatch
c_func
(paren
r_struct
id|task_struct
op_star
id|p
comma
id|sigset_t
op_star
id|ign
comma
id|sigset_t
op_star
r_catch
)paren
(brace
r_struct
id|k_sigaction
op_star
id|k
suffix:semicolon
r_int
id|i
suffix:semicolon
id|sigemptyset
c_func
(paren
id|ign
)paren
suffix:semicolon
id|sigemptyset
c_func
(paren
r_catch
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;sig
)paren
(brace
id|k
op_assign
id|p-&gt;sig-&gt;action
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
op_le
id|_NSIG
suffix:semicolon
op_increment
id|i
comma
op_increment
id|k
)paren
(brace
r_if
c_cond
(paren
id|k-&gt;sa.sa_handler
op_eq
id|SIG_IGN
)paren
id|sigaddset
c_func
(paren
id|ign
comma
id|i
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|k-&gt;sa.sa_handler
op_ne
id|SIG_DFL
)paren
id|sigaddset
c_func
(paren
r_catch
comma
id|i
)paren
suffix:semicolon
)brace
)brace
)brace
DECL|function|task_sig
r_static
r_inline
r_char
op_star
id|task_sig
c_func
(paren
r_struct
id|task_struct
op_star
id|p
comma
r_char
op_star
id|buffer
)paren
(brace
id|sigset_t
id|ign
comma
r_catch
suffix:semicolon
id|buffer
op_add_assign
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;SigPnd:&bslash;t&quot;
)paren
suffix:semicolon
id|buffer
op_assign
id|render_sigset_t
c_func
(paren
op_amp
id|p-&gt;pending.signal
comma
id|buffer
)paren
suffix:semicolon
op_star
id|buffer
op_increment
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
id|buffer
op_add_assign
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;SigBlk:&bslash;t&quot;
)paren
suffix:semicolon
id|buffer
op_assign
id|render_sigset_t
c_func
(paren
op_amp
id|p-&gt;blocked
comma
id|buffer
)paren
suffix:semicolon
op_star
id|buffer
op_increment
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
id|collect_sigign_sigcatch
c_func
(paren
id|p
comma
op_amp
id|ign
comma
op_amp
r_catch
)paren
suffix:semicolon
id|buffer
op_add_assign
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;SigIgn:&bslash;t&quot;
)paren
suffix:semicolon
id|buffer
op_assign
id|render_sigset_t
c_func
(paren
op_amp
id|ign
comma
id|buffer
)paren
suffix:semicolon
op_star
id|buffer
op_increment
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
id|buffer
op_add_assign
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;SigCgt:&bslash;t&quot;
)paren
suffix:semicolon
multiline_comment|/* Linux 2.0 uses &quot;SigCgt&quot; */
id|buffer
op_assign
id|render_sigset_t
c_func
(paren
op_amp
r_catch
comma
id|buffer
)paren
suffix:semicolon
op_star
id|buffer
op_increment
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
r_return
id|buffer
suffix:semicolon
)brace
DECL|function|task_cap
r_static
r_inline
r_char
op_star
id|task_cap
c_func
(paren
r_struct
id|task_struct
op_star
id|p
comma
r_char
op_star
id|buffer
)paren
(brace
r_return
id|buffer
op_plus
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;CapInh:&bslash;t%016x&bslash;n&quot;
l_string|&quot;CapPrm:&bslash;t%016x&bslash;n&quot;
l_string|&quot;CapEff:&bslash;t%016x&bslash;n&quot;
comma
id|cap_t
c_func
(paren
id|p-&gt;cap_inheritable
)paren
comma
id|cap_t
c_func
(paren
id|p-&gt;cap_permitted
)paren
comma
id|cap_t
c_func
(paren
id|p-&gt;cap_effective
)paren
)paren
suffix:semicolon
)brace
DECL|function|proc_pid_status
r_int
id|proc_pid_status
c_func
(paren
r_struct
id|task_struct
op_star
id|task
comma
r_char
op_star
id|buffer
)paren
(brace
r_char
op_star
id|orig
op_assign
id|buffer
suffix:semicolon
r_struct
id|mm_struct
op_star
id|mm
suffix:semicolon
id|buffer
op_assign
id|task_name
c_func
(paren
id|task
comma
id|buffer
)paren
suffix:semicolon
id|buffer
op_assign
id|task_state
c_func
(paren
id|task
comma
id|buffer
)paren
suffix:semicolon
id|task_lock
c_func
(paren
id|task
)paren
suffix:semicolon
id|mm
op_assign
id|task-&gt;mm
suffix:semicolon
r_if
c_cond
(paren
id|mm
)paren
(brace
id|atomic_inc
c_func
(paren
op_amp
id|mm-&gt;mm_users
)paren
suffix:semicolon
)brace
id|task_unlock
c_func
(paren
id|task
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mm
)paren
(brace
id|buffer
op_assign
id|task_mem
c_func
(paren
id|mm
comma
id|buffer
)paren
suffix:semicolon
id|mmput
c_func
(paren
id|mm
)paren
suffix:semicolon
)brace
id|buffer
op_assign
id|task_sig
c_func
(paren
id|task
comma
id|buffer
)paren
suffix:semicolon
id|buffer
op_assign
id|task_cap
c_func
(paren
id|task
comma
id|buffer
)paren
suffix:semicolon
macro_line|#if defined(CONFIG_ARCH_S390)
id|buffer
op_assign
id|task_show_regs
c_func
(paren
id|task
comma
id|buffer
)paren
suffix:semicolon
macro_line|#endif
r_return
id|buffer
op_minus
id|orig
suffix:semicolon
)brace
DECL|function|proc_pid_stat
r_int
id|proc_pid_stat
c_func
(paren
r_struct
id|task_struct
op_star
id|task
comma
r_char
op_star
id|buffer
)paren
(brace
r_int
r_int
id|vsize
comma
id|eip
comma
id|esp
comma
id|wchan
suffix:semicolon
r_int
id|priority
comma
id|nice
suffix:semicolon
r_int
id|tty_pgrp
op_assign
op_minus
l_int|1
comma
id|tty_nr
op_assign
l_int|0
suffix:semicolon
id|sigset_t
id|sigign
comma
id|sigcatch
suffix:semicolon
r_char
id|state
suffix:semicolon
r_int
id|res
suffix:semicolon
id|pid_t
id|ppid
suffix:semicolon
r_struct
id|mm_struct
op_star
id|mm
suffix:semicolon
id|state
op_assign
op_star
id|get_task_state
c_func
(paren
id|task
)paren
suffix:semicolon
id|vsize
op_assign
id|eip
op_assign
id|esp
op_assign
l_int|0
suffix:semicolon
id|task_lock
c_func
(paren
id|task
)paren
suffix:semicolon
id|mm
op_assign
id|task-&gt;mm
suffix:semicolon
r_if
c_cond
(paren
id|mm
)paren
(brace
id|atomic_inc
c_func
(paren
op_amp
id|mm-&gt;mm_users
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|task-&gt;tty
)paren
(brace
id|tty_pgrp
op_assign
id|task-&gt;tty-&gt;pgrp
suffix:semicolon
id|tty_nr
op_assign
id|kdev_t_to_nr
c_func
(paren
id|task-&gt;tty-&gt;device
)paren
suffix:semicolon
)brace
id|task_unlock
c_func
(paren
id|task
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mm
)paren
(brace
r_struct
id|vm_area_struct
op_star
id|vma
suffix:semicolon
id|down_read
c_func
(paren
op_amp
id|mm-&gt;mmap_sem
)paren
suffix:semicolon
id|vma
op_assign
id|mm-&gt;mmap
suffix:semicolon
r_while
c_loop
(paren
id|vma
)paren
(brace
id|vsize
op_add_assign
id|vma-&gt;vm_end
op_minus
id|vma-&gt;vm_start
suffix:semicolon
id|vma
op_assign
id|vma-&gt;vm_next
suffix:semicolon
)brace
id|eip
op_assign
id|KSTK_EIP
c_func
(paren
id|task
)paren
suffix:semicolon
id|esp
op_assign
id|KSTK_ESP
c_func
(paren
id|task
)paren
suffix:semicolon
id|up_read
c_func
(paren
op_amp
id|mm-&gt;mmap_sem
)paren
suffix:semicolon
)brace
id|wchan
op_assign
id|get_wchan
c_func
(paren
id|task
)paren
suffix:semicolon
id|collect_sigign_sigcatch
c_func
(paren
id|task
comma
op_amp
id|sigign
comma
op_amp
id|sigcatch
)paren
suffix:semicolon
multiline_comment|/* scale priority and nice values from timeslices to -20..20 */
multiline_comment|/* to make it look like a &quot;normal&quot; Unix priority/nice value  */
id|priority
op_assign
id|task_prio
c_func
(paren
id|task
)paren
suffix:semicolon
id|nice
op_assign
id|task_nice
c_func
(paren
id|task
)paren
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|tasklist_lock
)paren
suffix:semicolon
id|ppid
op_assign
id|task-&gt;pid
ques
c_cond
id|task-&gt;real_parent-&gt;pid
suffix:colon
l_int|0
suffix:semicolon
id|read_unlock
c_func
(paren
op_amp
id|tasklist_lock
)paren
suffix:semicolon
id|res
op_assign
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;%d (%s) %c %d %d %d %d %d %lu %lu &bslash;&n;%lu %lu %lu %lu %lu %ld %ld %ld %ld %ld %ld %lu %lu %ld %lu %lu %lu %lu %lu &bslash;&n;%lu %lu %lu %lu %lu %lu %lu %lu %d %d&bslash;n&quot;
comma
id|task-&gt;pid
comma
id|task-&gt;comm
comma
id|state
comma
id|ppid
comma
id|task-&gt;pgrp
comma
id|task-&gt;session
comma
id|tty_nr
comma
id|tty_pgrp
comma
id|task-&gt;flags
comma
id|task-&gt;min_flt
comma
id|task-&gt;cmin_flt
comma
id|task-&gt;maj_flt
comma
id|task-&gt;cmaj_flt
comma
id|task-&gt;times.tms_utime
comma
id|task-&gt;times.tms_stime
comma
id|task-&gt;times.tms_cutime
comma
id|task-&gt;times.tms_cstime
comma
id|priority
comma
id|nice
comma
l_int|0UL
multiline_comment|/* removed */
comma
id|task-&gt;it_real_value
comma
id|task-&gt;start_time
comma
id|vsize
comma
id|mm
ques
c_cond
id|mm-&gt;rss
suffix:colon
l_int|0
comma
multiline_comment|/* you might want to shift this left 3 */
id|task-&gt;rlim
(braket
id|RLIMIT_RSS
)braket
dot
id|rlim_cur
comma
id|mm
ques
c_cond
id|mm-&gt;start_code
suffix:colon
l_int|0
comma
id|mm
ques
c_cond
id|mm-&gt;end_code
suffix:colon
l_int|0
comma
id|mm
ques
c_cond
id|mm-&gt;start_stack
suffix:colon
l_int|0
comma
id|esp
comma
id|eip
comma
multiline_comment|/* The signal information here is obsolete.&n;&t;&t; * It must be decimal for Linux 2.0 compatibility.&n;&t;&t; * Use /proc/#/status for real-time signals.&n;&t;&t; */
id|task-&gt;pending.signal.sig
(braket
l_int|0
)braket
op_amp
l_int|0x7fffffffUL
comma
id|task-&gt;blocked.sig
(braket
l_int|0
)braket
op_amp
l_int|0x7fffffffUL
comma
id|sigign
dot
id|sig
(braket
l_int|0
)braket
op_amp
l_int|0x7fffffffUL
comma
id|sigcatch
dot
id|sig
(braket
l_int|0
)braket
op_amp
l_int|0x7fffffffUL
comma
id|wchan
comma
id|task-&gt;nswap
comma
id|task-&gt;cnswap
comma
id|task-&gt;exit_signal
comma
id|task-&gt;thread_info-&gt;cpu
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mm
)paren
(brace
id|mmput
c_func
(paren
id|mm
)paren
suffix:semicolon
)brace
r_return
id|res
suffix:semicolon
)brace
DECL|function|statm_pte_range
r_static
r_inline
r_void
id|statm_pte_range
c_func
(paren
id|pmd_t
op_star
id|pmd
comma
r_int
r_int
id|address
comma
r_int
r_int
id|size
comma
r_int
op_star
id|pages
comma
r_int
op_star
id|shared
comma
r_int
op_star
id|dirty
comma
r_int
op_star
id|total
)paren
(brace
r_int
r_int
id|end
comma
id|pmd_end
suffix:semicolon
id|pte_t
op_star
id|pte
suffix:semicolon
r_if
c_cond
(paren
id|pmd_none
c_func
(paren
op_star
id|pmd
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|pmd_bad
c_func
(paren
op_star
id|pmd
)paren
)paren
(brace
id|pmd_ERROR
c_func
(paren
op_star
id|pmd
)paren
suffix:semicolon
id|pmd_clear
c_func
(paren
id|pmd
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|preempt_disable
c_func
(paren
)paren
suffix:semicolon
id|pte
op_assign
id|pte_offset_map
c_func
(paren
id|pmd
comma
id|address
)paren
suffix:semicolon
id|end
op_assign
id|address
op_plus
id|size
suffix:semicolon
id|pmd_end
op_assign
(paren
id|address
op_plus
id|PMD_SIZE
)paren
op_amp
id|PMD_MASK
suffix:semicolon
r_if
c_cond
(paren
id|end
OG
id|pmd_end
)paren
id|end
op_assign
id|pmd_end
suffix:semicolon
r_do
(brace
id|pte_t
id|page
op_assign
op_star
id|pte
suffix:semicolon
r_struct
id|page
op_star
id|ptpage
suffix:semicolon
id|address
op_add_assign
id|PAGE_SIZE
suffix:semicolon
id|pte
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|pte_none
c_func
(paren
id|page
)paren
)paren
r_continue
suffix:semicolon
op_increment
op_star
id|total
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pte_present
c_func
(paren
id|page
)paren
)paren
r_continue
suffix:semicolon
id|ptpage
op_assign
id|pte_page
c_func
(paren
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
op_logical_neg
id|VALID_PAGE
c_func
(paren
id|ptpage
)paren
)paren
op_logical_or
id|PageReserved
c_func
(paren
id|ptpage
)paren
)paren
r_continue
suffix:semicolon
op_increment
op_star
id|pages
suffix:semicolon
r_if
c_cond
(paren
id|pte_dirty
c_func
(paren
id|page
)paren
)paren
op_increment
op_star
id|dirty
suffix:semicolon
r_if
c_cond
(paren
id|page_count
c_func
(paren
id|pte_page
c_func
(paren
id|page
)paren
)paren
OG
l_int|1
)paren
op_increment
op_star
id|shared
suffix:semicolon
)brace
r_while
c_loop
(paren
id|address
OL
id|end
)paren
suffix:semicolon
id|pte_unmap
c_func
(paren
id|pte
op_minus
l_int|1
)paren
suffix:semicolon
id|preempt_enable
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|statm_pmd_range
r_static
r_inline
r_void
id|statm_pmd_range
c_func
(paren
id|pgd_t
op_star
id|pgd
comma
r_int
r_int
id|address
comma
r_int
r_int
id|size
comma
r_int
op_star
id|pages
comma
r_int
op_star
id|shared
comma
r_int
op_star
id|dirty
comma
r_int
op_star
id|total
)paren
(brace
id|pmd_t
op_star
id|pmd
suffix:semicolon
r_int
r_int
id|end
suffix:semicolon
r_if
c_cond
(paren
id|pgd_none
c_func
(paren
op_star
id|pgd
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|pgd_bad
c_func
(paren
op_star
id|pgd
)paren
)paren
(brace
id|pgd_ERROR
c_func
(paren
op_star
id|pgd
)paren
suffix:semicolon
id|pgd_clear
c_func
(paren
id|pgd
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|pmd
op_assign
id|pmd_offset
c_func
(paren
id|pgd
comma
id|address
)paren
suffix:semicolon
id|address
op_and_assign
op_complement
id|PGDIR_MASK
suffix:semicolon
id|end
op_assign
id|address
op_plus
id|size
suffix:semicolon
r_if
c_cond
(paren
id|end
OG
id|PGDIR_SIZE
)paren
id|end
op_assign
id|PGDIR_SIZE
suffix:semicolon
r_do
(brace
id|statm_pte_range
c_func
(paren
id|pmd
comma
id|address
comma
id|end
op_minus
id|address
comma
id|pages
comma
id|shared
comma
id|dirty
comma
id|total
)paren
suffix:semicolon
id|address
op_assign
(paren
id|address
op_plus
id|PMD_SIZE
)paren
op_amp
id|PMD_MASK
suffix:semicolon
id|pmd
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
id|address
OL
id|end
)paren
suffix:semicolon
)brace
DECL|function|statm_pgd_range
r_static
r_void
id|statm_pgd_range
c_func
(paren
id|pgd_t
op_star
id|pgd
comma
r_int
r_int
id|address
comma
r_int
r_int
id|end
comma
r_int
op_star
id|pages
comma
r_int
op_star
id|shared
comma
r_int
op_star
id|dirty
comma
r_int
op_star
id|total
)paren
(brace
r_while
c_loop
(paren
id|address
OL
id|end
)paren
(brace
id|statm_pmd_range
c_func
(paren
id|pgd
comma
id|address
comma
id|end
op_minus
id|address
comma
id|pages
comma
id|shared
comma
id|dirty
comma
id|total
)paren
suffix:semicolon
id|address
op_assign
(paren
id|address
op_plus
id|PGDIR_SIZE
)paren
op_amp
id|PGDIR_MASK
suffix:semicolon
id|pgd
op_increment
suffix:semicolon
)brace
)brace
DECL|function|proc_pid_statm
r_int
id|proc_pid_statm
c_func
(paren
r_struct
id|task_struct
op_star
id|task
comma
r_char
op_star
id|buffer
)paren
(brace
r_struct
id|mm_struct
op_star
id|mm
suffix:semicolon
r_int
id|size
op_assign
l_int|0
comma
id|resident
op_assign
l_int|0
comma
id|share
op_assign
l_int|0
comma
id|trs
op_assign
l_int|0
comma
id|lrs
op_assign
l_int|0
comma
id|drs
op_assign
l_int|0
comma
id|dt
op_assign
l_int|0
suffix:semicolon
id|task_lock
c_func
(paren
id|task
)paren
suffix:semicolon
id|mm
op_assign
id|task-&gt;mm
suffix:semicolon
r_if
c_cond
(paren
id|mm
)paren
(brace
id|atomic_inc
c_func
(paren
op_amp
id|mm-&gt;mm_users
)paren
suffix:semicolon
)brace
id|task_unlock
c_func
(paren
id|task
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mm
)paren
(brace
r_struct
id|vm_area_struct
op_star
id|vma
suffix:semicolon
id|down_read
c_func
(paren
op_amp
id|mm-&gt;mmap_sem
)paren
suffix:semicolon
id|vma
op_assign
id|mm-&gt;mmap
suffix:semicolon
r_while
c_loop
(paren
id|vma
)paren
(brace
id|pgd_t
op_star
id|pgd
op_assign
id|pgd_offset
c_func
(paren
id|mm
comma
id|vma-&gt;vm_start
)paren
suffix:semicolon
r_int
id|pages
op_assign
l_int|0
comma
id|shared
op_assign
l_int|0
comma
id|dirty
op_assign
l_int|0
comma
id|total
op_assign
l_int|0
suffix:semicolon
id|statm_pgd_range
c_func
(paren
id|pgd
comma
id|vma-&gt;vm_start
comma
id|vma-&gt;vm_end
comma
op_amp
id|pages
comma
op_amp
id|shared
comma
op_amp
id|dirty
comma
op_amp
id|total
)paren
suffix:semicolon
id|resident
op_add_assign
id|pages
suffix:semicolon
id|share
op_add_assign
id|shared
suffix:semicolon
id|dt
op_add_assign
id|dirty
suffix:semicolon
id|size
op_add_assign
id|total
suffix:semicolon
r_if
c_cond
(paren
id|vma-&gt;vm_flags
op_amp
id|VM_EXECUTABLE
)paren
id|trs
op_add_assign
id|pages
suffix:semicolon
multiline_comment|/* text */
r_else
r_if
c_cond
(paren
id|vma-&gt;vm_flags
op_amp
id|VM_GROWSDOWN
)paren
id|drs
op_add_assign
id|pages
suffix:semicolon
multiline_comment|/* stack */
r_else
r_if
c_cond
(paren
id|vma-&gt;vm_end
OG
l_int|0x60000000
)paren
id|lrs
op_add_assign
id|pages
suffix:semicolon
multiline_comment|/* library */
r_else
id|drs
op_add_assign
id|pages
suffix:semicolon
id|vma
op_assign
id|vma-&gt;vm_next
suffix:semicolon
)brace
id|up_read
c_func
(paren
op_amp
id|mm-&gt;mmap_sem
)paren
suffix:semicolon
id|mmput
c_func
(paren
id|mm
)paren
suffix:semicolon
)brace
r_return
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;%d %d %d %d %d %d %d&bslash;n&quot;
comma
id|size
comma
id|resident
comma
id|share
comma
id|trs
comma
id|lrs
comma
id|drs
comma
id|dt
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * The way we support synthetic files &gt; 4K&n; * - without storing their contents in some buffer and&n; * - without walking through the entire synthetic file until we reach the&n; *   position of the requested data&n; * is to cleverly encode the current position in the file&squot;s f_pos field.&n; * There is no requirement that a read() call which returns `count&squot; bytes&n; * of data increases f_pos by exactly `count&squot;.&n; *&n; * This idea is Linus&squot; one. Bruno implemented it.&n; */
multiline_comment|/*&n; * For the /proc/&lt;pid&gt;/maps file, we use fixed length records, each containing&n; * a single line.&n; *&n; * f_pos = (number of the vma in the task-&gt;mm-&gt;mmap list) * PAGE_SIZE&n; *         + (index into the line)&n; */
multiline_comment|/* for systems with sizeof(void*) == 4: */
DECL|macro|MAPS_LINE_FORMAT4
mdefine_line|#define MAPS_LINE_FORMAT4&t;  &quot;%08lx-%08lx %s %08lx %s %lu&quot;
DECL|macro|MAPS_LINE_MAX4
mdefine_line|#define MAPS_LINE_MAX4&t;49 /* sum of 8  1  8  1 4 1 8 1 5 1 10 1 */
multiline_comment|/* for systems with sizeof(void*) == 8: */
DECL|macro|MAPS_LINE_FORMAT8
mdefine_line|#define MAPS_LINE_FORMAT8&t;  &quot;%016lx-%016lx %s %016lx %s %lu&quot;
DECL|macro|MAPS_LINE_MAX8
mdefine_line|#define MAPS_LINE_MAX8&t;73 /* sum of 16  1  16  1 4 1 16 1 5 1 10 1 */
DECL|macro|MAPS_LINE_FORMAT
mdefine_line|#define MAPS_LINE_FORMAT&t;(sizeof(void*) == 4 ? MAPS_LINE_FORMAT4 : MAPS_LINE_FORMAT8)
DECL|macro|MAPS_LINE_MAX
mdefine_line|#define MAPS_LINE_MAX&t;(sizeof(void*) == 4 ?  MAPS_LINE_MAX4 :  MAPS_LINE_MAX8)
DECL|function|proc_pid_maps_get_line
r_static
r_int
id|proc_pid_maps_get_line
(paren
r_char
op_star
id|buf
comma
r_struct
id|vm_area_struct
op_star
id|map
)paren
(brace
multiline_comment|/* produce the next line */
r_char
op_star
id|line
suffix:semicolon
r_char
id|str
(braket
l_int|5
)braket
suffix:semicolon
r_int
id|flags
suffix:semicolon
id|kdev_t
id|dev
suffix:semicolon
r_int
r_int
id|ino
suffix:semicolon
r_int
id|len
suffix:semicolon
id|flags
op_assign
id|map-&gt;vm_flags
suffix:semicolon
id|str
(braket
l_int|0
)braket
op_assign
id|flags
op_amp
id|VM_READ
ques
c_cond
l_char|&squot;r&squot;
suffix:colon
l_char|&squot;-&squot;
suffix:semicolon
id|str
(braket
l_int|1
)braket
op_assign
id|flags
op_amp
id|VM_WRITE
ques
c_cond
l_char|&squot;w&squot;
suffix:colon
l_char|&squot;-&squot;
suffix:semicolon
id|str
(braket
l_int|2
)braket
op_assign
id|flags
op_amp
id|VM_EXEC
ques
c_cond
l_char|&squot;x&squot;
suffix:colon
l_char|&squot;-&squot;
suffix:semicolon
id|str
(braket
l_int|3
)braket
op_assign
id|flags
op_amp
id|VM_MAYSHARE
ques
c_cond
l_char|&squot;s&squot;
suffix:colon
l_char|&squot;p&squot;
suffix:semicolon
id|str
(braket
l_int|4
)braket
op_assign
l_int|0
suffix:semicolon
id|dev
op_assign
id|NODEV
suffix:semicolon
id|ino
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|map-&gt;vm_file
op_ne
l_int|NULL
)paren
(brace
id|dev
op_assign
id|map-&gt;vm_file-&gt;f_dentry-&gt;d_inode-&gt;i_dev
suffix:semicolon
id|ino
op_assign
id|map-&gt;vm_file-&gt;f_dentry-&gt;d_inode-&gt;i_ino
suffix:semicolon
id|line
op_assign
id|d_path
c_func
(paren
id|map-&gt;vm_file-&gt;f_dentry
comma
id|map-&gt;vm_file-&gt;f_vfsmnt
comma
id|buf
comma
id|PAGE_SIZE
)paren
suffix:semicolon
id|buf
(braket
id|PAGE_SIZE
op_minus
l_int|1
)braket
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
id|line
op_sub_assign
id|MAPS_LINE_MAX
suffix:semicolon
r_if
c_cond
(paren
id|line
OL
id|buf
)paren
(brace
id|line
op_assign
id|buf
suffix:semicolon
)brace
)brace
r_else
id|line
op_assign
id|buf
suffix:semicolon
id|len
op_assign
id|sprintf
c_func
(paren
id|line
comma
id|MAPS_LINE_FORMAT
comma
id|map-&gt;vm_start
comma
id|map-&gt;vm_end
comma
id|str
comma
id|map-&gt;vm_pgoff
op_lshift
id|PAGE_SHIFT
comma
id|kdevname
c_func
(paren
id|dev
)paren
comma
id|ino
)paren
suffix:semicolon
r_if
c_cond
(paren
id|map-&gt;vm_file
)paren
(brace
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|len
suffix:semicolon
id|i
OL
id|MAPS_LINE_MAX
suffix:semicolon
id|i
op_increment
)paren
(brace
id|line
(braket
id|i
)braket
op_assign
l_char|&squot; &squot;
suffix:semicolon
)brace
id|len
op_assign
id|buf
op_plus
id|PAGE_SIZE
op_minus
id|line
suffix:semicolon
id|memmove
c_func
(paren
id|buf
comma
id|line
comma
id|len
)paren
suffix:semicolon
)brace
r_else
id|line
(braket
id|len
op_increment
)braket
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
DECL|function|proc_pid_read_maps
id|ssize_t
id|proc_pid_read_maps
(paren
r_struct
id|task_struct
op_star
id|task
comma
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
r_struct
id|mm_struct
op_star
id|mm
suffix:semicolon
r_struct
id|vm_area_struct
op_star
id|map
suffix:semicolon
r_char
op_star
id|tmp
comma
op_star
id|kbuf
suffix:semicolon
r_int
id|retval
suffix:semicolon
r_int
id|off
comma
id|lineno
comma
id|loff
suffix:semicolon
multiline_comment|/* reject calls with out of range parameters immediately */
id|retval
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_star
id|ppos
OG
id|LONG_MAX
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|count
op_eq
l_int|0
)paren
r_goto
id|out
suffix:semicolon
id|off
op_assign
(paren
r_int
)paren
op_star
id|ppos
suffix:semicolon
multiline_comment|/*&n;&t; * We might sleep getting the page, so get it first.&n;&t; */
id|retval
op_assign
op_minus
id|ENOMEM
suffix:semicolon
id|kbuf
op_assign
(paren
r_char
op_star
)paren
id|__get_free_page
c_func
(paren
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|kbuf
)paren
r_goto
id|out
suffix:semicolon
id|tmp
op_assign
(paren
r_char
op_star
)paren
id|__get_free_page
c_func
(paren
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tmp
)paren
r_goto
id|out_free1
suffix:semicolon
id|task_lock
c_func
(paren
id|task
)paren
suffix:semicolon
id|mm
op_assign
id|task-&gt;mm
suffix:semicolon
r_if
c_cond
(paren
id|mm
)paren
id|atomic_inc
c_func
(paren
op_amp
id|mm-&gt;mm_users
)paren
suffix:semicolon
id|task_unlock
c_func
(paren
id|task
)paren
suffix:semicolon
id|retval
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mm
)paren
r_goto
id|out_free2
suffix:semicolon
id|down_read
c_func
(paren
op_amp
id|mm-&gt;mmap_sem
)paren
suffix:semicolon
id|map
op_assign
id|mm-&gt;mmap
suffix:semicolon
id|lineno
op_assign
l_int|0
suffix:semicolon
id|loff
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|count
OG
id|PAGE_SIZE
)paren
id|count
op_assign
id|PAGE_SIZE
suffix:semicolon
r_while
c_loop
(paren
id|map
)paren
(brace
r_int
id|len
suffix:semicolon
r_if
c_cond
(paren
id|off
OG
id|PAGE_SIZE
)paren
(brace
id|off
op_sub_assign
id|PAGE_SIZE
suffix:semicolon
r_goto
id|next
suffix:semicolon
)brace
id|len
op_assign
id|proc_pid_maps_get_line
c_func
(paren
id|tmp
comma
id|map
)paren
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
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|retval
op_plus
id|len
OG
id|count
)paren
(brace
multiline_comment|/* only partial line transfer possible */
id|len
op_assign
id|count
op_minus
id|retval
suffix:semicolon
multiline_comment|/* save the offset where the next read&n;&t;&t;&t;&t; * must start */
id|loff
op_assign
id|len
op_plus
id|off
suffix:semicolon
)brace
id|memcpy
c_func
(paren
id|kbuf
op_plus
id|retval
comma
id|tmp
op_plus
id|off
comma
id|len
)paren
suffix:semicolon
id|retval
op_add_assign
id|len
suffix:semicolon
)brace
id|off
op_assign
l_int|0
suffix:semicolon
id|next
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|loff
)paren
id|lineno
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|retval
op_ge
id|count
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|loff
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|map
op_assign
id|map-&gt;vm_next
suffix:semicolon
)brace
id|up_read
c_func
(paren
op_amp
id|mm-&gt;mmap_sem
)paren
suffix:semicolon
id|mmput
c_func
(paren
id|mm
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
OG
id|count
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|buf
comma
id|kbuf
comma
id|retval
)paren
)paren
id|retval
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_else
op_star
id|ppos
op_assign
(paren
id|lineno
op_lshift
id|PAGE_SHIFT
)paren
op_plus
id|loff
suffix:semicolon
id|out_free2
suffix:colon
id|free_page
c_func
(paren
(paren
r_int
r_int
)paren
id|tmp
)paren
suffix:semicolon
id|out_free1
suffix:colon
id|free_page
c_func
(paren
(paren
r_int
r_int
)paren
id|kbuf
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|retval
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_SMP
DECL|function|proc_pid_cpu
r_int
id|proc_pid_cpu
c_func
(paren
r_struct
id|task_struct
op_star
id|task
comma
r_char
op_star
id|buffer
)paren
(brace
r_int
id|i
comma
id|len
suffix:semicolon
id|len
op_assign
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;cpu  %lu %lu&bslash;n&quot;
comma
id|task-&gt;times.tms_utime
comma
id|task-&gt;times.tms_stime
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
id|buffer
op_plus
id|len
comma
l_string|&quot;cpu%d %lu %lu&bslash;n&quot;
comma
id|i
comma
id|task-&gt;per_cpu_utime
(braket
id|cpu_logical_map
c_func
(paren
id|i
)paren
)braket
comma
id|task-&gt;per_cpu_stime
(braket
id|cpu_logical_map
c_func
(paren
id|i
)paren
)braket
)paren
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
macro_line|#endif
eof
