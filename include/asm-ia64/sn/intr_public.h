multiline_comment|/* $Id$&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 - 1997, 2000 Silicon Graphics, Inc.&n; * Copyright (C) 2000 by Colin Ngam&n; */
macro_line|#ifndef __SYS_SN_INTR_PUBLIC_H__
DECL|macro|__SYS_SN_INTR_PUBLIC_H__
mdefine_line|#define __SYS_SN_INTR_PUBLIC_H__
multiline_comment|/* REMEMBER: If you change these, the whole world needs to be recompiled.&n; * It would also require changing the hubspl.s code and SN0/intr.c&n; * Currently, the spl code has no support for multiple INTPEND1 masks.&n; */
DECL|macro|N_INTPEND0_MASKS
mdefine_line|#define&t;N_INTPEND0_MASKS&t;1
DECL|macro|N_INTPEND1_MASKS
mdefine_line|#define&t;N_INTPEND1_MASKS&t;1
DECL|macro|INTPEND0_MAXMASK
mdefine_line|#define INTPEND0_MAXMASK&t;(N_INTPEND0_MASKS - 1)
DECL|macro|INTPEND1_MAXMASK
mdefine_line|#define INTPEND1_MAXMASK&t;(N_INTPEND1_MASKS - 1)
macro_line|#include &lt;linux/config.h&gt;
macro_line|#if _LANGUAGE_C
macro_line|#if defined(CONFIG_SGI_IP35) || defined(CONFIG_IA64_SGI_SN1) || defined(CONFIG_IA64_GENERIC)
macro_line|#include &lt;asm/sn/sn1/arch.h&gt;
macro_line|#endif
macro_line|#include &lt;asm/sn/arch.h&gt;
r_struct
id|intr_vecblk_s
suffix:semicolon
multiline_comment|/* defined in asm/sn/intr.h */
multiline_comment|/*&n; * The following are necessary to create the illusion of a CEL&n; * on the IP27 hub.  We&squot;ll add more priority levels soon, but for&n; * now, any interrupt in a particular band effectively does an spl.&n; * These must be in the PDA since they&squot;re different for each processor.&n; * Users of this structure must hold the vector_lock in the appropriate vector&n; * block before modifying the mask arrays.  There&squot;s only one vector block&n; * for each Hub so a lock in the PDA wouldn&squot;t be adequate.&n; */
DECL|struct|hub_intmasks_s
r_typedef
r_struct
id|hub_intmasks_s
(brace
multiline_comment|/*&n;&t; * The masks are stored with the lowest-priority (most inclusive)&n;&t; * in the lowest-numbered masks (i.e., 0, 1, 2...).&n;&t; */
multiline_comment|/* INT_PEND0: */
DECL|member|intpend0_masks
id|hubreg_t
id|intpend0_masks
(braket
id|N_INTPEND0_MASKS
)braket
suffix:semicolon
multiline_comment|/* INT_PEND1: */
DECL|member|intpend1_masks
id|hubreg_t
id|intpend1_masks
(braket
id|N_INTPEND1_MASKS
)braket
suffix:semicolon
multiline_comment|/* INT_PEND0: */
DECL|member|dispatch0
r_struct
id|intr_vecblk_s
op_star
id|dispatch0
suffix:semicolon
multiline_comment|/* INT_PEND1: */
DECL|member|dispatch1
r_struct
id|intr_vecblk_s
op_star
id|dispatch1
suffix:semicolon
DECL|typedef|hub_intmasks_t
)brace
id|hub_intmasks_t
suffix:semicolon
macro_line|#endif /* _LANGUAGE_C */
macro_line|#endif /* __SYS_SN_INTR_PUBLIC_H__ */
eof
