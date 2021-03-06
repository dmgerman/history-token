multiline_comment|/*&n; * $Id: video-buf.h,v 1.9 2004/11/07 13:17:15 kraxel Exp $&n; *&n; * generic helper functions for video4linux capture buffers, to handle&n; * memory management and PCI DMA.  Right now bttv + saa7134 use it.&n; *&n; * The functions expect the hardware being able to scatter gatter&n; * (i.e. the buffers are not linear in physical memory, but fragmented&n; * into PAGE_SIZE chunks).  They also assume the driver does not need&n; * to touch the video data (thus it is probably not useful for USB as&n; * data often must be uncompressed by the drivers).&n; *&n; * (c) 2001,02 Gerd Knorr &lt;kraxel@bytesex.org&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; */
macro_line|#include &lt;linux/videodev.h&gt;
DECL|macro|UNSET
mdefine_line|#define UNSET (-1U)
multiline_comment|/* --------------------------------------------------------------------- */
multiline_comment|/*&n; * Return a scatterlist for some page-aligned vmalloc()&squot;ed memory&n; * block (NULL on errors).  Memory for the scatterlist is allocated&n; * using kmalloc.  The caller must free the memory.&n; */
r_struct
id|scatterlist
op_star
id|videobuf_vmalloc_to_sg
c_func
(paren
r_int
r_char
op_star
id|virt
comma
r_int
id|nr_pages
)paren
suffix:semicolon
multiline_comment|/*&n; * Return a scatterlist for a an array of userpages (NULL on errors).&n; * Memory for the scatterlist is allocated using kmalloc.  The caller&n; * must free the memory.&n; */
r_struct
id|scatterlist
op_star
id|videobuf_pages_to_sg
c_func
(paren
r_struct
id|page
op_star
op_star
id|pages
comma
r_int
id|nr_pages
comma
r_int
id|offset
)paren
suffix:semicolon
multiline_comment|/* --------------------------------------------------------------------- */
multiline_comment|/*&n; * A small set of helper functions to manage buffers (both userland&n; * and kernel) for DMA.&n; *&n; * videobuf_dma_init_*()&n; *&t;creates a buffer.  The userland version takes a userspace&n; *&t;pointer + length.  The kernel version just wants the size and&n; *&t;does memory allocation too using vmalloc_32().&n; *&n; * videobuf_dma_pci_*()&n; *&t;see Documentation/DMA-mapping.txt, these functions to&n; *&t;basically the same.  The map function does also build a&n; *&t;scatterlist for the buffer (and unmap frees it ...)&n; *&n; * videobuf_dma_free()&n; *&t;no comment ...&n; *&n; */
DECL|struct|videobuf_dmabuf
r_struct
id|videobuf_dmabuf
(brace
DECL|member|magic
id|u32
id|magic
suffix:semicolon
multiline_comment|/* for userland buffer */
DECL|member|offset
r_int
id|offset
suffix:semicolon
DECL|member|pages
r_struct
id|page
op_star
op_star
id|pages
suffix:semicolon
multiline_comment|/* for kernel buffers */
DECL|member|vmalloc
r_void
op_star
id|vmalloc
suffix:semicolon
multiline_comment|/* for overlay buffers (pci-pci dma) */
DECL|member|bus_addr
id|dma_addr_t
id|bus_addr
suffix:semicolon
multiline_comment|/* common */
DECL|member|sglist
r_struct
id|scatterlist
op_star
id|sglist
suffix:semicolon
DECL|member|sglen
r_int
id|sglen
suffix:semicolon
DECL|member|nr_pages
r_int
id|nr_pages
suffix:semicolon
DECL|member|direction
r_int
id|direction
suffix:semicolon
)brace
suffix:semicolon
r_void
id|videobuf_dma_init
c_func
(paren
r_struct
id|videobuf_dmabuf
op_star
id|dma
)paren
suffix:semicolon
r_int
id|videobuf_dma_init_user
c_func
(paren
r_struct
id|videobuf_dmabuf
op_star
id|dma
comma
r_int
id|direction
comma
r_int
r_int
id|data
comma
r_int
r_int
id|size
)paren
suffix:semicolon
r_int
id|videobuf_dma_init_kernel
c_func
(paren
r_struct
id|videobuf_dmabuf
op_star
id|dma
comma
r_int
id|direction
comma
r_int
id|nr_pages
)paren
suffix:semicolon
r_int
id|videobuf_dma_init_overlay
c_func
(paren
r_struct
id|videobuf_dmabuf
op_star
id|dma
comma
r_int
id|direction
comma
id|dma_addr_t
id|addr
comma
r_int
id|nr_pages
)paren
suffix:semicolon
r_int
id|videobuf_dma_pci_map
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_struct
id|videobuf_dmabuf
op_star
id|dma
)paren
suffix:semicolon
r_int
id|videobuf_dma_pci_sync
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_struct
id|videobuf_dmabuf
op_star
id|dma
)paren
suffix:semicolon
r_int
id|videobuf_dma_pci_unmap
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_struct
id|videobuf_dmabuf
op_star
id|dma
)paren
suffix:semicolon
r_int
id|videobuf_dma_free
c_func
(paren
r_struct
id|videobuf_dmabuf
op_star
id|dma
)paren
suffix:semicolon
multiline_comment|/* --------------------------------------------------------------------- */
multiline_comment|/*&n; * A small set of helper functions to manage video4linux buffers.&n; *&n; * struct videobuf_buffer holds the data structures used by the helper&n; * functions, additionally some commonly used fields for v4l buffers&n; * (width, height, lists, waitqueue) are in there.  That struct should&n; * be used as first element in the drivers buffer struct.&n; *&n; * about the mmap helpers (videobuf_mmap_*):&n; *&n; * The mmaper function allows to map any subset of contingous buffers.&n; * This includes one mmap() call for all buffers (which the original&n; * video4linux API uses) as well as one mmap() for every single buffer&n; * (which v4l2 uses).&n; *&n; * If there is a valid mapping for a buffer, buffer-&gt;baddr/bsize holds&n; * userspace address + size which can be feeded into the&n; * videobuf_dma_init_user function listed above.&n; *&n; */
r_struct
id|videobuf_buffer
suffix:semicolon
r_struct
id|videobuf_queue
suffix:semicolon
DECL|struct|videobuf_mapping
r_struct
id|videobuf_mapping
(brace
DECL|member|count
r_int
r_int
id|count
suffix:semicolon
DECL|member|start
r_int
r_int
id|start
suffix:semicolon
DECL|member|end
r_int
r_int
id|end
suffix:semicolon
DECL|member|q
r_struct
id|videobuf_queue
op_star
id|q
suffix:semicolon
)brace
suffix:semicolon
DECL|enum|videobuf_state
r_enum
id|videobuf_state
(brace
DECL|enumerator|STATE_NEEDS_INIT
id|STATE_NEEDS_INIT
op_assign
l_int|0
comma
DECL|enumerator|STATE_PREPARED
id|STATE_PREPARED
op_assign
l_int|1
comma
DECL|enumerator|STATE_QUEUED
id|STATE_QUEUED
op_assign
l_int|2
comma
DECL|enumerator|STATE_ACTIVE
id|STATE_ACTIVE
op_assign
l_int|3
comma
DECL|enumerator|STATE_DONE
id|STATE_DONE
op_assign
l_int|4
comma
DECL|enumerator|STATE_ERROR
id|STATE_ERROR
op_assign
l_int|5
comma
DECL|enumerator|STATE_IDLE
id|STATE_IDLE
op_assign
l_int|6
comma
)brace
suffix:semicolon
DECL|struct|videobuf_buffer
r_struct
id|videobuf_buffer
(brace
DECL|member|i
r_int
r_int
id|i
suffix:semicolon
DECL|member|magic
id|u32
id|magic
suffix:semicolon
multiline_comment|/* info about the buffer */
DECL|member|width
r_int
r_int
id|width
suffix:semicolon
DECL|member|height
r_int
r_int
id|height
suffix:semicolon
DECL|member|bytesperline
r_int
r_int
id|bytesperline
suffix:semicolon
multiline_comment|/* use only if != 0 */
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
DECL|member|input
r_int
r_int
id|input
suffix:semicolon
DECL|member|field
r_enum
id|v4l2_field
id|field
suffix:semicolon
DECL|member|state
r_enum
id|videobuf_state
id|state
suffix:semicolon
DECL|member|dma
r_struct
id|videobuf_dmabuf
id|dma
suffix:semicolon
DECL|member|stream
r_struct
id|list_head
id|stream
suffix:semicolon
multiline_comment|/* QBUF/DQBUF list */
multiline_comment|/* for mmap&squot;ed buffers */
DECL|member|memory
r_enum
id|v4l2_memory
id|memory
suffix:semicolon
DECL|member|boff
r_int
id|boff
suffix:semicolon
multiline_comment|/* buffer offset (mmap + overlay) */
DECL|member|bsize
r_int
id|bsize
suffix:semicolon
multiline_comment|/* buffer size */
DECL|member|baddr
r_int
r_int
id|baddr
suffix:semicolon
multiline_comment|/* buffer addr (userland ptr!) */
DECL|member|map
r_struct
id|videobuf_mapping
op_star
id|map
suffix:semicolon
multiline_comment|/* touched by irq handler */
DECL|member|queue
r_struct
id|list_head
id|queue
suffix:semicolon
DECL|member|done
id|wait_queue_head_t
id|done
suffix:semicolon
DECL|member|field_count
r_int
r_int
id|field_count
suffix:semicolon
DECL|member|ts
r_struct
id|timeval
id|ts
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|videobuf_queue_ops
r_struct
id|videobuf_queue_ops
(brace
DECL|member|buf_setup
r_int
(paren
op_star
id|buf_setup
)paren
(paren
r_struct
id|videobuf_queue
op_star
id|q
comma
r_int
r_int
op_star
id|count
comma
r_int
r_int
op_star
id|size
)paren
suffix:semicolon
DECL|member|buf_prepare
r_int
(paren
op_star
id|buf_prepare
)paren
(paren
r_struct
id|videobuf_queue
op_star
id|q
comma
r_struct
id|videobuf_buffer
op_star
id|vb
comma
r_enum
id|v4l2_field
id|field
)paren
suffix:semicolon
DECL|member|buf_queue
r_void
(paren
op_star
id|buf_queue
)paren
(paren
r_struct
id|videobuf_queue
op_star
id|q
comma
r_struct
id|videobuf_buffer
op_star
id|vb
)paren
suffix:semicolon
DECL|member|buf_release
r_void
(paren
op_star
id|buf_release
)paren
(paren
r_struct
id|videobuf_queue
op_star
id|q
comma
r_struct
id|videobuf_buffer
op_star
id|vb
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|videobuf_queue
r_struct
id|videobuf_queue
(brace
DECL|member|lock
r_struct
id|semaphore
id|lock
suffix:semicolon
DECL|member|irqlock
id|spinlock_t
op_star
id|irqlock
suffix:semicolon
DECL|member|pci
r_struct
id|pci_dev
op_star
id|pci
suffix:semicolon
DECL|member|type
r_enum
id|v4l2_buf_type
id|type
suffix:semicolon
DECL|member|inputs
r_int
r_int
id|inputs
suffix:semicolon
multiline_comment|/* for V4L2_BUF_FLAG_INPUT */
DECL|member|msize
r_int
r_int
id|msize
suffix:semicolon
DECL|member|field
r_enum
id|v4l2_field
id|field
suffix:semicolon
DECL|member|last
r_enum
id|v4l2_field
id|last
suffix:semicolon
multiline_comment|/* for field=V4L2_FIELD_ALTERNATE */
DECL|member|bufs
r_struct
id|videobuf_buffer
op_star
id|bufs
(braket
id|VIDEO_MAX_FRAME
)braket
suffix:semicolon
DECL|member|ops
r_struct
id|videobuf_queue_ops
op_star
id|ops
suffix:semicolon
multiline_comment|/* capture via mmap() + ioctl(QBUF/DQBUF) */
DECL|member|streaming
r_int
r_int
id|streaming
suffix:semicolon
DECL|member|stream
r_struct
id|list_head
id|stream
suffix:semicolon
multiline_comment|/* capture via read() */
DECL|member|reading
r_int
r_int
id|reading
suffix:semicolon
DECL|member|read_off
r_int
r_int
id|read_off
suffix:semicolon
DECL|member|read_buf
r_struct
id|videobuf_buffer
op_star
id|read_buf
suffix:semicolon
multiline_comment|/* driver private data */
DECL|member|priv_data
r_void
op_star
id|priv_data
suffix:semicolon
)brace
suffix:semicolon
r_void
op_star
id|videobuf_alloc
c_func
(paren
r_int
r_int
id|size
)paren
suffix:semicolon
r_int
id|videobuf_waiton
c_func
(paren
r_struct
id|videobuf_buffer
op_star
id|vb
comma
r_int
id|non_blocking
comma
r_int
id|intr
)paren
suffix:semicolon
r_int
id|videobuf_iolock
c_func
(paren
r_struct
id|pci_dev
op_star
id|pci
comma
r_struct
id|videobuf_buffer
op_star
id|vb
comma
r_struct
id|v4l2_framebuffer
op_star
id|fbuf
)paren
suffix:semicolon
r_void
id|videobuf_queue_init
c_func
(paren
r_struct
id|videobuf_queue
op_star
id|q
comma
r_struct
id|videobuf_queue_ops
op_star
id|ops
comma
r_struct
id|pci_dev
op_star
id|pci
comma
id|spinlock_t
op_star
id|irqlock
comma
r_enum
id|v4l2_buf_type
id|type
comma
r_enum
id|v4l2_field
id|field
comma
r_int
r_int
id|msize
comma
r_void
op_star
id|priv
)paren
suffix:semicolon
r_int
id|videobuf_queue_is_busy
c_func
(paren
r_struct
id|videobuf_queue
op_star
id|q
)paren
suffix:semicolon
r_void
id|videobuf_queue_cancel
c_func
(paren
r_struct
id|videobuf_queue
op_star
id|q
)paren
suffix:semicolon
r_enum
id|v4l2_field
id|videobuf_next_field
c_func
(paren
r_struct
id|videobuf_queue
op_star
id|q
)paren
suffix:semicolon
r_void
id|videobuf_status
c_func
(paren
r_struct
id|v4l2_buffer
op_star
id|b
comma
r_struct
id|videobuf_buffer
op_star
id|vb
comma
r_enum
id|v4l2_buf_type
id|type
)paren
suffix:semicolon
r_int
id|videobuf_reqbufs
c_func
(paren
r_struct
id|videobuf_queue
op_star
id|q
comma
r_struct
id|v4l2_requestbuffers
op_star
id|req
)paren
suffix:semicolon
r_int
id|videobuf_querybuf
c_func
(paren
r_struct
id|videobuf_queue
op_star
id|q
comma
r_struct
id|v4l2_buffer
op_star
id|b
)paren
suffix:semicolon
r_int
id|videobuf_qbuf
c_func
(paren
r_struct
id|videobuf_queue
op_star
id|q
comma
r_struct
id|v4l2_buffer
op_star
id|b
)paren
suffix:semicolon
r_int
id|videobuf_dqbuf
c_func
(paren
r_struct
id|videobuf_queue
op_star
id|q
comma
r_struct
id|v4l2_buffer
op_star
id|b
comma
r_int
id|nonblocking
)paren
suffix:semicolon
r_int
id|videobuf_streamon
c_func
(paren
r_struct
id|videobuf_queue
op_star
id|q
)paren
suffix:semicolon
r_int
id|videobuf_streamoff
c_func
(paren
r_struct
id|videobuf_queue
op_star
id|q
)paren
suffix:semicolon
r_int
id|videobuf_read_start
c_func
(paren
r_struct
id|videobuf_queue
op_star
id|q
)paren
suffix:semicolon
r_void
id|videobuf_read_stop
c_func
(paren
r_struct
id|videobuf_queue
op_star
id|q
)paren
suffix:semicolon
id|ssize_t
id|videobuf_read_stream
c_func
(paren
r_struct
id|videobuf_queue
op_star
id|q
comma
r_char
id|__user
op_star
id|data
comma
r_int
id|count
comma
id|loff_t
op_star
id|ppos
comma
r_int
id|vbihack
comma
r_int
id|nonblocking
)paren
suffix:semicolon
id|ssize_t
id|videobuf_read_one
c_func
(paren
r_struct
id|videobuf_queue
op_star
id|q
comma
r_char
id|__user
op_star
id|data
comma
r_int
id|count
comma
id|loff_t
op_star
id|ppos
comma
r_int
id|nonblocking
)paren
suffix:semicolon
r_int
r_int
id|videobuf_poll_stream
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_struct
id|videobuf_queue
op_star
id|q
comma
id|poll_table
op_star
id|wait
)paren
suffix:semicolon
r_int
id|videobuf_mmap_setup
c_func
(paren
r_struct
id|videobuf_queue
op_star
id|q
comma
r_int
r_int
id|bcount
comma
r_int
r_int
id|bsize
comma
r_enum
id|v4l2_memory
id|memory
)paren
suffix:semicolon
r_int
id|videobuf_mmap_free
c_func
(paren
r_struct
id|videobuf_queue
op_star
id|q
)paren
suffix:semicolon
r_int
id|videobuf_mmap_mapper
c_func
(paren
r_struct
id|videobuf_queue
op_star
id|q
comma
r_struct
id|vm_area_struct
op_star
id|vma
)paren
suffix:semicolon
multiline_comment|/* --------------------------------------------------------------------- */
multiline_comment|/*&n; * Local variables:&n; * c-basic-offset: 8&n; * End:&n; */
eof
