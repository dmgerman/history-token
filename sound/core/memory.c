multiline_comment|/*&n; *  Copyright (c) by Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *  Memory allocation routines.&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &lt;sound/info.h&gt;
macro_line|#ifdef CONFIG_SBUS
macro_line|#include &lt;asm/sbus.h&gt;
macro_line|#endif
multiline_comment|/*&n; *  memory allocation helpers and debug routines&n; */
macro_line|#ifdef CONFIG_SND_DEBUG_MEMORY
DECL|struct|snd_alloc_track
r_struct
id|snd_alloc_track
(brace
DECL|member|magic
r_int
r_int
id|magic
suffix:semicolon
DECL|member|caller
r_void
op_star
id|caller
suffix:semicolon
DECL|member|size
r_int
id|size
suffix:semicolon
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|data
r_int
id|data
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|snd_alloc_track_entry
mdefine_line|#define snd_alloc_track_entry(obj) (struct snd_alloc_track *)((char*)obj - (unsigned long)((struct snd_alloc_track *)0)-&gt;data)
DECL|variable|snd_alloc_pages
r_static
r_int
id|snd_alloc_pages
suffix:semicolon
DECL|variable|snd_alloc_kmalloc
r_static
r_int
id|snd_alloc_kmalloc
suffix:semicolon
DECL|variable|snd_alloc_vmalloc
r_static
r_int
id|snd_alloc_vmalloc
suffix:semicolon
r_static
id|LIST_HEAD
c_func
(paren
id|snd_alloc_kmalloc_list
)paren
suffix:semicolon
r_static
id|LIST_HEAD
c_func
(paren
id|snd_alloc_vmalloc_list
)paren
suffix:semicolon
DECL|variable|snd_alloc_kmalloc_lock
r_static
id|spinlock_t
id|snd_alloc_kmalloc_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|variable|snd_alloc_vmalloc_lock
r_static
id|spinlock_t
id|snd_alloc_vmalloc_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|macro|KMALLOC_MAGIC
mdefine_line|#define KMALLOC_MAGIC 0x87654321
DECL|macro|VMALLOC_MAGIC
mdefine_line|#define VMALLOC_MAGIC 0x87654320
DECL|variable|snd_memory_info_entry
r_static
id|snd_info_entry_t
op_star
id|snd_memory_info_entry
suffix:semicolon
DECL|function|snd_memory_init
r_void
id|snd_memory_init
c_func
(paren
r_void
)paren
(brace
id|snd_alloc_pages
op_assign
l_int|0
suffix:semicolon
id|snd_alloc_kmalloc
op_assign
l_int|0
suffix:semicolon
id|snd_alloc_vmalloc
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|snd_memory_done
r_void
id|snd_memory_done
c_func
(paren
r_void
)paren
(brace
r_struct
id|list_head
op_star
id|head
suffix:semicolon
r_struct
id|snd_alloc_track
op_star
id|t
suffix:semicolon
r_if
c_cond
(paren
id|snd_alloc_pages
OG
l_int|0
)paren
id|snd_printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Not freed snd_alloc_pages = %li&bslash;n&quot;
comma
id|snd_alloc_pages
)paren
suffix:semicolon
r_if
c_cond
(paren
id|snd_alloc_kmalloc
OG
l_int|0
)paren
id|snd_printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Not freed snd_alloc_kmalloc = %li&bslash;n&quot;
comma
id|snd_alloc_kmalloc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|snd_alloc_vmalloc
OG
l_int|0
)paren
id|snd_printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Not freed snd_alloc_vmalloc = %li&bslash;n&quot;
comma
id|snd_alloc_vmalloc
)paren
suffix:semicolon
r_for
c_loop
(paren
id|head
op_assign
id|snd_alloc_kmalloc_list.prev
suffix:semicolon
id|head
op_ne
op_amp
id|snd_alloc_kmalloc_list
suffix:semicolon
id|head
op_assign
id|head-&gt;prev
)paren
(brace
id|t
op_assign
id|list_entry
c_func
(paren
id|head
comma
r_struct
id|snd_alloc_track
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|t-&gt;magic
op_ne
id|KMALLOC_MAGIC
)paren
(brace
id|snd_printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Corrupted kmalloc&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|snd_printk
c_func
(paren
id|KERN_ERR
l_string|&quot;kmalloc(%ld) from %p not freed&bslash;n&quot;
comma
(paren
r_int
)paren
id|t-&gt;size
comma
id|t-&gt;caller
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|head
op_assign
id|snd_alloc_vmalloc_list.prev
suffix:semicolon
id|head
op_ne
op_amp
id|snd_alloc_vmalloc_list
suffix:semicolon
id|head
op_assign
id|head-&gt;prev
)paren
(brace
id|t
op_assign
id|list_entry
c_func
(paren
id|head
comma
r_struct
id|snd_alloc_track
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|t-&gt;magic
op_ne
id|VMALLOC_MAGIC
)paren
(brace
id|snd_printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Corrupted vmalloc&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|snd_printk
c_func
(paren
id|KERN_ERR
l_string|&quot;vmalloc(%ld) from %p not freed&bslash;n&quot;
comma
(paren
r_int
)paren
id|t-&gt;size
comma
id|t-&gt;caller
)paren
suffix:semicolon
)brace
)brace
DECL|function|__snd_kmalloc
r_void
op_star
id|__snd_kmalloc
c_func
(paren
r_int
id|size
comma
r_int
id|flags
comma
r_void
op_star
id|caller
)paren
(brace
r_int
r_int
id|cpu_flags
suffix:semicolon
r_struct
id|snd_alloc_track
op_star
id|t
suffix:semicolon
r_void
op_star
id|ptr
suffix:semicolon
id|ptr
op_assign
id|snd_wrapper_kmalloc
c_func
(paren
id|size
op_plus
r_sizeof
(paren
r_struct
id|snd_alloc_track
)paren
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ptr
op_ne
l_int|NULL
)paren
(brace
id|t
op_assign
(paren
r_struct
id|snd_alloc_track
op_star
)paren
id|ptr
suffix:semicolon
id|t-&gt;magic
op_assign
id|KMALLOC_MAGIC
suffix:semicolon
id|t-&gt;caller
op_assign
id|caller
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|snd_alloc_kmalloc_lock
comma
id|cpu_flags
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|t-&gt;list
comma
op_amp
id|snd_alloc_kmalloc_list
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|snd_alloc_kmalloc_lock
comma
id|cpu_flags
)paren
suffix:semicolon
id|t-&gt;size
op_assign
id|size
suffix:semicolon
id|snd_alloc_kmalloc
op_add_assign
id|size
suffix:semicolon
id|ptr
op_assign
id|t-&gt;data
suffix:semicolon
)brace
r_return
id|ptr
suffix:semicolon
)brace
DECL|macro|_snd_kmalloc
mdefine_line|#define _snd_kmalloc(size, flags) __snd_kmalloc((size), (flags), __builtin_return_address(0));
DECL|function|snd_hidden_kmalloc
r_void
op_star
id|snd_hidden_kmalloc
c_func
(paren
r_int
id|size
comma
r_int
id|flags
)paren
(brace
r_return
id|_snd_kmalloc
c_func
(paren
id|size
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|snd_hidden_kfree
r_void
id|snd_hidden_kfree
c_func
(paren
r_const
r_void
op_star
id|obj
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_struct
id|snd_alloc_track
op_star
id|t
suffix:semicolon
r_if
c_cond
(paren
id|obj
op_eq
l_int|NULL
)paren
(brace
id|snd_printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;null kfree (called from %p)&bslash;n&quot;
comma
id|__builtin_return_address
c_func
(paren
l_int|0
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|t
op_assign
id|snd_alloc_track_entry
c_func
(paren
id|obj
)paren
suffix:semicolon
r_if
c_cond
(paren
id|t-&gt;magic
op_ne
id|KMALLOC_MAGIC
)paren
(brace
id|snd_printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;bad kfree (called from %p)&bslash;n&quot;
comma
id|__builtin_return_address
c_func
(paren
l_int|0
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|snd_alloc_kmalloc_lock
comma
id|flags
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|t-&gt;list
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|snd_alloc_kmalloc_lock
comma
id|flags
)paren
suffix:semicolon
id|t-&gt;magic
op_assign
l_int|0
suffix:semicolon
id|snd_alloc_kmalloc
op_sub_assign
id|t-&gt;size
suffix:semicolon
id|obj
op_assign
id|t
suffix:semicolon
id|snd_wrapper_kfree
c_func
(paren
id|obj
)paren
suffix:semicolon
)brace
DECL|function|_snd_magic_kcalloc
r_void
op_star
id|_snd_magic_kcalloc
c_func
(paren
r_int
r_int
id|magic
comma
r_int
id|size
comma
r_int
id|flags
)paren
(brace
r_int
r_int
op_star
id|ptr
suffix:semicolon
id|ptr
op_assign
id|_snd_kmalloc
c_func
(paren
id|size
op_plus
r_sizeof
(paren
r_int
r_int
)paren
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ptr
)paren
(brace
op_star
id|ptr
op_increment
op_assign
id|magic
suffix:semicolon
id|memset
c_func
(paren
id|ptr
comma
l_int|0
comma
id|size
)paren
suffix:semicolon
)brace
r_return
id|ptr
suffix:semicolon
)brace
DECL|function|_snd_magic_kmalloc
r_void
op_star
id|_snd_magic_kmalloc
c_func
(paren
r_int
r_int
id|magic
comma
r_int
id|size
comma
r_int
id|flags
)paren
(brace
r_int
r_int
op_star
id|ptr
suffix:semicolon
id|ptr
op_assign
id|_snd_kmalloc
c_func
(paren
id|size
op_plus
r_sizeof
(paren
r_int
r_int
)paren
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ptr
)paren
op_star
id|ptr
op_increment
op_assign
id|magic
suffix:semicolon
r_return
id|ptr
suffix:semicolon
)brace
DECL|function|snd_magic_kfree
r_void
id|snd_magic_kfree
c_func
(paren
r_void
op_star
id|_ptr
)paren
(brace
r_int
r_int
op_star
id|ptr
op_assign
id|_ptr
suffix:semicolon
r_if
c_cond
(paren
id|ptr
op_eq
l_int|NULL
)paren
(brace
id|snd_printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;null snd_magic_kfree (called from %p)&bslash;n&quot;
comma
id|__builtin_return_address
c_func
(paren
l_int|0
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
op_star
op_decrement
id|ptr
op_assign
l_int|0
suffix:semicolon
(brace
r_struct
id|snd_alloc_track
op_star
id|t
suffix:semicolon
id|t
op_assign
id|snd_alloc_track_entry
c_func
(paren
id|ptr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|t-&gt;magic
op_ne
id|KMALLOC_MAGIC
)paren
(brace
id|snd_printk
c_func
(paren
id|KERN_ERR
l_string|&quot;bad snd_magic_kfree (called from %p)&bslash;n&quot;
comma
id|__builtin_return_address
c_func
(paren
l_int|0
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
id|snd_hidden_kfree
c_func
(paren
id|ptr
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|snd_hidden_vmalloc
r_void
op_star
id|snd_hidden_vmalloc
c_func
(paren
r_int
r_int
id|size
)paren
(brace
r_void
op_star
id|ptr
suffix:semicolon
id|ptr
op_assign
id|snd_wrapper_vmalloc
c_func
(paren
id|size
op_plus
r_sizeof
(paren
r_struct
id|snd_alloc_track
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ptr
)paren
(brace
r_struct
id|snd_alloc_track
op_star
id|t
op_assign
(paren
r_struct
id|snd_alloc_track
op_star
)paren
id|ptr
suffix:semicolon
id|t-&gt;magic
op_assign
id|VMALLOC_MAGIC
suffix:semicolon
id|t-&gt;caller
op_assign
id|__builtin_return_address
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|snd_alloc_vmalloc_lock
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|t-&gt;list
comma
op_amp
id|snd_alloc_vmalloc_list
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|snd_alloc_vmalloc_lock
)paren
suffix:semicolon
id|t-&gt;size
op_assign
id|size
suffix:semicolon
id|snd_alloc_vmalloc
op_add_assign
id|size
suffix:semicolon
id|ptr
op_assign
id|t-&gt;data
suffix:semicolon
)brace
r_return
id|ptr
suffix:semicolon
)brace
DECL|function|snd_hidden_vfree
r_void
id|snd_hidden_vfree
c_func
(paren
r_void
op_star
id|obj
)paren
(brace
r_struct
id|snd_alloc_track
op_star
id|t
suffix:semicolon
r_if
c_cond
(paren
id|obj
op_eq
l_int|NULL
)paren
(brace
id|snd_printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;null vfree (called from %p)&bslash;n&quot;
comma
id|__builtin_return_address
c_func
(paren
l_int|0
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|t
op_assign
id|snd_alloc_track_entry
c_func
(paren
id|obj
)paren
suffix:semicolon
r_if
c_cond
(paren
id|t-&gt;magic
op_ne
id|VMALLOC_MAGIC
)paren
(brace
id|snd_printk
c_func
(paren
id|KERN_ERR
l_string|&quot;bad vfree (called from %p)&bslash;n&quot;
comma
id|__builtin_return_address
c_func
(paren
l_int|0
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|spin_lock
c_func
(paren
op_amp
id|snd_alloc_vmalloc_lock
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|t-&gt;list
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|snd_alloc_vmalloc_lock
)paren
suffix:semicolon
id|t-&gt;magic
op_assign
l_int|0
suffix:semicolon
id|snd_alloc_vmalloc
op_sub_assign
id|t-&gt;size
suffix:semicolon
id|obj
op_assign
id|t
suffix:semicolon
id|snd_wrapper_vfree
c_func
(paren
id|obj
)paren
suffix:semicolon
)brace
DECL|function|snd_memory_info_read
r_static
r_void
id|snd_memory_info_read
c_func
(paren
id|snd_info_entry_t
op_star
id|entry
comma
id|snd_info_buffer_t
op_star
id|buffer
)paren
(brace
r_int
id|pages
op_assign
id|snd_alloc_pages
op_rshift
(paren
id|PAGE_SHIFT
op_minus
l_int|12
)paren
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buffer
comma
l_string|&quot;pages  : %li bytes (%li pages per %likB)&bslash;n&quot;
comma
id|pages
op_star
id|PAGE_SIZE
comma
id|pages
comma
id|PAGE_SIZE
op_div
l_int|1024
)paren
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buffer
comma
l_string|&quot;kmalloc: %li bytes&bslash;n&quot;
comma
id|snd_alloc_kmalloc
)paren
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buffer
comma
l_string|&quot;vmalloc: %li bytes&bslash;n&quot;
comma
id|snd_alloc_vmalloc
)paren
suffix:semicolon
)brace
DECL|function|snd_memory_info_init
r_int
id|__init
id|snd_memory_info_init
c_func
(paren
r_void
)paren
(brace
id|snd_info_entry_t
op_star
id|entry
suffix:semicolon
id|entry
op_assign
id|snd_info_create_module_entry
c_func
(paren
id|THIS_MODULE
comma
l_string|&quot;meminfo&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|entry
)paren
(brace
id|entry-&gt;content
op_assign
id|SNDRV_INFO_CONTENT_TEXT
suffix:semicolon
id|entry-&gt;c.text.read_size
op_assign
l_int|256
suffix:semicolon
id|entry-&gt;c.text.read
op_assign
id|snd_memory_info_read
suffix:semicolon
r_if
c_cond
(paren
id|snd_info_register
c_func
(paren
id|entry
)paren
OL
l_int|0
)paren
(brace
id|snd_info_free_entry
c_func
(paren
id|entry
)paren
suffix:semicolon
id|entry
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
id|snd_memory_info_entry
op_assign
id|entry
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_memory_info_done
r_int
id|__exit
id|snd_memory_info_done
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|snd_memory_info_entry
)paren
id|snd_info_unregister
c_func
(paren
id|snd_memory_info_entry
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#else
DECL|macro|_snd_kmalloc
mdefine_line|#define _snd_kmalloc kmalloc
macro_line|#endif /* CONFIG_SND_DEBUG_MEMORY */
DECL|function|snd_malloc_pages
r_void
op_star
id|snd_malloc_pages
c_func
(paren
r_int
r_int
id|size
comma
r_int
r_int
id|dma_flags
)paren
(brace
r_int
id|pg
suffix:semicolon
r_void
op_star
id|res
suffix:semicolon
id|snd_assert
c_func
(paren
id|size
OG
l_int|0
comma
r_return
l_int|NULL
)paren
suffix:semicolon
id|snd_assert
c_func
(paren
id|dma_flags
op_ne
l_int|0
comma
r_return
l_int|NULL
)paren
suffix:semicolon
r_for
c_loop
(paren
id|pg
op_assign
l_int|0
suffix:semicolon
id|PAGE_SIZE
op_star
(paren
l_int|1
op_lshift
id|pg
)paren
OL
id|size
suffix:semicolon
id|pg
op_increment
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|res
op_assign
(paren
r_void
op_star
)paren
id|__get_free_pages
c_func
(paren
id|dma_flags
comma
id|pg
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
r_struct
id|page
op_star
id|page
op_assign
id|virt_to_page
c_func
(paren
id|res
)paren
suffix:semicolon
r_struct
id|page
op_star
id|last_page
op_assign
id|page
op_plus
(paren
l_int|1
op_lshift
id|pg
)paren
suffix:semicolon
r_while
c_loop
(paren
id|page
OL
id|last_page
)paren
id|SetPageReserved
c_func
(paren
id|page
op_increment
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SND_DEBUG_MEMORY
id|snd_alloc_pages
op_add_assign
l_int|1
op_lshift
id|pg
suffix:semicolon
macro_line|#endif
)brace
r_return
id|res
suffix:semicolon
)brace
DECL|function|snd_malloc_pages_fallback
r_void
op_star
id|snd_malloc_pages_fallback
c_func
(paren
r_int
r_int
id|size
comma
r_int
r_int
id|dma_flags
comma
r_int
r_int
op_star
id|res_size
)paren
(brace
r_void
op_star
id|res
suffix:semicolon
id|snd_assert
c_func
(paren
id|size
OG
l_int|0
comma
r_return
l_int|NULL
)paren
suffix:semicolon
id|snd_assert
c_func
(paren
id|res_size
op_ne
l_int|NULL
comma
r_return
l_int|NULL
)paren
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
(paren
id|res
op_assign
id|snd_malloc_pages
c_func
(paren
id|size
comma
id|dma_flags
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
op_star
id|res_size
op_assign
id|size
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
id|size
op_rshift_assign
l_int|1
suffix:semicolon
)brace
r_while
c_loop
(paren
id|size
op_ge
id|PAGE_SIZE
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|snd_free_pages
r_void
id|snd_free_pages
c_func
(paren
r_void
op_star
id|ptr
comma
r_int
r_int
id|size
)paren
(brace
r_int
id|pg
suffix:semicolon
r_struct
id|page
op_star
id|page
comma
op_star
id|last_page
suffix:semicolon
r_if
c_cond
(paren
id|ptr
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
r_for
c_loop
(paren
id|pg
op_assign
l_int|0
suffix:semicolon
id|PAGE_SIZE
op_star
(paren
l_int|1
op_lshift
id|pg
)paren
OL
id|size
suffix:semicolon
id|pg
op_increment
)paren
suffix:semicolon
id|page
op_assign
id|virt_to_page
c_func
(paren
id|ptr
)paren
suffix:semicolon
id|last_page
op_assign
id|page
op_plus
(paren
l_int|1
op_lshift
id|pg
)paren
suffix:semicolon
r_while
c_loop
(paren
id|page
OL
id|last_page
)paren
id|ClearPageReserved
c_func
(paren
id|page
op_increment
)paren
suffix:semicolon
id|free_pages
c_func
(paren
(paren
r_int
r_int
)paren
id|ptr
comma
id|pg
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SND_DEBUG_MEMORY
id|snd_alloc_pages
op_sub_assign
l_int|1
op_lshift
id|pg
suffix:semicolon
macro_line|#endif
)brace
macro_line|#if defined(CONFIG_ISA) &amp;&amp; ! defined(CONFIG_PCI)
DECL|function|snd_malloc_isa_pages
r_void
op_star
id|snd_malloc_isa_pages
c_func
(paren
r_int
r_int
id|size
comma
id|dma_addr_t
op_star
id|dma_addr
)paren
(brace
r_void
op_star
id|dma_area
suffix:semicolon
id|dma_area
op_assign
id|snd_malloc_pages
c_func
(paren
id|size
comma
id|GFP_ATOMIC
op_or
id|GFP_DMA
)paren
suffix:semicolon
op_star
id|dma_addr
op_assign
id|dma_area
ques
c_cond
id|isa_virt_to_bus
c_func
(paren
id|dma_area
)paren
suffix:colon
l_int|0UL
suffix:semicolon
r_return
id|dma_area
suffix:semicolon
)brace
DECL|function|snd_malloc_isa_pages_fallback
r_void
op_star
id|snd_malloc_isa_pages_fallback
c_func
(paren
r_int
r_int
id|size
comma
id|dma_addr_t
op_star
id|dma_addr
comma
r_int
r_int
op_star
id|res_size
)paren
(brace
r_void
op_star
id|dma_area
suffix:semicolon
id|dma_area
op_assign
id|snd_malloc_pages_fallback
c_func
(paren
id|size
comma
id|GFP_ATOMIC
op_or
id|GFP_DMA
comma
id|res_size
)paren
suffix:semicolon
op_star
id|dma_addr
op_assign
id|dma_area
ques
c_cond
id|isa_virt_to_bus
c_func
(paren
id|dma_area
)paren
suffix:colon
l_int|0UL
suffix:semicolon
r_return
id|dma_area
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_ISA &amp;&amp; !CONFIG_PCI */
macro_line|#ifdef CONFIG_PCI
DECL|function|snd_malloc_pci_pages
r_void
op_star
id|snd_malloc_pci_pages
c_func
(paren
r_struct
id|pci_dev
op_star
id|pci
comma
r_int
r_int
id|size
comma
id|dma_addr_t
op_star
id|dma_addr
)paren
(brace
r_int
id|pg
suffix:semicolon
r_void
op_star
id|res
suffix:semicolon
id|snd_assert
c_func
(paren
id|size
OG
l_int|0
comma
r_return
l_int|NULL
)paren
suffix:semicolon
id|snd_assert
c_func
(paren
id|dma_addr
op_ne
l_int|NULL
comma
r_return
l_int|NULL
)paren
suffix:semicolon
r_for
c_loop
(paren
id|pg
op_assign
l_int|0
suffix:semicolon
id|PAGE_SIZE
op_star
(paren
l_int|1
op_lshift
id|pg
)paren
OL
id|size
suffix:semicolon
id|pg
op_increment
)paren
suffix:semicolon
id|res
op_assign
id|pci_alloc_consistent
c_func
(paren
id|pci
comma
id|PAGE_SIZE
op_star
(paren
l_int|1
op_lshift
id|pg
)paren
comma
id|dma_addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
op_ne
l_int|NULL
)paren
(brace
r_struct
id|page
op_star
id|page
op_assign
id|virt_to_page
c_func
(paren
id|res
)paren
suffix:semicolon
r_struct
id|page
op_star
id|last_page
op_assign
id|page
op_plus
(paren
l_int|1
op_lshift
id|pg
)paren
suffix:semicolon
r_while
c_loop
(paren
id|page
OL
id|last_page
)paren
id|SetPageReserved
c_func
(paren
id|page
op_increment
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SND_DEBUG_MEMORY
id|snd_alloc_pages
op_add_assign
l_int|1
op_lshift
id|pg
suffix:semicolon
macro_line|#endif
)brace
r_return
id|res
suffix:semicolon
)brace
DECL|function|snd_malloc_pci_pages_fallback
r_void
op_star
id|snd_malloc_pci_pages_fallback
c_func
(paren
r_struct
id|pci_dev
op_star
id|pci
comma
r_int
r_int
id|size
comma
id|dma_addr_t
op_star
id|dma_addr
comma
r_int
r_int
op_star
id|res_size
)paren
(brace
r_void
op_star
id|res
suffix:semicolon
id|snd_assert
c_func
(paren
id|res_size
op_ne
l_int|NULL
comma
r_return
l_int|NULL
)paren
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
(paren
id|res
op_assign
id|snd_malloc_pci_pages
c_func
(paren
id|pci
comma
id|size
comma
id|dma_addr
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
op_star
id|res_size
op_assign
id|size
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
id|size
op_rshift_assign
l_int|1
suffix:semicolon
)brace
r_while
c_loop
(paren
id|size
op_ge
id|PAGE_SIZE
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|snd_free_pci_pages
r_void
id|snd_free_pci_pages
c_func
(paren
r_struct
id|pci_dev
op_star
id|pci
comma
r_int
r_int
id|size
comma
r_void
op_star
id|ptr
comma
id|dma_addr_t
id|dma_addr
)paren
(brace
r_int
id|pg
suffix:semicolon
r_struct
id|page
op_star
id|page
comma
op_star
id|last_page
suffix:semicolon
r_if
c_cond
(paren
id|ptr
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
r_for
c_loop
(paren
id|pg
op_assign
l_int|0
suffix:semicolon
id|PAGE_SIZE
op_star
(paren
l_int|1
op_lshift
id|pg
)paren
OL
id|size
suffix:semicolon
id|pg
op_increment
)paren
suffix:semicolon
id|page
op_assign
id|virt_to_page
c_func
(paren
id|ptr
)paren
suffix:semicolon
id|last_page
op_assign
id|page
op_plus
(paren
l_int|1
op_lshift
id|pg
)paren
suffix:semicolon
r_while
c_loop
(paren
id|page
OL
id|last_page
)paren
id|ClearPageReserved
c_func
(paren
id|page
op_increment
)paren
suffix:semicolon
id|pci_free_consistent
c_func
(paren
id|pci
comma
id|PAGE_SIZE
op_star
(paren
l_int|1
op_lshift
id|pg
)paren
comma
id|ptr
comma
id|dma_addr
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SND_DEBUG_MEMORY
id|snd_alloc_pages
op_sub_assign
l_int|1
op_lshift
id|pg
suffix:semicolon
macro_line|#endif
)brace
macro_line|#endif /* CONFIG_PCI */
macro_line|#ifdef CONFIG_SBUS
DECL|function|snd_malloc_sbus_pages
r_void
op_star
id|snd_malloc_sbus_pages
c_func
(paren
r_struct
id|sbus_dev
op_star
id|sdev
comma
r_int
r_int
id|size
comma
id|dma_addr_t
op_star
id|dma_addr
)paren
(brace
r_int
id|pg
suffix:semicolon
r_void
op_star
id|res
suffix:semicolon
id|snd_assert
c_func
(paren
id|size
OG
l_int|0
comma
r_return
l_int|NULL
)paren
suffix:semicolon
id|snd_assert
c_func
(paren
id|dma_addr
op_ne
l_int|NULL
comma
r_return
l_int|NULL
)paren
suffix:semicolon
r_for
c_loop
(paren
id|pg
op_assign
l_int|0
suffix:semicolon
id|PAGE_SIZE
op_star
(paren
l_int|1
op_lshift
id|pg
)paren
OL
id|size
suffix:semicolon
id|pg
op_increment
)paren
suffix:semicolon
id|res
op_assign
id|sbus_alloc_consistent
c_func
(paren
id|sdev
comma
id|PAGE_SIZE
op_star
(paren
l_int|1
op_lshift
id|pg
)paren
comma
id|dma_addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
op_ne
l_int|NULL
)paren
(brace
r_struct
id|page
op_star
id|page
op_assign
id|virt_to_page
c_func
(paren
id|res
)paren
suffix:semicolon
r_struct
id|page
op_star
id|last_page
op_assign
id|page
op_plus
(paren
l_int|1
op_lshift
id|pg
)paren
suffix:semicolon
r_while
c_loop
(paren
id|page
OL
id|last_page
)paren
id|SetPageReserved
c_func
(paren
id|page
op_increment
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SND_DEBUG_MEMORY
id|snd_alloc_pages
op_add_assign
l_int|1
op_lshift
id|pg
suffix:semicolon
macro_line|#endif
)brace
r_return
id|res
suffix:semicolon
)brace
DECL|function|snd_malloc_sbus_pages_fallback
r_void
op_star
id|snd_malloc_sbus_pages_fallback
c_func
(paren
r_struct
id|sbus_dev
op_star
id|sdev
comma
r_int
r_int
id|size
comma
id|dma_addr_t
op_star
id|dma_addr
comma
r_int
r_int
op_star
id|res_size
)paren
(brace
r_void
op_star
id|res
suffix:semicolon
id|snd_assert
c_func
(paren
id|res_size
op_ne
l_int|NULL
comma
r_return
l_int|NULL
)paren
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
(paren
id|res
op_assign
id|snd_malloc_sbus_pages
c_func
(paren
id|sdev
comma
id|size
comma
id|dma_addr
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
op_star
id|res_size
op_assign
id|size
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
id|size
op_rshift_assign
l_int|1
suffix:semicolon
)brace
r_while
c_loop
(paren
id|size
op_ge
id|PAGE_SIZE
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|snd_free_sbus_pages
r_void
id|snd_free_sbus_pages
c_func
(paren
r_struct
id|sbus_dev
op_star
id|sdev
comma
r_int
r_int
id|size
comma
r_void
op_star
id|ptr
comma
id|dma_addr_t
id|dma_addr
)paren
(brace
r_int
id|pg
suffix:semicolon
r_struct
id|page
op_star
id|page
comma
op_star
id|last_page
suffix:semicolon
r_if
c_cond
(paren
id|ptr
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
r_for
c_loop
(paren
id|pg
op_assign
l_int|0
suffix:semicolon
id|PAGE_SIZE
op_star
(paren
l_int|1
op_lshift
id|pg
)paren
OL
id|size
suffix:semicolon
id|pg
op_increment
)paren
suffix:semicolon
id|page
op_assign
id|virt_to_page
c_func
(paren
id|ptr
)paren
suffix:semicolon
id|last_page
op_assign
id|page
op_plus
(paren
l_int|1
op_lshift
id|pg
)paren
suffix:semicolon
r_while
c_loop
(paren
id|page
OL
id|last_page
)paren
id|ClearPageReserved
c_func
(paren
id|page
op_increment
)paren
suffix:semicolon
id|sbus_free_consistent
c_func
(paren
id|sdev
comma
id|PAGE_SIZE
op_star
(paren
l_int|1
op_lshift
id|pg
)paren
comma
id|ptr
comma
id|dma_addr
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SND_DEBUG_MEMORY
id|snd_alloc_pages
op_sub_assign
l_int|1
op_lshift
id|pg
suffix:semicolon
macro_line|#endif
)brace
macro_line|#endif /* CONFIG_SBUS */
DECL|function|snd_kcalloc
r_void
op_star
id|snd_kcalloc
c_func
(paren
r_int
id|size
comma
r_int
id|flags
)paren
(brace
r_void
op_star
id|ptr
suffix:semicolon
id|ptr
op_assign
id|_snd_kmalloc
c_func
(paren
id|size
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ptr
)paren
id|memset
c_func
(paren
id|ptr
comma
l_int|0
comma
id|size
)paren
suffix:semicolon
r_return
id|ptr
suffix:semicolon
)brace
DECL|function|snd_kmalloc_strdup
r_char
op_star
id|snd_kmalloc_strdup
c_func
(paren
r_const
r_char
op_star
id|string
comma
r_int
id|flags
)paren
(brace
r_int
id|len
suffix:semicolon
r_char
op_star
id|ptr
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|string
)paren
r_return
l_int|NULL
suffix:semicolon
id|len
op_assign
id|strlen
c_func
(paren
id|string
)paren
op_plus
l_int|1
suffix:semicolon
id|ptr
op_assign
id|_snd_kmalloc
c_func
(paren
id|len
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ptr
)paren
id|memcpy
c_func
(paren
id|ptr
comma
id|string
comma
id|len
)paren
suffix:semicolon
r_return
id|ptr
suffix:semicolon
)brace
DECL|function|copy_to_user_fromio
r_int
id|copy_to_user_fromio
c_func
(paren
r_void
op_star
id|dst
comma
r_int
r_int
id|src
comma
r_int
id|count
)paren
(brace
macro_line|#if defined(__i386_) || defined(CONFIG_SPARC32)
r_return
id|copy_to_user
c_func
(paren
id|dst
comma
(paren
r_const
r_void
op_star
)paren
id|src
comma
id|count
)paren
ques
c_cond
op_minus
id|EFAULT
suffix:colon
l_int|0
suffix:semicolon
macro_line|#else
r_char
id|buf
(braket
l_int|1024
)braket
suffix:semicolon
r_while
c_loop
(paren
id|count
)paren
(brace
r_int
id|c
op_assign
id|count
suffix:semicolon
r_if
c_cond
(paren
id|c
OG
r_sizeof
(paren
id|buf
)paren
)paren
id|c
op_assign
r_sizeof
(paren
id|buf
)paren
suffix:semicolon
id|memcpy_fromio
c_func
(paren
id|buf
comma
(paren
r_void
op_star
)paren
id|src
comma
id|c
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|dst
comma
id|buf
comma
id|c
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|count
op_sub_assign
id|c
suffix:semicolon
id|dst
op_add_assign
id|c
suffix:semicolon
id|src
op_add_assign
id|c
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
macro_line|#endif
)brace
DECL|function|copy_from_user_toio
r_int
id|copy_from_user_toio
c_func
(paren
r_int
r_int
id|dst
comma
r_const
r_void
op_star
id|src
comma
r_int
id|count
)paren
(brace
macro_line|#if defined(__i386_) || defined(CONFIG_SPARC32)
r_return
id|copy_from_user
c_func
(paren
(paren
r_void
op_star
)paren
id|dst
comma
id|src
comma
id|count
)paren
ques
c_cond
op_minus
id|EFAULT
suffix:colon
l_int|0
suffix:semicolon
macro_line|#else
r_char
id|buf
(braket
l_int|1024
)braket
suffix:semicolon
r_while
c_loop
(paren
id|count
)paren
(brace
r_int
id|c
op_assign
id|count
suffix:semicolon
r_if
c_cond
(paren
id|c
OG
r_sizeof
(paren
id|buf
)paren
)paren
id|c
op_assign
r_sizeof
(paren
id|buf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|buf
comma
id|src
comma
id|c
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|memcpy_toio
c_func
(paren
(paren
r_void
op_star
)paren
id|dst
comma
id|buf
comma
id|c
)paren
suffix:semicolon
id|count
op_sub_assign
id|c
suffix:semicolon
id|dst
op_add_assign
id|c
suffix:semicolon
id|src
op_add_assign
id|c
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
macro_line|#endif
)brace
eof
