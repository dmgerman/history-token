macro_line|#ifndef _LINUX_TIOCL_H
DECL|macro|_LINUX_TIOCL_H
mdefine_line|#define _LINUX_TIOCL_H
DECL|macro|TIOCL_SETSEL
mdefine_line|#define TIOCL_SETSEL&t;2&t;/* set a selection */
DECL|macro|TIOCL_SELCHAR
mdefine_line|#define &t;TIOCL_SELCHAR&t;0&t;/* select characters */
DECL|macro|TIOCL_SELWORD
mdefine_line|#define &t;TIOCL_SELWORD&t;1&t;/* select whole words */
DECL|macro|TIOCL_SELLINE
mdefine_line|#define &t;TIOCL_SELLINE&t;2&t;/* select whole lines */
DECL|macro|TIOCL_SELPOINTER
mdefine_line|#define &t;TIOCL_SELPOINTER&t;3&t;/* show the pointer */
DECL|macro|TIOCL_SELCLEAR
mdefine_line|#define &t;TIOCL_SELCLEAR&t;4&t;/* clear visibility of selection */
DECL|macro|TIOCL_SELMOUSEREPORT
mdefine_line|#define &t;TIOCL_SELMOUSEREPORT&t;16&t;/* report beginning of selection */
DECL|macro|TIOCL_SELBUTTONMASK
mdefine_line|#define &t;TIOCL_SELBUTTONMASK&t;15&t;/* button mask for report */
multiline_comment|/* selection extent */
DECL|struct|tiocl_selection
r_struct
id|tiocl_selection
(brace
DECL|member|xs
r_int
r_int
id|xs
suffix:semicolon
multiline_comment|/* X start */
DECL|member|ys
r_int
r_int
id|ys
suffix:semicolon
multiline_comment|/* Y start */
DECL|member|xe
r_int
r_int
id|xe
suffix:semicolon
multiline_comment|/* X end */
DECL|member|ye
r_int
r_int
id|ye
suffix:semicolon
multiline_comment|/* Y end */
DECL|member|sel_mode
r_int
r_int
id|sel_mode
suffix:semicolon
multiline_comment|/* selection mode */
)brace
suffix:semicolon
DECL|macro|TIOCL_PASTESEL
mdefine_line|#define TIOCL_PASTESEL&t;3&t;/* paste previous selection */
DECL|macro|TIOCL_UNBLANKSCREEN
mdefine_line|#define TIOCL_UNBLANKSCREEN&t;4&t;/* unblank screen */
DECL|macro|TIOCL_SELLOADLUT
mdefine_line|#define TIOCL_SELLOADLUT&t;5
multiline_comment|/* set characters to be considered alphabetic when selecting */
multiline_comment|/* u32[8] bit array, 4 bytes-aligned with type */
multiline_comment|/* these two don&squot;t return a value: they write it back in the type */
DECL|macro|TIOCL_GETSHIFTSTATE
mdefine_line|#define TIOCL_GETSHIFTSTATE&t;6&t;/* write shift state */
DECL|macro|TIOCL_GETMOUSEREPORTING
mdefine_line|#define TIOCL_GETMOUSEREPORTING&t;7&t;/* write whether mouse event are reported */
DECL|macro|TIOCL_SETVESABLANK
mdefine_line|#define TIOCL_SETVESABLANK&t;10&t;/* set vesa blanking mode */
DECL|macro|TIOCL_SETKMSGREDIRECT
mdefine_line|#define TIOCL_SETKMSGREDIRECT&t;11&t;/* restrict kernel messages to a vt */
DECL|macro|TIOCL_GETFGCONSOLE
mdefine_line|#define TIOCL_GETFGCONSOLE&t;12&t;/* get foreground vt */
DECL|macro|TIOCL_SCROLLCONSOLE
mdefine_line|#define TIOCL_SCROLLCONSOLE&t;13&t;/* scroll console */
DECL|macro|TIOCL_BLANKSCREEN
mdefine_line|#define TIOCL_BLANKSCREEN&t;14&t;/* keep screen blank even if a key is pressed */
DECL|macro|TIOCL_BLANKEDSCREEN
mdefine_line|#define TIOCL_BLANKEDSCREEN&t;15&t;/* return which vt was blanked */
macro_line|#endif /* _LINUX_TIOCL_H */
eof
