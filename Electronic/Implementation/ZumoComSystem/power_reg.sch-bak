EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 7
Title "Zumo Communication System"
Date "2021-07-28"
Rev "V1.0"
Comp "NewTec GmbH"
Comment1 "Schneider, Niklas"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L TPS62056DGS:TPS62056DGS U2
U 1 1 60C6791C
P 5450 2000
F 0 "U2" H 5450 2670 50  0000 C CNN
F 1 "TPS62056DGS" H 5450 2579 50  0000 C CNN
F 2 "SOP50P490X110-10N" H 5450 2000 50  0001 L BNN
F 3 "https://www.ti.com/lit/ds/symlink/tps62056.pdf?HQS=dis-mous-null-mousermode-dsf-pf-null-wwe&ts=1624013814534&ref_url=https%253A%252F%252Feu.mouser.com%252F" H 5450 2000 50  0001 L BNN
	1    5450 2000
	1    0    0    -1  
$EndComp
$Comp
L LT1374CS8-5PBF:LT1374CS8-5PBF U1
U 1 1 60C689A1
P 4650 4200
F 0 "U1" H 6250 4565 50  0000 C CNN
F 1 "LT1374CS8-5PBF" H 6250 4474 50  0000 C CNN
F 2 "SO-8_S" H 4650 4200 50  0001 L BNN
F 3 "https://www.analog.com/media/en/technical-documentation/data-sheets/1374fd.pdf" H 4650 4200 50  0001 L BNN
F 4 "lt1374cs85#pbf" H 4650 4200 50  0001 L BNN "MANUFACTURER_PART_NUMBER"
F 5 "Linear Technology" H 4650 4200 50  0001 L BNN "VENDOR"
	1    4650 4200
	1    0    0    -1  
$EndComp
$Comp
L Device:L L1
U 1 1 60C698F7
P 6600 1800
F 0 "L1" V 6790 1800 50  0000 C CNN
F 1 "15uH" V 6699 1800 50  0000 C CNN
F 2 "Inductor_SMD:L_Wuerth_HCI-1040" H 6600 1800 50  0001 C CNN
F 3 "https://www.we-online.de/katalog/datasheet/74437368150.pdf" H 6600 1800 50  0001 C CNN
	1    6600 1800
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6150 1800 6450 1800
Text HLabel 1000 1250 0    50   Input ~ 0
V_Bat
$Comp
L power:+3V3 #PWR08
U 1 1 60CC7A1E
P 7200 1300
F 0 "#PWR08" H 7200 1150 50  0001 C CNN
F 1 "+3V3" H 7215 1473 50  0000 C CNN
F 2 "" H 7200 1300 50  0001 C CNN
F 3 "" H 7200 1300 50  0001 C CNN
	1    7200 1300
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR011
U 1 1 60CC818D
P 9250 3500
F 0 "#PWR011" H 9250 3350 50  0001 C CNN
F 1 "+5V" H 9265 3673 50  0000 C CNN
F 2 "" H 9250 3500 50  0001 C CNN
F 3 "" H 9250 3500 50  0001 C CNN
	1    9250 3500
	1    0    0    -1  
$EndComp
Wire Wire Line
	6150 1600 6350 1600
Wire Wire Line
	6350 1600 6350 1700
Wire Wire Line
	9100 4200 9250 4200
Wire Wire Line
	9250 4200 9250 3700
Wire Wire Line
	3950 2000 4650 2000
Wire Wire Line
	3950 4200 4650 4200
Connection ~ 3950 2000
Wire Wire Line
	4750 1600 3950 1600
$Comp
L power:GND #PWR06
U 1 1 60CDA80F
P 6350 2550
F 0 "#PWR06" H 6350 2300 50  0001 C CNN
F 1 "GND" H 6355 2377 50  0000 C CNN
F 2 "" H 6350 2550 50  0001 C CNN
F 3 "" H 6350 2550 50  0001 C CNN
	1    6350 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	4750 1800 4450 1800
Wire Wire Line
	4450 1800 4450 1900
Wire Wire Line
	4750 1900 4450 1900
Wire Wire Line
	6150 2300 6350 2300
Wire Wire Line
	6350 2300 6350 2400
Wire Wire Line
	6150 2400 6350 2400
Connection ~ 6350 2400
Wire Wire Line
	6350 2400 6350 2550
Wire Wire Line
	6150 1700 6350 1700
