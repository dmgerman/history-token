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
r_extern
r_void
id|__scsi_release_request
c_func
(paren
r_struct
id|scsi_request
op_star
id|sreq
)paren
suffix:semicolon
multiline_comment|/* scsi_devinfo.c */
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
id|scsi_init_devinfo
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|scsi_exit_devinfo
c_func
(paren
r_void
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
r_void
id|scsi_eh_wakeup
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|shost
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
r_void
id|scsi_device_unbusy
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
id|scsi_next_command
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
id|scsi_run_host_queues
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|shost
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
macro_line|# define scsi_exit_procfs()&t;&t;do { } while (0)
macro_line|#endif /* CONFIG_PROC_FS */
multiline_comment|/* scsi_scan.c */
r_extern
r_void
id|scsi_forget_host
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_extern
r_void
id|scsi_free_sdev
c_func
(paren
r_struct
id|scsi_device
op_star
)paren
suffix:semicolon
r_extern
r_void
id|scsi_free_shost
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_extern
r_void
id|scsi_rescan_device
c_func
(paren
r_struct
id|device
op_star
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
r_void
id|scsi_sysfs_init_host
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_extern
r_int
id|scsi_sysfs_add_host
c_func
(paren
r_struct
id|Scsi_Host
op_star
comma
r_struct
id|device
op_star
)paren
suffix:semicolon
r_extern
r_void
id|scsi_sysfs_remove_host
c_func
(paren
r_struct
id|Scsi_Host
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
r_extern
r_struct
r_class
id|shost_class
suffix:semicolon
r_extern
r_struct
r_class
id|sdev_class
suffix:semicolon
r_extern
r_struct
id|bus_type
id|scsi_bus_type
suffix:semicolon
macro_line|#endif /* _SCSI_PRIV_H */
eof
