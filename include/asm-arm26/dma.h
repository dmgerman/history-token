macro_line|#ifndef __ASM_ARM_DMA_H
DECL|macro|__ASM_ARM_DMA_H
mdefine_line|#define __ASM_ARM_DMA_H
DECL|typedef|dmach_t
r_typedef
r_int
r_int
id|dmach_t
suffix:semicolon
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/memory.h&gt;
macro_line|#include &lt;asm/scatterlist.h&gt;
singleline_comment|// FIXME - do we really need this? arm26 cant do &squot;proper&squot; DMA
DECL|typedef|dma_t
r_typedef
r_struct
id|dma_struct
id|dma_t
suffix:semicolon
DECL|typedef|dmamode_t
r_typedef
r_int
r_int
id|dmamode_t
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
id|dmach_t
comma
id|dma_t
op_star
)paren
suffix:semicolon
multiline_comment|/* optional */
DECL|member|free
r_void
(paren
op_star
id|free
)paren
(paren
id|dmach_t
comma
id|dma_t
op_star
)paren
suffix:semicolon
multiline_comment|/* optional */
DECL|member|enable
r_void
(paren
op_star
id|enable
)paren
(paren
id|dmach_t
comma
id|dma_t
op_star
)paren
suffix:semicolon
multiline_comment|/* mandatory */
DECL|member|disable
r_void
(paren
op_star
id|disable
)paren
(paren
id|dmach_t
comma
id|dma_t
op_star
)paren
suffix:semicolon
multiline_comment|/* mandatory */
DECL|member|residue
r_int
(paren
op_star
id|residue
)paren
(paren
id|dmach_t
comma
id|dma_t
op_star
)paren
suffix:semicolon
multiline_comment|/* optional */
DECL|member|setspeed
r_int
(paren
op_star
id|setspeed
)paren
(paren
id|dmach_t
comma
id|dma_t
op_star
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* optional */
DECL|member|type
r_char
op_star
id|type
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|dma_struct
r_struct
id|dma_struct
(brace
DECL|member|buf
r_struct
id|scatterlist
id|buf
suffix:semicolon
multiline_comment|/* single DMA                   */
DECL|member|sgcount
r_int
id|sgcount
suffix:semicolon
multiline_comment|/* number of DMA SG             */
DECL|member|sg
r_struct
id|scatterlist
op_star
id|sg
suffix:semicolon
multiline_comment|/* DMA Scatter-Gather List      */
DECL|member|active
r_int
r_int
id|active
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Transfer active              */
DECL|member|invalid
r_int
r_int
id|invalid
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Address/Count changed        */
DECL|member|using_sg
r_int
r_int
id|using_sg
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* using scatter list?          */
DECL|member|dma_mode
id|dmamode_t
id|dma_mode
suffix:semicolon
multiline_comment|/* DMA mode                     */
DECL|member|speed
r_int
id|speed
suffix:semicolon
multiline_comment|/* DMA speed                    */
DECL|member|lock
r_int
r_int
id|lock
suffix:semicolon
multiline_comment|/* Device is allocated          */
DECL|member|device_id
r_const
r_char
op_star
id|device_id
suffix:semicolon
multiline_comment|/* Device name                  */
DECL|member|dma_base
r_int
r_int
id|dma_base
suffix:semicolon
multiline_comment|/* Controller base address      */
DECL|member|dma_irq
r_int
id|dma_irq
suffix:semicolon
multiline_comment|/* Controller IRQ               */
DECL|member|state
r_int
id|state
suffix:semicolon
multiline_comment|/* Controller state             */
DECL|member|cur_sg
r_struct
id|scatterlist
id|cur_sg
suffix:semicolon
multiline_comment|/* Current controller buffer    */
DECL|member|d_ops
r_struct
id|dma_ops
op_star
id|d_ops
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Prototype: void arch_dma_init(dma)&n; * Purpose  : Initialise architecture specific DMA&n; * Params   : dma - pointer to array of DMA structures&n; */
r_extern
r_void
id|arch_dma_init
c_func
(paren
id|dma_t
op_star
id|dma
)paren
suffix:semicolon
r_extern
r_void
id|isa_init_dma
c_func
(paren
id|dma_t
op_star
id|dma
)paren
suffix:semicolon
DECL|macro|MAX_DMA_ADDRESS
mdefine_line|#define MAX_DMA_ADDRESS         0x03000000
DECL|macro|MAX_DMA_CHANNELS
mdefine_line|#define MAX_DMA_CHANNELS        3
multiline_comment|/* ARC */
DECL|macro|DMA_VIRTUAL_FLOPPY0
mdefine_line|#define DMA_VIRTUAL_FLOPPY0     0
DECL|macro|DMA_VIRTUAL_FLOPPY1
mdefine_line|#define DMA_VIRTUAL_FLOPPY1     1
DECL|macro|DMA_VIRTUAL_SOUND
mdefine_line|#define DMA_VIRTUAL_SOUND       2
multiline_comment|/* A5K */
DECL|macro|DMA_FLOPPY
mdefine_line|#define DMA_FLOPPY              0
multiline_comment|/*&n; * DMA modes&n; */
DECL|macro|DMA_MODE_MASK
mdefine_line|#define DMA_MODE_MASK&t;3
DECL|macro|DMA_MODE_READ
mdefine_line|#define DMA_MODE_READ&t; 0
DECL|macro|DMA_MODE_WRITE
mdefine_line|#define DMA_MODE_WRITE&t; 1
DECL|macro|DMA_MODE_CASCADE
mdefine_line|#define DMA_MODE_CASCADE 2
DECL|macro|DMA_AUTOINIT
mdefine_line|#define DMA_AUTOINIT&t; 4
r_extern
id|spinlock_t
id|dma_spin_lock
suffix:semicolon
DECL|function|claim_dma_lock
r_static
r_inline
r_int
r_int
id|claim_dma_lock
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|dma_spin_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|flags
suffix:semicolon
)brace
DECL|function|release_dma_lock
r_static
r_inline
r_void
id|release_dma_lock
c_func
(paren
r_int
r_int
id|flags
)paren
(brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|dma_spin_lock
comma
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/* Clear the &squot;DMA Pointer Flip Flop&squot;.&n; * Write 0 for LSB/MSB, 1 for MSB/LSB access.&n; */
DECL|macro|clear_dma_ff
mdefine_line|#define clear_dma_ff(channel)
multiline_comment|/* Set only the page register bits of the transfer address.&n; *&n; * NOTE: This is an architecture specific function, and should&n; *       be hidden from the drivers&n; */
r_extern
r_void
id|set_dma_page
c_func
(paren
id|dmach_t
id|channel
comma
r_char
id|pagenr
)paren
suffix:semicolon
multiline_comment|/* Request a DMA channel&n; *&n; * Some architectures may need to do allocate an interrupt&n; */
r_extern
r_int
id|request_dma
c_func
(paren
id|dmach_t
id|channel
comma
r_const
r_char
op_star
id|device_id
)paren
suffix:semicolon
multiline_comment|/* Free a DMA channel&n; *&n; * Some architectures may need to do free an interrupt&n; */
r_extern
r_void
id|free_dma
c_func
(paren
id|dmach_t
id|channel
)paren
suffix:semicolon
multiline_comment|/* Enable DMA for this channel&n; *&n; * On some architectures, this may have other side effects like&n; * enabling an interrupt and setting the DMA registers.&n; */
r_extern
r_void
id|enable_dma
c_func
(paren
id|dmach_t
id|channel
)paren
suffix:semicolon
multiline_comment|/* Disable DMA for this channel&n; *&n; * On some architectures, this may have other side effects like&n; * disabling an interrupt or whatever.&n; */
r_extern
r_void
id|disable_dma
c_func
(paren
id|dmach_t
id|channel
)paren
suffix:semicolon
multiline_comment|/* Test whether the specified channel has an active DMA transfer&n; */
r_extern
r_int
id|dma_channel_active
c_func
(paren
id|dmach_t
id|channel
)paren
suffix:semicolon
multiline_comment|/* Set the DMA scatter gather list for this channel&n; *&n; * This should not be called if a DMA channel is enabled,&n; * especially since some DMA architectures don&squot;t update the&n; * DMA address immediately, but defer it to the enable_dma().&n; */
r_extern
r_void
id|set_dma_sg
c_func
(paren
id|dmach_t
id|channel
comma
r_struct
id|scatterlist
op_star
id|sg
comma
r_int
id|nr_sg
)paren
suffix:semicolon
multiline_comment|/* Set the DMA address for this channel&n; *&n; * This should not be called if a DMA channel is enabled,&n; * especially since some DMA architectures don&squot;t update the&n; * DMA address immediately, but defer it to the enable_dma().&n; */
r_extern
r_void
id|set_dma_addr
c_func
(paren
id|dmach_t
id|channel
comma
r_int
r_int
id|physaddr
)paren
suffix:semicolon
multiline_comment|/* Set the DMA byte count for this channel&n; *&n; * This should not be called if a DMA channel is enabled,&n; * especially since some DMA architectures don&squot;t update the&n; * DMA count immediately, but defer it to the enable_dma().&n; */
r_extern
r_void
id|set_dma_count
c_func
(paren
id|dmach_t
id|channel
comma
r_int
r_int
id|count
)paren
suffix:semicolon
multiline_comment|/* Set the transfer direction for this channel&n; *&n; * This should not be called if a DMA channel is enabled,&n; * especially since some DMA architectures don&squot;t update the&n; * DMA transfer direction immediately, but defer it to the&n; * enable_dma().&n; */
r_extern
r_void
id|set_dma_mode
c_func
(paren
id|dmach_t
id|channel
comma
id|dmamode_t
id|mode
)paren
suffix:semicolon
multiline_comment|/* Set the transfer speed for this channel&n; */
r_extern
r_void
id|set_dma_speed
c_func
(paren
id|dmach_t
id|channel
comma
r_int
id|cycle_ns
)paren
suffix:semicolon
multiline_comment|/* Get DMA residue count. After a DMA transfer, this&n; * should return zero. Reading this while a DMA transfer is&n; * still in progress will return unpredictable results.&n; * If called before the channel has been used, it may return 1.&n; * Otherwise, it returns the number of _bytes_ left to transfer.&n; */
r_extern
r_int
id|get_dma_residue
c_func
(paren
id|dmach_t
id|channel
)paren
suffix:semicolon
macro_line|#ifndef NO_DMA
DECL|macro|NO_DMA
mdefine_line|#define NO_DMA&t;255
macro_line|#endif
macro_line|#endif /* _ARM_DMA_H */
eof
