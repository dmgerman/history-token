multiline_comment|/* $Id$&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 - 1997, 2000 Silicon Graphics, Inc.&n; * Copyright (C) 2000 by Colin Ngam&n; */
macro_line|#ifndef _ASM_SN_PIO_H
DECL|macro|_ASM_SN_PIO_H
mdefine_line|#define _ASM_SN_PIO_H
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/sn/sgi.h&gt;
macro_line|#include &lt;asm/sn/iobus.h&gt;
multiline_comment|/*&n; * pioaddr_t&t;- The kernel virtual address that a PIO can be done upon.&n; *&t;&t;  Should probably be (volatile void*) but EVEREST would do PIO&n; *&t;&t;  to long mostly, just cast for other sizes.&n; */
DECL|typedef|pioaddr_t
r_typedef
r_volatile
id|ulong
op_star
id|pioaddr_t
suffix:semicolon
multiline_comment|/*&n; * iopaddr_t&t;- the physical io space relative address (e.g. VME A16S 0x0800).&n; * iosapce_t&t;- specifies the io address space to be mapped/accessed.&n; * piomap_t&t;- the handle returned by pio_alloc() and used with all the pio&n; *&t;&t;  access functions.&n; */
DECL|struct|piomap
r_typedef
r_struct
id|piomap
(brace
DECL|member|pio_bus
id|uint
id|pio_bus
suffix:semicolon
DECL|member|pio_adap
id|uint
id|pio_adap
suffix:semicolon
macro_line|#ifdef IRIX
DECL|member|pio_iospace
id|iospace_t
id|pio_iospace
suffix:semicolon
macro_line|#endif
DECL|member|pio_flag
r_int
id|pio_flag
suffix:semicolon
DECL|member|pio_reg
r_int
id|pio_reg
suffix:semicolon
DECL|member|pio_name
r_char
id|pio_name
(braket
l_int|7
)braket
suffix:semicolon
multiline_comment|/* to identify the mapped device */
DECL|member|pio_next
r_struct
id|piomap
op_star
id|pio_next
suffix:semicolon
multiline_comment|/* dlist to link active piomap&squot;s */
DECL|member|pio_prev
r_struct
id|piomap
op_star
id|pio_prev
suffix:semicolon
multiline_comment|/* for debug and error reporting */
macro_line|#ifdef IRIX
DECL|member|pio_errfunc
r_void
(paren
op_star
id|pio_errfunc
)paren
(paren
)paren
suffix:semicolon
multiline_comment|/* Pointer to an error function */
multiline_comment|/* Used only for piomaps allocated&n;&t;&t;&t;&t;&t;   * in user level vme driver     */
macro_line|#endif
DECL|member|pio_iopmask
id|iopaddr_t
id|pio_iopmask
suffix:semicolon
multiline_comment|/* valid iop address bit mask */
DECL|member|pio_bushandle
id|iobush_t
id|pio_bushandle
suffix:semicolon
multiline_comment|/* bus-level handle */
DECL|typedef|piomap_t
)brace
id|piomap_t
suffix:semicolon
multiline_comment|/* Macro to get/set PIO error function */
DECL|macro|pio_seterrf
mdefine_line|#define&t;pio_seterrf(p,f)&t;(p)-&gt;pio_errfunc = (f)
DECL|macro|pio_geterrf
mdefine_line|#define&t;pio_geterrf(p)&t;&t;(p)-&gt;pio_errfunc
multiline_comment|/*&n; * pio_mapalloc() - allocates a handle that specifies a mapping from kernel&n; *&t;&t;    virtual to io space. The returned handle piomap is used&n; *&t;&t;    with the access functions to make sure that the mapping&n; *&t;&t;    to the iospace exists.&n; * pio_mapfree()  - frees the mapping as specified in the piomap handle.&n; * pio_mapaddr()  - returns the kv address that maps to piomap&squot;ed io address.&n; */
macro_line|#ifdef IRIX
r_extern
id|piomap_t
op_star
id|pio_mapalloc
c_func
(paren
id|uint
comma
id|uint
comma
id|iospace_t
op_star
comma
r_int
comma
r_char
op_star
)paren
suffix:semicolon
r_extern
r_void
id|pio_mapfree
c_func
(paren
id|piomap_t
op_star
)paren
suffix:semicolon
r_extern
id|caddr_t
id|pio_mapaddr
c_func
(paren
id|piomap_t
op_star
comma
id|iopaddr_t
)paren
suffix:semicolon
r_extern
id|piomap_t
op_star
id|pio_ioaddr
c_func
(paren
r_int
comma
id|iobush_t
comma
id|iopaddr_t
comma
id|piomap_t
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * PIO access functions.&n; */
r_extern
r_int
id|pio_badaddr
c_func
(paren
id|piomap_t
op_star
comma
id|iopaddr_t
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|pio_badaddr_val
c_func
(paren
id|piomap_t
op_star
comma
id|iopaddr_t
comma
r_int
comma
r_void
op_star
)paren
suffix:semicolon
r_extern
r_int
id|pio_wbadaddr
c_func
(paren
id|piomap_t
op_star
comma
id|iopaddr_t
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|pio_wbadaddr_val
c_func
(paren
id|piomap_t
op_star
comma
id|iopaddr_t
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|pio_bcopyin
c_func
(paren
id|piomap_t
op_star
comma
id|iopaddr_t
comma
r_void
op_star
comma
r_int
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|pio_bcopyout
c_func
(paren
id|piomap_t
op_star
comma
id|iopaddr_t
comma
r_void
op_star
comma
r_int
comma
r_int
comma
r_int
)paren
suffix:semicolon
multiline_comment|/*&n; * PIO RMW functions using piomap.&n; */
r_extern
r_void
id|pio_orb_rmw
c_func
(paren
id|piomap_t
op_star
comma
id|iopaddr_t
comma
r_int
r_char
)paren
suffix:semicolon
r_extern
r_void
id|pio_orh_rmw
c_func
(paren
id|piomap_t
op_star
comma
id|iopaddr_t
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|pio_orw_rmw
c_func
(paren
id|piomap_t
op_star
comma
id|iopaddr_t
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|pio_andb_rmw
c_func
(paren
id|piomap_t
op_star
comma
id|iopaddr_t
comma
r_int
r_char
)paren
suffix:semicolon
r_extern
r_void
id|pio_andh_rmw
c_func
(paren
id|piomap_t
op_star
comma
id|iopaddr_t
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|pio_andw_rmw
c_func
(paren
id|piomap_t
op_star
comma
id|iopaddr_t
comma
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/*&n; * Old RMW function interface&n; */
r_extern
r_void
id|orb_rmw
c_func
(paren
r_volatile
r_void
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|orh_rmw
c_func
(paren
r_volatile
r_void
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|orw_rmw
c_func
(paren
r_volatile
r_void
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|andb_rmw
c_func
(paren
r_volatile
r_void
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|andh_rmw
c_func
(paren
r_volatile
r_void
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|andw_rmw
c_func
(paren
r_volatile
r_void
op_star
comma
r_int
r_int
)paren
suffix:semicolon
macro_line|#endif&t;/* IRIX */
multiline_comment|/*&n; * piomap_t type defines&n; */
DECL|macro|PIOMAP_NTYPES
mdefine_line|#define PIOMAP_NTYPES&t;7
DECL|macro|PIOMAP_A16N
mdefine_line|#define PIOMAP_A16N&t;VME_A16NP
DECL|macro|PIOMAP_A16S
mdefine_line|#define PIOMAP_A16S&t;VME_A16S
DECL|macro|PIOMAP_A24N
mdefine_line|#define PIOMAP_A24N&t;VME_A24NP
DECL|macro|PIOMAP_A24S
mdefine_line|#define PIOMAP_A24S&t;VME_A24S
DECL|macro|PIOMAP_A32N
mdefine_line|#define PIOMAP_A32N&t;VME_A32NP
DECL|macro|PIOMAP_A32S
mdefine_line|#define PIOMAP_A32S&t;VME_A32S
DECL|macro|PIOMAP_A64
mdefine_line|#define PIOMAP_A64&t;6
DECL|macro|PIOMAP_EISA_IO
mdefine_line|#define PIOMAP_EISA_IO&t;0
DECL|macro|PIOMAP_EISA_MEM
mdefine_line|#define PIOMAP_EISA_MEM&t;1
DECL|macro|PIOMAP_PCI_IO
mdefine_line|#define PIOMAP_PCI_IO&t;0
DECL|macro|PIOMAP_PCI_MEM
mdefine_line|#define PIOMAP_PCI_MEM&t;1
DECL|macro|PIOMAP_PCI_CFG
mdefine_line|#define PIOMAP_PCI_CFG&t;2
DECL|macro|PIOMAP_PCI_ID
mdefine_line|#define PIOMAP_PCI_ID&t;3
multiline_comment|/* IBUS piomap types */
DECL|macro|PIOMAP_FCI
mdefine_line|#define PIOMAP_FCI&t;0
multiline_comment|/* dang gio piomap types */
DECL|macro|PIOMAP_GIO32
mdefine_line|#define&t;PIOMAP_GIO32&t;0
DECL|macro|PIOMAP_GIO64
mdefine_line|#define&t;PIOMAP_GIO64&t;1
DECL|macro|ET_MEM
mdefine_line|#define ET_MEM         &t;0
DECL|macro|ET_IO
mdefine_line|#define ET_IO          &t;1
DECL|macro|LAN_RAM
mdefine_line|#define LAN_RAM         2
DECL|macro|LAN_IO
mdefine_line|#define LAN_IO          3
DECL|macro|PIOREG_NULL
mdefine_line|#define PIOREG_NULL&t;-1
multiline_comment|/* standard flags values for pio_map routines,&n; * including {xtalk,pciio}_piomap calls.&n; * NOTE: try to keep these in step with DMAMAP flags.&n; */
DECL|macro|PIOMAP_UNFIXED
mdefine_line|#define PIOMAP_UNFIXED&t;0x0
DECL|macro|PIOMAP_FIXED
mdefine_line|#define PIOMAP_FIXED&t;0x1
DECL|macro|PIOMAP_NOSLEEP
mdefine_line|#define PIOMAP_NOSLEEP&t;0x2
DECL|macro|PIOMAP_INPLACE
mdefine_line|#define&t;PIOMAP_INPLACE&t;0x4
DECL|macro|PIOMAP_FLAGS
mdefine_line|#define&t;PIOMAP_FLAGS&t;0x7
macro_line|#endif&t;/* _ASM_SN_PIO_H */
eof
