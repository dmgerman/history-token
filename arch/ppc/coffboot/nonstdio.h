multiline_comment|/*&n; * Copyright (C) Paul Mackerras 1997.&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
DECL|typedef|FILE
r_typedef
r_int
id|FILE
suffix:semicolon
r_extern
id|FILE
op_star
id|stdin
comma
op_star
id|stdout
suffix:semicolon
DECL|macro|NULL
mdefine_line|#define NULL&t;((void *)0)
DECL|macro|EOF
mdefine_line|#define EOF&t;(-1)
DECL|macro|fopen
mdefine_line|#define fopen(n, m)&t;NULL
DECL|macro|fflush
mdefine_line|#define fflush(f)&t;0
DECL|macro|fclose
mdefine_line|#define fclose(f)&t;0
r_extern
r_char
op_star
id|fgets
c_func
(paren
)paren
suffix:semicolon
DECL|macro|perror
mdefine_line|#define perror(s)&t;printf(&quot;%s: no files!&bslash;n&quot;, (s))
eof
