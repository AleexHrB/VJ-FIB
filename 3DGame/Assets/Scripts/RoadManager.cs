using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
//using UnityEditor.Experimental.GraphView;
using UnityEngine;
using Random = System.Random;

public class RoadManager : MonoBehaviour
{
    public GameObject line;
    public GameObject longLine;
    public GameObject Ele;
    public GameObject Tea;
    public GameObject lineForat;
    public GameObject longLineForat;

    public GameObject Coin;
    public GameObject Rock;
    public GameObject Bob;
    public GameObject Shrimp;
     

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
    private bool eleLast;

    private void populate(Vector3 start, Vector3 dir, int len, GameObject parent)
    {
        Random rand = new Random();
        
        int act = 0 - len/2 + 5;
        int pastLane = -2;
        int lane = -2;

        while (act < len/2) {
            lane = rand.Next(1, 4) - 2;
            if (lane == pastLane) lane = rand.Next(1, 4) - 2;
            pastLane = lane;

            Vector3 shift;
            shift = new Vector3(2.5f * lane, 0, 0); 
           
            GameObject obstacle;
            int numRand = rand.Next(1, 101);
            if (numRand <= 50)
            {
                int sizeBatch = rand.Next(1, len - act);
                obstacle = Instantiate(Coin, new Vector3(0, 0, 1) * act + shift, Quaternion.identity);
                obstacle.transform.SetParent(parent.transform, false);
                //act += sizeBatch;
                act += 2;
            }
            else if (numRand <= 75)
            {
                act += 2;
            }

            else if (numRand <= 90)
            {
                obstacle = Instantiate(Rock, new Vector3(0, 0, 1) * act + shift, Quaternion.identity);
                obstacle.transform.SetParent(parent.transform, false);
                act += 5;
            }

            else if (numRand <= 95)
            {
                obstacle = Instantiate(Bob, new Vector3(0, 0, 1) * act + shift + new Vector3(0, 5, 0), Quaternion.Euler(0.0f, -90.0f, 0.0f));
                obstacle.transform.SetParent(parent.transform, false);


                act += 5;
            }
            else if (numRand <= 99 && act > 2) {
                obstacle = Instantiate(Shrimp, new Vector3(0, 0, 1) * act + shift, Quaternion.identity);
                obstacle.transform.SetParent(parent.transform, false);
                act += 5;
            }

            else if (act < len/2 - 5 && act > -len / 2 + 5)
            {
                Vector3 moveLane = new Vector3(1, 0, 0);
                obstacle = Instantiate(Shrimp, new Vector3(0, 0, 1) * act, Quaternion.identity);
                obstacle.transform.SetParent(parent.transform, false);

                GameObject obstacle2 = Instantiate(Shrimp, new Vector3(0, 0, 1) * act - moveLane * 2.5f, Quaternion.identity);
                obstacle2.transform.SetParent(parent.transform, false);

                GameObject obstacle3 = Instantiate(Shrimp, new Vector3(0, 0, 1) * act + moveLane * 2.5f, Quaternion.identity);
                obstacle3.transform.SetParent(parent.transform, false);
                act += 5;
            }
            else { ++act; }
   
        }
        
        
    }

