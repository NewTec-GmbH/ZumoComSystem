EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 7 7
Title "Zumo Communication System"
Date "2022-08-04"
Rev "V1.1"
Comp "NewTec GmbH"
Comment1 "Schneider, Niklas"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text Notes 9500 750  0    50   ~ 0
Display
Wire Notes Line
	9500 2400 9500 750 
Wire Notes Line
	9500 750  10900 750 
$Comp
L Connector_Generic:Conn_02x13_Odd_Even J?
U 1 1 60C60623
P 4900 4100
AR Path="/60C60623" Ref="J?"  Part="1" 
AR Path="/60C50401/60C60623" Ref="J4"  Part="1" 
F 0 "J4" H 4950 4917 50  0000 C CNN
F 1 "Pin-Header 2x13" H 4950 4826 50  0000 C CNN
F 2 "footprints:PinHeader_2x13_SMD_bottom" H 4900 4100 50  0001 C CNN
F 3 "~" H 4900 4100 50  0001 C CNN
F 4 "Samtec" H 4900 4100 50  0001 C CNN "Manufacturer"
F 5 "TSM-113-01-T-DV" H 4900 4100 50  0001 C CNN "Part-No."
	1    4900 4100
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_02x13_Odd_Even J?
U 1 1 60C60629
P 9200 4100
AR Path="/60C60629" Ref="J?"  Part="1" 
AR Path="/60C50401/60C60629" Ref="J6"  Part="1" 
F 0 "J6" H 9250 4917 50  0000 C CNN
F 1 "Pin-Header 2x13" H 9250 4826 50  0000 C CNN
F 2 "footprints:PinHeader_2x13_SMD_bottom" H 9200 4100 50  0001 C CNN
F 3 "~" H 9200 4100 50  0001 C CNN
F 4 "Samtec" H 9200 4100 50  0001 C CNN "Manufacturer"
F 5 "TSM-113-01-T-DV" H 9200 4100 50  0001 C CNN "Part-No."
	1    9200 4100
	1    0    0    -1  
$EndComp
Wire Wire Line
	3000 6900 3250 6900
Wire Wire Line
	3250 6900 3250 6500
Text HLabel 1400 6550 0    50   Input ~ 0
nRGB_LED_R
Text HLabel 1400 6900 0    50   Input ~ 0
nRGB_LED_G
Text HLabel 1400 7250 0    50   Input ~ 0
nRGB_LED_B
$Comp
L Device:R R28
U 1 1 61002789
P 2100 6900
F 0 "R28" V 1893 6900 50  0000 C CNN
F 1 "150" V 1984 6900 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 2030 6900 50  0001 C CNN
F 3 "~" H 2100 6900 50  0001 C CNN
F 4 "YAGEO" H 2100 6900 50  0001 C CNN "Manufacturer"
F 5 "RC0603FR-07150RL" H 2100 6900 50  0001 C CNN "Part-No."
	1    2100 6900
	0    1    1    0   
$EndComp
$Comp
L Device:R R29
U 1 1 61002936
P 2100 7250
F 0 "R29" V 1893 7250 50  0000 C CNN
F 1 "150" V 1984 7250 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 2030 7250 50  0001 C CNN
F 3 "~" H 2100 7250 50  0001 C CNN
F 4 "YAGEO" H 2100 7250 50  0001 C CNN "Manufacturer"
F 5 "RC0603FR-07150RL" H 2100 7250 50  0001 C CNN "Part-No."
	1    2100 7250
	0    1    1    0   
$EndComp
Wire Wire Line
	2250 6550 2450 6550
Wire Wire Line
	2450 6550 2450 6700
Wire Wire Line
	2450 6700 2600 6700
Wire Wire Line
	2450 7250 2450 7100
Wire Wire Line
	2450 7100 2600 7100
Wire Wire Line
	2250 7250 2450 7250
Text HLabel 1400 5750 0    50   Input ~ 0
nLED_C
$Comp
L power:GND #PWR062
U 1 1 6105FDAD
P 4450 3700
F 0 "#PWR062" H 4450 3450 50  0001 C CNN
F 1 "GND" H 4455 3527 50  0000 C CNN
F 2 "" H 4450 3700 50  0001 C CNN
F 3 "" H 4450 3700 50  0001 C CNN
	1    4450 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	4450 3600 4450 3700
Text Label 8550 4700 0    50   ~ 0
nRESET
$Comp
L power:GND #PWR065
U 1 1 61078CFA
P 5450 3700
F 0 "#PWR065" H 5450 3450 50  0001 C CNN
F 1 "GND" H 5455 3527 50  0000 C CNN
F 2 "" H 5450 3700 50  0001 C CNN
F 3 "" H 5450 3700 50  0001 C CNN
	1    5450 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	5450 3600 5450 3700
Wire Wire Line
	8800 1700 8950 1700
Wire Wire Line
	8200 1650 8050 1650
Wire Wire Line
	8200 1550 8050 1550
Wire Wire Line
	8050 1650 8050 1750
Wire Wire Line
	8050 1750 8200 1750
Connection ~ 8050 1650
Wire Wire Line
	8050 1550 8050 1650
$Comp
L power:GND #PWR075
U 1 1 61084EB9
P 7950 1650
F 0 "#PWR075" H 7950 1400 50  0001 C CNN
F 1 "GND" H 7955 1477 50  0000 C CNN
F 2 "" H 7950 1650 50  0001 C CNN
F 3 "" H 7950 1650 50  0001 C CNN
	1    7950 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	8050 1650 7950 1650
$Comp
L power:GND #PWR077
U 1 1 6108ED41
P 8950 1700
F 0 "#PWR077" H 8950 1450 50  0001 C CNN
F 1 "GND" H 8955 1527 50  0000 C CNN
F 2 "" H 8950 1700 50  0001 C CNN
F 3 "" H 8950 1700 50  0001 C CNN
	1    8950 1700
	1    0    0    -1  
$EndComp
Wire Wire Line
	8700 1850 8750 1850
Wire Wire Line
	8750 1850 8750 2050
Wire Wire Line
	8750 2050 10600 2050
Wire Wire Line
	10600 2050 10600 1850
Wire Wire Line
	10600 1850 10450 1850
Wire Notes Line
	10900 2400 9500 2400
