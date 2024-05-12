using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Move : MonoBehaviour
{
    public Vector3 direction; 
    public float speed;
    public bool canRotate;
    private int lane;
    private Quaternion target;
    private bool smoothRotate;
    private const double PI = 3.1415926535897931;

    // Start is called before the first frame update
    void Start()
    {
        lane = 1;
        direction = new Vector3(0,0,1.0f);
        canRotate = false;
        smoothRotate = false;
        speed = 10.0f;
    }

    // Update is called once per frame
    void Update()
    {
        transform.Translate(speed * direction * Time.deltaTime);
        Vector3 move = direction;
        move.x = direction.z;
        move.z = direction.x;
        float y = transform.rotation.eulerAngles.y;
        
        if (Input.GetKeyDown(KeyCode.LeftArrow) && lane > 0)
        {
            print(y);
            if (canRotate) {
                smoothRotate = true;
                
                target = Quaternion.Euler(0, y - 90.0f, 0);
            }

            else {
                transform.Translate(move*-2.5f);
                --lane;
            }
        }
        else if (Input.GetKeyDown(KeyCode.RightArrow) && lane < 2)
        {
            print(y);
            if (canRotate) {
                smoothRotate = true;
                target = Quaternion.Euler(0, y + 90.0f, 0);
            }

            else {
                transform.Translate(move*2.5f);
                ++lane;
            }
        }

        if (smoothRotate) {
            Quaternion before = transform.rotation;
            transform.rotation = Quaternion.Slerp(transform.rotation, target, Time.deltaTime * 8.5f);
            if (transform.rotation.Equals(before)) smoothRotate = false;
        }

    }
}
