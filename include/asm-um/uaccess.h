multiline_comment|/* &n; * Copyright (C) 2002 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#ifndef __UM_UACCESS_H
DECL|macro|__UM_UACCESS_H
mdefine_line|#define __UM_UACCESS_H
macro_line|#include &quot;linux/sched.h&quot;
DECL|macro|VERIFY_READ
mdefine_line|#define VERIFY_READ 0
DECL|macro|VERIFY_WRITE
mdefine_line|#define VERIFY_WRITE 1
multiline_comment|/*&n; * The fs value determines whether argument validity checking should be&n; * performed or not.  If get_fs() == USER_DS, checking is performed, with&n; * get_fs() == KERNEL_DS, checking is bypassed.&n; *&n; * For historical reasons, these macros are grossly misnamed.&n; */
DECL|macro|MAKE_MM_SEG
mdefine_line|#define MAKE_MM_SEG(s)&t;((mm_segment_t) { (s) })
DECL|macro|KERNEL_DS
mdefine_line|#define KERNEL_DS&t;MAKE_MM_SEG(0xFFFFFFFF)
DECL|macro|USER_DS
mdefine_line|#define USER_DS&t;&t;MAKE_MM_SEG(TASK_SIZE)
DECL|macro|get_ds
mdefine_line|#define get_ds()&t;(KERNEL_DS)
DECL|macro|get_fs
mdefine_line|#define get_fs()&t;(current_thread_info()-&gt;addr_limit)
DECL|macro|set_fs
mdefine_line|#define set_fs(x)&t;(current_thread_info()-&gt;addr_limit = (x))
DECL|macro|segment_eq
mdefine_line|#define segment_eq(a, b) ((a).seg == (b).seg)
macro_line|#include &quot;um_uaccess.h&quot;
DECL|macro|__copy_from_user
mdefine_line|#define __copy_from_user(to, from, n) copy_from_user(to, from, n)
DECL|macro|__copy_to_user
mdefine_line|#define __copy_to_user(to, from, n) copy_to_user(to, from, n)
DECL|macro|__copy_to_user_inatomic
mdefine_line|#define __copy_to_user_inatomic __copy_to_user
DECL|macro|__copy_from_user_inatomic
mdefine_line|#define __copy_from_user_inatomic __copy_from_user
DECL|macro|__get_user
mdefine_line|#define __get_user(x, ptr) &bslash;&n;({ &bslash;&n;        const __typeof__(ptr) __private_ptr = ptr; &bslash;&n;        __typeof__(*(__private_ptr)) __private_val; &bslash;&n;        int __private_ret = -EFAULT; &bslash;&n;        (x) = 0; &bslash;&n;&t;if (__copy_from_user(&amp;__private_val, (__private_ptr), &bslash;&n;&t;    sizeof(*(__private_ptr))) == 0) {&bslash;&n;        &t;(x) = (__typeof__(*(__private_ptr))) __private_val; &bslash;&n;&t;&t;__private_ret = 0; &bslash;&n;&t;} &bslash;&n;        __private_ret; &bslash;&n;}) 
DECL|macro|get_user
mdefine_line|#define get_user(x, ptr) &bslash;&n;({ &bslash;&n;        const __typeof__((*(ptr))) __user *private_ptr = (ptr); &bslash;&n;        (access_ok(VERIFY_READ, private_ptr, sizeof(*private_ptr)) ? &bslash;&n;&t; __get_user(x, private_ptr) : ((x) = 0, -EFAULT)); &bslash;&n;})
DECL|macro|__put_user
mdefine_line|#define __put_user(x, ptr) &bslash;&n;({ &bslash;&n;        __typeof__(ptr) __private_ptr = ptr; &bslash;&n;        __typeof__(*(__private_ptr)) __private_val; &bslash;&n;        int __private_ret = -EFAULT; &bslash;&n;        __private_val = (__typeof__(*(__private_ptr))) (x); &bslash;&n;        if (__copy_to_user((__private_ptr), &amp;__private_val, &bslash;&n;&t;&t;&t;   sizeof(*(__private_ptr))) == 0) { &bslash;&n;&t;&t;__private_ret = 0; &bslash;&n;&t;} &bslash;&n;        __private_ret; &bslash;&n;})
DECL|macro|put_user
mdefine_line|#define put_user(x, ptr) &bslash;&n;({ &bslash;&n;        __typeof__(*(ptr)) __user *private_ptr = (ptr); &bslash;&n;        (access_ok(VERIFY_WRITE, private_ptr, sizeof(*private_ptr)) ? &bslash;&n;&t; __put_user(x, private_ptr) : -EFAULT); &bslash;&n;})
DECL|macro|strlen_user
mdefine_line|#define strlen_user(str) strnlen_user(str, ~0UL &gt;&gt; 1)
DECL|struct|exception_table_entry
r_struct
id|exception_table_entry
(brace
DECL|member|insn
r_int
r_int
id|insn
suffix:semicolon
DECL|member|fixup
r_int
r_int
id|fixup
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
