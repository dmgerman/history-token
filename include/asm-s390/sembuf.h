macro_line|#ifndef _S390_SEMBUF_H
DECL|macro|_S390_SEMBUF_H
mdefine_line|#define _S390_SEMBUF_H
multiline_comment|/* &n; * The semid64_ds structure for S/390 architecture.&n; * Note extra padding because this structure is passed back and forth&n; * between kernel and user space.&n; *&n; * Pad space is left for:&n; * - 64-bit time_t to solve y2038 problem (for !__s390x__)&n; * - 2 miscellaneous 32-bit values&n; */
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
macro_line|#ifndef __s390x__
DECL|member|__unused1
r_int
r_int
id|__unused1
suffix:semicolon
macro_line|#endif /* ! __s390x__ */
DECL|member|sem_ctime
id|__kernel_time_t
id|sem_ctime
suffix:semicolon
multiline_comment|/* last change time */
macro_line|#ifndef __s390x__
DECL|member|__unused2
r_int
r_int
id|__unused2
suffix:semicolon
macro_line|#endif /* ! __s390x__ */
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
macro_line|#endif /* _S390_SEMBUF_H */
eof
