
Installing
----------

To install this firmware you need to do the following:

1. Copy the folder EZLink into your Arduino 'sketchbook' folder

2. Copy the folder libraries/PN532Lib to you Arduino 'sketchbook/libriries' folder

3. Then start the Ardunio IDE and select the sketch EZLink.

4. Since the RDM8800 has a LGT8F88A chip, you need to follow the instructions at 
http://wiki.iteadstudio.com/Iteaduino_Lite, to download and install the new Arduino IDE driver/patch so that you
can upload sketches to the LGT8F88A.

You can also see the blog at http://blog.iteadstudio.com/introduction-to-rdm8800-a-13-56mhz-configurable-rfid-module/#more-2151 for more information
on uploading new firmware to the RDM8800.

Features
--------

When a card is detected it returns as a comma seperated list of text fields.
They are the card number, balance, number of days since 1995-01-01 to expire 
and number of days since 1995-01-01 created.

So for example:

When an EZ-Link card is detected the reader will return the following text followed by a carrige return linefeed:

`1000130019390060,8.38,9107,6915`

Which can be broken up into the following comma seperated fields:

+ Number: `1000130019390060`
+ Balance: $`8.38`
+ Expire days: `9107`
+ Created days: `6915`

Thanks To
---------

+ [Stan Lee @ iteadstudio](Lizq@iteadstudio.com)
+ [source code farebot](https://github.com/codebutler/farebot)
+ [Original PN532 library by adafruit/ladyada](www.adafruit.com)





