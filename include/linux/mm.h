macro_line|#ifndef _LINUX_MM_H
DECL|macro|_LINUX_MM_H
mdefine_line|#define _LINUX_MM_H
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/gfp.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/mmzone.h&gt;
macro_line|#include &lt;linux/rbtree.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#ifndef CONFIG_DISCONTIGMEM          /* Don&squot;t use mapnrs, do it properly */
r_extern
r_int
r_int
id|max_mapnr
suffix:semicolon
macro_line|#endif
r_extern
r_int
r_int
id|num_physpages
suffix:semicolon
r_extern
r_void
op_star
id|high_memory
suffix:semicolon
r_extern
r_int
id|page_cluster
suffix:semicolon
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#ifndef MM_VM_SIZE
DECL|macro|MM_VM_SIZE
mdefine_line|#define MM_VM_SIZE(mm)&t;TASK_SIZE
macro_line|#endif
multiline_comment|/*&n; * Linux kernel virtual memory manager primitives.&n; * The idea being to have a &quot;virtual&quot; mm in the same way&n; * we have a virtual fs - giving a cleaner interface to the&n; * mm details, and allowing different kinds of memory mappings&n; * (from shared memory to executable loading to arbitrary&n; * mmap() functions).&n; */
multiline_comment|/*&n; * This struct defines a memory VMM memory area. There is one of these&n; * per VM-area/task.  A VM area is any part of the process virtual memory&n; * space that has a special rule for the page-fault handlers (ie a shared&n; * library, the executable area etc).&n; *&n; * This structure is exactly 64 bytes on ia32.  Please think very, very hard&n; * before adding anything to it.&n; */
DECL|struct|vm_area_struct
r_struct
id|vm_area_struct
(brace
DECL|member|vm_mm
r_struct
id|mm_struct
op_star
id|vm_mm
suffix:semicolon
multiline_comment|/* The address space we belong to. */
DECL|member|vm_start
r_int
r_int
id|vm_start
suffix:semicolon
multiline_comment|/* Our start address within vm_mm. */
DECL|member|vm_end
r_int
r_int
id|vm_end
suffix:semicolon
multiline_comment|/* The first byte after our end address&n;&t;&t;&t;&t;&t;   within vm_mm. */
multiline_comment|/* linked list of VM areas per task, sorted by address */
DECL|member|vm_next
r_struct
id|vm_area_struct
op_star
id|vm_next
suffix:semicolon
DECL|member|vm_page_prot
id|pgprot_t
id|vm_page_prot
suffix:semicolon
multiline_comment|/* Access permissions of this VMA. */
DECL|member|vm_flags
r_int
r_int
id|vm_flags
suffix:semicolon
multiline_comment|/* Flags, listed below. */
DECL|member|vm_rb
r_struct
id|rb_node
id|vm_rb
suffix:semicolon
multiline_comment|/*&n;&t; * For areas with an address space and backing store,&n;&t; * one of the address_space-&gt;i_mmap{,shared} lists,&n;&t; * for shm areas, the list of attaches, otherwise unused.&n;&t; */
DECL|member|shared
r_struct
id|list_head
id|shared
suffix:semicolon
multiline_comment|/* Function pointers to deal with this struct. */
DECL|member|vm_ops
r_struct
id|vm_operations_struct
op_star
id|vm_ops
suffix:semicolon
multiline_comment|/* Information about our backing store: */
DECL|member|vm_pgoff
r_int
r_int
id|vm_pgoff
suffix:semicolon
multiline_comment|/* Offset (within vm_file) in PAGE_SIZE&n;&t;&t;&t;&t;&t;   units, *not* PAGE_CACHE_SIZE */
DECL|member|vm_file
r_struct
id|file
op_star
id|vm_file
suffix:semicolon
multiline_comment|/* File we map to (can be NULL). */
DECL|member|vm_private_data
r_void
op_star
id|vm_private_data
suffix:semicolon
multiline_comment|/* was vm_pte (shared mem) */
)brace
suffix:semicolon
multiline_comment|/*&n; * vm_flags..&n; */
DECL|macro|VM_READ
mdefine_line|#define VM_READ&t;&t;0x00000001&t;/* currently active flags */
DECL|macro|VM_WRITE
mdefine_line|#define VM_WRITE&t;0x00000002
DECL|macro|VM_EXEC
mdefine_line|#define VM_EXEC&t;&t;0x00000004
DECL|macro|VM_SHARED
mdefine_line|#define VM_SHARED&t;0x00000008
DECL|macro|VM_MAYREAD
mdefine_line|#define VM_MAYREAD&t;0x00000010&t;/* limits for mprotect() etc */
DECL|macro|VM_MAYWRITE
mdefine_line|#define VM_MAYWRITE&t;0x00000020
DECL|macro|VM_MAYEXEC
mdefine_line|#define VM_MAYEXEC&t;0x00000040
DECL|macro|VM_MAYSHARE
mdefine_line|#define VM_MAYSHARE&t;0x00000080
DECL|macro|VM_GROWSDOWN
mdefine_line|#define VM_GROWSDOWN&t;0x00000100&t;/* general info on the segment */
DECL|macro|VM_GROWSUP
mdefine_line|#define VM_GROWSUP&t;0x00000200
DECL|macro|VM_SHM
mdefine_line|#define VM_SHM&t;&t;0x00000400&t;/* shared memory area, don&squot;t swap out */
DECL|macro|VM_DENYWRITE
mdefine_line|#define VM_DENYWRITE&t;0x00000800&t;/* ETXTBSY on write attempts.. */
DECL|macro|VM_EXECUTABLE
mdefine_line|#define VM_EXECUTABLE&t;0x00001000
DECL|macro|VM_LOCKED
mdefine_line|#define VM_LOCKED&t;0x00002000
DECL|macro|VM_IO
mdefine_line|#define VM_IO           0x00004000&t;/* Memory mapped I/O or similar */
multiline_comment|/* Used by sys_madvise() */
DECL|macro|VM_SEQ_READ
mdefine_line|#define VM_SEQ_READ&t;0x00008000&t;/* App will access data sequentially */
DECL|macro|VM_RAND_READ
mdefine_line|#define VM_RAND_READ&t;0x00010000&t;/* App will not benefit from clustered reads */
DECL|macro|VM_DONTCOPY
mdefine_line|#define VM_DONTCOPY&t;0x00020000      /* Do not copy this vma on fork */
DECL|macro|VM_DONTEXPAND
mdefine_line|#define VM_DONTEXPAND&t;0x00040000&t;/* Cannot expand with mremap() */
DECL|macro|VM_RESERVED
mdefine_line|#define VM_RESERVED&t;0x00080000&t;/* Don&squot;t unmap it from swap_out */
DECL|macro|VM_ACCOUNT
mdefine_line|#define VM_ACCOUNT&t;0x00100000&t;/* Is a VM accounted object */
DECL|macro|VM_HUGETLB
mdefine_line|#define VM_HUGETLB&t;0x00400000&t;/* Huge TLB Page VM */
DECL|macro|VM_NONLINEAR
mdefine_line|#define VM_NONLINEAR&t;0x00800000&t;/* Is non-linear (remap_file_pages) */
multiline_comment|/* It makes sense to apply VM_ACCOUNT to this vma. */
DECL|macro|VM_MAYACCT
mdefine_line|#define VM_MAYACCT(vma) (!!((vma)-&gt;vm_flags &amp; VM_HUGETLB))
macro_line|#ifndef VM_STACK_DEFAULT_FLAGS&t;&t;/* arch can override this */
DECL|macro|VM_STACK_DEFAULT_FLAGS
mdefine_line|#define VM_STACK_DEFAULT_FLAGS VM_DATA_DEFAULT_FLAGS
macro_line|#endif
macro_line|#ifdef CONFIG_STACK_GROWSUP
DECL|macro|VM_STACK_FLAGS
mdefine_line|#define VM_STACK_FLAGS&t;(VM_GROWSUP | VM_STACK_DEFAULT_FLAGS | VM_ACCOUNT)
macro_line|#else
DECL|macro|VM_STACK_FLAGS
mdefine_line|#define VM_STACK_FLAGS&t;(VM_GROWSDOWN | VM_STACK_DEFAULT_FLAGS | VM_ACCOUNT)
macro_line|#endif
DECL|macro|VM_READHINTMASK
mdefine_line|#define VM_READHINTMASK&t;&t;&t;(VM_SEQ_READ | VM_RAND_READ)
DECL|macro|VM_ClearReadHint
mdefine_line|#define VM_ClearReadHint(v)&t;&t;(v)-&gt;vm_flags &amp;= ~VM_READHINTMASK
DECL|macro|VM_NormalReadHint
mdefine_line|#define VM_NormalReadHint(v)&t;&t;(!((v)-&gt;vm_flags &amp; VM_READHINTMASK))
DECL|macro|VM_SequentialReadHint
mdefine_line|#define VM_SequentialReadHint(v)&t;((v)-&gt;vm_flags &amp; VM_SEQ_READ)
DECL|macro|VM_RandomReadHint
mdefine_line|#define VM_RandomReadHint(v)&t;&t;((v)-&gt;vm_flags &amp; VM_RAND_READ)
multiline_comment|/*&n; * mapping from the currently active vm_flags protection bits (the&n; * low four bits) to a page protection mask..&n; */
r_extern
id|pgprot_t
id|protection_map
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/*&n; * These are the virtual MM functions - opening of an area, closing and&n; * unmapping it (needed to keep files on disk up-to-date etc), pointer&n; * to the functions called when a no-page or a wp-page exception occurs. &n; */
DECL|struct|vm_operations_struct
r_struct
id|vm_operations_struct
(brace
DECL|member|open
r_void
(paren
op_star
id|open
)paren
(paren
r_struct
id|vm_area_struct
op_star
id|area
)paren
suffix:semicolon
DECL|member|close
r_void
(paren
op_star
id|close
)paren
(paren
r_struct
id|vm_area_struct
op_star
id|area
)paren
suffix:semicolon
DECL|member|nopage
r_struct
id|page
op_star
(paren
op_star
id|nopage
)paren
(paren
r_struct
id|vm_area_struct
op_star
id|area
comma
r_int
r_int
id|address
comma
r_int
op_star
id|type
)paren
suffix:semicolon
DECL|member|populate
r_int
(paren
op_star
id|populate
)paren
(paren
r_struct
id|vm_area_struct
op_star
id|area
comma
r_int
r_int
id|address
comma
r_int
r_int
id|len
comma
id|pgprot_t
id|prot
comma
r_int
r_int
id|pgoff
comma
r_int
id|nonblock
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* forward declaration; pte_chain is meant to be internal to rmap.c */
r_struct
id|pte_chain
suffix:semicolon
r_struct
id|mmu_gather
suffix:semicolon
r_struct
id|inode
suffix:semicolon
macro_line|#ifdef ARCH_HAS_ATOMIC_UNSIGNED
DECL|typedef|page_flags_t
r_typedef
r_int
id|page_flags_t
suffix:semicolon
macro_line|#else
DECL|typedef|page_flags_t
r_typedef
r_int
r_int
id|page_flags_t
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Each physical page in the system has a struct page associated with&n; * it to keep track of whatever it is we are using the page for at the&n; * moment. Note that we have no way to track which tasks are using&n; * a page.&n; *&n; * Try to keep the most commonly accessed fields in single cache lines&n; * here (16 bytes or greater).  This ordering should be particularly&n; * beneficial on 32-bit processors.&n; *&n; * The first line is data used in page cache lookup, the second line&n; * is used for linear searches (eg. clock algorithm scans). &n; *&n; * TODO: make this structure smaller, it could be as small as 32 bytes.&n; */
DECL|struct|page
r_struct
id|page
(brace
DECL|member|flags
id|page_flags_t
id|flags
suffix:semicolon
multiline_comment|/* atomic flags, some possibly&n;&t;&t;&t;&t;&t;   updated asynchronously */
DECL|member|count
id|atomic_t
id|count
suffix:semicolon
multiline_comment|/* Usage count, see below. */
DECL|member|mapping
r_struct
id|address_space
op_star
id|mapping
suffix:semicolon
multiline_comment|/* The inode (or ...) we belong to. */
DECL|member|index
id|pgoff_t
id|index
suffix:semicolon
multiline_comment|/* Our offset within mapping. */
DECL|member|lru
r_struct
id|list_head
id|lru
suffix:semicolon
multiline_comment|/* Pageout list, eg. active_list;&n;&t;&t;&t;&t;&t;   protected by zone-&gt;lru_lock !! */
r_union
(brace
DECL|member|chain
r_struct
id|pte_chain
op_star
id|chain
suffix:semicolon
multiline_comment|/* Reverse pte mapping pointer.&n;&t;&t;&t;&t;&t; * protected by PG_chainlock */
DECL|member|direct
id|pte_addr_t
id|direct
suffix:semicolon
DECL|member|pte
)brace
id|pte
suffix:semicolon
DECL|member|private
r_int
r_int
r_private
suffix:semicolon
multiline_comment|/* mapping-private opaque data */
multiline_comment|/*&n;&t; * On machines where all RAM is mapped into kernel address space,&n;&t; * we can simply calculate the virtual address. On machines with&n;&t; * highmem some memory is mapped into kernel virtual memory&n;&t; * dynamically, so we need a place to store that address.&n;&t; * Note that this field could be 16 bits on x86 ... ;)&n;&t; *&n;&t; * Architectures with slow multiplication can define&n;&t; * WANT_PAGE_VIRTUAL in asm/page.h&n;&t; */
macro_line|#if defined(WANT_PAGE_VIRTUAL)
DECL|member|virtual
r_void
op_star
r_virtual
suffix:semicolon
multiline_comment|/* Kernel virtual address (NULL if&n;&t;&t;&t;&t;&t;   not kmapped, ie. highmem) */
macro_line|#endif /* WANT_PAGE_VIRTUAL */
)brace
suffix:semicolon
multiline_comment|/*&n; * FIXME: take this include out, include page-flags.h in&n; * files which need it (119 of them)&n; */
macro_line|#include &lt;linux/page-flags.h&gt;
multiline_comment|/*&n; * Methods to modify the page usage count.&n; *&n; * What counts for a page usage:&n; * - cache mapping   (page-&gt;mapping)&n; * - private data    (page-&gt;private)&n; * - page mapped in a task&squot;s page tables, each mapping&n; *   is counted separately&n; *&n; * Also, many kernel routines increase the page count before a critical&n; * routine so they can be sure the page doesn&squot;t go away from under them.&n; */
DECL|macro|put_page_testzero
mdefine_line|#define put_page_testzero(p)&t;&t;&t;&t;&bslash;&n;&t;({&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;BUG_ON(page_count(p) == 0);&t;&t;&bslash;&n;&t;&t;atomic_dec_and_test(&amp;(p)-&gt;count);&t;&bslash;&n;&t;})
DECL|macro|set_page_count
mdefine_line|#define set_page_count(p,v) &t;atomic_set(&amp;(p)-&gt;count, v)
DECL|macro|__put_page
mdefine_line|#define __put_page(p)&t;&t;atomic_dec(&amp;(p)-&gt;count)
r_extern
r_void
id|FASTCALL
c_func
(paren
id|__page_cache_release
c_func
(paren
r_struct
id|page
op_star
)paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_HUGETLB_PAGE
DECL|function|page_count
r_static
r_inline
r_int
id|page_count
c_func
(paren
r_struct
id|page
op_star
id|p
)paren
(brace
r_if
c_cond
(paren
id|PageCompound
c_func
(paren
id|p
)paren
)paren
id|p
op_assign
(paren
r_struct
id|page
op_star
)paren
id|p
op_member_access_from_pointer
r_private
suffix:semicolon
r_return
id|atomic_read
c_func
(paren
op_amp
(paren
id|p
)paren
op_member_access_from_pointer
id|count
)paren
suffix:semicolon
)brace
DECL|function|get_page
r_static
r_inline
r_void
id|get_page
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
(brace
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|PageCompound
c_func
(paren
id|page
)paren
)paren
)paren
id|page
op_assign
(paren
r_struct
id|page
op_star
)paren
id|page
op_member_access_from_pointer
r_private
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|page-&gt;count
)paren
suffix:semicolon
)brace
DECL|function|put_page
r_static
r_inline
r_void
id|put_page
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
(brace
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|PageCompound
c_func
(paren
id|page
)paren
)paren
)paren
(brace
id|page
op_assign
(paren
r_struct
id|page
op_star
)paren
id|page
op_member_access_from_pointer
r_private
suffix:semicolon
r_if
c_cond
(paren
id|put_page_testzero
c_func
(paren
id|page
)paren
)paren
(brace
r_if
c_cond
(paren
id|page
(braket
l_int|1
)braket
dot
id|mapping
)paren
(brace
multiline_comment|/* destructor? */
(paren
op_star
(paren
r_void
(paren
op_star
)paren
(paren
r_struct
id|page
op_star
)paren
)paren
id|page
(braket
l_int|1
)braket
dot
id|mapping
)paren
(paren
id|page
)paren
suffix:semicolon
)brace
r_else
(brace
id|__page_cache_release
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
)brace
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|PageReserved
c_func
(paren
id|page
)paren
op_logical_and
id|put_page_testzero
c_func
(paren
id|page
)paren
)paren
id|__page_cache_release
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
macro_line|#else&t;&t;/* CONFIG_HUGETLB_PAGE */
DECL|macro|page_count
mdefine_line|#define page_count(p)&t;&t;atomic_read(&amp;(p)-&gt;count)
DECL|function|get_page
r_static
r_inline
r_void
id|get_page
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
(brace
id|atomic_inc
c_func
(paren
op_amp
id|page-&gt;count
)paren
suffix:semicolon
)brace
DECL|function|put_page
r_static
r_inline
r_void
id|put_page
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|PageReserved
c_func
(paren
id|page
)paren
op_logical_and
id|put_page_testzero
c_func
(paren
id|page
)paren
)paren
id|__page_cache_release
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
macro_line|#endif&t;&t;/* CONFIG_HUGETLB_PAGE */
multiline_comment|/*&n; * Multiple processes may &quot;see&quot; the same page. E.g. for untouched&n; * mappings of /dev/null, all processes see the same page full of&n; * zeroes, and text pages of executables and shared libraries have&n; * only one copy in memory, at most, normally.&n; *&n; * For the non-reserved pages, page-&gt;count denotes a reference count.&n; *   page-&gt;count == 0 means the page is free.&n; *   page-&gt;count == 1 means the page is used for exactly one purpose&n; *   (e.g. a private data page of one process).&n; *&n; * A page may be used for kmalloc() or anyone else who does a&n; * __get_free_page(). In this case the page-&gt;count is at least 1, and&n; * all other fields are unused but should be 0 or NULL. The&n; * management of this page is the responsibility of the one who uses&n; * it.&n; *&n; * The other pages (we may call them &quot;process pages&quot;) are completely&n; * managed by the Linux memory manager: I/O, buffers, swapping etc.&n; * The following discussion applies only to them.&n; *&n; * A page may belong to an inode&squot;s memory mapping. In this case,&n; * page-&gt;mapping is the pointer to the inode, and page-&gt;index is the&n; * file offset of the page, in units of PAGE_CACHE_SIZE.&n; *&n; * A page contains an opaque `private&squot; member, which belongs to the&n; * page&squot;s address_space.  Usually, this is the address of a circular&n; * list of the page&squot;s disk buffers.&n; *&n; * For pages belonging to inodes, the page-&gt;count is the number of&n; * attaches, plus 1 if `private&squot; contains something, plus one for&n; * the page cache itself.&n; *&n; * All pages belonging to an inode are in these doubly linked lists:&n; * mapping-&gt;clean_pages, mapping-&gt;dirty_pages and mapping-&gt;locked_pages;&n; * using the page-&gt;list list_head. These fields are also used for&n; * freelist managemet (when page-&gt;count==0).&n; *&n; * There is also a per-mapping radix tree mapping index to the page&n; * in memory if present. The tree is rooted at mapping-&gt;root.  &n; *&n; * All process pages can do I/O:&n; * - inode pages may need to be read from disk,&n; * - inode pages which have been modified and are MAP_SHARED may need&n; *   to be written to disk,&n; * - private pages which have been modified may need to be swapped out&n; *   to swap space and (later) to be read back into memory.&n; */
multiline_comment|/*&n; * The zone field is never updated after free_area_init_core()&n; * sets it, so none of the operations on it need to be atomic.&n; * We&squot;ll have up to (MAX_NUMNODES * MAX_NR_ZONES) zones total,&n; * so we use (MAX_NODES_SHIFT + MAX_ZONES_SHIFT) here to get enough bits.&n; */
DECL|macro|NODEZONE_SHIFT
mdefine_line|#define NODEZONE_SHIFT (sizeof(page_flags_t)*8 - MAX_NODES_SHIFT - MAX_ZONES_SHIFT)
DECL|macro|NODEZONE
mdefine_line|#define NODEZONE(node, zone)&t;((node &lt;&lt; ZONES_SHIFT) | zone)
DECL|function|page_zonenum
r_static
r_inline
r_int
r_int
id|page_zonenum
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
id|page-&gt;flags
op_rshift
id|NODEZONE_SHIFT
)paren
op_amp
(paren
op_complement
(paren
op_complement
l_int|0UL
op_lshift
id|ZONES_SHIFT
)paren
)paren
suffix:semicolon
)brace
DECL|function|page_nodenum
r_static
r_inline
r_int
r_int
id|page_nodenum
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
id|page-&gt;flags
op_rshift
(paren
id|NODEZONE_SHIFT
op_plus
id|ZONES_SHIFT
)paren
)paren
suffix:semicolon
)brace
r_struct
id|zone
suffix:semicolon
r_extern
r_struct
id|zone
op_star
id|zone_table
(braket
)braket
suffix:semicolon
DECL|function|page_zone
r_static
r_inline
r_struct
id|zone
op_star
id|page_zone
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
(brace
r_return
id|zone_table
(braket
id|page-&gt;flags
op_rshift
id|NODEZONE_SHIFT
)braket
suffix:semicolon
)brace
DECL|function|set_page_zone
r_static
r_inline
r_void
id|set_page_zone
c_func
(paren
r_struct
id|page
op_star
id|page
comma
r_int
r_int
id|nodezone_num
)paren
(brace
id|page-&gt;flags
op_and_assign
op_complement
(paren
op_complement
l_int|0UL
op_lshift
id|NODEZONE_SHIFT
)paren
suffix:semicolon
id|page-&gt;flags
op_or_assign
id|nodezone_num
op_lshift
id|NODEZONE_SHIFT
suffix:semicolon
)brace
macro_line|#ifndef CONFIG_DISCONTIGMEM
multiline_comment|/* The array of struct pages - for discontigmem use pgdat-&gt;lmem_map */
r_extern
r_struct
id|page
op_star
id|mem_map
suffix:semicolon
macro_line|#endif
DECL|function|lowmem_page_address
r_static
r_inline
r_void
op_star
id|lowmem_page_address
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
(brace
r_return
id|__va
c_func
(paren
id|page_to_pfn
c_func
(paren
id|page
)paren
op_lshift
id|PAGE_SHIFT
)paren
suffix:semicolon
)brace
macro_line|#if defined(CONFIG_HIGHMEM) &amp;&amp; !defined(WANT_PAGE_VIRTUAL)
DECL|macro|HASHED_PAGE_VIRTUAL
mdefine_line|#define HASHED_PAGE_VIRTUAL
macro_line|#endif
macro_line|#if defined(WANT_PAGE_VIRTUAL)
DECL|macro|page_address
mdefine_line|#define page_address(page) ((page)-&gt;virtual)
DECL|macro|set_page_address
mdefine_line|#define set_page_address(page, address)&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;(page)-&gt;virtual = (address);&t;&t;&bslash;&n;&t;} while(0)
DECL|macro|page_address_init
mdefine_line|#define page_address_init()  do { } while(0)
macro_line|#endif
macro_line|#if defined(HASHED_PAGE_VIRTUAL)
r_void
op_star
id|page_address
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
suffix:semicolon
r_void
id|set_page_address
c_func
(paren
r_struct
id|page
op_star
id|page
comma
r_void
op_star
r_virtual
)paren
suffix:semicolon
r_void
id|page_address_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if !defined(HASHED_PAGE_VIRTUAL) &amp;&amp; !defined(WANT_PAGE_VIRTUAL)
DECL|macro|page_address
mdefine_line|#define page_address(page) lowmem_page_address(page)
DECL|macro|set_page_address
mdefine_line|#define set_page_address(page, address)  do { } while(0)
DECL|macro|page_address_init
mdefine_line|#define page_address_init()  do { } while(0)
macro_line|#endif
multiline_comment|/*&n; * Return true if this page is mapped into pagetables.  Subtle: test pte.direct&n; * rather than pte.chain.  Because sometimes pte.direct is 64-bit, and .chain&n; * is only 32-bit.&n; */
DECL|function|page_mapped
r_static
r_inline
r_int
id|page_mapped
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
(brace
r_return
id|page-&gt;pte.direct
op_ne
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Error return values for the *_nopage functions&n; */
DECL|macro|NOPAGE_SIGBUS
mdefine_line|#define NOPAGE_SIGBUS&t;(NULL)
DECL|macro|NOPAGE_OOM
mdefine_line|#define NOPAGE_OOM&t;((struct page *) (-1))
multiline_comment|/*&n; * Different kinds of faults, as returned by handle_mm_fault().&n; * Used to decide whether a process gets delivered SIGBUS or&n; * just gets major/minor fault counters bumped up.&n; */
DECL|macro|VM_FAULT_OOM
mdefine_line|#define VM_FAULT_OOM&t;(-1)
DECL|macro|VM_FAULT_SIGBUS
mdefine_line|#define VM_FAULT_SIGBUS&t;0
DECL|macro|VM_FAULT_MINOR
mdefine_line|#define VM_FAULT_MINOR&t;1
DECL|macro|VM_FAULT_MAJOR
mdefine_line|#define VM_FAULT_MAJOR&t;2
DECL|macro|offset_in_page
mdefine_line|#define offset_in_page(p)&t;((unsigned long)(p) &amp; ~PAGE_MASK)
r_extern
r_void
id|show_free_areas
c_func
(paren
r_void
)paren
suffix:semicolon
r_struct
id|page
op_star
id|shmem_nopage
c_func
(paren
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
op_star
id|type
)paren
suffix:semicolon
r_struct
id|file
op_star
id|shmem_file_setup
c_func
(paren
r_char
op_star
id|name
comma
id|loff_t
id|size
comma
r_int
r_int
id|flags
)paren
suffix:semicolon
r_void
id|shmem_lock
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_int
id|lock
)paren
suffix:semicolon
r_int
id|shmem_zero_setup
c_func
(paren
r_struct
id|vm_area_struct
op_star
)paren
suffix:semicolon
r_void
id|zap_page_range
c_func
(paren
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
r_int
id|size
)paren
suffix:semicolon
r_int
id|unmap_vmas
c_func
(paren
r_struct
id|mmu_gather
op_star
op_star
id|tlbp
comma
r_struct
id|mm_struct
op_star
id|mm
comma
r_struct
id|vm_area_struct
op_star
id|start_vma
comma
r_int
r_int
id|start_addr
comma
r_int
r_int
id|end_addr
comma
r_int
r_int
op_star
id|nr_accounted
)paren
suffix:semicolon
r_void
id|unmap_page_range
c_func
(paren
r_struct
id|mmu_gather
op_star
id|tlb
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
r_int
id|size
)paren
suffix:semicolon
r_void
id|clear_page_tables
c_func
(paren
r_struct
id|mmu_gather
op_star
id|tlb
comma
r_int
r_int
id|first
comma
r_int
id|nr
)paren
suffix:semicolon
r_int
id|copy_page_range
c_func
(paren
r_struct
id|mm_struct
op_star
id|dst
comma
r_struct
id|mm_struct
op_star
id|src
comma
r_struct
id|vm_area_struct
op_star
id|vma
)paren
suffix:semicolon
r_int
id|zeromap_page_range
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|from
comma
r_int
r_int
id|size
comma
id|pgprot_t
id|prot
)paren
suffix:semicolon
r_extern
r_void
id|invalidate_mmap_range
c_func
(paren
r_struct
id|address_space
op_star
id|mapping
comma
id|loff_t
r_const
id|holebegin
comma
id|loff_t
r_const
id|holelen
)paren
suffix:semicolon
r_extern
r_int
id|vmtruncate
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
id|loff_t
id|offset
)paren
suffix:semicolon
r_extern
id|pmd_t
op_star
id|FASTCALL
c_func
(paren
id|__pmd_alloc
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
id|pgd_t
op_star
id|pgd
comma
r_int
r_int
id|address
)paren
)paren
suffix:semicolon
r_extern
id|pte_t
op_star
id|FASTCALL
c_func
(paren
id|pte_alloc_kernel
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
id|pmd_t
op_star
id|pmd
comma
r_int
r_int
id|address
)paren
)paren
suffix:semicolon
r_extern
id|pte_t
op_star
id|FASTCALL
c_func
(paren
id|pte_alloc_map
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
id|pmd_t
op_star
id|pmd
comma
r_int
r_int
id|address
)paren
)paren
suffix:semicolon
r_extern
r_int
id|install_page
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
id|addr
comma
r_struct
id|page
op_star
id|page
comma
id|pgprot_t
id|prot
)paren
suffix:semicolon
r_extern
r_int
id|install_file_pte
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
id|addr
comma
r_int
r_int
id|pgoff
comma
id|pgprot_t
id|prot
)paren
suffix:semicolon
r_extern
r_int
id|handle_mm_fault
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
id|write_access
)paren
suffix:semicolon
r_extern
r_int
id|make_pages_present
c_func
(paren
r_int
r_int
id|addr
comma
r_int
r_int
id|end
)paren
suffix:semicolon
r_extern
r_int
id|access_process_vm
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
r_int
r_int
id|addr
comma
r_void
op_star
id|buf
comma
r_int
id|len
comma
r_int
id|write
)paren
suffix:semicolon
r_void
id|put_dirty_page
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
r_struct
id|page
op_star
id|page
comma
r_int
r_int
id|address
comma
id|pgprot_t
id|prot
)paren
suffix:semicolon
r_int
id|get_user_pages
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
r_struct
id|mm_struct
op_star
id|mm
comma
r_int
r_int
id|start
comma
r_int
id|len
comma
r_int
id|write
comma
r_int
id|force
comma
r_struct
id|page
op_star
op_star
id|pages
comma
r_struct
id|vm_area_struct
op_star
op_star
id|vmas
)paren
suffix:semicolon
r_int
id|__set_page_dirty_buffers
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
suffix:semicolon
r_int
id|__set_page_dirty_nobuffers
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
suffix:semicolon
r_int
id|set_page_dirty_lock
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
suffix:semicolon
r_int
id|clear_page_dirty_for_io
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
suffix:semicolon
multiline_comment|/*&n; * Prototype to add a shrinker callback for ageable caches.&n; * &n; * These functions are passed a count `nr_to_scan&squot; and a gfpmask.  They should&n; * scan `nr_to_scan&squot; objects, attempting to free them.&n; *&n; * The callback must the number of objects which remain in the cache.&n; *&n; * The callback will be passes nr_to_scan == 0 when the VM is querying the&n; * cache size, so a fastpath for that case is appropriate.&n; */
DECL|typedef|shrinker_t
r_typedef
r_int
(paren
op_star
id|shrinker_t
)paren
(paren
r_int
id|nr_to_scan
comma
r_int
r_int
id|gfp_mask
)paren
suffix:semicolon
multiline_comment|/*&n; * Add an aging callback.  The int is the number of &squot;seeks&squot; it takes&n; * to recreate one of the objects that these functions age.&n; */
DECL|macro|DEFAULT_SEEKS
mdefine_line|#define DEFAULT_SEEKS 2
r_struct
id|shrinker
suffix:semicolon
r_extern
r_struct
id|shrinker
op_star
id|set_shrinker
c_func
(paren
r_int
comma
id|shrinker_t
)paren
suffix:semicolon
r_extern
r_void
id|remove_shrinker
c_func
(paren
r_struct
id|shrinker
op_star
id|shrinker
)paren
suffix:semicolon
multiline_comment|/*&n; * If the mapping doesn&squot;t provide a set_page_dirty a_op, then&n; * just fall through and assume that it wants buffer_heads.&n; * FIXME: make the method unconditional.&n; */
DECL|function|set_page_dirty
r_static
r_inline
r_int
id|set_page_dirty
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
(brace
r_if
c_cond
(paren
id|page-&gt;mapping
)paren
(brace
r_int
(paren
op_star
id|spd
)paren
(paren
r_struct
id|page
op_star
)paren
suffix:semicolon
id|spd
op_assign
id|page-&gt;mapping-&gt;a_ops-&gt;set_page_dirty
suffix:semicolon
r_if
c_cond
(paren
id|spd
)paren
r_return
(paren
op_star
id|spd
)paren
(paren
id|page
)paren
suffix:semicolon
)brace
r_return
id|__set_page_dirty_buffers
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * On a two-level page table, this ends up being trivial. Thus the&n; * inlining and the symmetry break with pte_alloc_map() that does all&n; * of this out-of-line.&n; */
DECL|function|pmd_alloc
r_static
r_inline
id|pmd_t
op_star
id|pmd_alloc
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
id|pgd_t
op_star
id|pgd
comma
r_int
r_int
id|address
)paren
(brace
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
id|__pmd_alloc
c_func
(paren
id|mm
comma
id|pgd
comma
id|address
)paren
suffix:semicolon
r_return
id|pmd_offset
c_func
(paren
id|pgd
comma
id|address
)paren
suffix:semicolon
)brace
r_extern
r_void
id|free_area_init
c_func
(paren
r_int
r_int
op_star
id|zones_size
)paren
suffix:semicolon
r_extern
r_void
id|free_area_init_node
c_func
(paren
r_int
id|nid
comma
id|pg_data_t
op_star
id|pgdat
comma
r_struct
id|page
op_star
id|pmap
comma
r_int
r_int
op_star
id|zones_size
comma
r_int
r_int
id|zone_start_pfn
comma
r_int
r_int
op_star
id|zholes_size
)paren
suffix:semicolon
r_extern
r_void
id|memmap_init_zone
c_func
(paren
r_struct
id|page
op_star
comma
r_int
r_int
comma
r_int
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|mem_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|show_mem
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|si_meminfo
c_func
(paren
r_struct
id|sysinfo
op_star
id|val
)paren
suffix:semicolon
r_extern
r_void
id|si_meminfo_node
c_func
(paren
r_struct
id|sysinfo
op_star
id|val
comma
r_int
id|nid
)paren
suffix:semicolon
multiline_comment|/* mmap.c */
r_extern
r_void
id|insert_vm_struct
c_func
(paren
r_struct
id|mm_struct
op_star
comma
r_struct
id|vm_area_struct
op_star
)paren
suffix:semicolon
r_extern
r_void
id|__vma_link_rb
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
id|rb_node
op_star
op_star
comma
r_struct
id|rb_node
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|vm_area_struct
op_star
id|copy_vma
c_func
(paren
r_struct
id|vm_area_struct
op_star
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
suffix:semicolon
r_extern
r_void
id|vma_relink_file
c_func
(paren
r_struct
id|vm_area_struct
op_star
comma
r_struct
id|vm_area_struct
op_star
)paren
suffix:semicolon
r_extern
r_void
id|exit_mmap
c_func
(paren
r_struct
id|mm_struct
op_star
)paren
suffix:semicolon
r_extern
r_int
r_int
id|get_unmapped_area
c_func
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
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
r_int
id|do_mmap_pgoff
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
id|flag
comma
r_int
r_int
id|pgoff
)paren
suffix:semicolon
DECL|function|do_mmap
r_static
r_inline
r_int
r_int
id|do_mmap
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
id|flag
comma
r_int
r_int
id|offset
)paren
(brace
r_int
r_int
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
(paren
id|offset
op_plus
id|PAGE_ALIGN
c_func
(paren
id|len
)paren
)paren
OL
id|offset
)paren
r_goto
id|out
suffix:semicolon
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
id|ret
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
id|flag
comma
id|offset
op_rshift
id|PAGE_SHIFT
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|ret
suffix:semicolon
)brace
r_extern
r_int
id|do_munmap
c_func
(paren
r_struct
id|mm_struct
op_star
comma
r_int
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
r_int
id|do_brk
c_func
(paren
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_static
r_inline
r_void
DECL|function|__vma_unlink
id|__vma_unlink
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
r_struct
id|vm_area_struct
op_star
id|prev
)paren
(brace
id|prev-&gt;vm_next
op_assign
id|vma-&gt;vm_next
suffix:semicolon
id|rb_erase
c_func
(paren
op_amp
id|vma-&gt;vm_rb
comma
op_amp
id|mm-&gt;mm_rb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mm-&gt;mmap_cache
op_eq
id|vma
)paren
id|mm-&gt;mmap_cache
op_assign
id|prev
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|can_vma_merge
id|can_vma_merge
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|vm_flags
)paren
(brace
macro_line|#ifdef CONFIG_MMU
r_if
c_cond
(paren
op_logical_neg
id|vma-&gt;vm_file
op_logical_and
id|vma-&gt;vm_flags
op_eq
id|vm_flags
)paren
r_return
l_int|1
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* filemap.c */
r_extern
r_int
r_int
id|page_unuse
c_func
(paren
r_struct
id|page
op_star
)paren
suffix:semicolon
r_extern
r_void
id|truncate_inode_pages
c_func
(paren
r_struct
id|address_space
op_star
comma
id|loff_t
)paren
suffix:semicolon
multiline_comment|/* generic vm_area_ops exported for stackable file systems */
r_struct
id|page
op_star
id|filemap_nopage
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
op_star
)paren
suffix:semicolon
multiline_comment|/* mm/page-writeback.c */
r_int
id|write_one_page
c_func
(paren
r_struct
id|page
op_star
id|page
comma
r_int
id|wait
)paren
suffix:semicolon
multiline_comment|/* readahead.c */
DECL|macro|VM_MAX_READAHEAD
mdefine_line|#define VM_MAX_READAHEAD&t;128&t;/* kbytes */
DECL|macro|VM_MIN_READAHEAD
mdefine_line|#define VM_MIN_READAHEAD&t;16&t;/* kbytes (includes current page) */
r_int
id|do_page_cache_readahead
c_func
(paren
r_struct
id|address_space
op_star
id|mapping
comma
r_struct
id|file
op_star
id|filp
comma
r_int
r_int
id|offset
comma
r_int
r_int
id|nr_to_read
)paren
suffix:semicolon
r_int
id|force_page_cache_readahead
c_func
(paren
r_struct
id|address_space
op_star
id|mapping
comma
r_struct
id|file
op_star
id|filp
comma
r_int
r_int
id|offset
comma
r_int
r_int
id|nr_to_read
)paren
suffix:semicolon
r_void
id|page_cache_readahead
c_func
(paren
r_struct
id|address_space
op_star
id|mapping
comma
r_struct
id|file_ra_state
op_star
id|ra
comma
r_struct
id|file
op_star
id|filp
comma
r_int
r_int
id|offset
)paren
suffix:semicolon
r_void
id|handle_ra_miss
c_func
(paren
r_struct
id|address_space
op_star
id|mapping
comma
r_struct
id|file_ra_state
op_star
id|ra
comma
id|pgoff_t
id|offset
)paren
suffix:semicolon
r_int
r_int
id|max_sane_readahead
c_func
(paren
r_int
r_int
id|nr
)paren
suffix:semicolon
multiline_comment|/* Do stack extension */
r_extern
r_int
id|expand_stack
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|address
)paren
suffix:semicolon
multiline_comment|/* Look up the first VMA which satisfies  addr &lt; vm_end,  NULL if none. */
r_extern
r_struct
id|vm_area_struct
op_star
id|find_vma
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_int
r_int
id|addr
)paren
suffix:semicolon
r_extern
r_struct
id|vm_area_struct
op_star
id|find_vma_prev
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_int
r_int
id|addr
comma
r_struct
id|vm_area_struct
op_star
op_star
id|pprev
)paren
suffix:semicolon
r_extern
r_int
id|split_vma
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
id|addr
comma
r_int
id|new_below
)paren
suffix:semicolon
multiline_comment|/* Look up the first VMA which intersects the interval start_addr..end_addr-1,&n;   NULL if none.  Assume start_addr &lt; end_addr. */
DECL|function|find_vma_intersection
r_static
r_inline
r_struct
id|vm_area_struct
op_star
id|find_vma_intersection
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_int
r_int
id|start_addr
comma
r_int
r_int
id|end_addr
)paren
(brace
r_struct
id|vm_area_struct
op_star
id|vma
op_assign
id|find_vma
c_func
(paren
id|mm
comma
id|start_addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vma
op_logical_and
id|end_addr
op_le
id|vma-&gt;vm_start
)paren
id|vma
op_assign
l_int|NULL
suffix:semicolon
r_return
id|vma
suffix:semicolon
)brace
r_extern
r_struct
id|vm_area_struct
op_star
id|find_extend_vma
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_int
r_int
id|addr
)paren
suffix:semicolon
r_extern
r_int
r_int
id|nr_used_zone_pages
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_struct
id|page
op_star
id|vmalloc_to_page
c_func
(paren
r_void
op_star
id|addr
)paren
suffix:semicolon
r_extern
r_struct
id|page
op_star
id|follow_page
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
r_int
id|write
)paren
suffix:semicolon
r_extern
r_int
id|remap_page_range
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|from
comma
r_int
r_int
id|to
comma
r_int
r_int
id|size
comma
id|pgprot_t
id|prot
)paren
suffix:semicolon
macro_line|#ifndef CONFIG_DEBUG_PAGEALLOC
r_static
r_inline
r_void
DECL|function|kernel_map_pages
id|kernel_map_pages
c_func
(paren
r_struct
id|page
op_star
id|page
comma
r_int
id|numpages
comma
r_int
id|enable
)paren
(brace
)brace
macro_line|#endif
macro_line|#ifndef CONFIG_ARCH_GATE_AREA
r_extern
r_struct
id|vm_area_struct
op_star
id|get_gate_vma
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
)paren
suffix:semicolon
r_int
id|in_gate_area
c_func
(paren
r_struct
id|task_struct
op_star
id|task
comma
r_int
r_int
id|addr
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _LINUX_MM_H */
eof
