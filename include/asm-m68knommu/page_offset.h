macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/* This handles the memory map.. */
macro_line|#ifdef CONFIG_COLDFIRE
macro_line|#if defined(CONFIG_SMALL)
DECL|macro|PAGE_OFFSET_RAW
mdefine_line|#define PAGE_OFFSET_RAW&t;&t;0x30020000
macro_line|#elif defined(CONFIG_CFV240)
DECL|macro|PAGE_OFFSET_RAW
mdefine_line|#define PAGE_OFFSET_RAW&t;&t;0x02000000
macro_line|#else
DECL|macro|PAGE_OFFSET_RAW
mdefine_line|#define PAGE_OFFSET_RAW&t;&t;0x00000000
macro_line|#endif
macro_line|#endif
macro_line|#ifdef CONFIG_M68360
DECL|macro|PAGE_OFFSET_RAW
mdefine_line|#define PAGE_OFFSET_RAW     0x00000000
macro_line|#endif
macro_line|#ifdef CONFIG_PILOT
macro_line|#ifdef CONFIG_M68328
DECL|macro|PAGE_OFFSET_RAW
mdefine_line|#define PAGE_OFFSET_RAW&t;&t;0x10000000
macro_line|#endif
macro_line|#ifdef CONFIG_M68EZ328
DECL|macro|PAGE_OFFSET_RAW
mdefine_line|#define PAGE_OFFSET_RAW&t;&t;0x00000000
macro_line|#endif
macro_line|#endif
macro_line|#ifdef CONFIG_UCSIMM
DECL|macro|PAGE_OFFSET_RAW
mdefine_line|#define PAGE_OFFSET_RAW&t;&t;0x00000000
macro_line|#endif
macro_line|#if defined(CONFIG_UCDIMM) || defined(CONFIG_DRAGEN2)
macro_line|#ifdef CONFIG_M68VZ328 
DECL|macro|PAGE_OFFSET_RAW
mdefine_line|#define PAGE_OFFSET_RAW&t;&t;0x00000000
macro_line|#endif /* CONFIG_M68VZ328 */
macro_line|#endif /* CONFIG_UCDIMM */
macro_line|#ifdef CONFIG_M68EZ328ADS
DECL|macro|PAGE_OFFSET_RAW
mdefine_line|#define PAGE_OFFSET_RAW&t;&t;0x00000000
macro_line|#endif
macro_line|#ifdef CONFIG_ALMA_ANS
DECL|macro|PAGE_OFFSET_RAW
mdefine_line|#define PAGE_OFFSET_RAW&t;&t;0x00000000
macro_line|#endif
macro_line|#ifdef CONFIG_M68EN302
DECL|macro|PAGE_OFFSET_RAW
mdefine_line|#define PAGE_OFFSET_RAW&t;&t;0x00000000
macro_line|#endif
eof
