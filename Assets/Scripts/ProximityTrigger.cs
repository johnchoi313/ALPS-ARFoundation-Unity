using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ProximityTrigger : MonoBehaviour {

    public List<ParticleSystem> particles;
    
    private Transform cam;

    public float proximityThreshold = 1.0f;

    // Start is called before the first frame update
    void Start() {
        cam = Camera.main.transform;
    }

    // Update is called once per frame
    void Update() {
        
        if(Vector3.Distance(transform.position, cam.position) < proximityThreshold) {
            foreach(ParticleSystem particle in particles) { particle.Play(); }
        } else {
            foreach(ParticleSystem particle in particles) { particle.Stop(); }
        }

    }
}
