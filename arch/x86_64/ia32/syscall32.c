multiline_comment|/* Copyright 2002,2003 Andi Kleen, SuSE Labs */
multiline_comment|/* vsyscall handling for 32bit processes. Map a stub page into it &n;   on demand because 32bit cannot reach the kernel&squot;s fixmaps */
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/gfp.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/stringify.h&gt;
macro_line|#include &lt;asm/proto.h&gt;
macro_line|#include &lt;asm/tlbflush.h&gt;
macro_line|#include &lt;asm/ia32_unistd.h&gt;
multiline_comment|/* 32bit SYSCALL stub mapped into user space. */
id|asm
c_func
(paren
l_string|&quot;&t;.code32&bslash;n&quot;
l_string|&quot;&bslash;nsyscall32:&bslash;n&quot;
l_string|&quot;&t;pushl %ebp&bslash;n&quot;
l_string|&quot;&t;movl  %ecx,%ebp&bslash;n&quot;
l_string|&quot;&t;syscall&bslash;n&quot;
l_string|&quot;&t;popl  %ebp&bslash;n&quot;
l_string|&quot;&t;ret&bslash;n&quot;
l_string|&quot;syscall32_end:&bslash;n&quot;
multiline_comment|/* signal trampolines */
l_string|&quot;sig32_rt_tramp:&bslash;n&quot;
l_string|&quot;&t;movl $&quot;
id|__stringify
c_func
(paren
id|__NR_ia32_rt_sigreturn
)paren
l_string|&quot;,%eax&bslash;n&quot;
l_string|&quot;   int $0x80&bslash;n&quot;
l_string|&quot;sig32_rt_tramp_end:&bslash;n&quot;
l_string|&quot;sig32_tramp:&bslash;n&quot;
l_string|&quot;&t;popl %eax&bslash;n&quot;
l_string|&quot;&t;movl $&quot;
id|__stringify
c_func
(paren
id|__NR_ia32_sigreturn
)paren
l_string|&quot;,%eax&bslash;n&quot;
l_string|&quot;&t;int $0x80&bslash;n&quot;
l_string|&quot;sig32_tramp_end:&bslash;n&quot;
l_string|&quot;&t;.code64&bslash;n&quot;
)paren
suffix:semicolon
r_extern
r_int
r_char
id|syscall32
(braket
)braket
comma
id|syscall32_end
(braket
)braket
suffix:semicolon
r_extern
r_int
r_char
id|sig32_rt_tramp
(braket
)braket
comma
id|sig32_rt_tramp_end
(braket
)braket
suffix:semicolon
r_extern
r_int
r_char
id|sig32_tramp
(braket
)braket
comma
id|sig32_tramp_end
(braket
)braket
suffix:semicolon
DECL|variable|syscall32_page
r_char
op_star
id|syscall32_page
suffix:semicolon
multiline_comment|/* RED-PEN: This knows too much about high level VM */
multiline_comment|/* Alternative would be to generate a vma with appropiate backing options&n;   and let it be handled by generic VM */
DECL|function|map_syscall32
r_int
id|map_syscall32
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_int
r_int
id|address
)paren
(brace
id|pte_t
op_star
id|pte
suffix:semicolon
r_int
id|err
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
id|spin_lock
c_func
(paren
op_amp
id|mm-&gt;page_table_lock
)paren
suffix:semicolon
id|pmd_t
op_star
id|pmd
op_assign
id|pmd_alloc
c_func
(paren
id|mm
comma
id|pgd_offset
c_func
(paren
id|mm
comma
id|address
)paren
comma
id|address
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pmd
op_logical_and
(paren
id|pte
op_assign
id|pte_alloc_map
c_func
(paren
id|mm
comma
id|pmd
comma
id|address
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|pte_none
c_func
(paren
op_star
id|pte
)paren
)paren
(brace
id|set_pte
c_func
(paren
id|pte
comma
id|mk_pte
c_func
(paren
id|virt_to_page
c_func
(paren
id|syscall32_page
)paren
comma
id|PAGE_KERNEL_VSYSCALL
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Flush only the local CPU. Other CPUs taking a fault&n;&t;&t;   will just end up here again */
id|__flush_tlb_one
c_func
(paren
id|address
)paren
suffix:semicolon
)brace
r_else
id|err
op_assign
op_minus
id|ENOMEM
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|mm-&gt;page_table_lock
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
id|err
suffix:semicolon
)brace
DECL|function|init_syscall32
r_static
r_int
id|__init
id|init_syscall32
c_func
(paren
r_void
)paren
(brace
id|syscall32_page
op_assign
(paren
r_void
op_star
)paren
id|get_zeroed_page
c_func
(paren
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|syscall32_page
)paren
id|panic
c_func
(paren
l_string|&quot;Cannot allocate syscall32 page&quot;
)paren
suffix:semicolon
id|SetPageReserved
c_func
(paren
id|virt_to_page
c_func
(paren
id|syscall32_page
)paren
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|syscall32_page
comma
id|syscall32
comma
id|syscall32_end
op_minus
id|syscall32
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|syscall32_page
op_plus
l_int|32
comma
id|sig32_rt_tramp
comma
id|sig32_rt_tramp_end
op_minus
id|sig32_rt_tramp
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|syscall32_page
op_plus
l_int|64
comma
id|sig32_tramp
comma
id|sig32_tramp_end
op_minus
id|sig32_tramp
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|init_syscall32
id|__initcall
c_func
(paren
id|init_syscall32
)paren
suffix:semicolon
eof
