multiline_comment|/*&n; * Adaptec AIC7xxx device driver host template for Linux.&n; *&n; * Copyright (c) 2000-2001 Adaptec Inc.&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. Redistributions in binary form must reproduce at minimum a disclaimer&n; *    substantially similar to the &quot;NO WARRANTY&quot; disclaimer below&n; *    (&quot;Disclaimer&quot;) and any redistribution must be conditioned upon&n; *    including a substantially similar Disclaimer requirement for further&n; *    binary redistribution.&n; * 3. Neither the names of the above-listed copyright holders nor the names&n; *    of any contributors may be used to endorse or promote products derived&n; *    from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU General Public License (&quot;GPL&quot;) version 2 as published by the Free&n; * Software Foundation.&n; *&n; * NO WARRANTY&n; * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS&n; * &quot;AS IS&quot; AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT&n; * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR&n; * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT&n; * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,&n; * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING&n; * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE&n; * POSSIBILITY OF SUCH DAMAGES.&n; *&n; * $Id: //depot/aic7xxx/linux/drivers/scsi/aic7xxx/aic7xxx_linux_host.h#5 $&n; */
macro_line|#ifndef _AIC7XXX_LINUX_HOST_H_
DECL|macro|_AIC7XXX_LINUX_HOST_H_
mdefine_line|#define _AIC7XXX_LINUX_HOST_H_
r_int
id|ahc_linux_proc_info
c_func
(paren
r_char
op_star
comma
r_char
op_star
op_star
comma
id|off_t
comma
r_int
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_int
id|ahc_linux_queue
c_func
(paren
id|Scsi_Cmnd
op_star
comma
r_void
(paren
op_star
)paren
(paren
id|Scsi_Cmnd
op_star
)paren
)paren
suffix:semicolon
r_int
id|ahc_linux_detect
c_func
(paren
id|Scsi_Host_Template
op_star
)paren
suffix:semicolon
r_int
id|ahc_linux_release
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_const
r_char
op_star
id|ahc_linux_info
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_int
id|ahc_linux_biosparam
c_func
(paren
id|Disk
op_star
comma
r_struct
id|block_device
op_star
comma
r_int
(braket
)braket
)paren
suffix:semicolon
r_int
id|ahc_linux_bus_reset
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_int
id|ahc_linux_dev_reset
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_int
id|ahc_linux_abort
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
macro_line|#if defined(__i386__)
DECL|macro|AIC7XXX_BIOSPARAM
macro_line|#  define AIC7XXX_BIOSPARAM ahc_linux_biosparam
macro_line|#else
DECL|macro|AIC7XXX_BIOSPARAM
macro_line|#  define AIC7XXX_BIOSPARAM NULL
macro_line|#endif
multiline_comment|/*&n; * Scsi_Host_Template (see hosts.h) for AIC-7xxx - some fields&n; * to do with card config are filled in after the card is detected.&n; */
DECL|macro|AIC7XXX
mdefine_line|#define AIC7XXX&t;{&t;&t;&t;&t;&t;&t;&bslash;&n;&t;next: NULL,&t;&t;&t;&t;&t;&t;&bslash;&n;&t;module: NULL,&t;&t;&t;&t;&t;&t;&bslash;&n;&t;proc_dir: NULL,&t;&t;&t;&t;&t;&t;&bslash;&n;&t;proc_info: ahc_linux_proc_info,&t;&t;&t;&t;&bslash;&n;&t;name: NULL,&t;&t;&t;&t;&t;&t;&bslash;&n;&t;detect: ahc_linux_detect,&t;&t;&t;&t;&bslash;&n;&t;release: ahc_linux_release,&t;&t;&t;&t;&bslash;&n;&t;info: ahc_linux_info,&t;&t;&t;&t;&t;&bslash;&n;&t;command: NULL,&t;&t;&t;&t;&t;&t;&bslash;&n;&t;queuecommand: ahc_linux_queue,&t;&t;&t;&t;&bslash;&n;&t;eh_strategy_handler: NULL,&t;&t;&t;&t;&bslash;&n;&t;eh_abort_handler: ahc_linux_abort,&t;&t;&t;&bslash;&n;&t;eh_device_reset_handler: ahc_linux_dev_reset,&t;&t;&bslash;&n;&t;eh_bus_reset_handler: ahc_linux_bus_reset,&t;&t;&bslash;&n;&t;eh_host_reset_handler: NULL,&t;&t;&t;&t;&bslash;&n;&t;abort: NULL,&t;&t;&t;&t;&t;&t;&bslash;&n;&t;reset: NULL,&t;&t;&t;&t;&t;&t;&bslash;&n;&t;slave_attach: ahc_linux_slave_attach,&t;&t;&t;&bslash;&n;&t;bios_param: AIC7XXX_BIOSPARAM,&t;&t;&t;&t;&bslash;&n;&t;can_queue: 253,&t;&t;/* max simultaneous cmds      */&bslash;&n;&t;this_id: -1,&t;&t;/* scsi id of host adapter    */&bslash;&n;&t;sg_tablesize: 0,&t;/* max scatter-gather cmds    */&bslash;&n;&t;cmd_per_lun: 2,&t;&t;/* cmds per lun&t;&t;      */&bslash;&n;&t;present: 0,&t;&t;/* number of 7xxx&squot;s present   */&bslash;&n;&t;unchecked_isa_dma: 0,&t;/* no memory DMA restrictions */&bslash;&n;&t;use_clustering: ENABLE_CLUSTERING,&t;&t;&t;&bslash;&n;&t;highmem_io: 1&t;&t;&t;&t;&t;&t;&bslash;&n;}
macro_line|#endif /* _AIC7XXX_LINUX_HOST_H_ */
eof
