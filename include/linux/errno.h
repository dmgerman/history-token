macro_line|#ifndef _LINUX_ERRNO_H
DECL|macro|_LINUX_ERRNO_H
mdefine_line|#define _LINUX_ERRNO_H
macro_line|#include &lt;asm/errno.h&gt;
macro_line|#ifdef __KERNEL__
multiline_comment|/* Should never be seen by user programs */
DECL|macro|ERESTARTSYS
mdefine_line|#define ERESTARTSYS&t;512
DECL|macro|ERESTARTNOINTR
mdefine_line|#define ERESTARTNOINTR&t;513
DECL|macro|ERESTARTNOHAND
mdefine_line|#define ERESTARTNOHAND&t;514&t;/* restart if no handler.. */
DECL|macro|ENOIOCTLCMD
mdefine_line|#define ENOIOCTLCMD&t;515&t;/* No ioctl command */
multiline_comment|/* Defined for the NFSv3 protocol */
DECL|macro|EBADHANDLE
mdefine_line|#define EBADHANDLE&t;521&t;/* Illegal NFS file handle */
DECL|macro|ENOTSYNC
mdefine_line|#define ENOTSYNC&t;522&t;/* Update synchronization mismatch */
DECL|macro|EBADCOOKIE
mdefine_line|#define EBADCOOKIE&t;523&t;/* Cookie is stale */
DECL|macro|ENOTSUPP
mdefine_line|#define ENOTSUPP&t;524&t;/* Operation is not supported */
DECL|macro|ETOOSMALL
mdefine_line|#define ETOOSMALL&t;525&t;/* Buffer or request is too small */
DECL|macro|ESERVERFAULT
mdefine_line|#define ESERVERFAULT&t;526&t;/* An untranslatable error occurred */
DECL|macro|EBADTYPE
mdefine_line|#define EBADTYPE&t;527&t;/* Type not supported by server */
DECL|macro|EJUKEBOX
mdefine_line|#define EJUKEBOX&t;528&t;/* Request initiated, but will not complete before timeout */
macro_line|#endif
macro_line|#endif
eof