Wire Wire Line
	6350 1700 6350 2300
Connection ~ 6350 2300
$Comp
L power:GND #PWR03
U 1 1 60CDABA5
P 4450 2550
F 0 "#PWR03" H 4450 2300 50  0001 C CNN
F 1 "GND" H 4455 2377 50  0000 C CNN
F 2 "" H 4450 2550 50  0001 C CNN
F 3 "" H 4450 2550 50  0001 C CNN
	1    4450 2550
	1    0    0    -1  
$EndComp
Connection ~ 4450 1900
Wire Wire Line
	4450 1900 4450 2550
Wire Wire Line
	6850 950  6850 1800
Wire Wire Line
	6850 1800 6750 1800
$Comp
L Device:C C2
U 1 1 60CE065A
P 4650 2250
F 0 "C2" H 4765 2296 50  0000 L CNN
F 1 "10uF" H 4765 2205 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 4688 2100 50  0001 C CNN
F 3 "https://product.tdk.com/en/system/files?file=dam/doc/product/capacitor/ceramic/mlcc/catalog/mlcc_commercial_general_en.pdf" H 4650 2250 50  0001 C CNN
	1    4650 2250
	1    0    0    -1  
$EndComp
Wire Wire Line
	6850 1800 6850 2050
Connection ~ 6850 1800
Wire Wire Line
	6850 2350 6850 2550
Wire Wire Line
	4650 2000 4650 2100
Connection ~ 4650 2000
Wire Wire Line
	4650 2000 4750 2000
Wire Wire Line
	4650 2400 4650 2550
$Comp
L power:GND #PWR05
U 1 1 60CE2DC8
P 4650 2550
F 0 "#PWR05" H 4650 2300 50  0001 C CNN
F 1 "GND" H 4655 2377 50  0000 C CNN
F 2 "" H 4650 2550 50  0001 C CNN
F 3 "" H 4650 2550 50  0001 C CNN
	1    4650 2550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR07
U 1 1 60CE2EFC
P 6850 2550
F 0 "#PWR07" H 6850 2300 50  0001 C CNN
F 1 "GND" H 6855 2377 50  0000 C CNN
F 2 "" H 6850 2550 50  0001 C CNN
F 3 "" H 6850 2550 50  0001 C CNN
	1    6850 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	4650 950  6850 950 
Wire Wire Line
	4750 1700 4650 1700
Wire Wire Line
	4650 1700 4650 950 
Wire Wire Line
	6850 1800 7200 1800
Connection ~ 6350 1700
Wire Wire Line
	7200 1800 7200 1300
Wire Wire Line
	3200 2000 3950 2000
Wire Wire Line
	3200 1250 3200 1500
Wire Wire Line
	3200 1900 3200 2000
$Comp
L power:GND #PWR01
U 1 1 60CF3E43
P 1950 2350
F 0 "#PWR01" H 1950 2100 50  0001 C CNN
F 1 "GND" H 1955 2177 50  0000 C CNN
F 2 "" H 1950 2350 50  0001 C CNN
F 3 "" H 1950 2350 50  0001 C CNN
	1    1950 2350
	1    0    0    -1  
$EndComp
Wire Wire Line
	3950 1600 3950 2000
$Comp
L MLL1200S:MLL1200S SW1
U 1 1 60CF5DEF
P 1950 1800
F 0 "SW1" H 1950 2265 50  0000 C CNN
F 1 "MLL1200S" H 1950 2174 50  0000 C CNN
F 2 "SW_MLL1200S" H 1950 1800 50  0001 L BNN
F 3 "https://www.te.com/commerce/DocumentDelivery/DDEController?Action=srchrtrv&DocNm=1308111-1_SWITCHES_CORE_PROGRAM_CATALOG&DocType=CS&DocLang=English" H 1950 1800 50  0001 L BNN
F 4 "1437575-1" H 1950 1800 50  0001 L BNN "Comment"
	1    1950 1800
	1    0    0    -1  
$EndComp
Wire Wire Line
	1550 1800 1450 1800
Wire Wire Line
	1450 1800 1450 2150
Wire Wire Line
	1450 2150 1950 2150
Wire Wire Line
	2500 2150 2500 1900
Wire Wire Line
	2500 1900 2350 1900
Wire Wire Line
	1950 2150 1950 2350
Connection ~ 1950 2150
Wire Wire Line
	1950 2150 2500 2150
Wire Wire Line
	3300 1500 3200 1500
