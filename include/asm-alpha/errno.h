macro_line|#ifndef _ALPHA_ERRNO_H
DECL|macro|_ALPHA_ERRNO_H
mdefine_line|#define _ALPHA_ERRNO_H
macro_line|#include &lt;asm-generic/errno-base.h&gt;
DECL|macro|EAGAIN
macro_line|#undef&t;EAGAIN&t;&t;&t;/* 11 in errno-base.h */
DECL|macro|EDEADLK
mdefine_line|#define&t;EDEADLK&t;&t;11&t;/* Resource deadlock would occur */
DECL|macro|EAGAIN
mdefine_line|#define&t;EAGAIN&t;&t;35&t;/* Try again */
DECL|macro|EWOULDBLOCK
mdefine_line|#define&t;EWOULDBLOCK&t;EAGAIN&t;/* Operation would block */
DECL|macro|EINPROGRESS
mdefine_line|#define&t;EINPROGRESS&t;36&t;/* Operation now in progress */
DECL|macro|EALREADY
mdefine_line|#define&t;EALREADY&t;37&t;/* Operation already in progress */
DECL|macro|ENOTSOCK
mdefine_line|#define&t;ENOTSOCK&t;38&t;/* Socket operation on non-socket */
DECL|macro|EDESTADDRREQ
mdefine_line|#define&t;EDESTADDRREQ&t;39&t;/* Destination address required */
DECL|macro|EMSGSIZE
mdefine_line|#define&t;EMSGSIZE&t;40&t;/* Message too long */
DECL|macro|EPROTOTYPE
mdefine_line|#define&t;EPROTOTYPE&t;41&t;/* Protocol wrong type for socket */
DECL|macro|ENOPROTOOPT
mdefine_line|#define&t;ENOPROTOOPT&t;42&t;/* Protocol not available */
DECL|macro|EPROTONOSUPPORT
mdefine_line|#define&t;EPROTONOSUPPORT&t;43&t;/* Protocol not supported */
DECL|macro|ESOCKTNOSUPPORT
mdefine_line|#define&t;ESOCKTNOSUPPORT&t;44&t;/* Socket type not supported */
DECL|macro|EOPNOTSUPP
mdefine_line|#define&t;EOPNOTSUPP&t;45&t;/* Operation not supported on transport endpoint */
DECL|macro|EPFNOSUPPORT
mdefine_line|#define&t;EPFNOSUPPORT&t;46&t;/* Protocol family not supported */
DECL|macro|EAFNOSUPPORT
mdefine_line|#define&t;EAFNOSUPPORT&t;47&t;/* Address family not supported by protocol */
DECL|macro|EADDRINUSE
mdefine_line|#define&t;EADDRINUSE&t;48&t;/* Address already in use */
DECL|macro|EADDRNOTAVAIL
mdefine_line|#define&t;EADDRNOTAVAIL&t;49&t;/* Cannot assign requested address */
DECL|macro|ENETDOWN
mdefine_line|#define&t;ENETDOWN&t;50&t;/* Network is down */
DECL|macro|ENETUNREACH
mdefine_line|#define&t;ENETUNREACH&t;51&t;/* Network is unreachable */
DECL|macro|ENETRESET
mdefine_line|#define&t;ENETRESET&t;52&t;/* Network dropped connection because of reset */
DECL|macro|ECONNABORTED
mdefine_line|#define&t;ECONNABORTED&t;53&t;/* Software caused connection abort */
DECL|macro|ECONNRESET
mdefine_line|#define&t;ECONNRESET&t;54&t;/* Connection reset by peer */
DECL|macro|ENOBUFS
mdefine_line|#define&t;ENOBUFS&t;&t;55&t;/* No buffer space available */
DECL|macro|EISCONN
mdefine_line|#define&t;EISCONN&t;&t;56&t;/* Transport endpoint is already connected */
DECL|macro|ENOTCONN
mdefine_line|#define&t;ENOTCONN&t;57&t;/* Transport endpoint is not connected */
DECL|macro|ESHUTDOWN
mdefine_line|#define&t;ESHUTDOWN&t;58&t;/* Cannot send after transport endpoint shutdown */
DECL|macro|ETOOMANYREFS
mdefine_line|#define&t;ETOOMANYREFS&t;59&t;/* Too many references: cannot splice */
DECL|macro|ETIMEDOUT
mdefine_line|#define&t;ETIMEDOUT&t;60&t;/* Connection timed out */
DECL|macro|ECONNREFUSED
mdefine_line|#define&t;ECONNREFUSED&t;61&t;/* Connection refused */
DECL|macro|ELOOP
mdefine_line|#define&t;ELOOP&t;&t;62&t;/* Too many symbolic links encountered */
DECL|macro|ENAMETOOLONG
mdefine_line|#define&t;ENAMETOOLONG&t;63&t;/* File name too long */
DECL|macro|EHOSTDOWN
mdefine_line|#define&t;EHOSTDOWN&t;64&t;/* Host is down */
DECL|macro|EHOSTUNREACH
mdefine_line|#define&t;EHOSTUNREACH&t;65&t;/* No route to host */
DECL|macro|ENOTEMPTY
mdefine_line|#define&t;ENOTEMPTY&t;66&t;/* Directory not empty */
DECL|macro|EUSERS
mdefine_line|#define&t;EUSERS&t;&t;68&t;/* Too many users */
DECL|macro|EDQUOT
mdefine_line|#define&t;EDQUOT&t;&t;69&t;/* Quota exceeded */
DECL|macro|ESTALE
mdefine_line|#define&t;ESTALE&t;&t;70&t;/* Stale NFS file handle */
DECL|macro|EREMOTE
mdefine_line|#define&t;EREMOTE&t;&t;71&t;/* Object is remote */
DECL|macro|ENOLCK
mdefine_line|#define&t;ENOLCK&t;&t;77&t;/* No record locks available */
DECL|macro|ENOSYS
mdefine_line|#define&t;ENOSYS&t;&t;78&t;/* Function not implemented */
DECL|macro|ENOMSG
mdefine_line|#define&t;ENOMSG&t;&t;80&t;/* No message of desired type */
DECL|macro|EIDRM
mdefine_line|#define&t;EIDRM&t;&t;81&t;/* Identifier removed */
DECL|macro|ENOSR
mdefine_line|#define&t;ENOSR&t;&t;82&t;/* Out of streams resources */
DECL|macro|ETIME
mdefine_line|#define&t;ETIME&t;&t;83&t;/* Timer expired */
DECL|macro|EBADMSG
mdefine_line|#define&t;EBADMSG&t;&t;84&t;/* Not a data message */
DECL|macro|EPROTO
mdefine_line|#define&t;EPROTO&t;&t;85&t;/* Protocol error */
DECL|macro|ENODATA
mdefine_line|#define&t;ENODATA&t;&t;86&t;/* No data available */
DECL|macro|ENOSTR
mdefine_line|#define&t;ENOSTR&t;&t;87&t;/* Device not a stream */
DECL|macro|ENOPKG
mdefine_line|#define&t;ENOPKG&t;&t;92&t;/* Package not installed */
DECL|macro|EILSEQ
mdefine_line|#define&t;EILSEQ&t;&t;116&t;/* Illegal byte sequence */
multiline_comment|/* The following are just random noise.. */
DECL|macro|ECHRNG
mdefine_line|#define&t;ECHRNG&t;&t;88&t;/* Channel number out of range */
DECL|macro|EL2NSYNC
mdefine_line|#define&t;EL2NSYNC&t;89&t;/* Level 2 not synchronized */
DECL|macro|EL3HLT
mdefine_line|#define&t;EL3HLT&t;&t;90&t;/* Level 3 halted */
DECL|macro|EL3RST
mdefine_line|#define&t;EL3RST&t;&t;91&t;/* Level 3 reset */
DECL|macro|ELNRNG
mdefine_line|#define&t;ELNRNG&t;&t;93&t;/* Link number out of range */
DECL|macro|EUNATCH
mdefine_line|#define&t;EUNATCH&t;&t;94&t;/* Protocol driver not attached */
DECL|macro|ENOCSI
mdefine_line|#define&t;ENOCSI&t;&t;95&t;/* No CSI structure available */
DECL|macro|EL2HLT
mdefine_line|#define&t;EL2HLT&t;&t;96&t;/* Level 2 halted */
DECL|macro|EBADE
mdefine_line|#define&t;EBADE&t;&t;97&t;/* Invalid exchange */
DECL|macro|EBADR
mdefine_line|#define&t;EBADR&t;&t;98&t;/* Invalid request descriptor */
DECL|macro|EXFULL
mdefine_line|#define&t;EXFULL&t;&t;99&t;/* Exchange full */
DECL|macro|ENOANO
mdefine_line|#define&t;ENOANO&t;&t;100&t;/* No anode */
DECL|macro|EBADRQC
mdefine_line|#define&t;EBADRQC&t;&t;101&t;/* Invalid request code */
DECL|macro|EBADSLT
mdefine_line|#define&t;EBADSLT&t;&t;102&t;/* Invalid slot */
DECL|macro|EDEADLOCK
mdefine_line|#define&t;EDEADLOCK&t;EDEADLK
DECL|macro|EBFONT
mdefine_line|#define&t;EBFONT&t;&t;104&t;/* Bad font file format */
DECL|macro|ENONET
mdefine_line|#define&t;ENONET&t;&t;105&t;/* Machine is not on the network */
DECL|macro|ENOLINK
mdefine_line|#define&t;ENOLINK&t;&t;106&t;/* Link has been severed */
DECL|macro|EADV
mdefine_line|#define&t;EADV&t;&t;107&t;/* Advertise error */
DECL|macro|ESRMNT
mdefine_line|#define&t;ESRMNT&t;&t;108&t;/* Srmount error */
DECL|macro|ECOMM
mdefine_line|#define&t;ECOMM&t;&t;109&t;/* Communication error on send */
DECL|macro|EMULTIHOP
mdefine_line|#define&t;EMULTIHOP&t;110&t;/* Multihop attempted */
DECL|macro|EDOTDOT
mdefine_line|#define&t;EDOTDOT&t;&t;111&t;/* RFS specific error */
DECL|macro|EOVERFLOW
mdefine_line|#define&t;EOVERFLOW&t;112&t;/* Value too large for defined data type */
DECL|macro|ENOTUNIQ
mdefine_line|#define&t;ENOTUNIQ&t;113&t;/* Name not unique on network */
DECL|macro|EBADFD
mdefine_line|#define&t;EBADFD&t;&t;114&t;/* File descriptor in bad state */
DECL|macro|EREMCHG
mdefine_line|#define&t;EREMCHG&t;&t;115&t;/* Remote address changed */
DECL|macro|EUCLEAN
mdefine_line|#define&t;EUCLEAN&t;&t;117&t;/* Structure needs cleaning */
DECL|macro|ENOTNAM
mdefine_line|#define&t;ENOTNAM&t;&t;118&t;/* Not a XENIX named type file */
DECL|macro|ENAVAIL
mdefine_line|#define&t;ENAVAIL&t;&t;119&t;/* No XENIX semaphores available */
DECL|macro|EISNAM
mdefine_line|#define&t;EISNAM&t;&t;120&t;/* Is a named type file */
DECL|macro|EREMOTEIO
mdefine_line|#define&t;EREMOTEIO&t;121&t;/* Remote I/O error */
DECL|macro|ELIBACC
mdefine_line|#define&t;ELIBACC&t;&t;122&t;/* Can not access a needed shared library */
DECL|macro|ELIBBAD
mdefine_line|#define&t;ELIBBAD&t;&t;123&t;/* Accessing a corrupted shared library */
DECL|macro|ELIBSCN
mdefine_line|#define&t;ELIBSCN&t;&t;124&t;/* .lib section in a.out corrupted */
DECL|macro|ELIBMAX
mdefine_line|#define&t;ELIBMAX&t;&t;125&t;/* Attempting to link in too many shared libraries */
DECL|macro|ELIBEXEC
mdefine_line|#define&t;ELIBEXEC&t;126&t;/* Cannot exec a shared library directly */
DECL|macro|ERESTART
mdefine_line|#define&t;ERESTART&t;127&t;/* Interrupted system call should be restarted */
DECL|macro|ESTRPIPE
mdefine_line|#define&t;ESTRPIPE&t;128&t;/* Streams pipe error */
DECL|macro|ENOMEDIUM
mdefine_line|#define ENOMEDIUM&t;129&t;/* No medium found */
DECL|macro|EMEDIUMTYPE
mdefine_line|#define EMEDIUMTYPE&t;130&t;/* Wrong medium type */
macro_line|#endif
eof
