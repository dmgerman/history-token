macro_line|#ifndef _LINUX_SEM_H
DECL|macro|_LINUX_SEM_H
mdefine_line|#define _LINUX_SEM_H
macro_line|#include &lt;linux/ipc.h&gt;
multiline_comment|/* semop flags */
DECL|macro|SEM_UNDO
mdefine_line|#define SEM_UNDO        0x1000  /* undo the operation on exit */
multiline_comment|/* semctl Command Definitions. */
DECL|macro|GETPID
mdefine_line|#define GETPID  11       /* get sempid */
DECL|macro|GETVAL
mdefine_line|#define GETVAL  12       /* get semval */
DECL|macro|GETALL
mdefine_line|#define GETALL  13       /* get all semval&squot;s */
DECL|macro|GETNCNT
mdefine_line|#define GETNCNT 14       /* get semncnt */
DECL|macro|GETZCNT
mdefine_line|#define GETZCNT 15       /* get semzcnt */
DECL|macro|SETVAL
mdefine_line|#define SETVAL  16       /* set semval */
DECL|macro|SETALL
mdefine_line|#define SETALL  17       /* set all semval&squot;s */
multiline_comment|/* ipcs ctl cmds */
DECL|macro|SEM_STAT
mdefine_line|#define SEM_STAT 18
DECL|macro|SEM_INFO
mdefine_line|#define SEM_INFO 19
multiline_comment|/* Obsolete, used only for backwards compatibility and libc5 compiles */
DECL|struct|semid_ds
r_struct
id|semid_ds
(brace
DECL|member|sem_perm
r_struct
id|ipc_perm
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
DECL|member|sem_base
r_struct
id|sem
op_star
id|sem_base
suffix:semicolon
multiline_comment|/* ptr to first semaphore in array */
DECL|member|sem_pending
r_struct
id|sem_queue
op_star
id|sem_pending
suffix:semicolon
multiline_comment|/* pending operations to be processed */
DECL|member|sem_pending_last
r_struct
id|sem_queue
op_star
op_star
id|sem_pending_last
suffix:semicolon
multiline_comment|/* last pending operation */
DECL|member|undo
r_struct
id|sem_undo
op_star
id|undo
suffix:semicolon
multiline_comment|/* undo requests on this array */
DECL|member|sem_nsems
r_int
r_int
id|sem_nsems
suffix:semicolon
multiline_comment|/* no. of semaphores in array */
)brace
suffix:semicolon
multiline_comment|/* Include the definition of semid64_ds */
macro_line|#include &lt;asm/sembuf.h&gt;
multiline_comment|/* semop system calls takes an array of these. */
DECL|struct|sembuf
r_struct
id|sembuf
(brace
DECL|member|sem_num
r_int
r_int
id|sem_num
suffix:semicolon
multiline_comment|/* semaphore index in array */
DECL|member|sem_op
r_int
id|sem_op
suffix:semicolon
multiline_comment|/* semaphore operation */
DECL|member|sem_flg
r_int
id|sem_flg
suffix:semicolon
multiline_comment|/* operation flags */
)brace
suffix:semicolon
multiline_comment|/* arg for semctl system calls. */
DECL|union|semun
r_union
id|semun
(brace
DECL|member|val
r_int
id|val
suffix:semicolon
multiline_comment|/* value for SETVAL */
DECL|member|buf
r_struct
id|semid_ds
op_star
id|buf
suffix:semicolon
multiline_comment|/* buffer for IPC_STAT &amp; IPC_SET */
DECL|member|array
r_int
r_int
op_star
id|array
suffix:semicolon
multiline_comment|/* array for GETALL &amp; SETALL */
DECL|member|__buf
r_struct
id|seminfo
op_star
id|__buf
suffix:semicolon
multiline_comment|/* buffer for IPC_INFO */
DECL|member|__pad
r_void
op_star
id|__pad
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|seminfo
r_struct
id|seminfo
(brace
DECL|member|semmap
r_int
id|semmap
suffix:semicolon
DECL|member|semmni
r_int
id|semmni
suffix:semicolon
DECL|member|semmns
r_int
id|semmns
suffix:semicolon
DECL|member|semmnu
r_int
id|semmnu
suffix:semicolon
DECL|member|semmsl
r_int
id|semmsl
suffix:semicolon
DECL|member|semopm
r_int
id|semopm
suffix:semicolon
DECL|member|semume
r_int
id|semume
suffix:semicolon
DECL|member|semusz
r_int
id|semusz
suffix:semicolon
DECL|member|semvmx
r_int
id|semvmx
suffix:semicolon
DECL|member|semaem
r_int
id|semaem
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|SEMMNI
mdefine_line|#define SEMMNI  128             /* &lt;= IPCMNI  max # of semaphore identifiers */
DECL|macro|SEMMSL
mdefine_line|#define SEMMSL  250             /* &lt;= 8 000 max num of semaphores per id */
DECL|macro|SEMMNS
mdefine_line|#define SEMMNS  (SEMMNI*SEMMSL) /* &lt;= INT_MAX max # of semaphores in system */
DECL|macro|SEMOPM
mdefine_line|#define SEMOPM  32&t;        /* &lt;= 1 000 max num of ops per semop call */
DECL|macro|SEMVMX
mdefine_line|#define SEMVMX  32767           /* &lt;= 32767 semaphore maximum value */
multiline_comment|/* unused */
DECL|macro|SEMUME
mdefine_line|#define SEMUME  SEMOPM          /* max num of undo entries per process */
DECL|macro|SEMMNU
mdefine_line|#define SEMMNU  SEMMNS          /* num of undo structures system wide */
DECL|macro|SEMAEM
mdefine_line|#define SEMAEM  (SEMVMX &gt;&gt; 1)   /* adjust on exit max value */
DECL|macro|SEMMAP
mdefine_line|#define SEMMAP  SEMMNS          /* # of entries in semaphore map */
DECL|macro|SEMUSZ
mdefine_line|#define SEMUSZ  20&t;&t;/* sizeof struct sem_undo */
macro_line|#ifdef __KERNEL__
multiline_comment|/* One semaphore structure for each semaphore in the system. */
DECL|struct|sem
r_struct
id|sem
(brace
DECL|member|semval
r_int
id|semval
suffix:semicolon
multiline_comment|/* current value */
DECL|member|sempid
r_int
id|sempid
suffix:semicolon
multiline_comment|/* pid of last operation */
)brace
suffix:semicolon
multiline_comment|/* One sem_array data structure for each set of semaphores in the system. */
DECL|struct|sem_array
r_struct
id|sem_array
(brace
DECL|member|sem_perm
r_struct
id|kern_ipc_perm
id|sem_perm
suffix:semicolon
multiline_comment|/* permissions .. see ipc.h */
DECL|member|sem_otime
id|time_t
id|sem_otime
suffix:semicolon
multiline_comment|/* last semop time */
DECL|member|sem_ctime
id|time_t
id|sem_ctime
suffix:semicolon
multiline_comment|/* last change time */
DECL|member|sem_base
r_struct
id|sem
op_star
id|sem_base
suffix:semicolon
multiline_comment|/* ptr to first semaphore in array */
DECL|member|sem_pending
r_struct
id|sem_queue
op_star
id|sem_pending
suffix:semicolon
multiline_comment|/* pending operations to be processed */
DECL|member|sem_pending_last
r_struct
id|sem_queue
op_star
op_star
id|sem_pending_last
suffix:semicolon
multiline_comment|/* last pending operation */
DECL|member|undo
r_struct
id|sem_undo
op_star
id|undo
suffix:semicolon
multiline_comment|/* undo requests on this array */
DECL|member|sem_nsems
r_int
r_int
id|sem_nsems
suffix:semicolon
multiline_comment|/* no. of semaphores in array */
)brace
suffix:semicolon
multiline_comment|/* One queue for each sleeping process in the system. */
DECL|struct|sem_queue
r_struct
id|sem_queue
(brace
DECL|member|next
r_struct
id|sem_queue
op_star
id|next
suffix:semicolon
multiline_comment|/* next entry in the queue */
DECL|member|prev
r_struct
id|sem_queue
op_star
op_star
id|prev
suffix:semicolon
multiline_comment|/* previous entry in the queue, *(q-&gt;prev) == q */
DECL|member|sleeper
r_struct
id|task_struct
op_star
id|sleeper
suffix:semicolon
multiline_comment|/* this process */
DECL|member|undo
r_struct
id|sem_undo
op_star
id|undo
suffix:semicolon
multiline_comment|/* undo structure */
DECL|member|pid
r_int
id|pid
suffix:semicolon
multiline_comment|/* process id of requesting process */
DECL|member|status
r_int
id|status
suffix:semicolon
multiline_comment|/* completion status of operation */
DECL|member|sma
r_struct
id|sem_array
op_star
id|sma
suffix:semicolon
multiline_comment|/* semaphore array for operations */
DECL|member|id
r_int
id|id
suffix:semicolon
multiline_comment|/* internal sem id */
DECL|member|sops
r_struct
id|sembuf
op_star
id|sops
suffix:semicolon
multiline_comment|/* array of pending operations */
DECL|member|nsops
r_int
id|nsops
suffix:semicolon
multiline_comment|/* number of operations */
DECL|member|alter
r_int
id|alter
suffix:semicolon
multiline_comment|/* operation will alter semaphore */
)brace
suffix:semicolon
multiline_comment|/* Each task has a list of undo requests. They are executed automatically&n; * when the process exits.&n; */
DECL|struct|sem_undo
r_struct
id|sem_undo
(brace
DECL|member|proc_next
r_struct
id|sem_undo
op_star
id|proc_next
suffix:semicolon
multiline_comment|/* next entry on this process */
DECL|member|id_next
r_struct
id|sem_undo
op_star
id|id_next
suffix:semicolon
multiline_comment|/* next entry on this semaphore set */
DECL|member|semid
r_int
id|semid
suffix:semicolon
multiline_comment|/* semaphore set identifier */
DECL|member|semadj
r_int
op_star
id|semadj
suffix:semicolon
multiline_comment|/* array of adjustments, one per semaphore */
)brace
suffix:semicolon
id|asmlinkage
r_int
id|sys_semget
(paren
id|key_t
id|key
comma
r_int
id|nsems
comma
r_int
id|semflg
)paren
suffix:semicolon
id|asmlinkage
r_int
id|sys_semop
(paren
r_int
id|semid
comma
r_struct
id|sembuf
op_star
id|sops
comma
r_int
id|nsops
)paren
suffix:semicolon
id|asmlinkage
r_int
id|sys_semctl
(paren
r_int
id|semid
comma
r_int
id|semnum
comma
r_int
id|cmd
comma
r_union
id|semun
id|arg
)paren
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _LINUX_SEM_H */
eof
