# ALPS ARFoundation-Unity Example Integration Project

<img src="https://img.shields.io/badge/unity-2020.3.38f1-blue"/> <img src="https://img.shields.io/badge/platform-iOS-green"/> <img src="https://img.shields.io/badge/license-MIT-red"/> 

The **Acoustic Location Processing System (ALPS)** by [Yodellabs](https://www.yodellabs.com/) is a markerless indoor positioning system for iOS smartphones and tablets (iPhones and iPads with ARkit compatibility). ALPS uses low-cost, energy harvesting ultrasound beacons to enable high accuracy localization applications such as multi-user augmented reality, fine grained retail analytics and next generation assistive technologies. 

https://user-images.githubusercontent.com/6497727/186274526-404aadf5-463e-43ac-8a1d-4362eee6932e.MOV

*Video of ALPS Running at the MuseumLab of Children's Museum of Pittsburgh, above.*


This repository integrates the ALPS iOS Framework with Unity's ARFoundation by providing an easy-to-use C# wrapper. 
This has been tested to work on Unity 2020.3.38f1, and will likely work on later versions as well. For more information about ARFoundation, please visit this link: https://github.com/Unity-Technologies/arfoundation-samples . ARFoundation has already been installed and configured in this repository, so you shouldn't need to change any settings for ARFoundation, unless you change the Unity version.


## Usage Notes

###Locations
This library has been configured to work at only **two** (2) locations where the ALPS system has already been physically installed, calibrated and configured. These locations are as follows:

* **Carnegie Mellon University Entertainment Technology Center** *(1st Floor, Randy Pausch Auditorium)* <br/>
700 Technology Dr, Pittsburgh, PA 15219
* **Children's Museum of Pittsburgh** *(1st Floor, MuseumLab TechLab)* <br/>
6 Allegheny Square E Suite 101, Pittsburgh, PA 15212


![CMU ETC](/ReadmeImages/cmuetc.jpg) <br/>
*Carnegie Mellon University's Entertainment Technology Center, main building.*

![Museum Lab](/ReadmeImages/museumlab.jpg) <br/>
*Children's Museum of Pittsburgh, MuseumLab building.*

###Running the ALPS app
To use the app, simply run the iOS app. Note that an active internet connection is required to connect to the ALPS positioning system! When the app is active, the installed ALPS beacons should automatically turn on and begin beaconing location data. When the ALPS system is not in use, they should automatically turn on and go to standby mode after 100 seconds of no activity.

![Museum Lab](/ReadmeImages/ALPS_sysadmin.png) <br/>

If for whatever reason the ALPS beacons do not automatically turn on (noted by a green blinking LED state on the ALPS base station), log in to the online ALPS system administration page at https://etc.alps.yodellabs.com/, go to the **Base Stations** tab and switch the Base Station at the correct location to *"Beaconing"* mode, as shown in the image above. The login username is `ETC` and the password is `**********` *(Note: this is not the actual password. If you need to know what the login credentials are, ask an appropriate administrator for support)*.

If the iOS App compiled and launched correctly, it should run now and connect to the ALPS system and update the location of the iOS device. To fully localize and converge on an accurate position/rotation, you may need to slowly walk around with the iOS device, facing the iOS device towards the ground at a 45 degree angle for around 30-60 seconds or until the ALPS positioning system successfully triangulates the iOS device's position.

## Unity Editor Notes

###Preparing an ARKit scene for ALPS

![ALPS Manager Info](/ReadmeImages/ALPS_Manager_Info.png) <br/>
To prepare an ARKit scene for ALPS, you just need to plop in the following prefabs from the prefabs folder into your scene:

* **GlobalFrame (ETC)** OR **GlobalFrame (MuseumLab)** <br/>
This is the global root node for ALPS, where everything should be parented under. This object must have a scale of `(-1,0,0)`. Note that you pick the GlobalFrame prefab based on which location you want to build your app for.
* **ALPS Manager** <br/>
This manages the ALPS connection. You will need to assign the `CamFrame` to the `AR Camera` (provided by ARFoundation), the `GlobalFrame` to an object representing the global root node, and `Info` to a text object where basic ALPS debugging info will be dumped.  
* **ALPS Canvas** <br/>
This contains a useful canvas with some basic text for debugging ALPS positioning.

![ALPS ETC Layout](/ReadmeImages/ALPS_ETC_Layout.jpg) <br/>
*This image above shows the beacon locations at CMU's ETC (marked by colored cubes).*

![Global Frame](/ReadmeImages/GlobalFrame.png) <br/>
*This image shows that the `GlobalFrame` object has a scale of `(-1,0,0)`.*

## Compilation

### Build Settings
![Build Settings](/ReadmeImages/BuildSettings.jpg) <br/>
There are three major scenes in the demo app: 

* **ALPS Scene Picker** *(This just allows the user to select the scene that they will be testing.)*
* **ALPS ETC** *This is a demo scene showing a floor map and beacon locations at the ETC.*
* **ALPS MuseumLab** *This is a demo scene showing a floor map and beacon locations at the MuseumLab.*

Note that the build target is for **iOS**.

### Player Settings
![Project Settings](/ReadmeImages/ProjectSettings.jpg) <br/>
In the Player Settings, make sure we have the following sections set correctly:

1. Set the **Bundle Identifier** to your preference.
2. Set the **Scripting Backend** to `IL2CPP`.
3. Set the **API Compatibility Level** to `.NET 4.0`.
4. Make sure **Camera Usage Description** has something filled in.
5. Make sure **Microphone Usage Description** has something filled in.
6. Make sure **Location Usage Description** has something filled in.

Then you can go to `File -> Build Settings -> Build` and Run to create an XCode project.

## XCode Settings
After Unity successfully builds an XCode project, we will need to do two things:

1. **Assigning a team** (this is required for all iOS apps, regardless of whether or not it was made in Unity).
2. **Assigning additional usage permissions** (needed by the ALPS system).

See below for more info:

### Adding Team and Signing
![XCode Team](/ReadmeImages/XCode_Team.jpg) <br/>
*Assign a team in the **Signing and Capabilities** tab. If you've never built for iOS before, you will need to create an Apple Developer account so you can fill this in here.*

### Adding Usage Permissions
![XCode Permissions](/ReadmeImages/XCode_Permissions.jpg) <br/>
For XCode to compile correctly and have the Unity iOS app not immediately crash upon successful compilation and push, we need the following permissions enabled in `XCode -> Unity-iPhone -> Info`:  

* `NSBluetoothPeriperhalUsageDescription `
* `NSBluetoothAlwaysUsageDescription`

The following permissions should have already been added by Unity in the previous step, but if they have not been enabled, you will need to enable them in XCode: 

* `NSLocationAlwaysAndWhenInUseUsageDescription`
* `NSLocationUsageDescription`
* `NSMicrophoneUsageDescription`
* `NSCameraUsageDescription`

When all of this has been set correctly, you should be able to press the compile and run button in XCode, which will build, push, and then launch the app on your connected iOS device.

Have fun! :)

