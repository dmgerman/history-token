multiline_comment|/* $Id: memreg.h,v 1.8 1996/08/29 09:48:23 davem Exp $ */
macro_line|#ifndef _SPARC_MEMREG_H
DECL|macro|_SPARC_MEMREG_H
mdefine_line|#define _SPARC_MEMREG_H
multiline_comment|/* memreg.h:  Definitions of the values found in the synchronous&n; *            and asynchronous memory error registers when a fault&n; *            occurs on the sun4c.&n; *&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; */
multiline_comment|/* First the synchronous error codes, these are usually just&n; * normal page faults.&n; */
DECL|macro|SUN4C_SYNC_WDRESET
mdefine_line|#define SUN4C_SYNC_WDRESET   0x0001  /* watchdog reset */
DECL|macro|SUN4C_SYNC_SIZE
mdefine_line|#define SUN4C_SYNC_SIZE      0x0002  /* bad access size? whuz this? */
DECL|macro|SUN4C_SYNC_PARITY
mdefine_line|#define SUN4C_SYNC_PARITY    0x0008  /* bad ram chips caused a parity error */
DECL|macro|SUN4C_SYNC_SBUS
mdefine_line|#define SUN4C_SYNC_SBUS      0x0010  /* the SBUS had some problems... */
DECL|macro|SUN4C_SYNC_NOMEM
mdefine_line|#define SUN4C_SYNC_NOMEM     0x0020  /* translation to non-existent ram */
DECL|macro|SUN4C_SYNC_PROT
mdefine_line|#define SUN4C_SYNC_PROT      0x0040  /* access violated pte protections */
DECL|macro|SUN4C_SYNC_NPRESENT
mdefine_line|#define SUN4C_SYNC_NPRESENT  0x0080  /* pte said that page was not present */
DECL|macro|SUN4C_SYNC_BADWRITE
mdefine_line|#define SUN4C_SYNC_BADWRITE  0x8000  /* while writing something went bogus */
DECL|macro|SUN4C_SYNC_BOLIXED
mdefine_line|#define SUN4C_SYNC_BOLIXED  &bslash;&n;        (SUN4C_SYNC_WDRESET | SUN4C_SYNC_SIZE | SUN4C_SYNC_SBUS | &bslash;&n;         SUN4C_SYNC_NOMEM | SUN4C_SYNC_PARITY)
multiline_comment|/* Now the asynchronous error codes, these are almost always produced&n; * by the cache writing things back to memory and getting a bad translation.&n; * Bad DVMA transactions can cause these faults too.&n; */
DECL|macro|SUN4C_ASYNC_BADDVMA
mdefine_line|#define SUN4C_ASYNC_BADDVMA 0x0010  /* error during DVMA access */
DECL|macro|SUN4C_ASYNC_NOMEM
mdefine_line|#define SUN4C_ASYNC_NOMEM   0x0020  /* write back pointed to bad phys addr */
DECL|macro|SUN4C_ASYNC_BADWB
mdefine_line|#define SUN4C_ASYNC_BADWB   0x0080  /* write back points to non-present page */
multiline_comment|/* Memory parity error register with associated bit constants. */
macro_line|#ifndef __ASSEMBLY__
r_extern
id|__volatile__
r_int
r_int
op_star
id|sun4c_memerr_reg
suffix:semicolon
macro_line|#endif
DECL|macro|SUN4C_MPE_ERROR
mdefine_line|#define&t;SUN4C_MPE_ERROR&t;0x80&t;/* Parity error detected. (ro) */
DECL|macro|SUN4C_MPE_MULTI
mdefine_line|#define&t;SUN4C_MPE_MULTI&t;0x40&t;/* Multiple parity errors detected. (ro) */
DECL|macro|SUN4C_MPE_TEST
mdefine_line|#define&t;SUN4C_MPE_TEST&t;0x20&t;/* Write inverse parity. (rw) */
DECL|macro|SUN4C_MPE_CHECK
mdefine_line|#define&t;SUN4C_MPE_CHECK&t;0x10&t;/* Enable parity checking. (rw) */
DECL|macro|SUN4C_MPE_ERR00
mdefine_line|#define&t;SUN4C_MPE_ERR00&t;0x08&t;/* Parity error in bits 0-7. (ro) */
DECL|macro|SUN4C_MPE_ERR08
mdefine_line|#define&t;SUN4C_MPE_ERR08&t;0x04&t;/* Parity error in bits 8-15. (ro) */
DECL|macro|SUN4C_MPE_ERR16
mdefine_line|#define&t;SUN4C_MPE_ERR16&t;0x02&t;/* Parity error in bits 16-23. (ro) */
DECL|macro|SUN4C_MPE_ERR24
mdefine_line|#define&t;SUN4C_MPE_ERR24&t;0x01&t;/* Parity error in bits 24-31. (ro) */
DECL|macro|SUN4C_MPE_ERRS
mdefine_line|#define&t;SUN4C_MPE_ERRS&t;0x0F&t;/* Bit mask for the error bits. (ro) */
macro_line|#endif /* !(_SPARC_MEMREG_H) */
eof
