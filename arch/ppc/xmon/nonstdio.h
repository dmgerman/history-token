multiline_comment|/*&n; * BK Id: SCCS/s.nonstdio.h 1.5 05/17/01 18:14:23 cort&n; */
DECL|typedef|FILE
r_typedef
r_int
id|FILE
suffix:semicolon
r_extern
id|FILE
op_star
id|xmon_stdin
comma
op_star
id|xmon_stdout
suffix:semicolon
DECL|macro|EOF
mdefine_line|#define EOF&t;(-1)
DECL|macro|stdin
mdefine_line|#define stdin&t;xmon_stdin
DECL|macro|stdout
mdefine_line|#define stdout&t;xmon_stdout
DECL|macro|printf
mdefine_line|#define printf&t;xmon_printf
DECL|macro|fprintf
mdefine_line|#define fprintf&t;xmon_fprintf
DECL|macro|fputs
mdefine_line|#define fputs&t;xmon_fputs
DECL|macro|fgets
mdefine_line|#define fgets&t;xmon_fgets
DECL|macro|putchar
mdefine_line|#define putchar&t;xmon_putchar
DECL|macro|getchar
mdefine_line|#define getchar&t;xmon_getchar
DECL|macro|putc
mdefine_line|#define putc&t;xmon_putc
DECL|macro|getc
mdefine_line|#define getc&t;xmon_getc
DECL|macro|fopen
mdefine_line|#define fopen(n, m)&t;NULL
DECL|macro|fflush
mdefine_line|#define fflush(f)&t;do {} while (0)
DECL|macro|fclose
mdefine_line|#define fclose(f)&t;do {} while (0)
r_extern
r_char
op_star
id|fgets
c_func
(paren
r_char
op_star
comma
r_int
comma
r_void
op_star
)paren
suffix:semicolon
r_extern
r_void
id|xmon_printf
c_func
(paren
r_const
r_char
op_star
comma
dot
dot
dot
)paren
suffix:semicolon
r_extern
r_void
id|xmon_fprintf
c_func
(paren
r_void
op_star
comma
r_const
r_char
op_star
comma
dot
dot
dot
)paren
suffix:semicolon
r_extern
r_void
id|xmon_sprintf
c_func
(paren
r_char
op_star
comma
r_const
r_char
op_star
comma
dot
dot
dot
)paren
suffix:semicolon
DECL|macro|perror
mdefine_line|#define perror(s)&t;printf(&quot;%s: no files!&bslash;n&quot;, (s))
eof
