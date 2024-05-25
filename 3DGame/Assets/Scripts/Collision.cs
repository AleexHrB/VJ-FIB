using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEditor;
using UnityEditor.Experimental.GraphView;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class Collision : MonoBehaviour
{
    public Animator anim;
    public AudioClip coin;
    public AudioClip woah;
    public AudioClip falling;
    public AudioClip crash;
    public AudioClip ding;
    public GameObject pollo;
    private bool impact;
    private bool dying;
    public GameOverScreen gameOverScreen;
    public GameObject enemies;
    private void Start()
    {
        anim = GetComponentInChildren<Animator>();
        impact = false;
        dying = false;
    }
    private void OnTriggerEnter(Collider other)
    {

        if (other.tag == "Bob") {
            GetComponent<AudioSource>().PlayOneShot(crash);
            anim.Play("mixamo_chocar");
            GetComponentInParent<Move>().speed = 0.0f;
            impact = true;
            gameOverScreen.gameOver();
        }
        else if (other.tag == "Rock")
        {
            print("Roca");
            Vector3 moveLane = GetComponentInParent<Move>().direction.x != 0 ? new Vector3 (0, 0, 1) : new Vector3 (1, 0, 0);
            anim.Play("mixamo_tropezar");
            enemies.GetComponent<Policia>().toPlayer(transform.parent.position - 2.5f*moveLane * (GetComponentInParent<Move>().lane - 1), GetComponentInParent<Move>().direction);
            
           
            //GetComponentInParent<Move>().speed = 1.0f;
            
        }

        else if (other.tag == "Poli")
        {
            anim.Play("mixamo_pillado");
            GetComponentInParent<Move>().speed = 0.0f;

        }


        else if (other.tag == "Gamba")
        {
            GetComponentInParent<Move>().speed = 0.0f;
            Instantiate(pollo, transform.position, transform.rotation);
            this.gameObject.transform.GetChild(0).gameObject.SetActive(false);
            GetComponent<AudioSource>().PlayOneShot(ding);
            gameOverScreen.gameOver();

        }



        else if (other.tag == "Coin")
        {
            GetComponent<AudioSource>().PlayOneShot(coin);
            GameObject.Find("ScoreText").GetComponent<Score>().score += 100;
            Destroy(other.gameObject, 0);
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
            gameOverScreen.gameOver();
        }

        else if (other.tag == "MidLane") {
            GetComponentInParent<Move>().stopTurn(1);
        }

        else if ( other.tag == "LeftLane")
        {
            GetComponentInParent<Move>().stopTurn(0);
        }
        else if (other.tag == "RightLane")
        {
            GetComponentInParent<Move>().stopTurn(2);
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
