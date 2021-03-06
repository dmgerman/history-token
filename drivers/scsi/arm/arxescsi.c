multiline_comment|/*&n; * linux/arch/arm/drivers/scsi/arxescsi.c&n; *&n; * Copyright (C) 1997-2000 Russell King, Stefan Hanske&n; *&n; * This driver is based on experimentation.  Hence, it may have made&n; * assumptions about the particular card that I have available, and&n; * may not be reliable!&n; *&n; * Changelog:&n; *  30-08-1997&t;RMK&t;0.0.0&t;Created, READONLY version as cumana_2.c&n; *  22-01-1998&t;RMK&t;0.0.1&t;Updated to 2.1.80&n; *  15-04-1998&t;RMK&t;0.0.1&t;Only do PIO if FAS216 will allow it.&n; *  11-06-1998 &t;SH&t;0.0.2   Changed to support ARXE 16-bit SCSI card&n; *&t;&t;&t;&t;enabled writing&n; *  01-01-2000&t;SH&t;0.1.0   Added *real* pseudo dma writing&n; *&t;&t;&t;&t;(arxescsi_pseudo_dma_write)&n; *  02-04-2000&t;RMK&t;0.1.1&t;Updated for new error handling code.&n; *  22-10-2000  SH&t;&t;Updated for new registering scheme.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/ecard.h&gt;
macro_line|#include &quot;../scsi.h&quot;
macro_line|#include &lt;scsi/scsi_host.h&gt;
macro_line|#include &quot;fas216.h&quot;
DECL|struct|arxescsi_info
r_struct
id|arxescsi_info
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
DECL|member|base
r_void
id|__iomem
op_star
id|base
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|DMADATA_OFFSET
mdefine_line|#define DMADATA_OFFSET&t;(0x200)
DECL|macro|DMASTAT_OFFSET
mdefine_line|#define DMASTAT_OFFSET&t;(0x600)
DECL|macro|DMASTAT_DRQ
mdefine_line|#define DMASTAT_DRQ&t;(1 &lt;&lt; 0)
DECL|macro|CSTATUS_IRQ
mdefine_line|#define CSTATUS_IRQ&t;(1 &lt;&lt; 0)
DECL|macro|VERSION
mdefine_line|#define VERSION &quot;1.10 (23/01/2003 2.5.57)&quot;
multiline_comment|/*&n; * Function: int arxescsi_dma_setup(host, SCpnt, direction, min_type)&n; * Purpose : initialises DMA/PIO&n; * Params  : host      - host&n; *&t;     SCpnt     - command&n; *&t;     direction - DMA on to/off of card&n; *&t;     min_type  - minimum DMA support that we must have for this transfer&n; * Returns : 0 if we should not set CMD_WITHDMA for transfer info command&n; */
r_static
id|fasdmatype_t
DECL|function|arxescsi_dma_setup
id|arxescsi_dma_setup
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
multiline_comment|/*&n;&t; * We don&squot;t do real DMA&n;&t; */
r_return
id|fasdma_pseudo
suffix:semicolon
)brace
DECL|function|arxescsi_pseudo_dma_write
r_static
r_void
id|arxescsi_pseudo_dma_write
c_func
(paren
r_int
r_char
op_star
id|addr
comma
r_void
id|__iomem
op_star
id|base
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;               stmdb   sp!, {r0-r12}&bslash;n&quot;
l_string|&quot;               mov     r3, %0&bslash;n&quot;
l_string|&quot;               mov     r1, %1&bslash;n&quot;
l_string|&quot;               add     r2, r1, #512&bslash;n&quot;
l_string|&quot;               mov     r4, #256&bslash;n&quot;
l_string|&quot;.loop_1:       ldmia   r3!, {r6, r8, r10, r12}&bslash;n&quot;
l_string|&quot;               mov     r5, r6, lsl #16&bslash;n&quot;
l_string|&quot;               mov     r7, r8, lsl #16&bslash;n&quot;
l_string|&quot;.loop_2:       ldrb    r0, [r1, #1536]&bslash;n&quot;
l_string|&quot;               tst     r0, #1&bslash;n&quot;
l_string|&quot;               beq     .loop_2&bslash;n&quot;
l_string|&quot;               stmia   r2, {r5-r8}&bslash;n&bslash;t&quot;
l_string|&quot;               mov     r9, r10, lsl #16&bslash;n&quot;
l_string|&quot;               mov     r11, r12, lsl #16&bslash;n&quot;
l_string|&quot;.loop_3:       ldrb    r0, [r1, #1536]&bslash;n&quot;
l_string|&quot;               tst     r0, #1&bslash;n&quot;
l_string|&quot;               beq     .loop_3&bslash;n&quot;
l_string|&quot;               stmia   r2, {r9-r12}&bslash;n&quot;
l_string|&quot;               subs    r4, r4, #16&bslash;n&quot;
l_string|&quot;               bne     .loop_1&bslash;n&quot;
l_string|&quot;               ldmia   sp!, {r0-r12}&bslash;n&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;r&quot;
(paren
id|base
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Function: int arxescsi_dma_pseudo(host, SCpnt, direction, transfer)&n; * Purpose : handles pseudo DMA&n; * Params  : host      - host&n; *&t;     SCpnt     - command&n; *&t;     direction - DMA on to/off of card&n; *&t;     transfer  - minimum number of bytes we expect to transfer&n; */
r_static
r_void
DECL|function|arxescsi_dma_pseudo
id|arxescsi_dma_pseudo
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
r_int
id|transfer
)paren
(brace
r_struct
id|arxescsi_info
op_star
id|info
op_assign
(paren
r_struct
id|arxescsi_info
op_star
)paren
id|host-&gt;hostdata
suffix:semicolon
r_int
r_int
id|length
comma
id|error
op_assign
l_int|0
suffix:semicolon
r_void
id|__iomem
op_star
id|base
op_assign
id|info-&gt;info.scsi.io_base
suffix:semicolon
r_int
r_char
op_star
id|addr
suffix:semicolon
id|length
op_assign
id|SCp-&gt;this_residual
suffix:semicolon
id|addr
op_assign
id|SCp-&gt;ptr
suffix:semicolon
r_if
c_cond
(paren
id|direction
op_eq
id|DMA_OUT
)paren
(brace
r_int
r_int
id|word
suffix:semicolon
r_while
c_loop
(paren
id|length
OG
l_int|256
)paren
(brace
r_if
c_cond
(paren
id|readb
c_func
(paren
id|base
op_plus
l_int|0x80
)paren
op_amp
id|STAT_INT
)paren
(brace
id|error
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
id|arxescsi_pseudo_dma_write
c_func
(paren
id|addr
comma
id|base
)paren
suffix:semicolon
id|addr
op_add_assign
l_int|256
suffix:semicolon
id|length
op_sub_assign
l_int|256
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
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
id|readb
c_func
(paren
id|base
op_plus
l_int|0x80
)paren
op_amp
id|STAT_INT
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|readb
c_func
(paren
id|base
op_plus
id|DMASTAT_OFFSET
)paren
op_amp
id|DMASTAT_DRQ
)paren
)paren
r_continue
suffix:semicolon
id|word
op_assign
op_star
id|addr
op_or
op_star
(paren
id|addr
op_plus
l_int|1
)paren
op_lshift
l_int|8
suffix:semicolon
id|writew
c_func
(paren
id|word
comma
id|base
op_plus
id|DMADATA_OFFSET
)paren
suffix:semicolon
r_if
c_cond
(paren
id|length
OG
l_int|1
)paren
(brace
id|addr
op_add_assign
l_int|2
suffix:semicolon
id|length
op_sub_assign
l_int|2
suffix:semicolon
)brace
r_else
(brace
id|addr
op_add_assign
l_int|1
suffix:semicolon
id|length
op_sub_assign
l_int|1
suffix:semicolon
)brace
)brace
)brace
r_else
(brace
r_if
c_cond
(paren
id|transfer
op_logical_and
(paren
id|transfer
op_amp
l_int|255
)paren
)paren
(brace
r_while
c_loop
(paren
id|length
op_ge
l_int|256
)paren
(brace
r_if
c_cond
(paren
id|readb
c_func
(paren
id|base
op_plus
l_int|0x80
)paren
op_amp
id|STAT_INT
)paren
(brace
id|error
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|readb
c_func
(paren
id|base
op_plus
id|DMASTAT_OFFSET
)paren
op_amp
id|DMASTAT_DRQ
)paren
)paren
r_continue
suffix:semicolon
id|readsw
c_func
(paren
id|base
op_plus
id|DMADATA_OFFSET
comma
id|addr
comma
l_int|256
op_rshift
l_int|1
)paren
suffix:semicolon
id|addr
op_add_assign
l_int|256
suffix:semicolon
id|length
op_sub_assign
l_int|256
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|error
)paren
)paren
r_while
c_loop
(paren
id|length
OG
l_int|0
)paren
(brace
r_int
r_int
id|word
suffix:semicolon
r_if
c_cond
(paren
id|readb
c_func
(paren
id|base
op_plus
l_int|0x80
)paren
op_amp
id|STAT_INT
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|readb
c_func
(paren
id|base
op_plus
id|DMASTAT_OFFSET
)paren
op_amp
id|DMASTAT_DRQ
)paren
)paren
r_continue
suffix:semicolon
id|word
op_assign
id|readw
c_func
(paren
id|base
op_plus
id|DMADATA_OFFSET
)paren
suffix:semicolon
op_star
id|addr
op_increment
op_assign
id|word
suffix:semicolon
r_if
c_cond
(paren
op_decrement
id|length
OG
l_int|0
)paren
(brace
op_star
id|addr
op_increment
op_assign
id|word
op_rshift
l_int|8
suffix:semicolon
id|length
op_decrement
suffix:semicolon
)brace
)brace
)brace
)brace
multiline_comment|/*&n; * Function: int arxescsi_dma_stop(host, SCpnt)&n; * Purpose : stops DMA/PIO&n; * Params  : host  - host&n; *&t;     SCpnt - command&n; */
DECL|function|arxescsi_dma_stop
r_static
r_void
id|arxescsi_dma_stop
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
multiline_comment|/*&n;&t; * no DMA to stop&n;&t; */
)brace
multiline_comment|/*&n; * Function: const char *arxescsi_info(struct Scsi_Host * host)&n; * Purpose : returns a descriptive string about this interface,&n; * Params  : host - driver host structure to return info for.&n; * Returns : pointer to a static buffer containing null terminated string.&n; */
DECL|function|arxescsi_info
r_static
r_const
r_char
op_star
id|arxescsi_info
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|host
)paren
(brace
r_struct
id|arxescsi_info
op_star
id|info
op_assign
(paren
r_struct
id|arxescsi_info
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
l_string|&quot;%s (%s) in slot %d v%s&quot;
comma
id|host-&gt;hostt-&gt;name
comma
id|info-&gt;info.scsi.type
comma
id|info-&gt;ec-&gt;slot_no
comma
id|VERSION
)paren
suffix:semicolon
r_return
id|string
suffix:semicolon
)brace
multiline_comment|/*&n; * Function: int arxescsi_proc_info(char *buffer, char **start, off_t offset,&n; *&t;&t;&t;&t;&t; int length, int host_no, int inout)&n; * Purpose : Return information about the driver to a user process accessing&n; *&t;     the /proc filesystem.&n; * Params  : buffer - a buffer to write information to&n; *&t;     start  - a pointer into this buffer set by this routine to the start&n; *&t;&t;      of the required information.&n; *&t;     offset - offset into information that we have read upto.&n; *&t;     length - length of buffer&n; *&t;     host_no - host number to return information for&n; *&t;     inout  - 0 for reading, 1 for writing.&n; * Returns : length of data written to buffer.&n; */
r_static
r_int
DECL|function|arxescsi_proc_info
id|arxescsi_proc_info
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
id|arxescsi_info
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
id|info
op_assign
(paren
r_struct
id|arxescsi_info
op_star
)paren
id|host-&gt;hostdata
suffix:semicolon
r_if
c_cond
(paren
id|inout
op_eq
l_int|1
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;ARXE 16-bit SCSI driver v%s&bslash;n&quot;
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
DECL|variable|arxescsi_template
r_static
id|Scsi_Host_Template
id|arxescsi_template
op_assign
(brace
dot
id|proc_info
op_assign
id|arxescsi_proc_info
comma
dot
id|name
op_assign
l_string|&quot;ARXE SCSI card&quot;
comma
dot
id|info
op_assign
id|arxescsi_info
comma
dot
id|queuecommand
op_assign
id|fas216_noqueue_command
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
l_int|0
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
l_string|&quot;arxescsi&quot;
comma
)brace
suffix:semicolon
r_static
r_int
id|__devinit
DECL|function|arxescsi_probe
id|arxescsi_probe
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
id|arxescsi_info
op_star
id|info
suffix:semicolon
r_int
r_int
id|resbase
comma
id|reslen
suffix:semicolon
r_void
id|__iomem
op_star
id|base
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|ret
op_assign
id|ecard_request_resources
c_func
(paren
id|ec
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
id|resbase
op_assign
id|ecard_resource_start
c_func
(paren
id|ec
comma
id|ECARD_RES_MEMC
)paren
suffix:semicolon
id|reslen
op_assign
id|ecard_resource_len
c_func
(paren
id|ec
comma
id|ECARD_RES_MEMC
)paren
suffix:semicolon
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
id|arxescsi_template
comma
r_sizeof
(paren
r_struct
id|arxescsi_info
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
id|info
op_assign
(paren
r_struct
id|arxescsi_info
op_star
)paren
id|host-&gt;hostdata
suffix:semicolon
id|info-&gt;ec
op_assign
id|ec
suffix:semicolon
id|info-&gt;base
op_assign
id|base
suffix:semicolon
id|info-&gt;info.scsi.io_base
op_assign
id|base
op_plus
l_int|0x2000
suffix:semicolon
id|info-&gt;info.scsi.irq
op_assign
id|NO_IRQ
suffix:semicolon
id|info-&gt;info.scsi.dma
op_assign
id|NO_DMA
suffix:semicolon
id|info-&gt;info.scsi.io_shift
op_assign
l_int|5
suffix:semicolon
id|info-&gt;info.ifcfg.clockrate
op_assign
l_int|24
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
l_int|0
suffix:semicolon
id|info-&gt;info.ifcfg.cntl3
op_assign
id|CNTL3_FASTSCSI
op_or
id|CNTL3_FASTCLK
suffix:semicolon
id|info-&gt;info.ifcfg.disconnect_ok
op_assign
l_int|0
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
id|arxescsi_dma_setup
suffix:semicolon
id|info-&gt;info.dma.pseudo
op_assign
id|arxescsi_dma_pseudo
suffix:semicolon
id|info-&gt;info.dma.stop
op_assign
id|arxescsi_dma_stop
suffix:semicolon
id|ec-&gt;irqaddr
op_assign
id|base
suffix:semicolon
id|ec-&gt;irqmask
op_assign
id|CSTATUS_IRQ
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
id|out_unregister
suffix:semicolon
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
id|fas216_release
c_func
(paren
id|host
)paren
suffix:semicolon
id|out_unregister
suffix:colon
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
id|ecard_release_resources
c_func
(paren
id|ec
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|arxescsi_remove
r_static
r_void
id|__devexit
id|arxescsi_remove
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
id|arxescsi_info
op_star
id|info
op_assign
(paren
r_struct
id|arxescsi_info
op_star
)paren
id|host-&gt;hostdata
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
id|iounmap
c_func
(paren
id|info-&gt;base
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
id|ecard_release_resources
c_func
(paren
id|ec
)paren
suffix:semicolon
)brace
DECL|variable|arxescsi_cids
r_static
r_const
r_struct
id|ecard_id
id|arxescsi_cids
(braket
)braket
op_assign
(brace
(brace
id|MANU_ARXE
comma
id|PROD_ARXE_SCSI
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
DECL|variable|arxescsi_driver
r_static
r_struct
id|ecard_driver
id|arxescsi_driver
op_assign
(brace
dot
id|probe
op_assign
id|arxescsi_probe
comma
dot
id|remove
op_assign
id|__devexit_p
c_func
(paren
id|arxescsi_remove
)paren
comma
dot
id|id_table
op_assign
id|arxescsi_cids
comma
dot
id|drv
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;arxescsi&quot;
comma
)brace
comma
)brace
suffix:semicolon
DECL|function|init_arxe_scsi_driver
r_static
r_int
id|__init
id|init_arxe_scsi_driver
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
id|arxescsi_driver
)paren
suffix:semicolon
)brace
DECL|function|exit_arxe_scsi_driver
r_static
r_void
id|__exit
id|exit_arxe_scsi_driver
c_func
(paren
r_void
)paren
(brace
id|ecard_remove_driver
c_func
(paren
op_amp
id|arxescsi_driver
)paren
suffix:semicolon
)brace
DECL|variable|init_arxe_scsi_driver
id|module_init
c_func
(paren
id|init_arxe_scsi_driver
)paren
suffix:semicolon
DECL|variable|exit_arxe_scsi_driver
id|module_exit
c_func
(paren
id|exit_arxe_scsi_driver
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Stefan Hanske&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;ARXESCSI driver for Acorn machines&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
