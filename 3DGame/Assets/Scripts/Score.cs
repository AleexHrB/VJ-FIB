using UnityEngine;
using UnityEngine.UI;

public class Score : MonoBehaviour
{
    public float score;
    public Text txtScore;

    // Update is called once per frame
    void Update()
    { 
         
        score = score + Time.deltaTime*10;
        txtScore.text = "Score: " + ((int) score).ToString();
    }
}
