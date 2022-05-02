using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraZoom : MonoBehaviour
{
    private float zoomLevel = 60;

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        zoomLevel -= Input.mouseScrollDelta.y;

        transform.localPosition = new Vector3(0, zoomLevel * .6f, -zoomLevel * .4f);
    }
}
