using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEditor;
//using UnityEditor.Experimental.GraphView;
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
    public AudioClip rock;

    public GameObject pollo;
    public GameObject particles;

    public GameOverScreen gameOverScreen;
    public GameObject enemies;
    public GameObject score;

    private void Start()
    {
        anim = GetComponentInChildren<Animator>();
    }

    private void OnTriggerEnter(Collider other)
    {
        if (!GetComponentInParent<Move>().GodMode) {
            switch (other.tag)
            {
                case "Bob":
                    GetComponent<AudioSource>().PlayOneShot(crash);
                    anim.Play("mixamo_chocar");
                    GetComponentInParent<Move>().speed = 0.0f;
                    score.GetComponent<Score>().dead = true;
                    GetComponentInParent<Move>().dead = true;
                    break;

                case "Rock":
                    GetComponent<AudioSource>().PlayOneShot(rock);
                    anim.Play("mixamo_tropezar");
                    enemies.gameObject.SetActive(true);
                    enemies.GetComponent<Policia>().toPlayer(GetComponentInParent<Move>().center, GetComponentInParent<Move>().direction, 1);

                    //GetComponentInParent<Move>().speed = 1.0f;
                    break;

                case "Poli":
                    anim.Play("mixamo_pillado");
                    GetComponentInParent<Move>().speed = 0.0f;
                    score.GetComponent<Score>().dead = true;
                    GetComponentInParent<Move>().dead = true;
                    enemies.GetComponent<Policia>().dance();
                    break;

                case "Gamba":
                    GetComponentInParent<Move>().speed = 0.0f;
                    Instantiate(pollo, transform.position, transform.rotation);
                    Instantiate(particles, transform.position, Quaternion.Euler(-90, 0, 0));
                    this.gameObject.transform.GetChild(0).gameObject.SetActive(false);
                    GetComponent<AudioSource>().PlayOneShot(ding);
                    gameOverScreen.gameOver();
                    score.GetComponent<Score>().dead = true;
                    GetComponentInParent<Move>().dead = true;
                    break;

                default:
                    break;
            }
        }

        switch (other.tag) {
            case "Coin":
                GetComponent<AudioSource>().PlayOneShot(coin);
                GameObject.Find("ScoreText").GetComponent<Score>().score += 100;
                Destroy(other.gameObject, 0);
                break;

            case "Turn":
                GetComponentInParent<Move>().rotationCenter = other.bounds.center;
                GetComponentInParent<Move>().canRotate = true;
                enemies.transform.position = new Vector3(0, 100, 0);
                break;

            case "Tea":
                GetComponentInParent<Move>().rotationCenter = other.bounds.center;
                GetComponentInParent<Move>().canRotate = true;
                if (gameObject.GetComponentInParent<Move>().GodMode)
                {
                    gameObject.GetComponentInParent<Move>().autoTurn(false);
                }
                enemies.transform.position = new Vector3(0, 100, 0);
                break;

            case "Fall":
                anim.Play("mixamo_caer");
                GetComponentInParent<Move>().falling = true;
                GetComponent<AudioSource>().PlayOneShot(woah);
                GetComponent<AudioSource>().PlayOneShot(falling);
                score.GetComponent<Score>().dead = true;
                GetComponentInParent<Move>().dead = true;
                GetComponentInParent<Move>().speed = 0;
                break;

            case "MidLane":
                GetComponentInParent<Move>().lane = 1;
                break;

            case "LeftLane":
                GetComponentInParent<Move>().lane = 0;
                break;

            case "RightLane":
                GetComponentInParent<Move>().lane = 2;
                break;

            case "RighTurn":
                GetComponentInParent<Move>().lane = 2;
                if (GetComponentInParent<Move>().GodMode)
                {
                    GetComponentInParent<Move>().autoTurn(true);
                }
                break;

            case "LefTurn":
                GetComponentInParent<Move>().lane = 0;
                if (GetComponentInParent<Move>().GodMode)
                {
                    GetComponentInParent<Move>().autoTurn(false);
                }
                break;

            case "MidTurn":
                GetComponentInParent<Move>().lane = 1;
                break;

            default:
                break;
        }
    }

    private void OnTriggerExit(Collider other)
    {

        if (other.tag == "Turn" || other.tag == "Tea")
        {

            GetComponentInParent<Move>().canRotate = false;
            if (enemies.GetComponent<Policia>().onPlayer)
            {
                enemies.transform.position = new Vector3(0,100,0);
                enemies.GetComponent<Policia>().toPlayer(GetComponentInParent<Move>().center, GetComponentInParent<Move>().direction, 1, true);
            }
        }
    }
}
