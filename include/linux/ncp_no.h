macro_line|#ifndef _NCP_NO
DECL|macro|_NCP_NO
mdefine_line|#define _NCP_NO
multiline_comment|/* these define the attribute byte as seen by NCP */
DECL|macro|aRONLY
mdefine_line|#define aRONLY&t;&t;&t;(ntohl(0x01000000))
DECL|macro|aHIDDEN
mdefine_line|#define aHIDDEN&t;&t;&t;(__constant_ntohl(0x02000000))
DECL|macro|aSYSTEM
mdefine_line|#define aSYSTEM&t;&t;&t;(__constant_ntohl(0x04000000))
DECL|macro|aEXECUTE
mdefine_line|#define aEXECUTE&t;&t;(ntohl(0x08000000))
DECL|macro|aDIR
mdefine_line|#define aDIR&t;&t;&t;(ntohl(0x10000000))
DECL|macro|aARCH
mdefine_line|#define aARCH&t;&t;&t;(ntohl(0x20000000))
DECL|macro|aSHARED
mdefine_line|#define aSHARED&t;&t;&t;(ntohl(0x80000000))
DECL|macro|aDONTSUBALLOCATE
mdefine_line|#define aDONTSUBALLOCATE&t;(ntohl(1L&lt;&lt;(11+8)))
DECL|macro|aTRANSACTIONAL
mdefine_line|#define aTRANSACTIONAL&t;&t;(ntohl(1L&lt;&lt;(12+8)))
DECL|macro|aPURGE
mdefine_line|#define aPURGE&t;&t;&t;(ntohl(1L&lt;&lt;(16-8)))
DECL|macro|aRENAMEINHIBIT
mdefine_line|#define aRENAMEINHIBIT&t;&t;(ntohl(1L&lt;&lt;(17-8)))
DECL|macro|aDELETEINHIBIT
mdefine_line|#define aDELETEINHIBIT&t;&t;(ntohl(1L&lt;&lt;(18-8)))
DECL|macro|aDONTCOMPRESS
mdefine_line|#define aDONTCOMPRESS&t;&t;(nothl(1L&lt;&lt;(27-24)))
macro_line|#endif /* _NCP_NO */
eof
