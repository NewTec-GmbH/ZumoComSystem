EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 7
Title "Zumo Communication System"
Date "2022-05-27"
Rev "V1.1"
Comp "NewTec GmbH"
Comment1 "Schneider, Niklas"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text HLabel 1000 1250 0    50   Input ~ 0
V_Bat
$Comp
L power:+3V3 #PWR014
U 1 1 60CC7A1E
P 9750 1250
F 0 "#PWR014" H 9750 1100 50  0001 C CNN
F 1 "+3V3" H 9765 1423 50  0000 C CNN
F 2 "" H 9750 1250 50  0001 C CNN
F 3 "" H 9750 1250 50  0001 C CNN
	1    9750 1250
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
	9100 4200 9250 4200
Wire Wire Line
	9250 4200 9250 3700
Wire Wire Line
	3950 2000 4650 2000
Wire Wire Line
	3950 4200 4650 4200
Connection ~ 3950 2000
Wire Wire Line
	9400 1500 8500 1500
Wire Wire Line
	9400 1500 9400 2000
Connection ~ 9400 1500
Wire Wire Line
	9400 2300 9400 2500
Wire Wire Line
	4650 2000 4650 2100
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
L power:GND #PWR013
U 1 1 60CE2EFC
P 9400 2500
F 0 "#PWR013" H 9400 2250 50  0001 C CNN
F 1 "GND" H 9405 2327 50  0000 C CNN
F 2 "" H 9400 2500 50  0001 C CNN
F 3 "" H 9400 2500 50  0001 C CNN
	1    9400 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	9400 1500 9750 1500
Wire Wire Line
	9750 1500 9750 1250
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
	4650 4300 4450 4300
$Comp
L power:GND #PWR03
U 1 1 60D140B6
P 3950 5400
F 0 "#PWR03" H 3950 5150 50  0001 C CNN
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
	4450 3700 4450 4300
Wire Wire Line
	9250 4500 9250 4200
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
Connection ~ 9250 3700
Wire Wire Line
	9250 3700 9250 3500
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
	8050 3450 8050 4300
Wire Wire Line
	3950 2000 3950 3450
Connection ~ 8050 4400
Connection ~ 3950 3450
Wire Wire Line
	3950 3450 3950 4200
Wire Wire Line
	7850 4400 8050 4400
Wire Wire Line
	1550 1600 1450 1600
Wire Wire Line
	1450 1600 1450 1250
Connection ~ 1450 1250
Wire Wire Line
	1450 1250 3250 1250
Wire Wire Line
	1000 1250 1450 1250
Wire Wire Line
	3250 2000 3250 1900
Wire Wire Line
	3250 2000 3950 2000
Wire Wire Line
	3250 1250 3250 1500
Text Notes 1350 1150 0    50   ~ 0
U_Bat_max = 8.4 V\nI_Bat_max = 4,2 A 
Text Notes 9150 3250 0    50   ~ 0
\nImax = 3 A 
Text Notes 9600 1000 0    50   ~ 0
Imax = 250mA 
$Comp
L LT1374CS8-5PBF:LT1374CS8-5PBF U1
U 1 1 60C689A1
P 4650 4200
F 0 "U1" H 6250 4565 50  0000 C CNN
F 1 "LT1374CS8-5PBF" H 6250 4474 50  0000 C CNN
F 2 "SO-8_S" H 4650 4200 50  0001 L BNN
F 3 "https://www.analog.com/media/en/technical-documentation/data-sheets/1374fd.pdf" H 4650 4200 50  0001 L BNN
F 4 "Analog Device" H 4650 4200 50  0001 C CNN "Manufacturer"
F 5 "LT1374CS8-5PBF" H 4650 4200 50  0001 C CNN "Part-No."
	1    4650 4200
	1    0    0    -1  
$EndComp
$Comp
L Device:C C2
U 1 1 60CE065A
P 4650 2250
F 0 "C2" H 4765 2296 50  0000 L CNN
F 1 "10u" H 4765 2205 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 4688 2100 50  0001 C CNN
F 3 "https://product.tdk.com/en/system/files?file=dam/doc/product/capacitor/ceramic/mlcc/catalog/mlcc_commercial_general_en.pdf" H 4650 2250 50  0001 C CNN
F 4 "TDK Corporation" H 4650 2250 50  0001 C CNN "Manufacturer"
F 5 "C2012X5R1V106M085AC" H 4650 2250 50  0001 C CNN "Part-No."
	1    4650 2250
	1    0    0    -1  