$Comp
L Connector_Generic:Conn_02x07_Odd_Even J?
U 1 1 60C5C844
P 8400 1650
AR Path="/60C5C844" Ref="J?"  Part="1" 
AR Path="/60C50401/60C5C844" Ref="J5"  Part="1" 
F 0 "J5" H 8500 2100 50  0000 R CNN
F 1 "Conn_02x07_Odd_Even" H 8850 2550 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x07_P2.54mm_Vertical" H 8400 1650 50  0001 C CNN
F 3 "~" H 8400 1650 50  0001 C CNN
F 4 "Samtec" H 8400 1650 50  0001 C CNN "Manufacturer"
F 5 "TSW-107-07-T-D" H 8400 1650 50  0001 C CNN "Part-No."
	1    8400 1650
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_02x07_Odd_Even J?
U 1 1 60C5C83E
P 10150 1650
AR Path="/60C5C83E" Ref="J?"  Part="1" 
AR Path="/60C50401/60C5C83E" Ref="J7"  Part="1" 
F 0 "J7" H 10250 2100 50  0000 R CNN
F 1 "Conn_02x07_Odd_Even" H 10900 2450 50  0000 R CNN
F 2 "footprints:PinSocket_2x07_P2.54mm_Vertical_SMD" H 10150 1650 50  0001 C CNN
F 3 "~" H 10150 1650 50  0001 C CNN
F 4 "Samtec" H 10150 1650 50  0001 C CNN "Manufacturer"
F 5 "SSM-107-T-DV-P" H 10150 1650 50  0001 C CNN "Part-No."
	1    10150 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	8700 1750 8800 1750
Wire Wire Line
	8800 1650 8800 1700
Connection ~ 8800 1700
Wire Wire Line
	8800 1700 8800 1750
Wire Wire Line
	8700 1650 8800 1650
Wire Notes Line
	10900 750  10900 2400
Wire Wire Line
	8200 1950 8100 1950
Wire Wire Line
	8100 1950 8100 2200
Wire Wire Line
	8100 2200 9900 2200
Wire Wire Line
	9900 2200 9900 1950
Wire Wire Line
	9900 1950 9950 1950
Wire Wire Line
	8050 1850 8050 2250
Wire Wire Line
	8050 2250 9850 2250
Wire Wire Line
	9850 2250 9850 1850
Wire Wire Line
	9850 1850 9950 1850
Wire Wire Line
	8050 1850 8200 1850
Wire Wire Line
	9950 1650 9800 1650
Wire Wire Line
	9950 1550 9800 1550
Wire Wire Line
	9800 1650 9800 1750
Wire Wire Line
	9800 1750 9950 1750
Connection ~ 9800 1650
Wire Wire Line
	9800 1550 9800 1650
$Comp
L power:GND #PWR078
U 1 1 610D809A
P 9700 1650
F 0 "#PWR078" H 9700 1400 50  0001 C CNN
F 1 "GND" H 9705 1477 50  0000 C CNN
F 2 "" H 9700 1650 50  0001 C CNN
F 3 "" H 9700 1650 50  0001 C CNN
	1    9700 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	9800 1650 9700 1650
Wire Wire Line
	10550 1700 10700 1700
$Comp
L power:GND #PWR081
U 1 1 610E5EFF
P 10700 1700
F 0 "#PWR081" H 10700 1450 50  0001 C CNN
F 1 "GND" H 10705 1527 50  0000 C CNN
F 2 "" H 10700 1700 50  0001 C CNN
F 3 "" H 10700 1700 50  0001 C CNN
	1    10700 1700
	1    0    0    -1  
$EndComp
Wire Wire Line
	10450 1750 10550 1750
Wire Wire Line
	10550 1650 10550 1700
Connection ~ 10550 1700
Wire Wire Line
	10550 1700 10550 1750
Wire Wire Line
	10450 1650 10550 1650
Wire Wire Line
	8700 1950 8700 2100
Wire Wire Line
	10550 2100 10550 1950
Wire Wire Line
	8700 2100 10550 2100
Wire Wire Line
	10550 1950 10450 1950
Wire Wire Line
	8200 1350 8200 900 
Wire Wire Line
	8200 900  9950 900 
Wire Wire Line
	9950 900  9950 1350
Wire Wire Line
	8200 1450 8100 1450
Wire Wire Line
	8100 1450 8100 850 
Wire Wire Line
	8100 850  9850 850 
Wire Wire Line
	9850 850  9850 1450
Wire Wire Line
	9850 1450 9950 1450
Wire Wire Line
	8700 1350 8700 1000
Wire Wire Line
	8700 1000 10500 1000
Wire Wire Line
	10500 1000 10500 1350
Wire Wire Line
	10500 1350 10450 1350
Wire Wire Line
	8700 1450 8750 1450
Wire Wire Line
	8750 1450 8750 1050
Wire Wire Line
	8750 1050 10550 1050
Wire Wire Line
	10550 1050 10550 1450
Wire Wire Line
	10550 1450 10450 1450
Wire Wire Line
	8700 1550 8800 1550
Wire Wire Line
	8800 1550 8800 1100
Wire Wire Line
	8800 1100 10600 1100
Wire Wire Line
	10600 1100 10600 1550
Wire Wire Line
	10600 1550 10450 1550
Text Label 3000 5300 2    50   ~ 0
LED_C
Text Label 9950 4300 2    50   ~ 0
LED_C
Wire Wire Line
	9950 4300 9500 4300
$Comp
L power:+3.3V #PWR073
U 1 1 61030266
P 7900 4150
F 0 "#PWR073" H 7900 4000 50  0001 C CNN
F 1 "+3.3V" H 7915 4323 50  0000 C CNN
F 2 "" H 7900 4150 50  0001 C CNN
F 3 "" H 7900 4150 50  0001 C CNN
	1    7900 4150
	1    0    0    -1  
$EndComp
Wire Wire Line
	7900 4250 7900 4150
$Comp
L Device:R R35
U 1 1 610325C6
P 7900 4400
F 0 "R35" H 7970 4446 50  0000 L CNN
F 1 "10k" H 7970 4355 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 7830 4400 50  0001 C CNN
F 3 "~" H 7900 4400 50  0001 C CNN
F 4 "TE Connectivity Passive Product" H 7900 4400 50  0001 C CNN "Manufacturer"
F 5 "CRGCQ0603J10K" H 7900 4400 50  0001 C CNN "Part-No."
	1    7900 4400
	1    0    0    -1  
$EndComp
Text Label 9950 4400 2    50   ~ 0
LED_A
Wire Wire Line
	9500 4400 9950 4400
