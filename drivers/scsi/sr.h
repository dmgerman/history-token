multiline_comment|/*&n; *      sr.h by David Giller&n; *      CD-ROM disk driver header file&n; *      &n; *      adapted from:&n; *      sd.h Copyright (C) 1992 Drew Eckhardt &n; *      SCSI disk driver header file by&n; *              Drew Eckhardt &n; *&n; *      &lt;drew@colorado.edu&gt;&n; *&n; *       Modified by Eric Youngdale eric@andante.org to&n; *       add scatter-gather, multiple outstanding request, and other&n; *       enhancements.&n; */
macro_line|#ifndef _SR_H
DECL|macro|_SR_H
mdefine_line|#define _SR_H
macro_line|#include &quot;scsi.h&quot;
macro_line|#include &lt;linux/genhd.h&gt;
multiline_comment|/* The CDROM is fairly slow, so we need a little extra time */
multiline_comment|/* In fact, it is very slow if it has to spin up first */
DECL|macro|IOCTL_TIMEOUT
mdefine_line|#define IOCTL_TIMEOUT 30*HZ
r_typedef
r_struct
(brace
DECL|member|capacity
r_int
id|capacity
suffix:semicolon
multiline_comment|/* size in blocks                       */
DECL|member|device
id|Scsi_Device
op_star
id|device
suffix:semicolon
DECL|member|vendor
r_int
r_int
id|vendor
suffix:semicolon
multiline_comment|/* vendor code, see sr_vendor.c         */
DECL|member|ms_offset
r_int
r_int
id|ms_offset
suffix:semicolon
multiline_comment|/* for reading multisession-CD&squot;s        */
DECL|member|needs_sector_size
r_int
id|needs_sector_size
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* needs to get sector size */
DECL|member|use
r_int
id|use
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* is this device still supportable     */
DECL|member|xa_flag
r_int
id|xa_flag
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* CD has XA sectors ? */
DECL|member|readcd_known
r_int
id|readcd_known
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* drive supports READ_CD (0xbe) */
DECL|member|readcd_cdda
r_int
id|readcd_cdda
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* reading audio data using READ_CD */
DECL|member|cdi
r_struct
id|cdrom_device_info
id|cdi
suffix:semicolon
DECL|member|disk
r_struct
id|gendisk
op_star
id|disk
suffix:semicolon
DECL|typedef|Scsi_CD
)brace
id|Scsi_CD
suffix:semicolon
r_int
id|sr_do_ioctl
c_func
(paren
id|Scsi_CD
op_star
comma
r_struct
id|cdrom_generic_command
op_star
)paren
suffix:semicolon
r_int
id|sr_lock_door
c_func
(paren
r_struct
id|cdrom_device_info
op_star
comma
r_int
)paren
suffix:semicolon
r_int
id|sr_tray_move
c_func
(paren
r_struct
id|cdrom_device_info
op_star
comma
r_int
)paren
suffix:semicolon
r_int
id|sr_drive_status
c_func
(paren
r_struct
id|cdrom_device_info
op_star
comma
r_int
)paren
suffix:semicolon
r_int
id|sr_disk_status
c_func
(paren
r_struct
id|cdrom_device_info
op_star
)paren
suffix:semicolon
r_int
id|sr_get_last_session
c_func
(paren
r_struct
id|cdrom_device_info
op_star
comma
r_struct
id|cdrom_multisession
op_star
)paren
suffix:semicolon
r_int
id|sr_get_mcn
c_func
(paren
r_struct
id|cdrom_device_info
op_star
comma
r_struct
id|cdrom_mcn
op_star
)paren
suffix:semicolon
r_int
id|sr_reset
c_func
(paren
r_struct
id|cdrom_device_info
op_star
)paren
suffix:semicolon
r_int
id|sr_select_speed
c_func
(paren
r_struct
id|cdrom_device_info
op_star
id|cdi
comma
r_int
id|speed
)paren
suffix:semicolon
r_int
id|sr_audio_ioctl
c_func
(paren
r_struct
id|cdrom_device_info
op_star
comma
r_int
r_int
comma
r_void
op_star
)paren
suffix:semicolon
r_int
id|sr_dev_ioctl
c_func
(paren
r_struct
id|cdrom_device_info
op_star
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_int
id|sr_is_xa
c_func
(paren
id|Scsi_CD
op_star
)paren
suffix:semicolon
multiline_comment|/* sr_vendor.c */
r_void
id|sr_vendor_init
c_func
(paren
id|Scsi_CD
op_star
)paren
suffix:semicolon
r_int
id|sr_cd_check
c_func
(paren
r_struct
id|cdrom_device_info
op_star
)paren
suffix:semicolon
r_int
id|sr_set_blocklength
c_func
(paren
id|Scsi_CD
op_star
comma
r_int
id|blocklength
)paren
suffix:semicolon
macro_line|#endif
eof
