multiline_comment|/*&n; * BK Id: SCCS/s.sembuf.h 1.5 05/17/01 18:14:25 cort&n; */
macro_line|#ifndef _PPC_SEMBUF_H
DECL|macro|_PPC_SEMBUF_H
mdefine_line|#define _PPC_SEMBUF_H
multiline_comment|/* &n; * The semid64_ds structure for PPC architecture.&n; */
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
DECL|member|__unused1
r_int
r_int
id|__unused1
suffix:semicolon
DECL|member|sem_otime
id|__kernel_time_t
id|sem_otime
suffix:semicolon
multiline_comment|/* last semop time */
DECL|member|__unused2
r_int
r_int
id|__unused2
suffix:semicolon
DECL|member|sem_ctime
id|__kernel_time_t
id|sem_ctime
suffix:semicolon
multiline_comment|/* last change time */
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
macro_line|#endif /* _PPC_SEMBUF_H */
eof