$Comp
L power:GND #PWR079
U 1 1 614F0444
P 9750 3600
F 0 "#PWR079" H 9750 3350 50  0001 C CNN
F 1 "GND" H 9755 3427 50  0000 C CNN
F 2 "" H 9750 3600 50  0001 C CNN
F 3 "" H 9750 3600 50  0001 C CNN
	1    9750 3600
	1    0    0    -1  
$EndComp
Wire Wire Line
	9750 3500 9750 3600
$Comp
L power:GND #PWR080
U 1 1 6150B9FF
P 9750 4800
F 0 "#PWR080" H 9750 4550 50  0001 C CNN
F 1 "GND" H 9755 4627 50  0000 C CNN
F 2 "" H 9750 4800 50  0001 C CNN
F 3 "" H 9750 4800 50  0001 C CNN
	1    9750 4800
	1    0    0    -1  
$EndComp
Wire Wire Line
	9750 4700 9750 4800
$Comp
L power:GND #PWR076
U 1 1 61512C5E
P 8750 3600
F 0 "#PWR076" H 8750 3350 50  0001 C CNN
F 1 "GND" H 8755 3427 50  0000 C CNN
F 2 "" H 8750 3600 50  0001 C CNN
F 3 "" H 8750 3600 50  0001 C CNN
	1    8750 3600
	1    0    0    -1  
$EndComp
Wire Wire Line
	8750 3500 8750 3600
Text Label 8550 4400 0    50   ~ 0
LED_B
Wire Wire Line
	8550 4400 9000 4400
Wire Wire Line
	1400 6550 1950 6550
Wire Wire Line
	1400 6900 1950 6900
Wire Wire Line
	1950 7250 1400 7250
Text HLabel 1400 4600 0    50   Input ~ 0
nLED_B
$Comp
L power:GND #PWR055
U 1 1 616AF1C8
P 2550 3550
F 0 "#PWR055" H 2550 3300 50  0001 C CNN
F 1 "GND" H 2555 3377 50  0000 C CNN
F 2 "" H 2550 3550 50  0001 C CNN
F 3 "" H 2550 3550 50  0001 C CNN
	1    2550 3550
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D8
U 1 1 616AF1EA
P 2300 3000
F 0 "D8" H 2293 2745 50  0000 C CNN
F 1 "LED, red" H 2293 2836 50  0000 C CNN
F 2 "LED_SMD:LED_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 2300 3000 50  0001 C CNN
F 3 "150060SS55040" H 2300 3000 50  0001 C CNN
F 4 " Würth Elektronik" H 2300 3000 50  0001 C CNN "Manufacturer"
F 5 "150060SS55040" H 2300 3000 50  0001 C CNN "Part-No."
	1    2300 3000
	-1   0    0    1   
$EndComp
Wire Wire Line
	2050 3000 2150 3000
Connection ~ 2550 3000
Wire Wire Line
	2450 3000 2550 3000
$Comp
L Device:R R21
U 1 1 617C95B1
P 1900 3000
F 0 "R21" V 1693 3000 50  0000 C CNN
F 1 "300" V 1784 3000 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 1830 3000 50  0001 C CNN
F 3 "~" H 1900 3000 50  0001 C CNN
F 4 "Bourns Inc." H 1900 3000 50  0001 C CNN "Manufacturer"
F 5 "CR0603-JW-301ELF" H 1900 3000 50  0001 C CNN "Part-No."
	1    1900 3000
	0    1    1    0   
$EndComp
Wire Wire Line
	2550 3000 2550 3100
Wire Wire Line
	2550 3500 2550 3550
Wire Wire Line
	1600 3000 1600 2900
Wire Wire Line
	1600 3000 1750 3000
$Comp
L power:+5V #PWR050
U 1 1 617C95AB
P 1600 2900
F 0 "#PWR050" H 1600 2750 50  0001 C CNN
F 1 "+5V" H 1615 3073 50  0000 C CNN
F 2 "" H 1600 2900 50  0001 C CNN
F 3 "" H 1600 2900 50  0001 C CNN
	1    1600 2900
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR047
U 1 1 61108F75
P 1350 2900
F 0 "#PWR047" H 1350 2750 50  0001 C CNN
F 1 "+3.3V" H 1365 3073 50  0000 C CNN
F 2 "" H 1350 2900 50  0001 C CNN
F 3 "" H 1350 2900 50  0001 C CNN
	1    1350 2900
	1    0    0    -1  
$EndComp
$Comp
L Device:R R22
U 1 1 61109359
P 1900 3300
F 0 "R22" V 1693 3300 50  0000 C CNN
F 1 "10k" V 1784 3300 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 1830 3300 50  0001 C CNN
F 3 "~" H 1900 3300 50  0001 C CNN
F 4 "TE Connectivity Passive Product" H 1900 3300 50  0001 C CNN "Manufacturer"
F 5 "CRGCQ0603J10K" H 1900 3300 50  0001 C CNN "Part-No."
	1    1900 3300
	0    1    1    0   
$EndComp
Text HLabel 1350 3450 0    50   Input ~ 0
nLED_A
Wire Wire Line
	2050 3300 2150 3300
Wire Wire Line
	1350 3300 1750 3300
Wire Wire Line
	1350 2900 1350 3300
Wire Wire Line
	1350 3450 2150 3450
Wire Wire Line
	2150 3450 2150 3300
Connection ~ 2150 3300
Wire Wire Line
	2150 3300 2250 3300
$Comp
L power:+3.3V #PWR060
U 1 1 61349A8D
P 3950 1100
F 0 "#PWR060" H 3950 950 50  0001 C CNN
F 1 "+3.3V" H 3965 1273 50  0000 C CNN
F 2 "" H 3950 1100 50  0001 C CNN
F 3 "" H 3950 1100 50  0001 C CNN
	1    3950 1100
	1    0    0    -1  
$EndComp
Wire Wire Line
	3950 1150 3950 1100
$Comp
L Device:R R30
U 1 1 61349A94
P 3950 1300
F 0 "R30" H 4020 1346 50  0000 L CNN
F 1 "10k" H 4020 1255 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 3880 1300 50  0001 C CNN
F 3 "~" H 3950 1300 50  0001 C CNN
F 4 "TE Connectivity Passive Product" H 3950 1300 50  0001 C CNN "Manufacturer"
F 5 "CRGCQ0603J10K" H 3950 1300 50  0001 C CNN "Part-No."
	1    3950 1300
	1    0    0    -1  
