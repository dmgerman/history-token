multiline_comment|/* sonet.h - SONET/SHD physical layer control */
multiline_comment|/* Written 1995-2000 by Werner Almesberger, EPFL LRC/ICA */
macro_line|#ifndef LINUX_SONET_H
DECL|macro|LINUX_SONET_H
mdefine_line|#define LINUX_SONET_H
DECL|macro|__SONET_ITEMS
mdefine_line|#define __SONET_ITEMS &bslash;&n;    __HANDLE_ITEM(section_bip); &t;/* section parity errors (B1) */ &bslash;&n;    __HANDLE_ITEM(line_bip);&t;&t;/* line parity errors (B2) */ &bslash;&n;    __HANDLE_ITEM(path_bip);&t;&t;/* path parity errors (B3) */ &bslash;&n;    __HANDLE_ITEM(line_febe);&t;&t;/* line parity errors at remote */ &bslash;&n;    __HANDLE_ITEM(path_febe);&t;&t;/* path parity errors at remote */ &bslash;&n;    __HANDLE_ITEM(corr_hcs);&t;&t;/* correctable header errors */ &bslash;&n;    __HANDLE_ITEM(uncorr_hcs);&t;&t;/* uncorrectable header errors */ &bslash;&n;    __HANDLE_ITEM(tx_cells);&t;&t;/* cells sent */ &bslash;&n;    __HANDLE_ITEM(rx_cells);&t;&t;/* cells received */
DECL|struct|sonet_stats
r_struct
id|sonet_stats
(brace
DECL|macro|__HANDLE_ITEM
mdefine_line|#define __HANDLE_ITEM(i) int i
id|__SONET_ITEMS
DECL|macro|__HANDLE_ITEM
macro_line|#undef __HANDLE_ITEM
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|macro|SONET_GETSTAT
mdefine_line|#define SONET_GETSTAT&t;_IOR(&squot;a&squot;,ATMIOC_PHYTYP,struct sonet_stats)
multiline_comment|/* get statistics */
DECL|macro|SONET_GETSTATZ
mdefine_line|#define SONET_GETSTATZ&t;_IOR(&squot;a&squot;,ATMIOC_PHYTYP+1,struct sonet_stats)
multiline_comment|/* ... and zero counters */
DECL|macro|SONET_SETDIAG
mdefine_line|#define SONET_SETDIAG&t;_IOWR(&squot;a&squot;,ATMIOC_PHYTYP+2,int)
multiline_comment|/* set error insertion */
DECL|macro|SONET_CLRDIAG
mdefine_line|#define SONET_CLRDIAG&t;_IOWR(&squot;a&squot;,ATMIOC_PHYTYP+3,int)
multiline_comment|/* clear error insertion */
DECL|macro|SONET_GETDIAG
mdefine_line|#define SONET_GETDIAG&t;_IOR(&squot;a&squot;,ATMIOC_PHYTYP+4,int)
multiline_comment|/* query error insertion */
DECL|macro|SONET_SETFRAMING
mdefine_line|#define SONET_SETFRAMING _IO(&squot;a&squot;,ATMIOC_PHYTYP+5)
multiline_comment|/* set framing mode (SONET/SDH) */
DECL|macro|SONET_GETFRAMING
mdefine_line|#define SONET_GETFRAMING _IOR(&squot;a&squot;,ATMIOC_PHYTYP+6,int)
multiline_comment|/* get framing mode */
DECL|macro|SONET_GETFRSENSE
mdefine_line|#define SONET_GETFRSENSE _IOR(&squot;a&squot;,ATMIOC_PHYTYP+7, &bslash;&n;  unsigned char[SONET_FRSENSE_SIZE])&t;/* get framing sense information */
DECL|macro|SONET_INS_SBIP
mdefine_line|#define SONET_INS_SBIP&t;  1&t;&t;/* section BIP */
DECL|macro|SONET_INS_LBIP
mdefine_line|#define SONET_INS_LBIP&t;  2&t;&t;/* line BIP */
DECL|macro|SONET_INS_PBIP
mdefine_line|#define SONET_INS_PBIP&t;  4&t;&t;/* path BIP */
DECL|macro|SONET_INS_FRAME
mdefine_line|#define SONET_INS_FRAME&t;  8&t;&t;/* out of frame */
DECL|macro|SONET_INS_LOS
mdefine_line|#define SONET_INS_LOS&t; 16&t;&t;/* set line to zero */
DECL|macro|SONET_INS_LAIS
mdefine_line|#define SONET_INS_LAIS&t; 32&t;&t;/* line alarm indication signal */
DECL|macro|SONET_INS_PAIS
mdefine_line|#define SONET_INS_PAIS&t; 64&t;&t;/* path alarm indication signal */
DECL|macro|SONET_INS_HCS
mdefine_line|#define SONET_INS_HCS&t;128&t;&t;/* insert HCS error */
DECL|macro|SONET_FRAME_SONET
mdefine_line|#define SONET_FRAME_SONET 0&t;&t;/* SONET STS-3 framing */
DECL|macro|SONET_FRAME_SDH
mdefine_line|#define SONET_FRAME_SDH   1&t;&t;/* SDH STM-1 framing */
DECL|macro|SONET_FRSENSE_SIZE
mdefine_line|#define SONET_FRSENSE_SIZE 6&t;&t;/* C1[3],H1[3] (0xff for unknown) */
macro_line|#ifndef __KERNEL__
DECL|macro|__SONET_ITEMS
macro_line|#undef __SONET_ITEMS
macro_line|#else
macro_line|#include &lt;asm/atomic.h&gt;
DECL|struct|k_sonet_stats
r_struct
id|k_sonet_stats
(brace
DECL|macro|__HANDLE_ITEM
mdefine_line|#define __HANDLE_ITEM(i) atomic_t i
id|__SONET_ITEMS
DECL|macro|__HANDLE_ITEM
macro_line|#undef __HANDLE_ITEM
)brace
suffix:semicolon
r_extern
r_void
id|sonet_copy_stats
c_func
(paren
r_struct
id|k_sonet_stats
op_star
id|from
comma
r_struct
id|sonet_stats
op_star
id|to
)paren
suffix:semicolon
r_extern
r_void
id|sonet_subtract_stats
c_func
(paren
r_struct
id|k_sonet_stats
op_star
id|from
comma
r_struct
id|sonet_stats
op_star
id|to
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif
eof
