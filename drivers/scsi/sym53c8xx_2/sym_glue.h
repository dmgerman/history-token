multiline_comment|/*&n; * Device driver for the SYMBIOS/LSILOGIC 53C8XX and 53C1010 family &n; * of PCI-SCSI IO processors.&n; *&n; * Copyright (C) 1999-2001  Gerard Roudier &lt;groudier@free.fr&gt;&n; *&n; * This driver is derived from the Linux sym53c8xx driver.&n; * Copyright (C) 1998-2000  Gerard Roudier&n; *&n; * The sym53c8xx driver is derived from the ncr53c8xx driver that had been &n; * a port of the FreeBSD ncr driver to Linux-1.2.13.&n; *&n; * The original ncr driver has been written for 386bsd and FreeBSD by&n; *         Wolfgang Stanglmeier        &lt;wolf@cologne.de&gt;&n; *         Stefan Esser                &lt;se@mi.Uni-Koeln.de&gt;&n; * Copyright (C) 1994  Wolfgang Stanglmeier&n; *&n; * Other major contributions:&n; *&n; * NVRAM detection and reading.&n; * Copyright (C) 1997 Richard Waltham &lt;dormouse@farsrobt.demon.co.uk&gt;&n; *&n; *-----------------------------------------------------------------------------&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions and the following disclaimer.&n; * 2. The name of the author may not be used to endorse or promote products&n; *    derived from this software without specific prior written permission.&n; *&n; * Where this Software is combined with software released under the terms of &n; * the GNU Public License (&quot;GPL&quot;) and the terms of the GPL would require the &n; * combined work to also be released under the terms of the GPL, the terms&n; * and conditions of this License will apply in addition to those of the&n; * GPL with the exception of any terms or conditions of this License that&n; * conflict with, or are expressly prohibited by, the GPL.&n; *&n; * THIS SOFTWARE IS PROVIDED BY THE AUTHORS AND CONTRIBUTORS ``AS IS&squot;&squot; AND&n; * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE&n; * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE&n; * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR&n; * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT&n; * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY&n; * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF&n; * SUCH DAMAGE.&n; */
macro_line|#ifndef SYM_GLUE_H
DECL|macro|SYM_GLUE_H
mdefine_line|#define SYM_GLUE_H
macro_line|#if 0
mdefine_line|#define SYM_CONF_DMA_ADDRESSING_MODE 2
macro_line|#endif
DECL|macro|LinuxVersionCode
mdefine_line|#define LinuxVersionCode(v, p, s) (((v)&lt;&lt;16)+((p)&lt;&lt;8)+(s))
macro_line|#include &lt;linux/version.h&gt;
macro_line|#if&t;LINUX_VERSION_CODE &lt; LinuxVersionCode(2, 2, 0)
macro_line|#error&t;&quot;This driver requires a kernel version not lower than 2.2.0&quot;
macro_line|#endif
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#if LINUX_VERSION_CODE &gt;= LinuxVersionCode(2,3,17)
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#else
macro_line|#include &lt;asm/spinlock.h&gt;
macro_line|#endif
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#ifdef __sparc__
macro_line|#  include &lt;asm/irq.h&gt;
macro_line|#endif
macro_line|#include &lt;linux/init.h&gt;
macro_line|#ifndef&t;__init
DECL|macro|__init
mdefine_line|#define&t;__init
macro_line|#endif
macro_line|#ifndef&t;__initdata
DECL|macro|__initdata
mdefine_line|#define&t;__initdata
macro_line|#endif
macro_line|#include &quot;../scsi.h&quot;
macro_line|#include &quot;../hosts.h&quot;
macro_line|#include &quot;../constants.h&quot;
macro_line|#include &quot;../sd.h&quot;
macro_line|#include &lt;linux/types.h&gt;
multiline_comment|/*&n; *  Define BITS_PER_LONG for earlier linux versions.&n; */
macro_line|#ifndef&t;BITS_PER_LONG
macro_line|#if (~0UL) == 0xffffffffUL
DECL|macro|BITS_PER_LONG
mdefine_line|#define&t;BITS_PER_LONG&t;32
macro_line|#else
DECL|macro|BITS_PER_LONG
mdefine_line|#define&t;BITS_PER_LONG&t;64
macro_line|#endif
macro_line|#endif
DECL|typedef|vm_offset_t
r_typedef
id|u_long
id|vm_offset_t
suffix:semicolon
macro_line|#ifndef bcopy
DECL|macro|bcopy
mdefine_line|#define bcopy(s, d, n)&t;memcpy((d), (s), (n))
macro_line|#endif
macro_line|#ifndef bzero
DECL|macro|bzero
mdefine_line|#define bzero(d, n)&t;memset((d), 0, (n))
macro_line|#endif
macro_line|#ifndef bcmp
DECL|macro|bcmp
mdefine_line|#define bcmp(a, b, n)&t;memcmp((a), (b), (n))
macro_line|#endif
multiline_comment|/*&n; *  General driver includes.&n; */
macro_line|#include &quot;sym53c8xx.h&quot;
macro_line|#include &quot;sym_misc.h&quot;
macro_line|#include &quot;sym_conf.h&quot;
macro_line|#include &quot;sym_defs.h&quot;
multiline_comment|/*&n; * Configuration addendum for Linux.&n; */
macro_line|#if&t;LINUX_VERSION_CODE &gt;= LinuxVersionCode(2,3,47)
DECL|macro|SYM_LINUX_DYNAMIC_DMA_MAPPING
mdefine_line|#define&t;SYM_LINUX_DYNAMIC_DMA_MAPPING
macro_line|#endif
DECL|macro|SYM_CONF_TIMER_INTERVAL
mdefine_line|#define&t;SYM_CONF_TIMER_INTERVAL&t;&t;((HZ+1)/2)
DECL|macro|SYM_OPT_HANDLE_DIR_UNKNOWN
mdefine_line|#define SYM_OPT_HANDLE_DIR_UNKNOWN
DECL|macro|SYM_OPT_HANDLE_DEVICE_QUEUEING
mdefine_line|#define SYM_OPT_HANDLE_DEVICE_QUEUEING
DECL|macro|SYM_OPT_NVRAM_PRE_READ
mdefine_line|#define SYM_OPT_NVRAM_PRE_READ
DECL|macro|SYM_OPT_SNIFF_INQUIRY
mdefine_line|#define SYM_OPT_SNIFF_INQUIRY
DECL|macro|SYM_OPT_LIMIT_COMMAND_REORDERING
mdefine_line|#define SYM_OPT_LIMIT_COMMAND_REORDERING
DECL|macro|SYM_OPT_ANNOUNCE_TRANSFER_RATE
mdefine_line|#define&t;SYM_OPT_ANNOUNCE_TRANSFER_RATE
macro_line|#ifdef&t;SYM_LINUX_DYNAMIC_DMA_MAPPING
DECL|macro|SYM_OPT_BUS_DMA_ABSTRACTION
mdefine_line|#define&t;SYM_OPT_BUS_DMA_ABSTRACTION
macro_line|#endif
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
multiline_comment|/*&n; *  Insert a delay in micro-seconds and milli-seconds.&n; */
r_void
id|sym_udelay
c_func
(paren
r_int
id|us
)paren
suffix:semicolon
r_void
id|sym_mdelay
c_func
(paren
r_int
id|ms
)paren
suffix:semicolon
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
DECL|typedef|stcb_p
r_typedef
r_struct
id|sym_stcb
op_star
id|stcb_p
suffix:semicolon
DECL|typedef|slcb_p
r_typedef
r_struct
id|sym_slcb
op_star
id|slcb_p
suffix:semicolon
DECL|typedef|sccb_p
r_typedef
r_struct
id|sym_sccb
op_star
id|sccb_p
suffix:semicolon
DECL|typedef|shcb_p
r_typedef
r_struct
id|sym_shcb
op_star
id|shcb_p
suffix:semicolon
multiline_comment|/*&n; *  Define a reference to the O/S dependant IO request.&n; */
DECL|typedef|cam_ccb_p
r_typedef
id|Scsi_Cmnd
op_star
id|cam_ccb_p
suffix:semicolon
multiline_comment|/* Generic */
DECL|typedef|cam_scsiio_p
r_typedef
id|Scsi_Cmnd
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
macro_line|#if defined(__i386__)&t;/* i386 implements full FLAT memory/MMIO model */
DECL|macro|inw_raw
mdefine_line|#define&t;inw_raw&t;&t;inw
DECL|macro|inl_raw
mdefine_line|#define&t;inl_raw&t;&t;inl
DECL|macro|outw_raw
mdefine_line|#define&t;outw_raw&t;outw
DECL|macro|outl_raw
mdefine_line|#define&t;outl_raw&t;outl
DECL|macro|readb_raw
mdefine_line|#define readb_raw(a)&t;(*(volatile unsigned char *) (a))
DECL|macro|readw_raw
mdefine_line|#define readw_raw(a)&t;(*(volatile unsigned short *) (a))
DECL|macro|readl_raw
mdefine_line|#define readl_raw(a)&t;(*(volatile unsigned int *) (a))
DECL|macro|writeb_raw
mdefine_line|#define writeb_raw(b,a)&t;((*(volatile unsigned char *) (a)) = (b))
DECL|macro|writew_raw
mdefine_line|#define writew_raw(b,a)&t;((*(volatile unsigned short *) (a)) = (b))
DECL|macro|writel_raw
mdefine_line|#define writel_raw(b,a)&t;((*(volatile unsigned int *) (a)) = (b))
macro_line|#else&t;/* Other little-endian */
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
macro_line|#endif
macro_line|#endif
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
multiline_comment|/*&n; *  If the CPU and the chip use same endian-ness adressing,&n; *  no byte reordering is needed for script patching.&n; *  Macro cpu_to_scr() is to be used for script patching.&n; *  Macro scr_to_cpu() is to be used for getting a DWORD &n; *  from the script.&n; */
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
multiline_comment|/*&n; *  Access to the controller chip.&n; *&n; *  If SYM_CONF_IOMAPPED is defined, the driver will use &n; *  normal IOs instead of the MEMORY MAPPED IO method  &n; *  recommended by PCI specifications.&n; *  If all PCI bridges, host brigdes and architectures &n; *  would have been correctly designed for PCI, this &n; *  option would be useless.&n; *&n; *  If the CPU and the chip use same endian-ness adressing,&n; *  no byte reordering is needed for accessing chip io &n; *  registers. Functions suffixed by &squot;_raw&squot; are assumed &n; *  to access the chip over the PCI without doing byte &n; *  reordering. Functions suffixed by &squot;_l2b&squot; are &n; *  assumed to perform little-endian to big-endian byte &n; *  reordering, those suffixed by &squot;_b2l&squot; blah, blah,&n; *  blah, ...&n; */
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
mdefine_line|#define INB_OFF(o)        readb((char *)np-&gt;s.mmio_va + sym_offb(o))
DECL|macro|OUTB_OFF
mdefine_line|#define OUTB_OFF(o, val)  writeb((val), (char *)np-&gt;s.mmio_va + sym_offb(o))
macro_line|#if&t;defined(__BIG_ENDIAN) &amp;&amp; !defined(SYM_CONF_CHIP_BIG_ENDIAN)
DECL|macro|INW_OFF
mdefine_line|#define INW_OFF(o)        readw_l2b((char *)np-&gt;s.mmio_va + sym_offw(o))
DECL|macro|INL_OFF
mdefine_line|#define INL_OFF(o)        readl_l2b((char *)np-&gt;s.mmio_va + (o))
DECL|macro|OUTW_OFF
mdefine_line|#define OUTW_OFF(o, val)  writew_b2l((val), (char *)np-&gt;s.mmio_va + sym_offw(o))
DECL|macro|OUTL_OFF
mdefine_line|#define OUTL_OFF(o, val)  writel_b2l((val), (char *)np-&gt;s.mmio_va + (o))
macro_line|#elif&t;defined(__LITTLE_ENDIAN) &amp;&amp; defined(SYM_CONF_CHIP_BIG_ENDIAN)
DECL|macro|INW_OFF
mdefine_line|#define INW_OFF(o)        readw_b2l((char *)np-&gt;s.mmio_va + sym_offw(o))
DECL|macro|INL_OFF
mdefine_line|#define INL_OFF(o)        readl_b2l((char *)np-&gt;s.mmio_va + (o))
DECL|macro|OUTW_OFF
mdefine_line|#define OUTW_OFF(o, val)  writew_l2b((val), (char *)np-&gt;s.mmio_va + sym_offw(o))
DECL|macro|OUTL_OFF
mdefine_line|#define OUTL_OFF(o, val)  writel_l2b((val), (char *)np-&gt;s.mmio_va + (o))
macro_line|#else
DECL|macro|INW_OFF
mdefine_line|#define INW_OFF(o)        readw_raw((char *)np-&gt;s.mmio_va + sym_offw(o))
DECL|macro|INL_OFF
mdefine_line|#define INL_OFF(o)        readl_raw((char *)np-&gt;s.mmio_va + (o))
DECL|macro|OUTW_OFF
mdefine_line|#define OUTW_OFF(o, val)  writew_raw((val), (char *)np-&gt;s.mmio_va + sym_offw(o))
DECL|macro|OUTL_OFF
mdefine_line|#define OUTL_OFF(o, val)  writel_raw((val), (char *)np-&gt;s.mmio_va + (o))
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
multiline_comment|/*&n; *  Remap SCSI data direction values.&n; */
macro_line|#ifndef&t;SCSI_DATA_UNKNOWN
DECL|macro|SCSI_DATA_UNKNOWN
mdefine_line|#define&t;SCSI_DATA_UNKNOWN&t;0
DECL|macro|SCSI_DATA_WRITE
mdefine_line|#define&t;SCSI_DATA_WRITE&t;&t;1
DECL|macro|SCSI_DATA_READ
mdefine_line|#define&t;SCSI_DATA_READ&t;&t;2
DECL|macro|SCSI_DATA_NONE
mdefine_line|#define&t;SCSI_DATA_NONE&t;&t;3
macro_line|#endif
DECL|macro|CAM_DIR_NONE
mdefine_line|#define CAM_DIR_NONE&t;&t;SCSI_DATA_NONE
DECL|macro|CAM_DIR_IN
mdefine_line|#define CAM_DIR_IN&t;&t;SCSI_DATA_READ
DECL|macro|CAM_DIR_OUT
mdefine_line|#define CAM_DIR_OUT&t;&t;SCSI_DATA_WRITE
DECL|macro|CAM_DIR_UNKNOWN
mdefine_line|#define CAM_DIR_UNKNOWN&t;&t;SCSI_DATA_UNKNOWN
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
DECL|member|bus
id|u_char
id|bus
suffix:semicolon
multiline_comment|/* PCI BUS number&t;&t;*/
DECL|member|device_fn
id|u_char
id|device_fn
suffix:semicolon
multiline_comment|/* PCI BUS device and function&t;*/
DECL|member|smp_lock
id|spinlock_t
id|smp_lock
suffix:semicolon
multiline_comment|/* Lock for SMP threading       */
DECL|member|mmio_va
id|vm_offset_t
id|mmio_va
suffix:semicolon
multiline_comment|/* MMIO kernel virtual address&t;*/
DECL|member|ram_va
id|vm_offset_t
id|ram_va
suffix:semicolon
multiline_comment|/* RAM  kernel virtual address&t;*/
DECL|member|io_port
id|u32
id|io_port
suffix:semicolon
multiline_comment|/* IO port address&t;&t;*/
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
DECL|member|wait_cmdq
id|SYM_QUEHEAD
id|wait_cmdq
suffix:semicolon
multiline_comment|/* Awaiting SCSI commands&t;*/
DECL|member|busy_cmdq
id|SYM_QUEHEAD
id|busy_cmdq
suffix:semicolon
multiline_comment|/* Enqueued SCSI commands&t;*/
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
macro_line|#if LINUX_VERSION_CODE &lt; LinuxVersionCode(2, 4, 0)
DECL|member|release_stage
id|u_char
id|release_stage
suffix:semicolon
multiline_comment|/* Synchronisation on release&t;*/
macro_line|#endif
)brace
suffix:semicolon
multiline_comment|/*&n; *  Return the name of the controller.&n; */
DECL|macro|sym_name
mdefine_line|#define sym_name(np) (np)-&gt;s.inst_name
multiline_comment|/*&n; *  Data structure used as input for the NVRAM reading.&n; *  Must resolve the IO macros and sym_name(), when  &n; *  used as sub-field &squot;s&squot; of another structure.&n; */
r_typedef
r_struct
(brace
DECL|member|bus
r_int
id|bus
suffix:semicolon
DECL|member|device_fn
id|u_char
id|device_fn
suffix:semicolon
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
id|vm_offset_t
id|mmio_va
suffix:semicolon
DECL|member|inst_name
r_char
id|inst_name
(braket
l_int|16
)braket
suffix:semicolon
DECL|typedef|sym_slot
)brace
id|sym_slot
suffix:semicolon
DECL|typedef|sym_nvram
r_typedef
r_struct
id|sym_nvram
id|sym_nvram
suffix:semicolon
DECL|typedef|sym_chip
r_typedef
r_struct
id|sym_pci_chip
id|sym_chip
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|pdev
r_struct
id|pci_dev
op_star
id|pdev
suffix:semicolon
DECL|member|s
id|sym_slot
id|s
suffix:semicolon
DECL|member|chip
id|sym_chip
id|chip
suffix:semicolon
DECL|member|nvram
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
macro_line|#ifdef&t;SYM_CONF_PQS_PDS_SUPPORT
DECL|member|pqs_pds
id|u_char
id|pqs_pds
suffix:semicolon
macro_line|#endif
DECL|member|attach_done
r_int
id|attach_done
suffix:semicolon
DECL|typedef|sym_device
)brace
id|sym_device
suffix:semicolon
DECL|typedef|sdev_p
r_typedef
id|sym_device
op_star
id|sdev_p
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
macro_line|#ifdef&t;SYM_LINUX_DYNAMIC_DMA_MAPPING
DECL|typedef|m_pool_ident_t
r_typedef
r_struct
id|pci_dev
op_star
id|m_pool_ident_t
suffix:semicolon
macro_line|#endif
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
macro_line|#ifndef&t;SYM_LINUX_DYNAMIC_DMA_MAPPING
multiline_comment|/*&n; *  Simple case.&n; *  All the memory assummed DMAable and O/S providing virtual &n; *  to bus physical address translation.&n; */
DECL|macro|__sym_calloc_dma
mdefine_line|#define __sym_calloc_dma(pool_id, size, name)&t;sym_calloc(size, name)
DECL|macro|__sym_mfree_dma
mdefine_line|#define __sym_mfree_dma(pool_id, m, size, name)&t;sym_mfree(m, size, name)
DECL|macro|__vtobus
mdefine_line|#define __vtobus(b, p)&t;&t;&t;&t;virt_to_bus(p)
macro_line|#else&t;/* SYM_LINUX_DYNAMIC_DMA_MAPPING */
multiline_comment|/*&n; *  Complex case.&n; *  We have to provide the driver memory allocator with methods for &n; *  it to maintain virtual to bus physical address translations.&n; */
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
l_int|0
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
macro_line|#endif&t;/* SYM_LINUX_DYNAMIC_DMA_MAPPING */
multiline_comment|/*&n; *  Set the status field of a CAM CCB.&n; */
r_static
id|__inline
r_void
DECL|function|sym_set_cam_status
id|sym_set_cam_status
c_func
(paren
id|Scsi_Cmnd
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
id|Scsi_Cmnd
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
id|Scsi_Cmnd
op_star
id|cmd
op_assign
id|cp-&gt;cam_ccb
suffix:semicolon
macro_line|#if LINUX_VERSION_CODE &gt;= LinuxVersionCode(2,3,99)
id|cmd-&gt;resid
op_assign
id|resid
suffix:semicolon
macro_line|#endif
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
macro_line|#ifdef&t;SYM_OPT_SNIFF_INQUIRY
r_void
id|sym_sniff_inquiry
c_func
(paren
id|hcb_p
id|np
comma
id|Scsi_Cmnd
op_star
id|cmd
comma
r_int
id|resid
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif /* SYM_GLUE_H */
eof
