EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 7
Title "Zumo Communication System"
Date "2022-05-27"
Rev "V1.1"
Comp "NewTec GmbH"
Comment1 "Schneider, Niklas"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Connector:USB_A J?
U 1 1 60C6499B
P 2250 3950
AR Path="/60C6499B" Ref="J?"  Part="1" 
AR Path="/60C500E6/60C6499B" Ref="J1"  Part="1" 
F 0 "J1" H 2307 4417 50  0000 C CNN
F 1 "USB_A_Molex_105057" H 2307 4326 50  0000 C CNN
F 2 "footprints:USB_A_Molex_105057_Vertical_2" H 2400 3900 50  0001 C CNN
F 3 "https://www.molex.com/pdm_docs/ps/PS-105057-001.pdf" H 2400 3900 50  0001 C CNN
F 4 "Molex" H 2250 3950 50  0001 C CNN "Manufacturer"
F 5 "1050570001" H 2250 3950 50  0001 C CNN "Part-No."
	1    2250 3950
	1    0    0    -1  
$EndComp
$Comp
L MAX3421EEHJ_T:MAX3421EEHJ+T U3
U 1 1 60C7A47F
P 5350 2950
F 0 "U3" H 5350 4420 50  0000 C CNN
F 1 "MAX3421EEHJ+T" H 5350 4329 50  0000 C CNN
F 2 "footprints:QFN50P500X500X80-33N_Generell" H 5350 2950 50  0001 L BNN
F 3 "https://eu.mouser.com/datasheet/2/256/MAX3421E-1513231.pdf" H 5350 2950 50  0001 L BNN
F 4 "Maxim Integrated" H 5350 2950 50  0001 C CNN "Manufacturer"
F 5 "MAX3421EEHJ+T" H 5350 2950 50  0001 C CNN "Part-No."
	1    5350 2950
	1    0    0    -1  
$EndComp
Text HLabel 4250 2050 0    50   Input ~ 0
SS
Text HLabel 6450 2050 2    50   Output ~ 0
INT
Text HLabel 4250 3650 0    50   Input ~ 0
SCK
Text HLabel 6450 3650 2    50   Output ~ 0
MISO
Text HLabel 6450 3750 2    50   BiDi ~ 0
MOSI
Wire Wire Line
	4650 2050 4250 2050
Wire Wire Line
	6050 2050 6250 2050
Wire Wire Line
	4650 3650 4250 3650
Wire Wire Line
	6050 3650 6450 3650
Wire Wire Line
	6050 3750 6450 3750
Wire Wire Line
	2250 4350 2250 4450
Wire Wire Line
	6050 4250 6150 4250
Wire Wire Line
	6150 4250 6150 4350
Wire Wire Line
	6050 1750 6250 1750
Wire Wire Line
	6250 1750 6250 1650
$Comp
L power:GND #PWR022
U 1 1 6171550F
P 6150 4350
F 0 "#PWR022" H 6150 4100 50  0001 C CNN
F 1 "GND" H 6155 4177 50  0000 C CNN
F 2 "" H 6150 4350 50  0001 C CNN
F 3 "" H 6150 4350 50  0001 C CNN
	1    6150 4350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR016
U 1 1 617158D8
P 2200 4450
F 0 "#PWR016" H 2200 4200 50  0001 C CNN
F 1 "GND" H 2205 4277 50  0000 C CNN
F 2 "" H 2200 4450 50  0001 C CNN
F 3 "" H 2200 4450 50  0001 C CNN
	1    2200 4450
	1    0    0    -1  
$EndComp
Wire Wire Line
	2150 4350 2150 4450
Wire Wire Line
	2150 4450 2200 4450
Connection ~ 2200 4450
Wire Wire Line
	2200 4450 2250 4450
Wire Wire Line
	2550 3750 2900 3750
Wire Wire Line
	2900 3750 2900 3650
$Comp
L power:+5V #PWR019
U 1 1 61716434
P 2900 3650
F 0 "#PWR019" H 2900 3500 50  0001 C CNN
F 1 "+5V" H 2915 3823 50  0000 C CNN
F 2 "" H 2900 3650 50  0001 C CNN
F 3 "" H 2900 3650 50  0001 C CNN
	1    2900 3650
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR023
U 1 1 61716978
P 6250 1650
F 0 "#PWR023" H 6250 1500 50  0001 C CNN
F 1 "+3.3V" H 6265 1823 50  0000 C CNN
F 2 "" H 6250 1650 50  0001 C CNN
F 3 "" H 6250 1650 50  0001 C CNN
	1    6250 1650
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR021
U 1 1 61716F75
P 4400 1650
F 0 "#PWR021" H 4400 1500 50  0001 C CNN
F 1 "+3.3V" H 4415 1823 50  0000 C CNN
F 2 "" H 4400 1650 50  0001 C CNN
F 3 "" H 4400 1650 50  0001 C CNN
	1    4400 1650
	1    0    0    -1  
