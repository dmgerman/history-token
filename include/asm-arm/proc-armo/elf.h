multiline_comment|/*&n; * ELF definitions for 26-bit CPUs&n; */
DECL|macro|ELF_EXEC_PAGESIZE
mdefine_line|#define ELF_EXEC_PAGESIZE&t;32768
macro_line|#ifdef __KERNEL__
multiline_comment|/* We can only execute 26-bit code. */
DECL|macro|ELF_PROC_OK
mdefine_line|#define ELF_PROC_OK(x)&t;&t;&bslash;&n;&t;((x)-&gt;e_flags &amp; EF_ARM_APCS26)
DECL|macro|SET_PERSONALITY
mdefine_line|#define SET_PERSONALITY(ex,ibcs2) set_personality(PER_LINUX)
macro_line|#endif
eof
