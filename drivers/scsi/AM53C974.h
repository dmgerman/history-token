multiline_comment|/* AM53/79C974 (PCscsi) driver release 0.5&n;&n; * The architecture and much of the code of this device&n; * driver was originally developed by Drew Eckhardt for&n; * the NCR5380. The following copyrights apply:&n; *  For the architecture and all parts similar to the NCR5380:&n; *    Copyright 1993, Drew Eckhardt&n; *      Visionary Computing &n; *      (Unix and Linux consulting and custom programming)&n; *      drew@colorado.edu&n; *      +1 (303) 666-5836&n; *&n; *  The AM53C974_nobios_detect code was originally developed by&n; *   Robin Cutshaw (robin@xfree86.org) and is used here in a &n; *   modified form.&n; *&n; *  For the other parts:&n; *    Copyright 1994, D. Frieauff&n; *    EMail: fri@rsx42sun0.dofn.de&n; *    Phone: x49-7545-8-2256 , x49-7541-42305&n; */
multiline_comment|/*&n; * $Log: AM53C974.h,v $&n; */
macro_line|#ifndef AM53C974_H
DECL|macro|AM53C974_H
mdefine_line|#define AM53C974_H
macro_line|#include &lt;scsi/scsicam.h&gt;
DECL|struct|AM53C974_hostdata
r_struct
id|AM53C974_hostdata
(brace
DECL|member|in_reset
r_volatile
r_int
id|in_reset
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* flag, says bus reset pending */
DECL|member|aborted
r_volatile
r_int
id|aborted
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* flag, says aborted */
DECL|member|selecting
r_volatile
r_int
id|selecting
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* selection started, but not yet finished */
DECL|member|disconnecting
r_volatile
r_int
id|disconnecting
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* disconnection started, but not yet finished */
DECL|member|dma_busy
r_volatile
r_int
id|dma_busy
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* dma busy when service request for info transfer received */
DECL|member|msgout
r_volatile
r_int
r_char
id|msgout
(braket
l_int|10
)braket
suffix:semicolon
multiline_comment|/* message to output in MSGOUT_PHASE */
DECL|member|last_message
r_volatile
r_int
r_char
id|last_message
(braket
l_int|10
)braket
suffix:semicolon
multiline_comment|/* last message OUT */
DECL|member|issue_queue
r_volatile
id|Scsi_Cmnd
op_star
id|issue_queue
suffix:semicolon
multiline_comment|/* waiting to be issued */
DECL|member|disconnected_queue
r_volatile
id|Scsi_Cmnd
op_star
id|disconnected_queue
suffix:semicolon
multiline_comment|/* waiting for reconnect */
DECL|member|sel_cmd
r_volatile
id|Scsi_Cmnd
op_star
id|sel_cmd
suffix:semicolon
multiline_comment|/* command for selection */
DECL|member|connected
r_volatile
id|Scsi_Cmnd
op_star
id|connected
suffix:semicolon
multiline_comment|/* currently connected command */
DECL|member|busy
r_volatile
r_int
r_char
id|busy
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* index = target, bit = lun */
DECL|member|sync_per
r_int
r_char
id|sync_per
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* synchronous transfer period (in effect) */
DECL|member|sync_off
r_int
r_char
id|sync_off
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* synchronous offset (in effect) */
DECL|member|sync_neg
r_int
r_char
id|sync_neg
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* sync. negotiation performed (in effect) */
DECL|member|sync_en
r_int
r_char
id|sync_en
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* sync. negotiation performed (in effect) */
DECL|member|max_rate
r_int
r_char
id|max_rate
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* max. transfer rate (setup) */
DECL|member|max_offset
r_int
r_char
id|max_offset
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* max. sync. offset (setup), only valid if corresponding sync_en is nonzero */
)brace
suffix:semicolon
DECL|macro|AM53C974
mdefine_line|#define AM53C974 {&t;&t;&t;&t;  &bslash;&n;    proc_name:      &quot;am53c974&quot;,    &t;          &bslash;&n;    name:           &quot;AM53C974&quot;,        &t;&t;  &bslash;&n;    detect:         AM53C974_pci_detect,&t;  &bslash;&n;    release:        AM53C974_release,&t;&t;  &bslash;&n;    info:           AM53C974_info,     &t;&t;  &bslash;&n;    command:        AM53C974_command,  &t;&t;  &bslash;&n;    queuecommand:   AM53C974_queue_command,&t;  &bslash;&n;    abort:          AM53C974_abort,    &t;&t;  &bslash;&n;    reset:          AM53C974_reset,    &t;&t;  &bslash;&n;    bios_param:     scsicam_bios_param,&t;&t;  &bslash;&n;    can_queue:      12,                 &t;  &bslash;&n;    this_id:        -1,                           &bslash;&n;    sg_tablesize:   SG_ALL,            &t;&t;  &bslash;&n;    cmd_per_lun:    1,                 &t;&t;  &bslash;&n;    use_clustering: DISABLE_CLUSTERING &t;&t;  &bslash;&n;    }
r_static
r_int
id|AM53C974_pci_detect
c_func
(paren
id|Scsi_Host_Template
op_star
id|tpnt
)paren
suffix:semicolon
r_static
r_int
id|AM53C974_release
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|shp
)paren
suffix:semicolon
r_static
r_const
r_char
op_star
id|AM53C974_info
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_static
r_int
id|AM53C974_command
c_func
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
)paren
suffix:semicolon
r_static
r_int
id|AM53C974_queue_command
c_func
(paren
id|Scsi_Cmnd
op_star
id|cmd
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
r_static
r_int
id|AM53C974_abort
c_func
(paren
id|Scsi_Cmnd
op_star
id|cmd
)paren
suffix:semicolon
r_static
r_int
id|AM53C974_reset
c_func
(paren
id|Scsi_Cmnd
op_star
id|cmd
comma
r_int
r_int
)paren
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* AM53C974_H */
eof
