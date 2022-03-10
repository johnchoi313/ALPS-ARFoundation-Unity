using System.Collections;
using System.Collections.Generic;

using UnityEngine;
using UnityEngine.UI;

public class SizeOffsetAdjuster : MonoBehaviour {

    [Header("Values")]
    public float offsetX = 0f;
    public float offsetY = 0f;
    public float offsetZ = 0f;
    
    public float scale = 1f;
    public int angle = 0;

    public float angleX = 0f;
    public float angleY = 0f;
    public float angleZ = 0f;

    [Header("Sliders")]
    public Slider scaleSlider;
    public Slider offsetXSlider;
    public Slider offsetYSlider;
    public Slider offsetZSlider;
    public Slider angleXSlider;
    public Slider angleYSlider;
    public Slider angleZSlider;

    [Header("Material")]
    public Material standardMaterial;
    public Material occluderMaterial;
    public Material smokeMaterial;
    
    [Header("Colors")]
    public Color smokeA;
    public Color smokeB;
    
    [Header("Pulse Speed")]
    public float pulseSpeed = 8f;
   
    public void setOffsetX(float value) { offsetX = value;
        PlayerPrefs.SetFloat("offsetX", offsetX);
    }
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

    public void rotateX(float value) { angleX = value;
        PlayerPrefs.SetFloat("angleX", angleX);        
    }
    public void rotateY(float value) { angleY = value;
        PlayerPrefs.SetFloat("angleY", angleY);        
    }
    public void rotateZ(float value) { angleZ = value;
        PlayerPrefs.SetFloat("angleZ", angleZ);        
    }
    

    public void setStandardMaterial() {
        GameObject[] occluders = GameObject.FindGameObjectsWithTag("Occluder");
        foreach(GameObject occluder in occluders) {
            occluder.SetActive(true);
            occluder.GetComponent<Renderer>().material = standardMaterial;
        }
    }
    public void setOccluderMaterial() {
        GameObject[] occluders = GameObject.FindGameObjectsWithTag("Occluder");
        foreach(GameObject occluder in occluders) {
            occluder.SetActive(true);
            occluder.GetComponent<Renderer>().material = occluderMaterial;
        }
    }
    public void setHidden() {
        GameObject[] occluders = GameObject.FindGameObjectsWithTag("Occluder");
        foreach(GameObject occluder in occluders) {
            occluder.SetActive(!occluder.activeSelf);
        }
    }
    
    // Start is called before the first frame update
    void Start() {
        
        offsetXSlider.value = PlayerPrefs.GetFloat("offsetX", offsetX);
        offsetYSlider.value = PlayerPrefs.GetFloat("offsetY", offsetY);
        offsetZSlider.value = PlayerPrefs.GetFloat("offsetZ", offsetZ);
             
        angleXSlider.value = PlayerPrefs.GetFloat("angleX", angleX);
        angleYSlider.value = PlayerPrefs.GetFloat("angleY", angleY);
        angleZSlider.value = PlayerPrefs.GetFloat("angleZ", angleZ);

        scaleSlider.value = PlayerPrefs.GetFloat("scale", scale);        

        offsetX = PlayerPrefs.GetFloat("offsetX", offsetX);
        offsetY = PlayerPrefs.GetFloat("offsetY", offsetY);
        offsetZ = PlayerPrefs.GetFloat("offsetY", offsetZ);
        scale = PlayerPrefs.GetFloat("scale", scale);    
        angle = PlayerPrefs.GetInt("angle", angle);    

        angleX = PlayerPrefs.GetFloat("angleX", angleX);
        angleY = PlayerPrefs.GetFloat("angleY", angleY);
        angleZ = PlayerPrefs.GetFloat("angleZ", angleZ);

    }

    // Update is called once per frame
    void Update() {
        
        GameObject[] offsetObjects = GameObject.FindGameObjectsWithTag("OffsetObject");
        foreach(GameObject offsetObject in offsetObjects) {
            offsetObject.transform.localPosition = new Vector3(offsetX,offsetY,offsetZ);
            offsetObject.transform.localScale = new Vector3(scale,scale,scale);
            offsetObject.transform.localEulerAngles = new Vector3(angle * 90f + angleX, angleY, angleZ);
        }

        smokeMaterial.SetColor("_TintColor", Color.Lerp(smokeA, smokeB, Mathf.Sin(Time.time*pulseSpeed)));

    }
}
