# BME590L_Lightbulb - Design Skills Project (Variable Light Intensity)

See Final Working Video on [YouTube](https://youtu.be/NFrjT-VMIhY).

## Usage Guide
1. Turn on device using red I/O switch.
1. Push white button closest to I/O switch to cycle through light modes:
+ `Off`
+ `Brightest`
+ `Intermediate Brightness`
+ `Least Bright`
+ `Flashing @ 2 Hz`
1. Push and hold white button furthest from I/O switch to show the remaining voltage left in the battery on the adjacent LED:
   + `GREEN` = battery high (>8V)
   + `BLUE` = battery medium (7-8V)
   + `RED` = battery low (<7V)

## Battery Replacement
1. Spin flaps on bottom away from center of device.
1. Pull top of case off of bottom of case and disconnect toggle switch Molex connection from board.
1. Remove battery wire Molex connection from board.
1. Remove battery from battery slot.
1. Detach wired cap from battery.
1. Attach wired cap to new battery.
1. Add new battery to battery slot.
1. Re-attach battery wire Molex connection to board.
1. Reconnect toggle switch Molex connection to board.
1. Replace case top over case bottom (note: may need to use tweezers or small object to guide push buttons through case top).
1. Spin flaps on bottom towards center of device.

## Documentation
1. [Bill of Materials](https://github.com/jcoop1219/BME590L_Lightbulb/blob/master/Documentation/Bill%20of%20Materials.xlsx)
1. [Final Device Photos](https://github.com/jcoop1219/BME590L_Lightbulb/tree/master/Documentation/Final%20Device%20Photos)

## Other Misc Notes:
+ Total weight = 9.9 oz
+ Current draw while on = 55 mA (lasts 7.2 hours on standard 9V battery)
+ Current draw while off = 0 mA (full off ensured by toggle I/O switch)