multiline_comment|/*&n; *  (c) 2003, 2004 Advanced Micro Devices, Inc.&n; *  Your use of this code is subject to the terms and conditions of the&n; *  GNU general public license version 2. See &quot;COPYING&quot; or&n; *  http://www.gnu.org/licenses/gpl.html&n; */
DECL|struct|powernow_k8_data
r_struct
id|powernow_k8_data
(brace
DECL|member|cpu
r_int
r_int
id|cpu
suffix:semicolon
DECL|member|numps
id|u32
id|numps
suffix:semicolon
multiline_comment|/* number of p-states */
DECL|member|batps
id|u32
id|batps
suffix:semicolon
multiline_comment|/* number of p-states supported on battery */
multiline_comment|/* these values are constant when the PSB is used to determine&n;&t; * vid/fid pairings, but are modified during the -&gt;target() call&n;&t; * when ACPI is used */
DECL|member|rvo
id|u32
id|rvo
suffix:semicolon
multiline_comment|/* ramp voltage offset */
DECL|member|irt
id|u32
id|irt
suffix:semicolon
multiline_comment|/* isochronous relief time */
DECL|member|vidmvs
id|u32
id|vidmvs
suffix:semicolon
multiline_comment|/* usable value calculated from mvs */
DECL|member|vstable
id|u32
id|vstable
suffix:semicolon
multiline_comment|/* voltage stabilization time, units 20 us */
DECL|member|plllock
id|u32
id|plllock
suffix:semicolon
multiline_comment|/* pll lock time, units 1 us */
multiline_comment|/* keep track of the current fid / vid */
DECL|member|currvid
DECL|member|currfid
id|u32
id|currvid
comma
id|currfid
suffix:semicolon
multiline_comment|/* the powernow_table includes all frequency and vid/fid pairings:&n;&t; * fid are the lower 8 bits of the index, vid are the upper 8 bits.&n;&t; * frequency is in kHz */
DECL|member|powernow_table
r_struct
id|cpufreq_frequency_table
op_star
id|powernow_table
suffix:semicolon
macro_line|#ifdef CONFIG_X86_POWERNOW_K8_ACPI
multiline_comment|/* the acpi table needs to be kept. it&squot;s only available if ACPI was&n;&t; * used to determine valid frequency/vid/fid states */
DECL|member|acpi_data
r_struct
id|acpi_processor_performance
id|acpi_data
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
multiline_comment|/* processor&squot;s cpuid instruction support */
DECL|macro|CPUID_PROCESSOR_SIGNATURE
mdefine_line|#define CPUID_PROCESSOR_SIGNATURE&t;1&t;/* function 1 */
DECL|macro|CPUID_XFAM
mdefine_line|#define CPUID_XFAM&t;&t;&t;0x0ff00000&t;/* extended family */
DECL|macro|CPUID_XFAM_K8
mdefine_line|#define CPUID_XFAM_K8&t;&t;&t;0
DECL|macro|CPUID_XMOD
mdefine_line|#define CPUID_XMOD&t;&t;&t;0x000f0000&t;/* extended model */
DECL|macro|CPUID_XMOD_REV_E
mdefine_line|#define CPUID_XMOD_REV_E&t;&t;0x00020000
DECL|macro|CPUID_USE_XFAM_XMOD
mdefine_line|#define CPUID_USE_XFAM_XMOD&t;&t;0x00000f00
DECL|macro|CPUID_GET_MAX_CAPABILITIES
mdefine_line|#define CPUID_GET_MAX_CAPABILITIES&t;0x80000000
DECL|macro|CPUID_FREQ_VOLT_CAPABILITIES
mdefine_line|#define CPUID_FREQ_VOLT_CAPABILITIES&t;0x80000007
DECL|macro|P_STATE_TRANSITION_CAPABLE
mdefine_line|#define P_STATE_TRANSITION_CAPABLE&t;6
multiline_comment|/* Model Specific Registers for p-state transitions. MSRs are 64-bit. For     */
multiline_comment|/* writes (wrmsr - opcode 0f 30), the register number is placed in ecx, and   */
multiline_comment|/* the value to write is placed in edx:eax. For reads (rdmsr - opcode 0f 32), */
multiline_comment|/* the register number is placed in ecx, and the data is returned in edx:eax. */
DECL|macro|MSR_FIDVID_CTL
mdefine_line|#define MSR_FIDVID_CTL      0xc0010041
DECL|macro|MSR_FIDVID_STATUS
mdefine_line|#define MSR_FIDVID_STATUS   0xc0010042
multiline_comment|/* Field definitions within the FID VID Low Control MSR : */
DECL|macro|MSR_C_LO_INIT_FID_VID
mdefine_line|#define MSR_C_LO_INIT_FID_VID     0x00010000
DECL|macro|MSR_C_LO_NEW_VID
mdefine_line|#define MSR_C_LO_NEW_VID          0x00001f00
DECL|macro|MSR_C_LO_NEW_FID
mdefine_line|#define MSR_C_LO_NEW_FID          0x0000002f
DECL|macro|MSR_C_LO_VID_SHIFT
mdefine_line|#define MSR_C_LO_VID_SHIFT        8
multiline_comment|/* Field definitions within the FID VID High Control MSR : */
DECL|macro|MSR_C_HI_STP_GNT_TO
mdefine_line|#define MSR_C_HI_STP_GNT_TO       0x000fffff
multiline_comment|/* Field definitions within the FID VID Low Status MSR : */
DECL|macro|MSR_S_LO_CHANGE_PENDING
mdefine_line|#define MSR_S_LO_CHANGE_PENDING   0x80000000&t;/* cleared when completed */
DECL|macro|MSR_S_LO_MAX_RAMP_VID
mdefine_line|#define MSR_S_LO_MAX_RAMP_VID     0x1f000000
DECL|macro|MSR_S_LO_MAX_FID
mdefine_line|#define MSR_S_LO_MAX_FID          0x003f0000
DECL|macro|MSR_S_LO_START_FID
mdefine_line|#define MSR_S_LO_START_FID        0x00003f00
DECL|macro|MSR_S_LO_CURRENT_FID
mdefine_line|#define MSR_S_LO_CURRENT_FID      0x0000003f
multiline_comment|/* Field definitions within the FID VID High Status MSR : */
DECL|macro|MSR_S_HI_MAX_WORKING_VID
mdefine_line|#define MSR_S_HI_MAX_WORKING_VID  0x001f0000
DECL|macro|MSR_S_HI_START_VID
mdefine_line|#define MSR_S_HI_START_VID        0x00001f00
DECL|macro|MSR_S_HI_CURRENT_VID
mdefine_line|#define MSR_S_HI_CURRENT_VID      0x0000001f
DECL|macro|MSR_C_HI_STP_GNT_BENIGN
mdefine_line|#define MSR_C_HI_STP_GNT_BENIGN   0x00000001
multiline_comment|/*&n; * There are restrictions frequencies have to follow:&n; * - only 1 entry in the low fid table ( &lt;=1.4GHz )&n; * - lowest entry in the high fid table must be &gt;= 2 * the entry in the&n; *   low fid table&n; * - lowest entry in the high fid table must be a &lt;= 200MHz + 2 * the entry&n; *   in the low fid table&n; * - the parts can only step at 200 MHz intervals, so 1.9 GHz is never valid&n; * - lowest frequency must be &gt;= interprocessor hypertransport link speed&n; *   (only applies to MP systems obviously)&n; */
multiline_comment|/* fids (frequency identifiers) are arranged in 2 tables - lo and hi */
DECL|macro|LO_FID_TABLE_TOP
mdefine_line|#define LO_FID_TABLE_TOP     6&t;/* fid values marking the boundary    */
DECL|macro|HI_FID_TABLE_BOTTOM
mdefine_line|#define HI_FID_TABLE_BOTTOM  8&t;/* between the low and high tables    */
DECL|macro|LO_VCOFREQ_TABLE_TOP
mdefine_line|#define LO_VCOFREQ_TABLE_TOP    1400&t;/* corresponding vco frequency values */
DECL|macro|HI_VCOFREQ_TABLE_BOTTOM
mdefine_line|#define HI_VCOFREQ_TABLE_BOTTOM 1600
DECL|macro|MIN_FREQ_RESOLUTION
mdefine_line|#define MIN_FREQ_RESOLUTION  200 /* fids jump by 2 matching freq jumps by 200 */
DECL|macro|MAX_FID
mdefine_line|#define MAX_FID 0x2a&t;/* Spec only gives FID values as far as 5 GHz */
DECL|macro|LEAST_VID
mdefine_line|#define LEAST_VID 0x1e&t;/* Lowest (numerically highest) useful vid value */
DECL|macro|MIN_FREQ
mdefine_line|#define MIN_FREQ 800&t;/* Min and max freqs, per spec */
DECL|macro|MAX_FREQ
mdefine_line|#define MAX_FREQ 5000
DECL|macro|INVALID_FID_MASK
mdefine_line|#define INVALID_FID_MASK 0xffffffc1  /* not a valid fid if these bits are set */
DECL|macro|INVALID_VID_MASK
mdefine_line|#define INVALID_VID_MASK 0xffffffe0  /* not a valid vid if these bits are set */
DECL|macro|STOP_GRANT_5NS
mdefine_line|#define STOP_GRANT_5NS 1 /* min poss memory access latency for voltage change */
DECL|macro|PLL_LOCK_CONVERSION
mdefine_line|#define PLL_LOCK_CONVERSION (1000/5) /* ms to ns, then divide by clock period */
DECL|macro|MAXIMUM_VID_STEPS
mdefine_line|#define MAXIMUM_VID_STEPS 1  /* Current cpus only allow a single step of 25mV */
DECL|macro|VST_UNITS_20US
mdefine_line|#define VST_UNITS_20US 20   /* Voltage Stabalization Time is in units of 20us */
multiline_comment|/*&n; * Most values of interest are enocoded in a single field of the _PSS&n; * entries: the &quot;control&quot; value.&n; */
DECL|macro|IRT_SHIFT
mdefine_line|#define IRT_SHIFT      30
DECL|macro|RVO_SHIFT
mdefine_line|#define RVO_SHIFT      28
DECL|macro|PLL_L_SHIFT
mdefine_line|#define PLL_L_SHIFT    20
DECL|macro|MVS_SHIFT
mdefine_line|#define MVS_SHIFT      18
DECL|macro|VST_SHIFT
mdefine_line|#define VST_SHIFT      11
DECL|macro|VID_SHIFT
mdefine_line|#define VID_SHIFT       6
DECL|macro|IRT_MASK
mdefine_line|#define IRT_MASK        3
DECL|macro|RVO_MASK
mdefine_line|#define RVO_MASK        3
DECL|macro|PLL_L_MASK
mdefine_line|#define PLL_L_MASK   0x7f
DECL|macro|MVS_MASK
mdefine_line|#define MVS_MASK        3
DECL|macro|VST_MASK
mdefine_line|#define VST_MASK     0x7f
DECL|macro|VID_MASK
mdefine_line|#define VID_MASK     0x1f
DECL|macro|FID_MASK
mdefine_line|#define FID_MASK     0x3f
multiline_comment|/*&n; * Version 1.4 of the PSB table. This table is constructed by BIOS and is&n; * to tell the OS&squot;s power management driver which VIDs and FIDs are&n; * supported by this particular processor.&n; * If the data in the PSB / PST is wrong, then this driver will program the&n; * wrong values into hardware, which is very likely to lead to a crash.&n; */
DECL|macro|PSB_ID_STRING
mdefine_line|#define PSB_ID_STRING      &quot;AMDK7PNOW!&quot;
DECL|macro|PSB_ID_STRING_LEN
mdefine_line|#define PSB_ID_STRING_LEN  10
DECL|macro|PSB_VERSION_1_4
mdefine_line|#define PSB_VERSION_1_4  0x14
DECL|struct|psb_s
r_struct
id|psb_s
(brace
DECL|member|signature
id|u8
id|signature
(braket
l_int|10
)braket
suffix:semicolon
DECL|member|tableversion
id|u8
id|tableversion
suffix:semicolon
DECL|member|flags1
id|u8
id|flags1
suffix:semicolon
DECL|member|vstable
id|u16
id|vstable
suffix:semicolon
DECL|member|flags2
id|u8
id|flags2
suffix:semicolon
DECL|member|num_tables
id|u8
id|num_tables
suffix:semicolon
DECL|member|cpuid
id|u32
id|cpuid
suffix:semicolon
DECL|member|plllocktime
id|u8
id|plllocktime
suffix:semicolon
DECL|member|maxfid
id|u8
id|maxfid
suffix:semicolon
DECL|member|maxvid
id|u8
id|maxvid
suffix:semicolon
DECL|member|numps
id|u8
id|numps
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Pairs of fid/vid values are appended to the version 1.4 PSB table. */
DECL|struct|pst_s
r_struct
id|pst_s
(brace
DECL|member|fid
id|u8
id|fid
suffix:semicolon
DECL|member|vid
id|u8
id|vid
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|dprintk
mdefine_line|#define dprintk(msg...) cpufreq_debug_printk(CPUFREQ_DEBUG_DRIVER, &quot;powernow-k8&quot;, msg)
r_static
r_int
id|core_voltage_pre_transition
c_func
(paren
r_struct
id|powernow_k8_data
op_star
id|data
comma
id|u32
id|reqvid
)paren
suffix:semicolon
r_static
r_int
id|core_voltage_post_transition
c_func
(paren
r_struct
id|powernow_k8_data
op_star
id|data
comma
id|u32
id|reqvid
)paren
suffix:semicolon
r_static
r_int
id|core_frequency_transition
c_func
(paren
r_struct
id|powernow_k8_data
op_star
id|data
comma
id|u32
id|reqfid
)paren
suffix:semicolon
r_static
r_void
id|powernow_k8_acpi_pst_values
c_func
(paren
r_struct
id|powernow_k8_data
op_star
id|data
comma
r_int
r_int
id|index
)paren
suffix:semicolon
eof
