using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;
using Random = System.Random;

public class RoadManager : MonoBehaviour
{
    public GameObject line;
    public GameObject longLine;
    public GameObject Ele;
    public GameObject Tea;
    public GameObject Coin;
    public GameObject Rock;

    public float lengthLine;
    public float lengthLong;
    public float lengthEle;
    public float lengthTea;

    private Vector3 direction;

    private float x;
    private float z;

    private float xLeft;
    private float zLeft;

    private float xRight;
    private float zRight;

    private bool stop;


    private void populate(Vector3 start, Vector3 dir, int len)
    {
        Random rand = new Random();
        
        int act = 0;

        while (act < len) {
            int numRand = rand.Next(1, 5);
            if (numRand == 1)
            {
                print("caca");
                int sizeBatch = rand.Next(1, len - act);
                int lane = rand.Next(1, 4) - 2;
                Vector3 shift;
                if (dir.x != 0) { shift = new Vector3(0, 0, 2.5f * lane); }
                else { shift = new Vector3(2.5f * lane, 0,0); }
                Instantiate(Coin, start + dir * act + shift, Quaternion.identity);
                //act += sizeBatch;
            }
            else if (numRand == 2)
            {
                Instantiate(Rock, start + dir * act, Quaternion.identity);
                act += 5;
            }
            else
            {
               
                act += 1;
            }
        }
        
        
    }

    private void generateRoad()
    {
        Random rand = new Random();
        int numRand = rand.Next(1, 101);

        if (numRand <= 40)
        {
            if (direction.x != 0)
            {

                populate(new Vector3(x, 0, z), direction, (int) lengthLine);
                Instantiate(line, new Vector3(x + (lengthLine / 2 * direction.x), 0.0f, z), Quaternion.Euler(0.0f, 90.0f, 0.0f));
                x += lengthLine * direction.x;
            }

            else
            {
                populate(new Vector3(x, 0, z), direction, (int)lengthLine);
                Instantiate(line, new Vector3(x, 0.0f, z + (lengthLine / 2 * direction.z)), Quaternion.identity);

                z += lengthLine * direction.z;
            }

        }

        else if (numRand <= 65)
        {
            if (direction.x != 0)
            {
                populate(new Vector3(x, 0, z), direction, (int)lengthLong);
                Instantiate(longLine, new Vector3(x + (lengthLong / 2 * direction.x), 0.0f, z), Quaternion.Euler(0.0f, 90.0f, 0.0f));
                x += lengthLong * direction.x;

            }
            else
            {
                populate(new Vector3(x, 0, z), direction, (int)lengthLong);
                Instantiate(longLine, new Vector3(x, 0.0f, z + (lengthLong / 2 * direction.z)), Quaternion.identity);
                z += lengthLong * direction.z;
            }
        }

        else if (numRand <= 73)
        {
            if (direction.x != 0)

            {
                Instantiate(Ele, new Vector3(x, 0.0f, z), Quaternion.Euler(0.0f, 90.0f * direction.x, 0.0f));
                x += lengthEle * direction.x;
                z += lengthEle * (-direction.x);
                direction = new Vector3(0, 0, -direction.x);

            }

            else
            {
                if (direction.z < 0)
                {
                    Instantiate(Ele, new Vector3(x, 0.0f, z), Quaternion.Euler(0.0f, 180.0f, 0.0f));
                }
                else
                {
                    Instantiate(Ele, new Vector3(x, 0.0f, z), Quaternion.identity);
                }

                x += lengthEle * (direction.z);
                z += lengthEle * (direction.z);
                direction = new Vector3(direction.z, 0, 0);

            }
            //L_cooldown = L_Wait;
        }

        else if (numRand <= 90)
        {
            if (direction.x != 0)

            {
                Instantiate(Ele, new Vector3(x, 0.0f, z), Quaternion.Euler(0.0f, 90.0f * direction.x, 180.0f));
                x += lengthEle * direction.x;
                z += lengthEle * (direction.x);
                direction = new Vector3(0, 0, direction.x);

            }

            else
            {
                if (direction.z < 0)
                {
                    Instantiate(Ele, new Vector3(x, 0.0f, z), Quaternion.Euler(0.0f, 180.0f, 180.0f));
                }
                else
                {
                    Instantiate(Ele, new Vector3(x, 0.0f, z), Quaternion.Euler(0.0f, 0f, 180.0f));
                }

                x += lengthEle * (-direction.z);
                z += lengthEle * (direction.z);
                direction = new Vector3(-direction.z, 0, 0);

            }
            //L_cooldown = L_Wait;
        }

        else if (!stop)
        {
            if (direction.x != 0)
            {

                Instantiate(Tea, new Vector3(x, 0.0f, z), Quaternion.Euler(0.0f, 90.0f * direction.x, 0.0f));


                x += lengthTea * direction.x;
                xRight = x;
                xLeft = x;


                zRight = z - (lengthLong + lengthTea) * direction.x;
                zLeft = z + (lengthLong + lengthTea) * direction.x;
            }

            else
            {
                if (direction.z < 0)
                {
                    Instantiate(Tea, new Vector3(x, 0.0f, z), Quaternion.Euler(0.0f, 180.0f, 0.0f));
                }
                else
                {
                    Instantiate(Tea, new Vector3(x, 0.0f, z), Quaternion.identity);
                }


                z += lengthTea * direction.z;
                zRight = z;
                zLeft = z;

                xRight = x + (lengthLong + lengthTea) * direction.z;
                xLeft = x - (lengthLong + lengthTea) * direction.z;

            }
            stop = true;
        }
        else {
            if (direction.x != 0)
            {

                Instantiate(line, new Vector3(x + (lengthLine / 2 * direction.x), 0.0f, z), Quaternion.Euler(0.0f, 90.0f, 0.0f));
                x += lengthLine * direction.x;
            }

            else
            {
                Instantiate(line, new Vector3(x, 0.0f, z + (lengthLine / 2 * direction.z)), Quaternion.identity);

                z += lengthLine * direction.z;
            }

        }
    }
    // Start is called before the first frame update
    private void OnTriggerEnter(Collider other)
    {
        if (other.tag == "Road" && !stop)
        {
            generateRoad();
        }

        else if (other.tag == "Left") {
            x = xLeft;
            z = zLeft;

            direction = direction.x != 0 ? new Vector3(0, 0, direction.x) : new Vector3(-direction.z, 0, 0);
            generateRoad();
            generateRoad();
            generateRoad();
            stop = false;
               
        }

        else if (other.tag == "Right")
        {
            x = xRight;
            z = zRight;

            direction = direction.x != 0 ? new Vector3(0, 0, -direction.x) : new Vector3(direction.z, 0, 0);
            generateRoad();
            generateRoad();
            generateRoad();
            
            stop = false;
        }
    }

    private void OnTriggerExit(Collider other)
    {
        if (other.tag == "delete" || other.tag == "Road" || other.tag == "Left" || other.tag == "Right")
        {
            Destroy(other.gameObject.transform.parent.gameObject, 3);
        }
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    private void Start()
    {
        x = 0;
        z = 125;
        direction = new Vector3(0, 0, 1);
        stop = false;
    }
}
