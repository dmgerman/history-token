multiline_comment|/*&n; *  include/asm-s390/s390-gdbregs.h&n; *&n; *  S390 version&n; *    Copyright (C) 1999 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Denis Joseph Barrow (djbarrow@de.ibm.com,barrow_dj@yahoo.com)&n; *&n; *  used both by the linux kernel for remote debugging &amp; gdb &n; */
macro_line|#ifndef _S390_GDBREGS_H
DECL|macro|_S390_GDBREGS_H
mdefine_line|#define _S390_GDBREGS_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;asm/s390-regs-common.h&gt;
macro_line|#else
macro_line|#include &lt;s390/s390-regs-common.h&gt;
macro_line|#endif
DECL|macro|S390_MAX_INSTR_SIZE
mdefine_line|#define S390_MAX_INSTR_SIZE 6
DECL|macro|NUM_REGS
mdefine_line|#define NUM_REGS      (2+NUM_GPRS+NUM_ACRS+NUM_CRS+1+NUM_FPRS)
DECL|macro|FIRST_ACR
mdefine_line|#define FIRST_ACR     (2+NUM_GPRS)
DECL|macro|LAST_ACR
mdefine_line|#define LAST_ACR      (FIRST_ACR+NUM_ACRS-1)
DECL|macro|FIRST_CR
mdefine_line|#define FIRST_CR      (FIRST_ACR+NUM_ACRS)
DECL|macro|LAST_CR
mdefine_line|#define LAST_CR       (FIRST_CR+NUM_CRS-1)
DECL|macro|PSWM_REGNUM
mdefine_line|#define PSWM_REGNUM    0
DECL|macro|PC_REGNUM
mdefine_line|#define PC_REGNUM      1
DECL|macro|GP0_REGNUM
mdefine_line|#define&t;GP0_REGNUM     2&t;&t;    /* GPR register 0 */ 
DECL|macro|GP_LAST_REGNUM
mdefine_line|#define GP_LAST_REGNUM (GP0_REGNUM+NUM_GPRS-1)
DECL|macro|RETADDR_REGNUM
mdefine_line|#define RETADDR_REGNUM (GP0_REGNUM+14)                   /* Usually return address */
DECL|macro|SP_REGNUM
mdefine_line|#define SP_REGNUM      (GP0_REGNUM+15)&t;    /* Contains address of top of stack */
DECL|macro|FP_REGNUM
mdefine_line|#define FP_REGNUM     SP_REGNUM /* needed in findvar.c still */
DECL|macro|FRAME_REGNUM
mdefine_line|#define FRAME_REGNUM  (GP0_REGNUM+11)
DECL|macro|FPC_REGNUM
mdefine_line|#define FPC_REGNUM    (GP0_REGNUM+NUM_GPRS+NUM_ACRS+NUM_CRS)
DECL|macro|FP0_REGNUM
mdefine_line|#define FP0_REGNUM    (FPC_REGNUM+1) /* FPR (Floating point) register 0 */
DECL|macro|FPLAST_REGNUM
mdefine_line|#define FPLAST_REGNUM (FP0_REGNUM+NUM_FPRS-1)&t;/* Last floating point register */
multiline_comment|/* The top of this structure is as similar as possible to a pt_regs structure to */
multiline_comment|/* simplify code */
r_typedef
r_struct
(brace
id|S390_REGS_COMMON
DECL|member|crs
id|__u32
id|crs
(braket
id|NUM_CRS
)braket
suffix:semicolon
DECL|member|fp_regs
id|s390_fp_regs
id|fp_regs
suffix:semicolon
DECL|typedef|s390_gdb_regs
)brace
id|s390_gdb_regs
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|macro|REGISTER_NAMES
mdefine_line|#define REGISTER_NAMES                                           &bslash;&n;{                                                                &bslash;&n;&quot;pswm&quot;,&quot;pswa&quot;,                                                   &bslash;&n;&quot;gpr0&quot;,&quot;gpr1&quot;,&quot;gpr2&quot;,&quot;gpr3&quot;,&quot;gpr4&quot;,&quot;gpr5&quot;,&quot;gpr6&quot;,&quot;gpr7&quot;,         &bslash;&n;&quot;gpr8&quot;,&quot;gpr9&quot;,&quot;gpr10&quot;,&quot;gpr11&quot;,&quot;gpr12&quot;,&quot;gpr13&quot;,&quot;gpr14&quot;,&quot;gpr15&quot;,   &bslash;&n;&quot;acr0&quot;,&quot;acr1&quot;,&quot;acr2&quot;,&quot;acr3&quot;,&quot;acr4&quot;,&quot;acr5&quot;,&quot;acr6&quot;,&quot;acr7&quot;,         &bslash;&n;&quot;acr8&quot;,&quot;acr9&quot;,&quot;acr10&quot;,&quot;acr11&quot;,&quot;acr12&quot;,&quot;acr13&quot;,&quot;acr14&quot;,&quot;acr15&quot;,   &bslash;&n;&quot;cr0&quot;,&quot;cr1&quot;,&quot;cr2&quot;,&quot;cr3&quot;,&quot;cr4&quot;,&quot;cr5&quot;,&quot;cr6&quot;,&quot;cr7&quot;,                 &bslash;&n;&quot;cr8&quot;,&quot;cr9&quot;,&quot;cr10&quot;,&quot;cr11&quot;,&quot;cr12&quot;,&quot;cr13&quot;,&quot;cr14&quot;,&quot;cr15&quot;,           &bslash;&n;&quot;fpc&quot;,                                                           &bslash;&n;&quot;fpr0&quot;,&quot;fpr1&quot;,&quot;fpr2&quot;,&quot;fpr3&quot;,&quot;fpr4&quot;,&quot;fpr5&quot;,&quot;fpr6&quot;,&quot;fpr7&quot;,         &bslash;&n;&quot;fpr8&quot;,&quot;fpr9&quot;,&quot;fpr10&quot;,&quot;fpr11&quot;,&quot;fpr12&quot;,&quot;fpr13&quot;,&quot;fpr14&quot;,&quot;fpr15&quot;    &bslash;&n;}
multiline_comment|/* Index within `registers&squot; of the first byte of the space for&n;   register N.  */
DECL|macro|FP0_OFFSET
mdefine_line|#define FP0_OFFSET ((PSW_MASK_SIZE+PSW_ADDR_SIZE)+ &bslash;&n;(GPR_SIZE*NUM_GPRS)+(ACR_SIZE+NUM_ACRS)+ &bslash;&n;(CR_SIZE*NUM_CRS)+(FPC_SIZE+FPC_PAD_SIZE))
DECL|macro|REGISTER_BYTES
mdefine_line|#define REGISTER_BYTES    &bslash;&n;((FP0_OFFSET)+(FPR_SIZE*NUM_FPRS))
DECL|macro|REGISTER_BYTE
mdefine_line|#define REGISTER_BYTE(N)  ((N) &lt; FP0_REGNUM ? (N)*4:(FP0_OFFSET+((N)-FP0_REGNUM)*FPR_SIZE))
macro_line|#endif
eof
