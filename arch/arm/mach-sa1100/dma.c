multiline_comment|/*&n; * arch/arm/kernel/dma-sa1100.c&n; *&n; * Support functions for the SA11x0 internal DMA channels.&n; *&n; * Copyright (C) 2000, 2001 by Nicolas Pitre&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
DECL|macro|DEBUG
macro_line|#undef DEBUG
macro_line|#ifdef DEBUG
DECL|macro|DPRINTK
mdefine_line|#define DPRINTK( s, arg... )  printk( &quot;dma&lt;%p&gt;: &quot; s, regs , ##arg )
macro_line|#else
DECL|macro|DPRINTK
mdefine_line|#define DPRINTK( x... )
macro_line|#endif
r_typedef
r_struct
(brace
DECL|member|device_id
r_const
r_char
op_star
id|device_id
suffix:semicolon
multiline_comment|/* device name */
DECL|member|device
id|u_long
id|device
suffix:semicolon
multiline_comment|/* this channel device, 0  if unused*/
DECL|member|callback
id|dma_callback_t
id|callback
suffix:semicolon
multiline_comment|/* to call when DMA completes */
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
multiline_comment|/* ... with private data ptr */
DECL|typedef|sa1100_dma_t
)brace
id|sa1100_dma_t
suffix:semicolon
DECL|variable|dma_chan
r_static
id|sa1100_dma_t
id|dma_chan
(braket
id|SA1100_DMA_CHANNELS
)braket
suffix:semicolon
DECL|variable|dma_list_lock
r_static
id|spinlock_t
id|dma_list_lock
suffix:semicolon
DECL|function|dma_irq_handler
r_static
id|irqreturn_t
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
id|dma_regs_t
op_star
id|dma_regs
op_assign
id|dev_id
suffix:semicolon
id|sa1100_dma_t
op_star
id|dma
op_assign
id|dma_chan
op_plus
(paren
(paren
(paren
id|u_int
)paren
id|dma_regs
op_rshift
l_int|5
)paren
op_amp
l_int|7
)paren
suffix:semicolon
r_int
id|status
op_assign
id|dma_regs-&gt;RdDCSR
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
id|KERN_CRIT
l_string|&quot;DMA on &bslash;&quot;%s&bslash;&quot; caused an error&bslash;n&quot;
comma
id|dma-&gt;device_id
)paren
suffix:semicolon
id|dma_regs-&gt;ClrDCSR
op_assign
id|DCSR_ERROR
suffix:semicolon
)brace
id|dma_regs-&gt;ClrDCSR
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
id|dma-&gt;callback
)paren
(brace
r_if
c_cond
(paren
id|status
op_amp
id|DCSR_DONEA
)paren
id|dma
op_member_access_from_pointer
id|callback
c_func
(paren
id|dma-&gt;data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
id|DCSR_DONEB
)paren
id|dma
op_member_access_from_pointer
id|callback
c_func
(paren
id|dma-&gt;data
)paren
suffix:semicolon
)brace
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;sa1100_request_dma - allocate one of the SA11x0&squot;s DMA chanels&n; *&t;@device: The SA11x0 peripheral targeted by this request&n; *&t;@device_id: An ascii name for the claiming device&n; *&t;@callback: Function to be called when the DMA completes&n; *&t;@data: A cookie passed back to the callback function&n; *&t;@dma_regs: Pointer to the location of the allocated channel&squot;s identifier&n; *&n; * &t;This function will search for a free DMA channel and returns the&n; * &t;address of the hardware registers for that channel as the channel&n; * &t;identifier. This identifier is written to the location pointed by&n; * &t;@dma_regs. The list of possible values for @device are listed into&n; * &t;linux/include/asm-arm/arch-sa1100/dma.h as a dma_device_t enum.&n; *&n; * &t;Note that reading from a port and writing to the same port are&n; * &t;actually considered as two different streams requiring separate&n; * &t;DMA registrations.&n; *&n; * &t;The @callback function is called from interrupt context when one&n; * &t;of the two possible DMA buffers in flight has terminated. That&n; * &t;function has to be small and efficient while posponing more complex&n; * &t;processing to a lower priority execution context.&n; *&n; * &t;If no channels are available, or if the desired @device is already in&n; * &t;use by another DMA channel, then an error code is returned.  This&n; * &t;function must be called before any other DMA calls.&n; **/
DECL|function|sa1100_request_dma
r_int
id|sa1100_request_dma
(paren
id|dma_device_t
id|device
comma
r_const
r_char
op_star
id|device_id
comma
id|dma_callback_t
id|callback
comma
r_void
op_star
id|data
comma
id|dma_regs_t
op_star
op_star
id|dma_regs
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
id|dma_regs
op_assign
l_int|NULL
suffix:semicolon
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
r_else
r_if
c_cond
(paren
op_logical_neg
id|dma_chan
(braket
id|i
)braket
dot
id|device
op_logical_and
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
id|dma-&gt;device
op_assign
id|device
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
id|i
op_assign
id|dma
op_minus
id|dma_chan
suffix:semicolon
id|regs
op_assign
(paren
id|dma_regs_t
op_star
)paren
op_amp
id|DDAR
c_func
(paren
id|i
)paren
suffix:semicolon
id|err
op_assign
id|request_irq
c_func
(paren
id|IRQ_DMA0
op_plus
id|i
comma
id|dma_irq_handler
comma
id|SA_INTERRUPT
comma
id|device_id
comma
id|regs
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
l_string|&quot;%s: unable to request IRQ %d for %s&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|IRQ_DMA0
op_plus
id|i
comma
id|device_id
)paren
suffix:semicolon
id|dma-&gt;device
op_assign
l_int|0
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
op_star
id|dma_regs
op_assign
id|regs
suffix:semicolon
id|dma-&gt;device_id
op_assign
id|device_id
suffix:semicolon
id|dma-&gt;callback
op_assign
id|callback
suffix:semicolon
id|dma-&gt;data
op_assign
id|data
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
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * &t;sa1100_free_dma - free a SA11x0 DMA channel&n; * &t;@regs: identifier for the channel to free&n; *&n; * &t;This clears all activities on a given DMA channel and releases it&n; * &t;for future requests.  The @regs identifier is provided by a&n; * &t;successful call to sa1100_request_dma().&n; **/
DECL|function|sa1100_free_dma
r_void
id|sa1100_free_dma
c_func
(paren
id|dma_regs_t
op_star
id|regs
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
id|SA1100_DMA_CHANNELS
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|regs
op_eq
(paren
id|dma_regs_t
op_star
)paren
op_amp
id|DDAR
c_func
(paren
id|i
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ge
id|SA1100_DMA_CHANNELS
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: bad DMA identifier&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|dma_chan
(braket
id|i
)braket
dot
id|device
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: Trying to free free DMA&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
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
id|free_irq
c_func
(paren
id|IRQ_DMA0
op_plus
id|i
comma
id|regs
)paren
suffix:semicolon
id|dma_chan
(braket
id|i
)braket
dot
id|device
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * &t;sa1100_start_dma - submit a data buffer for DMA&n; * &t;@regs: identifier for the channel to use&n; * &t;@dma_ptr: buffer physical (or bus) start address&n; * &t;@size: buffer size&n; *&n; * &t;This function hands the given data buffer to the hardware for DMA&n; * &t;access. If another buffer is already in flight then this buffer&n; * &t;will be queued so the DMA engine will switch to it automatically&n; * &t;when the previous one is done.  The DMA engine is actually toggling&n; * &t;between two buffers so at most 2 successful calls can be made before&n; * &t;one of them terminates and the callback function is called.&n; *&n; * &t;The @regs identifier is provided by a successful call to&n; * &t;sa1100_request_dma().&n; *&n; * &t;The @size must not be larger than %MAX_DMA_SIZE.  If a given buffer&n; * &t;is larger than that then it&squot;s the caller&squot;s responsibility to split&n; * &t;it into smaller chunks and submit them separately. If this is the&n; * &t;case then a @size of %CUT_DMA_SIZE is recommended to avoid ending&n; * &t;up with too small chunks. The callback function can be used to chain&n; * &t;submissions of buffer chunks.&n; *&n; * &t;Error return values:&n; * &t;%-EOVERFLOW:&t;Given buffer size is too big.&n; * &t;%-EBUSY:&t;Both DMA buffers are already in use.&n; * &t;%-EAGAIN:&t;Both buffers were busy but one of them just completed&n; * &t;&t;&t;but the interrupt handler has to execute first.&n; *&n; * &t;This function returs 0 on success.&n; **/
DECL|function|sa1100_start_dma
r_int
id|sa1100_start_dma
c_func
(paren
id|dma_regs_t
op_star
id|regs
comma
id|dma_addr_t
id|dma_ptr
comma
id|u_int
id|size
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|u_long
id|status
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|dma_ptr
op_amp
l_int|3
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;DMA: unaligned start address (0x%08lx)&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|dma_ptr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|size
OG
id|MAX_DMA_SIZE
)paren
r_return
op_minus
id|EOVERFLOW
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
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
id|ret
op_assign
op_minus
id|EBUSY
suffix:semicolon
r_goto
id|out
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
id|ret
op_assign
op_minus
id|EAGAIN
suffix:semicolon
r_goto
id|out
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
id|ret
op_assign
op_minus
id|EAGAIN
suffix:semicolon
r_goto
id|out
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
id|ret
op_assign
l_int|0
suffix:semicolon
id|out
suffix:colon
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
multiline_comment|/**&n; * &t;sa1100_get_dma_pos - return current DMA position&n; * &t;@regs: identifier for the channel to use&n; *&n; * &t;This function returns the current physical (or bus) address for the&n; * &t;given DMA channel.  If the channel is running i.e. not in a stopped&n; * &t;state then the caller must disable interrupts prior calling this&n; * &t;function and process the returned value before re-enabling them to&n; * &t;prevent races with the completion interrupt handler and the callback&n; * &t;function. The validation of the returned value is the caller&squot;s&n; * &t;responsibility as well -- the hardware seems to return out of range&n; * &t;values when the DMA engine completes a buffer.&n; *&n; * &t;The @regs identifier is provided by a successful call to&n; * &t;sa1100_request_dma().&n; **/
DECL|function|sa1100_get_dma_pos
id|dma_addr_t
id|sa1100_get_dma_pos
c_func
(paren
id|dma_regs_t
op_star
id|regs
)paren
(brace
r_int
id|status
suffix:semicolon
multiline_comment|/*&n;&t; * We must determine whether buffer A or B is active.&n;&t; * Two possibilities: either we are in the middle of&n;&t; * a buffer, or the DMA controller just switched to the&n;&t; * next toggle but the interrupt hasn&squot;t been serviced yet.&n;&t; * The former case is straight forward.  In the later case,&n;&t; * we&squot;ll do like if DMA is just at the end of the previous&n;&t; * toggle since all registers haven&squot;t been reset yet.&n;&t; * This goes around the edge case and since we&squot;re always&n;&t; * a little behind anyways it shouldn&squot;t make a big difference.&n;&t; * If DMA has been stopped prior calling this then the&n;&t; * position is exact.&n;&t; */
id|status
op_assign
id|regs-&gt;RdDCSR
suffix:semicolon
r_if
c_cond
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
r_return
id|regs-&gt;DBSA
suffix:semicolon
r_else
r_return
id|regs-&gt;DBSB
suffix:semicolon
)brace
multiline_comment|/**&n; * &t;sa1100_reset_dma - reset a DMA channel&n; * &t;@regs: identifier for the channel to use&n; *&n; * &t;This function resets and reconfigure the given DMA channel. This is&n; * &t;particularly useful after a sleep/wakeup event.&n; *&n; * &t;The @regs identifier is provided by a successful call to&n; * &t;sa1100_request_dma().&n; **/
DECL|function|sa1100_reset_dma
r_void
id|sa1100_reset_dma
c_func
(paren
id|dma_regs_t
op_star
id|regs
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
id|SA1100_DMA_CHANNELS
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|regs
op_eq
(paren
id|dma_regs_t
op_star
)paren
op_amp
id|DDAR
c_func
(paren
id|i
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ge
id|SA1100_DMA_CHANNELS
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: bad DMA identifier&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
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
id|dma_chan
(braket
id|i
)braket
dot
id|device
suffix:semicolon
)brace
DECL|variable|sa1100_request_dma
id|EXPORT_SYMBOL
c_func
(paren
id|sa1100_request_dma
)paren
suffix:semicolon
DECL|variable|sa1100_free_dma
id|EXPORT_SYMBOL
c_func
(paren
id|sa1100_free_dma
)paren
suffix:semicolon
DECL|variable|sa1100_start_dma
id|EXPORT_SYMBOL
c_func
(paren
id|sa1100_start_dma
)paren
suffix:semicolon
DECL|variable|sa1100_get_dma_pos
id|EXPORT_SYMBOL
c_func
(paren
id|sa1100_get_dma_pos
)paren
suffix:semicolon
DECL|variable|sa1100_reset_dma
id|EXPORT_SYMBOL
c_func
(paren
id|sa1100_reset_dma
)paren
suffix:semicolon
eof
