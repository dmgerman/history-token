multiline_comment|/* arch/arm/mach-s3c2410/s3c2410.h&n; *&n; * Copyright (c) 2004 Simtec Electronics&n; * Ben Dooks &lt;ben@simtec.co.uk&gt;&n; *&n; * Header file for s3c2410 machine directory&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * Modifications:&n; *     18-Aug-2004 BJD  Created initial version&n; *     20-Aug-2004 BJD  Added s3c2410_board struct&n; *     04-Sep-2004 BJD  Added s3c2410_init_uarts() call&n; *     17-Oct-2004 BJD  Moved board out to cpu&n; *     04-Jan-2005 BJD  Changed uart init&n;*/
r_extern
r_void
id|s3c2410_map_io
c_func
(paren
r_struct
id|map_desc
op_star
comma
r_int
id|count
)paren
suffix:semicolon
r_extern
r_void
id|s3c2410_init_irq
c_func
(paren
r_void
)paren
suffix:semicolon
r_struct
id|sys_timer
suffix:semicolon
r_extern
r_struct
id|sys_timer
id|s3c2410_timer
suffix:semicolon
eof
