multiline_comment|/*&n; * BK Id: SCCS/s.4xx_tlb.h 1.5 05/17/01 18:14:23 cort&n; */
multiline_comment|/*&n; *&n; *    Copyright (c) 1999 Grant Erickson &lt;grant@lcse.umn.edu&gt;&n; *&n; *    Module name: 4xx_tlb.h&n; *&n; *    Description:&n; *      Routines for manipulating the TLB on PowerPC 400-class processors.&n; *&n; */
macro_line|#ifndef __4XX_TLB_H__
DECL|macro|__4XX_TLB_H__
mdefine_line|#define __4XX_TLB_H__
macro_line|#ifdef __cplusplus
r_extern
l_string|&quot;C&quot;
(brace
macro_line|#endif
multiline_comment|/* Function Prototypes */
r_extern
r_void
id|PPC4xx_tlb_pin
c_func
(paren
r_int
r_int
id|va
comma
r_int
r_int
id|pa
comma
r_int
id|pagesz
comma
r_int
id|cache
)paren
suffix:semicolon
r_extern
r_void
id|PPC4xx_tlb_unpin
c_func
(paren
r_int
r_int
id|va
comma
r_int
r_int
id|pa
comma
r_int
id|size
)paren
suffix:semicolon
r_extern
r_void
id|PPC4xx_tlb_flush_all
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|PPC4xx_tlb_flush
c_func
(paren
r_int
r_int
id|va
comma
r_int
id|pid
)paren
suffix:semicolon
macro_line|#ifdef __cplusplus
)brace
macro_line|#endif
macro_line|#endif /* __4XX_TLB_H__ */
eof
