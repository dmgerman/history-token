DECL|macro|su_lasti
mdefine_line|#define su_lasti&t;u.bfs_sb.si_lasti
DECL|macro|su_blocks
mdefine_line|#define su_blocks&t;u.bfs_sb.si_blocks
DECL|macro|su_freeb
mdefine_line|#define su_freeb&t;u.bfs_sb.si_freeb
DECL|macro|su_freei
mdefine_line|#define su_freei&t;u.bfs_sb.si_freei
DECL|macro|su_lf_ioff
mdefine_line|#define su_lf_ioff&t;u.bfs_sb.si_lf_ioff
DECL|macro|su_lf_sblk
mdefine_line|#define su_lf_sblk&t;u.bfs_sb.si_lf_sblk
DECL|macro|su_lf_eblk
mdefine_line|#define su_lf_eblk&t;u.bfs_sb.si_lf_eblk
DECL|macro|su_imap
mdefine_line|#define su_imap&t;&t;u.bfs_sb.si_imap
DECL|macro|su_sbh
mdefine_line|#define su_sbh&t;&t;u.bfs_sb.si_sbh
DECL|macro|su_bfs_sb
mdefine_line|#define su_bfs_sb&t;u.bfs_sb.si_bfs_sb
DECL|macro|iu_dsk_ino
mdefine_line|#define iu_dsk_ino&t;u.bfs_i.i_dsk_ino
DECL|macro|iu_sblock
mdefine_line|#define iu_sblock&t;u.bfs_i.i_sblock
DECL|macro|iu_eblock
mdefine_line|#define iu_eblock&t;u.bfs_i.i_eblock
DECL|macro|printf
mdefine_line|#define printf(format, args...) &bslash;&n;&t;printk(KERN_ERR &quot;BFS-fs: &quot; __FUNCTION__ &quot;(): &quot; format, ## args)
eof
