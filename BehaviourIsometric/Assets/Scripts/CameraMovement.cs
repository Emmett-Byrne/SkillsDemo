using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraMovement : MonoBehaviour
{
    public float speed = 10;


    void FixedUpdate()
    {
        Vector3 translation = new Vector3(0,0,0);
        //TODO: Make movement diagonal for better isometric movement.
        translation += new Vector3(0.5f, 0, 0.5f) * Input.GetAxis("Vertical");
        translation += new Vector3(0.5f, 0, -0.5f) * Input.GetAxis("Horizontal");
        translation.Normalize();
        translation *= speed;
        transform.position += translation;
    }
}
