multiline_comment|/*&n; * include/linux/journal-head.h&n; *&n; * buffer_head fields for JBD&n; *&n; * 27 May 2001 ANdrew Morton &lt;andrewm@uow.edu.au&gt;&n; *&t;Created - pulled out of fs.h&n; */
macro_line|#ifndef JOURNAL_HEAD_H_INCLUDED
DECL|macro|JOURNAL_HEAD_H_INCLUDED
mdefine_line|#define JOURNAL_HEAD_H_INCLUDED
DECL|typedef|tid_t
r_typedef
r_int
r_int
id|tid_t
suffix:semicolon
multiline_comment|/* Unique transaction ID */
DECL|typedef|transaction_t
r_typedef
r_struct
id|transaction_s
id|transaction_t
suffix:semicolon
multiline_comment|/* Compound transaction type */
r_struct
id|buffer_head
suffix:semicolon
DECL|struct|journal_head
r_struct
id|journal_head
(brace
macro_line|#ifndef CONFIG_JBD_UNIFIED_BUFFERS
multiline_comment|/* Points back to our buffer_head. */
DECL|member|b_bh
r_struct
id|buffer_head
op_star
id|b_bh
suffix:semicolon
macro_line|#endif
multiline_comment|/* Reference count - see description in journal.c */
DECL|member|b_jcount
r_int
id|b_jcount
suffix:semicolon
multiline_comment|/* Journaling list for this buffer */
DECL|member|b_jlist
r_int
id|b_jlist
suffix:semicolon
multiline_comment|/* Copy of the buffer data frozen for writing to the log. */
DECL|member|b_frozen_data
r_char
op_star
id|b_frozen_data
suffix:semicolon
multiline_comment|/* Pointer to a saved copy of the buffer containing no&n;           uncommitted deallocation references, so that allocations can&n;           avoid overwriting uncommitted deletes. */
DECL|member|b_committed_data
r_char
op_star
id|b_committed_data
suffix:semicolon
multiline_comment|/* Pointer to the compound transaction which owns this buffer&squot;s&n;           metadata: either the running transaction or the committing&n;           transaction (if there is one).  Only applies to buffers on a&n;           transaction&squot;s data or metadata journaling list. */
multiline_comment|/* Protected by journal_datalist_lock */
DECL|member|b_transaction
id|transaction_t
op_star
id|b_transaction
suffix:semicolon
multiline_comment|/* Pointer to the running compound transaction which is&n;           currently modifying the buffer&squot;s metadata, if there was&n;           already a transaction committing it when the new transaction&n;           touched it. */
DECL|member|b_next_transaction
id|transaction_t
op_star
id|b_next_transaction
suffix:semicolon
multiline_comment|/* Doubly-linked list of buffers on a transaction&squot;s data,&n;           metadata or forget queue. */
multiline_comment|/* Protected by journal_datalist_lock */
DECL|member|b_tnext
DECL|member|b_tprev
r_struct
id|journal_head
op_star
id|b_tnext
comma
op_star
id|b_tprev
suffix:semicolon
multiline_comment|/*&n;&t; * Pointer to the compound transaction against which this buffer&n;&t; * is checkpointed.  Only dirty buffers can be checkpointed.&n;&t; */
multiline_comment|/* Protected by journal_datalist_lock */
DECL|member|b_cp_transaction
id|transaction_t
op_star
id|b_cp_transaction
suffix:semicolon
multiline_comment|/*&n;&t; * Doubly-linked list of buffers still remaining to be flushed&n;&t; * before an old transaction can be checkpointed.&n;&t; */
multiline_comment|/* Protected by journal_datalist_lock */
DECL|member|b_cpnext
DECL|member|b_cpprev
r_struct
id|journal_head
op_star
id|b_cpnext
comma
op_star
id|b_cpprev
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif&t;&t;/* JOURNAL_HEAD_H_INCLUDED */
eof
