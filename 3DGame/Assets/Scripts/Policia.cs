using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Policia : MonoBehaviour
{
    public bool onPlayer;
    public float speed;
    public Vector3 direction;
    private float initSpeed;
    // Start is called before the first frame update

    public void toPlayer(Vector3 posPlayer, Vector3 dir) {
        if (onPlayer) {
            speed += 2.0f;
        }

        else
        {
            direction = dir;
            transform.position = posPlayer - direction * 3;
            speed = initSpeed;
            GetComponent<Policia>().onPlayer = true;
        }
        
    }

    void Start()
    {
        direction = new Vector3(0, 0, 1);
        speed = 10.0f;
        initSpeed = speed;
        onPlayer = true;
    }

    // Update is called once per frame
    void Update()
    {
        transform.Translate(speed * direction * Time.deltaTime);
    }


}
