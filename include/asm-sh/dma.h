multiline_comment|/*&n; * include/asm-sh/dma.h&n; *&n; * Copyright (C) 2003, 2004  Paul Mundt&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; */
macro_line|#ifndef __ASM_SH_DMA_H
DECL|macro|__ASM_SH_DMA_H
mdefine_line|#define __ASM_SH_DMA_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;linux/sysdev.h&gt;
macro_line|#include &lt;asm/cpu/dma.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
multiline_comment|/* The maximum address that we can perform a DMA transfer to on this platform */
multiline_comment|/* Don&squot;t define MAX_DMA_ADDRESS; it&squot;s useless on the SuperH and any&n;   occurrence should be flagged as an error.  */
multiline_comment|/* But... */
multiline_comment|/* XXX: This is not applicable to SuperH, just needed for alloc_bootmem */
DECL|macro|MAX_DMA_ADDRESS
mdefine_line|#define MAX_DMA_ADDRESS&t;&t;(PAGE_OFFSET+0x10000000)
macro_line|#ifdef CONFIG_NR_DMA_CHANNELS
DECL|macro|MAX_DMA_CHANNELS
macro_line|#  define MAX_DMA_CHANNELS&t;(CONFIG_NR_DMA_CHANNELS)
macro_line|#else
DECL|macro|MAX_DMA_CHANNELS
macro_line|#  define MAX_DMA_CHANNELS&t;(CONFIG_NR_ONCHIP_DMA_CHANNELS)
macro_line|#endif
multiline_comment|/*&n; * Read and write modes can mean drastically different things depending on the&n; * channel configuration. Consult your DMAC documentation and module&n; * implementation for further clues.&n; */
DECL|macro|DMA_MODE_READ
mdefine_line|#define DMA_MODE_READ&t;&t;0x00
DECL|macro|DMA_MODE_WRITE
mdefine_line|#define DMA_MODE_WRITE&t;&t;0x01
DECL|macro|DMA_MODE_MASK
mdefine_line|#define DMA_MODE_MASK&t;&t;0x01
DECL|macro|DMA_AUTOINIT
mdefine_line|#define DMA_AUTOINIT&t;&t;0x10
multiline_comment|/*&n; * DMAC (dma_info) flags&n; */
r_enum
(brace
DECL|enumerator|DMAC_CHANNELS_CONFIGURED
id|DMAC_CHANNELS_CONFIGURED
op_assign
l_int|0x00
comma
DECL|enumerator|DMAC_CHANNELS_TEI_CAPABLE
id|DMAC_CHANNELS_TEI_CAPABLE
op_assign
l_int|0x01
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * DMA channel capabilities / flags&n; */
r_enum
(brace
DECL|enumerator|DMA_CONFIGURED
id|DMA_CONFIGURED
op_assign
l_int|0x00
comma
DECL|enumerator|DMA_TEI_CAPABLE
id|DMA_TEI_CAPABLE
op_assign
l_int|0x01
comma
)brace
suffix:semicolon
r_extern
id|spinlock_t
id|dma_spin_lock
suffix:semicolon
r_struct
id|dma_channel
suffix:semicolon
DECL|struct|dma_ops
r_struct
id|dma_ops
(brace
DECL|member|request
r_int
(paren
op_star
id|request
)paren
(paren
r_struct
id|dma_channel
op_star
id|chan
)paren
suffix:semicolon
DECL|member|free
r_void
(paren
op_star
id|free
)paren
(paren
r_struct
id|dma_channel
op_star
id|chan
)paren
suffix:semicolon
DECL|member|get_residue
r_int
(paren
op_star
id|get_residue
)paren
(paren
r_struct
id|dma_channel
op_star
id|chan
)paren
suffix:semicolon
DECL|member|xfer
r_int
(paren
op_star
id|xfer
)paren
(paren
r_struct
id|dma_channel
op_star
id|chan
)paren
suffix:semicolon
DECL|member|configure
r_void
(paren
op_star
id|configure
)paren
(paren
r_struct
id|dma_channel
op_star
id|chan
comma
r_int
r_int
id|flags
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|dma_channel
r_struct
id|dma_channel
(brace
DECL|member|dev_id
r_char
id|dev_id
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|chan
r_int
r_int
id|chan
suffix:semicolon
DECL|member|mode
r_int
r_int
id|mode
suffix:semicolon
DECL|member|count
r_int
r_int
id|count
suffix:semicolon
DECL|member|sar
r_int
r_int
id|sar
suffix:semicolon
DECL|member|dar
r_int
r_int
id|dar
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|member|busy
id|atomic_t
id|busy
suffix:semicolon
DECL|member|sem
r_struct
id|semaphore
id|sem
suffix:semicolon
DECL|member|wait_queue
id|wait_queue_head_t
id|wait_queue
suffix:semicolon
DECL|member|dev
r_struct
id|sys_device
id|dev
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|dma_info
r_struct
id|dma_info
(brace
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|nr_channels
r_int
r_int
id|nr_channels
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|member|ops
r_struct
id|dma_ops
op_star
id|ops
suffix:semicolon
DECL|member|channels
r_struct
id|dma_channel
op_star
id|channels
suffix:semicolon
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|to_dma_channel
mdefine_line|#define to_dma_channel(channel) container_of(channel, struct dma_channel, dev)
multiline_comment|/* arch/sh/drivers/dma/dma-api.c */
r_extern
r_int
id|dma_xfer
c_func
(paren
r_int
r_int
id|chan
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
id|size
comma
r_int
r_int
id|mode
)paren
suffix:semicolon
DECL|macro|dma_write
mdefine_line|#define dma_write(chan, from, to, size)&t;&bslash;&n;&t;dma_xfer(chan, from, to, size, DMA_MODE_WRITE)
DECL|macro|dma_write_page
mdefine_line|#define dma_write_page(chan, from, to)&t;&bslash;&n;&t;dma_write(chan, from, to, PAGE_SIZE)
DECL|macro|dma_read
mdefine_line|#define dma_read(chan, from, to, size)&t;&bslash;&n;&t;dma_xfer(chan, from, to, size, DMA_MODE_READ)
DECL|macro|dma_read_page
mdefine_line|#define dma_read_page(chan, from, to)&t;&bslash;&n;&t;dma_read(chan, from, to, PAGE_SIZE)
r_extern
r_int
id|request_dma
c_func
(paren
r_int
r_int
id|chan
comma
r_const
r_char
op_star
id|dev_id
)paren
suffix:semicolon
r_extern
r_void
id|free_dma
c_func
(paren
r_int
r_int
id|chan
)paren
suffix:semicolon
r_extern
r_int
id|get_dma_residue
c_func
(paren
r_int
r_int
id|chan
)paren
suffix:semicolon
r_extern
r_struct
id|dma_info
op_star
id|get_dma_info
c_func
(paren
r_int
r_int
id|chan
)paren
suffix:semicolon
r_extern
r_struct
id|dma_channel
op_star
id|get_dma_channel
c_func
(paren
r_int
r_int
id|chan
)paren
suffix:semicolon
r_extern
r_void
id|dma_wait_for_completion
c_func
(paren
r_int
r_int
id|chan
)paren
suffix:semicolon
r_extern
r_void
id|dma_configure_channel
c_func
(paren
r_int
r_int
id|chan
comma
r_int
r_int
id|flags
)paren
suffix:semicolon
r_extern
r_int
id|register_dmac
c_func
(paren
r_struct
id|dma_info
op_star
id|info
)paren
suffix:semicolon
r_extern
r_void
id|unregister_dmac
c_func
(paren
r_struct
id|dma_info
op_star
id|info
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SYSFS
multiline_comment|/* arch/sh/drivers/dma/dma-sysfs.c */
r_extern
r_int
id|dma_create_sysfs_files
c_func
(paren
r_struct
id|dma_channel
op_star
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_PCI
r_extern
r_int
id|isa_dma_bridge_buggy
suffix:semicolon
macro_line|#else
DECL|macro|isa_dma_bridge_buggy
mdefine_line|#define isa_dma_bridge_buggy&t;(0)
macro_line|#endif
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __ASM_SH_DMA_H */
eof
