# Design decisions
* No Chrarger
    * Implementation of a two-pole connection (VBat, GND) for an external battery charger
    * So the Micro-USB port is only used for comunication with the ESP. -> Not for Charging!


# HSI
* In case the battery voltage drops below 6 V, the software must switch off the power supply to the Pololu Zumo.
    * ESP-Port: 23 (IO15) -> active low
    * Zumo Pin: Left double row Pin-Header (J4) Pin 16