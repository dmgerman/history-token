macro_line|#ifndef _ASM_IPCBUF_H
DECL|macro|_ASM_IPCBUF_H
mdefine_line|#define _ASM_IPCBUF_H
multiline_comment|/*&n; * The ipc64_perm structure for alpha architecture.&n; * Note extra padding because this structure is passed back and forth&n; * between kernel and user space.&n; *&n; * Pad space is left for:&n; * - 32-bit seq&n; * - 2 miscellaneous 64-bit values&n; */
DECL|struct|ipc64_perm
r_struct
id|ipc64_perm
(brace
DECL|member|key
id|__kernel_key_t
id|key
suffix:semicolon
DECL|member|uid
id|__kernel_uid_t
id|uid
suffix:semicolon
DECL|member|gid
id|__kernel_gid_t
id|gid
suffix:semicolon
DECL|member|cuid
id|__kernel_uid_t
id|cuid
suffix:semicolon
DECL|member|cgid
id|__kernel_gid_t
id|cgid
suffix:semicolon
DECL|member|mode
id|__kernel_mode_t
id|mode
suffix:semicolon
DECL|member|seq
r_int
r_int
id|seq
suffix:semicolon
DECL|member|__pad1
r_int
r_int
id|__pad1
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
)brace
suffix:semicolon
macro_line|#endif /* _ASM_IPCBUF_H */
eof
