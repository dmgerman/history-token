multiline_comment|/******************************************************************************&n;**  High Performance device driver for the Symbios 53C896 controller.&n;**&n;**  Copyright (C) 1998-2001  Gerard Roudier &lt;groudier@free.fr&gt;&n;**&n;**  This driver also supports all the Symbios 53C8XX controller family, &n;**  except 53C810 revisions &lt; 16, 53C825 revisions &lt; 16 and all &n;**  revisions of 53C815 controllers.&n;**&n;**  This driver is based on the Linux port of the FreeBSD ncr driver.&n;** &n;**  Copyright (C) 1994  Wolfgang Stanglmeier&n;**  &n;**-----------------------------------------------------------------------------&n;**  &n;**  This program is free software; you can redistribute it and/or modify&n;**  it under the terms of the GNU General Public License as published by&n;**  the Free Software Foundation; either version 2 of the License, or&n;**  (at your option) any later version.&n;**&n;**  This program is distributed in the hope that it will be useful,&n;**  but WITHOUT ANY WARRANTY; without even the implied warranty of&n;**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;**  GNU General Public License for more details.&n;**&n;**  You should have received a copy of the GNU General Public License&n;**  along with this program; if not, write to the Free Software&n;**  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;**&n;**-----------------------------------------------------------------------------&n;**&n;**  The Linux port of the FreeBSD ncr driver has been achieved in &n;**  november 1995 by:&n;**&n;**          Gerard Roudier              &lt;groudier@free.fr&gt;&n;**&n;**  Being given that this driver originates from the FreeBSD version, and&n;**  in order to keep synergy on both, any suggested enhancements and corrections&n;**  received on Linux are automatically a potential candidate for the FreeBSD &n;**  version.&n;**&n;**  The original driver has been written for 386bsd and FreeBSD by&n;**          Wolfgang Stanglmeier        &lt;wolf@cologne.de&gt;&n;**          Stefan Esser                &lt;se@mi.Uni-Koeln.de&gt;&n;**&n;**-----------------------------------------------------------------------------&n;**&n;**  Major contributions:&n;**  --------------------&n;**&n;**  NVRAM detection and reading.&n;**    Copyright (C) 1997 Richard Waltham &lt;dormouse@farsrobt.demon.co.uk&gt;&n;**&n;*******************************************************************************&n;*/
macro_line|#ifndef SYM53C8XX_DEFS_H
DECL|macro|SYM53C8XX_DEFS_H
mdefine_line|#define SYM53C8XX_DEFS_H
multiline_comment|/*&n;**&t;Check supported Linux versions&n;*/
macro_line|#if !defined(LINUX_VERSION_CODE)
macro_line|#include &lt;linux/version.h&gt;
macro_line|#endif
macro_line|#include &lt;linux/config.h&gt;
DECL|macro|LinuxVersionCode
mdefine_line|#define LinuxVersionCode(v, p, s) (((v)&lt;&lt;16)+((p)&lt;&lt;8)+(s))
multiline_comment|/*&n; * NCR PQS/PDS special device support.&n; */
macro_line|#ifdef CONFIG_SCSI_NCR53C8XX_PQS_PDS
DECL|macro|SCSI_NCR_PQS_PDS_SUPPORT
mdefine_line|#define SCSI_NCR_PQS_PDS_SUPPORT
macro_line|#endif
multiline_comment|/*&n; *&t;No more an option, enabled by default.&n; */
macro_line|#ifndef CONFIG_SCSI_NCR53C8XX_NVRAM_DETECT
DECL|macro|CONFIG_SCSI_NCR53C8XX_NVRAM_DETECT
mdefine_line|#define CONFIG_SCSI_NCR53C8XX_NVRAM_DETECT
macro_line|#endif
multiline_comment|/*&n;**&t;These options are not tunable from &squot;make config&squot;&n;*/
DECL|macro|SCSI_NCR_PROC_INFO_SUPPORT
mdefine_line|#define&t;SCSI_NCR_PROC_INFO_SUPPORT
multiline_comment|/*&n;**&t;If you want a driver as small as possible, donnot define the &n;**&t;following options.&n;*/
DECL|macro|SCSI_NCR_BOOT_COMMAND_LINE_SUPPORT
mdefine_line|#define SCSI_NCR_BOOT_COMMAND_LINE_SUPPORT
DECL|macro|SCSI_NCR_DEBUG_INFO_SUPPORT
mdefine_line|#define SCSI_NCR_DEBUG_INFO_SUPPORT
DECL|macro|SCSI_NCR_PCI_FIX_UP_SUPPORT
mdefine_line|#define SCSI_NCR_PCI_FIX_UP_SUPPORT
macro_line|#ifdef&t;SCSI_NCR_PROC_INFO_SUPPORT
DECL|macro|SCSI_NCR_USER_COMMAND_SUPPORT
macro_line|#&t;define&t;SCSI_NCR_USER_COMMAND_SUPPORT
DECL|macro|SCSI_NCR_USER_INFO_SUPPORT
macro_line|#&t;define&t;SCSI_NCR_USER_INFO_SUPPORT
macro_line|#endif
multiline_comment|/*&n;**&t;To disable integrity checking, do not define the &n;**&t;following option.&n;*/
macro_line|#ifdef&t;CONFIG_SCSI_NCR53C8XX_INTEGRITY_CHECK
DECL|macro|SCSI_NCR_ENABLE_INTEGRITY_CHECK
macro_line|#&t;define SCSI_NCR_ENABLE_INTEGRITY_CHECK
macro_line|#endif
multiline_comment|/*==========================================================&n;**&n;** nvram settings - #define SCSI_NCR_NVRAM_SUPPORT to enable&n;**&n;**==========================================================&n;*/
macro_line|#ifdef CONFIG_SCSI_NCR53C8XX_NVRAM_DETECT
DECL|macro|SCSI_NCR_NVRAM_SUPPORT
mdefine_line|#define SCSI_NCR_NVRAM_SUPPORT
multiline_comment|/* #define SCSI_NCR_DEBUG_NVRAM */
macro_line|#endif
multiline_comment|/* ---------------------------------------------------------------------&n;** Take into account kernel configured parameters.&n;** Most of these options can be overridden at startup by a command line.&n;** ---------------------------------------------------------------------&n;*/
multiline_comment|/*&n; * For Ultra2 and Ultra3 SCSI support option, use special features. &n; *&n; * Value (default) means:&n; *&t;bit 0 : all features enabled, except:&n; *&t;&t;bit 1 : PCI Write And Invalidate.&n; *&t;&t;bit 2 : Data Phase Mismatch handling from SCRIPTS.&n; *&n; * Use boot options ncr53c8xx=specf:1 if you want all chip features to be &n; * enabled by the driver.&n; */
DECL|macro|SCSI_NCR_SETUP_SPECIAL_FEATURES
mdefine_line|#define&t;SCSI_NCR_SETUP_SPECIAL_FEATURES&t;&t;(3)
DECL|macro|SCSI_NCR_MAX_SYNC
mdefine_line|#define SCSI_NCR_MAX_SYNC&t;&t;&t;(80)
multiline_comment|/*&n; * Allow tags from 2 to 256, default 8&n; */
macro_line|#ifdef&t;CONFIG_SCSI_NCR53C8XX_MAX_TAGS
macro_line|#if&t;CONFIG_SCSI_NCR53C8XX_MAX_TAGS &lt; 2
DECL|macro|SCSI_NCR_MAX_TAGS
mdefine_line|#define SCSI_NCR_MAX_TAGS&t;(2)
macro_line|#elif&t;CONFIG_SCSI_NCR53C8XX_MAX_TAGS &gt; 256
DECL|macro|SCSI_NCR_MAX_TAGS
mdefine_line|#define SCSI_NCR_MAX_TAGS&t;(256)
macro_line|#else
DECL|macro|SCSI_NCR_MAX_TAGS
mdefine_line|#define&t;SCSI_NCR_MAX_TAGS&t;CONFIG_SCSI_NCR53C8XX_MAX_TAGS
macro_line|#endif
macro_line|#else
DECL|macro|SCSI_NCR_MAX_TAGS
mdefine_line|#define SCSI_NCR_MAX_TAGS&t;(8)
macro_line|#endif
multiline_comment|/*&n; * Allow tagged command queuing support if configured with default number &n; * of tags set to max (see above).&n; */
macro_line|#ifdef&t;CONFIG_SCSI_NCR53C8XX_DEFAULT_TAGS
DECL|macro|SCSI_NCR_SETUP_DEFAULT_TAGS
mdefine_line|#define&t;SCSI_NCR_SETUP_DEFAULT_TAGS&t;CONFIG_SCSI_NCR53C8XX_DEFAULT_TAGS
macro_line|#elif&t;defined CONFIG_SCSI_NCR53C8XX_TAGGED_QUEUE
DECL|macro|SCSI_NCR_SETUP_DEFAULT_TAGS
mdefine_line|#define&t;SCSI_NCR_SETUP_DEFAULT_TAGS&t;SCSI_NCR_MAX_TAGS
macro_line|#else
DECL|macro|SCSI_NCR_SETUP_DEFAULT_TAGS
mdefine_line|#define&t;SCSI_NCR_SETUP_DEFAULT_TAGS&t;(0)
macro_line|#endif
multiline_comment|/*&n; * Use normal IO if configured. Forced for alpha.&n; */
macro_line|#if defined(CONFIG_SCSI_NCR53C8XX_IOMAPPED)
DECL|macro|SCSI_NCR_IOMAPPED
mdefine_line|#define&t;SCSI_NCR_IOMAPPED
macro_line|#elif defined(__alpha__)
DECL|macro|SCSI_NCR_IOMAPPED
mdefine_line|#define&t;SCSI_NCR_IOMAPPED
macro_line|#elif defined(__powerpc__)
macro_line|#if LINUX_VERSION_CODE &lt;= LinuxVersionCode(2,4,3)
DECL|macro|SCSI_NCR_IOMAPPED
mdefine_line|#define&t;SCSI_NCR_IOMAPPED
DECL|macro|SCSI_NCR_PCI_MEM_NOT_SUPPORTED
mdefine_line|#define SCSI_NCR_PCI_MEM_NOT_SUPPORTED
macro_line|#endif
macro_line|#elif defined(__sparc__)
DECL|macro|SCSI_NCR_IOMAPPED
macro_line|#undef SCSI_NCR_IOMAPPED
macro_line|#endif
multiline_comment|/*&n; * Immediate arbitration&n; */
macro_line|#if defined(CONFIG_SCSI_NCR53C8XX_IARB)
DECL|macro|SCSI_NCR_IARB_SUPPORT
mdefine_line|#define SCSI_NCR_IARB_SUPPORT
macro_line|#endif
multiline_comment|/*&n; * Sync transfer frequency at startup.&n; * Allow from 5Mhz to 80Mhz default 20 Mhz.&n; */
macro_line|#ifndef&t;CONFIG_SCSI_NCR53C8XX_SYNC
DECL|macro|CONFIG_SCSI_NCR53C8XX_SYNC
mdefine_line|#define&t;CONFIG_SCSI_NCR53C8XX_SYNC&t;(20)
macro_line|#elif&t;CONFIG_SCSI_NCR53C8XX_SYNC &gt; SCSI_NCR_MAX_SYNC
DECL|macro|CONFIG_SCSI_NCR53C8XX_SYNC
macro_line|#undef&t;CONFIG_SCSI_NCR53C8XX_SYNC
DECL|macro|CONFIG_SCSI_NCR53C8XX_SYNC
mdefine_line|#define&t;CONFIG_SCSI_NCR53C8XX_SYNC&t;SCSI_NCR_MAX_SYNC
macro_line|#endif
macro_line|#if&t;CONFIG_SCSI_NCR53C8XX_SYNC == 0
DECL|macro|SCSI_NCR_SETUP_DEFAULT_SYNC
mdefine_line|#define&t;SCSI_NCR_SETUP_DEFAULT_SYNC&t;(255)
macro_line|#elif&t;CONFIG_SCSI_NCR53C8XX_SYNC &lt;= 5
DECL|macro|SCSI_NCR_SETUP_DEFAULT_SYNC
mdefine_line|#define&t;SCSI_NCR_SETUP_DEFAULT_SYNC&t;(50)
macro_line|#elif&t;CONFIG_SCSI_NCR53C8XX_SYNC &lt;= 20
DECL|macro|SCSI_NCR_SETUP_DEFAULT_SYNC
mdefine_line|#define&t;SCSI_NCR_SETUP_DEFAULT_SYNC&t;(250/(CONFIG_SCSI_NCR53C8XX_SYNC))
macro_line|#elif&t;CONFIG_SCSI_NCR53C8XX_SYNC &lt;= 33
DECL|macro|SCSI_NCR_SETUP_DEFAULT_SYNC
mdefine_line|#define&t;SCSI_NCR_SETUP_DEFAULT_SYNC&t;(11)
macro_line|#elif&t;CONFIG_SCSI_NCR53C8XX_SYNC &lt;= 40
DECL|macro|SCSI_NCR_SETUP_DEFAULT_SYNC
mdefine_line|#define&t;SCSI_NCR_SETUP_DEFAULT_SYNC&t;(10)
macro_line|#else
DECL|macro|SCSI_NCR_SETUP_DEFAULT_SYNC
mdefine_line|#define&t;SCSI_NCR_SETUP_DEFAULT_SYNC &t;(9)
macro_line|#endif
multiline_comment|/*&n; * Disallow disconnections at boot-up&n; */
macro_line|#ifdef CONFIG_SCSI_NCR53C8XX_NO_DISCONNECT
DECL|macro|SCSI_NCR_SETUP_DISCONNECTION
mdefine_line|#define SCSI_NCR_SETUP_DISCONNECTION&t;(0)
macro_line|#else
DECL|macro|SCSI_NCR_SETUP_DISCONNECTION
mdefine_line|#define SCSI_NCR_SETUP_DISCONNECTION&t;(1)
macro_line|#endif
multiline_comment|/*&n; * Force synchronous negotiation for all targets&n; */
macro_line|#ifdef CONFIG_SCSI_NCR53C8XX_FORCE_SYNC_NEGO
DECL|macro|SCSI_NCR_SETUP_FORCE_SYNC_NEGO
mdefine_line|#define SCSI_NCR_SETUP_FORCE_SYNC_NEGO&t;(1)
macro_line|#else
DECL|macro|SCSI_NCR_SETUP_FORCE_SYNC_NEGO
mdefine_line|#define SCSI_NCR_SETUP_FORCE_SYNC_NEGO&t;(0)
macro_line|#endif
multiline_comment|/*&n; * Disable master parity checking (flawed hardwares need that)&n; */
macro_line|#ifdef CONFIG_SCSI_NCR53C8XX_DISABLE_MPARITY_CHECK
DECL|macro|SCSI_NCR_SETUP_MASTER_PARITY
mdefine_line|#define SCSI_NCR_SETUP_MASTER_PARITY&t;(0)
macro_line|#else
DECL|macro|SCSI_NCR_SETUP_MASTER_PARITY
mdefine_line|#define SCSI_NCR_SETUP_MASTER_PARITY&t;(1)
macro_line|#endif
multiline_comment|/*&n; * Disable scsi parity checking (flawed devices may need that)&n; */
macro_line|#ifdef CONFIG_SCSI_NCR53C8XX_DISABLE_PARITY_CHECK
DECL|macro|SCSI_NCR_SETUP_SCSI_PARITY
mdefine_line|#define SCSI_NCR_SETUP_SCSI_PARITY&t;(0)
macro_line|#else
DECL|macro|SCSI_NCR_SETUP_SCSI_PARITY
mdefine_line|#define SCSI_NCR_SETUP_SCSI_PARITY&t;(1)
macro_line|#endif
multiline_comment|/*&n; * Vendor specific stuff&n; */
macro_line|#ifdef CONFIG_SCSI_NCR53C8XX_SYMBIOS_COMPAT
DECL|macro|SCSI_NCR_SETUP_LED_PIN
mdefine_line|#define SCSI_NCR_SETUP_LED_PIN&t;&t;(1)
DECL|macro|SCSI_NCR_SETUP_DIFF_SUPPORT
mdefine_line|#define SCSI_NCR_SETUP_DIFF_SUPPORT&t;(4)
macro_line|#else
DECL|macro|SCSI_NCR_SETUP_LED_PIN
mdefine_line|#define SCSI_NCR_SETUP_LED_PIN&t;&t;(0)
DECL|macro|SCSI_NCR_SETUP_DIFF_SUPPORT
mdefine_line|#define SCSI_NCR_SETUP_DIFF_SUPPORT&t;(0)
macro_line|#endif
multiline_comment|/*&n; * Settle time after reset at boot-up&n; */
DECL|macro|SCSI_NCR_SETUP_SETTLE_TIME
mdefine_line|#define SCSI_NCR_SETUP_SETTLE_TIME&t;(2)
multiline_comment|/*&n;**&t;Bridge quirks work-around option defaulted to 1.&n;*/
macro_line|#ifndef&t;SCSI_NCR_PCIQ_WORK_AROUND_OPT
DECL|macro|SCSI_NCR_PCIQ_WORK_AROUND_OPT
mdefine_line|#define&t;SCSI_NCR_PCIQ_WORK_AROUND_OPT&t;1
macro_line|#endif
multiline_comment|/*&n;**&t;Work-around common bridge misbehaviour.&n;**&n;**&t;- Do not flush posted writes in the opposite &n;**&t;  direction on read.&n;**&t;- May reorder DMA writes to memory.&n;**&n;**&t;This option should not affect performances &n;**&t;significantly, so it is the default.&n;*/
macro_line|#if&t;SCSI_NCR_PCIQ_WORK_AROUND_OPT == 1
DECL|macro|SCSI_NCR_PCIQ_MAY_NOT_FLUSH_PW_UPSTREAM
mdefine_line|#define&t;SCSI_NCR_PCIQ_MAY_NOT_FLUSH_PW_UPSTREAM
DECL|macro|SCSI_NCR_PCIQ_MAY_REORDER_WRITES
mdefine_line|#define&t;SCSI_NCR_PCIQ_MAY_REORDER_WRITES
DECL|macro|SCSI_NCR_PCIQ_MAY_MISS_COMPLETIONS
mdefine_line|#define&t;SCSI_NCR_PCIQ_MAY_MISS_COMPLETIONS
multiline_comment|/*&n;**&t;Same as option 1, but also deal with &n;**&t;misconfigured interrupts.&n;**&n;**&t;- Edge triggerred instead of level sensitive.&n;**&t;- No interrupt line connected.&n;**&t;- IRQ number misconfigured.&n;**&t;&n;**&t;If no interrupt is delivered, the driver will &n;**&t;catch the interrupt conditions 10 times per &n;**&t;second. No need to say that this option is &n;**&t;not recommended.&n;*/
macro_line|#elif&t;SCSI_NCR_PCIQ_WORK_AROUND_OPT == 2
DECL|macro|SCSI_NCR_PCIQ_MAY_NOT_FLUSH_PW_UPSTREAM
mdefine_line|#define&t;SCSI_NCR_PCIQ_MAY_NOT_FLUSH_PW_UPSTREAM
DECL|macro|SCSI_NCR_PCIQ_MAY_REORDER_WRITES
mdefine_line|#define&t;SCSI_NCR_PCIQ_MAY_REORDER_WRITES
DECL|macro|SCSI_NCR_PCIQ_MAY_MISS_COMPLETIONS
mdefine_line|#define&t;SCSI_NCR_PCIQ_MAY_MISS_COMPLETIONS
DECL|macro|SCSI_NCR_PCIQ_BROKEN_INTR
mdefine_line|#define&t;SCSI_NCR_PCIQ_BROKEN_INTR
multiline_comment|/*&n;**&t;Some bridge designers decided to flush &n;**&t;everything prior to deliver the interrupt.&n;**&t;This option tries to deal with such a &n;**&t;behaviour.&n;*/
macro_line|#elif&t;SCSI_NCR_PCIQ_WORK_AROUND_OPT == 3
DECL|macro|SCSI_NCR_PCIQ_SYNC_ON_INTR
mdefine_line|#define&t;SCSI_NCR_PCIQ_SYNC_ON_INTR
macro_line|#endif
multiline_comment|/*&n;**&t;Other parameters not configurable with &quot;make config&quot;&n;**&t;Avoid to change these constants, unless you know what you are doing.&n;*/
DECL|macro|SCSI_NCR_ALWAYS_SIMPLE_TAG
mdefine_line|#define SCSI_NCR_ALWAYS_SIMPLE_TAG
DECL|macro|SCSI_NCR_MAX_SCATTER
mdefine_line|#define SCSI_NCR_MAX_SCATTER&t;(127)
DECL|macro|SCSI_NCR_MAX_TARGET
mdefine_line|#define SCSI_NCR_MAX_TARGET&t;(16)
multiline_comment|/*&n;**   Compute some desirable value for CAN_QUEUE &n;**   and CMD_PER_LUN.&n;**   The driver will use lower values if these &n;**   ones appear to be too large.&n;*/
DECL|macro|SCSI_NCR_CAN_QUEUE
mdefine_line|#define SCSI_NCR_CAN_QUEUE&t;(8*SCSI_NCR_MAX_TAGS + 2*SCSI_NCR_MAX_TARGET)
DECL|macro|SCSI_NCR_CMD_PER_LUN
mdefine_line|#define SCSI_NCR_CMD_PER_LUN&t;(SCSI_NCR_MAX_TAGS)
DECL|macro|SCSI_NCR_SG_TABLESIZE
mdefine_line|#define SCSI_NCR_SG_TABLESIZE&t;(SCSI_NCR_MAX_SCATTER)
DECL|macro|SCSI_NCR_TIMER_INTERVAL
mdefine_line|#define SCSI_NCR_TIMER_INTERVAL&t;(HZ)
macro_line|#if 1 /* defined CONFIG_SCSI_MULTI_LUN */
DECL|macro|SCSI_NCR_MAX_LUN
mdefine_line|#define SCSI_NCR_MAX_LUN&t;(16)
macro_line|#else
DECL|macro|SCSI_NCR_MAX_LUN
mdefine_line|#define SCSI_NCR_MAX_LUN&t;(1)
macro_line|#endif
macro_line|#ifndef HOSTS_C
multiline_comment|/*&n;**&t;These simple macros limit expression involving &n;**&t;kernel time values (jiffies) to some that have &n;**&t;chance not to be too much incorrect. :-)&n;*/
DECL|macro|ktime_get
mdefine_line|#define ktime_get(o)&t;&t;(jiffies + (u_long) o)
DECL|macro|ktime_exp
mdefine_line|#define ktime_exp(b)&t;&t;((long)(jiffies) - (long)(b) &gt;= 0)
DECL|macro|ktime_dif
mdefine_line|#define ktime_dif(a, b)&t;&t;((long)(a) - (long)(b))
multiline_comment|/* These ones are not used in this driver */
DECL|macro|ktime_add
mdefine_line|#define ktime_add(a, o)&t;&t;((a) + (u_long)(o))
DECL|macro|ktime_sub
mdefine_line|#define ktime_sub(a, o)&t;&t;((a) - (u_long)(o))
multiline_comment|/*&n; *  IO functions definition for big/little endian CPU support.&n; *  For now, the NCR is only supported in little endian addressing mode, &n; */
macro_line|#ifdef&t;__BIG_ENDIAN
macro_line|#if&t;LINUX_VERSION_CODE &lt; LinuxVersionCode(2,1,0)
macro_line|#error&t;&quot;BIG ENDIAN byte ordering needs kernel version &gt;= 2.1.0&quot;
macro_line|#endif
DECL|macro|inw_l2b
mdefine_line|#define&t;inw_l2b&t;&t;inw
DECL|macro|inl_l2b
mdefine_line|#define&t;inl_l2b&t;&t;inl
DECL|macro|outw_b2l
mdefine_line|#define&t;outw_b2l&t;outw
DECL|macro|outl_b2l
mdefine_line|#define&t;outl_b2l&t;outl
DECL|macro|readb_raw
mdefine_line|#define&t;readb_raw&t;readb
DECL|macro|writeb_raw
mdefine_line|#define&t;writeb_raw&t;writeb
macro_line|#if defined(__hppa__)
DECL|macro|readw_l2b
mdefine_line|#define&t;readw_l2b(a)&t;le16_to_cpu(readw(a))
DECL|macro|readl_l2b
mdefine_line|#define&t;readl_l2b(a)&t;le32_to_cpu(readl(a))
DECL|macro|writew_b2l
mdefine_line|#define&t;writew_b2l(v,a)&t;writew(cpu_to_le16(v),a)
DECL|macro|writel_b2l
mdefine_line|#define&t;writel_b2l(v,a)&t;writel(cpu_to_le32(v),a)
macro_line|#else&t;/* Other bid-endian */
DECL|macro|readw_l2b
mdefine_line|#define&t;readw_l2b&t;readw
DECL|macro|readl_l2b
mdefine_line|#define&t;readl_l2b&t;readl
DECL|macro|writew_b2l
mdefine_line|#define&t;writew_b2l&t;writew
DECL|macro|writel_b2l
mdefine_line|#define&t;writel_b2l&t;writel
macro_line|#endif
macro_line|#else&t;/* little endian */
DECL|macro|inw_raw
mdefine_line|#define&t;inw_raw&t;&t;inw
DECL|macro|inl_raw
mdefine_line|#define&t;inl_raw&t;&t;inl
DECL|macro|outw_raw
mdefine_line|#define&t;outw_raw&t;outw
DECL|macro|outl_raw
mdefine_line|#define&t;outl_raw&t;outl
macro_line|#if defined(__i386__)&t;/* i386 implements full FLAT memory/MMIO model */
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
DECL|macro|readb_raw
mdefine_line|#define&t;readb_raw&t;readb
DECL|macro|readw_raw
mdefine_line|#define&t;readw_raw&t;readw
DECL|macro|readl_raw
mdefine_line|#define&t;readl_raw&t;readl
DECL|macro|writeb_raw
mdefine_line|#define&t;writeb_raw&t;writeb
DECL|macro|writew_raw
mdefine_line|#define&t;writew_raw&t;writew
DECL|macro|writel_raw
mdefine_line|#define&t;writel_raw&t;writel
macro_line|#endif
macro_line|#endif
macro_line|#ifdef&t;SCSI_NCR_BIG_ENDIAN
macro_line|#error&t;&quot;The NCR in BIG ENDIAN addressing mode is not (yet) supported&quot;
macro_line|#endif
multiline_comment|/*&n; *  IA32 architecture does not reorder STORES and prevents&n; *  LOADS from passing STORES. It is called `program order&squot; &n; *  by Intel and allows device drivers to deal with memory &n; *  ordering by only ensuring that the code is not reordered  &n; *  by the compiler when ordering is required.&n; *  Other architectures implement a weaker ordering that &n; *  requires memory barriers (and also IO barriers when they &n; *  make sense) to be used.&n; *  We want to be paranoid for ppc and ia64. :)&n; */
macro_line|#if&t;defined(__i386__) || defined(__x86_64__)
DECL|macro|MEMORY_BARRIER
mdefine_line|#define MEMORY_BARRIER()&t;do { ; } while(0)
macro_line|#elif&t;defined&t;__powerpc__
DECL|macro|MEMORY_BARRIER
mdefine_line|#define MEMORY_BARRIER()&t;__asm__ volatile(&quot;eieio; sync&quot; : : : &quot;memory&quot;)
macro_line|#elif&t;defined&t;__ia64__
DECL|macro|MEMORY_BARRIER
mdefine_line|#define MEMORY_BARRIER()&t;__asm__ volatile(&quot;mf.a; mf&quot; : : : &quot;memory&quot;)
macro_line|#else
DECL|macro|MEMORY_BARRIER
mdefine_line|#define MEMORY_BARRIER()&t;mb()
macro_line|#endif
multiline_comment|/*&n; *  If the NCR uses big endian addressing mode over the &n; *  PCI, actual io register addresses for byte and word &n; *  accesses must be changed according to lane routing.&n; *  Btw, ncr_offb() and ncr_offw() macros only apply to &n; *  constants and so donnot generate bloated code.&n; */
macro_line|#if&t;defined(SCSI_NCR_BIG_ENDIAN)
DECL|macro|ncr_offb
mdefine_line|#define ncr_offb(o)&t;(((o)&amp;~3)+((~((o)&amp;3))&amp;3))
DECL|macro|ncr_offw
mdefine_line|#define ncr_offw(o)&t;(((o)&amp;~3)+((~((o)&amp;3))&amp;2))
macro_line|#else
DECL|macro|ncr_offb
mdefine_line|#define ncr_offb(o)&t;(o)
DECL|macro|ncr_offw
mdefine_line|#define ncr_offw(o)&t;(o)
macro_line|#endif
multiline_comment|/*&n; *  If the CPU and the NCR use same endian-ness adressing,&n; *  no byte reordering is needed for script patching.&n; *  Macro cpu_to_scr() is to be used for script patching.&n; *  Macro scr_to_cpu() is to be used for getting a DWORD &n; *  from the script.&n; */
macro_line|#if&t;defined(__BIG_ENDIAN) &amp;&amp; !defined(SCSI_NCR_BIG_ENDIAN)
DECL|macro|cpu_to_scr
mdefine_line|#define cpu_to_scr(dw)&t;cpu_to_le32(dw)
DECL|macro|scr_to_cpu
mdefine_line|#define scr_to_cpu(dw)&t;le32_to_cpu(dw)
macro_line|#elif&t;defined(__LITTLE_ENDIAN) &amp;&amp; defined(SCSI_NCR_BIG_ENDIAN)
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
multiline_comment|/*&n; *  Access to the controller chip.&n; *&n; *  If SCSI_NCR_IOMAPPED is defined, the driver will use &n; *  normal IOs instead of the MEMORY MAPPED IO method  &n; *  recommended by PCI specifications.&n; *  If all PCI bridges, host brigdes and architectures &n; *  would have been correctly designed for PCI, this &n; *  option would be useless.&n; *&n; *  If the CPU and the NCR use same endian-ness adressing,&n; *  no byte reordering is needed for accessing chip io &n; *  registers. Functions suffixed by &squot;_raw&squot; are assumed &n; *  to access the chip over the PCI without doing byte &n; *  reordering. Functions suffixed by &squot;_l2b&squot; are &n; *  assumed to perform little-endian to big-endian byte &n; *  reordering, those suffixed by &squot;_b2l&squot; blah, blah,&n; *  blah, ...&n; */
macro_line|#if defined(SCSI_NCR_IOMAPPED)
multiline_comment|/*&n; *  IO mapped only input / ouput&n; */
DECL|macro|INB_OFF
mdefine_line|#define&t;INB_OFF(o)&t;&t;inb (np-&gt;base_io + ncr_offb(o))
DECL|macro|OUTB_OFF
mdefine_line|#define&t;OUTB_OFF(o, val)&t;outb ((val), np-&gt;base_io + ncr_offb(o))
macro_line|#if&t;defined(__BIG_ENDIAN) &amp;&amp; !defined(SCSI_NCR_BIG_ENDIAN)
DECL|macro|INW_OFF
mdefine_line|#define&t;INW_OFF(o)&t;&t;inw_l2b (np-&gt;base_io + ncr_offw(o))
DECL|macro|INL_OFF
mdefine_line|#define&t;INL_OFF(o)&t;&t;inl_l2b (np-&gt;base_io + (o))
DECL|macro|OUTW_OFF
mdefine_line|#define&t;OUTW_OFF(o, val)&t;outw_b2l ((val), np-&gt;base_io + ncr_offw(o))
DECL|macro|OUTL_OFF
mdefine_line|#define&t;OUTL_OFF(o, val)&t;outl_b2l ((val), np-&gt;base_io + (o))
macro_line|#elif&t;defined(__LITTLE_ENDIAN) &amp;&amp; defined(SCSI_NCR_BIG_ENDIAN)
DECL|macro|INW_OFF
mdefine_line|#define&t;INW_OFF(o)&t;&t;inw_b2l (np-&gt;base_io + ncr_offw(o))
DECL|macro|INL_OFF
mdefine_line|#define&t;INL_OFF(o)&t;&t;inl_b2l (np-&gt;base_io + (o))
DECL|macro|OUTW_OFF
mdefine_line|#define&t;OUTW_OFF(o, val)&t;outw_l2b ((val), np-&gt;base_io + ncr_offw(o))
DECL|macro|OUTL_OFF
mdefine_line|#define&t;OUTL_OFF(o, val)&t;outl_l2b ((val), np-&gt;base_io + (o))
macro_line|#else
DECL|macro|INW_OFF
mdefine_line|#define&t;INW_OFF(o)&t;&t;inw_raw (np-&gt;base_io + ncr_offw(o))
DECL|macro|INL_OFF
mdefine_line|#define&t;INL_OFF(o)&t;&t;inl_raw (np-&gt;base_io + (o))
DECL|macro|OUTW_OFF
mdefine_line|#define&t;OUTW_OFF(o, val)&t;outw_raw ((val), np-&gt;base_io + ncr_offw(o))
DECL|macro|OUTL_OFF
mdefine_line|#define&t;OUTL_OFF(o, val)&t;outl_raw ((val), np-&gt;base_io + (o))
macro_line|#endif&t;/* ENDIANs */
macro_line|#else&t;/* defined SCSI_NCR_IOMAPPED */
multiline_comment|/*&n; *  MEMORY mapped IO input / output&n; */
DECL|macro|INB_OFF
mdefine_line|#define INB_OFF(o)&t;&t;readb_raw((char *)np-&gt;reg + ncr_offb(o))
DECL|macro|OUTB_OFF
mdefine_line|#define OUTB_OFF(o, val)&t;writeb_raw((val), (char *)np-&gt;reg + ncr_offb(o))
macro_line|#if&t;defined(__BIG_ENDIAN) &amp;&amp; !defined(SCSI_NCR_BIG_ENDIAN)
DECL|macro|INW_OFF
mdefine_line|#define INW_OFF(o)&t;&t;readw_l2b((char *)np-&gt;reg + ncr_offw(o))
DECL|macro|INL_OFF
mdefine_line|#define INL_OFF(o)&t;&t;readl_l2b((char *)np-&gt;reg + (o))
DECL|macro|OUTW_OFF
mdefine_line|#define OUTW_OFF(o, val)&t;writew_b2l((val), (char *)np-&gt;reg + ncr_offw(o))
DECL|macro|OUTL_OFF
mdefine_line|#define OUTL_OFF(o, val)&t;writel_b2l((val), (char *)np-&gt;reg + (o))
macro_line|#elif&t;defined(__LITTLE_ENDIAN) &amp;&amp; defined(SCSI_NCR_BIG_ENDIAN)
DECL|macro|INW_OFF
mdefine_line|#define INW_OFF(o)&t;&t;readw_b2l((char *)np-&gt;reg + ncr_offw(o))
DECL|macro|INL_OFF
mdefine_line|#define INL_OFF(o)&t;&t;readl_b2l((char *)np-&gt;reg + (o))
DECL|macro|OUTW_OFF
mdefine_line|#define OUTW_OFF(o, val)&t;writew_l2b((val), (char *)np-&gt;reg + ncr_offw(o))
DECL|macro|OUTL_OFF
mdefine_line|#define OUTL_OFF(o, val)&t;writel_l2b((val), (char *)np-&gt;reg + (o))
macro_line|#else
DECL|macro|INW_OFF
mdefine_line|#define INW_OFF(o)&t;&t;readw_raw((char *)np-&gt;reg + ncr_offw(o))
DECL|macro|INL_OFF
mdefine_line|#define INL_OFF(o)&t;&t;readl_raw((char *)np-&gt;reg + (o))
DECL|macro|OUTW_OFF
mdefine_line|#define OUTW_OFF(o, val)&t;writew_raw((val), (char *)np-&gt;reg + ncr_offw(o))
DECL|macro|OUTL_OFF
mdefine_line|#define OUTL_OFF(o, val)&t;writel_raw((val), (char *)np-&gt;reg + (o))
macro_line|#endif
macro_line|#endif&t;/* defined SCSI_NCR_IOMAPPED */
DECL|macro|INB
mdefine_line|#define INB(r)&t;&t;INB_OFF (offsetof(struct ncr_reg,r))
DECL|macro|INW
mdefine_line|#define INW(r)&t;&t;INW_OFF (offsetof(struct ncr_reg,r))
DECL|macro|INL
mdefine_line|#define INL(r)&t;&t;INL_OFF (offsetof(struct ncr_reg,r))
DECL|macro|OUTB
mdefine_line|#define OUTB(r, val)&t;OUTB_OFF (offsetof(struct ncr_reg,r), (val))
DECL|macro|OUTW
mdefine_line|#define OUTW(r, val)&t;OUTW_OFF (offsetof(struct ncr_reg,r), (val))
DECL|macro|OUTL
mdefine_line|#define OUTL(r, val)&t;OUTL_OFF (offsetof(struct ncr_reg,r), (val))
multiline_comment|/*&n; *  Set bit field ON, OFF &n; */
DECL|macro|OUTONB
mdefine_line|#define OUTONB(r, m)&t;OUTB(r, INB(r) | (m))
DECL|macro|OUTOFFB
mdefine_line|#define OUTOFFB(r, m)&t;OUTB(r, INB(r) &amp; ~(m))
DECL|macro|OUTONW
mdefine_line|#define OUTONW(r, m)&t;OUTW(r, INW(r) | (m))
DECL|macro|OUTOFFW
mdefine_line|#define OUTOFFW(r, m)&t;OUTW(r, INW(r) &amp; ~(m))
DECL|macro|OUTONL
mdefine_line|#define OUTONL(r, m)&t;OUTL(r, INL(r) | (m))
DECL|macro|OUTOFFL
mdefine_line|#define OUTOFFL(r, m)&t;OUTL(r, INL(r) &amp; ~(m))
multiline_comment|/*&n; *  We normally want the chip to have a consistent view&n; *  of driver internal data structures when we restart it.&n; *  Thus these macros.&n; */
DECL|macro|OUTL_DSP
mdefine_line|#define OUTL_DSP(v)&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&bslash;&n;&t;&t;MEMORY_BARRIER();&t;&t;&bslash;&n;&t;&t;OUTL (nc_dsp, (v));&t;&t;&bslash;&n;&t;} while (0)
DECL|macro|OUTONB_STD
mdefine_line|#define OUTONB_STD()&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&bslash;&n;&t;&t;MEMORY_BARRIER();&t;&t;&bslash;&n;&t;&t;OUTONB (nc_dcntl, (STD|NOCOM));&t;&bslash;&n;&t;} while (0)
multiline_comment|/*&n;**&t;NCR53C8XX Device Ids&n;*/
macro_line|#ifndef PCI_DEVICE_ID_NCR_53C810
DECL|macro|PCI_DEVICE_ID_NCR_53C810
mdefine_line|#define PCI_DEVICE_ID_NCR_53C810 1
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_NCR_53C810AP
DECL|macro|PCI_DEVICE_ID_NCR_53C810AP
mdefine_line|#define PCI_DEVICE_ID_NCR_53C810AP 5
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_NCR_53C815
DECL|macro|PCI_DEVICE_ID_NCR_53C815
mdefine_line|#define PCI_DEVICE_ID_NCR_53C815 4
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_NCR_53C820
DECL|macro|PCI_DEVICE_ID_NCR_53C820
mdefine_line|#define PCI_DEVICE_ID_NCR_53C820 2
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_NCR_53C825
DECL|macro|PCI_DEVICE_ID_NCR_53C825
mdefine_line|#define PCI_DEVICE_ID_NCR_53C825 3
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_NCR_53C860
DECL|macro|PCI_DEVICE_ID_NCR_53C860
mdefine_line|#define PCI_DEVICE_ID_NCR_53C860 6
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_NCR_53C875
DECL|macro|PCI_DEVICE_ID_NCR_53C875
mdefine_line|#define PCI_DEVICE_ID_NCR_53C875 0xf
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_NCR_53C875J
DECL|macro|PCI_DEVICE_ID_NCR_53C875J
mdefine_line|#define PCI_DEVICE_ID_NCR_53C875J 0x8f
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_NCR_53C885
DECL|macro|PCI_DEVICE_ID_NCR_53C885
mdefine_line|#define PCI_DEVICE_ID_NCR_53C885 0xd
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_NCR_53C895
DECL|macro|PCI_DEVICE_ID_NCR_53C895
mdefine_line|#define PCI_DEVICE_ID_NCR_53C895 0xc
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_NCR_53C896
DECL|macro|PCI_DEVICE_ID_NCR_53C896
mdefine_line|#define PCI_DEVICE_ID_NCR_53C896 0xb
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_NCR_53C895A
DECL|macro|PCI_DEVICE_ID_NCR_53C895A
mdefine_line|#define PCI_DEVICE_ID_NCR_53C895A 0x12
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_NCR_53C875A
DECL|macro|PCI_DEVICE_ID_NCR_53C875A
mdefine_line|#define PCI_DEVICE_ID_NCR_53C875A 0x13
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_NCR_53C1510D
DECL|macro|PCI_DEVICE_ID_NCR_53C1510D
mdefine_line|#define PCI_DEVICE_ID_NCR_53C1510D 0xa
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_LSI_53C1010
DECL|macro|PCI_DEVICE_ID_LSI_53C1010
mdefine_line|#define PCI_DEVICE_ID_LSI_53C1010 0x20
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_LSI_53C1010_66
DECL|macro|PCI_DEVICE_ID_LSI_53C1010_66
mdefine_line|#define PCI_DEVICE_ID_LSI_53C1010_66 0x21
macro_line|#endif
multiline_comment|/*&n;**   NCR53C8XX devices features table.&n;*/
r_typedef
r_struct
(brace
DECL|member|device_id
r_int
r_int
id|device_id
suffix:semicolon
DECL|member|revision_id
r_int
r_int
id|revision_id
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|burst_max
r_int
r_char
id|burst_max
suffix:semicolon
multiline_comment|/* log-base-2 of max burst */
DECL|member|offset_max
r_int
r_char
id|offset_max
suffix:semicolon
DECL|member|nr_divisor
r_int
r_char
id|nr_divisor
suffix:semicolon
DECL|member|features
r_int
r_int
id|features
suffix:semicolon
DECL|macro|FE_LED0
mdefine_line|#define FE_LED0&t;&t;(1&lt;&lt;0)
DECL|macro|FE_WIDE
mdefine_line|#define FE_WIDE&t;&t;(1&lt;&lt;1)    /* Wide data transfers */
DECL|macro|FE_ULTRA
mdefine_line|#define FE_ULTRA&t;(1&lt;&lt;2)&t;  /* Ultra speed 20Mtrans/sec */
DECL|macro|FE_ULTRA2
mdefine_line|#define FE_ULTRA2&t;(1&lt;&lt;3)&t;  /* Ultra 2 - 40 Mtrans/sec */
DECL|macro|FE_DBLR
mdefine_line|#define FE_DBLR&t;&t;(1&lt;&lt;4)&t;  /* Clock doubler present */
DECL|macro|FE_QUAD
mdefine_line|#define FE_QUAD&t;&t;(1&lt;&lt;5)&t;  /* Clock quadrupler present */
DECL|macro|FE_ERL
mdefine_line|#define FE_ERL&t;&t;(1&lt;&lt;6)    /* Enable read line */
DECL|macro|FE_CLSE
mdefine_line|#define FE_CLSE&t;&t;(1&lt;&lt;7)    /* Cache line size enable */
DECL|macro|FE_WRIE
mdefine_line|#define FE_WRIE&t;&t;(1&lt;&lt;8)    /* Write &amp; Invalidate enable */
DECL|macro|FE_ERMP
mdefine_line|#define FE_ERMP&t;&t;(1&lt;&lt;9)    /* Enable read multiple */
DECL|macro|FE_BOF
mdefine_line|#define FE_BOF&t;&t;(1&lt;&lt;10)   /* Burst opcode fetch */
DECL|macro|FE_DFS
mdefine_line|#define FE_DFS&t;&t;(1&lt;&lt;11)   /* DMA fifo size */
DECL|macro|FE_PFEN
mdefine_line|#define FE_PFEN&t;&t;(1&lt;&lt;12)   /* Prefetch enable */
DECL|macro|FE_LDSTR
mdefine_line|#define FE_LDSTR&t;(1&lt;&lt;13)   /* Load/Store supported */
DECL|macro|FE_RAM
mdefine_line|#define FE_RAM&t;&t;(1&lt;&lt;14)   /* On chip RAM present */
DECL|macro|FE_VARCLK
mdefine_line|#define FE_VARCLK&t;(1&lt;&lt;15)   /* SCSI clock may vary */
DECL|macro|FE_RAM8K
mdefine_line|#define FE_RAM8K&t;(1&lt;&lt;16)   /* On chip RAM sized 8Kb */
DECL|macro|FE_64BIT
mdefine_line|#define FE_64BIT&t;(1&lt;&lt;17)   /* Have a 64-bit PCI interface */
DECL|macro|FE_IO256
mdefine_line|#define FE_IO256&t;(1&lt;&lt;18)   /* Requires full 256 bytes in PCI space */
DECL|macro|FE_NOPM
mdefine_line|#define FE_NOPM&t;&t;(1&lt;&lt;19)   /* Scripts handles phase mismatch */
DECL|macro|FE_LEDC
mdefine_line|#define FE_LEDC&t;&t;(1&lt;&lt;20)   /* Hardware control of LED */
DECL|macro|FE_DIFF
mdefine_line|#define FE_DIFF&t;&t;(1&lt;&lt;21)   /* Support Differential SCSI */
DECL|macro|FE_ULTRA3
mdefine_line|#define FE_ULTRA3&t;(1&lt;&lt;22)   /* Ultra-3 80Mtrans/sec */
DECL|macro|FE_66MHZ
mdefine_line|#define FE_66MHZ &t;(1&lt;&lt;23)   /* 66MHz PCI Support */
DECL|macro|FE_DAC
mdefine_line|#define FE_DAC&t; &t;(1&lt;&lt;24)   /* Support DAC cycles (64 bit addressing) */
DECL|macro|FE_ISTAT1
mdefine_line|#define FE_ISTAT1 &t;(1&lt;&lt;25)   /* Have ISTAT1, MBOX0, MBOX1 registers */
DECL|macro|FE_DAC_IN_USE
mdefine_line|#define FE_DAC_IN_USE&t;(1&lt;&lt;26)&t;  /* Platform does DAC cycles */
DECL|macro|FE_CACHE_SET
mdefine_line|#define FE_CACHE_SET&t;(FE_ERL|FE_CLSE|FE_WRIE|FE_ERMP)
DECL|macro|FE_SCSI_SET
mdefine_line|#define FE_SCSI_SET&t;(FE_WIDE|FE_ULTRA|FE_ULTRA2|FE_DBLR|FE_QUAD|F_CLK80)
DECL|macro|FE_SPECIAL_SET
mdefine_line|#define FE_SPECIAL_SET&t;(FE_CACHE_SET|FE_BOF|FE_DFS|FE_LDSTR|FE_PFEN|FE_RAM)
DECL|typedef|ncr_chip
)brace
id|ncr_chip
suffix:semicolon
multiline_comment|/*&n;**&t;DEL 397 - 53C875 Rev 3 - Part Number 609-0392410 - ITEM 3.&n;**&t;Memory Read transaction terminated by a retry followed by &n;**&t;Memory Read Line command.&n;*/
DECL|macro|FE_CACHE0_SET
mdefine_line|#define FE_CACHE0_SET&t;(FE_CACHE_SET &amp; ~FE_ERL)
multiline_comment|/*&n;**&t;DEL 397 - 53C875 Rev 3 - Part Number 609-0392410 - ITEM 5.&n;**&t;On paper, this errata is harmless. But it is a good reason for &n;**&t;using a shorter programmed burst length (64 DWORDS instead of 128).&n;*/
DECL|macro|SCSI_NCR_CHIP_TABLE
mdefine_line|#define SCSI_NCR_CHIP_TABLE&t;&t;&t;&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n; {PCI_DEVICE_ID_NCR_53C810, 0x0f, &quot;810&quot;,  4,  8, 4,&t;&t;&t;&bslash;&n; FE_ERL}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n; ,&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n; {PCI_DEVICE_ID_NCR_53C810, 0xff, &quot;810a&quot;, 4,  8, 4,&t;&t;&t;&bslash;&n; FE_CACHE_SET|FE_LDSTR|FE_PFEN|FE_BOF}&t;&t;&t;&t;&t;&bslash;&n; ,&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n; {PCI_DEVICE_ID_NCR_53C815, 0xff, &quot;815&quot;,  4,  8, 4,&t;&t;&t;&bslash;&n; FE_ERL|FE_BOF}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n; ,&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n; {PCI_DEVICE_ID_NCR_53C820, 0xff, &quot;820&quot;,  4,  8, 4,&t;&t;&t;&bslash;&n; FE_WIDE|FE_ERL}&t;&t;&t;&t;&t;&t;&t;&bslash;&n; ,&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n; {PCI_DEVICE_ID_NCR_53C825, 0x0f, &quot;825&quot;,  4,  8, 4,&t;&t;&t;&bslash;&n; FE_WIDE|FE_ERL|FE_BOF|FE_DIFF}&t;&t;&t;&t;&t;&t;&bslash;&n; ,&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n; {PCI_DEVICE_ID_NCR_53C825, 0xff, &quot;825a&quot;, 6,  8, 4,&t;&t;&t;&bslash;&n; FE_WIDE|FE_CACHE0_SET|FE_BOF|FE_DFS|FE_LDSTR|FE_PFEN|FE_RAM|FE_DIFF}&t;&bslash;&n; ,&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n; {PCI_DEVICE_ID_NCR_53C860, 0xff, &quot;860&quot;,  4,  8, 5,&t;&t;&t;&bslash;&n; FE_ULTRA|FE_CACHE_SET|FE_BOF|FE_LDSTR|FE_PFEN}&t;&t;&t;&t;&bslash;&n; ,&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n; {PCI_DEVICE_ID_NCR_53C875, 0x01, &quot;875&quot;,  6, 16, 5,&t;&t;&t;&bslash;&n; FE_WIDE|FE_ULTRA|FE_CACHE0_SET|FE_BOF|FE_DFS|FE_LDSTR|FE_PFEN|&t;&t;&bslash;&n; FE_RAM|FE_DIFF|FE_VARCLK}&t;&t;&t;&t;&t;&t;&bslash;&n; ,&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n; {PCI_DEVICE_ID_NCR_53C875, 0xff, &quot;875&quot;,  6, 16, 5,&t;&t;&t;&bslash;&n; FE_WIDE|FE_ULTRA|FE_DBLR|FE_CACHE0_SET|FE_BOF|FE_DFS|FE_LDSTR|FE_PFEN|&t;&bslash;&n; FE_RAM|FE_DIFF|FE_VARCLK}&t;&t;&t;&t;&t;&t;&bslash;&n; ,&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n; {PCI_DEVICE_ID_NCR_53C875J,0xff, &quot;875J&quot;, 6, 16, 5,&t;&t;&t;&bslash;&n; FE_WIDE|FE_ULTRA|FE_DBLR|FE_CACHE0_SET|FE_BOF|FE_DFS|FE_LDSTR|FE_PFEN|&t;&bslash;&n; FE_RAM|FE_VARCLK}&t;&t;&t;&t;&t;&t;&t;&bslash;&n; ,&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n; {PCI_DEVICE_ID_NCR_53C885, 0xff, &quot;885&quot;,  6, 16, 5,&t;&t;&t;&bslash;&n; FE_WIDE|FE_ULTRA|FE_DBLR|FE_CACHE0_SET|FE_BOF|FE_DFS|FE_LDSTR|FE_PFEN|&t;&bslash;&n; FE_RAM|FE_DIFF|FE_VARCLK}&t;&t;&t;&t;&t;&t;&bslash;&n; ,&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n; {PCI_DEVICE_ID_NCR_53C895, 0xff, &quot;895&quot;,  6, 31, 7,&t;&t;&t;&bslash;&n; FE_WIDE|FE_ULTRA2|FE_QUAD|FE_CACHE_SET|FE_BOF|FE_DFS|FE_LDSTR|FE_PFEN|&t;&bslash;&n; FE_RAM}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n; ,&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n; {PCI_DEVICE_ID_NCR_53C896, 0xff, &quot;896&quot;,  6, 31, 7,&t;&t;&t;&bslash;&n; FE_WIDE|FE_ULTRA2|FE_QUAD|FE_CACHE_SET|FE_BOF|FE_DFS|FE_LDSTR|FE_PFEN|&t;&bslash;&n; FE_RAM|FE_RAM8K|FE_64BIT|FE_DAC|FE_IO256|FE_NOPM|FE_LEDC|FE_ISTAT1}&t;&bslash;&n; ,&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n; {PCI_DEVICE_ID_NCR_53C895A, 0xff, &quot;895a&quot;,  6, 31, 7,&t;&t;&t;&bslash;&n; FE_WIDE|FE_ULTRA2|FE_QUAD|FE_CACHE_SET|FE_BOF|FE_DFS|FE_LDSTR|FE_PFEN|&t;&bslash;&n; FE_RAM|FE_RAM8K|FE_DAC|FE_IO256|FE_NOPM|FE_LEDC}&t;&t;&t;&bslash;&n; ,&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n; {PCI_DEVICE_ID_NCR_53C875A, 0xff, &quot;875a&quot;,  6, 31, 7,&t;&t;&t;&bslash;&n; FE_WIDE|FE_ULTRA|FE_QUAD|FE_CACHE_SET|FE_BOF|FE_DFS|FE_LDSTR|FE_PFEN|&t;&bslash;&n; FE_RAM|FE_DAC|FE_IO256|FE_NOPM|FE_LEDC}&t;&t;&t;&t;&bslash;&n; ,&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n; {PCI_DEVICE_ID_NCR_53C1510D, 0xff, &quot;1510D&quot;,  7, 31, 7,&t;&t;&t;&bslash;&n; FE_WIDE|FE_ULTRA2|FE_QUAD|FE_CACHE_SET|FE_BOF|FE_DFS|FE_LDSTR|FE_PFEN|&t;&bslash;&n; FE_RAM|FE_IO256}&t;&t;&t;&t;&t;&t;&t;&bslash;&n; ,&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n; {PCI_DEVICE_ID_LSI_53C1010, 0xff, &quot;1010-33&quot;,  6, 62, 7,&t;&t;&bslash;&n; FE_WIDE|FE_QUAD|FE_CACHE_SET|FE_BOF|FE_DFS|FE_LDSTR|FE_PFEN|FE_ISTAT1|&t;&bslash;&n; FE_RAM|FE_RAM8K|FE_64BIT|FE_DAC|FE_IO256|FE_NOPM|FE_LEDC|FE_ULTRA3}&t;&bslash;&n; ,&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n; {PCI_DEVICE_ID_LSI_53C1010_66, 0xff, &quot;1010-66&quot;,  6, 62, 7,&t;&t;&bslash;&n; FE_WIDE|FE_QUAD|FE_CACHE_SET|FE_BOF|FE_DFS|FE_LDSTR|FE_PFEN|FE_ISTAT1|&t;&bslash;&n; FE_RAM|FE_RAM8K|FE_64BIT|FE_DAC|FE_IO256|FE_NOPM|FE_LEDC|FE_ULTRA3|&t;&bslash;&n; FE_66MHZ}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;}
multiline_comment|/*&n; * List of supported NCR chip ids&n; */
DECL|macro|SCSI_NCR_CHIP_IDS
mdefine_line|#define SCSI_NCR_CHIP_IDS&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&bslash;&n;&t;PCI_DEVICE_ID_NCR_53C810,&t;&bslash;&n;&t;PCI_DEVICE_ID_NCR_53C815,&t;&bslash;&n;&t;PCI_DEVICE_ID_NCR_53C820,&t;&bslash;&n;&t;PCI_DEVICE_ID_NCR_53C825,&t;&bslash;&n;&t;PCI_DEVICE_ID_NCR_53C860,&t;&bslash;&n;&t;PCI_DEVICE_ID_NCR_53C875,&t;&bslash;&n;&t;PCI_DEVICE_ID_NCR_53C875J,&t;&bslash;&n;&t;PCI_DEVICE_ID_NCR_53C885,&t;&bslash;&n;&t;PCI_DEVICE_ID_NCR_53C895,&t;&bslash;&n;&t;PCI_DEVICE_ID_NCR_53C896,&t;&bslash;&n;&t;PCI_DEVICE_ID_NCR_53C895A,&t;&bslash;&n;&t;PCI_DEVICE_ID_NCR_53C1510D,&t;&bslash;&n; &t;PCI_DEVICE_ID_LSI_53C1010,&t;&bslash;&n; &t;PCI_DEVICE_ID_LSI_53C1010_66&t;&bslash;&n;}
multiline_comment|/*&n;**&t;Driver setup structure.&n;**&n;**&t;This structure is initialized from linux config options.&n;**&t;It can be overridden at boot-up by the boot command line.&n;*/
DECL|macro|SCSI_NCR_MAX_EXCLUDES
mdefine_line|#define SCSI_NCR_MAX_EXCLUDES 8
DECL|struct|ncr_driver_setup
r_struct
id|ncr_driver_setup
(brace
DECL|member|master_parity
id|u_char
id|master_parity
suffix:semicolon
DECL|member|scsi_parity
id|u_char
id|scsi_parity
suffix:semicolon
DECL|member|disconnection
id|u_char
id|disconnection
suffix:semicolon
DECL|member|special_features
id|u_char
id|special_features
suffix:semicolon
DECL|member|force_sync_nego
id|u_char
id|force_sync_nego
suffix:semicolon
DECL|member|reverse_probe
id|u_char
id|reverse_probe
suffix:semicolon
DECL|member|pci_fix_up
id|u_char
id|pci_fix_up
suffix:semicolon
DECL|member|use_nvram
id|u_char
id|use_nvram
suffix:semicolon
DECL|member|verbose
id|u_char
id|verbose
suffix:semicolon
DECL|member|default_tags
id|u_char
id|default_tags
suffix:semicolon
DECL|member|default_sync
id|u_short
id|default_sync
suffix:semicolon
DECL|member|debug
id|u_short
id|debug
suffix:semicolon
DECL|member|burst_max
id|u_char
id|burst_max
suffix:semicolon
DECL|member|led_pin
id|u_char
id|led_pin
suffix:semicolon
DECL|member|max_wide
id|u_char
id|max_wide
suffix:semicolon
DECL|member|settle_delay
id|u_char
id|settle_delay
suffix:semicolon
DECL|member|diff_support
id|u_char
id|diff_support
suffix:semicolon
DECL|member|irqm
id|u_char
id|irqm
suffix:semicolon
DECL|member|bus_check
id|u_char
id|bus_check
suffix:semicolon
DECL|member|optimize
id|u_char
id|optimize
suffix:semicolon
DECL|member|recovery
id|u_char
id|recovery
suffix:semicolon
DECL|member|host_id
id|u_char
id|host_id
suffix:semicolon
DECL|member|iarb
id|u_short
id|iarb
suffix:semicolon
DECL|member|excludes
id|u_long
id|excludes
(braket
id|SCSI_NCR_MAX_EXCLUDES
)braket
suffix:semicolon
DECL|member|tag_ctrl
r_char
id|tag_ctrl
(braket
l_int|100
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n;**&t;Initial setup.&n;**&t;Can be overriden at startup by a command line.&n;*/
DECL|macro|SCSI_NCR_DRIVER_SETUP
mdefine_line|#define SCSI_NCR_DRIVER_SETUP&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&bslash;&n;&t;SCSI_NCR_SETUP_MASTER_PARITY,&t;&t;&bslash;&n;&t;SCSI_NCR_SETUP_SCSI_PARITY,&t;&t;&bslash;&n;&t;SCSI_NCR_SETUP_DISCONNECTION,&t;&t;&bslash;&n;&t;SCSI_NCR_SETUP_SPECIAL_FEATURES,&t;&bslash;&n;&t;SCSI_NCR_SETUP_FORCE_SYNC_NEGO,&t;&t;&bslash;&n;&t;0,&t;&t;&t;&t;&t;&bslash;&n;&t;0,&t;&t;&t;&t;&t;&bslash;&n;&t;1,&t;&t;&t;&t;&t;&bslash;&n;&t;0,&t;&t;&t;&t;&t;&bslash;&n;&t;SCSI_NCR_SETUP_DEFAULT_TAGS,&t;&t;&bslash;&n;&t;SCSI_NCR_SETUP_DEFAULT_SYNC,&t;&t;&bslash;&n;&t;0x00,&t;&t;&t;&t;&t;&bslash;&n;&t;7,&t;&t;&t;&t;&t;&bslash;&n;&t;SCSI_NCR_SETUP_LED_PIN,&t;&t;&t;&bslash;&n;&t;1,&t;&t;&t;&t;&t;&bslash;&n;&t;SCSI_NCR_SETUP_SETTLE_TIME,&t;&t;&bslash;&n;&t;SCSI_NCR_SETUP_DIFF_SUPPORT,&t;&t;&bslash;&n;&t;0,&t;&t;&t;&t;&t;&bslash;&n;&t;1,&t;&t;&t;&t;&t;&bslash;&n;&t;0,&t;&t;&t;&t;&t;&bslash;&n;&t;0,&t;&t;&t;&t;&t;&bslash;&n;&t;255,&t;&t;&t;&t;&t;&bslash;&n;&t;0x00&t;&t;&t;&t;&t;&bslash;&n;}
multiline_comment|/*&n;**&t;Boot fail safe setup.&n;**&t;Override initial setup from boot command line:&n;**&t;ncr53c8xx=safe:y&n;*/
DECL|macro|SCSI_NCR_DRIVER_SAFE_SETUP
mdefine_line|#define SCSI_NCR_DRIVER_SAFE_SETUP&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&bslash;&n;&t;0,&t;&t;&t;&t;&t;&bslash;&n;&t;1,&t;&t;&t;&t;&t;&bslash;&n;&t;0,&t;&t;&t;&t;&t;&bslash;&n;&t;0,&t;&t;&t;&t;&t;&bslash;&n;&t;0,&t;&t;&t;&t;&t;&bslash;&n;&t;0,&t;&t;&t;&t;&t;&bslash;&n;&t;0,&t;&t;&t;&t;&t;&bslash;&n;&t;1,&t;&t;&t;&t;&t;&bslash;&n;&t;2,&t;&t;&t;&t;&t;&bslash;&n;&t;0,&t;&t;&t;&t;&t;&bslash;&n;&t;255,&t;&t;&t;&t;&t;&bslash;&n;&t;0x00,&t;&t;&t;&t;&t;&bslash;&n;&t;255,&t;&t;&t;&t;&t;&bslash;&n;&t;0,&t;&t;&t;&t;&t;&bslash;&n;&t;0,&t;&t;&t;&t;&t;&bslash;&n;&t;10,&t;&t;&t;&t;&t;&bslash;&n;&t;1,&t;&t;&t;&t;&t;&bslash;&n;&t;1,&t;&t;&t;&t;&t;&bslash;&n;&t;1,&t;&t;&t;&t;&t;&bslash;&n;&t;0,&t;&t;&t;&t;&t;&bslash;&n;&t;0,&t;&t;&t;&t;&t;&bslash;&n;&t;255&t;&t;&t;&t;&t;&bslash;&n;}
macro_line|#ifdef SCSI_NCR_NVRAM_SUPPORT
multiline_comment|/*&n;**&t;Symbios NvRAM data format&n;*/
DECL|macro|SYMBIOS_NVRAM_SIZE
mdefine_line|#define SYMBIOS_NVRAM_SIZE 368
DECL|macro|SYMBIOS_NVRAM_ADDRESS
mdefine_line|#define SYMBIOS_NVRAM_ADDRESS 0x100
DECL|struct|Symbios_nvram
r_struct
id|Symbios_nvram
(brace
multiline_comment|/* Header 6 bytes */
DECL|member|type
id|u_short
id|type
suffix:semicolon
multiline_comment|/* 0x0000 */
DECL|member|byte_count
id|u_short
id|byte_count
suffix:semicolon
multiline_comment|/* excluding header/trailer */
DECL|member|checksum
id|u_short
id|checksum
suffix:semicolon
multiline_comment|/* Controller set up 20 bytes */
DECL|member|v_major
id|u_char
id|v_major
suffix:semicolon
multiline_comment|/* 0x00 */
DECL|member|v_minor
id|u_char
id|v_minor
suffix:semicolon
multiline_comment|/* 0x30 */
DECL|member|boot_crc
id|u_int32
id|boot_crc
suffix:semicolon
DECL|member|flags
id|u_short
id|flags
suffix:semicolon
DECL|macro|SYMBIOS_SCAM_ENABLE
mdefine_line|#define SYMBIOS_SCAM_ENABLE&t;(1)
DECL|macro|SYMBIOS_PARITY_ENABLE
mdefine_line|#define SYMBIOS_PARITY_ENABLE&t;(1&lt;&lt;1)
DECL|macro|SYMBIOS_VERBOSE_MSGS
mdefine_line|#define SYMBIOS_VERBOSE_MSGS&t;(1&lt;&lt;2)
DECL|macro|SYMBIOS_CHS_MAPPING
mdefine_line|#define SYMBIOS_CHS_MAPPING&t;(1&lt;&lt;3)
DECL|macro|SYMBIOS_NO_NVRAM
mdefine_line|#define SYMBIOS_NO_NVRAM&t;(1&lt;&lt;3)&t;/* ??? */
DECL|member|flags1
id|u_short
id|flags1
suffix:semicolon
DECL|macro|SYMBIOS_SCAN_HI_LO
mdefine_line|#define SYMBIOS_SCAN_HI_LO&t;(1)
DECL|member|term_state
id|u_short
id|term_state
suffix:semicolon
DECL|macro|SYMBIOS_TERM_CANT_PROGRAM
mdefine_line|#define SYMBIOS_TERM_CANT_PROGRAM&t;(0)
DECL|macro|SYMBIOS_TERM_ENABLED
mdefine_line|#define SYMBIOS_TERM_ENABLED&t;&t;(1)
DECL|macro|SYMBIOS_TERM_DISABLED
mdefine_line|#define SYMBIOS_TERM_DISABLED&t;&t;(2)
DECL|member|rmvbl_flags
id|u_short
id|rmvbl_flags
suffix:semicolon
DECL|macro|SYMBIOS_RMVBL_NO_SUPPORT
mdefine_line|#define SYMBIOS_RMVBL_NO_SUPPORT&t;(0)
DECL|macro|SYMBIOS_RMVBL_BOOT_DEVICE
mdefine_line|#define SYMBIOS_RMVBL_BOOT_DEVICE&t;(1)
DECL|macro|SYMBIOS_RMVBL_MEDIA_INSTALLED
mdefine_line|#define SYMBIOS_RMVBL_MEDIA_INSTALLED&t;(2)
DECL|member|host_id
id|u_char
id|host_id
suffix:semicolon
DECL|member|num_hba
id|u_char
id|num_hba
suffix:semicolon
multiline_comment|/* 0x04 */
DECL|member|num_devices
id|u_char
id|num_devices
suffix:semicolon
multiline_comment|/* 0x10 */
DECL|member|max_scam_devices
id|u_char
id|max_scam_devices
suffix:semicolon
multiline_comment|/* 0x04 */
DECL|member|num_valid_scam_devives
id|u_char
id|num_valid_scam_devives
suffix:semicolon
multiline_comment|/* 0x00 */
DECL|member|rsvd
id|u_char
id|rsvd
suffix:semicolon
multiline_comment|/* Boot order 14 bytes * 4 */
DECL|struct|Symbios_host
r_struct
id|Symbios_host
(brace
DECL|member|type
id|u_short
id|type
suffix:semicolon
multiline_comment|/* 4:8xx / 0:nok */
DECL|member|device_id
id|u_short
id|device_id
suffix:semicolon
multiline_comment|/* PCI device id */
DECL|member|vendor_id
id|u_short
id|vendor_id
suffix:semicolon
multiline_comment|/* PCI vendor id */
DECL|member|bus_nr
id|u_char
id|bus_nr
suffix:semicolon
multiline_comment|/* PCI bus number */
DECL|member|device_fn
id|u_char
id|device_fn
suffix:semicolon
multiline_comment|/* PCI device/function number &lt;&lt; 3*/
DECL|member|word8
id|u_short
id|word8
suffix:semicolon
DECL|member|flags
id|u_short
id|flags
suffix:semicolon
DECL|macro|SYMBIOS_INIT_SCAN_AT_BOOT
mdefine_line|#define&t;SYMBIOS_INIT_SCAN_AT_BOOT&t;(1)
DECL|member|io_port
id|u_short
id|io_port
suffix:semicolon
multiline_comment|/* PCI io_port address */
DECL|member|host
)brace
id|host
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Targets 8 bytes * 16 */
DECL|struct|Symbios_target
r_struct
id|Symbios_target
(brace
DECL|member|flags
id|u_char
id|flags
suffix:semicolon
DECL|macro|SYMBIOS_DISCONNECT_ENABLE
mdefine_line|#define SYMBIOS_DISCONNECT_ENABLE&t;(1)
DECL|macro|SYMBIOS_SCAN_AT_BOOT_TIME
mdefine_line|#define SYMBIOS_SCAN_AT_BOOT_TIME&t;(1&lt;&lt;1)
DECL|macro|SYMBIOS_SCAN_LUNS
mdefine_line|#define SYMBIOS_SCAN_LUNS&t;&t;(1&lt;&lt;2)
DECL|macro|SYMBIOS_QUEUE_TAGS_ENABLED
mdefine_line|#define SYMBIOS_QUEUE_TAGS_ENABLED&t;(1&lt;&lt;3)
DECL|member|rsvd
id|u_char
id|rsvd
suffix:semicolon
DECL|member|bus_width
id|u_char
id|bus_width
suffix:semicolon
multiline_comment|/* 0x08/0x10 */
DECL|member|sync_offset
id|u_char
id|sync_offset
suffix:semicolon
DECL|member|sync_period
id|u_short
id|sync_period
suffix:semicolon
multiline_comment|/* 4*period factor */
DECL|member|timeout
id|u_short
id|timeout
suffix:semicolon
DECL|member|target
)brace
id|target
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* Scam table 8 bytes * 4 */
DECL|struct|Symbios_scam
r_struct
id|Symbios_scam
(brace
DECL|member|id
id|u_short
id|id
suffix:semicolon
DECL|member|method
id|u_short
id|method
suffix:semicolon
DECL|macro|SYMBIOS_SCAM_DEFAULT_METHOD
mdefine_line|#define SYMBIOS_SCAM_DEFAULT_METHOD&t;(0)
DECL|macro|SYMBIOS_SCAM_DONT_ASSIGN
mdefine_line|#define SYMBIOS_SCAM_DONT_ASSIGN&t;(1)
DECL|macro|SYMBIOS_SCAM_SET_SPECIFIC_ID
mdefine_line|#define SYMBIOS_SCAM_SET_SPECIFIC_ID&t;(2)
DECL|macro|SYMBIOS_SCAM_USE_ORDER_GIVEN
mdefine_line|#define SYMBIOS_SCAM_USE_ORDER_GIVEN&t;(3)
DECL|member|status
id|u_short
id|status
suffix:semicolon
DECL|macro|SYMBIOS_SCAM_UNKNOWN
mdefine_line|#define SYMBIOS_SCAM_UNKNOWN&t;&t;(0)
DECL|macro|SYMBIOS_SCAM_DEVICE_NOT_FOUND
mdefine_line|#define SYMBIOS_SCAM_DEVICE_NOT_FOUND&t;(1)
DECL|macro|SYMBIOS_SCAM_ID_NOT_SET
mdefine_line|#define SYMBIOS_SCAM_ID_NOT_SET&t;&t;(2)
DECL|macro|SYMBIOS_SCAM_ID_VALID
mdefine_line|#define SYMBIOS_SCAM_ID_VALID&t;&t;(3)
DECL|member|target_id
id|u_char
id|target_id
suffix:semicolon
DECL|member|rsvd
id|u_char
id|rsvd
suffix:semicolon
DECL|member|scam
)brace
id|scam
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|spare_devices
id|u_char
id|spare_devices
(braket
l_int|15
op_star
l_int|8
)braket
suffix:semicolon
DECL|member|trailer
id|u_char
id|trailer
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* 0xfe 0xfe 0x00 0x00 0x00 0x00 */
)brace
suffix:semicolon
DECL|typedef|Symbios_nvram
r_typedef
r_struct
id|Symbios_nvram
id|Symbios_nvram
suffix:semicolon
DECL|typedef|Symbios_host
r_typedef
r_struct
id|Symbios_host
id|Symbios_host
suffix:semicolon
DECL|typedef|Symbios_target
r_typedef
r_struct
id|Symbios_target
id|Symbios_target
suffix:semicolon
DECL|typedef|Symbios_scam
r_typedef
r_struct
id|Symbios_scam
id|Symbios_scam
suffix:semicolon
multiline_comment|/*&n;**&t;Tekram NvRAM data format.&n;*/
DECL|macro|TEKRAM_NVRAM_SIZE
mdefine_line|#define TEKRAM_NVRAM_SIZE 64
DECL|macro|TEKRAM_93C46_NVRAM_ADDRESS
mdefine_line|#define TEKRAM_93C46_NVRAM_ADDRESS 0
DECL|macro|TEKRAM_24C16_NVRAM_ADDRESS
mdefine_line|#define TEKRAM_24C16_NVRAM_ADDRESS 0x40
DECL|struct|Tekram_nvram
r_struct
id|Tekram_nvram
(brace
DECL|struct|Tekram_target
r_struct
id|Tekram_target
(brace
DECL|member|flags
id|u_char
id|flags
suffix:semicolon
DECL|macro|TEKRAM_PARITY_CHECK
mdefine_line|#define&t;TEKRAM_PARITY_CHECK&t;&t;(1)
DECL|macro|TEKRAM_SYNC_NEGO
mdefine_line|#define TEKRAM_SYNC_NEGO&t;&t;(1&lt;&lt;1)
DECL|macro|TEKRAM_DISCONNECT_ENABLE
mdefine_line|#define TEKRAM_DISCONNECT_ENABLE&t;(1&lt;&lt;2)
DECL|macro|TEKRAM_START_CMD
mdefine_line|#define&t;TEKRAM_START_CMD&t;&t;(1&lt;&lt;3)
DECL|macro|TEKRAM_TAGGED_COMMANDS
mdefine_line|#define TEKRAM_TAGGED_COMMANDS&t;&t;(1&lt;&lt;4)
DECL|macro|TEKRAM_WIDE_NEGO
mdefine_line|#define TEKRAM_WIDE_NEGO&t;&t;(1&lt;&lt;5)
DECL|member|sync_index
id|u_char
id|sync_index
suffix:semicolon
DECL|member|word2
id|u_short
id|word2
suffix:semicolon
DECL|member|target
)brace
id|target
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|host_id
id|u_char
id|host_id
suffix:semicolon
DECL|member|flags
id|u_char
id|flags
suffix:semicolon
DECL|macro|TEKRAM_MORE_THAN_2_DRIVES
mdefine_line|#define TEKRAM_MORE_THAN_2_DRIVES&t;(1)
DECL|macro|TEKRAM_DRIVES_SUP_1GB
mdefine_line|#define TEKRAM_DRIVES_SUP_1GB&t;&t;(1&lt;&lt;1)
DECL|macro|TEKRAM_RESET_ON_POWER_ON
mdefine_line|#define&t;TEKRAM_RESET_ON_POWER_ON&t;(1&lt;&lt;2)
DECL|macro|TEKRAM_ACTIVE_NEGATION
mdefine_line|#define TEKRAM_ACTIVE_NEGATION&t;&t;(1&lt;&lt;3)
DECL|macro|TEKRAM_IMMEDIATE_SEEK
mdefine_line|#define TEKRAM_IMMEDIATE_SEEK&t;&t;(1&lt;&lt;4)
DECL|macro|TEKRAM_SCAN_LUNS
mdefine_line|#define&t;TEKRAM_SCAN_LUNS&t;&t;(1&lt;&lt;5)
DECL|macro|TEKRAM_REMOVABLE_FLAGS
mdefine_line|#define&t;TEKRAM_REMOVABLE_FLAGS&t;&t;(3&lt;&lt;6)&t;/* 0: disable; 1: boot device; 2:all */
DECL|member|boot_delay_index
id|u_char
id|boot_delay_index
suffix:semicolon
DECL|member|max_tags_index
id|u_char
id|max_tags_index
suffix:semicolon
DECL|member|flags1
id|u_short
id|flags1
suffix:semicolon
DECL|macro|TEKRAM_F2_F6_ENABLED
mdefine_line|#define TEKRAM_F2_F6_ENABLED&t;&t;(1)
DECL|member|spare
id|u_short
id|spare
(braket
l_int|29
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|typedef|Tekram_nvram
r_typedef
r_struct
id|Tekram_nvram
id|Tekram_nvram
suffix:semicolon
DECL|typedef|Tekram_target
r_typedef
r_struct
id|Tekram_target
id|Tekram_target
suffix:semicolon
macro_line|#endif /* SCSI_NCR_NVRAM_SUPPORT */
multiline_comment|/**************** ORIGINAL CONTENT of ncrreg.h from FreeBSD ******************/
multiline_comment|/*-----------------------------------------------------------------&n;**&n;**&t;The ncr 53c810 register structure.&n;**&n;**-----------------------------------------------------------------&n;*/
DECL|struct|ncr_reg
r_struct
id|ncr_reg
(brace
DECL|member|nc_scntl0
multiline_comment|/*00*/
id|u_char
id|nc_scntl0
suffix:semicolon
multiline_comment|/* full arb., ena parity, par-&gt;ATN  */
DECL|member|nc_scntl1
multiline_comment|/*01*/
id|u_char
id|nc_scntl1
suffix:semicolon
multiline_comment|/* no reset                         */
DECL|macro|ISCON
mdefine_line|#define   ISCON   0x10  /* connected to scsi&t;&t;    */
DECL|macro|CRST
mdefine_line|#define   CRST    0x08  /* force reset                      */
DECL|macro|IARB
mdefine_line|#define   IARB    0x02  /* immediate arbitration            */
DECL|member|nc_scntl2
multiline_comment|/*02*/
id|u_char
id|nc_scntl2
suffix:semicolon
multiline_comment|/* no disconnect expected           */
DECL|macro|SDU
mdefine_line|#define   SDU     0x80  /* cmd: disconnect will raise error */
DECL|macro|CHM
mdefine_line|#define   CHM     0x40  /* sta: chained mode                */
DECL|macro|WSS
mdefine_line|#define   WSS     0x08  /* sta: wide scsi send           [W]*/
DECL|macro|WSR
mdefine_line|#define   WSR     0x01  /* sta: wide scsi received       [W]*/
DECL|member|nc_scntl3
multiline_comment|/*03*/
id|u_char
id|nc_scntl3
suffix:semicolon
multiline_comment|/* cnf system clock dependent       */
DECL|macro|EWS
mdefine_line|#define   EWS     0x08  /* cmd: enable wide scsi         [W]*/
DECL|macro|ULTRA
mdefine_line|#define   ULTRA   0x80  /* cmd: ULTRA enable                */
multiline_comment|/* bits 0-2, 7 rsvd for C1010       */
DECL|member|nc_scid
multiline_comment|/*04*/
id|u_char
id|nc_scid
suffix:semicolon
multiline_comment|/* cnf host adapter scsi address    */
DECL|macro|RRE
mdefine_line|#define   RRE     0x40  /* r/w:e enable response to resel.  */
DECL|macro|SRE
mdefine_line|#define   SRE     0x20  /* r/w:e enable response to select  */
DECL|member|nc_sxfer
multiline_comment|/*05*/
id|u_char
id|nc_sxfer
suffix:semicolon
multiline_comment|/* ### Sync speed and count         */
multiline_comment|/* bits 6-7 rsvd for C1010          */
DECL|member|nc_sdid
multiline_comment|/*06*/
id|u_char
id|nc_sdid
suffix:semicolon
multiline_comment|/* ### Destination-ID               */
DECL|member|nc_gpreg
multiline_comment|/*07*/
id|u_char
id|nc_gpreg
suffix:semicolon
multiline_comment|/* ??? IO-Pins                      */
DECL|member|nc_sfbr
multiline_comment|/*08*/
id|u_char
id|nc_sfbr
suffix:semicolon
multiline_comment|/* ### First byte in phase          */
DECL|member|nc_socl
multiline_comment|/*09*/
id|u_char
id|nc_socl
suffix:semicolon
DECL|macro|CREQ
mdefine_line|#define   CREQ&t;  0x80&t;/* r/w: SCSI-REQ                    */
DECL|macro|CACK
mdefine_line|#define   CACK&t;  0x40&t;/* r/w: SCSI-ACK                    */
DECL|macro|CBSY
mdefine_line|#define   CBSY&t;  0x20&t;/* r/w: SCSI-BSY                    */
DECL|macro|CSEL
mdefine_line|#define   CSEL&t;  0x10&t;/* r/w: SCSI-SEL                    */
DECL|macro|CATN
mdefine_line|#define   CATN&t;  0x08&t;/* r/w: SCSI-ATN                    */
DECL|macro|CMSG
mdefine_line|#define   CMSG&t;  0x04&t;/* r/w: SCSI-MSG                    */
DECL|macro|CC_D
mdefine_line|#define   CC_D&t;  0x02&t;/* r/w: SCSI-C_D                    */
DECL|macro|CI_O
mdefine_line|#define   CI_O&t;  0x01&t;/* r/w: SCSI-I_O                    */
DECL|member|nc_ssid
multiline_comment|/*0a*/
id|u_char
id|nc_ssid
suffix:semicolon
DECL|member|nc_sbcl
multiline_comment|/*0b*/
id|u_char
id|nc_sbcl
suffix:semicolon
DECL|member|nc_dstat
multiline_comment|/*0c*/
id|u_char
id|nc_dstat
suffix:semicolon
DECL|macro|DFE
mdefine_line|#define   DFE     0x80  /* sta: dma fifo empty              */
DECL|macro|MDPE
mdefine_line|#define   MDPE    0x40  /* int: master data parity error    */
DECL|macro|BF
mdefine_line|#define   BF      0x20  /* int: script: bus fault           */
DECL|macro|ABRT
mdefine_line|#define   ABRT    0x10  /* int: script: command aborted     */
DECL|macro|SSI
mdefine_line|#define   SSI     0x08  /* int: script: single step         */
DECL|macro|SIR
mdefine_line|#define   SIR     0x04  /* int: script: interrupt instruct. */
DECL|macro|IID
mdefine_line|#define   IID     0x01  /* int: script: illegal instruct.   */
DECL|member|nc_sstat0
multiline_comment|/*0d*/
id|u_char
id|nc_sstat0
suffix:semicolon
DECL|macro|ILF
mdefine_line|#define   ILF     0x80  /* sta: data in SIDL register lsb   */
DECL|macro|ORF
mdefine_line|#define   ORF     0x40  /* sta: data in SODR register lsb   */
DECL|macro|OLF
mdefine_line|#define   OLF     0x20  /* sta: data in SODL register lsb   */
DECL|macro|AIP
mdefine_line|#define   AIP     0x10  /* sta: arbitration in progress     */
DECL|macro|LOA
mdefine_line|#define   LOA     0x08  /* sta: arbitration lost            */
DECL|macro|WOA
mdefine_line|#define   WOA     0x04  /* sta: arbitration won             */
DECL|macro|IRST
mdefine_line|#define   IRST    0x02  /* sta: scsi reset signal           */
DECL|macro|SDP
mdefine_line|#define   SDP     0x01  /* sta: scsi parity signal          */
DECL|member|nc_sstat1
multiline_comment|/*0e*/
id|u_char
id|nc_sstat1
suffix:semicolon
DECL|macro|FF3210
mdefine_line|#define   FF3210  0xf0&t;/* sta: bytes in the scsi fifo      */
DECL|member|nc_sstat2
multiline_comment|/*0f*/
id|u_char
id|nc_sstat2
suffix:semicolon
DECL|macro|ILF1
mdefine_line|#define   ILF1    0x80  /* sta: data in SIDL register msb[W]*/
DECL|macro|ORF1
mdefine_line|#define   ORF1    0x40  /* sta: data in SODR register msb[W]*/
DECL|macro|OLF1
mdefine_line|#define   OLF1    0x20  /* sta: data in SODL register msb[W]*/
DECL|macro|DM
mdefine_line|#define   DM      0x04  /* sta: DIFFSENS mismatch (895/6 only) */
DECL|macro|LDSC
mdefine_line|#define   LDSC    0x02  /* sta: disconnect &amp; reconnect      */
DECL|member|nc_dsa
multiline_comment|/*10*/
id|u_char
id|nc_dsa
suffix:semicolon
multiline_comment|/* --&gt; Base page                    */
DECL|member|nc_dsa1
multiline_comment|/*11*/
id|u_char
id|nc_dsa1
suffix:semicolon
DECL|member|nc_dsa2
multiline_comment|/*12*/
id|u_char
id|nc_dsa2
suffix:semicolon
DECL|member|nc_dsa3
multiline_comment|/*13*/
id|u_char
id|nc_dsa3
suffix:semicolon
DECL|member|nc_istat
multiline_comment|/*14*/
id|u_char
id|nc_istat
suffix:semicolon
multiline_comment|/* --&gt; Main Command and status      */
DECL|macro|CABRT
mdefine_line|#define   CABRT   0x80  /* cmd: abort current operation     */
DECL|macro|SRST
mdefine_line|#define   SRST    0x40  /* mod: reset chip                  */
DECL|macro|SIGP
mdefine_line|#define   SIGP    0x20  /* r/w: message from host to ncr    */
DECL|macro|SEM
mdefine_line|#define   SEM     0x10  /* r/w: message between host + ncr  */
DECL|macro|CON
mdefine_line|#define   CON     0x08  /* sta: connected to scsi           */
DECL|macro|INTF
mdefine_line|#define   INTF    0x04  /* sta: int on the fly (reset by wr)*/
DECL|macro|SIP
mdefine_line|#define   SIP     0x02  /* sta: scsi-interrupt              */
DECL|macro|DIP
mdefine_line|#define   DIP     0x01  /* sta: host/script interrupt       */
DECL|member|nc_istat1
multiline_comment|/*15*/
id|u_char
id|nc_istat1
suffix:semicolon
multiline_comment|/* 896 and later cores only */
DECL|macro|FLSH
mdefine_line|#define   FLSH    0x04  /* sta: chip is flushing            */
DECL|macro|SRUN
mdefine_line|#define   SRUN    0x02  /* sta: scripts are running         */
DECL|macro|SIRQD
mdefine_line|#define   SIRQD   0x01  /* r/w: disable INT pin             */
DECL|member|nc_mbox0
multiline_comment|/*16*/
id|u_char
id|nc_mbox0
suffix:semicolon
multiline_comment|/* 896 and later cores only */
DECL|member|nc_mbox1
multiline_comment|/*17*/
id|u_char
id|nc_mbox1
suffix:semicolon
multiline_comment|/* 896 and later cores only */
DECL|member|nc_ctest0
multiline_comment|/*18*/
id|u_char
id|nc_ctest0
suffix:semicolon
DECL|member|nc_ctest1
multiline_comment|/*19*/
id|u_char
id|nc_ctest1
suffix:semicolon
DECL|member|nc_ctest2
multiline_comment|/*1a*/
id|u_char
id|nc_ctest2
suffix:semicolon
DECL|macro|CSIGP
mdefine_line|#define   CSIGP   0x40
multiline_comment|/* bits 0-2,7 rsvd for C1010        */
DECL|member|nc_ctest3
multiline_comment|/*1b*/
id|u_char
id|nc_ctest3
suffix:semicolon
DECL|macro|FLF
mdefine_line|#define   FLF     0x08  /* cmd: flush dma fifo              */
DECL|macro|CLF
mdefine_line|#define   CLF&t;  0x04&t;/* cmd: clear dma fifo&t;&t;    */
DECL|macro|FM
mdefine_line|#define   FM      0x02  /* mod: fetch pin mode              */
DECL|macro|WRIE
mdefine_line|#define   WRIE    0x01  /* mod: write and invalidate enable */
multiline_comment|/* bits 4-7 rsvd for C1010          */
DECL|member|nc_temp
multiline_comment|/*1c*/
id|u_int32
id|nc_temp
suffix:semicolon
multiline_comment|/* ### Temporary stack              */
DECL|member|nc_dfifo
multiline_comment|/*20*/
id|u_char
id|nc_dfifo
suffix:semicolon
DECL|member|nc_ctest4
multiline_comment|/*21*/
id|u_char
id|nc_ctest4
suffix:semicolon
DECL|macro|BDIS
mdefine_line|#define   BDIS    0x80  /* mod: burst disable               */
DECL|macro|MPEE
mdefine_line|#define   MPEE    0x08  /* mod: master parity error enable  */
DECL|member|nc_ctest5
multiline_comment|/*22*/
id|u_char
id|nc_ctest5
suffix:semicolon
DECL|macro|DFS
mdefine_line|#define   DFS     0x20  /* mod: dma fifo size               */
multiline_comment|/* bits 0-1, 3-7 rsvd for C1010          */
DECL|member|nc_ctest6
multiline_comment|/*23*/
id|u_char
id|nc_ctest6
suffix:semicolon
DECL|member|nc_dbc
multiline_comment|/*24*/
id|u_int32
id|nc_dbc
suffix:semicolon
multiline_comment|/* ### Byte count and command       */
DECL|member|nc_dnad
multiline_comment|/*28*/
id|u_int32
id|nc_dnad
suffix:semicolon
multiline_comment|/* ### Next command register        */
DECL|member|nc_dsp
multiline_comment|/*2c*/
id|u_int32
id|nc_dsp
suffix:semicolon
multiline_comment|/* --&gt; Script Pointer               */
DECL|member|nc_dsps
multiline_comment|/*30*/
id|u_int32
id|nc_dsps
suffix:semicolon
multiline_comment|/* --&gt; Script pointer save/opcode#2 */
DECL|member|nc_scratcha
multiline_comment|/*34*/
id|u_char
id|nc_scratcha
suffix:semicolon
multiline_comment|/* Temporary register a            */
DECL|member|nc_scratcha1
multiline_comment|/*35*/
id|u_char
id|nc_scratcha1
suffix:semicolon
DECL|member|nc_scratcha2
multiline_comment|/*36*/
id|u_char
id|nc_scratcha2
suffix:semicolon
DECL|member|nc_scratcha3
multiline_comment|/*37*/
id|u_char
id|nc_scratcha3
suffix:semicolon
DECL|member|nc_dmode
multiline_comment|/*38*/
id|u_char
id|nc_dmode
suffix:semicolon
DECL|macro|BL_2
mdefine_line|#define   BL_2    0x80  /* mod: burst length shift value +2 */
DECL|macro|BL_1
mdefine_line|#define   BL_1    0x40  /* mod: burst length shift value +1 */
DECL|macro|ERL
mdefine_line|#define   ERL     0x08  /* mod: enable read line            */
DECL|macro|ERMP
mdefine_line|#define   ERMP    0x04  /* mod: enable read multiple        */
DECL|macro|BOF
mdefine_line|#define   BOF     0x02  /* mod: burst op code fetch         */
DECL|member|nc_dien
multiline_comment|/*39*/
id|u_char
id|nc_dien
suffix:semicolon
DECL|member|nc_sbr
multiline_comment|/*3a*/
id|u_char
id|nc_sbr
suffix:semicolon
DECL|member|nc_dcntl
multiline_comment|/*3b*/
id|u_char
id|nc_dcntl
suffix:semicolon
multiline_comment|/* --&gt; Script execution control     */
DECL|macro|CLSE
mdefine_line|#define   CLSE    0x80  /* mod: cache line size enable      */
DECL|macro|PFF
mdefine_line|#define   PFF     0x40  /* cmd: pre-fetch flush             */
DECL|macro|PFEN
mdefine_line|#define   PFEN    0x20  /* mod: pre-fetch enable            */
DECL|macro|SSM
mdefine_line|#define   SSM     0x10  /* mod: single step mode            */
DECL|macro|IRQM
mdefine_line|#define   IRQM    0x08  /* mod: irq mode (1 = totem pole !) */
DECL|macro|STD
mdefine_line|#define   STD     0x04  /* cmd: start dma mode              */
DECL|macro|IRQD
mdefine_line|#define   IRQD    0x02  /* mod: irq disable                 */
DECL|macro|NOCOM
mdefine_line|#define&t;  NOCOM   0x01&t;/* cmd: protect sfbr while reselect */
multiline_comment|/* bits 0-1 rsvd for C1010          */
DECL|member|nc_adder
multiline_comment|/*3c*/
id|u_int32
id|nc_adder
suffix:semicolon
DECL|member|nc_sien
multiline_comment|/*40*/
id|u_short
id|nc_sien
suffix:semicolon
multiline_comment|/* --&gt;: interrupt enable            */
DECL|member|nc_sist
multiline_comment|/*42*/
id|u_short
id|nc_sist
suffix:semicolon
multiline_comment|/* &lt;--: interrupt status            */
DECL|macro|SBMC
mdefine_line|#define   SBMC    0x1000/* sta: SCSI Bus Mode Change (895/6 only) */
DECL|macro|STO
mdefine_line|#define   STO     0x0400/* sta: timeout (select)            */
DECL|macro|GEN
mdefine_line|#define   GEN     0x0200/* sta: timeout (general)           */
DECL|macro|HTH
mdefine_line|#define   HTH     0x0100/* sta: timeout (handshake)         */
DECL|macro|MA
mdefine_line|#define   MA      0x80  /* sta: phase mismatch              */
DECL|macro|CMP
mdefine_line|#define   CMP     0x40  /* sta: arbitration complete        */
DECL|macro|SEL
mdefine_line|#define   SEL     0x20  /* sta: selected by another device  */
DECL|macro|RSL
mdefine_line|#define   RSL     0x10  /* sta: reselected by another device*/
DECL|macro|SGE
mdefine_line|#define   SGE     0x08  /* sta: gross error (over/underflow)*/
DECL|macro|UDC
mdefine_line|#define   UDC     0x04  /* sta: unexpected disconnect       */
DECL|macro|RST
mdefine_line|#define   RST     0x02  /* sta: scsi bus reset detected     */
DECL|macro|PAR
mdefine_line|#define   PAR     0x01  /* sta: scsi parity error           */
DECL|member|nc_slpar
multiline_comment|/*44*/
id|u_char
id|nc_slpar
suffix:semicolon
DECL|member|nc_swide
multiline_comment|/*45*/
id|u_char
id|nc_swide
suffix:semicolon
DECL|member|nc_macntl
multiline_comment|/*46*/
id|u_char
id|nc_macntl
suffix:semicolon
DECL|member|nc_gpcntl
multiline_comment|/*47*/
id|u_char
id|nc_gpcntl
suffix:semicolon
DECL|member|nc_stime0
multiline_comment|/*48*/
id|u_char
id|nc_stime0
suffix:semicolon
multiline_comment|/* cmd: timeout for select&amp;handshake*/
DECL|member|nc_stime1
multiline_comment|/*49*/
id|u_char
id|nc_stime1
suffix:semicolon
multiline_comment|/* cmd: timeout user defined        */
DECL|member|nc_respid
multiline_comment|/*4a*/
id|u_short
id|nc_respid
suffix:semicolon
multiline_comment|/* sta: Reselect-IDs                */
DECL|member|nc_stest0
multiline_comment|/*4c*/
id|u_char
id|nc_stest0
suffix:semicolon
DECL|member|nc_stest1
multiline_comment|/*4d*/
id|u_char
id|nc_stest1
suffix:semicolon
DECL|macro|SCLK
mdefine_line|#define   SCLK    0x80&t;/* Use the PCI clock as SCSI clock&t;*/
DECL|macro|DBLEN
mdefine_line|#define   DBLEN   0x08&t;/* clock doubler running&t;&t;*/
DECL|macro|DBLSEL
mdefine_line|#define   DBLSEL  0x04&t;/* clock doubler selected&t;&t;*/
DECL|member|nc_stest2
multiline_comment|/*4e*/
id|u_char
id|nc_stest2
suffix:semicolon
DECL|macro|ROF
mdefine_line|#define   ROF     0x40&t;/* reset scsi offset (after gross error!) */
DECL|macro|EXT
mdefine_line|#define   EXT     0x02  /* extended filtering                     */
DECL|member|nc_stest3
multiline_comment|/*4f*/
id|u_char
id|nc_stest3
suffix:semicolon
DECL|macro|TE
mdefine_line|#define   TE     0x80&t;/* c: tolerAnt enable */
DECL|macro|HSC
mdefine_line|#define   HSC    0x20&t;/* c: Halt SCSI Clock */
DECL|macro|CSF
mdefine_line|#define   CSF    0x02&t;/* c: clear scsi fifo */
DECL|member|nc_sidl
multiline_comment|/*50*/
id|u_short
id|nc_sidl
suffix:semicolon
multiline_comment|/* Lowlevel: latched from scsi data */
DECL|member|nc_stest4
multiline_comment|/*52*/
id|u_char
id|nc_stest4
suffix:semicolon
DECL|macro|SMODE
mdefine_line|#define   SMODE  0xc0&t;/* SCSI bus mode      (895/6 only) */
DECL|macro|SMODE_HVD
mdefine_line|#define    SMODE_HVD 0x40&t;/* High Voltage Differential       */
DECL|macro|SMODE_SE
mdefine_line|#define    SMODE_SE  0x80&t;/* Single Ended                    */
DECL|macro|SMODE_LVD
mdefine_line|#define    SMODE_LVD 0xc0&t;/* Low Voltage Differential        */
DECL|macro|LCKFRQ
mdefine_line|#define   LCKFRQ 0x20&t;/* Frequency Lock (895/6 only)     */
multiline_comment|/* bits 0-5 rsvd for C1010          */
DECL|member|nc_53_
multiline_comment|/*53*/
id|u_char
id|nc_53_
suffix:semicolon
DECL|member|nc_sodl
multiline_comment|/*54*/
id|u_short
id|nc_sodl
suffix:semicolon
multiline_comment|/* Lowlevel: data out to scsi data  */
DECL|member|nc_ccntl0
multiline_comment|/*56*/
id|u_char
id|nc_ccntl0
suffix:semicolon
multiline_comment|/* Chip Control 0 (896)             */
DECL|macro|ENPMJ
mdefine_line|#define   ENPMJ  0x80&t;/* Enable Phase Mismatch Jump       */
DECL|macro|PMJCTL
mdefine_line|#define   PMJCTL 0x40&t;/* Phase Mismatch Jump Control      */
DECL|macro|ENNDJ
mdefine_line|#define   ENNDJ  0x20&t;/* Enable Non Data PM Jump          */
DECL|macro|DISFC
mdefine_line|#define   DISFC  0x10&t;/* Disable Auto FIFO Clear          */
DECL|macro|DILS
mdefine_line|#define   DILS   0x02&t;/* Disable Internal Load/Store      */
DECL|macro|DPR
mdefine_line|#define   DPR    0x01&t;/* Disable Pipe Req                 */
DECL|member|nc_ccntl1
multiline_comment|/*57*/
id|u_char
id|nc_ccntl1
suffix:semicolon
multiline_comment|/* Chip Control 1 (896)             */
DECL|macro|ZMOD
mdefine_line|#define   ZMOD   0x80&t;/* High Impedance Mode              */
DECL|macro|DIC
mdefine_line|#define&t;  DIC&t; 0x10&t;/* Disable Internal Cycles&t;    */
DECL|macro|DDAC
mdefine_line|#define   DDAC   0x08&t;/* Disable Dual Address Cycle       */
DECL|macro|XTIMOD
mdefine_line|#define   XTIMOD 0x04&t;/* 64-bit Table Ind. Indexing Mode  */
DECL|macro|EXTIBMV
mdefine_line|#define   EXTIBMV 0x02&t;/* Enable 64-bit Table Ind. BMOV    */
DECL|macro|EXDBMV
mdefine_line|#define   EXDBMV 0x01&t;/* Enable 64-bit Direct BMOV        */
DECL|member|nc_sbdl
multiline_comment|/*58*/
id|u_short
id|nc_sbdl
suffix:semicolon
multiline_comment|/* Lowlevel: data from scsi data    */
DECL|member|nc_5a_
multiline_comment|/*5a*/
id|u_short
id|nc_5a_
suffix:semicolon
DECL|member|nc_scr0
multiline_comment|/*5c*/
id|u_char
id|nc_scr0
suffix:semicolon
multiline_comment|/* Working register B               */
DECL|member|nc_scr1
multiline_comment|/*5d*/
id|u_char
id|nc_scr1
suffix:semicolon
multiline_comment|/*                                  */
DECL|member|nc_scr2
multiline_comment|/*5e*/
id|u_char
id|nc_scr2
suffix:semicolon
multiline_comment|/*                                  */
DECL|member|nc_scr3
multiline_comment|/*5f*/
id|u_char
id|nc_scr3
suffix:semicolon
multiline_comment|/*                                  */
DECL|member|nc_scrx
multiline_comment|/*60*/
id|u_char
id|nc_scrx
(braket
l_int|64
)braket
suffix:semicolon
multiline_comment|/* Working register C-R             */
DECL|member|nc_mmrs
multiline_comment|/*a0*/
id|u_int32
id|nc_mmrs
suffix:semicolon
multiline_comment|/* Memory Move Read Selector        */
DECL|member|nc_mmws
multiline_comment|/*a4*/
id|u_int32
id|nc_mmws
suffix:semicolon
multiline_comment|/* Memory Move Write Selector       */
DECL|member|nc_sfs
multiline_comment|/*a8*/
id|u_int32
id|nc_sfs
suffix:semicolon
multiline_comment|/* Script Fetch Selector            */
DECL|member|nc_drs
multiline_comment|/*ac*/
id|u_int32
id|nc_drs
suffix:semicolon
multiline_comment|/* DSA Relative Selector            */
DECL|member|nc_sbms
multiline_comment|/*b0*/
id|u_int32
id|nc_sbms
suffix:semicolon
multiline_comment|/* Static Block Move Selector       */
DECL|member|nc_dbms
multiline_comment|/*b4*/
id|u_int32
id|nc_dbms
suffix:semicolon
multiline_comment|/* Dynamic Block Move Selector      */
DECL|member|nc_dnad64
multiline_comment|/*b8*/
id|u_int32
id|nc_dnad64
suffix:semicolon
multiline_comment|/* DMA Next Address 64              */
DECL|member|nc_scntl4
multiline_comment|/*bc*/
id|u_short
id|nc_scntl4
suffix:semicolon
multiline_comment|/* C1010 only                       */
DECL|macro|U3EN
mdefine_line|#define   U3EN   0x80&t;/* Enable Ultra 3                   */
DECL|macro|AIPEN
mdefine_line|#define   AIPEN&t; 0x40   /* Allow check upper byte lanes     */
DECL|macro|XCLKH_DT
mdefine_line|#define   XCLKH_DT 0x08 /* Extra clock of data hold on DT&n;&t;&t;&t;&t;&t;transfer edge&t;            */
DECL|macro|XCLKH_ST
mdefine_line|#define   XCLKH_ST 0x04 /* Extra clock of data hold on ST&n;&t;&t;&t;&t;&t;transfer edge&t;            */
DECL|member|nc_aipcntl0
multiline_comment|/*be*/
id|u_char
id|nc_aipcntl0
suffix:semicolon
multiline_comment|/* Epat Control 1 C1010 only        */
DECL|member|nc_aipcntl1
multiline_comment|/*bf*/
id|u_char
id|nc_aipcntl1
suffix:semicolon
multiline_comment|/* AIP Control C1010_66 Only        */
DECL|member|nc_pmjad1
multiline_comment|/*c0*/
id|u_int32
id|nc_pmjad1
suffix:semicolon
multiline_comment|/* Phase Mismatch Jump Address 1    */
DECL|member|nc_pmjad2
multiline_comment|/*c4*/
id|u_int32
id|nc_pmjad2
suffix:semicolon
multiline_comment|/* Phase Mismatch Jump Address 2    */
DECL|member|nc_rbc
multiline_comment|/*c8*/
id|u_char
id|nc_rbc
suffix:semicolon
multiline_comment|/* Remaining Byte Count             */
DECL|member|nc_rbc1
multiline_comment|/*c9*/
id|u_char
id|nc_rbc1
suffix:semicolon
multiline_comment|/*                                  */
DECL|member|nc_rbc2
multiline_comment|/*ca*/
id|u_char
id|nc_rbc2
suffix:semicolon
multiline_comment|/*                                  */
DECL|member|nc_rbc3
multiline_comment|/*cb*/
id|u_char
id|nc_rbc3
suffix:semicolon
multiline_comment|/*                                  */
DECL|member|nc_ua
multiline_comment|/*cc*/
id|u_char
id|nc_ua
suffix:semicolon
multiline_comment|/* Updated Address                  */
DECL|member|nc_ua1
multiline_comment|/*cd*/
id|u_char
id|nc_ua1
suffix:semicolon
multiline_comment|/*                                  */
DECL|member|nc_ua2
multiline_comment|/*ce*/
id|u_char
id|nc_ua2
suffix:semicolon
multiline_comment|/*                                  */
DECL|member|nc_ua3
multiline_comment|/*cf*/
id|u_char
id|nc_ua3
suffix:semicolon
multiline_comment|/*                                  */
DECL|member|nc_esa
multiline_comment|/*d0*/
id|u_int32
id|nc_esa
suffix:semicolon
multiline_comment|/* Entry Storage Address            */
DECL|member|nc_ia
multiline_comment|/*d4*/
id|u_char
id|nc_ia
suffix:semicolon
multiline_comment|/* Instruction Address              */
DECL|member|nc_ia1
multiline_comment|/*d5*/
id|u_char
id|nc_ia1
suffix:semicolon
DECL|member|nc_ia2
multiline_comment|/*d6*/
id|u_char
id|nc_ia2
suffix:semicolon
DECL|member|nc_ia3
multiline_comment|/*d7*/
id|u_char
id|nc_ia3
suffix:semicolon
DECL|member|nc_sbc
multiline_comment|/*d8*/
id|u_int32
id|nc_sbc
suffix:semicolon
multiline_comment|/* SCSI Byte Count (3 bytes only)   */
DECL|member|nc_csbc
multiline_comment|/*dc*/
id|u_int32
id|nc_csbc
suffix:semicolon
multiline_comment|/* Cumulative SCSI Byte Count       */
multiline_comment|/* Following for C1010 only         */
DECL|member|nc_crcpad
multiline_comment|/*e0*/
id|u_short
id|nc_crcpad
suffix:semicolon
multiline_comment|/* CRC Value                        */
DECL|member|nc_crccntl0
multiline_comment|/*e2*/
id|u_char
id|nc_crccntl0
suffix:semicolon
multiline_comment|/* CRC control register             */
DECL|macro|SNDCRC
mdefine_line|#define   SNDCRC  0x10&t;/* Send CRC Request                 */
DECL|member|nc_crccntl1
multiline_comment|/*e3*/
id|u_char
id|nc_crccntl1
suffix:semicolon
multiline_comment|/* CRC control register             */
DECL|member|nc_crcdata
multiline_comment|/*e4*/
id|u_int32
id|nc_crcdata
suffix:semicolon
multiline_comment|/* CRC data register                */
DECL|member|nc_e8_
multiline_comment|/*e8*/
id|u_int32
id|nc_e8_
suffix:semicolon
multiline_comment|/* rsvd &t;&t;&t;    */
DECL|member|nc_ec_
multiline_comment|/*ec*/
id|u_int32
id|nc_ec_
suffix:semicolon
multiline_comment|/* rsvd &t;&t;&t;    */
DECL|member|nc_dfbc
multiline_comment|/*f0*/
id|u_short
id|nc_dfbc
suffix:semicolon
multiline_comment|/* DMA FIFO byte count              */
)brace
suffix:semicolon
multiline_comment|/*-----------------------------------------------------------&n;**&n;**&t;Utility macros for the script.&n;**&n;**-----------------------------------------------------------&n;*/
DECL|macro|REGJ
mdefine_line|#define REGJ(p,r) (offsetof(struct ncr_reg, p ## r))
DECL|macro|REG
mdefine_line|#define REG(r) REGJ (nc_, r)
DECL|typedef|ncrcmd
r_typedef
id|u_int32
id|ncrcmd
suffix:semicolon
multiline_comment|/*-----------------------------------------------------------&n;**&n;**&t;SCSI phases&n;**&n;**&t;DT phases illegal for ncr driver.&n;**&n;**-----------------------------------------------------------&n;*/
DECL|macro|SCR_DATA_OUT
mdefine_line|#define&t;SCR_DATA_OUT&t;0x00000000
DECL|macro|SCR_DATA_IN
mdefine_line|#define&t;SCR_DATA_IN&t;0x01000000
DECL|macro|SCR_COMMAND
mdefine_line|#define&t;SCR_COMMAND&t;0x02000000
DECL|macro|SCR_STATUS
mdefine_line|#define&t;SCR_STATUS&t;0x03000000
DECL|macro|SCR_DT_DATA_OUT
mdefine_line|#define SCR_DT_DATA_OUT&t;0x04000000
DECL|macro|SCR_DT_DATA_IN
mdefine_line|#define SCR_DT_DATA_IN&t;0x05000000
DECL|macro|SCR_MSG_OUT
mdefine_line|#define SCR_MSG_OUT&t;0x06000000
DECL|macro|SCR_MSG_IN
mdefine_line|#define SCR_MSG_IN      0x07000000
DECL|macro|SCR_ILG_OUT
mdefine_line|#define SCR_ILG_OUT&t;0x04000000
DECL|macro|SCR_ILG_IN
mdefine_line|#define SCR_ILG_IN&t;0x05000000
multiline_comment|/*-----------------------------------------------------------&n;**&n;**&t;Data transfer via SCSI.&n;**&n;**-----------------------------------------------------------&n;**&n;**&t;MOVE_ABS (LEN)&n;**&t;&lt;&lt;start address&gt;&gt;&n;**&n;**&t;MOVE_IND (LEN)&n;**&t;&lt;&lt;dnad_offset&gt;&gt;&n;**&n;**&t;MOVE_TBL&n;**&t;&lt;&lt;dnad_offset&gt;&gt;&n;**&n;**-----------------------------------------------------------&n;*/
DECL|macro|OPC_MOVE
mdefine_line|#define OPC_MOVE          0x08000000
DECL|macro|SCR_MOVE_ABS
mdefine_line|#define SCR_MOVE_ABS(l) ((0x00000000 | OPC_MOVE) | (l))
DECL|macro|SCR_MOVE_IND
mdefine_line|#define SCR_MOVE_IND(l) ((0x20000000 | OPC_MOVE) | (l))
DECL|macro|SCR_MOVE_TBL
mdefine_line|#define SCR_MOVE_TBL     (0x10000000 | OPC_MOVE)
DECL|macro|SCR_CHMOV_ABS
mdefine_line|#define SCR_CHMOV_ABS(l) ((0x00000000) | (l))
DECL|macro|SCR_CHMOV_IND
mdefine_line|#define SCR_CHMOV_IND(l) ((0x20000000) | (l))
DECL|macro|SCR_CHMOV_TBL
mdefine_line|#define SCR_CHMOV_TBL     (0x10000000)
DECL|struct|scr_tblmove
r_struct
id|scr_tblmove
(brace
DECL|member|size
id|u_int32
id|size
suffix:semicolon
DECL|member|addr
id|u_int32
id|addr
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*-----------------------------------------------------------&n;**&n;**&t;Selection&n;**&n;**-----------------------------------------------------------&n;**&n;**&t;SEL_ABS | SCR_ID (0..15)    [ | REL_JMP]&n;**&t;&lt;&lt;alternate_address&gt;&gt;&n;**&n;**&t;SEL_TBL | &lt;&lt; dnad_offset&gt;&gt;  [ | REL_JMP]&n;**&t;&lt;&lt;alternate_address&gt;&gt;&n;**&n;**-----------------------------------------------------------&n;*/
DECL|macro|SCR_SEL_ABS
mdefine_line|#define&t;SCR_SEL_ABS&t;0x40000000
DECL|macro|SCR_SEL_ABS_ATN
mdefine_line|#define&t;SCR_SEL_ABS_ATN&t;0x41000000
DECL|macro|SCR_SEL_TBL
mdefine_line|#define&t;SCR_SEL_TBL&t;0x42000000
DECL|macro|SCR_SEL_TBL_ATN
mdefine_line|#define&t;SCR_SEL_TBL_ATN&t;0x43000000
DECL|struct|scr_tblsel
r_struct
id|scr_tblsel
(brace
DECL|member|sel_scntl4
id|u_char
id|sel_scntl4
suffix:semicolon
DECL|member|sel_sxfer
id|u_char
id|sel_sxfer
suffix:semicolon
DECL|member|sel_id
id|u_char
id|sel_id
suffix:semicolon
DECL|member|sel_scntl3
id|u_char
id|sel_scntl3
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|SCR_JMP_REL
mdefine_line|#define SCR_JMP_REL     0x04000000
DECL|macro|SCR_ID
mdefine_line|#define SCR_ID(id)&t;(((u_int32)(id)) &lt;&lt; 16)
multiline_comment|/*-----------------------------------------------------------&n;**&n;**&t;Waiting for Disconnect or Reselect&n;**&n;**-----------------------------------------------------------&n;**&n;**&t;WAIT_DISC&n;**&t;dummy: &lt;&lt;alternate_address&gt;&gt;&n;**&n;**&t;WAIT_RESEL&n;**&t;&lt;&lt;alternate_address&gt;&gt;&n;**&n;**-----------------------------------------------------------&n;*/
DECL|macro|SCR_WAIT_DISC
mdefine_line|#define&t;SCR_WAIT_DISC&t;0x48000000
DECL|macro|SCR_WAIT_RESEL
mdefine_line|#define SCR_WAIT_RESEL  0x50000000
multiline_comment|/*-----------------------------------------------------------&n;**&n;**&t;Bit Set / Reset&n;**&n;**-----------------------------------------------------------&n;**&n;**&t;SET (flags {|.. })&n;**&n;**&t;CLR (flags {|.. })&n;**&n;**-----------------------------------------------------------&n;*/
DECL|macro|SCR_SET
mdefine_line|#define SCR_SET(f)     (0x58000000 | (f))
DECL|macro|SCR_CLR
mdefine_line|#define SCR_CLR(f)     (0x60000000 | (f))
DECL|macro|SCR_CARRY
mdefine_line|#define&t;SCR_CARRY&t;0x00000400
DECL|macro|SCR_TRG
mdefine_line|#define&t;SCR_TRG&t;&t;0x00000200
DECL|macro|SCR_ACK
mdefine_line|#define&t;SCR_ACK&t;&t;0x00000040
DECL|macro|SCR_ATN
mdefine_line|#define&t;SCR_ATN&t;&t;0x00000008
multiline_comment|/*-----------------------------------------------------------&n;**&n;**&t;Memory to memory move&n;**&n;**-----------------------------------------------------------&n;**&n;**&t;COPY (bytecount)&n;**&t;&lt;&lt; source_address &gt;&gt;&n;**&t;&lt;&lt; destination_address &gt;&gt;&n;**&n;**&t;SCR_COPY   sets the NO FLUSH option by default.&n;**&t;SCR_COPY_F does not set this option.&n;**&n;**&t;For chips which do not support this option,&n;**&t;ncr_copy_and_bind() will remove this bit.&n;**-----------------------------------------------------------&n;*/
DECL|macro|SCR_NO_FLUSH
mdefine_line|#define SCR_NO_FLUSH 0x01000000
DECL|macro|SCR_COPY
mdefine_line|#define SCR_COPY(n) (0xc0000000 | SCR_NO_FLUSH | (n))
DECL|macro|SCR_COPY_F
mdefine_line|#define SCR_COPY_F(n) (0xc0000000 | (n))
multiline_comment|/*-----------------------------------------------------------&n;**&n;**&t;Register move and binary operations&n;**&n;**-----------------------------------------------------------&n;**&n;**&t;SFBR_REG (reg, op, data)        reg  = SFBR op data&n;**&t;&lt;&lt; 0 &gt;&gt;&n;**&n;**&t;REG_SFBR (reg, op, data)        SFBR = reg op data&n;**&t;&lt;&lt; 0 &gt;&gt;&n;**&n;**&t;REG_REG  (reg, op, data)        reg  = reg op data&n;**&t;&lt;&lt; 0 &gt;&gt;&n;**&n;**-----------------------------------------------------------&n;**&t;On 810A, 860, 825A, 875, 895 and 896 chips the content &n;**&t;of SFBR register can be used as data (SCR_SFBR_DATA).&n;**&t;The 896 has additionnal IO registers starting at &n;**&t;offset 0x80. Bit 7 of register offset is stored in &n;**&t;bit 7 of the SCRIPTS instruction first DWORD.&n;**-----------------------------------------------------------&n;*/
DECL|macro|SCR_REG_OFS
mdefine_line|#define SCR_REG_OFS(ofs) ((((ofs) &amp; 0x7f) &lt;&lt; 16ul) + ((ofs) &amp; 0x80)) 
DECL|macro|SCR_SFBR_REG
mdefine_line|#define SCR_SFBR_REG(reg,op,data) &bslash;&n;        (0x68000000 | (SCR_REG_OFS(REG(reg))) | (op) | (((data)&amp;0xff)&lt;&lt;8ul))
DECL|macro|SCR_REG_SFBR
mdefine_line|#define SCR_REG_SFBR(reg,op,data) &bslash;&n;        (0x70000000 | (SCR_REG_OFS(REG(reg))) | (op) | (((data)&amp;0xff)&lt;&lt;8ul))
DECL|macro|SCR_REG_REG
mdefine_line|#define SCR_REG_REG(reg,op,data) &bslash;&n;        (0x78000000 | (SCR_REG_OFS(REG(reg))) | (op) | (((data)&amp;0xff)&lt;&lt;8ul))
DECL|macro|SCR_LOAD
mdefine_line|#define      SCR_LOAD   0x00000000
DECL|macro|SCR_SHL
mdefine_line|#define      SCR_SHL    0x01000000
DECL|macro|SCR_OR
mdefine_line|#define      SCR_OR     0x02000000
DECL|macro|SCR_XOR
mdefine_line|#define      SCR_XOR    0x03000000
DECL|macro|SCR_AND
mdefine_line|#define      SCR_AND    0x04000000
DECL|macro|SCR_SHR
mdefine_line|#define      SCR_SHR    0x05000000
DECL|macro|SCR_ADD
mdefine_line|#define      SCR_ADD    0x06000000
DECL|macro|SCR_ADDC
mdefine_line|#define      SCR_ADDC   0x07000000
DECL|macro|SCR_SFBR_DATA
mdefine_line|#define      SCR_SFBR_DATA   (0x00800000&gt;&gt;8ul)&t;/* Use SFBR as data */
multiline_comment|/*-----------------------------------------------------------&n;**&n;**&t;FROM_REG (reg)&t;&t;  SFBR = reg&n;**&t;&lt;&lt; 0 &gt;&gt;&n;**&n;**&t;TO_REG&t; (reg)&t;&t;  reg  = SFBR&n;**&t;&lt;&lt; 0 &gt;&gt;&n;**&n;**&t;LOAD_REG (reg, data)&t;  reg  = &lt;data&gt;&n;**&t;&lt;&lt; 0 &gt;&gt;&n;**&n;**&t;LOAD_SFBR(data) &t;  SFBR = &lt;data&gt;&n;**&t;&lt;&lt; 0 &gt;&gt;&n;**&n;**-----------------------------------------------------------&n;*/
DECL|macro|SCR_FROM_REG
mdefine_line|#define&t;SCR_FROM_REG(reg) &bslash;&n;&t;SCR_REG_SFBR(reg,SCR_OR,0)
DECL|macro|SCR_TO_REG
mdefine_line|#define&t;SCR_TO_REG(reg) &bslash;&n;&t;SCR_SFBR_REG(reg,SCR_OR,0)
DECL|macro|SCR_LOAD_REG
mdefine_line|#define&t;SCR_LOAD_REG(reg,data) &bslash;&n;&t;SCR_REG_REG(reg,SCR_LOAD,data)
DECL|macro|SCR_LOAD_SFBR
mdefine_line|#define SCR_LOAD_SFBR(data) &bslash;&n;        (SCR_REG_SFBR (gpreg, SCR_LOAD, data))
multiline_comment|/*-----------------------------------------------------------&n;**&n;**&t;LOAD  from memory   to register.&n;**&t;STORE from register to memory.&n;**&n;**&t;Only supported by 810A, 860, 825A, 875, 895 and 896.&n;**&n;**-----------------------------------------------------------&n;**&n;**&t;LOAD_ABS (LEN)&n;**&t;&lt;&lt;start address&gt;&gt;&n;**&n;**&t;LOAD_REL (LEN)        (DSA relative)&n;**&t;&lt;&lt;dsa_offset&gt;&gt;&n;**&n;**-----------------------------------------------------------&n;*/
DECL|macro|SCR_REG_OFS2
mdefine_line|#define SCR_REG_OFS2(ofs) (((ofs) &amp; 0xff) &lt;&lt; 16ul)
DECL|macro|SCR_NO_FLUSH2
mdefine_line|#define SCR_NO_FLUSH2&t;0x02000000
DECL|macro|SCR_DSA_REL2
mdefine_line|#define SCR_DSA_REL2&t;0x10000000
DECL|macro|SCR_LOAD_R
mdefine_line|#define SCR_LOAD_R(reg, how, n) &bslash;&n;        (0xe1000000 | how | (SCR_REG_OFS2(REG(reg))) | (n))
DECL|macro|SCR_STORE_R
mdefine_line|#define SCR_STORE_R(reg, how, n) &bslash;&n;        (0xe0000000 | how | (SCR_REG_OFS2(REG(reg))) | (n))
DECL|macro|SCR_LOAD_ABS
mdefine_line|#define SCR_LOAD_ABS(reg, n)&t;SCR_LOAD_R(reg, SCR_NO_FLUSH2, n)
DECL|macro|SCR_LOAD_REL
mdefine_line|#define SCR_LOAD_REL(reg, n)&t;SCR_LOAD_R(reg, SCR_NO_FLUSH2|SCR_DSA_REL2, n)
DECL|macro|SCR_LOAD_ABS_F
mdefine_line|#define SCR_LOAD_ABS_F(reg, n)&t;SCR_LOAD_R(reg, 0, n)
DECL|macro|SCR_LOAD_REL_F
mdefine_line|#define SCR_LOAD_REL_F(reg, n)&t;SCR_LOAD_R(reg, SCR_DSA_REL2, n)
DECL|macro|SCR_STORE_ABS
mdefine_line|#define SCR_STORE_ABS(reg, n)&t;SCR_STORE_R(reg, SCR_NO_FLUSH2, n)
DECL|macro|SCR_STORE_REL
mdefine_line|#define SCR_STORE_REL(reg, n)&t;SCR_STORE_R(reg, SCR_NO_FLUSH2|SCR_DSA_REL2,n)
DECL|macro|SCR_STORE_ABS_F
mdefine_line|#define SCR_STORE_ABS_F(reg, n)&t;SCR_STORE_R(reg, 0, n)
DECL|macro|SCR_STORE_REL_F
mdefine_line|#define SCR_STORE_REL_F(reg, n)&t;SCR_STORE_R(reg, SCR_DSA_REL2, n)
multiline_comment|/*-----------------------------------------------------------&n;**&n;**&t;Waiting for Disconnect or Reselect&n;**&n;**-----------------------------------------------------------&n;**&n;**&t;JUMP            [ | IFTRUE/IFFALSE ( ... ) ]&n;**&t;&lt;&lt;address&gt;&gt;&n;**&n;**&t;JUMPR           [ | IFTRUE/IFFALSE ( ... ) ]&n;**&t;&lt;&lt;distance&gt;&gt;&n;**&n;**&t;CALL            [ | IFTRUE/IFFALSE ( ... ) ]&n;**&t;&lt;&lt;address&gt;&gt;&n;**&n;**&t;CALLR           [ | IFTRUE/IFFALSE ( ... ) ]&n;**&t;&lt;&lt;distance&gt;&gt;&n;**&n;**&t;RETURN          [ | IFTRUE/IFFALSE ( ... ) ]&n;**&t;&lt;&lt;dummy&gt;&gt;&n;**&n;**&t;INT             [ | IFTRUE/IFFALSE ( ... ) ]&n;**&t;&lt;&lt;ident&gt;&gt;&n;**&n;**&t;INT_FLY         [ | IFTRUE/IFFALSE ( ... ) ]&n;**&t;&lt;&lt;ident&gt;&gt;&n;**&n;**&t;Conditions:&n;**&t;     WHEN (phase)&n;**&t;     IF   (phase)&n;**&t;     CARRYSET&n;**&t;     DATA (data, mask)&n;**&n;**-----------------------------------------------------------&n;*/
DECL|macro|SCR_NO_OP
mdefine_line|#define SCR_NO_OP       0x80000000
DECL|macro|SCR_JUMP
mdefine_line|#define SCR_JUMP        0x80080000
DECL|macro|SCR_JUMP64
mdefine_line|#define SCR_JUMP64      0x80480000
DECL|macro|SCR_JUMPR
mdefine_line|#define SCR_JUMPR       0x80880000
DECL|macro|SCR_CALL
mdefine_line|#define SCR_CALL        0x88080000
DECL|macro|SCR_CALLR
mdefine_line|#define SCR_CALLR       0x88880000
DECL|macro|SCR_RETURN
mdefine_line|#define SCR_RETURN      0x90080000
DECL|macro|SCR_INT
mdefine_line|#define SCR_INT         0x98080000
DECL|macro|SCR_INT_FLY
mdefine_line|#define SCR_INT_FLY     0x98180000
DECL|macro|IFFALSE
mdefine_line|#define IFFALSE(arg)   (0x00080000 | (arg))
DECL|macro|IFTRUE
mdefine_line|#define IFTRUE(arg)    (0x00000000 | (arg))
DECL|macro|WHEN
mdefine_line|#define WHEN(phase)    (0x00030000 | (phase))
DECL|macro|IF
mdefine_line|#define IF(phase)      (0x00020000 | (phase))
DECL|macro|DATA
mdefine_line|#define DATA(D)        (0x00040000 | ((D) &amp; 0xff))
DECL|macro|MASK
mdefine_line|#define MASK(D,M)      (0x00040000 | (((M ^ 0xff) &amp; 0xff) &lt;&lt; 8ul)|((D) &amp; 0xff))
DECL|macro|CARRYSET
mdefine_line|#define CARRYSET       (0x00200000)
multiline_comment|/*-----------------------------------------------------------&n;**&n;**&t;SCSI  constants.&n;**&n;**-----------------------------------------------------------&n;*/
multiline_comment|/*&n;**&t;Messages&n;*/
DECL|macro|M_COMPLETE
mdefine_line|#define&t;M_COMPLETE&t;(0x00)
DECL|macro|M_EXTENDED
mdefine_line|#define&t;M_EXTENDED&t;(0x01)
DECL|macro|M_SAVE_DP
mdefine_line|#define&t;M_SAVE_DP&t;(0x02)
DECL|macro|M_RESTORE_DP
mdefine_line|#define&t;M_RESTORE_DP&t;(0x03)
DECL|macro|M_DISCONNECT
mdefine_line|#define&t;M_DISCONNECT&t;(0x04)
DECL|macro|M_ID_ERROR
mdefine_line|#define&t;M_ID_ERROR&t;(0x05)
DECL|macro|M_ABORT
mdefine_line|#define&t;M_ABORT&t;&t;(0x06)
DECL|macro|M_REJECT
mdefine_line|#define&t;M_REJECT&t;(0x07)
DECL|macro|M_NOOP
mdefine_line|#define&t;M_NOOP&t;&t;(0x08)
DECL|macro|M_PARITY
mdefine_line|#define&t;M_PARITY&t;(0x09)
DECL|macro|M_LCOMPLETE
mdefine_line|#define&t;M_LCOMPLETE&t;(0x0a)
DECL|macro|M_FCOMPLETE
mdefine_line|#define&t;M_FCOMPLETE&t;(0x0b)
DECL|macro|M_RESET
mdefine_line|#define&t;M_RESET&t;&t;(0x0c)
DECL|macro|M_ABORT_TAG
mdefine_line|#define&t;M_ABORT_TAG&t;(0x0d)
DECL|macro|M_CLEAR_QUEUE
mdefine_line|#define&t;M_CLEAR_QUEUE&t;(0x0e)
DECL|macro|M_INIT_REC
mdefine_line|#define&t;M_INIT_REC&t;(0x0f)
DECL|macro|M_REL_REC
mdefine_line|#define&t;M_REL_REC&t;(0x10)
DECL|macro|M_TERMINATE
mdefine_line|#define&t;M_TERMINATE&t;(0x11)
DECL|macro|M_SIMPLE_TAG
mdefine_line|#define&t;M_SIMPLE_TAG&t;(0x20)
DECL|macro|M_HEAD_TAG
mdefine_line|#define&t;M_HEAD_TAG&t;(0x21)
DECL|macro|M_ORDERED_TAG
mdefine_line|#define&t;M_ORDERED_TAG&t;(0x22)
DECL|macro|M_IGN_RESIDUE
mdefine_line|#define&t;M_IGN_RESIDUE&t;(0x23)
DECL|macro|M_IDENTIFY
mdefine_line|#define&t;M_IDENTIFY   &t;(0x80)
DECL|macro|M_X_MODIFY_DP
mdefine_line|#define&t;M_X_MODIFY_DP&t;(0x00)
DECL|macro|M_X_SYNC_REQ
mdefine_line|#define&t;M_X_SYNC_REQ&t;(0x01)
DECL|macro|M_X_WIDE_REQ
mdefine_line|#define&t;M_X_WIDE_REQ&t;(0x03)
DECL|macro|M_X_PPR_REQ
mdefine_line|#define&t;M_X_PPR_REQ&t;(0x04)
multiline_comment|/*&n;**&t;Status&n;*/
DECL|macro|S_GOOD
mdefine_line|#define&t;S_GOOD&t;&t;(0x00)
DECL|macro|S_CHECK_COND
mdefine_line|#define&t;S_CHECK_COND&t;(0x02)
DECL|macro|S_COND_MET
mdefine_line|#define&t;S_COND_MET&t;(0x04)
DECL|macro|S_BUSY
mdefine_line|#define&t;S_BUSY&t;&t;(0x08)
DECL|macro|S_INT
mdefine_line|#define&t;S_INT&t;&t;(0x10)
DECL|macro|S_INT_COND_MET
mdefine_line|#define&t;S_INT_COND_MET&t;(0x14)
DECL|macro|S_CONFLICT
mdefine_line|#define&t;S_CONFLICT&t;(0x18)
DECL|macro|S_TERMINATED
mdefine_line|#define&t;S_TERMINATED&t;(0x20)
DECL|macro|S_QUEUE_FULL
mdefine_line|#define&t;S_QUEUE_FULL&t;(0x28)
DECL|macro|S_ILLEGAL
mdefine_line|#define&t;S_ILLEGAL&t;(0xff)
DECL|macro|S_SENSE
mdefine_line|#define&t;S_SENSE&t;&t;(0x80)
multiline_comment|/*&n; * End of ncrreg from FreeBSD&n; */
macro_line|#endif /* !defined HOSTS_C */
macro_line|#endif /* defined SYM53C8XX_DEFS_H */
eof