Connection ~ 3200 1500
$Comp
L Device:C C1
U 1 1 60D11B75
P 3950 4850
F 0 "C1" H 4065 4896 50  0000 L CNN
F 1 "22uF" H 4065 4805 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 3988 4700 50  0001 C CNN
F 3 "https://product.tdk.com/info/en/catalog/datasheets/mlcc_commercial_general_en.pdf?ref_disty=digikey" H 3950 4850 50  0001 C CNN
	1    3950 4850
	1    0    0    -1  
$EndComp
Wire Wire Line
	4650 4300 4450 4300
$Comp
L power:GND #PWR02
U 1 1 60D140B6
P 3950 5400
F 0 "#PWR02" H 3950 5150 50  0001 C CNN
F 1 "GND" H 3955 5227 50  0000 C CNN
F 2 "" H 3950 5400 50  0001 C CNN
F 3 "" H 3950 5400 50  0001 C CNN
	1    3950 5400
	1    0    0    -1  
$EndComp
Connection ~ 3950 4200
Wire Wire Line
	3950 4200 3950 4700
Wire Wire Line
	3950 5400 3950 5000
$Comp
L Device:D D2
U 1 1 60D196DD
P 8900 3700
F 0 "D2" H 8900 3917 50  0000 C CNN
F 1 "30V 100mA" H 8900 3826 50  0000 C CNN
F 2 "Diode_SMD:D_SOD-323" H 8900 3700 50  0001 C CNN
F 3 "https://my.centralsemi.com/datasheets/CMDSH-3.PDF" H 8900 3700 50  0001 C CNN
	1    8900 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	7850 4200 8650 4200
Wire Wire Line
	8650 4100 8650 4200
Connection ~ 8650 4200
Wire Wire Line
	8650 4200 8800 4200
Wire Wire Line
	9050 3700 9250 3700
Connection ~ 9250 4200
Wire Wire Line
	8750 3700 8650 3700
Wire Wire Line
	8650 3700 8650 3800
Wire Wire Line
	8650 3700 7950 3700
Wire Wire Line
	4450 3700 4450 4300
Connection ~ 8650 3700
$Comp
L Device:C C4
U 1 1 60D211FE
P 8050 4800
F 0 "C4" H 8165 4846 50  0000 L CNN
F 1 "1.5nF" H 8165 4755 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 8088 4650 50  0001 C CNN
F 3 "https://www.we-online.de/katalog/datasheet/885012206084.pdf" H 8050 4800 50  0001 C CNN
	1    8050 4800
	1    0    0    -1  
$EndComp
Wire Wire Line
	4650 4400 4450 4400
Wire Wire Line
	4450 4400 4450 4300
Connection ~ 4450 4300
Wire Wire Line
	9250 4500 9250 4200
$Comp
L Device:C C6
U 1 1 60D2533E
P 9250 4800
F 0 "C6" H 9365 4846 50  0000 L CNN
F 1 "100uF" H 9365 4755 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 9288 4650 50  0001 C CNN
F 3 "https://product.tdk.com/en/system/files?file=dam/doc/product/capacitor/ceramic/mlcc/catalog/mlcc_commercial_general_en.pdf" H 9250 4800 50  0001 C CNN
	1    9250 4800
	1    0    0    -1  
$EndComp
Wire Wire Line
	9250 4500 9250 4650
Connection ~ 9250 4500
Wire Wire Line
	7850 4500 9250 4500
Wire Wire Line
	8050 4650 8050 4400
$Comp
L power:GND #PWR09
U 1 1 60D2AA9B
P 8050 5400
F 0 "#PWR09" H 8050 5150 50  0001 C CNN
F 1 "GND" H 8055 5227 50  0000 C CNN
F 2 "" H 8050 5400 50  0001 C CNN
F 3 "" H 8050 5400 50  0001 C CNN
	1    8050 5400
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR012
U 1 1 60D2B041
P 9250 5400
F 0 "#PWR012" H 9250 5150 50  0001 C CNN
F 1 "GND" H 9255 5227 50  0000 C CNN
F 2 "" H 9250 5400 50  0001 C CNN
F 3 "" H 9250 5400 50  0001 C CNN
	1    9250 5400
	1    0    0    -1  
$EndComp
Wire Wire Line
	8050 4950 8050 5400
Wire Wire Line
	9250 4950 9250 5400
Wire Wire Line
	3950 3450 8050 3450
