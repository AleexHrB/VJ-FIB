using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Random = System.Random;

public class RoadGen : MonoBehaviour
{
    public GameObject StraightLine;
    public GameObject LongLine;
    public GameObject Tea;
    public GameObject Ele;
    private float x;
    private float z;
    public float lengthLine;
    public float lengthLong;
    public float lengthTea;
    public float lengthEle;


    public void generateRoad(Vector3 direction) {

        bool stopGenerate = false;
        Random rand = new Random();

        while (!stopGenerate) {
            int numRand = rand.Next(1, 101);

            if (numRand <= 10) {

                if (direction.x != 0)
                {
                    if (direction.x != 0)
                    {
                        if (direction.x < 0)
                        {
                            Instantiate(Tea, new Vector3(x + 20, 0.0f, z), Quaternion.Euler(0.0f, 90.0f * direction.x, 0.0f));
                        }
                        else {
                            Instantiate(Tea, new Vector3(x, 0.0f, z), Quaternion.Euler(0.0f, 90.0f * direction.x, 0.0f));
                        }
                        
                        x += lengthTea * direction.x;
                        z += lengthTea;
                        direction = new Vector3(0, 0, direction.z);
                    }
                    else
                    {
                        if (direction.z < 0)
                        {
                            Instantiate(Tea, new Vector3(x, 0.0f, z + 20), Quaternion.identity);
                        }
                        else
                        {
                            Instantiate(Tea, new Vector3(x, 0.0f, z), Quaternion.identity);
                        }
                        
                        x += lengthTea * direction.x;
                        z += lengthTea;
                        direction = new Vector3(direction.x,0,0);
                    }

                }
                else
                {

                }
                stopGenerate = true;
            }

            //Acabar
            else if (numRand <= 30) {
                if (direction.x != 0)
                {
                    if (direction.x != 0)
                    {
                        if (direction.x < 0)
                        {
                            Instantiate(Ele, new Vector3(x + 20, 0.0f, z), Quaternion.Euler(0.0f, 90.0f * direction.x, 0.0f));
                        }
                        else
                        {
                            Instantiate(Ele, new Vector3(x, 0.0f, z), Quaternion.Euler(0.0f, 90.0f * direction.x, 0.0f));
                        }

                        x += lengthEle * direction.x;
                        z += lengthEle;
                        direction = new Vector3(0, 0, -direction.z);
                    }
                    else
                    {
                        if (direction.z < 0)
                        {
                            Instantiate(Ele, new Vector3(x, 0.0f, z + 20), Quaternion.identity);
                        }
                        else
                        {
                            Instantiate(Ele, new Vector3(x, 0.0f, z), Quaternion.identity);
                        }

                        x += lengthEle * direction.x;
                        z += lengthEle * (-direction.x);
                        direction = new Vector3(-direction.x, 0, 0);
                    }

                }
            }

            else if (numRand <= 80) {
                
                if (direction.x != 0)
                {
                    Instantiate(StraightLine, new Vector3(x + (lengthLine/2 * direction.x), 0.0f, z), Quaternion.Euler(0.0f, 90.0f, 0.0f));
                    x += lengthLine * direction.x;
                }
                else {
                    Instantiate(StraightLine, new Vector3(x, 0.0f, z + (lengthLine/ 2 * direction.z)), Quaternion.identity);
                    z += lengthLine * direction.z;
                }

            }

            else if (numRand <= 100) {
                if (direction.x != 0)
                {
                    Instantiate(LongLine, new Vector3(x + (lengthLong / 2 * direction.x), 0.0f, z), Quaternion.Euler(0.0f, 90.0f, 0.0f));
                    x += lengthLong * direction.x;

                }
                else
                {
                    Instantiate(LongLine, new Vector3(x, 0.0f, z + (lengthLong / 2 * direction.z)), Quaternion.identity);
                    z += lengthLong * direction.z;
                }

            }

        }
    }

    // Start is called before the first frame update
    void Start()
    {
        x = 0;
        z = 0;
        Instantiate(LongLine, new Vector3(0.0f,0.0f, 0.0f),Quaternion.identity);
        z = z + lengthLong/2;
        Instantiate(Tea, new Vector3(0.0f,0.0f, z), Quaternion.identity);
        x += lengthTea;
        z += lengthTea;
        float xNeg = -x;
        Instantiate(LongLine, new Vector3(x + lengthLong/2,0.0f, z), Quaternion.Euler(0.0f, -90.0f, 0.0f));
        Instantiate(LongLine, new Vector3(xNeg - lengthLong/2,0.0f, z), Quaternion.Euler(0.0f, 90.0f, 0.0f));
        //canGenerate = false;
        x = xNeg - lengthLong;
        generateRoad(new Vector3(-1,0,0));
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
