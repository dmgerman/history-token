multiline_comment|/*&n; * (C) 2001, 2001 Red Hat, Inc.&n; * GPL&squot;d&n; * $Id: gen_probe.h,v 1.1 2001/09/02 18:50:13 dwmw2 Exp $&n; */
macro_line|#ifndef __LINUX_MTD_GEN_PROBE_H__
DECL|macro|__LINUX_MTD_GEN_PROBE_H__
mdefine_line|#define __LINUX_MTD_GEN_PROBE_H__
macro_line|#include &lt;linux/mtd/flashchip.h&gt;
macro_line|#include &lt;linux/mtd/map.h&gt; 
macro_line|#include &lt;linux/mtd/cfi.h&gt;
DECL|struct|chip_probe
r_struct
id|chip_probe
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|probe_chip
r_int
(paren
op_star
id|probe_chip
)paren
(paren
r_struct
id|map_info
op_star
id|map
comma
id|__u32
id|base
comma
r_struct
id|flchip
op_star
id|chips
comma
r_struct
id|cfi_private
op_star
id|cfi
)paren
suffix:semicolon
)brace
suffix:semicolon
r_struct
id|mtd_info
op_star
id|mtd_do_chip_probe
c_func
(paren
r_struct
id|map_info
op_star
id|map
comma
r_struct
id|chip_probe
op_star
id|cp
)paren
suffix:semicolon
macro_line|#endif /* __LINUX_MTD_GEN_PROBE_H__ */
eof
