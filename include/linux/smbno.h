macro_line|#ifndef _SMBNO_H_
DECL|macro|_SMBNO_H_
mdefine_line|#define _SMBNO_H_
multiline_comment|/* these define the attribute byte as seen by DOS */
DECL|macro|aRONLY
mdefine_line|#define aRONLY&t;(1L&lt;&lt;0)
DECL|macro|aHIDDEN
mdefine_line|#define aHIDDEN&t;(1L&lt;&lt;1)
DECL|macro|aSYSTEM
mdefine_line|#define aSYSTEM&t;(1L&lt;&lt;2)
DECL|macro|aVOLID
mdefine_line|#define aVOLID&t;(1L&lt;&lt;3)
DECL|macro|aDIR
mdefine_line|#define aDIR&t;(1L&lt;&lt;4)
DECL|macro|aARCH
mdefine_line|#define aARCH&t;(1L&lt;&lt;5)
multiline_comment|/* error classes */
DECL|macro|SUCCESS
mdefine_line|#define SUCCESS 0  /* The request was successful. */
DECL|macro|ERRDOS
mdefine_line|#define ERRDOS 0x01 /*  Error is from the core DOS operating system set. */
DECL|macro|ERRSRV
mdefine_line|#define ERRSRV 0x02 /* Error is generated by the server network file manager.*/
DECL|macro|ERRHRD
mdefine_line|#define ERRHRD 0x03  /* Error is an hardware error. */
DECL|macro|ERRCMD
mdefine_line|#define ERRCMD 0xFF  /* Command was not in the &quot;SMB&quot; format. */
multiline_comment|/* SMB X/Open error codes for the ERRdos error class */
DECL|macro|ERRbadfunc
mdefine_line|#define ERRbadfunc 1            /* Invalid function (or system call) */
DECL|macro|ERRbadfile
mdefine_line|#define ERRbadfile 2            /* File not found (pathname error) */
DECL|macro|ERRbadpath
mdefine_line|#define ERRbadpath 3            /* Directory not found */
DECL|macro|ERRnofids
mdefine_line|#define ERRnofids 4             /* Too many open files */
DECL|macro|ERRnoaccess
mdefine_line|#define ERRnoaccess 5           /* Access denied */
DECL|macro|ERRbadfid
mdefine_line|#define ERRbadfid 6             /* Invalid fid */
DECL|macro|ERRbadmcb
mdefine_line|#define ERRbadmcb 7             /* Memory control blocks destroyed */
DECL|macro|ERRnomem
mdefine_line|#define ERRnomem 8              /* Out of memory */
DECL|macro|ERRbadmem
mdefine_line|#define ERRbadmem 9             /* Invalid memory block address */
DECL|macro|ERRbadenv
mdefine_line|#define ERRbadenv 10            /* Invalid environment */
DECL|macro|ERRbadformat
mdefine_line|#define ERRbadformat 11         /* Invalid format */
DECL|macro|ERRbadaccess
mdefine_line|#define ERRbadaccess 12         /* Invalid open mode */
DECL|macro|ERRbaddata
mdefine_line|#define ERRbaddata 13           /* Invalid data (only from ioctl call) */
DECL|macro|ERRres
mdefine_line|#define ERRres 14               /* reserved */
DECL|macro|ERRbaddrive
mdefine_line|#define ERRbaddrive 15          /* Invalid drive */
DECL|macro|ERRremcd
mdefine_line|#define ERRremcd 16             /* Attempt to delete current directory */
DECL|macro|ERRdiffdevice
mdefine_line|#define ERRdiffdevice 17        /* rename/move across different filesystems */
DECL|macro|ERRnofiles
mdefine_line|#define ERRnofiles 18           /* no more files found in file search */
DECL|macro|ERRbadshare
mdefine_line|#define ERRbadshare 32          /* Share mode on file conflict with open mode */
DECL|macro|ERRlock
mdefine_line|#define ERRlock 33              /* Lock request conflicts with existing lock */
DECL|macro|ERRfilexists
mdefine_line|#define ERRfilexists 80         /* File in operation already exists */
DECL|macro|ERRbadpipe
mdefine_line|#define ERRbadpipe 230          /* Named pipe invalid */
DECL|macro|ERRpipebusy
mdefine_line|#define ERRpipebusy 231         /* All instances of pipe are busy */
DECL|macro|ERRpipeclosing
mdefine_line|#define ERRpipeclosing 232      /* named pipe close in progress */
DECL|macro|ERRnotconnected
mdefine_line|#define ERRnotconnected 233     /* No process on other end of named pipe */
DECL|macro|ERRmoredata
mdefine_line|#define ERRmoredata 234         /* More data to be returned */
DECL|macro|ERROR_INVALID_PARAMETER
mdefine_line|#define ERROR_INVALID_PARAMETER&t; 87
DECL|macro|ERROR_DISK_FULL
mdefine_line|#define ERROR_DISK_FULL&t;&t;112
DECL|macro|ERROR_INVALID_NAME
mdefine_line|#define ERROR_INVALID_NAME&t;123
DECL|macro|ERROR_DIR_NOT_EMPTY
mdefine_line|#define ERROR_DIR_NOT_EMPTY&t;145
DECL|macro|ERROR_NOT_LOCKED
mdefine_line|#define ERROR_NOT_LOCKED&t;158
DECL|macro|ERROR_ALREADY_EXISTS
mdefine_line|#define ERROR_ALREADY_EXISTS&t;183  /* see also 80 ? */
DECL|macro|ERROR_EAS_DIDNT_FIT
mdefine_line|#define ERROR_EAS_DIDNT_FIT&t;275 /* Extended attributes didn&squot;t fit */
DECL|macro|ERROR_EAS_NOT_SUPPORTED
mdefine_line|#define ERROR_EAS_NOT_SUPPORTED&t;282 /* Extended attributes not supported */
multiline_comment|/* Error codes for the ERRSRV class */
DECL|macro|ERRerror
mdefine_line|#define ERRerror 1              /* Non specific error code */
DECL|macro|ERRbadpw
mdefine_line|#define ERRbadpw 2              /* Bad password */
DECL|macro|ERRbadtype
mdefine_line|#define ERRbadtype 3            /* reserved */
DECL|macro|ERRaccess
mdefine_line|#define ERRaccess 4          /* No permissions to do the requested operation */
DECL|macro|ERRinvnid
mdefine_line|#define ERRinvnid 5             /* tid invalid */
DECL|macro|ERRinvnetname
mdefine_line|#define ERRinvnetname 6         /* Invalid servername */
DECL|macro|ERRinvdevice
mdefine_line|#define ERRinvdevice 7          /* Invalid device */
DECL|macro|ERRqfull
mdefine_line|#define ERRqfull 49             /* Print queue full */
DECL|macro|ERRqtoobig
mdefine_line|#define ERRqtoobig 50           /* Queued item too big */
DECL|macro|ERRinvpfid
mdefine_line|#define ERRinvpfid 52           /* Invalid print file in smb_fid */
DECL|macro|ERRsmbcmd
mdefine_line|#define ERRsmbcmd 64            /* Unrecognised command */
DECL|macro|ERRsrverror
mdefine_line|#define ERRsrverror 65          /* smb server internal error */
DECL|macro|ERRfilespecs
mdefine_line|#define ERRfilespecs 67         /* fid and pathname invalid combination */
DECL|macro|ERRbadlink
mdefine_line|#define ERRbadlink 68           /* reserved */
DECL|macro|ERRbadpermits
mdefine_line|#define ERRbadpermits 69        /* Access specified for a file is not valid */
DECL|macro|ERRbadpid
mdefine_line|#define ERRbadpid 70            /* reserved */
DECL|macro|ERRsetattrmode
mdefine_line|#define ERRsetattrmode 71       /* attribute mode invalid */
DECL|macro|ERRpaused
mdefine_line|#define ERRpaused 81            /* Message server paused */
DECL|macro|ERRmsgoff
mdefine_line|#define ERRmsgoff 82            /* Not receiving messages */
DECL|macro|ERRnoroom
mdefine_line|#define ERRnoroom 83            /* No room for message */
DECL|macro|ERRrmuns
mdefine_line|#define ERRrmuns 87             /* too many remote usernames */
DECL|macro|ERRtimeout
mdefine_line|#define ERRtimeout 88           /* operation timed out */
DECL|macro|ERRnoresource
mdefine_line|#define ERRnoresource  89   /* No resources currently available for request. */
DECL|macro|ERRtoomanyuids
mdefine_line|#define ERRtoomanyuids 90       /* too many userids */
DECL|macro|ERRbaduid
mdefine_line|#define ERRbaduid 91            /* bad userid */
DECL|macro|ERRuseMPX
mdefine_line|#define ERRuseMPX 250    /* temporarily unable to use raw mode, use MPX mode */
DECL|macro|ERRuseSTD
mdefine_line|#define ERRuseSTD 251    /* temporarily unable to use raw mode, use std.mode */
DECL|macro|ERRcontMPX
mdefine_line|#define ERRcontMPX 252          /* resume MPX mode */
DECL|macro|ERRbadPW
mdefine_line|#define ERRbadPW                /* reserved */
DECL|macro|ERRnosupport
mdefine_line|#define ERRnosupport 0xFFFF
multiline_comment|/* Error codes for the ERRHRD class */
DECL|macro|ERRnowrite
mdefine_line|#define ERRnowrite 19           /* read only media */
DECL|macro|ERRbadunit
mdefine_line|#define ERRbadunit 20           /* Unknown device */
DECL|macro|ERRnotready
mdefine_line|#define ERRnotready 21          /* Drive not ready */
DECL|macro|ERRbadcmd
mdefine_line|#define ERRbadcmd 22            /* Unknown command */
DECL|macro|ERRdata
mdefine_line|#define ERRdata 23              /* Data (CRC) error */
DECL|macro|ERRbadreq
mdefine_line|#define ERRbadreq 24            /* Bad request structure length */
DECL|macro|ERRseek
mdefine_line|#define ERRseek 25
DECL|macro|ERRbadmedia
mdefine_line|#define ERRbadmedia 26
DECL|macro|ERRbadsector
mdefine_line|#define ERRbadsector 27
DECL|macro|ERRnopaper
mdefine_line|#define ERRnopaper 28
DECL|macro|ERRwrite
mdefine_line|#define ERRwrite 29             /* write fault */
DECL|macro|ERRread
mdefine_line|#define ERRread 30              /* read fault */
DECL|macro|ERRgeneral
mdefine_line|#define ERRgeneral 31           /* General hardware failure */
DECL|macro|ERRwrongdisk
mdefine_line|#define ERRwrongdisk 34
DECL|macro|ERRFCBunavail
mdefine_line|#define ERRFCBunavail 35
DECL|macro|ERRsharebufexc
mdefine_line|#define ERRsharebufexc 36       /* share buffer exceeded */
DECL|macro|ERRdiskfull
mdefine_line|#define ERRdiskfull 39
multiline_comment|/*&n; * Access modes when opening a file&n; */
DECL|macro|SMB_ACCMASK
mdefine_line|#define SMB_ACCMASK&t;0x0003
DECL|macro|SMB_O_RDONLY
mdefine_line|#define SMB_O_RDONLY&t;0x0000
DECL|macro|SMB_O_WRONLY
mdefine_line|#define SMB_O_WRONLY&t;0x0001
DECL|macro|SMB_O_RDWR
mdefine_line|#define SMB_O_RDWR&t;0x0002
multiline_comment|/* offsets into message for common items */
DECL|macro|smb_com
mdefine_line|#define smb_com 8
DECL|macro|smb_rcls
mdefine_line|#define smb_rcls 9
DECL|macro|smb_reh
mdefine_line|#define smb_reh 10
DECL|macro|smb_err
mdefine_line|#define smb_err 11
DECL|macro|smb_flg
mdefine_line|#define smb_flg 13
DECL|macro|smb_flg2
mdefine_line|#define smb_flg2 14
DECL|macro|smb_reb
mdefine_line|#define smb_reb 13
DECL|macro|smb_tid
mdefine_line|#define smb_tid 28
DECL|macro|smb_pid
mdefine_line|#define smb_pid 30
DECL|macro|smb_uid
mdefine_line|#define smb_uid 32
DECL|macro|smb_mid
mdefine_line|#define smb_mid 34
DECL|macro|smb_wct
mdefine_line|#define smb_wct 36
DECL|macro|smb_vwv
mdefine_line|#define smb_vwv 37
DECL|macro|smb_vwv0
mdefine_line|#define smb_vwv0 37
DECL|macro|smb_vwv1
mdefine_line|#define smb_vwv1 39
DECL|macro|smb_vwv2
mdefine_line|#define smb_vwv2 41
DECL|macro|smb_vwv3
mdefine_line|#define smb_vwv3 43
DECL|macro|smb_vwv4
mdefine_line|#define smb_vwv4 45
DECL|macro|smb_vwv5
mdefine_line|#define smb_vwv5 47
DECL|macro|smb_vwv6
mdefine_line|#define smb_vwv6 49
DECL|macro|smb_vwv7
mdefine_line|#define smb_vwv7 51
DECL|macro|smb_vwv8
mdefine_line|#define smb_vwv8 53
DECL|macro|smb_vwv9
mdefine_line|#define smb_vwv9 55
DECL|macro|smb_vwv10
mdefine_line|#define smb_vwv10 57
DECL|macro|smb_vwv11
mdefine_line|#define smb_vwv11 59
DECL|macro|smb_vwv12
mdefine_line|#define smb_vwv12 61
DECL|macro|smb_vwv13
mdefine_line|#define smb_vwv13 63
DECL|macro|smb_vwv14
mdefine_line|#define smb_vwv14 65
multiline_comment|/* these are the trans2 sub fields for primary requests */
DECL|macro|smb_tpscnt
mdefine_line|#define smb_tpscnt smb_vwv0
DECL|macro|smb_tdscnt
mdefine_line|#define smb_tdscnt smb_vwv1
DECL|macro|smb_mprcnt
mdefine_line|#define smb_mprcnt smb_vwv2
DECL|macro|smb_mdrcnt
mdefine_line|#define smb_mdrcnt smb_vwv3
DECL|macro|smb_msrcnt
mdefine_line|#define smb_msrcnt smb_vwv4
DECL|macro|smb_flags
mdefine_line|#define smb_flags smb_vwv5
DECL|macro|smb_timeout
mdefine_line|#define smb_timeout smb_vwv6
DECL|macro|smb_pscnt
mdefine_line|#define smb_pscnt smb_vwv9
DECL|macro|smb_psoff
mdefine_line|#define smb_psoff smb_vwv10
DECL|macro|smb_dscnt
mdefine_line|#define smb_dscnt smb_vwv11
DECL|macro|smb_dsoff
mdefine_line|#define smb_dsoff smb_vwv12
DECL|macro|smb_suwcnt
mdefine_line|#define smb_suwcnt smb_vwv13
DECL|macro|smb_setup
mdefine_line|#define smb_setup smb_vwv14
DECL|macro|smb_setup0
mdefine_line|#define smb_setup0 smb_setup
DECL|macro|smb_setup1
mdefine_line|#define smb_setup1 (smb_setup+2)
DECL|macro|smb_setup2
mdefine_line|#define smb_setup2 (smb_setup+4)
multiline_comment|/* these are for the secondary requests */
DECL|macro|smb_spscnt
mdefine_line|#define smb_spscnt smb_vwv2
DECL|macro|smb_spsoff
mdefine_line|#define smb_spsoff smb_vwv3
DECL|macro|smb_spsdisp
mdefine_line|#define smb_spsdisp smb_vwv4
DECL|macro|smb_sdscnt
mdefine_line|#define smb_sdscnt smb_vwv5
DECL|macro|smb_sdsoff
mdefine_line|#define smb_sdsoff smb_vwv6
DECL|macro|smb_sdsdisp
mdefine_line|#define smb_sdsdisp smb_vwv7
DECL|macro|smb_sfid
mdefine_line|#define smb_sfid smb_vwv8
multiline_comment|/* and these for responses */
DECL|macro|smb_tprcnt
mdefine_line|#define smb_tprcnt smb_vwv0
DECL|macro|smb_tdrcnt
mdefine_line|#define smb_tdrcnt smb_vwv1
DECL|macro|smb_prcnt
mdefine_line|#define smb_prcnt smb_vwv3
DECL|macro|smb_proff
mdefine_line|#define smb_proff smb_vwv4
DECL|macro|smb_prdisp
mdefine_line|#define smb_prdisp smb_vwv5
DECL|macro|smb_drcnt
mdefine_line|#define smb_drcnt smb_vwv6
DECL|macro|smb_droff
mdefine_line|#define smb_droff smb_vwv7
DECL|macro|smb_drdisp
mdefine_line|#define smb_drdisp smb_vwv8
multiline_comment|/* the complete */
DECL|macro|SMBmkdir
mdefine_line|#define SMBmkdir      0x00   /* create directory */
DECL|macro|SMBrmdir
mdefine_line|#define SMBrmdir      0x01   /* delete directory */
DECL|macro|SMBopen
mdefine_line|#define SMBopen       0x02   /* open file */
DECL|macro|SMBcreate
mdefine_line|#define SMBcreate     0x03   /* create file */
DECL|macro|SMBclose
mdefine_line|#define SMBclose      0x04   /* close file */
DECL|macro|SMBflush
mdefine_line|#define SMBflush      0x05   /* flush file */
DECL|macro|SMBunlink
mdefine_line|#define SMBunlink     0x06   /* delete file */
DECL|macro|SMBmv
mdefine_line|#define SMBmv         0x07   /* rename file */
DECL|macro|SMBgetatr
mdefine_line|#define SMBgetatr     0x08   /* get file attributes */
DECL|macro|SMBsetatr
mdefine_line|#define SMBsetatr     0x09   /* set file attributes */
DECL|macro|SMBread
mdefine_line|#define SMBread       0x0A   /* read from file */
DECL|macro|SMBwrite
mdefine_line|#define SMBwrite      0x0B   /* write to file */
DECL|macro|SMBlock
mdefine_line|#define SMBlock       0x0C   /* lock byte range */
DECL|macro|SMBunlock
mdefine_line|#define SMBunlock     0x0D   /* unlock byte range */
DECL|macro|SMBctemp
mdefine_line|#define SMBctemp      0x0E   /* create temporary file */
DECL|macro|SMBmknew
mdefine_line|#define SMBmknew      0x0F   /* make new file */
DECL|macro|SMBchkpth
mdefine_line|#define SMBchkpth     0x10   /* check directory path */
DECL|macro|SMBexit
mdefine_line|#define SMBexit       0x11   /* process exit */
DECL|macro|SMBlseek
mdefine_line|#define SMBlseek      0x12   /* seek */
DECL|macro|SMBtcon
mdefine_line|#define SMBtcon       0x70   /* tree connect */
DECL|macro|SMBtconX
mdefine_line|#define SMBtconX      0x75   /* tree connect and X*/
DECL|macro|SMBtdis
mdefine_line|#define SMBtdis       0x71   /* tree disconnect */
DECL|macro|SMBnegprot
mdefine_line|#define SMBnegprot    0x72   /* negotiate protocol */
DECL|macro|SMBdskattr
mdefine_line|#define SMBdskattr    0x80   /* get disk attributes */
DECL|macro|SMBsearch
mdefine_line|#define SMBsearch     0x81   /* search directory */
DECL|macro|SMBsplopen
mdefine_line|#define SMBsplopen    0xC0   /* open print spool file */
DECL|macro|SMBsplwr
mdefine_line|#define SMBsplwr      0xC1   /* write to print spool file */
DECL|macro|SMBsplclose
mdefine_line|#define SMBsplclose   0xC2   /* close print spool file */
DECL|macro|SMBsplretq
mdefine_line|#define SMBsplretq    0xC3   /* return print queue */
DECL|macro|SMBsends
mdefine_line|#define SMBsends      0xD0   /* send single block message */
DECL|macro|SMBsendb
mdefine_line|#define SMBsendb      0xD1   /* send broadcast message */
DECL|macro|SMBfwdname
mdefine_line|#define SMBfwdname    0xD2   /* forward user name */
DECL|macro|SMBcancelf
mdefine_line|#define SMBcancelf    0xD3   /* cancel forward */
DECL|macro|SMBgetmac
mdefine_line|#define SMBgetmac     0xD4   /* get machine name */
DECL|macro|SMBsendstrt
mdefine_line|#define SMBsendstrt   0xD5   /* send start of multi-block message */
DECL|macro|SMBsendend
mdefine_line|#define SMBsendend    0xD6   /* send end of multi-block message */
DECL|macro|SMBsendtxt
mdefine_line|#define SMBsendtxt    0xD7   /* send text of multi-block message */
multiline_comment|/* Core+ protocol */
DECL|macro|SMBlockread
mdefine_line|#define SMBlockread&t;  0x13   /* Lock a range and read */
DECL|macro|SMBwriteunlock
mdefine_line|#define SMBwriteunlock 0x14 /* Unlock a range then write */
DECL|macro|SMBreadbraw
mdefine_line|#define SMBreadbraw   0x1a  /* read a block of data with no smb header */
DECL|macro|SMBwritebraw
mdefine_line|#define SMBwritebraw  0x1d  /* write a block of data with no smb header */
DECL|macro|SMBwritec
mdefine_line|#define SMBwritec     0x20  /* secondary write request */
DECL|macro|SMBwriteclose
mdefine_line|#define SMBwriteclose 0x2c  /* write a file then close it */
multiline_comment|/* dos extended protocol */
DECL|macro|SMBreadBraw
mdefine_line|#define SMBreadBraw      0x1A   /* read block raw */
DECL|macro|SMBreadBmpx
mdefine_line|#define SMBreadBmpx      0x1B   /* read block multiplexed */
DECL|macro|SMBreadBs
mdefine_line|#define SMBreadBs        0x1C   /* read block (secondary response) */
DECL|macro|SMBwriteBraw
mdefine_line|#define SMBwriteBraw     0x1D   /* write block raw */
DECL|macro|SMBwriteBmpx
mdefine_line|#define SMBwriteBmpx     0x1E   /* write block multiplexed */
DECL|macro|SMBwriteBs
mdefine_line|#define SMBwriteBs       0x1F   /* write block (secondary request) */
DECL|macro|SMBwriteC
mdefine_line|#define SMBwriteC        0x20   /* write complete response */
DECL|macro|SMBsetattrE
mdefine_line|#define SMBsetattrE      0x22   /* set file attributes expanded */
DECL|macro|SMBgetattrE
mdefine_line|#define SMBgetattrE      0x23   /* get file attributes expanded */
DECL|macro|SMBlockingX
mdefine_line|#define SMBlockingX      0x24   /* lock/unlock byte ranges and X */
DECL|macro|SMBtrans
mdefine_line|#define SMBtrans         0x25   /* transaction - name, bytes in/out */
DECL|macro|SMBtranss
mdefine_line|#define SMBtranss        0x26   /* transaction (secondary request/response) */
DECL|macro|SMBioctl
mdefine_line|#define SMBioctl         0x27   /* IOCTL */
DECL|macro|SMBioctls
mdefine_line|#define SMBioctls        0x28   /* IOCTL  (secondary request/response) */
DECL|macro|SMBcopy
mdefine_line|#define SMBcopy          0x29   /* copy */
DECL|macro|SMBmove
mdefine_line|#define SMBmove          0x2A   /* move */
DECL|macro|SMBecho
mdefine_line|#define SMBecho          0x2B   /* echo */
DECL|macro|SMBopenX
mdefine_line|#define SMBopenX         0x2D   /* open and X */
DECL|macro|SMBreadX
mdefine_line|#define SMBreadX         0x2E   /* read and X */
DECL|macro|SMBwriteX
mdefine_line|#define SMBwriteX        0x2F   /* write and X */
DECL|macro|SMBsesssetupX
mdefine_line|#define SMBsesssetupX    0x73   /* Session Set Up &amp; X (including User Logon) */
DECL|macro|SMBtconX
mdefine_line|#define SMBtconX         0x75   /* tree connect and X */
DECL|macro|SMBffirst
mdefine_line|#define SMBffirst        0x82   /* find first */
DECL|macro|SMBfunique
mdefine_line|#define SMBfunique       0x83   /* find unique */
DECL|macro|SMBfclose
mdefine_line|#define SMBfclose        0x84   /* find close */
DECL|macro|SMBinvalid
mdefine_line|#define SMBinvalid       0xFE   /* invalid command */
multiline_comment|/* Extended 2.0 protocol */
DECL|macro|SMBtrans2
mdefine_line|#define SMBtrans2        0x32   /* TRANS2 protocol set */
DECL|macro|SMBtranss2
mdefine_line|#define SMBtranss2       0x33   /* TRANS2 protocol set, secondary command */
DECL|macro|SMBfindclose
mdefine_line|#define SMBfindclose     0x34   /* Terminate a TRANSACT2_FINDFIRST */
DECL|macro|SMBfindnclose
mdefine_line|#define SMBfindnclose    0x35   /* Terminate a TRANSACT2_FINDNOTIFYFIRST */
DECL|macro|SMBulogoffX
mdefine_line|#define SMBulogoffX      0x74   /* user logoff */
multiline_comment|/* these are the TRANS2 sub commands */
DECL|macro|TRANSACT2_OPEN
mdefine_line|#define TRANSACT2_OPEN          0
DECL|macro|TRANSACT2_FINDFIRST
mdefine_line|#define TRANSACT2_FINDFIRST     1
DECL|macro|TRANSACT2_FINDNEXT
mdefine_line|#define TRANSACT2_FINDNEXT      2
DECL|macro|TRANSACT2_QFSINFO
mdefine_line|#define TRANSACT2_QFSINFO       3
DECL|macro|TRANSACT2_SETFSINFO
mdefine_line|#define TRANSACT2_SETFSINFO     4
DECL|macro|TRANSACT2_QPATHINFO
mdefine_line|#define TRANSACT2_QPATHINFO     5
DECL|macro|TRANSACT2_SETPATHINFO
mdefine_line|#define TRANSACT2_SETPATHINFO   6
DECL|macro|TRANSACT2_QFILEINFO
mdefine_line|#define TRANSACT2_QFILEINFO     7
DECL|macro|TRANSACT2_SETFILEINFO
mdefine_line|#define TRANSACT2_SETFILEINFO   8
DECL|macro|TRANSACT2_FSCTL
mdefine_line|#define TRANSACT2_FSCTL         9
DECL|macro|TRANSACT2_IOCTL
mdefine_line|#define TRANSACT2_IOCTL           10
DECL|macro|TRANSACT2_FINDNOTIFYFIRST
mdefine_line|#define TRANSACT2_FINDNOTIFYFIRST 11
DECL|macro|TRANSACT2_FINDNOTIFYNEXT
mdefine_line|#define TRANSACT2_FINDNOTIFYNEXT  12
DECL|macro|TRANSACT2_MKDIR
mdefine_line|#define TRANSACT2_MKDIR           13
macro_line|#endif /* _SMBNO_H_ */
eof
