multiline_comment|/*&n; *  linux/drivers/acorn/scsi/eesox.c&n; *&n; *  Copyright (C) 1997-2003 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  This driver is based on experimentation.  Hence, it may have made&n; *  assumptions about the particular card that I have available, and&n; *  may not be reliable!&n; *&n; *  Changelog:&n; *   01-10-1997&t;RMK&t;&t;Created, READONLY version&n; *   15-02-1998&t;RMK&t;&t;READ/WRITE version&n; *&t;&t;&t;&t;added DMA support and hardware definitions&n; *   14-03-1998&t;RMK&t;&t;Updated DMA support&n; *&t;&t;&t;&t;Added terminator control&n; *   15-04-1998&t;RMK&t;&t;Only do PIO if FAS216 will allow it.&n; *   27-06-1998&t;RMK&t;&t;Changed asm/delay.h to linux/delay.h&n; *   02-04-2000&t;RMK&t;0.0.3&t;Fixed NO_IRQ/NO_DMA problem, updated for new&n; *&t;&t;&t;&t;error handling code.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/dma-mapping.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/ecard.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &quot;../../scsi/scsi.h&quot;
macro_line|#include &quot;../../scsi/hosts.h&quot;
macro_line|#include &quot;fas216.h&quot;
macro_line|#include &quot;scsi.h&quot;
macro_line|#include &lt;scsi/scsicam.h&gt;
DECL|macro|EESOX_FAS216_OFFSET
mdefine_line|#define EESOX_FAS216_OFFSET&t;0x3000
DECL|macro|EESOX_FAS216_SHIFT
mdefine_line|#define EESOX_FAS216_SHIFT&t;5
DECL|macro|EESOX_DMASTAT
mdefine_line|#define EESOX_DMASTAT&t;&t;0x2800
DECL|macro|EESOX_STAT_INTR
mdefine_line|#define EESOX_STAT_INTR&t;&t;0x01
DECL|macro|EESOX_STAT_DMA
mdefine_line|#define EESOX_STAT_DMA&t;&t;0x02
DECL|macro|EESOX_CONTROL
mdefine_line|#define EESOX_CONTROL&t;&t;0x2800
DECL|macro|EESOX_INTR_ENABLE
mdefine_line|#define EESOX_INTR_ENABLE&t;0x04
DECL|macro|EESOX_TERM_ENABLE
mdefine_line|#define EESOX_TERM_ENABLE&t;0x02
DECL|macro|EESOX_RESET
mdefine_line|#define EESOX_RESET&t;&t;0x01
DECL|macro|EESOX_DMADATA
mdefine_line|#define EESOX_DMADATA&t;&t;0x3800
DECL|macro|VERSION
mdefine_line|#define VERSION &quot;1.10 (17/01/2003 2.5.59)&quot;
multiline_comment|/*&n; * Use term=0,1,0,0,0 to turn terminators on/off&n; */
DECL|variable|term
r_static
r_int
id|term
(braket
id|MAX_ECARDS
)braket
op_assign
(brace
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|1
)brace
suffix:semicolon
DECL|macro|NR_SG
mdefine_line|#define NR_SG&t;256
DECL|struct|eesoxscsi_info
r_struct
id|eesoxscsi_info
(brace
DECL|member|info
id|FAS216_Info
id|info
suffix:semicolon
DECL|member|ec
r_struct
id|expansion_card
op_star
id|ec
suffix:semicolon
DECL|member|ctl_port
r_void
op_star
id|ctl_port
suffix:semicolon
DECL|member|control
r_int
r_int
id|control
suffix:semicolon
DECL|member|sg
r_struct
id|scatterlist
id|sg
(braket
id|NR_SG
)braket
suffix:semicolon
multiline_comment|/* Scatter DMA list&t;*/
)brace
suffix:semicolon
multiline_comment|/* Prototype: void eesoxscsi_irqenable(ec, irqnr)&n; * Purpose  : Enable interrupts on EESOX SCSI card&n; * Params   : ec    - expansion card structure&n; *          : irqnr - interrupt number&n; */
r_static
r_void
DECL|function|eesoxscsi_irqenable
id|eesoxscsi_irqenable
c_func
(paren
r_struct
id|expansion_card
op_star
id|ec
comma
r_int
id|irqnr
)paren
(brace
r_struct
id|eesoxscsi_info
op_star
id|info
op_assign
(paren
r_struct
id|eesoxscsi_info
op_star
)paren
id|ec-&gt;irq_data
suffix:semicolon
id|info-&gt;control
op_or_assign
id|EESOX_INTR_ENABLE
suffix:semicolon
id|writeb
c_func
(paren
id|info-&gt;control
comma
id|info-&gt;ctl_port
)paren
suffix:semicolon
)brace
multiline_comment|/* Prototype: void eesoxscsi_irqdisable(ec, irqnr)&n; * Purpose  : Disable interrupts on EESOX SCSI card&n; * Params   : ec    - expansion card structure&n; *          : irqnr - interrupt number&n; */
r_static
r_void
DECL|function|eesoxscsi_irqdisable
id|eesoxscsi_irqdisable
c_func
(paren
r_struct
id|expansion_card
op_star
id|ec
comma
r_int
id|irqnr
)paren
(brace
r_struct
id|eesoxscsi_info
op_star
id|info
op_assign
(paren
r_struct
id|eesoxscsi_info
op_star
)paren
id|ec-&gt;irq_data
suffix:semicolon
id|info-&gt;control
op_and_assign
op_complement
id|EESOX_INTR_ENABLE
suffix:semicolon
id|writeb
c_func
(paren
id|info-&gt;control
comma
id|info-&gt;ctl_port
)paren
suffix:semicolon
)brace
DECL|variable|eesoxscsi_ops
r_static
r_const
id|expansioncard_ops_t
id|eesoxscsi_ops
op_assign
(brace
dot
id|irqenable
op_assign
id|eesoxscsi_irqenable
comma
dot
id|irqdisable
op_assign
id|eesoxscsi_irqdisable
comma
)brace
suffix:semicolon
multiline_comment|/* Prototype: void eesoxscsi_terminator_ctl(*host, on_off)&n; * Purpose  : Turn the EESOX SCSI terminators on or off&n; * Params   : host   - card to turn on/off&n; *          : on_off - !0 to turn on, 0 to turn off&n; */
r_static
r_void
DECL|function|eesoxscsi_terminator_ctl
id|eesoxscsi_terminator_ctl
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|host
comma
r_int
id|on_off
)paren
(brace
r_struct
id|eesoxscsi_info
op_star
id|info
op_assign
(paren
r_struct
id|eesoxscsi_info
op_star
)paren
id|host-&gt;hostdata
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
id|host-&gt;host_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|on_off
)paren
id|info-&gt;control
op_or_assign
id|EESOX_TERM_ENABLE
suffix:semicolon
r_else
id|info-&gt;control
op_and_assign
op_complement
id|EESOX_TERM_ENABLE
suffix:semicolon
id|writeb
c_func
(paren
id|info-&gt;control
comma
id|info-&gt;ctl_port
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
id|host-&gt;host_lock
comma
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/* Prototype: void eesoxscsi_intr(irq, *dev_id, *regs)&n; * Purpose  : handle interrupts from EESOX SCSI card&n; * Params   : irq    - interrupt number&n; *&t;      dev_id - user-defined (Scsi_Host structure)&n; *&t;      regs   - processor registers at interrupt&n; */
r_static
r_void
DECL|function|eesoxscsi_intr
id|eesoxscsi_intr
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
id|eesoxscsi_info
op_star
id|info
op_assign
id|dev_id
suffix:semicolon
id|fas216_intr
c_func
(paren
op_amp
id|info-&gt;info
)paren
suffix:semicolon
)brace
multiline_comment|/* Prototype: fasdmatype_t eesoxscsi_dma_setup(host, SCpnt, direction, min_type)&n; * Purpose  : initialises DMA/PIO&n; * Params   : host      - host&n; *&t;      SCpnt     - command&n; *&t;      direction - DMA on to/off of card&n; *&t;      min_type  - minimum DMA support that we must have for this transfer&n; * Returns  : type of transfer to be performed&n; */
r_static
id|fasdmatype_t
DECL|function|eesoxscsi_dma_setup
id|eesoxscsi_dma_setup
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|host
comma
id|Scsi_Pointer
op_star
id|SCp
comma
id|fasdmadir_t
id|direction
comma
id|fasdmatype_t
id|min_type
)paren
(brace
r_struct
id|eesoxscsi_info
op_star
id|info
op_assign
(paren
r_struct
id|eesoxscsi_info
op_star
)paren
id|host-&gt;hostdata
suffix:semicolon
r_struct
id|device
op_star
id|dev
op_assign
id|scsi_get_device
c_func
(paren
id|host
)paren
suffix:semicolon
r_int
id|dmach
op_assign
id|host-&gt;dma_channel
suffix:semicolon
r_if
c_cond
(paren
id|dmach
op_ne
id|NO_DMA
op_logical_and
(paren
id|min_type
op_eq
id|fasdma_real_all
op_logical_or
id|SCp-&gt;this_residual
op_ge
l_int|512
)paren
)paren
(brace
r_int
id|bufs
comma
id|map_dir
comma
id|dma_dir
suffix:semicolon
id|bufs
op_assign
id|copy_SCp_to_sg
c_func
(paren
op_amp
id|info-&gt;sg
(braket
l_int|0
)braket
comma
id|SCp
comma
id|NR_SG
)paren
suffix:semicolon
r_if
c_cond
(paren
id|direction
op_eq
id|DMA_OUT
)paren
id|map_dir
op_assign
id|DMA_TO_DEVICE
comma
id|dma_dir
op_assign
id|DMA_MODE_WRITE
suffix:semicolon
r_else
id|map_dir
op_assign
id|DMA_FROM_DEVICE
comma
id|dma_dir
op_assign
id|DMA_MODE_READ
suffix:semicolon
id|dma_map_sg
c_func
(paren
id|dev
comma
id|info-&gt;sg
comma
id|bufs
op_plus
l_int|1
comma
id|map_dir
)paren
suffix:semicolon
id|disable_dma
c_func
(paren
id|dmach
)paren
suffix:semicolon
id|set_dma_sg
c_func
(paren
id|dmach
comma
id|info-&gt;sg
comma
id|bufs
op_plus
l_int|1
)paren
suffix:semicolon
id|set_dma_mode
c_func
(paren
id|dmach
comma
id|dma_dir
)paren
suffix:semicolon
id|enable_dma
c_func
(paren
id|dmach
)paren
suffix:semicolon
r_return
id|fasdma_real_all
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * We don&squot;t do DMA, we only do slow PIO&n;&t; *&n;&t; * Some day, we will do Pseudo DMA&n;&t; */
r_return
id|fasdma_pseudo
suffix:semicolon
)brace
DECL|function|eesoxscsi_buffer_in
r_static
r_void
id|eesoxscsi_buffer_in
c_func
(paren
r_void
op_star
id|buf
comma
r_int
id|length
comma
r_void
op_star
id|base
)paren
(brace
r_const
r_void
op_star
id|reg_fas
op_assign
id|base
op_plus
id|EESOX_FAS216_OFFSET
suffix:semicolon
r_const
r_void
op_star
id|reg_dmastat
op_assign
id|base
op_plus
id|EESOX_DMASTAT
suffix:semicolon
r_const
r_void
op_star
id|reg_dmadata
op_assign
id|base
op_plus
id|EESOX_DMADATA
suffix:semicolon
r_const
r_register
r_int
r_int
id|mask
op_assign
l_int|0xffff
suffix:semicolon
r_do
(brace
r_int
r_int
id|status
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Interrupt request?&n;&t;&t; */
id|status
op_assign
id|readb
c_func
(paren
id|reg_fas
op_plus
(paren
id|REG_STAT
op_lshift
id|EESOX_FAS216_SHIFT
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
id|STAT_INT
)paren
r_break
suffix:semicolon
multiline_comment|/*&n;&t;&t; * DMA request active?&n;&t;&t; */
id|status
op_assign
id|readb
c_func
(paren
id|reg_dmastat
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|status
op_amp
id|EESOX_STAT_DMA
)paren
)paren
r_continue
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Get number of bytes in FIFO&n;&t;&t; */
id|status
op_assign
id|readb
c_func
(paren
id|reg_fas
op_plus
(paren
id|REG_CFIS
op_lshift
id|EESOX_FAS216_SHIFT
)paren
)paren
op_amp
id|CFIS_CF
suffix:semicolon
r_if
c_cond
(paren
id|status
OG
l_int|16
)paren
id|status
op_assign
l_int|16
suffix:semicolon
r_if
c_cond
(paren
id|status
OG
id|length
)paren
id|status
op_assign
id|length
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Align buffer.&n;&t;&t; */
r_if
c_cond
(paren
(paren
(paren
id|u32
)paren
id|buf
)paren
op_amp
l_int|2
op_logical_and
id|status
op_ge
l_int|2
)paren
(brace
op_star
(paren
(paren
id|u16
op_star
)paren
id|buf
)paren
op_increment
op_assign
id|readl
c_func
(paren
id|reg_dmadata
)paren
suffix:semicolon
id|status
op_sub_assign
l_int|2
suffix:semicolon
id|length
op_sub_assign
l_int|2
suffix:semicolon
)brace
r_if
c_cond
(paren
id|status
op_ge
l_int|8
)paren
(brace
r_int
r_int
id|l1
comma
id|l2
suffix:semicolon
id|l1
op_assign
id|readl
c_func
(paren
id|reg_dmadata
)paren
op_amp
id|mask
suffix:semicolon
id|l1
op_or_assign
id|readl
c_func
(paren
id|reg_dmadata
)paren
op_lshift
l_int|16
suffix:semicolon
id|l2
op_assign
id|readl
c_func
(paren
id|reg_dmadata
)paren
op_amp
id|mask
suffix:semicolon
id|l2
op_or_assign
id|readl
c_func
(paren
id|reg_dmadata
)paren
op_lshift
l_int|16
suffix:semicolon
op_star
(paren
(paren
id|u32
op_star
)paren
id|buf
)paren
op_increment
op_assign
id|l1
suffix:semicolon
op_star
(paren
(paren
id|u32
op_star
)paren
id|buf
)paren
op_increment
op_assign
id|l2
suffix:semicolon
id|length
op_sub_assign
l_int|8
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|status
op_ge
l_int|4
)paren
(brace
r_int
r_int
id|l1
suffix:semicolon
id|l1
op_assign
id|readl
c_func
(paren
id|reg_dmadata
)paren
op_amp
id|mask
suffix:semicolon
id|l1
op_or_assign
id|readl
c_func
(paren
id|reg_dmadata
)paren
op_lshift
l_int|16
suffix:semicolon
op_star
(paren
(paren
id|u32
op_star
)paren
id|buf
)paren
op_increment
op_assign
id|l1
suffix:semicolon
id|length
op_sub_assign
l_int|4
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|status
op_ge
l_int|2
)paren
(brace
op_star
(paren
(paren
id|u16
op_star
)paren
id|buf
)paren
op_increment
op_assign
id|readl
c_func
(paren
id|reg_dmadata
)paren
suffix:semicolon
id|length
op_sub_assign
l_int|2
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
id|length
)paren
suffix:semicolon
)brace
DECL|function|eesoxscsi_buffer_out
r_static
r_void
id|eesoxscsi_buffer_out
c_func
(paren
r_void
op_star
id|buf
comma
r_int
id|length
comma
r_void
op_star
id|base
)paren
(brace
r_const
r_void
op_star
id|reg_fas
op_assign
id|base
op_plus
id|EESOX_FAS216_OFFSET
suffix:semicolon
r_const
r_void
op_star
id|reg_dmastat
op_assign
id|base
op_plus
id|EESOX_DMASTAT
suffix:semicolon
r_const
r_void
op_star
id|reg_dmadata
op_assign
id|base
op_plus
id|EESOX_DMADATA
suffix:semicolon
r_do
(brace
r_int
r_int
id|status
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Interrupt request?&n;&t;&t; */
id|status
op_assign
id|readb
c_func
(paren
id|reg_fas
op_plus
(paren
id|REG_STAT
op_lshift
id|EESOX_FAS216_SHIFT
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
id|STAT_INT
)paren
r_break
suffix:semicolon
multiline_comment|/*&n;&t;&t; * DMA request active?&n;&t;&t; */
id|status
op_assign
id|readb
c_func
(paren
id|reg_dmastat
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|status
op_amp
id|EESOX_STAT_DMA
)paren
)paren
r_continue
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Get number of bytes in FIFO&n;&t;&t; */
id|status
op_assign
id|readb
c_func
(paren
id|reg_fas
op_plus
(paren
id|REG_CFIS
op_lshift
id|EESOX_FAS216_SHIFT
)paren
)paren
op_amp
id|CFIS_CF
suffix:semicolon
r_if
c_cond
(paren
id|status
OG
l_int|16
)paren
id|status
op_assign
l_int|16
suffix:semicolon
id|status
op_assign
l_int|16
op_minus
id|status
suffix:semicolon
r_if
c_cond
(paren
id|status
OG
id|length
)paren
id|status
op_assign
id|length
suffix:semicolon
id|status
op_and_assign
op_complement
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Align buffer.&n;&t;&t; */
r_if
c_cond
(paren
(paren
(paren
id|u32
)paren
id|buf
)paren
op_amp
l_int|2
op_logical_and
id|status
op_ge
l_int|2
)paren
(brace
id|writel
c_func
(paren
op_star
(paren
(paren
id|u16
op_star
)paren
id|buf
)paren
op_increment
op_lshift
l_int|16
comma
id|reg_dmadata
)paren
suffix:semicolon
id|status
op_sub_assign
l_int|2
suffix:semicolon
id|length
op_sub_assign
l_int|2
suffix:semicolon
)brace
r_if
c_cond
(paren
id|status
op_ge
l_int|8
)paren
(brace
r_int
r_int
id|l1
comma
id|l2
suffix:semicolon
id|l1
op_assign
op_star
(paren
(paren
id|u32
op_star
)paren
id|buf
)paren
op_increment
suffix:semicolon
id|l2
op_assign
op_star
(paren
(paren
id|u32
op_star
)paren
id|buf
)paren
op_increment
suffix:semicolon
id|writel
c_func
(paren
id|l1
op_lshift
l_int|16
comma
id|reg_dmadata
)paren
suffix:semicolon
id|writel
c_func
(paren
id|l1
comma
id|reg_dmadata
)paren
suffix:semicolon
id|writel
c_func
(paren
id|l2
op_lshift
l_int|16
comma
id|reg_dmadata
)paren
suffix:semicolon
id|writel
c_func
(paren
id|l2
comma
id|reg_dmadata
)paren
suffix:semicolon
id|length
op_sub_assign
l_int|8
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|status
op_ge
l_int|4
)paren
(brace
r_int
r_int
id|l1
suffix:semicolon
id|l1
op_assign
op_star
(paren
(paren
id|u32
op_star
)paren
id|buf
)paren
op_increment
suffix:semicolon
id|writel
c_func
(paren
id|l1
op_lshift
l_int|16
comma
id|reg_dmadata
)paren
suffix:semicolon
id|writel
c_func
(paren
id|l1
comma
id|reg_dmadata
)paren
suffix:semicolon
id|length
op_sub_assign
l_int|4
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|status
op_ge
l_int|2
)paren
(brace
id|writel
c_func
(paren
op_star
(paren
(paren
id|u16
op_star
)paren
id|buf
)paren
op_increment
op_lshift
l_int|16
comma
id|reg_dmadata
)paren
suffix:semicolon
id|length
op_sub_assign
l_int|2
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
id|length
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|eesoxscsi_dma_pseudo
id|eesoxscsi_dma_pseudo
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|host
comma
id|Scsi_Pointer
op_star
id|SCp
comma
id|fasdmadir_t
id|dir
comma
r_int
id|transfer_size
)paren
(brace
r_void
op_star
id|base
op_assign
(paren
r_void
op_star
)paren
id|host-&gt;base
suffix:semicolon
r_if
c_cond
(paren
id|dir
op_eq
id|DMA_IN
)paren
(brace
id|eesoxscsi_buffer_in
c_func
(paren
id|SCp-&gt;ptr
comma
id|SCp-&gt;this_residual
comma
id|base
)paren
suffix:semicolon
)brace
r_else
(brace
id|eesoxscsi_buffer_out
c_func
(paren
id|SCp-&gt;ptr
comma
id|SCp-&gt;this_residual
comma
id|base
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Prototype: int eesoxscsi_dma_stop(host, SCpnt)&n; * Purpose  : stops DMA/PIO&n; * Params   : host  - host&n; *&t;      SCpnt - command&n; */
r_static
r_void
DECL|function|eesoxscsi_dma_stop
id|eesoxscsi_dma_stop
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|host
comma
id|Scsi_Pointer
op_star
id|SCp
)paren
(brace
r_if
c_cond
(paren
id|host-&gt;dma_channel
op_ne
id|NO_DMA
)paren
id|disable_dma
c_func
(paren
id|host-&gt;dma_channel
)paren
suffix:semicolon
)brace
multiline_comment|/* Prototype: const char *eesoxscsi_info(struct Scsi_Host * host)&n; * Purpose  : returns a descriptive string about this interface,&n; * Params   : host - driver host structure to return info for.&n; * Returns  : pointer to a static buffer containing null terminated string.&n; */
DECL|function|eesoxscsi_info
r_const
r_char
op_star
id|eesoxscsi_info
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|host
)paren
(brace
r_struct
id|eesoxscsi_info
op_star
id|info
op_assign
(paren
r_struct
id|eesoxscsi_info
op_star
)paren
id|host-&gt;hostdata
suffix:semicolon
r_static
r_char
id|string
(braket
l_int|150
)braket
suffix:semicolon
id|sprintf
c_func
(paren
id|string
comma
l_string|&quot;%s (%s) in slot %d v%s terminators o%s&quot;
comma
id|host-&gt;hostt-&gt;name
comma
id|info-&gt;info.scsi.type
comma
id|info-&gt;ec-&gt;slot_no
comma
id|VERSION
comma
id|info-&gt;control
op_amp
id|EESOX_TERM_ENABLE
ques
c_cond
l_string|&quot;n&quot;
suffix:colon
l_string|&quot;ff&quot;
)paren
suffix:semicolon
r_return
id|string
suffix:semicolon
)brace
multiline_comment|/* Prototype: int eesoxscsi_set_proc_info(struct Scsi_Host *host, char *buffer, int length)&n; * Purpose  : Set a driver specific function&n; * Params   : host   - host to setup&n; *          : buffer - buffer containing string describing operation&n; *          : length - length of string&n; * Returns  : -EINVAL, or 0&n; */
r_static
r_int
DECL|function|eesoxscsi_set_proc_info
id|eesoxscsi_set_proc_info
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|host
comma
r_char
op_star
id|buffer
comma
r_int
id|length
)paren
(brace
r_int
id|ret
op_assign
id|length
suffix:semicolon
r_if
c_cond
(paren
id|length
op_ge
l_int|9
op_logical_and
id|strncmp
c_func
(paren
id|buffer
comma
l_string|&quot;EESOXSCSI&quot;
comma
l_int|9
)paren
op_eq
l_int|0
)paren
(brace
id|buffer
op_add_assign
l_int|9
suffix:semicolon
id|length
op_sub_assign
l_int|9
suffix:semicolon
r_if
c_cond
(paren
id|length
op_ge
l_int|5
op_logical_and
id|strncmp
c_func
(paren
id|buffer
comma
l_string|&quot;term=&quot;
comma
l_int|5
)paren
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|buffer
(braket
l_int|5
)braket
op_eq
l_char|&squot;1&squot;
)paren
id|eesoxscsi_terminator_ctl
c_func
(paren
id|host
comma
l_int|1
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|buffer
(braket
l_int|5
)braket
op_eq
l_char|&squot;0&squot;
)paren
id|eesoxscsi_terminator_ctl
c_func
(paren
id|host
comma
l_int|0
)paren
suffix:semicolon
r_else
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
)brace
r_else
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
)brace
r_else
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/* Prototype: int eesoxscsi_proc_info(char *buffer, char **start, off_t offset,&n; *&t;&t;&t;&t;      int length, int host_no, int inout)&n; * Purpose  : Return information about the driver to a user process accessing&n; *&t;      the /proc filesystem.&n; * Params   : buffer - a buffer to write information to&n; *&t;      start  - a pointer into this buffer set by this routine to the start&n; *&t;&t;       of the required information.&n; *&t;      offset - offset into information that we have read upto.&n; *&t;      length - length of buffer&n; *&t;      host_no - host number to return information for&n; *&t;      inout  - 0 for reading, 1 for writing.&n; * Returns  : length of data written to buffer.&n; */
DECL|function|eesoxscsi_proc_info
r_int
id|eesoxscsi_proc_info
c_func
(paren
r_char
op_star
id|buffer
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|offset
comma
r_int
id|length
comma
r_int
id|host_no
comma
r_int
id|inout
)paren
(brace
r_int
id|pos
comma
id|begin
suffix:semicolon
r_struct
id|Scsi_Host
op_star
id|host
suffix:semicolon
r_struct
id|eesoxscsi_info
op_star
id|info
suffix:semicolon
id|Scsi_Device
op_star
id|scd
suffix:semicolon
id|host
op_assign
id|scsi_host_hn_get
c_func
(paren
id|host_no
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|host
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|inout
op_eq
l_int|1
)paren
r_return
id|eesoxscsi_set_proc_info
c_func
(paren
id|host
comma
id|buffer
comma
id|length
)paren
suffix:semicolon
id|info
op_assign
(paren
r_struct
id|eesoxscsi_info
op_star
)paren
id|host-&gt;hostdata
suffix:semicolon
id|begin
op_assign
l_int|0
suffix:semicolon
id|pos
op_assign
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;EESOX SCSI driver v%s&bslash;n&quot;
comma
id|VERSION
)paren
suffix:semicolon
id|pos
op_add_assign
id|fas216_print_host
c_func
(paren
op_amp
id|info-&gt;info
comma
id|buffer
op_plus
id|pos
)paren
suffix:semicolon
id|pos
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|pos
comma
l_string|&quot;Term    : o%s&bslash;n&quot;
comma
id|info-&gt;control
op_amp
id|EESOX_TERM_ENABLE
ques
c_cond
l_string|&quot;n&quot;
suffix:colon
l_string|&quot;ff&quot;
)paren
suffix:semicolon
id|pos
op_add_assign
id|fas216_print_stats
c_func
(paren
op_amp
id|info-&gt;info
comma
id|buffer
op_plus
id|pos
)paren
suffix:semicolon
op_star
id|start
op_assign
id|buffer
op_plus
(paren
id|offset
op_minus
id|begin
)paren
suffix:semicolon
id|pos
op_sub_assign
id|offset
op_minus
id|begin
suffix:semicolon
r_if
c_cond
(paren
id|pos
OG
id|length
)paren
id|pos
op_assign
id|length
suffix:semicolon
r_return
id|pos
suffix:semicolon
)brace
DECL|function|eesoxscsi_show_term
r_static
id|ssize_t
id|eesoxscsi_show_term
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_char
op_star
id|buf
)paren
(brace
r_struct
id|expansion_card
op_star
id|ec
op_assign
id|ECARD_DEV
c_func
(paren
id|dev
)paren
suffix:semicolon
r_struct
id|Scsi_Host
op_star
id|host
op_assign
id|ecard_get_drvdata
c_func
(paren
id|ec
)paren
suffix:semicolon
r_struct
id|eesoxscsi_info
op_star
id|info
op_assign
(paren
r_struct
id|eesoxscsi_info
op_star
)paren
id|host-&gt;hostdata
suffix:semicolon
r_return
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;%d&bslash;n&quot;
comma
id|info-&gt;control
op_amp
id|EESOX_TERM_ENABLE
ques
c_cond
l_int|1
suffix:colon
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|eesoxscsi_store_term
r_static
id|ssize_t
id|eesoxscsi_store_term
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|len
)paren
(brace
r_struct
id|expansion_card
op_star
id|ec
op_assign
id|ECARD_DEV
c_func
(paren
id|dev
)paren
suffix:semicolon
r_struct
id|Scsi_Host
op_star
id|host
op_assign
id|ecard_get_drvdata
c_func
(paren
id|ec
)paren
suffix:semicolon
r_struct
id|eesoxscsi_info
op_star
id|info
op_assign
(paren
r_struct
id|eesoxscsi_info
op_star
)paren
id|host-&gt;hostdata
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
l_int|1
)paren
(brace
id|spin_lock_irqsave
c_func
(paren
id|host-&gt;host_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buf
(braket
l_int|0
)braket
op_ne
l_char|&squot;0&squot;
)paren
(brace
id|info-&gt;control
op_or_assign
id|EESOX_TERM_ENABLE
suffix:semicolon
)brace
r_else
(brace
id|info-&gt;control
op_and_assign
op_complement
id|EESOX_TERM_ENABLE
suffix:semicolon
)brace
id|writeb
c_func
(paren
id|info-&gt;control
comma
id|info-&gt;ctl_port
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
id|host-&gt;host_lock
comma
id|flags
)paren
suffix:semicolon
)brace
r_return
id|len
suffix:semicolon
)brace
r_static
id|DEVICE_ATTR
c_func
(paren
id|bus_term
comma
id|S_IRUGO
op_or
id|S_IWUSR
comma
id|eesoxscsi_show_term
comma
id|eesoxscsi_store_term
)paren
suffix:semicolon
DECL|variable|eesox_template
r_static
id|Scsi_Host_Template
id|eesox_template
op_assign
(brace
dot
id|module
op_assign
id|THIS_MODULE
comma
dot
id|proc_info
op_assign
id|eesoxscsi_proc_info
comma
dot
id|name
op_assign
l_string|&quot;EESOX SCSI&quot;
comma
dot
id|info
op_assign
id|eesoxscsi_info
comma
dot
id|command
op_assign
id|fas216_command
comma
dot
id|queuecommand
op_assign
id|fas216_queue_command
comma
dot
id|eh_host_reset_handler
op_assign
id|fas216_eh_host_reset
comma
dot
id|eh_bus_reset_handler
op_assign
id|fas216_eh_bus_reset
comma
dot
id|eh_device_reset_handler
op_assign
id|fas216_eh_device_reset
comma
dot
id|eh_abort_handler
op_assign
id|fas216_eh_abort
comma
dot
id|can_queue
op_assign
l_int|1
comma
dot
id|this_id
op_assign
l_int|7
comma
dot
id|sg_tablesize
op_assign
id|SG_ALL
comma
dot
id|cmd_per_lun
op_assign
l_int|1
comma
dot
id|use_clustering
op_assign
id|DISABLE_CLUSTERING
comma
dot
id|proc_name
op_assign
l_string|&quot;eesox&quot;
comma
)brace
suffix:semicolon
r_static
r_int
id|__devinit
DECL|function|eesoxscsi_probe
id|eesoxscsi_probe
c_func
(paren
r_struct
id|expansion_card
op_star
id|ec
comma
r_const
r_struct
id|ecard_id
op_star
id|id
)paren
(brace
r_struct
id|Scsi_Host
op_star
id|host
suffix:semicolon
r_struct
id|eesoxscsi_info
op_star
id|info
suffix:semicolon
r_int
r_int
id|resbase
comma
id|reslen
suffix:semicolon
r_int
r_char
op_star
id|base
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|resbase
op_assign
id|ecard_resource_start
c_func
(paren
id|ec
comma
id|ECARD_RES_IOCFAST
)paren
suffix:semicolon
id|reslen
op_assign
id|ecard_resource_len
c_func
(paren
id|ec
comma
id|ECARD_RES_IOCFAST
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|request_mem_region
c_func
(paren
id|resbase
comma
id|reslen
comma
l_string|&quot;eesoxscsi&quot;
)paren
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
id|base
op_assign
id|ioremap
c_func
(paren
id|resbase
comma
id|reslen
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|base
)paren
(brace
id|ret
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|out_region
suffix:semicolon
)brace
id|host
op_assign
id|scsi_register
c_func
(paren
op_amp
id|eesox_template
comma
r_sizeof
(paren
r_struct
id|eesoxscsi_info
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|host
)paren
(brace
id|ret
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|out_unmap
suffix:semicolon
)brace
id|host-&gt;base
op_assign
(paren
r_int
r_int
)paren
id|base
suffix:semicolon
id|host-&gt;irq
op_assign
id|ec-&gt;irq
suffix:semicolon
id|host-&gt;dma_channel
op_assign
id|ec-&gt;dma
suffix:semicolon
id|ecard_set_drvdata
c_func
(paren
id|ec
comma
id|host
)paren
suffix:semicolon
id|info
op_assign
(paren
r_struct
id|eesoxscsi_info
op_star
)paren
id|host-&gt;hostdata
suffix:semicolon
id|info-&gt;ec
op_assign
id|ec
suffix:semicolon
id|info-&gt;ctl_port
op_assign
id|base
op_plus
id|EESOX_CONTROL
suffix:semicolon
id|info-&gt;control
op_assign
id|term
(braket
id|ec-&gt;slot_no
)braket
ques
c_cond
id|EESOX_TERM_ENABLE
suffix:colon
l_int|0
suffix:semicolon
id|writeb
c_func
(paren
id|info-&gt;control
comma
id|info-&gt;ctl_port
)paren
suffix:semicolon
id|ec-&gt;irqaddr
op_assign
id|base
op_plus
id|EESOX_DMASTAT
suffix:semicolon
id|ec-&gt;irqmask
op_assign
id|EESOX_STAT_INTR
suffix:semicolon
id|ec-&gt;irq_data
op_assign
id|info
suffix:semicolon
id|ec-&gt;ops
op_assign
op_amp
id|eesoxscsi_ops
suffix:semicolon
id|info-&gt;info.scsi.io_base
op_assign
id|base
op_plus
id|EESOX_FAS216_OFFSET
suffix:semicolon
id|info-&gt;info.scsi.io_shift
op_assign
id|EESOX_FAS216_SHIFT
suffix:semicolon
id|info-&gt;info.scsi.irq
op_assign
id|host-&gt;irq
suffix:semicolon
id|info-&gt;info.ifcfg.clockrate
op_assign
l_int|40
suffix:semicolon
multiline_comment|/* MHz */
id|info-&gt;info.ifcfg.select_timeout
op_assign
l_int|255
suffix:semicolon
id|info-&gt;info.ifcfg.asyncperiod
op_assign
l_int|200
suffix:semicolon
multiline_comment|/* ns */
id|info-&gt;info.ifcfg.sync_max_depth
op_assign
l_int|7
suffix:semicolon
id|info-&gt;info.ifcfg.cntl3
op_assign
id|CNTL3_FASTSCSI
op_or
id|CNTL3_FASTCLK
suffix:semicolon
id|info-&gt;info.ifcfg.disconnect_ok
op_assign
l_int|1
suffix:semicolon
id|info-&gt;info.ifcfg.wide_max_size
op_assign
l_int|0
suffix:semicolon
id|info-&gt;info.ifcfg.capabilities
op_assign
id|FASCAP_PSEUDODMA
suffix:semicolon
id|info-&gt;info.dma.setup
op_assign
id|eesoxscsi_dma_setup
suffix:semicolon
id|info-&gt;info.dma.pseudo
op_assign
id|eesoxscsi_dma_pseudo
suffix:semicolon
id|info-&gt;info.dma.stop
op_assign
id|eesoxscsi_dma_stop
suffix:semicolon
id|device_create_file
c_func
(paren
op_amp
id|ec-&gt;dev
comma
op_amp
id|dev_attr_bus_term
)paren
suffix:semicolon
id|ret
op_assign
id|fas216_init
c_func
(paren
id|host
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_goto
id|out_free
suffix:semicolon
id|ret
op_assign
id|request_irq
c_func
(paren
id|host-&gt;irq
comma
id|eesoxscsi_intr
comma
l_int|0
comma
l_string|&quot;eesoxscsi&quot;
comma
id|info
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;scsi%d: IRQ%d not free: %d&bslash;n&quot;
comma
id|host-&gt;host_no
comma
id|host-&gt;irq
comma
id|ret
)paren
suffix:semicolon
r_goto
id|out_remove
suffix:semicolon
)brace
r_if
c_cond
(paren
id|host-&gt;dma_channel
op_ne
id|NO_DMA
)paren
(brace
r_if
c_cond
(paren
id|request_dma
c_func
(paren
id|host-&gt;dma_channel
comma
l_string|&quot;eesox&quot;
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;scsi%d: DMA%d not free, DMA disabled&bslash;n&quot;
comma
id|host-&gt;host_no
comma
id|host-&gt;dma_channel
)paren
suffix:semicolon
id|host-&gt;dma_channel
op_assign
id|NO_DMA
suffix:semicolon
)brace
r_else
(brace
id|set_dma_speed
c_func
(paren
id|host-&gt;dma_channel
comma
l_int|180
)paren
suffix:semicolon
id|info-&gt;info.ifcfg.capabilities
op_or_assign
id|FASCAP_DMA
suffix:semicolon
id|info-&gt;info.ifcfg.cntl3
op_or_assign
id|CNTL3_BS8
suffix:semicolon
)brace
)brace
id|ret
op_assign
id|fas216_add
c_func
(paren
id|host
comma
op_amp
id|ec-&gt;dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
l_int|0
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|host-&gt;dma_channel
op_ne
id|NO_DMA
)paren
id|free_dma
c_func
(paren
id|host-&gt;dma_channel
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
id|out_remove
suffix:colon
id|fas216_remove
c_func
(paren
id|host
)paren
suffix:semicolon
id|out_free
suffix:colon
id|device_remove_file
c_func
(paren
op_amp
id|ec-&gt;dev
comma
op_amp
id|dev_attr_bus_term
)paren
suffix:semicolon
id|scsi_unregister
c_func
(paren
id|host
)paren
suffix:semicolon
id|out_unmap
suffix:colon
id|iounmap
c_func
(paren
id|base
)paren
suffix:semicolon
id|out_region
suffix:colon
id|release_mem_region
c_func
(paren
id|resbase
comma
id|reslen
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|eesoxscsi_remove
r_static
r_void
id|__devexit
id|eesoxscsi_remove
c_func
(paren
r_struct
id|expansion_card
op_star
id|ec
)paren
(brace
r_struct
id|Scsi_Host
op_star
id|host
op_assign
id|ecard_get_drvdata
c_func
(paren
id|ec
)paren
suffix:semicolon
r_struct
id|eesoxscsi_info
op_star
id|info
op_assign
(paren
r_struct
id|eesoxscsi_info
op_star
)paren
id|host-&gt;hostdata
suffix:semicolon
r_int
r_int
id|resbase
comma
id|reslen
suffix:semicolon
id|ecard_set_drvdata
c_func
(paren
id|ec
comma
l_int|NULL
)paren
suffix:semicolon
id|fas216_remove
c_func
(paren
id|host
)paren
suffix:semicolon
r_if
c_cond
(paren
id|host-&gt;dma_channel
op_ne
id|NO_DMA
)paren
id|free_dma
c_func
(paren
id|host-&gt;dma_channel
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|host-&gt;irq
comma
id|info
)paren
suffix:semicolon
id|device_remove_file
c_func
(paren
op_amp
id|ec-&gt;dev
comma
op_amp
id|dev_attr_bus_term
)paren
suffix:semicolon
id|iounmap
c_func
(paren
(paren
r_void
op_star
)paren
id|host-&gt;base
)paren
suffix:semicolon
id|resbase
op_assign
id|ecard_resource_start
c_func
(paren
id|ec
comma
id|ECARD_RES_IOCFAST
)paren
suffix:semicolon
id|reslen
op_assign
id|ecard_resource_len
c_func
(paren
id|ec
comma
id|ECARD_RES_IOCFAST
)paren
suffix:semicolon
id|release_mem_region
c_func
(paren
id|resbase
comma
id|reslen
)paren
suffix:semicolon
id|fas216_release
c_func
(paren
id|host
)paren
suffix:semicolon
id|scsi_unregister
c_func
(paren
id|host
)paren
suffix:semicolon
)brace
DECL|variable|eesoxscsi_cids
r_static
r_const
r_struct
id|ecard_id
id|eesoxscsi_cids
(braket
)braket
op_assign
(brace
(brace
id|MANU_EESOX
comma
id|PROD_EESOX_SCSI2
)brace
comma
(brace
l_int|0xffff
comma
l_int|0xffff
)brace
comma
)brace
suffix:semicolon
DECL|variable|eesoxscsi_driver
r_static
r_struct
id|ecard_driver
id|eesoxscsi_driver
op_assign
(brace
dot
id|probe
op_assign
id|eesoxscsi_probe
comma
dot
id|remove
op_assign
id|__devexit_p
c_func
(paren
id|eesoxscsi_remove
)paren
comma
dot
id|id_table
op_assign
id|eesoxscsi_cids
comma
dot
id|drv
op_assign
(brace
dot
id|devclass
op_assign
op_amp
id|shost_devclass
comma
dot
id|name
op_assign
l_string|&quot;eesoxscsi&quot;
comma
)brace
comma
)brace
suffix:semicolon
DECL|function|eesox_init
r_static
r_int
id|__init
id|eesox_init
c_func
(paren
r_void
)paren
(brace
r_return
id|ecard_register_driver
c_func
(paren
op_amp
id|eesoxscsi_driver
)paren
suffix:semicolon
)brace
DECL|function|eesox_exit
r_static
r_void
id|__exit
id|eesox_exit
c_func
(paren
r_void
)paren
(brace
id|ecard_remove_driver
c_func
(paren
op_amp
id|eesoxscsi_driver
)paren
suffix:semicolon
)brace
DECL|variable|eesox_init
id|module_init
c_func
(paren
id|eesox_init
)paren
suffix:semicolon
DECL|variable|eesox_exit
id|module_exit
c_func
(paren
id|eesox_exit
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Russell King&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;EESOX &squot;Fast&squot; SCSI driver for Acorn machines&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|term
comma
l_string|&quot;1-8i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|term
comma
l_string|&quot;SCSI bus termination&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
