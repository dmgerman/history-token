macro_line|#ifndef __ASM_MACH_MPSPEC_H
DECL|macro|__ASM_MACH_MPSPEC_H
mdefine_line|#define __ASM_MACH_MPSPEC_H
multiline_comment|/*&n; * a maximum of 256 APICs with the current APIC ID architecture.&n; */
DECL|macro|MAX_APICS
mdefine_line|#define MAX_APICS 256
DECL|macro|MAX_IRQ_SOURCES
mdefine_line|#define MAX_IRQ_SOURCES 256
multiline_comment|/* Summit or generic (i.e. installer) kernels need lots of bus entries. */
multiline_comment|/* Maximum 256 PCI busses, plus 1 ISA bus in each of 4 cabinets. */
DECL|macro|MAX_MP_BUSSES
mdefine_line|#define MAX_MP_BUSSES 260
macro_line|#endif /* __ASM_MACH_MPSPEC_H */
eof
