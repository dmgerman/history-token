macro_line|#ifndef _PPC64_LMB_H
DECL|macro|_PPC64_LMB_H
mdefine_line|#define _PPC64_LMB_H
multiline_comment|/*&n; * Definitions for talking to the Open Firmware PROM on&n; * Power Macintosh computers.&n; *&n; * Copyright (C) 2001 Peter Bergner, IBM Corp.&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/prom.h&gt;
DECL|macro|MAX_LMB_REGIONS
mdefine_line|#define MAX_LMB_REGIONS 128
DECL|macro|LMB_ALLOC_ANYWHERE
mdefine_line|#define LMB_ALLOC_ANYWHERE&t;0
DECL|struct|lmb_property
r_struct
id|lmb_property
(brace
DECL|member|base
r_int
r_int
id|base
suffix:semicolon
DECL|member|physbase
r_int
r_int
id|physbase
suffix:semicolon
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|lmb_region
r_struct
id|lmb_region
(brace
DECL|member|cnt
r_int
r_int
id|cnt
suffix:semicolon
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
DECL|member|region
r_struct
id|lmb_property
id|region
(braket
id|MAX_LMB_REGIONS
op_plus
l_int|1
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|lmb
r_struct
id|lmb
(brace
DECL|member|debug
r_int
r_int
id|debug
suffix:semicolon
DECL|member|rmo_size
r_int
r_int
id|rmo_size
suffix:semicolon
DECL|member|memory
r_struct
id|lmb_region
id|memory
suffix:semicolon
DECL|member|reserved
r_struct
id|lmb_region
id|reserved
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|lmb
id|lmb
suffix:semicolon
r_extern
r_void
id|__init
id|lmb_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__init
id|lmb_analyze
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|__init
id|lmb_add
c_func
(paren
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
id|__init
id|lmb_reserve
c_func
(paren
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
r_int
id|__init
id|lmb_alloc
c_func
(paren
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
r_int
id|__init
id|lmb_alloc_base
c_func
(paren
r_int
r_int
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
r_int
id|__init
id|lmb_phys_mem_size
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_int
id|__init
id|lmb_end_of_DRAM
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_int
id|__init
id|lmb_abs_to_phys
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|__init
id|lmb_enforce_memory_limit
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|lmb_dump_all
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_int
id|io_hole_start
suffix:semicolon
macro_line|#endif /* _PPC64_LMB_H */
eof
