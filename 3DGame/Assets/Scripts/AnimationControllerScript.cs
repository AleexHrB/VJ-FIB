using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AnimationControllerScript : MonoBehaviour
{
    // Start is called before the first frame update
    public Animator anim;
    
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
