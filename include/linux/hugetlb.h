macro_line|#ifndef _LINUX_HUGETLB_H
DECL|macro|_LINUX_HUGETLB_H
mdefine_line|#define _LINUX_HUGETLB_H
macro_line|#ifdef CONFIG_HUGETLB_PAGE
r_struct
id|ctl_table
suffix:semicolon
DECL|function|is_vm_hugetlb_page
r_static
r_inline
r_int
id|is_vm_hugetlb_page
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
)paren
(brace
r_return
id|vma-&gt;vm_flags
op_amp
id|VM_HUGETLB
suffix:semicolon
)brace
r_int
id|hugetlb_sysctl_handler
c_func
(paren
r_struct
id|ctl_table
op_star
comma
r_int
comma
r_struct
id|file
op_star
comma
r_void
op_star
comma
r_int
op_star
)paren
suffix:semicolon
r_int
id|copy_hugetlb_page_range
c_func
(paren
r_struct
id|mm_struct
op_star
comma
r_struct
id|mm_struct
op_star
comma
r_struct
id|vm_area_struct
op_star
)paren
suffix:semicolon
r_int
id|follow_hugetlb_page
c_func
(paren
r_struct
id|mm_struct
op_star
comma
r_struct
id|vm_area_struct
op_star
comma
r_struct
id|page
op_star
op_star
comma
r_struct
id|vm_area_struct
op_star
op_star
comma
r_int
r_int
op_star
comma
r_int
op_star
comma
r_int
)paren
suffix:semicolon
r_void
id|zap_hugepage_range
c_func
(paren
r_struct
id|vm_area_struct
op_star
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_void
id|unmap_hugepage_range
c_func
(paren
r_struct
id|vm_area_struct
op_star
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_int
id|hugetlb_prefault
c_func
(paren
r_struct
id|address_space
op_star
comma
r_struct
id|vm_area_struct
op_star
)paren
suffix:semicolon
r_void
id|huge_page_release
c_func
(paren
r_struct
id|page
op_star
)paren
suffix:semicolon
r_int
id|hugetlb_report_meminfo
c_func
(paren
r_char
op_star
)paren
suffix:semicolon
r_int
id|is_hugepage_mem_enough
c_func
(paren
r_int
)paren
suffix:semicolon
r_struct
id|page
op_star
id|follow_huge_addr
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|address
comma
r_int
id|write
)paren
suffix:semicolon
r_struct
id|vm_area_struct
op_star
id|hugepage_vma
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
suffix:semicolon
r_struct
id|page
op_star
id|follow_huge_pmd
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
comma
id|pmd_t
op_star
id|pmd
comma
r_int
id|write
)paren
suffix:semicolon
r_int
id|is_aligned_hugepage_range
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
suffix:semicolon
r_int
id|pmd_huge
c_func
(paren
id|pmd_t
id|pmd
)paren
suffix:semicolon
r_extern
r_int
id|htlbpage_max
suffix:semicolon
r_static
r_inline
r_void
DECL|function|mark_mm_hugetlb
id|mark_mm_hugetlb
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
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
id|is_vm_hugetlb_page
c_func
(paren
id|vma
)paren
)paren
id|mm-&gt;used_hugetlb
op_assign
l_int|1
suffix:semicolon
)brace
macro_line|#ifndef ARCH_HAS_HUGEPAGE_ONLY_RANGE
DECL|macro|is_hugepage_only_range
mdefine_line|#define is_hugepage_only_range(addr, len)&t;0
macro_line|#endif
macro_line|#else /* !CONFIG_HUGETLB_PAGE */
DECL|function|is_vm_hugetlb_page
r_static
r_inline
r_int
id|is_vm_hugetlb_page
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|macro|follow_hugetlb_page
mdefine_line|#define follow_hugetlb_page(m,v,p,vs,a,b,i)&t;({ BUG(); 0; })
DECL|macro|follow_huge_addr
mdefine_line|#define follow_huge_addr(mm, vma, addr, write)&t;0
DECL|macro|copy_hugetlb_page_range
mdefine_line|#define copy_hugetlb_page_range(src, dst, vma)&t;({ BUG(); 0; })
DECL|macro|hugetlb_prefault
mdefine_line|#define hugetlb_prefault(mapping, vma)&t;&t;({ BUG(); 0; })
DECL|macro|zap_hugepage_range
mdefine_line|#define zap_hugepage_range(vma, start, len)&t;BUG()
DECL|macro|unmap_hugepage_range
mdefine_line|#define unmap_hugepage_range(vma, start, end)&t;BUG()
DECL|macro|huge_page_release
mdefine_line|#define huge_page_release(page)&t;&t;&t;BUG()
DECL|macro|is_hugepage_mem_enough
mdefine_line|#define is_hugepage_mem_enough(size)&t;&t;0
DECL|macro|hugetlb_report_meminfo
mdefine_line|#define hugetlb_report_meminfo(buf)&t;&t;0
DECL|macro|hugepage_vma
mdefine_line|#define hugepage_vma(mm, addr)&t;&t;&t;0
DECL|macro|mark_mm_hugetlb
mdefine_line|#define mark_mm_hugetlb(mm, vma)&t;&t;do { } while (0)
DECL|macro|follow_huge_pmd
mdefine_line|#define follow_huge_pmd(mm, addr, pmd, write)&t;0
DECL|macro|is_aligned_hugepage_range
mdefine_line|#define is_aligned_hugepage_range(addr, len)&t;0
DECL|macro|pmd_huge
mdefine_line|#define pmd_huge(x)&t;0
DECL|macro|is_hugepage_only_range
mdefine_line|#define is_hugepage_only_range(addr, len)&t;0
macro_line|#ifndef HPAGE_MASK
DECL|macro|HPAGE_MASK
mdefine_line|#define HPAGE_MASK&t;0&t;&t;/* Keep the compiler happy */
DECL|macro|HPAGE_SIZE
mdefine_line|#define HPAGE_SIZE&t;0
macro_line|#endif
macro_line|#endif /* !CONFIG_HUGETLB_PAGE */
macro_line|#ifdef CONFIG_HUGETLBFS
DECL|struct|hugetlbfs_config
r_struct
id|hugetlbfs_config
(brace
DECL|member|uid
id|uid_t
id|uid
suffix:semicolon
DECL|member|gid
id|gid_t
id|gid
suffix:semicolon
DECL|member|mode
id|umode_t
id|mode
suffix:semicolon
DECL|member|nr_blocks
r_int
id|nr_blocks
suffix:semicolon
DECL|member|nr_inodes
r_int
id|nr_inodes
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|hugetlbfs_sb_info
r_struct
id|hugetlbfs_sb_info
(brace
DECL|member|max_blocks
r_int
id|max_blocks
suffix:semicolon
multiline_comment|/* blocks allowed */
DECL|member|free_blocks
r_int
id|free_blocks
suffix:semicolon
multiline_comment|/* blocks free */
DECL|member|max_inodes
r_int
id|max_inodes
suffix:semicolon
multiline_comment|/* inodes allowed */
DECL|member|free_inodes
r_int
id|free_inodes
suffix:semicolon
multiline_comment|/* inodes free */
DECL|member|stat_lock
id|spinlock_t
id|stat_lock
suffix:semicolon
)brace
suffix:semicolon
DECL|function|HUGETLBFS_SB
r_static
r_inline
r_struct
id|hugetlbfs_sb_info
op_star
id|HUGETLBFS_SB
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_return
id|sb-&gt;s_fs_info
suffix:semicolon
)brace
DECL|macro|PSEUDO_DIRENT_SIZE
mdefine_line|#define PSEUDO_DIRENT_SIZE&t;20
r_extern
r_struct
id|file_operations
id|hugetlbfs_file_operations
suffix:semicolon
r_extern
r_struct
id|vm_operations_struct
id|hugetlb_vm_ops
suffix:semicolon
r_struct
id|file
op_star
id|hugetlb_zero_setup
c_func
(paren
r_int
)paren
suffix:semicolon
DECL|function|is_file_hugepages
r_static
r_inline
r_int
id|is_file_hugepages
c_func
(paren
r_struct
id|file
op_star
id|file
)paren
(brace
r_return
id|file-&gt;f_op
op_eq
op_amp
id|hugetlbfs_file_operations
suffix:semicolon
)brace
DECL|function|set_file_hugepages
r_static
r_inline
r_void
id|set_file_hugepages
c_func
(paren
r_struct
id|file
op_star
id|file
)paren
(brace
id|file-&gt;f_op
op_assign
op_amp
id|hugetlbfs_file_operations
suffix:semicolon
)brace
macro_line|#else /* !CONFIG_HUGETLBFS */
DECL|macro|is_file_hugepages
mdefine_line|#define is_file_hugepages(file)&t;&t;0
DECL|macro|set_file_hugepages
mdefine_line|#define set_file_hugepages(file)&t;BUG()
DECL|macro|hugetlb_zero_setup
mdefine_line|#define hugetlb_zero_setup(size)&t;ERR_PTR(-ENOSYS)
macro_line|#endif /* !CONFIG_HUGETLBFS */
macro_line|#endif /* _LINUX_HUGETLB_H */
eof
