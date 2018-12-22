using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Trigger : MonoBehaviour {
    public GameObject ball;
    public Text text;

    public GameObject won;

    private int score = 0;

    void Update()
    {
        text.text = ""+score;

        if (score >= 5)
        {
            won.SetActive(true);
            Time.timeScale = 0;
        }
    }

    private void OnTriggerEnter(Collider collider)
    {
        Debug.Log("Something entered");

        if (collider.tag == "Ball")
        {
            ball.transform.position = new Vector3(0, 6, 0);
            ++score;
            Debug.Log("Ball");
        }
    }

    public void Quit()
    {
        Application.Quit();
    }
}
