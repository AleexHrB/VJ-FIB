using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RoadGen : MonoBehaviour
{
    public GameObject road;
    // Start is called before the first frame update
    void Start()
    {
        int nLanes = 10;        
        float z = 0.0f;
        GameObject obj;

        for(int i = 0; i < 1000; ++i) {
            Instantiate(road, new Vector3(0.0f,0.0f, i),Quaternion.identity);
        }
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
