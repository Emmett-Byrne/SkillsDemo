using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraMovement : MonoBehaviour
{
    [SerializeField]
    public float speed = 10;

    private float previousX = 0;

    void Start()
    {
        previousX = Input.mousePosition.x;
    }

    void FixedUpdate()
    {
        float currentX = Input.mousePosition.x;

        //WASD movement
        Vector3 translation = new Vector3(Input.GetAxis("Horizontal"),0,Input.GetAxis("Vertical"));
        translation = Quaternion.Euler(0, transform.eulerAngles.y, 0) * translation;
        translation.Normalize();
        translation *= speed;
        transform.position += translation;
        
        //Spin Camera
        if (Input.GetMouseButton(2))
        {
            Vector3 rotation = transform.eulerAngles;
            rotation.y += (float)((currentX - previousX) * 0.1f);
            transform.eulerAngles = rotation;
        }
        previousX = Input.mousePosition.x;
    }
}
