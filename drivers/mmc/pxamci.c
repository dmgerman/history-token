multiline_comment|/*&n; *  linux/drivers/mmc/pxa.c - PXA MMCI driver&n; *&n; *  Copyright (C) 2003 Russell King, All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  This hardware is really sick.  No way to clear interrupts.  Have&n; *  to turn off the clock whenever we touch the device.  Yuck!&n; *&n; *&t;1 and 3 byte data transfers not supported&n; *&t;max block length up to 1023&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/dma-mapping.h&gt;
macro_line|#include &lt;linux/mmc/host.h&gt;
macro_line|#include &lt;linux/mmc/protocol.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/sizes.h&gt;
macro_line|#include &quot;pxamci.h&quot;
macro_line|#ifdef CONFIG_MMC_DEBUG
DECL|macro|DBG
mdefine_line|#define DBG(x...)&t;printk(KERN_DEBUG x)
macro_line|#else
DECL|macro|DBG
mdefine_line|#define DBG(x...)&t;do { } while (0)
macro_line|#endif
DECL|struct|pxamci_host
r_struct
id|pxamci_host
(brace
DECL|member|mmc
r_struct
id|mmc_host
op_star
id|mmc
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|res
r_struct
id|resource
op_star
id|res
suffix:semicolon
DECL|member|base
r_void
op_star
id|base
suffix:semicolon
DECL|member|irq
r_int
id|irq
suffix:semicolon
DECL|member|dma
r_int
id|dma
suffix:semicolon
DECL|member|clkrt
r_int
r_int
id|clkrt
suffix:semicolon
DECL|member|cmdat
r_int
r_int
id|cmdat
suffix:semicolon
DECL|member|imask
r_int
r_int
id|imask
suffix:semicolon
DECL|member|power_mode
r_int
r_int
id|power_mode
suffix:semicolon
DECL|member|req
r_struct
id|mmc_request
op_star
id|req
suffix:semicolon
DECL|member|cmd
r_struct
id|mmc_command
op_star
id|cmd
suffix:semicolon
DECL|member|data
r_struct
id|mmc_data
op_star
id|data
suffix:semicolon
DECL|member|sg_dma
id|dma_addr_t
id|sg_dma
suffix:semicolon
DECL|member|sg_cpu
r_struct
id|pxa_dma_desc
op_star
id|sg_cpu
suffix:semicolon
DECL|member|dma_buf
id|dma_addr_t
id|dma_buf
suffix:semicolon
DECL|member|dma_size
r_int
r_int
id|dma_size
suffix:semicolon
DECL|member|dma_dir
r_int
r_int
id|dma_dir
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * The base MMC clock rate&n; */
DECL|macro|CLOCKRATE
mdefine_line|#define CLOCKRATE&t;20000000
DECL|function|ns_to_clocks
r_static
r_inline
r_int
r_int
id|ns_to_clocks
c_func
(paren
r_int
r_int
id|ns
)paren
(brace
r_return
(paren
id|ns
op_star
(paren
id|CLOCKRATE
op_div
l_int|1000000
)paren
op_plus
l_int|999
)paren
op_div
l_int|1000
suffix:semicolon
)brace
DECL|function|pxamci_stop_clock
r_static
r_void
id|pxamci_stop_clock
c_func
(paren
r_struct
id|pxamci_host
op_star
id|host
)paren
(brace
r_if
c_cond
(paren
id|readl
c_func
(paren
id|host-&gt;base
op_plus
id|MMC_STAT
)paren
op_amp
id|STAT_CLK_EN
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
r_int
id|v
suffix:semicolon
id|writel
c_func
(paren
id|STOP_CLOCK
comma
id|host-&gt;base
op_plus
id|MMC_STRPCL
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Wait for the &quot;clock has stopped&quot; interrupt.&n;&t;&t; * We need to unmask the interrupt to receive&n;&t;&t; * the notification.  Sigh.&n;&t;&t; */
id|spin_lock_irqsave
c_func
(paren
op_amp
id|host-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|writel
c_func
(paren
id|host-&gt;imask
op_amp
op_complement
id|CLK_IS_OFF
comma
id|host-&gt;base
op_plus
id|MMC_I_MASK
)paren
suffix:semicolon
r_do
(brace
id|v
op_assign
id|readl
c_func
(paren
id|host-&gt;base
op_plus
id|MMC_I_REG
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
op_logical_neg
(paren
id|v
op_amp
id|CLK_IS_OFF
)paren
)paren
suffix:semicolon
id|writel
c_func
(paren
id|host-&gt;imask
comma
id|host-&gt;base
op_plus
id|MMC_I_MASK
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|host-&gt;lock
comma
id|flags
)paren
suffix:semicolon
)brace
)brace
DECL|function|pxamci_enable_irq
r_static
r_void
id|pxamci_enable_irq
c_func
(paren
r_struct
id|pxamci_host
op_star
id|host
comma
r_int
r_int
id|mask
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
id|host-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|host-&gt;imask
op_and_assign
op_complement
id|mask
suffix:semicolon
id|writel
c_func
(paren
id|host-&gt;imask
comma
id|host-&gt;base
op_plus
id|MMC_I_MASK
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|host-&gt;lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|pxamci_disable_irq
r_static
r_void
id|pxamci_disable_irq
c_func
(paren
r_struct
id|pxamci_host
op_star
id|host
comma
r_int
r_int
id|mask
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
id|host-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|host-&gt;imask
op_or_assign
id|mask
suffix:semicolon
id|writel
c_func
(paren
id|host-&gt;imask
comma
id|host-&gt;base
op_plus
id|MMC_I_MASK
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|host-&gt;lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|pxamci_setup_data
r_static
r_void
id|pxamci_setup_data
c_func
(paren
r_struct
id|pxamci_host
op_star
id|host
comma
r_struct
id|mmc_data
op_star
id|data
)paren
(brace
r_int
r_int
id|nob
op_assign
id|data-&gt;blocks
suffix:semicolon
r_int
r_int
id|timeout
comma
id|size
suffix:semicolon
id|dma_addr_t
id|dma
suffix:semicolon
id|u32
id|dcmd
suffix:semicolon
r_int
id|i
suffix:semicolon
id|host-&gt;data
op_assign
id|data
suffix:semicolon
r_if
c_cond
(paren
id|data-&gt;flags
op_amp
id|MMC_DATA_STREAM
)paren
id|nob
op_assign
l_int|0xffff
suffix:semicolon
id|writel
c_func
(paren
id|nob
comma
id|host-&gt;base
op_plus
id|MMC_NOB
)paren
suffix:semicolon
id|writel
c_func
(paren
l_int|1
op_lshift
id|data-&gt;blksz_bits
comma
id|host-&gt;base
op_plus
id|MMC_BLKLEN
)paren
suffix:semicolon
id|timeout
op_assign
id|ns_to_clocks
c_func
(paren
id|data-&gt;timeout_ns
)paren
op_plus
id|data-&gt;timeout_clks
suffix:semicolon
id|writel
c_func
(paren
(paren
id|timeout
op_plus
l_int|255
)paren
op_div
l_int|256
comma
id|host-&gt;base
op_plus
id|MMC_RDTO
)paren
suffix:semicolon
r_if
c_cond
(paren
id|data-&gt;flags
op_amp
id|MMC_DATA_READ
)paren
(brace
id|host-&gt;dma_dir
op_assign
id|DMA_FROM_DEVICE
suffix:semicolon
id|dcmd
op_assign
id|DCMD_INCTRGADDR
op_or
id|DCMD_FLOWTRG
suffix:semicolon
id|DRCMRTXMMC
op_assign
l_int|0
suffix:semicolon
id|DRCMRRXMMC
op_assign
id|host-&gt;dma
op_or
id|DRCMR_MAPVLD
suffix:semicolon
)brace
r_else
(brace
id|host-&gt;dma_dir
op_assign
id|DMA_TO_DEVICE
suffix:semicolon
id|dcmd
op_assign
id|DCMD_INCSRCADDR
op_or
id|DCMD_FLOWSRC
suffix:semicolon
id|DRCMRRXMMC
op_assign
l_int|0
suffix:semicolon
id|DRCMRTXMMC
op_assign
id|host-&gt;dma
op_or
id|DRCMR_MAPVLD
suffix:semicolon
)brace
id|dcmd
op_or_assign
id|DCMD_BURST32
op_or
id|DCMD_WIDTH1
suffix:semicolon
id|host-&gt;dma_size
op_assign
id|data-&gt;blocks
op_lshift
id|data-&gt;blksz_bits
suffix:semicolon
id|host-&gt;dma_buf
op_assign
id|dma_map_single
c_func
(paren
id|mmc_dev
c_func
(paren
id|host-&gt;mmc
)paren
comma
id|data-&gt;rq-&gt;buffer
comma
id|host-&gt;dma_size
comma
id|host-&gt;dma_dir
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
comma
id|size
op_assign
id|host-&gt;dma_size
comma
id|dma
op_assign
id|host-&gt;dma_buf
suffix:semicolon
id|size
suffix:semicolon
id|i
op_increment
)paren
(brace
id|u32
id|len
op_assign
id|size
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
id|DCMD_LENGTH
)paren
id|len
op_assign
l_int|0x1000
suffix:semicolon
r_if
c_cond
(paren
id|data-&gt;flags
op_amp
id|MMC_DATA_READ
)paren
(brace
id|host-&gt;sg_cpu
(braket
id|i
)braket
dot
id|dsadr
op_assign
id|host-&gt;res-&gt;start
op_plus
id|MMC_RXFIFO
suffix:semicolon
id|host-&gt;sg_cpu
(braket
id|i
)braket
dot
id|dtadr
op_assign
id|dma
suffix:semicolon
)brace
r_else
(brace
id|host-&gt;sg_cpu
(braket
id|i
)braket
dot
id|dsadr
op_assign
id|dma
suffix:semicolon
id|host-&gt;sg_cpu
(braket
id|i
)braket
dot
id|dtadr
op_assign
id|host-&gt;res-&gt;start
op_plus
id|MMC_TXFIFO
suffix:semicolon
)brace
id|host-&gt;sg_cpu
(braket
id|i
)braket
dot
id|dcmd
op_assign
id|dcmd
op_or
id|len
suffix:semicolon
id|dma
op_add_assign
id|len
suffix:semicolon
id|size
op_sub_assign
id|len
suffix:semicolon
r_if
c_cond
(paren
id|size
)paren
(brace
id|host-&gt;sg_cpu
(braket
id|i
)braket
dot
id|ddadr
op_assign
id|host-&gt;sg_dma
op_plus
(paren
id|i
op_plus
l_int|1
)paren
op_star
r_sizeof
(paren
r_struct
id|pxa_dma_desc
)paren
suffix:semicolon
)brace
r_else
(brace
id|host-&gt;sg_cpu
(braket
id|i
)braket
dot
id|ddadr
op_assign
id|DDADR_STOP
suffix:semicolon
)brace
)brace
id|wmb
c_func
(paren
)paren
suffix:semicolon
id|DDADR
c_func
(paren
id|host-&gt;dma
)paren
op_assign
id|host-&gt;sg_dma
suffix:semicolon
id|DCSR
c_func
(paren
id|host-&gt;dma
)paren
op_assign
id|DCSR_RUN
suffix:semicolon
)brace
DECL|function|pxamci_start_cmd
r_static
r_void
id|pxamci_start_cmd
c_func
(paren
r_struct
id|pxamci_host
op_star
id|host
comma
r_struct
id|mmc_command
op_star
id|cmd
comma
r_int
r_int
id|cmdat
)paren
(brace
id|WARN_ON
c_func
(paren
id|host-&gt;cmd
op_ne
l_int|NULL
)paren
suffix:semicolon
id|host-&gt;cmd
op_assign
id|cmd
suffix:semicolon
r_if
c_cond
(paren
id|cmd-&gt;flags
op_amp
id|MMC_RSP_BUSY
)paren
id|cmdat
op_or_assign
id|CMDAT_BUSY
suffix:semicolon
r_switch
c_cond
(paren
id|cmd-&gt;flags
op_amp
(paren
id|MMC_RSP_MASK
op_or
id|MMC_RSP_CRC
)paren
)paren
(brace
r_case
id|MMC_RSP_SHORT
op_or
id|MMC_RSP_CRC
suffix:colon
id|cmdat
op_or_assign
id|CMDAT_RESP_SHORT
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MMC_RSP_SHORT
suffix:colon
id|cmdat
op_or_assign
id|CMDAT_RESP_R3
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MMC_RSP_LONG
op_or
id|MMC_RSP_CRC
suffix:colon
id|cmdat
op_or_assign
id|CMDAT_RESP_R2
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
id|writel
c_func
(paren
id|cmd-&gt;opcode
comma
id|host-&gt;base
op_plus
id|MMC_CMD
)paren
suffix:semicolon
id|writel
c_func
(paren
id|cmd-&gt;arg
op_rshift
l_int|16
comma
id|host-&gt;base
op_plus
id|MMC_ARGH
)paren
suffix:semicolon
id|writel
c_func
(paren
id|cmd-&gt;arg
op_amp
l_int|0xffff
comma
id|host-&gt;base
op_plus
id|MMC_ARGL
)paren
suffix:semicolon
id|writel
c_func
(paren
id|cmdat
comma
id|host-&gt;base
op_plus
id|MMC_CMDAT
)paren
suffix:semicolon
id|writel
c_func
(paren
id|host-&gt;clkrt
comma
id|host-&gt;base
op_plus
id|MMC_CLKRT
)paren
suffix:semicolon
id|writel
c_func
(paren
id|START_CLOCK
comma
id|host-&gt;base
op_plus
id|MMC_STRPCL
)paren
suffix:semicolon
id|pxamci_enable_irq
c_func
(paren
id|host
comma
id|END_CMD_RES
)paren
suffix:semicolon
)brace
DECL|function|pxamci_finish_request
r_static
r_void
id|pxamci_finish_request
c_func
(paren
r_struct
id|pxamci_host
op_star
id|host
comma
r_struct
id|mmc_request
op_star
id|req
)paren
(brace
id|DBG
c_func
(paren
l_string|&quot;PXAMCI: request done&bslash;n&quot;
)paren
suffix:semicolon
id|host-&gt;req
op_assign
l_int|NULL
suffix:semicolon
id|host-&gt;cmd
op_assign
l_int|NULL
suffix:semicolon
id|host-&gt;data
op_assign
l_int|NULL
suffix:semicolon
id|mmc_request_done
c_func
(paren
id|host-&gt;mmc
comma
id|req
)paren
suffix:semicolon
)brace
DECL|function|pxamci_cmd_done
r_static
r_int
id|pxamci_cmd_done
c_func
(paren
r_struct
id|pxamci_host
op_star
id|host
comma
r_int
r_int
id|stat
)paren
(brace
r_struct
id|mmc_command
op_star
id|cmd
op_assign
id|host-&gt;cmd
suffix:semicolon
r_int
id|i
suffix:semicolon
id|u32
id|v
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cmd
)paren
r_return
l_int|0
suffix:semicolon
id|host-&gt;cmd
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/*&n;&t; * Did I mention this is Sick.  We always need to&n;&t; * discard the upper 8 bits of the first 16-bit word.&n;&t; */
id|v
op_assign
id|readl
c_func
(paren
id|host-&gt;base
op_plus
id|MMC_RES
)paren
op_amp
l_int|0xffff
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
l_int|4
suffix:semicolon
id|i
op_increment
)paren
(brace
id|u32
id|w1
op_assign
id|readl
c_func
(paren
id|host-&gt;base
op_plus
id|MMC_RES
)paren
op_amp
l_int|0xffff
suffix:semicolon
id|u32
id|w2
op_assign
id|readl
c_func
(paren
id|host-&gt;base
op_plus
id|MMC_RES
)paren
op_amp
l_int|0xffff
suffix:semicolon
id|cmd-&gt;resp
(braket
id|i
)braket
op_assign
id|v
op_lshift
l_int|24
op_or
id|w1
op_lshift
l_int|8
op_or
id|w2
op_rshift
l_int|8
suffix:semicolon
id|v
op_assign
id|w2
suffix:semicolon
)brace
r_if
c_cond
(paren
id|stat
op_amp
id|STAT_TIME_OUT_RESPONSE
)paren
(brace
id|cmd-&gt;error
op_assign
id|MMC_ERR_TIMEOUT
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|stat
op_amp
id|STAT_RES_CRC_ERR
op_logical_and
id|cmd-&gt;flags
op_amp
id|MMC_RSP_CRC
)paren
(brace
id|cmd-&gt;error
op_assign
id|MMC_ERR_BADCRC
suffix:semicolon
)brace
id|pxamci_disable_irq
c_func
(paren
id|host
comma
id|END_CMD_RES
)paren
suffix:semicolon
r_if
c_cond
(paren
id|host-&gt;data
op_logical_and
id|cmd-&gt;error
op_eq
id|MMC_ERR_NONE
)paren
(brace
id|pxamci_enable_irq
c_func
(paren
id|host
comma
id|DATA_TRAN_DONE
)paren
suffix:semicolon
)brace
r_else
(brace
id|pxamci_finish_request
c_func
(paren
id|host
comma
id|host-&gt;req
)paren
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|pxamci_data_done
r_static
r_int
id|pxamci_data_done
c_func
(paren
r_struct
id|pxamci_host
op_star
id|host
comma
r_int
r_int
id|stat
)paren
(brace
r_struct
id|mmc_data
op_star
id|data
op_assign
id|host-&gt;data
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|data
)paren
r_return
l_int|0
suffix:semicolon
id|DCSR
c_func
(paren
id|host-&gt;dma
)paren
op_assign
l_int|0
suffix:semicolon
id|dma_unmap_single
c_func
(paren
id|mmc_dev
c_func
(paren
id|host-&gt;mmc
)paren
comma
id|host-&gt;dma_buf
comma
id|host-&gt;dma_size
comma
id|host-&gt;dma_dir
)paren
suffix:semicolon
r_if
c_cond
(paren
id|stat
op_amp
id|STAT_READ_TIME_OUT
)paren
id|data-&gt;error
op_assign
id|MMC_ERR_TIMEOUT
suffix:semicolon
r_else
r_if
c_cond
(paren
id|stat
op_amp
(paren
id|STAT_CRC_READ_ERROR
op_or
id|STAT_CRC_WRITE_ERROR
)paren
)paren
id|data-&gt;error
op_assign
id|MMC_ERR_BADCRC
suffix:semicolon
id|data-&gt;bytes_xfered
op_assign
(paren
id|data-&gt;blocks
op_minus
id|readl
c_func
(paren
id|host-&gt;base
op_plus
id|MMC_NOB
)paren
)paren
op_lshift
id|data-&gt;blksz_bits
suffix:semicolon
id|pxamci_disable_irq
c_func
(paren
id|host
comma
id|DATA_TRAN_DONE
)paren
suffix:semicolon
id|host-&gt;data
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|host-&gt;req-&gt;stop
op_logical_and
id|data-&gt;error
op_eq
id|MMC_ERR_NONE
)paren
(brace
id|pxamci_stop_clock
c_func
(paren
id|host
)paren
suffix:semicolon
id|pxamci_start_cmd
c_func
(paren
id|host
comma
id|host-&gt;req-&gt;stop
comma
l_int|0
)paren
suffix:semicolon
)brace
r_else
(brace
id|pxamci_finish_request
c_func
(paren
id|host
comma
id|host-&gt;req
)paren
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|pxamci_irq
r_static
id|irqreturn_t
id|pxamci_irq
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|devid
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|pxamci_host
op_star
id|host
op_assign
id|devid
suffix:semicolon
r_int
r_int
id|ireg
suffix:semicolon
r_int
id|handled
op_assign
l_int|0
suffix:semicolon
id|ireg
op_assign
id|readl
c_func
(paren
id|host-&gt;base
op_plus
id|MMC_I_REG
)paren
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;PXAMCI: irq %08x&bslash;n&quot;
comma
id|ireg
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ireg
)paren
(brace
r_int
id|stat
op_assign
id|readl
c_func
(paren
id|host-&gt;base
op_plus
id|MMC_STAT
)paren
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;PXAMCI: stat %08x&bslash;n&quot;
comma
id|stat
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ireg
op_amp
id|END_CMD_RES
)paren
id|handled
op_or_assign
id|pxamci_cmd_done
c_func
(paren
id|host
comma
id|stat
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ireg
op_amp
id|DATA_TRAN_DONE
)paren
id|handled
op_or_assign
id|pxamci_data_done
c_func
(paren
id|host
comma
id|stat
)paren
suffix:semicolon
)brace
r_return
id|IRQ_RETVAL
c_func
(paren
id|handled
)paren
suffix:semicolon
)brace
DECL|function|pxamci_request
r_static
r_void
id|pxamci_request
c_func
(paren
r_struct
id|mmc_host
op_star
id|mmc
comma
r_struct
id|mmc_request
op_star
id|req
)paren
(brace
r_struct
id|pxamci_host
op_star
id|host
op_assign
id|mmc_priv
c_func
(paren
id|mmc
)paren
suffix:semicolon
r_int
r_int
id|cmdat
suffix:semicolon
id|WARN_ON
c_func
(paren
id|host-&gt;req
op_ne
l_int|NULL
)paren
suffix:semicolon
id|host-&gt;req
op_assign
id|req
suffix:semicolon
id|pxamci_stop_clock
c_func
(paren
id|host
)paren
suffix:semicolon
id|cmdat
op_assign
id|host-&gt;cmdat
suffix:semicolon
id|host-&gt;cmdat
op_and_assign
op_complement
id|CMDAT_INIT
suffix:semicolon
r_if
c_cond
(paren
id|req-&gt;data
)paren
(brace
id|pxamci_setup_data
c_func
(paren
id|host
comma
id|req-&gt;data
)paren
suffix:semicolon
id|cmdat
op_and_assign
op_complement
id|CMDAT_BUSY
suffix:semicolon
id|cmdat
op_or_assign
id|CMDAT_DATAEN
op_or
id|CMDAT_DMAEN
suffix:semicolon
r_if
c_cond
(paren
id|req-&gt;data-&gt;flags
op_amp
id|MMC_DATA_WRITE
)paren
id|cmdat
op_or_assign
id|CMDAT_WRITE
suffix:semicolon
r_if
c_cond
(paren
id|req-&gt;data-&gt;flags
op_amp
id|MMC_DATA_STREAM
)paren
id|cmdat
op_or_assign
id|CMDAT_STREAM
suffix:semicolon
)brace
id|pxamci_start_cmd
c_func
(paren
id|host
comma
id|req-&gt;cmd
comma
id|cmdat
)paren
suffix:semicolon
)brace
DECL|function|pxamci_set_ios
r_static
r_void
id|pxamci_set_ios
c_func
(paren
r_struct
id|mmc_host
op_star
id|mmc
comma
r_struct
id|mmc_ios
op_star
id|ios
)paren
(brace
r_struct
id|pxamci_host
op_star
id|host
op_assign
id|mmc_priv
c_func
(paren
id|mmc
)paren
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;pxamci_set_ios: clock %u power %u vdd %u.%02u&bslash;n&quot;
comma
id|ios-&gt;clock
comma
id|ios-&gt;power_mode
comma
id|ios-&gt;vdd
op_div
l_int|100
comma
id|ios-&gt;vdd
op_mod
l_int|100
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ios-&gt;clock
)paren
(brace
r_int
r_int
id|clk
op_assign
id|CLOCKRATE
op_div
id|ios-&gt;clock
suffix:semicolon
r_if
c_cond
(paren
id|CLOCKRATE
op_div
id|clk
OG
id|ios-&gt;clock
)paren
id|clk
op_lshift_assign
l_int|1
suffix:semicolon
id|host-&gt;clkrt
op_assign
id|fls
c_func
(paren
id|clk
)paren
op_minus
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t;&t; * we write clkrt on the next command&n;&t;&t; */
)brace
r_else
r_if
c_cond
(paren
id|readl
c_func
(paren
id|host-&gt;base
op_plus
id|MMC_STAT
)paren
op_amp
id|STAT_CLK_EN
)paren
(brace
multiline_comment|/*&n;&t;&t; * Ensure that the clock is off.&n;&t;&t; */
id|writel
c_func
(paren
id|STOP_CLOCK
comma
id|host-&gt;base
op_plus
id|MMC_STRPCL
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|host-&gt;power_mode
op_ne
id|ios-&gt;power_mode
)paren
(brace
id|host-&gt;power_mode
op_assign
id|ios-&gt;power_mode
suffix:semicolon
multiline_comment|/*&n;&t;&t; * power control?  none on the lubbock.&n;&t;&t; */
r_if
c_cond
(paren
id|ios-&gt;power_mode
op_eq
id|MMC_POWER_ON
)paren
id|host-&gt;cmdat
op_or_assign
id|CMDAT_INIT
suffix:semicolon
)brace
id|DBG
c_func
(paren
l_string|&quot;pxamci_set_ios: clkrt = %x cmdat = %x&bslash;n&quot;
comma
id|host-&gt;clkrt
comma
id|host-&gt;cmdat
)paren
suffix:semicolon
)brace
DECL|variable|pxamci_ops
r_static
r_struct
id|mmc_host_ops
id|pxamci_ops
op_assign
(brace
dot
id|request
op_assign
id|pxamci_request
comma
dot
id|set_ios
op_assign
id|pxamci_set_ios
comma
)brace
suffix:semicolon
DECL|function|platform_device_resource
r_static
r_struct
id|resource
op_star
id|platform_device_resource
c_func
(paren
r_struct
id|platform_device
op_star
id|dev
comma
r_int
r_int
id|mask
comma
r_int
id|nr
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
id|dev-&gt;num_resources
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|dev-&gt;resource
(braket
id|i
)braket
dot
id|flags
op_eq
id|mask
op_logical_and
id|nr
op_decrement
op_eq
l_int|0
)paren
r_return
op_amp
id|dev-&gt;resource
(braket
id|i
)braket
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|platform_device_irq
r_static
r_int
id|platform_device_irq
c_func
(paren
r_struct
id|platform_device
op_star
id|dev
comma
r_int
id|nr
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
id|dev-&gt;num_resources
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|dev-&gt;resource
(braket
id|i
)braket
dot
id|flags
op_eq
id|IORESOURCE_IRQ
op_logical_and
id|nr
op_decrement
op_eq
l_int|0
)paren
r_return
id|dev-&gt;resource
(braket
id|i
)braket
dot
id|start
suffix:semicolon
r_return
id|NO_IRQ
suffix:semicolon
)brace
DECL|function|pxamci_dma_irq
r_static
r_void
id|pxamci_dma_irq
c_func
(paren
r_int
id|dma
comma
r_void
op_star
id|devid
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;DMA%d: IRQ???&bslash;n&quot;
comma
id|dma
)paren
suffix:semicolon
id|DCSR
c_func
(paren
id|dma
)paren
op_assign
id|DCSR_STARTINTR
op_or
id|DCSR_ENDINTR
op_or
id|DCSR_BUSERR
suffix:semicolon
)brace
DECL|function|pxamci_probe
r_static
r_int
id|pxamci_probe
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_struct
id|platform_device
op_star
id|pdev
op_assign
id|to_platform_device
c_func
(paren
id|dev
)paren
suffix:semicolon
r_struct
id|mmc_host
op_star
id|mmc
suffix:semicolon
r_struct
id|pxamci_host
op_star
id|host
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|resource
op_star
id|r
suffix:semicolon
r_int
id|ret
comma
id|irq
suffix:semicolon
id|r
op_assign
id|platform_device_resource
c_func
(paren
id|pdev
comma
id|IORESOURCE_MEM
comma
l_int|0
)paren
suffix:semicolon
id|irq
op_assign
id|platform_device_irq
c_func
(paren
id|pdev
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|r
op_logical_or
id|irq
op_eq
id|NO_IRQ
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
id|r
op_assign
id|request_mem_region
c_func
(paren
id|r-&gt;start
comma
id|SZ_4K
comma
l_string|&quot;PXAMCI&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|r
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|mmc
op_assign
id|mmc_alloc_host
c_func
(paren
r_sizeof
(paren
r_struct
id|pxamci_host
)paren
comma
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mmc
)paren
(brace
id|ret
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|mmc-&gt;ops
op_assign
op_amp
id|pxamci_ops
suffix:semicolon
id|mmc-&gt;f_min
op_assign
l_int|312500
suffix:semicolon
id|mmc-&gt;f_max
op_assign
l_int|20000000
suffix:semicolon
id|mmc-&gt;ocr_avail
op_assign
id|MMC_VDD_32_33
suffix:semicolon
id|host
op_assign
id|mmc_priv
c_func
(paren
id|mmc
)paren
suffix:semicolon
id|host-&gt;mmc
op_assign
id|mmc
suffix:semicolon
id|host-&gt;dma
op_assign
op_minus
l_int|1
suffix:semicolon
id|host-&gt;sg_cpu
op_assign
id|dma_alloc_coherent
c_func
(paren
id|dev
comma
id|PAGE_SIZE
comma
op_amp
id|host-&gt;sg_dma
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|host-&gt;sg_cpu
)paren
(brace
id|ret
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|spin_lock_init
c_func
(paren
op_amp
id|host-&gt;lock
)paren
suffix:semicolon
id|host-&gt;res
op_assign
id|r
suffix:semicolon
id|host-&gt;irq
op_assign
id|irq
suffix:semicolon
id|host-&gt;imask
op_assign
id|TXFIFO_WR_REQ
op_or
id|RXFIFO_RD_REQ
op_or
id|CLK_IS_OFF
op_or
id|STOP_CMD
op_or
id|END_CMD_RES
op_or
id|PRG_DONE
op_or
id|DATA_TRAN_DONE
suffix:semicolon
id|host-&gt;base
op_assign
id|ioremap
c_func
(paren
id|r-&gt;start
comma
id|SZ_4K
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|host-&gt;base
)paren
(brace
id|ret
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Ensure that the host controller is shut down, and setup&n;&t; * with our defaults.&n;&t; */
id|pxamci_stop_clock
c_func
(paren
id|host
)paren
suffix:semicolon
id|writel
c_func
(paren
l_int|0
comma
id|host-&gt;base
op_plus
id|MMC_SPI
)paren
suffix:semicolon
id|writel
c_func
(paren
l_int|64
comma
id|host-&gt;base
op_plus
id|MMC_RESTO
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PREEMPT
macro_line|#error Not Preempt-safe
macro_line|#endif
id|pxa_gpio_mode
c_func
(paren
id|GPIO6_MMCCLK_MD
)paren
suffix:semicolon
id|pxa_gpio_mode
c_func
(paren
id|GPIO8_MMCCS0_MD
)paren
suffix:semicolon
id|CKEN
op_or_assign
id|CKEN12_MMC
suffix:semicolon
id|host-&gt;dma
op_assign
id|pxa_request_dma
c_func
(paren
l_string|&quot;PXAMCI&quot;
comma
id|DMA_PRIO_LOW
comma
id|pxamci_dma_irq
comma
id|host
)paren
suffix:semicolon
r_if
c_cond
(paren
id|host-&gt;dma
OL
l_int|0
)paren
(brace
id|ret
op_assign
op_minus
id|EBUSY
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|ret
op_assign
id|request_irq
c_func
(paren
id|host-&gt;irq
comma
id|pxamci_irq
comma
l_int|0
comma
l_string|&quot;PXAMCI&quot;
comma
id|host
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_goto
id|out
suffix:semicolon
id|dev_set_drvdata
c_func
(paren
id|dev
comma
id|host
)paren
suffix:semicolon
id|mmc_add_host
c_func
(paren
id|mmc
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|out
suffix:colon
r_if
c_cond
(paren
id|host
)paren
(brace
r_if
c_cond
(paren
id|host-&gt;dma
op_ge
l_int|0
)paren
id|pxa_free_dma
c_func
(paren
id|host-&gt;dma
)paren
suffix:semicolon
r_if
c_cond
(paren
id|host-&gt;base
)paren
id|iounmap
c_func
(paren
id|host-&gt;base
)paren
suffix:semicolon
r_if
c_cond
(paren
id|host-&gt;sg_cpu
)paren
id|dma_free_coherent
c_func
(paren
id|dev
comma
id|PAGE_SIZE
comma
id|host-&gt;sg_cpu
comma
id|host-&gt;sg_dma
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|mmc
)paren
id|mmc_free_host
c_func
(paren
id|mmc
)paren
suffix:semicolon
id|release_resource
c_func
(paren
id|r
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|pxamci_remove
r_static
r_int
id|pxamci_remove
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_struct
id|mmc_host
op_star
id|mmc
op_assign
id|dev_get_drvdata
c_func
(paren
id|dev
)paren
suffix:semicolon
id|dev_set_drvdata
c_func
(paren
id|dev
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mmc
)paren
(brace
r_struct
id|pxamci_host
op_star
id|host
op_assign
id|mmc_priv
c_func
(paren
id|mmc
)paren
suffix:semicolon
id|mmc_remove_host
c_func
(paren
id|mmc
)paren
suffix:semicolon
id|pxamci_stop_clock
c_func
(paren
id|host
)paren
suffix:semicolon
id|writel
c_func
(paren
id|TXFIFO_WR_REQ
op_or
id|RXFIFO_RD_REQ
op_or
id|CLK_IS_OFF
op_or
id|STOP_CMD
op_or
id|END_CMD_RES
op_or
id|PRG_DONE
op_or
id|DATA_TRAN_DONE
comma
id|host-&gt;base
op_plus
id|MMC_I_MASK
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|host-&gt;irq
comma
id|host
)paren
suffix:semicolon
id|pxa_free_dma
c_func
(paren
id|host-&gt;dma
)paren
suffix:semicolon
id|iounmap
c_func
(paren
id|host-&gt;base
)paren
suffix:semicolon
id|dma_free_coherent
c_func
(paren
id|dev
comma
id|PAGE_SIZE
comma
id|host-&gt;sg_cpu
comma
id|host-&gt;sg_dma
)paren
suffix:semicolon
id|release_resource
c_func
(paren
id|host-&gt;res
)paren
suffix:semicolon
id|mmc_free_host
c_func
(paren
id|mmc
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pxamci_suspend
r_static
r_int
id|pxamci_suspend
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
id|u32
id|state
comma
id|u32
id|level
)paren
(brace
r_struct
id|mmc_host
op_star
id|mmc
op_assign
id|dev_get_drvdata
c_func
(paren
id|dev
)paren
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|mmc
op_logical_and
id|level
op_eq
id|SUSPEND_DISABLE
)paren
id|ret
op_assign
id|mmc_suspend_host
c_func
(paren
id|mmc
comma
id|state
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|pxamci_resume
r_static
r_int
id|pxamci_resume
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
id|u32
id|level
)paren
(brace
r_struct
id|mmc_host
op_star
id|mmc
op_assign
id|dev_get_drvdata
c_func
(paren
id|dev
)paren
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|mmc
op_logical_and
id|level
op_eq
id|RESUME_ENABLE
)paren
id|ret
op_assign
id|mmc_resume_host
c_func
(paren
id|mmc
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|pxamci_driver
r_static
r_struct
id|device_driver
id|pxamci_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;pxamci&quot;
comma
dot
id|bus
op_assign
op_amp
id|platform_bus_type
comma
dot
id|probe
op_assign
id|pxamci_probe
comma
dot
id|remove
op_assign
id|pxamci_remove
comma
dot
id|suspend
op_assign
id|pxamci_suspend
comma
dot
id|resume
op_assign
id|pxamci_resume
comma
)brace
suffix:semicolon
DECL|function|pxamci_init
r_static
r_int
id|__init
id|pxamci_init
c_func
(paren
r_void
)paren
(brace
r_return
id|driver_register
c_func
(paren
op_amp
id|pxamci_driver
)paren
suffix:semicolon
)brace
DECL|function|pxamci_exit
r_static
r_void
id|__exit
id|pxamci_exit
c_func
(paren
r_void
)paren
(brace
id|driver_unregister
c_func
(paren
op_amp
id|pxamci_driver
)paren
suffix:semicolon
)brace
DECL|variable|pxamci_init
id|module_init
c_func
(paren
id|pxamci_init
)paren
suffix:semicolon
DECL|variable|pxamci_exit
id|module_exit
c_func
(paren
id|pxamci_exit
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;PXA Multimedia Card Interface Driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