$EndComp
NoConn ~ 4650 2250
NoConn ~ 4650 2450
NoConn ~ 4650 2550
NoConn ~ 4650 2650
NoConn ~ 4650 2750
NoConn ~ 4650 2850
NoConn ~ 4650 2950
NoConn ~ 4650 3050
NoConn ~ 4650 3150
NoConn ~ 6050 1950
NoConn ~ 6050 2450
NoConn ~ 6050 2550
NoConn ~ 6050 2650
NoConn ~ 6050 2750
NoConn ~ 6050 2850
NoConn ~ 6050 2950
NoConn ~ 6050 3050
NoConn ~ 6050 3150
$Comp
L Device:C C7
U 1 1 623D76FD
P 1550 6350
F 0 "C7" H 1665 6396 50  0000 L CNN
F 1 "18p" H 1665 6305 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 1588 6200 50  0001 C CNN
F 3 "~" H 1550 6350 50  0001 C CNN
F 4 "KEMET" H 1550 6350 50  0001 C CNN "Manufacturer"
F 5 "C0603C180J5GAC7867" H 1550 6350 50  0001 C CNN "Part-No."
	1    1550 6350
	1    0    0    -1  
$EndComp
$Comp
L Device:C C8
U 1 1 623D7CDF
P 3000 6350
F 0 "C8" H 3115 6396 50  0000 L CNN
F 1 "18p" H 3115 6305 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 3038 6200 50  0001 C CNN
F 3 "~" H 3000 6350 50  0001 C CNN
F 4 "KEMET" H 3000 6350 50  0001 C CNN "Manufacturer"
F 5 "C0603C180J5GAC7867" H 3000 6350 50  0001 C CNN "Part-No."
	1    3000 6350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR015
U 1 1 623D7F8C
P 1550 6500
F 0 "#PWR015" H 1550 6250 50  0001 C CNN
F 1 "GND" H 1555 6327 50  0000 C CNN
F 2 "" H 1550 6500 50  0001 C CNN
F 3 "" H 1550 6500 50  0001 C CNN
	1    1550 6500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR020
U 1 1 623D8337
P 3000 6500
F 0 "#PWR020" H 3000 6250 50  0001 C CNN
F 1 "GND" H 3005 6327 50  0000 C CNN
F 2 "" H 3000 6500 50  0001 C CNN
F 3 "" H 3000 6500 50  0001 C CNN
	1    3000 6500
	1    0    0    -1  
$EndComp
Wire Wire Line
	3000 5950 3000 6200
Wire Wire Line
	1550 5950 2100 5950
Wire Wire Line
	2400 5950 3000 5950
Wire Wire Line
	1550 5300 3500 5300
Text Label 3500 5300 2    50   ~ 0
XO
Text Label 3500 5400 2    50   ~ 0
XI
Wire Wire Line
	3000 5950 3000 5400
Wire Wire Line
	3000 5400 3500 5400
Connection ~ 3000 5950
Text Label 2850 3950 0    50   ~ 0
D+
Text Label 2850 4050 0    50   ~ 0
D-
Text Label 4050 3350 0    50   ~ 0
XI
Wire Wire Line
	4650 3350 4050 3350
Text Label 4050 3450 0    50   ~ 0
XO
Wire Wire Line
	4050 3450 4650 3450
Wire Wire Line
	1550 5300 1550 5950
Wire Wire Line
	2250 5750 2250 5500
Wire Wire Line
	2250 5500 2650 5500
$Comp
L power:GND #PWR018
U 1 1 623F4A4F
P 2650 5500
F 0 "#PWR018" H 2650 5250 50  0001 C CNN
F 1 "GND" H 2655 5327 50  0000 C CNN
F 2 "" H 2650 5500 50  0001 C CNN
F 3 "" H 2650 5500 50  0001 C CNN
	1    2650 5500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR017
U 1 1 623F4CEC
P 2250 6500
F 0 "#PWR017" H 2250 6250 50  0001 C CNN
F 1 "GND" H 2255 6327 50  0000 C CNN
F 2 "" H 2250 6500 50  0001 C CNN
F 3 "" H 2250 6500 50  0001 C CNN
	1    2250 6500
	1    0    0    -1  
$EndComp
Wire Wire Line
	2250 6150 2250 6500
Connection ~ 1550 5950
Wire Wire Line
	1550 5950 1550 6200
$Comp
L Device:Crystal_GND24 Y1
U 1 1 623EF4A9
P 2250 5950
F 0 "Y1" H 2444 5996 50  0000 L CNN
F 1 "FL1200112_12MHz" H 1900 6700 50  0000 L CNN
F 2 "Crystal:Crystal_SMD_3225-4Pin_3.2x2.5mm_HandSoldering" H 2250 5950 50  0001 C CNN
F 3 "https://www.diodes.com/assets/Datasheets/FL.pdf" H 2250 5950 50  0001 C CNN
F 4 "Diodes Incorporated" H 2250 5950 50  0001 C CNN "Manufacturer"
F 5 "FL1200112" H 2250 5950 50  0001 C CNN "Part-No."
	1    2250 5950
	1    0    0    -1  
