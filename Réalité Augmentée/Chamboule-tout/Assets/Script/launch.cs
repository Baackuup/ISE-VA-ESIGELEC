using System.Collections;
using System.Collections.Generic;
using UnityEngine;


public class launch : MonoBehaviour
{

	public Vector3 init_speed = new Vector3(-1.5f, 0f, 0f);
	private float fallTime;
	private float shotTime;
	private Rigidbody rbGO;
	private GameObject arrow;
	private bool started;
	public ForceInput force;
	public Vector3 init_pos;
	private bool triggered;
	private bool reset;
	protected bool fire_button = false;
	protected JoyButton joybutton;
	protected Joystick joystick;

	private GameObject Can;
	// Use this for initialization
	void Start()
	{
		//You get the Rigidbody component you attach to the GameObject
		fallTime = 0.0f;
		shotTime = 0.0f;
		started = false;
		triggered = false;
		reset = false;
		rbGO = GetComponent<Rigidbody>();
		arrow = GameObject.Find("arrow");
		init_pos = transform.localPosition;
		rbGO.useGravity = false;

		joybutton = FindObjectOfType<JoyButton>();

	}
	public void QuitApp()
	{
		Application.Quit();
	}
	public void AllReset()
	{
		// score back to zero

		// all Cans back on line
		for (int i = 1; i <= 6; i++)
		{
			Can = GameObject.Find("Can" + i.ToString());
			Rigidbody rbb = Can.GetComponent<Rigidbody>();

			if (i == 1)
				Can.transform.position = new Vector3(-0.283f, 0.758f, 0f);
			if (i == 2)
				Can.transform.position = new Vector3(0.221f, 0.758f, 0f);
			if (i == 3)
				Can.transform.position = new Vector3(0.699f, 0.758f, 0f);
			if (i == 4)
				Can.transform.position = new Vector3(-0.018f, 1.32f, 0f);
			if (i == 5)
				Can.transform.position = new Vector3(0.476f, 1.32f, 0f);
			if (i == 6)
				Can.transform.position = new Vector3(0.238f, 1.894f, 0f);


			Can.transform.rotation = Quaternion.identity;
			rbb.velocity = Vector3.zero;
			rbb.angularVelocity = Vector3.zero;
		}
		force.score = 0;
	}

	// Update is called once per frame
	void Update()
	{

		started = Input.GetMouseButtonDown(1);
		if (joybutton)
		{
			if (!fire_button && joybutton.pressed)
			{
				fire_button = true;
				started = true;
			}

			// stop jump action
			if (fire_button && !joybutton.pressed)
				fire_button = false;
		}

		reset = Input.GetMouseButtonDown(2);

		// check for ball speed, if above threshold, start timer
		if (Vector3.Magnitude(rbGO.velocity) > 0.01 && triggered == false)
		{
			// Debug.Log ("triggered");
			triggered = true;
		}

		if (reset)
		{
			AllReset();
		}
		// if time has started you can start playing
		if (fallTime > 0.0f)
		{
			if (started)
			{
				shotTime = 0.0f;
				triggered = true;
				rbGO.WakeUp();
				rbGO.useGravity = true;
				// compute 3d speed vector as unit vector oriented like parent arrow (-Z)
				// multiplied by ballspeed intensity
				Vector3 Zaxis = new Vector3(0, 0, -1);
				Vector3 RotatedX = arrow.transform.rotation * Zaxis;
				RotatedX *= -force.ballspeed;
				// Debug.Log ("speed=" + RotatedX);
				rbGO.AddForce(RotatedX, ForceMode.Impulse);
				started = false;
			}
		}
		else
		{
			rbGO.Sleep();
			//Debug.Log("sleep");
		}

		fallTime += Time.deltaTime;

		if (triggered)
		{
			shotTime += Time.deltaTime;
			if (shotTime > 5.0f)
			{
				transform.localPosition = init_pos;
				rbGO.Sleep();
				rbGO.useGravity = false;
				triggered = false;
				shotTime = 0.0f;
			}
		}
	}
}