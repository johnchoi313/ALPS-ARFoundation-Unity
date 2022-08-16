using UnityEngine;
using UnityEngine.UI;

using System.IO;
using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;

public unsafe class ALPS2022 : MonoBehaviour {
	
	[DllImport ("__Internal")]
	private static extern void _init();

	[DllImport ("__Internal")]
	private static extern void _updateARPose(float x, float y, float z, float eulerX, float eulerY, float eulerZ);

	/**
	* Method to start receiving location and transform updates from ALPS. This should be run after initializing the ALPSUnityManager using sharedManagerWithUsername()
	*/
	[DllImport ("__Internal")]
	private static extern void _startUpdatingLocation();

	/**
	* Method to stop receiving location and transform updates from ALPS.
	*/
	[DllImport ("__Internal")]
	private static extern void _stopUpdatingLocation();

	/**
	* Method to get the current location, location and rotation accuracy and AR transform data.
	* @param location pointer to an array of floats of length 3. The current location of the device as determined by ALPS will be copied into this array as [x, y, z]
	* @param locationAccuracy pointer to an array of floats of length 4. The accuracy of the location and rotation of the device in meters as determined by ALPS will be copied into this array as [accuracyX, accuracyY, accuracyZ, accuracyRotation]
	* @param transform pointer to an array of floats of length 16. The current 3D 4x4 transformation matrix to transform ARKit's frame of reference to ALPS' frame of reference will be copied into this array as a flattened SCNMatrix4 (see https://developer.apple.com/documentation/scenekit/scnmatrix4?language=objc). The SCNMatrix4 elements are copied into the array in the following order [m11, m12, m13, m14, m21, m22, m23, m24, m31, m32, m33, m34, m41, m42, m43, m44].
	*/
	[DllImport ("__Internal")]
	private static extern void _getLocationAndTransform (float *location, float *locationAccuracy, float *transform);

	[Header("Defined ALPS Threshold Constants:")]
	public float MIN_POSE_TRANSFORM_ACCURACY_X = 0.7f; // meters
	public float MIN_POSE_TRANSFORM_ACCURACY_Y = 0.7f; // meters
	public float MIN_POSE_TRANSFORM_ACCURACY_R = 0.2f; // radians

	[Header("Set to Global Transform:")]
	public Transform globalFrame;
	public Transform camFrame;

	public bool flipGlobal = false;
	public float globalRotateOffset = 90;

	[Header("Optional Info Text")]
	public Text info;
	
	[Header("ALPS-Internal Values.")]
	private float[] pLocation; 
	private float[] pAccuracy;
	private float[] pTransform; 

	[Header("ALPS->Unity Values.")]
	public Vector3 fusedLocation;
	public Vector3 fusedLocationAccuracy;

	public Matrix4x4 fusedMatrix;
	public Vector3 fusedTranslation;
	public Quaternion fusedRotation;

	public float fusedYaw;
	public float fusedYawAccuracy;
	

	void Awake() {
		pLocation = new float[3];
		pAccuracy = new float[4];
		pTransform = new float[4];
	}
	void Start() {
		//Login to ALPS system.		
		//unsafe {
		//	fixed (char* username = USERNAME)
		//	fixed (char* password = PASSWORD)
		//	{ _init(username, password); }
		//}

		_init();

		//Begin Acoustic Location Processing System... (internal on iPad.)
		_startUpdatingLocation();
	}


