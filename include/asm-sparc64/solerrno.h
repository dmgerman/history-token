multiline_comment|/* $Id: solerrno.h,v 1.1 1996/12/26 14:22:40 davem Exp $&n; * solerrno.h: Solaris error return codes for compatibility.&n; *&n; * Copyright (C) 1996 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef _SPARC64_SOLERRNO_H
DECL|macro|_SPARC64_SOLERRNO_H
mdefine_line|#define _SPARC64_SOLERRNO_H
DECL|macro|SOL_EPERM
mdefine_line|#define SOL_EPERM          1     /* Required superuser access perms  */
DECL|macro|SOL_ENOENT
mdefine_line|#define SOL_ENOENT         2     /* File or directory does not exist */
DECL|macro|SOL_ESRCH
mdefine_line|#define SOL_ESRCH          3     /* Process did not exist            */
DECL|macro|SOL_EINTR
mdefine_line|#define&t;SOL_EINTR          4     /* System call was interrupted      */
DECL|macro|SOL_EIO
mdefine_line|#define&t;SOL_EIO            5     /* An i/o error occurred            */
DECL|macro|SOL_ENXIO
mdefine_line|#define&t;SOL_ENXIO          6     /* Device or Address does not exist */
DECL|macro|SOL_E2BIG
mdefine_line|#define&t;SOL_E2BIG          7&t; /* Too many arguments were given    */
DECL|macro|SOL_ENOEXEC
mdefine_line|#define&t;SOL_ENOEXEC        8     /* Header of executable was munged  */
DECL|macro|SOL_EBADF
mdefine_line|#define&t;SOL_EBADF          9     /* Bogus file number                */
DECL|macro|SOL_ECHILD
mdefine_line|#define&t;SOL_ECHILD         10    /* No children of process exist     */
DECL|macro|SOL_EAGAIN
mdefine_line|#define&t;SOL_EAGAIN         11    /* beep beep, &quot;try again later&quot;     */
DECL|macro|SOL_ENOMEM
mdefine_line|#define&t;SOL_ENOMEM         12    /* No memory available              */
DECL|macro|SOL_EACCES
mdefine_line|#define&t;SOL_EACCES         13    /* Access not allowed               */
DECL|macro|SOL_EFAULT
mdefine_line|#define&t;SOL_EFAULT         14    /* Address passed was invalid       */
DECL|macro|SOL_ENOTBLK
mdefine_line|#define&t;SOL_ENOTBLK        15    /* blkdev op on non-block device    */
DECL|macro|SOL_EBUSY
mdefine_line|#define&t;SOL_EBUSY          16    /* Mounted device was busy          */
DECL|macro|SOL_EEXIST
mdefine_line|#define&t;SOL_EEXIST         17    /* File specified already exists    */
DECL|macro|SOL_EXDEV
mdefine_line|#define&t;SOL_EXDEV          18    /* Link request across diff devices */
DECL|macro|SOL_ENODEV
mdefine_line|#define&t;SOL_ENODEV         19    /* Device does not exist on system  */
DECL|macro|SOL_ENOTDIR
mdefine_line|#define&t;SOL_ENOTDIR        20    /* Dir operation on non-directory   */
DECL|macro|SOL_EISDIR
mdefine_line|#define&t;SOL_EISDIR         21    /* File was of directory type       */
DECL|macro|SOL_EINVAL
mdefine_line|#define&t;SOL_EINVAL         22    /* Argument passed was invalid      */
DECL|macro|SOL_ENFILE
mdefine_line|#define&t;SOL_ENFILE         23    /* No more room in file table       */
DECL|macro|SOL_EMFILE
mdefine_line|#define&t;SOL_EMFILE         24    /* Proc has too many files open     */
DECL|macro|SOL_ENOTTY
mdefine_line|#define&t;SOL_ENOTTY         25    /* Ioctl was invalid for req device */
DECL|macro|SOL_ETXTBSY
mdefine_line|#define&t;SOL_ETXTBSY        26    /* Text file in busy state          */
DECL|macro|SOL_EFBIG
mdefine_line|#define&t;SOL_EFBIG          27    /* Too big of a file for operation  */
DECL|macro|SOL_ENOSPC
mdefine_line|#define&t;SOL_ENOSPC         28    /* Disk is full                     */
DECL|macro|SOL_ESPIPE
mdefine_line|#define&t;SOL_ESPIPE         29    /* Seek attempted on non-seeking dev*/
DECL|macro|SOL_EROFS
mdefine_line|#define&t;SOL_EROFS          30    /* Write attempted on read-only fs  */
DECL|macro|SOL_EMLINK
mdefine_line|#define&t;SOL_EMLINK         31    /* Too many links in file search    */
DECL|macro|SOL_EPIPE
mdefine_line|#define&t;SOL_EPIPE          32    /* Call a plumber                   */
DECL|macro|SOL_EDOM
mdefine_line|#define&t;SOL_EDOM           33    /* Argument was out of fct domain   */
DECL|macro|SOL_ERANGE
mdefine_line|#define&t;SOL_ERANGE         34    /* Could not represent math result  */
DECL|macro|SOL_ENOMSG
mdefine_line|#define&t;SOL_ENOMSG         35    /* Message of req type doesn&squot;t exist */
DECL|macro|SOL_EIDRM
mdefine_line|#define&t;SOL_EIDRM          36    /* Identifier has been removed      */
DECL|macro|SOL_ECHRNG
mdefine_line|#define&t;SOL_ECHRNG         37    /* Req channel number out of range  */
DECL|macro|SOL_EL2NSYNC
mdefine_line|#define&t;SOL_EL2NSYNC       38    /* Could not sync at run level 2    */
DECL|macro|SOL_EL3HLT
mdefine_line|#define&t;SOL_EL3HLT         39    /* Halted at run level 3            */
DECL|macro|SOL_EL3RST
mdefine_line|#define&t;SOL_EL3RST         40    /* Reset at run level 3             */
DECL|macro|SOL_ELNRNG
mdefine_line|#define&t;SOL_ELNRNG         41    /* Out of range link number         */
DECL|macro|SOL_EUNATCH
mdefine_line|#define&t;SOL_EUNATCH        42    /* Driver for protocol not attached */
DECL|macro|SOL_ENOCSI
mdefine_line|#define&t;SOL_ENOCSI         43    /* CSI structure not around         */
DECL|macro|SOL_EL2HLT
mdefine_line|#define&t;SOL_EL2HLT         44    /* Halted at run level 2            */
DECL|macro|SOL_EDEADLK
mdefine_line|#define&t;SOL_EDEADLK        45    /* Deadlock condition detected      */
DECL|macro|SOL_ENOLCK
mdefine_line|#define&t;SOL_ENOLCK         46    /* Record locks unavailable         */
DECL|macro|SOL_ECANCELED
mdefine_line|#define&t;SOL_ECANCELED      47    /* Cancellation of oper. happened   */
DECL|macro|SOL_ENOTSUP
mdefine_line|#define&t;SOL_ENOTSUP        48    /* Attempt of unsupported operation */
DECL|macro|SOL_EDQUOT
mdefine_line|#define&t;SOL_EDQUOT         49    /* Users disk quota exceeded        */
DECL|macro|SOL_EBADE
mdefine_line|#define&t;SOL_EBADE          50    /* Invalid exchange                 */
DECL|macro|SOL_EBADR
mdefine_line|#define&t;SOL_EBADR          51    /* Request descriptor was invalid   */
DECL|macro|SOL_EXFULL
mdefine_line|#define&t;SOL_EXFULL         52    /* Full exchange                    */
DECL|macro|SOL_ENOANO
mdefine_line|#define&t;SOL_ENOANO         53    /* ano does not exist               */
DECL|macro|SOL_EBADRQC
mdefine_line|#define&t;SOL_EBADRQC        54    /* Req code was invalid             */
DECL|macro|SOL_EBADSLT
mdefine_line|#define&t;SOL_EBADSLT        55    /* Bad slot number                  */
DECL|macro|SOL_EDEADLOCK
mdefine_line|#define&t;SOL_EDEADLOCK      56    /* Deadlock in fs error             */
DECL|macro|SOL_EBFONT
mdefine_line|#define&t;SOL_EBFONT         57    /* Font file format invalid         */
multiline_comment|/* YOW, I LOVE SYSV STREAMS!!!! */
DECL|macro|SOL_ENOSTR
mdefine_line|#define&t;SOL_ENOSTR         60    /* Stream-op on non-stream dev      */
DECL|macro|SOL_ENODATA
mdefine_line|#define&t;SOL_ENODATA        61    /* No data avail at this time       */
DECL|macro|SOL_ETIME
mdefine_line|#define&t;SOL_ETIME          62    /* Expiration of time occurred      */
DECL|macro|SOL_ENOSR
mdefine_line|#define&t;SOL_ENOSR          63    /* Streams resources exhausted      */
DECL|macro|SOL_ENONET
mdefine_line|#define&t;SOL_ENONET         64    /* No network connected             */
DECL|macro|SOL_ENOPKG
mdefine_line|#define&t;SOL_ENOPKG         65    /* Non-installed package            */
DECL|macro|SOL_EREMOTE
mdefine_line|#define&t;SOL_EREMOTE        66    /* Object was on remote machine     */
DECL|macro|SOL_ENOLINK
mdefine_line|#define&t;SOL_ENOLINK        67    /* Cut link                         */
DECL|macro|SOL_EADV
mdefine_line|#define&t;SOL_EADV           68    /* Error in advertise               */
DECL|macro|SOL_ESRMNT
mdefine_line|#define&t;SOL_ESRMNT         69    /* Some magic srmount problem       */
DECL|macro|SOL_ECOMM
mdefine_line|#define&t;SOL_ECOMM          70    /* During send, comm error occurred */
DECL|macro|SOL_EPROTO
mdefine_line|#define&t;SOL_EPROTO         71    /* Protocol botch                   */
DECL|macro|SOL_EMULTIHOP
mdefine_line|#define&t;SOL_EMULTIHOP      74    /* Multihop attempted               */
DECL|macro|SOL_EBADMSG
mdefine_line|#define&t;SOL_EBADMSG        77    /* Message was unreadable           */
DECL|macro|SOL_ENAMETOOLONG
mdefine_line|#define&t;SOL_ENAMETOOLONG   78    /* Too long of a path name          */
DECL|macro|SOL_EOVERFLOW
mdefine_line|#define&t;SOL_EOVERFLOW      79    /* Data type too small for datum    */
DECL|macro|SOL_ENOTUNIQ
mdefine_line|#define&t;SOL_ENOTUNIQ       80    /* Logical name was not unique      */
DECL|macro|SOL_EBADFD
mdefine_line|#define&t;SOL_EBADFD         81    /* Op cannot be performed on fd     */
DECL|macro|SOL_EREMCHG
mdefine_line|#define&t;SOL_EREMCHG        82    /* Remote address is now different  */
DECL|macro|SOL_ELIBACC
mdefine_line|#define&t;SOL_ELIBACC        83    /* Shared lib could not be accessed */
DECL|macro|SOL_ELIBBAD
mdefine_line|#define&t;SOL_ELIBBAD        84    /* ShLib is corrupted in some way   */
DECL|macro|SOL_ELIBSCN
mdefine_line|#define&t;SOL_ELIBSCN        85    /* A.out ShLib problems             */
DECL|macro|SOL_ELIBMAX
mdefine_line|#define&t;SOL_ELIBMAX        86    /* Exceeded ShLib linkage limit     */
DECL|macro|SOL_ELIBEXEC
mdefine_line|#define&t;SOL_ELIBEXEC       87    /* Execution of ShLib attempted     */
DECL|macro|SOL_EILSEQ
mdefine_line|#define&t;SOL_EILSEQ         88    /* Bad byte sequence found          */
DECL|macro|SOL_ENOSYS
mdefine_line|#define&t;SOL_ENOSYS         89    /* Invalid filesystem operation     */
DECL|macro|SOL_ELOOP
mdefine_line|#define&t;SOL_ELOOP          90    /* Detected loop in symbolic links  */
DECL|macro|SOL_ERESTART
mdefine_line|#define&t;SOL_ERESTART       91    /* System call is restartable       */
DECL|macro|SOL_ESTRPIPE
mdefine_line|#define&t;SOL_ESTRPIPE       92    /* Do not sleep in head of stream   */
DECL|macro|SOL_ENOTEMPTY
mdefine_line|#define&t;SOL_ENOTEMPTY      93    /* Rmdir of non-empty directory     */
DECL|macro|SOL_EUSERS
mdefine_line|#define&t;SOL_EUSERS         94    /* Over abundance of users for ufs  */
DECL|macro|SOL_ENOTSOCK
mdefine_line|#define&t;SOL_ENOTSOCK       95    /* Sock-op on non-sock              */
DECL|macro|SOL_EDESTADDRREQ
mdefine_line|#define&t;SOL_EDESTADDRREQ   96    /* No dest addr given, but needed   */
DECL|macro|SOL_EMSGSIZE
mdefine_line|#define&t;SOL_EMSGSIZE       97    /* Msg too big                      */
DECL|macro|SOL_EPROTOTYPE
mdefine_line|#define&t;SOL_EPROTOTYPE     98    /* Bad socket protocol              */
DECL|macro|SOL_ENOPROTOOPT
mdefine_line|#define&t;SOL_ENOPROTOOPT    99    /* Unavailable protocol             */
DECL|macro|SOL_EPROTONOSUPPORT
mdefine_line|#define&t;SOL_EPROTONOSUPPORT 120  /* Unsupported protocol             */
DECL|macro|SOL_ESOCKTNOSUPPORT
mdefine_line|#define&t;SOL_ESOCKTNOSUPPORT 121  /* Unsupported socket type          */
DECL|macro|SOL_EOPNOTSUPP
mdefine_line|#define&t;SOL_EOPNOTSUPP     122   /* Unsupported sock-op              */
DECL|macro|SOL_EPFNOSUPPORT
mdefine_line|#define&t;SOL_EPFNOSUPPORT   123   /* Unsupported protocol family      */
DECL|macro|SOL_EAFNOSUPPORT
mdefine_line|#define&t;SOL_EAFNOSUPPORT   124   /* Unsup addr family for protocol   */
DECL|macro|SOL_EADDRINUSE
mdefine_line|#define&t;SOL_EADDRINUSE     125   /* Req addr is already in use       */
DECL|macro|SOL_EADDRNOTAVAIL
mdefine_line|#define&t;SOL_EADDRNOTAVAIL  126   /* Req addr not available right now */
DECL|macro|SOL_ENETDOWN
mdefine_line|#define&t;SOL_ENETDOWN       127   /* Your subnet is on fire           */
DECL|macro|SOL_ENETUNREACH
mdefine_line|#define&t;SOL_ENETUNREACH    128   /* Someone playing with gateway and */
multiline_comment|/* did not tell you he was going to */
DECL|macro|SOL_ENETRESET
mdefine_line|#define&t;SOL_ENETRESET      129   /* Buy less-buggy ethernet cards    */
DECL|macro|SOL_ECONNABORTED
mdefine_line|#define&t;SOL_ECONNABORTED   130   /* Aborted connection due to sw     */
DECL|macro|SOL_ECONNRESET
mdefine_line|#define&t;SOL_ECONNRESET     131   /* Your peers reset your connection */
DECL|macro|SOL_ENOBUFS
mdefine_line|#define&t;SOL_ENOBUFS        132   /* No buffer space available        */
DECL|macro|SOL_EISCONN
mdefine_line|#define&t;SOL_EISCONN        133   /* Connect on already connected     */
multiline_comment|/* socket attempted                 */
DECL|macro|SOL_ENOTCONN
mdefine_line|#define&t;SOL_ENOTCONN       134   /* Comm on non-connected socket     */
DECL|macro|SOL_ESHUTDOWN
mdefine_line|#define&t;SOL_ESHUTDOWN      143   /* Op attempted after sock-shutdown */
DECL|macro|SOL_ETOOMANYREFS
mdefine_line|#define&t;SOL_ETOOMANYREFS   144   /* Reference limit exceeded         */
DECL|macro|SOL_ETIMEDOUT
mdefine_line|#define&t;SOL_ETIMEDOUT      145   /* Timed out connection             */
DECL|macro|SOL_ECONNREFUSED
mdefine_line|#define&t;SOL_ECONNREFUSED   146   /* Connection refused by remote host*/
DECL|macro|SOL_EHOSTDOWN
mdefine_line|#define&t;SOL_EHOSTDOWN      147   /* Remote host is up in flames      */
DECL|macro|SOL_EHOSTUNREACH
mdefine_line|#define&t;SOL_EHOSTUNREACH   148   /* Make a left at Easton Ave.....   */
DECL|macro|SOL_EWOULDBLOCK
mdefine_line|#define&t;SOL_EWOULDBLOCK    EAGAIN /* Just an alias */
DECL|macro|SOL_EALREADY
mdefine_line|#define&t;SOL_EALREADY       149   /* Operation is already occurring   */
DECL|macro|SOL_EINPROGRESS
mdefine_line|#define&t;SOL_EINPROGRESS    150   /* Operation is happening now       */
DECL|macro|SOL_ESTALE
mdefine_line|#define&t;SOL_ESTALE         151   /* Fungus growth on NFS file handle */
macro_line|#endif /* !(_SPARC64_SOLERRNO_H) */
eof
