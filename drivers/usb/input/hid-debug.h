multiline_comment|/*&n; * $Id: hid-debug.h,v 1.8 2001/09/25 09:37:57 vojtech Exp $&n; *&n; *  (c) 1999 Andreas Gal&t;&t;&lt;gal@cs.uni-magdeburg.de&gt;&n; *  (c) 2000-2001 Vojtech Pavlik&t;&lt;vojtech@ucw.cz&gt;&n; *&n; *  Some debug stuff for the HID parser.&n; */
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; *&n; * Should you need to contact me, the author, you can do so either by&n; * e-mail - mail your message to &lt;vojtech@ucw.cz&gt;, or by paper mail:&n; * Vojtech Pavlik, Simunkova 1594, Prague 8, 182 00 Czech Republic&n; */
DECL|struct|hid_usage_entry
r_struct
id|hid_usage_entry
(brace
DECL|member|page
r_int
id|page
suffix:semicolon
DECL|member|usage
r_int
id|usage
suffix:semicolon
DECL|member|description
r_char
op_star
id|description
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|hid_usage_table
r_static
r_struct
id|hid_usage_entry
id|hid_usage_table
(braket
)braket
op_assign
(brace
(brace
l_int|0
comma
l_int|0
comma
l_string|&quot;Undefined&quot;
)brace
comma
(brace
l_int|1
comma
l_int|0
comma
l_string|&quot;GenericDesktop&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x01
comma
l_string|&quot;Pointer&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x02
comma
l_string|&quot;Mouse&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x04
comma
l_string|&quot;Joystick&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x05
comma
l_string|&quot;GamePad&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x06
comma
l_string|&quot;Keyboard&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x07
comma
l_string|&quot;Keypad&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x08
comma
l_string|&quot;MultiAxis&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x30
comma
l_string|&quot;X&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x31
comma
l_string|&quot;Y&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x32
comma
l_string|&quot;Z&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x33
comma
l_string|&quot;Rx&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x34
comma
l_string|&quot;Ry&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x35
comma
l_string|&quot;Rz&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x36
comma
l_string|&quot;Slider&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x37
comma
l_string|&quot;Dial&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x38
comma
l_string|&quot;Wheel&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x39
comma
l_string|&quot;HatSwitch&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x3a
comma
l_string|&quot;CountedBuffer&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x3b
comma
l_string|&quot;ByteCount&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x3c
comma
l_string|&quot;MotionWakeup&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x3d
comma
l_string|&quot;Start&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x3e
comma
l_string|&quot;Select&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x40
comma
l_string|&quot;Vx&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x41
comma
l_string|&quot;Vy&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x42
comma
l_string|&quot;Vz&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x43
comma
l_string|&quot;Vbrx&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x44
comma
l_string|&quot;Vbry&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x45
comma
l_string|&quot;Vbrz&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x46
comma
l_string|&quot;Vno&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x80
comma
l_string|&quot;SystemControl&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x81
comma
l_string|&quot;SystemPowerDown&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x82
comma
l_string|&quot;SystemSleep&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x83
comma
l_string|&quot;SystemWakeUp&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x84
comma
l_string|&quot;SystemContextMenu&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x85
comma
l_string|&quot;SystemMainMenu&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x86
comma
l_string|&quot;SystemAppMenu&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x87
comma
l_string|&quot;SystemMenuHelp&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x88
comma
l_string|&quot;SystemMenuExit&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x89
comma
l_string|&quot;SystemMenuSelect&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x8a
comma
l_string|&quot;SystemMenuRight&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x8b
comma
l_string|&quot;SystemMenuLeft&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x8c
comma
l_string|&quot;SystemMenuUp&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x8d
comma
l_string|&quot;SystemMenuDown&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x90
comma
l_string|&quot;D-padUp&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x91
comma
l_string|&quot;D-padDown&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x92
comma
l_string|&quot;D-padRight&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x93
comma
l_string|&quot;D-padLeft&quot;
)brace
comma
(brace
l_int|7
comma
l_int|0
comma
l_string|&quot;Keyboard&quot;
)brace
comma
(brace
l_int|8
comma
l_int|0
comma
l_string|&quot;LED&quot;
)brace
comma
(brace
l_int|9
comma
l_int|0
comma
l_string|&quot;Button&quot;
)brace
comma
(brace
l_int|10
comma
l_int|0
comma
l_string|&quot;Ordinal&quot;
)brace
comma
(brace
l_int|12
comma
l_int|0
comma
l_string|&quot;Hotkey&quot;
)brace
comma
(brace
l_int|13
comma
l_int|0
comma
l_string|&quot;Digitizers&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x01
comma
l_string|&quot;Digitizer&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x02
comma
l_string|&quot;Pen&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x03
comma
l_string|&quot;LightPen&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x04
comma
l_string|&quot;TouchScreen&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x05
comma
l_string|&quot;TouchPad&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x20
comma
l_string|&quot;Stylus&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x21
comma
l_string|&quot;Puck&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x22
comma
l_string|&quot;Finger&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x30
comma
l_string|&quot;TipPressure&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x31
comma
l_string|&quot;BarrelPressure&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x32
comma
l_string|&quot;InRange&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x33
comma
l_string|&quot;Touch&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x34
comma
l_string|&quot;UnTouch&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x35
comma
l_string|&quot;Tap&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x39
comma
l_string|&quot;TabletFunctionKey&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x3a
comma
l_string|&quot;ProgramChangeKey&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x3c
comma
l_string|&quot;Invert&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x42
comma
l_string|&quot;TipSwitch&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x43
comma
l_string|&quot;SecondaryTipSwitch&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x44
comma
l_string|&quot;BarrelSwitch&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x45
comma
l_string|&quot;Eraser&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x46
comma
l_string|&quot;TabletPick&quot;
)brace
comma
(brace
l_int|15
comma
l_int|0
comma
l_string|&quot;PhysicalInterfaceDevice&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x00
comma
l_string|&quot;Undefined&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x01
comma
l_string|&quot;Physical_Interface_Device&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x20
comma
l_string|&quot;Normal&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x21
comma
l_string|&quot;Set_Effect_Report&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x22
comma
l_string|&quot;Effect_Block_Index&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x23
comma
l_string|&quot;Parameter_Block_Offset&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x24
comma
l_string|&quot;ROM_Flag&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x25
comma
l_string|&quot;Effect_Type&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x26
comma
l_string|&quot;ET_Constant_Force&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x27
comma
l_string|&quot;ET_Ramp&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x28
comma
l_string|&quot;ET_Custom_Force_Data&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x30
comma
l_string|&quot;ET_Square&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x31
comma
l_string|&quot;ET_Sine&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x32
comma
l_string|&quot;ET_Triangle&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x33
comma
l_string|&quot;ET_Sawtooth_Up&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x34
comma
l_string|&quot;ET_Sawtooth_Down&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x40
comma
l_string|&quot;ET_Spring&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x41
comma
l_string|&quot;ET_Damper&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x42
comma
l_string|&quot;ET_Inertia&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x43
comma
l_string|&quot;ET_Friction&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x50
comma
l_string|&quot;Duration&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x51
comma
l_string|&quot;Sample_Period&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x52
comma
l_string|&quot;Gain&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x53
comma
l_string|&quot;Trigger_Button&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x54
comma
l_string|&quot;Trigger_Repeat_Interval&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x55
comma
l_string|&quot;Axes_Enable&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x56
comma
l_string|&quot;Direction_Enable&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x57
comma
l_string|&quot;Direction&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x58
comma
l_string|&quot;Type_Specific_Block_Offset&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x59
comma
l_string|&quot;Block_Type&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x5A
comma
l_string|&quot;Set_Envelope_Report&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x5B
comma
l_string|&quot;Attack_Level&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x5C
comma
l_string|&quot;Attack_Time&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x5D
comma
l_string|&quot;Fade_Level&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x5E
comma
l_string|&quot;Fade_Time&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x5F
comma
l_string|&quot;Set_Condition_Report&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x60
comma
l_string|&quot;CP_Offset&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x61
comma
l_string|&quot;Positive_Coefficient&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x62
comma
l_string|&quot;Negative_Coefficient&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x63
comma
l_string|&quot;Positive_Saturation&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x64
comma
l_string|&quot;Negative_Saturation&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x65
comma
l_string|&quot;Dead_Band&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x66
comma
l_string|&quot;Download_Force_Sample&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x67
comma
l_string|&quot;Isoch_Custom_Force_Enable&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x68
comma
l_string|&quot;Custom_Force_Data_Report&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x69
comma
l_string|&quot;Custom_Force_Data&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x6A
comma
l_string|&quot;Custom_Force_Vendor_Defined_Data&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x6B
comma
l_string|&quot;Set_Custom_Force_Report&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x6C
comma
l_string|&quot;Custom_Force_Data_Offset&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x6D
comma
l_string|&quot;Sample_Count&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x6E
comma
l_string|&quot;Set_Periodic_Report&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x6F
comma
l_string|&quot;Offset&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x70
comma
l_string|&quot;Magnitude&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x71
comma
l_string|&quot;Phase&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x72
comma
l_string|&quot;Period&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x73
comma
l_string|&quot;Set_Constant_Force_Report&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x74
comma
l_string|&quot;Set_Ramp_Force_Report&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x75
comma
l_string|&quot;Ramp_Start&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x76
comma
l_string|&quot;Ramp_End&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x77
comma
l_string|&quot;Effect_Operation_Report&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x78
comma
l_string|&quot;Effect_Operation&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x79
comma
l_string|&quot;Op_Effect_Start&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x7A
comma
l_string|&quot;Op_Effect_Start_Solo&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x7B
comma
l_string|&quot;Op_Effect_Stop&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x7C
comma
l_string|&quot;Loop_Count&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x7D
comma
l_string|&quot;Device_Gain_Report&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x7E
comma
l_string|&quot;Device_Gain&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x7F
comma
l_string|&quot;PID_Pool_Report&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x80
comma
l_string|&quot;RAM_Pool_Size&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x81
comma
l_string|&quot;ROM_Pool_Size&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x82
comma
l_string|&quot;ROM_Effect_Block_Count&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x83
comma
l_string|&quot;Simultaneous_Effects_Max&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x84
comma
l_string|&quot;Pool_Alignment&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x85
comma
l_string|&quot;PID_Pool_Move_Report&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x86
comma
l_string|&quot;Move_Source&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x87
comma
l_string|&quot;Move_Destination&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x88
comma
l_string|&quot;Move_Length&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x89
comma
l_string|&quot;PID_Block_Load_Report&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x8B
comma
l_string|&quot;Block_Load_Status&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x8C
comma
l_string|&quot;Block_Load_Success&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x8D
comma
l_string|&quot;Block_Load_Full&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x8E
comma
l_string|&quot;Block_Load_Error&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x8F
comma
l_string|&quot;Block_Handle&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x90
comma
l_string|&quot;PID_Block_Free_Report&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x91
comma
l_string|&quot;Type_Specific_Block_Handle&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x92
comma
l_string|&quot;PID_State_Report&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x94
comma
l_string|&quot;Effect_Playing&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x95
comma
l_string|&quot;PID_Device_Control_Report&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x96
comma
l_string|&quot;PID_Device_Control&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x97
comma
l_string|&quot;DC_Enable_Actuators&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x98
comma
l_string|&quot;DC_Disable_Actuators&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x99
comma
l_string|&quot;DC_Stop_All_Effects&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x9A
comma
l_string|&quot;DC_Device_Reset&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x9B
comma
l_string|&quot;DC_Device_Pause&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x9C
comma
l_string|&quot;DC_Device_Continue&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0x9F
comma
l_string|&quot;Device_Paused&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0xA0
comma
l_string|&quot;Actuators_Enabled&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0xA4
comma
l_string|&quot;Safety_Switch&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0xA5
comma
l_string|&quot;Actuator_Override_Switch&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0xA6
comma
l_string|&quot;Actuator_Power&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0xA7
comma
l_string|&quot;Start_Delay&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0xA8
comma
l_string|&quot;Parameter_Block_Size&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0xA9
comma
l_string|&quot;Device_Managed_Pool&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0xAA
comma
l_string|&quot;Shared_Parameter_Blocks&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0xAB
comma
l_string|&quot;Create_New_Effect_Report&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0xAC
comma
l_string|&quot;RAM_Pool_Available&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0
comma
l_int|NULL
)brace
)brace
suffix:semicolon
DECL|function|resolv_usage_page
r_static
r_void
id|resolv_usage_page
c_func
(paren
r_int
id|page
)paren
(brace
r_struct
id|hid_usage_entry
op_star
id|p
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|hid_usage_table
suffix:semicolon
id|p-&gt;description
suffix:semicolon
id|p
op_increment
)paren
r_if
c_cond
(paren
id|p-&gt;page
op_eq
id|page
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s&quot;
comma
id|p-&gt;description
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;%04x&quot;
comma
id|page
)paren
suffix:semicolon
)brace
DECL|function|resolv_usage
r_static
r_void
id|resolv_usage
c_func
(paren
r_int
id|usage
)paren
(brace
r_struct
id|hid_usage_entry
op_star
id|p
suffix:semicolon
id|resolv_usage_page
c_func
(paren
id|usage
op_rshift
l_int|16
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;.&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|hid_usage_table
suffix:semicolon
id|p-&gt;description
suffix:semicolon
id|p
op_increment
)paren
r_if
c_cond
(paren
id|p-&gt;page
op_eq
(paren
id|usage
op_rshift
l_int|16
)paren
)paren
(brace
r_for
c_loop
(paren
op_increment
id|p
suffix:semicolon
id|p-&gt;description
op_logical_and
id|p-&gt;page
op_eq
l_int|0
suffix:semicolon
id|p
op_increment
)paren
r_if
c_cond
(paren
id|p-&gt;usage
op_eq
(paren
id|usage
op_amp
l_int|0xffff
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s&quot;
comma
id|p-&gt;description
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;%04x&quot;
comma
id|usage
op_amp
l_int|0xffff
)paren
suffix:semicolon
)brace
DECL|function|tab
id|__inline__
r_static
r_void
id|tab
c_func
(paren
r_int
id|n
)paren
(brace
r_while
c_loop
(paren
id|n
op_decrement
)paren
id|printk
c_func
(paren
l_string|&quot; &quot;
)paren
suffix:semicolon
)brace
DECL|function|hid_dump_field
r_static
r_void
id|hid_dump_field
c_func
(paren
r_struct
id|hid_field
op_star
id|field
comma
r_int
id|n
)paren
(brace
r_int
id|j
suffix:semicolon
r_if
c_cond
(paren
id|field-&gt;physical
)paren
(brace
id|tab
c_func
(paren
id|n
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Physical(&quot;
)paren
suffix:semicolon
id|resolv_usage
c_func
(paren
id|field-&gt;physical
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;)&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|field-&gt;logical
)paren
(brace
id|tab
c_func
(paren
id|n
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Logical(&quot;
)paren
suffix:semicolon
id|resolv_usage
c_func
(paren
id|field-&gt;logical
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;)&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|tab
c_func
(paren
id|n
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Usage(%d)&bslash;n&quot;
comma
id|field-&gt;maxusage
)paren
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|field-&gt;maxusage
suffix:semicolon
id|j
op_increment
)paren
(brace
id|tab
c_func
(paren
id|n
op_plus
l_int|2
)paren
suffix:semicolon
id|resolv_usage
c_func
(paren
id|field-&gt;usage
(braket
id|j
)braket
dot
id|hid
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|field-&gt;logical_minimum
op_ne
id|field-&gt;logical_maximum
)paren
(brace
id|tab
c_func
(paren
id|n
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Logical Minimum(%d)&bslash;n&quot;
comma
id|field-&gt;logical_minimum
)paren
suffix:semicolon
id|tab
c_func
(paren
id|n
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Logical Maximum(%d)&bslash;n&quot;
comma
id|field-&gt;logical_maximum
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|field-&gt;physical_minimum
op_ne
id|field-&gt;physical_maximum
)paren
(brace
id|tab
c_func
(paren
id|n
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Physical Minimum(%d)&bslash;n&quot;
comma
id|field-&gt;physical_minimum
)paren
suffix:semicolon
id|tab
c_func
(paren
id|n
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Physical Maximum(%d)&bslash;n&quot;
comma
id|field-&gt;physical_maximum
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|field-&gt;unit_exponent
)paren
(brace
id|tab
c_func
(paren
id|n
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Unit Exponent(%d)&bslash;n&quot;
comma
id|field-&gt;unit_exponent
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|field-&gt;unit
)paren
(brace
r_char
op_star
id|systems
(braket
l_int|5
)braket
op_assign
(brace
l_string|&quot;None&quot;
comma
l_string|&quot;SI Linear&quot;
comma
l_string|&quot;SI Rotation&quot;
comma
l_string|&quot;English Linear&quot;
comma
l_string|&quot;English Rotation&quot;
)brace
suffix:semicolon
r_char
op_star
id|units
(braket
l_int|5
)braket
(braket
l_int|8
)braket
op_assign
(brace
(brace
l_string|&quot;None&quot;
comma
l_string|&quot;None&quot;
comma
l_string|&quot;None&quot;
comma
l_string|&quot;None&quot;
comma
l_string|&quot;None&quot;
comma
l_string|&quot;None&quot;
comma
l_string|&quot;None&quot;
comma
l_string|&quot;None&quot;
)brace
comma
(brace
l_string|&quot;None&quot;
comma
l_string|&quot;Centimeter&quot;
comma
l_string|&quot;Gram&quot;
comma
l_string|&quot;Seconds&quot;
comma
l_string|&quot;Kelvin&quot;
comma
l_string|&quot;Ampere&quot;
comma
l_string|&quot;Candela&quot;
comma
l_string|&quot;None&quot;
)brace
comma
(brace
l_string|&quot;None&quot;
comma
l_string|&quot;Radians&quot;
comma
l_string|&quot;Gram&quot;
comma
l_string|&quot;Seconds&quot;
comma
l_string|&quot;Kelvin&quot;
comma
l_string|&quot;Ampere&quot;
comma
l_string|&quot;Candela&quot;
comma
l_string|&quot;None&quot;
)brace
comma
(brace
l_string|&quot;None&quot;
comma
l_string|&quot;Inch&quot;
comma
l_string|&quot;Slug&quot;
comma
l_string|&quot;Seconds&quot;
comma
l_string|&quot;Fahrenheit&quot;
comma
l_string|&quot;Ampere&quot;
comma
l_string|&quot;Candela&quot;
comma
l_string|&quot;None&quot;
)brace
comma
(brace
l_string|&quot;None&quot;
comma
l_string|&quot;Degrees&quot;
comma
l_string|&quot;Slug&quot;
comma
l_string|&quot;Seconds&quot;
comma
l_string|&quot;Fahrenheit&quot;
comma
l_string|&quot;Ampere&quot;
comma
l_string|&quot;Candela&quot;
comma
l_string|&quot;None&quot;
)brace
)brace
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
id|sys
suffix:semicolon
id|__u32
id|data
op_assign
id|field-&gt;unit
suffix:semicolon
multiline_comment|/* First nibble tells us which system we&squot;re in. */
id|sys
op_assign
id|data
op_amp
l_int|0xf
suffix:semicolon
id|data
op_rshift_assign
l_int|4
suffix:semicolon
r_if
c_cond
(paren
id|sys
OG
l_int|4
)paren
(brace
id|tab
c_func
(paren
id|n
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Unit(Invalid)&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
r_int
id|earlier_unit
op_assign
l_int|0
suffix:semicolon
id|tab
c_func
(paren
id|n
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Unit(%s : &quot;
comma
id|systems
(braket
id|sys
)braket
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
r_sizeof
(paren
id|__u32
)paren
op_star
l_int|2
suffix:semicolon
id|i
op_increment
)paren
(brace
r_char
id|nibble
op_assign
id|data
op_amp
l_int|0xf
suffix:semicolon
id|data
op_rshift_assign
l_int|4
suffix:semicolon
r_if
c_cond
(paren
id|nibble
op_ne
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|earlier_unit
op_increment
OG
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;*&quot;
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;%s&quot;
comma
id|units
(braket
id|sys
)braket
(braket
id|i
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nibble
op_ne
l_int|1
)paren
(brace
multiline_comment|/* This is a _signed_ nibble(!) */
r_int
id|val
op_assign
id|nibble
op_amp
l_int|0x7
suffix:semicolon
r_if
c_cond
(paren
id|nibble
op_amp
l_int|0x08
)paren
(brace
id|val
op_assign
op_minus
(paren
(paren
l_int|0x7
op_amp
op_complement
id|val
)paren
op_plus
l_int|1
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;^%d&quot;
comma
id|val
)paren
suffix:semicolon
)brace
)brace
)brace
id|printk
c_func
(paren
l_string|&quot;)&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
id|tab
c_func
(paren
id|n
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Report Size(%u)&bslash;n&quot;
comma
id|field-&gt;report_size
)paren
suffix:semicolon
id|tab
c_func
(paren
id|n
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Report Count(%u)&bslash;n&quot;
comma
id|field-&gt;report_count
)paren
suffix:semicolon
id|tab
c_func
(paren
id|n
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Report Offset(%u)&bslash;n&quot;
comma
id|field-&gt;report_offset
)paren
suffix:semicolon
id|tab
c_func
(paren
id|n
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Flags( &quot;
)paren
suffix:semicolon
id|j
op_assign
id|field-&gt;flags
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s&quot;
comma
id|HID_MAIN_ITEM_CONSTANT
op_amp
id|j
ques
c_cond
l_string|&quot;Constant &quot;
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s&quot;
comma
id|HID_MAIN_ITEM_VARIABLE
op_amp
id|j
ques
c_cond
l_string|&quot;Variable &quot;
suffix:colon
l_string|&quot;Array &quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s&quot;
comma
id|HID_MAIN_ITEM_RELATIVE
op_amp
id|j
ques
c_cond
l_string|&quot;Relative &quot;
suffix:colon
l_string|&quot;Absolute &quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s&quot;
comma
id|HID_MAIN_ITEM_WRAP
op_amp
id|j
ques
c_cond
l_string|&quot;Wrap &quot;
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s&quot;
comma
id|HID_MAIN_ITEM_NONLINEAR
op_amp
id|j
ques
c_cond
l_string|&quot;NonLinear &quot;
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s&quot;
comma
id|HID_MAIN_ITEM_NO_PREFERRED
op_amp
id|j
ques
c_cond
l_string|&quot;NoPrefferedState &quot;
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s&quot;
comma
id|HID_MAIN_ITEM_NULL_STATE
op_amp
id|j
ques
c_cond
l_string|&quot;NullState &quot;
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s&quot;
comma
id|HID_MAIN_ITEM_VOLATILE
op_amp
id|j
ques
c_cond
l_string|&quot;Volatile &quot;
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s&quot;
comma
id|HID_MAIN_ITEM_BUFFERED_BYTE
op_amp
id|j
ques
c_cond
l_string|&quot;BufferedByte &quot;
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;)&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|function|hid_dump_device
r_static
r_void
id|__attribute__
c_func
(paren
(paren
id|unused
)paren
)paren
id|hid_dump_device
c_func
(paren
r_struct
id|hid_device
op_star
id|device
)paren
(brace
r_struct
id|hid_report_enum
op_star
id|report_enum
suffix:semicolon
r_struct
id|hid_report
op_star
id|report
suffix:semicolon
r_struct
id|list_head
op_star
id|list
suffix:semicolon
r_int
id|i
comma
id|k
suffix:semicolon
r_static
r_char
op_star
id|table
(braket
)braket
op_assign
(brace
l_string|&quot;INPUT&quot;
comma
l_string|&quot;OUTPUT&quot;
comma
l_string|&quot;FEATURE&quot;
)brace
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|HID_REPORT_TYPES
suffix:semicolon
id|i
op_increment
)paren
(brace
id|report_enum
op_assign
id|device-&gt;report_enum
op_plus
id|i
suffix:semicolon
id|list
op_assign
id|report_enum-&gt;report_list.next
suffix:semicolon
r_while
c_loop
(paren
id|list
op_ne
op_amp
id|report_enum-&gt;report_list
)paren
(brace
id|report
op_assign
(paren
r_struct
id|hid_report
op_star
)paren
id|list
suffix:semicolon
id|tab
c_func
(paren
l_int|2
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s&quot;
comma
id|table
(braket
id|i
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|report-&gt;id
)paren
id|printk
c_func
(paren
l_string|&quot;(%d)&quot;
comma
id|report-&gt;id
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;[%s]&quot;
comma
id|table
(braket
id|report-&gt;type
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|k
op_assign
l_int|0
suffix:semicolon
id|k
OL
id|report-&gt;maxfield
suffix:semicolon
id|k
op_increment
)paren
(brace
id|tab
c_func
(paren
l_int|4
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Field(%d)&bslash;n&quot;
comma
id|k
)paren
suffix:semicolon
id|hid_dump_field
c_func
(paren
id|report-&gt;field
(braket
id|k
)braket
comma
l_int|6
)paren
suffix:semicolon
)brace
id|list
op_assign
id|list-&gt;next
suffix:semicolon
)brace
)brace
)brace
DECL|function|hid_dump_input
r_static
r_void
id|__attribute__
c_func
(paren
(paren
id|unused
)paren
)paren
id|hid_dump_input
c_func
(paren
r_struct
id|hid_usage
op_star
id|usage
comma
id|__s32
id|value
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;hid-debug: input &quot;
)paren
suffix:semicolon
id|resolv_usage
c_func
(paren
id|usage-&gt;hid
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; = %d&bslash;n&quot;
comma
id|value
)paren
suffix:semicolon
)brace
eof
