macro_line|#ifndef __ASM_MACH_APIC_H
DECL|macro|__ASM_MACH_APIC_H
mdefine_line|#define __ASM_MACH_APIC_H
multiline_comment|/*&n; * Copyright 2004 James Cleverdon, IBM.&n; * Subject to the GNU Public License, v.2&n; *&n; * Generic APIC sub-arch defines.&n; *&n; * Hacked for x86-64 by James Cleverdon from i386 architecture code by&n; * Martin Bligh, Andi Kleen, James Bottomley, John Stultz, and&n; * James Cleverdon.&n; */
macro_line|#include &lt;asm/genapic.h&gt;
DECL|macro|INT_DELIVERY_MODE
mdefine_line|#define INT_DELIVERY_MODE (genapic-&gt;int_delivery_mode)
DECL|macro|INT_DEST_MODE
mdefine_line|#define INT_DEST_MODE (genapic-&gt;int_dest_mode)
DECL|macro|INT_DELIVERY_DEST
mdefine_line|#define INT_DELIVERY_DEST (genapic-&gt;int_delivery_dest)
DECL|macro|TARGET_CPUS
mdefine_line|#define TARGET_CPUS&t;  (genapic-&gt;target_cpus())
DECL|macro|apic_id_registered
mdefine_line|#define apic_id_registered (genapic-&gt;apic_id_registered)
DECL|macro|init_apic_ldr
mdefine_line|#define init_apic_ldr (genapic-&gt;init_apic_ldr)
DECL|macro|send_IPI_mask
mdefine_line|#define send_IPI_mask (genapic-&gt;send_IPI_mask)
DECL|macro|send_IPI_allbutself
mdefine_line|#define send_IPI_allbutself (genapic-&gt;send_IPI_allbutself)
DECL|macro|send_IPI_all
mdefine_line|#define send_IPI_all (genapic-&gt;send_IPI_all)
DECL|macro|cpu_mask_to_apicid
mdefine_line|#define cpu_mask_to_apicid (genapic-&gt;cpu_mask_to_apicid)
DECL|macro|phys_pkg_id
mdefine_line|#define phys_pkg_id&t;(genapic-&gt;phys_pkg_id)
macro_line|#endif /* __ASM_MACH_APIC_H */
eof
