multiline_comment|/*&n; *  linux/drivers/acorn/scsi/powertec.c&n; *&n; *  Copyright (C) 1997-2003 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/dma-mapping.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/ecard.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &quot;../scsi.h&quot;
macro_line|#include &lt;scsi/scsi_host.h&gt;
macro_line|#include &quot;fas216.h&quot;
macro_line|#include &quot;scsi.h&quot;
macro_line|#include &lt;scsi/scsicam.h&gt;
DECL|macro|POWERTEC_FAS216_OFFSET
mdefine_line|#define POWERTEC_FAS216_OFFSET&t;0x3000
DECL|macro|POWERTEC_FAS216_SHIFT
mdefine_line|#define POWERTEC_FAS216_SHIFT&t;6
DECL|macro|POWERTEC_INTR_STATUS
mdefine_line|#define POWERTEC_INTR_STATUS&t;0x2000
DECL|macro|POWERTEC_INTR_BIT
mdefine_line|#define POWERTEC_INTR_BIT&t;0x80
DECL|macro|POWERTEC_RESET_CONTROL
mdefine_line|#define POWERTEC_RESET_CONTROL&t;0x1018
DECL|macro|POWERTEC_RESET_BIT
mdefine_line|#define POWERTEC_RESET_BIT&t;1
DECL|macro|POWERTEC_TERM_CONTROL
mdefine_line|#define POWERTEC_TERM_CONTROL&t;0x2018
DECL|macro|POWERTEC_TERM_ENABLE
mdefine_line|#define POWERTEC_TERM_ENABLE&t;1
DECL|macro|POWERTEC_INTR_CONTROL
mdefine_line|#define POWERTEC_INTR_CONTROL&t;0x101c
DECL|macro|POWERTEC_INTR_ENABLE
mdefine_line|#define POWERTEC_INTR_ENABLE&t;1
DECL|macro|POWERTEC_INTR_DISABLE
mdefine_line|#define POWERTEC_INTR_DISABLE&t;0
DECL|macro|VERSION
mdefine_line|#define VERSION&t;&quot;1.10 (19/01/2003 2.5.59)&quot;
multiline_comment|/*&n; * Use term=0,1,0,0,0 to turn terminators on/off.&n; * One entry per slot.&n; */
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
DECL|struct|powertec_info
r_struct
id|powertec_info
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
DECL|member|term_port
r_void
op_star
id|term_port
suffix:semicolon
DECL|member|term_ctl
r_int
r_int
id|term_ctl
suffix:semicolon
DECL|member|sg
r_struct
id|scatterlist
id|sg
(braket
id|NR_SG
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Prototype: void powertecscsi_irqenable(ec, irqnr)&n; * Purpose  : Enable interrupts on Powertec SCSI card&n; * Params   : ec    - expansion card structure&n; *          : irqnr - interrupt number&n; */
r_static
r_void
DECL|function|powertecscsi_irqenable
id|powertecscsi_irqenable
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
id|writeb
c_func
(paren
id|POWERTEC_INTR_ENABLE
comma
id|ec-&gt;irq_data
)paren
suffix:semicolon
)brace
multiline_comment|/* Prototype: void powertecscsi_irqdisable(ec, irqnr)&n; * Purpose  : Disable interrupts on Powertec SCSI card&n; * Params   : ec    - expansion card structure&n; *          : irqnr - interrupt number&n; */
r_static
r_void
DECL|function|powertecscsi_irqdisable
id|powertecscsi_irqdisable
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
id|writeb
c_func
(paren
id|POWERTEC_INTR_DISABLE
comma
id|ec-&gt;irq_data
)paren
suffix:semicolon
)brace
DECL|variable|powertecscsi_ops
r_static
r_const
id|expansioncard_ops_t
id|powertecscsi_ops
op_assign
(brace
dot
id|irqenable
op_assign
id|powertecscsi_irqenable
comma
dot
id|irqdisable
op_assign
id|powertecscsi_irqdisable
comma
)brace
suffix:semicolon
multiline_comment|/* Prototype: void powertecscsi_terminator_ctl(host, on_off)&n; * Purpose  : Turn the Powertec SCSI terminators on or off&n; * Params   : host   - card to turn on/off&n; *          : on_off - !0 to turn on, 0 to turn off&n; */
r_static
r_void
DECL|function|powertecscsi_terminator_ctl
id|powertecscsi_terminator_ctl
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
id|powertec_info
op_star
id|info
op_assign
(paren
r_struct
id|powertec_info
op_star
)paren
id|host-&gt;hostdata
suffix:semicolon
id|info-&gt;term_ctl
op_assign
id|on_off
ques
c_cond
id|POWERTEC_TERM_ENABLE
suffix:colon
l_int|0
suffix:semicolon
id|writeb
c_func
(paren
id|info-&gt;term_ctl
comma
id|info-&gt;term_port
)paren
suffix:semicolon
)brace
multiline_comment|/* Prototype: void powertecscsi_intr(irq, *dev_id, *regs)&n; * Purpose  : handle interrupts from Powertec SCSI card&n; * Params   : irq    - interrupt number&n; *&t;      dev_id - user-defined (Scsi_Host structure)&n; *&t;      regs   - processor registers at interrupt&n; */
r_static
id|irqreturn_t
DECL|function|powertecscsi_intr
id|powertecscsi_intr
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
id|powertec_info
op_star
id|info
op_assign
id|dev_id
suffix:semicolon
r_return
id|fas216_intr
c_func
(paren
op_amp
id|info-&gt;info
)paren
suffix:semicolon
)brace
multiline_comment|/* Prototype: fasdmatype_t powertecscsi_dma_setup(host, SCpnt, direction, min_type)&n; * Purpose  : initialises DMA/PIO&n; * Params   : host      - host&n; *&t;      SCpnt     - command&n; *&t;      direction - DMA on to/off of card&n; *&t;      min_type  - minimum DMA support that we must have for this transfer&n; * Returns  : type of transfer to be performed&n; */
r_static
id|fasdmatype_t
DECL|function|powertecscsi_dma_setup
id|powertecscsi_dma_setup
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
id|powertec_info
op_star
id|info
op_assign
(paren
r_struct
id|powertec_info
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
id|info-&gt;info.ifcfg.capabilities
op_amp
id|FASCAP_DMA
op_logical_and
id|min_type
op_eq
id|fasdma_real_all
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
multiline_comment|/*&n;&t; * If we&squot;re not doing DMA,&n;&t; *  we&squot;ll do slow PIO&n;&t; */
r_return
id|fasdma_pio
suffix:semicolon
)brace
multiline_comment|/* Prototype: int powertecscsi_dma_stop(host, SCpnt)&n; * Purpose  : stops DMA/PIO&n; * Params   : host  - host&n; *&t;      SCpnt - command&n; */
r_static
r_void
DECL|function|powertecscsi_dma_stop
id|powertecscsi_dma_stop
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
multiline_comment|/* Prototype: const char *powertecscsi_info(struct Scsi_Host * host)&n; * Purpose  : returns a descriptive string about this interface,&n; * Params   : host - driver host structure to return info for.&n; * Returns  : pointer to a static buffer containing null terminated string.&n; */
DECL|function|powertecscsi_info
r_const
r_char
op_star
id|powertecscsi_info
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|host
)paren
(brace
r_struct
id|powertec_info
op_star
id|info
op_assign
(paren
r_struct
id|powertec_info
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
id|info-&gt;term_ctl
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
multiline_comment|/* Prototype: int powertecscsi_set_proc_info(struct Scsi_Host *host, char *buffer, int length)&n; * Purpose  : Set a driver specific function&n; * Params   : host   - host to setup&n; *          : buffer - buffer containing string describing operation&n; *          : length - length of string&n; * Returns  : -EINVAL, or 0&n; */
r_static
r_int
DECL|function|powertecscsi_set_proc_info
id|powertecscsi_set_proc_info
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
l_int|12
op_logical_and
id|strncmp
c_func
(paren
id|buffer
comma
l_string|&quot;POWERTECSCSI&quot;
comma
l_int|12
)paren
op_eq
l_int|0
)paren
(brace
id|buffer
op_add_assign
l_int|12
suffix:semicolon
id|length
op_sub_assign
l_int|12
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
id|powertecscsi_terminator_ctl
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
id|powertecscsi_terminator_ctl
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
multiline_comment|/* Prototype: int powertecscsi_proc_info(char *buffer, char **start, off_t offset,&n; *&t;&t;&t;&t;&t;int length, int host_no, int inout)&n; * Purpose  : Return information about the driver to a user process accessing&n; *&t;      the /proc filesystem.&n; * Params   : buffer  - a buffer to write information to&n; *&t;      start   - a pointer into this buffer set by this routine to the start&n; *&t;&t;        of the required information.&n; *&t;      offset  - offset into information that we have read upto.&n; *&t;      length  - length of buffer&n; *&t;      inout   - 0 for reading, 1 for writing.&n; * Returns  : length of data written to buffer.&n; */
DECL|function|powertecscsi_proc_info
r_int
id|powertecscsi_proc_info
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
id|inout
)paren
(brace
r_struct
id|powertec_info
op_star
id|info
suffix:semicolon
r_char
op_star
id|p
op_assign
id|buffer
suffix:semicolon
r_int
id|pos
suffix:semicolon
r_if
c_cond
(paren
id|inout
op_eq
l_int|1
)paren
r_return
id|powertecscsi_set_proc_info
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
id|powertec_info
op_star
)paren
id|host-&gt;hostdata
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;PowerTec SCSI driver v%s&bslash;n&quot;
comma
id|VERSION
)paren
suffix:semicolon
id|p
op_add_assign
id|fas216_print_host
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
l_string|&quot;Term    : o%s&bslash;n&quot;
comma
id|info-&gt;term_ctl
ques
c_cond
l_string|&quot;n&quot;
suffix:colon
l_string|&quot;ff&quot;
)paren
suffix:semicolon
id|p
op_add_assign
id|fas216_print_stats
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
id|fas216_print_devices
c_func
(paren
op_amp
id|info-&gt;info
comma
id|p
)paren
suffix:semicolon
op_star
id|start
op_assign
id|buffer
op_plus
id|offset
suffix:semicolon
id|pos
op_assign
id|p
op_minus
id|buffer
op_minus
id|offset
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
DECL|function|powertecscsi_show_term
r_static
id|ssize_t
id|powertecscsi_show_term
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
id|powertec_info
op_star
id|info
op_assign
(paren
r_struct
id|powertec_info
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
id|info-&gt;term_ctl
ques
c_cond
l_int|1
suffix:colon
l_int|0
)paren
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|powertecscsi_store_term
id|powertecscsi_store_term
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
r_if
c_cond
(paren
id|len
OG
l_int|1
)paren
id|powertecscsi_terminator_ctl
c_func
(paren
id|host
comma
id|buf
(braket
l_int|0
)braket
op_ne
l_char|&squot;0&squot;
)paren
suffix:semicolon
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
id|powertecscsi_show_term
comma
id|powertecscsi_store_term
)paren
suffix:semicolon
DECL|variable|powertecscsi_template
r_static
id|Scsi_Host_Template
id|powertecscsi_template
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
id|powertecscsi_proc_info
comma
dot
id|name
op_assign
l_string|&quot;PowerTec SCSI&quot;
comma
dot
id|info
op_assign
id|powertecscsi_info
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
l_int|8
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
l_int|2
comma
dot
id|use_clustering
op_assign
id|ENABLE_CLUSTERING
comma
dot
id|proc_name
op_assign
l_string|&quot;powertec&quot;
comma
)brace
suffix:semicolon
r_static
r_int
id|__devinit
DECL|function|powertecscsi_probe
id|powertecscsi_probe
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
id|powertec_info
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
l_string|&quot;powertecscsi&quot;
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
id|scsi_host_alloc
c_func
(paren
op_amp
id|powertecscsi_template
comma
r_sizeof
(paren
r_struct
id|powertec_info
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
id|ec-&gt;irqaddr
op_assign
id|base
op_plus
id|POWERTEC_INTR_STATUS
suffix:semicolon
id|ec-&gt;irqmask
op_assign
id|POWERTEC_INTR_BIT
suffix:semicolon
id|ec-&gt;irq_data
op_assign
id|base
op_plus
id|POWERTEC_INTR_CONTROL
suffix:semicolon
id|ec-&gt;ops
op_assign
op_amp
id|powertecscsi_ops
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
id|powertec_info
op_star
)paren
id|host-&gt;hostdata
suffix:semicolon
id|info-&gt;term_port
op_assign
id|base
op_plus
id|POWERTEC_TERM_CONTROL
suffix:semicolon
id|powertecscsi_terminator_ctl
c_func
(paren
id|host
comma
id|term
(braket
id|ec-&gt;slot_no
)braket
)paren
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
id|info-&gt;info.scsi.io_base
op_assign
id|base
op_plus
id|POWERTEC_FAS216_OFFSET
suffix:semicolon
id|info-&gt;info.scsi.io_shift
op_assign
id|POWERTEC_FAS216_SHIFT
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
id|info-&gt;info.ifcfg.capabilities
op_assign
l_int|0
suffix:semicolon
id|info-&gt;info.dma.setup
op_assign
id|powertecscsi_dma_setup
suffix:semicolon
id|info-&gt;info.dma.pseudo
op_assign
l_int|NULL
suffix:semicolon
id|info-&gt;info.dma.stop
op_assign
id|powertecscsi_dma_stop
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
id|powertecscsi_intr
comma
id|SA_INTERRUPT
comma
l_string|&quot;powertec&quot;
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
id|out_release
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
l_string|&quot;powertec&quot;
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;scsi%d: DMA%d not free, using PIO&bslash;n&quot;
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
id|out_release
suffix:colon
id|fas216_release
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
id|scsi_host_put
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
DECL|function|powertecscsi_remove
r_static
r_void
id|__devexit
id|powertecscsi_remove
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
id|powertecscsi_info
op_star
id|info
op_assign
(paren
r_struct
id|powertecscsi_info
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
id|scsi_host_put
c_func
(paren
id|host
)paren
suffix:semicolon
)brace
DECL|variable|powertecscsi_cids
r_static
r_const
r_struct
id|ecard_id
id|powertecscsi_cids
(braket
)braket
op_assign
(brace
(brace
id|MANU_ALSYSTEMS
comma
id|PROD_ALSYS_SCSIATAPI
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
DECL|variable|powertecscsi_driver
r_static
r_struct
id|ecard_driver
id|powertecscsi_driver
op_assign
(brace
dot
id|probe
op_assign
id|powertecscsi_probe
comma
dot
id|remove
op_assign
id|__devexit_p
c_func
(paren
id|powertecscsi_remove
)paren
comma
dot
id|id_table
op_assign
id|powertecscsi_cids
comma
dot
id|drv
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;powertecscsi&quot;
comma
)brace
comma
)brace
suffix:semicolon
DECL|function|powertecscsi_init
r_static
r_int
id|__init
id|powertecscsi_init
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
id|powertecscsi_driver
)paren
suffix:semicolon
)brace
DECL|function|powertecscsi_exit
r_static
r_void
id|__exit
id|powertecscsi_exit
c_func
(paren
r_void
)paren
(brace
id|ecard_remove_driver
c_func
(paren
op_amp
id|powertecscsi_driver
)paren
suffix:semicolon
)brace
DECL|variable|powertecscsi_init
id|module_init
c_func
(paren
id|powertecscsi_init
)paren
suffix:semicolon
DECL|variable|powertecscsi_exit
id|module_exit
c_func
(paren
id|powertecscsi_exit
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
l_string|&quot;Powertec SCSI driver&quot;
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
