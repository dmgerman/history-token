macro_line|#ifndef __LINUX_LTALK_H
DECL|macro|__LINUX_LTALK_H
mdefine_line|#define __LINUX_LTALK_H
DECL|macro|LTALK_HLEN
mdefine_line|#define LTALK_HLEN&t;&t;1
DECL|macro|LTALK_MTU
mdefine_line|#define LTALK_MTU&t;&t;600
DECL|macro|LTALK_ALEN
mdefine_line|#define LTALK_ALEN&t;&t;1
macro_line|#ifdef __KERNEL__
r_extern
r_void
id|ltalk_setup
c_func
(paren
r_struct
id|net_device
op_star
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif
eof
