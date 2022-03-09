using System.Collections;
using System.Collections.Generic;

using UnityEngine;
using UnityEngine.UI;

public class SizeOffsetAdjuster : MonoBehaviour {

    [Header("Values")]
    public float offsetY = 0f;
    public float offsetZ = 0f;
    public float scale = 1f;
    public int angle = 0;

    [Header("Sliders")]
    public Slider scaleSlider;
    public Slider offsetYSlider;
    public Slider offsetZSlider;

    [Header("Material")]
    public Material standardMaterial;
    public Material occluderMaterial;

    public void setOffsetY(float value) { offsetY = value;
        PlayerPrefs.SetFloat("offsetY", offsetY);
    }
    public void setOffsetZ(float value) { offsetZ = value;
        PlayerPrefs.SetFloat("offsetZ", offsetZ);    
    }
    public void setScale(float value) { scale = value;
        PlayerPrefs.SetFloat("scale", scale);        
    }
    public void rotate90() { angle++; angle = angle % 4;
        PlayerPrefs.SetInt("angle", angle);        
    }

    public void setStandardMaterial() {
        GameObject[] occluders = GameObject.FindGameObjectsWithTag("Occluder");
        foreach(GameObject occluder in occluders) {
            occluder.GetComponent<Renderer>().material = standardMaterial;
        }
    }
    public void setOccluderMaterial() {
        GameObject[] occluders = GameObject.FindGameObjectsWithTag("Occluder");
        foreach(GameObject occluder in occluders) {
            occluder.GetComponent<Renderer>().material = occluderMaterial;
        }
    }

    // Start is called before the first frame update
    void Start() {
        offsetYSlider.value = PlayerPrefs.GetFloat("offsetY", offsetY);
        offsetZSlider.value = PlayerPrefs.GetFloat("offsetZ", offsetZ);
        scaleSlider.value = PlayerPrefs.GetFloat("scale", scale);        
     
        offsetY = PlayerPrefs.GetFloat("offsetY", offsetY);
        offsetZ = PlayerPrefs.GetFloat("offsetY", offsetZ);
        scale = PlayerPrefs.GetFloat("scale", scale);    
        angle = PlayerPrefs.GetInt("angle", angle);    
    }

    // Update is called once per frame
    void Update() {
        
        GameObject[] offsetObjects = GameObject.FindGameObjectsWithTag("OffsetObject");
        foreach(GameObject offsetObject in offsetObjects) {
            offsetObject.transform.localPosition = new Vector3(0,offsetY,offsetZ);
            offsetObject.transform.localScale = new Vector3(scale,scale,scale);
            offsetObject.transform.localEulerAngles = new Vector3(angle * 90f, 0, 0);
        }

    }
}
