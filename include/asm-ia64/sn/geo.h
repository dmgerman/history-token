multiline_comment|/* $Id$&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 - 1997, 2000-2003 Silicon Graphics, Inc. All rights reserved.&n; */
macro_line|#ifndef __SYS_GEO_H__
DECL|macro|__SYS_GEO_H__
mdefine_line|#define __SYS_GEO_H__
multiline_comment|/* Include a platform-specific geo.h.  It must define at least:&n; *   geoid_t:&t;&t;Geographic identifier data type&n; *   geo_type_t:&t;Data type for the kind of geoid this is&n; *   GEO_TYPE_xxx:&t;Values for geo_type_t vars, eg. GEO_TYPE_NODE&n; *   GEO_MAX_LEN:&t;The maximum length of a geoid, formatted for printing&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_IA64_SGI_SN2
macro_line|#include &lt;asm/sn/sn2/geo.h&gt;
macro_line|#else
macro_line|#error &lt;&lt;BOMB! need geo.h for this platform &gt;&gt;
macro_line|#endif /* !SN2 &amp;&amp; ... */
multiline_comment|/* Declarations applicable to all platforms */
multiline_comment|/* parameter for hwcfg_format_geoid() */
DECL|macro|GEO_FORMAT_HWGRAPH
mdefine_line|#define GEO_FORMAT_HWGRAPH&t;1
DECL|macro|GEO_FORMAT_BRIEF
mdefine_line|#define GEO_FORMAT_BRIEF&t;2
multiline_comment|/* (the parameter for hwcfg_format_geoid_compt() is defined in the&n; * platform-specific geo.h file) */
multiline_comment|/* Routines for manipulating geoid_t values */
r_extern
id|moduleid_t
id|geo_module
c_func
(paren
id|geoid_t
id|g
)paren
suffix:semicolon
r_extern
id|slabid_t
id|geo_slab
c_func
(paren
id|geoid_t
id|g
)paren
suffix:semicolon
r_extern
id|geo_type_t
id|geo_type
c_func
(paren
id|geoid_t
id|g
)paren
suffix:semicolon
r_extern
r_int
id|geo_valid
c_func
(paren
id|geoid_t
id|g
)paren
suffix:semicolon
r_extern
r_int
id|geo_cmp
c_func
(paren
id|geoid_t
id|g0
comma
id|geoid_t
id|g1
)paren
suffix:semicolon
r_extern
id|geoid_t
id|geo_new
c_func
(paren
id|geo_type_t
id|type
comma
dot
dot
dot
)paren
suffix:semicolon
r_extern
id|geoid_t
id|hwcfg_parse_geoid
c_func
(paren
r_char
op_star
id|buffer
)paren
suffix:semicolon
r_extern
r_void
id|hwcfg_format_geoid
c_func
(paren
r_char
op_star
id|buffer
comma
id|geoid_t
id|m
comma
r_int
id|fmt
)paren
suffix:semicolon
r_extern
r_void
id|hwcfg_format_geoid_compt
c_func
(paren
r_char
op_star
id|buffer
comma
id|geoid_t
id|m
comma
r_int
id|compt
)paren
suffix:semicolon
r_extern
id|geoid_t
id|hwcfg_geo_get_self
c_func
(paren
id|geo_type_t
id|type
)paren
suffix:semicolon
r_extern
id|geoid_t
id|hwcfg_geo_get_by_nasid
c_func
(paren
id|geo_type_t
id|type
comma
id|nasid_t
id|nasid
)paren
suffix:semicolon
macro_line|#endif /* __SYS_GEO_H__ */
eof
