multiline_comment|/* &n; * Copyright (C) 2001 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#ifndef __2_5_COMPAT_H__
DECL|macro|__2_5_COMPAT_H__
mdefine_line|#define __2_5_COMPAT_H__
macro_line|#include &quot;linux/version.h&quot;
DECL|macro|INIT_CONSOLE
mdefine_line|#define INIT_CONSOLE(dev_name, write_proc, device_proc, setup_proc, f) { &bslash;&n;&t;name :&t;&t;dev_name, &bslash;&n;&t;write :&t;&t;write_proc, &bslash;&n;&t;read :&t;&t;NULL, &bslash;&n;&t;device :&t;device_proc, &bslash;&n;&t;setup :&t;&t;setup_proc, &bslash;&n;&t;flags :&t;&t;f, &bslash;&n;&t;index :&t;&t;-1, &bslash;&n;&t;cflag :&t;&t;0, &bslash;&n;&t;next :&t;&t;NULL &bslash;&n;}
DECL|macro|INIT_QUEUE
mdefine_line|#define INIT_QUEUE(queue, request, lock) blk_init_queue(queue, request, lock)
DECL|macro|INIT_HARDSECT
mdefine_line|#define INIT_HARDSECT(arr, maj, sizes)
DECL|macro|SET_PRI
mdefine_line|#define SET_PRI(task) do ; while(0)
macro_line|#endif
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
