multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 - 1997, 2000-2004 Silicon Graphics, Inc. All rights reserved.&n; */
macro_line|#ifndef _ASM_IA64_SN_GEO_H
DECL|macro|_ASM_IA64_SN_GEO_H
mdefine_line|#define _ASM_IA64_SN_GEO_H
multiline_comment|/* The geoid_t implementation below is based loosely on the pcfg_t&n;   implementation in sys/SN/promcfg.h. */
multiline_comment|/* Type declaractions */
multiline_comment|/* Size of a geoid_t structure (must be before decl. of geoid_u) */
DECL|macro|GEOID_SIZE
mdefine_line|#define GEOID_SIZE&t;8&t;/* Would 16 be better?  The size can&n;&t;&t;&t;&t;   be different on different platforms. */
DECL|macro|MAX_SLABS
mdefine_line|#define MAX_SLABS&t;0xe&t;/* slabs per module */
DECL|typedef|geo_type_t
r_typedef
r_int
r_char
id|geo_type_t
suffix:semicolon
multiline_comment|/* Fields common to all substructures */
DECL|struct|geo_any_s
r_typedef
r_struct
id|geo_any_s
(brace
DECL|member|module
id|moduleid_t
id|module
suffix:semicolon
multiline_comment|/* The module (box) this h/w lives in */
DECL|member|type
id|geo_type_t
id|type
suffix:semicolon
multiline_comment|/* What type of h/w is named by this geoid_t */
DECL|member|slab
id|slabid_t
id|slab
suffix:semicolon
multiline_comment|/* The logical assembly within the module */
DECL|typedef|geo_any_t
)brace
id|geo_any_t
suffix:semicolon
multiline_comment|/* Additional fields for particular types of hardware */
DECL|struct|geo_node_s
r_typedef
r_struct
id|geo_node_s
(brace
DECL|member|any
id|geo_any_t
id|any
suffix:semicolon
multiline_comment|/* No additional fields needed */
DECL|typedef|geo_node_t
)brace
id|geo_node_t
suffix:semicolon
DECL|struct|geo_rtr_s
r_typedef
r_struct
id|geo_rtr_s
(brace
DECL|member|any
id|geo_any_t
id|any
suffix:semicolon
multiline_comment|/* No additional fields needed */
DECL|typedef|geo_rtr_t
)brace
id|geo_rtr_t
suffix:semicolon
DECL|struct|geo_iocntl_s
r_typedef
r_struct
id|geo_iocntl_s
(brace
DECL|member|any
id|geo_any_t
id|any
suffix:semicolon
multiline_comment|/* No additional fields needed */
DECL|typedef|geo_iocntl_t
)brace
id|geo_iocntl_t
suffix:semicolon
DECL|struct|geo_pcicard_s
r_typedef
r_struct
id|geo_pcicard_s
(brace
DECL|member|any
id|geo_iocntl_t
id|any
suffix:semicolon
DECL|member|bus
r_char
id|bus
suffix:semicolon
multiline_comment|/* Bus/widget number */
DECL|member|slot
r_char
id|slot
suffix:semicolon
multiline_comment|/* PCI slot number */
DECL|typedef|geo_pcicard_t
)brace
id|geo_pcicard_t
suffix:semicolon
multiline_comment|/* Subcomponents of a node */
DECL|struct|geo_cpu_s
r_typedef
r_struct
id|geo_cpu_s
(brace
DECL|member|node
id|geo_node_t
id|node
suffix:semicolon
DECL|member|slice
r_char
id|slice
suffix:semicolon
multiline_comment|/* Which CPU on the node */
DECL|typedef|geo_cpu_t
)brace
id|geo_cpu_t
suffix:semicolon
DECL|struct|geo_mem_s
r_typedef
r_struct
id|geo_mem_s
(brace
DECL|member|node
id|geo_node_t
id|node
suffix:semicolon
DECL|member|membus
r_char
id|membus
suffix:semicolon
multiline_comment|/* The memory bus on the node */
DECL|member|memslot
r_char
id|memslot
suffix:semicolon
multiline_comment|/* The memory slot on the bus */
DECL|typedef|geo_mem_t
)brace
id|geo_mem_t
suffix:semicolon
DECL|union|geoid_u
r_typedef
r_union
id|geoid_u
(brace
DECL|member|any
id|geo_any_t
id|any
suffix:semicolon
DECL|member|node
id|geo_node_t
id|node
suffix:semicolon
DECL|member|iocntl
id|geo_iocntl_t
id|iocntl
suffix:semicolon
DECL|member|pcicard
id|geo_pcicard_t
id|pcicard
suffix:semicolon
DECL|member|rtr
id|geo_rtr_t
id|rtr
suffix:semicolon
DECL|member|cpu
id|geo_cpu_t
id|cpu
suffix:semicolon
DECL|member|mem
id|geo_mem_t
id|mem
suffix:semicolon
DECL|member|padsize
r_char
id|padsize
(braket
id|GEOID_SIZE
)braket
suffix:semicolon
DECL|typedef|geoid_t
)brace
id|geoid_t
suffix:semicolon
multiline_comment|/* Preprocessor macros */
DECL|macro|GEO_MAX_LEN
mdefine_line|#define GEO_MAX_LEN&t;48&t;/* max. formatted length, plus some pad:&n;&t;&t;&t;&t;   module/001c07/slab/5/node/memory/2/slot/4 */
multiline_comment|/* Values for geo_type_t */
DECL|macro|GEO_TYPE_INVALID
mdefine_line|#define GEO_TYPE_INVALID&t;0
DECL|macro|GEO_TYPE_MODULE
mdefine_line|#define GEO_TYPE_MODULE&t;&t;1
DECL|macro|GEO_TYPE_NODE
mdefine_line|#define GEO_TYPE_NODE&t;&t;2
DECL|macro|GEO_TYPE_RTR
mdefine_line|#define GEO_TYPE_RTR&t;&t;3
DECL|macro|GEO_TYPE_IOCNTL
mdefine_line|#define GEO_TYPE_IOCNTL&t;&t;4
DECL|macro|GEO_TYPE_IOCARD
mdefine_line|#define GEO_TYPE_IOCARD&t;&t;5
DECL|macro|GEO_TYPE_CPU
mdefine_line|#define GEO_TYPE_CPU&t;&t;6
DECL|macro|GEO_TYPE_MEM
mdefine_line|#define GEO_TYPE_MEM&t;&t;7
DECL|macro|GEO_TYPE_MAX
mdefine_line|#define GEO_TYPE_MAX&t;&t;(GEO_TYPE_MEM+1)
multiline_comment|/* Parameter for hwcfg_format_geoid_compt() */
DECL|macro|GEO_COMPT_MODULE
mdefine_line|#define GEO_COMPT_MODULE&t;1
DECL|macro|GEO_COMPT_SLAB
mdefine_line|#define GEO_COMPT_SLAB&t;&t;2
DECL|macro|GEO_COMPT_IOBUS
mdefine_line|#define GEO_COMPT_IOBUS&t;&t;3
DECL|macro|GEO_COMPT_IOSLOT
mdefine_line|#define GEO_COMPT_IOSLOT&t;4
DECL|macro|GEO_COMPT_CPU
mdefine_line|#define GEO_COMPT_CPU&t;&t;5
DECL|macro|GEO_COMPT_MEMBUS
mdefine_line|#define GEO_COMPT_MEMBUS&t;6
DECL|macro|GEO_COMPT_MEMSLOT
mdefine_line|#define GEO_COMPT_MEMSLOT&t;7
DECL|macro|GEO_INVALID_STR
mdefine_line|#define GEO_INVALID_STR&t;&t;&quot;&lt;invalid&gt;&quot;
DECL|macro|INVALID_NASID
mdefine_line|#define INVALID_NASID           ((nasid_t)-1)
DECL|macro|INVALID_CNODEID
mdefine_line|#define INVALID_CNODEID         ((cnodeid_t)-1)
DECL|macro|INVALID_PNODEID
mdefine_line|#define INVALID_PNODEID         ((pnodeid_t)-1)
DECL|macro|INVALID_SLAB
mdefine_line|#define INVALID_SLAB            (slabid_t)-1
DECL|macro|INVALID_MODULE
mdefine_line|#define INVALID_MODULE          ((moduleid_t)-1)
DECL|macro|INVALID_PARTID
mdefine_line|#define INVALID_PARTID          ((partid_t)-1)
DECL|function|geo_slab
r_static
r_inline
id|slabid_t
id|geo_slab
c_func
(paren
id|geoid_t
id|g
)paren
(brace
r_return
(paren
id|g.any.type
op_eq
id|GEO_TYPE_INVALID
)paren
ques
c_cond
id|INVALID_SLAB
suffix:colon
id|g.any.slab
suffix:semicolon
)brace
DECL|function|geo_module
r_static
r_inline
id|moduleid_t
id|geo_module
c_func
(paren
id|geoid_t
id|g
)paren
(brace
r_return
(paren
id|g.any.type
op_eq
id|GEO_TYPE_INVALID
)paren
ques
c_cond
id|INVALID_MODULE
suffix:colon
id|g.any.module
suffix:semicolon
)brace
r_extern
id|geoid_t
id|cnodeid_get_geoid
c_func
(paren
id|cnodeid_t
id|cnode
)paren
suffix:semicolon
macro_line|#endif /* _ASM_IA64_SN_GEO_H */
eof
