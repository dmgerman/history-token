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
macro_line|#include &lt;linux/serial_core.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/dma-mapping.h&gt;
macro_line|#include &lt;linux/mv643xx.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#if defined(CONFIG_SERIAL_MPSC_CONSOLE) &amp;&amp; defined(CONFIG_MAGIC_SYSRQ)
DECL|macro|SUPPORT_SYSRQ
mdefine_line|#define SUPPORT_SYSRQ
macro_line|#endif
DECL|macro|MPSC_NUM_CTLRS
mdefine_line|#define&t;MPSC_NUM_CTLRS&t;&t;2
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
id|phys_addr_t
id|mpsc_routing_base_p
suffix:semicolon
DECL|member|sdma_intr_base_p
id|phys_addr_t
id|sdma_intr_base_p
suffix:semicolon
DECL|member|mpsc_routing_base
r_void
op_star
id|mpsc_routing_base
suffix:semicolon
DECL|member|sdma_intr_base
r_void
op_star
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
id|phys_addr_t
id|mpsc_base_p
suffix:semicolon
DECL|member|sdma_base_p
id|phys_addr_t
id|sdma_base_p
suffix:semicolon
DECL|member|brg_base_p
id|phys_addr_t
id|brg_base_p
suffix:semicolon
multiline_comment|/* Virtual addresses of various blocks of registers (from platform) */
DECL|member|mpsc_base
r_void
op_star
id|mpsc_base
suffix:semicolon
DECL|member|sdma_base
r_void
op_star
id|sdma_base
suffix:semicolon
DECL|member|brg_base
r_void
op_star
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
multiline_comment|/*&n; *****************************************************************************&n; *&n; *&t;Multi-Protocol Serial Controller Interface Registers&n; *&n; *****************************************************************************&n; */
multiline_comment|/* Main Configuratino Register Offsets */
DECL|macro|MPSC_MMCRL
mdefine_line|#define&t;MPSC_MMCRL&t;&t;&t;0x0000
DECL|macro|MPSC_MMCRH
mdefine_line|#define&t;MPSC_MMCRH&t;&t;&t;0x0004
DECL|macro|MPSC_MPCR
mdefine_line|#define&t;MPSC_MPCR&t;&t;&t;0x0008
DECL|macro|MPSC_CHR_1
mdefine_line|#define&t;MPSC_CHR_1&t;&t;&t;0x000c
DECL|macro|MPSC_CHR_2
mdefine_line|#define&t;MPSC_CHR_2&t;&t;&t;0x0010
DECL|macro|MPSC_CHR_3
mdefine_line|#define&t;MPSC_CHR_3&t;&t;&t;0x0014
DECL|macro|MPSC_CHR_4
mdefine_line|#define&t;MPSC_CHR_4&t;&t;&t;0x0018
DECL|macro|MPSC_CHR_5
mdefine_line|#define&t;MPSC_CHR_5&t;&t;&t;0x001c
DECL|macro|MPSC_CHR_6
mdefine_line|#define&t;MPSC_CHR_6&t;&t;&t;0x0020
DECL|macro|MPSC_CHR_7
mdefine_line|#define&t;MPSC_CHR_7&t;&t;&t;0x0024
DECL|macro|MPSC_CHR_8
mdefine_line|#define&t;MPSC_CHR_8&t;&t;&t;0x0028
DECL|macro|MPSC_CHR_9
mdefine_line|#define&t;MPSC_CHR_9&t;&t;&t;0x002c
DECL|macro|MPSC_CHR_10
mdefine_line|#define&t;MPSC_CHR_10&t;&t;&t;0x0030
DECL|macro|MPSC_CHR_11
mdefine_line|#define&t;MPSC_CHR_11&t;&t;&t;0x0034
DECL|macro|MPSC_MPCR_FRZ
mdefine_line|#define&t;MPSC_MPCR_FRZ&t;&t;&t;(1 &lt;&lt; 9)
DECL|macro|MPSC_MPCR_CL_5
mdefine_line|#define&t;MPSC_MPCR_CL_5&t;&t;&t;0
DECL|macro|MPSC_MPCR_CL_6
mdefine_line|#define&t;MPSC_MPCR_CL_6&t;&t;&t;1
DECL|macro|MPSC_MPCR_CL_7
mdefine_line|#define&t;MPSC_MPCR_CL_7&t;&t;&t;2
DECL|macro|MPSC_MPCR_CL_8
mdefine_line|#define&t;MPSC_MPCR_CL_8&t;&t;&t;3
DECL|macro|MPSC_MPCR_SBL_1
mdefine_line|#define&t;MPSC_MPCR_SBL_1&t;&t;&t;0
DECL|macro|MPSC_MPCR_SBL_2
mdefine_line|#define&t;MPSC_MPCR_SBL_2&t;&t;&t;1
DECL|macro|MPSC_CHR_2_TEV
mdefine_line|#define&t;MPSC_CHR_2_TEV&t;&t;&t;(1&lt;&lt;1)
DECL|macro|MPSC_CHR_2_TA
mdefine_line|#define&t;MPSC_CHR_2_TA&t;&t;&t;(1&lt;&lt;7)
DECL|macro|MPSC_CHR_2_TTCS
mdefine_line|#define&t;MPSC_CHR_2_TTCS&t;&t;&t;(1&lt;&lt;9)
DECL|macro|MPSC_CHR_2_REV
mdefine_line|#define&t;MPSC_CHR_2_REV&t;&t;&t;(1&lt;&lt;17)
DECL|macro|MPSC_CHR_2_RA
mdefine_line|#define&t;MPSC_CHR_2_RA&t;&t;&t;(1&lt;&lt;23)
DECL|macro|MPSC_CHR_2_CRD
mdefine_line|#define&t;MPSC_CHR_2_CRD&t;&t;&t;(1&lt;&lt;25)
DECL|macro|MPSC_CHR_2_EH
mdefine_line|#define&t;MPSC_CHR_2_EH&t;&t;&t;(1&lt;&lt;31)
DECL|macro|MPSC_CHR_2_PAR_ODD
mdefine_line|#define&t;MPSC_CHR_2_PAR_ODD&t;&t;0
DECL|macro|MPSC_CHR_2_PAR_SPACE
mdefine_line|#define&t;MPSC_CHR_2_PAR_SPACE&t;&t;1
DECL|macro|MPSC_CHR_2_PAR_EVEN
mdefine_line|#define&t;MPSC_CHR_2_PAR_EVEN&t;&t;2
DECL|macro|MPSC_CHR_2_PAR_MARK
mdefine_line|#define&t;MPSC_CHR_2_PAR_MARK&t;&t;3
multiline_comment|/* MPSC Signal Routing */
DECL|macro|MPSC_MRR
mdefine_line|#define&t;MPSC_MRR&t;&t;&t;0x0000
DECL|macro|MPSC_RCRR
mdefine_line|#define&t;MPSC_RCRR&t;&t;&t;0x0004
DECL|macro|MPSC_TCRR
mdefine_line|#define&t;MPSC_TCRR&t;&t;&t;0x0008
multiline_comment|/*&n; *****************************************************************************&n; *&n; *&t;Serial DMA Controller Interface Registers&n; *&n; *****************************************************************************&n; */
DECL|macro|SDMA_SDC
mdefine_line|#define&t;SDMA_SDC&t;&t;&t;0x0000
DECL|macro|SDMA_SDCM
mdefine_line|#define&t;SDMA_SDCM&t;&t;&t;0x0008
DECL|macro|SDMA_RX_DESC
mdefine_line|#define&t;SDMA_RX_DESC&t;&t;&t;0x0800
DECL|macro|SDMA_RX_BUF_PTR
mdefine_line|#define&t;SDMA_RX_BUF_PTR&t;&t;&t;0x0808
DECL|macro|SDMA_SCRDP
mdefine_line|#define&t;SDMA_SCRDP&t;&t;&t;0x0810
DECL|macro|SDMA_TX_DESC
mdefine_line|#define&t;SDMA_TX_DESC&t;&t;&t;0x0c00
DECL|macro|SDMA_SCTDP
mdefine_line|#define&t;SDMA_SCTDP&t;&t;&t;0x0c10
DECL|macro|SDMA_SFTDP
mdefine_line|#define&t;SDMA_SFTDP&t;&t;&t;0x0c14
DECL|macro|SDMA_DESC_CMDSTAT_PE
mdefine_line|#define&t;SDMA_DESC_CMDSTAT_PE&t;&t;(1&lt;&lt;0)
DECL|macro|SDMA_DESC_CMDSTAT_CDL
mdefine_line|#define&t;SDMA_DESC_CMDSTAT_CDL&t;&t;(1&lt;&lt;1)
DECL|macro|SDMA_DESC_CMDSTAT_FR
mdefine_line|#define&t;SDMA_DESC_CMDSTAT_FR&t;&t;(1&lt;&lt;3)
DECL|macro|SDMA_DESC_CMDSTAT_OR
mdefine_line|#define&t;SDMA_DESC_CMDSTAT_OR&t;&t;(1&lt;&lt;6)
DECL|macro|SDMA_DESC_CMDSTAT_BR
mdefine_line|#define&t;SDMA_DESC_CMDSTAT_BR&t;&t;(1&lt;&lt;9)
DECL|macro|SDMA_DESC_CMDSTAT_MI
mdefine_line|#define&t;SDMA_DESC_CMDSTAT_MI&t;&t;(1&lt;&lt;10)
DECL|macro|SDMA_DESC_CMDSTAT_A
mdefine_line|#define&t;SDMA_DESC_CMDSTAT_A&t;&t;(1&lt;&lt;11)
DECL|macro|SDMA_DESC_CMDSTAT_AM
mdefine_line|#define&t;SDMA_DESC_CMDSTAT_AM&t;&t;(1&lt;&lt;12)
DECL|macro|SDMA_DESC_CMDSTAT_CT
mdefine_line|#define&t;SDMA_DESC_CMDSTAT_CT&t;&t;(1&lt;&lt;13)
DECL|macro|SDMA_DESC_CMDSTAT_C
mdefine_line|#define&t;SDMA_DESC_CMDSTAT_C&t;&t;(1&lt;&lt;14)
DECL|macro|SDMA_DESC_CMDSTAT_ES
mdefine_line|#define&t;SDMA_DESC_CMDSTAT_ES&t;&t;(1&lt;&lt;15)
DECL|macro|SDMA_DESC_CMDSTAT_L
mdefine_line|#define&t;SDMA_DESC_CMDSTAT_L&t;&t;(1&lt;&lt;16)
DECL|macro|SDMA_DESC_CMDSTAT_F
mdefine_line|#define&t;SDMA_DESC_CMDSTAT_F&t;&t;(1&lt;&lt;17)
DECL|macro|SDMA_DESC_CMDSTAT_P
mdefine_line|#define&t;SDMA_DESC_CMDSTAT_P&t;&t;(1&lt;&lt;18)
DECL|macro|SDMA_DESC_CMDSTAT_EI
mdefine_line|#define&t;SDMA_DESC_CMDSTAT_EI&t;&t;(1&lt;&lt;23)
DECL|macro|SDMA_DESC_CMDSTAT_O
mdefine_line|#define&t;SDMA_DESC_CMDSTAT_O&t;&t;(1&lt;&lt;31)
DECL|macro|SDMA_DESC_DFLT
mdefine_line|#define SDMA_DESC_DFLT&t;&t;&t;(SDMA_DESC_CMDSTAT_O |&t;&bslash;&n;&t;&t;&t;&t;&t;SDMA_DESC_CMDSTAT_EI)
DECL|macro|SDMA_SDC_RFT
mdefine_line|#define&t;SDMA_SDC_RFT&t;&t;&t;(1&lt;&lt;0)
DECL|macro|SDMA_SDC_SFM
mdefine_line|#define&t;SDMA_SDC_SFM&t;&t;&t;(1&lt;&lt;1)
DECL|macro|SDMA_SDC_BLMR
mdefine_line|#define&t;SDMA_SDC_BLMR&t;&t;&t;(1&lt;&lt;6)
DECL|macro|SDMA_SDC_BLMT
mdefine_line|#define&t;SDMA_SDC_BLMT&t;&t;&t;(1&lt;&lt;7)
DECL|macro|SDMA_SDC_POVR
mdefine_line|#define&t;SDMA_SDC_POVR&t;&t;&t;(1&lt;&lt;8)
DECL|macro|SDMA_SDC_RIFB
mdefine_line|#define&t;SDMA_SDC_RIFB&t;&t;&t;(1&lt;&lt;9)
DECL|macro|SDMA_SDCM_ERD
mdefine_line|#define&t;SDMA_SDCM_ERD&t;&t;&t;(1&lt;&lt;7)
DECL|macro|SDMA_SDCM_AR
mdefine_line|#define&t;SDMA_SDCM_AR&t;&t;&t;(1&lt;&lt;15)
DECL|macro|SDMA_SDCM_STD
mdefine_line|#define&t;SDMA_SDCM_STD&t;&t;&t;(1&lt;&lt;16)
DECL|macro|SDMA_SDCM_TXD
mdefine_line|#define&t;SDMA_SDCM_TXD&t;&t;&t;(1&lt;&lt;23)
DECL|macro|SDMA_SDCM_AT
mdefine_line|#define&t;SDMA_SDCM_AT&t;&t;&t;(1&lt;&lt;31)
DECL|macro|SDMA_0_CAUSE_RXBUF
mdefine_line|#define&t;SDMA_0_CAUSE_RXBUF&t;&t;(1&lt;&lt;0)
DECL|macro|SDMA_0_CAUSE_RXERR
mdefine_line|#define&t;SDMA_0_CAUSE_RXERR&t;&t;(1&lt;&lt;1)
DECL|macro|SDMA_0_CAUSE_TXBUF
mdefine_line|#define&t;SDMA_0_CAUSE_TXBUF&t;&t;(1&lt;&lt;2)
DECL|macro|SDMA_0_CAUSE_TXEND
mdefine_line|#define&t;SDMA_0_CAUSE_TXEND&t;&t;(1&lt;&lt;3)
DECL|macro|SDMA_1_CAUSE_RXBUF
mdefine_line|#define&t;SDMA_1_CAUSE_RXBUF&t;&t;(1&lt;&lt;8)
DECL|macro|SDMA_1_CAUSE_RXERR
mdefine_line|#define&t;SDMA_1_CAUSE_RXERR&t;&t;(1&lt;&lt;9)
DECL|macro|SDMA_1_CAUSE_TXBUF
mdefine_line|#define&t;SDMA_1_CAUSE_TXBUF&t;&t;(1&lt;&lt;10)
DECL|macro|SDMA_1_CAUSE_TXEND
mdefine_line|#define&t;SDMA_1_CAUSE_TXEND&t;&t;(1&lt;&lt;11)
DECL|macro|SDMA_CAUSE_RX_MASK
mdefine_line|#define&t;SDMA_CAUSE_RX_MASK&t;(SDMA_0_CAUSE_RXBUF | SDMA_0_CAUSE_RXERR | &bslash;&n;&t;SDMA_1_CAUSE_RXBUF | SDMA_1_CAUSE_RXERR)
DECL|macro|SDMA_CAUSE_TX_MASK
mdefine_line|#define&t;SDMA_CAUSE_TX_MASK&t;(SDMA_0_CAUSE_TXBUF | SDMA_0_CAUSE_TXEND | &bslash;&n;&t;SDMA_1_CAUSE_TXBUF | SDMA_1_CAUSE_TXEND)
multiline_comment|/* SDMA Interrupt registers */
DECL|macro|SDMA_INTR_CAUSE
mdefine_line|#define&t;SDMA_INTR_CAUSE&t;&t;&t;0x0000
DECL|macro|SDMA_INTR_MASK
mdefine_line|#define&t;SDMA_INTR_MASK&t;&t;&t;0x0080
multiline_comment|/*&n; *****************************************************************************&n; *&n; *&t;Baud Rate Generator Interface Registers&n; *&n; *****************************************************************************&n; */
DECL|macro|BRG_BCR
mdefine_line|#define&t;BRG_BCR&t;&t;&t;&t;0x0000
DECL|macro|BRG_BTR
mdefine_line|#define&t;BRG_BTR&t;&t;&t;&t;0x0004
macro_line|#endif&t;&t;&t;&t;/* __MPSC_H__ */
eof
