multiline_comment|/*&n; * arch/arm/kernel/dma-sa1100.c&n; *&n; * Support functions for the SA11x0 internal DMA channels.&n; * (see also Documentation/arm/SA1100/DMA)&n; *&n; * Copyright (C) 2000 Nicolas Pitre&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/mach/dma.h&gt;
DECL|macro|DEBUG
macro_line|#undef DEBUG
macro_line|#ifdef DEBUG
DECL|macro|DPRINTK
mdefine_line|#define DPRINTK( s, arg... )  printk( &quot;dma&lt;%s&gt;: &quot; s, dma-&gt;device_id , ##arg )
macro_line|#else
DECL|macro|DPRINTK
mdefine_line|#define DPRINTK( x... )
macro_line|#endif
multiline_comment|/*&n; * DMA control register structure&n; */
r_typedef
r_struct
(brace
DECL|member|DDAR
r_volatile
id|u_long
id|DDAR
suffix:semicolon
DECL|member|SetDCSR
r_volatile
id|u_long
id|SetDCSR
suffix:semicolon
DECL|member|ClrDCSR
r_volatile
id|u_long
id|ClrDCSR
suffix:semicolon
DECL|member|RdDCSR
r_volatile
id|u_long
id|RdDCSR
suffix:semicolon
DECL|member|DBSA
r_volatile
id|dma_addr_t
id|DBSA
suffix:semicolon
DECL|member|DBTA
r_volatile
id|u_long
id|DBTA
suffix:semicolon
DECL|member|DBSB
r_volatile
id|dma_addr_t
id|DBSB
suffix:semicolon
DECL|member|DBTB
r_volatile
id|u_long
id|DBTB
suffix:semicolon
DECL|typedef|dma_regs_t
)brace
id|dma_regs_t
suffix:semicolon
macro_line|#include &quot;dma.h&quot;
DECL|variable|dma_chan
id|sa1100_dma_t
id|dma_chan
(braket
id|MAX_SA1100_DMA_CHANNELS
)braket
suffix:semicolon
multiline_comment|/*&n; * Maximum physical DMA buffer size&n; */
DECL|macro|MAX_DMA_SIZE
mdefine_line|#define MAX_DMA_SIZE&t;&t;0x1fff
DECL|macro|MAX_DMA_ORDER
mdefine_line|#define MAX_DMA_ORDER&t;&t;12
multiline_comment|/*&n; * DMA processing...&n; */
DECL|function|start_sa1100_dma
r_static
r_inline
r_int
id|start_sa1100_dma
c_func
(paren
id|sa1100_dma_t
op_star
id|dma
comma
id|dma_addr_t
id|dma_ptr
comma
r_int
id|size
)paren
(brace
id|dma_regs_t
op_star
id|regs
op_assign
id|dma-&gt;regs
suffix:semicolon
r_int
id|status
suffix:semicolon
id|status
op_assign
id|regs-&gt;RdDCSR
suffix:semicolon
multiline_comment|/* If both DMA buffers are started, there&squot;s nothing else we can do. */
r_if
c_cond
(paren
(paren
id|status
op_amp
(paren
id|DCSR_STRTA
op_or
id|DCSR_STRTB
)paren
)paren
op_eq
(paren
id|DCSR_STRTA
op_or
id|DCSR_STRTB
)paren
)paren
(brace
id|DPRINTK
c_func
(paren
l_string|&quot;start: st %#x busy&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
(paren
id|status
op_amp
id|DCSR_BIU
)paren
op_logical_and
(paren
id|status
op_amp
id|DCSR_STRTB
)paren
)paren
op_logical_or
(paren
op_logical_neg
(paren
id|status
op_amp
id|DCSR_BIU
)paren
op_logical_and
op_logical_neg
(paren
id|status
op_amp
id|DCSR_STRTA
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
id|status
op_amp
id|DCSR_DONEA
)paren
(brace
multiline_comment|/* give a chance for the interrupt to be processed */
r_goto
id|irq_pending
suffix:semicolon
)brace
id|regs-&gt;DBSA
op_assign
id|dma_ptr
suffix:semicolon
id|regs-&gt;DBTA
op_assign
id|size
suffix:semicolon
id|regs-&gt;SetDCSR
op_assign
id|DCSR_STRTA
op_or
id|DCSR_IE
op_or
id|DCSR_RUN
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;start a=%#x s=%d on A&bslash;n&quot;
comma
id|dma_ptr
comma
id|size
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|status
op_amp
id|DCSR_DONEB
)paren
(brace
multiline_comment|/* give a chance for the interrupt to be processed */
r_goto
id|irq_pending
suffix:semicolon
)brace
id|regs-&gt;DBSB
op_assign
id|dma_ptr
suffix:semicolon
id|regs-&gt;DBTB
op_assign
id|size
suffix:semicolon
id|regs-&gt;SetDCSR
op_assign
id|DCSR_STRTB
op_or
id|DCSR_IE
op_or
id|DCSR_RUN
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;start a=%#x s=%d on B&bslash;n&quot;
comma
id|dma_ptr
comma
id|size
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
id|irq_pending
suffix:colon
r_return
op_minus
id|EAGAIN
suffix:semicolon
)brace
DECL|function|start_dma
r_static
r_int
id|start_dma
c_func
(paren
id|sa1100_dma_t
op_star
id|dma
comma
id|dma_addr_t
id|dma_ptr
comma
r_int
id|size
)paren
(brace
r_if
c_cond
(paren
id|channel_is_sa1111_sac
c_func
(paren
id|dma
op_minus
id|dma_chan
)paren
)paren
r_return
id|start_sa1111_sac_dma
c_func
(paren
id|dma
comma
id|dma_ptr
comma
id|size
)paren
suffix:semicolon
r_return
id|start_sa1100_dma
c_func
(paren
id|dma
comma
id|dma_ptr
comma
id|size
)paren
suffix:semicolon
)brace
multiline_comment|/* This must be called with IRQ disabled */
DECL|function|process_dma
r_static
r_void
id|process_dma
c_func
(paren
id|sa1100_dma_t
op_star
id|dma
)paren
(brace
id|dma_buf_t
op_star
id|buf
suffix:semicolon
r_int
id|chunksize
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|buf
op_assign
id|dma-&gt;tail
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buf
op_logical_or
id|dma-&gt;stopped
)paren
(brace
multiline_comment|/* no more data available */
id|DPRINTK
c_func
(paren
l_string|&quot;process: no more buf (dma %s)&bslash;n&quot;
comma
id|dma-&gt;curr
ques
c_cond
l_string|&quot;active&quot;
suffix:colon
l_string|&quot;inactive&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * Some devices may require DMA still sending data&n;&t;&t;&t; * at any time for clock reference, etc.&n;&t;&t;&t; * Note: if there is still a data buffer being&n;&t;&t;&t; * processed then the ref count is negative.  This&n;&t;&t;&t; * allows for the DMA termination to be accounted in&n;&t;&t;&t; * the proper order.&n;&t;&t;&t; */
r_if
c_cond
(paren
id|dma-&gt;spin_size
op_logical_and
id|dma-&gt;spin_ref
op_ge
l_int|0
)paren
(brace
id|chunksize
op_assign
id|dma-&gt;spin_size
suffix:semicolon
r_if
c_cond
(paren
id|chunksize
OG
id|MAX_DMA_SIZE
)paren
id|chunksize
op_assign
(paren
l_int|1
op_lshift
id|MAX_DMA_ORDER
)paren
suffix:semicolon
r_while
c_loop
(paren
id|start_dma
c_func
(paren
id|dma
comma
id|dma-&gt;spin_addr
comma
id|chunksize
)paren
op_eq
l_int|0
)paren
id|dma-&gt;spin_ref
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|dma-&gt;curr
op_ne
l_int|NULL
)paren
id|dma-&gt;spin_ref
op_assign
op_minus
id|dma-&gt;spin_ref
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Let&squot;s try to start DMA on the current buffer.&n;&t;&t; * If DMA is busy then we break here.&n;&t;&t; */
id|chunksize
op_assign
id|buf-&gt;size
suffix:semicolon
r_if
c_cond
(paren
id|chunksize
OG
id|MAX_DMA_SIZE
)paren
id|chunksize
op_assign
(paren
l_int|1
op_lshift
id|MAX_DMA_ORDER
)paren
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;process: b=%#x s=%d&bslash;n&quot;
comma
(paren
r_int
)paren
id|buf-&gt;id
comma
id|buf-&gt;size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|start_dma
c_func
(paren
id|dma
comma
id|buf-&gt;dma_ptr
comma
id|chunksize
)paren
op_ne
l_int|0
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dma-&gt;curr
)paren
id|dma-&gt;curr
op_assign
id|buf
suffix:semicolon
id|buf-&gt;ref
op_increment
suffix:semicolon
id|buf-&gt;dma_ptr
op_add_assign
id|chunksize
suffix:semicolon
id|buf-&gt;size
op_sub_assign
id|chunksize
suffix:semicolon
r_if
c_cond
(paren
id|buf-&gt;size
op_eq
l_int|0
)paren
(brace
multiline_comment|/* current buffer is done: move tail to the next one */
id|dma-&gt;tail
op_assign
id|buf-&gt;next
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;process: next b=%#x&bslash;n&quot;
comma
(paren
r_int
)paren
id|dma-&gt;tail
)paren
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/* This must be called with IRQ disabled */
DECL|function|sa1100_dma_done
r_void
id|sa1100_dma_done
(paren
id|sa1100_dma_t
op_star
id|dma
)paren
(brace
id|dma_buf_t
op_star
id|buf
op_assign
id|dma-&gt;curr
suffix:semicolon
r_if
c_cond
(paren
id|dma-&gt;spin_ref
OG
l_int|0
)paren
(brace
id|dma-&gt;spin_ref
op_decrement
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|buf
)paren
(brace
id|buf-&gt;ref
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|buf-&gt;ref
op_eq
l_int|0
op_logical_and
id|buf-&gt;size
op_eq
l_int|0
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * Current buffer is done.&n;&t;&t;&t; * Move current reference to the next one and send&n;&t;&t;&t; * the processed buffer to the callback function,&n;&t;&t;&t; * then discard it.&n;&t;&t;&t; */
id|DPRINTK
c_func
(paren
l_string|&quot;IRQ: buf done&bslash;n&quot;
)paren
suffix:semicolon
id|dma-&gt;curr
op_assign
id|buf-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|dma-&gt;curr
op_eq
l_int|NULL
)paren
id|dma-&gt;spin_ref
op_assign
op_minus
id|dma-&gt;spin_ref
suffix:semicolon
r_if
c_cond
(paren
id|dma-&gt;head
op_eq
id|buf
)paren
id|dma-&gt;head
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|dma-&gt;callback
)paren
(brace
r_int
id|size
op_assign
id|buf-&gt;dma_ptr
op_minus
id|buf-&gt;dma_start
suffix:semicolon
id|dma
op_member_access_from_pointer
id|callback
c_func
(paren
id|buf-&gt;id
comma
id|size
)paren
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|buf
)paren
suffix:semicolon
)brace
)brace
id|process_dma
c_func
(paren
id|dma
)paren
suffix:semicolon
)brace
DECL|function|dma_irq_handler
r_static
r_void
id|dma_irq_handler
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|sa1100_dma_t
op_star
id|dma
op_assign
(paren
id|sa1100_dma_t
op_star
)paren
id|dev_id
suffix:semicolon
r_int
id|status
op_assign
id|dma-&gt;regs-&gt;RdDCSR
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;IRQ: b=%#x st=%#x&bslash;n&quot;
comma
(paren
r_int
)paren
id|dma-&gt;curr-&gt;id
comma
id|status
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
(paren
id|DCSR_ERROR
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;DMA on &bslash;&quot;%s&bslash;&quot; caused an error&bslash;n&quot;
comma
id|dma-&gt;device_id
)paren
suffix:semicolon
id|dma-&gt;regs-&gt;ClrDCSR
op_assign
id|DCSR_ERROR
suffix:semicolon
)brace
id|dma-&gt;regs-&gt;ClrDCSR
op_assign
id|status
op_amp
(paren
id|DCSR_DONEA
op_or
id|DCSR_DONEB
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
id|DCSR_DONEA
)paren
id|sa1100_dma_done
(paren
id|dma
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
id|DCSR_DONEB
)paren
id|sa1100_dma_done
(paren
id|dma
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * DMA interface functions&n; */
DECL|variable|dma_list_lock
r_static
id|spinlock_t
id|dma_list_lock
suffix:semicolon
DECL|function|sa1100_request_dma
r_int
id|sa1100_request_dma
(paren
id|dmach_t
op_star
id|channel
comma
r_const
r_char
op_star
id|device_id
comma
id|dma_device_t
id|device
)paren
(brace
id|sa1100_dma_t
op_star
id|dma
op_assign
l_int|NULL
suffix:semicolon
id|dma_regs_t
op_star
id|regs
suffix:semicolon
r_int
id|i
comma
id|err
suffix:semicolon
op_star
id|channel
op_assign
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* to be sure we catch the freeing of a misregistered channel */
id|err
op_assign
l_int|0
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|dma_list_lock
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
id|SA1100_DMA_CHANNELS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|dma_chan
(braket
id|i
)braket
dot
id|in_use
)paren
(brace
r_if
c_cond
(paren
id|dma_chan
(braket
id|i
)braket
dot
id|device
op_eq
id|device
)paren
(brace
id|err
op_assign
op_minus
id|EBUSY
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|dma
)paren
(brace
id|dma
op_assign
op_amp
id|dma_chan
(braket
id|i
)braket
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|err
)paren
(brace
r_if
c_cond
(paren
id|dma
)paren
id|dma-&gt;in_use
op_assign
l_int|1
suffix:semicolon
r_else
id|err
op_assign
op_minus
id|ENOSR
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|dma_list_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_return
id|err
suffix:semicolon
id|err
op_assign
id|request_irq
c_func
(paren
id|dma-&gt;irq
comma
id|dma_irq_handler
comma
id|SA_INTERRUPT
comma
id|device_id
comma
(paren
r_void
op_star
)paren
id|dma
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
id|KERN_ERR
l_string|&quot;%s: unable to request IRQ %d for DMA channel&bslash;n&quot;
comma
id|device_id
comma
id|dma-&gt;irq
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
op_star
id|channel
op_assign
id|dma
op_minus
id|dma_chan
suffix:semicolon
id|dma-&gt;device_id
op_assign
id|device_id
suffix:semicolon
id|dma-&gt;device
op_assign
id|device
suffix:semicolon
id|dma-&gt;callback
op_assign
l_int|NULL
suffix:semicolon
id|dma-&gt;spin_size
op_assign
l_int|0
suffix:semicolon
id|regs
op_assign
id|dma-&gt;regs
suffix:semicolon
id|regs-&gt;ClrDCSR
op_assign
(paren
id|DCSR_DONEA
op_or
id|DCSR_DONEB
op_or
id|DCSR_STRTA
op_or
id|DCSR_STRTB
op_or
id|DCSR_IE
op_or
id|DCSR_ERROR
op_or
id|DCSR_RUN
)paren
suffix:semicolon
id|regs-&gt;DDAR
op_assign
id|device
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;requested&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sa1100_dma_set_callback
r_int
id|sa1100_dma_set_callback
c_func
(paren
id|dmach_t
id|channel
comma
id|dma_callback_t
id|cb
)paren
(brace
id|sa1100_dma_t
op_star
id|dma
op_assign
op_amp
id|dma_chan
(braket
id|channel
)braket
suffix:semicolon
r_if
c_cond
(paren
(paren
r_int
)paren
id|channel
op_ge
id|MAX_SA1100_DMA_CHANNELS
op_logical_or
op_logical_neg
id|dma-&gt;in_use
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|dma-&gt;callback
op_assign
id|cb
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;cb = %p&bslash;n&quot;
comma
id|cb
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sa1100_dma_set_spin
r_int
id|sa1100_dma_set_spin
c_func
(paren
id|dmach_t
id|channel
comma
id|dma_addr_t
id|addr
comma
r_int
id|size
)paren
(brace
id|sa1100_dma_t
op_star
id|dma
op_assign
op_amp
id|dma_chan
(braket
id|channel
)braket
suffix:semicolon
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
(paren
r_int
)paren
id|channel
op_ge
id|MAX_SA1100_DMA_CHANNELS
op_logical_or
op_logical_neg
id|dma-&gt;in_use
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;set spin %d at %#x&bslash;n&quot;
comma
id|size
comma
id|addr
)paren
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|dma-&gt;spin_addr
op_assign
id|addr
suffix:semicolon
id|dma-&gt;spin_size
op_assign
id|size
suffix:semicolon
r_if
c_cond
(paren
id|size
)paren
id|process_dma
c_func
(paren
id|dma
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sa1100_dma_queue_buffer
r_int
id|sa1100_dma_queue_buffer
c_func
(paren
id|dmach_t
id|channel
comma
r_void
op_star
id|buf_id
comma
id|dma_addr_t
id|data
comma
r_int
id|size
)paren
(brace
id|sa1100_dma_t
op_star
id|dma
suffix:semicolon
id|dma_buf_t
op_star
id|buf
suffix:semicolon
r_int
id|flags
suffix:semicolon
id|dma
op_assign
op_amp
id|dma_chan
(braket
id|channel
)braket
suffix:semicolon
r_if
c_cond
(paren
(paren
r_int
)paren
id|channel
op_ge
id|MAX_SA1100_DMA_CHANNELS
op_logical_or
op_logical_neg
id|dma-&gt;in_use
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|buf
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|buf
)paren
comma
id|GFP_ATOMIC
)paren
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
id|buf-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|buf-&gt;ref
op_assign
l_int|0
suffix:semicolon
id|buf-&gt;dma_ptr
op_assign
id|buf-&gt;dma_start
op_assign
id|data
suffix:semicolon
id|buf-&gt;size
op_assign
id|size
suffix:semicolon
id|buf-&gt;id
op_assign
id|buf_id
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;queueing b=%#x a=%#x s=%d&bslash;n&quot;
comma
(paren
r_int
)paren
id|buf_id
comma
id|data
comma
id|size
)paren
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dma-&gt;head
)paren
id|dma-&gt;head-&gt;next
op_assign
id|buf
suffix:semicolon
id|dma-&gt;head
op_assign
id|buf
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dma-&gt;tail
)paren
id|dma-&gt;tail
op_assign
id|buf
suffix:semicolon
id|process_dma
c_func
(paren
id|dma
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sa1100_dma_get_current
r_int
id|sa1100_dma_get_current
c_func
(paren
id|dmach_t
id|channel
comma
r_void
op_star
op_star
id|buf_id
comma
id|dma_addr_t
op_star
id|addr
)paren
(brace
id|sa1100_dma_t
op_star
id|dma
op_assign
op_amp
id|dma_chan
(braket
id|channel
)braket
suffix:semicolon
id|dma_regs_t
op_star
id|regs
suffix:semicolon
r_int
id|flags
comma
id|ret
suffix:semicolon
r_if
c_cond
(paren
(paren
r_int
)paren
id|channel
op_ge
id|MAX_SA1100_DMA_CHANNELS
op_logical_or
op_logical_neg
id|dma-&gt;in_use
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|channel_is_sa1111_sac
c_func
(paren
id|channel
)paren
)paren
r_return
id|sa1111_dma_get_current
c_func
(paren
id|channel
comma
id|buf_id
comma
id|addr
)paren
suffix:semicolon
id|regs
op_assign
id|dma-&gt;regs
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dma-&gt;curr
op_logical_and
id|dma-&gt;spin_ref
op_le
l_int|0
)paren
(brace
id|dma_buf_t
op_star
id|buf
op_assign
id|dma-&gt;curr
suffix:semicolon
r_int
id|status
comma
id|using_bufa
suffix:semicolon
id|status
op_assign
id|regs-&gt;RdDCSR
suffix:semicolon
multiline_comment|/*&n;&t;&t; * If we got here, that&squot;s because there is, or recently was, a&n;&t;&t; * buffer being processed.  We must determine whether buffer&n;&t;&t; * A or B is active.  Two possibilities: either we are&n;&t;&t; * in the middle of a buffer, or the DMA controller just&n;&t;&t; * switched to the next toggle but the interrupt hasn&squot;t been&n;&t;&t; * serviced yet.  The former case is straight forward.  In&n;&t;&t; * the later case, we&squot;ll do like if DMA is just at the end&n;&t;&t; * of the previous toggle since all registers haven&squot;t been&n;&t;&t; * reset yet.  This goes around the edge case and since we&squot;re&n;&t;&t; * always a little behind anyways it shouldn&squot;t make a big&n;&t;&t; * difference.  If DMA has been stopped prior calling this&n;&t;&t; * then the position is always exact.&n;&t;&t; */
id|using_bufa
op_assign
(paren
(paren
op_logical_neg
(paren
id|status
op_amp
id|DCSR_BIU
)paren
op_logical_and
(paren
id|status
op_amp
id|DCSR_STRTA
)paren
)paren
op_logical_or
(paren
(paren
id|status
op_amp
id|DCSR_BIU
)paren
op_logical_and
op_logical_neg
(paren
id|status
op_amp
id|DCSR_STRTB
)paren
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buf_id
)paren
op_star
id|buf_id
op_assign
id|buf-&gt;id
suffix:semicolon
op_star
id|addr
op_assign
(paren
id|using_bufa
)paren
ques
c_cond
id|regs-&gt;DBSA
suffix:colon
id|regs-&gt;DBSB
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Clamp funky pointers sometimes returned by the hardware&n;&t;&t; * on completed DMA transfers&n;&t;&t; */
r_if
c_cond
(paren
op_star
id|addr
template_param
id|buf-&gt;dma_ptr
)paren
op_star
id|addr
op_assign
id|buf-&gt;dma_ptr
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;curr_pos: b=%#x a=%#x&bslash;n&quot;
comma
(paren
r_int
)paren
id|dma-&gt;curr-&gt;id
comma
op_star
id|addr
)paren
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|dma-&gt;tail
op_logical_and
id|dma-&gt;stopped
)paren
(brace
id|dma_buf_t
op_star
id|buf
op_assign
id|dma-&gt;tail
suffix:semicolon
r_if
c_cond
(paren
id|buf_id
)paren
op_star
id|buf_id
op_assign
id|buf-&gt;id
suffix:semicolon
op_star
id|addr
op_assign
id|buf-&gt;dma_ptr
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|buf_id
)paren
op_star
id|buf_id
op_assign
l_int|NULL
suffix:semicolon
op_star
id|addr
op_assign
l_int|0
suffix:semicolon
id|ret
op_assign
op_minus
id|ENXIO
suffix:semicolon
)brace
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|sa1100_dma_stop
r_int
id|sa1100_dma_stop
c_func
(paren
id|dmach_t
id|channel
)paren
(brace
id|sa1100_dma_t
op_star
id|dma
op_assign
op_amp
id|dma_chan
(braket
id|channel
)braket
suffix:semicolon
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|channel_is_sa1111_sac
c_func
(paren
id|channel
)paren
)paren
r_return
id|sa1111_dma_stop
c_func
(paren
id|channel
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dma-&gt;stopped
)paren
r_return
l_int|0
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|dma-&gt;stopped
op_assign
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * Stop DMA and tweak state variables so everything could restart&n;&t; * from there when resume/wakeup occurs.&n;&t; */
id|dma-&gt;regs-&gt;ClrDCSR
op_assign
id|DCSR_RUN
op_or
id|DCSR_IE
suffix:semicolon
r_if
c_cond
(paren
id|dma-&gt;curr
)paren
(brace
id|dma_buf_t
op_star
id|buf
op_assign
id|dma-&gt;curr
suffix:semicolon
r_if
c_cond
(paren
id|dma-&gt;spin_ref
op_le
l_int|0
)paren
(brace
id|dma_addr_t
id|curpos
suffix:semicolon
id|sa1100_dma_get_current
c_func
(paren
id|channel
comma
l_int|NULL
comma
op_amp
id|curpos
)paren
suffix:semicolon
id|buf-&gt;size
op_add_assign
id|buf-&gt;dma_ptr
op_minus
id|curpos
suffix:semicolon
id|buf-&gt;dma_ptr
op_assign
id|curpos
suffix:semicolon
)brace
id|buf-&gt;ref
op_assign
l_int|0
suffix:semicolon
id|dma-&gt;tail
op_assign
id|buf
suffix:semicolon
id|dma-&gt;curr
op_assign
l_int|NULL
suffix:semicolon
)brace
id|dma-&gt;spin_ref
op_assign
l_int|0
suffix:semicolon
id|dma-&gt;regs-&gt;ClrDCSR
op_assign
id|DCSR_STRTA
op_or
id|DCSR_STRTB
op_or
id|DCSR_DONEA
op_or
id|DCSR_DONEB
suffix:semicolon
id|process_dma
c_func
(paren
id|dma
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sa1100_dma_resume
r_int
id|sa1100_dma_resume
c_func
(paren
id|dmach_t
id|channel
)paren
(brace
id|sa1100_dma_t
op_star
id|dma
op_assign
op_amp
id|dma_chan
(braket
id|channel
)braket
suffix:semicolon
r_if
c_cond
(paren
(paren
r_int
)paren
id|channel
op_ge
id|MAX_SA1100_DMA_CHANNELS
op_logical_or
op_logical_neg
id|dma-&gt;in_use
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|channel_is_sa1111_sac
c_func
(paren
id|channel
)paren
)paren
r_return
id|sa1111_dma_resume
c_func
(paren
id|channel
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dma-&gt;stopped
)paren
(brace
r_int
id|flags
suffix:semicolon
id|save_flags_cli
c_func
(paren
id|flags
)paren
suffix:semicolon
id|dma-&gt;stopped
op_assign
l_int|0
suffix:semicolon
id|dma-&gt;spin_ref
op_assign
l_int|0
suffix:semicolon
id|process_dma
c_func
(paren
id|dma
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sa1100_dma_flush_all
r_int
id|sa1100_dma_flush_all
c_func
(paren
id|dmach_t
id|channel
)paren
(brace
id|sa1100_dma_t
op_star
id|dma
op_assign
op_amp
id|dma_chan
(braket
id|channel
)braket
suffix:semicolon
id|dma_buf_t
op_star
id|buf
comma
op_star
id|next_buf
suffix:semicolon
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
(paren
r_int
)paren
id|channel
op_ge
id|MAX_SA1100_DMA_CHANNELS
op_logical_or
op_logical_neg
id|dma-&gt;in_use
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|channel_is_sa1111_sac
c_func
(paren
id|channel
)paren
)paren
id|sa1111_reset_sac_dma
c_func
(paren
id|channel
)paren
suffix:semicolon
r_else
id|dma-&gt;regs-&gt;ClrDCSR
op_assign
id|DCSR_STRTA
op_or
id|DCSR_STRTB
op_or
id|DCSR_DONEA
op_or
id|DCSR_DONEB
op_or
id|DCSR_RUN
op_or
id|DCSR_IE
suffix:semicolon
id|buf
op_assign
id|dma-&gt;curr
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buf
)paren
id|buf
op_assign
id|dma-&gt;tail
suffix:semicolon
id|dma-&gt;head
op_assign
id|dma-&gt;tail
op_assign
id|dma-&gt;curr
op_assign
l_int|NULL
suffix:semicolon
id|dma-&gt;stopped
op_assign
l_int|0
suffix:semicolon
id|dma-&gt;spin_ref
op_assign
l_int|0
suffix:semicolon
id|process_dma
c_func
(paren
id|dma
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
r_while
c_loop
(paren
id|buf
)paren
(brace
id|next_buf
op_assign
id|buf-&gt;next
suffix:semicolon
id|kfree
c_func
(paren
id|buf
)paren
suffix:semicolon
id|buf
op_assign
id|next_buf
suffix:semicolon
)brace
id|DPRINTK
c_func
(paren
l_string|&quot;flushed&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sa1100_free_dma
r_void
id|sa1100_free_dma
c_func
(paren
id|dmach_t
id|channel
)paren
(brace
id|sa1100_dma_t
op_star
id|dma
suffix:semicolon
r_if
c_cond
(paren
(paren
r_int
)paren
id|channel
op_ge
id|MAX_SA1100_DMA_CHANNELS
)paren
r_return
suffix:semicolon
id|dma
op_assign
op_amp
id|dma_chan
(braket
id|channel
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dma-&gt;in_use
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Trying to free free DMA%d&bslash;n&quot;
comma
id|channel
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|sa1100_dma_set_spin
c_func
(paren
id|channel
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
id|sa1100_dma_flush_all
c_func
(paren
id|channel
)paren
suffix:semicolon
r_if
c_cond
(paren
id|channel_is_sa1111_sac
c_func
(paren
id|channel
)paren
)paren
(brace
id|sa1111_cleanup_sac_dma
c_func
(paren
id|channel
)paren
suffix:semicolon
)brace
r_else
(brace
id|free_irq
c_func
(paren
id|IRQ_DMA0
op_plus
id|channel
comma
(paren
r_void
op_star
)paren
id|dma
)paren
suffix:semicolon
)brace
id|dma-&gt;in_use
op_assign
l_int|0
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;freed&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|variable|sa1100_request_dma
id|EXPORT_SYMBOL
c_func
(paren
id|sa1100_request_dma
)paren
suffix:semicolon
DECL|variable|sa1100_dma_set_callback
id|EXPORT_SYMBOL
c_func
(paren
id|sa1100_dma_set_callback
)paren
suffix:semicolon
DECL|variable|sa1100_dma_set_spin
id|EXPORT_SYMBOL
c_func
(paren
id|sa1100_dma_set_spin
)paren
suffix:semicolon
DECL|variable|sa1100_dma_queue_buffer
id|EXPORT_SYMBOL
c_func
(paren
id|sa1100_dma_queue_buffer
)paren
suffix:semicolon
DECL|variable|sa1100_dma_get_current
id|EXPORT_SYMBOL
c_func
(paren
id|sa1100_dma_get_current
)paren
suffix:semicolon
DECL|variable|sa1100_dma_stop
id|EXPORT_SYMBOL
c_func
(paren
id|sa1100_dma_stop
)paren
suffix:semicolon
DECL|variable|sa1100_dma_resume
id|EXPORT_SYMBOL
c_func
(paren
id|sa1100_dma_resume
)paren
suffix:semicolon
DECL|variable|sa1100_dma_flush_all
id|EXPORT_SYMBOL
c_func
(paren
id|sa1100_dma_flush_all
)paren
suffix:semicolon
DECL|variable|sa1100_free_dma
id|EXPORT_SYMBOL
c_func
(paren
id|sa1100_free_dma
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PM
multiline_comment|/* Drivers should call this from their PM callback function */
DECL|function|sa1100_dma_sleep
r_int
id|sa1100_dma_sleep
c_func
(paren
id|dmach_t
id|channel
)paren
(brace
id|sa1100_dma_t
op_star
id|dma
op_assign
op_amp
id|dma_chan
(braket
id|channel
)braket
suffix:semicolon
r_int
id|orig_state
suffix:semicolon
r_if
c_cond
(paren
(paren
r_int
)paren
id|channel
op_ge
id|MAX_SA1100_DMA_CHANNELS
op_logical_or
op_logical_neg
id|dma-&gt;in_use
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|channel_is_sa1111_sac
c_func
(paren
id|channel
)paren
)paren
(brace
multiline_comment|/* We&squot;ll cheat a little until someone actually&n;&t;&t; * write the real thing.&n;&t;&t; */
id|sa1111_reset_sac_dma
c_func
(paren
id|channel
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|orig_state
op_assign
id|dma-&gt;stopped
suffix:semicolon
id|sa1100_dma_stop
c_func
(paren
id|channel
)paren
suffix:semicolon
id|dma-&gt;regs-&gt;ClrDCSR
op_assign
id|DCSR_RUN
op_or
id|DCSR_IE
op_or
id|DCSR_STRTA
op_or
id|DCSR_STRTB
suffix:semicolon
id|dma-&gt;stopped
op_assign
id|orig_state
suffix:semicolon
id|dma-&gt;spin_ref
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sa1100_dma_wakeup
r_int
id|sa1100_dma_wakeup
c_func
(paren
id|dmach_t
id|channel
)paren
(brace
id|sa1100_dma_t
op_star
id|dma
op_assign
op_amp
id|dma_chan
(braket
id|channel
)braket
suffix:semicolon
id|dma_regs_t
op_star
id|regs
suffix:semicolon
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
(paren
r_int
)paren
id|channel
op_ge
id|MAX_SA1100_DMA_CHANNELS
op_logical_or
op_logical_neg
id|dma-&gt;in_use
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|channel_is_sa1111_sac
c_func
(paren
id|channel
)paren
)paren
(brace
multiline_comment|/* We&squot;ll cheat a little until someone actually&n;&t;&t; * write the real thing.&n;&t;&t; */
r_return
l_int|0
suffix:semicolon
)brace
id|regs
op_assign
id|dma-&gt;regs
suffix:semicolon
id|regs-&gt;ClrDCSR
op_assign
(paren
id|DCSR_DONEA
op_or
id|DCSR_DONEB
op_or
id|DCSR_STRTA
op_or
id|DCSR_STRTB
op_or
id|DCSR_IE
op_or
id|DCSR_ERROR
op_or
id|DCSR_RUN
)paren
suffix:semicolon
id|regs-&gt;DDAR
op_assign
id|dma-&gt;device
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|process_dma
c_func
(paren
id|dma
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|sa1100_dma_sleep
id|EXPORT_SYMBOL
c_func
(paren
id|sa1100_dma_sleep
)paren
suffix:semicolon
DECL|variable|sa1100_dma_wakeup
id|EXPORT_SYMBOL
c_func
(paren
id|sa1100_dma_wakeup
)paren
suffix:semicolon
macro_line|#endif
DECL|function|sa1100_init_dma
r_static
r_int
id|__init
id|sa1100_init_dma
c_func
(paren
r_void
)paren
(brace
r_int
id|channel
suffix:semicolon
r_for
c_loop
(paren
id|channel
op_assign
l_int|0
suffix:semicolon
id|channel
OL
id|SA1100_DMA_CHANNELS
suffix:semicolon
id|channel
op_increment
)paren
(brace
id|dma_chan
(braket
id|channel
)braket
dot
id|regs
op_assign
(paren
id|dma_regs_t
op_star
)paren
id|io_p2v
c_func
(paren
id|_DDAR
c_func
(paren
id|channel
)paren
)paren
suffix:semicolon
id|dma_chan
(braket
id|channel
)braket
dot
id|irq
op_assign
id|IRQ_DMA0
op_plus
id|channel
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|sa1100_init_dma
id|__initcall
c_func
(paren
id|sa1100_init_dma
)paren
suffix:semicolon
eof