$EndComp
$Comp
L MLL1200S:MLL1200S SW1
U 1 1 60CF5DEF
P 1950 1800
F 0 "SW1" H 1950 2265 50  0000 C CNN
F 1 "MLL1200S" H 1950 2174 50  0000 C CNN
F 2 "SW_MLL1200S" H 1950 1800 50  0001 L BNN
F 3 "https://www.te.com/commerce/DocumentDelivery/DDEController?Action=srchrtrv&DocNm=1308111-1_SWITCHES_CORE_PROGRAM_CATALOG&DocType=CS&DocLang=English" H 1950 1800 50  0001 L BNN
F 4 "TE Connectivity / P&B " H 1950 1800 50  0001 C CNN "Manufacturer"
F 5 "MLL1200S " H 1950 1800 50  0001 C CNN "Part-No."
	1    1950 1800
	1    0    0    -1  
$EndComp
$Comp
L Device:C C1
U 1 1 60D11B75
P 3950 4850
F 0 "C1" H 4065 4896 50  0000 L CNN
F 1 "22u" H 4065 4805 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 3988 4700 50  0001 C CNN
F 3 "https://product.tdk.com/info/en/catalog/datasheets/mlcc_commercial_general_en.pdf?ref_disty=digikey" H 3950 4850 50  0001 C CNN
F 4 " Murata Electronics " H 3950 4850 50  0001 C CNN "Manufacturer"
F 5 "GRM31CC81E226KE11L" H 3950 4850 50  0001 C CNN "Part-No."
	1    3950 4850
	1    0    0    -1  
$EndComp
$Comp
L Device:D D2
U 1 1 60D196DD
P 8900 3700
F 0 "D2" H 8900 3917 50  0000 C CNN
F 1 "30V 100mA" H 8900 3826 50  0000 C CNN
F 2 "Diode_SMD:D_SOD-323" H 8900 3700 50  0001 C CNN
F 3 "https://www.comchiptech.com/admin/files/product/SS8050-G%20RevA181526.pdf" H 8900 3700 50  0001 C CNN
F 4 "SMC Diode Solutions" H 8900 3700 50  0001 C CNN "Manufacturer"
F 5 "SD103BWSA" H 8900 3700 50  0001 C CNN "Part-No."
	1    8900 3700
	1    0    0    -1  
$EndComp
$Comp
L Device:C C3
U 1 1 60D211FE
P 8050 4800
F 0 "C3" H 8165 4846 50  0000 L CNN
F 1 "1.5n" H 8165 4755 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 8088 4650 50  0001 C CNN
F 3 "https://www.we-online.de/katalog/datasheet/885012206084.pdf" H 8050 4800 50  0001 C CNN
F 4 "TDK Corporation" H 8050 4800 50  0001 C CNN "Manufacturer"
F 5 "C3216X5R1V226M160AC" H 8050 4800 50  0001 C CNN "Part-No."
	1    8050 4800
	1    0    0    -1  
$EndComp
$Comp
L Device:C C5
U 1 1 60D2533E
P 9250 4800
F 0 "C5" H 9365 4846 50  0000 L CNN
F 1 "100u" H 9365 4755 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 9288 4650 50  0001 C CNN
F 3 "https://product.tdk.com/en/system/files?file=dam/doc/product/capacitor/ceramic/mlcc/catalog/mlcc_commercial_general_en.pdf" H 9250 4800 50  0001 C CNN
F 4 "TDK Corporation" H 9250 4800 50  0001 C CNN "Manufacturer"
F 5 "C3216X5R1A107M160AC" H 9250 4800 50  0001 C CNN "Part-No."
	1    9250 4800
	1    0    0    -1  
$EndComp
$Comp
L Device:D D1
U 1 1 60D62CCC
P 8650 4800
F 0 "D1" V 8604 4880 50  0000 L CNN
F 1 "40V 5A" V 8695 4880 50  0000 L CNN
F 2 "Diode_SMD:D_2114_3652Metric_Pad1.85x3.75mm_HandSolder" H 8650 4800 50  0001 C CNN
F 3 "https://datasheets.avx.com/schottky.pdf" H 8650 4800 50  0001 C CNN
F 4 " Kyocera AVX " H 8650 4800 50  0001 C CNN "Manufacturer"
F 5 "SD2114S040S5R0" H 8650 4800 50  0001 C CNN "Part-No."
	1    8650 4800
	0    1    1    0   
