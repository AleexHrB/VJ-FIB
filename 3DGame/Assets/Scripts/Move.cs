using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Move : MonoBehaviour
{
    public Vector3 speed; 
    private int lane;
    // Start is called before the first frame update
    void Start()
    {
        lane = 1;
    }

    // Update is called once per frame
    void Update()
    {
        transform.Translate(speed*Time.deltaTime);
         if (Input.GetKeyDown(KeyCode.LeftArrow) && lane > 0)
        {
            transform.Translate(new Vector3(-2.5f,0,0));
            --lane;
        }
        else if (Input.GetKeyDown(KeyCode.RightArrow) && lane < 2)
        {
            transform.Translate(new Vector3(2.5f,0,0));
            print("down arrow key is held down");
            ++lane;
        }
    }
}
