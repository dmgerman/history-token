multiline_comment|/*&n; * linux/include/asm-arm/vfp.h&n; *&n; * VFP register definitions.&n; * First, the standard VFP set.&n; */
DECL|macro|FPSID
mdefine_line|#define FPSID&t;&t;&t;cr0
DECL|macro|FPSCR
mdefine_line|#define FPSCR&t;&t;&t;cr1
DECL|macro|FPEXC
mdefine_line|#define FPEXC&t;&t;&t;cr8
multiline_comment|/* FPSID bits */
DECL|macro|FPSID_IMPLEMENTER_BIT
mdefine_line|#define FPSID_IMPLEMENTER_BIT&t;(24)
DECL|macro|FPSID_IMPLEMENTER_MASK
mdefine_line|#define FPSID_IMPLEMENTER_MASK&t;(0xff &lt;&lt; FPSID_IMPLEMENTER_BIT)
DECL|macro|FPSID_SOFTWARE
mdefine_line|#define FPSID_SOFTWARE&t;&t;(1&lt;&lt;23)
DECL|macro|FPSID_FORMAT_BIT
mdefine_line|#define FPSID_FORMAT_BIT&t;(21)
DECL|macro|FPSID_FORMAT_MASK
mdefine_line|#define FPSID_FORMAT_MASK&t;(0x3  &lt;&lt; FPSID_FORMAT_BIT)
DECL|macro|FPSID_NODOUBLE
mdefine_line|#define FPSID_NODOUBLE&t;&t;(1&lt;&lt;20)
DECL|macro|FPSID_ARCH_BIT
mdefine_line|#define FPSID_ARCH_BIT&t;&t;(16)
DECL|macro|FPSID_ARCH_MASK
mdefine_line|#define FPSID_ARCH_MASK&t;&t;(0xF  &lt;&lt; FPSID_ARCH_BIT)
DECL|macro|FPSID_PART_BIT
mdefine_line|#define FPSID_PART_BIT&t;&t;(8)
DECL|macro|FPSID_PART_MASK
mdefine_line|#define FPSID_PART_MASK&t;&t;(0xFF &lt;&lt; FPSID_PART_BIT)
DECL|macro|FPSID_VARIANT_BIT
mdefine_line|#define FPSID_VARIANT_BIT&t;(4)
DECL|macro|FPSID_VARIANT_MASK
mdefine_line|#define FPSID_VARIANT_MASK&t;(0xF  &lt;&lt; FPSID_VARIANT_BIT)
DECL|macro|FPSID_REV_BIT
mdefine_line|#define FPSID_REV_BIT&t;&t;(0)
DECL|macro|FPSID_REV_MASK
mdefine_line|#define FPSID_REV_MASK&t;&t;(0xF  &lt;&lt; FPSID_REV_BIT)
multiline_comment|/* FPEXC bits */
DECL|macro|FPEXC_EXCEPTION
mdefine_line|#define FPEXC_EXCEPTION&t;&t;(1&lt;&lt;31)
DECL|macro|FPEXC_ENABLE
mdefine_line|#define FPEXC_ENABLE&t;&t;(1&lt;&lt;30)
multiline_comment|/* FPSCR bits */
DECL|macro|FPSCR_DEFAULT_NAN
mdefine_line|#define FPSCR_DEFAULT_NAN&t;(1&lt;&lt;25)
DECL|macro|FPSCR_FLUSHTOZERO
mdefine_line|#define FPSCR_FLUSHTOZERO&t;(1&lt;&lt;24)
DECL|macro|FPSCR_ROUND_NEAREST
mdefine_line|#define FPSCR_ROUND_NEAREST&t;(0&lt;&lt;22)
DECL|macro|FPSCR_ROUND_PLUSINF
mdefine_line|#define FPSCR_ROUND_PLUSINF&t;(1&lt;&lt;22)
DECL|macro|FPSCR_ROUND_MINUSINF
mdefine_line|#define FPSCR_ROUND_MINUSINF&t;(2&lt;&lt;22)
DECL|macro|FPSCR_ROUND_TOZERO
mdefine_line|#define FPSCR_ROUND_TOZERO&t;(3&lt;&lt;22)
DECL|macro|FPSCR_RMODE_BIT
mdefine_line|#define FPSCR_RMODE_BIT&t;&t;(22)
DECL|macro|FPSCR_RMODE_MASK
mdefine_line|#define FPSCR_RMODE_MASK&t;(3 &lt;&lt; FPSCR_RMODE_BIT)
DECL|macro|FPSCR_STRIDE_BIT
mdefine_line|#define FPSCR_STRIDE_BIT&t;(20)
DECL|macro|FPSCR_STRIDE_MASK
mdefine_line|#define FPSCR_STRIDE_MASK&t;(3 &lt;&lt; FPSCR_STRIDE_BIT)
DECL|macro|FPSCR_LENGTH_BIT
mdefine_line|#define FPSCR_LENGTH_BIT&t;(16)
DECL|macro|FPSCR_LENGTH_MASK
mdefine_line|#define FPSCR_LENGTH_MASK&t;(7 &lt;&lt; FPSCR_LENGTH_BIT)
DECL|macro|FPSCR_IOE
mdefine_line|#define FPSCR_IOE&t;&t;(1&lt;&lt;8)
DECL|macro|FPSCR_DZE
mdefine_line|#define FPSCR_DZE&t;&t;(1&lt;&lt;9)
DECL|macro|FPSCR_OFE
mdefine_line|#define FPSCR_OFE&t;&t;(1&lt;&lt;10)
DECL|macro|FPSCR_UFE
mdefine_line|#define FPSCR_UFE&t;&t;(1&lt;&lt;11)
DECL|macro|FPSCR_IXE
mdefine_line|#define FPSCR_IXE&t;&t;(1&lt;&lt;12)
DECL|macro|FPSCR_IDE
mdefine_line|#define FPSCR_IDE&t;&t;(1&lt;&lt;15)
DECL|macro|FPSCR_IOC
mdefine_line|#define FPSCR_IOC&t;&t;(1&lt;&lt;0)
DECL|macro|FPSCR_DZC
mdefine_line|#define FPSCR_DZC&t;&t;(1&lt;&lt;1)
DECL|macro|FPSCR_OFC
mdefine_line|#define FPSCR_OFC&t;&t;(1&lt;&lt;2)
DECL|macro|FPSCR_UFC
mdefine_line|#define FPSCR_UFC&t;&t;(1&lt;&lt;3)
DECL|macro|FPSCR_IXC
mdefine_line|#define FPSCR_IXC&t;&t;(1&lt;&lt;4)
DECL|macro|FPSCR_IDC
mdefine_line|#define FPSCR_IDC&t;&t;(1&lt;&lt;7)
multiline_comment|/*&n; * VFP9-S specific.&n; */
DECL|macro|FPINST
mdefine_line|#define FPINST&t;&t;&t;cr9
DECL|macro|FPINST2
mdefine_line|#define FPINST2&t;&t;&t;cr10
multiline_comment|/* FPEXC bits */
DECL|macro|FPEXC_FPV2
mdefine_line|#define FPEXC_FPV2&t;&t;(1&lt;&lt;28)
DECL|macro|FPEXC_LENGTH_BIT
mdefine_line|#define FPEXC_LENGTH_BIT&t;(8)
DECL|macro|FPEXC_LENGTH_MASK
mdefine_line|#define FPEXC_LENGTH_MASK&t;(7 &lt;&lt; FPEXC_LENGTH_BIT)
DECL|macro|FPEXC_INV
mdefine_line|#define FPEXC_INV&t;&t;(1 &lt;&lt; 7)
DECL|macro|FPEXC_UFC
mdefine_line|#define FPEXC_UFC&t;&t;(1 &lt;&lt; 3)
DECL|macro|FPEXC_OFC
mdefine_line|#define FPEXC_OFC&t;&t;(1 &lt;&lt; 2)
DECL|macro|FPEXC_IOC
mdefine_line|#define FPEXC_IOC&t;&t;(1 &lt;&lt; 0)
multiline_comment|/* Bit patterns for decoding the packaged operation descriptors */
DECL|macro|VFPOPDESC_LENGTH_BIT
mdefine_line|#define VFPOPDESC_LENGTH_BIT&t;(9)
DECL|macro|VFPOPDESC_LENGTH_MASK
mdefine_line|#define VFPOPDESC_LENGTH_MASK&t;(0x07 &lt;&lt; VFPOPDESC_LENGTH_BIT)
DECL|macro|VFPOPDESC_UNUSED_BIT
mdefine_line|#define VFPOPDESC_UNUSED_BIT&t;(24)
DECL|macro|VFPOPDESC_UNUSED_MASK
mdefine_line|#define VFPOPDESC_UNUSED_MASK&t;(0xFF &lt;&lt; VFPOPDESC_UNUSED_BIT)
DECL|macro|VFPOPDESC_OPDESC_MASK
mdefine_line|#define VFPOPDESC_OPDESC_MASK&t;(~(VFPOPDESC_LENGTH_MASK | VFPOPDESC_UNUSED_MASK))
eof
