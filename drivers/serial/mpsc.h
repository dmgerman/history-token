multiline_comment|/*&n; * drivers/serial/mpsc.h&n; *&n; * Author: Mark A. Greer &lt;mgreer@mvista.com&gt;&n; *&n; * 2004 (c) MontaVista, Software, Inc.  This file is licensed under&n; * the terms of the GNU General Public License version 2.  This program&n; * is licensed &quot;as is&quot; without any warranty of any kind, whether express&n; * or implied.&n; */
macro_line|#ifndef&t;__MPSC_H__
DECL|macro|__MPSC_H__
mdefine_line|#define&t;__MPSC_H__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/moduleparam.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/tty_flip.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/sysrq.h&gt;
macro_line|#include &lt;linux/serial.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/dma-mapping.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#if defined(CONFIG_SERIAL_MPSC_CONSOLE) &amp;&amp; defined(CONFIG_MAGIC_SYSRQ)
DECL|macro|SUPPORT_SYSRQ
mdefine_line|#define SUPPORT_SYSRQ
macro_line|#endif
macro_line|#include &lt;linux/serial_core.h&gt;
macro_line|#include &quot;mpsc_defs.h&quot;
multiline_comment|/*&n; * Descriptors and buffers must be cache line aligned.&n; * Buffers lengths must be multiple of cache line size.&n; * Number of Tx &amp; Rx descriptors must be powers of 2.&n; */
DECL|macro|MPSC_RXR_ENTRIES
mdefine_line|#define&t;MPSC_RXR_ENTRIES&t;32
DECL|macro|MPSC_RXRE_SIZE
mdefine_line|#define&t;MPSC_RXRE_SIZE&t;&t;dma_get_cache_alignment()
DECL|macro|MPSC_RXR_SIZE
mdefine_line|#define&t;MPSC_RXR_SIZE&t;&t;(MPSC_RXR_ENTRIES * MPSC_RXRE_SIZE)
DECL|macro|MPSC_RXBE_SIZE
mdefine_line|#define&t;MPSC_RXBE_SIZE&t;&t;dma_get_cache_alignment()
DECL|macro|MPSC_RXB_SIZE
mdefine_line|#define&t;MPSC_RXB_SIZE&t;&t;(MPSC_RXR_ENTRIES * MPSC_RXBE_SIZE)
DECL|macro|MPSC_TXR_ENTRIES
mdefine_line|#define&t;MPSC_TXR_ENTRIES&t;32
DECL|macro|MPSC_TXRE_SIZE
mdefine_line|#define&t;MPSC_TXRE_SIZE&t;&t;dma_get_cache_alignment()
DECL|macro|MPSC_TXR_SIZE
mdefine_line|#define&t;MPSC_TXR_SIZE&t;&t;(MPSC_TXR_ENTRIES * MPSC_TXRE_SIZE)
DECL|macro|MPSC_TXBE_SIZE
mdefine_line|#define&t;MPSC_TXBE_SIZE&t;&t;dma_get_cache_alignment()
DECL|macro|MPSC_TXB_SIZE
mdefine_line|#define&t;MPSC_TXB_SIZE&t;&t;(MPSC_TXR_ENTRIES * MPSC_TXBE_SIZE)
DECL|macro|MPSC_DMA_ALLOC_SIZE
mdefine_line|#define&t;MPSC_DMA_ALLOC_SIZE&t;(MPSC_RXR_SIZE + MPSC_RXB_SIZE +&t;&bslash;&n;&t;&t;&t;&t;MPSC_TXR_SIZE + MPSC_TXB_SIZE +&t;&t;&bslash;&n;&t;&t;&t;&t;dma_get_cache_alignment() /* for alignment */)
multiline_comment|/* Rx and Tx Ring entry descriptors -- assume entry size is &lt;= cacheline size */
DECL|struct|mpsc_rx_desc
r_struct
id|mpsc_rx_desc
(brace
DECL|member|bufsize
id|u16
id|bufsize
suffix:semicolon
DECL|member|bytecnt
id|u16
id|bytecnt
suffix:semicolon
DECL|member|cmdstat
id|u32
id|cmdstat
suffix:semicolon
DECL|member|link
id|u32
id|link
suffix:semicolon
DECL|member|buf_ptr
id|u32
id|buf_ptr
suffix:semicolon
)brace
id|__attribute
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|mpsc_tx_desc
r_struct
id|mpsc_tx_desc
(brace
DECL|member|bytecnt
id|u16
id|bytecnt
suffix:semicolon
DECL|member|shadow
id|u16
id|shadow
suffix:semicolon
DECL|member|cmdstat
id|u32
id|cmdstat
suffix:semicolon
DECL|member|link
id|u32
id|link
suffix:semicolon
DECL|member|buf_ptr
id|u32
id|buf_ptr
suffix:semicolon
)brace
id|__attribute
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/*&n; * Some regs that have the erratum that you can&squot;t read them are are shared&n; * between the two MPSC controllers.  This struct contains those shared regs.&n; */
DECL|struct|mpsc_shared_regs
r_struct
id|mpsc_shared_regs
(brace
DECL|member|mpsc_routing_base_p
id|u32
id|mpsc_routing_base_p
suffix:semicolon
DECL|member|sdma_intr_base_p
id|u32
id|sdma_intr_base_p
suffix:semicolon
DECL|member|mpsc_routing_base
id|u32
id|mpsc_routing_base
suffix:semicolon
DECL|member|sdma_intr_base
id|u32
id|sdma_intr_base
suffix:semicolon
DECL|member|MPSC_MRR_m
id|u32
id|MPSC_MRR_m
suffix:semicolon
DECL|member|MPSC_RCRR_m
id|u32
id|MPSC_RCRR_m
suffix:semicolon
DECL|member|MPSC_TCRR_m
id|u32
id|MPSC_TCRR_m
suffix:semicolon
DECL|member|SDMA_INTR_CAUSE_m
id|u32
id|SDMA_INTR_CAUSE_m
suffix:semicolon
DECL|member|SDMA_INTR_MASK_m
id|u32
id|SDMA_INTR_MASK_m
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* The main driver data structure */
DECL|struct|mpsc_port_info
r_struct
id|mpsc_port_info
(brace
DECL|member|port
r_struct
id|uart_port
id|port
suffix:semicolon
multiline_comment|/* Overlay uart_port structure */
multiline_comment|/* Internal driver state for this ctlr */
DECL|member|ready
id|u8
id|ready
suffix:semicolon
DECL|member|rcv_data
id|u8
id|rcv_data
suffix:semicolon
DECL|member|c_iflag
id|tcflag_t
id|c_iflag
suffix:semicolon
multiline_comment|/* save termios-&gt;c_iflag */
DECL|member|c_cflag
id|tcflag_t
id|c_cflag
suffix:semicolon
multiline_comment|/* save termios-&gt;c_cflag */
multiline_comment|/* Info passed in from platform */
DECL|member|mirror_regs
id|u8
id|mirror_regs
suffix:semicolon
multiline_comment|/* Need to mirror regs? */
DECL|member|cache_mgmt
id|u8
id|cache_mgmt
suffix:semicolon
multiline_comment|/* Need manual cache mgmt? */
DECL|member|brg_can_tune
id|u8
id|brg_can_tune
suffix:semicolon
multiline_comment|/* BRG has baud tuning? */
DECL|member|brg_clk_src
id|u32
id|brg_clk_src
suffix:semicolon
DECL|member|mpsc_max_idle
id|u16
id|mpsc_max_idle
suffix:semicolon
DECL|member|default_baud
r_int
id|default_baud
suffix:semicolon
DECL|member|default_bits
r_int
id|default_bits
suffix:semicolon
DECL|member|default_parity
r_int
id|default_parity
suffix:semicolon
DECL|member|default_flow
r_int
id|default_flow
suffix:semicolon
multiline_comment|/* Physical addresses of various blocks of registers (from platform) */
DECL|member|mpsc_base_p
id|u32
id|mpsc_base_p
suffix:semicolon
DECL|member|sdma_base_p
id|u32
id|sdma_base_p
suffix:semicolon
DECL|member|brg_base_p
id|u32
id|brg_base_p
suffix:semicolon
multiline_comment|/* Virtual addresses of various blocks of registers (from platform) */
DECL|member|mpsc_base
id|u32
id|mpsc_base
suffix:semicolon
DECL|member|sdma_base
id|u32
id|sdma_base
suffix:semicolon
DECL|member|brg_base
id|u32
id|brg_base
suffix:semicolon
multiline_comment|/* Descriptor ring and buffer allocations */
DECL|member|dma_region
r_void
op_star
id|dma_region
suffix:semicolon
DECL|member|dma_region_p
id|dma_addr_t
id|dma_region_p
suffix:semicolon
DECL|member|rxr
id|dma_addr_t
id|rxr
suffix:semicolon
multiline_comment|/* Rx descriptor ring */
DECL|member|rxr_p
id|dma_addr_t
id|rxr_p
suffix:semicolon
multiline_comment|/* Phys addr of rxr */
DECL|member|rxb
id|u8
op_star
id|rxb
suffix:semicolon
multiline_comment|/* Rx Ring I/O buf */
DECL|member|rxb_p
id|u8
op_star
id|rxb_p
suffix:semicolon
multiline_comment|/* Phys addr of rxb */
DECL|member|rxr_posn
id|u32
id|rxr_posn
suffix:semicolon
multiline_comment|/* First desc w/ Rx data */
DECL|member|txr
id|dma_addr_t
id|txr
suffix:semicolon
multiline_comment|/* Tx descriptor ring */
DECL|member|txr_p
id|dma_addr_t
id|txr_p
suffix:semicolon
multiline_comment|/* Phys addr of txr */
DECL|member|txb
id|u8
op_star
id|txb
suffix:semicolon
multiline_comment|/* Tx Ring I/O buf */
DECL|member|txb_p
id|u8
op_star
id|txb_p
suffix:semicolon
multiline_comment|/* Phys addr of txb */
DECL|member|txr_head
r_int
id|txr_head
suffix:semicolon
multiline_comment|/* Where new data goes */
DECL|member|txr_tail
r_int
id|txr_tail
suffix:semicolon
multiline_comment|/* Where sent data comes off */
multiline_comment|/* Mirrored values of regs we can&squot;t read (if &squot;mirror_regs&squot; set) */
DECL|member|MPSC_MPCR_m
id|u32
id|MPSC_MPCR_m
suffix:semicolon
DECL|member|MPSC_CHR_1_m
id|u32
id|MPSC_CHR_1_m
suffix:semicolon
DECL|member|MPSC_CHR_2_m
id|u32
id|MPSC_CHR_2_m
suffix:semicolon
DECL|member|MPSC_CHR_10_m
id|u32
id|MPSC_CHR_10_m
suffix:semicolon
DECL|member|BRG_BCR_m
id|u32
id|BRG_BCR_m
suffix:semicolon
DECL|member|shared_regs
r_struct
id|mpsc_shared_regs
op_star
id|shared_regs
suffix:semicolon
)brace
suffix:semicolon
macro_line|#if defined(CONFIG_PPC32)
macro_line|#if defined(CONFIG_NOT_COHERENT_CACHE)
multiline_comment|/* No-ops when coherency is off b/c dma_cache_sync() does that work */
DECL|macro|MPSC_CACHE_INVALIDATE
mdefine_line|#define&t;MPSC_CACHE_INVALIDATE(pi, s, e)
DECL|macro|MPSC_CACHE_FLUSH
mdefine_line|#define&t;MPSC_CACHE_FLUSH(pi, s, e)
macro_line|#else /* defined(CONFIG_NOT_COHERENT_CACHE) */
multiline_comment|/* Coherency is on so dma_cache_sync() is no-op so must do manually */
DECL|macro|MPSC_CACHE_INVALIDATE
mdefine_line|#define&t;MPSC_CACHE_INVALIDATE(pi, s, e) {&t;&t;&t;&bslash;&n;&t;if (pi-&gt;cache_mgmt) {&t;&t;&t;&t;&t;&bslash;&n;&t;&t;invalidate_dcache_range((ulong)s, (ulong)e);&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;}
DECL|macro|MPSC_CACHE_FLUSH
mdefine_line|#define&t;MPSC_CACHE_FLUSH(pi, s, e) {&t;&t;&t;&bslash;&n;&t;if (pi-&gt;cache_mgmt) {&t;&t;&t;&t;&bslash;&n;&t;&t;flush_dcache_range((ulong)s, (ulong)e);&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&bslash;&n;}
macro_line|#endif /* defined(CONFIG_NOT_COHERENT_CACHE) */
macro_line|#else /* defined(CONFIG_PPC32) */
multiline_comment|/* Other architectures need to fill this in */
DECL|macro|MPSC_CACHE_INVALIDATE
mdefine_line|#define&t;MPSC_CACHE_INVALIDATE(pi, s, e)&t;BUG()
DECL|macro|MPSC_CACHE_FLUSH
mdefine_line|#define&t;MPSC_CACHE_FLUSH(pi, s, e)&t;BUG()
macro_line|#endif /* defined(CONFIG_PPC32) */
multiline_comment|/*&n; * &squot;MASK_INSERT&squot; takes the low-order &squot;n&squot; bits of &squot;i&squot;, shifts it &squot;b&squot; bits to&n; * the left, and inserts it into the target &squot;t&squot;.  The corresponding bits in&n; * &squot;t&squot; will have been cleared before the bits in &squot;i&squot; are inserted.&n; */
macro_line|#ifdef CONFIG_PPC32
DECL|macro|MASK_INSERT
mdefine_line|#define MASK_INSERT(t, i, n, b) ({&t;&t;&t;&t;&bslash;&n;&t;u32&t;rval = (t);&t;&t;&t;&t;&t;&bslash;&n;        __asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;rlwimi %0,%2,%4,32-(%3+%4),31-%4&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;: &quot;=r&quot; (rval)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;0&quot; (rval), &quot;r&quot; (i), &quot;i&quot; (n), &quot;i&quot; (b));&t;&bslash;&n;&t;rval;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
macro_line|#else
multiline_comment|/* These macros are really just examples.  Feel free to change them --MAG */
DECL|macro|GEN_MASK
mdefine_line|#define GEN_MASK(n, b)&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&bslash;&n;&t;u32&t;m, sl, sr;&t;&t;&bslash;&n;&t;sl = 32 - (n);&t;&t;&t;&bslash;&n;&t;sr = sl - (b);&t;&t;&t;&bslash;&n;&t;m = (0xffffffff &lt;&lt; sl) &gt;&gt; sr;&t;&bslash;&n;})
DECL|macro|MASK_INSERT
mdefine_line|#define MASK_INSERT(t, i, n, b)&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&bslash;&n;&t;u32&t;m, rval = (t);&t;&t;&bslash;&n;&t;m = GEN_MASK((n), (b));&t;&t;&bslash;&n;&t;rval &amp;= ~m;&t;&t;&t;&bslash;&n;&t;rval |= (((i) &lt;&lt; (b)) &amp; m);&t;&bslash;&n;})
macro_line|#endif
multiline_comment|/* I/O macros for regs that you can read */
DECL|macro|MPSC_READ
mdefine_line|#define&t;MPSC_READ(pi, unit, offset)&t;&t;&t;&t;&t;&bslash;&n;&t;readl((volatile void *)((pi)-&gt;unit##_base + (offset)))
DECL|macro|MPSC_WRITE
mdefine_line|#define&t;MPSC_WRITE(pi, unit, offset, v)&t;&t;&t;&t;&t;&bslash;&n;&t;writel(v, (volatile void *)((pi)-&gt;unit##_base + (offset)))
DECL|macro|MPSC_MOD_FIELD
mdefine_line|#define&t;MPSC_MOD_FIELD(pi, unit, offset, num_bits, shift, val)&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;u32&t;v;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;v = readl((volatile void *)((pi)-&gt;unit##_base + (offset)));&t;&bslash;&n;&t;writel(MASK_INSERT(v,val,num_bits,shift),&t;&t;&t;&bslash;&n;&t;&t;(volatile void *)((pi)-&gt;unit##_base+(offset)));&t;&t;&bslash;&n;}
multiline_comment|/* Macros for regs with erratum that are not shared between MPSC ctlrs */
DECL|macro|MPSC_READ_M
mdefine_line|#define&t;MPSC_READ_M(pi, unit, offset)&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;u32&t;v;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if ((pi)-&gt;mirror_regs) v = (pi)-&gt;offset##_m;&t;&t;&t;&bslash;&n;&t;else v = readl((volatile void *)((pi)-&gt;unit##_base + (offset)));&bslash;&n;&t;v;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|MPSC_WRITE_M
mdefine_line|#define&t;MPSC_WRITE_M(pi, unit, offset, v)&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if ((pi)-&gt;mirror_regs) (pi)-&gt;offset##_m = v;&t;&t;&t;&bslash;&n;&t;writel(v, (volatile void *)((pi)-&gt;unit##_base + (offset)));&t;&bslash;&n;})
DECL|macro|MPSC_MOD_FIELD_M
mdefine_line|#define&t;MPSC_MOD_FIELD_M(pi, unit, offset, num_bits, shift, val)&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;u32&t;v;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if ((pi)-&gt;mirror_regs) v = (pi)-&gt;offset##_m;&t;&t;&t;&bslash;&n;&t;else v = readl((volatile void *)((pi)-&gt;unit##_base + (offset)));&bslash;&n;&t;v = MASK_INSERT(v, val, num_bits, shift);&t;&t;&t;&bslash;&n;&t;if ((pi)-&gt;mirror_regs) (pi)-&gt;offset##_m = v;&t;&t;&t;&bslash;&n;&t;writel(v, (volatile void *)((pi)-&gt;unit##_base + (offset)));&t;&bslash;&n;})
multiline_comment|/* Macros for regs with erratum that are shared between MPSC ctlrs */
DECL|macro|MPSC_READ_S
mdefine_line|#define&t;MPSC_READ_S(pi, unit, offset)&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;u32&t;v;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if ((pi)-&gt;mirror_regs) v = (pi)-&gt;shared_regs-&gt;offset##_m;&t;&bslash;&n;&t;else v = readl((volatile void *)((pi)-&gt;shared_regs-&gt;unit##_base + &bslash;&n;&t;&t;(offset)));&t;&t;&t;&t;&t;&t;&bslash;&n;&t;v;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|MPSC_WRITE_S
mdefine_line|#define&t;MPSC_WRITE_S(pi, unit, offset, v)&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if ((pi)-&gt;mirror_regs) (pi)-&gt;shared_regs-&gt;offset##_m = v;&t;&bslash;&n;&t;writel(v, (volatile void *)((pi)-&gt;shared_regs-&gt;unit##_base +&t;&bslash;&n;&t;&t;(offset)));&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|MPSC_MOD_FIELD_S
mdefine_line|#define&t;MPSC_MOD_FIELD_S(pi, unit, offset, num_bits, shift, val)&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;u32&t;v;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if ((pi)-&gt;mirror_regs) v = (pi)-&gt;shared_regs-&gt;offset##_m;&t;&bslash;&n;&t;else v = readl((volatile void *)((pi)-&gt;shared_regs-&gt;unit##_base + &bslash;&n;&t;&t;(offset)));&t;&t;&t;&t;&t;&t;&bslash;&n;&t;v = MASK_INSERT(v, val, num_bits, shift);&t;&t;&t;&bslash;&n;&t;if ((pi)-&gt;mirror_regs) (pi)-&gt;shared_regs-&gt;offset##_m = v;&t;&bslash;&n;&t;writel(v, (volatile void *)((pi)-&gt;shared_regs-&gt;unit##_base +&t;&bslash;&n;&t;&t;(offset)));&t;&t;&t;&t;&t;&t;&bslash;&n;})
multiline_comment|/* Hooks to platform-specific code */
r_int
id|mpsc_platform_register_driver
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|mpsc_platform_unregister_driver
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Hooks back in to mpsc common to be called by platform-specific code */
r_struct
id|mpsc_port_info
op_star
id|mpsc_device_probe
c_func
(paren
r_int
id|index
)paren
suffix:semicolon
r_struct
id|mpsc_port_info
op_star
id|mpsc_device_remove
c_func
(paren
r_int
id|index
)paren
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* __MPSC_H__ */
eof
