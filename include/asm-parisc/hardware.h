macro_line|#ifndef _PARISC_HP_MACHINES_H_ 
DECL|macro|_PARISC_HP_MACHINES_H_
mdefine_line|#define _PARISC_HP_MACHINES_H_ 
DECL|struct|hp_hardware
r_struct
id|hp_hardware
(brace
DECL|member|hw_type
r_int
r_int
id|hw_type
suffix:colon
l_int|5
suffix:semicolon
multiline_comment|/* HPHW_xxx */
DECL|member|hversion
r_int
r_int
id|hversion
suffix:semicolon
DECL|member|sversion
r_int
r_int
id|sversion
suffix:colon
l_int|28
suffix:semicolon
DECL|member|opt
r_int
r_int
id|opt
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|hp_device
r_struct
id|hp_device
(brace
DECL|member|hw_type
r_int
r_int
id|hw_type
suffix:colon
l_int|5
suffix:semicolon
multiline_comment|/* HPHW_xxx */
DECL|member|hversion
r_int
r_int
id|hversion
suffix:semicolon
multiline_comment|/* HP-UX uses  hv_model:12 */
DECL|member|sversion
r_int
r_int
id|sversion
suffix:semicolon
multiline_comment|/* HP-UX uses sv_model:20 sv_opt:8 */
DECL|member|opt
r_int
r_int
id|opt
suffix:semicolon
DECL|member|hversion_rev
r_int
r_int
id|hversion_rev
suffix:semicolon
DECL|member|sversion_rev
r_int
r_int
id|sversion_rev
suffix:semicolon
DECL|member|reference
r_struct
id|hp_hardware
op_star
id|reference
suffix:semicolon
multiline_comment|/* This is a pointer to the&n;                                            reference */
DECL|member|managed
r_int
r_int
id|managed
suffix:semicolon
multiline_comment|/* this is if the device has a driver for it */
DECL|member|hpa
r_void
op_star
id|hpa
suffix:semicolon
macro_line|#ifdef __LP64__
multiline_comment|/* parms for pdc_pat_cell_module() call */
DECL|member|pcell_loc
r_int
r_int
id|pcell_loc
suffix:semicolon
multiline_comment|/* Physical Cell location */
DECL|member|mod_index
r_int
r_int
id|mod_index
suffix:semicolon
multiline_comment|/* PAT specific - Misc Module info */
multiline_comment|/* generic info returned from pdc_pat_cell_module() */
DECL|member|mod_info
r_int
r_int
id|mod_info
suffix:semicolon
multiline_comment|/* PAT specific - Misc Module info */
DECL|member|pmod_loc
r_int
r_int
id|pmod_loc
suffix:semicolon
multiline_comment|/* physical Module location */
DECL|member|mod_path
r_int
r_int
id|mod_path
suffix:semicolon
multiline_comment|/* Module HW path */
macro_line|#endif
)brace
suffix:semicolon
DECL|enum|cpu_type
r_enum
id|cpu_type
(brace
DECL|enumerator|pcx
id|pcx
op_assign
l_int|0
comma
multiline_comment|/* pa7000&t;&t;pa 1.0  */
DECL|enumerator|pcxs
id|pcxs
op_assign
l_int|1
comma
multiline_comment|/* pa7000&t;&t;pa 1.1a */
DECL|enumerator|pcxt
id|pcxt
op_assign
l_int|2
comma
multiline_comment|/* pa7100&t;&t;pa 1.1b */
DECL|enumerator|pcxt_
id|pcxt_
op_assign
l_int|3
comma
multiline_comment|/* pa7200&t;(t&squot;)&t;pa 1.1c */
DECL|enumerator|pcxl
id|pcxl
op_assign
l_int|4
comma
multiline_comment|/* pa7100lc&t;pa 1.1d */
DECL|enumerator|pcxl2
id|pcxl2
op_assign
l_int|5
comma
multiline_comment|/* pa7300lc&t;pa 1.1e */
DECL|enumerator|pcxu
id|pcxu
op_assign
l_int|6
comma
multiline_comment|/* pa8000&t;&t;pa 2.0  */
DECL|enumerator|pcxu_
id|pcxu_
op_assign
l_int|7
comma
multiline_comment|/* pa8200&t;(u+)&t;pa 2.0  */
DECL|enumerator|pcxw
id|pcxw
op_assign
l_int|8
comma
multiline_comment|/* pa8500&t;&t;pa 2.0  */
DECL|enumerator|pcxw_
id|pcxw_
op_assign
l_int|9
multiline_comment|/* pa8600&t;(w+)&t;pa 2.0  */
)brace
suffix:semicolon
r_extern
r_char
op_star
id|cpu_name_version
(braket
)braket
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* mapping from enum cpu_type to strings */
DECL|struct|pa_iodc_driver
r_struct
id|pa_iodc_driver
(brace
DECL|member|hw_type
r_int
r_int
id|hw_type
suffix:colon
l_int|5
suffix:semicolon
multiline_comment|/* HPHW_xxx */
DECL|member|hversion
r_int
r_int
id|hversion
suffix:semicolon
DECL|member|hversion_rev
r_int
r_int
id|hversion_rev
suffix:semicolon
DECL|member|sversion
r_int
r_int
id|sversion
suffix:colon
l_int|28
suffix:semicolon
DECL|member|sversion_rev
r_int
r_int
id|sversion_rev
suffix:semicolon
DECL|member|opt
r_int
r_int
id|opt
suffix:semicolon
DECL|member|check
r_int
r_int
id|check
suffix:semicolon
multiline_comment|/* Components that are significant */
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|version
r_char
op_star
id|version
suffix:semicolon
DECL|member|callback
r_int
(paren
op_star
id|callback
)paren
(paren
r_struct
id|hp_device
op_star
id|d
comma
r_struct
id|pa_iodc_driver
op_star
id|dri
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|DRIVER_CHECK_HWTYPE
mdefine_line|#define DRIVER_CHECK_HWTYPE          1
DECL|macro|DRIVER_CHECK_HVERSION
mdefine_line|#define DRIVER_CHECK_HVERSION        2
DECL|macro|DRIVER_CHECK_SVERSION
mdefine_line|#define DRIVER_CHECK_SVERSION        4
DECL|macro|DRIVER_CHECK_OPT
mdefine_line|#define DRIVER_CHECK_OPT             8
multiline_comment|/* The following two are useless right now */
DECL|macro|DRIVER_CHECK_HVERSION_REV
mdefine_line|#define DRIVER_CHECK_HVERSION_REV   16
DECL|macro|DRIVER_CHECK_SVERSION_REV
mdefine_line|#define DRIVER_CHECK_SVERSION_REV   32
DECL|macro|DRIVER_CHECK_EVERYTHING
mdefine_line|#define DRIVER_CHECK_EVERYTHING     63
DECL|macro|HPHW_NPROC
mdefine_line|#define HPHW_NPROC     0 
DECL|macro|HPHW_MEMORY
mdefine_line|#define HPHW_MEMORY    1       
DECL|macro|HPHW_B_DMA
mdefine_line|#define HPHW_B_DMA     2
DECL|macro|HPHW_OBSOLETE
mdefine_line|#define HPHW_OBSOLETE  3
DECL|macro|HPHW_A_DMA
mdefine_line|#define HPHW_A_DMA     4
DECL|macro|HPHW_A_DIRECT
mdefine_line|#define HPHW_A_DIRECT  5
DECL|macro|HPHW_OTHER
mdefine_line|#define HPHW_OTHER     6
DECL|macro|HPHW_BCPORT
mdefine_line|#define HPHW_BCPORT    7
DECL|macro|HPHW_CIO
mdefine_line|#define HPHW_CIO       8
DECL|macro|HPHW_CONSOLE
mdefine_line|#define HPHW_CONSOLE   9
DECL|macro|HPHW_FIO
mdefine_line|#define HPHW_FIO       10
DECL|macro|HPHW_BA
mdefine_line|#define HPHW_BA        11
DECL|macro|HPHW_IOA
mdefine_line|#define HPHW_IOA       12
DECL|macro|HPHW_BRIDGE
mdefine_line|#define HPHW_BRIDGE    13
DECL|macro|HPHW_FABRIC
mdefine_line|#define HPHW_FABRIC    14
DECL|macro|HPHW_FAULTY
mdefine_line|#define HPHW_FAULTY    31
r_extern
r_struct
id|hp_hardware
id|hp_hardware_list
(braket
)braket
suffix:semicolon
r_char
op_star
id|parisc_getHWtype
c_func
(paren
r_int
r_int
id|hw_type
)paren
suffix:semicolon
multiline_comment|/* Attention: first hversion, then sversion...! */
r_char
op_star
id|parisc_getHWdescription
c_func
(paren
r_int
r_int
id|hw_type
comma
r_int
r_int
id|hversion
comma
multiline_comment|/* have to be long ! */
r_int
r_int
id|sversion
)paren
suffix:semicolon
r_enum
id|cpu_type
id|parisc_get_cpu_type
c_func
(paren
r_int
r_int
id|hversion
)paren
suffix:semicolon
r_extern
r_int
id|register_driver
c_func
(paren
r_struct
id|pa_iodc_driver
op_star
id|driver
)paren
suffix:semicolon
macro_line|#endif
eof
