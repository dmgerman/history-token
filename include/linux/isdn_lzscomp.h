multiline_comment|/*&n; * $Id: isdn_lzscomp.h,v 1.1 1998/07/08 16:52:33 hipp Exp $&n; *&n; * Header for isdn_lzscomp.c&n; * Concentrated here to not mess up half a dozen kernel headers with code&n; * snippets&n; *&n; */
DECL|macro|CI_LZS_COMPRESS
mdefine_line|#define CI_LZS_COMPRESS&t;&t;17
DECL|macro|CILEN_LZS_COMPRESS
mdefine_line|#define CILEN_LZS_COMPRESS&t;5
DECL|macro|LZS_CMODE_NONE
mdefine_line|#define LZS_CMODE_NONE&t;&t;0
DECL|macro|LZS_CMODE_LCB
mdefine_line|#define LZS_CMODE_LCB&t;&t;1
DECL|macro|LZS_CMODE_CRC
mdefine_line|#define LZS_CMODE_CRC&t;&t;2
DECL|macro|LZS_CMODE_SEQNO
mdefine_line|#define LZS_CMODE_SEQNO&t;&t;3&t;/* MUST be implemented (default) */
DECL|macro|LZS_CMODE_EXT
mdefine_line|#define LZS_CMODE_EXT&t;&t;4&t;/* Seems to be what Win0.95 uses */
DECL|macro|LZS_COMP_MAX_HISTS
mdefine_line|#define LZS_COMP_MAX_HISTS&t;1&t;/* Don&squot;t waste peers ressources */
DECL|macro|LZS_COMP_DEF_HISTS
mdefine_line|#define LZS_COMP_DEF_HISTS&t;1&t;/* Most likely to negotiate */
DECL|macro|LZS_DECOMP_MAX_HISTS
mdefine_line|#define LZS_DECOMP_MAX_HISTS&t;32&t;/* More is really nonsense */
DECL|macro|LZS_DECOMP_DEF_HISTS
mdefine_line|#define LZS_DECOMP_DEF_HISTS&t;8&t;/* If we get it, this may be optimal */
DECL|macro|LZS_HIST_BYTE1
mdefine_line|#define LZS_HIST_BYTE1(word)   &t;(word&gt;&gt;8)&t;/* Just for better reading */
DECL|macro|LZS_HIST_BYTE2
mdefine_line|#define LZS_HIST_BYTE2(word)&t;(word&amp;0xff)&t;/* of this big endian stuff */
DECL|macro|LZS_HIST_WORD
mdefine_line|#define LZS_HIST_WORD(b1,b2)&t;((b1&lt;&lt;8)|b2)&t;/* (network byte order rulez) */
eof
