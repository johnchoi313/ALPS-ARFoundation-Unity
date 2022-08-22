# ALPS ARFoundation-Unity Example Integration Project

<img src="https://img.shields.io/badge/unity-2020.3.38f1-blue"/> <img src="https://img.shields.io/badge/platform-iOS-green"/> <img src="https://img.shields.io/badge/license-MIT-red"/> 




https://user-images.githubusercontent.com/6497727/186027742-1699954a-b9fd-4a31-9339-59028599008e.MOV

*Video of ALPS Running.*







## What version should I use?

A Unity package is either "Preview" or "Verified". The latest version of ARFoundation is usually marked as preview and may include experimental or unstable features. A "verified" package is developed targeting a specific version of Unity (though it may work with earlier version as well). All packages verified for the same version of Unity are known to work well together.

In ARFoundation, this means:

| Unity Version | ARFoundation Version |
| ------------- | -------------------- |
|    2018.4     | [1.5 (preview)](https://github.com/Unity-Technologies/arfoundation-samples/tree/1.5-preview)  |
|    2019.4     | [2.1 (verified)](https://github.com/Unity-Technologies/arfoundation-samples/tree/2.1)         |
|    2020.1     | [3.1 (verified)](https://github.com/Unity-Technologies/arfoundation-samples/tree/3.1)         |
|    2020.2     | [4.0 (verified)](https://github.com/Unity-Technologies/arfoundation-samples/tree/4.0)         |
|    2021.1     | 4.1 (verified)                                                                                |

## ARSubsystems

ARFoundation is built on "[subsystems](https://docs.unity3d.com/2019.3/Documentation/ScriptReference/Subsystem.html)" and depends on a separate package called [ARSubsystems](https://docs.unity3d.com/Packages/com.unity.xr.arsubsystems@4.1/manual/index.html). ARSubsystems defines an interface, and the platform-specific implementations are in the [ARCore](https://docs.unity3d.com/Packages/com.unity.xr.arcore@4.1/manual/index.html) and [ARKit](https://docs.unity3d.com/Packages/com.unity.xr.arkit@4.1/manual/index.html) packages. ARFoundation turns the AR data provided by ARSubsystems into Unity `GameObject`s and `MonoBehavour`s.

The `master` branch is compatible with Unity 2019.3 and later. For 2018.4, see the [1.5-preview branch](https://github.com/Unity-Technologies/arfoundation-samples/tree/1.5-preview).
