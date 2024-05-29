using UnityEngine;
using UnityEngine.UI;

public class Score : MonoBehaviour
{
    public float score;
    public Text txtScore;
    public bool dead = false;
    public GameObject camara;
    private bool changed;
    public AudioClip tense;

    // Update is called once per frame
    void Update()
    { 
         
        if (!dead) score = score + Time.deltaTime*10;
        txtScore.text = "Score: " + ((int) score).ToString();

        if (camara.GetComponent<Move>().speed > 15.0f && !changed) { 
            changed = true;
            camara.GetComponent<AudioSource>().clip = tense;
            camara.GetComponent<AudioSource>().Play();
        }
    }
}
