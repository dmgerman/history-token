multiline_comment|/*&n; * For boards with physically mapped flash and using &n; * drivers/mtd/maps/physmap.c mapping driver.&n; *&n; * $Id: physmap.h,v 1.2 2004/07/14 17:48:46 dwmw2 Exp $&n; *&n; * Copyright (C) 2003 MontaVista Software Inc.&n; * Author: Jun Sun, jsun@mvista.com or jsun@junsun.net&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; *&n; */
macro_line|#ifndef __LINUX_MTD_PHYSMAP__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#if defined(CONFIG_MTD_PHYSMAP) 
macro_line|#include &lt;linux/mtd/mtd.h&gt;
macro_line|#include &lt;linux/mtd/map.h&gt;
macro_line|#include &lt;linux/mtd/partitions.h&gt;
multiline_comment|/*&n; * The map_info for physmap.  Board can override size, buswidth, phys,&n; * (*set_vpp)(), etc in their initial setup routine.&n; */
r_extern
r_struct
id|map_info
id|physmap_map
suffix:semicolon
multiline_comment|/*&n; * Board needs to specify the exact mapping during their setup time.&n; */
DECL|function|physmap_configure
r_static
r_inline
r_void
id|physmap_configure
c_func
(paren
r_int
r_int
id|addr
comma
r_int
r_int
id|size
comma
r_int
id|buswidth
comma
r_void
(paren
op_star
id|set_vpp
)paren
(paren
r_struct
id|map_info
op_star
comma
r_int
)paren
)paren
(brace
id|physmap_map.phys
op_assign
id|addr
suffix:semicolon
id|physmap_map.size
op_assign
id|size
suffix:semicolon
id|physmap_map.buswidth
op_assign
id|buswidth
suffix:semicolon
id|physmap_map.set_vpp
op_assign
id|set_vpp
suffix:semicolon
)brace
macro_line|#if defined(CONFIG_MTD_PARTITIONS)
multiline_comment|/*&n; * Machines that wish to do flash partition may want to call this function in &n; * their setup routine.  &n; *&n; *&t;physmap_set_partitions(mypartitions, num_parts);&n; *&n; * Note that one can always override this hard-coded partition with &n; * command line partition (you need to enable CONFIG_MTD_CMDLINE_PARTS).&n; */
r_void
id|physmap_set_partitions
c_func
(paren
r_struct
id|mtd_partition
op_star
id|parts
comma
r_int
id|num_parts
)paren
suffix:semicolon
macro_line|#endif /* defined(CONFIG_MTD_PARTITIONS) */
macro_line|#endif /* defined(CONFIG_MTD) */
macro_line|#endif /* __LINUX_MTD_PHYSMAP__ */
eof