$EndComp
Wire Wire Line
	3950 1450 3950 1550
$Comp
L power:+3.3V #PWR070
U 1 1 613906B5
P 6250 1100
F 0 "#PWR070" H 6250 950 50  0001 C CNN
F 1 "+3.3V" H 6265 1273 50  0000 C CNN
F 2 "" H 6250 1100 50  0001 C CNN
F 3 "" H 6250 1100 50  0001 C CNN
	1    6250 1100
	1    0    0    -1  
$EndComp
Wire Wire Line
	6250 1150 6250 1100
$Comp
L Device:R R33
U 1 1 613906BC
P 6250 1300
F 0 "R33" H 6320 1346 50  0000 L CNN
F 1 "10k" H 6320 1255 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 6180 1300 50  0001 C CNN
F 3 "~" H 6250 1300 50  0001 C CNN
F 4 "TE Connectivity Passive Product" H 6250 1300 50  0001 C CNN "Manufacturer"
F 5 "CRGCQ0603J10K" H 6250 1300 50  0001 C CNN "Part-No."
	1    6250 1300
	1    0    0    -1  
$EndComp
Wire Wire Line
	6250 1450 6250 1550
$Comp
L power:GND #PWR056
U 1 1 6139F499
P 2600 4700
F 0 "#PWR056" H 2600 4450 50  0001 C CNN
F 1 "GND" H 2605 4527 50  0000 C CNN
F 2 "" H 2600 4700 50  0001 C CNN
F 3 "" H 2600 4700 50  0001 C CNN
	1    2600 4700
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D9
U 1 1 6139F49F
P 2350 4150
F 0 "D9" H 2343 3895 50  0000 C CNN
F 1 "LED, green" H 2343 3986 50  0000 C CNN
F 2 "LED_SMD:LED_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 2350 4150 50  0001 C CNN
F 3 "150060VS55040" H 2350 4150 50  0001 C CNN
F 4 " Würth Elektronik" H 2350 4150 50  0001 C CNN "Manufacturer"
F 5 "150060VS55040" H 2350 4150 50  0001 C CNN "Part-No."
	1    2350 4150
	-1   0    0    1   
$EndComp
Wire Wire Line
	2100 4150 2200 4150
Connection ~ 2600 4150
Wire Wire Line
	2500 4150 2600 4150
$Comp
L Device:R R23
U 1 1 6139F4A9
P 1950 4150
F 0 "R23" V 1743 4150 50  0000 C CNN
F 1 "300" V 1834 4150 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 1880 4150 50  0001 C CNN
F 3 "~" H 1950 4150 50  0001 C CNN
F 4 "Bourns Inc." H 1950 4150 50  0001 C CNN "Manufacturer"
F 5 "CR0603-JW-301ELF" H 1950 4150 50  0001 C CNN "Part-No."
	1    1950 4150
	0    1    1    0   
$EndComp
Wire Wire Line
	2600 4150 2600 4250
Wire Wire Line
	2600 4650 2600 4700
Wire Wire Line
	1650 4150 1650 4050
Wire Wire Line
	1650 4150 1800 4150
$Comp
L power:+5V #PWR051
U 1 1 6139F4BB
P 1650 4050
F 0 "#PWR051" H 1650 3900 50  0001 C CNN
F 1 "+5V" H 1665 4223 50  0000 C CNN
F 2 "" H 1650 4050 50  0001 C CNN
F 3 "" H 1650 4050 50  0001 C CNN
	1    1650 4050
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR048
U 1 1 6139F4C1
P 1400 4050
F 0 "#PWR048" H 1400 3900 50  0001 C CNN
F 1 "+3.3V" H 1415 4223 50  0000 C CNN
F 2 "" H 1400 4050 50  0001 C CNN
F 3 "" H 1400 4050 50  0001 C CNN
	1    1400 4050
	1    0    0    -1  
$EndComp
$Comp
L Device:R R24
U 1 1 6139F4C7
P 1950 4450
F 0 "R24" V 1743 4450 50  0000 C CNN
F 1 "10k" V 1834 4450 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 1880 4450 50  0001 C CNN
F 3 "~" H 1950 4450 50  0001 C CNN
F 4 "TE Connectivity Passive Product" H 1950 4450 50  0001 C CNN "Manufacturer"
F 5 "CRGCQ0603J10K" H 1950 4450 50  0001 C CNN "Part-No."
	1    1950 4450
	0    1    1    0   
$EndComp
Wire Wire Line
	2100 4450 2200 4450
Wire Wire Line
	1400 4450 1800 4450
Wire Wire Line
	1400 4050 1400 4450
Wire Wire Line
	1400 4600 2200 4600
Wire Wire Line
	2200 4600 2200 4450
Connection ~ 2200 4450
Wire Wire Line
	2200 4450 2300 4450
Wire Wire Line
	2600 4150 2950 4150
Wire Wire Line
	2550 3000 2900 3000
Text Label 2900 3000 2    50   ~ 0
LED_A
Text Label 2950 4150 2    50   ~ 0
LED_B
Wire Wire Line
	6000 4400 6000 4700
Wire Wire Line
	6000 4700 5200 4700
NoConn ~ 4700 3500
NoConn ~ 5200 3500
NoConn ~ 4700 3700
NoConn ~ 4700 3800
NoConn ~ 4700 3900
NoConn ~ 4700 4000
NoConn ~ 4700 4100
NoConn ~ 4700 4200
NoConn ~ 5200 3700
NoConn ~ 5200 3800
NoConn ~ 5200 3900
NoConn ~ 5200 4000
NoConn ~ 5200 4100
NoConn ~ 5200 4300
NoConn ~ 5200 4400
NoConn ~ 5200 4500
NoConn ~ 5200 4600
Wire Wire Line
	5450 3600 5200 3600
Wire Wire Line
	4450 3600 4700 3600
Wire Wire Line
	9500 3500 9750 3500
Wire Wire Line
	8750 3500 9000 3500
NoConn ~ 9000 3600
NoConn ~ 9000 3700
NoConn ~ 9000 3800
NoConn ~ 9000 3900
NoConn ~ 9000 4000
NoConn ~ 9000 4100
NoConn ~ 9000 4200
NoConn ~ 9000 4300
NoConn ~ 9500 3600
NoConn ~ 9500 3700
NoConn ~ 9500 3800
NoConn ~ 9500 3900
NoConn ~ 9500 4000
NoConn ~ 9500 4100
NoConn ~ 9500 4200
NoConn ~ 9500 4500
NoConn ~ 9500 4600
NoConn ~ 9000 4500
NoConn ~ 9000 4600
Wire Wire Line
	9500 4700 9750 4700
