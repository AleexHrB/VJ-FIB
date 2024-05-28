using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using TMPro;

public class Credits : MonoBehaviour
{
    public TMP_Text t1;

    // Update is called once per frame
    void Update()
    {
        Vector3 aux = t1.transform.position;
        aux.y += 100*Time.deltaTime;
        t1.transform.position = aux;
        if (aux.y > 1300.0f) SceneManager.LoadScene(0);

        if (Input.GetKeyDown(KeyCode.Escape)) { SceneManager.LoadScene(0); }
    }
}
