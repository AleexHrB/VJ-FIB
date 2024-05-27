using UnityEngine;
using UnityEngine.UI;

public class Score : MonoBehaviour
{
    public float score;
    public Text txtScore;
    public bool dead = false;

    // Update is called once per frame
    void Update()
    { 
         
        if (!dead) score = score + Time.deltaTime*10;
        txtScore.text = "Score: " + ((int) score).ToString();
    }
}
