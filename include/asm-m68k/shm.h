macro_line|#ifndef _M68K_SHM_H
DECL|macro|_M68K_SHM_H
mdefine_line|#define _M68K_SHM_H
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/* format of page table entries that correspond to shared memory pages&n;   currently out in swap space (see also mm/swap.c):&n;   bits 0-1 (PAGE_PRESENT) is  = 0&n;   bits 8..2 (SWP_TYPE) are = SHM_SWP_TYPE&n;   bits 31..9 are used like this:&n;   bits 15..9 (SHM_ID) the id of the shared memory segment&n;   bits 30..16 (SHM_IDX) the index of the page within the shared memory segment&n;                    (actually only bits 25..16 get used since SHMMAX is so low)&n;   bit 31 (SHM_READ_ONLY) flag whether the page belongs to a read-only attach&n;*/
multiline_comment|/* on the m68k both bits 0 and 1 must be zero */
multiline_comment|/* format on the sun3 is similar, but bits 30, 31 are set to zero and all&n;   others are reduced by 2. --m */
macro_line|#ifndef CONFIG_SUN3
DECL|macro|SHM_ID_SHIFT
mdefine_line|#define SHM_ID_SHIFT&t;9
macro_line|#else
DECL|macro|SHM_ID_SHIFT
mdefine_line|#define SHM_ID_SHIFT&t;7
macro_line|#endif
DECL|macro|_SHM_ID_BITS
mdefine_line|#define _SHM_ID_BITS&t;7
DECL|macro|SHM_ID_MASK
mdefine_line|#define SHM_ID_MASK&t;((1&lt;&lt;_SHM_ID_BITS)-1)
DECL|macro|SHM_IDX_SHIFT
mdefine_line|#define SHM_IDX_SHIFT&t;(SHM_ID_SHIFT+_SHM_ID_BITS)
DECL|macro|_SHM_IDX_BITS
mdefine_line|#define _SHM_IDX_BITS&t;15
DECL|macro|SHM_IDX_MASK
mdefine_line|#define SHM_IDX_MASK&t;((1&lt;&lt;_SHM_IDX_BITS)-1)
macro_line|#endif /* _M68K_SHM_H */
eof
