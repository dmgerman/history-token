multiline_comment|/*&n; * Device driver for the SYMBIOS/LSILOGIC 53C8XX and 53C1010 family &n; * of PCI-SCSI IO processors.&n; *&n; * Copyright (C) 1999-2001  Gerard Roudier &lt;groudier@free.fr&gt;&n; *&n; * This driver is derived from the Linux sym53c8xx driver.&n; * Copyright (C) 1998-2000  Gerard Roudier&n; *&n; * The sym53c8xx driver is derived from the ncr53c8xx driver that had been &n; * a port of the FreeBSD ncr driver to Linux-1.2.13.&n; *&n; * The original ncr driver has been written for 386bsd and FreeBSD by&n; *         Wolfgang Stanglmeier        &lt;wolf@cologne.de&gt;&n; *         Stefan Esser                &lt;se@mi.Uni-Koeln.de&gt;&n; * Copyright (C) 1994  Wolfgang Stanglmeier&n; *&n; * Other major contributions:&n; *&n; * NVRAM detection and reading.&n; * Copyright (C) 1997 Richard Waltham &lt;dormouse@farsrobt.demon.co.uk&gt;&n; *&n; *-----------------------------------------------------------------------------&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions and the following disclaimer.&n; * 2. The name of the author may not be used to endorse or promote products&n; *    derived from this software without specific prior written permission.&n; *&n; * Where this Software is combined with software released under the terms of &n; * the GNU Public License (&quot;GPL&quot;) and the terms of the GPL would require the &n; * combined work to also be released under the terms of the GPL, the terms&n; * and conditions of this License will apply in addition to those of the&n; * GPL with the exception of any terms or conditions of this License that&n; * conflict with, or are expressly prohibited by, the GPL.&n; *&n; * THIS SOFTWARE IS PROVIDED BY THE AUTHORS AND CONTRIBUTORS ``AS IS&squot;&squot; AND&n; * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE&n; * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE&n; * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR&n; * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT&n; * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY&n; * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF&n; * SUCH DAMAGE.&n; */
macro_line|#ifndef SYM_CONF_H
DECL|macro|SYM_CONF_H
mdefine_line|#define SYM_CONF_H
macro_line|#include &quot;sym53c8xx.h&quot;
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
multiline_comment|/*&n; *  Support for Immediate Arbitration.&n; *  Not advised.&n; */
multiline_comment|/* #define SYM_CONF_IARB_SUPPORT */
multiline_comment|/*&n; *  Number of lists for the optimization of the IO timeout handling.&n; *  Not used under FreeBSD and Linux.&n; */
macro_line|#ifndef SYM_CONF_TIMEOUT_ORDER_MAX
DECL|macro|SYM_CONF_TIMEOUT_ORDER_MAX
mdefine_line|#define SYM_CONF_TIMEOUT_ORDER_MAX&t;(8)
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
macro_line|#endif /* SYM_CONF_H */
eof
