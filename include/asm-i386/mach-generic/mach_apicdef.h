macro_line|#ifndef _GENAPIC_MACH_APICDEF_H
DECL|macro|_GENAPIC_MACH_APICDEF_H
mdefine_line|#define _GENAPIC_MACH_APICDEF_H 1
macro_line|#ifndef APIC_DEFINITION
macro_line|#include &lt;asm/genapic.h&gt;
DECL|macro|GET_APIC_ID
mdefine_line|#define GET_APIC_ID (genapic-&gt;get_apic_id)
DECL|macro|APIC_ID_MASK
mdefine_line|#define APIC_ID_MASK (genapic-&gt;apic_id_mask)
macro_line|#endif
macro_line|#endif
eof
