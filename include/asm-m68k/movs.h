macro_line|#ifndef  __MOVS_H__
DECL|macro|__MOVS_H__
mdefine_line|#define __MOVS_H__
multiline_comment|/*&n;** movs.h&n;**&n;** Inline assembly macros to generate movs &amp; related instructions&n;*/
multiline_comment|/* Set DFC register value */
DECL|macro|SET_DFC
mdefine_line|#define SET_DFC(x) &bslash;&n;        __asm__ __volatile__ (&quot; movec %0,%/dfc&quot; : : &quot;d&quot; (x));
multiline_comment|/* Get DFC register value */
DECL|macro|GET_DFC
mdefine_line|#define GET_DFC(x) &bslash;&n;        __asm__ __volatile__ (&quot; movec %/dfc, %0&quot; : &quot;=d&quot; (x) : );
multiline_comment|/* Set SFC register value */
DECL|macro|SET_SFC
mdefine_line|#define SET_SFC(x) &bslash;&n;        __asm__ __volatile__ (&quot; movec %0,%/sfc&quot; : : &quot;d&quot; (x));
multiline_comment|/* Get SFC register value */
DECL|macro|GET_SFC
mdefine_line|#define GET_SFC(x) &bslash;&n;        __asm__ __volatile__ (&quot; movec %/sfc, %0&quot; : &quot;=d&quot; (x) : );
DECL|macro|SET_VBR
mdefine_line|#define SET_VBR(x) &bslash;&n;        __asm__ __volatile__ (&quot; movec %0,%/vbr&quot; : : &quot;r&quot; (x));
DECL|macro|GET_VBR
mdefine_line|#define GET_VBR(x) &bslash;&n;        __asm__ __volatile__ (&quot; movec %/vbr, %0&quot; : &quot;=g&quot; (x) : );
multiline_comment|/* Set a byte using the &quot;movs&quot; instruction */
DECL|macro|SET_CONTROL_BYTE
mdefine_line|#define SET_CONTROL_BYTE(addr,value) &bslash;&n;        __asm__ __volatile__ (&quot; movsb %0, %1@&quot; : : &quot;d&quot; (value), &quot;a&quot; (addr));
multiline_comment|/* Get a byte using the &quot;movs&quot; instruction */
DECL|macro|GET_CONTROL_BYTE
mdefine_line|#define GET_CONTROL_BYTE(addr,value) &bslash;&n;        __asm__ __volatile__ (&quot; movsb %1@, %0&quot; : &quot;=d&quot; (value) : &quot;a&quot; (addr));
multiline_comment|/* Set a (long)word using the &quot;movs&quot; instruction */
DECL|macro|SET_CONTROL_WORD
mdefine_line|#define SET_CONTROL_WORD(addr,value) &bslash;&n;        __asm__ __volatile__ (&quot; movsl %0, %1@&quot; : : &quot;d&quot; (value), &quot;a&quot; (addr));
multiline_comment|/* Get a (long)word using the &quot;movs&quot; instruction */
DECL|macro|GET_CONTROL_WORD
mdefine_line|#define GET_CONTROL_WORD(addr,value) &bslash;&n;        __asm__ __volatile__ (&quot; movsl %1@, %0&quot; : &quot;=d&quot; (value) : &quot;a&quot; (addr));
macro_line|#endif
eof
