multiline_comment|/*&n; * kernel/power/pmdisk.c - Suspend-to-disk implmentation&n; *&n; * This STD implementation is initially derived from swsusp (suspend-to-swap).&n; * The original copyright on that was: &n; *&n; * Copyright (C) 1998-2001 Gabor Kuti &lt;seasons@fornax.hu&gt;&n; * Copyright (C) 1998,2001,2002 Pavel Machek &lt;pavel@suse.cz&gt;&n; *&n; * The additional parts are: &n; * &n; * Copyright (C) 2003 Patrick Mochel&n; * Copyright (C) 2003 Open Source Development Lab&n; * &n; * This file is released under the GPLv2. &n; *&n; * For more information, please see the text files in Documentation/power/&n; *&n; */
DECL|macro|DEBUG
macro_line|#undef DEBUG
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/bio.h&gt;
macro_line|#include &lt;linux/suspend.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/reboot.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/swapops.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;linux/utsname.h&gt;
macro_line|#include &lt;asm/mmu_context.h&gt;
macro_line|#include &quot;power.h&quot;
r_extern
id|asmlinkage
r_int
id|pmdisk_arch_suspend
c_func
(paren
r_int
id|resume
)paren
suffix:semicolon
multiline_comment|/* Variables to be preserved over suspend */
r_extern
r_int
id|pagedir_order_check
suffix:semicolon
r_extern
r_int
id|nr_copy_pages_check
suffix:semicolon
multiline_comment|/* For resume= kernel option */
DECL|variable|resume_file
r_static
r_char
id|resume_file
(braket
l_int|256
)braket
op_assign
id|CONFIG_PM_DISK_PARTITION
suffix:semicolon
DECL|variable|resume_device
r_static
id|dev_t
id|resume_device
suffix:semicolon
multiline_comment|/* Local variables that should not be affected by save */
r_extern
r_int
r_int
id|nr_copy_pages
suffix:semicolon
multiline_comment|/* Suspend pagedir is allocated before final copy, therefore it&n;   must be freed after resume &n;&n;   Warning: this is evil. There are actually two pagedirs at time of&n;   resume. One is &quot;pagedir_save&quot;, which is empty frame allocated at&n;   time of suspend, that must be freed. Second is &quot;pagedir_nosave&quot;, &n;   allocated at time of resume, that travels through memory not to&n;   collide with anything.&n; */
r_extern
id|suspend_pagedir_t
op_star
id|pagedir_nosave
suffix:semicolon
r_extern
id|suspend_pagedir_t
op_star
id|pagedir_save
suffix:semicolon
r_extern
r_int
id|pagedir_order
suffix:semicolon
DECL|struct|pmdisk_info
r_struct
id|pmdisk_info
(brace
DECL|member|uts
r_struct
id|new_utsname
id|uts
suffix:semicolon
DECL|member|version_code
id|u32
id|version_code
suffix:semicolon
DECL|member|num_physpages
r_int
r_int
id|num_physpages
suffix:semicolon
DECL|member|cpus
r_int
id|cpus
suffix:semicolon
DECL|member|image_pages
r_int
r_int
id|image_pages
suffix:semicolon
DECL|member|pagedir_pages
r_int
r_int
id|pagedir_pages
suffix:semicolon
DECL|member|pagedir
id|swp_entry_t
id|pagedir
(braket
l_int|768
)braket
suffix:semicolon
DECL|variable|pmdisk_info
)brace
id|__attribute__
c_func
(paren
(paren
id|aligned
c_func
(paren
id|PAGE_SIZE
)paren
)paren
)paren
id|pmdisk_info
suffix:semicolon
DECL|macro|PMDISK_SIG
mdefine_line|#define PMDISK_SIG&t;&quot;pmdisk-swap1&quot;
DECL|struct|pmdisk_header
r_struct
id|pmdisk_header
(brace
DECL|member|reserved
r_char
id|reserved
(braket
id|PAGE_SIZE
op_minus
l_int|20
op_minus
r_sizeof
(paren
id|swp_entry_t
)paren
)braket
suffix:semicolon
DECL|member|pmdisk_info
id|swp_entry_t
id|pmdisk_info
suffix:semicolon
DECL|member|orig_sig
r_char
id|orig_sig
(braket
l_int|10
)braket
suffix:semicolon
DECL|member|sig
r_char
id|sig
(braket
l_int|10
)braket
suffix:semicolon
DECL|variable|pmdisk_header
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
comma
id|aligned
c_func
(paren
id|PAGE_SIZE
)paren
)paren
)paren
id|pmdisk_header
suffix:semicolon
multiline_comment|/*&n; * XXX: We try to keep some more pages free so that I/O operations succeed&n; * without paging. Might this be more?&n; */
DECL|macro|PAGES_FOR_IO
mdefine_line|#define PAGES_FOR_IO&t;512
multiline_comment|/*&n; * Saving part...&n; */
multiline_comment|/* We memorize in swapfile_used what swap devices are used for suspension */
DECL|macro|SWAPFILE_UNUSED
mdefine_line|#define SWAPFILE_UNUSED    0
DECL|macro|SWAPFILE_SUSPEND
mdefine_line|#define SWAPFILE_SUSPEND   1&t;/* This is the suspending device */
DECL|macro|SWAPFILE_IGNORED
mdefine_line|#define SWAPFILE_IGNORED   2&t;/* Those are other swap devices ignored for suspension */
r_extern
r_int
r_int
id|swapfile_used
(braket
id|MAX_SWAPFILES
)braket
suffix:semicolon
r_extern
r_int
r_int
id|root_swap
suffix:semicolon
r_extern
r_int
id|swsusp_swap_check
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|swsusp_swap_lock
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|mark_swapfiles
r_static
r_int
id|mark_swapfiles
c_func
(paren
id|swp_entry_t
id|prev
)paren
(brace
r_int
id|error
suffix:semicolon
id|rw_swap_page_sync
c_func
(paren
id|READ
comma
id|swp_entry
c_func
(paren
id|root_swap
comma
l_int|0
)paren
comma
id|virt_to_page
c_func
(paren
(paren
r_int
r_int
)paren
op_amp
id|pmdisk_header
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|memcmp
c_func
(paren
l_string|&quot;SWAP-SPACE&quot;
comma
id|pmdisk_header.sig
comma
l_int|10
)paren
op_logical_or
op_logical_neg
id|memcmp
c_func
(paren
l_string|&quot;SWAPSPACE2&quot;
comma
id|pmdisk_header.sig
comma
l_int|10
)paren
)paren
(brace
id|memcpy
c_func
(paren
id|pmdisk_header.orig_sig
comma
id|pmdisk_header.sig
comma
l_int|10
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|pmdisk_header.sig
comma
id|PMDISK_SIG
comma
l_int|10
)paren
suffix:semicolon
id|pmdisk_header.pmdisk_info
op_assign
id|prev
suffix:semicolon
id|error
op_assign
id|rw_swap_page_sync
c_func
(paren
id|WRITE
comma
id|swp_entry
c_func
(paren
id|root_swap
comma
l_int|0
)paren
comma
id|virt_to_page
c_func
(paren
(paren
r_int
r_int
)paren
op_amp
id|pmdisk_header
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|pr_debug
c_func
(paren
l_string|&quot;pmdisk: Partition is not swap space.&bslash;n&quot;
)paren
suffix:semicolon
id|error
op_assign
op_minus
id|ENODEV
suffix:semicolon
)brace
r_return
id|error
suffix:semicolon
)brace
r_extern
r_int
id|swsusp_write_page
c_func
(paren
r_int
r_int
id|addr
comma
id|swp_entry_t
op_star
id|entry
)paren
suffix:semicolon
r_extern
r_int
id|swsusp_data_write
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|swsusp_data_free
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/**&n; *&t;free_pagedir - Free pages used by the page directory.&n; */
DECL|function|free_pagedir_entries
r_static
r_void
id|free_pagedir_entries
c_func
(paren
r_void
)paren
(brace
r_int
id|num
op_assign
id|pmdisk_info.pagedir_pages
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
id|num
suffix:semicolon
id|i
op_increment
)paren
id|swap_free
c_func
(paren
id|pmdisk_info.pagedir
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;write_pagedir - Write the array of pages holding the page directory.&n; *&t;@last:&t;Last swap entry we write (needed for header).&n; */
DECL|function|write_pagedir
r_static
r_int
id|write_pagedir
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|addr
op_assign
(paren
r_int
r_int
)paren
id|pagedir_nosave
suffix:semicolon
r_int
id|error
op_assign
l_int|0
suffix:semicolon
r_int
id|n
op_assign
id|SUSPEND_PD_PAGES
c_func
(paren
id|nr_copy_pages
)paren
suffix:semicolon
r_int
id|i
suffix:semicolon
id|pmdisk_info.pagedir_pages
op_assign
id|n
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Writing pagedir (%d pages)&bslash;n&quot;
comma
id|n
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
id|n
op_logical_and
op_logical_neg
id|error
suffix:semicolon
id|i
op_increment
comma
id|addr
op_add_assign
id|PAGE_SIZE
)paren
id|error
op_assign
id|swsusp_write_page
c_func
(paren
id|addr
comma
op_amp
id|pmdisk_info.pagedir
(braket
id|i
)braket
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
macro_line|#ifdef DEBUG
DECL|function|dump_pmdisk_info
r_static
r_void
id|dump_pmdisk_info
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
l_string|&quot; pmdisk: Version: %u&bslash;n&quot;
comma
id|pmdisk_info.version_code
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; pmdisk: Num Pages: %ld&bslash;n&quot;
comma
id|pmdisk_info.num_physpages
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; pmdisk: UTS Sys: %s&bslash;n&quot;
comma
id|pmdisk_info.uts.sysname
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; pmdisk: UTS Node: %s&bslash;n&quot;
comma
id|pmdisk_info.uts.nodename
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; pmdisk: UTS Release: %s&bslash;n&quot;
comma
id|pmdisk_info.uts.release
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; pmdisk: UTS Version: %s&bslash;n&quot;
comma
id|pmdisk_info.uts.version
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; pmdisk: UTS Machine: %s&bslash;n&quot;
comma
id|pmdisk_info.uts.machine
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; pmdisk: UTS Domain: %s&bslash;n&quot;
comma
id|pmdisk_info.uts.domainname
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; pmdisk: CPUs: %d&bslash;n&quot;
comma
id|pmdisk_info.cpus
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; pmdisk: Image: %ld Pages&bslash;n&quot;
comma
id|pmdisk_info.image_pages
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; pmdisk: Pagedir: %ld Pages&bslash;n&quot;
comma
id|pmdisk_info.pagedir_pages
)paren
suffix:semicolon
)brace
macro_line|#else
DECL|function|dump_pmdisk_info
r_static
r_void
id|dump_pmdisk_info
c_func
(paren
r_void
)paren
(brace
)brace
macro_line|#endif
DECL|function|init_header
r_static
r_void
id|init_header
c_func
(paren
r_void
)paren
(brace
id|memset
c_func
(paren
op_amp
id|pmdisk_info
comma
l_int|0
comma
r_sizeof
(paren
id|pmdisk_info
)paren
)paren
suffix:semicolon
id|pmdisk_info.version_code
op_assign
id|LINUX_VERSION_CODE
suffix:semicolon
id|pmdisk_info.num_physpages
op_assign
id|num_physpages
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|pmdisk_info.uts
comma
op_amp
id|system_utsname
comma
r_sizeof
(paren
id|system_utsname
)paren
)paren
suffix:semicolon
id|pmdisk_info.cpus
op_assign
id|num_online_cpus
c_func
(paren
)paren
suffix:semicolon
id|pmdisk_info.image_pages
op_assign
id|nr_copy_pages
suffix:semicolon
id|dump_pmdisk_info
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;write_header - Fill and write the suspend header.&n; *&t;@entry:&t;Location of the last swap entry used.&n; *&n; *&t;Allocate a page, fill header, write header. &n; *&n; *&t;@entry is the location of the last pagedir entry written on &n; *&t;entrance. On exit, it contains the location of the header. &n; */
DECL|function|write_header
r_static
r_int
id|write_header
c_func
(paren
id|swp_entry_t
op_star
id|entry
)paren
(brace
r_return
id|swsusp_write_page
c_func
(paren
(paren
r_int
r_int
)paren
op_amp
id|pmdisk_info
comma
id|entry
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;write_suspend_image - Write entire image and metadata.&n; *&n; */
DECL|function|write_suspend_image
r_static
r_int
id|write_suspend_image
c_func
(paren
r_void
)paren
(brace
r_int
id|error
suffix:semicolon
id|swp_entry_t
id|prev
op_assign
(brace
l_int|0
)brace
suffix:semicolon
r_if
c_cond
(paren
(paren
id|error
op_assign
id|swsusp_data_write
c_func
(paren
)paren
)paren
)paren
r_goto
id|FreeData
suffix:semicolon
r_if
c_cond
(paren
(paren
id|error
op_assign
id|write_pagedir
c_func
(paren
)paren
)paren
)paren
r_goto
id|FreePagedir
suffix:semicolon
r_if
c_cond
(paren
(paren
id|error
op_assign
id|write_header
c_func
(paren
op_amp
id|prev
)paren
)paren
)paren
r_goto
id|FreePagedir
suffix:semicolon
id|error
op_assign
id|mark_swapfiles
c_func
(paren
id|prev
)paren
suffix:semicolon
id|Done
suffix:colon
r_return
id|error
suffix:semicolon
id|FreePagedir
suffix:colon
id|free_pagedir_entries
c_func
(paren
)paren
suffix:semicolon
id|FreeData
suffix:colon
id|swsusp_data_free
c_func
(paren
)paren
suffix:semicolon
r_goto
id|Done
suffix:semicolon
)brace
r_extern
r_void
id|free_suspend_pagedir
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
id|suspend_prepare_image
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/**&n; *&t;pmdisk_suspend - Atomically snapshot the system.&n; *&n; *&t;This must be called with interrupts disabled, to prevent the &n; *&t;system changing at all from underneath us. &n; *&n; *&t;To do this, we count the number of pages in the system that we &n; *&t;need to save; make sure&t;we have enough memory and swap to clone&n; *&t;the pages and save them in swap, allocate the space to hold them,&n; *&t;and then snapshot them all.&n; */
DECL|function|pmdisk_suspend
r_int
id|pmdisk_suspend
c_func
(paren
r_void
)paren
(brace
r_int
id|error
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|error
op_assign
id|swsusp_swap_check
c_func
(paren
)paren
)paren
)paren
r_return
id|error
suffix:semicolon
r_return
id|suspend_prepare_image
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;suspend_save_image - Prepare and write saved image to swap.&n; *&n; *&t;IRQs are re-enabled here so we can resume devices and safely write&n; *&t;to the swap devices. We disable them again before we leave.&n; *&n; *&t;The second swsusp_swap_lock() will unlock ignored swap devices since&n; *&t;writing is finished.&n; *&t;It is important _NOT_ to umount filesystems at this point. We want&n; *&t;them synced (in case something goes wrong) but we DO not want to mark&n; *&t;filesystem clean: it is not. (And it does not matter, if we resume&n; *&t;correctly, we&squot;ll mark system clean, anyway.)&n; */
DECL|function|suspend_save_image
r_static
r_int
id|suspend_save_image
c_func
(paren
r_void
)paren
(brace
r_int
id|error
suffix:semicolon
id|device_resume
c_func
(paren
)paren
suffix:semicolon
id|swsusp_swap_lock
c_func
(paren
)paren
suffix:semicolon
id|error
op_assign
id|write_suspend_image
c_func
(paren
)paren
suffix:semicolon
id|swsusp_swap_lock
c_func
(paren
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/*&n; * Magic happens here&n; */
DECL|function|pmdisk_resume
r_int
id|pmdisk_resume
c_func
(paren
r_void
)paren
(brace
id|BUG_ON
(paren
id|nr_copy_pages_check
op_ne
id|nr_copy_pages
)paren
suffix:semicolon
id|BUG_ON
(paren
id|pagedir_order_check
op_ne
id|pagedir_order
)paren
suffix:semicolon
multiline_comment|/* Even mappings of &quot;global&quot; things (vmalloc) need to be fixed */
id|__flush_tlb_global
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* pmdisk_arch_suspend() is implemented in arch/?/power/pmdisk.S,&n;   and basically does:&n;&n;&t;if (!resume) {&n;&t;&t;save_processor_state();&n;&t;&t;SAVE_REGISTERS&n;&t;&t;return pmdisk_suspend();&n;&t;}&n;&t;GO_TO_SWAPPER_PAGE_TABLES&n;&t;COPY_PAGES_BACK&n;&t;RESTORE_REGISTERS&n;&t;restore_processor_state();&n;&t;return pmdisk_resume();&n;&n; */
multiline_comment|/* More restore stuff */
DECL|variable|resume_bdev
r_static
r_struct
id|block_device
op_star
id|resume_bdev
suffix:semicolon
multiline_comment|/**&n; *&t;Using bio to read from swap.&n; *&t;This code requires a bit more work than just using buffer heads&n; *&t;but, it is the recommended way for 2.5/2.6.&n; *&t;The following are to signal the beginning and end of I/O. Bios&n; *&t;finish asynchronously, while we want them to happen synchronously.&n; *&t;A simple atomic_t, and a wait loop take care of this problem.&n; */
DECL|variable|io_done
r_static
id|atomic_t
id|io_done
op_assign
id|ATOMIC_INIT
c_func
(paren
l_int|0
)paren
suffix:semicolon
DECL|function|start_io
r_static
r_void
id|start_io
c_func
(paren
r_void
)paren
(brace
id|atomic_set
c_func
(paren
op_amp
id|io_done
comma
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|end_io
r_static
r_int
id|end_io
c_func
(paren
r_struct
id|bio
op_star
id|bio
comma
r_int
r_int
id|num
comma
r_int
id|err
)paren
(brace
id|atomic_set
c_func
(paren
op_amp
id|io_done
comma
l_int|0
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|wait_io
r_static
r_void
id|wait_io
c_func
(paren
r_void
)paren
(brace
r_while
c_loop
(paren
id|atomic_read
c_func
(paren
op_amp
id|io_done
)paren
)paren
(brace
id|io_schedule
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/**&n; *&t;submit - submit BIO request.&n; *&t;@rw:&t;READ or WRITE.&n; *&t;@off&t;physical offset of page.&n; *&t;@page:&t;page we&squot;re reading or writing.&n; *&n; *&t;Straight from the textbook - allocate and initialize the bio.&n; *&t;If we&squot;re writing, make sure the page is marked as dirty.&n; *&t;Then submit it and wait.&n; */
DECL|function|submit
r_static
r_int
id|submit
c_func
(paren
r_int
id|rw
comma
id|pgoff_t
id|page_off
comma
r_void
op_star
id|page
)paren
(brace
r_int
id|error
op_assign
l_int|0
suffix:semicolon
r_struct
id|bio
op_star
id|bio
suffix:semicolon
id|bio
op_assign
id|bio_alloc
c_func
(paren
id|GFP_ATOMIC
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bio
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|bio-&gt;bi_sector
op_assign
id|page_off
op_star
(paren
id|PAGE_SIZE
op_rshift
l_int|9
)paren
suffix:semicolon
id|bio_get
c_func
(paren
id|bio
)paren
suffix:semicolon
id|bio-&gt;bi_bdev
op_assign
id|resume_bdev
suffix:semicolon
id|bio-&gt;bi_end_io
op_assign
id|end_io
suffix:semicolon
r_if
c_cond
(paren
id|bio_add_page
c_func
(paren
id|bio
comma
id|virt_to_page
c_func
(paren
id|page
)paren
comma
id|PAGE_SIZE
comma
l_int|0
)paren
OL
id|PAGE_SIZE
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;pmdisk: ERROR: adding page to bio at %ld&bslash;n&quot;
comma
id|page_off
)paren
suffix:semicolon
id|error
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_goto
id|Done
suffix:semicolon
)brace
r_if
c_cond
(paren
id|rw
op_eq
id|WRITE
)paren
id|bio_set_pages_dirty
c_func
(paren
id|bio
)paren
suffix:semicolon
id|start_io
c_func
(paren
)paren
suffix:semicolon
id|submit_bio
c_func
(paren
id|rw
op_or
(paren
l_int|1
op_lshift
id|BIO_RW_SYNC
)paren
comma
id|bio
)paren
suffix:semicolon
id|wait_io
c_func
(paren
)paren
suffix:semicolon
id|Done
suffix:colon
id|bio_put
c_func
(paren
id|bio
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
r_static
r_int
DECL|function|read_page
id|read_page
c_func
(paren
id|pgoff_t
id|page_off
comma
r_void
op_star
id|page
)paren
(brace
r_return
id|submit
c_func
(paren
id|READ
comma
id|page_off
comma
id|page
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|write_page
id|write_page
c_func
(paren
id|pgoff_t
id|page_off
comma
r_void
op_star
id|page
)paren
(brace
r_return
id|submit
c_func
(paren
id|WRITE
comma
id|page_off
comma
id|page
)paren
suffix:semicolon
)brace
r_extern
id|dev_t
id|__init
id|name_to_dev_t
c_func
(paren
r_const
r_char
op_star
id|line
)paren
suffix:semicolon
DECL|function|check_sig
r_static
r_int
id|__init
id|check_sig
c_func
(paren
r_void
)paren
(brace
r_int
id|error
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|pmdisk_header
comma
l_int|0
comma
r_sizeof
(paren
id|pmdisk_header
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|error
op_assign
id|read_page
c_func
(paren
l_int|0
comma
op_amp
id|pmdisk_header
)paren
)paren
)paren
r_return
id|error
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|memcmp
c_func
(paren
id|PMDISK_SIG
comma
id|pmdisk_header.sig
comma
l_int|10
)paren
)paren
(brace
id|memcpy
c_func
(paren
id|pmdisk_header.sig
comma
id|pmdisk_header.orig_sig
comma
l_int|10
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Reset swap signature now.&n;&t;&t; */
id|error
op_assign
id|write_page
c_func
(paren
l_int|0
comma
op_amp
id|pmdisk_header
)paren
suffix:semicolon
)brace
r_else
(brace
id|pr_debug
c_func
(paren
id|KERN_ERR
l_string|&quot;pmdisk: Invalid partition type.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
id|pr_debug
c_func
(paren
l_string|&quot;pmdisk: Signature found, resuming&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/*&n; * Sanity check if this image makes sense with this kernel/swap context&n; * I really don&squot;t think that it&squot;s foolproof but more than nothing..&n; */
DECL|function|sanity_check
r_static
r_const
r_char
op_star
id|__init
id|sanity_check
c_func
(paren
r_void
)paren
(brace
id|dump_pmdisk_info
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pmdisk_info.version_code
op_ne
id|LINUX_VERSION_CODE
)paren
(brace
r_return
l_string|&quot;kernel version&quot;
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pmdisk_info.num_physpages
op_ne
id|num_physpages
)paren
(brace
r_return
l_string|&quot;memory size&quot;
suffix:semicolon
)brace
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|pmdisk_info.uts.sysname
comma
id|system_utsname.sysname
)paren
)paren
r_return
l_string|&quot;system type&quot;
suffix:semicolon
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|pmdisk_info.uts.release
comma
id|system_utsname.release
)paren
)paren
r_return
l_string|&quot;kernel release&quot;
suffix:semicolon
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|pmdisk_info.uts.version
comma
id|system_utsname.version
)paren
)paren
r_return
l_string|&quot;version&quot;
suffix:semicolon
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|pmdisk_info.uts.machine
comma
id|system_utsname.machine
)paren
)paren
r_return
l_string|&quot;machine&quot;
suffix:semicolon
r_if
c_cond
(paren
id|pmdisk_info.cpus
op_ne
id|num_online_cpus
c_func
(paren
)paren
)paren
(brace
r_return
l_string|&quot;number of cpus&quot;
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|check_header
r_static
r_int
id|__init
id|check_header
c_func
(paren
r_void
)paren
(brace
r_const
r_char
op_star
id|reason
op_assign
l_int|NULL
suffix:semicolon
r_int
id|error
suffix:semicolon
id|init_header
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|error
op_assign
id|read_page
c_func
(paren
id|swp_offset
c_func
(paren
id|pmdisk_header.pmdisk_info
)paren
comma
op_amp
id|pmdisk_info
)paren
)paren
)paren
r_return
id|error
suffix:semicolon
multiline_comment|/* Is this same machine? */
r_if
c_cond
(paren
(paren
id|reason
op_assign
id|sanity_check
c_func
(paren
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;pmdisk: Resume mismatch: %s&bslash;n&quot;
comma
id|reason
)paren
suffix:semicolon
r_return
op_minus
id|EPERM
suffix:semicolon
)brace
id|nr_copy_pages
op_assign
id|pmdisk_info.image_pages
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|function|read_pagedir
r_static
r_int
id|__init
id|read_pagedir
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|addr
suffix:semicolon
r_int
id|i
comma
id|n
op_assign
id|pmdisk_info.pagedir_pages
suffix:semicolon
r_int
id|error
op_assign
l_int|0
suffix:semicolon
id|pagedir_order
op_assign
id|get_bitmask_order
c_func
(paren
id|n
)paren
suffix:semicolon
id|addr
op_assign
id|__get_free_pages
c_func
(paren
id|GFP_ATOMIC
comma
id|pagedir_order
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|addr
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|pagedir_nosave
op_assign
(paren
r_struct
id|pbe
op_star
)paren
id|addr
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;pmdisk: Reading pagedir (%d Pages)&bslash;n&quot;
comma
id|n
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
id|n
op_logical_and
op_logical_neg
id|error
suffix:semicolon
id|i
op_increment
comma
id|addr
op_add_assign
id|PAGE_SIZE
)paren
(brace
r_int
r_int
id|offset
op_assign
id|swp_offset
c_func
(paren
id|pmdisk_info.pagedir
(braket
id|i
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|offset
)paren
id|error
op_assign
id|read_page
c_func
(paren
id|offset
comma
(paren
r_void
op_star
)paren
id|addr
)paren
suffix:semicolon
r_else
id|error
op_assign
op_minus
id|EFAULT
suffix:semicolon
)brace
r_if
c_cond
(paren
id|error
)paren
id|free_pages
c_func
(paren
(paren
r_int
r_int
)paren
id|pagedir_nosave
comma
id|pagedir_order
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;read_image_data - Read image pages from swap.&n; *&n; *&t;You do not need to check for overlaps, check_pagedir()&n; *&t;already did that.&n; */
DECL|function|read_image_data
r_static
r_int
id|__init
id|read_image_data
c_func
(paren
r_void
)paren
(brace
r_struct
id|pbe
op_star
id|p
suffix:semicolon
r_int
id|error
op_assign
l_int|0
suffix:semicolon
r_int
id|i
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Reading image data (%d pages): &quot;
comma
id|nr_copy_pages
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
comma
id|p
op_assign
id|pagedir_nosave
suffix:semicolon
id|i
OL
id|nr_copy_pages
op_logical_and
op_logical_neg
id|error
suffix:semicolon
id|i
op_increment
comma
id|p
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|i
op_mod
l_int|100
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;.&quot;
)paren
suffix:semicolon
id|error
op_assign
id|read_page
c_func
(paren
id|swp_offset
c_func
(paren
id|p-&gt;swap_address
)paren
comma
(paren
r_void
op_star
)paren
id|p-&gt;address
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot; %d done.&bslash;n&quot;
comma
id|i
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|function|read_suspend_image
r_static
r_int
id|__init
id|read_suspend_image
c_func
(paren
r_void
)paren
(brace
r_int
id|error
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|error
op_assign
id|check_sig
c_func
(paren
)paren
)paren
)paren
r_return
id|error
suffix:semicolon
r_if
c_cond
(paren
(paren
id|error
op_assign
id|check_header
c_func
(paren
)paren
)paren
)paren
r_return
id|error
suffix:semicolon
r_if
c_cond
(paren
(paren
id|error
op_assign
id|read_pagedir
c_func
(paren
)paren
)paren
)paren
r_return
id|error
suffix:semicolon
r_if
c_cond
(paren
(paren
id|error
op_assign
id|swsusp_pagedir_relocate
c_func
(paren
)paren
)paren
)paren
r_goto
id|FreePagedir
suffix:semicolon
r_if
c_cond
(paren
(paren
id|error
op_assign
id|read_image_data
c_func
(paren
)paren
)paren
)paren
r_goto
id|FreePagedir
suffix:semicolon
id|Done
suffix:colon
r_return
id|error
suffix:semicolon
id|FreePagedir
suffix:colon
id|free_pages
c_func
(paren
(paren
r_int
r_int
)paren
id|pagedir_nosave
comma
id|pagedir_order
)paren
suffix:semicolon
r_goto
id|Done
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;pmdisk_save - Snapshot memory&n; */
DECL|function|pmdisk_save
r_int
id|pmdisk_save
c_func
(paren
r_void
)paren
(brace
r_int
id|error
suffix:semicolon
macro_line|#if defined (CONFIG_HIGHMEM) || defined (CONFIG_DISCONTIGMEM)
id|pr_debug
c_func
(paren
l_string|&quot;pmdisk: not supported with high- or discontig-mem.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EPERM
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
(paren
id|error
op_assign
id|arch_prepare_suspend
c_func
(paren
)paren
)paren
)paren
r_return
id|error
suffix:semicolon
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
id|save_processor_state
c_func
(paren
)paren
suffix:semicolon
id|error
op_assign
id|pmdisk_arch_suspend
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|restore_processor_state
c_func
(paren
)paren
suffix:semicolon
id|local_irq_enable
c_func
(paren
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;pmdisk_write - Write saved memory image to swap.&n; *&n; *&t;pmdisk_arch_suspend(0) returns after system is resumed.&n; *&n; *&t;pmdisk_arch_suspend() copies all &quot;used&quot; memory to &quot;free&quot; memory,&n; *&t;then unsuspends all device drivers, and writes memory to disk&n; *&t;using normal kernel mechanism.&n; */
DECL|function|pmdisk_write
r_int
id|pmdisk_write
c_func
(paren
r_void
)paren
(brace
r_return
id|suspend_save_image
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;pmdisk_read - Read saved image from swap.&n; */
DECL|function|pmdisk_read
r_int
id|__init
id|pmdisk_read
c_func
(paren
r_void
)paren
(brace
r_int
id|error
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strlen
c_func
(paren
id|resume_file
)paren
)paren
r_return
op_minus
id|ENOENT
suffix:semicolon
id|resume_device
op_assign
id|name_to_dev_t
c_func
(paren
id|resume_file
)paren
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;pmdisk: Resume From Partition: %s&bslash;n&quot;
comma
id|resume_file
)paren
suffix:semicolon
id|resume_bdev
op_assign
id|open_by_devnum
c_func
(paren
id|resume_device
comma
id|FMODE_READ
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|IS_ERR
c_func
(paren
id|resume_bdev
)paren
)paren
(brace
id|set_blocksize
c_func
(paren
id|resume_bdev
comma
id|PAGE_SIZE
)paren
suffix:semicolon
id|error
op_assign
id|read_suspend_image
c_func
(paren
)paren
suffix:semicolon
id|blkdev_put
c_func
(paren
id|resume_bdev
)paren
suffix:semicolon
)brace
r_else
id|error
op_assign
id|PTR_ERR
c_func
(paren
id|resume_bdev
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
id|pr_debug
c_func
(paren
l_string|&quot;Reading resume file was successful&bslash;n&quot;
)paren
suffix:semicolon
r_else
id|pr_debug
c_func
(paren
l_string|&quot;pmdisk: Error %d resuming&bslash;n&quot;
comma
id|error
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;pmdisk_restore - Replace running kernel with saved image.&n; */
DECL|function|pmdisk_restore
r_int
id|__init
id|pmdisk_restore
c_func
(paren
r_void
)paren
(brace
r_int
id|error
suffix:semicolon
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
id|save_processor_state
c_func
(paren
)paren
suffix:semicolon
id|error
op_assign
id|pmdisk_arch_suspend
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|restore_processor_state
c_func
(paren
)paren
suffix:semicolon
id|local_irq_enable
c_func
(paren
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;pmdisk_free - Free memory allocated to hold snapshot.&n; */
DECL|function|pmdisk_free
r_int
id|pmdisk_free
c_func
(paren
r_void
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;Freeing prev allocated pagedir&bslash;n&quot;
)paren
suffix:semicolon
id|free_suspend_pagedir
c_func
(paren
(paren
r_int
r_int
)paren
id|pagedir_save
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pmdisk_setup
r_static
r_int
id|__init
id|pmdisk_setup
c_func
(paren
r_char
op_star
id|str
)paren
(brace
r_if
c_cond
(paren
id|strlen
c_func
(paren
id|str
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|str
comma
l_string|&quot;off&quot;
)paren
)paren
id|resume_file
(braket
l_int|0
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_else
id|strncpy
c_func
(paren
id|resume_file
comma
id|str
comma
l_int|255
)paren
suffix:semicolon
)brace
r_else
id|resume_file
(braket
l_int|0
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;pmdisk=&quot;
comma
id|pmdisk_setup
)paren
suffix:semicolon
eof
