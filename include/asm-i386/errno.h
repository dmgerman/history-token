macro_line|#ifndef _I386_ERRNO_H
DECL|macro|_I386_ERRNO_H
mdefine_line|#define _I386_ERRNO_H
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
DECL|macro|EDEADLK
mdefine_line|#define&t;EDEADLK&t;&t;35&t;/* Resource deadlock would occur */
DECL|macro|ENAMETOOLONG
mdefine_line|#define&t;ENAMETOOLONG&t;36&t;/* File name too long */
DECL|macro|ENOLCK
mdefine_line|#define&t;ENOLCK&t;&t;37&t;/* No record locks available */
DECL|macro|ENOSYS
mdefine_line|#define&t;ENOSYS&t;&t;38&t;/* Function not implemented */
DECL|macro|ENOTEMPTY
mdefine_line|#define&t;ENOTEMPTY&t;39&t;/* Directory not empty */
DECL|macro|ELOOP
mdefine_line|#define&t;ELOOP&t;&t;40&t;/* Too many symbolic links encountered */
DECL|macro|EWOULDBLOCK
mdefine_line|#define&t;EWOULDBLOCK&t;EAGAIN&t;/* Operation would block */
DECL|macro|ENOMSG
mdefine_line|#define&t;ENOMSG&t;&t;42&t;/* No message of desired type */
DECL|macro|EIDRM
mdefine_line|#define&t;EIDRM&t;&t;43&t;/* Identifier removed */
DECL|macro|ECHRNG
mdefine_line|#define&t;ECHRNG&t;&t;44&t;/* Channel number out of range */
DECL|macro|EL2NSYNC
mdefine_line|#define&t;EL2NSYNC&t;45&t;/* Level 2 not synchronized */
DECL|macro|EL3HLT
mdefine_line|#define&t;EL3HLT&t;&t;46&t;/* Level 3 halted */
DECL|macro|EL3RST
mdefine_line|#define&t;EL3RST&t;&t;47&t;/* Level 3 reset */
DECL|macro|ELNRNG
mdefine_line|#define&t;ELNRNG&t;&t;48&t;/* Link number out of range */
DECL|macro|EUNATCH
mdefine_line|#define&t;EUNATCH&t;&t;49&t;/* Protocol driver not attached */
DECL|macro|ENOCSI
mdefine_line|#define&t;ENOCSI&t;&t;50&t;/* No CSI structure available */
DECL|macro|EL2HLT
mdefine_line|#define&t;EL2HLT&t;&t;51&t;/* Level 2 halted */
DECL|macro|EBADE
mdefine_line|#define&t;EBADE&t;&t;52&t;/* Invalid exchange */
DECL|macro|EBADR
mdefine_line|#define&t;EBADR&t;&t;53&t;/* Invalid request descriptor */
DECL|macro|EXFULL
mdefine_line|#define&t;EXFULL&t;&t;54&t;/* Exchange full */
DECL|macro|ENOANO
mdefine_line|#define&t;ENOANO&t;&t;55&t;/* No anode */
DECL|macro|EBADRQC
mdefine_line|#define&t;EBADRQC&t;&t;56&t;/* Invalid request code */
DECL|macro|EBADSLT
mdefine_line|#define&t;EBADSLT&t;&t;57&t;/* Invalid slot */
DECL|macro|EDEADLOCK
mdefine_line|#define&t;EDEADLOCK&t;EDEADLK
DECL|macro|EBFONT
mdefine_line|#define&t;EBFONT&t;&t;59&t;/* Bad font file format */
DECL|macro|ENOSTR
mdefine_line|#define&t;ENOSTR&t;&t;60&t;/* Device not a stream */
DECL|macro|ENODATA
mdefine_line|#define&t;ENODATA&t;&t;61&t;/* No data available */
DECL|macro|ETIME
mdefine_line|#define&t;ETIME&t;&t;62&t;/* Timer expired */
DECL|macro|ENOSR
mdefine_line|#define&t;ENOSR&t;&t;63&t;/* Out of streams resources */
DECL|macro|ENONET
mdefine_line|#define&t;ENONET&t;&t;64&t;/* Machine is not on the network */
DECL|macro|ENOPKG
mdefine_line|#define&t;ENOPKG&t;&t;65&t;/* Package not installed */
DECL|macro|EREMOTE
mdefine_line|#define&t;EREMOTE&t;&t;66&t;/* Object is remote */
DECL|macro|ENOLINK
mdefine_line|#define&t;ENOLINK&t;&t;67&t;/* Link has been severed */
DECL|macro|EADV
mdefine_line|#define&t;EADV&t;&t;68&t;/* Advertise error */
DECL|macro|ESRMNT
mdefine_line|#define&t;ESRMNT&t;&t;69&t;/* Srmount error */
DECL|macro|ECOMM
mdefine_line|#define&t;ECOMM&t;&t;70&t;/* Communication error on send */
DECL|macro|EPROTO
mdefine_line|#define&t;EPROTO&t;&t;71&t;/* Protocol error */
DECL|macro|EMULTIHOP
mdefine_line|#define&t;EMULTIHOP&t;72&t;/* Multihop attempted */
DECL|macro|EDOTDOT
mdefine_line|#define&t;EDOTDOT&t;&t;73&t;/* RFS specific error */
DECL|macro|EBADMSG
mdefine_line|#define&t;EBADMSG&t;&t;74&t;/* Not a data message */
DECL|macro|EOVERFLOW
mdefine_line|#define&t;EOVERFLOW&t;75&t;/* Value too large for defined data type */
DECL|macro|ENOTUNIQ
mdefine_line|#define&t;ENOTUNIQ&t;76&t;/* Name not unique on network */
DECL|macro|EBADFD
mdefine_line|#define&t;EBADFD&t;&t;77&t;/* File descriptor in bad state */
DECL|macro|EREMCHG
mdefine_line|#define&t;EREMCHG&t;&t;78&t;/* Remote address changed */
DECL|macro|ELIBACC
mdefine_line|#define&t;ELIBACC&t;&t;79&t;/* Can not access a needed shared library */
DECL|macro|ELIBBAD
mdefine_line|#define&t;ELIBBAD&t;&t;80&t;/* Accessing a corrupted shared library */
DECL|macro|ELIBSCN
mdefine_line|#define&t;ELIBSCN&t;&t;81&t;/* .lib section in a.out corrupted */
DECL|macro|ELIBMAX
mdefine_line|#define&t;ELIBMAX&t;&t;82&t;/* Attempting to link in too many shared libraries */
DECL|macro|ELIBEXEC
mdefine_line|#define&t;ELIBEXEC&t;83&t;/* Cannot exec a shared library directly */
DECL|macro|EILSEQ
mdefine_line|#define&t;EILSEQ&t;&t;84&t;/* Illegal byte sequence */
DECL|macro|ERESTART
mdefine_line|#define&t;ERESTART&t;85&t;/* Interrupted system call should be restarted */
DECL|macro|ESTRPIPE
mdefine_line|#define&t;ESTRPIPE&t;86&t;/* Streams pipe error */
DECL|macro|EUSERS
mdefine_line|#define&t;EUSERS&t;&t;87&t;/* Too many users */
DECL|macro|ENOTSOCK
mdefine_line|#define&t;ENOTSOCK&t;88&t;/* Socket operation on non-socket */
DECL|macro|EDESTADDRREQ
mdefine_line|#define&t;EDESTADDRREQ&t;89&t;/* Destination address required */
DECL|macro|EMSGSIZE
mdefine_line|#define&t;EMSGSIZE&t;90&t;/* Message too long */
DECL|macro|EPROTOTYPE
mdefine_line|#define&t;EPROTOTYPE&t;91&t;/* Protocol wrong type for socket */
DECL|macro|ENOPROTOOPT
mdefine_line|#define&t;ENOPROTOOPT&t;92&t;/* Protocol not available */
DECL|macro|EPROTONOSUPPORT
mdefine_line|#define&t;EPROTONOSUPPORT&t;93&t;/* Protocol not supported */
DECL|macro|ESOCKTNOSUPPORT
mdefine_line|#define&t;ESOCKTNOSUPPORT&t;94&t;/* Socket type not supported */
DECL|macro|EOPNOTSUPP
mdefine_line|#define&t;EOPNOTSUPP&t;95&t;/* Operation not supported on transport endpoint */
DECL|macro|EPFNOSUPPORT
mdefine_line|#define&t;EPFNOSUPPORT&t;96&t;/* Protocol family not supported */
DECL|macro|EAFNOSUPPORT
mdefine_line|#define&t;EAFNOSUPPORT&t;97&t;/* Address family not supported by protocol */
DECL|macro|EADDRINUSE
mdefine_line|#define&t;EADDRINUSE&t;98&t;/* Address already in use */
DECL|macro|EADDRNOTAVAIL
mdefine_line|#define&t;EADDRNOTAVAIL&t;99&t;/* Cannot assign requested address */
DECL|macro|ENETDOWN
mdefine_line|#define&t;ENETDOWN&t;100&t;/* Network is down */
DECL|macro|ENETUNREACH
mdefine_line|#define&t;ENETUNREACH&t;101&t;/* Network is unreachable */
DECL|macro|ENETRESET
mdefine_line|#define&t;ENETRESET&t;102&t;/* Network dropped connection because of reset */
DECL|macro|ECONNABORTED
mdefine_line|#define&t;ECONNABORTED&t;103&t;/* Software caused connection abort */
DECL|macro|ECONNRESET
mdefine_line|#define&t;ECONNRESET&t;104&t;/* Connection reset by peer */
DECL|macro|ENOBUFS
mdefine_line|#define&t;ENOBUFS&t;&t;105&t;/* No buffer space available */
DECL|macro|EISCONN
mdefine_line|#define&t;EISCONN&t;&t;106&t;/* Transport endpoint is already connected */
DECL|macro|ENOTCONN
mdefine_line|#define&t;ENOTCONN&t;107&t;/* Transport endpoint is not connected */
DECL|macro|ESHUTDOWN
mdefine_line|#define&t;ESHUTDOWN&t;108&t;/* Cannot send after transport endpoint shutdown */
DECL|macro|ETOOMANYREFS
mdefine_line|#define&t;ETOOMANYREFS&t;109&t;/* Too many references: cannot splice */
DECL|macro|ETIMEDOUT
mdefine_line|#define&t;ETIMEDOUT&t;110&t;/* Connection timed out */
DECL|macro|ECONNREFUSED
mdefine_line|#define&t;ECONNREFUSED&t;111&t;/* Connection refused */
DECL|macro|EHOSTDOWN
mdefine_line|#define&t;EHOSTDOWN&t;112&t;/* Host is down */
DECL|macro|EHOSTUNREACH
mdefine_line|#define&t;EHOSTUNREACH&t;113&t;/* No route to host */
DECL|macro|EALREADY
mdefine_line|#define&t;EALREADY&t;114&t;/* Operation already in progress */
DECL|macro|EINPROGRESS
mdefine_line|#define&t;EINPROGRESS&t;115&t;/* Operation now in progress */
DECL|macro|ESTALE
mdefine_line|#define&t;ESTALE&t;&t;116&t;/* Stale NFS file handle */
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
DECL|macro|EDQUOT
mdefine_line|#define&t;EDQUOT&t;&t;122&t;/* Quota exceeded */
DECL|macro|ENOMEDIUM
mdefine_line|#define&t;ENOMEDIUM&t;123&t;/* No medium found */
DECL|macro|EMEDIUMTYPE
mdefine_line|#define&t;EMEDIUMTYPE&t;124&t;/* Wrong medium type */
DECL|macro|EHASHCOLLISION
mdefine_line|#define&t;EHASHCOLLISION&t;125&t;/* Number of hash collisons exceeds maximum generation counter value.  */
macro_line|#endif
eof