$Comp
L power:GND #PWR063
U 1 1 6106979E
P 4450 4900
F 0 "#PWR063" H 4450 4650 50  0001 C CNN
F 1 "GND" H 4455 4727 50  0000 C CNN
F 2 "" H 4450 4900 50  0001 C CNN
F 3 "" H 4450 4900 50  0001 C CNN
	1    4450 4900
	1    0    0    -1  
$EndComp
Connection ~ 4450 4700
Wire Wire Line
	4700 4700 4450 4700
Wire Wire Line
	4450 4700 4450 4900
Wire Wire Line
	4450 4300 4700 4300
Wire Wire Line
	4450 4400 4700 4400
Connection ~ 4450 4400
Wire Wire Line
	4450 4400 4450 4300
Wire Wire Line
	4450 4500 4700 4500
Wire Wire Line
	4450 4500 4450 4400
Connection ~ 4450 4500
Connection ~ 4450 4600
Wire Wire Line
	4450 4600 4700 4600
Wire Wire Line
	4450 4700 4450 4600
Wire Wire Line
	4450 4600 4450 4500
Connection ~ 6250 1550
$Comp
L power:GND #PWR046
U 1 1 617DBB3D
P 1100 2200
F 0 "#PWR046" H 1100 1950 50  0001 C CNN
F 1 "GND" H 1105 2027 50  0000 C CNN
F 2 "" H 1100 2200 50  0001 C CNN
F 3 "" H 1100 2200 50  0001 C CNN
	1    1100 2200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR057
U 1 1 618039E4
P 2600 5850
F 0 "#PWR057" H 2600 5600 50  0001 C CNN
F 1 "GND" H 2605 5677 50  0000 C CNN
F 2 "" H 2600 5850 50  0001 C CNN
F 3 "" H 2600 5850 50  0001 C CNN
	1    2600 5850
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D10
U 1 1 618039EA
P 2350 5300
F 0 "D10" H 2343 5045 50  0000 C CNN
F 1 "LED, blue" H 2343 5136 50  0000 C CNN
F 2 "LED_SMD:LED_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 2350 5300 50  0001 C CNN
F 3 "150060BS55040" H 2350 5300 50  0001 C CNN
F 4 " Würth Elektronik" H 2350 5300 50  0001 C CNN "Manufacturer"
F 5 "150060BS55040" H 2350 5300 50  0001 C CNN "Part-No."
	1    2350 5300
	-1   0    0    1   
$EndComp
Wire Wire Line
	2100 5300 2200 5300
Connection ~ 2600 5300
Wire Wire Line
	2500 5300 2600 5300
$Comp
L Device:R R25
U 1 1 618039F3
P 1950 5300
F 0 "R25" V 1743 5300 50  0000 C CNN
F 1 "180" V 1834 5300 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 1880 5300 50  0001 C CNN
F 3 "~" H 1950 5300 50  0001 C CNN
F 4 "TE Connectivity Passive Product" H 1950 5300 50  0001 C CNN "Manufacturer"
F 5 "CRGP0603F180R" H 1950 5300 50  0001 C CNN "Part-No."
	1    1950 5300
	0    1    1    0   
$EndComp
Wire Wire Line
	2600 5300 2600 5400
Wire Wire Line
	2600 5800 2600 5850
Wire Wire Line
	1650 5300 1650 5200
Wire Wire Line
	1650 5300 1800 5300
$Comp
L power:+5V #PWR052
U 1 1 61803A05
P 1650 5200
F 0 "#PWR052" H 1650 5050 50  0001 C CNN
F 1 "+5V" H 1665 5373 50  0000 C CNN
F 2 "" H 1650 5200 50  0001 C CNN
F 3 "" H 1650 5200 50  0001 C CNN
	1    1650 5200
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR049
U 1 1 61803A0B
P 1400 5200
F 0 "#PWR049" H 1400 5050 50  0001 C CNN
F 1 "+3.3V" H 1415 5373 50  0000 C CNN
F 2 "" H 1400 5200 50  0001 C CNN
F 3 "" H 1400 5200 50  0001 C CNN
	1    1400 5200
	1    0    0    -1  
$EndComp
Wire Wire Line
	2100 5600 2200 5600
Wire Wire Line
	1400 5200 1400 5600
Wire Wire Line
	1400 5750 2200 5750
Wire Wire Line
	2200 5750 2200 5600
Connection ~ 2200 5600
Wire Wire Line
	2200 5600 2300 5600
Wire Wire Line
	2600 5300 3000 5300
Wire Wire Line
	5800 6050 5800 5900
Wire Wire Line
	5800 6450 5800 6550
Wire Wire Line
	5050 6250 5350 6250
$Comp
L power:GND #PWR068
U 1 1 618F40E8
P 5800 6550
F 0 "#PWR068" H 5800 6300 50  0001 C CNN
F 1 "GND" H 5805 6377 50  0000 C CNN
F 2 "" H 5800 6550 50  0001 C CNN
F 3 "" H 5800 6550 50  0001 C CNN
	1    5800 6550
	1    0    0    -1  
$EndComp
Wire Wire Line
	5800 5900 6400 5900
$Comp
L power:+3.3V #PWR067
U 1 1 618F40EF
P 5800 5400
F 0 "#PWR067" H 5800 5250 50  0001 C CNN
F 1 "+3.3V" H 5815 5573 50  0000 C CNN
F 2 "" H 5800 5400 50  0001 C CNN
F 3 "" H 5800 5400 50  0001 C CNN
	1    5800 5400
	1    0    0    -1  
$EndComp
Wire Wire Line
	5800 5450 5800 5400
$Comp
L Device:R R32
U 1 1 618F40F6
P 5800 5600
F 0 "R32" H 5870 5646 50  0000 L CNN
F 1 "10k" H 5870 5555 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 5730 5600 50  0001 C CNN
F 3 "~" H 5800 5600 50  0001 C CNN
F 4 "TE Connectivity Passive Product" H 5800 5600 50  0001 C CNN "Manufacturer"
F 5 "CRGCQ0603J10K" H 5800 5600 50  0001 C CNN "Part-No."
	1    5800 5600
	1    0    0    -1  
