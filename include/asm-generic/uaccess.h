macro_line|#ifndef _ASM_GENERIC_UACCESS_H_
DECL|macro|_ASM_GENERIC_UACCESS_H_
mdefine_line|#define _ASM_GENERIC_UACCESS_H_
multiline_comment|/*&n; * This macro should be used instead of __get_user() when accessing&n; * values at locations that are not known to be aligned.&n; */
DECL|macro|__get_user_unaligned
mdefine_line|#define __get_user_unaligned(x, ptr)&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__typeof__ (*(ptr)) __x;&t;&t;&t;&t;&t;&bslash;&n;&t;__copy_from_user(&amp;__x, (ptr), sizeof(*(ptr))) ? -EFAULT : 0;&t;&bslash;&n;&t;(x) = _x;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
multiline_comment|/*&n; * This macro should be used instead of __put_user() when accessing&n; * values at locations that are not known to be aligned.&n; */
DECL|macro|__put_user_unaligned
mdefine_line|#define __put_user_unaligned(x, ptr)&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__typeof__ (*(ptr)) __x = (x);&t;&t;&t;&t;&t;&bslash;&n;&t;__copy_to_user((ptr), &amp;__x, sizeof(*(ptr))) ? -EFAULT : 0;&t;&bslash;&n;})
macro_line|#endif /* _ASM_GENERIC_UACCESS_H */
eof
