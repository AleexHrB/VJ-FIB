using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;
using UnityEngine.SceneManagement;

public class Collision : MonoBehaviour
{
    public Animator anim;
    public AudioClip coin;
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

        if (other.gameObject.name.Equals("rock")) {
            anim.Play("mixamo_muerte");
            GetComponentInParent<Move>().speed = new Vector3(0, 0, 10);
            impact = true;
        }
        else
        {
            GetComponent<AudioSource>().PlayOneShot(coin);
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
            GetComponentInParent<Move>().speed = new Vector3(0, 0, 0);
            //SceneManager.LoadScene("TempleRun");
        }

        if (dying)
        {
            GetComponentInParent<Move>().speed = GetComponentInParent<Move>().speed - new Vector3(0, 0, 0.02f);
        }
    }
}