macro_line|#ifndef _NCR53C406A_H
DECL|macro|_NCR53C406A_H
mdefine_line|#define _NCR53C406A_H
multiline_comment|/*&n; *  NCR53c406a.h&n; * &n; *  Copyright (C) 1994 Normunds Saumanis (normunds@rx.tech.swh.lv)&n; *&n; *  This program is free software; you can redistribute it and/or modify it&n; *  under the terms of the GNU General Public License as published by the&n; *  Free Software Foundation; either version 2, or (at your option) any&n; *  later version.&n; *&n; *  This program is distributed in the hope that it will be useful, but&n; *  WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n; *  General Public License for more details.&n; *&n; */
macro_line|#ifndef NULL
DECL|macro|NULL
mdefine_line|#define NULL 0
macro_line|#endif
multiline_comment|/* NOTE:  scatter-gather support only works in PIO mode.&n; * Use SG_NONE if DMA mode is enabled!&n; */
DECL|macro|NCR53c406a
mdefine_line|#define NCR53c406a { &bslash;&n;     proc_name:         &quot;NCR53c406a&quot;&t;&t;/* proc_name */,        &bslash;&n;     name:              &quot;NCR53c406a&quot;&t;&t;/* name */,             &bslash;&n;     detect:            NCR53c406a_detect&t;/* detect */,           &bslash;&n;     info:              NCR53c406a_info&t;&t;/* info */,             &bslash;&n;     command:           NCR53c406a_command&t;/* command */,          &bslash;&n;     queuecommand:      NCR53c406a_queue&t;/* queuecommand */,     &bslash;&n;     abort:             NCR53c406a_abort&t;/* abort */,            &bslash;&n;     reset:             NCR53c406a_reset&t;/* reset */,            &bslash;&n;     bios_param:        NCR53c406a_biosparm&t;/* biosparm */,         &bslash;&n;     can_queue:         1&t;&t;&t;/* can_queue */,        &bslash;&n;     this_id:           7&t;&t;&t;/* SCSI ID of the chip */, &bslash;&n;     sg_tablesize:      32&t;&t;&t;/*SG_ALL*/ /*SG_NONE*/, &bslash;&n;     cmd_per_lun:       1&t;&t;&t;/* commands per lun */, &bslash;&n;     unchecked_isa_dma: 1&t;&t;&t;/* unchecked_isa_dma */, &bslash;&n;     use_clustering:    ENABLE_CLUSTERING                               &bslash;&n;}
r_int
id|NCR53c406a_detect
c_func
(paren
id|Scsi_Host_Template
op_star
)paren
suffix:semicolon
r_const
r_char
op_star
id|NCR53c406a_info
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_int
id|NCR53c406a_command
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_int
id|NCR53c406a_queue
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
id|NCR53c406a_abort
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_int
id|NCR53c406a_reset
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
id|NCR53c406a_biosparm
c_func
(paren
id|Disk
op_star
comma
id|kdev_t
comma
r_int
(braket
)braket
)paren
suffix:semicolon
macro_line|#endif /* _NCR53C406A_H */
multiline_comment|/*&n; * Overrides for Emacs so that we get a uniform tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-indent-level: 4&n; * c-brace-imaginary-offset: 0&n; * c-brace-offset: -4&n; * c-argdecl-indent: 4&n; * c-label-offset: -4&n; * c-continued-statement-offset: 4&n; * c-continued-brace-offset: 0&n; * indent-tabs-mode: nil&n; * tab-width: 8&n; * End:&n; */
eof
