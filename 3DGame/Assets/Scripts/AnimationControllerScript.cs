using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AnimationControllerScript : MonoBehaviour
{
    // Start is called before the first frame update
    public Animator anim;
    public AudioClip jump;
    public AudioClip slide;
    public GameOverScreen gameOverScreen;

    void Start()
    {
        anim = GetComponent<Animator>();
    }

    public void Slide() {
        if (!anim.GetCurrentAnimatorStateInfo(0).IsName("mixamo_slide"))
        {
            GetComponentInParent<AudioSource>().PlayOneShot(slide);
            anim.Play("mixamo_slide");
        }
        
        
        GetComponentInParent<BoxCollider>().center = new Vector3(0, 0.2f, 0);
    }

    public void Jump()
    {
        if (!anim.GetCurrentAnimatorStateInfo(0).IsName("mixamo_saltar")) { 
            GetComponentInParent<AudioSource>().PlayOneShot(jump);
            anim.Play("mixamo_saltar");
        }
        
        GetComponentInParent<BoxCollider>().center = new Vector3(0, 2.5f, 0);
    }

    // Update is called once per frame
    void Update()     
    {
        if (Input.GetKeyDown(KeyCode.Space) || Input.GetKeyDown(KeyCode.UpArrow) && !anim.GetCurrentAnimatorStateInfo(0).IsName("mixamo_saltar") && !GetComponentInParent<Move>().dead)
        {
            Jump();
        }

        else if (Input.GetKeyDown(KeyCode.DownArrow) && !anim.GetCurrentAnimatorStateInfo(0).IsName("mixamo_slide") && !GetComponentInParent<Move>().dead)
        {
            Slide();
        }

        else if (anim.GetCurrentAnimatorStateInfo(0).IsName("mixamo_correr"))
        {
            GetComponentInParent<BoxCollider>().center = new Vector3(0, 1.29f, 0);
        }

        else if (anim.GetCurrentAnimatorStateInfo(0).IsName("muerto")) {
            gameOverScreen.gameOver();
        }
    }
}
