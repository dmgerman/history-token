multiline_comment|/*&n; *  linux/drivers/mmc/mmci.c - ARM PrimeCell MMCI PL180/1 driver&n; *&n; *  Copyright (C) 2003 Deep Blue Solutions, Ltd, All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/moduleparam.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/err.h&gt;
macro_line|#include &lt;linux/mmc/host.h&gt;
macro_line|#include &lt;linux/mmc/protocol.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/hardware/amba.h&gt;
macro_line|#include &lt;asm/hardware/clock.h&gt;
macro_line|#include &lt;asm/mach/mmc.h&gt;
macro_line|#include &quot;mmci.h&quot;
DECL|macro|DRIVER_NAME
mdefine_line|#define DRIVER_NAME &quot;mmci-pl18x&quot;
macro_line|#ifdef CONFIG_MMC_DEBUG
DECL|macro|DBG
mdefine_line|#define DBG(host,fmt,args...)&t;&bslash;&n;&t;pr_debug(&quot;%s: %s: &quot; fmt, host-&gt;mmc-&gt;host_name, __func__ , args)
macro_line|#else
DECL|macro|DBG
mdefine_line|#define DBG(host,fmt,args...)&t;do { } while (0)
macro_line|#endif
DECL|variable|fmax
r_static
r_int
r_int
id|fmax
op_assign
l_int|515633
suffix:semicolon
r_static
r_void
DECL|function|mmci_request_end
id|mmci_request_end
c_func
(paren
r_struct
id|mmci_host
op_star
id|host
comma
r_struct
id|mmc_request
op_star
id|mrq
)paren
(brace
id|writel
c_func
(paren
l_int|0
comma
id|host-&gt;base
op_plus
id|MMCICOMMAND
)paren
suffix:semicolon
id|host-&gt;mrq
op_assign
l_int|NULL
suffix:semicolon
id|host-&gt;cmd
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|mrq-&gt;data
)paren
id|mrq-&gt;data-&gt;bytes_xfered
op_assign
id|host-&gt;data_xfered
suffix:semicolon
multiline_comment|/*&n;&t; * Need to drop the host lock here; mmc_request_done may call&n;&t; * back into the driver...&n;&t; */
id|spin_unlock
c_func
(paren
op_amp
id|host-&gt;lock
)paren
suffix:semicolon
id|mmc_request_done
c_func
(paren
id|host-&gt;mmc
comma
id|mrq
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|host-&gt;lock
)paren
suffix:semicolon
)brace
DECL|function|mmci_stop_data
r_static
r_void
id|mmci_stop_data
c_func
(paren
r_struct
id|mmci_host
op_star
id|host
)paren
(brace
id|writel
c_func
(paren
l_int|0
comma
id|host-&gt;base
op_plus
id|MMCIDATACTRL
)paren
suffix:semicolon
id|writel
c_func
(paren
l_int|0
comma
id|host-&gt;base
op_plus
id|MMCIMASK1
)paren
suffix:semicolon
id|host-&gt;data
op_assign
l_int|NULL
suffix:semicolon
id|host-&gt;buffer
op_assign
l_int|NULL
suffix:semicolon
)brace
DECL|function|mmci_start_data
r_static
r_void
id|mmci_start_data
c_func
(paren
r_struct
id|mmci_host
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
id|datactrl
comma
id|timeout
comma
id|irqmask
suffix:semicolon
r_void
op_star
id|base
suffix:semicolon
id|DBG
c_func
(paren
id|host
comma
l_string|&quot;blksz %04x blks %04x flags %08x&bslash;n&quot;
comma
l_int|1
op_lshift
id|data-&gt;blksz_bits
comma
id|data-&gt;blocks
comma
id|data-&gt;flags
)paren
suffix:semicolon
id|host-&gt;data
op_assign
id|data
suffix:semicolon
id|host-&gt;buffer
op_assign
id|data-&gt;req-&gt;buffer
suffix:semicolon
id|host-&gt;size
op_assign
id|data-&gt;blocks
op_lshift
id|data-&gt;blksz_bits
suffix:semicolon
id|host-&gt;data_xfered
op_assign
l_int|0
suffix:semicolon
id|timeout
op_assign
id|data-&gt;timeout_clks
op_plus
(paren
(paren
r_int
r_int
r_int
)paren
id|data-&gt;timeout_ns
op_star
id|host-&gt;cclk
)paren
op_div
l_int|1000000000ULL
suffix:semicolon
id|base
op_assign
id|host-&gt;base
suffix:semicolon
id|writel
c_func
(paren
id|timeout
comma
id|base
op_plus
id|MMCIDATATIMER
)paren
suffix:semicolon
id|writel
c_func
(paren
id|host-&gt;size
comma
id|base
op_plus
id|MMCIDATALENGTH
)paren
suffix:semicolon
id|datactrl
op_assign
id|MCI_DPSM_ENABLE
op_or
id|data-&gt;blksz_bits
op_lshift
l_int|4
suffix:semicolon
r_if
c_cond
(paren
id|data-&gt;flags
op_amp
id|MMC_DATA_READ
)paren
(brace
id|datactrl
op_or_assign
id|MCI_DPSM_DIRECTION
suffix:semicolon
id|irqmask
op_assign
id|MCI_RXFIFOHALFFULLMASK
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t; * We don&squot;t actually need to include &quot;FIFO empty&quot; here&n;&t;&t; * since its implicit in &quot;FIFO half empty&quot;.&n;&t;&t; */
id|irqmask
op_assign
id|MCI_TXFIFOHALFEMPTYMASK
suffix:semicolon
)brace
id|writel
c_func
(paren
id|datactrl
comma
id|base
op_plus
id|MMCIDATACTRL
)paren
suffix:semicolon
id|writel
c_func
(paren
id|readl
c_func
(paren
id|base
op_plus
id|MMCIMASK0
)paren
op_amp
op_complement
id|MCI_DATAENDMASK
comma
id|base
op_plus
id|MMCIMASK0
)paren
suffix:semicolon
id|writel
c_func
(paren
id|irqmask
comma
id|base
op_plus
id|MMCIMASK1
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|mmci_start_command
id|mmci_start_command
c_func
(paren
r_struct
id|mmci_host
op_star
id|host
comma
r_struct
id|mmc_command
op_star
id|cmd
comma
id|u32
id|c
)paren
(brace
r_void
op_star
id|base
op_assign
id|host-&gt;base
suffix:semicolon
id|DBG
c_func
(paren
id|host
comma
l_string|&quot;op %02x arg %08x flags %08x&bslash;n&quot;
comma
id|cmd-&gt;opcode
comma
id|cmd-&gt;arg
comma
id|cmd-&gt;flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|readl
c_func
(paren
id|base
op_plus
id|MMCICOMMAND
)paren
op_amp
id|MCI_CPSM_ENABLE
)paren
(brace
id|writel
c_func
(paren
l_int|0
comma
id|base
op_plus
id|MMCICOMMAND
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
)brace
id|c
op_or_assign
id|cmd-&gt;opcode
op_or
id|MCI_CPSM_ENABLE
suffix:semicolon
r_switch
c_cond
(paren
id|cmd-&gt;flags
op_amp
id|MMC_RSP_MASK
)paren
(brace
r_case
id|MMC_RSP_NONE
suffix:colon
r_default
suffix:colon
r_break
suffix:semicolon
r_case
id|MMC_RSP_LONG
suffix:colon
id|c
op_or_assign
id|MCI_CPSM_LONGRSP
suffix:semicolon
r_case
id|MMC_RSP_SHORT
suffix:colon
id|c
op_or_assign
id|MCI_CPSM_RESPONSE
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
multiline_comment|/*interrupt*/
l_int|0
)paren
id|c
op_or_assign
id|MCI_CPSM_INTERRUPT
suffix:semicolon
id|host-&gt;cmd
op_assign
id|cmd
suffix:semicolon
id|writel
c_func
(paren
id|cmd-&gt;arg
comma
id|base
op_plus
id|MMCIARGUMENT
)paren
suffix:semicolon
id|writel
c_func
(paren
id|c
comma
id|base
op_plus
id|MMCICOMMAND
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|mmci_data_irq
id|mmci_data_irq
c_func
(paren
r_struct
id|mmci_host
op_star
id|host
comma
r_struct
id|mmc_data
op_star
id|data
comma
r_int
r_int
id|status
)paren
(brace
r_if
c_cond
(paren
id|status
op_amp
id|MCI_DATABLOCKEND
)paren
(brace
id|host-&gt;data_xfered
op_add_assign
l_int|1
op_lshift
id|data-&gt;blksz_bits
suffix:semicolon
)brace
r_if
c_cond
(paren
id|status
op_amp
(paren
id|MCI_DATACRCFAIL
op_or
id|MCI_DATATIMEOUT
op_or
id|MCI_TXUNDERRUN
op_or
id|MCI_RXOVERRUN
)paren
)paren
(brace
r_if
c_cond
(paren
id|status
op_amp
id|MCI_DATACRCFAIL
)paren
id|data-&gt;error
op_assign
id|MMC_ERR_BADCRC
suffix:semicolon
r_else
r_if
c_cond
(paren
id|status
op_amp
id|MCI_DATATIMEOUT
)paren
id|data-&gt;error
op_assign
id|MMC_ERR_TIMEOUT
suffix:semicolon
r_else
r_if
c_cond
(paren
id|status
op_amp
(paren
id|MCI_TXUNDERRUN
op_or
id|MCI_RXOVERRUN
)paren
)paren
id|data-&gt;error
op_assign
id|MMC_ERR_FIFO
suffix:semicolon
id|status
op_or_assign
id|MCI_DATAEND
suffix:semicolon
)brace
r_if
c_cond
(paren
id|status
op_amp
id|MCI_DATAEND
)paren
(brace
id|mmci_stop_data
c_func
(paren
id|host
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|data-&gt;stop
)paren
(brace
id|mmci_request_end
c_func
(paren
id|host
comma
id|data-&gt;mrq
)paren
suffix:semicolon
)brace
r_else
(brace
id|mmci_start_command
c_func
(paren
id|host
comma
id|data-&gt;stop
comma
l_int|0
)paren
suffix:semicolon
)brace
)brace
)brace
r_static
r_void
DECL|function|mmci_cmd_irq
id|mmci_cmd_irq
c_func
(paren
r_struct
id|mmci_host
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
id|status
)paren
(brace
r_void
op_star
id|base
op_assign
id|host-&gt;base
suffix:semicolon
id|host-&gt;cmd
op_assign
l_int|NULL
suffix:semicolon
id|cmd-&gt;resp
(braket
l_int|0
)braket
op_assign
id|readl
c_func
(paren
id|base
op_plus
id|MMCIRESPONSE0
)paren
suffix:semicolon
id|cmd-&gt;resp
(braket
l_int|1
)braket
op_assign
id|readl
c_func
(paren
id|base
op_plus
id|MMCIRESPONSE1
)paren
suffix:semicolon
id|cmd-&gt;resp
(braket
l_int|2
)braket
op_assign
id|readl
c_func
(paren
id|base
op_plus
id|MMCIRESPONSE2
)paren
suffix:semicolon
id|cmd-&gt;resp
(braket
l_int|3
)braket
op_assign
id|readl
c_func
(paren
id|base
op_plus
id|MMCIRESPONSE3
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
id|MCI_CMDTIMEOUT
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
id|status
op_amp
id|MCI_CMDCRCFAIL
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
r_if
c_cond
(paren
op_logical_neg
id|cmd-&gt;data
op_logical_or
id|cmd-&gt;error
op_ne
id|MMC_ERR_NONE
)paren
(brace
id|mmci_request_end
c_func
(paren
id|host
comma
id|cmd-&gt;mrq
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
(paren
id|cmd-&gt;data-&gt;flags
op_amp
id|MMC_DATA_READ
)paren
)paren
(brace
id|mmci_start_data
c_func
(paren
id|host
comma
id|cmd-&gt;data
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * PIO data transfer IRQ handler.&n; */
DECL|function|mmci_pio_irq
r_static
id|irqreturn_t
id|mmci_pio_irq
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
r_struct
id|mmci_host
op_star
id|host
op_assign
id|dev_id
suffix:semicolon
r_void
op_star
id|base
op_assign
id|host-&gt;base
suffix:semicolon
id|u32
id|status
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_do
(brace
id|status
op_assign
id|readl
c_func
(paren
id|base
op_plus
id|MMCISTATUS
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|status
op_amp
(paren
id|MCI_RXDATAAVLBL
op_or
id|MCI_RXFIFOHALFFULL
op_or
id|MCI_TXFIFOHALFEMPTY
)paren
)paren
)paren
r_break
suffix:semicolon
id|DBG
c_func
(paren
id|host
comma
l_string|&quot;irq1 %08x&bslash;n&quot;
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
id|MCI_RXDATAAVLBL
op_or
id|MCI_RXFIFOHALFFULL
)paren
)paren
(brace
r_int
r_int
id|count
op_assign
id|host-&gt;size
op_minus
(paren
id|readl
c_func
(paren
id|base
op_plus
id|MMCIFIFOCNT
)paren
op_lshift
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|count
OL
l_int|0
)paren
id|count
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|count
op_logical_and
id|host-&gt;buffer
)paren
(brace
id|readsl
c_func
(paren
id|base
op_plus
id|MMCIFIFO
comma
id|host-&gt;buffer
comma
id|count
op_rshift
l_int|2
)paren
suffix:semicolon
id|host-&gt;buffer
op_add_assign
id|count
suffix:semicolon
id|host-&gt;size
op_sub_assign
id|count
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t;&t; * We only need to test the half-empty flag here - if&n;&t;&t; * the FIFO is completely empty, then by definition&n;&t;&t; * it is more than half empty.&n;&t;&t; */
r_if
c_cond
(paren
id|status
op_amp
id|MCI_TXFIFOHALFEMPTY
)paren
(brace
r_int
r_int
id|maxcnt
op_assign
id|status
op_amp
id|MCI_TXFIFOEMPTY
ques
c_cond
id|MCI_FIFOSIZE
suffix:colon
id|MCI_FIFOHALFSIZE
suffix:semicolon
r_int
r_int
id|count
op_assign
id|min
c_func
(paren
id|host-&gt;size
comma
id|maxcnt
)paren
suffix:semicolon
id|writesl
c_func
(paren
id|base
op_plus
id|MMCIFIFO
comma
id|host-&gt;buffer
comma
id|count
op_rshift
l_int|2
)paren
suffix:semicolon
id|host-&gt;buffer
op_add_assign
id|count
suffix:semicolon
id|host-&gt;size
op_sub_assign
id|count
suffix:semicolon
)brace
id|ret
op_assign
l_int|1
suffix:semicolon
)brace
r_while
c_loop
(paren
id|status
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * If we run out of data, disable the data IRQs; this&n;&t; * prevents a race where the FIFO becomes empty before&n;&t; * the chip itself has disabled the data path, and&n;&t; * stops us racing with our data end IRQ.&n;&t; */
r_if
c_cond
(paren
id|host-&gt;size
op_eq
l_int|0
)paren
(brace
id|writel
c_func
(paren
l_int|0
comma
id|base
op_plus
id|MMCIMASK1
)paren
suffix:semicolon
id|writel
c_func
(paren
id|readl
c_func
(paren
id|base
op_plus
id|MMCIMASK0
)paren
op_or
id|MCI_DATAENDMASK
comma
id|base
op_plus
id|MMCIMASK0
)paren
suffix:semicolon
)brace
r_return
id|IRQ_RETVAL
c_func
(paren
id|ret
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Handle completion of command and data transfers.&n; */
DECL|function|mmci_irq
r_static
id|irqreturn_t
id|mmci_irq
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
r_struct
id|mmci_host
op_star
id|host
op_assign
id|dev_id
suffix:semicolon
id|u32
id|status
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|host-&gt;lock
)paren
suffix:semicolon
r_do
(brace
r_struct
id|mmc_command
op_star
id|cmd
suffix:semicolon
r_struct
id|mmc_data
op_star
id|data
suffix:semicolon
id|status
op_assign
id|readl
c_func
(paren
id|host-&gt;base
op_plus
id|MMCISTATUS
)paren
suffix:semicolon
id|status
op_and_assign
id|readl
c_func
(paren
id|host-&gt;base
op_plus
id|MMCIMASK0
)paren
suffix:semicolon
id|writel
c_func
(paren
id|status
comma
id|host-&gt;base
op_plus
id|MMCICLEAR
)paren
suffix:semicolon
id|DBG
c_func
(paren
id|host
comma
l_string|&quot;irq0 %08x&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
id|data
op_assign
id|host-&gt;data
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
(paren
id|MCI_DATACRCFAIL
op_or
id|MCI_DATATIMEOUT
op_or
id|MCI_TXUNDERRUN
op_or
id|MCI_RXOVERRUN
op_or
id|MCI_DATAEND
op_or
id|MCI_DATABLOCKEND
)paren
op_logical_and
id|data
)paren
id|mmci_data_irq
c_func
(paren
id|host
comma
id|data
comma
id|status
)paren
suffix:semicolon
id|cmd
op_assign
id|host-&gt;cmd
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
(paren
id|MCI_CMDCRCFAIL
op_or
id|MCI_CMDTIMEOUT
op_or
id|MCI_CMDSENT
op_or
id|MCI_CMDRESPEND
)paren
op_logical_and
id|cmd
)paren
id|mmci_cmd_irq
c_func
(paren
id|host
comma
id|cmd
comma
id|status
)paren
suffix:semicolon
id|ret
op_assign
l_int|1
suffix:semicolon
)brace
r_while
c_loop
(paren
id|status
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|host-&gt;lock
)paren
suffix:semicolon
r_return
id|IRQ_RETVAL
c_func
(paren
id|ret
)paren
suffix:semicolon
)brace
DECL|function|mmci_request
r_static
r_void
id|mmci_request
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
id|mrq
)paren
(brace
r_struct
id|mmci_host
op_star
id|host
op_assign
id|mmc_priv
c_func
(paren
id|mmc
)paren
suffix:semicolon
id|WARN_ON
c_func
(paren
id|host-&gt;mrq
op_ne
l_int|NULL
)paren
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|host-&gt;lock
)paren
suffix:semicolon
id|host-&gt;mrq
op_assign
id|mrq
suffix:semicolon
r_if
c_cond
(paren
id|mrq-&gt;data
op_logical_and
id|mrq-&gt;data-&gt;flags
op_amp
id|MMC_DATA_READ
)paren
id|mmci_start_data
c_func
(paren
id|host
comma
id|mrq-&gt;data
)paren
suffix:semicolon
id|mmci_start_command
c_func
(paren
id|host
comma
id|mrq-&gt;cmd
comma
l_int|0
)paren
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|host-&gt;lock
)paren
suffix:semicolon
)brace
DECL|function|mmci_set_ios
r_static
r_void
id|mmci_set_ios
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
id|mmci_host
op_star
id|host
op_assign
id|mmc_priv
c_func
(paren
id|mmc
)paren
suffix:semicolon
id|u32
id|clk
op_assign
l_int|0
comma
id|pwr
op_assign
l_int|0
suffix:semicolon
id|DBG
c_func
(paren
id|host
comma
l_string|&quot;clock %uHz busmode %u powermode %u Vdd %u&bslash;n&quot;
comma
id|ios-&gt;clock
comma
id|ios-&gt;bus_mode
comma
id|ios-&gt;power_mode
comma
id|ios-&gt;vdd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ios-&gt;clock
)paren
(brace
r_if
c_cond
(paren
id|ios-&gt;clock
op_ge
id|host-&gt;mclk
)paren
(brace
id|clk
op_assign
id|MCI_CLK_BYPASS
suffix:semicolon
id|host-&gt;cclk
op_assign
id|host-&gt;mclk
suffix:semicolon
)brace
r_else
(brace
id|clk
op_assign
id|host-&gt;mclk
op_div
(paren
l_int|2
op_star
id|ios-&gt;clock
)paren
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|clk
OG
l_int|256
)paren
id|clk
op_assign
l_int|255
suffix:semicolon
id|host-&gt;cclk
op_assign
id|host-&gt;mclk
op_div
(paren
l_int|2
op_star
(paren
id|clk
op_plus
l_int|1
)paren
)paren
suffix:semicolon
)brace
id|clk
op_or_assign
id|MCI_CLK_ENABLE
suffix:semicolon
)brace
r_if
c_cond
(paren
id|host-&gt;plat-&gt;translate_vdd
)paren
id|pwr
op_or_assign
id|host-&gt;plat
op_member_access_from_pointer
id|translate_vdd
c_func
(paren
id|mmc_dev
c_func
(paren
id|mmc
)paren
comma
id|ios-&gt;vdd
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|ios-&gt;power_mode
)paren
(brace
r_case
id|MMC_POWER_OFF
suffix:colon
r_break
suffix:semicolon
r_case
id|MMC_POWER_UP
suffix:colon
id|pwr
op_or_assign
id|MCI_PWR_UP
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MMC_POWER_ON
suffix:colon
id|pwr
op_or_assign
id|MCI_PWR_ON
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ios-&gt;bus_mode
op_eq
id|MMC_BUSMODE_OPENDRAIN
)paren
id|pwr
op_or_assign
id|MCI_ROD
suffix:semicolon
id|writel
c_func
(paren
id|clk
comma
id|host-&gt;base
op_plus
id|MMCICLOCK
)paren
suffix:semicolon
r_if
c_cond
(paren
id|host-&gt;pwr
op_ne
id|pwr
)paren
(brace
id|host-&gt;pwr
op_assign
id|pwr
suffix:semicolon
id|writel
c_func
(paren
id|pwr
comma
id|host-&gt;base
op_plus
id|MMCIPOWER
)paren
suffix:semicolon
)brace
)brace
DECL|variable|mmci_ops
r_static
r_struct
id|mmc_host_ops
id|mmci_ops
op_assign
(brace
dot
id|request
op_assign
id|mmci_request
comma
dot
id|set_ios
op_assign
id|mmci_set_ios
comma
)brace
suffix:semicolon
DECL|function|mmci_check_status
r_static
r_void
id|mmci_check_status
c_func
(paren
r_int
r_int
id|data
)paren
(brace
r_struct
id|mmci_host
op_star
id|host
op_assign
(paren
r_struct
id|mmci_host
op_star
)paren
id|data
suffix:semicolon
r_int
r_int
id|status
suffix:semicolon
id|status
op_assign
id|host-&gt;plat
op_member_access_from_pointer
id|status
c_func
(paren
id|mmc_dev
c_func
(paren
id|host-&gt;mmc
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_xor
id|host-&gt;oldstat
)paren
id|mmc_detect_change
c_func
(paren
id|host-&gt;mmc
)paren
suffix:semicolon
id|host-&gt;oldstat
op_assign
id|status
suffix:semicolon
id|mod_timer
c_func
(paren
op_amp
id|host-&gt;timer
comma
id|jiffies
op_plus
id|HZ
)paren
suffix:semicolon
)brace
DECL|function|mmci_probe
r_static
r_int
id|mmci_probe
c_func
(paren
r_struct
id|amba_device
op_star
id|dev
comma
r_void
op_star
id|id
)paren
(brace
r_struct
id|mmc_platform_data
op_star
id|plat
op_assign
id|dev-&gt;dev.platform_data
suffix:semicolon
r_struct
id|mmci_host
op_star
id|host
suffix:semicolon
r_struct
id|mmc_host
op_star
id|mmc
suffix:semicolon
r_int
id|ret
suffix:semicolon
multiline_comment|/* must have platform data */
r_if
c_cond
(paren
op_logical_neg
id|plat
)paren
(brace
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|ret
op_assign
id|amba_request_regions
c_func
(paren
id|dev
comma
id|DRIVER_NAME
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
id|mmc
op_assign
id|mmc_alloc_host
c_func
(paren
r_sizeof
(paren
r_struct
id|mmci_host
)paren
comma
op_amp
id|dev-&gt;dev
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
id|rel_regions
suffix:semicolon
)brace
id|host
op_assign
id|mmc_priv
c_func
(paren
id|mmc
)paren
suffix:semicolon
id|host-&gt;clk
op_assign
id|clk_get
c_func
(paren
op_amp
id|dev-&gt;dev
comma
l_string|&quot;MCLK&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|host-&gt;clk
)paren
)paren
(brace
id|ret
op_assign
id|PTR_ERR
c_func
(paren
id|host-&gt;clk
)paren
suffix:semicolon
id|host-&gt;clk
op_assign
l_int|NULL
suffix:semicolon
r_goto
id|host_free
suffix:semicolon
)brace
id|ret
op_assign
id|clk_use
c_func
(paren
id|host-&gt;clk
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_goto
id|clk_free
suffix:semicolon
id|ret
op_assign
id|clk_enable
c_func
(paren
id|host-&gt;clk
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_goto
id|clk_unuse
suffix:semicolon
id|host-&gt;plat
op_assign
id|plat
suffix:semicolon
id|host-&gt;mclk
op_assign
id|clk_get_rate
c_func
(paren
id|host-&gt;clk
)paren
suffix:semicolon
id|host-&gt;mmc
op_assign
id|mmc
suffix:semicolon
id|host-&gt;base
op_assign
id|ioremap
c_func
(paren
id|dev-&gt;res.start
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
id|clk_disable
suffix:semicolon
)brace
id|mmc-&gt;ops
op_assign
op_amp
id|mmci_ops
suffix:semicolon
id|mmc-&gt;f_min
op_assign
(paren
id|host-&gt;mclk
op_plus
l_int|511
)paren
op_div
l_int|512
suffix:semicolon
id|mmc-&gt;f_max
op_assign
id|min
c_func
(paren
id|host-&gt;mclk
comma
id|fmax
)paren
suffix:semicolon
id|mmc-&gt;ocr_avail
op_assign
id|plat-&gt;ocr_mask
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|host-&gt;lock
)paren
suffix:semicolon
id|writel
c_func
(paren
l_int|0
comma
id|host-&gt;base
op_plus
id|MMCIMASK0
)paren
suffix:semicolon
id|writel
c_func
(paren
l_int|0
comma
id|host-&gt;base
op_plus
id|MMCIMASK1
)paren
suffix:semicolon
id|writel
c_func
(paren
l_int|0xfff
comma
id|host-&gt;base
op_plus
id|MMCICLEAR
)paren
suffix:semicolon
id|ret
op_assign
id|request_irq
c_func
(paren
id|dev-&gt;irq
(braket
l_int|0
)braket
comma
id|mmci_irq
comma
id|SA_SHIRQ
comma
id|DRIVER_NAME
l_string|&quot; (cmd)&quot;
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
id|unmap
suffix:semicolon
id|ret
op_assign
id|request_irq
c_func
(paren
id|dev-&gt;irq
(braket
l_int|1
)braket
comma
id|mmci_pio_irq
comma
id|SA_SHIRQ
comma
id|DRIVER_NAME
l_string|&quot; (pio)&quot;
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
id|irq0_free
suffix:semicolon
id|writel
c_func
(paren
id|MCI_IRQENABLE
comma
id|host-&gt;base
op_plus
id|MMCIMASK0
)paren
suffix:semicolon
id|amba_set_drvdata
c_func
(paren
id|dev
comma
id|mmc
)paren
suffix:semicolon
id|mmc_add_host
c_func
(paren
id|mmc
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: MMCI rev %x cfg %02x at 0x%08lx irq %d,%d&bslash;n&quot;
comma
id|mmc-&gt;host_name
comma
id|amba_rev
c_func
(paren
id|dev
)paren
comma
id|amba_config
c_func
(paren
id|dev
)paren
comma
id|dev-&gt;res.start
comma
id|dev-&gt;irq
(braket
l_int|0
)braket
comma
id|dev-&gt;irq
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|init_timer
c_func
(paren
op_amp
id|host-&gt;timer
)paren
suffix:semicolon
id|host-&gt;timer.data
op_assign
(paren
r_int
r_int
)paren
id|host
suffix:semicolon
id|host-&gt;timer.function
op_assign
id|mmci_check_status
suffix:semicolon
id|host-&gt;timer.expires
op_assign
id|jiffies
op_plus
id|HZ
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|host-&gt;timer
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|irq0_free
suffix:colon
id|free_irq
c_func
(paren
id|dev-&gt;irq
(braket
l_int|0
)braket
comma
id|host
)paren
suffix:semicolon
id|unmap
suffix:colon
id|iounmap
c_func
(paren
id|host-&gt;base
)paren
suffix:semicolon
id|clk_disable
suffix:colon
id|clk_disable
c_func
(paren
id|host-&gt;clk
)paren
suffix:semicolon
id|clk_unuse
suffix:colon
id|clk_unuse
c_func
(paren
id|host-&gt;clk
)paren
suffix:semicolon
id|clk_free
suffix:colon
id|clk_put
c_func
(paren
id|host-&gt;clk
)paren
suffix:semicolon
id|host_free
suffix:colon
id|mmc_free_host
c_func
(paren
id|mmc
)paren
suffix:semicolon
id|rel_regions
suffix:colon
id|amba_release_regions
c_func
(paren
id|dev
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|mmci_remove
r_static
r_int
id|mmci_remove
c_func
(paren
r_struct
id|amba_device
op_star
id|dev
)paren
(brace
r_struct
id|mmc_host
op_star
id|mmc
op_assign
id|amba_get_drvdata
c_func
(paren
id|dev
)paren
suffix:semicolon
id|amba_set_drvdata
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
id|mmci_host
op_star
id|host
op_assign
id|mmc_priv
c_func
(paren
id|mmc
)paren
suffix:semicolon
id|del_timer_sync
c_func
(paren
op_amp
id|host-&gt;timer
)paren
suffix:semicolon
id|mmc_remove_host
c_func
(paren
id|mmc
)paren
suffix:semicolon
id|writel
c_func
(paren
l_int|0
comma
id|host-&gt;base
op_plus
id|MMCIMASK0
)paren
suffix:semicolon
id|writel
c_func
(paren
l_int|0
comma
id|host-&gt;base
op_plus
id|MMCIMASK1
)paren
suffix:semicolon
id|writel
c_func
(paren
l_int|0
comma
id|host-&gt;base
op_plus
id|MMCICOMMAND
)paren
suffix:semicolon
id|writel
c_func
(paren
l_int|0
comma
id|host-&gt;base
op_plus
id|MMCIDATACTRL
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|dev-&gt;irq
(braket
l_int|0
)braket
comma
id|host
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|dev-&gt;irq
(braket
l_int|1
)braket
comma
id|host
)paren
suffix:semicolon
id|iounmap
c_func
(paren
id|host-&gt;base
)paren
suffix:semicolon
id|clk_disable
c_func
(paren
id|host-&gt;clk
)paren
suffix:semicolon
id|clk_unuse
c_func
(paren
id|host-&gt;clk
)paren
suffix:semicolon
id|clk_put
c_func
(paren
id|host-&gt;clk
)paren
suffix:semicolon
id|mmc_free_host
c_func
(paren
id|mmc
)paren
suffix:semicolon
id|amba_release_regions
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_PM
DECL|function|mmci_suspend
r_static
r_int
id|mmci_suspend
c_func
(paren
r_struct
id|amba_device
op_star
id|dev
comma
id|u32
id|state
)paren
(brace
r_struct
id|mmc_host
op_star
id|mmc
op_assign
id|amba_get_drvdata
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
)paren
(brace
r_struct
id|mmci_host
op_star
id|host
op_assign
id|mmc_priv
c_func
(paren
id|mmc
)paren
suffix:semicolon
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
r_if
c_cond
(paren
id|ret
op_eq
l_int|0
)paren
id|writel
c_func
(paren
l_int|0
comma
id|host-&gt;base
op_plus
id|MMCIMASK0
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|mmci_resume
r_static
r_int
id|mmci_resume
c_func
(paren
r_struct
id|amba_device
op_star
id|dev
)paren
(brace
r_struct
id|mmc_host
op_star
id|mmc
op_assign
id|amba_get_drvdata
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
)paren
(brace
r_struct
id|mmci_host
op_star
id|host
op_assign
id|mmc_priv
c_func
(paren
id|mmc
)paren
suffix:semicolon
id|writel
c_func
(paren
id|MCI_IRQENABLE
comma
id|host-&gt;base
op_plus
id|MMCIMASK0
)paren
suffix:semicolon
id|ret
op_assign
id|mmc_resume_host
c_func
(paren
id|mmc
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
macro_line|#else
DECL|macro|mmci_suspend
mdefine_line|#define mmci_suspend&t;NULL
DECL|macro|mmci_resume
mdefine_line|#define mmci_resume&t;NULL
macro_line|#endif
DECL|variable|mmci_ids
r_static
r_struct
id|amba_id
id|mmci_ids
(braket
)braket
op_assign
(brace
(brace
dot
id|id
op_assign
l_int|0x00041180
comma
dot
id|mask
op_assign
l_int|0x000fffff
comma
)brace
comma
(brace
dot
id|id
op_assign
l_int|0x00041181
comma
dot
id|mask
op_assign
l_int|0x000fffff
comma
)brace
comma
(brace
l_int|0
comma
l_int|0
)brace
comma
)brace
suffix:semicolon
DECL|variable|mmci_driver
r_static
r_struct
id|amba_driver
id|mmci_driver
op_assign
(brace
dot
id|drv
op_assign
(brace
dot
id|name
op_assign
id|DRIVER_NAME
comma
)brace
comma
dot
id|probe
op_assign
id|mmci_probe
comma
dot
id|remove
op_assign
id|mmci_remove
comma
dot
id|suspend
op_assign
id|mmci_suspend
comma
dot
id|resume
op_assign
id|mmci_resume
comma
dot
id|id_table
op_assign
id|mmci_ids
comma
)brace
suffix:semicolon
DECL|function|mmci_init
r_static
r_int
id|__init
id|mmci_init
c_func
(paren
r_void
)paren
(brace
r_return
id|amba_driver_register
c_func
(paren
op_amp
id|mmci_driver
)paren
suffix:semicolon
)brace
DECL|function|mmci_exit
r_static
r_void
id|__exit
id|mmci_exit
c_func
(paren
r_void
)paren
(brace
id|amba_driver_unregister
c_func
(paren
op_amp
id|mmci_driver
)paren
suffix:semicolon
)brace
DECL|variable|mmci_init
id|module_init
c_func
(paren
id|mmci_init
)paren
suffix:semicolon
DECL|variable|mmci_exit
id|module_exit
c_func
(paren
id|mmci_exit
)paren
suffix:semicolon
id|module_param
c_func
(paren
id|fmax
comma
id|uint
comma
l_int|0444
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;ARM PrimeCell PL180/181 Multimedia Card Interface driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
