EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Connector:Conn_01x06_Male J1
U 1 1 5F46A44B
P 3400 3150
F 0 "J1" H 3600 3600 50  0000 R CNN
F 1 "GPIO" H 3650 3500 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x06_P2.54mm_Vertical" H 3400 3150 50  0001 C CNN
F 3 "~" H 3400 3150 50  0001 C CNN
	1    3400 3150
	1    0    0    -1  
$EndComp
$Comp
L Connector:Mini-DIN-6 J2
U 1 1 5F46B3F1
P 7050 2750
F 0 "J2" H 7050 3117 50  0000 C CNN
F 1 "Keyboard" H 7050 3026 50  0000 C CNN
F 2 "Custom_Footprints:Connector_Mini-DIN_Female_6Pin_2rows" H 7050 2750 50  0001 C CNN
F 3 "http://service.powerdynamics.com/ec/Catalog17/Section%2011.pdf" H 7050 2750 50  0001 C CNN
	1    7050 2750
	1    0    0    -1  
$EndComp
$Comp
L Connector:Mini-DIN-6 J3
U 1 1 5F46DA3A
P 7050 4050
F 0 "J3" H 7050 4417 50  0000 C CNN
F 1 "Mouse" H 7050 4326 50  0000 C CNN
F 2 "Custom_Footprints:Connector_Mini-DIN_Female_6Pin_2rows" H 7050 4050 50  0001 C CNN
F 3 "http://service.powerdynamics.com/ec/Catalog17/Section%2011.pdf" H 7050 4050 50  0001 C CNN
	1    7050 4050
	1    0    0    -1  
$EndComp
$Comp
L Transistor_FET:2N7000 Q1
U 1 1 5F46DCA8
P 4500 2050
F 0 "Q1" H 4704 2096 50  0000 L CNN
F 1 "2N7000" H 4704 2005 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline" H 4700 1975 50  0001 L CIN
F 3 "https://www.fairchildsemi.com/datasheets/2N/2N7000.pdf" H 4500 2050 50  0001 L CNN
	1    4500 2050
	1    0    0    -1  
$EndComp
$Comp
L Device:R R3
U 1 1 5F46FC6A
P 4850 1700
F 0 "R3" V 4643 1700 50  0000 C CNN
F 1 "10k" V 4734 1700 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Vertical" V 4780 1700 50  0001 C CNN
F 3 "~" H 4850 1700 50  0001 C CNN
	1    4850 1700
	0    1    1    0   
$EndComp
$Comp
L Device:R R1
U 1 1 5F471900
P 4350 2400
F 0 "R1" V 4143 2400 50  0000 C CNN
F 1 "10k" V 4234 2400 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Vertical" V 4280 2400 50  0001 C CNN
F 3 "~" H 4350 2400 50  0001 C CNN
	1    4350 2400
	0    1    1    0   
$EndComp
Text Label 3600 2950 0    50   ~ 0
GND
Text Label 3600 3450 0    50   ~ 0
3v3
Text Label 3600 3050 0    50   ~ 0
CLK_K
Text Label 3600 3150 0    50   ~ 0
DATA_K
Text Label 3600 3250 0    50   ~ 0
CLK_M
Text Label 3600 3350 0    50   ~ 0
DATA_M
Wire Wire Line
	6750 2750 6550 2750
Wire Wire Line
	6550 4050 6750 4050
Wire Wire Line
	7350 2750 7750 2750
Wire Wire Line
	7750 4050 7350 4050
Wire Wire Line
	7750 2750 7750 2950
Connection ~ 7750 2950
Wire Wire Line
	7750 2950 7750 4050
Wire Wire Line
	4700 1700 4600 1700
Wire Wire Line
	4600 2250 4600 2400
Wire Wire Line
	4600 2400 4500 2400
$Comp
L Transistor_FET:2N7000 Q3
U 1 1 5F48E17E
P 4500 4200
F 0 "Q3" H 4704 4246 50  0000 L CNN
F 1 "2N7000" H 4704 4155 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline" H 4700 4125 50  0001 L CIN
F 3 "https://www.fairchildsemi.com/datasheets/2N/2N7000.pdf" H 4500 4200 50  0001 L CNN
	1    4500 4200
	1    0    0    -1  
