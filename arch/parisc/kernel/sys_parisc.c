multiline_comment|/*&n; *    PARISC specific syscalls&n; *&n; *    Copyright (C) 1999-2003 Matthew Wilcox &lt;willy at parisc-linux.org&gt;&n; *    Copyright (C) 2000-2003 Paul Bame &lt;bame at parisc-linux.org&gt;&n; *    Copyright (C) 2001 Thomas Bogendoerfer &lt;tsbogend at parisc-linux.org&gt;&n; *&n; *&n; *    This program is free software; you can redistribute it and/or modify&n; *    it under the terms of the GNU General Public License as published by&n; *    the Free Software Foundation; either version 2 of the License, or&n; *    (at your option) any later version.&n; *&n; *    This program is distributed in the hope that it will be useful,&n; *    but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *    GNU General Public License for more details.&n; *&n; *    You should have received a copy of the GNU General Public License&n; *    along with this program; if not, write to the Free Software&n; *    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/file.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/linkage.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/mman.h&gt;
macro_line|#include &lt;linux/shm.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/syscalls.h&gt;
DECL|function|sys_pipe
r_int
id|sys_pipe
c_func
(paren
r_int
op_star
id|fildes
)paren
(brace
r_int
id|fd
(braket
l_int|2
)braket
suffix:semicolon
r_int
id|error
suffix:semicolon
id|error
op_assign
id|do_pipe
c_func
(paren
id|fd
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
(brace
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|fildes
comma
id|fd
comma
l_int|2
op_star
r_sizeof
(paren
r_int
)paren
)paren
)paren
id|error
op_assign
op_minus
id|EFAULT
suffix:semicolon
)brace
r_return
id|error
suffix:semicolon
)brace
DECL|function|get_unshared_area
r_static
r_int
r_int
id|get_unshared_area
c_func
(paren
r_int
r_int
id|addr
comma
r_int
r_int
id|len
)paren
(brace
r_struct
id|vm_area_struct
op_star
id|vma
suffix:semicolon
id|addr
op_assign
id|PAGE_ALIGN
c_func
(paren
id|addr
)paren
suffix:semicolon
r_for
c_loop
(paren
id|vma
op_assign
id|find_vma
c_func
(paren
id|current-&gt;mm
comma
id|addr
)paren
suffix:semicolon
suffix:semicolon
id|vma
op_assign
id|vma-&gt;vm_next
)paren
(brace
multiline_comment|/* At this point:  (!vma || addr &lt; vma-&gt;vm_end). */
r_if
c_cond
(paren
id|TASK_SIZE
op_minus
id|len
OL
id|addr
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|vma
op_logical_or
id|addr
op_plus
id|len
op_le
id|vma-&gt;vm_start
)paren
r_return
id|addr
suffix:semicolon
id|addr
op_assign
id|vma-&gt;vm_end
suffix:semicolon
)brace
)brace
DECL|macro|DCACHE_ALIGN
mdefine_line|#define DCACHE_ALIGN(addr) (((addr) + (SHMLBA - 1)) &amp;~ (SHMLBA - 1))
multiline_comment|/*&n; * We need to know the offset to use.  Old scheme was to look for&n; * existing mapping and use the same offset.  New scheme is to use the&n; * address of the kernel data structure as the seed for the offset.&n; * We&squot;ll see how that works...&n; */
macro_line|#if 0
r_static
r_int
id|get_offset
c_func
(paren
r_struct
id|address_space
op_star
id|mapping
)paren
(brace
r_struct
id|vm_area_struct
op_star
id|vma
op_assign
id|list_entry
c_func
(paren
id|mapping-&gt;i_mmap_shared.next
comma
r_struct
id|vm_area_struct
comma
id|shared
)paren
suffix:semicolon
r_return
(paren
id|vma-&gt;vm_start
op_plus
(paren
(paren
id|pgoff
op_minus
id|vma-&gt;vm_pgoff
)paren
op_lshift
id|PAGE_SHIFT
)paren
)paren
op_amp
(paren
id|SHMLBA
op_minus
l_int|1
)paren
suffix:semicolon
)brace
macro_line|#else
multiline_comment|/* The mapping is cacheline aligned, so there&squot;s no information in the bottom&n; * few bits of the address.  We&squot;re looking for 10 bits (4MB / 4k), so let&squot;s&n; * drop the bottom 8 bits and use bits 8-17.  &n; */
DECL|function|get_offset
r_static
r_int
id|get_offset
c_func
(paren
r_struct
id|address_space
op_star
id|mapping
)paren
(brace
r_int
id|offset
op_assign
(paren
r_int
r_int
)paren
id|mapping
op_lshift
(paren
id|PAGE_SHIFT
op_minus
l_int|8
)paren
suffix:semicolon
r_return
id|offset
op_amp
l_int|0x3FF000
suffix:semicolon
)brace
macro_line|#endif
DECL|function|get_shared_area
r_static
r_int
r_int
id|get_shared_area
c_func
(paren
r_struct
id|address_space
op_star
id|mapping
comma
r_int
r_int
id|addr
comma
r_int
r_int
id|len
comma
r_int
r_int
id|pgoff
)paren
(brace
r_struct
id|vm_area_struct
op_star
id|vma
suffix:semicolon
r_int
id|offset
op_assign
id|get_offset
c_func
(paren
id|mapping
)paren
suffix:semicolon
id|addr
op_assign
id|DCACHE_ALIGN
c_func
(paren
id|addr
op_minus
id|offset
)paren
op_plus
id|offset
suffix:semicolon
r_for
c_loop
(paren
id|vma
op_assign
id|find_vma
c_func
(paren
id|current-&gt;mm
comma
id|addr
)paren
suffix:semicolon
suffix:semicolon
id|vma
op_assign
id|vma-&gt;vm_next
)paren
(brace
multiline_comment|/* At this point:  (!vma || addr &lt; vma-&gt;vm_end). */
r_if
c_cond
(paren
id|TASK_SIZE
op_minus
id|len
OL
id|addr
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|vma
op_logical_or
id|addr
op_plus
id|len
op_le
id|vma-&gt;vm_start
)paren
r_return
id|addr
suffix:semicolon
id|addr
op_assign
id|DCACHE_ALIGN
c_func
(paren
id|vma-&gt;vm_end
op_minus
id|offset
)paren
op_plus
id|offset
suffix:semicolon
r_if
c_cond
(paren
id|addr
OL
id|vma-&gt;vm_end
)paren
multiline_comment|/* handle wraparound */
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
)brace
DECL|function|arch_get_unmapped_area
r_int
r_int
id|arch_get_unmapped_area
c_func
(paren
r_struct
id|file
op_star
id|filp
comma
r_int
r_int
id|addr
comma
r_int
r_int
id|len
comma
r_int
r_int
id|pgoff
comma
r_int
r_int
id|flags
)paren
(brace
r_if
c_cond
(paren
id|len
OG
id|TASK_SIZE
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|addr
)paren
id|addr
op_assign
id|TASK_UNMAPPED_BASE
suffix:semicolon
r_if
c_cond
(paren
id|filp
op_logical_and
(paren
id|flags
op_amp
id|MAP_SHARED
)paren
)paren
(brace
id|addr
op_assign
id|get_shared_area
c_func
(paren
id|filp-&gt;f_mapping
comma
id|addr
comma
id|len
comma
id|pgoff
)paren
suffix:semicolon
)brace
r_else
(brace
id|addr
op_assign
id|get_unshared_area
c_func
(paren
id|addr
comma
id|len
)paren
suffix:semicolon
)brace
r_return
id|addr
suffix:semicolon
)brace
DECL|function|do_mmap2
r_static
r_int
r_int
id|do_mmap2
c_func
(paren
r_int
r_int
id|addr
comma
r_int
r_int
id|len
comma
r_int
r_int
id|prot
comma
r_int
r_int
id|flags
comma
r_int
r_int
id|fd
comma
r_int
r_int
id|pgoff
)paren
(brace
r_struct
id|file
op_star
id|file
op_assign
l_int|NULL
suffix:semicolon
r_int
r_int
id|error
op_assign
op_minus
id|EBADF
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|flags
op_amp
id|MAP_ANONYMOUS
)paren
)paren
(brace
id|file
op_assign
id|fget
c_func
(paren
id|fd
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|file
)paren
r_goto
id|out
suffix:semicolon
)brace
id|flags
op_and_assign
op_complement
(paren
id|MAP_EXECUTABLE
op_or
id|MAP_DENYWRITE
)paren
suffix:semicolon
id|down_write
c_func
(paren
op_amp
id|current-&gt;mm-&gt;mmap_sem
)paren
suffix:semicolon
id|error
op_assign
id|do_mmap_pgoff
c_func
(paren
id|file
comma
id|addr
comma
id|len
comma
id|prot
comma
id|flags
comma
id|pgoff
)paren
suffix:semicolon
id|up_write
c_func
(paren
op_amp
id|current-&gt;mm-&gt;mmap_sem
)paren
suffix:semicolon
r_if
c_cond
(paren
id|file
op_ne
l_int|NULL
)paren
id|fput
c_func
(paren
id|file
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|error
suffix:semicolon
)brace
DECL|function|sys_mmap2
id|asmlinkage
r_int
r_int
id|sys_mmap2
c_func
(paren
r_int
r_int
id|addr
comma
r_int
r_int
id|len
comma
r_int
r_int
id|prot
comma
r_int
r_int
id|flags
comma
r_int
r_int
id|fd
comma
r_int
r_int
id|pgoff
)paren
(brace
multiline_comment|/* Make sure the shift for mmap2 is constant (12), no matter what PAGE_SIZE&n;&t;   we have. */
r_return
id|do_mmap2
c_func
(paren
id|addr
comma
id|len
comma
id|prot
comma
id|flags
comma
id|fd
comma
id|pgoff
op_rshift
(paren
id|PAGE_SHIFT
op_minus
l_int|12
)paren
)paren
suffix:semicolon
)brace
DECL|function|sys_mmap
id|asmlinkage
r_int
r_int
id|sys_mmap
c_func
(paren
r_int
r_int
id|addr
comma
r_int
r_int
id|len
comma
r_int
r_int
id|prot
comma
r_int
r_int
id|flags
comma
r_int
r_int
id|fd
comma
r_int
r_int
id|offset
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|offset
op_amp
op_complement
id|PAGE_MASK
)paren
)paren
(brace
r_return
id|do_mmap2
c_func
(paren
id|addr
comma
id|len
comma
id|prot
comma
id|flags
comma
id|fd
comma
id|offset
op_rshift
id|PAGE_SHIFT
)paren
suffix:semicolon
)brace
r_else
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
)brace
DECL|function|sys_shmat_wrapper
r_int
id|sys_shmat_wrapper
c_func
(paren
r_int
id|shmid
comma
r_char
op_star
id|shmaddr
comma
r_int
id|shmflag
)paren
(brace
r_int
r_int
id|raddr
suffix:semicolon
r_int
id|r
suffix:semicolon
id|r
op_assign
id|do_shmat
c_func
(paren
id|shmid
comma
id|shmaddr
comma
id|shmflag
comma
op_amp
id|raddr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r
OL
l_int|0
)paren
r_return
id|r
suffix:semicolon
r_return
id|raddr
suffix:semicolon
)brace
multiline_comment|/* Fucking broken ABI */
macro_line|#ifdef CONFIG_PARISC64
DECL|function|parisc_truncate64
id|asmlinkage
r_int
id|parisc_truncate64
c_func
(paren
r_const
r_char
op_star
id|path
comma
r_int
r_int
id|high
comma
r_int
r_int
id|low
)paren
(brace
r_return
id|sys_truncate
c_func
(paren
id|path
comma
(paren
r_int
)paren
id|high
op_lshift
l_int|32
op_or
id|low
)paren
suffix:semicolon
)brace
DECL|function|parisc_ftruncate64
id|asmlinkage
r_int
id|parisc_ftruncate64
c_func
(paren
r_int
r_int
id|fd
comma
r_int
r_int
id|high
comma
r_int
r_int
id|low
)paren
(brace
r_return
id|sys_ftruncate
c_func
(paren
id|fd
comma
(paren
r_int
)paren
id|high
op_lshift
l_int|32
op_or
id|low
)paren
suffix:semicolon
)brace
multiline_comment|/* stubs for the benefit of the syscall_table since truncate64 and truncate &n; * are identical on LP64 */
DECL|function|sys_truncate64
id|asmlinkage
r_int
id|sys_truncate64
c_func
(paren
r_const
r_char
op_star
id|path
comma
r_int
r_int
id|length
)paren
(brace
r_return
id|sys_truncate
c_func
(paren
id|path
comma
id|length
)paren
suffix:semicolon
)brace
DECL|function|sys_ftruncate64
id|asmlinkage
r_int
id|sys_ftruncate64
c_func
(paren
r_int
r_int
id|fd
comma
r_int
r_int
id|length
)paren
(brace
r_return
id|sys_ftruncate
c_func
(paren
id|fd
comma
id|length
)paren
suffix:semicolon
)brace
DECL|function|sys_fcntl64
id|asmlinkage
r_int
id|sys_fcntl64
c_func
(paren
r_int
r_int
id|fd
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
r_return
id|sys_fcntl
c_func
(paren
id|fd
comma
id|cmd
comma
id|arg
)paren
suffix:semicolon
)brace
macro_line|#else
DECL|function|parisc_truncate64
id|asmlinkage
r_int
id|parisc_truncate64
c_func
(paren
r_const
r_char
op_star
id|path
comma
r_int
r_int
id|high
comma
r_int
r_int
id|low
)paren
(brace
r_return
id|sys_truncate64
c_func
(paren
id|path
comma
(paren
id|loff_t
)paren
id|high
op_lshift
l_int|32
op_or
id|low
)paren
suffix:semicolon
)brace
DECL|function|parisc_ftruncate64
id|asmlinkage
r_int
id|parisc_ftruncate64
c_func
(paren
r_int
r_int
id|fd
comma
r_int
r_int
id|high
comma
r_int
r_int
id|low
)paren
(brace
r_return
id|sys_ftruncate64
c_func
(paren
id|fd
comma
(paren
id|loff_t
)paren
id|high
op_lshift
l_int|32
op_or
id|low
)paren
suffix:semicolon
)brace
macro_line|#endif
DECL|function|parisc_pread64
id|asmlinkage
id|ssize_t
id|parisc_pread64
c_func
(paren
r_int
r_int
id|fd
comma
r_char
op_star
id|buf
comma
r_int
id|count
comma
r_int
r_int
id|high
comma
r_int
r_int
id|low
)paren
(brace
r_return
id|sys_pread64
c_func
(paren
id|fd
comma
id|buf
comma
id|count
comma
(paren
id|loff_t
)paren
id|high
op_lshift
l_int|32
op_or
id|low
)paren
suffix:semicolon
)brace
DECL|function|parisc_pwrite64
id|asmlinkage
id|ssize_t
id|parisc_pwrite64
c_func
(paren
r_int
r_int
id|fd
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|count
comma
r_int
r_int
id|high
comma
r_int
r_int
id|low
)paren
(brace
r_return
id|sys_pwrite64
c_func
(paren
id|fd
comma
id|buf
comma
id|count
comma
(paren
id|loff_t
)paren
id|high
op_lshift
l_int|32
op_or
id|low
)paren
suffix:semicolon
)brace
DECL|function|parisc_readahead
id|asmlinkage
id|ssize_t
id|parisc_readahead
c_func
(paren
r_int
id|fd
comma
r_int
r_int
id|high
comma
r_int
r_int
id|low
comma
r_int
id|count
)paren
(brace
r_return
id|sys_readahead
c_func
(paren
id|fd
comma
(paren
id|loff_t
)paren
id|high
op_lshift
l_int|32
op_or
id|low
comma
id|count
)paren
suffix:semicolon
)brace
DECL|function|sys_alloc_hugepages
id|asmlinkage
r_int
r_int
id|sys_alloc_hugepages
c_func
(paren
r_int
id|key
comma
r_int
r_int
id|addr
comma
r_int
r_int
id|len
comma
r_int
id|prot
comma
r_int
id|flag
)paren
(brace
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
DECL|function|sys_free_hugepages
id|asmlinkage
r_int
id|sys_free_hugepages
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
eof
