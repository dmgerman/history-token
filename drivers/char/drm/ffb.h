multiline_comment|/* ffb.h -- ffb DRM template customization -*- linux-c -*-&n; */
macro_line|#ifndef __FFB_H__
DECL|macro|__FFB_H__
mdefine_line|#define __FFB_H__
multiline_comment|/* This remains constant for all DRM template files.&n; */
DECL|macro|DRM
mdefine_line|#define DRM(x) ffb_##x
multiline_comment|/* General customization:&n; */
DECL|macro|__HAVE_KERNEL_CTX_SWITCH
mdefine_line|#define __HAVE_KERNEL_CTX_SWITCH&t;1
DECL|macro|__HAVE_RELEASE
mdefine_line|#define __HAVE_RELEASE&t;&t;&t;1
macro_line|#endif
eof
