multiline_comment|/*&n; *  linux/drivers/char/mem.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; *&n; *  Added devfs support. &n; *    Jan-11-1998, C. Scott Ananian &lt;cananian@alumni.princeton.edu&gt;&n; *  Shared /dev/zero mmaping support, Feb 2000, Kanoj Sarcar &lt;kanoj@sgi.com&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;linux/tpqic02.h&gt;
macro_line|#include &lt;linux/ftape.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/mman.h&gt;
macro_line|#include &lt;linux/random.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/raw.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/capability.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/devfs_fs_kernel.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#ifdef CONFIG_IA64
macro_line|# include &lt;linux/efi.h&gt;
macro_line|#endif
macro_line|#ifdef CONFIG_FB
r_extern
r_void
id|fbmem_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if defined(CONFIG_S390_TAPE) &amp;&amp; defined(CONFIG_S390_TAPE_CHAR)
r_extern
r_void
id|tapechar_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Architectures vary in how they handle caching for addresses&n; * outside of main memory.&n; *&n; */
DECL|function|uncached_access
r_static
r_inline
r_int
id|uncached_access
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_int
r_int
id|addr
)paren
(brace
macro_line|#if defined(__i386__)
multiline_comment|/*&n;&t; * On the PPro and successors, the MTRRs are used to set&n;&t; * memory types for physical addresses outside main memory,&n;&t; * so blindly setting PCD or PWT on those pages is wrong.&n;&t; * For Pentiums and earlier, the surround logic should disable&n;&t; * caching for the high addresses through the KEN pin, but&n;&t; * we maintain the tradition of paranoia in this code.&n;&t; */
r_if
c_cond
(paren
id|file-&gt;f_flags
op_amp
id|O_SYNC
)paren
r_return
l_int|1
suffix:semicolon
r_return
op_logical_neg
(paren
id|test_bit
c_func
(paren
id|X86_FEATURE_MTRR
comma
id|boot_cpu_data.x86_capability
)paren
op_logical_or
id|test_bit
c_func
(paren
id|X86_FEATURE_K6_MTRR
comma
id|boot_cpu_data.x86_capability
)paren
op_logical_or
id|test_bit
c_func
(paren
id|X86_FEATURE_CYRIX_ARR
comma
id|boot_cpu_data.x86_capability
)paren
op_logical_or
id|test_bit
c_func
(paren
id|X86_FEATURE_CENTAUR_MCR
comma
id|boot_cpu_data.x86_capability
)paren
)paren
op_logical_and
id|addr
op_ge
id|__pa
c_func
(paren
id|high_memory
)paren
suffix:semicolon
macro_line|#elif defined(CONFIG_IA64)
multiline_comment|/*&n;&t; * On ia64, we ignore O_SYNC because we cannot tolerate memory attribute aliases.&n;&t; */
r_return
op_logical_neg
(paren
id|efi_mem_attributes
c_func
(paren
id|addr
)paren
op_amp
id|EFI_MEMORY_WB
)paren
suffix:semicolon
macro_line|#else
multiline_comment|/*&n;&t; * Accessing memory above the top the kernel knows about or through a file pointer&n;&t; * that was marked O_SYNC will be done non-cached.&n;&t; */
r_if
c_cond
(paren
id|file-&gt;f_flags
op_amp
id|O_SYNC
)paren
r_return
l_int|1
suffix:semicolon
r_return
id|addr
op_ge
id|__pa
c_func
(paren
id|high_memory
)paren
suffix:semicolon
macro_line|#endif
)brace
macro_line|#ifndef ARCH_HAS_VALID_PHYS_ADDR_RANGE
DECL|function|valid_phys_addr_range
r_static
r_inline
r_int
id|valid_phys_addr_range
c_func
(paren
r_int
r_int
id|addr
comma
r_int
op_star
id|count
)paren
(brace
r_int
r_int
id|end_mem
suffix:semicolon
id|end_mem
op_assign
id|__pa
c_func
(paren
id|high_memory
)paren
suffix:semicolon
r_if
c_cond
(paren
id|addr
op_ge
id|end_mem
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_star
id|count
OG
id|end_mem
op_minus
id|addr
)paren
op_star
id|count
op_assign
id|end_mem
op_minus
id|addr
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
macro_line|#endif
DECL|function|do_write_mem
r_static
id|ssize_t
id|do_write_mem
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_void
op_star
id|p
comma
r_int
r_int
id|realp
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
id|ssize_t
id|written
suffix:semicolon
id|written
op_assign
l_int|0
suffix:semicolon
macro_line|#if defined(__sparc__) || (defined(__mc68000__) &amp;&amp; defined(CONFIG_MMU))
multiline_comment|/* we don&squot;t have page 0 mapped on sparc and m68k.. */
r_if
c_cond
(paren
id|realp
OL
id|PAGE_SIZE
)paren
(brace
r_int
r_int
id|sz
op_assign
id|PAGE_SIZE
op_minus
id|realp
suffix:semicolon
r_if
c_cond
(paren
id|sz
OG
id|count
)paren
id|sz
op_assign
id|count
suffix:semicolon
multiline_comment|/* Hmm. Do something? */
id|buf
op_add_assign
id|sz
suffix:semicolon
id|p
op_add_assign
id|sz
suffix:semicolon
id|count
op_sub_assign
id|sz
suffix:semicolon
id|written
op_add_assign
id|sz
suffix:semicolon
)brace
macro_line|#endif
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|p
comma
id|buf
comma
id|count
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|written
op_add_assign
id|count
suffix:semicolon
op_star
id|ppos
op_add_assign
id|written
suffix:semicolon
r_return
id|written
suffix:semicolon
)brace
multiline_comment|/*&n; * This funcion reads the *physical* memory. The f_pos points directly to the &n; * memory location. &n; */
DECL|function|read_mem
r_static
id|ssize_t
id|read_mem
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
r_if
c_cond
(paren
op_logical_neg
id|valid_phys_addr_range
c_func
(paren
id|p
comma
op_amp
id|count
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|read
op_assign
l_int|0
suffix:semicolon
macro_line|#if defined(__sparc__) || (defined(__mc68000__) &amp;&amp; defined(CONFIG_MMU))
multiline_comment|/* we don&squot;t have page 0 mapped on sparc and m68k.. */
r_if
c_cond
(paren
id|p
OL
id|PAGE_SIZE
)paren
(brace
r_int
r_int
id|sz
op_assign
id|PAGE_SIZE
op_minus
id|p
suffix:semicolon
r_if
c_cond
(paren
id|sz
OG
id|count
)paren
id|sz
op_assign
id|count
suffix:semicolon
r_if
c_cond
(paren
id|sz
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|clear_user
c_func
(paren
id|buf
comma
id|sz
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|buf
op_add_assign
id|sz
suffix:semicolon
id|p
op_add_assign
id|sz
suffix:semicolon
id|count
op_sub_assign
id|sz
suffix:semicolon
id|read
op_add_assign
id|sz
suffix:semicolon
)brace
)brace
macro_line|#endif
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|buf
comma
id|__va
c_func
(paren
id|p
)paren
comma
id|count
)paren
)paren
r_return
op_minus
id|EFAULT
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
DECL|function|write_mem
r_static
id|ssize_t
id|write_mem
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
r_int
r_int
id|p
op_assign
op_star
id|ppos
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|valid_phys_addr_range
c_func
(paren
id|p
comma
op_amp
id|count
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
id|do_write_mem
c_func
(paren
id|file
comma
id|__va
c_func
(paren
id|p
)paren
comma
id|p
comma
id|buf
comma
id|count
comma
id|ppos
)paren
suffix:semicolon
)brace
DECL|function|mmap_mem
r_static
r_int
id|mmap_mem
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_struct
id|vm_area_struct
op_star
id|vma
)paren
(brace
r_int
r_int
id|offset
op_assign
id|vma-&gt;vm_pgoff
op_lshift
id|PAGE_SHIFT
suffix:semicolon
r_int
id|uncached
suffix:semicolon
id|uncached
op_assign
id|uncached_access
c_func
(paren
id|file
comma
id|offset
)paren
suffix:semicolon
macro_line|#ifdef pgprot_noncached
r_if
c_cond
(paren
id|uncached
)paren
id|vma-&gt;vm_page_prot
op_assign
id|pgprot_noncached
c_func
(paren
id|vma-&gt;vm_page_prot
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Don&squot;t try to swap out physical pages.. */
id|vma-&gt;vm_flags
op_or_assign
id|VM_RESERVED
suffix:semicolon
multiline_comment|/*&n;&t; * Don&squot;t dump addresses that are not real memory to a core file.&n;&t; */
r_if
c_cond
(paren
id|uncached
)paren
id|vma-&gt;vm_flags
op_or_assign
id|VM_IO
suffix:semicolon
r_if
c_cond
(paren
id|remap_page_range
c_func
(paren
id|vma
comma
id|vma-&gt;vm_start
comma
id|offset
comma
id|vma-&gt;vm_end
op_minus
id|vma-&gt;vm_start
comma
id|vma-&gt;vm_page_prot
)paren
)paren
r_return
op_minus
id|EAGAIN
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_extern
r_int
id|vread
c_func
(paren
r_char
op_star
id|buf
comma
r_char
op_star
id|addr
comma
r_int
r_int
id|count
)paren
suffix:semicolon
r_extern
r_int
id|vwrite
c_func
(paren
r_char
op_star
id|buf
comma
r_char
op_star
id|addr
comma
r_int
r_int
id|count
)paren
suffix:semicolon
multiline_comment|/*&n; * This function reads the *virtual* memory as seen by the kernel.&n; */
DECL|function|read_kmem
r_static
id|ssize_t
id|read_kmem
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
op_assign
l_int|0
suffix:semicolon
id|ssize_t
id|virtr
op_assign
l_int|0
suffix:semicolon
r_char
op_star
id|kbuf
suffix:semicolon
multiline_comment|/* k-addr because vread() takes vmlist_lock rwlock */
r_if
c_cond
(paren
id|p
OL
(paren
r_int
r_int
)paren
id|high_memory
)paren
(brace
id|read
op_assign
id|count
suffix:semicolon
r_if
c_cond
(paren
id|count
OG
(paren
r_int
r_int
)paren
id|high_memory
op_minus
id|p
)paren
id|read
op_assign
(paren
r_int
r_int
)paren
id|high_memory
op_minus
id|p
suffix:semicolon
macro_line|#if defined(__sparc__) || (defined(__mc68000__) &amp;&amp; defined(CONFIG_MMU))
multiline_comment|/* we don&squot;t have page 0 mapped on sparc and m68k.. */
r_if
c_cond
(paren
id|p
template_param
l_int|0
)paren
(brace
r_int
id|tmp
op_assign
id|PAGE_SIZE
op_minus
id|p
suffix:semicolon
r_if
c_cond
(paren
id|tmp
OG
id|read
)paren
id|tmp
op_assign
id|read
suffix:semicolon
r_if
c_cond
(paren
id|clear_user
c_func
(paren
id|buf
comma
id|tmp
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|buf
op_add_assign
id|tmp
suffix:semicolon
id|p
op_add_assign
id|tmp
suffix:semicolon
id|read
op_sub_assign
id|tmp
suffix:semicolon
id|count
op_sub_assign
id|tmp
suffix:semicolon
)brace
macro_line|#endif
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|buf
comma
(paren
r_char
op_star
)paren
id|p
comma
id|read
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|p
op_add_assign
id|read
suffix:semicolon
id|buf
op_add_assign
id|read
suffix:semicolon
id|count
op_sub_assign
id|read
suffix:semicolon
)brace
r_if
c_cond
(paren
id|count
OG
l_int|0
)paren
(brace
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
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_while
c_loop
(paren
id|count
OG
l_int|0
)paren
(brace
r_int
id|len
op_assign
id|count
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
id|PAGE_SIZE
)paren
id|len
op_assign
id|PAGE_SIZE
suffix:semicolon
id|len
op_assign
id|vread
c_func
(paren
id|kbuf
comma
(paren
r_char
op_star
)paren
id|p
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|len
)paren
r_break
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
id|len
)paren
)paren
(brace
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
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|count
op_sub_assign
id|len
suffix:semicolon
id|buf
op_add_assign
id|len
suffix:semicolon
id|virtr
op_add_assign
id|len
suffix:semicolon
id|p
op_add_assign
id|len
suffix:semicolon
)brace
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
)brace
op_star
id|ppos
op_assign
id|p
suffix:semicolon
r_return
id|virtr
op_plus
id|read
suffix:semicolon
)brace
multiline_comment|/*&n; * This function writes to the *virtual* memory as seen by the kernel.&n; */
DECL|function|write_kmem
r_static
id|ssize_t
id|write_kmem
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
r_int
r_int
id|p
op_assign
op_star
id|ppos
suffix:semicolon
id|ssize_t
id|wrote
op_assign
l_int|0
suffix:semicolon
id|ssize_t
id|virtr
op_assign
l_int|0
suffix:semicolon
r_char
op_star
id|kbuf
suffix:semicolon
multiline_comment|/* k-addr because vwrite() takes vmlist_lock rwlock */
r_if
c_cond
(paren
id|p
OL
(paren
r_int
r_int
)paren
id|high_memory
)paren
(brace
id|wrote
op_assign
id|count
suffix:semicolon
r_if
c_cond
(paren
id|count
OG
(paren
r_int
r_int
)paren
id|high_memory
op_minus
id|p
)paren
id|wrote
op_assign
(paren
r_int
r_int
)paren
id|high_memory
op_minus
id|p
suffix:semicolon
id|wrote
op_assign
id|do_write_mem
c_func
(paren
id|file
comma
(paren
r_void
op_star
)paren
id|p
comma
id|p
comma
id|buf
comma
id|wrote
comma
id|ppos
)paren
suffix:semicolon
id|p
op_add_assign
id|wrote
suffix:semicolon
id|buf
op_add_assign
id|wrote
suffix:semicolon
id|count
op_sub_assign
id|wrote
suffix:semicolon
)brace
r_if
c_cond
(paren
id|count
OG
l_int|0
)paren
(brace
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
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_while
c_loop
(paren
id|count
OG
l_int|0
)paren
(brace
r_int
id|len
op_assign
id|count
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
id|PAGE_SIZE
)paren
id|len
op_assign
id|PAGE_SIZE
suffix:semicolon
r_if
c_cond
(paren
id|len
op_logical_and
id|copy_from_user
c_func
(paren
id|kbuf
comma
id|buf
comma
id|len
)paren
)paren
(brace
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
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|len
op_assign
id|vwrite
c_func
(paren
id|kbuf
comma
(paren
r_char
op_star
)paren
id|p
comma
id|len
)paren
suffix:semicolon
id|count
op_sub_assign
id|len
suffix:semicolon
id|buf
op_add_assign
id|len
suffix:semicolon
id|virtr
op_add_assign
id|len
suffix:semicolon
id|p
op_add_assign
id|len
suffix:semicolon
)brace
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
)brace
op_star
id|ppos
op_assign
id|p
suffix:semicolon
r_return
id|virtr
op_plus
id|wrote
suffix:semicolon
)brace
macro_line|#if defined(CONFIG_ISA) || !defined(__mc68000__)
DECL|function|read_port
r_static
id|ssize_t
id|read_port
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
id|i
op_assign
op_star
id|ppos
suffix:semicolon
r_char
op_star
id|tmp
op_assign
id|buf
suffix:semicolon
r_if
c_cond
(paren
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
id|buf
comma
id|count
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_while
c_loop
(paren
id|count
op_decrement
OG
l_int|0
op_logical_and
id|i
OL
l_int|65536
)paren
(brace
r_if
c_cond
(paren
id|__put_user
c_func
(paren
id|inb
c_func
(paren
id|i
)paren
comma
id|tmp
)paren
OL
l_int|0
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|i
op_increment
suffix:semicolon
id|tmp
op_increment
suffix:semicolon
)brace
op_star
id|ppos
op_assign
id|i
suffix:semicolon
r_return
id|tmp
op_minus
id|buf
suffix:semicolon
)brace
DECL|function|write_port
r_static
id|ssize_t
id|write_port
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
r_int
r_int
id|i
op_assign
op_star
id|ppos
suffix:semicolon
r_const
r_char
op_star
id|tmp
op_assign
id|buf
suffix:semicolon
r_if
c_cond
(paren
id|verify_area
c_func
(paren
id|VERIFY_READ
comma
id|buf
comma
id|count
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_while
c_loop
(paren
id|count
op_decrement
OG
l_int|0
op_logical_and
id|i
OL
l_int|65536
)paren
(brace
r_char
id|c
suffix:semicolon
r_if
c_cond
(paren
id|__get_user
c_func
(paren
id|c
comma
id|tmp
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|outb
c_func
(paren
id|c
comma
id|i
)paren
suffix:semicolon
id|i
op_increment
suffix:semicolon
id|tmp
op_increment
suffix:semicolon
)brace
op_star
id|ppos
op_assign
id|i
suffix:semicolon
r_return
id|tmp
op_minus
id|buf
suffix:semicolon
)brace
macro_line|#endif
DECL|function|read_null
r_static
id|ssize_t
id|read_null
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
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|write_null
r_static
id|ssize_t
id|write_null
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
r_return
id|count
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_MMU
multiline_comment|/*&n; * For fun, we are using the MMU for this.&n; */
DECL|function|read_zero_pagealigned
r_static
r_inline
r_int
id|read_zero_pagealigned
c_func
(paren
r_char
op_star
id|buf
comma
r_int
id|size
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
id|vma
suffix:semicolon
r_int
r_int
id|addr
op_assign
(paren
r_int
r_int
)paren
id|buf
suffix:semicolon
id|mm
op_assign
id|current-&gt;mm
suffix:semicolon
multiline_comment|/* Oops, this was forgotten before. -ben */
id|down_read
c_func
(paren
op_amp
id|mm-&gt;mmap_sem
)paren
suffix:semicolon
multiline_comment|/* For private mappings, just map in zero pages. */
r_for
c_loop
(paren
id|vma
op_assign
id|find_vma
c_func
(paren
id|mm
comma
id|addr
)paren
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
id|count
suffix:semicolon
r_if
c_cond
(paren
id|vma-&gt;vm_start
OG
id|addr
op_logical_or
(paren
id|vma-&gt;vm_flags
op_amp
id|VM_WRITE
)paren
op_eq
l_int|0
)paren
r_goto
id|out_up
suffix:semicolon
r_if
c_cond
(paren
id|vma-&gt;vm_flags
op_amp
id|VM_SHARED
)paren
r_break
suffix:semicolon
id|count
op_assign
id|vma-&gt;vm_end
op_minus
id|addr
suffix:semicolon
r_if
c_cond
(paren
id|count
OG
id|size
)paren
id|count
op_assign
id|size
suffix:semicolon
id|zap_page_range
c_func
(paren
id|vma
comma
id|addr
comma
id|count
)paren
suffix:semicolon
id|zeromap_page_range
c_func
(paren
id|vma
comma
id|addr
comma
id|count
comma
id|PAGE_COPY
)paren
suffix:semicolon
id|size
op_sub_assign
id|count
suffix:semicolon
id|buf
op_add_assign
id|count
suffix:semicolon
id|addr
op_add_assign
id|count
suffix:semicolon
r_if
c_cond
(paren
id|size
op_eq
l_int|0
)paren
r_goto
id|out_up
suffix:semicolon
)brace
id|up_read
c_func
(paren
op_amp
id|mm-&gt;mmap_sem
)paren
suffix:semicolon
multiline_comment|/* The shared case is hard. Let&squot;s do the conventional zeroing. */
r_do
(brace
r_int
r_int
id|unwritten
op_assign
id|clear_user
c_func
(paren
id|buf
comma
id|PAGE_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unwritten
)paren
r_return
id|size
op_plus
id|unwritten
op_minus
id|PAGE_SIZE
suffix:semicolon
id|cond_resched
c_func
(paren
)paren
suffix:semicolon
id|buf
op_add_assign
id|PAGE_SIZE
suffix:semicolon
id|size
op_sub_assign
id|PAGE_SIZE
suffix:semicolon
)brace
r_while
c_loop
(paren
id|size
)paren
suffix:semicolon
r_return
id|size
suffix:semicolon
id|out_up
suffix:colon
id|up_read
c_func
(paren
op_amp
id|mm-&gt;mmap_sem
)paren
suffix:semicolon
r_return
id|size
suffix:semicolon
)brace
DECL|function|read_zero
r_static
id|ssize_t
id|read_zero
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
id|left
comma
id|unwritten
comma
id|written
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|count
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|access_ok
c_func
(paren
id|VERIFY_WRITE
comma
id|buf
comma
id|count
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|left
op_assign
id|count
suffix:semicolon
multiline_comment|/* do we want to be clever? Arbitrary cut-off */
r_if
c_cond
(paren
id|count
op_ge
id|PAGE_SIZE
op_star
l_int|4
)paren
(brace
r_int
r_int
id|partial
suffix:semicolon
multiline_comment|/* How much left of the page? */
id|partial
op_assign
(paren
id|PAGE_SIZE
op_minus
l_int|1
)paren
op_amp
op_minus
(paren
r_int
r_int
)paren
id|buf
suffix:semicolon
id|unwritten
op_assign
id|clear_user
c_func
(paren
id|buf
comma
id|partial
)paren
suffix:semicolon
id|written
op_assign
id|partial
op_minus
id|unwritten
suffix:semicolon
r_if
c_cond
(paren
id|unwritten
)paren
r_goto
id|out
suffix:semicolon
id|left
op_sub_assign
id|partial
suffix:semicolon
id|buf
op_add_assign
id|partial
suffix:semicolon
id|unwritten
op_assign
id|read_zero_pagealigned
c_func
(paren
id|buf
comma
id|left
op_amp
id|PAGE_MASK
)paren
suffix:semicolon
id|written
op_add_assign
(paren
id|left
op_amp
id|PAGE_MASK
)paren
op_minus
id|unwritten
suffix:semicolon
r_if
c_cond
(paren
id|unwritten
)paren
r_goto
id|out
suffix:semicolon
id|buf
op_add_assign
id|left
op_amp
id|PAGE_MASK
suffix:semicolon
id|left
op_and_assign
op_complement
id|PAGE_MASK
suffix:semicolon
)brace
id|unwritten
op_assign
id|clear_user
c_func
(paren
id|buf
comma
id|left
)paren
suffix:semicolon
id|written
op_add_assign
id|left
op_minus
id|unwritten
suffix:semicolon
id|out
suffix:colon
r_return
id|written
ques
c_cond
id|written
suffix:colon
op_minus
id|EFAULT
suffix:semicolon
)brace
DECL|function|mmap_zero
r_static
r_int
id|mmap_zero
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_struct
id|vm_area_struct
op_star
id|vma
)paren
(brace
r_if
c_cond
(paren
id|vma-&gt;vm_flags
op_amp
id|VM_SHARED
)paren
r_return
id|shmem_zero_setup
c_func
(paren
id|vma
)paren
suffix:semicolon
r_if
c_cond
(paren
id|zeromap_page_range
c_func
(paren
id|vma
comma
id|vma-&gt;vm_start
comma
id|vma-&gt;vm_end
op_minus
id|vma-&gt;vm_start
comma
id|vma-&gt;vm_page_prot
)paren
)paren
r_return
op_minus
id|EAGAIN
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#else /* CONFIG_MMU */
DECL|function|read_zero
r_static
id|ssize_t
id|read_zero
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
id|todo
op_assign
id|count
suffix:semicolon
r_while
c_loop
(paren
id|todo
)paren
(brace
r_int
id|chunk
op_assign
id|todo
suffix:semicolon
r_if
c_cond
(paren
id|chunk
OG
l_int|4096
)paren
id|chunk
op_assign
l_int|4096
suffix:semicolon
multiline_comment|/* Just for latency reasons */
r_if
c_cond
(paren
id|clear_user
c_func
(paren
id|buf
comma
id|chunk
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|buf
op_add_assign
id|chunk
suffix:semicolon
id|todo
op_sub_assign
id|chunk
suffix:semicolon
id|cond_resched
c_func
(paren
)paren
suffix:semicolon
)brace
r_return
id|count
suffix:semicolon
)brace
DECL|function|mmap_zero
r_static
r_int
id|mmap_zero
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_struct
id|vm_area_struct
op_star
id|vma
)paren
(brace
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_MMU */
DECL|function|write_full
r_static
id|ssize_t
id|write_full
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
r_return
op_minus
id|ENOSPC
suffix:semicolon
)brace
multiline_comment|/*&n; * Special lseek() function for /dev/null and /dev/zero.  Most notably, you&n; * can fopen() both devices with &quot;a&quot; now.  This was previously impossible.&n; * -- SRB.&n; */
DECL|function|null_lseek
r_static
id|loff_t
id|null_lseek
c_func
(paren
r_struct
id|file
op_star
id|file
comma
id|loff_t
id|offset
comma
r_int
id|orig
)paren
(brace
r_return
id|file-&gt;f_pos
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * The memory devices use the full 32/64 bits of the offset, and so we cannot&n; * check against negative addresses: they are ok. The return value is weird,&n; * though, in that case (0).&n; *&n; * also note that seeking relative to the &quot;end of file&quot; isn&squot;t supported:&n; * it has no meaning, so it returns -EINVAL.&n; */
DECL|function|memory_lseek
r_static
id|loff_t
id|memory_lseek
c_func
(paren
r_struct
id|file
op_star
id|file
comma
id|loff_t
id|offset
comma
r_int
id|orig
)paren
(brace
id|loff_t
id|ret
suffix:semicolon
id|down
c_func
(paren
op_amp
id|file-&gt;f_dentry-&gt;d_inode-&gt;i_sem
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|orig
)paren
(brace
r_case
l_int|0
suffix:colon
id|file-&gt;f_pos
op_assign
id|offset
suffix:semicolon
id|ret
op_assign
id|file-&gt;f_pos
suffix:semicolon
id|force_successful_syscall_return
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|file-&gt;f_pos
op_add_assign
id|offset
suffix:semicolon
id|ret
op_assign
id|file-&gt;f_pos
suffix:semicolon
id|force_successful_syscall_return
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
id|file-&gt;f_dentry-&gt;d_inode-&gt;i_sem
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|open_port
r_static
r_int
id|open_port
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|filp
)paren
(brace
r_return
id|capable
c_func
(paren
id|CAP_SYS_RAWIO
)paren
ques
c_cond
l_int|0
suffix:colon
op_minus
id|EPERM
suffix:semicolon
)brace
DECL|macro|mmap_kmem
mdefine_line|#define mmap_kmem&t;mmap_mem
DECL|macro|zero_lseek
mdefine_line|#define zero_lseek&t;null_lseek
DECL|macro|full_lseek
mdefine_line|#define full_lseek      null_lseek
DECL|macro|write_zero
mdefine_line|#define write_zero&t;write_null
DECL|macro|read_full
mdefine_line|#define read_full       read_zero
DECL|macro|open_mem
mdefine_line|#define open_mem&t;open_port
DECL|macro|open_kmem
mdefine_line|#define open_kmem&t;open_mem
DECL|variable|mem_fops
r_static
r_struct
id|file_operations
id|mem_fops
op_assign
(brace
dot
id|llseek
op_assign
id|memory_lseek
comma
dot
id|read
op_assign
id|read_mem
comma
dot
id|write
op_assign
id|write_mem
comma
dot
id|mmap
op_assign
id|mmap_mem
comma
dot
id|open
op_assign
id|open_mem
comma
)brace
suffix:semicolon
DECL|variable|kmem_fops
r_static
r_struct
id|file_operations
id|kmem_fops
op_assign
(brace
dot
id|llseek
op_assign
id|memory_lseek
comma
dot
id|read
op_assign
id|read_kmem
comma
dot
id|write
op_assign
id|write_kmem
comma
dot
id|mmap
op_assign
id|mmap_kmem
comma
dot
id|open
op_assign
id|open_kmem
comma
)brace
suffix:semicolon
DECL|variable|null_fops
r_static
r_struct
id|file_operations
id|null_fops
op_assign
(brace
dot
id|llseek
op_assign
id|null_lseek
comma
dot
id|read
op_assign
id|read_null
comma
dot
id|write
op_assign
id|write_null
comma
)brace
suffix:semicolon
macro_line|#if defined(CONFIG_ISA) || !defined(__mc68000__)
DECL|variable|port_fops
r_static
r_struct
id|file_operations
id|port_fops
op_assign
(brace
dot
id|llseek
op_assign
id|memory_lseek
comma
dot
id|read
op_assign
id|read_port
comma
dot
id|write
op_assign
id|write_port
comma
dot
id|open
op_assign
id|open_port
comma
)brace
suffix:semicolon
macro_line|#endif
DECL|variable|zero_fops
r_static
r_struct
id|file_operations
id|zero_fops
op_assign
(brace
dot
id|llseek
op_assign
id|zero_lseek
comma
dot
id|read
op_assign
id|read_zero
comma
dot
id|write
op_assign
id|write_zero
comma
dot
id|mmap
op_assign
id|mmap_zero
comma
)brace
suffix:semicolon
DECL|variable|full_fops
r_static
r_struct
id|file_operations
id|full_fops
op_assign
(brace
dot
id|llseek
op_assign
id|full_lseek
comma
dot
id|read
op_assign
id|read_full
comma
dot
id|write
op_assign
id|write_full
comma
)brace
suffix:semicolon
DECL|function|kmsg_write
r_static
id|ssize_t
id|kmsg_write
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
r_char
op_star
id|tmp
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|tmp
op_assign
id|kmalloc
c_func
(paren
id|count
op_plus
l_int|1
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|ret
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|copy_from_user
c_func
(paren
id|tmp
comma
id|buf
comma
id|count
)paren
)paren
(brace
id|tmp
(braket
id|count
)braket
op_assign
l_int|0
suffix:semicolon
id|ret
op_assign
id|printk
c_func
(paren
l_string|&quot;%s&quot;
comma
id|tmp
)paren
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|tmp
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|kmsg_fops
r_static
r_struct
id|file_operations
id|kmsg_fops
op_assign
(brace
dot
id|write
op_assign
id|kmsg_write
comma
)brace
suffix:semicolon
DECL|function|memory_open
r_static
r_int
id|memory_open
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|filp
)paren
(brace
r_switch
c_cond
(paren
id|iminor
c_func
(paren
id|inode
)paren
)paren
(brace
r_case
l_int|1
suffix:colon
id|filp-&gt;f_op
op_assign
op_amp
id|mem_fops
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|filp-&gt;f_op
op_assign
op_amp
id|kmem_fops
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|filp-&gt;f_op
op_assign
op_amp
id|null_fops
suffix:semicolon
r_break
suffix:semicolon
macro_line|#if defined(CONFIG_ISA) || !defined(__mc68000__)
r_case
l_int|4
suffix:colon
id|filp-&gt;f_op
op_assign
op_amp
id|port_fops
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
r_case
l_int|5
suffix:colon
id|filp-&gt;f_op
op_assign
op_amp
id|zero_fops
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|7
suffix:colon
id|filp-&gt;f_op
op_assign
op_amp
id|full_fops
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|8
suffix:colon
id|filp-&gt;f_op
op_assign
op_amp
id|random_fops
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|9
suffix:colon
id|filp-&gt;f_op
op_assign
op_amp
id|urandom_fops
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|11
suffix:colon
id|filp-&gt;f_op
op_assign
op_amp
id|kmsg_fops
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
r_if
c_cond
(paren
id|filp-&gt;f_op
op_logical_and
id|filp-&gt;f_op-&gt;open
)paren
r_return
id|filp-&gt;f_op
op_member_access_from_pointer
id|open
c_func
(paren
id|inode
comma
id|filp
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|memory_fops
r_static
r_struct
id|file_operations
id|memory_fops
op_assign
(brace
dot
id|open
op_assign
id|memory_open
comma
multiline_comment|/* just a selector for the real open */
)brace
suffix:semicolon
r_static
r_const
r_struct
(brace
DECL|member|minor
r_int
r_int
id|minor
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|mode
id|umode_t
id|mode
suffix:semicolon
DECL|member|fops
r_struct
id|file_operations
op_star
id|fops
suffix:semicolon
DECL|variable|devlist
)brace
id|devlist
(braket
)braket
op_assign
(brace
multiline_comment|/* list of minor devices */
(brace
l_int|1
comma
l_string|&quot;mem&quot;
comma
id|S_IRUSR
op_or
id|S_IWUSR
op_or
id|S_IRGRP
comma
op_amp
id|mem_fops
)brace
comma
(brace
l_int|2
comma
l_string|&quot;kmem&quot;
comma
id|S_IRUSR
op_or
id|S_IWUSR
op_or
id|S_IRGRP
comma
op_amp
id|kmem_fops
)brace
comma
(brace
l_int|3
comma
l_string|&quot;null&quot;
comma
id|S_IRUGO
op_or
id|S_IWUGO
comma
op_amp
id|null_fops
)brace
comma
macro_line|#if defined(CONFIG_ISA) || !defined(__mc68000__)
(brace
l_int|4
comma
l_string|&quot;port&quot;
comma
id|S_IRUSR
op_or
id|S_IWUSR
op_or
id|S_IRGRP
comma
op_amp
id|port_fops
)brace
comma
macro_line|#endif
(brace
l_int|5
comma
l_string|&quot;zero&quot;
comma
id|S_IRUGO
op_or
id|S_IWUGO
comma
op_amp
id|zero_fops
)brace
comma
(brace
l_int|7
comma
l_string|&quot;full&quot;
comma
id|S_IRUGO
op_or
id|S_IWUGO
comma
op_amp
id|full_fops
)brace
comma
(brace
l_int|8
comma
l_string|&quot;random&quot;
comma
id|S_IRUGO
op_or
id|S_IWUSR
comma
op_amp
id|random_fops
)brace
comma
(brace
l_int|9
comma
l_string|&quot;urandom&quot;
comma
id|S_IRUGO
op_or
id|S_IWUSR
comma
op_amp
id|urandom_fops
)brace
comma
(brace
l_int|11
comma
l_string|&quot;kmsg&quot;
comma
id|S_IRUGO
op_or
id|S_IWUSR
comma
op_amp
id|kmsg_fops
)brace
comma
)brace
suffix:semicolon
DECL|function|chr_dev_init
r_static
r_int
id|__init
id|chr_dev_init
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|register_chrdev
c_func
(paren
id|MEM_MAJOR
comma
l_string|&quot;mem&quot;
comma
op_amp
id|memory_fops
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;unable to get major %d for memory devs&bslash;n&quot;
comma
id|MEM_MAJOR
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
id|ARRAY_SIZE
c_func
(paren
id|devlist
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
id|devfs_mk_cdev
c_func
(paren
id|MKDEV
c_func
(paren
id|MEM_MAJOR
comma
id|devlist
(braket
id|i
)braket
dot
id|minor
)paren
comma
id|S_IFCHR
op_or
id|devlist
(braket
id|i
)braket
dot
id|mode
comma
id|devlist
(braket
id|i
)braket
dot
id|name
)paren
suffix:semicolon
)brace
macro_line|#if defined (CONFIG_FB)
id|fbmem_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|chr_dev_init
id|fs_initcall
c_func
(paren
id|chr_dev_init
)paren
suffix:semicolon
eof
