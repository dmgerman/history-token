macro_line|#ifndef _ASM_IA64_IA32_PRIV_H
DECL|macro|_ASM_IA64_IA32_PRIV_H
mdefine_line|#define _ASM_IA64_IA32_PRIV_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/ia32.h&gt;
macro_line|#ifdef CONFIG_IA32_SUPPORT
macro_line|#include &lt;linux/binfmts.h&gt;
macro_line|#include &lt;linux/compat.h&gt;
macro_line|#include &lt;linux/rbtree.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
multiline_comment|/*&n; * 32 bit structures for IA32 support.&n; */
DECL|macro|IA32_PAGE_SIZE
mdefine_line|#define IA32_PAGE_SIZE&t;&t;(1UL &lt;&lt; IA32_PAGE_SHIFT)
DECL|macro|IA32_PAGE_MASK
mdefine_line|#define IA32_PAGE_MASK&t;&t;(~(IA32_PAGE_SIZE - 1))
DECL|macro|IA32_PAGE_ALIGN
mdefine_line|#define IA32_PAGE_ALIGN(addr)&t;(((addr) + IA32_PAGE_SIZE - 1) &amp; IA32_PAGE_MASK)
DECL|macro|IA32_CLOCKS_PER_SEC
mdefine_line|#define IA32_CLOCKS_PER_SEC&t;100&t;/* Cast in stone for IA32 Linux */
multiline_comment|/*&n; * partially mapped pages provide precise accounting of which 4k sub pages&n; * are mapped and which ones are not, thereby improving IA-32 compatibility.&n; */
DECL|struct|partial_page
r_struct
id|partial_page
(brace
DECL|member|next
r_struct
id|partial_page
op_star
id|next
suffix:semicolon
multiline_comment|/* linked list, sorted by address */
DECL|member|pp_rb
r_struct
id|rb_node
id|pp_rb
suffix:semicolon
multiline_comment|/* 64K is the largest &quot;normal&quot; page supported by ia64 ABI. So 4K*32&n;&t; * should suffice.*/
DECL|member|bitmap
r_int
r_int
id|bitmap
suffix:semicolon
DECL|member|base
r_int
r_int
id|base
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|partial_page_list
r_struct
id|partial_page_list
(brace
DECL|member|pp_head
r_struct
id|partial_page
op_star
id|pp_head
suffix:semicolon
multiline_comment|/* list head, points to the lowest&n;&t;&t;&t;&t;&t;   * addressed partial page */
DECL|member|ppl_rb
r_struct
id|rb_root
id|ppl_rb
suffix:semicolon
DECL|member|pp_hint
r_struct
id|partial_page
op_star
id|pp_hint
suffix:semicolon
multiline_comment|/* pp_hint-&gt;next is the last&n;&t;&t;&t;&t;&t;   * accessed partial page */
DECL|member|pp_count
id|atomic_t
id|pp_count
suffix:semicolon
multiline_comment|/* reference count */
)brace
suffix:semicolon
macro_line|#if PAGE_SHIFT &gt; IA32_PAGE_SHIFT
r_struct
id|partial_page_list
op_star
id|ia32_init_pp_list
(paren
r_void
)paren
suffix:semicolon
macro_line|#else
DECL|macro|ia32_init_pp_list
macro_line|# define ia32_init_pp_list()&t;0
macro_line|#endif
multiline_comment|/* sigcontext.h */
multiline_comment|/*&n; * As documented in the iBCS2 standard..&n; *&n; * The first part of &quot;struct _fpstate&quot; is just the&n; * normal i387 hardware setup, the extra &quot;status&quot;&n; * word is used to save the coprocessor status word&n; * before entering the handler.&n; */
DECL|struct|_fpreg_ia32
r_struct
id|_fpreg_ia32
(brace
DECL|member|significand
r_int
r_int
id|significand
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|exponent
r_int
r_int
id|exponent
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|_fpxreg_ia32
r_struct
id|_fpxreg_ia32
(brace
DECL|member|significand
r_int
r_int
id|significand
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|exponent
r_int
r_int
id|exponent
suffix:semicolon
DECL|member|padding
r_int
r_int
id|padding
(braket
l_int|3
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|_xmmreg_ia32
r_struct
id|_xmmreg_ia32
(brace
DECL|member|element
r_int
r_int
id|element
(braket
l_int|4
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|_fpstate_ia32
r_struct
id|_fpstate_ia32
(brace
DECL|member|cw
r_int
r_int
id|cw
comma
DECL|member|sw
id|sw
comma
DECL|member|tag
id|tag
comma
DECL|member|ipoff
id|ipoff
comma
DECL|member|cssel
id|cssel
comma
DECL|member|dataoff
id|dataoff
comma
DECL|member|datasel
id|datasel
suffix:semicolon
DECL|member|_st
r_struct
id|_fpreg_ia32
id|_st
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|status
r_int
r_int
id|status
suffix:semicolon
DECL|member|magic
r_int
r_int
id|magic
suffix:semicolon
multiline_comment|/* 0xffff = regular FPU data only */
multiline_comment|/* FXSR FPU environment */
DECL|member|_fxsr_env
r_int
r_int
id|_fxsr_env
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* FXSR FPU env is ignored */
DECL|member|mxcsr
r_int
r_int
id|mxcsr
suffix:semicolon
DECL|member|reserved
r_int
r_int
id|reserved
suffix:semicolon
DECL|member|_fxsr_st
r_struct
id|_fpxreg_ia32
id|_fxsr_st
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* FXSR FPU reg data is ignored */
DECL|member|_xmm
r_struct
id|_xmmreg_ia32
id|_xmm
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|padding
r_int
r_int
id|padding
(braket
l_int|56
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|sigcontext_ia32
r_struct
id|sigcontext_ia32
(brace
DECL|member|gs
DECL|member|__gsh
r_int
r_int
id|gs
comma
id|__gsh
suffix:semicolon
DECL|member|fs
DECL|member|__fsh
r_int
r_int
id|fs
comma
id|__fsh
suffix:semicolon
DECL|member|es
DECL|member|__esh
r_int
r_int
id|es
comma
id|__esh
suffix:semicolon
DECL|member|ds
DECL|member|__dsh
r_int
r_int
id|ds
comma
id|__dsh
suffix:semicolon
DECL|member|edi
r_int
r_int
id|edi
suffix:semicolon
DECL|member|esi
r_int
r_int
id|esi
suffix:semicolon
DECL|member|ebp
r_int
r_int
id|ebp
suffix:semicolon
DECL|member|esp
r_int
r_int
id|esp
suffix:semicolon
DECL|member|ebx
r_int
r_int
id|ebx
suffix:semicolon
DECL|member|edx
r_int
r_int
id|edx
suffix:semicolon
DECL|member|ecx
r_int
r_int
id|ecx
suffix:semicolon
DECL|member|eax
r_int
r_int
id|eax
suffix:semicolon
DECL|member|trapno
r_int
r_int
id|trapno
suffix:semicolon
DECL|member|err
r_int
r_int
id|err
suffix:semicolon
DECL|member|eip
r_int
r_int
id|eip
suffix:semicolon
DECL|member|cs
DECL|member|__csh
r_int
r_int
id|cs
comma
id|__csh
suffix:semicolon
DECL|member|eflags
r_int
r_int
id|eflags
suffix:semicolon
DECL|member|esp_at_signal
r_int
r_int
id|esp_at_signal
suffix:semicolon
DECL|member|ss
DECL|member|__ssh
r_int
r_int
id|ss
comma
id|__ssh
suffix:semicolon
DECL|member|fpstate
r_int
r_int
id|fpstate
suffix:semicolon
multiline_comment|/* really (struct _fpstate_ia32 *) */
DECL|member|oldmask
r_int
r_int
id|oldmask
suffix:semicolon
DECL|member|cr2
r_int
r_int
id|cr2
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* user.h */
multiline_comment|/*&n; * IA32 (Pentium III/4) FXSR, SSE support&n; *&n; * Provide support for the GDB 5.0+ PTRACE_{GET|SET}FPXREGS requests for&n; * interacting with the FXSR-format floating point environment.  Floating&n; * point data can be accessed in the regular format in the usual manner,&n; * and both the standard and SIMD floating point data can be accessed via&n; * the new ptrace requests.  In either case, changes to the FPU environment&n; * will be reflected in the task&squot;s state as expected.&n; */
DECL|struct|ia32_user_i387_struct
r_struct
id|ia32_user_i387_struct
(brace
DECL|member|cwd
r_int
id|cwd
suffix:semicolon
DECL|member|swd
r_int
id|swd
suffix:semicolon
DECL|member|twd
r_int
id|twd
suffix:semicolon
DECL|member|fip
r_int
id|fip
suffix:semicolon
DECL|member|fcs
r_int
id|fcs
suffix:semicolon
DECL|member|foo
r_int
id|foo
suffix:semicolon
DECL|member|fos
r_int
id|fos
suffix:semicolon
multiline_comment|/* 8*10 bytes for each FP-reg = 80 bytes */
DECL|member|st_space
r_struct
id|_fpreg_ia32
id|st_space
(braket
l_int|8
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ia32_user_fxsr_struct
r_struct
id|ia32_user_fxsr_struct
(brace
DECL|member|cwd
r_int
r_int
id|cwd
suffix:semicolon
DECL|member|swd
r_int
r_int
id|swd
suffix:semicolon
DECL|member|twd
r_int
r_int
id|twd
suffix:semicolon
DECL|member|fop
r_int
r_int
id|fop
suffix:semicolon
DECL|member|fip
r_int
id|fip
suffix:semicolon
DECL|member|fcs
r_int
id|fcs
suffix:semicolon
DECL|member|foo
r_int
id|foo
suffix:semicolon
DECL|member|fos
r_int
id|fos
suffix:semicolon
DECL|member|mxcsr
r_int
id|mxcsr
suffix:semicolon
DECL|member|reserved
r_int
id|reserved
suffix:semicolon
DECL|member|st_space
r_int
id|st_space
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* 8*16 bytes for each FP-reg = 128 bytes */
DECL|member|xmm_space
r_int
id|xmm_space
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* 8*16 bytes for each XMM-reg = 128 bytes */
DECL|member|padding
r_int
id|padding
(braket
l_int|56
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* signal.h */
DECL|macro|IA32_SET_SA_HANDLER
mdefine_line|#define IA32_SET_SA_HANDLER(ka,handler,restorer)&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;((ka)-&gt;sa.sa_handler = (__sighandler_t)&t;&t;&bslash;&n;&t;&t;&t;&t;&t;(((unsigned long)(restorer) &lt;&lt; 32)&t;&bslash;&n;&t;&t;&t;&t;&t; | ((handler) &amp; 0xffffffff)))
DECL|macro|IA32_SA_HANDLER
mdefine_line|#define IA32_SA_HANDLER(ka)&t;((unsigned long) (ka)-&gt;sa.sa_handler &amp; 0xffffffff)
DECL|macro|IA32_SA_RESTORER
mdefine_line|#define IA32_SA_RESTORER(ka)&t;((unsigned long) (ka)-&gt;sa.sa_handler &gt;&gt; 32)
DECL|macro|__IA32_NR_sigreturn
mdefine_line|#define __IA32_NR_sigreturn 119
DECL|macro|__IA32_NR_rt_sigreturn
mdefine_line|#define __IA32_NR_rt_sigreturn 173
DECL|struct|sigaction32
r_struct
id|sigaction32
(brace
DECL|member|sa_handler
r_int
r_int
id|sa_handler
suffix:semicolon
multiline_comment|/* Really a pointer, but need to deal with 32 bits */
DECL|member|sa_flags
r_int
r_int
id|sa_flags
suffix:semicolon
DECL|member|sa_restorer
r_int
r_int
id|sa_restorer
suffix:semicolon
multiline_comment|/* Another 32 bit pointer */
DECL|member|sa_mask
id|compat_sigset_t
id|sa_mask
suffix:semicolon
multiline_comment|/* A 32 bit mask */
)brace
suffix:semicolon
DECL|struct|old_sigaction32
r_struct
id|old_sigaction32
(brace
DECL|member|sa_handler
r_int
r_int
id|sa_handler
suffix:semicolon
multiline_comment|/* Really a pointer, but need to deal&n;&t;&t;&t;&t;&t;     with 32 bits */
DECL|member|sa_mask
id|compat_old_sigset_t
id|sa_mask
suffix:semicolon
multiline_comment|/* A 32 bit mask */
DECL|member|sa_flags
r_int
r_int
id|sa_flags
suffix:semicolon
DECL|member|sa_restorer
r_int
r_int
id|sa_restorer
suffix:semicolon
multiline_comment|/* Another 32 bit pointer */
)brace
suffix:semicolon
DECL|struct|sigaltstack_ia32
r_typedef
r_struct
id|sigaltstack_ia32
(brace
DECL|member|ss_sp
r_int
r_int
id|ss_sp
suffix:semicolon
DECL|member|ss_flags
r_int
id|ss_flags
suffix:semicolon
DECL|member|ss_size
r_int
r_int
id|ss_size
suffix:semicolon
DECL|typedef|stack_ia32_t
)brace
id|stack_ia32_t
suffix:semicolon
DECL|struct|ucontext_ia32
r_struct
id|ucontext_ia32
(brace
DECL|member|uc_flags
r_int
r_int
id|uc_flags
suffix:semicolon
DECL|member|uc_link
r_int
r_int
id|uc_link
suffix:semicolon
DECL|member|uc_stack
id|stack_ia32_t
id|uc_stack
suffix:semicolon
DECL|member|uc_mcontext
r_struct
id|sigcontext_ia32
id|uc_mcontext
suffix:semicolon
DECL|member|uc_sigmask
id|sigset_t
id|uc_sigmask
suffix:semicolon
multiline_comment|/* mask last for extensibility */
)brace
suffix:semicolon
DECL|struct|stat64
r_struct
id|stat64
(brace
DECL|member|st_dev
r_int
r_int
r_int
id|st_dev
suffix:semicolon
DECL|member|__pad0
r_int
r_char
id|__pad0
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|__st_ino
r_int
r_int
id|__st_ino
suffix:semicolon
DECL|member|st_mode
r_int
r_int
id|st_mode
suffix:semicolon
DECL|member|st_nlink
r_int
r_int
id|st_nlink
suffix:semicolon
DECL|member|st_uid
r_int
r_int
id|st_uid
suffix:semicolon
DECL|member|st_gid
r_int
r_int
id|st_gid
suffix:semicolon
DECL|member|st_rdev
r_int
r_int
r_int
id|st_rdev
suffix:semicolon
DECL|member|__pad3
r_int
r_char
id|__pad3
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|st_size_lo
r_int
r_int
id|st_size_lo
suffix:semicolon
DECL|member|st_size_hi
r_int
r_int
id|st_size_hi
suffix:semicolon
DECL|member|st_blksize
r_int
r_int
id|st_blksize
suffix:semicolon
DECL|member|st_blocks
r_int
r_int
id|st_blocks
suffix:semicolon
multiline_comment|/* Number 512-byte blocks allocated. */
DECL|member|__pad4
r_int
r_int
id|__pad4
suffix:semicolon
multiline_comment|/* future possible st_blocks high bits */
DECL|member|st_atime
r_int
r_int
id|st_atime
suffix:semicolon
DECL|member|st_atime_nsec
r_int
r_int
id|st_atime_nsec
suffix:semicolon
DECL|member|st_mtime
r_int
r_int
id|st_mtime
suffix:semicolon
DECL|member|st_mtime_nsec
r_int
r_int
id|st_mtime_nsec
suffix:semicolon
DECL|member|st_ctime
r_int
r_int
id|st_ctime
suffix:semicolon
DECL|member|st_ctime_nsec
r_int
r_int
id|st_ctime_nsec
suffix:semicolon
DECL|member|st_ino_lo
r_int
r_int
id|st_ino_lo
suffix:semicolon
DECL|member|st_ino_hi
r_int
r_int
id|st_ino_hi
suffix:semicolon
)brace
suffix:semicolon
DECL|union|sigval32
r_typedef
r_union
id|sigval32
(brace
DECL|member|sival_int
r_int
id|sival_int
suffix:semicolon
DECL|member|sival_ptr
r_int
r_int
id|sival_ptr
suffix:semicolon
DECL|typedef|sigval_t32
)brace
id|sigval_t32
suffix:semicolon
DECL|macro|SIGEV_PAD_SIZE32
mdefine_line|#define SIGEV_PAD_SIZE32 ((SIGEV_MAX_SIZE/sizeof(int)) - 3)
DECL|struct|compat_siginfo
r_typedef
r_struct
id|compat_siginfo
(brace
DECL|member|si_signo
r_int
id|si_signo
suffix:semicolon
DECL|member|si_errno
r_int
id|si_errno
suffix:semicolon
DECL|member|si_code
r_int
id|si_code
suffix:semicolon
r_union
(brace
DECL|member|_pad
r_int
id|_pad
(braket
(paren
(paren
l_int|128
op_div
r_sizeof
(paren
r_int
)paren
)paren
op_minus
l_int|3
)paren
)braket
suffix:semicolon
multiline_comment|/* kill() */
r_struct
(brace
DECL|member|_pid
r_int
r_int
id|_pid
suffix:semicolon
multiline_comment|/* sender&squot;s pid */
DECL|member|_uid
r_int
r_int
id|_uid
suffix:semicolon
multiline_comment|/* sender&squot;s uid */
DECL|member|_kill
)brace
id|_kill
suffix:semicolon
multiline_comment|/* POSIX.1b timers */
r_struct
(brace
DECL|member|_tid
id|timer_t
id|_tid
suffix:semicolon
multiline_comment|/* timer id */
DECL|member|_overrun
r_int
id|_overrun
suffix:semicolon
multiline_comment|/* overrun count */
DECL|member|_pad
r_char
id|_pad
(braket
r_sizeof
(paren
r_int
r_int
)paren
op_minus
r_sizeof
(paren
r_int
)paren
)braket
suffix:semicolon
DECL|member|_sigval
id|sigval_t32
id|_sigval
suffix:semicolon
multiline_comment|/* same as below */
DECL|member|_sys_private
r_int
id|_sys_private
suffix:semicolon
multiline_comment|/* not to be passed to user */
DECL|member|_timer
)brace
id|_timer
suffix:semicolon
multiline_comment|/* POSIX.1b signals */
r_struct
(brace
DECL|member|_pid
r_int
r_int
id|_pid
suffix:semicolon
multiline_comment|/* sender&squot;s pid */
DECL|member|_uid
r_int
r_int
id|_uid
suffix:semicolon
multiline_comment|/* sender&squot;s uid */
DECL|member|_sigval
id|sigval_t32
id|_sigval
suffix:semicolon
DECL|member|_rt
)brace
id|_rt
suffix:semicolon
multiline_comment|/* SIGCHLD */
r_struct
(brace
DECL|member|_pid
r_int
r_int
id|_pid
suffix:semicolon
multiline_comment|/* which child */
DECL|member|_uid
r_int
r_int
id|_uid
suffix:semicolon
multiline_comment|/* sender&squot;s uid */
DECL|member|_status
r_int
id|_status
suffix:semicolon
multiline_comment|/* exit code */
DECL|member|_utime
id|compat_clock_t
id|_utime
suffix:semicolon
DECL|member|_stime
id|compat_clock_t
id|_stime
suffix:semicolon
DECL|member|_sigchld
)brace
id|_sigchld
suffix:semicolon
multiline_comment|/* SIGILL, SIGFPE, SIGSEGV, SIGBUS */
r_struct
(brace
DECL|member|_addr
r_int
r_int
id|_addr
suffix:semicolon
multiline_comment|/* faulting insn/memory ref. */
DECL|member|_sigfault
)brace
id|_sigfault
suffix:semicolon
multiline_comment|/* SIGPOLL */
r_struct
(brace
DECL|member|_band
r_int
id|_band
suffix:semicolon
multiline_comment|/* POLL_IN, POLL_OUT, POLL_MSG */
DECL|member|_fd
r_int
id|_fd
suffix:semicolon
DECL|member|_sigpoll
)brace
id|_sigpoll
suffix:semicolon
DECL|member|_sifields
)brace
id|_sifields
suffix:semicolon
DECL|typedef|compat_siginfo_t
)brace
id|compat_siginfo_t
suffix:semicolon
DECL|struct|sigevent32
r_typedef
r_struct
id|sigevent32
(brace
DECL|member|sigev_value
id|sigval_t32
id|sigev_value
suffix:semicolon
DECL|member|sigev_signo
r_int
id|sigev_signo
suffix:semicolon
DECL|member|sigev_notify
r_int
id|sigev_notify
suffix:semicolon
r_union
(brace
DECL|member|_pad
r_int
id|_pad
(braket
id|SIGEV_PAD_SIZE32
)braket
suffix:semicolon
r_struct
(brace
DECL|member|_function
id|u32
id|_function
suffix:semicolon
DECL|member|_attribute
id|u32
id|_attribute
suffix:semicolon
multiline_comment|/* really pthread_attr_t */
DECL|member|_sigev_thread
)brace
id|_sigev_thread
suffix:semicolon
DECL|member|_sigev_un
)brace
id|_sigev_un
suffix:semicolon
DECL|typedef|sigevent_t32
)brace
id|sigevent_t32
suffix:semicolon
DECL|struct|old_linux32_dirent
r_struct
id|old_linux32_dirent
(brace
DECL|member|d_ino
id|u32
id|d_ino
suffix:semicolon
DECL|member|d_offset
id|u32
id|d_offset
suffix:semicolon
DECL|member|d_namlen
id|u16
id|d_namlen
suffix:semicolon
DECL|member|d_name
r_char
id|d_name
(braket
l_int|1
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * IA-32 ELF specific definitions for IA-64.&n; */
DECL|macro|_ASM_IA64_ELF_H
mdefine_line|#define _ASM_IA64_ELF_H&t;&t;/* Don&squot;t include elf.h */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
multiline_comment|/*&n; * This is used to ensure we don&squot;t load something for the wrong architecture.&n; */
DECL|macro|elf_check_arch
mdefine_line|#define elf_check_arch(x) ((x)-&gt;e_machine == EM_386)
multiline_comment|/*&n; * These are used to set parameters in the core dumps.&n; */
DECL|macro|ELF_CLASS
mdefine_line|#define ELF_CLASS&t;ELFCLASS32
DECL|macro|ELF_DATA
mdefine_line|#define ELF_DATA&t;ELFDATA2LSB
DECL|macro|ELF_ARCH
mdefine_line|#define ELF_ARCH&t;EM_386
DECL|macro|IA32_PAGE_OFFSET
mdefine_line|#define IA32_PAGE_OFFSET&t;0xc0000000
DECL|macro|IA32_STACK_TOP
mdefine_line|#define IA32_STACK_TOP&t;&t;IA32_PAGE_OFFSET
DECL|macro|IA32_GATE_OFFSET
mdefine_line|#define IA32_GATE_OFFSET&t;IA32_PAGE_OFFSET
DECL|macro|IA32_GATE_END
mdefine_line|#define IA32_GATE_END&t;&t;IA32_PAGE_OFFSET + PAGE_SIZE
multiline_comment|/*&n; * The system segments (GDT, TSS, LDT) have to be mapped below 4GB so the IA-32 engine can&n; * access them.&n; */
DECL|macro|IA32_GDT_OFFSET
mdefine_line|#define IA32_GDT_OFFSET&t;&t;(IA32_PAGE_OFFSET + PAGE_SIZE)
DECL|macro|IA32_TSS_OFFSET
mdefine_line|#define IA32_TSS_OFFSET&t;&t;(IA32_PAGE_OFFSET + 2*PAGE_SIZE)
DECL|macro|IA32_LDT_OFFSET
mdefine_line|#define IA32_LDT_OFFSET&t;&t;(IA32_PAGE_OFFSET + 3*PAGE_SIZE)
DECL|macro|ELF_EXEC_PAGESIZE
mdefine_line|#define ELF_EXEC_PAGESIZE&t;IA32_PAGE_SIZE
multiline_comment|/*&n; * This is the location that an ET_DYN program is loaded if exec&squot;ed.&n; * Typical use of this is to invoke &quot;./ld.so someprog&quot; to test out a&n; * new version of the loader.  We need to make sure that it is out of&n; * the way of the program that it will &quot;exec&quot;, and that there is&n; * sufficient room for the brk.&n; */
DECL|macro|ELF_ET_DYN_BASE
mdefine_line|#define ELF_ET_DYN_BASE&t;&t;(IA32_PAGE_OFFSET/3 + 0x1000000)
r_void
id|ia64_elf32_init
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
DECL|macro|ELF_PLAT_INIT
mdefine_line|#define ELF_PLAT_INIT(_r, load_addr)&t;ia64_elf32_init(_r)
DECL|macro|elf_addr_t
mdefine_line|#define elf_addr_t&t;u32
multiline_comment|/* This macro yields a bitmask that programs can use to figure out&n;   what instruction set this CPU supports.  */
DECL|macro|ELF_HWCAP
mdefine_line|#define ELF_HWCAP&t;0
multiline_comment|/* This macro yields a string that ld.so will use to load&n;   implementation specific libraries for optimization.  Not terribly&n;   relevant until we have real hardware to play with... */
DECL|macro|ELF_PLATFORM
mdefine_line|#define ELF_PLATFORM&t;NULL
macro_line|#ifdef __KERNEL__
DECL|macro|SET_PERSONALITY
macro_line|# define SET_PERSONALITY(EX,IBCS2)&t;&t;&t;&t;&bslash;&n;&t;(current-&gt;personality = (IBCS2) ? PER_SVR4 : PER_LINUX)
macro_line|#endif
DECL|macro|IA32_EFLAG
mdefine_line|#define IA32_EFLAG&t;0x200
multiline_comment|/*&n; * IA-32 ELF specific definitions for IA-64.&n; */
DECL|macro|__USER_CS
mdefine_line|#define __USER_CS      0x23
DECL|macro|__USER_DS
mdefine_line|#define __USER_DS      0x2B
multiline_comment|/*&n; * The per-cpu GDT has 32 entries: see &lt;asm-i386/segment.h&gt;&n; */
DECL|macro|GDT_ENTRIES
mdefine_line|#define GDT_ENTRIES 32
DECL|macro|GDT_SIZE
mdefine_line|#define GDT_SIZE&t;(GDT_ENTRIES * 8)
DECL|macro|TSS_ENTRY
mdefine_line|#define TSS_ENTRY 14
DECL|macro|LDT_ENTRY
mdefine_line|#define LDT_ENTRY&t;(TSS_ENTRY + 1)
DECL|macro|IA32_SEGSEL_RPL
mdefine_line|#define IA32_SEGSEL_RPL&t;&t;(0x3 &lt;&lt; 0)
DECL|macro|IA32_SEGSEL_TI
mdefine_line|#define IA32_SEGSEL_TI&t;&t;(0x1 &lt;&lt; 2)
DECL|macro|IA32_SEGSEL_INDEX_SHIFT
mdefine_line|#define IA32_SEGSEL_INDEX_SHIFT&t;3
DECL|macro|_TSS
mdefine_line|#define _TSS&t;&t;&t;((unsigned long) TSS_ENTRY &lt;&lt; IA32_SEGSEL_INDEX_SHIFT)
DECL|macro|_LDT
mdefine_line|#define _LDT&t;&t;&t;((unsigned long) LDT_ENTRY &lt;&lt; IA32_SEGSEL_INDEX_SHIFT)
DECL|macro|IA32_SEG_BASE
mdefine_line|#define IA32_SEG_BASE&t;&t;16
DECL|macro|IA32_SEG_TYPE
mdefine_line|#define IA32_SEG_TYPE&t;&t;40
DECL|macro|IA32_SEG_SYS
mdefine_line|#define IA32_SEG_SYS&t;&t;44
DECL|macro|IA32_SEG_DPL
mdefine_line|#define IA32_SEG_DPL&t;&t;45
DECL|macro|IA32_SEG_P
mdefine_line|#define IA32_SEG_P&t;&t;47
DECL|macro|IA32_SEG_HIGH_LIMIT
mdefine_line|#define IA32_SEG_HIGH_LIMIT&t;48
DECL|macro|IA32_SEG_AVL
mdefine_line|#define IA32_SEG_AVL&t;&t;52
DECL|macro|IA32_SEG_DB
mdefine_line|#define IA32_SEG_DB&t;&t;54
DECL|macro|IA32_SEG_G
mdefine_line|#define IA32_SEG_G&t;&t;55
DECL|macro|IA32_SEG_HIGH_BASE
mdefine_line|#define IA32_SEG_HIGH_BASE&t;56
DECL|macro|IA32_SEG_DESCRIPTOR
mdefine_line|#define IA32_SEG_DESCRIPTOR(base, limit, segtype, nonsysseg, dpl, segpresent, avl, segdb, gran)&t;&bslash;&n;&t;       (((limit) &amp; 0xffff)&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;| (((unsigned long) (base) &amp; 0xffffff) &lt;&lt; IA32_SEG_BASE)&t;&t;&t;&bslash;&n;&t;&t;| ((unsigned long) (segtype) &lt;&lt; IA32_SEG_TYPE)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;| ((unsigned long) (nonsysseg) &lt;&lt; IA32_SEG_SYS)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;| ((unsigned long) (dpl) &lt;&lt; IA32_SEG_DPL)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;| ((unsigned long) (segpresent) &lt;&lt; IA32_SEG_P)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;| ((((unsigned long) (limit) &gt;&gt; 16) &amp; 0xf) &lt;&lt; IA32_SEG_HIGH_LIMIT)&t;&t;&bslash;&n;&t;&t;| ((unsigned long) (avl) &lt;&lt; IA32_SEG_AVL)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;| ((unsigned long) (segdb) &lt;&lt; IA32_SEG_DB)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;| ((unsigned long) (gran) &lt;&lt; IA32_SEG_G)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;| ((((unsigned long) (base) &gt;&gt; 24) &amp; 0xff) &lt;&lt; IA32_SEG_HIGH_BASE))
DECL|macro|SEG_LIM
mdefine_line|#define SEG_LIM&t;&t;32
DECL|macro|SEG_TYPE
mdefine_line|#define SEG_TYPE&t;52
DECL|macro|SEG_SYS
mdefine_line|#define SEG_SYS&t;&t;56
DECL|macro|SEG_DPL
mdefine_line|#define SEG_DPL&t;&t;57
DECL|macro|SEG_P
mdefine_line|#define SEG_P&t;&t;59
DECL|macro|SEG_AVL
mdefine_line|#define SEG_AVL&t;&t;60
DECL|macro|SEG_DB
mdefine_line|#define SEG_DB&t;&t;62
DECL|macro|SEG_G
mdefine_line|#define SEG_G&t;&t;63
multiline_comment|/* Unscramble an IA-32 segment descriptor into the IA-64 format.  */
DECL|macro|IA32_SEG_UNSCRAMBLE
mdefine_line|#define IA32_SEG_UNSCRAMBLE(sd)&t;&t;&t;&t;&t;&t;&t;&t;&t; &bslash;&n;&t;(   (((sd) &gt;&gt; IA32_SEG_BASE) &amp; 0xffffff) | ((((sd) &gt;&gt; IA32_SEG_HIGH_BASE) &amp; 0xff) &lt;&lt; 24) &bslash;&n;&t; | ((((sd) &amp; 0xffff) | ((((sd) &gt;&gt; IA32_SEG_HIGH_LIMIT) &amp; 0xf) &lt;&lt; 16)) &lt;&lt; SEG_LIM)&t; &bslash;&n;&t; | ((((sd) &gt;&gt; IA32_SEG_TYPE) &amp; 0xf) &lt;&lt; SEG_TYPE)&t;&t;&t;&t;&t; &bslash;&n;&t; | ((((sd) &gt;&gt; IA32_SEG_SYS) &amp; 0x1) &lt;&lt; SEG_SYS)&t;&t;&t;&t;&t;&t; &bslash;&n;&t; | ((((sd) &gt;&gt; IA32_SEG_DPL) &amp; 0x3) &lt;&lt; SEG_DPL)&t;&t;&t;&t;&t;&t; &bslash;&n;&t; | ((((sd) &gt;&gt; IA32_SEG_P) &amp; 0x1) &lt;&lt; SEG_P)&t;&t;&t;&t;&t;&t; &bslash;&n;&t; | ((((sd) &gt;&gt; IA32_SEG_AVL) &amp; 0x1) &lt;&lt; SEG_AVL)&t;&t;&t;&t;&t;&t; &bslash;&n;&t; | ((((sd) &gt;&gt; IA32_SEG_DB) &amp; 0x1) &lt;&lt; SEG_DB)&t;&t;&t;&t;&t;&t; &bslash;&n;&t; | ((((sd) &gt;&gt; IA32_SEG_G) &amp; 0x1) &lt;&lt; SEG_G))
DECL|macro|IA32_IOBASE
mdefine_line|#define IA32_IOBASE&t;0x2000000000000000UL /* Virtual address for I/O space */
DECL|macro|IA32_CR0
mdefine_line|#define IA32_CR0&t;0x80000001&t;/* Enable PG and PE bits */
DECL|macro|IA32_CR4
mdefine_line|#define IA32_CR4&t;0x600&t;&t;/* MMXEX and FXSR on */
multiline_comment|/*&n; *  IA32 floating point control registers starting values&n; */
DECL|macro|IA32_FSR_DEFAULT
mdefine_line|#define IA32_FSR_DEFAULT&t;0x55550000&t;&t;/* set all tag bits */
DECL|macro|IA32_FCR_DEFAULT
mdefine_line|#define IA32_FCR_DEFAULT&t;0x17800000037fUL&t;/* extended precision, all masks */
DECL|macro|IA32_PTRACE_GETREGS
mdefine_line|#define IA32_PTRACE_GETREGS&t;12
DECL|macro|IA32_PTRACE_SETREGS
mdefine_line|#define IA32_PTRACE_SETREGS&t;13
DECL|macro|IA32_PTRACE_GETFPREGS
mdefine_line|#define IA32_PTRACE_GETFPREGS&t;14
DECL|macro|IA32_PTRACE_SETFPREGS
mdefine_line|#define IA32_PTRACE_SETFPREGS&t;15
DECL|macro|IA32_PTRACE_GETFPXREGS
mdefine_line|#define IA32_PTRACE_GETFPXREGS&t;18
DECL|macro|IA32_PTRACE_SETFPXREGS
mdefine_line|#define IA32_PTRACE_SETFPXREGS&t;19
DECL|macro|ia32_start_thread
mdefine_line|#define ia32_start_thread(regs,new_ip,new_sp) do {&t;&t;&t;&t;&bslash;&n;&t;set_fs(USER_DS);&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;ia64_psr(regs)-&gt;cpl = 3;&t;/* set user mode */&t;&t;&t;&bslash;&n;&t;ia64_psr(regs)-&gt;ri = 0;&t;&t;/* clear return slot number */&t;&t;&bslash;&n;&t;ia64_psr(regs)-&gt;is = 1;&t;&t;/* IA-32 instruction set */&t;&t;&bslash;&n;&t;regs-&gt;cr_iip = new_ip;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;regs-&gt;ar_rsc = 0xc;&t;&t;/* enforced lazy mode, priv. level 3 */&t;&bslash;&n;&t;regs-&gt;ar_rnat = 0;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;regs-&gt;loadrs = 0;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;regs-&gt;r12 = new_sp;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
multiline_comment|/*&n; * Local Descriptor Table (LDT) related declarations.&n; */
DECL|macro|IA32_LDT_ENTRIES
mdefine_line|#define IA32_LDT_ENTRIES&t;8192&t;&t;/* Maximum number of LDT entries supported. */
DECL|macro|IA32_LDT_ENTRY_SIZE
mdefine_line|#define IA32_LDT_ENTRY_SIZE&t;8&t;&t;/* The size of each LDT entry. */
DECL|macro|LDT_entry_a
mdefine_line|#define LDT_entry_a(info) &bslash;&n;&t;((((info)-&gt;base_addr &amp; 0x0000ffff) &lt;&lt; 16) | ((info)-&gt;limit &amp; 0x0ffff))
DECL|macro|LDT_entry_b
mdefine_line|#define LDT_entry_b(info)&t;&t;&t;&t;&bslash;&n;&t;(((info)-&gt;base_addr &amp; 0xff000000) |&t;&t;&bslash;&n;&t;(((info)-&gt;base_addr &amp; 0x00ff0000) &gt;&gt; 16) |&t;&bslash;&n;&t;((info)-&gt;limit &amp; 0xf0000) |&t;&t;&t;&bslash;&n;&t;(((info)-&gt;read_exec_only ^ 1) &lt;&lt; 9) |&t;&t;&bslash;&n;&t;((info)-&gt;contents &lt;&lt; 10) |&t;&t;&t;&bslash;&n;&t;(((info)-&gt;seg_not_present ^ 1) &lt;&lt; 15) |&t;&t;&bslash;&n;&t;((info)-&gt;seg_32bit &lt;&lt; 22) |&t;&t;&t;&bslash;&n;&t;((info)-&gt;limit_in_pages &lt;&lt; 23) |&t;&t;&bslash;&n;&t;((info)-&gt;useable &lt;&lt; 20) |&t;&t;&t;&bslash;&n;&t;0x7100)
DECL|macro|LDT_empty
mdefine_line|#define LDT_empty(info) (&t;&t;&t;&bslash;&n;&t;(info)-&gt;base_addr&t;== 0&t;&amp;&amp;&t;&bslash;&n;&t;(info)-&gt;limit&t;&t;== 0&t;&amp;&amp;&t;&bslash;&n;&t;(info)-&gt;contents&t;== 0&t;&amp;&amp;&t;&bslash;&n;&t;(info)-&gt;read_exec_only&t;== 1&t;&amp;&amp;&t;&bslash;&n;&t;(info)-&gt;seg_32bit&t;== 0&t;&amp;&amp;&t;&bslash;&n;&t;(info)-&gt;limit_in_pages&t;== 0&t;&amp;&amp;&t;&bslash;&n;&t;(info)-&gt;seg_not_present&t;== 1&t;&amp;&amp;&t;&bslash;&n;&t;(info)-&gt;useable&t;&t;== 0&t;)
r_static
r_inline
r_void
DECL|function|load_TLS
id|load_TLS
(paren
r_struct
id|thread_struct
op_star
id|t
comma
r_int
r_int
id|cpu
)paren
(brace
r_extern
r_int
r_int
op_star
id|cpu_gdt_table
(braket
id|NR_CPUS
)braket
suffix:semicolon
id|memcpy
c_func
(paren
id|cpu_gdt_table
(braket
id|cpu
)braket
op_plus
id|GDT_ENTRY_TLS_MIN
op_plus
l_int|0
comma
op_amp
id|t-&gt;tls_array
(braket
l_int|0
)braket
comma
r_sizeof
(paren
r_int
)paren
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|cpu_gdt_table
(braket
id|cpu
)braket
op_plus
id|GDT_ENTRY_TLS_MIN
op_plus
l_int|1
comma
op_amp
id|t-&gt;tls_array
(braket
l_int|1
)braket
comma
r_sizeof
(paren
r_int
)paren
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|cpu_gdt_table
(braket
id|cpu
)braket
op_plus
id|GDT_ENTRY_TLS_MIN
op_plus
l_int|2
comma
op_amp
id|t-&gt;tls_array
(braket
l_int|2
)braket
comma
r_sizeof
(paren
r_int
)paren
)paren
suffix:semicolon
)brace
DECL|struct|ia32_user_desc
r_struct
id|ia32_user_desc
(brace
DECL|member|entry_number
r_int
r_int
id|entry_number
suffix:semicolon
DECL|member|base_addr
r_int
r_int
id|base_addr
suffix:semicolon
DECL|member|limit
r_int
r_int
id|limit
suffix:semicolon
DECL|member|seg_32bit
r_int
r_int
id|seg_32bit
suffix:colon
l_int|1
suffix:semicolon
DECL|member|contents
r_int
r_int
id|contents
suffix:colon
l_int|2
suffix:semicolon
DECL|member|read_exec_only
r_int
r_int
id|read_exec_only
suffix:colon
l_int|1
suffix:semicolon
DECL|member|limit_in_pages
r_int
r_int
id|limit_in_pages
suffix:colon
l_int|1
suffix:semicolon
DECL|member|seg_not_present
r_int
r_int
id|seg_not_present
suffix:colon
l_int|1
suffix:semicolon
DECL|member|useable
r_int
r_int
id|useable
suffix:colon
l_int|1
suffix:semicolon
)brace
suffix:semicolon
r_struct
id|linux_binprm
suffix:semicolon
r_extern
r_void
id|ia32_init_addr_space
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_extern
r_int
id|ia32_setup_arg_pages
(paren
r_struct
id|linux_binprm
op_star
id|bprm
comma
r_int
id|exec_stack
)paren
suffix:semicolon
r_extern
r_int
r_int
id|ia32_do_mmap
(paren
r_struct
id|file
op_star
comma
r_int
r_int
comma
r_int
r_int
comma
r_int
comma
r_int
comma
id|loff_t
)paren
suffix:semicolon
r_extern
r_void
id|ia32_load_segment_descriptors
(paren
r_struct
id|task_struct
op_star
id|task
)paren
suffix:semicolon
DECL|macro|ia32f2ia64f
mdefine_line|#define ia32f2ia64f(dst,src)&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;ia64_ldfe(6,src);&t;&t;&t;&bslash;&n;&t;ia64_stop();&t;&t;&t;&t;&bslash;&n;&t;ia64_stf_spill(dst, 6);&t;&t;&t;&bslash;&n;} while(0)
DECL|macro|ia64f2ia32f
mdefine_line|#define ia64f2ia32f(dst,src)&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;ia64_ldf_fill(6, src);&t;&t;&t;&bslash;&n;&t;ia64_stop();&t;&t;&t;&t;&bslash;&n;&t;ia64_stfe(dst, 6);&t;&t;&t;&bslash;&n;} while(0)
DECL|struct|user_regs_struct32
r_struct
id|user_regs_struct32
(brace
DECL|member|ebx
DECL|member|ecx
DECL|member|edx
DECL|member|esi
DECL|member|edi
DECL|member|ebp
DECL|member|eax
id|__u32
id|ebx
comma
id|ecx
comma
id|edx
comma
id|esi
comma
id|edi
comma
id|ebp
comma
id|eax
suffix:semicolon
DECL|member|ds
DECL|member|__ds
DECL|member|es
DECL|member|__es
r_int
r_int
id|ds
comma
id|__ds
comma
id|es
comma
id|__es
suffix:semicolon
DECL|member|fs
DECL|member|__fs
DECL|member|gs
DECL|member|__gs
r_int
r_int
id|fs
comma
id|__fs
comma
id|gs
comma
id|__gs
suffix:semicolon
DECL|member|orig_eax
DECL|member|eip
id|__u32
id|orig_eax
comma
id|eip
suffix:semicolon
DECL|member|cs
DECL|member|__cs
r_int
r_int
id|cs
comma
id|__cs
suffix:semicolon
DECL|member|eflags
DECL|member|esp
id|__u32
id|eflags
comma
id|esp
suffix:semicolon
DECL|member|ss
DECL|member|__ss
r_int
r_int
id|ss
comma
id|__ss
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Prototypes for use in elfcore32.h */
r_extern
r_int
id|save_ia32_fpstate
(paren
r_struct
id|task_struct
op_star
comma
r_struct
id|ia32_user_i387_struct
id|__user
op_star
)paren
suffix:semicolon
r_extern
r_int
id|save_ia32_fpxstate
(paren
r_struct
id|task_struct
op_star
comma
r_struct
id|ia32_user_fxsr_struct
id|__user
op_star
)paren
suffix:semicolon
macro_line|#endif /* !CONFIG_IA32_SUPPORT */
macro_line|#endif /* _ASM_IA64_IA32_PRIV_H */
eof
