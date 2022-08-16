using UnityEngine;
using UnityEngine.UI;

using System.IO;
using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;

/*
public unsafe class ALPS : MonoBehaviour {
	
	[DllImport ("__Internal")]
	private static extern void _startUpdatingLocation();
	
	[DllImport ("__Internal")]
	private static extern void _stopUpdatingLocation();
	
	[DllImport ("__Internal")]
	private static extern void _getLocationAndTransform(float *locX, float *locY, float *locZ, float *transX, float *transY, float* transZ, float* transYaw, float* stdDevX, float* stdDevY, float* stdDevZ, float* stdDevYaw);
	
	[Header("Set to Global Transform:")]
	public Transform globalFrame;
	public Transform camFrame;
	public bool flipGlobal = false;

	[Header("Optional Info Text")]
	public Text info;
	
	[Header("ALPS Values. Read Only:")]
	public float locX;
	public float locY, locZ; 
	public float transX, transY, transZ, transYaw;
	public float stdDevX, stdDevY, stdDevZ, stdDevYaw;
	
	private float[] currLocation; 
	private float[] currTransform; 
	private float[] currLocationStdDev; 		

	// Use this for initialization
	void Start () {
		currLocation = new float[3];
		currTransform = new float[4];
		currLocationStdDev = new float[4];
	}

	void getLocationAndTransform() {
	   	fixed(float* _locX = &currLocation[0])
		fixed(float* _locY = &currLocation[1])
		fixed(float* _locZ = &currLocation[2])
		fixed(float* _transX = &currTransform[0])
		fixed(float* _transY = &currTransform[1])
		fixed(float* _transZ = &currTransform[2])
		fixed(float* _transYaw = &currTransform[3])
		fixed(float* _stdDevX = &currLocationStdDev[0])
		fixed(float* _stdDevY = &currLocationStdDev[1])
		fixed(float* _stdDevZ = &currLocationStdDev[2])
		fixed(float* _stdDevYaw = &currLocationStdDev[3]) { 
			_getLocationAndTransform(_locX, _locY, _locZ, _transX, _transY, _transZ, _transYaw, _stdDevX, _stdDevY, _stdDevZ, _stdDevYaw); 
			locX = *_locX; locY = *_locY; locZ = *_locZ;
			transX = *_transX; transY = *_transY; transZ = *_transZ; transYaw = *_transYaw;
			stdDevX = *_stdDevX; stdDevY = *_stdDevY; stdDevZ = *_stdDevZ; stdDevYaw = *_stdDevYaw;
		}
	}

	void Update () {
		//Ignore ALPS updates in editor.
		if (Application.platform == RuntimePlatform.IPhonePlayer) {
		   	getLocationAndTransform();		

			//If global is camera frame
			if(globalFrame != null) {
				if(flipGlobal) {
					
					float lookX = Mathf.Cos(-transYaw);
					float lookY = Mathf.Sin(-transYaw);

					globalFrame.transform.position = new Vector3(0,0,0);
					globalFrame.transform.LookAt(new Vector3(lookX, 0, lookY));
					globalFrame.transform.Rotate(0,90,0);

					Vector3 dist = globalFrame.position - camFrame.position;

					globalFrame.transform.position = new Vector3(-transX, transZ, transY); //+ dist;
				} 
				//If global is universe frame
				else {
					float lookX = Mathf.Cos(transYaw);
					float lookY = Mathf.Sin(transYaw);

					globalFrame.transform.position = new Vector3(0,0,0);
					globalFrame.transform.LookAt(new Vector3(lookX, 0, lookY));
					globalFrame.transform.Rotate(0,90,0);

					globalFrame.transform.Translate(transX, -transZ, -transY);
				}
			}
		}

		//Show ALPS info text		
		if(info != null) {
			info.text = "locX: " + locX.ToString("F2") + "\r\n";
			info.text += "locY: " + locY.ToString("F2") + "\r\n";
			info.text += "locZ: " + locZ.ToString("F2") + "\r\n\r\n";
			
			info.text += "transX: " + transX.ToString("F2") + "\r\n";
			info.text += "transY: " + transY.ToString("F2") + "\r\n";
			info.text += "transZ: " + transZ.ToString("F2") + "\r\n";
			info.text += "transYaw: " + transYaw.ToString("F2") + "\r\n\r\n";

			info.text += "stdDevX: " + stdDevX.ToString("F2") + "\r\n";
			info.text += "stdDevY: " + stdDevY.ToString("F2") + "\r\n";
			info.text += "stdDevZ: " + stdDevZ.ToString("F2") + "\r\n";
			info.text += "stdDevYaw: " + stdDevYaw.ToString("F2") + "\r\n\r\n";
		}
	}


}
*/