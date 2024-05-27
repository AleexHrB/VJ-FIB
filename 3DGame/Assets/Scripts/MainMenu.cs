using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class MainMenu : MonoBehaviour
{
    public void Start()
    {
        
    }
    public void playGame()
    {
        SceneManager.LoadScene(1);
    }

    public void loadCredits()
    {
        SceneManager.LoadScene(2);
    }

    public void loadMenu()
    {
        SceneManager.LoadScene(0);
    }

    public void loadHowTo()
    {
        SceneManager.LoadScene(3);
    }

    public void exitGame() { 
        Application.Quit();
    }
}
