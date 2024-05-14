using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CoinAnim : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        Vector3 aux = transform.position;
        aux.y = 1.5f * Mathf.Abs(Mathf.Sin(Mathf.PI * 1.0f * Time.time));
        transform.position = aux;
    }
}
