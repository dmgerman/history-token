multiline_comment|/****************************************************************************/
multiline_comment|/*&n; *&t;h8300_ne.h -- NE2000 in H8/300H Evalution Board.&n; *      &n; *&t;(C) Copyright 2002, Yoshinori Sato &lt;ysato@users.sourceforge.jp&gt;&n; */
multiline_comment|/****************************************************************************/
macro_line|#ifndef&t;h8300ne_h
DECL|macro|h8300ne_h
mdefine_line|#define&t;h8300ne_h
multiline_comment|/****************************************************************************/
multiline_comment|/* Such a description is OK ? */
DECL|macro|DEPEND_HEADER
mdefine_line|#define DEPEND_HEADER(target) &lt;asm/target/ne.h&gt; 
macro_line|#include DEPEND_HEADER(TARGET)
multiline_comment|/****************************************************************************/
macro_line|#endif&t;/* h8300ne_h */
eof
