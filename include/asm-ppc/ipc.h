macro_line|#ifndef __PPC_IPC_H__
DECL|macro|__PPC_IPC_H__
mdefine_line|#define __PPC_IPC_H__
multiline_comment|/* &n; * These are used to wrap system calls on PowerPC.&n; *&n; * See arch/ppc/kernel/syscalls.c for ugly details..&n; */
DECL|struct|ipc_kludge
r_struct
id|ipc_kludge
(brace
DECL|member|msgp
r_struct
id|msgbuf
op_star
id|msgp
suffix:semicolon
DECL|member|msgtyp
r_int
id|msgtyp
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|SEMOP
mdefine_line|#define SEMOP&t;&t; 1
DECL|macro|SEMGET
mdefine_line|#define SEMGET&t;&t; 2
DECL|macro|SEMCTL
mdefine_line|#define SEMCTL&t;&t; 3
DECL|macro|MSGSND
mdefine_line|#define MSGSND&t;&t;11
DECL|macro|MSGRCV
mdefine_line|#define MSGRCV&t;&t;12
DECL|macro|MSGGET
mdefine_line|#define MSGGET&t;&t;13
DECL|macro|MSGCTL
mdefine_line|#define MSGCTL&t;&t;14
DECL|macro|SHMAT
mdefine_line|#define SHMAT&t;&t;21
DECL|macro|SHMDT
mdefine_line|#define SHMDT&t;&t;22
DECL|macro|SHMGET
mdefine_line|#define SHMGET&t;&t;23
DECL|macro|SHMCTL
mdefine_line|#define SHMCTL&t;&t;24
DECL|macro|IPCCALL
mdefine_line|#define IPCCALL(version,op)&t;((version)&lt;&lt;16 | (op))
macro_line|#endif /* __PPC_IPC_H__ */
eof
