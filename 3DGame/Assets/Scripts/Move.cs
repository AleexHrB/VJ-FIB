using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UIElements;

public class Move : MonoBehaviour
{
    public Vector3 direction; 
    public float speed;
    public bool canRotate;
    private int lane;
    private Quaternion target;
    private Vector3 posTarget;
    private bool smoothRotate;
    public bool falling;
    private bool fell;
    public Vector3 rotationCenter;
    private const double PI = 3.1415926535897931;
    public GameObject road;
    public bool LTurn = false;
    public bool RTurn = false;
    public bool Tea;

    // Start is called before the first frame update
    void Start()
    {
        lane = 1;
        direction = new Vector3(0,0,1.0f);
        canRotate = false;
        smoothRotate = false;
        falling = false;
        speed = 10.0f;
        fell = false;
        LTurn = RTurn = false;
    }

    public void stopTurn(int box) {
        // Box = 0 -> Left
        // Box = 1 -> Mid
        // Box = 2 -> Right
        int dir = (int)(direction.x != 0 ? direction.x : direction.z);
        if (box == 0)
        {
            
            lane = 1 - 1*dir;
        }
        else if (box == 1)
        {
            lane = 1;
        }

        else if (box == 2) {
            lane = 1 + 1 * dir;
        }
    
        RTurn = false;
        LTurn = false;

        print(lane);
    }

    // Update is called once per frame
    void Update()
    {
        transform.Translate(new Vector3(0,0,speed) * Time.deltaTime);
        Vector3 move = direction;
        move.x = direction.z;
        move.z = direction.x;
        float y = transform.rotation.eulerAngles.y;

        if (RTurn) transform.Translate(new Vector3(speed,0,0) * Time.deltaTime);
        if (LTurn) transform.Translate(new Vector3(-speed,0,0) * Time.deltaTime);


        if (Input.GetKeyDown(KeyCode.LeftArrow))
        {
            
            if (canRotate) {
                smoothRotate = true;
                target = Quaternion.Euler(0, y - 90.0f, 0);
                posTarget = new Vector3(rotationCenter.x, 0, rotationCenter.z);
                direction = direction.x != 0 ? new Vector3(0, 0, 1) : new Vector3(-1, 0, 0);
             
            }

            else if (lane > 0) {
                //transform.Translate(new Vector3(-2.5f, 0.0f, 0.0f));
                LTurn = true;
                RTurn = false;
            }
        }
        else if (Input.GetKeyDown(KeyCode.RightArrow))
        {
            
            if (canRotate) {
                smoothRotate = true;
                target = Quaternion.Euler(0, y + 90.0f, 0);
                direction = direction.x != 0 ? new Vector3(0, 0, -1) : new Vector3(1, 0, 0);
                posTarget = new Vector3(rotationCenter.x, 0, rotationCenter.z);
          
            }

            else if (lane < 2){
                //transform.Translate(new Vector3(2.5f,0.0f,0.0f));
                RTurn = true;
                LTurn = false;
            }
        }

        if (smoothRotate) {
            canRotate = false;
            Quaternion before = transform.rotation;
            transform.rotation = Quaternion.Slerp(transform.rotation, target, Time.deltaTime * 8.5f);
            if (transform.rotation.eulerAngles.y >= (target.eulerAngles.y - 1) && transform.rotation.eulerAngles.y <= (target.eulerAngles.y + 1)) {
                transform.rotation = target;
                smoothRotate = false;
                lane = 1;
                transform.position = direction.x != 0 ? new Vector3(transform.position.x, 0.0f, rotationCenter.z) : new Vector3(rotationCenter.x, 0.0f, transform.position.z);
            }
        }

        if (falling)
        {
            y = transform.rotation.eulerAngles.y;
            transform.rotation = Quaternion.Slerp(transform.rotation, Quaternion.Euler(90.0f, y, 0), Time.deltaTime * 3.5f);
            if (transform.rotation.eulerAngles.x == 90)
            {
                falling = false;
                fell = true;
            }
            
        }
        if (fell)
        {
            transform.GetChild(1).transform.Translate(5 * new Vector3(0, -1, 0) * Time.deltaTime);
            //transform.GetChild(0).Translate(new Vector3(0, 2, 0) * Time.deltaTime);
           
        }

    }
}
