multiline_comment|/*&n; *  arch/s390/kernel/cpcmd.h&n; *&n; *  S390 version&n; *    Copyright (C) 1999 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Martin Schwidefsky (schwidefsky@de.ibm.com),&n; *               Christian Borntraeger (cborntra@de.ibm.com),&n; */
macro_line|#ifndef __CPCMD__
DECL|macro|__CPCMD__
mdefine_line|#define __CPCMD__
multiline_comment|/*&n; * the caller of __cpcmd has to ensure that the response buffer is below 2 GB&n; */
r_extern
r_void
id|__cpcmd
c_func
(paren
r_char
op_star
id|cmd
comma
r_char
op_star
id|response
comma
r_int
id|rlen
)paren
suffix:semicolon
macro_line|#ifndef __s390x__
DECL|macro|cpcmd
mdefine_line|#define cpcmd __cpcmd
macro_line|#else
r_extern
r_void
id|cpcmd
c_func
(paren
r_char
op_star
id|cmd
comma
r_char
op_star
id|response
comma
r_int
id|rlen
)paren
suffix:semicolon
macro_line|#endif /*__s390x__*/
macro_line|#endif
eof
