macro_line|#ifndef _MACH_IPI_H
DECL|macro|_MACH_IPI_H
mdefine_line|#define _MACH_IPI_H 1
macro_line|#include &lt;asm/genapic.h&gt;
DECL|macro|send_IPI_mask
mdefine_line|#define send_IPI_mask (genapic-&gt;send_IPI_mask)
DECL|macro|send_IPI_allbutself
mdefine_line|#define send_IPI_allbutself (genapic-&gt;send_IPI_allbutself)
DECL|macro|send_IPI_all
mdefine_line|#define send_IPI_all (genapic-&gt;send_IPI_all)
macro_line|#endif
eof
