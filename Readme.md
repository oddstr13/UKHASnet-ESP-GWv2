Arduino ESP8266 based UKHASnet gateway
======================================
Primarily written for the [Cube 1.9": ESP-12 RFM69][cube1in9-esp-rfm69],
but can easily enough be adapted to other ESP based boards with RFM69HW
([Rendered image of the PCB][cube1in9-esp-rfm69 image])  
On-board is a `ESP-12` module and a `RFM69HW`, along with a voltage regulator and a few passives.  

Dependencies
------------
  * [UKHASnetRFM69][ukhasnet-rfm69], branch: `arduino3` - [Zip download][ukhasnet-rfm69 download].  
    Radio interface library.  
    [Upstream ukhasnet-rfm69 repository][ukhasnet-rfm69 upstream].  
  * [Buffer][buffer] - [Zip download][buffer download].  
    Convenience class for managing character buffers in Arduino.  
    Originally written in `C` for my [ATmega328PB UKHASnet node][buffer origins].




[cube1in9-esp-rfm69]: https://bitbucket.org/openshell/cube-1.9-esp-12-rfm69/
[cube1in9-esp-rfm69 image]: https://bitbucket.org/openshell/cube-1.9-esp-12-rfm69/raw/default/images/top.png

[ukhasnet-rfm69]: https://github.com/oddstr13/ukhasnet-rfm69
[ukhasnet-rfm69 download]: https://github.com/oddstr13/ukhasnet-rfm69/archive/refs/heads/arduino3.zip
[ukhasnet-rfm69 upstream]: https://github.com/UKHASnet/ukhasnet-rfm69

[buffer]: https://github.com/oddstr13/arduino-buffer
[buffer download]: https://github.com/oddstr13/arduino-buffer/archive/refs/heads/master.zip
[buffer origins]: https://bitbucket.org/openshell/openshell-ukhasnet-arduino
