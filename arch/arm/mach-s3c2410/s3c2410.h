multiline_comment|/* arch/arm/mach-s3c2410/s3c2410.h&n; *&n; * Copyright (c) 2004 Simtec Electronics&n; *&t;Ben Dooks &lt;ben@simtec.co.uk&gt;&n; *&n; * Header file for s3c2410 machine directory&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * Modifications:&n; *     18-Aug-2004 BJD  Created initial version&n; *     20-Aug-2004 BJD  Added s3c2410_board struct&n; *     04-Sep-2004 BJD  Added s3c2410_init_uarts() call&n; *     17-Oct-2004 BJD  Moved board out to cpu&n; *     04-Jan-2005 BJD  Changed uart init&n; *     10-Jan-2005 BJD  Removed timer to cpu.h, moved 2410 specific bits here&n; *     14-Jan-2005 BJD  Added s3c2410_init_clocks call&n;*/
macro_line|#ifdef CONFIG_CPU_S3C2410
r_extern
r_int
id|s3c2410_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|s3c2410_map_io
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
id|s3c2410_init_uarts
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
r_extern
r_void
id|s3c2410_init_clocks
c_func
(paren
r_int
id|xtal
)paren
suffix:semicolon
macro_line|#else
DECL|macro|s3c2410_init_clocks
mdefine_line|#define s3c2410_init_clocks NULL
DECL|macro|s3c2410_init_uarts
mdefine_line|#define s3c2410_init_uarts NULL
DECL|macro|s3c2410_map_io
mdefine_line|#define s3c2410_map_io NULL
DECL|macro|s3c2410_init
mdefine_line|#define s3c2410_init NULL
macro_line|#endif
eof
