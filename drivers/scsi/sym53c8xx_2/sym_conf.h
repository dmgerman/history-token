multiline_comment|/*&n; * Device driver for the SYMBIOS/LSILOGIC 53C8XX and 53C1010 family &n; * of PCI-SCSI IO processors.&n; *&n; * Copyright (C) 1999-2001  Gerard Roudier &lt;groudier@free.fr&gt;&n; *&n; * This driver is derived from the Linux sym53c8xx driver.&n; * Copyright (C) 1998-2000  Gerard Roudier&n; *&n; * The sym53c8xx driver is derived from the ncr53c8xx driver that had been &n; * a port of the FreeBSD ncr driver to Linux-1.2.13.&n; *&n; * The original ncr driver has been written for 386bsd and FreeBSD by&n; *         Wolfgang Stanglmeier        &lt;wolf@cologne.de&gt;&n; *         Stefan Esser                &lt;se@mi.Uni-Koeln.de&gt;&n; * Copyright (C) 1994  Wolfgang Stanglmeier&n; *&n; * Other major contributions:&n; *&n; * NVRAM detection and reading.&n; * Copyright (C) 1997 Richard Waltham &lt;dormouse@farsrobt.demon.co.uk&gt;&n; *&n; *-----------------------------------------------------------------------------&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions and the following disclaimer.&n; * 2. The name of the author may not be used to endorse or promote products&n; *    derived from this software without specific prior written permission.&n; *&n; * Where this Software is combined with software released under the terms of &n; * the GNU Public License (&quot;GPL&quot;) and the terms of the GPL would require the &n; * combined work to also be released under the terms of the GPL, the terms&n; * and conditions of this License will apply in addition to those of the&n; * GPL with the exception of any terms or conditions of this License that&n; * conflict with, or are expressly prohibited by, the GPL.&n; *&n; * THIS SOFTWARE IS PROVIDED BY THE AUTHORS AND CONTRIBUTORS ``AS IS&squot;&squot; AND&n; * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE&n; * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE&n; * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR&n; * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT&n; * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY&n; * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF&n; * SUCH DAMAGE.&n; */
macro_line|#ifndef SYM_CONF_H
DECL|macro|SYM_CONF_H
mdefine_line|#define SYM_CONF_H
multiline_comment|/*-------------------------------------------------------------------&n; *  Static configuration.&n; *-------------------------------------------------------------------&n; */
multiline_comment|/*&n; *  Also support early NCR 810, 815 and 825 chips.&n; */
macro_line|#ifndef SYM_CONF_GENERIC_SUPPORT
DECL|macro|SYM_CONF_GENERIC_SUPPORT
mdefine_line|#define SYM_CONF_GENERIC_SUPPORT&t;(1)
macro_line|#endif
multiline_comment|/*&n; *  Use Normal IO instead of MMIO.&n; */
multiline_comment|/* #define SYM_CONF_IOMAPPED */
multiline_comment|/*&n; *  Max tags for a device (logical unit)&n; * &t;We use a power of 2, (7) means 2&lt;&lt;7=128&n; *  Maximum is 8 -&gt; 256 tags&n; */
macro_line|#ifndef SYM_CONF_MAX_TAG_ORDER
DECL|macro|SYM_CONF_MAX_TAG_ORDER
mdefine_line|#define SYM_CONF_MAX_TAG_ORDER&t;(6)
macro_line|#endif
multiline_comment|/*&n; *  Max number of scatter/gather entries for en IO.&n; *  Each entry costs 8 bytes in the internal CCB data structure.&n; */
macro_line|#ifndef SYM_CONF_MAX_SG
DECL|macro|SYM_CONF_MAX_SG
mdefine_line|#define SYM_CONF_MAX_SG&t;&t;(33)
macro_line|#endif
multiline_comment|/*&n; *  Max number of targets.&n; *  Maximum is 16 and you are advised not to change this value.&n; */
macro_line|#ifndef SYM_CONF_MAX_TARGET
DECL|macro|SYM_CONF_MAX_TARGET
mdefine_line|#define SYM_CONF_MAX_TARGET&t;(16)
macro_line|#endif
multiline_comment|/*&n; *  Max number of logical units.&n; *  SPI-2 allows up to 64 logical units, but in real life, target&n; *  that implements more that 7 logical units are pretty rare.&n; *  Anyway, the cost of accepting up to 64 logical unit is low in &n; *  this driver, thus going with the maximum is acceptable.&n; */
macro_line|#ifndef SYM_CONF_MAX_LUN
DECL|macro|SYM_CONF_MAX_LUN
mdefine_line|#define SYM_CONF_MAX_LUN&t;(64)
macro_line|#endif
multiline_comment|/*&n; *  Max number of IO control blocks queued to the controller.&n; *  Each entry needs 8 bytes and the queues are allocated contiguously.&n; *  Since we donnot want to allocate more than a page, the theorical &n; *  maximum is PAGE_SIZE/8. For safety, we announce a bit less to the &n; *  access method. :)&n; *  When not supplied, as it is suggested, the driver compute some &n; *  good value for this parameter.&n; */
multiline_comment|/* #define SYM_CONF_MAX_START&t;(PAGE_SIZE/8 - 16) */
multiline_comment|/*&n; *  Support for NVRAM.&n; */
macro_line|#ifndef SYM_CONF_NVRAM_SUPPORT
DECL|macro|SYM_CONF_NVRAM_SUPPORT
mdefine_line|#define SYM_CONF_NVRAM_SUPPORT&t;&t;(1)
macro_line|#endif
multiline_comment|/*&n; *  Support for Immediate Arbitration.&n; *  Not advised.&n; */
multiline_comment|/* #define SYM_CONF_IARB_SUPPORT */
multiline_comment|/*&n; *  Support for some PCI fix-ups (or assumed so).&n; */
DECL|macro|SYM_CONF_PCI_FIX_UP
mdefine_line|#define SYM_CONF_PCI_FIX_UP
multiline_comment|/*&n; *  Number of lists for the optimization of the IO timeout handling.&n; *  Not used under FreeBSD and Linux.&n; */
macro_line|#ifndef SYM_CONF_TIMEOUT_ORDER_MAX
DECL|macro|SYM_CONF_TIMEOUT_ORDER_MAX
mdefine_line|#define SYM_CONF_TIMEOUT_ORDER_MAX&t;(8)
macro_line|#endif
multiline_comment|/*&n; *  How the driver handles DMA addressing of user data.&n; *  0 :&t;32 bit addressing&n; *  1 :&t;40 bit addressing&n; *  2 :&t;64 bit addressing using segment registers&n; */
macro_line|#ifndef SYM_CONF_DMA_ADDRESSING_MODE
DECL|macro|SYM_CONF_DMA_ADDRESSING_MODE
mdefine_line|#define SYM_CONF_DMA_ADDRESSING_MODE&t;(0)
macro_line|#endif
multiline_comment|/*-------------------------------------------------------------------&n; *  Configuration that could be dynamic if it was possible &n; *  to pass arguments to the driver.&n; *-------------------------------------------------------------------&n; */
multiline_comment|/*&n; *  HOST default scsi id.&n; */
macro_line|#ifndef SYM_SETUP_HOST_ID
DECL|macro|SYM_SETUP_HOST_ID
mdefine_line|#define SYM_SETUP_HOST_ID&t;7
macro_line|#endif
multiline_comment|/*&n; *  Max synchronous transfers.&n; */
macro_line|#ifndef SYM_SETUP_MIN_SYNC
DECL|macro|SYM_SETUP_MIN_SYNC
mdefine_line|#define SYM_SETUP_MIN_SYNC&t;(9)
macro_line|#endif
multiline_comment|/*&n; *  Max wide order.&n; */
macro_line|#ifndef SYM_SETUP_MAX_WIDE
DECL|macro|SYM_SETUP_MAX_WIDE
mdefine_line|#define SYM_SETUP_MAX_WIDE&t;(1)
macro_line|#endif
multiline_comment|/*&n; *  Max SCSI offset.&n; */
macro_line|#ifndef SYM_SETUP_MAX_OFFS
DECL|macro|SYM_SETUP_MAX_OFFS
mdefine_line|#define SYM_SETUP_MAX_OFFS&t;(63)
macro_line|#endif
multiline_comment|/*&n; *  Default number of tags.&n; */
macro_line|#ifndef SYM_SETUP_MAX_TAG
DECL|macro|SYM_SETUP_MAX_TAG
mdefine_line|#define SYM_SETUP_MAX_TAG&t;(1&lt;&lt;SYM_CONF_MAX_TAG_ORDER)
macro_line|#endif
multiline_comment|/*&n; *  SYMBIOS NVRAM format support.&n; */
macro_line|#ifndef SYM_SETUP_SYMBIOS_NVRAM
DECL|macro|SYM_SETUP_SYMBIOS_NVRAM
mdefine_line|#define SYM_SETUP_SYMBIOS_NVRAM&t;(1)
macro_line|#endif
multiline_comment|/*&n; *  TEKRAM NVRAM format support.&n; */
macro_line|#ifndef SYM_SETUP_TEKRAM_NVRAM
DECL|macro|SYM_SETUP_TEKRAM_NVRAM
mdefine_line|#define SYM_SETUP_TEKRAM_NVRAM&t;(1)
macro_line|#endif
multiline_comment|/*&n; *  PCI parity checking.&n; *  It should not be an option, but some poor or broken &n; *  PCI-HOST bridges have been reported to make problems &n; *  when this feature is enabled.&n; *  Setting this option to 0 tells the driver not to &n; *  enable the checking against PCI parity.&n; */
macro_line|#ifndef SYM_SETUP_PCI_PARITY
DECL|macro|SYM_SETUP_PCI_PARITY
mdefine_line|#define SYM_SETUP_PCI_PARITY&t;(2)
macro_line|#endif
multiline_comment|/*&n; *  SCSI parity checking.&n; */
macro_line|#ifndef SYM_SETUP_SCSI_PARITY
DECL|macro|SYM_SETUP_SCSI_PARITY
mdefine_line|#define SYM_SETUP_SCSI_PARITY&t;(1)
macro_line|#endif
multiline_comment|/*&n; *  SCSI activity LED.&n; */
macro_line|#ifndef SYM_SETUP_SCSI_LED
DECL|macro|SYM_SETUP_SCSI_LED
mdefine_line|#define SYM_SETUP_SCSI_LED&t;(0)
macro_line|#endif
multiline_comment|/*&n; *  SCSI High Voltage Differential support.&n; *&n; *  HVD/LVD/SE capable controllers (895, 895A, 896, 1010) &n; *  report the actual SCSI BUS mode from the STEST4 IO &n; *  register.&n; *&n; *  But for HVD/SE only capable chips (825a, 875, 885), &n; *  the driver uses some heuristic to probe against HVD. &n; *  Normally, the chip senses the DIFFSENS signal and &n; *  should switch its BUS tranceivers to high impedance &n; *  in situation of the driver having been wrong about &n; *  the actual BUS mode. May-be, the BUS mode probing of &n; *  the driver is safe, but, given that it may be partially &n; *  based on some previous IO register settings, it &n; *  cannot be stated so. Thus, decision has been taken &n; *  to require a user option to be set for the DIFF probing &n; *  to be applied for the 825a, 875 and 885 chips.&n; *  &n; *  This setup option works as follows:&n; *&n; *    0  -&gt;  HVD only supported for 895, 895A, 896, 1010.&n; *    1  -&gt;  HVD probed  for 825A, 875, 885.&n; *    2  -&gt;  HVD assumed for 825A, 875, 885 (not advised).&n; */
macro_line|#ifndef SYM_SETUP_SCSI_DIFF
DECL|macro|SYM_SETUP_SCSI_DIFF
mdefine_line|#define SYM_SETUP_SCSI_DIFF&t;(0)
macro_line|#endif
multiline_comment|/*&n; *  IRQ mode.&n; */
macro_line|#ifndef SYM_SETUP_IRQ_MODE
DECL|macro|SYM_SETUP_IRQ_MODE
mdefine_line|#define SYM_SETUP_IRQ_MODE&t;(0)
macro_line|#endif
multiline_comment|/*&n; *  Check SCSI BUS signal on reset.&n; */
macro_line|#ifndef SYM_SETUP_SCSI_BUS_CHECK
DECL|macro|SYM_SETUP_SCSI_BUS_CHECK
mdefine_line|#define SYM_SETUP_SCSI_BUS_CHECK (1)
macro_line|#endif
multiline_comment|/*&n; *  Max burst for PCI (1&lt;&lt;value)&n; *  7 means: (1&lt;&lt;7) = 128 DWORDS.&n; */
macro_line|#ifndef SYM_SETUP_BURST_ORDER
DECL|macro|SYM_SETUP_BURST_ORDER
mdefine_line|#define SYM_SETUP_BURST_ORDER&t;(7)
macro_line|#endif
multiline_comment|/*&n; *  Only relevant if IARB support configured.&n; *  - Max number of successive settings of IARB hints.&n; *  - Set IARB on arbitration lost.&n; */
DECL|macro|SYM_CONF_IARB_MAX
mdefine_line|#define SYM_CONF_IARB_MAX 3
DECL|macro|SYM_CONF_SET_IARB_ON_ARB_LOST
mdefine_line|#define SYM_CONF_SET_IARB_ON_ARB_LOST 1
multiline_comment|/*&n; *  Returning wrong residuals may make problems.&n; *  When zero, this define tells the driver to &n; *  always return 0 as transfer residual.&n; *  Btw, all my testings of residuals have succeeded.&n; */
DECL|macro|SYM_SETUP_RESIDUAL_SUPPORT
mdefine_line|#define SYM_SETUP_RESIDUAL_SUPPORT 1
multiline_comment|/*&n; *  Supported maximum number of LUNs to announce to &n; *  the access method.&n; *  The driver supports up to 64 LUNs per target as &n; *  required by SPI-2/SPI-3. However some SCSI devices  &n; *  designed prior to these specifications or not being  &n; *  conformant may be highly confused when they are &n; *  asked about a LUN &gt; 7.&n; */
macro_line|#ifndef SYM_SETUP_MAX_LUN
DECL|macro|SYM_SETUP_MAX_LUN
mdefine_line|#define SYM_SETUP_MAX_LUN&t;(8)
macro_line|#endif
multiline_comment|/*&n; *  Bits indicating what kind of fix-ups we want.&n; *&n; *  Bit 0 (1) : cache line size configuration register.&n; *  Bit 1 (2) : MWI bit in command register.&n; *  Bit 2 (4) : latency timer if seems too low.&n; */
macro_line|#ifndef SYM_SETUP_PCI_FIX_UP
DECL|macro|SYM_SETUP_PCI_FIX_UP
mdefine_line|#define SYM_SETUP_PCI_FIX_UP (3)
macro_line|#endif
macro_line|#endif /* SYM_CONF_H */
eof
