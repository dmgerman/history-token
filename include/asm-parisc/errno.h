macro_line|#ifndef _PARISC_ERRNO_H
DECL|macro|_PARISC_ERRNO_H
mdefine_line|#define _PARISC_ERRNO_H
DECL|macro|EPERM
mdefine_line|#define&t;EPERM&t;&t; 1&t;/* Operation not permitted */
DECL|macro|ENOENT
mdefine_line|#define&t;ENOENT&t;&t; 2&t;/* No such file or directory */
DECL|macro|ESRCH
mdefine_line|#define&t;ESRCH&t;&t; 3&t;/* No such process */
DECL|macro|EINTR
mdefine_line|#define&t;EINTR&t;&t; 4&t;/* Interrupted system call */
DECL|macro|EIO
mdefine_line|#define&t;EIO&t;&t; 5&t;/* I/O error */
DECL|macro|ENXIO
mdefine_line|#define&t;ENXIO&t;&t; 6&t;/* No such device or address */
DECL|macro|E2BIG
mdefine_line|#define&t;E2BIG&t;&t; 7&t;/* Arg list too long */
DECL|macro|ENOEXEC
mdefine_line|#define&t;ENOEXEC&t;&t; 8&t;/* Exec format error */
DECL|macro|EBADF
mdefine_line|#define&t;EBADF&t;&t; 9&t;/* Bad file number */
DECL|macro|ECHILD
mdefine_line|#define&t;ECHILD&t;&t;10&t;/* No child processes */
DECL|macro|EAGAIN
mdefine_line|#define&t;EAGAIN&t;&t;11&t;/* Try again */
DECL|macro|ENOMEM
mdefine_line|#define&t;ENOMEM&t;&t;12&t;/* Out of memory */
DECL|macro|EACCES
mdefine_line|#define&t;EACCES&t;&t;13&t;/* Permission denied */
DECL|macro|EFAULT
mdefine_line|#define&t;EFAULT&t;&t;14&t;/* Bad address */
DECL|macro|ENOTBLK
mdefine_line|#define&t;ENOTBLK&t;&t;15&t;/* Block device required */
DECL|macro|EBUSY
mdefine_line|#define&t;EBUSY&t;&t;16&t;/* Device or resource busy */
DECL|macro|EEXIST
mdefine_line|#define&t;EEXIST&t;&t;17&t;/* File exists */
DECL|macro|EXDEV
mdefine_line|#define&t;EXDEV&t;&t;18&t;/* Cross-device link */
DECL|macro|ENODEV
mdefine_line|#define&t;ENODEV&t;&t;19&t;/* No such device */
DECL|macro|ENOTDIR
mdefine_line|#define&t;ENOTDIR&t;&t;20&t;/* Not a directory */
DECL|macro|EISDIR
mdefine_line|#define&t;EISDIR&t;&t;21&t;/* Is a directory */
DECL|macro|EINVAL
mdefine_line|#define&t;EINVAL&t;&t;22&t;/* Invalid argument */
DECL|macro|ENFILE
mdefine_line|#define&t;ENFILE&t;&t;23&t;/* File table overflow */
DECL|macro|EMFILE
mdefine_line|#define&t;EMFILE&t;&t;24&t;/* Too many open files */
DECL|macro|ENOTTY
mdefine_line|#define&t;ENOTTY&t;&t;25&t;/* Not a typewriter */
DECL|macro|ETXTBSY
mdefine_line|#define&t;ETXTBSY&t;&t;26&t;/* Text file busy */
DECL|macro|EFBIG
mdefine_line|#define&t;EFBIG&t;&t;27&t;/* File too large */
DECL|macro|ENOSPC
mdefine_line|#define&t;ENOSPC&t;&t;28&t;/* No space left on device */
DECL|macro|ESPIPE
mdefine_line|#define&t;ESPIPE&t;&t;29&t;/* Illegal seek */
DECL|macro|EROFS
mdefine_line|#define&t;EROFS&t;&t;30&t;/* Read-only file system */
DECL|macro|EMLINK
mdefine_line|#define&t;EMLINK&t;&t;31&t;/* Too many links */
DECL|macro|EPIPE
mdefine_line|#define&t;EPIPE&t;&t;32&t;/* Broken pipe */
DECL|macro|EDOM
mdefine_line|#define&t;EDOM&t;&t;33&t;/* Math argument out of domain of func */
DECL|macro|ERANGE
mdefine_line|#define&t;ERANGE&t;&t;34&t;/* Math result not representable */
DECL|macro|ENOMSG
mdefine_line|#define&t;ENOMSG&t;&t;35&t;/* No message of desired type */
DECL|macro|EIDRM
mdefine_line|#define&t;EIDRM&t;&t;36&t;/* Identifier removed */
DECL|macro|ECHRNG
mdefine_line|#define&t;ECHRNG&t;&t;37&t;/* Channel number out of range */
DECL|macro|EL2NSYNC
mdefine_line|#define&t;EL2NSYNC&t;38&t;/* Level 2 not synchronized */
DECL|macro|EL3HLT
mdefine_line|#define&t;EL3HLT&t;&t;39&t;/* Level 3 halted */
DECL|macro|EL3RST
mdefine_line|#define&t;EL3RST&t;&t;40&t;/* Level 3 reset */
DECL|macro|ELNRNG
mdefine_line|#define&t;ELNRNG&t;&t;41&t;/* Link number out of range */
DECL|macro|EUNATCH
mdefine_line|#define&t;EUNATCH&t;&t;42&t;/* Protocol driver not attached */
DECL|macro|ENOCSI
mdefine_line|#define&t;ENOCSI&t;&t;43&t;/* No CSI structure available */
DECL|macro|EL2HLT
mdefine_line|#define&t;EL2HLT&t;&t;44&t;/* Level 2 halted */
DECL|macro|EDEADLK
mdefine_line|#define&t;EDEADLK&t;&t;45&t;/* Resource deadlock would occur */
DECL|macro|EDEADLOCK
mdefine_line|#define&t;EDEADLOCK&t;EDEADLK
DECL|macro|ENOLCK
mdefine_line|#define&t;ENOLCK&t;&t;46&t;/* No record locks available */
DECL|macro|EILSEQ
mdefine_line|#define&t;EILSEQ&t;&t;47&t;/* Illegal byte sequence */
DECL|macro|ENONET
mdefine_line|#define&t;ENONET&t;&t;50&t;/* Machine is not on the network */
DECL|macro|ENODATA
mdefine_line|#define&t;ENODATA&t;&t;51&t;/* No data available */
DECL|macro|ETIME
mdefine_line|#define&t;ETIME&t;&t;52&t;/* Timer expired */
DECL|macro|ENOSR
mdefine_line|#define&t;ENOSR&t;&t;53&t;/* Out of streams resources */
DECL|macro|ENOSTR
mdefine_line|#define&t;ENOSTR&t;&t;54&t;/* Device not a stream */
DECL|macro|ENOPKG
mdefine_line|#define&t;ENOPKG&t;&t;55&t;/* Package not installed */
DECL|macro|ENOLINK
mdefine_line|#define&t;ENOLINK&t;&t;57&t;/* Link has been severed */
DECL|macro|EADV
mdefine_line|#define&t;EADV&t;&t;58&t;/* Advertise error */
DECL|macro|ESRMNT
mdefine_line|#define&t;ESRMNT&t;&t;59&t;/* Srmount error */
DECL|macro|ECOMM
mdefine_line|#define&t;ECOMM&t;&t;60&t;/* Communication error on send */
DECL|macro|EPROTO
mdefine_line|#define&t;EPROTO&t;&t;61&t;/* Protocol error */
DECL|macro|EMULTIHOP
mdefine_line|#define&t;EMULTIHOP&t;64&t;/* Multihop attempted */
DECL|macro|EDOTDOT
mdefine_line|#define&t;EDOTDOT&t;&t;66&t;/* RFS specific error */
DECL|macro|EBADMSG
mdefine_line|#define&t;EBADMSG&t;&t;67&t;/* Not a data message */
DECL|macro|EUSERS
mdefine_line|#define&t;EUSERS&t;&t;68&t;/* Too many users */
DECL|macro|EDQUOT
mdefine_line|#define&t;EDQUOT&t;&t;69&t;/* Quota exceeded */
DECL|macro|ESTALE
mdefine_line|#define&t;ESTALE&t;&t;70&t;/* Stale NFS file handle */
DECL|macro|EREMOTE
mdefine_line|#define&t;EREMOTE&t;&t;71&t;/* Object is remote */
DECL|macro|EOVERFLOW
mdefine_line|#define&t;EOVERFLOW&t;72&t;/* Value too large for defined data type */
multiline_comment|/* these errnos are defined by Linux but not HPUX. */
DECL|macro|EBADE
mdefine_line|#define&t;EBADE&t;&t;160&t;/* Invalid exchange */
DECL|macro|EBADR
mdefine_line|#define&t;EBADR&t;&t;161&t;/* Invalid request descriptor */
DECL|macro|EXFULL
mdefine_line|#define&t;EXFULL&t;&t;162&t;/* Exchange full */
DECL|macro|ENOANO
mdefine_line|#define&t;ENOANO&t;&t;163&t;/* No anode */
DECL|macro|EBADRQC
mdefine_line|#define&t;EBADRQC&t;&t;164&t;/* Invalid request code */
DECL|macro|EBADSLT
mdefine_line|#define&t;EBADSLT&t;&t;165&t;/* Invalid slot */
DECL|macro|EBFONT
mdefine_line|#define&t;EBFONT&t;&t;166&t;/* Bad font file format */
DECL|macro|ENOTUNIQ
mdefine_line|#define&t;ENOTUNIQ&t;167&t;/* Name not unique on network */
DECL|macro|EBADFD
mdefine_line|#define&t;EBADFD&t;&t;168&t;/* File descriptor in bad state */
DECL|macro|EREMCHG
mdefine_line|#define&t;EREMCHG&t;&t;169&t;/* Remote address changed */
DECL|macro|ELIBACC
mdefine_line|#define&t;ELIBACC&t;&t;170&t;/* Can not access a needed shared library */
DECL|macro|ELIBBAD
mdefine_line|#define&t;ELIBBAD&t;&t;171&t;/* Accessing a corrupted shared library */
DECL|macro|ELIBSCN
mdefine_line|#define&t;ELIBSCN&t;&t;172&t;/* .lib section in a.out corrupted */
DECL|macro|ELIBMAX
mdefine_line|#define&t;ELIBMAX&t;&t;173&t;/* Attempting to link in too many shared libraries */
DECL|macro|ELIBEXEC
mdefine_line|#define&t;ELIBEXEC&t;174&t;/* Cannot exec a shared library directly */
DECL|macro|ERESTART
mdefine_line|#define&t;ERESTART&t;175&t;/* Interrupted system call should be restarted */
DECL|macro|ESTRPIPE
mdefine_line|#define&t;ESTRPIPE&t;176&t;/* Streams pipe error */
DECL|macro|EUCLEAN
mdefine_line|#define&t;EUCLEAN&t;&t;177&t;/* Structure needs cleaning */
DECL|macro|ENOTNAM
mdefine_line|#define&t;ENOTNAM&t;&t;178&t;/* Not a XENIX named type file */
DECL|macro|ENAVAIL
mdefine_line|#define&t;ENAVAIL&t;&t;179&t;/* No XENIX semaphores available */
DECL|macro|EISNAM
mdefine_line|#define&t;EISNAM&t;&t;180&t;/* Is a named type file */
DECL|macro|EREMOTEIO
mdefine_line|#define&t;EREMOTEIO&t;181&t;/* Remote I/O error */
DECL|macro|ENOMEDIUM
mdefine_line|#define&t;ENOMEDIUM&t;182&t;/* No medium found */
DECL|macro|EMEDIUMTYPE
mdefine_line|#define&t;EMEDIUMTYPE&t;183&t;/* Wrong medium type */
multiline_comment|/* We now return you to your regularly scheduled HPUX. */
DECL|macro|ENOSYM
mdefine_line|#define ENOSYM&t;&t;215&t;/* symbol does not exist in executable */
DECL|macro|ENOTSOCK
mdefine_line|#define&t;ENOTSOCK&t;216&t;/* Socket operation on non-socket */
DECL|macro|EDESTADDRREQ
mdefine_line|#define&t;EDESTADDRREQ&t;217&t;/* Destination address required */
DECL|macro|EMSGSIZE
mdefine_line|#define&t;EMSGSIZE&t;218&t;/* Message too long */
DECL|macro|EPROTOTYPE
mdefine_line|#define&t;EPROTOTYPE&t;219&t;/* Protocol wrong type for socket */
DECL|macro|ENOPROTOOPT
mdefine_line|#define&t;ENOPROTOOPT&t;220&t;/* Protocol not available */
DECL|macro|EPROTONOSUPPORT
mdefine_line|#define&t;EPROTONOSUPPORT&t;221&t;/* Protocol not supported */
DECL|macro|ESOCKTNOSUPPORT
mdefine_line|#define&t;ESOCKTNOSUPPORT&t;222&t;/* Socket type not supported */
DECL|macro|EOPNOTSUPP
mdefine_line|#define&t;EOPNOTSUPP&t;223&t;/* Operation not supported on transport endpoint */
DECL|macro|EPFNOSUPPORT
mdefine_line|#define&t;EPFNOSUPPORT&t;224&t;/* Protocol family not supported */
DECL|macro|EAFNOSUPPORT
mdefine_line|#define&t;EAFNOSUPPORT&t;225&t;/* Address family not supported by protocol */
DECL|macro|EADDRINUSE
mdefine_line|#define&t;EADDRINUSE&t;226&t;/* Address already in use */
DECL|macro|EADDRNOTAVAIL
mdefine_line|#define&t;EADDRNOTAVAIL&t;227&t;/* Cannot assign requested address */
DECL|macro|ENETDOWN
mdefine_line|#define&t;ENETDOWN&t;228&t;/* Network is down */
DECL|macro|ENETUNREACH
mdefine_line|#define&t;ENETUNREACH&t;229&t;/* Network is unreachable */
DECL|macro|ENETRESET
mdefine_line|#define&t;ENETRESET&t;230&t;/* Network dropped connection because of reset */
DECL|macro|ECONNABORTED
mdefine_line|#define&t;ECONNABORTED&t;231&t;/* Software caused connection abort */
DECL|macro|ECONNRESET
mdefine_line|#define&t;ECONNRESET&t;232&t;/* Connection reset by peer */
DECL|macro|ENOBUFS
mdefine_line|#define&t;ENOBUFS&t;&t;233&t;/* No buffer space available */
DECL|macro|EISCONN
mdefine_line|#define&t;EISCONN&t;&t;234&t;/* Transport endpoint is already connected */
DECL|macro|ENOTCONN
mdefine_line|#define&t;ENOTCONN&t;235&t;/* Transport endpoint is not connected */
DECL|macro|ESHUTDOWN
mdefine_line|#define&t;ESHUTDOWN&t;236&t;/* Cannot send after transport endpoint shutdown */
DECL|macro|ETOOMANYREFS
mdefine_line|#define&t;ETOOMANYREFS&t;237&t;/* Too many references: cannot splice */
DECL|macro|EREFUSED
mdefine_line|#define EREFUSED&t;ECONNREFUSED&t;/* for HP&squot;s NFS apparently */
DECL|macro|ETIMEDOUT
mdefine_line|#define&t;ETIMEDOUT&t;238&t;/* Connection timed out */
DECL|macro|ECONNREFUSED
mdefine_line|#define&t;ECONNREFUSED&t;239&t;/* Connection refused */
DECL|macro|EREMOTERELEASE
mdefine_line|#define EREMOTERELEASE&t;240&t;/* Remote peer released connection */
DECL|macro|EHOSTDOWN
mdefine_line|#define&t;EHOSTDOWN&t;241&t;/* Host is down */
DECL|macro|EHOSTUNREACH
mdefine_line|#define&t;EHOSTUNREACH&t;242&t;/* No route to host */
DECL|macro|EALREADY
mdefine_line|#define&t;EALREADY&t;244&t;/* Operation already in progress */
DECL|macro|EINPROGRESS
mdefine_line|#define&t;EINPROGRESS&t;245&t;/* Operation now in progress */
DECL|macro|EWOULDBLOCK
mdefine_line|#define&t;EWOULDBLOCK&t;246&t;/* Operation would block (Linux returns EAGAIN) */
DECL|macro|ENOTEMPTY
mdefine_line|#define&t;ENOTEMPTY&t;247&t;/* Directory not empty */
DECL|macro|ENAMETOOLONG
mdefine_line|#define&t;ENAMETOOLONG&t;248&t;/* File name too long */
DECL|macro|ELOOP
mdefine_line|#define&t;ELOOP&t;&t;249&t;/* Too many symbolic links encountered */
DECL|macro|ENOSYS
mdefine_line|#define&t;ENOSYS&t;&t;251&t;/* Function not implemented */
DECL|macro|ENOTSUP
mdefine_line|#define ENOTSUP&t;&t;252&t;/* Function not implemented (POSIX.4 / HPUX) */
DECL|macro|ECANCELLED
mdefine_line|#define ECANCELLED&t;253&t;/* aio request was canceled before complete (POSIX.4 / HPUX) */
macro_line|#endif
eof
