multiline_comment|/*&n;   libata.h - helper library for ATA&n;&n;   Copyright 2003 Red Hat, Inc.  All rights reserved.&n;   Copyright 2003 Jeff Garzik&n;&n;   The contents of this file are subject to the Open&n;   Software License version 1.1 that can be found at&n;   http://www.opensource.org/licenses/osl-1.1.txt and is included herein&n;   by reference.&n;&n;   Alternatively, the contents of this file may be used under the terms&n;   of the GNU General Public License version 2 (the &quot;GPL&quot;) as distributed&n;   in the kernel source COPYING file, in which case the provisions of&n;   the GPL are applicable instead of the above.  If you wish to allow&n;   the use of your version of this file only under the terms of the&n;   GPL and not to allow others to use your version of this file under&n;   the OSL, indicate your decision by deleting the provisions above and&n;   replace them with the notice and other provisions required by the GPL.&n;   If you do not delete the provisions above, a recipient may use your&n;   version of this file under either the OSL or the GPL.&n;&n; */
macro_line|#ifndef __LIBATA_H__
DECL|macro|__LIBATA_H__
mdefine_line|#define __LIBATA_H__
DECL|macro|DRV_NAME
mdefine_line|#define DRV_NAME&t;&quot;libata&quot;
DECL|macro|DRV_VERSION
mdefine_line|#define DRV_VERSION&t;&quot;0.81&quot;&t;/* must be exactly four chars */
DECL|struct|ata_scsi_args
r_struct
id|ata_scsi_args
(brace
DECL|member|ap
r_struct
id|ata_port
op_star
id|ap
suffix:semicolon
DECL|member|dev
r_struct
id|ata_device
op_star
id|dev
suffix:semicolon
DECL|member|cmd
r_struct
id|scsi_cmnd
op_star
id|cmd
suffix:semicolon
DECL|member|done
r_void
(paren
op_star
id|done
)paren
(paren
r_struct
id|scsi_cmnd
op_star
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* libata-core.c */
r_extern
r_int
r_int
id|ata_dev_id_string
c_func
(paren
r_struct
id|ata_device
op_star
id|dev
comma
r_int
r_char
op_star
id|s
comma
r_int
r_int
id|ofs
comma
r_int
r_int
id|len
)paren
suffix:semicolon
r_extern
r_struct
id|ata_queued_cmd
op_star
id|ata_qc_new_init
c_func
(paren
r_struct
id|ata_port
op_star
id|ap
comma
r_struct
id|ata_device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_int
id|ata_qc_issue
c_func
(paren
r_struct
id|ata_queued_cmd
op_star
id|qc
)paren
suffix:semicolon
r_extern
r_void
id|ata_dev_select
c_func
(paren
r_struct
id|ata_port
op_star
id|ap
comma
r_int
r_int
id|device
comma
r_int
r_int
id|wait
comma
r_int
r_int
id|can_sleep
)paren
suffix:semicolon
r_extern
r_void
id|ata_tf_to_host_nolock
c_func
(paren
r_struct
id|ata_port
op_star
id|ap
comma
r_struct
id|ata_taskfile
op_star
id|tf
)paren
suffix:semicolon
r_extern
r_void
id|ata_thread_wake
c_func
(paren
r_struct
id|ata_port
op_star
id|ap
comma
r_int
r_int
id|thr_state
)paren
suffix:semicolon
multiline_comment|/* libata-scsi.c */
r_extern
r_void
id|ata_to_sense_error
c_func
(paren
r_struct
id|ata_queued_cmd
op_star
id|qc
)paren
suffix:semicolon
r_extern
r_void
id|ata_scsi_rw_queue
c_func
(paren
r_struct
id|ata_port
op_star
id|ap
comma
r_struct
id|ata_device
op_star
id|dev
comma
r_struct
id|scsi_cmnd
op_star
id|cmd
comma
r_void
(paren
op_star
id|done
)paren
(paren
r_struct
id|scsi_cmnd
op_star
)paren
comma
r_int
r_int
id|cmd_size
)paren
suffix:semicolon
r_extern
r_int
id|ata_scsi_error
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|host
)paren
suffix:semicolon
r_extern
r_int
r_int
id|ata_scsiop_inq_std
c_func
(paren
r_struct
id|ata_scsi_args
op_star
id|args
comma
id|u8
op_star
id|rbuf
comma
r_int
r_int
id|buflen
)paren
suffix:semicolon
r_extern
r_int
r_int
id|ata_scsiop_inq_00
c_func
(paren
r_struct
id|ata_scsi_args
op_star
id|args
comma
id|u8
op_star
id|rbuf
comma
r_int
r_int
id|buflen
)paren
suffix:semicolon
r_extern
r_int
r_int
id|ata_scsiop_inq_80
c_func
(paren
r_struct
id|ata_scsi_args
op_star
id|args
comma
id|u8
op_star
id|rbuf
comma
r_int
r_int
id|buflen
)paren
suffix:semicolon
r_extern
r_int
r_int
id|ata_scsiop_inq_83
c_func
(paren
r_struct
id|ata_scsi_args
op_star
id|args
comma
id|u8
op_star
id|rbuf
comma
r_int
r_int
id|buflen
)paren
suffix:semicolon
r_extern
r_int
r_int
id|ata_scsiop_noop
c_func
(paren
r_struct
id|ata_scsi_args
op_star
id|args
comma
id|u8
op_star
id|rbuf
comma
r_int
r_int
id|buflen
)paren
suffix:semicolon
r_extern
r_int
r_int
id|ata_scsiop_sync_cache
c_func
(paren
r_struct
id|ata_scsi_args
op_star
id|args
comma
id|u8
op_star
id|rbuf
comma
r_int
r_int
id|buflen
)paren
suffix:semicolon
r_extern
r_int
r_int
id|ata_scsiop_mode_sense
c_func
(paren
r_struct
id|ata_scsi_args
op_star
id|args
comma
id|u8
op_star
id|rbuf
comma
r_int
r_int
id|buflen
)paren
suffix:semicolon
r_extern
r_int
r_int
id|ata_scsiop_read_cap
c_func
(paren
r_struct
id|ata_scsi_args
op_star
id|args
comma
id|u8
op_star
id|rbuf
comma
r_int
r_int
id|buflen
)paren
suffix:semicolon
r_extern
r_int
r_int
id|ata_scsiop_report_luns
c_func
(paren
r_struct
id|ata_scsi_args
op_star
id|args
comma
id|u8
op_star
id|rbuf
comma
r_int
r_int
id|buflen
)paren
suffix:semicolon
r_extern
r_void
id|ata_scsi_badcmd
c_func
(paren
r_struct
id|scsi_cmnd
op_star
id|cmd
comma
r_void
(paren
op_star
id|done
)paren
(paren
r_struct
id|scsi_cmnd
op_star
)paren
comma
id|u8
id|asc
comma
id|u8
id|ascq
)paren
suffix:semicolon
r_extern
r_void
id|ata_scsi_rbuf_fill
c_func
(paren
r_struct
id|ata_scsi_args
op_star
id|args
comma
r_int
r_int
(paren
op_star
id|actor
)paren
(paren
r_struct
id|ata_scsi_args
op_star
id|args
comma
id|u8
op_star
id|rbuf
comma
r_int
r_int
id|buflen
)paren
)paren
suffix:semicolon
DECL|function|ata_bad_scsiop
r_static
r_inline
r_void
id|ata_bad_scsiop
c_func
(paren
r_struct
id|scsi_cmnd
op_star
id|cmd
comma
r_void
(paren
op_star
id|done
)paren
(paren
r_struct
id|scsi_cmnd
op_star
)paren
)paren
(brace
id|ata_scsi_badcmd
c_func
(paren
id|cmd
comma
id|done
comma
l_int|0x20
comma
l_int|0x00
)paren
suffix:semicolon
)brace
DECL|function|ata_bad_cdb
r_static
r_inline
r_void
id|ata_bad_cdb
c_func
(paren
r_struct
id|scsi_cmnd
op_star
id|cmd
comma
r_void
(paren
op_star
id|done
)paren
(paren
r_struct
id|scsi_cmnd
op_star
)paren
)paren
(brace
id|ata_scsi_badcmd
c_func
(paren
id|cmd
comma
id|done
comma
l_int|0x24
comma
l_int|0x00
)paren
suffix:semicolon
)brace
macro_line|#endif /* __LIBATA_H__ */
eof
