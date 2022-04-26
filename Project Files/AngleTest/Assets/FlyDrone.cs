using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FlyDrone : MonoBehaviour
{
    public float moveSpeed = 10.0f;
    public float rotationSpeed = 100.0f;

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        //Forward and Back
        if(Input.GetKey(KeyCode.UpArrow))
        {
            transform.position += transform.forward * moveSpeed * Time.deltaTime;
        }
        if (Input.GetKey(KeyCode.DownArrow))
        {
            transform.position -= transform.forward * moveSpeed * Time.deltaTime;
        }

        //Left and Right Turning
        if (Input.GetKey(KeyCode.A))
        {
            transform.Rotate(transform.up, -rotationSpeed * Time.deltaTime, Space.World);
        }
        if (Input.GetKey(KeyCode.D))
        {
            transform.Rotate(transform.up, rotationSpeed * Time.deltaTime, Space.World);
        }

        //
        if (Input.GetKey(KeyCode.W))
        {
            transform.Rotate(transform.right, rotationSpeed * Time.deltaTime, Space.World);
        }
        if (Input.GetKey(KeyCode.S))
        {
            transform.Rotate(transform.right, -rotationSpeed * Time.deltaTime, Space.World);
        }

        //
        if (Input.GetKey(KeyCode.Q))
        {
            transform.Rotate(transform.forward, rotationSpeed * Time.deltaTime, Space.World);
        }
        if (Input.GetKey(KeyCode.E))
        {
            transform.Rotate(transform.forward, -rotationSpeed * Time.deltaTime, Space.World);
        }
    }
}
