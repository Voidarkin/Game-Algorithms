using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FlyDrone : MonoBehaviour
{
    public GameObject bulletPrefab;
    public float MoveSpeed = 20.0f; // 20 units per second
    public float RotateSpeed = 180.0f; // 180 degrees per second
    public float cooldown = 0.5f;
    // Update is called once per frame
    void Update()
    {
        cooldown -= Time.deltaTime;
        if (Input.GetKeyDown(KeyCode.Space) && cooldown <= 0)
        {
            GameObject.Instantiate(bulletPrefab, transform.position, transform.rotation);
            cooldown = 0.5f;
        }
        // move
        if (Input.GetKey(KeyCode.UpArrow))
        {
            transform.Translate(transform.forward * MoveSpeed * Time.deltaTime,Space.World);
        }
        if (Input.GetKey(KeyCode.DownArrow))
        {
            transform.Translate(-transform.forward * MoveSpeed * Time.deltaTime, Space.World);
        }

        // yaw rotation
        if (Input.GetKey(KeyCode.LeftArrow))
        {
            transform.Rotate(transform.up,-RotateSpeed * Time.deltaTime,Space.World);
        }
        if (Input.GetKey(KeyCode.RightArrow))
        {
            transform.Rotate(transform.up, RotateSpeed * Time.deltaTime,Space.World);
        }

        // pitch rotation
        if (Input.GetKey(KeyCode.W))
        {
            transform.Rotate(transform.right, RotateSpeed * Time.deltaTime, Space.World);
        }
        if (Input.GetKey(KeyCode.S))
        {
            transform.Rotate(transform.right, -RotateSpeed * Time.deltaTime, Space.World);
        }

        // roll rotation
        if (Input.GetKey(KeyCode.A))
        {
            transform.Rotate(transform.forward, RotateSpeed * Time.deltaTime, Space.World);
        }
        if (Input.GetKey(KeyCode.D))
        {
            transform.Rotate(transform.forward, -RotateSpeed * Time.deltaTime, Space.World);
        }
    }
}
