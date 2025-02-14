using UnityEngine;
using UnityEngine.EventSystems;

public class JoyButton : MonoBehaviour, IPointerUpHandler, IPointerDownHandler // class inherit for interaction
{
    [HideInInspector] // variable is public, accessible to other scripts, but not appear in inspector
    public bool pressed = false;

    // Start is called before the first frame update
    void Start()
    {

    }

    // Update is called once per frame
    void Update()
    {

    }
    public void OnPointerDown(PointerEventData eventData) // button pressed
    {
        pressed = true;
    }

    public void OnPointerUp(PointerEventData eventData) // button release
    {
        pressed = false;
    }

}