$EndComp
$Comp
L Device:L L2
U 1 1 60C6A253
P 8950 4200
F 0 "L2" V 9140 4200 50  0000 C CNN
F 1 "15u" V 9049 4200 50  0000 C CNN
F 2 "Inductor_SMD:L_Vishay_IHLP-4040" H 8950 4200 50  0001 C CNN
F 3 "https://www.mouser.de/datasheet/2/427/lp40dz5a-1762293.pdf" H 8950 4200 50  0001 C CNN
F 4 " Vishay / Dale " H 8950 4200 50  0001 C CNN "Manufacturer"
F 5 "IHLP4040DZER150M5A" H 8950 4200 50  0001 C CNN "Part-No."
	1    8950 4200
	0    -1   -1   0   
$EndComp
$Comp
L Device:C C4
U 1 1 60D19B44
P 8650 3950
F 0 "C4" H 8400 4000 50  0000 L CNN
F 1 "270n" H 8300 3900 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 8688 3800 50  0001 C CNN
F 3 "https://api.kemet.com/component-edge/download/specsheet/C0805R274K5RACT500.pdf" H 8650 3950 50  0001 C CNN
F 4 "KEMET" H 8650 3950 50  0001 C CNN "Manufacturer"
F 5 "C0805C274K5RACTU" H 8650 3950 50  0001 C CNN "Part-No."
	1    8650 3950
	1    0    0    -1  
$EndComp
$Comp
L Device:L L1
U 1 1 60C698F7
P 8000 1500
F 0 "L1" V 8190 1500 50  0000 C CNN
F 1 "6.8u" V 8099 1500 50  0000 C CNN
F 2 "Inductor_SMD:L_Coilcraft_XxL4040" H 8000 1500 50  0001 C CNN
F 3 "https://www.mouser.de/datasheet/2/597/xal4000-270751.pdf" H 8000 1500 50  0001 C CNN
F 4 "Coilcraft" H 8000 1500 50  0001 C CNN "Manufacturer"
F 5 "XAL4030-682MEC " H 8000 1500 50  0001 C CNN "Part-No."
	1    8000 1500
	0    -1   -1   0   
$EndComp
$Comp
L Device:Q_PMOS_GSD Q1
U 1 1 62648C22
P 3150 1700
F 0 "Q1" H 3354 1654 50  0000 L CNN
F 1 "PMOS_GSD-TSM260P02CX RFG " H 3354 1745 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23_Handsoldering" H 3350 1800 50  0001 C CNN
F 3 "https://www.mouser.de/datasheet/2/395/TSM260P02_D1811-1918704.pdf" H 3150 1700 50  0001 C CNN
F 4 "Taiwan Semiconductor " H 3150 1700 50  0001 C CNN "Manufacturer"
F 5 "TSM260P02CX RFG " H 3150 1700 50  0001 C CNN "Part-No."
	1    3150 1700
	1    0    0    1   
$EndComp
Wire Wire Line
	4950 1800 4950 2550
$Comp
L power:GND #PWR06
U 1 1 60CDABA5
P 4950 2550
F 0 "#PWR06" H 4950 2300 50  0001 C CNN
F 1 "GND" H 4955 2377 50  0000 C CNN
F 2 "" H 4950 2550 50  0001 C CNN
F 3 "" H 4950 2550 50  0001 C CNN
	1    4950 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	4950 1800 5000 1800
$Comp
L power:GND #PWR07
U 1 1 62600CF4
P 6200 2550
F 0 "#PWR07" H 6200 2300 50  0001 C CNN
F 1 "GND" H 6205 2377 50  0000 C CNN
F 2 "" H 6200 2550 50  0001 C CNN
F 3 "" H 6200 2550 50  0001 C CNN
	1    6200 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	6200 2300 6200 2550
Wire Wire Line
	7500 1800 7500 2550
