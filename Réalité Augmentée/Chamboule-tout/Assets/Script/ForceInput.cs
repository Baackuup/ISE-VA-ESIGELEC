using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class ForceInput : MonoBehaviour {

    // Use this for initialization

    public float ballspeed;
	public GUIStyle style;
	public int score = -10;
	private GameObject Can;
	private bool vert_test;
	private Quaternion localQ;
	private float fallTime = 0.0f;
    float angle = 0.0f;
    Vector3 axis = Vector3.zero;
    public float slider_v;
    public Slider speed_slider;

    private bool[] scored = {false,false,false,false,false,false,false};
		// On choisit la taille et l'emplacement où sera affiché le score
		void OnGUI () {
			float x = Screen.width / 2f;
			float y = 30f;
			float width = 300f;
			float height = 20f;
			string text_speed = "Ball Speed: " + ballspeed.ToString ();
			string text_score = "Score = " + score.ToString ();

			GUI.Label(new Rect(x-(width/2f), y, width, height), text_speed, style);
			GUI.Label(new Rect(x-(width/2f), y+30f, width, height), text_score, style);
			
			if (score == 60) {
			string game_over = "GAME OVER, BRAVO !!";
			GUI.Label(new Rect(x-(width/2f), y+100f, width, height), game_over, style);
			}
		}

    public void slide_change (float value)
    {
            slider_v = value;
    }

	void Start () {

        if (speed_slider)
            speed_slider.onValueChanged.AddListener(slide_change);

        for (int i = 1; i <= 6; i++) {
			scored [i] = false;
		}
		score = 0;
		fallTime = 3.0f;
        
    }
		void Update() {

		// wait until some time has elapsed ...
		if (fallTime > 5.0f) {
			float roulette = (float)Input.GetAxisRaw ("Mouse ScrollWheel");
			ballspeed += roulette;

            // or get it from slider
            if (speed_slider)
            {
                // Debug.Log("change value");
                ballspeed = slider_v;
            }

			if (ballspeed < 0)
				ballspeed = 0;
			// for each Can: if moved enough from vertical, then add 10 to score and mark as moved
			for (int i = 1; i <= 6; i++) {
				// Debug.Log("finding Can:" + "Can" + i.ToString());
				Can = GameObject.Find ("Can" + i.ToString ());
                localQ = Can.transform.rotation;
                localQ.ToAngleAxis(out angle, out axis);

				float magRot = Mathf.Abs (localQ.eulerAngles.x) + Mathf.Abs (localQ.eulerAngles.z);
				if (Can != null && i == 1)
                {
                  // Debug.Log ("Can " + i + " axis= " + axis + " angle= " + angle);
                }
                // verticality test
                vert_test = true;
				if (magRot > 10 && magRot < 350)
					vert_test = false;
				if (magRot < -10 && magRot > -350)
					vert_test = false;
				if (vert_test == false && scored [i] == false) {
					//Debug.Log ("Can " + i + " has scored");
					//Debug.Log ("localQ=" + magRot);
					score += 10;
					scored [i] = true;
				}
			}
		}
		fallTime += Time.deltaTime;

	}
}
