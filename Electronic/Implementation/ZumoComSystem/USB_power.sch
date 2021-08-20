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
Text HLabel 2850 1450 2    50   Output ~ 0
V_LOADING
Text HLabel 2850 1750 2    50   BiDi ~ 0
D-
Text HLabel 2850 1650 2    50   BiDi ~ 0
D+
Wire Wire Line
	2300 1750 2850 1750
Wire Wire Line
	2300 1650 2850 1650
$Comp
L Connector:USB_B_Micro J2
U 1 1 60DEC307
P 2000 1650
F 0 "J2" H 2057 2117 50  0000 C CNN
F 1 "USB_B_Micro" H 2057 2026 50  0000 C CNN
F 2 "footprints:USB_Micro-B_Molex-105133-0001-3D" H 2150 1600 50  0001 C CNN
F 3 "~" H 2150 1600 50  0001 C CNN
	1    2000 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	2850 1450 2300 1450
Wire Wire Line
	1900 2050 1900 2150
Wire Wire Line
	2000 2150 2000 2050
Wire Wire Line
	1950 2150 1950 2250
$Comp
L power:GND #PWR020
U 1 1 60DEDA4E
P 1950 2250
F 0 "#PWR020" H 1950 2000 50  0001 C CNN
F 1 "GND" H 1955 2077 50  0000 C CNN
F 2 "" H 1950 2250 50  0001 C CNN
F 3 "" H 1950 2250 50  0001 C CNN
	1    1950 2250
	1    0    0    -1  
$EndComp
Wire Wire Line
	1900 2150 1950 2150
Connection ~ 1950 2150
Wire Wire Line
	1950 2150 2000 2150
NoConn ~ 2300 1850
$EndSCHEMATC
