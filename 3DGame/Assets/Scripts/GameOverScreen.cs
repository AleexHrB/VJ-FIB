using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class GameOverScreen : MonoBehaviour
{
    public void gameOver()
    {
        gameObject.SetActive(true);
    }

    public void returnMenu()
    {
        SceneManager.LoadScene(0);
    }

    public void playAgain()
    {
        gameObject.SetActive(false);
        SceneManager.LoadScene(1);
    }
}
