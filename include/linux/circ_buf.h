macro_line|#ifndef _LINUX_CIRC_BUF_H
DECL|macro|_LINUX_CIRC_BUF_H
mdefine_line|#define _LINUX_CIRC_BUF_H 1
DECL|struct|circ_buf
r_struct
id|circ_buf
(brace
DECL|member|buf
r_char
op_star
id|buf
suffix:semicolon
DECL|member|head
r_int
id|head
suffix:semicolon
DECL|member|tail
r_int
id|tail
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Return count in buffer.  */
DECL|macro|CIRC_CNT
mdefine_line|#define CIRC_CNT(head,tail,size) (((head) - (tail)) &amp; ((size)-1))
multiline_comment|/* Return space available, 0..size-1.  We always leave one free char&n;   as a completely full buffer has head == tail, which is the same as&n;   empty.  */
DECL|macro|CIRC_SPACE
mdefine_line|#define CIRC_SPACE(head,tail,size) CIRC_CNT((tail),((head)+1),(size))
multiline_comment|/* Return count up to the end of the buffer.  Carefully avoid&n;   accessing head and tail more than once, so they can change&n;   underneath us without returning inconsistent results.  */
DECL|macro|CIRC_CNT_TO_END
mdefine_line|#define CIRC_CNT_TO_END(head,tail,size) &bslash;&n;&t;({int end = (size) - (tail); &bslash;&n;&t;  int n = ((head) + end) &amp; ((size)-1); &bslash;&n;&t;  n &lt; end ? n : end;})
multiline_comment|/* Return space available up to the end of the buffer.  */
DECL|macro|CIRC_SPACE_TO_END
mdefine_line|#define CIRC_SPACE_TO_END(head,tail,size) &bslash;&n;&t;({int end = (size) - 1 - (head); &bslash;&n;&t;  int n = (end + (tail)) &amp; ((size)-1); &bslash;&n;&t;  n &lt;= end ? n : end+1;})
macro_line|#endif /* _LINUX_CIRC_BUF_H  */
eof
