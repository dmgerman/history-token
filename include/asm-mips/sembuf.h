macro_line|#ifndef _ASM_SEMBUF_H
DECL|macro|_ASM_SEMBUF_H
mdefine_line|#define _ASM_SEMBUF_H
multiline_comment|/* &n; * The semid64_ds structure for the MIPS architecture.&n; * Note extra padding because this structure is passed back and forth&n; * between kernel and user space.&n; *&n; * Pad space is left for:&n; * - 2 miscellaneous 64-bit values&n; */
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
)brace
suffix:semicolon
macro_line|#endif /* _ASM_SEMBUF_H */
eof
