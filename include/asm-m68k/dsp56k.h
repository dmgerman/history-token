multiline_comment|/*&n; * linux/include/asm-m68k/dsp56k.h - defines and declarations for&n; *                                   DSP56k device driver&n; *&n; * Copyright (C) 1996,1997 Fredrik Noring, lars brinkhoff &amp; Tomas Berndtsson&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file COPYING in the main directory of this archive&n; * for more details.&n; */
multiline_comment|/* Used for uploading DSP binary code */
DECL|struct|dsp56k_upload
r_struct
id|dsp56k_upload
(brace
DECL|member|len
r_int
id|len
suffix:semicolon
DECL|member|bin
r_char
op_star
id|bin
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* For the DSP host flags */
DECL|struct|dsp56k_host_flags
r_struct
id|dsp56k_host_flags
(brace
DECL|member|dir
r_int
id|dir
suffix:semicolon
multiline_comment|/* Bit field. 1 = write output bit, 0 = do nothing.&n;&t;&t;      * 0x0000 means reading only, 0x0011 means&n;&t;&t;      * writing the bits stored in `out&squot; on HF0 and HF1.&n;&t;&t;      * Note that HF2 and HF3 can only be read.&n;&t;&t;      */
DECL|member|out
r_int
id|out
suffix:semicolon
multiline_comment|/* Bit field like above. */
DECL|member|status
r_int
id|status
suffix:semicolon
multiline_comment|/* Host register&squot;s current state is returned */
)brace
suffix:semicolon
multiline_comment|/* ioctl command codes */
DECL|macro|DSP56K_UPLOAD
mdefine_line|#define DSP56K_UPLOAD&t;        1    /* Upload DSP binary program       */
DECL|macro|DSP56K_SET_TX_WSIZE
mdefine_line|#define DSP56K_SET_TX_WSIZE&t;2    /* Host transmit word size (1-4)   */
DECL|macro|DSP56K_SET_RX_WSIZE
mdefine_line|#define DSP56K_SET_RX_WSIZE&t;3    /* Host receive word size (1-4)    */
DECL|macro|DSP56K_HOST_FLAGS
mdefine_line|#define DSP56K_HOST_FLAGS&t;4    /* Host flag registers             */
DECL|macro|DSP56K_HOST_CMD
mdefine_line|#define DSP56K_HOST_CMD         5    /* Trig Host Command (0-31)        */
eof
