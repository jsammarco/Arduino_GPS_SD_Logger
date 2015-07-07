# Arduino GPS SD Logger
Logging gps data with an Arduino UNO / $8 GPS Module / SD Shield with Ethernet
![image](http://consultingjoe.com/includes/images/arduino_gps_logger.jpg)

The GPS is connected with software serial over pins 2/3 3.3V
**Receive: 2
Transmit: 3 Power: 3.3v**

**Note:** I plugged into 5v on accedent and it didn't fry it but I don't think it was working for me either. So just use 3.3v.

**Note:** If the GPS Baud doesn't work with 9600 try 4800 depending on firmware. Also make sure your communicating at 4800 with serial monitor if you are testing. 9600 may work but I read the cpu would be over worked.


Uses the TinyGPS++ library. So download and install that in your Arduino IDE.

###The hardware used was an Arduino UNO and the items listed below.

#####Seeed W5200 Ethernet Shield (MicroSD/I2C/UART/Ethernet) ($10)
[eBay Search for Seeed W5200 Ethernet Shield](http://www.ebay.com/sch/i.html?_from=R40&_trksid=p2047675.m570.l1313.TR0.TRC0.A0.H0.XSeeed+W5200+Ethernet+Shield.TRS5&_nkw=Seeed+W5200+Ethernet+Shield&_sacat=0)
#####GPS Module (Serial/USB) ($8)
Max. update rate. 4 Hz - Hardware Specs Below

http://www.u-blox.com/images/downloads/Product_Docs/PCI-5S_Prod_Summary(GPS.G5-PS5-07000).pdf

[eBay Search for U-blox PCI-5S](http://www.ebay.com/sch/i.html?_from=R40&_trksid=p2050601.m570.l1313.TR0.TRC0.H0.XU-blox+PCI-5S.TRS0&_nkw=U-blox+PCI-5S&_sacat=0)
#####GPS Antenna (u.fl) ($5)
[eBay Search for Antennas](http://www.ebay.com/sch/i.html?_odkw=u-blox+gps+pci-5s&_sop=15&_osacat=0&_from=R40&_trksid=p2045573.m570.l1313.TR0.TRC0.H0.Xgps+antenna+u.fl&_nkw=gps+antenna+u.fl&_sacat=0)

######*Example Data Stored to MicroSD in file GPS.txt*
	44.988014,-93.582573,0,7/7/2015 02:47:24.00
	44.988014,-93.582573,0,7/7/2015 02:47:24.00
	44.988014,-93.582581,0,7/7/2015 02:47:25.00
	44.988010,-93.582581,0,7/7/2015 02:47:26.00
	44.988010,-93.582581,0,7/7/2015 02:47:27.00
	44.988010,-93.582581,0,7/7/2015 02:47:28.00
	44.988010,-93.582581,0,7/7/2015 02:47:28.00
	44.988007,-93.582581,0,7/7/2015 02:47:29.00
	44.988007,-93.582581,0,7/7/2015 02:47:29.00
	44.988007,-93.582581,0,7/7/2015 02:47:30.00
	44.988007,-93.582581,0,7/7/2015 02:47:31.00
	44.988010,-93.582581,0,7/7/2015 02:47:32.00
