using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PigeonRandomizer : MonoBehaviour {

    public Animator animator;

    public float scaleMin = 1;
    public float scaleMax = 2;

    public float animMin = .3f;
    public float animMax = 2;

    public float randomPos = 0.5f;

    // Start is called before the first frame update
    void Start() {
        transform.Translate(Random.Range(randomPos,-randomPos),0,Random.Range(randomPos,-randomPos));
        transform.localScale *= Random.Range(scaleMin,scaleMax);
        transform.Rotate(0,Random.Range(0,360),0);
        animator.speed = Random.Range(animMin,animMax);
        animator.Play("idle",-1,Random.Range(0.0f,1.0f));
    }
}
