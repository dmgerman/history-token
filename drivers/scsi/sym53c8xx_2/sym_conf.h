multiline_comment|/*&n; * Device driver for the SYMBIOS/LSILOGIC 53C8XX and 53C1010 family &n; * of PCI-SCSI IO processors.&n; *&n; * Copyright (C) 1999-2001  Gerard Roudier &lt;groudier@free.fr&gt;&n; *&n; * This driver is derived from the Linux sym53c8xx driver.&n; * Copyright (C) 1998-2000  Gerard Roudier&n; *&n; * The sym53c8xx driver is derived from the ncr53c8xx driver that had been &n; * a port of the FreeBSD ncr driver to Linux-1.2.13.&n; *&n; * The original ncr driver has been written for 386bsd and FreeBSD by&n; *         Wolfgang Stanglmeier        &lt;wolf@cologne.de&gt;&n; *         Stefan Esser                &lt;se@mi.Uni-Koeln.de&gt;&n; * Copyright (C) 1994  Wolfgang Stanglmeier&n; *&n; * Other major contributions:&n; *&n; * NVRAM detection and reading.&n; * Copyright (C) 1997 Richard Waltham &lt;dormouse@farsrobt.demon.co.uk&gt;&n; *&n; *-----------------------------------------------------------------------------&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
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
