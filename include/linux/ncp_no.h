macro_line|#ifndef _NCP_NO
DECL|macro|_NCP_NO
mdefine_line|#define _NCP_NO
multiline_comment|/* these define the attribute byte as seen by NCP */
DECL|macro|aRONLY
mdefine_line|#define aRONLY&t;&t;&t;(__constant_cpu_to_le32(1))
DECL|macro|aHIDDEN
mdefine_line|#define aHIDDEN&t;&t;&t;(__constant_cpu_to_le32(2))
DECL|macro|aSYSTEM
mdefine_line|#define aSYSTEM&t;&t;&t;(__constant_cpu_to_le32(4))
DECL|macro|aEXECUTE
mdefine_line|#define aEXECUTE&t;&t;(__constant_cpu_to_le32(8))
DECL|macro|aDIR
mdefine_line|#define aDIR&t;&t;&t;(__constant_cpu_to_le32(0x10))
DECL|macro|aARCH
mdefine_line|#define aARCH&t;&t;&t;(__constant_cpu_to_le32(0x20))
DECL|macro|aSHARED
mdefine_line|#define aSHARED&t;&t;&t;(__constant_cpu_to_le32(0x80))
DECL|macro|aDONTSUBALLOCATE
mdefine_line|#define aDONTSUBALLOCATE&t;(__constant_cpu_to_le32(1L&lt;&lt;11))
DECL|macro|aTRANSACTIONAL
mdefine_line|#define aTRANSACTIONAL&t;&t;(__constant_cpu_to_le32(1L&lt;&lt;12))
DECL|macro|aPURGE
mdefine_line|#define aPURGE&t;&t;&t;(__constant_cpu_to_le32(1L&lt;&lt;16))
DECL|macro|aRENAMEINHIBIT
mdefine_line|#define aRENAMEINHIBIT&t;&t;(__constant_cpu_to_le32(1L&lt;&lt;17))
DECL|macro|aDELETEINHIBIT
mdefine_line|#define aDELETEINHIBIT&t;&t;(__constant_cpu_to_le32(1L&lt;&lt;18))
DECL|macro|aDONTCOMPRESS
mdefine_line|#define aDONTCOMPRESS&t;&t;(__constant_cpu_to_le32(1L&lt;&lt;27))
macro_line|#endif /* _NCP_NO */
eof
