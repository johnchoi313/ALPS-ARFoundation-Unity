using System.Collections;
using System.Collections.Generic;

using UnityEngine;
using UnityEngine.UI;

public class SizeOffsetAdjuster : MonoBehaviour {

    [Header("Values")]
    public float offsetY = 0f;
    public float offsetZ = 0f;
    public float scale = 1f;

    [Header("Sliders")]
    public Slider scaleSlider;
    public Slider offsetYSlider;
    public Slider offsetZSlider;

    public void setOffsetY(float value) { offsetY = value;
        PlayerPrefs.SetFloat("offsetY", offsetY);
    }
    public void setOffsetZ(float value) { offsetZ = value;
        PlayerPrefs.SetFloat("offsetZ", offsetZ);    
    }
    public void setScale(float value) { scale = value;
        PlayerPrefs.SetFloat("scale", scale);        
    }

    // Start is called before the first frame update
    void Start() {
        offsetYSlider.value = PlayerPrefs.GetFloat("offsetY", offsetY);
        offsetZSlider.value = PlayerPrefs.GetFloat("offsetZ", offsetZ);
        scaleSlider.value = PlayerPrefs.GetFloat("scale", scale);        
    }

    // Update is called once per frame
    void Update() {
        
        GameObject[] offsetObjects = GameObject.FindGameObjectsWithTag("OffsetObject");
        foreach(GameObject offsetObject in offsetObjects) {
            offsetObject.transform.localPosition = new Vector3(0,offsetY,offsetZ);
            offsetObject.transform.localScale = new Vector3(scale,scale,scale);
        }

    }
}