$EndComp
Connection ~ 5800 5900
Wire Wire Line
	5800 5750 5800 5900
Text HLabel 5050 6250 0    50   Input ~ 0
nON_OFF
Text Label 5750 4200 2    50   ~ 0
Main_Switch
Wire Wire Line
	5750 4200 5200 4200
$Comp
L power:+3.3V #PWR064
U 1 1 6194AF19
P 5350 5400
F 0 "#PWR064" H 5350 5250 50  0001 C CNN
F 1 "+3.3V" H 5365 5573 50  0000 C CNN
F 2 "" H 5350 5400 50  0001 C CNN
F 3 "" H 5350 5400 50  0001 C CNN
	1    5350 5400
	1    0    0    -1  
$EndComp
Wire Wire Line
	5350 5450 5350 5400
$Comp
L Device:R R31
U 1 1 6194AF20
P 5350 5600
F 0 "R31" H 5420 5646 50  0000 L CNN
F 1 "10k" H 5420 5555 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 5280 5600 50  0001 C CNN
F 3 "~" H 5350 5600 50  0001 C CNN
F 4 "TE Connectivity Passive Product" H 5350 5600 50  0001 C CNN "Manufacturer"
F 5 "CRGCQ0603J10K" H 5350 5600 50  0001 C CNN "Part-No."
	1    5350 5600
	1    0    0    -1  
$EndComp
Wire Wire Line
	5350 5750 5350 6250
Connection ~ 5350 6250
Wire Wire Line
	5350 6250 5500 6250
$Comp
L power:+3.3V #PWR072
U 1 1 6196F50A
P 7500 4150
F 0 "#PWR072" H 7500 4000 50  0001 C CNN
F 1 "+3.3V" H 7515 4323 50  0000 C CNN
F 2 "" H 7500 4150 50  0001 C CNN
F 3 "" H 7500 4150 50  0001 C CNN
	1    7500 4150
	1    0    0    -1  
$EndComp
Wire Wire Line
	7500 4250 7500 4150
$Comp
L Device:R R34
U 1 1 6196F511
P 7500 4400
F 0 "R34" H 7570 4446 50  0000 L CNN
F 1 "10k" H 7570 4355 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 7430 4400 50  0001 C CNN
F 3 "~" H 7500 4400 50  0001 C CNN
F 4 "TE Connectivity Passive Product" H 7500 4400 50  0001 C CNN "Manufacturer"
F 5 "CRGCQ0603J10K" H 7500 4400 50  0001 C CNN "Part-No."
	1    7500 4400
	1    0    0    -1  
$EndComp
Wire Wire Line
	1400 5600 1800 5600
$Comp
L Device:R R26
U 1 1 61803A11
P 1950 5600
F 0 "R26" V 1743 5600 50  0000 C CNN
F 1 "10k" V 1834 5600 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 1880 5600 50  0001 C CNN
F 3 "~" H 1950 5600 50  0001 C CNN
F 4 "TE Connectivity Passive Product" H 1950 5600 50  0001 C CNN "Manufacturer"
F 5 "CRGCQ0603J10K" H 1950 5600 50  0001 C CNN "Part-No."
	1    1950 5600
	0    1    1    0   
$EndComp
Wire Wire Line
	7900 4700 9000 4700
Wire Wire Line
	7900 5200 7900 5550
Wire Wire Line
	7500 5000 7600 5000
Connection ~ 7500 5000
Wire Wire Line
	7500 4550 7500 5000
Text Label 6400 5900 2    50   ~ 0
Main_Switch
Text HLabel 7150 5000 0    50   Input ~ 0
nRST
$Comp
L power:GND #PWR074
U 1 1 61075918
P 7900 5550
F 0 "#PWR074" H 7900 5300 50  0001 C CNN
F 1 "GND" H 7905 5377 50  0000 C CNN
F 2 "" H 7900 5550 50  0001 C CNN
F 3 "" H 7900 5550 50  0001 C CNN
	1    7900 5550
	1    0    0    -1  
$EndComp
Wire Wire Line
	7150 5000 7500 5000
Wire Wire Line
	7900 4800 7900 4700
Wire Wire Line
	7900 4550 7900 4700
Connection ~ 7900 4700
$Comp
L Device:Q_NMOS_GSD Q?
U 1 1 6232E791
P 2450 3300
AR Path="/60C3F332/6232E791" Ref="Q?"  Part="1" 
AR Path="/60C50401/6232E791" Ref="Q6"  Part="1" 
F 0 "Q6" H 2699 3300 50  0000 C CNN
F 1 "SI2302CDS-T1-BE3" H 3050 3200 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 2650 3400 50  0001 C CNN
F 3 "https://www.mouser.de/datasheet/2/196/Infineon_IRLML6246_DataSheet_v01_01_EN-1228486.pdf" H 2450 3300 50  0001 C CNN
F 4 "Vishay / Siliconix" H 2450 3300 50  0001 C CNN "Manufacturer"
F 5 "SI2302CDS-T1-BE3" H 2450 3300 50  0001 C CNN "Part-No."
	1    2450 3300
	1    0    0    -1  
$EndComp
$Comp
L Device:Q_NMOS_GSD Q?
U 1 1 6232F037
P 2500 5600
AR Path="/60C3F332/6232F037" Ref="Q?"  Part="1" 
AR Path="/60C50401/6232F037" Ref="Q8"  Part="1" 
F 0 "Q8" H 2749 5600 50  0000 C CNN
F 1 "SI2302CDS-T1-BE3" H 3100 5500 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 2700 5700 50  0001 C CNN
F 3 "https://www.mouser.de/datasheet/2/196/Infineon_IRLML6246_DataSheet_v01_01_EN-1228486.pdf" H 2500 5600 50  0001 C CNN
F 4 "Vishay / Siliconix" H 2500 5600 50  0001 C CNN "Manufacturer"
F 5 "SI2302CDS-T1-BE3" H 2500 5600 50  0001 C CNN "Part-No."
	1    2500 5600
	1    0    0    -1  
