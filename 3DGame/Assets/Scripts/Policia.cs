using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;

public class Policia : MonoBehaviour
{
    public bool onPlayer;
    public float speed;
    public Vector3 direction;
    private float initSpeed;
    public Vector3 target;
    public bool inmune;
    public Animator animLeft;
    public Animator animMid;
    public Animator animRight;
    // Start is called before the first frame update

    public void dance() {
        speed = 0;
        animMid.Play("mixamo_chicken");
        animLeft.Play("mixamo_chicken");
        animRight.Play("mixamo_chicken");
        float y = transform.rotation.eulerAngles.y;
        transform.rotation = Quaternion.Euler(0.0f, y + 180, 0.0f);
    }
    public void toPlayer(Vector3 posPlayer, Vector3 dir, int lane, bool turn=false) {
        if (onPlayer && !turn) {
            speed += 2.0f;
        }

        else
        {
            //inmune = true;
    
            direction = dir;
            transform.position = posPlayer - direction * 2.5f;

            if (direction.x != 0)
            {
                transform.rotation = Quaternion.Euler(0.0f, 90.0f*direction.x, 0.0f);
            }
            else {
                transform.rotation = Quaternion.Euler(0.0f, 90f - 90*direction.z, 0.0f);
            }

            
            //transform.position -= direction.x != 0 ? new Vector3(0, 0, 1) * (2.5f*(lane - 1)) : new Vector3(1, 0, 0) * (2.5f * (lane - 1));

            speed = initSpeed;
            GetComponent<Policia>().onPlayer = true;
        }
        
        
    }

    void Start()
    {
        animMid = transform.GetChild(0).GetComponent<Animator>();
        animRight = transform.GetChild(1).GetComponent<Animator>();
        animLeft = transform.GetChild(2).GetComponent<Animator>();

        direction = new Vector3(0, 0, 1);
        speed = 10.0f;
        initSpeed = speed;
        onPlayer = true;
        target = transform.position;
    }

    // Update is called once per frame
    void Update()
    {
        initSpeed += 0.01f * Time.deltaTime;
        speed += 0.01f * Time.deltaTime;
        
        target += speed * Time.deltaTime * direction;
        transform.position += speed * Time.deltaTime*direction;
        //transform.position = Vector3.Lerp(transform.position, target, Time.deltaTime * 6f);
        if (Mathf.Abs((transform.position.z - target.z)) < 1.0f) { inmune = false; }
    }


}
