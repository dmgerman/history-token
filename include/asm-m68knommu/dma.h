macro_line|#ifndef _M68K_DMA_H
DECL|macro|_M68K_DMA_H
mdefine_line|#define _M68K_DMA_H 1
singleline_comment|//#define&t;DMA_DEBUG&t;1
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_COLDFIRE
multiline_comment|/*&n; * ColdFire DMA Model:&n; *   ColdFire DMA supports two forms of DMA: Single and Dual address. Single&n; * address mode emits a source address, and expects that the device will either&n; * pick up the data (DMA READ) or source data (DMA WRITE). This implies that&n; * the device will place data on the correct byte(s) of the data bus, as the&n; * memory transactions are always 32 bits. This implies that only 32 bit&n; * devices will find single mode transfers useful. Dual address DMA mode&n; * performs two cycles: source read and destination write. ColdFire will&n; * align the data so that the device will always get the correct bytes, thus&n; * is useful for 8 and 16 bit devices. This is the mode that is supported&n; * below.&n; *&n; * AUG/22/2000 : added support for 32-bit Dual-Address-Mode (K) 2000 &n; *               Oliver Kamphenkel (O.Kamphenkel@tu-bs.de)&n; *&n; * AUG/25/2000 : addad support for 8, 16 and 32-bit Single-Address-Mode (K)2000&n; *               Oliver Kamphenkel (O.Kamphenkel@tu-bs.de)&n; *&n; * APR/18/2002 : added proper support for MCF5272 DMA controller.&n; *               Arthur Shipkowski (art@videon-central.com)&n; */
macro_line|#include &lt;asm/coldfire.h&gt;
macro_line|#include &lt;asm/mcfsim.h&gt;
macro_line|#include &lt;asm/mcfdma.h&gt;
multiline_comment|/*&n; * Set number of channels of DMA on ColdFire for different implementations.&n; */
macro_line|#if defined(CONFIG_M5249) || defined(CONFIG_M5307) || defined(CONFIG_M5407)
DECL|macro|MAX_M68K_DMA_CHANNELS
mdefine_line|#define MAX_M68K_DMA_CHANNELS 4
macro_line|#elif defined(CONFIG_M5272)
DECL|macro|MAX_M68K_DMA_CHANNELS
mdefine_line|#define MAX_M68K_DMA_CHANNELS 1
macro_line|#else
DECL|macro|MAX_M68K_DMA_CHANNELS
mdefine_line|#define MAX_M68K_DMA_CHANNELS 2
macro_line|#endif
r_extern
r_int
r_int
id|dma_base_addr
(braket
id|MAX_M68K_DMA_CHANNELS
)braket
suffix:semicolon
r_extern
r_int
r_int
id|dma_device_address
(braket
id|MAX_M68K_DMA_CHANNELS
)braket
suffix:semicolon
macro_line|#if !defined(CONFIG_M5272)
DECL|macro|DMA_MODE_WRITE_BIT
mdefine_line|#define DMA_MODE_WRITE_BIT  0x01  /* Memory/IO to IO/Memory select */
DECL|macro|DMA_MODE_WORD_BIT
mdefine_line|#define DMA_MODE_WORD_BIT   0x02  /* 8 or 16 bit transfers */
DECL|macro|DMA_MODE_LONG_BIT
mdefine_line|#define DMA_MODE_LONG_BIT   0x04  /* or 32 bit transfers */
DECL|macro|DMA_MODE_SINGLE_BIT
mdefine_line|#define DMA_MODE_SINGLE_BIT 0x08  /* single-address-mode */
multiline_comment|/* I/O to memory, 8 bits, mode */
DECL|macro|DMA_MODE_READ
mdefine_line|#define DMA_MODE_READ&t;            0
multiline_comment|/* memory to I/O, 8 bits, mode */
DECL|macro|DMA_MODE_WRITE
mdefine_line|#define DMA_MODE_WRITE&t;            1
multiline_comment|/* I/O to memory, 16 bits, mode */
DECL|macro|DMA_MODE_READ_WORD
mdefine_line|#define DMA_MODE_READ_WORD          2
multiline_comment|/* memory to I/O, 16 bits, mode */
DECL|macro|DMA_MODE_WRITE_WORD
mdefine_line|#define DMA_MODE_WRITE_WORD         3
multiline_comment|/* I/O to memory, 32 bits, mode */
DECL|macro|DMA_MODE_READ_LONG
mdefine_line|#define DMA_MODE_READ_LONG          4
multiline_comment|/* memory to I/O, 32 bits, mode */
DECL|macro|DMA_MODE_WRITE_LONG
mdefine_line|#define DMA_MODE_WRITE_LONG         5
multiline_comment|/* I/O to memory, 8 bits, single-address-mode */
DECL|macro|DMA_MODE_READ_SINGLE
mdefine_line|#define DMA_MODE_READ_SINGLE        8
multiline_comment|/* memory to I/O, 8 bits, single-address-mode */
DECL|macro|DMA_MODE_WRITE_SINGLE
mdefine_line|#define DMA_MODE_WRITE_SINGLE       9
multiline_comment|/* I/O to memory, 16 bits, single-address-mode */
DECL|macro|DMA_MODE_READ_WORD_SINGLE
mdefine_line|#define DMA_MODE_READ_WORD_SINGLE  10
multiline_comment|/* memory to I/O, 16 bits, single-address-mode */
DECL|macro|DMA_MODE_WRITE_WORD_SINGLE
mdefine_line|#define DMA_MODE_WRITE_WORD_SINGLE 11
multiline_comment|/* I/O to memory, 32 bits, single-address-mode */
DECL|macro|DMA_MODE_READ_LONG_SINGLE
mdefine_line|#define DMA_MODE_READ_LONG_SINGLE  12
multiline_comment|/* memory to I/O, 32 bits, single-address-mode */
DECL|macro|DMA_MODE_WRITE_LONG_SINGLE
mdefine_line|#define DMA_MODE_WRITE_LONG_SINGLE 13
macro_line|#else /* CONFIG_M5272 is defined */
multiline_comment|/* Source static-address mode */
DECL|macro|DMA_MODE_SRC_SA_BIT
mdefine_line|#define DMA_MODE_SRC_SA_BIT 0x01  
multiline_comment|/* Two bits to select between all four modes */
DECL|macro|DMA_MODE_SSIZE_MASK
mdefine_line|#define DMA_MODE_SSIZE_MASK 0x06 
multiline_comment|/* Offset to shift bits in */
DECL|macro|DMA_MODE_SSIZE_OFF
mdefine_line|#define DMA_MODE_SSIZE_OFF  0x01  
multiline_comment|/* Destination static-address mode */
DECL|macro|DMA_MODE_DES_SA_BIT
mdefine_line|#define DMA_MODE_DES_SA_BIT 0x10  
multiline_comment|/* Two bits to select between all four modes */
DECL|macro|DMA_MODE_DSIZE_MASK
mdefine_line|#define DMA_MODE_DSIZE_MASK 0x60  
multiline_comment|/* Offset to shift bits in */
DECL|macro|DMA_MODE_DSIZE_OFF
mdefine_line|#define DMA_MODE_DSIZE_OFF  0x05
multiline_comment|/* Size modifiers */
DECL|macro|DMA_MODE_SIZE_LONG
mdefine_line|#define DMA_MODE_SIZE_LONG  0x00
DECL|macro|DMA_MODE_SIZE_BYTE
mdefine_line|#define DMA_MODE_SIZE_BYTE  0x01
DECL|macro|DMA_MODE_SIZE_WORD
mdefine_line|#define DMA_MODE_SIZE_WORD  0x02
DECL|macro|DMA_MODE_SIZE_LINE
mdefine_line|#define DMA_MODE_SIZE_LINE  0x03
multiline_comment|/* &n; * Aliases to help speed quick ports; these may be suboptimal, however. They&n; * do not include the SINGLE mode modifiers since the MCF5272 does not have a&n; * mode where the device is in control of its addressing.&n; */
multiline_comment|/* I/O to memory, 8 bits, mode */
DECL|macro|DMA_MODE_READ
mdefine_line|#define DMA_MODE_READ&t;              ((DMA_MODE_SIZE_BYTE &lt;&lt; DMA_MODE_DSIZE_OFF) | (DMA_MODE_SIZE_BYTE &lt;&lt; DMA_MODE_SSIZE_OFF) | DMA_SRC_SA_BIT)
multiline_comment|/* memory to I/O, 8 bits, mode */
DECL|macro|DMA_MODE_WRITE
mdefine_line|#define DMA_MODE_WRITE&t;            ((DMA_MODE_SIZE_BYTE &lt;&lt; DMA_MODE_DSIZE_OFF) | (DMA_MODE_SIZE_BYTE &lt;&lt; DMA_MODE_SSIZE_OFF) | DMA_DES_SA_BIT)
multiline_comment|/* I/O to memory, 16 bits, mode */
DECL|macro|DMA_MODE_READ_WORD
mdefine_line|#define DMA_MODE_READ_WORD&t;        ((DMA_MODE_SIZE_WORD &lt;&lt; DMA_MODE_DSIZE_OFF) | (DMA_MODE_SIZE_WORD &lt;&lt; DMA_MODE_SSIZE_OFF) | DMA_SRC_SA_BIT)
multiline_comment|/* memory to I/O, 16 bits, mode */
DECL|macro|DMA_MODE_WRITE_WORD
mdefine_line|#define DMA_MODE_WRITE_WORD         ((DMA_MODE_SIZE_WORD &lt;&lt; DMA_MODE_DSIZE_OFF) | (DMA_MODE_SIZE_WORD &lt;&lt; DMA_MODE_SSIZE_OFF) | DMA_DES_SA_BIT)
multiline_comment|/* I/O to memory, 32 bits, mode */
DECL|macro|DMA_MODE_READ_LONG
mdefine_line|#define DMA_MODE_READ_LONG&t;        ((DMA_MODE_SIZE_LONG &lt;&lt; DMA_MODE_DSIZE_OFF) | (DMA_MODE_SIZE_LONG &lt;&lt; DMA_MODE_SSIZE_OFF) | DMA_SRC_SA_BIT)
multiline_comment|/* memory to I/O, 32 bits, mode */
DECL|macro|DMA_MODE_WRITE_LONG
mdefine_line|#define DMA_MODE_WRITE_LONG         ((DMA_MODE_SIZE_LONG &lt;&lt; DMA_MODE_DSIZE_OFF) | (DMA_MODE_SIZE_LONG &lt;&lt; DMA_MODE_SSIZE_OFF) | DMA_DES_SA_BIT)
macro_line|#endif /* !defined(CONFIG_M5272) */
macro_line|#if !defined(CONFIG_M5272)
multiline_comment|/* enable/disable a specific DMA channel */
DECL|function|enable_dma
r_static
id|__inline__
r_void
id|enable_dma
c_func
(paren
r_int
r_int
id|dmanr
)paren
(brace
r_volatile
r_int
r_int
op_star
id|dmawp
suffix:semicolon
macro_line|#ifdef DMA_DEBUG
id|printk
c_func
(paren
l_string|&quot;enable_dma(dmanr=%d)&bslash;n&quot;
comma
id|dmanr
)paren
suffix:semicolon
macro_line|#endif
id|dmawp
op_assign
(paren
r_int
r_int
op_star
)paren
id|dma_base_addr
(braket
id|dmanr
)braket
suffix:semicolon
id|dmawp
(braket
id|MCFDMA_DCR
)braket
op_or_assign
id|MCFDMA_DCR_EEXT
suffix:semicolon
)brace
DECL|function|disable_dma
r_static
id|__inline__
r_void
id|disable_dma
c_func
(paren
r_int
r_int
id|dmanr
)paren
(brace
r_volatile
r_int
r_int
op_star
id|dmawp
suffix:semicolon
r_volatile
r_int
r_char
op_star
id|dmapb
suffix:semicolon
macro_line|#ifdef DMA_DEBUG
id|printk
c_func
(paren
l_string|&quot;disable_dma(dmanr=%d)&bslash;n&quot;
comma
id|dmanr
)paren
suffix:semicolon
macro_line|#endif
id|dmawp
op_assign
(paren
r_int
r_int
op_star
)paren
id|dma_base_addr
(braket
id|dmanr
)braket
suffix:semicolon
id|dmapb
op_assign
(paren
r_int
r_char
op_star
)paren
id|dma_base_addr
(braket
id|dmanr
)braket
suffix:semicolon
multiline_comment|/* Turn off external requests, and stop any DMA in progress */
id|dmawp
(braket
id|MCFDMA_DCR
)braket
op_and_assign
op_complement
id|MCFDMA_DCR_EEXT
suffix:semicolon
id|dmapb
(braket
id|MCFDMA_DSR
)braket
op_assign
id|MCFDMA_DSR_DONE
suffix:semicolon
)brace
multiline_comment|/*&n; * Clear the &squot;DMA Pointer Flip Flop&squot;.&n; * Write 0 for LSB/MSB, 1 for MSB/LSB access.&n; * Use this once to initialize the FF to a known state.&n; * After that, keep track of it. :-)&n; * --- In order to do that, the DMA routines below should ---&n; * --- only be used while interrupts are disabled! ---&n; *&n; * This is a NOP for ColdFire. Provide a stub for compatibility.&n; */
DECL|function|clear_dma_ff
r_static
id|__inline__
r_void
id|clear_dma_ff
c_func
(paren
r_int
r_int
id|dmanr
)paren
(brace
)brace
multiline_comment|/* set mode (above) for a specific DMA channel */
DECL|function|set_dma_mode
r_static
id|__inline__
r_void
id|set_dma_mode
c_func
(paren
r_int
r_int
id|dmanr
comma
r_char
id|mode
)paren
(brace
r_volatile
r_int
r_char
op_star
id|dmabp
suffix:semicolon
r_volatile
r_int
r_int
op_star
id|dmawp
suffix:semicolon
macro_line|#ifdef DMA_DEBUG
id|printk
c_func
(paren
l_string|&quot;set_dma_mode(dmanr=%d,mode=%d)&bslash;n&quot;
comma
id|dmanr
comma
id|mode
)paren
suffix:semicolon
macro_line|#endif
id|dmabp
op_assign
(paren
r_int
r_char
op_star
)paren
id|dma_base_addr
(braket
id|dmanr
)braket
suffix:semicolon
id|dmawp
op_assign
(paren
r_int
r_int
op_star
)paren
id|dma_base_addr
(braket
id|dmanr
)braket
suffix:semicolon
singleline_comment|// Clear config errors
id|dmabp
(braket
id|MCFDMA_DSR
)braket
op_assign
id|MCFDMA_DSR_DONE
suffix:semicolon
singleline_comment|// Set command register
id|dmawp
(braket
id|MCFDMA_DCR
)braket
op_assign
id|MCFDMA_DCR_INT
op_or
singleline_comment|// Enable completion irq
id|MCFDMA_DCR_CS
op_or
singleline_comment|// Force one xfer per request
id|MCFDMA_DCR_AA
op_or
singleline_comment|// Enable auto alignment
singleline_comment|// single-address-mode
(paren
(paren
id|mode
op_amp
id|DMA_MODE_SINGLE_BIT
)paren
ques
c_cond
id|MCFDMA_DCR_SAA
suffix:colon
l_int|0
)paren
op_or
singleline_comment|// sets s_rw (-&gt; r/w) high if Memory to I/0
(paren
(paren
id|mode
op_amp
id|DMA_MODE_WRITE_BIT
)paren
ques
c_cond
id|MCFDMA_DCR_S_RW
suffix:colon
l_int|0
)paren
op_or
singleline_comment|// Memory to I/O or I/O to Memory
(paren
(paren
id|mode
op_amp
id|DMA_MODE_WRITE_BIT
)paren
ques
c_cond
id|MCFDMA_DCR_SINC
suffix:colon
id|MCFDMA_DCR_DINC
)paren
op_or
singleline_comment|// 32 bit, 16 bit or 8 bit transfers
(paren
(paren
id|mode
op_amp
id|DMA_MODE_WORD_BIT
)paren
ques
c_cond
id|MCFDMA_DCR_SSIZE_WORD
suffix:colon
(paren
(paren
id|mode
op_amp
id|DMA_MODE_LONG_BIT
)paren
ques
c_cond
id|MCFDMA_DCR_SSIZE_LONG
suffix:colon
id|MCFDMA_DCR_SSIZE_BYTE
)paren
)paren
op_or
(paren
(paren
id|mode
op_amp
id|DMA_MODE_WORD_BIT
)paren
ques
c_cond
id|MCFDMA_DCR_DSIZE_WORD
suffix:colon
(paren
(paren
id|mode
op_amp
id|DMA_MODE_LONG_BIT
)paren
ques
c_cond
id|MCFDMA_DCR_DSIZE_LONG
suffix:colon
id|MCFDMA_DCR_DSIZE_BYTE
)paren
)paren
suffix:semicolon
macro_line|#ifdef DEBUG_DMA
id|printk
c_func
(paren
l_string|&quot;%s(%d): dmanr=%d DSR[%x]=%x DCR[%x]=%x&bslash;n&quot;
comma
id|__FILE__
comma
id|__LINE__
comma
id|dmanr
comma
(paren
r_int
)paren
op_amp
id|dmabp
(braket
id|MCFDMA_DSR
)braket
comma
id|dmabp
(braket
id|MCFDMA_DSR
)braket
comma
(paren
r_int
)paren
op_amp
id|dmawp
(braket
id|MCFDMA_DCR
)braket
comma
id|dmawp
(braket
id|MCFDMA_DCR
)braket
)paren
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/* Set transfer address for specific DMA channel */
DECL|function|set_dma_addr
r_static
id|__inline__
r_void
id|set_dma_addr
c_func
(paren
r_int
r_int
id|dmanr
comma
r_int
r_int
id|a
)paren
(brace
r_volatile
r_int
r_int
op_star
id|dmawp
suffix:semicolon
r_volatile
r_int
r_int
op_star
id|dmalp
suffix:semicolon
macro_line|#ifdef DMA_DEBUG
id|printk
c_func
(paren
l_string|&quot;set_dma_addr(dmanr=%d,a=%x)&bslash;n&quot;
comma
id|dmanr
comma
id|a
)paren
suffix:semicolon
macro_line|#endif
id|dmawp
op_assign
(paren
r_int
r_int
op_star
)paren
id|dma_base_addr
(braket
id|dmanr
)braket
suffix:semicolon
id|dmalp
op_assign
(paren
r_int
r_int
op_star
)paren
id|dma_base_addr
(braket
id|dmanr
)braket
suffix:semicolon
singleline_comment|// Determine which address registers are used for memory/device accesses
r_if
c_cond
(paren
id|dmawp
(braket
id|MCFDMA_DCR
)braket
op_amp
id|MCFDMA_DCR_SINC
)paren
(brace
singleline_comment|// Source incrementing, must be memory
id|dmalp
(braket
id|MCFDMA_SAR
)braket
op_assign
id|a
suffix:semicolon
singleline_comment|// Set dest address, must be device
id|dmalp
(braket
id|MCFDMA_DAR
)braket
op_assign
id|dma_device_address
(braket
id|dmanr
)braket
suffix:semicolon
)brace
r_else
(brace
singleline_comment|// Destination incrementing, must be memory
id|dmalp
(braket
id|MCFDMA_DAR
)braket
op_assign
id|a
suffix:semicolon
singleline_comment|// Set source address, must be device
id|dmalp
(braket
id|MCFDMA_SAR
)braket
op_assign
id|dma_device_address
(braket
id|dmanr
)braket
suffix:semicolon
)brace
macro_line|#ifdef DEBUG_DMA
id|printk
c_func
(paren
l_string|&quot;%s(%d): dmanr=%d DCR[%x]=%x SAR[%x]=%08x DAR[%x]=%08x&bslash;n&quot;
comma
id|__FILE__
comma
id|__LINE__
comma
id|dmanr
comma
(paren
r_int
)paren
op_amp
id|dmawp
(braket
id|MCFDMA_DCR
)braket
comma
id|dmawp
(braket
id|MCFDMA_DCR
)braket
comma
(paren
r_int
)paren
op_amp
id|dmalp
(braket
id|MCFDMA_SAR
)braket
comma
id|dmalp
(braket
id|MCFDMA_SAR
)braket
comma
(paren
r_int
)paren
op_amp
id|dmalp
(braket
id|MCFDMA_DAR
)braket
comma
id|dmalp
(braket
id|MCFDMA_DAR
)braket
)paren
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/*&n; * Specific for Coldfire - sets device address.&n; * Should be called after the mode set call, and before set DMA address.&n; */
DECL|function|set_dma_device_addr
r_static
id|__inline__
r_void
id|set_dma_device_addr
c_func
(paren
r_int
r_int
id|dmanr
comma
r_int
r_int
id|a
)paren
(brace
macro_line|#ifdef DMA_DEBUG
id|printk
c_func
(paren
l_string|&quot;set_dma_device_addr(dmanr=%d,a=%x)&bslash;n&quot;
comma
id|dmanr
comma
id|a
)paren
suffix:semicolon
macro_line|#endif
id|dma_device_address
(braket
id|dmanr
)braket
op_assign
id|a
suffix:semicolon
)brace
multiline_comment|/*&n; * NOTE 2: &quot;count&quot; represents _bytes_.&n; */
DECL|function|set_dma_count
r_static
id|__inline__
r_void
id|set_dma_count
c_func
(paren
r_int
r_int
id|dmanr
comma
r_int
r_int
id|count
)paren
(brace
r_volatile
r_int
r_int
op_star
id|dmawp
suffix:semicolon
macro_line|#ifdef DMA_DEBUG
id|printk
c_func
(paren
l_string|&quot;set_dma_count(dmanr=%d,count=%d)&bslash;n&quot;
comma
id|dmanr
comma
id|count
)paren
suffix:semicolon
macro_line|#endif
id|dmawp
op_assign
(paren
r_int
r_int
op_star
)paren
id|dma_base_addr
(braket
id|dmanr
)braket
suffix:semicolon
id|dmawp
(braket
id|MCFDMA_BCR
)braket
op_assign
(paren
r_int
r_int
)paren
id|count
suffix:semicolon
)brace
multiline_comment|/*&n; * Get DMA residue count. After a DMA transfer, this&n; * should return zero. Reading this while a DMA transfer is&n; * still in progress will return unpredictable results.&n; * Otherwise, it returns the number of _bytes_ left to transfer.&n; */
DECL|function|get_dma_residue
r_static
id|__inline__
r_int
id|get_dma_residue
c_func
(paren
r_int
r_int
id|dmanr
)paren
(brace
r_volatile
r_int
r_int
op_star
id|dmawp
suffix:semicolon
r_int
r_int
id|count
suffix:semicolon
macro_line|#ifdef DMA_DEBUG
id|printk
c_func
(paren
l_string|&quot;get_dma_residue(dmanr=%d)&bslash;n&quot;
comma
id|dmanr
)paren
suffix:semicolon
macro_line|#endif
id|dmawp
op_assign
(paren
r_int
r_int
op_star
)paren
id|dma_base_addr
(braket
id|dmanr
)braket
suffix:semicolon
id|count
op_assign
id|dmawp
(braket
id|MCFDMA_BCR
)braket
suffix:semicolon
r_return
(paren
r_int
)paren
id|count
suffix:semicolon
)brace
macro_line|#else /* CONFIG_M5272 is defined */
multiline_comment|/*&n; * The MCF5272 DMA controller is very different than the controller defined above&n; * in terms of register mapping.  For instance, with the exception of the 16-bit &n; * interrupt register (IRQ#85, for reference), all of the registers are 32-bit.&n; *&n; * The big difference, however, is the lack of device-requested DMA.  All modes&n; * are dual address transfer, and there is no &squot;device&squot; setup or direction bit.&n; * You can DMA between a device and memory, between memory and memory, or even between&n; * two devices directly, with any combination of incrementing and non-incrementing&n; * addresses you choose.  This puts a crimp in distinguishing between the &squot;device &n; * address&squot; set up by set_dma_device_addr.&n; *&n; * Therefore, there are two options.  One is to use set_dma_addr and set_dma_device_addr,&n; * which will act exactly as above in -- it will look to see if the source is set to&n; * autoincrement, and if so it will make the source use the set_dma_addr value and the&n; * destination the set_dma_device_addr value.  Otherwise the source will be set to the&n; * set_dma_device_addr value and the destination will get the set_dma_addr value.&n; *&n; * The other is to use the provided set_dma_src_addr and set_dma_dest_addr functions&n; * and make it explicit.  Depending on what you&squot;re doing, one of these two should work&n; * for you, but don&squot;t mix them in the same transfer setup.&n; */
multiline_comment|/* enable/disable a specific DMA channel */
DECL|function|enable_dma
r_static
id|__inline__
r_void
id|enable_dma
c_func
(paren
r_int
r_int
id|dmanr
)paren
(brace
r_volatile
r_int
r_int
op_star
id|dmalp
suffix:semicolon
macro_line|#ifdef DMA_DEBUG
id|printk
c_func
(paren
l_string|&quot;enable_dma(dmanr=%d)&bslash;n&quot;
comma
id|dmanr
)paren
suffix:semicolon
macro_line|#endif
id|dmalp
op_assign
(paren
r_int
r_int
op_star
)paren
id|dma_base_addr
(braket
id|dmanr
)braket
suffix:semicolon
id|dmalp
(braket
id|MCFDMA_DMR
)braket
op_or_assign
id|MCFDMA_DMR_EN
suffix:semicolon
)brace
DECL|function|disable_dma
r_static
id|__inline__
r_void
id|disable_dma
c_func
(paren
r_int
r_int
id|dmanr
)paren
(brace
r_volatile
r_int
r_int
op_star
id|dmalp
suffix:semicolon
macro_line|#ifdef DMA_DEBUG
id|printk
c_func
(paren
l_string|&quot;disable_dma(dmanr=%d)&bslash;n&quot;
comma
id|dmanr
)paren
suffix:semicolon
macro_line|#endif
id|dmalp
op_assign
(paren
r_int
r_int
op_star
)paren
id|dma_base_addr
(braket
id|dmanr
)braket
suffix:semicolon
multiline_comment|/* Turn off external requests, and stop any DMA in progress */
id|dmalp
(braket
id|MCFDMA_DMR
)braket
op_and_assign
op_complement
id|MCFDMA_DMR_EN
suffix:semicolon
id|dmalp
(braket
id|MCFDMA_DMR
)braket
op_or_assign
id|MCFDMA_DMR_RESET
suffix:semicolon
)brace
multiline_comment|/*&n; * Clear the &squot;DMA Pointer Flip Flop&squot;.&n; * Write 0 for LSB/MSB, 1 for MSB/LSB access.&n; * Use this once to initialize the FF to a known state.&n; * After that, keep track of it. :-)&n; * --- In order to do that, the DMA routines below should ---&n; * --- only be used while interrupts are disabled! ---&n; *&n; * This is a NOP for ColdFire. Provide a stub for compatibility.&n; */
DECL|function|clear_dma_ff
r_static
id|__inline__
r_void
id|clear_dma_ff
c_func
(paren
r_int
r_int
id|dmanr
)paren
(brace
)brace
multiline_comment|/* set mode (above) for a specific DMA channel */
DECL|function|set_dma_mode
r_static
id|__inline__
r_void
id|set_dma_mode
c_func
(paren
r_int
r_int
id|dmanr
comma
r_char
id|mode
)paren
(brace
r_volatile
r_int
r_int
op_star
id|dmalp
suffix:semicolon
r_volatile
r_int
r_int
op_star
id|dmawp
suffix:semicolon
macro_line|#ifdef DMA_DEBUG
id|printk
c_func
(paren
l_string|&quot;set_dma_mode(dmanr=%d,mode=%d)&bslash;n&quot;
comma
id|dmanr
comma
id|mode
)paren
suffix:semicolon
macro_line|#endif
id|dmalp
op_assign
(paren
r_int
r_int
op_star
)paren
id|dma_base_addr
(braket
id|dmanr
)braket
suffix:semicolon
id|dmawp
op_assign
(paren
r_int
r_int
op_star
)paren
id|dma_base_addr
(braket
id|dmanr
)braket
suffix:semicolon
singleline_comment|// Clear config errors
id|dmalp
(braket
id|MCFDMA_DMR
)braket
op_or_assign
id|MCFDMA_DMR_RESET
suffix:semicolon
singleline_comment|// Set command register
id|dmalp
(braket
id|MCFDMA_DMR
)braket
op_assign
id|MCFDMA_DMR_RQM_DUAL
op_or
singleline_comment|// Mandatory Request Mode setting
id|MCFDMA_DMR_DSTT_SD
op_or
singleline_comment|// Set up addressing types; set to supervisor-data.
id|MCFDMA_DMR_SRCT_SD
op_or
singleline_comment|// Set up addressing types; set to supervisor-data. 
singleline_comment|// source static-address-mode
(paren
(paren
id|mode
op_amp
id|DMA_MODE_SRC_SA_BIT
)paren
ques
c_cond
id|MCFDMA_DMR_SRCM_SA
suffix:colon
id|MCFDMA_DMR_SRCM_IA
)paren
op_or
singleline_comment|// dest static-address-mode
(paren
(paren
id|mode
op_amp
id|DMA_MODE_DES_SA_BIT
)paren
ques
c_cond
id|MCFDMA_DMR_DSTM_SA
suffix:colon
id|MCFDMA_DMR_DSTM_IA
)paren
op_or
singleline_comment|// burst, 32 bit, 16 bit or 8 bit transfers are separately configurable on the MCF5272
(paren
(paren
(paren
id|mode
op_amp
id|DMA_MODE_SSIZE_MASK
)paren
op_rshift
id|DMA_MODE_SSIZE_OFF
)paren
op_lshift
id|MCFDMA_DMR_DSTS_OFF
)paren
op_or
(paren
(paren
(paren
id|mode
op_amp
id|DMA_MODE_SSIZE_MASK
)paren
op_rshift
id|DMA_MODE_SSIZE_OFF
)paren
op_lshift
id|MCFDMA_DMR_SRCS_OFF
)paren
suffix:semicolon
id|dmawp
(braket
id|MCFDMA_DIR
)braket
op_or_assign
id|MCFDMA_DIR_ASCEN
suffix:semicolon
multiline_comment|/* Enable completion interrupts */
macro_line|#ifdef DEBUG_DMA
id|printk
c_func
(paren
l_string|&quot;%s(%d): dmanr=%d DMR[%x]=%x DIR[%x]=%x&bslash;n&quot;
comma
id|__FILE__
comma
id|__LINE__
comma
id|dmanr
comma
(paren
r_int
)paren
op_amp
id|dmalp
(braket
id|MCFDMA_DMR
)braket
comma
id|dmabp
(braket
id|MCFDMA_DMR
)braket
comma
(paren
r_int
)paren
op_amp
id|dmawp
(braket
id|MCFDMA_DIR
)braket
comma
id|dmawp
(braket
id|MCFDMA_DIR
)braket
)paren
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/* Set transfer address for specific DMA channel */
DECL|function|set_dma_addr
r_static
id|__inline__
r_void
id|set_dma_addr
c_func
(paren
r_int
r_int
id|dmanr
comma
r_int
r_int
id|a
)paren
(brace
r_volatile
r_int
r_int
op_star
id|dmalp
suffix:semicolon
macro_line|#ifdef DMA_DEBUG
id|printk
c_func
(paren
l_string|&quot;set_dma_addr(dmanr=%d,a=%x)&bslash;n&quot;
comma
id|dmanr
comma
id|a
)paren
suffix:semicolon
macro_line|#endif
id|dmalp
op_assign
(paren
r_int
r_int
op_star
)paren
id|dma_base_addr
(braket
id|dmanr
)braket
suffix:semicolon
singleline_comment|// Determine which address registers are used for memory/device accesses
r_if
c_cond
(paren
id|dmalp
(braket
id|MCFDMA_DMR
)braket
op_amp
id|MCFDMA_DMR_SRCM
)paren
(brace
singleline_comment|// Source incrementing, must be memory
id|dmalp
(braket
id|MCFDMA_DSAR
)braket
op_assign
id|a
suffix:semicolon
singleline_comment|// Set dest address, must be device
id|dmalp
(braket
id|MCFDMA_DDAR
)braket
op_assign
id|dma_device_address
(braket
id|dmanr
)braket
suffix:semicolon
)brace
r_else
(brace
singleline_comment|// Destination incrementing, must be memory
id|dmalp
(braket
id|MCFDMA_DDAR
)braket
op_assign
id|a
suffix:semicolon
singleline_comment|// Set source address, must be device
id|dmalp
(braket
id|MCFDMA_DSAR
)braket
op_assign
id|dma_device_address
(braket
id|dmanr
)braket
suffix:semicolon
)brace
macro_line|#ifdef DEBUG_DMA
id|printk
c_func
(paren
l_string|&quot;%s(%d): dmanr=%d DMR[%x]=%x SAR[%x]=%08x DAR[%x]=%08x&bslash;n&quot;
comma
id|__FILE__
comma
id|__LINE__
comma
id|dmanr
comma
(paren
r_int
)paren
op_amp
id|dmawp
(braket
id|MCFDMA_DMR
)braket
comma
id|dmawp
(braket
id|MCFDMA_DMR
)braket
comma
(paren
r_int
)paren
op_amp
id|dmalp
(braket
id|MCFDMA_DSAR
)braket
comma
id|dmalp
(braket
id|MCFDMA_DSAR
)braket
comma
(paren
r_int
)paren
op_amp
id|dmalp
(braket
id|MCFDMA_DDAR
)braket
comma
id|dmalp
(braket
id|MCFDMA_DDAR
)braket
)paren
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/*&n; * Specific for Coldfire - sets device address.&n; * Should be called after the mode set call, and before set DMA address.&n; */
DECL|function|set_dma_device_addr
r_static
id|__inline__
r_void
id|set_dma_device_addr
c_func
(paren
r_int
r_int
id|dmanr
comma
r_int
r_int
id|a
)paren
(brace
macro_line|#ifdef DMA_DEBUG
id|printk
c_func
(paren
l_string|&quot;set_dma_device_addr(dmanr=%d,a=%x)&bslash;n&quot;
comma
id|dmanr
comma
id|a
)paren
suffix:semicolon
macro_line|#endif
id|dma_device_address
(braket
id|dmanr
)braket
op_assign
id|a
suffix:semicolon
)brace
multiline_comment|/*&n; * NOTE 2: &quot;count&quot; represents _bytes_.&n; *&n; * NOTE 3: While a 32-bit register, &quot;count&quot; is only a maximum 24-bit value.&n; */
DECL|function|set_dma_count
r_static
id|__inline__
r_void
id|set_dma_count
c_func
(paren
r_int
r_int
id|dmanr
comma
r_int
r_int
id|count
)paren
(brace
r_volatile
r_int
r_int
op_star
id|dmalp
suffix:semicolon
macro_line|#ifdef DMA_DEBUG
id|printk
c_func
(paren
l_string|&quot;set_dma_count(dmanr=%d,count=%d)&bslash;n&quot;
comma
id|dmanr
comma
id|count
)paren
suffix:semicolon
macro_line|#endif
id|dmalp
op_assign
(paren
r_int
r_int
op_star
)paren
id|dma_base_addr
(braket
id|dmanr
)braket
suffix:semicolon
id|dmalp
(braket
id|MCFDMA_DBCR
)braket
op_assign
id|count
suffix:semicolon
)brace
multiline_comment|/*&n; * Get DMA residue count. After a DMA transfer, this&n; * should return zero. Reading this while a DMA transfer is&n; * still in progress will return unpredictable results.&n; * Otherwise, it returns the number of _bytes_ left to transfer.&n; */
DECL|function|get_dma_residue
r_static
id|__inline__
r_int
id|get_dma_residue
c_func
(paren
r_int
r_int
id|dmanr
)paren
(brace
r_volatile
r_int
r_int
op_star
id|dmalp
suffix:semicolon
r_int
r_int
id|count
suffix:semicolon
macro_line|#ifdef DMA_DEBUG
id|printk
c_func
(paren
l_string|&quot;get_dma_residue(dmanr=%d)&bslash;n&quot;
comma
id|dmanr
)paren
suffix:semicolon
macro_line|#endif
id|dmalp
op_assign
(paren
r_int
r_int
op_star
)paren
id|dma_base_addr
(braket
id|dmanr
)braket
suffix:semicolon
id|count
op_assign
id|dmalp
(braket
id|MCFDMA_DBCR
)braket
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
macro_line|#endif /* !defined(CONFIG_M5272) */
macro_line|#endif /* CONFIG_COLDFIRE */
DECL|macro|MAX_DMA_CHANNELS
mdefine_line|#define MAX_DMA_CHANNELS 8
multiline_comment|/* Don&squot;t define MAX_DMA_ADDRESS; it&squot;s useless on the m68k/coldfire and any&n;   occurrence should be flagged as an error.  */
multiline_comment|/* under 2.4 it is actually needed by the new bootmem allocator */
DECL|macro|MAX_DMA_ADDRESS
mdefine_line|#define MAX_DMA_ADDRESS PAGE_OFFSET
multiline_comment|/* These are in kernel/dma.c: */
r_extern
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
suffix:semicolon
multiline_comment|/* reserve a DMA channel */
r_extern
r_void
id|free_dma
c_func
(paren
r_int
r_int
id|dmanr
)paren
suffix:semicolon
multiline_comment|/* release it again */
macro_line|#endif /* _M68K_DMA_H */
eof
