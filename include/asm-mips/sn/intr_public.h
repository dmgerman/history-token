multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 - 1997 Silicon Graphics, Inc.&n; */
macro_line|#ifndef __ASM_SN_INTR_PUBLIC_H
DECL|macro|__ASM_SN_INTR_PUBLIC_H
mdefine_line|#define __ASM_SN_INTR_PUBLIC_H
macro_line|#include &lt;asm/sn/arch.h&gt;
multiline_comment|/*&n; * The following are necessary to create the illusion of a CEL on the SN0 hub.&n; * We&squot;ll add more priority levels soon, but for now, any interrupt in a&n; * particular band effectively does an spl.  These must be in the PDA since&n; * they&squot;re different for each processor.  Users of this structure must hold the&n; * vector_lock in the appropriate vector block before modifying the mask arrays.&n; * There&squot;s only one vector block for each Hub so a lock in the PDA wouldn&squot;t be&n; * adequate.&n; */
DECL|struct|hub_intmasks_s
r_struct
id|hub_intmasks_s
(brace
multiline_comment|/*&n;&t; * The masks are stored with the lowest-priority (most inclusive)&n;&t; * in the lowest-numbered masks (i.e., 0, 1, 2...).&n;&t; */
DECL|member|intpend0_masks
id|hubreg_t
id|intpend0_masks
suffix:semicolon
multiline_comment|/* INT_PEND0 */
DECL|member|intpend1_masks
id|hubreg_t
id|intpend1_masks
suffix:semicolon
multiline_comment|/* INT_PEND1 */
)brace
suffix:semicolon
macro_line|#endif /* __ASM_SN_INTR_PUBLIC_H */
eof
