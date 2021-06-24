EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 5 7
Title "Zumo Communication System"
Date "2021-06-11"
Rev "V1.0"
Comp "NewTec GmbH"
Comment1 "Schneider, Niklas"
Comment2 "Schneider, Niklas"
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Connector:USB_A J?
U 1 1 60C6499B
P 9100 2750
AR Path="/60C6499B" Ref="J?"  Part="1" 
AR Path="/60C500E6/60C6499B" Ref="J2"  Part="1" 
F 0 "J2" H 9157 3217 50  0000 C CNN
F 1 "USB_A" H 9157 3126 50  0000 C CNN
F 2 "footprints:USB_A_Molex_105057_Vertical_2" H 9250 2700 50  0001 C CNN
F 3 " ~" H 9250 2700 50  0001 C CNN
	1    9100 2750
	-1   0    0    1   
$EndComp
$Comp
L MAX3421EEHJ_T:MAX3421EEHJ+T U5
U 1 1 60C7A47F
P 5350 2950
F 0 "U5" H 5350 4420 50  0000 C CNN
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
$EndSCHEMATC