$EndComp
$Comp
L Device:Q_NMOS_GSD Q?
U 1 1 6232F7FF
P 2500 4450
AR Path="/60C3F332/6232F7FF" Ref="Q?"  Part="1" 
AR Path="/60C50401/6232F7FF" Ref="Q7"  Part="1" 
F 0 "Q7" H 2749 4450 50  0000 C CNN
F 1 "SI2302CDS-T1-BE3" H 3100 4350 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 2700 4550 50  0001 C CNN
F 3 "https://www.mouser.de/datasheet/2/196/Infineon_IRLML6246_DataSheet_v01_01_EN-1228486.pdf" H 2500 4450 50  0001 C CNN
F 4 "Vishay / Siliconix" H 2500 4450 50  0001 C CNN "Manufacturer"
F 5 "SI2302CDS-T1-BE3" H 2500 4450 50  0001 C CNN "Part-No."
	1    2500 4450
	1    0    0    -1  
$EndComp
$Comp
L Device:Q_NMOS_GSD Q?
U 1 1 6232FCBD
P 5700 6250
AR Path="/60C3F332/6232FCBD" Ref="Q?"  Part="1" 
AR Path="/60C50401/6232FCBD" Ref="Q9"  Part="1" 
F 0 "Q9" H 5949 6250 50  0000 C CNN
F 1 "SI2302CDS-T1-BE3" H 6300 6150 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 5900 6350 50  0001 C CNN
F 3 "https://www.mouser.de/datasheet/2/196/Infineon_IRLML6246_DataSheet_v01_01_EN-1228486.pdf" H 5700 6250 50  0001 C CNN
F 4 "Vishay / Siliconix" H 5700 6250 50  0001 C CNN "Manufacturer"
F 5 "SI2302CDS-T1-BE3" H 5700 6250 50  0001 C CNN "Part-No."
	1    5700 6250
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR058
U 1 1 6222DB21
P 3250 6500
F 0 "#PWR058" H 3250 6350 50  0001 C CNN
F 1 "+5V" H 3265 6673 50  0000 C CNN
F 2 "" H 3250 6500 50  0001 C CNN
F 3 "" H 3250 6500 50  0001 C CNN
	1    3250 6500
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR069
U 1 1 62267367
P 6000 4400
F 0 "#PWR069" H 6000 4250 50  0001 C CNN
F 1 "+5V" H 6015 4573 50  0000 C CNN
F 2 "" H 6000 4400 50  0001 C CNN
F 3 "" H 6000 4400 50  0001 C CNN
	1    6000 4400
	1    0    0    -1  
$EndComp
Text Notes 5950 4050 0    50   ~ 0
Battery Voltage Zumo
Wire Wire Line
	2250 6900 2600 6900
$Comp
L Device:R R27
U 1 1 61001F8A
P 2100 6550
F 0 "R27" V 1893 6550 50  0000 C CNN
F 1 "300" V 1984 6550 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 2030 6550 50  0001 C CNN
F 3 "~" H 2100 6550 50  0001 C CNN
F 4 "Bourns Inc." H 2100 6550 50  0001 C CNN "Manufacturer"
F 5 "CR0603-JW-301ELF" H 2100 6550 50  0001 C CNN "Part-No."
	1    2100 6550
	0    1    1    0   
$EndComp
Text Notes 5950 4150 0    50   ~ 0
I_max = 2.6 A 
Wire Wire Line
	2300 1200 2300 1550
Text HLabel 2300 1200 1    50   Output ~ 0
nBUT_A
Text Label 2150 1550 2    50   ~ 0
BUT_A
Connection ~ 1750 1550
Wire Wire Line
	1750 1450 1750 1550
$Comp
L Device:R R20
U 1 1 612AF006
P 1750 1300
F 0 "R20" H 1820 1346 50  0000 L CNN
F 1 "10k" H 1820 1255 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 1680 1300 50  0001 C CNN
F 3 "~" H 1750 1300 50  0001 C CNN
F 4 "TE Connectivity Passive Product" H 1750 1300 50  0001 C CNN "Manufacturer"
F 5 "CRGCQ0603J10K" H 1750 1300 50  0001 C CNN "Part-No."
	1    1750 1300
	1    0    0    -1  
$EndComp
Wire Wire Line
	1750 1150 1750 1100
$Comp
L power:+3.3V #PWR053
U 1 1 61243628
P 1750 1100
F 0 "#PWR053" H 1750 950 50  0001 C CNN
F 1 "+3.3V" H 1765 1273 50  0000 C CNN
F 2 "" H 1750 1100 50  0001 C CNN
F 3 "" H 1750 1100 50  0001 C CNN
	1    1750 1100
	1    0    0    -1  
$EndComp
Wire Wire Line
	1750 1550 2300 1550
Connection ~ 3950 1550
Wire Wire Line
	4500 1200 4500 1550
Text HLabel 4500 1200 1    50   Output ~ 0
nBUT_B
Text Label 4350 1550 2    50   ~ 0
BUT_B
Wire Wire Line
	3950 1550 4500 1550
Text Label 6650 1550 2    50   ~ 0
BUT_C
Text HLabel 6800 1200 1    50   Output ~ 0
nBUT_C
Wire Wire Line
	6800 1200 6800 1550
Wire Wire Line
	6250 1550 6800 1550
$Comp
L Device:C C16
U 1 1 62612896
P 1750 1750
F 0 "C16" H 1865 1796 50  0000 L CNN
F 1 "10n" H 1865 1705 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 1788 1600 50  0001 C CNN
F 3 "~" H 1750 1750 50  0001 C CNN
F 4 "KEMET" H 1750 1750 50  0001 C CNN "Manufacturer"
F 5 "C0603C103M5RAC7411" H 1750 1750 50  0001 C CNN "Part-No."
	1    1750 1750
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR054
U 1 1 62612FD9
P 1750 2200
F 0 "#PWR054" H 1750 1950 50  0001 C CNN
F 1 "GND" H 1755 2027 50  0000 C CNN
F 2 "" H 1750 2200 50  0001 C CNN
F 3 "" H 1750 2200 50  0001 C CNN
	1    1750 2200
	1    0    0    -1  
$EndComp
Wire Wire Line
	1750 2200 1750 1900
Wire Wire Line
	1750 1600 1750 1550
$Comp
L Device:C C17
U 1 1 62627569
P 3950 1750
F 0 "C17" H 4065 1796 50  0000 L CNN
F 1 "10n" H 4065 1705 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 3988 1600 50  0001 C CNN
F 3 "~" H 3950 1750 50  0001 C CNN
F 4 "KEMET" H 3950 1750 50  0001 C CNN "Manufacturer"
F 5 "C0603C103M5RAC7411" H 3950 1750 50  0001 C CNN "Part-No."
	1    3950 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	3950 1600 3950 1550
