multiline_comment|/* &n; * struct flchip definition&n; * &n; * Contains information about the location and state of a given flash device &n; *&n; * (C) 2000 Red Hat. GPLd.&n; *&n; * $Id: flashchip.h,v 1.4 2000/07/03 12:58:41 dwmw2 Exp $&n; *&n; */
macro_line|#ifndef __MTD_FLASHCHIP_H__
DECL|macro|__MTD_FLASHCHIP_H__
mdefine_line|#define __MTD_FLASHCHIP_H__
multiline_comment|/* For spinlocks. sched.h includes spinlock.h from whichever directory it&n; * happens to be in - so we don&squot;t have to care whether we&squot;re on 2.2, which&n; * has asm/spinlock.h, or 2.4, which has linux/spinlock.h &n; */
macro_line|#include &lt;linux/sched.h&gt;
r_typedef
r_enum
(brace
DECL|enumerator|FL_READY
id|FL_READY
comma
DECL|enumerator|FL_STATUS
id|FL_STATUS
comma
DECL|enumerator|FL_CFI_QUERY
id|FL_CFI_QUERY
comma
DECL|enumerator|FL_JEDEC_QUERY
id|FL_JEDEC_QUERY
comma
DECL|enumerator|FL_ERASING
id|FL_ERASING
comma
DECL|enumerator|FL_ERASE_SUSPENDED
id|FL_ERASE_SUSPENDED
comma
DECL|enumerator|FL_WRITING
id|FL_WRITING
comma
DECL|enumerator|FL_WRITE_SUSPENDED
id|FL_WRITE_SUSPENDED
comma
DECL|enumerator|FL_PM_SUSPENDED
id|FL_PM_SUSPENDED
comma
DECL|enumerator|FL_SYNCING
id|FL_SYNCING
comma
DECL|enumerator|FL_UNLOADING
id|FL_UNLOADING
comma
DECL|enumerator|FL_UNKNOWN
id|FL_UNKNOWN
DECL|typedef|flstate_t
)brace
id|flstate_t
suffix:semicolon
multiline_comment|/* NOTE: confusingly, this can be used to refer to more than one chip at a time, &n;   if they&squot;re interleaved. */
DECL|struct|flchip
r_struct
id|flchip
(brace
DECL|member|start
r_int
r_int
id|start
suffix:semicolon
multiline_comment|/* Offset within the map */
singleline_comment|//&t;unsigned long len;
multiline_comment|/* We omit len for now, because when we group them together&n;&t;   we insist that they&squot;re all of the same size, and the chip size&n;&t;   is held in the next level up. If we get more versatile later,&n;&t;   it&squot;ll make it a damn sight harder to find which chip we want from&n;&t;   a given offset, and we&squot;ll want to add the per-chip length field&n;&t;   back in.&n;&t;*/
DECL|member|state
id|flstate_t
id|state
suffix:semicolon
DECL|member|oldstate
id|flstate_t
id|oldstate
suffix:semicolon
DECL|member|mutex
id|spinlock_t
op_star
id|mutex
suffix:semicolon
DECL|member|_spinlock
id|spinlock_t
id|_spinlock
suffix:semicolon
multiline_comment|/* We do it like this because sometimes they&squot;ll be shared. */
DECL|member|wq
id|wait_queue_head_t
id|wq
suffix:semicolon
multiline_comment|/* Wait on here when we&squot;re waiting for the chip&n;&t;&t;&t;     to be ready */
DECL|member|word_write_time
r_int
id|word_write_time
suffix:semicolon
DECL|member|buffer_write_time
r_int
id|buffer_write_time
suffix:semicolon
DECL|member|erase_time
r_int
id|erase_time
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* __MTD_FLASHCHIP_H__ */
eof
