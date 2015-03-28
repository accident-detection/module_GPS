# module_GPS
Implementation of Ublox Neo 6m GPS module functionalities with Arduino using TinyGPS++ library. Serial port prints various information such as longitude, latitude, altitude, speed etc. Longitude and latitude get written to an SD card in a .txt format. The .txt and .kml files are purposely separated. I didn't want to put too much load on the Arduino as file conversion will be handled on the server side.
In order to view your route in Google Earth, please copy the contents of gpsData.txt file into gpsData.kml file between the ```<coordinates>``` and ```</coordinates>``` tags.

**Note**: For some reason, when pasting a single coordinate into Google Earth or Google Maps, it works by pasting lat,lng. But for the .txt file which stores a route and is supposed to work with Google Earth, I had to have lng,lat format.

**Note2**: As this is a project done for my university, all comments and contents of print statements are in Croatian

When setting your .kml file, if you find that the route isn't shown properly, you can change altitude options between ```<altitudeMode>``` and ```</altitudeMode>``` tags. Options are:
* **Clamped to ground** - By default, all folders and placemarks are set to this option. Here, because the altitude for the placemark is locked to the ground, no height value is allowed for altitude. This ensures that the placemark remains fixed to the earth, regardless of whether terrain is on or off.
* **Clamped to sea floor** - This option is similiar to clamped to ground, the only difference is that the placemark is locked to the sea floor.
* **Relative to ground** - When this option is selected, altitude of the placemark is relative to the actual ground elevation of the view. For example, if you set 9 meters as the altitude of a placemark in Venice, Italy, the elevation of the placemark will be 9 meters above the ground because Venice is at sea level. However, if you set the same placemark above Denver, Colorado, the elevation of the placemark will be 1616 meters, because the elevation of Denver is 1607 meters. You can see this how this appears in the 3D viewer by setting elevation, tilting the view, and turning terrain on and off.
* **Relative to sea floor** - Again this option is very similiar to Relative to ground but the placemark is relative to the sea floor instead of the actual ground evelation of the view.
* **Absolute** - When this option is selected, altitude of the Placemark is above sea level. In the example above, if you have terrain on and keep altitude to 9 meters but set the altitude type to 'Absolute', the icon would disappear from view because it is actually below the level of the terrain at Denver, Colorado. You can adjust the altitude using the slider or by entering a value in meters in the 'Altitude' field.
