multiline_comment|/******************************************************************************&n;**  Device driver for the PCI-SCSI NCR538XX controller family.&n;**&n;**  Copyright (C) 1994  Wolfgang Stanglmeier&n;**&n;**  This program is free software; you can redistribute it and/or modify&n;**  it under the terms of the GNU General Public License as published by&n;**  the Free Software Foundation; either version 2 of the License, or&n;**  (at your option) any later version.&n;**&n;**  This program is distributed in the hope that it will be useful,&n;**  but WITHOUT ANY WARRANTY; without even the implied warranty of&n;**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;**  GNU General Public License for more details.&n;**&n;**  You should have received a copy of the GNU General Public License&n;**  along with this program; if not, write to the Free Software&n;**  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;**&n;**-----------------------------------------------------------------------------&n;**&n;**  This driver has been ported to Linux from the FreeBSD NCR53C8XX driver&n;**  and is currently maintained by&n;**&n;**          Gerard Roudier              &lt;groudier@club-internet.fr&gt;&n;**&n;**  Being given that this driver originates from the FreeBSD version, and&n;**  in order to keep synergy on both, any suggested enhancements and corrections&n;**  received on Linux are automatically a potential candidate for the FreeBSD &n;**  version.&n;**&n;**  The original driver has been written for 386bsd and FreeBSD by&n;**          Wolfgang Stanglmeier        &lt;wolf@cologne.de&gt;&n;**          Stefan Esser                &lt;se@mi.Uni-Koeln.de&gt;&n;**&n;**  And has been ported to NetBSD by&n;**          Charles M. Hannum           &lt;mycroft@gnu.ai.mit.edu&gt;&n;**&n;*******************************************************************************&n;*/
macro_line|#ifndef NCR53C8XX_H
DECL|macro|NCR53C8XX_H
mdefine_line|#define NCR53C8XX_H
macro_line|#include &quot;sym53c8xx_defs.h&quot;
multiline_comment|/*&n;**&t;Define Scsi_Host_Template parameters&n;**&n;**&t;Used by hosts.c and ncr53c8xx.c with module configuration.&n;*/
macro_line|#if (LINUX_VERSION_CODE &gt;= 0x020400) || defined(HOSTS_C) || defined(MODULE)
macro_line|#include &lt;scsi/scsicam.h&gt;
r_int
id|ncr53c8xx_abort
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_int
id|ncr53c8xx_detect
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
id|ncr53c8xx_info
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|host
)paren
suffix:semicolon
r_int
id|ncr53c8xx_queue_command
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
id|ncr53c8xx_reset
c_func
(paren
id|Scsi_Cmnd
op_star
comma
r_int
r_int
)paren
suffix:semicolon
macro_line|#ifdef MODULE
r_int
id|ncr53c8xx_release
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
macro_line|#else
DECL|macro|ncr53c8xx_release
mdefine_line|#define ncr53c8xx_release NULL
macro_line|#endif
macro_line|#if&t;LINUX_VERSION_CODE &gt;= LinuxVersionCode(2,1,75)
DECL|macro|NCR53C8XX
mdefine_line|#define NCR53C8XX {     name:           &quot;&quot;,&t;&t;&t;&bslash;&n;&t;&t;&t;detect:         ncr53c8xx_detect,&t;&bslash;&n;&t;&t;&t;release:        ncr53c8xx_release,&t;&bslash;&n;&t;&t;&t;info:           ncr53c8xx_info, &t;&bslash;&n;&t;&t;&t;queuecommand:   ncr53c8xx_queue_command,&bslash;&n;&t;&t;&t;abort:          ncr53c8xx_abort,&t;&bslash;&n;&t;&t;&t;reset:          ncr53c8xx_reset,&t;&bslash;&n;&t;&t;&t;bios_param:     scsicam_bios_param,&t;&bslash;&n;&t;&t;&t;can_queue:      SCSI_NCR_CAN_QUEUE,&t;&bslash;&n;&t;&t;&t;this_id:        7,&t;&t;&t;&bslash;&n;&t;&t;&t;sg_tablesize:   SCSI_NCR_SG_TABLESIZE,&t;&bslash;&n;&t;&t;&t;cmd_per_lun:    SCSI_NCR_CMD_PER_LUN,&t;&bslash;&n;&t;&t;&t;use_clustering: DISABLE_CLUSTERING} 
macro_line|#else
DECL|macro|NCR53C8XX
mdefine_line|#define NCR53C8XX {&t;NULL, NULL, NULL, NULL,&t;&t;&t;&t;&bslash;&n;&t;&t;&t;NULL,&t;&t;&t;ncr53c8xx_detect,&t;&bslash;&n;&t;&t;&t;ncr53c8xx_release,&t;ncr53c8xx_info,&t;NULL,&t;&bslash;&n;&t;&t;&t;ncr53c8xx_queue_command,ncr53c8xx_abort,&t;&bslash;&n;&t;&t;&t;ncr53c8xx_reset, NULL,&t;scsicam_bios_param,&t;&bslash;&n;&t;&t;&t;SCSI_NCR_CAN_QUEUE,&t;7,&t;&t;&t;&bslash;&n;&t;&t;&t;SCSI_NCR_SG_TABLESIZE,&t;SCSI_NCR_CMD_PER_LUN,&t;&bslash;&n;&t;&t;&t;0,&t;0,&t;DISABLE_CLUSTERING} 
macro_line|#endif /* LINUX_VERSION_CODE */
macro_line|#endif /* defined(HOSTS_C) || defined(MODULE) */ 
macro_line|#endif /* NCR53C8XX_H */
eof