    private void generateRoad()
    {
        Random rand = new Random();
        int numRand = rand.Next(1, 101);
        

        if (numRand <= 40 || eleLast)
        {
            if (direction.x != 0) 
            {
                if (numRand <= 10)
                {
                    GameObject RoadAux = Instantiate(lineForat, new Vector3(x + (lengthLine / 2 * direction.x), 0.0f, z), Quaternion.Euler(0.0f, 90.0f*direction.x, 0.0f));
                    populate(new Vector3(x, 0, z), direction, (int)lengthLine, RoadAux);
                    x += (lengthLine + 4) * direction.x;
                }

                else
                {
                    GameObject RoadAux = Instantiate(line, new Vector3(x + (lengthLine / 2 * direction.x), 0.0f, z), Quaternion.Euler(0.0f, 90.0f * direction.x, 0.0f));
                    populate(new Vector3(x, 0, z), direction, (int)lengthLine, RoadAux);
                    x += lengthLine * direction.x;
                }
                
            }

            else
            {
                if (numRand <= 10)
                {

                    GameObject RoadAux = Instantiate(lineForat, new Vector3(x, 0.0f, z + (lengthLine / 2 * direction.z)), Quaternion.Euler(0.0f, 90.0f - 90.0f*direction.z, 0.0f));
                    populate(new Vector3(x, 0, z), direction, (int)lengthLine, RoadAux);
                    z += (lengthLine + 4) * direction.z;
                }

                else
                {
                    GameObject RoadAux = Instantiate(line, new Vector3(x, 0.0f, z + (lengthLine / 2 * direction.z)), Quaternion.Euler(0.0f, 90.0f - 90.0f * direction.z, 0.0f));
                    populate(new Vector3(x, 0, z), direction, (int)lengthLine, RoadAux);
                    z += lengthLine * direction.z;
                }
                

            }
            eleLast = false;
        }

        else if (numRand <= 65)
        {
            if (direction.x != 0)
            {
                
                if (numRand <= 48){

                    GameObject RoadAux = Instantiate(longLineForat, new Vector3(x + (lengthLong / 2 * direction.x), 0.0f, z), Quaternion.Euler(0.0f, 90.0f*direction.x, 0.0f));
                    populate(new Vector3(x, 0, z), direction, (int)lengthLine, RoadAux);
                    x += (lengthLong + 4) * direction.x;
                }
                else
                {
                    GameObject RoadAux = Instantiate(longLine, new Vector3(x + (lengthLong / 2 * direction.x), 0.0f, z), Quaternion.Euler(0.0f, 90.0f * direction.x, 0.0f));
                    populate(new Vector3(x, 0, z), direction, (int)lengthLine, RoadAux);
                    x += lengthLong * direction.x;
                }
                

            }
            else
            {
                if (numRand <= 47)
                {

                    GameObject RoadAux = Instantiate(longLineForat, new Vector3(x, 0.0f, z + (lengthLong / 2 * direction.z)), Quaternion.Euler(0.0f, 90.0f - 90.0f * direction.z, 0.0f));
                    populate(new Vector3(x, 0, z), direction, (int)lengthLine, RoadAux);
                    z += (lengthLong + 4) * direction.z;
                }

                else {
                    GameObject RoadAux = Instantiate(longLine, new Vector3(x, 0.0f, z + (lengthLong / 2 * direction.z)), Quaternion.Euler(0.0f, 90.0f - 90.0f * direction.z, 0.0f));
                    populate(new Vector3(x, 0, z), direction, (int)lengthLine, RoadAux);
                    z += lengthLong * direction.z;
                }
                
            }
            eleLast = false;
        }

        else if (numRand <= 73 && !eleLast)
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
            eleLast = true;
        }

        else if (numRand <= 90 && !eleLast)
        {
            if (direction.x != 0)

            {
                GameObject L = Instantiate(Ele, new Vector3(x, 0.0f, z), Quaternion.Euler(0.0f, 90.0f * direction.x, 180.0f));
                L.transform.GetChild(0).Rotate(new Vector3(180.0f, 0, 0), Space.Self);
                L.transform.GetChild(1).Rotate(new Vector3(0, 0, 180.0f), Space.Self);
                x += lengthEle * direction.x;
                z += lengthEle * (direction.x);
                direction = new Vector3(0, 0, direction.x);

            }

            else
            {
                if (direction.z < 0)
                {
                    GameObject L = Instantiate(Ele, new Vector3(x, 0.0f, z), Quaternion.Euler(0.0f, 180.0f, 180.0f));
                    L.transform.GetChild(0).Rotate(new Vector3(180.0f, 0, 0), Space.Self);
                    L.transform.GetChild(1).Rotate(new Vector3(0, 0, 180.0f), Space.Self);

                }
                else
                {
                    GameObject L = Instantiate(Ele, new Vector3(x, 0.0f, z), Quaternion.Euler(0.0f, 0f, 180.0f));
                    L.transform.GetChild(0).Rotate(new Vector3(180.0f, 0, 0), Space.Self);
                    L.transform.GetChild(1).Rotate(new Vector3(0, 0, 180.0f), Space.Self);
                }

                x += lengthEle * (-direction.z);
                z += lengthEle * (direction.z);
                direction = new Vector3(-direction.z, 0, 0);

            }
            eleLast = true;
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
            eleLast = false;
        }
        else {
            if (direction.x != 0)
            {

                GameObject RoadAux = Instantiate(line, new Vector3(x + (lengthLine / 2 * direction.x), 0.0f, z), Quaternion.Euler(0.0f, 90.0f*direction.x, 0.0f));
                populate(new Vector3(x, 0, z), direction, (int)lengthLine, RoadAux);
                x += lengthLine * direction.x;
            }

            else
            {
                GameObject RoadAux = Instantiate(line, new Vector3(x, 0.0f, z + (lengthLine / 2 * direction.z)), Quaternion.Euler(0.0f, 90.0f - 90.0f * direction.z, 0.0f));
                populate(new Vector3(x, 0, z), direction, (int)lengthLine, RoadAux);

                z += lengthLine * direction.z;
            }
            eleLast = false;
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

            int nAhead = 3;
            for (int i = 0; i < nAhead; ++i) {
                generateRoad();
            }
            
            stop = false;
               
        }

        else if (other.tag == "Right")
        {
            x = xRight;
            z = zRight;

            direction = direction.x != 0 ? new Vector3(0, 0, -direction.x) : new Vector3(direction.z, 0, 0);
            
            int nAhead = 3;
            for (int i = 0; i < nAhead; ++i)
            {
                generateRoad();
            }

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

    private void Start()
    {
        x = 0;
        z = 125;
        direction = new Vector3(0, 0, 1);
        stop = false;
        eleLast = false;
    }
}
