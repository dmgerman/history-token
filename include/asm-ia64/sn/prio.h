multiline_comment|/* $Id$&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 - 1997, 2000 Silicon Graphics, Inc.&n; * Copyright (C) 2000 by Colin Ngam&n; */
macro_line|#ifndef _ASM_SN_PRIO_H
DECL|macro|_ASM_SN_PRIO_H
mdefine_line|#define _ASM_SN_PRIO_H
multiline_comment|/*&n; * Priority I/O function prototypes and macro definitions&n; */
DECL|typedef|bandwidth_t
r_typedef
r_int
r_int
id|bandwidth_t
suffix:semicolon
multiline_comment|/* These should be the same as FREAD/FWRITE */
DECL|macro|PRIO_READ_ALLOCATE
mdefine_line|#define PRIO_READ_ALLOCATE&t;0x1
DECL|macro|PRIO_WRITE_ALLOCATE
mdefine_line|#define PRIO_WRITE_ALLOCATE&t;0x2
DECL|macro|PRIO_READWRITE_ALLOCATE
mdefine_line|#define PRIO_READWRITE_ALLOCATE&t;(PRIO_READ_ALLOCATE | PRIO_WRITE_ALLOCATE)
r_extern
r_int
id|prioSetBandwidth
(paren
r_int
multiline_comment|/* fd */
comma
r_int
multiline_comment|/* alloc_type */
comma
id|bandwidth_t
multiline_comment|/* bytes_per_sec */
comma
id|pid_t
op_star
multiline_comment|/* pid */
)paren
suffix:semicolon
r_extern
r_int
id|prioGetBandwidth
(paren
r_int
multiline_comment|/* fd */
comma
id|bandwidth_t
op_star
multiline_comment|/* read_bw */
comma
id|bandwidth_t
op_star
multiline_comment|/* write_bw */
)paren
suffix:semicolon
r_extern
r_int
id|prioLock
(paren
id|pid_t
op_star
)paren
suffix:semicolon
r_extern
r_int
id|prioUnlock
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Error returns */
DECL|macro|PRIO_SUCCESS
mdefine_line|#define PRIO_SUCCESS     0
DECL|macro|PRIO_FAIL
mdefine_line|#define PRIO_FAIL       -1 
macro_line|#endif /* _ASM_SN_PRIO_H */
eof
