macro_line|#ifndef __ASM_SH64_SHMBUF_H
DECL|macro|__ASM_SH64_SHMBUF_H
mdefine_line|#define __ASM_SH64_SHMBUF_H
multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * include/asm-sh64/shmbuf.h&n; *&n; * Copyright (C) 2000, 2001  Paolo Alberelli&n; *&n; */
multiline_comment|/*&n; * The shmid64_ds structure for i386 architecture.&n; * Note extra padding because this structure is passed back and forth&n; * between kernel and user space.&n; *&n; * Pad space is left for:&n; * - 64-bit time_t to solve y2038 problem&n; * - 2 miscellaneous 32-bit values&n; */
DECL|struct|shmid64_ds
r_struct
id|shmid64_ds
(brace
DECL|member|shm_perm
r_struct
id|ipc64_perm
id|shm_perm
suffix:semicolon
multiline_comment|/* operation perms */
DECL|member|shm_segsz
r_int
id|shm_segsz
suffix:semicolon
multiline_comment|/* size of segment (bytes) */
DECL|member|shm_atime
id|__kernel_time_t
id|shm_atime
suffix:semicolon
multiline_comment|/* last attach time */
DECL|member|__unused1
r_int
r_int
id|__unused1
suffix:semicolon
DECL|member|shm_dtime
id|__kernel_time_t
id|shm_dtime
suffix:semicolon
multiline_comment|/* last detach time */
DECL|member|__unused2
r_int
r_int
id|__unused2
suffix:semicolon
DECL|member|shm_ctime
id|__kernel_time_t
id|shm_ctime
suffix:semicolon
multiline_comment|/* last change time */
DECL|member|__unused3
r_int
r_int
id|__unused3
suffix:semicolon
DECL|member|shm_cpid
id|__kernel_pid_t
id|shm_cpid
suffix:semicolon
multiline_comment|/* pid of creator */
DECL|member|shm_lpid
id|__kernel_pid_t
id|shm_lpid
suffix:semicolon
multiline_comment|/* pid of last operator */
DECL|member|shm_nattch
r_int
r_int
id|shm_nattch
suffix:semicolon
multiline_comment|/* no. of current attaches */
DECL|member|__unused4
r_int
r_int
id|__unused4
suffix:semicolon
DECL|member|__unused5
r_int
r_int
id|__unused5
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|shminfo64
r_struct
id|shminfo64
(brace
DECL|member|shmmax
r_int
r_int
id|shmmax
suffix:semicolon
DECL|member|shmmin
r_int
r_int
id|shmmin
suffix:semicolon
DECL|member|shmmni
r_int
r_int
id|shmmni
suffix:semicolon
DECL|member|shmseg
r_int
r_int
id|shmseg
suffix:semicolon
DECL|member|shmall
r_int
r_int
id|shmall
suffix:semicolon
DECL|member|__unused1
r_int
r_int
id|__unused1
suffix:semicolon
DECL|member|__unused2
r_int
r_int
id|__unused2
suffix:semicolon
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
macro_line|#endif /* __ASM_SH64_SHMBUF_H */
eof
