multiline_comment|/*&n; * Device driver for the SYMBIOS/LSILOGIC 53C8XX and 53C1010 family &n; * of PCI-SCSI IO processors.&n; *&n; * Copyright (C) 1999-2001  Gerard Roudier &lt;groudier@free.fr&gt;&n; *&n; * This driver is derived from the Linux sym53c8xx driver.&n; * Copyright (C) 1998-2000  Gerard Roudier&n; *&n; * The sym53c8xx driver is derived from the ncr53c8xx driver that had been &n; * a port of the FreeBSD ncr driver to Linux-1.2.13.&n; *&n; * The original ncr driver has been written for 386bsd and FreeBSD by&n; *         Wolfgang Stanglmeier        &lt;wolf@cologne.de&gt;&n; *         Stefan Esser                &lt;se@mi.Uni-Koeln.de&gt;&n; * Copyright (C) 1994  Wolfgang Stanglmeier&n; *&n; * Other major contributions:&n; *&n; * NVRAM detection and reading.&n; * Copyright (C) 1997 Richard Waltham &lt;dormouse@farsrobt.demon.co.uk&gt;&n; *&n; *-----------------------------------------------------------------------------&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef SYM_GLUE_H
DECL|macro|SYM_GLUE_H
mdefine_line|#define SYM_GLUE_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#ifdef __sparc__
macro_line|#  include &lt;asm/irq.h&gt;
macro_line|#endif
macro_line|#include &lt;scsi/scsi.h&gt;
macro_line|#include &lt;scsi/scsi_cmnd.h&gt;
macro_line|#include &lt;scsi/scsi_device.h&gt;
macro_line|#include &lt;scsi/scsi_transport_spi.h&gt;
macro_line|#include &lt;scsi/scsi_host.h&gt;
macro_line|#include &quot;sym53c8xx.h&quot;
macro_line|#include &quot;sym_defs.h&quot;
macro_line|#include &quot;sym_misc.h&quot;
multiline_comment|/*&n; * Configuration addendum for Linux.&n; */
DECL|macro|SYM_CONF_TIMER_INTERVAL
mdefine_line|#define&t;SYM_CONF_TIMER_INTERVAL&t;&t;((HZ+1)/2)
DECL|macro|SYM_OPT_HANDLE_DIR_UNKNOWN
mdefine_line|#define SYM_OPT_HANDLE_DIR_UNKNOWN
DECL|macro|SYM_OPT_HANDLE_DEVICE_QUEUEING
mdefine_line|#define SYM_OPT_HANDLE_DEVICE_QUEUEING
DECL|macro|SYM_OPT_LIMIT_COMMAND_REORDERING
mdefine_line|#define SYM_OPT_LIMIT_COMMAND_REORDERING
multiline_comment|/*&n; *  Print a message with severity.&n; */
DECL|macro|printf_emerg
mdefine_line|#define printf_emerg(args...)&t;printk(KERN_EMERG args)
DECL|macro|printf_alert
mdefine_line|#define&t;printf_alert(args...)&t;printk(KERN_ALERT args)
DECL|macro|printf_crit
mdefine_line|#define&t;printf_crit(args...)&t;printk(KERN_CRIT args)
DECL|macro|printf_err
mdefine_line|#define&t;printf_err(args...)&t;printk(KERN_ERR&t;args)
DECL|macro|printf_warning
mdefine_line|#define&t;printf_warning(args...)&t;printk(KERN_WARNING args)
DECL|macro|printf_notice
mdefine_line|#define&t;printf_notice(args...)&t;printk(KERN_NOTICE args)
DECL|macro|printf_info
mdefine_line|#define&t;printf_info(args...)&t;printk(KERN_INFO args)
DECL|macro|printf_debug
mdefine_line|#define&t;printf_debug(args...)&t;printk(KERN_DEBUG args)
DECL|macro|printf
mdefine_line|#define&t;printf(args...)&t;&t;printk(args)
multiline_comment|/*&n; *  A &squot;read barrier&squot; flushes any data that have been prefetched &n; *  by the processor due to out of order execution. Such a barrier &n; *  must notably be inserted prior to looking at data that have &n; *  been DMAed, assuming that program does memory READs in proper &n; *  order and that the device ensured proper ordering of WRITEs.&n; *&n; *  A &squot;write barrier&squot; prevents any previous WRITEs to pass further &n; *  WRITEs. Such barriers must be inserted each time another agent &n; *  relies on ordering of WRITEs.&n; *&n; *  Note that, due to posting of PCI memory writes, we also must &n; *  insert dummy PCI read transactions when some ordering involving &n; *  both directions over the PCI does matter. PCI transactions are &n; *  fully ordered in each direction.&n; */
DECL|macro|MEMORY_READ_BARRIER
mdefine_line|#define MEMORY_READ_BARRIER()&t;rmb()
DECL|macro|MEMORY_WRITE_BARRIER
mdefine_line|#define MEMORY_WRITE_BARRIER()&t;wmb()
multiline_comment|/*&n; *  IO functions definition for big/little endian CPU support.&n; *  For now, PCI chips are only supported in little endian addressing mode, &n; */
macro_line|#ifdef&t;__BIG_ENDIAN
DECL|macro|readw_l2b
mdefine_line|#define&t;readw_l2b&t;readw
DECL|macro|readl_l2b
mdefine_line|#define&t;readl_l2b&t;readl
DECL|macro|writew_b2l
mdefine_line|#define&t;writew_b2l&t;writew
DECL|macro|writel_b2l
mdefine_line|#define&t;writel_b2l&t;writel
macro_line|#else&t;/* little endian */
DECL|macro|readw_raw
mdefine_line|#define&t;readw_raw&t;readw
DECL|macro|readl_raw
mdefine_line|#define&t;readl_raw&t;readl
DECL|macro|writew_raw
mdefine_line|#define&t;writew_raw&t;writew
DECL|macro|writel_raw
mdefine_line|#define&t;writel_raw&t;writel
macro_line|#endif /* endian */
macro_line|#ifdef&t;SYM_CONF_CHIP_BIG_ENDIAN
macro_line|#error&t;&quot;Chips in BIG ENDIAN addressing mode are not (yet) supported&quot;
macro_line|#endif
multiline_comment|/*&n; *  If the CPU and the chip use same endian-ness addressing,&n; *  no byte reordering is needed for script patching.&n; *  Macro cpu_to_scr() is to be used for script patching.&n; *  Macro scr_to_cpu() is to be used for getting a DWORD &n; *  from the script.&n; */
DECL|macro|cpu_to_scr
mdefine_line|#define cpu_to_scr(dw)&t;cpu_to_le32(dw)
DECL|macro|scr_to_cpu
mdefine_line|#define scr_to_cpu(dw)&t;le32_to_cpu(dw)
multiline_comment|/*&n; *  Remap some status field values.&n; */
DECL|macro|CAM_REQ_CMP
mdefine_line|#define CAM_REQ_CMP&t;&t;DID_OK
DECL|macro|CAM_SEL_TIMEOUT
mdefine_line|#define CAM_SEL_TIMEOUT&t;&t;DID_NO_CONNECT
DECL|macro|CAM_CMD_TIMEOUT
mdefine_line|#define CAM_CMD_TIMEOUT&t;&t;DID_TIME_OUT
DECL|macro|CAM_REQ_ABORTED
mdefine_line|#define CAM_REQ_ABORTED&t;&t;DID_ABORT
DECL|macro|CAM_UNCOR_PARITY
mdefine_line|#define CAM_UNCOR_PARITY&t;DID_PARITY
DECL|macro|CAM_SCSI_BUS_RESET
mdefine_line|#define CAM_SCSI_BUS_RESET&t;DID_RESET&t;
DECL|macro|CAM_REQUEUE_REQ
mdefine_line|#define CAM_REQUEUE_REQ&t;&t;DID_SOFT_ERROR
DECL|macro|CAM_UNEXP_BUSFREE
mdefine_line|#define&t;CAM_UNEXP_BUSFREE&t;DID_ERROR
DECL|macro|CAM_SCSI_BUSY
mdefine_line|#define&t;CAM_SCSI_BUSY&t;&t;DID_BUS_BUSY
DECL|macro|CAM_DEV_NOT_THERE
mdefine_line|#define&t;CAM_DEV_NOT_THERE&t;DID_NO_CONNECT
DECL|macro|CAM_REQ_INVALID
mdefine_line|#define&t;CAM_REQ_INVALID&t;&t;DID_ERROR
DECL|macro|CAM_REQ_TOO_BIG
mdefine_line|#define&t;CAM_REQ_TOO_BIG&t;&t;DID_ERROR
DECL|macro|CAM_RESRC_UNAVAIL
mdefine_line|#define&t;CAM_RESRC_UNAVAIL&t;DID_ERROR
multiline_comment|/*&n; *  Remap data direction values.&n; */
DECL|macro|CAM_DIR_NONE
mdefine_line|#define CAM_DIR_NONE&t;&t;DMA_NONE
DECL|macro|CAM_DIR_IN
mdefine_line|#define CAM_DIR_IN&t;&t;DMA_FROM_DEVICE
DECL|macro|CAM_DIR_OUT
mdefine_line|#define CAM_DIR_OUT&t;&t;DMA_TO_DEVICE
DECL|macro|CAM_DIR_UNKNOWN
mdefine_line|#define CAM_DIR_UNKNOWN&t;&t;DMA_BIDIRECTIONAL
multiline_comment|/*&n; *  These ones are used as return code from &n; *  error recovery handlers under Linux.&n; */
DECL|macro|SCSI_SUCCESS
mdefine_line|#define SCSI_SUCCESS&t;SUCCESS
DECL|macro|SCSI_FAILED
mdefine_line|#define SCSI_FAILED&t;FAILED
multiline_comment|/*&n; *  System specific target data structure.&n; *  None for now, under Linux.&n; */
multiline_comment|/* #define SYM_HAVE_STCB */
multiline_comment|/*&n; *  System specific lun data structure.&n; */
DECL|macro|SYM_HAVE_SLCB
mdefine_line|#define SYM_HAVE_SLCB
DECL|struct|sym_slcb
r_struct
id|sym_slcb
(brace
DECL|member|reqtags
id|u_short
id|reqtags
suffix:semicolon
multiline_comment|/* Number of tags requested by user */
DECL|member|scdev_depth
id|u_short
id|scdev_depth
suffix:semicolon
multiline_comment|/* Queue depth set in select_queue_depth() */
)brace
suffix:semicolon
multiline_comment|/*&n; *  System specific command data structure.&n; *  Not needed under Linux.&n; */
multiline_comment|/* struct sym_sccb */
multiline_comment|/*&n; *  System specific host data structure.&n; */
DECL|struct|sym_shcb
r_struct
id|sym_shcb
(brace
multiline_comment|/*&n;&t; *  Chip and controller indentification.&n;&t; */
DECL|member|unit
r_int
id|unit
suffix:semicolon
DECL|member|inst_name
r_char
id|inst_name
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|chip_name
r_char
id|chip_name
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|device
r_struct
id|pci_dev
op_star
id|device
suffix:semicolon
DECL|member|host
r_struct
id|Scsi_Host
op_star
id|host
suffix:semicolon
DECL|member|ioaddr
r_void
id|__iomem
op_star
id|ioaddr
suffix:semicolon
multiline_comment|/* MMIO kernel io address&t;*/
DECL|member|ramaddr
r_void
id|__iomem
op_star
id|ramaddr
suffix:semicolon
multiline_comment|/* RAM  kernel io address&t;*/
DECL|member|io_ws
id|u_short
id|io_ws
suffix:semicolon
multiline_comment|/* IO window size&t;&t;*/
DECL|member|irq
r_int
id|irq
suffix:semicolon
multiline_comment|/* IRQ number&t;&t;&t;*/
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
multiline_comment|/* Timer handler link header&t;*/
DECL|member|lasttime
id|u_long
id|lasttime
suffix:semicolon
DECL|member|settle_time
id|u_long
id|settle_time
suffix:semicolon
multiline_comment|/* Resetting the SCSI BUS&t;*/
DECL|member|settle_time_valid
id|u_char
id|settle_time_valid
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; *  Return the name of the controller.&n; */
DECL|macro|sym_name
mdefine_line|#define sym_name(np) (np)-&gt;s.inst_name
r_struct
id|sym_nvram
suffix:semicolon
multiline_comment|/*&n; * The IO macros require a struct called &squot;s&squot; and are abused in sym_nvram.c&n; */
DECL|struct|sym_device
r_struct
id|sym_device
(brace
DECL|member|pdev
r_struct
id|pci_dev
op_star
id|pdev
suffix:semicolon
DECL|member|mmio_base
r_int
r_int
id|mmio_base
suffix:semicolon
DECL|member|ram_base
r_int
r_int
id|ram_base
suffix:semicolon
r_struct
(brace
DECL|member|ioaddr
r_void
id|__iomem
op_star
id|ioaddr
suffix:semicolon
DECL|member|ramaddr
r_void
id|__iomem
op_star
id|ramaddr
suffix:semicolon
DECL|member|s
)brace
id|s
suffix:semicolon
DECL|member|chip
r_struct
id|sym_chip
id|chip
suffix:semicolon
DECL|member|nvram
r_struct
id|sym_nvram
op_star
id|nvram
suffix:semicolon
DECL|member|device_id
id|u_short
id|device_id
suffix:semicolon
DECL|member|host_id
id|u_char
id|host_id
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; *  Driver host data structure.&n; */
DECL|struct|host_data
r_struct
id|host_data
(brace
DECL|member|ncb
r_struct
id|sym_hcb
op_star
id|ncb
suffix:semicolon
)brace
suffix:semicolon
DECL|function|sym_get_hcb
r_static
r_inline
r_struct
id|sym_hcb
op_star
id|sym_get_hcb
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|host
)paren
(brace
r_return
(paren
(paren
r_struct
id|host_data
op_star
)paren
id|host-&gt;hostdata
)paren
op_member_access_from_pointer
id|ncb
suffix:semicolon
)brace
macro_line|#include &quot;sym_fw.h&quot;
macro_line|#include &quot;sym_hipd.h&quot;
multiline_comment|/*&n; *  Set the status field of a CAM CCB.&n; */
r_static
id|__inline
r_void
DECL|function|sym_set_cam_status
id|sym_set_cam_status
c_func
(paren
r_struct
id|scsi_cmnd
op_star
id|cmd
comma
r_int
id|status
)paren
(brace
id|cmd-&gt;result
op_and_assign
op_complement
(paren
l_int|0xff
op_lshift
l_int|16
)paren
suffix:semicolon
id|cmd-&gt;result
op_or_assign
(paren
id|status
op_lshift
l_int|16
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *  Get the status field of a CAM CCB.&n; */
r_static
id|__inline
r_int
DECL|function|sym_get_cam_status
id|sym_get_cam_status
c_func
(paren
r_struct
id|scsi_cmnd
op_star
id|cmd
)paren
(brace
r_return
id|host_byte
c_func
(paren
id|cmd-&gt;result
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *  Build CAM result for a successful IO and for a failed IO.&n; */
DECL|function|sym_set_cam_result_ok
r_static
id|__inline
r_void
id|sym_set_cam_result_ok
c_func
(paren
r_struct
id|sym_ccb
op_star
id|cp
comma
r_struct
id|scsi_cmnd
op_star
id|cmd
comma
r_int
id|resid
)paren
(brace
id|cmd-&gt;resid
op_assign
id|resid
suffix:semicolon
id|cmd-&gt;result
op_assign
(paren
(paren
(paren
id|DID_OK
)paren
op_lshift
l_int|16
)paren
op_plus
(paren
(paren
id|cp-&gt;ssss_status
)paren
op_amp
l_int|0x7f
)paren
)paren
suffix:semicolon
)brace
r_void
id|sym_set_cam_result_error
c_func
(paren
r_struct
id|sym_hcb
op_star
id|np
comma
r_struct
id|sym_ccb
op_star
id|cp
comma
r_int
id|resid
)paren
suffix:semicolon
r_void
id|sym_xpt_done
c_func
(paren
r_struct
id|sym_hcb
op_star
id|np
comma
r_struct
id|scsi_cmnd
op_star
id|ccb
)paren
suffix:semicolon
DECL|macro|sym_print_addr
mdefine_line|#define sym_print_addr(cmd, arg...) dev_info(&amp;cmd-&gt;device-&gt;sdev_gendev , ## arg)
r_void
id|sym_xpt_async_bus_reset
c_func
(paren
r_struct
id|sym_hcb
op_star
id|np
)paren
suffix:semicolon
r_void
id|sym_xpt_async_sent_bdr
c_func
(paren
r_struct
id|sym_hcb
op_star
id|np
comma
r_int
id|target
)paren
suffix:semicolon
r_int
id|sym_setup_data_and_start
(paren
r_struct
id|sym_hcb
op_star
id|np
comma
r_struct
id|scsi_cmnd
op_star
id|csio
comma
r_struct
id|sym_ccb
op_star
id|cp
)paren
suffix:semicolon
r_void
id|sym_log_bus_error
c_func
(paren
r_struct
id|sym_hcb
op_star
id|np
)paren
suffix:semicolon
r_void
id|sym_sniff_inquiry
c_func
(paren
r_struct
id|sym_hcb
op_star
id|np
comma
r_struct
id|scsi_cmnd
op_star
id|cmd
comma
r_int
id|resid
)paren
suffix:semicolon
macro_line|#endif /* SYM_GLUE_H */
eof