	void Update () {
		//Only run ALPS system on iOS devices.
		if (Application.platform == RuntimePlatform.IPhonePlayer) {			
			//------ATTEMPT TO FUSE ALPS WITH ARKIT DATA TO GET NEW TRANSFORM DATA--------//
			_updateARPose( //Force feed ARKit camera data into ALPS for fusion:
				camFrame.position.x, camFrame.position.y, -camFrame.position.z,                        //position
				camFrame.localEulerAngles.x, camFrame.localEulerAngles.y, camFrame.localEulerAngles.z //rotation
			);
			//Get resulting fused ALPS + ARkit data:
			unsafe {
				fixed (float *_location = pLocation)
				fixed (float *_accuracy = pAccuracy)
				fixed (float *_transform = pTransform) {
					_getLocationAndTransform(_location, _accuracy, _transform);		
					//Location
					pLocation[0] = _location[0];
					pLocation[1] = _location[1];
					pLocation[2] = _location[2];
					//Accuracy
					pAccuracy[0] = _accuracy[0];
					pAccuracy[1] = _accuracy[1];
					pAccuracy[2] = _accuracy[2];
					pAccuracy[3] = _accuracy[3];
					//Transform
					pTransform[0] = _transform[0];
					pTransform[1] = _transform[1];
					pTransform[2] = _transform[2];
					pTransform[3] = _transform[3];
				}
			}

			//Get new location values
			fusedLocation = new Vector3(pLocation[0],pLocation[1],pLocation[2]);
			//Get new translation values
			fusedTranslation = new Vector3(pTransform[0],pTransform[2],pTransform[1]); //third colum is pos
			//Get new yaw
			fusedYaw = pTransform[3];
			//Get new accuracy values
			fusedLocationAccuracy = new Vector3(pAccuracy[0],pAccuracy[1],pAccuracy[2]);
			fusedYawAccuracy = pAccuracy[3];

			//------------UPDATE GLOBAL FRAME WITH NEW TRANSFORM VALUES-------------//
			//if(fusedLocationAccuracy.x < MIN_POSE_TRANSFORM_ACCURACY_X && fusedLocationAccuracy.z < MIN_POSE_TRANSFORM_ACCURACY_Y && fusedYawAccuracy < MIN_POSE_TRANSFORM_ACCURACY_R) {
				//if(globalTranslatorFrame != null && globalRotatorFrame != null) { //Apply new transform to global root node:
					//float lookX = Mathf.Cos((flipGlobal?-1:1) * fusedYaw);
					//float lookY = Mathf.Sin((flipGlobal?-1:1) * fusedYaw);

					//globalFrame.transform.position = new Vector3(0,0,0);
					//globalFrame.transform.LookAt(new Vector3(lookX, 0, lookY));
					//globalFrame.transform.Rotate(0,globalRotateOffset,0);

					//Vector3 dist = globalFrame.position - camFrame.position;
					//globalFrame.transform.position = new Vector3(fusedTranslation.x, fusedTranslation.y, fusedTranslation.z) * (flipGlobal?-1:1); //+dist
				

				if(flipGlobal) {
					
					float lookX = Mathf.Cos(-fusedYaw);
					float lookY = Mathf.Sin(-fusedYaw);

					globalFrame.transform.position = new Vector3(0,0,0);
					globalFrame.transform.LookAt(new Vector3(lookX, 0, lookY));
					globalFrame.transform.Rotate(0,globalRotateOffset,0);

					//Vector3 dist = globalFrame.position - camFrame.position;

					globalFrame.transform.position = new Vector3(-fusedTranslation.x, fusedTranslation.y, fusedTranslation.z); //+ dist;
				} 
				//If global is universe frame
				else {
					float lookX = Mathf.Cos(fusedYaw);
					float lookY = Mathf.Sin(fusedYaw);

					globalFrame.transform.position = new Vector3(0,0,0);
					globalFrame.transform.LookAt(new Vector3(lookX, 0, lookY));
					globalFrame.transform.Rotate(0,globalRotateOffset,0);

					globalFrame.transform.Translate(fusedTranslation.x, -fusedTranslation.y, -fusedTranslation.z);
				}


					//globalTranslatorFrame.localPosition = new Vector3(0,0,0);
					//globalRotatorFrame.localEulerAngles = new Vector3(0,0,0);
					//globalTranslatorFrame.localEulerAngles = new Vector3(0,0,0);


					//globalTranslatorFrame.Translate(-fusedTranslation.x, -fusedTranslation.y, fusedTranslation.z);
					//globalTranslatorFrame.RotateAround(new Vector3(0,0,0), Vector3.up, fusedYaw * 57.2958f);

					//globalRotatorFrame.Rotate(0,-fusedYaw * 57.2958f,0);

					//globalFrame.transform.Rotate(0,globalRotateOffset,0);

					//Vector3 dist = globalFrame.position - camFrame.position;
					
				
				
				//}
			//}
		}

		//Show ALPS info text		
		if(info != null) {
			info.text  = "camPosX: " + camFrame.position.x.ToString("F2") + "\r\n";
			info.text += "camPosY: " + camFrame.position.y.ToString("F2") + "\r\n";
			info.text += "camPosZ: " + camFrame.position.z.ToString("F2") + "\r\n\r\n";
			
			info.text += "camRotX: " + camFrame.localEulerAngles.x.ToString("F2") + "\r\n";
			info.text += "camRotY: " + camFrame.localEulerAngles.y.ToString("F2") + "\r\n";
			info.text += "camRotZ: " + camFrame.localEulerAngles.z.ToString("F2") + "\r\n\r\n";
			
			info.text += "locX: " + fusedLocation.x.ToString("F2") + "\r\n";
			info.text += "locY: " + fusedLocation.y.ToString("F2") + "\r\n";
			info.text += "locZ: " + fusedLocation.z.ToString("F2") + "\r\n\r\n";
			
			info.text += "transX: " + fusedTranslation.x.ToString("F2") + "\r\n";
			info.text += "transY: " + fusedTranslation.y.ToString("F2") + "\r\n";
			info.text += "transZ: " + fusedTranslation.z.ToString("F2") + "\r\n";
			info.text += "transYaw: " + fusedYaw.ToString("F2") + "\r\n\r\n";

			info.text += "accX: " + fusedLocationAccuracy.x.ToString("F2") + "\r\n";
			info.text += "accY: " + fusedLocationAccuracy.y.ToString("F2") + "\r\n";
			info.text += "accZ: " + fusedLocationAccuracy.z.ToString("F2") + "\r\n";
			info.text += "accYaw: " + fusedYawAccuracy.ToString("F2") + "\r\n\r\n";
		}
	}
}