$Comp
L Device:C C18
U 1 1 6263BD5A
P 6250 1750
F 0 "C18" H 6365 1796 50  0000 L CNN
F 1 "10n" H 6365 1705 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 6288 1600 50  0001 C CNN
F 3 "~" H 6250 1750 50  0001 C CNN
F 4 "KEMET" H 6250 1750 50  0001 C CNN "Manufacturer"
F 5 "C0603C103M5RAC7411" H 6250 1750 50  0001 C CNN "Part-No."
	1    6250 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	6250 1600 6250 1550
$Comp
L KMR221GLFS:KMR221GLFS SW3
U 1 1 627F711A
P 1100 1850
F 0 "SW3" V 1054 1935 50  0000 L CNN
F 1 "KMR221GLFS" V 1145 1935 50  0000 L CNN
F 2 "footprints:SW_KMR221GLFS" H 1100 1850 50  0001 L BNN
F 3 "-" H 1100 1850 50  0001 L BNN
F 4 " C&K" H 1100 1850 50  0001 C CNN "Manufacturer"
F 5 "KMR221GLFS" H 1100 1850 50  0001 C CNN "Part-No."
	1    1100 1850
	0    1    1    0   
$EndComp
Wire Wire Line
	1000 2150 1100 2150
$Comp
L power:GND #PWR059
U 1 1 6284D0AC
P 3300 2200
F 0 "#PWR059" H 3300 1950 50  0001 C CNN
F 1 "GND" H 3305 2027 50  0000 C CNN
F 2 "" H 3300 2200 50  0001 C CNN
F 3 "" H 3300 2200 50  0001 C CNN
	1    3300 2200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR061
U 1 1 6284D0B2
P 3950 2200
F 0 "#PWR061" H 3950 1950 50  0001 C CNN
F 1 "GND" H 3955 2027 50  0000 C CNN
F 2 "" H 3950 2200 50  0001 C CNN
F 3 "" H 3950 2200 50  0001 C CNN
	1    3950 2200
	1    0    0    -1  
$EndComp
$Comp
L KMR221GLFS:KMR221GLFS SW4
U 1 1 6284D0B9
P 3300 1850
F 0 "SW4" V 3254 1935 50  0000 L CNN
F 1 "KMR221GLFS" V 3345 1935 50  0000 L CNN
F 2 "footprints:SW_KMR221GLFS" H 3300 1850 50  0001 L BNN
F 3 "-" H 3300 1850 50  0001 L BNN
F 4 " C&K" H 3300 1850 50  0001 C CNN "Manufacturer"
F 5 "KMR221GLFS" H 3300 1850 50  0001 C CNN "Part-No."
	1    3300 1850
	0    1    1    0   
$EndComp
Wire Wire Line
	3200 2150 3300 2150
Wire Wire Line
	3950 1900 3950 2200
Wire Wire Line
	1100 2150 1100 2200
Connection ~ 1100 2150
Wire Wire Line
	3300 2150 3300 2200
Connection ~ 3300 2150
$Comp
L power:GND #PWR066
U 1 1 628C1E66
P 5600 2200
F 0 "#PWR066" H 5600 1950 50  0001 C CNN
F 1 "GND" H 5605 2027 50  0000 C CNN
F 2 "" H 5600 2200 50  0001 C CNN
F 3 "" H 5600 2200 50  0001 C CNN
	1    5600 2200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR071
U 1 1 628C1E6C
P 6250 2200
F 0 "#PWR071" H 6250 1950 50  0001 C CNN
F 1 "GND" H 6255 2027 50  0000 C CNN
F 2 "" H 6250 2200 50  0001 C CNN
F 3 "" H 6250 2200 50  0001 C CNN
	1    6250 2200
	1    0    0    -1  
$EndComp
Wire Wire Line
	6250 2200 6250 1900
$Comp
L KMR221GLFS:KMR221GLFS SW5
U 1 1 628C1E73
P 5600 1850
F 0 "SW5" V 5554 1935 50  0000 L CNN
F 1 "KMR221GLFS" V 5645 1935 50  0000 L CNN
F 2 "footprints:SW_KMR221GLFS" H 5600 1850 50  0001 L BNN
F 3 "-" H 5600 1850 50  0001 L BNN
F 4 " C&K" H 5600 1850 50  0001 C CNN "Manufacturer"
F 5 "KMR221GLFS" H 5600 1850 50  0001 C CNN "Part-No."
	1    5600 1850
	0    1    1    0   
$EndComp
Wire Wire Line
	5500 2150 5600 2150
Wire Wire Line
	5600 2150 5600 2200
Connection ~ 5600 2150
$Comp
L Device:Q_NMOS_GSD Q?
U 1 1 62330FDB
P 7800 5000
AR Path="/60C3F332/62330FDB" Ref="Q?"  Part="1" 
AR Path="/60C50401/62330FDB" Ref="Q10"  Part="1" 
F 0 "Q10" H 8100 5000 50  0000 C CNN
F 1 "SI2302CDS-T1-BE3" H 8400 4900 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 8000 5100 50  0001 C CNN
F 3 "https://www.mouser.de/datasheet/2/196/Infineon_IRLML6246_DataSheet_v01_01_EN-1228486.pdf" H 7800 5000 50  0001 C CNN
F 4 "Vishay / Siliconix" H 7800 5000 50  0001 C CNN "Manufacturer"
F 5 "SI2302CDS-T1-BE3" H 7800 5000 50  0001 C CNN "Part-No."
	1    7800 5000
	1    0    0    -1  
$EndComp
$Comp
L Device:LED_ARGB D11
U 1 1 62EBCED3
P 2800 6900
F 0 "D11" H 2800 7397 50  0000 C CNN
F 1 "LED_RGBA" H 2800 7306 50  0000 C CNN
F 2 "footprints:LED_RGB_1210" H 2800 6850 50  0001 C CNN
F 3 "https://docs.broadcom.com/doc/AV02-0610EN" H 2800 6850 50  0001 C CNN
	1    2800 6900
	1    0    0    -1  
$EndComp
Wire Wire Line
	1100 1550 1750 1550
Wire Wire Line
	3300 1550 3950 1550
Wire Wire Line
	5600 1550 6250 1550
Text Notes 4850 3200 0    50   ~ 0
left
Text Notes 9150 3200 0    50   ~ 0
right
$EndSCHEMATC
