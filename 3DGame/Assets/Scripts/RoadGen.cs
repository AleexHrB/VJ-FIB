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
    int turns = 0;
    public int L_Wait;


    public void generateRoad(Vector3 direction) {

        bool stopGenerate = false;
        Random rand = new Random();
        int L_cooldown = 0;
        int Lturns = 0;
        int Rturns = 0;

        while (!stopGenerate) {
            int numRand = rand.Next(1, 101);



            if (numRand <= 1)
            {

                if (direction.x != 0)
                {

                    Instantiate(Tea, new Vector3(x, 0.0f, z), Quaternion.Euler(0.0f, 90.0f * direction.x, 0.0f));

                    x += lengthTea * direction.x;
                    direction = new Vector3(0, 0, direction.z);
                    Instantiate(LongLine, new Vector3(x, 0, z + lengthLong / 2 + lengthTea), Quaternion.identity);
                    Instantiate(LongLine, new Vector3(x, 0, z - lengthLong / 2 - lengthTea), Quaternion.identity);
                    z += lengthTea;
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
                    Instantiate(LongLine, new Vector3(x + lengthLong / 2 + lengthTea, 0, z), Quaternion.Euler(0.0f, 90.0f, 0.0f));
                    Instantiate(LongLine, new Vector3(x - lengthLong / 2 - lengthTea, 0, z), Quaternion.Euler(0.0f, -90.0f, 0.0f));
                    direction = new Vector3(direction.x, 0, 0);
                    x += lengthTea;
                }

                stopGenerate = true;
            }

            //Acabar

            else if (numRand <= 15 && L_cooldown == 0 && turns >= -2) {
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
                L_cooldown = L_Wait;
                --turns;
            }

            else if (numRand <= 30 && L_cooldown == 0 && turns <= 2)
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
                L_cooldown = L_Wait;
                ++turns;
            }

            else if (numRand <= 80)
            {
                GameObject lin;
                if (direction.x != 0)
                {

                    lin = Instantiate(StraightLine, new Vector3(x + (lengthLine / 2 * direction.x), 0.0f, z), Quaternion.Euler(0.0f, 90.0f, 0.0f));
                    x += lengthLine * direction.x;
                }

                else
                {
                    lin = Instantiate(StraightLine, new Vector3(x, 0.0f, z + (lengthLine / 2 * direction.z)), Quaternion.identity);

                    z += lengthLine * direction.z;
                }

            }

            else if (numRand <= 100)
            {

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

            if (L_cooldown >  0) --L_cooldown; 
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
        x = x + lengthLong;
        generateRoad(new Vector3(1,0,0));
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
