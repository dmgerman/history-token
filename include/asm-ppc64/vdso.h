macro_line|#ifndef __PPC64_VDSO_H__
DECL|macro|__PPC64_VDSO_H__
mdefine_line|#define __PPC64_VDSO_H__
macro_line|#ifdef __KERNEL__
multiline_comment|/* Default link addresses for the vDSOs */
DECL|macro|VDSO32_LBASE
mdefine_line|#define VDSO32_LBASE&t;0
DECL|macro|VDSO64_LBASE
mdefine_line|#define VDSO64_LBASE&t;0
multiline_comment|/* Default map addresses */
DECL|macro|VDSO32_MBASE
mdefine_line|#define VDSO32_MBASE&t;0x100000
DECL|macro|VDSO64_MBASE
mdefine_line|#define VDSO64_MBASE&t;0x100000
DECL|macro|VDSO_VERSION_STRING
mdefine_line|#define VDSO_VERSION_STRING&t;LINUX_2.6.11
multiline_comment|/* Define if 64 bits VDSO has procedure descriptors */
DECL|macro|VDS64_HAS_DESCRIPTORS
macro_line|#undef VDS64_HAS_DESCRIPTORS
macro_line|#ifndef __ASSEMBLY__
r_extern
r_int
r_int
id|vdso64_pages
suffix:semicolon
r_extern
r_int
r_int
id|vdso32_pages
suffix:semicolon
multiline_comment|/* Offsets relative to thread-&gt;vdso_base */
r_extern
r_int
r_int
id|vdso64_rt_sigtramp
suffix:semicolon
r_extern
r_int
r_int
id|vdso32_sigtramp
suffix:semicolon
r_extern
r_int
r_int
id|vdso32_rt_sigtramp
suffix:semicolon
r_extern
r_void
id|vdso_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#else /* __ASSEMBLY__ */
macro_line|#ifdef __VDSO64__
macro_line|#ifdef VDS64_HAS_DESCRIPTORS
DECL|macro|V_FUNCTION_BEGIN
mdefine_line|#define V_FUNCTION_BEGIN(name)&t;&t;&bslash;&n;&t;.globl name;&t;&t;&t;&bslash;&n;        .section &quot;.opd&quot;,&quot;a&quot;;&t;&t;&bslash;&n;        .align 3;&t;&t;&t;&bslash;&n;&t;name:&t;&t;&t;&t;&bslash;&n;&t;.quad .name,.TOC.@tocbase,0;&t;&bslash;&n;&t;.previous;&t;&t;&t;&bslash;&n;&t;.globl .name;&t;&t;&t;&bslash;&n;&t;.type .name,@function; &t;&t;&bslash;&n;&t;.name:&t;&t;&t;&t;&bslash;&n;
DECL|macro|V_FUNCTION_END
mdefine_line|#define V_FUNCTION_END(name)&t;&t;&bslash;&n;&t;.size .name,.-.name;
DECL|macro|V_LOCAL_FUNC
mdefine_line|#define V_LOCAL_FUNC(name) (.name)
macro_line|#else /* VDS64_HAS_DESCRIPTORS */
DECL|macro|V_FUNCTION_BEGIN
mdefine_line|#define V_FUNCTION_BEGIN(name)&t;&t;&bslash;&n;&t;.globl name;&t;&t;&t;&bslash;&n;&t;name:&t;&t;&t;&t;&bslash;&n;
DECL|macro|V_FUNCTION_END
mdefine_line|#define V_FUNCTION_END(name)&t;&t;&bslash;&n;&t;.size name,.-name;
DECL|macro|V_LOCAL_FUNC
mdefine_line|#define V_LOCAL_FUNC(name) (name)
macro_line|#endif /* VDS64_HAS_DESCRIPTORS */
macro_line|#endif /* __VDSO64__ */
macro_line|#ifdef __VDSO32__
DECL|macro|V_FUNCTION_BEGIN
mdefine_line|#define V_FUNCTION_BEGIN(name)&t;&t;&bslash;&n;&t;.globl name;&t;&t;&t;&bslash;&n;&t;.type name,@function; &t;&t;&bslash;&n;&t;name:&t;&t;&t;&t;&bslash;&n;
DECL|macro|V_FUNCTION_END
mdefine_line|#define V_FUNCTION_END(name)&t;&t;&bslash;&n;&t;.size name,.-name;
DECL|macro|V_LOCAL_FUNC
mdefine_line|#define V_LOCAL_FUNC(name) (name)
macro_line|#endif /* __VDSO32__ */
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __PPC64_VDSO_H__ */
eof
