macro_line|#ifndef __ASM_SH64_SEMBUF_H
DECL|macro|__ASM_SH64_SEMBUF_H
mdefine_line|#define __ASM_SH64_SEMBUF_H
multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * include/asm-sh64/sembuf.h&n; *&n; * Copyright (C) 2000, 2001  Paolo Alberelli&n; *&n; */
multiline_comment|/*&n; * The semid64_ds structure for i386 architecture.&n; * Note extra padding because this structure is passed back and forth&n; * between kernel and user space.&n; *&n; * Pad space is left for:&n; * - 64-bit time_t to solve y2038 problem&n; * - 2 miscellaneous 32-bit values&n; */
DECL|struct|semid64_ds
r_struct
id|semid64_ds
(brace
DECL|member|sem_perm
r_struct
id|ipc64_perm
id|sem_perm
suffix:semicolon
multiline_comment|/* permissions .. see ipc.h */
DECL|member|sem_otime
id|__kernel_time_t
id|sem_otime
suffix:semicolon
multiline_comment|/* last semop time */
DECL|member|__unused1
r_int
r_int
id|__unused1
suffix:semicolon
DECL|member|sem_ctime
id|__kernel_time_t
id|sem_ctime
suffix:semicolon
multiline_comment|/* last change time */
DECL|member|__unused2
r_int
r_int
id|__unused2
suffix:semicolon
DECL|member|sem_nsems
r_int
r_int
id|sem_nsems
suffix:semicolon
multiline_comment|/* no. of semaphores in array */
DECL|member|__unused3
r_int
r_int
id|__unused3
suffix:semicolon
DECL|member|__unused4
r_int
r_int
id|__unused4
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* __ASM_SH64_SEMBUF_H */
eof