$EndComp
$Comp
L Device:R R7
U 1 1 5F48E184
P 4850 3850
F 0 "R7" V 4643 3850 50  0000 C CNN
F 1 "10k" V 4734 3850 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Vertical" V 4780 3850 50  0001 C CNN
F 3 "~" H 4850 3850 50  0001 C CNN
	1    4850 3850
	0    1    1    0   
$EndComp
$Comp
L Device:R R5
U 1 1 5F48E18A
P 4350 4550
F 0 "R5" V 4143 4550 50  0000 C CNN
F 1 "10k" V 4234 4550 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Vertical" V 4280 4550 50  0001 C CNN
F 3 "~" H 4350 4550 50  0001 C CNN
	1    4350 4550
	0    1    1    0   
$EndComp
Wire Wire Line
	4700 3850 4600 3850
Wire Wire Line
	4600 3850 4600 4000
Wire Wire Line
	4600 4400 4600 4550
Wire Wire Line
	4600 4550 4500 4550
Wire Wire Line
	3600 2950 7750 2950
Wire Wire Line
	4300 4200 4200 4200
Connection ~ 4200 4200
Wire Wire Line
	4200 4200 4200 4550
Wire Wire Line
	4200 2400 4200 2600
Wire Wire Line
	4300 2050 4200 2050
Wire Wire Line
	4200 2050 4200 2400
Connection ~ 4200 2400
$Comp
L Transistor_FET:2N7000 Q2
U 1 1 5F493E04
P 5600 2250
F 0 "Q2" H 5804 2296 50  0000 L CNN
F 1 "2N7000" H 5804 2205 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline" H 5800 2175 50  0001 L CIN
F 3 "https://www.fairchildsemi.com/datasheets/2N/2N7000.pdf" H 5600 2250 50  0001 L CNN
	1    5600 2250
	1    0    0    -1  
$EndComp
$Comp
L Device:R R4
U 1 1 5F493E0A
P 5950 1900
F 0 "R4" V 5743 1900 50  0000 C CNN
F 1 "10k" V 5834 1900 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Vertical" V 5880 1900 50  0001 C CNN
F 3 "~" H 5950 1900 50  0001 C CNN
	1    5950 1900
	0    1    1    0   
$EndComp
$Comp
L Device:R R2
U 1 1 5F493E10
P 5450 2600
F 0 "R2" V 5243 2600 50  0000 C CNN
F 1 "10k" V 5334 2600 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Vertical" V 5380 2600 50  0001 C CNN
F 3 "~" H 5450 2600 50  0001 C CNN
	1    5450 2600
	0    1    1    0   
$EndComp
Wire Wire Line
	5800 1900 5700 1900
Wire Wire Line
	5700 1900 5700 2050
Wire Wire Line
	5700 2450 5700 2600
Wire Wire Line
	5700 2600 5600 2600
$Comp
L Transistor_FET:2N7000 Q4
U 1 1 5F497176
P 5650 4400
F 0 "Q4" H 5854 4446 50  0000 L CNN
F 1 "2N7000" H 5854 4355 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline" H 5850 4325 50  0001 L CIN
F 3 "https://www.fairchildsemi.com/datasheets/2N/2N7000.pdf" H 5650 4400 50  0001 L CNN
	1    5650 4400
	1    0    0    -1  
$EndComp
$Comp
L Device:R R8
U 1 1 5F49717C
P 6000 4050
F 0 "R8" V 5793 4050 50  0000 C CNN
F 1 "10k" V 5884 4050 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Vertical" V 5930 4050 50  0001 C CNN
F 3 "~" H 6000 4050 50  0001 C CNN
	1    6000 4050
	0    1    1    0   
$EndComp
$Comp
L Device:R R6
U 1 1 5F497182
P 5500 4750
F 0 "R6" V 5293 4750 50  0000 C CNN
F 1 "10k" V 5384 4750 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Vertical" V 5430 4750 50  0001 C CNN
F 3 "~" H 5500 4750 50  0001 C CNN
	1    5500 4750
	0    1    1    0   
