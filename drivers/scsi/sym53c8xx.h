multiline_comment|/******************************************************************************&n;**  High Performance device driver for the Symbios 53C896 controller.&n;**&n;**  Copyright (C) 1998-2001  Gerard Roudier &lt;groudier@free.fr&gt;&n;**&n;**  This driver also supports all the Symbios 53C8XX controller family, &n;**  except 53C810 revisions &lt; 16, 53C825 revisions &lt; 16 and all &n;**  revisions of 53C815 controllers.&n;**&n;**  This driver is based on the Linux port of the FreeBSD ncr driver.&n;** &n;**  Copyright (C) 1994  Wolfgang Stanglmeier&n;**  &n;**-----------------------------------------------------------------------------&n;**  &n;**  This program is free software; you can redistribute it and/or modify&n;**  it under the terms of the GNU General Public License as published by&n;**  the Free Software Foundation; either version 2 of the License, or&n;**  (at your option) any later version.&n;**&n;**  This program is distributed in the hope that it will be useful,&n;**  but WITHOUT ANY WARRANTY; without even the implied warranty of&n;**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;**  GNU General Public License for more details.&n;**&n;**  You should have received a copy of the GNU General Public License&n;**  along with this program; if not, write to the Free Software&n;**  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;**&n;**-----------------------------------------------------------------------------&n;**&n;**  The Linux port of the FreeBSD ncr driver has been achieved in &n;**  november 1995 by:&n;**&n;**          Gerard Roudier              &lt;groudier@free.fr&gt;&n;**&n;**  Being given that this driver originates from the FreeBSD version, and&n;**  in order to keep synergy on both, any suggested enhancements and corrections&n;**  received on Linux are automatically a potential candidate for the FreeBSD &n;**  version.&n;**&n;**  The original driver has been written for 386bsd and FreeBSD by&n;**          Wolfgang Stanglmeier        &lt;wolf@cologne.de&gt;&n;**          Stefan Esser                &lt;se@mi.Uni-Koeln.de&gt;&n;**&n;**-----------------------------------------------------------------------------&n;**&n;**  Major contributions:&n;**  --------------------&n;**&n;**  NVRAM detection and reading.&n;**    Copyright (C) 1997 Richard Waltham &lt;dormouse@farsrobt.demon.co.uk&gt;&n;**&n;*******************************************************************************&n;*/
macro_line|#ifndef SYM53C8XX_H
DECL|macro|SYM53C8XX_H
mdefine_line|#define SYM53C8XX_H
macro_line|#include &quot;sym53c8xx_defs.h&quot;
multiline_comment|/*&n;**&t;Define Scsi_Host_Template parameters&n;**&n;**&t;Used by hosts.c and sym53c8xx.c with module configuration.&n;*/
macro_line|#if (LINUX_VERSION_CODE &gt;= 0x020400) || defined(HOSTS_C) || defined(MODULE)
macro_line|#include &lt;scsi/scsicam.h&gt;
r_int
id|sym53c8xx_abort
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_int
id|sym53c8xx_detect
c_func
(paren
id|Scsi_Host_Template
op_star
id|tpnt
)paren
suffix:semicolon
r_const
r_char
op_star
id|sym53c8xx_info
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|host
)paren
suffix:semicolon
r_int
id|sym53c8xx_queue_command
c_func
(paren
id|Scsi_Cmnd
op_star
comma
r_void
(paren
op_star
id|done
)paren
(paren
id|Scsi_Cmnd
op_star
)paren
)paren
suffix:semicolon
r_int
id|sym53c8xx_reset
c_func
(paren
id|Scsi_Cmnd
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_int
id|sym53c8xx_slave_configure
c_func
(paren
id|Scsi_Device
op_star
)paren
suffix:semicolon
r_int
id|sym53c8xx_release
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
macro_line|#endif /* defined(HOSTS_C) || defined(MODULE) */ 
macro_line|#endif /* SYM53C8XX_H */
eof
