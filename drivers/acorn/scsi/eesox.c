multiline_comment|/*&n; *  linux/drivers/acorn/scsi/eesox.c&n; *&n; *  Copyright (C) 1997-2000 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  This driver is based on experimentation.  Hence, it may have made&n; *  assumptions about the particular card that I have available, and&n; *  may not be reliable!&n; *&n; *  Changelog:&n; *   01-10-1997&t;RMK&t;&t;Created, READONLY version&n; *   15-02-1998&t;RMK&t;&t;READ/WRITE version&n; *&t;&t;&t;&t;added DMA support and hardware definitions&n; *   14-03-1998&t;RMK&t;&t;Updated DMA support&n; *&t;&t;&t;&t;Added terminator control&n; *   15-04-1998&t;RMK&t;&t;Only do PIO if FAS216 will allow it.&n; *   27-06-1998&t;RMK&t;&t;Changed asm/delay.h to linux/delay.h&n; *   02-04-2000&t;RMK&t;0.0.3&t;Fixed NO_IRQ/NO_DMA problem, updated for new&n; *&t;&t;&t;&t;error handling code.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/ecard.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &quot;../../scsi/sd.h&quot;
macro_line|#include &quot;../../scsi/hosts.h&quot;
macro_line|#include &quot;fas216.h&quot;
macro_line|#include &lt;scsi/scsicam.h&gt;
multiline_comment|/* Configuration */
DECL|macro|EESOX_XTALFREQ
mdefine_line|#define EESOX_XTALFREQ&t;&t;40
DECL|macro|EESOX_ASYNC_PERIOD
mdefine_line|#define EESOX_ASYNC_PERIOD&t;200
DECL|macro|EESOX_SYNC_DEPTH
mdefine_line|#define EESOX_SYNC_DEPTH&t;7
multiline_comment|/*&n; * List of devices that the driver will recognise&n; */
DECL|macro|EESOXSCSI_LIST
mdefine_line|#define EESOXSCSI_LIST&t;{ MANU_EESOX, PROD_EESOX_SCSI2 }
DECL|macro|EESOX_FAS216_OFFSET
mdefine_line|#define EESOX_FAS216_OFFSET&t;0xc00
DECL|macro|EESOX_FAS216_SHIFT
mdefine_line|#define EESOX_FAS216_SHIFT&t;3
DECL|macro|EESOX_STATUS
mdefine_line|#define EESOX_STATUS&t;&t;0xa00
DECL|macro|EESOX_STAT_INTR
mdefine_line|#define EESOX_STAT_INTR&t;&t;0x01
DECL|macro|EESOX_STAT_DMA
mdefine_line|#define EESOX_STAT_DMA&t;&t;0x02
DECL|macro|EESOX_CONTROL
mdefine_line|#define EESOX_CONTROL&t;&t;0xa00
DECL|macro|EESOX_INTR_ENABLE
mdefine_line|#define EESOX_INTR_ENABLE&t;0x04
DECL|macro|EESOX_TERM_ENABLE
mdefine_line|#define EESOX_TERM_ENABLE&t;0x02
DECL|macro|EESOX_RESET
mdefine_line|#define EESOX_RESET&t;&t;0x01
DECL|macro|EESOX_DMA_OFFSET
mdefine_line|#define EESOX_DMA_OFFSET&t;0xe00
multiline_comment|/*&n; * Version&n; */
DECL|macro|VER_MAJOR
mdefine_line|#define VER_MAJOR&t;0
DECL|macro|VER_MINOR
mdefine_line|#define VER_MINOR&t;0
DECL|macro|VER_PATCH
mdefine_line|#define VER_PATCH&t;3
DECL|variable|ecs
r_static
r_struct
id|expansion_card
op_star
id|ecs
(braket
id|MAX_ECARDS
)braket
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
l_string|&quot;EESOX SCSI driver&quot;
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
DECL|struct|control
r_struct
id|control
(brace
DECL|member|io_port
r_int
r_int
id|io_port
suffix:semicolon
DECL|member|control
r_int
r_int
id|control
suffix:semicolon
)brace
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|info
id|FAS216_Info
id|info
suffix:semicolon
DECL|member|control
r_struct
id|control
id|control
suffix:semicolon
DECL|member|dmaarea
r_int
r_int
id|dmaarea
suffix:semicolon
multiline_comment|/* Pseudo DMA area&t;*/
DECL|member|sg
r_struct
id|scatterlist
id|sg
(braket
id|NR_SG
)braket
suffix:semicolon
multiline_comment|/* Scatter DMA list&t;*/
DECL|typedef|EESOXScsi_Info
)brace
id|EESOXScsi_Info
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
id|control
op_star
id|control
op_assign
(paren
r_struct
id|control
op_star
)paren
id|ec-&gt;irq_data
suffix:semicolon
id|control-&gt;control
op_or_assign
id|EESOX_INTR_ENABLE
suffix:semicolon
id|outb
c_func
(paren
id|control-&gt;control
comma
id|control-&gt;io_port
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
id|control
op_star
id|control
op_assign
(paren
r_struct
id|control
op_star
)paren
id|ec-&gt;irq_data
suffix:semicolon
id|control-&gt;control
op_and_assign
op_complement
id|EESOX_INTR_ENABLE
suffix:semicolon
id|outb
c_func
(paren
id|control-&gt;control
comma
id|control-&gt;io_port
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
id|eesoxscsi_irqenable
comma
id|eesoxscsi_irqdisable
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
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
id|EESOXScsi_Info
op_star
id|info
op_assign
(paren
id|EESOXScsi_Info
op_star
)paren
id|host-&gt;hostdata
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|save_flags_cli
c_func
(paren
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|on_off
)paren
id|info-&gt;control.control
op_or_assign
id|EESOX_TERM_ENABLE
suffix:semicolon
r_else
id|info-&gt;control.control
op_and_assign
op_complement
id|EESOX_TERM_ENABLE
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|outb
c_func
(paren
id|info-&gt;control.control
comma
id|info-&gt;control.io_port
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
id|Scsi_Host
op_star
id|host
op_assign
(paren
r_struct
id|Scsi_Host
op_star
)paren
id|dev_id
suffix:semicolon
id|fas216_intr
c_func
(paren
id|host
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
id|EESOXScsi_Info
op_star
id|info
op_assign
(paren
id|EESOXScsi_Info
op_star
)paren
id|host-&gt;hostdata
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
op_assign
id|SCp-&gt;buffers_residual
suffix:semicolon
r_int
id|pci_dir
comma
id|dma_dir
suffix:semicolon
r_if
c_cond
(paren
id|bufs
)paren
id|memcpy
c_func
(paren
id|info-&gt;sg
op_plus
l_int|1
comma
id|SCp-&gt;buffer
op_plus
l_int|1
comma
r_sizeof
(paren
r_struct
id|scatterlist
)paren
op_star
id|bufs
)paren
suffix:semicolon
id|info-&gt;sg
(braket
l_int|0
)braket
dot
id|address
op_assign
id|SCp-&gt;ptr
suffix:semicolon
id|info-&gt;sg
(braket
l_int|0
)braket
dot
id|length
op_assign
id|SCp-&gt;this_residual
suffix:semicolon
r_if
c_cond
(paren
id|direction
op_eq
id|DMA_OUT
)paren
id|pci_dir
op_assign
id|PCI_DMA_TODEVICE
comma
id|dma_dir
op_assign
id|DMA_MODE_WRITE
suffix:semicolon
r_else
id|pci_dir
op_assign
id|PCI_DMA_FROMDEVICE
comma
id|dma_dir
op_assign
id|DMA_MODE_READ
suffix:semicolon
id|pci_map_sg
c_func
(paren
l_int|NULL
comma
id|info-&gt;sg
comma
id|bufs
op_plus
l_int|1
comma
id|pci_dir
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
id|EESOXScsi_Info
op_star
id|info
op_assign
(paren
id|EESOXScsi_Info
op_star
)paren
id|host-&gt;hostdata
suffix:semicolon
r_int
r_int
id|status
suffix:semicolon
r_int
r_int
id|length
op_assign
id|SCp-&gt;this_residual
suffix:semicolon
r_union
(brace
r_int
r_char
op_star
id|c
suffix:semicolon
r_int
r_int
op_star
id|s
suffix:semicolon
r_int
r_int
op_star
id|l
suffix:semicolon
)brace
id|buffer
suffix:semicolon
id|buffer.c
op_assign
id|SCp-&gt;ptr
suffix:semicolon
id|status
op_assign
id|inb
c_func
(paren
id|host-&gt;io_port
op_plus
id|EESOX_STATUS
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dir
op_eq
id|DMA_IN
)paren
(brace
r_while
c_loop
(paren
id|length
OG
l_int|8
)paren
(brace
r_if
c_cond
(paren
id|status
op_amp
id|EESOX_STAT_DMA
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
id|inw
c_func
(paren
id|info-&gt;dmaarea
)paren
suffix:semicolon
id|l1
op_or_assign
id|inw
c_func
(paren
id|info-&gt;dmaarea
)paren
op_lshift
l_int|16
suffix:semicolon
id|l2
op_assign
id|inw
c_func
(paren
id|info-&gt;dmaarea
)paren
suffix:semicolon
id|l2
op_or_assign
id|inw
c_func
(paren
id|info-&gt;dmaarea
)paren
op_lshift
l_int|16
suffix:semicolon
op_star
id|buffer.l
op_increment
op_assign
id|l1
suffix:semicolon
op_star
id|buffer.l
op_increment
op_assign
id|l2
suffix:semicolon
id|length
op_sub_assign
l_int|8
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|status
op_amp
id|EESOX_STAT_INTR
)paren
r_goto
id|end
suffix:semicolon
id|status
op_assign
id|inb
c_func
(paren
id|host-&gt;io_port
op_plus
id|EESOX_STATUS
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|length
OG
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|status
op_amp
id|EESOX_STAT_DMA
)paren
(brace
op_star
id|buffer.s
op_increment
op_assign
id|inw
c_func
(paren
id|info-&gt;dmaarea
)paren
suffix:semicolon
id|length
op_sub_assign
l_int|2
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|status
op_amp
id|EESOX_STAT_INTR
)paren
r_goto
id|end
suffix:semicolon
id|status
op_assign
id|inb
c_func
(paren
id|host-&gt;io_port
op_plus
id|EESOX_STATUS
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|length
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|status
op_amp
id|EESOX_STAT_DMA
)paren
(brace
op_star
id|buffer.c
op_increment
op_assign
id|inw
c_func
(paren
id|info-&gt;dmaarea
)paren
suffix:semicolon
id|length
op_sub_assign
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|status
op_amp
id|EESOX_STAT_INTR
)paren
r_goto
id|end
suffix:semicolon
id|status
op_assign
id|inb
c_func
(paren
id|host-&gt;io_port
op_plus
id|EESOX_STATUS
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
r_while
c_loop
(paren
id|length
OG
l_int|8
)paren
(brace
r_if
c_cond
(paren
id|status
op_amp
id|EESOX_STAT_DMA
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
id|buffer.l
op_increment
suffix:semicolon
id|l2
op_assign
op_star
id|buffer.l
op_increment
suffix:semicolon
id|outw
c_func
(paren
id|l1
comma
id|info-&gt;dmaarea
)paren
suffix:semicolon
id|outw
c_func
(paren
id|l1
op_rshift
l_int|16
comma
id|info-&gt;dmaarea
)paren
suffix:semicolon
id|outw
c_func
(paren
id|l2
comma
id|info-&gt;dmaarea
)paren
suffix:semicolon
id|outw
c_func
(paren
id|l2
op_rshift
l_int|16
comma
id|info-&gt;dmaarea
)paren
suffix:semicolon
id|length
op_sub_assign
l_int|8
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|status
op_amp
id|EESOX_STAT_INTR
)paren
r_goto
id|end
suffix:semicolon
id|status
op_assign
id|inb
c_func
(paren
id|host-&gt;io_port
op_plus
id|EESOX_STATUS
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|length
OG
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|status
op_amp
id|EESOX_STAT_DMA
)paren
(brace
id|outw
c_func
(paren
op_star
id|buffer.s
op_increment
comma
id|info-&gt;dmaarea
)paren
suffix:semicolon
id|length
op_sub_assign
l_int|2
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|status
op_amp
id|EESOX_STAT_INTR
)paren
r_goto
id|end
suffix:semicolon
id|status
op_assign
id|inb
c_func
(paren
id|host-&gt;io_port
op_plus
id|EESOX_STATUS
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|length
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|status
op_amp
id|EESOX_STAT_DMA
)paren
(brace
id|outw
c_func
(paren
op_star
id|buffer.c
op_increment
comma
id|info-&gt;dmaarea
)paren
suffix:semicolon
id|length
op_sub_assign
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|status
op_amp
id|EESOX_STAT_INTR
)paren
r_goto
id|end
suffix:semicolon
id|status
op_assign
id|inb
c_func
(paren
id|host-&gt;io_port
op_plus
id|EESOX_STATUS
)paren
suffix:semicolon
)brace
)brace
id|end
suffix:colon
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
multiline_comment|/* Prototype: int eesoxscsi_detect(Scsi_Host_Template * tpnt)&n; * Purpose  : initialises EESOX SCSI driver&n; * Params   : tpnt - template for this SCSI adapter&n; * Returns  : &gt;0 if host found, 0 otherwise.&n; */
r_int
DECL|function|eesoxscsi_detect
id|eesoxscsi_detect
c_func
(paren
id|Scsi_Host_Template
op_star
id|tpnt
)paren
(brace
r_static
r_const
id|card_ids
id|eesoxscsi_cids
(braket
)braket
op_assign
(brace
id|EESOXSCSI_LIST
comma
(brace
l_int|0xffff
comma
l_int|0xffff
)brace
)brace
suffix:semicolon
r_int
id|count
op_assign
l_int|0
suffix:semicolon
r_struct
id|Scsi_Host
op_star
id|host
suffix:semicolon
id|tpnt-&gt;proc_name
op_assign
l_string|&quot;eesox&quot;
suffix:semicolon
id|memset
c_func
(paren
id|ecs
comma
l_int|0
comma
r_sizeof
(paren
id|ecs
)paren
)paren
suffix:semicolon
id|ecard_startfind
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
id|EESOXScsi_Info
op_star
id|info
suffix:semicolon
id|ecs
(braket
id|count
)braket
op_assign
id|ecard_find
c_func
(paren
l_int|0
comma
id|eesoxscsi_cids
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ecs
(braket
id|count
)braket
)paren
r_break
suffix:semicolon
id|ecard_claim
c_func
(paren
id|ecs
(braket
id|count
)braket
)paren
suffix:semicolon
id|host
op_assign
id|scsi_register
c_func
(paren
id|tpnt
comma
r_sizeof
(paren
id|EESOXScsi_Info
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
id|ecard_release
c_func
(paren
id|ecs
(braket
id|count
)braket
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|host-&gt;io_port
op_assign
id|ecard_address
c_func
(paren
id|ecs
(braket
id|count
)braket
comma
id|ECARD_IOC
comma
id|ECARD_FAST
)paren
suffix:semicolon
id|host-&gt;irq
op_assign
id|ecs
(braket
id|count
)braket
op_member_access_from_pointer
id|irq
suffix:semicolon
id|host-&gt;dma_channel
op_assign
id|ecs
(braket
id|count
)braket
op_member_access_from_pointer
id|dma
suffix:semicolon
id|info
op_assign
(paren
id|EESOXScsi_Info
op_star
)paren
id|host-&gt;hostdata
suffix:semicolon
id|info-&gt;control.io_port
op_assign
id|host-&gt;io_port
op_plus
id|EESOX_CONTROL
suffix:semicolon
id|info-&gt;control.control
op_assign
id|term
(braket
id|count
)braket
ques
c_cond
id|EESOX_TERM_ENABLE
suffix:colon
l_int|0
suffix:semicolon
id|outb
c_func
(paren
id|info-&gt;control.control
comma
id|info-&gt;control.io_port
)paren
suffix:semicolon
id|ecs
(braket
id|count
)braket
op_member_access_from_pointer
id|irqaddr
op_assign
(paren
r_int
r_char
op_star
)paren
id|ioaddr
c_func
(paren
id|host-&gt;io_port
op_plus
id|EESOX_STATUS
)paren
suffix:semicolon
id|ecs
(braket
id|count
)braket
op_member_access_from_pointer
id|irqmask
op_assign
id|EESOX_STAT_INTR
suffix:semicolon
id|ecs
(braket
id|count
)braket
op_member_access_from_pointer
id|irq_data
op_assign
op_amp
id|info-&gt;control
suffix:semicolon
id|ecs
(braket
id|count
)braket
op_member_access_from_pointer
id|ops
op_assign
(paren
id|expansioncard_ops_t
op_star
)paren
op_amp
id|eesoxscsi_ops
suffix:semicolon
id|info-&gt;info.scsi.io_port
op_assign
id|host-&gt;io_port
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
id|EESOX_XTALFREQ
suffix:semicolon
id|info-&gt;info.ifcfg.select_timeout
op_assign
l_int|255
suffix:semicolon
id|info-&gt;info.ifcfg.asyncperiod
op_assign
id|EESOX_ASYNC_PERIOD
suffix:semicolon
id|info-&gt;info.ifcfg.sync_max_depth
op_assign
id|EESOX_SYNC_DEPTH
suffix:semicolon
id|info-&gt;info.ifcfg.cntl3
op_assign
id|CNTL3_BS8
op_or
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
id|info-&gt;dmaarea
op_assign
id|host-&gt;io_port
op_plus
id|EESOX_DMA_OFFSET
suffix:semicolon
id|request_region
c_func
(paren
id|host-&gt;io_port
op_plus
id|EESOX_FAS216_OFFSET
comma
l_int|16
op_lshift
id|EESOX_FAS216_SHIFT
comma
l_string|&quot;eesox2-fas&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|host-&gt;irq
op_ne
id|NO_IRQ
op_logical_and
id|request_irq
c_func
(paren
id|host-&gt;irq
comma
id|eesoxscsi_intr
comma
id|SA_INTERRUPT
comma
l_string|&quot;eesox&quot;
comma
id|host
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;scsi%d: IRQ%d not free, interrupts disabled&bslash;n&quot;
comma
id|host-&gt;host_no
comma
id|host-&gt;irq
)paren
suffix:semicolon
id|host-&gt;irq
op_assign
id|NO_IRQ
suffix:semicolon
)brace
r_if
c_cond
(paren
id|host-&gt;dma_channel
op_ne
id|NO_DMA
op_logical_and
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
id|fas216_init
c_func
(paren
id|host
)paren
suffix:semicolon
op_increment
id|count
suffix:semicolon
)brace
r_return
id|count
suffix:semicolon
)brace
multiline_comment|/* Prototype: int eesoxscsi_release(struct Scsi_Host * host)&n; * Purpose  : releases all resources used by this adapter&n; * Params   : host - driver host structure to return info for.&n; */
DECL|function|eesoxscsi_release
r_int
id|eesoxscsi_release
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|host
)paren
(brace
r_int
id|i
suffix:semicolon
id|fas216_release
c_func
(paren
id|host
)paren
suffix:semicolon
r_if
c_cond
(paren
id|host-&gt;irq
op_ne
id|NO_IRQ
)paren
id|free_irq
c_func
(paren
id|host-&gt;irq
comma
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
id|release_region
c_func
(paren
id|host-&gt;io_port
op_plus
id|EESOX_FAS216_OFFSET
comma
l_int|16
op_lshift
id|EESOX_FAS216_SHIFT
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
id|MAX_ECARDS
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|ecs
(braket
id|i
)braket
op_logical_and
id|host-&gt;io_port
op_eq
id|ecard_address
c_func
(paren
id|ecs
(braket
id|i
)braket
comma
id|ECARD_IOC
comma
id|ECARD_FAST
)paren
)paren
id|ecard_release
c_func
(paren
id|ecs
(braket
id|i
)braket
)paren
suffix:semicolon
r_return
l_int|0
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
id|EESOXScsi_Info
op_star
id|info
op_assign
(paren
id|EESOXScsi_Info
op_star
)paren
id|host-&gt;hostdata
suffix:semicolon
r_static
r_char
id|string
(braket
l_int|100
)braket
comma
op_star
id|p
suffix:semicolon
id|p
op_assign
id|string
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;%s &quot;
comma
id|host-&gt;hostt-&gt;name
)paren
suffix:semicolon
id|p
op_add_assign
id|fas216_info
c_func
(paren
op_amp
id|info-&gt;info
comma
id|p
)paren
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;v%d.%d.%d terminators o%s&quot;
comma
id|VER_MAJOR
comma
id|VER_MINOR
comma
id|VER_PATCH
comma
id|info-&gt;control.control
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
op_assign
id|scsi_hostlist
suffix:semicolon
id|EESOXScsi_Info
op_star
id|info
suffix:semicolon
id|Scsi_Device
op_star
id|scd
suffix:semicolon
r_while
c_loop
(paren
id|host
)paren
(brace
r_if
c_cond
(paren
id|host-&gt;host_no
op_eq
id|host_no
)paren
r_break
suffix:semicolon
id|host
op_assign
id|host-&gt;next
suffix:semicolon
)brace
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
id|EESOXScsi_Info
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
l_string|&quot;EESOX SCSI driver version %d.%d.%d&bslash;n&quot;
comma
id|VER_MAJOR
comma
id|VER_MINOR
comma
id|VER_PATCH
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
id|info-&gt;control.control
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
id|pos
op_add_assign
id|sprintf
(paren
id|buffer
op_plus
id|pos
comma
l_string|&quot;&bslash;nAttached devices:&bslash;n&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|scd
op_assign
id|host-&gt;host_queue
suffix:semicolon
id|scd
suffix:semicolon
id|scd
op_assign
id|scd-&gt;next
)paren
(brace
r_int
id|len
suffix:semicolon
id|proc_print_scsidevice
(paren
id|scd
comma
id|buffer
comma
op_amp
id|len
comma
id|pos
)paren
suffix:semicolon
id|pos
op_add_assign
id|len
suffix:semicolon
id|pos
op_add_assign
id|sprintf
(paren
id|buffer
op_plus
id|pos
comma
l_string|&quot;Extensions: &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|scd-&gt;tagged_supported
)paren
id|pos
op_add_assign
id|sprintf
(paren
id|buffer
op_plus
id|pos
comma
l_string|&quot;TAG %sabled [%d] &quot;
comma
id|scd-&gt;tagged_queue
ques
c_cond
l_string|&quot;en&quot;
suffix:colon
l_string|&quot;dis&quot;
comma
id|scd-&gt;current_tag
)paren
suffix:semicolon
id|pos
op_add_assign
id|sprintf
(paren
id|buffer
op_plus
id|pos
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pos
op_plus
id|begin
OL
id|offset
)paren
(brace
id|begin
op_add_assign
id|pos
suffix:semicolon
id|pos
op_assign
l_int|0
suffix:semicolon
)brace
)brace
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
DECL|variable|eesox_template
r_static
id|Scsi_Host_Template
id|eesox_template
op_assign
(brace
id|module
suffix:colon
id|THIS_MODULE
comma
id|proc_info
suffix:colon
id|eesoxscsi_proc_info
comma
id|name
suffix:colon
l_string|&quot;EESOX SCSI&quot;
comma
id|detect
suffix:colon
id|eesoxscsi_detect
comma
id|release
suffix:colon
id|eesoxscsi_release
comma
id|info
suffix:colon
id|eesoxscsi_info
comma
id|bios_param
suffix:colon
id|scsicam_bios_param
comma
id|can_queue
suffix:colon
l_int|1
comma
id|this_id
suffix:colon
l_int|7
comma
id|sg_tablesize
suffix:colon
id|SG_ALL
comma
id|cmd_per_lun
suffix:colon
l_int|1
comma
id|use_clustering
suffix:colon
id|DISABLE_CLUSTERING
comma
id|command
suffix:colon
id|fas216_command
comma
id|queuecommand
suffix:colon
id|fas216_queue_command
comma
id|eh_host_reset_handler
suffix:colon
id|fas216_eh_host_reset
comma
id|eh_bus_reset_handler
suffix:colon
id|fas216_eh_bus_reset
comma
id|eh_device_reset_handler
suffix:colon
id|fas216_eh_device_reset
comma
id|eh_abort_handler
suffix:colon
id|fas216_eh_abort
comma
id|use_new_eh_code
suffix:colon
l_int|1
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
id|scsi_register_module
c_func
(paren
id|MODULE_SCSI_HA
comma
op_amp
id|eesox_template
)paren
suffix:semicolon
r_if
c_cond
(paren
id|eesox_template.present
)paren
r_return
l_int|0
suffix:semicolon
id|scsi_unregister_module
c_func
(paren
id|MODULE_SCSI_HA
comma
op_amp
id|eesox_template
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
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
id|scsi_unregister_module
c_func
(paren
id|MODULE_SCSI_HA
comma
op_amp
id|eesox_template
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
eof
