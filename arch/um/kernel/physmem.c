multiline_comment|/*&n; * Copyright (C) 2000 - 2003 Jeff Dike (jdike@addtoit.com)&n; * Licensed under the GPL&n; */
macro_line|#include &quot;linux/mm.h&quot;
macro_line|#include &quot;linux/rbtree.h&quot;
macro_line|#include &quot;linux/slab.h&quot;
macro_line|#include &quot;linux/vmalloc.h&quot;
macro_line|#include &quot;linux/bootmem.h&quot;
macro_line|#include &quot;linux/module.h&quot;
macro_line|#include &quot;asm/types.h&quot;
macro_line|#include &quot;asm/pgtable.h&quot;
macro_line|#include &quot;kern_util.h&quot;
macro_line|#include &quot;user_util.h&quot;
macro_line|#include &quot;mode_kern.h&quot;
macro_line|#include &quot;mem.h&quot;
macro_line|#include &quot;mem_user.h&quot;
macro_line|#include &quot;os.h&quot;
macro_line|#include &quot;kern.h&quot;
macro_line|#include &quot;init.h&quot;
DECL|struct|phys_desc
r_struct
id|phys_desc
(brace
DECL|member|rb
r_struct
id|rb_node
id|rb
suffix:semicolon
DECL|member|fd
r_int
id|fd
suffix:semicolon
DECL|member|offset
id|__u64
id|offset
suffix:semicolon
DECL|member|virt
r_void
op_star
id|virt
suffix:semicolon
DECL|member|phys
r_int
r_int
id|phys
suffix:semicolon
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|phys_mappings
r_static
r_struct
id|rb_root
id|phys_mappings
op_assign
id|RB_ROOT
suffix:semicolon
DECL|function|find_rb
r_static
r_struct
id|rb_node
op_star
op_star
id|find_rb
c_func
(paren
r_void
op_star
id|virt
)paren
(brace
r_struct
id|rb_node
op_star
op_star
id|n
op_assign
op_amp
id|phys_mappings.rb_node
suffix:semicolon
r_struct
id|phys_desc
op_star
id|d
suffix:semicolon
r_while
c_loop
(paren
op_star
id|n
op_ne
l_int|NULL
)paren
(brace
id|d
op_assign
id|rb_entry
c_func
(paren
op_star
id|n
comma
r_struct
id|phys_desc
comma
id|rb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|d-&gt;virt
op_eq
id|virt
)paren
(brace
r_return
id|n
suffix:semicolon
)brace
r_if
c_cond
(paren
id|d-&gt;virt
OG
id|virt
)paren
(brace
id|n
op_assign
op_amp
(paren
op_star
id|n
)paren
op_member_access_from_pointer
id|rb_left
suffix:semicolon
)brace
r_else
id|n
op_assign
op_amp
(paren
op_star
id|n
)paren
op_member_access_from_pointer
id|rb_right
suffix:semicolon
)brace
r_return
id|n
suffix:semicolon
)brace
DECL|function|find_phys_mapping
r_static
r_struct
id|phys_desc
op_star
id|find_phys_mapping
c_func
(paren
r_void
op_star
id|virt
)paren
(brace
r_struct
id|rb_node
op_star
op_star
id|n
op_assign
id|find_rb
c_func
(paren
id|virt
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|n
op_eq
l_int|NULL
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
r_return
id|rb_entry
c_func
(paren
op_star
id|n
comma
r_struct
id|phys_desc
comma
id|rb
)paren
suffix:semicolon
)brace
DECL|function|insert_phys_mapping
r_static
r_void
id|insert_phys_mapping
c_func
(paren
r_struct
id|phys_desc
op_star
id|desc
)paren
(brace
r_struct
id|rb_node
op_star
op_star
id|n
op_assign
id|find_rb
c_func
(paren
id|desc-&gt;virt
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|n
op_ne
l_int|NULL
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;Physical remapping for %p already present&quot;
comma
id|desc-&gt;virt
)paren
suffix:semicolon
)brace
id|rb_link_node
c_func
(paren
op_amp
id|desc-&gt;rb
comma
(paren
op_star
id|n
)paren
op_member_access_from_pointer
id|rb_parent
comma
id|n
)paren
suffix:semicolon
id|rb_insert_color
c_func
(paren
op_amp
id|desc-&gt;rb
comma
op_amp
id|phys_mappings
)paren
suffix:semicolon
)brace
DECL|variable|descriptor_mappings
id|LIST_HEAD
c_func
(paren
id|descriptor_mappings
)paren
suffix:semicolon
DECL|struct|desc_mapping
r_struct
id|desc_mapping
(brace
DECL|member|fd
r_int
id|fd
suffix:semicolon
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|pages
r_struct
id|list_head
id|pages
suffix:semicolon
)brace
suffix:semicolon
DECL|function|find_mapping
r_static
r_struct
id|desc_mapping
op_star
id|find_mapping
c_func
(paren
r_int
id|fd
)paren
(brace
r_struct
id|desc_mapping
op_star
id|desc
suffix:semicolon
r_struct
id|list_head
op_star
id|ele
suffix:semicolon
(def_block
id|list_for_each
c_func
(paren
id|ele
comma
op_amp
id|descriptor_mappings
)paren
(brace
id|desc
op_assign
id|list_entry
c_func
(paren
id|ele
comma
r_struct
id|desc_mapping
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|desc-&gt;fd
op_eq
id|fd
)paren
(brace
r_return
id|desc
suffix:semicolon
)brace
)brace
)def_block
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|descriptor_mapping
r_static
r_struct
id|desc_mapping
op_star
id|descriptor_mapping
c_func
(paren
r_int
id|fd
)paren
(brace
r_struct
id|desc_mapping
op_star
id|desc
suffix:semicolon
id|desc
op_assign
id|find_mapping
c_func
(paren
id|fd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|desc
op_ne
l_int|NULL
)paren
(brace
r_return
id|desc
suffix:semicolon
)brace
id|desc
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|desc
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|desc
op_eq
l_int|NULL
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
op_star
id|desc
op_assign
(paren
(paren
r_struct
id|desc_mapping
)paren
(brace
dot
id|fd
op_assign
id|fd
comma
dot
id|list
op_assign
id|LIST_HEAD_INIT
c_func
(paren
id|desc-&gt;list
)paren
comma
dot
id|pages
op_assign
id|LIST_HEAD_INIT
c_func
(paren
id|desc-&gt;pages
)paren
)brace
)paren
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|desc-&gt;list
comma
op_amp
id|descriptor_mappings
)paren
suffix:semicolon
r_return
id|desc
suffix:semicolon
)brace
DECL|function|physmem_subst_mapping
r_int
id|physmem_subst_mapping
c_func
(paren
r_void
op_star
id|virt
comma
r_int
id|fd
comma
id|__u64
id|offset
comma
r_int
id|w
)paren
(brace
r_struct
id|desc_mapping
op_star
id|fd_maps
suffix:semicolon
r_struct
id|phys_desc
op_star
id|desc
suffix:semicolon
r_int
r_int
id|phys
suffix:semicolon
r_int
id|err
suffix:semicolon
id|fd_maps
op_assign
id|descriptor_mapping
c_func
(paren
id|fd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fd_maps
op_eq
l_int|NULL
)paren
(brace
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|phys
op_assign
id|__pa
c_func
(paren
id|virt
)paren
suffix:semicolon
id|desc
op_assign
id|find_phys_mapping
c_func
(paren
id|virt
)paren
suffix:semicolon
r_if
c_cond
(paren
id|desc
op_ne
l_int|NULL
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;Address 0x%p is already substituted&bslash;n&quot;
comma
id|virt
)paren
suffix:semicolon
)brace
id|err
op_assign
op_minus
id|ENOMEM
suffix:semicolon
id|desc
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|desc
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|desc
op_eq
l_int|NULL
)paren
(brace
r_goto
id|out
suffix:semicolon
)brace
op_star
id|desc
op_assign
(paren
(paren
r_struct
id|phys_desc
)paren
(brace
dot
id|fd
op_assign
id|fd
comma
dot
id|offset
op_assign
id|offset
comma
dot
id|virt
op_assign
id|virt
comma
dot
id|phys
op_assign
id|__pa
c_func
(paren
id|virt
)paren
comma
dot
id|list
op_assign
id|LIST_HEAD_INIT
c_func
(paren
id|desc-&gt;list
)paren
)brace
)paren
suffix:semicolon
id|insert_phys_mapping
c_func
(paren
id|desc
)paren
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|desc-&gt;list
comma
op_amp
id|fd_maps-&gt;pages
)paren
suffix:semicolon
id|virt
op_assign
(paren
r_void
op_star
)paren
(paren
(paren
r_int
r_int
)paren
id|virt
op_amp
id|PAGE_MASK
)paren
suffix:semicolon
id|err
op_assign
id|os_map_memory
c_func
(paren
id|virt
comma
id|fd
comma
id|offset
comma
id|PAGE_SIZE
comma
l_int|1
comma
id|w
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|err
)paren
(brace
r_goto
id|out
suffix:semicolon
)brace
id|rb_erase
c_func
(paren
op_amp
id|desc-&gt;rb
comma
op_amp
id|phys_mappings
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|desc
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|err
suffix:semicolon
)brace
DECL|variable|physmem_fd
r_static
r_int
id|physmem_fd
op_assign
op_minus
l_int|1
suffix:semicolon
DECL|function|remove_mapping
r_static
r_void
id|remove_mapping
c_func
(paren
r_struct
id|phys_desc
op_star
id|desc
)paren
(brace
r_void
op_star
id|virt
op_assign
id|desc-&gt;virt
suffix:semicolon
r_int
id|err
suffix:semicolon
id|rb_erase
c_func
(paren
op_amp
id|desc-&gt;rb
comma
op_amp
id|phys_mappings
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|desc-&gt;list
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|desc
)paren
suffix:semicolon
id|err
op_assign
id|os_map_memory
c_func
(paren
id|virt
comma
id|physmem_fd
comma
id|__pa
c_func
(paren
id|virt
)paren
comma
id|PAGE_SIZE
comma
l_int|1
comma
l_int|1
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;Failed to unmap block device page from physical memory, &quot;
l_string|&quot;errno = %d&quot;
comma
op_minus
id|err
)paren
suffix:semicolon
)brace
)brace
DECL|function|physmem_remove_mapping
r_int
id|physmem_remove_mapping
c_func
(paren
r_void
op_star
id|virt
)paren
(brace
r_struct
id|phys_desc
op_star
id|desc
suffix:semicolon
id|virt
op_assign
(paren
r_void
op_star
)paren
(paren
(paren
r_int
r_int
)paren
id|virt
op_amp
id|PAGE_MASK
)paren
suffix:semicolon
id|desc
op_assign
id|find_phys_mapping
c_func
(paren
id|virt
)paren
suffix:semicolon
r_if
c_cond
(paren
id|desc
op_eq
l_int|NULL
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
id|remove_mapping
c_func
(paren
id|desc
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|physmem_forget_descriptor
r_void
id|physmem_forget_descriptor
c_func
(paren
r_int
id|fd
)paren
(brace
r_struct
id|desc_mapping
op_star
id|desc
suffix:semicolon
r_struct
id|phys_desc
op_star
id|page
suffix:semicolon
r_struct
id|list_head
op_star
id|ele
comma
op_star
id|next
suffix:semicolon
id|__u64
id|offset
suffix:semicolon
r_void
op_star
id|addr
suffix:semicolon
r_int
id|err
suffix:semicolon
id|desc
op_assign
id|find_mapping
c_func
(paren
id|fd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|desc
op_eq
l_int|NULL
)paren
(brace
r_return
suffix:semicolon
)brace
(def_block
id|list_for_each_safe
c_func
(paren
id|ele
comma
id|next
comma
op_amp
id|desc-&gt;pages
)paren
(brace
id|page
op_assign
id|list_entry
c_func
(paren
id|ele
comma
r_struct
id|phys_desc
comma
id|list
)paren
suffix:semicolon
id|offset
op_assign
id|page-&gt;offset
suffix:semicolon
id|addr
op_assign
id|page-&gt;virt
suffix:semicolon
id|remove_mapping
c_func
(paren
id|page
)paren
suffix:semicolon
id|err
op_assign
id|os_seek_file
c_func
(paren
id|fd
comma
id|offset
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;physmem_forget_descriptor - failed to seek &quot;
l_string|&quot;to %lld in fd %d, error = %d&bslash;n&quot;
comma
id|offset
comma
id|fd
comma
op_minus
id|err
)paren
suffix:semicolon
)brace
id|err
op_assign
id|os_read_file
c_func
(paren
id|fd
comma
id|addr
comma
id|PAGE_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;physmem_forget_descriptor - failed to read &quot;
l_string|&quot;from fd %d to 0x%p, error = %d&bslash;n&quot;
comma
id|fd
comma
id|addr
comma
op_minus
id|err
)paren
suffix:semicolon
)brace
)brace
)def_block
id|list_del
c_func
(paren
op_amp
id|desc-&gt;list
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|desc
)paren
suffix:semicolon
)brace
DECL|variable|physmem_forget_descriptor
id|EXPORT_SYMBOL
c_func
(paren
id|physmem_forget_descriptor
)paren
suffix:semicolon
DECL|variable|physmem_remove_mapping
id|EXPORT_SYMBOL
c_func
(paren
id|physmem_remove_mapping
)paren
suffix:semicolon
DECL|variable|physmem_subst_mapping
id|EXPORT_SYMBOL
c_func
(paren
id|physmem_subst_mapping
)paren
suffix:semicolon
DECL|function|arch_free_page
r_void
id|arch_free_page
c_func
(paren
r_struct
id|page
op_star
id|page
comma
r_int
id|order
)paren
(brace
r_void
op_star
id|virt
suffix:semicolon
r_int
id|i
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
(paren
l_int|1
op_lshift
id|order
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
id|virt
op_assign
id|__va
c_func
(paren
id|page_to_phys
c_func
(paren
id|page
op_plus
id|i
)paren
)paren
suffix:semicolon
id|physmem_remove_mapping
c_func
(paren
id|virt
)paren
suffix:semicolon
)brace
)brace
DECL|function|is_remapped
r_int
id|is_remapped
c_func
(paren
r_void
op_star
id|virt
)paren
(brace
r_struct
id|phys_desc
op_star
id|desc
op_assign
id|find_phys_mapping
c_func
(paren
id|virt
)paren
suffix:semicolon
r_return
id|desc
op_ne
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* Changed during early boot */
DECL|variable|high_physmem
r_int
r_int
id|high_physmem
suffix:semicolon
r_extern
r_int
r_int
id|physmem_size
suffix:semicolon
DECL|function|to_virt
r_void
op_star
id|to_virt
c_func
(paren
r_int
r_int
id|phys
)paren
(brace
r_return
(paren
r_void
op_star
)paren
id|uml_physmem
op_plus
id|phys
suffix:semicolon
)brace
DECL|function|to_phys
r_int
r_int
id|to_phys
c_func
(paren
r_void
op_star
id|virt
)paren
(brace
r_return
(paren
(paren
r_int
r_int
)paren
id|virt
)paren
op_minus
id|uml_physmem
suffix:semicolon
)brace
DECL|function|init_maps
r_int
id|init_maps
c_func
(paren
r_int
r_int
id|physmem
comma
r_int
r_int
id|iomem
comma
r_int
r_int
id|highmem
)paren
(brace
r_struct
id|page
op_star
id|p
comma
op_star
id|map
suffix:semicolon
r_int
r_int
id|phys_len
comma
id|phys_pages
comma
id|highmem_len
comma
id|highmem_pages
suffix:semicolon
r_int
r_int
id|iomem_len
comma
id|iomem_pages
comma
id|total_len
comma
id|total_pages
suffix:semicolon
r_int
id|i
suffix:semicolon
id|phys_pages
op_assign
id|physmem
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|phys_len
op_assign
id|phys_pages
op_star
r_sizeof
(paren
r_struct
id|page
)paren
suffix:semicolon
id|iomem_pages
op_assign
id|iomem
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|iomem_len
op_assign
id|iomem_pages
op_star
r_sizeof
(paren
r_struct
id|page
)paren
suffix:semicolon
id|highmem_pages
op_assign
id|highmem
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|highmem_len
op_assign
id|highmem_pages
op_star
r_sizeof
(paren
r_struct
id|page
)paren
suffix:semicolon
id|total_pages
op_assign
id|phys_pages
op_plus
id|iomem_pages
op_plus
id|highmem_pages
suffix:semicolon
id|total_len
op_assign
id|phys_len
op_plus
id|iomem_pages
op_plus
id|highmem_len
suffix:semicolon
r_if
c_cond
(paren
id|kmalloc_ok
)paren
(brace
id|map
op_assign
id|kmalloc
c_func
(paren
id|total_len
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|map
op_eq
l_int|NULL
)paren
(brace
id|map
op_assign
id|vmalloc
c_func
(paren
id|total_len
)paren
suffix:semicolon
)brace
)brace
r_else
id|map
op_assign
id|alloc_bootmem_low_pages
c_func
(paren
id|total_len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|map
op_eq
l_int|NULL
)paren
(brace
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|total_pages
suffix:semicolon
id|i
op_increment
)paren
(brace
id|p
op_assign
op_amp
id|map
(braket
id|i
)braket
suffix:semicolon
id|set_page_count
c_func
(paren
id|p
comma
l_int|0
)paren
suffix:semicolon
id|SetPageReserved
c_func
(paren
id|p
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|p-&gt;lru
)paren
suffix:semicolon
)brace
id|mem_map
op_assign
id|map
suffix:semicolon
id|max_mapnr
op_assign
id|total_pages
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|phys_to_page
r_struct
id|page
op_star
id|phys_to_page
c_func
(paren
r_const
r_int
r_int
id|phys
)paren
(brace
r_return
op_amp
id|mem_map
(braket
id|phys
op_rshift
id|PAGE_SHIFT
)braket
suffix:semicolon
)brace
DECL|function|__virt_to_page
r_struct
id|page
op_star
id|__virt_to_page
c_func
(paren
r_const
r_int
r_int
id|virt
)paren
(brace
r_return
op_amp
id|mem_map
(braket
id|__pa
c_func
(paren
id|virt
)paren
op_rshift
id|PAGE_SHIFT
)braket
suffix:semicolon
)brace
DECL|function|page_to_phys
r_int
r_int
id|page_to_phys
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
(brace
r_return
(paren
id|page
op_minus
id|mem_map
)paren
op_lshift
id|PAGE_SHIFT
suffix:semicolon
)brace
DECL|function|mk_pte
id|pte_t
id|mk_pte
c_func
(paren
r_struct
id|page
op_star
id|page
comma
id|pgprot_t
id|pgprot
)paren
(brace
id|pte_t
id|pte
suffix:semicolon
id|pte_val
c_func
(paren
id|pte
)paren
op_assign
id|page_to_phys
c_func
(paren
id|page
)paren
op_plus
id|pgprot_val
c_func
(paren
id|pgprot
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pte_present
c_func
(paren
id|pte
)paren
)paren
(brace
id|pte_mknewprot
c_func
(paren
id|pte_mknewpage
c_func
(paren
id|pte
)paren
)paren
suffix:semicolon
)brace
r_return
id|pte
suffix:semicolon
)brace
multiline_comment|/* Changed during early boot */
DECL|variable|kmem_top
r_static
r_int
r_int
id|kmem_top
op_assign
l_int|0
suffix:semicolon
DECL|function|get_kmem_end
r_int
r_int
id|get_kmem_end
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|kmem_top
op_eq
l_int|0
)paren
(brace
id|kmem_top
op_assign
id|CHOOSE_MODE
c_func
(paren
id|kmem_end_tt
comma
id|kmem_end_skas
)paren
suffix:semicolon
)brace
r_return
id|kmem_top
suffix:semicolon
)brace
DECL|function|map_memory
r_void
id|map_memory
c_func
(paren
r_int
r_int
id|virt
comma
r_int
r_int
id|phys
comma
r_int
r_int
id|len
comma
r_int
id|r
comma
r_int
id|w
comma
r_int
id|x
)paren
(brace
id|__u64
id|offset
suffix:semicolon
r_int
id|fd
comma
id|err
suffix:semicolon
id|fd
op_assign
id|phys_mapping
c_func
(paren
id|phys
comma
op_amp
id|offset
)paren
suffix:semicolon
id|err
op_assign
id|os_map_memory
c_func
(paren
(paren
r_void
op_star
)paren
id|virt
comma
id|fd
comma
id|offset
comma
id|len
comma
id|r
comma
id|w
comma
id|x
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
r_if
c_cond
(paren
id|err
op_eq
op_minus
id|ENOMEM
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;try increasing the host&squot;s &quot;
l_string|&quot;/proc/sys/vm/max_map_count to &lt;physical &quot;
l_string|&quot;memory size&gt;/4096&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|panic
c_func
(paren
l_string|&quot;map_memory(0x%lx, %d, 0x%llx, %ld, %d, %d, %d) failed, &quot;
l_string|&quot;err = %d&bslash;n&quot;
comma
id|virt
comma
id|fd
comma
id|offset
comma
id|len
comma
id|r
comma
id|w
comma
id|x
comma
id|err
)paren
suffix:semicolon
)brace
)brace
DECL|macro|PFN_UP
mdefine_line|#define PFN_UP(x) (((x) + PAGE_SIZE-1) &gt;&gt; PAGE_SHIFT)
DECL|function|setup_physmem
r_void
id|setup_physmem
c_func
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|reserve_end
comma
r_int
r_int
id|len
comma
r_int
r_int
id|highmem
)paren
(brace
r_int
r_int
id|reserve
op_assign
id|reserve_end
op_minus
id|start
suffix:semicolon
r_int
id|pfn
op_assign
id|PFN_UP
c_func
(paren
id|__pa
c_func
(paren
id|reserve_end
)paren
)paren
suffix:semicolon
r_int
id|delta
op_assign
(paren
id|len
op_minus
id|reserve
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
r_int
id|err
comma
id|offset
comma
id|bootmap_size
suffix:semicolon
id|physmem_fd
op_assign
id|create_mem_file
c_func
(paren
id|len
op_plus
id|highmem
)paren
suffix:semicolon
id|offset
op_assign
id|uml_reserved
op_minus
id|uml_physmem
suffix:semicolon
id|err
op_assign
id|os_map_memory
c_func
(paren
(paren
r_void
op_star
)paren
id|uml_reserved
comma
id|physmem_fd
comma
id|offset
comma
id|len
op_minus
id|offset
comma
l_int|1
comma
l_int|1
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
(brace
id|os_print_error
c_func
(paren
id|err
comma
l_string|&quot;Mapping memory&quot;
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
id|bootmap_size
op_assign
id|init_bootmem
c_func
(paren
id|pfn
comma
id|pfn
op_plus
id|delta
)paren
suffix:semicolon
id|free_bootmem
c_func
(paren
id|__pa
c_func
(paren
id|reserve_end
)paren
op_plus
id|bootmap_size
comma
id|len
op_minus
id|bootmap_size
op_minus
id|reserve
)paren
suffix:semicolon
)brace
DECL|function|phys_mapping
r_int
id|phys_mapping
c_func
(paren
r_int
r_int
id|phys
comma
id|__u64
op_star
id|offset_out
)paren
(brace
r_struct
id|phys_desc
op_star
id|desc
op_assign
id|find_phys_mapping
c_func
(paren
id|__va
c_func
(paren
id|phys
op_amp
id|PAGE_MASK
)paren
)paren
suffix:semicolon
r_int
id|fd
op_assign
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|desc
op_ne
l_int|NULL
)paren
(brace
id|fd
op_assign
id|desc-&gt;fd
suffix:semicolon
op_star
id|offset_out
op_assign
id|desc-&gt;offset
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|phys
OL
id|physmem_size
)paren
(brace
id|fd
op_assign
id|physmem_fd
suffix:semicolon
op_star
id|offset_out
op_assign
id|phys
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|phys
OL
id|__pa
c_func
(paren
id|end_iomem
)paren
)paren
(brace
r_struct
id|iomem_region
op_star
id|region
op_assign
id|iomem_regions
suffix:semicolon
r_while
c_loop
(paren
id|region
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
(paren
id|phys
op_ge
id|region-&gt;phys
)paren
op_logical_and
(paren
id|phys
OL
id|region-&gt;phys
op_plus
id|region-&gt;size
)paren
)paren
(brace
id|fd
op_assign
id|region-&gt;fd
suffix:semicolon
op_star
id|offset_out
op_assign
id|phys
op_minus
id|region-&gt;phys
suffix:semicolon
r_break
suffix:semicolon
)brace
id|region
op_assign
id|region-&gt;next
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|phys
OL
id|__pa
c_func
(paren
id|end_iomem
)paren
op_plus
id|highmem
)paren
(brace
id|fd
op_assign
id|physmem_fd
suffix:semicolon
op_star
id|offset_out
op_assign
id|phys
op_minus
id|iomem_size
suffix:semicolon
)brace
r_return
id|fd
suffix:semicolon
)brace
DECL|function|uml_mem_setup
r_static
r_int
id|__init
id|uml_mem_setup
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
r_char
op_star
id|retptr
suffix:semicolon
id|physmem_size
op_assign
id|memparse
c_func
(paren
id|line
comma
op_amp
id|retptr
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|__uml_setup
c_func
(paren
l_string|&quot;mem=&quot;
comma
id|uml_mem_setup
comma
l_string|&quot;mem=&lt;Amount of desired ram&gt;&bslash;n&quot;
l_string|&quot;    This controls how much &bslash;&quot;physical&bslash;&quot; memory the kernel allocates&bslash;n&quot;
l_string|&quot;    for the system. The size is specified as a number followed by&bslash;n&quot;
l_string|&quot;    one of &squot;k&squot;, &squot;K&squot;, &squot;m&squot;, &squot;M&squot;, which have the obvious meanings.&bslash;n&quot;
l_string|&quot;    This is not related to the amount of memory in the host.  It can&bslash;n&quot;
l_string|&quot;    be more, and the excess, if it&squot;s ever used, will just be swapped out.&bslash;n&quot;
l_string|&quot;&t;Example: mem=64M&bslash;n&bslash;n&quot;
)paren
suffix:semicolon
DECL|function|find_iomem
r_int
r_int
id|find_iomem
c_func
(paren
r_char
op_star
id|driver
comma
r_int
r_int
op_star
id|len_out
)paren
(brace
r_struct
id|iomem_region
op_star
id|region
op_assign
id|iomem_regions
suffix:semicolon
r_while
c_loop
(paren
id|region
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|region-&gt;driver
comma
id|driver
)paren
)paren
(brace
op_star
id|len_out
op_assign
id|region-&gt;size
suffix:semicolon
r_return
id|region-&gt;virt
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|setup_iomem
r_int
id|setup_iomem
c_func
(paren
r_void
)paren
(brace
r_struct
id|iomem_region
op_star
id|region
op_assign
id|iomem_regions
suffix:semicolon
r_int
r_int
id|iomem_start
op_assign
id|high_physmem
op_plus
id|PAGE_SIZE
suffix:semicolon
r_int
id|err
suffix:semicolon
r_while
c_loop
(paren
id|region
op_ne
l_int|NULL
)paren
(brace
id|err
op_assign
id|os_map_memory
c_func
(paren
(paren
r_void
op_star
)paren
id|iomem_start
comma
id|region-&gt;fd
comma
l_int|0
comma
id|region-&gt;size
comma
l_int|1
comma
l_int|1
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Mapping iomem region for driver &squot;%s&squot; failed, &quot;
l_string|&quot;errno = %d&bslash;n&quot;
comma
id|region-&gt;driver
comma
op_minus
id|err
)paren
suffix:semicolon
)brace
r_else
(brace
id|region-&gt;virt
op_assign
id|iomem_start
suffix:semicolon
id|region-&gt;phys
op_assign
id|__pa
c_func
(paren
id|region-&gt;virt
)paren
suffix:semicolon
)brace
id|iomem_start
op_add_assign
id|region-&gt;size
op_plus
id|PAGE_SIZE
suffix:semicolon
id|region
op_assign
id|region-&gt;next
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|setup_iomem
id|__initcall
c_func
(paren
id|setup_iomem
)paren
suffix:semicolon
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
