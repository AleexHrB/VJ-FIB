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

        if (other.tag == "Bob")
        {
            GetComponent<AudioSource>().PlayOneShot(crash);
            anim.Play("mixamo_chocar");
            GetComponentInParent<Move>().speed = 0.0f;
            impact = true;
            gameOverScreen.gameOver();
        }
        else if (other.tag == "Rock")
        {
            anim.Play("mixamo_tropezar");
            enemies.gameObject.SetActive(true);
            enemies.GetComponent<Policia>().toPlayer(transform.parent.position, GetComponentInParent<Move>().direction, GetComponentInParent<Move>().lane);


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

            enemies.transform.position = new Vector3(0, 100, 0);

            if (gameObject.GetComponentInParent<Move>().GodMode) {
                gameObject.GetComponentInParent<Move>();
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

        else if (other.tag == "MidLane")
        {
            GetComponentInParent<Move>().stopTurn(1);
        }

        else if (other.tag == "LeftLane")
        {
            GetComponentInParent<Move>().stopTurn(0);
        }
        else if (other.tag == "RightLane")
        {
            GetComponentInParent<Move>().stopTurn(2);
        }

        else if (other.tag == "RighTurn") {
            GetComponentInParent<Move>().lane = 2;
            if (GetComponentInParent<Move>().GodMode)
            {
                GetComponentInParent<Move>().autoTurn(true);
            }
        }

        else if (other.tag == "LefTurn")
        {
            GetComponentInParent<Move>().lane = 0;
            if (GetComponentInParent<Move>().GodMode) {
                GetComponentInParent<Move>().autoTurn(false);
            }
        }

        else if (other.tag == "MidTurn")
        {
            GetComponentInParent<Move>().lane = 1;
        }
        //SceneManager.LoadScene("TempleRun");
    }

    private void OnTriggerExit(Collider other)
    {

        if (other.tag == "Turn")
        {

            GetComponentInParent<Move>().canRotate = false;
            if (enemies.GetComponent<Policia>().onPlayer)
            {
                enemies.transform.position = Vector3.zero;
                enemies.GetComponent<Policia>().toPlayer(transform.parent.position, GetComponentInParent<Move>().direction, GetComponentInParent<Move>().lane, true);
            }
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
