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

    public void toPlayer(Vector3 posPlayer, Vector3 dir, int lane, bool turn=false) {
        print("aa");
        if (onPlayer && !turn) {
            speed += 2.0f;
        }

        else
        {
            direction = dir;
            transform.position = posPlayer - direction * 3;

            if (direction.x != 0)
            {
                transform.rotation = Quaternion.Euler(0.0f, 90.0f*direction.x, 0.0f);
            }
            else {
                transform.rotation = Quaternion.Euler(0.0f, 90f - 90*direction.z, 0.0f);
            }

            
            transform.position -= direction.x != 0 ? new Vector3(0, 0, 1) * (2.5f*(lane - 1)) : new Vector3(1, 0, 0) * (2.5f * (lane - 1));

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
        initSpeed += 0.01f * Time.deltaTime;
        speed += 0.01f * Time.deltaTime;
        transform.Translate(speed * new Vector3(0.0f, 0.0f, 1.0f) * Time.deltaTime);
    }


}
