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
macro_line|#include &lt;scsi/scsi_host.h&gt;
macro_line|#ifndef bzero
DECL|macro|bzero
mdefine_line|#define bzero(d, n)&t;memset((d), 0, (n))
macro_line|#endif
multiline_comment|/*&n; *  General driver includes.&n; */
macro_line|#include &quot;sym_conf.h&quot;
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
DECL|macro|SYM_OPT_ANNOUNCE_TRANSFER_RATE
mdefine_line|#define&t;SYM_OPT_ANNOUNCE_TRANSFER_RATE
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
multiline_comment|/*&n; *  Insert a delay in micro-seconds&n; */
DECL|macro|sym_udelay
mdefine_line|#define sym_udelay(us)&t;udelay(us)
multiline_comment|/*&n; *  A &squot;read barrier&squot; flushes any data that have been prefetched &n; *  by the processor due to out of order execution. Such a barrier &n; *  must notably be inserted prior to looking at data that have &n; *  been DMAed, assuming that program does memory READs in proper &n; *  order and that the device ensured proper ordering of WRITEs.&n; *&n; *  A &squot;write barrier&squot; prevents any previous WRITEs to pass further &n; *  WRITEs. Such barriers must be inserted each time another agent &n; *  relies on ordering of WRITEs.&n; *&n; *  Note that, due to posting of PCI memory writes, we also must &n; *  insert dummy PCI read transactions when some ordering involving &n; *  both directions over the PCI does matter. PCI transactions are &n; *  fully ordered in each direction.&n; */
DECL|macro|MEMORY_READ_BARRIER
mdefine_line|#define MEMORY_READ_BARRIER()&t;rmb()
DECL|macro|MEMORY_WRITE_BARRIER
mdefine_line|#define MEMORY_WRITE_BARRIER()&t;wmb()
multiline_comment|/*&n; *  Let the compiler know about driver data structure names.&n; */
DECL|typedef|tcb_p
r_typedef
r_struct
id|sym_tcb
op_star
id|tcb_p
suffix:semicolon
DECL|typedef|lcb_p
r_typedef
r_struct
id|sym_lcb
op_star
id|lcb_p
suffix:semicolon
DECL|typedef|ccb_p
r_typedef
r_struct
id|sym_ccb
op_star
id|ccb_p
suffix:semicolon
DECL|typedef|hcb_p
r_typedef
r_struct
id|sym_hcb
op_star
id|hcb_p
suffix:semicolon
multiline_comment|/*&n; *  Define a reference to the O/S dependent IO request.&n; */
DECL|typedef|cam_ccb_p
r_typedef
r_struct
id|scsi_cmnd
op_star
id|cam_ccb_p
suffix:semicolon
multiline_comment|/* Generic */
DECL|typedef|cam_scsiio_p
r_typedef
r_struct
id|scsi_cmnd
op_star
id|cam_scsiio_p
suffix:semicolon
multiline_comment|/* SCSI I/O */
multiline_comment|/*&n; *  IO functions definition for big/little endian CPU support.&n; *  For now, PCI chips are only supported in little endian addressing mode, &n; */
macro_line|#ifdef&t;__BIG_ENDIAN
DECL|macro|inw_l2b
mdefine_line|#define&t;inw_l2b&t;&t;inw
DECL|macro|inl_l2b
mdefine_line|#define&t;inl_l2b&t;&t;inl
DECL|macro|outw_b2l
mdefine_line|#define&t;outw_b2l&t;outw
DECL|macro|outl_b2l
mdefine_line|#define&t;outl_b2l&t;outl
DECL|macro|readw_l2b
mdefine_line|#define&t;readw_l2b&t;readw
DECL|macro|readl_l2b
mdefine_line|#define&t;readl_l2b&t;readl
DECL|macro|writew_b2l
mdefine_line|#define&t;writew_b2l&t;writew
DECL|macro|writel_b2l
mdefine_line|#define&t;writel_b2l&t;writel
macro_line|#else&t;/* little endian */
DECL|macro|inw_raw
mdefine_line|#define&t;inw_raw&t;&t;inw
DECL|macro|inl_raw
mdefine_line|#define&t;inl_raw&t;&t;inl
DECL|macro|outw_raw
mdefine_line|#define&t;outw_raw&t;outw
DECL|macro|outl_raw
mdefine_line|#define&t;outl_raw&t;outl
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
multiline_comment|/*&n; *  If the chip uses big endian addressing mode over the &n; *  PCI, actual io register addresses for byte and word &n; *  accesses must be changed according to lane routing.&n; *  Btw, sym_offb() and sym_offw() macros only apply to &n; *  constants and so donnot generate bloated code.&n; */
macro_line|#if&t;defined(SYM_CONF_CHIP_BIG_ENDIAN)
DECL|macro|sym_offb
mdefine_line|#define sym_offb(o)&t;(((o)&amp;~3)+((~((o)&amp;3))&amp;3))
DECL|macro|sym_offw
mdefine_line|#define sym_offw(o)&t;(((o)&amp;~3)+((~((o)&amp;3))&amp;2))
macro_line|#else
DECL|macro|sym_offb
mdefine_line|#define sym_offb(o)&t;(o)
DECL|macro|sym_offw
mdefine_line|#define sym_offw(o)&t;(o)
macro_line|#endif
multiline_comment|/*&n; *  If the CPU and the chip use same endian-ness addressing,&n; *  no byte reordering is needed for script patching.&n; *  Macro cpu_to_scr() is to be used for script patching.&n; *  Macro scr_to_cpu() is to be used for getting a DWORD &n; *  from the script.&n; */
macro_line|#if&t;defined(__BIG_ENDIAN) &amp;&amp; !defined(SYM_CONF_CHIP_BIG_ENDIAN)
DECL|macro|cpu_to_scr
mdefine_line|#define cpu_to_scr(dw)&t;cpu_to_le32(dw)
DECL|macro|scr_to_cpu
mdefine_line|#define scr_to_cpu(dw)&t;le32_to_cpu(dw)
macro_line|#elif&t;defined(__LITTLE_ENDIAN) &amp;&amp; defined(SYM_CONF_CHIP_BIG_ENDIAN)
DECL|macro|cpu_to_scr
mdefine_line|#define cpu_to_scr(dw)&t;cpu_to_be32(dw)
DECL|macro|scr_to_cpu
mdefine_line|#define scr_to_cpu(dw)&t;be32_to_cpu(dw)
macro_line|#else
DECL|macro|cpu_to_scr
mdefine_line|#define cpu_to_scr(dw)&t;(dw)
DECL|macro|scr_to_cpu
mdefine_line|#define scr_to_cpu(dw)&t;(dw)
macro_line|#endif
multiline_comment|/*&n; *  Access to the controller chip.&n; *&n; *  If SYM_CONF_IOMAPPED is defined, the driver will use &n; *  normal IOs instead of the MEMORY MAPPED IO method  &n; *  recommended by PCI specifications.&n; *  If all PCI bridges, host brigdes and architectures &n; *  would have been correctly designed for PCI, this &n; *  option would be useless.&n; *&n; *  If the CPU and the chip use same endian-ness addressing,&n; *  no byte reordering is needed for accessing chip io &n; *  registers. Functions suffixed by &squot;_raw&squot; are assumed &n; *  to access the chip over the PCI without doing byte &n; *  reordering. Functions suffixed by &squot;_l2b&squot; are &n; *  assumed to perform little-endian to big-endian byte &n; *  reordering, those suffixed by &squot;_b2l&squot; blah, blah,&n; *  blah, ...&n; */
macro_line|#if defined(SYM_CONF_IOMAPPED)
multiline_comment|/*&n; *  IO mapped only input / ouput&n; */
DECL|macro|INB_OFF
mdefine_line|#define&t;INB_OFF(o)        inb (np-&gt;s.io_port + sym_offb(o))
DECL|macro|OUTB_OFF
mdefine_line|#define&t;OUTB_OFF(o, val)  outb ((val), np-&gt;s.io_port + sym_offb(o))
macro_line|#if&t;defined(__BIG_ENDIAN) &amp;&amp; !defined(SYM_CONF_CHIP_BIG_ENDIAN)
DECL|macro|INW_OFF
mdefine_line|#define&t;INW_OFF(o)        inw_l2b (np-&gt;s.io_port + sym_offw(o))
DECL|macro|INL_OFF
mdefine_line|#define&t;INL_OFF(o)        inl_l2b (np-&gt;s.io_port + (o))
DECL|macro|OUTW_OFF
mdefine_line|#define&t;OUTW_OFF(o, val)  outw_b2l ((val), np-&gt;s.io_port + sym_offw(o))
DECL|macro|OUTL_OFF
mdefine_line|#define&t;OUTL_OFF(o, val)  outl_b2l ((val), np-&gt;s.io_port + (o))
macro_line|#elif&t;defined(__LITTLE_ENDIAN) &amp;&amp; defined(SYM_CONF_CHIP_BIG_ENDIAN)
DECL|macro|INW_OFF
mdefine_line|#define&t;INW_OFF(o)        inw_b2l (np-&gt;s.io_port + sym_offw(o))
DECL|macro|INL_OFF
mdefine_line|#define&t;INL_OFF(o)        inl_b2l (np-&gt;s.io_port + (o))
DECL|macro|OUTW_OFF
mdefine_line|#define&t;OUTW_OFF(o, val)  outw_l2b ((val), np-&gt;s.io_port + sym_offw(o))
DECL|macro|OUTL_OFF
mdefine_line|#define&t;OUTL_OFF(o, val)  outl_l2b ((val), np-&gt;s.io_port + (o))
macro_line|#else
DECL|macro|INW_OFF
mdefine_line|#define&t;INW_OFF(o)        inw_raw (np-&gt;s.io_port + sym_offw(o))
DECL|macro|INL_OFF
mdefine_line|#define&t;INL_OFF(o)        inl_raw (np-&gt;s.io_port + (o))
DECL|macro|OUTW_OFF
mdefine_line|#define&t;OUTW_OFF(o, val)  outw_raw ((val), np-&gt;s.io_port + sym_offw(o))
DECL|macro|OUTL_OFF
mdefine_line|#define&t;OUTL_OFF(o, val)  outl_raw ((val), np-&gt;s.io_port + (o))
macro_line|#endif&t;/* ENDIANs */
macro_line|#else&t;/* defined SYM_CONF_IOMAPPED */
multiline_comment|/*&n; *  MEMORY mapped IO input / output&n; */
DECL|macro|INB_OFF
mdefine_line|#define INB_OFF(o)        readb(np-&gt;s.mmio_va + sym_offb(o))
DECL|macro|OUTB_OFF
mdefine_line|#define OUTB_OFF(o, val)  writeb((val), np-&gt;s.mmio_va + sym_offb(o))
macro_line|#if&t;defined(__BIG_ENDIAN) &amp;&amp; !defined(SYM_CONF_CHIP_BIG_ENDIAN)
DECL|macro|INW_OFF
mdefine_line|#define INW_OFF(o)        readw_l2b(np-&gt;s.mmio_va + sym_offw(o))
DECL|macro|INL_OFF
mdefine_line|#define INL_OFF(o)        readl_l2b(np-&gt;s.mmio_va + (o))
DECL|macro|OUTW_OFF
mdefine_line|#define OUTW_OFF(o, val)  writew_b2l((val), np-&gt;s.mmio_va + sym_offw(o))
DECL|macro|OUTL_OFF
mdefine_line|#define OUTL_OFF(o, val)  writel_b2l((val), np-&gt;s.mmio_va + (o))
macro_line|#elif&t;defined(__LITTLE_ENDIAN) &amp;&amp; defined(SYM_CONF_CHIP_BIG_ENDIAN)
DECL|macro|INW_OFF
mdefine_line|#define INW_OFF(o)        readw_b2l(np-&gt;s.mmio_va + sym_offw(o))
DECL|macro|INL_OFF
mdefine_line|#define INL_OFF(o)        readl_b2l(np-&gt;s.mmio_va + (o))
DECL|macro|OUTW_OFF
mdefine_line|#define OUTW_OFF(o, val)  writew_l2b((val), np-&gt;s.mmio_va + sym_offw(o))
DECL|macro|OUTL_OFF
mdefine_line|#define OUTL_OFF(o, val)  writel_l2b((val), np-&gt;s.mmio_va + (o))
macro_line|#else
DECL|macro|INW_OFF
mdefine_line|#define INW_OFF(o)        readw_raw(np-&gt;s.mmio_va + sym_offw(o))
DECL|macro|INL_OFF
mdefine_line|#define INL_OFF(o)        readl_raw(np-&gt;s.mmio_va + (o))
DECL|macro|OUTW_OFF
mdefine_line|#define OUTW_OFF(o, val)  writew_raw((val), np-&gt;s.mmio_va + sym_offw(o))
DECL|macro|OUTL_OFF
mdefine_line|#define OUTL_OFF(o, val)  writel_raw((val), np-&gt;s.mmio_va + (o))
macro_line|#endif
macro_line|#endif&t;/* defined SYM_CONF_IOMAPPED */
DECL|macro|OUTRAM_OFF
mdefine_line|#define OUTRAM_OFF(o, a, l) memcpy_toio(np-&gt;s.ram_va + (o), (a), (l))
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
DECL|member|mmio_va
r_void
id|__iomem
op_star
id|mmio_va
suffix:semicolon
multiline_comment|/* MMIO kernel virtual address&t;*/
DECL|member|ram_va
r_void
id|__iomem
op_star
id|ram_va
suffix:semicolon
multiline_comment|/* RAM  kernel virtual address&t;*/
DECL|member|io_port
id|u_long
id|io_port
suffix:semicolon
multiline_comment|/* IO port address cookie&t;*/
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
multiline_comment|/*&n; *  Data structure used as input for the NVRAM reading.&n; *  Must resolve the IO macros and sym_name(), when  &n; *  used as sub-field &squot;s&squot; of another structure.&n; */
DECL|struct|sym_slot
r_struct
id|sym_slot
(brace
DECL|member|base
id|u_long
id|base
suffix:semicolon
DECL|member|base_2
id|u_long
id|base_2
suffix:semicolon
DECL|member|base_c
id|u_long
id|base_c
suffix:semicolon
DECL|member|base_2_c
id|u_long
id|base_2_c
suffix:semicolon
DECL|member|irq
r_int
id|irq
suffix:semicolon
multiline_comment|/* port and address fields to fit INB, OUTB macros */
DECL|member|io_port
id|u_long
id|io_port
suffix:semicolon
DECL|member|mmio_va
r_void
id|__iomem
op_star
id|mmio_va
suffix:semicolon
DECL|member|inst_name
r_char
id|inst_name
(braket
l_int|16
)braket
suffix:semicolon
)brace
suffix:semicolon
r_struct
id|sym_nvram
suffix:semicolon
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
DECL|member|s
r_struct
id|sym_slot
id|s
suffix:semicolon
DECL|member|chip
r_struct
id|sym_pci_chip
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
multiline_comment|/*&n; *  The driver definitions (sym_hipd.h) must know about a &n; *  couple of things related to the memory allocator.&n; */
DECL|typedef|m_addr_t
r_typedef
id|u_long
id|m_addr_t
suffix:semicolon
multiline_comment|/* Enough bits to represent any address */
DECL|macro|SYM_MEM_PAGE_ORDER
mdefine_line|#define SYM_MEM_PAGE_ORDER 0&t;/* 1 PAGE  maximum */
DECL|macro|SYM_MEM_CLUSTER_SHIFT
mdefine_line|#define SYM_MEM_CLUSTER_SHIFT&t;(PAGE_SHIFT+SYM_MEM_PAGE_ORDER)
macro_line|#ifdef&t;MODULE
DECL|macro|SYM_MEM_FREE_UNUSED
mdefine_line|#define SYM_MEM_FREE_UNUSED&t;/* Free unused pages immediately */
macro_line|#endif
DECL|typedef|m_pool_ident_t
r_typedef
r_struct
id|pci_dev
op_star
id|m_pool_ident_t
suffix:semicolon
multiline_comment|/*&n; *  Include driver soft definitions.&n; */
macro_line|#include &quot;sym_fw.h&quot;
macro_line|#include &quot;sym_hipd.h&quot;
multiline_comment|/*&n; *  Memory allocator related stuff.&n; */
DECL|macro|SYM_MEM_GFP_FLAGS
mdefine_line|#define SYM_MEM_GFP_FLAGS&t;GFP_ATOMIC
DECL|macro|SYM_MEM_WARN
mdefine_line|#define SYM_MEM_WARN&t;1&t;/* Warn on failed operations */
DECL|macro|sym_get_mem_cluster
mdefine_line|#define sym_get_mem_cluster()&t;&bslash;&n;&t;__get_free_pages(SYM_MEM_GFP_FLAGS, SYM_MEM_PAGE_ORDER)
DECL|macro|sym_free_mem_cluster
mdefine_line|#define sym_free_mem_cluster(p)&t;&bslash;&n;&t;free_pages(p, SYM_MEM_PAGE_ORDER)
r_void
op_star
id|sym_calloc
c_func
(paren
r_int
id|size
comma
r_char
op_star
id|name
)paren
suffix:semicolon
r_void
id|sym_mfree
c_func
(paren
r_void
op_star
id|m
comma
r_int
id|size
comma
r_char
op_star
id|name
)paren
suffix:semicolon
multiline_comment|/*&n; *  We have to provide the driver memory allocator with methods for &n; *  it to maintain virtual to bus physical address translations.&n; */
DECL|macro|sym_m_pool_match
mdefine_line|#define sym_m_pool_match(mp_id1, mp_id2)&t;(mp_id1 == mp_id2)
DECL|function|sym_m_get_dma_mem_cluster
r_static
id|__inline
id|m_addr_t
id|sym_m_get_dma_mem_cluster
c_func
(paren
id|m_pool_p
id|mp
comma
id|m_vtob_p
id|vbp
)paren
(brace
r_void
op_star
id|vaddr
op_assign
l_int|NULL
suffix:semicolon
id|dma_addr_t
id|baddr
op_assign
l_int|0
suffix:semicolon
id|vaddr
op_assign
id|pci_alloc_consistent
c_func
(paren
id|mp-&gt;dev_dmat
comma
id|SYM_MEM_CLUSTER_SIZE
comma
op_amp
id|baddr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vaddr
)paren
(brace
id|vbp-&gt;vaddr
op_assign
(paren
id|m_addr_t
)paren
id|vaddr
suffix:semicolon
id|vbp-&gt;baddr
op_assign
(paren
id|m_addr_t
)paren
id|baddr
suffix:semicolon
)brace
r_return
(paren
id|m_addr_t
)paren
id|vaddr
suffix:semicolon
)brace
DECL|function|sym_m_free_dma_mem_cluster
r_static
id|__inline
r_void
id|sym_m_free_dma_mem_cluster
c_func
(paren
id|m_pool_p
id|mp
comma
id|m_vtob_p
id|vbp
)paren
(brace
id|pci_free_consistent
c_func
(paren
id|mp-&gt;dev_dmat
comma
id|SYM_MEM_CLUSTER_SIZE
comma
(paren
r_void
op_star
)paren
id|vbp-&gt;vaddr
comma
(paren
id|dma_addr_t
)paren
id|vbp-&gt;baddr
)paren
suffix:semicolon
)brace
DECL|macro|sym_m_create_dma_mem_tag
mdefine_line|#define sym_m_create_dma_mem_tag(mp)&t;(0)
DECL|macro|sym_m_delete_dma_mem_tag
mdefine_line|#define sym_m_delete_dma_mem_tag(mp)&t;do { ; } while (0)
r_void
op_star
id|__sym_calloc_dma
c_func
(paren
id|m_pool_ident_t
id|dev_dmat
comma
r_int
id|size
comma
r_char
op_star
id|name
)paren
suffix:semicolon
r_void
id|__sym_mfree_dma
c_func
(paren
id|m_pool_ident_t
id|dev_dmat
comma
r_void
op_star
id|m
comma
r_int
id|size
comma
r_char
op_star
id|name
)paren
suffix:semicolon
id|m_addr_t
id|__vtobus
c_func
(paren
id|m_pool_ident_t
id|dev_dmat
comma
r_void
op_star
id|m
)paren
suffix:semicolon
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
id|ccb
comma
r_int
id|status
)paren
(brace
id|ccb-&gt;result
op_and_assign
op_complement
(paren
l_int|0xff
op_lshift
l_int|16
)paren
suffix:semicolon
id|ccb-&gt;result
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
id|ccb
)paren
(brace
r_return
(paren
(paren
id|ccb-&gt;result
op_rshift
l_int|16
)paren
op_amp
l_int|0xff
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *  The dma mapping is mostly handled by the &n; *  SCSI layer and the driver glue under Linux.&n; */
DECL|macro|sym_data_dmamap_create
mdefine_line|#define sym_data_dmamap_create(np, cp)&t;&t;(0)
DECL|macro|sym_data_dmamap_destroy
mdefine_line|#define sym_data_dmamap_destroy(np, cp)&t;&t;do { ; } while (0)
DECL|macro|sym_data_dmamap_unload
mdefine_line|#define sym_data_dmamap_unload(np, cp)&t;&t;do { ; } while (0)
DECL|macro|sym_data_dmamap_presync
mdefine_line|#define sym_data_dmamap_presync(np, cp)&t;&t;do { ; } while (0)
DECL|macro|sym_data_dmamap_postsync
mdefine_line|#define sym_data_dmamap_postsync(np, cp)&t;do { ; } while (0)
multiline_comment|/*&n; *  Async handler for negotiations.&n; */
r_void
id|sym_xpt_async_nego_wide
c_func
(paren
id|hcb_p
id|np
comma
r_int
id|target
)paren
suffix:semicolon
DECL|macro|sym_xpt_async_nego_sync
mdefine_line|#define sym_xpt_async_nego_sync(np, target)&t;&bslash;&n;&t;sym_announce_transfer_rate(np, target)
DECL|macro|sym_xpt_async_nego_ppr
mdefine_line|#define sym_xpt_async_nego_ppr(np, target)&t;&bslash;&n;&t;sym_announce_transfer_rate(np, target)
multiline_comment|/*&n; *  Build CAM result for a successful IO and for a failed IO.&n; */
DECL|function|sym_set_cam_result_ok
r_static
id|__inline
r_void
id|sym_set_cam_result_ok
c_func
(paren
id|hcb_p
id|np
comma
id|ccb_p
id|cp
comma
r_int
id|resid
)paren
(brace
r_struct
id|scsi_cmnd
op_star
id|cmd
op_assign
id|cp-&gt;cam_ccb
suffix:semicolon
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
id|hcb_p
id|np
comma
id|ccb_p
id|cp
comma
r_int
id|resid
)paren
suffix:semicolon
multiline_comment|/*&n; *  Other O/S specific methods.&n; */
DECL|macro|sym_cam_target_id
mdefine_line|#define sym_cam_target_id(ccb)&t;(ccb)-&gt;target
DECL|macro|sym_cam_target_lun
mdefine_line|#define sym_cam_target_lun(ccb)&t;(ccb)-&gt;lun
DECL|macro|sym_freeze_cam_ccb
mdefine_line|#define&t;sym_freeze_cam_ccb(ccb)&t;do { ; } while (0)
r_void
id|sym_xpt_done
c_func
(paren
id|hcb_p
id|np
comma
id|cam_ccb_p
id|ccb
)paren
suffix:semicolon
r_void
id|sym_xpt_done2
c_func
(paren
id|hcb_p
id|np
comma
id|cam_ccb_p
id|ccb
comma
r_int
id|cam_status
)paren
suffix:semicolon
r_void
id|sym_print_addr
(paren
id|ccb_p
id|cp
)paren
suffix:semicolon
r_void
id|sym_xpt_async_bus_reset
c_func
(paren
id|hcb_p
id|np
)paren
suffix:semicolon
r_void
id|sym_xpt_async_sent_bdr
c_func
(paren
id|hcb_p
id|np
comma
r_int
id|target
)paren
suffix:semicolon
r_int
id|sym_setup_data_and_start
(paren
id|hcb_p
id|np
comma
id|cam_scsiio_p
id|csio
comma
id|ccb_p
id|cp
)paren
suffix:semicolon
r_void
id|sym_log_bus_error
c_func
(paren
id|hcb_p
id|np
)paren
suffix:semicolon
r_void
id|sym_sniff_inquiry
c_func
(paren
id|hcb_p
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
