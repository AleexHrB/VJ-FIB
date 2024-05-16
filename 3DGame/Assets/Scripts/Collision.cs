using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class Collision : MonoBehaviour
{
    public Animator anim;
    public AudioClip coin;
    public AudioClip woah;
    public AudioClip falling;
    private bool impact;
    private bool dying;

    private void Start()
    {
        anim = GetComponentInChildren<Animator>();
        impact = false;
        dying = false;
    }
    private void OnTriggerEnter(Collider other)
    {

        if (other.tag == "Rock") {
            anim.Play("mixamo_muerte");
            GetComponentInParent<Move>().speed = 10.0f;
            impact = true;
        }
        else if (other.tag == "Coin")
        {
            GetComponent<AudioSource>().PlayOneShot(coin);
            GameObject.Find("ScoreText").GetComponent<Score>().score += 1000;
        }
        else if (other.tag == "Turn" || other.tag == "Tea")
        {
            GetComponentInParent<Move>().rotationCenter = other.bounds.center;
            GetComponentInParent<Move>().canRotate = true;
            
            if (other.tag == "Tea")
            {
                GetComponentInParent<Move>().Tea = true;
            }
        }
        else if (other.tag == "Fall")
        {
            anim.Play("mixamo_caer");
            GetComponentInParent<Move>().falling = true;
            GetComponent<AudioSource>().PlayOneShot(woah);
            GetComponent<AudioSource>().PlayOneShot(falling);
        }
        //SceneManager.LoadScene("TempleRun");
    }

    private void OnTriggerExit(Collider other)
    {

        if (other.tag == "Turn")
        {

            GetComponentInParent<Move>().canRotate = false;
        }

        //SceneManager.LoadScene("TempleRun");
    }

    private void Update()
    {
        if (impact && anim.GetCurrentAnimatorStateInfo(0).IsName("mixamo_muerte"))
        {
            dying = true;
        }
        
        else if (dying && !anim.GetCurrentAnimatorStateInfo(0).IsName("mixamo_muerte")) {
            impact = false;
            dying = false;
            GetComponentInParent<Move>().speed = 0.0f;
            //SceneManager.LoadScene("TempleRun");
        }

        if (dying)
        {
            GetComponentInParent<Move>().speed -= 0.02f;
        }
    }
}
