multiline_comment|/* $Id: bsderrno.h,v 1.1 1996/12/26 13:25:21 davem Exp $&n; * bsderrno.h: Error numbers for NetBSD binary compatibility&n; *&n; * Copyright (C) 1996 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef _SPARC64_BSDERRNO_H
DECL|macro|_SPARC64_BSDERRNO_H
mdefine_line|#define _SPARC64_BSDERRNO_H
DECL|macro|BSD_EPERM
mdefine_line|#define BSD_EPERM         1      /* Operation not permitted */
DECL|macro|BSD_ENOENT
mdefine_line|#define BSD_ENOENT        2      /* No such file or directory */
DECL|macro|BSD_ESRCH
mdefine_line|#define BSD_ESRCH         3      /* No such process */
DECL|macro|BSD_EINTR
mdefine_line|#define BSD_EINTR         4      /* Interrupted system call */
DECL|macro|BSD_EIO
mdefine_line|#define BSD_EIO           5      /* Input/output error */
DECL|macro|BSD_ENXIO
mdefine_line|#define BSD_ENXIO         6      /* Device not configured */
DECL|macro|BSD_E2BIG
mdefine_line|#define BSD_E2BIG         7      /* Argument list too long */
DECL|macro|BSD_ENOEXEC
mdefine_line|#define BSD_ENOEXEC       8      /* Exec format error */
DECL|macro|BSD_EBADF
mdefine_line|#define BSD_EBADF         9      /* Bad file descriptor */
DECL|macro|BSD_ECHILD
mdefine_line|#define BSD_ECHILD        10     /* No child processes */
DECL|macro|BSD_EDEADLK
mdefine_line|#define BSD_EDEADLK       11     /* Resource deadlock avoided */
DECL|macro|BSD_ENOMEM
mdefine_line|#define BSD_ENOMEM        12     /* Cannot allocate memory */
DECL|macro|BSD_EACCES
mdefine_line|#define BSD_EACCES        13     /* Permission denied */
DECL|macro|BSD_EFAULT
mdefine_line|#define BSD_EFAULT        14     /* Bad address */
DECL|macro|BSD_ENOTBLK
mdefine_line|#define BSD_ENOTBLK       15     /* Block device required */
DECL|macro|BSD_EBUSY
mdefine_line|#define BSD_EBUSY         16     /* Device busy */
DECL|macro|BSD_EEXIST
mdefine_line|#define BSD_EEXIST        17     /* File exists */
DECL|macro|BSD_EXDEV
mdefine_line|#define BSD_EXDEV         18     /* Cross-device link */
DECL|macro|BSD_ENODEV
mdefine_line|#define BSD_ENODEV        19     /* Operation not supported by device */
DECL|macro|BSD_ENOTDIR
mdefine_line|#define BSD_ENOTDIR       20     /* Not a directory */
DECL|macro|BSD_EISDIR
mdefine_line|#define BSD_EISDIR        21     /* Is a directory */
DECL|macro|BSD_EINVAL
mdefine_line|#define BSD_EINVAL        22     /* Invalid argument */
DECL|macro|BSD_ENFILE
mdefine_line|#define BSD_ENFILE        23     /* Too many open files in system */
DECL|macro|BSD_EMFILE
mdefine_line|#define BSD_EMFILE        24     /* Too many open files */
DECL|macro|BSD_ENOTTY
mdefine_line|#define BSD_ENOTTY        25     /* Inappropriate ioctl for device */
DECL|macro|BSD_ETXTBSY
mdefine_line|#define BSD_ETXTBSY       26     /* Text file busy */
DECL|macro|BSD_EFBIG
mdefine_line|#define BSD_EFBIG         27     /* File too large */
DECL|macro|BSD_ENOSPC
mdefine_line|#define BSD_ENOSPC        28     /* No space left on device */
DECL|macro|BSD_ESPIPE
mdefine_line|#define BSD_ESPIPE        29     /* Illegal seek */
DECL|macro|BSD_EROFS
mdefine_line|#define BSD_EROFS         30     /* Read-only file system */
DECL|macro|BSD_EMLINK
mdefine_line|#define BSD_EMLINK        31     /* Too many links */
DECL|macro|BSD_EPIPE
mdefine_line|#define BSD_EPIPE         32     /* Broken pipe */
DECL|macro|BSD_EDOM
mdefine_line|#define BSD_EDOM          33     /* Numerical argument out of domain */
DECL|macro|BSD_ERANGE
mdefine_line|#define BSD_ERANGE        34     /* Result too large */
DECL|macro|BSD_EAGAIN
mdefine_line|#define BSD_EAGAIN        35     /* Resource temporarily unavailable */
DECL|macro|BSD_EWOULDBLOCK
mdefine_line|#define BSD_EWOULDBLOCK   EAGAIN /* Operation would block */
DECL|macro|BSD_EINPROGRESS
mdefine_line|#define BSD_EINPROGRESS   36     /* Operation now in progress */
DECL|macro|BSD_EALREADY
mdefine_line|#define BSD_EALREADY      37     /* Operation already in progress */
DECL|macro|BSD_ENOTSOCK
mdefine_line|#define BSD_ENOTSOCK      38     /* Socket operation on non-socket */
DECL|macro|BSD_EDESTADDRREQ
mdefine_line|#define BSD_EDESTADDRREQ  39     /* Destination address required */
DECL|macro|BSD_EMSGSIZE
mdefine_line|#define BSD_EMSGSIZE      40     /* Message too long */
DECL|macro|BSD_EPROTOTYPE
mdefine_line|#define BSD_EPROTOTYPE    41     /* Protocol wrong type for socket */
DECL|macro|BSD_ENOPROTOOPT
mdefine_line|#define BSD_ENOPROTOOPT   42     /* Protocol not available */
DECL|macro|BSD_EPROTONOSUPPORT
mdefine_line|#define BSD_EPROTONOSUPPORT  43  /* Protocol not supported */
DECL|macro|BSD_ESOCKTNOSUPPORT
mdefine_line|#define BSD_ESOCKTNOSUPPORT  44  /* Socket type not supported */
DECL|macro|BSD_EOPNOTSUPP
mdefine_line|#define BSD_EOPNOTSUPP    45     /* Operation not supported */
DECL|macro|BSD_EPFNOSUPPORT
mdefine_line|#define BSD_EPFNOSUPPORT  46     /* Protocol family not supported */
DECL|macro|BSD_EAFNOSUPPORT
mdefine_line|#define BSD_EAFNOSUPPORT  47     /* Address family not supported by protocol family */
DECL|macro|BSD_EADDRINUSE
mdefine_line|#define BSD_EADDRINUSE    48     /* Address already in use */
DECL|macro|BSD_EADDRNOTAVAIL
mdefine_line|#define BSD_EADDRNOTAVAIL 49     /* Can&squot;t assign requested address */
DECL|macro|BSD_ENETDOWN
mdefine_line|#define BSD_ENETDOWN      50     /* Network is down */
DECL|macro|BSD_ENETUNREACH
mdefine_line|#define BSD_ENETUNREACH   51     /* Network is unreachable */
DECL|macro|BSD_ENETRESET
mdefine_line|#define BSD_ENETRESET     52     /* Network dropped connection on reset */
DECL|macro|BSD_ECONNABORTED
mdefine_line|#define BSD_ECONNABORTED  53     /* Software caused connection abort */
DECL|macro|BSD_ECONNRESET
mdefine_line|#define BSD_ECONNRESET    54     /* Connection reset by peer */
DECL|macro|BSD_ENOBUFS
mdefine_line|#define BSD_ENOBUFS       55     /* No buffer space available */
DECL|macro|BSD_EISCONN
mdefine_line|#define BSD_EISCONN       56     /* Socket is already connected */
DECL|macro|BSD_ENOTCONN
mdefine_line|#define BSD_ENOTCONN      57     /* Socket is not connected */
DECL|macro|BSD_ESHUTDOWN
mdefine_line|#define BSD_ESHUTDOWN     58     /* Can&squot;t send after socket shutdown */
DECL|macro|BSD_ETOOMANYREFS
mdefine_line|#define BSD_ETOOMANYREFS  59     /* Too many references: can&squot;t splice */
DECL|macro|BSD_ETIMEDOUT
mdefine_line|#define BSD_ETIMEDOUT     60     /* Operation timed out */
DECL|macro|BSD_ECONNREFUSED
mdefine_line|#define BSD_ECONNREFUSED  61     /* Connection refused */
DECL|macro|BSD_ELOOP
mdefine_line|#define BSD_ELOOP         62     /* Too many levels of symbolic links */
DECL|macro|BSD_ENAMETOOLONG
mdefine_line|#define BSD_ENAMETOOLONG  63     /* File name too long */
DECL|macro|BSD_EHOSTDOWN
mdefine_line|#define BSD_EHOSTDOWN     64     /* Host is down */
DECL|macro|BSD_EHOSTUNREACH
mdefine_line|#define BSD_EHOSTUNREACH  65     /* No route to host */
DECL|macro|BSD_ENOTEMPTY
mdefine_line|#define BSD_ENOTEMPTY     66     /* Directory not empty */
DECL|macro|BSD_EPROCLIM
mdefine_line|#define BSD_EPROCLIM      67     /* Too many processes */
DECL|macro|BSD_EUSERS
mdefine_line|#define BSD_EUSERS        68     /* Too many users */
DECL|macro|BSD_EDQUOT
mdefine_line|#define BSD_EDQUOT        69     /* Disc quota exceeded */
DECL|macro|BSD_ESTALE
mdefine_line|#define BSD_ESTALE        70     /* Stale NFS file handle */
DECL|macro|BSD_EREMOTE
mdefine_line|#define BSD_EREMOTE       71     /* Too many levels of remote in path */
DECL|macro|BSD_EBADRPC
mdefine_line|#define BSD_EBADRPC       72     /* RPC struct is bad */
DECL|macro|BSD_ERPCMISMATCH
mdefine_line|#define BSD_ERPCMISMATCH  73     /* RPC version wrong */
DECL|macro|BSD_EPROGUNAVAIL
mdefine_line|#define BSD_EPROGUNAVAIL  74     /* RPC prog. not avail */
DECL|macro|BSD_EPROGMISMATCH
mdefine_line|#define BSD_EPROGMISMATCH 75     /* Program version wrong */
DECL|macro|BSD_EPROCUNAVAIL
mdefine_line|#define BSD_EPROCUNAVAIL  76     /* Bad procedure for program */
DECL|macro|BSD_ENOLCK
mdefine_line|#define BSD_ENOLCK        77     /* No locks available */
DECL|macro|BSD_ENOSYS
mdefine_line|#define BSD_ENOSYS        78     /* Function not implemented */
DECL|macro|BSD_EFTYPE
mdefine_line|#define BSD_EFTYPE        79     /* Inappropriate file type or format */
DECL|macro|BSD_EAUTH
mdefine_line|#define BSD_EAUTH         80     /* Authentication error */
DECL|macro|BSD_ENEEDAUTH
mdefine_line|#define BSD_ENEEDAUTH     81     /* Need authenticator */
DECL|macro|BSD_ELAST
mdefine_line|#define BSD_ELAST         81     /* Must be equal largest errno */
macro_line|#endif /* !(_SPARC64_BSDERRNO_H) */
eof