$EndComp
Wire Wire Line
	4650 2150 4400 2150
$Comp
L Device:R R6
U 1 1 6256E0B6
P 6250 1900
F 0 "R6" H 6320 1946 50  0000 L CNN
F 1 "2.2k" H 6320 1855 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 6180 1900 50  0001 C CNN
F 3 "~" H 6250 1900 50  0001 C CNN
F 4 "TE Connectivity Passive Product" H 6250 1900 50  0001 C CNN "Manufacturer"
F 5 "CRGCQ0603J2K2" H 6250 1900 50  0001 C CNN "Part-No."
	1    6250 1900
	1    0    0    -1  
$EndComp
Connection ~ 6250 1750
Connection ~ 6250 2050
Wire Wire Line
	6250 2050 6450 2050
Text HLabel 3550 1950 0    50   BiDi ~ 0
ESP_EN
Wire Wire Line
	4650 1950 4100 1950
$Comp
L Device:R R5
U 1 1 6256E70A
P 4100 1800
F 0 "R5" H 4170 1846 50  0000 L CNN
F 1 "DNP" H 4170 1755 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 4030 1800 50  0001 C CNN
F 3 "~" H 4100 1800 50  0001 C CNN
F 4 "-" H 4100 1800 50  0001 C CNN "Manufacturer"
F 5 "-" H 4100 1800 50  0001 C CNN "Part-No."
	1    4100 1800
	1    0    0    -1  
$EndComp
Connection ~ 4100 1950
Wire Wire Line
	4100 1650 4400 1650
Wire Wire Line
	3550 1950 3700 1950
Wire Wire Line
	4400 2150 4400 1650
Connection ~ 4400 1650
$Comp
L Device:R R4
U 1 1 62574913
P 3850 1950
F 0 "R4" V 3643 1950 50  0000 C CNN
F 1 "0" V 3734 1950 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 3780 1950 50  0001 C CNN
F 3 "~" H 3850 1950 50  0001 C CNN
F 4 "YAGEO" H 3850 1950 50  0001 C CNN "Manufacturer"
F 5 "RC0603FR-070RL" H 3850 1950 50  0001 C CNN "Part-No."
	1    3850 1950
	0    1    1    0   
$EndComp
Wire Wire Line
	4000 1950 4100 1950
$Comp
L Connector:TestPoint_2Pole TP?
U 1 1 62EEE2C4
P 3300 4000
AR Path="/60C4E4D0/62EEE2C4" Ref="TP?"  Part="1" 
AR Path="/60C500E6/62EEE2C4" Ref="TP1"  Part="1" 
F 0 "TP1" V 3254 4058 50  0000 L CNN
F 1 "TP_2P" V 3345 4058 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 3300 4000 50  0001 C CNN
F 3 "~" H 3300 4000 50  0001 C CNN
	1    3300 4000
	0    1    1    0   
$EndComp
Wire Wire Line
	2550 3950 3200 3950
Wire Wire Line
	3200 3800 3300 3800
Wire Wire Line
	4050 3800 4050 3950
Wire Wire Line
	4050 3950 4650 3950
Connection ~ 3300 3800
Wire Wire Line
	3300 3800 3500 3800
Wire Wire Line
	3200 3800 3200 3950
Wire Wire Line
	2550 4050 3200 4050
Wire Wire Line
	3200 4200 3300 4200
Wire Wire Line
	4050 4200 4050 4050
Wire Wire Line
	4050 4050 4650 4050
Wire Wire Line
	4050 4200 3800 4200
Connection ~ 3300 4200
Wire Wire Line
	3200 4050 3200 4200
Text Label 4400 3950 0    50   ~ 0
DR+
Text Label 4400 4050 0    50   ~ 0
DR-
$Comp
L Device:R R2
U 1 1 62EF4C70
P 3650 3800
F 0 "R2" V 3443 3800 50  0000 C CNN
F 1 "22" V 3534 3800 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 3580 3800 50  0001 C CNN
F 3 "~" H 3650 3800 50  0001 C CNN
F 4 "" H 3650 3800 50  0001 C CNN "Manufacturer"
F 5 "" H 3650 3800 50  0001 C CNN "Part-No."
	1    3650 3800
	0    1    1    0   
$EndComp
Wire Wire Line
	3800 3800 4050 3800
$Comp
L Device:R R3
U 1 1 62EF55BF
P 3650 4200
F 0 "R3" V 3443 4200 50  0000 C CNN
F 1 "22" V 3534 4200 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 3580 4200 50  0001 C CNN
F 3 "~" H 3650 4200 50  0001 C CNN
F 4 "" H 3650 4200 50  0001 C CNN "Manufacturer"
F 5 "" H 3650 4200 50  0001 C CNN "Part-No."
	1    3650 4200
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3500 4200 3300 4200
$EndSCHEMATC
