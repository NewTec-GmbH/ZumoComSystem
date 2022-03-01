EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 5 7
Title "Zumo Communication System"
Date "2021-08-20"
Rev "V1.0"
Comp "NewTec GmbH"
Comment1 "Schneider, Niklas"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text HLabel 6000 2350 0    50   Output ~ 0
V_LOADING
Text HLabel 3150 3300 2    50   BiDi ~ 0
D-
Text HLabel 3150 3200 2    50   BiDi ~ 0
D+
Wire Wire Line
	2800 3300 3150 3300
Wire Wire Line
	2800 3200 3150 3200
$Comp
L Connector:USB_B_Micro J2
U 1 1 60DEC307
P 2500 3200
F 0 "J2" H 2557 3667 50  0000 C CNN
F 1 "USB_B_Micro" H 2557 3576 50  0000 C CNN
F 2 "footprints:USB_Micro-B_Molex-105133-0001-3D" H 2650 3150 50  0001 C CNN
F 3 "~" H 2650 3150 50  0001 C CNN
	1    2500 3200
	1    0    0    -1  
$EndComp
Wire Wire Line
	2400 3600 2400 3700
Wire Wire Line
	2500 3700 2500 3600
Wire Wire Line
	2450 3700 2450 3800
$Comp
L power:GND #PWR020
U 1 1 60DEDA4E
P 2450 3800
F 0 "#PWR020" H 2450 3550 50  0001 C CNN
F 1 "GND" H 2455 3627 50  0000 C CNN
F 2 "" H 2450 3800 50  0001 C CNN
F 3 "" H 2450 3800 50  0001 C CNN
	1    2450 3800
	1    0    0    -1  
$EndComp
Wire Wire Line
	2400 3700 2450 3700
Connection ~ 2450 3700
Wire Wire Line
	2450 3700 2500 3700
NoConn ~ 2800 3400
$Comp
L LT1374CS8-5PBF:R1218N021A U?
U 1 1 621F5235
P 7300 2350
F 0 "U?" H 7300 2765 50  0000 C CNN
F 1 "R1218N021A" H 7300 2674 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23-6_Handsoldering" H 7700 2700 50  0001 C CNN
F 3 "https://www.nisshinbo-microdevices.co.jp/en/pdf/datasheet/r1218-ea.pdf" H 7700 2700 50  0001 C CNN
	1    7300 2350
	1    0    0    -1  
$EndComp
Wire Wire Line
	7650 2350 8100 2350
Wire Wire Line
	8100 2350 8100 2750
$Comp
L power:GND #PWR?
U 1 1 621F66D3
P 8100 2750
F 0 "#PWR?" H 8100 2500 50  0001 C CNN
F 1 "GND" H 8105 2577 50  0000 C CNN
F 2 "" H 8100 2750 50  0001 C CNN
F 3 "" H 8100 2750 50  0001 C CNN
	1    8100 2750
	1    0    0    -1  
$EndComp
Wire Wire Line
	6950 2350 6250 2350
Wire Wire Line
	6950 2200 5800 2200
Wire Wire Line
	5000 3000 6800 3000
$Comp
L Device:R R?
U 1 1 621FAFF2
P 5650 2200
F 0 "R?" V 5443 2200 50  0000 C CNN
F 1 "10k" V 5534 2200 50  0000 C CNN
F 2 "" V 5580 2200 50  0001 C CNN
F 3 "~" H 5650 2200 50  0001 C CNN
	1    5650 2200
	0    1    1    0   
$EndComp
Wire Wire Line
	5500 2200 5000 2200
$Comp
L Device:R R?
U 1 1 621FB991
P 8500 2500
F 0 "R?" H 8570 2546 50  0000 L CNN
F 1 "10" H 8570 2455 50  0000 L CNN
F 2 "" V 8430 2500 50  0001 C CNN
F 3 "~" H 8500 2500 50  0001 C CNN
	1    8500 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	7650 2200 8500 2200
$Comp
L Device:C C?
U 1 1 621FD3F7
P 7300 3000
F 0 "C?" V 7500 2950 50  0000 L CNN
F 1 "22uF" V 7100 2900 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 7338 2850 50  0001 C CNN
F 3 "https://product.tdk.com/info/en/catalog/datasheets/mlcc_commercial_general_en.pdf?ref_disty=digikey" H 7300 3000 50  0001 C CNN
	1    7300 3000
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6800 2500 6800 3000
Wire Wire Line
	6800 3000 7150 3000
Wire Wire Line
	6800 2500 6950 2500
Wire Wire Line
	7450 3000 7800 3000
Wire Wire Line
	7800 3000 7800 2500
Wire Wire Line
	7800 2500 7650 2500
Wire Wire Line
	8500 2650 8500 2750
$Comp
L power:GND #PWR?
U 1 1 621FE4AA
P 8500 2750
F 0 "#PWR?" H 8500 2500 50  0001 C CNN
F 1 "GND" H 8505 2577 50  0000 C CNN
F 2 "" H 8500 2750 50  0001 C CNN
F 3 "" H 8500 2750 50  0001 C CNN
	1    8500 2750
	1    0    0    -1  
$EndComp
Wire Wire Line
	8500 2200 8500 2350
Text Label 4150 3000 0    50   ~ 0
V_USB_Bat
Wire Wire Line
	2800 3000 5000 3000
Connection ~ 5000 3000
Connection ~ 6800 3000
Wire Wire Line
	5000 2200 5000 3000
$Comp
L Device:C C?
U 1 1 62201332
P 6250 2550
F 0 "C?" H 6365 2596 50  0000 L CNN
F 1 "220n" H 6365 2505 50  0000 L CNN
F 2 "" H 6288 2400 50  0001 C CNN
F 3 "~" H 6250 2550 50  0001 C CNN
	1    6250 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	6250 2700 6250 2750
Wire Wire Line
	6250 2400 6250 2350
Connection ~ 6250 2350
Wire Wire Line
	6250 2350 6000 2350
$Comp
L power:GND #PWR?
U 1 1 62201F1D
P 6250 2750
F 0 "#PWR?" H 6250 2500 50  0001 C CNN
F 1 "GND" H 6255 2577 50  0000 C CNN
F 2 "" H 6250 2750 50  0001 C CNN
F 3 "" H 6250 2750 50  0001 C CNN
	1    6250 2750
	1    0    0    -1  
$EndComp
Text Notes 6950 1750 0    50   ~ 0
V_Loading = 8.5V
$EndSCHEMATC
