multiline_comment|/* $Id$&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * usema/usemaclone-related stuff.&n; *&n; * `Inspired&squot; by IRIX&squot;s sys/usioctl.h&n; *&n; * Mike.&n; */
macro_line|#ifndef _ASM_USIOCTL_H
DECL|macro|_ASM_USIOCTL_H
mdefine_line|#define _ASM_USIOCTL_H
multiline_comment|/* ioctls */
DECL|macro|UIOC
mdefine_line|#define UIOC&t;(&squot;u&squot; &lt;&lt; 16 | &squot;s&squot; &lt;&lt; 8)
DECL|macro|UIOCATTACHSEMA
mdefine_line|#define UIOCATTACHSEMA&t;(UIOC|2)&t;/* attach to sema */
DECL|macro|UIOCBLOCK
mdefine_line|#define UIOCBLOCK&t;(UIOC|3)&t;/* block sync &quot;intr&quot;? */
DECL|macro|UIOCABLOCK
mdefine_line|#define UIOCABLOCK&t;(UIOC|4)&t;/* block async */
DECL|macro|UIOCNOIBLOCK
mdefine_line|#define UIOCNOIBLOCK&t;(UIOC|5)&t;/* IRIX: block sync intr&n;&t;&t;&t;&t;&t;   Linux: block sync nointr */
DECL|macro|UIOCUNBLOCK
mdefine_line|#define UIOCUNBLOCK&t;(UIOC|6)&t;/* unblock sync */
DECL|macro|UIOCAUNBLOCK
mdefine_line|#define UIOCAUNBLOCK&t;(UIOC|7)&t;/* unblock async */
DECL|macro|UIOCINIT
mdefine_line|#define UIOCINIT&t;(UIOC|8)&t;/* init sema (async) */
DECL|struct|usattach_s
r_typedef
r_struct
id|usattach_s
(brace
DECL|member|us_dev
id|dev_t
id|us_dev
suffix:semicolon
multiline_comment|/* attach dev */
DECL|member|us_handle
r_void
op_star
id|us_handle
suffix:semicolon
multiline_comment|/* userland semaphore handle */
DECL|typedef|usattach_t
)brace
id|usattach_t
suffix:semicolon
macro_line|#endif /* _ASM_USIOCTL_H */
eof