$Comp
L power:GND #PWR08
U 1 1 6260344D
P 7500 2550
F 0 "#PWR08" H 7500 2300 50  0001 C CNN
F 1 "GND" H 7505 2377 50  0000 C CNN
F 2 "" H 7500 2550 50  0001 C CNN
F 3 "" H 7500 2550 50  0001 C CNN
	1    7500 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	7400 1800 7500 1800
$Comp
L Device:C C6
U 1 1 62608AD6
P 9400 2150
F 0 "C6" H 9515 2196 50  0000 L CNN
F 1 "10u" H 9515 2105 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 9438 2000 50  0001 C CNN
F 3 "https://product.tdk.com/en/system/files?file=dam/doc/product/capacitor/ceramic/mlcc/catalog/mlcc_commercial_general_en.pdf" H 9400 2150 50  0001 C CNN
F 4 "TDK Corporation" H 9400 2150 50  0001 C CNN "Manufacturer"
F 5 "C2012X5R1V106M085AC" H 9400 2150 50  0001 C CNN "Part-No."
	1    9400 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	4650 2000 4650 1650
Wire Wire Line
	4650 1350 5000 1350
Connection ~ 4650 2000
Wire Wire Line
	5000 1500 4650 1500
Connection ~ 4650 1500
Wire Wire Line
	4650 1500 4650 1350
Wire Wire Line
	5000 1650 4650 1650
Connection ~ 4650 1650
Wire Wire Line
	4650 1650 4650 1500
Wire Wire Line
	7400 1500 7850 1500
$Comp
L Device:R R3
U 1 1 6262337C
P 6200 850
F 0 "R3" V 5993 850 50  0000 C CNN
F 1 "10k" V 6084 850 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 6130 850 50  0001 C CNN
F 3 "~" H 6200 850 50  0001 C CNN
F 4 "TE Connectivity Passive Product" H 6200 850 50  0001 C CNN "Manufacturer"
F 5 "CRGCQ0603J10K" H 6200 850 50  0001 C CNN "Part-No."
	1    6200 850 
	0    1    1    0   
$EndComp
Wire Wire Line
	7400 1350 7500 1350
Wire Wire Line
	7500 1350 7500 850 
Wire Wire Line
	7500 850  6350 850 
Wire Wire Line
	6050 850  4650 850 
Wire Wire Line
	4650 850  4650 1350
Connection ~ 4650 1350
Wire Wire Line
	7400 1650 8500 1650
Wire Wire Line
	8500 1650 8500 1500
Connection ~ 8500 1500
Wire Wire Line
	8500 1500 8150 1500
$Comp
L 2022-04-19_08-29-50:ADP2370ACPZ-3.3-R7 U2
U 1 1 625EC3B8
P 5000 1400
F 0 "U2" H 6200 1787 60  0000 C CNN
F 1 "ADP2370ACPZ-3.3-R7" H 6200 1681 60  0000 C CNN
F 2 "footprints:DFN300X300X80-9N_thermal" H 6200 1640 60  0001 C CNN
F 3 "https://www.analog.com/media/en/technical-documentation/data-sheets/ADP2370_2371.pdf" H 6200 1681 60  0001 C CNN
F 4 "Analog Device" H 5000 1400 50  0001 C CNN "Manufacturer"
F 5 "ADP2371ACPZ-3.3-R7" H 5000 1400 50  0001 C CNN "Part-No."
	1    5000 1400
	1    0    0    -1  
$EndComp
Wire Wire Line
	2350 1700 2950 1700
Wire Wire Line
	3950 3450 8050 3450
Wire Wire Line
	7850 4300 8050 4300
Connection ~ 8050 4300
Wire Wire Line
	8050 4300 8050 4400
Connection ~ 8650 3700
Wire Wire Line
	4450 3700 8650 3700
$Comp
L power:+5V #PWR?
U 1 1 62EA39DD
P 3600 3500
F 0 "#PWR?" H 3600 3350 50  0001 C CNN
F 1 "+5V" H 3615 3673 50  0000 C CNN
F 2 "" H 3600 3500 50  0001 C CNN
F 3 "" H 3600 3500 50  0001 C CNN
	1    3600 3500
	1    0    0    -1  
$EndComp
Wire Wire Line
	3600 3500 3600 4400
Wire Wire Line
	3600 4400 4650 4400
$EndSCHEMATC
