macro_line|#ifndef _ATARI_SLM_H
DECL|macro|_ATARI_SLM_H
mdefine_line|#define _ATARI_SLM_H
multiline_comment|/* Atari SLM laser printer specific ioctls */
DECL|macro|SLMIOGSTAT
mdefine_line|#define&t;SLMIOGSTAT&t;0xa100
DECL|macro|SLMIOGPSIZE
mdefine_line|#define&t;SLMIOGPSIZE&t;0xa101
DECL|macro|SLMIOGMFEED
mdefine_line|#define&t;SLMIOGMFEED&t;0xa102
DECL|macro|SLMIORESET
mdefine_line|#define&t;SLMIORESET&t;0xa140
DECL|macro|SLMIOSPSIZE
mdefine_line|#define&t;SLMIOSPSIZE&t;0xa181
DECL|macro|SLMIOSMFEED
mdefine_line|#define&t;SLMIOSMFEED&t;0xa182
multiline_comment|/* Status returning structure (SLMIOGSTAT) */
DECL|struct|SLM_status
r_struct
id|SLM_status
(brace
DECL|member|stat
r_int
id|stat
suffix:semicolon
multiline_comment|/* numeric status code */
DECL|member|str
r_char
id|str
(braket
l_int|40
)braket
suffix:semicolon
multiline_comment|/* status string */
)brace
suffix:semicolon
multiline_comment|/* Paper size structure (SLMIO[GS]PSIZE) */
DECL|struct|SLM_paper_size
r_struct
id|SLM_paper_size
(brace
DECL|member|width
r_int
id|width
suffix:semicolon
DECL|member|height
r_int
id|height
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* _ATARI_SLM_H */
eof
