# module_GPS
Implementation of Ublox Neo 6m GPS module functionalities with Arduino using TinyGPS++ library. Serial port prints various information such as longitude, latitude, altitude, speed etc. Longitude and latitude get written to an SD card in a .txt format. The .txt and .kml files are purposely separated. I didn't want to put too much load on the Arduino as file conversion will be handled on the server side.
In order to view your route in Google Earth, please copy the contents of gpsData.txt file into gpsData.kml file between the <coordinates> and </coordinates> tags.

Note: For some reason, when pasting a single coordinate into Google Earth or Google Maps, it works by pasting lat,lng. But for the .txt file which stores a route and is supposed to work with Google Earth, I had to have lng,lat format.

Note2: As this is a project done for my university, all comments and contents of print statements are in Croatian
