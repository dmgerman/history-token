macro_line|#ifndef _SCSI_PRIV_H
DECL|macro|_SCSI_PRIV_H
mdefine_line|#define _SCSI_PRIV_H
multiline_comment|/*&n; * These are the values that the owner field can take.&n; * They are used as an indication of who the command belongs to.&n; */
DECL|macro|SCSI_OWNER_HIGHLEVEL
mdefine_line|#define SCSI_OWNER_HIGHLEVEL      0x100
DECL|macro|SCSI_OWNER_MIDLEVEL
mdefine_line|#define SCSI_OWNER_MIDLEVEL       0x101
DECL|macro|SCSI_OWNER_LOWLEVEL
mdefine_line|#define SCSI_OWNER_LOWLEVEL       0x102
DECL|macro|SCSI_OWNER_ERROR_HANDLER
mdefine_line|#define SCSI_OWNER_ERROR_HANDLER  0x103
DECL|macro|SCSI_OWNER_BH_HANDLER
mdefine_line|#define SCSI_OWNER_BH_HANDLER     0x104
DECL|macro|SCSI_OWNER_NOBODY
mdefine_line|#define SCSI_OWNER_NOBODY         0x105
multiline_comment|/*&n; * Magic values for certain scsi structs. Shouldn&squot;t ever be used.&n; */
DECL|macro|SCSI_CMND_MAGIC
mdefine_line|#define SCSI_CMND_MAGIC&t;&t;0xE25C23A5
DECL|macro|SCSI_REQ_MAGIC
mdefine_line|#define SCSI_REQ_MAGIC&t;&t;0x75F6D354
multiline_comment|/*&n; *  Flag bit for the internal_timeout array&n; */
DECL|macro|NORMAL_TIMEOUT
mdefine_line|#define NORMAL_TIMEOUT&t;&t;0
multiline_comment|/*&n; * Scsi Error Handler Flags&n; */
DECL|macro|scsi_eh_eflags_chk
mdefine_line|#define scsi_eh_eflags_chk(scp, flags) &bslash;&n;&t;((scp)-&gt;eh_eflags &amp; (flags))
DECL|macro|scsi_eh_eflags_set
mdefine_line|#define scsi_eh_eflags_set(scp, flags) &bslash;&n;&t;do { (scp)-&gt;eh_eflags |= (flags); } while(0)
DECL|macro|scsi_eh_eflags_clr
mdefine_line|#define scsi_eh_eflags_clr(scp, flags) &bslash;&n;&t;do { (scp)-&gt;eh_eflags &amp;= ~(flags); } while(0)
DECL|macro|scsi_eh_eflags_clr_all
mdefine_line|#define scsi_eh_eflags_clr_all(scp) &bslash;&n;&t;(scp-&gt;eh_eflags = 0)
DECL|macro|SCSI_EH_CANCEL_CMD
mdefine_line|#define SCSI_EH_CANCEL_CMD&t;0x0001&t;/* Cancel this cmd */
DECL|macro|SCSI_EH_REC_TIMEOUT
mdefine_line|#define SCSI_EH_REC_TIMEOUT&t;0x0002&t;/* EH retry timed out */
DECL|macro|SCSI_SENSE_VALID
mdefine_line|#define SCSI_SENSE_VALID(scmd) &bslash;&n;&t;(((scmd)-&gt;sense_buffer[0] &amp; 0x70) == 0x70)
multiline_comment|/*&n; * scsi_target: representation of a scsi target, for now, this is only&n; * used for single_lun devices. If no one has active IO to the target,&n; * starget_sdev_user is NULL, else it points to the active sdev.&n; */
DECL|struct|scsi_target
r_struct
id|scsi_target
(brace
DECL|member|starget_sdev_user
r_struct
id|scsi_device
op_star
id|starget_sdev_user
suffix:semicolon
DECL|member|starget_refcnt
r_int
r_int
id|starget_refcnt
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* hosts.c */
r_extern
r_void
id|scsi_host_busy_inc
c_func
(paren
r_struct
id|Scsi_Host
op_star
comma
id|Scsi_Device
op_star
)paren
suffix:semicolon
r_extern
r_void
id|scsi_host_busy_dec_and_test
c_func
(paren
r_struct
id|Scsi_Host
op_star
comma
id|Scsi_Device
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|Scsi_Host
op_star
id|scsi_host_get_next
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_extern
r_void
id|scsi_host_init
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* scsi.c */
r_extern
r_int
id|scsi_dispatch_cmd
c_func
(paren
r_struct
id|scsi_cmnd
op_star
id|cmd
)paren
suffix:semicolon
r_extern
r_int
id|scsi_setup_command_freelist
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|shost
)paren
suffix:semicolon
r_extern
r_void
id|scsi_destroy_command_freelist
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|shost
)paren
suffix:semicolon
r_extern
r_void
id|scsi_done
c_func
(paren
r_struct
id|scsi_cmnd
op_star
id|cmd
)paren
suffix:semicolon
r_extern
r_void
id|scsi_finish_command
c_func
(paren
r_struct
id|scsi_cmnd
op_star
id|cmd
)paren
suffix:semicolon
r_extern
r_int
id|scsi_retry_command
c_func
(paren
r_struct
id|scsi_cmnd
op_star
id|cmd
)paren
suffix:semicolon
r_extern
r_int
id|scsi_attach_device
c_func
(paren
r_struct
id|scsi_device
op_star
id|sdev
)paren
suffix:semicolon
r_extern
r_void
id|scsi_detach_device
c_func
(paren
r_struct
id|scsi_device
op_star
id|sdev
)paren
suffix:semicolon
r_extern
r_void
id|scsi_rescan_device
c_func
(paren
r_struct
id|scsi_device
op_star
id|sdev
)paren
suffix:semicolon
r_extern
r_int
id|scsi_get_device_flags
c_func
(paren
r_int
r_char
op_star
id|vendor
comma
r_int
r_char
op_star
id|model
)paren
suffix:semicolon
r_extern
r_int
id|scsi_insert_special_req
c_func
(paren
r_struct
id|scsi_request
op_star
id|sreq
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|scsi_init_cmd_from_req
c_func
(paren
r_struct
id|scsi_cmnd
op_star
id|cmd
comma
r_struct
id|scsi_request
op_star
id|sreq
)paren
suffix:semicolon
multiline_comment|/* scsi_error.c */
r_extern
r_void
id|scsi_times_out
c_func
(paren
r_struct
id|scsi_cmnd
op_star
id|cmd
)paren
suffix:semicolon
r_extern
r_void
id|scsi_error_handler
c_func
(paren
r_void
op_star
id|host
)paren
suffix:semicolon
r_extern
r_int
id|scsi_decide_disposition
c_func
(paren
r_struct
id|scsi_cmnd
op_star
id|cmd
)paren
suffix:semicolon
r_extern
r_int
id|scsi_eh_scmd_add
c_func
(paren
r_struct
id|scsi_cmnd
op_star
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* scsi_lib.c */
r_extern
r_int
id|scsi_maybe_unblock_host
c_func
(paren
r_struct
id|scsi_device
op_star
id|sdev
)paren
suffix:semicolon
r_extern
r_void
id|scsi_setup_cmd_retry
c_func
(paren
r_struct
id|scsi_cmnd
op_star
id|cmd
)paren
suffix:semicolon
r_extern
r_int
id|scsi_queue_insert
c_func
(paren
r_struct
id|scsi_cmnd
op_star
id|cmd
comma
r_int
id|reason
)paren
suffix:semicolon
r_extern
r_void
id|scsi_queue_next_request
c_func
(paren
r_struct
id|request_queue
op_star
id|q
comma
r_struct
id|scsi_cmnd
op_star
id|cmd
)paren
suffix:semicolon
r_extern
r_struct
id|request_queue
op_star
id|scsi_alloc_queue
c_func
(paren
r_struct
id|scsi_device
op_star
id|sdev
)paren
suffix:semicolon
r_extern
r_void
id|scsi_free_queue
c_func
(paren
r_struct
id|request_queue
op_star
id|q
)paren
suffix:semicolon
r_extern
r_int
id|scsi_init_queue
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|scsi_exit_queue
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* scsi_proc.c */
macro_line|#ifdef CONFIG_PROC_FS
r_extern
r_void
id|scsi_proc_host_add
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_extern
r_void
id|scsi_proc_host_rm
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_extern
r_int
id|scsi_init_procfs
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|scsi_exit_procfs
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#else
DECL|macro|scsi_proc_host_add
macro_line|# define scsi_proc_host_add(shost)&t;do { } while (0)
DECL|macro|scsi_proc_host_rm
macro_line|# define scsi_proc_host_rm(shost)&t;do { } while (0)
DECL|macro|scsi_init_procfs
macro_line|# define scsi_init_procfs()&t;&t;(0)
DECL|macro|scsi_exit_procfs
macro_line|# define scsi_exit_procfs&t;&t;do { } while (0)
macro_line|#endif /* CONFIG_PROC_FS */
multiline_comment|/* scsi_scan.c */
r_extern
r_void
id|scsi_scan_host
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|shost
)paren
suffix:semicolon
r_extern
r_void
id|scsi_forget_host
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|shost
)paren
suffix:semicolon
multiline_comment|/* scsi_sysfs.c */
r_extern
r_int
id|scsi_device_register
c_func
(paren
r_struct
id|scsi_device
op_star
)paren
suffix:semicolon
r_extern
r_void
id|scsi_device_unregister
c_func
(paren
r_struct
id|scsi_device
op_star
)paren
suffix:semicolon
r_extern
r_int
id|scsi_upper_driver_register
c_func
(paren
r_struct
id|Scsi_Device_Template
op_star
)paren
suffix:semicolon
r_extern
r_void
id|scsi_upper_driver_unregister
c_func
(paren
r_struct
id|Scsi_Device_Template
op_star
)paren
suffix:semicolon
r_extern
r_int
id|scsi_sysfs_register
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|scsi_sysfs_unregister
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * dev_info: for the black/white list in the old scsi_static_device_list&n; */
DECL|struct|dev_info
r_struct
id|dev_info
(brace
DECL|member|vendor
r_char
op_star
id|vendor
suffix:semicolon
DECL|member|model
r_char
op_star
id|model
suffix:semicolon
DECL|member|revision
r_char
op_star
id|revision
suffix:semicolon
multiline_comment|/* revision known to be bad, unused */
DECL|member|flags
r_int
id|flags
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|dev_info
id|scsi_static_device_list
(braket
)braket
suffix:semicolon
multiline_comment|/*&n; * scsi_dev_info_list: structure to hold black/white listed devices.&n; */
DECL|struct|scsi_dev_info_list
r_struct
id|scsi_dev_info_list
(brace
DECL|member|dev_info_list
r_struct
id|list_head
id|dev_info_list
suffix:semicolon
DECL|member|vendor
r_char
id|vendor
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|model
r_char
id|model
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|flags
r_int
id|flags
suffix:semicolon
DECL|member|compatible
r_int
id|compatible
suffix:semicolon
multiline_comment|/* for use with scsi_static_device_list entries */
)brace
suffix:semicolon
r_extern
r_struct
id|list_head
id|scsi_dev_info_list
suffix:semicolon
r_extern
r_int
id|scsi_dev_info_list_add_str
c_func
(paren
r_char
op_star
)paren
suffix:semicolon
macro_line|#endif /* _SCSI_PRIV_H */
eof
