multiline_comment|/* arch/arm/mach-s3c2410/s3c2440.h&n; *&n; * Copyright (c) 2004-2005 Simtec Electronics&n; *&t;Ben Dooks &lt;ben@simtec.co.uk&gt;&n; *&n; * Header file for s3c2440 cpu support&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * Modifications:&n; *&t;24-Aug-2004 BJD  Start of S3C2440 CPU support&n; *&t;04-Nov-2004 BJD  Added s3c2440_init_uarts()&n; *&t;04-Jan-2005 BJD  Moved uart init to cpu code&n; *&t;10-Jan-2005 BJD  Moved 2440 specific init here&n;*/
macro_line|#ifdef CONFIG_CPU_S3C2440
r_extern
r_int
id|s3c2440_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|s3c2440_map_io
c_func
(paren
r_struct
id|map_desc
op_star
id|mach_desc
comma
r_int
id|size
)paren
suffix:semicolon
r_extern
r_void
id|s3c2440_init_uarts
c_func
(paren
r_struct
id|s3c2410_uartcfg
op_star
id|cfg
comma
r_int
id|no
)paren
suffix:semicolon
macro_line|#else
DECL|macro|s3c2440_init_uarts
mdefine_line|#define s3c2440_init_uarts NULL
DECL|macro|s3c2440_map_io
mdefine_line|#define s3c2440_map_io NULL
DECL|macro|s3c2440_init
mdefine_line|#define s3c2440_init NULL
macro_line|#endif
eof