*For more information about how to build an iOS app for Unity, refer to the following links:*

* https://www.juegostudio.com/blog/ios-game-development-via-unity-guide-for-beginners
* https://docs.unity3d.com/Manual/iphone.html

## This project was made possible with the support of

 <br/>

###Yodel Labs

![ALPS Logo](/ReadmeImages/alps-logo-dark.png) <br/>

[**Yodel Labs**](https://www.yodellabs.com/
) is a Carnegie Mellon University spinout founded in 2017. Our mission is to provide the most accurate location services in the mobile device industry, enabling your mobile app to bridge the gap between the virtual and the physical world.

 <br/>

###Carnegie Mellon University Entertainment Technology Center

![ETC Logo](/ReadmeImages/etc_logo.jpg) <br/>

Carnegie Mellon University's [**Entertainment Technology Center (ETC)**](https://www.etc.cmu.edu/) was founded in 1998 with Randy Pausch and Don Marinelli as the co-directors. The faculty and staff worked together to articulate our academic mission which focuses on educational goals and creative development. And we also created an R&D Agenda exploring transformational games, innovation by design and interactive storytelling. Throughout, we work to prepare students to graduate as creative professionals The ETC's unique, two-year, Master of Entertainment Technology (MET) degree was founded as a joint venture between Carnegie Mellon University’s School of Computer Science and the College of Fine Arts.  The MET is currently considered a terminal degree.

 <br/>

###Children's Museum of Pittsburgh MuseumLab

![MuseumLab Logo](/ReadmeImages/museumlab_Logo.png) <br/>

[**Children’s Museum of Pittsburgh**](https://pittsburghkids.org/) has grown along with your family, creating [**MuseumLab**](https://museumlab.org/) as a place where kids 10+ can have cutting-edge experiences in art, tech and making. It’s just the thing for their inquiring minds, increasing skills and independent inclinations. It all takes place in a “beautiful ruin” located right next door to the Children’s Museum, the former Carnegie Free Library of Allegheny. In creating MuseumLab, we renovated the building to reveal much of its original 1890 archways, columns and mosaic floors, and designed a unique space that honors the past while welcoming the future. And with the creation of MuseumLab, we’ve created the largest cultural campus for children in the country. Right here in Pittsburgh.

## Third Party Assets Used (FREE)
* azixMcAze | Unity-UIGradient (FREE) <br/>
https://github.com/azixMcAze/Unity-UIGradient

* doomlaser | DepthMask-Unity-Shader (FREE) <br/>
https://github.com/doomlaser/DepthMask-Unity-Shader

* SpaceMadness | Lunar Mobile Console - FREE (FREE) <br/> 
https://assetstore.unity.com/packages/tools/gui/lunar-mobile-console-free-82881

* Ciconia Studio | Free Double Sided Shaders (FREE) <br/>
https://assetstore.unity.com/packages/vfx/shaders/free-double-sided-shaders-23087

* OmniSAR Technologies | Lite FPS Counter - Probably the world's fastest FPS counter (FREE) <br/>
https://assetstore.unity.com/packages/tools/integration/lite-fps-counter-probably-the-world-s-fastest-fps-counter-132638