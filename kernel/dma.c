multiline_comment|/* $Id: dma.c,v 1.7 1994/12/28 03:35:33 root Exp root $&n; * linux/kernel/dma.c: A DMA channel allocator. Inspired by linux/kernel/irq.c.&n; *&n; * Written by Hennus Bergman, 1992.&n; *&n; * 1994/12/26: Changes by Alex Nash to fix a minor bug in /proc/dma.&n; *   In the previous version the reported device could end up being wrong,&n; *   if a device requested a DMA channel that was already in use.&n; *   [It also happened to remove the sizeof(char *) == sizeof(int)&n; *   assumption introduced because of those /proc/dma patches. -- Hennus]&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/system.h&gt;
multiline_comment|/* A note on resource allocation:&n; *&n; * All drivers needing DMA channels, should allocate and release them&n; * through the public routines `request_dma()&squot; and `free_dma()&squot;.&n; *&n; * In order to avoid problems, all processes should allocate resources in&n; * the same sequence and release them in the reverse order.&n; *&n; * So, when allocating DMAs and IRQs, first allocate the IRQ, then the DMA.&n; * When releasing them, first release the DMA, then release the IRQ.&n; * If you don&squot;t, you may cause allocation requests to fail unnecessarily.&n; * This doesn&squot;t really matter now, but it will once we get real semaphores&n; * in the kernel.&n; */
DECL|variable|dma_spin_lock
id|spinlock_t
id|dma_spin_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
multiline_comment|/*&n; *&t;If our port doesn&squot;t define this it has no PC like DMA&n; */
macro_line|#ifdef MAX_DMA_CHANNELS
multiline_comment|/* Channel n is busy iff dma_chan_busy[n].lock != 0.&n; * DMA0 used to be reserved for DRAM refresh, but apparently not any more...&n; * DMA4 is reserved for cascading.&n; */
DECL|struct|dma_chan
r_struct
id|dma_chan
(brace
DECL|member|lock
r_int
id|lock
suffix:semicolon
DECL|member|device_id
r_const
r_char
op_star
id|device_id
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|dma_chan_busy
r_static
r_struct
id|dma_chan
id|dma_chan_busy
(braket
id|MAX_DMA_CHANNELS
)braket
op_assign
(brace
(brace
l_int|0
comma
l_int|0
)brace
comma
(brace
l_int|0
comma
l_int|0
)brace
comma
(brace
l_int|0
comma
l_int|0
)brace
comma
(brace
l_int|0
comma
l_int|0
)brace
comma
(brace
l_int|1
comma
l_string|&quot;cascade&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0
)brace
comma
(brace
l_int|0
comma
l_int|0
)brace
comma
(brace
l_int|0
comma
l_int|0
)brace
)brace
suffix:semicolon
DECL|function|request_dma
r_int
id|request_dma
c_func
(paren
r_int
r_int
id|dmanr
comma
r_const
r_char
op_star
id|device_id
)paren
(brace
r_if
c_cond
(paren
id|dmanr
op_ge
id|MAX_DMA_CHANNELS
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|xchg
c_func
(paren
op_amp
id|dma_chan_busy
(braket
id|dmanr
)braket
dot
id|lock
comma
l_int|1
)paren
op_ne
l_int|0
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|dma_chan_busy
(braket
id|dmanr
)braket
dot
id|device_id
op_assign
id|device_id
suffix:semicolon
multiline_comment|/* old flag was 0, now contains 1 to indicate busy */
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* request_dma */
DECL|function|free_dma
r_void
id|free_dma
c_func
(paren
r_int
r_int
id|dmanr
)paren
(brace
r_if
c_cond
(paren
id|dmanr
op_ge
id|MAX_DMA_CHANNELS
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Trying to free DMA%d&bslash;n&quot;
comma
id|dmanr
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|xchg
c_func
(paren
op_amp
id|dma_chan_busy
(braket
id|dmanr
)braket
dot
id|lock
comma
l_int|0
)paren
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Trying to free free DMA%d&bslash;n&quot;
comma
id|dmanr
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
multiline_comment|/* free_dma */
macro_line|#else
DECL|function|request_dma
r_int
id|request_dma
c_func
(paren
r_int
r_int
id|dmanr
comma
r_const
r_char
op_star
id|device_id
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|free_dma
r_void
id|free_dma
c_func
(paren
r_int
r_int
id|dmanr
)paren
(brace
)brace
macro_line|#endif
macro_line|#ifdef CONFIG_PROC_FS
macro_line|#ifdef MAX_DMA_CHANNELS
DECL|function|proc_dma_show
r_static
r_int
id|proc_dma_show
c_func
(paren
r_struct
id|seq_file
op_star
id|m
comma
r_void
op_star
id|v
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
l_int|0
suffix:semicolon
id|i
OL
id|MAX_DMA_CHANNELS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|dma_chan_busy
(braket
id|i
)braket
dot
id|lock
)paren
(brace
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;%2d: %s&bslash;n&quot;
comma
id|i
comma
id|dma_chan_busy
(braket
id|i
)braket
dot
id|device_id
)paren
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#else
DECL|function|proc_dma_show
r_static
r_int
id|proc_dma_show
c_func
(paren
r_struct
id|seq_file
op_star
id|m
comma
r_void
op_star
id|v
)paren
(brace
id|seq_puts
c_func
(paren
id|m
comma
l_string|&quot;No DMA&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif /* MAX_DMA_CHANNELS */
DECL|function|proc_dma_open
r_static
r_int
id|proc_dma_open
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
id|file
)paren
(brace
r_char
op_star
id|buf
op_assign
id|kmalloc
c_func
(paren
id|PAGE_SIZE
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_struct
id|seq_file
op_star
id|m
suffix:semicolon
r_int
id|res
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buf
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|res
op_assign
id|single_open
c_func
(paren
id|file
comma
id|proc_dma_show
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|res
)paren
(brace
id|m
op_assign
id|file-&gt;private_data
suffix:semicolon
id|m-&gt;buf
op_assign
id|buf
suffix:semicolon
id|m-&gt;size
op_assign
id|PAGE_SIZE
suffix:semicolon
)brace
r_else
id|kfree
c_func
(paren
id|buf
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
DECL|variable|proc_dma_operations
r_static
r_struct
id|file_operations
id|proc_dma_operations
op_assign
(brace
dot
id|open
op_assign
id|proc_dma_open
comma
dot
id|read
op_assign
id|seq_read
comma
dot
id|llseek
op_assign
id|seq_lseek
comma
dot
id|release
op_assign
id|single_release
comma
)brace
suffix:semicolon
DECL|function|proc_dma_init
r_static
r_int
id|__init
id|proc_dma_init
c_func
(paren
r_void
)paren
(brace
r_struct
id|proc_dir_entry
op_star
id|e
suffix:semicolon
id|e
op_assign
id|create_proc_entry
c_func
(paren
l_string|&quot;dma&quot;
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|e
)paren
id|e-&gt;proc_fops
op_assign
op_amp
id|proc_dma_operations
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|proc_dma_init
id|__initcall
c_func
(paren
id|proc_dma_init
)paren
suffix:semicolon
macro_line|#endif
DECL|variable|request_dma
id|EXPORT_SYMBOL
c_func
(paren
id|request_dma
)paren
suffix:semicolon
DECL|variable|free_dma
id|EXPORT_SYMBOL
c_func
(paren
id|free_dma
)paren
suffix:semicolon
DECL|variable|dma_spin_lock
id|EXPORT_SYMBOL
c_func
(paren
id|dma_spin_lock
)paren
suffix:semicolon
eof
