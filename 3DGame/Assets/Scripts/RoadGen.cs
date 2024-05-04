using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RoadGen : MonoBehaviour
{
    public GameObject StraightLine;
    public GameObject LongLine;
    public GameObject Tea;
    public GameObject Ele;
    private float x;
    private float z;

    public void generateRoad(Vector3 direction) {

        bool stopGenerate = false;
        Random rand = new Random();

        while (!stopGenerate) {
            int numRand = rand.Next(1, 101);

            if (numRand <= 10) {

                Instantiate(Tea, new Vector3(x,0.0f, z), Quaternion.identity);
                stopGenerate = true;
            }

            //Acabar
            else if (numRand <= 30) {
                Instantiate(Ele, new Vector3(x,0.0f,z), Quaternion.identity);
            }

            else if (numRand <= 80) {

            }

            else if (numRand <= 100) {

            }

        }
    }

    // Start is called before the first frame update
    void Start()
    {
        Instantiate(LongLine, new Vector3(0.0f,0.0f, 0.0f),Quaternion.identity);
        Instantiate(Tea, new Vector3(0.0f,0.0f, 40.0f), Quaternion.identity);
        Instantiate(LongLine, new Vector3(53.0f,0.0f, 52.5f), Quaternion.Euler(0.0f, -90.0f, 0.0f));
        Instantiate(LongLine, new Vector3(-53.0f,0.0f, 52.5f), Quaternion.Euler(0.0f, 90.0f, 0.0f));
        canGenerate = false;
        x = 53.0f + 40.0f;
        z = 52.5f;
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
