multiline_comment|/*&n; * Kernel CAPI 2.0 Module&n; * &n; * Copyright 1999 by Carsten Paeth &lt;calle@calle.de&gt;&n; * Copyright 2002 by Kai Germaschewski &lt;kai@germaschewski.name&gt;&n; * &n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/isdn/capilli.h&gt;
macro_line|#ifdef KCAPI_DEBUG
DECL|macro|DBG
mdefine_line|#define DBG(format, arg...) do { &bslash;&n;printk(KERN_DEBUG &quot;%s: &quot; format &quot;&bslash;n&quot; , __FUNCTION__ , ## arg); &bslash;&n;} while (0)
macro_line|#else
DECL|macro|DBG
mdefine_line|#define DBG(format, arg...) /* */
macro_line|#endif
r_enum
(brace
DECL|enumerator|CARD_DETECTED
id|CARD_DETECTED
op_assign
l_int|1
comma
DECL|enumerator|CARD_LOADING
id|CARD_LOADING
op_assign
l_int|2
comma
DECL|enumerator|CARD_RUNNING
id|CARD_RUNNING
op_assign
l_int|3
comma
)brace
suffix:semicolon
r_extern
r_struct
id|list_head
id|capi_drivers
suffix:semicolon
r_extern
id|rwlock_t
id|capi_drivers_list_lock
suffix:semicolon
r_extern
r_struct
id|capi20_appl
op_star
id|capi_applications
(braket
id|CAPI_MAXAPPL
)braket
suffix:semicolon
r_extern
r_struct
id|capi_ctr
op_star
id|capi_cards
(braket
id|CAPI_MAXCONTR
)braket
suffix:semicolon
macro_line|#ifdef CONFIG_PROC_FS
r_void
id|kcapi_proc_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|kcapi_proc_exit
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#else
DECL|function|kcapi_proc_init
r_static
r_inline
r_void
id|kcapi_proc_init
c_func
(paren
r_void
)paren
(brace
)brace
suffix:semicolon
DECL|function|kcapi_proc_exit
r_static
r_inline
r_void
id|kcapi_proc_exit
c_func
(paren
r_void
)paren
(brace
)brace
suffix:semicolon
macro_line|#endif
eof
