multiline_comment|/*&n; *&t;Swansea University Computer Society&t;NET3&n; *&t;&n; *&t;This file declares the constants of special use with the SLIP/CSLIP/&n; *&t;KISS TNC driver.&n; */
macro_line|#ifndef __LINUX_SLIP_H
DECL|macro|__LINUX_SLIP_H
mdefine_line|#define __LINUX_SLIP_H
DECL|macro|SL_MODE_SLIP
mdefine_line|#define&t;&t;SL_MODE_SLIP&t;&t;0
DECL|macro|SL_MODE_CSLIP
mdefine_line|#define&t;&t;SL_MODE_CSLIP&t;&t;1
DECL|macro|SL_MODE_KISS
mdefine_line|#define &t;SL_MODE_KISS&t;&t;4
DECL|macro|SL_OPT_SIXBIT
mdefine_line|#define&t;&t;SL_OPT_SIXBIT&t;&t;2
DECL|macro|SL_OPT_ADAPTIVE
mdefine_line|#define&t;&t;SL_OPT_ADAPTIVE&t;&t;8
multiline_comment|/*&n; *&t;VSV = ioctl for keepalive &amp; outfill in SLIP driver &n; */
DECL|macro|SIOCSKEEPALIVE
mdefine_line|#define SIOCSKEEPALIVE&t;(SIOCDEVPRIVATE)&t;&t;/* Set keepalive timeout in sec */
DECL|macro|SIOCGKEEPALIVE
mdefine_line|#define SIOCGKEEPALIVE&t;(SIOCDEVPRIVATE+1)&t;&t;/* Get keepalive timeout */
DECL|macro|SIOCSOUTFILL
mdefine_line|#define SIOCSOUTFILL&t;(SIOCDEVPRIVATE+2)&t;&t;/* Set outfill timeout */
DECL|macro|SIOCGOUTFILL
mdefine_line|#define&t;SIOCGOUTFILL&t;(SIOCDEVPRIVATE+3)&t;&t;/* Get outfill timeout */
DECL|macro|SIOCSLEASE
mdefine_line|#define SIOCSLEASE&t;(SIOCDEVPRIVATE+4)&t;&t;/* Set &quot;leased&quot; line type */
DECL|macro|SIOCGLEASE
mdefine_line|#define&t;SIOCGLEASE&t;(SIOCDEVPRIVATE+5)&t;&t;/* Get line type */
macro_line|#endif
eof
