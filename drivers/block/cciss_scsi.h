multiline_comment|/*&n; *    Disk Array driver for Compaq SA53xx Controllers, SCSI Tape module&n; *    Copyright 2001 Compaq Computer Corporation&n; *&n; *    This program is free software; you can redistribute it and/or modify&n; *    it under the terms of the GNU General Public License as published by&n; *    the Free Software Foundation; either version 2 of the License, or&n; *    (at your option) any later version.&n; *&n; *    This program is distributed in the hope that it will be useful,&n; *    but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *    MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, GOOD TITLE or&n; *    NON INFRINGEMENT.  See the GNU General Public License for more details.&n; *&n; *    You should have received a copy of the GNU General Public License&n; *    along with this program; if not, write to the Free Software&n; *    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; *    Questions/Comments/Bugfixes to arrays@compaq.com&n; *&n; */
macro_line|#ifdef CONFIG_CISS_SCSI_TAPE
macro_line|#ifndef _CCISS_SCSI_H_
DECL|macro|_CCISS_SCSI_H_
mdefine_line|#define _CCISS_SCSI_H_
macro_line|#include &lt;scsi/scsicam.h&gt; /* possibly irrelevant, since we don&squot;t show disks */
singleline_comment|// the scsi id of the adapter...
DECL|macro|SELF_SCSI_ID
mdefine_line|#define SELF_SCSI_ID 15
singleline_comment|// 15 is somewhat arbitrary, since the scsi-2 bus
singleline_comment|// that&squot;s presented by the driver to the OS is
singleline_comment|// fabricated.  The &quot;real&quot; scsi-3 bus the 
singleline_comment|// hardware presents is fabricated too.
singleline_comment|// The actual, honest-to-goodness physical
singleline_comment|// bus that the devices are attached to is not 
singleline_comment|// addressible natively, and may in fact turn
singleline_comment|// out to be not scsi at all.
DECL|macro|SCSI_CCISS_CAN_QUEUE
mdefine_line|#define SCSI_CCISS_CAN_QUEUE 2
multiline_comment|/* this notation works fine for static initializations (as is the usual&n;   case for linux scsi drivers), but not so well for dynamic settings,&n;   so, if you change this, you also have to change cciss_unregister_scsi()&n;   in cciss_scsi.c  */
DECL|macro|CCISS_SCSI
mdefine_line|#define CCISS_SCSI {    &bslash;&n;&t;name:           &t;&quot;&quot;,&t;&t;&t;&t;&bslash;&n;&t;detect:         &t;cciss_scsi_detect,&t;&t;&bslash;&n;&t;release:        &t;cciss_scsi_release,&t;&t;&bslash;&n;&t;proc_info:           &t;cciss_scsi_proc_info,&t;&t;&bslash;&n;&t;queuecommand:   &t;cciss_scsi_queue_command,&t;&bslash;&n;&t;bios_param:     &t;scsicam_bios_param,&t;&t;&bslash;&n;&t;can_queue:      &t;SCSI_CCISS_CAN_QUEUE,&t;&t;&bslash;&n;&t;this_id:        &t;7,&t;&t;&t;&t;&bslash;&n;&t;sg_tablesize:   &t;MAXSGENTRIES, &t;&t;&t;&bslash;&n;&t;cmd_per_lun:&t;&t;1,&t;&t;&t;&t;&bslash;&n;&t;use_clustering:&t;&t;DISABLE_CLUSTERING,&bslash;&n;} 
multiline_comment|/* &n;&t;info:           &t;cciss_scsi_info,&t;&t;&bslash;&n;&n;Note, cmd_per_lun could give us some trouble, so I&squot;m setting it very low.&n;Likewise, SCSI_CCISS_CAN_QUEUE is set very conservatively.&n;&n;If the upper scsi layer tries to track how many commands we have &n;outstanding, it will be operating under the misapprehension that it is&n;the only one sending us requests.  We also have the block interface,&n;which is where most requests must surely come from, so the upper layer&squot;s&n;notion of how many requests we have outstanding will be wrong most or&n;all of the time. &n;&n;Note, the normal SCSI mid-layer error handling doesn&squot;t work well&n;for this driver because 1) it takes the io_request_lock before&n;calling error handlers and uses a local variable to store flags,&n;so the io_request_lock cannot be released and interrupts enabled&n;inside the error handlers, and, the error handlers cannot poll&n;for command completion because they might get commands from the&n;block half of the driver completing, and not know what to do&n;with them.  That&squot;s what we get for making a hybrid scsi/block&n;driver, I suppose.&n;&n;*/
DECL|struct|cciss_scsi_dev_t
r_struct
id|cciss_scsi_dev_t
(brace
DECL|member|devtype
r_int
id|devtype
suffix:semicolon
DECL|member|bus
DECL|member|target
DECL|member|lun
r_int
id|bus
comma
id|target
comma
id|lun
suffix:semicolon
multiline_comment|/* as presented to the OS */
DECL|member|scsi3addr
r_int
r_char
id|scsi3addr
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* as presented to the HW */
)brace
suffix:semicolon
DECL|struct|cciss_scsi_hba_t
r_struct
id|cciss_scsi_hba_t
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|ndevices
r_int
id|ndevices
suffix:semicolon
DECL|macro|CCISS_MAX_SCSI_DEVS_PER_HBA
mdefine_line|#define CCISS_MAX_SCSI_DEVS_PER_HBA 16
DECL|member|dev
r_struct
id|cciss_scsi_dev_t
id|dev
(braket
id|CCISS_MAX_SCSI_DEVS_PER_HBA
)braket
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* _CCISS_SCSI_H_ */
macro_line|#endif /* CONFIG_CISS_SCSI_TAPE */
eof
