using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AnimationControllerScript : MonoBehaviour
{
    // Start is called before the first frame update
    public Animator anim;
    public AudioClip jump;

    void Start()
    {
        anim = GetComponent<Animator>();
    }

    // Update is called once per frame
    void Update()     
    {
        if (Input.GetKeyDown(KeyCode.Space) ||Input.GetKeyDown(KeyCode.UpArrow) && anim.GetCurrentAnimatorStateInfo(0).IsName("mixamo_correr"))
        {
            anim.Play("mixamo_saltar");
            GetComponentInParent<AudioSource>().PlayOneShot(jump);
            GetComponentInParent<BoxCollider>().center = new Vector3(0, 2.5f, 0);
        }
        
        else if (Input.GetKeyDown(KeyCode.DownArrow) && anim.GetCurrentAnimatorStateInfo(0).IsName("mixamo_correr"))
        {
            anim.Play("mixamo_slide");
        }

        else if (Input.GetKeyDown(KeyCode.K))
        {
            anim.Play("mixamo_muerte");
        }
    }
}
