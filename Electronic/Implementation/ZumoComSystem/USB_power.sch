EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 5 7
Title "Zumo Communication System"
Date "2022-10-04"
Rev "V1.2"
Comp "NewTec GmbH"
Comment1 "Schneider, Niklas"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text HLabel 4450 3300 2    50   BiDi ~ 0
D-
Text HLabel 4450 3200 2    50   BiDi ~ 0
D+
Wire Wire Line
	2800 3300 3800 3300
Wire Wire Line
	2800 3200 3450 3200
$Comp
L Connector:USB_B_Micro J3
U 1 1 60DEC307
P 2500 3200
F 0 "J3" H 2557 3667 50  0000 C CNN
F 1 "USB_B_Micro" H 2557 3576 50  0000 C CNN
F 2 "footprints:USB_Micro-B_Molex-105133-0001-3D" H 2650 3150 50  0001 C CNN
F 3 "~" H 2650 3150 50  0001 C CNN
F 4 "Molex" H 2500 3200 50  0001 C CNN "Manufacturer"
F 5 "1051330001" H 2500 3200 50  0001 C CNN "Part-No."
	1    2500 3200
	1    0    0    -1  
$EndComp
Wire Wire Line
	2400 3600 2400 3700
Wire Wire Line
	2500 3700 2500 3600
Wire Wire Line
	2450 3700 2450 3950
$Comp
L power:GND #PWR030
U 1 1 60DEDA4E
P 2450 3950
F 0 "#PWR030" H 2450 3700 50  0001 C CNN
F 1 "GND" H 2455 3777 50  0000 C CNN
F 2 "" H 2450 3950 50  0001 C CNN
F 3 "" H 2450 3950 50  0001 C CNN
	1    2450 3950
	1    0    0    -1  
$EndComp
Wire Wire Line
	2400 3700 2450 3700
Connection ~ 2450 3700
Wire Wire Line
	2450 3700 2500 3700
NoConn ~ 2800 3400
$Comp
L power:VBUS #PWR031
U 1 1 6230EF27
P 3150 2700
F 0 "#PWR031" H 3150 2550 50  0001 C CNN
F 1 "VBUS" H 3165 2873 50  0000 C CNN
F 2 "" H 3150 2700 50  0001 C CNN
F 3 "" H 3150 2700 50  0001 C CNN
	1    3150 2700
	1    0    0    -1  
$EndComp
Wire Wire Line
	3150 2700 3150 3000
Wire Wire Line
	2800 3000 3150 3000
Connection ~ 3150 3000
$Comp
L Device:D D5
U 1 1 6235853C
P 3450 3600
F 0 "D5" V 3450 3680 50  0000 L CNN
F 1 "D5V0S1U2WS-7" V 3495 3680 50  0001 L CNN
F 2 "Diode_SMD:D_SOD-323_HandSoldering" H 3450 3600 50  0001 C CNN
F 3 "https://www.diodes.com/assets/Datasheets/D5V0S1U2WS.pdf" H 3450 3600 50  0001 C CNN
F 4 "Diodes Incorporated" H 3450 3600 50  0001 C CNN "Manufacturer"
F 5 "D5V0S1U2WS-7" H 3450 3600 50  0001 C CNN "Part-No."
	1    3450 3600
	0    1    1    0   
$EndComp
$Comp
L Device:D D6
U 1 1 62358EEE
P 3800 3600
F 0 "D6" V 3754 3680 50  0000 L CNN
F 1 "D5V0S1U2WS-7" V 3800 4000 50  0000 L CNN
F 2 "Diode_SMD:D_SOD-323_HandSoldering" H 3800 3600 50  0001 C CNN
F 3 "https://www.diodes.com/assets/Datasheets/D5V0S1U2WS.pdf" H 3800 3600 50  0001 C CNN
F 4 "Diodes Incorporated" H 3800 3600 50  0001 C CNN "Manufacturer"
F 5 "D5V0S1U2WS-7" H 3800 3600 50  0001 C CNN "Part-No."
	1    3800 3600
	0    1    1    0   
$EndComp
Wire Wire Line
	3450 3450 3450 3200
Connection ~ 3450 3200
Wire Wire Line
	3450 3200 4450 3200
Wire Wire Line
	3800 3450 3800 3300
Connection ~ 3800 3300
Wire Wire Line
	3800 3300 4450 3300
$Comp
L Device:D D4
U 1 1 62359ADA
P 3150 3600
F 0 "D4" V 3150 3680 50  0000 L CNN
F 1 "D5V0S1U2WS-7" V 3195 3680 50  0001 L CNN
F 2 "Diode_SMD:D_SOD-323_HandSoldering" H 3150 3600 50  0001 C CNN
F 3 "https://www.diodes.com/assets/Datasheets/D5V0S1U2WS.pdf" H 3150 3600 50  0001 C CNN
F 4 "Diodes Incorporated" H 3150 3600 50  0001 C CNN "Manufacturer"
F 5 "D5V0S1U2WS-7" H 3150 3600 50  0001 C CNN "Part-No."
	1    3150 3600
	0    1    1    0   
$EndComp
Wire Wire Line
	3150 3450 3150 3000
$Comp
L power:GND #PWR032
U 1 1 6235AC4B
P 3450 3950
F 0 "#PWR032" H 3450 3700 50  0001 C CNN
F 1 "GND" H 3455 3777 50  0000 C CNN
F 2 "" H 3450 3950 50  0001 C CNN
F 3 "" H 3450 3950 50  0001 C CNN
	1    3450 3950
	1    0    0    -1  
$EndComp
Wire Wire Line
	3150 3750 3150 3850
Wire Wire Line
	3150 3850 3450 3850
Wire Wire Line
	3800 3850 3800 3750
Wire Wire Line
	3450 3750 3450 3850
Connection ~ 3450 3850
Wire Wire Line
	3450 3850 3800 3850
Wire Wire Line
	3450 3850 3450 3950
$EndSCHEMATC
