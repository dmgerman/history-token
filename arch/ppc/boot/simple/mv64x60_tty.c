multiline_comment|/*&n; * arch/ppc/boot/simple/mv64x60_tty.c&n; *&n; * Bootloader version of the embedded MPSC/UART driver for the Marvell 64x60.&n; * Note: Due to a GT64260A erratum, DMA will be used for UART input (via SDMA).&n; *&n; * Author: Mark A. Greer &lt;mgreer@mvista.com&gt;&n; *&n; * 2001 (c) MontaVista Software, Inc. This file is licensed under&n; * the terms of the GNU General Public License version 2. This program&n; * is licensed &quot;as is&quot; without any warranty of any kind, whether express&n; * or implied.&n; */
multiline_comment|/* This code assumes that the data cache has been disabled (L1, L2, L3). */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/serial_reg.h&gt;
macro_line|#include &lt;asm/serial.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/mv64x60_defs.h&gt;
macro_line|#include &lt;mpsc_defs.h&gt;
DECL|variable|mv64x60_console_baud
id|u32
id|mv64x60_console_baud
op_assign
l_int|9600
suffix:semicolon
DECL|variable|mv64x60_mpsc_clk_src
id|u32
id|mv64x60_mpsc_clk_src
op_assign
l_int|8
suffix:semicolon
multiline_comment|/* TCLK */
DECL|variable|mv64x60_mpsc_clk_freq
id|u32
id|mv64x60_mpsc_clk_freq
op_assign
l_int|100000000
suffix:semicolon
r_extern
r_void
id|udelay
c_func
(paren
r_int
)paren
suffix:semicolon
r_static
r_void
id|stop_dma
c_func
(paren
r_int
id|chan
)paren
suffix:semicolon
DECL|variable|mv64x60_base
r_static
r_void
id|__iomem
op_star
id|mv64x60_base
op_assign
(paren
r_void
id|__iomem
op_star
)paren
id|CONFIG_MV64X60_NEW_BASE
suffix:semicolon
DECL|struct|sdma_regs
r_struct
id|sdma_regs
(brace
DECL|member|sdc
id|u32
id|sdc
suffix:semicolon
DECL|member|sdcm
id|u32
id|sdcm
suffix:semicolon
DECL|member|rx_desc
id|u32
id|rx_desc
suffix:semicolon
DECL|member|rx_buf_ptr
id|u32
id|rx_buf_ptr
suffix:semicolon
DECL|member|scrdp
id|u32
id|scrdp
suffix:semicolon
DECL|member|tx_desc
id|u32
id|tx_desc
suffix:semicolon
DECL|member|sctdp
id|u32
id|sctdp
suffix:semicolon
DECL|member|sftdp
id|u32
id|sftdp
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|sdma_regs
r_static
r_struct
id|sdma_regs
id|sdma_regs
(braket
l_int|2
)braket
suffix:semicolon
DECL|macro|SDMA_REGS_INIT
mdefine_line|#define&t;SDMA_REGS_INIT(s, reg_base) {&t;&t;&t;&bslash;&n;&t;(s)-&gt;sdc&t;= (reg_base) + SDMA_SDC;&t;&bslash;&n;&t;(s)-&gt;sdcm&t;= (reg_base) + SDMA_SDCM;&t;&bslash;&n;&t;(s)-&gt;rx_desc&t;= (reg_base) + SDMA_RX_DESC;&t;&bslash;&n;&t;(s)-&gt;rx_buf_ptr = (reg_base) + SDMA_RX_BUF_PTR;&t;&bslash;&n;&t;(s)-&gt;scrdp&t;= (reg_base) + SDMA_SCRDP;&t;&bslash;&n;&t;(s)-&gt;tx_desc&t;= (reg_base) + SDMA_TX_DESC;&t;&bslash;&n;&t;(s)-&gt;sctdp&t;= (reg_base) + SDMA_SCTDP;&t;&bslash;&n;&t;(s)-&gt;sftdp&t;= (reg_base) + SDMA_SFTDP;&t;&bslash;&n;}
DECL|variable|mpsc_base
r_static
id|u32
id|mpsc_base
(braket
l_int|2
)braket
op_assign
(brace
id|MV64x60_MPSC_0_OFFSET
comma
id|MV64x60_MPSC_1_OFFSET
)brace
suffix:semicolon
DECL|struct|mv64x60_rx_desc
r_struct
id|mv64x60_rx_desc
(brace
DECL|member|bufsize
id|u16
id|bufsize
suffix:semicolon
DECL|member|bytecnt
id|u16
id|bytecnt
suffix:semicolon
DECL|member|cmd_stat
id|u32
id|cmd_stat
suffix:semicolon
DECL|member|next_desc_ptr
id|u32
id|next_desc_ptr
suffix:semicolon
DECL|member|buffer
id|u32
id|buffer
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|mv64x60_tx_desc
r_struct
id|mv64x60_tx_desc
(brace
DECL|member|bytecnt
id|u16
id|bytecnt
suffix:semicolon
DECL|member|shadow
id|u16
id|shadow
suffix:semicolon
DECL|member|cmd_stat
id|u32
id|cmd_stat
suffix:semicolon
DECL|member|next_desc_ptr
id|u32
id|next_desc_ptr
suffix:semicolon
DECL|member|buffer
id|u32
id|buffer
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|MAX_RESET_WAIT
mdefine_line|#define&t;MAX_RESET_WAIT&t;10000
DECL|macro|MAX_TX_WAIT
mdefine_line|#define&t;MAX_TX_WAIT&t;10000
DECL|macro|RX_NUM_DESC
mdefine_line|#define&t;RX_NUM_DESC&t;2
DECL|macro|TX_NUM_DESC
mdefine_line|#define&t;TX_NUM_DESC&t;2
DECL|macro|RX_BUF_SIZE
mdefine_line|#define&t;RX_BUF_SIZE&t;32
DECL|macro|TX_BUF_SIZE
mdefine_line|#define&t;TX_BUF_SIZE&t;32
DECL|variable|rd
r_static
r_struct
id|mv64x60_rx_desc
id|rd
(braket
l_int|2
)braket
(braket
id|RX_NUM_DESC
)braket
id|__attribute__
(paren
(paren
id|aligned
c_func
(paren
l_int|32
)paren
)paren
)paren
suffix:semicolon
DECL|variable|td
r_static
r_struct
id|mv64x60_tx_desc
id|td
(braket
l_int|2
)braket
(braket
id|TX_NUM_DESC
)braket
id|__attribute__
(paren
(paren
id|aligned
c_func
(paren
l_int|32
)paren
)paren
)paren
suffix:semicolon
DECL|variable|rx_buf
r_static
r_char
id|rx_buf
(braket
l_int|2
)braket
(braket
id|RX_NUM_DESC
op_star
id|RX_BUF_SIZE
)braket
id|__attribute__
(paren
(paren
id|aligned
c_func
(paren
l_int|32
)paren
)paren
)paren
suffix:semicolon
DECL|variable|tx_buf
r_static
r_char
id|tx_buf
(braket
l_int|2
)braket
(braket
id|TX_NUM_DESC
op_star
id|TX_BUF_SIZE
)braket
id|__attribute__
(paren
(paren
id|aligned
c_func
(paren
l_int|32
)paren
)paren
)paren
suffix:semicolon
DECL|variable|cur_rd
r_static
r_int
id|cur_rd
(braket
l_int|2
)braket
op_assign
(brace
l_int|0
comma
l_int|0
)brace
suffix:semicolon
DECL|variable|cur_td
r_static
r_int
id|cur_td
(braket
l_int|2
)braket
op_assign
(brace
l_int|0
comma
l_int|0
)brace
suffix:semicolon
DECL|variable|chan_initialized
r_static
r_char
id|chan_initialized
(braket
l_int|2
)braket
op_assign
(brace
l_int|0
comma
l_int|0
)brace
suffix:semicolon
DECL|macro|RX_INIT_RDP
mdefine_line|#define&t;RX_INIT_RDP(rdp) {&t;&t;&t;&bslash;&n;&t;(rdp)-&gt;bufsize = 2;&t;&t;&t;&bslash;&n;&t;(rdp)-&gt;bytecnt = 0;&t;&t;&t;&bslash;&n;&t;(rdp)-&gt;cmd_stat = SDMA_DESC_CMDSTAT_L | SDMA_DESC_CMDSTAT_F |&t;&bslash;&n;&t;&t;SDMA_DESC_CMDSTAT_O;&t;&bslash;&n;}
macro_line|#ifdef CONFIG_MV64360
DECL|variable|cpu2mem_tab
r_static
id|u32
id|cpu2mem_tab
(braket
id|MV64x60_CPU2MEM_WINDOWS
)braket
(braket
l_int|2
)braket
op_assign
(brace
(brace
id|MV64x60_CPU2MEM_0_BASE
comma
id|MV64x60_CPU2MEM_0_SIZE
)brace
comma
(brace
id|MV64x60_CPU2MEM_1_BASE
comma
id|MV64x60_CPU2MEM_1_SIZE
)brace
comma
(brace
id|MV64x60_CPU2MEM_2_BASE
comma
id|MV64x60_CPU2MEM_2_SIZE
)brace
comma
(brace
id|MV64x60_CPU2MEM_3_BASE
comma
id|MV64x60_CPU2MEM_3_SIZE
)brace
)brace
suffix:semicolon
DECL|variable|com2mem_tab
r_static
id|u32
id|com2mem_tab
(braket
id|MV64x60_CPU2MEM_WINDOWS
)braket
(braket
l_int|2
)braket
op_assign
(brace
(brace
id|MV64360_MPSC2MEM_0_BASE
comma
id|MV64360_MPSC2MEM_0_SIZE
)brace
comma
(brace
id|MV64360_MPSC2MEM_1_BASE
comma
id|MV64360_MPSC2MEM_1_SIZE
)brace
comma
(brace
id|MV64360_MPSC2MEM_2_BASE
comma
id|MV64360_MPSC2MEM_2_SIZE
)brace
comma
(brace
id|MV64360_MPSC2MEM_3_BASE
comma
id|MV64360_MPSC2MEM_3_SIZE
)brace
)brace
suffix:semicolon
DECL|variable|dram_selects
r_static
id|u32
id|dram_selects
(braket
id|MV64x60_CPU2MEM_WINDOWS
)braket
op_assign
(brace
l_int|0xe
comma
l_int|0xd
comma
l_int|0xb
comma
l_int|0x7
)brace
suffix:semicolon
macro_line|#endif
r_int
r_int
DECL|function|serial_init
id|serial_init
c_func
(paren
r_int
id|chan
comma
r_void
op_star
id|ignored
)paren
(brace
id|u32
id|mpsc_routing_base
comma
id|sdma_base
comma
id|brg_bcr
comma
id|cdv
suffix:semicolon
r_int
id|i
suffix:semicolon
id|chan
op_assign
(paren
id|chan
op_eq
l_int|1
)paren
suffix:semicolon
multiline_comment|/* default to chan 0 if anything but 1 */
r_if
c_cond
(paren
id|chan_initialized
(braket
id|chan
)braket
)paren
r_return
id|chan
suffix:semicolon
id|chan_initialized
(braket
id|chan
)braket
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|chan
op_eq
l_int|0
)paren
(brace
id|sdma_base
op_assign
id|MV64x60_SDMA_0_OFFSET
suffix:semicolon
id|brg_bcr
op_assign
id|MV64x60_BRG_0_OFFSET
op_plus
id|BRG_BCR
suffix:semicolon
id|SDMA_REGS_INIT
c_func
(paren
op_amp
id|sdma_regs
(braket
l_int|0
)braket
comma
id|MV64x60_SDMA_0_OFFSET
)paren
suffix:semicolon
)brace
r_else
(brace
id|sdma_base
op_assign
id|MV64x60_SDMA_1_OFFSET
suffix:semicolon
id|brg_bcr
op_assign
id|MV64x60_BRG_1_OFFSET
op_plus
id|BRG_BCR
suffix:semicolon
id|SDMA_REGS_INIT
c_func
(paren
op_amp
id|sdma_regs
(braket
l_int|0
)braket
comma
id|MV64x60_SDMA_1_OFFSET
)paren
suffix:semicolon
)brace
id|mpsc_routing_base
op_assign
id|MV64x60_MPSC_ROUTING_OFFSET
suffix:semicolon
id|stop_dma
c_func
(paren
id|chan
)paren
suffix:semicolon
multiline_comment|/* Set up ring buffers */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|RX_NUM_DESC
suffix:semicolon
id|i
op_increment
)paren
(brace
id|RX_INIT_RDP
c_func
(paren
op_amp
id|rd
(braket
id|chan
)braket
(braket
id|i
)braket
)paren
suffix:semicolon
id|rd
(braket
id|chan
)braket
(braket
id|i
)braket
dot
id|buffer
op_assign
(paren
id|u32
)paren
op_amp
id|rx_buf
(braket
id|chan
)braket
(braket
id|i
op_star
id|RX_BUF_SIZE
)braket
suffix:semicolon
id|rd
(braket
id|chan
)braket
(braket
id|i
)braket
dot
id|next_desc_ptr
op_assign
(paren
id|u32
)paren
op_amp
id|rd
(braket
id|chan
)braket
(braket
id|i
op_plus
l_int|1
)braket
suffix:semicolon
)brace
id|rd
(braket
id|chan
)braket
(braket
id|RX_NUM_DESC
op_minus
l_int|1
)braket
dot
id|next_desc_ptr
op_assign
(paren
id|u32
)paren
op_amp
id|rd
(braket
id|chan
)braket
(braket
l_int|0
)braket
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
id|TX_NUM_DESC
suffix:semicolon
id|i
op_increment
)paren
(brace
id|td
(braket
id|chan
)braket
(braket
id|i
)braket
dot
id|bytecnt
op_assign
l_int|0
suffix:semicolon
id|td
(braket
id|chan
)braket
(braket
id|i
)braket
dot
id|shadow
op_assign
l_int|0
suffix:semicolon
id|td
(braket
id|chan
)braket
(braket
id|i
)braket
dot
id|buffer
op_assign
(paren
id|u32
)paren
op_amp
id|tx_buf
(braket
id|chan
)braket
(braket
id|i
op_star
id|TX_BUF_SIZE
)braket
suffix:semicolon
id|td
(braket
id|chan
)braket
(braket
id|i
)braket
dot
id|cmd_stat
op_assign
id|SDMA_DESC_CMDSTAT_F
op_or
id|SDMA_DESC_CMDSTAT_L
suffix:semicolon
id|td
(braket
id|chan
)braket
(braket
id|i
)braket
dot
id|next_desc_ptr
op_assign
(paren
id|u32
)paren
op_amp
id|td
(braket
id|chan
)braket
(braket
id|i
op_plus
l_int|1
)braket
suffix:semicolon
)brace
id|td
(braket
id|chan
)braket
(braket
id|TX_NUM_DESC
op_minus
l_int|1
)braket
dot
id|next_desc_ptr
op_assign
(paren
id|u32
)paren
op_amp
id|td
(braket
id|chan
)braket
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* Set MPSC Routing */
id|out_le32
c_func
(paren
id|mv64x60_base
op_plus
id|mpsc_routing_base
op_plus
id|MPSC_MRR
comma
l_int|0x3ffffe38
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_GT64260
id|out_le32
c_func
(paren
id|mv64x60_base
op_plus
id|GT64260_MPP_SERIAL_PORTS_MULTIPLEX
comma
l_int|0x00001102
)paren
suffix:semicolon
macro_line|#else /* Must be MV64360 or MV64460 */
(brace
id|u32
id|enables
comma
id|prot_bits
comma
id|v
suffix:semicolon
multiline_comment|/* Set up comm unit to memory mapping windows */
multiline_comment|/* Note: Assumes MV64x60_CPU2MEM_WINDOWS == 4 */
id|enables
op_assign
id|in_le32
c_func
(paren
id|mv64x60_base
op_plus
id|MV64360_CPU_BAR_ENABLE
)paren
op_amp
l_int|0xf
suffix:semicolon
id|prot_bits
op_assign
l_int|0
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
id|MV64x60_CPU2MEM_WINDOWS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|enables
op_amp
(paren
l_int|1
op_lshift
id|i
)paren
)paren
)paren
(brace
id|v
op_assign
id|in_le32
c_func
(paren
id|mv64x60_base
op_plus
id|cpu2mem_tab
(braket
id|i
)braket
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|v
op_assign
(paren
(paren
id|v
op_amp
l_int|0xffff
)paren
op_lshift
l_int|16
)paren
op_or
(paren
id|dram_selects
(braket
id|i
)braket
op_lshift
l_int|8
)paren
suffix:semicolon
id|out_le32
c_func
(paren
id|mv64x60_base
op_plus
id|com2mem_tab
(braket
id|i
)braket
(braket
l_int|0
)braket
comma
id|v
)paren
suffix:semicolon
id|v
op_assign
id|in_le32
c_func
(paren
id|mv64x60_base
op_plus
id|cpu2mem_tab
(braket
id|i
)braket
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|v
op_assign
(paren
id|v
op_amp
l_int|0xffff
)paren
op_lshift
l_int|16
suffix:semicolon
id|out_le32
c_func
(paren
id|mv64x60_base
op_plus
id|com2mem_tab
(braket
id|i
)braket
(braket
l_int|1
)braket
comma
id|v
)paren
suffix:semicolon
id|prot_bits
op_or_assign
(paren
l_int|0x3
op_lshift
(paren
id|i
op_lshift
l_int|1
)paren
)paren
suffix:semicolon
multiline_comment|/* r/w access */
)brace
)brace
id|out_le32
c_func
(paren
id|mv64x60_base
op_plus
id|MV64360_MPSC_0_REMAP
comma
l_int|0
)paren
suffix:semicolon
id|out_le32
c_func
(paren
id|mv64x60_base
op_plus
id|MV64360_MPSC_1_REMAP
comma
l_int|0
)paren
suffix:semicolon
id|out_le32
c_func
(paren
id|mv64x60_base
op_plus
id|MV64360_MPSC2MEM_ACC_PROT_0
comma
id|prot_bits
)paren
suffix:semicolon
id|out_le32
c_func
(paren
id|mv64x60_base
op_plus
id|MV64360_MPSC2MEM_ACC_PROT_1
comma
id|prot_bits
)paren
suffix:semicolon
id|out_le32
c_func
(paren
id|mv64x60_base
op_plus
id|MV64360_MPSC2MEM_BAR_ENABLE
comma
id|enables
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* MPSC 0/1 Rx &amp; Tx get clocks BRG0/1 */
id|out_le32
c_func
(paren
id|mv64x60_base
op_plus
id|mpsc_routing_base
op_plus
id|MPSC_RCRR
comma
l_int|0x00000100
)paren
suffix:semicolon
id|out_le32
c_func
(paren
id|mv64x60_base
op_plus
id|mpsc_routing_base
op_plus
id|MPSC_TCRR
comma
l_int|0x00000100
)paren
suffix:semicolon
multiline_comment|/* clear pending interrupts */
id|out_le32
c_func
(paren
id|mv64x60_base
op_plus
id|MV64x60_SDMA_INTR_OFFSET
op_plus
id|SDMA_INTR_MASK
comma
l_int|0
)paren
suffix:semicolon
id|out_le32
c_func
(paren
id|mv64x60_base
op_plus
id|SDMA_SCRDP
op_plus
id|sdma_base
comma
(paren
r_int
)paren
op_amp
id|rd
(braket
id|chan
)braket
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|out_le32
c_func
(paren
id|mv64x60_base
op_plus
id|SDMA_SCTDP
op_plus
id|sdma_base
comma
(paren
r_int
)paren
op_amp
id|td
(braket
id|chan
)braket
(braket
id|TX_NUM_DESC
op_minus
l_int|1
)braket
)paren
suffix:semicolon
id|out_le32
c_func
(paren
id|mv64x60_base
op_plus
id|SDMA_SFTDP
op_plus
id|sdma_base
comma
(paren
r_int
)paren
op_amp
id|td
(braket
id|chan
)braket
(braket
id|TX_NUM_DESC
op_minus
l_int|1
)braket
)paren
suffix:semicolon
id|out_le32
c_func
(paren
id|mv64x60_base
op_plus
id|SDMA_SDC
op_plus
id|sdma_base
comma
id|SDMA_SDC_RFT
op_or
id|SDMA_SDC_SFM
op_or
id|SDMA_SDC_BLMR
op_or
id|SDMA_SDC_BLMT
op_or
(paren
l_int|3
op_lshift
l_int|12
)paren
)paren
suffix:semicolon
id|cdv
op_assign
(paren
(paren
id|mv64x60_mpsc_clk_freq
op_div
(paren
l_int|32
op_star
id|mv64x60_console_baud
)paren
)paren
op_minus
l_int|1
)paren
suffix:semicolon
id|out_le32
c_func
(paren
id|mv64x60_base
op_plus
id|brg_bcr
comma
(paren
(paren
id|mv64x60_mpsc_clk_src
op_lshift
l_int|18
)paren
op_or
(paren
l_int|1
op_lshift
l_int|16
)paren
op_or
id|cdv
)paren
)paren
suffix:semicolon
multiline_comment|/* Put MPSC into UART mode, no null modem, 16x clock mode */
id|out_le32
c_func
(paren
id|mv64x60_base
op_plus
id|MPSC_MMCRL
op_plus
id|mpsc_base
(braket
id|chan
)braket
comma
l_int|0x000004c4
)paren
suffix:semicolon
id|out_le32
c_func
(paren
id|mv64x60_base
op_plus
id|MPSC_MMCRH
op_plus
id|mpsc_base
(braket
id|chan
)braket
comma
l_int|0x04400400
)paren
suffix:semicolon
id|out_le32
c_func
(paren
id|mv64x60_base
op_plus
id|MPSC_CHR_1
op_plus
id|mpsc_base
(braket
id|chan
)braket
comma
l_int|0
)paren
suffix:semicolon
id|out_le32
c_func
(paren
id|mv64x60_base
op_plus
id|MPSC_CHR_9
op_plus
id|mpsc_base
(braket
id|chan
)braket
comma
l_int|0
)paren
suffix:semicolon
id|out_le32
c_func
(paren
id|mv64x60_base
op_plus
id|MPSC_CHR_10
op_plus
id|mpsc_base
(braket
id|chan
)braket
comma
l_int|0
)paren
suffix:semicolon
id|out_le32
c_func
(paren
id|mv64x60_base
op_plus
id|MPSC_CHR_3
op_plus
id|mpsc_base
(braket
id|chan
)braket
comma
l_int|4
)paren
suffix:semicolon
id|out_le32
c_func
(paren
id|mv64x60_base
op_plus
id|MPSC_CHR_4
op_plus
id|mpsc_base
(braket
id|chan
)braket
comma
l_int|0
)paren
suffix:semicolon
id|out_le32
c_func
(paren
id|mv64x60_base
op_plus
id|MPSC_CHR_5
op_plus
id|mpsc_base
(braket
id|chan
)braket
comma
l_int|0
)paren
suffix:semicolon
id|out_le32
c_func
(paren
id|mv64x60_base
op_plus
id|MPSC_CHR_6
op_plus
id|mpsc_base
(braket
id|chan
)braket
comma
l_int|0
)paren
suffix:semicolon
id|out_le32
c_func
(paren
id|mv64x60_base
op_plus
id|MPSC_CHR_7
op_plus
id|mpsc_base
(braket
id|chan
)braket
comma
l_int|0
)paren
suffix:semicolon
id|out_le32
c_func
(paren
id|mv64x60_base
op_plus
id|MPSC_CHR_8
op_plus
id|mpsc_base
(braket
id|chan
)braket
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* 8 data bits, 1 stop bit */
id|out_le32
c_func
(paren
id|mv64x60_base
op_plus
id|MPSC_MPCR
op_plus
id|mpsc_base
(braket
id|chan
)braket
comma
(paren
l_int|3
op_lshift
l_int|12
)paren
)paren
suffix:semicolon
id|out_le32
c_func
(paren
id|mv64x60_base
op_plus
id|SDMA_SDCM
op_plus
id|sdma_base
comma
id|SDMA_SDCM_ERD
)paren
suffix:semicolon
id|out_le32
c_func
(paren
id|mv64x60_base
op_plus
id|MPSC_CHR_2
op_plus
id|mpsc_base
(braket
id|chan
)braket
comma
id|MPSC_CHR_2_EH
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|100
)paren
suffix:semicolon
r_return
id|chan
suffix:semicolon
)brace
r_static
r_void
DECL|function|stop_dma
id|stop_dma
c_func
(paren
r_int
id|chan
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/* Abort MPSC Rx (aborting Tx messes things up) */
id|out_le32
c_func
(paren
id|mv64x60_base
op_plus
id|MPSC_CHR_2
op_plus
id|mpsc_base
(braket
id|chan
)braket
comma
id|MPSC_CHR_2_RA
)paren
suffix:semicolon
multiline_comment|/* Abort SDMA Rx, Tx */
id|out_le32
c_func
(paren
id|mv64x60_base
op_plus
id|sdma_regs
(braket
id|chan
)braket
dot
id|sdcm
comma
id|SDMA_SDCM_AR
op_or
id|SDMA_SDCM_STD
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
id|MAX_RESET_WAIT
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
id|in_le32
c_func
(paren
id|mv64x60_base
op_plus
id|sdma_regs
(braket
id|chan
)braket
dot
id|sdcm
)paren
op_amp
(paren
id|SDMA_SDCM_AR
op_or
id|SDMA_SDCM_AT
)paren
)paren
op_eq
l_int|0
)paren
r_break
suffix:semicolon
id|udelay
c_func
(paren
l_int|100
)paren
suffix:semicolon
)brace
)brace
r_static
r_int
DECL|function|wait_for_ownership
id|wait_for_ownership
c_func
(paren
r_int
id|chan
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
id|MAX_TX_WAIT
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
id|in_le32
c_func
(paren
id|mv64x60_base
op_plus
id|sdma_regs
(braket
id|chan
)braket
dot
id|sdcm
)paren
op_amp
id|SDMA_SDCM_TXD
)paren
op_eq
l_int|0
)paren
r_break
suffix:semicolon
id|udelay
c_func
(paren
l_int|1000
)paren
suffix:semicolon
)brace
r_return
(paren
id|i
OL
id|MAX_TX_WAIT
)paren
suffix:semicolon
)brace
r_void
DECL|function|serial_putc
id|serial_putc
c_func
(paren
r_int
r_int
id|com_port
comma
r_int
r_char
id|c
)paren
(brace
r_struct
id|mv64x60_tx_desc
op_star
id|tdp
suffix:semicolon
r_if
c_cond
(paren
id|wait_for_ownership
c_func
(paren
id|com_port
)paren
op_eq
l_int|0
)paren
r_return
suffix:semicolon
id|tdp
op_assign
op_amp
id|td
(braket
id|com_port
)braket
(braket
id|cur_td
(braket
id|com_port
)braket
)braket
suffix:semicolon
r_if
c_cond
(paren
op_increment
id|cur_td
(braket
id|com_port
)braket
op_ge
id|TX_NUM_DESC
)paren
id|cur_td
(braket
id|com_port
)braket
op_assign
l_int|0
suffix:semicolon
op_star
(paren
id|unchar
op_star
)paren
(paren
id|tdp-&gt;buffer
op_xor
l_int|7
)paren
op_assign
id|c
suffix:semicolon
id|tdp-&gt;bytecnt
op_assign
l_int|1
suffix:semicolon
id|tdp-&gt;shadow
op_assign
l_int|1
suffix:semicolon
id|tdp-&gt;cmd_stat
op_assign
id|SDMA_DESC_CMDSTAT_L
op_or
id|SDMA_DESC_CMDSTAT_F
op_or
id|SDMA_DESC_CMDSTAT_O
suffix:semicolon
id|out_le32
c_func
(paren
id|mv64x60_base
op_plus
id|sdma_regs
(braket
id|com_port
)braket
dot
id|sctdp
comma
(paren
r_int
)paren
id|tdp
)paren
suffix:semicolon
id|out_le32
c_func
(paren
id|mv64x60_base
op_plus
id|sdma_regs
(braket
id|com_port
)braket
dot
id|sftdp
comma
(paren
r_int
)paren
id|tdp
)paren
suffix:semicolon
id|out_le32
c_func
(paren
id|mv64x60_base
op_plus
id|sdma_regs
(braket
id|com_port
)braket
dot
id|sdcm
comma
id|in_le32
c_func
(paren
id|mv64x60_base
op_plus
id|sdma_regs
(braket
id|com_port
)braket
dot
id|sdcm
)paren
op_or
id|SDMA_SDCM_TXD
)paren
suffix:semicolon
)brace
r_int
r_char
DECL|function|serial_getc
id|serial_getc
c_func
(paren
r_int
r_int
id|com_port
)paren
(brace
r_struct
id|mv64x60_rx_desc
op_star
id|rdp
suffix:semicolon
id|unchar
id|c
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|rdp
op_assign
op_amp
id|rd
(braket
id|com_port
)braket
(braket
id|cur_rd
(braket
id|com_port
)braket
)braket
suffix:semicolon
r_if
c_cond
(paren
(paren
id|rdp-&gt;cmd_stat
op_amp
(paren
id|SDMA_DESC_CMDSTAT_O
op_or
id|SDMA_DESC_CMDSTAT_ES
)paren
)paren
op_eq
l_int|0
)paren
(brace
id|c
op_assign
op_star
(paren
id|unchar
op_star
)paren
(paren
id|rdp-&gt;buffer
op_xor
l_int|7
)paren
suffix:semicolon
id|RX_INIT_RDP
c_func
(paren
id|rdp
)paren
suffix:semicolon
r_if
c_cond
(paren
op_increment
id|cur_rd
(braket
id|com_port
)braket
op_ge
id|RX_NUM_DESC
)paren
id|cur_rd
(braket
id|com_port
)braket
op_assign
l_int|0
suffix:semicolon
)brace
r_return
id|c
suffix:semicolon
)brace
r_int
DECL|function|serial_tstc
id|serial_tstc
c_func
(paren
r_int
r_int
id|com_port
)paren
(brace
r_struct
id|mv64x60_rx_desc
op_star
id|rdp
suffix:semicolon
r_int
id|loop_count
op_assign
l_int|0
suffix:semicolon
r_int
id|rc
op_assign
l_int|0
suffix:semicolon
id|rdp
op_assign
op_amp
id|rd
(braket
id|com_port
)braket
(braket
id|cur_rd
(braket
id|com_port
)braket
)braket
suffix:semicolon
multiline_comment|/* Go thru rcv desc&squot;s until empty looking for one with data (no error)*/
r_while
c_loop
(paren
(paren
(paren
id|rdp-&gt;cmd_stat
op_amp
id|SDMA_DESC_CMDSTAT_O
)paren
op_eq
l_int|0
)paren
op_logical_and
(paren
id|loop_count
op_increment
OL
id|RX_NUM_DESC
)paren
)paren
(brace
multiline_comment|/* If there was an error, reinit the desc &amp; continue */
r_if
c_cond
(paren
(paren
id|rdp-&gt;cmd_stat
op_amp
id|SDMA_DESC_CMDSTAT_ES
)paren
op_ne
l_int|0
)paren
(brace
id|RX_INIT_RDP
c_func
(paren
id|rdp
)paren
suffix:semicolon
r_if
c_cond
(paren
op_increment
id|cur_rd
(braket
id|com_port
)braket
op_ge
id|RX_NUM_DESC
)paren
id|cur_rd
(braket
id|com_port
)braket
op_assign
l_int|0
suffix:semicolon
id|rdp
op_assign
(paren
r_struct
id|mv64x60_rx_desc
op_star
)paren
id|rdp-&gt;next_desc_ptr
suffix:semicolon
)brace
r_else
(brace
id|rc
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_return
id|rc
suffix:semicolon
)brace
r_void
DECL|function|serial_close
id|serial_close
c_func
(paren
r_int
r_int
id|com_port
)paren
(brace
id|stop_dma
c_func
(paren
id|com_port
)paren
suffix:semicolon
)brace
eof