$EndComp
Wire Wire Line
	5850 4050 5750 4050
Wire Wire Line
	5750 4050 5750 4200
Wire Wire Line
	5750 4600 5750 4750
Wire Wire Line
	5750 4750 5650 4750
Wire Wire Line
	5350 4750 5350 4400
Wire Wire Line
	5350 4400 5450 4400
Wire Wire Line
	5300 2600 5300 2250
Wire Wire Line
	5300 2250 5400 2250
Wire Wire Line
	5300 2600 4200 2600
Connection ~ 5300 2600
Wire Wire Line
	4200 4550 4200 4750
Wire Wire Line
	4200 4750 5350 4750
Connection ~ 4200 4550
Connection ~ 5350 4750
Wire Wire Line
	5000 3850 6150 3850
Wire Wire Line
	6150 4050 6150 3850
Connection ~ 6150 3850
Wire Wire Line
	6150 3850 6550 3850
Wire Wire Line
	6100 1900 6100 1700
Wire Wire Line
	6100 1700 5000 1700
Wire Wire Line
	3600 3050 4600 3050
Wire Wire Line
	4600 3050 4600 2400
Connection ~ 4600 2400
Wire Wire Line
	3600 3150 5700 3150
Wire Wire Line
	5700 3150 5700 2600
Connection ~ 5700 2600
Wire Wire Line
	3600 3350 3850 3350
Wire Wire Line
	3850 5200 5750 5200
Wire Wire Line
	5750 5200 5750 4750
Connection ~ 5750 4750
Wire Wire Line
	3600 3250 3950 3250
Wire Wire Line
	3950 4950 4600 4950
Wire Wire Line
	4600 4950 4600 4550
Connection ~ 4600 4550
Wire Wire Line
	7350 2650 7550 2650
Wire Wire Line
	7550 2650 7550 1250
Wire Wire Line
	7550 1250 4600 1250
Wire Wire Line
	4600 1250 4600 1700
Connection ~ 6550 3850
Wire Wire Line
	6550 3850 6550 4050
Wire Wire Line
	6550 2750 6550 3850
Wire Wire Line
	4200 2600 4200 3450
Connection ~ 4200 2600
Wire Wire Line
	3600 3450 4200 3450
Connection ~ 4200 3450
Wire Wire Line
	4200 3450 4200 4200
Wire Wire Line
	3950 3250 3950 4950
Wire Wire Line
	3850 3350 3850 5200
Wire Wire Line
	4600 3850 4600 3450
Wire Wire Line
	4600 3450 7550 3450
Wire Wire Line
	7550 3450 7550 3950
Wire Wire Line
	7550 3950 7350 3950
Connection ~ 4600 3850
Wire Wire Line
	7350 4150 8050 4150
Wire Wire Line
	8050 4150 8050 3300
Wire Wire Line
	8050 3300 5750 3300
Wire Wire Line
	5750 3300 5750 4050
Connection ~ 5750 4050
Wire Wire Line
	7350 2850 8050 2850
Wire Wire Line
	8050 2850 8050 1450
Wire Wire Line
	8050 1450 5700 1450
Wire Wire Line
	5700 1450 5700 1900
Connection ~ 5700 1900
Text Label 7350 2650 0    50   ~ 0
KBDDATA
Text Label 7350 2850 0    50   ~ 0
KBDCLK
Text Label 6750 2750 2    50   ~ 0
5V
Text Label 7350 2750 0    50   ~ 0
GND
Text Label 7350 4050 0    50   ~ 0
GND
Text Label 6750 4050 2    50   ~ 0
5V
Wire Wire Line
	6100 1700 6550 1700
Wire Wire Line
	6550 1700 6550 2750
Connection ~ 6100 1700
Connection ~ 6550 2750
Text Label 7350 3950 0    50   ~ 0
MOUDATA
Text Label 7350 4150 0    50   ~ 0
MOUCLK
NoConn ~ 6750 2650
NoConn ~ 6750 2850
NoConn ~ 6750 3950
NoConn ~ 6750 4150
Wire Wire Line
	4600 1700 4600 1850
Connection ~ 4600 1700
$EndSCHEMATC
