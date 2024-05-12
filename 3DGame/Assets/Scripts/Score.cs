using UnityEngine;
using UnityEngine.UI;

public class Score : MonoBehaviour
{
    public int score;
    public Text txtScore;

    // Update is called once per frame
    void Update()
    { 
        ++score;
        txtScore.text = "Score: " + score.ToString();
    }
}
