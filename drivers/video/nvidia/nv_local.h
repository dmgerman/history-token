multiline_comment|/***************************************************************************&bslash;&n;|*                                                                           *|&n;|*       Copyright 1993-2003 NVIDIA, Corporation.  All rights reserved.      *|&n;|*                                                                           *|&n;|*     NOTICE TO USER:   The source code  is copyrighted under  U.S. and     *|&n;|*     international laws.  Users and possessors of this source code are     *|&n;|*     hereby granted a nonexclusive,  royalty-free copyright license to     *|&n;|*     use this code in individual and commercial software.                  *|&n;|*                                                                           *|&n;|*     Any use of this source code must include,  in the user documenta-     *|&n;|*     tion and  internal comments to the code,  notices to the end user     *|&n;|*     as follows:                                                           *|&n;|*                                                                           *|&n;|*       Copyright 1993-1999 NVIDIA, Corporation.  All rights reserved.      *|&n;|*                                                                           *|&n;|*     NVIDIA, CORPORATION MAKES NO REPRESENTATION ABOUT THE SUITABILITY     *|&n;|*     OF  THIS SOURCE  CODE  FOR ANY PURPOSE.  IT IS  PROVIDED  &quot;AS IS&quot;     *|&n;|*     WITHOUT EXPRESS OR IMPLIED WARRANTY OF ANY KIND.  NVIDIA, CORPOR-     *|&n;|*     ATION DISCLAIMS ALL WARRANTIES  WITH REGARD  TO THIS SOURCE CODE,     *|&n;|*     INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY, NONINFRINGE-     *|&n;|*     MENT,  AND FITNESS  FOR A PARTICULAR PURPOSE.   IN NO EVENT SHALL     *|&n;|*     NVIDIA, CORPORATION  BE LIABLE FOR ANY SPECIAL,  INDIRECT,  INCI-     *|&n;|*     DENTAL, OR CONSEQUENTIAL DAMAGES,  OR ANY DAMAGES  WHATSOEVER RE-     *|&n;|*     SULTING FROM LOSS OF USE,  DATA OR PROFITS,  WHETHER IN AN ACTION     *|&n;|*     OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,  ARISING OUT OF     *|&n;|*     OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOURCE CODE.     *|&n;|*                                                                           *|&n;|*     U.S. Government  End  Users.   This source code  is a &quot;commercial     *|&n;|*     item,&quot;  as that  term is  defined at  48 C.F.R. 2.101 (OCT 1995),     *|&n;|*     consisting  of &quot;commercial  computer  software&quot;  and  &quot;commercial     *|&n;|*     computer  software  documentation,&quot;  as such  terms  are  used in     *|&n;|*     48 C.F.R. 12.212 (SEPT 1995)  and is provided to the U.S. Govern-     *|&n;|*     ment only as  a commercial end item.   Consistent with  48 C.F.R.     *|&n;|*     12.212 and  48 C.F.R. 227.7202-1 through  227.7202-4 (JUNE 1995),     *|&n;|*     all U.S. Government End Users  acquire the source code  with only     *|&n;|*     those rights set forth herein.                                        *|&n;|*                                                                           *|&n; &bslash;***************************************************************************/
multiline_comment|/*&n; * GPL Licensing Note - According to Mark Vojkovich, author of the Xorg/&n; * XFree86 &squot;nv&squot; driver, this source code is provided under MIT-style licensing&n; * where the source code is provided &quot;as is&quot; without warranty of any kind.&n; * The only usage restriction is for the copyright notices to be retained&n; * whenever code is used.&n; *&n; * Antonino Daplas &lt;adaplas@pol.net&gt; 2005-03-11&n; */
macro_line|#ifndef __NV_LOCAL_H__
DECL|macro|__NV_LOCAL_H__
mdefine_line|#define __NV_LOCAL_H__
multiline_comment|/*&n; * This file includes any environment or machine specific values to access the&n; * HW.  Put all affected includes, typdefs, etc. here so the riva_hw.* files&n; * can stay generic in nature.&n; */
multiline_comment|/*&n; * HW access macros.  These assume memory-mapped I/O, and not normal I/O space.&n; */
DECL|macro|NV_WR08
mdefine_line|#define NV_WR08(p,i,d)  (__raw_writeb((d), (void __iomem *)(p) + (i)))
DECL|macro|NV_RD08
mdefine_line|#define NV_RD08(p,i)    (__raw_readb((void __iomem *)(p) + (i)))
DECL|macro|NV_WR16
mdefine_line|#define NV_WR16(p,i,d)  (__raw_writew((d), (void __iomem *)(p) + (i)))
DECL|macro|NV_RD16
mdefine_line|#define NV_RD16(p,i)    (__raw_readw((void __iomem *)(p) + (i)))
DECL|macro|NV_WR32
mdefine_line|#define NV_WR32(p,i,d)  (__raw_writel((d), (void __iomem *)(p) + (i)))
DECL|macro|NV_RD32
mdefine_line|#define NV_RD32(p,i)    (__raw_readl((void __iomem *)(p) + (i)))
multiline_comment|/* VGA I/O is now always done through MMIO */
DECL|macro|VGA_WR08
mdefine_line|#define VGA_WR08(p,i,d) (writeb((d), (void __iomem *)(p) + (i)))
DECL|macro|VGA_RD08
mdefine_line|#define VGA_RD08(p,i)   (readb((void __iomem *)(p) + (i)))
DECL|macro|NVDmaNext
mdefine_line|#define NVDmaNext(par, data) &bslash;&n;     NV_WR32(&amp;(par)-&gt;dmaBase[(par)-&gt;dmaCurrent++], 0, (data))
DECL|macro|NVDmaStart
mdefine_line|#define NVDmaStart(par, tag, size) {          &bslash;&n;     if((par)-&gt;dmaFree &lt;= (size))             &bslash;&n;        NVDmaWait(par, size);                 &bslash;&n;     NVDmaNext(par, ((size) &lt;&lt; 18) | (tag));  &bslash;&n;     (par)-&gt;dmaFree -= ((size) + 1);          &bslash;&n;}
macro_line|#if defined(__i386__)
DECL|macro|_NV_FENCE
mdefine_line|#define _NV_FENCE() outb(0, 0x3D0);
macro_line|#else
DECL|macro|_NV_FENCE
mdefine_line|#define _NV_FENCE() mb();
macro_line|#endif
DECL|macro|WRITE_PUT
mdefine_line|#define WRITE_PUT(par, data) {                   &bslash;&n;  volatile u8 scratch;                           &bslash;&n;  _NV_FENCE()                                    &bslash;&n;  scratch = NV_RD08((par)-&gt;FbStart, 0);          &bslash;&n;  NV_WR32(&amp;(par)-&gt;FIFO[0x0010], 0, (data) &lt;&lt; 2); &bslash;&n;  mb();                                          &bslash;&n;}
DECL|macro|READ_GET
mdefine_line|#define READ_GET(par) (NV_RD32(&amp;(par)-&gt;FIFO[0x0011], 0) &gt;&gt; 2)
DECL|macro|reverse_order
mdefine_line|#define reverse_order(l)        &bslash;&n;do {                            &bslash;&n;&t;u8 *a = (u8 *)(l);      &bslash;&n;&t;*a = byte_rev[*a], a++; &bslash;&n;&t;*a = byte_rev[*a], a++; &bslash;&n;&t;*a = byte_rev[*a], a++; &bslash;&n;&t;*a = byte_rev[*a];      &bslash;&n;} while(0)
macro_line|#endif&t;&t;&t;&t;/* __NV_LOCAL_H__ */
eof
