multiline_comment|/*&n; * ELF definitions for 32-bit CPUs&n; */
DECL|macro|ELF_EXEC_PAGESIZE
mdefine_line|#define ELF_EXEC_PAGESIZE&t;4096
macro_line|#ifdef __KERNEL__
multiline_comment|/* 32-bit code is always OK.  Some cpus can do 26-bit, some can&squot;t.  */
DECL|macro|ELF_PROC_OK
mdefine_line|#define ELF_PROC_OK(x)&t;&t;&t;&t;&bslash;&n;&t;((! ((x)-&gt;e_flags &amp; EF_ARM_APCS26))&t;&bslash;&n;&t;|| (elf_hwcap &amp; HWCAP_26BIT))
multiline_comment|/* Old NetWinder binaries were compiled in such a way that the iBCS&n;   heuristic always trips on them.  Until these binaries become uncommon&n;   enough not to care, don&squot;t trust the `ibcs&squot; flag here.  In any case&n;   there is no other ELF system currently supported by iBCS.&n;   @@ Could print a warning message to encourage users to upgrade.  */
DECL|macro|SET_PERSONALITY
mdefine_line|#define SET_PERSONALITY(ex,ibcs2) &bslash;&n;&t;set_personality(((ex).e_flags&amp;EF_ARM_APCS26 ?PER_LINUX :PER_LINUX_32BIT))
macro_line|#endif
eof
