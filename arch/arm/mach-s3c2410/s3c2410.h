multiline_comment|/* arch/arm/mach-s3c2410/s3c2410.h&n; *&n; * Copyright (c) 2004 Simtec Electronics&n; * Ben Dooks &lt;ben@simtec.co.uk&gt;&n; *&n; * Header file for s3c2410 machine directory&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * Modifications:&n; *     18-Aug-2004 BJD  Created initial version&n; *     20-Aug-2004 BJD  Added s3c2410_board struct&n; *     04-Sep-2004 BJD  Added s3c2410_init_uarts() call&n;*/
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
multiline_comment|/* the board structure is used at first initialsation time&n; * to get info such as the devices to register for this&n; * board. This is done because platfrom_add_devices() cannot&n; * be called from the map_io entry.&n; *&n;*/
DECL|struct|s3c2410_board
r_struct
id|s3c2410_board
(brace
DECL|member|devices
r_struct
id|platform_device
op_star
op_star
id|devices
suffix:semicolon
DECL|member|devices_count
r_int
r_int
id|devices_count
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_void
id|s3c2410_set_board
c_func
(paren
r_struct
id|s3c2410_board
op_star
id|board
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
eof
