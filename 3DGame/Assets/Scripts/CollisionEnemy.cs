using System.Collections;
using System.Collections.Generic;
using System.Security.Authentication.ExtendedProtection;
using UnityEngine;

public class CollisionEnemy : MonoBehaviour
{
    public GameOverScreen gameOverScreen;
    private void OnTriggerEnter(Collider other)
    {
        if (other.tag == "Bob")
        {
            GetComponent<Policia>().speed -= 1;
            GetComponent<Policia>().onPlayer = false;
        }

        else if (other.tag == "Gamba")
        {
            GetComponent<Policia>().speed -= 1;
            GetComponent<Policia>().onPlayer = false;
        }
        else if (other.tag == "Turn") {
            
        }
    }

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