Connection ~ 9250 3700
Wire Wire Line
	9250 3700 9250 3500
$Comp
L Device:D D1
U 1 1 60D62CCC
P 8650 4800
F 0 "D1" V 8604 4880 50  0000 L CNN
F 1 "40V 5A" V 8695 4880 50  0000 L CNN
F 2 "Diode_SMD:D_2114_3652Metric_Pad1.85x3.75mm_HandSolder" H 8650 4800 50  0001 C CNN
F 3 "https://datasheets.avx.com/schottky.pdf" H 8650 4800 50  0001 C CNN
	1    8650 4800
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR010
U 1 1 60D630D3
P 8650 5400
F 0 "#PWR010" H 8650 5150 50  0001 C CNN
F 1 "GND" H 8655 5227 50  0000 C CNN
F 2 "" H 8650 5400 50  0001 C CNN
F 3 "" H 8650 5400 50  0001 C CNN
	1    8650 5400
	1    0    0    -1  
$EndComp
Wire Wire Line
	8650 4950 8650 5400
Wire Wire Line
	8650 4200 8650 4650
Wire Wire Line
	4450 4500 4450 5400
$Comp
L power:GND #PWR04
U 1 1 60D67CF9
P 4450 5400
F 0 "#PWR04" H 4450 5150 50  0001 C CNN
F 1 "GND" H 4455 5227 50  0000 C CNN
F 2 "" H 4450 5400 50  0001 C CNN
F 3 "" H 4450 5400 50  0001 C CNN
	1    4450 5400
	1    0    0    -1  
$EndComp
Wire Wire Line
	4450 4500 4650 4500
Wire Wire Line
	7850 4300 7950 4300
Wire Wire Line
	7950 4300 7950 3700
Connection ~ 7950 3700
Wire Wire Line
	7950 3700 4450 3700
Wire Wire Line
	8050 3450 8050 4400
Wire Wire Line
	3950 2000 3950 3450
Connection ~ 8050 4400
Connection ~ 3950 3450
Wire Wire Line
	3950 3450 3950 4200
Wire Wire Line
	7850 4400 8050 4400
$Comp
L Device:L L2
U 1 1 60C6A253
P 8950 4200
F 0 "L2" V 9140 4200 50  0000 C CNN
F 1 "22uH" V 9049 4200 50  0000 C CNN
F 2 "footprints:L_Wuerth_HCI-1350_3D" H 8950 4200 50  0001 C CNN
F 3 "https://www.vishay.com/docs/34282/ihlp-6767gz-11.pdf" H 8950 4200 50  0001 C CNN
	1    8950 4200
	0    -1   -1   0   
$EndComp
$Comp
L Device:C C5
U 1 1 60D19B44
P 8650 3950
F 0 "C5" H 8400 4000 50  0000 L CNN
F 1 "270nF" H 8300 3900 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 8688 3800 50  0001 C CNN
F 3 "https://api.kemet.com/component-edge/download/specsheet/C0805R274K5RACT500.pdf" H 8650 3950 50  0001 C CNN
	1    8650 3950
	1    0    0    -1  
$EndComp
$Comp
L Device:C C3
U 1 1 60D9BDF5
P 6850 2200
F 0 "C3" H 6965 2246 50  0000 L CNN
F 1 "22uF" H 6965 2155 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 6888 2050 50  0001 C CNN
F 3 "https://product.tdk.com/info/en/catalog/datasheets/mlcc_commercial_general_en.pdf?ref_disty=digikey" H 6850 2200 50  0001 C CNN
	1    6850 2200
	1    0    0    -1  
$EndComp
Wire Wire Line
	1550 1600 1450 1600
Wire Wire Line
	1450 1600 1450 1250
Wire Wire Line
	2350 1700 2900 1700
Connection ~ 1450 1250
Wire Wire Line
	1450 1250 3200 1250
Wire Wire Line
	1000 1250 1450 1250
$Comp
L pspice:MPMOS M1
U 1 1 60D049A0
P 3100 1700
F 0 "M1" H 3388 1746 50  0000 L CNN
F 1 "40V 6A" H 3388 1655 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-89-3_Handsoldering" H 3100 1700 50  0001 C CNN
F 3 "https://my.centralsemi.com/datasheets/CXDM4060P.PDF" H 3100 1700 50  0001 C CNN
	1    3100 1700
	1    0    0    -1  
$EndComp
$EndSCHEMATC
