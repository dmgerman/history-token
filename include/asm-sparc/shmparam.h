multiline_comment|/* $Id: shmparam.h,v 1.6 1999/12/09 10:32:41 davem Exp $ */
macro_line|#ifndef _ASMSPARC_SHMPARAM_H
DECL|macro|_ASMSPARC_SHMPARAM_H
mdefine_line|#define _ASMSPARC_SHMPARAM_H
r_extern
r_int
id|vac_cache_size
suffix:semicolon
DECL|macro|SHMLBA
mdefine_line|#define SHMLBA (vac_cache_size ? vac_cache_size : &bslash;&n;&t;&t;(sparc_cpu_model == sun4c ? (64 * 1024) : &bslash;&n;&t;&t; (sparc_cpu_model == sun4 ? (128 * 1024) : PAGE_SIZE)))
macro_line|#endif /* _ASMSPARC_SHMPARAM_H */
eof
