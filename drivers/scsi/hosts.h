multiline_comment|/*&n; *  hosts.h Copyright (C) 1992 Drew Eckhardt&n; *          Copyright (C) 1993, 1994, 1995, 1998, 1999 Eric Youngdale&n; *&n; *  mid to low-level SCSI driver interface header&n; *      Initial versions: Drew Eckhardt&n; *      Subsequent revisions: Eric Youngdale&n; *&n; *  &lt;drew@colorado.edu&gt;&n; *&n; *&t; Modified by Eric Youngdale eric@andante.org to&n; *&t; add scatter-gather, multiple outstanding request, and other&n; *&t; enhancements.&n; *&n; *  Further modified by Eric Youngdale to support multiple host adapters&n; *  of the same type.&n; *&n; *  Jiffies wrap fixes (host-&gt;resetting), 3 Dec 1998 Andrea Arcangeli&n; *&n; *  Restructured scsi_host lists and associated functions.&n; *  September 04, 2002 Mike Anderson (andmike@us.ibm.com)&n; */
macro_line|#ifndef _HOSTS_H
DECL|macro|_HOSTS_H
mdefine_line|#define _HOSTS_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;scsi/scsi_host.h&gt;
multiline_comment|/**&n; * scsi_find_device - find a device given the host&n; * @shost:&t;SCSI host pointer&n; * @channel:&t;SCSI channel (zero if only one channel)&n; * @pun:&t;SCSI target number (physical unit number)&n; * @lun:&t;SCSI Logical Unit Number&n; **/
DECL|function|scsi_find_device
r_static
r_inline
r_struct
id|scsi_device
op_star
id|scsi_find_device
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|shost
comma
r_int
id|channel
comma
r_int
id|pun
comma
r_int
id|lun
)paren
(brace
r_struct
id|scsi_device
op_star
id|sdev
suffix:semicolon
id|list_for_each_entry
(paren
id|sdev
comma
op_amp
id|shost-&gt;my_devices
comma
id|siblings
)paren
r_if
c_cond
(paren
id|sdev-&gt;channel
op_eq
id|channel
op_logical_and
id|sdev-&gt;id
op_eq
id|pun
op_logical_and
id|sdev-&gt;lun
op_eq
id|lun
)paren
r_return
id|sdev
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
macro_line|#endif
eof
