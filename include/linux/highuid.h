macro_line|#ifndef _LINUX_HIGHUID_H
DECL|macro|_LINUX_HIGHUID_H
mdefine_line|#define _LINUX_HIGHUID_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
multiline_comment|/*&n; * general notes:&n; *&n; * CONFIG_UID16 is defined if the given architecture needs to&n; * support backwards compatibility for old system calls.&n; *&n; * kernel code should use uid_t and gid_t at all times when dealing with&n; * kernel-private data.&n; *&n; * old_uid_t and old_gid_t should only be different if CONFIG_UID16 is&n; * defined, else the platform should provide dummy typedefs for them&n; * such that they are equivalent to __kernel_{u,g}id_t.&n; *&n; * uid16_t and gid16_t are used on all architectures. (when dealing&n; * with structures hard coded to 16 bits, such as in filesystems)&n; */
multiline_comment|/*&n; * This is the &quot;overflow&quot; UID and GID. They are used to signify uid/gid&n; * overflow to old programs when they request uid/gid information but are&n; * using the old 16 bit interfaces.&n; * When you run a libc5 program, it will think that all highuid files or&n; * processes are owned by this uid/gid.&n; * The idea is that it&squot;s better to do so than possibly return 0 in lieu of&n; * 65536, etc.&n; */
r_extern
r_int
id|overflowuid
suffix:semicolon
r_extern
r_int
id|overflowgid
suffix:semicolon
r_extern
r_void
id|__bad_uid
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__bad_gid
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|DEFAULT_OVERFLOWUID
mdefine_line|#define DEFAULT_OVERFLOWUID&t;65534
DECL|macro|DEFAULT_OVERFLOWGID
mdefine_line|#define DEFAULT_OVERFLOWGID&t;65534
macro_line|#ifdef CONFIG_UID16
multiline_comment|/* prevent uid mod 65536 effect by returning a default value for high UIDs */
DECL|macro|high2lowuid
mdefine_line|#define high2lowuid(uid) ((uid) &amp; ~0xFFFF ? (old_uid_t)overflowuid : (old_uid_t)(uid))
DECL|macro|high2lowgid
mdefine_line|#define high2lowgid(gid) ((gid) &amp; ~0xFFFF ? (old_gid_t)overflowgid : (old_gid_t)(gid))
multiline_comment|/*&n; * -1 is different in 16 bits than it is in 32 bits&n; * these macros are used by chown(), setreuid(), ...,&n; */
DECL|macro|low2highuid
mdefine_line|#define low2highuid(uid) ((uid) == (old_uid_t)-1 ? (uid_t)-1 : (uid_t)(uid))
DECL|macro|low2highgid
mdefine_line|#define low2highgid(gid) ((gid) == (old_gid_t)-1 ? (gid_t)-1 : (gid_t)(gid))
DECL|macro|__convert_uid
mdefine_line|#define __convert_uid(size, uid) &bslash;&n;&t;(size &gt;= sizeof(uid) ? (uid) : high2lowuid(uid))
DECL|macro|__convert_gid
mdefine_line|#define __convert_gid(size, gid) &bslash;&n;&t;(size &gt;= sizeof(gid) ? (gid) : high2lowgid(gid))
macro_line|#else
DECL|macro|__convert_uid
mdefine_line|#define __convert_uid(size, uid) (uid)
DECL|macro|__convert_gid
mdefine_line|#define __convert_gid(size, gid) (gid)
macro_line|#endif /* !CONFIG_UID16 */
multiline_comment|/* uid/gid input should be always 32bit uid_t */
DECL|macro|SET_UID
mdefine_line|#define SET_UID(var, uid) do { (var) = __convert_uid(sizeof(var), (uid)); } while (0)
DECL|macro|SET_GID
mdefine_line|#define SET_GID(var, gid) do { (var) = __convert_gid(sizeof(var), (gid)); } while (0)
multiline_comment|/*&n; * Everything below this line is needed on all architectures, to deal with&n; * filesystems that only store 16 bits of the UID/GID, etc.&n; */
multiline_comment|/*&n; * This is the UID and GID that will get written to disk if a filesystem&n; * only supports 16-bit UIDs and the kernel has a high UID/GID to write&n; */
r_extern
r_int
id|fs_overflowuid
suffix:semicolon
r_extern
r_int
id|fs_overflowgid
suffix:semicolon
DECL|macro|DEFAULT_FS_OVERFLOWUID
mdefine_line|#define DEFAULT_FS_OVERFLOWUID&t;65534
DECL|macro|DEFAULT_FS_OVERFLOWGID
mdefine_line|#define DEFAULT_FS_OVERFLOWGID&t;65534
multiline_comment|/*&n; * Since these macros are used in architectures that only need limited&n; * 16-bit UID back compatibility, we won&squot;t use old_uid_t and old_gid_t&n; */
DECL|macro|fs_high2lowuid
mdefine_line|#define fs_high2lowuid(uid) ((uid) &amp; ~0xFFFF ? (uid16_t)fs_overflowuid : (uid16_t)(uid))
DECL|macro|fs_high2lowgid
mdefine_line|#define fs_high2lowgid(gid) ((gid) &amp; ~0xFFFF ? (gid16_t)fs_overflowgid : (gid16_t)(gid))
DECL|macro|low_16_bits
mdefine_line|#define low_16_bits(x)&t;((x) &amp; 0xFFFF)
DECL|macro|high_16_bits
mdefine_line|#define high_16_bits(x)&t;(((x) &amp; 0xFFFF0000) &gt;&gt; 16)
macro_line|#endif /* _LINUX_HIGHUID_H */
eof
