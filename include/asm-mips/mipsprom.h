macro_line|#ifndef __ASM_MIPS_PROM_H
DECL|macro|__ASM_MIPS_PROM_H
mdefine_line|#define __ASM_MIPS_PROM_H
DECL|macro|PROM_RESET
mdefine_line|#define PROM_RESET&t;&t;0
DECL|macro|PROM_EXEC
mdefine_line|#define PROM_EXEC&t;&t;1
DECL|macro|PROM_RESTART
mdefine_line|#define PROM_RESTART&t;&t;2
DECL|macro|PROM_REINIT
mdefine_line|#define PROM_REINIT&t;&t;3
DECL|macro|PROM_REBOOT
mdefine_line|#define PROM_REBOOT&t;&t;4
DECL|macro|PROM_AUTOBOOT
mdefine_line|#define PROM_AUTOBOOT&t;&t;5
DECL|macro|PROM_OPEN
mdefine_line|#define PROM_OPEN&t;&t;6
DECL|macro|PROM_READ
mdefine_line|#define PROM_READ&t;&t;7
DECL|macro|PROM_WRITE
mdefine_line|#define PROM_WRITE&t;&t;8
DECL|macro|PROM_IOCTL
mdefine_line|#define PROM_IOCTL&t;&t;9
DECL|macro|PROM_CLOSE
mdefine_line|#define PROM_CLOSE&t;&t;10
DECL|macro|PROM_GETCHAR
mdefine_line|#define PROM_GETCHAR&t;&t;11
DECL|macro|PROM_PUTCHAR
mdefine_line|#define PROM_PUTCHAR&t;&t;12
DECL|macro|PROM_SHOWCHAR
mdefine_line|#define PROM_SHOWCHAR&t;&t;13&t;/* XXX */
DECL|macro|PROM_GETS
mdefine_line|#define PROM_GETS&t;&t;14&t;/* XXX */
DECL|macro|PROM_PUTS
mdefine_line|#define PROM_PUTS&t;&t;15&t;/* XXX */
DECL|macro|PROM_PRINTF
mdefine_line|#define PROM_PRINTF&t;&t;16&t;/* XXX */
multiline_comment|/* What are these for? */
DECL|macro|PROM_INITPROTO
mdefine_line|#define PROM_INITPROTO&t;&t;17&t;/* XXX */
DECL|macro|PROM_PROTOENABLE
mdefine_line|#define PROM_PROTOENABLE&t;18&t;/* XXX */
DECL|macro|PROM_PROTODISABLE
mdefine_line|#define PROM_PROTODISABLE&t;19&t;/* XXX */
DECL|macro|PROM_GETPKT
mdefine_line|#define PROM_GETPKT&t;&t;20&t;/* XXX */
DECL|macro|PROM_PUTPKT
mdefine_line|#define PROM_PUTPKT&t;&t;21&t;/* XXX */
multiline_comment|/* More PROM shit.  Probably has to do with VME RMW cycles??? */
DECL|macro|PROM_ORW_RMW
mdefine_line|#define PROM_ORW_RMW&t;&t;22&t;/* XXX */
DECL|macro|PROM_ORH_RMW
mdefine_line|#define PROM_ORH_RMW&t;&t;23&t;/* XXX */
DECL|macro|PROM_ORB_RMW
mdefine_line|#define PROM_ORB_RMW&t;&t;24&t;/* XXX */
DECL|macro|PROM_ANDW_RMW
mdefine_line|#define PROM_ANDW_RMW&t;&t;25&t;/* XXX */
DECL|macro|PROM_ANDH_RMW
mdefine_line|#define PROM_ANDH_RMW&t;&t;26&t;/* XXX */
DECL|macro|PROM_ANDB_RMW
mdefine_line|#define PROM_ANDB_RMW&t;&t;27&t;/* XXX */
multiline_comment|/* Cache handling stuff */
DECL|macro|PROM_FLUSHCACHE
mdefine_line|#define PROM_FLUSHCACHE&t;&t;28&t;/* XXX */
DECL|macro|PROM_CLEARCACHE
mdefine_line|#define PROM_CLEARCACHE&t;&t;29&t;/* XXX */
multiline_comment|/* Libc alike stuff */
DECL|macro|PROM_SETJMP
mdefine_line|#define PROM_SETJMP&t;&t;30&t;/* XXX */
DECL|macro|PROM_LONGJMP
mdefine_line|#define PROM_LONGJMP&t;&t;31&t;/* XXX */
DECL|macro|PROM_BEVUTLB
mdefine_line|#define PROM_BEVUTLB&t;&t;32&t;/* XXX */
DECL|macro|PROM_GETENV
mdefine_line|#define PROM_GETENV&t;&t;33&t;/* XXX */
DECL|macro|PROM_SETENV
mdefine_line|#define PROM_SETENV&t;&t;34&t;/* XXX */
DECL|macro|PROM_ATOB
mdefine_line|#define PROM_ATOB&t;&t;35&t;/* XXX */
DECL|macro|PROM_STRCMP
mdefine_line|#define PROM_STRCMP&t;&t;36&t;/* XXX */
DECL|macro|PROM_STRLEN
mdefine_line|#define PROM_STRLEN&t;&t;37&t;/* XXX */
DECL|macro|PROM_STRCPY
mdefine_line|#define PROM_STRCPY&t;&t;38&t;/* XXX */
DECL|macro|PROM_STRCAT
mdefine_line|#define PROM_STRCAT&t;&t;39&t;/* XXX */
multiline_comment|/* Misc stuff */
DECL|macro|PROM_PARSER
mdefine_line|#define PROM_PARSER&t;&t;40&t;/* XXX */
DECL|macro|PROM_RANGE
mdefine_line|#define PROM_RANGE&t;&t;41&t;/* XXX */
DECL|macro|PROM_ARGVIZE
mdefine_line|#define PROM_ARGVIZE&t;&t;42&t;/* XXX */
DECL|macro|PROM_HELP
mdefine_line|#define PROM_HELP&t;&t;43&t;/* XXX */
multiline_comment|/* Entry points for some PROM commands */
DECL|macro|PROM_DUMPCMD
mdefine_line|#define PROM_DUMPCMD&t;&t;44&t;/* XXX */
DECL|macro|PROM_SETENVCMD
mdefine_line|#define PROM_SETENVCMD&t;&t;45&t;/* XXX */
DECL|macro|PROM_UNSETENVCMD
mdefine_line|#define PROM_UNSETENVCMD&t;46&t;/* XXX */
DECL|macro|PROM_PRINTENVCMD
mdefine_line|#define PROM_PRINTENVCMD&t;47&t;/* XXX */
DECL|macro|PROM_BEVEXCEPT
mdefine_line|#define PROM_BEVEXCEPT&t;&t;48&t;/* XXX */
DECL|macro|PROM_ENABLECMD
mdefine_line|#define PROM_ENABLECMD&t;&t;49&t;/* XXX */
DECL|macro|PROM_DISABLECMD
mdefine_line|#define PROM_DISABLECMD&t;&t;50&t;/* XXX */
DECL|macro|PROM_CLEARNOFAULT
mdefine_line|#define PROM_CLEARNOFAULT&t;51&t;/* XXX */
DECL|macro|PROM_NOTIMPLEMENT
mdefine_line|#define PROM_NOTIMPLEMENT&t;52&t;/* XXX */
DECL|macro|PROM_NV_GET
mdefine_line|#define PROM_NV_GET&t;&t;53&t;/* XXX */
DECL|macro|PROM_NV_SET
mdefine_line|#define PROM_NV_SET&t;&t;54&t;/* XXX */
macro_line|#endif /* __ASM_MIPS_PROM_H */
eof
