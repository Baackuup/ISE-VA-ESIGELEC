using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class orient_arrow : MonoBehaviour {

	public float speed = 15f;
    protected Joystick joystick;
    public float scale_inter_joy = 0.5f;
    
    // Use this for initialization
    void Start () {
        joystick = FindObjectOfType<Joystick>();
    }
	 
	// Update is called once per frame
	void Update () {
		float inputspeedX = 0f, inputspeedY = 0f;

        // for keyboard input
		inputspeedX = Input.GetAxisRaw("ArrowHorizontal") ;
		inputspeedY = Input.GetAxisRaw("ArrowVertical") ;
        // for virtual joystick inputs
        if (joystick)
        {
            inputspeedX += joystick.Horizontal * scale_inter_joy;
            inputspeedY += joystick.Vertical * scale_inter_joy;
        }
        transform.eulerAngles += new Vector3(-inputspeedY * speed * Time.deltaTime, inputspeedX * speed * Time.deltaTime, 0f);
	}
}
