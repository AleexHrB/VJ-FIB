using System.Collections;
using System.Collections.Generic;
using System.Security.Authentication.ExtendedProtection;
using UnityEngine;

public class CollisionEnemy : MonoBehaviour
{
    public GameOverScreen gameOverScreen;
    private void OnTriggerEnter(Collider other)
    {
        if (other.tag == "Bob" || other.tag == "Gamba")
        {
            GetComponent<Policia>().speed -= 1;
            GetComponent<Policia>().onPlayer = false;
        }
    }
}
