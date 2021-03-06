multiline_comment|/*&n; *    Disk Array driver for Compaq SMART2 Controllers&n; *    Copyright 1998 Compaq Computer Corporation&n; *&n; *    This program is free software; you can redistribute it and/or modify&n; *    it under the terms of the GNU General Public License as published by&n; *    the Free Software Foundation; either version 2 of the License, or&n; *    (at your option) any later version.&n; *&n; *    This program is distributed in the hope that it will be useful,&n; *    but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *    MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, GOOD TITLE or&n; *    NON INFRINGEMENT.  See the GNU General Public License for more details.&n; *&n; *    You should have received a copy of the GNU General Public License&n; *    along with this program; if not, write to the Free Software&n; *    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; *    Questions/Comments/Bugfixes to iss_storagedev@hp.com&n; *&n; */
macro_line|#ifndef IDA_IOCTL_H
DECL|macro|IDA_IOCTL_H
mdefine_line|#define IDA_IOCTL_H
macro_line|#include &quot;ida_cmd.h&quot;
macro_line|#include &quot;cpqarray.h&quot;
DECL|macro|IDAGETDRVINFO
mdefine_line|#define IDAGETDRVINFO&t;&t;0x27272828
DECL|macro|IDAPASSTHRU
mdefine_line|#define IDAPASSTHRU&t;&t;0x28282929
DECL|macro|IDAGETCTLRSIG
mdefine_line|#define IDAGETCTLRSIG&t;&t;0x29293030
DECL|macro|IDAREVALIDATEVOLS
mdefine_line|#define IDAREVALIDATEVOLS&t;0x30303131
DECL|macro|IDADRIVERVERSION
mdefine_line|#define IDADRIVERVERSION&t;0x31313232
DECL|macro|IDAGETPCIINFO
mdefine_line|#define IDAGETPCIINFO&t;&t;0x32323333
DECL|struct|_ida_pci_info_struct
r_typedef
r_struct
id|_ida_pci_info_struct
(brace
DECL|member|bus
r_int
r_char
id|bus
suffix:semicolon
DECL|member|dev_fn
r_int
r_char
id|dev_fn
suffix:semicolon
DECL|member|board_id
id|__u32
id|board_id
suffix:semicolon
DECL|typedef|ida_pci_info_struct
)brace
id|ida_pci_info_struct
suffix:semicolon
multiline_comment|/*&n; * Normally, the ioctl determines the logical unit for this command by&n; * the major,minor number of the fd passed to ioctl.  If you need to send&n; * a command to a different/nonexistant unit (such as during config), you&n; * can override the normal behavior by setting the unit valid bit. (Normally,&n; * it should be zero) The controller the command is sent to is still&n; * determined by the major number of the open device.&n; */
DECL|macro|UNITVALID
mdefine_line|#define UNITVALID&t;0x80
r_typedef
r_struct
(brace
DECL|member|cmd
id|__u8
id|cmd
suffix:semicolon
DECL|member|rcode
id|__u8
id|rcode
suffix:semicolon
DECL|member|unit
id|__u8
id|unit
suffix:semicolon
DECL|member|blk
id|__u32
id|blk
suffix:semicolon
DECL|member|blk_cnt
id|__u16
id|blk_cnt
suffix:semicolon
multiline_comment|/* currently, sg_cnt is assumed to be 1: only the 0th element of sg is used */
r_struct
(brace
DECL|member|addr
r_void
id|__user
op_star
id|addr
suffix:semicolon
DECL|member|size
r_int
id|size
suffix:semicolon
DECL|member|sg
)brace
id|sg
(braket
id|SG_MAX
)braket
suffix:semicolon
DECL|member|sg_cnt
r_int
id|sg_cnt
suffix:semicolon
DECL|union|ctlr_cmds
r_union
id|ctlr_cmds
(brace
DECL|member|drv
id|drv_info_t
id|drv
suffix:semicolon
DECL|member|buf
r_int
r_char
id|buf
(braket
l_int|1024
)braket
suffix:semicolon
DECL|member|id_ctlr
id|id_ctlr_t
id|id_ctlr
suffix:semicolon
DECL|member|drv_param
id|drv_param_t
id|drv_param
suffix:semicolon
DECL|member|id_log_drv
id|id_log_drv_t
id|id_log_drv
suffix:semicolon
DECL|member|id_log_drv_ext
id|id_log_drv_ext_t
id|id_log_drv_ext
suffix:semicolon
DECL|member|sense_log_drv_stat
id|sense_log_drv_stat_t
id|sense_log_drv_stat
suffix:semicolon
DECL|member|id_phys_drv
id|id_phys_drv_t
id|id_phys_drv
suffix:semicolon
DECL|member|blink_drv_leds
id|blink_drv_leds_t
id|blink_drv_leds
suffix:semicolon
DECL|member|sense_blink_leds
id|sense_blink_leds_t
id|sense_blink_leds
suffix:semicolon
DECL|member|config
id|config_t
id|config
suffix:semicolon
DECL|member|reorder_log_drv
id|reorder_log_drv_t
id|reorder_log_drv
suffix:semicolon
DECL|member|label_log_drv
id|label_log_drv_t
id|label_log_drv
suffix:semicolon
DECL|member|surf_delay
id|surf_delay_t
id|surf_delay
suffix:semicolon
DECL|member|overhead_delay
id|overhead_delay_t
id|overhead_delay
suffix:semicolon
DECL|member|mp_delay
id|mp_delay_t
id|mp_delay
suffix:semicolon
DECL|member|scsi_param
id|scsi_param_t
id|scsi_param
suffix:semicolon
DECL|member|c
)brace
id|c
suffix:semicolon
DECL|typedef|ida_ioctl_t
)brace
id|ida_ioctl_t
suffix:semicolon
macro_line|#endif /* IDA_IOCTL_H */
eof
