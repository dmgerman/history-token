macro_line|#ifndef _LINUX_SECUREBITS_H
DECL|macro|_LINUX_SECUREBITS_H
mdefine_line|#define _LINUX_SECUREBITS_H 1
DECL|macro|SECUREBITS_DEFAULT
mdefine_line|#define SECUREBITS_DEFAULT 0x00000000
r_extern
r_int
id|securebits
suffix:semicolon
multiline_comment|/* When set UID 0 has no special privileges. When unset, we support&n;   inheritance of root-permissions and suid-root executablew under&n;   compatibility mode. We raise the effective and inheritable bitmasks&n;   *of the executable file* if the effective uid of the new process is&n;   0. If the real uid is 0, we raise the inheritable bitmask of the&n;   executable file. */
DECL|macro|SECURE_NOROOT
mdefine_line|#define SECURE_NOROOT            0
multiline_comment|/* When set, setuid to/from uid 0 does not trigger capability-&quot;fixes&quot;&n;   to be compatible with old programs relying on set*uid to loose&n;   privileges. When unset, setuid doesn&squot;t change privileges. */
DECL|macro|SECURE_NO_SETUID_FIXUP
mdefine_line|#define SECURE_NO_SETUID_FIXUP   2
multiline_comment|/* Each securesetting is implemented using two bits. One bit specify&n;   whether the setting is on or off. The other bit specify whether the&n;   setting is fixed or not. A setting which is fixed cannot be changed&n;   from user-level. */
DECL|macro|issecure
mdefine_line|#define issecure(X) ( (1 &lt;&lt; (X+1)) &amp; SECUREBITS_DEFAULT ? &t;&bslash;&n;&t;&t;      (1 &lt;&lt; (X)) &amp; SECUREBITS_DEFAULT :&t;&t;&bslash;&n;&t;&t;      (1 &lt;&lt; (X)) &amp; securebits )
macro_line|#endif /* !_LINUX_SECUREBITS_H */
eof
