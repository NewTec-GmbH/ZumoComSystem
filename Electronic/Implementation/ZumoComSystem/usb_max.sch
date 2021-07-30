EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 7
Title "Zumo Communication System"
Date "2021-07-30"
Rev "V1.0"
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
F 1 "USB_A" H 2307 4326 50  0000 C CNN
F 2 "footprints:USB_A_Molex_105057_Vertical_2" H 2400 3900 50  0001 C CNN
F 3 " ~" H 2400 3900 50  0001 C CNN
	1    2250 3950
	1    0    0    -1  
$EndComp
$Comp
L MAX3421EEHJ_T:MAX3421EEHJ+T U3
U 1 1 60C7A47F
P 5350 2950
F 0 "U3" H 5350 4420 50  0000 C CNN
F 1 "MAX3421EEHJ+T" H 5350 4329 50  0000 C CNN
F 2 "QFP50P700X700X120-32N" H 5350 2950 50  0001 L BNN
F 3 "https://eu.mouser.com/datasheet/2/256/MAX3421E-1513231.pdf" H 5350 2950 50  0001 L BNN
F 4 "Maxim Integrated" H 5350 2950 50  0001 L BNN "MF"
F 5 "Ic Usb Periph/Host Cntrl 32tqfp - Max3421eehj+t" H 5350 2950 50  0001 L BNN "DESCRIPTION"
F 6 "MAX3421EEHJ+T" H 5350 2950 50  0001 L BNN "MP"
F 7 "TQFP-32 Maxim" H 5350 2950 50  0001 L BNN "PACKAGE"
F 8 "None" H 5350 2950 50  0001 L BNN "PRICE"
F 9 "Unavailable" H 5350 2950 50  0001 L BNN "AVAILABILITY"
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
	6050 2050 6450 2050
Wire Wire Line
	4650 3650 4250 3650
Wire Wire Line
	6050 3650 6450 3650
Wire Wire Line
	6050 3750 6450 3750
Wire Wire Line
	2550 3950 4650 3950
Wire Wire Line
	2550 4050 4650 4050
Wire Wire Line
	2250 4350 2250 4450
Wire Wire Line
	6050 4250 6150 4250
Wire Wire Line
	6150 4250 6150 4350
Wire Wire Line
	6050 1750 6450 1750
Wire Wire Line
	6450 1750 6450 1650
Wire Wire Line
	4650 1950 4250 1950
$Comp
L power:GND #PWR016
U 1 1 6171550F
P 6150 4350
F 0 "#PWR016" H 6150 4100 50  0001 C CNN
F 1 "GND" H 6155 4177 50  0000 C CNN
F 2 "" H 6150 4350 50  0001 C CNN
F 3 "" H 6150 4350 50  0001 C CNN
	1    6150 4350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR013
U 1 1 617158D8
P 2200 4450
F 0 "#PWR013" H 2200 4200 50  0001 C CNN
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
	2550 3750 2650 3750
Wire Wire Line
	2650 3750 2650 3650
$Comp
L power:+5V #PWR014
U 1 1 61716434
P 2650 3650
F 0 "#PWR014" H 2650 3500 50  0001 C CNN
F 1 "+5V" H 2665 3823 50  0000 C CNN
F 2 "" H 2650 3650 50  0001 C CNN
F 3 "" H 2650 3650 50  0001 C CNN
	1    2650 3650
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR017
U 1 1 61716978
P 6450 1650
F 0 "#PWR017" H 6450 1500 50  0001 C CNN
F 1 "+3.3V" H 6465 1823 50  0000 C CNN
F 2 "" H 6450 1650 50  0001 C CNN
F 3 "" H 6450 1650 50  0001 C CNN
	1    6450 1650
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR015
U 1 1 61716F75
P 4250 1650
F 0 "#PWR015" H 4250 1500 50  0001 C CNN
F 1 "+3.3V" H 4265 1823 50  0000 C CNN
F 2 "" H 4250 1650 50  0001 C CNN
F 3 "" H 4250 1650 50  0001 C CNN
	1    4250 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	4250 1650 4250 1950
NoConn ~ 4650 2150
NoConn ~ 4650 2250
NoConn ~ 4650 2450
NoConn ~ 4650 2550
NoConn ~ 4650 2650
NoConn ~ 4650 2750
NoConn ~ 4650 2850
NoConn ~ 4650 2950
NoConn ~ 4650 3050
NoConn ~ 4650 3150
NoConn ~ 4650 3350
NoConn ~ 4650 3450
NoConn ~ 6050 1950
NoConn ~ 6050 2450
NoConn ~ 6050 2550
NoConn ~ 6050 2650
NoConn ~ 6050 2750
NoConn ~ 6050 2850
NoConn ~ 6050 2950
NoConn ~ 6050 3050
NoConn ~ 6050 3150
$EndSCHEMATC
