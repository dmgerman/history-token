macro_line|#ifndef _ASM_MACH_MMZONE_H
DECL|macro|_ASM_MACH_MMZONE_H
mdefine_line|#define _ASM_MACH_MMZONE_H
macro_line|#include &lt;asm/sn/addrs.h&gt;
macro_line|#include &lt;asm/sn/arch.h&gt;
DECL|macro|pa_to_nid
mdefine_line|#define pa_to_nid(addr)&t;&t;NASID_TO_COMPACT_NODEID(NASID_GET(addr))
macro_line|#endif /* _ASM_MACH_MMZONE_H */
eof
