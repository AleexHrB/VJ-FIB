using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UIElements;

public class Move : MonoBehaviour
{
    public Vector3 direction; 
    public float speed;
    public bool canRotate;
    public int lane;
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
    public bool GodMode = false;
    public bool dead;
    private int IDhit = -1;

    public Vector3 center;

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
        center = Vector3.zero;
    }

    public void autoTurn(bool right) {
        float y = transform.rotation.eulerAngles.y;

        if (right)
        {
            smoothRotate = true;
            target = Quaternion.Euler(0, y + 90.0f, 0);
            direction = direction.x != 0 ? new Vector3(0, 0, -direction.x) : new Vector3(direction.z, 0, 0);
            posTarget = new Vector3(rotationCenter.x, 0, rotationCenter.z);
        }
        else {
            smoothRotate = true;
            target = Quaternion.Euler(0, y - 90.0f, 0);
            posTarget = new Vector3(rotationCenter.x, 0, rotationCenter.z);
            direction = direction.x != 0 ? new Vector3(0, 0, direction.x) : new Vector3(-direction.z, 0, 0);
        }
    }

    public void stopTurn(int box) {
        // Box = 0 -> Left
        // Box = 1 -> Mid
        // Box = 2 -> Right
        int dir = (int)(direction.x != 0 ? direction.x : direction.z);
        if (box == 0)
        {
            lane = 0;
        }
        else if (box == 1)
        {
            lane = 1;
        }

        else if (box == 2) {
            lane = 2;
        }
    
        RTurn = false;
        LTurn = false;

    }

    // Update is called once per frame
    void Update()
    {
        if (!dead) speed += 0.01f * Time.deltaTime;
        transform.Translate(new Vector3(0,0,speed) * Time.deltaTime);
        center += speed * direction * Time.deltaTime;
        float y = transform.rotation.eulerAngles.y;

        if (!smoothRotate && !canRotate) {
            Vector3 shift = direction.x != 0 ? new Vector3(0f, 0, -direction.x) : new Vector3(direction.z, 0, 0);
            if (lane == 0) shift = -2.5f * shift;
            else if (lane == 2) shift = 2.5f * shift;
            else if (lane == 1) shift = Vector3.zero;
            transform.position = Vector3.Lerp(transform.position, center + shift, Time.deltaTime * 8f);
        }
        

        if (Input.GetKeyDown(KeyCode.LeftArrow))
        {
            
            if (canRotate) {
                smoothRotate = true;
                target = Quaternion.Euler(0, y - 90.0f, 0);
                posTarget = new Vector3(rotationCenter.x, 0, rotationCenter.z);
                direction = direction.x != 0 ? new Vector3(0, 0, direction.x) : new Vector3(-direction.z, 0, 0);
             
            }

            else if (lane > 0 && !smoothRotate && !dead) {
                //transform.Translate(new Vector3(-2.5f, 0.0f, 0.0f));
                //LTurn = true;
                //RTurn = false;
                --lane;
            }
        }
        else if (Input.GetKeyDown(KeyCode.RightArrow))
        {
            
            if (canRotate) {
                smoothRotate = true;
                target = Quaternion.Euler(0, y + 90.0f, 0);
                direction = direction.x != 0 ? new Vector3(0, 0, -direction.x) : new Vector3(direction.z, 0, 0);
                posTarget = new Vector3(rotationCenter.x, 0, rotationCenter.z);
          
            }

            else if (lane < 2 && !smoothRotate && !dead)
            {
                //transform.Translate(new Vector3(2.5f,0.0f,0.0f));
                //RTurn = true;
                //LTurn = false;
                ++lane;
            }
        }

        else if (Input.GetKeyDown(KeyCode.G))
        {
            
            GodMode = !GodMode;
            print(GodMode);
        }

        if (smoothRotate) {
            canRotate = false;
            Quaternion before = transform.rotation;
            transform.rotation = Quaternion.Slerp(transform.rotation, target, Time.deltaTime * 8.5f);
            center = direction.x != 0 ? new Vector3(center.x, 0.0f, rotationCenter.z) : new Vector3(rotationCenter.x, 0.0f, center.z);
            if (transform.rotation.eulerAngles.y >= (target.eulerAngles.y - 1) && transform.rotation.eulerAngles.y <= (target.eulerAngles.y + 1)) {
                transform.rotation = target;
                smoothRotate = false;
                //lane = 1;
                //transform.position = direction.x != 0 ? new Vector3(transform.position.x, 0.0f, rotationCenter.z) : new Vector3(rotationCenter.x, 0.0f, transform.position.z);
                
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

    private void FixedUpdate()
    {
        if (GodMode)
        {
            int layerMask = 1 << 0;
            RaycastHit hit;
            if (Physics.Raycast(transform.position, transform.forward, out hit, 3.0f, layerMask) && IDhit != hit.colliderInstanceID) {
                print(hit.collider.tag);
                {
                    if (hit.collider.CompareTag("Rock") || hit.collider.CompareTag("Fall"))
                    {
                        transform.GetChild(0).GetChild(0).GetComponent<AnimationControllerScript>().Jump();
                    }

                    else if (hit.collider.CompareTag("Bob"))
                    {
                        lane = (lane + 1) % 3;
                    }

                    IDhit = hit.colliderInstanceID;
                }
            }

            else if (Physics.Raycast(transform.position + Vector3.up * 2, transform.forward, out hit, 3.0f, layerMask) && IDhit != hit.colliderInstanceID) {
                {
                    print(hit.collider.tag);
                    if (hit.collider.CompareTag("Gamba"))transform.GetChild(0).GetChild(0).GetComponent<AnimationControllerScript>().Slide();
                    IDhit = hit.colliderInstanceID;
                }
            }

            else IDhit = -1;

        }
    }
}
