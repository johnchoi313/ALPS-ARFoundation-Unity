using UnityEngine;
using UnityEngine.UI;

using System.IO;
using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;

public unsafe class ALPS2022 : MonoBehaviour {

	/**
	* Method to initialize ALPS. Note that ALPS iOS framework right now is hardcoded for ETC and Museumlab only, and will need a new framework for other locations.
	*/	
	[DllImport ("__Internal")]
	private static extern void _init();

	/**
	* Method to start updating ALPS with ARKit data. This should be run every frame after initializing.
	*/
	[DllImport ("__Internal")]
	private static extern void _updateARPose(float x, float y, float z, float eulerX, float eulerY, float eulerZ);

	/**
	* Method to start receiving location and transform updates from ALPS. This should be run once after initializing.
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
	* @param transform pointer to an array of floats of length 4. It represents [transX,transY,transZ,transYaw], in ARKit axes. Note that this is flipped from Unity -> X,Z,Y.
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

	[Header("Optional Info Text")]
	public Text info;
	
	[Header("ALPS-Internal Values.")]
	private float[] pLocation; 
	private float[] pAccuracy;
	private float[] pTransform; 

	[Header("ALPS->Unity Values.")]
	public Vector3 fusedLocation;
	public Vector3 fusedLocationAccuracy;
	public Vector3 fusedTranslation;
	public float fusedYaw;
	public float fusedYawAccuracy;
	
	void Awake() {
		pLocation = new float[3];
		pAccuracy = new float[4];
		pTransform = new float[4];
	}
	void Start() {
		if (Application.platform == RuntimePlatform.IPhonePlayer) {			
			//Login to ALPS system.		
			_init();
			//Begin Acoustic Location Processing System... (internal on iPad.)
			_startUpdatingLocation();
		}
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
			fusedTranslation = new Vector3(pTransform[0],pTransform[2],pTransform[1]);
			//Get new yaw
			fusedYaw = pTransform[3];
			//Get new accuracy values
			fusedLocationAccuracy = new Vector3(pAccuracy[0],pAccuracy[1],pAccuracy[2]);
			fusedYawAccuracy = pAccuracy[3];

			//------------UPDATE GLOBAL FRAME WITH NEW TRANSFORM VALUES-------------//
			//if(fusedLocationAccuracy.x < MIN_POSE_TRANSFORM_ACCURACY_X && fusedLocationAccuracy.z < MIN_POSE_TRANSFORM_ACCURACY_Y && fusedYawAccuracy < MIN_POSE_TRANSFORM_ACCURACY_R) {
				if(globalFrame != null) { //Apply new transform to global root node:
					float lookX = Mathf.Cos(fusedYaw);
					float lookY = Mathf.Sin(fusedYaw);

					globalFrame.transform.position = new Vector3(0,0,0);
					globalFrame.transform.LookAt(new Vector3(lookX, 0, lookY));
					globalFrame.transform.Rotate(0,90,0);

					globalFrame.transform.Translate(fusedTranslation.x, -fusedTranslation.y, -fusedTranslation.z);
				}
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