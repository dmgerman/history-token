multiline_comment|/*&n; * Copyright (C) 2000, 2001, 2002 Broadcom Corporation&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version 2&n; * of the License, or (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.&n; */
multiline_comment|/*  *********************************************************************&n;    *&n;    *  Broadcom Common Firmware Environment (CFE)&n;    *&n;    *  Device function prototypes&t;&t;File: cfe_api_int.h&n;    *&n;    *  This header defines all internal types and macros for the&n;    *  library.  This is stuff that&squot;s not exported to an app&n;    *  using the library.&n;    *&n;    *  Authors:  Mitch Lichtenberg, Chris Demetriou&n;    *&n;    ********************************************************************* */
macro_line|#ifndef CFE_API_INT_H
DECL|macro|CFE_API_INT_H
mdefine_line|#define CFE_API_INT_H
multiline_comment|/*  *********************************************************************&n;    *  Constants&n;    ********************************************************************* */
DECL|macro|CFE_CMD_FW_GETINFO
mdefine_line|#define CFE_CMD_FW_GETINFO&t;0
DECL|macro|CFE_CMD_FW_RESTART
mdefine_line|#define CFE_CMD_FW_RESTART&t;1
DECL|macro|CFE_CMD_FW_BOOT
mdefine_line|#define CFE_CMD_FW_BOOT&t;&t;2
DECL|macro|CFE_CMD_FW_CPUCTL
mdefine_line|#define CFE_CMD_FW_CPUCTL&t;3
DECL|macro|CFE_CMD_FW_GETTIME
mdefine_line|#define CFE_CMD_FW_GETTIME      4
DECL|macro|CFE_CMD_FW_MEMENUM
mdefine_line|#define CFE_CMD_FW_MEMENUM&t;5
DECL|macro|CFE_CMD_FW_FLUSHCACHE
mdefine_line|#define CFE_CMD_FW_FLUSHCACHE&t;6
DECL|macro|CFE_CMD_DEV_GETHANDLE
mdefine_line|#define CFE_CMD_DEV_GETHANDLE&t;9
DECL|macro|CFE_CMD_DEV_ENUM
mdefine_line|#define CFE_CMD_DEV_ENUM&t;10
DECL|macro|CFE_CMD_DEV_OPEN
mdefine_line|#define CFE_CMD_DEV_OPEN&t;11
DECL|macro|CFE_CMD_DEV_INPSTAT
mdefine_line|#define CFE_CMD_DEV_INPSTAT&t;12
DECL|macro|CFE_CMD_DEV_READ
mdefine_line|#define CFE_CMD_DEV_READ&t;13
DECL|macro|CFE_CMD_DEV_WRITE
mdefine_line|#define CFE_CMD_DEV_WRITE&t;14
DECL|macro|CFE_CMD_DEV_IOCTL
mdefine_line|#define CFE_CMD_DEV_IOCTL&t;15
DECL|macro|CFE_CMD_DEV_CLOSE
mdefine_line|#define CFE_CMD_DEV_CLOSE&t;16
DECL|macro|CFE_CMD_DEV_GETINFO
mdefine_line|#define CFE_CMD_DEV_GETINFO&t;17
DECL|macro|CFE_CMD_ENV_ENUM
mdefine_line|#define CFE_CMD_ENV_ENUM&t;20
DECL|macro|CFE_CMD_ENV_GET
mdefine_line|#define CFE_CMD_ENV_GET&t;&t;22
DECL|macro|CFE_CMD_ENV_SET
mdefine_line|#define CFE_CMD_ENV_SET&t;&t;23
DECL|macro|CFE_CMD_ENV_DEL
mdefine_line|#define CFE_CMD_ENV_DEL&t;&t;24
DECL|macro|CFE_CMD_MAX
mdefine_line|#define CFE_CMD_MAX&t;&t;32
DECL|macro|CFE_CMD_VENDOR_USE
mdefine_line|#define CFE_CMD_VENDOR_USE&t;0x8000&t;/* codes above this are for customer use */
multiline_comment|/*  *********************************************************************&n;    *  Structures&n;    ********************************************************************* */
DECL|typedef|cfe_xuint_t
r_typedef
r_uint64
id|cfe_xuint_t
suffix:semicolon
DECL|typedef|cfe_xint_t
r_typedef
r_int64
id|cfe_xint_t
suffix:semicolon
DECL|typedef|cfe_xptr_t
r_typedef
r_int64
id|cfe_xptr_t
suffix:semicolon
DECL|struct|xiocb_buffer_s
r_typedef
r_struct
id|xiocb_buffer_s
(brace
DECL|member|buf_offset
id|cfe_xuint_t
id|buf_offset
suffix:semicolon
multiline_comment|/* offset on device (bytes) */
DECL|member|buf_ptr
id|cfe_xptr_t
id|buf_ptr
suffix:semicolon
multiline_comment|/* pointer to a buffer */
DECL|member|buf_length
id|cfe_xuint_t
id|buf_length
suffix:semicolon
multiline_comment|/* length of this buffer */
DECL|member|buf_retlen
id|cfe_xuint_t
id|buf_retlen
suffix:semicolon
multiline_comment|/* returned length (for read ops) */
DECL|member|buf_ioctlcmd
id|cfe_xuint_t
id|buf_ioctlcmd
suffix:semicolon
multiline_comment|/* IOCTL command (used only for IOCTLs) */
DECL|typedef|xiocb_buffer_t
)brace
id|xiocb_buffer_t
suffix:semicolon
DECL|macro|buf_devflags
mdefine_line|#define buf_devflags buf_ioctlcmd&t;/* returned device info flags */
DECL|struct|xiocb_inpstat_s
r_typedef
r_struct
id|xiocb_inpstat_s
(brace
DECL|member|inp_status
id|cfe_xuint_t
id|inp_status
suffix:semicolon
multiline_comment|/* 1 means input available */
DECL|typedef|xiocb_inpstat_t
)brace
id|xiocb_inpstat_t
suffix:semicolon
DECL|struct|xiocb_envbuf_s
r_typedef
r_struct
id|xiocb_envbuf_s
(brace
DECL|member|enum_idx
id|cfe_xint_t
id|enum_idx
suffix:semicolon
multiline_comment|/* 0-based enumeration index */
DECL|member|name_ptr
id|cfe_xptr_t
id|name_ptr
suffix:semicolon
multiline_comment|/* name string buffer */
DECL|member|name_length
id|cfe_xint_t
id|name_length
suffix:semicolon
multiline_comment|/* size of name buffer */
DECL|member|val_ptr
id|cfe_xptr_t
id|val_ptr
suffix:semicolon
multiline_comment|/* value string buffer */
DECL|member|val_length
id|cfe_xint_t
id|val_length
suffix:semicolon
multiline_comment|/* size of value string buffer */
DECL|typedef|xiocb_envbuf_t
)brace
id|xiocb_envbuf_t
suffix:semicolon
DECL|struct|xiocb_cpuctl_s
r_typedef
r_struct
id|xiocb_cpuctl_s
(brace
DECL|member|cpu_number
id|cfe_xuint_t
id|cpu_number
suffix:semicolon
multiline_comment|/* cpu number to control */
DECL|member|cpu_command
id|cfe_xuint_t
id|cpu_command
suffix:semicolon
multiline_comment|/* command to issue to CPU */
DECL|member|start_addr
id|cfe_xuint_t
id|start_addr
suffix:semicolon
multiline_comment|/* CPU start address */
DECL|member|gp_val
id|cfe_xuint_t
id|gp_val
suffix:semicolon
multiline_comment|/* starting GP value */
DECL|member|sp_val
id|cfe_xuint_t
id|sp_val
suffix:semicolon
multiline_comment|/* starting SP value */
DECL|member|a1_val
id|cfe_xuint_t
id|a1_val
suffix:semicolon
multiline_comment|/* starting A1 value */
DECL|typedef|xiocb_cpuctl_t
)brace
id|xiocb_cpuctl_t
suffix:semicolon
DECL|struct|xiocb_time_s
r_typedef
r_struct
id|xiocb_time_s
(brace
DECL|member|ticks
id|cfe_xint_t
id|ticks
suffix:semicolon
multiline_comment|/* current time in ticks */
DECL|typedef|xiocb_time_t
)brace
id|xiocb_time_t
suffix:semicolon
DECL|struct|xiocb_exitstat_s
r_typedef
r_struct
id|xiocb_exitstat_s
(brace
DECL|member|status
id|cfe_xint_t
id|status
suffix:semicolon
DECL|typedef|xiocb_exitstat_t
)brace
id|xiocb_exitstat_t
suffix:semicolon
DECL|struct|xiocb_meminfo_s
r_typedef
r_struct
id|xiocb_meminfo_s
(brace
DECL|member|mi_idx
id|cfe_xint_t
id|mi_idx
suffix:semicolon
multiline_comment|/* 0-based enumeration index */
DECL|member|mi_type
id|cfe_xint_t
id|mi_type
suffix:semicolon
multiline_comment|/* type of memory block */
DECL|member|mi_addr
id|cfe_xuint_t
id|mi_addr
suffix:semicolon
multiline_comment|/* physical start address */
DECL|member|mi_size
id|cfe_xuint_t
id|mi_size
suffix:semicolon
multiline_comment|/* block size */
DECL|typedef|xiocb_meminfo_t
)brace
id|xiocb_meminfo_t
suffix:semicolon
DECL|struct|xiocb_fwinfo_s
r_typedef
r_struct
id|xiocb_fwinfo_s
(brace
DECL|member|fwi_version
id|cfe_xint_t
id|fwi_version
suffix:semicolon
multiline_comment|/* major, minor, eco version */
DECL|member|fwi_totalmem
id|cfe_xint_t
id|fwi_totalmem
suffix:semicolon
multiline_comment|/* total installed mem */
DECL|member|fwi_flags
id|cfe_xint_t
id|fwi_flags
suffix:semicolon
multiline_comment|/* various flags */
DECL|member|fwi_boardid
id|cfe_xint_t
id|fwi_boardid
suffix:semicolon
multiline_comment|/* board ID */
DECL|member|fwi_bootarea_va
id|cfe_xint_t
id|fwi_bootarea_va
suffix:semicolon
multiline_comment|/* VA of boot area */
DECL|member|fwi_bootarea_pa
id|cfe_xint_t
id|fwi_bootarea_pa
suffix:semicolon
multiline_comment|/* PA of boot area */
DECL|member|fwi_bootarea_size
id|cfe_xint_t
id|fwi_bootarea_size
suffix:semicolon
multiline_comment|/* size of boot area */
DECL|member|fwi_reserved1
id|cfe_xint_t
id|fwi_reserved1
suffix:semicolon
DECL|member|fwi_reserved2
id|cfe_xint_t
id|fwi_reserved2
suffix:semicolon
DECL|member|fwi_reserved3
id|cfe_xint_t
id|fwi_reserved3
suffix:semicolon
DECL|typedef|xiocb_fwinfo_t
)brace
id|xiocb_fwinfo_t
suffix:semicolon
DECL|struct|cfe_xiocb_s
r_typedef
r_struct
id|cfe_xiocb_s
(brace
DECL|member|xiocb_fcode
id|cfe_xuint_t
id|xiocb_fcode
suffix:semicolon
multiline_comment|/* IOCB function code */
DECL|member|xiocb_status
id|cfe_xint_t
id|xiocb_status
suffix:semicolon
multiline_comment|/* return status */
DECL|member|xiocb_handle
id|cfe_xint_t
id|xiocb_handle
suffix:semicolon
multiline_comment|/* file/device handle */
DECL|member|xiocb_flags
id|cfe_xuint_t
id|xiocb_flags
suffix:semicolon
multiline_comment|/* flags for this IOCB */
DECL|member|xiocb_psize
id|cfe_xuint_t
id|xiocb_psize
suffix:semicolon
multiline_comment|/* size of parameter list */
r_union
(brace
DECL|member|xiocb_buffer
id|xiocb_buffer_t
id|xiocb_buffer
suffix:semicolon
multiline_comment|/* buffer parameters */
DECL|member|xiocb_inpstat
id|xiocb_inpstat_t
id|xiocb_inpstat
suffix:semicolon
multiline_comment|/* input status parameters */
DECL|member|xiocb_envbuf
id|xiocb_envbuf_t
id|xiocb_envbuf
suffix:semicolon
multiline_comment|/* environment function parameters */
DECL|member|xiocb_cpuctl
id|xiocb_cpuctl_t
id|xiocb_cpuctl
suffix:semicolon
multiline_comment|/* CPU control parameters */
DECL|member|xiocb_time
id|xiocb_time_t
id|xiocb_time
suffix:semicolon
multiline_comment|/* timer parameters */
DECL|member|xiocb_meminfo
id|xiocb_meminfo_t
id|xiocb_meminfo
suffix:semicolon
multiline_comment|/* memory arena info parameters */
DECL|member|xiocb_fwinfo
id|xiocb_fwinfo_t
id|xiocb_fwinfo
suffix:semicolon
multiline_comment|/* firmware information */
DECL|member|xiocb_exitstat
id|xiocb_exitstat_t
id|xiocb_exitstat
suffix:semicolon
multiline_comment|/* Exit Status */
DECL|member|plist
)brace
id|plist
suffix:semicolon
DECL|typedef|cfe_xiocb_t
)brace
id|cfe_xiocb_t
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* CFE_API_INT_H */
eof
